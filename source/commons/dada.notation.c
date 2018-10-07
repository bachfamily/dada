/**
	@file
	dada.notation.c
	Common notation utilities for dada library

	by Daniele Ghisi
*/

#include "dada.notation.h"							// standard Max include, always required
#include "dada.windows.h"

// gs always stands for gathered syntax

// dada_gs_modif_fn must return non-zero ONLY if element must be destroyed 
void dada_roll_iterate_on_notes(t_llll *gs, dada_gs_modif_fn modif_fn, e_notation_objects notation_obj, void *arg1, void *arg2, void *arg3)
{
	t_llllelem *voice, *chord, *note, *next_chord, *next_note;
	for (voice = get_first_nonheader_elem(gs); voice; voice = voice->l_next) {
		if (hatom_gettype(&voice->l_hatom) != H_LLLL)
			continue;
		for (chord = hatom_getllll(&voice->l_hatom)->l_head; chord; chord = next_chord) {
			next_chord = chord->l_next;
			if (hatom_gettype(&chord->l_hatom) != H_LLLL)
				continue;
			long idx = 0;
            t_llll *chord_ll = hatom_getllll(&chord->l_hatom);
            double onset = chord_ll->l_head && is_hatom_number(&chord_ll->l_head->l_hatom) ? hatom_getdouble(&chord_ll->l_head->l_hatom) : 0.;
			for (note = chord_ll->l_head; note; note = next_note) {
				next_note = note->l_next;
				if (hatom_gettype(&note->l_hatom) != H_LLLL)
					continue;
				if (modif_fn(hatom_getllll(&note->l_hatom), notation_obj, &idx, &onset, arg1, arg2, arg3))
					llll_destroyelem(note);
				idx++;
			}
			if (!hatom_getllll(&chord->l_hatom)->l_head)
				llll_destroyelem(chord);
		}
	}
}

void dada_roll_iterate_on_chords(t_llll *gs, dada_gs_modif_fn modif_fn, e_notation_objects notation_obj, void *arg1, void *arg2, void *arg3)
{
	t_llllelem *voice, *chord, *next_chord;
	for (voice = get_first_nonheader_elem(gs); voice; voice = voice->l_next) {
		if (hatom_gettype(&voice->l_hatom) != H_LLLL)
			continue;
		long idx = 0;
		for (chord = hatom_getllll(&voice->l_hatom)->l_head; chord; chord = next_chord) {
			next_chord = chord->l_next;
			if (hatom_gettype(&chord->l_hatom) != H_LLLL)
				continue;
            t_llll *chord_ll = hatom_getllll(&chord->l_hatom);
            double onset = chord_ll->l_head && is_hatom_number(&chord_ll->l_head->l_hatom) ? hatom_getdouble(&chord_ll->l_head->l_hatom) : 0.;
			if (modif_fn(chord_ll, notation_obj, &idx, &onset, arg1, arg2, arg3))
				llll_destroyelem(chord);
			idx++;
		}
	}
}



void dada_iterate_on_markers(t_llll *gs, dada_gs_modif_fn modif_fn, e_notation_objects notation_obj, void *arg1, void *arg2, void *arg3)
{
	t_llll *ll = NULL;
	t_llllelem *elem = gs->l_head;
	
	while (elem && hatom_gettype(&elem->l_hatom) == H_SYM) 
		elem = elem->l_next;
	
	while (elem && hatom_gettype(&elem->l_hatom) == H_LLLL && (ll = hatom_getllll(&elem->l_hatom)) && ll->l_head && hatom_gettype(&ll->l_head->l_hatom) == H_SYM){
		if (hatom_getsym(&ll->l_head->l_hatom) == _llllobj_sym_markers) {
			t_llllelem *mkel, *nextmkel;
			long idx = 0;
//            llll_print(ll);
			for (mkel = ll->l_head->l_next; mkel; mkel = nextmkel) {
				nextmkel = mkel->l_next;
				if (hatom_gettype(&mkel->l_hatom) != H_LLLL)
					continue;
                t_llll *marker_ll = hatom_getllll(&mkel->l_hatom);
                double onset = marker_ll->l_head && is_hatom_number(&marker_ll->l_head->l_hatom) ? hatom_getdouble(&marker_ll->l_head->l_hatom) : 0.;
				if (modif_fn(hatom_getllll(&mkel->l_hatom), notation_obj, &idx, &onset, arg1, arg2, arg3))
					llll_destroyelem(mkel);
				idx++;
			}
		}
		elem = elem->l_next;
	}
}


t_llll *dada_sliceheader(t_llll *gs)
{
    // returns the header, sliced from the incoming gs
    t_llll *out = NULL;
    t_llllelem *nhel = get_first_nonheader_elem(gs);
    if (!nhel) {
        out = llll_clone(gs);
        llll_clear(gs);
    } else {
        t_llllelem *elem, *nextelem = NULL;
        out = llll_get();
        for (elem = gs->l_head; elem && elem != nhel; elem = elem->l_next)
            llll_appendhatom_clone(out, &elem->l_hatom);
        for (elem = gs->l_head; elem && elem != nhel; elem = nextelem) {
            nextelem = elem->l_next;
            llll_destroyelem(elem);
        }
    }
    
    return out;
}

// gs = gathered syntax
t_llll *dada_get_markers(t_llll *gs)
{
	t_llll *header = get_header(gs, false);
	t_llll *markers = NULL;
	t_llllelem *elem;
	for (elem = header->l_head; elem; elem = elem->l_next) {
		if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
			t_llll *ll = hatom_getllll(&elem->l_hatom);
			if (ll && ll->l_head && hatom_gettype(&ll->l_head->l_hatom) == H_SYM && hatom_getsym(&ll->l_head->l_hatom) == _llllobj_sym_markers) {
				markers = llll_clone(ll);
				llll_behead(markers);
				break;
			}
		}
	}
	llll_free(header);
    return markers ? markers : llll_get();
}


void dada_markers_delete_tempo_markers(t_llll *gs)
{
    if (!gs)
        return;
    t_llllelem *elem, *nextelem = NULL;
    for (elem = gs->l_head; elem; elem = nextelem) {
        nextelem = elem->l_next;
        if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
            t_llll *marker = hatom_getllll(&elem->l_hatom);
            if (marker && marker->l_size >= 4 && hatom_gettype(&marker->l_head->l_next->l_next->l_hatom) == H_SYM && hatom_getsym(&marker->l_head->l_next->l_next->l_hatom) == _llllobj_sym_tempo && hatom_gettype(&marker->l_head->l_next->l_next->l_next->l_hatom) == H_LLLL)  {
                llll_destroyelem(elem);
            }
        }
    }
}


double dada_get_first_marker_division_or_barline(t_llll *gs, char *is_division)
{
    t_llll *markers = dada_get_markers(gs);
    t_llllelem *elem;
    double res = 0;
    if (markers) {
        for (elem = markers->l_head; elem; elem = elem->l_next) {
            if (hatom_gettype(&elem->l_hatom) != H_LLLL)
                continue;
            t_llll *this_mk = hatom_getllll(&elem->l_hatom);
            if (this_mk->l_size >= 4 && hatom_gettype(&this_mk->l_head->l_next->l_next->l_hatom) == H_SYM && (hatom_getsym(&this_mk->l_head->l_next->l_next->l_hatom) == _llllobj_sym_division || hatom_getsym(&this_mk->l_head->l_next->l_next->l_hatom) == _llllobj_sym_barline))  {
                res = hatom_getdouble(&this_mk->l_head->l_hatom);
                if (is_division) {
                    if (hatom_getsym(&this_mk->l_head->l_next->l_next->l_hatom) == _llllobj_sym_barline)
                        *is_division = 0;
                    else
                        *is_division = 1;
                    break;
                }
            }
        }
        llll_free(markers);
    }
    return res;
}

t_tempo *dada_get_first_marker_tempo(t_llll *gs)
{
	t_llll *markers = dada_get_markers(gs);
	t_llllelem *elem;
	t_tempo *tp = NULL;
	if (markers) {
		for (elem = markers->l_head; elem; elem = elem->l_next) {
			if (hatom_gettype(&elem->l_hatom) != H_LLLL)
				continue;
			t_llll *this_mk = hatom_getllll(&elem->l_hatom);
			if (this_mk->l_size >= 4 && hatom_gettype(&this_mk->l_head->l_next->l_next->l_hatom) == H_SYM && hatom_getsym(&this_mk->l_head->l_next->l_next->l_hatom) == _llllobj_sym_tempo && hatom_gettype(&this_mk->l_head->l_next->l_next->l_next->l_hatom) == H_LLLL)  {
				tp = build_tempo_from_llll(hatom_getllll(&this_mk->l_head->l_next->l_next->l_next->l_hatom), DADA_DEFAULT_TEMPO_DIGITS);
				break;
			}
		}
		llll_free(markers);
	}
	return tp;
}


long dada_note_transpose_fn(t_llll *gs, e_notation_objects notation_obj, void *idx, void *onset, void *delta_mc, void *dummy2, void *dummy3)
{
	if (gs->l_head && is_hatom_number(&gs->l_head->l_hatom)) {
		double new_pitch = hatom_getdouble(&gs->l_head->l_hatom) + (*(double *)delta_mc);
		hatom_setdouble(&gs->l_head->l_hatom, new_pitch);
		return 0;
	}
	return 1;
}

long dada_note_transposencrop_fn(t_llll *gs, e_notation_objects notation_obj, void *idx, void *onset, void *delta_mc, void *crop_min_pitch, void *crop_max_pitch)
{
	if (gs->l_head && is_hatom_number(&gs->l_head->l_hatom)) {
		double new_pitch = hatom_getdouble(&gs->l_head->l_hatom) + (*(double *)delta_mc);
		if (new_pitch > *(double *)crop_max_pitch || new_pitch < *(double *)crop_min_pitch)
			return 1;
		else {
			hatom_setdouble(&gs->l_head->l_hatom, new_pitch);
			return 0;
		}
	}
	return 1;
}


void dada_roll_transposencrop(t_llll *gs, double delta_mc, double crop_min_pitch, double crop_max_pitch)
{
	dada_roll_iterate_on_notes(gs, dada_note_transposencrop_fn, k_NOTATION_OBJECT_ROLL, &delta_mc, &crop_min_pitch, &crop_max_pitch);
}

void dada_roll_transpose(t_llll *gs, double delta_mc)
{
	dada_roll_iterate_on_notes(gs, dada_note_transpose_fn, k_NOTATION_OBJECT_ROLL, &delta_mc, NULL, NULL);
}



long dada_invert_note_fn(t_llll *gs, e_notation_objects notation_obj, void *idx, void *onset, void *pitch_for_mirroring_mc, void *dummy2, void *dummy3)
{
	if (gs->l_head && is_hatom_number(&gs->l_head->l_hatom)) {
		hatom_setdouble(&gs->l_head->l_hatom, 2 * (*(double *)pitch_for_mirroring_mc) - hatom_getdouble(&gs->l_head->l_hatom));
		return 0;
	}
	return 1;
}

void dada_roll_invert(t_llll *gs, double pitch_for_mirroring_mc)
{
	dada_roll_iterate_on_notes(gs, dada_invert_note_fn, k_NOTATION_OBJECT_ROLL, &pitch_for_mirroring_mc, NULL, NULL);
	dada_roll_sort_notes(gs);
}


long dada_del_note_if_below_thresh_fn(t_llll *gs, e_notation_objects notation_obj, void *idx, void *onset, void *limit_mc, void *dummy2, void *dummy3)
{
	if (gs->l_head && is_hatom_number(&gs->l_head->l_hatom)) {
		double mc = hatom_getdouble(&gs->l_head->l_hatom);
		if (mc < *((double *)limit_mc))
			return 1;
		return 0;
	}
	return 1;
}


long dada_del_note_if_above_thresh_fn(t_llll *gs, e_notation_objects notation_obj, void *idx, void *onset, void *limit_mc, void *dummy2, void *dummy3)
{
	if (gs->l_head && is_hatom_number(&gs->l_head->l_hatom)) {
		double mc = hatom_getdouble(&gs->l_head->l_hatom);
		if (mc > *((double *)limit_mc))
			return 1;
		return 0;
	}
	return 1;
}


void dada_roll_crop_pitch(t_llll *gs, double limit_mc, char crop_direction)
{
	dada_roll_iterate_on_notes(gs, crop_direction ? dada_del_note_if_above_thresh_fn : dada_del_note_if_below_thresh_fn, k_NOTATION_OBJECT_ROLL, &limit_mc, NULL, NULL);
}

double dada_roll_note_get_duration(t_llll *gs)
{
	if (gs && gs->l_size >= 2)
		if (is_hatom_number(&gs->l_head->l_next->l_next->l_hatom))
			return hatom_getdouble(&gs->l_head->l_next->l_next->l_hatom);
	return 0;
}

double dada_roll_chord_get_duration(t_llll *gs)
{
	if (gs) {
		t_llllelem *note;
		double dur = 0;
		for (note = gs->l_head; note; note = note->l_next)
			if (hatom_gettype(&note->l_hatom) == H_LLLL){
				double note_dur = dada_roll_note_get_duration(hatom_getllll(&note->l_hatom));
				if (note_dur > dur)
					dur = note_dur;
			}
		return dur;
	}
	return 0;
}



// use negative values for "from" and "to" to avoid setting that limit
long dada_roll_crop_markers_fn(t_llll *marker, e_notation_objects notation_obj, void *idx, void *onset, void *from, void *to, void *keep_this_tempo) //void *copy_tempi)
{
	double from_val = *((double *)from);
	double to_val = *((double *)to);
//	char copy_tempi_val = *((char *)copy_tempi);
	
	if (marker && marker->l_head) {
		double onset = hatom_getdouble(&marker->l_head->l_hatom); // the marker onset
        if (keep_this_tempo && keep_this_tempo == marker->l_owner) {
            hatom_setdouble(&marker->l_head->l_hatom, from_val);
            return 0;
        }

/*		if (copy_tempi_val && marker->l_size >= 3 && hatom_gettype(&marker->l_head->l_next->l_next->l_hatom) == H_SYM && hatom_getsym(&marker->l_head->l_next->l_next->l_hatom) == _llllobj_sym_tempo) {
			hatom_setdouble(&marker->l_head->l_hatom, from_val);
			return 0;
		}
*/
        
		if (from_val >= 0 && to_val >= 0) {
			if (onset < from_val || onset > to_val)
                return 1; // 1 = delete
		} else if (from_val >= 0 && to_val < 0) {
			if (onset < from_val)
				return 1;
		} else if (from_val < 0 && to_val >= 0) {
			if (onset > to_val)
				return 1;
		}
        
	}
	return 0;
}


