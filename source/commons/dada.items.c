/**
	@file
	dada.items.c
	Function to handle the dada items

	by Daniele Ghisi
*/


#include "dada.items.h"
#include "dada.cursors.h"
#include "dada.interface.h"
#include "dada.popupmenu.h"
#include "dada.undo.h"
#include "dada.geometry.h"


// r_ob can be null if must_assign_ID is false
void dadaitem_init(t_dadaobj *r_ob, t_dadaitem *item, e_dadaitem_types type, long flags, char must_assign_ID, long forced_ID)
{
	item->type = type;
	item->flags = flags;
    item->internal_flags = 0;
	if (must_assign_ID && !forced_ID) 
		item->ID = shashtable_insert(r_ob->IDtable, item);
	else if (must_assign_ID) {
		shashtable_insert_with_key(r_ob->IDtable, item, forced_ID, true);
		item->ID = forced_ID;
	} else
		item->ID = 0;
	item->preselected = item->selected = NULL;
	item->dirty = 0;
}


// only appends flags if needed
void dadaitem_append_flags_to_llll(t_llll *ll, t_dadaitem *item, char even_if_flags_are_0)
{
	if (even_if_flags_are_0 || item->flags) {
		t_llll *flags = llll_get();
		llll_appendsym(flags, gensym("flags"), 0, WHITENULL_llll);
		if (item->flags & D_LOCK)
			llll_appendsym(flags, gensym("lock"), 0, WHITENULL_llll);
		if (item->flags & D_MUTE)
			llll_appendsym(flags, gensym("mute"), 0, WHITENULL_llll);
		if (item->flags & D_SOLO)
			llll_appendsym(flags, gensym("solo"), 0, WHITENULL_llll);
		if (item->flags & D_INACTIVE)
			llll_appendsym(flags, gensym("inactive"), 0, WHITENULL_llll);
        if (item->flags & D_SOLITARY)
            llll_appendsym(flags, gensym("solitary"), 0, WHITENULL_llll);
		llll_appendllll(ll, flags, 0, WHITENULL_llll);
	}
}


char dadaitem_check_solos_iterfn(t_dadaobj *r_ob, t_dadaitem *item, void *data)
{
	if (item->flags & D_SOLO) {
		*((long *)data) = 1;
		return 1;
	}
	return 0;
}


void dadaobj_update_solos(t_dadaobj *r_ob)
{
    if (r_ob->update_solos) // custom solo update
        (r_ob->update_solos)(r_ob->orig_obj);
    else {
        long has_solos = 0;
        dadaobj_dadaitem_iterate_all(r_ob, dadaitem_check_solos_iterfn, &has_solos);
        r_ob->m_play.has_solos = has_solos;
    }
}

long dadaitem_get_flags_from_llll(t_llll *ll, char *need_check_solos)
{
	long flags = 0;
	t_llllelem *elem;
	
	for (elem = ll->l_head; elem; elem = elem->l_next) {
		if (hatom_gettype(&elem->l_hatom) == H_SYM) {
			t_symbol *sym = hatom_getsym(&elem->l_hatom);
			if (sym == gensym("lock"))
				flags |= D_LOCK;
			else if (sym == gensym("mute"))
				flags |= D_MUTE;
			else if (sym == gensym("solo")) {
				flags |= D_SOLO;
                if (need_check_solos)
                    *need_check_solos = true;
            } else if (sym == gensym("inactive")) {
                flags |= D_INACTIVE;
            } else if (sym == gensym("solitary")) {
                flags |= D_SOLITARY;
            }
		}
	}
	return flags;
}

void dadaitem_set_flags_from_llll(t_dadaobj *r_ob, t_llll *ll, t_dadaitem *item, char also_update_solos)
{
	char need_check_solos = false;
	
	item->flags = dadaitem_get_flags_from_llll(ll, &need_check_solos);
	
	if (also_update_solos && need_check_solos)
		dadaobj_update_solos(r_ob);
}

void dadaitem_set_flags_from_llllelem(t_dadaobj *r_ob, t_llllelem *elem, t_dadaitem *item, char also_update_solos)
{
	item->flags = 0;
	if (elem && hatom_gettype(&elem->l_hatom) == H_LLLL)
		dadaitem_set_flags_from_llll(r_ob, hatom_getllll(&elem->l_hatom), item, also_update_solos);
}

void dadaitem_popup_change_flag_fn(t_dadaobj *r_ob, t_symbol *label, const t_llll *address) 
{
	t_dadaitem *item = r_ob->m_popup_menu.curr_popup_item;
	char need_check_solos = false;
	
	if (item) {
		if (label == gensym("Lock"))
			item->flags |= D_LOCK;
		else if (label == gensym("Mute"))
			item->flags |= D_MUTE; 
		else if (label == gensym("Solo")) {
			item->flags |= D_SOLO;
			need_check_solos = true;
		} else if (label == gensym("Make Inactive"))
			item->flags |= D_INACTIVE;
		else if (label == gensym("Unlock"))
			item->flags &= ~D_LOCK;
		else if (label == gensym("Unmute"))
			item->flags &= ~D_MUTE;
		else if (label == gensym("Unsolo")) {
			item->flags &= ~D_SOLO;
			need_check_solos = true;
		} else if (label == gensym("Make Active"))
			item->flags &= ~D_INACTIVE;
	}
	
    if (need_check_solos)
		dadaobj_update_solos(r_ob);
    
    dadaobj_invalidate_and_redraw(r_ob);

    undo_add_interface_step_for_dadaitem(r_ob, item, DADA_UNDO_OP_MODIFICATION, label);
}



char popup_unset_flags_for_dadaitem_iterfn(t_dadaobj *r_ob, t_dadaitem *item, void *data)
{
	long flags = *(long *)data;
	if (flags & D_LOCK)
		item->flags &= ~D_LOCK;
	else if (flags & D_SOLO)
		item->flags &= ~D_SOLO;
	else if (flags & D_MUTE)
		item->flags &= ~D_MUTE;
	else if (flags & D_INACTIVE)
		item->flags &= ~D_INACTIVE;
	return 0;
}


void popup_unset_flags_for_all_dadaitems_fn(t_dadaobj *r_ob, t_symbol *label, const t_llll *address)
{
	long flag = 0;
    char need_update_solos = false;
    
	undo_add_interface_step_for_whole_dadaobj(r_ob, label);
	
	if (label == gensym("No Lock"))
		flag = D_LOCK;
	else if (label == gensym("No Mute"))
		flag = D_MUTE; 
    else if (label == gensym("No Solo")) {
		flag = D_SOLO;
        need_update_solos = true;
    }
	else if (label == gensym("No Inactive"))
		flag = D_INACTIVE;
	
	dadaobj_dadaitem_iterate_all(r_ob, popup_unset_flags_for_dadaitem_iterfn, &flag);
    
    if (need_update_solos)
        dadaobj_update_solos(r_ob);
}



char dadaitem_should_be_played(t_dadaobj *r_ob, t_dadaitem *item)
{
	return (!(item->flags & D_MUTE) && (((item->flags & D_SOLO) > 0) || (!r_ob->m_play.has_solos)) ? true : false);
//	return ((((item->flags & D_SOLO) > 0) || (!r_ob->m_play.has_solos && !(item->flags & D_MUTE))) ? true : false);
}







/// **********************************///
///         DADAITEM CLASSES          ///
/// **********************************///



/////////// DECLARING A CLASS

void dadaobj_dadaitem_class_alloc(t_dadaobj *r_ob, e_dadaitem_types type, t_symbol *name, t_symbol *label, 
								  e_dadaitem_alloc_type alloc_type, long parent_class_id, char element_have_ID,
								  long element_size, long structure_offset, long max_num_items, long *num_items_field,
								  e_dada_func_types data_set_type, method data_set_fn, t_llll *data_set_args,
								  e_dada_func_types data_get_type, method data_get_fn, t_llll *data_get_args,
								  method postprocess_fn, method identifier_to_dadaitem_fn, method free_fn, char selectable, char include_in_background)
{
	t_item_class_manager *man = &r_ob->m_classes;
	long num_di_class = man->num_di_classes;
	if (num_di_class < DADA_MAX_DADAITEM_CLASSES) {
		man->di_class[num_di_class].type = type;
		man->di_class[num_di_class].name = name;
		man->di_class[num_di_class].label = label;
		man->di_class[num_di_class].element_size = element_size;
		man->di_class[num_di_class].struct_offset = structure_offset;
		man->di_class[num_di_class].num_items = 0;
        man->di_class[num_di_class].num_items_field = num_items_field;
		man->di_class[num_di_class].max_num_items = max_num_items;
        man->di_class[num_di_class].struct_offset = structure_offset;
		man->di_class[num_di_class].element_have_ID = element_have_ID;
		
		
		man->di_class[num_di_class].alloc_type = alloc_type;
		man->di_class[num_di_class].parent_class_id = parent_class_id;
		
//		void *obj = r_ob->orig_obj;

		// allocating memory
		if (alloc_type == DADA_ITEM_ALLOC_ARRAY)
			*(t_dadaitem **)(((long)(r_ob->orig_obj)) + structure_offset) = (t_dadaitem *)bach_newptr(max_num_items * element_size);
		else if (alloc_type == DADA_ITEM_ALLOC_OBJLLLL)
			*((t_llll **)(((long)(r_ob->orig_obj)) + structure_offset)) = llll_get();
		
		man->di_class[num_di_class].data_set_type =  data_set_type;
		man->di_class[num_di_class].data_set_fn = data_set_fn;
		man->di_class[num_di_class].data_set_args = data_set_args;
		man->di_class[num_di_class].data_get_type = data_get_type;
		man->di_class[num_di_class].data_get_fn = data_get_fn;
		man->di_class[num_di_class].data_get_args = data_get_args;

		man->di_class[num_di_class].data_single_set_type =  DADA_FUNC_X_o;
		man->di_class[num_di_class].data_single_set_fn = NULL;
		man->di_class[num_di_class].data_single_set_args = NULL;
		man->di_class[num_di_class].data_single_get_type = DADA_FUNC_X_o;
		man->di_class[num_di_class].data_single_get_fn = NULL;
		man->di_class[num_di_class].data_single_get_args = NULL;
		
		man->di_class[num_di_class].postprocess_fn = postprocess_fn;
		
		man->di_class[num_di_class].identifier_to_dadaitem_fn = identifier_to_dadaitem_fn;
		man->di_class[num_di_class].free_fn = free_fn;
		
		man->di_class[num_di_class].selectable = selectable;
        man->di_class[num_di_class].include_in_background = include_in_background;
		
		man->di_class[num_di_class].dirty = false;
		
		man->num_di_classes++;
	}
}

void dadaobj_dadaitem_class_ezalloc(t_dadaobj *r_ob, e_dadaitem_types type, t_symbol *name, t_symbol *label, 
									e_dadaitem_alloc_type alloc_type, long parent_class_id, char element_have_ID,
									long element_size, long structure_offset, long max_num_items, long *num_items_field,
									method postprocess_fn, method free_fn, char selectable, char include_in_background)
{
	t_llll *arg1 = llll_get();
	t_llll *arg2 = llll_get();
	llll_appendlong(arg1, type, 0, WHITENULL_llll);
	llll_appendlong(arg2, type, 0, WHITENULL_llll);
	dadaobj_dadaitem_class_alloc(r_ob, type, name, label, alloc_type, parent_class_id, element_have_ID,
								 element_size, structure_offset, max_num_items, num_items_field,
								 DADA_FUNC_v_dtXf, (method)dadaitem_class_set_from_llll, arg1,
								 DADA_FUNC_X_dt, (method)dadaitem_class_get_as_llll, arg2,
								 postprocess_fn, NULL, free_fn, selectable, include_in_background);
}

void dadaobj_dadaitem_class_add_single_set_get_func(t_dadaobj *r_ob, e_dadaitem_types type,
								  e_dada_func_types data_single_set_type, method data_single_set_fn, t_llll *data_single_set_args,
								  e_dada_func_types data_single_get_type, method data_single_get_fn, t_llll *data_single_get_args)
{
	t_item_class_manager *man = &r_ob->m_classes;
	long num_di_class = dadaitem_class_get_id(man, type);
	man->di_class[num_di_class].data_single_set_type =  data_single_set_type;
	man->di_class[num_di_class].data_single_set_fn = data_single_set_fn;
	man->di_class[num_di_class].data_single_set_args = data_single_set_args;
	man->di_class[num_di_class].data_single_get_type = data_single_get_type;
	man->di_class[num_di_class].data_single_get_fn = data_single_get_fn;
	man->di_class[num_di_class].data_single_get_args = data_single_get_args;
}



e_dadaitem_types dadaitem_class_name_to_type(t_item_class_manager *man, t_symbol *name)
{
	long i;
	for (i = 0; i < man->num_di_classes; i++)
		if (man->di_class[i].name == name)
			return man->di_class[i].type;
	return DADAITEM_TYPE_NONE;
}

t_symbol *dadaitem_class_get_label(t_item_class_manager *man, e_dadaitem_types type)
{
    long i;
    for (i = 0; i < man->num_di_classes; i++)
        if (man->di_class[i].type == type)
            return man->di_class[i].label;
    return _llllobj_sym_none;
}

long dadaitem_class_get_id(t_item_class_manager *man, e_dadaitem_types type)
{
	long i;
	for (i = 0; i < man->num_di_classes; i++)
		if (man->di_class[i].type == type)
			return i;
	return -1;
}

