/**
	@file
	dada.music~.c
	
	@name
	dada.music~
	
	@realname
	dada.music~
 
	@type
	object
	
	@module
	dada
 
	@author
	Daniele Ghisi
	
	@digest
	The discotheque of Babel
	
	@description
	Browse all music (if you are prepared to wait long enough...)
	
	@discussion
 
	@category
	dada interfaces, dada audio
 
	@keywords
	music~, music, babel, disco, discoteque, browse, combinatorics, exploration
	
	@seealso
	dada.terrain~
	
	@owner
	Daniele Ghisi
 */

#include <stdio.h>
#include <mpfr.h>
#include <gmp.h>

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

#define DADA_MUSIC_DEBUG


#ifdef DADA_MUSIC_DEBUG
#define music_dev_post(...) if (x->debug) post(__VA_ARGS__)
#else
#define music_dev_post(...) ((void) 0)
#endif

#define DADA_MUSIC_LEGEND_SIZE       4096

#define DADA_MUSIC_MAIN_VIEW_POS (1./2.)
#define DADA_MUSIC_GLOBAL_VIEW_POS (3./4.)

#define DADA_MUSIC_LODISPLAY_SAMPLE_THRESHOLD 1000000


#define DADA_MUSIC_MPFR_PRECISION       500
#define DADA_MUSIC_MPFR_PRECISION_HIGH  200000
#define DADA_MUSIC_MPFR_RND         MPFR_RNDN


typedef struct _music {
    t_dadaobj_pxjbox	b_ob;
    
    long                bitrate;
    double              sr;
    
    long                mpfr_precision;
    char                high_precision_display;
    
    char                output_buffer;
    t_buffer_ref        *l_buffer_reference;
    
    char                legend[DADA_MUSIC_LEGEND_SIZE];
    char                legend2[DADA_MUSIC_LEGEND_SIZE];
    
    mpfr_t              screen_start_hp;
    mpfr_t              screen_end_hp;
    mpfr_t              screen_domain_hp;
    
    long                mousemovenumsamps;
    mpfr_t              mousemovecoord_hp;
    mpfr_t              mousemovephase_hp;
    mpz_t               mousemovebufferidx;
    mpz_t               mousemovetotnumbuffers;
    
    long                mousedownnumsamps;
    mpfr_t              mousedowncoord_hp;
    mpfr_t              mousedownphase_hp;
    mpz_t               mousedownbufferidx;
    mpz_t               mousedowntotnumbuffers;

    void                *clock;
    char                startclock;
    
    double              interval_ms;
    
    // the buffer!
    uint16_t            *buffer;
    long                buffer_size;
    long                curr_play_sample;
    char                is_playing_sample;

    // debug stuff
    char                dsp_debug;
    char                debug;
} t_music;



void handle_aborts(int signal_number);



void *music_new(t_symbol *s, long argc, t_atom *argv);
void music_free(t_music *x);
void music_assist(t_music *x, void *b, long m, long a, char *s);
void music_paint(t_music *x, t_object *patcherview);
t_atom_long music_acceptsdrag(t_music *x, t_object *drag, t_object *view);
void music_perform64(t_music *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void music_dsp64(t_music *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void music_doset(t_music *x, t_symbol *s);
void music_anything(t_music *x, t_symbol *msg, long ac, t_atom *av);
void music_tick(t_music *x);
t_max_err music_notify(t_music *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void music_bang(t_music *x);

long music_key(t_music *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
long music_keyup(t_music *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);

t_max_err music_setattr_bitrate(t_music *x, void *attr, long ac, t_atom *av);
t_max_err music_setattr_sr(t_music *x, void *attr, long ac, t_atom *av);


double music_display_to_ms(t_music *x, double pixel);
double music_ms_to_display(t_music *x, double ms);
double music_deg_to_rad(t_music *x, double deg);
double music_rad_to_deg(t_music *x, double rad);

void music_autozoom(t_music *x);
void music_autozoom_do(t_music *x, t_object *view);

void music_iar(t_music *x);


void music_focusgained(t_music *x, t_object *patcherview);
void music_focuslost(t_music *x, t_object *patcherview);
void music_mousemove(t_music *x, t_object *patcherview, t_pt pt, long modifiers);
void music_mousedown(t_music *x, t_object *patcherview, t_pt pt, long modifiers);
void music_mousedrag(t_music *x, t_object *patcherview, t_pt pt, long modifiers);
void music_mousewheel(t_music *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc);
void music_mouseup(t_music *x, t_object *patcherview, t_pt pt, long modifiers);
void music_mouseenter(t_music *x, t_object *patcherview, t_pt pt, long modifiers);
void music_mouseleave(t_music *x, t_object *patcherview, t_pt pt, long modifiers);

void music_set(t_music *x, t_symbol *s);

void music_zoom_by(t_music *x, double zoom_factor, double around_this_coord);
void music_zoom_by_hp(t_music *x, double zoom_factor, mpfr_t around_this_coord_hp);
void music_zoom_exp_hp(t_music *x, mpfr_t zoom_exponent, mpfr_t around_this_coord_hp);


void music_buffer_set(t_music *x, long num_samples, mpz_t bufferidx, mpfr_t phase_hp, char mode);
void music_output_buffer(t_music *x);
void music_buffer_next(t_music *x, t_symbol *msg, long ac, t_atom *av);
void music_buffer_next_and_play(t_music *x, t_symbol *msg, long ac, t_atom *av);
void music_buffer_next_do(t_music *x, char and_then_play);

long music_buffer_to_numsamples_and_bufferidx(t_music *x, t_buffer_ref *buffer_ref, mpz_t bufferidx);

void music_send_mousedown_notification(t_music *x, t_symbol *sym, char force_verbose);

double samp_uint16_to_double(uint16_t samp);
t_float samp_uint16_to_float(uint16_t samp);

double music_samplenum_and_bufferidx_to_pixel(t_music *x, t_rect *rect, unsigned long samplenum, mpz_t bufferidx);
void music_samplenum_and_bufferidx_to_coord(t_music *x, unsigned long samplenum, mpz_t bufferidx, mpfr_t coord_hp);
void music_int(t_music *x, long num);



static t_class *s_music_class;
gmp_randstate_t r_state;


void reset_coords_to_zero(t_music *x, char also_mousemove)
{
    mpfr_set_d(x->mousedowncoord_hp, 0, DADA_MUSIC_MPFR_RND);
    mpfr_set_d(x->mousedownphase_hp, 0, DADA_MUSIC_MPFR_RND);
    x->mousedownnumsamps = 0;
    
    mpz_set_ui(x->mousedownbufferidx, 0);
    mpz_set_ui(x->mousedowntotnumbuffers, 1);
    
    if (also_mousemove) {
        mpfr_set_d(x->mousemovecoord_hp, 0, DADA_MUSIC_MPFR_RND);
        mpfr_set_d(x->mousemovephase_hp, 0, DADA_MUSIC_MPFR_RND);
        x->mousemovenumsamps = 0;
        mpz_set_ui(x->mousemovebufferidx, 0);
        mpz_set_ui(x->mousemovetotnumbuffers, 1);
    }
    
    jbox_redraw((t_jbox *)x);
}

t_max_err music_setattr_bitrate(t_music *x, void *attr, long ac, t_atom *av)
{
    if (ac && av){
        long br = atom_getlong(av);
        if (br == 4)
            x->bitrate = 4;
        else if (br == 8)
            x->bitrate = 8;
        else if (br == 16)
            x->bitrate = 16;
        else {
            object_warn((t_object *)x, "Supported bitrates are: 4, 8, 16. Using 16 by default.");
            x->bitrate = 16;
        }
        
        reset_coords_to_zero(x, true);
    }
    return MAX_ERR_NONE;
}

t_max_err music_setattr_sr(t_music *x, void *attr, long ac, t_atom *av)
{
    if (ac && av){
        long sr = atom_getfloat(av);
        if (sr < 1) {
            object_warn((t_object *)x, "Minimum sample rate is 1. Defaulting to 1.");
            x->sr = 1;
        }
        
        reset_coords_to_zero(x, true);
    }
    return MAX_ERR_NONE;
}



void music_int(t_music *x, long num)
{
    if (num) {
        music_anything(x, _llllobj_sym_play, 0, NULL);
    } else {
        music_anything(x, _llllobj_sym_stop, 0, NULL);
    }
    jbox_redraw((t_jbox *)x);
}


// here's where we set the buffer~ we're going to access
void music_doset(t_music *x, t_symbol *s)
{
    if (!x->l_buffer_reference)
        x->l_buffer_reference = buffer_ref_new((t_object *)x, s);
    else
        buffer_ref_set(x->l_buffer_reference, s);
}

void music_set(t_music *x, t_symbol *s)
{
    defer(x, (method)music_doset, s, 0, NULL);
}

t_max_err music_notify(t_music *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
    return buffer_ref_notify(x->l_buffer_reference, s, msg, sender, data);
/*
    if (msg == gensym("attr_modified")) {
        t_symbol *name = (t_symbol *)object_method((t_object *)data, gensym("getname"));
        if (name == gensym("showbuffers") || name == gensym("shownames") || name == gensym("showmusic") || name == gensym("staticfunction") || name == gensym("wheelfunction") || name == gensym("mode") || name == gensym("eqp") || name == gensym("modulation") || name == gensym("wheelmode"))
            music_iar(x);
    }
    return jbox_notify((t_jbox *)x, s, msg, sender, data); */
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

    t_class *c;

    CLASS_NEW_CHECK_SIZE(c, "dada.music~", (method)music_new, (method)music_free, (long)sizeof(t_music), 0L /* leave NULL!! */, A_GIMME, 0);

	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
    jbox_initclass(c, JBOX_FONTATTR);	// include fonts
	class_dspinitjbox(c);

    signal(SIGABRT, &handle_aborts);
    
	class_addmethod(c, (method)music_dsp64,					"dsp64", A_CANT, 0);
	class_addmethod(c, (method)music_paint,					"paint",	A_CANT, 0);
	class_addmethod(c, (method)music_assist,                  "assist",		A_CANT, 0);
	class_addmethod(c, (method)music_acceptsdrag,	"acceptsdrag_unlocked", A_CANT, 0);
	class_addmethod(c, (method)music_acceptsdrag,	"acceptsdrag_locked", A_CANT, 0);
    class_addmethod(c, (method)music_notify,                  "bachnotify", A_CANT, 0);
    class_addmethod(c, (method)music_notify,                  "notify", A_CANT, 0);

    
    // @method int @digest Play/Stop
    // @description Toggles playing engine.
    class_addmethod(c, (method) music_int, "int", A_LONG, 0);

    // @method set @digest Set linked output buffer
    // @description Sets the name a buffer (if any) that will contain the current played buffer at any time.
    class_addmethod(c, (method)music_set, "set", A_SYM, 0);

    // @method autozoom @digest Set domain and range automatically
    // @description Adapts view and zoom automatically according to the current buffer positions (only for buffer wheel <m>type</m>).
    class_addmethod(c, (method)music_autozoom, "autozoom", 0);

    // @method zoomby @digest Zoom by a given factor
    // @description A <m>zoomby</m> message, followed by a floating point number <m>N</m>, will increase or decrease the zoom by the factor <m>N</m>.
    // By default, the zooming happens around the domain center; if an additional "cursor" symbol is given, the zooming happens around the play cursor;
    // if instead of the "cursor" symbol a floating point number is given, the zooming happens around the specified coordinate.
    // @marg 0 @name factor @optional 0 @type number
    // @marg 1 @name center @optional 1 @type symbol/number
    class_addmethod(c, (method)music_anything, "zoomby", A_GIMME, 0);

    // @method zoomexp @digest Zoom by a given exponent
    // @description A <m>zoomexp</m> message, followed by a floating point number <m>N</m>,
    // will exponentially increase or decrease the zoom by the exponent <m>N</m>.
    // By default, the zooming happens around the domain center; if an additional "cursor" symbol is given, the zooming happens around the play cursor;
    // if instead of the "cursor" symbol a floating point number is given, the zooming happens around the specified coordinate.
    // @marg 0 @name exponent @optional 0 @type number
    // @marg 1 @name center @optional 1 @type symbol/number
    class_addmethod(c, (method)music_anything, "zoomexp", A_GIMME, 0);

    // @method cursor @digest Set cursor and syncing buffer
    // @description A <m>cursor</m> message will set the play cursor on a specific position on the timeline. <br />
    // If a float is given as argument, then it is assumed to be a 0-1 position on the timeline. <br />
    // If two arguments are given, they are<m>length_in_samps</m> and <m>phase</m>; in this case, the specific buffer having <m>length_in_samps</m> samples
    // and with position <m>phase</m> is targeted. If <m>phase</m> is an integer, then it is expected to be the relative index of the buffer
    // inside all the buffers of length <m>length_in_samps</m>; if it is a float, it is expected to be a coordinate between 0. and 1. <br />
    // If the syntax is
    // <b>cursor <m>length_in_samps</m> <m>partial_coord</m> <m>partial_coord</m> <m>partial_coord</m>...</b>
    // where <m>partial_coord</m> are hexadecimal symbols (and not integers!), then the buffer with the specified id (if any) is selected. <br />
    // If the syntax is
    // <b>cursor <m>buffername</m></b> where <m>buffername</m> is a symbol referring to a buffer,
    // then the cursor is set exactly on the localization of the buffer on the line (up to the current <m>bitdepth</m>),
    // @marg 0 @name arguments @optional 0 @type anything
    class_addmethod(c, (method)music_anything, "cursor", A_GIMME, 0);
    
    // @method setcursor @digest Set cursor without syncing buffer
    // @description A <m>setcursor</m> message works like a <m>cursor</m> message, except that it will not synchronize the linked buffer
    // (see <m>set</m> message), nor the buffer will be output (see <m>outputbuffer</m> attribute).
    // See <m>cursor</m> to know more.
    class_addmethod(c, (method)music_anything, "setcursor", A_GIMME, 0);
    
    class_addmethod(c, (method)music_anything, "postvalue", A_GIMME, 0);
    class_addmethod(c, (method)music_anything, "anything", A_GIMME, 0);
    class_addmethod(c, (method)music_bang, "bang", 0);
    
    
    // interface
    class_addmethod(c, (method) music_focusgained, "focusgained", A_CANT, 0);
    class_addmethod(c, (method) music_focuslost, "focuslost", A_CANT, 0);
    
    class_addmethod(c, (method) music_mousedown, "mousedown", A_CANT, 0);
    class_addmethod(c, (method) music_mouseup, "mouseup", A_CANT, 0);
    class_addmethod(c, (method) music_mousemove, "mousemove", A_CANT, 0);
    class_addmethod(c, (method) music_mousedrag, "mousedrag", A_CANT, 0);
    class_addmethod(c, (method) music_mousewheel, "mousewheel", A_CANT, 0);
    class_addmethod(c, (method) music_mouseenter, "mouseenter", A_CANT, 0);
    class_addmethod(c, (method) music_mouseleave, "mouseleave", A_CANT, 0);

    // @method (keyboard) @digest Play or set domain
    // @description
    // • <m>Spacebar</m>: toggle play<br />
    class_addmethod(c, (method) music_key, "key", A_CANT, 0);
    class_addmethod(c, (method) music_keyup, "keyup", A_CANT, 0);
    
    
    dadaobj_class_init(c, LLLL_OBJ_UIMSP, DADAOBJ_ZOOM | DADAOBJ_AXES | DADAOBJ_GRID | DADAOBJ_GRID_SHOWDEFAULT | DADAOBJ_GRID_FIXEDDEFAULT | DADAOBJ_BORDER | DADAOBJ_BORDER_SHOWDEFAULT | DADAOBJ_LABELS | DADAOBJ_LABELS_SHOWDEFAULT | DADAOBJ_BG | DADAOBJ_MOUSEHOVER | DADAOBJ_NOTIFICATIONS | DADAOBJ_PLAY);

    
    CLASS_ATTR_INVISIBLE(c, "playstep", ATTR_GET_OPAQUE | ATTR_SET_OPAQUE);
	CLASS_ATTR_DEFAULT(c,"patching_rect",0, "0. 0. 700. 200.");

    CLASS_STICKY_ATTR(c,"category",0,"Color");
    
    CLASS_STICKY_ATTR_CLEAR(c, "category");


    CLASS_STICKY_ATTR(c,"category",0,"Appearance");

    CLASS_ATTR_CHAR(c, "hiprec", 0, t_music, high_precision_display);
    CLASS_ATTR_STYLE_LABEL(c, "hiprec", 0, "onoff", "High Precision Display");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"hiprec",0,"0");
    // @description Toggles the ability to increase precision when zooming in. Beware: might slow things down enormously!
    
    CLASS_STICKY_ATTR_CLEAR(c, "category");

    
    
    CLASS_STICKY_ATTR(c,"category",0,"Settings");

    
    CLASS_ATTR_LONG(c, "bitdepth", 0, t_music, bitrate);
    CLASS_ATTR_STYLE_LABEL(c, "bitdepth", 0, "text", "Bit Depth");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"bitdepth",0,"4");
    CLASS_ATTR_ACCESSORS(c,	"bitdepth",	NULL,	music_setattr_bitrate);
    CLASS_ATTR_BASIC(c, "bitdepth", 0);
    // @description Sets the bit depth (only 4, 8 and 16 allowed).
    
    CLASS_ATTR_DOUBLE(c, "playinterval", 0, t_music, interval_ms);
    CLASS_ATTR_STYLE_LABEL(c, "playinterval", 0, "text", "Interval Between Pieces");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"playinterval",0,"500");
    CLASS_ATTR_BASIC(c, "playinterval", 0);
    // @description Sets the interval between different pieces in milliseconds.
    

    CLASS_ATTR_CHAR(c, "outputbuffer", 0, t_music, output_buffer);
    CLASS_ATTR_STYLE_LABEL(c, "outputbuffer", 0, "onoff", "Output Buffer");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"outputbuffer",0,"0");
    CLASS_ATTR_BASIC(c, "outputbuffer", 0);
    // @description Toggles the ability to output buffers as lllls from the middle outlet

    CLASS_ATTR_CHAR(c, "debug", 0, t_music, debug);
    CLASS_ATTR_STYLE_LABEL(c, "debug", 0, "onoff", "Debug");
    CLASS_ATTR_INVISIBLE(c, "debug", ATTR_GET_OPAQUE | ATTR_SET_OPAQUE);
    // @exclude all

    CLASS_ATTR_CHAR(c, "dspdebug", 0, t_music, dsp_debug);
    CLASS_ATTR_STYLE_LABEL(c, "dspdebug", 0, "onoff", "DSP Debug");
    CLASS_ATTR_INVISIBLE(c, "dspdebug", ATTR_GET_OPAQUE | ATTR_SET_OPAQUE);
    // @exclude all

    CLASS_STICKY_ATTR_CLEAR(c, "category");

    

    srand(time(NULL));
    gmp_randinit_default (r_state);
    
	class_register(CLASS_BOX, c);
	s_music_class = c;
    dadaobj_class_add_fileusage_method(c);
}

