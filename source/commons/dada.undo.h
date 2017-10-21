/**
	@file
	dada.undo.h
	Undo-redo mechanism header for dada library
 
	by Daniele Ghisi
 */


#ifndef _DADA_UNDO_H_
#define _DADA_UNDO_H_

#include "dada.commons.h"

#define DADA_SIG_oL void (*)(void *object, t_llll *ll)

/** Undo or redo operations. @ingroup undo
 */
typedef enum _dada_undo_redo
{
	DADA_UNDO = -1,		///< Undo operation
	DADA_REDO = 1		///< Redo operation
} e_dada_undo_redo;


/** Undo or redo operations. @ingroup undo
 */
typedef enum _dada_undo_operation_type
{
	DADA_UNDO_OP_MODIFICATION = 0,		
	DADA_UNDO_OP_CREATION = 1,			
	DADA_UNDO_OP_DELETION = 2			
} e_dada_undo_operation_type;



typedef struct _undo_tick
{
	e_dada_func_types		u_set_type;
	method					u_set_function;
	t_llll					*u_set_args;

	e_dada_func_types		u_get_type;
	method					u_get_function;
	t_llll					*u_get_args;
	
	e_dada_undo_operation_type	op_type;
    
    // only used for creation/deletion
    e_dadaitem_types            dadaitem_type;
    long                        dadaitem_ID;
} t_dada_undo_tick;





t_symbol *combine_string_with_symbol_for_undo(const char *str, t_symbol *sym, char make_sym_plural);
void call_function(t_dadaobj *r_ob, e_dada_func_types type, method func, t_llll *args, t_hatom *return_value);

t_dada_undo_tick *undo_redo_tick_new(t_dadaobj *r_ob, e_dada_func_types set_type, method set_func, t_llll *set_args, 
									 e_dada_func_types get_type, method get_func, t_llll *get_args, e_dada_undo_operation_type op_type,
                                     e_dadaitem_types type, long dadaitem_ID);
t_dada_undo_tick *undo_redo_tick_reverse(t_dadaobj *r_ob, t_dada_undo_tick *orig_tick);
void undo_redo_tick_free(t_dada_undo_tick *tick);
void undo_redo_free_all_ticks(t_undo_manager *man, e_dada_undo_redo what);
void undo_redo_clear(t_undo_manager *man, e_dada_undo_redo what);
void undo_redo_tick_push(t_undo_manager *man, e_dada_undo_redo what, t_dada_undo_tick *tick);
void undo_redo_marker_push(t_undo_manager *man, e_dada_undo_redo what, t_symbol *operation);
void undo_redo_tick_and_marker_push(t_undo_manager *man, e_dada_undo_redo what, t_dada_undo_tick *tick, t_symbol *operation);
void undo_tick_and_marker_push(t_undo_manager *man, t_dada_undo_tick *tick, t_symbol *operation);
void redo_tick_and_marker_push(t_undo_manager *man, t_dada_undo_tick *tick, t_symbol *operation);
void undo_check_max_num_steps(t_undo_manager *man);
char undo_are_there_free_undo_ticks(t_undo_manager *man);


// THIS IS THE FUNCTION TO BE USED, WHICH ALSO CHECKS THAT THE NUMBER OF UNDO STEPS BE < OF THE MAX ONE
void undo_add_interface_step(t_dadaobj *r_ob, e_dada_func_types set_type, method set_func, t_llll *set_args, 
							 e_dada_func_types get_type, method get_func, t_llll *get_args, e_dada_undo_operation_type op_type, t_symbol *operation,
                             e_dadaitem_types dadaitem_type = DADAITEM_TYPE_NONE, long dadaitem_ID = 0, char add_undo_marker = true);
void undo_add_interface_step_for_whole_dadaobj(t_dadaobj *r_ob, t_symbol *operation);
void undo_add_interface_step_for_dadaitem_class(t_dadaobj *r_ob, e_dadaitem_types type, t_symbol *operation);
void undo_add_interface_step_for_dadaitem(t_dadaobj *r_ob, t_dadaitem *item, e_dada_undo_operation_type op_type, t_symbol *operation, char add_undo_marker = true);
void undo_redo_perform(t_dadaobj *r_ob, e_dada_undo_redo what);
void undo_redo_post_debug(t_dadaobj *r_ob);



void dadaobj_add_undo_marker_if_needed(t_dadaobj *r_ob);



#endif // _DADA_UNDO_H_
