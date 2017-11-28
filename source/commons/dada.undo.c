/**
	@file
	dada.undo.c
	Undo-redo mechanism header for dada library

	by Daniele Ghisi
*/

#include "dada.undo.h"


t_symbol *combine_string_with_symbol_for_undo(const char *str, t_symbol *sym, char make_sym_plural)
{
	char buf[1000];
	snprintf_zero(buf, 1000, make_sym_plural ? "%s %ss" : "%s %s", str, sym->s_name);
	return gensym(buf);
}


void call_function(t_dadaobj *r_ob, e_dada_func_types type, method func, t_llll *args, t_hatom *return_value)
{
	t_object *ob = r_ob->orig_obj;
	switch (type) {
		case DADA_FUNC_v_oX:
			((void (*)(t_object *object, t_llll *ll)) func)(ob, hatom_getllll(&args->l_head->l_hatom));
			return_value->h_type = H_NULL;
			break;
		case DADA_FUNC_v_dX:
			((void (*)(t_dadaobj *object, t_llll *ll)) func)(r_ob, hatom_getllll(&args->l_head->l_hatom));
			return_value->h_type = H_NULL;
			break;
		case DADA_FUNC_v_otX:
			((void (*)(t_object *object, e_dadaitem_types type, t_llll *ll)) func)(ob, (e_dadaitem_types)hatom_getlong(&args->l_head->l_hatom), hatom_getllll(&args->l_head->l_next->l_hatom));
			return_value->h_type = H_NULL;
			break;
		case DADA_FUNC_v_dtX:
			((void (*)(t_dadaobj *object, e_dadaitem_types type, t_llll *ll)) func)(r_ob, (e_dadaitem_types)hatom_getlong(&args->l_head->l_hatom), hatom_getllll(&args->l_head->l_next->l_hatom));
			return_value->h_type = H_NULL;
			break;
        case DADA_FUNC_v_dtXf:
            ((void (*)(t_dadaobj *object, e_dadaitem_types type, t_llll *ll, long flags)) func)(r_ob, (e_dadaitem_types)hatom_getlong(&args->l_head->l_hatom), hatom_getllll(&args->l_head->l_next->l_hatom), 0);
            return_value->h_type = H_NULL;
            break;
		case DADA_FUNC_v_diX:
			((void (*)(t_dadaobj *object, long ID, t_llll *ll)) func)(r_ob, hatom_getlong(&args->l_head->l_hatom), hatom_getllll(&args->l_head->l_next->l_hatom));
			return_value->h_type = H_NULL;
			break;
		case DADA_FUNC_X_o:
			hatom_setllll(return_value, ((t_llll *(*)(t_object *object)) func)(ob));
			break;
		case DADA_FUNC_X_d:
			hatom_setllll(return_value, ((t_llll *(*)(t_dadaobj *object)) func)(r_ob));
			break;
		case DADA_FUNC_X_ot:
			hatom_setllll(return_value, ((t_llll *(*)(t_object *object, e_dadaitem_types type)) func)(ob, (e_dadaitem_types)hatom_getlong(&args->l_head->l_hatom)));
			break;
		case DADA_FUNC_X_dt:
			hatom_setllll(return_value, ((t_llll *(*)(t_dadaobj *object, e_dadaitem_types type)) func)(r_ob, (e_dadaitem_types)hatom_getlong(&args->l_head->l_hatom)));
			break;
		case DADA_FUNC_X_di:
			hatom_setllll(return_value, ((t_llll *(*)(t_dadaobj *object, long ID)) func)(r_ob, hatom_getlong(&args->l_head->l_hatom)));
			break;
		default:
			break;
	}
}

long function_type_to_set_variable_position(t_object *ob, e_dada_func_types type, char ignore_starting_object)
{
	switch (type) {
		case DADA_FUNC_v_oX:
		case DADA_FUNC_v_dX:
			return ignore_starting_object ? 1 : 2;
		case DADA_FUNC_v_otX:
		case DADA_FUNC_v_diX:
		case DADA_FUNC_v_dtX:
        case DADA_FUNC_v_dtXf:
			return ignore_starting_object ? 2 : 3;
		default:
			return 0;
	}
}

void undo_set_set_args_from_get_function(t_dadaobj *r_ob, t_dada_undo_tick *tick)
{
	// Setting the current get-value as parameter for the set function
	t_hatom h;
    if (tick->op_type == DADA_UNDO_OP_DELETION)
        h.h_type = H_NULL;
    else
        call_function(r_ob, tick->u_get_type, tick->u_get_function, tick->u_get_args, &h);
	if (h.h_type != H_NULL) {
		long idx = function_type_to_set_variable_position(r_ob->orig_obj, tick->u_set_type, true);
        if (idx > 0) {
//            if (hatom_gettype(h) == H_LLLL && !hatom_getllll(h))
			hatom_subs(tick->u_set_args, idx, &h);
        }
	}
}

