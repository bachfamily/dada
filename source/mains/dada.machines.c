/**
	@file
	dada.machines.c
	
	@name
	dada.machines
	
	@realname 
	dada.machines

	@type
	object
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
	Machine networks
	
	@description
	Apply transformation to score or generic data via a machine networks
	
	@discussion
 
	@category
	dada, dada interfaces, dada rule-based systems

	@keywords
	graph, network, label, node, machine, modify, change, roll, score
	
	@seealso
	cage.bounce
	
	@owner
	Daniele Ghisi
*/


#include "dada.interface.h"
#include "dada.geometry.h"
#include "dada.paint.h"
#include "notation.h"
//#include "dada.cursors.data.c"
#include "dada.math.h"
#include "dada.graphs.h"
#include "dada.popupmenu.h"
#include "dada.undo.h"
#include "dada.notation.h"

#define DADA_MACHINES_MAX_NUM_PROTOTYPES 1000

#define DADA_MACHINES_BALL_SELECTION_PAD 4
#define DADA_MACHINES_VERTEX_SELECTION_PAD 6
#define DADA_MACHINES_EDGE_SELECTION_PAD 4
#define DADA_MACHINES_INLET_OUTLET_SELECTION_PAD 3

#define DADA_MACHINES_INLET_WIDTH 5
#define DADA_MACHINES_INLET_HEIGHT 3

#define DADA_MACHINE_MAX_EDGES_FOR_SAME_VERTICES (DADA_GRAPH_MAX_VANILLABOX_OUTS * DADA_GRAPH_MAX_VANILLABOX_OUTS)


#define DADA_MACHINES_DEBUG_IDS false

////////////////////////// structures
/*
typedef enum _machine_types
{
	DADA_MACHINE_IDLE = 0,	
	DADA_MACHINE_INLET = 1,	
	DADA_MACHINE_OUTLET = 2,	
	DADA_MACHINE_TRANSPOSEUP = 3,	
	DADA_MACHINE_TRANSPOSEDOWN,	
	DADA_MACHINE_SHIFTRIGHT,	
	DADA_MACHINE_SHIFTLEFT,		
	DADA_MACHINE_INVERT,		
	DADA_MACHINE_RETROGRADE,		
	DADA_MACHINE_SPLIT,		
	DADA_MACHINE_COMBINE,
    DADA_MACHINE_JOIN,
	DADA_MACHINE_MIX,
	DADA_MACHINE_STRETCH,		
	DADA_MACHINE_COMPRESS,		
	DADA_MACHINE_GENERATENOTE,		
} e_machine_types;
*/

typedef enum _machine_process
{
	DADA_MACHINES_PROCESS_ALL = 0,
	DADA_MACHINES_PROCESS_HOT = 1,
	DADA_MACHINES_PROCESS_COLD = 2,
} e_machine_process;

typedef enum _machine_elements
{
	DADAITEM_TYPE_MACHINE_INLET = 100,
	DADAITEM_TYPE_MACHINE_OUTLET = 101,
} e_machine_elements;

typedef struct _machines_weighted_type
{
	long type;
	double relative_weight;
} t_machines_weighted_type;

typedef struct _machines_distrib
{
	long						num_types;
	t_machines_weighted_type	*w_type;
	
	// stuff one can compute out of the previous stuff
	double						total_weight;
	long						min_ins;	// minimum number of inlets in the machines
	long						max_ins;	// maximum number of inlets in the machines
} t_machines_distrib;


typedef struct _machine_prototype
{
    long		type_id;
    t_symbol    *fullname;
    t_symbol    *name;
    t_symbol    *dispchar;
    long        num_ins;
    long        num_outs;
    method      fun;
} t_machine_prototype;


typedef struct _machines 
{
	t_dadaobj_jbox		b_ob; // root object

    // dictionary of machines
    long                num_prototypes;
    t_machine_prototype *prototype;
    
	// settings
    char                nonroll_data; // custom non-roll data
	long				num_machine_out;
	long				num_machine_in;
	double				transp; // amount of transposition in midicents
	double				shift; // amount of shift in milliseconds
    double              stretch; // stretch factor
	double				length_for_generated_note;
    
    // these are filled in at startup and never touched again
    long                idle_prototype_id;
    long                inlet_prototype_id;
    long                outlet_prototype_id;
    long                num_standard_prototypes;

	// room and graph
	t_dada_graph		network_graph;	///< The graph representing the bouncing room
	double				network_machine_size;
	double				network_edge_linewidth;
	
	// display
	char			show_network;
	char			show_machines;
	char			line_style;

	t_jrgba			j_networkcolor;
	t_jrgba			j_machinecolor;
    t_jrgba         j_selectioncolor;

	// utilities
	char			firsttime;
	char			itsme;
	char			creating_new_obj;
	
	long			n_in;   // space for the inlet number used by all the proxies
    void			*n_proxy1;
	
	// outlets are declared in the dadaobj->llllobj structure, at the beginning
} t_machines;



///////////////////////// function prototypes
//// standard set
void *machines_new(t_symbol *s, long argc, t_atom *argv);
void machines_free(t_machines *x);
void machines_assist(t_machines *x, void *b, long m, long a, char *s);

void machines_paint(t_machines *x, t_object *view);


void machines_int(t_machines *x, t_atom_long num);
void machines_float(t_machines *x, double num);
void machines_anything(t_machines *x, t_symbol *msg, long ac, t_atom *av);
void machines_bang(t_machines *x);

void set_prototypes_from_llll(t_machines *x, t_llll* proto_ll, char add_mode);
t_llll *get_prototypes_as_llll(t_machines *x);

// get/set status
void machines_set_state(t_machines *x, t_llll *state);
t_llll *machines_get_state_sel(t_machines *x, char get_prototypes, char get_machines);
t_llll *machines_get_state(t_machines *x);

t_llll *machines_get_network(t_machines *x);
void machines_set_network(t_machines *x, t_llll *geometry);


