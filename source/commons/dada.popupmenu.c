/**
	@file
	dada.popupmenu.c
	Popup menu functions for dada library

	by Daniele Ghisi
*/

#include "dada.popupmenu.h"

void initialize_popup_menus(t_dadaobj *x)
{
	long i;
	x->m_popup_menu.num_popup_menus = 0;
	x->m_popup_menu.popup_is_shown = false;
	x->m_popup_menu.curr_popup_item = NULL;
	for (i = 0; i < DADA_MAX_NUM_POPUP_SUBMENUS; i++) {
		x->m_popup_menu.popup_menus[i] = NULL;
	}
	x->m_popup_menu.pointers_to_func = llll_get();
	x->m_popup_menu.labels = llll_get();
	x->m_popup_menu.addresses = llll_get();
}


// also handles the null case
void safe_next(t_llllelem **elem){
	if (*elem)
		*elem = (*elem)->l_next;
}



char build_popup_menu(t_dadaobj *x, t_llll *structure, t_llll *pointers_to_functions, 
					 t_llll *textcolors, t_llll *checked, t_llll *disabled, t_llll *icons) 
{
	t_popupmenu_manager *m_popup_menu = &x->m_popup_menu;
	// 1. counting the number of needed menus
	t_llllelem *elem, *func, *color, *check, *disab, *icon;
	int count = 1;
	for (elem = structure->l_head; elem; elem = elem->l_next) {
		if (hatom_gettype(&elem->l_hatom) == H_LLLL)
			count++;
	}
	
	if (count > DADA_MAX_NUM_POPUP_SUBMENUS)
		return -1; // can't build, not enough memory
	
	// 2. creating space for structures
	m_popup_menu->num_popup_menus = count;
	
	// 3. building root menu
	long ID = 1;
	if (!m_popup_menu->popup_menus[0])
		m_popup_menu->popup_menus[0] = jpopupmenu_create();
	else
		jpopupmenu_clear(m_popup_menu->popup_menus[0]);
	llll_clear(m_popup_menu->pointers_to_func);
	llll_clear(m_popup_menu->labels);
	llll_clear(m_popup_menu->addresses);
	
	
	// 2. putting elems in the same shape as the bas structure, in case
	// some element was used against a whole llll

	t_llll *real_pointers_to_functions = llll_clone(pointers_to_functions);
	t_llll *real_checked = checked && checked->l_head ? llll_clone(checked) : NULL;
	t_llll *real_disabled = disabled && disabled->l_head ? llll_clone(disabled) : NULL;
	t_llll *real_textcolors = textcolors && textcolors->l_head ? llll_clone(textcolors) : NULL;
	t_llll *real_icons = icons && icons->l_head ? llll_clone(icons) : NULL;

	llll_reshape_scalarmode(&real_pointers_to_functions, structure);
	llll_reshape_scalarmode(&real_checked, structure);
	llll_reshape_scalarmode(&real_disabled, structure);
	llll_reshape_scalarmode(&real_textcolors, structure);
	llll_reshape_scalarmode(&real_icons, structure);
	

	// 3. creating menus, in stack form
	//////////////////////////
	t_llll_stack *elem_stack = llll_stack_new();
	t_llll_stack *func_stack = llll_stack_new();
	t_llll_stack *icon_stack = llll_stack_new();
	t_llll_stack *check_stack = llll_stack_new();
	t_llll_stack *disab_stack = llll_stack_new();
	t_llll_stack *color_stack = llll_stack_new();
	t_llll_stack *count_stack = llll_stack_new();
	
	elem = structure->l_head;
	func = real_pointers_to_functions->l_head;
	icon = real_icons ? real_icons->l_head : NULL;
	check = real_checked ? real_checked->l_head : NULL;
	disab = real_disabled ? real_disabled->l_head : NULL;
	color = real_textcolors ? real_textcolors->l_head : NULL;
	
	int maxcount = 0;
	count = 0;

	t_llll *curr_address = llll_get();
	llll_appendlong(curr_address, 1, 0, WHITENULL_llll);
	
	while (1) {
		while (elem) {
			switch(elem->l_hatom.h_type) {
				case H_SYM:
				case H_LONG:
				case H_DOUBLE:
				case H_RAT:
				{
					t_symbol *sym = hatom_to_symbol(&elem->l_hatom);
					if (sym == gensym("separator")) {
						jpopupmenu_addseperator(m_popup_menu->popup_menus[count]);
						ID++; // in any case, to preserve correspondance in linear structures of m_popup_menu
						llll_appendobj(m_popup_menu->pointers_to_func, (void *)idle_popup_fn, 0, WHITENULL_llll);
						llll_appendsym(m_popup_menu->labels, sym, 0, WHITENULL_llll);
					} else {
						jpopupmenu_additem(m_popup_menu->popup_menus[count], ID++, sym->s_name, 
										   NULL, check && hatom_getlong(&check->l_hatom) ? 1 : 0, disab && hatom_getlong(&disab->l_hatom) ? 1 : 0, NULL);
						llll_appendobj(m_popup_menu->pointers_to_func, hatom_getobj(&func->l_hatom), 0, WHITENULL_llll);
						llll_appendsym(m_popup_menu->labels, sym, 0, WHITENULL_llll);
					}
					
					llll_appendllll_clone(m_popup_menu->addresses, curr_address, 0, WHITENULL_llll, NULL);

					t_llllelem *temp = elem;
					long temp_count = count;
					while (temp && !temp->l_next) {
						// submenu completed: we append it
						t_stack_popup_menu_helper *stackhelper = (t_stack_popup_menu_helper *)temp->l_parent->l_thing.w_obj;
						if (stackhelper) {
							jpopupmenu_addsubmenu(m_popup_menu->popup_menus[stackhelper->father_count], stackhelper->llll_name->s_name, m_popup_menu->popup_menus[temp_count], stackhelper->disabled);
							temp_count = stackhelper->father_count;
						}
						temp = temp->l_parent->l_owner;
					}
					
					elem = elem->l_next;
					safe_next(&func);
					safe_next(&icon);
					safe_next(&check);
					safe_next(&color);
					safe_next(&disab);
					hatom_setlong(&curr_address->l_tail->l_hatom, hatom_getlong(&curr_address->l_tail->l_hatom) + 1);
				}
					break;
					
				case H_LLLL:
				{
					llll_stack_push(elem_stack, elem->l_next);
					llll_stack_push(func_stack, func ? func->l_next : NULL);
					llll_stack_push(icon_stack, icon ? icon->l_next : NULL);
					llll_stack_push(check_stack, check ? check->l_next : NULL);
					llll_stack_push(disab_stack, color ? color->l_next : NULL);
					llll_stack_push(color_stack, disab ? disab->l_next : NULL);
					llll_stack_push(count_stack, (void *)count);

					elem = elem->l_hatom.h_w.w_llll->l_head;
					if (func)
						func = func->l_hatom.h_w.w_llll->l_head;
					if (icon)
						icon = icon->l_hatom.h_w.w_llll->l_head;
					if (check)
						check = check->l_hatom.h_w.w_llll->l_head;
					if (color)
						color = color->l_hatom.h_w.w_llll->l_head;
					if (disab)
						disab = disab->l_hatom.h_w.w_llll->l_head;
					
					llll_appendlong(curr_address, 1, 0, WHITENULL_llll);
					
					maxcount++;
					if (!m_popup_menu->popup_menus[maxcount])
						m_popup_menu->popup_menus[maxcount] = jpopupmenu_create();
					else
						jpopupmenu_clear(m_popup_menu->popup_menus[maxcount]);

					// submenu info
					t_stack_popup_menu_helper *stackhelper = (t_stack_popup_menu_helper *)bach_newptr(1 * sizeof(t_stack_popup_menu_helper));
					stackhelper->llll_name = hatom_getsym(&elem->l_hatom);
					stackhelper->father_count = count;
					stackhelper->disabled = disab && hatom_getlong(&disab->l_hatom) ? 1 : 0;
					elem->l_parent->l_thing.w_obj = stackhelper;
					
					llll_appendobj(m_popup_menu->pointers_to_func, (void *)idle_popup_fn, 0, WHITENULL_llll);
					llll_appendsym(m_popup_menu->labels, stackhelper->llll_name, 0, WHITENULL_llll);
					llll_appendllll_clone(m_popup_menu->addresses, curr_address, 0, WHITENULL_llll, NULL);

					ID++; // a dummy ID corresponds to the submenu name
					
					count = maxcount;
					
					elem = elem->l_next;
					safe_next(&func);
					safe_next(&icon);
					safe_next(&check);
					safe_next(&color);
					safe_next(&disab);
					hatom_setlong(&curr_address->l_tail->l_hatom, hatom_getlong(&curr_address->l_tail->l_hatom) + 1);
				}
					break;
					
				default:
					elem = elem->l_next;
					safe_next(&func);
					safe_next(&icon);
					safe_next(&check);
					safe_next(&color);
					safe_next(&disab);
					hatom_setlong(&curr_address->l_tail->l_hatom, hatom_getlong(&curr_address->l_tail->l_hatom) + 1);
					break;
			}
		}
		if (!elem_stack->s_items)
			break;
		
		elem = (t_llllelem *) llll_stack_pop(elem_stack);
		func = (t_llllelem *) llll_stack_pop(func_stack);
		icon = (t_llllelem *) llll_stack_pop(icon_stack);
		check = (t_llllelem *) llll_stack_pop(check_stack);
		disab = (t_llllelem *) llll_stack_pop(disab_stack);
		color = (t_llllelem *) llll_stack_pop(color_stack);
		count = (intptr_t)llll_stack_pop(count_stack);
		llll_betail(curr_address);
	}
		
	llll_freethings(structure, LLLL_FREETHING_MEM);

	llll_free(real_pointers_to_functions);
	llll_free(real_checked);
	llll_free(real_disabled);
	llll_free(real_textcolors);
	llll_free(real_icons);
	
	llll_stack_destroy(elem_stack);
	llll_stack_destroy(func_stack);
	llll_stack_destroy(icon_stack);
	llll_stack_destroy(check_stack);
	llll_stack_destroy(disab_stack);
	llll_stack_destroy(color_stack);
	llll_stack_destroy(count_stack);
	
	return 0;
}

