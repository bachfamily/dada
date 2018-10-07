/**
	@file
	dada.terrain~.c
	
	@name
	dada.terrain~
	
	@realname
	dada.terrain~
 
	@type
	object
	
	@module
	dada
 
	@author
	Daniele Ghisi
	
	@digest
	Wave-terrain synthesis
	
	@description
	Wave-terrain synthesis and polar buffer-based interpolation of radially arranged buffers
	
	@discussion
 
	@category
	dada interfaces, dada geometry, dada audio
 
	@keywords
	terrain~, wave, audio, terrain, interpolation,
	
	@seealso
	dada.terrain.ellipse~, dada.terrain.rect~, dada.terrain.segment~, dada.terrain.spiral~
	
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

#include "ext.h"							// standard Max include, always required
#include "ext_obex.h"						// required for new style Max object
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "z_dsp.h"							// should be after jpatcher_api.h
#include "ext_drag.h"
#include "ext_buffer.h"



#define DADA_TERRAIN_MAX_NUM_BUFFERS 16
#define DADA_TERRAIN_MAX_NUM_PATH_PT 4096
#define DADA_TERRAIN_BUF_SPEED_LINEAR 1 // 1 unit means 1 ms

#define DADA_TERRAIN_DEBUG


#ifdef DADA_TERRAIN_DEBUG
#define terrain_dev_post(...) if (x->debug) post(__VA_ARGS__)
#else
#define terrain_dev_post(...) ((void) 0)
#endif

typedef enum _terrain_type
{
    DADA_TERRAIN_TYPE_EQUATION = 0,
    DADA_TERRAIN_TYPE_WHEEL = 1,
} e_terrain_type;


typedef enum _path_mode
{
    DADA_TERRAIN_PATH_MODE_POINTS = 0,
    DADA_TERRAIN_PATH_MODE_LINES = 1,
} e_path_mode;


typedef enum _combination_mode
{
    DADA_TERRAIN_MODE_ADDITIVE = 0,
    DADA_TERRAIN_MODE_MULTIPLICATIVE = 1,
} e_combination_mode;

/** Polar coordinates */
typedef struct _polar_pt
{
    double rho;				///< The radius
    double theta;		    ///< The angle
} t_polar_pt;


typedef double (*terrain_wheel_fn)(double sample_val, double factor, double rho, double theta);
typedef double (*terrain_static_fn)(double x, double y, double rho, double theta);

typedef struct _terrain {
    t_dadaobj_pxjbox	b_ob;
    
    t_llll              *buffers_as_llll;
    long                num_buffers;
    double              buffer_angle[DADA_TERRAIN_MAX_NUM_BUFFERS];
    t_buffer_ref        *buffer_reference[DADA_TERRAIN_MAX_NUM_BUFFERS];
    t_buffer_info       buffer_info[DADA_TERRAIN_MAX_NUM_BUFFERS];
    
    char                terrain_type;
    char                polar;
    
    double              modulation_amount;
    char                equal_power;
    
    t_polar_pt          curr_pt;        // if x->polar is off it actually contains a standard t_pt information (quite ugly, but hacky)
    
    t_jrgba             j_path_color;
    double              path_line_width;
    long                path_max_points;
    t_pt                path[DADA_TERRAIN_MAX_NUM_PATH_PT];
    long                path_curr_idx;
    long                path_num_points;
    
    long                num_out_channels;
    
    char                autozoom;
    char                must_autozoom;
    
    // surfaces
    t_jsurface          *terrain;
    
    void                *clock;
    char                startclock;
    double              redraw_time_ms;
    
    void                *refresh_buffers_qelem;
    
    t_object            *clang_wheel;
    t_object            *clang_static;
    terrain_wheel_fn    terrain_wheel_fn;
    terrain_static_fn   terrain_static_fn;
    t_symbol            *terrain_wheel_code;
    t_symbol            *terrain_static_code;
    char                mode;

    // show/hide
    char                show_terrain;
    char                show_buffers;
    char                show_names;
    char                path_mode;
    
    
    // debug stuff
    char                dsp_debug;
    char                debug;
} t_terrain;


void *terrain_new(t_symbol *s, long argc, t_atom *argv);
void terrain_free(t_terrain *x);
void terrain_assist(t_terrain *x, void *b, long m, long a, char *s);
void terrain_paint(t_terrain *x, t_object *patcherview);
void terrain_paint_ext(t_terrain *x, t_object *view, t_dada_force_graphics *force_graphics);

