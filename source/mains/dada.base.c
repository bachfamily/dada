/**
	@file
	dada.base.c
	
	@name 
	dada.base
	
	@realname 
	dada.base

	@type
	object
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
	SQLite database
	
	@description
	Implements a database supporting lllls (and hence scores), as well as standard Max data types.
	
	@discussion
	
	@category
	dada, dada storage, dada corpus-based tools

	@keywords
	database, llll, storage 
	
	@seealso
	bach.shelf, dada.segment, dada.cartesian, dada.distances
	
	@owner
	Daniele Ghisi
*/

#include "dada.commons.h"
#include "ext.h"
#include "ext_obex.h"
#include "ext_database.h"
#include "ext_drag.h"
#include "dada.db.h"
#ifdef WIN_VERSION
#include "io.h"
#define strtok_r strtok_s
#endif
#include <string.h>

// Data Structures
typedef struct _base {
	t_llllobj_object d_obj;
	t_symbol	*d_name;
	t_symbol	*d_filename;
	t_fourcc	d_filetype;
	
	char		output_fieldnames;
    char        escape_single_quotes;
    char        convert_null_to_default;

    t_symbol    *utility_sym;
    t_llll      *utility_ll;
	
    t_xbase     *xbase;
    
    t_object *m_editor;
    
    char        editor_dirty;
    char        is_volatile;
    char        is_readonly; ///< This is unsupported for now, due to the fact that db_open_ext() does not seem to be exposed properly from Max API
    char        creating_new_obj;
} t_base;


// Prototypes
t_base*			base_new(t_symbol *s, short argc, t_atom *argv);
void			base_free(t_base *x);
void			base_bang(t_base *x);
void			base_dump(t_base *x);
void            base_getcols(t_base *x);
void			base_assist(t_base *x, void *b, long m, long a, char *s);
long            base_acceptsdrag(t_base *x, t_object *drag, t_object *view);
void			base_query(t_base *x, t_symbol *msg, long ac, t_atom *av);
void			base_anything(t_base *x, t_symbol *msg, long ac, t_atom *av);
void			base_entry_create(t_base *x, t_symbol *msg, long ac, t_atom *av);
void            base_entries_create_from_file(t_base *x, t_symbol *msg, long ac, t_atom *av);
void            base_entries_create_from_csv(t_base *x, t_symbol *msg, long ac, t_atom *av);
void			base_entry_destroy(t_base *x, t_symbol *tablename, long event_id);
void			base_table_create(t_base *x, t_symbol *msg, long ac, t_atom *av);
void			base_table_create_do(t_base *x, t_symbol *tablename, t_llll *specs);
void			base_table_destroy(t_base *x, t_symbol *tablename);
t_max_err		base_attr_name_set(t_base *x, void *attr, long argc, t_atom *argv);
void			base_appendtodictionary(t_base *x, t_dictionary *d);
void            base_dblclick(t_base *x);
void            base_wopen(t_base *x);
void            base_edclose(t_base *x, char **ht, long size);
void            base_okclose(t_base *x, char *s, short *result);
//long    base_edsave(t_base *x, char **ht, long size);

void            base_distanceentry_create(t_base *x, t_symbol *msg, long ac, t_atom *av);
void            base_distancetable_create(t_base *x, t_symbol *msg, long ac, t_atom *av);
void            base_distanceentries_bulk_create_from_ids(t_base *x, t_symbol *msg, long ac, t_atom *av);

t_llll          *db_to_llll(t_xbase *b, char output_fieldnames);
t_max_err       llll_to_db(t_xbase *b, t_llll *ll, char escape_single_quotes, char convert_null_to_default);


void base_read(t_base *x, t_symbol *s);
void base_write(t_base *x, t_symbol *s, long argc, t_atom *argv);
void base_writetxt(t_base *x, t_symbol *s, long argc, t_atom *argv);

const char *xbase_column_type_to_sqltype(t_xbase *b, char type);

void llll_read_sym2objs(t_object *x, t_symbol *s, read_fn outfn);


//////////// xbase interface
t_xbase *xbase_new(t_symbol *name);
void xbase_free(t_xbase *b);
void xbase_error(t_xbase *b, const char *text);
void xbase_entry_destroy(t_xbase *b, t_symbol *tablename, long event_id);
void xbase_table_destroy(t_xbase *b, t_symbol *tablename);
long tablename_to_tableidx(t_xbase *b, t_symbol *s);
long colname_to_colidx(t_xbase *b, long tableidx, t_symbol *s);
void xbase_destroy_all_tables(t_xbase *b);
void xbase_table_create_do(t_xbase *x, t_symbol *tablename, t_llll *specs, long num_skip_elems, char only_create_structures = false);
void xbase_free_lllls(t_xbase *b);

t_llll *xbase_db_query_from_llll(t_xbase *b, t_llll *query, char output_fieldnames);
t_llll *xbase_db_get_table_header(t_xbase *b, long table_idx);
long xbase_db_count_all_rows(t_xbase *b);
long xbase_db_count_table_rows(t_xbase *b, long table_num);



// Globals and Statics
static t_class	*s_base_class = NULL;
static t_class	*s_xbase_class = NULL;
static t_symbol	*ps_event = NULL;

/**********************************************************************/
// Class Definition and Life Cycle

void C74_EXPORT ext_main(void *moduleRef)
{
	common_symbols_init();
	llllobj_common_symbols_init();

	if (dada_check_bach_version() || llllobj_test()) {
        dada_error_bachcheck();
		return;
	}
	
	t_class *c; 
	
	CLASS_NEW_CHECK_SIZE(c, "dada.base",
				  (method)base_new,
				  (method)base_free,
				  (long)sizeof(t_base),
				  (method)NULL,
				  A_GIMME,
				  0L);
	
    
    
    // @method read @digest Load database from disk
    // @description The specified file is read from disk and the llll it contains is set as current database.
    // In order to have the correct syntax, the llll must be as the one written by <m>write</m> or <m>writetxt</m> messages.
    // @marg 0 @name file_name @optional 1 @type symbol
    class_addmethod(c, (method)base_read,                   "read",			A_DEFSYM,	0);
    
    
    // @method write @digest Save database in native format
    // @description A <m>write</m> message will save the database (as llll) in a file, in native format.
    // If an argument is given, this is the filename (if the file is in the search path
    // or in the same folder) or the full file path. If no argument is given, a dialog window pops up.
    // Syntax is expected to be in the format explained in the <m>dump</m> message documentation.
    // @marg 0 @name file @optional 1 @type symbol
    class_addmethod(c, (method)base_write,			"write",		A_GIMME, 0);
    
    // @method writetxt @digest Save database in text format
    // @description A <m>writetxt</m> message will save the database (as llll) in a file, in text format.
    // If an argument is given, this is the filename (if the file is in the search path
    // or in the same folder) or the full file path. If no argument is given, a dialog window pops up.
    // Syntax is expected to be in the format explained in the <m>dump</m> message documentation.
    // @marg 0 @name file @optional 1 @type symbol
    class_addmethod(c, (method)base_writetxt,			"writetxt",		A_GIMME, 0);
    

    
	class_addmethod(c, (method)base_appendtodictionary, "appendtodictionary", A_CANT, 0);
	class_addmethod(c, (method)base_bang,			"bang", 0);
	class_addmethod(c, (method)base_assist,			"assist",		A_CANT, 0);
    
    
    // @method (doubleclick) @digest Edit database as text
    // @description Doubleclicking on the object opens a text editor, where the whole database can be edited directly in text form.
    // To prevent unwanted long hangs, this is only true for small datasets: if you need to open large datasets in text form,
    // please use the <m>wopen</m> message explicitly.
    class_addmethod(c, (method)base_dblclick,		"dblclick",		A_CANT, 0);
    class_addmethod(c, (method)base_edclose,		"edclose",		A_CANT, 0);
    class_addmethod(c, (method)base_okclose,        "okclose", A_CANT, 0);
//    class_addmethod(c, (method)base_edsave,         "edsave", A_CANT, 0);
    

    // @method wopen @digest Open text editor for database
    // @description The <m>wopen</m> message will open a text editor for the database.
    class_addmethod(c, (method)base_wopen,          "wopen",    0);

    // @method (drag) @digest Drag-and-drop database loading
    // @description The specified file is read from disk and the database it contains (as llll) is opened.
    class_addmethod(c, (method)base_acceptsdrag, "acceptsdrag_locked", A_CANT, 0);
    class_addmethod(c, (method)base_acceptsdrag, "acceptsdrag_unlocked", A_CANT, 0);
    
    
    // @method dump @digest Output entire database as llll
    // @description Outputs the entire database in llll form (also outputs the column names depending on the
    // <m>outputcolnames</m> attribute).
    // Syntax is: <b><m>TABLE1</m> <m>TABLE2</m>...</b>, where each table is <b>[<m>TABLE_HEADER</m> <m>TABLE_CONTENT</m>]</b>,
    // where <m>TABLE_HEADER</m> is
    // <b>[<m>table_name</m> [<m>column_name1</m> <m>column_type1</m>] [<m>column_name2</m> <m>column_type2</m>]...]</b>
    // and <m>TABLE_CONTENT</m> is
    // <b>[[<m>table_id_name</m> <m>id</m>] [<m>field1_name</m> <m>content1</m>] [<m>field2_name</m> <m>content2</m>]...]</b>
    // and the <m>table_id_name</m> name is the singularized version of the table name, with the "_id" suffix (e.g.
    // for a table named "waves" this will be "wave_id").
    class_addmethod(c, (method)base_dump,			"dump", 0);

    // @method getcols @digest Output column names and types as llll
    // @description Outputs the table header for each table in the database, i.e. the column names and types.
    // Syntax is: <b><m>TABLE1</m> <m>TABLE2</m>...</b>, where each table is
    // <b>[<m>table_name</m> [<m>column_name1</m> <m>column_type1</m>] [<m>column_name2</m> <m>column_type2</m>]...]</b>
    class_addmethod(c, (method)base_getcols,			"getcols", 0);

    
    // @method query @digest Send a query
    // @description Sends a query to the database. The query result will be output from the first outlet.
    // @marg 0 @name query @optional 0 @type anything
    class_addmethod(c, (method)base_query,				"query",			A_GIMME, 0);

    class_addmethod(c, (method)base_anything,			"anything",		A_GIMME, 0);
	class_addmethod(c, (method)base_anything,			"list",			A_GIMME, 0);
	
	// @method clear @digest Delete entries
	// @description A <m>clear</m> message will delete all entries from all tables. If a table name
	// is specified as a second argument, only the entries of such table are deleted.
	// @marg 0 @name table_name @optional 1 @type symbol
	class_addmethod(c, (method)base_anything,			"clear",			A_GIMME, 0);

	
	// @method erase @digest Erase database
	// @description An <m>erase</m> message will delete all tables and all entries in the database.
	class_addmethod(c, (method)base_anything,			"erase",			A_GIMME, 0);
	
	
	// @method addentry @digest Add an entry to a table
	// @description An <m>addentry</m> message followed by a table name and some entry specification 
	// will add an entry to the table (if existing). Entry specification be in the form <b>[<m>columnname1</m> <m>content1</m>] [<m>columnname2</m> <m>content2</m>]... </b>.
	// @marg 0 @name table_name @optional 0 @type symbol	
	// @marg 1 @name specs @optional 0 @type llll
    // @example addentry towns [name NewYork] [population 8406000] @caption add an entry in the table "towns".
	class_addmethod(c, (method)base_entry_create,		"addentry",		A_GIMME, 0);
	class_addmethod(c, (method)base_entry_destroy,		"deleteentry",		A_SYM, A_LONG, 0); // ????? Are we sure???
    
    
    // @method adddistanceentry @digest Add an entry to a distance table
    // @description An <m>adddistanceentry</m> adds an entry in a distance table. Syntax is
    // <m>adddistanceentry</m> <m><b>distance_table_name</b></m> <m><b>reference_table_name</b></m>
    // <m><b>reference_column_name</b></m> <m><b>column_value1</b></m> <m><b>column_value2</b></m>
    // <m><b>distance</b></m>.
    // @marg 0 @name distance_table_name @optional 0 @type symbol
    // @marg 1 @name reference_table_name @optional 0 @type symbol
    // @marg 2 @name reference_column_name @optional 0 @type symbol
    // @marg 3 @name column_value1 @optional 0 @type atom
    // @marg 4 @name column_value2 @optional 0 @type atom
    // @marg 5 @name distance @optional 0 @type number
    // @example addentry disttowns towns name NewYork Buffalo 601 @caption add in "disttowns" the information about the distance between NewYork and Buffalo (idenfitied by their name inside the table "towns".
    class_addmethod(c, (method)base_distanceentry_create,		"adddistanceentry",		A_GIMME, 0);

    
    // @method adddistanceentry @digest Add an entry to a distance table
    // @description An <m>adddistanceentry</m> adds an entry in a distance table. Syntax is
    // <m>adddistanceentry</m> <m><b>distance_table_name</b></m> <m><b>reference_table_name</b></m>
    // <m><b>reference_column_name</b></m> <m><b>column_value1</b></m> <m><b>column_value2</b></m>
    // <m><b>distance</b></m>.
    // @marg 0 @name distance_table_name @optional 0 @type symbol
    // @marg 1 @name reference_table_name @optional 0 @type symbol
    // @marg 2 @name reference_column_name @optional 0 @type symbol
    // @marg 3 @name column_value1 @optional 0 @type atom
    // @marg 4 @name column_value2 @optional 0 @type atom
    // @marg 5 @name distance @optional 0 @type number
    // @example addentry disttowns towns name NewYork Buffalo 601 @caption add in "disttowns" the information about the distance between NewYork and Buffalo (idenfitied by their name inside the table "towns".
    class_addmethod(c, (method)base_distanceentries_bulk_create_from_ids,		"adddistanceentriesfromids",		A_GIMME, 0);


    // @method appendfromfile @digest Appends entries to table from file
    // @description Appends the content of a given text file (second argument) to a table (first argument).
    // The file should contain a properly formatted <m>llll</m> in the form
    // <b><m>ENTRY1</m> <m>ENTRY2</m>...</b>, where each <b><m>ENTRY</m></b> is in the form
    // <b>[[<m>column_name</m> <m>value[s]</m>] [<m>column_name</m> <m>value[s]</m>]...]</b>. <br />
    // If a third specification of the kind <b>[cols <m>colname1</m> <m>colname2</m>...]</b> is set,
    // only the specified columns will be imported into the database. <br />
    // If you have a massive amount of symbol entries in your table, this should be the preferred method of loading
    // them into a <o>dada.base</o> object, since it bypasses the Max symbol table, inserting strings directly into the SQLite database.
    // @marg 0 @name table_name @optional 0 @type symbol
    // @marg 1 @name filename @optional 1 @type symbol
    // @marg 2 @name columns @optional 1 @type llll
    class_addmethod(c, (method)base_entries_create_from_file,		"appendfromfile",		A_GIMME, 0);

    
    
    class_addmethod(c, (method)base_entries_create_from_csv,        "appendfromcsv",        A_GIMME, 0);

    
	// @method addtable @digest Add a table to the database
	// @description An <m>addtable</m> message followed by a table name and some columns specifications 
	// will add a table to the database having the given number and types of columns. 
	// Column specification must be in the form <b>[<m>name1</m> <m>type1</m>] [<m>name2</m> <m>type2</m>]... </b>
	// where each <m>name</m> is a symbol and each type is one of the symbols: "f" (float), "i" (integer),
    // "s" (symbol), "r" (rational), "p" (pitch), "l" (llll).
	// @marg 0 @name table_name @optional 0 @type symbol	
	// @marg 1 @name columns @optional 0 @type llll
    // @example addtable towns [name s] [population i] @caption add a table named "towns" with two columns: name (symbol) and popuplation (integer)
	class_addmethod(c, (method)base_table_create,		"addtable",		A_GIMME, 0);

    
    // @method adddistancetable @digest Add a distance table to the database
    // @description An <m>adddistancetable</m> message followed by a table name and the name of a reference table
    // will add a table designed to contain distances between the entries of the reference table.
    // Distances should be then added via <m>adddistanceentry</m>.
    // @marg 0 @name table_name @optional 0 @type symbol
    // @marg 1 @name reference_table_name @optional 0 @type symbol
    // @example adddistancetable disttowns towns @caption add a distance table named "disttowns" designed to contain distances of elements from the table "towns".
    class_addmethod(c, (method)base_distancetable_create,		"adddistancetable",		A_GIMME, 0);

    
	// @method deletetable @digest Delete a specific table
	// @description A <m>deletetable</m> message followed by a table name will delete such table (if it exists) from the database.
	// @marg 0 @name table_name @optional 0 @type symbol
	class_addmethod(c, (method)base_table_destroy,		"deletetable",		A_SYM, 0);

		
    llllobj_class_add_out_attr(c, LLLL_OBJ_VANILLA);

    CLASS_ATTR_SYM(c,		"name",	0,	t_base, d_name);
    CLASS_ATTR_STYLE_LABEL(c,"name",0,"text","Database Name");
	CLASS_ATTR_ACCESSORS(c,	"name",	NULL,	base_attr_name_set);
	// @description Sets the name of the database

	CLASS_STICKY_ATTR(c,"category",0,"Settings");
	
    CLASS_ATTR_CHAR(c,"volatile",0, t_base, is_volatile);
    CLASS_ATTR_STYLE_LABEL(c,"volatile",0,"onoff","Volatile Dataset File");
    // @description Toggles the ability to not commit any changes for a file-attached database.
    // The database can be modified locally, but nothing will be saved to disk
    // (unless explicitly forced by a <m>write</m> or <m>writetxt</m> message.

//    CLASS_ATTR_CHAR(c,"readonly",0, t_base, is_readonly);
//    CLASS_ATTR_STYLE_LABEL(c,"readonly",0,"onoff","Read-Only Dataset File");
    // @exclude all //<<< UNSUPPORTED FOR NOW
    // @description Toggles the ability to make the database read-only.

    
    CLASS_ATTR_CHAR(c,"outputcolnames",0, t_base, output_fieldnames);
	CLASS_ATTR_STYLE_LABEL(c,"outputcolnames",0,"onoff","Output Column Names");
	// @description Toggles the ability to output the column names in query answers. Defaults to 1.

    CLASS_ATTR_CHAR(c,"escapesinglequotes",0, t_base, escape_single_quotes);
    CLASS_ATTR_STYLE_LABEL(c,"escapesinglequotes",0,"onoff","Escape Single Quotes");
    // @description Toggles the ability to escape single quotes in symbols when adding entries. Defaults to 1.

    CLASS_ATTR_CHAR(c,"nulltodefault",0, t_base, convert_null_to_default);
    CLASS_ATTR_STYLE_LABEL(c,"nulltodefault",0,"onoff","Convert null lllls to Default Values");
    // @description Toggles the ability to convert null lllls to default values, for columns of type int, float and symbol.
    // Default is on. If you turn this off, the null lllls will result in NULL SQLite fields.

    
	CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	
	class_register(CLASS_BOX, c);
	s_base_class = c;
	ps_event = gensym("event");
    dadaobj_class_add_fileusage_method(c);


    
    
    //// REGISTERING THE XBASE CLASS
    
    t_class *d;
    d = class_new("dada.xbase", (method)xbase_new, (method)xbase_free, (short)sizeof(t_xbase), 0L, A_GIMME, 0);
    
//    class_addmethod(c, (method)initpargs_add,		"add",	A_GIMME,	0);
//    class_addmethod(c, (method)initpargs_remove,	"remove",	A_GIMME,	0);
//    class_addmethod(c, (method)initpargs_run,		"run",	A_GIMME,	0);
    
    class_register(CLASS_NOBOX, d);
    s_xbase_class = d;

    
	return;
}