// only make sense with DADA_ITEM_ALLOC_OBJLLLL alloc type
t_llll *dadaitem_get_class_llll(t_dadaobj *r_ob, long class_id)
{
	t_llll *ll = *((t_llll **)(((long)(r_ob->orig_obj)) + r_ob->m_classes.di_class[class_id].struct_offset));
	return ll;
}


// obtain chain of nested classes for a given "leaf"
void get_class_nesting(t_dadaobj *r_ob, long class_id, long *nesting)
{
	long i = 1, j;
	long temp[5];
	temp[0] = class_id;
	
	while (r_ob->m_classes.di_class[class_id].parent_class_id && i < 4) 
		temp[i++] = class_id = r_ob->m_classes.di_class[class_id].parent_class_id;
	
	for (j = 0; j < 4 && temp[i-j-1] != 0; j++)
		nesting[j] = temp[i-j-1];
	nesting[j] = 0;
}


t_dadaitem *dadaitem_class_get_nth_item(t_dadaobj *r_ob, long class_id, long n)
{
	t_item_class_manager *man = &r_ob->m_classes;
    long max = man->di_class[class_id].max_num_items;
    if (man->di_class[class_id].alloc_type == DADA_ITEM_ALLOC_ARRAY_DONT && man->di_class[class_id].num_items_field)
        max = *(man->di_class[class_id].num_items_field);
	if (n >= 0 && n < max) {
		switch (man->di_class[class_id].alloc_type) {
			case DADA_ITEM_ALLOC_ARRAY:
            case DADA_ITEM_ALLOC_ARRAY_DONT:
			{
				t_dadaitem *first = *((t_dadaitem **)(((long)(r_ob->orig_obj)) + man->di_class[class_id].struct_offset));
				return (t_dadaitem *)move_pointer_forward(first, n * man->di_class[class_id].element_size);
			}
				break;
			case DADA_ITEM_ALLOC_OBJLLLL:
			{
				t_llll *ll = dadaitem_get_class_llll(r_ob, class_id);
				t_llllelem *elem = llll_getindex(ll, n+1, I_STANDARD);
				if (elem)
					return (t_dadaitem *)hatom_getobj(&elem->l_hatom);	
			}
				break;
			default:
				break;
		}
	}
	return NULL;
}



long dadaitem_class_get_num_items_from_id(t_item_class_manager *man, long classid)
{
    return (man->di_class[classid].num_items_field ? *(man->di_class[classid].num_items_field) : man->di_class[classid].num_items);
}

long dadaitem_class_get_num_items(t_item_class_manager *man, e_dadaitem_types type)
{
	long id = dadaitem_class_get_id(man, type);
	if (id >= 0)
        return dadaitem_class_get_num_items_from_id(man, id);
	return 0;
}





void postprocess_for_dadaitem_class(t_dadaobj *r_ob, long class_id)
{
	t_item_class_manager *man = &r_ob->m_classes;
	if (man->di_class[class_id].postprocess_fn)
		(man->di_class[class_id].postprocess_fn)(r_ob);
}



char dadaitem_class_clear_free_fn(t_dadaobj *r_ob, t_dadaitem *item, void *data)
{
	long id = *(long *)data;
	(r_ob->m_classes.di_class[id].free_fn)((t_dadaobj *)r_ob, item);
	return 0;
}

void dadaitem_class_clear(t_dadaobj *r_ob, t_item_class_manager *class_man, t_interface_manager *interface_man, t_undo_manager *undo_man, 
						  e_dadaitem_types type, long flags)
{
	long id = dadaitem_class_get_id(class_man, type);
	if (id >= 0) {
		if (flags & DIA_UNDO)
			undo_add_interface_step_for_dadaitem_class(r_ob, type, combine_string_with_symbol_for_undo("Clear", class_man->di_class[id].label, false));
		
		// free all elements
		if (class_man->di_class[id].free_fn)
			dadaobj_dadaitem_iterate_for_class(r_ob, type, dadaitem_class_clear_free_fn, &id);
		
		// resync selection and preselection
		t_llllelem *elem, *next_elem;
		for (elem = interface_man->selection->l_head; elem; elem = next_elem) {
			t_dadaitem *sel = (t_dadaitem *)hatom_getobj(&elem->l_hatom);
			if (sel->type == type)
				llll_destroyelem(elem);
			next_elem = elem->l_next;
		}
		for (elem = interface_man->preselection->l_head; elem; elem = next_elem) {
			t_dadaitem *sel = (t_dadaitem *)hatom_getobj(&elem->l_hatom);
			if (sel->type == type)
				llll_destroyelem(elem);
			next_elem = elem->l_next;
		}
		
		class_man->di_class[id].num_items = 0;
        if (class_man->di_class[id].alloc_type == DADA_ITEM_ALLOC_OBJLLLL)
            llll_clear(dadaitem_get_class_llll(r_ob, id));

		if (flags & DIA_POSTPROCESS)
			postprocess_for_dadaitem_class(r_ob, id);
	}
}

void dadaobj_dadaitem_class_clear(t_dadaobj *r_ob, e_dadaitem_types type, long flags)
{
	dadaitem_class_clear(r_ob, &r_ob->m_classes, &r_ob->m_interface, &r_ob->m_undo, type, flags);
}

char dadaitem_class_get_dirty(t_item_class_manager *man, e_dadaitem_types type)
{
	long id = dadaitem_class_get_id(man, type);
	if (id >= 0) 
		return man->di_class[id].dirty;
	return false;
}



void dada_class_clean_all_dirty(t_item_class_manager *man)
{
	long i;
	for (i = 0; i < man->num_di_classes; i++)
		man->di_class[i].dirty = false;
}

void dadaobj_clean_all_dirty(t_dadaobj *r_ob)
{
	t_llllelem *elem;
	dada_class_clean_all_dirty(&r_ob->m_classes);
	for (elem = r_ob->m_undo.dirty_items->l_head; elem; elem = elem->l_next) {
		t_dadaitem *item = (t_dadaitem *)hatom_getobj(&elem->l_hatom);
		item->dirty = false;
	}
	llll_clear(r_ob->m_undo.dirty_items);
}





/////////// CREATION AND DELETION OF ITEMS
		

t_dadaitem *dadaitem_new(t_dadaobj *r_ob, e_dadaitem_types type)
{
	long id = dadaitem_class_get_id(&r_ob->m_classes, type);
	t_dadaitem *it = (t_dadaitem *)bach_newptrclear(r_ob->m_classes.di_class[id].element_size);
	return it;
}

long dadaitem_add(t_dadaobj *r_ob, e_dadaitem_types type, t_pt coord, double width, double height, t_jrgba color, t_symbol *name, long item_flags, char flags, long forced_id)
{
	long id = dadaitem_class_get_id(&r_ob->m_classes, type);
	if (id >= 0) {
		long num = dadaitem_class_get_num_items_from_id(&r_ob->m_classes, id);
		if (num + 1 < r_ob->m_classes.di_class[id].max_num_items) {
			
			char single_elems_undo = r_ob->m_classes.di_class[id].data_single_get_fn ? true : false;
			
			if (flags & DIA_UNDO && !single_elems_undo)
				undo_add_interface_step_for_dadaitem_class(r_ob, type, combine_string_with_symbol_for_undo("Add", r_ob->m_classes.di_class[id].label, false));
			
			t_dadaitem *item = NULL;
            t_llllelem *pos = NULL;

			switch (r_ob->m_classes.di_class[id].alloc_type) {
				case DADA_ITEM_ALLOC_ARRAY:
					item = dadaitem_class_get_nth_item(r_ob, id, num);
					break;
				case DADA_ITEM_ALLOC_OBJLLLL:
					item = dadaitem_new(r_ob, type);
					pos = llll_appendobj(dadaitem_get_class_llll(r_ob, id), item, 0, WHITENULL_llll);
					break;
				default:
					break;
			}

            if (item) {
                r_ob->m_classes.di_class[id].num_items++;
                // clear memory
                memset(item, 0, r_ob->m_classes.di_class[id].element_size);
                
                dadaitem_init(r_ob, item, type, item_flags, r_ob->m_classes.di_class[id].element_have_ID, forced_id);
                item->pos = pos;
                item->color = color;
                item->height = height;
                item->width = width;
                item->coord = coord;
                item->preselected = item->selected = NULL;
                item->name = name;
                
                if (flags & DIA_USE_ATTR_DEFAULTS) {
                    for (long i = 0; i < r_ob->m_inspector.attr_manager->num_attr[id]; i++) {
                        t_bach_attribute *attr = &(r_ob->m_inspector.attr_manager->attr[id][i]);
                        if (attr->default_val) {
                            t_llll *attrll = llll_from_text_buf(attr->default_val, false);
                            dadaitem_set_attr_from_llll(r_ob, item, attr, attrll, false);
                            llll_free(attrll);
                        }
                    }
                }
                
                if (flags & DIA_UNDO && !single_elems_undo)
                    undo_add_interface_step_for_dadaitem(r_ob, item, DADA_UNDO_OP_DELETION, combine_string_with_symbol_for_undo("Add", r_ob->m_classes.di_class[id].label, false));
                
                if (flags & DIA_POSTPROCESS)
                    postprocess_for_dadaitem_class(r_ob, id);
            }
            
			return num;
		}
	}
	return 0;
}

/*
char dadaitem_delete_direct(t_dadaobj *r_ob, t_dadaitem *item, char flags)
{
    long id = dadaitem_class_get_id(&r_ob->m_classes, type);
    switch (r_ob->m_classes.di_class[id].alloc_type) {
        case DADA_ITEM_ALLOC_OBJLLLL:
        default:
            return dadaitem_delete(r_ob, item->type, dadaitem_get_index(r_ob, item), flags);
            break;
    }
    
    t_dadaitem *item = dadaitem_class_get_nth_item(r_ob, id, item_idx);
    
    if (flags & DIA_UNDO)
        undo_add_interface_step_for_dadaitem(r_ob, item, DADA_UNDO_OP_CREATION, combine_string_with_symbol_for_undo("Delete", r_ob->m_classes.di_class[id].label, false));
    
    if (item->ID)
        shashtable_chuck_thing(r_ob->IDtable, item->ID);
    
    // free dada item
    if (r_ob->m_classes.di_class[id].free_fn)
        (r_ob->m_classes.di_class[id].free_fn)(r_ob, item);
    
    
    // remove from selection and preselection
    llll_destroyelem(item->selected);
    llll_destroyelem(item->preselected);
    
    switch (r_ob->m_classes.di_class[id].alloc_type) {
        case DADA_ITEM_ALLOC_ARRAY:
        {
            // shift array
            if (item_idx < num_items - 1)
                sysmem_copyptr(dadaitem_class_get_nth_item(r_ob, id, item_idx + 1), item, (num_items - item_idx - 1) * item_size);
            
            // resync selection and preselection
            t_llllelem *elem;
            for (elem = r_ob->m_interface.selection->l_head; elem; elem = elem->l_next) {
                t_dadaitem *sel = (t_dadaitem *)hatom_getobj(&elem->l_hatom);
                if (sel->type == type && ((long)sel > (long)item))
                    hatom_setobj(&elem->l_hatom, (t_object *)((long)sel - item_size));
            }
            for (elem = r_ob->m_interface.preselection->l_head; elem; elem = elem->l_next) {
                t_dadaitem *sel = (t_dadaitem *)hatom_getobj(&elem->l_hatom);
                if (sel->type == type && ((long)sel > (long)item))
                    hatom_setobj(&elem->l_hatom, (t_object *)((long)sel - item_size));
            }
        }
            break;
        case DADA_ITEM_ALLOC_OBJLLLL:
            llll_destroyelem(item->pos);
            break;
        default:
            break;
    }
    
    
    if (r_ob->m_interface.mousemove_item_identifier.type == type && r_ob->m_interface.mousemove_item_identifier.idx == item_idx) {
        r_ob->m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
        r_ob->m_interface.mousemove_item_identifier.flag = 0;
    }
    
    if (r_ob->m_interface.mousedown_item_identifier.type == type && r_ob->m_interface.mousedown_item_identifier.idx == item_idx) {
        r_ob->m_interface.mousedown_item_identifier.type = DADAITEM_TYPE_NONE;
        r_ob->m_interface.mousedown_item_identifier.flag = 0;
    }
    
    r_ob->m_classes.di_class[id].num_items--;
    
    if (flags & DIA_POSTPROCESS)
        postprocess_for_dadaitem_class(r_ob, id);
    
    return 0;
}
*/

