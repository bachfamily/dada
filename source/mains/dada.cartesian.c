/**
	@file
	dada.cartesian.c
	
	@name 
	dada.cartesian
	
	@realname 
	dada.cartesian
 
    @hiddenalias
    dada.catart

	@type
	object
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
	Cartesian display of a database
	
	@description
	2D interface for databases
	
	@discussion
    This object has been inspired by the CataRT software
    (by Diemo Schwarz, IMTR Team, Ircam--Centre Pompidou, and collaborators).
	
	@category
	dada, dada interfaces, dada corpus-based tools, dada geometry

	@keywords
	cartesian, corpus, database, concatenative, synthesis, exploration
	
	@seealso
	dada.base, dada.segment, dada.distances
	
	@owner
	Daniele Ghisi
*/


#include "dada.interface.h"
#include "dada.geometry.h"
#include "dada.paint.h"
#include "dada.popupmenu.h"
#include "dada.undo.h"
#include "ext_strings.h"
#include "ext_common.h"
#include "ext_symobject.h"
#include "ext_database.h"
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "indexmap.h"
#include "jdataview.h"
#include "dada.db.h"
#include "dada.notation.h"

#define DADA_CARTESIAN_INTERFACE_GRAIN_TOLERANCE 5
#define DADA_CARTESIAN_MAX_CONTENTFIELDS 32
#define DADA_CARTESIAN_MAX_CONVEXCOMB 32

////////////////////////// structures

enum {
	kOutletParameterNames = 0,
	kOutletParameterValues,
	kOutletPresetNames,
	kOutletPluginNames,
	kNumContolOutlets
};

enum {
    DADA_CARTESIAN_MODE_CARTESIAN = 0,
    DADA_CARTESIAN_MODE_CONVEXCOMB = 1
};


typedef struct _cartesian_grain
{
	long		result_idx;
	long		db_id;
	t_pt		coord;
	double		radius_px;
	
	t_atom		field_x;
	t_atom		field_y;
	t_atom		field_size;
	t_atom		field_color;
	t_atom		field_shape;
	
	t_jrgba		color;
	t_llllelem	*parent;
	long		shape;
	
	// bpm info
	double		bpm;
	double		phase;
    double      length_ms;
} t_cartesian_grain;

typedef struct _cartesian
{
	t_dadaobj_jbox	b_ob; // root object
	
	t_object	*d_dataview;	///< The dataview object
	t_hashtab	*d_columns;		///< The dataview columns:  column name -> column index
	t_object	*d_view;		///< The dbview object that we need to display in a dataview
	t_symbol	*d_query;
	t_llll  	*d_where_llll;
	t_symbol	*d_database;
    
	t_object	*d_db;			///< the actual database object

	
	t_symbol	*tablename;
	t_symbol	*field_x;
	t_symbol	*field_y;
	t_symbol	*field_size;
	t_symbol	*field_color;
	t_symbol	*field_shape;
	
    t_symbol	*field_content[DADA_CARTESIAN_MAX_CONTENTFIELDS];
    long        field_content_size;

    char        mode;
    t_symbol    *field_convexcomb[DADA_CARTESIAN_MAX_CONVEXCOMB];
    double      field_convexcomb_min[DADA_CARTESIAN_MAX_CONVEXCOMB];
    double      field_convexcomb_max[DADA_CARTESIAN_MAX_CONVEXCOMB];
    long        field_convexcomb_size;
    t_atom      field_convexcomb_norm;

    char		field_size_is_dummy;
	char		field_color_is_dummy;
	char		field_shape_is_dummy;
	char		field_x_is_string;
	char		field_y_is_string;
	char		field_size_is_string;
	char		field_color_is_string;
	char		field_shape_is_string;
	
	// notifications
	char		need_rebuild_grains;
	
	// behavior
	char		autozoom;
	
	// display
	double			maxradius;
	double			minradius;
	char			show_legend;
	double			legend_text_size;
	t_jrgba			j_legendcolor;
	char			show_turtle;
	t_jrgba			j_turtlecolor;
	char			show_grid;
	double			point_alpha;
    t_jrgba			j_graincolor;
	
	// beat synchronous processing
	char			beat_sync;
	double			last_beat_time;
	double			curr_beat_ms;
	t_symbol		*field_bpm;
	t_symbol		*field_phase;
    t_symbol		*field_length;
	char			field_bpm_is_dummy;
	char			field_phase_is_dummy;
    char			field_length_is_dummy;
    
    // playing stuff
//    char            play_one_grain_at_a_time;
//    char            loop_grains_if_no_other_grain_is_played;
    t_llll          *scheduled_times;
    double          antibis_ms;
    double          last_nonbeatsync_play_time;
    char            loop_last;
    char            interrupt_looping_on_mouseleave;
    char            interrupt_looping_when_not_hovering;
    char            interrupt_beatsync_on_mouseleave;
    t_cartesian_grain  *lastplayed_grain;
    t_symbol        *seq_router;

    void            *loop_clock;							///< The clock for the looping play (only used for non-beatsynchronous processing)


	// interface
	t_cartesian_grain	*mousehover_grain;
	t_cartesian_grain	*mousedown_grain;
	t_cartesian_grain	*turtled_grain;
    
	// points
	t_llll			*grains;
    
    // domain and range stored in object only for 01-relative knn queries.
    // THIS WON'T WORK WITH DIFFERENT VIEWS; but it is very important to have this
    double          domain_min;
    double          domain_max;
    double          range_min;
    double          range_max;
    
    char            relative_turtling;
    char            relative_knn;
    
    char            db_ok;
    char            is_creating_new_obj;
} t_cartesian;


///////////////////////// function prototypes
//// standard set
void *cartesian_new(t_symbol *s, long argc, t_atom *argv);
void cartesian_free(t_cartesian *x);
void cartesian_assist(t_cartesian *x, void *b, long m, long a, char *s);

void cartesian_paint(t_cartesian *x, t_object *view);
void cartesian_paint_ext(t_cartesian *x, t_object *view, t_dada_force_graphics *force_graphics);

void cartesian_int(t_cartesian *x, t_atom_long num);
void cartesian_float(t_cartesian *x, double num);
void cartesian_anything(t_cartesian *x, t_symbol *msg, long ac, t_atom *av);
void cartesian_bang(t_cartesian *x);

