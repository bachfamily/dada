/**
	@file
	dada.object.c
	Function to handle a dada object

	by Daniele Ghisi
*/


#include "dada.object.h"
#include "dada.cursors.h"
#include "dada.interface.h"
#include "dada.popupmenu.h"
#include "dada.undo.h"

long dada_check_bach_version()
{
    long min_required_bach_version = 80000;
    bach = (t_bach *) gensym("bach")->s_thing;
    if (!bach) {
        return 1;
    } else if (bach->b_version < min_required_bach_version) {
        return 1;
    }
    return 0;
}

void dada_error_bachcheck()
{
    if (!gensym("bach")->s_thing) {
        error("error: dada needs bach to be installed in order to work (www.bachproject.net).");
    } else {
        char temp[2048];
        snprintf_zero(temp, 2048, "%s", bach_get_current_version_string_verbose());
        if (temp[0]) {
            error("error: dada needs a bach version of at least 0.8.");
            error("   Your bach version is %s. Please upgrade bach.", temp);
        } else {
            error("error: dada needs a bach version of at least 0.8.", temp);
            error("   You have installed an older version. Please upgrade bach.");
        }
    }
}

long parse_version_string(char *str, long *major, long *minor, long *revision, long *maintenance)
{
    long maj = 0, min = 0, rev = 0, maint = 0;
    long count = 0;
    char temp_str[128];
    snprintf_zero(temp_str, 128, "%s", str);
    
    char *pch = strtok(temp_str, ".");
    while (pch != NULL)
    {
        switch (count) {
            case 0: maj = atoi(pch); break;
            case 1: min = atoi(pch); break;
            case 2: rev = atoi(pch); break;
            case 3: maint = atoi(pch); break;
            default: break;
        }
        pch = strtok (NULL, ".");
        count++;
    }
    
    if (major) *major = maj;
    if (minor) *minor = min;
    if (revision) *revision = rev;
    if (maintenance) *maintenance = maint;
    
    return maint + rev * 100 + min * 10000 + maj * 1000000;
}


long dada_get_current_version_number()
{
    char temp[1024];
    snprintf_zero(temp, 1024, "%s", DADA_VERSION);
    return parse_version_string(temp, NULL, NULL, NULL, NULL);
}

void dadaobj_set_version_number(t_dadaobj *d_ob, long version_number)
{
    d_ob->m_version_number = version_number;
}


void dadaobj_set_current_version_number(t_dadaobj *d_ob)
{
    dadaobj_set_version_number(d_ob, dada_get_current_version_number());
}


void dada_atomic_lock(t_dadaobj *r_ob)
{
	t_dada_atomic_lock *lock = &r_ob->l_lock;
	while (ATOMIC_INCREMENT_32(lock) > 1)
		ATOMIC_DECREMENT_BARRIER_32(lock);
}

void dada_atomic_unlock(t_dadaobj *r_ob)
{
	t_dada_atomic_lock *lock = &r_ob->l_lock;
	ATOMIC_DECREMENT_BARRIER(lock);
}

void dada_interface_setup(t_interface_manager *man, long changebang_outlet, long notification_outlet)
{
	man->changebang_out_num = changebang_outlet;
    man->notifications_out_num = notification_outlet;
	man->continuously_send_changebang = false;
	man->send_bang_from_messages = false;
	man->send_bang_upon_undo = true;
	man->mousedown_item = man->mousemove_item = NULL;
	man->mousedown_item_identifier.type = DADAITEM_TYPE_NONE;
	man->mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
	man->selection = llll_get();
	man->preselection = llll_get();
}

void dada_undo_setup(t_undo_manager *man)
{
	man->undo = llll_get();
	man->redo = llll_get();
	man->need_push_marker = NULL;
	man->post_process_fn = NULL;
	man->dirty_items = llll_get();
}

void dada_tools_setup(t_tool_manager *man, const char *tools, long flags)
{
	strncpy_zero(man->allowed_tools, tools, 50);
	man->curr_tool = DADA_TOOL_ARROW;
	
	if ((flags & DADAOBJ_ZOOM) && strlen(man->allowed_tools) < 50 && !strchr(man->allowed_tools, 'z')) {
		long len = strlen(man->allowed_tools);
		man->allowed_tools[len] = 'z';
		man->allowed_tools[len+1] = 0;
	}
	if ((flags & DADAOBJ_CENTEROFFSET) && strlen(man->allowed_tools) < 50 && !strchr(man->allowed_tools, 'x')) {
		long len = strlen(man->allowed_tools);
		man->allowed_tools[len] = 'x';
		man->allowed_tools[len+1] = 0;
	}
}


long get_mousedown_obj_type(void *rob)
{
    t_dadaobj *r_ob = (t_dadaobj *)rob;
    return r_ob->m_interface.mousedown_item ? r_ob->m_interface.mousedown_item->type : NULL;
}

void *get_mousedown_ptr(void *rob)
{
    t_dadaobj *r_ob = (t_dadaobj *)rob;
    return r_ob->m_interface.mousedown_item;
}

long get_mousedown_ptr_index(void *rob)
{
    t_dadaobj *r_ob = (t_dadaobj *)rob;
    return r_ob->m_interface.mousedown_item ? dadaitem_get_index(r_ob, r_ob->m_interface.mousedown_item) : 0;
}

void dadaobj_setup(t_object *ob, t_dadaobj *r_ob, e_llllobj_obj_types llllobj_type, long flags, t_pt zoom_static_additional,
				   long playout_outlet, long changebang_outlet, long notification_outlet, dada_paint_ext_fn paint_ext, invalidate_and_redraw_fn invalidate_and_redraw,
				   const char *tools, 
				   long stores, const char *outlets, ...)
{
    va_list args;
    va_start(args, outlets);
	
	r_ob->orig_obj = ob;
    r_ob->llllobj_type = llllobj_type;
    r_ob->m_paint.paint_ext = paint_ext;
    r_ob->m_paint.invalidate_and_redraw = invalidate_and_redraw;
	
	systhread_mutex_new_debug(&r_ob->l_mutex, 0);
	
	// Object flags
	r_ob->flags = flags;
	
	t_bach_attr_manager *man = r_ob->m_inspector.attr_manager = (t_bach_attr_manager *)bach_newptrclear(sizeof(t_bach_attr_manager));
	initialize_attr_manager(man);

	if (flags & DADAOBJ_INSPECTOR) {
		r_ob->m_inspector.bach_managing = false; // inspector is NOT stanard release bach inspecto
		bach_inspector_ui_classinit();

		r_ob->m_inspector.attr_manager->inspector_header = (bach_inspector_header_fn)dada_default_inspector_header_fn;
		r_ob->m_inspector.attr_manager->inspector_image = (bach_inspector_image_fn)dada_inspector_get_icon_surface_fn;
		r_ob->m_inspector.owner = ob;
        r_ob->m_inspector.thing = r_ob;
        
        r_ob->m_inspector.attr_manager->adapt_image = true;
        r_ob->m_inspector.attr_manager->adapt_image_max_ratio = 2.;
        
        r_ob->m_inspector.get_custom_mousedown_obj_type = get_mousedown_obj_type;
        r_ob->m_inspector.get_custom_mousedown_ptr = get_mousedown_ptr;
        r_ob->m_inspector.get_custom_mousedown_ptr_index = get_mousedown_ptr_index;
	}
		
	r_ob->m_zoom.zoom_perc = 100;
	r_ob->m_zoom.zoom_static_additional = zoom_static_additional;
	r_ob->m_zoom.zoom = zoom_static_additional;
	r_ob->m_zoom.max_zoom_perc = build_pt(DADA_MAX_ZOOM_PERC, DADA_MAX_ZOOM_PERC); 
	r_ob->m_zoom.min_zoom_perc = build_pt(DADA_MIN_ZOOM_PERC, DADA_MIN_ZOOM_PERC); 
	
	// interface
	dada_interface_setup(&r_ob->m_interface, changebang_outlet, notification_outlet);
	
	// Object tools
	dada_tools_setup(&r_ob->m_tools, tools, flags);
	
	// Dadaitem classes
	r_ob->m_classes.num_di_classes = 0;
	
	// clock and play
	r_ob->m_play.play_out_num = playout_outlet;
	r_ob->m_play.has_solos = false;
	
	
	// undo
	dada_undo_setup(&r_ob->m_undo);
	
	initialize_popup_menus(r_ob);
    
    r_ob->m_grid.must_update_grid_size = true;
	
	r_ob->m_cursors.curr_cursor = BACH_CURSOR_DEFAULT;
	load_cursors(r_ob);
	
	// hash table
	r_ob->IDtable = shashtable_new(1);
}

void dadaobj_jbox_setup(t_dadaobj_jbox *b_ob, long flags, t_pt zoom_static_additional,
						long playout_outlet, long changebang_outlet, long notification_outlet, dada_paint_ext_fn paint_ext, invalidate_and_redraw_fn invalidate_and_redraw,
						const char *tools, long stores, const char *outlets, ...)
{
	va_list args;
    va_start(args, outlets);

	llllobj_jbox_setup((t_llllobj_jbox *)b_ob, stores, outlets, args);
	dadaobj_setup((t_object *)b_ob, &b_ob->d_ob, LLLL_OBJ_UI, flags, zoom_static_additional, playout_outlet, changebang_outlet, notification_outlet, paint_ext, invalidate_and_redraw, tools, stores, outlets, args);
}

void dadaobj_pxjbox_setup(t_dadaobj_pxjbox *b_ob, long flags, t_pt zoom_static_additional,
						long playout_outlet, long changebang_outlet, long notification_outlet, dada_paint_ext_fn paint_ext, invalidate_and_redraw_fn invalidate_and_redraw,
						const char *tools, long stores, const char *outlets, ...)
{
	va_list args;
    va_start(args, outlets);
	
	llllobj_pxjbox_setup((t_llllobj_pxjbox *)b_ob, stores, outlets, args);
	dadaobj_setup((t_object *)b_ob, &b_ob->d_ob, LLLL_OBJ_UIMSP, flags, zoom_static_additional, playout_outlet, changebang_outlet, notification_outlet, paint_ext, invalidate_and_redraw, tools, stores, outlets, args);
}

void dadaobj_addfunctions(t_dadaobj *d_ob, dada_mousemove_fn mousemove_fn, method clock_task, method undo_postprocess, 
						  get_state_fn get_state, set_state_fn set_state, pixel_to_dadaitem_fn pixel_to_dadaitem, 
						  preselect_items_in_rectangle_fn preselect_items_in_rectangle, dadanotify_fn dadanotify)
{
	d_ob->m_tools.mousemove_fn = mousemove_fn;
	if (clock_task) {
		d_ob->m_play.setclock = gensym("");
		d_ob->m_play.m_clock = clock_task ? clock_new_debug(d_ob->orig_obj, (method) clock_task) : NULL; 
	} else {
		d_ob->m_play.m_clock = d_ob->m_play.setclock = NULL;
	}
	d_ob->m_undo.post_process_fn = undo_postprocess;
	d_ob->get_state = get_state;
	d_ob->set_state = set_state;
	d_ob->m_interface.pixel_to_dadaitem = pixel_to_dadaitem;
	d_ob->m_interface.preselect_items_in_rectangle = preselect_items_in_rectangle;
	d_ob->dadanotify = dadanotify;
}


void dadaobj_free(t_dadaobj *r_ob)
{
	free_cursors(r_ob);
	free_popup_menus(r_ob);
	
	llll_free(r_ob->m_interface.selection);
	llll_free(r_ob->m_interface.preselection);
	
	// free lllls of allocated class
	long i;
	for (i = 0; i < r_ob->m_classes.num_di_classes; i++) {
        if (r_ob->m_classes.di_class[i].alloc_type == DADA_ITEM_ALLOC_OBJLLLL)
            llll_free(*((t_llll **)(((long)(r_ob->orig_obj)) + r_ob->m_classes.di_class[i].struct_offset)));
		llll_free(r_ob->m_classes.di_class[i].data_get_args);
		llll_free(r_ob->m_classes.di_class[i].data_set_args);
	}
	
	if (r_ob->m_play.m_clock)
		object_free_debug(r_ob->m_play.m_clock);
	
	if (r_ob->flags & DADAOBJ_UNDO) {
		undo_redo_free_all_ticks(&r_ob->m_undo, DADA_UNDO);
		undo_redo_free_all_ticks(&r_ob->m_undo, DADA_REDO);
		llll_free(r_ob->m_undo.undo);
		llll_free(r_ob->m_undo.redo);
		llll_free(r_ob->m_undo.dirty_items);
	}
	
    if (r_ob->m_bg.bg_surface) {
        jgraphics_surface_destroy(r_ob->m_bg.bg_surface);
        r_ob->m_bg.bg_surface = NULL;
    }
    
	if (r_ob->l_mutex)
		systhread_mutex_free_debug(r_ob->l_mutex);
	
	shashtable_free(r_ob->IDtable);
}

void dadaobj_jbox_free(t_dadaobj_jbox *b_ob)
{
	dadaobj_free(&b_ob->d_ob);
    jbox_free(&b_ob->r_ob.l_box);
	llllobj_jbox_free((t_llllobj_jbox *)b_ob);
}

void dadaobj_pxjbox_free(t_dadaobj_pxjbox *b_ob)
{
	dadaobj_free(&b_ob->d_ob);
	llllobj_pxjbox_free((t_llllobj_pxjbox *)b_ob);
	jbox_free((t_jbox *)b_ob);
}

void dadaobj_send_changedbang(t_dadaobj *r_ob)
{
	if (r_ob->flags & DADAOBJ_CHANGEDBANG && (!r_ob->curr_change_is_from_message || r_ob->m_interface.send_bang_from_messages))
		llllobj_outlet_bang(r_ob->orig_obj, r_ob->llllobj_type, r_ob->m_interface.changebang_out_num);
}

void dadaobj_send_painted_notification(t_dadaobj *r_ob)
{
    t_llll *temp = llll_get();
    llll_appendsym(temp, _llllobj_sym_painted);
    llllobj_outlet_llll(r_ob->orig_obj, r_ob->llllobj_type, r_ob->m_interface.notifications_out_num, temp);
    llll_free(temp);
}

void dadaobj_send_notification_sym(t_dadaobj *r_ob, t_symbol *sym)
{
    if (r_ob->flags & DADAOBJ_NOTIFICATIONS && r_ob->m_interface.send_notifications) {
        t_llll *temp = llll_get();
        llll_appendsym(temp, sym);
        llllobj_outlet_llll(r_ob->orig_obj, r_ob->llllobj_type, r_ob->m_interface.notifications_out_num, temp);
        llll_free(temp);
    }
}

