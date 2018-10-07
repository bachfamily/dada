/**
	@file
	dada.kaleido.c
	
	@name 
	dada.kaleido
	
	@realname 
	dada.kaleido

	@type
	object
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
	Kaleidoscope interface
	
	@description
	Graphic interface in kaleidoscopic form.
	
	@discussion
	
	@category
	dada, dada interfaces, dada geometry

	@keywords
	kaleidoscope, reflection, mirror, virtual, chamber
	
	@seealso
	dada.bounce, dada.bodies, bach.tonnetz
	
	@owner
	Daniele Ghisi
*/


#include "dada.interface.h"
#include "dada.geometry.h"
#include "dada.paint.h"
#include "notation.h"
#include "dada.popupmenu.h"
//#include "dada.cursors.data.c"
#include "dada.undo.h"

#define	DADA_KALEIDO_MAX_SHAPES 16			///< Maximum number of polygons allowed in the editing chamber
											///  Must be less than or equal to 64 (otherwise change the #t_kaleido_bitfield declaration) 
#define DADA_KALEIDO_ROTATION_INTERFACE_FACTOR (2 * TWO_PI)
#define DADA_KALEIDO_ROTATION_SCALE_FACTOR 100.
#define DADA_KALEIDO_VERTEX_SELECTION_RADIUS 10
#define DADA_KALEIDO_SAMPLINGPOINT_SELECTION_PAD 4
#define DADA_KALEIDO_DEFAULT_TONEDIVISION 4

typedef t_uint64 t_kaleido_bitfield;		///< A bitfield with each bit corresponding to a polygon of the edit chamber


////////////////////////// structures

typedef enum _kaleido_element_types 
{
	DADA_KALEIDO_ELEMENT_NONE				= 0,	///< No shape
	DADA_KALEIDO_ELEMENT_SHAPE				= -10,	///< A shape
	DADA_KALEIDO_ELEMENT_VERTEX				= -11,	///< A vertex
	DADA_KALEIDO_ELEMENT_EDGE				= -12,	///< An edge
	DADA_KALEIDO_ELEMENT_CENTER				= -13,	///< The center of an ellipse
	DADA_KALEIDO_ELEMENT_RADIUSPOINT		= -14,	///< An ellipse radius point (corresponding to one of the two semiaxis)
	DADA_KALEIDO_ELEMENT_SAMPLINGPOINT		= -15,	///< A sampling point
} e_kaleido_element_types;


typedef enum _kaleido_output_when
{
    DADA_KALEIDO_OUTPUT_NEVER				= 0,	///< Never output info
    DADA_KALEIDO_OUTPUT_WHEN_HIT			= 1,	///< Output info when sampling point is inside polygon
    DADA_KALEIDO_OUTPUT_ALWAYS				= 2,	///< Always output info
} e_kaleido_output_when;


typedef enum _kaleido_metadata_type
{
    DADA_KALEIDO_METADATA_PITCHNVEL = 0,
    DADA_KALEIDO_METADATA_SCORE = 1,
} e_kaleido_metadata_type;


typedef struct _kaleido_sampling_pt
{
    t_dadaitem          r_it;                   ///< Contains the coordinate of the point, as well as the usual flags, etc.
	t_pt				coord_folded;			///< Coordinates of the folded point (i.e. the equivalent point, but reconducted inside
												///  the main chamber - if such reconduction is not possible, e.g. because the point
												///  is outside the main corolla and no extension is displayed, this info is useless,
												///  and a 0 is codified in the #is_in_main_chamber field)
	char				is_in_main_corolla;		///< Flag telling if the point is inside the main corolla or not
	double				pitch_mc;				///< Pitch associated to the sampling point
	long				velocity;				///< Velocity associated to the sampling point
    t_llll              *score;                 ///< Complex score, if needed
    t_symbol            *label;                 ///< Label
	t_kaleido_bitfield	shape_hits;             ///< Bitfield telling if the sampling point is currently hit by any of the polygons.
												///  (lsb: first polygon, and then onwards). This information is used while playing.
} t_kaleido_sampling_pt;


typedef struct _kaleido_shape
{
    t_dadaitem          r_it;
    t_shape             shape;
} t_kaleido_shape;

typedef struct _kaleido 
{
	t_dadaobj_jbox		b_ob; // root object
	
    long                sampling_metadata_type;
    
	// shapes
	long				num_shapes;     ///< The number of shapes in the chamber
	t_kaleido_shape		*shapes;        ///< The shapes in the chamber
	
	// mirrors
	long				num_steps;		///< Number of subdivision of the 180° angle. The mirror angle will be 180/num_steps
	double				mirror_size;	///< Mirrors size (in pixels)
	t_dadapolygon			main_corolla;	///< The whole circle of mirrors as a regular polygon (but without anything outside it)
	
	// sampling and playback
	long					num_sampling_points;
	t_kaleido_sampling_pt	*sampling_points;
	long					tonedivision;

	// graphic settings
	char			edit_mode;		///< Editing mode: are we displaying the chamber, i.e. shapes and the mirrors ("editing mode") or the result?
	char			show_sampling_points;

	//	behavior
	char			allow_edit_outside_chamber;
	char			play;			///< Send on/off notifications when shapes hit the sampled points. 
	char			send_hit_data;	///< Send hit data
    char            send_distance_data; ///< Send distances data, one of the #e_kaleido_output_when

	// display
	t_jrgba			j_samplingcolor;
	t_jrgba			j_chambercolor;
	double			chamber_border_size;
	char			show_chambers;
	char			extend_when_possible;	// extend outside the main corolla, whenever possible
	char			velocity_handling;
	double			sampling_points_size;

	// interface
	t_kaleido_bitfield	selected_shapes; // bitfield telling which shapes are selected
	
	// redraw/rebuild flags
	char			need_build_studio;	///< Do we need to rebuild the studio and chamber surfaces (filled with shapes)?
	char			need_build_tile;	///< Do we need to rebuild the basic tile?
    char            dont_paint;         ///< Attribute to avoid repainting. Handy for cpu-optimal tasks
	
	// preset fields
	t_atom		*preset_av;		
	long		preset_ac;		

    // solo fields (can't use the default dadaobject ones, since we need 2 different solo flags)
    char            has_solo_shapes;
    char            has_solo_samplingpoints;
    
	// utilities
	char			firsttime;
	char			itsme;
	char			creating_new_obj;
	
	// surfaces
	t_jsurface		*s_studio;
	t_jsurface		*s_chamber;
	t_jsurface		*s_tile;

	long			n_in;   // space for the inlet number used by all the proxies
    void			*n_proxy1;
	
	// outlets are declared in the dadaobj->llllobj structure, at the beginning
} t_kaleido;



///////////////////////// function prototypes
//// standard set
void *kaleido_new(t_symbol *s, long argc, t_atom *argv);
void kaleido_free(t_kaleido *x);
void kaleido_assist(t_kaleido *x, void *b, long m, long a, char *s);

void kaleido_paint(t_kaleido *x, t_object *view);
void kaleido_paint_ext(t_kaleido *x, t_object *view, t_dada_force_graphics *force_graphics);


void kaleido_int(t_kaleido *x, t_atom_long num);
void kaleido_float(t_kaleido *x, double num);
void kaleido_anything(t_kaleido *x, t_symbol *msg, long ac, t_atom *av);
void kaleido_bang(t_kaleido *x);


// setting sampling

void kaleido_setsample(t_kaleido *x, t_llll *args);
void kaleido_setsamplepitch(t_kaleido *x, t_llll *args);
void kaleido_setsamplevelocity(t_kaleido *x, t_llll *args);
void kaleido_sample(t_kaleido *x, t_llll *args);


// operations

void kaleido_rotate(t_kaleido *x, t_llll *args);
void kaleido_move(t_kaleido *x, t_llll *args);
void kaleido_scale(t_kaleido *x, t_llll *args);
void kaleido_shake(t_kaleido *x, t_llll *args);


// get/set status
void kaleido_set_state(t_kaleido *x, t_llll *state);
t_llll *kaleido_get_state(t_kaleido *x, char get_geometry, char get_shapes, char get_sampling);

t_llll *kaleido_get_geometry(t_kaleido *x);
t_llll *kaleido_get_shapes(t_kaleido *x);
t_llll *kaleido_get_sampling(t_kaleido *x);
void kaleido_set_geometry(t_kaleido *x, t_llll *geometry);
void kaleido_set_shapes(t_kaleido *x, t_llll *shapes);
void kaleido_set_sampling(t_kaleido *x, t_llll *sampling);
void kaleido_update_solos(t_kaleido *x);

char kaleido_sampling_point_should_be_played(t_kaleido *x, long idx);
char kaleido_shape_should_be_played_from_idx(t_kaleido *x, long idx);
char kaleido_shape_should_be_played(t_kaleido *x, t_kaleido_shape *shape);

void kaleido_iar(t_kaleido *x); // invalidate layers and redraw


// interface
void kaleido_focusgained(t_kaleido *x, t_object *patcherview);
void kaleido_focuslost(t_kaleido *x, t_object *patcherview);
void kaleido_mousedown(t_kaleido *x, t_object *patcherview, t_pt pt, long modifiers);
void kaleido_mousemove(t_kaleido *x, t_object *patcherview, t_pt pt, long modifiers);
void kaleido_mouseup(t_kaleido *x, t_object *patcherview, t_pt pt, long modifiers);
void kaleido_mousedrag(t_kaleido *x, t_object *patcherview, t_pt pt, long modifiers);
long kaleido_key(t_kaleido *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
long kaleido_keyup(t_kaleido *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
void kaleido_mouseenter(t_kaleido *x, t_object *patcherview, t_pt pt, long modifiers);
void kaleido_mouseleave(t_kaleido *x, t_object *patcherview, t_pt pt, long modifiers);

t_max_err kaleido_notify(t_kaleido *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void kaleido_jsave(t_kaleido *x, t_dictionary *d);
void kaleido_preset(t_kaleido *x);
void kaleido_begin_preset(t_kaleido *x, t_symbol *s, long argc, t_atom *argv);
void kaleido_restore_preset(t_kaleido *x, t_symbol *s, long argc, t_atom *argv);
void kaleido_end_preset(t_kaleido *x);

t_max_err kaleido_setattr_play(t_kaleido *x, t_object *attr, long ac, t_atom *av);
t_max_err kaleido_setattr_tonedivision(t_kaleido *x, t_object *attr, long ac, t_atom *av);
t_max_err kaleido_setattr_type(t_kaleido *x, t_object *attr, long ac, t_atom *av);



char coord_to_chamber(t_kaleido *x, t_pt coord, long *chamber_idx, t_kaleido_bitfield *shape_hit, long *first_hit, t_pt *folded_coord);
char pixel_to_chamber(t_kaleido *x, t_pt pt, t_object *view, long *chamber_idx, t_kaleido_bitfield *shape_hit, long *first_hit);
long coord_hit_test_edit_chamber(t_kaleido *x, t_pt coord, t_kaleido_bitfield *shape_hit, long max_hits);
long pixel_hit_test_edit_chamber(t_kaleido *x, t_pt pt, t_object *view, t_kaleido_bitfield *shape_hit, long max_hits);
long pixels_to_shape(t_kaleido *x, t_pt pt, t_object *view);
void get_sampling_info(t_kaleido *x, t_llll **hits, t_llll **colors);
void fold_all_sampling_points_in_main_chamber(t_kaleido *x);
void fold_sampling_point_in_main_chamber(t_kaleido *x, long idx);

void send_all_noteons(t_kaleido *x);
void send_all_noteoffs(t_kaleido *x);
void process_change(t_kaleido *x);

void kaleido_undo_postprocess(t_kaleido *x);
void kaleido_undo_step_push_shapes(t_kaleido *x, t_symbol *operation);
void kaleido_undo_step_push_sampling_points(t_kaleido *x, t_symbol *operation);







///////////////////////// utility functions


void send_playout_data_pitchnvel(t_kaleido *x, double midicents, long velocity, long MIDIchannel, long shape_num, long sample_idx)
{
	t_llll *ll = llll_get();
    t_llll *hit_ll = NULL;
	llll_appenddouble(ll, midicents, 0, WHITENULL_llll);
	llll_appendlong(ll, velocity, 0, WHITENULL_llll);
	llll_appendlong(ll, MIDIchannel, 0, WHITENULL_llll);
	if (x->send_hit_data) {
        hit_ll = llll_get();
        llll_appendsym(hit_ll, velocity > 0 ? gensym("hit") : gensym("release"));
		llll_appendllll(hit_ll, symbol_and_long_to_llll(gensym("shape"), shape_num + 1));
		llll_appendllll(hit_ll, symbol_and_long_to_llll(gensym("sample"), sample_idx + 1));
	}

    llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 3, ll);
    if (hit_ll) llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 2, hit_ll);
	
    llll_free(ll);
    if (hit_ll) llll_free(hit_ll);
}

// will also free score
void send_playout_data_score(t_kaleido *x, t_llll *score, long shape_num, long sample_idx)
{
    t_llll *hit_ll = NULL;
    if (x->send_hit_data) {
        hit_ll = llll_get();
        llll_appendsym(hit_ll, score ? gensym("hit") : gensym("release"));
        llll_appendllll(hit_ll, symbol_and_long_to_llll(gensym("shape"), shape_num + 1));
        llll_appendllll(hit_ll, symbol_and_long_to_llll(gensym("sample"), sample_idx + 1));
    }
    
    if (score) {
        llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 3, score);
        llll_free(score);
    }
    
    if (hit_ll) {
        llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 2, hit_ll);
        llll_free(hit_ll);
    }
}


void send_noteoff(t_kaleido *x, long sampling_point_idx)
{
    if (x->sampling_metadata_type == DADA_KALEIDO_METADATA_PITCHNVEL) {
        t_kaleido_bitfield test;
        long j;
        for (j = 0, test = 1; j < x->num_shapes; j++, test = test << 1)
            if (x->sampling_points[sampling_point_idx].shape_hits & test) {
                if (x->sampling_metadata_type == DADA_KALEIDO_METADATA_PITCHNVEL)
                    send_playout_data_pitchnvel(x, x->sampling_points[sampling_point_idx].pitch_mc, 0, x->shapes[j].shape.channel, j, sampling_point_idx);
                else
                    send_playout_data_score(x, NULL, j, sampling_point_idx);
            }
        
        x->sampling_points[sampling_point_idx].shape_hits = 0;
    }
}

void send_all_noteoffs(t_kaleido *x)
{
    long i;
    for (i = 0; i < x->num_sampling_points; i++)
        send_noteoff(x, i);
}

void send_all_noteons(t_kaleido *x)
{
	long i, j;
	t_kaleido_bitfield test;
	for (i = 0; i < x->num_sampling_points; i++) {
		coord_hit_test_edit_chamber(x, x->sampling_points[i].coord_folded, &x->sampling_points[i].shape_hits, NULL);
		for (j = 0, test = 1; j < x->num_shapes; j++, test = test << 1) 
            if (x->sampling_points[i].shape_hits & test) {
                if (x->sampling_metadata_type == DADA_KALEIDO_METADATA_PITCHNVEL)
                    send_playout_data_pitchnvel(x, x->sampling_points[i].pitch_mc, x->sampling_points[i].velocity, x->shapes[j].shape.channel, j, i);
                else
                    send_playout_data_score(x, x->sampling_points[i].score ? llll_clone(x->sampling_points[i].score) : llll_get(), j, i);
            }
	}
}

// process any change which has happened for the shapes
void process_change(t_kaleido *x)
{
//	llllobj_outlet_bang((t_object *)x, LLLL_OBJ_UI, 4);
    char send_distance_data = x->send_distance_data;
	
	if (x->play) {
		// If play is active, we see if some sampling point has been turned "on" or "off"
		long i, j;
		for (i = 0; i < x->num_sampling_points; i++) {
            
            if (!kaleido_sampling_point_should_be_played(x, i))
                continue;
            
			t_kaleido_bitfield new_hits, old_hits = x->sampling_points[i].shape_hits;			// e.g. old hits are 10010
			coord_hit_test_edit_chamber(x, x->sampling_points[i].coord_folded, &new_hits, NULL);	// e.g. new hits are 10100

			t_kaleido_bitfield changed, noteoffs, noteons;
			changed = old_hits ^ new_hits;	// e.g. changed is 00110
			noteoffs = changed & old_hits;	// e.g. noteoffs is 00010
			noteons = changed & new_hits;	// e.g. noteons is 00100
			
			x->sampling_points[i].shape_hits = new_hits;
			
			// Sending noteons and noteoffs
            t_kaleido_bitfield test;
            for (j = 0, test = 1; j < x->num_shapes; j++, test = test << 1) {
                if (noteoffs & test) {// sending note off
                    if (x->sampling_metadata_type == DADA_KALEIDO_METADATA_PITCHNVEL)
                        send_playout_data_pitchnvel(x, x->sampling_points[i].pitch_mc, 0, x->shapes[j].shape.channel, j, i);
                    else
                        send_playout_data_score(x, NULL, j, i);
                } else if (noteons & test) { // sending noteon
                    if (kaleido_shape_should_be_played_from_idx(x, j)) {
                        if (x->sampling_metadata_type == DADA_KALEIDO_METADATA_PITCHNVEL)
                            send_playout_data_pitchnvel(x, x->sampling_points[i].pitch_mc, x->sampling_points[i].velocity, x->shapes[j].shape.channel, j, i);
                        else
                            send_playout_data_score(x, x->sampling_points[i].score ? llll_clone(x->sampling_points[i].score) : llll_get(), j, i);
                    }
                }
            }
        }
        
        if (send_distance_data) {
            t_llll *dist = llll_get();
            for (j = 0; j < x->num_shapes; j++) {
                t_llll *this_shape_dist = llll_get();
                for (i = 0; i < x->num_sampling_points; i++) // building distance matrix
                    llll_appenddouble(this_shape_dist, pt_shape_distance(x->sampling_points[i].coord_folded, &x->shapes[j].shape));
                llll_appendllll(dist, this_shape_dist);
            }
            llll_prependsym(dist, gensym("distances"));
            llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 2, dist);
            llll_free(dist);
		}
		
	}
	
	jbox_redraw((t_jbox *)x);
}




void add_shape(t_kaleido *x, t_shape p)
{
	kaleido_undo_step_push_shapes(x, gensym("Add Shape"));
	if (x->num_shapes < DADA_KALEIDO_MAX_SHAPES) 
		x->shapes[x->num_shapes++].shape = p;
	x->need_build_studio = x->need_build_tile = true;
	jbox_redraw((t_jbox *)x);
}

// idx is 0-based (1st bit is 0)
void shift_bitfield(t_kaleido_bitfield *field, long idx, long shift)
{
	*field = ((((*field >> (idx + shift)) << (idx + shift)) ^ *field) | ((*field >> idx) << (idx + shift)));
}

// returns 0 if succesful, -1 otherwise
char delete_shape_do(t_kaleido *x, long main_idx)
{
	if (main_idx >= 0 && main_idx < x->num_shapes) {
		
		if (main_idx < x->num_shapes - 1) {
			sysmem_copyptr(&x->shapes[main_idx + 1], &x->shapes[main_idx], (x->num_shapes - main_idx - 1) * sizeof(t_shape));
			// TODO update selection bitfield
			shift_bitfield(&x->selected_shapes, main_idx + 1, -1); 
		}
		
		if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_KALEIDO_ELEMENT_SHAPE && x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx == main_idx) {
			x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADA_KALEIDO_ELEMENT_NONE;
			x->b_ob.d_ob.m_interface.mousemove_item_identifier.flag = 0;
		}
		
		if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADA_KALEIDO_ELEMENT_SHAPE && x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx == main_idx) {
			x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADA_KALEIDO_ELEMENT_NONE;
			x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag = 0;
		}
		
		x->num_shapes--;
		return 0;
	}
	return -1;
}

void delete_shape(t_kaleido *x, long main_idx)
{
	kaleido_undo_step_push_shapes(x, gensym("Delete Shape"));
	delete_shape_do(x, main_idx);
	x->need_build_studio = x->need_build_tile = true;
    dadaobj_update_solos(dadaobj_cast(x));
	process_change(x);
}

void delete_selected_shapes(t_kaleido *x) 
{
	long i;
	kaleido_undo_step_push_shapes(x, gensym("Delete Selected Shapes"));
	for (i = 0; i < x->num_shapes; i++)
		if (x->selected_shapes & (1 << i)) { 
			if (!delete_shape_do(x, i))
				i--;
		}
	
	x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADA_KALEIDO_ELEMENT_NONE;
	x->selected_shapes = 0;
	x->need_build_studio = x->need_build_tile = true;
	process_change(x);
	
}


long find_max_midichannel(t_kaleido *x)
{
	long i, max = 0;
	for (i = 1; i < x->num_shapes; i++) {
		if (x->shapes[i].shape.channel > max)
			max = x->shapes[i].shape.channel;
	}
	return max;
}


// returns the new shape index if succesful, -1 otherwise
long duplicate_shape(t_kaleido *x, long main_idx, char add_undo_step)
{
	if (main_idx >= 0 && main_idx < x->num_shapes && x->num_shapes + 1 < DADA_KALEIDO_MAX_SHAPES) {
        
        if (add_undo_step)
            kaleido_undo_step_push_shapes(x, gensym("Duplicate Shape"));
		
		clone_shape(&x->shapes[main_idx].shape, &x->shapes[x->num_shapes++].shape);

		// reassign midichannel
		x->shapes[x->num_shapes - 1].shape.channel = find_max_midichannel(x) + 1;
        
        // copying flags
        x->shapes[x->num_shapes - 1].r_it.flags = x->shapes[main_idx].r_it.flags;
		
		return x->num_shapes - 1;
	}
	return -1;
}


