/**
 @file
 dada.graph.c
 
 @name
 dada.graph
 
 @realname
 dada.graph
 
 @type
 object
 
 @module
 dada
 
 @author
 Daniele Ghisi
 
 @digest
 Graph network
 
 @description
 Provides an interface for graphs, including autopositioning of nodes
 
 @discussion
 The module relies on the Boost library in order to provide node autopositioning.
 
 @category
 dada, dada interfaces, dada rule-based systems
 
 @keywords
 graph, network, process,
 
 @seealso
 dada.machines, dada.nodes, bach.poset
 
 @owner
 Daniele Ghisi
 */

/// This define needs Boost to be loaded
//#ifdef MAC_VERSION
#define DADA_GRAPH_SUPPORT_VERTEX_PLACEMENT
//#endif

#include "dada.interface.h"
#include "dada.geometry.h"
#include "dada.paint.h"
#include "notation/notation.h"
//#include "dada.cursors.data.c"
#include "dada.math.h"
#include "dada.graphs.h"
#include "dada.popupmenu.h"
#include "dada.undo.h"
#include "dada.notation.h"

//#include "gvc.h"



#ifdef DADA_GRAPH_SUPPORT_VERTEX_PLACEMENT
#include <boost/config.hpp>
#include <boost/graph/fruchterman_reingold.hpp>
#include <boost/graph/random_layout.hpp>
#include <boost/graph/kamada_kawai_spring_layout.hpp>
#include <boost/graph/circle_layout.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/point_traits.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/limits.hpp>

using namespace boost;

#ifdef BOOST_NO_EXCEPTIONS
int foo = 1;
#endif

enum vertex_position_t { vertex_position };
namespace boost { BOOST_INSTALL_PROPERTY(vertex, position); }

typedef square_topology<>::point_type point;


struct simple_edge
{
    long first, second;
};
#endif


typedef enum _placement_algorithm
{
    DADA_GRAPH_ALGORITHM_RANDOM = 0,
    DADA_GRAPH_ALGORITHM_CIRCLE = 1,
    DADA_GRAPH_ALGORITHM_FRUCHTERMAN_REINGOLD_FORCE_DIRECTED_LAYOUT = 2,
    DADA_GRAPH_ALGORITHM_KAMADA_KAWAI_SPRING_LAYOUT = 3
} e_placement_algorithm;



#define DADA_UIGRAPH_VERTEX_SELECTION_PAD 6
#define DADA_UIGRAPH_EDGE_SELECTION_PAD 4

#define DADA_UIGRAPH_NODE_PAINT_PAD 4
#define DADA_UIGRAPH_CURVE_AMOUNT 25

#define DADA_UIGRAPH_DEBUG_IDS false


enum {
    DADA_GRAPH_NODEFORMAT_TEXT = 0,
    DADA_GRAPH_NODEFORMAT_NOTE = 1,
    DADA_GRAPH_NODEFORMAT_CHORD = 2,
    DADA_GRAPH_NODEFORMAT_ROLL = 3,
    DADA_GRAPH_NODEFORMAT_SCORE = 4,
};


////////////////////////// structures

typedef struct _uigraph
{
    t_dadaobj_jbox        b_ob; // root object
    
    // room and uigraph
    t_dada_graph        network_graph;    ///< The uigraph representing the bouncing room
    double                graph_arc_linewidth;
    
    char            autozoom;
    
    // node autopositioning
    char            autoposition_nodes;
    long            autoplacement_algorithm;
    double          autoplacement_size;
    
    // display
    char            show_arcs;
    char            show_nodes;
    char            show_arrows;
    char            show_arc_values;
    char            line_style;
    char            node_shape;
    double            node_size;
    char            node_format;
    long            tonedivision;
    char            edge_retouch_mode;
    
    t_jrgba            j_arccolor;
    t_jrgba            j_nodetextcolor;
    t_jrgba            j_nodebgcolor;
    t_jrgba            j_nodebordercolor;
    t_jrgba            j_turtlecolor;
    
    // Graphviz stuff
    //    GVC_t           *gvc;
    //    Agraph_t        *ag;
    
    // turtle
    long            turtled_vertex;
    t_llll          *turtled_vertex_history;
    t_atom          markov_avoid_repetition_memory;
    
    // utilities
    char            firsttime;
    char            itsme;
    char            creating_new_obj;
    char            need_recompute_nodes_width_height;
    
    // outlets are declared in the dadaobj->llllobj structure, at the beginning
} t_uigraph;



///////////////////////// function prototypes
//// standard set
void *uigraph_new(t_symbol *s, long argc, t_atom *argv);
void uigraph_free(t_uigraph *x);
void uigraph_assist(t_uigraph *x, void *b, long m, long a, char *s);

void uigraph_iar(t_uigraph *x);

void uigraph_paint(t_uigraph *x, t_object *view);
void uigraph_paint_ext(t_uigraph *x, t_object *view, t_dada_force_graphics *force_graphics);


void uigraph_int(t_uigraph *x, t_atom_long num);
void uigraph_float(t_uigraph *x, double num);
void uigraph_anything(t_uigraph *x, t_symbol *msg, long ac, t_atom *av);
void uigraph_bang(t_uigraph *x);


// get/set status
void uigraph_set_state(t_uigraph *x, t_llll *state);
t_llll *uigraph_get_state(t_uigraph *x);


// interface
void uigraph_focusgained(t_uigraph *x, t_object *patcherview);
void uigraph_focuslost(t_uigraph *x, t_object *patcherview);
void uigraph_mousedown(t_uigraph *x, t_object *patcherview, t_pt pt, long modifiers);
void uigraph_mousemove(t_uigraph *x, t_object *patcherview, t_pt pt, long modifiers);
void uigraph_mouseup(t_uigraph *x, t_object *patcherview, t_pt pt, long modifiers);
void uigraph_mousedrag(t_uigraph *x, t_object *patcherview, t_pt pt, long modifiers);
long uigraph_key(t_uigraph *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
long uigraph_keyup(t_uigraph *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
void uigraph_mousewheel(t_uigraph *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc);

void uigraph_mouseenter(t_uigraph *x, t_object *patcherview, t_pt pt, long modifiers);
void uigraph_mouseleave(t_uigraph *x, t_object *patcherview, t_pt pt, long modifiers);

t_max_err uigraph_notify(t_uigraph *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void uigraph_jsave(t_uigraph *x, t_dictionary *d);
void uigraph_preset(t_uigraph *x);
void uigraph_begin_preset(t_uigraph *x, t_symbol *s, long argc, t_atom *argv);
void uigraph_restore_preset(t_uigraph *x, t_symbol *s, long argc, t_atom *argv);
void uigraph_end_preset(t_uigraph *x);

// UNDO
void uigraph_undo_step_push_network(t_uigraph *x, t_symbol *operation);
void uigraph_postprocess_undo(t_uigraph *x);
void postprocess_network(t_uigraph *x);
void uigraph_network_process(t_uigraph *x, t_llll *ll);

t_max_err uigraph_setattr_linestyle(t_uigraph *x, t_object *attr, long ac, t_atom *av);
t_max_err uigraph_setattr_tonedivision(t_uigraph *x, t_object *attr, long ac, t_atom *av);

void uigraph_autozoom(t_uigraph *x);
void uigraph_recompute_nodes_width_height(t_uigraph *x);



///// uigraph ELEMENTS


char delete_edge(t_uigraph *x, long idx)
{
    uigraph_undo_step_push_network(x, gensym("Delete Edge"));
    
    if (!graph_delete_edge(&x->network_graph, idx)) {
        if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_EDGE && x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx == idx) {
            x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
            x->b_ob.d_ob.m_interface.mousemove_item_identifier.flag = 0;
        }
        
        if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_EDGE && x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx == idx) {
            x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADAITEM_TYPE_NONE;
            x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag = 0;
        }
        postprocess_network(x);
        return 0;
    }
    
    return 1;
}


char delete_vertex(t_uigraph *x, long idx, char preserve_edges)
{
    uigraph_undo_step_push_network(x, preserve_edges ? gensym("Remove Vertex") : gensym("Delete Vertex"));
    
    
    /*    if (false) {
     // keeping edges, whenever possible
     t_llll *edgeout = graph_vertex_get_outgoing_edges_list(&x->network_graph, idx);
     t_llll *edgein = graph_vertex_get_incoming_edges_list(&x->network_graph, idx);
     t_llllelem *edgein_el, *edgeout_el, *edgein_el_next, *edgeout_el_next;
     for (edgein_el = edgein->l_head; edgein_el; edgein_el = edgein_el_next) {
     edgein_el_next = edgein_el->l_next;
     long edgein = hatom_getlong(&edgein_el->l_hatom);
     long inlet = x->network_graph.edges[edgein].data.m_outinnum.num_in;
     // found edge from corresponding outlet
     
     for (edgeout_el = edgeout->l_head; edgeout_el; edgeout_el = edgeout_el_next) {
     edgeout_el_next = edgeout_el->l_next;
     long edgeout = hatom_getlong(&edgeout_el->l_hatom);
     long outlet = x->network_graph.edges[edgeout].data.m_outinnum.num_out;
     if (outlet == inlet) {
     graph_add_edge(&x->network_graph, x->network_graph.edges[edgein].start,
     x->network_graph.edges[edgeout].end,
     get_default_edge_metadata(&x->network_graph));
     }
     llll_destroyelem(edgeout_el);
     llll_destroyelem(edgein_el);
     }
     }
     llll_free(edgeout);
     llll_free(edgein);
     } */
    
    if (!graph_delete_vertex(&x->network_graph, idx, false)) {
        if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_VERTEX && x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx == idx) {
            x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
            x->b_ob.d_ob.m_interface.mousemove_item_identifier.flag = 0;
        }
        
        if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_VERTEX && x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx == idx) {
            x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADAITEM_TYPE_NONE;
            x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag = 0;
        }
        postprocess_network(x);
        return 0;
    }
    
    return 1;
}

void subdivide_edge(t_uigraph *x, long idx, long num_parts)
{
    uigraph_undo_step_push_network(x, gensym("Subdivide Edge"));
    graph_subdivide_edge(&x->network_graph, idx, num_parts, NULL, NULL);
    postprocess_network(x);
}

void move_vertex(t_uigraph *x, long idx, t_pt new_coord, char from_interface)
{
    uigraph_undo_step_push_network(x, gensym("Move Vertex"));
    t_pt new_processed_coord = x->network_graph.vertices[idx].r_it.coord;
    if (from_interface)
        drag_coord(dadaobj_cast(x), &new_processed_coord, new_coord, false);
    else
        new_processed_coord = new_coord;
    
    graph_move_vertex(&x->network_graph, idx, new_processed_coord);
    
    postprocess_network(x);
}


void move_edge_delta(t_uigraph *x, long idx, t_pt delta_coord, char from_interface)
{
    uigraph_undo_step_push_network(x, gensym("Move Edge"));
    t_pt delta_coord_processed = delta_coord;
    if (from_interface)
        drag_coord_delta(dadaobj_cast(x), &delta_coord_processed, false);
    
    graph_move_edge_delta(&x->network_graph, idx, delta_coord_processed);
    
    postprocess_network(x);
}


void change_label(t_uigraph *x, long idx, t_llll *new_label)
{
    if (idx >= 0 && idx < x->network_graph.num_vertices) {
        uigraph_undo_step_push_network(x, gensym("Change Label"));
        
        llll_free(x->network_graph.vertices[idx].data.m_llllnode.ll);
        x->network_graph.vertices[idx].data.m_llllnode.ll = new_label;
        
        postprocess_network(x);
    }
}



//////////////////////// global class pointer variable
t_class *uigraph_class;

