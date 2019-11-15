/**
	@file	notation_spectral.h 
	@brief	Spectral tools for notation objects
	
	by Daniele Ghisi
*/

#ifndef _NOTATION_SPECTRAL_H_
#define _NOTATION_SPECTRAL_H_

#include "math/spectral.h" // header with all the structures for the notation objects


#define	CONST_PTRACK_MIN_POINT_RADIUS	2
#define	CONST_PTRACK_MAX_POINT_RADIUS	5
#define CONST_USE_COSINE_IN_WAVE_MODEL	true
#define CONST_HARMONIC_TRANSIENT_CAN_MASK			true
#define CONST_HARMONIC_TRANSIENT_CAN_BE_MASKED		true

#define CONST_THRESHOLD_MS_EQUAL_PERIODS_FOR_MASKING 20

#ifndef DOXYGEN_SHOULD_SKIP_THIS
BEGIN_CHECK_LINKAGE
#endif


/** Flags telling if a peak inside a partial tracking pattern starts/ends/continues a voice.
	@ingroup	spectral
 */
typedef enum _ptrack_status {
	k_PARTIAL_TRACKING_VOICE_NO = 0,
	k_PARTIAL_TRACKING_VOICE_STARTS = 1,	///< A voice is starting
	k_PARTIAL_TRACKING_VOICE_ENDS = 2,		///< A voice is ending
	k_PARTIAL_TRACKING_VOICE_CONTINUE = 4,	///< A voice is continuing
} e_ptrack_status;


/** Flags describing the type of change occurred during a time signature detection.
	@ingroup	spectral
 */
typedef enum _tsd_adapt_type {
	k_TSD_ADAPT_TYPE_NONE = 0,					///< No change has been done
	k_TSD_ADAPT_TYPE_DIV_TO_SUBDIV = 1,			///< Divisions have become subdivisions, and measures have become divisions
	k_TSD_ADAPT_TYPE_SUBDIV_TO_DIV = 2,			///< Subdivisions have become divisions, and divisions have become measures
	k_TSD_ADAPT_TYPE_STANDARDIZED_DIV = 4,		///< Divisions have been standardized
	k_TSD_ADAPT_TYPE_STANDARDIZED_SUBDIV = 8,	///< Subdivisions have been standardized
} e_tsd_adapt_type;


#define	CONST_MULTIPHASE_NUM_PHASE_BINS	72

// UNUSED; UNDOCUMENTED
typedef struct _multiphase_bin
{
	double	ampli[CONST_MULTIPHASE_NUM_PHASE_BINS];
	double	phase[CONST_MULTIPHASE_NUM_PHASE_BINS];
} t_multiphase_bin;


// UNUSED; UNDOCUMENTED
typedef struct _multiphase_spectrogram
{
	long				num_samples;
	long				num_bins;
	t_multiphase_bin	**bins; //it'll be sized bins[num_samples][num_bins]
} t_multiphase_spectrogram;


/** Structure representing a peak in a frequency spectrum
	@ingroup	spectral
 */ 
typedef struct _spectral_peak
{
	double	freq;		///< Central frequency of the peak;
	double	amplitude;	///< Amplitude of the peak
	double	phase;		///< Phase of the peak
	double	width;		///< Width of the peak in hertz
	
	long	frame_number;	///< ID of the frame (0-based)
	double	frame_ms;		///< Temporal position (in ms) of the frame start
	
	// ptrack stuff
	struct _ptrack_voice	*ptrack_parent;		///< If inside a partial tracking voice, this is the structure corresponding to the voice.
	struct _spectral_peak	*ptrack_next;		///< Pointer to the next peak, if inside a partial-tracking pattern
	struct _spectral_peak	*ptrack_prev;		///< Pointer to the previous peak, if inside a partial-tracking pattern
	e_ptrack_status			ptrack_status;		///< Status of the point: does it start/end/continue a voice? (UNUSED)

	// time signature detection stuff
	struct _tsd_frame	*tsdetect_parent;	///< If inside a time signature detection algorithm, this is the structure corresponding to the partial tracking voice.
	struct _spectral_peak	*tsdetect_next;		///< Pointer to the next peak, if inside a time signature detection
	struct _spectral_peak	*tsdetect_prev;		///< Pointer to the previous peak, if inside a time signature detection

	// internal flags
	e_ptrack_status			done;		///< (Private) Flag telling if we have already inserted the peak in some #t_ptrack_voice during a partial tracking process
} t_spectral_peak;