void duplicate_selected_shapes(t_kaleido *x, char new_shapes_are_new_selection, char transfer_mousedown) 
{
	long i;
	long mousedown_shape = x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADA_KALEIDO_ELEMENT_SHAPE ? x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx : -1;
	t_kaleido_bitfield new_selection = 0;
		
	kaleido_undo_step_push_shapes(x, gensym("Duplicate Selected Shapes"));

	for (i = 0; i < x->num_shapes; i++)
		if (x->selected_shapes & (1 << i)) {
			long new_idx = duplicate_shape(x, i, false);
			if (new_shapes_are_new_selection && new_idx >= 0)
				new_selection |= (1 << new_idx);
			if (transfer_mousedown && mousedown_shape == i)
				mousedown_shape = new_idx;
		}

	if (new_shapes_are_new_selection)
		x->selected_shapes = new_selection;
	
	if (transfer_mousedown && x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADA_KALEIDO_ELEMENT_SHAPE)
		x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx = mousedown_shape;
	
	x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag |= DADAITEM_IDENTIFIER_FLAG_DUPLICATED;
	
	x->need_build_studio = x->need_build_tile = true;
	process_change(x);
}


void move_shape(t_kaleido *x, t_kaleido_shape *shape, t_pt delta)
{
    if (shape->r_it.flags & D_INACTIVE)
        return;

	kaleido_undo_step_push_shapes(x, gensym("Move Shape"));
	shape_translate(&shape->shape, delta);
	x->need_build_studio = x->need_build_tile = true;
	process_change(x);
}


void move_all_shapes(t_kaleido *x, t_pt delta)
{
	long i;
	kaleido_undo_step_push_shapes(x, gensym("Move All Shapes"));
    for (i = 0; i < x->num_shapes; i++) {
        if (x->shapes[i].r_it.flags & D_INACTIVE)
            continue;
		shape_translate(&x->shapes[i].shape, delta);
    }
	x->need_build_studio = x->need_build_tile = true;
	process_change(x);
}


void move_selected_shapes(t_kaleido *x, t_pt delta)
{
	long i;

	if (x->selected_shapes == 0)
		return;
	
	kaleido_undo_step_push_shapes(x, gensym("Move Selected Shapes"));
	
	for (i = 0; i < x->num_shapes; i++)
		if (x->selected_shapes & (1 << i))
			shape_translate(&x->shapes[i].shape, delta);
    
	x->need_build_studio = x->need_build_tile = true;
	process_change(x);
}

void rotate_shape(t_kaleido *x, t_kaleido_shape *shape, t_pt center, double angle, char center_is_wr_to_baricenter)
{
	t_jmatrix rotmat;
    
    if (shape->r_it.flags & D_INACTIVE)
        return;
    
	kaleido_undo_step_push_shapes(x, gensym("Rotate Shape"));

	jgraphics_matrix_init_rotate(&rotmat, angle);
	if (center_is_wr_to_baricenter)
		center = pt_pt_sum(center, get_shape_barycenter(&shape->shape));

	shape_rotate_from_matrix(&shape->shape, center, &rotmat);
	
	x->need_build_studio = x->need_build_tile = true;
	process_change(x);
}

void rotate_selected_shapes(t_kaleido *x, t_pt center, double angle, char center_is_wr_to_baricenter)
{
	long i;
	t_jmatrix rotmat;
	
	if (x->selected_shapes == 0)
		return;
	
	kaleido_undo_step_push_shapes(x, gensym("Rotate Selected Shapes"));

	jgraphics_matrix_init_rotate(&rotmat, angle);
	
	for (i = 0; i < x->num_shapes; i++) {
		if (x->selected_shapes & (1 << i)) {
			t_pt this_center = center;
			
			if (center_is_wr_to_baricenter) 
				this_center = pt_pt_sum(center, get_shape_barycenter(&x->shapes[i].shape));
			
			shape_rotate_from_matrix(&x->shapes[i].shape, this_center, &rotmat);
		}
	}
	
	x->need_build_studio = x->need_build_tile = true;
	process_change(x);
}

void rotate_all_shapes(t_kaleido *x, t_pt center, double angle, char center_is_wr_to_baricenter)
{
	long i;
	t_jmatrix rotmat;

	kaleido_undo_step_push_shapes(x, gensym("Rotate All Shapes"));

	jgraphics_matrix_init_rotate(&rotmat, angle);

	for (i = 0; i < x->num_shapes; i++) {
        if (x->shapes[i].r_it.flags & D_INACTIVE)
            continue;
        
		t_pt this_center = center;

		if (center_is_wr_to_baricenter) 
			this_center = pt_pt_sum(center, get_shape_barycenter(&x->shapes[i].shape));
		
		shape_rotate_from_matrix(&x->shapes[i].shape, this_center, &rotmat);
	}
	
	x->need_build_studio = x->need_build_tile = true;
	process_change(x);
}


void scale_shape(t_kaleido *x, t_kaleido_shape *shape, t_pt center, double factor_x, double factor_y, char center_is_wr_to_baricenter)
{
    if (shape->r_it.flags & D_INACTIVE)
        return;
    
	kaleido_undo_step_push_shapes(x, gensym("Scale Shape"));
	if (center_is_wr_to_baricenter)
		center = pt_pt_sum(center, get_shape_barycenter(&shape->shape));
		
	shape_scale(&shape->shape, center, factor_x, factor_y);
	
	x->need_build_studio = x->need_build_tile = true;
	process_change(x);
}


void scale_all_shapes(t_kaleido *x, t_pt center, double factor_x, double factor_y, char center_is_wr_to_baricenter)
{
	long i;
	kaleido_undo_step_push_shapes(x, gensym("Scale All Shapes"));
	for (i = 0; i < x->num_shapes; i++) {
        if (x->shapes[i].r_it.flags & D_INACTIVE)
            return;

        t_pt this_center = center;
		if (center_is_wr_to_baricenter)
			this_center = pt_pt_sum(center, get_shape_barycenter(&x->shapes[i].shape));

		shape_scale(&x->shapes[i].shape, this_center, factor_x, factor_y);
	}
	
	x->need_build_studio = x->need_build_tile = true;
	process_change(x);
}

void scale_selected_shapes(t_kaleido *x, t_pt center, double factor_x, double factor_y, char center_is_wr_to_baricenter)
{
	long i;

	if (x->selected_shapes == 0)
		return;

	kaleido_undo_step_push_shapes(x, gensym("Scale Selected Shapes"));

	for (i = 0; i < x->num_shapes; i++) {
		if (x->selected_shapes & (1 << i)) {
			t_pt this_center = center;
			
			if (center_is_wr_to_baricenter)
				this_center = pt_pt_sum(center, get_shape_barycenter(&x->shapes[i].shape));
			
			shape_scale(&x->shapes[i].shape, this_center, factor_x, factor_y);
		}
	}
	
	x->need_build_studio = x->need_build_tile = true;
	process_change(x);
}


void change_shape_color_constraint_do(t_kaleido *x, t_shape *shape, double delta_hue, double delta_lightness)
{
	change_hue_and_lightness(&shape->color, delta_hue, delta_lightness, 0.05, 0.8);
}


void change_shape_color_constraint(t_kaleido *x, t_shape *shape, double delta_hue, double delta_lightness)
{
	kaleido_undo_step_push_shapes(x, gensym("Change Shape Color"));
	change_shape_color_constraint_do(x, shape, delta_hue, delta_lightness);
	x->need_build_tile = x->need_build_studio = true;
	jbox_redraw((t_jbox *)x);
}


void change_selected_shapes_color_constraint(t_kaleido *x, double delta_hue, double delta_lightness)
{
	long i;

	if (x->selected_shapes == 0)
		return;

	kaleido_undo_step_push_shapes(x, gensym("Change Selected Shapes Color"));

	for (i = 0; i < x->num_shapes; i++) 
		if (x->selected_shapes & (1 << i)) 
			change_shape_color_constraint_do(x, &x->shapes[i].shape, delta_hue, delta_lightness);
	
	x->need_build_studio = x->need_build_tile = true;
	process_change(x);
}


void shake_shape(t_kaleido *x, t_kaleido_shape *shape, double min_abs_shift, double max_abs_shift,
				   double min_abs_angle, double max_abs_angle, t_pt region_center, double region_radius)
{
    if (shape->r_it.flags & D_INACTIVE)
        return;

	kaleido_undo_step_push_shapes(x, gensym("Shake Shape"));
	shape_shake(&shape->shape, min_abs_shift, max_abs_shift, min_abs_angle, max_abs_angle, region_center, region_radius);
	
	x->need_build_studio = x->need_build_tile = true;
	process_change(x);
}


void shake_all_shapes(t_kaleido *x, double min_abs_shift, double max_abs_shift, 
						double min_abs_angle, double max_abs_angle, t_pt region_center, double region_radius)
{
	long i;
	kaleido_undo_step_push_shapes(x, gensym("Shake All Shapes"));
    for (i = 0; i < x->num_shapes; i++)  {
        if (x->shapes[i].r_it.flags & D_INACTIVE)
            continue;
		shape_shake(&x->shapes[i].shape, min_abs_shift, max_abs_shift, min_abs_angle, max_abs_angle, region_center, region_radius);
    }
	
	x->need_build_studio = x->need_build_tile = true;
	process_change(x);
}

void shake_selected_shapes(t_kaleido *x, double min_abs_shift, double max_abs_shift, 
					  double min_abs_angle, double max_abs_angle, t_pt region_center, double region_radius)
{
	long i;
	kaleido_undo_step_push_shapes(x, gensym("Shake Selected Shapes"));
	for (i = 0; i < x->num_shapes; i++) 
		if (x->selected_shapes & (1 << i))
			shape_shake(&x->shapes[i].shape, min_abs_shift, max_abs_shift, min_abs_angle, max_abs_angle, region_center, region_radius);
	
	x->need_build_studio = x->need_build_tile = true;
	process_change(x);
}



////// sampling points interface function


void delete_sampling_point(t_kaleido *x, long idx)
{

	kaleido_undo_step_push_sampling_points(x, gensym("Delete Sampling Point"));
	
	if (idx >= 0 && idx < x->num_sampling_points) {
        if (x->play) // if playing, send note off
			send_noteoff(x, idx);
		
		if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADA_KALEIDO_ELEMENT_SAMPLINGPOINT && x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx == idx)
			x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADA_KALEIDO_ELEMENT_NONE;

		if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_KALEIDO_ELEMENT_SAMPLINGPOINT && x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx == idx)
			x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADA_KALEIDO_ELEMENT_NONE;

		if (idx < x->num_sampling_points - 1)
			sysmem_copyptr(&x->sampling_points[idx + 1], &x->sampling_points[idx], (x->num_sampling_points - idx - 1) * sizeof(t_kaleido_sampling_pt));

		x->num_sampling_points--;
	}
	
	jbox_invalidate_layer((t_object *)x, NULL, gensym("sampling_points"));
	jbox_redraw((t_jbox *)x);
}


void move_sampling_point(t_kaleido *x, long idx, t_pt delta)
{
	kaleido_undo_step_push_sampling_points(x, gensym("Move Sampling Point"));
	
	if (idx >= 0 && idx < x->num_sampling_points) 
		x->sampling_points[idx].r_it.coord = pt_pt_sum(x->sampling_points[idx].r_it.coord, delta);
	fold_sampling_point_in_main_chamber(x, idx);
    process_change(x);
}


void change_sampling_point_pitch(t_kaleido *x, long idx, double delta_mc)
{
	kaleido_undo_step_push_sampling_points(x, gensym("Change Sampling Point Pitch"));
	if (idx >= 0 && idx < x->num_sampling_points) 
		x->sampling_points[idx].pitch_mc += delta_mc;
}

void change_sampling_point_velocity(t_kaleido *x, long idx, long delta_vel)
{
	kaleido_undo_step_push_sampling_points(x, gensym("Change Sampling Point Velocity"));
	if (idx >= 0 && idx < x->num_sampling_points) 
		x->sampling_points[idx].velocity = CLAMP(x->sampling_points[idx].velocity + delta_vel, DADA_MIN_VELOCITY, DADA_MAX_VELOCITY);
}

long add_sampling_point(t_kaleido *x, t_pt new_coord, double mc, long vel, t_symbol *label, t_llll *score)
{
    if (true) {
        kaleido_undo_step_push_sampling_points(x, gensym("Add Sampling Point"));
        
        // not the best idea ever... resizing this array all the times. However this function is called rarely (and non-programmatically).
        x->sampling_points = (t_kaleido_sampling_pt *)bach_resizeptrclear(x->sampling_points, (x->num_sampling_points + 1) * sizeof(t_kaleido_sampling_pt));
        x->sampling_points[x->num_sampling_points].r_it.coord = new_coord;
        x->sampling_points[x->num_sampling_points].pitch_mc = mc;
        x->sampling_points[x->num_sampling_points].velocity = vel;
        x->sampling_points[x->num_sampling_points].label = label;
        x->sampling_points[x->num_sampling_points].score = score;
        dadaitem_init(dadaobj_cast(x), &x->sampling_points[x->num_sampling_points].r_it, DADAITEM_TYPE_CUSTOM, 0, false, 0);
        x->num_sampling_points++;
        fold_sampling_point_in_main_chamber(x, x->num_sampling_points);
        
        return x->num_sampling_points - 1;
    }
    return -1;
}


// returns the new samplingpoint index if succesful, -1 otherwise
long duplicate_sampling_point(t_kaleido *x, long idx, t_pt new_coord, char transfer_mousedown)
{
	if (idx >= 0 && idx < x->num_sampling_points) {

		kaleido_undo_step_push_sampling_points(x, gensym("Duplicate Sampling Point"));

        // not the best idea ever... resizing this array all the times. However this function is called rarely (and non-programmatically).
		x->sampling_points = (t_kaleido_sampling_pt *)bach_resizeptr(x->sampling_points, (x->num_sampling_points + 1) * sizeof(t_kaleido_sampling_pt));
		x->sampling_points[x->num_sampling_points] = x->sampling_points[idx];
		x->sampling_points[x->num_sampling_points].r_it.coord = new_coord;
		x->num_sampling_points++;
		fold_sampling_point_in_main_chamber(x, x->num_sampling_points);
		
		if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADA_KALEIDO_ELEMENT_SAMPLINGPOINT && x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx == idx)
			x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx = x->num_sampling_points - 1;
		
		return x->num_sampling_points - 1;
	}
	return -1;
}


	
//////////////////////// global class pointer variable
t_class *kaleido_class;

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


	CLASS_NEW_CHECK_SIZE(c, "dada.kaleido", (method)kaleido_new, (method)kaleido_free, (long)sizeof(t_kaleido), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, 0);	// include textfield and Fonts attributes
	//	jbox_initclass(c, 0);
	
	// paint & utilities
	class_addmethod(c, (method) kaleido_paint,			"paint", A_CANT, 0);
	class_addmethod(c, (method) kaleido_assist,			"assist",		A_CANT, 0);  
	class_addmethod(c, (method)	kaleido_notify,			"bachnotify",		A_CANT,		0);

	// save & preset
    class_addmethod(c, (method) kaleido_preset, "preset", 0);
    class_addmethod(c, (method) kaleido_begin_preset, "begin_preset", A_GIMME, 0);
    class_addmethod(c, (method) kaleido_restore_preset, "restore_preset", A_GIMME, 0);
    class_addmethod(c, (method) kaleido_end_preset, "end_preset", 0);
	CLASS_METHOD_ATTR_PARSE(c, "begin_preset", "undocumented", gensym("long"), 0L, "1");
	CLASS_METHOD_ATTR_PARSE(c, "restore_preset", "undocumented", gensym("long"), 0L, "1");
	CLASS_METHOD_ATTR_PARSE(c, "end_preset", "undocumented", gensym("long"), 0L, "1");
	class_addmethod(c, (method) kaleido_jsave, "jsave", A_CANT, 0);
	
	// interface
	class_addmethod(c, (method) kaleido_focusgained, "focusgained", A_CANT, 0);
	class_addmethod(c, (method) kaleido_focuslost, "focuslost", A_CANT, 0);
    
    // @method (mouse) @digest Edit content
    // @description
    // @copy DADA_DOC_MOUSE_COMMANDS_STANDARD_NAVIGATION
    // • <m>click+drag</m> on a shape ot move it<br />
    //    ↪ Add the <m>Alt</m> key to duplicate it<br />
    // • <m>click</m> on a machine to select it<br />
    //    ↪ Add the <m>Shift</m> key to add it to the current selection<br />
    // • <m>Cmd+click</m> (mac) or <m>Ctrl+click</m> (win) on an shape to delete it<br />
	class_addmethod(c, (method) kaleido_mousedown, "mousedown", A_CANT, 0);
	class_addmethod(c, (method) kaleido_mousedrag, "mousedrag", A_CANT, 0);
	class_addmethod(c, (method) kaleido_mouseup, "mouseup", A_CANT, 0);
    
    // @method (keyboard) @digest Edit content
    // @description
    // @copy DADA_DOC_KEYBOARDS_COMMANDS_STANDARD_NAVIGATION
    // • <m>Cmd+Z</m> (mac) or <m>Ctrl+Z</m> (win): perform undo step<br />
    // • <m>Cmd+Shift+Z</m> (mac) or <m>Ctrl+Y</m> (win): perform redo step<br />
    // • <m>Tab</m>: toggle edit mode<br />
    // • <m>Esc</m>: send all note offs<br />
    // • <m>Cmd+A</m> (mac) or <m>Ctrl+A</m> (win): select all shapes<br />
    // • <m>Backspace</m>: delete selected shapes<br />
    // • <m>Spacebar</m>: toggle <m>play</m> attribute<br />
  	class_addmethod(c, (method) kaleido_key, "key", A_CANT, 0);
  	class_addmethod(c, (method) kaleido_keyup, "keyup", A_CANT, 0);
    
    // @method (tools) @digest Navigate
    // @description
    // @copy DADA_DOC_TOOLS_INTRO
    // @copy DADA_DOC_TOOLS_ZX
    // @copy DADA_DOC_TOOLS_NV
    // @copy DADA_DOC_TOOLS_SR
    // @copy DADA_DOC_TOOLS_Q
	class_addmethod(c, (method) kaleido_mousemove, "mousemove", A_CANT, 0);
    class_addmethod(c, (method) kaleido_mouseenter, "mouseenter", A_CANT, 0);
    class_addmethod(c, (method) kaleido_mouseleave, "mouseleave", A_CANT, 0);

	
	// @method sample @digest Set sampling points and output sampling information
	// @description The symbol <m>sample</m> followed by a list in the form
	// <b>[<m>x1</m> <m>y1</m>] [<m>x2</m> <m>y2</m>] ...</b> sets the coordinates of points on the
	// canvas to be sampled, and then outputs the sampled information (see <m>bang</m>). This is equivalent
	// as using the <m>setsample</m> message followed by a <m>bang</m>.
    // @marg 0 @name coordinates @optional 0 @type llll
    class_addmethod(c, (method)kaleido_anything,		"sample",		A_GIMME,	0);

	// @method setsample @digest Set sampling points
	// @description The symbol <m>sample</m> followed by a list in the form
	// <b>[[<m>x1</m> <m>y1</m>] <m>pitch_mc1</m> <m>velocity1</m>] [[<m>x2</m> <m>y2</m>] <m>pitch_mc2</m> <m>velocity2</m>] ...</b>
	// sets the coordinates of points on the canvas to be sampled, as well as their associated pitches (in midicents) and
	// velocities (1 to 127), which will be used at playtime. Pitches and velocities are optional, and can be dropped (in which 
	// case a default pitch of 6000 and a default velocity of 100 will be used).
    // If the <m>type</m> attribute is set to "Scores", then the syntax
    // <b>[[<m>x1</m> <m>y1</m>] <m>label1</m> <m>score1</m>]] [[<m>x2</m> <m>y2</m>] <m>label2</m> <m>score2</m>] ...</b>
    // is expected
    // @marg 0 @name sampling_points @optional 0 @type llll
	class_addmethod(c, (method)kaleido_anything,	"setsample",		A_GIMME,	0);