// interface
void machines_focusgained(t_machines *x, t_object *patcherview);
void machines_focuslost(t_machines *x, t_object *patcherview);
void machines_mousedown(t_machines *x, t_object *patcherview, t_pt pt, long modifiers);
void machines_mousemove(t_machines *x, t_object *patcherview, t_pt pt, long modifiers);
void machines_mouseup(t_machines *x, t_object *patcherview, t_pt pt, long modifiers);
void machines_mousedrag(t_machines *x, t_object *patcherview, t_pt pt, long modifiers);
long machines_key(t_machines *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
long machines_keyup(t_machines *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
void machines_mousewheel(t_machines *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc);

void machines_mouseenter(t_machines *x, t_object *patcherview, t_pt pt, long modifiers);
void machines_mouseleave(t_machines *x, t_object *patcherview, t_pt pt, long modifiers);

t_max_err machines_notify(t_machines *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void machines_jsave(t_machines *x, t_dictionary *d);
void machines_preset(t_machines *x);
void machines_begin_preset(t_machines *x, t_symbol *s, long argc, t_atom *argv);
void machines_restore_preset(t_machines *x, t_symbol *s, long argc, t_atom *argv);
void machines_end_preset(t_machines *x);

// UNDO
void machines_undo_step_push_network(t_machines *x, t_symbol *operation);
void machines_postprocess_undo(t_machines *x);
void postprocess_network(t_machines *x);
void machines_network_process(t_machines *x, t_llll *ll);

t_max_err machines_setattr_linestyle(t_machines *x, t_object *attr, long ac, t_atom *av);


void build_random_network(t_machines *x, t_pt starting_coord, double min_random_dist, double max_random_dist, long tot_num_machines, t_machines_distrib distrib);
t_pt node_pix_to_inlet_outlet_pix(t_machines *x, t_pt center, t_pt pix, long num, long total, char inlet_or_outlet, double zoom);
t_pt get_inlet_outlet_pix(t_machines *x, t_pt center, long idx, long num, char inlet_or_outlet, double zoom);



//// ADD MACHINE
long add_machine_type(t_machines *x, t_symbol *fullname, t_symbol *name, t_symbol *dispchar, long num_ins, long num_outs, method function)
{
    if (x->num_prototypes < DADA_MACHINES_MAX_NUM_PROTOTYPES) {
        long idx = x->num_prototypes;
        x->prototype[idx].fullname = fullname;
        x->prototype[idx].name = name;
        x->prototype[idx].dispchar = dispchar;
        x->prototype[idx].num_ins = num_ins;
        x->prototype[idx].num_outs = num_outs;
        x->prototype[idx].fun = function;
        x->num_prototypes++;
        return idx;
    } else {
        object_error((t_object *)x, "Can't add machine prototype: maximum number of machines prototypes reached");
        return -1;
    }
}


void machine_idle_fn(t_machines *x, long numins, t_llll **in, long numouts, t_llll **out)
{
    out[0] = in[0];
    if (!x->nonroll_data)
        dada_roll_prepend_roll_sym(out[0]);
}

void machine_inlet_fn(t_machines *x, long numins, t_llll **in, long numouts, t_llll **out)
{
    out[0] = in[0];
    if (!x->nonroll_data)
        dada_roll_prepend_roll_sym(out[0]);
}

void machine_outlet_fn(t_machines *x, long numins, t_llll **in, long numouts, t_llll **out)
{
    out[0] = in[0];
    if (!x->nonroll_data)
        dada_roll_prepend_roll_sym(out[0]);
}

void machine_swap_fn(t_machines *x, long numins, t_llll **in, long numouts, t_llll **out)
{
    out[0] = in[1];
    out[1] = in[0];
    if (!x->nonroll_data)
        dada_roll_prepend_roll_sym(out[0]);
}


void machine_transposeup_fn(t_machines *x, long numins, t_llll **in, long numouts, t_llll **out)
{
    dada_roll_transpose(in[0], x->transp);
    out[0] = in[0];
    dada_roll_prepend_roll_sym(out[0]);
}

void machine_transposedown_fn(t_machines *x, long numins, t_llll **in, long numouts, t_llll **out)
{
    dada_roll_transpose(in[0], -x->transp);
    out[0] = in[0];
    dada_roll_prepend_roll_sym(out[0]);
}

void machine_shiftleft_fn(t_machines *x, long numins, t_llll **in, long numouts, t_llll **out)
{
    dada_roll_shift(in[0], -x->shift);
    out[0] = in[0];
    dada_roll_prepend_roll_sym(out[0]);
}

void machine_shiftright_fn(t_machines *x, long numins, t_llll **in, long numouts, t_llll **out)
{
    dada_roll_shift(in[0], x->shift);
    out[0] = in[0];
    dada_roll_prepend_roll_sym(out[0]);
}

void machine_circularshiftleft_fn(t_machines *x, long numins, t_llll **in, long numouts, t_llll **out)
{
    dada_roll_circularshift(in[0], -x->shift);
    out[0] = in[0];
    dada_roll_prepend_roll_sym(out[0]);
}

void machine_circularshiftright_fn(t_machines *x, long numins, t_llll **in, long numouts, t_llll **out)
{
    dada_roll_circularshift(in[0], x->shift);
    out[0] = in[0];
    dada_roll_prepend_roll_sym(out[0]);
}


void machine_invert_fn(t_machines *x, long numins, t_llll **in, long numouts, t_llll **out)
{
    dada_roll_invert(in[0], 6000);
    out[0] = in[0];
    dada_roll_prepend_roll_sym(out[0]);
}

void machine_slice_fn(t_machines *x, long numins, t_llll **in, long numouts, t_llll **out)
{
    out[1] = dada_roll_slice(in[0], in[0]->l_thing.w_double / 2., true, true, false);
    out[0] = in[0];
    dada_roll_prepend_roll_sym(out[0]);
    dada_roll_prepend_roll_sym(out[1]);
}

void machine_split_fn(t_machines *x, long numins, t_llll **in, long numouts, t_llll **out)
{
    out[1] = dada_roll_split_preserve(in[0], in[0]->l_thing.w_double / 2., true, true, false);
    out[0] = in[0];
    dada_roll_prepend_roll_sym(out[0]);
    dada_roll_prepend_roll_sym(out[1]);
}

void machine_blend_fn(t_machines *x, long numins, t_llll **in, long numouts, t_llll **out)
{
    if (!in[0] && !in[1]) {
        out[0] = llll_get();
    } else if (!in[1]) {
        out[0] = in[0];
    } else if (!in[0]) {
        out[0] = in[1];
    } else {
        dada_roll_blend(in[0], in[1], MAX(in[0]->l_thing.w_double, in[1]->l_thing.w_double) / 2., true);
        out[0] = in[0];
    }
    dada_roll_prepend_roll_sym(out[0]);
}


void machine_join_fn(t_machines *x, long numins, t_llll **in, long numouts, t_llll **out)
{
    if (!in[0] && !in[1]) {
        out[0] = llll_get();
    } else if (!in[1]) {
        out[0] = in[0];
    } else if (!in[0]) {
        out[0] = in[1];
    } else {
        dada_roll_join(in[0], in[1]);
        out[0] = in[0];
    }
    dada_roll_prepend_roll_sym(out[0]);
}

void machine_mix_fn(t_machines *x, long numins, t_llll **in, long numouts, t_llll **out)
{
    if (!in[0] && !in[1]) {
        out[0] = llll_get();
    } else if (!in[1]) {
        out[0] = in[0];
    } else if (!in[0]) {
        out[0] = in[1];
    } else {
        dada_roll_mix(in[0], in[1]);
        out[0] = in[0];
    }
    dada_roll_prepend_roll_sym(out[0]);
}

void machine_retrograde_fn(t_machines *x, long numins, t_llll **in, long numouts, t_llll **out)
{
    dada_roll_retrograde(in[0], in[0]->l_thing.w_double);
    out[0] = in[0];
    dada_roll_prepend_roll_sym(out[0]);
}

void machine_stretch_fn(t_machines *x, long numins, t_llll **in, long numouts, t_llll **out)
{
    dada_roll_stretch(in[0], x->stretch);
    out[0] = in[0];
    dada_roll_prepend_roll_sym(out[0]);
}

void machine_compress_fn(t_machines *x, long numins, t_llll **in, long numouts, t_llll **out)
{
    dada_roll_stretch(in[0], 1./x->stretch);
    out[0] = in[0];
    dada_roll_prepend_roll_sym(out[0]);
}


void machine_generatenote_fn(t_machines *x, long numins, t_llll **in, long numouts, t_llll **out)
{
    out[0] = dada_roll_gen(0, 6000, x->length_for_generated_note, 100);
    dada_roll_prepend_roll_sym(out[0]);
}

void machine_pitchroute_fn(t_machines *x, long numins, t_llll **in, long numouts, t_llll **out)
{
    if (dada_roll_get_average_pitch(in[0], true) <= 6000) {
        out[0] = in[0];
        out[1] = dada_roll_gen_empty(dada_get_num_voices(in[0]));
    } else {
        out[1] = in[0];
        out[0] = dada_roll_gen_empty(dada_get_num_voices(in[0]));
    }
    dada_roll_prepend_roll_sym(out[0]);
    dada_roll_prepend_roll_sym(out[1]);
}

void machine_timeroute_fn(t_machines *x, long numins, t_llll **in, long numouts, t_llll **out)
{
    double t = dada_roll_get_average_timepos(in[0], true);
    if (t <= in[0]->l_thing.w_double / 2.) {
        out[0] = in[0];
        out[1] = dada_roll_gen_empty(dada_get_num_voices(in[0]));
    } else {
        out[1] = in[0];
        out[0] = dada_roll_gen_empty(dada_get_num_voices(in[0]));
    }
    dada_roll_prepend_roll_sym(out[0]);
    dada_roll_prepend_roll_sym(out[1]);
}


void machine_filterempty_fn(t_machines *x, long numins, t_llll **in, long numouts, t_llll **out)
{
    if (dada_roll_get_num_chords(in[0])) {
        out[0] = in[0];
    } else {
        llll_free(in[0]);
        out[0] = NULL;
    }
}

void load_default_machines(t_machines *x)
{
    // data flux related machines
    x->idle_prototype_id = add_machine_type(x, gensym("Idle"), gensym("idle"), gensym(" "), 1, 1, (method)machine_idle_fn);
    x->inlet_prototype_id = add_machine_type(x, gensym("Inlet"), gensym("inlet"), gensym("I"), 1, 1, (method)machine_inlet_fn);
    x->outlet_prototype_id = add_machine_type(x, gensym("Outlet"), gensym("outlet"), gensym("O"), 1, 1, (method)machine_outlet_fn);
    add_machine_type(x, gensym("Swap"), gensym("swap"), gensym("x"), 2, 2, (method)machine_swap_fn);
    
    // roll-related machines
    add_machine_type(x, gensym("Transpose Up"), gensym("transposeup"), gensym("↑"), 1, 1, (method)machine_transposeup_fn);
    add_machine_type(x, gensym("Transpose Down"), gensym("transposedown"), gensym("↓"), 1, 1, (method)machine_transposedown_fn);
    add_machine_type(x, gensym("Shift Left"), gensym("shiftleft"), gensym("←"), 1, 1, (method)machine_shiftleft_fn);
    add_machine_type(x, gensym("Shift Right"), gensym("shiftright"), gensym("→"), 1, 1, (method)machine_shiftright_fn);
    add_machine_type(x, gensym("Circular Shift Left"), gensym("circularshiftleft"), gensym("↫"), 1, 1, (method)machine_circularshiftleft_fn);
    add_machine_type(x, gensym("Circular Shift Right"), gensym("circularshiftright"), gensym("↬"), 1, 1, (method)machine_circularshiftright_fn);
    add_machine_type(x, gensym("Invert"), gensym("invert"), gensym("↕"), 1, 1, (method)machine_invert_fn);
    add_machine_type(x, gensym("Retrograde"), gensym("retrograde"), gensym("↩"), 1, 1, (method)machine_retrograde_fn);
    add_machine_type(x, gensym("Slice"), gensym("slice"), gensym("ʌ"), 1, 2, (method)machine_slice_fn);
    add_machine_type(x, gensym("Join"), gensym("join"), gensym("v"), 2, 1, (method)machine_join_fn);
    add_machine_type(x, gensym("Split"), gensym("split"), gensym("ᴖ"), 1, 2, (method)machine_split_fn);
    add_machine_type(x, gensym("Blend"), gensym("blend"), gensym("ᴗ"), 2, 1, (method)machine_blend_fn);
    add_machine_type(x, gensym("Mix"), gensym("mix"), gensym("+"), 2, 1, (method)machine_mix_fn);
    add_machine_type(x, gensym("Stretch"), gensym("stretch"), gensym("‹›"), 1, 1, (method)machine_stretch_fn);
    add_machine_type(x, gensym("Compress"), gensym("compress"), gensym("›‹"), 1, 1, (method)machine_compress_fn);
    add_machine_type(x, gensym("Filter Empty"), gensym("filterempty"), gensym("ø"), 1, 1, (method)machine_filterempty_fn);
    add_machine_type(x, gensym("Pitch Route"), gensym("pitchroute"), gensym("?"), 1, 2, (method)machine_pitchroute_fn);
    add_machine_type(x, gensym("Time Route"), gensym("timeroute"), gensym("¿"), 1, 2, (method)machine_timeroute_fn);
    x->num_standard_prototypes = 1 + add_machine_type(x, gensym("Generate Note"), gensym("generatenote"), gensym("♪"), 0, 1, (method)machine_generatenote_fn);
}



void add_custom_prototype_from_llllelem(t_machines *x, t_llllelem *elem)
{
    long a = x->num_prototypes;
    if (hatom_gettype(&elem->l_hatom) == H_LLLL && a < DADA_MACHINES_MAX_NUM_PROTOTYPES) {
        t_llll *this_llll = hatom_getllll(&elem->l_hatom);
        t_machine_prototype *pr = &x->prototype[a];

        llll_parseargs((t_object *)x, this_llll, "sssii",
                       gensym("name"), &pr->name,
                       gensym("fullname"), &pr->fullname,
                       gensym("char"), &pr->dispchar,
                       gensym("numins"), &pr->num_ins,
                       gensym("numouts"), &pr->num_outs);
        
        pr->fun = NULL; // lambda loop defined!
        x->num_prototypes++;
    }
}


// works also with r_ob = NULL, this is designed to have bach.quantize also take advantage of the articulationinfo system
void set_prototypes_from_llll(t_machines *x, t_llll* proto_ll, char add_mode)
{
    if (proto_ll) {
        t_llllelem *elem;
        if (!add_mode) // delete existing ones
            x->num_prototypes = x->num_standard_prototypes;
        
        for (elem = proto_ll->l_head; elem; elem = elem->l_next)
            add_custom_prototype_from_llllelem(x, elem);
    }
}

t_llll *get_prototypes_as_llll(t_machines *x)
{
    long i;
    t_llll *ll = llll_get();
    llll_appendsym(ll, gensym("prototypes"));
    for (i = x->num_standard_prototypes; i < x->num_prototypes; i++) {
        t_llll *this_proto = llll_get();
        t_machine_prototype *pr = &x->prototype[i];
        llll_appendllll(this_proto, symbol_and_symbol_to_llll(gensym("name"), pr->name));
        llll_appendllll(this_proto, symbol_and_symbol_to_llll(gensym("fullname"), pr->fullname));
        llll_appendllll(this_proto, symbol_and_symbol_to_llll(gensym("char"), pr->dispchar));
        llll_appendllll(this_proto, symbol_and_long_to_llll(gensym("numins"), pr->num_ins));
        llll_appendllll(this_proto, symbol_and_long_to_llll(gensym("numouts"), pr->num_outs));
        llll_appendllll(ll, this_proto);
    }
    
    return ll;
}





//// MACHINE SYMBOLS AND LABLES HANDLING
void machine_type_to_text(t_machines *x, long type_id, char *buf)
{
    sprintf(buf, "%s", x->prototype[type_id].dispchar->s_name);
}


long label_to_machine(t_machines *x, t_symbol *label)
{
    long i;
    for (i = 0; i < x->num_prototypes; i++) {
        if (label == x->prototype[i].name || label == x->prototype[i].fullname)
            return i;
    }
    return 0;
}

long machine_to_popup_index(t_machines *x, long machine_idx)
{
    return machine_idx;
}

t_symbol *machine_to_name(t_machines *x, long machine_type)
{
    return x->prototype[machine_type].name;
}

long machine_to_num_ins(t_machines *x, long machine_type)
{
    return x->prototype[machine_type].num_ins;
}

long machine_to_num_outs(t_machines *x, long machine_type)
{
    return x->prototype[machine_type].num_outs;
}

char are_inlet_and_outlet_connected(t_machines *x, long vertex1, long outlet1, long vertex2, long inlet2)
{
	long j;
	for (j = 0; j < x->network_graph.num_edges; j++)
		if (x->network_graph.edges[j].start == vertex1 && x->network_graph.edges[j].end == vertex2 &&
			x->network_graph.edges[j].data.m_outinnum.num_out == outlet1 && x->network_graph.edges[j].data.m_outinnum.num_in == inlet2)
			return true;
	
	return false;
}




///// GRAPH ELEMENTS


char delete_edge(t_machines *x, long idx)
{
	machines_undo_step_push_network(x, gensym("Delete Edge"));
	 
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


char delete_vertex(t_machines *x, long idx, char preserve_edges)
{
	machines_undo_step_push_network(x, preserve_edges ? gensym("Remove Vertex") : gensym("Delete Vertex"));
	
	
	if (preserve_edges) {
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
								   x->network_graph.edges[edgeout].end, build_outinnum_metadata(x->network_graph.edges[edgein].data.m_outinnum.num_out, x->network_graph.edges[edgeout].data.m_outinnum.num_in));
				}
				llll_destroyelem(edgeout_el);
			}
            llll_destroyelem(edgein_el);
		}
		llll_free(edgeout);
		llll_free(edgein);
	}
		
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

void subdivide_edge(t_machines *x, long idx, long num_parts)
{
	machines_undo_step_push_network(x, gensym("Subdivide Edge"));
	graph_subdivide_edge(&x->network_graph, idx, num_parts, NULL, NULL, x->network_machine_size, x->network_machine_size);
	postprocess_network(x);
}

void extrude_edge(t_machines *x, long idx)
{
	machines_undo_step_push_network(x, gensym("Extrude Edge"));
	graph_extrude_edge(&x->network_graph, idx, NULL, NULL, x->network_machine_size, x->network_machine_size);
	postprocess_network(x);
}


void move_vertex(t_machines *x, long idx, t_pt new_coord, char from_interface)
{
	machines_undo_step_push_network(x, gensym("Move Vertex"));
	t_pt new_processed_coord = x->network_graph.vertices[idx].r_it.coord;
	if (from_interface)
		drag_coord(dadaobj_cast(x), &new_processed_coord, new_coord, false);
	else
		new_processed_coord = new_coord;

	graph_move_vertex(&x->network_graph, idx, new_processed_coord);
	
	postprocess_network(x);
}


void move_edge_delta(t_machines *x, long idx, t_pt delta_coord, char from_interface)
{
	machines_undo_step_push_network(x, gensym("Move Edge"));
	t_pt delta_coord_processed = delta_coord;
	if (from_interface)
		drag_coord_delta(dadaobj_cast(x), &delta_coord_processed, false);
	
	graph_move_edge_delta(&x->network_graph, idx, delta_coord_processed);

	postprocess_network(x);
}


void change_machine(t_machines *x, long idx, long new_type)
{
	if (idx >= 0 && idx < x->network_graph.num_vertices) {
		machines_undo_step_push_network(x, gensym("Change Machine"));

		x->network_graph.vertices[idx].data.m_vanillabox.type = machine_to_name(x, new_type);
		long num_ins = x->network_graph.vertices[idx].data.m_vanillabox.num_ins = machine_to_num_ins(x, new_type);
		long num_outs = x->network_graph.vertices[idx].data.m_vanillabox.num_outs = machine_to_num_outs(x, new_type);
		
		// verify cables!
		long i;
		for (i = 0; i < x->network_graph.num_edges; ) {
			if (x->network_graph.edges[i].start == idx && x->network_graph.edges[i].data.m_outinnum.num_out >= num_outs)
				graph_delete_edge(&x->network_graph, i);
			else if (x->network_graph.edges[i].end == idx && x->network_graph.edges[i].data.m_outinnum.num_in >= num_ins)
				graph_delete_edge(&x->network_graph, i);
			else 
				i++;
		}
		
		postprocess_network(x);
	}
}

void change_machine_for_selection(t_machines *x, long long new_type)
{
    long i;
    char some_selected = false;
    for (i = 0; i < x->network_graph.num_vertices; i++) {
        if (dadaitem_is_selected(&x->network_graph.vertices[i].r_it)) {
            some_selected = true;
            break;
        }
    }
    
    if (some_selected) {
        machines_undo_step_push_network(x, gensym("Change Machines"));
        for (i = 0; i < x->network_graph.num_vertices; i++) {
            if (dadaitem_is_selected(&x->network_graph.vertices[i].r_it)) {
                
                x->network_graph.vertices[i].data.m_vanillabox.type = machine_to_name(x, new_type);
                long num_ins = x->network_graph.vertices[i].data.m_vanillabox.num_ins = machine_to_num_ins(x, new_type);
                long num_outs = x->network_graph.vertices[i].data.m_vanillabox.num_outs = machine_to_num_outs(x, new_type);
                
                // verify cables!
                long j;
                for (j = 0; j < x->network_graph.num_edges; ) {
                    if (x->network_graph.edges[j].start == i && x->network_graph.edges[j].data.m_outinnum.num_out >= num_outs)
                        graph_delete_edge(&x->network_graph, i);
                    else if (x->network_graph.edges[j].end == i && x->network_graph.edges[j].data.m_outinnum.num_in >= num_ins)
                        graph_delete_edge(&x->network_graph, j);
                    else
                        j++;
                }
            }
        }
        
        postprocess_network(x);
    }
}

void machines_autozoom_do(t_machines *x, t_object *view)
{
    t_rect rect;
    
    jbox_get_rect_for_view((t_object *)x, view, &rect);
    //	center = get_center_pix(dadaobj_cast(x), view, &rect);
    
    
    if (x->network_graph.num_vertices <= 0)
        return;
    
    systhread_mutex_lock(x->b_ob.d_ob.l_mutex);
    
    // Initialize
    long i;
    double max_x = x->network_graph.vertices[0].r_it.coord.x, min_x = max_x, max_y = x->network_graph.vertices[0].r_it.coord.y, min_y = max_y;
    
    
    for (i = 1; i < x->network_graph.num_vertices; i++) {
        t_pt this_coord = x->network_graph.vertices[i].r_it.coord;
        if (this_coord.x > max_x)
            max_x = this_coord.x;
        if (this_coord.y > max_y)
            max_y = this_coord.y;
        if (this_coord.x < min_x)
            min_x = this_coord.x;
        if (this_coord.y < min_y)
            min_y = this_coord.y;
    }
    
    if (max_x == min_x) {
        max_x -= 0.5;
        min_x += 0.5;
    }
    if (max_y == min_y) {
        max_y -= 0.5;
        min_y += 0.5;
    }

    max_x += x->network_machine_size/2.;
    max_y += x->network_machine_size/2.;
    min_x -= x->network_machine_size/2.;
    min_y -= x->network_machine_size/2.;

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


void machines_autozoom(t_machines *x)
{
    machines_autozoom_do(x, jpatcher_get_firstview((t_object *)gensym("#P")->s_thing));
}


	
//////////////////////// global class pointer variable
t_class *machines_class;

int C74_EXPORT main(void)
{	
	t_class *c;
	
	common_symbols_init();
	llllobj_common_symbols_init();
	
	srand(time(NULL)); // needed for the shake function

	if (llllobj_check_version(BACH_LLLL_VERSION) || llllobj_test()) {
		error("bach: bad installation");
		return 1;
	}


	CLASS_NEW_CHECK_SIZE(c, "dada.machines", (method)machines_new, (method)machines_free, (long)sizeof(t_machines), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, 0);	// include textfield and Fonts attributes
	//	jbox_initclass(c, 0);
	
	// paint & utilities
	class_addmethod(c, (method) machines_paint,			"paint", A_CANT, 0);
	class_addmethod(c, (method) machines_assist,			"assist",		A_CANT, 0);  
	class_addmethod(c, (method)	machines_notify,			"bachnotify",		A_CANT,		0);

	// save & preset
    class_addmethod(c, (method) machines_preset, "preset", 0);
    class_addmethod(c, (method) machines_begin_preset, "begin_preset", A_GIMME, 0);
    class_addmethod(c, (method) machines_restore_preset, "restore_preset", A_GIMME, 0);
    class_addmethod(c, (method) machines_end_preset, "end_preset", 0);
	CLASS_METHOD_ATTR_PARSE(c, "begin_preset", "undocumented", gensym("long"), 0L, "1");
	CLASS_METHOD_ATTR_PARSE(c, "restore_preset", "undocumented", gensym("long"), 0L, "1");
	CLASS_METHOD_ATTR_PARSE(c, "end_preset", "undocumented", gensym("long"), 0L, "1");
	class_addmethod(c, (method) machines_jsave, "jsave", A_CANT, 0);
	
	// interface
	class_addmethod(c, (method) machines_focusgained, "focusgained", A_CANT, 0);
	class_addmethod(c, (method) machines_focuslost, "focuslost", A_CANT, 0);
    
    // @method (mouse) @digest Edit content
    // @description
    // @copy DADA_DOC_MOUSE_COMMANDS_STANDARD_NAVIGATION
    // Specific commands: <br />
    // • <m>click+drag</m>: move room elements or balls<br />
    //    ↪ Add the <m>Alt</m> key to duplicate them<br />
    // • <m>Cmd+click</m> (mac) or <m>Ctrl+click</m> (win) on an element or ball to delete it<br />

	class_addmethod(c, (method) machines_mousedown, "mousedown", A_CANT, 0);
	class_addmethod(c, (method) machines_mousedrag, "mousedrag", A_CANT, 0);
	class_addmethod(c, (method) machines_mouseup, "mouseup", A_CANT, 0);
    
    // @method (keyboard) @digest Edit content
    // @description
    // @copy DADA_DOC_KEYBOARDS_COMMANDS_STANDARD_NAVIGATION
    // • <m>Cmd+Z</m> (mac) or <m>Ctrl+Z</m> (win): Perform undo step<br />
    // • <m>Cmd+Shift+Z</m> (mac) or <m>Ctrl+Y</m> (win): Perform redo step<br />
    // • <m>Cmd+A</m> (mac) or <m>Ctrl+A</m> (win): Select all<br />
    // • <m>Cmd+A</m> (mac) or <m>Ctrl+A</m> (win): Select all<br />
    // • <m>→</m>, <m>←</m>, <m>↑</m>, <m>↓</m>: Move selected machines <br />
    //    ↪ Add the <m>Shift</m> key (mac) to move more rapidly. <br />
    // • <m>Backspace</m>: Delete selected machines<br />
    // • <m>Tab</m>: Automatically set domain and range<br />
  	class_addmethod(c, (method) machines_key, "key", A_CANT, 0);
  	class_addmethod(c, (method) machines_keyup, "keyup", A_CANT, 0);

    
    // @method (tools) @digest Navigate or edit content
    // @description
    // @copy DADA_DOC_TOOLS_INTRO
    // @copy DADA_DOC_TOOLS_ZX
    // @copy DADA_DOC_TOOLS_A
	class_addmethod(c, (method) machines_mousemove, "mousemove", A_CANT, 0);
	class_addmethod(c, (method) machines_mouseenter, "mouseenter", A_CANT, 0);
	class_addmethod(c, (method) machines_mouseleave, "mouseleave", A_CANT, 0);
	class_addmethod(c, (method) machines_mousewheel, "mousewheel", A_CANT, 0);
	
	class_addmethod(c, (method) machines_bang,			"bang",			0);

	// @method roll @digest Process <o>bach.roll</o>'s gathered syntax
	// @description Any <m>llll</m> starting with a <m>roll</m> symbol will be considered as the <o>bach.roll</o>'s gathered syntax to be processed, and the
	// result is output from the first outlet.
    // @marg 0 @name roll_gathered_syntax @optional 0 @type llll
	class_addmethod(c, (method)machines_anything,	"roll",			A_GIMME,	0);

    // @method llll @digest Set object state
    // @description Any <m>llll</m> not starting with a <m>roll</m> symbol will be considered the llll syntax setting the state of the object.
    // See the <m>dump</m> message to know more about the state syntax.
    class_addmethod(c, (method)machines_anything,	"anything",			A_GIMME,	0);
    class_addmethod(c, (method)machines_anything,	"setstoredstate",	A_GIMME, 0);
    
    
    // @method dump @digest Output state
    // @description Outputs the current state of the object. The syntax is
    // <b>machines (prototypes <m>PROTOTYPE1</m> <m>PROTOTYPE2</m>...) (network (vertices <m>VERTEX1</m> <m>VERTEX2</m>...) (edges <m>EDGE1</m> <m>EDGE2</m>...))</b>.
    // Each prototype is in the syntax
    // <b>((name <m>name</m>) (fullname <m>fullname</m>) (char <m>displaychars</m>) (numins <m>ins</m>) (numouts <m>outs</m>))</b>.
    // Each vertex is in the syntax
    // <b>((coord <m>x</m> <m>y</m>) (type <m>machinetype</m>) (numins <m>ins</m>) (numouts <m>outs</m>)</b>.
    // Each connection is in the syntax
    // <b>(<m>vertex1</m> <m>vertex2</m> (numin <m>in</m>) (numout <m>out</m>))</b>,
    // representing a connection from the outlet <m>out</m> of vertex of index <m>vertex1</m> (in the vertex list), to the inlet
    // <m>in</m> of the vertex of index <m>vertex2</m>. <br />
    // The <m>dump prototypes</m> message only dumps the prototypes; the <m>dump network</m> message only dumps the network. <br />
    // @marg 0 @name what @optional 1 @type symbol
    class_addmethod(c, (method)machines_anything,	"dump",			A_GIMME,	0);

    
    // @method clear @digest Clear machines
    // @description Deletes all existing machines.
    class_addmethod(c, (method)machines_anything,		"clear",		A_GIMME,	0);

    // @method domain @digest Set the X domain
    // @description The <m>domain</m> message, followed by two numbers, sets minimum and maximum coordinates
    // to be displayed on the X axis.
    // The <m>domain</m> message,  followed by the "start" or "end" symbol and a number, sets the coordinate
    // to be displayed respectively at the left boundary or at the right boundary of the object box.
    // @marg 0 @name arguments @optional 0 @type list
    class_addmethod(c, (method)machines_anything,		"domain",		A_GIMME,	0);
    
    // @method range @digest Set the Y range
    // @description The <m>range</m> message, followed by two numbers, sets minimum and maximum coordinates
    // to be displayed on the Y axis
    // The <m>range</m> message,  followed by the "start" or "end" symbol and a number, sets the coordinate
    // to be displayed respectively at the bottom boundary or at top right boundary of the object box.
    // @marg 0 @name arguments @optional 0 @type list
    class_addmethod(c, (method)machines_anything,		"range",		A_GIMME,	0);
    
    
    // @method getdomain @digest Retrieve current X domain
    // @description The <m>getdomain</m> message outputs from the third outlet the minimum and maximum
    // coordinates displayed on the X axis, preceded by a <m>domain</m> symbol.
    class_addmethod(c, (method)machines_anything,		"getdomain",		A_GIMME,	0);
    
    
    // @method getrange @digest Retrieve current Y range
    // @description The <m>getrange</m> message outputs from the third outlet the minimum and maximum
    // coordinates displayed on the Y axis, preceded by a <m>range</m> symbol.
    class_addmethod(c, (method)machines_anything,		"getrange",		A_GIMME,	0);
    
    // @method autozoom @digest Set domain and range automatically
    // @description Sets domain and range automatically depending on the displayed machines.
    class_addmethod(c, (method)machines_autozoom,		"autozoom",	0);

  
    DADAOBJ_JBOX_DECLARE_READWRITE_METHODS(c);
    DADAOBJ_JBOX_DECLARE_ACCEPTSDRAG_METHODS(c);

	llllobj_class_add_out_attr(c, LLLL_OBJ_UI);
	dadaobj_class_init(c, LLLL_OBJ_UI, DADAOBJ_BBGIMAGE | DADAOBJ_ZOOM | DADAOBJ_CENTEROFFSET | DADAOBJ_EMBED | DADAOBJ_MOUSEHOVER | DADAOBJ_GRID | DADAOBJ_LABELS | DADAOBJ_SNAPTOGRID | DADAOBJ_AXES | DADAOBJ_UNDO | DADAOBJ_SELECTION | DADAOBJ_NOTIFICATIONS | DADAOBJ_BORDER | DADAOBJ_BORDER_SHOWDEFAULT);

	
	CLASS_ATTR_DEFAULT(c, "patching_rect", 0, "0 0 300 300");
	// @exclude dada.machines
	CLASS_ATTR_DEFAULT(c, "presentation_rect", 0, "0 0 300 300");
	// @exclude dada.machines
	

	CLASS_STICKY_ATTR(c,"category",0,"Color");

	CLASS_ATTR_RGBA(c, "networkcolor", 0, t_machines, j_networkcolor);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "networkcolor", 0, "0.3 0.3 0.3 1.");
	CLASS_ATTR_STYLE_LABEL(c, "networkcolor", 0, "rgba", "Network Color");
	CLASS_ATTR_BASIC(c, "networkcolor", 0);
	// @description Color of the network

	CLASS_ATTR_RGBA(c, "machinecolor", 0, t_machines, j_machinecolor);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "machinecolor", 0, "0.2 0.2 0.2 1.");
	CLASS_ATTR_STYLE_LABEL(c, "machinecolor", 0, "rgba", "Machine Color");
	// @description Color of the machines
	
    CLASS_ATTR_RGBA(c, "selectioncolor", 0, t_machines, j_selectioncolor);
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "selectioncolor", 0, "0.8 0. 0.8 1.");
    CLASS_ATTR_STYLE_LABEL(c, "selectioncolor", 0, "rgba", "Selection Color");
    // @description Color of the selection

	CLASS_STICKY_ATTR_CLEAR(c, "category");

	

	
	CLASS_STICKY_ATTR(c,"category",0,"Settings");

