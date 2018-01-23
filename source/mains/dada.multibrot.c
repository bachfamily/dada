/**
	@file
	dada.multibrot.c
	
	@name
	dada.multibrot
	
	@realname 
	dada.multibrot

	@type
	object
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
    Mandelbrot set and its generalizations
	
	@description
	Get divergence information of multibrot sets
 
	@discussion
    The multibrot set is defined as the set of all non-divergent complex points <m>c</m> under the iterated system
    z ↤ z^d + c
    The exponent d is the set via the <m>exp</m> attribute.
    Complex points are interpreted in the straightforward (x, y) representation of the Gauss plane.
 
	@category
	dada, dada interfaces, dada rule-based systems

	@keywords
	surface, multibrot, fractal, mandelbrot, set, julia, series, converge, convergence, diverge, divergence
	
	@seealso
	bach.nodes
	
	@owner
	Daniele Ghisi
*/


#include "dada.interface.h"
#include "dada.geometry.h"
#include "dada.paint.h"
#include "notation.h"
//#include "dada.cursors.data.c"
#include "dada.math.h"
#include "dada.popupmenu.h"
#include "dada.undo.h"

#define DADA_multibrot_NOTEPOPUP_WIDTH 50
#define DADA_multibrot_NOTEPOPUP_HEIGHT 70

 

typedef struct _multibrot 
{
	t_dadaobj_jbox		b_ob; // root object
	

	//	behavior
    long            max_iterations;         ///< Max algorithm iterations
	
    t_pt            tester_coord;
    
	// display
	t_jrgba			j_testercolor;
    double			tester_size;

    t_jrgba			j_multibrotcolor;
    double          start_pos[2];
    double          exp;

    char			show_focus;
	
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
} t_multibrot;



///////////////////////// function prototypes
//// standard set
void *multibrot_new(t_symbol *s, long argc, t_atom *argv);
void multibrot_free(t_multibrot *x);
void multibrot_assist(t_multibrot *x, void *b, long m, long a, char *s);

void multibrot_paint(t_multibrot *x, t_object *view);
void multibrot_exportpng(t_multibrot *x, t_symbol *file, long dpi, double width, double height, t_pt exportcenteroffset);


void multibrot_int(t_multibrot *x, t_atom_long num);
void multibrot_float(t_multibrot *x, double num);
void multibrot_anything(t_multibrot *x, t_symbol *msg, long ac, t_atom *av);
void multibrot_bang(t_multibrot *x);


// get/set status
void multibrot_set_state(t_multibrot *x, t_llll *state);
t_llll *multibrot_get_state(t_multibrot *x, char get_multibrot, char get_testers);