// tp1 - tp2
t_timepoint timepoints_diff(t_timepoint tp1, t_timepoint tp2)
{
    t_timepoint res;
    if (tp1.measure_num == tp2.measure_num) {
        res.measure_num = 0;
        res.pt_in_measure = rat_rat_diff(tp1.pt_in_measure, tp2.pt_in_measure);
    } else {
        res.measure_num = tp1.measure_num - tp2.measure_num;
        res.pt_in_measure = tp1.pt_in_measure; // yep, there's a good reason for that, provided that no timepoint has pt_in_measure >= measuresymdur
//        res.pt_in_measure = tp2.pt_in_measure; // yep, there's a good reason for that, provided that no timepoint has pt_in_measure >= measuresymdur
    }
    res.voice_num = tp2.voice_num - tp1.voice_num;
    return res;
}



// use negative measure values for "from" and "to" to avoid setting that limit
long dada_score_crop_and_shift_markers_fn(t_llll *marker, e_notation_objects notation_obj, void *idx, void *onset, void *from, void *to, void *dummy)
{
    t_timepoint from_tp = *((t_timepoint *)from);
    t_timepoint to_tp = *((t_timepoint *)to);
    
    if (marker && marker->l_head) {
        if (hatom_gettype(&marker->l_head->l_hatom) != H_LLLL)
            return 1; // we delete the milliseconds-attached markers, for now
        
        t_llll *mk_ll = hatom_getllll(&marker->l_head->l_hatom);
        if (mk_ll->l_size < 3 || mk_ll->l_depth != 1)
            return 1; // delete
        
        t_timepoint this_tp;
        this_tp.voice_num = hatom_getlong(&mk_ll->l_head->l_hatom) - 1;
        this_tp.measure_num = hatom_getlong(&mk_ll->l_head->l_next->l_hatom) - 1;
        this_tp.pt_in_measure = hatom_getrational(&mk_ll->l_head->l_next->l_next->l_hatom);
        
        if (from_tp.measure_num >= 0 && to_tp.measure_num >= 0) {
            if (timepoints_compare(this_tp, from_tp) < 0 || timepoints_compare(this_tp, to_tp) >= 0)
                return 1;
            else {
                // must shift timepoint, anyway
                t_timepoint res_tp = timepoints_diff(this_tp, from_tp);
                hatom_setlong(&mk_ll->l_head->l_next->l_hatom, res_tp.measure_num + 1);
                hatom_setrational(&mk_ll->l_head->l_next->l_next->l_hatom, res_tp.pt_in_measure);
            }
        } else if (from_tp.measure_num >= 0 && to_tp.measure_num < 0) {
            if (timepoints_compare(this_tp, from_tp) < 0)
                return 1;
            else {
                // must shift timepoint, anyway
                t_timepoint res_tp = timepoints_diff(this_tp, from_tp);
                hatom_setlong(&mk_ll->l_head->l_next->l_hatom, res_tp.measure_num + 1);
                hatom_setrational(&mk_ll->l_head->l_next->l_next->l_hatom, res_tp.pt_in_measure);
            }
        } else if (from_tp.measure_num < 0 && to_tp.measure_num >= 0) {
            if (timepoints_compare(this_tp, to_tp) >= 0)
                return 1;
        }
        
    }
    return 0;
}




char is_symbol_notename(t_symbol *s)
{
    if (!s)
        return 0;
    
    long i, l = strlen(s->s_name);
    
    if (l < 1)
        return 0;
    
    for (i = 0; i < l; i++)
        if (isupper(s->s_name[i]) || isnumber(s->s_name[i])) {
            // might still be a notename
        } else
            return 0;
    return 1;
}

char dada_roll_is_llll_note(t_llll *gs)
{
    if (gs->l_size < 2)
        return 0;
    
    if (hatom_gettype(&gs->l_head->l_hatom) == H_SYM && !is_symbol_notename(hatom_getsym(&gs->l_head->l_hatom)))
        return 0;
    
    return 1;
}

long dada_roll_chord_crop_tails_fn(t_llll *gs, e_notation_objects notation_obj, void *idx, void *onset, void *tail_pos, void *mark_cropped_notes, void *tolerance)
{
	t_llllelem *note = gs->l_head, *next_note;
	if (note) {
		double tp = *(double *)tail_pos;
		double onset = hatom_getdouble(&gs->l_head->l_hatom); // actually the chord onset
		
		for (note = gs->l_head->l_next; note; note = next_note) {
			next_note = note->l_next;
			if (hatom_gettype(&note->l_hatom) == H_LLLL) {
				t_llll *note_ll = hatom_getllll(&note->l_hatom);
				if (dada_roll_is_llll_note(note_ll)) {
					t_hatom *h = &note_ll->l_head->l_next->l_hatom;
					double dur = hatom_getdouble(h);
					if (onset + dur > tp) {
                        if (tp <= onset + (tolerance ? *((double *)tolerance) : 0))
							llll_destroyelem(note);
						else  {
							hatom_setdouble(h, tp - onset);
							if (mark_cropped_notes)
								note_ll->l_thing.w_long |= DADA_CUT_NOTE_START;
						}
					}
				}
			}
		}
		if (!gs->l_head->l_next || hatom_gettype(&gs->l_head->l_next->l_hatom) != H_LLLL)
			return 1;
	}
	return 0;
}

long dada_roll_chord_crop_head_fn(t_llll *gs, e_notation_objects notation_obj, void *idx, void *onset, void *head_pos, void *mark_cropped_notes, void *dummy3)
{
	t_llllelem *note = gs->l_head, *next_note;
	if (note) {
		double onset = hatom_getdouble(&gs->l_head->l_hatom); // actually the chord onset
		double hp = *(double *)head_pos;
		if (onset < hp) {
			double delta = hp - onset;
			for (note = gs->l_head->l_next; note; note = next_note) {
				next_note = note->l_next;
				if (hatom_gettype(&note->l_hatom) == H_LLLL) {
					t_llll *note_ll = hatom_getllll(&note->l_hatom);
					if (dada_roll_is_llll_note(note_ll)) {
						t_hatom *h = &note_ll->l_head->l_next->l_hatom;
						double dur = hatom_getdouble(h);
						if (onset + dur <= hp) 
							llll_destroyelem(note);
						else {
							hatom_setdouble(h, dur - delta);
							if (mark_cropped_notes)
								note_ll->l_thing.w_long |= DADA_CUT_NOTE_END;
						}
					}
				}
			}
			hatom_setdouble(&gs->l_head->l_hatom, hp);
			if (!gs->l_head->l_next || hatom_gettype(&gs->l_head->l_next->l_hatom) != H_LLLL)
				return 1;
		}
	}
	return 0;
}

long dada_roll_chord_shiftncrop_fn(t_llll *gs, e_notation_objects notation_obj, void *idx, void *onset, void *delta_onset_ms, void *crop_length_ms, void *dummy)
{
	if (gs->l_head && is_hatom_number(&gs->l_head->l_hatom)) {
		double this_onset = hatom_getdouble(&gs->l_head->l_hatom);
		double new_onset = this_onset + *(double *)delta_onset_ms;
		double head_pos = 0;
		hatom_setdouble(&gs->l_head->l_hatom, new_onset);
		if (*(double *)delta_onset_ms > 0)
			return dada_roll_chord_crop_tails_fn(gs, notation_obj, idx, onset, crop_length_ms, NULL, NULL);
		else
			return dada_roll_chord_crop_head_fn(gs, notation_obj, idx, onset, &head_pos, NULL, NULL);
	}
	return 1;
}


void dada_roll_shiftncrop(t_llll *gs, double shift_delta_ms, double crop_length_ms)
{
	dada_roll_iterate_on_chords(gs, dada_roll_chord_shiftncrop_fn, k_NOTATION_OBJECT_ROLL, &shift_delta_ms, &crop_length_ms, NULL);
}


long dada_roll_chord_shift_fn(t_llll *gs, e_notation_objects notation_obj, void *idx, void *onset, void *delta_onset_ms, void *dummy2, void *dummy3)
{
	if (gs->l_head && is_hatom_number(&gs->l_head->l_hatom)) {
		double this_onset = hatom_getdouble(&gs->l_head->l_hatom);
		double new_onset = this_onset + *(double *)delta_onset_ms;
		hatom_setdouble(&gs->l_head->l_hatom, new_onset);
		return 0;
	}
	return 1;
}

long dada_roll_marker_shift_fn(t_llll *marker, e_notation_objects notation_obj, void *idx, void *onset, void *delta_onset_ms, void *dummy2, void *dummy3)
{
	if (marker && marker->l_head && is_hatom_number(&marker->l_head->l_hatom)) {
		double this_onset = hatom_getdouble(&marker->l_head->l_hatom);
		double new_onset = this_onset + *(double *)delta_onset_ms;
		hatom_setdouble(&marker->l_head->l_hatom, new_onset);
		return 0;
	}
	return 1;
}

void dada_roll_prepend_roll_sym(t_llll *gs)
{
    if (gs) {
        if (!gs->l_head || hatom_gettype(&gs->l_head->l_hatom) != H_SYM || hatom_getsym(&gs->l_head->l_hatom) != _llllobj_sym_roll)
            llll_prependsym(gs, _llllobj_sym_roll);
    }
}

//destructve
void dada_roll_shift(t_llll *gs, double shift_delta_ms, char via_cropping)
{
    if (via_cropping && shift_delta_ms < 0) {
        t_llll *rightpart = dada_roll_split_preserve(gs, -shift_delta_ms, false, false, false);
        llll_clear(gs);
        llll_chain(gs, rightpart);
    }
    
	dada_roll_iterate_on_chords(gs, dada_roll_chord_shift_fn, k_NOTATION_OBJECT_ROLL, &shift_delta_ms, NULL, NULL);
	dada_iterate_on_markers(gs, dada_roll_marker_shift_fn, k_NOTATION_OBJECT_ROLL, &shift_delta_ms, NULL, NULL);
}


double dada_roll_get_first_onset(t_llll *gs)
{
	// find first onset
	t_llllelem *voice_el = get_first_nonheader_elem(gs);
	double best_onset = -1;
	for (; voice_el; voice_el = voice_el->l_next) {
		if (hatom_gettype(&voice_el->l_hatom) == H_LLLL) {
			t_llllelem *chord_el = hatom_getllll(&voice_el->l_hatom)->l_head;
			t_llll *ll;
			while (chord_el && hatom_gettype(&chord_el->l_hatom) != H_LLLL) 
				chord_el = chord_el->l_next;
			if (chord_el && (ll = hatom_getllll(&chord_el->l_hatom)) && ll->l_head && is_hatom_number(&ll->l_head->l_hatom)) {
				double this_onset = hatom_getdouble(&ll->l_head->l_hatom);
				if (best_onset < 0 || this_onset < best_onset)
					best_onset = this_onset;
			}
		}
	}	
	return MAX(0, best_onset);
}

void dada_roll_trim_blank_starting_space(t_llll *gs, double *new_gs_offset_ms)
{
	double offset = dada_roll_get_first_onset(gs);
	if (new_gs_offset_ms)
		*new_gs_offset_ms = offset;
	dada_roll_shift(gs, -offset);
}




long dada_roll_chord_applywin_fn(t_llll *gs, e_notation_objects notation_obj, void *idx, void *onset, void *wintype, void *duration_ms, void *dummy2)
{
    e_dada_windows wintype_ok = (e_dada_windows)(*((long *)wintype));
    
    if (gs->l_head && is_hatom_number(&gs->l_head->l_hatom)) {
        double totdur = *((double *)duration_ms);
        double this_onset = hatom_getdouble(&gs->l_head->l_hatom);

        for (t_llllelem *note = gs->l_head->l_next; note; note = note->l_next) {
            if (hatom_gettype(&note->l_hatom) == H_LLLL) {
                t_llll *note_ll = hatom_getllll(&note->l_hatom);
                if (note_ll->l_size >= 3 && dada_roll_is_llll_note(note_ll)) {
                    t_hatom *h = &note_ll->l_head->l_next->l_next->l_hatom;
                    double new_vel = hatom_getdouble(h) * dada_get_window_value(wintype_ok, this_onset/totdur);
                    hatom_setlong(h, CLAMP((long)round(new_vel), DADA_MIN_VELOCITY, DADA_MAX_VELOCITY));
                }
            }
        }

    }
    return 0;
}

void dada_roll_apply_window_on_velocities(t_llll *gs, e_dada_windows window_type, double *duration_ms)
{
    long window_type_long = (long)window_type;
    double totdur = duration_ms ? *((double *)duration_ms) : dada_roll_get_length(gs);
    dada_roll_iterate_on_chords(gs, dada_roll_chord_applywin_fn, k_NOTATION_OBJECT_ROLL, &window_type_long, &totdur, NULL);
}





long dada_score_chord_applywin_fn(t_llll *gs, e_notation_objects notation_obj, void *idx, void *symonset, void *wintype, void *tot_symduration, void *dummy2)
{
    e_dada_windows wintype_ok = (e_dada_windows)(*((long *)wintype));
    t_rational this_symonset = *((t_rational *)symonset);
    if (gs->l_head && is_hatom_number(&gs->l_head->l_hatom)) {
        t_rational totsymdur = *((t_rational *)tot_symduration);
        
        for (t_llllelem *note = gs->l_head->l_next; note; note = note->l_next) {
            if (hatom_gettype(&note->l_hatom) == H_LLLL) {
                t_llll *note_ll = hatom_getllll(&note->l_hatom);
                if (note_ll->l_size >= 2 && dada_roll_is_llll_note(note_ll)) {
                    t_hatom *h = &note_ll->l_head->l_next->l_hatom;
                    double new_vel = hatom_getdouble(h) * dada_get_window_value(wintype_ok, rat2double(this_symonset)/rat2double(totsymdur));
                    hatom_setlong(h, CLAMP((long)round(new_vel), DADA_MIN_VELOCITY, DADA_MAX_VELOCITY));
                }
            }
        }
        
    }
    return 0;
}

