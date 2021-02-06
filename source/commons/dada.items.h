/**
	@file
	dada.items.h
	Header for the handling of dada items
 
	by Daniele Ghisi
 */

#ifndef _DADA_ITEMS_H_
#define _DADA_ITEMS_H_

#include "dada.object.h"

#define move_pointer_forward(ptr, num_bytes) (((char *)ptr) + num_bytes)


typedef enum _dadaitem_action_flags // DIA stands for Dada Item Action
{
	DIA_UNDO_TICK			= 0x01,	//< Add undo tick
    DIA_UNDO_MARKER			= 0x02,	//< Also add undo marker (only makes sense if DIA_UNDO_TICK is also present)
	DIA_POSTPROCESS         = 0x04,	//< Perform dadaitem class postprocessing after action
	DIA_INTERFACE           = 0x08,	//< Account for interface modifications (such as: drag direction is fixed, or snap to grid)
    DIA_SNAPTOGRID          = 0x10,	//< Snap to grid straight away (otherwise snapping is usually performed at mouseup)
    DIA_USE_ATTR_DEFAULTS   = 0x20,	//< Use attribute defaults
} e_dadaitem_action_flags;

#define DIA_UNDO                        (DIA_UNDO_TICK | DIA_UNDO_MARKER)
#define DIA_UNDO_POSTPROCESS			(DIA_UNDO | DIA_POSTPROCESS)
#define DIA_UNDO_POSTPROCESS_INTERFACE  (DIA_UNDO | DIA_POSTPROCESS | DIA_INTERFACE)

#define DECLARE_DADA_ATTR(r_ob, man, forced_position, name, displayed_label, owner_type, struct_name, struct_member, attr_type, attr_size, display_type, preprocess_flags, postprocess_flags, default) \
{ \
	long di_class_id = dadaitem_class_get_id(&((t_dadaobj *)r_ob)->m_classes, owner_type); \
	bach_attribute_declare(man, forced_position, name, displayed_label, di_class_id, calcoffset(struct_name, struct_member), attr_type, attr_size, display_type, preprocess_flags, postprocess_flags); \
	bach_attribute_add_functions(bach_attribute_get(man, di_class_id, name), (bach_getter_fn)dada_default_get_bach_attr, (bach_setter_fn)dada_default_set_bach_attr, (bach_attr_process_fn)dada_default_attr_preprocess, (bach_attr_process_fn)dada_default_attr_postprocess, (bach_inactive_fn)dada_default_attr_inactive); \
    if (default) bach_attribute_get(man, di_class_id, name)->default_val = default; \
}


#define DECLARE_DADA_ATTR_SUBSTRUCTURE(r_ob, man, forced_position, name, displayed_label, owner_type, struct_name, struct_member, substruct_name, substruct_member, attr_type, attr_size, display_type, preprocess_flags, postprocess_flags) \
{ \
	long di_class_id = dadaitem_class_get_id(&((t_dadaobj *)r_ob)->m_classes, owner_type); \
	bach_attribute_declare(man, forced_position, name, displayed_label, di_class_id, calcoffset(struct_name, struct_member) + calcoffset(substruct_name, substruct_member), attr_type, attr_size, display_type, preprocess_flags, postprocess_flags); \
	bach_attribute_add_functions(bach_attribute_get(man, di_class_id, name), (bach_getter_fn)dada_default_get_bach_attr, (bach_setter_fn)dada_default_set_bach_attr, NULL, NULL, (bach_inactive_fn)dada_default_attr_inactive); \
}


/////////////   STANDARD EXTENSIONS OF THE DADA ITEM


typedef struct _dada_ball
{
	t_dadaitem	r_it;		///< Common properties of dada items
	
	t_pt		speed;		///< Speed (velocity) of the ball
	long		channel;	///< MIDIchannel of the ball
} t_dada_ball;


typedef struct _dada_card
{
	t_dadaitem	r_it;		///< Common properties of dada items
	
	t_symbol	*text;
	t_symbol	*icon_path;
	double		value;	
	
	// accessory stuff
	t_jsurface	*icon_surface;
	double		icon_width;
	double		icon_height;
} t_dada_card;