// interface
void multibrot_focusgained(t_multibrot *x, t_object *patcherview);
void multibrot_focuslost(t_multibrot *x, t_object *patcherview);
void multibrot_mousedown(t_multibrot *x, t_object *patcherview, t_pt pt, long modifiers);
void multibrot_mousemove(t_multibrot *x, t_object *patcherview, t_pt pt, long modifiers);
void multibrot_mouseup(t_multibrot *x, t_object *patcherview, t_pt pt, long modifiers);
void multibrot_mousedrag(t_multibrot *x, t_object *patcherview, t_pt pt, long modifiers);
long multibrot_key(t_multibrot *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
long multibrot_keyup(t_multibrot *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
void multibrot_mousewheel(t_multibrot *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc);

void multibrot_mouseenter(t_multibrot *x, t_object *patcherview, t_pt pt, long modifiers);
void multibrot_mouseleave(t_multibrot *x, t_object *patcherview, t_pt pt, long modifiers);

t_max_err multibrot_notify(t_multibrot *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void multibrot_jsave(t_multibrot *x, t_dictionary *d);
void multibrot_preset(t_multibrot *x);
void multibrot_begin_preset(t_multibrot *x, t_symbol *s, long argc, t_atom *argv);
void multibrot_restore_preset(t_multibrot *x, t_symbol *s, long argc, t_atom *argv);
void multibrot_end_preset(t_multibrot *x);

t_max_err multibrot_setattr_tonedivision(t_multibrot *x, t_object *attr, long ac, t_atom *av);

void multibrot_undo_step_push_multibrot(t_multibrot *x, t_symbol *operation);
void multibrot_undo_postprocess(t_multibrot *x);

void process_change(t_multibrot *x);
double get_pitch_at_coord(t_multibrot *x, t_pt coord, double *velocity);


long coord_to_iteration(t_multibrot *x, t_pt coord);




///////////////////////// utility functions

// process any change which has happened for the shapes
void process_change(t_multibrot *x)
{
//	if (!x->creating_new_obj)
//		llllobj_outlet_bang((t_object *)x, LLLL_OBJ_UI, 3);
	
	jbox_redraw((t_jbox *)x);
}


//////////////////////// global class pointer variable
t_class *multibrot_class;

int C74_EXPORT main(void)
{	
	t_class *c;
	
	common_symbols_init();
	llllobj_common_symbols_init();
	
	srand(time(NULL)); // needed for the shake function

	if (dada_check_bach_version() || llllobj_test()) {
		dada_error_bachcheck();
		return 1;
	}


	CLASS_NEW_CHECK_SIZE(c, "dada.multibrot", (method)multibrot_new, (method)multibrot_free, (long)sizeof(t_multibrot), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, 0);	// include textfield and Fonts attributes
	//	jbox_initclass(c, 0);
	
	// paint & utilities
	class_addmethod(c, (method) multibrot_paint,			"paint", A_CANT, 0);
	class_addmethod(c, (method) multibrot_assist,			"assist",		A_CANT, 0);  
	class_addmethod(c, (method)	multibrot_notify,			"bachnotify",		A_CANT,		0);

	// save & preset
    class_addmethod(c, (method) multibrot_preset, "preset", 0);
    class_addmethod(c, (method) multibrot_begin_preset, "begin_preset", A_GIMME, 0);
    class_addmethod(c, (method) multibrot_restore_preset, "restore_preset", A_GIMME, 0);
    class_addmethod(c, (method) multibrot_end_preset, "end_preset", 0);
	CLASS_METHOD_ATTR_PARSE(c, "begin_preset", "undocumented", gensym("long"), 0L, "1");
	CLASS_METHOD_ATTR_PARSE(c, "restore_preset", "undocumented", gensym("long"), 0L, "1");
	CLASS_METHOD_ATTR_PARSE(c, "end_preset", "undocumented", gensym("long"), 0L, "1");
	class_addmethod(c, (method) multibrot_jsave, "jsave", A_CANT, 0);
	
	// interface
	class_addmethod(c, (method) multibrot_focusgained, "focusgained", A_CANT, 0);
	class_addmethod(c, (method) multibrot_focuslost, "focuslost", A_CANT, 0);
    
    // @method (mouse) @digest Output information
    // @description
    // @copy DADA_DOC_MOUSE_COMMANDS_STANDARD_NAVIGATION
    // <m>click</m> or <m>click+drag</m>: set tester position and output divergence information
	class_addmethod(c, (method) multibrot_mousedown, "mousedown", A_CANT, 0);
	class_addmethod(c, (method) multibrot_mousedrag, "mousedrag", A_CANT, 0);
	class_addmethod(c, (method) multibrot_mouseup, "mouseup", A_CANT, 0);
    
    
    // @method (keyboard) @digest Navigate
    // @description
    // @copy DADA_DOC_KEYBOARDS_COMMANDS_STANDARD_NAVIGATION
    // <m>Esc</m>: reset zoom
  	class_addmethod(c, (method) multibrot_key, "key", A_CANT, 0);
  	class_addmethod(c, (method) multibrot_keyup, "keyup", A_CANT, 0);
    
    // @method (tools) @digest Navigate
    // @description
    // @copy DADA_DOC_TOOLS_INTRO
    // @copy DADA_DOC_TOOLS_ZX
	class_addmethod(c, (method) multibrot_mousemove, "mousemove", A_CANT, 0);
	class_addmethod(c, (method) multibrot_mouseenter, "mouseenter", A_CANT, 0);
	class_addmethod(c, (method) multibrot_mouseleave, "mouseleave", A_CANT, 0);
	class_addmethod(c, (method) multibrot_mousewheel, "mousewheel", A_CANT, 0);
//	class_addmethod(c, (method) multibrot_bang,			"bang",			0);


    // @method getinfo @digest Output information
    // @description A <m>getinfo</m> symbol, followed by two numbers <m>x</m> and <m>y</m>,
    // outputs the information for the point (<m>x</m>, <m>y</m>), in the form:
    // <b>(coord <m>x</m> <m>y</m>) (belong <m>B</m>) (numiter <m>N</m>)</b>, where <m>B</m> is 1 if the iterated system
    // multibrots for the introduced point, or 0 otherwise, and <m>N</m> is the number of iterations
    // that it took to verify the divergence (if any, otherwise <m>N</m> will be equal to <m>maxiter</m>).
    // @marg 0 @name x @optional 0 @type number
    // @marg 1 @name y @optional 0 @type number
	class_addmethod(c, (method)multibrot_anything,	"anything",			A_GIMME,	0);
	class_addmethod(c, (method)multibrot_anything,	"setstoredstate",	A_GIMME, 0);

    
    // @method domain @digest Set the X domain
    // @description The <m>domain</m> message, followed by two numbers, sets minimum and maximum coordinates
    // to be displayed on the X axis.
    // The <m>domain</m> message,  followed by the "start" or "end" symbol and a number, sets the coordinate
    // to be displayed respectively at the left boundary or at the right boundary of the object box.
    // @marg 0 @name arguments @optional 0 @type list
    class_addmethod(c, (method)multibrot_anything,		"domain",		A_GIMME,	0);
    
    // @method range @digest Set the Y range
    // @description The <m>range</m> message, followed by two numbers, sets minimum and maximum coordinates
    // to be displayed on the Y axis
    // The <m>range</m> message,  followed by the "start" or "end" symbol and a number, sets the coordinate
    // to be displayed respectively at the bottom boundary or at top right boundary of the object box.
    // @marg 0 @name arguments @optional 0 @type list
    class_addmethod(c, (method)multibrot_anything,		"range",		A_GIMME,	0);
    
    
    // @method getdomain @digest Retrieve current X domain
    // @description The <m>getdomain</m> message outputs from the third outlet the minimum and maximum
    // coordinates displayed on the X axis, preceded by a <m>domain</m> symbol.
    class_addmethod(c, (method)multibrot_anything,		"getdomain",		A_GIMME,	0);
    
    
    // @method getrange @digest Retrieve current Y range
    // @description The <m>getrange</m> message outputs from the third outlet the minimum and maximum
    // coordinates displayed on the Y axis, preceded by a <m>range</m> symbol.
    class_addmethod(c, (method)multibrot_anything,		"getrange",		A_GIMME,	0);
  
    
    // @method exportpng @digest Export PNG image
    // @description The word <m>exportpng</m>, followed by an file path, exports the current canvas as a PNG image.
    // This can be further followed by a list formatted as:
    // <b>(<m>specification</m> <m>value</m>) (<m>specification</m> <m>value</m>)...</b>. <br />
    // Each specification can be one of the followings: <br />
    // • "dpi": the value is expected to be the dpi resolution of the exported image; <br />
    // • "width": the value is expected to be the width of the exported image in pixels; <br />
    // • "height": the value is expected to be the height of the exported image in pixels; <br />
    // • "center": the value is expected to be an llll containing the coordinates of the center; <br />
    // @marg 0 @name filename @optional 0 @type symbol
    // @marg 1 @name params @optional 1 @type llll
    class_addmethod(c, (method)multibrot_anything,		"exportpng",	A_GIMME,	0);
    
	llllobj_class_add_out_attr(c, LLLL_OBJ_UI);
	dadaobj_class_init(c, LLLL_OBJ_UI, DADAOBJ_BORDER | DADAOBJ_BORDER_SHOWDEFAULT | DADAOBJ_ZOOM | DADAOBJ_CENTEROFFSET | DADAOBJ_AXES | DADAOBJ_GRID | DADAOBJ_LABELS);
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"grid",0,"0.2 0.2");

    CLASS_ATTR_FILTER_CLIP(c, "zoom", 10, ATOM_LONG_MAX); // default clipping for zoom

    
	CLASS_ATTR_DEFAULT(c, "patching_rect", 0, "0 0 300 300");
	// @exclude dada.multibrot
	CLASS_ATTR_DEFAULT(c, "presentation_rect", 0, "0 0 300 300");
	// @exclude dada.node
	

	CLASS_STICKY_ATTR(c,"category",0,"Color");
	
	CLASS_ATTR_RGBA(c, "setcolor", 0, t_multibrot, j_multibrotcolor);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "setcolor", 0, "0. 0. 0. 1.");
	CLASS_ATTR_STYLE_LABEL(c, "setcolor", 0, "rgba", "Set Color");
	CLASS_ATTR_BASIC(c, "setcolor", 0);
	// @description Color of the multibrot set (i.e. of all the non-divergent points)
    
    CLASS_ATTR_RGBA(c, "knobcolor", 0, t_multibrot, j_testercolor);
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "knobcolor", 0, "0.3 0.3 0.3 1.");
    CLASS_ATTR_STYLE_LABEL(c, "knobcolor", 0, "rgba", "Knob Color");
    CLASS_ATTR_BASIC(c, "knobcolor", 0);
    // @description Sets the color of the test cursor.


	CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	
	CLASS_STICKY_ATTR(c,"category",0,"Algorithm");
	
	CLASS_ATTR_LONG(c, "maxiter", 0, t_multibrot, max_iterations);
    CLASS_ATTR_STYLE_LABEL(c, "maxiter", 0, "text", "Maximum Number of Iterations");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"maxiter",0,"100");
	// @description Sets the maximum number of iterations for the convergence algorithm.
    // The bigger this number is, the slower the calculation will be.

    CLASS_ATTR_DOUBLE_ARRAY(c, "start", 0, t_multibrot, start_pos, 2);
    CLASS_ATTR_STYLE_LABEL(c, "start", 0, "text", "Starting Position");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"start",0,"0 0");
    // @description Sets the initial position for the convergence algorithm;

    CLASS_ATTR_DOUBLE(c, "exp", 0, t_multibrot, exp);
    CLASS_ATTR_STYLE_LABEL(c, "exp", 0, "text", "Exponent");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"exp",0,"2.");
    // @description Sets the exponent for the convergence formula.

	CLASS_STICKY_ATTR_CLEAR(c, "category");
	
	CLASS_STICKY_ATTR(c,"category",0,"Appearance");
	
	CLASS_ATTR_CHAR(c, "showfocus", 0, t_multibrot, show_focus);
    CLASS_ATTR_STYLE_LABEL(c, "showfocus", 0, "onoff", "Show Focus");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showfocus",0,"1");
    
    CLASS_ATTR_DOUBLE(c, "knobsize", 0, t_multibrot, tester_size);
    CLASS_ATTR_STYLE_LABEL(c, "knobsize", 0, "text", "Knob Size");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"knobsize",0,"5.");
    // @description Sets the knob size.

	CLASS_STICKY_ATTR_CLEAR(c, "category");

		
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	multibrot_class = c;

	dev_post("dada.surf compiled %s %s", __DATE__, __TIME__);
	return 0;
}