char filename_is_not_sql_file(t_symbol *s)
{
    if (s && strlen(s->s_name) > 0 && strcmp(s->s_name + strlen(s->s_name) - 4, ".db3") != 0)
        return 1;
    return 0;
}


char xbase_attach_to_text_file(t_xbase *b)
{
    if (filename_is_not_sql_file(b->d_filename))
        return 1;
    return 0;
}

char xbase_attach_to_sql_file(t_xbase *b)
{
    if (b->d_filename && strlen(b->d_filename->s_name) > 0 && strcmp(b->d_filename->s_name + strlen(b->d_filename->s_name) - 4, ".db3") == 0)
        return 1;
    return 0;
}



char xbase_store_lllls_with_phonenumbers(t_xbase *b)
{
    if (xbase_attach_to_sql_file(b))
        return 0;
    return 1;
}

void base_assist(t_base *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type anything/llll @digest Incoming queries or messages
		sprintf(s, "Incoming queries or messages");
	} 
	else {	
		char *type = NULL;
		llllobj_get_llll_outlet_type_as_string((t_object *) x, LLLL_OBJ_VANILLA, a, &type);
		if (a == 0)	// @out 0 @type llll @digest Query results or dump
			sprintf(s, "llll (%s): Query Results or Dump", type);
		else 	// @out 1 @type bang @digest Bang when an external file has been properly loaded
			sprintf(s, "bang when Reading is Completed"); 			
	}
}

long base_acceptsdrag(t_base *x, t_object *drag, t_object *view)
{
    if (true) {
        jdrag_object_add(drag, (t_object *)x, gensym("read"));
        return true;
    }
    return false;
}

void base_wopen(t_base *x)
{
    if (!x->m_editor)
        x->m_editor = (t_object *)object_new(CLASS_NOBOX, gensym("jed"), (t_object *)x, 0);
    else
        object_attr_setchar(x->m_editor, gensym("visible"), 1);
    
    char *buf = NULL;
    t_llll *ll = db_to_llll(x->xbase, true);
    
    llll_to_text_buf_pretty(ll, &buf, 0, BACH_DEFAULT_MAXDECIMALS, 0, "\t", -1, LLLL_T_NONE, LLLL_TE_SMART, LLLL_TB_SMART, NULL);
    //    llll_to_text_buf_pretty(ll, &buf, 0, BACH_DEFAULT_MAXDECIMALS, 0, "\t", -1, 0, NULL);
    //    llll_to_text_buf(ll, &buf);
    
    void *rv = object_method(x->m_editor, gensym("settext"), buf, gensym("utf-8"));  // non-0 if the text was too long
    if (rv) {
        t_object *ed = x->m_editor;
        x->m_editor = NULL;
        object_free(ed);
    } else {
        object_attr_setsym(x->m_editor, gensym("title"), gensym("Database as llll"));
    }
    llll_free(ll);}

// this lets us double-click on sphinx~ to open up the buffer~ it references
void base_dblclick(t_base *x)
{
    if (xbase_db_count_all_rows(x->xbase) > 10000) { /// < more than 10k entries would take a LONG time to deparse. one may use "wopen" then
        object_warn((t_object *)x, "You have double clicked a dada.base containing more than 10000 entries: are you sure you want to deparse and show it in textual form?");
        object_warn((t_object *)x, "   If yes, please use an explicit \"wopen\" message instead – this may take long!");
        return;
    }
    
    base_wopen(x);
}

void base_okclose(t_base *x, char *s, short *result)
{
    *result = 3;
    x->editor_dirty = true;
}

void base_edclose(t_base *x, char **ht, long size)
{
    // do something with the text
    if (x->editor_dirty && !x->is_readonly && ht) {
        t_llll *ll = llll_from_text_buf(*ht, size > MAX_SYM_LENGTH);
        if (ll) {
            xbase_destroy_all_tables(x->xbase);
            llll_to_db(x->xbase, ll, x->escape_single_quotes, x->convert_null_to_default);
            llll_free(ll);
        } else
            object_error((t_object *)x, "Can't modify database: it is wrongly formatted");
    }
    x->m_editor = NULL;
    x->editor_dirty = false;
}


long base_edsave(t_base *x, char **ht, long size)
{
    // do something with the text
    return 0;       // tell editor it can save the text
}


t_llll *xbase_get_all_table_headers(t_xbase *b)
{
    t_llll *all = llll_get();
    for (long i = 0; i < b->num_tables; i++)
        llll_appendllll(all, xbase_db_get_table_header(b, i));
    return all;
}


t_symbol *filename_to_metafilename(t_symbol *s)
{
    char temp[MAX_PATH_CHARS];
    snprintf_zero(temp, MAX_PATH_CHARS, "%s.dadameta", s->s_name);
    return gensym(temp);
}

void base_appendtodictionary(t_base *x, t_dictionary *d)
{
    if (!x->is_volatile && x->xbase && x->xbase->d_dirty) {
        
        if (xbase_attach_to_text_file(x->xbase)) {
            t_llll *ll = db_to_llll(x->xbase, true);
            //        llll_print(ll, NULL, 0, 0, NULL);
            if (x->d_filetype == 1280068684) // 'LLLL': file was native
                llll_writenative((t_object *) x, x->xbase->d_filename, ll);
            else { // textual
                t_llll *args = llll_get();
                llll_appendsym(args, x->xbase->d_filename);
                llll_writetxt((t_object *) x, ll, args, BACH_DEFAULT_MAXDECIMALS, 0, "\t", -1, LLLL_T_NONE, LLLL_TE_SMART, LLLL_TB_SMART);
                llll_free(args);
            }
        }
        
        if (!x->creating_new_obj) {
            if (xbase_attach_to_sql_file(x->xbase)) {
                t_llll *ll = xbase_get_all_table_headers(x->xbase);
                t_llll *arguments = llll_get();
                llll_appendsym(arguments, filename_to_metafilename(x->xbase->d_filename));
                llll_writetxt((t_object *)x, ll, arguments, BACH_DEFAULT_MAXDECIMALS, 0, "\t", -1, LLLL_T_NONE, LLLL_TE_SMART, LLLL_TB_SMART);
            }
        }
        
        x->xbase->d_dirty = false;
    }
}