t_atom_long terrain_acceptsdrag(t_terrain *x, t_object *drag, t_object *view);
void terrain_perform64(t_terrain *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void terrain_dsp64(t_terrain *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void terrain_doset(t_terrain *x, t_symbol *s);
void terrain_anything(t_terrain *x, t_symbol *msg, long ac, t_atom *av);
void terrain_tick(t_terrain *x);
t_max_err terrain_notify(t_terrain *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void terrain_bang(t_terrain *x);

double terrain_display_to_ms(t_terrain *x, double pixel);
double terrain_ms_to_display(t_terrain *x, double ms);
double terrain_deg_to_rad(t_terrain *x, double deg);
double terrain_rad_to_deg(t_terrain *x, double rad);

t_polar_pt terrain_cartopol(t_pt pt);
t_pt terrain_poltocar(t_polar_pt polar);

void terrain_autozoom(t_terrain *x);
void terrain_autozoom_do(t_terrain *x, t_object *view, char also_lock_mutex);

double terrain_get_buffer_length_ms(t_terrain *x, long idx);
void terrain_iar(t_terrain *x);


void terrain_set_custom_wheelfunction(t_terrain *x, t_symbol *code);
t_max_err terrain_setattr_wheelfunction(t_terrain *x, void *attr, long argc, t_atom *argv);
void terrain_set_custom_staticfunction(t_terrain *x, t_symbol *code);
t_max_err terrain_setattr_staticfunction(t_terrain *x, void *attr, long argc, t_atom *argv);


DEFINE_LLLL_ATTR_DEFAULT_GETTER(t_terrain, buffers_as_llll, terrain_getattr_buffers);




static t_class *s_terrain_class;





double terrain_display_to_ms(t_terrain *x, double pixel)
{
    return pixel * DADA_TERRAIN_BUF_SPEED_LINEAR;
}

double terrain_ms_to_display(t_terrain *x, double ms)
{
    return ms / DADA_TERRAIN_BUF_SPEED_LINEAR;
}

// 180 : PI = deg : rad
double terrain_deg_to_rad(t_terrain *x, double deg)
{
    return deg * PI / 180.;
}

double terrain_rad_to_deg(t_terrain *x, double rad)
{
    return rad * 180. / PI;
}

void terrain_free_buffer_refs(t_terrain *x, long from_idx, long to_idx)
{
    long i;
    for (i = from_idx; i <= to_idx && i < DADA_TERRAIN_MAX_NUM_BUFFERS; i++) {
        object_free(x->buffer_reference[i]);
        x->buffer_reference[i] = NULL;
    }
}

// here's where we set the buffer~ we're going to access
void terrain_dosetbuffers(t_terrain *x, t_symbol *msg, long ac, t_atom *av)
{
    t_llll *ll = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UIMSP, NULL, ac, av, LLLL_PARSE_CLONE);
    t_llll *subll = NULL;
    t_llllelem *elem;

    dadaobj_mutex_lock(dadaobj_cast(x));

    long old_num_buffers = x->num_buffers;
    x->num_buffers = 0; // so that any other process will handle this as no-buffers situation.
    long num_buffers = 0;
    
    // free all buffer references
    terrain_free_buffer_refs(x, 0, old_num_buffers - 1);
    
    for (elem = ll->l_head; elem; elem = elem->l_next) {
        if (hatom_gettype(&elem->l_hatom) == H_LLLL && (subll = hatom_getllll(&elem->l_hatom)) && subll->l_size >= 2 && hatom_gettype(&subll->l_head->l_hatom) == H_SYM) {
            
            t_symbol *buffername = hatom_getsym(&subll->l_head->l_hatom);
            double bufferangle = hatom_to_angle_in_rad(&subll->l_head->l_next->l_hatom);
//            double bufferangle = terrain_deg_to_rad(x, hatom_getdouble(&subll->l_head->l_next->l_hatom));
            
            if (!x->buffer_reference[num_buffers])
                x->buffer_reference[num_buffers] = buffer_ref_new((t_object *)x, buffername);
            else
                buffer_ref_set(x->buffer_reference[num_buffers], buffername);
            
            x->buffer_angle[num_buffers] = bufferangle;
            
            // updating info
            t_buffer_obj *ob = buffer_ref_getobject(x->buffer_reference[num_buffers]);
            if (ob) {
                buffer_getinfo(ob, &x->buffer_info[num_buffers]);
                num_buffers++;
                if (num_buffers == DADA_TERRAIN_MAX_NUM_BUFFERS)
                    break;
            } else {
                // BUFFER NOT FOUND
                object_error((t_object *)x, "Couldn't link with buffer %s", buffername->s_name);
            }
        } else {
            object_error((t_object *)x, "Wrong syntax in buffer definition");
        }
        
    }
    llll_free(ll);

    x->num_buffers = num_buffers; // and we're ready to go, again!
    
    dadaobj_mutex_unlock(dadaobj_cast(x));

    terrain_iar(x);
}

t_max_err terrain_setattr_buffers(t_terrain *x, t_object *attr, long ac, t_atom *av)
{
    t_llll *ll;
    if (ac == 0 || av) {
        if ((ll = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UIMSP, NULL, ac, av, LLLL_PARSE_CLONE))) {
            t_llll *free_me;
            dadaobj_mutex_lock(dadaobj_cast(x));
            free_me = x->buffers_as_llll;
            
            t_atom *av = NULL;
            long ac = llll_deparse(ll, &av, 0, 0);
            defer_low(x, (method)terrain_dosetbuffers, NULL, ac, av);
            bach_freeptr(av);
            
            x->buffers_as_llll = ll;
            dadaobj_mutex_unlock(dadaobj_cast(x));
            llll_free(free_me);
            
            if (x->autozoom)
                x->must_autozoom = true;
        }
    }
    return MAX_ERR_NONE;
}

void terrain_refresh_buffers_qelem_do(t_terrain *x)
{
    t_atom *av = NULL;
    long ac = llll_deparse(x->buffers_as_llll, &av, 0, 0);
    defer(x, (method)terrain_dosetbuffers, NULL, ac, av);
    bach_freeptr(av);
}

t_max_err terrain_notify(t_terrain *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
    if (msg == gensym("buffer_modified")) {
        qelem_set(x->refresh_buffers_qelem);
    } else if (msg == gensym("attr_modified")) {
        t_symbol *name = (t_symbol *)object_method((t_object *)data, gensym("getname"));
        if (name == gensym("showbuffers") || name == gensym("shownames") || name == gensym("showterrain") || name == gensym("staticfunction") || name == gensym("wheelfunction") || name == gensym("mode") || name == gensym("eqp") || name == gensym("modulation") || name == gensym("wheelmode"))
            terrain_iar(x);
        else if (name == gensym("type")) {
            object_attr_setdisabled((t_object *)x, gensym("showbuffers"), x->terrain_type != DADA_TERRAIN_TYPE_WHEEL);
            object_attr_setdisabled((t_object *)x, gensym("shownames"), x->terrain_type != DADA_TERRAIN_TYPE_WHEEL);
            object_attr_setdisabled((t_object *)x, gensym("autozoom"), x->terrain_type != DADA_TERRAIN_TYPE_WHEEL);
            object_attr_setdisabled((t_object *)x, gensym("wheelmode"), x->terrain_type != DADA_TERRAIN_TYPE_WHEEL);
            object_attr_setdisabled((t_object *)x, gensym("buffers"), x->terrain_type != DADA_TERRAIN_TYPE_WHEEL);
            object_attr_setdisabled((t_object *)x, gensym("modulation"), x->terrain_type != DADA_TERRAIN_TYPE_WHEEL);
            object_attr_setdisabled((t_object *)x, gensym("eqp"), x->terrain_type != DADA_TERRAIN_TYPE_WHEEL);
            object_attr_setdisabled((t_object *)x, gensym("wheelfunction"), x->terrain_type != DADA_TERRAIN_TYPE_WHEEL);
            object_attr_setdisabled((t_object *)x, gensym("staticfunction"), x->terrain_type != DADA_TERRAIN_TYPE_EQUATION);
            terrain_iar(x);
        }
    }
    return jbox_notify((t_jbox *)x, s, msg, sender, data);
}

int C74_EXPORT main(void)
{
    common_symbols_init();
    
    llllobj_common_symbols_init();
    
    srand(time(NULL));
    
    if (dada_check_bach_version() || llllobj_test()) {
        dada_error_bachcheck();
        return 1;
    }

    t_class *c;

	c = class_new("dada.terrain~", (method)terrain_new, (method)terrain_free, sizeof(t_terrain), 0L, A_GIMME, 0);

	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
    jbox_initclass(c, JBOX_FONTATTR);	// include fonts
	class_dspinitjbox(c);

	class_addmethod(c, (method)terrain_dsp64,					"dsp64", A_CANT, 0);
	class_addmethod(c, (method)terrain_paint,					"paint",	A_CANT, 0);
	class_addmethod(c, (method)terrain_assist,                  "assist",		A_CANT, 0);
	class_addmethod(c, (method)terrain_acceptsdrag,	"acceptsdrag_unlocked", A_CANT, 0);
	class_addmethod(c, (method)terrain_acceptsdrag,	"acceptsdrag_locked", A_CANT, 0);
    class_addmethod(c, (method)terrain_notify,                  "bachnotify", A_CANT, 0);
    class_addmethod(c, (method)terrain_notify,                  "notify", A_CANT, 0);

    // @method autozoom @digest Set domain and range automatically
    // @description Adapts view and zoom automatically according to the current buffer positions (only for buffer wheel <m>type</m>).
    class_addmethod(c, (method)terrain_autozoom, "autozoom", 0);

    class_addmethod(c, (method)terrain_anything, "postvalue", A_GIMME, 0);
    class_addmethod(c, (method)terrain_anything, "anything", A_GIMME, 0);
    class_addmethod(c, (method)terrain_bang, "bang", 0);
    
    
    
    dadaobj_class_init(c, LLLL_OBJ_UIMSP, DADAOBJ_ZOOM | DADAOBJ_AXES | DADAOBJ_GRID | DADAOBJ_LABELS | DADAOBJ_EXPORTTOJITTER);

    
	CLASS_ATTR_DEFAULT(c,"patching_rect",0, "0. 0. 128. 128.");

    CLASS_STICKY_ATTR(c,"category",0,"Color");
    
    CLASS_ATTR_RGBA(c, "pathcolor", 0, t_terrain, j_path_color);
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "pathcolor", 0, "0. 0.0 0.5 1.");
    CLASS_ATTR_STYLE_LABEL(c, "pathcolor", 0, "rgba", "Path Color");
    CLASS_ATTR_BASIC(c, "pathcolor", 0);
    // @description Sets the color of the path.
    
    CLASS_STICKY_ATTR_CLEAR(c, "category");


    CLASS_STICKY_ATTR(c,"category",0,"Display");

    CLASS_ATTR_DOUBLE(c, "linewidth", 0, t_terrain, path_line_width);
    CLASS_ATTR_STYLE_LABEL(c, "linewidth", 0, "text", "Path Line Width");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"linewidth",0,"1");
    // @description Sets the path line width in pixels

    CLASS_ATTR_DOUBLE(c, "interval", 0, t_terrain, redraw_time_ms);
    CLASS_ATTR_STYLE_LABEL(c, "interval", 0, "text", "Redraw Time In Milliseconds");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"interval",0,"100");
    // @description Sets the redraw time in milliseconds.
    
    CLASS_ATTR_LONG(c, "numpoints", 0, t_terrain, path_max_points);
    CLASS_ATTR_STYLE_LABEL(c, "numpoints", 0, "text", "Number Of Path Points");
    CLASS_ATTR_FILTER_CLIP(c, "numpoints", 0, DADA_TERRAIN_MAX_NUM_PATH_PT);
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"numpoints",0,"50");
    // @description Sets the number of path points
    
    
    CLASS_ATTR_CHAR(c, "showbuffers", 0, t_terrain, show_buffers);
    CLASS_ATTR_STYLE_LABEL(c, "showbuffers", 0, "onoff", "Show Buffer Arrows");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showbuffers",0,"1");
    // @description Toggles the display of buffer arrows.

    CLASS_ATTR_CHAR(c, "shownames", 0, t_terrain, show_names);
    CLASS_ATTR_STYLE_LABEL(c, "shownames", 0, "onoff", "Show Buffer Names");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"shownames",0,"1");
    // @description Toggles the display of buffer names.

    CLASS_ATTR_CHAR(c, "showterrain", 0, t_terrain, show_terrain);
    CLASS_ATTR_STYLE_LABEL(c, "showterrain", 0, "onoff", "Show Terrain");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showterrain",0,"1");
    // @description Toggles the display of the terrain.

    
    CLASS_ATTR_CHAR(c, "pathmode", 0, t_terrain, path_mode);
    CLASS_ATTR_STYLE_LABEL(c, "pathmode", 0, "enumindex", "Path Mode");
    CLASS_ATTR_ENUMINDEX(c,"pathmode", 0, "Points Lines");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"pathmode",0,"1");
    // @description Choose the display mode for the path

    
    CLASS_STICKY_ATTR_CLEAR(c, "category");

    
    
    CLASS_STICKY_ATTR(c,"category",0,"Settings");

    CLASS_ATTR_CHAR(c, "type", 0, t_terrain, terrain_type);
    CLASS_ATTR_STYLE_LABEL(c, "type", 0, "enumindex", "Terrain Type");
    CLASS_ATTR_ENUMINDEX(c,"type", 0, "Static Equation Buffer Wheel");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"type",0,"1");
    CLASS_ATTR_BASIC(c, "type", 0);
    // @description If non-zero, the input is interpreted as polar coordinates (radius, angle: default);
    // otherwise as cartesian coordinates (x, y)

    CLASS_ATTR_CHAR(c, "polar", 0, t_terrain, polar);
    CLASS_ATTR_STYLE_LABEL(c, "polar", 0, "onoff", "Polar Input");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"polar",0,"1");
    CLASS_ATTR_BASIC(c, "polar", 0);
    // @description If non-zero, the input is interpreted as polar coordinates (radius, angle: default);
    // otherwise as cartesian coordinates (x, y)

    
    CLASS_ATTR_CHAR(c, "autozoomwhenupdated", 0, t_terrain, autozoom);
    CLASS_ATTR_STYLE_LABEL(c, "autozoomwhenupdated", 0, "onoff", "Auto Zoom When Updated");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"autozoomwhenupdated",0,"1");
    // @description Toggles the ability to zoom automatically when the buffers are changed (for buffer wheel <m>type</m> only).
    
    CLASS_ATTR_CHAR(c, "wheelmode", 0, t_terrain, mode);
    CLASS_ATTR_STYLE_LABEL(c, "wheelmode", 0, "enumindex", "Wheel Combination Mode");
    CLASS_ATTR_ENUMINDEX(c,"wheelmode", 0, "Additive Multiplicative");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"wheelmode",0,"1");
    // @description Choose combination mode for wave functions (for buffer wheel <m>type</m> only).
    
    CLASS_ATTR_LLLL(c, "buffers", 0, t_terrain, buffers_as_llll, terrain_getattr_buffers, terrain_setattr_buffers);
    CLASS_ATTR_STYLE_LABEL(c,"buffers",0,"text_large","Buffers And Angles");
    CLASS_ATTR_BASIC(c, "buffers", 0);
    CLASS_ATTR_SAVE(c, "buffers", 0);
    // @description Sets the buffer names and the buffer angles (for buffer wheel <m>type</m> only).
    // Syntax is expected to be: <b>[<m>name1</m> <m>angle1</m>] [<m>name2</m> <m>angle2</m>]...</b>,
    // where <m>name</m> is a symbol identifying the buffer names, and <m>angle</m> is its angle in the buffer wheel,
    // in radians. You can append the degrees ° symbol after the number (without any spaces) or substitute the angle with
    // <b>[<m>angleindeg</m> deg]</b> if you want to define an angle in degrees.

    CLASS_ATTR_SYM(c, "wheelfunction", 0, t_terrain, terrain_wheel_code);
    CLASS_ATTR_STYLE_LABEL(c, "wheelfunction", 0, "text_large", "Wheel Function Code");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"wheelfunction",0,"");
    CLASS_ATTR_ACCESSORS(c,	"wheelfunction",	NULL, terrain_setattr_wheelfunction);
    // @description Sets a custom function for computation of wave-terrain samples (for buffer wheel <m>type</m> only).

    CLASS_ATTR_SYM(c, "staticfunction", 0, t_terrain, terrain_static_code);
    CLASS_ATTR_STYLE_LABEL(c, "staticfunction", 0, "text_large", "Static Function Code");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"staticfunction",0,"\"return sin(2*PI*x/100.)*cos(2*PI*y/100.);\"");
    CLASS_ATTR_ACCESSORS(c,	"staticfunction",	NULL, terrain_setattr_staticfunction);
    // @description Sets a custom function for the wave terrain (for static equation <m>type</m> only).

    CLASS_ATTR_DOUBLE(c, "modulation", 0, t_terrain, modulation_amount);
    CLASS_ATTR_STYLE_LABEL(c, "modulation", 0, "text", "Modulation Amount");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"modulation",0,"0");
    // @description Sets the amount of frequency modulation between neighboring buffers.

    CLASS_ATTR_CHAR(c, "eqp", 0, t_terrain, equal_power);
    CLASS_ATTR_STYLE_LABEL(c, "eqp", 0, "onoff", "Equal Power Interpolation");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"eqp",0,"1");
    // @description Toggles equal-power interpolation.

    

    CLASS_ATTR_CHAR(c, "debug", 0, t_terrain, debug);
    CLASS_ATTR_STYLE_LABEL(c, "debug", 0, "onoff", "Debug");
    CLASS_ATTR_INVISIBLE(c, "debug", ATTR_GET_OPAQUE | ATTR_SET_OPAQUE);
    // @exclude all

    CLASS_ATTR_CHAR(c, "dspdebug", 0, t_terrain, dsp_debug);
    CLASS_ATTR_STYLE_LABEL(c, "dspdebug", 0, "onoff", "DSP Debug");
    CLASS_ATTR_INVISIBLE(c, "dspdebug", ATTR_GET_OPAQUE | ATTR_SET_OPAQUE);
    // @exclude all

    CLASS_STICKY_ATTR_CLEAR(c, "category");

    


    
	class_register(CLASS_BOX, c);
	s_terrain_class = c;
}


