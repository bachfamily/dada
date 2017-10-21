/**
	@file
	dada.paint.h
	Paint and display utilities header for dada library
 
	by Daniele Ghisi
 */

#ifndef _DADA_PAINT_H_
#define _DADA_PAINT_H_

#define DADA_MAX_SLIDES_PER_SPRITE 10

#include "dada.h"
#include "dada.commons.h"
#include "notation.h"
#include "dada.geometry.h"

/** Line styles.	@ingroup graphs */
typedef enum _dada_line_style 
{
	DADA_LINE_STRAIGHT = 0,		///< Straight line
	DADA_LINE_SEGMENTED = 1,	///< Segmented line
	DADA_LINE_CURVE = 2,		///< Curved line
} e_dada_line_style;



typedef struct _dada_sprite
{
	t_symbol			*name;
	
	t_rect				source_rect;										///< Source rectangle
	char				allow_stretch;										///< Stretch when destination rectangle has different dimensions
	
	long				num_slides;											///< Number of slides (e.g. as animated gif)
	t_jsurface			*slide_left[DADA_MAX_SLIDES_PER_SPRITE];	///< Actual slides surfaces, left-oriented
	t_jsurface			*slide_right[DADA_MAX_SLIDES_PER_SPRITE];	///< Actual slides surfaces, right-oriented (leave NULL it if not needed)
	t_symbol			*slide_path[DADA_MAX_SLIDES_PER_SPRITE];	///< Actual slides file path (left oriented only, the other one will be automatically computed)
	double				slide_time;											///< Duration of each "slide" in milliseconds
} t_dada_sprite;




#define DADA_DEFAULT_RECT_ROUNDNESS	8

void ezpaint_note_with_staff(t_object *x, t_jgraphics *g, t_object *view, double midicents, e_accidentals_preferences accpref, long tonedivision,
							 t_pt staff_topleft, double staff_width, double fontsize, double note_x_pos, char shift_note_for_accidentals,
							 t_jrgba *staffcolor, t_jrgba *clefcolor, t_jrgba *notecolor);


void paint_cross(t_jgraphics *g, t_jrgba *color, t_pt center, double size, double linewidth);
void paint_square(t_jgraphics *g, t_jrgba *bordercolor, t_jrgba *fillcolor, t_pt center, double halfside, double borderwidth);
void paint_hexagon(t_jgraphics *g, t_jrgba *bordercolor, t_jrgba *fillcolor, t_pt center, double circumradius, double borderwidth, char pointy_topped);
void paint_pointed_corolla(t_jgraphics *g, t_jrgba *color, t_pt center, double radius, double num_points, double pointradius);
void paint_rectangle_fast(t_jgraphics *g, t_jrgba *bordercolor, t_jrgba *fillcolor, double x, double y, double width, double height, double borderwidth);
void paint_square_fast(t_jgraphics *g, t_jrgba *bordercolor, t_jrgba *fillcolor, t_pt center, double halfside, double borderwidth);
void paint_line_advanced(t_jgraphics *g, t_jrgba color, t_pt start, t_pt end, double linewidth, e_dada_line_style style, 
						 char show_arrows, double arrow_size, char *label, t_jfont *jf_label, double curve_amount);
void paint_curve_advanced(t_jgraphics *g, t_jrgba color, t_pt start, t_pt end, double linewidth, double curve_height, char paint_arrow, 
						  double arrow_size, char *label, t_jfont *jf);
void paint_regular_polygon(t_jgraphics *g, long num_vertices, t_jrgba *bordercolor, t_jrgba *fillcolor, t_pt center, double circumradius, double borderwidth);

char is_pt_in_curve_advanced_shape(t_pt pt, t_pt start, t_pt end, double linewidth, double curve_height);

// sprites
void sprite_init(t_dada_sprite *sprite, t_symbol *name, t_rect *source_rect, char allow_stretch, double slide_time, long num_slides, t_symbol **slides);
void paint_sprite(t_jgraphics *g, t_dada_sprite *sprite, long slide_idx, t_rect source, t_rect dest, char direction, t_jhsla *deltacolor);
void sprite_free(t_dada_sprite *sprite);
void sprite_reinit(t_dada_sprite *sprite, t_symbol *name, t_rect source_rect, char allow_stretch, double slide_time, long num_slides, ...);

void dadaobj_paint_shape(t_dadaobj *r_ob, t_shape *sh, t_pt center, t_jgraphics *g, t_jrgba *bordercolor, t_jrgba *fillcolor, double linewidth);
void dadaobj_paint_shape_from_view(t_dadaobj *r_ob, t_shape *sh, t_object *view, t_jgraphics *g, t_jrgba *bordercolor, t_jrgba *fillcolor, double linewidth);
void dadaobj_paint_shape_dotted(t_dadaobj *r_ob, t_shape *sh, t_pt center, t_jgraphics *g, t_jrgba *color, double dot_distance, double dot_radius);

void dadaobj_paint_selection_rectangle(t_dadaobj *r_ob, t_jgraphics *g, t_jrgba *border_color, t_jrgba *fill_color);

void dadaobj_paint_polygon(t_dadaobj *r_ob, t_pt center, t_jgraphics *g, t_polygon *p, t_jrgba *bordercolor, t_jrgba *fillcolor, double linewidth);
void dadaobj_paint_dashed_polygon_contour(t_dadaobj *r_ob, t_pt center, t_jgraphics *g, t_polygon *p, t_jrgba *bordercolor, double linewidth, double dashlength);
long rect_linetorect_intersect(t_pt p, t_rect r, t_pt *intersection);


#endif // _DADA_PAINT_H_