t_max_err multibrot_notify(t_multibrot *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	if (msg == _sym_attr_modified) {
		t_symbol *attr_name = (t_symbol *)object_method((t_object *)data, _sym_getname);
//		if (attr_name == _llllobj_sym_zoom || attr_name == gensym("showvelocity") || attr_name == gensym("p") || attr_name == gensym("fast")) {
			jbox_invalidate_layer((t_object *)x, NULL, gensym("surface"));
			jbox_redraw((t_jbox *)x);
//		}
		
		if (!x->itsme)
			process_change(x);
	}
	
	return MAX_ERR_NONE;
}


void multibrot_begin_preset(t_multibrot *x, t_symbol *s, long argc, t_atom *argv)
{
	x->preset_ac = atom_getlong(argv) ;
	x->preset_av = (t_atom *)bach_newptr(x->preset_ac * sizeof(t_atom));
	
	// could allocate memory here etc.
	//	post("begin_preset %ld values will be arriving",x->b_ob.d_ob.preset_ac);
}


void multibrot_restore_preset(t_multibrot *x, t_symbol *s, long argc, t_atom *argv)
{
	long start, size;
	
	start = atom_getlong(argv);
	size = atom_getlong(argv + 1);
	//	post("restore_preset start %ld size %ld", start,size);
	
	sysmem_copyptr(argv+2, x->preset_av+start, size*sizeof(t_atom));
}