void change_precision(t_music *x, long new_precision)
{
    x->mpfr_precision = new_precision;
    mpfr_prec_round(x->screen_domain_hp, new_precision, DADA_MUSIC_MPFR_RND);
    mpfr_prec_round(x->screen_start_hp, new_precision, DADA_MUSIC_MPFR_RND);
    mpfr_prec_round(x->screen_end_hp, new_precision, DADA_MUSIC_MPFR_RND);
    mpfr_prec_round(x->mousemovecoord_hp, new_precision, DADA_MUSIC_MPFR_RND);
    mpfr_prec_round(x->mousedowncoord_hp, new_precision, DADA_MUSIC_MPFR_RND);
    mpfr_prec_round(x->mousemovephase_hp, new_precision, DADA_MUSIC_MPFR_RND);
    mpfr_prec_round(x->mousedownphase_hp, new_precision, DADA_MUSIC_MPFR_RND);
}


void *music_new(t_symbol *s, long argc, t_atom *argv)
{
	t_music *x = NULL;
	t_dictionary *d=NULL;
	long boxflags;
    
	if (!(d=object_dictionaryarg(argc,argv)))
		return NULL;

    if ((x = (t_music *)object_alloc_debug(s_music_class))) {
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
        dsp_setupjbox((t_pxjbox *)x, 1);
        
        dadaobj_pxjbox_setup((t_dadaobj_pxjbox *)x, DADAOBJ_ZOOM | DADAOBJ_AXES | DADAOBJ_GRID | DADAOBJ_BORDER | DADAOBJ_BORDER_SHOWDEFAULT |  DADAOBJ_BG | DADAOBJ_MOUSEHOVER | DADAOBJ_NOTIFICATIONS | DADAOBJ_PLAY, build_pt(1., 1.), -1, -1, 2, NULL, (invalidate_and_redraw_fn)music_iar, "", 0, "44s");
        x->b_ob.d_ob.m_zoom.max_zoom_perc = build_pt(100000, 100000);
        //    dadaobj_addfunctions(dadaobj_cast(x), (dada_mousemove_fn)music_mousemove, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
        
        x->clock = clock_new(x,(method)music_tick);
        x->interval_ms = 500;
        x->bitrate = 4;
        x->sr = 44100;

        x->buffer = (uint16_t *)sysmem_newptr(1 * sizeof(uint16_t));
        x->buffer_size = 1;
        x->buffer[0] = 32768;
        
        x->mpfr_precision = DADA_MUSIC_MPFR_PRECISION;
        
        mpfr_init2(x->screen_domain_hp, x->mpfr_precision);
        mpfr_init2(x->screen_start_hp, x->mpfr_precision);
        mpfr_init2(x->screen_end_hp, x->mpfr_precision);
        mpfr_init2(x->mousemovecoord_hp, x->mpfr_precision);
        mpfr_init2(x->mousedowncoord_hp, x->mpfr_precision);
        mpfr_init2(x->mousemovephase_hp, x->mpfr_precision);
        mpfr_init2(x->mousedownphase_hp, x->mpfr_precision);
        mpz_init(x->mousemovebufferidx);
        mpz_init(x->mousedownbufferidx);
        mpz_init(x->mousemovetotnumbuffers);
        mpz_init(x->mousedowntotnumbuffers);
        
        mpz_set_ui(x->mousemovebufferidx, 0);
        mpz_set_ui(x->mousedownbufferidx, 0);
        mpz_set_ui(x->mousemovetotnumbuffers, 1);
        mpz_set_ui(x->mousedowntotnumbuffers, 1);
        
        mpfr_set_d(x->mousemovecoord_hp, 0., DADA_MUSIC_MPFR_RND);
        mpfr_set_d(x->mousedowncoord_hp, 0., DADA_MUSIC_MPFR_RND);
        mpfr_set_d(x->mousemovephase_hp, 0., DADA_MUSIC_MPFR_RND);
        mpfr_set_d(x->mousedownphase_hp, 0., DADA_MUSIC_MPFR_RND);
        mpfr_set_d(x->screen_start_hp, 0., DADA_MUSIC_MPFR_RND);
        mpfr_set_d(x->screen_end_hp, 1., DADA_MUSIC_MPFR_RND);
        mpfr_set_d(x->screen_domain_hp, 1., DADA_MUSIC_MPFR_RND);
        
        attr_dictionary_process(x,d);
        
        jbox_ready((t_jbox *)x);
        
        dadaobj_set_current_version_number(dadaobj_cast(x));

        return x;
    }
    
    
    return NULL;
}


