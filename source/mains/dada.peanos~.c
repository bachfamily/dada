/**
	@file
	dada.peanos~.c
	
	@name
	dada.peanos~
	
	@realname
	dada.peanos~
 
	@type
	object
	
	@module
	dada
 
	@author
	Daniele Ghisi
	
	@digest
	The timbrotheque of Babel
	
	@description
	Browse static timbres
	
	@discussion
 
	@category
	dada interfaces, dada audio
 
	@keywords
	peanos~, Peano, timbre, music, babel, disco, discoteque, browse, combinatorics, exploration, static
	
	@seealso
	dada.terrain~
	
	@owner
	Daniele Ghisi
 */

#include "dada.peanomath.h" // MPFR & GMP inside
#include "dada.bandpassgaintable.h"
#include <stdio.h>

#include "dada.interface.h"
#include "dada.geometry.h"
#include "dada.paint.h"
#include "notation/notation.h"
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

#include <signal.h>


#define DADA_PEANOS_INSET_TOP 8
#define DADA_PEANOS_INSET_LEFT 24
#define DADA_PEANOS_INSET_BOTTOM 24
#define DADA_PEANOS_INSET_RIGHT 48 //8 //< includes noisiness bar
#define DADA_PEANOS_INSET_RIGHT_NOISINESS 36 //8 //< includes noisiness bar
#define DADA_PEANOS_UI_NOISINESS_WIDTH 12


#define DADA_PEANOS_MAXPARTIALS 1024

#define DADA_PEANOS_DEBUG


#ifdef DADA_PEANOS_DEBUG
#define peanos_dev_post(...) if (x->debug) post(__VA_ARGS__)
#else
#define peanos_dev_post(...) ((void) 0)
#endif

#define DADA_PEANOS_LEGEND_SIZE       4096

#define DADA_PEANOS_MAIN_VIEW_POS (1./2.)
#define DADA_PEANOS_GLOBAL_VIEW_POS (3./4.)

#define DADA_PEANOS_LODISPLAY_SAMPLE_THRESHOLD 1000000


#define DADA_PEANOS_DEFAULT_MINPREC 500

//#define DADA_PEANOS_MPFR_PRECISION       500
//#define DADA_PEANOS_MPFR_PRECISION_HIGH  200000

#define DADA_PEANOS_MPFR_RND         MPFR_RNDN

// Coordinates for specifying a peanos~ point.
typedef struct _ptn
{
    double x;                ///< The horizontal coordinate
    double y;                ///< The vertical coordinate
    double n;                ///< The noisiness angle
} t_ptn;

// Biquad coefficients
typedef struct _biquad_coeffs
{
    double a1;
    double a2;
    double b0;
    double b1;
    double b2;
} t_biquad_coeffs;


#define DADA_PEANOS_SIN_TABLE_SIZE 8192
double sin_table[DADA_PEANOS_SIN_TABLE_SIZE+1];


typedef struct _peanos {
    t_dadaobj_pxjbox	b_ob;
    
    char                mode;
    char                model; // 0 = standard; 1 = padded for continuity
    
    // synthesis
    char                synthesis_mode;
    char                use_lookup_table;
    double              noisiness_to_q_exp;
    char                autoclear_filters;
    char                delay_interp_to_avoid_clicks;
    long                interp_freq_samps;
    long                interp_amp_samps;
    long                interp_noisiness_samps;
    long                interp_freq_samps_offset;
    long                interp_amp_samps_offset;
    long                interp_noisiness_samps_offset;

    long                bitrate;
    double              sr;
    double              timestep;
    
    long                float_precision_minimum;
    long                float_precision_maximum;
    long                legend_num_digits;
    char                show_legend;
    char                show_spectrum;
    char                show_spectrum_from_fzero;

    char                output_coords;
    char                output_coords_as_sym;
    long                output_coords_as_sym_precision;
    
    char                legend[DADA_PEANOS_LEGEND_SIZE];
    char                legend2[DADA_PEANOS_LEGEND_SIZE];
    
    // array containing values for: alpha, sigma, xi respectively
    mpfr_t              coord_hp[3];
    mpfr_t              screen_start_hp[3];
    mpfr_t              screen_end_hp[3];
    mpfr_t              screen_domain_hp[3];
    long                mpfr_precision[3];

    double              fzero;
    
    long                num_partials;
    long                precision;
    double              *curr_freqs; // freqs are normalized freqs: 1 = fzero
    double              *curr_amps;
    double              *curr_noisinesses;
    double              *next_freqs;
    double              *next_amps;
    double              *next_noisinesses;
    double              *phases;

    bool                must_interp;
    bool                must_process_coords_when_interp_has_ended;
    long                must_change_numpartials;
    long                must_change_model;
    
    
    double              *mem_ff1;
    double              *mem_ff2;
    double              *mem_fb1;
    double              *mem_fb2;
    char                editing_noisiness;
    
    char                mousedrag_constraint;
    
    
    // debug stuff
    char                dsp_debug;
    char                debug;
} t_peanos;



void handle_aborts(int signal_number);

void process_coords(t_peanos *x);
double get_gain_compensation(double freq, double noisiness, double sr);
double peanos_dbtoa(float db);
double peanos_atodb(double a);

void peanos_clear(t_peanos *x);
long model_get_num_partials(t_peanos *x);