// will also free the ll, destructive.
void dadaobj_send_notification_llll(t_dadaobj *r_ob, t_llll *ll)
{
    if (r_ob->flags & DADAOBJ_NOTIFICATIONS && r_ob->m_interface.send_notifications) {
        llllobj_outlet_llll(r_ob->orig_obj, r_ob->llllobj_type, r_ob->m_interface.notifications_out_num, ll);
        llll_free(ll);
    }
}


void dadaobj_jbox_send_changebang(t_dadaobj *r_ob)
{
	llllobj_outlet_bang(r_ob->orig_obj, LLLL_OBJ_UI, r_ob->m_interface.changebang_out_num);
}


void dadaobj_invalidate_and_redraw(t_dadaobj *d_ob)
{
    if (!d_ob->m_paint.dont_repaint) {
        if (d_ob->m_paint.invalidate_and_redraw)
            d_ob->m_paint.invalidate_and_redraw(d_ob->orig_obj);
        else
            jbox_redraw((t_jbox *)d_ob->orig_obj);
    }
}

t_max_err dadaobj_setattr_zoom(t_dadaobj *d_ob, t_object *attr, long ac, t_atom *av)
{
	if (ac && av && is_atom_number(av)) {
		double zoom_perc = atom_getfloat(av);
        CLIP_ASSIGN(zoom_perc, d_ob->m_zoom.min_zoom_perc.x, d_ob->m_zoom.max_zoom_perc.x);
		d_ob->m_zoom.zoom_perc = zoom_perc;
		if (d_ob->flags & DADAOBJ_SPLITXYZOOM)
			d_ob->m_zoom.zoom = build_pt(d_ob->m_zoom.zoom_static_additional.x * d_ob->m_zoom.zoom_perc / 100., d_ob->m_zoom.zoom_static_additional.y * d_ob->m_zoom.zoom_y_perc / 100.);
		else
			d_ob->m_zoom.zoom = pt_number_prod(d_ob->m_zoom.zoom_static_additional, d_ob->m_zoom.zoom_perc / 100.);
        d_ob->m_grid.must_update_grid_size = true;
        dadaobj_invalidate_and_redraw(d_ob);
	}
	return MAX_ERR_NONE;
}


t_max_err dadaobj_setattr_vzoom(t_dadaobj *d_ob, t_object *attr, long ac, t_atom *av)
{
	if (ac && av && is_atom_number(av)) {
		double zoom_y_perc = atom_getfloat(av);
        CLIP_ASSIGN(zoom_y_perc, d_ob->m_zoom.min_zoom_perc.y, d_ob->m_zoom.max_zoom_perc.y);
		d_ob->m_zoom.zoom_y_perc = zoom_y_perc;
		if (d_ob->flags & DADAOBJ_SPLITXYZOOM)
			d_ob->m_zoom.zoom = build_pt(d_ob->m_zoom.zoom_static_additional.x * d_ob->m_zoom.zoom_perc / 100., d_ob->m_zoom.zoom_static_additional.y * d_ob->m_zoom.zoom_y_perc / 100.);
		else
			d_ob->m_zoom.zoom = pt_number_prod(d_ob->m_zoom.zoom_static_additional, d_ob->m_zoom.zoom_perc / 100.);
        d_ob->m_grid.must_update_grid_size = true;
        dadaobj_invalidate_and_redraw(d_ob);
	}
	return MAX_ERR_NONE;
}


t_max_err dadaobj_setattr_grid(t_dadaobj *d_ob, t_object *attr, long ac, t_atom *av)
{
    if (ac && av && is_atom_number(av)) {
        d_ob->m_grid.grid_size_fixed.x = atom_getfloat(av);
        d_ob->m_grid.grid_size_fixed.y = ac > 1 ? atom_getfloat(av + 1) : atom_getfloat(av);
        jbox_invalidate_layer(d_ob->orig_obj, NULL, gensym("grid"));
        jbox_redraw((t_jbox *)d_ob->orig_obj);
    }
    return MAX_ERR_NONE;
}

t_max_err dadaobj_setattr_showgrid(t_dadaobj *d_ob, t_object *attr, long ac, t_atom *av)
{
    if (ac && av && is_atom_number(av)) {
        d_ob->m_grid.show_grid = atom_getlong(av);
        jbox_invalidate_layer(d_ob->orig_obj, NULL, gensym("grid"));
        jbox_redraw((t_jbox *)d_ob->orig_obj);
    }
    return MAX_ERR_NONE;
}

t_max_err dadaobj_setattr_gridmode(t_dadaobj *d_ob, t_object *attr, long ac, t_atom *av)
{
    if (ac && av && is_atom_number(av)) {
        d_ob->m_grid.grid_mode = atom_getlong(av);
        object_attr_setdisabled(d_ob->orig_obj, gensym("grid"), d_ob->m_grid.grid_mode == 1);
        d_ob->m_grid.must_update_grid_size = true;
        jbox_invalidate_layer(d_ob->orig_obj, NULL, gensym("grid"));
        jbox_redraw((t_jbox *)d_ob->orig_obj);
    }
    return MAX_ERR_NONE;
}


t_max_err dadaobj_setattr_gridcolor(t_dadaobj *d_ob, t_object *attr, long ac, t_atom *av)
{
    if (ac >= 3) {
        d_ob->m_grid.j_gridcolor.red = atom_getfloat(av);
        d_ob->m_grid.j_gridcolor.green = atom_getfloat(av+1);
        d_ob->m_grid.j_gridcolor.blue = atom_getfloat(av+2);
        d_ob->m_grid.j_gridcolor.alpha = ac >= 4 ? atom_getfloat(av+3) : 1.;
        jbox_invalidate_layer(d_ob->orig_obj, NULL, gensym("grid"));
        jbox_redraw((t_jbox *)d_ob->orig_obj);
    }
    return MAX_ERR_NONE;
}

t_max_err dadaobj_setattr_showaxeslabels(t_dadaobj *d_ob, t_object *attr, long ac, t_atom *av)
{
    if (ac && av && is_atom_number(av)) {
        d_ob->m_grid.show_axes_labels = atom_getlong(av);
        jbox_invalidate_layer(d_ob->orig_obj, NULL, gensym("grid"));
        jbox_redraw((t_jbox *)d_ob->orig_obj);
    }
    return MAX_ERR_NONE;
}

t_max_err dadaobj_setattr_axeslabelscolor(t_dadaobj *d_ob, t_object *attr, long ac, t_atom *av)
{
    if (ac >= 3) {
        d_ob->m_grid.j_axeslabelscolor.red = atom_getfloat(av);
        d_ob->m_grid.j_axeslabelscolor.green = atom_getfloat(av+1);
        d_ob->m_grid.j_axeslabelscolor.blue = atom_getfloat(av+2);
        d_ob->m_grid.j_axeslabelscolor.alpha = ac >= 4 ? atom_getfloat(av+3) : 1.;
        jbox_invalidate_layer(d_ob->orig_obj, NULL, gensym("grid"));
        jbox_redraw((t_jbox *)d_ob->orig_obj);
    }
    return MAX_ERR_NONE;
}


t_max_err dadaobj_setattr_xlabel(t_dadaobj *d_ob, t_object *attr, long ac, t_atom *av)
{
    if (ac && av && atom_gettype(av) == A_SYM)
        d_ob->m_grid.x_label = atom_getsym(av);
    else
        d_ob->m_grid.x_label = _llllobj_sym_empty_symbol;
    jbox_invalidate_layer(d_ob->orig_obj, NULL, gensym("grid"));
    jbox_redraw((t_jbox *)d_ob->orig_obj);
    return MAX_ERR_NONE;
}

t_max_err dadaobj_setattr_ylabel(t_dadaobj *d_ob, t_object *attr, long ac, t_atom *av)
{
    if (ac && av && atom_gettype(av) == A_SYM)
        d_ob->m_grid.y_label = atom_getsym(av);
    else
        d_ob->m_grid.y_label = _llllobj_sym_empty_symbol;
    jbox_invalidate_layer(d_ob->orig_obj, NULL, gensym("grid"));
    jbox_redraw((t_jbox *)d_ob->orig_obj);
    return MAX_ERR_NONE;
}

t_max_err dadaobj_setattr_showaxes(t_dadaobj *d_ob, t_object *attr, long ac, t_atom *av)
{
    if (ac && av && is_atom_number(av)) {
        d_ob->m_grid.show_axes = atom_getlong(av);
        jbox_invalidate_layer(d_ob->orig_obj, NULL, gensym("grid"));
        jbox_redraw((t_jbox *)d_ob->orig_obj);
    }
    return MAX_ERR_NONE;
}

t_max_err dadaobj_setattr_axescolor(t_dadaobj *d_ob, t_object *attr, long ac, t_atom *av)
{
    if (ac >= 3) {
        d_ob->m_grid.j_axescolor.red = atom_getfloat(av);
        d_ob->m_grid.j_axescolor.green = atom_getfloat(av+1);
        d_ob->m_grid.j_axescolor.blue = atom_getfloat(av+2);
        d_ob->m_grid.j_axescolor.alpha = ac >= 4 ? atom_getfloat(av+3) : 1.;
        jbox_invalidate_layer(d_ob->orig_obj, NULL, gensym("grid"));
        jbox_redraw((t_jbox *)d_ob->orig_obj);
    }
    return MAX_ERR_NONE;
}

t_max_err dadaobj_setattr_showgridlabels(t_dadaobj *d_ob, t_object *attr, long ac, t_atom *av)
{
    if (ac && av && is_atom_number(av)) {
        d_ob->m_grid.show_labels = atom_getlong(av);
        jbox_invalidate_layer(d_ob->orig_obj, NULL, gensym("grid"));
        jbox_redraw((t_jbox *)d_ob->orig_obj);
    }
    return MAX_ERR_NONE;
}

t_max_err dadaobj_setattr_gridlabelscolor(t_dadaobj *d_ob, t_object *attr, long ac, t_atom *av)
{
    if (ac >= 3) {
        d_ob->m_grid.j_labelscolor.red = atom_getfloat(av);
        d_ob->m_grid.j_labelscolor.green = atom_getfloat(av+1);
        d_ob->m_grid.j_labelscolor.blue = atom_getfloat(av+2);
        d_ob->m_grid.j_labelscolor.alpha = ac >= 4 ? atom_getfloat(av+3) : 1.;
        jbox_invalidate_layer(d_ob->orig_obj, NULL, gensym("grid"));
        jbox_redraw((t_jbox *)d_ob->orig_obj);
    }
    return MAX_ERR_NONE;
}

t_max_err dadaobj_setattr_gridlabelsfontsize(t_dadaobj *d_ob, t_object *attr, long ac, t_atom *av)
{
    if (ac && av && is_atom_number(av)) {
        d_ob->m_grid.labelsfontsize = atom_getfloat(av);
        jbox_invalidate_layer(d_ob->orig_obj, NULL, gensym("grid"));
        jbox_redraw((t_jbox *)d_ob->orig_obj);
    }
    return MAX_ERR_NONE;
}

t_max_err dadaobj_setattr_axeslabelsfontsize(t_dadaobj *d_ob, t_object *attr, long ac, t_atom *av)
{
    if (ac && av && is_atom_number(av)) {
        d_ob->m_grid.axeslabelsfontsize = atom_getfloat(av);
        jbox_invalidate_layer(d_ob->orig_obj, NULL, gensym("grid"));
        jbox_redraw((t_jbox *)d_ob->orig_obj);
    }
    return MAX_ERR_NONE;
}




t_max_err dadaobj_setattr_maxundosteps(t_dadaobj *d_ob, t_object *attr, long ac, t_atom *av)
{
	if (ac && av && is_atom_number(av)) {
		d_ob->m_undo.max_num_steps = atom_getlong(av);
		undo_check_max_num_steps(&d_ob->m_undo);
	}
	return MAX_ERR_NONE;
}



t_max_err dadaobj_setattr_bgimage(t_dadaobj *d_ob, t_object *attr, long ac, t_atom *av)
{
    if (d_ob->m_bg.bg_surface) {
        jgraphics_surface_destroy(d_ob->m_bg.bg_surface);
        d_ob->m_bg.bg_surface = NULL;
    }
    
    if (ac > 0 && atom_gettype(av) == A_SYM && atom_getsym(av) != _llllobj_sym_none && atom_getsym(av) != _llllobj_sym_empty_symbol) {
        d_ob->m_bg.bg_surface = get_surface_from_file(atom_getsym(av));
        //jgraphics_surface_destroy(sky);
        d_ob->m_bg.bg_image = atom_getsym(av);
    } else {
        d_ob->m_bg.bg_image = _llllobj_sym_none;
    }
    
    return MAX_ERR_NONE;
}


t_max_err dadaobj_jbox_setattr_bgimage(t_dadaobj_jbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_bgimage(&b_ob->d_ob, attr, ac, av);
}

t_max_err dadaobj_jbox_setattr_zoom(t_dadaobj_jbox *b_ob, t_object *attr, long ac, t_atom *av)
{
	return dadaobj_setattr_zoom(&b_ob->d_ob, attr, ac, av);
}


t_max_err dadaobj_jbox_setattr_vzoom(t_dadaobj_jbox *b_ob, t_object *attr, long ac, t_atom *av)
{
	return dadaobj_setattr_vzoom(&b_ob->d_ob, attr, ac, av);
}

t_max_err dadaobj_jbox_setattr_grid(t_dadaobj_jbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_grid(&b_ob->d_ob, attr, ac, av);
}

t_max_err dadaobj_jbox_setattr_showgrid(t_dadaobj_jbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_showgrid(&b_ob->d_ob, attr, ac, av);
}

t_max_err dadaobj_jbox_setattr_gridmode(t_dadaobj_jbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_gridmode(&b_ob->d_ob, attr, ac, av);
}


t_max_err dadaobj_jbox_setattr_gridcolor(t_dadaobj_jbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_gridcolor(&b_ob->d_ob, attr, ac, av);
}

t_max_err dadaobj_jbox_setattr_showaxeslabels(t_dadaobj_jbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_showaxeslabels(&b_ob->d_ob, attr, ac, av);
}


t_max_err dadaobj_jbox_setattr_axeslabelscolor(t_dadaobj_jbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_axeslabelscolor(&b_ob->d_ob, attr, ac, av);
}