/** Structure representing a voice in a partial tracking pattern
	@ingroup	spectral
 */ 
typedef struct _ptrack_voice
{
	long			ID;				///< Voice ID (1-based)
	t_spectral_peak *first_peak;	///< First peak of the voice
	t_spectral_peak *last_peak;		///< Last peak of the voice
	long			num_peaks;		///< Number of peaks in the voice
	
	// internal flags
	char			is_active;		///< (Private) Flag telling if at a given moment the voice is active

	// double linked list
	struct _ptrack_voice	*prev;	///< Pointer to previous partial track voice
	struct _ptrack_voice	*next;	///< Pointer to next partial track voice
} t_ptrack_voice;



/** Structure representing a division/subdivision pattern for a time signature.
	For instance, a time signature of 6/8 will have div = 3, subdiv = 2.
	@ingroup	spectral
 */ 
typedef struct _div_subdiv
{
	long	div;		///< division ratio
	long	subdiv;		///< subdivision ratio
} t_div_subdiv;


/** Structure representing the phase set of a point inside a measure, namely the
	phases with respect to subdivision, division and measure itself. All goes from 0 to 1.
	@ingroup	spectral
 */ 
typedef struct _phase_set
{
	double	phase_subdiv;		///< Phase (0 to 1) with respect to subdivision
	double	phase_div;			///< Phase (0 to 1) with respect to division
	double	phase_measure;		///< Phase (0 to 1) with respect to measure
} t_phase_set;


/** Structure representing a changes done in the division/subdivision ratios
	@ingroup	spectral
 */
typedef struct _tsd_adaptation
{
	e_tsd_adapt_type	type;			///< Type of the change
	t_rational			old_new_div_ratio;
	t_rational			old_new_subdiv_ratio;
} t_tsd_adaptation;


/** Structure representing a configuration solution, or a segment-configuration solution
	@ingroup	spectral
 */ 
