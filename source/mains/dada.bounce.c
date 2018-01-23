/**
	@file
	dada.bounce.c
	
	@name
	dada.bounce
	
	@realname 
	dada.bounce

	@type
	object
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
	Bounce balls in 2D chambers
	
	@description
	Implements a geometrical bouncing chamber for balls traveling at constant speed.
    Each edge hit triggers musical data.
	
	@discussion
 
	@category
	dada, dada interfaces, dada geometry

	@keywords
	bounce, wall, chamber
	
	@seealso
	dada.kaleido, dada.bodies
	
	@owner
	Daniele Ghisi
*/


#include "dada.interface.h"
#include "dada.geometry.h"
#include "dada.paint.h"
#include "notation.h"
//#include "dada.cursors.data.c"
#include "dada.math.h"
#include "dada.graphs.h"
#include "dada.popupmenu.h"
#include "dada.undo.h"

#define DADA_BOUNCE_MAX_BALLS 64			///< Maximum number of balls allowed
											///  Must be less than or equal to 64 (otherwise change the #t_bounce_bitfield declaration) 

#define DADA_BOUNCE_ROTATION_INTERFACE_FACTOR (2 * TWO_PI)
#define DADA_BOUNCE_ROTATION_SCALE_FACTOR 100.

#define DADA_BOUNCE_BALL_SELECTION_PAD 4
#define DADA_BOUNCE_VERTEX_SELECTION_PAD 6
#define DADA_BOUNCE_EDGE_SELECTION_PAD 4
#define DADA_BOUNCE_DEFAULT_TONEDIVISION 4
#define DADA_BOUNCE_DEFAULT_SPEED (build_pt(100, 0))

#define DADA_BOUNCE_NOTEPOPUP_WIDTH 50
#define DADA_BOUNCE_NOTEPOPUP_HEIGHT 70

#define DADA_BOUNCE_MAX_MIDICHANNELS 257 // 0th is actually unused, we keep them 1-based


typedef t_uint64 t_bounce_bitfield;		///< A bitfield with each bit corresponding to a bouncing ball


////////////////////////// structures


typedef enum _bounce_pitch_display_type
{
	DADA_BOUNCE_PITCH_DISPLAY_NONE = 0,		///< Don't display pitch bounce
	DADA_BOUNCE_PITCH_DISPLAY_POINT = 1,		///< Display a single point
	DADA_BOUNCE_PITCH_DISPLAY_NOTENAME = 2,	///< Display the note name
	DADA_BOUNCE_PITCH_DISPLAY_NOTE = 3,		///< Display the whole note
} e_bounce_pitch_display_type;

typedef enum _bounce_pitch_mode
{
	DADA_BOUNCE_EDGES_HAVE_METADATA = 0,
	DADA_BOUNCE_VERTICES_HAVE_METADATA = 1,
} e_bounce_pitch_mode;

typedef enum _bounce_metadata_type
{
    DADA_BOUNCE_METADATA_PITCHNVEL = 0,
    DADA_BOUNCE_METADATA_SCORE = 1,
} e_bounce_metadata_type;


typedef struct _collision
{
	long	edge_idx;
	t_pt	collision_pt;
} t_collision;



typedef struct _bounce 
{
	t_dadaobj_jbox		b_ob; // root object

    char                metadata_type;
    
	// balls
	t_dada_ball			*balls;
	double				ball_size; // not the size of the array, the size of the actual ball

	// room and graph
	t_dada_graph		room_graph;	///< The graph representing the bouncing room
	double				room_vertex_size;
	double				room_edge_linewidth;
	long                pitch_mode;
    char                use_ball_idx_as_channel;
	
	// playback
	char				output_bounce_data;
    char                send_noteoffs;
    double              currently_played_note[DADA_BOUNCE_MAX_MIDICHANNELS];
	long				tonedivision;
	char				velocities_depend_on_normal_speed_components;
	
	// display
	e_bounce_pitch_display_type	show_pitch;	///< How do we show pitches
	char			show_balls;
	char			show_room;
	char			show_speed;
	double			speed_display_factor;
    t_jrgba			j_roomcolor;

	// blinking while playing
    long            hit_edge;
    double          blink_time;
    
    // utilities
	char			firsttime;
	char			itsme;
	char			creating_new_obj;
	
	long			n_in;   // space for the inlet number used by all the proxies
    void			*n_proxy1;
	
	// outlets are declared in the dadaobj->llllobj structure, at the beginning
} t_bounce;



///////////////////////// function prototypes
//// standard set
void *bounce_new(t_symbol *s, long argc, t_atom *argv);
void bounce_free(t_bounce *x);
void bounce_assist(t_bounce *x, void *b, long m, long a, char *s);

void bounce_paint(t_bounce *x, t_object *view);


void bounce_int(t_bounce *x, t_atom_long num);
void bounce_float(t_bounce *x, double num);
void bounce_anything(t_bounce *x, t_symbol *msg, long ac, t_atom *av);
void bounce_bang(t_bounce *x);


// get/set status
void bounce_set_state(t_bounce *x, t_llll *state);
t_llll *bounce_get_state_sel(t_bounce *x, char get_bounce, char get_testers);
t_llll *bounce_get_state(t_bounce *x);

t_llll *bounce_get_room(t_bounce *x);
t_llll *bounce_get_balls(t_bounce *x);
void bounce_set_room(t_bounce *x, t_llll *geometry);
void bounce_set_balls(t_bounce *x, t_llll *balls);

long bounce_add_ball(t_bounce *x, t_llll *ball);


// interface
void bounce_focusgained(t_bounce *x, t_object *patcherview);
void bounce_focuslost(t_bounce *x, t_object *patcherview);
void bounce_mousedown(t_bounce *x, t_object *patcherview, t_pt pt, long modifiers);
void bounce_mousemove(t_bounce *x, t_object *patcherview, t_pt pt, long modifiers);
void bounce_mouseup(t_bounce *x, t_object *patcherview, t_pt pt, long modifiers);
void bounce_mousedrag(t_bounce *x, t_object *patcherview, t_pt pt, long modifiers);
long bounce_key(t_bounce *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
long bounce_keyup(t_bounce *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
void bounce_mousewheel(t_bounce *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc);

void bounce_mouseenter(t_bounce *x, t_object *patcherview, t_pt pt, long modifiers);
void bounce_mouseleave(t_bounce *x, t_object *patcherview, t_pt pt, long modifiers);

t_max_err bounce_notify(t_bounce *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void bounce_jsave(t_bounce *x, t_dictionary *d);
void bounce_preset(t_bounce *x);
void bounce_begin_preset(t_bounce *x, t_symbol *s, long argc, t_atom *argv);
void bounce_restore_preset(t_bounce *x, t_symbol *s, long argc, t_atom *argv);
void bounce_end_preset(t_bounce *x);

t_max_err bounce_setattr_tonedivision(t_bounce *x, t_object *attr, long ac, t_atom *av);
t_max_err bounce_setattr_type(t_bounce *x, t_object *attr, long ac, t_atom *av);

// UNDO
void bounce_undo_step_push_balls(t_bounce *x, t_symbol *operation);
void bounce_undo_step_push_room(t_bounce *x, t_symbol *operation);
void bounce_undo_step_push(t_bounce *x, t_symbol *operation);
void bounce_postprocess_undo(t_bounce *x);

// sequencing
void bounce_stop(t_bounce *x, t_symbol *s, long argc, t_atom *argv);
void bounce_play(t_bounce *x, t_symbol *s, long argc, t_atom *argv);
void bounce_task(t_bounce *x);
void bounce_clock(t_bounce *x, t_symbol *s);




///////////////////////// utility functions



void send_all_noteoffs(t_bounce *x)
{
    long i;
    long num_balls = dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_BALL);
    for (i = 0; i < num_balls; i++) {
        long MIDIchannel = x->balls[i].channel;
        double currently_played_note = currently_played_note = x->currently_played_note[MIDIchannel];
        if (currently_played_note) {
            // sending note off
            t_llll *ll = llll_get();
            llll_appenddouble(ll, currently_played_note, 0, WHITENULL_llll);
            llll_appendlong(ll, 0, 0, WHITENULL_llll);
            llll_appendlong(ll, MIDIchannel, 0, WHITENULL_llll);
            llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 3, ll);
            llll_free(ll);
            x->currently_played_note[MIDIchannel] = 0;
        }
    }
}

void append_playout_pitchnvel_data(t_bounce *x, t_llll *outlet2, t_llll *outlet3, double midicents, long velocity, long MIDIchannel, long ball_idx, t_pt hit_pt, long edge_id, long connected_component_id)
{
    double currently_played_note;
    if (x->send_noteoffs && MIDIchannel < DADA_BOUNCE_MAX_MIDICHANNELS && (currently_played_note = x->currently_played_note[MIDIchannel])) {
        // sending note off
        t_llll *ll = llll_get();
        llll_appenddouble(ll, currently_played_note, 0, WHITENULL_llll);
        llll_appendlong(ll, 0, 0, WHITENULL_llll);
        llll_appendlong(ll, MIDIchannel, 0, WHITENULL_llll);
        llll_appendobj(outlet3, ll);
//        llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 3, ll);
//        llll_free(ll);
        x->currently_played_note[MIDIchannel] = 0;
    }
    
	t_llll *ll = llll_get();
	llll_appenddouble(ll, midicents, 0, WHITENULL_llll);
	llll_appendlong(ll, velocity, 0, WHITENULL_llll);
	llll_appendlong(ll, MIDIchannel, 0, WHITENULL_llll);
    llll_appendobj(outlet3, ll);
//    llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 3, ll);
//    llll_free(ll);
  
    if (MIDIchannel < DADA_BOUNCE_MAX_MIDICHANNELS)
        x->currently_played_note[MIDIchannel] = midicents;

    if (x->output_bounce_data) {
        t_llll *bounceinfo = llll_get();
        llll_appendllll(bounceinfo, symbol_and_long_to_llll(gensym("ball"), ball_idx + 1));

        t_llll *position = llll_get();
        llll_appendsym(position, gensym("position"));
        llll_appenddouble(position, hit_pt.x);
        llll_appenddouble(position, hit_pt.y);
        llll_appendllll(bounceinfo, position);
        
        t_llll *speed = llll_get();
        llll_appendsym(speed, gensym("speed"));
        llll_appenddouble(speed, x->balls[ball_idx].speed.x);
        llll_appenddouble(speed, x->balls[ball_idx].speed.y);
        llll_appendllll(bounceinfo, speed);

        llll_appendllll(bounceinfo, symbol_and_long_to_llll(gensym("edge"), edge_id + 1));
        llll_appendllll(bounceinfo, symbol_and_long_to_llll(gensym("component"), connected_component_id + 1));

        llll_appendobj(outlet2, bounceinfo);
//        llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 2, bounceinfo);
//        llll_free(bounceinfo);
    }
}

// will also free score
void append_playout_score_data(t_bounce *x, t_llll *outlet2, t_llll *outlet3, t_llll *score, long ball_idx, t_pt hit_pt, long edge_id, long connected_component_id)
{
    llll_appendobj(outlet3, score);
//    llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 3, score);
//    llll_free(score);
    
    if (x->output_bounce_data) {
        t_llll *bounceinfo = llll_get();
        llll_appendllll(bounceinfo, symbol_and_long_to_llll(gensym("ball"), ball_idx + 1));
        
        t_llll *position = llll_get();
        llll_appendsym(position, gensym("position"));
        llll_appenddouble(position, hit_pt.x);
        llll_appenddouble(position, hit_pt.y);
        llll_appendllll(bounceinfo, position);
        
        t_llll *speed = llll_get();
        llll_appendsym(speed, gensym("speed"));
        llll_appenddouble(speed, x->balls[ball_idx].speed.x);
        llll_appenddouble(speed, x->balls[ball_idx].speed.y);
        llll_appendllll(bounceinfo, speed);
        
        llll_appendllll(bounceinfo, symbol_and_long_to_llll(gensym("edge"), edge_id + 1));
        llll_appendllll(bounceinfo, symbol_and_long_to_llll(gensym("component"), connected_component_id + 1));
        
        llll_appendobj(outlet2, bounceinfo);
//        llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 2, bounceinfo);
//        llll_free(bounceinfo);
    }
}


////////////////////// INTERFACE FOR DADA ITEMS


///// BALLS:

void postprocess_ball(t_dadaobj *r_ob)
{
	jbox_redraw((t_jbox *)r_ob->orig_obj);
}


// returns the new ball index if succesful, -1 otherwise
long duplicate_ball(t_bounce *x, long idx)
{
	bounce_undo_step_push_balls(x, gensym("Duplicate Ball"));
	long newidx = dadaitem_ball_duplicate(dadaobj_cast(x), idx, 0);
	if (newidx >= 0) {
		t_dada_ball *ball = (t_dada_ball *)dadaitem_from_type_and_idx(dadaobj_cast(x), DADAITEM_TYPE_BALL, newidx);
		if (ball) {
			ball->speed = x->balls[idx].speed;
			ball->channel = dadaitem_ball_find_max_channel(dadaobj_cast(x)) + 1;
			ball->r_it.color = dada_long_to_color(dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_BALL) - 1);
		}
	}
	return newidx;
}


///// GRAPH ELEMENTS

void postprocess_room(t_bounce *x)
{
	jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
	jbox_redraw((t_jbox *)x);
}

char delete_edge(t_bounce *x, long idx)
{
	bounce_undo_step_push_room(x, gensym("Delete Edge"));
	 
	if (!graph_delete_edge(&x->room_graph, idx)) {
		if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_EDGE && x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx == idx) {
			x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
			x->b_ob.d_ob.m_interface.mousemove_item_identifier.flag = 0;
		}
		
		if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_EDGE && x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx == idx) {
			x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADAITEM_TYPE_NONE;
			x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag = 0;
		}
		postprocess_room(x);
		return 0;
	}
	
	return 1;
}


char delete_vertex(t_bounce *x, long idx, char preserve_edges)
{
	bounce_undo_step_push_room(x, gensym("Delete Vertex"));
	
	if (!graph_delete_vertex(&x->room_graph, idx, preserve_edges)) {
		if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_VERTEX && x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx == idx) {
			x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
			x->b_ob.d_ob.m_interface.mousemove_item_identifier.flag = 0;
		}
		
		if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_VERTEX && x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx == idx) {
			x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADAITEM_TYPE_NONE;
			x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag = 0;
		}
		postprocess_room(x);
		return 0;
	}
	
	return 1;
}

char delete_connected_component(t_bounce *x, long idx)
{
	bounce_undo_step_push_room(x, gensym("Delete Figure"));
	if (!graph_delete_connected_component(&x->room_graph, idx)) {
		if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_CONNECTED_COMPONENT && x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx == idx) {
			x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
			x->b_ob.d_ob.m_interface.mousemove_item_identifier.flag = 0;
		}
		
		if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_CONNECTED_COMPONENT && x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx == idx) {
			x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADAITEM_TYPE_NONE;
			x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag = 0;
		}
		postprocess_room(x);
		return 0;
	}
	
	return 1;
}



t_dada_graph_metadata bounce_default_vertex_metadata(t_bounce *x)
{
    if (x->metadata_type == DADA_BOUNCE_METADATA_PITCHNVEL)
        return DADA_DEFAULT_VERTEX_PITCHNVEL_METADATA;
    else
        return DADA_DEFAULT_VERTEX_SCORE_METADATA;
}

t_dada_graph_metadata bounce_default_edge_metadata(t_bounce *x)
{
    if (x->metadata_type == DADA_BOUNCE_METADATA_PITCHNVEL)
        return DADA_DEFAULT_EDGE_PITCHNVEL_METADATA;
    else
        return DADA_DEFAULT_EDGE_SCORE_METADATA;
}



t_llll *symbol_and_long_couple_to_llll(t_symbol *sym, long n1, long n2)
{
    t_llll *ll = llll_get();
    llll_appendsym(ll, sym);
    llll_appendlong(ll, n1);
    llll_appendlong(ll, n2);
    return ll;
}


void notify_ball_add(t_bounce *x, long ball_idx)
{
    if (ball_idx >= 0) {
        t_llll *ll = llll_get();
        llll_appendsym(ll, gensym("addball"));
        llll_appendlong(ll, ball_idx + 1);
        llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, ll);
        llll_free(ll);
    }
}