typedef struct _dada_block
{
	t_dadaitem	r_it;		///< Common properties of dada items
	
    long		state;
    
    char        solid;  ///< Is block solid? Or just background

    long        how_bumpeable; // a combination of e_dada_gamechar_via

	t_llll		*music;
	double		points;
	t_symbol	*sprite;
    t_symbol	*fragment_sprite;

    long        hit_count;
    t_llll		*hit_sequence;
    char        loop_hit_sequence;
    
    t_symbol    *prototype_dummy_for_attr; ///< Dummy field for prototype attribute linkage (unused: only referred via setter/getter)

    // internal
    t_pt        broken_slice_delta_coord;
    t_pt        broken_slice_speed;
} t_dada_block;


typedef struct _dada_coin
{
	t_dadaitem	r_it;		///< Common properties of dada items
	
	char		takeable;
	char		taken;

	t_llll		*music;
	double		points;
	long		vp;
	t_symbol	*sprite;

    t_symbol    *prototype_dummy_for_attr; ///< Dummy field for prototype attribute linkage (unused: only referred via setter/getter)
} t_dada_coin;


typedef struct _dada_portal
{
    t_dadaitem	r_it;		///< Common properties of dada items
    
    char        open;
    long        how_enter; /// a combination of e_dada_gamechar_via
    long        how_exit;   /// a combination of e_dada_gamechar_via
    t_symbol	*sprite;
    
    char        hero_only;

    t_llll		*music;
    t_llll		*enter_sequence;
    t_llll		*exit_sequence;

    t_symbol    *prototype_dummy_for_attr; ///< Dummy field for prototype attribute linkage (unused: only referred via setter/getter)
} t_dada_portal;



typedef enum _dada_gamechar_states
{
    DADA_GAMECHAR_STATE_IDLE        =	0x00,
	DADA_GAMECHAR_STATE_WALKING     =	0x01,
	DADA_GAMECHAR_STATE_JUMPING     =	0x02,
	DADA_GAMECHAR_STATE_FLYING      =	0x04,
	DADA_GAMECHAR_STATE_SWIMMING    =	0x08,   // yet unused
    DADA_GAMECHAR_STATE_RUNNING     =	0x10,   // yet unused
    DADA_GAMECHAR_STATE_GLIDING     =	0x20,	
	DADA_GAMECHAR_STATE_DYING       =	0x40,
	DADA_GAMECHAR_STATE_DEAD        =	0x80,
    DADA_GAMECHAR_STATE_GENERATING	=	0x100,
    DADA_GAMECHAR_STATE_ENTERINGPORTAL  =	0x200,
    DADA_GAMECHAR_STATE_EXITINGPORTAL	=	0x400,
    DADA_GAMECHAR_STATE_ELSEWHERE	=	0x800,
} e_dada_gamechar_states;

typedef enum _dada_gamechar_abilities
{
    DADA_GAMECHAR_ABILITY_NONE	=       0x00,
    DADA_GAMECHAR_ABILITY_WALK	=       0x01,
    DADA_GAMECHAR_ABILITY_JUMP	=       0x02,
    DADA_GAMECHAR_ABILITY_FLY	=       0x04,
    DADA_GAMECHAR_ABILITY_SWIM	=       0x08,   // yet unused
    DADA_GAMECHAR_ABILITY_RUN	=       0x10,	// yet unused
    DADA_GAMECHAR_ABILITY_GLIDE	=       0x20,
    DADA_GAMECHAR_ABILITY_BREAK	=       0x40,
    DADA_GAMECHAR_ABILITY_KILL	=       0x80,
    DADA_GAMECHAR_ABILITY_SHOOT	=       0x100,
    DADA_GAMECHAR_ABILITY_DIG	=       0x200,  // yet unused
    DADA_GAMECHAR_ABILITY_DIE	=       0x400,
} e_dada_gamechar_abilities;



typedef enum _dada_gamechar_types
{
    DADA_GAMECHAR_TYPE_IDLE         = 0,
    DADA_GAMECHAR_TYPE_USERCONTROL  = 1,         // controlled by user: "heroes"
    DADA_GAMECHAR_TYPE_ENEMY        = 2,
    DADA_GAMECHAR_TYPE_FOOD         = 3,
    DADA_GAMECHAR_TYPE_BULLET       = 4,
} e_dada_gamechar_types;