void dada_score_apply_window_on_velocities(t_llll *gs, e_dada_windows window_type, t_rational *tot_symduration)
{
    long window_type_long = (long)window_type;
    t_rational totdur = tot_symduration ? *tot_symduration : dada_score_gettotsymduration(gs);
    dada_score_iterate_on_chords(gs, dada_score_chord_applywin_fn, k_NOTATION_OBJECT_ROLL, &window_type_long, &totdur, NULL);
}







double dada_roll_get_length(t_llll *gs)
{
	return get_max_rhythm_length(gs);
}


long dada_roll_get_labels_fn(t_llll *gs, e_notation_objects notation_obj, void *idx, void *onset, void *labels, void *dummy2, void *dummy3)
{
	t_llllelem *el = NULL, *l_el = NULL;
	t_llll *labels_ll = (t_llll *)labels;
	for (el = gs->l_head; el; el = el->l_next) {
		t_llll *ll = NULL;
		if (hatom_gettype(&el->l_hatom) == H_LLLL && (ll = hatom_getllll(&el->l_hatom)) && ll->l_head && 
			hatom_gettype(&ll->l_head->l_hatom) == H_SYM && hatom_getsym(&ll->l_head->l_hatom) == _llllobj_sym_name) {
			t_llll *this_label = llll_clone(ll);
			llll_behead(this_label);
			
			t_llllelem *single_label;
			for (single_label = this_label->l_head; single_label; single_label = single_label->l_next) {
				t_llll *single_label_ll = llll_get();
				llll_appendhatom_clone(single_label_ll, &single_label->l_hatom, 0, WHITENULL_llll);
				
				// check if already present
				char found = 0;
				for (l_el = labels_ll->l_head; l_el; l_el = l_el->l_next) {
					t_llll *l_ll = hatom_getllll(&l_el->l_hatom);
					t_llll *l_ll_label = hatom_getllll(&l_ll->l_head->l_hatom);
					
					if (llll_eq_ignoretype(l_ll_label, single_label_ll)) {
						long count = hatom_getlong(&l_ll->l_head->l_next->l_hatom);
						hatom_setlong(&l_ll->l_head->l_next->l_hatom, count+1);
						found = 1;
						break;
					}
				}
				
				if (!found) {
					t_llll *l_ll = llll_get();
					llll_appendllll(l_ll, single_label_ll, 0, WHITENULL_llll); // label
					llll_appendlong(l_ll, 1, 0, WHITENULL_llll); // count
					llll_appendllll(labels_ll, l_ll, 0, WHITENULL_llll);
				} else {
					llll_free(single_label_ll);
				}
			}
			
			llll_free(this_label);
		}
	}

	return 0;
}


// gs = gathered syntax
t_llll *dada_roll_get_labels(t_llll *gs)
{
	t_llll *labels = llll_get();
	dada_roll_iterate_on_chords(gs, (dada_gs_modif_fn)dada_roll_get_labels_fn, k_NOTATION_OBJECT_ROLL, labels, NULL, NULL);
	dada_roll_iterate_on_notes(gs, (dada_gs_modif_fn)dada_roll_get_labels_fn, k_NOTATION_OBJECT_ROLL, labels, NULL, NULL);
	return labels;
}



long dada_roll_retain_label_fn(t_llll *gs, e_notation_objects notation_obj, void *idx, void *onset, void *label_hatom, void *dummy2, void *dummy3)
{
	t_llll *chord_labels = NULL;
	t_hatom *label_h = (t_hatom *)label_hatom;
	llll_parseargs(NULL, gs, "l", _llllobj_sym_name, &chord_labels);
	
    if (!is_name_contained(label_h, chord_labels)) {
		// checking note by note
		t_llllelem *el = gs->l_head, *nextel;
		char at_least_one_note_remains = false;
		while (el) {
			nextel = el->l_next;
			if (hatom_gettype(&el->l_hatom) == H_LLLL) {
				t_llll *ll = hatom_getllll(&el->l_hatom);
				if (ll && ll->l_head && hatom_gettype(&ll->l_head->l_hatom) != H_SYM) { // it's a note
					t_llll *note_labels = NULL;
					llll_parseargs(NULL, ll, "l", _llllobj_sym_name, &note_labels);
					if (!is_name_contained(label_h, note_labels)) {
						llll_destroyelem(el);
					} else 
						at_least_one_note_remains = true;
					llll_free(note_labels);
				}
			}
			el = nextel;
		}
		
		if (!at_least_one_note_remains) {
			llll_free(chord_labels);
			return 1; // must delete whole chord.
		}
	}
	
	llll_free(chord_labels);
	return 0;
}

long dada_roll_retain_label_for_markers_fn(t_llll *marker, e_notation_objects notation_obj, void *idx, void *onset, void *label_hatom, void *dummy2, void *dummy3)
{
	if (marker && marker->l_head) {
		char must_free = false;
		t_llll *ll = NULL;
		if (hatom_gettype(&marker->l_head->l_next->l_hatom) == H_LLLL) {
			ll = hatom_getllll(&marker->l_head->l_next->l_hatom);
		} else {
			ll = llll_get();
			llll_appendhatom_clone(ll, &marker->l_head->l_next->l_hatom, 0, WHITENULL_llll);
			must_free = true;
		}
		
		if (!is_name_contained((t_hatom *)label_hatom, ll)) {
			if (must_free)
				llll_free(ll);
			return 1;
		}
		
		if (must_free)
			llll_free(ll);
	}
	return 0;
}


void dada_roll_retain_label(t_llll *gs, t_hatom *label)
{
	dada_roll_iterate_on_chords(gs, (dada_gs_modif_fn)dada_roll_retain_label_fn, k_NOTATION_OBJECT_ROLL, label, NULL, NULL);
	dada_iterate_on_markers(gs, (dada_gs_modif_fn)dada_roll_retain_label_for_markers_fn, k_NOTATION_OBJECT_ROLL, label, NULL, NULL);
}


t_llll *dada_roll_extract_label(t_llll *gs, t_hatom *label, double *new_gs_offset_ms)
{
	t_llll *gs_cloned = llll_clone(gs);
	dada_roll_retain_label(gs_cloned, label);
	dada_roll_trim_blank_starting_space(gs_cloned, new_gs_offset_ms);
	return gs_cloned;
}


// joins the notes which had been cut
void dada_roll_join_cut_notes(t_llll *gs, long sew_this, long with_this)
{
	t_llllelem *voice, *chord, *note, *chord_tmp, *note_tmp, *next_note_tmp, *next_chord_tmp;
	for (voice = gs->l_head; voice; voice = voice->l_next) {
		t_llll *voice_ll = hatom_getllll(&voice->l_hatom);
		for (chord = voice_ll->l_head; chord; chord = chord->l_next) {
			if (hatom_gettype(&chord->l_hatom) == H_LLLL) {
				t_llll *chord_ll = hatom_getllll(&chord->l_hatom);
				if (chord_ll->l_size > 0) {
					double chord_onset = hatom_getdouble(&chord_ll->l_head->l_hatom);
					for (note = chord_ll->l_head->l_next; note; note = note->l_next) {
						if (hatom_gettype(&note->l_hatom) == H_LLLL) {
							t_llll *note_ll = hatom_getllll(&note->l_hatom);
							if (note_ll->l_size >= 2 && note_ll->l_thing.w_long & sew_this) {
								double note_tail = chord_onset + hatom_getdouble(&note_ll->l_head->l_next->l_hatom);
								double pitch = hatom_getdouble(&note_ll->l_head->l_hatom);
								char found = false;
								
								for (chord_tmp = chord->l_next; chord_tmp && !found; chord_tmp = next_chord_tmp) {
									next_chord_tmp = chord_tmp->l_next;
									if (hatom_gettype(&chord_tmp->l_hatom) == H_LLLL) {
										t_llll *chord_tmp_ll = hatom_getllll(&chord_tmp->l_hatom);
										if (chord_tmp_ll->l_size > 0) {
											double chord_tmp_onset = hatom_getdouble(&chord_tmp_ll->l_head->l_hatom);
											if (fabs(chord_tmp_onset - note_tail) < DADA_JOIN_CUT_NOTES_EPSILON_MS) {
												for (note_tmp = chord_tmp_ll->l_head->l_next; note_tmp && !found; note_tmp = next_note_tmp) {
													next_note_tmp = note_tmp->l_next;
													if (hatom_gettype(&note_tmp->l_hatom) == H_LLLL) {
														t_llll *note_tmp_ll = hatom_getllll(&note_tmp->l_hatom);
														if (note_tmp_ll->l_size >= 2 && note_tmp_ll->l_thing.w_long & with_this) {
															double pitch_tmp = hatom_getdouble(&note_tmp_ll->l_head->l_hatom); 
															if (pitch_tmp == pitch) { // no need of epsilon, I think
																double note_tail_tmp = chord_tmp_onset + hatom_getdouble(&note_tmp_ll->l_head->l_next->l_hatom); 
																hatom_setdouble(&note_ll->l_head->l_next->l_hatom, note_tail_tmp - chord_onset);
																llll_destroyelem(note_tmp);
																found = true;
															}
														}
													}
												}
											} else if (chord_tmp_onset > note_tail)
												break;
											
											if (!chord_tmp_ll->l_head->l_next || hatom_gettype(&chord_tmp_ll->l_head->l_next->l_hatom) != H_LLLL) 
												llll_destroyelem(chord_tmp);
										}
									}
								}
								
							}
						}
					}
				}
			}
		}
	}
}


char* get_string_for_lthing(t_hatom *h){
	if (hatom_gettype(h) == H_LLLL) {
		char *out = (char *)bach_newptr(20 * sizeof(char));	
		snprintf_zero(out, 20, "{:%ld}", hatom_getllll(h)->l_thing.w_long); 
		return out;
	}
	return NULL;
}


void dada_roll_circularshift(t_llll *gs, double shift_delta_ms)
{
	double max_len = dada_roll_get_length(gs);
	double inv_max_len = -max_len;
	t_llll *gs2;
	
	dada_roll_iterate_on_chords(gs, dada_roll_chord_shift_fn, k_NOTATION_OBJECT_ROLL, &shift_delta_ms, NULL, NULL);
	if (shift_delta_ms > 0) {
		gs2 = dada_roll_split_preserve(gs, max_len, true, true, false);
		dada_roll_iterate_on_chords(gs2, dada_roll_chord_shift_fn, k_NOTATION_OBJECT_ROLL, &inv_max_len, NULL, NULL);
	} else {
		gs2 = dada_roll_split_preserve(gs, 0, true, true, false);
		dada_roll_iterate_on_chords(gs, dada_roll_chord_shift_fn, k_NOTATION_OBJECT_ROLL, &max_len, NULL, NULL);
	} 
	dada_roll_mix(gs, gs2, DADA_CUT_ANY, DADA_CUT_ANY);
}


long sort_by_first_subelem_fn(void *dummy, t_llllelem *a, t_llllelem *b)
{
	long type_a = hatom_gettype(&a->l_hatom);
	long type_b = hatom_gettype(&b->l_hatom);
	
	if (type_a == H_LLLL && type_b != H_LLLL)
		return 1;
	if (type_a != H_LLLL && type_b == H_LLLL)
		return 0;
	if (type_a == H_LLLL && type_b == H_LLLL) {
		t_llll *ll_a = hatom_getllll(&a->l_hatom);
		t_llll *ll_b = hatom_getllll(&b->l_hatom);
		if (ll_a && ll_b && ll_a->l_head && ll_b->l_head && is_hatom_number(&ll_a->l_head->l_hatom) && is_hatom_number(&ll_b->l_head->l_hatom))
			return (hatom_getdouble(&ll_a->l_head->l_hatom) <= hatom_getdouble(&ll_b->l_head->l_hatom));
	}
	return 1;
}



void dada_roll_sort_chords(t_llll *gs)
{
	// sort each voice
	t_llllelem *voice;
	for (voice = gs->l_head; voice; voice = voice->l_next) {
		if (hatom_gettype(&voice->l_hatom) == H_LLLL) {
			t_llll *voice_ll = hatom_getllll(&voice->l_hatom);
			t_llll *new_voice_ll = NULL;
			llll_mergesort_with_lthings(voice_ll, &new_voice_ll, sort_by_first_subelem_fn, NULL);
			new_voice_ll->l_owner = voice;
			hatom_setllll(&voice->l_hatom, new_voice_ll);
		}
	}
}

void dada_roll_sort_notes(t_llll *gs)
{
	// sort each chord
	t_llllelem *voice, *chord;
	for (voice = gs->l_head; voice; voice = voice->l_next) {
        if (hatom_gettype(&voice->l_hatom) == H_LLLL) {
            t_llll *voice_ll = hatom_getllll(&voice->l_hatom);
            for (chord = voice_ll->l_head; chord; chord = chord->l_next) {
                if (hatom_gettype(&chord->l_hatom) == H_LLLL) {
                    t_llll *chord_ll = hatom_getllll(&chord->l_hatom);
                    double onset = 0;
                    if (chord_ll && chord_ll->l_head && is_hatom_number(&chord_ll->l_head->l_hatom)) {
                        onset = hatom_getdouble(&chord_ll->l_head->l_hatom);
                        llll_behead(chord_ll);
                    }
                    
                    t_llll *new_chord_ll = NULL;
                    llll_mergesort_with_lthings(chord_ll, &new_chord_ll, sort_by_first_subelem_fn, NULL);
                    llll_prependdouble(new_chord_ll, onset, 0, WHITENULL_llll);
                    new_chord_ll->l_owner = chord;
                    hatom_setllll(&chord->l_hatom, new_chord_ll);
                }
            }
        }
	}
}