void C74_EXPORT ext_main(void *moduleRef)
{	
	t_class *c;
	
	common_symbols_init();
	llllobj_common_symbols_init();
	
	srand(time(NULL)); 

	if (dada_check_bach_version() || llllobj_test()) {
		dada_error_bachcheck();
		return;
	}


	CLASS_NEW_CHECK_SIZE(c, "dada.graph", (method)uigraph_new, (method)uigraph_free, (long)sizeof(t_uigraph), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, JBOX_FONTATTR);	// include textfield and Fonts attributes
	//	jbox_initclass(c, 0);
	
	// paint & utilities
	class_addmethod(c, (method) uigraph_paint,			"paint", A_CANT, 0);
	class_addmethod(c, (method) uigraph_assist,			"assist",		A_CANT, 0);  
	class_addmethod(c, (method)	uigraph_notify,			"bachnotify",		A_CANT,		0);

	// save & preset
    class_addmethod(c, (method) uigraph_preset, "preset", 0);
    class_addmethod(c, (method) uigraph_begin_preset, "begin_preset", A_GIMME, 0);
    class_addmethod(c, (method) uigraph_restore_preset, "restore_preset", A_GIMME, 0);
    class_addmethod(c, (method) uigraph_end_preset, "end_preset", 0);
    CLASS_METHOD_ATTR_PARSE(c, "begin_preset", "undocumented", gensym("long"), 0L, "1");
    CLASS_METHOD_ATTR_PARSE(c, "restore_preset", "undocumented", gensym("long"), 0L, "1");
    CLASS_METHOD_ATTR_PARSE(c, "end_preset", "undocumented", gensym("long"), 0L, "1");
    class_addmethod(c, (method) uigraph_jsave, "jsave", A_CANT, 0);
    
    // interface
    class_addmethod(c, (method) uigraph_focusgained, "focusgained", A_CANT, 0);
    class_addmethod(c, (method) uigraph_focuslost, "focuslost", A_CANT, 0);
    
    // @method (mouse) @digest Edit content
    // @description
    // @copy DADA_DOC_MOUSE_COMMANDS_STANDARD_NAVIGATION
    // • <m>click+drag</m> on an element ot move it<br />
    //    ↪ Add the <m>Alt</m> key to duplicate it<br />
    // • <m>Cmd+click</m> (mac) or <m>Ctrl+click</m> (win) on to delete it<br />
    // • <m>right click</m> or <m>two fingers tap</m>: open contextual menu<br />
    class_addmethod(c, (method) uigraph_mousedown, "mousedown", A_CANT, 0);
    class_addmethod(c, (method) uigraph_mousedrag, "mousedrag", A_CANT, 0);
    class_addmethod(c, (method) uigraph_mouseup, "mouseup", A_CANT, 0);
    
    // @method (keyboard) @digest Edit content
    // @description
    // @copy DADA_DOC_KEYBOARDS_COMMANDS_STANDARD_NAVIGATION
    // • <m>Return</m>: place vertices automatically<br />
    // • <m>Cmd+Z</m> (mac) or <m>Ctrl+Z</m> (win): perform undo step<br />
    // • <m>Cmd+Shift+Z</m> (mac) or <m>Ctrl+Y</m> (win): perform redo step<br />
    // @copy DADA_DOC_TOOLS_INTRO
    // @copy DADA_DOC_TOOLS_ZX
    // @copy DADA_DOC_TOOLS_L
    class_addmethod(c, (method) uigraph_key, "key", A_CANT, 0);
    class_addmethod(c, (method) uigraph_keyup, "keyup", A_CANT, 0);
    class_addmethod(c, (method) uigraph_mousemove, "mousemove", A_CANT, 0);
    class_addmethod(c, (method) uigraph_mouseenter, "mouseenter", A_CANT, 0);
    class_addmethod(c, (method) uigraph_mouseleave, "mouseleave", A_CANT, 0);
    class_addmethod(c, (method) uigraph_mousewheel, "mousewheel", A_CANT, 0);
    
    class_addmethod(c, (method)uigraph_bang,            "bang",            0);
    
    // @method llll @digest Process <o>bach.roll</o>'s gathered syntax
    // @description Any <m>llll</m> will be considered as the <o>bach.roll</o>'s gathered syntax to be processed, and the
    // result is output through the outlet(s).
    class_addmethod(c, (method)uigraph_anything,    "anything",            A_GIMME,    0);
    class_addmethod(c, (method)uigraph_anything,    "setstoredstate",    A_GIMME, 0);
    
    
    // @method autozoom @digest Set domain and range automatically
    // @description Adapts view and zoom automatically according to the current stars' and planets' positions.
    class_addmethod(c, (method) uigraph_anything, "autozoom", A_GIMME, 0);
    
    // @method autocoord @digest Assign node coordinates automatically
    // @description Assigns the node coordinates automatically, according to the current <m>autocoordalgo</m>.
    class_addmethod(c, (method) uigraph_anything, "autocoord", A_GIMME, 0);
    
    
    // @method llll @digest Set state
    // @description Sets the current state of the object. The syntax must follow the one described in the
    // <m>dump</m> message documentation.
    class_addmethod(c, (method) uigraph_anything, "graph", A_GIMME, 0);
    
    // @method dump @digest Output state
    // @description Outputs the current state of the graph, in the syntax.
    //    <b>graph [<m>VERTEX1</m> <m>VERTEX2</m>...] [<m>EDGE1</m> <m>EDGE2</m>...]</b>.
    //  Each vertex is an llll shaped as <b>((coord <m>x</m> <m>y</m>) (label <m>label</m>) (bgcolor <m>r</m> <m>g</m> <m>b</m> <m>a</m>)
    // (bordercolor <m>r</m> <m>g</m> <m>b</m> <m>a</m>) (textcolor <m>r</m> <m>g</m> <m>b</m> <m>a</m>))</b>.
    //  Each edge is an llll shaped as <b>[<m>edge_start_vertex_index</m> <m>edge_end_vertex_index</m> [weight <m>edgeweight</m>]]</b>.
    class_addmethod(c, (method) uigraph_anything, "dump", A_GIMME, 0);
    
    
    // @method clear @digest Clear graph
    // @description Deletes all nodes and vertices.
    class_addmethod(c, (method) uigraph_anything, "clear", A_GIMME, 0);
    
    // @method domain @digest Set the X domain
    // @description The <m>domain</m> message, followed by two numbers, sets minimum and maximum coordinates
    // to be displayed on the X axis.
    // The <m>domain</m> message,  followed by the "start" or "end" symbol and a number, sets the coordinate
    // to be displayed respectively at the left boundary or at the right boundary of the object box.
    // @marg 0 @name arguments @optional 0 @type list
    class_addmethod(c, (method)uigraph_anything,        "domain",        A_GIMME,    0);
    
    // @method range @digest Set the Y range
    // @description The <m>range</m> message, followed by two numbers, sets minimum and maximum coordinates
    // to be displayed on the Y axis
    // The <m>range</m> message,  followed by the "start" or "end" symbol and a number, sets the coordinate
    // to be displayed respectively at the bottom boundary or at top right boundary of the object box.
    // @marg 0 @name arguments @optional 0 @type list
    class_addmethod(c, (method)uigraph_anything,        "range",        A_GIMME,    0);
    
    
    // @method getdomain @digest Retrieve current X domain
    // @description The <m>getdomain</m> message outputs from the third outlet the minimum and maximum
    // coordinates displayed on the X axis, preceded by a <m>domain</m> symbol.
    class_addmethod(c, (method)uigraph_anything,        "getdomain",        A_GIMME,    0);
    
    
    // @method getrange @digest Retrieve current Y range
    // @description The <m>getrange</m> message outputs from the third outlet the minimum and maximum
    // coordinates displayed on the Y axis, preceded by a <m>range</m> symbol.
    class_addmethod(c, (method)uigraph_anything,        "getrange",        A_GIMME,    0);
    
    
    
    
    // @method setturtle @digest Set the turtle
    // @description The <m>setturtle</m> message, followed by an integer <m>N</m> sets the turtle on the <m>N</m>-th vertex, without causing any output.
    // If followed by the "coord" symbol and an <m>llll</m> of the kind <b>[<m>x</m>, <m>y</m>]</b>
    // it sets the turtle on the nearest vertex to the given (<m>x</m>, <m>y</m>) location, always without causing any output. <br />
    // If <m>relativeturtle</m> is on, the coordinates are expected to be between 0 and 1, relative to the current domain and range
    // (caveat: more precisely, to the domain and range of the latest painted view of the object). <br />
    // If the <m>setturtle</m> message is followed by the "label" symbol, i.e. <b>setturtle label <m>vertexlabel</m></b>,
    // the turtle is positioned on the grain (if any) having <m>vertexlabel</m> as label.
    // @marg 0 @name label_or_coord @optional 1 @type sym
    // @marg 1 @name index_or_coord_or_label @optional 0 @type llll/sym
    // @example setturtle 3 @caption Set the turtle on the 3rd vertex
    // @example setturtle coord [0 10] @caption Set the turtle on the nearest vertex to x=0, y=10
    // @example setturtle label Warsaw @caption Set the turtle on the vertex having "Warsaw" as label
    class_addmethod(c, (method)uigraph_anything,        "setturtle",        A_GIMME,    0);
    
    
    // @method turtle @digest Set the turtle and output vertex data
    // @description The <m>setturtle</m> message, followed by an integer <m>N</m> sets the turtle on the <m>N</m>-th vertex,
    // outputting the corresponding vertex data, prepended by the "turtle" symbol and the vertex number.
    // If followed by the "coord" symbol and an <m>llll</m> of the kind <b>[<m>x</m>, <m>y</m>]</b>
    // it sets the turtle on the nearest vertex to the given (<m>x</m>, <m>y</m>) location. <br />
    // If <m>relativeturtle</m> is on, the coordinates are expected to be between 0 and 1, relative to the current domain and range
    // (caveat: more precisely, to the domain and range of the latest painted view of the object). <br />
    // If the <m>setturtle</m> message is followed by the "label" symbol, i.e. <b>setturtle label <m>vertexlabel</m></b>,
    // the turtle is positioned on the grain (if any) having <m>vertexlabel</m> as label.
    // @marg 0 @name label_or_coord @optional 1 @type sym
    // @marg 1 @name index_or_coord_or_label @optional 0 @type llll/sym
    // @example turtle 3 @caption Set the turtle on the 3rd vertex, and output vertex data
    // @example turtle coord [0 10] @caption Set the turtle on the nearest vertex to x=0, y=10, and output vertex data
    // @example turtle label Warsaw @caption Set the turtle on the vertex having "Warsaw" as label, and output vertex data
    class_addmethod(c, (method)uigraph_anything,        "turtle",        A_GIMME,    0);
    
    
    // @method getturtle @digest Output turtle vertex data
    // @description The <m>getturtle</m> message outputs the vertex data for the vertex where the turtle is currently located, if any.
    class_addmethod(c, (method)uigraph_anything,        "getturtle",        A_GIMME,    0);
    
    
    // @method turtlemarkov @digest Move the turtle on the probability graph
    // @description The <m>turtlemarkov</m> message will move the turtle on a vertex which is connected to the current vertex,
    // in a probabilistic fashion (i.e.: the more distant vertices are,
    // the less likely it is for the turtle to end up on them).
    // If <m>memory</m> is greater than 1, then repetition with previous states will be avoided, according to such attribute.
    // If there's no connected grain to the current turtled vertex, or if no new vertex could be reached, and "end" notification is sent.
    // @seealso turtleclear
    class_addmethod(c, (method)uigraph_anything,        "turtlemarkov",        A_GIMME,    0);
    
    
    // @method turtleclear @digest Clear history of turtled vertices
    // @description The <m>turtleclear</m> message will clear the history of turtled vertices (useful in combination with <m>turtlemarkov</m>,
    // to reset the repetition avoidance mechanism).
    // @seealso turtlemarkov
    class_addmethod(c, (method)uigraph_anything,        "turtleclear",        A_GIMME,    0);
    
    
    DADAOBJ_JBOX_DECLARE_READWRITE_METHODS(c);
    DADAOBJ_JBOX_DECLARE_IMAGE_METHODS(c);
    DADAOBJ_JBOX_DECLARE_ACCEPTSDRAG_METHODS(c);
    
    llllobj_class_add_out_attr(c, LLLL_OBJ_UI);
    dadaobj_class_init(c, LLLL_OBJ_UI, DADAOBJ_BBGIMAGE | DADAOBJ_ZOOM | DADAOBJ_CENTEROFFSET | DADAOBJ_EMBED | DADAOBJ_MOUSEHOVER | DADAOBJ_GRID | DADAOBJ_BORDER | DADAOBJ_BORDER_SHOWDEFAULT | DADAOBJ_LABELS | DADAOBJ_UNDO | DADAOBJ_AXES | DADAOBJ_NOTIFICATIONS | DADAOBJ_EXPORTTOJITTER);
    
    
    CLASS_ATTR_DEFAULT(c, "patching_rect", 0, "0 0 300 300");
    // @exclude dada.uigraph
    CLASS_ATTR_DEFAULT(c, "presentation_rect", 0, "0 0 300 300");
    // @exclude dada.uigraph
    
    
    CLASS_STICKY_ATTR(c,"category",0,"Color");
    
    CLASS_ATTR_RGBA(c, "arccolor", 0, t_uigraph, j_arccolor);
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "arccolor", 0, "0.3 0.3 0.3 1.");
    CLASS_ATTR_STYLE_LABEL(c, "arccolor", 0, "rgba", "Default Arc Color");
    // @description Sets the color of the arcs.
    
    CLASS_ATTR_RGBA(c, "nodebgcolor", 0, t_uigraph, j_nodebgcolor);
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "nodebgcolor", 0, "0.95 0.95 0.95 1.");
    CLASS_ATTR_STYLE_LABEL(c, "nodebgcolor", 0, "rgba", "Default Node Background Color");
    // @description Sets the default color of the node background.
    
    CLASS_ATTR_RGBA(c, "nodetextcolor", 0, t_uigraph, j_nodetextcolor);
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "nodetextcolor", 0, "0.1 0.1 0.1 1.");
    CLASS_ATTR_STYLE_LABEL(c, "nodetextcolor", 0, "rgba", "Default Node Text Color");
    // @description Sets the default color of the text in the nodes.
    
    CLASS_ATTR_RGBA(c, "nodebordercolor", 0, t_uigraph, j_nodebordercolor);
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "nodebordercolor", 0, "0.1 0.1 0.1 1.");
    CLASS_ATTR_STYLE_LABEL(c, "nodebordercolor", 0, "rgba", "Default Node Border Color");
    // @description Sets the default color of the border of nodes.
    
    CLASS_ATTR_RGBA(c, "turtlecolor", 0, t_uigraph, j_turtlecolor);
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "turtlecolor", 0, "0.34 0.87 0.20 1.");
    CLASS_ATTR_STYLE_LABEL(c, "turtlecolor", 0, "rgba", "Turtle Color");
    // @description Sets the color of the turtle.
    
    CLASS_STICKY_ATTR_CLEAR(c, "category");
    
    
    
    CLASS_STICKY_ATTR(c,"category",0,"Settings");
    
    CLASS_ATTR_CHAR(c, "autozoomwhenupdated", 0, t_uigraph, autozoom);
    CLASS_ATTR_STYLE_LABEL(c, "autozoomwhenupdated", 0, "onoff", "Auto Zoom When Updated");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"autozoomwhenupdated",0,"1");
    // @description Toggles the ability to adjust the zoom automatically when the graph is changed.
    
    CLASS_ATTR_CHAR(c, "autocoordwhenupdated", 0, t_uigraph, autoposition_nodes);
    CLASS_ATTR_STYLE_LABEL(c, "autocoordwhenupdated", 0, "enumindex", "Automatically Assign Node Coordinates When Updated");
    CLASS_ATTR_ENUMINDEX(c,"autocoordwhenupdated", 0, "Never If Not Assigned Always");
    CLASS_ATTR_BASIC(c, "autocoordwhenupdated", 0);
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"autocoordwhenupdated",0,"1");
    // @description Toggles the ability to assign node coordinates automatically, via the node placement
    // algorithm set by the attribute <m>autocoordalgo</m>.
    
    CLASS_ATTR_CHAR(c, "autocoordalgo", 0, t_uigraph, autoplacement_algorithm);
    CLASS_ATTR_STYLE_LABEL(c, "autocoordalgo", 0, "enumindex", "Autoplacement Algorithm");
    CLASS_ATTR_ENUMINDEX(c,"autocoordalgo", 0, "Random Circle Fruchterman-Reingold Kamada-Kawai");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"autocoordalgo",0,"2");
    // @description Sets the node placement algorithm for automatical node coordinates assignment.
    
    CLASS_ATTR_DOUBLE(c, "autocoordsize", 0, t_uigraph, autoplacement_size);
    CLASS_ATTR_STYLE_LABEL(c, "autocoordsize", 0, "text", "Autoplacement Start Canvas Size");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"autocoordsize",0,"100");
    // @description Size of the starting canvas for the autoplacement algorithm.
    
    CLASS_ATTR_CHAR(c, "tonedivision", 0, t_uigraph, tonedivision);
    CLASS_ATTR_STYLE_LABEL(c, "tonedivision", 0, "text", "Microtonal Division");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"tonedivision",0,"2");
    CLASS_ATTR_ACCESSORS(c, "tonedivision", (method)NULL, (method)uigraph_setattr_tonedivision);
    // @description @copy BACH_DOC_TONEDIVISION
    
    CLASS_ATTR_ATOM(c, "memory", 0, t_uigraph, markov_avoid_repetition_memory);
    CLASS_ATTR_STYLE_LABEL(c, "memory", 0, "text", "Markov Turtling Avoid Repetitions Memory");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"memory",0,"1");
    // @description Sets a number <m>N</m> so that repetitions of the same grain will be avoided before <m>N</m> steps have passed.
    // Set this value to "inf" to always avoid repetitions. Default is 1: repetition is only avoided with the current step (i.e.
    // the new step will be different from the current one.
    // A <m>turtleclear</m> message will reset the memory.
    
    CLASS_STICKY_ATTR_CLEAR(c, "category");
    
    
    CLASS_STICKY_ATTR(c,"category",0,"Appearance");
    
    CLASS_ATTR_CHAR(c, "shownodes", 0, t_uigraph, show_nodes);
    CLASS_ATTR_STYLE_LABEL(c, "shownodes", 0, "onoff", "Show Nodes");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"shownodes",0,"1");
    // @description Toggles the ability to show the nodes.
    
    CLASS_ATTR_CHAR(c, "showarrows", 0, t_uigraph, show_arrows);
    CLASS_ATTR_STYLE_LABEL(c, "showarrows", 0, "onoff", "Show Arrows");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showarrows",0,"1");
    // @description Toggles the ability to show the edge arrows.
    
    CLASS_ATTR_CHAR(c, "showedges", 0, t_uigraph, show_arcs);
    CLASS_ATTR_STYLE_LABEL(c, "showedges", 0, "onoff", "Show Edges");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showedges",0,"1");
    // @description Toggles the ability to show the edges.
    
    CLASS_ATTR_CHAR(c, "showweights", 0, t_uigraph, show_arc_values);
    CLASS_ATTR_STYLE_LABEL(c, "showweights", 0, "onoff", "Show Arc Weights");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showweights",0,"0");
    CLASS_ATTR_BASIC(c,"showweights",0);
    // @description Toggles the ability to show the edge weights.
    
    CLASS_ATTR_DOUBLE(c, "edgewidth", 0, t_uigraph, graph_arc_linewidth);
    CLASS_ATTR_STYLE_LABEL(c, "edgewidth", 0, "text", "Network Edge Line Width");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"edgewidth",0,"1.5");
    // @description Sets the line with for the edge lines.
    
    CLASS_ATTR_CHAR(c, "linestyle", 0, t_uigraph, line_style);
    CLASS_ATTR_STYLE_LABEL(c, "linestyle", 0, "enumindex", "Line Style");
    CLASS_ATTR_ENUMINDEX(c,"linestyle", 0, "Straight Segmented Curve");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"linestyle",0,"0");
    CLASS_ATTR_ACCESSORS(c, "linestyle", (method)NULL, (method)uigraph_setattr_linestyle);
    // @description Sets the line style for the edges.
    
    CLASS_ATTR_CHAR(c, "nodeshape", 0, t_uigraph, node_shape);
    CLASS_ATTR_STYLE_LABEL(c, "nodeshape", 0, "enumindex", "Node Shape");
    CLASS_ATTR_ENUMINDEX(c,"nodeshape", 0, "None Rectangular Ellipse");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"nodeshape",0,"0");
    // @description Sets the line style for the edges.
    
    CLASS_ATTR_CHAR(c, "nodeformat", 0, t_uigraph, node_format);
    CLASS_ATTR_STYLE_LABEL(c, "nodeformat", 0, "enumindex", "Node Format");
    CLASS_ATTR_ENUMINDEX(c,"nodeformat", 0, "Text Note");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"nodeformat",0,"0");
    // @description Sets the format for the node display.
    
    CLASS_ATTR_DOUBLE(c, "nodesize", 0, t_uigraph, node_size);
    CLASS_ATTR_STYLE_LABEL(c, "nodesize", 0, "text", "Node Size");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"nodesize",0,"0.");
    // @description Size of the node (0. meaning auto).
    
    
    CLASS_ATTR_CHAR(c, "edgeretouch", 0, t_uigraph, edge_retouch_mode);
    CLASS_ATTR_STYLE_LABEL(c, "edgeretouch", 0, "enumindex", "Edge Retouch");
    CLASS_ATTR_ENUMINDEX(c,"edgeretouch", 0, "None Snap To Border Snap To Midpoints");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"edgeretouch",0,"1");
    // @description Sets the edge retouch mode.
    
	CLASS_STICKY_ATTR_CLEAR(c, "category");

		
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	uigraph_class = c;
    dadaobj_class_add_fileusage_method(c);

	dev_post("dada.uigraph compiled %s %s", __DATE__, __TIME__);
	return;
}


