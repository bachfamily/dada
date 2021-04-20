/**
	@file
	dada.distances.c
	
	@name 
	dada.distances
	
	@realname 
	dada.distances

	@type
	object
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
	Distance-based representation of points
	
	@description
	2D interface representation of points via multidimensional scaling
	
	@discussion
	
	@category
	dada, dada interfaces, dada corpus-based tools, dada geometry

	@keywords
	distances, corpus, database, map, scaling, graph, exploration
	
	@seealso
	dada.base, dada.segment, dada.cartesian
	
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
#include "SimpleMatrix.h"
#include "dada.graphs.h"

#define DADA_DISTANCES_INTERFACE_GRAIN_TOLERANCE 5
#define DADA_DISTANCES_MAX_CONTENTFIELDS 10
#define DADA_DISTANCES_MAX_CONVEXCOMB 32

//////////////////////////// structures

enum {
	kOutletParameterNames = 0,
	kOutletParameterValues,
	kOutletPresetNames,
	kOutletPluginNames,
	kNumContolOutlets
};

typedef struct _distances_grain
{
	long		result_idx;
	long		db_id;
	t_pt		coord;
	double		radius_px;

    char        has_uniform_grid_coord;
    t_pt        uniform_grid_coord;
    
    long        graph_ID;

	t_atom		field_x;
	t_atom		field_y;
	t_atom		field_size;
	t_atom		field_color;
	t_atom		field_shape;
	
	t_jrgba		color;
	t_llllelem	*parent;
	long		shape;
	
    t_symbol    *label;
    
	// bpm info
	double		bpm;
	double		phase;
    double      length_ms;
    
    
    // private field
    double      prev_grid_activity;
    double      grid_activity;
} t_distances_grain;


typedef struct _distances 
{
	t_dadaobj_jbox	b_ob; // root object
	
	t_object	*d_dataview;	///< The dataview object
	t_hashtab	*d_columns;		///< The dataview columns:  column name -> column index
	t_object	*d_view;		///< The dbview object that we need to display in a dataview
	t_symbol	*d_query;		
    long        d_where_ac;
    t_atom      *d_where_av;
	t_symbol	*d_database;
    
	t_object	*d_db;			///< the actual database object

    
    smat::Matrix<double> *D;    ///< distance matrix
    long        random_seed;
    long        numiter;
	
	t_symbol	*tablename;
    t_symbol	*disttablename;

	t_symbol	*field_size;
	t_symbol	*field_color;
	t_symbol	*field_shape;
	
    t_symbol	*field_content[DADA_DISTANCES_MAX_CONTENTFIELDS];
    long        field_content_size;

    char		field_size_is_dummy;
	char		field_color_is_dummy;
	char		field_shape_is_dummy;
	char		field_size_is_string;
	char		field_color_is_string;
	char		field_shape_is_string;
	
	// notifications
	char		need_rebuild_grains;
	
	// behavior
	char		autozoom;
	
	// display
    t_jrgba         j_axiscolor;
	double			maxradius;
	double			minradius;
	char			show_legend;
	double			legend_text_size;
    double			labels_text_size;
	t_jrgba			j_legendcolor;
	char			show_turtle;
	t_jrgba			j_turtlecolor;
	char			show_grid;
	double			point_alpha;
    t_jrgba			j_edgecolor;
    char            show_edges;
    char            show_grains;
    t_jrgba         j_graincolor;
    
    char            paint_labels;
    double          max_dist_edge;
    double          align_to_uniform_grid;
    long            uniform_grid_size[2];
    double          uniform_grid_learning_rate;
    char            also_compute_uniform_grid;

	// beat synchronous processing
	char			beat_sync;
	double			last_beat_time;
	double			curr_beat_ms;
	t_symbol		*field_bpm;
	t_symbol		*field_phase;
    t_symbol		*field_length;
    t_symbol		*field_label;
	char			field_bpm_is_dummy;
	char			field_phase_is_dummy;
    char			field_length_is_dummy;
    char			field_label_is_dummy;
    
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
    t_distances_grain  *lastplayed_grain;
    t_symbol        *seq_router;

    void            *loop_clock;							///< The clock for the looping play (only used for non-beatsynchronous processing)


	// interface
	t_distances_grain	*mousehover_grain;
	t_distances_grain	*mousedown_grain;
	t_distances_grain	*turtled_grain;
    t_llll              *turtled_grain_history;
    t_atom              markov_avoid_repetition_memory;
    
	// points
	t_llll			*grains;
    t_llll          *grains_grid;  // points organized in the uniform grid
    t_dada_graph    graph;
    
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
} t_distances;


///////////////////////// function prototypes
//// standard set
void *distances_new(t_symbol *s, long argc, t_atom *argv);
void distances_free(t_distances *x);
void distances_assist(t_distances *x, void *b, long m, long a, char *s);

void distances_paint(t_distances *x, t_object *view);
void distances_paint_ext(t_distances *x, t_object *view, t_dada_force_graphics *force_graphics);

void distances_get_boundaries(t_distances *x, double *min_x, double *max_x, double *min_y, double *max_y);
void rebuild_grains(t_distances *x, char preserve_turtle);
void rebuild_grains_defer_low(t_distances *x, char preserve_turtle);

void distances_int(t_distances *x, t_atom_long num);
void distances_float(t_distances *x, double num);
void distances_anything(t_distances *x, t_symbol *msg, long ac, t_atom *av);
void distances_bang(t_distances *x);

// interface
void distances_focusgained(t_distances *x, t_object *patcherview);
void distances_focuslost(t_distances *x, t_object *patcherview);
void distances_mousedown(t_distances *x, t_object *patcherview, t_pt pt, long modifiers);
void distances_mousemove(t_distances *x, t_object *patcherview, t_pt pt, long modifiers);
void distances_mouseup(t_distances *x, t_object *patcherview, t_pt pt, long modifiers);
void distances_mousedrag(t_distances *x, t_object *patcherview, t_pt pt, long modifiers);
long distances_key(t_distances *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
long distances_keyup(t_distances *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
void distances_mousewheel(t_distances *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc);	
void distances_mouseleave(t_distances *x, t_object *patcherview, t_pt pt, long modifiers); 
void distances_mouseenter(t_distances *x, t_object *patcherview, t_pt pt, long modifiers);
t_max_err distances_notify(t_distances *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

void distances_dump(t_distances *x);
void distances_clock(t_distances *x, t_symbol *s);
void distances_autozoom(t_distances *x);
void distances_autozoom_do(t_distances *x, t_object *view);
void distances_initdataview(t_distances *x);

t_max_err distances_set_query(t_distances *x, void *attr, long argc, t_atom *argv);
t_max_err distances_set_database(t_distances *x, void *attr, long argc, t_atom *argv);
t_max_err distances_set_where(t_distances *x, void *attr, long argc, t_atom *argv);
t_max_err distances_set_uniform(t_distances *x, void *attr, long argc, t_atom *argv);
t_max_err distances_set_uniformpar(t_distances *x, void *attr, long argc, t_atom *argv);

t_llll *get_grain_contentfield(t_distances *x, t_distances_grain *gr);
void output_grain_contentfield(t_distances *x, t_distances_grain *gr, t_symbol *router, char beat_sync);
void distances_loop_tick(t_distances *x);
void distances_schedule_interface_grain_llll(t_distances *x, t_distances_grain *gr, t_llll *ll);
void do_send_llll(t_distances *x, t_symbol *s, long ac, t_atom *av);

t_pt distances_get_grain_pt(t_distances *x, t_pt center, t_distances_grain *gr);
t_pt distances_get_grain_coord(t_distances *x, t_distances_grain *gr);

void distances_set_turtledgrain(t_distances *x, t_distances_grain *gr);

/* void distances_jsave(t_distances *x, t_dictionary *d);
void distances_preset(t_distances *x);
void distances_begin_preset(t_distances *x, t_symbol *s, long argc, t_atom *argv);
void distances_restore_preset(t_distances *x, t_symbol *s, long argc, t_atom *argv);
void distances_end_preset(t_distances *x);

 void distances_clear(t_distances *x, char also_outside_world);
 void distances_undo_postprocess(t_distances *x);
*/



//////////////////////// global class pointer variable
static t_class *distances_class;
static t_symbol	*ps_dbview_update = NULL;
static t_symbol	*ps_dbview_query_changed = NULL;





///////////////////////// utility functions


long distances_colname_to_coltype(t_distances *x, t_symbol *tablename, t_symbol *colname)
{
    if (colname && colname->s_name) {
        t_xbase *xbase = (t_xbase *)x->d_database->s_thing; // database already exists
        if (xbase && xbase->magic == DADA_XBASE_MAGIC_GOOD) {
            return colname_to_coltype(xbase, tablename, colname);
        }
    }
    
    return 0;
}


void distances_iar(t_distances *x)
{
	jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
	jbox_invalidate_layer((t_object *)x, NULL, gensym("grains"));
	jbox_redraw((t_jbox *)x);
}


// process any change which has happened for the shapes
void process_change(t_distances *x)
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

	CLASS_NEW_CHECK_SIZE(c, "dada.distances", (method)distances_new, (method)distances_free, (long)sizeof(t_distances), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, 0);	// include textfield and Fonts attributes
	//	jbox_initclass(c, 0);
	
	// paint & utilities
	class_addmethod(c, (method) distances_paint,			"paint", A_CANT, 0);
	class_addmethod(c, (method) distances_assist,			"assist",		A_CANT, 0);  
	class_addmethod(c, (method)	distances_notify,			"bachnotify",		A_CANT,		0);

	// save & preset