void multibrot_end_preset(t_multibrot *x)
{
	//	post("end_preset received");
	multibrot_anything(x, NULL, x->preset_ac,x->preset_av);
	bach_freeptr(x->preset_av);
}

void multibrot_preset(t_multibrot *x){
	t_atom temp[256];
	void *buf;
	long i, index, size;
	char wrote = false, begin = true, done = false;
	
	t_llll *data = multibrot_get_state(x, true, true);
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


void multibrot_jsave(t_multibrot *x, t_dictionary *d)
{
	if (x->b_ob.d_ob.save_data_with_patcher){
		if (x->b_ob.r_ob.l_dictll) {
			llll_store_in_dictionary(x->b_ob.r_ob.l_dictll, d, "multibrot_data", NULL);
		} else {
			t_llll *data = multibrot_get_state(x, true, true);
			llll_store_in_dictionary(data, d, "multibrot_data", NULL);
			llll_free(data);
		}
	} 
}
		



t_llll *multibrot_get_state(t_multibrot *x, char get_multibrot, char get_testers)
{
	// How do we save the information?
	// Two sublists: 1) multibrot, 2) testers
	// 1) in the form: ("multibrot" NODE1 NODE2 NODE3...) with NODE equal to ((x y) pitch_mc velocity)
	// 2) in the form: ("testers" TESTER1 TESTER2 TESTER3...) with TESTER equal to ((x y) channel)
	
	t_llll *data = llll_get();
    
    llll_appendsym(data, gensym("multibrot"));
    
/*	if (get_multibrot)
		llll_appendllll(data, multibrot_get_multibrot(x), 0, WHITENULL_llll);
	if (get_testers)
		llll_appendllll(data, multibrot_get_testers(x), 0, WHITENULL_llll);
*/
	return data;
}



// see multibrot_get_state about the codification of info
void multibrot_set_state(t_multibrot *x, t_llll *state)
{
/*	t_llll *multibrot = (state->l_head && hatom_gettype(&state->l_head->l_hatom) == H_LLLL) ? hatom_getllll(&state->l_head->l_hatom) : NULL;
	t_llll *testers = (state->l_head && state->l_head->l_next && hatom_gettype(&state->l_head->l_next->l_hatom) == H_LLLL) ? hatom_getllll(&state->l_head->l_next->l_hatom) : NULL;

	x->itsme = true;

	if (multibrot)
		multibrot_set_multibrot(x, multibrot);
	
	if (testers)
		multibrot_set_testers(x, testers);
	
	x->itsme = false;

	// reprocess stuff
	jbox_invalidate_layer((t_object *)x, NULL, gensym("surface"));
	process_change(x); */
}

void multibrot_assist(t_multibrot *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type getinfo @digest Get information about point
                             // @description First inlet expects <m>getinfo</m> message followed by the <m>x</m> and <m>y</m> of the point to inspect.
		sprintf(s, "getinfo");
	} 
	else {	
		if (a == 0)	// @out 0 @type llll @digest Dump outlet (unused)
			sprintf(s, "Dump Outlet (unused)"); // @description This outlet is currently unused, and kept for possible future compatibiity.
        else if (a == 1)	// @out 1 @type llll @digest Queries and Notifications
            sprintf(s, "Queries and Notifications"); // @description Outputs result for queries and notifications
		else if (a == 2)	// @out 2 @type llll @digest Click information
			sprintf(s, "Click Information"); // @description Outputs convergence information for the clicked point
		else if (a == 3)	// @out 3 @type llll @digest Message information
			sprintf(s, "Message Information"); // @description Outputs convergence information when a <m>getinfo</m> message is received
		else 	// @out 4 @type bang @digest bang when object is changed via the interface (unused)
            sprintf(s, "bang when Changed (unused)"); // @description This outlet is currently unused, and kept for possible future compatibiity.

	}
}