void *peanos_new(t_symbol *s, long argc, t_atom *argv);
void peanos_free(t_peanos *x);
void peanos_assist(t_peanos *x, void *b, long m, long a, char *s);
void peanos_paint(t_peanos *x, t_object *patcherview);
t_atom_long peanos_acceptsdrag(t_peanos *x, t_object *drag, t_object *view);
void peanos_perform64(t_peanos *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void peanos_dsp64(t_peanos *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void peanos_doset(t_peanos *x, t_symbol *s);
void peanos_anything(t_peanos *x, t_symbol *msg, long ac, t_atom *av);
void peanos_tick(t_peanos *x);
t_max_err peanos_notify(t_peanos *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void peanos_bang(t_peanos *x);

long peanos_key(t_peanos *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
long peanos_keyup(t_peanos *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);

void peanos_iar(t_peanos *x);

char *peanos_mpfr_get_str(int base, size_t size, mpfr_srcptr num_hp, mpfr_rnd_t precision, size_t cut_to_this_size, bool trim_ending_zeros);


void peanos_focusgained(t_peanos *x, t_object *patcherview);
void peanos_focuslost(t_peanos *x, t_object *patcherview);
void peanos_mousemove(t_peanos *x, t_object *patcherview, t_pt pt, long modifiers);
void peanos_mousedown(t_peanos *x, t_object *patcherview, t_pt pt, long modifiers);
void peanos_mousedrag(t_peanos *x, t_object *patcherview, t_pt pt, long modifiers);
void peanos_mousewheel(t_peanos *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc);
void peanos_mouseup(t_peanos *x, t_object *patcherview, t_pt pt, long modifiers);
void peanos_mouseenter(t_peanos *x, t_object *patcherview, t_pt pt, long modifiers);
void peanos_mouseleave(t_peanos *x, t_object *patcherview, t_pt pt, long modifiers);

void peanos_set(t_peanos *x, t_symbol *s);

void peanos_zoom_by(t_peanos *x, int coord, double zoom_factor, double around_this_coord);
void peanos_zoom_by_hp(t_peanos *x, int coord, double zoom_factor, mpfr_t around_this_coord_hp);
void peanos_zoom_exp_hp(t_peanos *x, int coord, mpfr_t zoom_exponent, mpfr_t around_this_coord_hp);


void peanos_send_mousedown_notification(t_peanos *x, t_symbol *sym, char force_verbose);

double samp_uint16_to_double(uint16_t samp);
t_float samp_uint16_to_float(uint16_t samp);

void peanos_int(t_peanos *x, long num);
void peanos_jsave(t_peanos *x, t_dictionary *d);
t_llll *peanos_get_state(t_peanos *x);
void peanos_set_state(t_peanos *x, t_llll *ll);
void peanos_preset(t_peanos *x);
void peanos_end_preset(t_peanos *x);
void peanos_begin_preset(t_peanos *x, t_symbol *s, long argc, t_atom *argv);
void peanos_restore_preset(t_peanos *x, t_symbol *s, long argc, t_atom *argv);



static t_class *s_peanos_class;
// gmp_randstate_t r_state;

t_llll *peanos_get_state(t_peanos *x)
{
    t_llll *out = llll_get();
    for (int i = 0; i < 3; i++) {
        char *str = peanos_mpfr_get_str(10, 0, x->coord_hp[i], DADA_PEANOS_MPFR_RND, 0, 0);
        llll_appendsym(out, gensym(str));
        bach_freeptr(str);
    }
    return out;
}

void peanos_set_state(t_peanos *x, t_llll *ll)
{
    // clearing things first
    for (int i = 0; i < 3; i++)
        mpfr_set_d(x->coord_hp[i], 0, DADA_PEANOS_MPFR_RND);

    // parsing ll then
    if (ll->l_size >= 3) {
        t_llllelem *el = ll->l_head;
        for (int i = 0; i < 3 && el; i++) {
            t_symbol *sym = hatom_getsym(&el->l_hatom);
            if (sym) {
                mpfr_set_str(x->coord_hp[i], sym->s_name, 10, DADA_PEANOS_MPFR_RND);
            }
            el = el->l_next;
        }
    }
    process_coords(x);
    peanos_iar(x);
}


void peanos_begin_preset(t_peanos *x, t_symbol *s, long argc, t_atom *argv)
{
    dadaobj_begin_preset(dadaobj_cast(x), s, argc, argv);
}


void peanos_restore_preset(t_peanos *x, t_symbol *s, long argc, t_atom *argv)
{
    dadaobj_restore_preset(dadaobj_cast(x), s, argc, argv);
}

void peanos_end_preset(t_peanos *x)
{
    dadaobj_end_preset(dadaobj_cast(x));
}

void peanos_preset(t_peanos *x) {
    dadaobj_preset(dadaobj_cast(x));
}

void peanos_jsave(t_peanos *x, t_dictionary *d)
{
    //post("***** JSAVE *****");
    t_llll *whole_info = peanos_get_state(x);
    llll_store_in_dictionary(whole_info, d, "peanos_data", NULL);
    llll_free(whole_info);
}

void resize_partials_arrays(t_peanos *x, long newsize)
{
    // we are static! much better ;)
    return;
/*    x->curr_amps = (double *)bach_resizeptrclear(x->curr_amps, newsize * sizeof(double));
    x->curr_freqs = (double *)bach_resizeptrclear(x->curr_freqs, newsize * sizeof(double));
    x->curr_noisinesses = (double *)bach_resizeptrclear(x->curr_noisinesses, newsize * sizeof(double));
    x->next_amps = (double *)bach_resizeptrclear(x->next_amps, newsize * sizeof(double));
    x->next_freqs = (double *)bach_resizeptrclear(x->next_freqs, newsize * sizeof(double));
    x->next_noisinesses = (double *)bach_resizeptrclear(x->next_noisinesses, newsize * sizeof(double));
    x->phases = (double *)bach_resizeptrclear(x->phases, newsize * sizeof(double));
    x->mem_ff1 = (double *)bach_resizeptrclear(x->mem_ff1, newsize * sizeof(double));
    x->mem_ff2 = (double *)bach_resizeptrclear(x->mem_ff2, newsize * sizeof(double));
    x->mem_fb1 = (double *)bach_resizeptrclear(x->mem_fb1, newsize * sizeof(double));
    x->mem_fb2 = (double *)bach_resizeptrclear(x->mem_fb2, newsize * sizeof(double)); */
}

void peanos_change_model_do(t_peanos *x, long newmodel)
{
    x->model = newmodel;
    resize_partials_arrays(x, model_get_num_partials(x));
    process_coords(x);
}

void peanos_change_numpartials_do(t_peanos *x, long newnumpartials)
{
    resize_partials_arrays(x, newnumpartials);
    x->num_partials = newnumpartials;
    process_coords(x);
}

// To DO: if one changes the attribute with audio on it's a mess! gotta make this thread safe.
t_max_err peanos_setattr_numpartials(t_peanos *x, t_object *attr, long ac, t_atom *av){
    if (ac) {
        long this_num_partials = MAX(1, atom_getlong(av));
        if (this_num_partials > DADA_PEANOS_MAXPARTIALS) {
            object_error((t_object *)x, "Too many partials!");
        } else {
            if (this_num_partials != x->num_partials) {
                if (sys_getdspstate())
                    x->must_change_numpartials = this_num_partials;
                else
                    peanos_change_numpartials_do(x, this_num_partials);
            }
        }
    }
    return MAX_ERR_NONE;
}
// To DO: if one changes the attribute with audio on it's a mess! gotta make this thread safe.
t_max_err peanos_setattr_model(t_peanos *x, t_object *attr, long ac, t_atom *av){
    if (ac) {
        long this_model = atom_getlong(av);
        if (this_model != x->model) {
            if (sys_getdspstate())
                x->must_change_model = this_model;
            else
                peanos_change_model_do(x, this_model);
        }
    }
    return MAX_ERR_NONE;
}



void C74_EXPORT ext_main(void *moduleRef)
{
    common_symbols_init();
    
    llllobj_common_symbols_init();
    
    srand(time(NULL));
    
    if (dada_check_bach_version() || llllobj_test()) {
        dada_error_bachcheck();
        return;
    }
    
    for (int i = 0; i < DADA_PEANOS_SIN_TABLE_SIZE + 1; i++) // + 1 is to ease interpolation later
        sin_table[i] = sin(TWOPI * (double)i/DADA_PEANOS_SIN_TABLE_SIZE);

    t_class *c;

    CLASS_NEW_CHECK_SIZE(c, "dada.peanos~", (method)peanos_new, (method)peanos_free, (long)sizeof(t_peanos), 0L /* leave NULL!! */, A_GIMME, 0);

	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
    jbox_initclass(c, JBOX_FONTATTR);	// include fonts
	class_dspinitjbox(c);

    signal(SIGABRT, &handle_aborts);
    
	class_addmethod(c, (method)peanos_dsp64,					"dsp64", A_CANT, 0);
	class_addmethod(c, (method)peanos_paint,					"paint",	A_CANT, 0);
	class_addmethod(c, (method)peanos_assist,                  "assist",		A_CANT, 0);
	class_addmethod(c, (method)peanos_acceptsdrag,	"acceptsdrag_unlocked", A_CANT, 0);
	class_addmethod(c, (method)peanos_acceptsdrag,	"acceptsdrag_locked", A_CANT, 0);
    class_addmethod(c, (method)peanos_notify,                  "bachnotify", A_CANT, 0);
    class_addmethod(c, (method)peanos_notify,                  "notify", A_CANT, 0);
    
    class_addmethod(c, (method) peanos_preset, "preset", 0);
    class_addmethod(c, (method) peanos_begin_preset, "begin_preset", A_GIMME, 0);
    class_addmethod(c, (method) peanos_restore_preset, "restore_preset", A_GIMME, 0);
    class_addmethod(c, (method) peanos_end_preset, "end_preset", 0);
    CLASS_METHOD_ATTR_PARSE(c, "begin_preset", "undocumented", gensym("long"), 0L, "1");
    CLASS_METHOD_ATTR_PARSE(c, "restore_preset", "undocumented", gensym("long"), 0L, "1");
    CLASS_METHOD_ATTR_PARSE(c, "end_preset", "undocumented", gensym("long"), 0L, "1");
    class_addmethod(c, (method)peanos_jsave, "jsave", A_CANT, 0);

    // @method zoomby @digest Zoom by a given factor
    // @description A <m>zoomby</m> message, followed by a floating point number <m>N</m>, will increase or decrease the zoom by the factor <m>N</m>.
    // By default, the zooming happens around the domain center; if an additional "cursor" symbol is given, the zooming happens around the play cursor;
    // if instead of the "cursor" symbol a floating point number is given, the zooming happens around the specified coordinate.
    // @marg 0 @name factor @optional 0 @type number
    // @marg 1 @name center @optional 1 @type symbol/number
    class_addmethod(c, (method)peanos_anything, "zoomby", A_GIMME, 0);

    // @method zoomexp @digest Zoom by a given exponent
    // @description A <m>zoomexp</m> message, followed by a floating point number <m>N</m>,
    // will exponentially increase or decrease the zoom by the exponent <m>N</m>.
    // By default, the zooming happens around the domain center; if an additional "cursor" symbol is given, the zooming happens around the play cursor;
    // if instead of the "cursor" symbol a floating point number is given, the zooming happens around the specified coordinate.
    // @marg 0 @name exponent @optional 0 @type number
    // @marg 1 @name center @optional 1 @type symbol/number
    class_addmethod(c, (method)peanos_anything, "zoomexp", A_GIMME, 0);

    // @method clear @digest Clear filters
    // @description A <m>clear</m> message clears the filter memory.
    class_addmethod(c, (method)peanos_clear, "clear", 0);

    class_addmethod(c, (method)peanos_anything, "postvalue", A_GIMME, 0);
    class_addmethod(c, (method)peanos_anything, "anything", A_GIMME, 0);
    class_addmethod(c, (method)peanos_bang, "bang", 0);
    
    
    // interface
    class_addmethod(c, (method) peanos_focusgained, "focusgained", A_CANT, 0);
    class_addmethod(c, (method) peanos_focuslost, "focuslost", A_CANT, 0);
    
    class_addmethod(c, (method) peanos_mousedown, "mousedown", A_CANT, 0);
    class_addmethod(c, (method) peanos_mouseup, "mouseup", A_CANT, 0);
    class_addmethod(c, (method) peanos_mousemove, "mousemove", A_CANT, 0);
    class_addmethod(c, (method) peanos_mousedrag, "mousedrag", A_CANT, 0);
    class_addmethod(c, (method) peanos_mousewheel, "mousewheel", A_CANT, 0);
    class_addmethod(c, (method) peanos_mouseenter, "mouseenter", A_CANT, 0);
    class_addmethod(c, (method) peanos_mouseleave, "mouseleave", A_CANT, 0);

    // @method (keyboard) @digest Play or set domain
    // @description
    // • <m>Spacebar</m>: toggle play<br />
    class_addmethod(c, (method) peanos_key, "key", A_CANT, 0);
    class_addmethod(c, (method) peanos_keyup, "keyup", A_CANT, 0);
    
    
    dadaobj_class_init(c, LLLL_OBJ_UIMSP, DADAOBJ_ZOOM | DADAOBJ_BORDER | DADAOBJ_BG); // | DADAOBJ_NOTIFICATIONS);

    
    CLASS_ATTR_INVISIBLE(c, "playstep", ATTR_GET_OPAQUE | ATTR_SET_OPAQUE);
	CLASS_ATTR_DEFAULT(c,"patching_rect",0, "0. 0. 700. 200.");

    CLASS_STICKY_ATTR(c,"category",0,"Color");
    
    CLASS_STICKY_ATTR_CLEAR(c, "category");


    CLASS_STICKY_ATTR(c,"category",0,"Precision");

    CLASS_ATTR_LONG(c, "minfloatprec", 0, t_peanos, float_precision_minimum);
    CLASS_ATTR_STYLE_LABEL(c, "minfloatprec", 0, "text", "Minimum Floating-Point Numbers Precision");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"minfloatprec",0,"500");
    // @description Sets the minimum precision of floating point numbers

    CLASS_ATTR_LONG(c, "maxfloatprec", 0, t_peanos, float_precision_maximum);
    CLASS_ATTR_STYLE_LABEL(c, "maxfloatprec", 0, "text", "Maximum Floating-Point Numbers Precision");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"maxfloatprec",0,"0");
    // @description Sets the maximum precision of floating point numbers (while zooming); leave 0 for unlimited
    // (but beware, things can become slow!!!)

    CLASS_ATTR_LONG(c, "peanoprec", 0, t_peanos, precision);
    CLASS_ATTR_STYLE_LABEL(c, "peanoprec", 0, "text", "Peano Computation Precision");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"peanoprec",0,"20");
    // @description Sets the number of items in the Peano ternary expansions

    CLASS_ATTR_LONG(c, "outputcoordsassymprec", 0, t_peanos, output_coords_as_sym_precision);
    CLASS_ATTR_STYLE_LABEL(c, "outputcoordsassymprec", 0, "text", "Coordinate Output Symbol Precision");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"outputcoordsassymprec",0,"100");
    // @description Sets the precision of the coordinate output as symbols, if <m>outputcoordsassym</m> is on.

    CLASS_ATTR_LONG(c, "coordsdisplayprec", 0, t_peanos, legend_num_digits);
    CLASS_ATTR_STYLE_LABEL(c, "coordsdisplayprec", 0, "text", "Number of Digits of the Displayed Coordinates");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"coordsdisplayprec",0,"50");
    // @description Sets the number of digits in the coordinates legend
    

    CLASS_STICKY_ATTR_CLEAR(c, "category");

    CLASS_STICKY_ATTR(c,"category",0,"Appearance");

    CLASS_ATTR_CHAR(c, "showspectrum", 0, t_peanos, show_spectrum);
    CLASS_ATTR_STYLE_LABEL(c, "showspectrum", 0, "onoff", "Show Spectrum");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showspectrum",0,"1");
    // @description Toggles the display of the spectral configuration

    CLASS_ATTR_CHAR(c, "spectrumfromfzero", 0, t_peanos, show_spectrum_from_fzero);
    CLASS_ATTR_STYLE_LABEL(c, "spectrumfromfzero", 0, "onoff", "Start Spectrum at Fundamental Frequency");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"spectrumfromfzero",0,"0");
    // @description Toggles the ability to shift the beginning of the spectrum at the fundamental frequency.

    
    CLASS_ATTR_CHAR(c, "showcoords", 0, t_peanos, show_legend);
    CLASS_ATTR_STYLE_LABEL(c, "showcoords", 0, "onoff", "Show Coordinates");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showcoords",0,"1");
    // @description Toggles the display of the coordinates legend

    CLASS_STICKY_ATTR_CLEAR(c, "category");

    
    
    CLASS_STICKY_ATTR(c,"category",0,"Behavior");
    
    CLASS_ATTR_CHAR(c, "outputcoords", 0, t_peanos, output_coords);
    CLASS_ATTR_STYLE_LABEL(c, "outputcoords", 0, "onoff", "Output Coordinates As Floats");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"outputcoords",0,"1");
    CLASS_ATTR_BASIC(c, "outputcoords", 0);
    // @description Toggles the ability to output the coordinates of the points from the third outlet in numerical form.

    CLASS_ATTR_CHAR(c, "outputcoordsassym", 0, t_peanos, output_coords_as_sym);
    CLASS_ATTR_STYLE_LABEL(c, "outputcoordsassym", 0, "onoff", "Output Coordinates As Symbols");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"outputcoordsassym",0,"0");
    CLASS_ATTR_BASIC(c, "outputcoordsassym", 0);
    // @description Toggles the ability to output the coordinates of the points from the third outlet as symbols, with a precision
    // given by the <m>outputcoordsassymprec</m> attribute.

    CLASS_STICKY_ATTR_CLEAR(c, "category");

    CLASS_STICKY_ATTR(c,"category",0,"Settings");

    CLASS_ATTR_CHAR(c, "mode", 0, t_peanos, mode);
    CLASS_ATTR_STYLE_LABEL(c, "mode", 0, "enumindex", "Mode");
    CLASS_ATTR_ENUMINDEX(c,"mode", 0, "Active Passive");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"mode",0,"0");
    CLASS_ATTR_BASIC(c, "mode", 0);
    // @description Sets the user interface mode: either "active" (coordinates are and via messages)
    // or "passive" (coordinates are expected from the audio inlets).

    CLASS_ATTR_CHAR(c, "model", 0, t_peanos, model);
    CLASS_ATTR_STYLE_LABEL(c, "model", 0, "enumindex", "Mode");
    CLASS_ATTR_ENUMINDEX(c,"model", 0, "Standard Padded For Continuity");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"model",0,"0");
    CLASS_ATTR_ACCESSORS(c, "model", (method)NULL, (method)peanos_setattr_model);
    CLASS_ATTR_BASIC(c, "model", 0);
    // @description Sets the geometric model to be used
    
    CLASS_ATTR_LONG(c, "numpartials", 0, t_peanos, num_partials);
    CLASS_ATTR_STYLE_LABEL(c, "numpartials", 0, "text", "Number Of Partials");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"numpartials",0,"16");
    CLASS_ATTR_ACCESSORS(c, "numpartials", (method)NULL, (method)peanos_setattr_numpartials);
    CLASS_ATTR_BASIC(c, "numpartials", 0);
    // @description Sets the number of partials in the model

    CLASS_STICKY_ATTR_CLEAR(c, "category");

    
    CLASS_STICKY_ATTR(c,"category",0,"Synthesis");
    
    CLASS_ATTR_CHAR(c, "synth", 0, t_peanos, synthesis_mode);
    CLASS_ATTR_STYLE_LABEL(c, "synth", 0, "enumindex", "Synthesis Mode");
    CLASS_ATTR_ENUMINDEX(c,"synth", 0, "Sinusoids+Filtered Noise Bandwidth-Enhanced Oscillators");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"synth",0,"0");
    CLASS_ATTR_BASIC(c, "synth", 0);
    // @description Sets the synthesis mode

    CLASS_ATTR_CHAR(c, "lookuptable", 0, t_peanos, use_lookup_table);
    CLASS_ATTR_STYLE_LABEL(c, "lookuptable", 0, "onoff", "Use Lookup Table");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"lookuptable",0,"1");
    // @description Toggles the ability to use sinusoidal lookup tables

    CLASS_ATTR_CHAR(c, "autoclear", 0, t_peanos, autoclear_filters);
    CLASS_ATTR_STYLE_LABEL(c, "autoclear", 0, "onoff", "Autoclear Filter Memory");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"autoclear",0,"0");
    // @description Toggles the ability to automatically clear the memory of DSP filters when changing coordinate.
    // This comes at the price of possibly introducing clicks at coordinate change.

    CLASS_ATTR_CHAR(c, "autodelay", 0, t_peanos, delay_interp_to_avoid_clicks);
    CLASS_ATTR_STYLE_LABEL(c, "autodelay", 0, "onoff", "Delay Computation To Avoid Clicks");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"autodelay",0,"1");
    // @description Toggles the ability to automatically delay an interpolation if another one is happening

    
    CLASS_ATTR_LONG(c, "freqsmooth", 0, t_peanos, interp_freq_samps);
    CLASS_ATTR_STYLE_LABEL(c, "freqsmooth", 0, "text", "Number of Samples for Frequency Smoothing");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"freqsmooth",0,"4096");
    // @description Sets the number of samples across which every frequency change is linearly interpolated.
    
    CLASS_ATTR_LONG(c, "magsmooth", 0, t_peanos, interp_amp_samps);
    CLASS_ATTR_STYLE_LABEL(c, "magsmooth", 0, "text", "Number of Samples for Magnitude Smoothing");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"magsmooth",0,"4096");
    // @description Sets the number of samples across which every amplitude change is linearly interpolated.

    CLASS_ATTR_LONG(c, "noisesmooth", 0, t_peanos, interp_noisiness_samps);
    CLASS_ATTR_STYLE_LABEL(c, "noisesmooth", 0, "text", "Number of Samples for Noisiness Smoothing");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"noisesmooth",0,"4096");
    // @description Sets the number of samples across which every noisiness change is linearly interpolated.

    
    
    
/*    CLASS_ATTR_DOUBLE(c, "noisinessexp", 0, t_peanos, noisiness_to_q_exp);
    CLASS_ATTR_STYLE_LABEL(c, "noisinessexp", 0, "text", "Noisiness to Q Conversion Exponent");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"noisinessexp",0,"8.");
    // @description Sets the exponent for the conversion between noisiness and filter Q factor
    // only when <m>synth</m> is "Sinusoids+Filtered Noise"
  */
    
    CLASS_ATTR_DOUBLE(c, "fzero", 0, t_peanos, fzero);
    CLASS_ATTR_STYLE_LABEL(c, "fzero", 0, "text", "Fundamental Frequency");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"fzero",0,"220");
    CLASS_ATTR_BASIC(c, "fzero", 0);
    // @description Sets the fundamental frequency
    
    CLASS_STICKY_ATTR_CLEAR(c, "category");

    

    CLASS_ATTR_CHAR(c, "debug", 0, t_peanos, debug);
    CLASS_ATTR_STYLE_LABEL(c, "debug", 0, "onoff", "Debug");
    CLASS_ATTR_INVISIBLE(c, "debug", ATTR_GET_OPAQUE | ATTR_SET_OPAQUE);
    // @exclude all

    CLASS_ATTR_CHAR(c, "dspdebug", 0, t_peanos, dsp_debug);
    CLASS_ATTR_STYLE_LABEL(c, "dspdebug", 0, "onoff", "DSP Debug");
    CLASS_ATTR_INVISIBLE(c, "dspdebug", ATTR_GET_OPAQUE | ATTR_SET_OPAQUE);
    // @exclude all


    

    srand(time(NULL));