/*    class_addmethod(c, (method) distances_preset, "preset", 0);
    class_addmethod(c, (method) distances_begin_preset, "begin_preset", A_GIMME, 0);
    class_addmethod(c, (method) distances_restore_preset, "restore_preset", A_GIMME, 0);
    class_addmethod(c, (method) distances_end_preset, "end_preset", 0);
	CLASS_METHOD_ATTR_PARSE(c, "begin_preset", "undocumented", gensym("long"), 0L, "1");
	CLASS_METHOD_ATTR_PARSE(c, "restore_preset", "undocumented", gensym("long"), 0L, "1");
	CLASS_METHOD_ATTR_PARSE(c, "end_preset", "undocumented", gensym("long"), 0L, "1");
	class_addmethod(c, (method) distances_jsave, "jsave", A_CANT, 0);
*/
	
	// @method (mouse) @digest Navigate or output grain content
	// @description When a grain is clicked, its content is output through the second outlet preceded by a "click" symbol.
	// If the <m>mousehover</m> attribute is set to 1, when a grain is hovered with the mouse, its content is output through
	// the second outlet, preceded by a "hover" symbol.
    // Use scroll or two finger swipe to move in the plane. Use <m>Cmd</m>+scroll to change zoom.
	class_addmethod(c, (method) distances_focusgained, "focusgained", A_CANT, 0);
	class_addmethod(c, (method) distances_focuslost, "focuslost", A_CANT, 0); 	
	class_addmethod(c, (method) distances_mousedown, "mousedown", A_CANT, 0);
	class_addmethod(c, (method) distances_mousedrag, "mousedrag", A_CANT, 0);
	class_addmethod(c, (method) distances_mouseup, "mouseup", A_CANT, 0);

    // @method (keyboard) @digest Autozoom
    // @description Use <m>Tab</m> to set the zoom automatically depending on the displayed points
    class_addmethod(c, (method) distances_key, "key", A_CANT, 0);
  	class_addmethod(c, (method) distances_keyup, "keyup", A_CANT, 0);
    
    // @method (tools) @digest Navigate
    // @description
    // @copy DADA_DOC_TOOLS_INTRO
    // @copy DADA_DOC_TOOLS_ZX
	class_addmethod(c, (method) distances_mousemove, "mousemove", A_CANT, 0);
	class_addmethod(c, (method) distances_mousewheel, "mousewheel", A_CANT, 0);
	class_addmethod(c, (method) distances_mouseenter, "mouseenter", A_CANT, 0);
	class_addmethod(c, (method) distances_mouseleave, "mouseleave", A_CANT, 0);

    // @method clock @digest Select a clock source
    // @description The word <m>clock</m>, followed by the name of an existing <m>setclock</m> objects, sets the
    // object to be controlled by that <m>setclock</m> object rather than by Max's internal millisecond clock.
    // The word <m>clock</m> by itself sets the object back to using Max's regular millisecond clock.
    class_addmethod(c, (method)distances_clock,	"clock", A_DEFSYM, 0);
    
    
	// @method bang @digest Output sampling information
	// @description Output the sampling information regarding the sampling points set via the <m>sample</m> message.
	class_addmethod(c, (method)distances_bang,			"bang",			0);

        
	// @method dump @digest Output content of all grains
	// @description Outputs from the first outlet an llll containing the content field of all the grains.
	class_addmethod(c, (method)distances_dump,		"dump",		A_GIMME,	0);

    
    // @method autozoom @digest Set domain and range automatically
    // @description Sets domain and range automatically depending on the displayed grains.
    class_addmethod(c, (method)distances_autozoom,		"autozoom",	0);

    
    // @method domain @digest Set the X domain
    // @description The <m>domain</m> message, followed by two numbers, sets minimum and maximum coordinates
    // to be displayed on the X axis.
    // The <m>domain</m> message,  followed by the "start" or "end" symbol and a number, sets the coordinate
    // to be displayed respectively at the left boundary or at the right boundary of the object box.
    // @marg 0 @name arguments @optional 0 @type list
    class_addmethod(c, (method)distances_anything,		"domain",		A_GIMME,	0);
    
    // @method range @digest Set the Y range
    // @description The <m>range</m> message, followed by two numbers, sets minimum and maximum coordinates
    // to be displayed on the Y axis
    // The <m>range</m> message,  followed by the "start" or "end" symbol and a number, sets the coordinate
    // to be displayed respectively at the bottom boundary or at top right boundary of the object box.
    // @marg 0 @name arguments @optional 0 @type list
    class_addmethod(c, (method)distances_anything,		"range",		A_GIMME,	0);

    
    // @method getdomain @digest Retrieve current X domain
    // @description The <m>getdomain</m> message outputs from the third outlet the minimum and maximum
    // coordinates displayed on the X axis, preceded by a <m>domain</m> symbol.
    class_addmethod(c, (method)distances_anything,		"getdomain",		A_GIMME,	0);

    
    // @method getrange @digest Retrieve current Y range
    // @description The <m>getrange</m> message outputs from the third outlet the minimum and maximum
    // coordinates displayed on the Y axis, preceded by a <m>range</m> symbol.
    class_addmethod(c, (method)distances_anything,		"getrange",		A_GIMME,	0);

    
    
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
    class_addmethod(c, (method)distances_anything,		"setturtle",		A_GIMME,	0);
	

    // @method turtle @digest Set the turtle and output grain content
	// @description The <m>turtle</m> message, followed by a <m>llll</m> of the kind <b>[<m>x</m>, <m>y</m>]</b>
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
	class_addmethod(c, (method)distances_anything,		"turtle",		A_GIMME,	0);

    
    // @method turtlemarkov @digest Move the turtle on the probability graph
    // @description The <m>turtlemarkov</m> message will move the turtle on a grain which is connected to the current turtle grain
    // (i.e. whose distance is less than <m>maxdistedge</m>), in a probabilistic fashion (i.e.: the more distant grains are,
    // the less likely it is for the turtle to end up on them).
    // If <m>memory</m> is greater than 1, then repetition with previous states will be avoided, according to such attribute.
    // If there's no connected grain to the current turtled grain, or if no new grain could be reached, and "end" notification is sent.
    // @seealso turtleclear
    class_addmethod(c, (method)distances_anything,		"turtlemarkov",		A_GIMME,	0);

    
    // @method turtleclear @digest Clear history of turtled grains
    // @description The <m>turtleclear</m> message will clear the history of turtled grains (useful in combination with <m>turtlemarkov</m>,
    // to reset the repetition avoidance mechanism).
    // @seealso turtlemarkov
    class_addmethod(c, (method)distances_anything,		"turtleclear",		A_GIMME,	0);

    
	
	// @method turtledelta @digest Move the turtle and output grain content
	// @description The <m>turtledelta</m> message, followed by a <m>llll</m> of the kind <b>[<m>delta_x</m>, <m>delta_y</m>]</b>
	// moves the turtle of a (<m>delta_x</m>, <m>delta_y</m>) vector and sets it to the nearest grain to the new position (ignoring
	// the grain which previously had the turtle). The content field(s) of such grain are then output from the second outlet preceded by the
	// "turtle" symbol. <br />
    // If <m>relativeturtle</m> is on, the coordinates are expected to be between 0 and 1, relative to the current domain and range
    // (caveat: more precisely, to the domain and range of the latest painted view of the object).
	// @marg 0 @name delta_position @optional 0 @type llll
	class_addmethod(c, (method)distances_anything,		"turtledelta",		A_GIMME,	0);
	
	
    // @method getturtle @digest Output turtle grain content
    // @description The <m>getturtle</m> message outputs the grain content for the grain where the turtle is currently located, if any.
    class_addmethod(c, (method)distances_anything,		"getturtle",		A_GIMME,	0);

    
    
	// @method knn @digest Find nearest neighbors
	// @description The <m>knn</m> message, followed by an integer <m>K</m> and an <m>llll</m> of the kind <b>[<m>x</m>, <m>y</m>]</b>,
	// finds the <m>K</m> points which are nearest to the location (<m>x</m>, <m>y</m>), and outputs their content field(s) from the third outlet. <br />
    // If <m>relativeknn</m> is on, the coordinates are expected to be between 0 and 1, relative to the current domain and range
    // (caveat: more precisely, to the domain and range of the latest painted view of the object).
	// @marg 0 @name number_of_neighbors @optional 0 @type int
	// @marg 1 @name position @optional 0 @type llll
	class_addmethod(c, (method)distances_anything,		"knn",		A_GIMME,	0);
	

    // @method getnumgrains @digest Get the number of currently displayed grains
    // @description The <m>getnumgrains</m> message returns the number of currently displayed grains, preceded by the "numgrains" symbol, from the
    // third outlet. <br />
    // N.B.: the grain calculation is performed during the paint method; unless your object is repainted, this number won't be updated.
    // A "done" notification is sent through the third outlet whenever grains have been properly recomputed. Be sure to use such notification
    // to trigger a <m>getnumgrains</m> message.
    class_addmethod(c, (method)distances_anything,		"getnumgrains",		A_GIMME,	0);
    
    
    // @method getgrid @digest Output uniform grid
    // @description The <m>getgrid</m> message outputs from the notification outlet
    // the content of each grain arranged in matrix form (corresponding to the grid on gets when
    // setting <m>uniform</m> to 1).
    class_addmethod(c, (method)distances_anything,		"getgrid",		A_GIMME,	0);

    // @method getgraph @digest Output graph in llll form
    // @description The <m>getgraph</m> message outputs the information in graph form from the notification outlet,
    // as vertices (along with their content) and connections (edges),
    // depending on the <m>maxdistedge</m> attribute.
    class_addmethod(c, (method)distances_anything,		"getgraph",		A_GIMME,	0);

	class_addmethod(c, (method)distances_anything,	"anything",			A_GIMME,	0);

    
    DADAOBJ_JBOX_DECLARE_IMAGE_METHODS(c);
    
	llllobj_class_add_out_attr(c, LLLL_OBJ_UI);
	
	dadaobj_class_init(c, LLLL_OBJ_UI, DADAOBJ_BBGIMAGE | DADAOBJ_ZOOM | DADAOBJ_CENTEROFFSET | DADAOBJ_GRID | DADAOBJ_AXES | DADAOBJ_LABELS |  DADAOBJ_MOUSEHOVER | DADAOBJ_GRID_SHOWDEFAULT | DADAOBJ_LABELS_SHOWDEFAULT | DADAOBJ_EXPORTTOJITTER);
	CLASS_ATTR_FILTER_CLIP(c, "zoom", 0.0001, 100000);

	
	CLASS_ATTR_DEFAULT(c, "patching_rect", 0, "0 0 300 300");
	// @exclude dada.distances
	CLASS_ATTR_DEFAULT(c, "presentation_rect", 0, "0 0 300 300");
	// @exclude dada.distances
	

	CLASS_STICKY_ATTR(c,"category",0,"Color");
	
	CLASS_ATTR_RGBA(c, "legendcolor", 0, t_distances, j_legendcolor);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "legendcolor", 0, "0.25 0.25 0.25 1.");
	CLASS_ATTR_STYLE_LABEL(c, "legendcolor", 0, "rgba", "Legend Text Color");
	// @description Sets the color of the legend.

	CLASS_ATTR_RGBA(c, "turtlecolor", 0, t_distances, j_turtlecolor);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "turtlecolor", 0, "0.34 0.87 0.20 1.");
	CLASS_ATTR_STYLE_LABEL(c, "turtlecolor", 0, "rgba", "Turtle Color");
	// @description Sets the color of the turtle.

    CLASS_ATTR_RGBA(c, "graincolor", 0, t_distances, j_graincolor);
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "graincolor", 0, "0. 0. 0. 1.");
    CLASS_ATTR_STYLE_LABEL(c, "graincolor", 0, "rgba", "Default Grain Color");
    // @description Sets the default grain color.

    CLASS_ATTR_RGBA(c, "edgecolor", 0, t_distances, j_edgecolor);
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "edgecolor", 0, "0. 0. 0. 1.");
    CLASS_ATTR_STYLE_LABEL(c, "edgecolor", 0, "rgba", "Graph Edge Color");
    // @description Sets the color of the edges in the distance graph

	CLASS_STICKY_ATTR_CLEAR(c, "category");

	

	CLASS_STICKY_ATTR(c,"category",0,"Settings");
	
	CLASS_ATTR_SYM(c,			"query",			ATTR_SET_DEFER_LOW,	t_distances, d_query);
	CLASS_ATTR_ACCESSORS(c,		"query",			NULL, distances_set_query);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"query",0,"");
	CLASS_ATTR_INVISIBLE(c, "query", ATTR_GET_OPAQUE | ATTR_SET_OPAQUE);
	// @exclude dada.distances
	
    CLASS_ATTR_ATOM_VARSIZE(c,"where", ATTR_SET_DEFER, t_distances, d_where_av, d_where_ac, 32500); // list limit is somewhere below 2^15, this should be a safe limit
    CLASS_ATTR_STYLE_LABEL(c, "where", 0, "text", "Where Clause For Display Query");
    CLASS_ATTR_ACCESSORS(c,        "where",            NULL, distances_set_where);
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"where",0,"");
    // @description Sets the SQLite 'WHERE' clause to sieve displayed data.

	CLASS_ATTR_SYM(c,			"database",			ATTR_SET_DEFER_LOW,	t_distances, d_database);
	CLASS_ATTR_ACCESSORS(c,		"database",			NULL, distances_set_database);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"database",0,"");
	CLASS_ATTR_SAVE(c,			"database",			0);
    CLASS_ATTR_STYLE_LABEL(c,	"database", 0, "text", "Database Name");
    CLASS_ATTR_BASIC(c, "database", 0);
	// @description Sets the database name. The database must be instantiated via a <o>dada.base</o> object having such name.
	

	CLASS_ATTR_SYM(c, "table", ATTR_SET_DEFER_LOW, t_distances, tablename);
    CLASS_ATTR_STYLE_LABEL(c, "table", 0, "text", "Table Name");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"table",0,"");
    CLASS_ATTR_BASIC(c, "table", 0);
	// @description Sets the name of the database table to be displayed.

    
    CLASS_ATTR_SYM(c, "distancetable", ATTR_SET_DEFER_LOW, t_distances, disttablename);
    CLASS_ATTR_STYLE_LABEL(c, "distancetable", 0, "text", "Distance Table Name");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"distancetable",0,"");
    CLASS_ATTR_BASIC(c, "distancetable", 0);
    // @description Sets the name of the database table containing distances between element of the defined <m>table</m>.
    
    CLASS_ATTR_ATOM(c, "memory", 0, t_distances, markov_avoid_repetition_memory);
    CLASS_ATTR_STYLE_LABEL(c, "memory", 0, "text", "Markov Turtling Avoid Repetitions Memory");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"memory",0,"1");
    // @description Sets a number <m>N</m> so that repetitions of the same grain will be avoided before <m>N</m> steps have passed.
    // Set this value to "inf" to always avoid repetitions. Default is 1: repetition is only avoided with the current step (i.e.
    // the new step will be different from the current one.
    // A <m>turtleclear</m> message will reset the memory.
    
	
    CLASS_STICKY_ATTR_CLEAR(c, "category");

    
    CLASS_STICKY_ATTR(c,"category",0,"Fields");
	
	CLASS_ATTR_SYM(c, "sizefield", 0, t_distances, field_size);
    CLASS_ATTR_STYLE_LABEL(c, "sizefield", 0, "text", "Size Range Field");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"sizefield",0,"none");
	// @description Sets the name of the field (column) to be mapped on the grain size, if any (use "none" to avoid defining it).

	CLASS_ATTR_SYM(c, "colorfield", 0, t_distances, field_color);
    CLASS_ATTR_STYLE_LABEL(c, "colorfield", 0, "text", "Color Spectrum Field");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"colorfield",0,"none");
	// @description Sets the name of the field (column) to be mapped on the grain color, if any (use "none" to avoid defining it).
	
	CLASS_ATTR_SYM(c, "shapefield", 0, t_distances, field_shape);
    CLASS_ATTR_STYLE_LABEL(c, "shapefield", 0, "text", "Shape Field");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"shapefield",0,"none");
	// @description Sets the name of the field (column) to be mapped on the grain shape, if any (use "none" to avoid defining it).
	// Must be an integer field (1 being mapped to a circle, 2 to a triangle, 3 to a square, and so on)
	
    CLASS_ATTR_SYM_VARSIZE(c, "contentfield", 0, t_distances, field_content, field_content_size, DADA_DISTANCES_MAX_CONTENTFIELDS);
    CLASS_ATTR_STYLE_LABEL(c, "contentfield", 0, "text", "Content Field(s)");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"contentfield",0,"content");
    CLASS_ATTR_BASIC(c, "contentfield", 0);
	// @description Sets the name of the field or fields (columns) to be output
	// when the grain is clicked or hovered (usually a score gathered syntax).

    
    
	CLASS_ATTR_SYM(c, "bpmfield", 0, t_distances, field_bpm);
    CLASS_ATTR_STYLE_LABEL(c, "bpmfield", 0, "text", "BPM Field");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"bpmfield",0,"none");
	// @description Sets the name of the field (column) bearing the BPM value, if any (use "none" to avoid defining it).
	
	CLASS_ATTR_SYM(c, "phasefield", 0, t_distances, field_phase);
    CLASS_ATTR_STYLE_LABEL(c, "phasefield", 0, "text", "BPM Phase Field");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"phasefield",0,"none");
	// @description Sets the name of the field (column) bearing the BPM phase value, if any (use "none" to avoid defining it).

    CLASS_ATTR_SYM(c, "lengthfield", 0, t_distances, field_length);
    CLASS_ATTR_STYLE_LABEL(c, "lengthfield", 0, "text", "Length Field (Milliseconds)");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"lengthfield",0,"none");
    // @description Sets the name of the field (column) bearing the length of the content (in milliseconds), if any (use "none" to avoid defining it).

    
    CLASS_ATTR_SYM(c, "labelfield", 0, t_distances, field_label);
    CLASS_ATTR_STYLE_LABEL(c, "labelfield", 0, "text", "Label Field");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"labelfield",0,"none");
    // @description Sets the name of the field (column) bearing the labels.

    
	CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	
	CLASS_STICKY_ATTR(c,"category",0,"Behavior");

    CLASS_ATTR_LONG(c, "seed", 0, t_distances, random_seed);
    CLASS_ATTR_STYLE_LABEL(c, "seed", 0, "text", "Random Seed");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"seed",0,"1");
    // @description Sets a random seed for the multidimensional scaling algorithm.

    CLASS_ATTR_LONG(c, "numiter", 0, t_distances, numiter);
    CLASS_ATTR_STYLE_LABEL(c, "numiter", 0, "text", "Number Of Iterations");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"numiter",0,"30");
    CLASS_ATTR_BASIC(c, "numiter", 0);
    CLASS_ATTR_FILTER_MIN(c, "numiter", 1);
    // @description Sets the number of iterations for the multidimensional scaling algorithm.

    
	CLASS_ATTR_CHAR(c, "autozoomwhenupdated", 0, t_distances, autozoom);
    CLASS_ATTR_STYLE_LABEL(c, "autozoomwhenupdated", 0, "onoff", "Auto Zoom When Updated");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"autozoomwhenupdated",0,"1");
	// @description Toggles the ability to zoom automatically when the database is updated.

    CLASS_ATTR_CHAR(c, "relativeturtle", 0, t_distances, relative_turtling);
    CLASS_ATTR_STYLE_LABEL(c, "relativeturtle", 0, "onoff", "Relative Turtling");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"relativeturtle",0,"0");
    // @description If <m>relativeturtle</m> is on, the values used for the <m>turtle</m>, <m>setturtle</m> and <m>turtledelta</m> messages
    // are expected to be between 0 and 1, corresponding to the minimum and maximum coordinates displayed in the domain and range of the object
    // (caveat: more precisely, to the domain and range of the latest painted view of the object).
    
    CLASS_ATTR_CHAR(c, "relativeknn", 0, t_distances, relative_knn);
    CLASS_ATTR_STYLE_LABEL(c, "relativeknn", 0, "onoff", "Relative KNN");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"relativeknn",0,"0");
    // @description If <m>relativeknn</m> is on, the values used for the <m>knn</m> message
    // are expected to be between 0 and 1, corresponding to the minimum and maximum coordinates displayed in the domain and range of the object
    // (caveat: more precisely, to the domain and range of the latest painted view of the object).
    
    CLASS_STICKY_ATTR_CLEAR(c, "category");
    
    

    CLASS_STICKY_ATTR(c,"category",0,"Play");

    CLASS_ATTR_CHAR(c, "beatsync", 0, t_distances, beat_sync);
    CLASS_ATTR_STYLE_LABEL(c, "beatsync", 0, "onoff", "Beat Synchronous Interface Play");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"beatsync",0,"0");
    CLASS_ATTR_BASIC(c, "beatsync", 0);
	// @description Toggles the ability to postpone playing of grains depending on the beat grid
	// given from the current tempo (see <m>bpmfield</m>) and depending on the grain phase (see <m>phasefield</m>).

    CLASS_ATTR_DOUBLE(c, "mindist", 0, t_distances, antibis_ms);
    CLASS_ATTR_STYLE_LABEL(c, "mindist", 0, "text", "Grains Scheduling Separation Time");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"mindist",0,"0");
    // @description Sets a minimum distance (in milliseconds) for two grains to be scheduled.
    // In <m>beatsync</m> mode, this avoids multiple grains to be scheduled at the same moment.
    // Use a negative number to turn this behavior off.
    
    CLASS_ATTR_CHAR(c, "looplast", 0, t_distances, loop_last);
    CLASS_ATTR_STYLE_LABEL(c, "looplast", 0, "onoff", "Loop Last Played Grain");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"looplast",0,"0");
    // @description Toggles the ability to loop the last played grain if no other grain has been sequenced.

    CLASS_ATTR_CHAR(c, "stoploopwhennothovered", 0, t_distances, interrupt_looping_when_not_hovering);
    CLASS_ATTR_STYLE_LABEL(c, "stoploopwhennothovered", 0, "onoff", "Stop Looped Playing When Mouse Is Not Hovering");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"stoploopwhennothovered",0,"1");
    // @description Toggles the ability to stop looped playing when mouse is not hovering any point

    CLASS_ATTR_CHAR(c, "stoplooponmouseleave", 0, t_distances, interrupt_looping_on_mouseleave);
    CLASS_ATTR_STYLE_LABEL(c, "stoplooponmouseleave", 0, "onoff", "Stop Looped Playing When Mouse Leaves");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"stoplooponmouseleave",0,"1");
    // @description Toggles the ability to stop looped playing when mouse leaves the object.
    
    
    CLASS_ATTR_CHAR(c, "stopbeatsonmouseleave", 0, t_distances, interrupt_beatsync_on_mouseleave);
    CLASS_ATTR_STYLE_LABEL(c, "stopbeatsonmouseleave", 0, "onoff", "Stop Beat Sync Bangs When Mouse Leaves");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"stopbeatsonmouseleave",0,"0");
    // @description Toggles the ability to stop beat sync bangs to be sent out from the last outlet when mouse leaves the object.

	CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	
	CLASS_STICKY_ATTR(c,"category",0,"Appearance");

	CLASS_ATTR_DOUBLE(c, "minr", 0, t_distances, minradius);
    CLASS_ATTR_STYLE_LABEL(c, "minr", 0, "text", "Minimum Point Radius");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"minr",0,"2");
	// @description Sets a minimum radius for point display.
	
	CLASS_ATTR_DOUBLE(c, "maxr", 0, t_distances, maxradius);
    CLASS_ATTR_STYLE_LABEL(c, "maxr", 0, "text", "Maximum Point Radius");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"maxr",0,"8");
	// @description Sets a maximum radius for point display.
	
	CLASS_ATTR_CHAR(c, "showlegend", 0, t_distances, show_legend);
    CLASS_ATTR_STYLE_LABEL(c, "showlegend", 0, "onoff", "Show Legend");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showlegend",0,"1");
	// @description Toggles the ability to display the point legend on mousehover.

	CLASS_ATTR_CHAR(c, "showturtle", 0, t_distances, show_turtle);
    CLASS_ATTR_STYLE_LABEL(c, "showturtle", 0, "onoff", "Show Turtle");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showturtle",0,"1");
	// @description Toggles the ability to display the turtle.
	
	CLASS_ATTR_DOUBLE(c, "legendsize", 0, t_distances, legend_text_size);
    CLASS_ATTR_STYLE_LABEL(c, "legendsize", 0, "text", "Legend Text Size");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"legendsize",0,"12");
	// @description Sets the text font size for the legend.

    CLASS_ATTR_DOUBLE(c, "labelsize", 0, t_distances, labels_text_size);
    CLASS_ATTR_STYLE_LABEL(c, "labelsize", 0, "text", "Labels Text Size");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"labelsize",0,"9");
    // @description Sets the text font size for the labels.
    
	CLASS_ATTR_DOUBLE(c, "alpha", 0, t_distances, point_alpha);
    CLASS_ATTR_STYLE_LABEL(c, "alpha", 0, "text", "Point Opacity");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"alpha",0,"50");
	// @description Sets the transparency/opacity of displayed grains.
	
    CLASS_ATTR_CHAR(c, "showlabels", 0, t_distances, paint_labels);
    CLASS_ATTR_STYLE_LABEL(c, "showlabels", 0, "onoff", "Show Labels");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showlabels",0,"1");
    CLASS_ATTR_BASIC(c, "showlabels", 0);
    // @description Show/hide the labels display

    CLASS_ATTR_DOUBLE(c, "maxdistedge", 0, t_distances, max_dist_edge);
    CLASS_ATTR_STYLE_LABEL(c, "maxdistedge", 0, "text", "Maximum Distance for Edge Painting");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"maxdistedge",0,"10.");
    CLASS_ATTR_BASIC(c,"maxdistedge",0);
    // @description Sets a maximum distance for edges to be painted. Use 0 to avoid painting edges.


    CLASS_ATTR_CHAR(c, "uniform", 0, t_distances, also_compute_uniform_grid);
    CLASS_ATTR_ACCESSORS(c, "uniform", NULL, distances_set_uniform);
    CLASS_ATTR_STYLE_LABEL(c, "uniform", 0, "onoff", "Also Compute Uniform Grid");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"uniform",0,"0.");
    CLASS_ATTR_FILTER_CLIP(c, "uniform", 0., 1.);
    // @description Toggles the computation of the uniform grid. By default, to avoid wasting useless CPU-time, this is off.
    // You need to turn this on before touching to the other uniform grid attributes <m>uniformpar</m> and <m>uniformsize</m>.

    CLASS_ATTR_DOUBLE(c, "uniformpar", 0, t_distances, align_to_uniform_grid);
    CLASS_ATTR_ACCESSORS(c, "uniformpar", NULL, distances_set_uniformpar);
    CLASS_ATTR_STYLE_LABEL(c, "uniformpar", 0, "text", "Align To Uniform Grid");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"uniformpar",0,"0.");
    CLASS_ATTR_FILTER_CLIP(c, "uniformpar", 0., 1.);
    // @description Sets an alignment factor to align elements to an uniform grid (in a 0-1 range: 0. = unaligned, 1. = perfectly aligned).
    // The <m>uniform</m> attribute must be on.
    
    CLASS_ATTR_LONG_ARRAY(c, "uniformsize", 0, t_distances, uniform_grid_size, 2);
    CLASS_ATTR_STYLE_LABEL(c, "uniformsize", 0, "text", "Uniform Grid Size");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"uniformsize",0,"0 0");
    // @description Sets the number of rows and columns of the uniform grid.
    // If any of the entry is less or equal to 0, the number of rows and columns will be automatically assigned.
    // The <m>uniform</m> attribute must be on.

    
    
    CLASS_ATTR_DOUBLE(c, "uniformlr", 0, t_distances, uniform_grid_learning_rate);
    CLASS_ATTR_STYLE_LABEL(c, "uniformlr", 0, "text", "Uniform Grid Learning Rate");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"uniformlr",0,"1.");
    CLASS_ATTR_FILTER_CLIP(c, "uniformlr", 0.001, 1.);
    CLASS_ATTR_INVISIBLE(c, "uniformlr", ATTR_GET_OPAQUE | ATTR_SET_OPAQUE);
    // @exclude all
    // @description Sets a learning rate for the uniform grid algorithm.
    // The <m>uniform</m> attribute must be on.
    
    
    
    CLASS_ATTR_CHAR(c, "showedges", 0, t_distances, show_edges);
    CLASS_ATTR_STYLE_LABEL(c, "showedges", 0, "onoff", "Show Graph Edges");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showedges",0,"1");
    CLASS_ATTR_BASIC(c, "showedges", 0);
    // @description Show/hide the graph edges

    CLASS_ATTR_CHAR(c, "showgrains", 0, t_distances, show_grains);
    CLASS_ATTR_STYLE_LABEL(c, "showgrains", 0, "onoff", "Show Graph Nodes");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showgrains",0,"1");
    // @description Show/hide the graph nodes (grains)

    
    CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	distances_class = c;
    dadaobj_class_add_fileusage_method(c);

	ps_dbview_update = gensym("dbview_update");
	ps_dbview_query_changed = gensym("dbview_query_changed");

	dev_post("dada.distances compiled %s %s", __DATE__, __TIME__);
	return;
}