void *terrain_new(t_symbol *s, long argc, t_atom *argv)
{
	t_terrain *x = NULL;
	t_dictionary *d=NULL;
	long boxflags;
    
	if (!(d=object_dictionaryarg(argc,argv)))
		return NULL;

    if ((x = (t_terrain *)object_alloc_debug(s_terrain_class))) {
        boxflags = 0
        | JBOX_DRAWFIRSTIN
        | JBOX_NODRAWBOX
        | JBOX_DRAWINLAST
        | JBOX_TRANSPARENT
        //		| JBOX_NOGROW
        //		| JBOX_GROWY
        | JBOX_GROWBOTH
        //		| JBOX_HILITE
        //		| JBOX_BACKGROUND
        //		| JBOX_DRAWBACKGROUND
        //		| JBOX_NOFLOATINSPECTOR
        //		| JBOX_TEXTFIELD
        //		| JBOX_MOUSEDRAGDELTA
        //		| JBOX_TEXTFIELD
        ;
        
        x->autozoom = 1;
        x->num_out_channels = 1;
        x->buffers_as_llll = llll_get();
        x->path_num_points = 0;
        x->startclock = false;

        jbox_new((t_jbox *)x, boxflags, argc, argv);
        x->b_ob.r_ob.l_ob.z_box.b_firstin = (t_object *)x;
        dsp_setupjbox((t_pxjbox *)x, 2);
        
        char outlets_buf[256];
        long i;
        for (i = 0; i < 255 && i < x->num_out_channels; i++)
            outlets_buf[i] = 's';
        outlets_buf[i] = 0;
        
        dadaobj_pxjbox_setup((t_dadaobj_pxjbox *)x, DADAOBJ_ZOOM | DADAOBJ_AXES | DADAOBJ_GRID, build_pt(1., 1.), -1, -1, -1, (dada_paint_ext_fn)terrain_paint_ext, (invalidate_and_redraw_fn)terrain_iar, "", 0, outlets_buf);
        x->b_ob.d_ob.m_zoom.max_zoom_perc = build_pt(100000, 100000);
        //    dadaobj_addfunctions(dadaobj_cast(x), (dada_mousemove_fn)terrain_mousemove, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
        
        x->clock = clock_new(x,(method)terrain_tick);
        x->refresh_buffers_qelem = qelem_new_debug(x, (method) terrain_refresh_buffers_qelem_do);
        x->clang_wheel = (t_object *)object_new(CLASS_NOBOX, gensym("clang"), gensym("dadaterrain"));
        x->clang_static = (t_object *)object_new(CLASS_NOBOX, gensym("clang"), gensym("dadaterrain"));

        attr_dictionary_process(x,d);
        
        jbox_ready((t_jbox *)x);
        
        dadaobj_set_current_version_number(dadaobj_cast(x));

        return x;
    }
    
    return NULL;
}