// interface
void cartesian_focusgained(t_cartesian *x, t_object *patcherview);
void cartesian_focuslost(t_cartesian *x, t_object *patcherview);
void cartesian_mousedown(t_cartesian *x, t_object *patcherview, t_pt pt, long modifiers);
void cartesian_mousemove(t_cartesian *x, t_object *patcherview, t_pt pt, long modifiers);
void cartesian_mouseup(t_cartesian *x, t_object *patcherview, t_pt pt, long modifiers);
void cartesian_mousedrag(t_cartesian *x, t_object *patcherview, t_pt pt, long modifiers);
long cartesian_key(t_cartesian *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
long cartesian_keyup(t_cartesian *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
void cartesian_mousewheel(t_cartesian *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc);
void cartesian_mouseleave(t_cartesian *x, t_object *patcherview, t_pt pt, long modifiers);
void cartesian_mouseenter(t_cartesian *x, t_object *patcherview, t_pt pt, long modifiers);
t_max_err cartesian_notify(t_cartesian *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

void cartesian_dump(t_cartesian *x);
void cartesian_clock(t_cartesian *x, t_symbol *s);
void cartesian_autozoom(t_cartesian *x);
void cartesian_autozoom_do(t_cartesian *x, t_object *view);
void cartesian_initdataview(t_cartesian *x);

t_max_err cartesian_set_query(t_cartesian *x, void *attr, long argc, t_atom *argv);
t_max_err cartesian_set_database(t_cartesian *x, void *attr, long argc, t_atom *argv);
t_max_err cartesian_setattr_where(t_cartesian *x, void *attr, long argc, t_atom *argv);

t_llll *get_grain_contentfield(t_cartesian *x, t_cartesian_grain *gr);
void output_grain_contentfield(t_cartesian *x, t_cartesian_grain *gr, t_symbol *router, char beat_sync);
void cartesian_loop_tick(t_cartesian *x);
void cartesian_schedule_interface_grain_llll(t_cartesian *x, t_cartesian_grain *gr, t_llll *ll);
void do_send_llll(t_cartesian *x, t_symbol *s, long ac, t_atom *av);
void rebuild_grains(t_cartesian *x, char preserve_turtle);
void rebuild_grains_defer_low(t_cartesian *x, char preserve_turtle);


/* void cartesian_jsave(t_cartesian *x, t_dictionary *d);
void cartesian_preset(t_cartesian *x);
void cartesian_begin_preset(t_cartesian *x, t_symbol *s, long argc, t_atom *argv);
void cartesian_restore_preset(t_cartesian *x, t_symbol *s, long argc, t_atom *argv);
void cartesian_end_preset(t_cartesian *x);

 void cartesian_clear(t_cartesian *x, char also_outside_world);
 void cartesian_undo_postprocess(t_cartesian *x);
*/


DEFINE_LLLL_ATTR_DEFAULT_GETTER(t_cartesian, d_where_llll, cartesian_getattr_where);

//////////////////////// global class pointer variable
static t_class *cartesian_class;
static t_symbol	*ps_dbview_update = NULL;
static t_symbol	*ps_dbview_query_changed = NULL;





///////////////////////// utility functions


long cartesian_colname_to_coltype(t_cartesian *x, t_symbol *tablename, t_symbol *colname)
{
    if (colname && colname->s_name) {
        if (colname == table_name_to_idname(tablename))
            return 'i';
        
        t_xbase *xbase = (t_xbase *)x->d_database->s_thing; // database already exists
        if (xbase && xbase->magic == DADA_XBASE_MAGIC_GOOD) {
            return colname_to_coltype(xbase, tablename, colname);
        }
    }
    
    return 0;
}


void cartesian_iar(t_cartesian *x)
{
	jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("grains"));
	jbox_redraw((t_jbox *)x);
}


// process any change which has happened for the shapes
void process_change(t_cartesian *x)
{
	jbox_redraw((t_jbox *)x);
}



void C74_EXPORT ext_main(void *moduleRef)
{	
	t_class *c;
	
	common_symbols_init();
	llllobj_common_symbols_init();
	

	if (dada_check_bach_version() || llllobj_test()) {
		dada_error_bachcheck();
		return;
	}

	srand(time(NULL)); // needed for the random function

	CLASS_NEW_CHECK_SIZE(c, "dada.cartesian", (method)cartesian_new, (method)cartesian_free, (long)sizeof(t_cartesian),
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, 0);	// include textfield and Fonts attributes
	//	jbox_initclass(c, 0);
	
	// paint & utilities
	class_addmethod(c, (method) cartesian_paint,			"paint", A_CANT, 0);
	class_addmethod(c, (method) cartesian_assist,			"assist",		A_CANT, 0);
	class_addmethod(c, (method)	cartesian_notify,			"bachnotify",		A_CANT,		0);

	// save & preset
/*    class_addmethod(c, (method) cartesian_preset, "preset", 0);
    class_addmethod(c, (method) cartesian_begin_preset, "begin_preset", A_GIMME, 0);
    class_addmethod(c, (method) cartesian_restore_preset, "restore_preset", A_GIMME, 0);
    class_addmethod(c, (method) cartesian_end_preset, "end_preset", 0);
	CLASS_METHOD_ATTR_PARSE(c, "begin_preset", "undocumented", gensym("long"), 0L, "1");
	CLASS_METHOD_ATTR_PARSE(c, "restore_preset", "undocumented", gensym("long"), 0L, "1");
	CLASS_METHOD_ATTR_PARSE(c, "end_preset", "undocumented", gensym("long"), 0L, "1");
	class_addmethod(c, (method) cartesian_jsave, "jsave", A_CANT, 0);
*/
	
	// @method (mouse) @digest Navigate or output grain content
	// @description When a grain is clicked, its content is output through the second outlet preceded by a "click" symbol.
	// If the <m>mousehover</m> attribute is set to 1, when a grain is hovered with the mouse, its content is output through
	// the second outlet, preceded by a "hover" symbol.
	// In any case, grain output could be postponed if beat synchronization is active (see <m>beatsync</m> attribute). <br />
    // Use scroll or two finger swipe to move in the plane. Use <m>Cmd</m>+scroll to change horizontal zoom,
    // add <m>Alt</m> to change vertical zoom.
	class_addmethod(c, (method) cartesian_focusgained, "focusgained", A_CANT, 0);
	class_addmethod(c, (method) cartesian_focuslost, "focuslost", A_CANT, 0);
	class_addmethod(c, (method) cartesian_mousedown, "mousedown", A_CANT, 0);
	class_addmethod(c, (method) cartesian_mousedrag, "mousedrag", A_CANT, 0);
	class_addmethod(c, (method) cartesian_mouseup, "mouseup", A_CANT, 0);

    // @method (keyboard) @digest Autozoom
    // @description Use <m>Tab</m> to set the zoom automatically depending on the displayed points
    class_addmethod(c, (method) cartesian_key, "key", A_CANT, 0);
  	class_addmethod(c, (method) cartesian_keyup, "keyup", A_CANT, 0);
    
    // @method (tools) @digest Navigate
    // @description
    // @copy DADA_DOC_TOOLS_INTRO
    // @copy DADA_DOC_TOOLS_ZX
	class_addmethod(c, (method) cartesian_mousemove, "mousemove", A_CANT, 0);
	class_addmethod(c, (method) cartesian_mousewheel, "mousewheel", A_CANT, 0);
	class_addmethod(c, (method) cartesian_mouseenter, "mouseenter", A_CANT, 0);
	class_addmethod(c, (method) cartesian_mouseleave, "mouseleave", A_CANT, 0);

    // @method clock @digest Select a clock source
    // @description The word <m>clock</m>, followed by the name of an existing <m>setclock</m> objects, sets the
    // object to be controlled by that <m>setclock</m> object rather than by Max's internal millisecond clock.
    // The word <m>clock</m> by itself sets the object back to using Max's regular millisecond clock.
    class_addmethod(c, (method)cartesian_clock,	"clock", A_DEFSYM, 0);
    
    
	// @method bang @digest Output sampling information
	// @description Output the sampling information regarding the sampling points set via the <m>sample</m> message.
	class_addmethod(c, (method)cartesian_bang,			"bang",			0);

        
	// @method dump @digest Output content of all grains
	// @description Outputs from the first outlet an llll containing the content field of all the grains.
	class_addmethod(c, (method)cartesian_dump,		"dump",		A_GIMME,	0);

    
    // @method autozoom @digest Set domain and range automatically
    // @description Sets domain and range automatically depending on the displayed grains.
    class_addmethod(c, (method)cartesian_autozoom,		"autozoom",	0);

    // @method domain @digest Set the X domain
    // @description The <m>domain</m> message, followed by two numbers, sets minimum and maximum coordinates
    // to be displayed on the X axis.
    // The <m>domain</m> message,  followed by the "start" or "end" symbol and a number, sets the coordinate
    // to be displayed respectively at the left boundary or at the right boundary of the object box.
    // @marg 0 @name arguments @optional 0 @type list
    class_addmethod(c, (method)cartesian_anything,		"domain",		A_GIMME,	0);
    
    // @method range @digest Set the Y range
    // @description The <m>range</m> message, followed by two numbers, sets minimum and maximum coordinates
    // to be displayed on the Y axis
    // The <m>range</m> message,  followed by the "start" or "end" symbol and a number, sets the coordinate
    // to be displayed respectively at the bottom boundary or at top right boundary of the object box.
    // @marg 0 @name arguments @optional 0 @type list
    class_addmethod(c, (method)cartesian_anything,		"range",		A_GIMME,	0);

    
    // @method getdomain @digest Retrieve current X domain
    // @description The <m>getdomain</m> message outputs from the third outlet the minimum and maximum
    // coordinates displayed on the X axis, preceded by a <m>domain</m> symbol.
    class_addmethod(c, (method)cartesian_anything,		"getdomain",		A_GIMME,	0);

    
    // @method getrange @digest Retrieve current Y range
    // @description The <m>getrange</m> message outputs from the third outlet the minimum and maximum
    // coordinates displayed on the Y axis, preceded by a <m>range</m> symbol.
    class_addmethod(c, (method)cartesian_anything,		"getrange",		A_GIMME,	0);

    
    
    // @method setturtle @digest Set the turtle
    // @description The <m>setturtle</m> message, followed by a <m>llll</m> of the kind <b>[<m>x</m>, <m>y</m>]</b>
    // sets the turtle on the nearest grain to the given (<m>x</m>, <m>y</m>) location, without causing any output. <br />
    // If <m>relativeturtle</m> is on, the coordinates are expected to be between 0 and 1, relative to the current domain and range
    // (caveat: more precisely, to the domain and range of the latest painted view of the object). <br />
    // If the <m>setturtle</m> message is followed by a symbol, this is considered as a column name, and a column value is then expected
    // as second argument. Syntax is <b>setturtle <m>colname</m> <m>value</m></b>.
    // In this case, the turtle is positioned on the (first found) grain (if any) having <m>value</m> as value for the field <m>colname</m>.
    // @marg 0 @name position_or_columnname @optional 0 @type llll/sym
    // @marg 1 @name column_value @optional 1 @type anything
    // @example setturtle [0 10] @caption Set the turtle on the nearest grain to x=0, y=10
    // @example setturtle name Warsaw @caption Set the turtle on the grain having "Warsaw" as content for the column "name"
    class_addmethod(c, (method)cartesian_anything,		"setturtle",		A_GIMME,	0);
	
    
	// @method turtle @digest Set the turtle and output grain content
	// @description The <m>turtle</m> message, followed by a <m>llll</m> of the kind <b>[<m>x</m> <m>y</m>]</b>
	// sets the turtle on the nearest grain to the given (<m>x</m>, <m>y</m>) location, and outputs the grain content field(s)
	// from the second outlet, preceded by the "turtle" symbol. <br />
    // If <m>relativeturtle</m> is on, the coordinates are expected to be between 0 and 1, relative to the current domain and range
    // (caveat: more precisely, to the domain and range of the latest painted view of the object). <br />
    // If the <m>turtle</m> message is followed by a symbol, this is considered as a column name, and a column value is then expected
    // as second argument. Syntax is <b>turtle <m>colname</m> <m>value</m></b>.
    // In this case, the turtle is positioned on the (first found) grain (if any) having <m>value</m> as value for the field <m>colname</m>.
    // @marg 0 @name position_or_columnname @optional 0 @type llll/sym
    // @marg 1 @name column_value @optional 1 @type anything
    // @example turtle [0 10] @caption Set the turtle on the nearest grain to x=0, y=10, and output content
    // @example turtle name Warsaw @caption Set the turtle on the grain having "Warsaw" as content for the column "name", and output content
	class_addmethod(c, (method)cartesian_anything,		"turtle",		A_GIMME,	0);

	
	// @method turtledelta @digest Move the turtle and output grain content
	// @description The <m>turtledelta</m> message, followed by a <m>llll</m> of the kind <b>[<m>delta_x</m>, <m>delta_y</m>]</b>
	// moves the turtle of a (<m>delta_x</m>, <m>delta_y</m>) vector and sets it to the nearest grain to the new position (ignoring
	// the grain which previously had the turtle). The content field(s) of such grain are then output from the second outlet preceded by the
	// "turtle" symbol. <br />
    // If <m>relativeturtle</m> is on, the coordinates are expected to be between 0 and 1, relative to the current domain and range
    // (caveat: more precisely, to the domain and range of the latest painted view of the object).
	// @marg 0 @name delta_position @optional 0 @type llll
	class_addmethod(c, (method)cartesian_anything,		"turtledelta",		A_GIMME,	0);
	
	
    // @method getturtle @digest Output turtle grain content
    // @description The <m>getturtle</m> message outputs the grain content for the grain where the turtle is currently located, if any.
    class_addmethod(c, (method)cartesian_anything,		"getturtle",		A_GIMME,	0);

    
	// @method knn @digest Find nearest neighbors
	// @description The <m>knn</m> message, followed by an integer <m>K</m> and an <m>llll</m> of the kind <b>[<m>x</m>, <m>y</m>]</b>,
	// finds the <m>K</m> points which are nearest to the location (<m>x</m>, <m>y</m>), and outputs their content field(s) from the third outlet. <br />
    // If an additional wrapped list of the kind <b>[<m>weight_x</m>, <m>weight_y</m>]</b> is given, then weights are applied to the knn (which
    // is useful in the case of dimensions having quite different orders of magnitudes). <br />
    // If <m>relativeknn</m> is on, the coordinates are expected to be between 0 and 1, relative to the current domain and range
    // (caveat: more precisely, to the domain and range of the latest painted view of the object).
	// @marg 0 @name number_of_neighbors @optional 0 @type int
	// @marg 1 @name position @optional 0 @type llll
    // @marg 2 @name weights @optional 1 @type llll
	class_addmethod(c, (method)cartesian_anything,		"knn",		A_GIMME,	0);
	

    // @method getnumgrains @digest Get the number of currently displayed grains
    // @description The <m>getnumgrains</m> message returns the number of currently displayed grains, preceded by the "numgrains" symbol, from the
    // third outlet.
    // N.B.: the grain calculation is performed during the paint method; unless your object is repainted, this number won't be updated.
    // A "done" notification is sent through the third outlet whenever grains have been properly recomputed. Be sure to use such notification
    // to trigger a <m>getnumgrains</m> message.
    class_addmethod(c, (method)cartesian_anything,		"getnumgrains",		A_GIMME,	0);

    
	class_addmethod(c, (method)cartesian_anything,	"anything",			A_GIMME,	0);

    
    
    DADAOBJ_JBOX_DECLARE_IMAGE_METHODS(c);

	llllobj_class_add_out_attr(c, LLLL_OBJ_UI);
	
	dadaobj_class_init(c, LLLL_OBJ_UI, DADAOBJ_BBGIMAGE | DADAOBJ_ZOOM | DADAOBJ_SPLITXYZOOM | DADAOBJ_CENTEROFFSET | DADAOBJ_GRID | DADAOBJ_AXES | DADAOBJ_LABELS | DADAOBJ_MOUSEHOVER | DADAOBJ_AXES_SHOWDEFAULT | DADAOBJ_GRID_SHOWDEFAULT | DADAOBJ_LABELS_SHOWDEFAULT | DADAOBJ_EXPORTTOJITTER);
	CLASS_ATTR_FILTER_CLIP(c, "zoom", 0.0001, 100000);

	
	CLASS_ATTR_DEFAULT(c, "patching_rect", 0, "0 0 300 300");
	// @exclude dada.cartesian
	CLASS_ATTR_DEFAULT(c, "presentation_rect", 0, "0 0 300 300");
	// @exclude dada.cartesian
	

	CLASS_STICKY_ATTR(c,"category",0,"Color");
	
	CLASS_ATTR_RGBA(c, "legendcolor", 0, t_cartesian, j_legendcolor);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "legendcolor", 0, "0.25 0.25 0.25 1.");
	CLASS_ATTR_STYLE_LABEL(c, "legendcolor", 0, "rgba", "Legend Text Color");
	// @description Sets the color of the legend.

	CLASS_ATTR_RGBA(c, "turtlecolor", 0, t_cartesian, j_turtlecolor);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "turtlecolor", 0, "0.34 0.87 0.20 1.");
	CLASS_ATTR_STYLE_LABEL(c, "turtlecolor", 0, "rgba", "Turtle Color");
	// @description Sets the color of the turtle.

    CLASS_ATTR_RGBA(c, "graincolor", 0, t_cartesian, j_graincolor);
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "graincolor", 0, "0. 0. 0. 1.");
    CLASS_ATTR_STYLE_LABEL(c, "graincolor", 0, "rgba", "Default Grain Color");
    // @description Sets the default grain color.

	CLASS_STICKY_ATTR_CLEAR(c, "category");

	

	CLASS_STICKY_ATTR(c,"category",0,"Settings");
	
	CLASS_ATTR_SYM(c,			"query",			ATTR_SET_DEFER_LOW,	t_cartesian, d_query);
	CLASS_ATTR_ACCESSORS(c,		"query",			NULL, cartesian_set_query);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"query",0,"");
	CLASS_ATTR_INVISIBLE(c, "query", ATTR_GET_OPAQUE | ATTR_SET_OPAQUE);
	// @exclude dada.cartesian
	
    CLASS_ATTR_LLLL(c,"where", ATTR_SET_DEFER, t_cartesian, d_where_llll, cartesian_getattr_where, cartesian_setattr_where);
    CLASS_ATTR_STYLE_LABEL(c, "where", 0, "text", "Where Clause For Display Query");
    CLASS_ATTR_BASIC(c, "where", 0);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"where",0,"");
	// @description Sets the SQLite 'WHERE' clause to sieve displayed data.

	CLASS_ATTR_SYM(c,			"database",			ATTR_SET_DEFER_LOW,	t_cartesian, d_database);
	CLASS_ATTR_ACCESSORS(c,		"database",			NULL, cartesian_set_database);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"database",0,"");
	CLASS_ATTR_SAVE(c,			"database",			0);
    CLASS_ATTR_STYLE_LABEL(c,	"database", 0, "text", "Database Name");
    CLASS_ATTR_BASIC(c, "database", 0);
	// @description Sets the database name. The database must be instantiated via a <o>dada.base</o> object having such name.
	

	CLASS_ATTR_SYM(c, "table", ATTR_SET_DEFER_LOW, t_cartesian, tablename);
    CLASS_ATTR_STYLE_LABEL(c, "table", 0, "text", "Table Name");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"table",0,"");
    CLASS_ATTR_BASIC(c, "table", 0);
	// @description Sets the name of the database table to be displayed.
    

    CLASS_ATTR_CHAR(c, "mode", 0, t_cartesian, mode);
    CLASS_ATTR_STYLE_LABEL(c, "mode", 0, "text", "Display Mode");
    CLASS_ATTR_ENUMINDEX(c,"mode", 0, "Cartesian Convex Combination");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"mode",0,"");
    // @description Sets the display mode: Cartesian (default) or Convex Combination
    
    CLASS_ATTR_DOUBLE_VARSIZE(c, "convexcombmin", 0, t_cartesian, field_convexcomb_min, field_convexcomb_size, DADA_CARTESIAN_MAX_CONVEXCOMB);
    CLASS_ATTR_STYLE_LABEL(c, "convexcombmin", 0, "text", "Convex Combination Minimum Values");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"convexcombmin",0,"");
    // @description Sets the minimum values for the fields to be used as vertices in Convex Combination <m>mode</m>.

    CLASS_ATTR_DOUBLE_VARSIZE(c, "convexcombmax", 0, t_cartesian, field_convexcomb_max, field_convexcomb_size, DADA_CARTESIAN_MAX_CONVEXCOMB);
    CLASS_ATTR_STYLE_LABEL(c, "convexcombmax", 0, "text", "Convex Combination Maximum Values");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"convexcombmax",0,"");
    // @description Sets the maximum values for the fields to be used as vertices in Convex Combination <m>mode</m>.
    
    CLASS_ATTR_ATOM(c, "convexcombp", 0, t_cartesian, field_convexcomb_norm);
    CLASS_ATTR_STYLE_LABEL(c, "convexcombp", 0, "text", "Convex Combination P Value");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"convexcombp",0,"2.");
    // @description Sets the p value of the norm used in Convex Combination <m>mode</m>.

    
    
	
    CLASS_STICKY_ATTR_CLEAR(c, "category");

    CLASS_STICKY_ATTR(c,"category",0,"Fields");
	
	CLASS_ATTR_SYM(c, "xfield", 0, t_cartesian, field_x);
    CLASS_ATTR_STYLE_LABEL(c, "xfield", 0, "text", "X Axis Field");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"xfield",0,"none");
    CLASS_ATTR_BASIC(c, "xfield", 0);
	// @description Sets the name of the field (column) to be displayed on the X axis.

	CLASS_ATTR_SYM(c, "yfield", 0, t_cartesian, field_y);
    CLASS_ATTR_STYLE_LABEL(c, "yfield", 0, "text", "Y Axis Field");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"yfield",0,"none");
    CLASS_ATTR_BASIC(c, "yfield", 0);
	// @description Sets the name of the field (column) to be displayed on the Y axis.

	CLASS_ATTR_SYM(c, "sizefield", 0, t_cartesian, field_size);
    CLASS_ATTR_STYLE_LABEL(c, "sizefield", 0, "text", "Size Range Field");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"sizefield",0,"none");
	// @description Sets the name of the field (column) to be mapped on the grain size, if any (use "none" to avoid defining it).

	CLASS_ATTR_SYM(c, "colorfield", 0, t_cartesian, field_color);
    CLASS_ATTR_STYLE_LABEL(c, "colorfield", 0, "text", "Color Spectrum Field");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"colorfield",0,"none");
	// @description Sets the name of the field (column) to be mapped on the grain color, if any (use "none" to avoid defining it).
	
	CLASS_ATTR_SYM(c, "shapefield", 0, t_cartesian, field_shape);
    CLASS_ATTR_STYLE_LABEL(c, "shapefield", 0, "text", "Shape Field");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"shapefield",0,"none");
	// @description Sets the name of the field (column) to be mapped on the grain shape, if any (use "none" to avoid defining it).
	// Must be an integer field (1 being mapped to a circle, 2 to a triangle, 3 to a square, and so on)
	
    CLASS_ATTR_SYM_VARSIZE(c, "contentfield", 0, t_cartesian, field_content, field_content_size, DADA_CARTESIAN_MAX_CONTENTFIELDS);
    CLASS_ATTR_STYLE_LABEL(c, "contentfield", 0, "text", "Content Field(s)");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"contentfield",0,"content");
    CLASS_ATTR_BASIC(c, "contentfield", 0);
	// @description Sets the name of the field or fields (columns) to be output
	// when the grain is clicked or hovered (usually a score gathered syntax).

    
    CLASS_ATTR_SYM_VARSIZE(c, "convexcombfield", 0, t_cartesian, field_convexcomb, field_convexcomb_size, DADA_CARTESIAN_MAX_CONVEXCOMB);
    CLASS_ATTR_STYLE_LABEL(c, "convexcombfield", 0, "text", "Convex Combination Fields");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"convexcombfield",0,"none");
    // @description Sets the names of the fields to be used as vertices in Convex Combination <m>mode</m>.
    
    
	CLASS_ATTR_SYM(c, "bpmfield", 0, t_cartesian, field_bpm);
    CLASS_ATTR_STYLE_LABEL(c, "bpmfield", 0, "text", "BPM Field");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"bpmfield",0,"none");
	// @description Sets the name of the field (column) bearing the BPM value, if any (use "none" to avoid defining it).
	
	CLASS_ATTR_SYM(c, "phasefield", 0, t_cartesian, field_phase);
    CLASS_ATTR_STYLE_LABEL(c, "phasefield", 0, "text", "BPM Phase Field");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"phasefield",0,"none");
	// @description Sets the name of the field (column) bearing the BPM phase value, if any (use "none" to avoid defining it).

    CLASS_ATTR_SYM(c, "lengthfield", 0, t_cartesian, field_length);
    CLASS_ATTR_STYLE_LABEL(c, "lengthfield", 0, "text", "Length Field (Milliseconds)");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"lengthfield",0,"none");
    // @description Sets the name of the field (column) bearing the length of the content (in milliseconds), if any (use "none" to avoid defining it).

    
	CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	
	CLASS_STICKY_ATTR(c,"category",0,"Behavior");
	
	CLASS_ATTR_CHAR(c, "autozoomwhenupdated", 0, t_cartesian, autozoom);
    CLASS_ATTR_STYLE_LABEL(c, "autozoomwhenupdated", 0, "onoff", "Auto Zoom When Updated");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"autozoomwhenupdated",0,"1");
	// @description Toggles the ability to zoom automatically when the database is updated.

    CLASS_ATTR_CHAR(c, "relativeturtle", 0, t_cartesian, relative_turtling);
    CLASS_ATTR_STYLE_LABEL(c, "relativeturtle", 0, "onoff", "Relative Turtling");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"relativeturtle",0,"0");
    // @description If <m>relativeturtle</m> is on, the values used for the <m>turtle</m>, <m>setturtle</m> and <m>turtledelta</m> messages
    // are expected to be between 0 and 1, corresponding to the minimum and maximum coordinates displayed in the domain and range of the object
    // (caveat: more precisely, to the domain and range of the latest painted view of the object).
    
    CLASS_ATTR_CHAR(c, "relativeknn", 0, t_cartesian, relative_knn);
    CLASS_ATTR_STYLE_LABEL(c, "relativeknn", 0, "onoff", "Relative KNN");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"relativeknn",0,"0");
    // @description If <m>relativeknn</m> is on, the values used for the <m>knn</m> message
    // are expected to be between 0 and 1, corresponding to the minimum and maximum coordinates displayed in the domain and range of the object
    // (caveat: more precisely, to the domain and range of the latest painted view of the object).
    
    CLASS_STICKY_ATTR_CLEAR(c, "category");
    
    

    CLASS_STICKY_ATTR(c,"category",0,"Play");

    CLASS_ATTR_CHAR(c, "beatsync", 0, t_cartesian, beat_sync);
    CLASS_ATTR_STYLE_LABEL(c, "beatsync", 0, "onoff", "Beat Synchronous Interface Play");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"beatsync",0,"0");
    CLASS_ATTR_BASIC(c, "beatsync", 0);
	// @description Toggles the ability to postpone playing of grains depending on the beat grid
	// given from the current tempo (see <m>bpmfield</m>) and depending on the grain phase (see <m>phasefield</m>).

    CLASS_ATTR_DOUBLE(c, "mindist", 0, t_cartesian, antibis_ms);
    CLASS_ATTR_STYLE_LABEL(c, "mindist", 0, "text", "Grains Scheduling Separation Time");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"mindist",0,"0");
    // @description Sets a minimum distance (in milliseconds) for two grains to be scheduled.
    // In <m>beatsync</m> mode, this avoids multiple grains to be scheduled at the same moment.
    // Use a negative number to turn this behavior off.
    
    CLASS_ATTR_CHAR(c, "looplast", 0, t_cartesian, loop_last);
    CLASS_ATTR_STYLE_LABEL(c, "looplast", 0, "onoff", "Loop Last Played Grain");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"looplast",0,"0");
    // @description Toggles the ability to loop the last played grain if no other grain has been sequenced.

    CLASS_ATTR_CHAR(c, "stoploopwhennothovered", 0, t_cartesian, interrupt_looping_when_not_hovering);
    CLASS_ATTR_STYLE_LABEL(c, "stoploopwhennothovered", 0, "onoff", "Stop Looped Playing When Mouse Is Not Hovering");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"stoploopwhennothovered",0,"1");
    // @description Toggles the ability to stop looped playing when mouse is not hovering any point

    CLASS_ATTR_CHAR(c, "stoplooponmouseleave", 0, t_cartesian, interrupt_looping_on_mouseleave);
    CLASS_ATTR_STYLE_LABEL(c, "stoplooponmouseleave", 0, "onoff", "Stop Looped Playing When Mouse Leaves");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"stoplooponmouseleave",0,"1");
    // @description Toggles the ability to stop looped playing when mouse leaves the object.
    
    
    CLASS_ATTR_CHAR(c, "stopbeatsonmouseleave", 0, t_cartesian, interrupt_beatsync_on_mouseleave);
    CLASS_ATTR_STYLE_LABEL(c, "stopbeatsonmouseleave", 0, "onoff", "Stop Beat Sync Bangs When Mouse Leaves");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"stopbeatsonmouseleave",0,"0");
    // @description Toggles the ability to stop beat sync bangs to be sent out from the last outlet when mouse leaves the object.

	CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	
	CLASS_STICKY_ATTR(c,"category",0,"Appearance");

	CLASS_ATTR_DOUBLE(c, "minr", 0, t_cartesian, minradius);
    CLASS_ATTR_STYLE_LABEL(c, "minr", 0, "text", "Minimum Point Radius");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"minr",0,"2");
	// @description Sets a minimum radius for point display.
	
	CLASS_ATTR_DOUBLE(c, "maxr", 0, t_cartesian, maxradius);
    CLASS_ATTR_STYLE_LABEL(c, "maxr", 0, "text", "Maximum Point Radius");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"maxr",0,"8");
	// @description Sets a maximum radius for point display.
	
	CLASS_ATTR_CHAR(c, "showlegend", 0, t_cartesian, show_legend);
    CLASS_ATTR_STYLE_LABEL(c, "showlegend", 0, "onoff", "Show Legend");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showlegend",0,"1");
	// @description Toggles the ability to display the point legend on mousehover.

	CLASS_ATTR_CHAR(c, "showturtle", 0, t_cartesian, show_turtle);
    CLASS_ATTR_STYLE_LABEL(c, "showturtle", 0, "onoff", "Show Turtle");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showturtle",0,"1");
	// @description Toggles the ability to display the turtle.
	
	CLASS_ATTR_DOUBLE(c, "legendsize", 0, t_cartesian, legend_text_size);
    CLASS_ATTR_STYLE_LABEL(c, "legendsize", 0, "text", "Legend Text Size");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"legendsize",0,"12");
	// @description Sets the text font size for the legend.

	CLASS_ATTR_DOUBLE(c, "alpha", 0, t_cartesian, point_alpha);
    CLASS_ATTR_STYLE_LABEL(c, "alpha", 0, "text", "Point Opacity");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"alpha",0,"50");
	// @description Sets the transparency/opacity of displayed grains.
	
	CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	cartesian_class = c;
    dadaobj_class_add_fileusage_method(c);

	ps_dbview_update = gensym("dbview_update");
	ps_dbview_query_changed = gensym("dbview_query_changed");

	dev_post("dada.cartesian compiled %s %s", __DATE__, __TIME__);
	return;
}