char dadaitem_delete(t_dadaobj *r_ob, e_dadaitem_types type, long item_idx, char flags)
{
	long id = dadaitem_class_get_id(&r_ob->m_classes, type);
	if (id >= 0) {
		long num_items = dadaitem_class_get_num_items_from_id(&r_ob->m_classes, id);
		long item_size = r_ob->m_classes.di_class[id].element_size;
		if (item_idx >= 0 && item_idx < num_items) {
			t_dadaitem *item = dadaitem_class_get_nth_item(r_ob, id, item_idx);

            if (flags & DIA_UNDO)
				undo_add_interface_step_for_dadaitem(r_ob, item, DADA_UNDO_OP_CREATION, combine_string_with_symbol_for_undo("Delete", r_ob->m_classes.di_class[id].label, false), flags & DIA_UNDO_MARKER);

            if (item->ID)
                shashtable_chuck_thing(r_ob->IDtable, item->ID);
            
			// free dada item
			if (r_ob->m_classes.di_class[id].free_fn)
				(r_ob->m_classes.di_class[id].free_fn)(r_ob, item);

			
			// remove from selection and preselection
			llll_destroyelem(item->selected);
			llll_destroyelem(item->preselected);

			switch (r_ob->m_classes.di_class[id].alloc_type) {
				case DADA_ITEM_ALLOC_ARRAY:
				{
					// shift array
					if (item_idx < num_items - 1) 
						sysmem_copyptr(dadaitem_class_get_nth_item(r_ob, id, item_idx + 1), item, (num_items - item_idx - 1) * item_size);

					// resync selection and preselection
					t_llllelem *elem;
					for (elem = r_ob->m_interface.selection->l_head; elem; elem = elem->l_next) {
						t_dadaitem *sel = (t_dadaitem *)hatom_getobj(&elem->l_hatom);
						if (sel->type == type && ((long)sel > (long)item))
							hatom_setobj(&elem->l_hatom, (t_object *)((long)sel - item_size));
					}
					for (elem = r_ob->m_interface.preselection->l_head; elem; elem = elem->l_next) {
						t_dadaitem *sel = (t_dadaitem *)hatom_getobj(&elem->l_hatom);
						if (sel->type == type && ((long)sel > (long)item))
							hatom_setobj(&elem->l_hatom, (t_object *)((long)sel - item_size));
					}
				}
					break;
				case DADA_ITEM_ALLOC_OBJLLLL:
					llll_destroyelem(item->pos);
					break;
				default:
					break;
			}
			
			
			if (r_ob->m_interface.mousemove_item_identifier.type == type && r_ob->m_interface.mousemove_item_identifier.idx == item_idx) {
				r_ob->m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
				r_ob->m_interface.mousemove_item_identifier.flag = 0;
			}
			
			if (r_ob->m_interface.mousedown_item_identifier.type == type && r_ob->m_interface.mousedown_item_identifier.idx == item_idx) {
				r_ob->m_interface.mousedown_item_identifier.type = DADAITEM_TYPE_NONE;
				r_ob->m_interface.mousedown_item_identifier.flag = 0;
			}
            
            if (r_ob->m_interface.mousedown_item == item)
                r_ob->m_interface.mousedown_item = NULL;

            if (r_ob->m_interface.last_mousedown_item == item)
                r_ob->m_interface.last_mousedown_item = NULL;

            if (r_ob->m_interface.mousemove_item == item)
                r_ob->m_interface.mousemove_item = NULL;

			r_ob->m_classes.di_class[id].num_items--;

			if (flags & DIA_POSTPROCESS)
				postprocess_for_dadaitem_class(r_ob, id);

			return 0;
		}
	}
	return -1;
}

char dadaitem_delete_direct(t_dadaobj *r_ob, t_dadaitem *item, char flags)
{
    long id = dadaitem_class_get_id(&r_ob->m_classes, item->type);
    if (id >= 0) {
        if (r_ob->m_classes.di_class[id].alloc_type != DADA_ITEM_ALLOC_OBJLLLL) {
            long idx = dadaitem_get_index(r_ob, item);
            return dadaitem_delete(r_ob, item->type, idx, flags);
        } else {
            if (flags & DIA_UNDO)
                undo_add_interface_step_for_dadaitem(r_ob, item, DADA_UNDO_OP_CREATION, combine_string_with_symbol_for_undo("Delete", r_ob->m_classes.di_class[id].label, false), flags & DIA_UNDO_MARKER);
            
            if (item->ID)
                shashtable_chuck_thing(r_ob->IDtable, item->ID);
            
            // free dada item
            if (r_ob->m_classes.di_class[id].free_fn)
                (r_ob->m_classes.di_class[id].free_fn)(r_ob, item);
            
            
            // remove from selection and preselection
            llll_destroyelem(item->selected);
            llll_destroyelem(item->preselected);
            
            llll_destroyelem(item->pos);
            /*
             if (r_ob->m_interface.mousemove_item_identifier.type == item->type && r_ob->m_interface.mousemove_item_identifier.idx == item_idx) {
             r_ob->m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
             r_ob->m_interface.mousemove_item_identifier.flag = 0;
             }
             
             if (r_ob->m_interface.mousedown_item_identifier.type == item->type && r_ob->m_interface.mousedown_item_identifier.idx == item_idx) {
             r_ob->m_interface.mousedown_item_identifier.type = DADAITEM_TYPE_NONE;
             r_ob->m_interface.mousedown_item_identifier.flag = 0;
             }
             */
            
            if (r_ob->m_interface.mousedown_item == item)
                r_ob->m_interface.mousedown_item = NULL;
            
            if (r_ob->m_interface.mousemove_item == item)
                r_ob->m_interface.mousemove_item = NULL;

            r_ob->m_classes.di_class[id].num_items--;
            
            if (flags & DIA_POSTPROCESS)
                postprocess_for_dadaitem_class(r_ob, id);
            
            return 0;
        }
    }
    return -1;
}





long dadaitem_duplicate(t_dadaobj *r_ob, e_dadaitem_types type, long idx, char flags)
{
	t_dadaitem *item = dadaitem_class_get_nth_item(r_ob, dadaitem_class_get_id(&r_ob->m_classes, type), idx);
	if (item) {
		if (flags & DIA_UNDO)
			undo_add_interface_step_for_dadaitem_class(r_ob, type, combine_string_with_symbol_for_undo("Duplicate", r_ob->m_classes.di_class[dadaitem_class_get_id(&r_ob->m_classes, type)].label, false));

		long res = dadaitem_add(r_ob, type, item->coord, item->height, item->width, item->color, item->name, item->flags, flags & (~DIA_UNDO));
        long class_id = dadaitem_class_get_id(&r_ob->m_classes, type);
        t_dadaitem *newitem = dadaitem_class_get_nth_item(r_ob, class_id, res);
        
        t_llll *ll = dadaitem_get_as_llll(r_ob, item);
        dadaitem_set_from_llll(r_ob, newitem, ll, 0);
        llll_free(ll);
        
        return res;
	}
	return -1;
}

void dadaitem_move(t_dadaobj *r_ob, t_dadaitem *item, t_pt new_coord, char flags)
{
	if (item) {
		if (flags & DIA_UNDO)
			undo_add_interface_step_for_dadaitem(r_ob, item, DADA_UNDO_OP_MODIFICATION, combine_string_with_symbol_for_undo("Move", r_ob->m_classes.di_class[dadaitem_class_get_id(&r_ob->m_classes, item->type)].label, false));

		if (flags & DIA_INTERFACE) 
			drag_coord(r_ob, &item->coord, new_coord, flags & DIA_SNAPTOGRID);
		else
			item->coord = new_coord;
		
		if (flags & DIA_POSTPROCESS) 
			postprocess_for_dadaitem_class(r_ob, dadaitem_class_get_id(&r_ob->m_classes, item->type));
	}
}

void dadaitem_move_delta(t_dadaobj *r_ob, t_dadaitem *item, t_pt delta_coord, char flags)
{
	if (item) {
		t_pt delta = delta_coord;
		
		if (flags & DIA_UNDO)
			undo_add_interface_step_for_dadaitem(r_ob, item, DADA_UNDO_OP_MODIFICATION, combine_string_with_symbol_for_undo("Move", r_ob->m_classes.di_class[dadaitem_class_get_id(&r_ob->m_classes, item->type)].label, false));
		
		if (flags & DIA_INTERFACE)
			drag_coord_delta(r_ob, &delta, flags & DIA_SNAPTOGRID);
		
		item->coord = pt_pt_sum(item->coord, delta_coord);

		if (flags & DIA_POSTPROCESS) 
			postprocess_for_dadaitem_class(r_ob, dadaitem_class_get_id(&r_ob->m_classes, item->type));
	}
}

void dadaitem_set_color(t_dadaobj *r_ob, t_dadaitem *item, t_jrgba new_color, char flags)
{
	if (item)  {
		if (flags & DIA_UNDO)
			undo_add_interface_step_for_dadaitem_class(r_ob, item->type, combine_string_with_symbol_for_undo("Change Color For", r_ob->m_classes.di_class[dadaitem_class_get_id(&r_ob->m_classes, item->type)].label, false));
		
		item->color = new_color;
		
		if (flags & DIA_POSTPROCESS)
			postprocess_for_dadaitem_class(r_ob, dadaitem_class_get_id(&r_ob->m_classes, item->type));
	}
}

void dadaitem_change_hue_and_lightness(t_dadaobj *r_ob, t_dadaitem *item, 
									   double delta_hue, double delta_lightness,
									   double min_lightness, double max_lightness, char flags)
{
	if (item) {
		if (flags & DIA_UNDO)
			undo_add_interface_step_for_dadaitem_class(r_ob, item->type, combine_string_with_symbol_for_undo("Change Color For", r_ob->m_classes.di_class[dadaitem_class_get_id(&r_ob->m_classes, item->type)].label, false));

		change_hue_and_lightness(&item->color, delta_hue, delta_lightness, min_lightness, max_lightness);
		
		if (flags & DIA_POSTPROCESS)
			postprocess_for_dadaitem_class(r_ob, dadaitem_class_get_id(&r_ob->m_classes, item->type));
	}
}


t_rect dadaitem_get_rect_baricentric(t_dadaitem *item)
{
	return build_rect(item->coord.x, item->coord.y, item->width, item->height);
}

t_rect dadaitem_get_rect_boundingbox(t_dadaitem *item)
{
	return build_rect(item->coord.x - item->width/2., item->coord.y - item->height / 2., item->width, item->height);
}


char dadaitem_is_pt_in_rect(t_dadaitem *item, t_pt pt)
{
	// could be made faster
	return is_pt_in_rectangle(pt, dadaitem_get_rect_boundingbox(item));
}

char dadaitem_is_pt_in_rect_tolerance(t_dadaitem *item, t_pt pt, double tolerance)
{
    // could be made faster
    return is_pt_in_rectangle_tolerance(pt, dadaitem_get_rect_boundingbox(item), tolerance);
}





/////////// SPECIFIC WRAPPERS FOR EACH NON-CUSTOM TYPE
//// BALLS

void dadaitem_ball_clear(t_dadaobj *r_ob, char flags)
{
	dadaitem_class_clear(r_ob, &r_ob->m_classes, &r_ob->m_interface, &r_ob->m_undo, DADAITEM_TYPE_BALL, flags);
}

long dadaitem_ball_add(t_dadaobj *r_ob, t_pt coord, t_pt speed, t_jrgba color, long channel, long item_flags, char flags)
{
	long res = dadaitem_add(r_ob, DADAITEM_TYPE_BALL, coord, 0, 0, color, NULL, item_flags, flags);
	if (res >= 0) {
		t_dadaitem *item = dadaitem_class_get_nth_item(r_ob, dadaitem_class_get_id(&r_ob->m_classes, DADAITEM_TYPE_BALL), res);
        if (item) {
            ((t_dada_ball *)item)->speed = speed;
            ((t_dada_ball *)item)->channel = channel;
        }
		return res;
	}
	return -1;
}

char dadaitem_ball_delete(t_dadaobj *r_ob, long idx, char flags)
{
	return dadaitem_delete(r_ob, DADAITEM_TYPE_BALL, idx, flags);
}


long dadaitem_ball_duplicate(t_dadaobj *r_ob, long idx, char flags)
{
	return dadaitem_duplicate(r_ob, DADAITEM_TYPE_BALL, idx, flags);
}

void dadaitem_ball_move(t_dadaobj *r_ob, long idx, t_pt new_coord, char flags)
{
	dadaitem_move(r_ob, dadaitem_from_type_and_idx(r_ob, DADAITEM_TYPE_BALL, idx), new_coord, flags);
}

void dadaitem_ball_move_delta(t_dadaobj *r_ob, long idx, t_pt delta_coord, char flags)
{
	dadaitem_move_delta(r_ob, dadaitem_from_type_and_idx(r_ob, DADAITEM_TYPE_BALL, idx), delta_coord, flags);
}

void dadaitem_ball_set_channel(t_dadaobj *r_ob, long idx, long new_channel, char flags)
{
	t_dada_ball *ball = (t_dada_ball *)dadaitem_from_type_and_idx(r_ob, DADAITEM_TYPE_BALL, idx);
	if (ball) {
		if (flags & DIA_UNDO)
			undo_add_interface_step_for_dadaitem_class(r_ob, DADAITEM_TYPE_BALL, gensym("Change MIDIchannel For Ball"));
		
		ball->channel = new_channel;
		
		if (flags & DIA_POSTPROCESS)
			postprocess_for_dadaitem_class(r_ob, dadaitem_class_get_id(&r_ob->m_classes, DADAITEM_TYPE_BALL));
	}
}

void dadaitem_ball_set_color(t_dadaobj *r_ob, long idx, t_jrgba new_color, char flags)
{
	dadaitem_set_color(r_ob, dadaitem_from_type_and_idx(r_ob, DADAITEM_TYPE_BALL, idx), new_color, flags);
}


void dadaitem_ball_change_hue_and_lightness(t_dadaobj *r_ob, long idx, 
									   double delta_hue, double delta_lightness,
									   double min_lightness, double max_lightness, char flags)
{
	dadaitem_change_hue_and_lightness(r_ob, dadaitem_from_type_and_idx(r_ob, DADAITEM_TYPE_BALL, idx), 
									  delta_hue, delta_lightness, min_lightness, max_lightness, flags);
}