t_max_err uigraph_setattr_tonedivision(t_uigraph *x, t_object *attr, long ac, t_atom *av)
{
    if (ac && av && is_atom_number(av)) {
        x->tonedivision = MAX(2, atom_getlong(av));
        if (x->tonedivision != 2 && x->tonedivision != 4 && x->tonedivision != 8)
            object_warn((t_object *)x, "Only 2, 4 and 8 tonedivision are graphically supported.");
    }
    return MAX_ERR_NONE;
}

t_max_err uigraph_setattr_linestyle(t_uigraph *x, t_object *attr, long ac, t_atom *av)
{
    if (ac && av && is_atom_number(av)) {
        x->line_style = atom_getlong(av);
        graph_change_line_style(&x->network_graph, (e_dada_line_style)x->line_style);
        uigraph_iar(x);
    }
    return MAX_ERR_NONE;
}


t_max_err uigraph_notify(t_uigraph *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
    if (msg == _sym_attr_modified) {
        t_symbol *attr_name = (t_symbol *)object_method((t_object *)data, _sym_getname);
        if (attr_name == _llllobj_sym_zoom || attr_name == gensym("center") || attr_name == gensym("showarcs") || attr_name == gensym("showweights")
            || attr_name == gensym("nodebgcolor") || attr_name == gensym("nodebordercolor")
            || attr_name == gensym("nodetextcolor") || attr_name == gensym("showarrows")) {
            uigraph_iar(x);
        } else if (attr_name == gensym("nodesize") || attr_name == gensym("nodeformat") || attr_name == gensym("nodeshape") || attr_name == gensym("shape") || attr_name == gensym("edgeretouch")) {
            x->need_recompute_nodes_width_height = true;
            uigraph_iar(x);
        } else if (attr_name == gensym("grid")) {
            jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
            jbox_redraw((t_jbox *)x);
        }
    }
    
    return MAX_ERR_NONE;
}


void uigraph_begin_preset(t_uigraph *x, t_symbol *s, long argc, t_atom *argv)
{
    dadaobj_begin_preset(dadaobj_cast(x), s, argc, argv);
}


void uigraph_restore_preset(t_uigraph *x, t_symbol *s, long argc, t_atom *argv)
{
    dadaobj_restore_preset(dadaobj_cast(x), s, argc, argv);
}

void uigraph_end_preset(t_uigraph *x)
{
    dadaobj_end_preset(dadaobj_cast(x));
}

void uigraph_preset(t_uigraph *x)
{
    dadaobj_preset(dadaobj_cast(x));
}


void uigraph_jsave(t_uigraph *x, t_dictionary *d)
{
    if (x->b_ob.d_ob.save_data_with_patcher){
        if (x->b_ob.r_ob.l_dictll) {
            llll_store_in_dictionary(x->b_ob.r_ob.l_dictll, d, "uigraph_data", NULL);
        } else {
            t_llll *data = uigraph_get_state(x);
            llll_store_in_dictionary(data, d, "uigraph_data", NULL);
            llll_free(data);
        }
    }
}



t_llll *uigraph_get_state(t_uigraph *x)
{
    t_llll *data = llll_get();
    llll_appendsym(data, gensym("graph"));
    llll_chain_clone(data, graph_to_llll(&x->network_graph));
    return data;
}



// see uigraph_get_state about the codification of info
void uigraph_set_state(t_uigraph *x, t_llll *state)
{
    
    t_llll *ll = llll_clone(state);
    
    if (ll->l_head && hatom_gettype(&ll->l_head->l_hatom) == H_SYM && hatom_getsym(&ll->l_head->l_hatom) == gensym("graph"))
        llll_behead(ll);
    
    x->itsme = true;
    graph_from_llll(ll, &x->network_graph);
    x->itsme = false;
    
    postprocess_network(x);
}



void uigraph_assist(t_uigraph *x, void *b, long m, long a, char *s)
{
    if (m == ASSIST_INLET) {     // @in 0 @type llll @digest Network graph, or messages
        sprintf(s, "llll: Graph or messages");
    }
    else {
        char *type = NULL;
        llllobj_get_llll_outlet_type_as_string((t_object *) x, LLLL_OBJ_UI, a, &type);
        if (a == 0)    // @out 0 @type llll @digest Dump outlet
            sprintf(s, "llll (%s): Dump Outlet", type);
        else if (a == 1)     // @out 1 @type llll @digest Node value on mouse hover or click
            sprintf(s, "llll (%s): Node Value on Mouse Hover or Click", type);
        else if (a == 2)    // @out 2 @type llll @digest Queries and notifications
            sprintf(s, "llll (%s): Queries and Notifications", type);
        else     // @out 3 @type bang @digest bang when object is changed via the interface
            sprintf(s, "bang when Changed");
    }
}

void uigraph_free(t_uigraph *x)
{
    llll_free(x->turtled_vertex_history);
    
    // more things to free
    graph_free(&x->network_graph);
    dadaobj_jbox_free((t_dadaobj_jbox *)x); // jbox_free and llllobj_free are inside here
}


