/**
	@file
	dada.nodes.c
	
	@name
	dada.nodes
	
	@realname 
	dada.nodes

	@type
	object
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
	Interpolate pitches with a 2D interface
	
	@description
	Displays pitches in a 2-dimensional space, and interpolates between them
	
	@discussion
	Some pitch nodes are defined inside the 2d space, each node has some coordinates, a pitch and a velocity.
	The pitch in each point of the 2d space is given as a result of a inverse distance weighting interpolation
	of all pitches. Some test cursor are then defined, which can be moved around the space in order to retrieve
	information about pitch and velocity.
 
	@category
	dada, dada interfaces, dada geometry

	@keywords
	node, distance, surface, pitch, explore, node, interpolate
	
	@seealso
	bach.tonnetz, nodes
	
	@owner
	Daniele Ghisi
*/


#include "dada.interface.h"
#include "dada.geometry.h"
#include "dada.paint.h"
#include "notation/notation.h"
//#include "dada.cursors.data.c"
#include "dada.math.h"
#include "dada.popupmenu.h"
#include "dada.undo.h"

#define DADA_NODES_MAX_NODES 64				///< Maximum number of pitch nodes allowed
											///  Must be less than or equal to 64 (otherwise change the #t_nodes_bitfield declaration) 
#define DADA_NODES_MAX_TESTERS 4			///< Maximum number of test cursors allowed
											///  Must be less than or equal to 64 (otherwise change the #t_nodes_bitfield declaration) 

#define DADA_NODES_ROTATION_INTERFACE_FACTOR (2 * TWO_PI)
#define DADA_NODES_VERTEX_SELECTION_RADIUS 10
#define DADA_NODES_NODE_SELECTION_PAD 4
#define DADA_NODES_TESTER_SELECTION_PAD 4
#define DADA_NODES_DEFAULT_TONEDIVISION 4

#define DADA_NODES_NOTEPOPUP_WIDTH 50
#define DADA_NODES_NOTEPOPUP_HEIGHT 70

 
typedef t_uint64 t_nodes_bitfield;		///< A bitfield with each bit corresponding to a pitch node


////////////////////////// structures

typedef enum _nodes_element_types 
{
	DADA_NODES_ELEMENT_NONE = 0,			///< No shape
	DADA_NODES_ELEMENT_NODE = -10,			///< A pitch node
	DADA_NODES_ELEMENT_TESTER = -11,		///< A test cursor
} e_nodes_element_types;


typedef enum _nodes_pitch_display_type
{
	DADA_NODES_PITCH_DISPLAY_NONE = 0,		///< Don't display pitch nodes
	DADA_NODES_PITCH_DISPLAY_POINT = 1,		///< Display a single point
	DADA_NODES_PITCH_DISPLAY_NOTENAME = 2,	///< Display the note name
	DADA_NODES_PITCH_DISPLAY_NOTE = 3,		///< Display the whole note
} e_nodes_pitch_display_type;



typedef struct _nodes_node
{
	t_pt				coord;					///< Coordinates of the pitch node
	double				pitch_mc;				///< Pitch associated to the node
	long				velocity;				///< Velocity associated to the node
	
	// display stuff
	t_rect		node_rect;						///< Coordinates of the displayed note rectangle
} t_nodes_node;

typedef struct _nodes_tester
{
	t_pt				coord;					///< Coordinates of the tester
	long				channel;				///< MIDIchannel of the tester
} t_nodes_tester;

typedef struct _nodes 
{
	t_dadaobj_jbox		b_ob; // root object
	
	// nodes
	long				num_nodes;						///< The number of pitch nodes
	t_nodes_node		nodes[DADA_NODES_MAX_NODES];	///< The pitch nodes
	
	// test cursor and playback
	long				num_testers;
	t_nodes_tester		testers[DADA_NODES_MAX_TESTERS];
	long				tonedivision;

	// display
	e_nodes_pitch_display_type	show_nodes;	///< How do we show pitches?
	char			show_testers;
	double			min_pitch;	///< Minimum displayed pitch in midicents (associated with the #min_color)
	double			max_pitch;	///< Maximum displayed pitch in midicents (associated with the #max_color)
	char			show_velocity;

	//	behavior
	double			p;						///< Exponent for the inverse distance formula
	char			fastpow;				///< Use fastpow() instead of pow()
											// To do: http://martin.ankerl.com/2012/01/25/optimized-approximative-pow-in-c-and-cpp/
											// Doesn't work for little endian??
	
	// display
	t_jrgba			j_testercolor;
	double			node_size;
	double			tester_size;

	// interface
	t_nodes_bitfield		selected_nodes;		///< bitfield telling which nodes are selected
	t_nodes_bitfield		selected_testers;	///< bitfield telling which test cursors are selected
	
	// preset fields
	t_atom		*preset_av;		
	long		preset_ac;		

	// utilities
	char			firsttime;
	char			itsme;
	char			creating_new_obj;
	
	long			n_in;   // space for the inlet number used by all the proxies
    void			*n_proxy1;
	
	// outlets are declared in the dadaobj->llllobj structure, at the beginning
} t_nodes;



///////////////////////// function prototypes
//// standard set
void *nodes_new(t_symbol *s, long argc, t_atom *argv);
void nodes_free(t_nodes *x);
void nodes_assist(t_nodes *x, void *b, long m, long a, char *s);

void nodes_paint(t_nodes *x, t_object *view);
void nodes_paint_ext(t_nodes *x, t_object *view, t_dada_force_graphics *force_graphics);


void nodes_int(t_nodes *x, t_atom_long num);
void nodes_float(t_nodes *x, double num);
void nodes_anything(t_nodes *x, t_symbol *msg, long ac, t_atom *av);
void nodes_bang(t_nodes *x);


// get/set status
void nodes_set_state(t_nodes *x, t_llll *state);
t_llll *nodes_get_state(t_nodes *x, char get_nodes, char get_testers);

t_llll *nodes_get_geometry(t_nodes *x);
t_llll *nodes_get_shapes(t_nodes *x);
t_llll *nodes_get_sampling(t_nodes *x);
void nodes_set_geometry(t_nodes *x, t_llll *geometry);
void nodes_set_shapes(t_nodes *x, t_llll *shapes);
void nodes_set_sampling(t_nodes *x, t_llll *sampling);


// interface
void nodes_focusgained(t_nodes *x, t_object *patcherview);
void nodes_focuslost(t_nodes *x, t_object *patcherview);
void nodes_mousedown(t_nodes *x, t_object *patcherview, t_pt pt, long modifiers);
void nodes_mousemove(t_nodes *x, t_object *patcherview, t_pt pt, long modifiers);
void nodes_mouseup(t_nodes *x, t_object *patcherview, t_pt pt, long modifiers);
void nodes_mousedrag(t_nodes *x, t_object *patcherview, t_pt pt, long modifiers);
long nodes_key(t_nodes *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
long nodes_keyup(t_nodes *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
void nodes_mousewheel(t_nodes *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc);

void nodes_mouseenter(t_nodes *x, t_object *patcherview, t_pt pt, long modifiers);
void nodes_mouseleave(t_nodes *x, t_object *patcherview, t_pt pt, long modifiers);

t_max_err nodes_notify(t_nodes *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void nodes_jsave(t_nodes *x, t_dictionary *d);
void nodes_preset(t_nodes *x);
void nodes_begin_preset(t_nodes *x, t_symbol *s, long argc, t_atom *argv);
void nodes_restore_preset(t_nodes *x, t_symbol *s, long argc, t_atom *argv);
void nodes_end_preset(t_nodes *x);

t_max_err nodes_setattr_tonedivision(t_nodes *x, t_object *attr, long ac, t_atom *av);

void nodes_undo_step_push_nodes(t_nodes *x, t_symbol *operation);
void nodes_undo_postprocess(t_nodes *x);

void process_change(t_nodes *x);
double get_pitch_at_coord(t_nodes *x, t_pt coord, double *velocity);






///////////////////////// utility functions


void send_tester(t_nodes *x)
{
	t_llll *ll = llll_get();
	double velocity = 0;
	
	llll_appenddouble(ll, get_pitch_at_coord(x, x->testers[0].coord, &velocity), 0, WHITENULL_llll);
	llll_appenddouble(ll, velocity, 0, WHITENULL_llll);
	llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, ll);
	llll_free(ll);
}

// process any change which has happened for the shapes
void process_change(t_nodes *x)
{
//	if (!x->creating_new_obj)
//		llllobj_outlet_bang((t_object *)x, LLLL_OBJ_UI, 3);
	
	jbox_redraw((t_jbox *)x);
}


// idx is 0-based (1st bit is 0)
void shift_bitfield(t_nodes_bitfield *field, long idx, long shift)
{
	*field = ((((*field >> (idx + shift)) << (idx + shift)) ^ *field) | ((*field >> idx) << (idx + shift)));
}


long add_node_do(t_nodes *x, t_pt coord, double MIDIcents, long velocity)
{
	long num_nodes = x->num_nodes;
	if (num_nodes + 1 < DADA_NODES_MAX_NODES) {
		x->nodes[num_nodes].coord = coord;
		x->nodes[num_nodes].pitch_mc = MIDIcents;
		x->nodes[num_nodes].velocity = velocity;
		x->num_nodes++;
		return num_nodes;
	}
	return -1;
}

long add_node(t_nodes *x, t_pt coord, double MIDIcents, long velocity)
{
	nodes_undo_step_push_nodes(x, gensym("Add Node"));
	char res = add_node_do(x, coord, MIDIcents, velocity);
	jbox_invalidate_layer((t_object *)x, NULL, gensym("surface"));
	process_change(x);
	return res;
}

long add_node_from_llll(t_nodes *x, t_llll *node)
{
    t_pt coord = build_pt(0, 0);
    double pitch = 6000;
    long vel = 100;
    dadaobj_parseargs(dadaobj_cast(x), node, (char *)"Pdl", gensym("coord"), &coord, gensym("pitch"), &pitch, gensym("vel"), &vel);
    return add_node(x, coord, pitch, vel);
}



// returns 0 if succesful, -1 otherwise
char delete_node_do(t_nodes *x, long idx)
{
	if (idx >= 0 && idx < x->num_nodes) {
		if (idx < x->num_nodes - 1) {
			sysmem_copyptr(&x->nodes[idx + 1], &x->nodes[idx], (x->num_nodes - idx - 1) * sizeof(t_nodes_node));
			shift_bitfield(&x->selected_nodes, idx + 1, -1); 
		}
		
		if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_NODES_ELEMENT_NODE && x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx == idx) {
			x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADA_NODES_ELEMENT_NONE;
			x->b_ob.d_ob.m_interface.mousemove_item_identifier.flag = 0;
		}
		
		if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADA_NODES_ELEMENT_NODE && x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx == idx) {
			x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADA_NODES_ELEMENT_NONE;
			x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag = 0;
		}
		
		x->num_nodes--;
		return 0;
	}
	return -1;
}

