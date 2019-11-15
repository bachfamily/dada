/**
	@file
	dada.interface.c
	Interface utilities for dada library

	by Daniele Ghisi
*/

#include "dada.interface.h"
#include "dada.popupmenu.h"
#include "dada.undo.h"

void dadaobj_anything(t_dadaobj *r_ob, t_symbol *msg, long ac, t_atom *av) 
{
	r_ob->curr_change_is_from_message = true;
}

char dadaobj_mousemove(t_dadaobj *r_ob, t_object *patcherview, t_pt pt, long modifiers)
{
	if (r_ob->m_interface.allow_mouse_hover) {
		r_ob->m_interface.mousemove_pix = pt;
		r_ob->m_interface.mousemove_coord = pix_to_coord_from_view(r_ob, patcherview, pt);
		r_ob->m_interface.has_been_dragged = 0;
		
		if (!r_ob->m_interface.mouse_is_down) {
			if (r_ob->m_interface.pixel_to_dadaitem)
				r_ob->m_interface.mousemove_item = (t_dadaitem *)(r_ob->m_interface.pixel_to_dadaitem)(r_ob, pt, patcherview, modifiers, &r_ob->m_interface.mousemove_coord, 0., &r_ob->m_interface.mousemove_item_identifier);
			else
				r_ob->m_interface.mousemove_item = pixel_to_dadaitem(r_ob, pt, patcherview, modifiers, &r_ob->m_interface.mousemove_coord, 0., &r_ob->m_interface.mousemove_item_identifier);
		}
        
        if (r_ob->m_interface.mousemove_item && dadaitem_is_in_background(r_ob, r_ob->m_interface.mousemove_item)) {
            r_ob->m_interface.mousemove_item = NULL;
            r_ob->m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
            r_ob->m_interface.mousemove_item_identifier.idx = 0;
        }
		
		if (r_ob->m_tools.curr_tool == DADA_TOOL_ZOOM) {
			dada_set_cursor(r_ob, patcherview, BACH_CURSOR_SCALE);
			return 1;
		} else if (r_ob->m_tools.curr_tool == DADA_TOOL_MOVE_CENTER) {
			dada_set_cursor(r_ob, patcherview, BACH_CURSOR_DRAGGINGHAND);
			return 1;
		}
	}

	return 0;
}



char dadaobj_mousedown(t_dadaobj *r_ob, t_object *patcherview, t_pt pt, long modifiers)
{
	r_ob->curr_change_is_from_message = false;

	r_ob->m_interface.has_been_dragged = 0;
    r_ob->m_interface.has_been_modified_while_mousedown = 0;
	r_ob->m_interface.mouse_is_down = 1;
	r_ob->m_interface.main_drag_direction = 0;
	
	r_ob->m_interface.mousedown_pix = r_ob->m_interface.mousedrag_pix = r_ob->m_interface.mousemove_pix = pt;
	
	if (r_ob->m_interface.pixel_to_dadaitem)
		r_ob->m_interface.mousedown_item = (t_dadaitem *)(r_ob->m_interface.pixel_to_dadaitem)(r_ob, pt, patcherview, modifiers, &r_ob->m_interface.mousedown_coord, 0., &r_ob->m_interface.mousedown_item_identifier);
	else
		r_ob->m_interface.mousedown_item = pixel_to_dadaitem(r_ob, pt, patcherview, modifiers, &r_ob->m_interface.mousedown_coord, 0., &r_ob->m_interface.mousedown_item_identifier);
	
    r_ob->m_interface.last_mousedown_item = r_ob->m_interface.mousedown_item;
    
	if (r_ob->flags & DADAOBJ_SELECTION && !(modifiers & eCommandKey) && !(modifiers & ePopupMenu)) {
		if (r_ob->m_tools.curr_tool == DADA_TOOL_SELECT && 
			(!r_ob->m_interface.mousedown_item || r_ob->m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_NONE || dadaitem_is_in_background(r_ob, r_ob->m_interface.mousedown_item)))
			dada_set_cursor(r_ob, patcherview, BACH_CURSOR_CROSSHAIR);
		
		dadaobj_selection_clear_preselection(r_ob);
		if (!(modifiers & eShiftKey) && !(r_ob->m_interface.mousedown_item && r_ob->m_interface.mousedown_item->selected))
			dadaobj_selection_clear_selection(r_ob);
		
		if (r_ob->m_interface.mousedown_item && dadaitem_is_selectable(r_ob, r_ob->m_interface.mousedown_item)) {
            dadaobj_selection_select_item(r_ob, r_ob->m_interface.mousedown_item, (modifiers & eShiftKey) ? k_SELECTION_MODE_INVOLUTIVE : k_SELECTION_MODE_FORCE_SELECT);
		}
		
        dadaobj_invalidate_and_redraw(r_ob);
		return 1;
	}

	return 0;
}	