void uigraph_iar(t_uigraph *x)
{
    jbox_invalidate_layer((t_object *)x, NULL, gensym("nodes"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("arcs"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
    jbox_redraw((t_jbox *)x);
}

void *uigraph_new(t_symbol *s, long argc, t_atom *argv)
{
    t_uigraph *x = NULL;
    t_dictionary *d = NULL;
    long boxflags;
    t_llll *llll_for_rebuild = NULL;
    
    if (!(d = object_dictionaryarg(argc,argv)))
        return NULL;
    
    if ((x = (t_uigraph *)object_alloc_debug(uigraph_class))) {
        char symmetric = false;
        
        //        x->gvc = gvContext();
        
        x->creating_new_obj = true;
        x->turtled_vertex = -1; // no cursor
        
        x->b_ob.d_ob.m_tools.curr_tool = DADA_TOOL_ARROW;
        x->firsttime = true;
        x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
        x->turtled_vertex_history = llll_get();
        
        boxflags = 0
        | JBOX_DRAWFIRSTIN
        | JBOX_NODRAWBOX
        | JBOX_DRAWINLAST
        | JBOX_TRANSPARENT
        //      | JBOX_NOGROW
        //        | JBOX_GROWY
        | JBOX_GROWBOTH
        | JBOX_HILITE
        //      | JBOX_BACKGROUND
        | JBOX_DRAWBACKGROUND
        //      | JBOX_NOFLOATINSPECTOR
        //      | JBOX_MOUSEDRAGDELTA
        //      | JBOX_TEXTFIELD
        ;
        
        x->need_recompute_nodes_width_height = true;
        
        jbox_new((t_jbox *)x, boxflags, argc, argv);
        x->b_ob.r_ob.l_box.b_firstin = (t_object *)x;
        
        dadaobj_jbox_setup((t_dadaobj_jbox *)x, DADAOBJ_BBGIMAGE | DADAOBJ_ZOOM | DADAOBJ_CENTEROFFSET | DADAOBJ_UNDO | DADAOBJ_CHANGEDBANG | DADAOBJ_NOTIFICATIONS, build_pt(1., 1.), 1, 2, 1, (dada_paint_ext_fn)uigraph_paint_ext, (invalidate_and_redraw_fn)uigraph_iar, "l", 1, "b44");
        dadaobj_addfunctions(dadaobj_cast(x), (dada_mousemove_fn)uigraph_mousemove, NULL, (method)uigraph_postprocess_undo, (get_state_fn)uigraph_get_state, (set_state_fn)uigraph_set_state, NULL, NULL, NULL);
        
        graph_new(&x->network_graph, symmetric ? DADA_GRAPH_FLAG_SYMMETRIC : DADA_GRAPH_FLAG_NONE, DADA_GRAPH_METADATA_LLLLNODE, DADA_GRAPH_METADATA_WEIGHT, DADA_LINE_CURVE);
        
        attr_dictionary_process(x,d);
        
        t_shape shape = ezbuild_dadapolygon(DADA_BLACK, 1, 4, -100., -100., 100., -100., 100., 100., -100., 100.);
        t_llll *defaultll1 = llll_from_text_buf("0", 0);
        t_llll *defaultll2 = llll_from_text_buf("1", 0);
        graph_add_vertex(&x->network_graph, build_pt(-100, 0), build_llllnode_metadata(defaultll1, x->j_nodebgcolor, x->j_nodebordercolor, x->j_nodetextcolor));
        graph_add_vertex(&x->network_graph, build_pt(100, 0), build_llllnode_metadata(defaultll2, x->j_nodebgcolor, x->j_nodebordercolor, x->j_nodetextcolor));
        graph_add_edge(&x->network_graph, 0, 1, get_default_edge_metadata(&x->network_graph));
        llll_free(defaultll1);
        llll_free(defaultll2);
        
        if ((llll_for_rebuild = llll_retrieve_from_dictionary(d, "uigraph_data"))) { // new method
            llllobj_manage_dict_llll((t_object *)x, LLLL_OBJ_UI, llll_for_rebuild);
            uigraph_set_state(x, llll_for_rebuild);
            llll_free(llll_for_rebuild);
        }
        
        jbox_ready((t_jbox *)x);
        
        dadaobj_set_current_version_number(dadaobj_cast(x));
        
        x->creating_new_obj = false;
    }
    return x;
}

void uigraph_int(t_uigraph *x, t_atom_long num)
{
    t_atom argv[1];
    atom_setlong(argv, num);
    uigraph_anything(x, _sym_list, 1, argv);
}

void uigraph_float(t_uigraph *x, double num)
{
    t_atom argv[1];
    atom_setfloat(argv, num);
    uigraph_anything(x, _sym_list, 1, argv);
}


void uigraph_autozoom(t_uigraph *x)
{
    dadaobj_cast(x)->m_zoom.must_autozoom = true;
    uigraph_iar(x);
}

void uigraph_autozoom_do(t_uigraph *x, t_object *view)
{
    t_rect rect;
    
    jbox_get_rect_for_view((t_object *)x, view, &rect);
    //    center = get_center_pix(dadaobj_cast(x), view, &rect);
    
    
    systhread_mutex_lock(x->b_ob.d_ob.l_mutex);
    
    long num_vertices = x->network_graph.num_vertices;
    
    if (num_vertices <= 0) {
        systhread_mutex_unlock(x->b_ob.d_ob.l_mutex);
        return;
    }
    
    // Initialize
    double max_x = x->network_graph.vertices[0].r_it.coord.x, min_x = max_x;
    double max_y = x->network_graph.vertices[0].r_it.coord.y, min_y = max_y;
    
    for (long v = 1; v < num_vertices; v++) {
        t_pt this_coord = x->network_graph.vertices[v].r_it.coord;
        t_pt wh = delta_pix_to_delta_coord(dadaobj_cast(x), build_pt(x->network_graph.vertices[v].data.m_llllnode.width/2., -x->network_graph.vertices[v].data.m_llllnode.height/2.));
        double w_2 = wh.x;
        double h_2 = wh.y;
        if (this_coord.x + w_2 > max_x)
            max_x = this_coord.x + w_2;
        if (this_coord.y + h_2 > max_y)
            max_y = this_coord.y + h_2;
        if (this_coord.x - w_2 < min_x)
            min_x = this_coord.x - w_2;
        if (this_coord.y - h_2 < min_y)
            min_y = this_coord.y - h_2;
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
    
    systhread_mutex_unlock(x->b_ob.d_ob.l_mutex);
    
    if (rect.width > 0 && rect.height > 0) {
        if ((max_x - min_x)/rect.width < (max_y - min_y)/rect.height) {
            dadaobj_setdomain(dadaobj_cast(x), view, min_x, max_x);
            dadaobj_setrange(dadaobj_cast(x), view, min_y, max_y);
        } else {
            dadaobj_setrange(dadaobj_cast(x), view, min_y, max_y);
            dadaobj_setdomain(dadaobj_cast(x), view, min_x, max_x);
        }
    }
}


void uigraph_dump(t_uigraph *x)
{
    t_llll *ll = uigraph_get_state(x);
    llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 0, ll);
    llll_free(ll);
}


void uigraph_bang(t_uigraph *x)
{
    uigraph_anything(x, _sym_bang, 0, NULL);
}


void send_turtle(t_uigraph *x)
{
    t_llll *ll = llll_get();
    llll_appendsym(ll, gensym("turtle"), 0, WHITENULL_llll);
    llll_appendlong(ll, x->turtled_vertex + 1, 0, WHITENULL_llll);
    llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, ll);
    llll_free(ll);
}

void send_markov_end(t_uigraph *x)
{
    t_llll *ll = llll_get();
    llll_appendsym(ll, gensym("end"), 0, WHITENULL_llll);
    llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, ll);
    llll_free(ll);
}

void uigraph_set_turtledvertex(t_uigraph *x, long vertex_id)
{
    long steps = (atom_gettype(&x->markov_avoid_repetition_memory) == A_SYM ? -1 : labs(atom_getlong(&x->markov_avoid_repetition_memory)));
    
    if (vertex_id >= 0)
        x->turtled_vertex = vertex_id;
    else
        x->turtled_vertex = -1;
    
    if (vertex_id >= 0)
        llll_prependlong(x->turtled_vertex_history, vertex_id);
    if (steps >= 0 && x->turtled_vertex_history->l_size > steps)
        llll_free(llll_slice(x->turtled_vertex_history, steps));
}

long move_turtle_markov(t_uigraph *x)
{
    long res = 0;
    
    dadaobj_mutex_lock(dadaobj_cast(x));
    if (x->turtled_vertex >= 0 && x->turtled_vertex < x->network_graph.num_vertices) {
        t_llll *adj_list = graph_vertex_get_outgoing_edges_list(&x->network_graph, x->turtled_vertex);
        t_llllelem *elem;
        
        // sieving adj_list according to turtle markov avoidance memory
        if (x->turtled_vertex_history->l_size > 1) {
            t_llllelem *nextelem;
            for (elem = adj_list->l_head; elem; elem = nextelem) {
                nextelem = elem->l_next;
                long edge = hatom_getlong(&elem->l_hatom);
                long new_cursor = x->network_graph.edges[edge].end;
                if (is_long_in_llll_first_level(x->turtled_vertex_history, new_cursor))
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
                double this_weight = MAX(0., x->network_graph.edges[edge].data.m_double);
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
                    double this_weight = MAX(0., x->network_graph.edges[edge].data.m_double);
                    sum += this_weight;
                    if (random_pick < sum) {
                        new_cursor = x->network_graph.edges[edge].end;
                        break;
                    }
                }
                
                if (new_cursor < 0)
                    res = 1; // done
                else {
                    uigraph_set_turtledvertex(x, new_cursor);
                }
            }
        }
    }
    dadaobj_mutex_unlock(dadaobj_cast(x));
    
    return res;
}





#ifdef DADA_GRAPH_SUPPORT_VERTEX_PLACEMENT

/*
 template<typename Graph>
 void
 test_cube(Graph*)
 //void uigraph_autoposition(t_uigraph *x)
 {
 enum {A, B, C, D, E, F, G, H};
 simple_edge cube_edges[12] = {
 {A, E}, {A, B}, {A, D}, {B, F}, {B, C}, {C, D}, {C, G}, {D, H},
 {E, H}, {E, F}, {F, G}, {G, H}
 };
 
 Graph g(&cube_edges[0], &cube_edges[12], 8);
 
 typedef typename graph_traits<Graph>::edge_iterator edge_iterator;
 typedef typename graph_traits<Graph>::vertex_iterator vertex_iterator;
 
 vertex_iterator vi, vi_end;
 int i = 0;
 for (tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
 put(vertex_index, g, *vi, i++);
 
 edge_iterator ei, ei_end;
 for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
 put(edge_weight, g, *ei, 1.0);
 std::cerr << "(" << (char)(get(vertex_index, g, source(*ei, g)) + 'A')
 << ", " << (char)(get(vertex_index, g, target(*ei, g)) + 'A')
 << ") ";
 }
 std::cerr << std::endl;
 
 minstd_rand gen;
 typedef square_topology<> Topology;
 Topology topology(gen, 50.0);
 std::vector<Topology::point_difference_type> displacements(num_vertices(g));
 rectangle_topology<> rect_top(gen, 0, 0, 50, 50);
 random_graph_layout(g, get(vertex_position, g), rect_top);
 
 fruchterman_reingold_force_directed_layout
 (g,
 get(vertex_position, g),
 topology,
 square_distance_attractive_force(),
 square_distance_repulsive_force(),
 all_force_pairs(),
 linear_cooling<double>(100),
 make_iterator_property_map(displacements.begin(),
 get(vertex_index, g),
 Topology::point_difference_type()));
 
 std::cout << "Cube layout (Fruchterman-Reingold).\n";
 //    print_graph_layout(g, get(vertex_position, g), square_topology<>(50.));
 //    dump_graph_layout("cube-fr", g, get(vertex_position, g));
 } */



template<typename Graph, typename PositionMap, typename Topology>
void print_graph_layout(const Graph& g, PositionMap position, const Topology& topology)
{
    typedef typename Topology::point_type Point;
    // Find min/max ranges
    Point min_point = position[*vertices(g).first], max_point = min_point;
    BGL_FORALL_VERTICES_T(v, g, Graph) {
        min_point = topology.pointwise_min(min_point, position[v]);
        max_point = topology.pointwise_max(max_point, position[v]);
    }
    
    
    for (int y = (int)min_point[1]; y <= (int)max_point[1]; ++y) {
        for (int x = (int)min_point[0]; x <= (int)max_point[0]; ++x) {
            typename graph_traits<Graph>::vertex_iterator vi, vi_end;
            // Find vertex at this position
            typename graph_traits<Graph>::vertices_size_type index = 0;
            for (tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi, ++index) {
                if ((int)position[*vi][0] == x && (int)position[*vi][1] == y)
                    break;
            }
            
            if (vi == vi_end) std::cout << ' ';
            else std::cout << (char)(index + 'A');
        }
        std::cout << std::endl;
    }
}