/*	// @method setsamplepitch @digest Set pitch of a sampling point
	// @description Each sampling point can be assigned a pitch via the <m>setsamplepitch</m> message
	// followed by a plain list of pitches (in midicents), one for each assigned sample.
	// Default pitch is 6000 (used when no pitches are defined, or when less pitches than samples are input). 
	class_addmethod(c, (method)kaleido_anything,	"setsamplepitch",		A_GIMME,	0);

	// @method setsamplevelocity @digest Set velocity of a sampling point
	// @description Each sampling point can be assigned a velocity via the <m>setsamplevelocity</m> message
	// followed by a plain list of velocities (1 to 127), one for each assigned sample.
	// Default velocity is 100 (used when no velocities are defined, or when less velocities than samples are input). 
	class_addmethod(c, (method)kaleido_anything,	"setsamplevelocity",		A_GIMME,	0);
*/
	
	// @method bang @digest Output sampling information
	// @description Output the sampling information regarding the sampling points set via the <m>sample</m> message.
	class_addmethod(c, (method)kaleido_bang,			"bang",			0);

	// @method rotate @digest Rotate elements
	// @description The word <m>rotate</m> followed the index of a shape, and an angle (in radians), rotates
	// the shape. The angle can be set in degrees by appending the degrees ° symbol after the number (without any spaces) or
    // by replacing the number with an llll in the form <b>[<m>amount_in_degrees</m> deg]</b>.
    // If the index of the shape is <m>0</m> or the <m>all</m> symbol, all shapes will be rotated.
	// If a third argument is added, in the form <b>[<m>x</m> <m>y</m>]</b>, it sets the coordinates of the origin for the rotation.
	// If no third argument is added, the default center of rotation is the shape barycenter (if a single shape is being rotated)
	// or the origin <b>[0 0]</b> if all shapes are being rotated.
	// The center of rotation llll can be replaced by the <m>barycenter</m> symbol, to specify that rotation must happen around individuals barycenters. 
	// Alternatively you can add the "barycenter" symbol as third element in order to specify that coordinates are barycentric coordinates. 
    // @marg 0 @name shape_index @optional 0 @type int/all
    // @marg 1 @name angle @optional 0 @type number/llll
    // @marg 2 @name origin @optional 1 @type llll/barycenter
	class_addmethod(c, (method)kaleido_anything,	"rotate",		A_GIMME,	0);

	// @method move @digest Translate elements
	// @description The word <m>move</m> followed the index of a shape and a vector in wrapped <b>[<m>x</m> <m>y</m>]</b> syntax,
	// translates the shape of the given vector. If the index of the shape is <m>0</m> or the <m>all</m> symbol, all shapes will be translated.
    // @marg 0 @name shape_index @optional 0 @type int/all
    // @marg 1 @name amount @optional 0 @type llll
	class_addmethod(c, (method)kaleido_anything,	"move",		A_GIMME,	0);

	// @method scale @digest Rescale elements
	// @description The word <m>scale</m> followed the index of a shape and a number, scales the given shape of the factor
	// specified by the number.
	// If the index of the shape is <m>0</m> or the <m>all</m> symbol, all shapes will be scaled.
	// If, instead of a single factor, a list in the form <b>[<m>x_scale</m> <m>y_scale</m>]</b> is given,
	// two different scale factors are applied for the X and Y axis.
	// You can provide as third argument the scaling center, in <b>[<m>x</m> <m>y</m>]</b> form. If no center is provided, 
	// by default the barycenter is used for single shape scaling, while the origin <b>[0, 0]</b> is used when all shapes are to be scaled
	// The scaling center llll can be replaced by the <m>barycenter</m> symbol, to specify that scaling must happen with respect to individuals baricenters.
	// Alternatively you can add the "barycenter" symbol as third element in order to specify that coordinates are barycentric coordinates. 
    // @marg 0 @name shape_index @optional 0 @type int/all
    // @marg 1 @name factor @optional 0 @type number
    // @marg 2 @name origin @optional 1 @type llll/barycenter
	class_addmethod(c, (method)kaleido_anything,	"scale",		A_GIMME,	0);

	// @method shake @digest Shake elements
	// @description The word <m>shake</m> followed the index of a shape, shakes the given shape, i.e. randomly modifies its position and
	// orientation. 
	// If the index of the shape is <m>0</m> or the <m>all</m> symbol, all shapes will be shaken.
	// You can specify via two optional elements the intensity of such shaking, in the form 
	// <b>[<m>min_shift</m> <m>max_shift</m>] [<m>min_rotation</m> <m>max_rotation</m>]</b>.
	// Where the each value is intended as absolute value (of the shift or of the rotation). The direction of the shift and the rotation
	// are chosen randomly. The rotation always happens around the shape's barycenter.
	// The default minimum shift and minimum rotation is 0; the default maximum shift is one fifth of the mirror size; 
	// the default maximum rotation is 10 degrees.
	// A third optional element sets the shaking region, as a circle where each shape barycenter should fall, in the form
	// <b>[[<m>center_x</m> <m>center_y</m>] <m>radius</m>]</b>. By default the center is the barycenter of the main chamber, i.e.
	// of the triangle formed by the three mirrors; the radius is by default the <m>mirrorsize</m>.
    // @marg 0 @name shape_index @optional 0 @type int/all
    // @marg 1 @name shift @optional 1 @type number/llll
    // @marg 2 @name rotation @optional 1 @type number/llll
    // @marg 3 @name shake_region @optional 1 @type llll
	class_addmethod(c, (method)kaleido_anything,	"shake",		A_GIMME,	0);
	
	// @method flush @digest Send all note-offs
	// @description The word <m>flush</m> force all the note-offs for notes being played to be sent. 
	// This is effective only when the <m>play</m> attribute is set to 1.
	class_addmethod(c, (method)kaleido_anything,	"flush",		A_GIMME,	0);

	
	class_addmethod(c, (method)kaleido_anything,	"anything",			A_GIMME,	0);
	class_addmethod(c, (method)kaleido_anything,	"setstoredstate",	A_GIMME, 0);


    
    // @method domain @digest Set the X domain
    // @description The <m>domain</m> message, followed by two numbers, sets minimum and maximum coordinates
    // to be displayed on the X axis.
    // The <m>domain</m> message,  followed by the "start" or "end" symbol and a number, sets the coordinate
    // to be displayed respectively at the left boundary or at the right boundary of the object box.
    // @marg 0 @name arguments @optional 0 @type list
    class_addmethod(c, (method)kaleido_anything,		"domain",		A_GIMME,	0);
    
    // @method range @digest Set the Y range
    // @description The <m>range</m> message, followed by two numbers, sets minimum and maximum coordinates
    // to be displayed on the Y axis
    // The <m>range</m> message,  followed by the "start" or "end" symbol and a number, sets the coordinate
    // to be displayed respectively at the bottom boundary or at top right boundary of the object box.
    // @marg 0 @name arguments @optional 0 @type list
    class_addmethod(c, (method)kaleido_anything,		"range",		A_GIMME,	0);
    
    
    // @method getdomain @digest Retrieve current X domain
    // @description The <m>getdomain</m> message outputs from the third outlet the minimum and maximum
    // coordinates displayed on the X axis, preceded by a <m>domain</m> symbol.
    class_addmethod(c, (method)kaleido_anything,		"getdomain",		A_GIMME,	0);
    
    
    // @method getrange @digest Retrieve current Y range
    // @description The <m>getrange</m> message outputs from the third outlet the minimum and maximum
    // coordinates displayed on the Y axis, preceded by a <m>range</m> symbol.
    class_addmethod(c, (method)kaleido_anything,		"getrange",		A_GIMME,	0);
    
    
    
    DADAOBJ_JBOX_DECLARE_READWRITE_METHODS(c);
    DADAOBJ_JBOX_DECLARE_IMAGE_METHODS(c);
    DADAOBJ_JBOX_DECLARE_ACCEPTSDRAG_METHODS(c);

	llllobj_class_add_out_attr(c, LLLL_OBJ_UI);
	dadaobj_class_init(c, LLLL_OBJ_UI, DADAOBJ_BBGIMAGE | DADAOBJ_ZOOM | DADAOBJ_UNDO | DADAOBJ_EMBED | DADAOBJ_MOUSEHOVER | DADAOBJ_CHANGEDBANG | DADAOBJ_NOTIFICATIONS | DADAOBJ_EXPORTTOJITTER);

	
	CLASS_ATTR_DEFAULT(c, "patching_rect", 0, "0 0 300 300");
	// @exclude dada.kaleido
	CLASS_ATTR_DEFAULT(c, "presentation_rect", 0, "0 0 300 300");
	// @exclude dada.kaleido
	

	CLASS_STICKY_ATTR(c,"category",0,"Color");
	
	CLASS_ATTR_RGBA(c, "samplingcolor", 0, t_kaleido, j_samplingcolor);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "samplingcolor", 0, "0.76 0.01 0. 1.");
	CLASS_ATTR_STYLE_LABEL(c, "samplingcolor", 0, "rgba", "Sampling Points Color");
	CLASS_ATTR_BASIC(c, "samplingcolor", 0);
	// @description Color of the markings for the sampling points
	
	CLASS_ATTR_RGBA(c, "chambercolor", 0, t_kaleido, j_chambercolor);
	CLASS_ATTR_STYLE_LABEL(c, "chambercolor",0,"rgba","Chambers Color");
	CLASS_ATTR_DEFAULTNAME_SAVE_PAINT(c,"chambercolor",0,"1. 1. 1. 1.");
	// @description Sets the color for the chamber borders

    DADAOBJ_CLASS_ATTR_RGBA_SUBSTRUCTURE(c, LLLL_OBJ_UI, "playcolor", 0, t_dadaobj, m_play, t_play_manager, play_color);
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "playcolor", 0, "0.34 0.87 0.20 1.");
    CLASS_ATTR_STYLE_LABEL(c, "playcolor", 0, "rgba", "Play Color");
    CLASS_ATTR_CATEGORY(c, "playcolor", 0, "Color");
    // @description Sets the playing color.

	CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	
	CLASS_STICKY_ATTR(c,"category",0,"Behavior");
	
	CLASS_ATTR_CHAR(c, "play", 0, t_kaleido, play);
    CLASS_ATTR_STYLE_LABEL(c, "play", 0, "onoff", "Play");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"play",0,"0");
	CLASS_ATTR_ACCESSORS(c, "play", (method)NULL, (method)kaleido_setattr_play);
	CLASS_ATTR_BASIC(c, "play", 0);

	CLASS_ATTR_CHAR(c, "sendhit", 0, t_kaleido, send_hit_data);
    CLASS_ATTR_STYLE_LABEL(c, "sendhit", 0, "onoff", "Send Hit Data");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"sendhit",0,"0");

    CLASS_ATTR_CHAR(c, "senddist", 0, t_kaleido, send_distance_data);
    CLASS_ATTR_STYLE_LABEL(c, "senddist", 0, "onoff", "Send Distance Matrix");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"senddist",0,"0");

	CLASS_ATTR_CHAR(c, "directedit", 0, t_kaleido, allow_edit_outside_chamber);
    CLASS_ATTR_STYLE_LABEL(c, "directedit", 0, "onoff", "Allow Direct Editing");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"directedit",0,"1");

	CLASS_ATTR_CHAR(c, "edit", 0, t_kaleido, edit_mode);
    CLASS_ATTR_STYLE_LABEL(c, "edit", 0, "onoff", "Display Editing Chamber");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"edit",0,"0");
	
	CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	CLASS_STICKY_ATTR(c,"category",0,"Settings");
    
    
    CLASS_ATTR_LONG(c,"type",0, t_kaleido, sampling_metadata_type);
    CLASS_ATTR_STYLE_LABEL(c,"type",0,"enumindex","Sampling Type");
    CLASS_ATTR_ENUMINDEX(c,"type", 0, "Pitch And Velocity Scores");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"type", 0, "0");
    CLASS_ATTR_ACCESSORS(c, "type", (method)NULL, (method)kaleido_setattr_type);
    // @description Sets the sampling metadata type: either a combination of pitch and velocity (simple case)
    // or a complex score.

    CLASS_ATTR_LONG(c, "count", 0, t_kaleido, num_steps);
    CLASS_ATTR_STYLE_LABEL(c, "count", 0, "text", "Number Of Mirror Chambers In Semiplane");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"count",0,"3");
	CLASS_ATTR_FILTER_MIN(c, "count", 2);
	CLASS_ATTR_BASIC(c, "count", 0);
	
	CLASS_ATTR_CHAR(c, "extend", 0, t_kaleido, extend_when_possible);
    CLASS_ATTR_STYLE_LABEL(c, "extend", 0, "onoff", "Extend Pattern For Good Configurations");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"extend",0,"1");
	CLASS_ATTR_BASIC(c, "extend", 0);

	CLASS_ATTR_DOUBLE(c, "mirrorsize", 0, t_kaleido, mirror_size);
    CLASS_ATTR_STYLE_LABEL(c, "mirrorsize", 0, "text", "Mirror Size");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"mirrorsize",0,"100");
	CLASS_ATTR_FILTER_MIN(c, "mirrorsize", 1);
	CLASS_ATTR_BASIC(c, "mirrorsize", 0);

	CLASS_ATTR_CHAR(c, "tonedivision", 0, t_kaleido, tonedivision);
    CLASS_ATTR_STYLE_LABEL(c, "tonedivision", 0, "text", "Microtonal Division");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"tonedivision",0,"2");
	CLASS_ATTR_ACCESSORS(c, "tonedivision", (method)NULL, (method)kaleido_setattr_tonedivision);

	CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	CLASS_STICKY_ATTR(c,"category",0,"Appearance");
    
    CLASS_ATTR_CHAR(c, "nopaint", 0, t_kaleido, dont_paint);
    CLASS_ATTR_STYLE_LABEL(c, "nopaint", 0, "onoff", "Don't Paint Kaleidoscopes");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"nopaint",0,"0");

	CLASS_ATTR_CHAR(c, "showsampling", 0, t_kaleido, show_sampling_points);
    CLASS_ATTR_STYLE_LABEL(c, "showsampling", 0, "onoff", "Show Sampling Points");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showsampling",0,"1");
	
	CLASS_ATTR_DOUBLE(c, "chamberborder", 0, t_kaleido, chamber_border_size);
    CLASS_ATTR_STYLE_LABEL(c, "chamberborder", 0, "text", "Chamber Border Width");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"chamberborder",0,"0.5");
	CLASS_ATTR_FILTER_MIN(c, "chamberborder", 0);
	
	CLASS_ATTR_CHAR(c, "showchambers", 0, t_kaleido, show_chambers);
    CLASS_ATTR_STYLE_LABEL(c, "showchambers", 0, "onoff", "Show Virtual Chambers");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showchambers",0,"1");

	CLASS_ATTR_DOUBLE(c, "samplingptsize", 0, t_kaleido, sampling_points_size);
    CLASS_ATTR_STYLE_LABEL(c, "samplingptsize", 0, "text", "Sampling Point Size");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"samplingptsize",0,"5.");
	
	CLASS_ATTR_CHAR(c, "showvelocity", 0, t_kaleido, velocity_handling); 
	CLASS_ATTR_STYLE_LABEL(c,"showvelocity",0,"enumindex","Show Velocity");
	CLASS_ATTR_ENUMINDEX(c,"showvelocity", 0, "None Colorscale Colorspectrum Point Size");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showvelocity",0,"3");
	// @description Attribute deciding how the velocity of a sampling point should be displayed:
	// <m>None</m>: velocity must be graphically ignored<br />
	// <m>Colorscale</m>: by changing the lightness of the point inner color<br />
	// <m>Colorspectrum</m>: by changing the point inner color over a spectrum of colors (red to blue) <br />
	// <m>Point Size</m>: by changing the point size

	CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	kaleido_class = c;

	dev_post("dada.kaleido compiled %s %s", __DATE__, __TIME__);
	return 0;
}

void rebuild_main_corolla_dadapolygon(t_kaleido *x)
{
	long i;
	long num_vertices = x->num_steps * 2;
	x->main_corolla.num_vertices = num_vertices;
	for (i = 0; i < num_vertices && i < DADA_POLYGON_MAX_VERTICES; i++) {
		x->main_corolla.vertex[i].x = x->mirror_size * cos(TWO_PI * ((double)i/num_vertices));
		x->main_corolla.vertex[i].y = x->mirror_size * sin(TWO_PI * ((double)i/num_vertices));
	}
}

t_max_err kaleido_notify(t_kaleido *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	if (msg == _sym_attr_modified) {
		t_symbol *attr_name = (t_symbol *)object_method((t_object *)data, _sym_getname);
		if (attr_name == _llllobj_sym_zoom || attr_name == gensym("mirrorsize") || attr_name == gensym("showchambers")) {
			x->need_build_studio = x->need_build_tile = true;
			jbox_redraw((t_jbox *)x);
		} else if (attr_name == gensym("count")) {
			x->need_build_tile = true;
			jbox_redraw((t_jbox *)x);
		} else if (attr_name == gensym("showvelocity")) {
			jbox_invalidate_layer((t_object *)x, NULL, gensym("sampling_points"));
			jbox_redraw((t_jbox *)x);
		} 
		
		if (attr_name == gensym("mirrorsize") || attr_name == gensym("count"))
			rebuild_main_corolla_dadapolygon(x);
		
		if (!x->itsme)
			process_change(x);
	}
	
	return MAX_ERR_NONE;
}

t_max_err kaleido_setattr_play(t_kaleido *x, t_object *attr, long ac, t_atom *av)
{
	if (ac && av && is_atom_number(av)) {
		char old_play = x->play, new_play = (atom_getlong(av) == 0 ? 0 : 1);
		if (old_play != new_play) {
			x->play = new_play;
            dadaobj_cast(x)->m_play.is_playing = x->play;
			if (!x->creating_new_obj) {
                dadaobj_send_notification_sym(dadaobj_cast(x), new_play ? _llllobj_sym_play : _llllobj_sym_stop);
				if (old_play)
					send_all_noteoffs(x);
				else
					send_all_noteons(x);
			}
		}
//		object_attr_setdisabled((t_object *)x, gensym("extendedplay"), x->play == 0);
	}
	return MAX_ERR_NONE;
}

t_max_err kaleido_setattr_tonedivision(t_kaleido *x, t_object *attr, long ac, t_atom *av)
{
	if (ac && av && is_atom_number(av)) {
		x->tonedivision = MAX(2, atom_getlong(av));
		if (x->tonedivision != 2 && x->tonedivision != 4 && x->tonedivision != 8)
			object_warn((t_object *)x, "Only 2, 4 and 8 tonedivision are graphically supported.");
	}
	return MAX_ERR_NONE;
}


t_max_err kaleido_setattr_type(t_kaleido *x, t_object *attr, long ac, t_atom *av)
{
    if (ac && av && is_atom_number(av)) {
        long new_type = atom_getlong(av);
        if (new_type != x->sampling_metadata_type) {
            x->sampling_metadata_type = new_type;
        }
    }
    return MAX_ERR_NONE;
}


void kaleido_begin_preset(t_kaleido *x, t_symbol *s, long argc, t_atom *argv)
{
	x->preset_ac = atom_getlong(argv) ;
	x->preset_av = (t_atom *)bach_newptr(x->preset_ac * sizeof(t_atom));
	
	// could allocate memory here etc.
	//	post("begin_preset %ld values will be arriving",x->b_ob.d_ob.preset_ac);
}


void kaleido_restore_preset(t_kaleido *x, t_symbol *s, long argc, t_atom *argv)
{
	long start, size;
	
	start = atom_getlong(argv);
	size = atom_getlong(argv + 1);
	//	post("restore_preset start %ld size %ld", start,size);
	
	sysmem_copyptr(argv+2, x->preset_av+start, size*sizeof(t_atom));
}

void kaleido_end_preset(t_kaleido *x)
{
	//	post("end_preset received");
	kaleido_anything(x, NULL, x->preset_ac,x->preset_av);
	bach_freeptr(x->preset_av);
}

void kaleido_preset(t_kaleido *x){
	t_atom temp[256];
	void *buf;
	long i, index, size;
	char wrote = false, begin = true, done = false;
	
	t_llll *data = kaleido_get_state(x, true, true, true);
	llll_prependsym(data, gensym("setstoredstate"), 0, WHITENULL_llll);
	
	// 1. we deparse the list
	t_atom *av = NULL, *this_av = NULL;
	long ac = llll_deparse(data, &av, 0, LLLL_D_FLOAT64 | LLLL_D_QUOTE); //offset 0
	this_av = av;
	
	// 2. We fill the binbuf
	buf = gensym("_preset")->s_thing; 
	if (!buf)	// no preset object
		return;
	
	index = 0;
	while (!done) {
		i = index;
		size = ac - index;
		if (size > 250)
			size = 250;
		else	// you are at the end
			done = true;
		
		sysmem_copyptr(this_av, temp+5, 250*sizeof(t_atom));
		
		if (size) {
			atom_setobj(temp, x);
			atom_setsym(temp + 1, ob_sym(x));
			if (begin) {
				atom_setsym(temp + 2, gensym("begin_preset"));
				atom_setlong(temp + 3, ac);
				binbuf_insert(buf, NULL, 4, temp);
				begin = false;
			}
			atom_setsym(temp + 2, gensym("restore_preset"));
			atom_setlong(temp + 3, index);
			atom_setlong(temp + 4, size);
			binbuf_insert(buf, NULL, size + 5, temp);
			wrote = true;
		}
		index += size;
		this_av += 250;
	}
	if (wrote) {
		atom_setobj(temp, x);
		atom_setsym(temp + 1, ob_sym(x));
		atom_setsym(temp + 2, gensym("end_preset"));
		binbuf_insert(buf, NULL, 3, temp);
	}
	
	if (av) bach_freeptr(av);
}


void kaleido_jsave(t_kaleido *x, t_dictionary *d)
{
	if (x->b_ob.d_ob.save_data_with_patcher){
		if (x->b_ob.r_ob.l_dictll) {
			llll_store_in_dictionary(x->b_ob.r_ob.l_dictll, d, "kaleido_data", NULL);
		} else {
			t_llll *data = kaleido_get_state(x, true, true, true);
			llll_store_in_dictionary(data, d, "kaleido_data", NULL);
			llll_free(data);
		}
	} 
}
		
t_llll *kaleido_get_geometry(t_kaleido *x)
{
	t_llll *out_ll = llll_get();
    llll_appendsym(out_ll, gensym("geometry"));
	llll_appendllll(out_ll, symbol_and_long_to_llll(gensym("count"), x->num_steps));
    llll_appendllll(out_ll, symbol_and_double_to_llll(gensym("mirrorsize"), x->mirror_size));
    llll_appendllll(out_ll, symbol_and_long_to_llll(gensym("extend"), x->extend_when_possible));
	return out_ll;
}