t_max_err dadaobj_jbox_setattr_xlabel(t_dadaobj_jbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_xlabel(&b_ob->d_ob, attr, ac, av);
}

t_max_err dadaobj_jbox_setattr_ylabel(t_dadaobj_jbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_ylabel(&b_ob->d_ob, attr, ac, av);
}

t_max_err dadaobj_jbox_setattr_showaxes(t_dadaobj_jbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_showaxes(&b_ob->d_ob, attr, ac, av);
}


t_max_err dadaobj_jbox_setattr_axescolor(t_dadaobj_jbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_axescolor(&b_ob->d_ob, attr, ac, av);
}

t_max_err dadaobj_jbox_setattr_showgridlabels(t_dadaobj_jbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_showgridlabels(&b_ob->d_ob, attr, ac, av);
}


t_max_err dadaobj_jbox_setattr_gridlabelscolor(t_dadaobj_jbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_gridlabelscolor(&b_ob->d_ob, attr, ac, av);
}


t_max_err dadaobj_jbox_setattr_gridlabelsfontsize(t_dadaobj_jbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_gridlabelsfontsize(&b_ob->d_ob, attr, ac, av);
}


t_max_err dadaobj_jbox_setattr_axeslabelsfontsize(t_dadaobj_jbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_axeslabelsfontsize(&b_ob->d_ob, attr, ac, av);
}

t_max_err dadaobj_jbox_setattr_maxundosteps(t_dadaobj_jbox *b_ob, t_object *attr, long ac, t_atom *av)
{
	return dadaobj_setattr_maxundosteps(&b_ob->d_ob, attr, ac, av);
}


t_max_err dadaobj_pxjbox_setattr_bgimage(t_dadaobj_pxjbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_bgimage(&b_ob->d_ob, attr, ac, av);
}


t_max_err dadaobj_pxjbox_setattr_zoom(t_dadaobj_pxjbox *b_ob, t_object *attr, long ac, t_atom *av)
{
	return dadaobj_setattr_zoom(&b_ob->d_ob, attr, ac, av);
}


t_max_err dadaobj_pxjbox_setattr_grid(t_dadaobj_pxjbox *b_ob, t_object *attr, long ac, t_atom *av)
{
	return dadaobj_setattr_grid(&b_ob->d_ob, attr, ac, av);
}

t_max_err dadaobj_pxjbox_setattr_showgrid(t_dadaobj_pxjbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_showgrid(&b_ob->d_ob, attr, ac, av);
}

t_max_err dadaobj_pxjbox_setattr_gridmode(t_dadaobj_pxjbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_gridmode(&b_ob->d_ob, attr, ac, av);
}

t_max_err dadaobj_pxjbox_setattr_gridcolor(t_dadaobj_pxjbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_gridcolor(&b_ob->d_ob, attr, ac, av);
}


t_max_err dadaobj_pxjbox_setattr_showaxeslabels(t_dadaobj_pxjbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_showaxeslabels(&b_ob->d_ob, attr, ac, av);
}

t_max_err dadaobj_pxjbox_setattr_axeslabelscolor(t_dadaobj_pxjbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_axeslabelscolor(&b_ob->d_ob, attr, ac, av);
}

t_max_err dadaobj_pxjbox_setattr_xlabel(t_dadaobj_pxjbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_xlabel(&b_ob->d_ob, attr, ac, av);
}

t_max_err dadaobj_pxjbox_setattr_ylabel(t_dadaobj_pxjbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_ylabel(&b_ob->d_ob, attr, ac, av);
}


t_max_err dadaobj_pxjbox_setattr_showaxes(t_dadaobj_pxjbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_showaxes(&b_ob->d_ob, attr, ac, av);
}

t_max_err dadaobj_pxjbox_setattr_axescolor(t_dadaobj_pxjbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_axescolor(&b_ob->d_ob, attr, ac, av);
}

t_max_err dadaobj_pxjbox_setattr_showgridlabels(t_dadaobj_pxjbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_showgridlabels(&b_ob->d_ob, attr, ac, av);
}

t_max_err dadaobj_pxjbox_setattr_gridlabelscolor(t_dadaobj_pxjbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_gridlabelscolor(&b_ob->d_ob, attr, ac, av);
}

t_max_err dadaobj_pxjbox_setattr_gridlabelsfontsize(t_dadaobj_pxjbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_gridlabelsfontsize(&b_ob->d_ob, attr, ac, av);
}

t_max_err dadaobj_pxjbox_setattr_axeslabelsfontsize(t_dadaobj_pxjbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_axeslabelsfontsize(&b_ob->d_ob, attr, ac, av);
}



t_max_err dadaobj_pxjbox_setattr_vzoom(t_dadaobj_pxjbox *b_ob, t_object *attr, long ac, t_atom *av)
{
    return dadaobj_setattr_vzoom(&b_ob->d_ob, attr, ac, av);
}

t_max_err dadaobj_pxjbox_setattr_maxundosteps(t_dadaobj_pxjbox *b_ob, t_object *attr, long ac, t_atom *av)
{
	return dadaobj_setattr_maxundosteps(&b_ob->d_ob, attr, ac, av);
}