char dadaobj_mouseup(t_dadaobj *r_ob, t_object *patcherview, t_pt pt, long modifiers)
{
	r_ob->m_interface.mouse_is_down = 0;
	
    dadaobj_add_undo_marker_if_needed(r_ob);

	if (r_ob->flags & DADAOBJ_SELECTION) {
		dadaobj_selection_move_preselection_to_selection(r_ob, k_SELECTION_MODE_INVOLUTIVE);
		jbox_redraw((t_jbox *)r_ob->orig_obj);
	}

//	if (r_ob->m_interface.has_been_dragged)
//		move_preselected_items_to_selection(r_ob);
	
	if (popup_menu_is_shown((t_dadaobj *)r_ob)) 
		return 1; // when popup is shown, we don't need to continue analyzing mouseup behavior

    if (r_ob->flags & DADAOBJ_INSPECTOR)
        dada_inspector_resync_with_selection(r_ob);
    
	dadaobj_clean_all_dirty(r_ob);
	
	r_ob->m_interface.mousedown_item = NULL;
	r_ob->m_interface.mousedown_item_identifier.type = DADAITEM_TYPE_NONE;
	
	return 0;
}


char dadaobj_mousedrag(t_dadaobj *r_ob, t_object *patcherview, t_pt pt, long modifiers)
{
    r_ob->curr_change_is_from_message = false;
    
	r_ob->m_interface.mousedrag_delta_pix = pt_pt_diff(pt, r_ob->m_interface.mousedrag_pix);
	r_ob->m_interface.mousedrag_pix = pt;
	r_ob->m_interface.mousedrag_coord = pix_to_coord_from_view(r_ob, patcherview, pt);
	r_ob->m_interface.mousedrag_delta_coord = delta_pix_to_delta_coord(r_ob, r_ob->m_interface.mousedrag_delta_pix);
	
    
	if (!r_ob->m_interface.has_been_dragged) {
		if ((r_ob->m_interface.mousedown_item || r_ob->m_interface.mousedown_item_identifier.type != DADAITEM_TYPE_NONE))
			if (modifiers & eShiftKey) // choosing "main" direction
				r_ob->m_interface.main_drag_direction = (fabs(r_ob->m_interface.mousedrag_delta_pix.x) > fabs(r_ob->m_interface.mousedrag_delta_pix.y) ? 1 : -1);
		r_ob->m_interface.has_been_dragged = 1;
	}

	if (r_ob->flags & DADAOBJ_CENTEROFFSET && r_ob->m_zoom.allow_center_shifting && (modifiers == eControlKey + eAltKey || r_ob->m_tools.curr_tool == DADA_TOOL_MOVE_CENTER)) {
		dada_set_cursor(r_ob, patcherview, BACH_CURSOR_DRAGGINGHAND);
		double vals[2];
		vals[0] = r_ob->m_zoom.center_offset.x;
		vals[1] = r_ob->m_zoom.center_offset.y;
		t_pt new_center_offset = pt_pt_sum(r_ob->m_zoom.center_offset, 
										   build_pt(r_ob->m_interface.mousedrag_delta_pix.x / r_ob->m_zoom.zoom.x, -r_ob->m_interface.mousedrag_delta_pix.y / r_ob->m_zoom.zoom.y));
		if (r_ob->flags & DADAOBJ_CENTEROFFSETX)
			vals[0] = new_center_offset.x;
		if (r_ob->flags & DADAOBJ_CENTEROFFSETX)
			vals[1] = new_center_offset.y;
 
        dadaobj_setcenteroffset(r_ob, build_pt(vals[0], vals[1]));
        dadaobj_invalidate_and_redraw(r_ob);
		return 1;
	} else if (r_ob->flags & DADAOBJ_ZOOM && r_ob->m_zoom.allow_zoom && r_ob->m_tools.curr_tool == DADA_TOOL_ZOOM) {
		dada_set_cursor(r_ob, patcherview, BACH_CURSOR_SCALE);
		
		if (r_ob->flags & DADAOBJ_SPLITXYZOOM) {
			double y_inc = -r_ob->m_interface.mousedrag_delta_pix.y/100.;
			double new_zoom_y_perc = r_ob->m_zoom.zoom_y_perc - 100 * y_inc * 3 * (modifiers & eShiftKey ? DADA_FINER_FROM_KEYBOARD : 1.);
			new_zoom_y_perc = CLAMP(new_zoom_y_perc, DADA_MIN_ZOOM_PERC, DADA_MAX_ZOOM_PERC);
            dadaobj_setvzoom(r_ob, new_zoom_y_perc);

			double x_inc = -r_ob->m_interface.mousedrag_delta_pix.x/100.;
			double new_zoom_x_perc = r_ob->m_zoom.zoom_perc - 100 * x_inc * 3 * (modifiers & eShiftKey ? DADA_FINER_FROM_KEYBOARD : 1.);
			new_zoom_x_perc = CLAMP(new_zoom_x_perc, DADA_MIN_ZOOM_PERC, DADA_MAX_ZOOM_PERC);
            dadaobj_sethzoom(r_ob, new_zoom_x_perc);
		} else {
			double y_inc = -r_ob->m_interface.mousedrag_delta_pix.y/100.;
			double new_zoom_perc = r_ob->m_zoom.zoom_perc - 100 * y_inc * 3 * (modifiers & eShiftKey ? DADA_FINER_FROM_KEYBOARD : 1.);
			new_zoom_perc = CLAMP(new_zoom_perc, DADA_MIN_ZOOM_PERC, DADA_MAX_ZOOM_PERC);
            dadaobj_sethzoom(r_ob, new_zoom_perc);
		}
        dadaobj_invalidate_and_redraw(r_ob);
		
		return 1;
	} 
	
	if (r_ob->flags & DADAOBJ_SELECTION && r_ob->m_tools.curr_tool == DADA_TOOL_SELECT) {
		dada_set_cursor(r_ob, patcherview, BACH_CURSOR_CROSSHAIR);
		dadaobj_selection_clear_preselection(r_ob);
		dadaobj_selection_preselect_items_in_rectangle(r_ob, patcherview, build_rect(r_ob->m_interface.mousedown_coord.x, 
																					 r_ob->m_interface.mousedown_coord.y, 
																					 r_ob->m_interface.mousedrag_coord.x - r_ob->m_interface.mousedown_coord.x, 
																					 r_ob->m_interface.mousedrag_coord.y - r_ob->m_interface.mousedown_coord.y));
        dadaobj_invalidate_and_redraw(r_ob);
		return 1;
	}
	
	return 0;
}