void notify_edges_creation(t_bounce *x, t_symbol *operation, long old_edge, long new_added_edges_start_idx, long new_added_edges_end_idx)
{
    t_llll *ll = llll_get();
    llll_appendsym(ll, gensym("edge"));
    llll_appendsym(ll, operation);
    
    t_llll *ll_item = llll_get();
    llll_appendllll(ll_item, symbol_and_long_to_llll(gensym("edge"), old_edge + 1));
    llll_appendllll(ll_item, symbol_and_long_couple_to_llll(gensym("vertices"), x->room_graph.edges[old_edge].start + 1, x->room_graph.edges[old_edge].end + 1));
    llll_appendllll(ll_item, symbol_and_long_to_llll(gensym("component"), x->room_graph.vertices[x->room_graph.edges[old_edge].start].connected_component_idx + 1));
    llll_appendllll(ll, ll_item);
    
    long i;
    for (i = new_added_edges_start_idx; i >= 0 && i <= new_added_edges_end_idx; i++) {
        t_llll *ll_item2 = llll_get();
        llll_appendllll(ll_item2, symbol_and_long_to_llll(gensym("edge"), i + 1));
        llll_appendllll(ll_item2, symbol_and_long_couple_to_llll(gensym("vertices"), x->room_graph.edges[i].start + 1, x->room_graph.edges[new_added_edges_end_idx].end + 1));
        llll_appendllll(ll_item2, symbol_and_long_to_llll(gensym("component"), x->room_graph.vertices[x->room_graph.edges[i].start].connected_component_idx + 1));
        llll_appendllll(ll, ll_item2);
    }
    
    llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, ll);
    llll_free(ll);
}


void split_edge(t_bounce *x, long idx, t_pt split_point)
{
    long edge1_idx, edge2_idx;
    bounce_undo_step_push_room(x, gensym("Split Edge"));
    graph_split_edge(&x->room_graph, idx, split_point, &edge1_idx, &edge2_idx);
    if (edge1_idx && edge2_idx)
        notify_edges_creation(x, gensym("split"), idx, edge2_idx, edge2_idx);
    postprocess_room(x);
}


void subdivide_edge(t_bounce *x, long idx, long num_parts)
{
    long new_edges_start_idx, new_edges_end_idx;
	bounce_undo_step_push_room(x, gensym("Subdivide Edge"));
	graph_subdivide_edge(&x->room_graph, idx, num_parts, &new_edges_start_idx, &new_edges_end_idx);
    notify_edges_creation(x, gensym("subdivide"), idx, new_edges_start_idx, new_edges_end_idx);
	postprocess_room(x);
}

void extrude_edge(t_bounce *x, long idx)
{
    long new_edges_start_idx, new_edges_end_idx;
	bounce_undo_step_push_room(x, gensym("Extrude Edge"));
	graph_extrude_edge(&x->room_graph, idx, &new_edges_start_idx, &new_edges_end_idx);
    notify_edges_creation(x, gensym("extrude"), idx, new_edges_start_idx, new_edges_end_idx);
	postprocess_room(x);
}

void move_vertex(t_bounce *x, long idx, t_pt new_coord, char from_interface)
{
	bounce_undo_step_push_room(x, gensym("Move Vertex"));
	t_pt new_processed_coord = x->room_graph.vertices[idx].r_it.coord;
	if (from_interface)
		drag_coord(dadaobj_cast(x), &new_processed_coord, new_coord, true);
	else
		new_processed_coord = new_coord;

	graph_move_vertex(&x->room_graph, idx, new_processed_coord);
	
	postprocess_room(x);
}

void move_vertex_delta(t_bounce *x, long idx, t_pt delta_coord, char from_interface)
{
    bounce_undo_step_push_room(x, gensym("Move Vertex"));
    t_pt delta_coord_processed = delta_coord;
    if (from_interface)
        drag_coord_delta(dadaobj_cast(x), &delta_coord_processed, true);
    
    graph_move_vertex_delta(&x->room_graph, idx, delta_coord_processed);
    
    postprocess_room(x);
}


void move_edge_delta(t_bounce *x, long idx, t_pt delta_coord, char from_interface)
{
	bounce_undo_step_push_room(x, gensym("Move Edge"));
	t_pt delta_coord_processed = delta_coord;
	if (from_interface)
		drag_coord_delta(dadaobj_cast(x), &delta_coord_processed, true);
	
	graph_move_edge_delta(&x->room_graph, idx, delta_coord_processed);

	postprocess_room(x);
}


void move_connected_component_delta(t_bounce *x, long idx, t_pt delta_coord, char from_interface)
{
	bounce_undo_step_push_room(x, gensym("Move Figure"));
	t_pt delta_coord_processed = delta_coord;
	if (from_interface)
		drag_coord_delta(dadaobj_cast(x), &delta_coord_processed, true);
	
	graph_move_connected_component_delta(&x->room_graph, idx, delta_coord_processed);
	
	postprocess_room(x);
}





	
//////////////////////// global class pointer variable
t_class *bounce_class;