void dadaobj_class_init(t_class *c, e_llllobj_obj_types type, long flags)
{
    DADAOBJ_CLASS_ATTR_LONG(c, type, "versionnumber", 0, t_dadaobj, m_version_number);
    CLASS_ATTR_DEFAULT_SAVE(c,"versionnumber", 0, "0");
    CLASS_ATTR_INVISIBLE(c, "versionnumber", ATTR_GET_OPAQUE | ATTR_SET_OPAQUE); // invisible attribute
    // @exclude all

    if (type == LLLL_OBJ_UI || type == LLLL_OBJ_UIMSP) {
        DADAOBJ_CLASS_ATTR_CHAR_SUBSTRUCTURE(c,type, "notifypaint", 0, t_dadaobj, m_paint, t_paint_manager, notify_when_painted);
        CLASS_ATTR_STYLE_LABEL(c, "notifypaint", 0, "onoff", "Notify Display Refresh");
        CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "notifypaint", 0, "0");
        CLASS_ATTR_CATEGORY(c, "notifypaint", 0, "Behavior");
        // @description Toggles the ability to notify every new redraw of the box via a "painted" symbol.
    }
       
    if (flags & DADAOBJ_BORDER) {
        DADAOBJ_CLASS_ATTR_CHAR_SUBSTRUCTURE(c,type, "showborder", 0, t_dadaobj, m_bg, t_bg_manager, show_border);
        CLASS_ATTR_STYLE_LABEL(c, "showborder", 0, "onoff", "Show Border");
        CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "showborder", 0, flags & DADAOBJ_BORDER_SHOWDEFAULT ? "1" : "0");
        CLASS_ATTR_CATEGORY(c, "showborder", 0, "Appearance");
        // @description Sets the color of the border.
        // @includeifflagged DADAOBJ_BORDER

        
        DADAOBJ_CLASS_ATTR_RGBA_SUBSTRUCTURE(c,type, "bordercolor", 0, t_dadaobj, m_bg, t_bg_manager, bordercolor);
        CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bordercolor", 0, "0. 0. 0. 1.");
        CLASS_ATTR_STYLE_LABEL(c, "bordercolor", 0, "rgba", "Border Color");
        CLASS_ATTR_CATEGORY(c, "bordercolor", 0, "Color");
        // @description Sets the color of the border.
        // @includeifflagged DADAOBJ_BORDER
        
        DADAOBJ_CLASS_ATTR_CHAR_SUBSTRUCTURE(c,type, "showfocus", 0, t_dadaobj, m_bg, t_bg_manager, show_focus);
        CLASS_ATTR_STYLE_LABEL(c, "showfocus", 0, "onoff", "Show Focus");
        CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showfocus",0,"1");
        CLASS_ATTR_CATEGORY(c, "showfocus", 0, "Appearance");
        // @description Toggles the ability to draw a thicker border when the object has the focus.
        // @includeifflagged DADAOBJ_BORDER
    }

    if (flags & DADAOBJ_BG) {
        DADAOBJ_CLASS_ATTR_RGBA_SUBSTRUCTURE(c,type, "bgcolor", 0, t_dadaobj, m_bg, t_bg_manager, bgcolor);
        CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgcolor", 0, "1. 1. 1. 1.");
        CLASS_ATTR_STYLE_LABEL(c, "bgcolor", 0, "rgba", "Background Color");
        CLASS_ATTR_CATEGORY(c, "bgcolor", 0, "Color");
        CLASS_ATTR_BASIC(c, "bgcolor", 0);
        // @description Sets the color of the background.
        // @includeifflagged DADAOBJ_BG
    }

    if (flags & DADAOBJ_BGIMAGE) {
        DADAOBJ_CLASS_ATTR_SYM_SUBSTRUCTURE(c,type, "bgimage", 0, t_dadaobj, m_bg, t_bg_manager, bg_image);
        CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "bgimage", 0, "none");
        CLASS_ATTR_STYLE_LABEL(c, "bgimage", 0, "text", "Background Image");
        CLASS_ATTR_ACCESSORS(c, "bgimage", (method)NULL, type == LLLL_OBJ_UI ? (method)dadaobj_jbox_setattr_bgimage : (method)dadaobj_pxjbox_setattr_bgimage);
        CLASS_ATTR_CATEGORY(c, "bgimage", 0, "Appearance");
        CLASS_ATTR_BASIC(c, "bgimage", 0);
        // @description Sets a background image texture, tiling the plane. Use "" or "none" to remove the image.
        // @includeifflagged DADAOBJ_BGIMAGE
    }

    
    if (flags & DADAOBJ_ZOOM) {
		DADAOBJ_CLASS_ATTR_DOUBLE_SUBSTRUCTURE(c, type, "zoom", 0, t_dadaobj, m_zoom, t_zoom_manager, zoom_perc);
		CLASS_ATTR_STYLE_LABEL(c, "zoom", 0, "text", flags & DADAOBJ_SPLITXYZOOM ? "Horizontal Zoom %" : "Zoom %");
		CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"zoom",0,"100");
		CLASS_ATTR_BASIC(c, "zoom", 0);
		CLASS_ATTR_CATEGORY(c, "zoom", 0, "Appearance");
		CLASS_ATTR_ACCESSORS(c, "zoom", (method)NULL, type == LLLL_OBJ_UI ? (method)dadaobj_jbox_setattr_zoom : (method)dadaobj_pxjbox_setattr_zoom);
		// @description Sets the object zoom percentage (or horizontal zoom, if the object is separately zoommable on horizontal and on vertical axis).
		// @includeifflagged DADAOBJ_ZOOMX+DADAOBJ_ZOOMY+DADAOBJ_SPLITXYZOOM
        
		if (flags & DADAOBJ_SPLITXYZOOM) {
			DADAOBJ_CLASS_ATTR_DOUBLE_SUBSTRUCTURE(c, type, "vzoom", 0, t_dadaobj, m_zoom, t_zoom_manager, zoom_y_perc);
			CLASS_ATTR_STYLE_LABEL(c, "vzoom", 0, "text", "Vertical Zoom %");
			CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"vzoom",0,"100");
			CLASS_ATTR_BASIC(c, "vzoom", 0);
			CLASS_ATTR_CATEGORY(c, "vzoom", 0, "Appearance");
			CLASS_ATTR_ACCESSORS(c, "vzoom", (method)NULL, type == LLLL_OBJ_UI ? (method)dadaobj_jbox_setattr_vzoom : (method)dadaobj_pxjbox_setattr_vzoom);
			// @description Sets the object vertical zoom percentage
			// @includeifflagged DADAOBJ_ZOOMX+DADAOBJ_ZOOMY+DADAOBJ_SPLITXYZOOM
		}
		
		DADAOBJ_CLASS_ATTR_CHAR_SUBSTRUCTURE(c, type, "allowzoom", 0, t_dadaobj, m_zoom, t_zoom_manager, allow_zoom);
		CLASS_ATTR_STYLE_LABEL(c, "allowzoom", 0, "onoff", "Allow Zoom");
		CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"allowzoom",0,"1");
		CLASS_ATTR_FILTER_CLIP(c, "allowzoom", 0, 1);
		CLASS_ATTR_CATEGORY(c, "allowzoom", 0, "Behavior");
		// @description Toggles the ability to allow zooming
		// @includeifflagged DADAOBJ_ZOOMX+DADAOBJ_ZOOMY
	}
	
	if (flags & DADAOBJ_CENTEROFFSET) {
		DADAOBJ_CLASS_ATTR_DOUBLE_ARRAY_SUBSTRUCTURE(c, type, "center", 0, t_dadaobj, m_zoom, t_zoom_manager, center_offset, 2);
		CLASS_ATTR_STYLE_LABEL(c, "center", 0, "text", "Center Coordinates");
		CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"center",0,"0 0");
		CLASS_ATTR_CATEGORY(c, "center", 0, "Appearance");
		// @description Sets the coordinate of the center
		// @includeifflagged DADAOBJ_CENTEROFFSET

		DADAOBJ_CLASS_ATTR_CHAR_SUBSTRUCTURE(c, type, "allowcentershift", 0, t_dadaobj, m_zoom, t_zoom_manager, allow_center_shifting);
		CLASS_ATTR_STYLE_LABEL(c, "allowcentershift", 0, "onoff", "Allow Center Shifting");
		CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"allowcentershift",0,"1");
		CLASS_ATTR_FILTER_CLIP(c, "allowcentershift", 0, 1);
		CLASS_ATTR_CATEGORY(c, "allowcentershift", 0, "Behavior");
		// @description Toggles the ability to allow the center to shift.
		// @includeifflagged DADAOBJ_CENTEROFFSET
	}
	
	if (flags & DADAOBJ_CHANGEDBANG) {
		DADAOBJ_CLASS_ATTR_CHAR_SUBSTRUCTURE(c, type, "messagebang",0,  t_dadaobj, m_interface, t_interface_manager, send_bang_from_messages);
		CLASS_ATTR_STYLE_LABEL(c,"messagebang",0,"onoff","Send bang Upon Messages");
		CLASS_ATTR_DEFAULT_SAVE(c,"messagebang",0,"0");
		CLASS_ATTR_CATEGORY(c, "messagebang", 0, "Behavior");
		// @description Toggles the ability to send the changed bang also when changes happen via messages.
		// @includeifflagged DADAOBJ_CHANGEDBANG

        DADAOBJ_CLASS_ATTR_CHAR_SUBSTRUCTURE(c, type, "continuousbang",0,  t_dadaobj, m_interface, t_interface_manager, continuously_send_changebang);
        CLASS_ATTR_STYLE_LABEL(c,"continuousbang",0,"onoff","Continuously Output bang if Changed ");
        CLASS_ATTR_DEFAULT_SAVE(c,"continuousbang",0,"0");
        CLASS_ATTR_CATEGORY(c, "continuousbang", 0, "Behavior");
        // @description Toggles the ability to send the changed bang continuously during mousedrag actions.
        // @includeifflagged DADAOBJ_CHANGEDBANG

		if (flags & DADAOBJ_UNDO) {
			DADAOBJ_CLASS_ATTR_CHAR_SUBSTRUCTURE(c, type, "undobang",0,  t_dadaobj, m_interface, t_interface_manager, send_bang_upon_undo);
			CLASS_ATTR_STYLE_LABEL(c,"undobang",0,"onoff","Send bang Upon Undo");
			CLASS_ATTR_DEFAULT_SAVE(c,"undobang",0,"1");
			CLASS_ATTR_CATEGORY(c, "undobang", 0, "Behavior");
			// @description Toggles the ability to send the changed bang also when changes happen via messages.
			// @includeifflagged DADAOBJ_CHANGEDBANG+DADAOBJ_UNDO
		}
	}
	
	
	if (flags & DADAOBJ_UNDO) {
		DADAOBJ_CLASS_ATTR_LONG_SUBSTRUCTURE(c, type, "maxundosteps",0, t_dadaobj, m_undo, t_undo_manager, max_num_steps);
		CLASS_ATTR_STYLE_LABEL(c,"maxundosteps",0,"text","Maximum Number Of Undo Steps");
		CLASS_ATTR_DEFAULT_SAVE(c,"maxundosteps",0,"50");
		CLASS_ATTR_CATEGORY(c, "maxundosteps", 0, "Behavior");
		CLASS_ATTR_ACCESSORS(c, "maxundosteps", (method)NULL, type == LLLL_OBJ_UI ? (method)dadaobj_jbox_setattr_maxundosteps : (method)dadaobj_pxjbox_setattr_maxundosteps);
		// @description Sets the maximum number of undo steps (0 being: no undo).
		// @includeifflagged DADAOBJ_UNDO

		DADAOBJ_CLASS_ATTR_CHAR_SUBSTRUCTURE(c, type, "verboseundo",0, t_dadaobj, m_undo, t_undo_manager, verbose_undo);
		CLASS_ATTR_STYLE_LABEL(c,"verboseundo",0,"onoff","Post Undo/Redo Steps");
		CLASS_ATTR_DEFAULT_SAVE(c,"verboseundo",0,"0");
		CLASS_ATTR_CATEGORY(c, "verboseundo", 0, "Behavior");
		// @description Toggles the ability to post undo/redo steps in the Max window.
		// @includeifflagged DADAOBJ_UNDO
        
        if (flags & DADAOBJ_PLAY) {
            DADAOBJ_CLASS_ATTR_CHAR_SUBSTRUCTURE(c, type, "undobeforeplay",0, t_dadaobj, m_undo, t_undo_manager, undo_before_play);
            CLASS_ATTR_STYLE_LABEL(c,"undobeforeplay",0,"onoff","Save State For Undo Before Playing");
            CLASS_ATTR_DEFAULT_SAVE(c,"undobeforeplay",0,"1");
            CLASS_ATTR_CATEGORY(c, "undobeforeplay", 0, "Behavior");
            // @description Toggles the ability to save the state for an undo step before playing
            // @includeifflagged DADAOBJ_UNDO+DADAOBJ_PLAY
        }
	}
	
	if (flags & DADAOBJ_EMBED) {
		DADAOBJ_CLASS_ATTR_CHAR(c, type, "embed",0, t_dadaobj, save_data_with_patcher);
		CLASS_ATTR_STYLE_LABEL(c,"embed",0,"onoff","Save Data With Patcher");
		CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"embed",0,"1");
		CLASS_ATTR_BASIC(c,"embed",0);
		CLASS_ATTR_CATEGORY(c, "embed", 0, "Behavior");
		// @description Toggles the ability to embed the state of the object within the patcher.
		// @includeifflagged DADAOBJ_UNDO
	}
	
	if (flags & DADAOBJ_MOUSEHOVER) {
		DADAOBJ_CLASS_ATTR_CHAR_SUBSTRUCTURE(c, type, "mousehover", 0, t_dadaobj, m_interface, t_interface_manager, allow_mouse_hover);
		CLASS_ATTR_STYLE_LABEL(c, "mousehover", 0, "onoff", "Allow Mouse Hovering");
		CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"mousehover",0,"1");
		CLASS_ATTR_CATEGORY(c, "mousehover", 0, "Behavior");
		// @description Toggles mouse hovering capabilities.
		// @includeifflagged DADAOBJ_MOUSEHOVER
    }
    
    
    if (flags & DADAOBJ_NOTIFICATIONS) {
        DADAOBJ_CLASS_ATTR_CHAR_SUBSTRUCTURE(c, type, "notify", 0, t_dadaobj, m_interface, t_interface_manager, send_notifications);
        CLASS_ATTR_STYLE_LABEL(c, "notify", 0, "enumindex", "Send Notifications");
        CLASS_ATTR_ENUMINDEX(c,"notify", 0, "Don't Basic Verbose");
        CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"notify",0,"0");
        CLASS_ATTR_CATEGORY(c, "notify", 0, "Behavior");
        CLASS_ATTR_BASIC(c, "notify", 0);
        // @description Toggles the ability to send notifications for interface activities (such as clicks, mousehovers, etc.).
        // Notifications are sent through the dedicated outlet. If the "Verbose" mode is set, whenever meaningful, the state
        // of the notified element will be also output.
        // @includeifflagged DADAOBJ_NOTIFICATIONS
    }

    
    if (flags & DADAOBJ_GRID) {
        
        if (flags & DADAOBJ_SNAPTOGRID) {
            DADAOBJ_CLASS_ATTR_CHAR_SUBSTRUCTURE(c, type, "snaptogrid",0, t_dadaobj, m_grid, t_grid_manager, snap_to_grid);
            CLASS_ATTR_STYLE_LABEL(c,"snaptogrid",0,"onoff","Snap To Grid");
            CLASS_ATTR_DEFAULT_SAVE(c,"snaptogrid",0,"0");
            CLASS_ATTR_CATEGORY(c, "snaptogrid", 0, "Axes And Grid");
            // @description Toggles the ability to snap items to the grid.
            // @includeifflagged DADAOBJ_GRID+DADAOBJ_SNAPTOGRID
        }
        
        DADAOBJ_CLASS_ATTR_CHAR_SUBSTRUCTURE(c, type, "gridmode",0, t_dadaobj, m_grid, t_grid_manager, grid_mode);
        CLASS_ATTR_STYLE_LABEL(c,"gridmode",0,"enumindex","Grid Mode");
        CLASS_ATTR_DEFAULT_SAVE(c,"gridmode",0, flags & DADAOBJ_GRID_FIXEDDEFAULT ? "0" : "1");
        CLASS_ATTR_ENUMINDEX(c,"gridmode", 0, "Fixed Automatic");
        CLASS_ATTR_CATEGORY(c, "gridmode", 0, "Axes And Grid");
        CLASS_ATTR_ACCESSORS(c, "gridmode", (method)NULL, type == LLLL_OBJ_UI ? (method)dadaobj_jbox_setattr_gridmode : (method)dadaobj_pxjbox_setattr_gridmode);
        // @description Sets the grid mode, either Fixed (0) or Automatic (1 = default). In Automatic mode the space between grid lines
        // is automatically adapted according to the level of zoom.
        // @includeifflagged DADAOBJ_GRID
        
        DADAOBJ_CLASS_ATTR_DOUBLE_ARRAY_SUBSTRUCTURE(c, type, "gridstep",0, t_dadaobj, m_grid, t_grid_manager, grid_size_fixed, 2);
		CLASS_ATTR_STYLE_LABEL(c, "gridstep", 0, "text", "Grid Size");
		CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"gridstep",0,"10 10");
		CLASS_ATTR_CATEGORY(c, "gridstep", 0, "Axes And Grid");
        CLASS_ATTR_ACCESSORS(c, "gridstep", (method)NULL, type == LLLL_OBJ_UI ? (method)dadaobj_jbox_setattr_grid : (method)dadaobj_pxjbox_setattr_grid);
		// @description Sets the grid size, in coordinates (only useful if <m>gridmode</m> is set to 0 = Fixed)
		// @includeifflagged DADAOBJ_GRID

		DADAOBJ_CLASS_ATTR_CHAR_SUBSTRUCTURE(c, type, "showgrid",0, t_dadaobj, m_grid, t_grid_manager, show_grid);
		CLASS_ATTR_STYLE_LABEL(c,"showgrid",0,"onoff","Show Grid");
        CLASS_ATTR_DEFAULT_SAVE(c,"showgrid",0, flags & DADAOBJ_GRID_SHOWDEFAULT ? "1" : "0");
		CLASS_ATTR_CATEGORY(c, "showgrid", 0, "Axes And Grid");
        CLASS_ATTR_ACCESSORS(c, "showgrid", (method)NULL, type == LLLL_OBJ_UI ? (method)dadaobj_jbox_setattr_showgrid : (method)dadaobj_pxjbox_setattr_showgrid);
		// @description Toggles the display of the grid.
		// @includeifflagged DADAOBJ_GRID

		DADAOBJ_CLASS_ATTR_RGBA_SUBSTRUCTURE(c,type, "gridcolor", 0, t_dadaobj, m_grid, t_grid_manager, j_gridcolor);
		CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "gridcolor", 0, "0. 0. 0. 0.1");
		CLASS_ATTR_STYLE_LABEL(c, "gridcolor", 0, "rgba", "Grid Color");
		CLASS_ATTR_CATEGORY(c, "gridcolor", 0, "Color");
        CLASS_ATTR_ACCESSORS(c, "gridcolor", (method)NULL, type == LLLL_OBJ_UI ? (method)dadaobj_jbox_setattr_gridcolor : (method)dadaobj_pxjbox_setattr_gridcolor);
		// @description Sets the grid color.
		// @includeifflagged DADAOBJ_GRID
	}

    if (flags & DADAOBJ_AXES) {
        DADAOBJ_CLASS_ATTR_CHAR_SUBSTRUCTURE(c, type, "showaxes",0, t_dadaobj, m_grid, t_grid_manager, show_axes);
        CLASS_ATTR_STYLE_LABEL(c,"showaxes",0,"onoff","Show Axes");
        CLASS_ATTR_DEFAULT_SAVE(c,"showaxes",0, flags & DADAOBJ_AXES_SHOWDEFAULT ? "1" : "0");
        CLASS_ATTR_CATEGORY(c, "showaxes", 0, "Axes And Grid");
        CLASS_ATTR_ACCESSORS(c, "showaxes", (method)NULL, type == LLLL_OBJ_UI ? (method)dadaobj_jbox_setattr_showaxes : (method)dadaobj_pxjbox_setattr_showaxes);
        // @description Toggles the display of the x and y axes.
        // @includeifflagged DADAOBJ_AXES
        
        DADAOBJ_CLASS_ATTR_RGBA_SUBSTRUCTURE(c,type, "axescolor", 0, t_dadaobj, m_grid, t_grid_manager, j_axescolor);
        CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "axescolor", 0, "0.4 0.4 0.4 1.");
        CLASS_ATTR_STYLE_LABEL(c, "axescolor", 0, "rgba", "Axes Color");
        CLASS_ATTR_ACCESSORS(c, "axescolor", (method)NULL, type == LLLL_OBJ_UI ? (method)dadaobj_jbox_setattr_axescolor : (method)dadaobj_pxjbox_setattr_axescolor);
        CLASS_ATTR_CATEGORY(c, "axescolor", 0, "Color");
        // @description Sets the color of the x and y axes.
        // @includeifflagged DADAOBJ_AXES
    }
    
    if (flags & DADAOBJ_LABELS) {
        DADAOBJ_CLASS_ATTR_CHAR_SUBSTRUCTURE(c, type, "showgridlabels",0, t_dadaobj, m_grid, t_grid_manager, show_labels);
        CLASS_ATTR_STYLE_LABEL(c,"showgridlabels",0,"onoff","Show Grid Labels");
        CLASS_ATTR_DEFAULT_SAVE(c,"showgridlabels",0, flags & DADAOBJ_LABELS_SHOWDEFAULT ? "1" : "0");
        CLASS_ATTR_CATEGORY(c, "showgridlabels", 0, "Axes And Grid");
        CLASS_ATTR_ACCESSORS(c, "showgridlabels", (method)NULL, type == LLLL_OBJ_UI ? (method)dadaobj_jbox_setattr_showgridlabels : (method)dadaobj_pxjbox_setattr_showgridlabels);
        // @description Toggles the display of the grid labels.
        // @includeifflagged DADAOBJ_LABELS
        
        DADAOBJ_CLASS_ATTR_RGBA_SUBSTRUCTURE(c,type, "gridlabelscolor", 0, t_dadaobj, m_grid, t_grid_manager, j_labelscolor);
        CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "gridlabelscolor", 0, "0.4 0.4 0.4 1.");
        CLASS_ATTR_STYLE_LABEL(c, "gridlabelscolor", 0, "rgba", "Grid Labels Color");
        CLASS_ATTR_ACCESSORS(c, "gridlabelscolor", (method)NULL, type == LLLL_OBJ_UI ? (method)dadaobj_jbox_setattr_gridlabelscolor : (method)dadaobj_pxjbox_setattr_gridlabelscolor);
        CLASS_ATTR_CATEGORY(c, "gridlabelscolor", 0, "Color");
        // @description Sets the color of the grid labels.
        // @includeifflagged DADAOBJ_LABELS

        
        DADAOBJ_CLASS_ATTR_DOUBLE_SUBSTRUCTURE(c, type, "gridlabelsfontsize",0, t_dadaobj, m_grid, t_grid_manager, labelsfontsize);
        CLASS_ATTR_STYLE_LABEL(c,"gridlabelsfontsize",0,"text","Grid Labels Font Size");
        CLASS_ATTR_DEFAULT_SAVE(c,"gridlabelsfontsize",0, "8.");
        CLASS_ATTR_CATEGORY(c, "gridlabelsfontsize", 0, "Axes And Grid");
        CLASS_ATTR_ACCESSORS(c, "gridlabelsfontsize", (method)NULL, type == LLLL_OBJ_UI ? (method)dadaobj_jbox_setattr_gridlabelsfontsize : (method)dadaobj_pxjbox_setattr_gridlabelsfontsize);
        // @description Sets the size of the grid labels font.
        // @includeifflagged DADAOBJ_LABELS
        
        
        DADAOBJ_CLASS_ATTR_CHAR_SUBSTRUCTURE(c, type, "showaxeslabels",0, t_dadaobj, m_grid, t_grid_manager, show_axes_labels);
        CLASS_ATTR_STYLE_LABEL(c,"showaxeslabels",0,"onoff","Show Axes Labels");
        CLASS_ATTR_DEFAULT_SAVE(c,"showaxeslabels",0, "0");
        CLASS_ATTR_CATEGORY(c, "showaxeslabels", 0, "Axes And Grid");
        CLASS_ATTR_ACCESSORS(c, "showaxeslabels", (method)NULL, type == LLLL_OBJ_UI ? (method)dadaobj_jbox_setattr_showaxeslabels : (method)dadaobj_pxjbox_setattr_showaxeslabels);
        // @description Toggles the display of the x and y axes labels.
        // @includeifflagged DADAOBJ_AXES+DADAOBJ_LABELS
        
        DADAOBJ_CLASS_ATTR_RGBA_SUBSTRUCTURE(c,type, "axeslabelscolor", 0, t_dadaobj, m_grid, t_grid_manager, j_axeslabelscolor);
        CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "axeslabelscolor", 0, "0.4 0.4 0.4 1.");
        CLASS_ATTR_STYLE_LABEL(c, "axeslabelscolor", 0, "rgba", "Axes Labels Color");
        CLASS_ATTR_ACCESSORS(c, "axeslabelscolor", (method)NULL, type == LLLL_OBJ_UI ? (method)dadaobj_jbox_setattr_axeslabelscolor : (method)dadaobj_pxjbox_setattr_axeslabelscolor);
        CLASS_ATTR_CATEGORY(c, "axeslabelscolor", 0, "Color");
        // @description Sets the color of the x and y axes labels.
        // @includeifflagged DADAOBJ_AXES+DADAOBJ_LABELS
        
        DADAOBJ_CLASS_ATTR_DOUBLE_SUBSTRUCTURE(c, type, "axeslabelsfontsize",0, t_dadaobj, m_grid, t_grid_manager, axeslabelsfontsize);
        CLASS_ATTR_STYLE_LABEL(c,"axeslabelsfontsize",0,"text","Axes Labels Font Size");
        CLASS_ATTR_DEFAULT_SAVE(c,"axeslabelsfontsize",0, "10.");
        CLASS_ATTR_CATEGORY(c, "axeslabelsfontsize", 0, "Axes And Grid");
        CLASS_ATTR_ACCESSORS(c, "axeslabelsfontsize", (method)NULL, type == LLLL_OBJ_UI ? (method)dadaobj_jbox_setattr_axeslabelsfontsize : (method)dadaobj_pxjbox_setattr_axeslabelsfontsize);
        // @description Sets the size of the axes labels font.
        // @includeifflagged DADAOBJ_LABELS
        
        DADAOBJ_CLASS_ATTR_SYM_SUBSTRUCTURE(c,type, "xlabel", 0, t_dadaobj, m_grid, t_grid_manager, x_label);
        CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "xlabel", 0, "");
        CLASS_ATTR_STYLE_LABEL(c, "xlabel", 0, "text", "X Axis Label");
        CLASS_ATTR_ACCESSORS(c, "xlabel", (method)NULL, type == LLLL_OBJ_UI ? (method)dadaobj_jbox_setattr_xlabel : (method)dadaobj_pxjbox_setattr_xlabel);
        CLASS_ATTR_CATEGORY(c, "xlabel", 0, "Axes And Grid");
        // @description Sets the label for the x axis.
        // @includeifflagged DADAOBJ_AXES+DADAOBJ_LABELS
        
        DADAOBJ_CLASS_ATTR_SYM_SUBSTRUCTURE(c,type, "ylabel", 0, t_dadaobj, m_grid, t_grid_manager, y_label);
        CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "ylabel", 0, "");
        CLASS_ATTR_STYLE_LABEL(c, "ylabel", 0, "text", "Y Axis Label");
        CLASS_ATTR_ACCESSORS(c, "ylabel", (method)NULL, type == LLLL_OBJ_UI ? (method)dadaobj_jbox_setattr_ylabel : (method)dadaobj_pxjbox_setattr_ylabel);
        CLASS_ATTR_CATEGORY(c, "ylabel", 0, "Axes And Grid");
        // @description Sets the label for the y axis.
        // @includeifflagged DADAOBJ_AXES+DADAOBJ_LABELS
        
    }
    

	if (flags & DADAOBJ_PLAY) {
		DADAOBJ_CLASS_ATTR_DOUBLE_SUBSTRUCTURE(c,type,"playstep",0, t_dadaobj, m_play, t_play_manager, play_step_ms);
		CLASS_ATTR_STYLE_LABEL(c,"playstep",0,"text","Play Step (ms)");
		CLASS_ATTR_DEFAULT_SAVE(c,"playstep",0,"50");
		CLASS_ATTR_CATEGORY(c, "playstep", 0, "Behavior");
		// @description Sets the play step interval in milliseconds.
		// @includeifflagged DADAOBJ_PLAY
        
        if (flags & DADAOBJ_BORDER) {
            DADAOBJ_CLASS_ATTR_RGBA_SUBSTRUCTURE(c,type, "playcolor", 0, t_dadaobj, m_play, t_play_manager, play_color);
            CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "playcolor", 0, "0.34 0.87 0.20 1.");
            CLASS_ATTR_STYLE_LABEL(c, "playcolor", 0, "rgba", "Play Color");
            CLASS_ATTR_CATEGORY(c, "playcolor", 0, "Color");
            // @description Sets the playing color.
            // @includeifflagged DADAOBJ_PLAY+DADAOBJ_BORDER
        }
	}
    
    if (flags & DADAOBJ_EXPORTTOJITTER) {
        DADAOBJ_CLASS_ATTR_SYM_SUBSTRUCTURE(c,type,"jitmatrix",0, t_dadaobj, m_paint, t_paint_manager, jit_destination_matrix);
        CLASS_ATTR_STYLE_LABEL(c,"jitmatrix",0,"text","");
        CLASS_ATTR_DEFAULT_SAVE(c,"jitmatrix",0,"");
        CLASS_ATTR_CATEGORY(c, "jitmatrix", 0, "Behavior");
        // @description Sets the name of a jitter matrix to which the output should be mirrored.
        // @includeifflagged DADAOBJ_EXPORTTOJITTER
    }
        

}