char dadaobj_mousewheel(t_dadaobj *r_ob, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc)
{
    if (r_ob->flags & DADAOBJ_ZOOM && r_ob->m_zoom.allow_zoom &&
        (modifiers == eCommandKey || modifiers == eCommandKey + eShiftKey ||
         (r_ob->flags & DADAOBJ_SPLITXYZOOM && modifiers == eCommandKey + eShiftKey + eAltKey) ||
         (r_ob->flags & DADAOBJ_SPLITXYZOOM && modifiers == eCommandKey + eAltKey) ||
         r_ob->m_tools.curr_tool == DADA_TOOL_ZOOM)) {
            
            t_pt coord = pix_to_coord_from_view(r_ob, view, pt);
            double zoom_perc = (r_ob->flags & DADAOBJ_SPLITXYZOOM && modifiers & eAltKey) ? r_ob->m_zoom.zoom_y_perc : r_ob->m_zoom.zoom_perc;
            double new_zoom_perc = zoom_perc * exp(-y_inc * 0.01 * (modifiers & eShiftKey ? DADA_FINER_FROM_KEYBOARD : 1.));
           
            if (r_ob->flags & DADAOBJ_SPLITXYZOOM && modifiers & eAltKey)
                dadaobj_setvzoom(r_ob, new_zoom_perc);
            else
                dadaobj_sethzoom(r_ob, new_zoom_perc);
            
            if (r_ob->flags & DADAOBJ_CENTEROFFSET &&  r_ob->m_zoom.allow_center_shifting) {
                // by changing the zoom from zoom_perc to new_zoom_perc, I have shifted the position coord (under which the mouse was)
                t_pt shifted_pt = coord_to_pix_from_view(r_ob, view, coord);
                t_pt delta_pt = pt_pt_diff(shifted_pt, pt);
                t_pt delta_coord = delta_pix_to_delta_coord(r_ob, delta_pt);
                double vals[2];
                vals[0] = r_ob->m_zoom.center_offset.x;
                vals[1] = r_ob->m_zoom.center_offset.y;
                
                if (r_ob->flags & DADAOBJ_CENTEROFFSETX)
                    vals[0] = r_ob->m_zoom.center_offset.x - delta_coord.x;
                if (r_ob->flags & DADAOBJ_CENTEROFFSETY)
                    vals[1] = r_ob->m_zoom.center_offset.y - delta_coord.y;
                
                dadaobj_setcenteroffset(r_ob, build_pt(vals[0], vals[1]));
            }
            
            jbox_redraw((t_jbox *)r_ob->orig_obj);
            return 1;
        } else if (r_ob->flags & DADAOBJ_CENTEROFFSET &&  r_ob->m_zoom.allow_center_shifting &&
                   (modifiers == 0 || r_ob->m_tools.curr_tool == DADA_TOOL_MOVE_CENTER)) {
            double vals[2];
            vals[0] = r_ob->m_zoom.center_offset.x;
            vals[1] = r_ob->m_zoom.center_offset.y;
            
            if (r_ob->flags & DADAOBJ_CENTEROFFSETX)
                vals[0] = r_ob->m_zoom.center_offset.x + 10 * x_inc/r_ob->m_zoom.zoom.x;
            if (r_ob->flags & DADAOBJ_CENTEROFFSETY)
                vals[1] = r_ob->m_zoom.center_offset.y - 10 * y_inc/r_ob->m_zoom.zoom.y;
            
            dadaobj_setcenteroffset(r_ob, build_pt(vals[0], vals[1]));
//            object_attr_setdouble_array(r_ob->orig_obj, gensym("center"), 2, vals);
            return 1;
            
        }
    return 0;
}	


