/**
	notation_spectral.c - spectral functions for notation objects

	by Daniele Ghisi
*/

#include "foundation/bach.h"
#include "dada.notation.spectral.h" // notation.h is inside here
#include "math/llll_settheory.h"

/// ******************************
/// SPECTROGRAM FUNCTIONS
/// ******************************

double get_max_rhythm_length(t_llll *chords_in_gathered_syntax){
	double max_len = 0;
	t_llllelem *elem;
	for (elem = chords_in_gathered_syntax->l_head; elem; elem = elem->l_next){
		if (hatom_gettype(&elem->l_hatom) == H_LLLL){
			t_llll *voicellll = hatom_getllll(&elem->l_hatom);
			t_llllelem *chelem;
			for (chelem = voicellll->l_head; chelem; chelem = chelem->l_next){
				if (hatom_gettype(&chelem->l_hatom) == H_LLLL) {
					t_llll *chllll = hatom_getllll(&chelem->l_hatom);
					if (chllll && chllll->l_head && chllll->l_head->l_next && is_hatom_number(&chllll->l_head->l_hatom)){
						double onset = hatom_getdouble(&chllll->l_head->l_hatom);
						t_llllelem *noteselem;
						for (noteselem = chllll->l_head->l_next; noteselem; noteselem = noteselem->l_next){
							if (hatom_gettype(&noteselem->l_hatom) == H_LLLL) {
								t_llll *thisllll = hatom_getllll(&noteselem->l_hatom);
								double dur = (thisllll->l_head && thisllll->l_head->l_next && is_hatom_number(&thisllll->l_head->l_next->l_hatom) ? hatom_getdouble(&thisllll->l_head->l_next->l_hatom) : 0);
								if (onset + dur > max_len)
									max_len = onset + dur;
							}
						}
					}
				}
			}
		}
	}
	return max_len;
}


t_llll *cut_window_from_rhythm(t_llll *chords_in_gathered_syntax, double win_start_ms, double win_end_ms){
	t_llll *windowed_chords = llll_get();
	t_llllelem *elem;
	for (elem = chords_in_gathered_syntax->l_head; elem; elem = elem->l_next){
		if (hatom_gettype(&elem->l_hatom) == H_LLLL){
			t_llll *newvoicellll = llll_get();
			t_llll *voicellll = hatom_getllll(&elem->l_hatom);
			t_llllelem *chelem;
			for (chelem = voicellll->l_head; chelem; chelem = chelem->l_next){
				if (hatom_gettype(&chelem->l_hatom) == H_LLLL) {
					t_llll *chllll = hatom_getllll(&chelem->l_hatom);
					if (chllll && chllll->l_head && chllll->l_head->l_next && is_hatom_number(&chllll->l_head->l_hatom)){
						double onset = hatom_getdouble(&chllll->l_head->l_hatom);
						if (onset >= win_start_ms && onset <= win_end_ms)
							llll_appendhatom_clone(newvoicellll, &chelem->l_hatom, 0, WHITENULL_llll);
					}
				}
			}
			llll_appendllll(windowed_chords, newvoicellll, 0, WHITENULL_llll);
		}
	}
	return windowed_chords;
}


//onsets must be with respect to the window (so if an event starts at the beginning of the window, this is 0)
// chords_in_gathered_syntax must be (onset (pitch dur vel) (pitch dur vel)...) (onset (pitch dur vel)...)...

void get_spectral_rhythm_config_in_window(double win_start_ms, double win_end_ms, t_llll *chords_in_gathered_syntax, 
											 char is_chord_onset_relative_to_window, char is_single_frame, e_win_types window_type, double velocity_handling_slope, 
											 double voice_coupling, double outer_mc_threshold, double inner_mc_threshold, char normalize, char show_phase,
											 t_llll **separate_peaks,
											 double *sampled_amplitudes, double *sampled_phase, long num_sampling_points, double min_bpm, double max_bpm, double decay_bpm,
											 double min_singleampli_threshold, double min_globalampli_threshold, e_shape_types shape_of_contributions, char filter_subharmonics){
	double win_dur = win_end_ms - win_start_ms;
	double relative_end_ms = 0;
	double *weight_of_index_i;
	t_llll *laced_llll;
	t_llllelem *elem;
	long i;
	t_llllelem *lacedelem1, *lacedelem2;
	double accounted_couples;
	weight_of_index_i = (double *) bach_newptr(num_sampling_points * sizeof (double));
							 
	if (separate_peaks)
		*separate_peaks = llll_get(); 

	if (sampled_amplitudes){
		long i;
		for (i = 0; i < num_sampling_points; i++) {
			sampled_amplitudes[i] = 0;
			sampled_phase[i] = 0;
			weight_of_index_i[i] = 0;
		}
	}
	
	// step1: build a interlaced list containing (onset voice_number pitch dur vel) (onset voice_number pitch dur vel) (onset voice_number pitch dur vel)... for each note
	laced_llll = llll_get();
	
	i = 0;
	for (elem = chords_in_gathered_syntax->l_head; elem; elem = elem->l_next){
		if (hatom_gettype(&elem->l_hatom) == H_LLLL){
			t_llll *voicellll = hatom_getllll(&elem->l_hatom);
			t_llllelem *chelem;
			i++;
			for (chelem = voicellll->l_head; chelem; chelem = chelem->l_next){
				if (hatom_gettype(&chelem->l_hatom) == H_LLLL) {
					t_llll *chllll = hatom_getllll(&chelem->l_hatom);
					if (chllll && chllll->l_head && chllll->l_head->l_next && is_hatom_number(&chllll->l_head->l_hatom)){
						double onset = hatom_getdouble(&chllll->l_head->l_hatom);
						double relative_onset = is_chord_onset_relative_to_window ? onset : onset - win_start_ms;
						if (relative_onset >= 0 && (relative_onset <= win_dur || is_single_frame)){ 
							t_llllelem *noteselem;
							for (noteselem = chllll->l_head->l_next; noteselem; noteselem = noteselem->l_next){
								if (hatom_gettype(&noteselem->l_hatom) == H_LLLL) {
									t_llll *thisllll = hatom_getllll(&noteselem->l_hatom);
									t_llll *notellll = llll_get();
									double mc = (thisllll->l_head && is_hatom_number(&thisllll->l_head->l_hatom) ? hatom_getdouble(&thisllll->l_head->l_hatom) : 0);
									double dur = (thisllll->l_head && thisllll->l_head->l_next && is_hatom_number(&thisllll->l_head->l_next->l_hatom) ? hatom_getdouble(&thisllll->l_head->l_next->l_hatom) : 0);
									long vel = (thisllll->l_head && thisllll->l_head->l_next && thisllll->l_head->l_next->l_next && is_hatom_number(&thisllll->l_head->l_next->l_next->l_hatom) ? hatom_getlong(&thisllll->l_head->l_next->l_next->l_hatom) : 0);
									if (relative_onset + dur > relative_end_ms)
										relative_end_ms = relative_onset + dur;
									
									llll_appenddouble(notellll, relative_onset, 0, WHITENULL_llll);
									llll_appendlong(notellll, i, 0, WHITENULL_llll); // voice number
									llll_appenddouble(notellll, mc, 0, WHITENULL_llll);
									llll_appenddouble(notellll, dur, 0, WHITENULL_llll);
									llll_appendlong(notellll, vel, 0, WHITENULL_llll);
									llll_appendllll(laced_llll, notellll, 0, WHITENULL_llll);
								}
							}
						}
					}
				}
			}
		}
	}
	
	if (is_single_frame)
		win_dur = relative_end_ms;

	// step2: sort list by onse
	llll_inplacesort(laced_llll, (sort_fn) llll_sort_by_first);

	// step3: consider each couples of elements
	accounted_couples = 0;
	for (lacedelem1 = laced_llll->l_head; lacedelem1; lacedelem1 = lacedelem1->l_next){
		for (lacedelem2 = lacedelem1->l_next; lacedelem2; lacedelem2 = lacedelem2->l_next){
			double weight = 1.; // weight for the couple
			double weight_windowing, weight_velocity, weight_pitch, weight_voices;
			t_llll *llll1 = hatom_getllll(&lacedelem1->l_hatom);
			t_llll *llll2 = hatom_getllll(&lacedelem2->l_hatom);
			double onset1 = hatom_getdouble(&llll1->l_head->l_hatom);
			double onset2 = hatom_getdouble(&llll2->l_head->l_hatom);
			long voicenum1 = hatom_getlong(&llll1->l_head->l_next->l_hatom);
			long voicenum2 = hatom_getlong(&llll2->l_head->l_next->l_hatom);
			double mc1 = hatom_getdouble(&llll1->l_head->l_next->l_next->l_hatom);
			double mc2 = hatom_getdouble(&llll2->l_head->l_next->l_next->l_hatom);
//			double dur1 = hatom_getdouble(&llll1->l_head->l_next->l_next->l_next->l_hatom); // unused for now, that's ok
//			double dur2 = hatom_getdouble(&llll2->l_head->l_next->l_next->l_next->l_hatom); // unused for now, that's ok
			long vel1 = hatom_getlong(&llll1->l_head->l_next->l_next->l_next->l_next->l_hatom);
			long vel2 = hatom_getlong(&llll2->l_head->l_next->l_next->l_next->l_next->l_hatom);
			
			if (onset2 == onset1) {
				// we don't take this into consideration
			} else if (onset2 > onset1) {
				double delta_onsets = onset2 - onset1;
				double freq = 1000./delta_onsets;
				double phase = TWOPI * (onset1/delta_onsets - floor(onset1/delta_onsets));
				double bpm = freq * 60;
				
				//a. change global weigth of the couple with respect to the windowing
				if (window_type == k_WIN_HANNING) {
					weight_windowing = (weight/4.) * (2 - cos(TWOPI * onset1/win_dur) - cos(TWOPI * onset1/win_dur));
				} else if (window_type == k_WIN_HAMMING) {
					weight_windowing = (weight/2.) * (1.08 - 0.46 * cos(TWOPI * onset1/win_dur) - 0.46 * cos(TWOPI * onset2/win_dur));
				} else if (window_type == k_WIN_COSINE) { 
					weight_windowing = (weight/2.) * (cos((onset1/win_dur - 0.5) * PIOVERTWO) + cos((onset2/win_dur - 0.5) * PIOVERTWO));
				} else if (window_type == k_WIN_TRIANGULAR) {
					weight_windowing = (weight/2.) * (fabs(onset2 - win_dur/2.)/(win_dur/2.) + fabs(onset1 - win_dur/2.)/(win_dur/2.));
				} else {
					weight_windowing = 1.;
				}
				
				//b. change weigth depending on velocities
				weight_velocity = rescale_with_slope((vel2 + vel1)/2., CONST_MIN_VELOCITY, CONST_MAX_VELOCITY, 0, 1, velocity_handling_slope);

				//c. change weight depending on voices
				weight_voices = (voicenum1 == voicenum2 ? 1. : voice_coupling);
				accounted_couples += weight_voices;
				
				//d. change weight depending on pitches
				weight_pitch = CLAMP(rescale_with_slope(fabs(mc2 - mc1), inner_mc_threshold, outer_mc_threshold, 0, 1, 0), 0., 1.);
				
				dev_post("(%.2fms, %.2fmc, voice %ld) and (%.2fms, %.2fmc, voice %ld)", onset1, mc1, voicenum1, onset2, mc2, voicenum2);
				dev_post("    >> freq: %.2fbpm, %.2fHz. Weights: window %.2f, vel %.2f, pitch %.2f, voices %.2f", freq, bpm, weight_windowing, weight_velocity, weight_pitch, weight_voices);

				// global weight (amplitude)
				weight = pow(weight_windowing * weight_velocity * weight_pitch * weight_voices, 1./4.);
				
				if (weight >= min_singleampli_threshold) {
					if (separate_peaks) {
						t_llll *this_llll = llll_get();
						llll_appenddouble(this_llll, freq, 0, WHITENULL_llll);
						llll_appenddouble(this_llll, weight, 0, WHITENULL_llll);
						llll_appenddouble(this_llll, phase, 0, WHITENULL_llll);
						llll_appendllll(*separate_peaks, this_llll, 0, WHITENULL_llll);
					} 

					if (sampled_amplitudes)
						take_amplitude_into_account(bpm, weight, true, phase, sampled_amplitudes, sampled_phase, num_sampling_points, min_bpm, max_bpm, decay_bpm, weight_of_index_i, shape_of_contributions, false);
				} 
			} else {
				dev_post("Bug in spectrorhythm!");
			}
		}
	}
	
	if (normalize && accounted_couples > 0){
		for (i = 0; i < num_sampling_points; i++) {
			sampled_amplitudes[i] /= accounted_couples;
			if (sampled_amplitudes[i] < min_globalampli_threshold)
				sampled_amplitudes[i] = 0;
		}
	}
	bach_freeptr(weight_of_index_i);
	llll_free(laced_llll);
}