t_base* base_new(t_symbol *s, short argc, t_atom *argv)
{
	t_base* x;
	
	long true_ac = attr_args_offset(argc, argv);

	x = (t_base*)object_alloc(s_base_class);
	if (x) {
        x->creating_new_obj = true;
        x->convert_null_to_default = true;
		x->output_fieldnames = true;
        x->escape_single_quotes = true;
		x->d_filename = NULL;
		x->d_filetype = 0;
        x->m_editor = NULL;
        x->xbase = NULL;

		llllobj_obj_setup((t_llllobj_object *)x, 1, "b4");
		
		
		// @arg 0 @name name @optional 1 @type symbol @digest Name
		// @description The first arguments sets the database name.
        // If the name is not set, an unique name will be assigned to the database.
		if (true_ac >= 1 && atom_gettype(argv) == A_SYM) {
			t_symbol *dbname = atom_getsym(argv);
			
			// @arg 1 @name filename @optional 1 @type symbol @digest Filename
			// @description The second argument, if set, sets the database filename.
			// If such argument is set, the database is automatically read from the file and saved in the file whenever the patch is saved.
            // If the name provided terminates with the ".db3" extension, the database is stored as a standard native SQLite3 database,
            // which guarantees the best performance at reloading. Otherwise, the database is saved as in bach textual form.
            if (true_ac >= 2 && atom_gettype(argv) == A_SYM) {
                x->d_filename = atom_getsym(argv + 1); //dada_ezlocate_file(atom_getsym(argv + 1), &x->d_filetype);
                if (filename_is_not_sql_file(x->d_filename)) {
                    t_symbol *located = dada_ezlocate_file(x->d_filename, &x->d_filetype);
                    if (!located) { // create one!
                        llll_writetxt((t_object *)x, llll_get(), symbol2llll(x->d_filename), BACH_DEFAULT_MAXDECIMALS, 0, "\t", -1, LLLL_T_NONE, LLLL_TE_SMART, LLLL_TB_SMART);
                        x->d_filename = dada_ezlocate_file(x->d_filename, &x->d_filetype);
                    } else
                        x->d_filename = located;
                }
            }
			
			object_attr_setsym(x, _sym_name, dbname);
		} else
            object_attr_setsym(x, _sym_name, symbol_unique());
        
        if (x->xbase)
            x->xbase->d_nodirty = true;
        attr_args_process(x, argc, argv);
		
		if (xbase_attach_to_text_file(x->xbase))
			base_read(x, x->xbase->d_filename);
        
        if (x->xbase)
            x->d_filename = x->xbase->d_filename;
        x->creating_new_obj = false;
        if (x->xbase)
            x->xbase->d_nodirty = false;
	}
	return x;
}


void base_free(t_base *x)
{
    xbase_free(x->xbase);
//	db_close(&x->d_db);
//	bach_freeptr(x->table);
}


/**********************************************************************/
// Methods

/*
 void base_entry_create(t_base *x, t_symbol *s)
{
	t_max_err	err = MAX_ERR_NONE;
	
	err = db_query(x->d_db, NULL, "INSERT INTO cues ( 'name' ) VALUES ( \"%s\" )", s->s_name);
	if(err)
		object_error((t_object*)x, "error creating event");
}


void base_cue_destroy(t_base *x, t_symbol *s)
{
	t_max_err	err = MAX_ERR_NONE;
	
	err = db_query(x->d_db, NULL, "DELETE FROM cues WHERE name = \"%s\" ", s->s_name);
	if(err)
		object_error((t_object*)x, "error deleting cue");
}


void base_cue_rename(t_base *x, t_symbol *s1, t_symbol *s2)
{
	t_max_err	err = MAX_ERR_NONE;
	
	err = db_query(x->d_db, NULL, "UPDATE cues SET name = \"%s\" WHERE name = \"%s\" ", s2->s_name, s1->s_name);
	if(err)
		object_error((t_object*)x, "error deleting cue");
}


void base_cue_do(t_base *x, t_symbol *s)
{
	t_max_err	err = MAX_ERR_NONE;
	t_db_result	*result = NULL;
	char		*str = NULL;
	int			i;
	int			numrecords;
	
	err = db_query(x->d_db, &result, "SELECT value FROM events WHERE cue_id_ext = \
				   (SELECT cue_id FROM cues WHERE name = \"%s\") ", s->s_name);
	if(err){
		object_error((t_object*)x, "invalid cue specified for 'do'");
		return;
	}
	
	numrecords = db_result_numrecords(result);
	for(i=0; i<numrecords; i++){
		t_atom	*av = NULL;
		long	ac = 0;
		
		str = db_result_string(result, i, 0);
		atom_setparse(&ac, &av, str);
		if(ac && av){
			outlet_anything(x->d_outlet, ps_event, ac, av);
			sysmem_freeptr(av);
		}
	}
}

*/


t_symbol *sym_or_obj_hatom_to_sym(t_hatom *h)
{
    t_symbol *this_sym = NULL; // symbol
    if (h->h_type == H_OBJ) {
        this_sym = gensym((char *)hatom_getobj(h));
    } else {
        this_sym = hatom_getsym(h);
    }
    return this_sym;
}

long get_num_single_quotes(char *buf, long size)
{
    long i, count_single_quotes = 0;
    for (i = 0; i < size; i++)
    if (buf[i] == '\'')
        count_single_quotes++;
    return count_single_quotes;
}


void escape_single_quotes_do(char *buf, long size)
{
    long i;
    long count_single_quotes = get_num_single_quotes(buf, size);
    long len_buf = strlen(buf);
    
    if (len_buf + count_single_quotes >= size)
        buf = (char *)bach_resizeptr(buf, (size + count_single_quotes) * sizeof(char));
    
    for (i = 0; i < len_buf; i++) {
        if (buf[i] == '\'') {
            bach_copyptr(buf + i, buf + i + 1, size - i - 1);
            buf[i] = '\'';
            i++;
            len_buf++;
        }
    }
}


long llll_obj_to_sym_fn(void *data, t_hatom *a, const t_llll *address)
{
    if (hatom_gettype(a) == H_OBJ)
        hatom_setsym(a, gensym((char *)hatom_getobj(a)));
    return 1;
}

void xbase_set_dirty(t_xbase *b)
{
    if (!b->d_nodirty) {
        b->d_dirty = true;
        // TO DO: set dirty flag for patch too.
    }
}

void xbase_entry_create_do(t_xbase *b, t_symbol *table_name, t_llllelem *specs_head, t_llll *only_these_fields, char escape_single_quotes, char convert_null_to_default)
{
    if (!specs_head) {
        xbase_error(b, "No entry has been specified!");
		return;
    }
    
    xbase_set_dirty(b);

	long tableidx = table_name ? tablename_to_tableidx(b, table_name) : -1;
	char firstname = true;
	if (tableidx > -1) {
		t_llllelem *elem;
		char *names, *values;
        const long STEP_SIZE = 8192, SAFETY_SIZE = 512;
        long names_size = 0, values_size = 0, this_names_size, this_values_size;
        long NAMES_ALLOC = STEP_SIZE, VALUES_ALLOC = STEP_SIZE;
        names = (char *)bach_newptr(NAMES_ALLOC * sizeof(char));
        values = (char *)bach_newptr(VALUES_ALLOC * sizeof(char));
        names_size = 1; values_size = 1;
        // names_size = NAMES_ALLOC; values_size = VALUES_ALLOC; // why did we do this???
        
        long names_cur = 0, values_cur = 0;
		names[0] = values[0] = 0;
		for (elem = specs_head; elem; elem = elem->l_next) {
			if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
				t_llll *ll = hatom_getllll(&elem->l_hatom);
                long router_type = hatom_gettype(&ll->l_head->l_hatom);
				if (ll && ll->l_head && (router_type == H_SYM || router_type == H_OBJ)) {
                    t_symbol *this_name = sym_or_obj_hatom_to_sym(&ll->l_head->l_hatom);
                    this_values_size = this_names_size = 0;
                    if (this_name && (!only_these_fields || is_symbol_in_llll_first_level(only_these_fields, this_name))) {
                        long col_idx = colname_to_colidx(b, tableidx, this_name);
                        if (col_idx >= 0) {
                            char col_type = b->table[tableidx].column_type[col_idx];
                            
                            if (col_type == 'l' || ll->l_head->l_next || convert_null_to_default) {
                                if (NAMES_ALLOC - names_size < SAFETY_SIZE) {
                                    NAMES_ALLOC += STEP_SIZE;
                                    names = (char *)bach_resizeptr(names, NAMES_ALLOC * sizeof(char));
                                }
                                if (VALUES_ALLOC - names_size < SAFETY_SIZE) {
                                    VALUES_ALLOC += STEP_SIZE;
                                    values = (char *)bach_resizeptr(values, VALUES_ALLOC * sizeof(char));
                                }
                                this_names_size = snprintf_zero(names + names_cur, NAMES_ALLOC - names_size, firstname ? "'%s'" : ", '%s'", this_name->s_name);
                                names_cur += this_names_size;
                                names_size += this_names_size;
                                
                                
                                if (col_idx > -1) {
                                    switch (col_type) {
                                        case 'i':
                                            this_values_size = snprintf_zero(values + values_cur, VALUES_ALLOC - values_size, firstname ? "%ld" : ", %ld", ll->l_head->l_next ? (long)hatom_getlong(&ll->l_head->l_next->l_hatom) : 0);
                                            break;
                                        case 'f':
                                            this_values_size = snprintf_zero(values + values_cur, VALUES_ALLOC - values_size, firstname ? "%f" : ", %f", ll->l_head->l_next ? hatom_getdouble(&ll->l_head->l_next->l_hatom) : 0);
                                            break;
                                        case 'r':
                                        {
                                            t_llll *temp_ll = llll_get();
                                            char *buf = NULL;
                                            llll_appendrat(temp_ll, ll->l_head->l_next ? hatom_getrational(&ll->l_head->l_next->l_hatom) : genrat(0,1));
                                            llll_to_text_buf(temp_ll, &buf, 0, BACH_DEFAULT_MAXDECIMALS, LLLL_T_NONE, LLLL_TE_SMART, LLLL_TB_SMART, NULL);
                                            this_values_size = snprintf_zero(values + values_cur, VALUES_ALLOC - values_size, firstname ? "'%s'" : ", '%s'", buf);
                                            bach_freeptr(buf);
                                            llll_free(temp_ll);
                                            break;
                                        }
                                        case 'p':
                                        {
                                            t_llll *temp_ll = llll_get();
                                            char *buf = NULL;
                                            llll_appendpitch(temp_ll, ll->l_head->l_next ? hatom_getpitch(&ll->l_head->l_next->l_hatom) : t_pitch(0));
                                            llll_to_text_buf(temp_ll, &buf, 0, BACH_DEFAULT_MAXDECIMALS, LLLL_T_NONE, LLLL_TE_SMART, LLLL_TB_SMART, NULL);
                                            this_values_size = snprintf_zero(values + values_cur, VALUES_ALLOC - values_size, firstname ? "'%s'" : ", '%s'", buf);
                                            bach_freeptr(buf);
                                            llll_free(temp_ll);
                                            break;
                                        }
                                        case 's':
                                        {
                                            char *text = NULL, *textcpy = NULL;
                                            if (ll->l_head->l_next) {
                                                if (hatom_gettype(&ll->l_head->l_next->l_hatom) == H_SYM) {
                                                    t_symbol *s = hatom_getsym(&ll->l_head->l_next->l_hatom);
                                                    text = s->s_name;
                                                } else if (hatom_gettype(&ll->l_head->l_next->l_hatom) == H_OBJ) { // string as an H_OBJ, useful sometimes to avoid generating symbols
                                                    text = (char *)hatom_getobj(&ll->l_head->l_next->l_hatom);
                                                }
                                            }
                                            
                                            char num_single_quotes = (escape_single_quotes && text ? get_num_single_quotes(text, strlen(text)) : 0);
                                            char use_copy = false;
                                            if (num_single_quotes > 0 && text) {
                                                long size = strlen(text);
                                                long newsize = (size + num_single_quotes + 10);
                                                textcpy = (char *)bach_newptr(newsize * sizeof(char));
                                                strncpy_zero(textcpy, text, size+1);
                                                escape_single_quotes_do(textcpy, newsize);
                                                use_copy = true;
                                            }
                                            
                                            while ((use_copy && textcpy && values_size + (long)strlen(textcpy) + SAFETY_SIZE > VALUES_ALLOC) ||
                                                   (!use_copy && text && values_size + (long)strlen(text) + SAFETY_SIZE > VALUES_ALLOC)) {
                                                VALUES_ALLOC += STEP_SIZE;
                                                values = (char *)bach_resizeptr(values, VALUES_ALLOC * sizeof(char));
                                            }
                                            
                                            this_values_size = snprintf_zero(values + values_cur, VALUES_ALLOC - values_size, firstname ? "'%s'" : ", '%s'", use_copy ? (textcpy ? textcpy : "") : (text ? text : ""));
                                            
                                            if (num_single_quotes > 0 && text)
                                                bach_freeptr(textcpy);
                                            
                                        }
                                            break;
                                            
                                        case 'l':
                                        {
                                            t_llll *newll = llll_behead(llll_clone(ll));
                                            if (!newll) newll = llll_get();
                                            
                                            // must convert H_OBJs element in the llll into symbols
                                            llll_funall(newll, llll_obj_to_sym_fn, NULL, 1, -1, FUNALL_ONLY_PROCESS_ATOMS);
                                            
                                            if (xbase_store_lllls_with_phonenumbers(b)) {
                                                this_values_size = snprintf_zero(values + values_cur, VALUES_ALLOC - values_size, firstname ? "%d" : ", %d", newll->l_phonenumber);
                                                llll_appendobj(b->table[tableidx].lllls, newll, 0, WHITENULL_llll);
                                            } else {
                                                char *deparsed = NULL;
                                                llll_to_text_buf(newll, &deparsed, 0, BACH_DEFAULT_MAXDECIMALS, LLLL_T_NONE, LLLL_TE_SMART, LLLL_TB_SMART, NULL);
                                                
                                                while (deparsed && values_size + strlen(deparsed) + SAFETY_SIZE > VALUES_ALLOC) {
                                                    VALUES_ALLOC += STEP_SIZE;
                                                    values = (char *)bach_resizeptr(values, VALUES_ALLOC * sizeof(char));
                                                }
                                                
                                                this_values_size = snprintf_zero(values + values_cur, VALUES_ALLOC - values_size, firstname ? "'%s'" : ", '%s'", deparsed);
                                                bach_freeptr(deparsed);
                                            }
                                        }
                                            break;
                                            
                                        default:
                                            break;
                                    }
                                } else {
                                    // id field??
                                    t_symbol *id_field_name = table_name_to_idname(table_name);
                                    if (this_name == id_field_name)
                                        this_values_size = snprintf_zero(values + values_cur, VALUES_ALLOC - values_size, firstname ? "%ld" : ", %ld", (long)hatom_getlong(&ll->l_head->l_next->l_hatom));
                                }
                                
                                
                                values_cur += this_values_size;
                                values_size += this_values_size;
                                
                                firstname = false;
                            }
                        }
                    }
				}
			}
		}
		
//      THESE TWO LINES HAVE ISSUES WHEN FORMAT STRINGS ARE VERY LONG.
//      BETTER USE THE db_query_direct() function instead (see below
        
//		if (db_query(b->d_db, NULL, "INSERT INTO %s ( %s ) VALUES ( %s )", table_name->s_name, names, values))
//			xbase_error(b, "Error while creating entry");

        char query_test[DADA_QUERY_ALLOC_CHAR_SIZE];
        snprintf(query_test, DADA_QUERY_ALLOC_CHAR_SIZE, "INSERT INTO %s ( %s ) VALUES ( %s )", table_name->s_name, names, values);
        if (db_query_direct(b->d_db, NULL, query_test))
            xbase_error(b, "Error while creating entry");
            
        bach_freeptr(names);
        bach_freeptr(values);
        
	} else {
        char buf[256];
        snprintf_zero(buf, 256, "Unknown table '%s'.", table_name ? table_name->s_name : "");
        xbase_error(b, buf);
	}
}