int C74_EXPORT main(void)
{	
	t_class *c;
	
	common_symbols_init();
	llllobj_common_symbols_init();
	
	srand(time(NULL)); // needed for the shake function

	if (dada_check_bach_version() || llllobj_test()) {
		dada_error_bachcheck();
		return 1;
	}


	CLASS_NEW_CHECK_SIZE(c, "dada.bounce", (method)bounce_new, (method)bounce_free, (long)sizeof(t_bounce), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, 0);
	
    
	// paint & utilities
	class_addmethod(c, (method) bounce_paint,			"paint", A_CANT, 0);
	class_addmethod(c, (method) bounce_assist,			"assist",		A_CANT, 0);  
	class_addmethod(c, (method)	bounce_notify,			"bachnotify",		A_CANT,		0);

	// save & preset
    class_addmethod(c, (method) bounce_preset, "preset", 0);
    class_addmethod(c, (method) bounce_begin_preset, "begin_preset", A_GIMME, 0);
    class_addmethod(c, (method) bounce_restore_preset, "restore_preset", A_GIMME, 0);
    class_addmethod(c, (method) bounce_end_preset, "end_preset", 0);
	CLASS_METHOD_ATTR_PARSE(c, "begin_preset", "undocumented", gensym("long"), 0L, "1");
	CLASS_METHOD_ATTR_PARSE(c, "restore_preset", "undocumented", gensym("long"), 0L, "1");
	CLASS_METHOD_ATTR_PARSE(c, "end_preset", "undocumented", gensym("long"), 0L, "1");
	class_addmethod(c, (method) bounce_jsave, "jsave", A_CANT, 0);
	
	// interface
	class_addmethod(c, (method) bounce_focusgained, "focusgained", A_CANT, 0);
	class_addmethod(c, (method) bounce_focuslost, "focuslost", A_CANT, 0); 	

    // @method (mouse) @digest Edit content
    // @description
    // @copy DADA_DOC_MOUSE_COMMANDS_STANDARD_NAVIGATION
    // • <m>click+drag</m> on an element ot move it<br />
    //    ↪ Add the <m>Alt</m> key to duplicate it<br />
    // • <m>Cmd+click</m> (mac) or <m>Ctrl+click</m> (win) on to delete it<br />
    // • <m>right click</m> or <m>two fingers tap</m>: open contextual menu<br />
    class_addmethod(c, (method) bounce_mousedown, "mousedown", A_CANT, 0);
	class_addmethod(c, (method) bounce_mousedrag, "mousedrag", A_CANT, 0);
	class_addmethod(c, (method) bounce_mouseup, "mouseup", A_CANT, 0);
    
    // @method (keyboard) @digest Edit content or play
    // @description
    // @copy DADA_DOC_KEYBOARDS_COMMANDS_STANDARD_NAVIGATION
    // • <m>Cmd+Z</m> (mac) or <m>Ctrl+Z</m> (win): perform undo step<br />
    // • <m>Cmd+Shift+Z</m> (mac) or <m>Ctrl+Y</m> (win): perform redo step<br />
    // • <m>Spacebar</m>: toggle play<br />
  	class_addmethod(c, (method) bounce_key, "key", A_CANT, 0);
  	class_addmethod(c, (method) bounce_keyup, "keyup", A_CANT, 0);
    
    
    // @method (tools) @digest Navigate or edit content
    // @description
    // @copy DADA_DOC_TOOLS_INTRO
    // @copy DADA_DOC_TOOLS_ZX
    // @copy DADA_DOC_TOOLS_NV
    // @copy DADA_DOC_TOOLS_SR
    // @copy DADA_DOC_TOOLS_Q
    // @copy DADA_DOC_TOOLS_L
	class_addmethod(c, (method) bounce_mousemove, "mousemove", A_CANT, 0);
	class_addmethod(c, (method) bounce_mouseenter, "mouseenter", A_CANT, 0);
	class_addmethod(c, (method) bounce_mouseleave, "mouseleave", A_CANT, 0);
	class_addmethod(c, (method) bounce_mousewheel, "mousewheel", A_CANT, 0);
	
	// @method bang @digest Perform single step
	// @description Performs a single step of movement.
	class_addmethod(c, (method)bounce_bang,			"bang",			0);

	// @method move @digest Translate elements
	// @description The word <m>move</m> followed by an element type (either <m>vertex</m> or
    // <m>edge</m> or <m>component</m> or <m>ball</m>), followed by the index of a shape or ball and a
    // vector in wrapped <b>(<m>x</m> <m>y</m>)</b> syntax,
	// translates the element by the given vector.
    // @marg 0 @name element_type @optional 0 @type symbol
    // @marg 1 @name element_index @optional 0 @type long
    // @marg 2 @name delta_coord @optional 0 @type llll
    // @example move component 1 (10 10) @caption Move the 1st connected component by (10, 10)
    // @example move vertex 5 (-4 0) @caption Move the 5th vertex by (-4, 0)
    // @example move edge 3 (0 10) @caption Shift 2nd edge up by 10
    // @example move ball 1 (0 10) @caption Shift 1st ball up by 10
    class_addmethod(c, (method)bounce_anything,	"move",		A_GIMME,	0);

    // @method rotate @digest Rotate elements
    // @description The word <m>rotate</m> followed by an element type (either <m>component</m> or <m>ball</m>),
    // followed by the index of a shape and an angle in radians
    // rotates the element by the given angle. If the angle is terminates with the degrees ° symbol after the number (without any spaces)
    // or if it is given as an llll of the form <b>(<m>angle</m> deg)</b>,
    // then the angle is assumed to be in degrees.
    // @marg 0 @name element_type @optional 0 @type symbol
    // @marg 1 @name element_index @optional 0 @type long
    // @marg 2 @name angle @optional 0 @type number/llll
    // @example rotate component 1 2 @caption Rotate the 1st connected component by 2 radians
    // @example rotate ball 1 (30 deg) @caption Rotate the 1st ball by 30 degrees
    class_addmethod(c, (method)bounce_anything,	"rotate",		A_GIMME,	0);
    
    // @method scale @digest Scale elements
    // @description The word <m>scale</m> followed by an element type (either <m>component</m> or <m>ball</m>),
    // followed by the index of a shape and a floating point number,
    // scales the element by the given number.
    // @marg 0 @name element_type @optional 0 @type symbol
    // @marg 1 @name element_index @optional 0 @type long
    // @marg 2 @name factor @optional 0 @type number
    // @example scale ball 3 4 @caption Scale 3rd ball velocity by 4
    // @example scale component 1 0.5 @caption Shrink 1st connected component by 2
    class_addmethod(c, (method)bounce_anything,	"scale",		A_GIMME,	0);
    
    
    // @method addball @digest Add a ball
    // @description Adds a new ball in the room. The correct syntax is:
    // <b>addball <m>BALL_SYNTAX</m></b>, where the ball syntax is the one
    // documented in the <m>dump</m> message. The ball syntax should NOT be wrapped in parenthesis.
    // For instance, a valid message is: <b>addball (coord -90. 20.) (speed 100. 30.) (color 0.4 0. 0. 1.)</b>
    // After the ball has been added, a notification is sent through the second outlet in the form
    // <b>addball <m>ball_index</m></b>.
    // @marg 0 @name ball_syntax @optional 0 @type llll
    class_addmethod(c, (method)bounce_anything,	"addball",		A_GIMME,	0);

    
    // @method deleteball @digest Delete a ball
    // @description Deletes the <m>N</m>-th ball, where N is the specified index argument.
    // @marg 0 @name index @optional 0 @type long
    class_addmethod(c, (method)bounce_anything,	"deleteball",	A_GIMME,	0);
    
    
    // @method split @digest Split edges
    // @description The word <m>split</m> followed by the <m>edge</m> symbol,
    // by the index of the edge to be split, and by the wrapped llll with the
    // splitting <b>(<m>x</m> <m>y</m>)</b> coordinates, splits the given edge
    // at the specified point, and outputs a notification through the second outlet
    // containing the <m>edge split</m> symbols, plus the sequence of newly created edges.
    // @marg 0 @name edge @optional 0 @type symbol
    // @marg 1 @name edge_index @optional 0 @type long
    // @marg 2 @name split_point @optional 0 @type llll
    // @example split edge 3 (-40 0) @caption Split 3rd edge by adding a point at (-40, 0)
    class_addmethod(c, (method)bounce_anything,	"split",		A_GIMME,	0);

    
    // @method meta @digest Assign metadata
    // @description The word <m>meta</m>, followed by the <m>edge</m> symbol or the <m>vertex</m> symbol,
    // and the edge or vertex index, assigns metadata to a vertex or an edge.
    // The metadata should be contained in the llll specified as
    // further argument.
    // If the metadata <m>type</m> is set to "Pitch and velocity", such llll should contain a specification such as <b>(pitch <m>mc</m>)</b> and/or
    // <b>(velocity <m>vel</m>)</b>.
    // If the metadata <m>type</m> is set to "Scores", such llll should be the score itself.
    // @marg 0 @name element_type @optional 0 @type symbol
    // @marg 1 @name element_index @optional 0 @type long
    // @marg 2 @name metadata @optional 0 @type llll
    // @example meta edge 5 (pitch 6300) (vel 80) @caption Assign a pitch of 6300 cents and a velocity of 80 as metadata for 5th edge
    // @example meta vertex 4 (pitch 6300) (vel 80) @caption The same, for 4th vertex
    // @example meta edge 1 (score roll ((200 (7200. 405. 100)) (700 (6300. 405. 100)))) @caption Assign a bach.roll syntax as score metadata for edge 1
    // @example meta edge 1 (score score (((( 4 4 ) (( 1/4 120 ))) ( 1 ( 4700. 100 0 ))))) @caption Assign a bach.score syntax as score metadata for edge 1
    class_addmethod(c, (method)bounce_anything,	"meta",		A_GIMME,	0);
    
    
    // @method subdivide @digest Subdivide edges
    // @description The word <m>subdivide</m> followed by the <m>edge</m> symbol,
    // by the index of the edge to be subdivide, and by an integer number, subdivides the given edge
    // into the specified number of new segments, and outputs a notification through the second outlet
    // containing the <m>edge subdivide</m> symbols, plus the sequence of newly created edges.
    // @marg 0 @name edge @optional 0 @type symbol
    // @marg 1 @name edge_index @optional 0 @type long
    // @marg 2 @name num_subdivisions @optional 0 @type long
    // @example subdivide edge 5 4 @caption Subdivide 5th edge into 4 parts
    class_addmethod(c, (method)bounce_anything,	"subdivide",		A_GIMME,	0);

    
	// @method flush @digest Send all note-offs
	// @description The word <m>flush</m> force all the note-offs for notes being played to be sent. 
	// This is effective only when the <m>play</m> attribute is set to 1.
	class_addmethod(c, (method)bounce_anything,	"flush",		A_GIMME,	0);

    
    // @method clear @digest Clear elements
    // @description The word <m>clear</m> force all elements to be deleted.
    // A first argument limits the elements to be dumped.
    // The <m>clear room</m> message only clears the room state; the <m>clear balls</m> message only clears the balls state. <br />
    // @marg 0 @name what @optional 1 @type symbol
    class_addmethod(c, (method)bounce_anything,	"clear",		A_GIMME,	0);


    // @method dump @digest Output state
    // @description Outputs the current state of the object. The syntax is
    // <b>bounce (room <m>GRAPH</m>) (balls <m>BALL1</m> <m>BALL2</m>...)</b>.
    // each ball is in the syntax
    // <b>(coord <m>x</m> <m>y</m>) (speed <m>x</m> <m>y</m>) (color <m>r</m> <m>g</m> <m>b</m> <m>a</m>)
    // (channel <m>MIDIchannel</m>) (flags <m>flags</m>)</b>. <br />
    // A first argument limits the elements to be dumped.
    // The <m>dump room</m> message only dumps the room state; the <m>dump balls</m> message only dumps the balls state. <br />
    // @copy DADA_DOC_SYNTAX_GRAPH
    // @copy DADA_DOC_SYNTAX_FLAGS
    // @marg 0 @name what @optional 1 @type symbol
    class_addmethod(c, (method)bounce_anything,	"dump",		A_GIMME,	0);
    
    // @method llll @digest Set state
    // @description Sets the current state of the object. The syntax must follow the one described in the
    // <m>dump</m> message documentation (although room only or balls only can be assigned).
	class_addmethod(c, (method)bounce_anything,	"anything",			A_GIMME,	0);
	class_addmethod(c, (method)bounce_anything,	"setstoredstate",	A_GIMME, 0);


    // @method notes @digest Assign pitches and velocities
    // @description When <m>type</m> is set to "Pitch and Velocity", the <m>notes</m> message assigns
    // a pitch and velocity to each of the edges. An llll of type <b>(<m>pitch</m> <m>vel</m>) (<m>pitch</m> <m>vel</m>)...</b>
    // is expected as argument.
    // @marg 0 @name pitch_and_vels @optional 0 @type llll
    class_addmethod(c, (method)bounce_anything,	"notes",			A_GIMME,	0);

    // @method scores @digest Assign scores
    // @description When <m>type</m> is set to "Scores", the <m>scores</m> message assigns
    // a score to each of the edges. An llll of type <b>(<m>SCORE1</m>) (<m>SCORE2</m>)...</b>
    // is expected as argument, where each <m>SCORE</m> is usually a <o>bach.roll</o> or <o>bach.score</o> gathered syntax,
    // but can also be any other llll.
    // @marg 0 @name scores @optional 0 @type llll
    class_addmethod(c, (method)bounce_anything,	"scores",			A_GIMME,	0);

    // @method domain @digest Set the X domain
    // @description The <m>domain</m> message, followed by two numbers, sets minimum and maximum coordinates
    // to be displayed on the X axis.
    // The <m>domain</m> message,  followed by the "start" or "end" symbol and a number, sets the coordinate
    // to be displayed respectively at the left boundary or at the right boundary of the object box.
    // @marg 0 @name arguments @optional 0 @type list
    class_addmethod(c, (method)bounce_anything,		"domain",		A_GIMME,	0);
    
    // @method range @digest Set the Y range
    // @description The <m>range</m> message, followed by two numbers, sets minimum and maximum coordinates
    // to be displayed on the Y axis
    // The <m>range</m> message,  followed by the "start" or "end" symbol and a number, sets the coordinate
    // to be displayed respectively at the bottom boundary or at top right boundary of the object box.
    // @marg 0 @name arguments @optional 0 @type list
    class_addmethod(c, (method)bounce_anything,		"range",		A_GIMME,	0);
    
    
    // @method getdomain @digest Retrieve current X domain
    // @description The <m>getdomain</m> message outputs from the third outlet the minimum and maximum
    // coordinates displayed on the X axis, preceded by a <m>domain</m> symbol.
    class_addmethod(c, (method)bounce_anything,		"getdomain",		A_GIMME,	0);
    
    
    // @method getrange @digest Retrieve current Y range
    // @description The <m>getrange</m> message outputs from the third outlet the minimum and maximum
    // coordinates displayed on the Y axis, preceded by a <m>range</m> symbol.
    class_addmethod(c, (method)bounce_anything,		"getrange",		A_GIMME,	0);
    

    // @method int @digest Play/Stop
    // @description A non-zero integer triggers a <m>play</m> message, a zero integer triggers a <m>stop</m> message
    class_addmethod(c, (method)bounce_int, "int", A_LONG, 0);


    
	// @method play @digest Start sequencing
	// @description Starts the sequencing engine.
	class_addmethod(c, (method)bounce_play,	"play",		A_GIMME,	0);

	// @method stop @digest Stop sequencing
	// @description Stops the sequencing engine.
	class_addmethod(c, (method)bounce_stop,	"stop",		A_GIMME,	0);
	
	
	// @method clock @digest Select a clock source
	// @description The word <m>clock</m>, followed by the name of an existing <m>setclock</m> objects, sets the <o>dada.bounce</o> 
	// object to be controlled by that <m>setclock</m> object rather than by Max's internal millisecond clock. 
	// The word <m>clock</m> by itself sets the object back to using Max's regular millisecond clock.
	class_addmethod(c, (method) bounce_clock,	"clock", A_DEFSYM, 0);

  

    DADAOBJ_JBOX_DECLARE_READWRITE_METHODS(c);
    DADAOBJ_JBOX_DECLARE_ACCEPTSDRAG_METHODS(c);

	llllobj_class_add_out_attr(c, LLLL_OBJ_UI);
	dadaobj_class_init(c, LLLL_OBJ_UI, DADAOBJ_BBGIMAGE | DADAOBJ_ZOOM | DADAOBJ_CENTEROFFSET | DADAOBJ_EMBED | DADAOBJ_MOUSEHOVER | DADAOBJ_GRID | DADAOBJ_LABELS | DADAOBJ_SNAPTOGRID | DADAOBJ_AXES | DADAOBJ_UNDO | DADAOBJ_PLAY | DADAOBJ_NOTIFICATIONS | DADAOBJ_BORDER | DADAOBJ_BORDER_SHOWDEFAULT);

	
	CLASS_ATTR_DEFAULT(c, "patching_rect", 0, "0 0 300 300");
	// @exclude dada.bounce
	CLASS_ATTR_DEFAULT(c, "presentation_rect", 0, "0 0 300 300");
	// @exclude dada.bounce
	

	CLASS_STICKY_ATTR(c,"category",0,"Color");

	CLASS_ATTR_RGBA(c, "roomcolor", 0, t_bounce, j_roomcolor);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "roomcolor", 0, "0.3 0.3 0.3 1.");
	CLASS_ATTR_STYLE_LABEL(c, "roomcolor", 0, "rgba", "Room Color");
	CLASS_ATTR_BASIC(c, "roomcolor", 0);
	// @description Sets the color of the graph constituting the room.

	CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	
	CLASS_STICKY_ATTR(c,"category",0,"Behavior");

    CLASS_ATTR_CHAR(c, "noteoff", 0, t_bounce, send_noteoffs);
    CLASS_ATTR_STYLE_LABEL(c, "noteoff", 0, "onoff", "Send Noteoff Information");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"noteoff",0,"1");
    CLASS_ATTR_BASIC(c, "noteoff", 0);
    // @description Toggles the ability to send the noteoff information for a previous edge, once a ball hits a new one.

	CLASS_ATTR_CHAR(c, "bouncedata", 0, t_bounce, output_bounce_data);
    CLASS_ATTR_STYLE_LABEL(c, "bouncedata", 0, "onoff", "Output Bounce Data");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"bouncedata",0,"1");
    // @description Toggles the ability to output bounce information from third outlet.

	CLASS_ATTR_CHAR(c, "speedvel", 0, t_bounce, velocities_depend_on_normal_speed_components);
    CLASS_ATTR_STYLE_LABEL(c, "speedvel", 0, "onoff", "Velocities Depend On Normal Speed");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"speedvel",0,"1");
    // @description Toggles the ability to rescale velocities depending on the normal component of the
    // speed of the ball bouncing on an edge.
	
	CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	CLASS_STICKY_ATTR(c,"category",0,"Settings");


    CLASS_ATTR_LONG(c,"type",0, t_bounce, metadata_type);
    CLASS_ATTR_STYLE_LABEL(c,"type",0,"enumindex","Metadata Type");
    CLASS_ATTR_ENUMINDEX(c,"type", 0, "Pitch And Velocity Scores");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"type", 0, "0");
    CLASS_ATTR_ACCESSORS(c, "type", (method)NULL, (method)bounce_setattr_type);
    // @description Sets the graph metadata type: either a combination of pitch and velocity (simple case)
    // or a complex score.
    
    
	CLASS_ATTR_LONG(c,"mode",0, t_bounce, pitch_mode);
	CLASS_ATTR_STYLE_LABEL(c,"mode",0,"enumindex","Metadata Mode");
	CLASS_ATTR_ENUMINDEX(c,"mode", 0, "Edges Have Metadata Vertices Have Metadata");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"mode", 0, "0");
    // @description Sets the graph metadata mode: either edges have pitch and velocity information (0), or
    // vertices do (1). In this case, when a ball hits an edge, the resulting pitch/velocity will be the
    // appropriate interpolation of the vertices' pitches.
	
    
    CLASS_ATTR_CHAR(c,"indexaschannel",0, t_bounce, use_ball_idx_as_channel);
    CLASS_ATTR_STYLE_LABEL(c,"indexaschannel",0,"onoff","Use Ball Index As Channel");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"indexaschannel",0,"0");
    // @description If active, the output MIDI channel is NOT the ball midichannel, rather the ball index.

	CLASS_ATTR_CHAR(c, "tonedivision", 0, t_bounce, tonedivision);
    CLASS_ATTR_STYLE_LABEL(c, "tonedivision", 0, "text", "Microtonal Division");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"tonedivision",0,"2");
	CLASS_ATTR_ACCESSORS(c, "tonedivision", (method)NULL, (method)bounce_setattr_tonedivision);
    // @description @copy BACH_DOC_TONEDIVISION

		
	CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	CLASS_STICKY_ATTR(c,"category",0,"Appearance");
	
	CLASS_ATTR_CHAR(c, "showballs", 0, t_bounce, show_balls);
    CLASS_ATTR_STYLE_LABEL(c, "showballs", 0, "onoff", "Show Balls");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showballs",0,"3");
    // @descriptions Toggles the ability to display the balls.

	CLASS_ATTR_CHAR(c, "showspeed", 0, t_bounce, show_speed);
    CLASS_ATTR_STYLE_LABEL(c, "showspeed", 0, "onoff", "Show Ball Speed");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showspeed",0,"1");
    // @descriptions Toggles the ability to display the ball speed.

	CLASS_ATTR_DOUBLE(c, "speeddisplayfactor", 0, t_bounce, speed_display_factor);
    CLASS_ATTR_STYLE_LABEL(c, "speeddisplayfactor", 0, "text", "Speed Display Factor");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"speeddisplayfactor",0,"0.2");
    // @descriptions Sets the display factor for the ball speed.

	CLASS_ATTR_CHAR(c, "showroom", 0, t_bounce, show_room);
    CLASS_ATTR_STYLE_LABEL(c, "showroom", 0, "onoff", "Show Room");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showroom",0,"1");
    // @descriptions Toggles the ability to show the room graph.
	
	CLASS_ATTR_DOUBLE(c, "ballsize", 0, t_bounce, ball_size);
    CLASS_ATTR_STYLE_LABEL(c, "ballsize", 0, "text", "Ball Size");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"ballsize",0,"3.");
    // @descriptions Sets the size of each ball.

	CLASS_ATTR_DOUBLE(c, "vertexsize", 0, t_bounce, room_vertex_size);
    CLASS_ATTR_STYLE_LABEL(c, "vertexsize", 0, "text", "Room Vertex Size");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"vertexsize",0,"4.");
    // @descriptions Sets the size of each vertex.

	CLASS_ATTR_DOUBLE(c, "edgewidth", 0, t_bounce, room_edge_linewidth);
    CLASS_ATTR_STYLE_LABEL(c, "edgewidth", 0, "text", "Room Edge Line Width");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"edgewidth",0,"1.5");
    // @descriptions Sets the edge width.

    CLASS_ATTR_DOUBLE(c, "blinktime", 0, t_bounce, blink_time);
    CLASS_ATTR_STYLE_LABEL(c, "blinktime", 0, "text", "Blinking Time");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"blinktime",0,"200");
    // @description Sets the blinking time of the played edges in milliseconds

	CLASS_STICKY_ATTR_CLEAR(c, "category");

		
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	bounce_class = c;

	dev_post("dada.bounce compiled %s %s", __DATE__, __TIME__);
	return 0;
}

t_max_err bounce_notify(t_bounce *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	if (msg == _sym_attr_modified) {
		t_symbol *attr_name = (t_symbol *)object_method((t_object *)data, _sym_getname);
		if (attr_name == _llllobj_sym_zoom || attr_name == gensym("center") || attr_name == gensym("roomcolor") ) {
			jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
			jbox_redraw((t_jbox *)x);
		} else if (attr_name == gensym("grid")) {
			jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
			jbox_redraw((t_jbox *)x);
		}
	}
	
	return MAX_ERR_NONE;
}

t_max_err bounce_setattr_type(t_bounce *x, t_object *attr, long ac, t_atom *av)
{
    if (ac && av && is_atom_number(av)) {
        long new_type = atom_getlong(av);
        if (new_type != x->metadata_type) {
            x->metadata_type = new_type;
            graph_free_all_metadata_lllls(&x->room_graph);
            if (x->metadata_type == DADA_BOUNCE_METADATA_SCORE)
                x->room_graph.edge_metadata_type = x->room_graph.vertex_metadata_type = DADA_GRAPH_METADATA_SCORE;
            else
                x->room_graph.edge_metadata_type = x->room_graph.vertex_metadata_type = DADA_GRAPH_METADATA_PITCHNVEL;
            graph_assign_all_default_metadata(&x->room_graph);
        }
    }
    return MAX_ERR_NONE;
}

t_max_err bounce_setattr_tonedivision(t_bounce *x, t_object *attr, long ac, t_atom *av)
{
	if (ac && av && is_atom_number(av)) {
		x->tonedivision = MAX(2, atom_getlong(av));
		if (x->tonedivision != 2 && x->tonedivision != 4 && x->tonedivision != 8)
			object_warn((t_object *)x, "Only 2, 4 and 8 tonedivision are graphically supported.");
	}
	return MAX_ERR_NONE;
}


void bounce_begin_preset(t_bounce *x, t_symbol *s, long argc, t_atom *argv)
{
	dadaobj_begin_preset(dadaobj_cast(x), s, argc, argv);
}


void bounce_restore_preset(t_bounce *x, t_symbol *s, long argc, t_atom *argv)
{
	dadaobj_restore_preset(dadaobj_cast(x), s, argc, argv);
}

void bounce_end_preset(t_bounce *x)
{
	dadaobj_end_preset(dadaobj_cast(x));
}

void bounce_preset(t_bounce *x) {
	dadaobj_preset(dadaobj_cast(x));
}


void bounce_jsave(t_bounce *x, t_dictionary *d)
{
	if (x->b_ob.d_ob.save_data_with_patcher){
		if (x->b_ob.r_ob.l_dictll) {
			llll_store_in_dictionary(x->b_ob.r_ob.l_dictll, d, "bounce_data", NULL);
		} else {
			t_llll *data = bounce_get_state(x);
			llll_store_in_dictionary(data, d, "bounce_data", NULL);
			llll_free(data);
		}
	} 
}
		

void bounce_set_scores(t_bounce *x, t_llll *ll)
{
    long i;
    t_llllelem *elem;
    if (x->pitch_mode == DADA_BOUNCE_EDGES_HAVE_METADATA) {
        for (i = 0, elem = ll->l_head; elem && i < x->room_graph.num_edges; i++, elem = elem->l_next) {
            if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
                t_llll *subll = hatom_getllll(&elem->l_hatom);
                if (subll) {
                    llll_free(x->room_graph.edges[i].data.m_llllscore.ll);
                    x->room_graph.edges[i].data.m_llllscore.ll = llll_clone(subll);
                }
            }
        }
    }
}