void take_amplitude_into_account(double bpm, double ampli, char consider_phase, double phase, double *sampled_amplitudes, double *sampled_phases, long num_sampling_points, 
								 double min_bpm, double max_bpm, double decay_bpm, double *weight_of_index_i, e_shape_types shape_of_contributions, char check_nonnegative_ampli){
	if (bpm >= min_bpm && bpm <= max_bpm){ 
		long max_idx, min_idx, i;
		
		// retrieving max an min index to change in the arrays
		if (shape_of_contributions == k_SHAPE_PUNCTUAL) {
			max_idx = min_idx = (long) CLAMP(round(rescale(bpm, min_bpm, max_bpm, 0, num_sampling_points - 1)), 0, num_sampling_points - 1);
		} else {
			min_idx = (long) CLAMP(floor(rescale(bpm-decay_bpm, min_bpm, max_bpm, 0, num_sampling_points - 1)), 0, num_sampling_points - 1);
			max_idx = (long) CLAMP(ceil(rescale(bpm+decay_bpm, min_bpm, max_bpm, 0, num_sampling_points - 1)), 0, num_sampling_points - 1);
		}
		
		for (i = min_idx; i <= max_idx; i++){
			double this_bpm = rescale_with_slope(i, 0, num_sampling_points - 1, min_bpm, max_bpm, 0);
			double this_weight;
			if (decay_bpm < 0)
				this_weight = ampli;
			else {
				double t = (bpm - this_bpm)/decay_bpm; // between -1. and 1.
				if (shape_of_contributions == k_SHAPE_TRIANGULAR)
					this_weight = ampli * (1. - fabs(t));
				else if (shape_of_contributions == k_SHAPE_COSINE) 
					this_weight = ampli * cos(t * PIOVERTWO);
				else if (shape_of_contributions == k_SHAPE_HANNING) 
					this_weight = ampli * (0.5 * (1 - cos((t + 1.) * PI)));
				else if (shape_of_contributions == k_SHAPE_GAUSSIAN) 
					this_weight = ampli * exp(-0.5*(t*t/0.1024));				// TO DO: use a table for optimization!
				else	// punctual: k_SHAPE_PUNCTUAL: only nearest bin is taken into account
					this_weight = ampli;
			}
			
			sampled_amplitudes[i] += MAX(0, this_weight);
			if (check_nonnegative_ampli && sampled_amplitudes[i] < 0)
				sampled_amplitudes[i] = 0;
			
			if (consider_phase) {
				if (this_weight > weight_of_index_i[i]){
					sampled_phases[i] = phase;
					weight_of_index_i[i] = ampli;
				}
			}
		}
	}
}


/// ******************************
/// MODELING ONSET FUNCTION
/// ******************************

// onsetf must already be initialized and containing at least num_sampling_point elements. it'll be filled with the correct onset function data.
// sampling step is in milliseconds
void gathered_syntax_to_onset_function(t_llll *chords_in_gathered_syntax, long num_sampling_points, double sampling_freq, double *onsetf, e_shape_types shape_of_contributions, double peak_spreading_ms)
{
	long i;
	t_llllelem *elem;
	double sampling_step_ms = 1000 / sampling_freq;
	double max_representable_onset = num_sampling_points * sampling_step_ms;
	double h = peak_spreading_ms / sampling_step_ms; // spread in number of bins
	
	// 1. erasing onsetf array
	for (i = 0; i < num_sampling_points; i++)
		onsetf[i] = 0.;

	// 2. filling onsetf array
	for (elem = chords_in_gathered_syntax->l_head; elem; elem = elem->l_next){
		if (hatom_gettype(&elem->l_hatom) == H_LLLL){
			t_llll *voicellll = hatom_getllll(&elem->l_hatom);
			t_llllelem *chelem;
			for (chelem = voicellll->l_head; chelem; chelem = chelem->l_next){
				if (hatom_gettype(&chelem->l_hatom) == H_LLLL) {
					t_llll *chllll = hatom_getllll(&chelem->l_hatom);
					if (chllll && chllll->l_head && chllll->l_head->l_next && is_hatom_number(&chllll->l_head->l_hatom)){
						double onset = hatom_getdouble(&chllll->l_head->l_hatom);
						if (onset >= 0 && onset <= max_representable_onset){ 
							double chord_energy = 0;
							t_llllelem *noteselem;
							for (noteselem = chllll->l_head->l_next; noteselem; noteselem = noteselem->l_next){
								if (hatom_gettype(&noteselem->l_hatom) == H_LLLL) {
									t_llll *thisllll = hatom_getllll(&noteselem->l_hatom);
//									double mc = (thisllll->l_head && is_hatom_number(&thisllll->l_head->l_hatom) ? hatom_getdouble(&thisllll->l_head->l_hatom) : 0);
//									double dur = (thisllll->l_head && thisllll->l_head->l_next && is_hatom_number(&thisllll->l_head->l_next->l_hatom) ? hatom_getdouble(&thisllll->l_head->l_next->l_hatom) : 0);
									long vel = (thisllll->l_head && thisllll->l_head->l_next && thisllll->l_head->l_next->l_next && is_hatom_number(&thisllll->l_head->l_next->l_next->l_hatom) ? hatom_getlong(&thisllll->l_head->l_next->l_next->l_hatom) : 0);
									
									chord_energy += ((double)vel)/CONST_MAX_VELOCITY;
									
								}
							}
							if (chord_energy > 0){
								// we add the contribution of the chord in the proper bins of the onsetf array
								
								if (shape_of_contributions == k_SHAPE_PUNCTUAL) {
									// easiest case, just find the proper bin
									long bin_idx = (long) CLAMP(round(onset/sampling_step_ms), 0, num_sampling_points - 1);
									onsetf[bin_idx] += sqrt(chord_energy);

								} else if (shape_of_contributions == k_SHAPE_TRIANGULAR) {
									// default case: spreading the peak with triangular shape on <peak_spreading> bins (h)
									double b = sqrt((3 * chord_energy) / (2 * h)); // maximum y value of the peak function, assumed at x = onset
									long j, center_bin_idx = (long) floor(onset/sampling_step_ms);
									
									for (j = MAX(0, center_bin_idx - h); j <= center_bin_idx + h && j < num_sampling_points; j++) {
										double bin_from = j * sampling_step_ms;
										double bin_to = bin_from + sampling_step_ms;
										
										if (bin_from <= onset && onset <= bin_to) {
											double f_bin_from = bin_from * b / h - onset * b / h + b;
											double f_bin_to = -bin_to * b / h + onset * b / h + b;

											// central point: contribution is a double trapece (unless one or both of the two sides is actually a triangle, if h is very small)
											if (f_bin_from >= 0)
												onsetf[j] += MAX(0, (b + f_bin_from) * (onset - bin_from) / 2.);
											else
												onsetf[j] += MAX(0, b * h / 2.);
												
											if (f_bin_to >= 0)
												onsetf[j] += MAX(0, (b + f_bin_to) * (bin_to - onset) / 2.);
											else 
												onsetf[j] += MAX(0, b * h / 2.);
												
										} else if (bin_from < onset) {
											// we're in the part of the function under the segment y = (b/h) x - ab/h +b

											double f_bin_from = bin_from * b / h - onset * b / h + b;
											double f_bin_to = bin_to * b / h - onset * b / h + b;

											if (f_bin_from >= 0) {
												onsetf[j] += (f_bin_from + f_bin_to) * sampling_step_ms / 2.;
											} else if (f_bin_to > 0) {
												onsetf[j] += f_bin_to * (bin_to - (onset - h)) / 2.;
											}
										} else if (bin_from > onset) {
											// we're in the part of the function under the segment y = -(b/h) x + ab/h +b

											double f_bin_from = -bin_from * b / h + onset * b / h + b;
											double f_bin_to = -bin_to * b / h + onset * b / h + b;

											if (f_bin_to >= 0) {
												onsetf[j] += (f_bin_from + f_bin_to) * sampling_step_ms / 2.;
											} else if (f_bin_from > 0) {
												onsetf[j] += f_bin_from * ((onset + h) - bin_from) / 2.;
											}
										}
									}
								}
								
								// TO DO: taking into account note-release as well?
							}
						}
					}
				}
			}
		}
	}
}


void free_multiphase_spectrogram(t_multiphase_spectrogram *mph){
	long i;
	for (i = 0; i < mph->num_samples; i++)
		bach_freeptr(mph->bins[i]);
	bach_freeptr(mph->bins);
}


	
	
// remove "noise" in gathered syntax by clustering and then taking the average
// destructive, works "inplace"
void cluster_averaging(t_llll **chords_in_gathered_syntax, double thresh_ms) 
{
	t_llllelem *elem, *cur;
	t_llll *cloned = llll_clone(*chords_in_gathered_syntax); // we work on a copy 

	// appending voice number to each element
	long i;
	for (i = 1, elem = cloned->l_head; elem; i++){
		t_llllelem *nextchelem = elem->l_next;
		if (hatom_gettype(&elem->l_hatom) == H_LLLL){
			t_llll *voicellll = hatom_getllll(&elem->l_hatom);
			t_llllelem *chelem = voicellll->l_head;
			while (chelem) {
				t_llllelem *nextchelem = chelem->l_next;
				if (hatom_gettype(&chelem->l_hatom) == H_LLLL) {
					t_llll *chllll = hatom_getllll(&chelem->l_hatom);
					llll_appendlong(chllll, i, 0, WHITENULL_llll);
				} else 
					llll_destroyelem(chelem);
				chelem = nextchelem;
			}
		} else 
			llll_destroyelem(elem);
		elem = nextchelem;
	}
	llll_flat(cloned, 0, 1, 0, LLLL_FREETHING_DONT); // remove "voice" level
	llll_inplacesort(cloned, (sort_fn)llll_sort_by_first); // sorting by onset
	
	dev_llll_print(cloned, NULL, 0, 2, NULL);
	
	// clustering and averaging
	while (true) {
		// finding smallest difference
		t_llllelem *best_diff_el = NULL;
		double best_diff = 0;
		for (cur = cloned->l_head; cur && cur->l_next; cur = cur->l_next) {
			double this_onset = hatom_getdouble(&cur->l_hatom.h_w.w_llll->l_head->l_hatom);
			double next_onset = hatom_getdouble(&cur->l_next->l_hatom.h_w.w_llll->l_head->l_hatom);
			double this_diff = next_onset - this_onset;
			
			if (this_diff > 0) {
				if (!best_diff_el || this_diff < best_diff) {
					best_diff = this_diff;
					best_diff_el = cur;
				}
			}
		}
		
		if (!best_diff_el || best_diff > thresh_ms)	
			break;
		
		// trying to extend the diffs to previous and/or next, to finally found the cluster (left, right)
		t_llllelem *left = best_diff_el, *right = best_diff_el->l_next;
		double tot_width = best_diff;
		while (left && right && tot_width < thresh_ms) {
			double right_adj = 0, left_adj = 0;
			
			if (right->l_next)
				right_adj = hatom_getdouble(&right->l_next->l_hatom.h_w.w_llll->l_head->l_hatom) - hatom_getdouble(&right->l_hatom.h_w.w_llll->l_head->l_hatom);
			if (left->l_prev)
				left_adj = hatom_getdouble(&left->l_hatom.h_w.w_llll->l_head->l_hatom) - hatom_getdouble(&left->l_prev->l_hatom.h_w.w_llll->l_head->l_hatom);
			
			if (!left->l_prev && !right->l_next)
				break;
			else if (left->l_prev && (!right->l_next || left_adj <= right_adj)) {
				if (tot_width + left_adj < thresh_ms) {
					left = left->l_prev;
					tot_width += left_adj;
				} else
					break;
			} else if (right->l_next && (!left->l_next || left_adj >= right_adj)) {
				if (tot_width + right_adj < thresh_ms) {
					right = right->l_next;
					tot_width += right_adj;
				} else
					break;
			} else
				break;
		}
		
		
		// computing average of cluster positions
		double sum = 0;
		long count = 0;
		for (elem = left; elem; elem = elem->l_next) {
			count++;
			sum += hatom_getdouble(&elem->l_hatom.h_w.w_llll->l_head->l_hatom);
			if (elem == right)
				break;
		}
		

		sum /= count;
		
		// reassigning onset to all elements in the cluster
		for (elem = left; elem; elem = elem->l_next, count++) {
			hatom_setdouble(&elem->l_hatom.h_w.w_llll->l_head->l_hatom, sum);
			if (elem == right)
				break;
		}
		
	}
	

	// reassign voice-wise ordering
	llll_inplacesort(cloned, (sort_fn)llll_sort_by_last); // mergesort is stable, thus onsets are ordere
	cur = cloned->l_head;
	elem = cur ? cur->l_next : NULL;
	long cur_long = 1;
	while (elem) {
		t_llllelem *nextelem = elem->l_next;
		long this_id = hatom_getlong(&elem->l_hatom.h_w.w_llll->l_tail->l_hatom);
		if (this_id > cur_long){
			llll_wrap_element_range(cur, elem->l_prev);
			cur = elem;
			cur_long = this_id;
		}
		elem = nextelem;
	}
	llll_wrap_element_range(cur, cloned->l_tail);
	
	
	llll_free(*chords_in_gathered_syntax);
	*chords_in_gathered_syntax = cloned;
}		