//    gmp_randinit_default (r_state);
    
	class_register(CLASS_BOX, c);
	s_peanos_class = c;
    dadaobj_class_add_fileusage_method(c);
}

void change_precision(t_peanos *x, int coord, long new_precision)
{
    x->mpfr_precision[coord] = new_precision;
    mpfr_prec_round(x->coord_hp[coord], new_precision, DADA_PEANOS_MPFR_RND);
    mpfr_prec_round(x->screen_start_hp[coord], new_precision, DADA_PEANOS_MPFR_RND);
    mpfr_prec_round(x->screen_end_hp[coord], new_precision, DADA_PEANOS_MPFR_RND);
    mpfr_prec_round(x->screen_domain_hp[coord], new_precision, DADA_PEANOS_MPFR_RND);
}



t_max_err peanos_notify(t_peanos *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
    return jbox_notify((t_jbox *)x, s, msg, sender, data);
}


void *peanos_new(t_symbol *s, long argc, t_atom *argv)
{
	t_peanos *x = NULL;
	t_dictionary *d=NULL;
	long boxflags;
    t_llll *llll_for_rebuild = NULL;

	if (!(d=object_dictionaryarg(argc,argv)))
		return NULL;

    if ((x = (t_peanos *)object_alloc_debug(s_peanos_class))) {
        boxflags = 0
        | JBOX_DRAWFIRSTIN
        | JBOX_NODRAWBOX
        | JBOX_DRAWINLAST
        | JBOX_TRANSPARENT
        //		| JBOX_NOGROW
        //		| JBOX_GROWY
        | JBOX_GROWBOTH
        | JBOX_HILITE
        //		| JBOX_BACKGROUND
        //		| JBOX_DRAWBACKGROUND
        //		| JBOX_NOFLOATINSPECTOR
        //		| JBOX_TEXTFIELD
        //		| JBOX_MOUSEDRAGDELTA
        //		| JBOX_TEXTFIELD
        ;
        
        jbox_new((t_jbox *)x, boxflags, argc, argv);
        x->b_ob.r_ob.l_ob.z_box.b_firstin = (t_object *)x;
        dsp_setupjbox((t_pxjbox *)x, 3);
        
        dadaobj_pxjbox_setup((t_dadaobj_pxjbox *)x, DADAOBJ_ZOOM | DADAOBJ_BORDER | DADAOBJ_BG, build_pt(1., 1.), -1, -1, 2, NULL, (invalidate_and_redraw_fn)peanos_iar, "", 0, "44s", NULL);
        x->b_ob.d_ob.m_zoom.max_zoom_perc = build_pt(100000, 100000);
        dadaobj_addfunctions(dadaobj_cast(x), NULL, NULL, NULL, (get_state_fn)peanos_get_state, (set_state_fn)peanos_set_state, NULL, NULL, NULL);

        x->sr = 44100; // will be replaced by the dsp methods
        x->timestep = TWOPI * 1./x->sr;
        x->float_precision_minimum = DADA_PEANOS_DEFAULT_MINPREC;
        x->noisiness_to_q_exp = 8.;
        
        for (int i = 0; i < 3; i++) {
            x->mpfr_precision[i] = x->float_precision_minimum;
            mpfr_init2(x->screen_domain_hp[i], x->float_precision_minimum);
            mpfr_init2(x->screen_start_hp[i], x->float_precision_minimum);
            mpfr_init2(x->screen_end_hp[i], x->float_precision_minimum);
            mpfr_init2(x->coord_hp[i], x->float_precision_minimum);
        }
        
        for (int i = 0; i < 3; i++) {
            mpfr_set_d(x->coord_hp[i], 0., DADA_PEANOS_MPFR_RND);
            mpfr_set_d(x->screen_start_hp[i], 0., DADA_PEANOS_MPFR_RND);
            mpfr_set_d(x->screen_end_hp[i], 1., DADA_PEANOS_MPFR_RND);
            mpfr_set_d(x->screen_domain_hp[i], 1., DADA_PEANOS_MPFR_RND);
        }

        x->must_change_numpartials = -1;
        x->must_change_model = -1;
        
        x->fzero = 220;
        x->precision = 20;
        x->num_partials = 16;
        // +3 is for the possible padding model
        x->curr_amps = (double *)bach_newptrclear((DADA_PEANOS_MAXPARTIALS + 3) * sizeof(double));
        x->curr_freqs = (double *)bach_newptrclear((DADA_PEANOS_MAXPARTIALS + 3) * sizeof(double));
        x->curr_noisinesses = (double *)bach_newptrclear((DADA_PEANOS_MAXPARTIALS + 3) * sizeof(double));
        x->next_amps = (double *)bach_newptrclear((DADA_PEANOS_MAXPARTIALS + 3) * sizeof(double));
        x->next_freqs = (double *)bach_newptrclear((DADA_PEANOS_MAXPARTIALS + 3) * sizeof(double));
        x->next_noisinesses = (double *)bach_newptrclear((DADA_PEANOS_MAXPARTIALS + 3) * sizeof(double));
        x->phases = (double *)bach_newptrclear((DADA_PEANOS_MAXPARTIALS + 3) * sizeof(double));
        x->mem_ff1 = (double *)bach_newptrclear((DADA_PEANOS_MAXPARTIALS + 3) * sizeof(double));
        x->mem_ff2 = (double *)bach_newptrclear((DADA_PEANOS_MAXPARTIALS + 3) * sizeof(double));
        x->mem_fb1 = (double *)bach_newptrclear((DADA_PEANOS_MAXPARTIALS + 3) * sizeof(double));
        x->mem_fb2 = (double *)bach_newptrclear((DADA_PEANOS_MAXPARTIALS + 3) * sizeof(double));

        jbox_set_fontsize((t_object *)x, 8.);
        jbox_set_fontname((t_object *)x, gensym("<Monospaced>"));
        
        attr_dictionary_process(x,d);
        
        if ((llll_for_rebuild = llll_retrieve_from_dictionary(d, "peanos_data"))) {
            llllobj_manage_dict_llll((t_object *)x, LLLL_OBJ_UIMSP, llll_for_rebuild);
            peanos_set_state(x, llll_for_rebuild);
            llll_free(llll_for_rebuild);
        }

        jbox_ready((t_jbox *)x);
        
        dadaobj_set_current_version_number(dadaobj_cast(x));

        process_coords(x);
        
        return x;
    }
    
    
    return NULL;
}


void peanos_free(t_peanos *x)
{
    bach_freeptr(x->mem_fb1);
    bach_freeptr(x->mem_fb2);
    bach_freeptr(x->mem_ff1);
    bach_freeptr(x->mem_ff2);
    
    bach_freeptr(x->curr_amps);
    bach_freeptr(x->curr_freqs);
    bach_freeptr(x->curr_noisinesses);
    bach_freeptr(x->next_amps);
    bach_freeptr(x->next_freqs);
    bach_freeptr(x->next_noisinesses);
    bach_freeptr(x->phases);
                                                                                   
    for (int i = 0; i < 3; i++) {
        mpfr_clear(x->coord_hp[i]);
        mpfr_clear(x->screen_start_hp[i]);
        mpfr_clear(x->screen_end_hp[i]);
        mpfr_clear(x->screen_domain_hp[i]);
    }

    dsp_freejbox((t_pxjbox *)x);
    dadaobj_pxjbox_free((t_dadaobj_pxjbox *)x);
}


/// HANDLING SIGNALS

void handle_aborts(int signal_number)
{
    error("Something is wrong.");
    error("  If you are setting the cursor on a point, your computer isn't able to play from that point.");
    error("  Wait for better computers, or resume from a previous point.");
    
    /*Your code goes here. You can output debugging info.
     If you return from this function, and it was called
     because abort() was called, your program will exit or crash anyway
     (with a dialog box on Windows).
     */
}

void output_coords(t_peanos *x)
{
    if (x->output_coords) {
        t_llll *coord = llll_get();
        llll_appendsym(coord, gensym("coords"));
        llll_appenddouble(coord, mpfr_get_d(x->coord_hp[0], DADA_PEANOS_MPFR_RND));
        llll_appenddouble(coord, mpfr_get_d(x->coord_hp[1], DADA_PEANOS_MPFR_RND));
        llll_appenddouble(coord, mpfr_get_d(x->coord_hp[2], DADA_PEANOS_MPFR_RND));
        llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UIMSP, 2, coord);
        llll_free(coord);
    }
    
    if (x->output_coords_as_sym){
        long precision = x->output_coords_as_sym_precision;
        t_llll *coord = llll_get();
        char *text1 = peanos_mpfr_get_str(10, precision, x->coord_hp[0], DADA_PEANOS_MPFR_RND, precision, false);
        char *text2 = peanos_mpfr_get_str(10, precision, x->coord_hp[1], DADA_PEANOS_MPFR_RND, precision, false);
        char *text3 = peanos_mpfr_get_str(10, precision, x->coord_hp[2], DADA_PEANOS_MPFR_RND, precision, false);
        llll_appendsym(coord, gensym("coordsassym"));
        llll_appendsym(coord, gensym(text1));
        llll_appendsym(coord, gensym(text2));
        llll_appendsym(coord, gensym(text3));
        llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UIMSP, 2, coord);
        llll_free(coord);
        bach_freeptr(text1);
        bach_freeptr(text2);
        bach_freeptr(text3);
    }

    t_llll *ll = llll_get();
    t_llll *freqs = llll_get();
    t_llll *amps = llll_get();
    t_llll *nois = llll_get();
    long np = x->num_partials;
    for (long i = 0; i < np; i++) {
        llll_appenddouble(freqs, x->next_freqs[i] * x->fzero);
        llll_appenddouble(amps, x->next_amps[i]);
        llll_appenddouble(nois, x->next_noisinesses[i]);
    }
    llll_appendllll(ll, freqs);
    llll_appendllll(ll, amps);
    llll_appendllll(ll, nois);
    llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UIMSP, 1, ll);
    llll_free(ll);
}

void peanos_set_mustinterp(t_peanos *x)
{
    x->must_interp = true;
    x->interp_amp_samps_offset = 0;
    x->interp_freq_samps_offset = 0;
    x->interp_noisiness_samps_offset = 0;
}

void process_coords(t_peanos *x)
{
    dadaobj_mutex_lock(dadaobj_cast(x));
    
    if (sys_getdspstate() && x->must_interp && x->delay_interp_to_avoid_clicks) {
        // an interpolation is already going on. let's do this later to avoid clicks
        x->must_process_coords_when_interp_has_ended = true;
        dadaobj_mutex_unlock(dadaobj_cast(x));
        return;
    }

    x->must_process_coords_when_interp_has_ended = false;

    // clipping in [0, 1]
    for (int i = 0; i < 3; i++) {
        if (mpfr_cmp_d(x->coord_hp[i], 0.) < 0)
            mpfr_set_d(x->coord_hp[i], 0., DADA_PEANOS_MPFR_RND);
        
        if (mpfr_cmp_d(x->coord_hp[i], 1.) > 0)
            mpfr_set_d(x->coord_hp[i], 1., DADA_PEANOS_MPFR_RND);
    }
    
    //
    
    long N = x->num_partials;
    long precision = x->precision;
    
    double *model_amps = x->next_amps;
    double *model_freqs = x->next_freqs;
    double *model_noisinesses = x->next_noisinesses;

    if (x->model == 0) { // Standard model
        // Amplitudes
        double sph[N];
        sph[0] = 1;
        unitIntervalToHyperCube(x->coord_hp[0], N-1, precision, sph+1);
        for (long i = 1; i < N; i++)
            sph[i] *= PIOVERTWO;
        sphericalToCartesian(sph, model_amps, N);
        
        // Freqs
        unitIntervalToHyperCube(x->coord_hp[1], N, precision, model_freqs);
        for (long i = 0; i < N; i++)
            model_freqs[i] = (1 + i + model_freqs[i]);
        
        // Noisiness
        unitIntervalToHyperCube(x->coord_hp[2], N, precision, model_noisinesses);

    } else { // Model padded for continuity
        
        // Amplitudes
        long Npad = N+2;
        double sph[N+2], valpha[N+2];
        sph[0] = 1;
        unitIntervalToHyperCube(x->coord_hp[0], N+1, precision, sph+1);
        for (long i = 1; i < N+2; i++)
            sph[i] *= PIOVERTWO;
        sphericalToCartesian(sph, valpha, N+2);
        
        // additional infrastructure to preserve continuity (see paper)
        double den = sqrt(valpha[Npad-2]*valpha[Npad-2] + valpha[Npad-1] * valpha[Npad-1]);
        double phinminonealpha = 0;
        if (den != 0)
            phinminonealpha = acos(valpha[Npad-2]/den);
        double phionebeta = PIOVERTWO * (2./3. + (1/PIOVERTWO) * phinminonealpha/3.);
        double S = sin(phionebeta);
        double C = cos(phionebeta);
        double sigma_d = mpfr_get_d(x->coord_hp[1], DADA_PEANOS_MPFR_RND);
        for (long i = 0; i < N; i++)
            model_amps[i] = pow(S, sigma_d) * valpha[i];
        model_amps[N] = pow(S, sigma_d) * sqrt(1 - sigma_d) * valpha[N];
        model_amps[N+1] = C * sqrt(sigma_d);
        double norm_amps = 0;
        for (long i = 0; i < Npad; i++)
            norm_amps += model_amps[i]*model_amps[i];
        norm_amps = sqrt(norm_amps);
        for (long i = 0; i < Npad; i++)
            model_amps[i] /= norm_amps;
        
        
        
        // Freqs
        unitIntervalToHyperCube(x->coord_hp[1], N+2, precision, model_freqs);
        for (long i = 0; i < N+1; i++)
            model_freqs[i] = (1 + i + model_freqs[i]);
        model_freqs[N+1] = model_freqs[N+1] * x->fzero;
        
        // Noisiness
        unitIntervalToHyperCube(x->coord_hp[2], N+2, precision, model_noisinesses);
    }
    
    peanos_set_mustinterp(x);
    dadaobj_mutex_unlock(dadaobj_cast(x));
}




///// CONVERSIONS