char delete_node(t_nodes *x, long main_idx)
{
	nodes_undo_step_push_nodes(x, gensym("Delete Node"));
	char res = delete_node_do(x, main_idx);
	jbox_invalidate_layer((t_object *)x, NULL, gensym("surface"));
	process_change(x);
	return res;
}

void delete_selected_nodes(t_nodes *x) 
{
	long i;
	nodes_undo_step_push_nodes(x, gensym("Delete Selected Nodes"));
	for (i = 0; i < x->num_nodes; i++)
		if (x->selected_nodes & (1 << i)) { 
			if (!delete_node_do(x, i))
				i--;
		}
	
	x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADA_NODES_ELEMENT_NONE;
	x->selected_nodes = 0;
	jbox_invalidate_layer((t_object *)x, NULL, gensym("surface"));
	process_change(x);
	
}


long find_max_midichannel(t_nodes *x)
{
	long i, max = 0;
	for (i = 1; i < x->num_testers; i++) {
		if (x->testers[i].channel > max)
			max = x->testers[i].channel;
	}
	return max;
}


// returns the new node index if succesful, -1 otherwise
long duplicate_node(t_nodes *x, long idx)
{
	if (idx >= 0 && idx < x->num_nodes && x->num_nodes + 1 < DADA_NODES_MAX_NODES) {
		
		nodes_undo_step_push_nodes(x, gensym("Duplicate Node"));

		x->nodes[x->num_nodes].velocity = x->nodes[idx].velocity;
		x->nodes[x->num_nodes].pitch_mc = x->nodes[idx].pitch_mc;
		x->nodes[x->num_nodes].coord = x->nodes[idx].coord;
		
		x->num_nodes ++;
		
		return x->num_nodes - 1;
	}
	return -1;
}



void move_node_delta(t_nodes *x, t_nodes_node *node, t_pt delta)
{
	nodes_undo_step_push_nodes(x, gensym("Move Node"));
	node->coord = pt_pt_sum(node->coord, delta);
	jbox_invalidate_layer((t_object *)x, NULL, gensym("surface"));
	process_change(x);
}


void move_all_nodes_delta(t_nodes *x, t_pt delta)
{
	long i;
	nodes_undo_step_push_nodes(x, gensym("Move All Nodes"));
	for (i = 0; i < x->num_nodes; i++)
		x->nodes[i].coord = pt_pt_sum(x->nodes[i].coord, delta);
	jbox_invalidate_layer((t_object *)x, NULL, gensym("surface"));
	process_change(x);
}



void move_selected_nodes_delta(t_nodes *x, t_pt delta)
{
	long i;
	
	if (x->selected_nodes == 0)
		return;
	
	nodes_undo_step_push_nodes(x, gensym("Move Selected Nodes"));
	
	for (i = 0; i < x->num_nodes; i++)
		if (x->selected_nodes & (1 << i))
			x->nodes[i].coord = pt_pt_sum(x->nodes[i].coord, delta);
	jbox_invalidate_layer((t_object *)x, NULL, gensym("surface"));
	process_change(x);
}


void move_node(t_nodes *x, t_nodes_node *node, t_pt new_coord)
{
	nodes_undo_step_push_nodes(x, gensym("Move Node"));
	node->coord = new_coord;
	jbox_invalidate_layer((t_object *)x, NULL, gensym("surface"));
	process_change(x);
}


void move_all_nodes(t_nodes *x, t_pt new_coord)
{
	long i;
	nodes_undo_step_push_nodes(x, gensym("Move All Nodes"));
	for (i = 0; i < x->num_nodes; i++)
		x->nodes[i].coord = new_coord;
	jbox_invalidate_layer((t_object *)x, NULL, gensym("surface"));
	process_change(x);
}


void move_selected_nodes(t_nodes *x, t_pt new_coord)
{
	long i;

	if (x->selected_nodes == 0)
		return;
	
	nodes_undo_step_push_nodes(x, gensym("Move Selected Nodes"));

	for (i = 0; i < x->num_nodes; i++)
		if (x->selected_nodes & (1 << i))
			x->nodes[i].coord = new_coord;
	jbox_invalidate_layer((t_object *)x, NULL, gensym("surface"));
	process_change(x);
}






////// sampling points interface function


void delete_tester(t_nodes *x, long idx)
{
	if (idx >= 0 && idx < x->num_testers) {
		
		if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADA_NODES_ELEMENT_TESTER && x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx == idx)
			x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADA_NODES_ELEMENT_NONE;

		if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_NODES_ELEMENT_TESTER && x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx == idx)
			x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADA_NODES_ELEMENT_NONE;

		if (idx < x->num_testers - 1)
			sysmem_copyptr(&x->testers[idx + 1], &x->testers[idx], (x->num_testers - idx - 1) * sizeof(t_nodes_tester));

		x->num_testers--;
	}
	
	jbox_redraw((t_jbox *)x);
}


void move_tester(t_nodes *x, long idx, t_pt delta)
{
	if (idx >= 0 && idx < x->num_testers) 
		x->testers[idx].coord = pt_pt_sum(x->testers[idx].coord, delta);
	jbox_redraw((t_jbox *)x);
}




//////////////////////// global class pointer variable
t_class *nodes_class;