t_llll *kaleido_get_single_shape(t_kaleido *x, long idx)
{
    long i = idx;
    t_llll *shapes_ll = llll_get();
    switch (x->shapes[i].shape.type) {
        case DADA_SHAPE_ELLIPSE:
            llll_appendsym(shapes_ll, gensym("ellipse"), 0, WHITENULL_llll);
            llll_appendllll(shapes_ll, symbol_and_llll_to_llll_chained(gensym("color"), color_to_llll(&x->shapes[i].shape.color)));
            llll_appendllll(shapes_ll, symbol_and_llll_to_llll_chained(gensym("center"), pt_to_llll(x->shapes[i].shape.shape.ellipse.center, 0)));
            llll_appendllll(shapes_ll, symbol_and_llll_to_llll_chained(gensym("radius"), pt_to_llll(x->shapes[i].shape.shape.ellipse.radius, 0)));
            llll_appendllll(shapes_ll, symbol_and_double_to_llll(gensym("rotation"), rad2deg(x->shapes[i].shape.shape.ellipse.rotation)));
            llll_appendllll(shapes_ll, symbol_and_long_to_llll(gensym("channel"), x->shapes[i].shape.channel));
            dadaitem_append_flags_to_llll(shapes_ll, &x->shapes[i].r_it, true);
            break;
        case DADA_SHAPE_POLYGON:
        {
            t_llll *vertices = llll_get();
            llll_appendsym(shapes_ll, gensym("polygon"), 0, WHITENULL_llll);
            llll_appendllll(shapes_ll, symbol_and_llll_to_llll_chained(gensym("color"), color_to_llll(&x->shapes[i].shape.color)));
            llll_appendllll(shapes_ll, symbol_and_long_to_llll(gensym("channel"), x->shapes[i].shape.channel));
            llll_appendsym(vertices, gensym("vertices"));
            for (long j = 0; j < x->shapes[i].shape.shape.polygon.num_vertices; j++)
                llll_appendllll(vertices, pt_to_llll(x->shapes[i].shape.shape.polygon.vertex[j], 0));
            llll_appendllll(shapes_ll, vertices);
            dadaitem_append_flags_to_llll(shapes_ll, &x->shapes[i].r_it, true);
        }
            break;
        default:
            break;
    }
    return shapes_ll;
}


t_llll *kaleido_get_shapes(t_kaleido *x)
{
	t_llll *out_ll = llll_get();
	for (long i = 0; i < x->num_shapes; i++)
		llll_appendllll(out_ll, kaleido_get_single_shape(x, i), 0, WHITENULL_llll);
    
	llll_prependsym(out_ll, gensym("shapes"), 0, WHITENULL_llll);
	return out_ll;
}


t_llll *kaleido_get_single_sampling_pt(t_kaleido *x, long idx)
{
    long i = idx;
    t_llll *ll = llll_get();
    llll_appendllll(ll, symbol_and_llll_to_llll_chained(gensym("coord"), pt_to_llll(x->sampling_points[i].r_it.coord, 0)));
    if (x->sampling_metadata_type == DADA_KALEIDO_METADATA_PITCHNVEL) {
        llll_appendllll(ll, symbol_and_double_to_llll(gensym("pitch"), x->sampling_points[i].pitch_mc));
        llll_appendllll(ll, symbol_and_long_to_llll(gensym("velocity"), x->sampling_points[i].velocity));
    } else {
        llll_appendllll(ll, symbol_and_llll_to_llll_chained(gensym("score"), x->sampling_points[i].score ? llll_clone(x->sampling_points[i].score) : llll_get()));
        llll_appendllll(ll, symbol_and_symbol_to_llll(gensym("label"), x->sampling_points[i].label ? x->sampling_points[i].label : _llllobj_sym_score));
    }
    dadaitem_append_flags_to_llll(ll, &x->sampling_points[i].r_it, true);
    return ll;
}

t_llll *kaleido_get_sampling(t_kaleido *x)
{
	long i;
	t_llll *out_ll = llll_get();
	for (i = 0; i < x->num_sampling_points; i++)
		llll_appendllll(out_ll, kaleido_get_single_sampling_pt(x, i));
	llll_prependsym(out_ll, gensym("sampling"), 0, WHITENULL_llll);
	return out_ll;
}



t_llll *kaleido_get_state(t_kaleido *x, char get_geometry, char get_shapes, char get_sampling)
{
	// How do we save the information?
	// Three sublists: 1) kaleidoscope geometry, 2) shapes, 3) sampling points
	// 1) in the form: ("geometry" num_steps mirror_size extend_when_possible)
	// 2) in the form: ("shapes" SHAPE1 SHAPE2 SHAPE3...) with SHAPE equal to
	//					(polygon (r g b a) midichannel (x1 y1) (x2 y2) (x3 y3) ...) for a polygon and 
	//                 (ellipse (r g b a) midichannel (xcenter ycenter) (radius_x radius_y) rotation_angle) for an ellipse
	// 3) in the form: ("sampling" PT1 PT2...) with PT equal to 
	//					((x y) pitch velocity) for each point
	
	t_llll *data = llll_get();
	
    llll_appendsym(data, gensym("kaleido"));
    
	if (get_geometry)
		llll_appendllll(data, kaleido_get_geometry(x), 0, WHITENULL_llll);
	if (get_shapes)
		llll_appendllll(data, kaleido_get_shapes(x), 0, WHITENULL_llll);
	if (get_sampling)
		llll_appendllll(data, kaleido_get_sampling(x), 0, WHITENULL_llll);
	
	return data;
}

void kaleido_set_geometry(t_kaleido *x, t_llll *geometry)
{
    long count = x->num_steps;
    double mirrorsize = x->mirror_size;
    long extend = x->extend_when_possible;
    
    dadaobj_parseargs(dadaobj_cast(x), geometry, (char *)"ldl", gensym("count"), &count, gensym("mirrorsize"), &mirrorsize, gensym("extend"), &extend);
    
    object_attr_setlong(x, _sym_count, count);
	object_attr_setfloat(x, gensym("mirrorsize"), mirrorsize);
	object_attr_setchar(x, gensym("extend"), (char)extend);
}


void kaleido_set_shapes(t_kaleido *x, t_llll *shapes)
{
	long i, j;
	t_llllelem *temp, *elem;
	
	x->num_shapes = MAX(0, shapes->l_size - 1);
	
	for (i = 0, elem = shapes->l_head ? shapes->l_head->l_next : NULL; elem && i < DADA_KALEIDO_MAX_SHAPES; elem = elem->l_next, i++) {
		if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
			t_llll *shape_ll = hatom_getllll(&elem->l_hatom);
			
			if (hatom_gettype(&shape_ll->l_head->l_hatom) == H_SYM) {
				t_symbol *type = hatom_getsym(&shape_ll->l_head->l_hatom);
				
                if (type == gensym("polygon")) {
                    t_llll *vertices = NULL;
                    x->shapes[i].shape.type = DADA_SHAPE_POLYGON;
                    
                    dadaobj_parseargs(dadaobj_cast(x), shape_ll, (char *)"Cl4F", gensym("color"), &x->shapes[i].shape.color, gensym("channel"), &x->shapes[i].shape.channel, gensym("vertices"), &vertices, gensym("flags"), &x->shapes[i].r_it.flags);
                    
                    x->shapes[i].shape.shape.polygon.num_vertices = MAX(0, vertices ? vertices->l_size : 0);
                    for (j = 0, temp = vertices ? vertices->l_head : NULL; temp && j < DADA_POLYGON_MAX_VERTICES; j++, temp = temp->l_next)
                        if (hatom_gettype(&temp->l_hatom) == H_LLLL)
                            x->shapes[i].shape.shape.polygon.vertex[j] = llll_to_pt(hatom_getllll(&temp->l_hatom));
                } else if (type == gensym("ellipse")) {
                    x->shapes[i].shape.type = DADA_SHAPE_ELLIPSE;
                    
                    dadaobj_parseargs(dadaobj_cast(x), shape_ll, (char *)"ClPPd", gensym("color"), &x->shapes[i].shape.color, gensym("channel"), &x->shapes[i].shape.channel, gensym("center"), &x->shapes[i].shape.shape.ellipse.center, gensym("radius"), &x->shapes[i].shape.shape.ellipse.radius, gensym("rotation"), &x->shapes[i].shape.shape.ellipse.rotation, gensym("flags"), &x->shapes[i].r_it.flags);

                    x->shapes[i].shape.shape.ellipse.rotation = deg2rad(x->shapes[i].shape.shape.ellipse.rotation);
                } else {
                    x->shapes[i].shape.type = DADA_SHAPE_NONE;
                }
			}
		}
	}
}


void kaleido_free_sampling_points(t_kaleido *x)
{
    for (long i = 0; i < x->num_sampling_points; i++)
        if (x->sampling_points[i].score)
            llll_free(x->sampling_points[i].score);
    bach_freeptr(x->sampling_points);
}

void kaleido_set_sampling(t_kaleido *x, t_llll *sampling)
{
	t_llllelem *elem;
	long i;
	
    kaleido_free_sampling_points(x);
	
	if (sampling->l_size > 1) {
		x->num_sampling_points = sampling->l_size - 1;
		x->sampling_points = (t_kaleido_sampling_pt *)bach_newptrclear((sampling->l_size - 1) * sizeof(t_kaleido_sampling_pt));
		for (i = 0, elem = sampling->l_head->l_next; elem; elem = elem->l_next, i++) {
			if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
				t_llll *point_ll = hatom_getllll(&elem->l_hatom);
                t_llll *score = NULL;
                t_symbol *label = _llllobj_sym_score;
                dadaobj_parseargs(dadaobj_cast(x), point_ll, (char *)"Pdls4F",
                                  gensym("coord"), &x->sampling_points[i].r_it.coord,
                                  gensym("pitch"), &x->sampling_points[i].pitch_mc,
                                  gensym("velocity"), &x->sampling_points[i].velocity,
                                  gensym("label"), &label,
                                  gensym("score"), &score,
                                  gensym("flags"), &x->sampling_points[i].r_it.flags);
                x->sampling_points[i].label = label;
                if (score)
                    x->sampling_points[i].score = score;
			}
		}
	} else {
		x->num_sampling_points = 0;
		x->sampling_points = NULL;
	}
}

// see kaleido_get_state about the codification of info
void kaleido_set_state(t_kaleido *x, t_llll *state)
{
    if (!state)
        return;
    
    if (!x->creating_new_obj && x->play)
        send_all_noteoffs(x);
    
    x->itsme = true;
    
    t_llllelem *el;
    for (el = state->l_head; el; el = el->l_next) {
        if (hatom_gettype(&el->l_hatom) == H_LLLL) {
            t_llll *ll = hatom_getllll(&el->l_hatom);
            if (ll && ll->l_head && hatom_gettype(&ll->l_head->l_hatom) == H_SYM) {
                t_symbol *router = hatom_getsym(&ll->l_head->l_hatom);
                if (router == gensym("geometry"))
                    kaleido_set_geometry(x, ll);
                else if (router == gensym("shapes"))
                    kaleido_set_shapes(x, ll);
                else if (router == gensym("sampling"))
                    kaleido_set_sampling(x, ll);
            }
        }
    }
    
    x->itsme = false;
    
    dadaobj_update_solos(dadaobj_cast(x));
    
    // reprocess stuff
    fold_all_sampling_points_in_main_chamber(x);
    jbox_invalidate_layer((t_object *)x, NULL, gensym("sampling_points"));
    process_change(x);

}


void kaleido_update_solos(t_kaleido *x)
{
    long i;
    char has_solos_shapes = 0, has_solo_samplingpoints = 0;
    for (i = 0; i < x->num_shapes; i++) {
        if (x->shapes[i].r_it.flags & D_SOLO) {
            has_solos_shapes = true;
            break;
        }
    }
    for (i = 0; i < x->num_sampling_points; i++) {
        if (x->sampling_points[i].r_it.flags & D_SOLO) {
            has_solo_samplingpoints = true;
            break;
        }
    }
    x->has_solo_samplingpoints = has_solo_samplingpoints;
    x->has_solo_shapes = has_solos_shapes;
    kaleido_iar(x);
}


void kaleido_assist(t_kaleido *x, void *b, long m, long a, char *s)
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
        else if (a == 2)	// @out 2 @type llll @digest Information about sampling point hits
            sprintf(s, "llll (%s): Hit Data", type);
        else if (a == 3)	// @out 3 @type llll @digest Playout
            sprintf(s, "llll (%s): Playout", type);
        else 	// @out 4 @type bang @digest bang when object is changed via the interface
            sprintf(s, "bang when Changed"); 			
    }
}

void kaleido_free(t_kaleido *x)
{
	if (x->s_chamber)
		jgraphics_surface_destroy(x->s_chamber);
	if (x->s_studio)
		jgraphics_surface_destroy(x->s_studio);
	if (x->s_tile)
		jgraphics_surface_destroy(x->s_tile);

	bach_freeptr(x->shapes);
    kaleido_free_sampling_points(x);
	object_free_debug(x->n_proxy1);

	dadaobj_jbox_free((t_dadaobj_jbox *)x); // jbox_free and llllobj_free are inside here
}

void kaleido_iar(t_kaleido *x)
{
    jbox_invalidate_layer((t_object *)x, NULL, gensym("sampling_points"));
    x->need_build_studio = x->need_build_tile = true;
    jbox_redraw((t_jbox *)x);
}

void *kaleido_new(t_symbol *s, long argc, t_atom *argv)
{
	t_kaleido *x = NULL;
	t_dictionary *d = NULL;
	long boxflags;
	t_llll *llll_for_rebuild = NULL;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;    
	
	if ((x = (t_kaleido *)object_alloc_debug(kaleido_class))) {
		
		x->creating_new_obj = true;
		
		x->num_shapes = 0;
		x->firsttime = true;
		x->need_build_studio = true;
		x->selected_shapes = 0;
		x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADA_KALEIDO_ELEMENT_NONE;
		x->num_sampling_points = 0;
		x->sampling_points = NULL;
		
		x->shapes = (t_kaleido_shape *)bach_newptrclear(DADA_KALEIDO_MAX_SHAPES * sizeof(t_kaleido_shape));
		
//		add_shape(x, build_triangle(build_jrgba(0.3, 0, 0, 0.5), 0, 0, 100, 100, 0, 100));
//		add_shape(x, build_triangle(build_jrgba(0, 0.3, 0, 0.5), 20, 40, 80, 30, 0, 100));
		add_shape(x, ezbuild_dadapolygon(build_jrgba(0.3, 0, 0, 0.5), 1, 3, 0., 0., 100., 100., 0., 100.));
		add_shape(x, ezbuild_dadapolygon(build_jrgba(0., 0.3, 0, 0.5), 2, 3, 20., 40., 80., 30., 0., 100.));
		add_shape(x, ezbuild_dadapolygon(build_jrgba(0, 0, 0.3, 0.5), 3, 4, 0., 0., 0., 50., 50., 50., 50., 0.));
		
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
		//		| JBOX_DRAWBACKGROUND
		//      | JBOX_NOFLOATINSPECTOR
		//      | JBOX_MOUSEDRAGDELTA
		//      | JBOX_TEXTFIELD
		;
		
		jbox_new((t_jbox *)x, boxflags, argc, argv);
		x->b_ob.r_ob.l_box.b_firstin = (t_object *)x;
		x->n_proxy1 = proxy_new((t_object *) x, 1, &x->n_in);

		dadaobj_jbox_setup((t_dadaobj_jbox *)x, DADAOBJ_BBGIMAGE | DADAOBJ_ZOOM | DADAOBJ_UNDO | DADAOBJ_CHANGEDBANG | DADAOBJ_NOTIFICATIONS, build_pt(1., 1.), 3, 4, 2, (dada_paint_ext_fn)kaleido_paint_ext, (invalidate_and_redraw_fn)kaleido_iar, "qvnrs", 2, "b4444");
		dadaobj_addfunctions(dadaobj_cast(x), (dada_mousemove_fn)kaleido_mousemove, NULL, (method)kaleido_undo_postprocess, (get_state_fn)kaleido_get_state, (set_state_fn)kaleido_set_state, NULL, NULL, NULL);

        x->b_ob.d_ob.update_solos = (update_solos_fn)kaleido_update_solos;
        
		attr_dictionary_process(x,d);
		
		rebuild_main_corolla_dadapolygon(x);
		
		if ((llll_for_rebuild = llll_retrieve_from_dictionary(d, "kaleido_data"))) { // new method
			llllobj_manage_dict_llll((t_object *)x, LLLL_OBJ_UI, llll_for_rebuild);
			kaleido_set_state(x, llll_for_rebuild);
			llll_free(llll_for_rebuild);
		}
		
		jbox_ready((t_jbox *)x);
        
        dadaobj_set_current_version_number(dadaobj_cast(x));

		x->creating_new_obj = false;
	}
	return x;
}

void kaleido_int(t_kaleido *x, t_atom_long num)
{
	t_atom argv[1];
	atom_setlong(argv, num);
	kaleido_anything(x, _sym_list, 1, argv);
}

void kaleido_float(t_kaleido *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	kaleido_anything(x, _sym_list, 1, argv);
}

// output sampled information
void kaleido_bang(t_kaleido *x)
{	
	t_llll *sampled_hits = NULL, *sampled_colors = NULL;
	get_sampling_info(x, &sampled_hits, &sampled_colors);
	llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 2, sampled_colors);
	llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, sampled_hits);
	llll_free(sampled_colors);
	llll_free(sampled_hits);
}

void kaleido_dump(t_kaleido *x, char get_geometry, char get_shapes, char get_sampling)
{	
	t_llll *ll = kaleido_get_state(x, get_geometry, get_shapes, get_sampling);
	llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 0, ll);
	llll_free(ll);
}


void kaleido_anything(t_kaleido *x, t_symbol *msg, long ac, t_atom *av)
{
	dadaobj_anything(dadaobj_cast(x), msg, ac, av);

	t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, msg, ac, av, LLLL_PARSE_CLONE);
	if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
		t_symbol *router = hatom_getsym(&parsed->l_head->l_hatom);
		llll_behead(parsed);
		
        if (dadaobj_anything_handle_domain_or_range(dadaobj_cast(x), router, parsed)) {
            // nothing to do!
        } else if (router == gensym("sample"))
			kaleido_sample(x, parsed);
		else if (router == gensym("setsample"))
			kaleido_setsample(x, parsed);
		else if (router == gensym("setsamplepitch"))
			kaleido_setsamplepitch(x, parsed);
		else if (router == gensym("setsamplevelocity"))
			kaleido_setsamplevelocity(x, parsed);
		else if (router == gensym("rotate"))
			kaleido_rotate(x, parsed);
		else if (router == gensym("move"))
			kaleido_move(x, parsed);
		else if (router == gensym("scale"))
			kaleido_scale(x, parsed);
		else if (router == gensym("shake"))
			kaleido_shake(x, parsed);
		else if (router == gensym("setstoredstate") || router == gensym("kaleido"))
			kaleido_set_state(x, parsed);
		else if (router == gensym("flush") && x->play)
			send_all_noteoffs(x);
		else if (router == _sym_dump)
			kaleido_dump(x, parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("geometry")), 
						 parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("shapes")),
						 parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("sampling")));
		
	} else if (parsed) {
		kaleido_set_state(x, parsed);
	}
	llll_free(parsed);
}
				 
				 
				 
void kaleido_setsample(t_kaleido *x, t_llll *args)
{
	t_llllelem *elem;
	long i;
	
	if (x->play)
		send_all_noteoffs(x);

	x->num_sampling_points = 0;
	
	if (args && args->l_size > 0) {
		
		if (x->sampling_points) {
			long i, old_size = sizeof(x->sampling_points)/sizeof(t_kaleido_sampling_pt);
            // free lllls before resizing
            for (i = old_size; i < x->num_sampling_points; i++)
                if (x->sampling_points[i].score)
                    llll_free(x->sampling_points[i].score);
			x->sampling_points = (t_kaleido_sampling_pt *)bach_resizeptrclear(x->sampling_points, args->l_size * sizeof(t_kaleido_sampling_pt));
			for (i = old_size; i < (long)args->l_size; i++) {
				x->sampling_points[i].pitch_mc = DADA_DEFAULT_PITCH;
				x->sampling_points[i].velocity = DADA_DEFAULT_VELOCITY;
			}
		} else {
			x->sampling_points = (t_kaleido_sampling_pt *)bach_newptrclear(args->l_size * sizeof(t_kaleido_sampling_pt));
			for (i = 0; i < (long)args->l_size; i++) {
				x->sampling_points[i].pitch_mc = DADA_DEFAULT_PITCH;
				x->sampling_points[i].velocity = DADA_DEFAULT_VELOCITY;
			}
		}
		
		for (elem = args->l_head; elem; elem = elem->l_next) {
			if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
                t_llll *ll = hatom_getllll(&elem->l_hatom);
                t_llllelem *elem;
                if (ll->l_head && hatom_gettype(&ll->l_head->l_hatom) == H_LLLL) {
                    x->sampling_points[x->num_sampling_points].r_it.coord = llll_to_pt(hatom_getllll(&ll->l_head->l_hatom));
                    elem = ll->l_head->l_next;
                    if (elem) {
                        if (x->sampling_metadata_type == DADA_KALEIDO_METADATA_PITCHNVEL) {
                            if (is_hatom_number(&elem->l_hatom))
                                x->sampling_points[x->num_sampling_points].pitch_mc = hatom_getdouble(&elem->l_hatom);
                            elem = elem->l_next;
                            if (elem && is_hatom_number(&elem->l_hatom))
                                x->sampling_points[x->num_sampling_points].velocity = hatom_getlong(&elem->l_hatom);
                        } else {
                            if (hatom_gettype(&elem->l_hatom) == H_SYM)
                                x->sampling_points[x->num_sampling_points].label = hatom_getsym(&elem->l_hatom);
                            t_llll *score = llll_clone(ll);
                            llll_behead(score);
                            llll_behead(score);
                            x->sampling_points[x->num_sampling_points].score = score;
                        }
                    }
                    x->num_sampling_points++;
                }
			}
		}
	}
	
	fold_all_sampling_points_in_main_chamber(x);
	
	
	jbox_invalidate_layer((t_object *)x, NULL, gensym("sampling_points"));
	if (x->show_sampling_points)
		jbox_redraw((t_jbox *)x);
}
				 