typedef enum _dada_block_states
{
    DADA_BLOCK_IDLE	=       0x00,
    DADA_BLOCK_BREAKING	=	0x01,
    DADA_BLOCK_INVISIBLE =	0x02,
} e_dada_block_states;


typedef enum _dada_gamechar_via
{
	DADA_GAMECHAR_VIA_SIDE_NONE		=	0x00,
	DADA_GAMECHAR_VIA_SIDE_TOP		=	0x01,
	DADA_GAMECHAR_VIA_SIDE_BOTTOM	=	0x02,
	DADA_GAMECHAR_VIA_SIDE_LEFT		=	0x04,
	DADA_GAMECHAR_VIA_SIDE_RIGHT	=	0x08,
    DADA_GAMECHAR_VIA_BUMP          =	0x10,
    DADA_GAMECHAR_VIA_TOUCH_GROUND  =	0x20,
    DADA_GAMECHAR_VIA_BULLET        =	0x40,
    DADA_GAMECHAR_VIA_GLIDE         =	0x80,
    DADA_GAMECHAR_VIA_SIDE_LEFT_RIGHT           =	DADA_GAMECHAR_VIA_SIDE_LEFT + DADA_GAMECHAR_VIA_SIDE_RIGHT,
    DADA_GAMECHAR_VIA_SIDE_TOP_BOTTOM           =	DADA_GAMECHAR_VIA_SIDE_TOP + DADA_GAMECHAR_VIA_SIDE_BOTTOM,
	DADA_GAMECHAR_VIA_SIDE_TOP_LEFT_RIGHT		=	DADA_GAMECHAR_VIA_SIDE_TOP + DADA_GAMECHAR_VIA_SIDE_LEFT + DADA_GAMECHAR_VIA_SIDE_RIGHT,
	DADA_GAMECHAR_VIA_SIDE_BOTTOM_LEFT_RIGHT	=	DADA_GAMECHAR_VIA_SIDE_BOTTOM + DADA_GAMECHAR_VIA_SIDE_LEFT + DADA_GAMECHAR_VIA_SIDE_RIGHT,
    DADA_GAMECHAR_VIA_SIDE_ANY                  =	DADA_GAMECHAR_VIA_SIDE_BOTTOM + DADA_GAMECHAR_VIA_SIDE_TOP + DADA_GAMECHAR_VIA_SIDE_LEFT + DADA_GAMECHAR_VIA_SIDE_RIGHT,
} e_dada_gamechar_via;



typedef struct _dada_gamechar
{
	t_dadaitem	r_it;		///< Common properties of dada items

	t_pt			speed;
	t_pt			accel;
	
	t_llll			*music;

    long            type;           // one of the #e_dada_gamechar_types
	long			state;          // one of the #e_dada_gamechar_states
	long			abilities;      // a combination of #e_dada_gamechar_abilities
	char			direction;
	
	long			how_dies;	  // one of the #e_dada_gamechar_via
	long			how_kills;	  // one of the #e_dada_gamechar_via
	
    double          physics_ext[4]; // left, right, top and bottom extensions
    
	double			points; // it's the character's score, however we don't name it "score" to avoid confusion with musical scores
	long			vp;		// current number of victory points

    t_llll          *kill_sequence;          // List of actions to do when character is killed or eaten
	t_llll			*resurrectpositions;	// List of (x, y) coordinates for resuming game
	
	// all sprites refer to the right
	t_symbol		*sprite_idle;
	t_symbol		*sprite_walk;
	t_symbol		*sprite_jump;
	t_symbol		*sprite_fly;
    t_symbol		*sprite_glide;
	t_symbol		*sprite_dead;
    
    t_symbol		*bullet_gamechar;

    t_symbol    *prototype_dummy_for_attr; ///< Dummy field for prototype attribute linkage (unused: only referred via setter/getter)

    // internal: no attributes
    char			forced_hdirection;
	char			forced_vdirection; 
	char			on_ground; //< Character has feet on the ground
    t_dadaitem      *generated_from;
    t_dada_portal   *portal;
    long            generation_or_portal_direction;
} t_dada_gamechar;





typedef char (*dadaitem_itertypefn)(t_dadaobj *r_ob, t_dadaitem_class *cl, void *data);
typedef char (*dadaitem_iterfn)(t_dadaobj *r_ob, t_dadaitem *item, void *data);