void C74_EXPORT ext_main(void *moduleRef)
{	
	t_class *c;
	
	common_symbols_init();
	llllobj_common_symbols_init();
	
	srand(time(NULL)); // needed for the shake function

	if (dada_check_bach_version() || llllobj_test()) {
		dada_error_bachcheck();
		return;
	}


	CLASS_NEW_CHECK_SIZE(c, "dada.nodes", (method)nodes_new, (method)nodes_free, (long)sizeof(t_nodes), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, 0);	// include textfield and Fonts attributes
	//	jbox_initclass(c, 0);
	
	// paint & utilities
	class_addmethod(c, (method) nodes_paint,			"paint", A_CANT, 0);
	class_addmethod(c, (method) nodes_assist,			"assist",		A_CANT, 0);  
	class_addmethod(c, (method)	nodes_notify,			"bachnotify",		A_CANT,		0);

	// save & preset
    class_addmethod(c, (method) nodes_preset, "preset", 0);
    class_addmethod(c, (method) nodes_begin_preset, "begin_preset", A_GIMME, 0);
    class_addmethod(c, (method) nodes_restore_preset, "restore_preset", A_GIMME, 0);
    class_addmethod(c, (method) nodes_end_preset, "end_preset", 0);
	CLASS_METHOD_ATTR_PARSE(c, "begin_preset", "undocumented", gensym("long"), 0L, "1");
	CLASS_METHOD_ATTR_PARSE(c, "restore_preset", "undocumented", gensym("long"), 0L, "1");
	CLASS_METHOD_ATTR_PARSE(c, "end_preset", "undocumented", gensym("long"), 0L, "1");
	class_addmethod(c, (method) nodes_jsave, "jsave", A_CANT, 0);
	
	// interface
	class_addmethod(c, (method) nodes_focusgained, "focusgained", A_CANT, 0);
	class_addmethod(c, (method) nodes_focuslost, "focuslost", A_CANT, 0); 	

    // @method (mouse) @digest Edit content
    // @description
    // @copy DADA_DOC_MOUSE_COMMANDS_STANDARD_NAVIGATION
    // Specific commands: <br />
    // • <m>click</m> or <m>click+drag</m>: set tester and output interpolated pitch and velocity content<br />
    // • <m>Alt+click+drag</m> on a node: duplicate node<br />
    // • <m>Cmd+click</m> (mac) or <m>Ctrl+click</m> (win) on a node: delete node<br />
    class_addmethod(c, (method) nodes_mousedown, "mousedown", A_CANT, 0);
	class_addmethod(c, (method) nodes_mousedrag, "mousedrag", A_CANT, 0);
	class_addmethod(c, (method) nodes_mouseup, "mouseup", A_CANT, 0);
    
    // @method (keyboard) @digest Undo/Redo
    // @description
    // @copy DADA_DOC_KEYBOARDS_COMMANDS_STANDARD_NAVIGATION
    // • <m>Cmd+Z</m> (mac) or <m>Ctrl+Z</m> (win): perform undo step<br />
    // • <m>Cmd+Shift+Z</m> (mac) or <m>Ctrl+Y</m> (win): perform redo step<br />
  	class_addmethod(c, (method) nodes_key, "key", A_CANT, 0);
  	class_addmethod(c, (method) nodes_keyup, "keyup", A_CANT, 0);
	class_addmethod(c, (method) nodes_mousemove, "mousemove", A_CANT, 0);
	class_addmethod(c, (method) nodes_mouseenter, "mouseenter", A_CANT, 0);
	class_addmethod(c, (method) nodes_mouseleave, "mouseleave", A_CANT, 0);
	class_addmethod(c, (method) nodes_mousewheel, "mousewheel", A_CANT, 0);
	
    // @method (tools) @digest Navigate or edit content
    // @description
    // @copy DADA_DOC_TOOLS_INTRO
    // @copy DADA_DOC_TOOLS_ZX
    // @copy DADA_DOC_TOOLS_NV
    class_addmethod(c, (method)nodes_bang,			"bang",			0);


    // @method dump @digest Output state
    // @description Outputs the current state of the object. The syntax is
    // <b>nodes [nodes <m>NODE1</m> <m>NODE2</m>...] [testers <m>TESTER1</m> <m>TESTER2</m>...]</b>.
    // Currently a single tester is supported. <br />
    // Each node is in the syntax
    // <b>[coord <m>x</m> <m>y</m>] [pitch <m>pitch_cents</m>] [velocity <m>vel</m>]</b>.<br />
    // Each tester is in the syntax
    // <b>[coord <m>x</m> <m>y</m>] [channel <m>MIDIchannel</m></b>.
    class_addmethod(c, (method)nodes_anything,	"dump",			A_GIMME,	0);

    // @method clear @digest Clear all nodes
    // @description Deletes all the nodes.
    class_addmethod(c, (method)nodes_anything,	"clear",			A_GIMME,	0);
    
    // @method interp @digest Output interpolated values
    // @description The symbol <m>interp</m> followed by two numbers <m>X</m> and <m>Y</m>
    // outputs the interpolated values of pitch (in midicents) and velocity
    // corresponding to the input (<m>X</m> <m>Y</m>) coordinates. The interpolated values are
    // preceded by the "interp" symbol and output from the third outlet.
    // @marg 0 @name x @optional 0 @type float
    // @marg 0 @name y @optional 0 @type float
    class_addmethod(c, (method)nodes_anything,	"interp",			A_GIMME,	0);

    
    // @method addnode @digest Add a node
    // @description Adds a new node. The correct syntax is:
    // <b>addnode <m>NODE_SYNTAX</m></b>, where the node syntax is the one
    // documented in the <m>dump</m> message. The node syntax should NOT be wrapped in parenthesis.
    // For instance, a valid message is: <b>addnode [coord -90. 20.] [pitch 6000] [vel 127]</b>
    // After the node has been added, a notification is sent through the third outlet in the form
    // <b>addnode <m>node_index</m></b>.
    // @marg 0 @name node_syntax @optional 0 @type llll
    class_addmethod(c, (method)nodes_anything,	"addnode",			A_GIMME,	0);

    // @method deletenode @digest Delete a node
    // @description Deletes the <m>N</m>-th node.
    // @marg 0 @name node_index @optional 0 @type int
    class_addmethod(c, (method)nodes_anything,	"deletenode",			A_GIMME,	0);

    
    // @method llll @digest Set state
    // @description Sets the current state of the object. The syntax must follow the one described in the
    // <m>dump</m> message documentation (although nodes only or testers only can be assigned).
	class_addmethod(c, (method)nodes_anything,	"anything",			A_GIMME,	0);
	class_addmethod(c, (method)nodes_anything,	"setstoredstate",	A_GIMME, 0);

    
    
    // @method domain @digest Set the X domain
    // @description The <m>domain</m> message, followed by two numbers, sets minimum and maximum coordinates
    // to be displayed on the X axis.
    // The <m>domain</m> message,  followed by the "start" or "end" symbol and a number, sets the coordinate
    // to be displayed respectively at the left boundary or at the right boundary of the object box.
    // @marg 0 @name arguments @optional 0 @type list
    class_addmethod(c, (method)nodes_anything,		"domain",		A_GIMME,	0);
    
    // @method range @digest Set the Y range
    // @description The <m>range</m> message, followed by two numbers, sets minimum and maximum coordinates
    // to be displayed on the Y axis
    // The <m>range</m> message,  followed by the "start" or "end" symbol and a number, sets the coordinate
    // to be displayed respectively at the bottom boundary or at top right boundary of the object box.
    // @marg 0 @name arguments @optional 0 @type list
    class_addmethod(c, (method)nodes_anything,		"range",		A_GIMME,	0);
    
    
    // @method getdomain @digest Retrieve current X domain
    // @description The <m>getdomain</m> message outputs from the third outlet the minimum and maximum
    // coordinates displayed on the X axis, preceded by a <m>domain</m> symbol.
    class_addmethod(c, (method)nodes_anything,		"getdomain",		A_GIMME,	0);
    
    
    // @method getrange @digest Retrieve current Y range
    // @description The <m>getrange</m> message outputs from the third outlet the minimum and maximum
    // coordinates displayed on the Y axis, preceded by a <m>range</m> symbol.
    class_addmethod(c, (method)nodes_anything,		"getrange",		A_GIMME,	0);
    
    

    DADAOBJ_JBOX_DECLARE_READWRITE_METHODS(c);
    DADAOBJ_JBOX_DECLARE_IMAGE_METHODS(c);
    DADAOBJ_JBOX_DECLARE_ACCEPTSDRAG_METHODS(c);

	llllobj_class_add_out_attr(c, LLLL_OBJ_UI);
	dadaobj_class_init(c, LLLL_OBJ_UI, DADAOBJ_BORDER | DADAOBJ_BORDER_SHOWDEFAULT | DADAOBJ_ZOOM | DADAOBJ_CENTEROFFSET | DADAOBJ_UNDO | DADAOBJ_EMBED | DADAOBJ_MOUSEHOVER | DADAOBJ_NOTIFICATIONS | DADAOBJ_EXPORTTOJITTER);

	CLASS_ATTR_DEFAULT(c, "patching_rect", 0, "0 0 300 300");
	// @exclude dada.nodes
	CLASS_ATTR_DEFAULT(c, "presentation_rect", 0, "0 0 300 300");
	// @exclude dada.node
	

	CLASS_STICKY_ATTR(c,"category",0,"Color");
	
	CLASS_ATTR_RGBA(c, "knobcolor", 0, t_nodes, j_testercolor);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "knobcolor", 0, "0.3 0.3 0.3 1.");
	CLASS_ATTR_STYLE_LABEL(c, "knobcolor", 0, "rgba", "Knob Color");
	CLASS_ATTR_BASIC(c, "knobcolor", 0);
	// @description Sets the color of the test cursors.

	CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	
	CLASS_STICKY_ATTR(c,"category",0,"Behavior");
	
	CLASS_ATTR_CHAR(c, "coarse", 0, t_nodes, fastpow);
    CLASS_ATTR_STYLE_LABEL(c, "coarse", 0, "onoff", "Coarse Computing");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"coarse",0,"1");
    // @description Toggles coarse computing (faster, but less precise).
	
	CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	CLASS_STICKY_ATTR(c,"category",0,"Settings");
	
	CLASS_ATTR_CHAR(c, "tonedivision", 0, t_nodes, tonedivision);
    CLASS_ATTR_STYLE_LABEL(c, "tonedivision", 0, "text", "Microtonal Division");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"tonedivision",0,"2");
	CLASS_ATTR_ACCESSORS(c, "tonedivision", (method)NULL, (method)nodes_setattr_tonedivision);
    // @description @copy BACH_DOC_TONEDIVISION

	CLASS_ATTR_DOUBLE(c, "p", 0, t_nodes, p);
    CLASS_ATTR_STYLE_LABEL(c, "p", 0, "text", "Inverse Distance Exponent");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"p",0,"3");
	CLASS_ATTR_FILTER_MIN(c, "p", 0);
    // @description Sets the exponent for the inverse distance function.
	
	CLASS_ATTR_DOUBLE(c, "minpitch", 0, t_nodes, min_pitch);
    CLASS_ATTR_STYLE_LABEL(c, "minpitch", 0, "text", "Minimum Pitch");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"minpitch",0,"3600");
    // @description Sets the pitch corresponding to the red color.

	CLASS_ATTR_DOUBLE(c, "maxpitch", 0, t_nodes, max_pitch);
    CLASS_ATTR_STYLE_LABEL(c, "maxpitch", 0, "text", "Maximum Pitch");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"maxpitch",0,"8400");
    // @description Sets the pitch corresponding to the violet color.

	CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	CLASS_STICKY_ATTR(c,"category",0,"Appearance");
	
	CLASS_ATTR_CHAR(c, "shownodes", 0, t_nodes, show_nodes);
    CLASS_ATTR_STYLE_LABEL(c, "shownodes", 0, "enumindex", "Show Pitch Nodes");
	CLASS_ATTR_ENUMINDEX(c,"shownodes", 0, "None Point Note Name Note"); 
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"shownodes",0,"3");
    // @description Toggles the visibility of the nodes.

	CLASS_ATTR_CHAR(c, "showknob", 0, t_nodes, show_testers);
    CLASS_ATTR_STYLE_LABEL(c, "showknob", 0, "onoff", "Show Knob");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showknob",0,"1");
    // @description Toggles the visibility of the testing knob.
		
	CLASS_ATTR_DOUBLE(c, "nodesize", 0, t_nodes, node_size);
    CLASS_ATTR_STYLE_LABEL(c, "nodesize", 0, "text", "Pitch Node Size");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"nodesize",0,"2.");
    // @description Sets the node size for displayed pitches

	CLASS_ATTR_DOUBLE(c, "knobsize", 0, t_nodes, tester_size);
    CLASS_ATTR_STYLE_LABEL(c, "knobsize", 0, "text", "Knob Size");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"knobsize",0,"5.");
    // @description Sets the knob size.
	
	CLASS_ATTR_CHAR(c,"showvelocity",0, t_nodes, show_velocity);
	CLASS_ATTR_STYLE_LABEL(c,"showvelocity",0,"enumindex","Show Velocity");
	CLASS_ATTR_ENUMINDEX(c,"showvelocity", 0, "None Transparency Darkness Lightness");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showvelocity", 0, "2");
	CLASS_ATTR_BASIC(c, "showvelocity", 0);
    // @description Sets the fashion in which velocity is displayed.

	CLASS_STICKY_ATTR_CLEAR(c, "category");

		
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	nodes_class = c;
    dadaobj_class_add_fileusage_method(c);

	dev_post("dada.nodes compiled %s %s", __DATE__, __TIME__);
	return;
}