void view_create_do(t_cartesian *x, t_symbol *msg, long ac, t_atom *av)
{
    db_view_create(x->d_db, x->d_query->s_name, &x->d_view);
    object_attach_byptr_register(x, x->d_view, _sym_nobox);
//    dadaobj_invalidate_and_redraw(dadaobj_cast(x));
}

t_max_err cartesian_set_query(t_cartesian *x, void *attr, long argc, t_atom *argv)
{
    if (argc && argv) {
        x->d_query = atom_getsym(argv);
		object_attr_setsym(x->d_view, _sym_query, x->d_query);
		if (x->d_db && x->d_query) {
//			db_view_create(x->d_db, x->d_query->s_name, &x->d_view);
//			object_attach_byptr_register(x, x->d_view, _sym_nobox);
            defer_low(x, (method)view_create_do, NULL, 0, NULL);
		}
	}
	return MAX_ERR_NONE;
}



t_max_err cartesian_setattr_where(t_cartesian *x, void *attr, long argc, t_atom *argv)
{
    t_llll *ll;
    if ((ll = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, _llllobj_sym_none, argc, argv, LLLL_PARSE_CLONE, LLLL_I_ALL))) {
        t_llll *free_me;
        dadaobj_mutex_lock(dadaobj_cast(x));
        free_me = x->d_where_llll;
        if (ll && ll->l_head)
            llll_destroyelem(ll->l_head);
        if (ll->l_size == 1 && hatom_getsym(&ll->l_head->l_hatom) == _llllobj_sym_null) // we treat the "null" case separately, this has to be parsed and not ignore.
            llll_clear(ll);
        x->d_where_llll = ll;
        dadaobj_mutex_unlock(dadaobj_cast(x));
        llll_free(free_me);
    }
    return MAX_ERR_NONE;
}



// this MUST be deferred_low, because if we have a [dada.base] with the same db name and a db3 binding in the patch,
// and if it happens to be instantiated NEXT, the db_open(,NULL,) stuff will prevent the filenaming bond
void cartesian_set_database_do(t_cartesian *x, t_symbol *msg, long argc, t_atom *argv)
{
    t_max_err err;
    db_view_remove(x->d_db, &x->d_view);
    db_close(&x->d_db);
    
    x->d_database = msg;
    err = db_open(x->d_database, NULL, &x->d_db);
    if (!err && x->d_db && x->d_query) {
        x->db_ok = true;
        defer_low(x, (method)view_create_do, NULL, 0, NULL);
    }

    object_attr_touch((t_object *)x, gensym("database"));
}

t_max_err cartesian_set_database(t_cartesian *x, void *attr, long argc, t_atom *argv)
{
	if (argc && argv && atom_gettype(argv) == A_SYM && atom_getsym(argv) && strlen(atom_getsym(argv)->s_name) > 0) {
        defer_low(x, (method) cartesian_set_database_do, atom_getsym(argv), 0, NULL);
	}
	return MAX_ERR_NONE;
}





t_max_err cartesian_notify(t_cartesian *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	if (msg == _sym_attr_modified) {
		t_symbol *attr_name = (t_symbol *)object_method((t_object *)data, _sym_getname);
		if (attr_name == gensym("beatsync")) {
			object_attr_setdisabled((t_object *)x, gensym("bpmfield"), x->beat_sync == 0);
			object_attr_setdisabled((t_object *)x, gensym("phasefield"), x->beat_sync == 0);
			if (x->beat_sync) {
				setclock_fdelay(x->b_ob.d_ob.m_play.setclock->s_thing, x->b_ob.d_ob.m_play.m_clock, x->curr_beat_ms);
				setclock_getftime(x->b_ob.d_ob.m_play.setclock->s_thing, &x->last_beat_time);
			} else {
				setclock_unset(x->b_ob.d_ob.m_play.setclock->s_thing, x->b_ob.d_ob.m_play.m_clock);
			}
		}
        if (attr_name == gensym("stoplooponmouseleave")) {
            if (x->beat_sync)
                setclock_fdelay(x->b_ob.d_ob.m_play.setclock->s_thing, x->b_ob.d_ob.m_play.m_clock, 0);
        }
		if (attr_name == _sym_table) {
			char query[1024];
			snprintf_zero(query, 1024, "SELECT * FROM %s", x->tablename->s_name);
			object_attr_setsym((t_object *)x, gensym("query"), gensym(query));
		}
        if (attr_name == gensym("where")) {
        
        }
		if (attr_name == _sym_table || attr_name == gensym("colorfield") || attr_name == gensym("sizefield") || attr_name == gensym("shapefield") ||
			attr_name == gensym("xfield") ||  attr_name == gensym("yfield") || attr_name == gensym("lengthfield") ||
            attr_name == gensym("where") || attr_name == gensym("database") || attr_name == gensym("mode") || attr_name == gensym("convexcombfield") || attr_name == gensym("convexcombmin") || attr_name == gensym("convexcombmax") || attr_name == gensym("convexcombp") || attr_name == gensym("alpha") || attr_name == gensym("maxr") || attr_name == gensym("minr"))  {
            if (!x->is_creating_new_obj) {
                x->need_rebuild_grains = true;
                rebuild_grains(x, true); // straight away
            }
            cartesian_iar(x);
        } else if (attr_name == gensym("center") || attr_name == gensym("zoom") || attr_name == gensym("vzoom") || attr_name == gensym("grid") || attr_name == gensym("graincolor")) {
            cartesian_iar(x);
		} else
            jbox_redraw((t_jbox *)x);
		
	} else
	if (sender == x->d_view) {
		if (msg == ps_dbview_update) {
			cartesian_bang(x);
		}
		else if (msg == ps_dbview_query_changed) {	// dump all of the columns
			t_object	*column = NULL;
			t_symbol	**column_names = NULL;
			long		numcolumns = 0;
			long		i;
			
			hashtab_getkeys(x->d_columns, &numcolumns, &column_names);
			if (column_names) {
				for (i=0; i<numcolumns; i++) {
					column = jdataview_getnamedcolumn(x->d_dataview, column_names[i]);
					if (column)
						jdataview_deletecolumn(x->d_dataview, column);
				}		
				sysmem_freeptr(column_names);
			}
			hashtab_clear(x->d_columns);
		}
		else if (msg == _sym_free) {
			object_detach_byptr((t_object *)x, x->d_view);
			x->d_view = NULL;		
		}
	}
	return jbox_notify((t_jbox*)x, s, msg, sender, data);
}