t_llll *only_keep_values_in_range(t_llll *ll, double from, double to)
{
	t_llllelem *elem;
	t_llll *out = llll_get();
	for (elem = ll->l_head; elem; elem = elem->l_next){
		double d = hatom_getdouble(&elem->l_hatom);
		if (d >= from && d <= to)
			llll_appenddouble(out, d, 0, WHITENULL_llll);
	}
	return out;
}

// voice_num is 1-based
double get_median_hz(t_llll *onsets, long voice_num, double center_ms, double window_size_ms) 
{
	double start = center_ms - window_size_ms;
	double end = center_ms + window_size_ms;
	double res = 0;
	t_llllelem *llelem = llll_getindex(onsets, voice_num, I_STANDARD);
	if (llelem && hatom_gettype(&llelem->l_hatom) == H_LLLL) {
		t_llll *ll = hatom_getllll(&llelem->l_hatom);
		t_llll *trimmed = only_keep_values_in_range(ll, start, end);
		t_llll *dx = llll_x2dx_of_plain_double_llll(trimmed);
		t_hatom median;
		hatom_setdouble(&median, 0); // we initialize it
		llll_inplacesort(dx, (sort_fn)llll_leq_elem);
		llll_median(dx, &median);
		res = hatom_getdouble(&median); // this is in ms
		res = 1000./res; // this is in hertz
		llll_free(trimmed);
		llll_free(dx);
	}
	return res;
}

t_llll *only_keep_notes_gathered_values_in_range(t_llll *ll, double from, double to, t_llllelem **last_taken_elem)
{
	t_llllelem *elem;
	t_llll *out = llll_get();
	for (elem = ll->l_head; elem; elem = elem->l_next){
		double onset = hatom_getdouble(&elem->l_hatom.h_w.w_llll->l_head->l_hatom);
		double dur = hatom_getdouble(&elem->l_hatom.h_w.w_llll->l_head->l_next->l_next->l_next->l_hatom);
		if (onset >= from && onset <= to || onset + dur >= from && onset + dur <= to || onset <= from && onset + dur >= to) {
			llll_appendhatom_clone(out, &elem->l_hatom, 0, WHITENULL_llll);
			if (last_taken_elem)
				*last_taken_elem = elem;
		}
	}
	return out;
}


double snap_to_nearest_onset_from_notes_gathered_values(t_llll *ll, double onset)
{
	t_llllelem *elem;
	double best = onset;
	for (elem = ll->l_head; elem; elem = elem->l_next){
		double thisonset = hatom_getdouble(&elem->l_hatom.h_w.w_llll->l_head->l_hatom);
		if (thisonset == onset)
			return onset;
		else if (thisonset < onset)
			best = thisonset;
		else {
			if (thisonset - onset < onset - best)
				return thisonset;
			else
				return best;
		}
	}
	return best;
}


//returns chroma norm
double get_chroma_and_tonal_centroid(t_llll *notes_laced_llll, double *chroma, double *tonal_centroid, 
										char blackandwhite_chroma, char use_decay, double win_start, double win_end, char win_direction)
{
	const double r1 = 1;
	const double r2 = 1;
	const double r3 = 0.5;
	t_llllelem *elem;
	double chroma_norm = 0;
	
	long i;
	for (i = 0; i < 12; i++)
		chroma[i] = 0;
	
	// calculating chroma
	for (elem = notes_laced_llll->l_head; elem; elem = elem->l_next) {
		t_llll *ll = elem->l_hatom.h_w.w_llll;
		double this_mc = hatom_getdouble(&ll->l_head->l_next->l_next->l_hatom);
		double this_vel = hatom_getdouble(&ll->l_head->l_next->l_next->l_next->l_next->l_hatom);
		double contribution = blackandwhite_chroma ? 1 : this_vel/CONST_MAX_VELOCITY;
		if (use_decay) {
			double win_size = win_end - win_start;
			double pt_ms = hatom_getdouble(&ll->l_head->l_hatom) + (win_direction == 1 ? 0 : hatom_getdouble(&ll->l_head->l_next->l_next->l_next->l_hatom));
			double factor = CLAMP((win_size - (win_direction == 1 ? pt_ms - win_start : win_end - pt_ms))/win_size, 0, 1);
			contribution *= factor;
		}
		if (blackandwhite_chroma) {
			if (contribution > chroma[mc_to_pitch_class(this_mc, 12)])
				chroma[mc_to_pitch_class(this_mc, 12)] = contribution;
		} else {
			chroma[mc_to_pitch_class(this_mc, 12)] += contribution;
		}
	}
	
	for (i = 0; i < 12; i++)
		chroma_norm += fabs(chroma[i]);
	
	// calculating tonal centroid
	if (chroma_norm > 0) {
		for (i = 0; i < 6; i++)
			tonal_centroid[i] = 0;
		for (i = 0; i < 12; i++) {
			tonal_centroid[0] += r1 * sin(i * 7 * PI / 6.) * chroma[i];
			tonal_centroid[1] += r1 * cos(i * 7 * PI / 6.) * chroma[i];
			tonal_centroid[2] += r2 * sin(i * 3 * PI / 2.) * chroma[i];
			tonal_centroid[3] += r2 * cos(i * 3 * PI / 2.) * chroma[i];
			tonal_centroid[4] += r3 * sin(i * 2 * PI / 3.) * chroma[i];
			tonal_centroid[5] += r3 * cos(i * 2 * PI / 3.) * chroma[i];
		}
		for (i = 0; i < 6; i++)
			tonal_centroid[i] /= chroma_norm;
	}
	return chroma_norm;
}

double get_tonal_centroids_dist(double *tonal_centroid1, double *tonal_centroid2)
{
	long i;
	double dist = 0;
	for (i = 0; i < 5; i++) {
		double this_val = fabs(tonal_centroid1[i] - tonal_centroid2[i]);
		dist += this_val * this_val;
	}
	return sqrt(dist);
}

t_llll *detect_harmonic_changes(t_llll *notes_laced_llll, double win_size, double hop_size, double harmonic_changes_contribution, 
								char snap_to_nearest_onset, double median_filter_window_ms, double delete_softer_harmonic_changes_inside_win_ms, t_llll **debug)
{
	// IMPLEMENTATION could be faster
	// we follow Detecting Harmonic Change In Musical Audio (Christopher Harte and Mark Sandler, Martin Gasser)
	
	if (!notes_laced_llll || !notes_laced_llll->l_tail)
		return llll_get();
	else {
		
		// detecting max onset (is the last onset)
		double max_onset = hatom_getdouble(&notes_laced_llll->l_tail->l_hatom.h_w.w_llll->l_head->l_hatom);
		t_llllelem *elem;
		
		// build an llll containing ((start_ms end_ms) (<chroma vector>) (<tonal centroid>))
		double onset1, onset2;
		double prev_centroid[6];
		prev_centroid[0] = prev_centroid[1] = prev_centroid[2] = prev_centroid[3] = prev_centroid[4] = prev_centroid[5] = 0;

		long i;
		t_llll *transition_probabilities = llll_get();
		t_llll *transition_onsets = llll_get();
		t_llll *filtered_probabilities;

		long num_peaks = 0;
		double *peak_bins = NULL, *peak_amplis = NULL, *peak_phases = NULL;
		long *peak_bin_widths = NULL;
		
		t_llll *out_trans;
		double *fpr, *dummy_phase;
		long j, k;

		if (debug)
			*debug = llll_get();
		
		for (onset1 = 0, onset2 = onset1 + win_size; onset2 <= max_onset - win_size; onset1 += hop_size, onset2 += hop_size) {
			t_llll *partial1 = only_keep_notes_gathered_values_in_range(notes_laced_llll, onset1, onset1 + win_size, NULL);
			t_llll *partial2 = only_keep_notes_gathered_values_in_range(notes_laced_llll, onset2, onset2 + win_size, NULL);
			
			double this_dist;

			double chroma1[12], tonal_centroid1[6], chroma_norm1 = 0;
			double chroma2[12], tonal_centroid2[6], chroma_norm2 = 0;
			
			chroma_norm1 = get_chroma_and_tonal_centroid(partial1, chroma1, tonal_centroid1, true, true, onset1, onset1 + win_size, -1);
			chroma_norm2 = get_chroma_and_tonal_centroid(partial2, chroma2, tonal_centroid2, true, true, onset2, onset2 + win_size, 1);
			
			this_dist = get_tonal_centroids_dist(tonal_centroid1, tonal_centroid2);
			
			llll_appenddouble(transition_probabilities, this_dist, 0, WHITENULL_llll);
			llll_appenddouble(transition_onsets, onset2, 0, WHITENULL_llll);
			
			if (false) { // debug
				post("-------------"); 
				post("> onset1 (%.0f, %.0f)", onset1, onset1 + win_size);
				post("       chroma1 [%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f]", 
					 chroma1[0], chroma1[1], chroma1[2], chroma1[3], chroma1[4], chroma1[5], 
					 chroma1[6], chroma1[7], chroma1[8], chroma1[9], chroma1[10], chroma1[11]);
				post("       tonal centroid1 [%.2f %.2f %.2f %.2f %.2f %.2f]", 
					 tonal_centroid1[0], tonal_centroid1[1], tonal_centroid1[2], tonal_centroid1[3], 
					 tonal_centroid1[4], tonal_centroid1[5]);
				post("> onset2 (%.0f, %.0f)", onset2, onset2 + win_size);
				post("       chroma2 [%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f]", 
					 chroma2[0], chroma2[1], chroma2[2], chroma2[3], chroma2[4], chroma2[5], 
					 chroma2[6], chroma2[7], chroma2[8], chroma2[9], chroma2[10], chroma2[11]);
				post("       tonal centroid2 [%.2f %.2f %.2f %.2f %.2f %.2f]", 
					 tonal_centroid2[0], tonal_centroid2[1], tonal_centroid2[2], tonal_centroid2[3], 
					 tonal_centroid2[4], tonal_centroid2[5]);
				post("> dist = %.4f", this_dist);
			}
			llll_free(partial1);
			llll_free(partial2);
		}
		
		// filtering transition_probabilities
		filtered_probabilities = llll_medianfilter(transition_probabilities, MAX(1, (long) round(median_filter_window_ms/hop_size))); // filtering

//		filtered_probabilities = llll_meanfilter(transition_probabilities, 0); //MAX(1, (long) round(400./hop_size)));
//		filtered_probabilities = llll_clone(transition_probabilities);

		if (false) { // debug
			llll_print(transition_probabilities, NULL, 0, 2, NULL);
			llll_print(filtered_probabilities, NULL, 0, 2, NULL);
		}

		if (debug) {
			t_llll *d1 = llll_get();
			llll_appendllll_clone(d1, transition_onsets, 0, WHITENULL_llll, NULL);
			llll_appendllll_clone(d1, filtered_probabilities, 0, WHITENULL_llll, NULL);
			llll_trans_inplace(d1, 0);
			llll_appendllll(*debug, d1, 0, WHITENULL_llll);
		}
		

		fpr = (double *)bach_newptr(filtered_probabilities->l_size * sizeof(double));
		dummy_phase = (double *)bach_newptr(filtered_probabilities->l_size * sizeof(double));
		for (elem = filtered_probabilities->l_head, i = 0; i < (long)filtered_probabilities->l_size; elem = elem ? elem->l_next : NULL, i++)  {
			fpr[i] = hatom_getdouble(&elem->l_hatom);
			dummy_phase[i] = 0;
		}
		
		// finding tonal transitions
		out_trans = llll_get();

		find_peaks_for_frame(filtered_probabilities->l_size, fpr, dummy_phase, 0, 0.3, 0, &num_peaks, &peak_bins, &peak_amplis, &peak_phases, &peak_bin_widths, false);

		// filtering soft peaks lying near to higher peaks
		for (i = 0; i < num_peaks - 1; i++) {
			double onset_i = win_size + peak_bins[i] * hop_size;
			for (j = i+1; j < num_peaks; j++) {
				double onset_j = win_size + peak_bins[j] * hop_size;
				if (fabs(onset_i - onset_j) < delete_softer_harmonic_changes_inside_win_ms) {
					// gotta delete onset_j
					for (k = j+1; k < num_peaks; k++) {
						peak_bins[k-1] = peak_bins[k];
						peak_amplis[k-1] = peak_amplis[k];
						peak_phases[k-1] = peak_phases[k];
						peak_bin_widths[k-1] = peak_bin_widths[k];
					}
					num_peaks--;
					j--;
				}
			}
		}
		
		if (debug) {
			t_llll *d2 = llll_get();
			for (i = 0; i < num_peaks; i++) {
				t_llll *this_ll = llll_get();
				double onset = win_size + peak_bins[i] * hop_size;
				llll_appenddouble(this_ll, snap_to_nearest_onset ? snap_to_nearest_onset_from_notes_gathered_values(notes_laced_llll, onset) : onset, 0, WHITENULL_llll);
				//				llll_appenddouble(this_ll, peak_bins[i], 0, WHITENULL_llll);
				llll_appenddouble(this_ll, peak_amplis[i], 0, WHITENULL_llll);
				llll_appendllll(d2, this_ll, 0, WHITENULL_llll);
			}
			llll_appendllll(*debug, d2, 0, WHITENULL_llll);
		}

		for (i = 0; i < num_peaks; i++) {
			t_llll *this_peak = llll_get();
			double onset = win_size + peak_bins[i] * hop_size;
			llll_appenddouble(this_peak, snap_to_nearest_onset ? snap_to_nearest_onset_from_notes_gathered_values(notes_laced_llll, onset) : onset, 0, WHITENULL_llll);
			llll_appendlong(this_peak, 0, 0, WHITENULL_llll); // voice number
			llll_appenddouble(this_peak, 6000, 0, WHITENULL_llll); // dummy
			llll_appenddouble(this_peak, 1000, 0, WHITENULL_llll); // dummy
			llll_appendlong(this_peak, harmonic_changes_contribution * CONST_MAX_VELOCITY * peak_amplis[i], 0, WHITENULL_llll);
			llll_appendlong(this_peak, -1, 0, WHITENULL_llll); // chord idx, dummy
			llll_appendlong(this_peak, 1, 0, WHITENULL_llll); // num notes, dummy
			llll_appenddouble(this_peak, 0, 0, WHITENULL_llll); // maxima extension, dummy
			llll_appenddouble(this_peak, 0, 0, WHITENULL_llll); // minima extension, dummy
			llll_appendllll(out_trans, this_peak, 0, WHITENULL_llll);
		}
		
		if (num_peaks) {
			bach_freeptr(peak_bins);
			bach_freeptr(peak_amplis);
			bach_freeptr(peak_phases);
			bach_freeptr(peak_bin_widths);
		} 
		
		llll_free(transition_probabilities);
		llll_free(transition_onsets);
		llll_free(filtered_probabilities);
		
		bach_freeptr(fpr);
		bach_freeptr(dummy_phase);

		return out_trans;
	}
}