t_dada_undo_tick *undo_redo_tick_new(t_dadaobj *r_ob, e_dada_func_types set_type, method set_func, t_llll *set_args, 
									 e_dada_func_types get_type, method get_func, t_llll *get_args, e_dada_undo_operation_type op_type,
                                     e_dadaitem_types type, long dadaitem_ID)
{
	t_dada_undo_tick *tick = (t_dada_undo_tick *)bach_newptr(sizeof(t_dada_undo_tick));
	tick->u_set_function = set_func;
	tick->u_set_args = set_args ? set_args : llll_get();
	tick->u_set_type = set_type;
	tick->u_get_function = get_func;
	tick->u_get_args = get_args ? get_args : llll_get();
	tick->u_get_type = get_type;
	tick->op_type = op_type;
    tick->dadaitem_type = type;
    tick->dadaitem_ID = dadaitem_ID;
	
	undo_set_set_args_from_get_function(r_ob, tick);

	return tick;
}

t_dada_undo_tick *undo_redo_tick_reverse(t_dadaobj *r_ob, t_dada_undo_tick *orig_tick)
{
	t_dada_undo_tick *tick = (t_dada_undo_tick *)bach_newptr(sizeof(t_dada_undo_tick));
	tick->u_set_function = orig_tick->u_set_function;
	tick->u_set_args = orig_tick->u_set_args ? llll_clone(orig_tick->u_set_args) : NULL;
	tick->u_set_type = orig_tick->u_set_type;
	tick->u_get_function = orig_tick->u_get_function;
	tick->u_get_args = orig_tick->u_get_args ? llll_clone(orig_tick->u_get_args) : NULL;
	tick->u_get_type = orig_tick->u_get_type;
    switch (orig_tick->op_type) {
        case DADA_UNDO_OP_CREATION:
            tick->op_type = DADA_UNDO_OP_DELETION;
            break;
        case DADA_UNDO_OP_DELETION:
            tick->op_type = DADA_UNDO_OP_CREATION;
            break;
        default:
            tick->op_type = orig_tick->op_type;
            break;
    }
    tick->dadaitem_ID = orig_tick->dadaitem_ID;
    tick->dadaitem_type = orig_tick->dadaitem_type;
	return tick;
}


void undo_redo_tick_free(t_dada_undo_tick *tick)
{
	llll_free(tick->u_set_args);
	llll_free(tick->u_get_args);
	bach_freeptr(tick);
}

void undo_redo_free_all_ticks(t_undo_manager *man, e_dada_undo_redo what)
{
	t_llll *ll = (what == DADA_UNDO ? man->undo : man->redo);
	t_llllelem *elem;
	if (ll)
		for (elem = ll->l_head; elem; elem = elem->l_next)
			if (hatom_gettype(&elem->l_hatom) == H_OBJ)
				undo_redo_tick_free((t_dada_undo_tick *)hatom_getobj(&elem->l_hatom));
}

void undo_redo_clear(t_undo_manager *man, e_dada_undo_redo what)
{
	undo_redo_free_all_ticks(man, what);
	llll_clear(what == DADA_UNDO ? man->undo : man->redo);
	if (what == DADA_UNDO)
		man->num_undo_steps = 0;
	else
		man->num_redo_steps = 0;
}


void undo_redo_tick_push(t_undo_manager *man, e_dada_undo_redo what, t_dada_undo_tick *tick)
{
	llll_prependobj(what == DADA_UNDO ? man->undo : man->redo, tick, 0, WHITENULL_llll);
}

void undo_redo_marker_push(t_undo_manager *man, e_dada_undo_redo what, t_symbol *operation)
{
#ifdef DADA_DEBUG_UNDO
    post("- Undo marker added: %s", operation ? operation->s_name : "Unknown");
#endif

	llll_prependsym(what == DADA_UNDO ? man->undo : man->redo, operation, 0, WHITENULL_llll);
	if (what == DADA_UNDO)
		man->num_undo_steps ++;
	else
		man->num_redo_steps ++;
}

void undo_redo_tick_and_marker_push(t_undo_manager *man, e_dada_undo_redo what, t_dada_undo_tick *tick, t_symbol *operation)
{
	undo_redo_tick_push(man, what, tick);
	undo_redo_marker_push(man, what, operation);
}