void dadaitem_ball_speed_scale(t_dadaobj *r_ob, long idx, double factor, char flags)
{
	t_dada_ball *ball = (t_dada_ball *)dadaitem_from_type_and_idx(r_ob, DADAITEM_TYPE_BALL, idx);
	if (ball) {
		if (flags & DIA_UNDO)
			undo_add_interface_step_for_dadaitem_class(r_ob, DADAITEM_TYPE_BALL, gensym("Change Speed For Ball"));
	
		ball->speed = pt_number_prod(ball->speed, factor);
	
		if (flags & DIA_POSTPROCESS)
			postprocess_for_dadaitem_class(r_ob, dadaitem_class_get_id(&r_ob->m_classes, DADAITEM_TYPE_BALL));
	}
}

void dadaitem_ball_speed_rotate(t_dadaobj *r_ob, long idx, double angle, char flags)
{
	t_dada_ball *ball = (t_dada_ball *)dadaitem_from_type_and_idx(r_ob, DADAITEM_TYPE_BALL, idx);
	if (ball) {
		if (flags & DIA_UNDO)
			undo_add_interface_step_for_dadaitem_class(r_ob, DADAITEM_TYPE_BALL, gensym("Rotate Speed For Ball"));
		
		t_jmatrix rotmat;
		jgraphics_matrix_init_rotate(&rotmat, angle);
		jgraphics_matrix_transform_point(&rotmat, &ball->speed.x, &ball->speed.y);
		
		if (flags & DIA_POSTPROCESS)
			postprocess_for_dadaitem_class(r_ob, dadaitem_class_get_id(&r_ob->m_classes, DADAITEM_TYPE_BALL));
	}
}

void dadaitem_ball_speed_set_angle(t_dadaobj *r_ob, long idx, double angle, char flags)
{
	t_dada_ball *ball = (t_dada_ball *)dadaitem_from_type_and_idx(r_ob, DADAITEM_TYPE_BALL, idx);
	if (ball) {
		if (flags & DIA_UNDO)
			undo_add_interface_step_for_dadaitem_class(r_ob, DADAITEM_TYPE_BALL, gensym("Set Speed Angle For Ball"));

		ball->speed.x = pt_norm(ball->speed);
		ball->speed.y = 0;
		dadaitem_ball_speed_rotate(r_ob, idx, angle, 0);
		
		if (flags & DIA_POSTPROCESS)
			postprocess_for_dadaitem_class(r_ob, dadaitem_class_get_id(&r_ob->m_classes, DADAITEM_TYPE_BALL));
	}
}



long dadaitem_ball_find_max_channel(t_dadaobj *r_ob)
{
	long i;
	long max = 0;
	long id = dadaitem_class_get_id(&r_ob->m_classes, DADAITEM_TYPE_BALL);
	long num_balls = dadaitem_class_get_num_items_from_id(&r_ob->m_classes, id);
	t_dada_ball *ball = (t_dada_ball *)dadaitem_class_get_nth_item(r_ob, id, 0);
	for (i = 1; i < num_balls; i++, ball ++)
		if (ball->channel > max)
			max = ball->channel;
	return max;
}




//// CARDS

void dadaitem_card_clear(t_dadaobj *r_ob, char flags)
{
	dadaitem_class_clear(r_ob, &r_ob->m_classes, &r_ob->m_interface, &r_ob->m_undo, DADAITEM_TYPE_CARD, flags);
}

long dadaitem_card_add(t_dadaobj *r_ob, t_pt coord, double width, double height, t_jrgba color, t_symbol *text, t_symbol *icon_path, double value, long item_flags, char flags)
{
	long res = dadaitem_add(r_ob, DADAITEM_TYPE_CARD, coord, width, height, color, NULL, item_flags, flags);
	if (res >= 0) {
		t_dadaitem *item = dadaitem_class_get_nth_item(r_ob, dadaitem_class_get_id(&r_ob->m_classes, DADAITEM_TYPE_CARD), res);
		((t_dada_card *)item)->text = text;
		((t_dada_card *)item)->icon_path = icon_path;
		((t_dada_card *)item)->value = value;

		// creating surface
		((t_dada_card *)item)->icon_surface = NULL;
		((t_dada_card *)item)->icon_width = ((t_dada_card *)item)->icon_height = 0;
        if (icon_path)
            ((t_dada_card *)item)->icon_surface = get_surface_from_file(icon_path);
		
		if (((t_dada_card *)item)->icon_surface){
			((t_dada_card *)item)->icon_width = jgraphics_image_surface_get_width(((t_dada_card *)item)->icon_surface);
			((t_dada_card *)item)->icon_height = jgraphics_image_surface_get_height(((t_dada_card *)item)->icon_surface);
		}
			
		return res;
	}
	return -1;
}

t_rect dadaitem_card_get_rect(t_dadaobj *r_ob, t_dada_card *card)
{
	double height = card->r_it.height, width = card->r_it.width;
	if (height < 0 && card->icon_width > 0) 
		height = width * card->icon_height / card->icon_width;
	else if (width < 0 && card->icon_height > 0) 
		width = height * card->icon_width / card->icon_height;

	return build_rect(card->r_it.coord.x - width / 2., card->r_it.coord.y + height / 2., width, -height);
}

char dadaitem_card_delete(t_dadaobj *r_ob, long idx, char flags)
{
	return dadaitem_delete(r_ob, DADAITEM_TYPE_CARD, idx, flags);
}


void dadaitem_card_move(t_dadaobj *r_ob, long idx, t_pt new_coord, char flags)
{
	dadaitem_move(r_ob, dadaitem_from_type_and_idx(r_ob, DADAITEM_TYPE_CARD, idx), new_coord, flags);
}

void dadaitem_card_move_delta(t_dadaobj *r_ob, long idx, t_pt delta_coord, char flags)
{
	dadaitem_move_delta(r_ob, dadaitem_from_type_and_idx(r_ob, DADAITEM_TYPE_CARD, idx), delta_coord, flags);
}


void dadaitem_card_change_value_delta(t_dadaobj *r_ob, long idx, double delta_val, char flags)
{
	t_dada_card *card = (t_dada_card *)dadaitem_from_type_and_idx(r_ob, DADAITEM_TYPE_CARD, idx);

	if (flags & DIA_UNDO)
		undo_add_interface_step_for_dadaitem_class(r_ob, DADAITEM_TYPE_CARD, gensym("Change Value"));

	card->value += delta_val;

	if (flags & DIA_POSTPROCESS) 
		postprocess_for_dadaitem_class(r_ob, dadaitem_class_get_id(&r_ob->m_classes, DADAITEM_TYPE_CARD));
}




//// VIDEOGAME CHARACTERS

void dadaitem_gamechar_free(t_dadaobj *r_ob, t_dadaitem *item)
{
	t_dada_gamechar *game = (t_dada_gamechar *)item;
	llll_free(game->music); 
	llll_free(game->resurrectpositions); 
    llll_free(game->kill_sequence);
}

void dadaitem_gamechar_clear(t_dadaobj *r_ob, char flags)
{
	
	dadaitem_class_clear(r_ob, &r_ob->m_classes, &r_ob->m_interface, &r_ob->m_undo, DADAITEM_TYPE_GAMECHAR, flags);
}

long dadaitem_gamechar_add(t_dadaobj *r_ob, t_pt coord, double width, double height, t_jrgba color, 
						   t_pt speed, t_symbol *name, long type, double points, long vp,
						   long state, long state_ability, long how_dies, long how_kills, char direction, t_llll *music, 
						   t_symbol *idle_sprite, t_symbol *walk_sprite, t_symbol *jump_sprite, t_symbol *fly_sprite,
                           t_symbol *glide_sprite, t_symbol *dead_sprite, t_symbol *bullet_gamechar,
						   t_llll *resurrectpositions, t_llll *kill_sequence, double *physics_ext, long item_flags, char flags)
{
	long res = dadaitem_add(r_ob, DADAITEM_TYPE_GAMECHAR, coord, width, height, color, name, item_flags, flags);
	if (res >= 0) {
		t_dadaitem *item = dadaitem_class_get_nth_item(r_ob, dadaitem_class_get_id(&r_ob->m_classes, DADAITEM_TYPE_GAMECHAR), res);
		((t_dada_gamechar *)item)->speed = speed;
		((t_dada_gamechar *)item)->type = type;
		((t_dada_gamechar *)item)->points = points;
		((t_dada_gamechar *)item)->vp = vp;
		((t_dada_gamechar *)item)->how_dies = how_dies;
		((t_dada_gamechar *)item)->how_kills = how_kills;
		((t_dada_gamechar *)item)->state = state;
		((t_dada_gamechar *)item)->abilities = state_ability;
		((t_dada_gamechar *)item)->direction = direction;
		((t_dada_gamechar *)item)->music = music;
        ((t_dada_gamechar *)item)->kill_sequence = kill_sequence;
		((t_dada_gamechar *)item)->resurrectpositions = resurrectpositions;
        ((t_dada_gamechar *)item)->physics_ext[0] = physics_ext ? physics_ext[0] : width / 2.;
        ((t_dada_gamechar *)item)->physics_ext[1] = physics_ext ? physics_ext[1] : width / 2.;
        ((t_dada_gamechar *)item)->physics_ext[2] = physics_ext ? physics_ext[2] : height / 2.;
        ((t_dada_gamechar *)item)->physics_ext[3] = physics_ext ? physics_ext[3] : height / 2.;
		
		((t_dada_gamechar *)item)->sprite_idle = idle_sprite ? idle_sprite : _llllobj_sym_none;
		((t_dada_gamechar *)item)->sprite_walk = walk_sprite ? walk_sprite : _llllobj_sym_none;
		((t_dada_gamechar *)item)->sprite_jump = jump_sprite ? jump_sprite : _llllobj_sym_none;
		((t_dada_gamechar *)item)->sprite_fly = fly_sprite ? fly_sprite : _llllobj_sym_none;
        ((t_dada_gamechar *)item)->sprite_glide = glide_sprite ? glide_sprite : _llllobj_sym_none;
		((t_dada_gamechar *)item)->sprite_dead = dead_sprite ? dead_sprite : _llllobj_sym_none;
        ((t_dada_gamechar *)item)->bullet_gamechar = bullet_gamechar ? bullet_gamechar : _llllobj_sym_none;
		
		return res;
	}
	return -1;
}

char dadaitem_gamechar_delete(t_dadaobj *r_ob, long idx, char flags)
{
	return dadaitem_delete(r_ob, DADAITEM_TYPE_GAMECHAR, idx, flags);
}



t_llll *dadaitem_gamechar_ability_to_llll(long ability)
{
	t_llll *ll = llll_get();
	if (ability & DADA_GAMECHAR_ABILITY_WALK)
		llll_appendsym(ll, gensym("walk"));
	if (ability & DADA_GAMECHAR_ABILITY_JUMP)
		llll_appendsym(ll, gensym("jump"));
	if (ability & DADA_GAMECHAR_ABILITY_FLY)
		llll_appendsym(ll, gensym("fly"));
	if (ability & DADA_GAMECHAR_ABILITY_SWIM)
		llll_appendsym(ll, gensym("swim"));
    if (ability & DADA_GAMECHAR_ABILITY_RUN)
        llll_appendsym(ll, gensym("run"));
    if (ability & DADA_GAMECHAR_ABILITY_GLIDE)
        llll_appendsym(ll, gensym("glide"));
    if (ability & DADA_GAMECHAR_ABILITY_BREAK)
        llll_appendsym(ll, gensym("break"));
    if (ability & DADA_GAMECHAR_ABILITY_KILL)
        llll_appendsym(ll, gensym("kill"));
    if (ability & DADA_GAMECHAR_ABILITY_DIE)
        llll_appendsym(ll, gensym("die"));
    if (ability & DADA_GAMECHAR_ABILITY_SHOOT)
        llll_appendsym(ll, gensym("shoot"));
    
    if (!ll->l_head)
        llll_appendsym(ll, gensym("none"));

	return ll;
}

long dadaitem_gamechar_llll_to_ability(t_llll *ll)
{
    if (ll->l_size == 1 && hatom_gettype(&ll->l_head->l_hatom) == H_LONG)
        return hatom_getlong(&ll->l_head->l_hatom); // single long: bitfield value
    
    long res = 0;
    if (is_symbol_in_llll_first_level(ll, gensym("walk")))
        res += DADA_GAMECHAR_ABILITY_WALK;
    if (is_symbol_in_llll_first_level(ll, gensym("jump")))
        res += DADA_GAMECHAR_ABILITY_JUMP;
    if (is_symbol_in_llll_first_level(ll, gensym("fly")))
        res += DADA_GAMECHAR_ABILITY_FLY;
    if (is_symbol_in_llll_first_level(ll, gensym("swim")))
        res += DADA_GAMECHAR_ABILITY_SWIM;
    if (is_symbol_in_llll_first_level(ll, gensym("run")))
        res += DADA_GAMECHAR_ABILITY_RUN;
    if (is_symbol_in_llll_first_level(ll, gensym("glide")))
        res += DADA_GAMECHAR_ABILITY_GLIDE;
    if (is_symbol_in_llll_first_level(ll, gensym("break")))
        res += DADA_GAMECHAR_ABILITY_BREAK;
    if (is_symbol_in_llll_first_level(ll, gensym("kill")))
        res += DADA_GAMECHAR_ABILITY_KILL;
    if (is_symbol_in_llll_first_level(ll, gensym("die")))
        res += DADA_GAMECHAR_ABILITY_DIE;
    if (is_symbol_in_llll_first_level(ll, gensym("shoot")))
        res += DADA_GAMECHAR_ABILITY_SHOOT;
    return res;
}