void terrain_free(t_terrain *x)
{
    object_free_debug(x->clang_wheel);
    object_free_debug(x->clang_static);
    
    qelem_free(x->refresh_buffers_qelem);
    
    freeobject((t_object *)x->clock);
    
    terrain_free_buffer_refs(x, 0, x->num_buffers - 1);
    
    if (x->terrain)
        jgraphics_surface_destroy(x->terrain);
	
    dsp_freejbox((t_pxjbox *)x);
    dadaobj_pxjbox_free((t_dadaobj_pxjbox *)x);
}


void terrain_assist(t_terrain *x, void *b, long m, long a, char *s)
{
    if (m == ASSIST_INLET) 	{
        if (a == 0)
            sprintf(s, "(signal) Radius");
        else
            sprintf(s, "(signal) Angle");
    } else
        sprintf(s, "(signal) Audio Output");
}


void terrain_set_custom_wheelfunction(t_terrain *x, t_symbol *code)
{
    t_atom ret, fun, str;
    t_object *string;
    
    if (!code || strlen(code->s_name) == 0) {
//        object_error((t_object *)x, "No custom rule defined!");
        x->terrain_wheel_fn = NULL;
        return;
    }

    if (strlen(code->s_name) == 0) {
        x->terrain_wheel_fn = NULL;
        return;
    }

    // Set rule, by appending
    long size = strlen(code->s_name) + 2000;
    char *buf = (char *)bach_newptr(size * sizeof(char)); // buf + 100
    
    snprintf_zero(buf, size, "%s \n"
                  "double terrain_custom_wheelfunction(double sample, double factor, double rho, double theta); \n"
                  "double terrain_custom_wheelfunction(double sample, double factor, double rho, double theta) { \n"
                  "%s \n"
                  "}", dada_get_default_include(), code->s_name);
    
    // recreate clang object
    object_free(x->clang_wheel);
    x->clang_wheel = (t_object *)object_new(CLASS_NOBOX, gensym("clang"), gensym("dadaterrain"));
    
    object_method(x->clang_wheel, gensym("include_standard_headers"));

    /*
    t_symbol *ps_addsymbol = gensym("addsymbol");
    object_method(x->clang_wheel, ps_addsymbol, gensym("acosh"), &acosh);
    object_method(x->clang_wheel, ps_addsymbol, gensym("asinh"), &asinh);
    object_method(x->clang_wheel, ps_addsymbol, gensym("atanh"), &atanh);
    object_method(x->clang_wheel, ps_addsymbol, gensym("modf"), &modf);
    object_method(x->clang_wheel, ps_addsymbol, gensym("hypot"), &hypot);
    object_method(x->clang_wheel, ps_addsymbol, gensym("trunc"), &trunc);
    object_method(x->clang_wheel, ps_addsymbol, gensym("round"), &round);
    */
    
    // make a new string object (alternative to symbol that avoids post)
    string = (t_object *)object_new(CLASS_NOBOX, gensym("string"), buf);
    atom_setobj(&str, string);
    
    // compile the string
    object_method_typed(x->clang_wheel, gensym("compile"), 1, &str, &ret);
    
    // obtain the function (executable code)
    object_method_sym(x->clang_wheel, gensym("getfunction"), gensym("terrain_custom_wheelfunction"), &fun);
    
    // get the function pointer
    
    dadaobj_mutex_lock(dadaobj_cast(x));
    x->terrain_wheel_fn = (terrain_wheel_fn)atom_getobj(&fun);
    
    // must check that there is code, otherwise there was a compile error
    if (!x->terrain_wheel_fn)
        object_error((t_object *)x, "Syntax error in custom function!");
    else {
        // test arccosine
/*        for (long i = 0; i < 360; i++) {
            post("angle: %d°, result: %.2f", i, (x->terrain_wheel_fn)(deg2rad(i), 0., 0.));
        }
 */
    }
    dadaobj_mutex_unlock(dadaobj_cast(x));

    bach_freeptr(buf);
    
    // Destroy the string (but not the clang: we need the compiled function!)
    object_free(string);
}