void multibrot_free(t_multibrot *x)
{
	object_free_debug(x->n_proxy1);
	dadaobj_jbox_free((t_dadaobj_jbox *)x); // jbox_free and llllobj_free are inside here
}


void multibrot_iar(t_multibrot *x)
{
    jbox_invalidate_layer((t_object *)x, NULL, gensym("surface"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
    jbox_redraw((t_jbox *)x);
}

void *multibrot_new(t_symbol *s, long argc, t_atom *argv)
{
	t_multibrot *x = NULL;
	t_dictionary *d = NULL;
	long boxflags;
	t_llll *llll_for_rebuild = NULL;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;    
	
	if ((x = (t_multibrot *)object_alloc_debug(multibrot_class))) {
		
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

		dadaobj_jbox_setup((t_dadaobj_jbox *)x, DADAOBJ_BORDER | DADAOBJ_BORDER_SHOWDEFAULT | DADAOBJ_ZOOM | DADAOBJ_CENTEROFFSET, build_pt(100., 100.), 2, 3, 2, (invalidate_and_redraw_fn)multibrot_iar, "vn", 2, "b4444");
		dadaobj_addfunctions(dadaobj_cast(x), (dada_mousemove_fn)multibrot_mousemove, NULL, (method)multibrot_undo_postprocess, (get_state_fn)multibrot_get_state, (set_state_fn)multibrot_set_state, NULL, NULL, NULL);
        x->b_ob.d_ob.m_zoom.max_zoom_perc = build_pt(1000000000, 1000000000);

		x->b_ob.d_ob.m_tools.curr_tool = DADA_TOOL_ARROW;
		x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
		
		x->firsttime = true;
		
		attr_dictionary_process(x,d);
		
		if ((llll_for_rebuild = llll_retrieve_from_dictionary(d, "multibrot_data"))) { // new method
			llllobj_manage_dict_llll((t_object *)x, LLLL_OBJ_UI, llll_for_rebuild);
			multibrot_set_state(x, llll_for_rebuild);
			llll_free(llll_for_rebuild);
		}
		
		jbox_ready((t_jbox *)x);
		
        dadaobj_set_current_version_number(dadaobj_cast(x));

		x->creating_new_obj = false;
	}
	return x;
}

void multibrot_int(t_multibrot *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	multibrot_anything(x, _sym_list, 1, argv);
}

void multibrot_float(t_multibrot *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	multibrot_anything(x, _sym_list, 1, argv);
}

// output sampled information
void multibrot_bang(t_multibrot *x)
{	
	return;
}

void multibrot_dump(t_multibrot *x, char get_multibrot, char get_testers)
{	
	t_llll *ll = multibrot_get_state(x, get_multibrot, get_testers);
	llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 0, ll);
	llll_free(ll);
}

void output_info_for_pt(t_multibrot *x, t_pt pt, long outletnum)
{
    t_llll *ll = llll_get();
    long iteration_num = coord_to_iteration(x, pt);
    llll_appendllll(ll, symbol_and_llll_to_llll_chained(gensym("coord"), pt_to_llll(pt, false)));
    llll_appendllll(ll, symbol_and_long_to_llll(gensym("belong"), iteration_num >= x->max_iterations));
    llll_appendllll(ll, symbol_and_long_to_llll(gensym("numiter"), iteration_num));
    llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, outletnum, ll);
    llll_free(ll);
}