void bounce_set_pitchandvel(t_bounce *x, t_llll *ll)
{
	long i;
	t_llllelem *elem;
	if (x->pitch_mode == DADA_BOUNCE_EDGES_HAVE_METADATA) { 
		for (i = 0, elem = ll->l_head; elem && i < x->room_graph.num_edges; i++, elem = elem->l_next) {
			if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
				t_llll *subll = hatom_getllll(&elem->l_hatom);
				if (subll && subll->l_head && is_hatom_number(&subll->l_head->l_hatom)) {
					x->room_graph.edges[i].data.m_pitchnvel.pitch_mc = hatom_getdouble(&subll->l_head->l_hatom);
					if (subll->l_head->l_next && is_hatom_number(&subll->l_head->l_next->l_hatom))
						x->room_graph.edges[i].data.m_pitchnvel.velocity = CLAMP(hatom_getlong(&subll->l_head->l_next->l_hatom), DADA_MIN_VELOCITY, DADA_MAX_VELOCITY);
				}
			} else if (is_hatom_number(&elem->l_hatom)) {
				x->room_graph.edges[i].data.m_pitchnvel.pitch_mc = hatom_getdouble(&elem->l_hatom);
			}
		}
	}
}


t_llll *bounce_get_room(t_bounce *x)
{
	t_llll *out_ll = llll_get();
	llll_appendsym(out_ll, gensym("room"), 0, WHITENULL_llll);
    llll_chain(out_ll, graph_to_llll(&x->room_graph));
	return out_ll;
}


t_llll *bounce_get_single_ball(t_bounce *x, long idx)
{
    long i = idx;
    t_llll *ll = llll_get();
    llll_appendllll(ll, symbol_and_llll_to_llll_chained(gensym("coord"), pt_to_llll(x->balls[i].r_it.coord, false)) , 0, WHITENULL_llll);
    llll_appendllll(ll, symbol_and_llll_to_llll_chained(gensym("speed"), pt_to_llll(x->balls[i].speed, false)), 0, WHITENULL_llll);
    llll_appendllll(ll, symbol_and_llll_to_llll_chained(gensym("color"), color_to_llll(&x->balls[i].r_it.color)), 0, WHITENULL_llll);
    llll_appendllll(ll, symbol_and_long_to_llll(gensym("channel"), x->balls[i].channel), 0, WHITENULL_llll);
    dadaitem_append_flags_to_llll(ll, (t_dadaitem*)(&x->balls[i]), true);
    return ll;
}

t_llll *bounce_get_balls(t_bounce *x)
{
	long i;
	t_llll *out_ll = llll_get();
	long num_balls = dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_BALL);
	for (i = 0; i < num_balls; i++)
		llll_appendllll(out_ll, bounce_get_single_ball(x, i), 0, WHITENULL_llll);
	llll_prependsym(out_ll, gensym("balls"), 0, WHITENULL_llll);
	return out_ll;
}


t_llll *bounce_get_state_sel(t_bounce *x, char get_room, char get_balls)
{
	// How do we save the information?
	// Three sublists: 1) room graph, 2) balls
	// 1) in the form: ("room" ("vert" NODE1 NODE2 NODE3...) ("adj" ADJ1 ADJ2 ADJ3...)) 
	//		with NODE equal to the vertex coordinates: (x y), and ADJ equal to an adjacency list, 
	//		namely ADJ_j (v1 v2 v3 v4...) where v_i are the vertices adjacent to the j-th node.
	// 2) in the form: ("balls" BALL1 BALL2...) with BALL equal to ((x y) (vel_x vel_y) (r g b a) channel)
	
	t_llll *data = llll_get();
	
    llll_appendsym(data, gensym("bounce"), 0, WHITENULL_llll);

    if (get_room)
		llll_appendllll(data, bounce_get_room(x), 0, WHITENULL_llll);
	if (get_balls)
		llll_appendllll(data, bounce_get_balls(x), 0, WHITENULL_llll);
	
	return data;
}

t_llll *bounce_get_state(t_bounce *x)
{
	return bounce_get_state_sel(x, true, true);
}


void bounce_set_room(t_bounce *x, t_llll *room)
{
	if (room && room->l_head && room->l_head->l_next && hatom_gettype(&room->l_head->l_next->l_hatom) == H_LLLL &&
        hatom_getllll(&room->l_head->l_next->l_hatom)->l_head && hatom_gettype(&hatom_getllll(&room->l_head->l_next->l_hatom)->l_head->l_hatom) != H_SYM) {
        // OLD SYNTAX...
		graph_from_llll(hatom_getllll(&room->l_head->l_next->l_hatom), &x->room_graph);
    } else if (room && room->l_head) {
        graph_from_llll(room, &x->room_graph);
    }
}

void bounce_set_balls(t_bounce *x, t_llll *balls)
{
	long i;
	t_llllelem *elem;
	
	dadaitem_ball_clear(dadaobj_cast(x), 0);
	
	for (i = 0, elem = balls->l_head ? balls->l_head->l_next : NULL; elem && i < DADA_BOUNCE_MAX_BALLS; elem = elem->l_next, i++) {
		if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
			t_llll *ll = hatom_getllll(&elem->l_hatom);
            t_pt coord = build_pt(0, 0), speed = build_pt(0, 0);
            t_jrgba color = DADA_BLACK;
            long flags = 0, channel = 1;
			dadaobj_parseargs(dadaobj_cast(x), ll, (char *)"PPClF", gensym("coord"), &coord, gensym("speed"), &speed, gensym("color"), &color, gensym("channel"), &channel, gensym("flags"), &flags);
			dadaitem_ball_add(dadaobj_cast(x), coord, speed, color, channel, flags, 0);
		}
	}
	dadaobj_update_solos(dadaobj_cast(x));
}

long bounce_add_ball(t_bounce *x, t_llll *ball)
{
    t_pt coord = build_pt(0, 0), speed = build_pt(0, 0);
    t_jrgba color = get_grey(0);
    long channel = 1, flags = 0;
    dadaobj_parseargs(dadaobj_cast(x), ball, (char *)"PPClF", gensym("coord"), &coord, gensym("speed"), &speed, gensym("color"), &color, gensym("channel"), &channel, gensym("flags"), &flags);
//    dadaobj_parse_llll(dadaobj_cast(x), ball, (char *)"PPClF", &coord, &speed, &color, &channel, &flags);
    return dadaitem_ball_add(dadaobj_cast(x), coord, speed, color, channel, flags, 0);
}

void bounce_delete_ball(t_bounce *x, long idx)
{
    dadaitem_ball_delete(dadaobj_cast(x), idx, 0);
}


// see bounce_get_state about the codification of info
void bounce_set_state(t_bounce *x, t_llll *state)
{
    if (!state)
        return;
    
    x->itsme = true;

    t_llllelem *el;
    for (el = state->l_head; el; el = el->l_next) {
        if (hatom_gettype(&el->l_hatom) == H_LLLL) {
            t_llll *ll = hatom_getllll(&el->l_hatom);
            if (ll && ll->l_head && hatom_gettype(&ll->l_head->l_hatom) == H_SYM) {
                t_symbol *router = hatom_getsym(&ll->l_head->l_hatom);
                if (router == gensym("room"))
                    bounce_set_room(x, ll);
                else if (router == gensym("balls"))
                    bounce_set_balls(x, ll);
            }
        }
    }
	
	x->itsme = false;

	postprocess_ball(dadaobj_cast(x));
	postprocess_room(x);
}



void bounce_iterator_fn(t_bounce *x, dadaitem_iterfn iterator_fn, void *data)
{
	long i;
	long num_balls = dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_BALL);
	for (i = 0; i < num_balls; i++)
		if (iterator_fn(dadaobj_cast(x), (t_dadaitem *)&x->balls[i], data))
			return;
}





void bounce_assist(t_bounce *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type anything/llll @digest Incoming symbol or list
		sprintf(s, "Incoming symbol or list");
	} 
	else {	
        char *type = NULL;
        llllobj_get_llll_outlet_type_as_string((t_object *) x, LLLL_OBJ_UI, a, &type);
		if (a == 0)	// @out 0 @type llll @digest Dump outlet
			sprintf(s, "llll (%s): Dump Outlet", type);
		else if (a == 1)	// @out 1 @type llll @digest Queries and notifications
			sprintf(s, "llll (%s): Queries and Notifications", type);
        else if (a == 2)	// @out 2 @type llll @digest Information about bounce occurrence
            sprintf(s, "llll (%s): Bounce Data", type);
		else if (a == 3)	// @out 3 @type llll @digest Playout
			sprintf(s, "llll (%s): Playout", type);
		else 	// @out 4 @type bang @digest bang when object is changed via the interface
			sprintf(s, "bang when Changed"); 			
	}
}

void bounce_free(t_bounce *x)
{
	graph_free(&x->room_graph);
	object_free_debug(x->n_proxy1);
	dadaobj_jbox_free((t_dadaobj_jbox *)x); // jbox_free and llllobj_free are inside here
}


void bounce_iar(t_bounce *x) // invalidate and redraw
{
    jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
    jbox_redraw((t_jbox *)x);
}


void *bounce_new(t_symbol *s, long argc, t_atom *argv)
{
	t_bounce *x = NULL;
	t_dictionary *d = NULL;
	long boxflags;
	t_llll *llll_for_rebuild = NULL;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;    
	
	if ((x = (t_bounce *)object_alloc_debug(bounce_class))) {
		
		x->creating_new_obj = true;
        x->hit_edge = -1;
        x->output_bounce_data = true;
		
		
		boxflags = 0 
				| JBOX_DRAWFIRSTIN 
				| JBOX_NODRAWBOX
				| JBOX_DRAWINLAST
				| JBOX_TRANSPARENT  
		//      | JBOX_NOGROW
		//		| JBOX_GROWY
				| JBOX_GROWBOTH
				| JBOX_HILITE
		//      | JBOX_BACKGROUND
				| JBOX_DRAWBACKGROUND
		//      | JBOX_NOFLOATINSPECTOR
		//      | JBOX_MOUSEDRAGDELTA
		//      | JBOX_TEXTFIELD
		;
		
		jbox_new((t_jbox *)x, boxflags, argc, argv);
		x->b_ob.r_ob.l_box.b_firstin = (t_object *)x;
		x->n_proxy1 = proxy_new((t_object *) x, 1, &x->n_in);

		dadaobj_jbox_setup((t_dadaobj_jbox *)x, DADAOBJ_BBGIMAGE | DADAOBJ_ZOOM | DADAOBJ_CENTEROFFSET | DADAOBJ_UNDO | DADAOBJ_CHANGEDBANG | DADAOBJ_NOTIFICATIONS, build_pt(1., 1.), 2, 4, 1, (invalidate_and_redraw_fn)bounce_iar, "qnvsrl", 2, "b4444");

        dadaobj_addfunctions(dadaobj_cast(x), (dada_mousemove_fn)bounce_mousemove, (method)bounce_task, (method)bounce_postprocess_undo, (get_state_fn)bounce_get_state, (set_state_fn)bounce_set_state, NULL, NULL, NULL);

		dadaobj_dadaitem_class_alloc(dadaobj_cast(x), DADAITEM_TYPE_BALL, gensym("ball"), gensym("Ball"), DADA_ITEM_ALLOC_ARRAY, 0, false, sizeof(t_dada_ball), calcoffset(t_bounce, balls), DADA_BOUNCE_MAX_BALLS, NULL, DADA_FUNC_v_oX, (method)bounce_set_balls, NULL, DADA_FUNC_X_o, (method)bounce_get_balls, NULL, (method)postprocess_ball, NULL, NULL, false, false);
		
		graph_new(&x->room_graph, DADA_GRAPH_FLAG_SYMMETRIC | DADA_GRAPH_FLAG_CONNECTED_COMPONENTS, DADA_GRAPH_METADATA_PITCHNVEL,
				  DADA_GRAPH_METADATA_PITCHNVEL, DADA_LINE_STRAIGHT);

		t_shape shape = ezbuild_dadapolygon(DADA_BLACK, 1, 4, -100., -100., 100., -100., 100., 100., -100., 100.);
		graph_import_dadapolygon(&x->room_graph, &shape.shape.polygon, DADA_DEFAULT_VERTEX_PITCHNVEL_METADATA, DADA_DEFAULT_EDGE_PITCHNVEL_METADATA, true);

		dadaitem_ball_add(dadaobj_cast(x), build_pt(0, 0), DADA_BOUNCE_DEFAULT_SPEED, DADA_RED, 1, 0, 0);

		
		x->firsttime = true;
		x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
		x->b_ob.d_ob.m_tools.curr_tool = DADA_TOOL_ARROW;

		
		attr_dictionary_process(x,d);
		
		if ((llll_for_rebuild = llll_retrieve_from_dictionary(d, "bounce_data"))) { // new method
			llllobj_manage_dict_llll((t_object *)x, LLLL_OBJ_UI, llll_for_rebuild);
			bounce_set_state(x, llll_for_rebuild);
			llll_free(llll_for_rebuild);
		}
 
		jbox_ready((t_jbox *)x);
        
        dadaobj_set_current_version_number(dadaobj_cast(x));
        
        x->creating_new_obj = false;
	}
	return x;
}

void bounce_int(t_bounce *x, t_atom_long num)
{
    if (num == 0)
        bounce_stop(x, NULL, 0, NULL);
    else
        bounce_play(x, NULL, 0, NULL);
    /*	t_atom argv[1];
     atom_setlong(argv, num);
     bounce_anything(x, _sym_list, 1, argv); */

}

void bounce_float(t_bounce *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	bounce_anything(x, _sym_list, 1, argv);
}


void bounce_dump(t_bounce *x, char get_room, char get_balls)
{	
	t_llll *ll = bounce_get_state_sel(x, get_room, get_balls);
	llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 0, ll);
	llll_free(ll);
}

void bounce_clear(t_bounce *x, char clear_room, char clear_balls)
{
    if (clear_balls)
        dadaitem_ball_clear(dadaobj_cast(x), 0);
    
    if (clear_room)
        graph_clear(&x->room_graph);
}