void terrain_set_custom_staticfunction(t_terrain *x, t_symbol *code)
{
    t_atom ret, fun, str;
    t_object *string;
    
    if (!code || strlen(code->s_name) == 0) {
        object_error((t_object *)x, "No custom rule defined!");
        return;
    }
    
    if (strlen(code->s_name) == 0) {
        x->terrain_wheel_fn = NULL;
        return;
    }
    
    // Set rule, by appending
    long size = strlen(code->s_name) + 2000;
    char *buf = (char *)bach_newptr(size * sizeof(char)); // buf + 100
    snprintf_zero(buf, size, "%s \n"
                  "double terrain_custom_staticfunction(double x, double y, double rho, double theta); \n"
                  "double terrain_custom_staticfunction(double x, double y, double rho, double theta) { \n"
                  "%s \n"
                  "}", dada_get_default_include(), code->s_name);
    
    // recreate clang object
    object_free(x->clang_static);
    x->clang_static = (t_object *)object_new(CLASS_NOBOX, gensym("clang"), gensym("dadaterrain"));
    
    object_method(x->clang_static, gensym("include_standard_headers"));
    
    // make a new string object (alternative to symbol that avoids post)
    string = (t_object *)object_new(CLASS_NOBOX, gensym("string"), buf);
    atom_setobj(&str, string);
    
    // compile the string
    object_method_typed(x->clang_static, gensym("compile"), 1, &str, &ret);
    
    // obtain the function (executable code)
    object_method_sym(x->clang_static, gensym("getfunction"), gensym("terrain_custom_staticfunction"), &fun);
    
    // get the function pointer
    
    dadaobj_mutex_lock(dadaobj_cast(x));
    x->terrain_static_fn = (terrain_static_fn)atom_getobj(&fun);
    
    // must check that there is code, otherwise there was a compile error
    if (!x->terrain_static_fn)
        object_error((t_object *)x, "Syntax error in custom function!");
    else {
        // test arccosine
        /*        for (long i = 0; i < 360; i++) {
         post("angle: %d°, result: %.2f", i, (x->terrain_wheel_fn)(deg2rad(i), 0., 0.));
         }
         */
    }
    dadaobj_mutex_unlock(dadaobj_cast(x));
    
    bach_freeptr(buf);
    
    // Destroy the string (but not the clang: we need the compiled function!)
    object_free(string);
}

void terrain_bang(t_terrain *x)
{
    terrain_iar(x);
}

t_max_err terrain_setattr_wheelfunction(t_terrain *x, void *attr, long argc, t_atom *argv)
{
    if (!sys_getdspstate()) {
        if (argc) {
            t_symbol *code = atom_getsym(argv);
            if (code != _llllobj_sym_none) {
                // SHOULD NEVER BE DONE WITH DSP ON!!!!
                terrain_set_custom_wheelfunction(x, code);
                x->terrain_wheel_code = code;
            } else {
                x->terrain_wheel_fn = NULL;
                x->terrain_wheel_code = _llllobj_sym_none;
            }
        } else {
            x->terrain_wheel_fn = NULL;
            x->terrain_wheel_code = _llllobj_sym_none;
        }
    } else {
        object_error((t_object *)x, "Can't change function while DSP is on!");
    }
    return MAX_ERR_NONE;
}


t_max_err terrain_setattr_staticfunction(t_terrain *x, void *attr, long argc, t_atom *argv)
{
    if (!sys_getdspstate()) {
        if (argc) {
            t_symbol *code = atom_getsym(argv);
            if (code != _llllobj_sym_none) {
                // SHOULD NEVER BE DONE WITH DSP ON!!!!
                terrain_set_custom_staticfunction(x, code);
                x->terrain_static_code = code;
            } else {
                x->terrain_static_fn = NULL;
                x->terrain_static_code = _llllobj_sym_none;
            }
        } else {
            x->terrain_static_fn = NULL;
            x->terrain_static_code = _llllobj_sym_none;
        }
    } else {
        object_error((t_object *)x, "Can't change function while DSP is on!");
    }
    return MAX_ERR_NONE;
}


double terrain_get_buffer_length_ms(t_terrain *x, long idx)
{
    return (x->buffer_info[idx].b_frames * 1000.) / x->buffer_info[idx].b_sr;
}


double terrain_get_sample_from_buffer(t_terrain *x, long buf_idx, double sample, long channel)
{
//    terrain_dev_post("sample: %.2f", sample);
    
    long num_frames = x->buffer_info[buf_idx].b_frames;
    t_object *buffer = buffer_ref_getobject(x->buffer_reference[buf_idx]);
    double res = 0;
    
    if (!buffer)
        return 0;
    
    if (sample < 0 || sample > num_frames) {
       return 0;
        // TO DO: interpolate between -1 and 0, and b_frames
    }
    
    t_float *tab = buffer_locksamples(buffer);

    if (!tab) return 0;
    
    long nc = buffer_getchannelcount(buffer);
    
    if (nc <= 0) return 0;
    
    long below_idx = CLAMP((long)sample, 0, num_frames - 1); // TO DO: no need for CLAMP?
    long above_idx = (below_idx < num_frames * nc - 1) ? below_idx + 1 : below_idx;
    
#ifdef DADA_TERRAIN_DEBUG
    if (x->debug) {
        long num_frames_check = buffer_getframecount(buffer);
        if (above_idx >= num_frames_check * nc) {
            long foo = 7;
            foo ++;
            object_error((t_object *)x, "Error!!!");
        }
        if (above_idx >= num_frames * nc) {
            long foo = 7;
            foo ++;
            object_error((t_object *)x, "Error!!!");
        }
    }
#endif
    
    t_float below = tab[below_idx * nc + channel];
    t_float above = tab[above_idx * nc + channel];
    res = ((double)below) + (((double)above) - ((double)below))*fmod(sample, 1.);

    buffer_unlocksamples(buffer);

    return res;
}

double terrain_get_sample_from_buffer_ms(t_terrain *x, long buf_idx, double ms, long channel)
{
    return terrain_get_sample_from_buffer(x, buf_idx, ms * x->buffer_info[buf_idx].b_sr / 1000., channel);
}

char is_angle_between(double *angle, double *below, double *above)
{
    while (*below >= *above)
        *above += TWOPI;

    while (*angle >= *above)
        *angle -= TWOPI;

    while (true) {
        if (*angle >= *below)
            return (*angle <= *above);
        
        *angle += TWOPI;
    }
    
    return 0;
}

t_polar_pt terrain_cartopol(t_pt pt)
{
    t_polar_pt polar;
    polar.rho = sqrt(pt.x*pt.x + pt.y*pt.y);
    polar.theta = atan2(pt.y, pt.x);
    return polar;
}