void dada_remove_voice_flags(t_llll *gs)
{
	t_llllelem *voice;
	for (voice = gs->l_head; voice; voice = voice->l_next) {
		if (hatom_gettype(&voice->l_hatom) == H_LLLL) {
			t_llll *voice_ll = hatom_getllll(&voice->l_hatom);
			if (voice_ll->l_tail && hatom_gettype(&voice_ll->l_tail->l_hatom) != H_LLLL)
				llll_destroyelem(voice_ll->l_tail);
		}
	}
}

void *copy_lthing_fn(void *x)
{
	return x;
}

// DESTRUCTIVE g1 becomes the result AND ALSO FREES gs2
void dada_roll_mix(t_llll *gs1, t_llll *gs2, long sew_this, long with_this)
{
	if (!gs2)
		return;
	
	t_llll *mix = llll_get();
    
    t_llll *header = dada_sliceheader(gs1);
    llll_free(dada_sliceheader(gs2));
    
	t_llll *gs1_clone = llll_clone_extended(gs1, WHITENULL_llll, 0, copy_lthing_fn);
	dada_remove_voice_flags(gs2);
	

	llll_appendllll(mix, gs1_clone, 0, WHITENULL_llll);
	llll_appendllll(mix, gs2, 0, WHITENULL_llll);
	mix = llll_trans(mix, 0);
	llll_flat(mix, 2, 2, 0, LLLL_FREETHING_DONT);
	llll_clear(gs1);
	llll_chain(gs1, mix);

	dada_roll_sort_chords(gs1);
	dada_roll_join_cut_notes(gs1, sew_this, with_this);
    
    llll_rchain(header, gs1);
}

// DESTRUCTIVE g1 becomes the result AND ALSO FREES gs2
void dada_roll_blend(t_llll *gs1, t_llll *gs2, double split_point, double mark_split)
{
	dada_roll_iterate_on_chords(gs1, dada_roll_chord_crop_tails_fn, k_NOTATION_OBJECT_ROLL, &split_point, &mark_split, NULL);
	if (gs2) 
		dada_roll_iterate_on_chords(gs2, dada_roll_chord_crop_head_fn, k_NOTATION_OBJECT_ROLL, &split_point, &mark_split, NULL);
	dada_roll_mix(gs1, gs2);
}

// DESTRUCTIVE g1 becomes the result AND ALSO FREES gs2
void dada_roll_join(t_llll *gs1, t_llll *gs2)
{
    dada_roll_shift(gs2, dada_roll_get_length(gs1));
    dada_roll_mix(gs1, gs2);
}

t_llllelem *dada_roll_get_last_tempo_marker_before_time(t_llll *gs, double time)
{
    t_llll *ll = NULL;
    t_llllelem *res = NULL;
    t_llllelem *elem = gs->l_head;
    
    while (elem && hatom_gettype(&elem->l_hatom) == H_SYM)
        elem = elem->l_next;
    
    while (elem && hatom_gettype(&elem->l_hatom) == H_LLLL && (ll = hatom_getllll(&elem->l_hatom)) && ll->l_head && hatom_gettype(&ll->l_head->l_hatom) == H_SYM){
        if (hatom_getsym(&ll->l_head->l_hatom) == _llllobj_sym_markers) {
            t_llllelem *mkel, *nextmkel;
            for (mkel = ll->l_head->l_next; mkel; mkel = nextmkel) {
                nextmkel = mkel->l_next;
                if (hatom_gettype(&mkel->l_hatom) != H_LLLL)
                    continue;
                t_llll *mkllll = hatom_getllll(&mkel->l_hatom);
                if (mkllll) {
                    double onset = hatom_getdouble(&mkllll->l_head->l_hatom);
                    if (onset <= time &&
                        mkllll->l_size >= 4 && hatom_gettype(&mkllll->l_head->l_next->l_next->l_hatom) == H_SYM && hatom_getsym(&mkllll->l_head->l_next->l_next->l_hatom) == _llllobj_sym_tempo && hatom_gettype(&mkllll->l_head->l_next->l_next->l_next->l_hatom) == H_LLLL)
                        res = mkel;
                    else if (onset > time)
                        break;
                }
            }
        }
        elem = elem->l_next;
    }
    return res;
}


// gs becomes its left part, returns right part
t_llll *dada_roll_split_preserve(t_llll *gs, double split_point, char mark_split_left_parts, char mark_split_right_parts, char copy_tempi)
{
	double temp = split_point;
    double tolerance = 0.1;
	t_llll *right_part = llll_clone(gs);

//    post(">");
//    llll_print(gs, NULL, 0, 0, NULL);

    dada_roll_iterate_on_chords(right_part, dada_roll_chord_crop_head_fn, k_NOTATION_OBJECT_ROLL, &temp, &mark_split_right_parts, NULL);
	dada_roll_iterate_on_chords(gs, dada_roll_chord_crop_tails_fn, k_NOTATION_OBJECT_ROLL, &temp, &mark_split_left_parts, &tolerance);

//	llll_print(gs, NULL, 0, 0, NULL);
//	llll_print(right_part, NULL, 0, 0, NULL);
	
	// handling markers
	double dummy = -1;
    t_llllelem *start_tempo_for_right_part = dada_roll_get_last_tempo_marker_before_time(right_part, temp);
	temp = split_point - CONST_EPSILON_DOUBLE_EQ;
	dada_iterate_on_markers(right_part, dada_roll_crop_markers_fn, k_NOTATION_OBJECT_ROLL, &temp, &dummy, start_tempo_for_right_part);
	temp = split_point + CONST_EPSILON_DOUBLE_EQ;
	dada_iterate_on_markers(gs, dada_roll_crop_markers_fn, k_NOTATION_OBJECT_ROLL, &dummy, &temp, NULL);

//	llll_print(gs, NULL, 0, 0, NULL);
//	llll_print(right_part, NULL, 0, 0, NULL);
//	post("<");

	return right_part;
}

// gs becomes its left part, returns right part
t_llll *dada_roll_split(t_llll *gs, double split_point, char mark_split_left_parts, char mark_split_right_parts, char copy_tempi)
{
    t_llll *right = dada_roll_split_preserve(gs, split_point, mark_split_left_parts, mark_split_right_parts, copy_tempi);
    dada_roll_shift(right, -split_point);
    return right;
}


// gs becomes its left part, returns right part
t_llll *dada_roll_slice(t_llll *gs, double slice_point, char mark_split_left_parts, char mark_split_right_parts, char copy_tempi)
{
    t_llll *right_gs = dada_roll_split_preserve(gs, slice_point, mark_split_left_parts, mark_split_right_parts, copy_tempi);
    dada_roll_shift(right_gs, -slice_point);
    return right_gs;
}



long dada_roll_note_get_average_pitch_fn(t_llll *gs, e_notation_objects notation_obj, void *idx, void *onset, void *running_total, void *weight_total, void *use_dur_and_vel)
{
    if (gs->l_size >= 3 && is_hatom_number(&gs->l_head->l_hatom)) {
        double pitch = hatom_getdouble(&gs->l_head->l_hatom);
        double duration = hatom_getdouble(&gs->l_head->l_next->l_hatom);
        double velocity = hatom_getdouble(&gs->l_head->l_next->l_next->l_hatom);
        double weight = *((char *)use_dur_and_vel) ? (duration / 1000.) * (velocity / 127.) : 1;
        *((double *)running_total) += pitch * weight;
        *((double *)weight_total) += weight;
        return 0;
    }
    return 1;
}

double dada_roll_get_average_pitch(t_llll *gs, char use_dur_and_vel)
{
    double running_total = 0, weight_total = 0;
    dada_roll_iterate_on_notes(gs, dada_roll_note_get_average_pitch_fn, k_NOTATION_OBJECT_ROLL, &running_total, &weight_total, &use_dur_and_vel);
    return weight_total ? running_total / weight_total : 0;
}



long dada_roll_get_average_timepos_fn(t_llll *gs, e_notation_objects notation_obj, void *idx, void *onset, void *running_total, void *weight_total, void *use_vel)
{
    t_llllelem *elem;
    double this_onset = gs->l_head ? hatom_getdouble(&gs->l_head->l_hatom) : 0;
    for (elem = gs->l_head; elem; elem = elem->l_next) {
        if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
            t_llll *ll = hatom_getllll(&elem->l_hatom);
            if (ll && ll->l_size >= 3 && hatom_gettype(&ll->l_head->l_hatom) != H_SYM) {
                double duration = hatom_getdouble(&ll->l_head->l_next->l_hatom);
                double velocity = hatom_getdouble(&ll->l_head->l_next->l_next->l_hatom);
                double weight = *((char *)use_vel) ? (velocity / 127.) : 1;
                *((double *)running_total) += (this_onset + duration/2.) * weight;
                *((double *)weight_total) += weight;
            }
        }
    }
    return 0;
}


double dada_roll_get_average_timepos(t_llll *gs, char use_vel)
{
    double running_total = 0, weight_total = 0;
    dada_roll_iterate_on_chords(gs, dada_roll_get_average_timepos_fn, k_NOTATION_OBJECT_ROLL, &running_total, &weight_total, &use_vel);
    return weight_total ? running_total / weight_total : 0;
}

// not so simple an operation, after all
// use total_length < 0 to infer it from the gs
void dada_roll_retrograde(t_llll *gs, double total_length)
{
	t_llll *r = llll_get(); // will contain the retrograde, which will then be put inside gs
	if (total_length < 0)
		total_length = dada_roll_get_length(gs);
	
	t_llllelem *voice, *chord, *note;
	for (voice = gs->l_head; voice; voice = voice->l_next) {
        if (hatom_gettype(&voice->l_hatom) == H_LLLL) {
            t_llll *voice_ll = hatom_getllll(&voice->l_hatom);
            t_llll *r_voice_ll = llll_get();
            for (chord = voice_ll->l_head; chord; chord = chord->l_next) {
                if (hatom_gettype(&chord->l_hatom) == H_LLLL) {
                    t_llll *chord_ll = hatom_getllll(&chord->l_hatom);
                    if (chord_ll->l_size > 0) {
                        
                        double chord_onset = hatom_getdouble(&chord_ll->l_head->l_hatom);
                        long num_r_chords = 0;
                        double *r_chord_durs = (double *)bach_newptr(chord_ll->l_size * sizeof(double));
                        long i, r_flag = 0;
                        
                        for (note = chord_ll->l_head->l_next; note; note = note->l_next) {
                            if (hatom_gettype(&note->l_hatom) == H_LLLL) {
                                t_llll *note_ll = hatom_getllll(&note->l_hatom);
                                if (note_ll->l_size >= 2) {
                                    double note_dur = hatom_getdouble(&note_ll->l_head->l_next->l_hatom);
                                    if (!is_double_in_double_array(r_chord_durs, num_r_chords, note_dur, 0))
                                        r_chord_durs[num_r_chords++] = note_dur;
                                    
                                }
                            } else if (hatom_gettype(&note->l_hatom) == H_LONG)
                                r_flag = hatom_getlong(&note->l_hatom);
                        }
                        
                        for (i = 0; i < num_r_chords; i++) {
                            t_llll *new_ch_ll = llll_get();
                            double new_onset = total_length - (chord_onset + r_chord_durs[i]);
                            llll_appenddouble(new_ch_ll, new_onset, 0, WHITENULL_llll);
                            for (note = chord_ll->l_head->l_next; note; note = note->l_next) {
                                if (hatom_gettype(&note->l_hatom) == H_LLLL) {
                                    t_llll *note_ll = hatom_getllll(&note->l_hatom);
                                    if (note_ll->l_size >= 2) {
                                        double note_dur = hatom_getdouble(&note_ll->l_head->l_next->l_hatom);
                                        if (note_dur == r_chord_durs[i]) {
                                            t_llll *cloned_ll = llll_clone_extended(note_ll, WHITENULL_llll, 0, copy_lthing_fn);
                                            llll_appendllll_clone(new_ch_ll, cloned_ll, 0, WHITENULL_llll, NULL);
                                        }
                                    }
                                }
                            }
                            llll_appendlong(new_ch_ll, r_flag, 0, WHITENULL_llll);
                            llll_appendllll(r_voice_ll, new_ch_ll, 0, WHITENULL_llll);
                        }
                        
                        bach_freeptr(r_chord_durs);
                    } else
                        llll_appendhatom_clone(r_voice_ll, &chord->l_hatom, 0, WHITENULL_llll);
                    
                } else
                    llll_appendhatom_clone(r_voice_ll, &chord->l_hatom, 0, WHITENULL_llll);
            }
            llll_appendllll(r, r_voice_ll, 0, WHITENULL_llll);
        }
	}
	
	llll_clear(gs);
	llll_chain(gs, r);
	dada_roll_sort_chords(gs);
}




long dada_get_num_voices(t_llll *gs)
{
    t_llllelem *nhe = get_first_nonheader_elem(gs);
    t_llllelem *el;
    long count = 0;
    for (el = nhe; el; el = el->l_next)
        if (hatom_gettype(&el->l_hatom) == H_LLLL)
            count++;
    return count;
}

t_llll *dada_roll_gen_empty(long num_voices)
{
    t_llll *gs = llll_get();
    long i;
    for (i = 0; i < num_voices; i++)
        llll_appendllll(gs, llll_get());
    gs->l_thing.w_double = 0;
    return gs;
}

t_llll *dada_roll_gen(double onset, double cents, double duration, long velocity)
{
	t_llll *gs = llll_get();
	t_llll *voice = llll_get();
	t_llll *chord = llll_get();
	t_llll *note = llll_get();
	llll_appenddouble(note, cents, 0, WHITENULL_llll);
	llll_appenddouble(note, duration, 0, WHITENULL_llll);
	llll_appendlong(note, velocity, 0, WHITENULL_llll);
	llll_appenddouble(chord, onset, 0, WHITENULL_llll);
	llll_appendllll(chord, note, 0, WHITENULL_llll);
	llll_appendllll(voice, chord, 0, WHITENULL_llll);
	llll_appendllll(gs, voice, 0, WHITENULL_llll);
	gs->l_thing.w_double = duration;
	return gs;
}


long remove_all_marking_to_note_llll_lthing_fn(t_llll *gs, e_notation_objects notation_obj, void *idx, void *onset, void *dummy1, void *dummy2, void *dummy3)
{
	gs->l_thing.w_long = 0;
	return 0;
}