//// DADA ITEMS
void dadaitem_init(t_dadaobj *r_ob, t_dadaitem *item, e_dadaitem_types type, long flags, char must_assign_ID, long forced_ID);

void dadaitem_append_flags_to_llll(t_llll *ll, t_dadaitem *item, char even_if_flags_are_0);
void dadaitem_popup_change_flag_fn(t_dadaobj *r_ob, t_symbol *label, const t_llll *address);
long dadaitem_get_flags_from_llll(t_llll *ll, char *need_check_solos);
void dadaitem_set_flags_from_llllelem(t_dadaobj *r_ob, t_llllelem *elem, t_dadaitem *item, char also_update_solos);
void dadaitem_set_flags_from_llll(t_dadaobj *r_ob, t_llll *ll, t_dadaitem *item, char also_update_solos);
char dadaitem_should_be_played(t_dadaobj *r_ob, t_dadaitem *item);
void dadaobj_update_solos(t_dadaobj *r_ob);
void popup_unset_flags_for_all_dadaitems_fn(t_dadaobj *r_ob, t_symbol *label, const t_llll *address);

/// dadaitem classes
void dadaobj_dadaitem_class_alloc(t_dadaobj *r_ob, e_dadaitem_types type, t_symbol *name, t_symbol *label, 
								  e_dadaitem_alloc_type alloc_type, long parent_class_id, char elements_have_ID,
								  long element_size, long structure_offset, long max_num_items, long *num_items_field,
								  e_dada_func_types data_set_type, method data_set_fn, t_llll *data_set_args,
								  e_dada_func_types data_get_type, method data_get_fn, t_llll *data_get_args,
								  method postprocess_fn, method identifier_to_dadaitem_fn, method free_fn, char selectable, char include_in_background);
void dadaobj_dadaitem_class_ezalloc(t_dadaobj *r_ob, e_dadaitem_types type, t_symbol *name, t_symbol *label, 
									e_dadaitem_alloc_type alloc_type, long parent_class_id, char elements_have_ID,
									long element_size, long structure_offset, long max_num_items, long *num_items_field,
									method postprocess_fn, method free_fn, char selectable, char include_in_background);
void dadaobj_dadaitem_class_add_single_set_get_func(t_dadaobj *r_ob, e_dadaitem_types type,
													e_dada_func_types data_single_set_type, method data_single_set_fn, t_llll *data_single_set_args,
													e_dada_func_types data_single_get_type, method data_single_get_fn, t_llll *data_single_get_args);


long dadaitem_class_get_id(t_item_class_manager *man, e_dadaitem_types type);
t_symbol *dadaitem_class_get_label(t_item_class_manager *man, e_dadaitem_types type);
e_dadaitem_types dadaitem_class_name_to_type(t_item_class_manager *man, t_symbol *name);
t_dadaitem *dadaitem_class_get_nth_item(t_dadaobj *r_ob, long class_id, long n);
long dadaitem_class_get_num_items(t_item_class_manager *man, e_dadaitem_types type);
long dadaitem_class_get_num_items_from_id(t_item_class_manager *man, long classid);
void dadaitem_class_clear(t_dadaobj *r_ob, t_item_class_manager *class_man, t_interface_manager *interface_man, t_undo_manager *undo_man, e_dadaitem_types type, long flags);
void dadaobj_dadaitem_class_clear(t_dadaobj *r_ob, e_dadaitem_types type, long flags);
char dadaitem_class_get_dirty(t_item_class_manager *man, e_dadaitem_types type);
void dada_class_clean_all_dirty(t_item_class_manager *man);
void dadaobj_clean_all_dirty(t_dadaobj *r_ob);
void postprocess_for_dadaitem_class(t_dadaobj *r_ob, long class_id);