void view_create_do(t_distances *x, t_symbol *msg, long ac, t_atom *av)
{
    db_view_create(x->d_db, x->d_query->s_name, &x->d_view);
    object_attach_byptr_register(x, x->d_view, _sym_nobox);
}

t_max_err distances_set_uniform(t_distances *x, void *attr, long argc, t_atom *argv)
{
    if (argc && argv) {
        x->also_compute_uniform_grid = atom_getlong(argv);
        x->need_rebuild_grains = true;
        rebuild_grains(x, true); // straight away
        distances_iar(x);
    }
    return MAX_ERR_NONE;
}

t_max_err distances_set_uniformpar(t_distances *x, void *attr, long argc, t_atom *argv)
{
    if (argc && argv) {
        x->align_to_uniform_grid = atom_getfloat(argv);
        x->need_rebuild_grains = true;
        rebuild_grains(x, true); // straight away
        distances_iar(x);
    }
    return MAX_ERR_NONE;
}

t_max_err distances_set_query(t_distances *x, void *attr, long argc, t_atom *argv)
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

t_max_err distances_set_where(t_distances *x, void *attr, long argc, t_atom *argv)
{
    if (!argc) {
        x->d_where_ac = 0;
    } else {
        x->d_where_ac = argc;
        for (long i = 0; i < MIN(32500, argc); i++)
            x->d_where_av[i] = argv[i];
    }
    return MAX_ERR_NONE;
}



