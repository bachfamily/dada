/**
	@file
	dada.db.h
	Database utilities header for dada library
 
	by Daniele Ghisi
 */

#ifndef _DADA_DB_H_
#define _DADA_DB_H_


#include "dada.items.h"
#include "ext_database.h"

#define DADA_XBASE_MAX_TABLES 256
#define DADA_XBASE_MAX_COLUMNS 1024
#define DADA_XBASE_MAGIC_GOOD 12481632
#define DADA_XBASE_MAGIC_BAD 666


#define DADA_QUERY_ALLOC_CHAR_SIZE (8192 * 4)


typedef struct _db_table {
    t_symbol *name;
    long num_columns;
    t_symbol	*column_name[DADA_XBASE_MAX_COLUMNS];
    char		column_type[DADA_XBASE_MAX_COLUMNS];		// i = int, f = float, l = llll, s = symbol
    t_llll		*lllls; /// lllls inside the table
} t_db_table;


// This is the actual database wrapper, which will be shared by t_base objects having the same name.
// Most of the API functions will involve thie t_xbase, and NOT the actual t_base object.
// A reference counting is set in place in order to only free the t_xbase objects when no other object
// uses them
typedef struct _xbase {
    t_object    r_ob;
    
    long        magic;
    t_database	*d_db;
    t_symbol    *d_name;
    long		num_tables;
    t_db_table	*table;
    long        ref_count;
    
    t_symbol    *d_filename;
    
    char        d_dirty;
    char        d_nodirty; // if toggled, won't set d_dirty flag
} t_xbase;




long db_result_numfields_local(t_db_result *result);
char* db_result_fieldname_local(t_db_result *result, long fieldindex);
long db_result_long_local(t_db_result *result, long recordindex, long fieldindex);
float db_result_double_local(t_db_result *result, long recordindex, long fieldindex);
t_symbol *db_result_symbol_local(t_db_result *result, long recordindex, long fieldindex);
t_symbol *table_name_to_idname(t_symbol *tablename);
char** db_result_firstrecord(t_db_result *result);

long tablename_to_tableidx(t_xbase *b, t_symbol *s);
long colname_to_colidx(t_xbase *b, long tableidx, t_symbol *s);
long colname_to_coltype(t_xbase *b, t_symbol *tablename, t_symbol *colname);

#endif // _DADA_DB_H_