/*	CLASS_ATTR_LONG(c,"machineout",0, t_machines, num_machine_out);
	CLASS_ATTR_STYLE_LABEL(c,"machineout",0,"text","Number of Machines Outlets");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"machineout", 0, "1");
*/
	CLASS_ATTR_DOUBLE(c,"transp",0, t_machines, transp);
	CLASS_ATTR_STYLE_LABEL(c,"transp",0,"text","Amount of Transposition in Cents");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"transp", 0, "100");
	// @description Amount of a transposition step for a transposition machine, in cents.

	CLASS_ATTR_DOUBLE(c,"shift",0, t_machines, shift);
	CLASS_ATTR_STYLE_LABEL(c,"shift",0,"text","Amount of Time Shift in Milliseconds");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"shift", 0, "100");
	// @description Amount of a time shift step for a shift machine, in milliseconds.
    
    CLASS_ATTR_DOUBLE(c,"stretch",0, t_machines, stretch);
    CLASS_ATTR_STYLE_LABEL(c,"stretch",0,"text","Stretch Factor");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"stretch", 0, "2");
    // @description Stretch factor for a stretch or compress machine.
	
	CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	CLASS_STICKY_ATTR(c,"category",0,"Appearance");
	
	CLASS_ATTR_CHAR(c, "shownetwork", 0, t_machines, show_network);
    CLASS_ATTR_STYLE_LABEL(c, "shownetwork", 0, "onoff", "Show Network");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"shownetwork",0,"1");

	CLASS_ATTR_CHAR(c, "showmachines", 0, t_machines, show_machines);
    CLASS_ATTR_STYLE_LABEL(c, "showmachines", 0, "onoff", "Show Machines");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showmachines",0,"1");
	
	CLASS_ATTR_DOUBLE(c, "machinesize", 0, t_machines, network_machine_size);
    CLASS_ATTR_STYLE_LABEL(c, "machinesize", 0, "text", "Network Machine Size");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"machinesize",0,"20.");

	CLASS_ATTR_DOUBLE(c, "edgewidth", 0, t_machines, network_edge_linewidth);
    CLASS_ATTR_STYLE_LABEL(c, "edgewidth", 0, "text", "Network Edge Line Width");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"edgewidth",0,"1.5");
	
	CLASS_ATTR_CHAR(c, "linestyle", 0, t_machines, line_style);
    CLASS_ATTR_STYLE_LABEL(c, "linestyle", 0, "enumindex", "Line Style");
	CLASS_ATTR_ENUMINDEX(c,"linestyle", 0, "Straight Segmented Curve"); 
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"linestyle",0,"0");
	CLASS_ATTR_ACCESSORS(c, "linestyle", (method)NULL, (method)machines_setattr_linestyle);

	CLASS_STICKY_ATTR_CLEAR(c, "category");

		
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	machines_class = c;

	dev_post("dada.machines compiled %s %s", __DATE__, __TIME__);
	return 0;
}