// this MUST be deferred_low, because if we have a [dada.base] with the same db name and a db3 binding in the patch,
// and if it happens to be instantiated NEXT, the db_open(,NULL,) stuff will prevent the filenaming bond
void distances_set_database_do(t_distances *x, t_symbol *msg, long argc, t_atom *argv)
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

t_max_err distances_set_database(t_distances *x, void *attr, long argc, t_atom *argv)
{
    if (argc && argv && atom_gettype(argv) == A_SYM && atom_getsym(argv) && strlen(atom_getsym(argv)->s_name) > 0) {
        defer_low(x, (method) distances_set_database_do, atom_getsym(argv), 0, NULL);
    }
	return MAX_ERR_NONE;
}





t_max_err distances_notify(t_distances *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
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
        if (attr_name == gensym("memory")) {
            llll_clear(x->turtled_grain_history);
        }
		if (attr_name == _sym_table) {
			char query[1024];
			snprintf_zero(query, 1024, "SELECT * FROM %s", x->tablename->s_name);
			object_attr_setsym((t_object *)x, gensym("query"), gensym(query));
		}
        if (attr_name == gensym("where")) {

        }
        if (attr_name == gensym("uniform")) {
            object_attr_setdisabled((t_object *)x, gensym("uniformsize"), x->also_compute_uniform_grid == 0);
            object_attr_setdisabled((t_object *)x, gensym("uniformpar"), x->also_compute_uniform_grid == 0);
            object_attr_setdisabled((t_object *)x, gensym("uniformls"), x->also_compute_uniform_grid == 0);
            if (x->also_compute_uniform_grid == 0) {
                if (!x->is_creating_new_obj) {
                    x->need_rebuild_grains = true;
                    rebuild_grains(x, true); // straight away
                }
                distances_iar(x);
            }
        }
		if (attr_name == _sym_table || attr_name == gensym("colorfield") || attr_name == gensym("sizefield") || attr_name == gensym("shapefield") ||
			attr_name == gensym("distancetable") ||  attr_name == gensym("table") || attr_name == gensym("lengthfield") ||
            attr_name == gensym("where") || attr_name == gensym("database") || attr_name == gensym("labelfield") || attr_name == gensym("maxdistedge") || attr_name == gensym("uniformlr") || attr_name == gensym("uniformsize") || attr_name == gensym("alpha") || attr_name == gensym("maxr") || attr_name == gensym("minr") || attr_name == gensym("seed") || attr_name == gensym("numiter"))  {
            if (!x->is_creating_new_obj) {
                x->need_rebuild_grains = true;
                rebuild_grains(x, true); // straight away
            }
            distances_iar(x);
        } else if (attr_name == gensym("center") || attr_name == gensym("zoom") || attr_name == gensym("vzoom") || attr_name == gensym("grid") || attr_name == gensym("uniform") || attr_name == gensym("showedges") || attr_name == gensym("showgrains") || attr_name == gensym("edgecolor") || attr_name == gensym("graincolor")) {
            distances_iar(x);
		} else
            jbox_redraw((t_jbox *)x);
		
	} else
	if (sender == x->d_view) {
		if (msg == ps_dbview_update) {
			distances_bang(x);
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

void distances_begin_preset(t_distances *x, t_symbol *s, long argc, t_atom *argv)
{
	dadaobj_begin_preset(dadaobj_cast(x), s, argc, argv);
}

void distances_restore_preset(t_distances *x, t_symbol *s, long argc, t_atom *argv)
{
	dadaobj_restore_preset(dadaobj_cast(x), s, argc, argv);
}

void distances_end_preset(t_distances *x)
{
	dadaobj_end_preset(dadaobj_cast(x));
}

void distances_preset(t_distances *x) {
	dadaobj_preset(dadaobj_cast(x));
}


void distances_jsave(t_distances *x, t_dictionary *d)
{
	if (x->b_ob.d_ob.save_data_with_patcher){
		if (x->b_ob.r_ob.l_dictll) {
			llll_store_in_dictionary(x->b_ob.r_ob.l_dictll, d, "distances_data", NULL);
		} else {
			t_llll *data = distances_get_state(x);
			llll_store_in_dictionary(data, d, "distances_data", NULL);
			llll_free(data);
		}
	} 
}
*/		

void distances_assist(t_distances *x, void *b, long m, long a, char *s)
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

void distances_free(t_distances *x)
{
    graph_free(&x->graph);
    if (x->D)
        delete x->D;
	db_view_remove(x->d_db, &x->d_view);
	db_close(&x->d_db);
    llll_free(x->scheduled_times);
    sysmem_freeptr(x->d_where_av);
    llll_free(x->grains);
    llll_free(x->grains_grid);
    llll_free(x->turtled_grain_history);
    object_free(x->loop_clock);
	dadaobj_jbox_free((t_dadaobj_jbox *)x); // jbox_free and llllobj_free are inside here
}


void distances_dump(t_distances *x)
{
	t_llllelem *elem;
	t_llll *res = llll_get();
	
	systhread_mutex_lock(x->b_ob.d_ob.l_mutex);
	for (elem = x->grains->l_head; elem; elem = elem->l_next) {
		t_distances_grain *gr = (t_distances_grain *)hatom_getobj(&elem->l_hatom);
		t_llll *gr_ll = get_grain_contentfield(x, gr);
		llll_appendllll(res, gr_ll, 0, WHITENULL_llll);
	}
	systhread_mutex_unlock(x->b_ob.d_ob.l_mutex);
	
	llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 0, res);
	llll_free(res);
}

//// beat synchronous processing
void distances_task(t_distances *x)
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

void post_creation_do(t_distances *x, t_symbol *msg, long ac, t_atom *av)
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


void *distances_new(t_symbol *s, long argc, t_atom *argv)
{
	t_distances *x = NULL;
	t_dictionary *d = NULL;
	long boxflags;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;    
	
	if ((x = (t_distances *)object_alloc_debug(distances_class))) {
		
        x->is_creating_new_obj = true;
		x->grains = llll_get();
        x->grains_grid = llll_get();
        x->scheduled_times = llll_get();
		x->curr_beat_ms = 1000;
        x->loop_clock = clock_new(x, (method)distances_loop_tick);
        x->turtled_grain_history = llll_get();
        x->d_where_ac = 0;
        x->d_where_av = (t_atom *)sysmem_newptr(32500 * sizeof(t_atom));

        graph_new(&x->graph, DADA_GRAPH_FLAG_SYMMETRIC, DADA_GRAPH_METADATA_OBJ, DADA_GRAPH_METADATA_DOUBLE, DADA_LINE_STRAIGHT);
 		
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

		dadaobj_jbox_setup((t_dadaobj_jbox *)x, DADAOBJ_BBGIMAGE | DADAOBJ_ZOOM | DADAOBJ_CENTEROFFSET, build_pt(5, 5), 3, 4, 2, (dada_paint_ext_fn)distances_paint_ext, (invalidate_and_redraw_fn)distances_iar, "vn", 2, "b444");
		dadaobj_addfunctions(dadaobj_cast(x), (dada_mousemove_fn)distances_mousemove, (method)distances_task, NULL, NULL, NULL, NULL, NULL, NULL);

		x->d_columns = hashtab_new(13);
		hashtab_flags(x->d_columns, OBJ_FLAG_DATA);
		x->d_query = _sym_nothing;
		x->d_database = gensym("");
		x->tablename = _sym_nothing;

		distances_initdataview(x);
        
        attr_dictionary_process(x,d);

        // changing min and max zoom
        x->b_ob.d_ob.m_zoom.max_zoom_perc = build_pt(10000, 10000);
        x->b_ob.d_ob.m_zoom.min_zoom_perc = build_pt(0.01, 0.01);
        
        jbox_ready((t_jbox *)x);
        
        defer_low(x, (method)post_creation_do, NULL, 0, NULL);
    }
	return x;
}

void distances_initdataview(t_distances *x)
{
	x->d_dataview = (t_object*)jdataview_new();
	jdataview_setclient(x->d_dataview, (t_object*)x);
	jdataview_setcolumnheaderheight(x->d_dataview, 40);
	jdataview_setheight(x->d_dataview, 16.0);
}	


void distances_int(t_distances *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	distances_anything(x, _sym_list, 1, argv);
}

void distances_float(t_distances *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	distances_anything(x, _sym_list, 1, argv);
}

void distances_autozoom(t_distances *x)
{
    dadaobj_cast(x)->m_zoom.must_autozoom = true;
    distances_iar(x);
}


void distances_clock(t_distances *x, t_symbol *s)
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

double distances_grain_get_sum_of_weights(t_distances *x, t_distances_grain *gr)
{
    t_llll *adj_list = graph_vertex_get_outgoing_edges_list(&x->graph, gr->graph_ID);
    t_llllelem *elem;
    
    if (!adj_list || adj_list->l_size == 0) {
        llll_free(adj_list);
        return 0;
    }
    
    double sum = 0.;
    for (elem = adj_list->l_head; elem; elem = elem->l_next) {
        long edge = hatom_getlong(&elem->l_hatom);
        double this_weight = MAX(0., x->graph.edges[edge].data.m_double);
        sum += this_weight;
    }
    
    llll_free(adj_list);
    return sum;

}


long move_turtle_markov(t_distances *x)
{
    long res = 0;
    dadaobj_mutex_lock(dadaobj_cast(x));
    if (x->turtled_grain) {
        t_llll *adj_list = graph_vertex_get_outgoing_edges_list(&x->graph, x->turtled_grain->graph_ID);
        t_llllelem *elem;
        
        // sieving adj_list according to turtle markov avoidance memory
        if (x->turtled_grain_history->l_size > 1) {
            t_llllelem *nextelem;
            for (elem = adj_list->l_head; elem; elem = nextelem) {
                nextelem = elem->l_next;
                long edge = hatom_getlong(&elem->l_hatom);
                long new_cursor = (x->graph.edges[edge].end == x->turtled_grain->graph_ID ? x->graph.edges[edge].start : x->graph.edges[edge].end);
                t_distances_grain *new_cursor_grain = (t_distances_grain *)x->graph.vertices[new_cursor].data.m_obj;
                if (is_obj_in_llll_first_level(x->turtled_grain_history, new_cursor_grain))
                    llll_destroyelem(elem);
            }
        }
        
        if (!adj_list || adj_list->l_size == 0) {
            res = 1; // done
        } else {
            t_llll *weights = llll_get();
            double sum = 0.;
            for (elem = adj_list->l_head; elem; elem = elem->l_next) {
                long edge = hatom_getlong(&elem->l_hatom);
                double this_weight = MAX(0., x->graph.edges[edge].data.m_double);
                sum += this_weight;
                llll_appenddouble(weights, this_weight, 0, WHITENULL_llll);
            }
            
            if (sum <= 0.) {
                res = 1; // done
            } else {
                double random_pick = rand_range(0., sum);
                long new_cursor = -1, i;
                sum = 0;
                for (elem = adj_list->l_head, i = 0; elem; elem = elem->l_next, i++) {
                    long edge = hatom_getlong(&elem->l_hatom);
                    double this_weight = MAX(0., x->graph.edges[edge].data.m_double);
                    sum += this_weight;
                    if (random_pick < sum) {
                        new_cursor = (x->graph.edges[edge].end == x->turtled_grain->graph_ID ? x->graph.edges[edge].start : x->graph.edges[edge].end);
                        break;
                    }
                }
                
                if (new_cursor < 0)
                    res = 1;
                else
                    distances_set_turtledgrain(x, (t_distances_grain *)x->graph.vertices[new_cursor].data.m_obj);
            }
        }
        llll_free(adj_list);
    }
    dadaobj_mutex_unlock(dadaobj_cast(x));
    return res;
}


void distances_bang(t_distances *x)
{
    x->need_rebuild_grains = true;
    rebuild_grains(x, false); // straight away
    distances_iar(x);
    return;
}

void distances_clear(t_distances *x, char also_outside_current_world)
{	
	jbox_redraw((t_jbox *)x);
}

long sort_by_pt_distance_fn(void *data, t_llllelem *a, t_llllelem *b)
{
    t_distances *x = ((t_distances *)(((void **)data)[0]));
    t_pt coord = *((t_pt *)(((void **)data)[1]));
    t_pt a_coord = distances_get_grain_coord(x, (t_distances_grain *)hatom_getobj(&a->l_hatom));
    t_pt b_coord = distances_get_grain_coord(x, (t_distances_grain *)hatom_getobj(&b->l_hatom));
    
    return (pt_pt_distance_squared(a_coord, coord) <= pt_pt_distance_squared(b_coord, coord));
}

long sort_by_pt_distance_relative_fn(void *data, t_llllelem *a, t_llllelem *b)
{
    t_distances *x = ((t_distances *)(((void **)data)[0]));
    t_pt coord = *((t_pt *)(((void **)data)[1]));
    t_rect relative_rect = *((t_rect *)(((void **)data)[2]));
    t_pt a_coord = distances_get_grain_coord(x, (t_distances_grain *)hatom_getobj(&a->l_hatom));
    t_pt b_coord = distances_get_grain_coord(x, (t_distances_grain *)hatom_getobj(&b->l_hatom));
    
    t_pt a_pt = build_pt((a_coord.x - relative_rect.x)/relative_rect.width, (a_coord.y - relative_rect.y)/relative_rect.height);
    t_pt b_pt = build_pt((b_coord.x - relative_rect.x)/relative_rect.width, (b_coord.y - relative_rect.y)/relative_rect.height);
    
    return (pt_pt_distance_squared(a_pt, coord) <= pt_pt_distance_squared(b_pt, coord));
}




t_llll *distances_get_knn(t_distances *x, long num_neighbors, t_pt coord, t_distances_grain *but_not_this_grain, char coord_are_01)
{
	t_llllelem *elem;
	long count;
    void *data[3];

//	post("- coord: %ld, %ld", coord.x, coord.y);

    if (coord_are_01) {
        t_rect rect = build_rect(x->domain_min, x->range_min, x->domain_max - x->domain_min, x->range_max - x->range_min);
        data[0] = x;
        data[1] = &coord;
        data[2] = &rect;
        
        llll_inplacesort(x->grains, (sort_fn) sort_by_pt_distance_relative_fn, data);
    } else {
        data[0] = x;
        data[1] = &coord;
        llll_inplacesort(x->grains, (sort_fn) sort_by_pt_distance_fn, data);
    }
	 
    
	t_llll *res = llll_get();
	for (elem = x->grains->l_head, count = 0; elem && count < num_neighbors; elem = elem->l_next){
		if (but_not_this_grain && but_not_this_grain == (t_distances_grain *)hatom_getobj(&elem->l_hatom))
			continue;
		llll_appendobj(res, hatom_getobj(&elem->l_hatom), 0, WHITENULL_llll);
		count++;
	}
	
	return res;
}

t_distances_grain *distances_get_1nn(t_distances *x, t_pt coord, t_distances_grain *but_not_this_grain, char coord_are_01)
{
	t_distances_grain *gr = NULL;
	
	t_llll *res = distances_get_knn(x, 1, coord, but_not_this_grain, coord_are_01);
	
	if (res->l_head) 
		gr = (t_distances_grain *)hatom_getobj(&res->l_head->l_hatom);
	
	llll_free(res);
	return gr;
}

long subs_objs_fn(void *data, t_hatom *a, const t_llll *address)
{
    t_distances *x = (t_distances *)data;
    if (hatom_gettype(a) == H_OBJ) {
        t_distances_grain *gr = (t_distances_grain *)hatom_getobj(a);
        t_llll *content = get_grain_contentfield(x, gr);
        hatom_change_to_llll(a, content);
    }
    return 1;
}


t_distances_grain *distances_get_grain_from_table_id(t_distances *x, long table_id)
{
    for (t_llllelem *elem = x->grains->l_head; elem; elem = elem->l_next) {
        t_distances_grain *gr = (t_distances_grain *)hatom_getobj(&elem->l_hatom);
        if (gr->db_id == table_id)
            return gr;
    }
    return NULL;
}

t_distances_grain *distances_get_grain_from_field_value(t_distances *x, t_symbol *fieldname, char *value)
{
    char query[2048];
    t_symbol *tablename = x->tablename;
    t_symbol *tablenameid = table_name_to_idname(tablename);
    t_db_result	*result = NULL;
    snprintf_zero(query, 2048, "SELECT %s FROM %s WHERE %s IS %s", tablenameid->s_name, tablename->s_name, fieldname->s_name, value);
    t_max_err err = db_query(x->d_db, &result, query);
    t_distances_grain *gr = NULL;
    
    if (err)
        object_error((t_object *)x, "Error while retrieving grain! Check the fieldname and value specifications.");
    else {
        long numrecords = db_result_numrecords(result);
        long numfields = db_result_numfields_local(result);
        
        if (numrecords >= 1 && numfields >= 1) {
            long id = db_result_long_local(result, 0, 0);
            gr = distances_get_grain_from_table_id(x, id);
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


void distances_set_turtledgrain(t_distances *x, t_distances_grain *gr)
{
    long steps = (atom_gettype(&x->markov_avoid_repetition_memory) == A_SYM ? -1 : labs(atom_getlong(&x->markov_avoid_repetition_memory)));
    x->turtled_grain = gr;
    if (gr)
        llll_prependobj(x->turtled_grain_history, gr);
    if (steps >= 0 && x->turtled_grain_history->l_size > steps)
        llll_free(llll_slice(x->turtled_grain_history, steps));
}

// Beware, will modify args!!!!
// But won't free it
void distances_setturtle(t_distances *x, t_llll *args)
{
    dadaobj_mutex_lock(dadaobj_cast(x));
    if (hatom_gettype(&args->l_head->l_hatom) == H_LLLL) {
        // The grain can be the nearest grain to an (x y) value...
        t_pt pt = llll_to_pt(hatom_getllll(&args->l_head->l_hatom));
        distances_set_turtledgrain(x, distances_get_1nn(x, pt, NULL, x->relative_turtling));
    } else if (hatom_gettype(&args->l_head->l_hatom) == H_SYM) {
        // ... or the grain having a certain field set to a certain value
        char *valuestr = NULL;
        t_symbol *tablename = hatom_getsym(&args->l_head->l_hatom);
        llll_behead(args);
        llll_to_text_buf(args, &valuestr, 0, BACH_DEFAULT_MAXDECIMALS, LLLL_T_NONE, LLLL_TE_SQL_STYLE, LLLL_TB_SQL_STYLE, NULL);
        distances_set_turtledgrain(x, distances_get_grain_from_field_value(x, tablename, valuestr));
        bach_freeptr(valuestr);
    }
    dadaobj_mutex_unlock(dadaobj_cast(x));
}

void distances_anything(t_distances *x, t_symbol *msg, long ac, t_atom *av)
{
	dadaobj_anything(dadaobj_cast(x), msg, ac, av);
	
	t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, msg, ac, av, LLLL_PARSE_RETAIN);
    if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
        t_symbol *router = hatom_getsym(&parsed->l_head->l_hatom);
        llll_behead(parsed);

        if (dadaobj_anything_handle_domain_or_range(dadaobj_cast(x), router, parsed, 2)) {
            // nothing to do!
        } else if (router == gensym("getgrid")) {
            t_llllelem *rowel, *el;
            t_llll *out = llll_get();
            dadaobj_mutex_lock(dadaobj_cast(x));
            for (rowel = x->grains_grid->l_head; rowel; rowel = rowel->l_next)  {
                t_llll *rowres = llll_get();
                for (el = hatom_getllll(&rowel->l_hatom)->l_head; el; el = el->l_next)  {
                    t_llll *this_content = get_grain_contentfield(x, (t_distances_grain *)hatom_getobj(&el->l_hatom));
                    llll_appendllll(rowres, this_content, 0, WHITENULL_llll);
                }
                llll_appendllll(out, rowres);
            }
            dadaobj_mutex_unlock(dadaobj_cast(x));
            
            llll_prependsym(out, gensym("grid"), 0, WHITENULL_llll);
            llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 2, out);
            llll_free(out);
            
        } else if (router == gensym("getgraph")) {
            dadaobj_mutex_lock(dadaobj_cast(x));
            t_llll *out = graph_to_llll(&x->graph);
            llll_funall(out, subs_objs_fn, x, 1, -1, FUNALL_ONLY_PROCESS_ATOMS);
            dadaobj_mutex_unlock(dadaobj_cast(x));
            
            llll_prependsym(out, gensym("graph"), 0, WHITENULL_llll);
            llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 2, out);
            llll_free(out);

        } else if (router == gensym("knn") && parsed->l_size >= 2 && hatom_gettype(&parsed->l_head->l_hatom) == H_LONG && hatom_gettype(&parsed->l_head->l_next->l_hatom) == H_LLLL) {
            dadaobj_mutex_lock(dadaobj_cast(x));
            t_llll *grains_knn = distances_get_knn(x, hatom_getlong(&parsed->l_head->l_hatom), llll_to_pt(hatom_getllll(&parsed->l_head->l_next->l_hatom)), NULL, x->relative_knn);
            t_llllelem *elem;
            t_llll *out = llll_get();
            for (elem = grains_knn->l_head; elem; elem = elem->l_next)  {
                t_llll *this_content = get_grain_contentfield(x, (t_distances_grain *)hatom_getobj(&elem->l_hatom));
                llll_appendllll(out, this_content, 0, WHITENULL_llll);
            }
            dadaobj_mutex_unlock(dadaobj_cast(x));
            
            llll_prependsym(out, gensym("knn"), 0, WHITENULL_llll);
            llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 2, out);
            llll_free(out);
            llll_free(grains_knn);

        } else if (router == gensym("getnumgrains")) {
            t_llll *out = symbol_and_long_to_llll(gensym("numgrains"), x->grains->l_size);
            llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 2, out);
            llll_free(out);
            
        } else if (router == gensym("setturtle") && parsed->l_size >= 1) {
            // set the turtle to a given grain, without outputting the result
            
            distances_setturtle(x, parsed);
            jbox_redraw((t_jbox *)x);
            
        } else if (router == gensym("turtleclear")) {
            llll_clear(x->turtled_grain_history);
            
        } else if (router == gensym("turtlemarkov")) {
            // moving turtle to one of the neighbors
            if (move_turtle_markov(x)) {
                t_llll *end = llll_get();
                llll_appendsym(end, gensym("turtle"));
                llll_appendsym(end, _llllobj_sym_end);
                llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, end);
                llll_free(end);
            } else if (x->turtled_grain) {
                output_grain_contentfield(x, x->turtled_grain, gensym("turtle"), x->beat_sync);
            }
            jbox_redraw((t_jbox *)x);
            
        } else if (router == gensym("turtle") && parsed->l_size >= 1) {
            // set the turtle to a given grain,
            distances_setturtle(x, parsed);
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
            distances_set_turtledgrain(x, distances_get_1nn(x, pt_pt_sum(previous, delta), x->turtled_grain, x->relative_turtling));
            if (x->turtled_grain)
                output_grain_contentfield(x, x->turtled_grain, gensym("turtle"), x->beat_sync);
            jbox_redraw((t_jbox *)x);
        }
    }
    llll_free(parsed);
}