void multibrot_anything(t_multibrot *x, t_symbol *msg, long ac, t_atom *av)
{
	dadaobj_anything(dadaobj_cast(x), msg, ac, av);

	t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, msg, ac, av, LLLL_PARSE_CLONE);
	if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
		t_symbol *router = hatom_getsym(&parsed->l_head->l_hatom);
		llll_behead(parsed);
		
        // There's no state nor dump for multibrot right now.
        // We'll keep them for possible future compatibility
/*		if (router == gensym("setstoredstate") || router == gensym("multibrot"))
			multibrot_set_state(x, parsed);
		else if (router == _sym_dump)
			multibrot_dump(x, parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("multibrot")), 
						 parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("testers")));
 */
        
        if (dadaobj_anything_handle_domain_or_range(dadaobj_cast(x), router, parsed, 1)) {
            // nothing to do!
        } else if (router == gensym("getinfo")) {
            t_pt pt = llll_to_pt(parsed);
            output_info_for_pt(x, pt, 3);
        } else if (router == gensym("exportpng")) {
            long dpi;
            t_symbol *filename;
            double width, height;
            t_pt exportcenter;
            if (!dadaobj_parse_export_png_syntax(dadaobj_cast(x), NULL, parsed, &filename, &dpi, &width, &height, &exportcenter))
                multibrot_exportpng(x, filename, dpi, width, height, exportcenter);
        }
	} else {
//		multibrot_set_state(x, parsed);
	}
	llll_free(parsed);
}


t_dadaitem_identifier pixel_to_element(t_multibrot *x, t_pt pt, t_object *view, t_pt *coordinates, char include_testers)
{
	t_dadaitem_identifier result;
	result.type = DADAITEM_TYPE_NONE;
	result.flag = 0;
    result.idx = result.secondary_idx = result.tertiary_idx = -1;
	
/*	if (include_testers && (idx = pixel_to_tester(x, pt, view, coordinates)) >= 0) {
		result.type = DADA_multibrot_ELEMENT_TESTER;
		result.idx = idx;
	} else if ((idx = pixel_to_node(x, pt, view, coordinates)) >= 0) {
		result.type = DADA_multibrot_ELEMENT_NODE;
		result.idx = idx;
	}
*/
	return result;
}




//// GRAPHIC DRAWING


t_pt complex_exp(t_pt pt, double exp)
{
    if (exp == 2.) {
        double xtemp = pt.x * pt.x - pt.y * pt.y;
        pt.y = 2 * pt.x * pt.y;
        pt.x = xtemp;
        return pt;
    } else if (exp == 1.) {
        return pt;
    } else if (exp == 0.) {
        return build_pt(1., 0.);
    } else if (exp == 3.) {
        double ptx2 = pt.x * pt.x;
        double pty2 = pt.y * pt.y;
        double xtemp = ptx2 * pt.x - 3 * pt.x * pty2;
        pt.y = 3 * ptx2 * pt.y - pty2 * pt.y;
        pt.x = xtemp;
        return pt;
    } else if (exp == 5.) {
        double xtemp = pow(pt.x, 5) - 10 * pow(pt.x, 3) * pow(pt.y, 2) + 5 * pt.x * pow(pt.y, 4);
        pt.y = 5*pow(pt.x, 4)*pt.y-10*pt.x * pt.x *pow(pt.y, 3)+pow(pt.y, 5);
        pt.x = xtemp;
        return pt;
    } else {
        double temp1 = pow(pt.x*pt.x+pt.y*pt.y, exp/2.);
        double temp2 = exp*atan2(pt.y,pt.x);
        double xtmp=temp1*cos(temp2);
        pt.y=temp1*sin(temp2);
        pt.x=xtmp;
        
/*        long double ptx = pt.x, pty = pt.y;
        long double rho = sqrtl(ptx * ptx + pty * pty);
        long double theta = atan2l(pty, ptx);
        return build_pt(rho * cosl(exp * theta), rho * sinl(exp * theta)); */
        return pt;
    }
    return build_pt(0, 0);
}

long coord_to_iteration(t_multibrot *x, t_pt coord)
{
    t_pt pt = build_pt(x->start_pos[0], x->start_pos[1]);
    long iteration = 0;
    double exp = x->exp;
    long max_iteration = x->max_iterations;
    while ( pt.x * pt.x + pt.y * pt.y < 2 * 2  &&  iteration < max_iteration ) {
        // computing pt * pt + coord
        pt = complex_exp(pt, exp);
        pt.x += coord.x;
        pt.y += coord.y;

/*        double xtemp = pt.x * pt.x - pt.y * pt.y + coord.x;
        pt.y = 2 * pt.x * pt.y + coord.y;
        pt.x = xtemp;
*/
        iteration++;
    }
    return iteration;
}

t_jrgba iteration_to_color(t_multibrot *x, long iteration)
{
    if (iteration == x->max_iterations)
        return x->j_multibrotcolor;
    return double_to_color(iteration, 0., x->max_iterations, false);
}