void popup_menu_popup(t_dadaobj *r_ob, t_object *view, long initial_item_ID) {
	t_popupmenu_manager *m_popup_menu = &r_ob->m_popup_menu;
	t_pt screen_pt;
	int ptx, pty;
	long curr_cursor = BACH_CURSOR_DEFAULT;
	jmouse_getposition_global(&ptx, &pty);
	screen_pt = build_pt(ptx, pty);
	m_popup_menu->popup_is_shown = true;
	
	if (view) {
		curr_cursor = r_ob->m_cursors.curr_cursor;
		dada_set_cursor(r_ob, view, BACH_CURSOR_DEFAULT);
	}
	
	long chosenelem = jpopupmenu_popup(m_popup_menu->popup_menus[0], screen_pt, initial_item_ID);
	
	t_llllelem *func = llll_getindex(m_popup_menu->pointers_to_func, chosenelem, I_NON_NEGATIVE);
	t_llllelem *sym_elem = llll_getindex(m_popup_menu->labels, chosenelem, I_NON_NEGATIVE);
	t_symbol *sym = sym_elem && hatom_gettype(&sym_elem->l_hatom) == H_SYM ? hatom_getsym(&sym_elem->l_hatom) : NULL;
	t_llllelem *llelem = llll_getindex(m_popup_menu->addresses, chosenelem, I_NON_NEGATIVE);
	t_llll *ll = llelem ? hatom_getllll(&llelem->l_hatom) : NULL;
	
	r_ob->curr_change_is_from_message = false;

	if (func)
		((dada_popup_fn)hatom_getobj(&func->l_hatom))(r_ob, sym, ll);

	m_popup_menu->popup_is_shown = false;
	m_popup_menu->curr_popup_item = NULL;
	
	if (view) 
		dada_set_cursor(r_ob, view, (e_bach_mouse_cursors)curr_cursor);
}