void clear_grains(t_distances *x)
{
    t_llllelem *elem;
	for (elem = x->grains->l_head; elem; elem = elem->l_next)
		bach_freeptr(hatom_getobj(&elem->l_hatom));
	llll_clear(x->grains);
	x->mousehover_grain = x->mousedown_grain = x->lastplayed_grain = NULL;
}




long sort_by_pt_distance_and_activity_fn(void *data, t_llllelem *a, t_llllelem *b)
{
    t_distances *x = (t_distances *)(((void **)data)[0]);
    t_pt coord = *((t_pt *)(((void **)data)[1]));
    
    t_distances_grain *a_gr = (t_distances_grain *)hatom_getobj(&a->l_hatom);
    t_distances_grain *b_gr = (t_distances_grain *)hatom_getobj(&b->l_hatom);
//    t_pt coord = *((t_pt *)(((void **)data)[0]));
//    t_rect relative_rect = *((t_rect *)(((void **)data)[1]));
    
    const double dist_coeff = 1.;
    const double activity_coeff = 0.;
    
    double dist_a = pt_pt_distance(a_gr->coord, coord)/x->max_dist_edge;
    double dist_b = pt_pt_distance(b_gr->coord, coord)/x->max_dist_edge;
    
    double activity_a = a_gr->prev_grid_activity;
    double activity_b = b_gr->grid_activity;
    
    double tot = (dist_b - dist_a)*dist_coeff + (activity_b - activity_a)*activity_coeff;
    return (tot >= 0);
}