long dadaitem_gamechar_llllelem_to_ability(t_llllelem *elem)
{
    if (!elem) return 0;
    
    if (hatom_gettype(&elem->l_hatom) == H_LLLL)
        return dadaitem_gamechar_llll_to_ability(hatom_getllll(&elem->l_hatom));
    else if (hatom_gettype(&elem->l_hatom) == H_LONG)
        return hatom_getlong(&elem->l_hatom);
    else if (hatom_gettype(&elem->l_hatom) == H_SYM) {
        t_llll *temp = llll_get();
        llll_appendsym(temp, hatom_getsym(&elem->l_hatom));
        long res = dadaitem_gamechar_llll_to_ability(temp);
        llll_free(temp);
        return res;
    }
    return 0;
}




t_llll *dadaitem_gamechar_state_to_llll(long state)
{
    t_llll *ll = llll_get();
    if (state & DADA_GAMECHAR_STATE_WALKING)
        llll_appendsym(ll, gensym("walking"));
    if (state & DADA_GAMECHAR_STATE_JUMPING)
        llll_appendsym(ll, gensym("jumping"));
    if (state & DADA_GAMECHAR_STATE_FLYING)
        llll_appendsym(ll, gensym("flying"));
    if (state & DADA_GAMECHAR_STATE_SWIMMING)
        llll_appendsym(ll, gensym("swimming"));
    if (state & DADA_GAMECHAR_STATE_RUNNING)
        llll_appendsym(ll, gensym("running"));
    if (state & DADA_GAMECHAR_STATE_GLIDING)
        llll_appendsym(ll, gensym("gliding"));
    if (state & DADA_GAMECHAR_STATE_DYING)
        llll_appendsym(ll, gensym("dying"));
    if (state & DADA_GAMECHAR_STATE_DEAD)
        llll_appendsym(ll, gensym("dead"));
    if (state & DADA_GAMECHAR_STATE_GENERATING)
        llll_appendsym(ll, gensym("generating"));
    if (state & DADA_GAMECHAR_STATE_ENTERINGPORTAL)
        llll_appendsym(ll, gensym("enteringportal"));
    if (state & DADA_GAMECHAR_STATE_EXITINGPORTAL)
        llll_appendsym(ll, gensym("exitingportal"));
    if (state & DADA_GAMECHAR_STATE_ELSEWHERE)
        llll_appendsym(ll, gensym("elsewhere"));
    
    if (!ll->l_head)
        llll_appendsym(ll, gensym("idle"));
    return ll;
}


long dadaitem_gamechar_llll_to_state(t_llll *ll)
{
    if (ll->l_size == 1 && hatom_gettype(&ll->l_head->l_hatom) == H_LONG)
        return hatom_getlong(&ll->l_head->l_hatom); // single long: bitfield value

	long res = 0;
    if (is_symbol_in_llll_first_level(ll, gensym("idle")))
        res += DADA_GAMECHAR_STATE_IDLE;
	if (is_symbol_in_llll_first_level(ll, gensym("walking")))
		res += DADA_GAMECHAR_STATE_WALKING;
	if (is_symbol_in_llll_first_level(ll, gensym("jumping")))
		res += DADA_GAMECHAR_STATE_JUMPING;
	if (is_symbol_in_llll_first_level(ll, gensym("flying")))
		res += DADA_GAMECHAR_STATE_FLYING;
	if (is_symbol_in_llll_first_level(ll, gensym("swimming")))
		res += DADA_GAMECHAR_STATE_SWIMMING;
    if (is_symbol_in_llll_first_level(ll, gensym("running")))
        res += DADA_GAMECHAR_STATE_RUNNING;
    if (is_symbol_in_llll_first_level(ll, gensym("gliding")))
        res += DADA_GAMECHAR_STATE_GLIDING;
    if (is_symbol_in_llll_first_level(ll, gensym("dying")))
        res += DADA_GAMECHAR_STATE_DYING;
    if (is_symbol_in_llll_first_level(ll, gensym("dead")))
        res += DADA_GAMECHAR_STATE_DEAD;
    if (is_symbol_in_llll_first_level(ll, gensym("generating")))
        res += DADA_GAMECHAR_STATE_GENERATING;
    if (is_symbol_in_llll_first_level(ll, gensym("enteringportal")))
        res += DADA_GAMECHAR_STATE_ENTERINGPORTAL;
    if (is_symbol_in_llll_first_level(ll, gensym("exitingportal")))
        res += DADA_GAMECHAR_STATE_EXITINGPORTAL;
    if (is_symbol_in_llll_first_level(ll, gensym("elsewhere")))
        res += DADA_GAMECHAR_STATE_ELSEWHERE;
	return res;
}



long dadaitem_gamechar_llllelem_to_state(t_llllelem *elem)
{
    if (!elem) return 0;
    
    if (hatom_gettype(&elem->l_hatom) == H_LLLL)
        return dadaitem_gamechar_llll_to_state(hatom_getllll(&elem->l_hatom));
    else if (hatom_gettype(&elem->l_hatom) == H_LONG)
        return hatom_getlong(&elem->l_hatom);
    else if (hatom_gettype(&elem->l_hatom) == H_SYM) {
        t_llll *temp = llll_get();
        llll_appendsym(temp, hatom_getsym(&elem->l_hatom));
        long res = dadaitem_gamechar_llll_to_state(temp);
        llll_free(temp);
        return res;
    }
    return 0;
}


t_symbol *dadaitem_gamechar_type_to_symbol(long type)
{
    switch (type) {
        case DADA_GAMECHAR_TYPE_USERCONTROL:
            return gensym("usercontrol");
            break;

        case DADA_GAMECHAR_TYPE_ENEMY:
            return gensym("enemy");
            break;

        case DADA_GAMECHAR_TYPE_FOOD:
            return gensym("food");
            break;
            
        case DADA_GAMECHAR_TYPE_BULLET:
            return gensym("bullet");
            break;
            
        default:
            return gensym("idle");
            break;
    }
}



long dadaitem_gamechar_symbol_to_type(t_symbol *sym)
{
    if (sym == gensym("usercontrol"))
        return DADA_GAMECHAR_TYPE_USERCONTROL;
    if (sym == gensym("enemy"))
        return DADA_GAMECHAR_TYPE_ENEMY;
    if (sym == gensym("food"))
        return DADA_GAMECHAR_TYPE_FOOD;
    if (sym == gensym("bullet"))
        return DADA_GAMECHAR_TYPE_BULLET;
    return DADA_GAMECHAR_TYPE_IDLE;
}


t_llll *dadaitem_gamechar_via_to_llll(long via)
{
    t_llll *ll = llll_get();
    if (via & DADA_GAMECHAR_VIA_SIDE_LEFT)
        llll_appendsym(ll, gensym("left"));
    if (via & DADA_GAMECHAR_VIA_SIDE_RIGHT)
        llll_appendsym(ll, gensym("right"));
    if (via & DADA_GAMECHAR_VIA_SIDE_TOP)
        llll_appendsym(ll, gensym("top"));
    if (via & DADA_GAMECHAR_VIA_SIDE_BOTTOM)
        llll_appendsym(ll, gensym("bottom"));
    if (via & DADA_GAMECHAR_VIA_BUMP)
        llll_appendsym(ll, gensym("bump"));
    if (via & DADA_GAMECHAR_VIA_BULLET)
        llll_appendsym(ll, gensym("bullet"));
    if (via & DADA_GAMECHAR_VIA_GLIDE)
        llll_appendsym(ll, gensym("glide"));
    
    if (!ll->l_head)
        llll_appendsym(ll, gensym("none"));
    
    return ll;
}

long dadaitem_llll_to_via(t_llll *ll)
{
    if (ll->l_size == 1 && hatom_gettype(&ll->l_head->l_hatom) == H_LONG)
        return hatom_getlong(&ll->l_head->l_hatom); // single long: bitfield value
    
    long res = 0;
    if (is_symbol_in_llll_first_level(ll, gensym("left")))
        res += DADA_GAMECHAR_VIA_SIDE_LEFT;
    if (is_symbol_in_llll_first_level(ll, gensym("right")))
        res += DADA_GAMECHAR_VIA_SIDE_RIGHT;
    if (is_symbol_in_llll_first_level(ll, gensym("top")))
        res += DADA_GAMECHAR_VIA_SIDE_TOP;
    if (is_symbol_in_llll_first_level(ll, gensym("bottom")))
        res += DADA_GAMECHAR_VIA_SIDE_BOTTOM;
    if (is_symbol_in_llll_first_level(ll, gensym("bump")))
        res += DADA_GAMECHAR_VIA_BUMP;
    if (is_symbol_in_llll_first_level(ll, gensym("bullet")))
        res += DADA_GAMECHAR_VIA_BULLET;
    if (is_symbol_in_llll_first_level(ll, gensym("glide")))
        res += DADA_GAMECHAR_VIA_GLIDE;

    return res;
}

long dadaitem_gamechar_llllelem_to_via(t_llllelem *elem)
{
    if (!elem) return 0;
    
    if (hatom_gettype(&elem->l_hatom) == H_LLLL)
        return dadaitem_llll_to_via(hatom_getllll(&elem->l_hatom));
    else if (hatom_gettype(&elem->l_hatom) == H_LONG)
        return hatom_getlong(&elem->l_hatom);
    else if (hatom_gettype(&elem->l_hatom) == H_SYM) {
        t_llll *temp = llll_get();
        llll_appendsym(temp, hatom_getsym(&elem->l_hatom));
        long res = dadaitem_llll_to_via(temp);
        llll_free(temp);
        return res;
    }
    return 0;
}










//// BLOCKS

void dadaitem_block_free(t_dadaobj *r_ob, t_dadaitem *item)
{
	t_dada_block *block = (t_dada_block *)item;
	llll_free(block->music);
    llll_free(block->hit_sequence);
}

void dadaitem_block_clear(t_dadaobj *r_ob, char flags)
{
	dadaitem_class_clear(r_ob, &r_ob->m_classes, &r_ob->m_interface, &r_ob->m_undo, DADAITEM_TYPE_BLOCK, flags);
}

long dadaitem_block_add(t_dadaobj *r_ob, t_pt coord, double width, double height, t_jrgba color, t_symbol *name, char solid, long how_bumpeable, long state, t_symbol *sprite, t_symbol *break_sprite, double points, t_llll *music, t_llll *hit_sequence, char loop_hit_sequence, long item_flags, char flags)
{
	long res = dadaitem_add(r_ob, DADAITEM_TYPE_BLOCK, coord, width, height, color, name, item_flags, flags);
	if (res >= 0) {
		t_dadaitem *item = dadaitem_class_get_nth_item(r_ob, dadaitem_class_get_id(&r_ob->m_classes, DADAITEM_TYPE_BLOCK), res);
		((t_dada_block *)item)->state = state;
        ((t_dada_block *)item)->solid = solid;
        ((t_dada_block *)item)->how_bumpeable = how_bumpeable;
		((t_dada_block *)item)->sprite = sprite;
        ((t_dada_block *)item)->fragment_sprite = break_sprite;
        ((t_dada_block *)item)->hit_count = 0;
		((t_dada_block *)item)->points = points;
		((t_dada_block *)item)->music = music;
        ((t_dada_block *)item)->hit_sequence = hit_sequence;
        ((t_dada_block *)item)->loop_hit_sequence = loop_hit_sequence;
        
		
		return res;
	}
	return -1;
}

char dadaitem_block_delete(t_dadaobj *r_ob, long idx, char flags)
{
	return dadaitem_delete(r_ob, DADAITEM_TYPE_BLOCK, idx, flags);
}




//// COINS


void dadaitem_coin_free(t_dadaobj *r_ob, t_dadaitem *item)
{
	t_dada_coin *coin = (t_dada_coin *)item;
	llll_free(coin->music); 
}

void dadaitem_coin_clear(t_dadaobj *r_ob, char flags)
{
	dadaitem_class_clear(r_ob, &r_ob->m_classes, &r_ob->m_interface, &r_ob->m_undo, DADAITEM_TYPE_COIN, flags);
}

long dadaitem_coin_add(t_dadaobj *r_ob, t_pt coord, double width, double height, t_jrgba color, t_symbol *name,
					   char takeable, char taken, t_symbol *sprite, double points, long vp, t_llll *music, long item_flags, char flags)
{
	long res = dadaitem_add(r_ob, DADAITEM_TYPE_COIN, coord, width, height, color, name, item_flags, flags);
	if (res >= 0) {
		t_dadaitem *item = dadaitem_class_get_nth_item(r_ob, dadaitem_class_get_id(&r_ob->m_classes, DADAITEM_TYPE_COIN), res);
		((t_dada_coin *)item)->takeable = takeable;
		((t_dada_coin *)item)->taken = taken;
		((t_dada_coin *)item)->sprite = sprite;
		((t_dada_coin *)item)->points = points;
		((t_dada_coin *)item)->vp = vp;
		((t_dada_coin *)item)->music = music;
		
		return res;
	}
	return -1;
}