void dadaobj_mutex_lock(t_dadaobj *r_ob)
{
	systhread_mutex_lock(r_ob->l_mutex);
}

void dadaobj_mutex_unlock(t_dadaobj *r_ob)
{
	systhread_mutex_unlock(r_ob->l_mutex);
}


t_object *dadaobj_get_patcher(t_dadaobj *r_ob)
{
    t_object *mypatcher = NULL;
    object_obex_lookup(r_ob->orig_obj, gensym("#P"), &mypatcher);
    return mypatcher;
}


t_object *dadaobj_get_firstview(t_dadaobj *r_ob)
{
    t_object *mypatcher = dadaobj_get_patcher(r_ob);
    if (mypatcher)
        return jpatcher_get_firstview(mypatcher);
    else
        return NULL;
}

long dadaobj_anything_handle_domain_or_range(t_dadaobj *r_ob, t_symbol *router, t_llll *args, long outletnum)
{
    if (outletnum < 0)
        outletnum = r_ob->m_interface.notifications_out_num;
    
    if (router == gensym("getdomain")) {
        // get the displayed domain (only works for first view)
        t_object *view = jpatcher_get_firstview(dadaobj_get_patcher(r_ob));
        
        t_llll *res = llll_get();
        double min, max;
        dadaobj_getdomain(r_ob, view, &min, &max, NULL);
        
        llll_appendsym(res, _llllobj_sym_domain);
        llll_appenddouble(res, min);
        llll_appenddouble(res, max);
        llllobj_outlet_llll(r_ob->orig_obj, LLLL_OBJ_UI, outletnum, res);
        llll_free(res);
        return 1;
        
    } else if (router == gensym("getrange")) {
        // set the displayed domain (only works for first view)
        t_object *view = jpatcher_get_firstview(dadaobj_get_patcher(r_ob));

        double min, max;
        t_llll *res = llll_get();
        dadaobj_getrange(r_ob, view, &min, &max, NULL);
        
        llll_appendsym(res, _llllobj_sym_range);
        llll_appenddouble(res, min);
        llll_appenddouble(res, max);
        llllobj_outlet_llll(r_ob->orig_obj, LLLL_OBJ_UI, outletnum, res);
        llll_free(res);
        return 1;
        
    } else if (router == _llllobj_sym_domain && args->l_size >= 2 && is_hatom_number(&args->l_head->l_hatom) && is_hatom_number(&args->l_head->l_next->l_hatom)) {
        // set the displayed domain
        double min = hatom_getdouble(&args->l_head->l_hatom);
        double max = hatom_getdouble(&args->l_head->l_next->l_hatom);
        
        FOR_ALL_VIEWS(r_ob)
            dadaobj_setdomain(r_ob, view, min, max);
        return 1;

    } else if (router == _llllobj_sym_domain && args->l_size >= 2 && hatom_gettype(&args->l_head->l_hatom) == H_SYM && is_hatom_number(&args->l_head->l_next->l_hatom)) {
        // set the displayed domain start
        double min, max;
        double new_val = hatom_getdouble(&args->l_head->l_next->l_hatom);
        
        if (hatom_getsym(&args->l_head->l_hatom) == _llllobj_sym_start) {
            FOR_ALL_VIEWS(r_ob) {
                dadaobj_getdomain(r_ob, view, &min, &max, NULL);
                dadaobj_setdomain(r_ob, view, new_val, new_val + (max - min));
            }
            return 1;
        } else if (hatom_getsym(&args->l_head->l_hatom) == _llllobj_sym_end) {
            FOR_ALL_VIEWS(r_ob) {
                dadaobj_getdomain(r_ob, view, &min, &max, NULL);
                dadaobj_setdomain(r_ob, view, new_val - (max - min), new_val);
            }
            return 1;
        } else
            return 0;

    } else if (router == _llllobj_sym_range && args->l_size >= 2 && is_hatom_number(&args->l_head->l_hatom) && is_hatom_number(&args->l_head->l_next->l_hatom)) {
        // set the displayed range
        double min = hatom_getdouble(&args->l_head->l_hatom);
        double max = hatom_getdouble(&args->l_head->l_next->l_hatom);
        FOR_ALL_VIEWS(r_ob) dadaobj_setrange(r_ob, view, min, max);
        return 1;

    } else if (router == _llllobj_sym_range && args->l_size >= 2 && hatom_gettype(&args->l_head->l_hatom) == H_SYM && is_hatom_number(&args->l_head->l_next->l_hatom)) {
        // set the displayed domain start
        double min, max;
        double new_val = hatom_getdouble(&args->l_head->l_next->l_hatom);
        
        if (hatom_getsym(&args->l_head->l_hatom) == _llllobj_sym_start) {
            FOR_ALL_VIEWS(r_ob) {
                dadaobj_getrange(r_ob, view, &min, &max, NULL);
                dadaobj_setrange(r_ob, view, new_val, new_val + (max - min));
            }
            return 1;
        } else if (hatom_getsym(&args->l_head->l_hatom) == _llllobj_sym_end) {
            FOR_ALL_VIEWS(r_ob) {
                dadaobj_getrange(r_ob, view, &min, &max, NULL);
                dadaobj_setrange(r_ob, view, new_val - (max - min), new_val);
            }
            return 1;
        } else
            return 0;
    
    }
    return 0;
}




// warning: also modifies <ll>
long dadaobj_parse_export_png_syntax(t_dadaobj *r_ob, t_object *view, t_llll *ll, t_symbol **filename, long *dpi, double *width, double *height, t_pt *exportcenter)
{
    long canceled = 0;
    *dpi = 72;
    *filename = NULL;
    
    double domain_min = 0, domain_max = 100, range_min = 0, range_max = 100;
    if (!view) {
//        view = jpatcher_get_firstview((t_object *)gensym("#P")->s_thing);
        view = jpatcher_get_firstview(r_ob->orig_obj);
    }
    dadaobj_getdomain(r_ob, view, &domain_min, &domain_max, NULL);
    dadaobj_getrange(r_ob, view, &range_min, &range_max, NULL);
    t_pt w = delta_coord_to_delta_pix(r_ob, build_pt(domain_max - domain_min, range_max - range_min));
    
    *width = w.x;
    *height = fabs(w.y);

    *exportcenter = build_pt(-(domain_min + domain_max)/2., -(range_min + range_max)/2.);
    
    t_llll *exportcenter_ll = NULL;
    if (ll->l_head && hatom_gettype(&ll->l_head->l_hatom) == H_SYM) {
        *filename = hatom_getsym(&ll->l_head->l_hatom);
        llll_behead(ll);
    }
    llll_parseargs(r_ob->orig_obj, ll, "siddl", gensym("filename"), &filename, gensym("dpi"), &dpi, gensym("width"), &width, gensym("height"), &height, gensym("center"), &exportcenter_ll);
    if (exportcenter_ll)
        *exportcenter = llll_to_pt(exportcenter_ll);
    
    if (!(*filename) || (*filename) == gensym("")) {      // if no argument supplied, ask for file
        char buf[MAX_PATH_CHARS], fullbuf[MAX_PATH_CHARS];
        short path;
        t_fourcc outtype = 0;
        t_fourcc filetype[] = {'PNG ', 'PNGf'};
        fullbuf[0] = 0;
        strncpy_zero(buf, "export.png", MAX_PATH_CHARS);
        if (saveasdialog_extended(buf, &path, &outtype, filetype, 3)) {    // non-zero: user cancelled
            canceled = 1;
        } else {
            path_topotentialname(path, buf, fullbuf, false);
        }
        if (!strchr(fullbuf, '.')) {
            strncat_zero(fullbuf, ".png", MAX_PATH_CHARS);
        }
        *filename = gensym(fullbuf);
    }

    llll_free(exportcenter_ll);
    
    return canceled;
}