t_max_err machines_setattr_linestyle(t_machines *x, t_object *attr, long ac, t_atom *av)
{
	if (ac && av && is_atom_number(av)) {
		x->line_style = atom_getlong(av);
		graph_change_line_style(&x->network_graph, (e_dada_line_style)x->line_style);
		jbox_invalidate_layer((t_object *)x, NULL, gensym("network"));
		jbox_redraw((t_jbox *)x);
	}
	return MAX_ERR_NONE;
}


t_max_err machines_notify(t_machines *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	if (msg == _sym_attr_modified) {
		t_symbol *attr_name = (t_symbol *)object_method((t_object *)data, _sym_getname);
		if (attr_name == _llllobj_sym_zoom || attr_name == gensym("center")) {
			jbox_invalidate_layer((t_object *)x, NULL, gensym("network"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
			jbox_redraw((t_jbox *)x);
		} else if (attr_name == gensym("grid")) {
			jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
			jbox_redraw((t_jbox *)x);
		}
	}
	
	return MAX_ERR_NONE;
}


void machines_begin_preset(t_machines *x, t_symbol *s, long argc, t_atom *argv)
{
	dadaobj_begin_preset(dadaobj_cast(x), s, argc, argv);
}


void machines_restore_preset(t_machines *x, t_symbol *s, long argc, t_atom *argv)
{
	dadaobj_restore_preset(dadaobj_cast(x), s, argc, argv);
}

void machines_end_preset(t_machines *x)
{
	dadaobj_end_preset(dadaobj_cast(x));
}

void machines_preset(t_machines *x) 
{
	dadaobj_preset(dadaobj_cast(x));
}


void machines_jsave(t_machines *x, t_dictionary *d)
{
	if (x->b_ob.d_ob.save_data_with_patcher){
		if (x->b_ob.r_ob.l_dictll) {
			llll_store_in_dictionary(x->b_ob.r_ob.l_dictll, d, "machines_data", NULL);
		} else {
			t_llll *data = machines_get_state(x);
//            llll_check(data);
			llll_store_in_dictionary(data, d, "machines_data", NULL);
			llll_free(data);
		}
	} 
}		


t_llll *machines_get_network(t_machines *x)
{
	t_llll *out_ll = llll_get();
	llll_appendsym(out_ll, gensym("network"), 0, WHITENULL_llll);
    llll_chain(out_ll, graph_to_llll(&x->network_graph));
	return out_ll;
}



t_llll *machines_get_state_sel(t_machines *x, char get_prototypes, char get_network)
{
	// How do we save the information?
	// A sublist: 1) network graph
	// 1) in the form: ("network" ("vert" NODE1 NODE2 NODE3...) ("adj" ADJ1 ADJ2 ADJ3...)) 
	//		with NODE equal to the vertex coordinates: (x y), and ADJ equal to an adjacency list, 
	//		namely ADJ_j (v1 v2 v3 v4...) where v_i are the vertices adjacent to the j-th node.
	
	t_llll *data = llll_get();
	
    llll_appendsym(data, gensym("machines"));
    if (get_prototypes)
        llll_appendllll(data, get_prototypes_as_llll(x), 0, WHITENULL_llll);

    if (get_network)
		llll_appendllll(data, machines_get_network(x), 0, WHITENULL_llll);
	
	return data;
}

t_llll *machines_get_state(t_machines *x)
{
	return machines_get_state_sel(x, true, true);
}


void machines_set_network(t_machines *x, t_llll *network)
{
    if (network && network->l_head)
        graph_from_llll(network, &x->network_graph, x->network_machine_size, x->network_machine_size);
}



// see machines_get_state about the codification of info
void machines_set_state(t_machines *x, t_llll *state)
{
    
    t_llllelem *elem = state->l_head;
    
    x->itsme = true;
    if (elem && hatom_gettype(&elem->l_hatom) == H_SYM && hatom_getsym(&elem->l_hatom) == gensym("machines"))
        elem = elem->l_next;
    
    while (elem && hatom_gettype(&elem->l_hatom) == H_LLLL && hatom_getllll(&elem->l_hatom)->l_head &&
           hatom_gettype(&hatom_getllll(&elem->l_hatom)->l_head->l_hatom) == H_SYM){
        
        if (hatom_getsym(&hatom_getllll(&elem->l_hatom)->l_head->l_hatom) == gensym("network")) {
            machines_set_network(x, hatom_getllll(&elem->l_hatom));
        }  else if (hatom_getsym(&hatom_getllll(&elem->l_hatom)->l_head->l_hatom) == gensym("prototypes")) {
            set_prototypes_from_llll(x, hatom_getllll(&elem->l_hatom), false);
        }
        
        elem = elem->l_next;
    }
    x->itsme = false;

	postprocess_network(x);
}



void machines_assist(t_machines *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { 
		if (a < x->num_machine_in)  // @in 0 @loop 1 @type anything @digest Network inlet
			sprintf(s, "Network Inlet %ld", a+1);
        else  // @in -1 @type llll @digest Lambda inlet
            sprintf(s, "Lambda Inlet"); // @description Lambda inlet receiving the result of the implemented custom operations
	} else {
		char *type = NULL;
		llllobj_get_llll_outlet_type_as_string((t_object *) x, LLLL_OBJ_UI, a, &type);
		if (a < x->num_machine_out)	// @out 0 @loop 1 @type llll @digest Network outlet
			sprintf(s, "llll (%s): Network Outlet %ld", type, a+1); 			
        else if (a == x->num_machine_out)	// @out -3 @type llll @digest Queries and notifications
            sprintf(s, "llll (%s): Queries and Notifications", type);
		else if (a == x->num_machine_out + 1)	// @out -2 @type llll @digest Lambda outlet
			sprintf(s, "llll (%s): Lambda Outlet", type); 			
		else 	// @out -1 @type bang @digest bang when object is changed via the interface
			sprintf(s, "bang when Changed");
	}
}

void machines_free(t_machines *x)
{
	// free vertex metadata
	long i, j;
	for (i = 0; i < x->network_graph.num_vertices; i++) {
		for (j = 0; j < DADA_GRAPH_MAX_VANILLABOX_INS; j++)
			llll_free(x->network_graph.vertices[i].data.m_vanillabox.ins[j]);
//		for (j = 0; j < DADA_GRAPH_MAX_VANILLABOX_OUTS; j++)
//			llll_free(x->network_graph.vertices[i].data.m_vanillabox.outs[j]);
	}
	
	graph_free(&x->network_graph);
	object_free_debug(x->n_proxy1);
	dadaobj_jbox_free((t_dadaobj_jbox *)x); // jbox_free and llllobj_free are inside here
}

void machines_iar(t_machines *x)
{
    jbox_invalidate_layer((t_object *)x, NULL, gensym("network"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
    jbox_redraw((t_jbox *)x);
}




void *machines_new(t_symbol *s, long argc, t_atom *argv)
{
	t_machines *x = NULL;
	t_dictionary *d = NULL;
	long boxflags;
	t_llll *llll_for_rebuild = NULL;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;    
	
	if ((x = (t_machines *)object_alloc_debug(machines_class))) {
		
		x->creating_new_obj = true;
		
        x->num_prototypes = 0;
        x->prototype = (t_machine_prototype *)bach_newptr(DADA_MACHINES_MAX_NUM_PROTOTYPES * sizeof(t_machine_prototype));
        
		x->b_ob.d_ob.m_tools.curr_tool = DADA_TOOL_ARROW;
		x->firsttime = true;
		x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
		
		x->num_machine_out = x->num_machine_in = 1;
		
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
				| JBOX_DRAWBACKGROUND
		//      | JBOX_NOFLOATINSPECTOR
		//      | JBOX_MOUSEDRAGDELTA
		//      | JBOX_TEXTFIELD
		;
		
		jbox_new((t_jbox *)x, boxflags, argc, argv);
		x->b_ob.r_ob.l_box.b_firstin = (t_object *)x;
		x->n_proxy1 = proxy_new((t_object *) x, 1, &x->n_in);

        load_default_machines(x);
        
		dadaobj_jbox_setup((t_dadaobj_jbox *)x, DADAOBJ_BBGIMAGE | DADAOBJ_ZOOM | DADAOBJ_CENTEROFFSET | DADAOBJ_UNDO | DADAOBJ_CHANGEDBANG | DADAOBJ_SELECTION | DADAOBJ_NOTIFICATIONS, build_pt(1., 1.), 1, 3, 1, (invalidate_and_redraw_fn)machines_iar, "la", 2, "b444");
		dadaobj_addfunctions(dadaobj_cast(x), (dada_mousemove_fn)machines_mousemove, NULL, (method)machines_postprocess_undo, (get_state_fn)machines_get_state, (set_state_fn)machines_set_state, NULL, NULL, NULL);

        x->b_ob.d_ob.m_interface.selection_tolerance = DADA_MACHINES_VERTEX_SELECTION_PAD;
        
        dadaobj_dadaitem_class_alloc(dadaobj_cast(x), DADAITEM_TYPE_VERTEX, gensym("vertex"), gensym("Vertex"), DADA_ITEM_ALLOC_ARRAY_DONT, 0, false, sizeof(t_dada_graph_vertex), calcoffset(t_machines, network_graph) + calcoffset(t_dada_graph, vertices), 0, &x->network_graph.num_vertices, DADA_FUNC_NONE, NULL, NULL, DADA_FUNC_NONE, NULL, NULL, (method)postprocess_network, NULL, NULL, true, false);

        
        graph_new(&x->network_graph, DADA_GRAPH_FLAG_NONE, DADA_GRAPH_METADATA_VANILLABOX, DADA_GRAPH_METADATA_OUTINNUM, DADA_LINE_STRAIGHT);
		
        t_shape shape = ezbuild_dadapolygon(DADA_BLACK, 1, 4, -100., -100., 100., -100., 100., 100., -100., 100.);
		graph_import_dadapolygon(&x->network_graph, &shape.shape.polygon, build_vanillabox_metadata(gensym("transposeup"), 1, 1),
							 build_outinnum_metadata(0, 0), false);
		graph_delete_edge(&x->network_graph, x->network_graph.num_edges - 1);
		graph_reverse_edge(&x->network_graph, graph_vertices_to_edge(&x->network_graph, 0, 1));
		graph_reverse_edge(&x->network_graph, graph_vertices_to_edge(&x->network_graph, 1, 2));
		graph_reverse_edge(&x->network_graph, graph_vertices_to_edge(&x->network_graph, 2, 3));
		x->network_graph.vertices[0].data.m_vanillabox.type = gensym("outlet");
		x->network_graph.vertices[x->network_graph.num_vertices - 1].data.m_vanillabox.type = gensym("inlet");
		
		attr_dictionary_process(x,d);
		
		if ((llll_for_rebuild = llll_retrieve_from_dictionary(d, "machines_data"))) { // new method
			llllobj_manage_dict_llll((t_object *)x, LLLL_OBJ_UI, llll_for_rebuild);
			machines_set_state(x, llll_for_rebuild);
			llll_free(llll_for_rebuild);
		}
		
		jbox_ready((t_jbox *)x);
		
		x->creating_new_obj = false;
	}
	return x;
}

void machines_int(t_machines *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	machines_anything(x, _sym_list, 1, argv);
}

void machines_float(t_machines *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	machines_anything(x, _sym_list, 1, argv);
}


void machines_dump(t_machines *x, char get_prototypes, char get_network)
{	
	t_llll *ll = machines_get_state_sel(x, get_prototypes, get_network);
	llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 0, ll);
	llll_free(ll);
 }

void machines_bang(t_machines *x)
{	
	machines_anything(x, _sym_bang, 0, NULL);
}

void llll_to_distrib(t_machines *x, t_llll *ll, t_machines_distrib *distrib)
{
	distrib->num_types = ll->l_size;
	distrib->w_type = (t_machines_weighted_type *)bach_newptr(distrib->num_types * sizeof(t_machines_weighted_type));

	t_llllelem *elem;
	long i = 0;
	for (elem = ll->l_head; elem && i < distrib->num_types; elem = elem->l_next) {
		if (hatom_gettype(&elem->l_hatom) == H_SYM) {
			distrib->w_type[i].type = label_to_machine(x, hatom_getsym(&elem->l_hatom));
			distrib->w_type[i].relative_weight = 1.;
			i++;
		} else if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
			t_llll *subll = hatom_getllll(&elem->l_hatom);
			if (subll->l_depth == 1 && subll->l_head && hatom_gettype(&subll->l_head->l_hatom) == H_SYM) {
				distrib->w_type[i].type = label_to_machine(x, hatom_getsym(&subll->l_head->l_hatom));
				distrib->w_type[i].relative_weight = subll->l_head->l_next && is_hatom_number(&subll->l_head->l_next->l_hatom) ? hatom_getdouble(&subll->l_head->l_next->l_hatom) : 1.;
				i++;
			}
		}
	}
	distrib->num_types = i;
}

void distrib_init_default(t_machines *x, t_machines_distrib *distrib)
{
	long i;
	distrib->num_types = x->num_prototypes - 3;
	distrib->w_type = (t_machines_weighted_type *)bach_newptr(distrib->num_types * sizeof(t_machines_weighted_type));
	for (i = 0; i < distrib->num_types; i++)  {
		distrib->w_type[i].relative_weight = 1;
		distrib->w_type[i].type = i + 3; // excluding idle, inlet and outlet
	}
}

void machines_anything(t_machines *x, t_symbol *msg, long ac, t_atom *av)
{
    long inlet = proxy_getinlet((t_object *) x);

    dadaobj_anything(dadaobj_cast(x), msg, ac, av);

    if (inlet == 0) {
        t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, msg, ac, av, LLLL_PARSE_CLONE);
        char must_free = true;
        
        if (parsed && parsed->l_head) {
            char data = 0;
            if (hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
                t_symbol *router = hatom_getsym(&parsed->l_head->l_hatom);
                llll_behead(parsed);
                
                if (dadaobj_anything_handle_domain_or_range(dadaobj_cast(x), router, parsed)) {
                    // nothing to do!
                } else if (router == gensym("setstoredstate") || router == gensym("machines")) {
                    machines_set_state(x, parsed);
                } else if (router == _sym_dump) {
                    machines_dump(x, parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("prototypes")), parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("network")));
                } else if (router == _llllobj_sym_roll) {
                    data = 1;
                } else if (router == gensym("data")) {
                    data = 2;
                } else if (router == gensym("clear")) {
                    machines_undo_step_push_network(x, gensym("Clear"));
                    graph_clear(&x->network_graph);
                    postprocess_network(x);
                } else if (router == gensym("random")) {
                    long num_machines = 100;
                    t_machines_distrib distrib;
                    distrib.num_types = 0;
                    if (parsed->l_head && is_hatom_number(&parsed->l_head->l_hatom)) {
                        num_machines = hatom_getlong(&parsed->l_head->l_hatom);
                        llll_behead(parsed);
                    }
                    if (parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom))
                        llll_to_distrib(x, hatom_getllll(&parsed->l_head->l_hatom), &distrib);
                    else
                        distrib_init_default(x, &distrib);
                    build_random_network(x, build_pt(0, 0), 30, 60, num_machines, distrib);
                    machines_autozoom(x);
                    bach_freeptr(distrib.w_type);
                }
            } else {
                machines_set_state(x, parsed);
            }
            
            if (data > 0) {
                x->nonroll_data = false;
                if (msg != _sym_bang) {
                    llllobj_store_llll((t_object *)x, LLLL_OBJ_UI, parsed, 0);
                    must_free = false;
                }
                
                t_llll *ll = llllobj_get_store_contents((t_object *)x, LLLL_OBJ_UI, 0, true);
                if (data == 1)
                    llll_free(dada_sliceheader(ll));
                else
                    x->nonroll_data = true;
                machines_network_process(x, ll);
            }
        }
        if (must_free)
            llll_free(parsed);
   
    } else if (inlet == x->num_machine_in) { // lambda inlet
        llllobj_parse_and_store((t_object *)x, LLLL_OBJ_UI, msg, ac, av, inlet);
    }
}