void music_free(t_music *x)
{
    sysmem_freeptr(x->buffer);
    
    mpz_clear(x->mousemovebufferidx);
    mpz_clear(x->mousedownbufferidx);
    mpz_clear(x->mousemovetotnumbuffers);
    mpz_clear(x->mousedowntotnumbuffers);
    mpfr_clear(x->screen_domain_hp);
    mpfr_clear(x->screen_start_hp);
    mpfr_clear(x->screen_end_hp);
    mpfr_clear(x->mousemovecoord_hp);
    mpfr_clear(x->mousedowncoord_hp);
    mpfr_clear(x->mousemovephase_hp);
    mpfr_clear(x->mousedownphase_hp);

    freeobject((t_object *)x->clock);
    
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




///// CONVERSIONS


void music_get_num_buffers_for_samplenum(t_music *x, unsigned long samplenum, mpz_t numbuffers)
{
    if (x->bitrate == 4)
        mpz_ui_pow_ui(numbuffers, 16, samplenum);
    else if (x->bitrate == 8)
        mpz_ui_pow_ui(numbuffers, 256, samplenum);
    else
        mpz_ui_pow_ui(numbuffers, 65536, samplenum);
}



void music_pix_to_coord(t_music *x, t_rect *rect, t_pt pixel, mpfr_t coord_hp, char high_precision)
{
    // coord = start_coord + pix/width * domain_coord
    
    // rough estimate
    mpfr_set_d(coord_hp, pixel.x, DADA_MUSIC_MPFR_RND);
    mpfr_div_d(coord_hp, coord_hp, rect->width, DADA_MUSIC_MPFR_RND);
    mpfr_mul(coord_hp, coord_hp, x->screen_domain_hp, DADA_MUSIC_MPFR_RND);
    mpfr_add(coord_hp, coord_hp, x->screen_start_hp, DADA_MUSIC_MPFR_RND);
    
    if (high_precision) {
        // needed precision, roughly inversely proportional to (1-coord)
        mpfr_t temp;
        mpfr_init2(temp, mpfr_get_prec(coord_hp));
        mpfr_d_sub(temp, 1., coord_hp, DADA_MUSIC_MPFR_RND);
        mpfr_d_div(temp, 1., temp, DADA_MUSIC_MPFR_RND);

        mpfr_mul_d(temp, temp, DADA_MUSIC_MPFR_PRECISION_HIGH * x->bitrate/4, DADA_MUSIC_MPFR_RND);

        long precision = mpfr_get_ui(temp, DADA_MUSIC_MPFR_RND) + 1;
//        post("%ld", precision);
        mpfr_clear(temp);
        
        mpfr_set_prec(coord_hp, precision);
        
        // ok, now making precision better! :)
        
        mpfr_set_d(coord_hp, pixel.x, DADA_MUSIC_MPFR_RND);
        mpfr_div_d(coord_hp, coord_hp, rect->width, DADA_MUSIC_MPFR_RND);
        mpfr_mul(coord_hp, coord_hp, x->screen_domain_hp, DADA_MUSIC_MPFR_RND);
        mpfr_add(coord_hp, coord_hp, x->screen_start_hp, DADA_MUSIC_MPFR_RND);
    }
    
}

double music_coord_to_pix(t_music *x, t_rect *rect, mpfr_t coord_hp)
{
    // pix = width * (coord - start_coord)/domain_coord
    mpfr_t temp;
    mpfr_init2(temp, x->mpfr_precision);
    mpfr_set(temp, coord_hp, DADA_MUSIC_MPFR_RND);
    
    mpfr_sub(temp, temp, x->screen_start_hp, DADA_MUSIC_MPFR_RND);
    mpfr_div(temp, temp, x->screen_domain_hp, DADA_MUSIC_MPFR_RND);
    mpfr_mul_d(temp, temp, rect->width, DADA_MUSIC_MPFR_RND);
    
    double res = mpfr_get_d(temp, DADA_MUSIC_MPFR_RND);

    mpfr_clear(temp);
    
    return res;
}

void music_coord_to_pix_hp(t_music *x, t_rect *rect, mpfr_t coord_hp, mpfr_t pixel)
{
    // pix = width * (coord - start_coord)/domain_coord
    mpfr_set(pixel, coord_hp, DADA_MUSIC_MPFR_RND);
    
    mpfr_sub(pixel, pixel, x->screen_start_hp, DADA_MUSIC_MPFR_RND);
    mpfr_div(pixel, pixel, x->screen_domain_hp, DADA_MUSIC_MPFR_RND);
    mpfr_mul_d(pixel, pixel, rect->width, DADA_MUSIC_MPFR_RND);
}




void music_samplenum_to_pixel_hp(t_music *x, t_rect *rect, unsigned long samplenum, mpfr_t pixel_hp)
{
    // the inverse of DADA_MUSIC_SR*(1./(1-$f1) - 1.)
    // y = sr * (1/(1-x) - 1)
    // y/sr + 1 = 1/(1-x)
    // 1/(y/sr + 1) = 1-x
    // x = 1- 1/(y/sr + 1)
    
    mpfr_set_ui(pixel_hp, samplenum, DADA_MUSIC_MPFR_RND);
    mpfr_div_d(pixel_hp, pixel_hp, x->sr, DADA_MUSIC_MPFR_RND);
    mpfr_add_d(pixel_hp, pixel_hp, 1., DADA_MUSIC_MPFR_RND);
    mpfr_d_div(pixel_hp, 1., pixel_hp, DADA_MUSIC_MPFR_RND);
    mpfr_d_sub(pixel_hp, 1., pixel_hp, DADA_MUSIC_MPFR_RND);
    
    music_coord_to_pix_hp(x, rect, pixel_hp, pixel_hp);
}



double music_samplenum_to_pixel(t_music *x, t_rect *rect, unsigned long samplenum)
{
    // the inverse of DADA_MUSIC_SR*(1./(1-$f1) - 1.)
    // y = sr * (1/(1-x) - 1)
    // y/sr + 1 = 1/(1-x)
    // 1/(y/sr + 1) = 1-x
    // x = 1- 1/(y/sr + 1)
    
    mpfr_t coord_hp;
    mpfr_init2(coord_hp, x->mpfr_precision);

    mpfr_set_ui(coord_hp, samplenum, DADA_MUSIC_MPFR_RND);
    mpfr_div_d(coord_hp, coord_hp, x->sr, DADA_MUSIC_MPFR_RND);
    mpfr_add_d(coord_hp, coord_hp, 1., DADA_MUSIC_MPFR_RND);
    mpfr_d_div(coord_hp, 1., coord_hp, DADA_MUSIC_MPFR_RND);
    mpfr_d_sub(coord_hp, 1., coord_hp, DADA_MUSIC_MPFR_RND);
    
    double res = music_coord_to_pix(x, rect, coord_hp);
    
    mpfr_clear(coord_hp);
    
    return res;
}


void music_samplenum_and_bufferidx_to_coord(t_music *x, unsigned long samplenum, mpz_t bufferidx, mpfr_t coord_hp)
{
    // the inverse of DADA_MUSIC_SR*(1./(1-$f1) - 1.)
    // y = sr * (1/(1-x) - 1)
    // y/sr + 1 = 1/(1-x)
    // 1/(y/sr + 1) = 1-x
    // x = 1- 1/(y/sr + 1)
    
    mpfr_set_z(coord_hp, bufferidx, DADA_MUSIC_MPFR_RND);
    
    mpz_t numbuffers;
    mpz_init(numbuffers);
    music_get_num_buffers_for_samplenum(x, samplenum, numbuffers);
    
    mpfr_div_z(coord_hp, coord_hp, numbuffers, MPFR_RNDD);
    
    mpfr_add_ui(coord_hp, coord_hp, samplenum, DADA_MUSIC_MPFR_RND);
    
    mpfr_div_d(coord_hp, coord_hp, x->sr, DADA_MUSIC_MPFR_RND);
    mpfr_add_d(coord_hp, coord_hp, 1., DADA_MUSIC_MPFR_RND);
    mpfr_d_div(coord_hp, 1., coord_hp, DADA_MUSIC_MPFR_RND);
    mpfr_d_sub(coord_hp, 1., coord_hp, DADA_MUSIC_MPFR_RND);
    mpz_clear(numbuffers);
}


double music_samplenum_and_bufferidx_to_pixel(t_music *x, t_rect *rect, unsigned long samplenum, mpz_t bufferidx)
{
    // the inverse of DADA_MUSIC_SR*(1./(1-$f1) - 1.)
    // y = sr * (1/(1-x) - 1)
    // y/sr + 1 = 1/(1-x)
    // 1/(y/sr + 1) = 1-x
    // x = 1- 1/(y/sr + 1)
    
    mpfr_t coord_hp;
    mpfr_init2(coord_hp, x->mpfr_precision);
    
    music_samplenum_and_bufferidx_to_coord(x, samplenum, bufferidx, coord_hp);
    
    double res = music_coord_to_pix(x, rect, coord_hp);
    
    mpfr_clear(coord_hp);
    
    return res;
}


unsigned long music_coord_to_samplenum_and_bufferidx(t_music *x, mpfr_t coord, mpz_t bufferidx, char high_precision, char *precision_has_been_lowered)
{
    if (precision_has_been_lowered)
        *precision_has_been_lowered = false;
    
    mpfr_t coord_hp;
    mpfr_init2(coord_hp, mpfr_get_prec(coord));
    mpfr_set(coord_hp, coord, DADA_MUSIC_MPFR_RND);
    
    mpfr_d_sub(coord_hp, 1., coord_hp, DADA_MUSIC_MPFR_RND);
    mpfr_d_div(coord_hp, 1., coord_hp, DADA_MUSIC_MPFR_RND);
    mpfr_sub_d(coord_hp, coord_hp, 1., DADA_MUSIC_MPFR_RND);
    mpfr_mul_d(coord_hp, coord_hp, x->sr, DADA_MUSIC_MPFR_RND);
    
    long numsamples = mpfr_get_ui(coord_hp, MPFR_RNDD);
    
    if (!high_precision && numsamples > DADA_MUSIC_LODISPLAY_SAMPLE_THRESHOLD && mpfr_cmp_d(x->screen_domain_hp, 0.00000001) > 0) {
        uint64_t r = rand() % numsamples;
        mpz_set_ui(bufferidx, r);
//        mpz_urandomb(bufferidx, r_state, numsamples);

        mpfr_set_d(coord_hp, (double)r, DADA_MUSIC_MPFR_RND);
        mpfr_div_ui(coord_hp, coord_hp, numsamples, DADA_MUSIC_MPFR_RND);
//        mpz_set_ui(bufferidx, r);
        
        if (precision_has_been_lowered)
            *precision_has_been_lowered = true;
    } else {
        mpfr_frac(coord_hp, coord_hp, MPFR_RNDD);
        
        music_get_num_buffers_for_samplenum(x, numsamples, bufferidx);
        mpfr_mul_z(coord_hp, coord_hp, bufferidx, MPFR_RNDD);
        mpfr_get_z(bufferidx, coord_hp, MPFR_RNDD);
    }
    
    mpfr_clear(coord_hp);
    return numsamples;
}

// basic equation is info = sr * (1/(1-x) - 1)
unsigned long music_coord_to_samplenum(t_music *x, mpfr_t coord)
{
    mpfr_t coord_hp;
    mpfr_init2(coord_hp, x->mpfr_precision);
    mpfr_set(coord_hp, coord, DADA_MUSIC_MPFR_RND);
    
    mpfr_d_sub(coord_hp, 1., coord_hp, DADA_MUSIC_MPFR_RND);
    mpfr_d_div(coord_hp, 1., coord_hp, DADA_MUSIC_MPFR_RND);
    mpfr_sub_d(coord_hp, coord_hp, 1., DADA_MUSIC_MPFR_RND);
    mpfr_mul_d(coord_hp, coord_hp, x->sr, DADA_MUSIC_MPFR_RND);
    
    long numsamples = mpfr_get_ui(coord_hp, MPFR_RNDD);
    
    mpfr_clear(coord_hp);
    
    return numsamples;
}

void music_pix_to_info(t_music *x, t_rect *rect, t_pt pixel, unsigned long *numsamples, mpfr_t phase_hp, char high_precision)
{
    mpfr_init2(phase_hp, x->mpfr_precision);
    
    music_pix_to_coord(x, rect, pixel, phase_hp, high_precision);
    
    // now we compute x->sr*(1./(1-$f1) - 1.) to get the number of samples + mantissa
    
    mpfr_d_sub(phase_hp, 1., phase_hp, DADA_MUSIC_MPFR_RND);
    mpfr_d_div(phase_hp, 1., phase_hp, DADA_MUSIC_MPFR_RND);
    mpfr_sub_d(phase_hp, phase_hp, 1., DADA_MUSIC_MPFR_RND);
    mpfr_mul_d(phase_hp, phase_hp, x->sr, DADA_MUSIC_MPFR_RND);
    
    *numsamples = mpfr_get_ui(phase_hp, MPFR_RNDD);
    
    mpfr_frac(phase_hp, phase_hp, MPFR_RNDD);
    
    
    
    // ok, we should set the precision of the phase_hp to the correct one, depending on the
}


void fill_mousedown_fields_from_coord(t_music *x)
{
    // x->mousedowncoord_hp given, all the other stuff is calculated
    x->mousedownnumsamps = music_coord_to_samplenum_and_bufferidx(x, x->mousedowncoord_hp, x->mousedownbufferidx, true, NULL);
    music_get_num_buffers_for_samplenum(x, x->mousedownnumsamps, x->mousedowntotnumbuffers);
    mpfr_set_z(x->mousedownphase_hp, x->mousedownbufferidx, MPFR_RNDD);
    mpfr_div_z(x->mousedownphase_hp, x->mousedownphase_hp, x->mousedowntotnumbuffers, MPFR_RNDD);
}


void fill_mousedown_fields_from_samplenum_and_bufferidx(t_music *x)
{
    // x->mousedownnumsamps and x->mousedownbufferidx are given, all the rest is calculated
    music_samplenum_and_bufferidx_to_coord(x, x->mousedownnumsamps, x->mousedownbufferidx, x->mousedowncoord_hp);
    music_get_num_buffers_for_samplenum(x, x->mousedownnumsamps, x->mousedowntotnumbuffers);
    mpfr_set_z(x->mousedownphase_hp, x->mousedownbufferidx, MPFR_RNDD);
    mpfr_div_z(x->mousedownphase_hp, x->mousedownphase_hp, x->mousedowntotnumbuffers, MPFR_RNDD);
}



void music_assist(t_music *x, void *b, long m, long a, char *s)
{
    if (m == ASSIST_INLET) { // @in 0 @type anything/llll @digest Incoming messages
        sprintf(s, "Incoming messages");
    }
    else {
        char *type = NULL;
        llllobj_get_llll_outlet_type_as_string((t_object *) x, LLLL_OBJ_UIMSP, a, &type);
        if (a == 0)	// @out 0 @type signal @digest Music!
            sprintf(s, "(signal): Music!");
        else if (a == 1)	// @out 1 @type llll @digest Buffer as llll
            sprintf(s, "llll (%s): Buffer", type);
        else 	// @out 2 @type bang @digest bang when playhead position changes
            sprintf(s, "bang When Changed");
    }
}


void music_bang(t_music *x)
{
    music_iar(x);
}


void music_autozoom_do(t_music *x, t_object *view)
{
/*    t_rect rect;
    t_dadaobj *d_ob = dadaobj_cast(x);
    jbox_get_rect_for_view((t_object *)x, view, &rect);
    //	center = get_center_pix(dadaobj_cast(x), view, &rect);
    
    
    if (x->num_buffers <= 0)
        return;
    
    dadaobj_mutex_lock(d_ob);
    
    // Initialize
    double max_radius_ms = 0;
    long i;
    for (i = 0; i < x->num_buffers; i++) {
        double this_radius_ms = music_get_buffer_length_ms(x, i);
        if (this_radius_ms > max_radius_ms)
            max_radius_ms = this_radius_ms;
    }

    if (max_radius_ms == 0)
        max_radius_ms = 1000;
    
    // adding pad
    max_radius_ms *= 1.05;
    
    dadaobj_mutex_unlock(d_ob);
    
    double max_radius_px = music_ms_to_display(x, max_radius_ms);
    double zoom = (100.*MIN(rect.width, rect.height)/max_radius_px)/2.;
    dadaobj_setzoom(d_ob, build_pt(zoom, zoom)); */
}


void music_autozoom(t_music *x)
{
    music_autozoom_do(x, jpatcher_get_firstview((t_object *)gensym("#P")->s_thing));
}


double music_start_as_double(t_music *x)
{
    return mpfr_get_d(x->screen_start_hp, DADA_MUSIC_MPFR_RND);
}


double music_end_as_double(t_music *x)
{
    return mpfr_get_d(x->screen_end_hp, DADA_MUSIC_MPFR_RND);
}


double music_domain_as_double(t_music *x)
{
    return mpfr_get_d(x->screen_domain_hp, DADA_MUSIC_MPFR_RND);
}


long music_paint_single_grid_line(t_music *x, t_jgraphics *g, t_rect *rect, long num_samps, t_jfont *jf_label, char *label, double *curr_x_pix)
{
    t_jrgba color = dadaobj_cast(x)->m_grid.j_gridcolor;
    t_jrgba labelcolor = dadaobj_cast(x)->m_grid.j_labelscolor;
    double x_pix = music_samplenum_to_pixel(x, rect, num_samps);
    
    if (*curr_x_pix == *curr_x_pix && x_pix - *curr_x_pix < 20)
        return 1;
    
    *curr_x_pix = x_pix;
    
    double y1 = DADA_MUSIC_MAIN_VIEW_POS * rect->height;
    double y0 = y1 - 35;
    if (x_pix > 0 && x_pix < rect->width) {
        paint_line(g, color, x_pix, y0, x_pix, y1, 0.5);
        if (jf_label) {
            if (x_pix - 20 <= 0)
                write_text(g, jf_label, labelcolor, label, x_pix, y0 - 50, 100, 50, JGRAPHICS_TEXT_JUSTIFICATION_BOTTOM | JGRAPHICS_TEXT_JUSTIFICATION_LEFT, true, false);
            else if (x_pix + 20 >= rect->width)
                write_text(g, jf_label, labelcolor, label, x_pix - 100, y0 - 50, 100, 50, JGRAPHICS_TEXT_JUSTIFICATION_BOTTOM | JGRAPHICS_TEXT_JUSTIFICATION_RIGHT, true, false);
            else
                write_text(g, jf_label, labelcolor, label, x_pix - 50, y0 - 50, 100, 50, JGRAPHICS_TEXT_JUSTIFICATION_BOTTOM | JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, true, false);
        }
    }
    
    return 0;
}

char might_need_to_paint_buffers(t_music *x, long startnumsamps)
{
    mpfr_t temp;
    mpfr_init2(temp, mpfr_get_prec(x->screen_domain_hp));
    mpfr_set(temp, x->screen_domain_hp, DADA_MUSIC_MPFR_RND);
    mpfr_d_div(temp, 1., temp, DADA_MUSIC_MPFR_RND);

 //   post("1/domain = %ld", mpfr_get_ui(temp, DADA_MUSIC_MPFR_RND));

    mpfr_div_ui(temp, temp, startnumsamps, DADA_MUSIC_MPFR_RND);

    double ratio = mpfr_get_d(temp, DADA_MUSIC_MPFR_RND);
//    post("(1/domain) * startnumsamps = %.4f", mpfr_get_d(temp, DADA_MUSIC_MPFR_RND));

    
    if (startnumsamps >= 3 && ratio < 32768)
        return 0;
    
    return 1;
}

void music_paint(t_music *x, t_object *patcherview)
{
    t_dadaobj *r_ob = dadaobj_cast(x);
	t_rect rect;
    t_jgraphics *g = (t_jgraphics *) patcherview_get_jgraphics(patcherview); // obtain graphics context
    jbox_get_rect_for_view((t_object *)x, patcherview, &rect);

    t_jfont *jf = jfont_create_debug(jbox_get_fontname((t_object *)x)->s_name, (t_jgraphics_font_slant)jbox_get_font_slant((t_object *)x), (t_jgraphics_font_weight)jbox_get_font_weight((t_object *)x), jbox_get_fontsize((t_object *)x));

    t_jrgba bufferline_color = DADA_GREY_50;
    t_jrgba sample_ticks_color = DADA_GREY_50;
    
    dadaobj_paint_background(r_ob, g, &rect);
    
    
    double y = DADA_MUSIC_MAIN_VIEW_POS * rect.height;
    double continuous_line_starts_from = 0.;

    
    // painting "grid"
    if (dadaobj_cast(x)->m_grid.show_grid) {
        t_jfont *jf_labels = dadaobj_cast(x)->m_grid.show_labels ? jf : NULL;
        double x_pix = NAN;
        if (music_paint_single_grid_line(x, g, &rect, 0, jf_labels, (char *)"0sec", &x_pix)) goto ticks;
        if (music_paint_single_grid_line(x, g, &rect, 0.25 * x->sr, jf_labels, (char *)"¼sec", &x_pix)) goto ticks;
        if (music_paint_single_grid_line(x, g, &rect, 0.5 * x->sr, jf_labels, (char *)"½sec", &x_pix)) goto ticks;
        if (music_paint_single_grid_line(x, g, &rect, x->sr, jf_labels, (char *)"1sec", &x_pix)) goto ticks;
        if (music_paint_single_grid_line(x, g, &rect, 2 * x->sr, jf_labels, (char *)"2sec", &x_pix)) goto ticks;
        if (music_paint_single_grid_line(x, g, &rect, 5 * x->sr, jf_labels, (char *)"5sec", &x_pix)) goto ticks;
        if (music_paint_single_grid_line(x, g, &rect, 60 * x->sr, jf_labels, (char *)"1min", &x_pix)) goto ticks;
        if (music_paint_single_grid_line(x, g, &rect, 3600 * x->sr, jf_labels, (char *)"1h", &x_pix)) goto ticks;
        if (music_paint_single_grid_line(x, g, &rect, 24 * 3600 * x->sr, jf_labels, (char *)"1day", &x_pix)) goto ticks;
        if (music_paint_single_grid_line(x, g, &rect, 30 * 24 * 3600 * x->sr, jf_labels, (char *)"1month", &x_pix)) goto ticks;
        if (music_paint_single_grid_line(x, g, &rect, 365 * 24 * 3600 * x->sr, jf_labels, (char *)"1year", &x_pix)) goto ticks;
    }
    
ticks:
    // paint TICKS for number of samples and SINGLE BUFFERS
    long start_num_samples = music_coord_to_samplenum(x, x->screen_start_hp);
    double prev_x = 0;
    char painting_buffers_one_by_one = true;
    mpfr_t this_x_hp, prev_x_hp, diff_hp;
    mpfr_init2(this_x_hp, x->mpfr_precision);
    mpfr_init2(prev_x_hp, x->mpfr_precision);
    mpfr_init2(diff_hp, x->mpfr_precision);
    char mntpb = might_need_to_paint_buffers(x, start_num_samples);
    for (long s = start_num_samples; ; s++) {
        music_samplenum_to_pixel_hp(x, &rect, s, this_x_hp);
        
        double this_x = mpfr_get_d(this_x_hp, DADA_MUSIC_MPFR_RND);
        double diff = (this_x - prev_x);
        mpfr_sub(diff_hp, this_x_hp, prev_x_hp, DADA_MUSIC_MPFR_RND);
        
        if (mntpb && painting_buffers_one_by_one) {
            if (s == 1) {
                continuous_line_starts_from = this_x;
            } else if (s > 1 && s > start_num_samples) {
                // checking if we need to draw the buffers for this number of samples as simple dots
                // (due to the fact that they are extremely zoomed in)
                
                mpz_t numbuffers;
                mpz_init(numbuffers);
                music_get_num_buffers_for_samplenum(x, s-1, numbuffers);
                
                mpfr_t ratio;
                mpfr_init2(ratio, x->mpfr_precision);
                mpfr_div_z(ratio, diff_hp, numbuffers, MPFR_RNDD);
                
                if (mpfr_cmp_d(ratio, 1.) > 0) {
                    continuous_line_starts_from = this_x;
                    
                    // paint buffers one by one!
                    mpz_t counter;
                    mpz_init(counter);
                    
                    if (s == start_num_samples + 1) {
                        long new_s = music_coord_to_samplenum_and_bufferidx(x, x->screen_start_hp, counter, false, NULL);
                        C74_ASSERT(new_s==start_num_samples);
                    } else
                        mpz_set_ui(counter, 1); // won't paint 0, there's already the number tick
                    
                    for (; mpz_cmp(counter, numbuffers) < 0; mpz_add_ui(counter, counter, 1)) {
                        double buf_x = music_samplenum_and_bufferidx_to_pixel(x, &rect, s-1, counter);
                        paint_circle_filled(g, bufferline_color, buf_x, y, 0.5);
                        if (buf_x > rect.width)
                            break;
                    }
                    
                    mpz_clear(counter);
                } else
                    painting_buffers_one_by_one = false;
                mpz_clear(numbuffers);
                mpfr_clear(ratio);
            }
        }
        
        if (this_x > rect.width)
            break;
        
        if (s > start_num_samples && fabs(diff) < 1) {
            paint_line(g, sample_ticks_color, this_x - 0.5, y, rect.width, y, 6);
            break;
        } else {
            paint_line(g, sample_ticks_color, this_x, y - 3, this_x, y + 3, 1);
            
            if (s > start_num_samples && fabs(diff) > 15) {
                char ticktext[2048];
                snprintf_zero(ticktext, 2048, "%ld·", s);
                
                double w, h;
                jfont_text_measure(jf, ticktext, &w, &h);
                
                if (fabs(diff) > w + 3)
                    write_text(g, jf, sample_ticks_color, ticktext, this_x - 100, y + 5, 200, 100, JGRAPHICS_TEXT_JUSTIFICATION_TOP | JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, true, false);
            }
        }
        
        prev_x = this_x;
        mpfr_set(prev_x_hp, this_x_hp, DADA_MUSIC_MPFR_RND);
    }
    mpfr_clear(this_x_hp);
    mpfr_clear(prev_x_hp);
    mpfr_clear(diff_hp);
    
    
    // paint line
    paint_line(g, bufferline_color, continuous_line_starts_from, y, rect.width, y, 1);

    
    // painting mousedown start
    t_jrgba mousestart_color = DADA_GREY_50;
    double mousedown_x = music_samplenum_and_bufferidx_to_pixel(x, &rect, x->mousedownnumsamps, x->mousedownbufferidx);
    paint_line(g, mousestart_color, mousedown_x, y, mousedown_x, y - 20, 1);
    paint_circle(g, DADA_GREY_75, mousestart_color, mousedown_x, y - 23, 3, 1);
    
    
    // painting global view
    y = DADA_MUSIC_GLOBAL_VIEW_POS * rect.height;
    {
        paint_line(g, bufferline_color, 0, y, rect.width, y, 1);
        
        t_rect r = build_rect(music_start_as_double(x) * rect.width, y - 4, music_domain_as_double(x) * rect.width, 8);
        t_jrgba smallrect_bordercolor = DADA_GREY_75;
        paint_rect(g, &r, &smallrect_bordercolor, NULL, 1, 0);
        
    }

    
    if (x->legend[0]) {
        double w, h;
        jfont_text_measure(jf, x->legend, &w, &h);
        write_text(g, jf, DADA_GREY_75, x->legend, 4, 4, rect.width - 8, rect.height - 8, JGRAPHICS_TEXT_JUSTIFICATION_TOPRIGHT, true, true);
        if (x->legend2[0])
            write_text(g, jf, DADA_GREY_75, x->legend2, 4, 4 + h, rect.width - 8, rect.height - 8 - h, JGRAPHICS_TEXT_JUSTIFICATION_TOPRIGHT, true, true);
    }
    
    dadaobj_paint_border(r_ob, g, &rect);
    
    jfont_destroy_debug(jf);
}


t_atom_long music_acceptsdrag(t_music *x, t_object *drag, t_object *view)
{
/*    if (jdrag_matchdragrole(drag, gensym("imagefile"), 0) && x->b_ob.d_ob.flags & DADAOBJ_BGIMAGE) {
        jdrag_box_add(drag, (t_object *)x, gensym("bgimage"));
        return true;
    } */
    return false;
}

void music_redraw_do(t_music *x, t_symbol *msg, long ac, t_atom *av)
{
    jbox_redraw((t_jbox *)x);
}

void music_post_array_do(t_music *x, t_symbol *msg, long ac, t_atom *av)
{
    long size;
    char *text = NULL;
    atom_gettext(ac, av, &size, &text, 0);
    post("%s", text);
    sysmem_freeptr(text);
}

void music_post_array(t_music *x, long num_elems, double *elems)
{
#ifdef MAC_VERSION
#ifdef DADA_MUSIC_DEBUG
    if (x->dsp_debug) {
        t_atom a[num_elems];
        long i;
        for (i = 0; i < num_elems; i++)
            atom_setfloat(a+i, elems[i]);
        defer_low(x, (method)music_post_array_do, NULL, num_elems, a);
    }
#endif
#endif
}


void music_perform64(t_music *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    int			i, n = sampleframes;
    t_uint16    *buf = x->buffer;
    long        buf_size = x->buffer_size;
    long        curr_sample = x->curr_play_sample;
    t_double	*out = outs[0];
    
    if (numouts < 1 || !x->is_playing_sample)
        goto zero;

    n = sampleframes;
    while (n--) {
        *out++ = (curr_sample < buf_size) ? samp_uint16_to_float(buf[curr_sample]) : 0;
        curr_sample++;
    }
    
    if (curr_sample >= buf_size) {
        // ended
        x->is_playing_sample = 0;
        defer(x, (method)music_buffer_next_and_play, NULL, 0, NULL);
    } else {
        x->curr_play_sample = curr_sample;
    }

/*
 
    // TO DO: buffer_locksamples might be called here just once for all buffers, instead of having it
    // called inside music_get_sample_rhotheta()
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
                sample = music_get_sample_rhotheta(x, *in0++, *in1++, i);
                FIX_DENORM_NAN_DOUBLE(sample);
                *out++ = sample;
            }
        } else {
            while (n--) {
                sample = music_get_sample_xy(x, *in0++, *in1++, i);
                FIX_DENORM_NAN_DOUBLE(sample);
                *out++ = sample;
            }
        }
        music_post_array(x, sampleframes, ins[0]);
        music_post_array(x, sampleframes, outs[0]);
    }
    
    if (x->startclock) {
        x->startclock = 0;
        clock_delay(x->clock, 0);
    }
*/
    
    return;
    
zero: // actually we'll never reach this line
    for (i = 0; i < numouts; i++) {
        t_double	*out = outs[i];
        n = sampleframes;
        while (n--)
            *out++ = 0.0;
    }
}

void music_dsp64(t_music *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    if (x->sr != samplerate) {
        x->sr = samplerate;
        reset_coords_to_zero(x, true);
    }
    object_method(dsp64, gensym("dsp_add64"), x, music_perform64, 0, NULL);
    x->startclock = true;
}


void music_anything_do(t_music *x, t_symbol *msg, long ac, t_atom *av)
{
    dadaobj_anything(dadaobj_cast(x), msg, ac, av);
    
    t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, msg, ac, av, LLLL_PARSE_CLONE);
    if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
        t_symbol *router = hatom_getsym(&parsed->l_head->l_hatom);
        llll_behead(parsed);
        
        if (dadaobj_anything_handle_domain_or_range(dadaobj_cast(x), router, parsed, 1)) {
            // nothing to do!
        } else if (router == gensym("zoomby") && parsed->l_head) {
            double factor = hatom_getdouble(&parsed->l_head->l_hatom);
            
            t_llllelem *center_el = parsed->l_head->l_next;
            if (center_el && hatom_gettype(&center_el->l_hatom) == H_SYM && hatom_getsym(&center_el->l_hatom) == _llllobj_sym_cursor) // zoom around cursor
                music_zoom_by_hp(x, factor, x->mousedowncoord_hp);
            else if (center_el && is_hatom_number(&center_el->l_hatom)) // zoom around specific point
                music_zoom_by(x, factor, hatom_getdouble(&center_el->l_hatom));
            else { // zoom around domain center
                mpfr_t temp;
                mpfr_init2(temp, x->mpfr_precision);
                mpfr_set(temp, x->screen_domain_hp, DADA_MUSIC_MPFR_RND);
                mpfr_mul_d(temp, temp, 0.5, DADA_MUSIC_MPFR_RND);
                mpfr_add(temp, temp, x->screen_start_hp, DADA_MUSIC_MPFR_RND);
                music_zoom_by_hp(x, factor, temp);
                mpfr_clear(temp);
            }
            jbox_redraw((t_jbox *)x);
            
        } else if (router == gensym("zoomexp") && parsed->l_head) {
            mpfr_t exponent;
            mpfr_init2(exponent, x->mpfr_precision);
            mpfr_set_d(exponent, hatom_getdouble(&parsed->l_head->l_hatom), DADA_MUSIC_MPFR_RND);
            
            t_llllelem *center_el = parsed->l_head->l_next;
            if (center_el && hatom_gettype(&center_el->l_hatom) == H_SYM && hatom_getsym(&center_el->l_hatom) == _llllobj_sym_cursor) // zoom around cursor
                music_zoom_exp_hp(x, exponent, x->mousedowncoord_hp);
            else if (center_el && is_hatom_number(&center_el->l_hatom)) { // zoom around specific point
                mpfr_t temp;
                mpfr_init2(temp, x->mpfr_precision);
                mpfr_set_d(temp, hatom_getdouble(&center_el->l_hatom), DADA_MUSIC_MPFR_RND);
                music_zoom_exp_hp(x, exponent, temp);
                mpfr_clear(temp);
            } else { // zoom around domain center
                mpfr_t temp;
                mpfr_init2(temp, x->mpfr_precision);
                mpfr_set(temp, x->screen_domain_hp, DADA_MUSIC_MPFR_RND);
                mpfr_mul_d(temp, temp, 0.5, DADA_MUSIC_MPFR_RND);
                mpfr_add(temp, temp, x->screen_start_hp, DADA_MUSIC_MPFR_RND);
                music_zoom_exp_hp(x, exponent, temp);
                mpfr_clear(temp);
            }
            
            mpfr_clear(exponent);
            jbox_redraw((t_jbox *)x);
            
        } else if ((router == gensym("setcursor") || router == gensym("cursor")) && parsed->l_head) {
            
            if (parsed->l_size == 1 && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
                t_buffer_ref *ref = buffer_ref_new((t_object *)x, hatom_getsym(&parsed->l_head->l_hatom));
                if (ref) {
                    x->mousedownnumsamps = music_buffer_to_numsamples_and_bufferidx(x, ref, x->mousedownbufferidx);
                    fill_mousedown_fields_from_samplenum_and_bufferidx(x);
                    object_free(ref);
                }
                
            } else if (parsed->l_size == 1 && is_hatom_number(&parsed->l_head->l_hatom)) {
                double coord = hatom_getdouble(&parsed->l_head->l_hatom);
                mpfr_set_d(x->mousedowncoord_hp, coord, DADA_MUSIC_MPFR_RND);
                fill_mousedown_fields_from_coord(x);
            
            } else if (parsed->l_size == 2 && is_hatom_number(&parsed->l_head->l_hatom) && is_hatom_number(&parsed->l_head->l_next->l_hatom)) {
                long samps = 0;
                mpz_t bufferidx;
                mpz_init(bufferidx);
                samps = hatom_getlong(&parsed->l_head->l_hatom);
                if (parsed->l_head->l_next && hatom_gettype(&parsed->l_head->l_next->l_hatom) == H_LONG) {
                    mpz_set_ui(bufferidx, hatom_getlong(&parsed->l_head->l_next->l_hatom));
                } else if (parsed->l_head->l_next && hatom_gettype(&parsed->l_head->l_next->l_hatom) == H_DOUBLE) {
                    mpfr_t phase;
                    mpfr_init2(phase, DADA_MUSIC_MPFR_PRECISION_HIGH);
                    mpfr_set_d(phase, hatom_getdouble(&parsed->l_head->l_next->l_hatom), DADA_MUSIC_MPFR_RND);
                    music_get_num_buffers_for_samplenum(x, samps, bufferidx);
                    mpfr_mul_z(phase, phase, bufferidx, DADA_MUSIC_MPFR_RND);
                    mpfr_get_z(bufferidx, phase, MPFR_RNDD);
                    mpfr_clear(phase);
                }
                music_samplenum_and_bufferidx_to_coord(x, samps, bufferidx, x->mousedowncoord_hp);
                fill_mousedown_fields_from_coord(x);
                mpz_clear(bufferidx);
                
            } else if (parsed->l_size >= 2 && hatom_gettype(&parsed->l_head->l_hatom) == H_LONG && hatom_gettype(&parsed->l_head->l_next->l_hatom) == H_SYM) {
                long samps = hatom_getlong(&parsed->l_head->l_hatom);

                // converting llll to hexadecimal
                long STEP_SIZE = 8192;
                long hex_string_allocated = STEP_SIZE;
                char *hex_string = (char *)bach_newptr(STEP_SIZE * sizeof(char));
                long cur = 0;
                for (t_llllelem *el = parsed->l_head->l_next; el; el = el->l_next) {
                    if (hatom_gettype(&el->l_hatom) != H_SYM) continue;
                    t_symbol *this_hex = hatom_getsym(&el->l_hatom);
                    if (this_hex) {
                        long this_len = strlen(this_hex->s_name);
                        while (cur + this_len + 1 >= hex_string_allocated) {
                            hex_string_allocated += STEP_SIZE;
                            hex_string = (char *)sysmem_resizeptr(hex_string, hex_string_allocated);
                        }
                        if (this_len >= 2 && this_hex->s_name[0] == '0' && this_hex->s_name[1] == 'x')
                            cur += snprintf_zero(hex_string + cur, this_len + 1, "%s", this_hex->s_name + 2);
                        else
                            cur += snprintf_zero(hex_string + cur, this_len + 1, "%s", this_hex->s_name);
                    }
                }
                hex_string[cur] = 0;
                
                mpz_t bufferidx;
                mpz_init(bufferidx);
                mpz_set_ui(bufferidx, 0);
                char c[2];
                c[1]=0;
                
                for (long i = 0; i < strlen(hex_string); i++) {
                    c[0] = hex_string[i];
                    mpz_mul_ui(bufferidx, bufferidx, 16);
                    mpz_add_ui(bufferidx, bufferidx, strtol(c, NULL, 16));
                }
                
                music_samplenum_and_bufferidx_to_coord(x, samps, bufferidx, x->mousedowncoord_hp);
                fill_mousedown_fields_from_coord(x);
                mpz_clear(bufferidx);
            } else if (hatom_gettype(&parsed->l_head->l_hatom) == H_SYM && parsed->l_head->l_next && hatom_gettype(&parsed->l_head->l_next->l_hatom) == H_LLLL) {
                t_llll *ll = hatom_getllll(&parsed->l_head->l_next->l_hatom);
                long samps = ll->l_size;
                long multiplier = powl(2, x->bitrate);
                mpz_t bufferidx;
                mpz_init(bufferidx);
                mpz_set_ui(bufferidx, 0);
                for (t_llllelem *elem = ll->l_head; elem; elem = elem->l_next) {
                    mpz_mul_ui(bufferidx, bufferidx, multiplier);
                    if (hatom_gettype(&elem->l_hatom) == H_LONG)
                        mpz_add_ui(bufferidx, bufferidx, hatom_getlong(&elem->l_hatom));
                    else if (hatom_gettype(&elem->l_hatom) == H_DOUBLE) {
                        double d = hatom_getdouble(&elem->l_hatom);
                        long l = floor((d + 1) * (multiplier/2));
                        mpz_add_ui(bufferidx, bufferidx, l);
                    }
                }
                music_samplenum_and_bufferidx_to_coord(x, samps, bufferidx, x->mousedowncoord_hp);
                fill_mousedown_fields_from_coord(x);
                mpz_clear(bufferidx);
            }
            
            if (router == gensym("cursor")) {
                music_buffer_set(x, x->mousedownnumsamps, x->mousedownbufferidx, x->mousedownphase_hp, 1);
                if (x->output_buffer)
                    music_output_buffer(x);
            }
            jbox_redraw((t_jbox *)x);
            
        } else if (router == gensym("getcursor")) {
            music_send_mousedown_notification(x, gensym("cursor"), true);

        } else if (router == gensym("next")) {
            music_buffer_next_do(x, false);
            if (x->output_buffer)
                music_output_buffer(x);

        } else if (router == gensym("resetzoom")) {
            mpfr_set_d(x->screen_start_hp, 0., DADA_MUSIC_MPFR_RND);
            mpfr_set_d(x->screen_domain_hp, 1., DADA_MUSIC_MPFR_RND);
            mpfr_set_d(x->screen_end_hp, 1., DADA_MUSIC_MPFR_RND);
            jbox_redraw((t_jbox *)x);
            
        } else if (router == gensym("play")) {
            x->curr_play_sample = 0;
            x->is_playing_sample = true;
            dadaobj_cast(x)->m_play.is_playing = true;
            jbox_redraw((t_jbox *)x);
        } else if (router == gensym("stop")) {
            x->curr_play_sample = 0;
            clock_unset(x->clock);
            x->is_playing_sample = false;
            dadaobj_cast(x)->m_play.is_playing = false;
            jbox_redraw((t_jbox *)x);
        }
    } else if (parsed) {
    }
    llll_free(parsed);
}