char dadaitem_coin_delete(t_dadaobj *r_ob, long idx, char flags)
{
	return dadaitem_delete(r_ob, DADAITEM_TYPE_COIN, idx, flags);
}


//// PORTALS


void dadaitem_portal_free(t_dadaobj *r_ob, t_dadaitem *item)
{
    t_dada_portal *portal = (t_dada_portal *)item;
    llll_free(portal->music);
    llll_free(portal->enter_sequence);
    llll_free(portal->exit_sequence);
}

void dadaitem_portal_clear(t_dadaobj *r_ob, char flags)
{
    dadaitem_class_clear(r_ob, &r_ob->m_classes, &r_ob->m_interface, &r_ob->m_undo, DADAITEM_TYPE_PORTAL, flags);
}

long dadaitem_portal_add(t_dadaobj *r_ob, t_pt coord, double width, double height, t_jrgba color, t_symbol *name, t_symbol *sprite,
                       char open, long enter_via, long exit_via, t_llll *enter_sequence, t_llll *exit_sequence, t_llll *music, char hero_only, long item_flags, char flags)
{
    long res = dadaitem_add(r_ob, DADAITEM_TYPE_PORTAL, coord, width, height, color, name, item_flags, flags);
    if (res >= 0) {
        t_dadaitem *item = dadaitem_class_get_nth_item(r_ob, dadaitem_class_get_id(&r_ob->m_classes, DADAITEM_TYPE_PORTAL), res);
        ((t_dada_portal *)item)->open = open;
        ((t_dada_portal *)item)->how_enter = enter_via;
        ((t_dada_portal *)item)->how_exit = exit_via;
        ((t_dada_portal *)item)->hero_only = hero_only;
        ((t_dada_portal *)item)->enter_sequence = enter_sequence;
        ((t_dada_portal *)item)->exit_sequence = exit_sequence;
        ((t_dada_portal *)item)->music = music;
        ((t_dada_portal *)item)->sprite = sprite;
        
        return res;
    }
    return -1;
}

char dadaitem_portal_delete(t_dadaobj *r_ob, long idx, char flags)
{
    return dadaitem_delete(r_ob, DADAITEM_TYPE_PORTAL, idx, flags);
}






////////////////////////


t_dadaitem *dadaitem_from_identifier(t_dadaobj *r_ob, t_dadaitem_identifier *identifier)
{
	e_dadaitem_types type = (e_dadaitem_types)identifier->type;
	long class_id = dadaitem_class_get_id(&r_ob->m_classes, type);
	if (type < 0) {
		// custom type
		if (r_ob->m_classes.di_class[class_id].identifier_to_dadaitem_fn) 
			return (t_dadaitem *)(r_ob->m_classes.di_class[class_id].identifier_to_dadaitem_fn)(r_ob->orig_obj, identifier);
		else
			return NULL;
	} else 
		return dadaitem_class_get_nth_item(r_ob, class_id, identifier->idx);
}

t_dadaitem *dadaitem_from_type_and_idx(t_dadaobj *r_ob, e_dadaitem_types type, long idx)
{
	long class_id = dadaitem_class_get_id(&r_ob->m_classes, type);
	if (type < 0) {
		// custom type
		if (r_ob->m_classes.di_class[class_id].identifier_to_dadaitem_fn) {
			t_dadaitem_identifier ident;
			ident.flag = 0;
			ident.idx = idx;
			ident.type = type;
			return (t_dadaitem *)(r_ob->m_classes.di_class[class_id].identifier_to_dadaitem_fn)(r_ob->orig_obj, &ident);
		} else
			return NULL;
	} else 
		return dadaitem_class_get_nth_item(r_ob, class_id, idx);
}


long dadaitem_get_index(t_dadaobj *r_ob, t_dadaitem *item)
{
    long class_id = dadaitem_class_get_id(&r_ob->m_classes, item->type);
    switch (r_ob->m_classes.di_class[class_id].alloc_type) {
        case DADA_ITEM_ALLOC_ARRAY:
        case DADA_ITEM_ALLOC_ARRAY_DONT:
        {
            long class_id = dadaitem_class_get_id(&r_ob->m_classes, item->type);
            t_dadaitem_identifier ident;
            ident.flag = 0;
            ident.idx = 0;
            ident.type = item->type;
            
            t_dadaitem *first_item = dadaitem_from_type_and_idx(r_ob, item->type, 0);
            
            return ((long)item - (long)first_item)/r_ob->m_classes.di_class[class_id].element_size;
        }
            break;
        case DADA_ITEM_ALLOC_OBJLLLL:
        {
            t_llllelem *elem;
            t_llll *ll = dadaitem_get_class_llll(r_ob, class_id);
            long count = 0;
            for (elem = ll->l_head; elem; elem = elem->l_next, count++)
                if (hatom_getobj(&elem->l_hatom) == item)
                    return count;
            return -1;
        }
            break;
        default:
            return -1;
            break;
    }
}


char pixel_to_dadaitem_do_fn(t_dadaobj *r_ob, t_dadaitem *item, void *data)
{
	t_dadaitem **found = (t_dadaitem **)(((void **)data)[0]);
	t_dadaitem_identifier *result = (t_dadaitem_identifier *)(((void **)data)[1]);
	t_pt coord = *(t_pt *)(((void **)data)[2]);
	double selection_pad = *(double *)(((void **)data)[3]);
	double selection_pad_squared = *(double *)(((void **)data)[4]);
	switch (item->type) {

		case DADAITEM_TYPE_BALL:
			if (pt_pt_distance_squared(item->coord, coord) <= selection_pad_squared) {
				if (result) {
					result->type = DADAITEM_TYPE_BALL;
					result->idx = dadaitem_get_index((t_dadaobj *)r_ob, item);
				}
				*found = item;
				return 1;
			}
			break;
		
		case DADAITEM_TYPE_VERTEX:
            if (dadaitem_is_pt_in_rect_tolerance(item, coord, r_ob->m_interface.selection_tolerance)) {
				if (result) {
					result->type = DADAITEM_TYPE_VERTEX;
					result->idx = dadaitem_get_index((t_dadaobj *)r_ob, item);
				}
				*found = item;
				return 1;
			}
			break;

		case DADAITEM_TYPE_BLOCK:
			if (dadaitem_is_pt_in_rect(item, coord)) {
				if (result) {
					result->type = DADAITEM_TYPE_BLOCK;
					result->idx = dadaitem_get_index((t_dadaobj *)r_ob, item);
				}
				*found = item;
				return 1;
			}
			break;

		case DADAITEM_TYPE_COIN:
			if (dadaitem_is_pt_in_rect(item, coord)) {
				if (result) {
					result->type = DADAITEM_TYPE_COIN;
					result->idx = dadaitem_get_index((t_dadaobj *)r_ob, item);
				}
				*found = item;
				return 1;
			}
			break;

		case DADAITEM_TYPE_GAMECHAR:
			if (dadaitem_is_pt_in_rect(item, coord)) {
				if (result) {
					result->type = DADAITEM_TYPE_GAMECHAR;
					result->idx = dadaitem_get_index((t_dadaobj *)r_ob, item);
				}
				*found = item;
				return 1;
			}
			break;
			
        case DADAITEM_TYPE_PORTAL:
            if (dadaitem_is_pt_in_rect(item, coord)) {
                if (result) {
                    result->type = DADAITEM_TYPE_PORTAL;
                    result->idx = dadaitem_get_index((t_dadaobj *)r_ob, item);
                }
                *found = item;
                return 1;
            }
            break;
            

        default:
			break;
	}

	return 0;
}


t_dadaitem *pixel_to_dadaitem(t_dadaobj *r_ob, t_pt pt, t_object *view, long modifiers, t_pt *coordinates, double selection_pad, t_dadaitem_identifier *identifier)
{
	t_dadaitem *found = NULL;
	
	if (identifier) {
		identifier->idx = identifier->secondary_idx = identifier->tertiary_idx = -1;
		identifier->type = DADAITEM_TYPE_NONE;
		identifier->flag = 0;
	}
	
	t_pt coord = pix_to_coord_from_view(r_ob, view, pt);
	if (coordinates)
		*coordinates = coord;
	
	double selection_pad_squared = selection_pad * selection_pad;
	void *data[5];
	data[0] = &found;
	data[1] = identifier;
	data[2] = &coord;
	data[3] = &selection_pad;
	data[4] = &selection_pad_squared;
	
	dadaobj_dadaitem_iterate_all(r_ob, pixel_to_dadaitem_do_fn, data);
	
	return found;
}





/// *************************************///
///				ITERATORS				 ///
/// *************************************///



void dadaobj_dadaitem_iterate_for_class(t_dadaobj *r_ob, e_dadaitem_types class_type, dadaitem_iterfn iterfn, void *data)
{
	t_item_class_manager *man = &r_ob->m_classes;
	long class_id = dadaitem_class_get_id(man, class_type);
	t_dadaitem *item;
	switch (man->di_class[class_id].alloc_type) {
		case DADA_ITEM_ALLOC_ARRAY:
		{
			long j;
			long num_bytes = man->di_class[class_id].element_size;
			for (j = 0, item = dadaitem_class_get_nth_item(r_ob, class_id, 0); item && j < dadaitem_class_get_num_items_from_id(man, class_id);
				 j++, item = (t_dadaitem *)move_pointer_forward(item, num_bytes))
				if ((iterfn)(r_ob, item, data))
					return;
		}
			break;
		case DADA_ITEM_ALLOC_OBJLLLL:
		{
			t_llllelem *elem;
			t_llll *ll = dadaitem_get_class_llll(r_ob, class_id);
			for (elem = ll->l_head; elem; elem = elem->l_next)
				if ((iterfn)(r_ob, (t_dadaitem *)hatom_getobj(&elem->l_hatom), data))
					return;
		}
			break;
		default:
			break;
	}
}

void dadaitem_iterate_all_extended(t_dadaobj *r_ob, dadaitem_itertypefn itertypefn, void *data1, dadaitem_iterfn iterfn, void *data2)
{
	long i;
	t_item_class_manager *man = &r_ob->m_classes;
	for (i = 0; i < man->num_di_classes; i++) {
		if (!itertypefn || itertypefn(r_ob, &man->di_class[i], data1)) {
			t_dadaitem *item;
			switch (man->di_class[i].alloc_type) {
				case DADA_ITEM_ALLOC_ARRAY:
                case DADA_ITEM_ALLOC_ARRAY_DONT:
				{
					long j;
					long num_bytes = man->di_class[i].element_size;
					for (j = 0, item = dadaitem_class_get_nth_item(r_ob, i, 0); item && j < dadaitem_class_get_num_items_from_id(man, i);
						 j++, item = (t_dadaitem *)move_pointer_forward(item, num_bytes))
						if ((iterfn)(r_ob, item, data2))
							return;
				}
					break;
				case DADA_ITEM_ALLOC_OBJLLLL:
				{
					t_llllelem *elem;
					t_llll *ll = dadaitem_get_class_llll(r_ob, i);
					for (elem = ll->l_head; elem; elem = elem->l_next)
						if ((iterfn)(r_ob, (t_dadaitem *)hatom_getobj(&elem->l_hatom), data2))
							return;
				}
					break;
				default:
					break;
			}			
		}
	}
}

void dadaobj_dadaitem_iterate_all(t_dadaobj *r_ob, dadaitem_iterfn iterfn, void *data)
{
	dadaitem_iterate_all_extended(r_ob, NULL, NULL, iterfn, data);
}


char dadaitem_iterate_all_selectable_fn(t_dadaobj *r_ob, t_dadaitem_class *cl, void *data)
{
	return cl->selectable;
}

void dadaobj_dadaitem_iterate_all_selectable(t_dadaobj *r_ob, dadaitem_iterfn iterfn, void *data)
{
	dadaitem_iterate_all_extended(r_ob, dadaitem_iterate_all_selectable_fn, NULL, iterfn, data);
}


/// *************************************///
///         DADAITEM SELECTION           ///
/// *************************************///



void dadaobj_selection_select_item(t_dadaobj *r_ob, t_dadaitem *item, e_selection_modes mode)
{
	t_interface_manager *man = &r_ob->m_interface;
	switch (mode) {
		case k_SELECTION_MODE_FORCE_SELECT:
			if (!item->selected) 
				item->selected = llll_appendobj(man->selection, item, 0, WHITENULL_llll);
			break;
		case k_SELECTION_MODE_FORCE_UNSELECT:
			if (item->selected) {
				llll_destroyelem(item->selected);
				item->selected = NULL;
			}
			break;
		default:
			if (item->selected) {
				llll_destroyelem(item->selected);
				item->selected = NULL;
			} else {
				item->selected = llll_appendobj(man->selection, item, 0, WHITENULL_llll);
			}
			break;
	}
}

void dadaobj_selection_preselect_item(t_dadaobj *r_ob, t_dadaitem *item, e_selection_modes mode)
{
	t_interface_manager *man = &r_ob->m_interface;
	switch (mode) {
		case k_SELECTION_MODE_FORCE_SELECT:
			if (!item->preselected) 
				item->preselected = llll_appendobj(man->preselection, item, 0, WHITENULL_llll);
			break;
		case k_SELECTION_MODE_FORCE_UNSELECT:
			if (item->preselected) {
				llll_destroyelem(item->preselected);
				item->preselected = NULL;
			}
			break;
		default:
			if (item->preselected) {
				llll_destroyelem(item->preselected);
				item->preselected = NULL;
			} else {
				item->preselected = llll_appendobj(man->preselection, item, 0, WHITENULL_llll);
			}
			break;
	}
}


