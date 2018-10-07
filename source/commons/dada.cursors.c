/**
	@file
	dada.cursors.c
	Cursor utilities for dada library

	by Daniele Ghisi
*/

#include "dada.cursors.h"
#include "dada.cursors.data.c"



void load_cursors(t_dadaobj *x)
{
	t_cursor_manager *manager = &x->m_cursors;
	if (!manager->resources.s_cursor_rotate)
		manager->resources.s_cursor_rotate = jgraphics_image_surface_create_from_filedata(cursor_rotate_png, sizeof(cursor_rotate_png));
	if (!manager->resources.s_cursor_changecolor)
		manager->resources.s_cursor_changecolor = jgraphics_image_surface_create_from_filedata(cursor_changecolor_png, sizeof(cursor_changecolor_png));
	if (!manager->resources.s_cursor_scale)
		manager->resources.s_cursor_scale = jgraphics_image_surface_create_from_filedata(cursor_scale_png, sizeof(cursor_scale_png));
	if (!manager->resources.s_cursor_delete) 
		manager->resources.s_cursor_delete = jgraphics_image_surface_create_from_filedata(cursor_delete_png, sizeof(cursor_delete_png));
	if (!manager->resources.s_cursor_addpoint)
		manager->resources.s_cursor_addpoint = jgraphics_image_surface_create_from_filedata(cursor_addpoint_png, sizeof(cursor_addpoint_png));
	if (!manager->resources.s_cursor_deletepoint)
		manager->resources.s_cursor_deletepoint = jgraphics_image_surface_create_from_filedata(cursor_deletepoint_png, sizeof(cursor_deletepoint_png));
	if (!manager->resources.s_cursor_duplicatepoint)
		manager->resources.s_cursor_duplicatepoint = jgraphics_image_surface_create_from_filedata(cursor_duplicatepoint_png, sizeof(cursor_duplicatepoint_png));
	if (!manager->resources.s_cursor_changepitch)
		manager->resources.s_cursor_changepitch = jgraphics_image_surface_create_from_filedata(cursor_changepitch_png, sizeof(cursor_changepitch_png));
	if (!manager->resources.s_cursor_changevelocity)
		manager->resources.s_cursor_changevelocity = jgraphics_image_surface_create_from_filedata(cursor_changevelocity_png, sizeof(cursor_changevelocity_png));
	if (!manager->resources.s_cursor_pencil)
		manager->resources.s_cursor_pencil = jgraphics_image_surface_create_from_filedata(cursor_pencil_png, sizeof(cursor_pencil_png));
	if (!manager->resources.s_cursor_eraser)
		manager->resources.s_cursor_eraser = jgraphics_image_surface_create_from_filedata(cursor_eraser_png, sizeof(cursor_eraser_png));
	if (!manager->resources.s_cursor_glue)
		manager->resources.s_cursor_glue = jgraphics_image_surface_create_from_filedata(cursor_glue_png, sizeof(cursor_glue_png));
}


void free_cursors(t_dadaobj *x)
{
	t_cursor_manager *manager = &x->m_cursors;
	if (manager->resources.s_cursor_rotate)
		jgraphics_surface_destroy(manager->resources.s_cursor_rotate);
	if (manager->resources.s_cursor_changecolor)
		jgraphics_surface_destroy(manager->resources.s_cursor_changecolor);
	if (manager->resources.s_cursor_scale)
		jgraphics_surface_destroy(manager->resources.s_cursor_scale);
	if (manager->resources.s_cursor_delete) 
		jgraphics_surface_destroy(manager->resources.s_cursor_delete);
	if (manager->resources.s_cursor_addpoint)
		jgraphics_surface_destroy(manager->resources.s_cursor_addpoint);
	if (manager->resources.s_cursor_deletepoint)
		jgraphics_surface_destroy(manager->resources.s_cursor_deletepoint);
	if (manager->resources.s_cursor_duplicatepoint)
		jgraphics_surface_destroy(manager->resources.s_cursor_duplicatepoint);
	if (manager->resources.s_cursor_changepitch)
		jgraphics_surface_destroy(manager->resources.s_cursor_changepitch);
	if (manager->resources.s_cursor_changevelocity)
		jgraphics_surface_destroy(manager->resources.s_cursor_changevelocity);
	if (manager->resources.s_cursor_eraser)
		jgraphics_surface_destroy(manager->resources.s_cursor_eraser);
	if (manager->resources.s_cursor_pencil)
		jgraphics_surface_destroy(manager->resources.s_cursor_pencil);
	if (manager->resources.s_cursor_glue)
		jgraphics_surface_destroy(manager->resources.s_cursor_glue);
}