template<typename Graph, typename PositionMap, typename Topology>
void assign_points(const Graph& g, PositionMap position, const Topology& topology, t_dada_graph *dada_graph)
{
    typename graph_traits<Graph>::vertex_iterator vi, vi_end;
    // Find vertex at this position
    typename graph_traits<Graph>::vertices_size_type index = 0;
    for (tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi, ++index) {
        long idx = get(vertex_index, g, *vi);
        dada_graph->vertices[idx].r_it.coord.x = position[*vi][0];
        dada_graph->vertices[idx].r_it.coord.y = position[*vi][1];
        //        if ((int)position[*vi][0] == x && (int)position[*vi][1] == y)
        //            break;
    }
}

/*
 template<typename Graph, typename PositionMap>
 void dump_graph_layout(std::string name, const Graph& g, PositionMap position)
 {
 std::ofstream out((name + ".dot").c_str());
 out << "graph " << name << " {" << std::endl;
 
 typename graph_traits<Graph>::vertex_iterator vi, vi_end;
 for (tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi) {
 out << "  n" << get(vertex_index, g, *vi) << "[ pos=\""
 << (int)position[*vi][0] + 25 << ", " << (int)position[*vi][1] + 25
 << "\" ];\n";
 }
 
 typename graph_traits<Graph>::edge_iterator ei, ei_end;
 for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
 out << "  n" << get(vertex_index, g, source(*ei, g)) << " -- n"
 << get(vertex_index, g, target(*ei, g)) << ";\n";
 }
 out << "}\n";
 }
 */


struct kamada_kawai_done
{
    kamada_kawai_done() : last_delta() {}
    
    template<typename Graph>
    bool operator()(double delta_p,
                    typename boost::graph_traits<Graph>::vertex_descriptor /*p*/,
                    const Graph& /*g*/,
                    bool global)
    {
        if (global) {
            double diff = last_delta - delta_p;
            if (diff < 0) diff = -diff;
            last_delta = delta_p;
            return diff < 0.01;
        } else {
            return delta_p < 0.01;
        }
    }
    
    double last_delta;
};


template<typename Graph>
void
autoposition_nodes_do(Graph*, t_dada_graph *dada_graph, t_uigraph *x)
{
    const int numverts = dada_graph->num_vertices;
    const int numedg = dada_graph->num_edges;
    simple_edge *edge_array = (simple_edge *)bach_newptr(dada_graph->num_edges * sizeof(simple_edge));
    for (long i = 0; i < dada_graph->num_edges; i++) {
        edge_array[i].first = dada_graph->edges[i].start;
        edge_array[i].second = dada_graph->edges[i].end;
    }
    
    
    Graph g(&edge_array[0], &edge_array[numedg], numverts);
    
    typedef typename graph_traits<Graph>::edge_iterator edge_iterator;
    typedef typename graph_traits<Graph>::vertex_iterator vertex_iterator;
    
    vertex_iterator vi, vi_end;
    int i = 0;
    for (tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi) {
        put(vertex_index, g, *vi, i++);
    }
    
    edge_iterator ei, ei_end;
    for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
        put(edge_weight, g, *ei, 1.0);
        //        std::cerr << "(" << (char)(get(vertex_index, g, source(*ei, g)) + 'A') << ", " << (char)(get(vertex_index, g, target(*ei, g)) + 'A') << ") ";
    }
    //    std::cerr << std::endl;
    
    
    double graph_size = x->autoplacement_size;
    minstd_rand gen;
    typedef square_topology<> Topology;
    Topology topology(gen, 50.0);
    std::vector<Topology::point_difference_type> displacements(num_vertices(g));
    rectangle_topology<> rect_top(gen, 0, 0, graph_size, graph_size);
    
    switch (x->autoplacement_algorithm) {
        case DADA_GRAPH_ALGORITHM_RANDOM:
            random_graph_layout(g, get(vertex_position, g), rect_top);
            break;
            
        case DADA_GRAPH_ALGORITHM_CIRCLE:
            circle_graph_layout(g, get(vertex_position, g), graph_size/2.);
            break;
            
        case DADA_GRAPH_ALGORITHM_FRUCHTERMAN_REINGOLD_FORCE_DIRECTED_LAYOUT:
            random_graph_layout(g, get(vertex_position, g), rect_top);
            fruchterman_reingold_force_directed_layout(g,
                                                       get(vertex_position, g),
                                                       topology,
                                                       square_distance_attractive_force(),
                                                       square_distance_repulsive_force(),
                                                       all_force_pairs(),
                                                       linear_cooling<double>(1000),
                                                       make_iterator_property_map(displacements.begin(),
                                                                                  get(vertex_index, g),
                                                                                  Topology::point_difference_type()));
            break;
            
        case DADA_GRAPH_ALGORITHM_KAMADA_KAWAI_SPRING_LAYOUT:
        {
            Topology::point_type origin;
            origin[0] = origin[1] = graph_size;
            Topology::point_difference_type extent;
            extent[0] = extent[1] = graph_size;
            
            circle_graph_layout(g, get(vertex_position, g), graph_size/2.);
            
            if (!kamada_kawai_spring_layout(g,
                                            get(vertex_position, g),
                                            get(edge_weight, g),
                                            topology,
                                            side_length(graph_size),
                                            kamada_kawai_done()))
                object_warn((t_object *)x, "Could not apply Kamada-Kawai spring layout.");
        }
            break;
            
        default:
            break;
    }
    
    
    
    //    print_graph_layout(g, get(vertex_position, g), square_topology<>(50.));
    assign_points(g, get(vertex_position, g), square_topology<>(50.), dada_graph);
}
#endif



void uigraph_autocoord_do(t_uigraph *x)
{
#ifdef DADA_GRAPH_SUPPORT_VERTEX_PLACEMENT
    typedef adjacency_list<listS, listS, undirectedS,
    // Vertex properties
    property<vertex_index_t, int,
    property<vertex_position_t, point> >,
    // Edge properties
    property<edge_weight_t, double> > Graph;
    
    autoposition_nodes_do((Graph*)0, &x->network_graph, x);
    uigraph_recompute_nodes_width_height(x);
#endif
}

/*
 void uigraph_autoposition(t_uigraph *x)
 {
 t_dada_graph *dada_graph = &x->network_graph;
 
    // create a typedef for the Graph type
    typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;
//    typedef adjacency_list<vecS, vecS, undirectedS, VertexProperties, EdgeProperty> Graph
    
    // Make convenient labels for the vertices
//    enum { A, B, C, D, E, N };
    const int num_vertices = dada_graph->num_vertices;
    const char* name = "ABCDE";
    
    // writing out the edges in the graph
    typedef std::pair<int, int> Edge;
    //    Edge edge_array[] = { Edge(A,B), Edge(A,D), Edge(C,A), Edge(D,C), Edge(C,E), Edge(B,D), Edge(D,E) };
    const int num_edges = dada_graph->num_edges;
    Edge *edge_array = (Edge *)bach_newptr(dada_graph->num_edges * sizeof(Edge));
    for (long i = 0; i < dada_graph->num_edges; i++)
        Edge(dada_graph->edges[i].start, dada_graph->edges[i].end);
    
    // declare a graph object
    //    Graph g(num_vertices);
    Graph g(edge_array, edge_array + sizeof(edge_array) / sizeof(Edge), num_vertices);
    
    
    // add the edges to the graph object
    for (int i = 0; i < num_edges; ++i)
        add_edge(edge_array[i].first, edge_array[i].second, g);
    
    
    typedef graph_traits<Graph>::vertex_descriptor Vertex;
    
    // get the property map for vertex indices
    typedef property_map<Graph, vertex_index_t>::type IndexMap;
    IndexMap index = get(vertex_index, g);
    
    post("vertices(g) = ");
    typedef graph_traits<Graph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    for (vp = vertices(g); vp.first != vp.second; ++vp.first) {
        Vertex v = *vp.first;
        post("%ld", index[v]);
    }
    
    
    
    
    typedef typename graph_traits<Graph>::edge_iterator edge_iterator;
    typedef typename graph_traits<Graph>::vertex_iterator vertex_iterator;
    
    vertex_iterator vi, vi_end;
    int i = 0;
    for (tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
        put(vertex_index, g, *vi, i++);
    
    edge_iterator ei, ei_end;
    for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
        put(edge_weight, g, *ei, 1.0);
        std::cerr << "(" << (char)(get(vertex_index, g, source(*ei, g)) + 'A')
        << ", " << (char)(get(vertex_index, g, target(*ei, g)) + 'A')
        << ") ";
    }
    std::cerr << std::endl;
    
    
    
    minstd_rand gen;
    typedef square_topology<> Topology;
    Topology topology(gen, 50.0);
    std::vector<Topology::point_difference_type> displacements(num_vertices);
    rectangle_topology<> rect_top(gen, 0, 0, 50, 50);
    random_graph_layout(g, get(vertex_position, g), rect_top);
    
    fruchterman_reingold_force_directed_layout(g,
                                               get(vertex_position, g),
                                               topology,
                                               square_distance_attractive_force(),
                                               square_distance_repulsive_force(),
                                               all_force_pairs(),
                                               linear_cooling<double>(100),
                                               make_iterator_property_map(displacements.begin(),
                                                                          get(vertex_index, g),
                                                                          Topology::point_difference_type()));
    
    std::cout << "Cube layout (Fruchterman-Reingold).\n";
    print_graph_layout(g, get(vertex_position, g), square_topology<>(50.));
    
    bach_freeptr(edge_array);
}*/





long uigraph_get_1nn(t_uigraph *x, t_pt coord)
{
    double best_d = -1;
    long best = -1;
    dadaobj_mutex_lock(dadaobj_cast(x));
    for (long i = 0; i < x->network_graph.num_vertices; i++) {
        double this_d = pt_pt_distance_squared(x->network_graph.vertices[i].r_it.coord, coord);
        if (best_d < 0 || this_d < best_d) {
            best = i;
            best_d = this_d;
        }
    }
    dadaobj_mutex_unlock(dadaobj_cast(x));
    return best;
}

long uigraph_label_to_vertex(t_uigraph *x, t_llll *label, char lock_mutex)
{
    long found = -1;
    if (lock_mutex)
        dadaobj_mutex_lock(dadaobj_cast(x));
    for (long i = 0; i < x->network_graph.num_vertices; i++) {
        if (llll_eq_ignoretype(label, x->network_graph.vertices[i].data.m_llllnode.ll)) {
            found = i;
            break;
        }
    }
    if (lock_mutex)
        dadaobj_mutex_unlock(dadaobj_cast(x));
    return found;
}

// Beware, will modify args!!!!
// But won't free it
void uigraph_setturtle(t_uigraph *x, t_llll *args)
{
    dadaobj_mutex_lock(dadaobj_cast(x));
    if (is_hatom_number(&args->l_head->l_hatom)) {
        long vertex_id = hatom_getlong(&args->l_head->l_hatom);
        uigraph_set_turtledvertex(x, vertex_id);
    } else if (hatom_gettype(&args->l_head->l_hatom) == H_SYM && args->l_head->l_next) {
        t_symbol *s = hatom_getsym(&args->l_head->l_hatom);
        if (s == gensym("coord")) {
            t_pt pt = llll_to_pt(hatom_getllll(&args->l_head->l_next->l_hatom));
            uigraph_set_turtledvertex(x, uigraph_get_1nn(x, pt));
        } else if (s == gensym("label")) {
            llll_behead(args);
            uigraph_set_turtledvertex(x, uigraph_label_to_vertex(x, args, false));
        }
    }
    dadaobj_mutex_unlock(dadaobj_cast(x));
}