void peanos_pix_to_coord(t_peanos *x, t_rect *rect, t_ptn pixel, mpfr_t coord_hp[3], char high_precision)
{
    // coord = start_coord + pix/width * domain_coord
    
    for (int i = 0; i < 3; i++) {
        // rough estimate
        mpfr_set_d(coord_hp[i], (i == 0 ? pixel.x - DADA_PEANOS_INSET_LEFT :
                                 i == 1 ? pixel.y - DADA_PEANOS_INSET_TOP :
                                 pixel.n - DADA_PEANOS_INSET_TOP), DADA_PEANOS_MPFR_RND);
        mpfr_div_d(coord_hp[i], coord_hp[i], (i == 0 ? rect->width - DADA_PEANOS_INSET_LEFT - DADA_PEANOS_INSET_RIGHT :
                                              i == 1 ? rect->height - DADA_PEANOS_INSET_TOP - DADA_PEANOS_INSET_BOTTOM :
                                              rect->height - DADA_PEANOS_INSET_TOP - DADA_PEANOS_INSET_BOTTOM), DADA_PEANOS_MPFR_RND);
        mpfr_mul(coord_hp[i], coord_hp[i], x->screen_domain_hp[i], DADA_PEANOS_MPFR_RND);
        if (i == 1 || i == 2)
            mpfr_sub(coord_hp[i], x->screen_end_hp[i], coord_hp[i], DADA_PEANOS_MPFR_RND);
        else
            mpfr_add(coord_hp[i], coord_hp[i], x->screen_start_hp[i], DADA_PEANOS_MPFR_RND);
        
        if (high_precision) {
            // TO DO: adjust precision automatically
            
/*            // needed precision, roughly inversely proportional to (1-coord)
            mpfr_t temp;
            mpfr_init2(temp, mpfr_get_prec(coord_hp[i]));
            mpfr_d_sub(temp, 1., coord_hp[i], DADA_PEANOS_MPFR_RND);
            mpfr_d_div(temp, 1., temp, DADA_PEANOS_MPFR_RND);
            
            mpfr_mul_d(temp, temp, DADA_PEANOS_MPFR_PRECISION_HIGH * x->bitrate/4, DADA_PEANOS_MPFR_RND);
            
            long precision = MIN(DADA_PEANOS_MPFR_PRECISION, mpfr_get_ui(temp, DADA_PEANOS_MPFR_RND) + 1);
            //        post("%ld", precision);
            mpfr_clear(temp);
            
            mpfr_set_prec(coord_hp[i], precision);
            
            // ok, now making precision better! :)
            
            mpfr_set_d(coord_hp[i], pixel.x, DADA_PEANOS_MPFR_RND);
            mpfr_div_d(coord_hp[i], coord_hp[i], rect->width, DADA_PEANOS_MPFR_RND);
            mpfr_mul(coord_hp[i], coord_hp[i], x->screen_domain_hp[i], DADA_PEANOS_MPFR_RND);
            mpfr_add(coord_hp[i], coord_hp[i], x->screen_start_hp[i], DADA_PEANOS_MPFR_RND); */
        }
    }
    
    for (int i = 0; i < 3; i++) {
        if (mpfr_cmp_d(x->coord_hp[i], 0.) < 0)
            mpfr_set_d(x->coord_hp[i], 0., DADA_PEANOS_MPFR_RND);
        
        if (mpfr_cmp_d(x->coord_hp[i], 1.) > 0)
            mpfr_set_d(x->coord_hp[i], 1., DADA_PEANOS_MPFR_RND);
    }
    
}

t_ptn peanos_coord_to_pix(t_peanos *x, t_rect *rect, mpfr_t coord_hp[3])
{
    t_ptn res;
    
    // pix = width * (coord - start_coord)/domain_coord
    mpfr_t temp;
    mpfr_init2(temp, x->mpfr_precision[0]);
    mpfr_set(temp, coord_hp[0], DADA_PEANOS_MPFR_RND);
    mpfr_sub(temp, temp, x->screen_start_hp[0], DADA_PEANOS_MPFR_RND);
    mpfr_div(temp, temp, x->screen_domain_hp[0], DADA_PEANOS_MPFR_RND);
    mpfr_mul_d(temp, temp, rect->width - DADA_PEANOS_INSET_LEFT - DADA_PEANOS_INSET_RIGHT, DADA_PEANOS_MPFR_RND);
    
    res.x = DADA_PEANOS_INSET_LEFT + mpfr_get_d(temp, DADA_PEANOS_MPFR_RND);

    mpfr_clear(temp);


    mpfr_init2(temp, x->mpfr_precision[1]);
    mpfr_set(temp, coord_hp[1], DADA_PEANOS_MPFR_RND);
    mpfr_sub(temp, temp, x->screen_start_hp[1], DADA_PEANOS_MPFR_RND);
    mpfr_div(temp, temp, x->screen_domain_hp[1], DADA_PEANOS_MPFR_RND);
    mpfr_mul_d(temp, temp, rect->height - DADA_PEANOS_INSET_TOP - DADA_PEANOS_INSET_BOTTOM, DADA_PEANOS_MPFR_RND);
    
    res.y = rect->height - DADA_PEANOS_INSET_BOTTOM - mpfr_get_d(temp, DADA_PEANOS_MPFR_RND);
    
    mpfr_clear(temp);

    
    // pix = width * (coord - start_coord)/domain_coord
    mpfr_init2(temp, x->mpfr_precision[2]);
    mpfr_set(temp, coord_hp[2], DADA_PEANOS_MPFR_RND);
    mpfr_sub(temp, temp, x->screen_start_hp[2], DADA_PEANOS_MPFR_RND);
    mpfr_div(temp, temp, x->screen_domain_hp[2], DADA_PEANOS_MPFR_RND);
    mpfr_mul_d(temp, temp, rect->height - DADA_PEANOS_INSET_TOP - DADA_PEANOS_INSET_BOTTOM, DADA_PEANOS_MPFR_RND);

    res.n = rect->height - DADA_PEANOS_INSET_BOTTOM - mpfr_get_d(temp, DADA_PEANOS_MPFR_RND);
    
    mpfr_clear(temp);

    return res;
}

void peanos_coord_to_pix_hp(t_peanos *x, t_rect *rect, mpfr_t coord_hp[3], mpfr_t pix_hp[3])
{
    // pix = width * (coord - start_coord)/domain_coord
    mpfr_set(pix_hp[0], coord_hp[0], DADA_PEANOS_MPFR_RND);
    mpfr_sub(pix_hp[0], pix_hp[0], x->screen_start_hp[0], DADA_PEANOS_MPFR_RND);
    mpfr_div(pix_hp[0], pix_hp[0], x->screen_domain_hp[0], DADA_PEANOS_MPFR_RND);
    mpfr_mul_d(pix_hp[0], pix_hp[0], rect->width - DADA_PEANOS_INSET_LEFT - DADA_PEANOS_INSET_RIGHT, DADA_PEANOS_MPFR_RND);
    mpfr_add_d(pix_hp[0], pix_hp[0], DADA_PEANOS_INSET_LEFT, DADA_PEANOS_MPFR_RND);

    mpfr_set(pix_hp[1], coord_hp[1], DADA_PEANOS_MPFR_RND);
    mpfr_sub(pix_hp[1], pix_hp[1], x->screen_start_hp[1], DADA_PEANOS_MPFR_RND);
    mpfr_div(pix_hp[1], pix_hp[1], x->screen_domain_hp[1], DADA_PEANOS_MPFR_RND);
    mpfr_mul_d(pix_hp[1], pix_hp[1], rect->height - DADA_PEANOS_INSET_TOP - DADA_PEANOS_INSET_BOTTOM, DADA_PEANOS_MPFR_RND);
    mpfr_d_sub(pix_hp[1], rect->height - DADA_PEANOS_INSET_BOTTOM, pix_hp[1], DADA_PEANOS_MPFR_RND);

    mpfr_set(pix_hp[2], coord_hp[2], DADA_PEANOS_MPFR_RND);
    mpfr_sub(pix_hp[2], pix_hp[2], x->screen_start_hp[2], DADA_PEANOS_MPFR_RND);
    mpfr_div(pix_hp[2], pix_hp[2], x->screen_domain_hp[2], DADA_PEANOS_MPFR_RND);
    mpfr_d_sub(pix_hp[2], rect->height - DADA_PEANOS_INSET_BOTTOM, pix_hp[2], DADA_PEANOS_MPFR_RND);
}




void peanos_assist(t_peanos *x, void *b, long m, long a, char *s)
{
    if (m == ASSIST_INLET) {
        if (a == 0) // @in 0 @type number/llll @digest amplitude configuration (alpha)
            sprintf(s, "number/llll: amplitude configuration (α)");
        else if (a == 1) // @in 1 @type number/llll @digest frequency shift configuration (sigma)
            sprintf(s, "number/llll: frequency shift configuration (ς)");
        else // @in 2 @type number/llll @digest noisiness configuration (xi)
            sprintf(s, "number/llll: noisiness configuration (κ)");
    }
    else {
        char *type = NULL;
        llllobj_get_llll_outlet_type_as_string((t_object *) x, LLLL_OBJ_UIMSP, a, &type);
        if (a == 0)	// @out 0 @type signal @digest Audio output
            sprintf(s, "(signal): Audio");
        else if (a == 1)	// @out 1 @type llll @digest Coordinate information
            sprintf(s, "llll (%s): Frequencies, Amplitudes, Noisinesses", type);
        else 	// @out 2 @type bang @digest bang when playhead position changes
            sprintf(s, "llll (%s): Coordinates", type);
    }
}


void peanos_bang(t_peanos *x)
{
    process_coords(x);
    output_coords(x);
    peanos_iar(x);
}

/*
double peanos_start_as_double(t_peanos *x)
{
    return mpfr_get_d(x->screen_start_hp, DADA_PEANOS_MPFR_RND);
}


double peanos_end_as_double(t_peanos *x)
{
    return mpfr_get_d(x->screen_end_hp, DADA_PEANOS_MPFR_RND);
}


double peanos_domain_as_double(t_peanos *x)
{
    return mpfr_get_d(x->screen_domain_hp, DADA_PEANOS_MPFR_RND);
}
*/