void bounce_anything(t_bounce *x, t_symbol *msg, long ac, t_atom *av)
{
	dadaobj_anything(dadaobj_cast(x), msg, ac, av);

	long num_inlet = proxy_getinlet((t_object *)x);
	t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, msg, ac, av, LLLL_PARSE_CLONE);
	if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
		t_symbol *router = hatom_getsym(&parsed->l_head->l_hatom);
		llll_behead(parsed);
		
        if (dadaobj_anything_handle_domain_or_range(dadaobj_cast(x), router, parsed)) {
            // nothing to do!
        } else if (router == gensym("setstoredstate") || router == gensym("bounce")) {
            bounce_undo_step_push(x, gensym("Set State"));
			bounce_set_state(x, parsed);
            bounce_postprocess_undo(x);
            
        } else if (router == _sym_dump)
			bounce_dump(x, parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("room")), 
						 parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("balls")));
		
        else if (router == gensym("notes"))
			bounce_set_pitchandvel(x, parsed);

        else if (router == gensym("scores"))
            bounce_set_scores(x, parsed);
        
        else if (router == gensym("flush"))
            send_all_noteoffs(x);

        else if (router == gensym("clear")) {
            bounce_undo_step_push(x, gensym("Clear"));
            bounce_clear(x, parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("room")), parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("balls")));
            bounce_postprocess_undo(x);

        } else if (router == gensym("addball")) {
            bounce_undo_step_push_balls(x, gensym("Add Ball"));
            notify_ball_add(x, bounce_add_ball(x, parsed));
            bounce_postprocess_undo(x);

        } else if (router == gensym("deleteball") && parsed->l_head && is_hatom_number(&parsed->l_head->l_hatom)) {
            bounce_undo_step_push_balls(x, gensym("Delete Ball"));
            bounce_delete_ball(x, hatom_getlong(&parsed->l_head->l_hatom));
            bounce_postprocess_undo(x);
            
        } else if (router == _sym_move) {
            if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
                t_symbol *what = hatom_getsym(&parsed->l_head->l_hatom);
                llll_behead(parsed);
                if (what == gensym("vertex")) {
                    if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_LONG &&
                        parsed->l_head->l_next && hatom_gettype(&parsed->l_head->l_next->l_hatom) == H_LLLL) {
                        move_vertex_delta(x, hatom_getlong(&parsed->l_head->l_hatom) - 1, llll_to_pt(hatom_getllll(&parsed->l_head->l_next->l_hatom)), false);
                    }
                } else if (what == gensym("edge")) {
                        if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_LONG &&
                            parsed->l_head->l_next && hatom_gettype(&parsed->l_head->l_next->l_hatom) == H_LLLL) {
                            move_edge_delta(x, hatom_getlong(&parsed->l_head->l_hatom) - 1, llll_to_pt(hatom_getllll(&parsed->l_head->l_next->l_hatom)), false);
                        }
                } else if (what == gensym("component")) {
                    if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_LONG &&
                        parsed->l_head->l_next && hatom_gettype(&parsed->l_head->l_next->l_hatom) == H_LLLL) {
                        move_connected_component_delta(x, hatom_getlong(&parsed->l_head->l_hatom) - 1, llll_to_pt(hatom_getllll(&parsed->l_head->l_next->l_hatom)), false);
                    }
                } else if (what == gensym("ball")) {
                    if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_LONG &&
                        parsed->l_head->l_next && hatom_gettype(&parsed->l_head->l_next->l_hatom) == H_LLLL) {
                        dadaitem_ball_move_delta(dadaobj_cast(x), hatom_getlong(&parsed->l_head->l_hatom) - 1, llll_to_pt(hatom_getllll(&parsed->l_head->l_next->l_hatom)), DIA_UNDO_POSTPROCESS);
                    }
                }
            }

        } else if (router == _sym_rotate) {
                if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
                    t_symbol *what = hatom_getsym(&parsed->l_head->l_hatom);
                    llll_behead(parsed);
                    if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_LONG &&
                        parsed->l_head->l_next) {
                            long idx = hatom_getlong(&parsed->l_head->l_hatom) - 1;
                        double angle = hatom_to_angle_in_rad(&parsed->l_head->l_next->l_hatom);
                        if (what == gensym("component")) {
                            graph_rotate_connected_component(&x->room_graph, idx, angle);
                            bounce_iar(x);
                        } else if (what == gensym("ball")) {
                            dadaitem_ball_speed_rotate(dadaobj_cast(x), idx, angle, DIA_UNDO_POSTPROCESS);
                        }
                    }
                }

        } else if (router == _sym_scale) {
            if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
                t_symbol *what = hatom_getsym(&parsed->l_head->l_hatom);
                llll_behead(parsed);
                if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_LONG &&
                    parsed->l_head->l_next && is_hatom_number(&parsed->l_head->l_next->l_hatom)) {
                    long idx = hatom_getlong(&parsed->l_head->l_hatom) - 1;
                    double factor = hatom_getdouble(&parsed->l_head->l_next->l_hatom);
                    if (what == gensym("component")) {
                        graph_scale_connected_component(&x->room_graph, idx, factor);
                        bounce_iar(x);
                    } else if (what == gensym("ball")) {
                        dadaitem_ball_speed_scale(dadaobj_cast(x), idx, factor, DIA_UNDO_POSTPROCESS);
                    }
                }
            }
            
        } else if (router == gensym("subdivide")) {
            if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
                t_symbol *what = hatom_getsym(&parsed->l_head->l_hatom);
                llll_behead(parsed);
                if (what == gensym("edge")) {
                    if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_LONG &&
                        parsed->l_head->l_next && hatom_gettype(&parsed->l_head->l_next->l_hatom) == H_LONG) {
                        subdivide_edge(x, hatom_getlong(&parsed->l_head->l_hatom) - 1, hatom_getlong(&parsed->l_head->l_next->l_hatom));
                    }
                }
            }

        } else if (router == gensym("split")) {
            if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
                t_symbol *what = hatom_getsym(&parsed->l_head->l_hatom);
                llll_behead(parsed);
                if (what == gensym("edge")) {
                    if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_LONG &&
                        parsed->l_head->l_next && hatom_gettype(&parsed->l_head->l_next->l_hatom) == H_LLLL) {
                        split_edge(x, hatom_getlong(&parsed->l_head->l_hatom) - 1, llll_to_pt(hatom_getllll(&parsed->l_head->l_next->l_hatom)));
                    }
                }
            }

        } else if (router == gensym("meta")) {

            if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
                t_symbol *what = hatom_getsym(&parsed->l_head->l_hatom);
                llll_behead(parsed);
                if (what == gensym("edge")) {
                    if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_LONG &&
                        parsed->l_head->l_next) {
                        graph_set_metadata_to_edge_from_llll(&x->room_graph, hatom_getlong(&parsed->l_head->l_hatom) - 1, parsed);
                    }
                } else if (what == gensym("vertex")) {
                    if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_LONG &&
                        parsed->l_head->l_next) {
                        graph_set_metadata_to_vertex_from_llll(&x->room_graph, hatom_getlong(&parsed->l_head->l_hatom) - 1, parsed);
                    }
                }
            }

        }
        
	} else if (parsed) {
        bounce_undo_step_push(x, gensym("Set State"));
		bounce_set_state(x, parsed);
        bounce_postprocess_undo(x);
	}
	llll_free(parsed);
}




long coord_to_ball(t_bounce *x, t_pt coord)
{
	long i;
	long num_balls = dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_BALL);
    double zoom = dadaobj_cast(x)->m_zoom.zoom.x;
	for (i = 0; i < num_balls; i++)
		if (pt_pt_distance(x->balls[i].r_it.coord, coord) <= x->ball_size + DADA_BOUNCE_BALL_SELECTION_PAD/zoom)
			return i;
	return -1;
}

long pixel_to_ball(t_bounce *x, t_pt pt, t_object *view, t_pt *coordinates)
{
	t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), view, pt);
	if (coordinates)
		*coordinates = coord;
	return coord_to_ball(x, coord);
}

long pixel_to_graph_vertex(t_bounce *x, t_pt pt, t_object *view, t_pt *coordinates)
{
	t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), view, pt);
    double zoom = dadaobj_cast(x)->m_zoom.zoom.x;
	if (coordinates)
		*coordinates = coord;
	return graph_coord_to_vertex(dadaobj_cast(x), &x->room_graph, coord, x->room_vertex_size / x->b_ob.d_ob.m_zoom.zoom.x, DADA_BOUNCE_VERTEX_SELECTION_PAD/zoom);
}

long pixel_to_graph_edge(t_bounce *x, t_pt pt, t_object *view, t_pt *coordinates)
{
	t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), view, pt);
    double zoom = dadaobj_cast(x)->m_zoom.zoom.x;
	if (coordinates)
		*coordinates = coord;
	return graph_coord_to_edge(dadaobj_cast(x), &x->room_graph, coord, x->room_edge_linewidth / x->b_ob.d_ob.m_zoom.zoom.x, DADA_BOUNCE_EDGE_SELECTION_PAD/zoom);
}

long pixel_to_graph_connected_component(t_bounce *x, t_pt pt, t_object *view, t_pt *coordinates)
{
	t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), view, pt);
	if (coordinates)
		*coordinates = coord;
	return graph_coord_to_connected_component(&x->room_graph, coord);
}

t_dadaitem_identifier pixel_to_element(t_bounce *x, t_pt pt, t_object *view, t_pt *coordinates)
{
	t_dadaitem_identifier result;
	long idx = -1;
	result.type = DADAITEM_TYPE_NONE;
	result.flag = 0;
	result.idx = result.secondary_idx = result.tertiary_idx = -1;
	
	if ((idx = pixel_to_ball(x, pt, view, coordinates)) >= 0) {
		result.type = DADAITEM_TYPE_BALL;
		result.idx = idx;
	} else if ((idx = pixel_to_graph_vertex(x, pt, view, coordinates)) >= 0) {
		result.type = DADAITEM_TYPE_VERTEX;
		result.idx = idx;
	} else if ((idx = pixel_to_graph_edge(x, pt, view, coordinates)) >= 0) {
		result.type = DADAITEM_TYPE_EDGE;
		result.idx = idx;
	} else if ((idx = pixel_to_graph_connected_component(x, pt, view, coordinates)) >= 0) {
		result.type = DADAITEM_TYPE_CONNECTED_COMPONENT;
		result.idx = idx;
	}

	return result;
}



//// GRAPHIC DRAWING


void paint_edge_note(t_bounce *x, t_jgraphics *g, t_object *view, long edge_idx, t_rect noterect, t_jrgba bgcolor)
{
/*	t_jrgba staffcolor = build_jrgba(0.2, 0.2, 0.2, 1);
	t_jrgba bordercolor = build_jrgba(0.2, 0.2, 0.2, 1);
	
	
	ezpaint_note_with_staff((t_object *)x, g, view, node->pitch_mc, k_ACC_AUTO, x->tonedivision, build_pt(noterect.x + 3 * zoom, noterect.y + 25 * zoom), 
							noterect.width - 6 * zoom, 24 * zoom, noterect.x + 31 * zoom, false, &staffcolor, &staffcolor, &staffcolor);

	jgraphics_set_source_rgba(g, 0, 0, 0, 1);*/
}

void paint_connected_component(t_bounce *x, t_jgraphics *g, t_object *view, t_rect rect, t_pt center, long idx, t_jrgba *color)
{
	if (idx >= 0 && idx < x->room_graph.num_connected_components) {
		t_dadapolygon *poly = &x->room_graph.connected_components[idx].poly;
		
		if (poly->num_vertices > 2) {
			t_pt coord = poly->vertex[0];
			t_pt pix = coord_to_pix(dadaobj_cast(x), center, coord);
			jgraphics_move_to(g, pix.x, pix.y);
			long i;
			for (i = 1; i < poly->num_vertices; i++) {
				coord = poly->vertex[i];
				pix = coord_to_pix(dadaobj_cast(x), center, coord);
				jgraphics_line_to(g, pix.x, pix.y);
				
			}
			jgraphics_close_path(g);
			jgraphics_set_line_width(g,0);
			jgraphics_set_source_jrgba(g, color);
			jgraphics_fill(g);
		}
	}
}

void repaint_played_elements(t_bounce *x, t_jgraphics *g, t_object *view, t_rect rect, t_pt center)
{
    if (x->hit_edge >= 0) {
        graph_paint_edge(dadaobj_cast(x), g, view, rect, center, &x->room_graph, change_alpha(x->b_ob.d_ob.m_play.play_color, x->b_ob.d_ob.m_play.play_color.alpha * 0.9), x->hit_edge, 0, 0, NULL, 4, false, NULL, false, NULL, false);
    }
}


void paint_score_label(t_bounce *x, t_jgraphics *g, t_pt pt, t_symbol *symbol)
{
    char label[1024];
    snprintf(label, 1024, "%s", symbol ? symbol->s_name : "score");
    t_jfont *jf = jfont_create("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, 11);
    write_text(g, jf, DADA_BLACK, label, pt.x + 5, pt.y + 5, 300, 300, JGRAPHICS_TEXT_JUSTIFICATION_LEFT | JGRAPHICS_TEXT_JUSTIFICATION_TOP, 1, 0);
    jfont_destroy(jf);
}

void repaint_hovered_elements(t_bounce *x, t_jgraphics *g, t_object *view, t_rect rect, t_pt center)
{
	// re-paint selected and hovered elements
	t_jrgba staffcolor = build_jrgba(0.2, 0.2, 0.2, 1);
	t_jrgba bordercolor = build_jrgba(0.2, 0.2, 0.2, 1);
	t_jrgba bgcolor = build_jrgba(1, 1, 1, 0.8);

	
	if (x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_CREATE_LINE && x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_VERTEX) {
		t_pt pt2 = coord_to_pix(dadaobj_cast(x), center, x->room_graph.vertices[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx].r_it.coord);
		double rect_size = (x->room_vertex_size + DADA_BOUNCE_VERTEX_SELECTION_PAD);
		paint_rectangle(g, x->j_roomcolor, change_alpha(x->j_roomcolor, 0.3), pt2.x - rect_size/2., pt2.y - rect_size/2., rect_size, rect_size, 1);
		
		paint_line(g, x->j_roomcolor, pt2.x, pt2.y, x->b_ob.d_ob.m_interface.mousedrag_pix.x, x->b_ob.d_ob.m_interface.mousedrag_pix.y, 1);
	}
	
	switch (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type) {
		case DADAITEM_TYPE_VERTEX:
		{
			t_pt pt = coord_to_pix(dadaobj_cast(x), center, x->room_graph.vertices[x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx].r_it.coord);
			double rect_size = (x->room_vertex_size + DADA_BOUNCE_VERTEX_SELECTION_PAD);
			paint_rectangle(g, x->j_roomcolor, change_alpha(x->j_roomcolor, 0.3), pt.x - rect_size/2., pt.y - rect_size/2., rect_size, rect_size, 1);
			
			if (x->pitch_mode == DADA_BOUNCE_VERTICES_HAVE_METADATA) {
                if (x->metadata_type == DADA_BOUNCE_METADATA_PITCHNVEL) {
                    t_rect noterect = build_rect(pt.x - 25, pt.y - 35, 50, 70);
                    paint_rectangle_rounded(g, bordercolor, bgcolor, noterect.x, noterect.y, noterect.width, noterect.height, 1, DADA_DEFAULT_RECT_ROUNDNESS, DADA_DEFAULT_RECT_ROUNDNESS);
                    ezpaint_note_with_staff((t_object *)x, g, view, x->room_graph.vertices[x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx].data.m_pitchnvel.pitch_mc, k_ACC_AUTO,
                                            x->tonedivision, build_pt(noterect.x + 3, noterect.y + 25),
                                            noterect.width - 6, 24, noterect.x + 31, false, &staffcolor, &staffcolor, &staffcolor);
                } else {
                    paint_score_label(x, g, pt, x->room_graph.vertices[x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx].data.m_llllscore.label);
                }
			}
		}
			break;
			
		case DADAITEM_TYPE_EDGE:
		{
			t_pt pt1 = coord_to_pix(dadaobj_cast(x), center, x->room_graph.vertices[x->room_graph.edges[x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx].start].r_it.coord);
			t_pt pt2 = coord_to_pix(dadaobj_cast(x), center, x->room_graph.vertices[x->room_graph.edges[x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx].end].r_it.coord);
			t_pt avg = pt_number_prod(pt_pt_sum(pt1, pt2), 0.5);
			t_pt corner;

			paint_line(g, change_alpha(x->j_roomcolor, 0.3), pt1.x, pt1.y, pt2.x, pt2.y, x->room_edge_linewidth + DADA_BOUNCE_EDGE_SELECTION_PAD);
			paint_line(g, x->j_roomcolor, avg.x - x->room_vertex_size, avg.y - x->room_vertex_size, avg.x + x->room_vertex_size, avg.y + x->room_vertex_size, 2);
			paint_line(g, x->j_roomcolor, avg.x + x->room_vertex_size, avg.y - x->room_vertex_size, avg.x - x->room_vertex_size, avg.y + x->room_vertex_size, 2);
			
			if (x->pitch_mode == DADA_BOUNCE_EDGES_HAVE_METADATA) {
                if (x->metadata_type == DADA_BOUNCE_METADATA_PITCHNVEL) {
                    t_rect noterect = get_rect_near_pt_inside_rect(avg, 50, 70, build_rect(0, 0, rect.width, rect.height), build_pt(10, 10), build_pt(10, 10), &corner);
                    paint_dashed_line(g, x->j_roomcolor, avg.x, avg.y, corner.x, corner.y, 3, 3);
                    
                    paint_rectangle_rounded(g, bordercolor, bgcolor, noterect.x, noterect.y, noterect.width, noterect.height, 1, DADA_DEFAULT_RECT_ROUNDNESS, DADA_DEFAULT_RECT_ROUNDNESS);
                    ezpaint_note_with_staff((t_object *)x, g, view, x->room_graph.edges[x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx].data.m_pitchnvel.pitch_mc, k_ACC_AUTO,
                                            x->tonedivision, build_pt(noterect.x + 3, noterect.y + 25),
                                            noterect.width - 6, 24, noterect.x + 31, false, &staffcolor, &staffcolor, &staffcolor);
                } else {
                    paint_score_label(x, g, avg, x->room_graph.edges[x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx].data.m_llllscore.label);
                }
			}
		}
			break;
		case DADAITEM_TYPE_CONNECTED_COMPONENT:
		{
			t_jrgba color = change_alpha(x->j_roomcolor, 0.3);
			paint_connected_component(x, g, view, rect, center, x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx, &color);
			
            if (x->metadata_type == DADA_BOUNCE_METADATA_PITCHNVEL) {
                if (x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_CHANGE_PITCH || x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_CHANGE_VELOCITY) {
                    long i, idx = x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx;
                    if (idx >= 0 && idx < x->room_graph.num_connected_components) {
                        if (x->pitch_mode == DADA_BOUNCE_EDGES_HAVE_METADATA) {
                            for (i = 0; i < x->room_graph.num_edges; i++) {
                                if (x->room_graph.vertices[x->room_graph.edges[i].start].connected_component_idx == idx) {
                                    t_pt pt1 = coord_to_pix(dadaobj_cast(x), center, x->room_graph.vertices[x->room_graph.edges[i].start].r_it.coord);
                                    t_pt pt2 = coord_to_pix(dadaobj_cast(x), center, x->room_graph.vertices[x->room_graph.edges[i].end].r_it.coord);
                                    t_pt avg = pt_number_prod(pt_pt_sum(pt1, pt2), 0.5);
                                    t_rect noterect = build_rect(avg.x - 25, avg.y - 35, 50, 70);
                                    paint_rectangle_rounded(g, bordercolor, bgcolor, noterect.x, noterect.y, noterect.width, noterect.height, 1, DADA_DEFAULT_RECT_ROUNDNESS, DADA_DEFAULT_RECT_ROUNDNESS);
                                    ezpaint_note_with_staff((t_object *)x, g, view, x->room_graph.edges[i].data.m_pitchnvel.pitch_mc, k_ACC_AUTO,
                                                            x->tonedivision, build_pt(noterect.x + 3, noterect.y + 25),
                                                            noterect.width - 6, 24, noterect.x + 31, false, &staffcolor, &staffcolor, &staffcolor);
                                }
                            }
                        } else  {
                            for (i = 0; i < x->room_graph.num_vertices; i++) {
                                if (x->room_graph.vertices[i].connected_component_idx == idx) {
                                    t_pt pt = coord_to_pix(dadaobj_cast(x), center, x->room_graph.vertices[i].r_it.coord);
                                    t_rect noterect = build_rect(pt.x - 25, pt.y - 35, 50, 70);
                                    paint_rectangle_rounded(g, bordercolor, bgcolor, noterect.x, noterect.y, noterect.width, noterect.height, 1, DADA_DEFAULT_RECT_ROUNDNESS, DADA_DEFAULT_RECT_ROUNDNESS);
                                    ezpaint_note_with_staff((t_object *)x, g, view, x->room_graph.vertices[i].data.m_pitchnvel.pitch_mc, k_ACC_AUTO, 
                                                            x->tonedivision, build_pt(noterect.x + 3, noterect.y + 25), 
                                                            noterect.width - 6, 24, noterect.x + 31, false, &staffcolor, &staffcolor, &staffcolor);
                                }
                            }
                        }
                    }
                }
            }
			
			break;
		}
		default: 
			break;
	}
}

void bounce_paint_graph(t_bounce *x, t_object *view, t_rect rect, t_pt center){
	
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("room"), rect.width, rect.height);
	
	if (g) {
//        t_jfont *jf_label = jfont_create("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, 11);
		graph_paint(dadaobj_cast(x), g, view, rect, center, &x->room_graph, x->j_roomcolor, true, true,
					x->room_vertex_size, x->room_vertex_size, NULL, x->room_edge_linewidth, 0, NULL, false, NULL, false);
		jbox_end_layer((t_object *)x, view, gensym("room"));
//        jfont_destroy(jf_label);
	}
	
	jbox_paint_layer((t_object *)x, view, gensym("room"), 0., 0.);	// position of the layer
}