t_max_err nodes_notify(t_nodes *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	if (msg == _sym_attr_modified) {
		t_symbol *attr_name = (t_symbol *)object_method((t_object *)data, _sym_getname);
		if (attr_name == _llllobj_sym_zoom || attr_name == gensym("showvelocity") || attr_name == gensym("p") || attr_name == gensym("coarse")) {
			jbox_invalidate_layer((t_object *)x, NULL, gensym("surface"));
			jbox_redraw((t_jbox *)x);
		} 
		
		if (!x->itsme)
			process_change(x);
	}
	
	return MAX_ERR_NONE;
}

t_max_err nodes_setattr_tonedivision(t_nodes *x, t_object *attr, long ac, t_atom *av)
{
	if (ac && av && is_atom_number(av)) {
		x->tonedivision = MAX(2, atom_getlong(av));
		if (x->tonedivision != 2 && x->tonedivision != 4 && x->tonedivision != 8)
			object_warn((t_object *)x, "Only 2, 4 and 8 tonedivision are graphically supported.");
	}
	return MAX_ERR_NONE;
}


void nodes_begin_preset(t_nodes *x, t_symbol *s, long argc, t_atom *argv)
{
	x->preset_ac = atom_getlong(argv) ;
	x->preset_av = (t_atom *)bach_newptr(x->preset_ac * sizeof(t_atom));
	
	// could allocate memory here etc.
	//	post("begin_preset %ld values will be arriving",x->b_ob.d_ob.preset_ac);
}


void nodes_restore_preset(t_nodes *x, t_symbol *s, long argc, t_atom *argv)
{
	long start, size;
	
	start = atom_getlong(argv);
	size = atom_getlong(argv + 1);
	//	post("restore_preset start %ld size %ld", start,size);
	
	sysmem_copyptr(argv+2, x->preset_av+start, size*sizeof(t_atom));
}

void nodes_end_preset(t_nodes *x)
{
	//	post("end_preset received");
	nodes_anything(x, NULL, x->preset_ac,x->preset_av);
	bach_freeptr(x->preset_av);
}

void nodes_preset(t_nodes *x){
	t_atom temp[256];
	void *buf;
	long i, index, size;
	char wrote = false, begin = true, done = false;
	
	t_llll *data = nodes_get_state(x, true, true);
	llll_prependsym(data, gensym("setstoredstate"), 0, WHITENULL_llll);
	
	// 1. we deparse the list
	t_atom *av = NULL, *this_av = NULL;
	long ac = llll_deparse(data, &av, 0, LLLL_D_FLOAT64 | LLLL_D_QUOTE); //offset 0
	this_av = av;
	
	// 2. We fill the binbuf
	buf = gensym("_preset")->s_thing; 
	if (!buf)	// no preset object
		return;
	
	index = 0;
	while (!done) {
		i = index;
		size = ac - index;
		if (size > 250)
			size = 250;
		else	// you are at the end
			done = true;
		
		sysmem_copyptr(this_av, temp+5, 250*sizeof(t_atom));
		
		if (size) {
			atom_setobj(temp, x);
			atom_setsym(temp + 1, ob_sym(x));
			if (begin) {
				atom_setsym(temp + 2, gensym("begin_preset"));
				atom_setlong(temp + 3, ac);
				binbuf_insert(buf, NULL, 4, temp);
				begin = false;
			}
			atom_setsym(temp + 2, gensym("restore_preset"));
			atom_setlong(temp + 3, index);
			atom_setlong(temp + 4, size);
			binbuf_insert(buf, NULL, size + 5, temp);
			wrote = true;
		}
		index += size;
		this_av += 250;
	}
	if (wrote) {
		atom_setobj(temp, x);
		atom_setsym(temp + 1, ob_sym(x));
		atom_setsym(temp + 2, gensym("end_preset"));
		binbuf_insert(buf, NULL, 3, temp);
	}
	
	if (av) bach_freeptr(av);
}


void nodes_jsave(t_nodes *x, t_dictionary *d)
{
	if (x->b_ob.d_ob.save_data_with_patcher){
		if (x->b_ob.r_ob.l_dictll) {
			llll_store_in_dictionary(x->b_ob.r_ob.l_dictll, d, "nodes_data", NULL);
		} else {
			t_llll *data = nodes_get_state(x, true, true);
			llll_store_in_dictionary(data, d, "nodes_data", NULL);
			llll_free(data);
		}
	} 
}
		

t_llll *nodes_get_single_node(t_nodes *x, long idx)
{
    t_llll *node_ll = llll_get();
    llll_appendllll(node_ll, symbol_and_llll_to_llll_chained(gensym("coord"), pt_to_llll(x->nodes[idx].coord, false)));
    llll_appendllll(node_ll, symbol_and_double_to_llll(gensym("pitch"), x->nodes[idx].pitch_mc));
    llll_appendllll(node_ll, symbol_and_long_to_llll(gensym("velocity"), x->nodes[idx].velocity));
    return node_ll;
}

t_llll *nodes_get_nodes(t_nodes *x)
{
	long i;
	t_llll *out_ll = llll_get();
	for (i = 0; i < x->num_nodes; i++)
		llll_appendllll(out_ll, nodes_get_single_node(x, i));

    llll_prependsym(out_ll, gensym("nodes"), 0, WHITENULL_llll);
	return out_ll;
}


t_llll *nodes_get_testers(t_nodes *x)
{
	long i;
	t_llll *out_ll = llll_get();
	for (i = 0; i < x->num_testers; i++) {
		t_llll *ll = llll_get();
        llll_appendllll(ll, symbol_and_llll_to_llll(gensym("coord"), pt_to_llll(x->testers[i].coord, false)));
		llll_appendllll(ll, symbol_and_long_to_llll(gensym("channel"), x->testers[i].channel));
		llll_appendllll(out_ll, ll, 0, WHITENULL_llll);
	}
	llll_prependsym(out_ll, gensym("testers"), 0, WHITENULL_llll);
	return out_ll;
}


t_llll *nodes_get_state(t_nodes *x, char get_nodes, char get_testers)
{
	// How do we save the information?
	// Two sublists: 1) nodes, 2) testers
	// 1) in the form: ("nodes" NODE1 NODE2 NODE3...) with NODE equal to ((x y) pitch_mc velocity)
	// 2) in the form: ("testers" TESTER1 TESTER2 TESTER3...) with TESTER equal to ((x y) channel)
	
	t_llll *data = llll_get();
	
    llll_appendsym(data, gensym("nodes"));
    
	if (get_nodes)
		llll_appendllll(data, nodes_get_nodes(x), 0, WHITENULL_llll);
	if (get_testers)
		llll_appendllll(data, nodes_get_testers(x), 0, WHITENULL_llll);
	
	return data;
}


void nodes_set_nodes(t_nodes *x, t_llll *nodes)
{
	long i;
	t_llllelem *elem;
	
	x->num_nodes = MAX(0, nodes->l_size - 1);
	
	for (i = 0, elem = nodes->l_head ? nodes->l_head->l_next : NULL; elem && i < DADA_NODES_MAX_NODES; elem = elem->l_next, i++) {
		if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
			t_llll *ll = hatom_getllll(&elem->l_hatom);
            t_llllelem *spec_el = ll->l_head;
            for (spec_el = ll->l_head; spec_el; spec_el = spec_el->l_next) {
                if (hatom_gettype(&spec_el->l_hatom) != H_LLLL) continue;
                t_llll *spec = hatom_getllll(&spec_el->l_hatom);
                if (!spec || !spec->l_head || hatom_gettype(&spec->l_head->l_hatom) != H_SYM) continue;
                t_symbol *router = hatom_getsym(&spec->l_head->l_hatom);
                if (router == gensym("coord") && spec->l_size >= 3) {
                    x->nodes[i].coord.x = hatom_getdouble(&spec->l_head->l_next->l_hatom);
                    x->nodes[i].coord.y = hatom_getdouble(&spec->l_head->l_next->l_next->l_hatom);
                } else if (router == gensym("pitch") && spec->l_size >= 2) {
                    x->nodes[i].pitch_mc = hatom_getdouble(&spec->l_head->l_next->l_hatom);
                } else if (router == gensym("velocity") && spec->l_size >= 2) {
                    x->nodes[i].velocity = hatom_getlong(&spec->l_head->l_next->l_hatom);
                }
            }
		}
	}
}