/*

void cartesian_begin_preset(t_cartesian *x, t_symbol *s, long argc, t_atom *argv)
{
	dadaobj_begin_preset(dadaobj_cast(x), s, argc, argv);
}

void cartesian_restore_preset(t_cartesian *x, t_symbol *s, long argc, t_atom *argv)
{
	dadaobj_restore_preset(dadaobj_cast(x), s, argc, argv);
}

void cartesian_end_preset(t_cartesian *x)
{
	dadaobj_end_preset(dadaobj_cast(x));
}

void cartesian_preset(t_cartesian *x) {
	dadaobj_preset(dadaobj_cast(x));
}


void cartesian_jsave(t_cartesian *x, t_dictionary *d)
{
	if (x->b_ob.d_ob.save_data_with_patcher){
		if (x->b_ob.r_ob.l_dictll) {
			llll_store_in_dictionary(x->b_ob.r_ob.l_dictll, d, "cartesian_data", NULL);
		} else {
			t_llll *data = cartesian_get_state(x);
			llll_store_in_dictionary(data, d, "cartesian_data", NULL);
			llll_free(data);
		}
	} 
}
*/		

void cartesian_assist(t_cartesian *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type anything @digest Incoming <m>knn</m> message or <m>bang</m> to refresh
		sprintf(s, "knn message or bang to refresh");
	} 
	else {	
		char *type = NULL;
		llllobj_get_llll_outlet_type_as_string((t_object *) x, LLLL_OBJ_UI, a, &type);
		if (a == 0)	// @out 0 @type llll @digest Dump outlet
			sprintf(s, "llll (%s): Dump Outlet", type);
		else if (a == 1)	// @out 1 @type llll @digest Mouse hover/click content
			sprintf(s, "llll (%s): Content on Mouse Hover or Click", type); 			
		else if (a == 2)	// @out 2 @type llll @digest Queries result
			sprintf(s, "llll (%s): Queries result", type); 			
		else 	// @out 3 @type bang @digest Beat sync bang
			sprintf(s, "bang for Beat Synchronization"); 			
	}
}

void cartesian_free(t_cartesian *x)
{
	db_view_remove(x->d_db, &x->d_view);
	db_close(&x->d_db);
    llll_free(x->scheduled_times);
    llll_free(x->d_where_llll);
    llll_free(x->grains);
    object_free(x->loop_clock);
	dadaobj_jbox_free((t_dadaobj_jbox *)x); // jbox_free and llllobj_free are inside here
}


void cartesian_dump(t_cartesian *x)
{
	t_llllelem *elem;
	t_llll *res = llll_get();
	
	systhread_mutex_lock(x->b_ob.d_ob.l_mutex);
	for (elem = x->grains->l_head; elem; elem = elem->l_next) {
		t_cartesian_grain *gr = (t_cartesian_grain *)hatom_getobj(&elem->l_hatom);
		t_llll *gr_ll = get_grain_contentfield(x, gr);
		llll_appendllll(res, gr_ll, 0, WHITENULL_llll);
	}
	systhread_mutex_unlock(x->b_ob.d_ob.l_mutex);
	
	llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 0, res);
	llll_free(res);
}

//// beat synchronous processing
void cartesian_task(t_cartesian *x)
{
	// *first* we send a bang, so that user might send any other message such as knn or anything similar
	llllobj_outlet_bang((t_object *)x, LLLL_OBJ_UI, 3);
	
	setclock_fdelay(x->b_ob.d_ob.m_play.setclock->s_thing, x->b_ob.d_ob.m_play.m_clock, x->curr_beat_ms);
	setclock_getftime(x->b_ob.d_ob.m_play.setclock->s_thing, &x->last_beat_time);
    
    if (x->loop_last && x->scheduled_times->l_size == 0 && x->lastplayed_grain) {
        output_grain_contentfield(x, x->lastplayed_grain, _llllobj_sym_loop, 2);
    }
    
    llll_clear(x->scheduled_times);
}


void post_creation_do(t_cartesian *x, t_symbol *msg, long ac, t_atom *av)
{
    x->is_creating_new_obj = false;
    
    dadaobj_set_current_version_number(dadaobj_cast(x));
    
    if (x->db_ok) {
        x->need_rebuild_grains = false;
        rebuild_grains(x, false);

        // has to be deferred, because it should not happen before database has been set (and that operation was deferred): but this whole function has been deferlowed, so no need to defer again
        dadaobj_invalidate_and_redraw(dadaobj_cast(x));

        //        rebuild_grains_defer_low(x, false);
    }
}


void *cartesian_new(t_symbol *s, long argc, t_atom *argv)
{
	t_cartesian *x = NULL;
	t_dictionary *d = NULL;
	long boxflags;

	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;    
	
	if ((x = (t_cartesian *)object_alloc_debug(cartesian_class))) {
		
		x->grains = llll_get();
        x->scheduled_times = llll_get();
		x->curr_beat_ms = 1000;
        x->loop_clock = clock_new(x, (method)cartesian_loop_tick);
        x->is_creating_new_obj = true;
        x->d_where_llll = llll_get();
        
        for (long i = 0; i < DADA_CARTESIAN_MAX_CONVEXCOMB; i++)
            x->field_convexcomb_max[i] = 1.;

 		
		boxflags = 0 
				| JBOX_DRAWFIRSTIN 
				| JBOX_NODRAWBOX
				| JBOX_DRAWINLAST
				| JBOX_TRANSPARENT  
		//      | JBOX_NOGROW
		//		| JBOX_GROWY
				| JBOX_GROWBOTH
				| JBOX_HILITE
		//      | JBOX_BACKGROUND
		//		| JBOX_DRAWBACKGROUND
		//      | JBOX_NOFLOATINSPECTOR
		//      | JBOX_MOUSEDRAGDELTA
		//      | JBOX_TEXTFIELD
		;
		
		jbox_new((t_jbox *)x, boxflags, argc, argv);
		x->b_ob.r_ob.l_box.b_firstin = (t_object *)x;
//		object_obex_store((void *)x, _sym_dumpout, (t_object*)outlet_new(x, NULL));

		dadaobj_jbox_setup((t_dadaobj_jbox *)x, DADAOBJ_BBGIMAGE | DADAOBJ_ZOOM | DADAOBJ_SPLITXYZOOM | DADAOBJ_CENTEROFFSET, build_pt(5, 5), 3, 4, 2, (dada_paint_ext_fn)cartesian_paint_ext, (invalidate_and_redraw_fn)cartesian_iar, "vn", 2, "b444");
		dadaobj_addfunctions(dadaobj_cast(x), (dada_mousemove_fn)cartesian_mousemove, (method)cartesian_task, NULL, NULL, NULL, NULL, NULL, NULL);

		x->d_columns = hashtab_new(13);
		hashtab_flags(x->d_columns, OBJ_FLAG_DATA);
		x->d_query = _sym_nothing;
		x->d_database = gensym("");
		x->tablename = _sym_nothing;

		cartesian_initdataview(x);
        
        attr_dictionary_process(x,d);

        // changing min and max zoom
        x->b_ob.d_ob.m_zoom.max_zoom_perc = build_pt(10000, 10000);
        x->b_ob.d_ob.m_zoom.min_zoom_perc = build_pt(0.01, 0.01);
        
        jbox_ready((t_jbox *)x);

        defer_low(x, (method)post_creation_do, NULL, 0, NULL);
    }
	return x;
}

void cartesian_initdataview(t_cartesian *x)
{
	x->d_dataview = (t_object*)jdataview_new();
	jdataview_setclient(x->d_dataview, (t_object*)x);
	jdataview_setcolumnheaderheight(x->d_dataview, 40);
	jdataview_setheight(x->d_dataview, 16.0);
}	


void cartesian_int(t_cartesian *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	cartesian_anything(x, _sym_list, 1, argv);
}

void cartesian_float(t_cartesian *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	cartesian_anything(x, _sym_list, 1, argv);
}

void cartesian_autozoom(t_cartesian *x)
{
    dadaobj_cast(x)->m_zoom.must_autozoom = true;
    cartesian_iar(x);
}


void cartesian_clock(t_cartesian *x, t_symbol *s)
{
    void *old = x->b_ob.d_ob.m_play.setclock->s_thing;
    t_object *c = 0;
    
    // the line below can be restated as:
    // if s is the empty symbol
    // or s->s_thing is zero
    // or s->s_thing is non-zero and a setclock object
    if (s && (s == gensym("") || ((c = (t_object *) s->s_thing) && zgetfn(c, gensym("unset"))))) {
        if (old) {
            setclock_unset(x->b_ob.d_ob.m_play.setclock->s_thing, x->loop_clock);
            setclock_unset(x->b_ob.d_ob.m_play.setclock->s_thing, x->b_ob.d_ob.m_play.m_clock);
        }
        x->b_ob.d_ob.m_play.setclock = s;
    } 
}



void cartesian_bang(t_cartesian *x)
{	
	x->need_rebuild_grains = true;
    rebuild_grains(x, true); // straight away
	cartesian_iar(x);
	return;
/*	
	t_object	*result = NULL;
	long		numrecords;
	long		numfields;
	long		i;
	char		*fieldname = NULL;
	t_symbol	*sfieldname = NULL;
	t_object	*column;
	t_atom_long	column_index;
	t_rowref	*rowrefs = NULL;
	t_max_err	err;
	
	db_view_getresult(x->d_view, &result);
	jdataview_clear(x->d_dataview);
	if (!result)
		return;
	
	numrecords = (long)object_method(result, _sym_numrecords);
	if (numrecords) {
		numfields = (long)object_method(result, _sym_numfields);
		for (i = 0; i < numfields; i++) {
			fieldname = (char*)object_method(result, _sym_fieldnamebyindex, i);
			if (fieldname) {
				sfieldname = gensym(fieldname);
				err = hashtab_lookuplong(x->d_columns, sfieldname, &column_index);
				if (!err) {
					; // column already exists, so we leave it alone
				}
				else{
					column = jdataview_addcolumn(x->d_dataview, sfieldname, NULL, true);
					jcolumn_setlabel(column, sfieldname);
					jcolumn_setwidth(column, 110);
					jcolumn_setmaxwidth(column, 300);
					hashtab_store(x->d_columns, sfieldname, (t_object*)i);
				}
			}
		}
		
		rowrefs = (t_rowref*)malloc(sizeof(t_rowref) * numrecords);
		for (i = 0; i < numrecords; i++)
			rowrefs[i] = (t_rowref*)(i+1);
		jdataview_addrows(x->d_dataview, numrecords, rowrefs);
		free(rowrefs);
	} */
}

void cartesian_clear(t_cartesian *x, char also_outside_current_world)
{	
	jbox_redraw((t_jbox *)x);
}

void cartesian_dump(t_cartesian *x, char get_world, char get_notes)
{	
	;
}


long sort_by_pt_distance_fn(void *data, t_llllelem *a, t_llllelem *b)
{
	t_cartesian_grain *a_gr = (t_cartesian_grain *)hatom_getobj(&a->l_hatom);
	t_cartesian_grain *b_gr = (t_cartesian_grain *)hatom_getobj(&b->l_hatom);
    t_pt coord = *((t_pt *)(((void **)data)[0]));
    if (((void **)data)[1]) {
        t_pt weights = *((t_pt *)(((void **)data)[1]));
        return (pt_pt_distance_squared_weighted(a_gr->coord, coord, weights) <= pt_pt_distance_squared_weighted(b_gr->coord, coord, weights));
    } else {
        return (pt_pt_distance_squared(a_gr->coord, coord) <= pt_pt_distance_squared(b_gr->coord, coord));
    }
}

long sort_by_pt_distance_relative_fn(void *data, t_llllelem *a, t_llllelem *b)
{
    t_cartesian_grain *a_gr = (t_cartesian_grain *)hatom_getobj(&a->l_hatom);
    t_cartesian_grain *b_gr = (t_cartesian_grain *)hatom_getobj(&b->l_hatom);
    t_pt coord = *((t_pt *)(((void **)data)[0]));
    t_pt weights = *((t_pt *)(((void **)data)[1]));
    t_rect relative_rect = *((t_rect *)(((void **)data)[2]));
    
    t_pt a_pt = build_pt((a_gr->coord.x - relative_rect.x)/relative_rect.width, (a_gr->coord.y - relative_rect.y)/relative_rect.height);
    t_pt b_pt = build_pt((b_gr->coord.x - relative_rect.x)/relative_rect.width, (b_gr->coord.y - relative_rect.y)/relative_rect.height);
    
    if (((void **)data)[1]) {
        t_pt weights = *((t_pt *)(((void **)data)[1]));
        return (pt_pt_distance_squared_weighted(a_pt, coord, weights) <= pt_pt_distance_squared_weighted(b_pt, coord, weights));
    } else {
        return (pt_pt_distance_squared(a_pt, coord) <= pt_pt_distance_squared(b_pt, coord));
    }
}