t_pt terrain_poltocar(t_polar_pt polar)
{
    t_pt pt;
    pt.x = polar.rho * cos(polar.theta);
    pt.y = polar.rho * sin(polar.theta);
    return pt;
}


void cartopol(double x, double y, double *rho, double *theta)
{
    *rho = sqrt(x*x + y*y);
    *theta = atan2(y, x);
}

void poltocar(double rho, double theta, double *x, double *y)
{
    *x = rho * cos(theta);
    *y = rho * sin(theta);
}


double terrain_get_sample_rhotheta(t_terrain *x, double rho, double theta, long channel)
{
    if (x->terrain_type == DADA_TERRAIN_TYPE_EQUATION) {
        if (x->terrain_static_fn) {
            double x_val, y_val, res;
            poltocar(rho, theta, &x_val, &y_val);
            res = (x->terrain_static_fn)(x_val, y_val, rho, theta);
            return res;
        } else {
            return 0.;
        }
    }
    
    char mode = x->mode;
    double res = (mode == DADA_TERRAIN_MODE_MULTIPLICATIVE ? 1 : 0);
    long num_bufs = x->num_buffers;
    double modulation_amount = x->modulation_amount;
    char equal_power = x->equal_power;
    double sample, factor, contribution;
    
    if (num_bufs <= 0)
        return 0;
    
    if (num_bufs == 1) {
        double sample = terrain_get_sample_from_buffer_ms(x, 0, terrain_display_to_ms(x, rho), channel);
        if (x->terrain_wheel_fn) {
            contribution = (x->terrain_wheel_fn)(sample, 1., rho, theta);
        } else {
            contribution = sample;
        }
        terrain_dev_post(" · contribution for buffer 0: %.2f (sample: %.4f, factor: %.2f)", contribution, sample, 1.);
        return contribution;
    }
    
    
    long i, h, j;
    double bai, bah, baj; // buffer angles
    double this_theta;
    for (i = 0; i < num_bufs; i++) {
        h = (i == 0 ? num_bufs - 1 : i - 1);
        j = (i == num_bufs - 1 ? 0 : i + 1);
        bai = x->buffer_angle[i];
        bah = x->buffer_angle[h];
        baj = x->buffer_angle[j];
        this_theta = theta;
        if (bai != bah && bai != baj) {
            if (is_angle_between(&this_theta, &bah, &baj)) {     // theta must be between bah and baj; contribution is 0 outside
                
                while (bai < bah) bai += TWOPI;
                
                // now we have 0 < bah < bai < baj.
                // And bah < theta < baj. But where is theta w.r. to bai?
                char side = (this_theta <= bai ? -1 : 1);
                
                // This factor will be 0 when theta = bah or baj, and 1 when theta = bai
                if (equal_power) {
                    // not really equal_power, ok, but it works quite well - quadratic factor
                    factor = ((this_theta - bah)*(baj - this_theta))/((bai - bah)*(baj - bai));
                    if (DADA_TERRAIN_MODE_MULTIPLICATIVE)
                        factor = pow(factor, 0.3); // empirical, I admit that...
                } else {
                    // linear factor
                    factor = (side < 0) ? (this_theta - bah)/(bai - bah) : (baj - this_theta)/(baj - bai);
                }
                
                // We compute the sample, depending on the modulation amount
                if (modulation_amount == 0) {
                    sample = terrain_get_sample_from_buffer_ms(x, i, terrain_display_to_ms(x, rho), channel);
                } else {
                    double modul_sample = terrain_get_sample_from_buffer_ms(x, side < 0 ? h : j, rho, channel);
                    double delta = (1 - factor) * modulation_amount * modul_sample;
                    sample = terrain_get_sample_from_buffer_ms(x, i, terrain_display_to_ms(x, rho) + delta, channel);
                }
                
                
                if (x->terrain_wheel_fn) {
                    contribution = (x->terrain_wheel_fn)(sample, factor, rho, theta);
                } else {
                    switch (mode) {
                        case DADA_TERRAIN_MODE_MULTIPLICATIVE:
                            contribution = cos(factor * acos(sample));
                            break;
                            
                        default:
                            contribution = factor * sample;
                            break;
                    }
                }
                terrain_dev_post(" · contribution for buffer %ld: %.2f (sample: %.4f, factor: %.2f)", i, contribution, sample, factor);
                
                if (mode == DADA_TERRAIN_MODE_MULTIPLICATIVE)
                    res *= contribution;
                else
                    res += contribution;
            }
        }
    }
    
    terrain_dev_post(" – result: %.6f", res);

    return res;
}



double terrain_get_sample_xy(t_terrain *x, double x_val, double y_val, long channel)
{
    if (x->terrain_type == DADA_TERRAIN_TYPE_EQUATION) {
        if (x->terrain_static_fn) {
            double rho, theta;
            cartopol(x_val, y_val, &rho, &theta);
            return (x->terrain_static_fn)(x_val, y_val, rho, theta);
        } else {
            return 0.;
        }
    }

    double rho, theta;
    cartopol(x_val, y_val, &rho, &theta);
    terrain_dev_post("x = %.2f, y = %.2f, rho = %.2f, theta = %.2f", x_val, y_val, rho, theta);
    return terrain_get_sample_rhotheta(x, rho, theta, channel);
}

t_jrgba terrain_long_to_color(long l)
{
    switch (l % 5) {
        case 1:
            return build_jrgba(0.603516, 1., 0.125, 1.);
            break;

        case 2:
            return build_jrgba(0.898438, 1., 0.1875, 1.);
            break;

        case 3:
            return build_jrgba(0.0625, 0.956055, 1., 1.);
            break;

        case 4:
            return build_jrgba(1., 0.625, 0.923828, 1.);
            break;
            
            
        default:
            return build_jrgba(1., 0.870117, 0.5625, 1.); //0.972656, 1., 0.125, 1.);
            break;
    }
}

void terrain_paint_buffers(t_terrain *x, t_object *view, t_rect *rect, t_dada_force_graphics *force_graphics)
{
    t_dadaobj *r_ob = dadaobj_cast(x);
    t_pt center = view ? get_center_pix(r_ob, view, rect) : force_graphics->center_pix;
    double width = view ? rect->width : force_graphics->rect.width, height = view ? rect->height : force_graphics->rect.height;
    
    t_jgraphics *g = view ? jbox_start_layer((t_object *)x, view, gensym("buffers"), width, height) : force_graphics->graphic_context;
    if (g) {

        // paint buffer arrows and name
        if (x->show_names) {
            t_jfont *jf = jfont_create_debug(jbox_get_fontname((t_object *)x)->s_name, (t_jgraphics_font_slant)jbox_get_font_slant((t_object *)x), (t_jgraphics_font_weight)jbox_get_font_weight((t_object *)x), jbox_get_fontsize((t_object *)x));
            long i;
            for (i = 0; i < x->num_buffers; i++) {
                double angle = positive_fmod(x->buffer_angle[i], TWOPI);
                double length_ms = terrain_get_buffer_length_ms(x, i);
                double length_coord = terrain_ms_to_display(x, length_ms);
                t_pt delta_px = delta_coord_to_delta_pix(r_ob, build_pt(length_coord, length_coord));
                t_jrgba color = terrain_long_to_color(i);
                t_pt tip = build_pt(center.x + delta_px.x * cos(angle), center.y + delta_px.y * sin(angle));
                
                if (x->show_buffers)
                    paint_arrow(g, color, center.x, center.y, tip.x, tip.y, 2, 6, 6);
                
                t_jsurface *names_surface = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, width, height);

                if (x->show_names) {
                    double text_width, text_height;
                    char ordinary = (angle < PIOVERTWO || angle > 3*PIOVERTWO);
                    double rotation_angle = ordinary ? angle : angle + PI;
                    double pad = 2 * jbox_get_fontsize((t_object *)x);
                    t_jgraphics *gt = jgraphics_create(names_surface);
                    
                    jgraphics_translate(gt, center.x, center.y);
                    jgraphics_rotate(gt, -rotation_angle);
                    
                    jfont_text_measure(jf, x->buffer_info[i].b_name ? x->buffer_info[i].b_name->s_name : "???", &text_width, &text_height);
                    write_text_simple(gt, jf, color, x->buffer_info[i].b_name ? x->buffer_info[i].b_name->s_name : "???", ordinary ? pad : -text_width - pad, -text_height, width, height);

                    jgraphics_rotate(gt, rotation_angle);
                    jgraphics_translate(gt, -center.x, -center.y);
                }
                
                t_rect rect_ok = build_rect(0, 0, width, height);
                jgraphics_image_surface_draw(g, names_surface, rect_ok, rect_ok);
            }
            jfont_destroy(jf);
        }
        
        if (view)
            jbox_end_layer((t_object *)x, view, gensym("buffers"));
    }
    
    
    if (view)
        jbox_paint_layer((t_object *)x, view, gensym("buffers"), 0., 0.);	// position of the layer
}