void dada_set_cursor(t_dadaobj *r_ob, t_object *patcherview, e_bach_mouse_cursors cursor)
{
    if (r_ob->m_cursors.curr_cursor != cursor)
        bach_set_cursor((t_object *)r_ob->orig_obj, &r_ob->m_cursors.curr_cursor, patcherview, cursor);
	
/*	return;
	
	if (r_ob->m_cursors.curr_cursor != cursor) {
		r_ob->m_cursors.curr_cursor = cursor;
		switch (cursor) {
			case BACH_CURSOR_SCALE:
				if (r_ob->m_cursors.resources.s_cursor_scale)
					jmouse_setcursor_surface(patcherview, (t_object*) r_ob, r_ob->m_cursors.resources.s_cursor_scale, 16, 16); 
				break;
				
			case BACH_CURSOR_CHANGE_COLOR:
				if (r_ob->m_cursors.resources.s_cursor_changecolor)
					jmouse_setcursor_surface(patcherview, (t_object*) r_ob, r_ob->m_cursors.resources.s_cursor_changecolor, 3, 3); 
				break;
				
			case BACH_CURSOR_NOTE_UPDOWN:
				if (r_ob->m_cursors.resources.s_cursor_changepitch)
					jmouse_setcursor_surface(patcherview, (t_object*) r_ob, r_ob->m_cursors.resources.s_cursor_changepitch, 11, 11); 
				break;
				
			case BACH_CURSOR_CHANGE_VELOCITY:
				if (r_ob->m_cursors.resources.s_cursor_changevelocity)
					jmouse_setcursor_surface(patcherview, (t_object*) r_ob, r_ob->m_cursors.resources.s_cursor_changevelocity, 11, 11); 
				break;
				
			case BACH_CURSOR_ROTATION:
				if (r_ob->m_cursors.resources.s_cursor_rotate)
					jmouse_setcursor_surface(patcherview, (t_object*) r_ob, r_ob->m_cursors.resources.s_cursor_rotate, 16, 16); 
				break;
				
			case BACH_CURSOR_DELETE:
				if (r_ob->m_cursors.resources.s_cursor_delete)
					jmouse_setcursor_surface(patcherview, (t_object*) r_ob, r_ob->m_cursors.resources.s_cursor_delete, 11, 11); 
				break;

			case BACH_CURSOR_DELETE_POINT:
				if (r_ob->m_cursors.resources.s_cursor_deletepoint)
					jmouse_setcursor_surface(patcherview, (t_object*) r_ob, r_ob->m_cursors.resources.s_cursor_deletepoint, 3, 3); 
				break;

			case BACH_CURSOR_DUPLICATE_POINT:
				if (r_ob->m_cursors.resources.s_cursor_duplicatepoint)
					jmouse_setcursor_surface(patcherview, (t_object*) r_ob, r_ob->m_cursors.resources.s_cursor_duplicatepoint, 3, 3); 
				break;

			case BACH_CURSOR_PENCIL:
				if (r_ob->m_cursors.resources.s_cursor_pencil)
					jmouse_setcursor_surface(patcherview, (t_object*) r_ob, r_ob->m_cursors.resources.s_cursor_pencil, 3, 3); 
				break;
			
			case BACH_CURSOR_ERASER:
				if (r_ob->m_cursors.resources.s_cursor_eraser)
					jmouse_setcursor_surface(patcherview, (t_object*) r_ob, r_ob->m_cursors.resources.s_cursor_eraser, 3, 3); 
				break;

			case BACH_CURSOR_GLUE:
				if (r_ob->m_cursors.resources.s_cursor_glue)
					jmouse_setcursor_surface(patcherview, (t_object*) r_ob, r_ob->m_cursors.resources.s_cursor_glue, 3, 3); 
				break;
				
			case BACH_CURSOR_RESIZE_BOTTOMRIGHTCORNER:
				jmouse_setcursor(patcherview, (t_object*) r_ob, JMOUSE_CURSOR_RESIZE_BOTTOMRIGHTCORNER);
				break;
				
			case BACH_CURSOR_RESIZE_BOTTOMLEFTCORNER:
				jmouse_setcursor(patcherview, (t_object*) r_ob, JMOUSE_CURSOR_RESIZE_BOTTOMLEFTCORNER);
				break;

			case BACH_CURSOR_RESIZE_FOURWAY:
				jmouse_setcursor(patcherview, (t_object*) r_ob, JMOUSE_CURSOR_RESIZE_FOURWAY);
				break;

			case BACH_CURSOR_RESIZE_LEFTRIGHT:
				jmouse_setcursor(patcherview, (t_object*) r_ob, JMOUSE_CURSOR_RESIZE_LEFTRIGHT);
				break;

			case BACH_CURSOR_RESIZE_UPDOWN:
				jmouse_setcursor(patcherview, (t_object*) r_ob, JMOUSE_CURSOR_RESIZE_UPDOWN);
				break;
				
			case BACH_CURSOR_RESIZE_TOPLEFTCORNER:
				jmouse_setcursor(patcherview, (t_object*) r_ob, JMOUSE_CURSOR_RESIZE_TOPLEFTCORNER);
				break;

			case BACH_CURSOR_RESIZE_TOPRIGHTCORNER:
				jmouse_setcursor(patcherview, (t_object*) r_ob, JMOUSE_CURSOR_RESIZE_TOPRIGHTCORNER);
				break;

			case BACH_CURSOR_MOVE:
				jmouse_setcursor(patcherview, (t_object*) r_ob, JMOUSE_CURSOR_RESIZE_FOURWAY);
				break;

			case BACH_CURSOR_DUPLICATE:
				jmouse_setcursor(patcherview, (t_object*) r_ob, JMOUSE_CURSOR_COPYING);
				break;

			case BACH_CURSOR_DRAGGINGHAND:
				jmouse_setcursor(patcherview, (t_object*) r_ob, JMOUSE_CURSOR_DRAGGINGHAND);
				break;
				
			case BACH_CURSOR_NONE:
				jmouse_setcursor(patcherview, (t_object*) r_ob, JMOUSE_CURSOR_NONE);
				break;

			case BACH_CURSOR_CROSSHAIR:
				jmouse_setcursor(patcherview, (t_object*) r_ob, JMOUSE_CURSOR_CROSSHAIR);
				break;
				
			default:
				jmouse_setcursor(patcherview, (t_object*) r_ob, JMOUSE_CURSOR_ARROW);
				break;
		}
	} */
}