void peanos_paint(t_peanos *x, t_object *patcherview)
{
    t_dadaobj *r_ob = dadaobj_cast(x);
	t_rect rect;
    t_jgraphics *g = (t_jgraphics *) patcherview_get_jgraphics(patcherview); // obtain graphics context
    jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
    double fontsize = jbox_get_fontsize((t_object *)x);
    t_jfont *jf = jfont_create_debug(jbox_get_fontname((t_object *)x)->s_name, (t_jgraphics_font_slant)jbox_get_font_slant((t_object *)x), (t_jgraphics_font_weight)jbox_get_font_weight((t_object *)x), jbox_get_fontsize((t_object *)x));
    t_jfont *jf_greek = jfont_create_debug("Times New Roman", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, 2 * jbox_get_fontsize((t_object *)x));

    dadaobj_paint_background(r_ob, g, &rect);
    
    double innerwidth = rect.width - DADA_PEANOS_INSET_LEFT - DADA_PEANOS_INSET_RIGHT;
    double innerheight = rect.height - DADA_PEANOS_INSET_TOP - DADA_PEANOS_INSET_BOTTOM;
    
    if (x->show_spectrum) { // it's a quick'n'dirty geometrical representation, not a real spectrogram
        long num_partials = model_get_num_partials(x);
        for (long p = 0; p < num_partials; p++) {
            double amp = x->next_amps[p];
            double freq = x->next_freqs[p] * x->fzero;
            double noisiness = x->next_noisinesses[p];
            double sr = x->sr;
            if (amp > 0 && freq > 0) {
                const double HEIGHT = innerheight / 2.;
                t_jrgba color = dada_long_to_color(p);
                color.alpha = 0.2;
                double amp_wk = rescale(peanos_atodb(amp * get_gain_compensation(freq, noisiness, sr)), -12, 60, 0., 1.);
                double mc = 69 + 12. * log2(freq/440.);
                if (mc > 0 && mc < 130) {
                    double mc_base =  x->show_spectrum_from_fzero ? 69 + 12. * log2(x->fzero /440.) : 0;
                    double px = rescale(mc, mc_base, 130, DADA_PEANOS_INSET_LEFT + 1, DADA_PEANOS_INSET_LEFT + innerwidth - 2);
                    double semiwidth = rescale(pow(noisiness, 6.), 0, 1, 0, 5. * innerwidth);
                    if (noisiness > 0.999) {
                        paint_rectangle(g, color, color, DADA_PEANOS_INSET_LEFT, DADA_PEANOS_INSET_TOP + innerheight - amp_wk * HEIGHT, innerwidth, amp_wk * HEIGHT, 1);
                    } else {
                        paint_triangle(g, color, color, px - semiwidth, DADA_PEANOS_INSET_TOP + innerheight, px + semiwidth, DADA_PEANOS_INSET_TOP + innerheight, px, DADA_PEANOS_INSET_TOP + innerheight - amp_wk * HEIGHT, 1);
                    }
                }
            }
        }
    }
    
    // painting the point
    t_ptn pt = peanos_coord_to_pix(x, &rect, x->coord_hp);
    double LARGENUMBEROFPIXELS = 10000000;
    if (pt.x > LARGENUMBEROFPIXELS)
        pt.x = LARGENUMBEROFPIXELS;
    if (pt.y > LARGENUMBEROFPIXELS)
        pt.y = LARGENUMBEROFPIXELS;
    if (pt.n > LARGENUMBEROFPIXELS)
        pt.n = LARGENUMBEROFPIXELS;
    
    if (x->mousedrag_constraint == 1)
        paint_dashed_line(g, build_jrgba(0., 0., 0., 0.2), pt.x, DADA_PEANOS_INSET_TOP, pt.x, DADA_PEANOS_INSET_TOP + innerheight, 1, 6);
    if (x->mousedrag_constraint == 2)
        paint_dashed_line(g, build_jrgba(0., 0., 0., 0.2), DADA_PEANOS_INSET_LEFT, pt.y, DADA_PEANOS_INSET_LEFT + innerwidth, pt.y, 1, 6);

    paint_circle(g, build_jrgba(0., 0., 0., 0.1), build_jrgba(0., 0., 0., 0.1), pt.x, pt.y, 4., 0);
    paint_circle(g, DADA_BLACK, DADA_BLACK, pt.x, pt.y, 1.5, 1.);
//    paint_arc_stroken(g, DADA_BLACK, pt.x, pt.y, 20, 1., -PI, -PI + pt.n);
    
    // repainting borders
    paint_filledrectangle(g, DADA_WHITE, 0, 0, DADA_PEANOS_INSET_LEFT, rect.height);
    paint_filledrectangle(g, DADA_WHITE, rect.width - DADA_PEANOS_INSET_RIGHT, 0, DADA_PEANOS_INSET_RIGHT + 1, rect.height);
    paint_filledrectangle(g, DADA_WHITE, 0, 0, rect.width, DADA_PEANOS_INSET_TOP);
    paint_filledrectangle(g, DADA_WHITE, 0, rect.height - DADA_PEANOS_INSET_BOTTOM, rect.width, DADA_PEANOS_INSET_BOTTOM + 1);

    paint_strokenrectangle(g, DADA_GREY_50, DADA_PEANOS_INSET_LEFT, DADA_PEANOS_INSET_TOP, innerwidth, innerheight, 1);

    
    // NOISINESS BAR
    double NNESS_LEFT = rect.width - DADA_PEANOS_INSET_RIGHT_NOISINESS;
    double NNESS_WIDTH = DADA_PEANOS_UI_NOISINESS_WIDTH;
    
    paint_strokenrectangle(g, DADA_GREY_50, NNESS_LEFT, DADA_PEANOS_INSET_TOP, NNESS_WIDTH, innerheight, 1);

    if (pt.n <= rect.height - DADA_PEANOS_INSET_BOTTOM) {
        if (pt.n < rect.height - DADA_PEANOS_INSET_BOTTOM)
            paint_filledrectangle(g, DADA_GREY_25, NNESS_LEFT, pt.n, NNESS_WIDTH, rect.height - DADA_PEANOS_INSET_BOTTOM - pt.n);
        paint_filledrectangle(g, DADA_BLACK, NNESS_LEFT, pt.n-1.5, NNESS_WIDTH, 3);
    }
    
    // yet again
    paint_filledrectangle(g, DADA_WHITE, 0, 0, rect.width, DADA_PEANOS_INSET_TOP);

    
    
    // ZOOM POSITIONS
    // power 10
    mpfr_t screen_middle[3];
    mpfr_t temp, exponent;
    double zoombar_pos[3];
    double zoombar_halfwidth[3][5];
    for (int i = 0; i < 3; i++) {
        mpfr_init2(temp, x->mpfr_precision[i]);
        mpfr_init2(exponent, x->mpfr_precision[i]);
        mpfr_init2(screen_middle[i], x->mpfr_precision[i]);
        mpfr_set(screen_middle[i], x->screen_start_hp[i], DADA_PEANOS_MPFR_RND);
        mpfr_add(screen_middle[i], screen_middle[i], x->screen_end_hp[i], DADA_PEANOS_MPFR_RND);
        mpfr_div_ui(screen_middle[i], screen_middle[i], 2, DADA_PEANOS_MPFR_RND);
        zoombar_pos[i] = mpfr_get_d(screen_middle[i], DADA_PEANOS_MPFR_RND);
        
        for (int j = 0; j < 5; j++) {
            mpfr_set(temp, x->screen_domain_hp[i], DADA_PEANOS_MPFR_RND);
            mpfr_set_ui(exponent, 10, DADA_PEANOS_MPFR_RND);
            mpfr_pow_ui(exponent, exponent, j, DADA_PEANOS_MPFR_RND);
            mpfr_ui_div(exponent, 1, exponent, DADA_PEANOS_MPFR_RND);
            mpfr_pow(temp, temp, exponent, DADA_PEANOS_MPFR_RND);
            zoombar_halfwidth[i][j] = mpfr_get_d(temp, DADA_PEANOS_MPFR_RND)/2.;
        }
        mpfr_clear(temp);
        mpfr_clear(exponent);
    }
    /*
    paint_rectangle(g, build_jrgba(0, 0, 0, 1), build_jrgba(0, 0, 0, 0.1),
                    DADA_PEANOS_INSET_LEFT + innerwidth * (zoombar_pos[0] - zoombar_halfwidth[0]),
                    rect.height - DADA_PEANOS_INSET_BOTTOM, innerwidth * 2 * zoombar_halfwidth[0], 4, 0);
    paint_rectangle(g, build_jrgba(0, 0, 0, 1), build_jrgba(0, 0, 0, 0.1),
                    DADA_PEANOS_INSET_LEFT - 4, DADA_PEANOS_INSET_TOP + innerheight * (zoombar_pos[1] - zoombar_halfwidth[1]),
                    4, innerheight * 2 * zoombar_halfwidth[1], 0);
    paint_rectangle(g, build_jrgba(0, 0, 0, 1), build_jrgba(0, 0, 0, 0.1),
                    NNESS_LEFT + NNESS_WIDTH, DADA_PEANOS_INSET_TOP + innerheight * (zoombar_pos[2] - zoombar_halfwidth[2]),
                    4, innerheight * 2 * zoombar_halfwidth[2], 0);
    */

    for (int j = 0; j < 5; j++) {
        double alpha = 0.3 * pow(1. - j / 4., 1.);
        double left_pos;
        left_pos = MAX(0, zoombar_pos[0] - zoombar_halfwidth[0][j]);
        paint_rectangle(g, build_jrgba(0, 0, 0, 1), build_jrgba(0, 0, 0, alpha),
                        DADA_PEANOS_INSET_LEFT + innerwidth * left_pos,
                        rect.height - DADA_PEANOS_INSET_BOTTOM, MAX(1, innerwidth * MIN(1-left_pos, 2 * zoombar_halfwidth[0][j])), 4, 0);
        left_pos = MAX(0, (1 - zoombar_pos[1]) - zoombar_halfwidth[1][j]);
        paint_rectangle(g, build_jrgba(0, 0, 0, 1), build_jrgba(0, 0, 0, alpha),
                        DADA_PEANOS_INSET_LEFT - 4, DADA_PEANOS_INSET_TOP + innerheight * left_pos,
                        4, MAX(1, innerheight * MIN(1-left_pos, 2 * zoombar_halfwidth[1][j])), 0);
        left_pos = MAX(0, (1 - zoombar_pos[2]) - zoombar_halfwidth[2][j]);
        paint_rectangle(g, build_jrgba(0, 0, 0, 1), build_jrgba(0, 0, 0, alpha),
                        NNESS_LEFT + NNESS_WIDTH, DADA_PEANOS_INSET_TOP + innerheight * left_pos,
                        4, MAX(1, innerheight * MIN(1-left_pos, 2 * zoombar_halfwidth[2][j])), 0);
    }
    
    for (int i = 0; i < 3; i++)
        mpfr_clear(screen_middle[i]);

    
    // LEGENDS
    long MCx = MIN(40, innerwidth/(15. * (fontsize/8.)));
    long MCy = MIN(40, innerheight/(15. * (fontsize/8.)));
    char *text1 = peanos_mpfr_get_str(10, MCx, x->screen_start_hp[0], DADA_PEANOS_MPFR_RND, MCx, true);
    char *text2 = peanos_mpfr_get_str(10, MCx, x->screen_end_hp[0], DADA_PEANOS_MPFR_RND, MCx, true);
    char *text3 = peanos_mpfr_get_str(10, MCy, x->screen_start_hp[1], DADA_PEANOS_MPFR_RND, MCy, true);
    char *text4 = peanos_mpfr_get_str(10, MCy, x->screen_end_hp[1], DADA_PEANOS_MPFR_RND, MCy, true);
    char *text5 = peanos_mpfr_get_str(10, MCy, x->screen_start_hp[2], DADA_PEANOS_MPFR_RND, MCy, true);
    char *text6 = peanos_mpfr_get_str(10, MCy, x->screen_end_hp[2], DADA_PEANOS_MPFR_RND, MCy, true);

    // LEGEND ALPHA
    {
        write_text(g, jf_greek, DADA_GREY_25, "α", DADA_PEANOS_INSET_LEFT, rect.height - DADA_PEANOS_INSET_BOTTOM + 4, innerwidth, DADA_PEANOS_INSET_BOTTOM - 4, JGRAPHICS_TEXT_JUSTIFICATION_HCENTERED | JGRAPHICS_TEXT_JUSTIFICATION_TOP, true, false);
        
        write_text(g, jf, DADA_GREY_50, text1, DADA_PEANOS_INSET_LEFT, rect.height - DADA_PEANOS_INSET_BOTTOM + 8, innerwidth / 2, DADA_PEANOS_INSET_BOTTOM - 4, JGRAPHICS_TEXT_JUSTIFICATION_LEFT | JGRAPHICS_TEXT_JUSTIFICATION_TOP, true, false);
        write_text(g, jf, DADA_GREY_50, text2, DADA_PEANOS_INSET_LEFT + innerwidth / 2., rect.height - DADA_PEANOS_INSET_BOTTOM + 8, innerwidth / 2., DADA_PEANOS_INSET_BOTTOM - 4, JGRAPHICS_TEXT_JUSTIFICATION_RIGHT | JGRAPHICS_TEXT_JUSTIFICATION_TOP, true, false);
    }

    
    /// LEGENDA SIGMA
    {
        jgraphics_set_source_rgba(g, 0, 0, 0, 1);   // setting alpha to 1 otherwise we have blending issues
        double inset = DADA_PEANOS_INSET_LEFT - 8;
        t_jsurface *forverticallegend = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, 2 * rect.height, 2 * inset);
        t_jsurface *verticallegend = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, 2 * inset, 2 * rect.height);
        t_jgraphics *g_forverticallegend = jgraphics_create(forverticallegend);
        t_jfont *jf2 = jfont_create_debug(jbox_get_fontname((t_object *)x)->s_name, (t_jgraphics_font_slant)jbox_get_font_slant((t_object *)x), (t_jgraphics_font_weight)jbox_get_font_weight((t_object *)x), 2 * jbox_get_fontsize((t_object *)x));
        t_jfont *jf_greek2 = jfont_create_debug("Times New Roman", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, 2 * 2 * jbox_get_fontsize((t_object *)x));
        
        write_text(g_forverticallegend, jf_greek2, DADA_GREY_25, "ς", 2 * DADA_PEANOS_INSET_BOTTOM, 0, 2 * innerheight, 2 * inset, JGRAPHICS_TEXT_JUSTIFICATION_HCENTERED | JGRAPHICS_TEXT_JUSTIFICATION_VCENTERED, true, false);
        
        write_text(g_forverticallegend, jf2, DADA_GREY_50, text3, 2 * DADA_PEANOS_INSET_BOTTOM, 4, 2 * innerheight/2, 2 * inset, JGRAPHICS_TEXT_JUSTIFICATION_LEFT | JGRAPHICS_TEXT_JUSTIFICATION_BOTTOM, true, false);
        write_text(g_forverticallegend, jf2, DADA_GREY_50, text4, 2 * (DADA_PEANOS_INSET_BOTTOM + innerheight/2.), 4, 2 * innerheight/2, 2 * inset, JGRAPHICS_TEXT_JUSTIFICATION_RIGHT | JGRAPHICS_TEXT_JUSTIFICATION_BOTTOM, true, false);
        
        t_jrgba color;
        for (long i = 0; i < 2 * inset; i++) {
            for (long j = 0; j < 2 * rect.height; j++) {
                jgraphics_image_surface_get_pixel(forverticallegend, j, i, &color);
                jgraphics_image_surface_set_pixel(verticallegend, i, 2*rect.height - j, color);
            }
        }
        jfont_destroy(jf2);
        jfont_destroy(jf_greek2);
        jgraphics_destroy(g_forverticallegend);
        jgraphics_image_surface_draw(g, verticallegend, build_rect(0, 0, 2*inset, 2*rect.height), build_rect(0, 0, inset, rect.height));
        jgraphics_surface_destroy(forverticallegend);
        jgraphics_surface_destroy(verticallegend);
    }
    

    /// LEGENDA KAPPA
    {
        jgraphics_set_source_rgba(g, 0, 0, 0, 1);   // setting alpha to 1 otherwise we have blending issues
        double inset = DADA_PEANOS_INSET_LEFT - 8;
        t_jsurface *forverticallegend = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, 2 * rect.height, 2 * inset);
        t_jsurface *verticallegend = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, 2 * inset, 2 * rect.height);
        t_jgraphics *g_forverticallegend = jgraphics_create(forverticallegend);
        t_jfont *jf2 = jfont_create_debug(jbox_get_fontname((t_object *)x)->s_name, (t_jgraphics_font_slant)jbox_get_font_slant((t_object *)x), (t_jgraphics_font_weight)jbox_get_font_weight((t_object *)x), 2 * jbox_get_fontsize((t_object *)x));
        t_jfont *jf_greek2 = jfont_create_debug("Times New Roman", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, 2 * 2 * jbox_get_fontsize((t_object *)x));
        
        write_text(g_forverticallegend, jf_greek2, DADA_GREY_25, "κ", 2 * DADA_PEANOS_INSET_TOP, 0, 2 * innerheight, 2 * inset, JGRAPHICS_TEXT_JUSTIFICATION_HCENTERED | JGRAPHICS_TEXT_JUSTIFICATION_VCENTERED, true, false);
        
        write_text(g_forverticallegend, jf2, DADA_GREY_50, text6, 2 * DADA_PEANOS_INSET_TOP, 0, 2 * innerheight/2, 2 * inset, JGRAPHICS_TEXT_JUSTIFICATION_LEFT | JGRAPHICS_TEXT_JUSTIFICATION_BOTTOM, true, false);
        write_text(g_forverticallegend, jf2, DADA_GREY_50, text5, 2 * (DADA_PEANOS_INSET_TOP + innerheight/2.), 0, 2 * innerheight/2, 2 * inset, JGRAPHICS_TEXT_JUSTIFICATION_RIGHT | JGRAPHICS_TEXT_JUSTIFICATION_BOTTOM, true, false);
        
        t_jrgba color;
        for (long i = 0; i < 2 * inset; i++) {
            for (long j = 0; j < 2 * rect.height; j++) {
                jgraphics_image_surface_get_pixel(forverticallegend, j, i, &color);
                jgraphics_image_surface_set_pixel(verticallegend, 2 * inset - i, j, color);
            }
        }
        jfont_destroy(jf2);
        jfont_destroy(jf_greek2);
        jgraphics_destroy(g_forverticallegend);
        jgraphics_image_surface_draw(g, verticallegend, build_rect(0, 0, 2*inset, 2*rect.height), build_rect(NNESS_LEFT + NNESS_WIDTH+4, 0, inset, rect.height));
        jgraphics_surface_destroy(forverticallegend);
        jgraphics_surface_destroy(verticallegend);
    }
    
    bach_freeptr(text1);
    bach_freeptr(text2);
    bach_freeptr(text3);
    bach_freeptr(text4);
    bach_freeptr(text5);
    bach_freeptr(text6);
    
    // LEGEND
    if (x->show_legend) {
        long MC = MIN(x->legend_num_digits, innerwidth/(5.1 * (fontsize/8.)) - 3);
        char *text_coord0 = peanos_mpfr_get_str(10, MC, x->coord_hp[0], DADA_PEANOS_MPFR_RND, MC, false);
        char *text_coord1 = peanos_mpfr_get_str(10, MC, x->coord_hp[1], DADA_PEANOS_MPFR_RND, MC, false);
        char *text_coord2 = peanos_mpfr_get_str(10, MC, x->coord_hp[2], DADA_PEANOS_MPFR_RND, MC, false);
        char text_coords[2048];
        snprintf_zero(text_coords, 2048, "α = %s\nς = %s\nκ = %s", text_coord0, text_coord1, text_coord2);
        write_text(g, jf, DADA_GREY_50, text_coords, DADA_PEANOS_INSET_LEFT, DADA_PEANOS_INSET_TOP, innerwidth, innerheight, JGRAPHICS_TEXT_JUSTIFICATION_RIGHT | JGRAPHICS_TEXT_JUSTIFICATION_TOP, false, false);
        
        bach_freeptr(text_coord0);
        bach_freeptr(text_coord1);
        bach_freeptr(text_coord2);
    }

    
    
    dadaobj_paint_border(r_ob, g, &rect);
    
    jfont_destroy_debug(jf);
}