void get_uniform_num_rows_cols(t_distances *x, long num_grains, long *num_rows, long *num_cols)
{
    if (x->uniform_grid_size[0] <= 0 || x->uniform_grid_size[1] <= 0) {
        long square_root = (long) sqrt(num_grains);
        for (long i = square_root; i > 0; i--) {
            if (num_grains % i == 0) {
                *num_rows = i;
                *num_cols = num_grains/i;
                return;
            }
        }
    } else {
        *num_rows = x->uniform_grid_size[0];
        *num_cols = x->uniform_grid_size[1];
    }
}



void build_grains(t_distances *x)
{
    if (!x->d_database || strlen(x->d_database->s_name) <= 0) {
//        object_error((t_object *)x, "Define a valid database name.");
        x->db_ok = false;
        return; // nothing to build

    }
    
    if (!x->tablename || strlen(x->tablename->s_name) <= 0) {
//        object_error((t_object *)x, "Define a valid table name.");
        return; // nothing to build
    }

    
    if (!x->disttablename || strlen(x->disttablename->s_name) <= 0) {
//        object_error((t_object *)x, "Define a valid distance table name.");
        return; // nothing to build
    }

	
	// QUERY:
	t_max_err	err = MAX_ERR_NONE;
	t_db_result	*result = NULL;
	
    t_symbol *distancetablename = x->disttablename;
	t_symbol *tablename = x->tablename;
	t_symbol *colorfield = x->field_color;
	t_symbol *sizefield = x->field_size;
	t_symbol *shapefield = x->field_shape;
    t_symbol *bpmfield = x->field_bpm; //x->beat_sync ? x->field_bpm : NULL;
    t_symbol *phasefield = x->field_phase; // x->beat_sync ? x->field_phase : NULL;
    t_symbol *lengthfield = x->field_length;
    t_symbol *labelfield = x->field_label;
	char colorfield_dummy = false, sizefield_dummy = false, shapefield_dummy = false, bpmfield_dummy = false, phasefield_dummy = false, lengthfield_dummy = false, labelfield_dummy = false;
	t_symbol *idname = table_name_to_idname(tablename);
	long i;
	long numrecords, numfields;

	x->field_color_is_string = x->field_size_is_string = x->field_shape_is_string = false;
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

    if (!labelfield || strlen(labelfield->s_name) == 0 || labelfield == _sym_none) {
        labelfield = idname;
        x->field_label_is_dummy = labelfield_dummy = true;
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
			for (i = 0; i < numrecords; i++) 
				field_size_unique_sym[i] = gensym(db_result_string(result, i, 0));
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
			for (i = 0; i < numrecords; i++) 
				field_color_unique_sym[i] = gensym(db_result_string(result, i, 0));
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
			for (i = 0; i < numrecords; i++) 
				field_shape_unique_sym[i] = gensym(db_result_string(result, i, 0));
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
    char query[DADA_QUERY_ALLOC_CHAR_SIZE];
    long query_alloc = DADA_QUERY_ALLOC_CHAR_SIZE;

    
    
    /// OBTAINING MAXIMUM ID OF GRAINS
    long num_idxs = 0;
    snprintf_zero(query, query_alloc, "SELECT MAX(%s) FROM %s", idname->s_name, tablename->s_name);
    if (db_query(x->d_db, &result, query) == MAX_ERR_NONE)
        num_idxs = db_result_double_local(result, 0, 0) + 1;
    object_free(result);
    result = NULL;

    /// OBTAINING IDs OF GRAINS TO BE DISPLAYED
    
    snprintf_zero(query, query_alloc, "SELECT %s FROM %s", idname->s_name, tablename->s_name);
    if (x->d_where_ac > 0) {
        char *buf = NULL;
        long size = 0;
        atom_gettext(x->d_where_ac, x->d_where_av, &size, &buf, OBEX_UTIL_ATOM_GETTEXT_SYM_NO_QUOTE);
        snprintf_zero(query + strlen(query), query_alloc - strlen(query), " WHERE %s", buf);
        sysmem_freeptr(buf);
    }
    
    err = db_query(x->d_db, &result, query);
    
    if (err)
        object_error((t_object *)x, "Error while executing query!");
    
    numrecords = db_result_numrecords(result);
    numfields = db_result_numfields_local(result);
    
    if (num_idxs > 0 && numrecords > 0 && numfields >= 1) {
        long *used_ids, *id_to_idx_map;
        long num_grains = numrecords;
        char **record = db_result_firstrecord(result);
        
        used_ids = (long *)bach_newptr(numrecords * sizeof(long));
        id_to_idx_map = (long *)bach_newptrclear(num_idxs * sizeof(long));
        
        for (i = 0; i < numrecords && record; i++) {
            long this_id = atol(record[0]);
            used_ids[i] = this_id;
            id_to_idx_map[this_id] = i;
            record = db_result_nextrecord(result);
        }
        
        // obtaining distances between ids
        t_db_result *dist_result = NULL;
        char distquery[2048];
        snprintf_zero(distquery, 2048, "SELECT %s1, %s2, distance FROM %s WHERE %s1 IN ( %s ) AND %s2 IN ( %s ) ", idname->s_name, idname->s_name, distancetablename->s_name, idname->s_name, query, idname->s_name, query);
        
        err = db_query(x->d_db, &dist_result, distquery);

        numrecords = db_result_numrecords(dist_result);
        numfields = db_result_numfields_local(dist_result);

        
        // buiding empty distance matrix
        if (x->D)
            delete x->D;
        x->D = new smat::Matrix<double>(num_grains, num_grains, 0.0);
        
        if (numfields >= 3) {
            char **record = db_result_firstrecord(dist_result);
            
            while (record) {
                long id1 = atol(record[0]);
                long id2 = atol(record[1]);
                double dist = atof(record[2]);
                
                long row = id_to_idx_map[id1];
                long column = id_to_idx_map[id2];
                if (row == column)
                    x->D->set(row, column, 0); // a distance is 0 on the same object :)
                else {
                    x->D->set(row, column, dist);
                    x->D->set(column, row, dist); // a distance is symmetric :)
                }

                record = db_result_nextrecord(dist_result);
            }

            smat::Matrix<double> *X0 = new smat::Matrix<double>(num_grains, 2, 0.0);
            for (i = 0; i < num_grains; i++) {
                X0->set(i, 0, 100 * cos(TWOPI * ((double)i/num_grains)));
                X0->set(i, 1, 100 * sin(TWOPI * ((double)i/num_grains)));
            }

            smat::Matrix<double> *X = MDS_UCF(x->D, X0, 2, x->numiter, x->random_seed);
//            X->saveTxt("/tmp/swissX1.txt");

            // add grains
            for (i = 0; i < num_grains; i++) {
                t_distances_grain *gr = (t_distances_grain *)bach_newptr(sizeof(t_distances_grain));
                double val_col, val_size, val_shape;
                long colorfield_idx = 0;
                t_db_result *inner_result = NULL;
                
                snprintf_zero(query, 2048, "SELECT %s,%s,%s,%s,%s,%s,%s FROM %s WHERE %s == %ld",
                              colorfield->s_name, sizefield->s_name, shapefield->s_name, bpmfield->s_name, phasefield->s_name, lengthfield->s_name, labelfield->s_name, tablename->s_name, idname->s_name, used_ids[i]);

                err = db_query(x->d_db, &inner_result, query);
                
                numrecords = db_result_numrecords(inner_result);
                numfields = db_result_numfields_local(inner_result);

                
                if (x->field_color_is_string) {
                    atom_setsym(&gr->field_color, db_result_symbol_local(inner_result, 0, colorfield_idx));
                    val_col = find_symbol_in_symbol_array(gr->field_color.a_w.w_sym, field_color_unique_sym, field_color_unique_sym_size);
                } else {
                    val_col = db_result_double_local(inner_result, 0, colorfield_idx);
                    atom_setfloat(&gr->field_color, val_col);
                }
                
                if (x->field_size_is_string) {
                    atom_setsym(&gr->field_size, db_result_symbol_local(inner_result, 0, colorfield_idx+1));
                    val_size = find_symbol_in_symbol_array(gr->field_size.a_w.w_sym, field_size_unique_sym, field_size_unique_sym_size);
                } else {
                    val_size = db_result_double_local(inner_result, 0, colorfield_idx+1);
                    atom_setfloat(&gr->field_size, val_size);
                }
                
                if (x->field_shape_is_string) {
                    atom_setsym(&gr->field_shape, db_result_symbol_local(inner_result, 0, colorfield_idx+1));
                    val_shape = find_symbol_in_symbol_array(gr->field_shape.a_w.w_sym, field_shape_unique_sym, field_shape_unique_sym_size);
                } else {
                    val_shape = db_result_double_local(inner_result, 0, colorfield_idx+2);
                    atom_setfloat(&gr->field_shape, val_shape);
                }
                
                gr->result_idx = i;
                gr->db_id = used_ids[i];
                gr->coord = build_pt(X->get(i, 0), X->get(i, 1));
                gr->radius_px = sizefield_dummy ? x->minradius : (min_field_size == max_field_size ? x->minradius : rescale(val_size, min_field_size, max_field_size, x->minradius, x->maxradius));
                gr->color = colorfield_dummy ? x->j_graincolor : double_to_color(val_col, min_field_color, max_field_color, false);
                gr->color.alpha = x->point_alpha/100.;
                gr->shape = shapefield_dummy ? 0 : val_shape;
                
                gr->bpm = bpmfield_dummy ? 60. : db_result_double_local(inner_result, 0, colorfield_idx+3);
                gr->phase = phasefield_dummy ? 0. : db_result_double_local(inner_result, 0, colorfield_idx+4);
                gr->length_ms = lengthfield_dummy ? 0. : db_result_double_local(inner_result, 0, colorfield_idx+5);
                gr->label = labelfield_dummy ? NULL : db_result_symbol_local(inner_result, 0, colorfield_idx+6);
                
                gr->has_uniform_grid_coord = false;
                gr->uniform_grid_coord = build_pt(0, 0);
                gr->grid_activity = gr->prev_grid_activity = 0;
                
                gr->parent = llll_appendobj(x->grains, gr);

                object_free(inner_result);
            }
            
            
            // building graph
            graph_clear(&x->graph);
            for (t_llllelem *elem = x->grains->l_head; elem; elem = elem->l_next) {
                t_distances_grain *gr = (t_distances_grain *)hatom_getobj(&elem->l_hatom);
                gr->graph_ID = graph_add_vertex(&x->graph, gr->coord, build_obj_metadata(gr));
            }
            if (x->max_dist_edge > 0.) {
                for (t_llllelem *elem = x->grains->l_head; elem; elem = elem->l_next) {
                    for (t_llllelem *elem2 = elem->l_next; elem2; elem2 = elem2->l_next) {
                        t_distances_grain *gr1 = (t_distances_grain *)hatom_getobj(&elem->l_hatom);
                        t_distances_grain *gr2 = (t_distances_grain *)hatom_getobj(&elem2->l_hatom);
                        double this_dist = x->D->get(gr1->result_idx, gr2->result_idx);
                        if (this_dist < x->max_dist_edge)
                            graph_add_edge(&x->graph, gr1->graph_ID, gr2->graph_ID, build_double_metadata(1. - this_dist/x->max_dist_edge));
                    }
                }
            }

            
            
            // computing uniform grid, if needed. This is slow!
            if (x->also_compute_uniform_grid) {
                long num_rows = 1;
                long num_cols = num_grains;
                double xmin = 0, xmax = 0, ymin = 0, ymax = 0;
                long j;
                
                get_uniform_num_rows_cols(x, num_grains, &num_rows, &num_cols);
                
                t_pt *grid_coord = (t_pt *)bach_newptr((num_rows * num_cols) * sizeof(t_pt));
                t_pt *orig_grid_coord = (t_pt *)bach_newptr((num_rows * num_cols) * sizeof(t_pt));
                t_distances_grain **grid_retracted_grains = (t_distances_grain **)bach_newptrclear((num_rows * num_cols) * sizeof(t_distances_grain *));
                
                distances_get_boundaries(x, &xmin, &xmax, &ymin, &ymax);
                
                if (isnan(xmin) || isnan(xmax) || isnan(ymin) || isnan(ymax)) {
                    distances_get_boundaries(x, &xmin, &xmax, &ymin, &ymax);
                    xmin = xmax = ymin = ymax = 0;
                    num_cols = num_rows = 1;
                }
                
                double col_width = num_cols > 1 ? (xmax - xmin)/    (num_cols - 1) : 0;
                double row_width = num_rows > 1 ? (ymax - ymin)/(num_rows - 1) : 0;
                for (i = 0; i < num_rows; i++)
                    for (j = 0; j < num_cols; j++)
                        orig_grid_coord[i * num_cols + j] = grid_coord[i * num_cols + j] = build_pt(num_cols > 1 ? xmin + col_width * j : 0.5*(xmin + xmax), num_rows > 1 ? ymin + row_width * i : 0.5*(ymin + ymax));
                
                t_llll *grains_copy = llll_clone(x->grains);
                
                
                
                // retracting the grid towards the nearest point
                double learning_rate = MAX(0.001, x->uniform_grid_learning_rate);
                double distance_account_thresh = 0.5;
                double distance_taken_thresh = 0.001;
                void *data[2];
                data[0] = x;
                
                
                t_llllelem *elem;
                for (elem = grains_copy->l_head; elem; elem = elem->l_next) {
                    t_distances_grain *gr = (t_distances_grain *)hatom_getobj(&elem->l_hatom);
                    gr->grid_activity = distances_grain_get_sum_of_weights(x, gr);
                }

                
                while (true){
/*                    t_llllelem *elem;
                    for (elem = grains_copy->l_head; elem; elem = elem->l_next) {
                        t_distances_grain *gr = (t_distances_grain *)hatom_getobj(&elem->l_hatom);
                        gr->prev_grid_activity = gr->grid_activity;
                        gr->grid_activity = distances_grain_get_sum_of_weights(x, gr);
                    }
                     */
                    char entered = false;
                    
                    for (i = 0; i < num_rows; i++) {
                        for (j = 0; j < num_cols; j++) {
                            
                            if (!grains_copy->l_head)
                                break; // done, all points have been assigned
                            
                            if (grid_retracted_grains[i * num_cols + j])
                                continue; // already captured
                            
                            entered = true;
                            
                            // choosing point towards which to go
                            data[1] = &(grid_coord[i*num_cols + j]);
                            llll_inplacesort(grains_copy, (sort_fn)sort_by_pt_distance_and_activity_fn, data);
                            t_distances_grain *chosen_grain = (t_distances_grain *)hatom_getobj(&grains_copy->l_head->l_hatom);
                            
                            grid_coord[i * num_cols + j] = pt_pt_sum(grid_coord[i * num_cols + j], pt_number_prod(pt_pt_diff(chosen_grain->coord, grid_coord[i * num_cols + j]), learning_rate));
                            
                            double new_dist = pt_pt_distance(chosen_grain->coord, grid_coord[i * num_cols + j]);
                            
                            if (new_dist < distance_taken_thresh) {
                                // done! This (i, j) has been "captured" by a grain
                                grid_retracted_grains[i * num_cols + j] = chosen_grain;
                                llll_destroyelem(grains_copy->l_head);
                                
                            }
/*                            else if (new_dist < distance_account_thresh)
                                chosen_grain->grid_activity += distance_account_thresh - new_dist; */
                        }
                    }
                    
                    if (!grains_copy->l_head || !entered)
                        break; // done, all points have been assigned
                }
                
                for (i = 0; i < num_rows; i++) {
                    for (j = 0; j < num_cols; j++) {
                        if (grid_retracted_grains[i * num_cols + j]) {
                            grid_retracted_grains[i * num_cols + j]->uniform_grid_coord = orig_grid_coord[i * num_cols + j];
                        }
                    }
                }
                
                llll_clear(x->grains_grid);
                for (i = 0; i < num_rows; i++) {
                    t_llll *grid_row = llll_get();
                    for (j = 0; j < num_cols; j++)
                        llll_appendobj(grid_row, grid_retracted_grains[i * num_cols + j]);
                    llll_appendllll(x->grains_grid, grid_row);
                }
                llll_rev(x->grains_grid, 1, 1);
                
                bach_freeptr(grid_coord);
                bach_freeptr(orig_grid_coord);
                bach_freeptr(grid_retracted_grains);
            }
            
            
            delete X;
        }
        
        object_free(dist_result);
        
        bach_freeptr(used_ids);
        bach_freeptr(id_to_idx_map);
    }

    object_free(result);
	
	if (field_color_unique_sym)
		bach_freeptr(field_color_unique_sym);
	if (field_size_unique_sym)
		bach_freeptr(field_size_unique_sym);
	if (field_shape_unique_sym)
		bach_freeptr(field_shape_unique_sym);
}

t_pt distances_get_grain_pt(t_distances *x, t_pt center, t_distances_grain *gr)
{
    t_pt orig_pt = coord_to_pix(dadaobj_cast(x), center, gr->coord);
    t_pt uniform_grid_pt = coord_to_pix(dadaobj_cast(x), center, gr->uniform_grid_coord);
    
    return pt_pt_sum(orig_pt, pt_number_prod(pt_pt_diff(uniform_grid_pt, orig_pt), x->align_to_uniform_grid));

}

t_pt distances_get_grain_coord(t_distances *x, t_distances_grain *gr)
{
    t_pt orig_coord = gr->coord;
    t_pt uniform_grid_coord = gr->uniform_grid_coord;
    
    return pt_pt_sum(orig_coord, pt_number_prod(pt_pt_diff(uniform_grid_coord, orig_coord), x->align_to_uniform_grid));
    
}


//// GRAPHIC DRAWING
void distances_paint_grains(t_distances *x, t_jgraphics *g, t_object *view, t_rect rect, t_pt center, t_jfont *jf_labels)
{
	
	char use_layers = false;

	if (!g) {
 		use_layers = true;
		g = jbox_start_layer((t_object *)x, view, gensym("grains"), rect.width, rect.height);
	}
	
	if (g){
        t_jrgba edgecolor = x->j_edgecolor;
		t_llllelem *elem;
        
        if (x->show_edges) {
            if (x->max_dist_edge > 0.) {
                t_llllelem *elem2;
                for (elem = x->grains->l_head; elem; elem = elem->l_next) {
                    for (elem2 = elem->l_next; elem2; elem2 = elem2->l_next) {
                        t_distances_grain *gr1 = (t_distances_grain *)hatom_getobj(&elem->l_hatom);
                        t_distances_grain *gr2 = (t_distances_grain *)hatom_getobj(&elem2->l_hatom);
                        double this_dist = x->D->get(gr1->result_idx, gr2->result_idx);
                        if (this_dist < x->max_dist_edge) {
                            t_pt pix1 = distances_get_grain_pt(x, center, gr1);
                            t_pt pix2 = distances_get_grain_pt(x, center, gr2);
                            paint_line(g, build_jrgba(edgecolor.red, edgecolor.green, edgecolor.blue, edgecolor.alpha * (1. - this_dist/x->max_dist_edge)), pix1.x, pix1.y, pix2.x, pix2.y, 1);
                        }
                    }
                }
                
            }
        }
        
        if (x->show_grains) {
            for (elem = x->grains->l_head; elem; elem = elem->l_next) {
                t_distances_grain *gr = (t_distances_grain *)hatom_getobj(&elem->l_hatom);
                t_pt pt = distances_get_grain_pt(x, center, gr);
                
                if (pt.x + gr->radius_px >= 0 && pt.x - gr->radius_px <= rect.width &&
                    pt.y + gr->radius_px >= 0 && pt.y - gr->radius_px <= rect.height) {
                    
                    if (gr->shape <= 0)
                        paint_circle_filled(g, gr->color, pt.x, pt.y, gr->radius_px);
                    else
                        paint_regular_polygon(g, gr->shape + 2, NULL, &gr->color, pt, gr->radius_px, 1);
                }
                
                /*            t_pt uniform_grid_pt = coord_to_pix(dadaobj_cast(x), center, gr->uniform_grid_coord);
                 paint_circle_filled(g, gr->color, uniform_grid_pt.x, uniform_grid_pt.y, 2);
                 paint_dashed_line(g, gr->color, pt.x, pt.y, uniform_grid_pt.x, uniform_grid_pt.y, 0.5, 3);
                 */
                if (x->paint_labels && gr->label)
                    write_text_standard(g, jf_labels, DADA_GREY_25, gr->label->s_name, pt.x + gr->radius_px, pt.y + gr->radius_px, 200, 200);
                
            }
        }
     
		
		if (use_layers)
			jbox_end_layer((t_object *)x, view, gensym("grains"));
	}
	
	if (use_layers)
		jbox_paint_layer((t_object *)x, view, gensym("grains"), 0., 0.);	// position of the layer
}


char *distances_atom_to_string(t_atom *a, long max_decimals)
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
        long len = strlen(res);
        if (len > 0) {
            if (res[len-1] == ' ')
                res[len-1] = 0;
            if (res[len-1] == '.')
                res[len-1] = 0;
        }
		return res;
	}
}