/// generic functions
long dadaitem_add(t_dadaobj *r_ob, e_dadaitem_types type, t_pt coord, double height, double width, t_jrgba color, t_symbol *name, long item_flags, char flags, long forced_id = 0);
char dadaitem_delete(t_dadaobj *r_ob, e_dadaitem_types type, long item_idx, char flags);
char dadaitem_delete_direct(t_dadaobj *r_ob, t_dadaitem *item, char flags);
long dadaitem_duplicate(t_dadaobj *r_ob, e_dadaitem_types type, long idx, char flags);
void dadaitem_move(t_dadaobj *r_ob, t_dadaitem *item, t_pt new_coord, char flags);
void dadaitem_move_delta(t_dadaobj *r_ob, t_dadaitem *item, t_pt delta_coord, char flags);
void dadaitem_set_color(t_dadaobj *r_ob, t_dadaitem *item, t_jrgba new_color, char flags);
void dadaitem_change_hue_and_lightness(t_dadaobj *r_ob, t_dadaitem *item, 
									   double delta_hue, double delta_lightness,
									   double min_lightness, double max_lightness, char flags);
t_rect dadaitem_get_rect_baricentric(t_dadaitem *item);
t_rect dadaitem_get_rect_boundingbox(t_dadaitem *item);
char dadaitem_is_pt_in_rect(t_dadaitem *item, t_pt pt);
char dadaitem_is_pt_in_rect_tolerance(t_dadaitem *item, t_pt pt, double tolerance);


// dada balls functions
void dadaitem_ball_clear(t_dadaobj *r_ob, char flags);
long dadaitem_ball_add(t_dadaobj *r_ob, t_pt coord, t_pt speed, t_jrgba color, long channel, long item_flags, char flags);
char dadaitem_ball_delete(t_dadaobj *r_ob, long idx, char flags);
long dadaitem_ball_duplicate(t_dadaobj *r_ob, long idx, char flags);
void dadaitem_ball_move(t_dadaobj *r_ob, long idx, t_pt new_coord, char flags);
void dadaitem_ball_move_delta(t_dadaobj *r_ob, long idx, t_pt delta_coord, char flags);
void dadaitem_ball_set_channel(t_dadaobj *r_ob, long idx, long new_channel, char flags);
void dadaitem_ball_set_color(t_dadaobj *r_ob, long idx, t_jrgba new_color, char flags);
void dadaitem_ball_change_hue_and_lightness(t_dadaobj *r_ob, long idx, 
												 double delta_hue, double delta_lightness,
												 double min_lightness, double max_lightness, char flags);
void dadaitem_ball_speed_scale(t_dadaobj *r_ob, long idx, double factor, char flags);
void dadaitem_ball_speed_rotate(t_dadaobj *r_ob, long idx, double angle, char flags);
void dadaitem_ball_speed_set_angle(t_dadaobj *r_ob, long idx, double angle, char flags);
long dadaitem_ball_find_max_channel(t_dadaobj *r_ob);


// dada card functions
void dadaitem_card_clear(t_dadaobj *r_ob, char flags);
long dadaitem_card_add(t_dadaobj *r_ob, t_pt coord, double width, double height, t_jrgba color, t_symbol *text, t_symbol *icon_path, double value, long item_flags, char flags);
char dadaitem_card_delete(t_dadaobj *r_ob, long idx, char flags);
void dadaitem_card_move(t_dadaobj *r_ob, long idx, t_pt new_coord, char flags);
void dadaitem_card_move_delta(t_dadaobj *r_ob, long idx, t_pt delta_coord, char flags);
t_rect dadaitem_card_get_rect(t_dadaobj *r_ob, t_dada_card *card);
void dadaitem_card_change_value_delta(t_dadaobj *r_ob, long idx, double delta_val, char flags);

// dada block functions
void dadaitem_block_free(t_dadaobj *r_ob, t_dadaitem *item);
void dadaitem_block_clear(t_dadaobj *r_ob, char flags);
long dadaitem_block_add(t_dadaobj *r_ob, t_pt coord, double width, double height, t_jrgba color, t_symbol *name, char solid, long how_bumpeable, long state, t_symbol *sprite, t_symbol *break_sprite, double points, t_llll *music, t_llll *hit_sequence, char loop_hit_sequence, long item_flags, char flags);
char dadaitem_block_delete(t_dadaobj *r_ob, long idx, char flags);

// dada coin functions
void dadaitem_coin_free(t_dadaobj *r_ob, t_dadaitem *item);
void dadaitem_coin_clear(t_dadaobj *r_ob, char flags);
long dadaitem_coin_add(t_dadaobj *r_ob, t_pt coord, double width, double height, t_jrgba color, t_symbol *name, 
					   char takable, char taken, t_symbol *type, double points, long vp, t_llll *music, long item_flags, char flags);
