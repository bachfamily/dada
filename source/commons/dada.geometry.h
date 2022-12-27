/**
	@file
	dada.geometry.h
	Geometric utilities header for dada library
 
	by Daniele Ghisi
 */

#ifndef _DADA_GEOMETRY_H_
#define _DADA_GEOMETRY_H_


#include "dada.h"
#include "dada.math.h"

#define TWO_PI 6.2831853072
#define DADA_POLYGON_MAX_VERTICES 100


/** Shape types.	@ingroup geometry */
typedef enum _dada_shape_types 
{
	DADA_SHAPE_NONE = 0,	///< No shape
	DADA_SHAPE_POLYGON,		///< A poligon
	DADA_SHAPE_ELLIPSE		///< An ellipse
} e_dada_shape_types;


/** A polygon with a maximum fixed number of vertices (differently from the bach #t_polygon).	
 Somehow an "ezpolygon".
 @ingroup geometry */
typedef struct _dadapolygon
{
	long num_vertices;
	t_pt vertex[DADA_POLYGON_MAX_VERTICES];
} t_dadapolygon;



/** An ellipse.	@ingroup geometry */
typedef struct _ellipse
{
	t_pt		center;		///< Center of the circle
	t_pt		radius;     ///< Radius with respect to the (x, y) axis
	double		rotation;	///< Rotation angle (from x axis), in radians
} t_ellipse;



typedef union shapeword
{
	t_dadapolygon	polygon;	///< Polygon
	t_ellipse	ellipse;	///< Ellipse
} t_shapeword;


/** A colored shape, with an optional channel.	@ingroup geometry */
typedef struct _shape
{
	e_dada_shape_types	type;		///< Shape type
	t_jrgba				color;		///< Shape color
	long				channel;	///< Used as voice number of MIDIchannel associated to the shape
	union shapeword	shape;			///< Actual shape
} t_shape;

void dadapolygon_to_polygon(t_dadapolygon *dp, t_polygon **p);
void polygon_to_dadapolygon(t_polygon *p, t_dadapolygon *dp);

t_shape ezbuild_dadapolygon(t_jrgba color, long MIDIchannel, long count, ...);
t_shape build_dadapolygon(t_jrgba color, long MIDIchannel, long num_vertices, t_pt *vertices);
t_shape build_ellipse(t_jrgba color, long MIDIchannel, t_pt center, t_pt radius, double rotation);


t_pt get_dadapolygon_barycenter(t_dadapolygon *poly);
t_pt get_shape_barycenter(t_shape *shape);

double get_shape_barycentric_outermost_radius(t_shape *shape, t_pt *barycenter);
double get_shape_barycentric_innermost_radius(t_shape *shape, t_pt *barycenter);


void shape_translate(t_shape *shape, t_pt delta);
double rotation_matrix_to_angle(t_jmatrix *rotation_matrix);
void make_angle_standard(double *angle);
void shape_rotate_from_matrix(t_shape *shape, t_pt rotation_center, t_jmatrix *rotation_matrix);
void shape_scale(t_shape *shape, t_pt scale_center, double factor_x, double factor_y);
void shape_shake(t_shape *shape, double min_abs_shift, double max_abs_shift, 
				 double min_abs_angle, double max_abs_angle, t_pt region_center, double region_radius);
void shape_offset(t_shape *shape, double how_much);



/**	Determine if a point lies inside a generic polygon
	@ingroup	geometry
	@param	pt		The point
	@param	poly	The polygon
	@return			1 if (ptx, pty) is inside the polygon, 0 otherwise
 */ 
char is_pt_in_dadapolygon(t_pt pt, t_dadapolygon *poly);



/**	Determine if a point lies inside a shape
	@ingroup	geometry
	@param	pt		The point
	@param	shape	The shape
	@return			1 if (ptx, pty) is inside the shape, 0 otherwise
 */ 
char is_pt_in_shape(t_pt pt, t_shape *shape);
char is_pt_in_ellipse(t_pt pt, t_ellipse *ellipse);

double pt_dadapolygon_distance(t_pt pt, t_dadapolygon *poly);
double pt_ellipse_distance(t_pt pt, t_ellipse *ell);
double pt_shape_distance(t_pt pt, t_shape *shape);


t_pt get_ellipse_radiuspoint_coord(t_ellipse *ellipse, long idx);
double get_dadapolygon_perimeter(t_dadapolygon *poly);
double get_average_vertex_distance_from_barycenter(t_dadapolygon *poly);
t_dadapolygon build_regular_dadapolygon(long num_vertices, t_pt center, double circumradius);

char get_segment_intersection(t_pt line1_start, t_pt line1_end, t_pt line2_start, t_pt line2_end, t_pt *collision_pt);
t_pt pt_rotate(t_pt pt, double angle);


// also works for nonstandard rectangles (with negative height/width)
char is_pt_in_rectangle_extended(t_pt pt, t_rect rect);

int is_pt_in_horizontal_line_shape(double point_x, double point_y, double line_y, double start_x, double end_x, double line_width);
int is_pt_in_vertical_line_shape(double point_x, double point_y, double line_x, double start_y, double end_y, double line_width);
int is_pt_in_line_shape_improved(double point_x, double point_y, double start_x, double start_y, double end_x, double end_y, double line_width);
int is_pt_in_segmented_line_shape(double point_x, double point_y, double start_x, double start_y, double end_x, double end_y, double line_width);
double pt_norm_squared(t_pt pt);
double pt_pt_cmp(t_pt pt1, t_pt pt2);
t_pt pt_normalize(t_pt pt);
t_pt get_random_pt_in_rect(t_rect rect);
t_pt get_random_pt_near_pt(t_pt pt, double min_dist, double max_dist);

t_rect rect_boundingbox_to_baricentric(t_rect boundingbox);
t_rect rect_baricentric_to_boundingbox(t_rect baricentric);


void find_convex_hull(long num_points, t_pt *points, t_dadapolygon *poly);


char duplicate_dadapolygon_vertex(t_dadapolygon *poly, long idx, t_pt new_pt);
char delete_dadapolygon_vertex(t_dadapolygon *poly, long idx, char min_number_of_vertices_to_remain);
char move_dadapolygon_vertex(t_dadapolygon *poly, long idx, t_pt new_pt, char given_as_delta);
void clone_shape(t_shape *giver, t_shape *cloned);

double pt_pt_distance_squared_weighted(t_pt pt1, t_pt pt2, t_pt weight);

t_rect get_rect_near_pt_inside_rect(t_pt pt, double width, double height, t_rect rect, t_pt delta, t_pt pad, t_pt *nearest_corner);

#endif // _DADA_GEOMETRY_H_