typedef struct _tsd_config
{
	long				ID;				///< Index of the configuration
	
	t_div_subdiv		detected_ratios;	///< Detected ratios of the configuration
	t_div_subdiv		ratios;				///< (Possibly user-modified) ratios of the configuration
	double				weight;			///< Probability weight of the configuration
	t_phase_set			phase;			///< Phase configuration of the point inside the measure (with respect to subdivisions, divisions and measure itself)
	long				voice_nums[3];	///< Voice numbers of the 3 chosen peaks building the configuration
	double				tempo_div;		///< Tempo referred to the measure division
	
	struct	_tsd_frame	*parent;		///< Parent frame
	
	// deduced by the ratios and settings
	t_timesignature		ts;				///< Time signature
	t_rational			tempo_figure;	///< Division figure = tempo figure
	
	// used by segment-wise-configurations
	double				*ist_meas_phases;		///< Istantaneous phase (0. to 1.) of the measure cycle (one for each detected frame)
	double				*ist_div_phases;		///< Istantaneous phase (0. to 1.)  of the division cycle (one for each detected frame)
	double				*ist_subdiv_phases;		///< Istantaneous phase (0. to 1.) of the subdivision cycle (one for each detected frame)
	double				cycles_bpm[3];			///< BPM of the measure cycle, division cycle and subdivision cycle
	t_tsd_adaptation	adapt;					///< Adaptation needed (because tempo was too small or too high)

	long				detected_start_fr;	///< Segment detected starting frame, 1-based
	long				detected_end_fr;	///< Segment detected ending frame, 1-based
	
	// user settable/modifiable stuff for segment-configurations
	long				start_fr;			///< Segment starting frame (possibly clipped or extended by the user), 1-based 
	long				end_fr;				///< Segment ending frame (possibly clipped or extended by the user), 1-based
	long				force_barline_rot;	///< Force the rotation of the barline by a certain number of steps (0 = ordinary, 1 = measure barlines will correspond to former first division, 2 = ...)
	long				force_div_rot;		///< Force the rotation of the divisions by a certain number of steps (0 = ordinary, 1 = division barlines will correspond to former first division, 2 = ...)
	long				force_add_div;		///< Force the number of division to be augmented by a certain amount

	// onsets
	t_llll				*detected_onsets_ms; ///< Detected onsets within the frame range (detected_start_fr, detected_end_fr) 
	t_llll				*onsets_ms;			 ///< Possibly clipped or extended onsets within the frame range (start_fr, end_fr)
	double				detected_onsets_std_dev_ms; ///< Standard deviation of the detected onsets (in milliseconds)
	double				detected_onsets_std_dev_rel; ///< Relative standard deviation of the detected onsets (standard deviation divided by the average).

	// painting stuff
	long				painting_line; /// (Private): The 1-based index of the line on which the configuration will be painted
	t_rect				painting_rect; /// (Private): Graphical rectangle (pixels) for painting the configuration

	
	struct _tsd_config	*next;	///< Pointer to next configuration
	struct _tsd_config	*prev;	///< Pointer to previous configuration
} t_tsd_config;


/** Structure representing a frame in a time signature detection
	@ingroup	spectral
 */ 
typedef struct _tsd_frame
{
	long				frame_num;			///< Frame number
	
	t_spectral_peak		*first_peak;		///< First peak inside the frame
	t_spectral_peak		*last_peak;			///< Last peak inside the frame
	long				num_peaks;			///< Number of peaks
	
	t_tsd_config			*first_tsd_config;	///< First guessed possibility for the time signature configuration in the frame
	t_tsd_config			*last_tsd_config;	///< Last guessed possibility for the time signature configuration in the frame
	long				num_tsd_configs;		///< Number of possibilities
	
	struct _tsd_frame	*next;		///< Pointer to next tsd_frame
	struct _tsd_frame	*prev;		///< Pointer to previous tsd_frame
} t_tsd_frame;



/** Structure representing a segment of time signature detection
	@ingroup	spectral
 */ 
typedef struct _tsd_segment
{
	long				start_frame;	///< Start frame for the segment
	long				end_frame;		///< End frame for the segment
	double				weight;
	
	t_tsd_config		global_config;	///< Global configuration

	long				num_configs;	///< Number of configurations composing the segment
	t_tsd_config		**configs;		///< Array of configurations (will have #num_configs element of type (t_tsd_config *)
	
	struct _tsd_frame	*next;		///< Pointer to next tsd_frame
	struct _tsd_frame	*prev;		///< Pointer to previous tsd_frame
} t_tsd_segment;



// -----------------------------------
// SYMBOLIC SPECTRAL ANALYSIS
// -----------------------------------

t_llll *cut_window_from_rhythm(t_llll *chords_in_gathered_syntax, double win_start_ms, double win_end_ms);	
void get_spectral_rhythm_config_in_window(double win_start_ms, double win_end_ms, t_llll *chords_in_gathered_syntax, 
										  char is_chord_onset_relative_to_window, char is_single_frame, e_win_types window_type, double velocity_handling_slope, 
										  double voice_coupling, double outer_mc_threshold, double inner_mc_threshold, char normalize, char show_phase,
										  t_llll **separate_peaks,
										  double *sampled_amplitudes, double *sampled_phase, long num_sampling_points, double min_bpm, double max_bpm, double decay_bpm,
										  double min_singleampli_threshold, double min_globalampli_threshold, e_shape_types shape_of_contributions, char filter_subharmonics);
