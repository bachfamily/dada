/**
	@file
	dada.notation.h
	Common notation header for dada library
 
	by Daniele Ghisi
 */

#ifndef _DADA_NOTATION_H_
#define _DADA_NOTATION_H_

#include "dada.commons.h"
#include "dada.windows.h"
#include "notation.h"



#define DADA_CUT_NOTE_START     0x01
#define DADA_CUT_NOTE_END       0x02
#define DADA_CUT_ANY            (DADA_CUT_NOTE_START | DADA_CUT_NOTE_END)

#define DADA_JOIN_CUT_NOTES_EPSILON_MS 0.01


// all elements are 0-based (as a general rule, things are 0-based internally, but 1-based for the user)
typedef struct _dada_score_path
{
	long	voice_num;
	long	measure_num;
	long	chord_idx;
	long	note_idx;
} t_dada_score_path;

// Gathered syntax modification function
typedef long (*dada_gs_modif_fn)(t_llll *ll, e_notation_objects obj, void *idx, void *onset, void *arg1, void *arg2, void *arg3);

void dada_roll_transpose(t_llll *gs, double delta_mc);
void dada_roll_transposencrop(t_llll *gs, double delta_mc, double crop_min_pitch, double crop_max_pitch);
void dada_roll_invert(t_llll *gs, double pitch_for_mirroring_mc);
void dada_roll_shift(t_llll *gs, double shift_delta_ms, char via_cropping = true);
void dada_roll_shiftncrop(t_llll *gs, double shift_delta_ms, double crop_length_ms);
void dada_roll_mix(t_llll *gs1, t_llll *gs2, long sew_this = DADA_CUT_NOTE_START, long with_this = DADA_CUT_NOTE_END);
t_llll *dada_roll_slice(t_llll *gs, double slice_point, char mark_split_left_parts, char mark_split_right_parts, char copy_tempi);
t_llll *dada_roll_split_preserve(t_llll *gs, double split_point, char mark_split_left_parts, char mark_split_right_parts, char copy_tempi); // preserves the note position
t_llll *dada_roll_split(t_llll *gs, double split_point, char mark_split_left_parts, char mark_split_right_parts, char copy_tempi);
void dada_roll_blend(t_llll *gs1, t_llll *gs2, double split_point, double mark_split);
void dada_roll_join(t_llll *gs1, t_llll *gs2);
void dada_roll_circularshift(t_llll *gs, double shift_delta_ms);
double dada_roll_get_length(t_llll *gs);
t_llll *dada_roll_gen(double onset, double cents, double duration, long velocity);
t_llll *dada_roll_gen_empty(long num_voices);
void dada_roll_retrograde(t_llll *gs, double total_length);
void dada_roll_stretch(t_llll *gs, double factor);
void dada_roll_trim_blank_starting_space(t_llll *gs, double *new_gs_offset_ms);
t_llll *dada_roll_get_labels(t_llll *gs);
void dada_roll_retain_label(t_llll *gs, t_hatom *label);
t_llll *dada_roll_extract_label(t_llll *gs, t_hatom *label, double *new_gs_offset_ms);
long dada_roll_get_max_num_notes_per_chord(t_llll *gs);
long dada_roll_get_num_chords(t_llll *gs);
double dada_roll_get_average_pitch(t_llll *gs, char use_dur_and_vel);
double dada_roll_get_average_timepos(t_llll *gs, char use_dur_and_vel);
void dada_roll_prepend_roll_sym(t_llll *gs);

void dada_roll_collapse(t_llll *gs, char collapse_voices, t_llll **voice_flags, char collapse_chords, t_llll **chord_flags, char mark_lthings);
void dada_roll_uncollapse(t_llll *gs, t_llll *voice_flags, char also_uncollapse_chords, t_llll *chord_flags, char remove_empty_chords);
void dada_roll_free_path_in_lthings(t_llll *gs);
void dada_roll_apply_window_on_velocities(t_llll *gs, e_dada_windows window_type, double *duration_ms);

t_timepoint timepoints_diff(t_timepoint tp1, t_timepoint tp2);

void *copy_lthing_fn(void *x);

void dada_roll_sort_notes(t_llll *gs);
void dada_roll_sort_chords(t_llll *gs);

t_llll *dada_sliceheader(t_llll *gs);

void dada_roll_iterate_on_notes(t_llll *gs, dada_gs_modif_fn modif_fn, e_notation_objects notation_obj, void *arg1, void *arg2, void *arg3);
void dada_roll_iterate_on_chords(t_llll *gs, dada_gs_modif_fn modif_fn, e_notation_objects notation_obj, void *arg1, void *arg2, void *arg3);
void dada_score_iterate_on_measures(t_llll *gs, dada_gs_modif_fn modif_fn, e_notation_objects notation_obj, void *arg1, void *arg2, void *arg3);
void dada_score_iterate_on_chords(t_llll *gs, dada_gs_modif_fn modif_fn, e_notation_objects notation_obj, void *arg1, void *arg2, void *arg3);

void dada_iterate_on_markers(t_llll *gs, dada_gs_modif_fn modif_fn, e_notation_objects notation_obj, void *arg1, void *arg2, void *arg3);
t_llll *dada_get_markers(t_llll *gs); // markers are cloned
t_tempo *dada_get_first_marker_tempo(t_llll *gs); // tempo is allocated
double dada_get_first_marker_division_or_barline(t_llll *gs, char *is_division);
void dada_markers_delete_tempo_markers(t_llll *gs);

void remove_all_marking_to_llll_lthings(t_llll *gs, e_notation_objects notation_obj);


long dada_score_getnummeas(t_llll *gs);
t_llll *dada_score_getts(t_llll *gs);
t_rational dada_measure_getsymdur(t_llll *gs);
t_llll *dada_score_getdivisions(t_llll *gs);
t_rational dada_score_gettotsymduration(t_llll *gs);

// all returned tempi are allocated and need to be freed
t_tempo *dada_measure_get_last_tempo(t_llll *gs);
t_tempo *dada_measure_get_first_tempo(t_llll *gs);
t_tempo *dada_score_get_first_tempo(t_llll *gs);
t_tempo *dada_score_get_last_tempo(t_llll *gs);

void dada_measure_add_starting_tempo(t_llll *gs, t_tempo *tempo);

long dada_get_num_voices(t_llll *gs);


t_llll *dada_score_multisplit_measures(t_llll *gs, long num_splits, long *split_measure_num, char copy_tempi);
t_llll *dada_score_split(t_llll *gs, t_timepoint split_pt, t_timesignature *splitpt_ts, t_tempo *splitpt_tempo, char copy_tempi);
void dada_score_apply_window_on_velocities(t_llll *gs, e_dada_windows window_type, t_rational *tot_symduration);

#endif // _DADA_NOTATION_H