void terrain_paint_terrain(t_terrain *x, t_object *view, t_rect *rect, t_dada_force_graphics *force_graphics)
{
    t_dadaobj *r_ob = dadaobj_cast(x);
    t_pt center = view ? get_center_pix(r_ob, view, rect) : force_graphics->center_pix;
    double width = view ? rect->width : force_graphics->rect.width, height = view ? rect->height : force_graphics->rect.height;
    
    t_jgraphics *g = view ? jbox_start_layer((t_object *)x, view, gensym("terrain"), width, height) : force_graphics->graphic_context;

    if (g) {
        long i, j;
        t_pt this_coord;
        double this_val, c;
        
        if (view && x->must_autozoom && x->terrain_type == DADA_TERRAIN_TYPE_WHEEL) {
            r_ob->m_paint.dont_repaint = true;
            terrain_autozoom_do(x, view, false);
            r_ob->m_paint.dont_repaint = false;
            center = get_center_pix(r_ob, view, rect);
            x->must_autozoom = false;
        }
        
        if (x->show_terrain) {
            jgraphics_surface_destroy(x->terrain);
            x->terrain = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, width, height);
            
            for (i = 0; i < width; i++) {
                for (j = 0; j < height; j++) {
                    this_coord = pix_to_coord(r_ob, center, build_pt(i, j));
                    this_val = terrain_get_sample_xy(x, this_coord.x, this_coord.y, 0);
                    terrain_dev_post("%.6f", this_val);
                    c = CLAMP((this_val+1)*0.5, 0., 1.);
                    jgraphics_image_surface_set_pixel(x->terrain, i, j, build_jrgba(c, c, c, 1));
                }
            }
            
            t_rect rect_ok = build_rect(0, 0, width, height);
            jgraphics_image_surface_draw(g, x->terrain, rect_ok, rect_ok); // draw fast apparently doesn't work on retina display
        }
        
        if (view)
            jbox_end_layer((t_object *)x, view, gensym("terrain"));
    }
    
    if (view)
        jbox_paint_layer((t_object *)x, view, gensym("terrain"), 0., 0.);	// position of the layer
}


void terrain_autozoom_do(t_terrain *x, t_object *view, char also_lock_mutex)
{
    t_rect rect;
    t_dadaobj *d_ob = dadaobj_cast(x);
    jbox_get_rect_for_view((t_object *)x, view, &rect);
    //	center = get_center_pix(dadaobj_cast(x), view, &rect);
    
    
    if (x->num_buffers <= 0)
        return;
    
    if (also_lock_mutex)
        dadaobj_mutex_lock(d_ob);
    
    // Initialize
    double max_radius_ms = 0;
    long i;
    for (i = 0; i < x->num_buffers; i++) {
        double this_radius_ms = terrain_get_buffer_length_ms(x, i);
        if (this_radius_ms > max_radius_ms)
            max_radius_ms = this_radius_ms;
    }

    if (max_radius_ms == 0)
        max_radius_ms = 1000;
    
    // adding pad
    max_radius_ms *= 1.05;
    
    if (also_lock_mutex)
        dadaobj_mutex_unlock(d_ob);
    
    double max_radius_px = terrain_ms_to_display(x, max_radius_ms);
    double zoom = (100.*MIN(rect.width, rect.height)/max_radius_px)/2.;
    dadaobj_setzoom(d_ob, build_pt(zoom, zoom));
}


void terrain_autozoom(t_terrain *x)
{
    terrain_autozoom_do(x, jpatcher_get_firstview((t_object *)gensym("#P")->s_thing), true);
}

void terrain_paint_ext(t_terrain *x, t_object *patcherview, t_dada_force_graphics *force_graphics)
{
    t_dadaobj *r_ob = dadaobj_cast(x);
    long i;
	t_rect rect = force_graphics->rect;
    t_jgraphics *g = force_graphics->graphic_context; // obtain graphics context
    t_pt center = force_graphics->center_pix;

    dadaobj_paint_background(r_ob, g, &rect);
    
    dadaobj_mutex_lock(r_ob);
    terrain_paint_terrain(x, patcherview, &rect, force_graphics);
    dadaobj_mutex_unlock(r_ob);
    
    dadaobj_paint_grid(r_ob, patcherview, force_graphics);
    
    dadaobj_mutex_lock(r_ob);
    if (x->terrain_type == DADA_TERRAIN_TYPE_WHEEL)
        terrain_paint_buffers(x, patcherview, &rect, force_graphics);
    dadaobj_mutex_unlock(r_ob);
    
    long max_path_pts = x->path_max_points;
    long curr_idx = x->path_curr_idx % DADA_TERRAIN_MAX_NUM_PATH_PT;
    long path_num_points = x->path_num_points;
    char path_mode = x->path_mode;
    long count = 0;
    if (max_path_pts > 0 && path_num_points > 0) { // Paint path points
        long start_idx = curr_idx - MIN(path_num_points, max_path_pts);
        if (start_idx < 0) start_idx += DADA_TERRAIN_MAX_NUM_PATH_PT;
        t_pt pt = coord_to_pix(r_ob, center, x->path[start_idx]);
        if (isnan(pt.x) || isnan(pt.y))
            pt = build_pt(0, 0);
        jgraphics_set_source_jrgba(g, &x->j_path_color);
        jgraphics_set_line_width(g, x->path_line_width);
        
        if (path_mode == DADA_TERRAIN_PATH_MODE_LINES)
            jgraphics_move_to(g, pt.x, pt.y);
        else
            paint_circle_filled(g, x->j_path_color, pt.x, pt.y, x->path_line_width*2);
        
        for (i = start_idx, count = 0; count < path_num_points; count++) {
            if (i == curr_idx)
                break;
            t_pt this_pt = coord_to_pix(r_ob, center, x->path[i]);
            
            if (!isnan(this_pt.x) && !isnan(this_pt.y)) {
                if (path_mode == DADA_TERRAIN_PATH_MODE_LINES)
                    jgraphics_line_to(g, this_pt.x, this_pt.y);
                else
                    paint_circle_filled(g, x->j_path_color, this_pt.x, this_pt.y, x->path_line_width*2);
            }
            
            i++;
            if (i == DADA_TERRAIN_MAX_NUM_PATH_PT)
                i = 0;
        }
        if (path_mode == DADA_TERRAIN_PATH_MODE_LINES)
            jgraphics_stroke(g);
    }
    
    dadaobj_paint_border(r_ob, g, &rect);
}