void dadaobj_selection_clear_selection(t_dadaobj *r_ob) 
{
	t_interface_manager *man = &r_ob->m_interface;
	t_llllelem *elem;	
	for (elem = man->selection->l_head; elem; elem = elem->l_next) {
		t_dadaitem *item = (t_dadaitem *)hatom_getobj(&elem->l_hatom);
		item->selected = NULL;
	}
	llll_clear(man->selection);
}

void dadaobj_selection_clear_preselection(t_dadaobj *r_ob) 
{
	t_interface_manager *man = &r_ob->m_interface;
	t_llllelem *elem;
	for (elem = man->preselection->l_head; elem; elem = elem->l_next) {
		t_dadaitem *item = (t_dadaitem *)hatom_getobj(&elem->l_hatom);
		item->preselected = NULL;
	}
	llll_clear(man->preselection);
}

void dadaobj_selection_move_preselection_to_selection(t_dadaobj *r_ob, e_selection_modes mode)
{
	t_interface_manager *man = &r_ob->m_interface;
	if (man->preselection->l_head) {
		t_llllelem *elem;
		for (elem = man->preselection->l_head; elem; elem = elem->l_next) {
			t_dadaitem *item = (t_dadaitem *)hatom_getobj(&elem->l_hatom);
			dadaobj_selection_select_item(r_ob, item, mode);
		}
		dadaobj_selection_clear_preselection(r_ob);
	}
}

	
char dadaobj_selection_preselect_items_in_rectangle_default_fn(t_dadaobj *r_ob, t_dadaitem *item, void *data)
{
	t_rect rect = *(t_rect *)data;
	if (is_pt_in_rectangle_extended(item->coord, rect))
		dadaobj_selection_preselect_item(r_ob, item, k_SELECTION_MODE_FORCE_SELECT);
	return 0;
}


void dadaobj_selection_preselect_items_in_rectangle(t_dadaobj *r_ob, t_object *view, t_rect coord)
{
	if (r_ob->m_interface.preselect_items_in_rectangle)
		(r_ob->m_interface.preselect_items_in_rectangle)(r_ob, view, coord);
	else
		dadaobj_dadaitem_iterate_all_selectable(r_ob, dadaobj_selection_preselect_items_in_rectangle_default_fn, &coord);
	jbox_redraw((t_jbox *)r_ob->orig_obj);
}


char dadaobj_selection_select_all_fn(t_dadaobj *r_ob, t_dadaitem *item, void *data)
{
    dadaobj_selection_select_item(r_ob, item, k_SELECTION_MODE_FORCE_SELECT);
    return 0;
}

void dadaobj_selection_select_all(t_dadaobj *r_ob)
{
    dadaobj_dadaitem_iterate_all_selectable(r_ob, dadaobj_selection_select_all_fn, NULL);
}


void dadaobj_selection_iterate(t_dadaobj *r_ob, dadaitem_iterfn iterfn, void *data)
{
	t_llllelem *elem, *nextelem;
	t_interface_manager *man = &r_ob->m_interface;

    // flagging elements for processing (useful for any process which needs to actually change the selection, such as duplication, deletion etc)
    for (elem = man->selection->l_head; elem; elem = elem->l_next) {
        t_dadaitem *item = (t_dadaitem *)hatom_getobj(&elem->l_hatom);
        item->internal_flags |= DADAITEM_FLAG_TOPROCESS;
    }
    
    // actually processing them
	for (elem = man->selection->l_head; elem; elem = nextelem) {
        nextelem = elem->l_next;
		t_dadaitem *item = (t_dadaitem *)hatom_getobj(&elem->l_hatom);
        if ((item->internal_flags & DADAITEM_FLAG_TOPROCESS) && (iterfn)(r_ob, item, data)) {
            item->internal_flags &= ~DADAITEM_FLAG_TOPROCESS;
            return;
        }
	}
}

char dadaobj_selection_force_rebuild_llll_fn(t_dadaobj *r_ob, t_dadaitem *item, void *data)
{
	if (item->selected)
		item->selected = llll_appendobj(r_ob->m_interface.selection, item, 0, WHITENULL_llll);
	return 0;
}

void dadaobj_selection_force_rebuild_llll(t_dadaobj *r_ob)
{
	llll_clear(r_ob->m_interface.selection);
	dadaobj_dadaitem_iterate_all_selectable(r_ob, dadaobj_selection_force_rebuild_llll_fn, NULL);
}

char dadaobj_preselection_force_rebuild_llll_fn(t_dadaobj *r_ob, t_dadaitem *item, void *data)
{
	if (item->preselected)
		item->preselected = llll_appendobj(r_ob->m_interface.preselection, item, 0, WHITENULL_llll);
	return 0;
}

void dadaobj_preselection_force_rebuild_llll(t_dadaobj *r_ob)
{
	llll_clear(r_ob->m_interface.preselection);
	dadaobj_dadaitem_iterate_all_selectable(r_ob, dadaobj_preselection_force_rebuild_llll_fn, NULL);
}



char dadaobj_selection_contains_type(t_dadaobj *r_ob, e_dadaitem_types type)
{
	t_interface_manager *man = &r_ob->m_interface;
 	t_llllelem *elem;
	for (elem = man->selection->l_head; elem; elem = elem->l_next) {
		t_dadaitem *item = (t_dadaitem *)hatom_getobj(&elem->l_hatom);
		if (item->type == type)
			return true;
	}
	return false;
}


char dadaobj_selection_move_delta_fn(t_dadaobj *r_ob, t_dadaitem *item, void *data)
{
	t_pt delta_coord = *(t_pt *)(((void **)data)[0]);
	char flags = *(char *)(((void **)data)[1]);
	dadaitem_move_delta(r_ob, item, delta_coord, flags);
	return 0;
}


void dadaobj_selection_move_delta(t_dadaobj *r_ob, t_pt delta_coord, char flags)
{
	void *data[2];
	data[0] = &delta_coord;
	data[1] = &flags;
	dadaobj_selection_iterate(r_ob, dadaobj_selection_move_delta_fn, data);
}

char dadaobj_selection_delete_fn(t_dadaobj *r_ob, t_dadaitem *item, void *data)
{
	dadaitem_delete((t_dadaobj *)r_ob, item->type, dadaitem_get_index((t_dadaobj *)r_ob, item), *((char *)data));
	return 0;
}


void dadaobj_selection_delete(t_dadaobj *r_ob, char flags)
{
	dadaobj_selection_iterate(r_ob, dadaobj_selection_delete_fn, &flags);
}


char dadaobj_selection_duplicate_fn(t_dadaobj *r_ob, t_dadaitem *item, void *data)
{
    long idx = dadaitem_get_index(r_ob, item);
    long newidx = dadaitem_duplicate(r_ob, item->type, idx, 0);
    t_dadaitem *newitem = dadaitem_from_type_and_idx(r_ob, item->type, newidx);
    if (newitem)
        dadaobj_selection_select_item(r_ob, newitem, k_SELECTION_MODE_FORCE_SELECT);
    dadaobj_selection_select_item(r_ob, item, k_SELECTION_MODE_FORCE_UNSELECT);
    return 0;
}


void dadaobj_selection_duplicate(t_dadaobj *r_ob, char flags)
{
    dadaobj_selection_iterate(r_ob, dadaobj_selection_duplicate_fn, &flags);
}


char dadaitem_is_selected(t_dadaitem *it)
{
	return (it->selected != NULL);
}


char dadaitem_is_preselected(t_dadaitem *it)
{
	return (it->preselected != NULL);
}

char dadaitem_is_preselected_xor_selected(t_dadaitem *it)
{
	return (dadaitem_is_preselected(it) ^ dadaitem_is_selected(it));
}

char dadaitem_is_selectable(t_dadaobj *r_ob, t_dadaitem *it)
{
    long class_id = dadaitem_class_get_id(&r_ob->m_classes, it->type);
    if (class_id >= 0)
        return r_ob->m_classes.di_class[class_id].selectable;
    return false;
}

char dadaitem_is_in_background(t_dadaobj *r_ob, t_dadaitem *it)
{
    long class_id = dadaitem_class_get_id(&r_ob->m_classes, it->type);
    if (class_id >= 0)
        return r_ob->m_classes.di_class[class_id].include_in_background;
    return false;
}





/// *************************************///
///         DADAITEM ATTRIBUTES          ///
/// *************************************///


t_llll *dadaitem_get_attr_as_llll(t_dadaobj *r_ob, t_dadaitem *item, t_bach_attribute *attr)
{
	t_llll *ll = llll_get();
	long ac = 0;
	t_atom *av = NULL;
    if (attr->getter != (bach_getter_fn)dada_default_get_bach_attr)
        (attr->getter)(&r_ob->m_inspector, item, attr, &ac, &av);
    else
        dada_default_get_bach_attr(r_ob->orig_obj, item, attr, &ac, &av);
	llll_appendsym(ll, attr->name, 0, WHITENULL_llll);
	llll_chain(ll, llllobj_parse_llll(r_ob->orig_obj, LLLL_OBJ_UI, NULL, ac, av, LLLL_PARSE_CLONE));
	bach_freeptr(av);
	return ll;
}



// if attributes are defined!
void dadaitem_set_attr_from_llll(t_dadaobj *r_ob, t_dadaitem *item, t_bach_attribute *attr, t_llll *ll, char ll_has_symbol_router)
{
	t_atom *av = NULL;
	long ac = llll_deparse(ll, &av, 0, 0);

	// setting attribute
	if (attr->setter)
		((*attr->setter)(r_ob->orig_obj, item, attr, ll_has_symbol_router && ac ? ac - 1 : ac, ll_has_symbol_router && ac ? av + 1 : av));
	else 
		dada_default_set_bach_attr(r_ob->orig_obj, item, attr, ll_has_symbol_router && ac ? ac - 1 : ac, ll_has_symbol_router && ac ? av + 1 : av);
	
	// notifying
	if (r_ob->dadanotify)
		(r_ob->dadanotify)(r_ob, _sym_attr_modified, attr->name, item, NULL);

	bach_freeptr(av);
}	



// if attributes are defined!
t_llll *dadaitem_get_as_llll(t_dadaobj *r_ob, t_dadaitem *item)
{
	t_llll *ll = llll_get();
	long class_id = dadaitem_class_get_id(&r_ob->m_classes, item->type);
	t_bach_attr_manager *man = r_ob->m_inspector.attr_manager;
    long i, num_attrs = man->num_attr[class_id];
    for (i = 0; i < num_attrs; i++)
        if (!(man->attr[class_id][i].flags & DADA_ATTRIBUTE_FLAG_DONTRETRIEVE))
            llll_appendllll(ll, dadaitem_get_attr_as_llll(r_ob, item, &man->attr[class_id][i]), 0, WHITENULL_llll);
    return ll;
}


char dadaitem_class_get_as_llll_fn(t_dadaobj *r_ob, t_dadaitem *item, void *data)
{
	t_llll *ll = *(t_llll **)(((void **)data)[0]);
	long class_id = *(long *)(((void **)data)[1]);
	t_bach_attr_manager *man = ((t_dadaobj *)r_ob)->m_inspector.attr_manager;
	long i, num_attrs = man->num_attr[class_id];
	t_llll *thisitem_ll = llll_get();
    for (i = 0; i < num_attrs; i++) {
        if (!(man->attr[class_id][i].flags & DADA_ATTRIBUTE_FLAG_DONTRETRIEVE))
            llll_appendllll(thisitem_ll, dadaitem_get_attr_as_llll((t_dadaobj *)r_ob, item, &man->attr[class_id][i]), 0, WHITENULL_llll);
    }
	llll_appendllll(ll, thisitem_ll, 0, WHITENULL_llll);
	
	return 0;
}

t_symbol *make_name_plural(t_symbol *name)
{
    char buf[2048];
    snprintf_zero(buf, 2048, "%ss", name->s_name);
    return gensym(buf);
}

// if attributes are defined!
t_llll *dadaitem_class_get_as_llll(t_dadaobj *r_ob, e_dadaitem_types type)
{
	long class_id = dadaitem_class_get_id(&r_ob->m_classes, type);

	t_llll *ll = llll_get();
	void *data[2];
	data[0] = &ll;
	data[1] = &class_id;
	dadaobj_dadaitem_iterate_for_class(r_ob, type, dadaitem_class_get_as_llll_fn, data);
	
	llll_prependsym(ll, make_name_plural(r_ob->m_classes.di_class[class_id].name), 0, WHITENULL_llll);

	return ll;
}
	
	
// if attributes are defined!
void dadaitem_set_from_llll(t_dadaobj *r_ob, t_dadaitem *item, t_llll *ll, long flags)
{
    if (!item)
        return;
    
	long class_id = dadaitem_class_get_id(&r_ob->m_classes, item->type);
	t_bach_attr_manager *man = r_ob->m_inspector.attr_manager;
	
	t_llllelem *elem;
	for (elem = ll->l_head; elem; elem = elem->l_next) {
		if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
			t_llll *ll = hatom_getllll(&elem->l_hatom);
			if (ll->l_head && hatom_gettype(&ll->l_head->l_hatom) == H_SYM) {
				t_bach_attribute *attr = get_bach_attribute(man, class_id, hatom_getsym(&ll->l_head->l_hatom));
				if (attr && !(attr->flags & DADA_ATTRIBUTE_FLAG_DONTSET))
					dadaitem_set_attr_from_llll(r_ob, item, attr, ll, true);
			}
		}
	}
}