t_jrgba get_color_at_coord(t_multibrot *x, t_pt coord, double *pitch_at_coord, double *velocity_at_coord)
{
    return iteration_to_color(x, coord_to_iteration(x, coord));

}


void multibrot_paint_surface(t_multibrot *x, t_object *view, t_jgraphics *g, t_rect rect, t_pt center, double zoom){
	
    char to_layer = 0;
    if (!g) {
        to_layer = 1;
        g = jbox_start_layer((t_object *)x, view, gensym("surface"), rect.width, rect.height);
    }
	
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
		
        if (to_layer)
            jbox_end_layer((t_object *)x, view, gensym("surface"));
	}
	
    if (to_layer)
        jbox_paint_layer((t_object *)x, view, gensym("surface"), 0., 0.);	// position of the layer
}


void paint_main_tester(t_multibrot *x, t_jgraphics *g, t_object *view, t_rect rect, t_pt center)
{
    double size = x->tester_size;
    t_pt pix = coord_to_pix(dadaobj_cast(x), center, x->tester_coord);
    paint_line(g, x->j_testercolor, pix.x + 1.5, pix.y, pix.x + size + 1.5, pix.y, 1);
    paint_line(g, x->j_testercolor, pix.x - 1.5, pix.y, pix.x - size - 1.5, pix.y, 1);
    paint_line(g, x->j_testercolor, pix.x, pix.y + 1.5, pix.x, pix.y + size + 1.5, 1);
    paint_line(g, x->j_testercolor, pix.x, pix.y - 1.5, pix.x, pix.y - size - 1.5, 1);
}

void multibrot_paint(t_multibrot *x, t_object *view)
{
	t_rect rect;
	t_pt center = get_center_pix(dadaobj_cast(x), view, &rect);
	double zoom = x->b_ob.d_ob.m_zoom.zoom.x;
	t_jgraphics *g = (t_jgraphics*) patcherview_get_jgraphics(view); 

	jgraphics_set_source_rgba(g, 0, 0, 0, 1); // alpha = 1;
	
	multibrot_paint_surface(x, view, NULL, rect, center, zoom); // g = NULL, since we wanna paint it on a layer

    dadaobj_paint_grid(dadaobj_cast(x), view, rect, center);

    if (x->b_ob.d_ob.m_interface.mouse_is_down)
        paint_main_tester(x, g, view, rect, center);
    
    dadaobj_paint_border(dadaobj_cast(x), g, &rect);
}


void multibrot_exportpng(t_multibrot *x, t_symbol *file, long dpi, double width, double height, t_pt exportcenteroffset)
{
    t_rect exportrect = build_rect(0, 0, width, height);
    t_pt exportcenter = coord_to_pix(dadaobj_cast(x), build_pt(width/2., height/2.), exportcenteroffset);
    t_fourcc outtype = 0;
    t_fourcc filetype[] = {'PNG', 'PNG ', 'PNGf'};
    short path = 0;
    char filename[MAX_PATH_CHARS];
    filename[0] = 0;
    
    if (file) {
        path_frompotentialpathname(file->s_name, &path, filename);
    } else {
        if (bach_openfile_for_read((t_object *)x, gensym("testfile.png"), &path, filetype, sizeof(filetype) / sizeof(t_fourcc), &outtype, filename) == MAX_ERR_NONE)
            filename[0] = 0;
    }
    
    if (filename[0]){
        t_jsurface *s_studio = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, exportrect.width, exportrect.height);
        t_jgraphics *g_studio = jgraphics_create(s_studio);
        jgraphics_set_source_rgba(g_studio, 0, 0, 0, 1.);
        multibrot_paint_surface(x, NULL, g_studio, exportrect, exportcenter, x->b_ob.d_ob.m_zoom.zoom.x);
        jgraphics_image_surface_writepng(s_studio, filename, path, dpi);
        jgraphics_destroy(g_studio);
        jgraphics_surface_destroy(s_studio);
    }
}



///////// POPUP MENU FUNCTIONS
/*
void popup_delete_node(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_multibrot *x = (t_multibrot *)d_ob->orig_obj;
	if (d_ob->m_interface.mousedown_item_identifier.type == DADA_multibrot_ELEMENT_NODE)
		delete_node(x, d_ob->m_interface.mousedown_item_identifier.idx);
}

void show_node_popup_menu(t_multibrot *x, t_object *patcherview, t_pt pt, long modifiers)
{
	ezdisplay_popup_menu(dadaobj_cast(x), patcherview,
						 (char *)"Delete", "0", "", "", "", "", 
						 (void *)popup_delete_node, WHITENULL);
}

void show_bg_popup_menu(t_multibrot *x, t_object *patcherview, t_pt pt, long modifiers)
{
	ezdisplay_popup_menu(dadaobj_cast(x), patcherview,
						 (char *)"Center View Reset Zoom", "0", "", "", "", "", 
						 (void *)popup_center_view, (void *)popup_reset_zoom, WHITENULL);
}


*/