void base_entry_create(t_base *x, t_symbol *msg, long ac, t_atom *av)
{
	//	long num_inlet = proxy_getinlet((t_object *)x);
	t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_VANILLA, NULL, ac, av, LLLL_PARSE_RETAIN);
	if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
		xbase_entry_create_do(x->xbase, hatom_getsym(&parsed->l_head->l_hatom), parsed->l_head->l_next, NULL, x->escape_single_quotes, x->convert_null_to_default);
	}
	llll_free(parsed);
}


char xbase_util_llllelem_to_ids_and_dist(t_llllelem *elem, long *id1, long *id2, double *dist)
{
    if (hatom_gettype(&elem->l_hatom) != H_LLLL)
        return 1;
    
    t_llll *ll = hatom_getllll(&elem->l_hatom);
    if (!ll)
        return 1;
    
    if (ll->l_size == 3 && is_hatom_number(&ll->l_head->l_hatom) && is_hatom_number(&ll->l_head->l_next->l_hatom) && is_hatom_number(&ll->l_head->l_next->l_next->l_hatom)) {
        *id1 = hatom_getlong(&ll->l_head->l_hatom);
        *id2 = hatom_getlong(&ll->l_head->l_next->l_hatom);
        *dist = hatom_getdouble(&ll->l_head->l_next->l_next->l_hatom);
        return 0;
    } else
        return 1;
}

void xbase_distanceentries_create_bulk_from_idxs_do(t_xbase *b, t_symbol *disttable, t_symbol *reftable, t_llll *vals)
{
    if (vals && vals->l_head) {
        char query[4096];
        t_symbol *reftable_id = table_name_to_idname(reftable);
        t_llllelem *elem;
        long id1 = 0, id2 = 0;
        double dist = 0;
        long cursor = 0;
        long safety_limit = 3600;
        query[0] = 0;
        
        xbase_set_dirty(b);

        for (elem = vals->l_head; elem; ) {
            if (!xbase_util_llllelem_to_ids_and_dist(elem, &id1, &id2, &dist)) {
                if (cursor == 0) {
                    cursor += sprintf(query,    "INSERT INTO '%s' (%s1, %s2, distance) SELECT %ld AS '%s1', %ld AS '%s2', %f AS 'distance' ",
                                  disttable->s_name, reftable_id->s_name, reftable_id->s_name, id1, reftable_id->s_name, id2, reftable_id->s_name, dist);
                    elem = elem->l_next;
                } else if (cursor < safety_limit) {
                    cursor += sprintf(query + cursor, "UNION ALL SELECT %ld, %ld, %f ", id1, id2, dist);
                    elem = elem->l_next;
                } else {
                    // query overflow. Let's get this query sent, and then send a new one
                    if (query[0]) {
                        if (db_query_direct(b->d_db, NULL, query))
                            xbase_error(b, "Error while creating entry");
                    } else { // bad thing, should never happen
                        xbase_error(b, "Error while creating entry");
                        break;
                    }
                    cursor = 0;
                }
            }
        }
        
        if (query[0])
            if (db_query_direct(b->d_db, NULL, query))
                xbase_error(b, "Error while creating entry");
    }
}


void xbase_distanceentry_create_do(t_xbase *b, t_symbol *disttable, t_symbol *reftable, t_symbol *fieldname, t_hatom *val1, t_hatom *val2, double dist_val)
{
    //	long num_inlet = proxy_getinlet((t_object *)x);
    char *name1 = NULL, *name2 = NULL;
    char *name1ok = NULL, *name2ok = NULL;
    t_symbol *reftableidname = table_name_to_idname(reftable);

    xbase_set_dirty(b);

    hatom_to_text_buf(val1, &name1);
    if (hatom_gettype(val1) == H_SYM) {
        long len = strlen(name1);
        name1ok = (char *)bach_newptr((len + 3) * sizeof(char));
        strncpy(name1ok + 1, name1, len);
        name1ok[0] = '\'';
        name1ok[len+1] = '\'';
        name1ok[len+2] = 0;
        bach_freeptr(name1);
        name1 = name1ok;
    }
    hatom_to_text_buf(val2, &name2);
    if (hatom_gettype(val2) == H_SYM) {
        long len = strlen(name2);
        name2ok = (char *)bach_newptr((len + 3) * sizeof(char));
        strncpy(name2ok + 1, name2, len);
        name2ok[0] = '\'';
        name2ok[len+1] = '\'';
        name2ok[len+2] = 0;
        bach_freeptr(name2);
        name2 = name2ok;
    }
    char buf1[2048], buf2[2048];
    snprintf_zero(buf1, 2048, "%s1", reftableidname->s_name);
    snprintf_zero(buf2, 2048, "%s2", reftableidname->s_name);
    long id1 = -1, id2 = -1;
    t_max_err err = MAX_ERR_NONE;
    t_db_result	*result1 = NULL, *result2 = NULL;
    long numrecords, numfields;
    
    if (name1 && name2 && reftableidname && reftable && fieldname) {
        // get id of entry 1 in table reftable
        char query[2048];
        snprintf_zero(query, 2048, "SELECT %s FROM %s WHERE %s IS %s", reftableidname->s_name, reftable->s_name, fieldname->s_name, name1);
        err = db_query(b->d_db, &result1, query);
        
        if (err)
            xbase_error(b, "Error while executing query!");
        else {
            
            numrecords = db_result_numrecords(result1);
            numfields = db_result_numfields_local(result1);
            
            if (numrecords >= 1 && numfields >= 1) {
                id1 = db_result_long_local(result1, 0, 0);
                
                snprintf_zero(query, 2048, "SELECT %s FROM %s WHERE %s IS %s", reftableidname->s_name, reftable->s_name, fieldname->s_name, name2);
                
                err = db_query(b->d_db, &result2, query);
                
                if (err)
                    xbase_error(b, "Error while executing query!");
                else {
                    numrecords = db_result_numrecords(result2);
                    numfields = db_result_numfields_local(result2);
                    
                    if (numrecords >= 1 && numfields >= 1) {
                        id2 = db_result_long_local(result2, 0, 0);
                        char buf_add[2048];
                        snprintf_zero(buf_add, 2048, "( %s %ld ) ( %s %ld ) ( distance %f )", buf1, id1, buf2, id2, dist_val);
                        t_llll *specs = llll_from_text_buf(buf_add, 0);
                        xbase_entry_create_do(b, disttable, specs->l_head, NULL, true, true);
                        llll_free(specs);
                    }
                }
                
                object_free(result2);
                
            } else {
                xbase_error(b, "Error while executing query!");
            }
        }
        
        object_free(result1);
        
        bach_freeptr(name1);
        bach_freeptr(name2);
    }
}



void base_distanceentries_bulk_create_from_ids(t_base *x, t_symbol *msg, long ac, t_atom *av)
{
    //	long num_inlet = proxy_getinlet((t_object *)x);
    t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_VANILLA, NULL, ac, av, LLLL_PARSE_CLONE);
    if (parsed && parsed->l_size >= 3 && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM &&
        hatom_gettype(&parsed->l_head->l_next->l_hatom) == H_SYM) {
        t_symbol *disttable = hatom_getsym(&parsed->l_head->l_hatom);
        t_symbol *reftable = hatom_getsym(&parsed->l_head->l_next->l_hatom);
        llll_behead(parsed);
        llll_behead(parsed);
        
        xbase_distanceentries_create_bulk_from_idxs_do(x->xbase, disttable, reftable, parsed);
    }
    llll_free(parsed);
}



void base_distanceentry_create(t_base *x, t_symbol *msg, long ac, t_atom *av)
{
    //	long num_inlet = proxy_getinlet((t_object *)x);
    t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_VANILLA, NULL, ac, av, LLLL_PARSE_RETAIN);
    if (parsed && parsed->l_size >= 6 && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM &&
        hatom_gettype(&parsed->l_head->l_next->l_hatom) == H_SYM) {
        t_symbol *disttable = hatom_getsym(&parsed->l_head->l_hatom);
        t_symbol *reftable = hatom_getsym(&parsed->l_head->l_next->l_hatom);
        t_symbol *fieldname = hatom_getsym(&parsed->l_head->l_next->l_next->l_hatom);
//        t_symbol *reftableidname = table_name_to_idname(reftable);
        double dist_val = 0.;
        dist_val = hatom_getdouble(&parsed->l_head->l_next->l_next->l_next->l_next->l_next->l_hatom);

        xbase_distanceentry_create_do(x->xbase, disttable, reftable, fieldname, &parsed->l_head->l_next->l_next->l_next->l_hatom, &parsed->l_head->l_next->l_next->l_next->l_next->l_hatom, dist_val);
    }
    llll_free(parsed);
}






long llll_free_with_strings_fn(void *data, t_hatom *a, const t_llll *address)
{
    if (hatom_gettype(a) == H_OBJ)
        bach_freeptr(hatom_getobj(a));
    return 1;
}

void llll_free_with_strings(t_llll *ll)
{
    llll_funall(ll, llll_free_with_strings_fn, NULL, 1, -1, FUNALL_ONLY_PROCESS_ATOMS);
}