void undo_tick_and_marker_push(t_undo_manager *man, t_dada_undo_tick *tick, t_symbol *operation)
{
	undo_redo_tick_push(man, DADA_UNDO, tick);
	undo_redo_marker_push(man, DADA_UNDO, operation);
}

void redo_tick_and_marker_push(t_undo_manager *man, t_dada_undo_tick *tick, t_symbol *operation)
{
	undo_redo_tick_push(man, DADA_REDO, tick);
	undo_redo_marker_push(man, DADA_REDO, operation);
}

void undo_check_max_num_steps(t_undo_manager *man)
{
	// check number of undo steps
	while (man->num_undo_steps > man->max_num_steps && man->undo->l_tail) {
		// deleting old undo steps
		if (hatom_gettype(&man->undo->l_tail->l_hatom) == H_SYM)
			man->num_undo_steps--;
		llll_betail(man->undo);
	}
}

char undo_are_there_free_undo_ticks(t_undo_manager *man)
{
	if (man->undo && man->undo->l_head && hatom_gettype(&man->undo->l_head->l_hatom) != H_SYM)
		return 1;
	return 0;
}

void undo_add_interface_step(t_dadaobj *r_ob, e_dada_func_types set_type, method set_func, t_llll *set_args, 
							 e_dada_func_types get_type, method get_func, t_llll *get_args, e_dada_undo_operation_type op_type, t_symbol *operation,
                             e_dadaitem_types type, long dadaitem_ID, char add_undo_marker)
{
	t_undo_manager *man = &r_ob->m_undo;
	t_interface_manager *interface_man = &r_ob->m_interface;
    long id = dadaitem_class_get_id(&r_ob->m_classes, type);
    char single_elems_undo = id >= 0 && r_ob->m_classes.di_class[id].data_single_get_fn ? true : false;

    r_ob->m_interface.has_been_modified_while_mousedown = true;

	if ((man->max_num_steps > 0) && (single_elems_undo || !(interface_man->has_been_dragged && undo_are_there_free_undo_ticks(man)))) {
		
#ifdef DADA_DEBUG_UNDO
        post("- Undo tick added for dadaitem type: %s, id: %ld", id >= 0 ? r_ob->m_classes.di_class[id].label->s_name : "Unknown", dadaitem_ID);
#endif
		// clear redo list
		undo_redo_clear(man, DADA_REDO);
		
		// add undo tick
		undo_redo_tick_push(man, DADA_UNDO, undo_redo_tick_new(r_ob, set_type, set_func, set_args, get_type, get_func, get_args, op_type, type, dadaitem_ID));
		
		// add undo marker
		if (!interface_man->mouse_is_down && add_undo_marker)
			undo_redo_marker_push(man, DADA_UNDO, operation);
		else
			man->need_push_marker = operation;
		
		// check number of undo steps, possibly deleting the oldest ones if needed
		undo_check_max_num_steps(man);
        
        undo_redo_post_debug(r_ob);
		
	} 
	
	if (interface_man->continuously_send_changebang)
		dadaobj_send_changedbang(r_ob);
}


void undo_add_interface_step_for_whole_dadaobj(t_dadaobj *r_ob, t_symbol *operation)
{
	undo_add_interface_step(r_ob, DADA_FUNC_v_oX, (method)r_ob->set_state, NULL, DADA_FUNC_X_o, (method)r_ob->get_state, NULL, DADA_UNDO_OP_MODIFICATION, operation);
}

// type must NOT be 0 unless r_ob is a dadaobj (whole undo)
void undo_add_interface_step_for_dadaitem_class(t_dadaobj *r_ob, e_dadaitem_types type, t_symbol *operation)
{
	t_item_class_manager *class_man = &r_ob->m_classes;
	if (type == 0) {
		undo_add_interface_step_for_whole_dadaobj(r_ob, operation);
	} else {
		long id = dadaitem_class_get_id(class_man, type);
		if (id >= 0) {
			t_dadaitem_class *c = &class_man->di_class[id];
			if (!c->dirty)
				undo_add_interface_step(r_ob, c->data_set_type, c->data_set_fn, llll_clone(c->data_set_args), 
									c->data_get_type, c->data_get_fn, llll_clone(c->data_get_args), DADA_UNDO_OP_MODIFICATION, operation, type, 0);
			c->dirty = true;
		}
	}
}