// note_neighborhood_to_consider: number of adjacent notes to a given one which will trigger a wave. Leave 0 to consider all notes.
// returns a debug llll
void gathered_syntax_to_onset_wave(t_llll *chords_in_gathered_syntax, 
									double *wave, long num_sampling_points, double sampling_freq, 
									double decay_time, double voice_coupling, long note_neighborhood_to_consider,
									double outer_onset_threshold, double inner_onset_threshold, double onset_decay_slope,
									double outer_mc_threshold, double inner_mc_threshold,
									char also_normalize, char use_cosine, char use_masking_detection, double non_sequential_events_multiplier,
									t_multiphase_spectrogram *mph, long num_fft_bins, double waveshaping_exponent, double harmonic_changes_contribution, 
									t_llll **debug,
									double harm_changes_winsize, double harm_changes_hopsize, char snap_detected_harmonic_changes_to_nearest_onset, 
									double harmonic_changes_median_filtering_window, double delete_softer_harmonic_changes_inside_win_ms,
									double gain_multiplier_for_maxima, double gain_multiplier_for_minima, double extend_masking_ms, char extend_masking_components_over_masked_ones,
									double debug_clip_min_bpm, double debug_clip_max_bpm){
	
	long i, j, k;

	// build multiphase spectrogram (UNUSED!!! OLD AND UNUSED!!!)
	if (mph){
		mph->num_samples = num_sampling_points;
		mph->num_bins = num_fft_bins;
		mph->bins = (t_multiphase_bin **)bach_newptr(num_sampling_points * sizeof(t_multiphase_bin *));
		for (i = 0; i < num_sampling_points; i++)
			mph->bins[i] = (t_multiphase_bin *)bach_newptr(num_fft_bins * sizeof(t_multiphase_bin));
		for (i = 0; i < num_sampling_points; i++)
			for (j = 0; j < num_fft_bins; j++)
				for (k = 0; k < CONST_MULTIPHASE_NUM_PHASE_BINS; k++) {
					mph->bins[i][j].ampli[k] = 0;
					mph->bins[i][j].phase[k] = 0;
				}
	}
									
									
	t_llll *laced_llll; //, *only_onsets;
	t_llllelem *elem;
	t_llllelem *lacedelem1, *lacedelem2;

	// 1. resetting the onset wave array
	for (i = 0; i < num_sampling_points; i++)
		wave[i] = 0;
	
	
/*	// 2. obtaining only_onsets
	only_onsets = llll_get();
	for (elem = chords_in_gathered_syntax->l_head; elem; elem = elem->l_next){
		if (hatom_gettype(&elem->l_hatom) == H_LLLL){
			t_llll *voicellll = hatom_getllll(&elem->l_hatom);
			t_llll *voice_onsets = llll_get();
			t_llllelem *chelem;
			num_voices++;
			for (chelem = voicellll->l_head; chelem; chelem = chelem->l_next){
				if (hatom_gettype(&chelem->l_hatom) == H_LLLL) {
					t_llll *chllll = hatom_getllll(&chelem->l_hatom);
					if (chllll && chllll->l_head && chllll->l_head->l_next && is_hatom_number(&chllll->l_head->l_hatom)){
						double onset = hatom_getdouble(&chllll->l_head->l_hatom);
						llll_appenddouble(voice_onsets, onset, 0, WHITENULL_llll);
					}
				}
			}
			llll_appendllll(only_onsets, voice_onsets, 0, WHITENULL_llll);
		}
	} */
	

	// 3. build an interlaced list containing (onset voice_number pitch dur vel chord_idx num notes) (onset voice_number pitch dur vel chord_idx) (onset voice_number pitch dur vel chord_idx)... for each note
	//    we also build some running medians of onset differences

	laced_llll = llll_get();
	i = 0;
	for (elem = chords_in_gathered_syntax->l_head; elem; elem = elem->l_next){
		if (hatom_gettype(&elem->l_hatom) == H_LLLL){
			t_llll *voicellll = hatom_getllll(&elem->l_hatom);
			t_llllelem *chelem;
			long chord_idx = 1;
			i++;
			for (chelem = voicellll->l_head; chelem; chelem = chelem->l_next, chord_idx++){
				if (hatom_gettype(&chelem->l_hatom) == H_LLLL) {
					t_llll *chllll = hatom_getllll(&chelem->l_hatom);
					if (chllll && chllll->l_head && chllll->l_head->l_next && is_hatom_number(&chllll->l_head->l_hatom)){
						double onset = hatom_getdouble(&chllll->l_head->l_hatom);
						t_llllelem *noteselem;
						for (noteselem = chllll->l_head->l_next; noteselem; noteselem = noteselem->l_next){
							if (hatom_gettype(&noteselem->l_hatom) == H_LLLL) {
								t_llll *thisllll = hatom_getllll(&noteselem->l_hatom);
								t_llll *notellll = llll_get();
								double mc = (thisllll->l_head && is_hatom_number(&thisllll->l_head->l_hatom) ? hatom_getdouble(&thisllll->l_head->l_hatom) : 0);
								double dur = (thisllll->l_head && thisllll->l_head->l_next && is_hatom_number(&thisllll->l_head->l_next->l_hatom) ? hatom_getdouble(&thisllll->l_head->l_next->l_hatom) : 0);
								long vel = (thisllll->l_head && thisllll->l_head->l_next && thisllll->l_head->l_next->l_next && is_hatom_number(&thisllll->l_head->l_next->l_next->l_hatom) ? hatom_getlong(&thisllll->l_head->l_next->l_next->l_hatom) : 0);
								
								llll_appenddouble(notellll, onset, 0, WHITENULL_llll);
								llll_appendlong(notellll, i, 0, WHITENULL_llll); // voice number
								llll_appenddouble(notellll, mc, 0, WHITENULL_llll);
								llll_appenddouble(notellll, dur, 0, WHITENULL_llll);
								llll_appendlong(notellll, vel, 0, WHITENULL_llll);
								llll_appendlong(notellll, chord_idx, 0, WHITENULL_llll);
//								llll_appendlong(notellll, get_num_llll_in_llll_first_level(chllll), 0, WHITENULL_llll);
								llll_appendllll(laced_llll, notellll, 0, WHITENULL_llll);
							}
						}
					}
				}
			}
		}
	}
	

	// 3. sort list by onset
	llll_inplacesort(laced_llll, (sort_fn) llll_sort_by_first);

	// 4. adding reference about number of synchronous notes to each one
	lacedelem1 = laced_llll->l_head;
	while (lacedelem1){
		t_llll *ll = lacedelem1->l_hatom.h_w.w_llll;
		t_llllelem *lastcountedelem = lacedelem1;
		double this_onset1 = hatom_getdouble(&ll->l_head->l_hatom);
		long count = 1;
		for (lacedelem2 = lacedelem1->l_next; lacedelem2; lacedelem2 = lacedelem2->l_next){
			double this_onset2 = hatom_getdouble(&lacedelem2->l_hatom.h_w.w_llll->l_head->l_hatom);
			if (this_onset2 - this_onset1 > CONST_EPSILON1) {
				break;
			} else {
				lastcountedelem = lacedelem2;
				count++;
			}
		}
		for (lacedelem2 = lacedelem1; lacedelem2; lacedelem2 = lacedelem2->l_next){
			llll_appendlong(lacedelem2->l_hatom.h_w.w_llll, count, 0, WHITENULL_llll);
			if (lacedelem2 == lastcountedelem)
				break;
		}
		lacedelem1 = lastcountedelem->l_next;
	}

	
	// 4. check for local minima and maxima
	for (lacedelem1 = laced_llll->l_head; lacedelem1; lacedelem1 = lacedelem1->l_next){
		double this_mc = hatom_getdouble(&lacedelem1->l_hatom.h_w.w_llll->l_head->l_next->l_next->l_hatom);
		double orig_onset = hatom_getdouble(&lacedelem1->l_hatom.h_w.w_llll->l_head->l_hatom), mc;
		double right_minima_ext = orig_onset;
		double left_minima_ext = orig_onset;
		double left_maxima_ext = orig_onset;
		double right_maxima_ext = orig_onset;
		t_llllelem *temp_next, *temp_prev;
		
		temp_next = lacedelem1->l_next, 
		temp_prev = lacedelem1->l_prev;
		while (temp_next && (mc = hatom_getdouble(&temp_next->l_hatom.h_w.w_llll->l_head->l_next->l_next->l_hatom)) > this_mc) {
			double this_onset = hatom_getdouble(&temp_next->l_hatom.h_w.w_llll->l_head->l_hatom);
			right_minima_ext = this_onset;
			temp_next = temp_next->l_next;
		}
		while (temp_prev && (mc = hatom_getdouble(&temp_prev->l_hatom.h_w.w_llll->l_head->l_next->l_next->l_hatom)) > this_mc) {
			double this_onset = hatom_getdouble(&temp_prev->l_hatom.h_w.w_llll->l_head->l_hatom);
			left_minima_ext = this_onset;
			temp_prev = temp_prev->l_prev;
		}
		if (left_minima_ext == orig_onset && lacedelem1->l_prev)
			right_minima_ext = orig_onset;
		if (right_minima_ext == orig_onset && lacedelem1->l_next)
			left_minima_ext = orig_onset;

		temp_next = lacedelem1->l_next, 
		temp_prev = lacedelem1->l_prev;
		while (temp_next && hatom_getdouble(&temp_next->l_hatom.h_w.w_llll->l_head->l_next->l_next->l_hatom) < this_mc) {
			right_maxima_ext = hatom_getdouble(&temp_next->l_hatom.h_w.w_llll->l_head->l_hatom);
			temp_next = temp_next->l_next;
		}
		while (temp_prev && hatom_getdouble(&temp_prev->l_hatom.h_w.w_llll->l_head->l_next->l_next->l_hatom) < this_mc) {
			left_maxima_ext = hatom_getdouble(&temp_prev->l_hatom.h_w.w_llll->l_head->l_hatom);
			temp_prev = temp_prev->l_prev;
		}
		if (left_maxima_ext == orig_onset && lacedelem1->l_prev)
			right_maxima_ext = orig_onset;
		if (right_maxima_ext == orig_onset && lacedelem1->l_next)
			left_maxima_ext = orig_onset;

		llll_appenddouble(lacedelem1->l_hatom.h_w.w_llll, right_maxima_ext - left_maxima_ext, 0, WHITENULL_llll);
		llll_appenddouble(lacedelem1->l_hatom.h_w.w_llll, right_minima_ext - left_minima_ext, 0, WHITENULL_llll);
	}


	// 4. detect harmonic changes, and put them as dummy events in the voice 0
	if (harmonic_changes_contribution > 0) {
		t_llll *harm_changes = detect_harmonic_changes(laced_llll, harm_changes_winsize, harm_changes_hopsize, harmonic_changes_contribution, 
														snap_detected_harmonic_changes_to_nearest_onset, harmonic_changes_median_filtering_window, 
														delete_softer_harmonic_changes_inside_win_ms, debug);
		llll_post(harm_changes, 0, 1, 2, NULL, NULL);
//		llll_clear(laced_llll); // ONLY FOR DEBUG: PURE HARMONIC CONTRIBUTION!
		llll_chain(laced_llll, harm_changes);
		llll_inplacesort(laced_llll, (sort_fn) llll_sort_by_first); // then sort again the list
	}


	// 5. detecting couples which are to be taken into account for onset wave creation, and choose their "couple_gain" (amplitude factor due to the velocities, distances and other factors)
	t_llll *couples = llll_get();
	for (lacedelem1 = laced_llll->l_head; lacedelem1; lacedelem1 = lacedelem1->l_next){
		long curr_num_mins = 0, curr_num_maxs = 0;
		double curr_weight_mins = 0, curr_weight_maxs = 0;
		for (lacedelem2 = lacedelem1->l_next; lacedelem2; lacedelem2 = lacedelem2->l_next){
			t_llll *llll1 = hatom_getllll(&lacedelem1->l_hatom);
			t_llll *llll2 = hatom_getllll(&lacedelem2->l_hatom);
			double onset1 = hatom_getdouble(&llll1->l_head->l_hatom);
			double onset2 = hatom_getdouble(&llll2->l_head->l_hatom);
			long voicenum1 = hatom_getlong(&llll1->l_head->l_next->l_hatom);
			long voicenum2 = hatom_getlong(&llll2->l_head->l_next->l_hatom);
			double mc1 = hatom_getdouble(&llll1->l_head->l_next->l_next->l_hatom);
			double mc2 = hatom_getdouble(&llll2->l_head->l_next->l_next->l_hatom);
//			double dur1 = hatom_getdouble(&llll1->l_head->l_next->l_next->l_next->l_hatom); // unused for now, that's ok
//			double dur2 = hatom_getdouble(&llll2->l_head->l_next->l_next->l_next->l_hatom); // unused for now, that's ok
			long vel1 = hatom_getlong(&llll1->l_head->l_next->l_next->l_next->l_next->l_hatom);
			long vel2 = hatom_getlong(&llll2->l_head->l_next->l_next->l_next->l_next->l_hatom);
			long idx1 = hatom_getlong(&llll1->l_head->l_next->l_next->l_next->l_next->l_next->l_hatom);
			long idx2 = hatom_getlong(&llll2->l_head->l_next->l_next->l_next->l_next->l_next->l_hatom);
			long num_chord_notes1 = hatom_getlong(&llll1->l_head->l_next->l_next->l_next->l_next->l_next->l_next->l_hatom);
			long num_chord_notes2 = hatom_getlong(&llll2->l_head->l_next->l_next->l_next->l_next->l_next->l_next->l_hatom);
			double maxima_ext1 = hatom_getdouble(&llll1->l_head->l_next->l_next->l_next->l_next->l_next->l_next->l_next->l_hatom);
			double maxima_ext2 = hatom_getdouble(&llll2->l_head->l_next->l_next->l_next->l_next->l_next->l_next->l_next->l_hatom);
			double minima_ext1 = hatom_getdouble(&llll1->l_head->l_next->l_next->l_next->l_next->l_next->l_next->l_next->l_next->l_hatom);
			double minima_ext2 = hatom_getdouble(&llll2->l_head->l_next->l_next->l_next->l_next->l_next->l_next->l_next->l_next->l_hatom);
			
			if (onset2 > onset1 && onset2 - onset1 < outer_onset_threshold && 
				(voicenum1 == voicenum2 || (voice_coupling > 0 && voicenum1 != 0 && voicenum2 != 0))) {	// voicenum = 0 is reserved for dummy harmonic-change-notes
				double this_delta_onset = onset2 - onset1;
				if (note_neighborhood_to_consider <= 0 || abs(idx1 - idx2) <= note_neighborhood_to_consider) {
					// retrieve amplitude of the synusoidal wave
					
					double delta_onsets = onset2 - onset1;
					double omega = TWOPI * 1000./delta_onsets;
					double phase = TWOPI * (1. - positive_fmod(onset1/delta_onsets, 1.));
					char need_to_drop_this = false;

					double couple_gain = 1.;
					double couple_importance = 1.;	// will be used to decide masking
					t_llll *thisll = llll_get();

					// change gain depending on velocities
					couple_gain *= rescale_with_slope(vel2 + vel1, 0, 2 * CONST_MAX_VELOCITY, 0., 1., 0.);
					
					// change gain depending on voices
					couple_gain *= (voicenum1 == voicenum2 ? 1. : voice_coupling);

					// changing gain because the two notes belong to two chords
//					couple_gain *= MIN(MIN(num_chord_notes1, num_chord_notes2), 3); // CHANGE THE "3" NUMBER? GAUGE

					// change gain depending on local minimum/maximum
					if (maxima_ext1 > 0 && maxima_ext2 > 0) {
//						couple_gain *= rescale(CLAMP((mc1 + mc2)/2., 3600, 8400), 3600, 8400, 1., gain_multiplier_for_maxima);
						double gain_to_use = pow(gain_multiplier_for_maxima, 1/(1 + 2 * curr_weight_maxs + pow(fabs(mc2 - mc1)/500., 2))) ; 
						couple_gain *= rescale(CLAMP((mc1 + mc2)/2., 3600, 8400), 3600, 8400, 1., gain_to_use);
						curr_num_maxs++;
						curr_weight_maxs += CLAMP(rescale(mc2, mc1, mc1 - 1200, 1., 0.), 0., 1.);
					}

					else if (minima_ext1 > 0 && minima_ext2 > 0) {
						// the gain also depends on how many minima were BEFORE this existing minima (between onset 1 and onset 2)
						// we take the average
//						double gain_to_use = pow(gain_multiplier_for_minima, 1/(1 + 2 * curr_weight_mins)) ; 
						double gain_to_use = pow(gain_multiplier_for_minima, 1/(1 + 2 * curr_weight_mins + pow(fabs(mc2 - mc1)/500., 2))) ; 
						couple_gain *= rescale(CLAMP((mc1 + mc2)/2., 3600, 8400), 3600, 8400, gain_to_use, 1.);
						curr_num_mins++;
//						curr_weight_mins += rescale(mc2, 3600, 8400, 1., 0.);
						curr_weight_mins += CLAMP(rescale(mc2, mc1, mc1 + 1200, 1., 0.), 0., 1.);
					}


					couple_importance = couple_gain;

					// change gain depending on onsets (the farther the notes are, the more we will ignore the contribution)
					if (onset2 - onset1 > inner_onset_threshold)
						couple_gain *= rescale_with_slope(CLAMP(onset2 - onset1 - inner_onset_threshold, 0, outer_onset_threshold - inner_onset_threshold), 0, outer_onset_threshold - inner_onset_threshold, 1, 0, onset_decay_slope);

					// change gain depending on non sequentiality
					if (!(idx2 == idx1 + 1 && voicenum1 == voicenum2))
						couple_gain *= non_sequential_events_multiplier;
					
					// changing importance because the two notes belong to two chords
					couple_importance *= pow(1.2, MIN(MIN(num_chord_notes1, num_chord_notes2), 3) - 1); // CHANGE THE "3" NUMBER? GAUGE

					// change importance
					if (onset2 - onset1 > outer_onset_threshold)	// we change the importance only for notes OUTSIDE the outer threshold
						couple_importance *= rescale_with_slope(onset2 - onset1 - outer_onset_threshold, 0, outer_onset_threshold - inner_onset_threshold, 1, 0, onset_decay_slope);

//					if (!(idx2 == idx1 + 1 && voicenum1 == voicenum2))
//						couple_importance *= 0.7 * rescale_with_slope(CLAMP(onset2 - onset1, 0, outer_onset_threshold), 0, outer_onset_threshold, 1, 0, 0); // CONSTANT TO GAUGE
										
					// OLD MASKING DETECTION ALGORITHM, now we do it separately later
					if (use_masking_detection && false) {
						elem = couples->l_tail;
						while (elem){
							const double THRESHOLD_MS = 40;
							t_llllelem *prev = elem->l_prev;
							t_llll *ll = hatom_getllll(&elem->l_hatom);
							double prev_onset1 = hatom_getdouble(&ll->l_head->l_next->l_hatom);
							double prev_onset2 = hatom_getdouble(&ll->l_head->l_next->l_next->l_hatom);
							double prev_delta_onset = fabs(prev_onset2 - prev_onset1);
							double prev_couple_gain = hatom_getdouble(&ll->l_head->l_next->l_next->l_next->l_next->l_next->l_hatom);
							double ratio = fabs(prev_delta_onset/this_delta_onset);
							if (prev_onset1 + this_delta_onset + THRESHOLD_MS < onset1)
								break;
							else if (((prev_onset1 < onset2 && onset2 < prev_onset2) ||
									  (onset1 < prev_onset2 && prev_onset2 < onset2)) &&
//									 fabs(this_delta_onset - prev_delta_onset) < THRESHOLD_MS) {
									 fabs(round(ratio) * this_delta_onset - ratio * this_delta_onset) < THRESHOLD_MS) {
								
								if (prev_couple_gain >= couple_gain) {
									// the existing one is masking this one
									need_to_drop_this = true;
									break;
								} else {
									llll_destroyelem(elem);
								}
							}
							elem = prev;
						}
					}
					
					if (need_to_drop_this)
						llll_free(thisll);
					else {
						llll_appenddouble(thisll, onset1, 0, WHITENULL_llll);
						llll_appenddouble(thisll, onset2, 0, WHITENULL_llll);
						llll_appenddouble(thisll, omega, 0, WHITENULL_llll);
						llll_appenddouble(thisll, phase, 0, WHITENULL_llll);
						llll_appenddouble(thisll, couple_gain, 0, WHITENULL_llll);
						llll_appendlong(thisll, voicenum1, 0, WHITENULL_llll);
						llll_appendlong(thisll, voicenum2, 0, WHITENULL_llll);
						llll_appendlong(thisll, mc1, 0, WHITENULL_llll);
						llll_appendlong(thisll, mc2, 0, WHITENULL_llll);
						llll_appenddouble(thisll, 0, 0, WHITENULL_llll);	// extend at left
						llll_appenddouble(thisll, 0, 0, WHITENULL_llll); // extend at right
						llll_appenddouble(thisll, couple_importance, 0, WHITENULL_llll);
						llll_appendllll(couples, thisll, 0, WHITENULL_llll);
					}
				}
			}
		}
	}
	// now the list couples has as elements (onset1, onset2, omega, phase, couple_gain, voice1, voice2, mc1, mc2, left_ext, right_ext, couple_importance)


	// masking detection
	if (use_masking_detection) {
		t_llllelem *elemA, *elemB, *elem_ordered_by_importance;
		long i;
		t_llll **lists_to_sort;
		t_llll *indices;
		
		dev_post("START of masking detection");

		// A couple is masking another one when they are overlapping, the period of the masked cond couple is equal or divisor of the masking couple,
		// and when these periods are out of phase. In this case, we discard the least important couple (and might eventually give a "prize" to the most important one?)

		// Since we need to have a N log(N) algorithm, I think that the only way to implement it is to run through the list ordered by couple,
		// but referring then (in order to check for overlapping couples) to the list ordered by onset (so that we can break the cycle
		// if we are too far away, thus not increasing complexity).

		// Finding maximum note duration
		double max_dur = 0;
		for (lacedelem1 = laced_llll->l_head; lacedelem1; lacedelem1 = lacedelem1->l_next){
			double dur1 = hatom_getdouble(&lacedelem1->l_hatom.h_w.w_llll->l_head->l_next->l_next->l_next->l_hatom);
			if (dur1 > max_dur)
				max_dur = dur1;
		}

		// Thus building a second list containing couple elements addresses
		indices = llll_get();
		for (elemA = couples->l_head, i = 1; elemA; elemA = elemA->l_next, i++) 
			llll_appendlong(indices, i, 0, WHITENULL_llll);

		// We sort the couples by onset
		llll_inplacesort(couples, (sort_fn) llll_sort_by_first);

		// Suppose couples are (a b c d e f g h i), ordered by onset
		// We sort couples by importance, only in order to retrieve the ordered list of addresses
		lists_to_sort = (t_llll **) bach_newptr(2 * sizeof(t_llll *));
		lists_to_sort[0] = couples;  // (a b c d e f g h i)
		lists_to_sort[1] = indices;  // (1 2 3 4 5 6 7 8 9)
		llll_multisort(lists_to_sort, lists_to_sort, 2, (sort_fn)llll_sort_by_last);
		llll_rev(lists_to_sort[0], 0, 1);
		llll_rev(lists_to_sort[1], 0, 1);
		indices = lists_to_sort[1];  // (7 2 4 1 5 6 8 3 9)
		couples = lists_to_sort[0];  // (g b d a e f h c i)
		bach_freeptr(lists_to_sort);

		// setting the l_thing of each couple element to point to the corresponding father element of the elem_address list
		// (will be used later when we need to destroy elements;
		// setting the l_things, to they point to the corresponding elements
		for (elemA = indices->l_head, elemB = couples->l_head; elemA && elemB; elemA = elemA->l_next, elemB = elemB->l_next) {
			hatom_change_to_obj(&elemA->l_hatom, elemB);
			elemB->l_thing.w_obj = elemA;
		}
		// now indices has (&g &b &d &a &e &f &h &c &i) 

		// Finally, we sort again the couples by onset
		llll_inplacesort(couples, (sort_fn) llll_sort_by_first);

		for (elem_ordered_by_importance = indices->l_head; elem_ordered_by_importance; elem_ordered_by_importance = elem_ordered_by_importance->l_next) {
			t_llllelem *elemA = (t_llllelem *)hatom_getobj(&elem_ordered_by_importance->l_hatom); // couple of events
			t_llll *A_ll = elemA->l_hatom.h_w.w_llll;
			double A_onset1 = A_ll->l_head->l_hatom.h_w.w_double;
			double A_onset2 = A_ll->l_head->l_next->l_hatom.h_w.w_double;
			double A_delta_onset = A_onset2 - A_onset1;
			long A_voice1 = A_ll->l_head->l_next->l_next->l_next->l_next->l_next->l_hatom.h_w.w_long;
			double A_couple_importance = A_ll->l_tail->l_hatom.h_w.w_double;
			
//			long debug_count = 0;
			
			if (!CONST_HARMONIC_TRANSIENT_CAN_MASK && A_voice1 == 0)
				continue;		// if it is an harmonic transient couple, it won't mask anything.
			
			elemB = elemA;
			
			// Choosing the starting element; we go backward in the list, so that we are sure that no
			// elements before elemB can be masked by elemA.
			while (elemB){
				double B_onset1 = hatom_getdouble(&elemB->l_hatom.h_w.w_llll->l_head->l_hatom);
//				debug_count++;
				if (B_onset1 + outer_onset_threshold + extend_masking_ms < A_onset1)
					break;
				if (!elemB->l_prev)
					break;
				elemB = elemB->l_prev;
			}
			
//			debug_count = 0;
			// Cycle on the elements which might possibly be masked
			while (elemB) {
				t_llllelem *elemBnext = elemB->l_next;
				t_llll *B_ll = elemB->l_hatom.h_w.w_llll;
				double B_onset1 = B_ll->l_head->l_hatom.h_w.w_double;
				double B_onset2 = B_ll->l_head->l_next->l_hatom.h_w.w_double;
				double B_couple_importance = B_ll->l_tail->l_hatom.h_w.w_double;
				long B_voice1 = B_ll->l_head->l_next->l_next->l_next->l_next->l_next->l_hatom.h_w.w_long;

//				debug_count++;
				
				if (!CONST_HARMONIC_TRANSIENT_CAN_BE_MASKED && B_voice1 == 0) { // if it is an harmonic transient couple, we leave it untouched 
					elemB = elemBnext;
					continue;
				} else if (elemB == elemA || A_couple_importance <= B_couple_importance) {
					elemB = elemBnext;
					continue;
				} else if (B_onset1 > A_onset2 + extend_masking_ms)
					 break;
				
				double superposition = MIN(B_onset2, A_onset2) - MAX(B_onset1, A_onset1);
				if (superposition > 0 - extend_masking_ms) {
					double B_delta_onset = B_onset2 - B_onset1;
					double A_B_ratio = fabs(A_delta_onset/B_delta_onset);
					long round_A_B_ratio = round(A_B_ratio);
					double B_A_ratio = fabs(B_delta_onset/A_delta_onset);
					long round_B_A_ratio = round(B_A_ratio);
					char must_drop = true;
					
					if (round_A_B_ratio > 0 && fabs(round_A_B_ratio * B_delta_onset - A_B_ratio * B_delta_onset) < round_A_B_ratio * CONST_THRESHOLD_MS_EQUAL_PERIODS_FOR_MASKING) {
						long k = round((A_onset1 - B_onset1)/B_delta_onset);
						if (fabs(B_onset1 + k * B_delta_onset - A_onset1) < round_A_B_ratio * CONST_THRESHOLD_MS_EQUAL_PERIODS_FOR_MASKING) // phases are in sync
							must_drop = false;
					}
					if (round_B_A_ratio > 0 && fabs(round_B_A_ratio * A_delta_onset - B_A_ratio * A_delta_onset) < round_B_A_ratio * CONST_THRESHOLD_MS_EQUAL_PERIODS_FOR_MASKING) {
						long k = round((A_onset1 - B_onset1)/A_delta_onset);
						if (fabs(B_onset1 + k * A_delta_onset - A_onset1) < round_B_A_ratio * CONST_THRESHOLD_MS_EQUAL_PERIODS_FOR_MASKING) // phases are in sync
							must_drop = false;
					}

					if (must_drop) {
						// dropping B couple!
						
						if (extend_masking_components_over_masked_ones) {
							// extending original
							double A_left_ext = A_ll->l_tail->l_prev->l_prev->l_hatom.h_w.w_double;
							double A_right_ext = A_ll->l_tail->l_prev->l_hatom.h_w.w_double;
							
							hatom_setdouble(&A_ll->l_tail->l_prev->l_prev->l_hatom, MAX(A_left_ext, A_onset1 - B_onset1));
							hatom_setdouble(&A_ll->l_tail->l_prev->l_hatom, MAX(A_right_ext, B_onset2 - A_onset2));
						}
						
						// verbose:
						if (60 * (1000/B_delta_onset) >= debug_clip_min_bpm && 60 * (1000/B_delta_onset) <= debug_clip_max_bpm) {
//							long A_voice2 = A_ll->l_head->l_next->l_next->l_next->l_next->l_next->l_next->l_hatom.h_w.w_long;
//							long B_voice2 = B_ll->l_head->l_next->l_next->l_next->l_next->l_next->l_next->l_hatom.h_w.w_long;
							long B_mc1 = hatom_getdouble(&B_ll->l_head->l_next->l_next->l_next->l_next->l_next->l_next->l_next->l_hatom);
							long B_mc2 = hatom_getdouble(&B_ll->l_head->l_next->l_next->l_next->l_next->l_next->l_next->l_next->l_next->l_hatom);
							long A_mc1 = hatom_getdouble(&A_ll->l_head->l_next->l_next->l_next->l_next->l_next->l_next->l_next->l_hatom);
							long A_mc2 = hatom_getdouble(&A_ll->l_head->l_next->l_next->l_next->l_next->l_next->l_next->l_next->l_next->l_hatom);
							char *B_mc1_str = NULL, *B_mc2_str = NULL;
							char *A_mc1_str = NULL, *A_mc2_str = NULL;
							ezmidicents2notename(4, B_mc1, k_NOTE_NAMES_ANGLOSAXON, true, &B_mc1_str, 2);
							ezmidicents2notename(4, B_mc2, k_NOTE_NAMES_ANGLOSAXON, true, &B_mc2_str, 2);
							ezmidicents2notename(4, A_mc1, k_NOTE_NAMES_ANGLOSAXON, true, &A_mc1_str, 2);
							ezmidicents2notename(4, A_mc2, k_NOTE_NAMES_ANGLOSAXON, true, &A_mc2_str, 2);
							//dev_post("- Dropping couple (voice %ld, onset %.0fms, %s) – (voice %ld, onset %.0fms, %s) – importance %.2f", B_voice1, B_onset1, B_mc1_str, B_voice2, B_onset2, B_mc2_str, B_couple_importance);
							//dev_post("  because it is covered by couple (voice %ld, onset %.0fms, %s) – (voice %ld, onset %.0fms, %s) – importance %.2f", A_voice1, A_onset1, A_mc1_str, A_voice2, A_onset2, A_mc2_str, A_couple_importance);
							//dev_post("  Delta onset = %.0fms ≈ %ld · %.0fms", A_delta_onset, round_B_A_ratio, B_delta_onset);
							bach_freeptr(B_mc1_str);
							bach_freeptr(B_mc2_str);
							bach_freeptr(A_mc1_str);
							bach_freeptr(A_mc2_str);
						}
						
						// destroy elemB (and possibly destroying element in the elem_addresses list!)
						if (elemB->l_thing.w_obj)
							llll_destroyelem_no_depth_check((t_llllelem *)elemB->l_thing.w_obj);
						llll_destroyelem_no_depth_check(elemB);
					}
				}
				elemB = elemBnext;
			}
//			dev_post("count: %ld", debug_count);
		}

		dev_post("END of masking detection");
		
		// removing l_thing fields
		for (elemA = couples->l_head; elemA; elemA = elemA->l_next)
			elemA->l_thing.w_obj = NULL;
		llll_free(indices);
		
		if (true) { //verbose
			dev_post("Couples left:");
			for (elemA = couples->l_head; elemA; elemA = elemA->l_next) {
				t_llll *A_ll = elemA->l_hatom.h_w.w_llll;
				double A_onset1 = hatom_getdouble(&A_ll->l_head->l_hatom);
				double A_onset2 = hatom_getdouble(&A_ll->l_head->l_next->l_hatom);
				double A_delta_onset = A_onset2 - A_onset1;
				if (60 * (1000/A_delta_onset) >= debug_clip_min_bpm && 60 * (1000/A_delta_onset) <= debug_clip_max_bpm) {
//					double A_couple_gain = hatom_getdouble(&A_ll->l_head->l_next->l_next->l_next->l_next->l_hatom);
//					double A_couple_importance = hatom_getdouble(&A_ll->l_tail->l_hatom);
//					long A_voice1 = hatom_getdouble(&A_ll->l_head->l_next->l_next->l_next->l_next->l_next->l_next->l_hatom);
//					long A_voice2 = hatom_getdouble(&A_ll->l_head->l_next->l_next->l_next->l_next->l_next->l_next->l_next->l_hatom);
					long A_mc1 = hatom_getdouble(&A_ll->l_head->l_next->l_next->l_next->l_next->l_next->l_next->l_next->l_next->l_hatom);
					long A_mc2 = hatom_getdouble(&A_ll->l_head->l_next->l_next->l_next->l_next->l_next->l_next->l_next->l_next->l_next->l_hatom);
					char *A_mc1_str = NULL, *A_mc2_str = NULL;
					ezmidicents2notename(4, A_mc1, k_NOTE_NAMES_ANGLOSAXON, true, &A_mc1_str, 2);
					ezmidicents2notename(4, A_mc2, k_NOTE_NAMES_ANGLOSAXON, true, &A_mc2_str, 2);
					//dev_post("- (voice %ld, onset %.0fms, %s) – (voice %ld, onset %.0fms, %s) – delta onset: %.0fms – importance %.2f – gain %.2f", A_voice1, A_onset1, A_mc1_str, A_voice2, A_onset2, A_mc2_str, A_delta_onset, A_couple_importance, A_couple_gain);
					bach_freeptr(A_mc1_str);
					bach_freeptr(A_mc2_str);
				}
			}
		}
	}

	// 6: consider each couples of elements and build the wave component
	for (elem = couples->l_head; elem; elem = elem->l_next){
		t_llll *ll = hatom_getllll(&elem->l_hatom);
		double onset1 = ll->l_head->l_hatom.h_w.w_double;
		double onset2 = ll->l_head->l_next->l_hatom.h_w.w_double;
		double omega = ll->l_head->l_next->l_next->l_hatom.h_w.w_double;
		double phase = ll->l_head->l_next->l_next->l_next->l_hatom.h_w.w_double;
		double couple_gain = ll->l_head->l_next->l_next->l_next->l_next->l_hatom.h_w.w_double;
		double left_ext = ll->l_tail->l_prev->l_prev->l_hatom.h_w.w_double;
		double right_ext = ll->l_tail->l_prev->l_hatom.h_w.w_double;
		long start_i = MAX(0, round((onset1 - left_ext) * sampling_freq / 1000.) - 1);
		long i;
		
		// precomputed values
		double couple_gain_div_decay_time = couple_gain/decay_time;
		double couple_gain_div_delta_onsets = couple_gain / (onset2 - onset1);
		double omega_div_1000 = omega / 1000.;
		double onset1_minus_left_ext = onset1 - left_ext;
		double onset2_minus_left_ext = onset2 - left_ext;
		double onset2_plus_right_ext = onset2 + right_ext;
		double onset2_plus_right_ext_plus_decay_time = onset2 + right_ext + decay_time;
		double _1000_div_sampling_freq = 1000 / sampling_freq;
		
		if (debug_clip_max_bpm > 0) {
			if (omega / TWOPI * 60 > debug_clip_max_bpm || omega / TWOPI * 60 < debug_clip_min_bpm)
				continue;
		}
			
		// we add to the wave the component linked to the these two notes:
		// a sine wave fading in between onset1-onset2 and then fading out between onset2 and onset2 + decay_time
		for (i = start_i; i < num_sampling_points; i++){
			// to do: only calculate the right number of points, not ALL points
			double t = _1000_div_sampling_freq * i;
			double amplitude = 0;
			
			if (t < onset1_minus_left_ext)
				continue;
			
			if (t > onset2_plus_right_ext_plus_decay_time)
				break;
			
			if (t >= onset1_minus_left_ext && t <= onset2_minus_left_ext) {
				amplitude = couple_gain_div_delta_onsets * (t - onset1_minus_left_ext); 
			} else if (t > onset2_minus_left_ext && t < onset2_plus_right_ext) {
				amplitude = couple_gain;
			} else if (t >= onset2_plus_right_ext) {
				amplitude = couple_gain - (t - onset2_plus_right_ext) * couple_gain_div_decay_time; 
			}
			
			// AGAIN: mph is UNUSED!!!
			if (mph && amplitude > 0){
				const double P = 3; // should be a parameter
				double temp = sqrt(4 * P * amplitude);
				double freq_bin = num_fft_bins * (1000 / (onset2 - onset1)) / sampling_freq;
				long j_min = floor(freq_bin - temp);
				long j_max = ceil(freq_bin + temp);
				for (j = MAX(0, j_min); j <= j_max && j < mph->num_bins; j++) {
					double this_ampli = MAX(0, amplitude - (j - freq_bin)*(j - freq_bin)/(4 * P));
					if (this_ampli > 0) {
						double phase_bin = TWOPI/CONST_MULTIPHASE_NUM_PHASE_BINS;
						double this_phase = positive_fmod(omega * t/1000. + phase, TWOPI);
						long this_phase_bin = floor(positive_fmod(this_phase + phase_bin/2, TWOPI)/phase_bin);
						if (this_phase_bin < CONST_MULTIPHASE_NUM_PHASE_BINS) {
							mph->bins[i][j].ampli[this_phase_bin] += this_ampli;
							mph->bins[i][j].phase[this_phase_bin] += this_ampli * (positive_fmod(this_phase + phase_bin/2, TWOPI) - phase_bin/2);	// we'll divide by the whole this_ampli sum later
						}
					}
				}
			}
			
			if (use_cosine)
				wave[i] += amplitude * cos(omega_div_1000 * t + phase);
			else
				wave[i] += amplitude * sin(omega_div_1000 * t + phase);
		}
	}
	
	if (waveshaping_exponent != 1)
		for (i = 0; i < num_sampling_points; i++)
			wave[i] = fsign(wave[i])*pow(fabs(wave[i]), waveshaping_exponent);

	if (also_normalize)
		normalize(num_sampling_points, wave, 1.);


	if (mph) {
		// dividing all phases by the ampli 
		for (i = 0; i < num_sampling_points; i++)
			for (j = 0; j < num_fft_bins; j++)
				for (k = 0; k < CONST_MULTIPHASE_NUM_PHASE_BINS; k++) 
					mph->bins[i][j].phase[k] /= mph->bins[i][j].ampli[k];
	}

	llll_free(laced_llll);
	llll_free(couples);
}