void kaleido_setsamplepitch(t_kaleido *x, t_llll *args)
{
	t_llllelem *elem;
	long i;
	
	for (i = 0, elem = args->l_head; elem && i < x->num_sampling_points; elem = elem->l_next, i++) 
		if (is_hatom_number(&elem->l_hatom))
			x->sampling_points[i].pitch_mc = hatom_getdouble(&elem->l_hatom);
	
}

				 
void kaleido_setsamplevelocity(t_kaleido *x, t_llll *args)
{
	t_llllelem *elem;
	long i;
	
	for (i = 0, elem = args->l_head; elem && i < x->num_sampling_points; elem = elem->l_next, i++) 
		if (is_hatom_number(&elem->l_hatom))
			x->sampling_points[i].velocity = CLAMP(hatom_getlong(&elem->l_hatom), DADA_MIN_VELOCITY, DADA_MAX_VELOCITY);
	
	jbox_invalidate_layer((t_object *)x, NULL, gensym("sampling_points"));
}
				 
void kaleido_sample(t_kaleido *x, t_llll *args)
{
	kaleido_setsample(x, args);
	kaleido_bang(x);
}

void kaleido_select_all(t_kaleido *x)
{
	long i;
	for (i = 0; i < x->num_shapes; i++)
		x->selected_shapes |= (1 << i);
	jbox_redraw((t_jbox *)x);
}

void kaleido_rotate(t_kaleido *x, t_llll *args)
{
	t_pt center = build_pt(0, 0);
	char center_is_user_specified = false;
	char center_is_wr_to_baricenter = false;
	double angle = 0;
	
	// custom origin for rotation
	if (args->l_size >= 3) {
		long type = hatom_gettype(&args->l_head->l_next->l_next->l_hatom);
		if (type == H_LLLL) {
			t_llll *pt_ll = hatom_getllll(&args->l_head->l_next->l_next->l_hatom);
			center = llll_to_pt(pt_ll);
			if (pt_ll->l_size >= 3 && hatom_gettype(&pt_ll->l_head->l_next->l_next->l_next->l_hatom) == H_SYM &&
				hatom_getsym(&args->l_head->l_next->l_next->l_next->l_hatom) == gensym("barycenter"))
				center_is_wr_to_baricenter = true;
		} else if (type == H_SYM && hatom_getsym(&args->l_head->l_next->l_next->l_hatom) == gensym("barycenter")) {
			center_is_wr_to_baricenter = true;
		}
		center_is_user_specified = true;
	}
	
	if (args->l_size >= 2) {
		// rotation angle
        angle = hatom_to_angle_in_rad(&args->l_head->l_next->l_hatom);
		
		// which shapes do we want to rotate?
		if (hatom_gettype(&args->l_head->l_hatom) != H_LONG)
			rotate_all_shapes(x, center, angle, center_is_wr_to_baricenter);
		else {
			long idx = hatom_getlong(&args->l_head->l_hatom);
			if (idx <= 0)
				rotate_all_shapes(x, center, angle, center_is_wr_to_baricenter);
			else if (idx > 0 && idx <= x->num_shapes)
				rotate_shape(x, &x->shapes[idx - 1], center, angle, center_is_wr_to_baricenter || !center_is_user_specified);
		}
	}
}
				 
void kaleido_move(t_kaleido *x, t_llll *args)
{
	t_pt vector = build_pt(0, 0);
	
	// vector for moving
	if (args->l_size >= 2 && hatom_gettype(&args->l_head->l_next->l_hatom) == H_LLLL)
		vector = llll_to_pt(hatom_getllll(&args->l_head->l_next->l_hatom));
	
	if (args->l_size >= 1) {
		// which shapes do we want to move?
		if (hatom_gettype(&args->l_head->l_hatom) != H_LONG)
			move_all_shapes(x, vector);
		else {
			long idx = hatom_getlong(&args->l_head->l_hatom);
			if (idx <= 0)
				move_all_shapes(x, vector);
			else if (idx > 0 && idx <= x->num_shapes)
				move_shape(x, &x->shapes[idx - 1], vector);
		}
	}
}


				 
void kaleido_scale(t_kaleido *x, t_llll *args)
{
	double factor_x = 1., factor_y = 1.;
	t_pt center = build_pt(0, 0);
	char center_is_user_specified = false;
	char center_is_wr_to_baricenter = false;
	
	// custom origin for scaling
	if (args->l_size >= 3) {
		long type = hatom_gettype(&args->l_head->l_next->l_next->l_hatom);
		if (type == H_LLLL) {
			t_llll *pt_ll = hatom_getllll(&args->l_head->l_next->l_next->l_hatom);
			center = llll_to_pt(pt_ll);
			if (pt_ll->l_size >= 3 && hatom_gettype(&pt_ll->l_head->l_next->l_next->l_next->l_hatom) == H_SYM &&
				hatom_getsym(&args->l_head->l_next->l_next->l_next->l_hatom) == gensym("barycenter"))
				center_is_wr_to_baricenter = true;
		} else if (type == H_SYM && hatom_getsym(&args->l_head->l_next->l_next->l_hatom) == gensym("barycenter")) {
			center_is_wr_to_baricenter = true;
		}
		center_is_user_specified = true;
	}
				
	// custom origin for rotation
	if (args->l_size >= 2) {
		if (hatom_gettype(&args->l_head->l_next->l_hatom) == H_LLLL) {
			t_llll *ll = hatom_getllll(&args->l_head->l_next->l_hatom);
			if (ll && ll->l_depth == 1 && ll->l_size >= 2) {
				if (is_hatom_number(&ll->l_head->l_hatom))
					factor_x = hatom_getdouble(&ll->l_head->l_hatom);
				if (is_hatom_number(&ll->l_head->l_next->l_hatom))
					factor_y = hatom_getdouble(&ll->l_head->l_next->l_hatom);
			}
		} else if (is_hatom_number(&args->l_head->l_next->l_hatom)) {
			factor_x = factor_y = hatom_getdouble(&args->l_head->l_next->l_hatom);
		}
	}
	
	if (args->l_size >= 1) {
		// which shapes do we want to scale?
		if (hatom_gettype(&args->l_head->l_hatom) != H_LONG)
			scale_all_shapes(x, center, factor_x, factor_y, center_is_wr_to_baricenter);
		else {
			long idx = hatom_getlong(&args->l_head->l_hatom);
			if (idx <= 0)
				scale_all_shapes(x, center, factor_x, factor_y, center_is_wr_to_baricenter);
			else if (idx > 0 && idx <= x->num_shapes)
				scale_shape(x, &x->shapes[idx - 1], center, factor_x, factor_y, center_is_wr_to_baricenter || !center_is_user_specified);
		}
	}
}



void kaleido_shake(t_kaleido *x, t_llll *args)
{
	double min_shift = 0, max_shift = x->mirror_size / 5.;
	double min_rot = 0, max_rot = deg2rad(10);

	
	// By default the region center is the barycenter of the main chamber, and the region radius is the mirror size 
	t_pt region_center;
	double region_radius = x->mirror_size;
	region_center.x = (x->main_corolla.vertex[0].x + x->main_corolla.vertex[1].x)/3.;
	region_center.y = (x->main_corolla.vertex[0].y + x->main_corolla.vertex[1].y)/3.;

	// custom min-max shift
	if (args->l_size >= 2) {
		long type = hatom_gettype(&args->l_head->l_next->l_hatom);
		if (type == H_LLLL) {
			t_llll *shift_ll = hatom_getllll(&args->l_head->l_next->l_hatom);
			if (shift_ll->l_size >= 2) {
				if (is_hatom_number(&shift_ll->l_head->l_hatom))
					min_shift = hatom_getdouble(&shift_ll->l_head->l_hatom);
				if (is_hatom_number(&shift_ll->l_head->l_next->l_hatom))
					max_shift = hatom_getdouble(&shift_ll->l_head->l_next->l_hatom);
			}
		} else if (type == H_LONG || type == H_RAT || type == H_DOUBLE) {
			max_shift = hatom_getdouble(&args->l_head->l_next->l_hatom);
		}
	}

	// custom min-max rotate
	if (args->l_size >= 3) {
		long type = hatom_gettype(&args->l_head->l_next->l_next->l_hatom);
		if (type == H_LLLL) {
			t_llll *rot_ll = hatom_getllll(&args->l_head->l_next->l_next->l_hatom);
			if (rot_ll->l_size >= 2) {
				if (is_hatom_number(&rot_ll->l_head->l_hatom))
					min_rot = hatom_getdouble(&rot_ll->l_head->l_hatom);
				if (is_hatom_number(&rot_ll->l_head->l_next->l_hatom))
					max_rot = hatom_getdouble(&rot_ll->l_head->l_next->l_hatom);
			}
		} else if (type == H_LONG || type == H_RAT || type == H_DOUBLE) {
			max_rot = hatom_getdouble(&args->l_head->l_next->l_next->l_hatom);
		}
	}

	// custom shake region
	if (args->l_size >= 4) {
		long type = hatom_gettype(&args->l_head->l_next->l_next->l_hatom);
		if (type == H_LLLL) {
			t_llll *subll = hatom_getllll(&args->l_head->l_next->l_next->l_hatom);
			if (subll->l_size >= 2) {
				if (hatom_gettype(&subll->l_head->l_hatom) == H_LLLL)
					region_center = llll_to_pt(hatom_getllll(&subll->l_head->l_hatom));
				if (is_hatom_number(&subll->l_head->l_next->l_hatom))
					region_radius = hatom_getdouble(&subll->l_head->l_next->l_hatom);
			}
		}
	}
	
	if (args->l_size >= 1) {
		// which shapes do we want to shake?
		if (hatom_gettype(&args->l_head->l_hatom) != H_LONG)
			shake_all_shapes(x, min_shift, max_shift, min_rot, max_rot, region_center, region_radius);
		else {
			long idx = hatom_getlong(&args->l_head->l_hatom);
			if (idx <= 0)
				shake_all_shapes(x, min_shift, max_shift, min_rot, max_rot, region_center, region_radius);
			else if (idx > 0 && idx <= x->num_shapes)
				shake_shape(x, &x->shapes[idx - 1], min_shift, max_shift, min_rot, max_rot, region_center, region_radius);
		}
	}
}





// mode == 0 -> standard
// mode == 1 -> selected shape
// mode == 2 -> mousehover shape
void paint_shape(t_kaleido *x, t_jgraphics *g, t_rect rect, t_pt center, t_kaleido_shape *shape, char mode)
{
    t_shape *sh = &shape->shape;
	double zoom = x->b_ob.d_ob.m_zoom.zoom.x;
	long j;
	t_jrgba color1, color2;
	t_jrgba white = build_jrgba(1, 1, 1, 0.75);
	
	if (mode != 0) {
		color1 = color2 = shape->shape.color;
		color1.alpha = (mode == 1 ? 0.5 : 0.15); //(kpoly->color.alpha + 1)/2.;
		color2.alpha = 1;
	}
	
	jgraphics_set_source_jrgba(g, mode != 0 ? &color1 : &sh->color);
	
	switch (sh->type) {
		case DADA_SHAPE_POLYGON:
			jgraphics_move_to(g, center.x + sh->shape.polygon.vertex[0].x * zoom, center.y - sh->shape.polygon.vertex[0].y * zoom);
			for (j = 1; j < sh->shape.polygon.num_vertices; j++) {
				jgraphics_line_to(g, center.x + sh->shape.polygon.vertex[j].x * zoom, center.y - sh->shape.polygon.vertex[j].y * zoom);
			}
			jgraphics_close_path(g); 
			break;
		case DADA_SHAPE_ELLIPSE:
		{
			t_pt center_pix = build_pt(center.x + sh->shape.ellipse.center.x * zoom, center.y - sh->shape.ellipse.center.y * zoom);
			jgraphics_translate(g, center_pix.x, center_pix.y);
			jgraphics_rotate(g, -sh->shape.ellipse.rotation);
//			jgraphics_ovalarc(g, center_pix.x, center_pix.y, shape->shape.ellipse.radius_x, shape->shape.ellipse.radius_y, 0., 6.29);
			jgraphics_ovalarc(g, 0, 0, sh->shape.ellipse.radius.x * zoom, sh->shape.ellipse.radius.y * zoom, 0., 6.29);
			jgraphics_rotate(g, +sh->shape.ellipse.rotation);
			jgraphics_translate(g, -center_pix.x, -center_pix.y);
//			jgraphics_translate(g, 0, 0);
//			jgraphics_rotate(g, 0);
		}
			break;
		default:
			break;
	}
	
	if (mode == 1) {
		// SELECTION
		jgraphics_fill_preserve(g);
		jgraphics_set_line_width(g, 3);
		jgraphics_set_source_jrgba(g, &color2);
		jgraphics_stroke(g);
		
		switch (sh->type) {
			case DADA_SHAPE_POLYGON:
				for (j = 0; j < sh->shape.polygon.num_vertices; j++) {
					paint_circle(g, white, white, center.x + sh->shape.polygon.vertex[j].x * zoom, center.y - sh->shape.polygon.vertex[j].y * zoom, 5, 0);
					paint_circle(g, color2, color2, center.x + sh->shape.polygon.vertex[j].x * zoom, center.y - sh->shape.polygon.vertex[j].y * zoom, 3, 0);
				}
				break;
			case DADA_SHAPE_ELLIPSE:
			{
				t_pt point1 = get_ellipse_radiuspoint_coord(&sh->shape.ellipse, 0);
				t_pt point2 = get_ellipse_radiuspoint_coord(&sh->shape.ellipse, 1);
				paint_circle(g, white, white, center.x + point1.x * zoom, center.y - point1.y * zoom, 5, 0);
				paint_circle(g, white, white, center.x + point2.x * zoom, center.y - point2.y * zoom, 5, 0);
				paint_circle(g, white, white, center.x + sh->shape.ellipse.center.x * zoom, center.y - sh->shape.ellipse.center.y * zoom, 5, 0);
				paint_circle(g, color2, color2, center.x + point1.x * zoom, center.y - point1.y * zoom, 3, 0);
				paint_circle(g, color2, color2, center.x + point2.x * zoom, center.y - point2.y * zoom, 3, 0);
				paint_circle(g, color2, color2, center.x + sh->shape.ellipse.center.x * zoom, center.y - sh->shape.ellipse.center.y * zoom, 3, 0);
			}
				break;
			default:
				break;
		}
		
	} else if (mode == 2) {
		// MOUSE HOVERING
		long main_idx = x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx;
		long secondary_idx = x->b_ob.d_ob.m_interface.mousemove_item_identifier.secondary_idx;
		switch (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type) {
			case DADA_KALEIDO_ELEMENT_SHAPE:
				jgraphics_fill_preserve(g);
				jgraphics_set_line_width(g, 2);
				jgraphics_set_source_jrgba(g, &color2);
				jgraphics_stroke(g);
				break;
			case DADA_KALEIDO_ELEMENT_VERTEX:
				jgraphics_fill(g);
				if (main_idx >= 0 && main_idx < x->num_shapes && x->shapes[main_idx].shape.type == DADA_SHAPE_POLYGON) {
					if (secondary_idx >= 0 && secondary_idx < x->shapes[main_idx].shape.shape.polygon.num_vertices) {
						t_pt vertex_pt = x->shapes[main_idx].shape.shape.polygon.vertex[secondary_idx];
						paint_circle(g, color2, color2, center.x + vertex_pt.x * zoom, center.y - vertex_pt.y * zoom, 3, 0);
						paint_circle_stroken(g, color2, center.x + vertex_pt.x * zoom, center.y - vertex_pt.y * zoom, DADA_KALEIDO_VERTEX_SELECTION_RADIUS, 1);
					}
				}
				break;
			case DADA_KALEIDO_ELEMENT_EDGE:
				jgraphics_fill(g);
				if (main_idx >= 0 && main_idx < x->num_shapes && x->shapes[main_idx].shape.type == DADA_SHAPE_POLYGON) {
					if (secondary_idx >= 0 && secondary_idx < x->shapes[main_idx].shape.shape.polygon.num_vertices) {
						t_pt vertex_pt1 = x->shapes[main_idx].shape.shape.polygon.vertex[secondary_idx];
						t_pt vertex_pt2 = x->shapes[main_idx].shape.shape.polygon.vertex[(secondary_idx + 1) % x->shapes[main_idx].shape.shape.polygon.num_vertices];
						paint_circle(g, color2, color2, center.x + vertex_pt1.x * zoom, center.y - vertex_pt1.y * zoom, 3, 0);
						paint_circle(g, color2, color2, center.x + vertex_pt2.x * zoom, center.y - vertex_pt2.y * zoom, 3, 0);
						paint_line(g, color2, vertex_pt1.x, vertex_pt1.y, vertex_pt2.x, vertex_pt2.y, 2.5);
					}
				}
				break;
			case DADA_KALEIDO_ELEMENT_CENTER:
				jgraphics_fill(g);
				if (main_idx >= 0 && main_idx < x->num_shapes && x->shapes[main_idx].shape.type == DADA_SHAPE_ELLIPSE) {
					t_pt center_pt = x->shapes[main_idx].shape.shape.ellipse.center;
					paint_circle(g, color2, color2, center.x + center_pt.x * zoom, center.y - center_pt.y * zoom, 3, 0);
					paint_circle_stroken(g, color2, center.x + center_pt.x * zoom, center.y - center_pt.y * zoom, DADA_KALEIDO_VERTEX_SELECTION_RADIUS, 1);
				}
				break;
			case DADA_KALEIDO_ELEMENT_RADIUSPOINT:
				jgraphics_fill(g);
				if (main_idx >= 0 && main_idx < x->num_shapes && x->shapes[main_idx].shape.type == DADA_SHAPE_ELLIPSE) {
					if (secondary_idx >= 0 && secondary_idx < 2) {
						t_pt point = get_ellipse_radiuspoint_coord(&x->shapes[main_idx].shape.shape.ellipse, secondary_idx);
						paint_circle(g, color2, color2, center.x + point.x * zoom, center.y - point.y * zoom, 3, 0);
						paint_circle_stroken(g, color2, center.x + point.x * zoom, center.y - point.y * zoom, DADA_KALEIDO_VERTEX_SELECTION_RADIUS, 1);
					}
				}
				break;
			default:
				break;
		}
		
	} else {
		// NOTHING MORE THAN PAINT
		jgraphics_fill(g);
	}
    
    if (mode == 0) {
        // muted/inactive/solo?
        if (shape->r_it.flags & D_SOLO) {
            t_shape sh_extr;
            clone_shape(sh, &sh_extr);
            shape_offset(&sh_extr, 10);
            dadaobj_paint_shape_dotted(dadaobj_cast(x), &sh_extr, center, g, &sh->color, 10, 1);
        }
        if (!kaleido_shape_should_be_played(x, shape)) {
            t_pt bc;
            double radius = get_shape_barycentric_innermost_radius(sh, &bc);
            paint_cross(g, &sh->color, coord_to_pix(dadaobj_cast(x), center, bc), radius - 4, 1);
        }
        if (shape->r_it.flags & D_INACTIVE) {
            t_shape sh_extr;
            t_jrgba color = DADA_COLOR_INACTIVE;
            clone_shape(sh, &sh_extr);
            shape_offset(&sh_extr, 10);
            dadaobj_paint_shape(dadaobj_cast(x), &sh_extr, center, g, NULL, &color, 0);
        }
    }
}

void build_studio(t_kaleido *x, t_rect rect, t_pt center, t_jgraphics *g)
{
	// building the "studio" (the environment with mirrors and polygons)
	// and the "chamber" (a copy of the part inside the mirrors only, and its mirrored image w.r. to the X axis)

	double zoom = x->b_ob.d_ob.m_zoom.zoom.x;
	long i, j;
	long chamber_size = ceil(x->mirror_size * zoom);

	if (x->s_studio)
		jgraphics_surface_destroy(x->s_studio);
	x->s_studio = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, rect.width, rect.height);
	
	if (x->s_chamber) 
		jgraphics_surface_destroy(x->s_chamber);
	x->s_chamber = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, chamber_size, 2 * chamber_size);

	t_jgraphics *g_studio = jgraphics_create(x->s_studio);
	t_jgraphics *g_chamber = jgraphics_create(x->s_chamber);
	
	jgraphics_set_line_width(g_studio, 0);

	for (i = 0; i < x->num_shapes; i++) 
		paint_shape(x, g_studio, rect, center, &x->shapes[i], 0);
	
	jgraphics_image_surface_draw(g_chamber, x->s_studio, build_rect(center.x, center.y - chamber_size, chamber_size, chamber_size), build_rect(0, 0, chamber_size, chamber_size));

	for (i = 0; i < chamber_size; i++)
		for (j = 0; j < chamber_size; j++) {
			t_jrgba	this_color;
			jgraphics_image_surface_get_pixel(x->s_chamber, i, j, &this_color);
			jgraphics_image_surface_set_pixel(x->s_chamber, i, 2 * chamber_size - j - 1, this_color); // reflecting pixels down for mirrored image
		}
	
	jgraphics_destroy(g_chamber);
	jgraphics_destroy(g_studio);
    
}