void base_entries_create_from_file_fn(t_base *x, t_llll *ll)
{
    t_llllelem *elem;
    
    if (!ll) {
        object_error((t_object *)x, "Wrong llll syntax in file!");
        return;
    }
    
// Better would be doing something like this,
//    INSERT INTO 'tablename'
//    SELECT 'data1' AS 'column1', 'data2' AS 'column2'
//    UNION ALL SELECT 'data1', 'data2'
//    UNION ALL SELECT 'data1', 'data2'
//    UNION ALL SELECT 'data1', 'data2'
// however I feel that the text will be too long for Max SQLite API.
// best would be INSERT INTO tab1 VALUES(?,?,?);
    
    for (elem = ll->l_head; elem; elem = elem->l_next) {
        if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
            t_llll *subll = hatom_getllll(&elem->l_hatom);
            xbase_entry_create_do(x->xbase, x->utility_sym, subll->l_head, x->utility_ll, x->escape_single_quotes, x->convert_null_to_default);
        }
    }
    llll_free_with_strings(ll);
    
    llllobj_outlet_bang((t_object *)x, LLLL_OBJ_VANILLA, 1);
}

void base_entries_create_from_file_do(t_base *x, t_symbol *table_name, t_symbol *file, t_llll *fields)
{
    x->utility_sym = table_name;
    x->utility_ll = fields;
    llll_read_sym2objs((t_object *)x, file, (read_fn)base_entries_create_from_file_fn);
}

void base_entries_create_from_file(t_base *x, t_symbol *msg, long ac, t_atom *av)
{
    if (xbase_attach_to_sql_file(x->xbase))
        db_transaction_start(x->xbase->d_db);
    
    t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_VANILLA, NULL, ac, av, LLLL_PARSE_RETAIN);
    t_llll *fields = NULL;
    if (parsed) {
        llll_parseargs_and_attrs(NULL, parsed, "l", gensym("cols"), &fields);
//        llll_parseargs(NULL, parsed, "l", gensym("cols"), &fields);
        if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
            base_entries_create_from_file_do(x, hatom_getsym(&parsed->l_head->l_hatom), parsed->l_head->l_next && hatom_gettype(&parsed->l_head->l_next->l_hatom) == H_SYM ? hatom_getsym(&parsed->l_head->l_next->l_hatom) : NULL, fields);
        }
        llll_free(fields);
        llll_free(parsed);
    }

    if (xbase_attach_to_sql_file(x->xbase))
        db_transaction_end(x->xbase->d_db);
}


char* mystrsep(char** stringp, const char* delim)
{
    char* start = *stringp;
    char* p;
    
    p = (start != NULL) ? strpbrk(start, delim) : NULL;
    
    if (p == NULL)
    {
        *stringp = NULL;
    }
    else
    {
        *p = '\0';
        *stringp = p + 1;
    }
    
    return start;
}


void base_entries_create_from_csv_do(t_object *x, t_symbol *s, long ac, t_atom *av)
{
    const long DADABASE_CSV_MAXCOLS = 8192;
    const long DADABASE_CSV_MAXLINELENGTH = 8192*16;

    t_base *b=(t_base *)x;
    t_fourcc filetype;
    t_symbol *filepath = dada_ezlocate_file(s, &filetype);
    t_symbol *table = atom_getsym(av);
    t_llll *fields = (t_llll *)atom_getobj(av+1);
    t_llll *mapping = (t_llll *)atom_getobj(av+2);
    t_llll *sticky = (t_llll *)atom_getobj(av+3);

    if (table == NULL) {
        object_error(x, "Undefined table!");
        return;
    }

    if (filepath == NULL) {
        object_error(x, "Cannot locate file!");
        return;
    }
    
    FILE* filePointer;
    char *buffer = sysmem_newptr(DADABASE_CSV_MAXLINELENGTH * sizeof(char));

    filePointer = fopen(filepath->s_name, "r");
    
    long line = 0;
    long tableidx = tablename_to_tableidx(b->xbase, table);
    if (tableidx > -1) {
        t_symbol **csvcols = (t_symbol **)sysmem_newptr(DADABASE_CSV_MAXCOLS * sizeof(t_symbol *));
        char *csvcolstype = (char *)sysmem_newptr(DADABASE_CSV_MAXCOLS * sizeof(char));
        while(fgets(buffer, DADABASE_CSV_MAXLINELENGTH, filePointer)) {
            char *temp = sysmem_newptr(DADABASE_CSV_MAXLINELENGTH * sizeof(char));
            char *tofree=temp;
            strncpy_zero(temp, buffer, DADABASE_CSV_MAXLINELENGTH);
            
            if (strlen(temp) > 0) {
                while (temp[strlen(temp)-1] == '\n' || temp[strlen(temp)-1] == '\r')
                    temp[strlen(temp)-1] = 0;
            }
            
            if (line == 0) { // header
                char* token = strtok(temp, ",");
                long numcsvcols = 0;
                while (token && numcsvcols < DADABASE_CSV_MAXCOLS) {
                    t_symbol *s = gensym(token);
                    if (fields == NULL || is_symbol_in_llll_first_level(fields, s)) {
                        // checking mapping
                        if (mapping) {
                            for (t_llllelem *el = mapping->l_head; el; el = el->l_next) {
                                if (hatom_gettype(&el->l_hatom) == H_LLLL) {
                                    t_llll *mll = hatom_getllll(&el->l_hatom);
                                    if (mll && mll->l_size >= 2 && hatom_gettype(&mll->l_head->l_hatom) == H_SYM && hatom_getsym(&mll->l_head->l_hatom) == s)
                                        s = hatom_getsym(&mll->l_head->l_next->l_hatom);
                                }
                            }
                        }
                        
                        if (s) {
                            long col_idx = colname_to_colidx(b->xbase, tableidx, s);
                            if (col_idx > -1) {
                                csvcols[numcsvcols] = s;
                                csvcolstype[numcsvcols] = b->xbase->table[tableidx].column_type[col_idx];
                            } else {
                                csvcols[numcsvcols] = NULL;
                                csvcolstype[numcsvcols] = 0;
                            }
                        } else {
                            csvcols[numcsvcols] = NULL;
                            csvcolstype[numcsvcols] = 0;
                        }
                    } else {
                        csvcols[numcsvcols] = NULL;
                        csvcolstype[numcsvcols] = 0;
                    }
                    token = strtok(NULL, ",");
                    numcsvcols++;
                }
                
            } else {
                
                t_llll *specs = sticky ? llll_clone(sticky) : llll_get();
                char* token = mystrsep(&temp, ",");
                long colnum = 0;
                while (token && colnum < DADABASE_CSV_MAXCOLS) {
                    if (csvcols[colnum] != NULL) {
                        t_llll *these_specs = llll_get();
                        llll_appendsym(these_specs, csvcols[colnum]);
                        
                        switch (csvcolstype[colnum]) {
                            case 'i':
                                llll_appendlong(these_specs, atol(token));
                                break;
                            case 'f':
                                llll_appendlong(these_specs, atof(token));
                                break;
                            default:
                                llll_appendsym(these_specs, gensym(token));
                                break;
                        }
                        llll_appendllll(specs, these_specs);
                    }
                    token = mystrsep(&temp, ",");
                    colnum++;
                }
                
                xbase_entry_create_do(b->xbase, table, specs->l_head, fields, b->escape_single_quotes, b->convert_null_to_default);
                
            }
            
            line++;
            sysmem_freeptr(tofree);
        }
        
        fclose(filePointer);
        sysmem_freeptr(csvcols);
        sysmem_freeptr(csvcolstype);
        sysmem_freeptr(buffer);
    }
    
    llll_free(fields);
    llll_free(mapping);
    llll_free(sticky);
}

void base_entries_create_from_csv(t_base *x, t_symbol *msg, long ac, t_atom *av)
{
    if (xbase_attach_to_sql_file(x->xbase))
        db_transaction_start(x->xbase->d_db);
    
    t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_VANILLA, NULL, ac, av, LLLL_PARSE_RETAIN);
    t_llll *fields = NULL;
    t_llll *mapping = NULL;
    t_llll *sticky = NULL;
    if (parsed) {
        llll_parseargs_and_attrs(NULL, parsed, "lll", gensym("cols"), &fields, gensym("mapping"), &mapping, gensym("sticky"), &sticky);
        if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
            t_atom av[4];
            t_symbol *sy = parsed->l_head->l_next && hatom_gettype(&parsed->l_head->l_next->l_hatom) == H_SYM ? hatom_getsym(&parsed->l_head->l_next->l_hatom) : NULL;
            atom_setsym(av, hatom_getsym(&parsed->l_head->l_hatom));
            atom_setobj(av+1, fields);
            atom_setobj(av+2, mapping);
            atom_setobj(av+3, sticky);

            defer(x, (method)base_entries_create_from_csv_do, sy, 3, av); // will free all the fields, mapping and sticky lllls
        }
        llll_free(parsed);
    }
    
    if (xbase_attach_to_sql_file(x->xbase))
        db_transaction_end(x->xbase->d_db);
}

/*
void base_entry_create(t_base *x, t_symbol *s, long argc, t_atom *argv)
{
	t_symbol	*name = atom_getsym(argv);
	char		*text = NULL;
	long		textsize = 0;
	t_max_err	err = MAX_ERR_NONE;
	
	if(argc < 2){
		object_error((t_object*)x, "at least two arguments required to create an event");
		return;
	}
	
	atom_gettext(argc-1, argv+1, &textsize, &text, 0);
	if(text && textsize){
		err = db_query(x->d_db, NULL, "INSERT INTO events ( 'cue_id_ext' , 'value' ) \
					   VALUES ( (SELECT cue_id FROM cues WHERE name = \"%s\") , \"%s\") ", 
					   name->s_name, text);
		if(err)
			object_error((t_object*)x, "error creating event");
	}
}
 */

void xbase_error(t_xbase *b, const char *text)
{
    error("Database %s: %s", b->d_name ? b->d_name->s_name : "", text);
}


void xbase_entry_destroy(t_xbase *b, t_symbol *tablename, long event_id)
{
	t_max_err	err = MAX_ERR_NONE;
	t_symbol *idname = table_name_to_idname(tablename);

    xbase_set_dirty(b);
	err = db_query(b->d_db, NULL, "DELETE FROM %s WHERE %s = %ld", tablename->s_name, idname->s_name);

	if (err)
        xbase_error(b, "Error deleting entry");
}


void base_entry_destroy(t_base *x, t_symbol *tablename, long event_id)
{
    xbase_entry_destroy(x->xbase, tablename, event_id);
}


void xbase_table_destroy(t_xbase *b, t_symbol *tablename)
{
	long table_idx = tablename_to_tableidx(b, tablename);
	if (table_idx > -1) {
        xbase_set_dirty(b);
        db_query(b->d_db, NULL, "DROP TABLE IF EXISTS %s", tablename->s_name);
		memcpy(&b->table[table_idx + 1], &b->table[table_idx], (DADA_XBASE_MAX_TABLES - table_idx - 1) * sizeof(t_db_table));
		b->num_tables--;
	}
} 


void base_table_destroy(t_base *x, t_symbol *tablename)
{
    xbase_table_destroy(x->xbase, tablename);
}


void xbase_destroy_all_tables(t_xbase *b)
{
	long i;
    if (!b->d_db) return;
    xbase_set_dirty(b);
    for (i = 0; i < b->num_tables; i++)
		db_query(b->d_db, NULL, "DROP TABLE IF EXISTS %s", b->table[i].name->s_name);
	b->num_tables = 0;
    xbase_set_dirty(b);
}