// if attributes are defined!
t_dadaitem *dadaitem_add_from_llll(t_dadaobj *r_ob, e_dadaitem_types type, t_llll *ll, long flags)
{
	long class_id = dadaitem_class_get_id(&r_ob->m_classes, type);
	t_bach_attr_manager *man = r_ob->m_inspector.attr_manager;
	
	if (flags & DIA_UNDO)
		undo_add_interface_step_for_dadaitem_class(r_ob, type, combine_string_with_symbol_for_undo("Add", r_ob->m_classes.di_class[class_id].label, false));

	long idx = dadaitem_add(r_ob, type, build_pt(0, 0), 0, 0, DADA_BLACK, NULL, 0, flags);
	t_dadaitem *item = dadaitem_from_type_and_idx(r_ob, type, idx);

    if (item) {
        t_llllelem *elem;
        for (elem = ll->l_head; elem; elem = elem->l_next) {
            if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
                t_llll *ll = hatom_getllll(&elem->l_hatom);
                if (ll->l_head && hatom_gettype(&ll->l_head->l_hatom) == H_SYM) {
                    t_bach_attribute *attr = get_bach_attribute(man, class_id, hatom_getsym(&ll->l_head->l_hatom));
                    if (attr)
                        dadaitem_set_attr_from_llll(r_ob, item, attr, ll, true);
                }
            }
        }
    }

	if (flags & DIA_POSTPROCESS)
		postprocess_for_dadaitem_class(r_ob, class_id);

	return item;
}


// if attributes are defined!
void dadaitem_class_set_from_llll(t_dadaobj *r_ob, e_dadaitem_types type, t_llll *ll, long flags)
{
	t_llllelem *elem;
	long id = dadaitem_class_get_id(&r_ob->m_classes, type);

	if (flags & DIA_UNDO)
		undo_add_interface_step_for_dadaitem_class(r_ob, type, combine_string_with_symbol_for_undo("Set", r_ob->m_classes.di_class[id].label, false));

	dadaobj_dadaitem_class_clear(r_ob, type, 0);
	
	for (elem = ll->l_head; elem; elem = elem->l_next) {
		if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
			long idx = dadaitem_add(r_ob, type, build_pt(0, 0), 0, 0, DADA_BLACK, NULL, 0, flags & DIA_USE_ATTR_DEFAULTS);
			t_dadaitem *item = dadaitem_from_type_and_idx(r_ob, type, idx);
			dadaitem_set_from_llll(r_ob, item, hatom_getllll(&elem->l_hatom), 0);
		}
	}

	if (flags & DIA_POSTPROCESS)
		postprocess_for_dadaitem_class(r_ob, id);
}


// DESTRUCTIVE ON MESSAGE
void dadaitem_set_from_message(t_dadaobj *r_ob, t_llll *message, long flags)
{
	if (!message || !message->l_head || hatom_gettype(&message->l_head->l_hatom) != H_SYM)
		return;

	e_dadaitem_types type = dadaitem_class_name_to_type(&r_ob->m_classes, hatom_getsym(&message->l_head->l_hatom));
	llll_behead(message);
	
	if (type != DADAITEM_TYPE_NONE)  {
		long class_id = dadaitem_class_get_id(&r_ob->m_classes, type), item_id = -1;
		if (message && message->l_head && hatom_gettype(&message->l_head->l_hatom) == H_LONG) {
			item_id = hatom_getlong(&message->l_head->l_hatom) - 1;
			llll_behead(message);
			if (item_id >= 0 && item_id < dadaitem_class_get_num_items_from_id(&r_ob->m_classes, class_id))
				dadaitem_set_from_llll(r_ob, dadaitem_class_get_nth_item(r_ob, class_id, item_id), message, flags);
		}
	}
}

// DESTRUCTIVE ON MESSAGE
t_dadaitem *dadaitem_add_from_message(t_dadaobj *r_ob, t_llll *message, long flags)
{
	if (!message || !message->l_head || hatom_gettype(&message->l_head->l_hatom) != H_SYM)
		return NULL;
	
	e_dadaitem_types type = dadaitem_class_name_to_type(&r_ob->m_classes, hatom_getsym(&message->l_head->l_hatom));
	llll_behead(message);

	if (type != DADAITEM_TYPE_NONE) 
		return dadaitem_add_from_llll(r_ob, type, message, flags);
	else
		return NULL;
}

// DESTRUCTIVE ON MESSAGE
void dadaitem_delete_from_message(t_dadaobj *r_ob, t_llll *message, long flags)
{
	if (!message || !message->l_head || hatom_gettype(&message->l_head->l_hatom) != H_SYM)
		return;

	e_dadaitem_types type = dadaitem_class_name_to_type(&r_ob->m_classes, hatom_getsym(&message->l_head->l_hatom));
	llll_behead(message);

	if (type != DADAITEM_TYPE_NONE && message && message->l_head && hatom_gettype(&message->l_head->l_hatom) == H_LONG)  
		dadaitem_delete(r_ob, type, hatom_getlong(&message->l_head->l_hatom) - 1, flags);
}


void dada_default_attr_postprocess(t_bach_inspector_manager *man, void *elem, t_bach_attribute *attr)
{
    if (man && man->thing) {
        t_dadaobj *r_ob = (t_dadaobj *)man->thing;
        dadaobj_invalidate_and_redraw(r_ob);
        dadaobj_add_undo_marker_if_needed(r_ob);
    }
}


void dada_default_attr_preprocess(t_bach_inspector_manager *man, void *elem, t_bach_attribute *attr)
{
    if (man && man->thing && elem) {
        t_dadaitem *item = (t_dadaitem *)elem;
        t_dadaobj *r_ob = (t_dadaobj *)man->thing;
        undo_add_interface_step_for_dadaitem(r_ob, item, DADA_UNDO_OP_MODIFICATION, gensym("Change Attribute"));
    }
}


void dada_default_set_bach_attr(t_object *ob, void *obj, t_bach_attribute *attr, long ac, t_atom *av)
{
	long i;
	void *field = (char *) obj + attr->field_position;
	//	t_atom none_atom;
	
	if (!ac || !av) {
		ac = 0;
		av = NULL;
	}
		
	switch (attr->attr_type) {
		case k_BACH_ATTR_CHAR:
			if (attr->display_type == k_BACH_ATTR_DISPLAY_CHAR)
				*((char *)field) = (ac ? atom_getsym(av)->s_name[0] : 0);
			else
				*((char *)field) = (ac ? atom_getlong(av) : 0);
			break;
		case k_BACH_ATTR_LONG:
			*((long *)field) = (ac ? atom_getlong(av) : 0);
			break;
		case k_BACH_ATTR_RAT:
		{
			t_llll *parsed = llllobj_parse_llll(ob, LLLL_OBJ_UI, NULL, ac, av, LLLL_PARSE_CLONE);
			*((t_rational *)field) = (parsed->l_head && is_hatom_number(&parsed->l_head->l_hatom) ? (hatom_gettype(&parsed->l_head->l_hatom) == H_DOUBLE ? approx_double_with_rat_fixed_den(hatom_getdouble(&parsed->l_head->l_hatom), CONST_RAT_APPROX_TEMPI_DEN, 0, NULL) : hatom_getrational(&parsed->l_head->l_hatom) ) : long2rat(0));
			llll_free(parsed);
			break;
		}
		case k_BACH_ATTR_COLOR:
			*((t_jrgba *)field) = (ac >= 3 ? build_jrgba(atom_getfloat(av), atom_getfloat(av+1), atom_getfloat(av+2), ac >= 4 ? atom_getfloat(av+3) : 1.) : build_jrgba(0, 0, 0, 1));
			break;
		case k_BACH_ATTR_DOUBLE:
			*((double *)field) = (ac ? atom_getfloat(av) : 0);
			break;
		case k_BACH_ATTR_SYM:
			*((t_symbol **)field) = (ac == 1 && atom_gettype(av) == A_SYM ? atom_getsym(av) : (ac ? ac_av_to_single_symbol(ac, av) : _llllobj_sym_empty_symbol));
			break;
		case k_BACH_ATTR_ATOM:
			*((t_atom *)field) = *av;
			break;
		case k_BACH_ATTR_LONG_ARRAY:
			for (i = 0; i < attr->attr_size && i < ac; i++)
				((long *)field)[i] = atom_getlong(av+i);
			break;
		case k_BACH_ATTR_RAT_ARRAY:
		{
			t_llll *parsed = llllobj_parse_llll(ob, LLLL_OBJ_UI, NULL, ac, av, LLLL_PARSE_CLONE);
			t_llllelem *elem;
			for (i = 0, elem = parsed->l_head; i < attr->attr_size && i < ac && elem; i++, elem = elem->l_next)
				if (is_hatom_number(&elem->l_hatom))
					((t_rational *)field)[i] = hatom_getrational(&elem->l_hatom);
			llll_free(parsed);
			break;
		}
		case k_BACH_ATTR_DOUBLE_ARRAY:
			for (i = 0; i < attr->attr_size && i < ac; i++)
				((double *)field)[i] = atom_getfloat(av+i);
			break;
		case k_BACH_ATTR_ATOM_ARRAY:
			for (i = 0; i < attr->attr_size && i < ac; i++)
				((t_atom *)field)[i] = av[i];
			break;
		case k_BACH_ATTR_ATOM_ARRAY_VARSIZE:
			for (i = 0; i < attr->attr_size && i < ac; i++)
				((t_atom *)field)[i] = av[i];
			*((long *)((char *) obj + attr->field_position_for_var_attr_size)) = ac;
			break;
		case k_BACH_ATTR_LLLL:
			if (*((t_llll **)field))
				llll_free(*((t_llll **)field));
			*((t_llll **)field) = llllobj_parse_llll(ob, LLLL_OBJ_UI, NULL, ac, av, LLLL_PARSE_CLONE);
			break;
		case k_BACH_ATTR_BIT:
			if (ac) {
				if (atom_getlong(av)) 
					*((long *)field) |= attr->attr_size;
				else
					*((long *)field) &= ~attr->attr_size;
			}
			break;
		case k_BACH_ATTR_OBJ:
			//there's no default for this case! handle each case separately
			break;
		default:
			break;
	}
}


// like atom_setparse, will allocate memory if ac and av are NULL, otherwise will attempt to use the indicated memory // (t_note *)obj
void dada_default_get_bach_attr(t_object *ob, void *obj, t_bach_attribute *attr, long *ac, t_atom **av)
{
	void *field = (char *) obj + attr->field_position;
	long size;
	char *string;
	
	size = attr->attr_type == k_BACH_ATTR_ATOM_ARRAY_VARSIZE ? *((long *)((char *) obj + attr->field_position_for_var_attr_size)) : attr->attr_size;
	string = field2string(field, attr->attr_type, size, -1); // all decimals, we'll trim them later
	atom_setparse_debug(ac, av, string);
	bach_freeptr(string);
}


long dada_default_attr_inactive(t_object *ob, void *elem, t_bach_attribute *attr){
	return 0;	// active
}


t_bach_attribute *get_dada_attribute(t_dadaobj *r_ob, e_dadaitem_types elemtype, t_symbol *name)
{
	long di_class_id = dadaitem_class_get_id(&r_ob->m_classes, elemtype);
	return get_bach_attribute(r_ob->m_inspector.attr_manager, di_class_id, name);
}


t_dadaitem *dadaitem_get_from_ID(t_dadaobj *r_ob, long ID)
{
    return (t_dadaitem *)shashtable_retrieve(r_ob->IDtable, ID);
}

char dadaitem_get_from_name_fn(t_dadaobj *r_ob, t_dadaitem *item, void *data)
{
    t_dadaitem **found = (t_dadaitem **)(((void **)data)[0]);
    t_symbol *name = (t_symbol *)(((void **)data)[1]);

    if (item->name == name) {
        *found = item;
        return 1;
    }
    return 0;
}

t_dadaitem *dadaitem_get_from_name(t_dadaobj *r_ob, t_symbol *name)
{
    t_dadaitem *found = NULL;
    void *data[2];
    data[0] = &found;
    data[1] = name;
    
    dadaobj_dadaitem_iterate_all(r_ob, (dadaitem_iterfn)dadaitem_get_from_name_fn, data);
    
    return found;
}



char dadaitem_append_from_name_fn(t_dadaobj *r_ob, t_dadaitem *item, void *data)
{
    t_llll *ll = (t_llll *)(((void **)data)[0]);
    t_symbol *name = (t_symbol *)(((void **)data)[1]);
    
    if (item->name == name)
        llll_appendobj(ll, item);

    return 0;
}

t_llll *dadaitem_get_all_from_name(t_dadaobj *r_ob, t_symbol *name)
{
    t_llll *found = llll_get();
    void *data[2];
    data[0] = found;
    data[1] = name;
    
    dadaobj_dadaitem_iterate_all(r_ob, (dadaitem_iterfn)dadaitem_append_from_name_fn, data);
    
    return found;
}



long dadaitem_get_ID_from_name(t_dadaobj *r_ob, t_symbol *name)
{
    t_dadaitem *res = dadaitem_get_from_name(r_ob, name);
    return res ? res->ID : 0;
}