void remove_all_marking_to_llll_lthings(t_llll *gs, e_notation_objects notation_obj)
{
	dada_roll_iterate_on_notes(gs, remove_all_marking_to_note_llll_lthing_fn, notation_obj, NULL, NULL, NULL);
	gs->l_thing.w_double = 0;
}


long dada_roll_stretch_onset_fn(t_llll *gs, e_notation_objects notation_obj, void *idx, void *onset, void *factor, void *dummy2, void *dummy3)
{
	if (gs->l_head && is_hatom_number(&gs->l_head->l_hatom)) {
		double this_onset = hatom_getdouble(&gs->l_head->l_hatom);
		hatom_setdouble(&gs->l_head->l_hatom, this_onset * (*(double *)factor));
		return 0;
	}
	return 1;
}


long dada_roll_stretch_dur_fn(t_llll *gs, e_notation_objects notation_obj, void *idx, void *onset, void *factor, void *dummy2, void *dummy3)
{
	if (gs->l_head && gs->l_head->l_next && is_hatom_number(&gs->l_head->l_next->l_hatom)) {
		double this_dur = hatom_getdouble(&gs->l_head->l_next->l_hatom);
		hatom_setdouble(&gs->l_head->l_next->l_hatom, this_dur * (*(double *)factor));
		return 0;
	}
	return 1;
}

void dada_roll_stretch(t_llll *gs, double factor)
{
	dada_roll_iterate_on_chords(gs, dada_roll_stretch_onset_fn, k_NOTATION_OBJECT_ROLL, &factor, NULL, NULL);
	dada_roll_iterate_on_notes(gs, dada_roll_stretch_dur_fn, k_NOTATION_OBJECT_ROLL, &factor, NULL, NULL);
	gs->l_thing.w_double *= factor;
}









////// ******************* ///////
////// SCORE 
////// ******************* ///////


void dada_score_iterate_on_measures(t_llll *gs, dada_gs_modif_fn modif_fn, e_notation_objects notation_obj, void *arg1, void *arg2, void *arg3)
{
	t_llllelem *voice, *meas, *next_meas;
	t_timepoint idx = build_timepoint_with_voice(0, long2rat(0), 0);
	for (voice = get_first_nonheader_elem(gs); voice; voice = voice->l_next, idx.voice_num++) {
        t_rational symonset = long2rat(0);
		if (hatom_gettype(&voice->l_hatom) != H_LLLL)
			continue;
		idx.measure_num = 0;
		for (meas = hatom_getllll(&voice->l_hatom)->l_head; meas; meas = next_meas, idx.measure_num++) {
			next_meas = meas->l_next;
			if (hatom_gettype(&meas->l_hatom) != H_LLLL)
				continue;
            t_llll *measure_ll = hatom_getllll(&meas->l_hatom);
			if (modif_fn(measure_ll, notation_obj, &idx, &symonset, arg1, arg2, arg3))
				llll_destroyelem(meas);
            symonset = rat_rat_sum(symonset, dada_measure_getsymdur(measure_ll));
		}
	}
}


void dada_score_iterate_on_chords(t_llll *gs, dada_gs_modif_fn modif_fn, e_notation_objects notation_obj, void *arg1, void *arg2, void *arg3)
{
    t_llllelem *voice, *meas, *next_meas;
    t_timepoint idx = build_timepoint_with_voice(0, long2rat(0), 0);
    
    for (voice = get_first_nonheader_elem(gs); voice; voice = voice->l_next, idx.voice_num++) {
        t_rational symonset = long2rat(0), symonset_base = long2rat(0);

        if (hatom_gettype(&voice->l_hatom) != H_LLLL)
            continue;

        idx.measure_num = 0;
        for (meas = hatom_getllll(&voice->l_hatom)->l_head; meas; meas = next_meas, idx.measure_num++) {
            next_meas = meas->l_next;
            symonset = symonset_base;
            
            if (hatom_gettype(&meas->l_hatom) != H_LLLL)
                continue;
            
            t_llll *measure_ll = hatom_getllll(&meas->l_hatom);
            t_llllelem *measureinfo = measure_ll->l_head;
            
            // Let's get the measure whole duration, and then work backwards
            // We don't rely on the time signature (maybe the measure has LESS content)
            t_llllelem *elem = measureinfo ? measureinfo->l_next : NULL, *nextelem;
            t_llll *parent = NULL;
            long idx = 0;
            long in_grace_level = 0;
            
            while (elem) {
                nextelem = elem->l_next;
                parent = elem->l_parent;
                if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
                    t_llll *ll = hatom_getllll(&elem->l_hatom);
                    
                    if (hatom_gettype(&ll->l_head->l_hatom) == H_SYM && hatom_getsym(&ll->l_head->l_hatom) == _llllobj_sym_leveltype) {
                        // nothing to do
                    } else if (hatom_gettype(&ll->l_head->l_hatom) == H_LLLL) {
                        if (is_symbol_in_llll_first_level(ll, _llllobj_sym_g))
                            in_grace_level++;
                        nextelem = ll->l_head;
                    } else if (is_hatom_number(&ll->l_head->l_hatom)) {
                        // process chord!
                        if (modif_fn(ll, notation_obj, &idx, &symonset, arg1, arg2, arg3))
                            llll_destroyelem(elem);
                        if (!in_grace_level)
                            symonset = rat_rat_sum(symonset, rat_abs(hatom_getrational(&ll->l_head->l_hatom)));
                        idx++;
                    }
                }
                if (!nextelem && parent->l_owner) {
                    while (!parent->l_owner->l_next && parent->l_owner->l_parent->l_owner) {
                        parent = parent->l_owner->l_parent;
                        if (is_symbol_in_llll_first_level(parent, _llllobj_sym_g))
                            in_grace_level--;
                    }
                    if (parent == measure_ll) // extremely important, otherwise we get to end ABOVE measure_ll (which is a measure belonging to some other llll, it's NOT cloned!)
                        break;
                    nextelem = parent->l_owner->l_next;
                }
                elem = nextelem;
            }
            
            symonset_base = rat_rat_sum(symonset_base, dada_measure_getsymdur(measure_ll));
        }
    }
}






void dada_score_measure_crop_handle_leveltype_and_tupletinfo(t_llll *ll)
{
    t_llll *temp = ll;
    while (temp) {
        if (temp->l_head && hatom_gettype(&temp->l_head->l_hatom) == H_LLLL) {
            t_llll *temphead = hatom_getllll(&temp->l_head->l_hatom);
            if (hatom_gettype(&temphead->l_head->l_hatom) == H_SYM && hatom_getsym(&temphead->l_head->l_hatom) == _llllobj_sym_leveltype) {
                long leveltype = 0;
                char symbolic = 0;
                if (temphead->l_head->l_next && is_hatom_number(&temphead->l_head->l_next->l_hatom))
                    leveltype = hatom_getlong(&temphead->l_head->l_next->l_hatom);
                else if (temphead->l_head->l_next && hatom_gettype(&temphead->l_head->l_next->l_hatom) == H_SYM) {
                    leveltype = symbol2leveltype(hatom_getsym(&temphead->l_head->l_next->l_hatom));
                    symbolic = 1;
                }
                if (leveltype & (k_RHYTHM_LEVEL_TUPLET | k_RHYTHM_LEVEL_FORCE_TUPLET)) {
                    if (symbolic)
                        hatom_setsym(&temphead->l_head->l_next->l_hatom, _llllobj_sym_i);
                    else
                        hatom_setlong(&temphead->l_head->l_next->l_hatom, k_RHYTHM_LEVEL_IGNORE);
                    if (temp->l_head->l_next && hatom_gettype(&temp->l_head->l_next->l_hatom) == H_LLLL) {
                        t_llll *tempheadnext = hatom_getllll(&temp->l_head->l_next->l_hatom);
                        if (hatom_gettype(&tempheadnext->l_head->l_hatom) == H_SYM && hatom_getsym(&tempheadnext->l_head->l_hatom) == _llllobj_sym_tupletinfo)
                            llll_destroyelem(temp->l_head->l_next);
                    }
                }
            }
        }
        temp = temp->l_owner ? temp->l_owner->l_parent : NULL;
    }
}


long dada_score_measure_crop_tails_fn(t_llll *gs, e_notation_objects notation_obj, void *idx_param, void *onset, void *tail_pos, void *dummy2, void *dummy3)
{
	t_llllelem *measureinfo = gs->l_head;
	t_timepoint tp = *(t_timepoint *)tail_pos;
	t_timepoint idx = *(t_timepoint *)idx_param; 
	t_rational measure_symdur = dada_measure_getsymdur(gs);
	
	if (idx.measure_num > tp.measure_num || (idx.measure_num == tp.measure_num && tp.pt_in_measure.r_num == 0)) 
		return 1; // delete measure
	
	if (idx.measure_num < tp.measure_num || (idx.measure_num == tp.measure_num && rat_rat_cmp(tp.pt_in_measure, measure_symdur) > 0))
		return 0; // keep measure as is
	
	if (!measureinfo) 
		return 1;
	
    t_llllelem *elem = measureinfo ? measureinfo->l_next : NULL, *nextelem;
	t_rational symonset = long2rat(0);
	t_llll *parent = NULL;
    long in_grace_level = 0;
	while (elem) {
		nextelem = elem->l_next;
		parent = elem->l_parent;
		
		if (rat_rat_cmp(symonset, tp.pt_in_measure) >= 0) {
            if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
                t_llll *ll = hatom_getllll(&elem->l_hatom);
                dada_score_measure_crop_handle_leveltype_and_tupletinfo(ll);
            }
            llll_destroyelem(elem);
		} else {
			
			if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
				t_llll *ll = hatom_getllll(&elem->l_hatom);
				if (hatom_gettype(&ll->l_head->l_hatom) == H_SYM && hatom_getsym(&ll->l_head->l_hatom) == _llllobj_sym_leveltype) {
					// nothing to do
				} else if (hatom_gettype(&ll->l_head->l_hatom) == H_LLLL) {
                    if (is_symbol_in_llll_first_level(ll, _llllobj_sym_g))
                        in_grace_level++;
					nextelem = ll->l_head;
//					nextelem = hatom_getllll(&ll->l_head->l_hatom)->l_head;
				} else if (is_hatom_number(&ll->l_head->l_hatom)) {
					// process chord
					t_rational this_symdur = rat_abs(hatom_getrational(&ll->l_head->l_hatom));
					long sign = hatom_getrational(&ll->l_head->l_hatom).r_num >= 0 ? 1 : -1;
                    t_rational nextsymonset = in_grace_level == 0 ? rat_rat_sum(symonset, this_symdur) : symonset;
					if (rat_rat_cmp(nextsymonset, tp.pt_in_measure) > 0) {
                        // crop
						hatom_setrational(&ll->l_head->l_hatom, rat_long_prod(rat_rat_diff(tp.pt_in_measure, symonset), sign));
                        dada_score_measure_crop_handle_leveltype_and_tupletinfo(ll);
					} // else: nothing to do
					
					symonset = nextsymonset;
				}
			}
		}
		
		if (!nextelem && parent->l_owner) {
            if (is_symbol_in_llll_first_level(parent, _llllobj_sym_g))
                in_grace_level--;
			while (!parent->l_owner->l_next && parent->l_owner->l_parent->l_owner)
				parent = parent->l_owner->l_parent;
			if (parent == gs) // extremely important, otherwise we get to end ABOVE gs (which is a measure belonging to some other llll, it's NOT cloned!)
				break;
			nextelem = parent->l_owner->l_next;
		}
		
		elem = nextelem;
	}
	
	if (hatom_gettype(&measureinfo->l_hatom) == H_LLLL) {
		t_llll *measureinfo_ll = hatom_getllll(&measureinfo->l_hatom);
		if (measureinfo_ll->l_head && hatom_gettype(&measureinfo_ll->l_head->l_hatom) == H_LLLL) { 
			t_llll *timesig = hatom_getllll(&measureinfo_ll->l_head->l_hatom);
			t_timesignature ts = get_timesignature_from_llll(NULL, timesig);

			// cropping ts
			long i, j, count_nums = 0, count = 0;
			t_rational curr_onset = long2rat(0);
			for (i = 0; i < ts.num_numerator_elements; i++, count++) {
				t_rational next_onset = rat_rat_sum(curr_onset, genrat(ts.numerator_elements[i], ts.denominator));
				count_nums += ts.numerator_elements[i];
				long cmp = rat_rat_cmp(next_onset, tp.pt_in_measure);
				if (cmp == 0) {
					ts.num_numerator_elements = count + 1;
					ts.numerator = count_nums;
					break;
				} else if (cmp > 0) {
					t_rational diff = rat_rat_diff(tp.pt_in_measure, curr_onset);
					long this_lcm = lcm(diff.r_den, ts.denominator);
					long mult = this_lcm/ ts.denominator;
					for (j = 0; j < i; j++)
						ts.numerator_elements[j] *= mult;
					ts.denominator = this_lcm;
					ts.numerator_elements[i] = diff.r_num * (this_lcm/diff.r_den);
					ts.numerator = 0;
					for (j = 0; j <= i; j++)
						ts.numerator += ts.numerator_elements[i];
					ts.num_numerator_elements = count+1;
					break;
				}
			}
			
			t_llll *newtimesig = get_timesignature_as_llll(&ts);
			hatom_change_to_llll_and_free(&measureinfo_ll->l_head->l_hatom, newtimesig);
		}
	}
	
	return 0;
}



