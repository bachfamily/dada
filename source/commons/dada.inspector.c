/**
	@file
	dada.inspector.c
	Inspector utilities for dada library

	by Daniele Ghisi
*/

#include "dada.inspector.h"

void dada_inspector_open(t_dadaobj *r_ob)
{
	if (r_ob->m_interface.selection->l_size == 1) {
		t_dadaitem *it = (t_dadaitem *)hatom_getobj(&r_ob->m_interface.selection->l_head->l_hatom);
		long di_class_id = dadaitem_class_get_id(&r_ob->m_classes, it->type);
		open_bach_inspector(NULL, &r_ob->m_inspector, it, di_class_id);
    } else if (r_ob->m_interface.selection->l_size > 1) {
        open_bach_inspector(NULL, &r_ob->m_inspector, NULL, k_MIXED);
    } else if (r_ob->m_interface.last_mousedown_item) {
        long di_class_id = dadaitem_class_get_id(&r_ob->m_classes, r_ob->m_interface.last_mousedown_item->type);
        open_bach_inspector(NULL, &r_ob->m_inspector, r_ob->m_interface.last_mousedown_item, di_class_id);
    }
}


t_jsurface *dada_inspector_get_icon_surface_fn(t_object *r_ob, t_bach_inspector_manager *man, void *obj, long elem_type)
{
    return NULL;
}

void dada_default_inspector_header_fn(t_object *r_ob, t_bach_inspector_manager *man, void *elem, long class_id, char *txt)
{
    if (class_id < 0) {
        snprintf_zero(txt, CONST_BACH_INSPECTOR_MAX_HEADER_NUM_CHARS, "No Element");
    } else if (class_id == k_MIXED) {
        snprintf_zero(txt, CONST_BACH_INSPECTOR_MAX_HEADER_NUM_CHARS, "Multiple Elements");
    } else {
        t_dadaobj *d_ob = (t_dadaobj *)man->thing;
        t_dadaitem *item = (t_dadaitem *)elem;
        long idx = elem ? dadaitem_get_index(d_ob, (t_dadaitem *)elem) + 1 : 0;
        if (item && item->name)
            snprintf_zero(txt, CONST_BACH_INSPECTOR_MAX_HEADER_NUM_CHARS, "%s %d (%s)", d_ob->m_classes.di_class[class_id].label->s_name, idx, item->name->s_name);
        else
            snprintf_zero(txt, CONST_BACH_INSPECTOR_MAX_HEADER_NUM_CHARS, "%s %d", d_ob->m_classes.di_class[class_id].label->s_name, idx);
    }
}


/*

void switch_dada_inspector(t_dadaobj *r_ob, t_dadaitem *it)
{
	if (r_ob->m_inspector.inspector_ui && r_ob->m_inspector.inspector_ui->edited_attribute)
		bach_inspector_enter(r_ob);
	
	r_ob->active_inspector_enumindex = NULL;
	r_ob->active_inspector_enumindex_mouseover_idx = -1;
	r_ob->active_inspector_color = NULL;
	open_bach_inspector(r_ob, obj, obj_type);
	
	resync_selection_with_bach_inspector(r_ob);
}

*/



void dada_inspector_resync_with_selection(t_dadaobj *r_ob)
{
    if (r_ob->m_inspector.inspector_patcher && r_ob->m_inspector.inspector_ui){
        if (r_ob->m_interface.selection->l_size == 1) {
            t_dadaitem *it = (t_dadaitem *)hatom_getobj(&r_ob->m_interface.selection->l_head->l_hatom);
            long di_class_id = dadaitem_class_get_id(&r_ob->m_classes, it->type);
            open_bach_inspector(NULL, &r_ob->m_inspector, it, di_class_id);
        } else if (r_ob->m_interface.selection->l_size > 1){
            open_bach_inspector(NULL, &r_ob->m_inspector, NULL, k_MIXED);
        } else if (r_ob->m_interface.last_mousedown_item){
            long di_class_id = dadaitem_class_get_id(&r_ob->m_classes, r_ob->m_interface.last_mousedown_item->type);
            open_bach_inspector(NULL, &r_ob->m_inspector, r_ob->m_interface.last_mousedown_item, di_class_id);
        } else {
            open_bach_inspector(NULL, &r_ob->m_inspector, NULL, -1);
        }
    }
}