// bins data syntax must be: ((num pos ampli phase) (num pos ampli phase)...) one sublist for each bin
// where pos is usually the Hz starting position for the bin. 
// returns: ((peak_bpm peak_phase ampli width) (peak_bpm peak_phase ampli width) (peak_bpm peak_phase ampli width)...)
// if amps_only is non-zero, peak_phase is dropped; if return_bpm is true it assumes that the incoming data is a FFT data, and multiplies the 
// frequency peaks as output by 60 to get the BPMs.  
t_llll *get_peaks(t_llll *spectral_data, char amps_only, char return_bpm,
					long numpeaks, double minpeakamp, double minpeakrelamp, double sampling_frequency, long num_sampling_vals){
	t_llllelem *frame;
	long i;

	t_llll *out = llll_get();	

	for (frame = spectral_data->l_head; frame; frame = frame->l_next) {
		t_llll *fr = hatom_getllll(&frame->l_hatom);
		long num_bins = fr->l_size;
		t_llllelem *el;
		t_llll *frame_peaks = llll_get();
		double *sampling_vals = (double *) bach_newptr(num_bins * sizeof(double));
		double *sampling_phase = (double *) bach_newptr(num_bins * sizeof(double));
		
		for (el = fr->l_head, i = 0; el && i < num_bins; el = el->l_next, i++) {
			sampling_vals[i] = hatom_getdouble(&el->l_hatom.h_w.w_llll->l_head->l_next->l_next->l_hatom);
			sampling_phase[i] = amps_only ? 0 : hatom_getdouble(&el->l_hatom.h_w.w_llll->l_head->l_next->l_next->l_next->l_hatom) * PI/180.;
		}
		
		double *peak_bins = NULL, *peak_amplis = NULL, *peak_phases = NULL;
		long *peak_bin_widths = NULL, num_found_peaks = 0, i;
		find_peaks_for_frame(num_bins, sampling_vals, sampling_phase, numpeaks, minpeakamp, minpeakrelamp, 
								&num_found_peaks, &peak_bins, &peak_amplis, &peak_phases, &peak_bin_widths, true);
		
		for (i = 0; i < num_found_peaks; i++){
			// building output llll: (peak_bpm peak_phase ampli width)
			t_llll *thispeak = llll_get();
			llll_appenddouble(thispeak, (return_bpm ? 60. : 1.) * peak_bins[i] * sampling_frequency/num_sampling_vals, 0, WHITENULL_llll); // bpm
			if (!amps_only)
				llll_appenddouble(thispeak, rad2deg(peak_phases[i]), 0, WHITENULL_llll); // phase (in degrees)
			llll_appenddouble(thispeak, peak_amplis[i], 0, WHITENULL_llll); // ampli
			llll_appendlong(thispeak, peak_bin_widths[i], 0, WHITENULL_llll); // bin width
			llll_appendllll(frame_peaks, thispeak, 0, WHITENULL_llll);
		}
		
		llll_appendllll(out, frame_peaks, 0, WHITENULL_llll);
		
		if (peak_bins)
			bach_freeptr(peak_bins);
		if (peak_amplis)
			bach_freeptr(peak_amplis);
		if (peak_phases)
			bach_freeptr(peak_phases);
		if (peak_bin_widths)
			bach_freeptr(peak_bin_widths);
		bach_freeptr(sampling_vals);
		bach_freeptr(sampling_phase);
	}
	return out;
}