void rebuild_grains(t_distances *x, char preserve_turtle)
{
    dadaobj_mutex_lock(dadaobj_cast(x));
    // preserve turtle?
    long graph_ID = x->turtled_grain ? x->turtled_grain->graph_ID : -1;
    clear_grains(x);
    build_grains(x);
    if (preserve_turtle && graph_ID >= 0 && graph_ID < x->graph.num_vertices)
        distances_set_turtledgrain(x, (t_distances_grain *)x->graph.vertices[graph_ID].data.m_obj);
    else
        distances_set_turtledgrain(x, NULL);
    x->need_rebuild_grains = false;
    if (x->autozoom)
        dadaobj_cast(x)->m_zoom.must_autozoom = true;
    dadaobj_mutex_unlock(dadaobj_cast(x));
    llllobj_outlet_symbol_as_llll((t_object *)x, LLLL_OBJ_UI, 2, _sym_done);
}


void rebuild_grains_defer_low_do(t_distances *x, t_symbol *msg, long ac, t_atom *av)
{
    rebuild_grains(x, ac ? atom_getlong(av) : 0);
}

void rebuild_grains_defer_low(t_distances *x, char preserve_turtle)
{
    t_atom av;
    atom_setlong(&av, preserve_turtle);
    defer_low(x, (method)rebuild_grains_defer_low_do, NULL, 1, &av);
}