void uigraph_anything(t_uigraph *x, t_symbol *msg, long ac, t_atom *av)
{
    dadaobj_anything(dadaobj_cast(x), msg, ac, av);
    
    t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, msg, ac, av, LLLL_PARSE_CLONE);
    if (parsed && parsed->l_head) {
        if (hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
            t_symbol *router = hatom_getsym(&parsed->l_head->l_hatom);
            llll_behead(parsed);
            
            if (dadaobj_anything_handle_domain_or_range(dadaobj_cast(x), router, parsed)) {
                // nothing to do!
            } else if (router == gensym("setstoredstate")) {
                uigraph_set_state(x, parsed);
            } else if (router == gensym("clear")) {
                dadaobj_mutex_lock(dadaobj_cast(x));
                graph_clear(&x->network_graph);
                dadaobj_mutex_unlock(dadaobj_cast(x));
                uigraph_iar(x);
            } else if (router == gensym("graph")) {
                uigraph_set_state(x, parsed);
                
                char must_autoposition = (x->autoposition_nodes > 0);
                
                if (x->autoposition_nodes == 1) {
                    for (t_llllelem *el = parsed->l_head; el; el = el->l_next) {
                        if (hatom_gettype(&el->l_hatom) != H_LLLL)
                            continue;
                        t_llll *el_ll = hatom_getllll(&el->l_hatom);
                        if (!el_ll || !el_ll->l_head || hatom_gettype(&el_ll->l_head->l_hatom) != H_SYM || hatom_getsym(&el_ll->l_head->l_hatom) != gensym("vertices"))
                            continue;
                        for (t_llllelem *subel = el_ll->l_head->l_next; subel; subel = subel->l_next) { // iterate on vertex llll
                            if (hatom_gettype(&subel->l_hatom) != H_LLLL)
                                continue;
                            t_llll *vert_ll = hatom_getllll(&subel->l_hatom);
                            if (!vert_ll)
                                continue;
                            for (t_llllelem *subsubel = vert_ll->l_head; subsubel; subsubel = subsubel->l_next) {
                                if (hatom_gettype(&subsubel->l_hatom) != H_LLLL)
                                    continue;
                                t_llll *prop_ll = hatom_getllll(&subsubel->l_hatom);
                                if (prop_ll && prop_ll->l_head && hatom_gettype(&prop_ll->l_head->l_hatom) == H_SYM && hatom_getsym(&prop_ll->l_head->l_hatom)== gensym("coord")) {
                                    must_autoposition = false;
                                    break;
                                }
                            }
                            
                            if (!must_autoposition)
                                break;
                        }
                        if (!must_autoposition)
                            break;
                    }
                }
                
                x->need_recompute_nodes_width_height = true;
                
                if (must_autoposition)
                    uigraph_autocoord_do(x);
                
                if (x->autozoom) {
                    dadaobj_cast(x)->m_zoom.must_autozoom = true;
                    uigraph_iar(x);
                }
                
            } else if (router == gensym("autozoom")) {
                dadaobj_cast(x)->m_zoom.must_autozoom = true;
                uigraph_iar(x);
            } else if (router == gensym("autocoord")) {
                uigraph_autocoord_do(x);
                dadaobj_cast(x)->m_zoom.must_autozoom = true;
                uigraph_iar(x);
                
            } else if (router == _sym_dump) {
                uigraph_dump(x);
                
            } else if (router == gensym("getturtle")) {
                if (x->turtled_vertex >= 0)
                    send_turtle(x);
                
            } else if (router == gensym("setturtle") && parsed->l_size >= 1) {
                // set the turtle to a given grain, without outputting the result
                uigraph_setturtle(x, parsed);
                jbox_redraw((t_jbox *)x);
                
            } else if (router == gensym("turtle") && parsed->l_size >= 1) {
                // set the turtle to a given grain,
                uigraph_setturtle(x, parsed);
                if (x->turtled_vertex >= 0)
                    send_turtle(x);
                jbox_redraw((t_jbox *)x);
                
            } else if (router == gensym("turtleclear")) {
                llll_clear(x->turtled_vertex_history);
            } else if (router == gensym("turtlemarkov")) {
                // moving turtle to one of the neighbors
                if (move_turtle_markov(x)) {
                    send_markov_end(x);
                } else if (x->turtled_vertex) {
                    send_turtle(x);
                }
                jbox_redraw((t_jbox *)x);
            }
        }
        
    }
    llll_free(parsed);
}




/// *************************************




long pixel_to_uigraph_vertex(t_uigraph *x, t_pt pt, t_object *view, t_pt *coordinates)
{
    t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), view, pt);
    if (coordinates)
        *coordinates = coord;
    return graph_coord_to_vertex(dadaobj_cast(x), &x->network_graph, coord, -1, DADA_UIGRAPH_VERTEX_SELECTION_PAD);
}

long pixel_to_uigraph_edge(t_uigraph *x, t_pt pt, t_object *view, t_pt *coordinates)
{
    t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), view, pt);
    if (coordinates)
        *coordinates = coord;
    
    return graph_coord_to_edge(dadaobj_cast(x), &x->network_graph, coord, -1, DADA_UIGRAPH_EDGE_SELECTION_PAD);
}


t_dadaitem_identifier pixel_to_element(t_uigraph *x, t_pt pt, t_object *view, t_pt *coordinates)
{
    t_dadaitem_identifier result;
    long idx = -1;
    result.type = DADAITEM_TYPE_NONE;
    result.flag = 0;
    result.idx = result.secondary_idx = result.tertiary_idx = -1;
    
    if ((idx = pixel_to_uigraph_vertex(x, pt, view, coordinates)) >= 0) {
        result.type = DADAITEM_TYPE_VERTEX;
        result.idx = idx;
    } else if ((idx = pixel_to_uigraph_edge(x, pt, view, coordinates)) >= 0) {
        result.type = DADAITEM_TYPE_EDGE;
        result.idx = idx;
    }
    
    return result;
}



//// GRAPHIC DRAWING



void uigraph_recompute_nodes_width_height(t_uigraph *x)
{
    long i;
    double fontsize = jbox_get_fontsize((t_object *)x);
    t_jfont *jf = jfont_create_debug(jbox_get_fontname((t_object *)x)->s_name, (t_jgraphics_font_slant)jbox_get_font_slant((t_object *)x), (t_jgraphics_font_weight)jbox_get_font_weight((t_object *)x), fontsize);
    
    for (i = 0; i < x->network_graph.num_vertices; i++) {
        // paint machine
        if (!x->network_graph.vertices[i].data.m_llllnode.ll)
            x->network_graph.vertices[i].data.m_llllnode.width = x->network_graph.vertices[i].data.m_llllnode.height = 0;
        else if (x->node_size > 0) {
            x->network_graph.vertices[i].data.m_llllnode.width = x->network_graph.vertices[i].data.m_llllnode.height = x->node_size;
        } else {
            switch (x->node_format) {
                case DADA_GRAPH_NODEFORMAT_TEXT:
                {
                    char *buf = NULL;
                    llll_to_text_buf(x->network_graph.vertices[i].data.m_llllnode.ll, &buf, 0, BACH_DEFAULT_MAXDECIMALS, LLLL_T_NONE, LLLL_TE_NONE, LLLL_TB_NONE, NULL);
                    jfont_text_measure(jf, buf, &x->network_graph.vertices[i].data.m_llllnode.width, &x->network_graph.vertices[i].data.m_llllnode.height);
                    bach_freeptr(buf);
                }
                    break;
                    
                case DADA_GRAPH_NODEFORMAT_NOTE:
                    x->network_graph.vertices[i].data.m_llllnode.height = fontsize * 5.;
                    x->network_graph.vertices[i].data.m_llllnode.width = fontsize * 3.7;
                    break;
                    
                case DADA_GRAPH_NODEFORMAT_ROLL:
                    x->network_graph.vertices[i].data.m_llllnode.height = fontsize * 5.;
                    x->network_graph.vertices[i].data.m_llllnode.width = fontsize * 10.;
                    break;
                    
                default:
                    break;
            }
        }
    }
    jfont_destroy_debug(jf);
}


void uigraph_vertex_to_properties(t_dada_graph_vertex *v, double *width, double *height)
{
    *width = v->data.m_llllnode.width + DADA_UIGRAPH_NODE_PAINT_PAD;
    *height = v->data.m_llllnode.height + DADA_UIGRAPH_NODE_PAINT_PAD;
}

void uigraph_edge_to_properties(t_dada_graph_edge *e, char *label)
{
    char *buf = double_to_string(e->data.m_double, 2);
    strncpy_zero(label, buf, 256);
    bach_freeptr(buf);
}

/*
 void uigraph_paint_single_arc(t_uigraph *x, t_jgraphics *g, t_object *view, t_dada_graph_edge *e,
 t_jrgba line_color, double line_width, char show_arc_values, t_jfont *jf_arc_values)
 {
 t_dada_graph_vertex *v1 = &x->network_graph.vertices[e->start];
 t_dada_graph_vertex *v2 = &x->network_graph.vertices[e->end];
 t_pt pix1 = coord_to_pix_from_view(dadaobj_cast(x), view, v1->r_it.coord);
 t_pt pix2 = coord_to_pix_from_view(dadaobj_cast(x), view, v2->r_it.coord);
 double width1 = v1->data.m_llllnode.width + DADA_UIGRAPH_NODE_PAINT_PAD, height1 = v1->data.m_llllnode.height + DADA_UIGRAPH_NODE_PAINT_PAD;
 double width2 = v2->data.m_llllnode.width + DADA_UIGRAPH_NODE_PAINT_PAD, height2 = v2->data.m_llllnode.height + DADA_UIGRAPH_NODE_PAINT_PAD;
 t_pt zoom = x->b_ob.d_ob.m_zoom.zoom;
 
 // choose start and end point
 t_pt start, end;
 if (fabs(pix1.x - pix2.x) > fabs(pix1.y - pix2.y)) { // delta x larger than delta y
 if (pix2.x > pix1.x) {
 start.x = pix1.x + width1 / 2.;
 end.x = pix2.x - width2 / 2.;
 start.y = pix1.y;
 end.y = pix2.y;
 } else {
 start.x = pix1.x - width1 / 2.;
 end.x = pix2.x + width2 / 2.;
 start.y = pix1.y;
 end.y = pix2.y;
 }
 } else {
 if (pix1.y > pix2.y) {
 start.y = pix1.y - height1 / 2.;
 end.y = pix2.y + height2 / 2.;
 start.x = pix1.x;
 end.x = pix2.x;
 } else {
 start.y = pix1.y + height1 / 2.;
 end.y = pix2.y - height2 / 2.;
 start.x = pix1.x;
 end.x = pix2.x;
 }
 }
 
 char *buf = NULL;
 if (show_arc_values)
 buf = double_to_string(e->data.m_double, 2);
 
 paint_curve_advanced(g, line_color, start, end, line_width, DADA_UIGRAPH_CURVE_AMOUNT * zoom.x, x->show_arrows, DADA_GRAPH_ARROW_SIZE * zoom.x, buf, jf_arc_values);
 if (buf)
 bach_freeptr(buf);
 
 if (DADA_UIGRAPH_DEBUG_IDS) { // debug IDs
 char buf2[100];
 snprintf_zero(buf2, 100, "{%ld}", ((long)e - (long)&x->network_graph.edges)/sizeof(t_dada_graph_edge));
 write_text_simple(g, jf_arc_values, x->j_arccolor, buf, 0.5*(pix1.x + pix2.x) + 2,
 0.5 * (pix1.y + pix2.y), 300, 300);
 }
 }
 */

void repaint_hovered_elements(t_uigraph *x, t_jgraphics *g, t_rect rect, t_pt center)
{
    
    if (x->turtled_vertex >= 0 && x->turtled_vertex < x->network_graph.num_vertices){
        t_dada_graph_vertex *v = &x->network_graph.vertices[x->turtled_vertex];
        t_pt pt2 = coord_to_pix(dadaobj_cast(x), center, v->r_it.coord);
        paint_rectangle(g, x->j_turtlecolor, change_alpha(x->j_turtlecolor, 0.3), pt2.x - (v->data.m_llllnode.width + DADA_UIGRAPH_NODE_PAINT_PAD)/2., pt2.y - (v->data.m_llllnode.height + DADA_UIGRAPH_NODE_PAINT_PAD)/2., v->data.m_llllnode.width + DADA_UIGRAPH_NODE_PAINT_PAD, v->data.m_llllnode.height + DADA_UIGRAPH_NODE_PAINT_PAD, 2);
    }
    
    
    // re-paint hovered elements
    if (x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_CREATE_LINE && x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_VERTEX) {
        t_dada_graph_vertex *v = &x->network_graph.vertices[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx];
        t_pt pt2 = coord_to_pix(dadaobj_cast(x), center, v->r_it.coord);
        paint_rectangle(g, x->j_nodebordercolor, change_alpha(x->j_nodebgcolor, 0.3), pt2.x - (v->data.m_llllnode.width + DADA_UIGRAPH_NODE_PAINT_PAD)/2., pt2.y - (v->data.m_llllnode.height + DADA_UIGRAPH_NODE_PAINT_PAD)/2., v->data.m_llllnode.width + DADA_UIGRAPH_NODE_PAINT_PAD, v->data.m_llllnode.height + DADA_UIGRAPH_NODE_PAINT_PAD, 2);
        
        paint_line(g, x->j_arccolor, pt2.x, pt2.y, x->b_ob.d_ob.m_interface.mousedrag_pix.x, x->b_ob.d_ob.m_interface.mousedrag_pix.y, 1);
    }
    
    if (x->b_ob.d_ob.m_interface.allow_mouse_hover) {
        switch (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type) {
            case DADAITEM_TYPE_VERTEX:
            {
                t_dada_graph_vertex *v = &x->network_graph.vertices[x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx];
                t_pt pt2 = coord_to_pix(dadaobj_cast(x), center, v->r_it.coord);
                paint_rectangle(g, x->j_nodebordercolor, change_alpha(x->j_nodebgcolor, 0.3), pt2.x - (v->data.m_llllnode.width + DADA_UIGRAPH_NODE_PAINT_PAD)/2., pt2.y - (v->data.m_llllnode.height + DADA_UIGRAPH_NODE_PAINT_PAD)/2., v->data.m_llllnode.width + DADA_UIGRAPH_NODE_PAINT_PAD, v->data.m_llllnode.height + DADA_UIGRAPH_NODE_PAINT_PAD, 2);
            }
                break;
                
            case DADAITEM_TYPE_EDGE:
            {
                t_pt pt1 = coord_to_pix(dadaobj_cast(x), center, x->network_graph.vertices[x->network_graph.edges[x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx].start].r_it.coord);
                t_pt pt2 = coord_to_pix(dadaobj_cast(x), center, x->network_graph.vertices[x->network_graph.edges[x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx].end].r_it.coord);
                t_pt avg = pt_number_prod(pt_pt_sum(pt1, pt2), 0.5);
                
                graph_paint_edge(dadaobj_cast(x), g, rect, center, &x->network_graph, change_alpha(x->j_arccolor, 0.3), x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx,
                                 0, 0, (vertex_to_properties_fn)uigraph_vertex_to_properties, x->graph_arc_linewidth + 2, x->edge_retouch_mode, (edge_to_properties_fn)uigraph_edge_to_properties, false, NULL, false);
            }
                break;
        }
    }
    
}