long get_ptrack_voice_start_frame(t_ptrack_voice *pvoice)
{
	return pvoice->first_peak ? pvoice->first_peak->frame_number : -1;
}

long get_ptrack_voice_end_frame(t_ptrack_voice *pvoice)
{
	return pvoice->last_peak ? pvoice->last_peak->frame_number : -1;
}

long get_ptrack_voice_frame_duration(t_ptrack_voice *pvoice)
{
	return get_ptrack_voice_end_frame(pvoice) - get_ptrack_voice_start_frame(pvoice);
}

void free_ptrack_voice(t_ptrack_voice *pvoice){
	bach_freeptr(pvoice);
}

t_ptrack_voice *build_ptrack_voice(long ID){
	t_ptrack_voice *pvoice = (t_ptrack_voice *)bach_newptr(sizeof(t_ptrack_voice));
	pvoice->first_peak = pvoice->last_peak = NULL;
	pvoice->ID = ID;
	pvoice->is_active = false;
	return pvoice;
}

void delete_peak_from_ptrack_voice(t_spectral_peak *peak){
	t_spectral_peak *nx = peak->ptrack_next, *pr = peak->ptrack_prev;
	if (nx && pr) {
		nx->ptrack_prev = pr;
		pr->ptrack_next = nx;
	} else if (nx) {
		nx->ptrack_prev = NULL;
		peak->ptrack_parent->first_peak = nx;
	} else if (pr) {
		pr->ptrack_next = NULL;
		peak->ptrack_parent->last_peak = pr;
	} else {
		peak->ptrack_parent->last_peak = peak->ptrack_parent->first_peak = NULL;
	}
	peak->ptrack_parent = NULL;
}