void dadaobj_paint_background(t_dadaobj *r_ob, t_jgraphics *g, t_rect *rect)
{
    t_pt center_pix = coord_to_pix(r_ob, build_pt(rect->width/2., rect->height/2.), r_ob->m_zoom.center_offset);
    
    paint_background(r_ob->orig_obj, g, rect, &r_ob->m_bg.bgcolor, 0.);

    if (r_ob->m_bg.bg_surface) {
        t_jpattern *pat = jgraphics_pattern_create_for_surface(r_ob->m_bg.bg_surface);
        double width = jgraphics_image_surface_get_width(r_ob->m_bg.bg_surface);
        double height = jgraphics_image_surface_get_height(r_ob->m_bg.bg_surface);
        t_jmatrix m;
        jgraphics_matrix_init_translate(&m, -center_pix.x, -center_pix.y);
        jgraphics_matrix_scale(&m, 1./r_ob->m_zoom.zoom.x, 1./r_ob->m_zoom.zoom.y);
        jgraphics_pattern_set_matrix(pat, &m);
        jgraphics_matrix_translate(&m, width/2, height/2.);
        jgraphics_set_source(g, pat);
        jgraphics_paint(g);
        jgraphics_pattern_destroy(pat);
    }
}


void dadaobj_paint_border(t_dadaobj *r_ob, t_jgraphics *g, t_rect *rect)
{
    if (r_ob->m_bg.show_border) {
        paint_border(r_ob->orig_obj, g, rect, r_ob->m_play.is_playing ? &r_ob->m_play.play_color : &r_ob->m_bg.bordercolor, (r_ob->m_interface.has_focus && r_ob->m_bg.show_focus) ? 2.5 : 1, 0.);
    }
}


// buf mus be sized at least 16 chars
void dadaobj_double_to_string(double val, char *buf, int max_decimals, char also_remove_dots_for_ints)
{
    char thisnum[32];
    long j;
    
    if (max_decimals == -1)
        snprintf_zero(thisnum, 32, "%f", val);
    else
        snprintf_zero(thisnum, 32, "%.*f", max_decimals, val);
    
    for (j = MIN(31, strlen(thisnum) - 1); j >= 0; j--) {
        if (thisnum[j] == '0')
            thisnum[j] = 0;
        else if (thisnum[j] == '.' && also_remove_dots_for_ints) {
            thisnum[j] = 0;
            break;
        } else
            break;
    }
    
    snprintf_zero(buf, 16, "%s", thisnum);
}