char dadaobj_focusgained(t_dadaobj *r_ob, t_object *patcherview) 
{
	r_ob->m_interface.has_focus = true;
	jbox_redraw((t_jbox *)r_ob->orig_obj);
	return 0;
}

char dadaobj_focuslost(t_dadaobj *r_ob, t_object *patcherview) 
{
	r_ob->m_interface.has_focus = false;
	jbox_redraw((t_jbox *)r_ob->orig_obj);
	return 0;
}

char dadaobj_mouseenter(t_dadaobj *r_ob, t_object *patcherview, t_pt pt, long modifiers) 
{
	r_ob->m_interface.mouse_is_over = true;
	jbox_redraw((t_jbox *)r_ob->orig_obj);
	return 0;
}

char dadaobj_mouseleave(t_dadaobj *r_ob, t_object *patcherview, t_pt pt, long modifiers) 
{
	r_ob->m_interface.mouse_is_over = false;
	jbox_redraw((t_jbox *)r_ob->orig_obj);
	return 0;
}



char dadaobj_keyup(t_dadaobj *r_ob, t_object *patcherview, long keycode, long modifiers, long textcharacter)
{
	if (strchr(r_ob->m_tools.allowed_tools, keycode)) {
		r_ob->m_tools.curr_tool = DADA_TOOL_ARROW;
        if (r_ob->m_tools.mousemove_fn)
            (r_ob->m_tools.mousemove_fn)(r_ob->orig_obj, patcherview, r_ob->m_interface.mousemove_pix, modifiers);
		return 1;
	}
	return 0;
}

char dadaobj_key(t_dadaobj *r_ob, t_object *patcherview, long keycode, long modifiers, long textcharacter)
{
	r_ob->curr_change_is_from_message = false;
	
	if ((r_ob->flags & DADAOBJ_UNDO) && keycode == 'z' && (modifiers & eCommandKey)) {
		undo_redo_perform(r_ob, (modifiers & eShiftKey) ? DADA_REDO : DADA_UNDO);
		return 1;
	}
	
	if ((r_ob->flags & DADAOBJ_INSPECTOR) && keycode == 'i' && (modifiers & eCommandKey)) {
		// open dada inspector
        if (r_ob->m_inspector.inspector_patcher)
            bring_external_inspector_to_front(&r_ob->m_inspector);
        dada_inspector_open(r_ob);
        return 1;
	}
    
    if ((r_ob->flags & DADAOBJ_SELECTION) && keycode == 'a' && (modifiers & eCommandKey)) {
        dadaobj_selection_select_all(r_ob);
        dadaobj_invalidate_and_redraw(r_ob);
        return 1;
    }
    

	if (strchr(r_ob->m_tools.allowed_tools, keycode) && !(modifiers & (eCommandKey | eControlKey)) ) {
		dadaobj_set_tool(r_ob, keycode, patcherview, r_ob->m_interface.mousemove_pix, modifiers);
		return 1;
	} else if (keycode == JKEY_ESC) {
		if (r_ob->flags & DADAOBJ_CENTEROFFSET) 
			reset_center_offset(r_ob);
        reset_zoom(r_ob);
		dadaobj_set_tool(r_ob, DADA_TOOL_ARROW, patcherview, r_ob->m_interface.mousemove_pix, modifiers);
		return 0; // BUT WE PASS THROUGH THE ESC CHARACTER, if the object needs to handle it also for other stuff (e.g. clear selection) 
	}
	return 0;
}


/// TOOLS
void dada_set_tool(t_dadaobj *r_ob, t_tool_manager *man, char tool, t_object *patcherview, t_pt pix, long modifiers)
{
	man->curr_tool = tool;
    if (man->mousemove_fn)
        (man->mousemove_fn)(r_ob->orig_obj, patcherview, pix, modifiers);
}