char dadaitem_coin_delete(t_dadaobj *r_ob, long idx, char flags);

// dada portal functions
void dadaitem_portal_free(t_dadaobj *r_ob, t_dadaitem *item);
void dadaitem_portal_clear(t_dadaobj *r_ob, char flags);
long dadaitem_portal_add(t_dadaobj *r_ob, t_pt coord, double width, double height, t_jrgba color, t_symbol *name, t_symbol *sprite,
                         char open, long enter_via, long exit_via, t_llll *enter_sequence, t_llll *exit_sequence, t_llll *music, char hero_only, long item_flags, char flags);
char dadaitem_portal_delete(t_dadaobj *r_ob, long idx, char flags);

// dada gamechar functions
void dadaitem_gamechar_free(t_dadaobj *r_ob, t_dadaitem *item);
void dadaitem_gamechar_clear(t_dadaobj *r_ob, char flags);
long dadaitem_gamechar_add(t_dadaobj *r_ob, t_pt coord, double width, double height, t_jrgba color, 
						   t_pt speed, t_symbol *name, long type, double points, long vp, 
						   long state, long state_ability, long how_dies, long how_kills, char direction, t_llll *music, 
						   t_symbol *idle_sprite, t_symbol *walk_sprite, t_symbol *jump_sprite, t_symbol *fly_sprite,
                           t_symbol *glide_sprite, t_symbol *dead_sprite, t_symbol *bullet_gamechar,
						   t_llll *resurrectpositions, t_llll *kill_sequence, double *physics_ext, long item_flags, char flags);
char dadaitem_gamechar_delete(t_dadaobj *r_ob, long idx, char flags);

t_llll *dadaitem_gamechar_ability_to_llll(long ability);
long dadaitem_gamechar_llll_to_ability(t_llll *ll);
long dadaitem_gamechar_llllelem_to_ability(t_llllelem *elem);

t_llll *dadaitem_gamechar_state_to_llll(long state);
long dadaitem_gamechar_llll_to_state(t_llll *ll);
long dadaitem_gamechar_llllelem_to_state(t_llllelem *elem);

t_llll *dadaitem_gamechar_via_to_llll(long state);
long dadaitem_llll_to_via(t_llll *ll);
long dadaitem_gamechar_llllelem_to_via(t_llllelem *elem);

long dadaitem_gamechar_symbol_to_type(t_symbol *sym);
t_symbol *dadaitem_gamechar_type_to_symbol(long type);



t_dadaitem *dadaitem_from_identifier(t_dadaobj *r_ob, t_dadaitem_identifier *identifier);
t_dadaitem *dadaitem_from_type_and_idx(t_dadaobj *r_ob, e_dadaitem_types type, long idx);
long dadaitem_get_index(t_dadaobj *r_ob, t_dadaitem *item);

t_dadaitem *pixel_to_dadaitem(t_dadaobj *r_ob, t_pt pt, t_object *view, long modifiers, t_pt *coordinates, double selection_pad, t_dadaitem_identifier *identifier);


// iterators
void dadaobj_dadaitem_iterate_for_class(t_dadaobj *r_ob, e_dadaitem_types class_type, dadaitem_iterfn iterfn, void *data);
void dadaobj_dadaitem_iterate_all_extended(t_dadaobj *r_ob, dadaitem_itertypefn itertypefn, void *data1, dadaitem_iterfn iterfn, void *data2);
void dadaobj_dadaitem_iterate_all(t_dadaobj *r_ob, dadaitem_iterfn iterfn, void *data);
void dadaobj_dadaitem_iterate_all_selectable(t_dadaobj *r_ob, dadaitem_iterfn iterfn, void *data);



