/**
	@file
	dada.graphs.h
	Graphs and networks utilities header for dada library
 
	by Daniele Ghisi
 */

#ifndef _DADA_GRAPHS_H_
#define _DADA_GRAPHS_H_

#include "dada.h"
#include "dada.object.h"
#include "dada.geometry.h"
#include "dada.commons.h"
#include "dada.paint.h"


#define DADA_GRAPH_ALLOC_STEP	256
#define DADA_DEFAULT_EDGE_PITCHNVEL_METADATA (build_pitchnvel_metadata(6000, 100))
#define DADA_DEFAULT_VERTEX_PITCHNVEL_METADATA (build_pitchnvel_metadata(6000, 100))
#define DADA_DEFAULT_EDGE_LONG_METADATA (build_long_metadata(0))
#define DADA_DEFAULT_VERTEX_LONG_METADATA (build_long_metadata(0))
#define DADA_DEFAULT_VERTEX_DOUBLE_METADATA (build_double_metadata(0.))
#define DADA_DEFAULT_VERTEX_OBJ_METADATA (build_double_metadata(NULL))
#define DADA_DEFAULT_EDGE_DOUBLE_METADATA (build_double_metadata(0.))
#define DADA_DEFAULT_EDGE_VANILLABOX_METADATA (build_vanillabox_metadata(gensym("idle"),1,1))
#define DADA_DEFAULT_VERTEX_VANILLABOX_METADATA (build_vanillabox_metadata(gensym("idle"),1,1))
#define DADA_DEFAULT_EDGE_OUTINNUM_METADATA (build_outinnum_metadata(0,0))
#define DADA_DEFAULT_VERTEX_OUTINNUM_METADATA (build_outinnum_metadata(0,0))
#define DADA_DEFAULT_EDGE_SCORE_METADATA (build_score_metadata(NULL))
#define DADA_DEFAULT_VERTEX_SCORE_METADATA (build_score_metadata(NULL))

#define DADA_GRAPH_EDGE_DEFAULT_SELECTION_PAD 4
#define DADA_GRAPH_VERTEX_DEFAULT_SELECTION_PAD 4

#define DADA_GRAPH_CURVE_AMOUNT 25

#define DADA_GRAPH_MAX_VANILLABOX_INS 2
#define DADA_GRAPH_MAX_VANILLABOX_OUTS 2

/** Graph flags.	@ingroup graphs */
typedef enum _dada_graph_flags 
{
	DADA_GRAPH_FLAG_NONE					= 0,
	DADA_GRAPH_FLAG_SYMMETRIC				= 1,	///< Symmetric edges: no need to repeat edges, they'll be counted once for (a b) and (b a)
	DADA_GRAPH_FLAG_CONNECTED_COMPONENTS	= 2,	///< Also retrieves and synchronize the information about connected components
} e_dada_graph_flags;


/** Graph edge flags.	@ingroup graphs */
typedef enum _dada_graph_edge_flags
{
    DADA_GRAPH_EDGE_FLAG_NONE					= 0,
    DADA_GRAPH_EDGE_FLAG_PASSTHROUGH				= 1,	///< Edge is non-solid
} e_dada_graph_edge_flags;


/** Metadata types.	@ingroup graphs */
typedef enum _dada_graph_metadata_type 
{
	DADA_GRAPH_METADATA_NONE = 0,		///< None
	DADA_GRAPH_METADATA_PITCHNVEL = 1,	///< Pitch + velocity
	DADA_GRAPH_METADATA_LONG = 2,		///< A long number
	DADA_GRAPH_METADATA_DOUBLE = 3,		///< A double precision number
	DADA_GRAPH_METADATA_VANILLABOX = 4,	///< A box with inlets and outlets, and a type
	DADA_GRAPH_METADATA_OUTINNUM = 5,	///< Number of inlet and outlet
    DADA_GRAPH_METADATA_LLLLNODE = 6,	///< Node to display an llll
    DADA_GRAPH_METADATA_OBJ = 7,        ///< Generic pointer
    DADA_GRAPH_METADATA_SCORE = 8,      ///< A score as llll
    DADA_GRAPH_METADATA_WEIGHT = 9,		///< A weight, as double precision number
} e_dada_graph_metadata_type;