void build_tile(t_kaleido *x, t_rect rect, t_pt center)
{

	double zoom = x->b_ob.d_ob.m_zoom.zoom.x;
	long i;
	long chamber_size = ceil(x->mirror_size * zoom);
	t_jrgba chamber_border = x->j_chambercolor;

	if (x->s_tile)
		jgraphics_surface_destroy(x->s_tile);
	x->s_tile = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, 2 * chamber_size, 2 * chamber_size);
	

	// CREATING PATTERNS, one for each virtual chamber
	
	// allocating memory for patterns
	t_jpattern **pat = (t_jpattern **)bach_newptr(x->num_steps * sizeof(t_jpattern *));
	double step_radians = TWO_PI / x->num_steps;
	for (i = 0; i < x->num_steps; i++) { // order of corollas
		double a = step_radians * i; // current angle
		t_jmatrix mat;
		
		// a = 0;					//x->temp * i; 
		
		//			pat[i] = quick_pattern_from_file("align.png"); 
		pat[i] = jgraphics_pattern_create_for_surface(x->s_chamber);
		
		// rotating the pattern
		jgraphics_matrix_init_rotate(&mat, a);
		
		// reshifting the (left) origin of the mirrors to the middle point in the object canvas
		double sin_a = sin(a);
		double cos_a = cos(a);
		jgraphics_matrix_translate(&mat, 0, chamber_size);
		
		jgraphics_matrix_translate(&mat, -chamber_size * cos_a, -chamber_size * sin_a);
		jgraphics_matrix_translate(&mat, chamber_size * sin_a, -chamber_size * cos_a);
		//			jgraphics_matrix_translate(&mat, -center.x * cos_a, -center.x * sin_a);
		//			jgraphics_matrix_translate(&mat, center.y * sin_a, -center.y * cos_a);
		
		jgraphics_pattern_set_matrix(pat[i], &mat); 
	}
	
	
	t_jgraphics *g_tile = jgraphics_create(x->s_tile);
	
	// we paint each shape
	t_jmatrix matrix;
	jgraphics_matrix_init_identity(&matrix);
	
	t_pt init_c1, init_c2, init_c3, init_c4; // coordinates of the camera rhomboid
	t_pt c1, c2, c3, c4;					 // coordinates of the generic rhomboid
	t_pt p1, p2, p3, p4;					 // corresponding pixels
	
	t_rect source_rect = build_rect(0, 0, chamber_size, 2 * chamber_size);
	t_rect dest_rect = build_rect(center.x, center.y - chamber_size, chamber_size, 2 * chamber_size);
	
	c1 = build_pt(0, 0);
	c2 = build_pt(x->mirror_size * cos(3.1415926536 / x->num_steps), x->mirror_size * sin(3.1415926536 / x->num_steps));
	c3 = build_pt(x->mirror_size, 0);
	c4 = build_pt(c2.x, -c2.y);
	
	init_c1 = c1;
	init_c2 = c2;
	init_c3 = c3;
	init_c4 = c4;
	
	for (i = 0; i < x->num_steps; i++) { 
		
		c1 = init_c1;
		c2 = init_c2;
		c3 = init_c3;
		c4 = init_c4;
		
		jgraphics_matrix_init_rotate(&matrix, i * step_radians);
		
		jgraphics_matrix_transform_point(&matrix, &c1.x, &c1.y);
		jgraphics_matrix_transform_point(&matrix, &c2.x, &c2.y);
		jgraphics_matrix_transform_point(&matrix, &c3.x, &c3.y);
		jgraphics_matrix_transform_point(&matrix, &c4.x, &c4.y);
		
		t_pt this_center = build_pt(chamber_size, chamber_size);
		p1 = coord_to_pix(dadaobj_cast(x), this_center, c1);
		p2 = coord_to_pix(dadaobj_cast(x), this_center, c2);
		p3 = coord_to_pix(dadaobj_cast(x), this_center, c3);
		p4 = coord_to_pix(dadaobj_cast(x), this_center, c4);
		
		jgraphics_move_to(g_tile, p1.x, p1.y);
		jgraphics_line_to(g_tile, p2.x, p2.y);
		jgraphics_line_to(g_tile, p3.x, p3.y);
		jgraphics_line_to(g_tile, p4.x, p4.y);
		jgraphics_close_path(g_tile); 
		
		jgraphics_set_source (g_tile, pat[i]);
		
		if (x->show_chambers) {
			jgraphics_fill_preserve(g_tile);
			jgraphics_set_line_width(g_tile, x->chamber_border_size);
			jgraphics_set_source_jrgba(g_tile, &chamber_border);
			jgraphics_stroke(g_tile);
			paint_line(g_tile, chamber_border, p1.x, p1.y, p3.x, p3.y, 1);
		} else 
			jgraphics_fill(g_tile);
	}
	
	
	for (i = 0; i < x->num_steps; i++)
		jgraphics_pattern_destroy(pat[i]);
	bach_freeptr(pat);
	
	fold_all_sampling_points_in_main_chamber(x);
	
	jgraphics_destroy(g_tile);
}


void paint_static_layer1(t_kaleido *x, t_object *view, t_rect rect){
	
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("static_layer1"), rect.width, rect.height);
	
	if (g){
		
		
		t_fourcc outtype;
		t_fourcc filetype = 'PNG';
		char filename[MAX_PATH_CHARS];
		short path;
		strcpy(filename, "align.png");    // must copy symbol before calling locatefile_extended
		
		if (locatefile_extended(filename, &path, &outtype, &filetype, 1)) {
			t_jsurface *lena = jgraphics_image_surface_create_from_file(filename, path);
//			double height = jgraphics_image_surface_get_height(lena);
//			double width = jgraphics_image_surface_get_width(lena);
			
//			jgraphics_rotate(g, x->temp); // pi/2
//			jgraphics_image_surface_draw(g, lena, build_rect(0, 0, width, height), build_rect(0, 0, rect.width, rect.height));
			
						
			t_jpattern *pattern = jgraphics_pattern_create_for_surface(lena);
/*			t_jrgba bgcolor = build_jrgba(1, 0, 0, 1);
			t_jrgba gradientcolor = build_jrgba(0, 1, 0, 1);
			pattern = jgraphics_pattern_create_radial(rect.width/2, rect.height/2, 0.0,
													  rect.width,   rect.height/2, 0.0);
			jgraphics_pattern_add_color_stop_rgba(pattern, 0.0,
												  bgcolor.red,
												  bgcolor.green,
												  bgcolor.blue,
												  bgcolor.alpha);
			jgraphics_pattern_add_color_stop_rgba(pattern, 0.7,
												  bgcolor.red,
												  bgcolor.green,
												  bgcolor.blue,
												  bgcolor.alpha);
			jgraphics_pattern_add_color_stop_rgba(pattern, 0.8,
												  gradientcolor.red,
												  gradientcolor.green,
												  gradientcolor.blue,
												  gradientcolor.alpha);
			jgraphics_pattern_add_color_stop_rgba(pattern, 0.9,
												  bgcolor.red,
												  bgcolor.green,
												  bgcolor.blue,
												  bgcolor.alpha);
			jgraphics_pattern_add_color_stop_rgba(pattern, 1.0,
												  bgcolor.red,
												  bgcolor.green,
												  bgcolor.blue,
												  bgcolor.alpha);*/
			
			t_jmatrix matrix;
			jgraphics_matrix_init_rotate(&matrix, 0.2);
			jgraphics_pattern_set_matrix(pattern, &matrix);
			
			jgraphics_rectangle (g, 0, 0, rect.width, rect.height);
			jgraphics_set_source (g, pattern);
			jgraphics_fill (g);

		
			jgraphics_surface_destroy(lena);
			jgraphics_pattern_destroy(pattern);
		}
		
		jbox_end_layer((t_object *)x, view, gensym("static_layer1"));
	}
	
	jbox_paint_layer((t_object *)x, view, gensym("static_layer1"), 0., 0.);	// position of the layer


	/*	t_jgraphics *context;
	 t_jpattern *pattern;
	 t_rect rect;
	 
	 context = (t_jgraphics *)patcherview_get_jgraphics(view);
	 jbox_get_rect_for_view((t_object *)x, view, &rect);
	 t_jrgba bgcolor = build_jrgba(1, 0, 0, 1);
	 t_jrgba gradientcolor = build_jrgba(0, 1, 0, 1);
	 // draw gradient
	 pattern = jgraphics_pattern_create_radial(rect.width/2, rect.height/2, 0.0,
	 rect.width,   rect.height/2, 0.0);
	 jgraphics_pattern_add_color_stop_rgba(pattern, 0.0,
	 bgcolor.red,
	 bgcolor.green,
	 bgcolor.blue,
	 bgcolor.alpha);
	 jgraphics_pattern_add_color_stop_rgba(pattern, 0.7,
	 bgcolor.red,
	 bgcolor.green,
	 bgcolor.blue,
	 bgcolor.alpha);
	 jgraphics_pattern_add_color_stop_rgba(pattern, 0.8,
	 gradientcolor.red,
	 gradientcolor.green,
	 gradientcolor.blue,
	 gradientcolor.alpha);
	 jgraphics_pattern_add_color_stop_rgba(pattern, 0.9,
	 bgcolor.red,
	 bgcolor.green,
	 bgcolor.blue,
	 bgcolor.alpha);
	 jgraphics_pattern_add_color_stop_rgba(pattern, 1.0,
	 bgcolor.red,
	 bgcolor.green,
	 bgcolor.blue,
	 bgcolor.alpha);
	 jgraphics_set_source(context, pattern);
	 jgraphics_pattern_destroy(pattern);
	 jgraphics_paint(context);
	 
	 return; */
}



// fills chamber_idx with the index of the virtual chamber (0-based, -1 if none) and (if not NULL) fills shape_hit_test
// with the hit test for each one of the shapes in the chamber.
// Returns 1 if point is inside a chamber, 0 therwise 
char coord_to_chamber(t_kaleido *x, t_pt coord, long *chamber_idx, t_kaleido_bitfield *shape_hit, long *first_hit, t_pt *folded_coord)
{
	double cx = coord.x, cy = coord.y;
	double step_radians = TWO_PI/(2 * x->num_steps);
	long res = -1, i;
	double mirror_size = x->mirror_size;
	
	if (shape_hit)
		*shape_hit = 0;
	
	if (x->extend_when_possible) {
	// folding the coordinates to reach the equivalent point inside the "main" chamber
		if (x->num_steps == 2) {
			while (cy > cx + mirror_size){
				cx = cx + mirror_size;
				cy = cy - mirror_size;
			}
			while (cy < cx - mirror_size){
				cx = cx - mirror_size;
				cy = cy + mirror_size;
			}
			while (cy > - cx + mirror_size){
				cx = cx - mirror_size;
				cy = cy - mirror_size;
			}
			while (cy < - cx - mirror_size){
				cx = cx + mirror_size;
				cy = cy + mirror_size;
			}
			
		} else if (x->num_steps == 3) {
			// (cx, cy) is inside an hexagon. Let's try to find the cubic coordinates of such hexagon.
			// See http://www.redblobgames.com/grids/hexagons/, section "Pixel to Hex"
			double cubic_x = cx / (mirror_size * 3./2.);
			double cubic_y = (sqrt(3) * cy - cx) / (3 * mirror_size);			
			double cubic_z = - cubic_x - cubic_y;

			round_cubic_coordinates_for_hex_grid(&cubic_x, &cubic_y, &cubic_z); 
			// now cubic_x, cubic_y and cubic_z are the cube coordinate of our flat-topped hex grid
			
			// so we need to reshift the original coordinates "down" to the (0, 0, 0) hexagon, by using the
			// rounded cubic coordiantes.
			cx -= cubic_x * (mirror_size * 3./2.);
			cy -= cubic_x * (mirror_size * sqrt(3.)/2.) + cubic_y * (mirror_size * sqrt(3.));
		}
	}

	if (is_pt_in_dadapolygon(build_pt(cx, cy), &x->main_corolla)) {
		double angle = atan2(cy, cx);
		if (angle < 0)
			angle += TWO_PI;
		res = floor(angle/step_radians); 
		
		// find shape hit and folded coordinates (coordinates reconducted inside the main chamber)
		if (shape_hit || folded_coord) {
			char found_first_hit = false;
			if (res >= 0) {
				t_jmatrix mat;
				jgraphics_matrix_init_rotate(&mat, -(((res + 1) % (2 * x->num_steps))/2) * step_radians * 2); // integer division by 2 is on purpose
				jgraphics_matrix_transform_point(&mat, &cx, &cy);
				if (res % 2)
					cy = -cy;
				
				if (folded_coord)
					*folded_coord = build_pt(cx, cy);
				
				if (shape_hit) {
					t_kaleido_bitfield test;
					for (i = 0, test = 1; i < x->num_shapes; i++, test = test << 1) {
						if (is_pt_in_shape(build_pt(cx, cy), &x->shapes[i].shape)) {
							*shape_hit |= test; 
							if (first_hit && !found_first_hit) {
								*first_hit = i;
								found_first_hit = true;
							}
						}
					}
				}
			}
		}
	}
	
	*chamber_idx = res;
	
	return (res >= 0 ? true : false);
}




char pixel_to_chamber(t_kaleido *x, t_pt pt, t_object *view, long *chamber_idx, t_kaleido_bitfield *shape_hit, long *first_hit){
	t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), view, pt);
	return coord_to_chamber(x, coord, chamber_idx, shape_hit, first_hit, NULL);
}


long coord_hit_test_edit_chamber(t_kaleido *x, t_pt coord, t_kaleido_bitfield *shape_hit, long max_hits){
	long i, num_hits = 0, first_hit = -1;
	t_kaleido_bitfield test;

	if (max_hits == 0)
		max_hits = x->num_shapes;
	
	*shape_hit = 0;
	for (i = 0, test = 1; i < x->num_shapes && num_hits < max_hits; i++, test = test << 1) {
		if (is_pt_in_shape(coord, &x->shapes[i].shape)) {
			num_hits++;
			*shape_hit |= test;
			if (first_hit < 0)
				first_hit = i;
		} 
	}
	
	return first_hit;
}
	
					 
					 
// find the shape under a given pixel in the edit chamber, fills the shape_hit array, returns the first hit
long pixel_hit_test_edit_chamber(t_kaleido *x, t_pt pt, t_object *view, t_kaleido_bitfield *shape_hit, long max_hits)
{
	t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), view, pt);
	
	return coord_hit_test_edit_chamber(x, coord, shape_hit, max_hits);
}

// returns just the first match
long pixel_to_shape(t_kaleido *x, t_pt pt, t_object *view)
{
	t_kaleido_bitfield shape_hit = 0;
	if (x->edit_mode)
		return pixel_hit_test_edit_chamber(x, pt, view, &shape_hit, 1);
	else {
		long idx = -1, first_hit = -1;
		pixel_to_chamber(x, pt, view, &idx, &shape_hit, &first_hit);
		return first_hit;
	}
}

t_dadaitem_identifier coord_to_element_edit_chamber(t_kaleido *x, t_pt coord)
{
	long i, j;
	t_dadaitem_identifier result;
	result.type = DADA_KALEIDO_ELEMENT_NONE;
	result.flag = 0;
	
	// Are we on a polygon vertex, or on an ellipse radiuspoint?
	for (i = 0; i < x->num_shapes; i++) {
		switch (x->shapes[i].shape.type) {
			case DADA_SHAPE_POLYGON:
				for (j = 0; j < x->shapes[i].shape.shape.polygon.num_vertices; j++) {
					if (pt_pt_distance(coord, x->shapes[i].shape.shape.polygon.vertex[j]) <= DADA_KALEIDO_VERTEX_SELECTION_RADIUS) {
						result.type = DADA_KALEIDO_ELEMENT_VERTEX;
						result.idx = i;
						result.secondary_idx = j;
						return result;
					}
				}
				break;
			case DADA_SHAPE_ELLIPSE:
			{
				t_pt radpt1 = get_ellipse_radiuspoint_coord(&x->shapes[i].shape.shape.ellipse, 0);
				t_pt radpt2 = get_ellipse_radiuspoint_coord(&x->shapes[i].shape.shape.ellipse, 1);
				if (pt_pt_distance(coord, radpt1) <= DADA_KALEIDO_VERTEX_SELECTION_RADIUS) {
					result.type = DADA_KALEIDO_ELEMENT_RADIUSPOINT;
					result.idx = i;
					result.secondary_idx = 0;
					return result;
				} else if (pt_pt_distance(coord, radpt2) <= DADA_KALEIDO_VERTEX_SELECTION_RADIUS) {
					result.type = DADA_KALEIDO_ELEMENT_RADIUSPOINT;
					result.idx = i;
					result.secondary_idx = 1;
					return result;
				}
				break;
			}
			default:
				break;
		}
	}
	
	
	// Are we on a shape???
	t_kaleido_bitfield shape_hit = 0;
	long first_hit = coord_hit_test_edit_chamber(x, coord, &shape_hit, 0);
	if (first_hit > -1) {
		result.type = DADA_KALEIDO_ELEMENT_SHAPE;
		result.idx = first_hit;
	}

	return result;
}

t_dadaitem_identifier pixel_to_element_edit_chamber(t_kaleido *x, t_pt pt, t_object *view, t_pt *coordinates)
{
	t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), view, pt);
	if (coordinates)
		*coordinates = coord;
	return coord_to_element_edit_chamber(x, coord);
}

long coordinate_to_sampling_point(t_kaleido *x, t_pt coord)
{
	long i;
	for (i = 0; i < x->num_sampling_points; i++)
		if (pt_pt_distance(x->sampling_points[i].r_it.coord, coord) <= x->sampling_points_size + DADA_KALEIDO_SAMPLINGPOINT_SELECTION_PAD)
			return i;
	return -1;
}

long pixel_to_sampling_point(t_kaleido *x, t_pt pt, t_object *view, t_pt *coordinates)
{
	t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), view, pt);
	if (coordinates)
		*coordinates = coord;
	return coordinate_to_sampling_point(x, coord);
}

t_dadaitem_identifier pixel_to_element(t_kaleido *x, t_pt pt, t_object *view, t_pt *coordinates)
{
	t_kaleido_bitfield shape_hit = 0;
	t_dadaitem_identifier result;
	result.type = DADA_KALEIDO_ELEMENT_NONE;
	result.flag = 0;
    result.idx = result.secondary_idx = result.tertiary_idx = -1;
	
	if (x->edit_mode)
		result = pixel_to_element_edit_chamber(x, pt, view, coordinates);
	else {
		long sampling_pt = pixel_to_sampling_point(x, pt, view, coordinates);
		if (sampling_pt >= 0) {
			result.type = DADA_KALEIDO_ELEMENT_SAMPLINGPOINT;
			result.idx = sampling_pt;
		} else {
			long idx = -1, first_hit = -1;
			pixel_to_chamber(x, pt, view, &idx, &shape_hit, &first_hit);
			if (first_hit >= 0) {
				result.type = DADA_KALEIDO_ELEMENT_SHAPE;
				result.idx = first_hit;
			}
		}
	}
	
	return result;
}
	

void fold_sampling_point_in_main_chamber(t_kaleido *x, long idx)
{
	long chamber_idx;
	x->sampling_points[idx].is_in_main_corolla = coord_to_chamber(x, x->sampling_points[idx].r_it.coord, &chamber_idx, NULL, NULL, &x->sampling_points[idx].coord_folded);
}

void fold_all_sampling_points_in_main_chamber(t_kaleido *x)
{
	long i;
	for (i = 0; i < x->num_sampling_points; i++) 
		fold_sampling_point_in_main_chamber(x, i);
}

// obtain the sampled information about shape hits and colors
void get_sampling_info(t_kaleido *x, t_llll **hits, t_llll **colors)
{
	long i, j;
	t_kaleido_bitfield test;
	
	if (hits && !*hits)
		*hits = llll_get();
	
	if (colors && !*colors)
		*colors = llll_get();
	
	for (i = 0; i < x->num_sampling_points; i++) {
		t_kaleido_bitfield shape_hit = 0;
		
		if (x->sampling_points[i].is_in_main_corolla) {
			coord_hit_test_edit_chamber(x, x->sampling_points[i].coord_folded, &shape_hit, 0);
			
			if (hits) {
				t_llll *this_hits = llll_get();
				for (j = 0, test = 1; j < x->num_shapes; j++, test = test << 1)
					if (shape_hit & test)
						llll_appendlong(this_hits, j + 1, 0, WHITENULL_llll); // 1-based outside, as always!
				llll_appendllll(*hits, this_hits, 0, WHITENULL_llll);
			}
			
			if (colors) {
				t_jrgba color = build_jrgba(0, 0, 0, 0);
				t_llll *this_color = llll_get();
				for (j = 0, test = 1; j < x->num_shapes; j++, test = test << 1)
					if (shape_hit & test)
						color = color_alphablend(color, x->shapes[j].shape.color);
				llll_appenddouble(this_color, color.red, 0, WHITENULL_llll);
				llll_appenddouble(this_color, color.green, 0, WHITENULL_llll);
				llll_appenddouble(this_color, color.blue, 0, WHITENULL_llll);
				llll_appenddouble(this_color, color.alpha, 0, WHITENULL_llll);
				llll_appendllll(*colors, this_color, 0, WHITENULL_llll);
			}
			
		} else {
			if (hits) 
				llll_appendllll(*hits, llll_get(), 0, WHITENULL_llll);
			if (colors) {
				t_llll *this_color = llll_get();
				llll_appenddouble(this_color, 0, 0, WHITENULL_llll);
				llll_appenddouble(this_color, 0, 0, WHITENULL_llll);
				llll_appenddouble(this_color, 0, 0, WHITENULL_llll);
				llll_appenddouble(this_color, 0, 0, WHITENULL_llll);
				llll_appendllll(*colors, this_color, 0, WHITENULL_llll);
			}
		}
	}
}


//// GRAPHIC DRAWING

char kaleido_sampling_point_should_be_played(t_kaleido *x, long idx)
{
    if (idx < 0 || idx >= x->num_sampling_points)
        return false;
    
    t_dadaitem *item = &x->sampling_points[idx].r_it;
    return ((!(item->flags & D_MUTE) && (((item->flags & D_SOLO) > 0) || (!x->has_solo_samplingpoints))) ? true : false);
//    return ((((item->flags & D_SOLO) > 0) || (!x->has_solo_samplingpoints && !(item->flags & D_MUTE))) ? true : false);
}

char kaleido_shape_should_be_played_from_idx(t_kaleido *x, long idx)
{
    if (idx < 0 || idx >= x->num_shapes)
        return false;
    
    t_dadaitem *item = &x->shapes[idx].r_it;
    return ((!(item->flags & D_MUTE) && (((item->flags & D_SOLO) > 0) || (!x->has_solo_shapes))) ? true : false);
    //    return ((((item->flags & D_SOLO) > 0) || (!x->has_solo_samplingpoints && !(item->flags & D_MUTE))) ? true : false);
}