void bounce_paint(t_bounce *x, t_object *view)
{
	t_rect rect;
	t_pt center = get_center_pix(dadaobj_cast(x), view, &rect);
	long i;
	t_jgraphics *g = (t_jgraphics*) patcherview_get_jgraphics(view); 
	
	jgraphics_set_source_rgba(g, 0, 0, 0, 1); // alpha = 1;
	
    dadaobj_paint_background(dadaobj_cast(x), g, &rect);

    dadaobj_paint_grid(dadaobj_cast(x), view, rect, center);
		
	if (x->show_room)
		bounce_paint_graph(x, view, rect, center);
	
	if (x->show_balls || x->show_speed) {
		long num_balls = dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_BALL);
		for (i = 0; i < num_balls; i++) {
			t_pt pix = coord_to_pix(dadaobj_cast(x), center, x->balls[i].r_it.coord);
			t_pt speed = x->balls[i].speed;
			
			if (x->show_speed && (speed.x != 0 || speed.y != 0)) { // paint speed vector
				t_pt tip = pt_pt_sum(pix, pt_number_prod(build_pt(speed.x * x->speed_display_factor, -speed.y * x->speed_display_factor), x->b_ob.d_ob.m_zoom.zoom.x));
				paint_arrow(g, x->balls[i].r_it.color, pix.x, pix.y, tip.x, tip.y, 1, 5, 5);
			}

			if (x->show_balls) { // paint balls
				paint_circle(g, x->balls[i].r_it.color, change_alpha(x->balls[i].r_it.color, 0.8), pix.x, pix.y, x->ball_size, 1);
                
				if (x->balls[i].r_it.flags & D_INACTIVE)
					paint_circle_filled(g, DADA_COLOR_INACTIVE, pix.x, pix.y, x->ball_size + DADA_BOUNCE_BALL_SELECTION_PAD);
				
                if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_BALL && x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx == i)
					paint_circle_stroken(g, x->balls[i].r_it.color, pix.x, pix.y, x->ball_size + DADA_BOUNCE_BALL_SELECTION_PAD, 1);
				
                if (x->balls[i].r_it.flags & D_SOLO)
					paint_pointed_corolla(g, &x->balls[i].r_it.color, pix, 6, 8, 1);
                
                if (!dadaitem_should_be_played(dadaobj_cast(x), (t_dadaitem *)&x->balls[i])) {
					t_jrgba color = (x->balls[i].r_it.flags & D_MUTE) ? x->balls[i].r_it.color : change_alpha(x->balls[i].r_it.color, 0.4);
					paint_cross(g, &color, pix, 4.5, 1.5);
				}
			}
			
		}
	}
	
	if (x->b_ob.d_ob.m_tools.curr_tool != DADA_TOOL_ZOOM && x->b_ob.d_ob.m_tools.curr_tool != DADA_TOOL_MOVE_CENTER)
		repaint_hovered_elements(x, g, view, rect, center);

    repaint_played_elements(x, g, view, rect, center);
    
    dadaobj_paint_border(dadaobj_cast(x), g, &rect);
}






///////// POPUP MENU FUNCTIONS

void popup_delete_edge(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_bounce *x = (t_bounce *)d_ob->orig_obj;
	if (d_ob->m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_EDGE)
		delete_edge(x, d_ob->m_interface.mousedown_item_identifier.idx);
}

void popup_delete_vertex(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_bounce *x = (t_bounce *)d_ob->orig_obj;
	if (d_ob->m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_VERTEX)
		delete_vertex(x, d_ob->m_interface.mousedown_item_identifier.idx, label == gensym("Remove"));
}

void popup_subdivide_edge(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_bounce *x = (t_bounce *)d_ob->orig_obj;
	if (d_ob->m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_EDGE)
		subdivide_edge(x, d_ob->m_interface.mousedown_item_identifier.idx, hatom_getlong(&address->l_tail->l_hatom));
}

void popup_extrude_edge(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_bounce *x = (t_bounce *)d_ob->orig_obj;
	if (d_ob->m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_EDGE)
		extrude_edge(x, d_ob->m_interface.mousedown_item_identifier.idx);
}

void popup_passthrough(t_dadaobj *d_ob, t_symbol *label, const t_llll *address)
{
    t_bounce *x = (t_bounce *)d_ob->orig_obj;
    if (d_ob->m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_EDGE) {
        long idx = d_ob->m_interface.mousedown_item_identifier.idx;
        
        if (idx >= 0 && idx < x->room_graph.num_edges) {
            if (x->room_graph.edges[idx].flag & DADA_GRAPH_EDGE_FLAG_PASSTHROUGH)
                x->room_graph.edges[idx].flag &= ~DADA_GRAPH_EDGE_FLAG_PASSTHROUGH;
            else
                x->room_graph.edges[idx].flag |= DADA_GRAPH_EDGE_FLAG_PASSTHROUGH;
            postprocess_room(x);
        }
    }
}



void show_edge_popup_menu(t_bounce *x, t_object *patcherview, t_pt pt, long modifiers)
{
    char checked[256];
    long passthrough = 0;
    
    long idx = dadaobj_cast(x)->m_interface.mousedown_item_identifier.idx;
    if (idx >= 0 && idx < x->room_graph.num_edges)
        if (x->room_graph.edges[idx].flag & DADA_GRAPH_EDGE_FLAG_PASSTHROUGH)
            passthrough = 1;
    
    snprintf_zero(checked, 256, "0 0 0 %ld", passthrough);
    ezdisplay_popup_menu(dadaobj_cast(x), patcherview,
						 (char *)"Delete (Subdivide Into 2 Into 3 Into 4 Into 5 Into 6 Into 7 Into 8) Extrude Pass-through", "0 0 0 0", checked, "", "", "",
						 (void *)popup_delete_edge, (void *)popup_subdivide_edge, (void *)popup_extrude_edge, (void *)popup_passthrough, WHITENULL);
}



void show_vertex_popup_menu(t_bounce *x, t_object *patcherview, t_pt pt, long modifiers)
{
	ezdisplay_popup_menu(dadaobj_cast(x), patcherview, 
						 (char *)"Remove Delete", "0 0", "", "", "", "", 
						 (void *)popup_delete_vertex, (void *)popup_delete_vertex, WHITENULL);
}



void popup_delete_ball(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_bounce *x = (t_bounce *)d_ob->orig_obj;
	if (d_ob->m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_BALL)
		dadaitem_ball_delete(dadaobj_cast(x), d_ob->m_interface.mousedown_item_identifier.idx, DIA_UNDO_POSTPROCESS);
}


void popup_set_ball_speed_direction(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_bounce *x = (t_bounce *)d_ob->orig_obj;
	if (d_ob->m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_BALL)
		dadaitem_ball_speed_set_angle(dadaobj_cast(x), d_ob->m_interface.mousedown_item_identifier.idx, (hatom_getlong(&address->l_tail->l_hatom) - 2) * PI/4., DIA_UNDO_POSTPROCESS);
}

void popup_set_ball_color(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_bounce *x = (t_bounce *)d_ob->orig_obj;
	if (d_ob->m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_BALL) {
		long idx = x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx;
		long num_balls = dadaitem_class_get_num_items(&d_ob->m_classes, DADAITEM_TYPE_BALL);
		if (idx >= 0 && idx < num_balls) {
			t_jrgba color = symbol_to_color(label);
			double alpha = x->balls[idx].r_it.color.alpha;
			color.alpha = alpha;
			x->balls[idx].r_it.color = color;
			
			postprocess_ball(dadaobj_cast(x));
		}
	}
}

void popup_set_ball_channel(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_bounce *x = (t_bounce *)d_ob->orig_obj;
	if (d_ob->m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_BALL)
		dadaitem_ball_set_channel(dadaobj_cast(x), d_ob->m_interface.mousedown_item_identifier.idx, hatom_getlong(&address->l_tail->l_hatom) - 1, DIA_UNDO_POSTPROCESS);
}

void show_ball_popup_menu(t_bounce *x, t_object *patcherview, t_pt pt, long modifiers)
{
	// what will be checked
	t_llll *checked = llll_from_text_buf((char *)"0 0 0 (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0) 0", false);
	char *checked_buf = NULL;
	long num_balls = dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_BALL);
	if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_BALL && x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx >= 0 && x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx < num_balls) {
		long channel = x->balls[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx].channel;
		if (channel >= 1 && channel <= 16) {
			t_llllelem *elem = llll_getindex(hatom_getllll(&checked->l_head->l_next->l_next->l_next->l_hatom), channel + 1, I_NON_NEGATIVE); // +1 is for the first MIDIchannel symbol
			if (elem)
				hatom_setlong(&elem->l_hatom, 1);
		}
	}
	llll_to_text_buf(checked, &checked_buf, 0, BACH_DEFAULT_MAXDECIMALS, LLLL_T_NONE, LLLL_TE_SMART, LLLL_TB_SMART, NULL);
	
	ezdisplay_popup_menu_for_dadaitem(dadaobj_cast(x), patcherview, (t_dadaitem *)&x->balls[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx], D_SOLO | D_MUTE | D_INACTIVE,
						 (char *)"Delete separator ( Speed Direction 0° 45° 90° 145° 180° 225° 270° 315° ) ( MIDIchannel 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 ) ( Color Red Green Blue Yellow Orange Violet )", 
						 "0 0 0 0 0", checked_buf, "", "", "", 
						 (void *)popup_delete_ball, NULL, (void *)popup_set_ball_speed_direction, (void *)popup_set_ball_channel, (void *)popup_set_ball_color, WHITENULL);
	
	llll_free(checked);
	bach_freeptr(checked_buf);
	bounce_mousemove(x, patcherview, pt, modifiers);
}


void popup_add_ball(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_bounce *x = (t_bounce *)d_ob->orig_obj;
	long num_balls = dadaitem_class_get_num_items(&d_ob->m_classes, DADAITEM_TYPE_BALL);
	dadaitem_ball_add(dadaobj_cast(x), d_ob->m_interface.mousedown_coord, DADA_BOUNCE_DEFAULT_SPEED, dada_long_to_color(num_balls), 
					  dadaitem_ball_find_max_channel(dadaobj_cast(x)) + 1, 0, DIA_UNDO_POSTPROCESS);
}


void popup_add_vertex(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_bounce *x = (t_bounce *)d_ob->orig_obj;
	graph_add_vertex(&x->room_graph, d_ob->m_interface.mousedown_coord, bounce_default_vertex_metadata(x));
	postprocess_room(x);
}


void popup_add_dadapolygon(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_bounce *x = (t_bounce *)d_ob->orig_obj;
	t_dadapolygon poly = build_regular_dadapolygon(hatom_getlong(&address->l_tail->l_hatom) + 1, d_ob->m_interface.mousedown_coord, 50 / d_ob->m_zoom.zoom.x);
	graph_import_dadapolygon(&x->room_graph, &poly, bounce_default_edge_metadata(x), bounce_default_edge_metadata(x), true);
	postprocess_room(x);
}


void show_bg_popup_menu(t_bounce *x, t_object *patcherview, t_pt pt, long modifiers)
{
	ezdisplay_popup_menu(dadaobj_cast(x), patcherview, 
						 (char *)"Center View Reset Zoom separator Add Ball (Add Room Element Vertex (Polygon Triangle Square Pentagon Hexagon Heptagon Octagon)) separator No Solo No Mute", 
						 "0 0 0 0 (0 0 0) 0 0 0", "", "", "", "", 
						 (void *)popup_center_view, (void *)popup_reset_zoom, NULL, (void *)popup_add_ball, NULL, (void *)popup_add_vertex, (void *)popup_add_dadapolygon, NULL, (void *)popup_unset_flags_for_all_dadaitems_fn, (void *)popup_unset_flags_for_all_dadaitems_fn, WHITENULL);
}

void popup_delete_connected_component(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_bounce *x = (t_bounce *)d_ob->orig_obj;
	if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_CONNECTED_COMPONENT)
		delete_connected_component(x, d_ob->m_interface.mousedown_item_identifier.idx);
}

void popup_bring_to_front(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_bounce *x = (t_bounce *)d_ob->orig_obj;
	if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_CONNECTED_COMPONENT)
		graph_connected_component_bring_to_front(&x->room_graph, d_ob->m_interface.mousedown_item_identifier.idx);
}

void popup_send_to_back(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_bounce *x = (t_bounce *)d_ob->orig_obj;
	if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_CONNECTED_COMPONENT)
		graph_connected_component_send_to_back(&x->room_graph, d_ob->m_interface.mousedown_item_identifier.idx);
}