t_atom_long peanos_acceptsdrag(t_peanos *x, t_object *drag, t_object *view)
{
    return false;
}

void peanos_redraw_do(t_peanos *x, t_symbol *msg, long ac, t_atom *av)
{
    jbox_redraw((t_jbox *)x);
}

void peanos_post_array_do(t_peanos *x, t_symbol *msg, long ac, t_atom *av)
{
    long size;
    char *text = NULL;
    atom_gettext(ac, av, &size, &text, 0);
    post("%s", text);
    sysmem_freeptr(text);
}

void peanos_post_array(t_peanos *x, long num_elems, double *elems)
{
#ifdef MAC_VERSION
#ifdef DADA_PEANOS_DEBUG
    if (x->dsp_debug) {
        t_atom a[num_elems];
        long i;
        for (i = 0; i < num_elems; i++)
            atom_setfloat(a+i, elems[i]);
        defer_low(x, (method)peanos_post_array_do, NULL, num_elems, a);
    }
#endif
#endif
}


double lininterp(double start, double end, long i, long numsteps, bool *done)
{
    if (i >= numsteps - 1) {
        *done = true;
        return end; // done
    }
    return start + (end - start) * (double)i/(numsteps-1);
}

long model_get_num_partials(t_peanos *x)
{
    return x->num_partials + (x->model == 1 ? 3 : 0);
}

void peanos_clear(t_peanos *x)
{
    long np = model_get_num_partials(x);
    for (long i = 0; i < np; i++) {
        x->mem_ff1[i] = x->mem_ff2[i] = 0;
        x->mem_fb1[i] = x->mem_fb2[i] = 0;
    }
}


double biquad_apply(double sample, t_biquad_coeffs *coeffs, double *ff1, double *ff2, double *fb1, double *fb2)
{
    double res = sample * coeffs->b0 + (*ff1) * coeffs->b1 + (*ff2) * coeffs->b2 - (*fb1) * coeffs->a1 - (*fb2) * coeffs->a2;
    *ff2 = *ff1;
    *fb2 = *fb1;
    *ff1 = sample;
    *fb1 = res;
    return res;
}

void biquad_coefficients_from_params(double cutoff_freq, double amp, double Q, double sr, t_biquad_coeffs *coeffs)
{
    if (Q == 0) {
        double epsilon = 0.001;
        coeffs->a1 = amp-epsilon;
        coeffs->a2 = 0.;
        coeffs->b0 = -(amp-epsilon);
        coeffs->b1 = -0.001039;
        coeffs->b2 = -0.998887;
    } else {
        if (Q == sr/2.)
            Q = sr/2.00001;
        if (cutoff_freq == 0) {
            amp = 0;
            cutoff_freq = 20;
        }
        double w0 = 2*PI*cutoff_freq/sr;
        double alpha = sin(w0)/(2*Q);
        double alpha_plus_one = (1 + alpha);
        coeffs->a1 = -2 * cos(w0) / alpha_plus_one;
        coeffs->a2 = (1 - alpha) / alpha_plus_one;
        coeffs->b0 = alpha * amp / alpha_plus_one;
        coeffs->b1 = 0;
        coeffs->b2 = -alpha * amp / alpha_plus_one;
    }
}


double noisiness_to_q(double noisiness, double sr, double exponent)
{
    return pow(1.-noisiness, exponent)*(sr/2.);
}

double peanos_dbtoa(float db)
{
    return pow(10, db/20.);
}

double peanos_atodb(double a)
{
    return 20 * log10(a);
}

double get_gain_compensation(double freq, double noisiness, double sr)
{
// using gain compensation table
    int intf = (int)((round(freq) * 44100./sr) - 1);
    int intn = (int)(round(noisiness*100));
    if (intf < 22049 && intn < 101)
        return peanos_dbtoa(-bandpass_gains[intf][intn]);
    else
        return 0.;
}

void get_split_gains(char synthesis_mode, double noisiness, double freq, double sr, double *sine_gain, double *noise_gain)
{
    if (synthesis_mode == 1) {
        *sine_gain = sqrt(1 - noisiness);
        *noise_gain = sqrt(2 * noisiness);
    } else {
        if (noisiness <= 0.) {
            *sine_gain = 1;
            *noise_gain = 0;
        } else if (noisiness <= 0.3) {
            *sine_gain = (1 - noisiness/0.3);
            *sine_gain *= *sine_gain;
            *noise_gain = sqrt(1 - *sine_gain * *sine_gain) * get_gain_compensation(freq, noisiness, sr);
        } else {
            *sine_gain = 0;
            *noise_gain = get_gain_compensation(freq, noisiness, sr);
        }
    }
}

void peanos_perform64(t_peanos *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    if (x->must_change_numpartials > 0) {
        peanos_change_numpartials_do(x, x->must_change_numpartials);
        x->must_change_numpartials = -1;
    }

    if (x->must_change_model >= 0) {
        peanos_change_model_do(x, x->must_change_model);
        x->must_change_model = -1;
    }

    t_double	*out = outs[0];
    long np = model_get_num_partials(x);
    
    assert(np < DADA_PEANOS_MAXPARTIALS);
    
    double *phases = x->phases;
    double *mem_ff1 = x->mem_ff1;
    double *mem_ff2 = x->mem_ff2;
    double *mem_fb1 = x->mem_fb1;
    double *mem_fb2 = x->mem_fb2;
    double timestep = x->timestep;
    double global_gain = 0.0625;
    char mode = x->mode;
    char use_lookup_table = x->use_lookup_table;
    char must_interp = x->must_interp;
    char synthesis_mode = x->synthesis_mode;
    bool autoclear_filters = x->autoclear_filters;
    double sr = x->sr;
    double fzero = x->fzero;
    double noisinessToQexponent = x->noisiness_to_q_exp;
    long interp_freq_samps, interp_amp_samps, interp_noisiness_samps, interp_freq_samps_offset, interp_amp_samps_offset, interp_noisiness_samps_offset;
    
    if (numouts < 1)
        return;
    
    // Beware, for Max ins[2] coincides with outs[0]
    
    if (mode == 1) { // passive
        interp_freq_samps = interp_amp_samps = interp_noisiness_samps = sampleframes;
        interp_freq_samps_offset = interp_amp_samps_offset = interp_noisiness_samps_offset = 0;
        process_coords(x);
    } else {
        if (x->must_process_coords_when_interp_has_ended && !x->must_interp) {
            process_coords(x);
            peanos_iar(x);
        }
        interp_freq_samps = x->interp_freq_samps;
        interp_amp_samps = x->interp_amp_samps;
        interp_noisiness_samps = x->interp_noisiness_samps;
        interp_freq_samps_offset = x->interp_freq_samps_offset;
        interp_amp_samps_offset = x->interp_amp_samps_offset;
        interp_noisiness_samps_offset = x->interp_noisiness_samps_offset;
    }
    
    double freq, amp, noisiness; // = ins[2][0];
    bool interp_freq_done = false, interp_amp_done = false, interp_noisiness_done = false;
    double b1, a0;
    double noise_gain, sine_gain;
    t_biquad_coeffs coeffs;
    
    for (int i = 0; i < sampleframes; i++)
        out[i] = 0.;

    for (long p = 0; p < np; p++) {
        if (!must_interp) {
            freq = x->curr_freqs[p] * fzero;
            amp = x->curr_amps[p];
            noisiness = x->curr_noisinesses[p];
            get_split_gains(synthesis_mode, noisiness, freq, sr, &sine_gain, &noise_gain);
            if (synthesis_mode == 1) {
                b1 = exp(-2.0 * PI * (pow(noisiness, 2.)/2));
                a0 = 1.0 - b1;
            } else {
                biquad_coefficients_from_params(freq, amp, noisiness_to_q(noisiness, sr, noisinessToQexponent), sr, &coeffs);
            }
        }
        
        for (int i = 0; i < sampleframes; i++) {
            if (must_interp) {
                freq = lininterp(x->curr_freqs[p] * fzero, x->next_freqs[p] * fzero, interp_freq_samps_offset + i, interp_freq_samps, &interp_freq_done);
                amp = lininterp(x->curr_amps[p], x->next_amps[p], interp_amp_samps_offset + i, interp_amp_samps, &interp_amp_done);
                noisiness = lininterp(x->curr_noisinesses[p], x->next_noisinesses[p], interp_noisiness_samps_offset + i, interp_noisiness_samps, &interp_noisiness_done);
                get_split_gains(synthesis_mode, noisiness, freq, sr, &sine_gain, &noise_gain);
                if (autoclear_filters)
                    peanos_clear(x);
                if (synthesis_mode == 1) {
                    b1 = exp(-2.0 * PI * (pow(noisiness, 2.)/2)); // equivalent to: cutoff_freq = pow(noisiness, 2.)*sr/2
                    a0 = 1.0 - b1;
                } else {
                    biquad_coefficients_from_params(freq, amp, noisiness_to_q(noisiness, sr, noisinessToQexponent), sr, &coeffs);
                }
            }
            
            phases[p] += freq * timestep;
            while (phases[p] >= TWOPI) phases[p] -= TWOPI;
            
            if (freq > 0 && freq < sr/2.) {
                double sinusoid;
                if (use_lookup_table) {
                    double phmap = phases[p] * DADA_PEANOS_SIN_TABLE_SIZE / TWOPI;
                    int i1 = (int)phmap;
                    double res = phmap - i1;
                    int i2 = i1+1;
                    sinusoid = (1 - res) * sin_table[i1] + res * sin_table[i2];
                } else {
                    sinusoid = sin(phases[p]);
                }
                
                double whitenoise = 2 * (double)rand()/RAND_MAX - 1;
                double filterednoise;
                
                if (synthesis_mode == 1) {
                    // two passages of a 1-st order lowpass
                    filterednoise =  whitenoise * a0 + mem_ff1[p] * b1;
                    mem_ff1[p] = filterednoise;
                    filterednoise =  filterednoise * a0 + mem_ff2[p] * b1;
                    mem_ff2[p] = filterednoise;
                    
                    out[i] += global_gain * amp * (sine_gain + noise_gain * filterednoise) * sinusoid;
                } else { // additive synth + filtered noise via biquad
                    filterednoise = noisiness == 1 ? whitenoise : biquad_apply(whitenoise, &coeffs, mem_ff1+p, mem_ff2+p, mem_fb1+p, mem_fb2+p);
                    out[i] += global_gain * amp * (sine_gain * sinusoid + noise_gain * filterednoise);
                }
            }
        }
    }
    
    if (must_interp) {
        if (interp_amp_done) {
            for (long p = 0; p < np; p++)
                x->curr_amps[p] = x->next_amps[p];
        } else {
            x->interp_amp_samps_offset += sampleframes;
        }
        if (interp_freq_done) {
            for (long p = 0; p < np; p++)
                x->curr_freqs[p] = x->next_freqs[p];
        } else {
            x->interp_freq_samps_offset += sampleframes;
        }
        if (interp_noisiness_done) {
            for (long p = 0; p < np; p++)
                x->curr_noisinesses[p] = x->next_noisinesses[p];
        } else {
            x->interp_noisiness_samps_offset += sampleframes;
        }
        if (interp_amp_done && interp_freq_done && interp_noisiness_done) {
            x->interp_freq_samps_offset = 0;
            x->interp_amp_samps_offset = 0;
            x->interp_noisiness_samps_offset = 0;
            x->must_interp = false;
        }
    }

#ifdef DENORM_WANT_FIX
    for (int i = 0; i < sampleframes; i++)
        out[i] = FIX_DENORM_NAN_DOUBLE(out[i]);
#endif
    
}

void peanos_dsp64(t_peanos *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    if (x->sr != samplerate) {
        x->sr = samplerate;
        x->timestep = TWOPI * 1./x->sr;
//        reset_coords_to_zero(x, true);
    }
    object_method(dsp64, gensym("dsp_add64"), x, peanos_perform64, 0, NULL);
}


void peanos_anything(t_peanos *x, t_symbol *msg, long ac, t_atom *av)
{
    dadaobj_anything(dadaobj_cast(x), msg, ac, av);
    
    t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, msg, ac, av, LLLL_PARSE_CLONE);
    if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
        t_symbol *router = hatom_getsym(&parsed->l_head->l_hatom);
        llll_behead(parsed);
        
//        if (dadaobj_anything_handle_domain_or_range(dadaobj_cast(x), router, parsed, 1)) {
            // nothing to do! we handle this natively...