// This is not a true tree-based sublinear knn, just a linear search.
// TO DO: improve it in the future, by making it a true O(logN) knn
t_llll *cartesian_get_knn(t_cartesian *x, long num_neighbors, t_pt coord, t_pt *weights, t_cartesian_grain *but_not_this_grain, char coord_are_01)
{
	t_llllelem *elem;
	long count;

//	post("- coord: %ld, %ld", coord.x, coord.y);

    void *data[3];
    t_rect rect;
    if (coord_are_01)
        rect = build_rect(x->domain_min, x->range_min, x->domain_max - x->domain_min, x->range_max - x->range_min);
    data[0] = &coord;
    data[1] = weights;
    data[2] = &rect;
    
    if (coord_are_01) {
        llll_inplacesort(x->grains, (sort_fn) sort_by_pt_distance_relative_fn, data);
    } else
        llll_inplacesort(x->grains, (sort_fn) sort_by_pt_distance_fn, data);
	
	t_llll *res = llll_get();
	for (elem = x->grains->l_head, count = 0; elem && count < num_neighbors; elem = elem->l_next){
		if (but_not_this_grain && but_not_this_grain == (t_cartesian_grain *)hatom_getobj(&elem->l_hatom))
			continue;
		llll_appendobj(res, hatom_getobj(&elem->l_hatom), 0, WHITENULL_llll);
		count++;
	}
	
	return res;
}

t_cartesian_grain *cartesian_get_1nn(t_cartesian *x, t_pt coord, t_pt *weights, t_cartesian_grain *but_not_this_grain, char coord_are_01)
{
	t_cartesian_grain *gr = NULL;
	
	t_llll *res = cartesian_get_knn(x, 1, coord, weights, but_not_this_grain, coord_are_01);
	
	if (res->l_head) 
		gr = (t_cartesian_grain *)hatom_getobj(&res->l_head->l_hatom);
	
	llll_free(res);
	return gr;
}




t_cartesian_grain *cartesian_get_grain_from_table_id(t_cartesian *x, long table_id)
{
    for (t_llllelem *elem = x->grains->l_head; elem; elem = elem->l_next) {
        t_cartesian_grain *gr = (t_cartesian_grain *)hatom_getobj(&elem->l_hatom);
        if (gr->db_id == table_id)
            return gr;
    }
    return NULL;
}

t_cartesian_grain *cartesian_get_grain_from_field_value(t_cartesian *x, t_symbol *fieldname, char *value)
{
    char query[2048];
    t_symbol *tablename = x->tablename;
    t_symbol *tablenameid = table_name_to_idname(tablename);
    t_db_result	*result = NULL;
    snprintf_zero(query, 2048, "SELECT %s FROM %s WHERE %s IS %s", tablenameid->s_name, tablename->s_name, fieldname->s_name, value);
    t_max_err err = db_query(x->d_db, &result, query);
    t_cartesian_grain *gr = NULL;
    
    if (err)
        object_error((t_object *)x, "Error while retrieving grain! Check the fieldname and value specifications.");
    else {
        long numrecords = db_result_numrecords(result);
        long numfields = db_result_numfields_local(result);
        
        if (numrecords >= 1 && numfields >= 1) {
            long id = db_result_long_local(result, 0, 0);
            gr = cartesian_get_grain_from_table_id(x, id);
            if (!gr)
                object_warn((t_object *)x, "Warning: the found grain is currently not displayed.");
        } else {
            object_warn((t_object *)x, "Warning: no grain could be found with the desired field specifications.");
        }
    }
    object_free(result);
    result = NULL;
    return gr;
}


// Beware, will modify args!!!!
// But won't free it
void cartesian_setturtle(t_cartesian *x, t_llll *args)
{
    dadaobj_mutex_lock(dadaobj_cast(x));
    if (hatom_gettype(&args->l_head->l_hatom) == H_LLLL) {
        // The grain can be the nearest grain to an (x y) value...
        char has_weights = false;
        t_pt weights;
        if (args->l_head->l_next && hatom_gettype(&args->l_head->l_next->l_hatom) == H_LLLL) {
            has_weights = true;
            weights = llll_to_pt(hatom_getllll(&args->l_head->l_next->l_hatom));
        }
        t_pt pt = llll_to_pt(hatom_getllll(&args->l_head->l_hatom));
        x->turtled_grain = cartesian_get_1nn(x, pt, has_weights ? &weights : NULL, NULL, x->relative_turtling);
    } else if (hatom_gettype(&args->l_head->l_hatom) == H_SYM) {
        // ... or the grain having a certain field set to a certain value
        char *  valuestr = NULL;
        t_symbol *tablename = hatom_getsym(&args->l_head->l_hatom);
        llll_behead(args);
        llll_to_text_buf(args, &valuestr, 0, BACH_DEFAULT_MAXDECIMALS, LLLL_T_NONE, LLLL_TE_SQL_STYLE, LLLL_TB_SQL_STYLE, NULL);
        x->turtled_grain = cartesian_get_grain_from_field_value(x, tablename, valuestr);
        bach_freeptr(valuestr);
    }
    dadaobj_mutex_unlock(dadaobj_cast(x));
}


void cartesian_anything(t_cartesian *x, t_symbol *msg, long ac, t_atom *av)
{
	dadaobj_anything(dadaobj_cast(x), msg, ac, av);
	
	t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, msg, ac, av, LLLL_PARSE_RETAIN);
    if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
        t_symbol *router = hatom_getsym(&parsed->l_head->l_hatom);
        llll_behead(parsed);

        if (dadaobj_anything_handle_domain_or_range(dadaobj_cast(x), router, parsed, 2)) {
            // nothing to do!
        } else if (router == gensym("knn") && parsed->l_size >= 2 && hatom_gettype(&parsed->l_head->l_hatom) == H_LONG && hatom_gettype(&parsed->l_head->l_next->l_hatom) == H_LLLL) {
            long n = hatom_getlong(&parsed->l_head->l_hatom);
            t_pt coord = llll_to_pt(hatom_getllll(&parsed->l_head->l_next->l_hatom));
            char has_weights = false;
            t_pt weights;
            if (parsed->l_size >= 2 && hatom_gettype(&parsed->l_head->l_next->l_next->l_hatom) == H_LLLL) {
                has_weights = true;
                weights = llll_to_pt(hatom_getllll(&parsed->l_head->l_next->l_next->l_hatom));
            }
            t_llll *grains_knn = cartesian_get_knn(x, n, coord, has_weights ? &weights : NULL, NULL, x->relative_knn);
            t_llllelem *elem;
            t_llll *out = llll_get();
            for (elem = grains_knn->l_head; elem; elem = elem->l_next)  {
                t_llll *this_content = get_grain_contentfield(x, (t_cartesian_grain *)hatom_getobj(&elem->l_hatom));
                llll_appendllll(out, this_content, 0, WHITENULL_llll);
            }
            
            llll_prependsym(out, gensym("knn"), 0, WHITENULL_llll);
            llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 2, out);
            llll_free(out);
            llll_free(grains_knn);
            
        } else if (router == gensym("getnumgrains")) {
            t_llll *out = symbol_and_long_to_llll(gensym("numgrains"), x->grains->l_size);
            llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 2, out);
            llll_free(out);
            
        } else if (router == gensym("setturtle") && parsed->l_size >= 1) {
            cartesian_setturtle(x, parsed);
            jbox_redraw((t_jbox *)x);
            
        } else if (router == gensym("turtle") && parsed->l_size >= 1) {
            cartesian_setturtle(x, parsed);
            if (x->turtled_grain)
                output_grain_contentfield(x, x->turtled_grain, gensym("turtle"), x->beat_sync);
            jbox_redraw((t_jbox *)x);
            
        } else if (router == gensym("getturtle")) {
            if (x->turtled_grain)
                output_grain_contentfield(x, x->turtled_grain, gensym("turtle"), x->beat_sync);

        } else if (router == gensym("turtledelta") && parsed->l_size >= 1 && hatom_gettype(&parsed->l_head->l_hatom) == H_LLLL) {
            // move in a manner similar to the "turtle" programming language
            t_pt delta = llll_to_pt(hatom_getllll(&parsed->l_head->l_hatom));
            t_pt previous = x->turtled_grain ? x->turtled_grain->coord : build_pt(0, 0);
            if (x->turtled_grain && x->relative_turtling) {
                previous = build_pt((x->turtled_grain->coord.x - x->domain_min)/(x->domain_max - x->domain_min), (x->turtled_grain->coord.y - x->range_min)/(x->range_max - x->range_min));
            }
            char has_weights = false;
            t_pt weights;
            if (parsed->l_head->l_next && hatom_gettype(&parsed->l_head->l_next->l_hatom) == H_LLLL) {
                has_weights = true;
                weights = llll_to_pt(hatom_getllll(&parsed->l_head->l_next->l_hatom));
            }
            if ((x->turtled_grain = cartesian_get_1nn(x, pt_pt_sum(previous, delta), has_weights ? &weights : NULL, x->turtled_grain, x->relative_turtling)))
                output_grain_contentfield(x, x->turtled_grain, gensym("turtle"), x->beat_sync);
            jbox_redraw((t_jbox *)x);
        }
    }
    llll_free(parsed);
}

void clear_grains(t_cartesian *x)
{
    t_llllelem *elem;
	for (elem = x->grains->l_head; elem; elem = elem->l_next)
		bach_freeptr(hatom_getobj(&elem->l_hatom));
	llll_clear(x->grains);
	x->mousehover_grain = x->mousedown_grain = x->lastplayed_grain = NULL;
}




void convexcomb_to_xy(double *val, long num_vals, double *xv, double *yv, double norm)
{
    normalize_array(val, num_vals, norm);
    
    // vertex i has coordinates (cos(2pi/num_vals), sin(2pi/num_vals))
    long i;
    *xv = *yv = 0;
    for (i = 0; i < num_vals; i++) {
        *xv += val[i] * cos(i * TWOPI/num_vals);
        *yv += val[i] * sin(i * TWOPI/num_vals);
    }
}