void dadaobj_set_tool(t_dadaobj *r_ob, char tool, t_object *patcherview, t_pt pix, long modifiers)
{
	dada_set_tool(r_ob, &r_ob->m_tools, tool, patcherview, pix, modifiers);
}


///// STANDARD POPUP INTERFACE FUNCTIONS

void reset_center_offset(t_dadaobj *r_ob)
{
	if (r_ob->m_zoom.allow_center_shifting) {
		double vals[2];
		vals[0] = vals[1] = 0;
        dadaobj_setcenteroffset(r_ob, build_pt(vals[0], vals[1]));
//		object_attr_setdouble_array(r_ob->orig_obj, gensym("center"), 2, vals);
	}
}


void reset_zoom(t_dadaobj *r_ob)
{
	if (r_ob->m_zoom.allow_zoom)
        dadaobj_setzoom(r_ob, build_pt(100, 100));
}


void popup_center_view(t_dadaobj *r_ob, t_symbol *label, const t_llll *address) 
{
	reset_center_offset(r_ob);
}


void popup_reset_zoom(t_dadaobj *r_ob, t_symbol *label, const t_llll *address) 
{
	reset_zoom(r_ob);
}



//// PRESETS 

void dadaobj_begin_preset(t_dadaobj *r_ob, t_symbol *s, long argc, t_atom *argv)
{
	r_ob->preset_ac = atom_getlong(argv) ;
	r_ob->preset_av = (t_atom *)bach_newptr(r_ob->preset_ac * sizeof(t_atom));
}


void dadaobj_restore_preset(t_dadaobj *r_ob, t_symbol *s, long argc, t_atom *argv)
{
	long start, size;
	
	start = atom_getlong(argv);
	size = atom_getlong(argv + 1);
	
	sysmem_copyptr(argv+2, r_ob->preset_av+start, size*sizeof(t_atom));
}

void dadaobj_end_preset(t_dadaobj *r_ob)
{
	object_method_typed(r_ob->orig_obj, NULL, r_ob->preset_ac, r_ob->preset_av, NULL);
	bach_freeptr(r_ob->preset_av);
}

void dadaobj_preset(t_dadaobj *r_ob)
{
	t_atom temp[256];
	void *buf;
	long i, index, size;
	char wrote = false, begin = true, done = false;
	t_object *ob = r_ob->orig_obj;
	
	t_llll *data = ((get_state_fn)(r_ob->get_state))(ob);
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
			atom_setobj(temp, ob);
			atom_setsym(temp + 1, ob_sym(ob));
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
		atom_setobj(temp, ob);
		atom_setsym(temp + 1, ob_sym(ob));
		atom_setsym(temp + 2, gensym("end_preset"));
		binbuf_insert(buf, NULL, 3, temp);
	}
	
	if (av) bach_freeptr(av);
}



//// SET DOMAIN or RANGE


void dadaobj_getdomain(t_dadaobj *r_ob, t_object *view, double *min, double *max, t_dada_force_graphics *force_graphics)
{
    t_rect rect;
    if (view) {
        jbox_get_rect_for_view(r_ob->orig_obj, view, &rect);
        double width_coord = rect.width / r_ob->m_zoom.zoom.x;
        *min = -r_ob->m_zoom.center_offset.x - width_coord/2.;
        *max = -r_ob->m_zoom.center_offset.x + width_coord/2.;
    } else if (force_graphics) {
        rect = force_graphics->rect;
        double width_coord = rect.width / force_graphics->zoom.x;
        *min = -force_graphics->center_offset.x - width_coord/2.;
        *max = -force_graphics->center_offset.x + width_coord/2.;
    } else {
        object_error(r_ob->orig_obj, "Can't get domain!");
    }
}

void dadaobj_getrange(t_dadaobj *r_ob, t_object *view, double *min, double *max, t_dada_force_graphics *force_graphics)
{
    t_rect rect;
    if (view) {
        jbox_get_rect_for_view(r_ob->orig_obj, view, &rect);
        double heigh_coord = rect.height / r_ob->m_zoom.zoom.y;
        *min = -r_ob->m_zoom.center_offset.y - heigh_coord/2.;
        *max = -r_ob->m_zoom.center_offset.y + heigh_coord/2.;
    } else if (force_graphics) {
        rect = force_graphics->rect;
        double heigh_coord = rect.height / force_graphics->zoom.y;
        *min = -force_graphics->center_offset.y - heigh_coord/2.;
        *max = -force_graphics->center_offset.y + heigh_coord/2.;
    } else {
        object_error(r_ob->orig_obj, "Can't get range!");
    }
}