void xbase_table_create_do(t_xbase *b, t_symbol *tablename, t_llll *specs, long num_skip_elems, char only_create_structures)
{
	if (b->num_tables >= DADA_XBASE_MAX_TABLES) {
		xbase_error(b, "Maximum number of tables reached");
		return;
	}
	
    xbase_set_dirty(b);

	b->table[b->num_tables].num_columns = 0;
	b->table[b->num_tables].name = tablename ? tablename : _sym_table;
	
    if (tablename_to_tableidx(b, b->table[b->num_tables].name) >= 0 || db_query_table_new(b->d_db, tablename->s_name) != MAX_ERR_NONE) {
        char buf[256];
        snprintf_zero(buf, 256, "Error creating table '%s'", b->table[b->num_tables].name->s_name);
		xbase_error(b, buf);
		return;
	}
    
//    llll_print(specs, NULL, 0, 0, NULL);
	
	t_llllelem *colelem = specs->l_head;
    for (long j = 0; j < num_skip_elems; j++)
        if (colelem->l_next)
            colelem = colelem->l_next;
	for (; colelem; colelem = colelem->l_next) {
		if (hatom_gettype(&colelem->l_hatom) == H_LLLL) {
			t_llll *col = hatom_getllll(&colelem->l_hatom);
			if (col && col->l_head && col->l_head->l_next && hatom_gettype(&col->l_head->l_hatom) == H_SYM && hatom_gettype(&col->l_head->l_next->l_hatom) == H_SYM) {
				t_symbol *name = hatom_getsym(&col->l_head->l_hatom);
				t_symbol *type = hatom_getsym(&col->l_head->l_next->l_hatom);
                if (name && type && strlen(name->s_name) > 0 && strlen(type->s_name) > 0) {
                    long curr_num_cols = b->table[b->num_tables].num_columns;
                    if (curr_num_cols < DADA_XBASE_MAX_COLUMNS) {
                        b->table[b->num_tables].column_name[curr_num_cols] = name;
                        b->table[b->num_tables].column_type[curr_num_cols] = type->s_name[0];
                        b->table[b->num_tables].num_columns++;
                        if (!only_create_structures && db_query_table_addcolumn(b->d_db, b->table[b->num_tables].name->s_name, name->s_name, xbase_column_type_to_sqltype(b, type->s_name[0]), 0) != MAX_ERR_NONE) {
                            char buf[256];
                            snprintf_zero(buf, 256, "Error creating column '%s'", name->s_name);
                            xbase_error(b, buf);
                        }
                    } else {
                        xbase_error(b, "Too many columns in table!");
                    }
                }
			}
			
		}
	}
	b->num_tables++;
} 

void base_table_create(t_base *x, t_symbol *msg, long ac, t_atom *av)
{
	t_llll *ll = llllobj_parse_llll((t_object *)x, LLLL_OBJ_VANILLA, NULL, ac, av, LLLL_PARSE_RETAIN);
	if (ll && ll->l_head && hatom_gettype(&ll->l_head->l_hatom) == H_SYM)
		xbase_table_create_do(x->xbase, hatom_getsym(&ll->l_head->l_hatom), ll, 1);
	llll_free(ll);
}

void base_distancetable_create(t_base *x, t_symbol *msg, long ac, t_atom *av)
{
    t_llll *ll = llllobj_parse_llll((t_object *)x, LLLL_OBJ_VANILLA, NULL, ac, av, LLLL_PARSE_RETAIN);
    if (ll && ll->l_head && hatom_gettype(&ll->l_head->l_hatom) == H_SYM && ll->l_head->l_next && hatom_gettype(&ll->l_head->l_next->l_hatom) == H_SYM) {
        t_symbol *distance_table_name = hatom_getsym(&ll->l_head->l_hatom);
        t_symbol *ref_table_name = hatom_getsym(&ll->l_head->l_next->l_hatom);
        t_symbol *ref_table_name_idname = table_name_to_idname(ref_table_name);
        char buf[2048];
        snprintf_zero(buf, 2048, "( %s1 i ) ( %s2 i ) ( distance f )", ref_table_name_idname->s_name, ref_table_name_idname->s_name);
        t_llll *specs = llll_from_text_buf(buf, false);
        xbase_table_create_do(x->xbase, distance_table_name, specs, 0);
        llll_free(specs);
    }
    llll_free(ll);
}


void xbase_clear_table(t_xbase *b, t_symbol *tablename)
{
    xbase_set_dirty(b);
    db_query(b->d_db, NULL, "DELETE FROM %s", tablename->s_name);
}

void xbase_clear_all_tables(t_xbase *b)
{
	long i;
    xbase_set_dirty(b);
    for (i = 0; i < b->num_tables; i++)
		xbase_clear_table(b, b->table[i].name);
}

void base_bang(t_base *x)
{
//	t_db_result	*result = NULL;
//	t_max_err err;
//	err = db_query(x->d_db, &result, "ATTACH DATABASE 'testDB.db' as 'TEST'");
//	err = db_query(x->d_db, &result, ".dump");
//	object_free(result);
}

void base_dump(t_base *x)
{
    if (x->xbase) {
        x->xbase->d_nodirty = true;
        t_llll *ll = db_to_llll(x->xbase, x->output_fieldnames);
        llllobj_outlet_llll((t_object *)x, LLLL_OBJ_VANILLA, 0, ll);
        llll_free(ll);
        x->xbase->d_nodirty = false;
    }
}

t_llll *getcols(t_xbase *b)
{
    long i;
    t_llll *ll = llll_get();
    for (i = 0; i < b->num_tables; i++) {
        t_llll *this_table_header = xbase_db_get_table_header(b, i);
        llll_appendllll(ll, this_table_header, 0, WHITENULL_llll);
    }
    return ll;
}

void base_getcols(t_base *x)
{
    t_llll *ll = getcols(x->xbase);
    llllobj_outlet_llll((t_object *)x, LLLL_OBJ_VANILLA, 0, ll);
    llll_free(ll);
}


t_llll *xbase_db_get_table_header(t_xbase *b, long table_idx)
{
	t_llll *header = llll_get();
	llll_appendsym(header, b->table[table_idx].name, 0, WHITENULL_llll);
	
	long j;
	for (j = 0; j < b->table[table_idx].num_columns; j++) {
		t_llll *this_header = llll_get();
		char sym[2]; sym[0] = b->table[table_idx].column_type[j]; sym[1] = 0;
		llll_appendsym(this_header, b->table[table_idx].column_name[j], 0, WHITENULL_llll);
		llll_appendsym(this_header, gensym(sym), 0, WHITENULL_llll);
		llll_appendllll(header, this_header, 0, WHITENULL_llll);
	}

	return header;
}

t_llll *db_to_llll(t_xbase *b, char output_fieldnames)
{
	long i;
	char query[2000];
	t_llll *ll = llll_get();
	for (i = 0; i < b->num_tables; i++) {
		snprintf_zero(query, 2000, "SELECT * FROM %s", b->table[i].name->s_name);
		t_llll *query_ll = llll_from_text_buf(query, false);
		t_llll *this_table_content = xbase_db_query_from_llll(b, query_ll, output_fieldnames);
		t_llll *this_table_header = xbase_db_get_table_header(b, i);
		t_llll *this_table = llll_get();
		llll_appendllll(this_table, this_table_header, 0, WHITENULL_llll);
		llll_appendllll(this_table, this_table_content, 0, WHITENULL_llll);
		llll_appendllll(ll, this_table, 0, WHITENULL_llll);
	}
	return ll;
}

t_max_err llll_to_db(t_xbase *b, t_llll *ll, char escape_single_quotes, char convert_null_to_default)
{
	t_llllelem *elem, *item;
	t_max_err err = MAX_ERR_NONE;
	
    xbase_set_dirty(b);
	xbase_destroy_all_tables(b);
	
	// setting columns
	for (elem = ll->l_head; elem; elem = elem->l_next) {
		if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
			t_llll *ll = hatom_getllll(&elem->l_hatom);
			t_llll *header = (ll && ll->l_head && hatom_gettype(&ll->l_head->l_hatom) == H_LLLL) ? hatom_getllll(&ll->l_head->l_hatom) : NULL;
			t_llll *body = (ll && ll->l_head && ll->l_head->l_next && hatom_gettype(&ll->l_head->l_next->l_hatom) == H_LLLL) ? hatom_getllll(&ll->l_head->l_next->l_hatom) : NULL;
			
			t_symbol *tablename = NULL;
			
			if (header && header->l_head && hatom_gettype(&header->l_head->l_hatom) == H_SYM) {
				tablename = hatom_getsym(&header->l_head->l_hatom);
				xbase_table_create_do(b, tablename, header, 1);
			} else 
				err = MAX_ERR_GENERIC;
			
			if (body) {
				for (item = body->l_head; item; item = item->l_next) {
					if (hatom_gettype(&item->l_hatom) == H_LLLL) {
						t_llll *entry = hatom_getllll(&item->l_hatom);
						if (entry && tablename)
							xbase_entry_create_do(b, tablename, entry->l_head, NULL, escape_single_quotes, convert_null_to_default);
						else
							err = MAX_ERR_GENERIC;
					}
				}
			}
		}
	}
	
	return err;
}



void base_return(t_base *x, t_llll *ll)
{
	if (!ll) {
		object_error((t_object *) x, "Bad input file");
		return;
	}
	
	if (llll_to_db(x->xbase, ll, x->escape_single_quotes, x->convert_null_to_default))
		object_error((t_object *)x, "Wrong database syntax found. Correctly formed tables and entries have however been properly imported.");

	llllobj_outlet_bang((t_object *)x, LLLL_OBJ_VANILLA, 1);
	
    llll_free(ll);
	return;
	
}


void base_read(t_base *x, t_symbol *s)
{
    llll_read((t_object *) x, s, (read_fn) base_return);
}

void base_write(t_base *x, t_symbol *s, long argc, t_atom *argv){
	t_llll *state_ll = db_to_llll(x->xbase, true);
	t_symbol *filename = NULL;
	if ((argc >= 1) && (atom_gettype(argv) == A_SYM))
		filename = atom_getsym(argv);
	llll_writenative((t_object *) x, filename, state_ll);
}

void base_writetxt(t_base *x, t_symbol *s, long argc, t_atom *argv){
    t_llll *arguments = llllobj_parse_llll((t_object *) x, LLLL_OBJ_VANILLA, NULL, argc, argv, LLLL_PARSE_CLONE);
    t_llll *state_ll = db_to_llll(x->xbase, true);
    llll_writetxt((t_object *) x, state_ll, arguments, BACH_DEFAULT_MAXDECIMALS, 0, "\t", -1, LLLL_T_NONE, LLLL_TE_SMART, LLLL_TB_SMART);
}


void base_anything(t_base *x, t_symbol *msg, long ac, t_atom *av)
{
	
	t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_VANILLA, msg, ac, av, LLLL_PARSE_RETAIN);
	if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
		t_symbol *router = hatom_getsym(&parsed->l_head->l_hatom);
		if (router == gensym("erase")) 
			xbase_destroy_all_tables(x->xbase);
		else if (router == gensym("addentry") && parsed->l_head->l_next && hatom_gettype(&parsed->l_head->l_next->l_hatom) == H_SYM) 
			xbase_entry_create_do(x->xbase, hatom_getsym(&parsed->l_head->l_next->l_hatom), parsed->l_head->l_next->l_next, NULL, x->escape_single_quotes, x->convert_null_to_default);
        else if (router == gensym("addtable") && parsed->l_head->l_next && hatom_gettype(&parsed->l_head->l_next->l_hatom) == H_SYM)
            xbase_table_create_do(x->xbase, hatom_getsym(&parsed->l_head->l_next->l_hatom), parsed, 2);
		else if (router == _sym_clear) {
			if (parsed->l_head->l_next && hatom_gettype(&parsed->l_head->l_next->l_hatom) == H_SYM)
				xbase_clear_table(x->xbase, hatom_getsym(&parsed->l_head->l_next->l_hatom));
			else
				xbase_clear_all_tables(x->xbase);
        } else
            object_error((t_object *)x, "Unknown message '%s'", router ? router->s_name : "");
			
	}
	llll_free(parsed);
}


long xbase_db_count_table_rows(t_xbase *b, long table_num)
{
    char buf[2048];
    t_symbol *table_name = b->table[table_num].name;
    t_symbol *id_name = table_name_to_idname(table_name);
    if (table_name && id_name) {
        snprintf_zero(buf, 2048, "SELECT COUNT(%s) FROM %s", id_name->s_name, table_name->s_name);
        
        t_max_err    err = MAX_ERR_NONE;
        t_db_result    *result = NULL;
        err = db_query_direct(b->d_db, &result, buf);
        if (err == MAX_ERR_NONE) {
            long numrecords = db_result_numrecords(result);
            if (numrecords >= 1) {
                char **record = db_result_firstrecord(result);
                return atol(record[0]);
            }
        }
    }

    return 0;
}