void music_anything(t_music *x, t_symbol *msg, long ac, t_atom *av)
{
    defer(x, (method)music_anything_do, msg, ac, av);
}

void music_iar(t_music *x)
{
    jbox_redraw((t_jbox *)x);
}

void music_tick(t_music *x)
{
    x->curr_play_sample = 0;
    x->is_playing_sample = true;
}






char *music_mpfr_get_str(int base, size_t size, mpfr_srcptr num_hp, mpfr_rnd_t precision, size_t cut_to_this_size)
{
    mpfr_exp_t exponent = 0;
    char *num_str = mpfr_get_str(NULL, &exponent, base, 0 /*size*/, num_hp, precision);
    char use_ellipsis = false;
    
    if (cut_to_this_size > 0 && cut_to_this_size < size) {
        use_ellipsis = true;
    }
    
    long len = strlen(num_str);

    if (exponent > 0)
        exponent = 0;
    exponent *= -1;
    
    char *res = (char *)bach_newptr((len + exponent + 4) * sizeof(char)); // + 4 is :
    
    char *pre_zeros = (char *)bach_newptr((exponent + 1) * sizeof(char));
    long i = 0;
    for (i = 0; i < exponent; i++)
        pre_zeros[i] = '0';
    pre_zeros[i] = 0;
    
    snprintf_zero(res, len + exponent + 1, "%s%s", pre_zeros, num_str);
    
    if (size < (len + exponent + 1))
        res[size] = 0;

    if (use_ellipsis && cut_to_this_size < (len + exponent + 1)) {
        res[cut_to_this_size] = res[cut_to_this_size+1] = res[cut_to_this_size+2] = '.';
        res[cut_to_this_size+3] = 0;
    }

    mpfr_free_str(num_str);
    
    bach_freeptr(pre_zeros);
    return res;
}