void append_peak_to_tsd_frame(t_tsd_frame *frame, t_spectral_peak *peak){
	if (frame->last_peak) {
		frame->last_peak->tsdetect_next = peak;
	} else {
		frame->first_peak = peak;
	}
	frame->last_peak = peak;
	peak->tsdetect_prev = frame->last_peak;
	peak->tsdetect_parent = frame;
	frame->num_peaks++;
}


void append_tsd_config_to_tsd_frame(t_tsd_config *tsc, t_tsd_frame *frame){
	if (!frame->first_tsd_config) {
		frame->first_tsd_config = frame->last_tsd_config = tsc;
		tsc->next = tsc->prev = NULL;
	} else {
		frame->last_tsd_config->next = tsc;
		tsc->prev = frame->last_tsd_config;
		tsc->next = NULL;
		frame->last_tsd_config = tsc;
	}
	tsc->parent = frame;
	frame->num_tsd_configs++;
}


void append_peak_to_ptrack_voice(t_ptrack_voice *pvoice, t_spectral_peak *peak){
	if (pvoice->last_peak) {
		pvoice->last_peak->ptrack_next = peak;
	} else {
		pvoice->first_peak = peak;
	}
	peak->ptrack_prev = pvoice->last_peak;
	pvoice->last_peak = peak;
	peak->ptrack_parent = pvoice;
	pvoice->num_peaks++;
}

t_ptrack_voice *build_and_append_ptvoice(t_ptrack_voice **first_ptvoice, t_ptrack_voice **last_ptvoice){
	t_ptrack_voice *ptvoice = (t_ptrack_voice *)bach_newptr(sizeof(t_ptrack_voice));
	if (*last_ptvoice) {
		ptvoice->ID = (*last_ptvoice)->ID + 1;
		(*last_ptvoice)->next = ptvoice;
		ptvoice->prev = *last_ptvoice;
	} else {
		ptvoice->ID = 1;
		*first_ptvoice = ptvoice;
		ptvoice->prev = NULL;
	}
	ptvoice->next = NULL;
	*last_ptvoice = ptvoice;
	ptvoice->is_active = false;
	ptvoice->num_peaks = 0;
	ptvoice->first_peak = ptvoice->last_peak = NULL;
	return ptvoice;
}

void delete_ptvoice(t_ptrack_voice *voice, t_ptrack_voice **first_ptvoice, t_ptrack_voice **last_ptvoice){
	t_ptrack_voice *temp;
	for (temp = voice->next; temp; temp = temp->next)
		temp->ID--;
		
	if (voice == *last_ptvoice && voice == *first_ptvoice) {
		*first_ptvoice = *last_ptvoice = NULL;
	} else if (voice == *last_ptvoice) {
		*last_ptvoice = voice->prev;
		voice->prev->next = NULL;
	} else if (voice == *first_ptvoice) {
		*first_ptvoice = voice->next;
		voice->next->prev = NULL;
	} else {
		voice->prev->next = voice->next;
		voice->next->prev = voice->prev;
	}
	bach_freeptr(voice);
}

double freq_ratio(double freq1, double freq2){
	return (freq1 > freq2 ? freq1/freq2 : freq2/freq1);
}

double phase_dist(double phase1, double phase2, double modulo)
{
	return angle_dist(phase1, phase2, modulo);
}

double phase_error(double phase1, double phase2, double freq1, double freq2, double distance_ms, double modulo){
	double phase2_ideal = phase1 + ((freq1 + freq2)/2.) * modulo * distance_ms/1000.;
	return phase_dist(phase2_ideal, phase2, modulo);
}