void nodes_set_testers(t_nodes *x, t_llll *testers)
{
	long i;
	t_llllelem *temp, *elem;
	
	x->num_testers = MAX(0, testers->l_size - 1);
	
	for (i = 0, elem = testers->l_head ? testers->l_head->l_next : NULL; elem && i < DADA_NODES_MAX_NODES; elem = elem->l_next, i++) {
        if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
            t_llll *ll = hatom_getllll(&elem->l_hatom);
            t_llllelem *spec_el = ll->l_head;
            for (spec_el = ll->l_head; spec_el; spec_el = spec_el->l_next) {
                if (hatom_gettype(&spec_el->l_hatom) != H_LLLL) continue;
                t_llll *spec = hatom_getllll(&spec_el->l_hatom);
                if (!spec || !spec->l_head || hatom_gettype(&spec->l_head->l_hatom) != H_SYM) continue;
                t_symbol *router = hatom_getsym(&spec->l_head->l_hatom);
                if (router == gensym("coord") && spec->l_size >= 3) {
                    x->testers[i].coord.x = hatom_getdouble(&spec->l_head->l_next->l_hatom);
                    x->testers[i].coord.y = hatom_getdouble(&spec->l_head->l_next->l_next->l_hatom);
                } else if (router == gensym("channel") && spec->l_size >= 2) {
                    x->testers[i].channel = hatom_getlong(&spec->l_head->l_next->l_hatom);
                }
            }
        }
	}
}


// see nodes_get_state about the codification of info
void nodes_set_state(t_nodes *x, t_llll *state)
{
	x->itsme = true;

    t_llllelem *el;
    for (el = state->l_head; el; el = el->l_next) {
        if (hatom_gettype(&el->l_hatom) == H_LLLL) {
            t_llll *ll = hatom_getllll(&el->l_hatom);
            if (ll && ll->l_head && hatom_gettype(&ll->l_head->l_hatom) == H_SYM) {
                t_symbol *router = hatom_getsym(&ll->l_head->l_hatom);
                if (router == gensym("nodes"))
                    nodes_set_nodes(x, ll);
                else if (router == gensym("testers"))
                    nodes_set_testers(x, ll);
            }
        }
    }

	x->itsme = false;

	// reprocess stuff
	jbox_invalidate_layer((t_object *)x, NULL, gensym("surface"));
	process_change(x);
}

void nodes_assist(t_nodes *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type anything @digest Incoming symbol or list
		sprintf(s, "Incoming symbol or list");
	} 
	else {	
		if (a == 0)	// @out 0 @type llll @digest Dump outlet
			sprintf(s, "Dump Outlet"); 			
		else if (a == 1)	// @out 1 @type llll @digest Knob pitch and velocity
			sprintf(s, "Knob Pitch and Velocity"); 			
		else if (a == 2)	// @out 2 @type llll @digest Queries and notifications
			sprintf(s, "Queries and Notifications"); 			
		else 	// @out 3 @type bang @digest bang when object is changed via the interface
			sprintf(s, "bang when Changed"); 			
	}
}

void nodes_free(t_nodes *x)
{
	object_free_debug(x->n_proxy1);
	dadaobj_jbox_free((t_dadaobj_jbox *)x); // jbox_free and llllobj_free are inside here
}

void nodes_iar(t_nodes *x)
{
    jbox_invalidate_layer((t_object *)x, NULL, gensym("surface"));
    jbox_redraw((t_jbox *)x);
}



void *nodes_new(t_symbol *s, long argc, t_atom *argv)
{
	t_nodes *x = NULL;
	t_dictionary *d = NULL;
	long boxflags;
	t_llll *llll_for_rebuild = NULL;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;    
	
	if ((x = (t_nodes *)object_alloc_debug(nodes_class))) {
		
		x->creating_new_obj = true;
		
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
		x->n_proxy1 = proxy_new((t_object *) x, 1, &x->n_in);

		dadaobj_jbox_setup((t_dadaobj_jbox *)x, DADAOBJ_BORDER | DADAOBJ_BORDER_SHOWDEFAULT | DADAOBJ_ZOOM | DADAOBJ_CENTEROFFSET | DADAOBJ_UNDO | DADAOBJ_CHANGEDBANG | DADAOBJ_NOTIFICATIONS, build_pt(1., 1.), 2, 3, 2, (dada_paint_ext_fn)nodes_paint_ext, (invalidate_and_redraw_fn)nodes_iar, "vn", 2, "b444");
		dadaobj_addfunctions(dadaobj_cast(x), (dada_mousemove_fn)nodes_mousemove, NULL, (method)nodes_undo_postprocess, (get_state_fn)nodes_get_state, (set_state_fn)nodes_set_state, NULL, NULL, NULL);

		x->b_ob.d_ob.m_tools.curr_tool = DADA_TOOL_ARROW;
		x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADA_NODES_ELEMENT_NONE;
		
		x->firsttime = true;
		x->selected_nodes = x->selected_testers = 0;
		x->num_testers = 1;
		x->num_nodes = 0;
		x->testers[0].coord = build_pt(0, 0);
        x->testers[0].channel = 1;
		
		add_node(x, build_pt(-70, -70), 6000, 100);
		add_node(x, build_pt(80, 0), 7200, 100);
		add_node(x, build_pt(0, 70), 3600, 100);
		
		attr_dictionary_process(x,d);
		
		if ((llll_for_rebuild = llll_retrieve_from_dictionary(d, "nodes_data"))) { // new method
			llllobj_manage_dict_llll((t_object *)x, LLLL_OBJ_UI, llll_for_rebuild);
			nodes_set_state(x, llll_for_rebuild);
			llll_free(llll_for_rebuild);
		}
		
		jbox_ready((t_jbox *)x);
        
        dadaobj_set_current_version_number(dadaobj_cast(x));
		
		x->creating_new_obj = false;
	}
	return x;
}

void nodes_int(t_nodes *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	nodes_anything(x, _sym_list, 1, argv);
}

void nodes_float(t_nodes *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	nodes_anything(x, _sym_list, 1, argv);
}

// output sampled information
void nodes_bang(t_nodes *x)
{	
	return;
}

void nodes_dump(t_nodes *x, char get_nodes, char get_testers)
{	
	t_llll *ll = nodes_get_state(x, get_nodes, get_testers);
	llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 0, ll);
	llll_free(ll);
}

void nodes_clear(t_nodes *x)
{
    x->num_nodes = 0;
}


void notify_node_add(t_nodes *x, long node_idx)
{
    if (node_idx >= 0) {
        t_llll *ll = llll_get();
        llll_appendsym(ll, gensym("addnode"));
        llll_appendlong(ll, node_idx + 1);
        llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, ll);
        llll_free(ll);
    }
}

void nodes_anything(t_nodes *x, t_symbol *msg, long ac, t_atom *av)
{
	dadaobj_anything(dadaobj_cast(x), msg, ac, av);

	t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, msg, ac, av, LLLL_PARSE_CLONE);
	if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
		t_symbol *router = hatom_getsym(&parsed->l_head->l_hatom);
		llll_behead(parsed);
		
        if (dadaobj_anything_handle_domain_or_range(dadaobj_cast(x), router, parsed)) {
            // nothing to do!
        } else if (router == gensym("setstoredstate") || router == gensym("nodes"))
			nodes_set_state(x, parsed);
		else if (router == _sym_dump)
			nodes_dump(x, parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("nodes")), 
						 parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("testers")));
        else if (router == _sym_clear) {
            nodes_undo_step_push_nodes(x, gensym("Clear"));
            nodes_clear(x);
            nodes_undo_postprocess(x);
        } else if (router == gensym("addnode")) {
            nodes_undo_step_push_nodes(x, gensym("Add Node"));
            notify_node_add(x, add_node_from_llll(x, parsed));
            nodes_undo_postprocess(x);
        } else if (router == gensym("deletenode")) {
            if (parsed->l_head && is_hatom_number(&parsed->l_head->l_hatom))
                delete_node(x, hatom_getlong(&parsed->l_head->l_hatom) - 1);
        } else if (router == _llllobj_sym_interp) {
            t_pt coord = build_pt(0, 0);
            double vel = 0;
            if (parsed->l_head && is_hatom_number(&parsed->l_head->l_hatom))
                coord.x = hatom_getdouble(&parsed->l_head->l_hatom);
            if (parsed->l_head && parsed->l_head->l_next && is_hatom_number(&parsed->l_head->l_next->l_hatom))
                coord.y = hatom_getdouble(&parsed->l_head->l_next->l_hatom);
            
            double mc = get_pitch_at_coord(x, coord, &vel);
            t_llll *out = llll_get();
            llll_appendsym(out, _llllobj_sym_interp);
            llll_appenddouble(out, mc);
            llll_appenddouble(out, vel);
            llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, out);
            llll_free(out);
        }
		
	} else if (parsed) {
		nodes_set_state(x, parsed);
	}
	llll_free(parsed);
}