/*        } else if (router == gensym("zoomby") && parsed->l_head) {
            double factor = hatom_getdouble(&parsed->l_head->l_hatom);
            
            t_llllelem *center_el = parsed->l_head->l_next;
            if (center_el && hatom_gettype(&center_el->l_hatom) == H_SYM && hatom_getsym(&center_el->l_hatom) == _llllobj_sym_cursor) // zoom around cursor
                peanos_zoom_by_hp(x, factor, x->mousedowncoord_hp);
            else if (center_el && is_hatom_number(&center_el->l_hatom)) // zoom around specific point
                peanos_zoom_by(x, factor, hatom_getdouble(&center_el->l_hatom));
            else { // zoom around domain center
                mpfr_t temp;
                mpfr_init2(temp, x->mpfr_precision);
                mpfr_set(temp, x->screen_domain_hp, DADA_PEANOS_MPFR_RND);
                mpfr_mul_d(temp, temp, 0.5, DADA_PEANOS_MPFR_RND);
                mpfr_add(temp, temp, x->screen_start_hp, DADA_PEANOS_MPFR_RND);
                peanos_zoom_by_hp(x, factor, temp);
                mpfr_clear(temp);
            }
            jbox_redraw((t_jbox *)x);
            
        } else if (router == gensym("zoomexp") && parsed->l_head) {
            mpfr_t exponent;
            mpfr_init2(exponent, x->mpfr_precision);
            mpfr_set_d(exponent, hatom_getdouble(&parsed->l_head->l_hatom), DADA_PEANOS_MPFR_RND);
            
            t_llllelem *center_el = parsed->l_head->l_next;
            if (center_el && hatom_gettype(&center_el->l_hatom) == H_SYM && hatom_getsym(&center_el->l_hatom) == _llllobj_sym_cursor) // zoom around cursor
                peanos_zoom_exp_hp(x, exponent, x->mousedowncoord_hp);
            else if (center_el && is_hatom_number(&center_el->l_hatom)) { // zoom around specific point
                mpfr_t temp;
                mpfr_init2(temp, x->mpfr_precision);
                mpfr_set_d(temp, hatom_getdouble(&center_el->l_hatom), DADA_PEANOS_MPFR_RND);
                peanos_zoom_exp_hp(x, exponent, temp);
                mpfr_clear(temp);
            } else { // zoom around domain center
                mpfr_t temp;
                mpfr_init2(temp, x->mpfr_precision);
                mpfr_set(temp, x->screen_domain_hp, DADA_PEANOS_MPFR_RND);
                mpfr_mul_d(temp, temp, 0.5, DADA_PEANOS_MPFR_RND);
                mpfr_add(temp, temp, x->screen_start_hp, DADA_PEANOS_MPFR_RND);
                peanos_zoom_exp_hp(x, exponent, temp);
                mpfr_clear(temp);
            }
            
            mpfr_clear(exponent);
            jbox_redraw((t_jbox *)x); */
        if (router == gensym("setstoredstate") || router == gensym("peanos")) {
//            peanos_undo_step_push(x, gensym("Set State"));
            peanos_set_state(x, parsed);
        } else if (router == gensym("coords") || router == gensym("setcoords")) {
            if (parsed->l_size == 3) {
                t_llllelem *el = parsed->l_head;
                for (int i = 0; i < 3 && el; i++) {
                    if (hatom_gettype(&el->l_hatom) == H_SYM) {
                        t_symbol *s = hatom_getsym(&el->l_hatom);
                        mpfr_set_str(x->coord_hp[i], s->s_name, 10, DADA_PEANOS_MPFR_RND);
                    } else if (hatom_gettype(&el->l_hatom) == H_RAT) {
                        t_rational r = hatom_getrational(&el->l_hatom);
                        mpfr_set_ui(x->coord_hp[i], r.r_num, DADA_PEANOS_MPFR_RND);
                        mpfr_div_ui(x->coord_hp[i], x->coord_hp[i], r.r_den, DADA_PEANOS_MPFR_RND);
                    } else {
                        mpfr_set_d(x->coord_hp[i], hatom_getdouble(&el->l_hatom), DADA_PEANOS_MPFR_RND);
                    }
                    el = el->l_next;
                }
                process_coords(x);
                if (router == gensym("coords"))
                    output_coords(x);
                jbox_redraw((t_jbox *)x);
            } else {
                object_error((t_object *)x, "Wrong input syntax.");
            }
        } else if (router == gensym("move")) {
            if (parsed->l_size == 3) {
                t_llllelem *el = parsed->l_head;
                for (int i = 0; i < 3 && el; i++) {
                    if (hatom_gettype(&el->l_hatom) == H_LLLL) {
                        t_llll *ll = hatom_getllll(&el->l_hatom);
                        if (ll && ll->l_size >= 2) {
                            double d = hatom_getdouble(&ll->l_head->l_hatom);
                            long exponent = hatom_getlong(&ll->l_head->l_next->l_hatom);
                            mpfr_t temp, tempexp;
                            mpfr_init2(temp, x->mpfr_precision[i]);
                            mpfr_init2(tempexp, x->mpfr_precision[i]);
                            mpfr_set_d(temp, d, DADA_PEANOS_MPFR_RND);
                            mpfr_set_ui(tempexp, exponent, DADA_PEANOS_MPFR_RND);
                            mpfr_ui_pow_ui(tempexp, 10, exponent, DADA_PEANOS_MPFR_RND);
                            mpfr_mul(temp, temp, tempexp, DADA_PEANOS_MPFR_RND);
                            mpfr_add(x->coord_hp[i], x->coord_hp[i], temp, DADA_PEANOS_MPFR_RND);
                            mpfr_clear(temp);
                            mpfr_clear(tempexp);
                        }
                    } else if (hatom_gettype(&el->l_hatom) == H_SYM) {
                        t_symbol *s = hatom_getsym(&el->l_hatom);
                        mpfr_t temp;
                        mpfr_init2(temp, x->mpfr_precision[i]);
                        mpfr_set_str(temp, s->s_name, 10, DADA_PEANOS_MPFR_RND);
                        mpfr_add(x->coord_hp[i], x->coord_hp[i], temp, DADA_PEANOS_MPFR_RND);
                        mpfr_clear(temp);
                    } else if (hatom_gettype(&el->l_hatom) == H_RAT) {
                        t_rational r = hatom_getrational(&el->l_hatom);
                        mpfr_t temp;
                        mpfr_init2(temp, x->mpfr_precision[i]);
                        mpfr_set_ui(temp, r.r_num, DADA_PEANOS_MPFR_RND);
                        mpfr_div_ui(temp, temp, r.r_den, DADA_PEANOS_MPFR_RND);
                        mpfr_add(x->coord_hp[i], x->coord_hp[i], temp, DADA_PEANOS_MPFR_RND);
                        mpfr_clear(temp);
                    } else {
                        mpfr_add_d(x->coord_hp[i], x->coord_hp[i], hatom_getdouble(&el->l_hatom), DADA_PEANOS_MPFR_RND);
                    }
                    el = el->l_next;
                }
                process_coords(x);
                if (router == gensym("coords"))
                    output_coords(x);
                jbox_redraw((t_jbox *)x);
            } else {
                object_error((t_object *)x, "Wrong input syntax.");
            }
        }
        llll_free(parsed);
    }
}

void peanos_iar(t_peanos *x)
{
    jbox_redraw((t_jbox *)x);
}

char *peanos_mpfr_get_str(int base, size_t size, mpfr_srcptr num_hp, mpfr_rnd_t rounding, size_t cut_to_this_size, bool trim_ending_zeros)
{
    mpfr_exp_t exponent = 0;
    char *num_str = mpfr_get_str(NULL, &exponent, base, 0 /*size*/, num_hp, rounding);
    char use_ellipsis = false;
    
    if (cut_to_this_size > 0 && cut_to_this_size < size) {
        use_ellipsis = true;
    }
    
    long len = strlen(num_str);

    char *res = (char *)bach_newptr((len + exponent + 4) * sizeof(char)); // + 4 is :
    res[0] = 0;
    
    if (exponent > 0) { // won't need anything with exp > 1
        char *pre = (char *)bach_newptr((exponent + 1) * sizeof(char));
        for (long i = 0; i < exponent && i < len; i++)
            pre[i] = num_str[i];
        pre[exponent] = 0;
        snprintf_zero(res, len + exponent + 4, "%s.%s", pre, num_str+exponent);
        bach_freeptr(pre);
    } else if (exponent <= 0) {
        exponent *= -1;
        char *pre_zeros = (char *)bach_newptr((exponent + 1) * sizeof(char));
        for (long i = 0; i < exponent; i++)
            pre_zeros[i] = '0';
        pre_zeros[exponent] = 0;
        snprintf_zero(res, len + exponent + 4, "0.%s%s", pre_zeros, num_str);
        bach_freeptr(pre_zeros);
    }

    if (size > 0 && size < (len + exponent + 1))
        res[size] = 0;
    
    if (trim_ending_zeros) {
        long l = strlen(res);
        for (int i = l-1; i > 0; i--) {
            if (res[i] == '0')
                res[i] = 0;
            else
                break;
        }
    }

    if (use_ellipsis && cut_to_this_size < (len + exponent + 1)) {
        res[cut_to_this_size] = res[cut_to_this_size+1] = res[cut_to_this_size+2] = '.';
        res[cut_to_this_size+3] = 0;
    }
    

    mpfr_free_str(num_str);
    return res;
}

////// INTERFACE


void peanos_focusgained(t_peanos *x, t_object *patcherview)
{
    if (dadaobj_focusgained(dadaobj_cast(x), patcherview))
        return;
}

void peanos_focuslost(t_peanos *x, t_object *patcherview)
{
    if (dadaobj_focuslost(dadaobj_cast(x), patcherview))
        return;
}

void peanos_mousemove(t_peanos *x, t_object *patcherview, t_pt pt, long modifiers)
{
    
    llll_format_modifiers(&modifiers, NULL);

    long mousedrag_constraint = 0;
    if (modifiers & eShiftKey && modifiers & eAltKey) {
        mousedrag_constraint = 1;
    } else if (modifiers & eShiftKey) {
        mousedrag_constraint = 2;
    } else {
        mousedrag_constraint = 0;
    }
    
    if (mousedrag_constraint != x->mousedrag_constraint) {
        x->mousedrag_constraint = mousedrag_constraint;
        peanos_iar(x);
    }

        
    if (dadaobj_mousemove(dadaobj_cast(x), patcherview, pt, modifiers))
        return;
    

    
    /*
    x->legend[0] = 0;
    if (x->b_ob.d_ob.m_interface.allow_mouse_hover) {
        if (!x->b_ob.d_ob.m_interface.mouse_is_down) {
            unsigned long numsamps = 0;
            t_rect rect;
            get_center_pix(dadaobj_cast(x), patcherview, &rect);
            peanos_pix_to_coord(x, &rect, pt, x->mousemovecoord_hp, false);

            char lowprec = 0;
            numsamps = peanos_coord_to_samplenum_and_bufferidx(x, x->mousemovecoord_hp, x->mousemovebufferidx, false, &lowprec);
            if (lowprec) {
                mpfr_set(x->mousemovephase_hp, x->mousemovecoord_hp, MPFR_RNDD);
                mpfr_frac(x->mousemovephase_hp, x->mousemovephase_hp, MPFR_RNDD);
            } else {
                peanos_get_num_buffers_for_samplenum(x, numsamps, x->mousemovetotnumbuffers);
                mpfr_set_z(x->mousemovephase_hp, x->mousemovebufferidx, MPFR_RNDD);
                mpfr_div_z(x->mousemovephase_hp, x->mousemovephase_hp, x->mousemovetotnumbuffers, MPFR_RNDD);
            }
            
            x->mousemovenumsamps = numsamps;
            
            char *phase_str = peanos_mpfr_get_str(16, numsamps * x->bitrate/4, x->mousemovephase_hp, DADA_PEANOS_MPFR_RND, 64);
            snprintf(x->legend, DADA_PEANOS_LEGEND_SIZE, "%ld samps (%.3f sec)", numsamps, (1.*numsamps)/x->sr);
            mpfr_snprintf(x->legend2, DADA_PEANOS_LEGEND_SIZE, "id: %ld.%s", numsamps, phase_str);
            bach_freeptr(phase_str);

            jbox_redraw((t_jbox *)x);
        }
    } else {
        if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type != DADAITEM_TYPE_NONE) {
            x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
            dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
            jbox_redraw((t_jbox *)x);
        }
    }
    */
    /*
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
    */
}


long peanos_char2int(char c)
{
    switch (c) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 'a': return 10;
        case 'b': return 11;
        case 'c': return 12;
        case 'd': return 13;
        case 'e': return 14;
        case 'f': return 15;
        default: return 0;
    }
}

double samp_uint16_to_double(uint16_t samp)
{
    return samp/32768. - 1.;
}

t_float samp_uint16_to_float(uint16_t samp)
{
    return samp/32768. - 1.;
}


void peanos_send_mousedown_notification(t_peanos *x, t_symbol *sym, char forceverbose)
{
    long n = dadaobj_cast(x)->m_interface.send_notifications;
/*
    if (forceverbose)
        n = DADAOBJ_NOTIFY_VERBOSE;
    switch (n) {
        case DADAOBJ_NOTIFY_BASIC:
            dadaobj_send_notification_sym(dadaobj_cast(x), sym);
            break;
            
        case DADAOBJ_NOTIFY_VERBOSE:
        {
            t_llll *ll = llll_get();
            t_llll *sub_ll = llll_get();
            llll_appendsym(ll, sym);
            llll_appenddouble(ll, mpfr_get_d(x->mousedowncoord_hp, DADA_PEANOS_MPFR_RND));
            llll_appendlong(sub_ll, x->mousedownnumsamps);
            llll_appenddouble(sub_ll, mpfr_get_d(x->mousedownphase_hp, DADA_PEANOS_MPFR_RND));
            llll_appendllll(ll, sub_ll);
            dadaobj_send_notification_llll(dadaobj_cast(x), ll);
        }
            break;
        
        default:
            break;
    }
 */
}

void peanos_mousedown(t_peanos *x, t_object *patcherview, t_pt pt, long modifiers)
{
    if (dadaobj_mousedown(dadaobj_cast(x), patcherview, pt, modifiers)){
        // don't return
    }
    
//    x->b_ob.d_ob.m_interface.mousedown_item_identifier = pixel_to_element(x, pt, patcherview, &x->b_ob.d_ob.m_interface.mousedown_coord);
    
    x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = 0;

    if (modifiers & ePopupMenu) {
        
        
    } else {
        llll_format_modifiers(&modifiers, NULL);

        t_rect rect;
        get_center_pix(dadaobj_cast(x), patcherview, &rect);
        
        if (pt.x > rect.width - DADA_PEANOS_INSET_RIGHT_NOISINESS) {
            // handling noisiness
            t_ptn ptn = peanos_coord_to_pix(x, &rect, x->coord_hp);
            ptn.n = pt.y;
            peanos_pix_to_coord(x, &rect, ptn, x->coord_hp, true);
            process_coords(x);
            output_coords(x);
            x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = 2;
        } else {
            t_ptn ptn = peanos_coord_to_pix(x, &rect, x->coord_hp);
            if (modifiers & eShiftKey && modifiers & eAltKey) {
                x->mousedrag_constraint = 1;
                ptn.y = pt.y;
            } else if (modifiers & eShiftKey) {
                x->mousedrag_constraint = 2;
                ptn.x = pt.x;
            } else {
                ptn.x = pt.x;
                ptn.y = pt.y;
            }
            peanos_pix_to_coord(x, &rect, ptn, x->coord_hp, true);
            process_coords(x);
            output_coords(x);
            x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = 1;
        }

    }
    
    jbox_redraw((t_jbox *)x);
    
}