void dadaobj_paint_grid(t_dadaobj *r_ob, t_object *view, t_dada_force_graphics *force_graphics)
{
    if (r_ob->m_grid.must_update_grid_size) {
        dadaobj_update_grid_size(r_ob, view);
        r_ob->m_grid.must_update_grid_size = false;
    }
    
    if (!r_ob->m_grid.show_grid && !r_ob->m_grid.show_axes && !r_ob->m_grid.show_labels)
        return;
    
    t_rect rect = force_graphics->rect;
    t_pt center = force_graphics->center_pix;
    t_jgraphics *g = view ? jbox_start_layer(r_ob->orig_obj, view, gensym("grid"), rect.width, rect.height) : force_graphics->graphic_context;
    
    t_pt grid_size = dadaobj_get_grid_size(r_ob);
    if (g) {
        if (r_ob->m_grid.show_grid) {
            
            double pix;
            t_pt pix_step = build_pt(grid_size.x * r_ob->m_zoom.zoom.x, grid_size.y * r_ob->m_zoom.zoom.y);
            
            if (pix_step.x <= 0) pix_step.x = 1;
            if (pix_step.y <= 0) pix_step.y = 1;
            
            for (pix = center.x; pix < rect.width; pix += pix_step.x)
                if (pix > 0 && pix < rect.width)
                    paint_line_fast(g, r_ob->m_grid.j_gridcolor, pix, 0, pix, rect.height, 1);
            
            for (pix = center.x - pix_step.x; pix > 0; pix -= pix_step.x)
                if (pix > 0 && pix < rect.width)
                    paint_line_fast(g, r_ob->m_grid.j_gridcolor, pix, 0, pix, rect.height, 1);
            
            for (pix = center.y; pix < rect.height; pix += pix_step.y)
                if (pix > 0 && pix < rect.height)
                    paint_line_fast(g, r_ob->m_grid.j_gridcolor, 0, pix, rect.width, pix, 1);
            
            for (pix = center.y - pix_step.y; pix > 0; pix -= pix_step.y)
                if (pix > 0 && pix < rect.height)
                    paint_line_fast(g, r_ob->m_grid.j_gridcolor, 0, pix, rect.width, pix, 1);
        }
        
        if (r_ob->m_grid.show_axes) {
            t_pt origin = view ? get_center_pix(r_ob, view, NULL) : force_graphics->center_pix;
            const double PAD = 10, PAD_2 = 3;
            
            if (origin.x > -PAD && origin.x < rect.width + PAD)
                paint_arrow(g, r_ob->m_grid.j_axescolor, origin.x, rect.height, origin.x, 0 + PAD_2, 1, DADA_AXIS_ARROW_SIZE, DADA_AXIS_ARROW_SIZE);
            
            if (origin.y > -PAD && origin.y < rect.height + PAD)
                paint_arrow(g, r_ob->m_grid.j_axescolor, 0, origin.y, rect.width - PAD_2, origin.y, 1, DADA_AXIS_ARROW_SIZE, DADA_AXIS_ARROW_SIZE);
        }
        
        if (r_ob->m_grid.show_labels || (r_ob->m_grid.show_axes && r_ob->m_grid.show_axes_labels)) {
            t_pt origin = view ? get_center_pix(r_ob, view, NULL) : force_graphics->center_pix;
            t_pt coord = build_pt(0, 0);
            t_pt pix_step = build_pt(grid_size.x * r_ob->m_zoom.zoom.x, grid_size.y * r_ob->m_zoom.zoom.y);
            t_jfont *jf_labels = jfont_create_debug("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, r_ob->m_grid.labelsfontsize);
            double pix;
            char text[16];
            char labels_are_on_axes = r_ob->m_grid.show_axes;
            
            const double PIX_THRESH = 5 * r_ob->m_grid.labelsfontsize;
            double AXIS_PAD = 3;
            
            double y_pos = CLAMP(origin.y, 0, rect.height);
            double x_pos = CLAMP(origin.x, 0, rect.width);
            long y_align = (y_pos > rect.height/2 ? -1 : 1);
            long x_align = (x_pos > rect.width/2 ? -1 : 1);
            
            if (!labels_are_on_axes) {
                y_pos = rect.height;
                y_align = -1;
                x_pos = 0;
                x_align = 1;
            }
            
            
            if (r_ob->m_grid.show_labels) {
                long x_step = pix_step.x <= 0.01 ? 0 : (pix_step.x < PIX_THRESH ? PIX_THRESH/pix_step.x : 1);
                long y_step = pix_step.y <= 0.01 ? 0 : (pix_step.y < PIX_THRESH ? PIX_THRESH/pix_step.y : 1);
                
                pix_step.x *= x_step;
                pix_step.y *= y_step;
                
                if (pix_step.x > 0) {
                    for (pix = center.x + pix_step.x * labels_are_on_axes, coord = build_pt(x_step * grid_size.x * labels_are_on_axes, 0); pix < rect.width; pix += pix_step.x, coord.x += x_step * grid_size.x)
                        if (pix > 0 && pix < rect.width) {
                            dadaobj_double_to_string(coord.x, text, 4, true);
                            write_text(g, jf_labels, r_ob->m_grid.j_labelscolor, text, pix - 100, y_pos - (y_align < 0) * 100 + (y_align < 0 ? -AXIS_PAD : AXIS_PAD), 200, 100, JGRAPHICS_TEXT_JUSTIFICATION_HCENTERED | (y_align < 0 ? JGRAPHICS_TEXT_JUSTIFICATION_BOTTOM : JGRAPHICS_TEXT_JUSTIFICATION_TOP), true, false);
                        }
                    
                    for (pix = center.x - pix_step.x, coord = build_pt(-x_step * grid_size.x, 0); pix > 0; pix -= pix_step.x, coord.x -= x_step * grid_size.x)
                        if (pix > 0 && pix < rect.width) {
                            dadaobj_double_to_string(coord.x, text, 4, true);
                            write_text(g, jf_labels, r_ob->m_grid.j_labelscolor, text, pix - 100, y_pos - (y_align < 0) * 100 + (y_align < 0 ? -AXIS_PAD : AXIS_PAD), 200, 100, JGRAPHICS_TEXT_JUSTIFICATION_HCENTERED | (y_align < 0 ? JGRAPHICS_TEXT_JUSTIFICATION_BOTTOM : JGRAPHICS_TEXT_JUSTIFICATION_TOP), true, false);
                        }
                }
                
                if (pix_step.y > 0) {
                    for (pix = center.y + pix_step.y * labels_are_on_axes, coord = build_pt(0, -y_step * grid_size.y * labels_are_on_axes); pix < rect.height; pix += pix_step.y, coord.y -= y_step * grid_size.y)
                        if (pix > 0 && pix < rect.height) {
                            dadaobj_double_to_string(coord.y, text, 4, true);
                            write_text(g, jf_labels, r_ob->m_grid.j_labelscolor, text, x_pos - (x_align < 0) * 100 + (x_align < 0 ? -AXIS_PAD : AXIS_PAD), pix - 100, 100, 200, JGRAPHICS_TEXT_JUSTIFICATION_VCENTERED | (x_align < 0 ? JGRAPHICS_TEXT_JUSTIFICATION_RIGHT : JGRAPHICS_TEXT_JUSTIFICATION_LEFT), true, false);
                        }
                    
                    for (pix = center.y - pix_step.y, coord = build_pt(0, y_step * grid_size.y); pix > 0; pix -= pix_step.y, coord.y += y_step * grid_size.y)
                        if (pix > 0 && pix < rect.height) {
                            dadaobj_double_to_string(coord.y, text, 4, true);
                            write_text(g, jf_labels, r_ob->m_grid.j_labelscolor, text, x_pos - (x_align < 0) * 100 + (x_align < 0 ? -AXIS_PAD : AXIS_PAD), pix - 100, 100, 200, JGRAPHICS_TEXT_JUSTIFICATION_VCENTERED | (x_align < 0 ? JGRAPHICS_TEXT_JUSTIFICATION_RIGHT : JGRAPHICS_TEXT_JUSTIFICATION_LEFT), true, false);
                        }
                }
                
                jfont_destroy(jf_labels);
            }
            
            if (r_ob->m_grid.show_axes && r_ob->m_grid.show_axes_labels) {
                t_jfont *jf_labels = jfont_create_debug("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, r_ob->m_grid.axeslabelsfontsize);
                if (r_ob->m_grid.x_label && r_ob->m_grid.x_label->s_name && strlen(r_ob->m_grid.x_label->s_name) > 0)
                    write_text(g, jf_labels, r_ob->m_grid.j_axeslabelscolor, r_ob->m_grid.x_label->s_name, 0, y_align < 0 ? y_pos + AXIS_PAD : 0, rect.width  - AXIS_PAD, y_align < 0 ? rect.height - (y_pos + AXIS_PAD) : y_pos - AXIS_PAD, JGRAPHICS_TEXT_JUSTIFICATION_RIGHT | (y_align < 0 ? JGRAPHICS_TEXT_JUSTIFICATION_TOP : JGRAPHICS_TEXT_JUSTIFICATION_BOTTOM), true, true);
                if (r_ob->m_grid.y_label && r_ob->m_grid.y_label->s_name && strlen(r_ob->m_grid.y_label->s_name) > 0)
                    write_text_in_vertical(g, jf_labels, r_ob->m_grid.j_axeslabelscolor, r_ob->m_grid.y_label->s_name, x_align > 0 ? 0 : x_pos + AXIS_PAD, AXIS_PAD, x_align > 0 ? x_pos - AXIS_PAD : rect.width - (x_pos + AXIS_PAD), rect.height - AXIS_PAD, JGRAPHICS_TEXT_JUSTIFICATION_TOP | (x_align > 0 ? JGRAPHICS_TEXT_JUSTIFICATION_RIGHT : JGRAPHICS_TEXT_JUSTIFICATION_LEFT), 1.);
                jfont_destroy(jf_labels);
            }
        }
        
        
        if (view)
            jbox_end_layer(r_ob->orig_obj, view, gensym("grid"));
    }
    
    if (view)
        jbox_paint_layer(r_ob->orig_obj, view, gensym("grid"), 0., 0.);    // position of the layer
}



/*
void dadaobj_paint_grid_old(t_dadaobj *r_ob, t_object *view, t_dada_force_graphics *force_graphics)
{
    if (!r_ob->m_grid.show_grid && !r_ob->m_grid.show_axes && !r_ob->m_grid.show_labels)
        return;
    
    t_rect rect = force_graphics->rect;
    t_pt center = force_graphics->center_pix;
    t_jgraphics *g = view ? jbox_start_layer(r_ob->orig_obj, view, gensym("grid"), rect.width, rect.height) : force_graphics->graphic_context;
    
    if (g) {
        if (r_ob->m_grid.show_grid) {
            
            double pix;
            t_pt pix_step = build_pt(r_ob->m_grid.grid_size.x * r_ob->m_zoom.zoom.x, r_ob->m_grid.grid_size.y * r_ob->m_zoom.zoom.y);
            
            if (pix_step.x <= 0) pix_step.x = 1;
            if (pix_step.y <= 0) pix_step.y = 1;
            
            for (pix = center.x; pix < rect.width; pix += pix_step.x)
                if (pix > 0 && pix < rect.width)
                    paint_line_fast(g, r_ob->m_grid.j_gridcolor, pix, 0, pix, rect.height, 1);
            
            for (pix = center.x - pix_step.x; pix > 0; pix -= pix_step.x)
                if (pix > 0 && pix < rect.width)
                    paint_line_fast(g, r_ob->m_grid.j_gridcolor, pix, 0, pix, rect.height, 1);
            
            for (pix = center.y; pix < rect.height; pix += pix_step.y)
                if (pix > 0 && pix < rect.height)
                    paint_line_fast(g, r_ob->m_grid.j_gridcolor, 0, pix, rect.width, pix, 1);
            
            for (pix = center.y - pix_step.y; pix > 0; pix -= pix_step.y)
                if (pix > 0 && pix < rect.height)
                    paint_line_fast(g, r_ob->m_grid.j_gridcolor, 0, pix, rect.width, pix, 1);
        }
        
        if (r_ob->m_grid.show_axes) {
            t_pt origin = view ? get_center_pix(r_ob, view, NULL) : force_graphics->center_pix;
            const double PAD = 10, PAD_2 = 3;
            
            if (origin.x > -PAD && origin.x < rect.width + PAD)
                paint_arrow(g, r_ob->m_grid.j_axescolor, origin.x, rect.height, origin.x, 0 + PAD_2, 1, DADA_AXIS_ARROW_SIZE, DADA_AXIS_ARROW_SIZE);

            if (origin.y > -PAD && origin.y < rect.height + PAD)
                paint_arrow(g, r_ob->m_grid.j_axescolor, 0, origin.y, rect.width - PAD_2, origin.y, 1, DADA_AXIS_ARROW_SIZE, DADA_AXIS_ARROW_SIZE);
        }
        
        if (r_ob->m_grid.show_labels || (r_ob->m_grid.show_axes && r_ob->m_grid.show_axes_labels)) {
            t_pt origin = view ? get_center_pix(r_ob, view, NULL) : force_graphics->center_pix;
            t_pt coord = build_pt(0, 0);
            t_pt pix_step = build_pt(r_ob->m_grid.grid_size.x * r_ob->m_zoom.zoom.x, r_ob->m_grid.grid_size.y * r_ob->m_zoom.zoom.y);
            t_jfont *jf_labels = jfont_create_debug("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, r_ob->m_grid.labelsfontsize);
            double pix;
            char text[16];
            char labels_are_on_axes = r_ob->m_grid.show_axes;
            
            const double PIX_THRESH = 5 * r_ob->m_grid.labelsfontsize;
            double AXIS_PAD = 3;
            
            double y_pos = CLAMP(origin.y, 0, rect.height);
            double x_pos = CLAMP(origin.x, 0, rect.width);
            long y_align = (y_pos > rect.height/2 ? -1 : 1);
            long x_align = (x_pos > rect.width/2 ? -1 : 1);
            
            if (!labels_are_on_axes) {
                y_pos = rect.height;
                y_align = -1;
                x_pos = 0;
                x_align = 1;
            }
            
            
            if (r_ob->m_grid.show_labels) {
                long x_step = pix_step.x <= 0.01 ? 0 : (pix_step.x < PIX_THRESH ? PIX_THRESH/pix_step.x : 1);
                long y_step = pix_step.y <= 0.01 ? 0 : (pix_step.y < PIX_THRESH ? PIX_THRESH/pix_step.y : 1);
                
                pix_step.x *= x_step;
                pix_step.y *= y_step;
                
                if (pix_step.x > 0) {
                    for (pix = center.x + pix_step.x * labels_are_on_axes, coord = build_pt(x_step * r_ob->m_grid.grid_size.x * labels_are_on_axes, 0); pix < rect.width; pix += pix_step.x, coord.x += x_step * r_ob->m_grid.grid_size.x)
                        if (pix > 0 && pix < rect.width) {
                            dadaobj_double_to_string(coord.x, text, 4, true);
                            write_text(g, jf_labels, r_ob->m_grid.j_labelscolor, text, pix - 100, y_pos - (y_align < 0) * 100 + (y_align < 0 ? -AXIS_PAD : AXIS_PAD), 200, 100, JGRAPHICS_TEXT_JUSTIFICATION_HCENTERED | (y_align < 0 ? JGRAPHICS_TEXT_JUSTIFICATION_BOTTOM : JGRAPHICS_TEXT_JUSTIFICATION_TOP), true, false);
                        }
                    
                    for (pix = center.x - pix_step.x, coord = build_pt(-x_step * r_ob->m_grid.grid_size.x, 0); pix > 0; pix -= pix_step.x, coord.x -= x_step * r_ob->m_grid.grid_size.x)
                        if (pix > 0 && pix < rect.width) {
                            dadaobj_double_to_string(coord.x, text, 4, true);
                            write_text(g, jf_labels, r_ob->m_grid.j_labelscolor, text, pix - 100, y_pos - (y_align < 0) * 100 + (y_align < 0 ? -AXIS_PAD : AXIS_PAD), 200, 100, JGRAPHICS_TEXT_JUSTIFICATION_HCENTERED | (y_align < 0 ? JGRAPHICS_TEXT_JUSTIFICATION_BOTTOM : JGRAPHICS_TEXT_JUSTIFICATION_TOP), true, false);
                        }
                }
                
                if (pix_step.y > 0) {
                    for (pix = center.y + pix_step.y * labels_are_on_axes, coord = build_pt(0, -y_step * r_ob->m_grid.grid_size.y * labels_are_on_axes); pix < rect.height; pix += pix_step.y, coord.y -= y_step * r_ob->m_grid.grid_size.y)
                        if (pix > 0 && pix < rect.height) {
                            dadaobj_double_to_string(coord.y, text, 4, true);
                            write_text(g, jf_labels, r_ob->m_grid.j_labelscolor, text, x_pos - (x_align < 0) * 100 + (x_align < 0 ? -AXIS_PAD : AXIS_PAD), pix - 100, 100, 200, JGRAPHICS_TEXT_JUSTIFICATION_VCENTERED | (x_align < 0 ? JGRAPHICS_TEXT_JUSTIFICATION_RIGHT : JGRAPHICS_TEXT_JUSTIFICATION_LEFT), true, false);
                        }
                    
                    for (pix = center.y - pix_step.y, coord = build_pt(0, y_step * r_ob->m_grid.grid_size.y); pix > 0; pix -= pix_step.y, coord.y += y_step * r_ob->m_grid.grid_size.y)
                        if (pix > 0 && pix < rect.height) {
                            dadaobj_double_to_string(coord.y, text, 4, true);
                            write_text(g, jf_labels, r_ob->m_grid.j_labelscolor, text, x_pos - (x_align < 0) * 100 + (x_align < 0 ? -AXIS_PAD : AXIS_PAD), pix - 100, 100, 200, JGRAPHICS_TEXT_JUSTIFICATION_VCENTERED | (x_align < 0 ? JGRAPHICS_TEXT_JUSTIFICATION_RIGHT : JGRAPHICS_TEXT_JUSTIFICATION_LEFT), true, false);
                        }
                }
                
                jfont_destroy(jf_labels);
            }
            
            if (r_ob->m_grid.show_axes && r_ob->m_grid.show_axes_labels) {
                t_jfont *jf_labels = jfont_create_debug("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, r_ob->m_grid.axeslabelsfontsize);
                if (r_ob->m_grid.x_label && r_ob->m_grid.x_label->s_name && strlen(r_ob->m_grid.x_label->s_name) > 0)
                    write_text(g, jf_labels, r_ob->m_grid.j_axeslabelscolor, r_ob->m_grid.x_label->s_name, 0, y_align < 0 ? y_pos + AXIS_PAD : 0, rect.width  - AXIS_PAD, y_align < 0 ? rect.height - (y_pos + AXIS_PAD) : y_pos - AXIS_PAD, JGRAPHICS_TEXT_JUSTIFICATION_RIGHT | (y_align < 0 ? JGRAPHICS_TEXT_JUSTIFICATION_TOP : JGRAPHICS_TEXT_JUSTIFICATION_BOTTOM), true, true);
                if (r_ob->m_grid.y_label && r_ob->m_grid.y_label->s_name && strlen(r_ob->m_grid.y_label->s_name) > 0)
                    write_text_in_vertical(g, jf_labels, r_ob->m_grid.j_axeslabelscolor, r_ob->m_grid.y_label->s_name, x_align > 0 ? 0 : x_pos + AXIS_PAD, AXIS_PAD, x_align > 0 ? x_pos - AXIS_PAD : rect.width - (x_pos + AXIS_PAD), rect.height - AXIS_PAD, JGRAPHICS_TEXT_JUSTIFICATION_TOP | (x_align > 0 ? JGRAPHICS_TEXT_JUSTIFICATION_RIGHT : JGRAPHICS_TEXT_JUSTIFICATION_LEFT), 1.);
                jfont_destroy(jf_labels);
            }
        }
        
        
        if (view)
            jbox_end_layer(r_ob->orig_obj, view, gensym("grid"));
    }
    
    if (view)
        jbox_paint_layer(r_ob->orig_obj, view, gensym("grid"), 0., 0.);	// position of the layer
}
*/

void dadaobj_jbox_set_state_and_free_llll(t_object *x, t_llll *ll)
{
    if (ll) {
        t_dadaobj *r_ob = &((t_dadaobj_jbox *)x)->d_ob;
        r_ob->set_state(x, ll);
        llll_free(ll);
    } else {
        object_error(x, "Can't set object state.");
    }
}

void dadaobj_jbox_read(t_dadaobj_jbox *x, t_symbol *s, long argc, t_atom *argv)
{
    t_dadaobj *r_ob = &x->d_ob;
    if (r_ob->set_state) {
        t_symbol *filename = NULL;
        if ((argc >= 1) && (atom_gettype(argv) == A_SYM))
            filename = atom_getsym(argv);
        llll_read(r_ob->orig_obj, filename, (read_fn)dadaobj_jbox_set_state_and_free_llll);
        jbox_invalidate_layer(r_ob->orig_obj, NULL, gensym("room"));
    } else {
        object_error(r_ob->orig_obj, "Read method is not supported.");
    }
}


void dadaobj_jbox_write(t_dadaobj_jbox *x, t_symbol *s, long argc, t_atom *argv)
{
    t_dadaobj *r_ob = &x->d_ob;
    if (r_ob->get_state) {
        t_llll *ll;
        t_symbol *filename = NULL;
        if ((argc >= 1) && (atom_gettype(argv) == A_SYM))
            filename = atom_getsym(argv);
        ll =  r_ob->get_state(r_ob->orig_obj);
        llll_writenative(r_ob->orig_obj, filename, ll);
    } else {
        object_error(r_ob->orig_obj, "Writing methods are not supported.");
    }
}

void dadaobj_jbox_writetxt(t_dadaobj_jbox *x, t_symbol *s, long argc, t_atom *argv)
{
    t_dadaobj *r_ob = &x->d_ob;
    if (r_ob->get_state) {
        t_llll *arguments = llllobj_parse_llll((t_object *) x, LLLL_OBJ_VANILLA, NULL, argc, argv, LLLL_PARSE_CLONE);
        t_llll *state_ll = r_ob->get_state(r_ob->orig_obj);
        llll_writetxt(r_ob->orig_obj, state_ll, arguments, BACH_DEFAULT_MAXDECIMALS, 0, "\t", -1, LLLL_T_NONE, LLLL_TE_SMART, LLLL_TB_SMART);
    } else {
        object_error(r_ob->orig_obj, "Writing methods are not supported.");
    }
}

void dadaobj_jbox_readsinglesymbol(t_dadaobj_jbox *x, t_symbol *s, long argc, t_atom *argv)
{
    t_atom a;
    char *text = NULL;
    long size;
    atom_gettext_debug(argc, argv, &size, &text, 0);
    if (size > 0) {
        t_symbol *s = gensym(text);
        atom_setsym(&a, s);
        bach_freeptr(text);
        dadaobj_jbox_read(x, NULL, 1, &a);
    }
}


t_atom_long dadaobj_jbox_acceptsdrag(t_dadaobj_jbox *x, t_object *drag, t_object *view)
{
    if (jdrag_matchdragrole(drag, gensym("imagefile"), 0) && x->d_ob.flags & DADAOBJ_BGIMAGE) {
        jdrag_box_add(drag, (t_object *)x, gensym("bgimage"));
        return true;
    } else if (true) {
        jdrag_box_add(drag, (t_object *)x, gensym("readsinglesymbol"));
        return true;
    }
    return false;
}


long dadaitem_identifier_eq(t_dadaitem_identifier id1, t_dadaitem_identifier id2)
{
    if (id1.type != id2.type)
        return 0;
    
    if (id1.idx != id2.idx)
        return 0;
    
    if (id1.secondary_idx != id2.secondary_idx)
        return 0;

    if (id1.tertiary_idx != id2.tertiary_idx)
        return 0;
    
    return 1;
}



t_dada_force_graphics dadaobj_get_forced_graphics_from_view(t_dadaobj *r_ob, t_object *view)
{
    t_rect rect;
    t_jgraphics *g = (t_jgraphics*) patcherview_get_jgraphics(view);
    jbox_get_rect_for_view(r_ob->orig_obj, view, &rect);
    
    t_dada_force_graphics out;
    out.graphic_context = g;
    out.rect = rect;
    out.zoom = r_ob->m_zoom.zoom;
    out.center_offset = r_ob->m_zoom.center_offset;
    out.center_pix = get_center_pix(r_ob, view, &rect);
    
    return out;
}



void dadaobj_paint_to_jitter_matrix(t_dadaobj *r_ob, t_symbol *matrix_name, long width, long height)
{
    t_object *x = r_ob->orig_obj;
    long w = width, h = height;
    t_rect draw_rect = build_rect(0, 0, w, h);
    t_jsurface *draw_surface = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, w, h);
    t_jgraphics *draw_g = jgraphics_create(draw_surface);
    
    jgraphics_set_source_rgba(draw_g, 0, 0, 0, 1.);
    //    jgraphics_image_surface_draw(g, bg_slots_surface, rect_oo, rect_oo);
    
    t_dada_force_graphics force_graphics;
    force_graphics.graphic_context = draw_g;
    force_graphics.rect = draw_rect;
    force_graphics.center_offset = r_ob->m_zoom.center_offset;
    force_graphics.zoom = r_ob->m_zoom.zoom;
    force_graphics.center_pix = coord_to_pix(r_ob, build_pt(draw_rect.width/2., draw_rect.height/2.), r_ob->m_zoom.center_offset);
    
    (r_ob->m_paint.paint_ext)(x, NULL, &force_graphics);
    
    //find matrix
    t_jrgba color;
    void *matrix = jit_object_findregistered(matrix_name);
    if (matrix && jit_object_method(matrix, _jit_sym_class_jit_matrix)) {
        long savelock;
        t_jit_matrix_info minfo;
        char *bp,*p;
        
        savelock = (long) jit_object_method(matrix,_jit_sym_lock,1);
        jit_object_method(matrix,_jit_sym_getinfo,&minfo);
        jit_object_method(matrix,_jit_sym_getdata,&bp);
        
        if (!bp || minfo.dimcount < 2 || (minfo.planecount != 1 && minfo.planecount != 4)) {
            object_error((t_object *)x, "Error with jitter matrix");
            object_error((t_object *)x, "   Please check that it exists, that it has at least 2 dimensions and either 1 or 4 planes.");
            jit_object_method(matrix,_jit_sym_lock,savelock);
        } else {
            
            if (minfo.dim[0] != w || minfo.dim[1] != h) {
                minfo.dim[0] = w;
                minfo.dim[1] = h;
                if (jit_object_method(matrix, _jit_sym_setinfo, &minfo))
                    object_warn((t_object *)x, "Cannot resize jitter matrix automatically");
                jit_object_method(matrix,_jit_sym_getinfo,&minfo);
                jit_object_method(matrix,_jit_sym_getdata,&bp);
            }
            
            if (!bp || minfo.dimcount < 2 || (minfo.planecount != 1 && minfo.planecount != 4)) {
                object_error((t_object *)x, "Error with jitter matrix");
                object_error((t_object *)x, "   Please check that it exists, that it has at least 2 dimensions and either 1 or 4 planes.");
                jit_object_method(matrix,_jit_sym_lock,savelock);
            } else {
                
                long actual_w = minfo.dim[0], actual_h = minfo.dim[1];
                
                if (minfo.type==_jit_sym_char) {
                    for (long i = 0; i < actual_w; i++) {
                        for (long j = 0; j < actual_h; j++) {
                            jgraphics_image_surface_get_pixel(draw_surface, i, j, &color);
                            p = bp + (j)*minfo.dimstride[1] + (i)*minfo.dimstride[0];
                            if (minfo.planecount == 1) {
                                t_jhsla color_hsla = rgba_to_hsla(color);
                                *((uchar *)p) = round(color_hsla.lightness * color_hsla.alpha * 255);
                            } else {
                                *((uchar *)p) = round(color.alpha * 255);
                                *(((uchar *)p) + 1) = round(color.red * 255);
                                *(((uchar *)p) + 2) = round(color.green * 255);
                                *(((uchar *)p) + 3) = round(color.blue * 255);
                            }
                        }
                    }
                    
                } else if (minfo.type==_jit_sym_long) {
                    /*                bp += plane*4;
                     for (i=0; i<argc; i++,j++) {
                     p = bp + (j/minfo.dim[0])*minfo.dimstride[1] + (j%minfo.dim[0])*minfo.dimstride[0];
                     *((t_int32 *)p) = jit_atom_getlong(argv+i);
                     } */
                } else if (minfo.type==_jit_sym_float32) {
                    for (long i = 0; i < actual_w; i++) {
                        for (long j = 0; j < actual_h; j++) {
                            jgraphics_image_surface_get_pixel(draw_surface, i, j, &color);
                            p = bp + (j)*minfo.dimstride[1] + (i)*minfo.dimstride[0];
                            if (minfo.planecount == 1) {
                                t_jhsla color_hsla = rgba_to_hsla(color);
                                *((float *)p) = color_hsla.lightness * color_hsla.alpha;
                            } else {
                                *(((float *)p)) = color.alpha;
                                *(((float *)p) + 1) = color.red;
                                *(((float *)p) + 2) = color.green;
                                *(((float *)p) + 3) = color.blue;
                            }
                        }
                    }
                    
                    /*                bp += x->plane*4;
                     for (i=0; i<argc; i++,j++) {
                     p = bp + (j/minfo.dim[0])*minfo.dimstride[1] + (j%minfo.dim[0])*minfo.dimstride[0];
                     *((float *)p) = jit_atom_getfloat(argv+i);
                     } */
                } else if (minfo.type==_jit_sym_float64) {
                    
                    for (long i = 0; i < actual_w; i++) {
                        for (long j = 0; j < actual_h; j++) {
                            jgraphics_image_surface_get_pixel(draw_surface, i, j, &color);
                            p = bp + (j)*minfo.dimstride[1] + (i)*minfo.dimstride[0];
                            if (minfo.planecount == 1) {
                                t_jhsla color_hsla = rgba_to_hsla(color);
                                *((double *)p) = color_hsla.lightness * color_hsla.alpha;
                            } else {
                                *((double *)p) = color.alpha;
                                *(((double *)p) + 1) = color.red;
                                *(((double *)p) + 2) = color.green;
                                *(((double *)p) + 3) = color.blue;
                            }
                        }
                    }
                    
                    /*                bp += x->plane*8;
                     for (i=0; i<argc; i++,j++) {
                     p = bp + (j/minfo.dim[0])*minfo.dimstride[1] + (j%minfo.dim[0])*minfo.dimstride[0];
                     *((double *)p) = jit_atom_getfloat(argv+i);
                     } */
                }
            }
            
            jit_object_method(matrix,_jit_sym_lock,savelock);
        }
    } else {
        object_error((t_object *)x, "Can't find jitter matrix!");
        //        jit_error_sym(x,_jit_sym_err_calculate);
    }
    
    
    jgraphics_destroy(draw_g);
    jgraphics_surface_destroy(draw_surface);
}




void dadaobj_paint(t_dadaobj *r_ob, t_object *view)
{
    t_dada_force_graphics forced_graphics = dadaobj_get_forced_graphics_from_view(r_ob, view);
    
    r_ob->m_geometry.last_used_view_width_pix = forced_graphics.rect.width;
    r_ob->m_geometry.last_used_view_height_pix = forced_graphics.rect.height;
    

    (r_ob->m_paint.paint_ext)(r_ob->orig_obj, view, &forced_graphics);
    
    if (r_ob->m_paint.jit_destination_matrix && strlen(r_ob->m_paint.jit_destination_matrix->s_name) > 0)
        dadaobj_paint_to_jitter_matrix(r_ob, r_ob->m_paint.jit_destination_matrix, forced_graphics.rect.width, forced_graphics.rect.height);
    
    if (r_ob->m_paint.notify_when_painted)
        dadaobj_send_painted_notification(r_ob);
}







void get_filename_extension(char *filename, char *ext, char also_truncate_filename)
{
    char *dot = strrchr(filename, '.');
    if (!dot || dot == filename)
        ext[0] = 0;
    else {
        strncpy_zero(ext, dot + 1, MAX_FILENAME_CHARS);
        if (also_truncate_filename)
            *dot = 0;
    }
}


void dadaobj_jbox_exportimage_do(t_dadaobj_jbox *x, t_symbol *s, long ac, t_atom *av)
{
    t_llll *arguments = (t_llll *) atom_getobj(av);
    t_dadaobj *r_ob = &x->d_ob;
    char ok = true;
    double height = -1, width = -1; // x->d_ob.m_geometry.last_used_view_height_pix, width = x->d_ob.m_geometry.last_used_view_width_pix;
    long dpi = 72;
    t_symbol *filename_sym = NULL, *type_sym = NULL;
    t_pt center = x->d_ob.m_zoom.center_offset, zoom = x->d_ob.m_zoom.zoom;
    t_llll *center_ll = NULL, *zoom_ll = NULL;
    char cooked = 0;
    t_pt center_prev = center;
    t_pt zoom_prev = zoom;
    double width_pix = -1, height_pix = -1;

    llll_parseargs_and_attrs(r_ob->orig_obj, arguments, "ssiddddll",
                             _sym_filename, &filename_sym,
                             _sym_type, &type_sym,
                             gensym("dpi"), &dpi,
                             gensym("height"), &height,
                             gensym("width"), &width,
                             gensym("pixelwidth"), &width_pix,
                             gensym("pixelheight"), &height_pix,
                             gensym("center"), &center_ll,
                             gensym("zoom"), &zoom_ll
                             );
    
    //    dev_llll_print(arguments, NULL, 0, 2, NULL);
    if (zoom_ll || center_ll)
        cooked = 1;
    
    if (center_ll) {
        center = llll_to_pt(center_ll);
        llll_free(center_ll);
    }

    if (zoom_ll) {
        // zoom is defined.
        if (zoom_ll->l_size == 1)
            zoom.x = zoom.y = hatom_getdouble(&zoom_ll->l_head->l_hatom);
        else
            zoom = llll_to_pt(zoom_ll);
        zoom.x *= 100; zoom.y *= 100; // zoom were given in percentage
        llll_free(zoom_ll);
        
        if (height_pix > 0)
            height = height_pix/zoom.y;
        else if (height > 0)
            height_pix = height * zoom.y;
        if (width_pix > 0)
            width = width_pix/zoom.y;
        else if (width > 0)
            width_pix = width * zoom.y;
    } else {
        if (height > 0 && height_pix > 0) {
            zoom.y = height_pix/height;
        } else if (height > 0) {
            height_pix = height*zoom.y;
        } else if (height_pix > 0 ) {
            height = height_pix/zoom.y;
        }
        if (width > 0 && width_pix > 0) {
            zoom.x = width_pix/width;
        } else if (width > 0) {
            width_pix = width*zoom.x;
        } else if (width_pix > 0 ) {
            width = width_pix/zoom.x;
        }
    }
    
    if (height_pix < 0)
        height_pix = x->d_ob.m_geometry.last_used_view_height_pix;
    if (width_pix < 0)
        width_pix = x->d_ob.m_geometry.last_used_view_width_pix;

    if (!cooked && (height_pix != x->d_ob.m_geometry.last_used_view_height_pix || width_pix != x->d_ob.m_geometry.last_used_view_width_pix))
        cooked = 1;
    
//    object_post((t_object *)x, "1 %s", filename_sym ? filename_sym->s_name : "<none>" );
    if (arguments->l_size) {
        filename_sym = hatom_getsym(&arguments->l_head->l_hatom);
        if (filename_sym)
            llll_destroyelem(arguments->l_head);
    }

//    object_post((t_object *)x, "2 %s", filename_sym ? filename_sym->s_name : "<none>" );

    if (!filename_sym) {
        t_fourcc filetype = 'PICT', outtype;
        char filename_temp[MAX_PATH_CHARS];
        char full_filename_temp[MAX_PATH_CHARS];
        full_filename_temp[0] = 0;
        short path = 0;
        if (saveasdialog_extended(filename_temp, &path, &outtype, &filetype, 1) == 0) {
            path_topotentialname(path, filename_temp, full_filename_temp, 0);
            if (full_filename_temp[0])
                filename_sym = gensym(full_filename_temp);
        }
    }
    
    if (filename_sym) {
        char new_temp_filename[MAX_FILENAME_CHARS];
        char extension[MAX_FILENAME_CHARS];
        get_filename_extension(filename_sym->s_name, extension, false);
        if (strcasecmp(extension, "png") != 0) {
            snprintf_zero(new_temp_filename, MAX_FILENAME_CHARS, "%s.png", filename_sym->s_name);
            filename_sym = gensym(new_temp_filename);
        }
    }
    
    if (!type_sym) {
        if (filename_sym) {
            char extension[MAX_FILENAME_CHARS];
            get_filename_extension(filename_sym->s_name, extension, false);
            if (strcasecmp(extension, "png") == 0)
                type_sym = gensym("png");
            else if (strcasecmp(extension, "jpg") == 0 || strcasecmp(extension, "jpeg") == 0)
                type_sym = gensym("jpeg");
            else
                type_sym = gensym("png");
        }
    }
    
    if (filename_sym) {
        
        if (cooked) {
            // you never know
            r_ob->m_zoom.zoom = zoom;
            r_ob->m_zoom.center_offset = center;
        }
        
        // getting output path
        short path = path_getdefault();
        char filename[MAX_FILENAME_CHARS];
        char extension[MAX_FILENAME_CHARS];
        filename[0] = 0;
        path_frompotentialpathname(filename_sym->s_name, &path, filename);
        if (!filename[0])
            snprintf(filename, MAX_FILENAME_CHARS, "%s", filename_sym->s_name);
        get_filename_extension(filename, extension, false);

//        double w = delta_coord_to_delta_pix(r_ob, build_pt(width, 0)).x, h = delta_coord_to_delta_pix(r_ob, build_pt(0, height)).y;
        double w = width_pix, h = height_pix;
        t_rect shot_rect = build_rect(0, 0, w, h);
        t_jsurface *shot_surface = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, w, h);
        t_jgraphics *shot_g = jgraphics_create(shot_surface);
        
        jgraphics_set_source_rgba(shot_g, 0, 0, 0, 1.);
        
        t_dada_force_graphics force_graphics;
        force_graphics.graphic_context = shot_g;
        force_graphics.rect = shot_rect;
        force_graphics.center_offset = center; //x->d_ob.m_zoom.center_offset;
        force_graphics.center_pix = coord_to_pix(&x->d_ob, build_pt(force_graphics.rect.width/2., force_graphics.rect.height/2.), force_graphics.center_offset);
        force_graphics.zoom = zoom; //x->d_ob.m_zoom.zoom;
        
        (x->d_ob.m_paint.paint_ext)((t_object *)x, NULL, &force_graphics);
            
        if (type_sym && strcasecmp(extension, "png") == 0) {
            if (jgraphics_image_surface_writepng(shot_surface, filename, path, dpi) != MAX_ERR_NONE) {
                object_error((t_object *)x, "Error while exporting image.");
            }
        } else if (type_sym && (strcasecmp(extension, "jpeg") == 0 || strcasecmp(extension, "jpg") == 0)) {
            if (jgraphics_image_surface_writejpeg(shot_surface, filename, path) != MAX_ERR_NONE) {
                object_error((t_object *)x, "Error while exporting image.");
            }
        }
        
        jgraphics_destroy(shot_g);
        jgraphics_surface_destroy(shot_surface);
        
        if (cooked) {
            // you never know
            r_ob->m_zoom.zoom = zoom_prev;
            r_ob->m_zoom.center_offset = center_prev;
        }

    } else {
        ok = false;
    }
    
    if (arguments)
        llll_free(arguments);
}

void dadaobj_jbox_exportimage(t_dadaobj_jbox *x, t_symbol *s, long argc, t_atom *argv)
{
    t_atom av;
    t_llll *arguments = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, NULL, argc, argv, LLLL_PARSE_CLONE);
    atom_setobj(&av, arguments);
    defer(x, (method)dadaobj_jbox_exportimage_do, s, 1, &av);
}


void dadaobj_jbox_paintjit(t_dadaobj_jbox *x, t_symbol *matrix_name)
{
    dadaobj_paint_to_jitter_matrix(&x->d_ob, matrix_name, x->d_ob.m_geometry.last_used_view_width_pix, x->d_ob.m_geometry.last_used_view_height_pix);
}