void nodes_select_all(t_nodes *x)
{
	long i;
	for (i = 0; i < x->num_nodes; i++)
		x->selected_nodes |= (1 << i);
	for (i = 0; i < x->num_testers; i++)
		x->selected_testers |= (1 << i);
	jbox_redraw((t_jbox *)x);
}

				 
void nodes_move(t_nodes *x, t_llll *args)
{
	t_pt vector = build_pt(0, 0);
	
	// vector for moving
	if (args->l_size >= 2 && hatom_gettype(&args->l_head->l_next->l_hatom) == H_LLLL)
		vector = llll_to_pt(hatom_getllll(&args->l_head->l_next->l_hatom));
	
	if (args->l_size >= 1) {
		// which shapes do we want to move?
		if (hatom_gettype(&args->l_head->l_hatom) != H_LONG)
			move_all_nodes(x, vector);
		else {
			long idx = hatom_getlong(&args->l_head->l_hatom);
			if (idx <= 0)
				move_all_nodes(x, vector);
			else if (idx > 0 && idx <= x->num_nodes)
				move_node(x, &x->nodes[idx - 1], vector);
		}
	}
}




long coordinate_to_node(t_nodes *x, t_pt coord)
{
	long i;
	switch (x->show_nodes) {
		case DADA_NODES_PITCH_DISPLAY_POINT:
			for (i = 0; i < x->num_nodes; i++)
				if (pt_pt_distance(x->nodes[i].coord, coord) <= x->node_size + DADA_NODES_NODE_SELECTION_PAD)
					return i;
			break;
		case DADA_NODES_PITCH_DISPLAY_NOTENAME:
		case DADA_NODES_PITCH_DISPLAY_NOTE:
			for (i = 0; i < x->num_nodes; i++)
				if (is_pt_in_rectangle(coord, x->nodes[i].node_rect))
					return i;
			break;
		default:
			break;
	}
	return -1;
}

long coordinate_to_tester(t_nodes *x, t_pt coord)
{
	long i;
	for (i = 0; i < x->num_testers; i++)
		if (pt_pt_distance(x->testers[i].coord, coord) <= x->tester_size + DADA_NODES_TESTER_SELECTION_PAD)
			return i;
	return -1;
}

long pixel_to_node(t_nodes *x, t_pt pt, t_object *view, t_pt *coordinates)
{
	t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), view, pt);
	if (coordinates)
		*coordinates = coord;
	return coordinate_to_node(x, coord);
}

long pixel_to_tester(t_nodes *x, t_pt pt, t_object *view, t_pt *coordinates)
{
	t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), view, pt);
	if (coordinates)
		*coordinates = coord;
	return coordinate_to_tester(x, coord);
}


t_dadaitem_identifier pixel_to_element(t_nodes *x, t_pt pt, t_object *view, t_pt *coordinates, char include_testers)
{
	t_dadaitem_identifier result;
	long idx = -1;
	result.type = DADA_NODES_ELEMENT_NONE;
	result.flag = 0;
    result.idx = result.secondary_idx = result.tertiary_idx = -1;

	if (include_testers && (idx = pixel_to_tester(x, pt, view, coordinates)) >= 0) {
		result.type = DADA_NODES_ELEMENT_TESTER;
		result.idx = idx;
	} else if ((idx = pixel_to_node(x, pt, view, coordinates)) >= 0) {
		result.type = DADA_NODES_ELEMENT_NODE;
		result.idx = idx;
	}

	return result;
}


void change_node_pitch(t_nodes *x, long idx, double delta_mc)
{
	nodes_undo_step_push_nodes(x, gensym("Change Pitch"));
	if (idx >= 0 && idx < x->num_nodes) 
		x->nodes[idx].pitch_mc += delta_mc;
}
	
void change_node_velocity(t_nodes *x, long idx, double delta_vel)
{
	nodes_undo_step_push_nodes(x, gensym("Change Velocity"));
	if (idx >= 0 && idx < x->num_nodes) 
		x->nodes[idx].velocity = CLAMP(x->nodes[idx].velocity + delta_vel, DADA_MIN_VELOCITY, DADA_MAX_VELOCITY);
}

void change_tester_channel(t_nodes *x, long idx, long channel)
{
	nodes_undo_step_push_nodes(x, gensym("Change MIDIchannel"));
	if (idx >= 0 && idx < x->num_testers) 
		x->testers[idx].channel = channel;
}


//// GRAPHIC DRAWING



double get_pitch_at_coord(t_nodes *x, t_pt coord, double *velocity)
{
	// Inverse distance weighting
	long n;
	double wu = 0, w = 0, wv = 0;
	double pitch = 0;
	char precise_match = false;
	double temp = 0;
	
	for (n = 0; n < x->num_nodes; n++){
		double dist = pt_pt_distance(x->nodes[n].coord, coord);
		if (dist <= CONST_EPSILON1) {
			precise_match = true;
			pitch = x->nodes[n].pitch_mc;
			if (velocity)
			*velocity = x->nodes[n].velocity;
			break;
		} else {
			temp = x->fastpow ? 1/fast_pow(dist, x->p) : 1/pow(dist, x->p);
			w += temp;
			wu += temp * x->nodes[n].pitch_mc;
			wv += temp * x->nodes[n].velocity;
		}
	}
	
	if (!precise_match)  {
		pitch = wu/w;
		if (velocity)
			*velocity = wv/w;
	}
	return pitch;
}


t_jrgba get_color_at_coord(t_nodes *x, t_pt coord, double *pitch_at_coord, double *velocity_at_coord)
{
	double velocity;
	double pitch_at_c = 0;
	double pitch = CLAMP((pitch_at_c = get_pitch_at_coord(x, coord, &velocity)), x->min_pitch, x->max_pitch);
	
	velocity = CLAMP(velocity, 0, DADA_MAX_VELOCITY);
	t_jrgba color = double_to_color(CLAMP(pitch, x->min_pitch, x->max_pitch), x->min_pitch, x->max_pitch, false);
	
	switch (x->show_velocity) {
		case 1:
			change_color_for_velocity_alpha(&color, velocity);
			break;
		case 2:
			change_color_for_velocity_darken(&color, velocity);
			break;
		case 3:
			change_color_for_velocity_lighten(&color, velocity);
			break;
		default:
			break;
	}
	
	if (pitch_at_coord)
		*pitch_at_coord = pitch_at_c;
	if (velocity_at_coord)
		*velocity_at_coord = velocity;
	return color;
}


void nodes_paint_surface(t_nodes *x, t_object *view, t_rect rect, t_pt center, double zoom, t_dada_force_graphics *force_graphics)
{
	
    t_jgraphics *g = view ? jbox_start_layer((t_object *)x, view, gensym("surface"), rect.width, rect.height) : force_graphics->graphic_context;
	
	if (g){
		long i, j;
		double step_x = 1, step_y = 1; // modify this?
		
		t_jsurface *surf = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, rect.width, rect.height);
		
		for (i = 0; i < rect.width; i += step_x) {
			for (j = 0; j < rect.height; j+= step_y) {
				t_pt coord = pix_to_coord(dadaobj_cast(x), center, build_pt(i, j));
				t_jrgba color = get_color_at_coord(x, coord, NULL, NULL);
				jgraphics_image_surface_set_pixel(surf, i, j, color);
			}
		}
		
		t_rect rect_ok = build_rect(0, 0, rect.width, rect.height);
		jgraphics_image_surface_draw(g, surf, rect_ok, rect_ok);
		
        if (view)
            jbox_end_layer((t_object *)x, view, gensym("surface"));
	}
	
    if (view)
        jbox_paint_layer((t_object *)x, view, gensym("surface"), 0., 0.);	// position of the layer
}


void paint_node_note(t_nodes *x, t_jgraphics *g, t_object *view, t_nodes_node *node, t_rect noterect, t_jrgba bgcolor, double zoom)
{
	t_jrgba staffcolor = build_jrgba(0.2, 0.2, 0.2, 1);
	t_jrgba bordercolor = build_jrgba(0.2, 0.2, 0.2, 1);
	
	paint_rectangle_rounded(g, bordercolor, bgcolor, noterect.x, noterect.y, noterect.width, noterect.height, 1, DADA_DEFAULT_RECT_ROUNDNESS, DADA_DEFAULT_RECT_ROUNDNESS);
	
	ezpaint_note_with_staff((t_object *)x, g, node->pitch_mc, k_ACC_AUTO, x->tonedivision, build_pt(noterect.x + 3 * zoom, noterect.y + 25 * zoom), noterect.width - 6 * zoom, 24 * zoom, noterect.x + 31 * zoom, false, &staffcolor, &staffcolor, &staffcolor);

	jgraphics_set_source_rgba(g, 0, 0, 0, 1);
}