void dadaobj_setdomain(t_dadaobj *r_ob, t_object *view, double min, double max)
{
    t_rect rect;
    jbox_get_rect_for_view(r_ob->orig_obj, view, &rect);

    if (min > max)
        swap_doubles(&min, &max);
    
    if (max == min)
        max += 0.0001;
    
    double xzoom = rect.width/(max - min);
    r_ob->m_zoom.zoom.x = xzoom;
    r_ob->m_zoom.zoom_perc = xzoom * 100 / r_ob->m_zoom.zoom_static_additional.x;

    double vals[2];
    vals[0] = r_ob->m_zoom.center_offset.x;
    vals[1] = r_ob->m_zoom.center_offset.y;
    
    vals[0] = -(min + max)/2.;
    
    dadaobj_setcenteroffset(r_ob, build_pt(vals[0], vals[1]));
    
    r_ob->m_grid.must_update_grid_size = true;
    
    if (!(r_ob->flags & DADAOBJ_SPLITXYZOOM))
        dadaobj_setzoom(r_ob, build_pt(r_ob->m_zoom.zoom_perc, r_ob->m_zoom.zoom_perc)); // re-putting zoom equal both for x and y
}

void dadaobj_setdomain_start(t_dadaobj *r_ob, t_object *view, double start)
{
    double min, max;
    dadaobj_getdomain(r_ob, view, &min, &max, NULL);
    dadaobj_setdomain(r_ob, view, start, max-min);
}

void dadaobj_setrange(t_dadaobj *r_ob, t_object *view, double min, double max)
{
    t_rect rect;
    jbox_get_rect_for_view(r_ob->orig_obj, view, &rect);
    
    if (min > max)
        swap_doubles(&min, &max);
    
    if (max == min)
        max += 0.0001;
    
    double yzoom = rect.height/(max - min);
    r_ob->m_zoom.zoom.y = yzoom;
    r_ob->m_zoom.zoom_y_perc = yzoom * 100 / r_ob->m_zoom.zoom_static_additional.y;
    
    
    double vals[2];
    vals[0] = r_ob->m_zoom.center_offset.x;
    vals[1] = r_ob->m_zoom.center_offset.y;
    
    vals[1] = -(min + max)/2.;
    
    dadaobj_setcenteroffset(r_ob, build_pt(vals[0], vals[1]));

    r_ob->m_grid.must_update_grid_size = true;

    if (!(r_ob->flags & DADAOBJ_SPLITXYZOOM))
        dadaobj_setzoom(r_ob, build_pt(r_ob->m_zoom.zoom_y_perc, r_ob->m_zoom.zoom_y_perc)); // re-putting zoom equal both for x and y
}

void dadaobj_setrange_start(t_dadaobj *r_ob, t_object *view, double start)
{
    double min, max;
    dadaobj_getrange(r_ob, view, &min, &max, NULL);
    dadaobj_setrange(r_ob, view, start, max-min);
}

void dadaobj_setcenteroffset(t_dadaobj *r_ob, t_pt new_center_offset)
{
    double vals[2];
    vals[0] = new_center_offset.x;
    vals[1] = new_center_offset.y;
    
    if (!r_ob->m_paint.dont_repaint)
        object_attr_setdouble_array(r_ob->orig_obj, gensym("center"), 2, vals);
    else
        r_ob->m_zoom.center_offset = build_pt(vals[0], vals[1]);
}


void dadaobj_sethzoom(t_dadaobj *r_ob, double zoom)
{
    if (!r_ob->m_paint.dont_repaint)
        object_attr_setfloat(r_ob->orig_obj, gensym("zoom"), zoom);
    else {
        t_atom av;
        atom_setfloat(&av, zoom);
        dadaobj_setattr_zoom(r_ob, NULL, 1, &av);
    }
}

void dadaobj_setvzoom(t_dadaobj *r_ob, double zoom)
{
    if (!r_ob->m_paint.dont_repaint)
        object_attr_setfloat(r_ob->orig_obj, gensym("vzoom"), zoom);
    else {
        t_atom av;
        atom_setfloat(&av, zoom);
        dadaobj_setattr_vzoom(r_ob, NULL, 1, &av);
    }
}

void dadaobj_setzoom(t_dadaobj *r_ob, t_pt new_zoom)
{
    dadaobj_setvzoom(r_ob, new_zoom.y);
    dadaobj_sethzoom(r_ob, new_zoom.x);
}




t_pt dadaobj_coord_to_01_coord(t_dadaobj *r_ob, t_object *view, t_pt coord)
{
    double dom_min, dom_max, range_min, range_max;
    dadaobj_getdomain(r_ob, view, &dom_min, &dom_max, NULL);
    dadaobj_getrange(r_ob, view, &range_min, &range_max, NULL);
    t_pt res;
    res.x = (coord.x - dom_min)/(dom_max - dom_min);
    res.y = (coord.y - range_min)/(range_max - range_min);
    return res;
}