/// *************************************
/// REAL GRAPH PROCESSING FUNCTION

void machine_process_once(t_machines *x, long vertex_idx, t_llll **out)
{
    t_vanillabox *vb = &x->network_graph.vertices[vertex_idx].data.m_vanillabox;
    long type = label_to_machine(x, vb->type);
    long i;
    
    if (type >= 0 && type < x->num_prototypes && x->prototype[type].fun)
        (x->prototype[type].fun)(x, vb->num_ins, vb->ins, vb->num_outs, out);
    else if (type >= x->num_standard_prototypes) {
        // lambda processing
        
        // Storing a null default answer
        llllobj_store_llll((t_object *)x, LLLL_OBJ_UI, llll_get(), x->num_machine_in);
        
        // Outputting candidate from lambda loop, in the form
        // symbol (input1)(input2)...
        t_llll *ll_lambda = llll_get();
        llll_appendsym(ll_lambda, x->prototype[type].name);
        for (i = 0; i < vb->num_ins; i++)
            llll_appendllll(ll_lambda, vb->ins[i] ? vb->ins[i] : llll_get());
        
        llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, x->num_machine_out + 1, ll_lambda);
        
        // we expect the answer to be in the form
        // (output1)(output2)...
        t_llll *answer1 = llllobj_get_store_contents((t_object *) x, LLLL_OBJ_UI, x->num_machine_in, true);
        t_llllelem *elem;
        for (i = 0, elem = answer1->l_head; i < vb->num_outs; elem = elem ? elem->l_next : NULL, i++) {
            if (elem && hatom_gettype(&elem->l_hatom) == H_LLLL)
                out[i] = llll_clone(hatom_getllll(&elem->l_hatom));
            else {
                out[i] = llll_get();
            }
        }
        
        llll_free(answer1);
        llll_free(ll_lambda);
    }

    for (i = 0; i < vb->num_ins; i++)
        vb->ins[i] = NULL;
}


long sort_edges_righttoleft_fn(void *data, t_llllelem *a, t_llllelem *b)
{	
	t_machines *x = (t_machines *)data;
	long l_a = hatom_getlong(&a->l_hatom);
	long l_b = hatom_getlong(&b->l_hatom);
	long outnum_a = x->network_graph.edges[l_a].data.m_outinnum.num_out;
	long outnum_b = x->network_graph.edges[l_b].data.m_outinnum.num_out;
	long end_a = x->network_graph.edges[l_a].end;
	long end_b = x->network_graph.edges[l_b].end;
	
	if (outnum_a == outnum_b) {
		if (end_a == end_b) {
			return (x->network_graph.edges[l_a].data.m_outinnum.num_in >= x->network_graph.edges[l_b].data.m_outinnum.num_in);
  		} else if (x->network_graph.vertices[end_a].r_it.coord.x >= x->network_graph.vertices[end_b].r_it.coord.x)
			return 1;
		return 0;
	} else 
		return (outnum_a >= outnum_b);
}


// use inlet_num < 0 and ll = NULL for generators
void machines_network_process_node(t_machines *x, long vertex_idx, long inlet_num, t_llll *ll, e_machine_process flags)
{
	t_dada_graph *graph = &x->network_graph;
	if (inlet_num < 0 || inlet_num < graph->vertices[vertex_idx].data.m_vanillabox.num_ins) {
		if (inlet_num >= 0) {
			llll_free(graph->vertices[vertex_idx].data.m_vanillabox.ins[inlet_num]);
			graph->vertices[vertex_idx].data.m_vanillabox.ins[inlet_num] = ll;
		}
		
		if (inlet_num <= 0) { // trigger process
			long i;
			t_llll *out[DADA_GRAPH_MAX_VANILLABOX_OUTS];

			machine_process_once(x, vertex_idx, out);
			
			long num_outs = graph->vertices[vertex_idx].data.m_vanillabox.num_outs;
			
			// retrieve edges going out
			t_llll *adj_list = graph_vertex_get_outgoing_edges_list(graph, vertex_idx);
			t_llllelem *edge_el;
			llll_mergesort_inplace(&adj_list, sort_edges_righttoleft_fn, x);
			
			for (edge_el = adj_list->l_head; edge_el; edge_el = edge_el->l_next) {
				long edge = hatom_getlong(&edge_el->l_hatom);
				t_outinnum *ion = &graph->edges[edge].data.m_outinnum;
				if (flags == DADA_MACHINES_PROCESS_ALL ||
					((flags == DADA_MACHINES_PROCESS_COLD) && (ion->num_in > 0)) ||
					((flags == DADA_MACHINES_PROCESS_HOT) && (ion->num_in == 0))) {
					if (graph->vertices[graph->edges[edge].end].data.m_vanillabox.type == machine_to_name(x, x->outlet_prototype_id)) {
						// spit out!
                        if (out[ion->num_out]) {
                            t_llll *clone_out = llll_clone_extended(out[ion->num_out], WHITENULL_llll, 0, copy_lthing_fn);
                            if (!x->nonroll_data) {
                                remove_all_marking_to_llll_lthings(clone_out, k_NOTATION_OBJECT_ROLL);
                                dada_roll_prepend_roll_sym(clone_out);
                            }
                            llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 0, clone_out);
                            llll_free(clone_out);
                        }
					} else if (ion->num_out <= num_outs) {
                        if (out[ion->num_out])
                            machines_network_process_node(x, graph->edges[edge].end, ion->num_in, llll_clone_extended(out[ion->num_out], WHITENULL_llll, 0, copy_lthing_fn), DADA_MACHINES_PROCESS_ALL);
					}
				}
			}
			
			for (i = 0; i < num_outs; i++) 
				llll_free(out[i]);
		}
	}
}

void machines_network_process(t_machines *x, t_llll *ll)
{
	// Find inlet nodes
	long i;
	ll->l_thing.w_double = x->length_for_generated_note = get_max_rhythm_length(ll);
	
	// 1. Processing generators (i.e. machines with no inlets) shooting in cold inlets 
	for (i = 0; i < x->network_graph.num_vertices; i++) {
		if (machine_to_num_ins(x, label_to_machine(x, x->network_graph.vertices[i].data.m_vanillabox.type)) == 0)
			machines_network_process_node(x, i, -1, NULL, DADA_MACHINES_PROCESS_COLD);
	}

	// 2. Processing generators (i.e. machines with no inlets) shooting in hot inlets 
	for (i = 0; i < x->network_graph.num_vertices; i++) {
		if (machine_to_num_ins(x, label_to_machine(x, x->network_graph.vertices[i].data.m_vanillabox.type)) == 0)
			machines_network_process_node(x, i, -1, NULL, DADA_MACHINES_PROCESS_HOT);
	}
	
	// 3. Processing Inlets
	for (i = 0; i < x->network_graph.num_vertices; i++) {
		if (x->network_graph.vertices[i].data.m_vanillabox.type == machine_to_name(x, x->inlet_prototype_id))
			machines_network_process_node(x, i, 0, ll, DADA_MACHINES_PROCESS_ALL);
	}
}



/// *************************************




long pixel_to_graph_vertex(t_machines *x, t_pt pt, t_object *view, t_pt *coordinates)
{
	t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), view, pt);
	if (coordinates)
		*coordinates = coord;
	return graph_coord_to_vertex(dadaobj_cast(x), &x->network_graph, coord, x->network_machine_size / x->b_ob.d_ob.m_zoom.zoom.x, DADA_MACHINES_VERTEX_SELECTION_PAD);
}

long pixel_to_graph_edge(t_machines *x, t_pt pt, t_object *view, t_pt *coordinates)
{
	t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), view, pt);
	if (coordinates)
		*coordinates = coord;
	return graph_coord_to_edge(dadaobj_cast(x), &x->network_graph, coord, x->network_edge_linewidth / x->b_ob.d_ob.m_zoom.zoom.x, DADA_MACHINES_EDGE_SELECTION_PAD);
}


long pixel_to_edge(t_machines *x, t_pt coord, t_object *view, double edge_width_in_coord, double tolerance, double zoom)
{
	long i;
    t_pt center = get_center_pix(dadaobj_cast(x), view, NULL);
	for (i = 0; i < x->network_graph.num_edges; i++) {
		t_pt start = get_inlet_outlet_pix(x, center, x->network_graph.edges[i].start, x->network_graph.edges[i].data.m_outinnum.num_out, x->outlet_prototype_id, zoom);
		t_pt end = get_inlet_outlet_pix(x, center, x->network_graph.edges[i].end, x->network_graph.edges[i].data.m_outinnum.num_in, x->inlet_prototype_id, zoom);
		switch (x->network_graph.line_style) {
			case DADA_LINE_SEGMENTED:
				if (is_pt_in_segmented_line_shape(coord.x, coord.y, start.x, start.y, end.x, end.y, edge_width_in_coord + 2 * tolerance))
					return i;
				break;
			default:
				if (is_pt_in_line_shape_improved(coord.x, coord.y, start.x, start.y, end.x, end.y, edge_width_in_coord + 2 * tolerance))
					return i;
				break;
		}
	}
	return -1;
}