void show_connected_component_popup_menu(t_bounce *x, t_object *patcherview, t_pt pt, long modifiers)
{
	// what will be checked
	char disabled[40];
	sprintf(disabled, "0 0 %d %d 0 0 0 0 0", x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx == x->room_graph.num_connected_components - 1, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx == 0);
	
	ezdisplay_popup_menu_for_dadaitem(dadaobj_cast(x), patcherview, NULL, 0,
						 (char *)"Delete separator Bring To Front Send To Back separator Center View separator Add Ball (Add Room Element Vertex (Polygon Triangle Square Pentagon Hexagon Heptagon Octagon))", 
						 "0 0 0 0 0 0 0 0 (0 0 0)", "", disabled, "", "", 
						 (void *)popup_delete_connected_component, NULL, (void *)popup_bring_to_front, (void *)popup_send_to_back, NULL, (void *)popup_center_view, NULL, (void *)popup_add_ball, NULL, (void *)popup_add_vertex, (void *)popup_add_dadapolygon, WHITENULL);
	
	bounce_mousemove(x, patcherview, pt, modifiers);
}



////////// INTERFACE FUNCTIONS

void bounce_focusgained(t_bounce *x, t_object *patcherview) {
	if (dadaobj_focusgained(dadaobj_cast(x), patcherview))
		return;
}

void bounce_focuslost(t_bounce *x, t_object *patcherview) {
	if (dadaobj_focuslost(dadaobj_cast(x), patcherview))
		return;
}


void bounce_output_notification(t_bounce *x, t_dadaitem_identifier *ident, t_symbol *sym)
{
    t_llll *ll = llll_get();
    llll_appendsym(ll, sym);
    
    switch (ident->type) {
        case DADAITEM_TYPE_BALL:
            llll_appendsym(ll, gensym("ball"));
            llll_appendlong(ll, ident->idx + 1);
            if (dadaobj_cast(x)->m_interface.send_notifications == DADAOBJ_NOTIFY_VERBOSE)
                llll_appendllll(ll, bounce_get_single_ball(x, ident->idx));
            break;
            
        case DADAITEM_TYPE_EDGE:
            llll_appendsym(ll, gensym("edge"));
            llll_appendlong(ll, ident->idx + 1);
            if (dadaobj_cast(x)->m_interface.send_notifications == DADAOBJ_NOTIFY_VERBOSE)
                llll_appendllll(ll, graph_edge_to_llll(&x->room_graph, ident->idx));
            break;
            
        case DADAITEM_TYPE_VERTEX:
            llll_appendsym(ll, gensym("vertex"));
            llll_appendlong(ll, ident->idx + 1);
            if (dadaobj_cast(x)->m_interface.send_notifications == DADAOBJ_NOTIFY_VERBOSE)
                llll_appendllll(ll, graph_vertex_to_llll(&x->room_graph, ident->idx));
            break;
            
        case DADAITEM_TYPE_CONNECTED_COMPONENT:
            llll_appendsym(ll, gensym("component"));
            llll_appendlong(ll, ident->idx + 1);
            break;
            
        default:
            llll_appendsym(ll, _llllobj_sym_none);
            break;
    }

    dadaobj_send_notification_llll(dadaobj_cast(x), ll);
}

void bounce_mousemove(t_bounce *x, t_object *patcherview, t_pt pt, long modifiers)
{
    t_dadaitem_identifier old_ident = x->b_ob.d_ob.m_interface.mousemove_item_identifier;

	llll_format_modifiers(&modifiers, NULL);
	
	if (dadaobj_mousemove(dadaobj_cast(x), patcherview, pt, modifiers))
		return;

	if (x->b_ob.d_ob.m_interface.allow_mouse_hover) {
		if (!x->b_ob.d_ob.m_interface.mouse_is_down) {
            x->b_ob.d_ob.m_interface.mousemove_item_identifier = pixel_to_element(x, pt, patcherview, NULL);
            
            if (!dadaitem_identifier_eq(old_ident, x->b_ob.d_ob.m_interface.mousemove_item_identifier))
                bounce_output_notification(x, &x->b_ob.d_ob.m_interface.mousemove_item_identifier, gensym("hover"));
            
			jbox_redraw((t_jbox *)x);
		}
	} else {
		if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type != DADAITEM_TYPE_NONE) {
			x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
			dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
			jbox_redraw((t_jbox *)x);
		}
	}
	
	
	if (popup_menu_is_shown(dadaobj_cast(x))) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
	} else if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_BALL && x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_CHANGE_COLOR) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_CHANGE_COLOR);
	} else if ((x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_BALL || x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_CONNECTED_COMPONENT) && x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_SCALE) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_SCALE);
	} else if ((x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_BALL || x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_CONNECTED_COMPONENT) && x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_ROTATE) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_ROTATION);
	} else if ((x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_BALL || x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_CONNECTED_COMPONENT) && modifiers == eAltKey) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DUPLICATE);
	} else if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_VERTEX && modifiers == eAltKey) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DUPLICATE_POINT);
	} else if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type != DADAITEM_TYPE_NONE && modifiers == eCommandKey) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DELETE);
	} else if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type != DADAITEM_TYPE_NONE && x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_ARROW) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_MOVE);
	} else if (((x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_EDGE && x->pitch_mode == DADA_BOUNCE_EDGES_HAVE_METADATA) || (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_VERTEX && x->pitch_mode == DADA_BOUNCE_VERTICES_HAVE_METADATA)
				|| x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_CONNECTED_COMPONENT) && x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_CHANGE_PITCH) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_NOTE_UPDOWN);
	} else if (((x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_EDGE && x->pitch_mode == DADA_BOUNCE_EDGES_HAVE_METADATA) || (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_VERTEX && x->pitch_mode == DADA_BOUNCE_VERTICES_HAVE_METADATA) 
				|| x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_CONNECTED_COMPONENT) && x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_CHANGE_VELOCITY) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_CHANGE_VELOCITY);
	} else if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_VERTEX && x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_CREATE_LINE) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_GLUE);
	} else {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
	}

}


void bounce_mousedown(t_bounce *x, t_object *patcherview, t_pt pt, long modifiers){

	if (dadaobj_mousedown(dadaobj_cast(x), patcherview, pt, modifiers))
		return;

	x->b_ob.d_ob.m_interface.mousedown_item_identifier = pixel_to_element(x, pt, patcherview, &x->b_ob.d_ob.m_interface.mousedown_coord);

	if (modifiers & ePopupMenu) {
		
		switch (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type) {
			case DADAITEM_TYPE_EDGE:
				show_edge_popup_menu(x, patcherview, pt, modifiers);
				break;
			case DADAITEM_TYPE_VERTEX:
				show_vertex_popup_menu(x, patcherview, pt, modifiers);
				break;
			case DADAITEM_TYPE_BALL:
				show_ball_popup_menu(x, patcherview, pt, modifiers);
				break;
			case DADAITEM_TYPE_CONNECTED_COMPONENT:
				show_connected_component_popup_menu(x, patcherview, pt, modifiers);
				break;
			case DADAITEM_TYPE_NONE:
				show_bg_popup_menu(x, patcherview, pt, modifiers);
				break;
			default:
				break;
		}
		
	} else {
        
		llll_format_modifiers(&modifiers, NULL);
        
        bounce_output_notification(x, &x->b_ob.d_ob.m_interface.mousedown_item_identifier, gensym("click"));
        
		switch (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type) {
			case DADAITEM_TYPE_BALL:
				if (modifiers == eCommandKey) {
					if (dadaitem_ball_delete(dadaobj_cast(x), x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, DIA_UNDO_POSTPROCESS_INTERFACE))
						object_error((t_object *)x, "Can't delete ball.");
				}
				break;

			case DADAITEM_TYPE_EDGE:
				if (modifiers == eCommandKey) {
					if (delete_edge(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx))
						object_error((t_object *)x, "Can't delete edge.");
				}
				break;

			case DADAITEM_TYPE_VERTEX:
				if (modifiers == eCommandKey) {
					if (delete_vertex(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, true))
						object_error((t_object *)x, "Can't remove vertex.");
				}
				break;

			case DADAITEM_TYPE_CONNECTED_COMPONENT:
				if (modifiers == eCommandKey) {
					if (delete_connected_component(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx))
						object_error((t_object *)x, "Can't delete figure.");
				}
				break;
				
			default:
//				x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADAITEM_TYPE_NONE;
//				x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx = 0;
				break;
		}
	}
	
	jbox_redraw((t_jbox *)x);
	
}

void bounce_mouseup(t_bounce *x, t_object *patcherview, t_pt pt, long modifiers){

	llll_format_modifiers(&modifiers, NULL);
	
	if (x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_CREATE_LINE && 
		x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_VERTEX && x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_VERTEX &&
		x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx >= 0 && x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx < x->room_graph.num_vertices &&
		x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx >= 0 && x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx < x->room_graph.num_vertices) {

		bounce_undo_step_push_room(x, gensym("Add Edge"));
		graph_add_edge(&x->room_graph, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx, bounce_default_edge_metadata(x));
		postprocess_room(x);
		jbox_redraw((t_jbox *)x);
	} else if (dadaobj_mouseup(dadaobj_cast(x), patcherview, pt, modifiers))
		return;


	x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADAITEM_TYPE_NONE;
	x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag = 0;
}

void bounce_mousedrag(t_bounce *x, t_object *patcherview, t_pt pt, long modifiers){
	
	llll_format_modifiers(&modifiers, NULL);
	
	if (dadaobj_mousedrag(dadaobj_cast(x), patcherview, pt, modifiers))
		return;

	switch (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type) {
		case DADAITEM_TYPE_BALL:
			switch (modifiers) {
				case eAltKey:
					if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag & DADAITEM_IDENTIFIER_FLAG_DUPLICATED) {
						t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), patcherview, pt);
						dadaitem_ball_move(dadaobj_cast(x), x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, coord, DIA_UNDO_POSTPROCESS_INTERFACE | DIA_SNAPTOGRID);
					} else {
						long new_idx = duplicate_ball(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx);
						if (new_idx < 0) {
							object_error((t_object *)x, "Can't duplicate ball.");
							x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
						} else {
							x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx = x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx = new_idx;
							x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag |= DADAITEM_IDENTIFIER_FLAG_DUPLICATED;
							jbox_redraw((t_jbox *)x);
						}
					}
					break;
				default:
					switch (x->b_ob.d_ob.m_tools.curr_tool) {
						case DADA_TOOL_ROTATE:
							dadaitem_ball_speed_rotate(dadaobj_cast(x), x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, x->b_ob.d_ob.m_interface.mousedrag_delta_pix.y/DADA_BOUNCE_ROTATION_INTERFACE_FACTOR, DIA_UNDO_POSTPROCESS_INTERFACE);
							jbox_redraw((t_jbox *)x);
							break;
						case DADA_TOOL_CHANGE_COLOR:
							dadaitem_ball_change_hue_and_lightness(dadaobj_cast(x), x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, x->b_ob.d_ob.m_interface.mousedrag_delta_pix.x/50, -x->b_ob.d_ob.m_interface.mousedrag_delta_pix.y/100, 0.05, 0.8, DIA_UNDO_POSTPROCESS_INTERFACE);
							break;
						case DADA_TOOL_SCALE: // actually change speed
						{
							double scale_factor = pow(2, -x->b_ob.d_ob.m_interface.mousedrag_delta_pix.y/DADA_BOUNCE_ROTATION_SCALE_FACTOR);
							dadaitem_ball_speed_scale(dadaobj_cast(x), x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, scale_factor, DIA_UNDO_POSTPROCESS_INTERFACE);
							jbox_redraw((t_jbox *)x);
						}
							break;
						default:
							t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), patcherview, pt);
							dadaitem_ball_move(dadaobj_cast(x), x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, coord, DIA_UNDO_POSTPROCESS_INTERFACE | DIA_SNAPTOGRID);
							break;
					} 
					break;
			}
			break;
		
		case DADAITEM_TYPE_VERTEX:
			switch (modifiers) {
				case eAltKey:
					if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag & DADAITEM_IDENTIFIER_FLAG_DUPLICATED) {
						t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), patcherview, pt);
						move_vertex(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, coord, true);
					} else {
						t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), patcherview, pt);
						bounce_undo_step_push_room(x, gensym("Duplicate Vertex"));
						long new_idx = graph_duplicate_vertex(&x->room_graph, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, coord, true);
						if (new_idx < 0) {
							object_error((t_object *)x, "Can't duplicate vertex.");
							x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
						} else {
							x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx = x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx = new_idx;
							x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag |= DADAITEM_IDENTIFIER_FLAG_DUPLICATED;
							jbox_redraw((t_jbox *)x);
						}
					}
					break;
				default:
					switch (x->b_ob.d_ob.m_tools.curr_tool) {
						case DADA_TOOL_CHANGE_PITCH:
							if (x->pitch_mode == DADA_BOUNCE_VERTICES_HAVE_METADATA) {
								bounce_undo_step_push_room(x, gensym("Change Pitch"));
								graph_change_vertex_pitch(&x->room_graph, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, -x->b_ob.d_ob.m_interface.mousedrag_delta_pix.y * 10);
								jbox_redraw((t_jbox *)x);
							}
							break;
						case DADA_TOOL_CHANGE_VELOCITY:
							if (x->pitch_mode == DADA_BOUNCE_VERTICES_HAVE_METADATA) {
								bounce_undo_step_push_room(x, gensym("Change Velocity"));
								graph_change_vertex_velocity(&x->room_graph, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, -x->b_ob.d_ob.m_interface.mousedrag_delta_pix.y / 1.);
								jbox_redraw((t_jbox *)x);
							}
							break;
						case DADA_TOOL_CREATE_LINE:
							x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx = pixel_to_graph_vertex(x, pt, patcherview, NULL);
							x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = (x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx < 0) ? DADAITEM_TYPE_NONE : DADAITEM_TYPE_VERTEX;
							if (graph_are_vertices_connected(&x->room_graph, x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx))
								x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE; // can't connect: already connected
							jbox_redraw((t_jbox *)x);
							break;
						default:
							move_vertex(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, pix_to_coord_from_view(dadaobj_cast(x), patcherview, pt), true);
							break;
					}
					break;
			}
			break;

		case DADAITEM_TYPE_EDGE:
			switch (modifiers) {
				case eAltKey:
					break;
				default:
					switch (x->b_ob.d_ob.m_tools.curr_tool) {
						case DADA_TOOL_CHANGE_PITCH:
							if (x->pitch_mode == DADA_BOUNCE_EDGES_HAVE_METADATA) {
                                bounce_undo_step_push_room(x, gensym("Change Pitch"));
								graph_change_edge_pitch(&x->room_graph, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, -x->b_ob.d_ob.m_interface.mousedrag_delta_pix.y * 10);
								jbox_redraw((t_jbox *)x);
							}
							break;
						case DADA_TOOL_CHANGE_VELOCITY:
							if (x->pitch_mode == DADA_BOUNCE_EDGES_HAVE_METADATA) {
								bounce_undo_step_push_room(x, gensym("Change Velocity"));
								graph_change_edge_velocity(&x->room_graph, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, -x->b_ob.d_ob.m_interface.mousedrag_delta_pix.y / 1.);
								jbox_redraw((t_jbox *)x);
							}
							break;
						default:
						{
							t_pt delta = delta_pix_to_delta_coord(dadaobj_cast(x), x->b_ob.d_ob.m_interface.mousedrag_delta_pix);
							move_edge_delta(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, delta, true);
							break;
						}			
					}
					break;
			}
			break;

		case DADAITEM_TYPE_CONNECTED_COMPONENT:
			switch (modifiers) {
				case eAltKey:
					if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag & DADAITEM_IDENTIFIER_FLAG_DUPLICATED) {
						t_pt delta = delta_pix_to_delta_coord(dadaobj_cast(x), x->b_ob.d_ob.m_interface.mousedrag_delta_pix);
						move_connected_component_delta(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, delta, true);
					} else {
						t_pt delta = delta_pix_to_delta_coord(dadaobj_cast(x), x->b_ob.d_ob.m_interface.mousedrag_delta_pix);
						bounce_undo_step_push_room(x, gensym("Duplicate figure"));
						long new_idx = graph_duplicate_connected_component(&x->room_graph, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, delta);
						if (new_idx < 0) {
							object_error((t_object *)x, "Can't duplicate figure.");
							x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
						} else {
							x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx = x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx = new_idx;
							x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag |= DADAITEM_IDENTIFIER_FLAG_DUPLICATED;
							jbox_redraw((t_jbox *)x);
						}
					}
					break;
				default:
					switch (x->b_ob.d_ob.m_tools.curr_tool) {
						case DADA_TOOL_CHANGE_PITCH:
							bounce_undo_step_push_room(x, gensym("Change Pitch"));
							graph_change_connected_component_pitch(&x->room_graph, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, -x->b_ob.d_ob.m_interface.mousedrag_delta_pix.y * 10);
							jbox_redraw((t_jbox *)x);
							break;
						case DADA_TOOL_CHANGE_VELOCITY:
							bounce_undo_step_push_room(x, gensym("Change Velocity"));
							graph_change_connected_component_velocity(&x->room_graph, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, -x->b_ob.d_ob.m_interface.mousedrag_delta_pix.y * 10);
							jbox_redraw((t_jbox *)x);
							break;
						case DADA_TOOL_ROTATE:
							bounce_undo_step_push_room(x, gensym("Rotate Figure"));
							graph_rotate_connected_component(&x->room_graph, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, x->b_ob.d_ob.m_interface.mousedrag_delta_pix.y/DADA_BOUNCE_ROTATION_INTERFACE_FACTOR);
							jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
							jbox_redraw((t_jbox *)x);
							break;
						case DADA_TOOL_SCALE: // actually change speed
						{
							double scale_factor = pow(2, -x->b_ob.d_ob.m_interface.mousedrag_delta_pix.y/DADA_BOUNCE_ROTATION_SCALE_FACTOR);
							bounce_undo_step_push_room(x, gensym("Scale Figure"));
							graph_scale_connected_component(&x->room_graph, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, scale_factor);
							jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
							jbox_redraw((t_jbox *)x);
						}
							break;
						default:
						{
							t_pt delta = delta_pix_to_delta_coord(dadaobj_cast(x), x->b_ob.d_ob.m_interface.mousedrag_delta_pix);
							move_connected_component_delta(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, delta, true);
							break;
						}			
					}
					break;
			}
			break;
			
		default:
			break;
	}
}