////// INTERFACE



void music_focusgained(t_music *x, t_object *patcherview)
{
    if (dadaobj_focusgained(dadaobj_cast(x), patcherview))
        return;
}

void music_focuslost(t_music *x, t_object *patcherview)
{
    if (dadaobj_focuslost(dadaobj_cast(x), patcherview))
        return;
}

void music_mousemove(t_music *x, t_object *patcherview, t_pt pt, long modifiers)
{
    
    llll_format_modifiers(&modifiers, NULL);
    
    if (dadaobj_mousemove(dadaobj_cast(x), patcherview, pt, modifiers))
        return;
    
    x->legend[0] = 0;
    if (x->b_ob.d_ob.m_interface.allow_mouse_hover) {
        if (!x->b_ob.d_ob.m_interface.mouse_is_down) {
            unsigned long numsamps = 0;
            t_rect rect;
            get_center_pix(dadaobj_cast(x), patcherview, &rect);
            music_pix_to_coord(x, &rect, pt, x->mousemovecoord_hp, false);

            char lowprec = 0;
            numsamps = music_coord_to_samplenum_and_bufferidx(x, x->mousemovecoord_hp, x->mousemovebufferidx, false, &lowprec);
            if (lowprec) {
                mpfr_set(x->mousemovephase_hp, x->mousemovecoord_hp, MPFR_RNDD);
                mpfr_frac(x->mousemovephase_hp, x->mousemovephase_hp, MPFR_RNDD);
            } else {
                music_get_num_buffers_for_samplenum(x, numsamps, x->mousemovetotnumbuffers);
                mpfr_set_z(x->mousemovephase_hp, x->mousemovebufferidx, MPFR_RNDD);
                mpfr_div_z(x->mousemovephase_hp, x->mousemovephase_hp, x->mousemovetotnumbuffers, MPFR_RNDD);
            }
            
            x->mousemovenumsamps = numsamps;
            
            char *phase_str = music_mpfr_get_str(16, numsamps * x->bitrate/4, x->mousemovephase_hp, DADA_MUSIC_MPFR_RND, 64);
            snprintf(x->legend, DADA_MUSIC_LEGEND_SIZE, "%ld samps (%.3f sec)", numsamps, (1.*numsamps)/x->sr);
            mpfr_snprintf(x->legend2, DADA_MUSIC_LEGEND_SIZE, "id: %ld.%s", numsamps, phase_str);
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

void post_buffer(t_music *x)
{
    for (long i = 0; i < x->buffer_size; i++) {
        post("%ld", x->buffer[i]);
    }
}

long music_char2int(char c)
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


void music_output_buffer(t_music *x)
{
    t_llll *ll = llll_get();
    long size = x->buffer_size;
    for (long i = 0; i < size; i++)
        llll_appenddouble(ll, samp_uint16_to_double(x->buffer[i]));
    llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UIMSP, 1, ll);
    llll_free(ll);
}

// MODE == 1 is the best one
void music_buffer_set(t_music *x, long num_samples, mpz_t bufferidx, mpfr_t phase_hp, char mode)
{
    if (num_samples == 0)
        num_samples = 1;
    
    if (x->buffer_size != num_samples) {
        x->buffer_size = num_samples;
        x->buffer = (uint16_t *)sysmem_resizeptr(x->buffer, num_samples * sizeof(uint16_t));
    }

    if (num_samples == 0) {
        x->buffer[0] = 32768;
        goto next;
    }

    if (mode == 0) {
        mpz_t q, r;
        mpz_init(r);
        mpz_init(q);
        mpz_set(q, bufferidx);
        
        for (long i = num_samples - 1; i >= 0; i--) {
            mpz_fdiv_qr_ui(q, r, q, 16);
            
            unsigned long this_samp, r_ui = mpz_get_ui(r);
            
            if (x->bitrate == 4) {
                this_samp = r_ui * 4096;
            } else if (x->bitrate == 8) {
                this_samp = r_ui * 256;
            } else {
                this_samp = r_ui;
            }
            
            x->buffer[i] = this_samp;
        }
        
        mpz_clear(q);
        mpz_clear(r);
        
    } else if (mode == 1) {
        char *bufferstr16 = mpz_get_str(NULL, 16, bufferidx);
        long len = strlen(bufferstr16);
        if (x->bitrate == 4) {
            for (long i = num_samples - 1, cur = len - 1; i >= 0; cur-=1, i--)
                x->buffer[i] = cur >= 0 ? music_char2int(bufferstr16[cur])*4096 : 0;
        } else if (x->bitrate == 8) {
            for (long i = num_samples - 1, cur = len - 2; i >= 0; cur-=2, i--)
                x->buffer[i] = cur >= 0 ? (music_char2int(bufferstr16[cur+1]) + 16 * music_char2int(bufferstr16[cur]))*256 : 0;
        } else {
            for (long i = num_samples - 1, cur = len - 4; i >= 0; cur-=4, i--)
                x->buffer[i] = cur >= 0 ? (music_char2int(bufferstr16[cur+3]) + 16 * music_char2int(bufferstr16[cur+2]) + 256 * music_char2int(bufferstr16[cur+1]) + 4096 * music_char2int(bufferstr16[cur])) : 0;
        }
        free(bufferstr16);
        
    } else {
        char *phase_str = music_mpfr_get_str(16, 0, phase_hp, DADA_MUSIC_MPFR_RND, 0);
        long phase_str_len = strlen(phase_str);
        long buffercur = 0;
        
        if (x->bitrate == 4) {
            for (long cur = 0; cur < phase_str_len && cur < num_samples; cur += 1)
                x->buffer[buffercur++] = music_char2int(phase_str[cur])*4096;
        } else if (x->bitrate == 8) {
            for (long cur = 0; cur+1 < phase_str_len && cur < num_samples; cur += 2)
                x->buffer[buffercur++] = music_char2int(phase_str[cur])*4096 + music_char2int(phase_str[cur+1])*256;
        } else if (x->bitrate == 16) {
            for (long cur = 0; cur+3 < phase_str_len && cur < num_samples; cur += 4)
                x->buffer[buffercur++] = music_char2int(phase_str[cur])*4096 + music_char2int(phase_str[cur+1])*256+ music_char2int(phase_str[cur+2])*16+ music_char2int(phase_str[cur+3]);
        }
    }

next:
    
    if (x->l_buffer_reference) {
        // sync buffer
        t_buffer_obj	*buffer = buffer_ref_getobject(x->l_buffer_reference);
        long frames, nc;
        
        t_atom a;
        atom_setlong(&a, num_samples);
        typedmess(buffer, gensym("sizeinsamps"), 1, &a);
        
        
        t_float	*tab = buffer_locksamples(buffer);
        if (!tab)
            goto end;
        
        frames = buffer_getframecount(buffer);
        nc = buffer_getchannelcount(buffer);
        
        if (nc == 1) {
            for (long i = 0; i < num_samples && i < frames; i++) {
                tab[i] = samp_uint16_to_float(x->buffer[i]);
            }
        } else if (nc > 1) {
            for (long i = 0; i < num_samples && i * nc + nc - 1 < frames; i++) {
                double val = samp_uint16_to_float(x->buffer[i]);
                for (long c = 0; c < nc; c++) {
                    tab[i * nc + c] = val;
                }
            }
        }
        
    end:
        buffer_unlocksamples(buffer);
    }
    
//     post_buffer(x);
//    bach_freeptr(phase_str);
}


long music_buffer_to_numsamples_and_bufferidx(t_music *x, t_buffer_ref *buffer_ref, mpz_t bufferidx)
{
    long num_samples = 0, nc = 1;
    t_buffer_obj *buffer = buffer_ref_getobject(buffer_ref);
    if (buffer) {
        mpz_t temp, multiplier;
        mpz_init(temp);
        mpz_init(multiplier);

        unsigned long numbitsteps = iexp2(x->bitrate);
        t_float	*tab = buffer_locksamples(buffer);
        if (!tab)
            goto end;
        
        num_samples = buffer_getframecount(buffer);
        nc = buffer_getchannelcount(buffer);
        
        mpz_set_ui(bufferidx, 0);
        mpz_set_ui(multiplier, 1);
        
        for (long i = num_samples - 1; i >= 0; i--) {
            double this_val = tab[i * nc];
            long quantized = MIN(numbitsteps - 1, ((this_val + 1.) * 0.5)*numbitsteps);

            mpz_mul_ui(temp, multiplier, quantized);
            mpz_add(bufferidx, bufferidx, temp);
            mpz_mul_ui(multiplier, multiplier, numbitsteps);
        }
        
        mpz_clear(temp);
        mpz_clear(multiplier);
        
    end:
        buffer_unlocksamples(buffer);
    }
    
    return num_samples;
}

void music_send_next_notification(t_music *x)
{
    switch (dadaobj_cast(x)->m_interface.send_notifications) {
        case DADAOBJ_NOTIFY_BASIC:
        case DADAOBJ_NOTIFY_VERBOSE:
            dadaobj_send_notification_sym(dadaobj_cast(x), gensym("next"));
            break;
            
        default:
            break;
    }
}

void music_buffer_next_do(t_music *x, char and_then_play)
{

    t_buffer_obj	*buffer = x->l_buffer_reference ? buffer_ref_getobject(x->l_buffer_reference) : NULL;
    t_float	*tab = NULL;
    long frames = 0, nc = 1;
    
    if (buffer) {
        tab = buffer_locksamples(buffer);
        if (tab) {
            frames = buffer_getframecount(buffer);
            nc = buffer_getchannelcount(buffer);
        }
    }
    
    char overflow = false;
    
    mpz_add_ui(x->mousedownbufferidx, x->mousedownbufferidx, 1);

    if (mpz_cmp(x->mousedownbufferidx, x->mousedowntotnumbuffers) >= 0) {
        overflow = true;
    } else {
        // increase this buffer
        long buffer_size = x->buffer_size;
        long i = buffer_size - 1;
        long step = 1;
        if (x->bitrate == 4)
            step = 4096;
        else if (x->bitrate == 8)
            step = 256;
        
        while (true) {
            long newval = ((long)x->buffer[i]) + step;
            if (newval < 65536) {
                x->buffer[i] = newval;
                if (buffer && tab) {
                    for (long c = 0; c < nc; c++) {
                        t_float f = samp_uint16_to_float(newval);
                        if (i * nc + c < frames)
                            tab[i * nc + c] = f;
                    }
                }
                break;
            } else {
                for (long j = i; j < buffer_size; j++) {
                    x->buffer[j] = 0;
                    if (buffer && tab) {
                        for (long c = 0; c < nc; c++) {
                            t_float f = samp_uint16_to_float(0);
                            if (j * nc + c < frames)
                                tab[j * nc + c] = f;
                        }
                    }
                }
                i--;
            }
            if (i < 0) {
                overflow = true;
                break;
            }
        }
    }
    
    if (buffer && tab) {
        buffer_unlocksamples(buffer);
        buffer_setdirty(buffer);
    }
    
    if (overflow) {
        // overflow! Next number of samples
        x->mousedownnumsamps++;
        x->buffer_size = x->mousedownnumsamps;
        sysmem_freeptr(x->buffer);
        x->buffer = (uint16_t *)sysmem_newptrclear(x->mousedownnumsamps * sizeof(uint16_t));
        
        if (buffer) {
            t_atom a;
            atom_setlong(&a, x->mousedownnumsamps);
            typedmess(buffer, gensym("sizeinsamps"), 1, &a);

            tab = buffer_locksamples(buffer);
            if (tab) {
                frames = buffer_getframecount(buffer);
                nc = buffer_getchannelcount(buffer);
                t_float f = samp_uint16_to_float(0);
                for (long i = 0; i < frames; i++) {
                    for (long c = 0; c < nc; c++) {
                        if (i * nc + c < frames)
                            tab[i * nc + c] = f;
                    }
                }
                buffer_unlocksamples(buffer);
            }
        }

        mpz_set_ui(x->mousedownbufferidx, 0);
        music_get_num_buffers_for_samplenum(x, x->mousedownnumsamps, x->mousedowntotnumbuffers);
    }
    
    music_send_next_notification(x);
    
    if (and_then_play) {
        clock_fdelay(x->clock, x->interval_ms);
    }
    
    jbox_redraw((t_jbox *)x);
}

void music_buffer_next(t_music *x, t_symbol *msg, long ac, t_atom *av)
{
    music_buffer_next_do(x, false);
}

void music_buffer_next_and_play(t_music *x, t_symbol *msg, long ac, t_atom *av)
{
    music_buffer_next_do(x, true);
}



void music_send_mousedown_notification(t_music *x, t_symbol *sym, char forceverbose)
{
    long n = dadaobj_cast(x)->m_interface.send_notifications;
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
            llll_appenddouble(ll, mpfr_get_d(x->mousedowncoord_hp, DADA_MUSIC_MPFR_RND));
            llll_appendlong(sub_ll, x->mousedownnumsamps);
            llll_appenddouble(sub_ll, mpfr_get_d(x->mousedownphase_hp, DADA_MUSIC_MPFR_RND));
            llll_appendllll(ll, sub_ll);
            dadaobj_send_notification_llll(dadaobj_cast(x), ll);
        }
            break;
        
        default:
            break;
    }
}