long pixel_to_inlet_or_outlet(t_machines *x, t_pt pt, t_object *view, t_pt *coordinates, long *type, long *secondary_idx, double zoom)
{
	t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), view, pt);
	t_pt center = get_center_pix(dadaobj_cast(x), view, NULL);
	if (coordinates)
		*coordinates = coord;
	long i, j;
	for (i = 0; i < x->network_graph.num_vertices; i++) {
		long num_ins = x->network_graph.vertices[i].data.m_vanillabox.num_ins;
		long num_outs = x->network_graph.vertices[i].data.m_vanillabox.num_outs;
		for (j = 0; j < num_ins; j++) {
			t_pt pix = node_pix_to_inlet_outlet_pix(x, center, coord_to_pix(dadaobj_cast(x), center, x->network_graph.vertices[i].r_it.coord), j, num_ins, x->inlet_prototype_id, zoom);
			t_rect rect = build_rect(pix.x - DADA_MACHINES_INLET_WIDTH/2., pix.y - DADA_MACHINES_INLET_HEIGHT/2., DADA_MACHINES_INLET_WIDTH, DADA_MACHINES_INLET_HEIGHT);
			if (is_pt_in_rectangle_tolerance(pt, rect, DADA_MACHINES_INLET_OUTLET_SELECTION_PAD)) {
				*secondary_idx = j;
				*type = DADAITEM_TYPE_MACHINE_INLET;
				return i;
			}
		}
		for (j = 0; j < num_outs; j++) {
			t_pt pix = node_pix_to_inlet_outlet_pix(x, center, coord_to_pix(dadaobj_cast(x), center, x->network_graph.vertices[i].r_it.coord), j, num_outs, x->outlet_prototype_id, zoom);
			t_rect rect = build_rect(pix.x - DADA_MACHINES_INLET_WIDTH/2., pix.y - DADA_MACHINES_INLET_HEIGHT/2., DADA_MACHINES_INLET_WIDTH, DADA_MACHINES_INLET_HEIGHT);
			if (is_pt_in_rectangle_tolerance(pt, rect, DADA_MACHINES_INLET_OUTLET_SELECTION_PAD)) {
				*secondary_idx = j;
				*type = DADAITEM_TYPE_MACHINE_OUTLET;
				return i;
			}
		}
	}
	return -1;
}

t_dadaitem_identifier pixel_to_element(t_machines *x, t_pt pt, t_object *view, t_pt *coordinates)
{
	t_dadaitem_identifier result;
	long idx = -1;
    double zoom = x->b_ob.d_ob.m_zoom.zoom.x;
	result.type = DADAITEM_TYPE_NONE;
	result.flag = 0;
    result.idx = result.secondary_idx = result.tertiary_idx = -1;
	
	if ((idx = pixel_to_inlet_or_outlet(x, pt, view, coordinates, &result.type, &result.secondary_idx, zoom)) >= 0) {
		result.idx = idx;
	} else if ((idx = pixel_to_graph_vertex(x, pt, view, coordinates)) >= 0) {
		result.type = DADAITEM_TYPE_VERTEX;
		result.idx = idx;
	} else if ((idx = pixel_to_edge(x, pt, view, x->network_edge_linewidth, DADA_MACHINES_EDGE_SELECTION_PAD, zoom)) >= 0) {
		result.type = DADAITEM_TYPE_EDGE;
		result.idx = idx;
	}

	return result;
}



//// GRAPHIC DRAWING



void paint_hovered_elements1(t_machines *x, t_jgraphics *g, t_object *view, t_rect rect, t_pt center)
{
    double zoom = x->b_ob.d_ob.m_zoom.zoom.x;
	if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_MACHINE_INLET || x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_MACHINE_OUTLET) {
		t_pt pt2 = get_inlet_outlet_pix(x, center, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, x->b_ob.d_ob.m_interface.mousedown_item_identifier.secondary_idx, x->b_ob.d_ob.m_interface.mousedown_item_identifier.type, zoom);
		paint_circle(g, change_alpha(x->j_machinecolor, 0.3), DADA_TRANSPARENT, pt2.x, pt2.y, DADA_MACHINES_INLET_WIDTH + DADA_MACHINES_INLET_OUTLET_SELECTION_PAD, 2);
		paint_line(g, x->j_networkcolor, pt2.x, pt2.y, x->b_ob.d_ob.m_interface.mousedrag_pix.x, x->b_ob.d_ob.m_interface.mousedrag_pix.y, 1);
	}
	
	long i = x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx;
	switch (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type) {
		case DADAITEM_TYPE_EDGE:
		{
			t_dada_graph_vertex *v1 = &x->network_graph.vertices[x->network_graph.edges[i].start];
			t_dada_graph_vertex *v2 = &x->network_graph.vertices[x->network_graph.edges[i].end];
			t_pt pix1 = coord_to_pix(dadaobj_cast(x), center, v1->r_it.coord);
			t_pt pix2 = coord_to_pix(dadaobj_cast(x), center, v2->r_it.coord);
			t_pt pix1_ok = node_pix_to_inlet_outlet_pix(x, center, pix1, x->network_graph.edges[i].data.m_outinnum.num_out, v1->data.m_vanillabox.num_outs, x->outlet_prototype_id, zoom);
			t_pt pix2_ok = node_pix_to_inlet_outlet_pix(x, center, pix2, x->network_graph.edges[i].data.m_outinnum.num_in, v2->data.m_vanillabox.num_ins, x->inlet_prototype_id, zoom);
			paint_line_advanced(g, change_alpha(x->j_networkcolor, 0.3), pix1_ok, pix2_ok, 
								x->network_edge_linewidth + DADA_GRAPH_EDGE_DEFAULT_SELECTION_PAD, (e_dada_line_style) x->line_style, false, DADA_GRAPH_ARROW_SIZE, NULL, NULL, DADA_GRAPH_CURVE_AMOUNT * x->b_ob.d_ob.m_zoom.zoom.x);
		}
			break;
		case DADAITEM_TYPE_VERTEX:
		{
			t_pt pix = coord_to_pix(dadaobj_cast(x), center, x->network_graph.vertices[i].r_it.coord);
			paint_rectangle(g, x->j_networkcolor, change_alpha(x->j_networkcolor, 0.3), pix.x - x->network_machine_size/2. * zoom - DADA_GRAPH_VERTEX_DEFAULT_SELECTION_PAD/2., pix.y - x->network_machine_size/2. * zoom - DADA_GRAPH_VERTEX_DEFAULT_SELECTION_PAD/2., x->network_machine_size * zoom + DADA_GRAPH_VERTEX_DEFAULT_SELECTION_PAD, x->network_machine_size * zoom + DADA_GRAPH_VERTEX_DEFAULT_SELECTION_PAD, 0);
		}
			break;
		default:
			break;
	}
}

void paint_hovered_elements2(t_machines *x, t_jgraphics *g, t_object *view, t_rect rect, t_pt center)
{
    double zoom = x->b_ob.d_ob.m_zoom.zoom.x;
	long i = x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx;
	switch (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type) {
		case DADAITEM_TYPE_MACHINE_INLET:
		case DADAITEM_TYPE_MACHINE_OUTLET:
		{
			t_pt pix = coord_to_pix(dadaobj_cast(x), center, x->network_graph.vertices[i].r_it.coord);
			long j = x->b_ob.d_ob.m_interface.mousemove_item_identifier.secondary_idx;
			t_pt inpix = node_pix_to_inlet_outlet_pix(x, center, pix, j, x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_MACHINE_INLET ? 
													  x->network_graph.vertices[i].data.m_vanillabox.num_ins : x->network_graph.vertices[i].data.m_vanillabox.num_outs, 
													  x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_MACHINE_INLET ? x->inlet_prototype_id : x->outlet_prototype_id, zoom);
			paint_circle(g, change_alpha(x->j_machinecolor, 0.3), DADA_TRANSPARENT, inpix.x, inpix.y, DADA_MACHINES_INLET_WIDTH + DADA_MACHINES_INLET_OUTLET_SELECTION_PAD, 2);
		}
			break;
		default:
			break;
	}
}


t_pt node_pix_to_inlet_outlet_pix(t_machines *x, t_pt center, t_pt pix, long num, long total, char inlet_or_outlet, double zoom)
{
	return build_pt(pix.x - zoom * x->network_machine_size/2. + zoom * (num + 1) * x->network_machine_size/(total + 1),
					pix.y + (inlet_or_outlet == x->inlet_prototype_id ? -1 : 1) * zoom * x->network_machine_size/2.);
}

t_pt node_coord_to_inlet_outlet_pix(t_machines *x, t_pt center, t_pt coord, long num, long total, char inlet_or_outlet, double zoom)
{
	t_pt pix = coord_to_pix(dadaobj_cast(x), center, coord);
	return node_pix_to_inlet_outlet_pix(x, center, pix, num, total, inlet_or_outlet, zoom);
}

t_pt get_inlet_outlet_pix(t_machines *x, t_pt center, long idx, long num, char inlet_or_outlet, double zoom)
{
	t_pt pix_v = coord_to_pix(dadaobj_cast(x), center, x->network_graph.vertices[idx].r_it.coord);
	long total = inlet_or_outlet == x->inlet_prototype_id ? x->network_graph.vertices[idx].data.m_vanillabox.num_ins : x->network_graph.vertices[idx].data.m_vanillabox.num_outs;
	return node_pix_to_inlet_outlet_pix(x, center, pix_v, num, total, inlet_or_outlet, zoom);
}


void machines_paint_graph(t_machines *x, t_object *view, t_rect rect, t_pt center, char paint_edges, char paint_machines)
{
	
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("network"), rect.width, rect.height);
	t_rect rect_00 = build_rect(0, 0, rect.width, rect.height);
	if (g) {
		long i;
		t_dada_graph *graph = &x->network_graph;
		char buf[100];
        double zoom = x->b_ob.d_ob.m_zoom.zoom.x;
        t_jfont *jf = jfont_create_debug("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_BOLD, x->network_machine_size * 0.8 * zoom);
        
        // paint lines
        if (paint_edges) {
            for (i = 0; i < graph->num_edges; i++) {
                t_dada_graph_vertex *v1 = &graph->vertices[graph->edges[i].start];
                t_dada_graph_vertex *v2 = &graph->vertices[graph->edges[i].end];
                t_pt pix1 = coord_to_pix(dadaobj_cast(x), center, v1->r_it.coord);
                t_pt pix2 = coord_to_pix(dadaobj_cast(x), center, v2->r_it.coord);
                t_pt pix1_ok = node_pix_to_inlet_outlet_pix(x, center, pix1, graph->edges[i].data.m_outinnum.num_out, v1->data.m_vanillabox.num_outs, x->outlet_prototype_id, zoom);
                t_pt pix2_ok = node_pix_to_inlet_outlet_pix(x, center, pix2, graph->edges[i].data.m_outinnum.num_in, v2->data.m_vanillabox.num_ins, x->inlet_prototype_id, zoom);
                
                if (is_pt_in_rectangle(pix1_ok, rect_00) || is_pt_in_rectangle(pix2_ok, rect_00)) {
                    paint_line_advanced(g, x->j_networkcolor, pix1_ok, pix2_ok,  x->network_edge_linewidth, graph->line_style, true, DADA_GRAPH_ARROW_SIZE * zoom, NULL, NULL, DADA_GRAPH_CURVE_AMOUNT * x->b_ob.d_ob.m_zoom.zoom.x);
                    
                    if (DADA_MACHINES_DEBUG_IDS) { // debug IDs
                        snprintf_zero(buf, 100, "{%ld}", i);
                        write_text_simple(g, jf, x->j_machinecolor, buf, 0.5*(pix1_ok.x + pix2_ok.x) + 2,
                                          0.5 * (pix1_ok.y + pix2_ok.y), 300, 300);
                        
                    }
                }
            }
        }
        if (paint_machines) {
            for (i = 0; i < x->network_graph.num_vertices; i++) {
                // paint machine
                t_pt pix = coord_to_pix(dadaobj_cast(x), center, x->network_graph.vertices[i].r_it.coord);
                long type = label_to_machine(x, x->network_graph.vertices[i].data.m_vanillabox.type);
                long selected = dadaitem_is_preselected_xor_selected(&x->network_graph.vertices[i].r_it);
                t_jrgba machine_fill_color = selected ? change_alpha(x->j_selectioncolor, 0.3) : change_alpha(DADA_WHITE, 0.9);
                
                // inlet or outlet?
                if (type == x->inlet_prototype_id) {
                    t_pt pix1 = node_pix_to_inlet_outlet_pix(x, center, pix, 0, 1, x->inlet_prototype_id, zoom);
                    paint_dashed_line(g, x->j_networkcolor, 5, 0, pix1.x, pix1.y, x->network_edge_linewidth, 3);
                } else if (type == x->outlet_prototype_id) {
                    t_pt pix1 = node_pix_to_inlet_outlet_pix(x, center, pix, 0, 1, x->outlet_prototype_id, zoom);
                    paint_dashed_line(g, x->j_networkcolor, pix1.x, pix1.y, 5, rect.height, x->network_edge_linewidth, 3);
                }
                
                if (is_pt_in_rectangle_tolerance(pix, rect_00, x->network_machine_size/2.)) {
                    t_pt upperleft_corner = build_pt(pix.x - x->network_machine_size/2. * zoom, pix.y - x->network_machine_size/2. * zoom);
                    machine_type_to_text(x, type, buf);
                    paint_square(g, selected ? &x->j_selectioncolor : &x->j_machinecolor, &machine_fill_color, pix, x->network_machine_size/2. * zoom, 0.5);
                    write_text(g, jf, x->j_machinecolor, buf, upperleft_corner.x, upperleft_corner.y,
                               x->network_machine_size * zoom, x->network_machine_size * zoom, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, true, false);
                    
                    if (DADA_MACHINES_DEBUG_IDS) { // debug IDs
                        snprintf_zero(buf, 100, "<%ld>", i);
                        write_text_simple(g, jf, x->j_machinecolor, buf, upperleft_corner.x+x->network_machine_size + 2,
                                          upperleft_corner.y, 300, 300);
                        
                    }
                    
                    // paint inlets and outlets
                    long j;
                    long num_ins = machine_to_num_ins(x, type);
                    long num_outs = machine_to_num_outs(x, type);
                    for (j = 0; j < num_ins; j++) {
                        t_pt inpix = node_pix_to_inlet_outlet_pix(x, center, pix, j, num_ins, x->inlet_prototype_id, zoom);
                        paint_rectangle_rounded(g, x->j_machinecolor, x->j_machinecolor, inpix.x - DADA_MACHINES_INLET_WIDTH /2.,
                                                inpix.y - DADA_MACHINES_INLET_HEIGHT / 2., DADA_MACHINES_INLET_WIDTH, DADA_MACHINES_INLET_HEIGHT, 0, 2, 2);
                    }
                    for (j = 0; j < num_outs; j++) {
                        t_pt inpix = node_pix_to_inlet_outlet_pix(x, center, pix, j, num_outs, x->outlet_prototype_id, zoom);
                        paint_rectangle_rounded(g, x->j_machinecolor, x->j_machinecolor, inpix.x - DADA_MACHINES_INLET_WIDTH /2.,
                                                inpix.y - DADA_MACHINES_INLET_HEIGHT / 2., DADA_MACHINES_INLET_WIDTH, DADA_MACHINES_INLET_HEIGHT, 0, 2, 2);
                    }
                }
            }
		}
		
		jfont_destroy_debug(jf);
		jbox_end_layer((t_object *)x, view, gensym("network"));
	}
	
	jbox_paint_layer((t_object *)x, view, gensym("network"), 0., 0.);	// position of the layer
}