// type must NOT be 0 unless r_ob is a dadaobj (whole undo)
void undo_add_interface_step_for_dadaitem(t_dadaobj *r_ob, t_dadaitem *item, e_dada_undo_operation_type op_type, t_symbol *operation, char add_undo_marker)
{
	
	if (!item->dirty) {
		long id = dadaitem_class_get_id(&r_ob->m_classes, item->type);
		t_dadaitem_class *c = &r_ob->m_classes.di_class[id];

		if (c->data_single_set_fn && c->data_single_get_fn) {
			//element-specific undo
			t_llll *data_single_set_args = llll_clone(c->data_single_set_args);
			t_llll *data_single_get_args = llll_clone(c->data_single_get_args);
			if (c->data_single_set_type == DADA_FUNC_v_diX) {
				if (!data_single_set_args)
					data_single_set_args = llll_get();
				llll_appendlong(data_single_set_args, item->ID, 0, WHITENULL_llll);
			}
			if (c->data_single_get_type == DADA_FUNC_X_di) {
				if (!data_single_get_args)
					data_single_get_args = llll_get();
				llll_appendlong(data_single_get_args, item->ID, 0, WHITENULL_llll);
			}
			undo_add_interface_step(r_ob, c->data_single_set_type, c->data_single_set_fn, data_single_set_args, 
									c->data_single_get_type, c->data_single_get_fn, data_single_get_args, op_type, operation, item->type, item->ID, add_undo_marker);
			item->dirty = true;
			llll_appendobj(r_ob->m_undo.dirty_items, item, 0, WHITENULL_llll);
		} else
			// whole class undo
			undo_add_interface_step_for_dadaitem_class(r_ob, item->type, operation);
	}
}


void undo_redo_post_debug_do(t_dadaobj *r_ob, e_dada_undo_redo what)
{
    t_llllelem *elem;
    t_undo_manager *man = &r_ob->m_undo;
    t_llll *what_ll = (what == DADA_UNDO ? man->undo : man->redo);
    post("Current %s list:", what == DADA_UNDO ? "undo" : "redo");
    for (elem = what_ll->l_head; elem; elem = elem->l_next) {
        if (hatom_gettype(&elem->l_hatom) == H_OBJ) {
            t_dada_undo_tick *tick = (t_dada_undo_tick *)hatom_getobj(&elem->l_hatom);
            char *bufget = NULL, *bufset = NULL;
            t_symbol *label = dadaitem_class_get_label(&r_ob->m_classes, tick->dadaitem_type);
            post("    %s(%s, %s%ld)", tick->op_type == DADA_UNDO_OP_CREATION ? "↑" : (tick->op_type == DADA_UNDO_OP_DELETION ? "↓" : "~"), label->s_name, tick->dadaitem_ID > 0 ? "ID=" : "all elements-ID=", tick->dadaitem_ID);
            if (tick->u_get_args) {
                llll_to_text_buf(tick->u_get_args, &bufget, 0, BACH_DEFAULT_MAXDECIMALS, LLLL_T_NONE, LLLL_TE_SMART, LLLL_TB_SMART, NULL);
                post("       get args: %s", bufget);
                bach_freeptr(bufget);
            }
            if (tick->u_set_args) {
                llll_to_text_buf(tick->u_set_args, &bufset, 0, BACH_DEFAULT_MAXDECIMALS, LLLL_T_NONE, LLLL_TE_SMART, LLLL_TB_SMART, NULL);
                post("       set args: %s", bufset);
                bach_freeptr(bufset);
            }
        } else if (hatom_gettype(&elem->l_hatom) == H_SYM){
            post("  • %s", hatom_getsym(&elem->l_hatom)->s_name);
        } else {
            post("  !!! Wrong element !!!");
        }
    }
}

void undo_redo_post_debug(t_dadaobj *r_ob)
{
#ifdef DADA_DEBUG_UNDO
    undo_redo_post_debug_do(r_ob, DADA_UNDO);
    undo_redo_post_debug_do(r_ob, DADA_REDO);
#endif
}