long xbase_db_count_all_rows(t_xbase *b)
{
    long count = 0;
    for (long i = 0; i < b->num_tables; i++)
        count += xbase_db_count_table_rows(b, i);
    return count;
}
t_llll *xbase_db_query(t_xbase *b, char *buf, char output_fieldnames)
{
	t_max_err	err = MAX_ERR_NONE;
	t_db_result	*result = NULL;
    
    xbase_set_dirty(b);

//    err = db_query(b->d_db, &result, "%s", buf);
    // it's extremely important that we don't do this:
    // err = db_query(b->d_db, &result, buf);
    
    err = db_query_direct(b->d_db, &result, buf);

	if (err)
		xbase_error(b, "Error while executing query.");
	
	
	long i, j;
	long numrecords, numfields;
	
	numrecords = db_result_numrecords(result);
	
	// Find table from query
	long table_idx = 0;
	char *table = strcasestr(buf, "FROM ");
	if (table) {
		table += 5;
		char *tablename = strdup(table), *tmp;
		tmp = tablename;
		while (*tmp && *tmp != ' ')
			tmp++;
		*tmp = 0;
		table_idx = tablename_to_tableidx(b, gensym(tablename));
	}
	
	
	t_llll *global = NULL;
	
	if (table_idx > -1) {
		numfields = db_result_numfields_local(result);
		char fieldtypes[DADA_XBASE_MAX_COLUMNS];
		t_symbol *fieldnames[DADA_XBASE_MAX_COLUMNS];
		
		// retrieving field types
		for (j = 0; j < numfields && j < DADA_XBASE_MAX_COLUMNS; j++) {
			char *thisfieldname = db_result_fieldname_local(result, j);
			fieldnames[j] = gensym(thisfieldname);
			if (fieldnames[j] == table_name_to_idname(b->table[table_idx].name))
				fieldtypes[j] = 'i';
			else {
				long fieldidx = colname_to_colidx(b, table_idx, fieldnames[j]);
				fieldtypes[j] = (fieldidx >= 0 ? b->table[table_idx].column_type[fieldidx] : 0);
			}
		} 
		
		global = llll_get();
        
        i=0;
        for (char **record = db_result_firstrecord(result); record && i < numrecords; record = db_result_nextrecord(result), i++){
			t_llll *this_record = llll_get();
			for (j = 0; j < numfields; j++) {
				t_llll *this_field = NULL;
				
				if (output_fieldnames)  {
					this_field = llll_get();
					llll_appendsym(this_field, fieldnames[j]);
				}
				
				switch (fieldtypes[j]) {
					case 'i':
						llll_appendlong(output_fieldnames ? this_field : this_record, atol(record[j]));
						break;
					case 'f':
						llll_appenddouble(output_fieldnames ? this_field : this_record, atof(record[j]));
						break;
					case 'r':
					{
						t_symbol *rational_as_symbol = gensym(record[j]);
						if (rational_as_symbol) {
							t_llll *temp = llll_from_text_buf(rational_as_symbol->s_name, 0);
							if (temp && temp->l_head && is_hatom_number(&temp->l_head->l_hatom))
								llll_appendrat(output_fieldnames ? this_field : this_record, hatom_getrational(&temp->l_head->l_hatom));
							llll_free(temp);
						}
						break;
					}
                    case 'p':
                    {
                        t_symbol *pitch_as_symbol = gensym(record[j]);
                        if (pitch_as_symbol) {
                            t_llll *temp = llll_from_text_buf(pitch_as_symbol->s_name, 0);
                            if (temp && temp->l_head && hatom_gettype(&temp->l_head->l_hatom) == H_PITCH)
                                llll_appendpitch(output_fieldnames ? this_field : this_record, hatom_getpitch(&temp->l_head->l_hatom));
                            llll_free(temp);
                        }
                    }
                        break;
					case 's':
						llll_appendsym(output_fieldnames ? this_field : this_record, gensym(record[j]));
						break;
					case 'l':
					{
                        if (xbase_store_lllls_with_phonenumbers(b)) {
                            long phonenumber = atol(record[j]);
                            t_llll *ll = llll_retrieve_from_phonenumber_and_retain(phonenumber);
                            if (output_fieldnames)
                                llll_chain_clone(this_field, ll ? llll_clone(ll) : llll_get());
                            else
                                llll_appendllll(this_record, ll ? llll_clone(ll) : llll_get());
                            if (ll)
                                llll_release(ll);
                        } else {
                            t_llll *record_ll = llll_from_text_buf(record[j], false);
                            llll_chain(output_fieldnames ? this_field : this_record, record_ll);
                            break;
                        }
                    }
                        break;
					default:
                        // might be another query such as MAX(...) MIN(...) COUNT(...) // TO DO: how do I automatically get the type???
                        llll_appenddouble(output_fieldnames ? this_field : this_record, atol(record[j]));
                        break;
				}
				
				if (output_fieldnames)  
					llll_appendllll(this_record, this_field, 0, WHITENULL_llll);
			}
			
			llll_appendllll(global, this_record, 0, WHITENULL_llll);
		}
	}
	
	
	object_free(result);
	return global;
}

t_llll *xbase_db_query_from_llll(t_xbase *b, t_llll *query, char output_fieldnames)
{
    char *buf = NULL;
    t_llll *res = NULL;
    
    // we had LLLL_T_NO_DOUBLE_QUOTES here!!!
//    long textsize = llll_to_text_buf(query, &buf, 0, BACH_DEFAULT_MAXDECIMALS, LLLL_T_NO_DOUBLE_QUOTES, NULL);
    long textsize = llll_to_text_buf(query, &buf, 0, BACH_DEFAULT_MAXDECIMALS, LLLL_T_NONE, LLLL_TE_NONE, LLLL_TB_NONE, NULL);
    if (textsize)
        res = xbase_db_query(b, buf, output_fieldnames);
    bach_freeptr(buf);
    return res;
}


void base_query(t_base *x, t_symbol *msg, long ac, t_atom *av)
{
	if (x->xbase->num_tables == 0) {
		object_error((t_object *)x, "Database has no tables!");
		return;
	}

    t_llll *result = NULL;
    

/*    t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_VANILLA, NULL, ac, av, LLLL_PARSE_RETAIN);
    result = base_db_query_from_llll(x, parsed);
    llll_free(parsed);
*/
    if (msg == _llllobj_sym_bach_llll || (ac > 0 && atom_gettype(av) == A_SYM && atom_getsym(av) ==_llllobj_sym_bach_llll)) {
        t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_VANILLA, NULL, ac, av, LLLL_PARSE_RETAIN);
        result = xbase_db_query_from_llll(x->xbase, parsed, x->output_fieldnames);
        llll_free(parsed);
    } else {
        char *buf = NULL;
        long size = 0;
        t_max_err err = atom_gettext_debug(ac, av, &size, &buf, OBEX_UTIL_ATOM_GETTEXT_SYM_NO_QUOTE);
        if (err == MAX_ERR_NONE)
            result = xbase_db_query(x->xbase, buf, x->output_fieldnames);
        else
            object_error((t_object *)x, "Error while parsing syntax!");
        bach_freeptr(buf);
    }
	
	if (result) {
		llllobj_outlet_llll((t_object *)x, LLLL_OBJ_VANILLA, 0, result);
		llll_free(result);
	}
	
}


/**********************************************************************/
// Attribute Accessors

const char *xbase_column_type_to_sqltype(t_xbase *b, char type)
{
		switch (type) {
			case 'i':
				return "BIGINT";
				break;
			case 'f':
				return "DOUBLE PRECISION";
				break;
			case 'r':
				return "VARCHAR(512)";
				break;
            case 'p':
                return "VARCHAR(512)";
                break;
			case 's':
				return "VARCHAR(512)";
				break;
			case 'l':
                if (xbase_store_lllls_with_phonenumbers(b))
                    return "BIGINT";
                else
                    return "TEXT";
				break;
			default:
				return "";
				break;
		}
}



void xbase_set_header_from_llll(t_xbase *b, t_llll *ll)
{
    if (!ll) {
        error("Bad input file");
        return;
    }
    
    b->num_tables = 0;
    xbase_set_dirty(b);

    // setting columns
    for (t_llllelem *elem = ll->l_head; elem; elem = elem->l_next) {
        if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
            t_llll *header = hatom_getllll(&elem->l_hatom);
            
            if (header && header->l_head && hatom_gettype(&header->l_head->l_hatom) == H_SYM) {
                t_symbol *tablename = hatom_getsym(&header->l_head->l_hatom);
                xbase_table_create_do(b, tablename, header, 1, true);
            }
        }
    }
    
//    llllobj_outlet_bang((t_object *)x, LLLL_OBJ_VANILLA, 1);
    
    llll_free(ll);
    return;
    
}


long file_exists(char *fname) {
    char temp[MAX_PATH_CHARS];
    path_nameconform(fname, temp, PATH_STYLE_MAX, PATH_TYPE_BOOT);
    if (access(temp, 0) != -1 ) {
        // file exists
        return 1;
    } else {
        // file doesn't exist
        return 0;
    }
}

t_max_err rebuild_database(t_xbase *b, char readonly)
{
	long i, j;
	t_max_err err = MAX_ERR_NONE;

	
	// close the old database (if needed) and open the new one
    t_symbol *filename = b->d_filename; //dada_ezlocate_file(b->d_filename, NULL); // UNSUPPORTED FOR NOW
    if (filename && strlen(filename->s_name) <= 0)
        filename = NULL;
    if (xbase_attach_to_text_file(b)) // attached to textual file.
        filename = NULL;
	
	xbase_free_lllls(b);
	db_close(&b->d_db);

    if (filename) {
        short outpath = 0;
        t_symbol *filename_resolved = dada_ezresolve_file(filename, &outpath);

// should be like this
//        db_open_ext(b->d_name, filename_resolved->s_name, &b->d_db, readonly ? DB_OPEN_FLAGS_READONLY : DB_OPEN_FLAGS_NONE);
// but the function db_open_ext() is not found in Max api, so read-only is unsupported by now
        db_open(b->d_name, filename_resolved->s_name, &b->d_db);

        char metafile_found = false;
        t_symbol *metafile = filename_to_metafilename(filename_resolved);
        
        if (metafile && file_exists(metafile->s_name))
            metafile_found = true;
        
        if (metafile_found) {
            // we recovere the tables
            llll_read((t_object *)b, metafile, (read_fn) xbase_set_header_from_llll);
        } else if (metafile) {
            // create metafile
            t_llll *ll = xbase_get_all_table_headers(b);
            t_llll *arguments = llll_get();
            llll_appendsym(arguments, metafile);
            llll_writetxt((t_object *)b, ll, arguments, BACH_DEFAULT_MAXDECIMALS, 0, "\t", -1, LLLL_T_NONE, LLLL_TE_SMART, LLLL_TB_SMART);
        } else {
            error("No file attached!");
        }

    } else {
        db_open(b->d_name, NULL, &b->d_db);

        // by passing NULL for the second parameter to db_open() we are specifying that
        // the db exist solely in memory.
        // if you wish for it to be persistent (stored on disk),
        // this is left as an exersize for the reader...
        
        
        // hence we set up the tables in the database
        
        for (i = 0; i < b->num_tables; i++) {
            t_symbol *tablename = b->table[i].name ? b->table[i].name : _sym_table;
            err = db_query_table_new(b->d_db, tablename->s_name);
            for (j = 0; j < b->table[i].num_columns; j++) {
                err = db_query_table_addcolumn(b->d_db, tablename->s_name, b->table[i].column_name[j]->s_name, xbase_column_type_to_sqltype(b, b->table[i].column_type[j]), 0);
            }
        } 

    }
	// The above will return error codes if the tables or columns already exist.
	// This is okay, so we will always return MAX_ERR_NONE.
	return MAX_ERR_NONE;
}



void xbase_free_table_lllls(t_xbase *b, long tableidx)
{
    t_llllelem *elem;
    for (elem = b->table[tableidx].lllls->l_head; elem; elem = elem->l_next)
        llll_free((t_llll *)hatom_getobj(&elem->l_hatom));
    llll_clear(b->table[tableidx].lllls);
}

void xbase_free_lllls(t_xbase *b)
{
    long i;
    for (i = 0; i < b->num_tables; i++)
        xbase_free_table_lllls(b, i);
}

void xbase_free(t_xbase *b)
{
    if (!b)
        return; // nothing to do
    
    b->ref_count--;
    
    if (b->ref_count <= 0) {
        if (b->d_db)
            db_close(&b->d_db);
        b->d_name->s_thing = NULL;
        xbase_free_lllls(b);
        bach_freeptr(b->table);
        b->magic = DADA_XBASE_MAGIC_BAD;
        bach_freeptr(b);
    }
}

t_xbase *xbase_new(t_symbol *name)
{
    if (name->s_thing)
        return NULL;

    long i;
    
    t_xbase *b = NULL;
    
    if ((b = (t_xbase *) object_alloc(s_xbase_class))) {
        //    b = (t_xbase *)bach_newptr(sizeof(t_xbase));
        b->ref_count = 0;
        b->d_filename = NULL;
        b->num_tables = 0;
        b->d_db = NULL;
        b->d_name = name;
        b->magic = DADA_XBASE_MAGIC_GOOD;
        b->d_dirty = false;
        b->d_nodirty = true;
        b->table = (t_db_table *)bach_newptr(DADA_XBASE_MAX_TABLES * sizeof(t_db_table));
        for (i = 0; i < DADA_XBASE_MAX_TABLES; i++)
            b->table[i].lllls = llll_get();
        name->s_thing = (t_object *)b; // putting the xbase in the symbol s_thing
        return b;
    } else
        error("couldn't instantiate the xbase");

    if (b)
        return b;
    
    object_free_debug(b); // unlike freeobject(), this works even if the argument is NULL
    return NULL;
}