void machines_paint(t_machines *x, t_object *view)
{
	t_rect rect;
	t_pt center = get_center_pix(dadaobj_cast(x), view, &rect);
	t_jgraphics *g = (t_jgraphics*) patcherview_get_jgraphics(view); 
	
	jgraphics_set_source_rgba(g, 0, 0, 0, 1); // alpha = 1;
	
    dadaobj_paint_background(dadaobj_cast(x), g, &rect);
    
    dadaobj_paint_grid(dadaobj_cast(x), view, rect, center);
		
	if (x->b_ob.d_ob.m_interface.allow_mouse_hover && x->b_ob.d_ob.m_tools.curr_tool != DADA_TOOL_ZOOM && x->b_ob.d_ob.m_tools.curr_tool != DADA_TOOL_MOVE_CENTER)
		paint_hovered_elements1(x, g, view, rect, center);

	jgraphics_set_source_rgba(g, 0, 0, 0, 1); // alpha = 1;
    machines_paint_graph(x, view, rect, center, x->show_network, x->show_machines);

	if (x->b_ob.d_ob.m_interface.allow_mouse_hover && x->b_ob.d_ob.m_tools.curr_tool != DADA_TOOL_ZOOM && x->b_ob.d_ob.m_tools.curr_tool != DADA_TOOL_MOVE_CENTER)
		paint_hovered_elements2(x, g, view, rect, center);

    if (x->b_ob.d_ob.m_interface.mouse_is_down && x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_SELECT) {
        t_jrgba border = change_alpha(x->j_selectioncolor, 0.5);
        t_jrgba inner = change_alpha(x->j_selectioncolor, 0.1);
        dadaobj_paint_selection_rectangle(dadaobj_cast(x), g, &border, &inner);
    }

    dadaobj_paint_border(dadaobj_cast(x), g, &rect);
}






///////// POPUP MENU FUNCTIONS

void popup_delete_edge(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_machines *x = (t_machines *)d_ob->orig_obj;
	if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_EDGE)
		delete_edge(x, d_ob->m_interface.mousedown_item_identifier.idx);
}

void popup_delete_vertex(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_machines *x = (t_machines *)d_ob->orig_obj;
	if (d_ob->m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_VERTEX) {
		long idx = d_ob->m_interface.mousedown_item_identifier.idx;
		
		delete_vertex(x, idx, label == gensym("Remove"));
	}
}

void popup_subdivide_edge(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_machines *x = (t_machines *)d_ob->orig_obj;
	if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_EDGE)
		subdivide_edge(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, hatom_getlong(&address->l_tail->l_hatom));
}

void popup_extrude_edge(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_machines *x = (t_machines *)d_ob->orig_obj;
	if (d_ob->m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_EDGE)
		extrude_edge(x, d_ob->m_interface.mousedown_item_identifier.idx);
}



void show_edge_popup_menu(t_machines *x, t_object *patcherview, t_pt pt, long modifiers)
{
	ezdisplay_popup_menu(dadaobj_cast(x), patcherview,
						 (char *)"Delete (Subdivide Into 2 Into 3 Into 4 Into 5 Into 6 Into 7 Into 8) Extrude", "0 0 0", "", "", "", "", 
						 (void *)popup_delete_edge, (void *)popup_subdivide_edge, (void *)popup_extrude_edge, WHITENULL);
}



void popup_change_machine(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_machines *x = (t_machines *)d_ob->orig_obj;
	if (d_ob->m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_VERTEX) {
        change_machine_for_selection(x, label_to_machine(x, label));
	}
}


void show_vertex_popup_menu(t_machines *x, t_object *patcherview, t_pt pt, long modifiers)
{
    long machine = -1;
	if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_VERTEX && x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx >= 0 && x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx < x->network_graph.num_vertices) {
		machine = label_to_machine(x, x->network_graph.vertices[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx].data.m_vanillabox.type);
	}
	
    t_llll *structure_ll = llll_get();
    t_llll *substructure_ll = llll_get();
    t_llll *functions_model_ll = llll_get();
    t_llll *subfunctions_model_ll = llll_get();
    t_llll *checked_ll = llll_get();
    t_llll *subchecked_ll = llll_get();
    llll_appendsym(structure_ll, gensym("Delete"));
    llll_appendobj(functions_model_ll, (void *)popup_delete_vertex);
    llll_appendlong(checked_ll, 0);
    llll_appendsym(structure_ll, gensym("separator"));
    llll_appendobj(functions_model_ll, NULL);
    llll_appendlong(checked_ll, 0);

    llll_appendsym(substructure_ll, gensym("Change Machine"));
    llll_appendobj(subfunctions_model_ll, NULL);
    llll_appendlong(subchecked_ll, 0);

    long i;
    for (i = 0; i < x->num_prototypes; i++) {
        llll_appendsym(substructure_ll, x->prototype[i].fullname);
        llll_appendobj(functions_model_ll, (void *)popup_change_machine);
        llll_appendlong(subchecked_ll, machine == i);
    }
    llll_appendllll(structure_ll, substructure_ll);
    llll_appendllll(functions_model_ll, subfunctions_model_ll);
    llll_appendllll(checked_ll, subchecked_ll);
    
    display_popup_menu(dadaobj_cast(x), patcherview, structure_ll, functions_model_ll, NULL, checked_ll, NULL, NULL, 0);
    
    llll_free(structure_ll);
    llll_free(functions_model_ll);
    llll_free(checked_ll);
}



void popup_add_machine(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_machines *x = (t_machines *)d_ob->orig_obj;
	long machine = label_to_machine(x, label);
	graph_add_vertex(&x->network_graph, d_ob->m_interface.mousedown_coord, build_vanillabox_metadata(machine_to_name(x, machine), machine_to_num_ins(x, machine), machine_to_num_outs(x, machine)), x->network_machine_size, x->network_machine_size);
	
	postprocess_network(x);
}



void show_bg_popup_menu(t_machines *x, t_object *patcherview, t_pt pt, long modifiers)
{
    
    t_llll *structure_ll = llll_get();
    t_llll *substructure_ll = llll_get();
    t_llll *functions_model_ll = llll_get();
    t_llll *subfunctions_model_ll = llll_get();
    
    llll_appendsym(structure_ll, gensym("Center View"));
    llll_appendobj(functions_model_ll, (void *)popup_center_view);

    llll_appendsym(structure_ll, gensym("Reset Zoom"));
    llll_appendobj(functions_model_ll, (void *)popup_reset_zoom);

    llll_appendsym(structure_ll, gensym("separator"));
    llll_appendobj(functions_model_ll, NULL);
    
    llll_appendsym(substructure_ll, gensym("Add Machine"));
    llll_appendobj(subfunctions_model_ll, NULL);
    
    long i;
    for (i = 0; i < x->num_prototypes; i++) {
        llll_appendsym(substructure_ll, x->prototype[i].fullname);
        llll_appendobj(functions_model_ll, (void *)popup_add_machine);
    }
    llll_appendllll(structure_ll, substructure_ll);
    llll_appendllll(functions_model_ll, subfunctions_model_ll);
    
    display_popup_menu(dadaobj_cast(x), patcherview, structure_ll, functions_model_ll, NULL, NULL, NULL, NULL, 0);
    
    llll_free(structure_ll);
    llll_free(functions_model_ll);
}


////////// INTERFACE FUNCTIONS

void machines_focusgained(t_machines *x, t_object *patcherview) {
	if (dadaobj_focusgained(dadaobj_cast(x), patcherview))
		return;
}

void machines_focuslost(t_machines *x, t_object *patcherview) {
	if (dadaobj_focuslost(dadaobj_cast(x), patcherview))
		return;
}

void machines_mousemove(t_machines *x, t_object *patcherview, t_pt pt, long modifiers) {

	llll_format_modifiers(&modifiers, NULL);
	
	if (dadaobj_mousemove(dadaobj_cast(x), patcherview, pt, modifiers))
		return;

	if (x->b_ob.d_ob.m_interface.allow_mouse_hover) {
		if (!x->b_ob.d_ob.m_interface.mouse_is_down) {
			x->b_ob.d_ob.m_interface.mousemove_item_identifier = pixel_to_element(x, pt, patcherview, NULL);
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
    } else if (x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_SELECT) {
        dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_CROSSHAIR);
	} else if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_VERTEX && modifiers == eAltKey) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DUPLICATE_POINT);
	} else if ((x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_VERTEX || x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_EDGE) 
			   && modifiers == eCommandKey) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DELETE);
	} else if ((x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_VERTEX || x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_EDGE) 
			   && x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_ARROW) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_MOVE);
	} else if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_MACHINE_OUTLET) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_GLUE);
	} else {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
	}

}


void machines_mousedown(t_machines *x, t_object *patcherview, t_pt pt, long modifiers){

    if (dadaobj_mousedown(dadaobj_cast(x), patcherview, pt, modifiers)){
        // don't return
    }

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

char machines_snap_selection_to_grid_fn(t_dadaobj *r_ob, t_dadaitem *item, void *data)
{
    dadaitem_move(r_ob, item, build_pt(round(item->coord.x/r_ob->m_grid.grid_size.x) * r_ob->m_grid.grid_size.x, round(item->coord.y/r_ob->m_grid.grid_size.y) * r_ob->m_grid.grid_size.y), DIA_INTERFACE);
    return 0;
}


void machines_snap_selection_to_grid(t_machines *x)
{
    dadaobj_selection_iterate(dadaobj_cast(x), machines_snap_selection_to_grid_fn, NULL);
}

    
void machines_mouseup(t_machines *x, t_object *patcherview, t_pt pt, long modifiers)
{
    char dirty = undo_are_there_free_undo_ticks(&x->b_ob.d_ob.m_undo);

	llll_format_modifiers(&modifiers, NULL);
	
    if (x->b_ob.d_ob.m_grid.snap_to_grid && dirty) {
        machines_snap_selection_to_grid(x);
        machines_iar(x);
    }
    
	if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_MACHINE_OUTLET && x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_MACHINE_INLET &&
		x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx >= 0 && x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx < x->network_graph.num_vertices &&
		x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx >= 0 && x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx < x->network_graph.num_vertices) {
		
		machines_undo_step_push_network(x, gensym("Connect Machines"));
		graph_add_edge(&x->network_graph, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx, 
					   build_outinnum_metadata(x->b_ob.d_ob.m_interface.mousedown_item_identifier.secondary_idx, 
											   x->b_ob.d_ob.m_interface.mousemove_item_identifier.secondary_idx));
		postprocess_network(x);
		jbox_redraw((t_jbox *)x);
	}
	
	if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_MACHINE_OUTLET && x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_MACHINE_INLET) {
		machines_mousemove(x, patcherview, pt, modifiers);
		jbox_redraw((t_jbox *)x);
	}

    if (dadaobj_mouseup(dadaobj_cast(x), patcherview, pt, modifiers))
        return;

	x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADAITEM_TYPE_NONE;
	x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag = 0;
}

char machine_move_vertices_delta_fn(t_dadaobj *r_ob, t_dadaitem *item, void *data)
{
    item->coord = pt_pt_sum(item->coord, *((t_pt *)data));
    return 0;
}


void machines_mousedrag(t_machines *x, t_object *patcherview, t_pt pt, long modifiers){
	
	llll_format_modifiers(&modifiers, NULL);
	
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
						machines_undo_step_push_network(x, gensym("Duplicate Vertex"));
						long new_idx = graph_duplicate_vertex(&x->network_graph, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, coord, false);
						if (new_idx < 0) {
							object_error((t_object *)x, "Can't duplicate vertex.");
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
						default:
                        {
                            machines_undo_step_push_network(x, gensym("Move Vertices"));
                            t_pt delta_coord = x->b_ob.d_ob.m_interface.mousedrag_delta_coord;
                            dadaobj_selection_iterate(dadaobj_cast(x), (dadaitem_iterfn)machine_move_vertices_delta_fn, &delta_coord);
                            machines_iar(x);
							break;
                        }
					}
					break;
			}
			break;

		case DADAITEM_TYPE_EDGE:
		{
			t_pt delta = delta_pix_to_delta_coord(dadaobj_cast(x), x->b_ob.d_ob.m_interface.mousedrag_delta_pix);
			move_edge_delta(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, delta, true);
		}
			break;
			
		case DADAITEM_TYPE_MACHINE_OUTLET:
        {
            double zoom = x->b_ob.d_ob.m_zoom.zoom.x;
			x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
			x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx = pixel_to_inlet_or_outlet(x, pt, patcherview, NULL, &x->b_ob.d_ob.m_interface.mousemove_item_identifier.type, &x->b_ob.d_ob.m_interface.mousemove_item_identifier.secondary_idx, zoom);
			if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type != DADAITEM_TYPE_MACHINE_INLET || x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx == x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx)
				x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
			if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_MACHINE_INLET &&
				are_inlet_and_outlet_connected(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, x->b_ob.d_ob.m_interface.mousedown_item_identifier.secondary_idx,
											   x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx, x->b_ob.d_ob.m_interface.mousemove_item_identifier.secondary_idx))
					x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE; // can't connect: already connected
			jbox_redraw((t_jbox *)x);
        }
			break;
			
			
		default:
			break;
	}
}