char kaleido_shape_should_be_played(t_kaleido *x, t_kaleido_shape *shape)
{
    t_dadaitem *item = &shape->r_it;
    return ((!(item->flags & D_MUTE) && (((item->flags & D_SOLO) > 0) || (!x->has_solo_shapes))) ? true : false);
}

void kaleido_paint_sampling_points(t_kaleido *x, t_object *view, t_rect rect, t_pt center, double zoom, t_dada_force_graphics *force_graphics)
{
	
    t_jgraphics *g = view ? jbox_start_layer((t_object *)x, view, gensym("sampling_points"), rect.width, rect.height) : force_graphics->graphic_context;
	
	if (g){
        
        long i;
        t_jrgba white = get_grey(1);
        white.alpha = x->j_samplingcolor.alpha;
        
        for (i = 0; i < x->num_sampling_points; i++){
            t_pt p;
            t_jrgba color;
            double size;
            
            if (x->sampling_metadata_type == DADA_KALEIDO_METADATA_PITCHNVEL) {
                double temp = ((double)x->sampling_points[i].velocity - 1)/(DADA_MAX_VELOCITY - 1);
                size = (x->velocity_handling == 3) ? x->sampling_points_size * (temp * 0.6 + 0.4) : x->sampling_points_size;
                
                switch (x->velocity_handling) {
                    case 1:
                        color = color_interp(white, x->j_samplingcolor, temp * 0.8 + 0.2);
                        break;
                    case 2:
                        color = double_to_color(temp, 0., 1., false);
                        break;
                    default:
                        color = x->j_samplingcolor;
                        break;
                }
            } else {
                size = x->sampling_points_size;
                color = x->j_samplingcolor;
            }
            
			p = coord_to_pix(dadaobj_cast(x), center, x->sampling_points[i].r_it.coord);
			
            paint_circle(g, white, color, p.x, p.y, size, 1.);

            if (x->sampling_points[i].r_it.flags & D_SOLO)
                paint_pointed_corolla(g, &color, p, size * 1.4, 8, 1);
            
            if (!kaleido_sampling_point_should_be_played(x, i))
				paint_cross(g, &color, p, size * 1.4, 1.);
		}
 
        if (view)
            jbox_end_layer((t_object *)x, view, gensym("sampling_points"));
	}
	
    if (view)
	jbox_paint_layer((t_object *)x, view, gensym("sampling_points"), 0., 0.);	// position of the layer
}


void paint_sampling_point_note(t_kaleido *x, t_jgraphics *g, t_kaleido_sampling_pt *spt, t_rect noterect)
{
	t_jrgba staffcolor = build_jrgba(0.2, 0.2, 0.2, 1);
	t_jrgba bordercolor = build_jrgba(0.2, 0.2, 0.2, 1);
	t_jrgba bgcolor = build_jrgba(1, 1, 1, 0.9);
	
	paint_rectangle_rounded(g, bordercolor, bgcolor, noterect.x, noterect.y, noterect.width, noterect.height, 1, DADA_DEFAULT_RECT_ROUNDNESS, DADA_DEFAULT_RECT_ROUNDNESS);
	
	ezpaint_note_with_staff((t_object *)x, g, spt->pitch_mc, k_ACC_AUTO, x->tonedivision, build_pt(noterect.x + 3, noterect.y + 25), 
							noterect.width - 6, 24, noterect.x + 31, false, &staffcolor, &staffcolor, &staffcolor);

	jgraphics_set_source_rgba(g, 0, 0, 0, 1);
}

void paint_score_label(t_kaleido *x, t_jgraphics *g, t_pt pt, t_symbol *symbol)
{
    char label[1024];
    snprintf(label, 1024, "%s", symbol ? symbol->s_name : "score");
    t_jfont *jf = jfont_create("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, 11);
    write_text(g, jf, DADA_BLACK, label, pt.x + 5, pt.y + 5, 300, 300, JGRAPHICS_TEXT_JUSTIFICATION_LEFT | JGRAPHICS_TEXT_JUSTIFICATION_TOP, 1, 0);
    jfont_destroy(jf);
}

void repaint_hovered_and_selected_items(t_kaleido *x, t_jgraphics *g, t_rect rect, t_pt center)
{
	// re-paint selected and hovered elements
	switch (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type) {
		case DADA_KALEIDO_ELEMENT_SHAPE:
		case DADA_KALEIDO_ELEMENT_VERTEX:
		case DADA_KALEIDO_ELEMENT_EDGE:
		case DADA_KALEIDO_ELEMENT_RADIUSPOINT:
			paint_shape(x, g, rect, center, &x->shapes[x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx], 2);
			break;
		case DADA_KALEIDO_ELEMENT_SAMPLINGPOINT:
		{
			t_kaleido_sampling_pt *spt = &x->sampling_points[x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx];
			t_pt spt_pixel = coord_to_pix(dadaobj_cast(x), center, spt->r_it.coord) ;
			spt_pixel.y = round_to_semiinteger(spt_pixel.y);

			t_jrgba bordercolor = build_jrgba(0.2, 0.2, 0.2, 1);
			paint_circle_stroken(g, bordercolor, spt_pixel.x, spt_pixel.y, x->sampling_points_size + DADA_KALEIDO_SAMPLINGPOINT_SELECTION_PAD, 1);
            
            if (x->sampling_metadata_type == DADA_KALEIDO_METADATA_PITCHNVEL) {
                t_rect pos = get_rect_near_pt_inside_rect(spt_pixel, 50, 70, build_rect(0, 0, rect.width, rect.height), build_pt(20, 20), build_pt(10, 10), NULL);
                paint_dashed_line(g, bordercolor, spt_pixel.x, spt_pixel.y, pos.x > spt_pixel.x ? pos.x : pos.x + pos.width,
                                  pos.y < spt_pixel.y ? pos.y + pos.height : pos.y, 3, 3);
                
                paint_sampling_point_note(x, g, spt, pos);
            } else {
                paint_score_label(x, g, build_pt(spt_pixel.x + 1, spt_pixel.y + 1), spt->label);
            }
			
			break;
		}
		default:
			break;
	}
	
	if (x->selected_shapes > 0) {
		long i;
		for (i = 0; i < x->num_shapes; i++)
			if (x->selected_shapes & (1 << i))
				paint_shape(x, g, rect, center, &x->shapes[i], 1);
	}
}


void kaleido_paint_ext(t_kaleido *x, t_object *view, t_dada_force_graphics *force_graphics)
{
    t_jgraphics *g = force_graphics->graphic_context;
    t_rect rect = force_graphics->rect;
    t_pt center = force_graphics->center_pix;
	double zoom = force_graphics->zoom.x;

	jgraphics_set_source_rgba(g, 0, 0, 0, 1); // alpha = 1;
	
    dadaobj_paint_background(dadaobj_cast(x), g, &rect);
    
    if (x->dont_paint)
        return;

    if (x->need_build_studio) {
		build_studio(x, rect, center, g);
		x->need_build_studio = false;
	}
	if (x->need_build_tile) {
		build_tile(x, rect, center);
		x->need_build_tile = false;
	}
    
    
/*	{
        jbox_invalidate_layer((t_object *)x, NULL, gensym("sampling_points"));
        kaleido_paint_sampling_points(x, view, rect, center, zoom);
//        jbox_invalidate_layer((t_object *)x, NULL, gensym("static_layer1"));
//        paint_static_layer1(x, view, rect);
        return;
	}
*/
	
	
	// calculate mirror vertices
	if (x->edit_mode) {
		t_pt p1 = center;
		t_pt p2 = coord_to_pix(dadaobj_cast(x), center, x->main_corolla.vertex[0]);
		t_pt p3 = coord_to_pix(dadaobj_cast(x), center, x->main_corolla.vertex[1]);
		
		// draw background
		jgraphics_image_surface_draw_fast(g, x->s_studio);
		
		repaint_hovered_and_selected_items(x, g, rect, center);
		
		// turn light off
		t_jrgba black = build_jrgba(0, 0, 0, 0.3);
		jgraphics_set_source_jrgba(g, &black);
		jgraphics_set_line_width(g, 0);
		jgraphics_move_to(g, p1.x, p1.y);
		jgraphics_line_to(g, p2.x, p2.y);
		jgraphics_line_to(g, p3.x, p3.y);
		jgraphics_line_to(g, p3.x, 0);
		jgraphics_line_to(g, rect.width, 0);
		jgraphics_line_to(g, rect.width, rect.height);
		jgraphics_line_to(g, 0, rect.height);
		jgraphics_line_to(g, 0, 0);
		jgraphics_line_to(g, p3.x, 0);
		jgraphics_line_to(g, p3.x, p3.y);
		jgraphics_close_path(g); 
		jgraphics_fill(g);
		
		// paint mirrors
		paint_triangle(g, build_jrgba(0, 0, 0, 0.9), build_jrgba(0, 0, 0, 0), p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, 4);
		
	} else {
		
		// drawing tiled copies
		long chamber_size = ceil(x->mirror_size * zoom);
		t_rect r_tile = build_rect(0, 0, 2 * chamber_size, 2 * chamber_size);
		t_pt curr_center = center;
		
		if (!x->extend_when_possible) {
			jgraphics_image_surface_draw(g, x->s_tile, r_tile, build_rect(curr_center.x - chamber_size, curr_center.y - chamber_size, 2 * chamber_size, 2 * chamber_size));
		} else {
			switch (x->num_steps) {
				case 3: // equilateral triangular tile
				{
					t_pt curr_center;
					double mirror_size = x->mirror_size * zoom;
					double triangle_height = mirror_size * sqrt(3)/2.;
					double mirror_size_3_2 = mirror_size * 3/2.;
					long row = 1 - ceil(center.y/triangle_height);
					long col = 1 - ceil((center.x + mirror_size)/mirror_size_3_2);
					curr_center.x =  center.x + col * mirror_size_3_2;
					while (curr_center.x - mirror_size < rect.width) {
						curr_center.y =  center.y + (row + (((row % 2 && col % 2 == 0) || (row % 2 == 0 && col % 2)) ? -1 : 0)) * triangle_height;
						while (curr_center.y - triangle_height < rect.height) {
							jgraphics_image_surface_draw(g, x->s_tile, r_tile, build_rect(curr_center.x - chamber_size, curr_center.y - chamber_size, 2 * chamber_size, 2 * chamber_size));
							curr_center.y += 2 * triangle_height;
						}
						curr_center.x += mirror_size_3_2;
						col++;
					}
					break;
				}
				case 2: // 45° isosceles triangular tie
				{
					t_pt curr_center;
					double mirror_size = x->mirror_size * zoom;
					long row = 1 - ceil((center.y + mirror_size)/mirror_size);
					long col = 1 - ceil((center.x + mirror_size)/mirror_size);
					curr_center.x =  center.x + col * mirror_size;
					while (curr_center.x - mirror_size < rect.width) {
						curr_center.y =  center.y + (row + (((row % 2 && col % 2 == 0) || (row % 2 == 0 && col % 2)) ? -1 : 0)) * mirror_size;
						while (curr_center.y - mirror_size < rect.height) {
							jgraphics_image_surface_draw(g, x->s_tile, r_tile, build_rect(curr_center.x - chamber_size, curr_center.y - chamber_size, 2 * chamber_size, 2 * chamber_size));
							curr_center.y += 2 * mirror_size;
						}
						curr_center.x += mirror_size;
						col++;
					}
					break;
				}				
				default:
					jgraphics_image_surface_draw(g, x->s_tile, r_tile, build_rect(curr_center.x - chamber_size, curr_center.y - chamber_size, 2 * chamber_size, 2 * chamber_size));
					break;
			}
		}
		
		if (x->show_sampling_points)
			kaleido_paint_sampling_points(x, view, rect, center, zoom, force_graphics);

		repaint_hovered_and_selected_items(x, g, rect, center);
	}


    dadaobj_paint_border(dadaobj_cast(x), g, &rect);
}


void kaleido_paint(t_kaleido *x, t_object *view)
{
    dadaobj_paint(dadaobj_cast(x), view);
}

///////// POPUP MENU FUNCTIONS



void popup_make_regular(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_kaleido *x = (t_kaleido *)d_ob->orig_obj;
	long idx = x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx;
	if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADA_KALEIDO_ELEMENT_SHAPE) {
		if (x->shapes[idx].shape.type == DADA_SHAPE_POLYGON) {
			long num_verts = x->shapes[idx].shape.shape.polygon.num_vertices;
			double new_radius = get_dadapolygon_perimeter(&x->shapes[idx].shape.shape.polygon) / (2 * num_verts * sin(PI/num_verts));
			t_pt barycenter = get_dadapolygon_barycenter(&x->shapes[idx].shape.shape.polygon);
			long i;
			for (i = 0; i < num_verts; i++) 
				x->shapes[idx].shape.shape.polygon.vertex[i] = pt_pt_sum(barycenter, pt_number_prod(build_pt(cos(TWO_PI * i/num_verts), sin(TWO_PI * i/num_verts)), new_radius));
			
		} else if (x->shapes[idx].shape.type == DADA_SHAPE_ELLIPSE) {
			double average_radius = 0.5 * (x->shapes[idx].shape.shape.ellipse.radius.x + x->shapes[idx].shape.shape.ellipse.radius.y);
			x->shapes[idx].shape.shape.ellipse.radius.x = average_radius;
			x->shapes[idx].shape.shape.ellipse.radius.y = average_radius;
			x->shapes[idx].shape.shape.ellipse.rotation = 0;
		}
		
		x->need_build_tile = x->need_build_studio = true;
		process_change(x);
        dadaobj_send_changedbang(d_ob);
	}
}

void popup_make_dadapolygon(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_kaleido *x = (t_kaleido *)d_ob->orig_obj;
	long idx = x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx;
	if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADA_KALEIDO_ELEMENT_SHAPE && x->shapes[idx].shape.type == DADA_SHAPE_ELLIPSE) {
		t_pt center = x->shapes[idx].shape.shape.ellipse.center;
		double semiside = x->shapes[idx].shape.shape.ellipse.radius.x;
		x->shapes[idx].shape.type = DADA_SHAPE_POLYGON;
		x->shapes[idx].shape.shape.polygon.num_vertices = 4;
		x->shapes[idx].shape.shape.polygon.vertex[0] = pt_pt_sum(center, build_pt(semiside, -semiside));
		x->shapes[idx].shape.shape.polygon.vertex[1] = pt_pt_sum(center, build_pt(semiside, semiside));
		x->shapes[idx].shape.shape.polygon.vertex[2] = pt_pt_sum(center, build_pt(-semiside, semiside));
		x->shapes[idx].shape.shape.polygon.vertex[3] = pt_pt_sum(center, build_pt(-semiside, -semiside));
		
		x->need_build_tile = x->need_build_studio = true;
		process_change(x);
        dadaobj_send_changedbang(d_ob);
	}
}


void popup_make_ellipse(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_kaleido *x = (t_kaleido *)d_ob->orig_obj;
	long idx = x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx;
	if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADA_KALEIDO_ELEMENT_SHAPE && x->shapes[idx].shape.type == DADA_SHAPE_POLYGON) {
		double avg_dist_from_baryc = get_average_vertex_distance_from_barycenter(&x->shapes[idx].shape.shape.polygon);
		t_pt baryc = get_dadapolygon_barycenter(&x->shapes[idx].shape.shape.polygon);
		
		x->shapes[idx].shape.type = DADA_SHAPE_ELLIPSE;
		x->shapes[idx].shape.shape.ellipse.center = baryc;
		x->shapes[idx].shape.shape.ellipse.radius.x = x->shapes[idx].shape.shape.ellipse.radius.y = avg_dist_from_baryc;
		x->shapes[idx].shape.shape.ellipse.rotation = 0;
		
		x->need_build_tile = x->need_build_studio = true;
		process_change(x);
        dadaobj_send_changedbang(d_ob);
	}
}


void popup_change_color(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_kaleido *x = (t_kaleido *)d_ob->orig_obj;
	long idx = x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx;
	if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADA_KALEIDO_ELEMENT_SHAPE) {
		t_jrgba color = symbol_to_color(label);
		double alpha = x->shapes[idx].shape.color.alpha;
		color.alpha = alpha;
		x->shapes[idx].shape.color = color;
		
		x->need_build_tile = x->need_build_studio = true;
		process_change(x);
        dadaobj_send_changedbang(d_ob);
	}
}

void popup_change_opacity(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_kaleido *x = (t_kaleido *)d_ob->orig_obj;
	long idx = x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx;
	if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADA_KALEIDO_ELEMENT_SHAPE) {
		double alpha = 1.;
		if (label == gensym("25%"))
			alpha = 0.25;
		else if (label == gensym("50%"))
			alpha = 0.5;
		else if (label == gensym("75%"))
			alpha = 0.75;
		else
			alpha = 1.;
		x->shapes[idx].shape.color.alpha = alpha;
		
		x->need_build_tile = x->need_build_studio = true;
		process_change(x);
        dadaobj_send_changedbang(d_ob);
	}
}

void popup_delete_shape(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_kaleido *x = (t_kaleido *)d_ob->orig_obj;
    if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADA_KALEIDO_ELEMENT_SHAPE) {
		delete_shape(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx);
        dadaobj_send_changedbang(d_ob);
    }
}

void popup_change_midichannel(t_dadaobj *d_ob, t_symbol *label, const t_llll *address)
{
	t_kaleido *x = (t_kaleido *)d_ob->orig_obj;
	if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADA_KALEIDO_ELEMENT_SHAPE) {
        if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx >= 0 && x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx < x->num_shapes && address && address->l_tail) {
            x->shapes[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx].shape.channel = hatom_getlong(&address->l_tail->l_hatom) - 1; // -1 is for the menu MIDIchannels symbol
            dadaobj_send_changedbang(d_ob);
        }
	}
}
	
	
void show_shape_popup_menu(t_kaleido *x, t_object *patcherview, t_pt pt, long modifiers)
{
	// what will be checked
	t_llll *checked = llll_from_text_buf((char *)"0 0 0 (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0) 0 0 0 0 0 0", false);
	char *checked_buf = NULL;
	if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADA_KALEIDO_ELEMENT_SHAPE && x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx >= 0 && x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx < x->num_shapes) {
		long channel = x->shapes[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx].shape.channel;
		if (x->shapes[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx].shape.type == DADA_SHAPE_ELLIPSE)
			hatom_setlong(&checked->l_head->l_next->l_hatom, 1);
		else if (x->shapes[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx].shape.type == DADA_SHAPE_POLYGON)
			hatom_setlong(&checked->l_head->l_hatom, 1);
		if (channel >= 1 && channel <= 16) {
			t_llllelem *elem = llll_getindex(hatom_getllll(&checked->l_head->l_next->l_next->l_next->l_hatom), channel + 1, I_NON_NEGATIVE); // +1 is for the first MIDIchannel symbol
			if (elem)
				hatom_setlong(&elem->l_hatom, 1);
		}
	}
	llll_to_text_buf(checked, &checked_buf, 0, BACH_DEFAULT_MAXDECIMALS, LLLL_T_NONE, LLLL_TE_SMART, LLLL_TB_SMART, NULL);
	
    ezdisplay_popup_menu_for_dadaitem(dadaobj_cast(x), patcherview, (t_dadaitem *)&x->shapes[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx],
                                      D_SOLO | D_MUTE | D_INACTIVE,
						 (char *)"Polygon Ellipse separator ( MIDIchannel 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 ) ( Color Red Green Blue Yellow Orange Violet ) ( Opacity 25% 50% 75% 100% ) separator Make Regular separator Delete",
						 "0 0 0 0 0 0 0 0 0 0", checked_buf, "", "", "", 
						 (void *)popup_make_dadapolygon, (void *)popup_make_ellipse, NULL, (void *)popup_change_midichannel, (void *)popup_change_color, (void *)popup_change_opacity, NULL, 
						 (void *)popup_make_regular, NULL, (void *)popup_delete_shape, WHITENULL);
	
	llll_free(checked);
	bach_freeptr(checked_buf);
}

void popup_new_dadapolygon(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_kaleido *x = (t_kaleido *)d_ob->orig_obj;
	long i, num_verts = hatom_getlong(&address->l_tail->l_hatom) + 1;
	t_pt vertices[DADA_POLYGON_MAX_VERTICES];
	
	for (i = 0; i < num_verts; i++) 
		vertices[i] = pt_pt_sum(x->b_ob.d_ob.m_interface.mousedown_coord, pt_number_prod(build_pt(cos(TWO_PI * i/num_verts), sin(TWO_PI * i/num_verts)), x->mirror_size/3.));

	add_shape(x, build_dadapolygon(change_alpha(dada_long_to_color(x->num_shapes), 0.5), find_max_midichannel(x) + 1, num_verts, vertices));
    dadaobj_send_changedbang(d_ob);
}

void popup_new_circle(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_kaleido *x = (t_kaleido *)d_ob->orig_obj;
	add_shape(x, build_ellipse(change_alpha(dada_long_to_color(x->num_shapes), 0.5), find_max_midichannel(x) + 1, x->b_ob.d_ob.m_interface.mousedown_coord, build_pt(x->mirror_size/3., x->mirror_size/3.), 0));
    dadaobj_send_changedbang(d_ob);
}

void popup_new_sampling_point(t_dadaobj *d_ob, t_symbol *label, const t_llll *address)
{
    t_kaleido *x = (t_kaleido *)d_ob->orig_obj;
    t_pt coord = x->b_ob.d_ob.m_interface.mousedown_coord;
    add_sampling_point(x, coord, DADA_DEFAULT_PITCH, DADA_DEFAULT_VELOCITY, _llllobj_sym_score, x->sampling_metadata_type == DADA_KALEIDO_METADATA_SCORE ? llll_get() : NULL);
    dadaobj_send_changedbang(d_ob);
    kaleido_iar(x);
}