////////// INTERFACE FUNCTIONS

void multibrot_focusgained(t_multibrot *x, t_object *patcherview) {
	if (dadaobj_focusgained(dadaobj_cast(x), patcherview))
		return;
}

void multibrot_focuslost(t_multibrot *x, t_object *patcherview) {
	if (dadaobj_focuslost(dadaobj_cast(x), patcherview))
		return;
}

void multibrot_mousemove(t_multibrot *x, t_object *patcherview, t_pt pt, long modifiers) {

	llll_format_modifiers(&modifiers, NULL);
	
	if (dadaobj_mousemove(dadaobj_cast(x), patcherview, pt, modifiers))
		return;

	if (x->b_ob.d_ob.m_interface.allow_mouse_hover) {
		x->b_ob.d_ob.m_interface.mousemove_item_identifier = pixel_to_element(x, pt, patcherview, NULL, false);
		jbox_redraw((t_jbox *)x);
	} else {
		if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type != DADAITEM_TYPE_NONE) {
			x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
			dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
			jbox_redraw((t_jbox *)x);
		}
	}
	
    dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);

}


void multibrot_mousedown(t_multibrot *x, t_object *patcherview, t_pt pt, long modifiers)
{

	if (dadaobj_mousedown(dadaobj_cast(x), patcherview, pt, modifiers))
		return;

	x->b_ob.d_ob.m_interface.mousedown_item_identifier = pixel_to_element(x, pt, patcherview, &x->b_ob.d_ob.m_interface.mousedown_coord, false);
		
    llll_format_modifiers(&modifiers, NULL);
    x->tester_coord = x->b_ob.d_ob.m_interface.mousedown_coord;
    output_info_for_pt(x, x->tester_coord, 2);
	jbox_redraw((t_jbox *)x);
}

void multibrot_mouseup(t_multibrot *x, t_object *patcherview, t_pt pt, long modifiers)
{

	llll_format_modifiers(&modifiers, NULL);
	
	if (dadaobj_mouseup(dadaobj_cast(x), patcherview, pt, modifiers))
		return;

	x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADAITEM_TYPE_NONE;
	x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag = 0;

	if (x->b_ob.d_ob.m_cursors.curr_cursor == BACH_CURSOR_NONE) { 
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
		multibrot_mousemove(x, patcherview, pt, modifiers);
	}
    jbox_redraw((t_jbox *)x);
}

void multibrot_mousedrag(t_multibrot *x, t_object *patcherview, t_pt pt, long modifiers)
{
	
	llll_format_modifiers(&modifiers, NULL);
	
    if (dadaobj_mousedrag(dadaobj_cast(x), patcherview, pt, modifiers)) {
        jbox_invalidate_layer((t_object *)x, NULL, gensym("surface"));
        return;
    }

    x->tester_coord = x->b_ob.d_ob.m_interface.mousedrag_coord;
    output_info_for_pt(x, x->tester_coord, 2);

    jbox_redraw((t_jbox *)x);
}



void multibrot_mousewheel(t_multibrot *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc)
{
	llll_format_modifiers(&modifiers, NULL);  

	if (dadaobj_mousewheel(dadaobj_cast(x), view, pt, modifiers, x_inc, y_inc)) {
        multibrot_iar(x);
		return;
	}
}



long multibrot_keyup(t_multibrot *x, t_object *patcherview, long keycode, long modifiers, long textcharacter)
{
			
	llll_format_modifiers(&modifiers, &keycode);

	if (dadaobj_keyup(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
		return 1;
	
	return 0;
}

long multibrot_key(t_multibrot *x, t_object *patcherview, long keycode, long modifiers, long textcharacter)
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
            dadaobj_setzoom(dadaobj_cast(x), build_pt(100, 100));
            jbox_invalidate_layer((t_object *)x, NULL, gensym("surface"));
            break;
		default:
			break;
	}

	return 0;
}


void multibrot_mouseenter(t_multibrot *x, t_object *patcherview, t_pt pt, long modifiers) 
{
	if (dadaobj_mouseenter(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
}

void multibrot_mouseleave(t_multibrot *x, t_object *patcherview, t_pt pt, long modifiers) 
{
	if (dadaobj_mouseleave(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
}



////// UNDO HANDLING


void multibrot_undo_postprocess(t_multibrot *x)
{
	jbox_invalidate_layer((t_object *)x, NULL, gensym("surface"));
	jbox_redraw((t_jbox *)x);
}


void multibrot_undo_step_push(t_multibrot *x, t_symbol *operation)
{
	undo_add_interface_step(dadaobj_cast(x), DADA_FUNC_v_oX, (method)multibrot_set_state, NULL, DADA_FUNC_X_o, (method)multibrot_get_state, NULL, DADA_UNDO_OP_MODIFICATION, operation);
}