void repaint_hovered_note(t_nodes *x, t_jgraphics *g, t_object *view, t_rect rect, t_pt center)
{
	// re-paint selected and hovered elements
	switch (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type) {
		case DADA_NODES_ELEMENT_NODE:
			if (x->show_nodes == DADA_NODES_PITCH_DISPLAY_POINT) {
				t_nodes_node *node = &x->nodes[x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx];
				t_jrgba bordercolor = get_grey(0.2);
				t_pt node_pixel = coord_to_pix(dadaobj_cast(x), center, node->coord);
				node_pixel.y = round_to_semiinteger(node_pixel.y);
				
				t_rect pos = build_rect(node_pixel.x + 80 < rect.width ? node_pixel.x + 20 : node_pixel.x - 70, 
										node_pixel.y - 100 > 0 ? node_pixel.y - 90 : node_pixel.y + 20, DADA_NODES_NOTEPOPUP_WIDTH, DADA_NODES_NOTEPOPUP_HEIGHT);
				paint_dashed_line(g, bordercolor, node_pixel.x, node_pixel.y, pos.x > node_pixel.x ? pos.x : pos.x + pos.width, 
								  pos.y < node_pixel.y ? pos.y + pos.height : pos.y, 3, 3);
				
				paint_node_note(x, g, view, node, pos, build_jrgba(1, 1, 1, 0.9), 1);
			}
			
			break;
		default: 
			if (x->b_ob.d_ob.m_interface.allow_mouse_hover && x->b_ob.d_ob.m_interface.mouse_is_over && (!x->b_ob.d_ob.m_interface.mouse_is_down || (x->b_ob.d_ob.m_interface.mouse_is_down && x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADA_NODES_ELEMENT_TESTER))) {
				t_pt pt = x->b_ob.d_ob.m_interface.mouse_is_down ? x->b_ob.d_ob.m_interface.mousedrag_pix : x->b_ob.d_ob.m_interface.mousemove_pix;
				double pitch_mc = 0;
				t_jrgba color = get_color_at_coord(x, pix_to_coord_from_view(dadaobj_cast(x), view, pt), &pitch_mc, NULL);
				t_jrgba white = change_alpha(get_grey_to_write_over_color(color, 0.2), x->b_ob.d_ob.m_interface.mouse_is_down ? 0.9 : 0.6);
				t_rect pos = x->b_ob.d_ob.m_interface.mouse_is_down ? get_rect_near_pt_inside_rect(build_pt(pt.x, pt.y), 40, 20, build_rect(0, 0, rect.width, rect.height), build_pt(10, 10), build_pt(10, 10), NULL) :
												build_rect(pt.x - 20, pt.y - 10, 40, 20);
				ezpaint_note_with_staff((t_object *)x, g, pitch_mc, k_ACC_AUTO, x->tonedivision, 
										build_pt(pos.x, round_to_semiinteger(pos.y)), 
										pos.width, 16, pos.x + 25, false, &white, &white, &white);
			}
			break;
	}
	
}

void paint_main_tester(t_nodes *x, t_jgraphics *g, t_object *view, t_rect rect, t_pt center)
{
	double size = x->tester_size;
	t_pt pix = coord_to_pix(dadaobj_cast(x), center, x->testers[0].coord);
	paint_line(g, x->j_testercolor, pix.x + 1.5, pix.y, pix.x + size + 1.5, pix.y, 1);
	paint_line(g, x->j_testercolor, pix.x - 1.5, pix.y, pix.x - size - 1.5, pix.y, 1);
	paint_line(g, x->j_testercolor, pix.x, pix.y + 1.5, pix.x, pix.y + size + 1.5, 1);
	paint_line(g, x->j_testercolor, pix.x, pix.y - 1.5, pix.x, pix.y - size - 1.5, 1);
}

void nodes_paint_ext(t_nodes *x, t_object *view, t_dada_force_graphics *force_graphics)
{
    long i;
	t_rect rect = force_graphics->rect;
	t_pt center = force_graphics->center_pix;
	double zoom = force_graphics->zoom.x;
    t_jgraphics *g = force_graphics->graphic_context;
	
	jgraphics_set_source_rgba(g, 0, 0, 0, 1); // alpha = 1;
	
	nodes_paint_surface(x, view, rect, center, zoom, force_graphics);
	
	for (i = 0; i < x->num_nodes; i++) {
		t_jrgba color = get_grey(0.2);
		t_pt pix = coord_to_pix(dadaobj_cast(x), center, x->nodes[i].coord);
		switch (x->show_nodes) {
			case DADA_NODES_PITCH_DISPLAY_POINT:
				paint_circle(g, color, color, pix.x, pix.y, x->node_size, 1);
				if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_NODES_ELEMENT_NODE && x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx == i)
					paint_circle_stroken(g, color, pix.x, pix.y, x->node_size + DADA_NODES_NODE_SELECTION_PAD, 1);
				x->nodes[i].node_rect = rect = build_rect(pix.x, pix.y, 0, 0);
				break;
			case DADA_NODES_PITCH_DISPLAY_NOTENAME:
			{
				char *buf = NULL;
				double w, h;
				t_jrgba color2 = build_jrgba(1, 1, 1, 0.9), color1 = get_grey(0.3);
				t_jfont *jf = jfont_create_debug("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, x->node_size * 6 * x->b_ob.d_ob.m_zoom.zoom.x);

				ezmidicents2notename(5, x->nodes[i].pitch_mc, k_NOTE_NAMES_ANGLOSAXON, true, &buf, x->tonedivision);
				jfont_text_measure(jf, buf, &w, &h);
				
				paint_rectangle_rounded(g, color1, change_alpha(color2, x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_NODES_ELEMENT_NODE && x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx == i ? 1 : 0.7), pix.x - w/2 - 3, pix.y - h/2 - 3, w + 6, h + 6, 1, DADA_DEFAULT_RECT_ROUNDNESS, DADA_DEFAULT_RECT_ROUNDNESS);

				double w_as_coord = w/x->b_ob.d_ob.m_zoom.zoom.x, h_as_coord = h/x->b_ob.d_ob.m_zoom.zoom.x;
				x->nodes[i].node_rect = build_rect(x->nodes[i].coord.x - w_as_coord/2, x->nodes[i].coord.y - h_as_coord/2, w_as_coord, h_as_coord);

				write_text_simple(g, jf, color1, buf, pix.x - w/2, pix.y - h/2, w + 20, h + 20);
				
				bach_freeptr(buf);
				jfont_destroy_debug(jf);
				break;
			}
			case DADA_NODES_PITCH_DISPLAY_NOTE:
			{
				double w_as_coord = DADA_NODES_NOTEPOPUP_WIDTH * x->node_size / 2., h_as_coord = DADA_NODES_NOTEPOPUP_HEIGHT * x->node_size / 2.;
				t_rect pos = build_rect(pix.x - DADA_NODES_NOTEPOPUP_WIDTH * x->b_ob.d_ob.m_zoom.zoom.x/2., pix.y - DADA_NODES_NOTEPOPUP_HEIGHT * x->b_ob.d_ob.m_zoom.zoom.x/2., DADA_NODES_NOTEPOPUP_WIDTH * x->b_ob.d_ob.m_zoom.zoom.x, DADA_NODES_NOTEPOPUP_HEIGHT * x->b_ob.d_ob.m_zoom.zoom.x);
				paint_node_note(x, g, view, &x->nodes[i], pos, x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_NODES_ELEMENT_NODE && x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx == i ? DADA_WHITE : change_alpha(DADA_WHITE, 0.9), x->b_ob.d_ob.m_zoom.zoom.x);
				x->nodes[i].node_rect = build_rect(x->nodes[i].coord.x - w_as_coord/2, x->nodes[i].coord.y - h_as_coord/2, w_as_coord, h_as_coord);
				break;
			}
			default:
				break;
		}
	}
	
	if (x->b_ob.d_ob.m_tools.curr_tool != DADA_TOOL_ZOOM && x->b_ob.d_ob.m_tools.curr_tool != DADA_TOOL_MOVE_CENTER)
		repaint_hovered_note(x, g, view, rect, center);
	
	paint_main_tester(x, g, view, rect, center);
	
	// paint border
    dadaobj_paint_border(dadaobj_cast(x), g, &rect);
}

void nodes_paint(t_nodes *x, t_object *view)
{
    dadaobj_paint(dadaobj_cast(x), view);
}



///////// POPUP MENU FUNCTIONS

void nodes_popup_center_view(t_dadaobj *r_ob, t_symbol *label, const t_llll *address)
{
    reset_center_offset(r_ob);
    jbox_invalidate_layer((t_object *)r_ob->orig_obj, NULL, gensym("surface"));
}


void nodes_popup_reset_zoom(t_dadaobj *r_ob, t_symbol *label, const t_llll *address)
{
    reset_zoom(r_ob);
    jbox_invalidate_layer((t_object *)r_ob->orig_obj, NULL, gensym("surface"));
}

void nodes_popup_add_node(t_dadaobj *r_ob, t_symbol *label, const t_llll *address)
{
    add_node((t_nodes *)r_ob->orig_obj, r_ob->m_interface.mousedown_coord, 6000, 100);
    jbox_invalidate_layer((t_object *)r_ob->orig_obj, NULL, gensym("surface"));
}


void popup_delete_node(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_nodes *x = (t_nodes *)d_ob->orig_obj;
	if (d_ob->m_interface.mousedown_item_identifier.type == DADA_NODES_ELEMENT_NODE)
		delete_node(x, d_ob->m_interface.mousedown_item_identifier.idx);
}

void show_node_popup_menu(t_nodes *x, t_object *patcherview, t_pt pt, long modifiers)
{
	ezdisplay_popup_menu(dadaobj_cast(x), patcherview,
						 (char *)"Delete", "0", "", "", "", "", 
						 (void *)popup_delete_node, WHITENULL);
}

void show_bg_popup_menu(t_nodes *x, t_object *patcherview, t_pt pt, long modifiers)
{
	ezdisplay_popup_menu(dadaobj_cast(x), patcherview,
						 (char *)"Add Node Center View Reset Zoom", "0", "", "", "", "",
						 (void *)nodes_popup_add_node, (void *)nodes_popup_center_view, (void *)nodes_popup_reset_zoom, WHITENULL);
}




////////// INTERFACE FUNCTIONS

void nodes_focusgained(t_nodes *x, t_object *patcherview) {
	if (dadaobj_focusgained(dadaobj_cast(x), patcherview))
		return;
}

void nodes_focuslost(t_nodes *x, t_object *patcherview) {
	if (dadaobj_focuslost(dadaobj_cast(x), patcherview))
		return;
}