void popup_rotate_all(t_dadaobj *d_ob, t_symbol *label, const t_llll *address)
{
	t_kaleido *x = (t_kaleido *)d_ob->orig_obj;
	rotate_all_shapes(x, build_pt(0, 0), 0.2617993878 * (hatom_getlong(&address->l_tail->l_hatom) - 1), false);
    dadaobj_send_changedbang(d_ob);
}

void popup_shake_all(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_kaleido *x = (t_kaleido *)d_ob->orig_obj;
	double region_radius = x->mirror_size;
	long idx = hatom_getlong(&address->l_tail->l_hatom) - 1;
	t_pt region_center;
	region_center.x = (x->main_corolla.vertex[0].x + x->main_corolla.vertex[1].x)/3.;
	region_center.y = (x->main_corolla.vertex[0].y + x->main_corolla.vertex[1].y)/3.;
	shake_all_shapes(x, 0, 20 * idx, 0, 20 * idx, region_center, region_radius);
    dadaobj_send_changedbang(d_ob);
}

void popup_no_solos(t_dadaobj *d_ob, t_symbol *label, const t_llll *address)
{
    t_kaleido *x = (t_kaleido *)d_ob->orig_obj;
    long i;
    for (i = 0; i < x->num_sampling_points; i++)
        x->sampling_points[i].r_it.flags &= ~D_SOLO;
    for (i = 0; i < x->num_shapes; i++)
        x->shapes[i].r_it.flags &= ~D_SOLO;
    dadaobj_update_solos(d_ob);
    dadaobj_send_changedbang(d_ob);
}

void popup_no_mute(t_dadaobj *d_ob, t_symbol *label, const t_llll *address)
{
    t_kaleido *x = (t_kaleido *)d_ob->orig_obj;
    long i;
    for (i = 0; i < x->num_sampling_points; i++)
        x->sampling_points[i].r_it.flags &= ~D_MUTE;
    for (i = 0; i < x->num_shapes; i++)
        x->shapes[i].r_it.flags &= ~D_MUTE;
    dadaobj_invalidate_and_redraw(d_ob);
    dadaobj_send_changedbang(d_ob);
}

void popup_no_inactive(t_dadaobj *d_ob, t_symbol *label, const t_llll *address)
{
    t_kaleido *x = (t_kaleido *)d_ob->orig_obj;
    long i;
    for (i = 0; i < x->num_shapes; i++)
        x->shapes[i].r_it.flags &= ~D_INACTIVE;
    dadaobj_invalidate_and_redraw(d_ob);
    dadaobj_send_changedbang(d_ob);
}
void show_background_popup_menu(t_kaleido *x, t_object *patcherview, t_pt pt, long modifiers)
{
	ezdisplay_popup_menu(dadaobj_cast(x), patcherview, 
						 (char *)"(New Polygon Triangle Square Pentagon Hexagon) New Ellipse New Sampling Point separator (Rotate 15° 30° 45° 60° 75° 90° 105° 120° 135° 150° 165° 180°) (Shake Light Medium Heavy) separator No Solo No Mute No Inactive",
						 "", "", "", "", "", 
						 (void *)popup_new_dadapolygon, (void *)popup_new_circle, (void *)popup_new_sampling_point, NULL, (void *)popup_rotate_all, (void *)popup_shake_all, NULL, (void *)popup_no_solos, (void *)popup_no_mute, (void *)popup_no_inactive, WHITENULL);
}

void popup_delete_samplingpoint(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_kaleido *x = (t_kaleido *)d_ob->orig_obj;
	if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADA_KALEIDO_ELEMENT_SAMPLINGPOINT)
		delete_sampling_point(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx);
}

void show_samplingpoint_popup_menu(t_kaleido *x, t_object *patcherview, t_pt pt, long modifiers)
{
    ezdisplay_popup_menu_for_dadaitem(dadaobj_cast(x), patcherview, (t_dadaitem *)&x->sampling_points[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx],
                                      D_SOLO | D_MUTE,
                                      (char *)"Delete", "", "", "", "", "",
                                      (void *)popup_delete_samplingpoint, WHITENULL);
}



////////// INTERFACE FUNCTIONS


void kaleido_focusgained(t_kaleido *x, t_object *patcherview) {
	if (dadaobj_focusgained(dadaobj_cast(x), patcherview))
		return;
}

void kaleido_focuslost(t_kaleido *x, t_object *patcherview) {
	if (dadaobj_focuslost(dadaobj_cast(x), patcherview))
		return;
}


void kaleido_output_notification(t_kaleido *x, t_dadaitem_identifier *ident, t_symbol *sym)
{
    t_llll *ll = llll_get();
    llll_appendsym(ll, sym);
    
    switch (ident->type) {
        case DADA_KALEIDO_ELEMENT_SHAPE:
            llll_appendsym(ll, gensym("shape"));
            llll_appendlong(ll, ident->idx + 1);
            if (dadaobj_cast(x)->m_interface.send_notifications == DADAOBJ_NOTIFY_VERBOSE)
                llll_appendllll(ll, kaleido_get_single_shape(x, ident->idx));
            break;
            
        case DADA_KALEIDO_ELEMENT_SAMPLINGPOINT:
            llll_appendsym(ll, gensym("sampling"));
            llll_appendlong(ll, ident->idx + 1);
            if (dadaobj_cast(x)->m_interface.send_notifications == DADAOBJ_NOTIFY_VERBOSE)
                llll_appendllll(ll, kaleido_get_single_sampling_pt(x, ident->idx));
            break;
            
        default:
            llll_appendsym(ll, _llllobj_sym_none);
            break;
    }
    
    dadaobj_send_notification_llll(dadaobj_cast(x), ll);
}


void kaleido_mousemove(t_kaleido *x, t_object *patcherview, t_pt pt, long modifiers)
{
    t_dadaitem_identifier old_ident = x->b_ob.d_ob.m_interface.mousemove_item_identifier;

    llll_format_modifiers(&modifiers, NULL);
	if (dadaobj_mousemove(dadaobj_cast(x), patcherview, pt, modifiers))
		return;

	if (x->b_ob.d_ob.m_interface.allow_mouse_hover && (x->edit_mode || x->allow_edit_outside_chamber)) {
		x->b_ob.d_ob.m_interface.mousemove_item_identifier = pixel_to_element(x, pt, patcherview, NULL);
        
        if (!dadaitem_identifier_eq(old_ident, x->b_ob.d_ob.m_interface.mousemove_item_identifier))
            kaleido_output_notification(x, &x->b_ob.d_ob.m_interface.mousemove_item_identifier, gensym("hover"));
        
		jbox_redraw((t_jbox *)x);
	} else {
		if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_KALEIDO_ELEMENT_SHAPE) {
			x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADA_KALEIDO_ELEMENT_NONE;
			dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
			jbox_redraw((t_jbox *)x);
		}
	}
	
	
	if (popup_menu_is_shown(dadaobj_cast(x))) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
	} else if ((x->edit_mode || x->allow_edit_outside_chamber) && x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_KALEIDO_ELEMENT_SHAPE && x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_SCALE) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_SCALE);
	} else if ((x->edit_mode || x->allow_edit_outside_chamber) && x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_KALEIDO_ELEMENT_SHAPE && x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_CHANGE_COLOR) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_CHANGE_COLOR);
	} else if (x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_CHANGE_PITCH && x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_KALEIDO_ELEMENT_SAMPLINGPOINT) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_NOTE_UPDOWN);
	} else if (x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_CHANGE_VELOCITY && x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_KALEIDO_ELEMENT_SAMPLINGPOINT) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_CHANGE_VELOCITY);
	} else if (x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_ROTATE && (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_KALEIDO_ELEMENT_SHAPE || x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_KALEIDO_ELEMENT_NONE)) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_ROTATION);
	} else if (x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_ARROW
			   && (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_KALEIDO_ELEMENT_SHAPE || x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_KALEIDO_ELEMENT_SAMPLINGPOINT)
			   && modifiers == eCommandKey) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DELETE);
	} else if (x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_ARROW
			   && x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_KALEIDO_ELEMENT_VERTEX
			   && modifiers == eCommandKey) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DELETE_POINT);
	} else if (x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_ARROW
			   && (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_KALEIDO_ELEMENT_SHAPE || x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_KALEIDO_ELEMENT_SAMPLINGPOINT)
			   && modifiers == eAltKey) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DUPLICATE);
	} else if (x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_ARROW
			   && x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_KALEIDO_ELEMENT_VERTEX
			   && modifiers == eAltKey) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DUPLICATE_POINT);
	} else if (x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_ARROW && x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_KALEIDO_ELEMENT_RADIUSPOINT) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_RESIZE_BOTTOMLEFTCORNER);
	} else if (x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_ARROW && 
			   (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_KALEIDO_ELEMENT_SHAPE || x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_KALEIDO_ELEMENT_VERTEX || x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_KALEIDO_ELEMENT_RADIUSPOINT)) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_MOVE);
	} else {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
	}
}


void kaleido_mousedown(t_kaleido *x, t_object *patcherview, t_pt pt, long modifiers){

	if (dadaobj_mousedown(dadaobj_cast(x), patcherview, pt, modifiers))
		return;

	x->b_ob.d_ob.m_interface.mousedown_item_identifier = pixel_to_element(x, pt, patcherview, &x->b_ob.d_ob.m_interface.mousedown_coord);

	if (modifiers & ePopupMenu) {
		
		switch (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type) {
			case DADA_KALEIDO_ELEMENT_SHAPE:
				show_shape_popup_menu(x, patcherview, pt, modifiers);
				break;
			case DADA_KALEIDO_ELEMENT_NONE:
				show_background_popup_menu(x, patcherview, pt, modifiers);
				break;
			case DADA_KALEIDO_ELEMENT_SAMPLINGPOINT:
				show_samplingpoint_popup_menu(x, patcherview, pt, modifiers);
				break;
			default:
				break;
		}
		
	} else {
		
		llll_format_modifiers(&modifiers, NULL);

        kaleido_output_notification(x, &x->b_ob.d_ob.m_interface.mousedown_item_identifier, gensym("click"));
		
        switch (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type) {
			case DADA_KALEIDO_ELEMENT_SHAPE:
				if (modifiers == eCommandKey) {
					delete_shape(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx);
				} else {
					long shape = x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx;
					if (shape >= 0 && (x->selected_shapes & (1 << shape))) {
						//	nothing to do, already selected
					} else if (shape >= 0 && modifiers & eShiftKey)
						x->selected_shapes |= (1 << shape);
					else if (shape >= 0)
						x->selected_shapes = (1 << shape);
					else if (!(modifiers & eShiftKey))
						x->selected_shapes = 0;
				}
				break;
				
			case DADA_KALEIDO_ELEMENT_VERTEX:
				x->selected_shapes = 0; // clear selection
				if (modifiers == eCommandKey) {
					delete_dadapolygon_vertex(&x->shapes[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx].shape.shape.polygon, x->b_ob.d_ob.m_interface.mousedown_item_identifier.secondary_idx, 3);
					x->need_build_tile = x->need_build_studio = true;
				}
			
			case DADA_KALEIDO_ELEMENT_SAMPLINGPOINT:
				if (modifiers == eCommandKey) {
					delete_sampling_point(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx);
					jbox_invalidate_layer((t_object *)x, NULL, gensym("sampling_points"));
				}
			
			default:
				x->selected_shapes = 0; // clear selection
				break;
		}
	}
	
	jbox_redraw((t_jbox *)x);
	
}

void kaleido_mouseup(t_kaleido *x, t_object *patcherview, t_pt pt, long modifiers){
	
	llll_format_modifiers(&modifiers, NULL);
	
	if (dadaobj_mouseup(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
	
	if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADA_KALEIDO_ELEMENT_SAMPLINGPOINT && x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_CHANGE_PITCH) 
		x->sampling_points[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx].pitch_mc = snap_to_microtonal_grid_do(x->sampling_points[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx].pitch_mc, x->tonedivision);
	
	x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADA_KALEIDO_ELEMENT_NONE;
	x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag = 0;
}

void kaleido_mousedrag(t_kaleido *x, t_object *patcherview, t_pt pt, long modifiers){

	llll_format_modifiers(&modifiers, NULL);
	
	if (dadaobj_mousedrag(dadaobj_cast(x), patcherview, pt, modifiers))
		return;

	t_pt delta = x->b_ob.d_ob.m_interface.mousedrag_delta_pix;
	double zoom = x->b_ob.d_ob.m_zoom.zoom.x;
	
	if (x->edit_mode || x->allow_edit_outside_chamber) {
		
		switch (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type) {
			case DADA_KALEIDO_ELEMENT_SHAPE:
				switch (modifiers) {
					case eAltKey:
						if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag & DADAITEM_IDENTIFIER_FLAG_DUPLICATED) {
							move_selected_shapes(x, build_pt(delta.x/zoom, -delta.y/zoom));
						} else {
							duplicate_selected_shapes(x, true, true);
						}
						break;
					case 0:
						switch (x->b_ob.d_ob.m_tools.curr_tool) {
							case DADA_TOOL_ARROW:
								move_selected_shapes(x, build_pt(delta.x/zoom, -delta.y/zoom));
								break;
							case DADA_TOOL_SCALE:
							{
								double scale_factor = pow(2, -delta.y/DADA_KALEIDO_ROTATION_SCALE_FACTOR);
								scale_selected_shapes(x, build_pt(0, 0), scale_factor, scale_factor, true);
							}
								break;
							case DADA_TOOL_ROTATE:
								if (x->selected_shapes > 0) 
									rotate_selected_shapes(x, build_pt(0, 0), delta.y/DADA_KALEIDO_ROTATION_INTERFACE_FACTOR, true);
								else
									rotate_all_shapes(x, build_pt(0, 0), delta.y/DADA_KALEIDO_ROTATION_INTERFACE_FACTOR, false);
								break;
							case DADA_TOOL_CHANGE_COLOR:
								change_selected_shapes_color_constraint(x, delta.x/50, -delta.y/100);
								break;
							default:
								break;
						}
						break;
				}
				break;
				
			case DADA_KALEIDO_ELEMENT_VERTEX:
				switch (modifiers) {
					case eAltKey:
						if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag & DADAITEM_IDENTIFIER_FLAG_DUPLICATED) {
							t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), patcherview, pt);
							move_dadapolygon_vertex(&x->shapes[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx].shape.shape.polygon, x->b_ob.d_ob.m_interface.mousedown_item_identifier.secondary_idx, coord , false);
							x->need_build_studio = x->need_build_tile = true;
							jbox_redraw((t_jbox *)x);
						} else {
							kaleido_undo_step_push_shapes(x, gensym("Duplicate Vertex"));
							t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), patcherview, pt);
							long new_idx = duplicate_dadapolygon_vertex(&x->shapes[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx].shape.shape.polygon, x->b_ob.d_ob.m_interface.mousedown_item_identifier.secondary_idx, coord);
							if (new_idx < 0) {
								object_error((t_object *)x, "Can't duplicate vertex: maximun number of sides reached.");
								x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADA_KALEIDO_ELEMENT_NONE;
							} else {
								x->b_ob.d_ob.m_interface.mousedown_item_identifier.secondary_idx = new_idx;
								x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag |= DADAITEM_IDENTIFIER_FLAG_DUPLICATED;
								x->need_build_studio = x->need_build_tile = true;
								jbox_redraw((t_jbox *)x);
							}
						}
						break;
					case eCommandKey:
						if (x->shapes[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx].shape.shape.polygon.num_vertices > 3)
							kaleido_undo_step_push_shapes(x, gensym("Delete Vertex"));
						if (delete_dadapolygon_vertex(&x->shapes[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx].shape.shape.polygon, x->b_ob.d_ob.m_interface.mousedown_item_identifier.secondary_idx, 3))
							object_error((t_object *)x, "Can't delete vertex: polygon must have at least three sides.");
						else {
							x->need_build_studio = x->need_build_tile = true;
							jbox_redraw((t_jbox *)x);
						}
						break;
					default:
					{
						kaleido_undo_step_push_shapes(x, gensym("Move Vertex"));
						t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), patcherview, pt);
						move_dadapolygon_vertex(&x->shapes[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx].shape.shape.polygon, x->b_ob.d_ob.m_interface.mousedown_item_identifier.secondary_idx, coord , false);
						x->need_build_studio = x->need_build_tile = true;
						jbox_redraw((t_jbox *)x);
					}
						break;
				}
				break;
				
			case DADA_KALEIDO_ELEMENT_RADIUSPOINT:
				if (!modifiers || modifiers == eShiftKey) {
					t_ellipse *el = &x->shapes[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx].shape.shape.ellipse;
					double delta_r = 0;
					kaleido_undo_step_push_shapes(x, gensym("Modify Radius"));
					t_pt delta_prime = build_pt(delta.x, -delta.y); 
					if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.secondary_idx == 0) {
						t_pt vector = pt_pt_diff(get_ellipse_radiuspoint_coord(el, 0), el->center);
						delta_r =  pt_pt_scalarprod(vector, delta_prime)/(sqrt(vector.x * vector.x + vector.y * vector.y));
					} else if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.secondary_idx == 1) {
						t_pt vector = pt_pt_diff(get_ellipse_radiuspoint_coord(el, 1), el->center);
						delta_r =  pt_pt_scalarprod(vector, delta_prime)/(sqrt(vector.x * vector.x + vector.y * vector.y));
					}
					
					if (modifiers & eShiftKey)  {
						el->radius.x += delta_r;
						el->radius.y += delta_r;
					} else if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.secondary_idx == 0)
						el->radius.x += delta_r;
					else
						el->radius.y += delta_r;

					el->radius.x = MAX(0, el->radius.x);
					el->radius.y = MAX(0, el->radius.y);
					
					x->need_build_studio = x->need_build_tile = true;
					jbox_redraw((t_jbox *)x);
				}
				break;
				
			case DADA_KALEIDO_ELEMENT_SAMPLINGPOINT:
				switch (modifiers) {
					case eAltKey:
						if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag & DADAITEM_IDENTIFIER_FLAG_DUPLICATED) {
							move_sampling_point(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, build_pt(delta.x/zoom, -delta.y/zoom));
						} else {
							t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), patcherview, pt);
							duplicate_sampling_point(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, coord, true);
							x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag |= DADAITEM_IDENTIFIER_FLAG_DUPLICATED;
						}
						break;
					case 0:
						switch (x->b_ob.d_ob.m_tools.curr_tool) {
							case DADA_TOOL_ARROW:
								move_sampling_point(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, build_pt(delta.x/zoom, -delta.y/zoom));
								break;
							case DADA_TOOL_CHANGE_PITCH:
								change_sampling_point_pitch(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, -delta.y * 10);
								break;
							case DADA_TOOL_CHANGE_VELOCITY:
								change_sampling_point_velocity(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, -delta.y / 1.);
								break;
							default:
								break;
						}
						break;
				}
				jbox_invalidate_layer((t_object *)x, NULL, gensym("sampling_points"));
				jbox_redraw((t_jbox *)x);
				break;
				
			default:
				if (x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_ROTATE) 
					rotate_all_shapes(x, build_pt(0, 0), delta.y/DADA_KALEIDO_ROTATION_INTERFACE_FACTOR, false);
				break;
		}
	}
}

void kaleido_mouseenter(t_kaleido *x, t_object *patcherview, t_pt pt, long modifiers)
{
    jbox_redraw((t_jbox *)x);
}

void kaleido_mouseleave(t_kaleido *x, t_object *patcherview, t_pt pt, long modifiers)
{
    x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADA_KALEIDO_ELEMENT_NONE;
    x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx = 0;
    jbox_redraw((t_jbox *)x);
}

long kaleido_keyup(t_kaleido *x, t_object *patcherview, long keycode, long modifiers, long textcharacter){
			
	llll_format_modifiers(&modifiers, &keycode);

	if (dadaobj_keyup(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
		return 1;
	
	return 0;
}

long kaleido_key(t_kaleido *x, t_object *patcherview, long keycode, long modifiers, long textcharacter){
	llll_format_modifiers(&modifiers, &keycode);
	
	if (dadaobj_key(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
		return 1;

	switch (keycode) {
		case JKEY_TAB:	// edit
			x->edit_mode = !x->edit_mode;
			jbox_redraw((t_jbox *)x);
			return 1;
		case JKEY_ESC:
			send_all_noteoffs(x);
			x->selected_shapes = 0;
			jbox_redraw((t_jbox *)x);
			return 1;
        case JKEY_SPACEBAR:
            object_attr_setchar(x, _llllobj_sym_play, !x->play);
            return 1;
		case JKEY_BACKSPACE:
			delete_selected_shapes(x);
			return 1;
		case 'a':
			if (modifiers == eCommandKey) {
				kaleido_select_all(x);
				return 1;
			}
			break;
		case 'p':
			break;
		default:
			break;
	}

	return 0;
}



////////////////// UNDO HANDLING


void kaleido_undo_postprocess(t_kaleido *x)
{
	jbox_invalidate_layer((t_object *)x, NULL, gensym("sampling_points"));
	x->need_build_tile = x->need_build_studio = true;
	process_change(x);
	jbox_redraw((t_jbox *)x);
}


void kaleido_undo_step_push_shapes(t_kaleido *x, t_symbol *operation)
{
	undo_add_interface_step(dadaobj_cast(x), DADA_FUNC_v_oX, (method)kaleido_set_shapes , NULL, DADA_FUNC_X_o, (method)kaleido_get_shapes, NULL, DADA_UNDO_OP_MODIFICATION,operation);
}

void kaleido_undo_step_push_sampling_points(t_kaleido *x, t_symbol *operation)
{
	undo_add_interface_step(dadaobj_cast(x), DADA_FUNC_v_oX, (method)kaleido_set_sampling , NULL, DADA_FUNC_X_o, (method)kaleido_get_sampling, NULL, DADA_UNDO_OP_MODIFICATION,operation);
}