long dada_score_measure_crop_heads_fn(t_llll *gs, e_notation_objects notation_obj, void *idx_param, void *onset, void *tail_pos, void *dummy2, void *dummy3)
{
	t_llllelem *measureinfo = gs->l_head;
	t_timepoint tp = *(t_timepoint *)tail_pos;
	t_timepoint idx = *(t_timepoint *)idx_param;
	
	t_rational measure_symdur = dada_measure_getsymdur(gs);

	if (idx.measure_num < tp.measure_num || (idx.measure_num == tp.measure_num && rat_rat_cmp(tp.pt_in_measure, measure_symdur) >= 0))
		return 1; // delete measure
	
	if (idx.measure_num > tp.measure_num || (idx.measure_num == tp.measure_num && tp.pt_in_measure.r_num == 0))
		return 0; // keep measure as is
	
	if (!measureinfo) 
		return 1;
	
//	post("###");
//	llll_print(gs, NULL, 0, 0, NULL);
	
	// Let's get the measure whole duration, and then work backwards
	// We don't rely on the time signature (maybe the measure has LESS content)
    t_llllelem *elem = measureinfo ? measureinfo->l_next : NULL, *nextelem;
	t_llll *parent = NULL;
	t_rational global_symdur = long2rat(0);
    long in_grace_level = 0;
	while (elem) {
		nextelem = elem->l_next;
		parent = elem->l_parent;
		if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
			t_llll *ll = hatom_getllll(&elem->l_hatom);
			
//			char *buf = NULL;
//			llll_to_text_buf(ll, &buf, 0, 0, 0, NULL);
			
			if (hatom_gettype(&ll->l_head->l_hatom) == H_SYM && hatom_getsym(&ll->l_head->l_hatom) == _llllobj_sym_leveltype) {
				// nothing to do
			} else if (hatom_gettype(&ll->l_head->l_hatom) == H_LLLL) {
                if (is_symbol_in_llll_first_level(ll, _llllobj_sym_g))
                    in_grace_level++;
				nextelem = ll->l_head;
//				nextelem = hatom_getllll(&ll->l_head->l_hatom)->l_head;
			} else if (is_hatom_number(&ll->l_head->l_hatom)) {
				// process chord
                if (in_grace_level == 0) {
                    t_rational this_symdur = rat_abs(hatom_getrational(&ll->l_head->l_hatom));
                    global_symdur = rat_rat_sum(this_symdur, global_symdur);
                }
			}
		}
		if (!nextelem && parent->l_owner) {
            if (is_symbol_in_llll_first_level(parent, _llllobj_sym_g))
                in_grace_level--;
			while (!parent->l_owner->l_next && parent->l_owner->l_parent->l_owner)
				parent = parent->l_owner->l_parent;
			if (parent == gs) // extremely important, otherwise we get to end ABOVE gs (which is a measure belonging to some other llll, it's NOT cloned!)
				break;
			nextelem = parent->l_owner->l_next;
		}
		elem = nextelem;
	}

	
	t_rational target_pt_in_measure_bw = rat_rat_diff(global_symdur, tp.pt_in_measure);
	
	// And now working backwards!!
	elem = gs->l_tail;
	t_rational symonsetbw = long2rat(0);
	while (elem && elem != measureinfo) {
		nextelem = elem->l_prev;
		parent = elem->l_parent;
		
/*		t_llll *templl = llll_get();
		llll_appendhatom_clone(templl, &elem->l_hatom, 0, WHITENULL_llll);
		post(" >");
		llll_print(templl, NULL, 0, 2, NULL);
*/		
		if (rat_rat_cmp(symonsetbw, target_pt_in_measure_bw) >= 0) {
			if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
				t_llll *ll = hatom_getllll(&elem->l_hatom);
				if (hatom_gettype(&ll->l_head->l_hatom) == H_SYM && hatom_getsym(&ll->l_head->l_hatom) == _llllobj_sym_leveltype) {
                    dada_score_measure_crop_handle_leveltype_and_tupletinfo(ll);
				} else {
					llll_destroyelem(elem);
				}
			}
		} else {
			
			if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
				t_llll *ll = hatom_getllll(&elem->l_hatom);
				if (hatom_gettype(&ll->l_head->l_hatom) == H_SYM && hatom_getsym(&ll->l_head->l_hatom) == _llllobj_sym_leveltype) {
					// nothing to do
				} else if (hatom_gettype(&ll->l_head->l_hatom) == H_LLLL) {
					nextelem = ll->l_tail;
				} else if (is_hatom_number(&ll->l_head->l_hatom)) {
					// process chord
					t_rational this_symdur = rat_abs(hatom_getrational(&ll->l_head->l_hatom));
					long sign = hatom_getrational(&ll->l_head->l_hatom).r_num >= 0 ? 1 : -1;
					t_rational nextsymonsetbw = rat_rat_sum(symonsetbw, this_symdur);
					if (rat_rat_cmp(nextsymonsetbw, target_pt_in_measure_bw) > 0) {
                        // crop
						hatom_setrational(&ll->l_head->l_hatom, rat_long_prod(rat_rat_diff(target_pt_in_measure_bw, symonsetbw), sign));
                        dada_score_measure_crop_handle_leveltype_and_tupletinfo(ll);
					} // else: nothing to do
					
					symonsetbw = nextsymonsetbw;
				}
			}
		}
		
		if (!nextelem && parent->l_owner) {
			while (!parent->l_owner->l_prev && parent->l_owner->l_parent->l_owner)
				parent = parent->l_owner->l_parent;
			if (parent == gs) // extremely important, otherwise we get to end ABOVE gs (which is a measure belonging to some other llll, it's NOT cloned!)
				break;
			nextelem = parent->l_owner->l_prev;
		}
		
		elem = nextelem;
	}
	
	if (hatom_gettype(&measureinfo->l_hatom) == H_LLLL) {
		t_llll *measureinfo_ll = hatom_getllll(&measureinfo->l_hatom);
		if (measureinfo_ll->l_head && hatom_gettype(&measureinfo_ll->l_head->l_hatom) == H_LLLL) { 
			t_llll *timesig = hatom_getllll(&measureinfo_ll->l_head->l_hatom);
			t_timesignature ts = get_timesignature_from_llll(NULL, timesig);
			
			// cropping ts
			long i, j, count_nums = 0, count = 0;
			t_rational curr_onset = long2rat(0);
			for (i = ts.num_numerator_elements-1; i >= 0; i--, count++) {
				t_rational next_onset = rat_rat_sum(curr_onset, genrat(ts.numerator_elements[i], ts.denominator));
				count_nums += ts.numerator_elements[i];
				long cmp = rat_rat_cmp(next_onset, target_pt_in_measure_bw);
				if (cmp == 0) {
					ts.num_numerator_elements = count + 1;
					ts.numerator = count_nums;
					sysmem_copyptr(&ts.numerator_elements[i], &ts.numerator_elements[0], (count + 1) * sizeof(long));
					break;
				} else if (cmp > 0) {
					t_rational diff = rat_rat_diff(target_pt_in_measure_bw, curr_onset);
					long this_lcm = lcm(diff.r_den, ts.denominator);
					long mult = this_lcm/ ts.denominator;
					for (j = 0; j < i; j++)
						ts.numerator_elements[j] *= mult;
					ts.denominator = this_lcm;
					ts.numerator_elements[i] = diff.r_num * (this_lcm/diff.r_den);
					ts.numerator = 0;
					for (j = 0; j <= i; j++)
						ts.numerator += ts.numerator_elements[i];
					ts.num_numerator_elements = count+1;
					sysmem_copyptr(&ts.numerator_elements[i], &ts.numerator_elements[0], (count + 1) * sizeof(long));
					break;
				}
			}
			
			t_llll *newtimesig = get_timesignature_as_llll(&ts);
			hatom_change_to_llll_and_free(&measureinfo_ll->l_head->l_hatom, newtimesig);
		}
	}
	
	return 0;
}




// gs becomes its left part, returns right part
t_llll *dada_score_split(t_llll *gs, t_timepoint split_pt, t_timesignature *splitpt_ts, t_tempo *splitpt_tempo, char copy_tempi)
{
	t_timepoint temp = split_pt;
	t_llll *right_part = llll_clone(gs);

//    post("---");
//	llll_print(gs, NULL, 0, 6, NULL);

	dada_score_iterate_on_measures(right_part, dada_score_measure_crop_heads_fn, k_NOTATION_OBJECT_SCORE, &temp, NULL, NULL);
	
//	llll_print(right_part, NULL, 0, 6, NULL);

	dada_score_iterate_on_measures(gs, dada_score_measure_crop_tails_fn, k_NOTATION_OBJECT_SCORE, &temp, NULL, NULL);
	
//	llll_print(gs, NULL, 0, 6, NULL);
//	post("---");
	
	// copying last tempi of gs to right_part
	if (copy_tempi) {
		t_llllelem *voice_elem1, *voice_elem2;
		for (voice_elem1 = get_first_nonheader_elem(gs), voice_elem2 = get_first_nonheader_elem(right_part); 
			 voice_elem1 && voice_elem2; voice_elem1 = voice_elem1->l_next, voice_elem2 = voice_elem2->l_next) {
			if (hatom_gettype(&voice_elem1->l_hatom) == H_LLLL && hatom_gettype(&voice_elem2->l_hatom) == H_LLLL) {
				// finding last tempo of voice_elem1;
				t_llll *ll1 = hatom_getllll(&voice_elem1->l_hatom);
				t_llll *ll2 = hatom_getllll(&voice_elem2->l_hatom);
				t_llllelem *elem;
				t_tempo *tempo = NULL;
				for (elem = ll1->l_tail; elem; elem = elem->l_prev) {
					if (hatom_gettype(&elem->l_hatom) == H_LLLL) 
						tempo = dada_measure_get_last_tempo(hatom_getllll(&elem->l_hatom));
				}
				
				if (tempo) {
					// setting tempo to voice_elem2
					if (ll2->l_head && hatom_gettype(&ll2->l_head->l_hatom) == H_LLLL) 
						dada_measure_add_starting_tempo(hatom_getllll(&ll2->l_head->l_hatom), tempo);
					bach_freeptr(tempo);
				}
			}
		}
	}
    
    
    
    // handling markers
    t_timepoint dummy = build_timepoint_with_voice(-1, long2rat(0), -1);
    dada_iterate_on_markers(right_part, dada_score_crop_and_shift_markers_fn, k_NOTATION_OBJECT_SCORE, &temp, &dummy, NULL);
    dada_iterate_on_markers(gs, dada_score_crop_and_shift_markers_fn, k_NOTATION_OBJECT_SCORE, &dummy, &temp, NULL);

	
	return right_part;
}

t_tempo *dada_measure_get_last_tempo(t_llll *gs)
{
	if (gs && gs->l_head && hatom_gettype(&gs->l_head->l_hatom) == H_LLLL) {
		t_llll *measureinfo = hatom_getllll(&gs->l_head->l_hatom);
		if (measureinfo && measureinfo->l_head && measureinfo->l_head->l_next && hatom_gettype(&measureinfo->l_head->l_next->l_hatom) == H_LLLL) {
			t_llll *tempo_ll = hatom_getllll(&measureinfo->l_head->l_next->l_hatom);
			if (tempo_ll->l_depth == 1) { // single_tempo
				return build_tempo_from_llll(tempo_ll, DADA_DEFAULT_TEMPO_DIGITS);
			} else if (tempo_ll->l_depth > 1 && tempo_ll->l_tail && hatom_gettype(&tempo_ll->l_tail->l_hatom) == H_LLLL) {
				return build_tempo_from_llll(hatom_getllll(&tempo_ll->l_tail->l_hatom), DADA_DEFAULT_TEMPO_DIGITS);
			}
		}
	}
	return NULL;
}

t_tempo *dada_measure_get_first_tempo(t_llll *gs)
{
	if (gs && gs->l_head && hatom_gettype(&gs->l_head->l_hatom) == H_LLLL) {
		t_llll *measureinfo = hatom_getllll(&gs->l_head->l_hatom);
		if (measureinfo && measureinfo->l_head && measureinfo->l_head->l_next && hatom_gettype(&measureinfo->l_head->l_next->l_hatom) == H_LLLL) {
			t_llll *tempo_ll = hatom_getllll(&measureinfo->l_head->l_next->l_hatom);
			if (tempo_ll->l_depth == 1) { // single_tempo
				return build_tempo_from_llll(tempo_ll, DADA_DEFAULT_TEMPO_DIGITS);
			} else if (tempo_ll->l_depth > 1 && tempo_ll->l_head && hatom_gettype(&tempo_ll->l_tail->l_hatom) == H_LLLL) {
				return build_tempo_from_llll(hatom_getllll(&tempo_ll->l_head->l_hatom), DADA_DEFAULT_TEMPO_DIGITS);
			}
		}
	}
	return NULL;
}



// tempo is updated with last tempo, if any
void dada_measure_tempo_update_with_last_tempo(t_llll *gs, t_tempo **tempo)
{
	t_tempo *last_tempo = dada_measure_get_last_tempo(gs);
	if (last_tempo) {
		if (tempo && *tempo)
			bach_freeptr(*tempo);
		*tempo = last_tempo;
	}
}

void dada_measure_add_starting_tempo(t_llll *gs, t_tempo *tempo)
{
	if (tempo && gs && gs->l_head && hatom_gettype(&gs->l_head->l_hatom) == H_LLLL) {
		t_llll *measureinfo = hatom_getllll(&gs->l_head->l_hatom);
		if (measureinfo) {
			t_llll *tempo_ll = llll_get();
			
			llll_appendrat(tempo_ll, tempo->tempo_figure, 0, WHITENULL_llll);
			llll_appendrat(tempo_ll, tempo->figure_tempo_value, 0, WHITENULL_llll);
			
			if (!measureinfo->l_head) 
				llll_appendllll(measureinfo, llll_get(), 0, WHITENULL_llll);
			
			if (!measureinfo->l_head->l_next)
				llll_insertllll_after(tempo_ll, measureinfo->l_head, 0, WHITENULL_llll);
			else { 
				if (hatom_gettype(&measureinfo->l_head->l_next->l_hatom) == H_LLLL) {
					t_llll *existing_tempo_ll = hatom_getllll(&measureinfo->l_head->l_next->l_hatom);
					if (existing_tempo_ll->l_depth == 1) {
						if (existing_tempo_ll->l_size == 0) {
							llll_prependllll(existing_tempo_ll, tempo_ll, 0, WHITENULL_llll);
						} else if (existing_tempo_ll->l_size <= 2 || (is_hatom_number(&existing_tempo_ll->l_head->l_next->l_next->l_hatom) &&
																 hatom_getrational(&existing_tempo_ll->l_head->l_next->l_next->l_hatom).r_num == 0))
							llll_free(tempo_ll); // there's a tempo at the beginning
						else {
							llll_wrap_element_range(existing_tempo_ll->l_head, existing_tempo_ll->l_tail);
							llll_prependllll(existing_tempo_ll, tempo_ll, 0, WHITENULL_llll);
						}
					} else {
						// checking if there's a tempo at the beginning of the measure
						char theres_tempo_at_beginning_of_measure = false;
						if (existing_tempo_ll->l_head && hatom_gettype(&existing_tempo_ll->l_head->l_hatom) == H_LLLL) {
							t_llll *temp_ll = hatom_getllll(&existing_tempo_ll->l_head->l_hatom);
							if (temp_ll && temp_ll->l_size == 0) {
								// nothing to do
							} else if (temp_ll && (temp_ll->l_size <= 2 || (is_hatom_number(&temp_ll->l_head->l_next->l_next->l_hatom) &&
																	 hatom_getrational(&temp_ll->l_head->l_next->l_next->l_hatom).r_num == 0)))
								theres_tempo_at_beginning_of_measure = true;
						}
						
						if (!theres_tempo_at_beginning_of_measure)
							llll_prependllll(existing_tempo_ll, tempo_ll, 0, WHITENULL_llll);
					}
				} else 
					llll_free(tempo_ll);
			}
		}
	}
}