// selection mechanism
void dadaobj_selection_select_item(t_dadaobj *r_ob, t_dadaitem *item, e_selection_modes mode);
void dadaobj_selection_preselect_item(t_dadaobj *r_ob, t_dadaitem *item, e_selection_modes mode);
void dadaobj_selection_clear_selection(t_dadaobj *r_ob);
void dadaobj_selection_clear_preselection(t_dadaobj *r_ob);
void dadaobj_selection_move_preselection_to_selection(t_dadaobj *r_ob, e_selection_modes mode);
void dadaobj_selection_preselect_items_in_rectangle(t_dadaobj *r_ob, t_object *view, t_rect coord);
void dadaobj_selection_iterate(t_dadaobj *r_ob, dadaitem_iterfn iterfn, void *data);
void dadaobj_selection_force_rebuild_llll(t_dadaobj *r_ob);
void dadaobj_preselection_force_rebuild_llll(t_dadaobj *r_ob);
char dadaobj_selection_contains_type(t_dadaobj *r_ob, e_dadaitem_types type);
void dadaobj_selection_move_delta(t_dadaobj *r_ob, t_pt delta_coord, char flags);
void dadaobj_selection_delete(t_dadaobj *r_ob, char flags);
void dadaobj_selection_select_all(t_dadaobj *r_ob);
void dadaobj_selection_duplicate(t_dadaobj *r_ob, char flags);

char dadaitem_is_preselected(t_dadaitem *it);
char dadaitem_is_selected(t_dadaitem *it);
char dadaitem_is_preselected_xor_selected(t_dadaitem *it);
char dadaitem_is_selectable(t_dadaobj *r_ob, t_dadaitem *it);
char dadaitem_is_in_background(t_dadaobj *r_ob, t_dadaitem *it);


// IDs and names
t_dadaitem *dadaitem_get_from_ID(t_dadaobj *r_ob, long ID);
t_dadaitem *dadaitem_get_from_name(t_dadaobj *r_ob, t_symbol *name);
t_llll *dadaitem_get_all_from_name(t_dadaobj *r_ob, t_symbol *name);
long dadaitem_get_ID_from_name(t_dadaobj *r_ob, t_symbol *name);

// attributes
long dada_default_attr_inactive(t_object *ob, void *elem, t_bach_attribute *attr);
void dada_default_get_bach_attr(t_object *ob, void *obj, t_bach_attribute *attr, long *ac, t_atom **av);
void dada_default_set_bach_attr(t_object *ob, void *obj, t_bach_attribute *attr, long ac, t_atom *av);
void dada_default_attr_postprocess(t_bach_inspector_manager *man, void *elem, t_bach_attribute *attr);
void dada_default_attr_preprocess(t_bach_inspector_manager *man, void *elem, t_bach_attribute *attr);
t_llll *dadaitem_get_attr_as_llll(t_dadaobj *r_ob, t_dadaitem *item, t_bach_attribute *attr);
t_llll *dadaitem_get_as_llll(t_dadaobj *r_ob, t_dadaitem *item);
t_llll *dadaitem_class_get_as_llll(t_dadaobj *r_ob, e_dadaitem_types type);

// IDs
t_dadaitem *dadaitem_get_from_ID(t_dadaobj *r_ob, long ID);


// for undo:
t_llll *dadaitem_get_as_llll_ID(t_dadaobj *r_ob, long ID);
void dadaitem_set_from_llll_ID(t_dadaobj *r_ob, long ID, t_llll *ll);
void dadaitem_add_with_ID(t_dadaobj *r_ob, e_dadaitem_types type, long ID);
void dadaitem_delete_from_ID(t_dadaobj *r_ob, e_dadaitem_types type, long ID);

void dadaitem_set_attr_from_llll(t_dadaobj *r_ob, t_dadaitem *item, t_bach_attribute *attr, t_llll *ll, char ll_has_symbol_router);
void dadaitem_set_from_llll(t_dadaobj *r_ob, t_dadaitem *item, t_llll *ll, long flags);

t_dadaitem *dadaitem_add_from_llll(t_dadaobj *r_ob, e_dadaitem_types type, t_llll *ll, long flags);

void dadaitem_class_set_from_llll(t_dadaobj *r_ob, e_dadaitem_types type, t_llll *ll, long flags);
void dadaitem_set_from_message(t_dadaobj *r_ob, t_llll *message, long flags);
t_dadaitem *dadaitem_add_from_message(t_dadaobj *r_ob, t_llll *message, long flags);
void dadaitem_delete_from_message(t_dadaobj *r_ob, t_llll *message, long flags);
t_bach_attribute *get_dada_attribute(t_dadaobj *r_ob, e_dadaitem_types elemtype, t_symbol *name);


#endif // _DADA_ITEMS_H_