long build_grains(t_cartesian *x)
{
    long num_output_grains = 0;
    
    if (!x->d_database || strlen(x->d_database->s_name) <= 0 || !x->tablename || strlen(x->tablename->s_name) <= 0) {
//        object_error((t_object *)x, "Define a valid database and table name.");
        if (!x->d_database || strlen(x->d_database->s_name) <= 0)
            x->db_ok = false;
        return 0; // nothing to build
    }

    if (!x->field_x || strlen(x->field_x->s_name) <= 0 || !x->field_y || strlen(x->field_y->s_name) <= 0 || x->field_x == _sym_none || x->field_y == _sym_none) {
//        object_error((t_object *)x, "Define valid 'xfield' and 'yfield' attributes.");
        return 0;
    }
	
	
	// QUERY:
	t_max_err	err = MAX_ERR_NONE;
	t_db_result	*result = NULL;
	
	t_symbol *tablename = x->tablename;
	t_symbol *xfield = x->field_x;
	t_symbol *yfield = x->field_y;
	t_symbol *colorfield = x->field_color;
	t_symbol *sizefield = x->field_size;
	t_symbol *shapefield = x->field_shape;
    t_symbol *bpmfield = x->field_bpm; //x->beat_sync ? x->field_bpm : NULL;
    t_symbol *phasefield = x->field_phase; // x->beat_sync ? x->field_phase : NULL;
    t_symbol *lengthfield = x->field_length;
	char colorfield_dummy = false, sizefield_dummy = false, shapefield_dummy = false, bpmfield_dummy = false, phasefield_dummy = false, lengthfield_dummy = false;
	t_symbol *idname = table_name_to_idname(tablename);
	long i;
	long numrecords, numfields;

	x->field_x_is_string = x->field_y_is_string = x->field_color_is_string = x->field_size_is_string = x->field_shape_is_string = false;
	x->field_color_is_dummy = x->field_size_is_dummy = x->field_shape_is_dummy = x->field_bpm_is_dummy = x->field_phase_is_dummy = x->field_length_is_dummy = false;
	
	
	//// 1. FIND IF THERE'S ANY DUMMY FIELD
	
	
	if (!colorfield || strlen(colorfield->s_name) == 0 || colorfield == _sym_none) {
		colorfield = idname;
		x->field_color_is_dummy = colorfield_dummy = true;
	}
	
	if (!sizefield || strlen(sizefield->s_name) == 0 || sizefield == _sym_none) {
		sizefield = idname;
		x->field_size_is_dummy = sizefield_dummy = true;
	}	

	if (!shapefield || strlen(shapefield->s_name) == 0 || shapefield == _sym_none) {
		shapefield = idname;
		x->field_shape_is_dummy = shapefield_dummy = true;
	}

	if (!bpmfield || strlen(bpmfield->s_name) == 0 || bpmfield == _sym_none) {
		bpmfield = idname;
		x->field_bpm_is_dummy = bpmfield_dummy = true;
	}

	if (!phasefield || strlen(phasefield->s_name) == 0 || phasefield == _sym_none) {
		phasefield = idname;
		x->field_phase_is_dummy = phasefield_dummy = true;
	}

    if (!lengthfield || strlen(lengthfield->s_name) == 0 || lengthfield == _sym_none) {
        lengthfield = idname;
        x->field_length_is_dummy = lengthfield_dummy = true;
    }

    
	//// 2. FIND IF THERE IS ANY STRING-TYPED FIELD
	
	char typequery[512];
	char *r;
	t_symbol **field_color_unique_sym = NULL;
	long field_color_unique_sym_size = 0;
	t_symbol **field_size_unique_sym = NULL;
	long field_size_unique_sym_size = 0;
	t_symbol **field_shape_unique_sym = NULL;
	long field_shape_unique_sym_size = 0;
	t_symbol **field_x_unique_sym = NULL;
	long field_x_unique_sym_size = 0;
	t_symbol **field_y_unique_sym = NULL;
	long field_y_unique_sym_size = 0;

	snprintf_zero(typequery, 512, "SELECT typeof(MIN(%s)) FROM %s", xfield->s_name, tablename->s_name);
	if (strlen(xfield->s_name) > 0 && db_query(x->d_db, &result, typequery) == MAX_ERR_NONE) {
		r = db_result_string(result, 0, 0); // not sure if I have to free this (Max API examples did not)
		if (r && strcmp(r, "text") == 0) {
			x->field_x_is_string = true;

			// ... and if yes, build up a table 
			snprintf_zero(typequery, 512, "SELECT DISTINCT %s FROM %s", xfield->s_name, tablename->s_name);
			db_query(x->d_db, &result, typequery);
			field_x_unique_sym_size = numrecords = db_result_numrecords(result);
			field_x_unique_sym = (t_symbol **)bach_newptr(numrecords * sizeof(t_symbol *));
            i = 0;
            for (char **record = db_result_firstrecord(result); i < numrecords && record; record = db_result_nextrecord(result), i++)
                field_x_unique_sym[i] = gensym(record[0]);
		}
        object_free(result);
        result = NULL;
	}
    
	
	snprintf_zero(typequery, 512, "SELECT typeof(MIN(%s)) FROM %s", yfield->s_name, tablename->s_name);
	if (strlen(yfield->s_name) > 0 && db_query(x->d_db, &result, typequery) == MAX_ERR_NONE) {
		r = db_result_string(result, 0, 0); // not sure if I have to free this
		if (r && strcmp(r, "text") == 0) {
			x->field_y_is_string = true;

			// ... and if yes, build up a table 
			snprintf_zero(typequery, 512, "SELECT DISTINCT %s FROM %s", yfield->s_name, tablename->s_name);
			db_query(x->d_db, &result, typequery);
			field_y_unique_sym_size = numrecords = db_result_numrecords(result);
			field_y_unique_sym = (t_symbol **)bach_newptr(numrecords * sizeof(t_symbol *));
            i = 0;
            for (char **record = db_result_firstrecord(result); i < numrecords && record; record = db_result_nextrecord(result), i++)
                field_y_unique_sym[i] = gensym(record[0]);

		}
        object_free(result);
        result = NULL;
	}

	snprintf_zero(typequery, 512, "SELECT typeof(MIN(%s)) FROM %s", sizefield->s_name, tablename->s_name);
	if (strlen(sizefield->s_name) > 0 && db_query(x->d_db, &result, typequery) == MAX_ERR_NONE) {
		r = db_result_string(result, 0, 0); // not sure if I have to free this
		if (r && strcmp(r, "text") == 0)  {
			x->field_size_is_string = true;

			// ... and if yes, build up a table 
			snprintf_zero(typequery, 512, "SELECT DISTINCT %s FROM %s", sizefield->s_name, tablename->s_name);
			db_query(x->d_db, &result, typequery);
			field_size_unique_sym_size = numrecords = db_result_numrecords(result);
			field_size_unique_sym = (t_symbol **)bach_newptr(numrecords * sizeof(t_symbol *));
            i = 0;
            for (char **record = db_result_firstrecord(result); i < numrecords && record; record = db_result_nextrecord(result), i++)
                field_size_unique_sym[i] = gensym(record[0]);
		}
        object_free(result);
        result = NULL;
	}
	
	snprintf_zero(typequery, 512, "SELECT typeof(MIN(%s)) FROM %s", colorfield->s_name, tablename->s_name);
	if (strlen(colorfield->s_name) > 0 && db_query(x->d_db, &result, typequery) == MAX_ERR_NONE) {
		r = db_result_string(result, 0, 0); // not sure if I have to free this
		if (r && strcmp(r, "text") == 0)  {
			x->field_color_is_string = true;
			
			// ... and if yes, build up a table 
			snprintf_zero(typequery, 512, "SELECT DISTINCT %s FROM %s", colorfield->s_name, tablename->s_name);
			db_query(x->d_db, &result, typequery);
			field_color_unique_sym_size = numrecords = db_result_numrecords(result);
			field_color_unique_sym = (t_symbol **)bach_newptr(numrecords * sizeof(t_symbol *));
            i = 0;
            for (char **record = db_result_firstrecord(result); i < numrecords && record; record = db_result_nextrecord(result), i++)
                field_color_unique_sym[i] = gensym(record[0]);
		}
        object_free(result);
        result = NULL;
	}
	

	snprintf_zero(typequery, 512, "SELECT typeof(MIN(%s)) FROM %s", shapefield->s_name, tablename->s_name);
	if (strlen(shapefield->s_name) > 0 && db_query(x->d_db, &result, typequery) == MAX_ERR_NONE) {
		r = db_result_string(result, 0, 0); // not sure if I have to free this
		if (r && strcmp(r, "text") == 0)  {
			x->field_shape_is_string = true;
			
			// ... and if yes, build up a table 
			snprintf_zero(typequery, 512, "SELECT DISTINCT %s FROM %s", shapefield->s_name, tablename->s_name);
			db_query(x->d_db, &result, typequery);
			field_shape_unique_sym_size = numrecords = db_result_numrecords(result);
			field_shape_unique_sym = (t_symbol **)bach_newptr(numrecords * sizeof(t_symbol *));
            i = 0;
            for (char **record = db_result_firstrecord(result); i < numrecords && record; record = db_result_nextrecord(result), i++)
                field_shape_unique_sym[i] = gensym(record[0]);
		}
        object_free(result);
        result = NULL;
	}
	
	
	//// 3. FIND MIN/MAX for size and color
	
	double min_field_size = 0, max_field_size = 1;
	double min_field_color = 0, max_field_color = 1;
	

	if (!sizefield_dummy) {
		if (x->field_size_is_string) {
			min_field_size = 0; 
			max_field_size = field_size_unique_sym_size - 1;
		} else {
			// obtain min and max of sizefield
			char minquery[512];
			char maxquery[512];
			snprintf_zero(minquery, 1024, "SELECT MIN(%s) FROM %s", sizefield->s_name, tablename->s_name);
			snprintf_zero(maxquery, 1024, "SELECT MAX(%s) FROM %s", sizefield->s_name, tablename->s_name);
			if (db_query(x->d_db, &result, minquery) == MAX_ERR_NONE) 
				min_field_size = db_result_double_local(result, 0, 0);
            object_free(result);
            result = NULL;
			if (db_query(x->d_db, &result, maxquery) == MAX_ERR_NONE)
				max_field_size = db_result_double_local(result, 0, 0);
            object_free(result);
            result = NULL;
		}
	}

	
	if (!colorfield_dummy) {
		if (x->field_color_is_string) {
			min_field_color = 0; 
			max_field_color = field_color_unique_sym_size - 1;
		} else {
			// obtain min and max of colorfield
			char minquery[512];
			char maxquery[512];
			snprintf_zero(minquery, 1024, "SELECT MIN(%s) FROM %s", colorfield->s_name, tablename->s_name);
			snprintf_zero(maxquery, 1024, "SELECT MAX(%s) FROM %s", colorfield->s_name, tablename->s_name);
			if (db_query(x->d_db, &result, minquery) == MAX_ERR_NONE) 
				min_field_color = db_result_double_local(result, 0, 0);
            object_free(result);
            result = NULL;
			if (db_query(x->d_db, &result, maxquery) == MAX_ERR_NONE)
				max_field_color = db_result_double_local(result, 0, 0);
            object_free(result);
            result = NULL;
		}
	}
	
    long colorfield_idx = 3;
    
    char *query = NULL;
    long query_alloc = DADA_QUERY_ALLOC_CHAR_SIZE;
    char *where = NULL;

    if (x->d_where_llll->l_size > 0) {
        query_alloc += llll_to_text_buf(x->d_where_llll, &where, 0, BACH_DEFAULT_MAXDECIMALS, LLLL_T_NONE, LLLL_TE_NONE, LLLL_TB_NONE, NULL);
    }
    
    query = (char *)sysmem_newptr(query_alloc * sizeof(char));

    if (x->mode == DADA_CARTESIAN_MODE_CARTESIAN) {
        snprintf_zero(query, query_alloc, "SELECT %s,%s,%s,%s,%s,%s,%s,%s,%s FROM %s",
                      idname->s_name, xfield->s_name, yfield->s_name, colorfield->s_name, sizefield->s_name, shapefield->s_name, bpmfield->s_name, phasefield->s_name, lengthfield->s_name, tablename->s_name);
    } else {
        long i;
        snprintf_zero(query, query_alloc, "SELECT %s,", idname->s_name);
        for (i = 0; i < x->field_convexcomb_size; i++)
            snprintf_zero(query + strlen(query), query_alloc - strlen(query), "%s,", x->field_convexcomb[i] ? x->field_convexcomb[i]->s_name : "none");
        snprintf_zero(query + strlen(query), query_alloc - strlen(query), "%s,%s,%s,%s,%s,%s FROM %s", colorfield->s_name, sizefield->s_name, shapefield->s_name, bpmfield->s_name, phasefield->s_name, lengthfield->s_name, tablename->s_name);
        colorfield_idx = x->field_convexcomb_size+1;
    }

    if (where) {
        snprintf_zero(query + strlen(query), query_alloc - strlen(query), " WHERE %s", where);
        sysmem_freeptr(where);
    }

	err = db_query(x->d_db, &result, query);
    
    sysmem_freeptr(query);
	
	
	if (err)
		object_error((t_object *)x, "Error while executing query!");
	
	numrecords = db_result_numrecords(result);
	numfields = db_result_numfields_local(result);
	
    num_output_grains = 0;
	if (numfields >= 8) {
        i = 0;
        for (char **record = db_result_firstrecord(result); i < numrecords; record = db_result_nextrecord(result), i++) {
            
            if (!record) continue;
            
			// add grain
			t_cartesian_grain *gr = (t_cartesian_grain *)bach_newptr(sizeof(t_cartesian_grain));
			double val_x, val_y, val_col, val_size, val_shape;
            num_output_grains++;
			
            if (x->mode == DADA_CARTESIAN_MODE_CARTESIAN) {
                if (x->field_x_is_string) {
                    atom_setsym(&gr->field_x, gensym(record[1]));
                    val_x = find_symbol_in_symbol_array(gr->field_x.a_w.w_sym, field_x_unique_sym, field_x_unique_sym_size);
                } else {
                    val_x = atof(record[1]);
                    atom_setfloat(&gr->field_x, val_x);
                }
                
                if (x->field_y_is_string) {
                    atom_setsym(&gr->field_y, gensym(record[2]));
                    val_y = find_symbol_in_symbol_array(gr->field_y.a_w.w_sym, field_y_unique_sym, field_y_unique_sym_size);
                } else {
                    val_y = atof(record[2]);
                    atom_setfloat(&gr->field_y, val_y);
                }
            } else {
                // convex combination
                long j;
                double res[DADA_CARTESIAN_MAX_CONVEXCOMB];
                for (j = 0; j < x->field_convexcomb_size; j++) {
                    if (x->field_convexcomb_max[j] > x->field_convexcomb_min[j])
                        res[j] = CLAMP(atof(record[1+j]), x->field_convexcomb_min[j], x->field_convexcomb_max[j]);
                    else
                        res[j] = 0;
                }
                convexcomb_to_xy(res, x->field_convexcomb_size, &val_x, &val_y, is_atom_number(&x->field_convexcomb_norm) ? atom_getfloat(&x->field_convexcomb_norm) : -1);
            }

			if (x->field_color_is_string) {
                atom_setsym(&gr->field_color, gensym(record[colorfield_idx]));
                val_col = find_symbol_in_symbol_array(gr->field_color.a_w.w_sym, field_color_unique_sym, field_color_unique_sym_size);
			} else {
				val_col = atof(record[colorfield_idx]);
				atom_setfloat(&gr->field_color, val_col);
			}
			
			if (x->field_size_is_string) {
				atom_setsym(&gr->field_size, gensym(record[colorfield_idx+1]));
				val_size = find_symbol_in_symbol_array(gr->field_size.a_w.w_sym, field_size_unique_sym, field_size_unique_sym_size); 
			} else {
                val_size = atof(record[colorfield_idx+1]);
				atom_setfloat(&gr->field_size, val_size);
			}
			
			if (x->field_shape_is_string) {
				atom_setsym(&gr->field_shape, gensym(record[colorfield_idx+2]));
				val_shape = find_symbol_in_symbol_array(gr->field_shape.a_w.w_sym, field_shape_unique_sym, field_shape_unique_sym_size); 
			} else {
                val_shape = atof(record[colorfield_idx+2]);
				atom_setfloat(&gr->field_shape, val_shape);
			}		
			
			gr->result_idx = i;
            gr->db_id = atol(record[0]);
			gr->coord = build_pt(val_x, val_y);
			gr->radius_px = sizefield_dummy ? x->minradius : (min_field_size == max_field_size ? x->minradius : rescale(val_size, min_field_size, max_field_size, x->minradius, x->maxradius));
			gr->color = colorfield_dummy ? x->j_graincolor : double_to_color(CLAMP(val_col, min_field_color, max_field_color), min_field_color, max_field_color, false);
			gr->color.alpha = x->point_alpha/100.;
			gr->parent = llll_appendobj(x->grains, gr, 0, WHITENULL_llll);
			gr->shape = shapefield_dummy ? 0 : val_shape;
			
			gr->bpm = bpmfield_dummy ? 60. : atof(record[colorfield_idx+3]);
            gr->phase = phasefield_dummy ? 0. : atof(record[colorfield_idx+4]);
            gr->length_ms = lengthfield_dummy ? 0. :atof(record[colorfield_idx+5]);
		}
	}
	
    object_free(result);
	
	if (field_x_unique_sym)
		bach_freeptr(field_x_unique_sym);
	if (field_y_unique_sym)
		bach_freeptr(field_y_unique_sym);
	if (field_color_unique_sym)
		bach_freeptr(field_color_unique_sym);
	if (field_size_unique_sym)
		bach_freeptr(field_size_unique_sym);
	if (field_shape_unique_sym)
		bach_freeptr(field_shape_unique_sym);

    return num_output_grains;
}