void uigraph_paint_arcs(t_uigraph *x, t_object *view, t_rect rect, t_pt center, t_dada_force_graphics *force_graphics)
{
    t_jgraphics *g = view ? jbox_start_layer((t_object *)x, view, gensym("arcs"), rect.width, rect.height) : force_graphics->graphic_context;
    
    t_rect rect_00 = build_rect(0, 0, rect.width, rect.height);
    double fontsize = jbox_get_fontsize((t_object *)x);
    t_jfont *jf = x->show_arc_values ? jfont_create_debug("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_BOLD, fontsize) : NULL;
    if (g) {
        graph_paint(dadaobj_cast(x), g, rect_00, center, &x->network_graph, x->j_arccolor, false, true, x->node_size, x->node_size,
                    (vertex_to_properties_fn)uigraph_vertex_to_properties, x->graph_arc_linewidth, x->edge_retouch_mode, (edge_to_properties_fn)uigraph_edge_to_properties, false, jf, x->show_arrows);
        
        if (view)
            jbox_end_layer((t_object *)x, view, gensym("arcs"));
    }
    
    if (jf)
        jfont_destroy_debug(jf);
    
    if (view)
        jbox_paint_layer((t_object *)x, view, gensym("arcs"), 0., 0.);    // position of the layer
}




void uigraph_paint_nodes(t_uigraph *x, t_object *view, t_rect rect, t_pt center, t_dada_force_graphics *force_graphics)
{
    
    t_jgraphics *g = view ? jbox_start_layer((t_object *)x, view, gensym("nodes"), rect.width, rect.height) : force_graphics->graphic_context;
    
    t_rect rect_00 = build_rect(0, 0, rect.width, rect.height);
    if (g) {
        double fontsize = jbox_get_fontsize((t_object *)x);
        t_jfont *jf = jfont_create_debug(jbox_get_fontname((t_object *)x)->s_name, (t_jgraphics_font_slant)jbox_get_font_slant((t_object *)x), (t_jgraphics_font_weight)jbox_get_font_weight((t_object *)x), fontsize);
        //        t_jfont *jf = jfont_create_debug("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_BOLD, node_font_size);
        char buf[100];
        
        for (long i = 0; i < x->network_graph.num_vertices; i++) {
            // paint node
            t_pt pix = coord_to_pix(dadaobj_cast(x), center, x->network_graph.vertices[i].r_it.coord);
            double width = x->network_graph.vertices[i].data.m_llllnode.width + DADA_UIGRAPH_NODE_PAINT_PAD;
            double height = x->network_graph.vertices[i].data.m_llllnode.height + DADA_UIGRAPH_NODE_PAINT_PAD;
            t_jrgba bg_color = x->network_graph.vertices[i].data.m_llllnode.bgcolor;
            t_jrgba border_color = x->network_graph.vertices[i].data.m_llllnode.bordercolor;
            t_jrgba text_color = x->network_graph.vertices[i].data.m_llllnode.textcolor;
            
            if (bg_color.red < 0) bg_color = x->j_nodebgcolor;
            if (border_color.red < 0) border_color = x->j_nodebordercolor;
            if (text_color.red < 0) text_color = x->j_nodetextcolor;
            
            if (is_pt_in_rectangle_tolerance(pix, rect_00, MAX(width, height)/2.)) {
                t_pt upperleft_corner = build_pt(pix.x - width/2., pix.y - height/2.);
                
                switch (x->node_shape) {
                    case 1:
                        paint_rectangle(g, border_color, bg_color, upperleft_corner.x, upperleft_corner.y, width, height, 0.5);
                        break;
                    case 2:
                        paint_ellipse_filled(g, bg_color, pix.x, pix.y, width/2., height/2.);
                        paint_ellipse_stroken(g, border_color, pix.x, pix.y, width/2., height/2., 0.5);
                        break;
                    default:
                        break;
                }
                
                switch (x->node_format) {
                    case DADA_GRAPH_NODEFORMAT_TEXT:
                    {
                        char *label = NULL;
                        llll_to_text_buf(x->network_graph.vertices[i].data.m_llllnode.ll, &label, 0, BACH_DEFAULT_MAXDECIMALS, LLLL_T_NONE, LLLL_TE_NONE, LLLL_TB_NONE, NULL);
                        if (label) {
                            write_text(g, jf, text_color, label, upperleft_corner.x, upperleft_corner.y,
                                       width+1, height+1, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, true, false);
                            bach_freeptr(label);
                        }
                    }
                        break;
                        
                    case DADA_GRAPH_NODEFORMAT_NOTE:
                    {
                        char *label = NULL;
                        llll_to_text_buf(x->network_graph.vertices[i].data.m_llllnode.ll, &label, 0, BACH_DEFAULT_MAXDECIMALS, LLLL_T_NONE, LLLL_TE_NONE, LLLL_TB_NONE, NULL);
                        long midicents = 6000;
                        if (x->network_graph.vertices[i].data.m_llllnode.ll && x->network_graph.vertices[i].data.m_llllnode.ll->l_head) {
                            if (is_hatom_number(&x->network_graph.vertices[i].data.m_llllnode.ll->l_head->l_hatom))
                                midicents = hatom_getdouble(&x->network_graph.vertices[i].data.m_llllnode.ll->l_head->l_hatom);
                            else if (hatom_gettype(&x->network_graph.vertices[i].data.m_llllnode.ll->l_head->l_hatom) == H_LLLL) {
                                t_llll *ll = hatom_getllll(&x->network_graph.vertices[i].data.m_llllnode.ll->l_head->l_hatom);
                                if (ll && ll->l_head && is_hatom_number(&ll->l_head->l_hatom))
                                    midicents = hatom_getdouble(&ll->l_head->l_hatom);
                            }
                        }
                        ezpaint_note_with_staff((t_object *)x, g, midicents, k_ACC_AUTO,
                                                x->tonedivision, build_pt(upperleft_corner.x, upperleft_corner.y + fontsize * 1.4),
                                                width, fontsize * 2, upperleft_corner.x + 31 * fontsize/12., false, &text_color, &text_color, &text_color);
                    }
                        break;
                        
                        
                        /// SUPER TEST!
                    case DADA_GRAPH_NODEFORMAT_ROLL:
                    {
                        t_object *roll = (t_object *)object_new(CLASS_NOBOX, gensym("bach.roll"));
                        
                        t_atom *av = NULL;
                        t_atom ret;
                        long ac = llll_deparse(x->network_graph.vertices[i].data.m_llllnode.ll, &av, 0, 0);
                        
                        object_method(roll, gensym("read"), ac, av);
                        bach_freeptr(av);
                        
                        object_free(roll);
                    }
                        /// SUPER TEST END
                        
                        
                    default:
                        break;
                }
                
                
                if (DADA_UIGRAPH_DEBUG_IDS) { // debug IDs
                    snprintf_zero(buf, 100, "<%ld>", i);
                    write_text_simple(g, jf, DADA_GREY_50, buf, upperleft_corner.x+width + 2,
                                      upperleft_corner.y, 300, 300);
                    
                }
            }
        }
        
        jfont_destroy_debug(jf);
        if (view)
            jbox_end_layer((t_object *)x, view, gensym("nodes"));
    }
    
    if (view)
        jbox_paint_layer((t_object *)x, view, gensym("nodes"), 0., 0.);    // position of the layer
}





void uigraph_paint_ext(t_uigraph *x, t_object *view, t_dada_force_graphics *force_graphics)
{
    t_rect rect = force_graphics->rect;
    t_jgraphics *g = force_graphics->graphic_context;
    t_pt center = force_graphics->center_pix;
    
    jgraphics_set_source_rgba(g, 0, 0, 0, 1); // alpha = 1;
    
    dadaobj_paint_background(dadaobj_cast(x), g, &rect);
    
    dadaobj_paint_grid(dadaobj_cast(x), view, force_graphics);
    
    //    if (x->b_ob.d_ob.m_interface.allow_mouse_hover && x->b_ob.d_ob.m_tools.curr_tool != DADA_TOOL_ZOOM && x->b_ob.d_ob.m_tools.curr_tool != DADA_TOOL_MOVE_CENTER)
    //        paint_hovered_elements1(x, g, view, rect, center);
    
    jgraphics_set_source_rgba(g, 0, 0, 0, 1); // alpha = 1;
    if (x->show_arcs)
        uigraph_paint_arcs(x, view, rect, center, force_graphics);
    if (x->show_nodes)
        uigraph_paint_nodes(x, view, rect, center, force_graphics);
    
    if (x->b_ob.d_ob.m_tools.curr_tool != DADA_TOOL_ZOOM && x->b_ob.d_ob.m_tools.curr_tool != DADA_TOOL_MOVE_CENTER)
        repaint_hovered_elements(x, g, rect, center);
    
    dadaobj_paint_border(dadaobj_cast(x), g, &rect);
}

void uigraph_paint(t_uigraph *x, t_object *view)
{
    if (x->need_recompute_nodes_width_height) {
        uigraph_recompute_nodes_width_height(x);
        x->need_recompute_nodes_width_height = false;
    }
    
    if (view && dadaobj_cast(x)->m_zoom.must_autozoom) {
        uigraph_autozoom_do(x, view);
        dadaobj_cast(x)->m_zoom.must_autozoom = false;
    }
    
    dadaobj_paint(dadaobj_cast(x), view);
}




///////// POPUP MENU FUNCTIONS

void popup_delete_edge(t_dadaobj *d_ob, t_symbol *label, const t_llll *address)
{
    t_uigraph *x = (t_uigraph *)d_ob->orig_obj;
    if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_EDGE)
        delete_edge(x, d_ob->m_interface.mousedown_item_identifier.idx);
}

void popup_delete_vertex(t_dadaobj *d_ob, t_symbol *label, const t_llll *address)
{
    t_uigraph *x = (t_uigraph *)d_ob->orig_obj;
    if (d_ob->m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_VERTEX) {
        long idx = d_ob->m_interface.mousedown_item_identifier.idx;
        
        delete_vertex(x, idx, label == gensym("Remove"));
    }
}

void popup_subdivide_edge(t_dadaobj *d_ob, t_symbol *label, const t_llll *address)
{
    t_uigraph *x = (t_uigraph *)d_ob->orig_obj;
    if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_EDGE)
        subdivide_edge(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, hatom_getlong(&address->l_tail->l_hatom));
}



void show_edge_popup_menu(t_uigraph *x, t_object *patcherview, t_pt pt, long modifiers)
{
    ezdisplay_popup_menu(dadaobj_cast(x), patcherview,
                         (char *)"Delete (Subdivide Into 2 Into 3 Into 4 Into 5 Into 6 Into 7 Into 8)", "0 0 0", "", "", "", "",
                         (void *)popup_delete_edge, (void *)popup_subdivide_edge, WHITENULL);
}



void show_vertex_popup_menu(t_uigraph *x, t_object *patcherview, t_pt pt, long modifiers)
{
    // what will be checked
    ezdisplay_popup_menu(dadaobj_cast(x), patcherview,
                         (char *)"Delete",
                         "0 0 0", "0", "", "", "",
                         (void *)popup_delete_vertex, WHITENULL);
}