// num_peaks is sized num_frames;
// peaks is sized num_frames; each peaks[i] is sized num_peaks[i];
// fills num_ptrack_voices and ptrack_voices with the array of voices
// locut freq is in Hz
void partial_tracking(long num_frames, long *num_peaks, t_spectral_peak ***peaks, double frame_hop_ms,
						long max_num_ptrack_voices, double min_amp_for_a_voice_to_start, double min_amp_for_a_voice_to_continue, char min_amps_are_relative,
						double max_freq_ratio_for_a_voice_to_continue, double max_phase_error_for_a_voice_to_continue,
						double attack_time, double release_time, double lowcut_freq, long *num_ptrack_voices, t_ptrack_voice **first_pt_voice, t_ptrack_voice **last_pt_voice){
						
	long i, j, curr_num_ptrack_voices = 0;
	
	t_ptrack_voice *ptvoice;
	t_ptrack_voice *first_ptvoice = NULL, *last_ptvoice = NULL;
		
	double max_peak_amplitude = 0;	
	
	// setting all peaks as NOT done (= not handled yet)
	for (i = 0; i < num_frames; i++)
		for (j = 0; j < num_peaks[i]; j++) {
			peaks[i][j]->done = k_PARTIAL_TRACKING_VOICE_NO;
			if (peaks[i][j]->amplitude > max_peak_amplitude)
				max_peak_amplitude = peaks[i][j]->amplitude;
		}

	// we modify threshold accounting for "min_amps_are_relative" possibility
	if (min_amps_are_relative) {
		min_amp_for_a_voice_to_start *= max_peak_amplitude;
		min_amp_for_a_voice_to_continue *= max_peak_amplitude;
	}
	

	for (i = 0; i < num_frames; i++){
		
		// checking if some existing voice can be continued
		for (ptvoice = first_ptvoice; ptvoice; ptvoice = ptvoice->next) {
			if (ptvoice->is_active) {
				long min_peak_ratio_ID = -1;
				double min_peak_ratio = -1;
				
				// checking which is the nearest peak to the ending point of the voice
				for (j = 0; j < num_peaks[i]; j++){
					if (!peaks[i][j]->done && peaks[i][j]->amplitude >= min_amp_for_a_voice_to_continue){
						double f_ratio = freq_ratio(peaks[i][j]->freq, ptvoice->last_peak->freq);
						if (min_peak_ratio < 0 || f_ratio < min_peak_ratio){
							min_peak_ratio = f_ratio;
							min_peak_ratio_ID = j;
						}
					}
				}
				
				if (min_peak_ratio_ID >= 0){
					if (min_peak_ratio < max_freq_ratio_for_a_voice_to_continue &&
						phase_error(ptvoice->last_peak->phase, peaks[i][min_peak_ratio_ID]->phase, ptvoice->last_peak->freq, peaks[i][min_peak_ratio_ID]->freq, 
							peaks[i][min_peak_ratio_ID]->frame_ms - ptvoice->last_peak->frame_ms, TWOPI) < max_phase_error_for_a_voice_to_continue){

						// prevent voice crossing!
						char has_crossed = false;
						t_ptrack_voice *tmp_ptvoice;
						for (tmp_ptvoice = first_ptvoice; tmp_ptvoice; tmp_ptvoice = tmp_ptvoice->next) {
							if (tmp_ptvoice->is_active && tmp_ptvoice->last_peak->frame_number == i) {
								if (tmp_ptvoice->last_peak->ptrack_prev && ptvoice->last_peak &&
									((tmp_ptvoice->last_peak->freq > peaks[i][min_peak_ratio_ID]->freq &&
									  tmp_ptvoice->last_peak->ptrack_prev->freq < ptvoice->last_peak->freq) || 
									 (tmp_ptvoice->last_peak->freq < peaks[i][min_peak_ratio_ID]->freq &&
									  tmp_ptvoice->last_peak->ptrack_prev->freq > ptvoice->last_peak->freq))) {
										 has_crossed = true;
										 break;
									 }
							}
						}

						if (!has_crossed) {
							append_peak_to_ptrack_voice(ptvoice, peaks[i][min_peak_ratio_ID]);
							peaks[i][min_peak_ratio_ID]->done = k_PARTIAL_TRACKING_VOICE_STARTS; // WATCH OUT!!!
						}
					}
				}
			}
		}
		
		// checking if new voices can be started
		for (j = 0; j < num_peaks[i]; j++){
			long num_active_voices = 0;
			for (ptvoice = first_ptvoice; ptvoice; ptvoice = ptvoice->next) 
				if (ptvoice->is_active)
					num_active_voices++;
			
			if (!peaks[i][j]->done && peaks[i][j]->amplitude >= min_amp_for_a_voice_to_start && peaks[i][j]->freq >= lowcut_freq && num_active_voices < max_num_ptrack_voices){
				// start a voice
				t_ptrack_voice *new_ptvoice = build_and_append_ptvoice(&first_ptvoice, &last_ptvoice);
				new_ptvoice->is_active = true;
				append_peak_to_ptrack_voice(new_ptvoice, peaks[i][j]);
				peaks[i][j]->done = k_PARTIAL_TRACKING_VOICE_STARTS; // WATCH OUT!!!
				curr_num_ptrack_voices++;
			}
		}

		// checking if some voices have become unactive
		for (ptvoice = first_ptvoice; ptvoice; ptvoice = ptvoice->next) {
			if (ptvoice->last_peak && (i - ptvoice->last_peak->frame_number) * frame_hop_ms >= release_time)
				ptvoice->is_active = false;
		}
	}
	
	// checking attacks (deleting voices whose length is < attack time)
	ptvoice = first_ptvoice;
	while (ptvoice) {
		t_ptrack_voice *next = ptvoice->next;
		if (!ptvoice->first_peak || ptvoice->last_peak->frame_ms - ptvoice->first_peak->frame_ms < attack_time) {
			delete_ptvoice(ptvoice, &first_ptvoice, &last_ptvoice);
			curr_num_ptrack_voices--;
		}
		ptvoice = next;
	}
	
	*num_ptrack_voices = curr_num_ptrack_voices;
	*first_pt_voice = first_ptvoice;
	*last_pt_voice = last_ptvoice;
}



// autocorrelation function
void bach_acf(int nfft, kiss_fft_cfg cfg, kiss_fft_cfg icfg, const kiss_fft_cpx *fin, kiss_fft_cpx *fout)
{
	kiss_fft_cpx *temp1 = (kiss_fft_cpx *) bach_newptr(nfft * sizeof(kiss_fft_cpx));
	kiss_fft_cpx *temp2 = (kiss_fft_cpx *) bach_newptr(nfft * sizeof(kiss_fft_cpx));
	long i;
	
	// See http://en.wikipedia.org/wiki/Autocorrelation#Efficient_computation
	
 
    kiss_fft(cfg, fin, temp1);
	for (i = 0; i < nfft; i++) {
		temp1[i].r /= nfft;
		temp1[i].i /= nfft;
	}

	for (i = 0; i < nfft; i++)
		temp2[i] = cpx_product(temp1[i], cpx_conjugate(temp1[i]));
		
    kiss_fft(icfg, temp2, fout);
	for (i = 0; i < nfft; i++) {
		fout[i].r /= nfft;
		fout[i].i /= nfft;
	}
	bach_freeptr(temp1);
	bach_freeptr(temp2);
}


double get_averaged_phase_at_frame(t_ptrack_voice *ptv, long frame_num, double frame_hop_size)
{
	t_spectral_peak *peak;
	
	if (frame_num < ptv->first_peak->frame_number)
		return positive_fmod(ptv->first_peak->phase - TWOPI * ptv->first_peak->freq * frame_hop_size * (ptv->first_peak->frame_number - frame_num), TWOPI);

	if (frame_num > ptv->last_peak->frame_number)
		return positive_fmod(ptv->last_peak->phase + TWOPI * ptv->last_peak->freq * frame_hop_size * (frame_num - ptv->last_peak->frame_number), TWOPI);

	for (peak = ptv->first_peak; peak; peak = peak->ptrack_next){
		if (peak->frame_number == frame_num)
			return peak->phase;
		else if (peak->frame_number > frame_num) {
			double interp_freq = (peak->freq * (peak->frame_number - frame_num) + peak->ptrack_prev->freq * (frame_num - peak->ptrack_prev->frame_number))/(peak->frame_number - peak->ptrack_prev->frame_number);
			if (peak->ptrack_prev && frame_num - peak->ptrack_prev->frame_number < peak->frame_number - frame_num)
				return positive_fmod(peak->ptrack_prev->phase + TWOPI * frame_hop_size * (frame_num - peak->ptrack_prev->frame_number) / interp_freq, TWOPI);
			else
				return positive_fmod(peak->phase - TWOPI * frame_hop_size * (peak->frame_number - frame_num) / interp_freq, TWOPI);
		}
	}
	
	return 0;
}

double get_averaged_freq_at_frame(t_ptrack_voice *ptv, long frame_num, double frame_hop_size)
{
	t_spectral_peak *peak;
	
	if (frame_num < ptv->first_peak->frame_number)
		return ptv->first_peak->freq;

	if (frame_num > ptv->last_peak->frame_number)
		return ptv->last_peak->freq;

	for (peak = ptv->first_peak; peak; peak = peak->ptrack_next){
		if (peak->frame_number == frame_num)
			return peak->freq;
		else if (peak->frame_number > frame_num) {
			return (peak->freq * (peak->frame_number - frame_num) + peak->ptrack_prev->freq * (frame_num - peak->ptrack_prev->frame_number))/(peak->frame_number - peak->ptrack_prev->frame_number);
		}
	}
	
	return ptv->first_peak ? ptv->first_peak->freq : 0;
}

void get_ptrack_voice_average_frequence_and_ampli(t_ptrack_voice *ptv, double *freq, double *amp) 
{
	t_spectral_peak *peak;
	double freq_sum = 0;
	double ampli_sum = 0;
	for (peak = ptv->first_peak; peak; peak = peak->ptrack_next) {
		freq_sum += peak->amplitude * peak->freq;
		ampli_sum += peak->amplitude;
	}
	if (freq)
		*freq = freq_sum/ampli_sum;
	if (amp)
		*amp = ampli_sum/ptv->num_peaks;
}

void get_ptrack_voice_average_frequence_and_ampli_in_frame_range(t_ptrack_voice *ptv, double *freq, double *amp, long start_frame, long end_frame) 
{
	t_spectral_peak *peak;
	double freq_sum = 0;
	double ampli_sum = 0;
	for (peak = ptv->first_peak; peak; peak = peak->ptrack_next) {
		if (peak->frame_number >= start_frame && peak->frame_number <= end_frame) {
			freq_sum += peak->amplitude * peak->freq;
			ampli_sum += peak->amplitude;
		}
	}
	if (freq)
		*freq = freq_sum/ampli_sum;
	if (amp)
		*amp = ampli_sum/ptv->num_peaks;
}

void get_ptrack_voices_superposition_range(t_ptrack_voice *pt1, t_ptrack_voice *pt2, t_ptrack_voice *pt3, long *start_frame, long *end_frame) 
{
	long s1 = pt1->first_peak->frame_number;
	long s2 = pt2->first_peak->frame_number;
	long s3 = pt3->first_peak->frame_number;
	long e1 = pt1->last_peak->frame_number;
	long e2 = pt2->last_peak->frame_number;
	long e3 = pt3->last_peak->frame_number;
	long max_s = MAX(s1, MAX(s2, s3)); 
	long min_e = MIN(e1, MIN(e2, e3));
	if (max_s > min_e) 
		*start_frame = *end_frame = -1;
	else {
		*start_frame = max_s;
		*end_frame = min_e;
	}
}

// merge the configuration "giver" to the configuration "adopter"
void merge_configs(t_tsd_config *adopter, t_tsd_config *giver)
{
	
}


/*
void test_kiss_fft()
{
	kiss_fft_cfg cfg = kiss_fft_alloc(16, false, NULL, NULL);
	kiss_fft_cfg icfg = kiss_fft_alloc(16, true, NULL, NULL);
	kiss_fft_cpx cx_in[16];
	kiss_fft_cpx cx_out[16];
	kiss_fft_cpx cx_in2[16];
	long i;
	
	srand(time(NULL));
	for (i = 0; i < 16; i++) {
		cx_in[i].r = (rand() % 100)/100.;
		cx_in[i].i = (rand() % 100)/100.;
	}
	
	kiss_fft(cfg, cx_in, cx_out);
	kiss_fft(icfg, cx_out, cx_in2);
	
	for (i = 0; i < 16; i++){
		cx_in2[i].r /= 16.;
		cx_in2[i].i /= 16.;
	}
	
	kiss_fft_scalar dist = cpx_euclidean_dist(16, cx_in, cx_in2);
	post("dist: %.2f", dist);
	
	free(cfg);
} */