void rebuild_grains(t_cartesian *x, char preserve_turtle)
{
    dadaobj_mutex_lock(dadaobj_cast(x));
    // preserve turtle?
    long db_ID = x->turtled_grain ? x->turtled_grain->db_id : -1;
    long num_grains = 0;
    
    clear_grains(x);
    num_grains = build_grains(x);
    x->turtled_grain = NULL;
    if (preserve_turtle && db_ID >= 0) {
        t_llllelem *elem;
        for (elem = x->grains->l_head; elem; elem = elem->l_next) {
            t_cartesian_grain *gr = (t_cartesian_grain *)hatom_getobj(&elem->l_hatom);
            if (gr->db_id == db_ID) {
                x->turtled_grain = gr;
                break;
            }
        }
    }
    x->need_rebuild_grains = false;
    if (x->autozoom)
        dadaobj_cast(x)->m_zoom.must_autozoom = true;
    dadaobj_mutex_unlock(dadaobj_cast(x));
    llllobj_outlet_symbol_as_llll((t_object *)x, LLLL_OBJ_UI, 2, _sym_done);
    
    t_llll *numgrains_ll = llll_get();
    llll_appendsym(numgrains_ll, gensym("numgrains"));
    llll_appendlong(numgrains_ll, num_grains);
    llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 2, numgrains_ll);
}


void rebuild_grains_defer_low_do(t_cartesian *x, t_symbol *msg, long ac, t_atom *av)
{
    rebuild_grains(x, ac ? atom_getlong(av) : 0);
}

void rebuild_grains_defer_low(t_cartesian *x, char preserve_turtle)
{
    t_atom av;
    atom_setlong(&av, preserve_turtle);
    defer_low(x, (method)rebuild_grains_defer_low_do, NULL, 1, &av);
}



//// GRAPHIC DRAWING
void cartesian_paint_grains(t_cartesian *x, t_jgraphics *g, t_object *view, t_rect rect, t_pt center, t_dada_force_graphics *force_graphics)
{
	
	char use_layers = false;

	if (!g) {
 		use_layers = true;
        g = view ? jbox_start_layer((t_object *)x, view, gensym("grains"), rect.width, rect.height) : force_graphics->graphic_context;
	}
	
	if (g){
//        post("painting");
		
		t_llllelem *elem;
		for (elem = x->grains->l_head; elem; elem = elem->l_next) {
			t_cartesian_grain *gr = (t_cartesian_grain *)hatom_getobj(&elem->l_hatom);
			t_pt pt = coord_to_pix(dadaobj_cast(x), center, gr->coord);
            
            if (pt.x + gr->radius_px >= 0 && pt.x - gr->radius_px <= rect.width &&
                pt.y + gr->radius_px >= 0 && pt.y - gr->radius_px <= rect.height) {
                if (gr->shape <= 0)
                    paint_circle_filled(g, gr->color, pt.x, pt.y, gr->radius_px);
                else
                    paint_regular_polygon(g, gr->shape + 2, NULL, &gr->color, pt, gr->radius_px, 1);
            }
			
		}
		
		if (use_layers && view)
			jbox_end_layer((t_object *)x, view, gensym("grains"));
	}
	
	if (use_layers && view)
		jbox_paint_layer((t_object *)x, view, gensym("grains"), 0., 0.);	// position of the layer
}


char *cartesian_atom_to_string(t_atom *a, long max_decimals)
{
    if (!a) {
        char *res = (char *)bach_newptr(1 * sizeof(char));
        res[0] = 0;
        return res;
    }
	if (atom_gettype(a) == A_SYM) {
        long len = strlen(atom_getsym(a)->s_name);
        char *res = (char *)bach_newptr((len + 1) * sizeof(char));
        sysmem_copyptr(atom_getsym(a)->s_name, res, len * sizeof(char));
        res[len] = 0;
		return res;
	} else {
		char *res = double_to_string(atom_getfloat(a), max_decimals);
		if (res[strlen(res)-1] == ' ')
			res[strlen(res)-1] = 0;
		if (res[strlen(res)-1] == '.')
			res[strlen(res)-1] = 0;
		return res;
	}
}

void cartesian_paint_ext(t_cartesian *x, t_object *view, t_dada_force_graphics *force_graphics)
{
    t_jgraphics *g = force_graphics->graphic_context;
	t_rect rect = force_graphics->rect;
	t_pt center = force_graphics->center_pix;
	t_jfont *jf = jfont_create_debug("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, x->legend_text_size);


    if (!x->db_ok) {
        dadaobj_paint_background(dadaobj_cast(x), g, &rect);
        write_text(g, jf, DADA_GREY_50, "(must set 'database' and 'table' attributes)", 0, 0, rect.width, rect.height, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, true, true);
        return;
    } else if (!x->tablename || strlen(x->tablename->s_name) == 0) {
        dadaobj_paint_background(dadaobj_cast(x), g, &rect);
        write_text(g, jf, DADA_GREY_50, "(must set 'table' attribute)", 0, 0, rect.width, rect.height, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, true, true);
        return;
    } else if (!x->field_x || strlen(x->field_x->s_name) <= 0 || !x->field_y || strlen(x->field_y->s_name) <= 0 || x->field_x == _sym_none || x->field_y == _sym_none) {
        dadaobj_paint_background(dadaobj_cast(x), g, &rect);
        write_text(g, jf, DADA_GREY_50, "(must set both 'xfield' and 'yfield' attributes)", 0, 0, rect.width, rect.height, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, true, true);
        return;
    }

    
    
    // getting rectangle dimensions
    dadaobj_getdomain(dadaobj_cast(x), view, &x->domain_min, &x->domain_max, force_graphics);
    dadaobj_getrange(dadaobj_cast(x), view, &x->range_min, &x->range_max, force_graphics);

    dadaobj_paint_background(dadaobj_cast(x), g, &rect);

    dadaobj_mutex_lock(dadaobj_cast(x));

    dadaobj_paint_grid(dadaobj_cast(x), view, force_graphics); // axis are inside here

	// grains
	cartesian_paint_grains(x, g, view, rect, center, force_graphics);
	
    // painting turtle, if any
    if (x->show_turtle && x->turtled_grain) {
        t_pt pt = coord_to_pix(dadaobj_cast(x), center, x->turtled_grain->coord);
        paint_hexagon(g, &x->j_turtlecolor, NULL, pt, x->turtled_grain->radius_px + 4, 2, true);
    }
    
    if (x->mode == DADA_CARTESIAN_MODE_CONVEXCOMB) {
        t_jrgba polycolor = DADA_GREY_50;
        long i, n = x->field_convexcomb_size;
        t_pt verts[DADA_CARTESIAN_MAX_CONVEXCOMB];
        for (i = 0; i < n; i++)
            verts[i] = coord_to_pix(dadaobj_cast(x), center, build_pt(cos(i * TWOPI/n), sin(i * TWOPI/n)));

        double dashes[2];
        dashes[0] = 10; dashes[1] = 5;
        jgraphics_set_dash(g, dashes, 2, 0);
        jgraphics_set_line_width(g, 1.);
        jgraphics_set_source_jrgba(g, &polycolor);
        jgraphics_move_to(g, verts[0].x, verts[0].y);
        for (i = 0; i < n; i++) {
            jgraphics_line_to(g, verts[i].x, verts[i].y);
        }
        jgraphics_close_path(g);
        jgraphics_stroke(g);
        jgraphics_set_dash(g, NULL, 0, 0);
        
        for (i = 0; i < n; i++) {
            paint_square(g, &polycolor, &polycolor, verts[i], 2, 0);
            write_text_standard(g, jf, polycolor, x->field_convexcomb[i] ? x->field_convexcomb[i]->s_name : "none", verts[i].x + 4, verts[i].y - 4, 200, 200);
        }
    }
    
	// painting mousehover, if any
	if (x->mousehover_grain) {
		t_pt pt = coord_to_pix(dadaobj_cast(x), center, x->mousehover_grain->coord);
//		post("%.2f, %.2f", x->mousehover_grain->coord.x, x->mousehover_grain->coord.y);
		paint_circle_stroken(g, DADA_BLACK, pt.x, pt.y, x->mousehover_grain->radius_px + DADA_CARTESIAN_INTERFACE_GRAIN_TOLERANCE, 1);
		
		if (x->show_legend) {
			char legend[1024];
            if (x->mode == DADA_CARTESIAN_MODE_CARTESIAN) {
                char *str_x = cartesian_atom_to_string(&x->mousehover_grain->field_x, 2), *str_y = cartesian_atom_to_string(&x->mousehover_grain->field_y, 2);
                snprintf_zero(legend, 1024, "ID %ld, %s %s, %s %s", x->mousehover_grain->db_id, x->field_x->s_name, str_x, x->field_y->s_name, str_y);
                bach_freeptr(str_x);
                bach_freeptr(str_y);
            } else
                snprintf_zero(legend, 1024, "ID %ld", x->mousehover_grain->db_id);
			
            if (!x->field_size_is_dummy) {
				char *str_size = cartesian_atom_to_string(&x->mousehover_grain->field_size, 2);
				snprintf_zero(legend + strlen(legend), 1024 - strlen(legend), ", %s %s", x->field_size->s_name, str_size);
				bach_freeptr(str_size);
			}
			if (!x->field_color_is_dummy) {
				char *str_color = cartesian_atom_to_string(&x->mousehover_grain->field_color, 2);
				snprintf_zero(legend + strlen(legend), 1024 - strlen(legend), ", %s %s", x->field_color->s_name, str_color);
				bach_freeptr(str_color);
			}
			if (!x->field_shape_is_dummy) {
				char *str_shape = cartesian_atom_to_string(&x->mousehover_grain->field_shape, 2);
				snprintf_zero(legend + strlen(legend), 1024 - strlen(legend), ", %s %s", x->field_shape->s_name, str_shape);
				bach_freeptr(str_shape);
			}
			write_text(g, jf, x->j_legendcolor, legend, 5, 5, rect.width - 10, rect.height - 10, JGRAPHICS_TEXT_JUSTIFICATION_RIGHT | JGRAPHICS_TEXT_JUSTIFICATION_TOP, true, true);
		}
	}
	
    dadaobj_mutex_unlock(dadaobj_cast(x));

    dadaobj_paint_border(dadaobj_cast(x), g, &rect);

	jfont_destroy(jf);
}


void cartesian_paint(t_cartesian *x, t_object *view)
{
    if (x->need_rebuild_grains) {
        rebuild_grains(x, true);
    }
    
    if (view && dadaobj_cast(x)->m_zoom.must_autozoom) {
        cartesian_autozoom_do(x, view);
        dadaobj_cast(x)->m_zoom.must_autozoom = false;
    }

    dadaobj_paint(dadaobj_cast(x), view);
}


void cartesian_autozoom_do(t_cartesian *x, t_object *view)
{
	t_rect rect;
	
	jbox_get_rect_for_view((t_object *)x, view, &rect);
//	center = get_center_pix(dadaobj_cast(x), view, &rect);

	
	if (!x->grains || !x->grains->l_head)
		return;
	
	systhread_mutex_lock(x->b_ob.d_ob.l_mutex);

	// Initialize
	t_cartesian_grain *gr = (t_cartesian_grain *)hatom_getobj(&x->grains->l_head->l_hatom);
	double max_x = gr->coord.x, min_x = gr->coord.x, max_y = gr->coord.y, min_y = gr->coord.y;

	
    if (x->mode == DADA_CARTESIAN_MODE_CARTESIAN) {
        t_llllelem *elem;
        for (elem = x->grains->l_head->l_next; elem; elem = elem->l_next) {
            t_cartesian_grain *gr = (t_cartesian_grain *)hatom_getobj(&elem->l_hatom);
            if (gr->coord.x > max_x)
                max_x = gr->coord.x;
            if (gr->coord.y > max_y)
                max_y = gr->coord.y;
            if (gr->coord.x < min_x)
                min_x = gr->coord.x;
            if (gr->coord.y < min_y)
                min_y = gr->coord.y;
        }
        
        if (max_x == min_x) {
            max_x -= 0.5;
            min_x += 0.5;
        }
        if (max_y == min_y) {
            max_y -= 0.5;
            min_y += 0.5;
        }
    } else {
        max_x = max_y = 1.;
        min_x = min_y = -1.;
    }
    
    // adding pads
    max_x += (max_x - min_x) * 0.05;
    min_x -= (max_x - min_x) * 0.05;
    max_y += (max_y - min_y) * 0.05;
    min_y -= (max_y - min_y) * 0.05;
	
	systhread_mutex_unlock(x->b_ob.d_ob.l_mutex);

    dadaobj_setdomain(dadaobj_cast(x), view, min_x, max_x);
    dadaobj_setrange(dadaobj_cast(x), view, min_y, max_y);
}



///////// POPUP MENU FUNCTIONS
/*

void popup_clear(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_cartesian *x = (t_cartesian *)d_ob->orig_obj;
	cartesian_clear(x, false);
}

void popup_evolve(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_cartesian *x = (t_cartesian *)d_ob->orig_obj;
	cartesian_bang(x);
}

void popup_random(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_cartesian *x = (t_cartesian *)d_ob->orig_obj;
	cartesian_random(x, hatom_getlong(&address->l_tail->l_hatom) == 3 ? 1 : 0, DADA_LIFE_DEFAULT_RANDOM_DENSITY, false) ;
}

void show_bg_popup_menu(t_cartesian *x, t_object *patcherview, t_pt pt, long modifiers)
{
	ezdisplay_popup_menu(dadaobj_cast(x), patcherview,
						 (char *)"Center View Reset Zoom Clear separator Next Generation separator (Random Configuration Uniform Gaussian)", 
						 "0 0 0 0 0 0 0", "", "", "", "", 
						 (void *)popup_center_view, (void *)popup_reset_zoom, (void *)popup_clear, NULL, (void *)popup_evolve, NULL, (void *)popup_random, WHITENULL);
}
*/

////////// INTERFACE FUNCTIONS


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

// returns the content field already cloned
t_llll *get_grain_contentfield(t_cartesian *x, t_cartesian_grain *gr)
{
	t_max_err	err = MAX_ERR_NONE;
	t_symbol *tablename = x->tablename;
	t_symbol *idname = table_name_to_idname(tablename);
	
	char query[8192];
    long f;
    t_llll *out = llll_get();
    
    for (f = 0; f < x->field_content_size; f++) {
        t_db_result	*result = NULL;
        snprintf_zero(query, 8192, "SELECT %s FROM %s WHERE %s = %ld", x->field_content[f]->s_name, tablename->s_name, idname->s_name, gr->db_id);
        err = db_query(x->d_db, &result, query);
        
        long type = cartesian_colname_to_coltype(x, tablename, x->field_content[f]);
        
        if (err)
            dev_post("Error while executing query!!!");
        //			object_error((t_object*)x, "Error while executing query.");
        
        long numrecords, numfields;
        numrecords = db_result_numrecords(result);
        numfields = db_result_numfields_local(result);
        
        t_llll *this_out = llll_get();
        llll_appendsym(this_out, x->field_content[f]);
        
        if (numrecords > 0 && numfields > 0) {
            switch (type) {
                case 's':
                    llll_appendsym(this_out, db_result_symbol_local(result, 0, 0));
                    break;
                    
                case 'i':
                    llll_appendlong(this_out, db_result_long_local(result, 0, 0));
                    break;
                    
                case 'f':
                    llll_appenddouble(this_out, db_result_double_local(result, 0, 0));
                    break;
                    
                default: // llll
                {
                    t_xbase *xbase = (t_xbase *)x->d_database->s_thing; // database already exists
                    if (xbase_store_lllls_with_phonenumbers(xbase)) {
                        long phonenumber = db_result_long_local(result, 0, 0);
                        t_llll *ll = llll_retrieve_from_phonenumber_and_retain(phonenumber);
                        if (ll) {
                            llll_chain_clone(this_out, ll);
                            llll_release(ll);
                        }
                    } else {
                        char **record = db_result_firstrecord(result);
                        t_llll *ll = llll_from_text_buf(record[0], false);
                        llll_chain(this_out, ll);
                        break;
                    }
                }
                    break;
            }
        }
        llll_appendllll(out, this_out);
        
        object_free(result);
    }
	return out;
}

void cartesian_loop_tick(t_cartesian *x)
{
    if (x->lastplayed_grain)
        output_grain_contentfield(x, x->lastplayed_grain, x->seq_router, 3);
    // schedule another metronome tick
//    clock_fdelay(x->m_clock, x->m_interval);
}

void cartesian_send_grain(t_cartesian *x, t_symbol *s, long argc, t_atom *argv)
{
    if (x->lastplayed_grain)
        output_grain_contentfield(x, x->lastplayed_grain, atom_getsym(argv), atom_getlong(argv+1));
}

void output_none_contentfield(t_cartesian *x, t_symbol *router)
{
    t_llll *ll = llll_get();
    llll_appendsym(ll, router, 0, WHITENULL_llll);
    llll_appendsym(ll, _sym_none, 0, WHITENULL_llll);
    llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, ll);
}