void take_amplitude_into_account(double bpm, double ampli, char consider_phase, double phase, double *sampled_amplitudes, double *sampled_phases, long num_sampling_points, 
								 double min_bpm, double max_bpm, double decay_bpm, double *weight_of_index_i, e_shape_types shape_of_contributions, char check_nonnegative_ampli);

void gathered_syntax_to_onset_function(t_llll *chords_in_gathered_syntax, long num_sampling_points, double sampling_step, double *onsetf, e_shape_types shape_of_contributions, double peak_spreading);


void gathered_syntax_to_onset_wave(t_llll *chords_in_gathered_syntax, 
									double *wave, long num_sampling_points, double sampling_freq, 
									double decay_time, double voice_coupling, long note_neighborhood_to_consider,
									double outer_onset_threshold, double inner_onset_threshold, double onset_decay_slope,
									double outer_mc_threshold, double inner_mc_threshold,
									char also_normalize, char use_cosine, char use_masking_detection, double non_sequential_events_multiplier,
									t_multiphase_spectrogram *mph, long num_fft_bins, double waveshaping_exponent, double harmonic_changes_contribution,
									t_llll **debug, double harm_changes_winsize, double harm_changes_hopsize, 
									char snap_detected_harmonic_changes_to_nearest_onset, double harmonic_changes_median_filtering_window,
									double delete_softer_harmonic_changes_inside_win_ms, 
									double gain_multiplier_for_maxima, double gain_multiplier_for_minima, double extend_masking_ms, 
									char extend_masking_components_over_masked_ones,
									double debug_clip_min_bpm, double debug_clip_max_bpm);

void cluster_averaging(t_llll **chords_in_gathered_syntax, double thresh_ms);
void free_multiphase_spectrogram(t_multiphase_spectrogram *mph);

t_llll *get_peaks(t_llll *spectral_data, char amps_only, char return_bpm,
					long numpeaks, double minpeakamp, double minpeakrelamp, double sampling_frequency, long num_sampling_vals);

void partial_tracking(long num_frames, long *num_peaks, t_spectral_peak ***peaks, double frame_hop_ms,
						long max_num_ptrack_voices, double min_amp_for_a_voice_to_start, double min_amp_for_a_voice_to_continue, char min_amps_are_relative,
						double max_freq_ratio_for_a_voice_to_continue, double max_phase_error_for_a_voice_to_continue,
						double attack_time, double release_time, double lowcut_freq, long *num_ptrack_voices, t_ptrack_voice **first_pt_voice, t_ptrack_voice **last_pt_voice);

double get_averaged_phase_at_frame(t_ptrack_voice *ptv, long frame_num, double frame_hop_size); // NOT averaged: interpolated!
double get_averaged_freq_at_frame(t_ptrack_voice *ptv, long frame_num, double frame_hop_size); // NOT averaged: interpolated!
void get_ptrack_voices_superposition_range(t_ptrack_voice *pt1, t_ptrack_voice *pt2, t_ptrack_voice *pt3, long *start_frame, long *end_frame);
void get_ptrack_voice_average_frequence_and_ampli(t_ptrack_voice *ptv, double *freq, double *amp);
void append_peak_to_tsd_frame(t_tsd_frame *frame, t_spectral_peak *peak);

double freq_ratio(double freq1, double freq2);
double phase_dist(double phase1, double phase2, double modulo);
double phase_error(double phase1, double phase2, double freq1, double freq2, double distance_ms, double modulo);
void append_tsd_config_to_tsd_frame(t_tsd_config *tsc, t_tsd_frame *frame);
void get_ptrack_voice_average_frequence_and_ampli_in_frame_range(t_ptrack_voice *ptv, double *freq, double *amp, long start_frame, long end_frame);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
END_CHECK_LINKAGE
#endif

#endif // _NOTATION_SPECTRAL_H_