// gs becomes its left part, returns right part
// split_measure_num are 0-based, and indicates the measure to split
t_llll *dada_score_multisplit_measures(t_llll *gs, long num_splits, long *split_measure_num, char copy_tempi)
{
	t_llll **res = (t_llll **)bach_newptr((num_splits + 1) * sizeof(t_llll *));
    t_llll **mk = (t_llll **)bach_newptr((num_splits + 1) * sizeof(t_llll *));
	t_llll **res_voice = (t_llll **)bach_newptr((num_splits + 1) * sizeof(t_llll *));
	
	long i;
	for (i = 0; i <= num_splits; i++)
		res[i] = llll_get();
    
    // copying headers
    t_llll *header = get_header(gs, false);
    t_llll *markers = dada_get_markers(gs);
    
    if (header) {
        // removing markers element from header
        t_llllelem *el, *nextel;
        t_llll *tmp;
        for (el = header->l_head; el; el = nextel) {
            nextel = el->l_next;
            if (hatom_gettype(&el->l_hatom) == H_LLLL) {
                tmp = hatom_getllll(&el->l_hatom);
                if (tmp && tmp->l_head && hatom_gettype(&tmp->l_head->l_hatom) == H_SYM && hatom_getsym(&tmp->l_head->l_hatom) == _llllobj_sym_markers)
                    llll_destroyelem(el);
            }
        }
        
        for (i = 0; i <= num_splits; i++)
            llll_chain_clone(res[i], header);
        llll_free(header);
    }
    
    
    // handling markers
    for (i = 0; i <= num_splits; i++) {
        mk[i] = llll_get();
        llll_appendsym(mk[i], _llllobj_sym_markers);
    }
    long meas_num = 0;
    i = 0;
    for (t_llllelem *mkelem = markers->l_head; mkelem; mkelem = mkelem->l_next) {
        if (hatom_gettype(&mkelem->l_hatom) != H_LLLL)
            continue;
        t_llll *mk_ll = hatom_getllll(&mkelem->l_hatom);
        if (!mk_ll || !mk_ll->l_head)
            continue;
        
        if (hatom_gettype(&mk_ll->l_head->l_hatom) == H_LLLL) { // measure-attached marker
            t_llll *pos = hatom_getllll(&mk_ll->l_head->l_hatom);
            if (pos->l_size >= 3 && pos->l_depth == 1) {
                meas_num = hatom_getlong(&pos->l_head->l_next->l_hatom) - 1; // 0 - based

                while (meas_num >= split_measure_num[i])
                    i++;
                
                if (i > num_splits)
                    break;
                
                t_llll *newmk_ll = llll_clone(mk_ll);
                if (i > 0)
                    hatom_setlong(&newmk_ll->l_head->l_hatom.h_w.w_llll->l_head->l_next->l_hatom, meas_num - split_measure_num[i-1] + 1);
                llll_appendllll(mk[i], newmk_ll);
            }
        } else if (is_hatom_number(&mk_ll->l_head->l_hatom)) { // milliseconds-attached marker
            // we ignore it for now in multisplits
        }
    }
    // copying to header
    for (i = 0; i <= num_splits; i++)
        llll_appendllll(res[i], mk[i]);
    llll_free(markers);
    
    
    
	t_llllelem *voice, *meas;
	char must_add_tempo;
    for (voice = get_first_nonheader_elem(gs); voice; voice = voice->l_next) {
		if (hatom_gettype(&voice->l_hatom) != H_LLLL)
			continue;
		
		t_llll *voice_ll = hatom_getllll(&voice->l_hatom);
		t_tempo *tempo = NULL, *tempo_temp = NULL; // current tempo and temp variable
		
		// adding voices
		for (i = 0; i <= num_splits; i++) 
			res_voice[i] = llll_get();
		
		// retrieving voice flag if any
		long voice_flag = 0;
		if (hatom_gettype(&voice_ll->l_tail->l_hatom) == H_LONG)
			voice_flag = hatom_getlong(&voice_ll->l_tail->l_hatom);
		
		// distributing measures
		long meas_num = 0;
		i = 0;
		for (meas = voice_ll->l_head; meas; meas = meas->l_next, meas_num++) {
            if (hatom_gettype(&meas->l_hatom) != H_LLLL)
                continue;
            
			while (meas_num >= split_measure_num[i]) {
				i++;
				must_add_tempo = (copy_tempi && (tempo != NULL));
			}
			
			if (i > num_splits)
				break;
			
			t_llllelem *newmeas = llll_appendhatom_clone(res_voice[i], &meas->l_hatom);
			
			if (hatom_gettype(&newmeas->l_hatom) == H_LLLL) {
				t_llll *meas_ll = hatom_getllll(&newmeas->l_hatom);
				
				// updating tempo
				dada_measure_tempo_update_with_last_tempo(meas_ll, &tempo_temp);

				// copying previous tempo
				if (copy_tempi && must_add_tempo)
					dada_measure_add_starting_tempo(meas_ll, tempo);

				tempo = tempo_temp;
			}
		}
			
		for (i = 0; i <= num_splits; i++) {
			llll_appendlong(res_voice[i], voice_flag);
			llll_appendllll(res[i], res_voice[i]);
		}

         bach_freeptr(tempo_temp);
	}
	
	t_llll *res_all = llll_get();
	for (i = 0; i <= num_splits; i++) {
		llll_prependsym(res[i], _llllobj_sym_score);
		llll_appendllll(res_all, res[i]);
	}

    
	bach_freeptr(res);
	bach_freeptr(res_voice);
	
	return res_all;
}



long dada_score_getnummeas(t_llll *gs)
{
	t_llllelem *voice, *meas;
	long num_meas = 0;
	for (voice = get_first_nonheader_elem(gs); voice; voice = voice->l_next) {
		long this_num_meas = 0;
		if (hatom_gettype(&voice->l_hatom) != H_LLLL)
			continue;
		
		t_llll *voice_ll = hatom_getllll(&voice->l_hatom);
		for (meas = voice_ll->l_head; meas; meas = meas->l_next) {
			if (hatom_gettype(&meas->l_hatom) != H_LLLL)
				continue;
			this_num_meas++;
		}
		
		if (this_num_meas > num_meas)
			num_meas = this_num_meas;
	}
	return num_meas;
}

t_rational dada_measure_getsymdur(t_llll *gs)
{
	if (gs->l_head && hatom_gettype(&gs->l_head->l_hatom) == H_LLLL) {
		t_llll *measureinfo_ll = hatom_getllll(&gs->l_head->l_hatom);
		if (measureinfo_ll->l_head && hatom_gettype(&measureinfo_ll->l_head->l_hatom) == H_LLLL) { 
			t_llll *timesig = hatom_getllll(&measureinfo_ll->l_head->l_hatom);
			t_timesignature ts = get_timesignature_from_llll(NULL, timesig);
			return genrat(ts.numerator, ts.denominator);
		}
	}
	return long2rat(0);
}


t_rational dada_score_gettotsymduration(t_llll *gs)
{
    t_llllelem *voice, *meas;
    t_rational totsymdur = long2rat(0);
    for (voice = get_first_nonheader_elem(gs); voice; voice = voice->l_next) {
        t_rational this_totsymdur = long2rat(0);
        if (hatom_gettype(&voice->l_hatom) != H_LLLL)
            continue;
        
        t_llll *voice_ll = hatom_getllll(&voice->l_hatom);
        for (meas = voice_ll->l_head; meas; meas = meas->l_next) {
            if (hatom_gettype(&meas->l_hatom) != H_LLLL)
                continue;
            
            this_totsymdur = rat_rat_sum(this_totsymdur, dada_measure_getsymdur(hatom_getllll(&meas->l_hatom)));
        }
        
        if (rat_rat_cmp(this_totsymdur, totsymdur) == 1)
            totsymdur = this_totsymdur;
    }
    return totsymdur;
}


long dada_score_measure_convert_to_ts_fn(t_llll *gs, e_notation_objects notation_obj, void *idx, void *onset, void *dummy, void *dummy2, void *dummy3)
{
	if (gs->l_head && hatom_gettype(&gs->l_head->l_hatom) == H_LLLL) {
		t_llll *measureinfo_ll = hatom_getllll(&gs->l_head->l_hatom);
		if (measureinfo_ll->l_head && hatom_gettype(&measureinfo_ll->l_head->l_hatom) == H_LLLL) { 
			t_llll *timesig = hatom_getllll(&measureinfo_ll->l_head->l_hatom);
			t_timesignature *ts = (t_timesignature *)bach_newptr(sizeof(t_timesignature)); 
			*ts = get_timesignature_from_llll(NULL, timesig);
			hatom_change_to_obj_and_free(&gs->l_owner->l_hatom, ts);
			return 0;
		}
	}
	
	return 1;
}



//obtain llll with t_timesignature structures
t_llll *dada_score_getts(t_llll *gs)
{
	t_llll *ts = get_body(gs);
	dada_score_iterate_on_measures(ts, dada_score_measure_convert_to_ts_fn, k_NOTATION_OBJECT_SCORE, NULL, NULL, NULL);

	return ts;
}




long dada_score_measure_convert_to_divisions_fn(t_llll *gs, e_notation_objects notation_obj, void *idx, void *onset, void *dummy, void *dummy2, void *dummy3)
{
	if (gs->l_head && hatom_gettype(&gs->l_head->l_hatom) == H_LLLL) {
		t_llll *measureinfo_ll = hatom_getllll(&gs->l_head->l_hatom);
		if (measureinfo_ll->l_head && hatom_gettype(&measureinfo_ll->l_head->l_hatom) == H_LLLL) { 
			t_llll *timesig = hatom_getllll(&measureinfo_ll->l_head->l_hatom);
			t_timesignature ts = get_timesignature_from_llll(NULL, timesig);
			t_llll *divs = ts_to_beaming_boxes(NULL, &ts, NULL, NULL);
			hatom_change_to_llll_and_free(&gs->l_owner->l_hatom, divs);
			return 0;
		}
	}
	
	return 1;
}

//obtain llll with t_timesignature structures
t_llll *dada_score_getdivisions(t_llll *gs)
{
    t_llll *ts = get_body(gs);
	dada_score_iterate_on_measures(ts, dada_score_measure_convert_to_divisions_fn, k_NOTATION_OBJECT_SCORE, NULL, NULL, NULL);
	
	return ts;
}



t_tempo *dada_score_get_first_tempo(t_llll *gs)
{
	t_llllelem *voice_elem, *meas_elem;
	for (voice_elem = get_first_nonheader_elem(gs); voice_elem; voice_elem = voice_elem->l_next) {
		if (hatom_gettype(&voice_elem->l_hatom) != H_LLLL)
			continue;
		for (meas_elem = hatom_getllll(&voice_elem->l_hatom)->l_head; meas_elem; meas_elem = meas_elem->l_next) {
			if (hatom_gettype(&meas_elem->l_hatom) != H_LLLL)
				continue;
			t_tempo *tp = dada_measure_get_first_tempo(hatom_getllll(&meas_elem->l_hatom));
			if (tp)
				return tp;
		}
	}
	return NULL;
}


t_tempo *dada_score_get_last_tempo(t_llll *gs)
{
	t_llllelem *voice_elem, *meas_elem;
	for (voice_elem = get_first_nonheader_elem(gs); voice_elem; voice_elem = voice_elem->l_next) {
		if (hatom_gettype(&voice_elem->l_hatom) != H_LLLL)
			continue;
		for (meas_elem = hatom_getllll(&voice_elem->l_hatom)->l_tail; meas_elem; meas_elem = meas_elem->l_prev) {
			if (hatom_gettype(&meas_elem->l_hatom) != H_LLLL)
				continue;
			t_tempo *tp = dada_measure_get_first_tempo(hatom_getllll(&meas_elem->l_hatom));
			if (tp)
				return tp;
		}
	}
	return NULL;
}


long dada_roll_get_max_num_notes_fn(t_llll *gs, e_notation_objects notation_obj, void *idx, void *onset, void *num_notes, void *dummy2, void *dummy3)
{
	t_llllelem *elem;
	long this_count = 0;
	for (elem = gs->l_head; elem; elem = elem->l_next) {
		if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
			t_llll *ll = hatom_getllll(&elem->l_hatom);
			if (ll && ll->l_head && hatom_gettype(&ll->l_head->l_hatom) != H_SYM)
				this_count++;
		}
	}
	if (this_count > *((long *)num_notes))
		*((long *)num_notes) = this_count;
	return 1;
}


long dada_roll_get_max_num_notes_per_chord(t_llll *gs)
{
	long num = 0;
	dada_roll_iterate_on_chords(gs, (dada_gs_modif_fn)dada_roll_get_max_num_notes_fn, k_NOTATION_OBJECT_ROLL, &num, NULL, NULL);
	return num;
}

long dada_roll_get_num_chords_fn(t_llll *gs, e_notation_objects notation_obj, void *idx, void *onset, void *count, void *dummy2, void *dummy3)
{
    (*((long *)count))++;
    return 0;
}