void music_mousedown(t_music *x, t_object *patcherview, t_pt pt, long modifiers)
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
        
        
        // SCROLLBAR
        if (fabs(pt.y - DADA_MUSIC_GLOBAL_VIEW_POS * rect.height) < 10) {
            // set screen starting point
            // screen_start = pt.x/rect.width
            
            x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = 1; // scrollbar
            
            mpfr_set_d(x->screen_start_hp, pt.x/rect.width, DADA_MUSIC_MPFR_RND);
            
            if (mpfr_cmp_d(x->screen_start_hp, 0.) < 0)
                mpfr_set_d(x->screen_start_hp, 0., DADA_MUSIC_MPFR_RND);
            
            mpfr_add(x->screen_end_hp, x->screen_start_hp, x->screen_domain_hp, DADA_MUSIC_MPFR_RND);
            
            if (mpfr_cmp_d(x->screen_end_hp, 1.) > 0) {
                mpfr_set_d(x->screen_end_hp, 1., DADA_MUSIC_MPFR_RND);
                mpfr_sub(x->screen_start_hp, x->screen_end_hp, x->screen_domain_hp, DADA_MUSIC_MPFR_RND);
            }
            
        // PLAYSTART
        } else if (fabs(pt.y - DADA_MUSIC_MAIN_VIEW_POS * rect.height) < 40){
            
            t_rect rect;
            get_center_pix(dadaobj_cast(x), patcherview, &rect);
            music_pix_to_coord(x, &rect, pt, x->mousedowncoord_hp, true);
            
/*
            mpfr_exp_t exponent;
            char *num_str = mpfr_get_str(NULL, &exponent, 10, 0, x->mousedowncoord_hp, GMP_RNDN);
            post("%s", num_str);
  */
            
            fill_mousedown_fields_from_coord(x);
            
            x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = 2; // playstart

            music_buffer_set(x, x->mousedownnumsamps, x->mousedownbufferidx, x->mousedownphase_hp, 1);

            if (x->output_buffer)
                music_output_buffer(x);
            
            music_send_mousedown_notification(x, gensym("movedcursor"), false);
            
        }
    }
    
    jbox_redraw((t_jbox *)x);
    
}

