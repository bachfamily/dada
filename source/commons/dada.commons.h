/**
	@file
	dada.commons.h
	Common utilities header for dada library
 
	by Daniele Ghisi
 */

#ifndef _DADA_COMMONS_H_
#define _DADA_COMMONS_H_

#include "dada.cursors.h"
#include "dada.inspector.h"

#define DADA_DEFAULT_PITCH		6000
#define DADA_DEFAULT_VELOCITY	100
#define DADA_MIN_VELOCITY		1
#define DADA_MAX_VELOCITY		127

#define DADA_DEFAULT_TEMPO_DIGITS 2

#define SQRT3 1.732050808
#define SQRT3OVER2 0.866025404

/// Standard palette colors

#define DADA_RED (build_jrgba(0.4, 0., 0., 1.))
#define DADA_GREEN (build_jrgba(0., 0.4, 0., 1.))
#define DADA_BLUE (build_jrgba(0., 0., 0.4, 1.))
#define DADA_YELLOW (build_jrgba(0.7, 0.68, 0., 1.))
#define DADA_ORANGE (build_jrgba(0.8, 0.34, 0., 1.))
#define DADA_VIOLET (build_jrgba(0.4, 0., 0.4, 1.))
#define DADA_BLACK (build_jrgba(0., 0., 0., 1.))
#define DADA_GREY_10 (build_jrgba(0.1, 0.1, 0.1, 1.))
#define DADA_GREY_25 (build_jrgba(0.25, 0.25, 0.25, 1.))
#define DADA_GREY_50 (build_jrgba(0.5, 0.5, 0.5, 1.))
#define DADA_GREY_75 (build_jrgba(0.75, 0.75, 0.75, 1.))
#define DADA_GREY_90 (build_jrgba(0.9, 0.9, 0.9, 1.))
#define DADA_WHITE (build_jrgba(1., 1., 1., 1.))
#define DADA_TRANSPARENT (build_jrgba(0., 0., 0., 0.))

#define DADA_COLOR_INACTIVE (build_jrgba(0., 0., 0., 0.4))



// A wrapper for class_new() also checking that the class size is acceptable
// Useful for debugging huge objects such as bach.score

#define CLASS_NEW_CHECK_SIZE_EXT(CLASS, name, mnew, mfree, size, mmenu, type, ...) \
{ \
if (size < 16384 - 16) \
CLASS = class_new(name, mnew, mfree, size, mmenu, type, __VA_ARGS__); \
else { \
post("Class %s too large, size = %d", name, (int) size); \
return; \
} \
}


#ifdef WIN_VERSION
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#include "Shlwapi.h"
#define strcasestr StrStrI
#define qsort_r(base, nmemb, size, arg, cmpfn) qsort_s(base, nmemb, size, cmpfn, arg)
#endif


t_symbol *dada_ezlocate_file(t_symbol *file_name, t_fourcc *file_type);
t_symbol *dada_ezlocate_folder(t_symbol *foldername);
t_symbol *dada_ezresolve_file(t_symbol *file_name, short *outpath);
void dada_path_split(const char *fullpath, char *path, char *filename);

//t_jsurface *dada_quick_surface_from_file(char *file_name); // use gensurface_from_file
//t_jpattern *dada_quick_pattern_from_file(char *file_name);


unsigned short get_default_accidental_char(double screen_acc_double);
void llll_reshape_scalarmode(t_llll **ll, t_llll *model);
t_jrgba dada_long_to_color(long i);
void change_color_for_velocity_alpha(t_jrgba *color, long velocity);
void change_color_for_velocity_lighten(t_jrgba *color, long velocity);
void change_color_for_velocity_darken(t_jrgba *color, long velocity);

t_llll *color_to_llll(t_jrgba *color);
t_jrgba llll_to_color(t_llll *ll);
void change_hue_and_lightness(t_jrgba *color, double delta_hue, double delta_lightness, double min_lightness, double max_lightness);
t_jrgba symbol_to_color(t_symbol *sym);
void dadaobj_parse_llll(t_dadaobj *r_ob, t_llll *ll, char *model, ...);
void dadaobj_parseargs(t_dadaobj *r_ob, t_llll *ll, char *model, ...);

t_jsurface *get_surface_from_file(t_symbol *file_path);
t_jsurface *clone_surface(t_jsurface *orig, char mirror_x, char mirror_y);


t_pt get_center_pix(t_dadaobj *r_ob, t_object *patcherview, t_rect *drawrect);
t_pt coord_to_pix(t_dadaobj *r_ob, t_pt center, t_pt coord);
t_pt pix_to_coord(t_dadaobj *r_ob, t_pt center, t_pt pixel);
t_pt pix_to_coord_from_view(t_dadaobj *r_ob, t_object *view, t_pt pixel);
t_pt coord_to_pix_from_view(t_dadaobj *r_ob, t_object *view, t_pt coord);
t_pt delta_pix_to_delta_coord(t_dadaobj *r_ob, t_pt delta_pixel);
t_pt delta_coord_to_delta_pix(t_dadaobj *r_ob, t_pt delta_coord);
t_pt get_min_displayed_coord(t_dadaobj *r_ob, t_pt center, t_rect rect);
t_pt get_max_displayed_coord(t_dadaobj *r_ob, t_pt center, t_rect rect);
t_rect rect_coord_to_pix(t_dadaobj *r_ob, t_pt center, t_rect coord, char autoflip_height);
t_rect rect_pix_to_coord(t_dadaobj *r_ob, t_pt center, t_rect pixel, char autoflip_height);

void round_cubic_coordinates_for_hex_grid(double *x, double *y, double *z);

double freq_to_mc(double freq, double diapason);
double mc_to_freq(double mc, double diapason);
double rand_f(double min, double max);

void hatom_subs(t_llll *ll, long pos, t_hatom *h);
t_llll *llll_comb_fix(t_llll *ll, t_atom_long startk, t_atom_long endk, t_atom_long max_gap);

t_llll *symbol_and_llll_to_llll(t_symbol *sym, t_llll *ll);
t_llll *symbol_and_llll_to_llll_chained(t_symbol *sym, t_llll *ll);
long find_symbol_in_symbol_array(t_symbol *elem, t_symbol **array, long array_length);

long dada_llll_check(t_llll *ll);
const char *dada_get_default_include();
double hatom_to_angle_in_rad(t_hatom *h);


#endif // _DADA_COMMONS_H