void machines_mousewheel(t_machines *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc){
	llll_format_modifiers(&modifiers, NULL);  

	if (dadaobj_mousewheel(dadaobj_cast(x), view, pt, modifiers, x_inc, y_inc)) {
		jbox_invalidate_layer((t_object *)x, NULL, gensym("network"));
		jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
		jbox_redraw((t_jbox *)x);
		return;
	}
}



long machines_keyup(t_machines *x, t_object *patcherview, long keycode, long modifiers, long textcharacter){
			
	llll_format_modifiers(&modifiers, &keycode);

	if (dadaobj_keyup(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
		return 1;
	
	return 0;
}


char delete_selected_vertices(t_machines *x)
{
    long i;
    for (i = 0; i < x->network_graph.num_vertices; i++)
        if (dadaitem_is_selected(&x->network_graph.vertices[i].r_it)) {
            if (!graph_delete_vertex(&x->network_graph, i, false)) {
                if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_VERTEX && x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx == i) {
                    x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
                    x->b_ob.d_ob.m_interface.mousemove_item_identifier.flag = 0;
                }
                
                if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_VERTEX && x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx == i) {
                    x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADAITEM_TYPE_NONE;
                    x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag = 0;
                }
                postprocess_network(x);
            }
            i--;
        }
    return 0;
}


long machines_key(t_machines *x, t_object *patcherview, long keycode, long modifiers, long textcharacter)
{
	llll_format_modifiers(&modifiers, &keycode);

	if (dadaobj_key(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
		return 1;

	switch (keycode) {
        case JKEY_BACKSPACE:
            machines_undo_step_push_network(x, gensym("Delete Vertices"));
            delete_selected_vertices(x);
            machines_iar(x);
            return 1;
        case JKEY_TAB:
            machines_autozoom_do(x, patcherview);
            return 1;
        case JKEY_UPARROW:
        case JKEY_DOWNARROW:
        case JKEY_LEFTARROW:
        case JKEY_RIGHTARROW:
        {
            machines_undo_step_push_network(x, gensym("Move Machines"));
            double amountx = x->b_ob.d_ob.m_grid.snap_to_grid ? x->b_ob.d_ob.m_grid.grid_size.x : 10;
            double amounty = x->b_ob.d_ob.m_grid.snap_to_grid ? x->b_ob.d_ob.m_grid.grid_size.y : 10;
            t_pt delta_coord = (keycode == JKEY_UPARROW ? build_pt(0, amounty) : (keycode == JKEY_DOWNARROW ? build_pt(0, -amounty) : (keycode == JKEY_LEFTARROW ? build_pt(-amountx, 0) : (keycode == JKEY_RIGHTARROW ? build_pt(amountx, 0) : build_pt(0, 0)))));
            if (modifiers & eShiftKey) delta_coord = pt_number_prod(delta_coord, 4);
            dadaobj_selection_iterate(dadaobj_cast(x), (dadaitem_iterfn)machine_move_vertices_delta_fn, &delta_coord);
            if (x->b_ob.d_ob.m_grid.snap_to_grid)
                machines_snap_selection_to_grid(x);
            machines_iar(x);
        }
            return 1;
		case JKEY_ESC:
            dadaobj_setzoom(dadaobj_cast(x), build_pt(100, 100));
            machines_iar(x);
			return 1;
		default:
			break;
	}

	return 0;
}


void machines_mouseenter(t_machines *x, t_object *patcherview, t_pt pt, long modifiers) 
{
	if (dadaobj_mouseenter(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
}

void machines_mouseleave(t_machines *x, t_object *patcherview, t_pt pt, long modifiers) 
{
	if (dadaobj_mouseleave(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
}



//// UNDO
void postprocess_network(t_machines *x)
{
	jbox_invalidate_layer((t_object *)x, NULL, gensym("network"));
	jbox_redraw((t_jbox *)x);
}


void machines_postprocess_undo(t_machines *x)
{
	jbox_invalidate_layer((t_object *)x, NULL, gensym("network"));
	jbox_redraw((t_jbox *)x);
}


void machines_undo_step_push_network(t_machines *x, t_symbol *operation)
{
	undo_add_interface_step(dadaobj_cast(x), DADA_FUNC_v_oX, (method)machines_set_network, NULL, DADA_FUNC_X_o, (method)machines_get_network, NULL, DADA_UNDO_OP_MODIFICATION,operation);
}



///// BUILD RANDOM GRAPH


long get_random_type(t_machines *x, t_machines_distrib *distrib, long min_num_inlets, long max_num_inlets)
{
	long i, i_start = 0;
	double temp, temp_start = 0, temp_end = distrib->total_weight, val;
	
	if (min_num_inlets > 0 || max_num_inlets < DADA_GRAPH_MAX_VANILLABOX_INS) {
		char forced_start = false, forced_end = false;
		for (temp = 0, i = 0; i < distrib->num_types; i++) {
			long num_ins = machine_to_num_ins(x, distrib->w_type[i].type);
			if (!forced_start && num_ins >= min_num_inlets) {
				temp_start = temp;
				i_start = i;
				forced_start = true;
			} 
			if (!forced_end && num_ins > max_num_inlets) {
				temp_end = temp;
				forced_end = true;
				break;
			} 
			temp += distrib->w_type[i].relative_weight;
		}
	}
	
	val = rand_range(temp_start, temp_end);
	for (temp = temp_start, i = i_start; temp < temp_end && i < distrib->num_types; i++) {
		temp += distrib->w_type[i].relative_weight;
		if (val < temp)
			return distrib->w_type[i].type;
	}
	
	return x->idle_prototype_id;
}

/*
long get_vertex_first_free_inlet(t_machines *x, long idx)
{
	long i;
	long num_ins = x->network_graph.vertices[idx].data.m_vanillabox.num_ins;
	for (i = 0; i < num_ins; i++) {
		if (!x->network_graph.vertices[idx].data.m_vanillabox.ins[i])
			return i;
	}
	return -1;
}
*/
	
/*
long find_nearest_free_node(t_machines *x, t_pt pt, long *free_inlet)
{
	long i, i_min = -1, i_free_inlet = 0;
	double dist = -1;
	for (i = 0; i < x->network_graph.num_vertices; i++) {
		double this_dist = pt_pt_distance(pt, x->network_graph.vertices[i].r_it.coord);
		long min_free_inlet = get_vertex_first_free_inlet(i);
		if (min_free_inlet >= 0 && (dist < 0 || this_dist < dist)) {
			this_dist = dist;
			i_min = i;
			i_free_inlet = min_free_inlet;
		}
	}
	if (free_inlet)
		*free_inlet = min_free_inlet;
	return i_min;
}*/


void distrib_fill_min_max_inlets(t_machines *x, t_machines_distrib *distrib)
{
	long i;
	long min = DADA_GRAPH_MAX_VANILLABOX_INS, max = 0;
	for (i = 0; i < distrib->num_types; i++) {
		if (distrib->w_type[i].relative_weight > 0) {
			long type = distrib->w_type[i].type;
			long num_ins = machine_to_num_ins(x, type);
			if (num_ins < min)
				min = num_ins;
			if (num_ins < max)
				max = num_ins;
		}
	}
	distrib->min_ins = min;
	distrib->max_ins = max;
}

t_dada_graph_metadata build_vanillabox_metadata_auto_ins_outs(t_machines *x, long machine_type)
{
	return build_vanillabox_metadata(machine_to_name(x, machine_type), machine_to_num_ins(x, machine_type), machine_to_num_outs(x, machine_type));
}

void build_random_branch(t_machines *x, long from, long from_outlet_num, long to, long to_inlet_num,
						 long *curr_num_machines, long tot_num_machines, t_machines_distrib *distrib, 
						 t_pt *coord, double min_rand_coord_dist, double max_rand_coord_dist, long branch_depth)
{
	if (*curr_num_machines < tot_num_machines && (rand_range(0, 100) <= 100./branch_depth)) {
		t_pt new_coord = get_random_pt_near_pt(*coord, min_rand_coord_dist, max_rand_coord_dist);
		long max_allowed_num_ins = (distrib->min_ins == 0 && *curr_num_machines < tot_num_machines - 1 ? DADA_GRAPH_MAX_VANILLABOX_INS : 1); // if we can generate stuff, then we can allow more than 1 inlet.
		long type = get_random_type(x, distrib, 1, max_allowed_num_ins);
		long num_ins = machine_to_num_ins(x, type);
		long num_outs = machine_to_num_outs(x, type);
		long i;
		
		// generating vertex
		long new_vertex = graph_add_vertex(&x->network_graph, new_coord, build_vanillabox_metadata_auto_ins_outs(x, type), x->network_machine_size, x->network_machine_size);
		graph_add_edge(&x->network_graph, from, new_vertex, build_outinnum_metadata(from_outlet_num, 0));
		(*curr_num_machines)++;

		for (i = 1; i < num_ins; i++) {
			// need generate stuff to fill inlets after the first one
			t_pt gen_coord = get_random_pt_near_pt(*coord, min_rand_coord_dist, max_rand_coord_dist);
			long gen_type = get_random_type(x, distrib, 0, 0);
			long gen_new_vertex = graph_add_vertex(&x->network_graph, gen_coord, build_vanillabox_metadata_auto_ins_outs(x, gen_type), x->network_machine_size, x->network_machine_size);
			(*curr_num_machines)++;
			*coord = gen_coord;
			build_random_branch(x, gen_new_vertex, 0, new_vertex, i, curr_num_machines, tot_num_machines, distrib, coord, min_rand_coord_dist, max_rand_coord_dist, branch_depth+1);
		}
		
		*coord = new_coord;
		
		if (num_outs > 1) {
			// need create branches for outlets after the first one: if we fork, we'll need to merge later on.
			t_pt middle_coord = get_random_pt_near_pt(*coord, min_rand_coord_dist, max_rand_coord_dist);
			long middle_type = get_random_type(x, distrib, num_outs, num_outs);
			long middle_new_vertex = graph_add_vertex(&x->network_graph, middle_coord, build_vanillabox_metadata_auto_ins_outs(x, middle_type), x->network_machine_size, x->network_machine_size);
			(*curr_num_machines)++;
			*coord = middle_coord;
			
			for (i = 0; i < num_outs; i++) 
				build_random_branch(x, new_vertex, i, middle_new_vertex, i, curr_num_machines, tot_num_machines, distrib, coord, min_rand_coord_dist, max_rand_coord_dist, branch_depth+1);
			new_vertex = middle_new_vertex;
		}
		
		// building branch from 1st outlet to desired inlet
		build_random_branch(x, new_vertex, 0, to, to_inlet_num, curr_num_machines, tot_num_machines, distrib, coord, min_rand_coord_dist, max_rand_coord_dist, branch_depth);
	} else {
		graph_add_edge(&x->network_graph, from, to, build_outinnum_metadata(from_outlet_num, to_inlet_num));
	}
}

int cmpfunc (void *data, const void * a, const void * b)
{
    t_machines *x = (t_machines *)data;
	return ( machine_to_num_ins(x, ((t_machines_weighted_type *)a)->type) - machine_to_num_ins(x, ((t_machines_weighted_type *)b)->type));
}

void build_random_network(t_machines *x, t_pt starting_coord, double min_random_dist, double max_random_dist, long tot_num_machines, t_machines_distrib distrib)
{
	long i;
	
	// sort distrib by number of inlets
	qsort_r(distrib.w_type, distrib.num_types, sizeof(t_machines_weighted_type), x, cmpfunc);
	
	distrib.total_weight = 0;
	for (i = 0; i < distrib.num_types; i++)
		distrib.total_weight += distrib.w_type[i].relative_weight;
	distrib_fill_min_max_inlets(x, &distrib);

	machines_undo_step_push_network(x, gensym("Build Random Network"));
	
	graph_clear(&x->network_graph);
	
	t_pt coord = starting_coord;
	long inlet = graph_add_vertex(&x->network_graph, coord, build_vanillabox_metadata(gensym("inlet"), machine_to_num_ins(x, x->inlet_prototype_id), machine_to_num_outs(x, x->inlet_prototype_id)), x->network_machine_size, x->network_machine_size);
	long outlet = graph_add_vertex(&x->network_graph, starting_coord, build_vanillabox_metadata(gensym("outlet"), machine_to_num_ins(x, x->outlet_prototype_id), machine_to_num_outs(x, x->outlet_prototype_id)), x->network_machine_size, x->network_machine_size);

	long curr_num_machines = 2;
	build_random_branch(x, inlet, 0, outlet, 0, &curr_num_machines, tot_num_machines, &distrib, &coord, min_random_dist, max_random_dist, 1);
	
	// find connected with outlet
	for (i = 0; i < x->network_graph.num_vertices; i++)
		if (graph_are_vertices_connected(&x->network_graph, i, outlet)) {
			graph_move_vertex(&x->network_graph, outlet, get_random_pt_near_pt(x->network_graph.vertices[i].r_it.coord, min_random_dist, max_random_dist));
			break;
		}
	
	postprocess_network(x);
}