void music_mouseup(t_music *x, t_object *patcherview, t_pt pt, long modifiers)
{
    llll_format_modifiers(&modifiers, NULL);
    
    if (dadaobj_mouseup(dadaobj_cast(x), patcherview, pt, modifiers))
        return;
}




void music_mousedrag(t_music *x, t_object *patcherview, t_pt pt, long modifiers)
{
    llll_format_modifiers(&modifiers, NULL);
    
    if (dadaobj_mousedrag(dadaobj_cast(x), patcherview, pt, modifiers))
        return;
    
    switch (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type) {
        case 1: // scrollbar
        {
            t_rect rect;
            get_center_pix(dadaobj_cast(x), patcherview, &rect);

            if (modifiers & eShiftKey) {
                
                mpfr_set_d(x->screen_end_hp, pt.x/rect.width, DADA_MUSIC_MPFR_RND);

                if (mpfr_cmp(x->screen_start_hp, x->screen_end_hp) >= 0) {
                    mpfr_set(x->screen_end_hp, x->screen_start_hp, DADA_MUSIC_MPFR_RND);
                    mpfr_add_d(x->screen_end_hp, x->screen_end_hp, 0.00000001, DADA_MUSIC_MPFR_RND);
                }

                if (mpfr_cmp_d(x->screen_start_hp, 0.) < 0)
                    mpfr_set_d(x->screen_start_hp, 0., DADA_MUSIC_MPFR_RND);
                
                mpfr_sub(x->screen_domain_hp, x->screen_end_hp, x->screen_start_hp, DADA_MUSIC_MPFR_RND);
                
                if (mpfr_cmp_d(x->screen_end_hp, 1.) > 0) {
                    mpfr_set_d(x->screen_end_hp, 1., DADA_MUSIC_MPFR_RND);
                    mpfr_sub(x->screen_start_hp, x->screen_end_hp, x->screen_domain_hp, DADA_MUSIC_MPFR_RND);
                }
                
            } else {
                mpfr_set_d(x->screen_start_hp, pt.x/rect.width, DADA_MUSIC_MPFR_RND);
                
                if (mpfr_cmp_d(x->screen_start_hp, 0.) < 0)
                    mpfr_set_d(x->screen_start_hp, 0., DADA_MUSIC_MPFR_RND);
                
                mpfr_add(x->screen_end_hp, x->screen_start_hp, x->screen_domain_hp, DADA_MUSIC_MPFR_RND);

                if (mpfr_cmp(x->screen_end_hp, x->screen_start_hp) < 0) {
                    mpfr_swap(x->screen_end_hp, x->screen_start_hp);
                    
                    if (mpfr_cmp_d(x->screen_start_hp, 0.) < 0)
                        mpfr_set_d(x->screen_start_hp, 0., DADA_MUSIC_MPFR_RND);
                }

                if (mpfr_cmp_d(x->screen_end_hp, 1.) > 0) {
                    mpfr_set_d(x->screen_end_hp, 1., DADA_MUSIC_MPFR_RND);
                    mpfr_sub(x->screen_start_hp, x->screen_end_hp, x->screen_domain_hp, DADA_MUSIC_MPFR_RND);
                }
            }
            jbox_redraw((t_jbox *)x);
        }
            break;
            
        case 2:
        {
            unsigned long numsamps = 0;
            unsigned long old_numsamps = x->mousedownnumsamps;

            mpz_t temp;
            mpz_init(temp);
            mpz_set(temp, x->mousedownbufferidx);
            
            t_rect rect;
            get_center_pix(dadaobj_cast(x), patcherview, &rect);
            music_pix_to_coord(x, &rect, pt, x->mousedowncoord_hp, true);
            
            numsamps = music_coord_to_samplenum_and_bufferidx(x, x->mousedowncoord_hp, x->mousedownbufferidx, true, NULL);
            music_get_num_buffers_for_samplenum(x, numsamps, x->mousedowntotnumbuffers);
            
            mpfr_set_z(x->mousedownphase_hp, x->mousedownbufferidx, MPFR_RNDD);
            mpfr_div_z(x->mousedownphase_hp, x->mousedownphase_hp, x->mousedowntotnumbuffers, MPFR_RNDD);
            
            x->mousedownnumsamps = numsamps;
            
            char *phase_str = music_mpfr_get_str(16, numsamps * x->bitrate/4, x->mousedownphase_hp, DADA_MUSIC_MPFR_RND, 64);
            snprintf(x->legend, DADA_MUSIC_LEGEND_SIZE, "%ld samps (%.3f sec)", numsamps, (1.*numsamps)/x->sr);
            mpfr_snprintf(x->legend2, DADA_MUSIC_LEGEND_SIZE, "id: %ld.%s", numsamps, phase_str);
            bach_freeptr(phase_str);

            
            if (x->mousedownnumsamps <= 0) {
                x->mousedownnumsamps = 0;
                mpfr_set_d(x->mousedownphase_hp, 0., DADA_MUSIC_MPFR_RND);
                mpfr_set_d(x->mousedowncoord_hp, 0., DADA_MUSIC_MPFR_RND);
            }
            if (old_numsamps != x->mousedownnumsamps
                || mpz_cmp(temp, x->mousedownbufferidx)) {
                music_buffer_set(x, numsamps, x->mousedownbufferidx, x->mousedownphase_hp, 1);
                if (x->output_buffer)
                    music_output_buffer(x);
                music_send_mousedown_notification(x, gensym("movedcursor"), false);
            }

            mpz_clear(temp);
            jbox_redraw((t_jbox *)x);
        }
            break;
            
        default:
            break;
    }
}