void terrain_paint(t_terrain *x, t_object *patcherview)
{
    dadaobj_paint(dadaobj_cast(x), patcherview);
}


t_atom_long terrain_acceptsdrag(t_terrain *x, t_object *drag, t_object *view)
{
/*    if (jdrag_matchdragrole(drag, gensym("imagefile"), 0) && x->b_ob.d_ob.flags & DADAOBJ_BGIMAGE) {
        jdrag_box_add(drag, (t_object *)x, gensym("bgimage"));
        return true;
    } */
    return false;
}

void terrain_redraw_do(t_terrain *x, t_symbol *msg, long ac, t_atom *av)
{
    jbox_redraw((t_jbox *)x);
}

void terrain_post_array_do(t_terrain *x, t_symbol *msg, long ac, t_atom *av)
{
    long size;
    char *text = NULL;
    atom_gettext(ac, av, &size, &text, 0);
    post("%s", text);
    sysmem_freeptr(text);
}

void terrain_post_array(t_terrain *x, long num_elems, double *elems)
{
#ifdef DADA_TERRAIN_DEBUG
    if (x->dsp_debug) {
        t_atom a[num_elems];
        long i;
        for (i = 0; i < num_elems; i++)
            atom_setfloat(a+i, elems[i]);
        defer_low(x, (method)terrain_post_array_do, NULL, num_elems, a);
    }
#endif
}


void terrain_perform64(t_terrain *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    int			i, n = sampleframes;
    char        polar = x->polar;
    long		index, chan, frames, nc;
    double      sample;
    
    if (numins < 2 || numouts < 1)
        goto zero;

    
    // TO DO: buffer_locksamples might be called here just once for all buffers, instead of having it
    // called inside terrain_get_sample_rhotheta()
    for (i = 0; i < numouts; i++) {
        t_double	*out = outs[i];
        t_double	*in0 = ins[0];
        t_double	*in1 = ins[1];

        // setting new path point
        long idx = rand() % sampleframes; // to avoid aliasing
        x->curr_pt.rho = in0[idx];
        x->curr_pt.theta = in1[idx];

        // calculating values
        n = sampleframes;
        if (polar) {
            while (n--) {
                /// interpolare tra sample i-1 e i di 4 punti (cioè ne aggiungo 3)
                /// quindi sovracampiono di fattore 4, quindi poi farò un passabasso calcolato a 16kHz/4 ~ 4kHz perché poi ritirerò su di un fattore 4
                /// e poi uso [filterdesign] per calcolare i coefficienti biquad del filtro.
                // la finestra deve ovviamente scorrere, e poi prendo sempre il primo o ultimo elemento (ma sempre lo stesso).
                sample = terrain_get_sample_rhotheta(x, *in0++, *in1++, i);
                FIX_DENORM_NAN_DOUBLE(sample);
                *out++ = sample;
            }
        } else {
            while (n--) {
                sample = terrain_get_sample_xy(x, *in0++, *in1++, i);
                FIX_DENORM_NAN_DOUBLE(sample);
                *out++ = sample;
            }
        }
        terrain_post_array(x, sampleframes, ins[0]);
        terrain_post_array(x, sampleframes, outs[0]);
    }
    
    if (x->startclock) {
        x->startclock = 0;
        clock_delay(x->clock, 0);
    }

    
    return;
    
zero: // actually we'll never reach this line
    for (i = 0; i < numouts; i++) {
        t_double	*out = outs[i];
        n = sampleframes;
        while (n--)
            *out++ = 0.0;
    }
}

void terrain_clear_path(t_terrain *x)
{
    x->path_curr_idx = 0;
    x->path_num_points = 0;
}

void terrain_dsp64(t_terrain *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	// only put perf func on dsp chain if sig is connected
    terrain_clear_path(x);
	if (count[0]) {
		object_method(dsp64, gensym("dsp_add64"), x, terrain_perform64, 0, NULL);
        x->startclock = true;
	}
}


void terrain_anything(t_terrain *x, t_symbol *msg, long ac, t_atom *av)
{
    dadaobj_anything(dadaobj_cast(x), msg, ac, av);
    
    t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, msg, ac, av, LLLL_PARSE_CLONE);
    if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
        t_symbol *router = hatom_getsym(&parsed->l_head->l_hatom);
        llll_behead(parsed);
        
        if (dadaobj_anything_handle_domain_or_range(dadaobj_cast(x), router, parsed, 1)) {
            // nothing to do!
        } else if (router == gensym("clear")) {
            x->num_buffers = 0;
            terrain_clear_path(x);
            terrain_iar(x);
        } else if (router == gensym("clearpath")) {
            terrain_clear_path(x);
        } else if (router == gensym("postvalue")) {
            if (parsed->l_size >= 2) {
                double v1 = hatom_getdouble(&parsed->l_head->l_hatom);
                double v2 = hatom_getdouble(&parsed->l_head->l_next->l_hatom);
                long channel = (parsed->l_size >= 3 ? hatom_getlong(&parsed->l_head->l_next->l_next->l_hatom) : 1) - 1;
                double sample = (x->polar ? terrain_get_sample_rhotheta(x, v1, v2, channel) : terrain_get_sample_xy(x, v1, v2, channel));
                object_post((t_object *)x, "- %s = %.3f, %s = %.3f, channel %ld --> sample = %.3f", x->polar ? "rho" : "x", v1, x->polar ? "theta" : "y", v2, channel, sample);
            }
        }
    } else if (parsed) {
    }
    llll_free(parsed);
}

void terrain_iar(t_terrain *x)
{
    jbox_invalidate_layer((t_object *)x, NULL, gensym("terrain"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("buffers"));
    jbox_redraw((t_jbox *)x);
}

void terrain_tick(t_terrain *x)
{
    // careful: thread issues with audio thread?
    // might be irrelevant for our purposes...
    long max_path_pts = x->path_max_points;
    long curr_idx = x->path_curr_idx;
    if (max_path_pts > 0) {
        double x_val = x->curr_pt.rho, y_val = x->curr_pt.theta;
        if (x->polar)
            poltocar(x->curr_pt.rho, x->curr_pt.theta, &x_val, &y_val);
        x->path[curr_idx] = build_pt(x_val, y_val);
        curr_idx++;
        if (curr_idx >= DADA_TERRAIN_MAX_NUM_PATH_PT) {
            curr_idx = 0;
        }
        if (x->path_num_points < DADA_TERRAIN_MAX_NUM_PATH_PT)
            x->path_num_points++;
        x->path_curr_idx = curr_idx;
        jbox_redraw((t_jbox *)x);
    }

    if (sys_getdspstate())	// if the dsp is still on, schedule a next pictmeter_tick() call
        clock_fdelay(x->clock, x->redraw_time_ms);
}