void undo_redo_perform(t_dadaobj *r_ob, e_dada_undo_redo what)
{
	t_undo_manager *man = &r_ob->m_undo;
	t_interface_manager *interface_man = &r_ob->m_interface;
	t_object *ob = r_ob->orig_obj;
	e_dada_undo_redo inv_what = (what == DADA_UNDO ? DADA_REDO : DADA_UNDO);
	
	t_llll *what_ll = (what == DADA_UNDO ? man->undo : man->redo);
	while (what_ll->l_head && hatom_gettype(&what_ll->l_head->l_hatom) != H_SYM) {
		if (hatom_gettype(&what_ll->l_head->l_hatom) == H_OBJ)
			bach_freeptr(hatom_getobj(&what_ll->l_head->l_hatom));
		llll_behead(what_ll);
	}
	
	if (!what_ll->l_head) {
		if (man->verbose_undo) {
			if (what == DADA_UNDO)
				object_warn(ob, "Can't Undo");
			else
				object_warn(ob, "Can't Redo");
		}
		return;
	}
	
	t_symbol *marker = hatom_getsym(&what_ll->l_head->l_hatom);
	llll_behead(what_ll);
	
	while (what_ll->l_head && hatom_gettype(&what_ll->l_head->l_hatom) == H_OBJ) { // perform ticks
		t_dada_undo_tick *tick = (t_dada_undo_tick *)hatom_getobj(&what_ll->l_head->l_hatom);
//		if (llll_check(tick->u_get_args))
//			post("FF!");
//		if (llll_check(tick->u_set_args))
//			post("FF2!");
		t_dada_undo_tick *inv_tick = undo_redo_tick_reverse(r_ob, tick);
		t_hatom rv;
		
		// we get the current state for redo
		undo_set_set_args_from_get_function(r_ob, inv_tick);

		// we recreate the dadaitem if needed
        if (tick->op_type == DADA_UNDO_OP_CREATION)
            dadaitem_add_with_ID(r_ob, tick->dadaitem_type, tick->dadaitem_ID);

        if (tick->op_type == DADA_UNDO_OP_DELETION)
            // we delete the item
            dadaitem_delete_from_ID(r_ob, tick->dadaitem_type, tick->dadaitem_ID);
        else
            // we set the previous state
            call_function(r_ob, tick->u_set_type, tick->u_set_function, tick->u_set_args, &rv);

        // possibly freeing the result value
        if (hatom_gettype(&rv) == H_LLLL)
			llll_free(hatom_getllll(&rv));
		
		undo_redo_tick_push(man, inv_what, inv_tick);
		
		undo_redo_tick_free(tick);
		llll_behead(what_ll);
	}
	
	man->post_process_fn(r_ob->orig_obj);

	if (what == DADA_UNDO)
		man->num_undo_steps --;
	else
		man->num_redo_steps --;
	
	undo_redo_marker_push(man, inv_what, marker);
	
	if (man->verbose_undo) {
		char buf[200];
		snprintf_zero(buf, 200, "%s %s", what == DADA_UNDO ? "Undo" : "Redo", marker->s_name);
		object_post(ob, buf);
	}
    
    undo_redo_post_debug(r_ob);
    
	if (r_ob->m_interface.send_bang_upon_undo)
		dadaobj_send_changedbang(r_ob);
}

t_llll *dadaitem_get_as_llll_ID(t_dadaobj *r_ob, long ID)
{
	t_dadaitem *item = (t_dadaitem *)shashtable_retrieve(r_ob->IDtable, ID);
	if (item)
		return dadaitem_get_as_llll(r_ob, item);
    return llll_get();
//    return NULL;
}


void dadaitem_set_from_llll_ID(t_dadaobj *r_ob, long ID, t_llll *ll)
{
	t_dadaitem *item = (t_dadaitem *)shashtable_retrieve(r_ob->IDtable, ID);
	if (item)
		dadaitem_set_from_llll(r_ob, item, ll, 0);
}


void dadaitem_add_with_ID(t_dadaobj *r_ob, e_dadaitem_types type, long ID)
{
    dadaitem_add(r_ob, type, build_pt(0, 0), 0, 0, DADA_BLACK, NULL, 0, 0, ID);
}

void dadaitem_delete_from_ID(t_dadaobj *r_ob, e_dadaitem_types type, long ID)
{
    t_dadaitem *item = (t_dadaitem *)shashtable_retrieve(r_ob->IDtable, ID);
    if (item)
        dadaitem_delete(r_ob, type, dadaitem_get_index(r_ob, item), 0);
}


void dadaobj_add_undo_marker_if_needed(t_dadaobj *r_ob)
{
    if (r_ob->flags & DADAOBJ_UNDO && r_ob->m_undo.need_push_marker) {
        char changed_something = undo_are_there_free_undo_ticks(&r_ob->m_undo);
        if (changed_something) {
            undo_redo_marker_push(&r_ob->m_undo, DADA_UNDO, r_ob->m_undo.need_push_marker);
            if (r_ob->flags & DADAOBJ_CHANGEDBANG)
                dadaobj_send_changedbang(r_ob);
        }
        undo_redo_post_debug(r_ob);
    }
}