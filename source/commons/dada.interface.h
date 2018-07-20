/**
	@file
	dada.interface.h
	Interface utilities header for dada library
 
	by Daniele Ghisi
 */


#ifndef _DADA_INTERFACE_H_
#define _DADA_INTERFACE_H_

#include "dada.commons.h"

#define DADA_MIN_ZOOM_PERC  1
#define DADA_MAX_ZOOM_PERC  1000
#define DADA_FINER_FROM_KEYBOARD	0.04


/** Dada selection modes; more precisely: way of merging the preselection with the selection. */
typedef enum _dada_selection_modes {
	DADA_SELECTION_MODE_INVOLUTIVE = 0,			///< If a preselected item is reselected, it'll be unselected (default, used almost everywhere in the interface)
	DADA_SELECTION_MODE_FORCE_SELECT = 1,		///< If a preselected item is reselected, it just stays selected (all objects in the preselection are FORCED to be selected)
	DADA_SELECTION_MODE_FORCE_UNSELECT = -1,	///< If a NON-preselected item is selected, it'll just stays UNselected (all objects in the preselection are FORCED to be unselected)
} e_dada_selection_modes;


///////// INTERFACE FUNCTIONS
// these all return 1 if some action has been intercepted, 0 otherwise 
char dadaobj_focusgained(t_dadaobj *r_ob, t_object *patcherview);
char dadaobj_focuslost(t_dadaobj *r_ob, t_object *patcherview);
char dadaobj_mouseenter(t_dadaobj *r_ob, t_object *patcherview, t_pt pt, long modifiers);
char dadaobj_mouseleave(t_dadaobj *r_ob, t_object *patcherview, t_pt pt, long modifiers);
char dadaobj_mousewheel(t_dadaobj *r_ob, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc);
char dadaobj_mousedrag(t_dadaobj *r_ob, t_object *patcherview, t_pt pt, long modifiers);
char dadaobj_mouseup(t_dadaobj *r_ob, t_object *patcherview, t_pt pt, long modifiers);
char dadaobj_mousedown(t_dadaobj *r_ob, t_object *patcherview, t_pt pt, long modifiers);
char dadaobj_mousemove(t_dadaobj *r_ob, t_object *patcherview, t_pt pt, long modifiers);
char dadaobj_key(t_dadaobj *r_ob, t_object *patcherview, long keycode, long modifiers, long textcharacter);
char dadaobj_keyup(t_dadaobj *r_ob, t_object *patcherview, long keycode, long modifiers, long textcharacter);
void dadaobj_anything(t_dadaobj *r_ob, t_symbol *msg, long ac, t_atom *av);

void drag_coord(t_dadaobj *r_ob, t_pt *coord, t_pt new_coord, char snap_to_grid);
void drag_coord_delta(t_dadaobj *r_ob, t_pt *delta_coord, char snap_to_grid);


/// TOOLS
void dada_set_tool(t_dadaobj *r_ob, t_tool_manager *man, char tool, t_object *patcherview, t_pt pix, long modifiers);
void dadaobj_set_tool(t_dadaobj *r_ob, char tool, t_object *patcherview, t_pt pix, long modifiers);

// GRAPHIC STUFF
void reset_zoom(t_dadaobj *o);
void reset_center_offset(t_dadaobj *o);

/// POPUP
void popup_center_view(t_dadaobj *o, t_symbol *label, const t_llll *address);
void popup_reset_zoom(t_dadaobj *o, t_symbol *label, const t_llll *address);


// PRESETS
void dadaobj_begin_preset(t_dadaobj *r_ob, t_symbol *s, long argc, t_atom *argv);
void dadaobj_restore_preset(t_dadaobj *r_ob, t_symbol *s, long argc, t_atom *argv);
void dadaobj_end_preset(t_dadaobj *r_ob);
void dadaobj_preset(t_dadaobj *r_ob);

// DOMAIN AND RANGE, center offset
void dadaobj_getrange(t_dadaobj *r_ob, t_object *view, double *min, double *max, t_dada_force_graphics *force_graphics);
void dadaobj_getdomain(t_dadaobj *r_ob, t_object *view, double *min, double *max, t_dada_force_graphics *force_graphics);
void dadaobj_setrange(t_dadaobj *r_ob, t_object *view, double min, double max);
void dadaobj_setdomain_start(t_dadaobj *r_ob, t_object *view, double start);
void dadaobj_setrange_start(t_dadaobj *r_ob, t_object *view, double start);
void dadaobj_setdomain(t_dadaobj *r_ob, t_object *view, double min, double max);
void dadaobj_setcenteroffset(t_dadaobj *r_ob, t_pt new_center_offset);
void dadaobj_setzoom(t_dadaobj *r_ob, t_pt new_zoom);
void dadaobj_setvzoom(t_dadaobj *r_ob, double zoom);
void dadaobj_sethzoom(t_dadaobj *r_ob, double zoom);
t_pt dadaobj_coord_to_01_coord(t_dadaobj *r_ob, t_object *view, t_pt coord);

// MULTITOUCH AND MIRA
void dadaobj_jbox_mt(t_dadaobj_jbox *x, t_symbol *s, long argc, t_atom *argv);


////////// GRID FUNCTIONS
void snap_coord_to_grid(t_dadaobj *r_ob, t_pt *coord);
void paint_grid(t_dadaobj *r_ob, t_jgraphics *g, t_rect rect, t_pt center);


#endif // _DADA_INTERFACE_H_