char display_popup_menu(t_dadaobj *r_ob, t_object *view, t_llll *structure, t_llll *pointers_to_functions, 
					  t_llll *textcolors, t_llll *checked, t_llll *disabled, t_llll *icons, long initial_item_ID) 
{
	long res = build_popup_menu(r_ob, structure, pointers_to_functions, textcolors, checked, disabled, icons);
	popup_menu_popup(r_ob, view, initial_item_ID);
	return res;
}

char ezdisplay_popup_menu_for_dadaitem(t_dadaobj *r_ob, t_object *view, t_dadaitem *item, long autodisplay_flags, const char *structure, const char *functions_llll_model, const char *checked, const char *disabled, const char *icons, const char *textcolors, ...)
{
	t_llll *structure_ll = llll_from_text_buf((char *)structure, false);
	t_llll *functions_model_ll = llll_from_text_buf((char *)functions_llll_model, false);
	t_llll *checked_ll = llll_from_text_buf((char *)checked, false);
	t_llll *disabled_ll = llll_from_text_buf((char *)disabled, false);
	t_llll *icons_ll = llll_from_text_buf((char *)icons, false);
	t_llll *textcolors_ll = llll_from_text_buf((char *)textcolors, false);
	t_llll *pointers_to_functions_ll = llll_get();
	
	va_list argptr;
	va_start(argptr, textcolors);
	while (true) {
		void *this_fn = va_arg(argptr, void *);
		if (this_fn == WHITENULL)
			break;
		llll_appendobj(pointers_to_functions_ll, this_fn ? (void *)this_fn : (void *)idle_popup_fn, 0, WHITENULL_llll);
	}
	
	llll_reshape(pointers_to_functions_ll, functions_model_ll, NULL);
	
	r_ob->m_popup_menu.curr_popup_item = item;
	
	if (autodisplay_flags) {
		llll_appendsym(structure_ll, gensym("separator"), 0, WHITENULL_llll);
		llll_appendobj(pointers_to_functions_ll, (void *)idle_popup_fn, 0, WHITENULL_llll);
		if (autodisplay_flags & D_LOCK) {
			llll_appendsym(structure_ll, (item->flags & D_LOCK) ? gensym("Unlock") : gensym("Lock"), 0, WHITENULL_llll);
			llll_appendobj(pointers_to_functions_ll, (void *)dadaitem_popup_change_flag_fn, 0, WHITENULL_llll);
		}
		if (autodisplay_flags & D_MUTE) {
			llll_appendsym(structure_ll, (item->flags & D_MUTE) ? gensym("Unmute") : gensym("Mute"), 0, WHITENULL_llll);
			llll_appendobj(pointers_to_functions_ll, (void *)dadaitem_popup_change_flag_fn, 0, WHITENULL_llll);
		}
		if (autodisplay_flags & D_SOLO) {
			llll_appendsym(structure_ll, (item->flags & D_SOLO) ? gensym("Unsolo") : gensym("Solo"), 0, WHITENULL_llll);
			llll_appendobj(pointers_to_functions_ll, (void *)dadaitem_popup_change_flag_fn, 0, WHITENULL_llll);
		}
		if (autodisplay_flags & D_INACTIVE) {
			llll_appendsym(structure_ll, (item->flags & D_INACTIVE) ? gensym("Make Active") : gensym("Make Inactive"), 0, WHITENULL_llll);
			llll_appendobj(pointers_to_functions_ll, (void *)dadaitem_popup_change_flag_fn, 0, WHITENULL_llll);
		}
	}
	
	va_end(argptr);
	
	char res = display_popup_menu(r_ob, view, structure_ll, pointers_to_functions_ll, textcolors_ll, checked_ll, disabled_ll, icons_ll, 0);
	
	llll_free(structure_ll);
	llll_free(functions_model_ll);
	llll_free(disabled_ll);
	llll_free(checked_ll);
	llll_free(icons_ll);
	llll_free(textcolors_ll);
	llll_free(pointers_to_functions_ll);
	
	return res;
	
}


void free_popup_menus(t_dadaobj *x)
{
	long i;
	x->m_popup_menu.num_popup_menus = 0;
	llll_free(x->m_popup_menu.pointers_to_func);
	llll_free(x->m_popup_menu.labels);
	llll_free(x->m_popup_menu.addresses);
	for (i = 0; i < DADA_MAX_NUM_POPUP_SUBMENUS; i++) {
		if (x->m_popup_menu.popup_menus[i]) 
			jpopupmenu_destroy(x->m_popup_menu.popup_menus[i]);
	}
}

void idle_popup_fn(void *obj, t_symbol *label, const t_llll *address)
{
	return;
}

char popup_menu_is_shown(t_dadaobj *x)
{
	return x->m_popup_menu.popup_is_shown;
}