long dada_roll_get_num_chords(t_llll *gs)
{
    long count = 0;
    dada_roll_iterate_on_chords(gs, (dada_gs_modif_fn)dada_roll_get_num_chords_fn, k_NOTATION_OBJECT_ROLL, &count, NULL, NULL);
    return count;
}

void dada_roll_collapse(t_llll *gs, char collapse_voices, t_llll **voice_flags, char collapse_chords, t_llll **chord_flags, char mark_lthings)
{
	if (voice_flags)
		*voice_flags = llll_get();
	
	if (chord_flags)
		*chord_flags = llll_get();
	
	// 1. MARKING LLLLS CHORDS 
	t_llllelem *voice, *chord, *next_chord;
	long voice_num = 0;
	for (voice = get_first_nonheader_elem(gs); voice; voice = voice->l_next, voice_num++) {
		if (hatom_gettype(&voice->l_hatom) != H_LLLL)
			continue;
		
		t_llll *voice_ll = hatom_getllll(&voice->l_hatom);
		t_llll *this_voice_chord_flags = NULL;
		
		if (chord_flags)
			this_voice_chord_flags = llll_get();

		// retrieving voice flag
		if (voice_flags && hatom_gettype(&voice_ll->l_tail->l_hatom) != H_LLLL)
			llll_appendhatom_clone(*voice_flags, &voice_ll->l_tail->l_hatom, 0, WHITENULL_llll);
		
		long chord_num = 0;
		for (chord = voice_ll->l_head; chord; chord = next_chord, chord_num++) {
			next_chord = chord->l_next;
			if (hatom_gettype(&chord->l_hatom) != H_LLLL) {
				llll_destroyelem(chord);
				continue;
			}
			
			t_llll *chord_ll = hatom_getllll(&chord->l_hatom);
			if (collapse_chords) {

				t_llllelem *note, *next_note;

				t_llll *this_chord_info = llll_get();
				if (chord_ll->l_head && is_hatom_number(&chord_ll->l_head->l_hatom)) {
					double chord_onset = hatom_getdouble(&chord_ll->l_head->l_hatom);
					
					// retrieving chord flag, and names
					for (note = chord_ll->l_head->l_next; note; note = next_note) {
						next_note = note->l_next;
						if (hatom_gettype(&note->l_hatom) != H_LLLL) {
							llll_appendhatom_clone(this_chord_info, &note->l_hatom, 0, WHITENULL_llll);
							llll_destroyelem(note);
						} else {
							t_llll *thisll = hatom_getllll(&note->l_hatom);
							if (thisll->l_head && hatom_gettype(&thisll->l_head->l_hatom) == H_SYM) {
								llll_appendhatom_clone(this_chord_info, &note->l_hatom, 0, WHITENULL_llll);
								llll_destroyelem(note);
							}
						}
					}
					
					if (chord_flags) 
						llll_appendllll(this_voice_chord_flags, this_chord_info, 0, WHITENULL_llll);
					else 
						llll_free(this_chord_info);
					
					long note_num = 0;
					t_llllelem *next_note;
					for (note = chord_ll->l_head; note; note = next_note) {
						next_note = note->l_next;

						if (hatom_gettype(&note->l_hatom) == H_LLLL) {
							t_llll *note_ll = hatom_getllll(&note->l_hatom);
							if (mark_lthings){
								t_dada_score_path *path = (t_dada_score_path *)bach_newptrclear(sizeof(t_dada_score_path));
								path->voice_num = voice_num;
								path->chord_idx = chord_num;
								path->note_idx = note_num;
								note_ll->l_thing.w_obj = path;
							}
							llll_prependdouble(note_ll, chord_onset, 0, WHITENULL_llll);
							llll_wrap_element_range(note_ll->l_head->l_next, note_ll->l_tail);
							note_num++;
						} else 
							llll_destroyelem(note);
					}
				}
				
			} else {
				if (mark_lthings){
					t_dada_score_path *path = (t_dada_score_path *)bach_newptrclear(sizeof(t_dada_score_path));
					path->voice_num = voice_num;
					path->chord_idx = chord_num;
					chord_ll->l_thing.w_obj = path;
				}
			}
		}
		
		if (chord_flags)
			llll_appendllll(*chord_flags, this_voice_chord_flags, 0, WHITENULL_llll);
	}

//	post("chord flags:");
//	if (chord_flags)
//		llll_print(*chord_flags, NULL, 0, BACH_DEFAULT_MAXDECIMALS, NULL);
//	llll_print(gs, NULL, 0, BACH_DEFAULT_MAXDECIMALS, NULL);
	
	// 2. FLATTENING, SORTING and REWRAPPING
	llll_flat(gs, collapse_voices ? 1 : 2, collapse_chords ? 2 : 1, 0, LLLL_FREETHING_MEM);
	llll_inplacesort(gs, (sort_fn)llll_sort_by_first);
	if (collapse_voices)
		llll_wrap_element_range(gs->l_head, gs->l_tail);

//	llll_print(gs, NULL, 0, BACH_DEFAULT_MAXDECIMALS, NULL);
}


void dada_roll_free_path_in_lthings(t_llll *gs)
{
	t_llllelem *elem, *voice;
	for (voice = get_first_nonheader_elem(gs); voice; voice = voice->l_next) {
		if (hatom_gettype(&voice->l_hatom) != H_LLLL)
			continue;
		t_llll *voice_ll = hatom_getllll(&voice->l_hatom);
		for (elem = voice_ll->l_head; elem; elem = elem->l_next) {
			t_llll *ll = hatom_getllll(&elem->l_hatom);
			if (ll->l_thing.w_obj)
				bach_freeptr(ll->l_thing.w_obj);
			ll->l_thing.w_obj = NULL;
		}
	}
}

// gs must be FLATTENED: i.e. without voice level.
void dada_roll_uncollapse(t_llll *gs, t_llll *voice_flags, char also_uncollapse_chords, t_llll *chord_flags,
						  char remove_empty_chords)
{
	t_llllelem *voice, *nextvoice; // expected to be a single one!
	
	/// 1. GET MAX VOICE NUMBER
	long num_voices = voice_flags->l_size;
	t_llllelem *elem, *note;
	long i;
	for (elem = get_first_nonheader_elem(gs); elem; elem = elem->l_next) {
		if (hatom_gettype(&elem->l_hatom) != H_LLLL)
			continue;
		t_llll *ll = hatom_getllll(&elem->l_hatom);
		if (ll && ll->l_thing.w_obj) {
			t_dada_score_path *path = (t_dada_score_path *)ll->l_thing.w_obj;
			long this_voice_num = path->voice_num;
			if (this_voice_num > num_voices)
				num_voices = this_voice_num;
		}
	}
	
	t_llll *out_voices = llll_get();
	t_llll *voice_ll[num_voices];
	for (i = 0; i < num_voices; i++) {
		voice_ll[i] = llll_get();
		llll_appendllll(out_voices, voice_ll[i], 0, WHITENULL_llll);
	}
	
	// 2. REASSIGNING CHORDS
	if (also_uncollapse_chords) {
		for (note = get_first_nonheader_elem(gs); note; note = note->l_next) {
			if (hatom_gettype(&note->l_hatom) != H_LLLL) 
				continue;
			t_llll *note_ll = hatom_getllll(&note->l_hatom);
			t_dada_score_path *path = (t_dada_score_path *)note_ll->l_thing.w_obj;
			long this_voice_num = path->voice_num;
			long this_chord_num = path->chord_idx;
			
//			post("note-ll");
//			llll_print(note_ll, NULL, 0, BACH_DEFAULT_MAXDECIMALS, NULL);
			
			while ((long)voice_ll[this_voice_num]->l_size < this_chord_num + 1)
				llll_appendllll(voice_ll[this_voice_num], llll_get(), 0, WHITENULL_llll);
			
			t_llllelem *chord_llelem = llll_getindex(voice_ll[this_voice_num], this_chord_num + 1, I_STANDARD);
			if (chord_llelem && hatom_gettype(&chord_llelem->l_hatom) == H_LLLL && note_ll->l_head && note_ll->l_head->l_next && 
				is_hatom_number(&note_ll->l_head->l_hatom) && hatom_gettype(&note_ll->l_head->l_next->l_hatom) == H_LLLL) {
				
				t_llll *chord_ll = hatom_getllll(&chord_llelem->l_hatom);
				if (chord_ll->l_size == 0) 
					llll_appenddouble(chord_ll, hatom_getdouble(&note_ll->l_head->l_hatom), 0, WHITENULL_llll);
				
				llll_appendllll_clone(chord_ll, hatom_getllll(&note_ll->l_head->l_next->l_hatom), 0, WHITENULL_llll, NULL);
			}
		}
		
		if (remove_empty_chords) {
			for (i = 0; i < num_voices; i++) {
				t_llllelem *chord_llelem, *next_chord_llelem;
				for (chord_llelem = voice_ll[i]->l_head; chord_llelem; chord_llelem = next_chord_llelem) {
					next_chord_llelem = chord_llelem->l_next;
					if (hatom_gettype(&chord_llelem->l_hatom) == H_LLLL && hatom_getllll(&chord_llelem->l_hatom)->l_size == 0)
						llll_destroyelem(chord_llelem);
				}
			}
		}
		
	} else {
		t_llllelem *chord_llelem;
		for (chord_llelem = get_first_nonheader_elem(gs); chord_llelem; chord_llelem = chord_llelem->l_next) {
			if (hatom_gettype(&chord_llelem->l_hatom) != H_LLLL) 
				continue;
			
			t_llll *chord_ll = hatom_getllll(&chord_llelem->l_hatom);
			t_dada_score_path *path = (t_dada_score_path *)chord_ll->l_thing.w_obj;
			long this_voice_num = path->voice_num;
			if (this_voice_num >= 0 && this_voice_num < num_voices)
				llll_appendllll_clone(voice_ll[this_voice_num], chord_ll, 0, WHITENULL_llll, NULL);
		}
	}
	
	if (also_uncollapse_chords && chord_flags) {
		// Appending chord_flags
		t_llllelem *chord_flag_voice_elem;
		for (chord_flag_voice_elem = chord_flags->l_head, i = 0; chord_flag_voice_elem && i < num_voices; i++, chord_flag_voice_elem = chord_flag_voice_elem->l_next) {
			if (hatom_gettype(&chord_flag_voice_elem->l_hatom) == H_LLLL) {
				t_llllelem *chord_flag_elem;
				t_llllelem *copied_elem;
				t_llll *chord_flags_ll = hatom_getllll(&chord_flag_voice_elem->l_hatom);
				for (chord_flag_elem = chord_flags_ll->l_head, copied_elem = voice_ll[i]->l_head; chord_flag_elem && copied_elem; chord_flag_elem = chord_flag_elem->l_next, copied_elem = copied_elem->l_next) {
					if (hatom_gettype(&copied_elem->l_hatom) == H_LLLL && hatom_gettype(&chord_flag_elem->l_hatom) == H_LLLL)
						llll_chain_clone(hatom_getllll(&copied_elem->l_hatom), hatom_getllll(&chord_flag_elem->l_hatom));
				}
			}
		}
	}

	
	// Appending voice_flags
	t_llllelem *voice_flag_elem;
	for (voice_flag_elem = voice_flags->l_head, i = 0; voice_flag_elem && i < num_voices; voice_flag_elem = voice_flag_elem->l_next, i++) 
		llll_appendhatom_clone(voice_ll[i], &voice_flag_elem->l_hatom, 0, WHITENULL_llll);
	
	// Destroying old gs content
	voice = get_first_nonheader_elem(gs);
	while (voice) {
		nextvoice = voice->l_next;
		llll_destroyelem(voice);
		voice = nextvoice;
	}
	
	// Chaining new content
	llll_chain(gs, out_voices);
}

/*


long dada_score_get_labels_fn(t_llll *gs, e_notation_objects notation_obj, void *idx, void *onset, void *labels, void *dummy2, void *dummy3)
{
	t_llllelem *el = NULL, *l_el = NULL;
	t_llll *labels_ll = (t_llll *)labels;
	for (el = gs->l_head; el; el = el->l_next) {
		t_llll *ll = NULL;
		if (hatom_gettype(&el->l_hatom) == H_LLLL && (ll = hatom_getllll(&el->l_hatom)) && ll->l_head && 
			hatom_gettype(&ll->l_head->l_hatom) == H_SYM && hatom_getsym(&ll->l_head->l_hatom) == _llllobj_sym_name) {
			t_llll *this_label = llll_clone(ll);
			llll_behead(this_label);
			
			t_llllelem *single_label;
			for (single_label = this_label->l_head; single_label; single_label = single_label->l_next) {
				t_llll *single_label_ll = llll_get();
				llll_appendhatom_clone(single_label_ll, &single_label->l_hatom, 0, WHITENULL_llll);
				
				// check if already present
				char found = 0;
				for (l_el = labels_ll->l_head; l_el; l_el = l_el->l_next) {
					t_llll *l_ll = hatom_getllll(&l_el->l_hatom);
					t_llll *l_ll_label = hatom_getllll(&l_ll->l_head->l_hatom);
					
					if (llll_eq_ignoretype(l_ll_label, single_label_ll)) {
						long count = hatom_getlong(&l_ll->l_head->l_next->l_hatom);
						hatom_setlong(&l_ll->l_head->l_next->l_hatom, count+1);
						found = 1;
						break;
					}
				}
				
				if (!found) {
					t_llll *l_ll = llll_get();
					llll_appendllll(l_ll, single_label_ll, 0, WHITENULL_llll); // label
					llll_appendlong(l_ll, 1, 0, WHITENULL_llll); // count
					llll_appendllll(labels_ll, l_ll, 0, WHITENULL_llll);
				} else {
					llll_free(single_label_ll);
				}
			}
			
			llll_free(this_label);
		}
	}
	
	return 0;
}


// gs = gathered syntax
t_llll *dada_score_get_labels(t_llll *gs)
{
	t_llll *labels = llll_get();
	dada_score_iterate_on_measures(gs, (dada_gs_modif_fn)dada_score_get_labels_fn, k_NOTATION_OBJECT_SCORE, labels, NULL, NULL);
	return labels;
}

*/