// mode = 0, MAIN THREAD; mode = 1: BEAT SYNC; mode = 2: SCHEDULER WITH DELAY = 0, mode = 3: SCHEDULED WITH DELAY > 0
void output_grain_contentfield(t_cartesian *x, t_cartesian_grain *gr, t_symbol *router, char mode)
{
    t_llll *out = gr ? get_grain_contentfield(x, gr) : symbol2llll(_llllobj_sym_none);
	
    if (out) {
        llll_prependsym(out, router, 0, WHITENULL_llll);
        x->lastplayed_grain = gr;
        
        setclock_unset(x->b_ob.d_ob.m_play.setclock->s_thing, x->loop_clock);
        
        switch (mode) {
            case 1:
                cartesian_schedule_interface_grain_llll(x, gr, out);
                break;
            case 2:
            {
                t_atom atom;
                atom_setobj(&atom, out);
                schedule_delay((t_object *)x, (method)do_send_llll, 0., NULL, 1, &atom);
            }
                break;
            default:
            {
                double this_time = systimer_gettime();
                if (this_time >= x->last_nonbeatsync_play_time + x->antibis_ms) {
                    x->last_nonbeatsync_play_time = this_time;
                    if (x->loop_last && x->lastplayed_grain) {
                        x->seq_router = _llllobj_sym_loop;
                        setclock_fdelay(x->b_ob.d_ob.m_play.setclock->s_thing, x->loop_clock, gr->length_ms);
                    }
                    llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, out);
                    llll_free(out);
                } else {
                    x->seq_router = router;
                    setclock_fdelay(x->b_ob.d_ob.m_play.setclock->s_thing, x->loop_clock, x->last_nonbeatsync_play_time + x->antibis_ms - this_time);
                }
            }
                break;
        }
    }
}


t_cartesian_grain *pix_to_grain(t_cartesian *x, t_pt center, t_pt pix)
{
	t_llllelem *elem;
	for (elem = x->grains->l_head; elem; elem = elem->l_next) {
		t_cartesian_grain *gr = (t_cartesian_grain *)hatom_getobj(&elem->l_hatom);
		t_pt pix1 = coord_to_pix(dadaobj_cast(x), center, gr->coord);
		double radius = gr->radius_px + DADA_CARTESIAN_INTERFACE_GRAIN_TOLERANCE;
		if (pt_pt_distance_squared(pix, pix1) < radius * radius)
			return gr; 
	}
	return NULL;
}

t_cartesian_grain *pix_to_grain_from_view(t_cartesian *x, t_object *patcherview, t_pt pix)
{
	t_rect rect;
	t_pt center;
	jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
	center = get_center_pix(dadaobj_cast(x), patcherview, &rect);
	
	return pix_to_grain(x, center, pix);
}

void cartesian_focusgained(t_cartesian *x, t_object *patcherview) {
	if (dadaobj_focusgained(dadaobj_cast(x), patcherview))
		return;
}

void cartesian_focuslost(t_cartesian *x, t_object *patcherview) {
	if (dadaobj_focuslost(dadaobj_cast(x), patcherview))
		return;
	dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
}
							 
void do_send_llll(t_cartesian *x, t_symbol *s, long ac, t_atom *av)
{
	t_llll *ll = (t_llll *) av[0].a_w.w_obj;
	llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, ll);
	llll_free(ll);
}
							 
							 
void cartesian_schedule_interface_grain_llll(t_cartesian *x, t_cartesian_grain *gr, t_llll *ll)
{
    if (!gr)
        return;
    
    dadaobj_mutex_lock(dadaobj_cast(x));
	double curr_beat_ms = gr->bpm > 0 ? 60000./gr->bpm : 1000.;
	double phase = positive_fmod(gr->phase, 1.);
	x->curr_beat_ms  = curr_beat_ms;
	
	t_atom atom;
	double anticipation_ms = (1 - phase) * curr_beat_ms;
	double this_clock_ms = 0;
	double delay = 0;
	
//    post("Scheduling grain %ld", gr->result_idx);
//    post("• Beat duration is %.2fms, phase is %.2f: needed %.2fms of anticipation", curr_beat_ms, phase, anticipation_ms);

    setclock_getftime(x->b_ob.d_ob.m_play.setclock->s_thing, &this_clock_ms);
    
    // chainging clock time to match new tempo
    setclock_unset(x->b_ob.d_ob.m_play.setclock->s_thing, x->b_ob.d_ob.m_play.m_clock);
    setclock_fdelay(x->b_ob.d_ob.m_play.setclock->s_thing, x->b_ob.d_ob.m_play.m_clock, x->curr_beat_ms - (this_clock_ms - x->last_beat_time));

//    post("• Current clock time: %.2fms, last beat time: %.2fms", this_clock_ms, x->last_beat_time);
	this_clock_ms -= x->last_beat_time;
	if (this_clock_ms > x->curr_beat_ms - anticipation_ms) // can't schedule for this beat, we'll do it for next one
		delay = (x->curr_beat_ms - anticipation_ms) - this_clock_ms + curr_beat_ms;
	else
		delay = (x->curr_beat_ms - anticipation_ms) - this_clock_ms;
    
    double sched_global_time = this_clock_ms + delay + x->last_beat_time;
    
    // 
	
    if (x->antibis_ms >= 0 && !is_double_in_llll_first_level_with_tolerance(x->scheduled_times, sched_global_time, x->antibis_ms)) {
        llll_appenddouble(x->scheduled_times, sched_global_time);
        
//        post("• Grain %ld scheduled for %.2fms", gr->result_idx, sched_global_time);
        
        atom_setobj(&atom, ll);
        schedule_fdelay((t_object *)x, (method)do_send_llll, delay, NULL, 1, &atom);
    } else {
//        post("• There's a grain already scheduled near %.2fms!", this_clock_ms + delay + x->last_beat_time);

    }
    
    dadaobj_mutex_unlock(dadaobj_cast(x));
}

void cartesian_mousemove(t_cartesian *x, t_object *patcherview, t_pt pt, long modifiers) {

	llll_format_modifiers(&modifiers, NULL);
	if (dadaobj_mousemove(dadaobj_cast(x), patcherview, pt, modifiers))
		return;

	t_cartesian_grain *new_mousehover_grain = NULL;
	if (x->b_ob.d_ob.m_interface.allow_mouse_hover) 
		 new_mousehover_grain = pix_to_grain_from_view(x, patcherview, pt);
	
//    post("x->mousehover_grain = %p, new_mousehover_grain = %p", x->mousehover_grain, new_mousehover_grain);
	if (new_mousehover_grain != x->mousehover_grain) {
		x->mousehover_grain = new_mousehover_grain;
		
        if (new_mousehover_grain) {
            output_grain_contentfield(x, new_mousehover_grain, gensym("hover"), x->beat_sync);
        } else {
            output_none_contentfield(x, gensym("hover"));

            if (x->interrupt_looping_when_not_hovering) {
                x->lastplayed_grain = NULL;
                setclock_unset(x->b_ob.d_ob.m_play.setclock->s_thing, x->loop_clock);
            }
		}
        
		jbox_redraw((t_jbox *)x);
	}

}


void cartesian_mousedown(t_cartesian *x, t_object *patcherview, t_pt pt, long modifiers){

	if (dadaobj_mousedown(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
	
	x->mousedown_grain = pix_to_grain_from_view(x, patcherview, pt);
	
	if (x->mousedown_grain) {
		output_grain_contentfield(x, x->mousedown_grain, gensym("click"), false);
		jbox_redraw((t_jbox *)x);
	}

	
/*	if (modifiers & ePopupMenu)
		show_bg_popup_menu(x, patcherview, pt, modifiers);
	else
		cartesian_mousedrag(x, patcherview, pt, modifiers);
*/
}

void cartesian_mouseup(t_cartesian *x, t_object *patcherview, t_pt pt, long modifiers){
	x->mousedown_grain = NULL;
	llll_format_modifiers(&modifiers, NULL);
	
	if (dadaobj_mouseup(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
}

void cartesian_mousedrag(t_cartesian *x, t_object *patcherview, t_pt pt, long modifiers){

	llll_format_modifiers(&modifiers, NULL);
	
	if (dadaobj_mousedrag(dadaobj_cast(x), patcherview, pt, modifiers))
		return;

/*	if (!modifiers || modifiers == eCommandKey) {
		t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), patcherview, pt);
		long pen_size = round(DADA_LIFE_PEN_SIZE / x->b_ob.d_ob.zoom.x);
		
		if (pen_size > 1) {
			long min_x, max_x, min_y, max_y, i, j;
			if (pen_size % 2) {
				min_x = round(coord.x) - ((pen_size - 1) / 2);
				min_y = round(coord.y) - ((pen_size - 1) / 2);
			} else {
				min_x = floor(coord.x) - (pen_size / 2 - 1);
				min_y = floor(coord.y) - (pen_size / 2 - 1);
			}
			max_x = min_x + pen_size - 1;
			max_y = min_y + pen_size - 1;
			for (i = min_x; i <= max_x; i++)
				for (j = min_y; j <= max_y; j++)
					cartesian_set_cell_from_mousedrag(x, i, j, modifiers);
		} else
			cartesian_set_cell_from_mousedrag(x, round(coord.x), round(coord.y), modifiers);
		
			jbox_invalidate_layer((t_object *)x, NULL, gensym("world"));
		jbox_redraw((t_jbox *)x);
	}
*/
}

long cartesian_keyup(t_cartesian *x, t_object *patcherview, long keycode, long modifiers, long textcharacter){
			
	llll_format_modifiers(&modifiers, &keycode);

	if (dadaobj_keyup(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
		return 1;
	
	return 0;
}

long cartesian_key(t_cartesian *x, t_object *patcherview, long keycode, long modifiers, long textcharacter){
	llll_format_modifiers(&modifiers, &keycode);
	
	if (dadaobj_key(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
		return 1;

	switch (keycode) {
		case JKEY_TAB:
			cartesian_autozoom_do(x, patcherview);
			return 1;
		default:
			break;
	} 
	return 0;
}

void cartesian_mousewheel(t_cartesian *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc){
	llll_format_modifiers(&modifiers, NULL);  
	
	if (dadaobj_mousewheel(dadaobj_cast(x), view, pt, modifiers, x_inc, y_inc)) {
		cartesian_iar(x);
		return;
	}
}

void cartesian_mouseenter(t_cartesian *x, t_object *patcherview, t_pt pt, long modifiers)
{
    if (x->interrupt_beatsync_on_mouseleave && x->beat_sync) {
        setclock_fdelay(x->b_ob.d_ob.m_play.setclock->s_thing, x->b_ob.d_ob.m_play.m_clock, 0);
    }

	if (dadaobj_mouseenter(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
}

void cartesian_mouseleave(t_cartesian *x, t_object *patcherview, t_pt pt, long modifiers)
{
    if (x->b_ob.d_ob.m_interface.allow_mouse_hover && x->mousehover_grain)
        output_none_contentfield(x, gensym("hover"));
    
	x->mousehover_grain = NULL;
    
    if (x->interrupt_looping_on_mouseleave) {
        x->lastplayed_grain = NULL;
        setclock_unset(x->b_ob.d_ob.m_play.setclock->s_thing, x->loop_clock);
    }
    if (x->interrupt_beatsync_on_mouseleave)
        setclock_unset(x->b_ob.d_ob.m_play.setclock->s_thing, x->b_ob.d_ob.m_play.m_clock);
	if (dadaobj_mouseleave(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
}



////////////////// UNDO HANDLING

/*
void cartesian_undo_postprocess(t_cartesian *x)
{
	jbox_invalidate_layer((t_object *)x, NULL, gensym("sampling_points"));
	process_change(x);
	jbox_redraw((t_jbox *)x);
}


void cartesian_undo_step_push_sampling_points(t_cartesian *x, t_symbol *operation)
{
	undo_add_interface_step(dadaobj_cast(x), DADA_FUNC_v_oX, (method)cartesian_set_sampling , NULL, DADA_FUNC_X_o, (method)cartesian_get_sampling, NULL, operation);
}
*/




