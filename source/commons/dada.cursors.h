/**
	@file
	dada.cursors.h
	Cursor utilities header for dada library
 
	by Daniele Ghisi
 */

#ifndef _DADA_CURSORS_H_
#define _DADA_CURSORS_H_


#include "dada.items.h"


/*
 typedef enum _dada_mouse_cursors {
	BACH_CURSOR_DEFAULT = 0,														///< Default
	BACH_CURSOR_COPY					= BACH_CURSOR_COPY,							///< Copy cursor (arrow and plus)
	BACH_CURSOR_CROSSHAIR				= BACH_CURSOR_CROSSHAIR,						///< Selection "+" (crosshair)
	BACH_CURSOR_POINTINGHAND			= BACH_CURSOR_POINTINGHAND,					///< Pointing hand
	BACH_CURSOR_DRAGGINGHAND,					///< Open hand (for dragging)
	BACH_CURSOR_ROTATION,						///< Rotation cursor
	BACH_CURSOR_RESIZE_UPDOWN,					///< Up-down arrows
	BACH_CURSOR_RESIZE_LEFTRIGHT,				///< Left-right arrows
	BACH_CURSOR_RESIZE_FOURWAY,					///< Up-down-left-right arrows
	BACH_CURSOR_RESIZE_TOPLEFTCORNER,			///< Top-left corner arrows
	BACH_CURSOR_RESIZE_TOPRIGHTCORNER,			///< Top-right corner arrows
	BACH_CURSOR_RESIZE_BOTTOMLEFTCORNER,		///< Bottom-left corner arrows
	BACH_CURSOR_RESIZE_BOTTOMRIGHTCORNER,		///< Bottom-right corner arrows
	BACH_CURSOR_CHANGE_COLOR,					///< Color changer cursor
	BACH_CURSOR_NOTE_UPDOWN,					///< Pitch changer cursor
	BACH_CURSOR_CHANGE_VELOCITY,				///< Velocity changer cursor
	BACH_CURSOR_MOVE,							///< Move element cursor
	BACH_CURSOR_SCALE,							///< Scale element cursor
	BACH_CURSOR_DELETE,							///< Delete element cursor
	BACH_CURSOR_DUPLICATE,						///< Duplicate element cursor
	BACH_CURSOR_DELETE_POINT,					///< Delete point cursor
	BACH_CURSOR_ADD_POINT,						///< Add point cursor
	BACH_CURSOR_DUPLICATE_POINT,				///< Duplicate point cursor
	BACH_CURSOR_PENCIL,							///< Pencil cursor
	BACH_CURSOR_ERASER,							///< Eraser cursor
	BACH_CURSOR_GLUE,							///< Glue cursor
	BACH_CURSOR_CURVE,							///< Curve cursor
	BACH_CURSOR_NONE							///< No cursor
} e_dada_mouse_cursors;
*/

void load_cursors(t_dadaobj *x);
void free_cursors(t_dadaobj *x);
void dada_set_cursor(t_dadaobj *r_ob, t_object *patcherview, e_bach_mouse_cursors cursor);

#endif // _DADA_CURSORS_H_