// also takes into account the drag direction
void drag_coord(t_dadaobj *r_ob, t_pt *coord, t_pt new_coord, char snap_to_grid)
{
	// DRAG DIRECTION
	switch (r_ob->m_interface.main_drag_direction) {
		case 1: // x axis
			coord->x = new_coord.x;
			break;
		case -1: // y axis
			coord->y = new_coord.y;
			break;
		default:
			*coord = new_coord;
			break;
	}

	// GRID
	if (snap_to_grid && r_ob->m_grid.snap_to_grid)
		snap_coord_to_grid(r_ob, coord);
}


// also takes into account the drag direction
void drag_coord_delta(t_dadaobj *r_ob, t_pt *delta_coord, char snap_to_grid)
{
	// DRAG DIRECTION
	switch (r_ob->m_interface.main_drag_direction) {
		case 1: // x axis
			delta_coord->y = 0;
			break;
		case -1: // y axis
			delta_coord->x = 0;
			break;
		default:
			break;
	}

	// GRID will be handled at mouseup
    if (snap_to_grid && r_ob->m_grid.snap_to_grid) {
		t_pt old_delta_coord = *delta_coord;
		snap_coord_to_grid(r_ob, delta_coord);
		t_pt diff_temp = pt_pt_diff(*delta_coord, old_delta_coord);
		t_pt diff = build_pt(diff_temp.x * r_ob->m_zoom.zoom.x, diff_temp.y * r_ob->m_zoom.zoom.y);
		r_ob->m_interface.mousedrag_pix = pt_pt_sum(r_ob->m_interface.mousedrag_pix, build_pt(diff.x, -diff.y));
	} 
}


/// GRIDS

t_pt get_best_grid(t_dadaobj *r_ob, t_object *view)
{
    const double LOG5 = 0.69897;
    double width = 100. / r_ob->m_zoom.zoom.x;
    double height = 100. / r_ob->m_zoom.zoom.y;
    double l10w = log10(width);
    double l10h = log10(height);
    double fl_l10w = floor(l10w);
    double fl_l10h = floor(l10h);
    double step_x = pow(10., fl_l10w)*(l10w - fl_l10w < LOG5 ? 1. : 5.);
    double step_y = pow(10., fl_l10h)*(l10h - fl_l10h < LOG5 ? 1. : 5.);
    return build_pt(step_x, step_y);
}


void dadaobj_update_grid_size(t_dadaobj *r_ob, t_object *view)
{
    if (r_ob->m_grid.grid_mode == 1) {
        r_ob->m_grid.grid_size_curr = get_best_grid(r_ob, view);
    }
}


t_pt dadaobj_get_grid_size(t_dadaobj *r_ob)
{
    if (r_ob->m_grid.grid_mode == 1)
        return r_ob->m_grid.grid_size_curr;
    else
        return r_ob->m_grid.grid_size_fixed;
}

void snap_coord_to_grid(t_dadaobj *r_ob, t_pt *coord)
{
	t_pt grid_size = dadaobj_get_grid_size(r_ob);
	coord->x = round(coord->x / grid_size.x) * grid_size.x;
	coord->y = round(coord->y / grid_size.y) * grid_size.y;
}




/////// MIRA / MIRAWEB INTERACTION


long dadaobj_mt_get_num_fingers_down(t_dadaobj *r_ob)
{
    long res = 0;
    for (long i = 0; i < 10; i++)
        res += (r_ob->m_mt.finger_state[i] > 0);
    return res;
}