/** Graph edge retouch modes.	@ingroup graphs */
typedef enum _dada_graph_edge_retouch_modes
{
    DADA_GRAPH_EDGERETOUCH_NONE = 0,
    DADA_GRAPH_EDGERETOUCH_SNAP_TO_BORDER = 1,
    DADA_GRAPH_EDGERETOUCH_SNAP_TO_MIDPOINTS = 2,
} e_dada_graph_edge_retouch_modes;



typedef struct _pitchnvel
{
	double	pitch_mc;
	long	velocity;
} t_pitchnvel;


typedef struct _vanillabox
{
    t_symbol *type;
	long	 num_ins;
	long	 num_outs;
	t_llll	 *ins[DADA_GRAPH_MAX_VANILLABOX_INS];
//	t_llll	 *outs[DADA_GRAPH_MAX_VANILLABOX_OUTS];
} t_vanillabox;

typedef struct _outinnum
{
	long	num_in;
	long	num_out;
} t_outinnum;


typedef struct _llllnode
{
	t_llll	*ll;
	t_jrgba	bgcolor;
	t_jrgba	bordercolor;
	t_jrgba	textcolor;
	double	width;
	double	height;
} t_llllnode;


typedef struct _llllscore
{
    t_llll      *ll;
    t_symbol    *label;
} t_llllscore;



typedef union _dada_graph_metadata
{
	t_pitchnvel		m_pitchnvel;
	long			m_long;
	double			m_double;
	t_vanillabox	m_vanillabox;
	t_outinnum		m_outinnum;
	t_llllnode		m_llllnode;
    t_llllscore		m_llllscore;
    void			*m_obj;
} t_dada_graph_metadata;


typedef struct _dada_graph_vertex
{
	t_dadaitem				r_it;	// Vertex coordinates are here inside

	long					connected_component_idx;	//< Only filled if #DADA_GRAPH_FLAG_CONNECTED_COMPONENTS is set
	t_dada_graph_metadata	data;	// vertex is "colored" with additional meta-data
	long					flag;
} t_dada_graph_vertex;


typedef struct _dada_graph_edge
{
	long	start;      // index of starting vertex
	long	end;        // index of ending vertex
	t_dada_graph_metadata	data;	// edge is "colored" with additional meta-data
	long	flag;						// a custom flag
} t_dada_graph_edge;


typedef struct _dada_graph_connected_component
{
	long		num_vertices;
	long		*vertices;
	t_dadapolygon	poly;
	long		flag;
} t_dada_graph_connected_component;


// A structure to represent a graph, as sequence of vertices and an adjacences list.
typedef struct _dada_graph
{
	// type:
	long						flags;					///< A combination of #e_dada_graph_flags determining the type of graph
	e_dada_graph_metadata_type	vertex_metadata_type;	///< Type of metadata contained in the vertices
	e_dada_graph_metadata_type	edge_metadata_type;		///< Type of metadata contained in the edges
	e_dada_line_style			line_style;				///< Line style for drawing

	// vertices
	long				num_vertices;	///< Number of vertices
	t_dada_graph_vertex	*vertices;
	long				num_allocated_vertices;

	// edges
	long				num_edges;		///< Number of edges
	t_dada_graph_edge	*edges;		///< 0-based, as anything which is internal
	long				num_allocated_edges;
	
	// connected components
	long								num_connected_components;
	t_dada_graph_connected_component	*connected_components;
	long								num_allocated_connected_components;
	
	// internal flags, don't use
	char					dont_reparse_or_update_connected_components;
} t_dada_graph;


typedef void (*vertex_to_properties_fn)(t_dada_graph_vertex *v, double *width, double *height);
// label must be already instantiated and AT LEAST 256 chars
typedef void (*edge_to_properties_fn)(t_dada_graph_edge *e, char *label);