void peanos_mouseup(t_peanos *x, t_object *patcherview, t_pt pt, long modifiers)
{
    llll_format_modifiers(&modifiers, NULL);
    if (x->mousedrag_constraint != 0) {
        x->mousedrag_constraint = 0;
        peanos_iar(x);
    }
    if (dadaobj_mouseup(dadaobj_cast(x), patcherview, pt, modifiers))
        return;
}




void peanos_mousedrag(t_peanos *x, t_object *patcherview, t_pt pt, long modifiers)
{
    llll_format_modifiers(&modifiers, NULL);
    
    if (dadaobj_mousedrag(dadaobj_cast(x), patcherview, pt, modifiers))
        return;

    t_rect rect;
    get_center_pix(dadaobj_cast(x), patcherview, &rect);

    x->mousedrag_constraint = 0;
    if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == 1) {
        t_ptn ptn = peanos_coord_to_pix(x, &rect, x->coord_hp);
        if (modifiers & eShiftKey && modifiers & eAltKey) {
            x->mousedrag_constraint = 1;
            ptn.y = pt.y;
        } else if (modifiers & eShiftKey) {
            x->mousedrag_constraint = 2;
            ptn.x = pt.x;
        } else {
            ptn.x = pt.x;
            ptn.y = pt.y;
        }
        peanos_pix_to_coord(x, &rect, ptn, x->coord_hp, true);
        process_coords(x);
        output_coords(x);
    } else if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == 2) {
        t_ptn ptn = peanos_coord_to_pix(x, &rect, x->coord_hp);
        ptn.n = pt.y;
        peanos_pix_to_coord(x, &rect, ptn, x->coord_hp, true);
        process_coords(x);
        output_coords(x);
    }
    
//    peanos_send_mousedown_notification(x, gensym("movedcursor"), false);
    jbox_redraw((t_jbox *)x);
}


void change_precision_according_to_domain(t_peanos *x)
{
    if (x->float_precision_maximum == 0 || x->float_precision_maximum > x->float_precision_minimum) {
        for (int i = 0; i < 3; i++) {
            mpfr_exp_t exponent = mpfr_get_exp(x->screen_domain_hp[i]);
            long new_precision = MAX(x->float_precision_minimum, -exponent + x->float_precision_minimum);
            if (x->mpfr_precision[i] != new_precision) {
                change_precision(x, i, new_precision);
                
//                char text[1024];
//                snprintf_zero(text, 1024, "New precision for coordinate %d: %ld", i, new_precision);
//                post(text);
            }
        }
    }
}

void peanos_zoom_by_hp(t_peanos *x, int coord, double zoom_factor, mpfr_t around_this_coord_hp)
{
    mpfr_t temp;
    mpfr_init2(temp, mpfr_get_prec(around_this_coord_hp));
    
    mpfr_set(temp, x->screen_start_hp[coord], DADA_PEANOS_MPFR_RND);
    mpfr_sub(temp, temp, around_this_coord_hp, DADA_PEANOS_MPFR_RND);
    mpfr_div_d(temp, temp, zoom_factor, DADA_PEANOS_MPFR_RND);
    mpfr_add(temp, temp, around_this_coord_hp, DADA_PEANOS_MPFR_RND);
    mpfr_set(x->screen_start_hp[coord], temp, DADA_PEANOS_MPFR_RND);

    mpfr_set(temp, x->screen_end_hp[coord], DADA_PEANOS_MPFR_RND);
    mpfr_sub(temp, temp, around_this_coord_hp, DADA_PEANOS_MPFR_RND);
    mpfr_div_d(temp, temp, zoom_factor, DADA_PEANOS_MPFR_RND);
    mpfr_add(temp, temp, around_this_coord_hp, DADA_PEANOS_MPFR_RND);
    mpfr_set(x->screen_end_hp[coord], temp, DADA_PEANOS_MPFR_RND);

    if (mpfr_cmp_d(x->screen_start_hp[coord], 0.) < 0)
        mpfr_set_d(x->screen_start_hp[coord], 0., DADA_PEANOS_MPFR_RND);

    if (mpfr_cmp_d(x->screen_end_hp[coord], 1.) > 0)
        mpfr_set_d(x->screen_end_hp[coord], 1., DADA_PEANOS_MPFR_RND);

/*    if (mpfr_cmp(x->screen_end_hp, x->screen_start_hp) <= 0) {
        mpfr_add_d(x->screen_end_hp, x->screen_start_hp, 0.000000001, DADA_PEANOS_MPFR_RND);
    } */

    mpfr_sub(x->screen_domain_hp[coord], x->screen_end_hp[coord], x->screen_start_hp[coord], DADA_PEANOS_MPFR_RND);
    
    change_precision_according_to_domain(x);
    
    mpfr_clear(temp);
}

void peanos_zoom_by(t_peanos *x, int coord, double zoom_factor, double around_this_coord)
{
    mpfr_t temp;
    mpfr_init2(temp, x->mpfr_precision[coord]);
    mpfr_set_d(temp, around_this_coord, DADA_PEANOS_MPFR_RND);
    peanos_zoom_by_hp(x, coord, zoom_factor, temp);
    mpfr_clear(temp);
}

void peanos_zoom_exp_hp(t_peanos *x, int coord, mpfr_t zoom_exponent, mpfr_t around_this_coord_hp)
{
    mpfr_t temp;
    char negative = 0;
    mpfr_init2(temp, mpfr_get_prec(around_this_coord_hp));
    
    mpfr_set(temp, x->screen_start_hp[coord], DADA_PEANOS_MPFR_RND);
    mpfr_sub(temp, temp, around_this_coord_hp, DADA_PEANOS_MPFR_RND);
    if (mpfr_cmp_d(temp, 0.) < 0) {
        negative = 1;
        mpfr_abs(temp, temp, DADA_PEANOS_MPFR_RND);
    }
    mpfr_pow(temp, temp, zoom_exponent, DADA_PEANOS_MPFR_RND);
    if (negative)
        mpfr_mul_d(temp, temp, -1., DADA_PEANOS_MPFR_RND);
    mpfr_add(temp, temp, around_this_coord_hp, DADA_PEANOS_MPFR_RND);
    mpfr_set(x->screen_start_hp[coord], temp, DADA_PEANOS_MPFR_RND);
    
    negative = 0;
    mpfr_set(temp, x->screen_end_hp[coord], DADA_PEANOS_MPFR_RND);
    mpfr_sub(temp, temp, around_this_coord_hp, DADA_PEANOS_MPFR_RND);
    if (mpfr_cmp_d(temp, 0.) < 0) {
        negative = 1;
        mpfr_abs(temp, temp, DADA_PEANOS_MPFR_RND);
    }
    mpfr_pow(temp, temp, zoom_exponent, DADA_PEANOS_MPFR_RND);
    if (negative)
        mpfr_mul_d(temp, temp, -1., DADA_PEANOS_MPFR_RND);
    mpfr_add(temp, temp, around_this_coord_hp, DADA_PEANOS_MPFR_RND);
    mpfr_set(x->screen_end_hp[coord], temp, DADA_PEANOS_MPFR_RND);
    
    if (mpfr_cmp_d(x->screen_start_hp[coord], 0.) < 0)
        mpfr_set_d(x->screen_start_hp[coord], 0., DADA_PEANOS_MPFR_RND);
    
    if (mpfr_cmp_d(x->screen_end_hp[coord], 1.) > 0)
        mpfr_set_d(x->screen_end_hp[coord], 1., DADA_PEANOS_MPFR_RND);
    
/*    if (mpfr_cmp(x->screen_end_hp, x->screen_start_hp) <= 0) {
        mpfr_add_d(x->screen_end_hp, x->screen_start_hp, 0.000000001, DADA_PEANOS_MPFR_RND);
    } */
    
    mpfr_sub(x->screen_domain_hp[coord], x->screen_end_hp[coord], x->screen_start_hp[coord], DADA_PEANOS_MPFR_RND);
    
    change_precision_according_to_domain(x);
    
    mpfr_clear(temp);
}



void peanos_mousewheel(t_peanos *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc)
{
    llll_format_modifiers(&modifiers, NULL);  
    t_dadaobj *r_ob = dadaobj_cast(x);
    
    t_rect rect;
    get_center_pix(r_ob, view, &rect);

    int coord = (pt.x > rect.width - DADA_PEANOS_INSET_RIGHT_NOISINESS ? 2 : (modifiers & eAltKey ? 1 : 0));
    if (modifiers & eCommandKey) {

        mpfr_t temp_hp[3];
        for (int i = 0; i < 3; i++)
            mpfr_init2(temp_hp[i], x->mpfr_precision[i]);
        
        t_ptn ptn = peanos_coord_to_pix(x, &rect, x->coord_hp);
        if (coord == 2)
            ptn.n = pt.y;
        else
            ptn.x = pt.x; ptn.y = pt.y;
        peanos_pix_to_coord(x, &rect, ptn, temp_hp, false);
        
        if (modifiers & eControlKey) {
            double zoom_exponent = exp(-y_inc * 0.01 * (modifiers & eShiftKey ? DADA_FINER_FROM_KEYBOARD : 1.));
            mpfr_t zoom_exponent_hp;
            mpfr_init2(zoom_exponent_hp, x->mpfr_precision[coord]);
            mpfr_set_d(zoom_exponent_hp, zoom_exponent, DADA_PEANOS_MPFR_RND);
            peanos_zoom_exp_hp(x, coord, zoom_exponent_hp, temp_hp[coord]);
            mpfr_clear(zoom_exponent_hp);
        } else {
            double zoom_factor = exp(-y_inc * 0.01 * (modifiers & eShiftKey ? DADA_FINER_FROM_KEYBOARD : 1.));
            peanos_zoom_by_hp(x, coord, zoom_factor, temp_hp[coord]);
        }
        
        for (int i = 0; i < 3; i++)
            mpfr_clear(temp_hp[i]);
        
        peanos_iar(x);

    } else {
        for (int c = 0; c < 3; c++) {
            if (coord == 2 && c != 2)
                continue;
            double inc = (c == 0 ? x_inc : -y_inc);
            if (inc != 0){
                mpfr_t toadd_hp;
                mpfr_init2(toadd_hp, x->mpfr_precision[c]);
                mpfr_mul_d(toadd_hp, x->screen_domain_hp[c], - 0.01 * inc, DADA_PEANOS_MPFR_RND);
                
                mpfr_add(x->screen_start_hp[c], x->screen_start_hp[c], toadd_hp, DADA_PEANOS_MPFR_RND);
                
                if (mpfr_cmp_d(x->screen_start_hp[c], 0.) < 0)
                    mpfr_set_d(x->screen_start_hp[c], 0., DADA_PEANOS_MPFR_RND);
                
                mpfr_add(x->screen_end_hp[c], x->screen_start_hp[c], x->screen_domain_hp[c], DADA_PEANOS_MPFR_RND);
                
                if (mpfr_cmp_d(x->screen_end_hp[c], 1.) > 0) {
                    mpfr_set_d(x->screen_end_hp[c], 1., DADA_PEANOS_MPFR_RND);
                    mpfr_sub(x->screen_start_hp[c], x->screen_end_hp[c], x->screen_domain_hp[c], DADA_PEANOS_MPFR_RND);
                }
                
                mpfr_clear(toadd_hp);
            }
        }
        peanos_iar(x);
    }
    
    /*
    if (dadaobj_mousewheel(dadaobj_cast(x), view, pt, modifiers, x_inc, y_inc)) {
        jbox_invalidate_layer((t_object *)x, NULL, gensym("network"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
        jbox_redraw((t_jbox *)x);
        return;
    } */
}




long peanos_keyup(t_peanos *x, t_object *patcherview, long keycode, long modifiers, long textcharacter){
    
    llll_format_modifiers(&modifiers, &keycode);
    
    if (dadaobj_keyup(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
        return 1;
    
    return 0;
}

long peanos_key(t_peanos *x, t_object *patcherview, long keycode, long modifiers, long textcharacter)
{
    
    
    llll_format_modifiers(&modifiers, &keycode);
    
    if (dadaobj_key(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter)) {
        return 1;
    }
    
    if (keycode == JKEY_ESC) {
        // reset zoom
        for (int i = 0; i < 3; i++) {
            mpfr_set_d(x->screen_start_hp[i], 0., DADA_PEANOS_MPFR_RND);
            mpfr_set_d(x->screen_end_hp[i], 1., DADA_PEANOS_MPFR_RND);
            mpfr_set_d(x->screen_domain_hp[i], 1., DADA_PEANOS_MPFR_RND);
        }
        jbox_redraw((t_jbox *)x);
        return 1;
    } else if (keycode == JKEY_TAB) {
        // set coord around player
        
        for (int i = 0; i < 3; i++) {
            mpfr_t toadd_hp;
            mpfr_init2(toadd_hp, mpfr_get_prec(x->screen_domain_hp[i]));
            mpfr_mul_d(toadd_hp, x->screen_domain_hp[i], 0.5, DADA_PEANOS_MPFR_RND);
            
            mpfr_add(x->screen_end_hp[i], x->coord_hp[i], toadd_hp, DADA_PEANOS_MPFR_RND);
            mpfr_sub(x->screen_start_hp[i], x->coord_hp[i], toadd_hp, DADA_PEANOS_MPFR_RND);
            
            if (mpfr_cmp_d(x->screen_start_hp[i], 0.) < 0)
                mpfr_set_d(x->screen_start_hp[i], 0., DADA_PEANOS_MPFR_RND);
            
            if (mpfr_cmp_d(x->screen_end_hp[i], 1.) > 0)
                mpfr_set_d(x->screen_end_hp[i], 1., DADA_PEANOS_MPFR_RND);
            
            mpfr_sub(x->screen_domain_hp[i], x->screen_end_hp[i], x->screen_start_hp[i], DADA_PEANOS_MPFR_RND);
            mpfr_clear(toadd_hp);
        }
        jbox_redraw((t_jbox *)x);
        return 1;
    }
    return 0;
}



void peanos_mouseenter(t_peanos *x, t_object *patcherview, t_pt pt, long modifiers)
{
    if (dadaobj_mouseenter(dadaobj_cast(x), patcherview, pt, modifiers))
        return;
}

void peanos_mouseleave(t_peanos *x, t_object *patcherview, t_pt pt, long modifiers)
{
    x->legend[0] = 0;
    x->legend[1] = 0;
    if (dadaobj_mouseleave(dadaobj_cast(x), patcherview, pt, modifiers))
        return;
}