void dadaobj_jbox_mt(t_dadaobj_jbox *x, t_symbol *s, long argc, t_atom *argv)
{
    t_dadaobj *r_ob = &x->d_ob;
    t_object *orig_obj = r_ob->orig_obj;
    if (argc) {
        t_object *firstview = jpatcher_get_firstview((t_object *)orig_obj);
        
        //        if (atom_gettype(argv) == A_SYM && atom_getsym(argv) == gensym("region") && argc >= 4) { // region <regionID> <finger> <state> <device>
        //            long finger_id = CLAMP(atom_getlong(argv + 2), 1, 10) - 1;
        //            long state = CLAMP(atom_getlong(argv + 3), 0, 1);
        //            finger_state[finger_id] = state;
        //        } else
        if (atom_gettype(argv) == A_SYM && atom_getsym(argv) == gensym("touch") && argc >= 5) { // touch <x> <y> <finger> <state> <region> <device>
            long finger_id = CLAMP(atom_getlong(argv + 3), 1, 10) - 1;
            long state = CLAMP(atom_getlong(argv + 4), 0, 1);
            t_pt pos = build_pt(atom_getfloat(argv + 1) * r_ob->m_geometry.last_used_view_width_pix, atom_getfloat(argv + 2) * r_ob->m_geometry.last_used_view_height_pix);
            
            //            dev_object_post((t_object *)r_ob, "• Mira finger %ld %s", finger_id + 1, state ? "ON" : "OFF");
            
            if (!r_ob->m_mt.pinching) {
                if (r_ob->m_mt.finger_state[finger_id]) {
                    if (!state) {
                        // finger released
                        method mouseup = object_method_direct_getmethod((t_object *) orig_obj, gensym("mouseup"));
                        if (mouseup) (mouseup)(orig_obj, firstview, pos, 0);
                    } else {
                        // finger dragged
                        method mousedrag = object_method_direct_getmethod((t_object *) orig_obj, gensym("mousedrag"));
                        if (mousedrag) (mousedrag)(orig_obj, firstview, pos, 0);
                    }
                } else {
                    if (!state) {
                        // should not happen, in principle
                    } else {
                        // finger pressed
                        method mousedown = object_method_direct_getmethod((t_object *) orig_obj, gensym("mousedown"));
                        if (mousedown) (mousedown)(orig_obj, firstview, pos, 0);
                    }
                }
            }
            
            r_ob->m_mt.finger_state[finger_id] = state;
            r_ob->m_mt.finger_pos[finger_id] = pos;
            
            if (dadaobj_mt_get_num_fingers_down(r_ob) == 0)
                r_ob->m_mt.pinching = false;
            
            // swipe = scroll
        } else if (atom_gettype(argv) == A_SYM && atom_getsym(argv) == gensym("swipe") && argc >= 2) { // swipe <direction> <device>
            if (r_ob->flags & DADAOBJ_CENTEROFFSET) {
                t_symbol *direction = atom_getsym(argv + 1);
                method mousewheel = object_method_direct_getmethod((t_object *) orig_obj, gensym("mousewheel"));
                if (mousewheel) {
                    if (r_ob->flags & DADAOBJ_CENTEROFFSETX) {
                        if (direction == gensym("left"))
                            (mousewheel)(orig_obj, firstview, r_ob->m_mt.finger_pos[0], 0, -r_ob->m_geometry.last_used_view_width_pix / (10 * r_ob->m_zoom.zoom.x), 0.);
                        else if (direction == gensym("right"))
                            (mousewheel)(orig_obj, firstview, r_ob->m_mt.finger_pos[0], 0, r_ob->m_geometry.last_used_view_width_pix / (10 * r_ob->m_zoom.zoom.x), 0.);
                    }
                    if (r_ob->flags & DADAOBJ_CENTEROFFSETY) {
                        if (direction == gensym("up"))
                            (mousewheel)(orig_obj, firstview, r_ob->m_mt.finger_pos[0], 0, 0., -r_ob->m_geometry.last_used_view_height_pix / (10 * r_ob->m_zoom.zoom.x));
                        else if (direction == gensym("down"))
                            (mousewheel)(orig_obj, firstview, r_ob->m_mt.finger_pos[0], 0, 0., r_ob->m_geometry.last_used_view_height_pix / (10 * r_ob->m_zoom.zoom.x));
                    }
                }
            }
            
            // pinch = change zoom
        } else if (atom_gettype(argv) == A_SYM && atom_getsym(argv) == gensym("pinch") && argc >= 2) { // pinch <change> <velocity> <state> <device>
            if (r_ob->flags & DADAOBJ_ZOOM) {
                double change = atom_getfloat(argv + 1);
                if (!r_ob->m_mt.pinching) {
                    // just started pinching!
                    r_ob->m_mt.zoom_at_pinch_start = r_ob->m_zoom.zoom;
                    r_ob->m_mt.pinching = true;
                }
                object_attr_setfloat((t_object *)orig_obj, gensym("zoom"), r_ob->m_mt.zoom_at_pinch_start.x * change * 100.);
                if (r_ob->flags & DADAOBJ_SPLITXYZOOM)
                    object_attr_setfloat((t_object *)orig_obj, gensym("vzoom"), r_ob->m_mt.zoom_at_pinch_start.y * change * 100.);
                //            method mousewheel = object_method_direct_getmethod((t_object *) r_ob, gensym("mousewheel"));
                //            (mousewheel)(r_ob, firstview, r_ob->mt_finger_pos[0], eCommandKey, 0., 4 * (r_ob->zoom_x - change * r_ob->zoom_x)/CONST_Y_MOUSEWHEEL_FACTOR);
            }
            
            // tap = play/stop
        } else if (atom_gettype(argv) == A_SYM && atom_getsym(argv) == gensym("tap")) { //} && argc >= 3) { // tap <x> <y> <region> <device>
            method key = object_method_direct_getmethod((t_object *) orig_obj, gensym("key"));
            if (key) (key)(orig_obj, firstview, (long)JKEY_SPACEBAR, 0, 32);
        }
    }
}
