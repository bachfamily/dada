/**
	@file
	dada.db.c
	Database utilities for dada library

	by Daniele Ghisi
*/

#include "dada.db.h"
#include "dada.commons.h"

///// LOCAL FUNCTION OVERRIDING OR MISSING IN CYCLING API
 
long db_result_numfields_local(t_db_result *result)
{
	if (result)
		return (long)object_method(result, _sym_numfields);
	else
		return 0;
}


char* db_result_fieldname_local(t_db_result *result, long fieldindex)
{
	return (char *)object_method(result, _sym_fieldnamebyindex, fieldindex);
}


long db_result_long_local(t_db_result *result, long recordindex, long fieldindex)
{
	char*	c = (char *)object_method(result, _sym_valuebyindex, recordindex, fieldindex);
	long	l = 0;
	
	if (c)
		sscanf(c, "%ld", &l);
	return l;
}

float db_result_double_local(t_db_result *result, long recordindex, long fieldindex)
{
	char*	c = (char *)object_method(result, _sym_valuebyindex, recordindex, fieldindex);
	double	f = 0;
	
	if (c)
		sscanf(c, "%lf", &f);
	return f;
}

t_symbol *db_result_symbol_local(t_db_result *result, long recordindex, long fieldindex)
{
    char *c = db_result_string(result, recordindex, fieldindex);
    return c ? gensym(c) : NULL;
}


char** db_result_firstrecord(t_db_result *result)
{
    db_result_reset(result);
    return db_result_nextrecord(result);
/*    if (result)
        return (char **)object_method(result, _sym_recordbyindex, 0);
    else
        return NULL; */
}


t_symbol *table_name_to_idname(t_symbol *tablename)
{
	char idname[256];
	strncpy_zero(idname, tablename->s_name, 252);
	
	// singularize
	if (idname[strlen(idname)-1] == 's')
		idname[strlen(idname)-1] = 0;
	
	strncpy_zero(idname + strlen(idname), "_id", 4);

	return gensym(idname);
}






long tablename_to_tableidx(t_xbase *b, t_symbol *s)
{
    long i;
    for (i = 0; i < b->num_tables; i++)
        if (b->table[i].name == s)
            return i;
    return -1;
}


long colname_to_colidx(t_xbase *b, long tableidx, t_symbol *s)
{
    long i;
    for (i = 0; i < b->table[tableidx].num_columns; i++)
        if (b->table[tableidx].column_name[i] == s)
            return i;
    return -1;
}


long colname_to_coltype(t_xbase *b, t_symbol *tablename, t_symbol *colname)
{
    long table_idx = tablename_to_tableidx(b, tablename);
    if (table_idx >= 0 && table_idx < b->num_tables) {
        long col_idx = colname_to_colidx(b, table_idx, colname);
        if (col_idx >= 0 && col_idx < b->table[table_idx].num_columns) {
            return b->table[table_idx].column_type[col_idx];
        }
    }
    
    return 'i'; // useful for _ids columns
}








char filename_is_not_sql_file(t_symbol *s)
{
    if (s && strlen(s->s_name) > 0 && strcmp(s->s_name + strlen(s->s_name) - 4, ".db3") != 0)
        return 1;
    return 0;
}


char xbase_is_attached_to_text_file(t_xbase *b)
{
    if (filename_is_not_sql_file(b->d_filename))
        return 1;
    return 0;
}

char xbase_is_attached_to_sql_file(t_xbase *b)
{
    if (b->d_filename && strlen(b->d_filename->s_name) > 0 && strcmp(b->d_filename->s_name + strlen(b->d_filename->s_name) - 4, ".db3") == 0)
        return 1;
    return 0;
}



char xbase_store_lllls_with_phonenumbers(t_xbase *b)
{
    if (xbase_is_attached_to_sql_file(b) || b->d_force_store_lllls_as_text)
        return 0;
    return 1;
}