void change_precision_according_to_domain(t_music *x)
{
    if (x->high_precision_display) {
        mpfr_t temp;
        mpfr_init2(temp, mpfr_get_prec(x->screen_domain_hp));
        mpfr_set(temp, x->screen_domain_hp, DADA_MUSIC_MPFR_RND);
        
        mpfr_d_div(temp, 1.*DADA_MUSIC_MPFR_PRECISION, temp, DADA_MUSIC_MPFR_RND);
        long new_precision = mpfr_get_ui(temp, MPFR_RNDD);
        
        //    post("new precision: %ld", new_precision);
        
        change_precision(x, new_precision);
        
        mpfr_clear(temp);
    }
}

void music_zoom_by_hp(t_music *x, double zoom_factor, mpfr_t around_this_coord_hp)
{
    mpfr_t temp;
    mpfr_init2(temp, mpfr_get_prec(around_this_coord_hp));
    
    mpfr_set(temp, x->screen_start_hp, DADA_MUSIC_MPFR_RND);
    mpfr_sub(temp, temp, around_this_coord_hp, DADA_MUSIC_MPFR_RND);
    mpfr_div_d(temp, temp, zoom_factor, DADA_MUSIC_MPFR_RND);
    mpfr_add(temp, temp, around_this_coord_hp, DADA_MUSIC_MPFR_RND);
    mpfr_set(x->screen_start_hp, temp, DADA_MUSIC_MPFR_RND);

    mpfr_set(temp, x->screen_end_hp, DADA_MUSIC_MPFR_RND);
    mpfr_sub(temp, temp, around_this_coord_hp, DADA_MUSIC_MPFR_RND);
    mpfr_div_d(temp, temp, zoom_factor, DADA_MUSIC_MPFR_RND);
    mpfr_add(temp, temp, around_this_coord_hp, DADA_MUSIC_MPFR_RND);
    mpfr_set(x->screen_end_hp, temp, DADA_MUSIC_MPFR_RND);

    if (mpfr_cmp_d(x->screen_start_hp, 0.) < 0)
        mpfr_set_d(x->screen_start_hp, 0., DADA_MUSIC_MPFR_RND);

    if (mpfr_cmp_d(x->screen_end_hp, 1.) > 0)
        mpfr_set_d(x->screen_end_hp, 1., DADA_MUSIC_MPFR_RND);

/*    if (mpfr_cmp(x->screen_end_hp, x->screen_start_hp) <= 0) {
        mpfr_add_d(x->screen_end_hp, x->screen_start_hp, 0.000000001, DADA_MUSIC_MPFR_RND);
    } */

    mpfr_sub(x->screen_domain_hp, x->screen_end_hp, x->screen_start_hp, DADA_MUSIC_MPFR_RND);
    
    change_precision_according_to_domain(x);
    
    mpfr_clear(temp);
}

void music_zoom_by(t_music *x, double zoom_factor, double around_this_coord)
{
    mpfr_t temp;
    mpfr_init2(temp, x->mpfr_precision);
    mpfr_set_d(temp, around_this_coord, DADA_MUSIC_MPFR_RND);
    music_zoom_by_hp(x, zoom_factor, temp);
    mpfr_clear(temp);
}

void music_zoom_exp_hp(t_music *x, mpfr_t zoom_exponent, mpfr_t around_this_coord_hp)
{
    mpfr_t temp;
    char negative = 0;
    mpfr_init2(temp, mpfr_get_prec(around_this_coord_hp));
    
    mpfr_set(temp, x->screen_start_hp, DADA_MUSIC_MPFR_RND);
    mpfr_sub(temp, temp, around_this_coord_hp, DADA_MUSIC_MPFR_RND);
    if (mpfr_cmp_d(temp, 0.) < 0) {
        negative = 1;
        mpfr_abs(temp, temp, DADA_MUSIC_MPFR_RND);
    }
    mpfr_pow(temp, temp, zoom_exponent, DADA_MUSIC_MPFR_RND);
    if (negative)
        mpfr_mul_d(temp, temp, -1., DADA_MUSIC_MPFR_RND);
    mpfr_add(temp, temp, around_this_coord_hp, DADA_MUSIC_MPFR_RND);
    mpfr_set(x->screen_start_hp, temp, DADA_MUSIC_MPFR_RND);
    
    negative = 0;
    mpfr_set(temp, x->screen_end_hp, DADA_MUSIC_MPFR_RND);
    mpfr_sub(temp, temp, around_this_coord_hp, DADA_MUSIC_MPFR_RND);
    if (mpfr_cmp_d(temp, 0.) < 0) {
        negative = 1;
        mpfr_abs(temp, temp, DADA_MUSIC_MPFR_RND);
    }
    mpfr_pow(temp, temp, zoom_exponent, DADA_MUSIC_MPFR_RND);
    if (negative)
        mpfr_mul_d(temp, temp, -1., DADA_MUSIC_MPFR_RND);
    mpfr_add(temp, temp, around_this_coord_hp, DADA_MUSIC_MPFR_RND);
    mpfr_set(x->screen_end_hp, temp, DADA_MUSIC_MPFR_RND);
    
    if (mpfr_cmp_d(x->screen_start_hp, 0.) < 0)
        mpfr_set_d(x->screen_start_hp, 0., DADA_MUSIC_MPFR_RND);
    
    if (mpfr_cmp_d(x->screen_end_hp, 1.) > 0)
        mpfr_set_d(x->screen_end_hp, 1., DADA_MUSIC_MPFR_RND);
    
/*    if (mpfr_cmp(x->screen_end_hp, x->screen_start_hp) <= 0) {
        mpfr_add_d(x->screen_end_hp, x->screen_start_hp, 0.000000001, DADA_MUSIC_MPFR_RND);
    } */
    
    mpfr_sub(x->screen_domain_hp, x->screen_end_hp, x->screen_start_hp, DADA_MUSIC_MPFR_RND);
    
    change_precision_according_to_domain(x);
    
    mpfr_clear(temp);
}



void music_mousewheel(t_music *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc)
{
    llll_format_modifiers(&modifiers, NULL);  
    t_dadaobj *r_ob = dadaobj_cast(x);
    
    
    if (modifiers & eCommandKey) {
        
        double zoom_factor = exp(-y_inc * 0.01 * (modifiers & eShiftKey ? DADA_FINER_FROM_KEYBOARD : 1.));
        
        t_rect rect;
        mpfr_t temp_hp;
        mpfr_init2(temp_hp, x->mpfr_precision);
        get_center_pix(r_ob, view, &rect);
        music_pix_to_coord(x, &rect, pt, temp_hp, false);
        
        music_zoom_by_hp(x, zoom_factor, temp_hp);
        
        mpfr_clear(temp_hp);
    
    } else if (x_inc != 0){
        
        mpfr_t toadd_hp;
        mpfr_init2(toadd_hp, x->mpfr_precision);
        mpfr_mul_d(toadd_hp, x->screen_domain_hp, - 0.01 * x_inc, DADA_MUSIC_MPFR_RND);
        
        mpfr_add(x->screen_start_hp, x->screen_start_hp, toadd_hp, DADA_MUSIC_MPFR_RND);
        
        if (mpfr_cmp_d(x->screen_start_hp, 0.) < 0)
            mpfr_set_d(x->screen_start_hp, 0., DADA_MUSIC_MPFR_RND);

        mpfr_add(x->screen_end_hp, x->screen_start_hp, x->screen_domain_hp, DADA_MUSIC_MPFR_RND);

        if (mpfr_cmp_d(x->screen_end_hp, 1.) > 0) {
            mpfr_set_d(x->screen_end_hp, 1., DADA_MUSIC_MPFR_RND);
            mpfr_sub(x->screen_start_hp, x->screen_end_hp, x->screen_domain_hp, DADA_MUSIC_MPFR_RND);
        }
        
        mpfr_clear(toadd_hp);
    }
    
    /*
    if (dadaobj_mousewheel(dadaobj_cast(x), view, pt, modifiers, x_inc, y_inc)) {
        jbox_invalidate_layer((t_object *)x, NULL, gensym("network"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
        jbox_redraw((t_jbox *)x);
        return;
    } */
}




long music_keyup(t_music *x, t_object *patcherview, long keycode, long modifiers, long textcharacter){
    
    llll_format_modifiers(&modifiers, &keycode);
    
    if (dadaobj_keyup(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
        return 1;
    
    return 0;
}

long music_key(t_music *x, t_object *patcherview, long keycode, long modifiers, long textcharacter)
{
    
    
    llll_format_modifiers(&modifiers, &keycode);
    
    if (dadaobj_key(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter)) {
        return 1;
    }
    
    
    if (keycode == JKEY_SPACEBAR) {
        music_int(x, !dadaobj_cast(x)->m_play.is_playing);
        return 1;
    } else if (keycode == JKEY_ESC) {
        // reset zoom
        mpfr_set_d(x->screen_start_hp, 0., DADA_MUSIC_MPFR_RND);
        mpfr_set_d(x->screen_end_hp, 1., DADA_MUSIC_MPFR_RND);
        mpfr_set_d(x->screen_domain_hp, 1., DADA_MUSIC_MPFR_RND);
        jbox_redraw((t_jbox *)x);
        return 1;
    } else if (keycode == JKEY_RETURN) {
        // reset zoom
        reset_coords_to_zero(x, false);
        jbox_redraw((t_jbox *)x);
        return 1;
    } else if (keycode == JKEY_TAB) {
        // set coord around player
        
        mpfr_t toadd_hp;
        mpfr_init2(toadd_hp, mpfr_get_prec(x->screen_domain_hp));
        mpfr_mul_d(toadd_hp, x->screen_domain_hp, 0.5, DADA_MUSIC_MPFR_RND);
        
        mpfr_add(x->screen_end_hp, x->mousedowncoord_hp, toadd_hp, DADA_MUSIC_MPFR_RND);
        mpfr_sub(x->screen_start_hp, x->mousedowncoord_hp, toadd_hp, DADA_MUSIC_MPFR_RND);
        
        if (mpfr_cmp_d(x->screen_start_hp, 0.) < 0)
            mpfr_set_d(x->screen_start_hp, 0., DADA_MUSIC_MPFR_RND);

        if (mpfr_cmp_d(x->screen_end_hp, 1.) > 0)
            mpfr_set_d(x->screen_end_hp, 1., DADA_MUSIC_MPFR_RND);

        mpfr_sub(x->screen_domain_hp, x->screen_end_hp, x->screen_start_hp, DADA_MUSIC_MPFR_RND);
        mpfr_clear(toadd_hp);
        jbox_redraw((t_jbox *)x);
        return 1;
    }
    return 0;
}



void music_mouseenter(t_music *x, t_object *patcherview, t_pt pt, long modifiers)
{
    if (dadaobj_mouseenter(dadaobj_cast(x), patcherview, pt, modifiers))
        return;
}

void music_mouseleave(t_music *x, t_object *patcherview, t_pt pt, long modifiers)
{
    x->legend[0] = 0;
    x->legend[1] = 0;
    if (dadaobj_mouseleave(dadaobj_cast(x), patcherview, pt, modifiers))
        return;
}