void distances_paint_ext(t_distances *x, t_object *view, t_dada_force_graphics *force_graphics)
{
	t_jgraphics *g = force_graphics->graphic_context;
	t_rect rect = force_graphics->rect;
	t_pt center = force_graphics->center_pix;
	t_jfont *jf = jfont_create_debug("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, x->legend_text_size);
    t_jfont *jf_labels = jfont_create_debug("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, x->labels_text_size);

    if (!x->db_ok) {
        dadaobj_paint_background(dadaobj_cast(x), g, &rect);
        write_text(g, jf, DADA_GREY_50, "(must set 'database', 'table' & 'distancetable' attributes)", 0, 0, rect.width, rect.height, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, true, true);
        return;
    }  else if (!x->tablename || strlen(x->tablename->s_name) == 0 || !x->disttablename || strlen(x->disttablename->s_name) == 0) {
        dadaobj_paint_background(dadaobj_cast(x), g, &rect);
        write_text(g, jf, DADA_GREY_50, "(must set both 'table' and 'distancetable' attributes)", 0, 0, rect.width, rect.height, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, true, true);
        return;
    }

    dadaobj_getdomain(dadaobj_cast(x), view, &x->domain_min, &x->domain_max, force_graphics);
    dadaobj_getrange(dadaobj_cast(x), view, &x->range_min, &x->range_max, force_graphics);

    dadaobj_paint_background(dadaobj_cast(x), g, &rect);

    dadaobj_mutex_lock(dadaobj_cast(x));

    dadaobj_paint_grid(dadaobj_cast(x), view, force_graphics); // axis are inside here

	// grains
    distances_paint_grains(x, view ? NULL : force_graphics->graphic_context, view, rect, center, jf_labels);
	
    // painting turtle, if any
    if (x->show_turtle && x->turtled_grain) {
        t_pt pt = distances_get_grain_pt(x, center, x->turtled_grain);
        paint_hexagon(g, &x->j_turtlecolor, NULL, pt, x->turtled_grain->radius_px + 4, 2, true);
    }
    
	// painting mousehover, if any
	if (x->mousehover_grain) {
		t_pt pt = distances_get_grain_pt(x, center, x->mousehover_grain);
		paint_circle_stroken(g, DADA_BLACK, pt.x, pt.y, x->mousehover_grain->radius_px + DADA_DISTANCES_INTERFACE_GRAIN_TOLERANCE, 1);
		
		if (x->show_legend) {
            char legend[1024];
            char *str_x = distances_atom_to_string(&x->mousehover_grain->field_x, 2), *str_y = distances_atom_to_string(&x->mousehover_grain->field_y, 2);
            snprintf_zero(legend, 1024, "ID %ld", x->mousehover_grain->db_id);
            bach_freeptr(str_x);
            bach_freeptr(str_y);
			
            if (!x->field_size_is_dummy) {
				char *str_size = distances_atom_to_string(&x->mousehover_grain->field_size, 2);
				snprintf_zero(legend + strlen(legend), 1024 - strlen(legend), ", %s %s", x->field_size->s_name, str_size);
				bach_freeptr(str_size);
			}
			if (!x->field_color_is_dummy) {
				char *str_color = distances_atom_to_string(&x->mousehover_grain->field_color, 2);
				snprintf_zero(legend + strlen(legend), 1024 - strlen(legend), ", %s %s", x->field_color->s_name, str_color);
				bach_freeptr(str_color);
			}
			if (!x->field_shape_is_dummy) {
				char *str_shape = distances_atom_to_string(&x->mousehover_grain->field_shape, 2);
				snprintf_zero(legend + strlen(legend), 1024 - strlen(legend), ", %s %s", x->field_shape->s_name, str_shape);
				bach_freeptr(str_shape);
			}
			write_text(g, jf, x->j_legendcolor, legend, 5, 5, rect.width - 10, rect.height - 10, JGRAPHICS_TEXT_JUSTIFICATION_RIGHT | JGRAPHICS_TEXT_JUSTIFICATION_TOP, true, true);
		}
	}
	
    dadaobj_mutex_unlock(dadaobj_cast(x));

    dadaobj_paint_border(dadaobj_cast(x), g, &rect);

	jfont_destroy(jf);
    jfont_destroy(jf_labels);
}

void distances_paint(t_distances *x, t_object *view)
{
    if (x->need_rebuild_grains) {
        rebuild_grains(x, true);
    }
    
    if (view && dadaobj_cast(x)->m_zoom.must_autozoom) {
        distances_autozoom_do(x, view);
        dadaobj_cast(x)->m_zoom.must_autozoom = false;
    }
    
    dadaobj_paint(dadaobj_cast(x), view);
}

void distances_get_boundaries(t_distances *x, double *min_x, double *max_x, double *min_y, double *max_y)
{
    if (!x->grains || !x->grains->l_head)
        return;

    
    t_llllelem *elem;
    t_distances_grain *gr = (t_distances_grain *)hatom_getobj(&x->grains->l_head->l_hatom);
    *max_x = gr->coord.x; *min_x = gr->coord.x; *max_y = gr->coord.y; *min_y = gr->coord.y;

    for (elem = x->grains->l_head->l_next; elem; elem = elem->l_next) {
        t_distances_grain *gr = (t_distances_grain *)hatom_getobj(&elem->l_hatom);
        if (!isnan(gr->coord.x) && gr->coord.x > *max_x)
            *max_x = gr->coord.x;
        if (!isnan(gr->coord.y) && gr->coord.y > *max_y)
            *max_y = gr->coord.y;
        if (!isnan(gr->coord.x) && gr->coord.x < *min_x)
            *min_x = gr->coord.x;
        if (!isnan(gr->coord.y) && gr->coord.y < *min_y)
            *min_y = gr->coord.y;
    }
}

void distances_autozoom_do(t_distances *x, t_object *view)
{
	t_rect rect;
	
	jbox_get_rect_for_view((t_object *)x, view, &rect);
//	center = get_center_pix(dadaobj_cast(x), view, &rect);

	
	if (!x->grains || !x->grains->l_head)
		return;
	
	systhread_mutex_lock(x->b_ob.d_ob.l_mutex);

	// Initialize
	t_distances_grain *gr = (t_distances_grain *)hatom_getobj(&x->grains->l_head->l_hatom);
	double max_x = gr->coord.x, min_x = gr->coord.x, max_y = gr->coord.y, min_y = gr->coord.y;

	
    t_llllelem *elem;
    for (elem = x->grains->l_head->l_next; elem; elem = elem->l_next) {
        t_distances_grain *gr = (t_distances_grain *)hatom_getobj(&elem->l_hatom);
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
    
    // adding pads
    max_x += (max_x - min_x) * 0.05;
    min_x -= (max_x - min_x) * 0.05;
    max_y += (max_y - min_y) * 0.05;
    min_y -= (max_y - min_y) * 0.05;

    // equalizing zooms
    double zoom_x = (max_x - min_x)/rect.width;
    double zoom_y = (max_y - min_y)/rect.height;
    
    if (zoom_y < zoom_x) {
        double diff = (zoom_x - zoom_y) * rect.height;
        max_y += diff/2.;
        min_y -= diff/2.;
    } else if (zoom_x < zoom_y) {
        double diff = (zoom_y - zoom_x) * rect.width;
        max_x += diff/2.;
        min_x -= diff/2.;
    }

	systhread_mutex_unlock(x->b_ob.d_ob.l_mutex);

    dadaobj_setdomain(dadaobj_cast(x), view, min_x, max_x);
    dadaobj_setrange(dadaobj_cast(x), view, min_y, max_y);
}



///////// POPUP MENU FUNCTIONS
/*

void popup_clear(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_distances *x = (t_distances *)d_ob->orig_obj;
	distances_clear(x, false);
}

void popup_evolve(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_distances *x = (t_distances *)d_ob->orig_obj;
	distances_bang(x);
}

void popup_random(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_distances *x = (t_distances *)d_ob->orig_obj;
	distances_random(x, hatom_getlong(&address->l_tail->l_hatom) == 3 ? 1 : 0, DADA_LIFE_DEFAULT_RANDOM_DENSITY, false) ;
}

void show_bg_popup_menu(t_distances *x, t_object *patcherview, t_pt pt, long modifiers)
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
t_llll *get_grain_contentfield(t_distances *x, t_distances_grain *gr)
{
	t_max_err	err = MAX_ERR_NONE;
	t_symbol *tablename = x->tablename;
	t_symbol *idname = table_name_to_idname(tablename);
	
	char query[256];
    long f;
    t_llll *out = llll_get();
    
    if (!gr)
        return out;
    
    for (f = 0; f < x->field_content_size; f++) {
        t_db_result	*result = NULL;
        snprintf_zero(query, 256, "SELECT %s FROM %s WHERE %s = %ld", x->field_content[f]->s_name, tablename->s_name, idname->s_name, gr->db_id);
        err = db_query(x->d_db, &result, query);
        
        long type = distances_colname_to_coltype(x, tablename, x->field_content[f]);
        
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
    }
	return out;
}

void distances_loop_tick(t_distances *x)
{
    if (x->lastplayed_grain)
        output_grain_contentfield(x, x->lastplayed_grain, x->seq_router, 3);
    // schedule another metronome tick
//    clock_fdelay(x->m_clock, x->m_interval);
}

void distances_send_grain(t_distances *x, t_symbol *s, long argc, t_atom *argv)
{
    if (x->lastplayed_grain)
        output_grain_contentfield(x, x->lastplayed_grain, atom_getsym(argv), atom_getlong(argv+1));
}

// mode = 0, MAIN THREAD; mode = 1: BEAT SYNC; mode = 2: SCHEDULER WITH DELAY = 0, mode = 3: SCHEDULED WITH DELAY > 0
void output_grain_contentfield(t_distances *x, t_distances_grain *gr, t_symbol *router, char mode)
{
    t_llll *out = gr ? get_grain_contentfield(x, gr) : symbol2llll(_llllobj_sym_none);
	
    if (out) {
        llll_prependsym(out, router, 0, WHITENULL_llll);
        x->lastplayed_grain = gr;
        
        setclock_unset(x->b_ob.d_ob.m_play.setclock->s_thing, x->loop_clock);
        
        switch (mode) {
            case 1:
                distances_schedule_interface_grain_llll(x, gr, out);
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


t_distances_grain *pix_to_grain(t_distances *x, t_pt center, t_pt pix)
{
	t_llllelem *elem;
	for (elem = x->grains->l_head; elem; elem = elem->l_next) {
		t_distances_grain *gr = (t_distances_grain *)hatom_getobj(&elem->l_hatom);
		t_pt pix1 = distances_get_grain_pt(x, center, gr);
		double radius = gr->radius_px + DADA_DISTANCES_INTERFACE_GRAIN_TOLERANCE;
		if (pt_pt_distance_squared(pix, pix1) < radius * radius)
			return gr; 
	}
	return NULL;
}

t_distances_grain *pix_to_grain_from_view(t_distances *x, t_object *patcherview, t_pt pix)
{
	t_rect rect;
	t_pt center;
	jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
	center = get_center_pix(dadaobj_cast(x), patcherview, &rect);
	
	return pix_to_grain(x, center, pix);
}

void distances_focusgained(t_distances *x, t_object *patcherview) {
	if (dadaobj_focusgained(dadaobj_cast(x), patcherview))
		return;
}

void distances_focuslost(t_distances *x, t_object *patcherview) {
	if (dadaobj_focuslost(dadaobj_cast(x), patcherview))
		return;
	dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
}
							 
void do_send_llll(t_distances *x, t_symbol *s, long ac, t_atom *av)
{
	t_llll *ll = (t_llll *) av[0].a_w.w_obj;
	llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, ll);
	llll_free(ll);
}
							 
							 
void distances_schedule_interface_grain_llll(t_distances *x, t_distances_grain *gr, t_llll *ll)
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

void distances_mousemove(t_distances *x, t_object *patcherview, t_pt pt, long modifiers) {

	llll_format_modifiers(&modifiers, NULL);
	if (dadaobj_mousemove(dadaobj_cast(x), patcherview, pt, modifiers))
		return;

	t_distances_grain *new_mousehover_grain = NULL;
	if (x->b_ob.d_ob.m_interface.allow_mouse_hover) 
		 new_mousehover_grain = pix_to_grain_from_view(x, patcherview, pt);
	
    
	if (new_mousehover_grain != x->mousehover_grain) {
		x->mousehover_grain = new_mousehover_grain;
		
        if (new_mousehover_grain)
			output_grain_contentfield(x, new_mousehover_grain, gensym("hover"), x->beat_sync);
		else {
			t_llll *ll = llll_get();
			llll_appendsym(ll, gensym("hover"), 0, WHITENULL_llll);
			llll_appendsym(ll, _sym_none, 0, WHITENULL_llll);
			llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, ll);

            if (x->interrupt_looping_when_not_hovering) {
                x->lastplayed_grain = NULL;
                setclock_unset(x->b_ob.d_ob.m_play.setclock->s_thing, x->loop_clock);
            }
		}
        
		jbox_redraw((t_jbox *)x);
	}

}


void distances_mousedown(t_distances *x, t_object *patcherview, t_pt pt, long modifiers){

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
		distances_mousedrag(x, patcherview, pt, modifiers);
*/
}

void distances_mouseup(t_distances *x, t_object *patcherview, t_pt pt, long modifiers){
	x->mousedown_grain = NULL;
	llll_format_modifiers(&modifiers, NULL);
	
	if (dadaobj_mouseup(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
}

void distances_mousedrag(t_distances *x, t_object *patcherview, t_pt pt, long modifiers){

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
					distances_set_cell_from_mousedrag(x, i, j, modifiers);
		} else
			distances_set_cell_from_mousedrag(x, round(coord.x), round(coord.y), modifiers);
		
			jbox_invalidate_layer((t_object *)x, NULL, gensym("world"));
		jbox_redraw((t_jbox *)x);
	}
*/
}

long distances_keyup(t_distances *x, t_object *patcherview, long keycode, long modifiers, long textcharacter){
			
	llll_format_modifiers(&modifiers, &keycode);

	if (dadaobj_keyup(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
		return 1;
	
	return 0;
}

long distances_key(t_distances *x, t_object *patcherview, long keycode, long modifiers, long textcharacter){
	llll_format_modifiers(&modifiers, &keycode);
	
	if (dadaobj_key(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
		return 1;

	switch (keycode) {
		case JKEY_TAB:
			distances_autozoom_do(x, patcherview);
			return 1;
		default:
			break;
	} 
	return 0;
}

void distances_mousewheel(t_distances *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc){
	llll_format_modifiers(&modifiers, NULL);  
	
	if (dadaobj_mousewheel(dadaobj_cast(x), view, pt, modifiers, x_inc, y_inc)) {
		distances_iar(x);
		return;
	}
}

void distances_mouseenter(t_distances *x, t_object *patcherview, t_pt pt, long modifiers) 
{
    if (x->interrupt_beatsync_on_mouseleave && x->beat_sync) {
        setclock_fdelay(x->b_ob.d_ob.m_play.setclock->s_thing, x->b_ob.d_ob.m_play.m_clock, 0);
    }

	if (dadaobj_mouseenter(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
}

void distances_mouseleave(t_distances *x, t_object *patcherview, t_pt pt, long modifiers) 
{
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
void distances_undo_postprocess(t_distances *x)
{
	jbox_invalidate_layer((t_object *)x, NULL, gensym("sampling_points"));
	process_change(x);
	jbox_redraw((t_jbox *)x);
}


void distances_undo_step_push_sampling_points(t_distances *x, t_symbol *operation)
{
	undo_add_interface_step(dadaobj_cast(x), DADA_FUNC_v_oX, (method)distances_set_sampling , NULL, DADA_FUNC_X_o, (method)distances_get_sampling, NULL, operation);
}
*/




