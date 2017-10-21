/**
	@file
	dada.popupmenu.h
	Popup menu functions header for dada library
 
	by Daniele Ghisi
 */


#ifndef _DADA_POPUPMENU_H_
#define _DADA_POPUPMENU_H_

#include "dada.commons.h"

typedef struct _stack_popup_menu_helper
{
	t_symbol	*llll_name;
	int			father_count;
	char		disabled;
} t_stack_popup_menu_helper;


typedef void (*dada_popup_fn)(void *obj, t_symbol *label, const t_llll *address);

void initialize_popup_menus(t_dadaobj *x);
char build_popup_menu(t_dadaobj *x, t_llll *structure, t_llll *pointers_to_functions, 
					 t_llll *textcolors, t_llll *checked, t_llll *disabled, t_llll *icons);
void popup_menu_popup(t_dadaobj *x, t_object *view, long initial_item_ID);
char display_popup_menu(t_dadaobj *x, t_object *view, t_llll *structure, t_llll *pointers_to_functions, 
					 t_llll *textcolors, t_llll *checked, t_llll *disabled, t_llll *icons, long initial_item_ID);

// EASIEST WAY TO DISPLAY A POPUP MENU:
// For a dadaitem...
char ezdisplay_popup_menu_for_dadaitem(t_dadaobj *r_ob, t_object *view, t_dadaitem *item, long autodisplay_flags, const char *structure, const char *functions_llll_model,
									   const char *checked, const char *disabled, const char *icons, const char *textcolors, ...);
// ... or for anything else
#define ezdisplay_popup_menu(x, view, structure, functions_llll_model, checked, disabled, icons, textcolors, ...) \
	ezdisplay_popup_menu_for_dadaitem(x, view, NULL, 0, structure, functions_llll_model, checked, disabled, icons, textcolors, __VA_ARGS__)


void free_popup_menus(t_dadaobj *x);
char popup_menu_is_shown(t_dadaobj *x);
void idle_popup_fn(void *obj, t_symbol *label, const t_llll *address);


#endif // _DADA_POPUPMENU_H_