t_max_err base_attr_name_set(t_base *x, void *attr, long argc, t_atom *argv)
{
    t_symbol	*newname = atom_getsym(argv);
    
    if (newname == x->d_name)
        return MAX_ERR_NONE;
    
    // verifying if need to delete old xbase
    // close the old database (if needed)...
    if (x->xbase && x->xbase->ref_count <= 1)
        xbase_free(x->xbase);
    
    //... and open (or reference) the new one
    x->d_name = newname;
    if (newname->s_thing) {
        x->xbase = (t_xbase *)newname->s_thing; // database already exists
        // We verify that this is a REAL database, and not some buffer or stuff like that!
        // Ok, still a little chance that this is not the case, but we really need to have no luck :-D
        if (x->xbase->magic != DADA_XBASE_MAGIC_GOOD) {
            // not a real database, some other thing!!
            object_error((t_object *)x, "The name '%s' is already in use, and is not a dada database. Using a default unique name instead.", newname->s_name);
            x->xbase = NULL;
            x->d_name = symbol_unique();
            x->xbase = xbase_new(x->d_name);
            x->xbase->d_filename = x->d_filename;
            rebuild_database(x->xbase, x->is_readonly);
        } else if (!x->xbase->d_filename && x->d_filename) {
            x->xbase->d_filename = x->d_filename;
            rebuild_database(x->xbase, x->is_readonly);
        }
    } else {
        x->xbase = xbase_new(newname);
        x->xbase->d_filename = x->d_filename;
        rebuild_database(x->xbase, x->is_readonly);
    }
    x->xbase->ref_count++;
    
    x->xbase->d_nodirty = false;
    
    return MAX_ERR_NONE;
}



///////////////////////////////
//// A SERIES OF PARSING FUNCTIONS IN ORDER TO AVOID PASSING BY SYMBOLS - AND USING STRINGS INSTEAD
//// this is useful while using appendfromfile, because it can fill up the symbol table
//////////////////////////////


char *bach_strdup_safe(const char *str)
{
    long len = strlen(str);
    if (len < 0) len = 0;
    char *res = (char *) bach_newptr((len + 1) * sizeof(char));
    strncpy(res, str, len);
    res[len] = 0;
    return res;
}

t_llll *llll_parse_sym2objs(long ac, t_atom *av) // creates a new llll from a list in text format
{
    //	char *inlist;
    long i;
    t_llll *this_llll, *temp_llll;
    long len;
    t_llll_stack *stack;
    char *cursor = NULL, *thing_end, *txt, *more_txt, *bspos;
    long type;
    long a, b;
    char dollarnum[2048];
    t_llll *x;
    
    t_symbol *f64m = _llllobj_sym_float64_marker;
    t_symbol *f6405 = _llllobj_sym_float64_marker_05;
    t_symbol *f64corrupt = _llllobj_sym_float64_marker_corrupt;
    
    x = llll_get();
    
    if (!ac)
        return x;
    if (ac == 1 && atom_gettype(av) == A_OBJ) {
        cursor = (char *) atom_getobj(av);
        ac = -1;
    }
    
    this_llll = x;
    stack = llll_stack_new();
    
    for (i = 0; i < ac || (i == 0 && ac < 0); i++, av++) {
        if (!cursor) {
            switch (type = atom_gettype(av)) {
                case A_LONG:
                    llll_appendlong(this_llll, av->a_w.w_long, 0, WHITENULL_llll);
                    break;
                case A_FLOAT:
                    llll_appenddouble(this_llll, av->a_w.w_float, 0, WHITENULL_llll);
                    break;
                case A_COMMA:
                    llll_appendsym(this_llll, gensym(","), 0, WHITENULL_llll);
                    break;
                case A_SEMI:
                    llll_appendsym(this_llll, gensym(";"), 0, WHITENULL_llll);
                    break;
                case A_DOLLSYM:
                    llll_appendsym(this_llll, gensym("$"), 0, WHITENULL_llll);
                    break;
                case A_DOLLAR:
#ifdef BACH_MAX
                    snprintf_zero(dollarnum, 2048, "$" ATOM_LONG_PRINTF_FMT, av->a_w.w_long);
#else
                    snprintf(dollarnum, 2048, "$" ATOM_LONG_PRINTF_FMT, av->a_w.w_long);
#endif
                    llll_appendsym(this_llll, gensym(dollarnum), 0, WHITENULL_llll);
                    break;
                case A_SYM:
                    if (av->a_w.w_sym == f64m || av->a_w.w_sym == f6405 || av->a_w.w_sym == f64corrupt) {
                        t_uint64 l;
                        double *f = (double *) &l;
                        l = (++av)->a_w.w_long;
#ifdef C74_X64
#ifdef BACH_USE_NATIVE_128BIT_INTEGER
                        l |= ((t_atom_longlong) ((++av)->a_w.w_long)) << 32;
#else
                        l |= (((t_atom_longlong) ((++av)->a_w.w_long)) << 32).getLo();
#endif
#else
                        l |= ((t_atom_longlong) ((++av)->a_w.w_long)) << 32;
#endif
                        i += 2;
                        llll_appenddouble(this_llll, *f, 0, WHITENULL_llll);
                    } else {
                        cursor = av->a_w.w_sym->s_name;
                        if (*cursor == QUOTE_CHAR && *(cursor + 1)) {
                            //							if (!strrchr(cursor, '\\')
                            llll_appendsym(this_llll, gensym(cursor + 1), 0, WHITENULL_llll);
                            /*							else {
                             len = strlen(cursor);
                             txt = (char *) bach_newptr(len);
                             strncpy_zero(txt, cursor + 1, len);
                             while (bspos = strchr(txt, '\\'))
                             strcpy(bspos, bspos - 1);
                             llll_appendsym(this_llll, gensym(txt), 0, WHITENULL_llll);
                             bach_freeptr(txt);
                             } */
                            cursor = NULL;
                        } else if (llll_contains_separators(cursor)) {
                            llll_appendsym(this_llll, av->a_w.w_sym, 0, WHITENULL_llll);
                            cursor = NULL;
                        }
                    }
                    break;
            }
        }
        while (cursor && *cursor) {
            long backtick = 0, type;
            char prev_thing_end;
            switch (*cursor) {
                case '(':
                case '[':
                    temp_llll = llll_get();
                    llll_appendllll(this_llll, temp_llll, 0, WHITENULL_llll);
                    llll_stack_push(stack, this_llll);
                    this_llll = temp_llll;
                    cursor++;
                    break;
                    
                case ')': // terminates a sub-list
                case ']': // terminates a sub-list
                    temp_llll = (t_llll *) llll_stack_pop(stack);
                    if (!temp_llll)
                        goto llll_parse_err;
                    if (temp_llll->l_depth <= this_llll->l_depth)
                        temp_llll->l_depth = 1 + this_llll->l_depth;
                    this_llll = temp_llll;
                    cursor++;
                    break;
                    
                case '"':
                    cursor++;
                    thing_end = cursor;
                    while (*thing_end && *thing_end != '"')
                        thing_end++;
                    if (!*thing_end)
                        goto llll_parse_err;
                    len = thing_end - cursor;
                    txt = (char *) bach_newptr(len + 1);
#ifdef BACH_MAX
                    strncpy_zero(txt, cursor, len + 1);
#else
                    strncpy(txt, cursor, len + 1);
#endif
                    *(txt + len) = 0; // txt contains the current re-parsed llll atom
                    llll_appendobj(this_llll, bach_strdup_safe(txt));
//                    llll_appendsym(this_llll, gensym(txt), 0, WHITENULL_llll);
                    cursor = thing_end + 1;
                    break;
                    
                case QUOTE_CHAR:
                    if (ac < 0) {
                        backtick = 1;	// backtick is set if the current item begins with ` in string mode
                        cursor++;
                    }
                    
                default:
                    thing_end = cursor;
                    prev_thing_end = 0;
                    // search for the end of this element, which is given by:
                    
                    while (*thing_end &&																// the string end, or
                           (backtick || (*thing_end != '(' && *thing_end != ')' && *thing_end != '[' && *thing_end != ']')) &&					// a parenthesis, but only if we don't have backtick set
                           (!isspace(*thing_end) || (prev_thing_end == '\\' && ac < 0))) {	// a space, but only if it's not backslashed, or we're not in string mode
                        prev_thing_end = *thing_end;
                        thing_end ++;
                    }
                    
                    len = thing_end - cursor;
                    txt = (char *) bach_newptr(len + 1); 
#ifdef BACH_MAX
                    strncpy_zero(txt, cursor, len + 1);
#else
                    strncpy(txt, cursor, len + 1);
#endif
                    *(txt + len) = 0; // txt contains the current re-parsed llll atom
                    
                    type = backtick ? H_SYM : llll_typecheck(txt);
                    
                    switch(type) {
                        case H_LONG:
                            llll_appendlong(this_llll, strtol(txt, NULL, 10), 0, WHITENULL_llll);
                            break;
                        case H_DOUBLE:
                            llll_appenddouble(this_llll, strtod(txt, NULL), 0, WHITENULL_llll);
                            break;
                        case H_SYM:
                            if (!strcmp(txt, "nil")) {
                                llll_appendllll(this_llll, llll_get(), 0, WHITENULL_llll);
                                break;
                            }
                            if (!strcmp(txt, "null"))
                                break;
                            
                            if (ac < 0) {
                                char *this_txt = txt;
                                bspos = txt;
                                while (*bspos) {
                                    if (*bspos == '\\')
                                        bspos++;
                                    *this_txt++ = *bspos++;
                                }
                                *this_txt = 0;
                            }
                            
                            // duplicate string: and we append it as an OBJECT not as a symbol
                            llll_appendobj(this_llll, bach_strdup_safe(txt));
//                            llll_appendsym(this_llll, gensym(txt), 0, WHITENULL_llll);
                            break;
                        case H_RAT:
                            a = strtol(txt, &more_txt, 10);
                            b = strtol(more_txt + 1, NULL, 10);
                            llll_appendrat_from_elems(this_llll, a, b, 0, WHITENULL_llll);							
                            break;
                        default:
                            break;
                    }
                    bach_freeptr(txt);
                    cursor = thing_end; // points to the separator, because it must be parsed
                    break;
            }
            cursor = llll_next_thing(cursor);			
        }
        cursor = NULL;
    }
    
    if (stack->s_items)
        goto llll_parse_err;
    llll_stack_destroy(stack);
    return x;
    
llll_parse_err:
    llll_stack_destroy(stack);
    llll_free(x);
    return NULL;
}


// creates a llll from a text buffer
t_llll *llll_from_text_buf_sym2objs(const char *txtbuf)
{
    t_llll *ll;
    t_atom av;
    atom_setobj(&av, (t_object *) txtbuf);
    // llll_text2atoms(txtbuf, &ac, &av);
    ll = llll_parse_sym2objs(1, &av);
    // bach_freeptr(av);
    return ll;
}


t_llll *llll_readfile_sym2objs(t_object *x, t_filehandle fh)
{
    t_ptr_size size;
    char *buffer;
    t_llll *ll = NULL;
    
    // allocate memory block that is the size of the file
    sysfile_geteof(fh, &size);
    buffer = (char *) bach_newptr(size + 1);
    
    // read in the file
    sysfile_read(fh, &size, buffer);
    sysfile_close(fh);
    
    if (strncmp(buffer, "\nbach", 5)) { // it's text format
        *(buffer + size) = 0;
        ll = llll_from_text_buf_sym2objs(buffer);
    } else { // it's in old native format
        ll = llll_from_native_buf(buffer, size);
    }
    bach_freeptr(buffer);
    return ll;
}


void llll_doread_sym2objs(t_object *x, t_symbol *s, long ac, t_atom *av)
{
    t_fourcc outtype = 0;
    t_llll *ll;
    void (*outfn)(t_object *x, t_llll *outll) = (read_fn) atom_getobj(av);
    t_fourcc filetype[] = {'LLLL', 'TEXT'};
    t_filehandle fh;
    short path;
    char filename[MAX_PATH_CHARS];
    t_dictionary *dict = NULL;
    
    if (bach_openfile_for_read(x, s, &path, filetype, sizeof(filetype) / sizeof(t_fourcc), &outtype, filename) != MAX_ERR_NONE // file not found
        || *filename == 0) // canceled by user
        return;
    
    if (dictionary_read(filename, path, &dict) == MAX_ERR_NONE) {
        ll = llll_retrieve_from_dictionary(dict, "data");
        object_free(dict);
    } else {
        if (bach_readfile(x, filename, path, &fh) != MAX_ERR_NONE)
            return;
        ll = llll_readfile_sym2objs(x, fh);
    }
    
    // we have a file
    (outfn)(x, ll);
}

void llll_read_sym2objs(t_object *x, t_symbol *s, read_fn outfn)
{
    t_atom av;
    atom_setobj(&av, (void *) outfn);
    defer(x, (method)llll_doread_sym2objs, s, 1, &av);
}