void nodes_output_notification(t_nodes *x, t_dadaitem_identifier *ident, t_symbol *sym)
{
    t_llll *ll = llll_get();
    llll_appendsym(ll, sym);
    
    switch (ident->type) {
        case DADA_NODES_ELEMENT_NODE:
            llll_appendsym(ll, gensym("node"));
            llll_appendlong(ll, ident->idx + 1);
            if (dadaobj_cast(x)->m_interface.send_notifications == DADAOBJ_NOTIFY_VERBOSE)
                llll_appendllll(ll, nodes_get_single_node(x, ident->idx));
            break;

        default:
            llll_appendsym(ll, _llllobj_sym_none);
            break;
    }
    
    dadaobj_send_notification_llll(dadaobj_cast(x), ll);
}

void nodes_mousemove(t_nodes *x, t_object *patcherview, t_pt pt, long modifiers)
{

    t_dadaitem_identifier old_ident = x->b_ob.d_ob.m_interface.mousemove_item_identifier;
	llll_format_modifiers(&modifiers, NULL);
	
	if (dadaobj_mousemove(dadaobj_cast(x), patcherview, pt, modifiers))
		return;

	if (x->b_ob.d_ob.m_interface.allow_mouse_hover) {
		x->b_ob.d_ob.m_interface.mousemove_item_identifier = pixel_to_element(x, pt, patcherview, NULL, false);
        if (!dadaitem_identifier_eq(old_ident, x->b_ob.d_ob.m_interface.mousemove_item_identifier))
            nodes_output_notification(x, &x->b_ob.d_ob.m_interface.mousemove_item_identifier, gensym("hover"));
		jbox_redraw((t_jbox *)x);
	} else {
		if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type != DADA_NODES_ELEMENT_NONE) {
			x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADA_NODES_ELEMENT_NONE;
			dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
			jbox_redraw((t_jbox *)x);
		}
	}
	
	
	if (popup_menu_is_shown(dadaobj_cast(x))) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
	} else if (x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_CHANGE_PITCH && x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_NODES_ELEMENT_NODE) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_NOTE_UPDOWN);
	} else if (x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_CHANGE_VELOCITY && x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_NODES_ELEMENT_NODE) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_CHANGE_VELOCITY);
	} else if (x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_ARROW
			   && (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_NODES_ELEMENT_NODE || x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_NODES_ELEMENT_TESTER)
			   && modifiers == eCommandKey) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DELETE);
	} else if (x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_ARROW
			   && (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_NODES_ELEMENT_NODE || x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_NODES_ELEMENT_TESTER)
			   && modifiers == eAltKey) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DUPLICATE);
	} else if (x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_ARROW && 
			   (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_NODES_ELEMENT_NODE || x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADA_NODES_ELEMENT_TESTER)) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_MOVE);
	} else if (x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_ARROW && x->b_ob.d_ob.m_interface.mousemove_item_identifier.type != DADA_NODES_ELEMENT_NODE) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_NONE);
	} else  {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
	}

}


void nodes_mousedown(t_nodes *x, t_object *patcherview, t_pt pt, long modifiers){

	if (dadaobj_mousedown(dadaobj_cast(x), patcherview, pt, modifiers))
		return;

	x->b_ob.d_ob.m_interface.mousedown_item_identifier = pixel_to_element(x, pt, patcherview, &x->b_ob.d_ob.m_interface.mousedown_coord, false);

	if (modifiers & ePopupMenu) {
		
		switch (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type) {
			case DADA_NODES_ELEMENT_NODE:
				show_node_popup_menu(x, patcherview, pt, modifiers);
				break;
			default:
				show_bg_popup_menu(x, patcherview, pt, modifiers);
				break;
		}
		
	} else {
		
		llll_format_modifiers(&modifiers, NULL);

        nodes_output_notification(x, &x->b_ob.d_ob.m_interface.mousedown_item_identifier, gensym("click"));

        switch (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type) {
			case DADA_NODES_ELEMENT_NODE:
				if (modifiers == eCommandKey) {
					if (delete_node(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx))
						object_error((t_object *)x, "Can't delete node.");
					else
						jbox_invalidate_layer((t_object *)x, NULL, gensym("sampling_points"));
				}
				break;
				
			default:
				x->selected_nodes = x->selected_testers = 0; // clear selection
				x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADA_NODES_ELEMENT_TESTER;
				x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx = 0;
				x->testers[0].coord = pix_to_coord_from_view(dadaobj_cast(x), patcherview, pt);
				send_tester(x);
				break;
		}
	}
	
	jbox_redraw((t_jbox *)x);
	
}

void nodes_mouseup(t_nodes *x, t_object *patcherview, t_pt pt, long modifiers){

	llll_format_modifiers(&modifiers, NULL);
	
	if (dadaobj_mouseup(dadaobj_cast(x), patcherview, pt, modifiers))
		return;

	x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADA_NODES_ELEMENT_NONE;
	x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag = 0;

	if (x->b_ob.d_ob.m_cursors.curr_cursor == BACH_CURSOR_NONE) { 
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
		nodes_mousemove(x, patcherview, pt, modifiers);
	}
}

void nodes_mousedrag(t_nodes *x, t_object *patcherview, t_pt pt, long modifiers){
	
	llll_format_modifiers(&modifiers, NULL);
	
	if (dadaobj_mousedrag(dadaobj_cast(x), patcherview, pt, modifiers))
		return;

	t_pt delta = x->b_ob.d_ob.m_interface.mousedrag_delta_pix;

	if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADA_NODES_ELEMENT_TESTER) 
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_NONE);
	
	
	switch (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type) {
		case DADA_NODES_ELEMENT_TESTER:
			x->testers[0].coord = pix_to_coord_from_view(dadaobj_cast(x), patcherview, pt);
			send_tester(x);
			jbox_redraw((t_jbox *)x);
			break;
			
		case DADA_NODES_ELEMENT_NODE:
			switch (modifiers) {
				case eAltKey:
					if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag & DADAITEM_IDENTIFIER_FLAG_DUPLICATED) {
						t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), patcherview, pt);
						move_node(x, &x->nodes[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx], coord);
					} else {
						t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), patcherview, pt);
						long new_idx = duplicate_node(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx);
						if (new_idx < 0) {
							object_error((t_object *)x, "Can't duplicate node.");
							x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADA_NODES_ELEMENT_NONE;
						} else {
							x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx = x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx = new_idx;
							x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag |= DADAITEM_IDENTIFIER_FLAG_DUPLICATED;
							jbox_invalidate_layer((t_object *)x, NULL, gensym("surface"));
							jbox_redraw((t_jbox *)x);
						}
					}
					break;
				default:
					switch (x->b_ob.d_ob.m_tools.curr_tool) {
						case DADA_TOOL_CHANGE_PITCH:
							change_node_pitch(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, -delta.y * 10);
							jbox_invalidate_layer((t_object *)x, NULL, gensym("surface"));
							jbox_redraw((t_jbox *)x);
							break;
						case DADA_TOOL_CHANGE_VELOCITY:
							change_node_velocity(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, -delta.y / 1.);
							jbox_invalidate_layer((t_object *)x, NULL, gensym("surface"));
							jbox_redraw((t_jbox *)x);
							break;
						default:
							t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), patcherview, pt);
							move_node(x, &x->nodes[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx], coord);
							break;
					}
					break;
			}
			break;
		default:
			break;
	}
}



void nodes_mousewheel(t_nodes *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc){
	llll_format_modifiers(&modifiers, NULL);  

	if (dadaobj_mousewheel(dadaobj_cast(x), view, pt, modifiers, x_inc, y_inc)) {
		jbox_invalidate_layer((t_object *)x, NULL, gensym("surface"));
		jbox_redraw((t_jbox *)x);
		return;
	}
}



long nodes_keyup(t_nodes *x, t_object *patcherview, long keycode, long modifiers, long textcharacter){
			
	llll_format_modifiers(&modifiers, &keycode);

	if (dadaobj_keyup(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
		return 1;
	
	return 0;
}

long nodes_key(t_nodes *x, t_object *patcherview, long keycode, long modifiers, long textcharacter)
{
	llll_format_modifiers(&modifiers, &keycode);

	if (dadaobj_key(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
		return 1;

	switch (keycode) {
/*		case JKEY_SPACEBAR:	// play/stop
			object_attr_setchar(x, _llllobj_sym_play, !x->play);
			jbox_redraw((t_jbox *)x);
			return 1;
		case JKEY_BACKSPACE:
			delete_selected_shapes(x);
			return 1;*/
		case JKEY_ESC:
			x->selected_nodes = x->selected_testers = 0;
            jbox_invalidate_layer((t_object *)x, NULL, gensym("surface"));
			jbox_redraw((t_jbox *)x);
			return 1;
		case 'a':
			if (modifiers == eCommandKey)
				nodes_select_all(x);
			return 1;
		default:
			break;
	}

	return 0;
}


void nodes_mouseenter(t_nodes *x, t_object *patcherview, t_pt pt, long modifiers) 
{
	if (dadaobj_mouseenter(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
}

void nodes_mouseleave(t_nodes *x, t_object *patcherview, t_pt pt, long modifiers) 
{
	if (dadaobj_mouseleave(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
}



////// UNDO HANDLING


void nodes_undo_postprocess(t_nodes *x)
{
	jbox_invalidate_layer((t_object *)x, NULL, gensym("surface"));
	jbox_redraw((t_jbox *)x);
}


void nodes_undo_step_push_nodes(t_nodes *x, t_symbol *operation)
{
	undo_add_interface_step(dadaobj_cast(x), DADA_FUNC_v_oX, (method)nodes_set_nodes , NULL, DADA_FUNC_X_o, (method)nodes_get_nodes, NULL, DADA_UNDO_OP_MODIFICATION, operation);
}