void graph_new(t_dada_graph *graph, long flags, e_dada_graph_metadata_type vertex_metadata_type, e_dada_graph_metadata_type edge_metadata_type, e_dada_line_style line_style);
void graph_set_metadata_to_vertex_from_llll(t_dada_graph *graph, long vertex_id, t_llll *metadata_ll);
void graph_set_metadata_to_edge_from_llll(t_dada_graph *graph, long edge_id, t_llll *metadata_ll);
t_llll *graph_vertex_to_llll(t_dada_graph *graph, long vertex_id);
t_llll *graph_edge_to_llll(t_dada_graph *graph, long edge_id);
t_llll *graph_to_llll(t_dada_graph *graph);
void graph_from_llll(t_llll *ll, t_dada_graph *graph, double node_width = 0, double node_height = 0);
void graph_free(t_dada_graph *graph);
void graph_assign_all_default_metadata(t_dada_graph *graph);
void graph_paint_edge(t_dadaobj *r_ob, t_jgraphics *g, t_rect rect, t_pt center, t_dada_graph *graph,
					  t_jrgba graph_color, long edge_index,
					  double fixed_vertex_width, double fixed_vertex_height, vertex_to_properties_fn vertex_to_properties,
					  double edge_width, char edge_retouch_mode, edge_to_properties_fn edge_to_properties, char paint_hover, t_jfont *jf_label, char show_arrows, double arrow_size);
void graph_paint(t_dadaobj *r_ob, t_jgraphics *g, t_rect rect, t_pt center, t_dada_graph *graph,
				 t_jrgba graph_color, char paint_vertices, char paint_edges, 
				 double fixed_vertex_width, double fixed_vertex_height, vertex_to_properties_fn vertex_to_properties,
				 double edge_width, char edge_retouch_mode, edge_to_properties_fn edge_to_properties, char paint_hover, t_jfont *jf_label, char show_arrows, double arrow_size);

long graph_coord_to_vertex(t_dadaobj *r_ob, t_dada_graph *graph, t_pt coord, double vertex_size_in_coord, double tolerance);
long graph_coord_to_edge(t_dadaobj *r_ob, t_dada_graph *graph, t_pt coord, double edge_width_in_coord, double tolerance);
void graph_clear(t_dada_graph *graph);
long graph_add_vertex(t_dada_graph *graph, t_pt coord, t_dada_graph_metadata metadata, double width = 0, double height = 0, long flag = 0);
long graph_import_dadapolygon(t_dada_graph *graph, t_dadapolygon *poly, t_dada_graph_metadata vertex_metadata,
						  t_dada_graph_metadata edge_metadata, char sides_in_harm_series, double node_width = 0, double node_height = 0);
long graph_add_edge(t_dada_graph *graph, long idx1, long idx2, t_dada_graph_metadata metadata, long flag = 0);
long graph_add_edge_symmetric(t_dada_graph *graph, long idx1, long idx2, t_dada_graph_metadata metadata);
void graph_change_line_style(t_dada_graph *graph, e_dada_line_style new_style);

t_pt graph_vertex_index_to_coord(t_dada_graph *graph, long idx);
void graph_move_vertex(t_dada_graph *graph, long idx, t_pt new_coord);
void graph_move_vertex_delta(t_dada_graph *graph, long idx, t_pt delta_coord);
void graph_move_edge(t_dada_graph *graph, long idx, t_pt new_barycenter_coord);
void graph_move_edge_delta(t_dada_graph *graph, long idx, t_pt delta_coord);

long graph_vertices_to_edge(t_dada_graph *graph, long idx1, long idx2);
void graph_vertices_to_edges(t_dada_graph *graph, long idx1, long idx2, long *edges, long *num_edges, long max_num_edges);
char graph_are_vertices_connected(t_dada_graph *graph, long idx1, long idx2);
t_llll *graph_vertex_to_edge_list(t_dada_graph *graph, long idx);