void bounce_mousewheel(t_bounce *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc){
	llll_format_modifiers(&modifiers, NULL);  

	if (dadaobj_mousewheel(dadaobj_cast(x), view, pt, modifiers, x_inc, y_inc)) {
		jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
		jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
		jbox_redraw((t_jbox *)x);
		return;
	}
}



long bounce_keyup(t_bounce *x, t_object *patcherview, long keycode, long modifiers, long textcharacter){
			
	llll_format_modifiers(&modifiers, &keycode);

	if (dadaobj_keyup(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
		return 1;
	
	return 0;
}

long bounce_key(t_bounce *x, t_object *patcherview, long keycode, long modifiers, long textcharacter)
{
	llll_format_modifiers(&modifiers, &keycode);

	if (dadaobj_key(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
		return 1;

	switch (keycode) {
		case JKEY_SPACEBAR:	// play/stop
			if (x->b_ob.d_ob.m_play.is_playing)
				bounce_stop(x, NULL, 0, NULL);
			else
				bounce_play(x, NULL, 0, NULL);
			return 1;
		case JKEY_ESC:
			jbox_redraw((t_jbox *)x);
			return 1;
		default:
			break;
	}

	return 0;
}


void bounce_mouseenter(t_bounce *x, t_object *patcherview, t_pt pt, long modifiers) 
{
	if (dadaobj_mouseenter(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
}

void bounce_mouseleave(t_bounce *x, t_object *patcherview, t_pt pt, long modifiers) 
{
	if (dadaobj_mouseleave(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
}



//// UNDO

void bounce_postprocess_undo(t_bounce *x)
{
	jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
	jbox_redraw((t_jbox *)x);
}


void bounce_undo_step_push_room(t_bounce *x, t_symbol *operation)
{
	undo_add_interface_step(dadaobj_cast(x), DADA_FUNC_v_oX, (method)bounce_set_room, NULL, DADA_FUNC_X_o, (method)bounce_get_room, NULL, DADA_UNDO_OP_MODIFICATION,operation);
}

void bounce_undo_step_push_balls(t_bounce *x, t_symbol *operation)
{
	undo_add_interface_step(dadaobj_cast(x), DADA_FUNC_v_oX, (method)bounce_set_balls, NULL, DADA_FUNC_X_o, (method)bounce_get_balls, NULL, DADA_UNDO_OP_MODIFICATION,operation);
}

void bounce_undo_step_push(t_bounce *x, t_symbol *operation)
{
    undo_add_interface_step(dadaobj_cast(x), DADA_FUNC_v_oX, (method)bounce_set_state, NULL, DADA_FUNC_X_o, (method)bounce_get_state, NULL, DADA_UNDO_OP_MODIFICATION,operation);
}



/////////////// SEQUENCING SYSTEM

void bounce_clock(t_bounce *x, t_symbol *s) 
{
	void *old = x->b_ob.d_ob.m_play.setclock->s_thing; 
	t_object *c = 0; 
	
	// the line below can be restated as: 
	// if s is the empty symbol 
	// or s->s_thing is zero 
	// or s->s_thing is non-zero and a setclock object  
	if (s && (s == gensym("") || ((c = (t_object *) s->s_thing) && zgetfn(c, gensym("unset"))))) { 
		if (old) 
            bounce_stop(x, NULL, 0, NULL); 
		x->b_ob.d_ob.m_play.setclock = s; 
	} 
}

void bounce_play(t_bounce *x, t_symbol *s, long argc, t_atom *argv)
{
    if (x->b_ob.d_ob.m_undo.undo_before_play)
        bounce_undo_step_push(x, gensym("Play"));

    x->b_ob.d_ob.m_play.is_playing = true;
	setclock_fdelay(x->b_ob.d_ob.m_play.setclock->s_thing, x->b_ob.d_ob.m_play.m_clock, x->b_ob.d_ob.m_play.play_step_ms);
	jbox_redraw((t_jbox *)x);
    dadaobj_send_notification_sym(dadaobj_cast(x), _llllobj_sym_play);
}


void bounce_stop(t_bounce *x, t_symbol *s, long argc, t_atom *argv)
{
	setclock_unset(x->b_ob.d_ob.m_play.setclock->s_thing, x->b_ob.d_ob.m_play.m_clock);
	x->b_ob.d_ob.m_play.is_playing = false;
	jbox_redraw((t_jbox *)x);
    if (x->send_noteoffs)
        send_all_noteoffs(x);
    dadaobj_send_notification_sym(dadaobj_cast(x), _llllobj_sym_stop);
}


void bounce_unset_played_elem(t_bounce *x, t_symbol *s, long argc, t_atom *argv)
{
    x->hit_edge = -1;
}

void bounce_bang(t_bounce *x)
{
	// compute new positions for each ball
	long i, j;
	double delta_t = x->b_ob.d_ob.m_play.play_step_ms;
	long num_balls = dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_BALL);

    t_llll *to_out2 = llll_get(), *to_out3 = llll_get();
    
    dadaobj_mutex_lock(dadaobj_cast(x));
    for (i = 0; i < num_balls; i++) {
		
		if (x->balls[i].r_it.flags & D_INACTIVE)
			continue;
		
		t_pt old_coord = x->balls[i].r_it.coord;
		t_pt new_coord = pt_pt_sum(old_coord, pt_number_prod(x->balls[i].speed, delta_t/1000.));
		t_pt old_speed = x->balls[i].speed;
		t_pt new_speed = x->balls[i].speed;
		long num_hits = 0, last_hit = -1;
		t_pt prev_collision_pt;
		t_llll *collisions = llll_get();
		char angle_hit = false;
		
		while (true) {
			double dist = -1;
			long collision_idx = -1;
			t_pt collision_pt = old_coord, this_collision_pt;
			
			// detect edge hits
			for (j = 0; j < x->room_graph.num_edges; j++) {
				if (j == last_hit)
					continue;
				
				t_pt edge_start = x->room_graph.vertices[x->room_graph.edges[j].start].r_it.coord;
				t_pt edge_end = x->room_graph.vertices[x->room_graph.edges[j].end].r_it.coord;
				if (get_segment_intersection(old_coord, new_coord, edge_start, edge_end, &this_collision_pt)) {
					double this_dist = pt_norm_squared(pt_pt_diff(this_collision_pt, old_coord));
					if (dist < 0 || this_dist < dist) {
						collision_idx = j;
						collision_pt = this_collision_pt;
						dist = this_dist;
					}
				}
			}
			
			///// 1) IF NO EDGE HAS BEEN HIT, WE EXIT
			if (collision_idx < 0) 
				break; 
			
			///// 2) IF AN EDGE HAS BEEN HIT AT THE SAME POINT AS THE PREVIOUS HIT, THIS IS A CORNER, AND WE HANDLE IT SEPARATELY, to avoid infinite loops
			if (num_hits > 0 && pt_pt_distance(this_collision_pt, prev_collision_pt) < 0.001) // !pt_pt_cmp(this_collision_pt, prev_collision_pt)) 
				angle_hit = true;

			
			///// 3) OTHERWISE WE GO ON AND HANDLE THE COLLISION
			prev_collision_pt = this_collision_pt;
			last_hit = collision_idx;

			// handling collision: rebounce
			if (num_hits > 0 || old_coord.x != collision_pt.x || old_coord.y != collision_pt.y) {
				t_pt edge_start = x->room_graph.vertices[x->room_graph.edges[collision_idx].start].r_it.coord;
				t_pt edge_end = x->room_graph.vertices[x->room_graph.edges[collision_idx].end].r_it.coord;
                t_pt normal = pt_pt_diff(edge_end, edge_start);
                
                char must_bounce = (x->room_graph.edges[collision_idx].flag & DADA_GRAPH_EDGE_FLAG_PASSTHROUGH ? 0 : 1);
                
                if (must_bounce) {
                    t_jmatrix rot;
                    jgraphics_matrix_init_rotate(&rot, PIOVERTWO);
                    jgraphics_matrix_transform_point(&rot, &normal.x, &normal.y);
                    double norm = pt_norm(normal);
                    if (norm > 0)
                        normal = pt_number_prod(normal, 1./norm);
                    
                    // bouncing the speed
                    if (angle_hit)
                        new_speed = pt_number_prod(x->balls[i].speed, -1);
                    else
                        new_speed = pt_pt_sum(pt_number_prod(normal, -2 * pt_pt_scalarprod(old_speed, normal)), old_speed);
                    
                    // bouncing the coordinates
                    if (angle_hit) {
                        double dist1 = pt_pt_distance(this_collision_pt, x->balls[i].r_it.coord);
                        double dist2 = pt_norm(pt_number_prod(x->balls[i].speed, delta_t/1000.));
                        new_coord = pt_pt_sum(x->balls[i].r_it.coord, pt_number_prod(pt_number_prod(x->balls[i].speed, delta_t/1000.), rescale(dist1, 0, dist2, -1, 1)));
                    } else {
                        t_pt diff = pt_pt_diff(new_coord, collision_pt);
                        t_pt new_diff = pt_pt_sum(pt_number_prod(normal, -2 * pt_pt_scalarprod(diff, normal)), diff);
                        new_coord = pt_pt_sum(collision_pt, new_diff);
                    }
                }
				
				// send play information
				if (dadaitem_should_be_played(dadaobj_cast(x), (t_dadaitem *)&x->balls[i])) {
                    if (x->metadata_type == DADA_BOUNCE_METADATA_PITCHNVEL) {
                        double midicents;
                        double velocity;
                        if (x->pitch_mode == DADA_BOUNCE_EDGES_HAVE_METADATA) {
                            midicents = x->room_graph.edges[collision_idx].data.m_pitchnvel.pitch_mc;
                            velocity = x->room_graph.edges[collision_idx].data.m_pitchnvel.velocity;
                        } else {
                            double dist_to_collision = pt_pt_distance(this_collision_pt, edge_start);
                            double dist_whole_edge = pt_pt_distance(edge_end, edge_start);
                            midicents = rescale(dist_to_collision/dist_whole_edge, 0, 1, x->room_graph.vertices[x->room_graph.edges[collision_idx].start].data.m_pitchnvel.pitch_mc,
                                                x->room_graph.vertices[x->room_graph.edges[collision_idx].end].data.m_pitchnvel.pitch_mc);
                            velocity = rescale(dist_to_collision/dist_whole_edge, 0, 1, x->room_graph.vertices[x->room_graph.edges[collision_idx].start].data.m_pitchnvel.velocity,
                                               x->room_graph.vertices[x->room_graph.edges[collision_idx].end].data.m_pitchnvel.velocity);
                        }
                        
                        
                        if (x->velocities_depend_on_normal_speed_components)
                            velocity = CLAMP(round(velocity * fabs(pt_pt_scalarprod(old_speed, normal))/(sqrt(old_speed.x*old_speed.x + old_speed.y * old_speed.y))), DADA_MIN_VELOCITY, DADA_MAX_VELOCITY);
                        
                        x->hit_edge = collision_idx;
                        
                        schedule_fdefer((t_object *)x, (method)bounce_unset_played_elem, x->blink_time, NULL, 0, NULL);
                        
//                        dadaobj_mutex_unlock(dadaobj_cast(x));
                        append_playout_pitchnvel_data(x, to_out2, to_out3, midicents, velocity, x->use_ball_idx_as_channel ? i+1 : x->balls[i].channel, i, collision_pt, collision_idx, x->room_graph.vertices[x->room_graph.edges[collision_idx].start].connected_component_idx);
//                        dadaobj_mutex_lock(dadaobj_cast(x));
                    } else { // scores
                        t_llll *score = x->room_graph.edges[collision_idx].data.m_llllscore.ll;
                        x->hit_edge = collision_idx;
                        schedule_fdefer((t_object *)x, (method)bounce_unset_played_elem, x->blink_time, NULL, 0, NULL);
//                        dadaobj_mutex_unlock(dadaobj_cast(x));
                        append_playout_score_data(x, to_out2, to_out3, score ? llll_clone(score) : llll_get(), i, collision_pt, collision_idx, x->room_graph.vertices[x->room_graph.edges[collision_idx].start].connected_component_idx);
//                        dadaobj_mutex_lock(dadaobj_cast(x));
                    }
				}
				
				old_coord = collision_pt;
				old_speed = new_speed;
				
				num_hits++;

				x->room_graph.edges[collision_idx].flag |= 8192; // some flag we don't use
				llll_appendlong(collisions, collision_idx, 0, WHITENULL_llll);
				
				if (angle_hit) // we're done, otherwise we're stuck in an infinite loop
					break;
			}
		}
		

		x->balls[i].r_it.coord = new_coord;
		x->balls[i].speed = new_speed;

		t_llllelem *elem;
		for (elem = collisions->l_head; elem; elem = elem->l_next)
			x->room_graph.edges[elem->l_hatom.h_w.w_long].flag &= ~8192;
		llll_free(collisions);
	}
    dadaobj_mutex_unlock(dadaobj_cast(x));
    
    for (t_llllelem *elem = to_out3->l_head; elem; elem = elem->l_next) {
        if (hatom_gettype(&elem->l_hatom) == H_OBJ) {
            t_llll *ll = (t_llll *)hatom_getobj(&elem->l_hatom);
            llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 3, ll);
            llll_free(ll);
        }
    }
    for (t_llllelem *elem = to_out2->l_head; elem; elem = elem->l_next) {
        if (hatom_gettype(&elem->l_hatom) == H_OBJ) {
            t_llll *ll = (t_llll *)hatom_getobj(&elem->l_hatom);
            llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 2, ll);
            llll_free(ll);
        }
    }
    llll_free(to_out3);
    llll_free(to_out2);
	jbox_redraw((t_jbox *)x);
}

void bounce_task(t_bounce *x)
{	
	bounce_bang(x);
	setclock_fdelay(x->b_ob.d_ob.m_play.setclock->s_thing, x->b_ob.d_ob.m_play.m_clock, x->b_ob.d_ob.m_play.play_step_ms);
}