void popup_add_node(t_dadaobj *d_ob, t_symbol *label, const t_llll *address)
{
    t_jrgba default_color = build_jrgba(-1, -1, -1, 0);
    t_uigraph *x = (t_uigraph *)d_ob->orig_obj;
    t_llll *ll = llll_from_text_buf("node", false);
    graph_add_vertex(&x->network_graph, d_ob->m_interface.mousedown_coord, build_llllnode_metadata(ll, default_color, default_color, default_color));
    llll_free(ll);
    postprocess_network(x);
}



void show_bg_popup_menu(t_uigraph *x, t_object *patcherview, t_pt pt, long modifiers)
{
    ezdisplay_popup_menu(dadaobj_cast(x), patcherview,
                         (char *)"Center View Reset Zoom separator Add Node",
                         "0 0 0 0 0 0", "", "", "", "",
                         (void *)popup_center_view, (void *)popup_reset_zoom, NULL, (void *)popup_add_node, WHITENULL);
}


////////// INTERFACE FUNCTIONS

void uigraph_focusgained(t_uigraph *x, t_object *patcherview) {
    if (dadaobj_focusgained(dadaobj_cast(x), patcherview))
        return;
}

void uigraph_focuslost(t_uigraph *x, t_object *patcherview) {
    if (dadaobj_focuslost(dadaobj_cast(x), patcherview))
        return;
}


void uigraph_output_notification(t_uigraph *x, t_dadaitem_identifier *ident, t_symbol *sym)
{
    long idx = ident->idx;
    t_llll *ll = llll_get();
    llll_appendsym(ll, sym);
    
    dadaobj_mutex_lock(dadaobj_cast(x));
    switch (ident->type) {
        case DADAITEM_TYPE_EDGE:
            llll_appendsym(ll, gensym("edge"));
            llll_appendlong(ll, ident->idx + 1);
            if (dadaobj_cast(x)->m_interface.send_notifications == DADAOBJ_NOTIFY_VERBOSE) {
                if (idx >= 0 && idx < x->network_graph.num_edges) {
                    long v1 = x->network_graph.edges[idx].start;
                    long v2 = x->network_graph.edges[idx].end;
                    if (v1 >= 0 && v1 < x->network_graph.num_vertices && v2 >= 0 && v2 < x->network_graph.num_vertices) {
                        llll_appendllll_clone(ll, x->network_graph.vertices[v1].data.m_llllnode.ll);
                        llll_appenddouble(ll, x->network_graph.edges[idx].data.m_double);
                        llll_appendllll_clone(ll, x->network_graph.vertices[v2].data.m_llllnode.ll);
                    }
                }
            }
            break;
            
        case DADAITEM_TYPE_VERTEX:
            llll_appendsym(ll, gensym("vertex"));
            llll_appendlong(ll, ident->idx + 1);
            if (dadaobj_cast(x)->m_interface.send_notifications == DADAOBJ_NOTIFY_VERBOSE) {
                if (idx >= 0 && idx < x->network_graph.num_vertices)
                    llll_appendllll_clone(ll, x->network_graph.vertices[idx].data.m_llllnode.ll);
            }
            break;
            
        default:
            llll_appendsym(ll, _llllobj_sym_none);
            break;
    }
    dadaobj_mutex_unlock(dadaobj_cast(x));
    
    dadaobj_send_notification_llll(dadaobj_cast(x), ll);
}


void uigraph_mousemove(t_uigraph *x, t_object *patcherview, t_pt pt, long modifiers)
{
    t_dadaitem_identifier old_ident = x->b_ob.d_ob.m_interface.mousemove_item_identifier;
    llll_format_modifiers(&modifiers, NULL);
    
    if (dadaobj_mousemove(dadaobj_cast(x), patcherview, pt, modifiers))
        return;
    
    if (x->b_ob.d_ob.m_interface.allow_mouse_hover) {
        if (!x->b_ob.d_ob.m_interface.mouse_is_down) {
            x->b_ob.d_ob.m_interface.mousemove_item_identifier = pixel_to_element(x, pt, patcherview, NULL);
            
            if (!dadaitem_identifier_eq(old_ident, x->b_ob.d_ob.m_interface.mousemove_item_identifier))
                uigraph_output_notification(x, &x->b_ob.d_ob.m_interface.mousemove_item_identifier, gensym("hover"));
            
            jbox_redraw((t_jbox *)x);
        }
    } else {
        if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type != DADAITEM_TYPE_NONE) {
            x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
            dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
            jbox_redraw((t_jbox *)x);
        }
    }
    
    
    if (popup_menu_is_shown(dadaobj_cast(x))) {
        dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
    } else if (modifiers & eAltKey && x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_EDGE) {
        dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_RESIZE_UPDOWN);
    } else if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_VERTEX && modifiers == eAltKey) {
        dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DUPLICATE_POINT);
    } else if ((x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_VERTEX || x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_EDGE)
               && modifiers == eCommandKey) {
        dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DELETE);
    } else if ((x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_VERTEX || x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_EDGE)
               && x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_ARROW) {
        dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_MOVE);
        //    } else if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_MACHINE_OUTLET) {
        //        dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_GLUE);
    } else {
        dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
    }
    
}


void uigraph_mousedown(t_uigraph *x, t_object *patcherview, t_pt pt, long modifiers){
    
    if (dadaobj_mousedown(dadaobj_cast(x), patcherview, pt, modifiers))
        return;
    
    x->b_ob.d_ob.m_interface.mousedown_item_identifier = pixel_to_element(x, pt, patcherview, &x->b_ob.d_ob.m_interface.mousedown_coord);
    
    if (modifiers & ePopupMenu) {
        
        switch (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type) {
            case DADAITEM_TYPE_EDGE:
                show_edge_popup_menu(x, patcherview, pt, modifiers);
                break;
            case DADAITEM_TYPE_VERTEX:
                show_vertex_popup_menu(x, patcherview, pt, modifiers);
                break;
            case DADAITEM_TYPE_NONE:
                show_bg_popup_menu(x, patcherview, pt, modifiers);
                break;
            default:
                break;
        }
        
    } else {
        
        llll_format_modifiers(&modifiers, NULL);
        
        uigraph_output_notification(x, &x->b_ob.d_ob.m_interface.mousedown_item_identifier, gensym("click"));
        
        switch (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type) {
            case DADAITEM_TYPE_EDGE:
                if (modifiers == eCommandKey) {
                    if (delete_edge(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx))
                        object_error((t_object *)x, "Can't delete edge.");
                }
                break;
                
            case DADAITEM_TYPE_VERTEX:
                if (modifiers == eCommandKey) {
                    if (delete_vertex(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, true))
                        object_error((t_object *)x, "Can't remove vertex.");
                }
                break;
                
            default:
                break;
        }
    }
    
    jbox_redraw((t_jbox *)x);
    
}

void uigraph_mouseup(t_uigraph *x, t_object *patcherview, t_pt pt, long modifiers){
    t_dadaitem_identifier mousedown_item_identifier = x->b_ob.d_ob.m_interface.mousedown_item_identifier;
    t_dadaitem_identifier mouseup_item_identifier = pixel_to_element(x, pt, patcherview, NULL);
    
    
    llll_format_modifiers(&modifiers, NULL);
    
    if (dadaobj_mouseup(dadaobj_cast(x), patcherview, pt, modifiers))
        return;
    
    if (x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_CREATE_LINE &&
        mousedown_item_identifier.type == DADAITEM_TYPE_VERTEX && mouseup_item_identifier.type == DADAITEM_TYPE_VERTEX &&
        mousedown_item_identifier.idx >= 0 && mousedown_item_identifier.idx < x->network_graph.num_vertices &&
        mouseup_item_identifier.idx >= 0 && mouseup_item_identifier.idx < x->network_graph.num_vertices) {
        
        uigraph_undo_step_push_network(x, gensym("Connect Nodes"));
        graph_add_edge(&x->network_graph, mousedown_item_identifier.idx, mouseup_item_identifier.idx, get_default_edge_metadata(&x->network_graph));
        postprocess_network(x);
        jbox_redraw((t_jbox *)x);
    }
    
    x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADAITEM_TYPE_NONE;
    x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag = 0;
}

void uigraph_mousedrag(t_uigraph *x, t_object *patcherview, t_pt pt, long modifiers){
    
    llll_format_modifiers(&modifiers, NULL);
    
    //    post("%ld", x->b_ob.d_ob.m_interface.mousedown_item_identifier.type);
    
    if (dadaobj_mousedrag(dadaobj_cast(x), patcherview, pt, modifiers))
        return;
    
    switch (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type) {
            
        case DADAITEM_TYPE_VERTEX:
            switch (modifiers) {
                case eAltKey:
                    if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag & DADAITEM_IDENTIFIER_FLAG_DUPLICATED) {
                        t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), patcherview, pt);
                        move_vertex(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, coord, true);
                    } else {
                        t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), patcherview, pt);
                        uigraph_undo_step_push_network(x, gensym("Duplicate Node"));
                        long new_idx = graph_duplicate_vertex(&x->network_graph, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, coord, false);
                        if (new_idx < 0) {
                            object_error((t_object *)x, "Can't duplicate node.");
                            x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
                        } else {
                            x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx = x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx = new_idx;
                            x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag |= DADAITEM_IDENTIFIER_FLAG_DUPLICATED;
                            jbox_redraw((t_jbox *)x);
                        }
                    }
                    break;
                default:
                    switch (x->b_ob.d_ob.m_tools.curr_tool) {
                        case DADA_TOOL_CREATE_LINE:
                            jbox_redraw((t_jbox *)x);
                            break;
                        default:
                            move_vertex(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, pix_to_coord_from_view(dadaobj_cast(x), patcherview, pt), true);
                            break;
                    }
                    break;
            }
            break;
            
        case DADAITEM_TYPE_EDGE:
        {
            switch (modifiers) {
                case eAltKey:
                {
                    // change weight
                    double curr_weight = x->network_graph.edges[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx].data.m_double;
                    double new_weight = curr_weight - x->b_ob.d_ob.m_interface.mousedrag_delta_pix.y / 20.;
                    x->network_graph.edges[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx].data.m_double = new_weight;
                    jbox_invalidate_layer((t_object *)x, NULL, gensym("arcs"));
                    jbox_redraw((t_jbox *)x);
                }
                    break;
                default:
                    t_pt delta = delta_pix_to_delta_coord(dadaobj_cast(x), x->b_ob.d_ob.m_interface.mousedrag_delta_pix);
                    move_edge_delta(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, delta, true);
                    break;
            }
        }
            break;
            
        default:
            break;
    }
}



void uigraph_mousewheel(t_uigraph *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc){
    llll_format_modifiers(&modifiers, NULL);
    
    if (dadaobj_mousewheel(dadaobj_cast(x), view, pt, modifiers, x_inc, y_inc)) {
        jbox_invalidate_layer((t_object *)x, NULL, gensym("nodes"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("arcs"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
        jbox_redraw((t_jbox *)x);
        return;
    }
}



long uigraph_keyup(t_uigraph *x, t_object *patcherview, long keycode, long modifiers, long textcharacter){
    
    llll_format_modifiers(&modifiers, &keycode);
    
    if (dadaobj_keyup(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
        return 1;
    
    return 0;
}

long uigraph_key(t_uigraph *x, t_object *patcherview, long keycode, long modifiers, long textcharacter)
{
    llll_format_modifiers(&modifiers, &keycode);
    
    if (dadaobj_key(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
        return 1;
    
    switch (keycode) {
        case JKEY_ESC:
            jbox_redraw((t_jbox *)x);
            return 1;
        case JKEY_TAB:
            uigraph_autozoom_do(x, patcherview);
            uigraph_iar(x);
            return 1;
        case JKEY_RETURN:
            uigraph_autocoord_do(x);
            uigraph_autozoom_do(x, patcherview);
            uigraph_iar(x);
            return 1;
        default:
            break;
    }
    
    return 0;
}


void uigraph_mouseenter(t_uigraph *x, t_object *patcherview, t_pt pt, long modifiers)
{
    if (dadaobj_mouseenter(dadaobj_cast(x), patcherview, pt, modifiers))
        return;
}

void uigraph_mouseleave(t_uigraph *x, t_object *patcherview, t_pt pt, long modifiers)
{
    if (dadaobj_mouseleave(dadaobj_cast(x), patcherview, pt, modifiers))
        return;
}



//// UNDO
void postprocess_network(t_uigraph *x)
{
    jbox_invalidate_layer((t_object *)x, NULL, gensym("nodes"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("arcs"));
    jbox_redraw((t_jbox *)x);
}


void uigraph_postprocess_undo(t_uigraph *x)
{
    jbox_invalidate_layer((t_object *)x, NULL, gensym("nodes"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("arcs"));
    jbox_redraw((t_jbox *)x);
}


void uigraph_undo_step_push_network(t_uigraph *x, t_symbol *operation)
{
    undo_add_interface_step(dadaobj_cast(x), DADA_FUNC_v_oX, (method)uigraph_set_state, NULL, DADA_FUNC_X_o, (method)uigraph_get_state, NULL, DADA_UNDO_OP_MODIFICATION,operation);
}



