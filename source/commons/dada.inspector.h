/**
	@file
	dada.inspector.h
	Inspector utilities header for dada library
 
	by Daniele Ghisi
 */


#ifndef _DADA_INSPECTOR_H_
#define _DADA_INSPECTOR_H_

#include "dada.commons.h"

#endif // _DADA_INSPECTOR_H_

void dada_inspector_open(t_dadaobj *r_ob);
t_jsurface *dada_inspector_get_icon_surface_fn(t_object *r_ob, t_bach_inspector_manager *man, void *obj, long elem_type);
void dada_default_inspector_header_fn(t_object *r_ob, t_bach_inspector_manager *man, void *elem, long class_id, char *txt);
void dada_inspector_resync_with_selection(t_dadaobj *r_ob);