// these all return 0 if succesful, 1 if error (or the element idx if pertinent)
char graph_change_edge_velocity(t_dada_graph *graph, long idx, double delta_vel);
char graph_change_edge_pitch(t_dada_graph *graph, long idx, double delta_mc);
char graph_change_vertex_pitch(t_dada_graph *graph, long idx, double delta_mc);
char graph_change_vertex_velocity(t_dada_graph *graph, long idx, double delta_vel);
char graph_delete_edge_from_vertices(t_dada_graph *graph, long idx1, long idx2);
char graph_delete_edge(t_dada_graph *graph, long j);
char graph_reverse_edge(t_dada_graph *graph, long j);
char graph_delete_vertex(t_dada_graph *graph, long idx, char preserve_edges);
char graph_subdivide_edge(t_dada_graph *graph, long idx, long num_parts, long *new_edge_start_idx, long *new_edge_end_idx, double vertex_width = 0, double vertex_height = 0);
char graph_split_edge(t_dada_graph *graph, long idx, t_pt split_point, long *edge1_idx, long *edge2_idx, double vertex_width = 0, double vertex_height = 0);
char graph_extrude_edge(t_dada_graph *graph, long idx, long *new_edge_start_idx, long *new_edge_end_idx, double vertex_width = 0, double vertex_height = 0);
t_llll *graph_vertex_get_vertices_adj_list(t_dada_graph *graph, long idx);
t_llll *graph_vertex_get_outgoing_edges_list(t_dada_graph *graph, long idx);
t_llll *graph_vertex_get_incoming_edges_list(t_dada_graph *graph, long idx);

void graph_parse_connected_components(t_dada_graph *graph);
long graph_add_connected_component(t_dada_graph *graph, long num_vertices, long *vertices);
long graph_coord_to_connected_component(t_dada_graph *graph, t_pt coord);
void graph_update_connected_component_convex_hull(t_dada_graph *graph, long idx);
char graph_delete_connected_component(t_dada_graph *graph, long idx);
char graph_change_connected_component_pitch(t_dada_graph *graph, long idx, double delta_mc);
char graph_change_connected_component_velocity(t_dada_graph *graph, long idx, double delta_vel);
void graph_move_connected_component_delta(t_dada_graph *graph, long idx, t_pt delta_coord);

long graph_append_vertex_to_connected_component(t_dada_graph *graph, long connected_component_idx, long vertex_idx);
long graph_duplicate_vertex(t_dada_graph *graph, long idx, t_pt new_coords, char add_edge_from_old_to_new);

char graph_scale_connected_component(t_dada_graph *graph, long idx, double factor);
char graph_rotate_connected_component(t_dada_graph *graph, long idx, double angle);
long graph_duplicate_connected_component(t_dada_graph *graph, long idx, t_pt delta_pt);

long graph_connected_component_bring_to_front(t_dada_graph *graph, long idx);
long graph_connected_component_send_to_back(t_dada_graph *graph, long idx);

t_dada_graph_metadata build_pitchnvel_metadata(double pitch_mc, long vel);
t_dada_graph_metadata build_score_metadata(t_llll *score);
t_dada_graph_metadata build_long_metadata(long num);
t_dada_graph_metadata build_obj_metadata(void *obj);
t_dada_graph_metadata build_double_metadata(double num);
t_dada_graph_metadata build_vanillabox_metadata(t_symbol *type, long num_ins, long num_outs);
t_dada_graph_metadata build_outinnum_metadata(long num_out, long num_in);
t_dada_graph_metadata build_llllnode_metadata(t_llll *ll, t_jrgba bgcolor, t_jrgba bordercolor, t_jrgba textcolor);
t_dada_graph_metadata get_default_vertex_metadata(t_dada_graph *graph);
t_dada_graph_metadata get_default_edge_metadata(t_dada_graph *graph);
t_dada_graph_metadata clone_metadata(e_dada_graph_metadata_type type, t_dada_graph_metadata in);

void graph_free_all_metadata_lllls(t_dada_graph *graph);
void graph_free(t_dada_graph *graph);
void edge_free(t_dada_graph *graph, long edge_id);
void vertex_free(t_dada_graph *graph, long vertex_id);


#endif // _DADA_GRAPHS_H_

