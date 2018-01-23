/**
	@file
	dada.bodies.c
	
	@name
	dada.bodies
	
	@realname
	dada.bodies
 
	@type
	object
	
	@module
	dada
 
	@author
	Daniele Ghisi
	
	@digest
	Music via gravitation
	
	@description
	Implements a simplified model of a universe with steady stars being played by the passage of planets.
	
	@discussion
 
	@category
	dada, dada interfaces, dada geometry
 
	@keywords
	body, bodies, gravity, attract, law, Newton, universe, test, play
	
	@seealso
	dada.bounce, dada.kaleido, dada.life
	
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

#define DADA_BODIES_MAX_BODIES 64
#define DADA_BODIES_MAX_PARTICLES 64
#define	DADA_BODIES_MAX_ARROWNOTES 30
#define DADA_BODIES_PARTICLE_RADIUS 2
#define DADA_BODIES_ARROWNOTE_ADDITIONAL_RADIUS 6
#define DADA_BODIES_ARROWNOTE_END_PT_RADIUS 2.5
#define DADA_BODIES_THRESHOLD_FOR_ANGLES 0.3
#define DADA_BODIES_SELECTION_PAD 4

#define DADA_BODIES_MIN_LIGHTNESS 0.05
#define DADA_BODIES_MAX_LIGHTNESS 0.8

#define DADA_BODIES_DEFAULT_X_SPEED 150

t_class	*s_bodies_class = NULL;
typedef t_uint64 t_particles_bitfield;		///< A bitfield with each bit corresponding to a particle


t_clipboard clipboard = {k_NONE, k_NOTATION_OBJECT_CUSTOM, NULL, NULL, 0.};

enum
{
    DADAITEM_TYPE_BODIES_BODY = 120,
    DADAITEM_TYPE_BODIES_PARTICLE = 121,
    DADAITEM_TYPE_BODIES_ARROWNOTE = 122,
};

typedef enum _law_type
{
    DADA_BODIES_LAW_NEWTON = 0,
    DADA_BODIES_LAW_NEWTON_OUTSIDE = 1,
    DADA_BODIES_LAW_CUSTOM = 2,
    DADA_BODIES_LAW_NONE = 3
} e_law_type;

typedef enum _approx_method
{
	k_METHOD_EULER = 0,
	k_METHOD_LEAPFROG = 1,
	k_METHOD_RUNGE_KUTTA = 2,
} e_approx_method;

typedef struct _arrownote
{
    double	angle;
	double	midicents;
	
	t_pt	label_center;
	double	label_width;
	double	label_height;
	char	label_text[10];
} t_arrownote;


typedef struct _body
{
    t_dadaitem  r_it;
	double		mass;
    double		density;
	double		radius;
	
	long		num_arrownotes;
	t_arrownote	arrownote[DADA_BODIES_MAX_ARROWNOTES];

    long        midichannel;
	char		mode;
} t_body;


typedef struct _particle
{
    t_dadaitem  r_it;
	t_pt		speed;		// speed
	t_pt		acc;		// acceleration

    t_pt		a_i1;		//< next acceleration

    long        midichannel;
} t_particle;


typedef struct _bodies
{
    t_dadaobj_jbox		b_ob; // root object

	t_body		*body;
	long		num_bodies;

	t_particle	*particle;
	long		num_particles;
	
	double		G;
    

	long		tone_division;
	
	// colors
	char		show_bodies_id;
	char		show_particles_id;
    char		show_density;
    char		show_notes;

	long		cycle_num;		///< Number of cycle since last play
	double		time;
	
	char                    show_speed;
	char                    show_acceleration;
    t_particles_bitfield    follow_particle;
	
	char		approx_method;
	char		running;
	char		hide_while_running;
    
    char        must_follow;
	
	long		last_played_note[DADA_BODIES_MAX_BODIES];
    long		last_played_arrow[DADA_BODIES_MAX_BODIES];

	char		use_particle_midichannels;
    char        use_idx_as_channel;
	char		there_are_solo_bodies;
	char		there_are_solo_particles;
	char		there_are_solitary_bodies;

	char		playback;
    char		sendhitdata;
//	char		playtoroll;
    char        highlight_play;

	double		zero_velocity_distance;
	double		max_velocity_distance;
//	double		max_velocity_radius;
	double		velocity_slope;
	
	// law
    e_law_type  law_type;
	long		law_ac;
	t_atom		law_av[100];	
	t_lexpr		*n_lexpr;		///< Expression evaluator
	t_lexpr		*n_lexpr2;		///< Expression evaluator for calculating velocity in circular motion

	// popup menu
	t_jfont *popup_main_font;					
	t_jfont *popup_secondary_font;				
	t_jpopupmenu *popup_body;					
	t_jpopupmenu *popup_body_midichannels;		
	t_jpopupmenu *popup_body_transpose;		
	t_jpopupmenu *popup_particle_midichannels;	
	t_jpopupmenu *popup_particle_forceperiod;	
	t_jpopupmenu *popup_particle;				
	t_jpopupmenu *popup_background;				
	
    t_object *patcher_parent;
    
	// outlets
	void		*out1;
	void		*out2;
	void		*out3;
	void		*out4;

	// proxy
	long		n_in;
	void		*proxy;
} t_bodies;

typedef struct _pt4
{
	double x;
	double y;
	double z;
	double w;
} t_pt4;


void bodies_assist(t_bodies *x, void *b, long m, long a, char *s);
t_bodies* bodies_new(t_symbol *s, long argc, t_atom *argv);

void bodies_int(t_bodies *x, long n);
void bodies_float(t_bodies *x, double num);
void bodies_free(t_bodies *x);

void bodies_paint(t_bodies *x, t_object *view);

void bodies_mousedrag(t_bodies *x, t_object *patcherview, t_pt pt, long modifiers);
void bodies_mousedown(t_bodies *x, t_object *patcherview, t_pt pt, long modifiers);
void bodies_mouseup(t_bodies *x, t_object *patcherview, t_pt pt, long modifiers);
void bodies_mousedoubleclick(t_bodies *x, t_object *patcherview, t_pt pt, long modifiers);
void bodies_mousewheel(t_bodies *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc);
void bodies_mousemove(t_bodies *x, t_object *patcherview, t_pt pt, long modifiers);
long bodies_key(t_bodies *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
long bodies_keyup(t_bodies *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
//void bodies_focusgained(t_bodies *x, t_object *patcherview);
//void bodies_focuslost(t_bodies *x, t_object *patcherview);

void bodies_anything(t_bodies *x, t_symbol *s, long argc, t_atom *argv);
void uniformly_distribute_arrownotes(t_bodies *x, long body_idx, char add_mirror);

t_llll *bodies_get_state(t_bodies *x);
void bodies_set_state(t_bodies *x, t_llll *status);
t_llll *get_curr_state(t_bodies *x, char get_bodies, char get_particles);
void bodies_set_state_from_gimme(t_bodies *x, t_symbol *s, long argc, t_atom *argv);
void set_arrows_from_gimme(t_bodies *x, t_symbol *s, long argc, t_atom *argv);
void set_equally_spaced_arrows_from_gimme(t_bodies *x, t_symbol *s, long argc, t_atom *argv);
void update_mass_from_density_and_radius_for_body(t_bodies *x, long i);
void update_mass_from_density_and_radius(t_bodies *x);
void bodies_postprocess_undo(t_bodies *x);
void bodies_undo_step_push(t_bodies *x, t_symbol *operation);
void bodies_set_body_state(t_bodies *x, long idx, t_llll *this_body);
void bodies_set_particle_state(t_bodies *x, long idx, t_llll *this_particle);
void force_circular_motion_for_particle(t_bodies *x, long particle_idx, char also_put_to_zero_position);
void send_noteoff(t_bodies *x, long idx);
void bodies_autozoom(t_bodies *x, t_object *view, t_rect *rect);
void bodies_follow(t_bodies *x, t_object *view, t_rect *rect);


void send_values(t_bodies *x);
void bodies_preset(t_bodies *x);
void bodies_end_preset(t_bodies *x);
void bodies_begin_preset(t_bodies *x, t_symbol *s, long argc, t_atom *argv);
void bodies_restore_preset(t_bodies *x, t_symbol *s, long argc, t_atom *argv);

void bodies_task(t_bodies *x);
void bodies_play(t_bodies *x, t_symbol *s, long argc, t_atom *argv);
void bodies_stop(t_bodies *x, t_symbol *s, long argc, t_atom *argv);
void bodies_clock(t_bodies *x, t_symbol *s);
	
void bodies_jsave(t_bodies *x, t_dictionary *d);

t_max_err bodies_notify(t_bodies *x, t_symbol *s, t_symbol *msg, void *sender, void *data);

t_pt4 build_pt4(double x, double y, double z, double w);
t_pt get_topleft_angle_for_writing_around_the_clock(t_pt center, double radius, double alpha, double label_width, double label_height);
double delta_coord_to_angle(t_bodies *x, t_pt center, t_pt pt);
double pt_to_angle(t_bodies *x, t_pt center, t_pt pt);
double delta_coord_to_angle_from_the_top(t_bodies *x, t_pt center, t_pt pt);
void force_particle_period(t_bodies *x, long particle_idx, double period);
void compute_label_for_all_arrownotes(t_bodies *x, long body_idx);
void recompute_solo_flag(t_bodies *x);

long add_body_from_llll(t_bodies *x, t_llll *body_as_llll);
long add_body(t_bodies *x, t_pt position, double density, double radius, t_jrgba color, long midichannel);
t_llll *get_body_info_as_llll(t_bodies *x, long body_idx);
t_llll *get_particle_info_as_llll(t_bodies *x, long particle_idx);

void bodies_forceperiod(t_bodies *x, t_symbol *s, long argc, t_atom *argv);
void bodies_forcecircular(t_bodies *x, t_symbol *s, long argc, t_atom *argv);
void bodies_restart(t_bodies *x);
void bodies_dump(t_bodies *x, char dump_bodies, char dump_particles);
void bodies_settime(t_bodies *x, double time);

t_max_err bodies_setattr_law(t_bodies *x, void *attr, long ac, t_atom *av);
void bodies_clear(t_bodies *x, t_symbol *s, long argc, t_atom *argv);


void bodies_initialize_popup_menus(t_bodies *x);
void bodies_destroy_popup_menus(t_bodies *x);



const char *lexpr_subs[] = {"G", "m", "d", "r"};
const long lexpr_subs_count = 4;




void copy_body(t_bodies *x, long body_idx){
	clipboard.type = (e_element_types)DADAITEM_TYPE_BODIES_BODY;
	clipboard.gathered_syntax = get_body_info_as_llll(x, body_idx);
}

void paste(t_bodies *x, t_pt where){
	if (clipboard.type == DADAITEM_TYPE_BODIES_BODY) {
		long id = add_body_from_llll(x, clipboard.gathered_syntax);
		x->body[id].r_it.coord = where;
		compute_label_for_all_arrownotes(x, id);
		jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
	}
}


void bodies_clear(t_bodies *x, t_symbol *s, long argc, t_atom *argv){
    char bodies = true, particles = true;
    bodies_undo_step_push(x, gensym("Clear"));
    if ((argc >= 1) && (atom_gettype(argv) == A_SYM)) {
        if (atom_getsym(argv) == gensym("bodies") || (atom_getsym(argv) == gensym("stars")))
            particles = false;
        else if (atom_getsym(argv) == gensym("particles") || atom_getsym(argv) == gensym("planets"))
            bodies = false;
    }
    if (bodies)
        x->num_bodies = 0;
    if (particles)
        x->num_particles = 0;
	jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
	jbox_redraw((t_jbox *) x);
}



void bodies_jsave(t_bodies *x, t_dictionary *d)
{
	//post("***** JSAVE *****");
	t_llll *whole_info = get_curr_state(x, true, true);
	llll_store_in_dictionary(whole_info, d, "whole_bodies_data", NULL);
	llll_free(whole_info);
}

int C74_EXPORT main(void)
{
	t_class *c;
	
	common_symbols_init();
	llllobj_common_symbols_init();
	
	if (dada_check_bach_version() || llllobj_test()) {
		dada_error_bachcheck();
		return 1;
	}
	
	c = class_new("dada.bodies", 
							(method)bodies_new,
							(method)bodies_free,
							sizeof(t_bodies),
							(method)NULL,
							A_GIMME,
							0L);
	
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	
	jbox_initclass(c, JBOX_FIXWIDTH);
//	jbox_initclass(c, JBOX_COLOR | JBOX_FIXWIDTH | JBOX_FONTATTR);
	
	class_addmethod(c, (method) bodies_paint, "paint", A_CANT, 0);
	class_addmethod(c, (method) bodies_int, "int", A_LONG, 0);
	class_addmethod(c, (method) bodies_float, "float", A_FLOAT, 0);
	
    // @method (mouse) @digest Edit content
    // @description
    // @copy DADA_DOC_MOUSE_COMMANDS_STANDARD_NAVIGATION
    // • <m>click+drag</m> on an element ot move it<br />
    //    ↪ Add the <m>Alt</m> key to duplicate it<br />
    // • <m>Cmd+click</m> (mac) or <m>Ctrl+click</m> (win) on an element to delete it<br />
    // • <m>Cmd+click</m> (mac) or <m>Ctrl+click</m> (win) on the background to add a star<br />
    // • <m>Alt+Cmd+click</m> (mac) or <m>Alt+Ctrl+click</m> (win) on the background to add a planet<br />
    // • <m>Shift+click</m> on a star to add a note<br />
    // • <m>right click</m> or <m>two fingers tap</m>: open contextual menu<br />
	class_addmethod(c, (method) bodies_mousedown, "mousedown", A_CANT, 0);
	class_addmethod(c, (method) bodies_mousedrag, "mousedrag", A_CANT, 0);
	class_addmethod(c, (method) bodies_mouseup, "mouseup", A_CANT, 0);
    
    // @method (keyboard) @digest Undo/redo or play
    // @description
    // @copy DADA_DOC_KEYBOARDS_COMMANDS_STANDARD_NAVIGATION
    // • <m>Cmd+Z</m> (mac) or <m>Ctrl+Z</m> (win): perform undo step<br />
    // • <m>Cmd+Shift+Z</m> (mac) or <m>Ctrl+Y</m> (win): perform redo step<br />
    // • <m>Spacebar</m>: toggle play<br />
    // • <m>Tab</m>: autozoom<br />
	class_addmethod(c, (method) bodies_key, "key", A_CANT, 0);
    class_addmethod(c, (method) bodies_keyup, "keyup", A_CANT, 0);

    // @method (tools) @digest Navigate
    // @description
    // @copy DADA_DOC_TOOLS_INTRO
    // @copy DADA_DOC_TOOLS_ZX
    // @copy DADA_DOC_TOOLS_N
    // @copy DADA_DOC_TOOLS_SR
    // @copy DADA_DOC_TOOLS_Q
    class_addmethod(c, (method) bodies_mousemove, "mousemove", A_CANT, 0);
    class_addmethod(c, (method) bodies_mousewheel, "mousewheel", A_CANT, 0);
    class_addmethod(c, (method) bodies_mousedoubleclick, "mousedoubleclick", A_CANT, 0);
    

//	class_addmethod(c, (method) bodies_select, "select", A_GIMME, 0);
	class_addmethod(c, (method) bodies_set_state_from_gimme, "set", A_GIMME, 0);
	class_addmethod(c, (method) set_arrows_from_gimme, "setarrows", A_GIMME, 0);
	class_addmethod(c, (method) set_equally_spaced_arrows_from_gimme, "seteqspacedarrows", A_GIMME, 0);
    

    // @method clear @digest Clear
    // @description Deletes all bodies and particles
    class_addmethod(c, (method) bodies_clear, "clear", A_GIMME, 0);


    class_addmethod(c, (method) bodies_preset, "preset", 0);
//    class_addmethod(c, (method) bodies_begin_preset, "begin_preset", A_GIMME, 0);
//    class_addmethod(c, (method) bodies_restore_preset, "restore_preset", A_GIMME, 0);
//    class_addmethod(c, (method) bodies_end_preset, "end_preset", 0);
    
	class_addmethod(c, (method) bodies_assist, "assist", A_CANT, 0);
	class_addmethod(c, (method) bodies_notify, "bachnotify", A_CANT, 0);

    // @method play @digest Start sequencing
    // @description Starts the sequencing engine.
    class_addmethod(c, (method) bodies_play,	"play",		A_GIMME,	0);
    
    // @method stop @digest Stop sequencing
    // @description Stops the sequencing engine.
    class_addmethod(c, (method) bodies_stop,	"stop",		A_GIMME,	0);
    
    
    // @method clock @digest Select a clock source
    // @description The word <m>clock</m>, followed by the name of an existing <m>setclock</m> objects, sets the <o>dada.bounce</o>
    // object to be controlled by that <m>setclock</m> object rather than by Max's internal millisecond clock.
    // The word <m>clock</m> by itself sets the object back to using Max's regular millisecond clock.
	class_addmethod(c, (method) bodies_clock, "clock", A_DEFSYM, 0);
	class_addmethod(c, (method) bodies_jsave, "jsave", A_CANT, 0);
	
    // @method forceperiod @digest Force the period of a planet
    // @description The symbol <m>forceperiod</m> followed by an integer <m>N</m> and a floating point number <m>P</m>
    // forces the <m>N</m>-th planet to have circular motion of period <m>P</m> (in milliseconds) with respect to its nearest star.
    // Notice that this only applies to the ideal situation where that single star exists; if other stars come into play,
    // the motion will in generall not be circular, but rather will be affected by the other stars' presence.
    // Also, differently from <m>forcecircular</m> this message only works properly when the gravitational law is the default standard one,
    // and it doesn't work for a custom <m>law</m>.
    // @marg 0 @name planet_index @optional 0 @type int
    // @marg 1 @name period_ms @optional 0 @type float
    class_addmethod(c, (method) bodies_forceperiod, "forceperiod", A_GIMME);

    
    // @method forceperiod @digest Force a planet to have circular motion
    // @description The symbol <m>forcecircular</m> followed by an integer <m>N</m>
    // forces the <m>N</m>-th planet to have circular motion with respect to its nearest star.
    // Notice that this only applies to the ideal situation where that single star exists; if other starsst come into play,
    // the motion will in generall not be circular, but rather will be affected by the other stars' presence.
    // If an additional "zero" symbol is set as second argument, the position and velocity of the planet are "zeroed" by
    // putting the planet right above the star, with a rightward pointing horizontal velocity.
    // @marg 0 @name planet_index @optional 0 @type int
    // @marg 0 @name zero_position @optional 1 @type symbol
    class_addmethod(c, (method) bodies_forcecircular, "forcecircular", A_GIMME);


    // @method llll @digest Set state
    // @description Sets the current state of the object. The syntax must follow the one described in the
    // <m>dump</m> message documentation (although stars only or planets only can be assigned).
    class_addmethod(c, (method) bodies_anything, "bodies", A_GIMME, 0);

    // @method star @digest Change star
    // @description Modifies the state of one of the star. The <m>star</m> word must be followed by the
    // index of the star to be modified, and the new <m>STAR</m> llll, in the syntax explained in the
    // <m>dump</m> message.
    // Not all the specifications need to be assigned; the unassigned attributes will be kept as they are.
    // @marg 0 @name star_index @optional 0 @type int
    // @marg 1 @name star_syntax @optional 0 @type llll
    class_addmethod(c, (method) bodies_anything, "star", A_GIMME, 0);
    class_addmethod(c, (method) bodies_anything, "body", A_GIMME, 0);

    // @method planet @digest Change planet
    // @description Modifies the state of one of the planet. The <m>planet</m> word must be followed by the
    // index of the planet to be modified, and the new <m>PLANET</m> llll, in the syntax explained in the
    // <m>dump</m> message.
    // Not all the specifications need to be assigned; the unassigned attributes will be kept as they are.
    // @marg 0 @name planet_index @optional 0 @type int
    // @marg 1 @name planet_syntax @optional 0 @type llll
    class_addmethod(c, (method) bodies_anything, "planet", A_GIMME, 0);
    class_addmethod(c, (method) bodies_anything, "particle", A_GIMME, 0);
    
    
    // @method addstars @digest Add stars
    // @description Add stars to the universe. The <m>addstars</m> word must be followed by an llll in the form
    // <b><m>STAR1</m> <m>STAR2</m>...</b>, each in the syntax explained in the <m>dump</m> message.
    // @marg 0 @name bodies_llll @optional 0 @type llll
    class_addmethod(c, (method) bodies_anything, "addbodies", A_GIMME, 0);
    class_addmethod(c, (method) bodies_anything, "addstars", A_GIMME, 0);

    // @method addplanets @digest Add planets
    // @description Add test particles to the universe. The <m>addplanets</m> word must be followed by an llll in the form
    // <b><m>PLANET1</m> <m>PLANET2</m>...</b>, each in the syntax explained in the <m>dump</m> message.
    // @marg 0 @name particles_llll @optional 0 @type llll
    class_addmethod(c, (method) bodies_anything, "addparticles", A_GIMME, 0);
    class_addmethod(c, (method) bodies_anything, "addplanets", A_GIMME, 0);

    // @method deletestar @digest Delete a star
    // @description The word <m>deletestar</m> followed by an integer <m>N</m> deletes the <m>N</m>-th star from the world.
    // @marg 0 @name index @optional 0 @type int
    class_addmethod(c, (method) bodies_anything, "deletebody", A_GIMME, 0);
    class_addmethod(c, (method) bodies_anything, "deletepstar", A_GIMME, 0);

    // @method deleteplanet @digest Delete a planet
    // @description The word <m>deleteplanet</m> followed by an integer <m>N</m> deletes the <m>N</m>-th planet from the world.
    // @marg 0 @name index @optional 0 @type int
    class_addmethod(c, (method) bodies_anything, "deleteparticle", A_GIMME, 0);
    class_addmethod(c, (method) bodies_anything, "deleteplanet", A_GIMME, 0);

    class_addmethod(c, (method) bodies_anything, "anything", A_GIMME, 0);

    // @method dump @digest Output state
    // @description Outputs the current state of the object. The syntax is
    // <b>bodies (stars <m>STAR1</m> <m>STAR2</m>...) (planets <m>PLANET1</m> <m>PLANET2</m>...)</b>.
    // Each star is in the syntax
    // <b>(coord <m>x</m> <m>y</m>) (density <m>d</m>) (radius <m>r</m>) (notes <m>NOTE1</m> <m>NOTE2</m>...) (color <m>r</m> <m>g</m> <m>b</m> <m>a</m>)
    // (channel <m>MIDIchannel</m>) (flags <m>flags</m>)</b>, where each <m>NOTE</m> is in the syntax <b>(<m>angle</m> <m>MIDIcents</m>)</b>.<br />
    // Each particle is in the syntax
    // <b>(coord <m>x</m> <m>y</m>) (speed <m>x</m> <m>y</m>) (acc <m>x</m> <m>y</m>) (color <m>r</m> <m>g</m> <m>b</m> <m>a</m>)
    // (channel <m>MIDIchannel</m>) (flags <m>flags</m>)</b>. <br /> <br />
    // @copy DADA_DOC_SYNTAX_FLAGS
    class_addmethod(c, (method) bodies_anything, "dump", A_GIMME, 0);

    
    
    // @method autozoom @digest Set domain and range automatically
    // @description Adapts view and zoom automatically according to the current stars' and planets' positions.
    class_addmethod(c, (method) bodies_anything, "autozoom", A_GIMME, 0);

    
    // @method follow @digest Follow planets
    // @description Start following one or more planets. Following a single planet means that the particle will always be kept
    // in a "subjective view" at the center of the displayed region. If more than one planet is followed, their barycenter is kept
    // at the center of the displayed region, and the zoom is also adapted in case they end up being outside the displayed region.
    // Use <m>follow all</m> to follow all planets.
    // Use <m>follow</m> without any argument to stop following planets.
    // @marg 0 @name particles_indices @optional 1 @type list
    class_addmethod(c, (method) bodies_anything, "follow", A_GIMME, 0);

    // @method distribute @digest Evenly distribute star notes
    // @description The word <m>distribute</m>, followed by an integer <m>N</m>, distributes evenly the angles of the notes belonging to
    // the <m>N</m>-th star. Add a <m>mirror</m> symbol as second argument in order to also add mirrored notes in a forward-backward configuration.
    // @marg 0 @name body_index @optional 0 @type int
    // @marg 1 @name mirror @optional 1 @type symbol
    class_addmethod(c, (method) bodies_anything, "distribute", A_GIMME, 0);

    
    
    // @method restart @digest Restart
    // @description Sets the current time to 0.
    class_addmethod(c, (method) bodies_restart, "restart", 0);

    // @method settime @digest Set time
    // @description Sets the current time to a given value, in milliseconds.
    // @marg 0 @name time_ms @optional 0 @type float
    class_addmethod(c, (method) bodies_settime, "settime", A_FLOAT);
	
    
    // @method domain @digest Set the X domain
    // @description The <m>domain</m> message, followed by two numbers, sets minimum and maximum coordinates
    // to be displayed on the X axis.
    // The <m>domain</m> message,  followed by the "start" or "end" symbol and a number, sets the coordinate
    // to be displayed respectively at the left boundary or at the right boundary of the object box.
    // @marg 0 @name arguments @optional 0 @type list
    class_addmethod(c, (method)bodies_anything,		"domain",		A_GIMME,	0);
    
    // @method range @digest Set the Y range
    // @description The <m>range</m> message, followed by two numbers, sets minimum and maximum coordinates
    // to be displayed on the Y axis
    // The <m>range</m> message,  followed by the "start" or "end" symbol and a number, sets the coordinate
    // to be displayed respectively at the bottom boundary or at top right boundary of the object box.
    // @marg 0 @name arguments @optional 0 @type list
    class_addmethod(c, (method)bodies_anything,		"range",		A_GIMME,	0);
    
    
    // @method getdomain @digest Retrieve current X domain
    // @description The <m>getdomain</m> message outputs from the third outlet the minimum and maximum
    // coordinates displayed on the X axis, preceded by a <m>domain</m> symbol.
    class_addmethod(c, (method)bodies_anything,		"getdomain",		A_GIMME,	0);
    
    
    // @method getrange @digest Retrieve current Y range
    // @description The <m>getrange</m> message outputs from the third outlet the minimum and maximum
    // coordinates displayed on the Y axis, preceded by a <m>range</m> symbol.
    class_addmethod(c, (method)bodies_anything,		"getrange",		A_GIMME,	0);
    
    
    DADAOBJ_JBOX_DECLARE_READWRITE_METHODS(c);
    DADAOBJ_JBOX_DECLARE_ACCEPTSDRAG_METHODS(c);

	llllobj_class_add_out_attr(c, LLLL_OBJ_UI);
    dadaobj_class_init(c, LLLL_OBJ_UI, DADAOBJ_BBGIMAGE | DADAOBJ_ZOOM | DADAOBJ_CENTEROFFSET | DADAOBJ_GRID | DADAOBJ_AXES | DADAOBJ_LABELS | DADAOBJ_GRID_SHOWDEFAULT | DADAOBJ_SNAPTOGRID | DADAOBJ_MOUSEHOVER | DADAOBJ_UNDO | DADAOBJ_PLAY | DADAOBJ_NOTIFICATIONS | DADAOBJ_BORDER | DADAOBJ_BORDER_SHOWDEFAULT);

    // CHANGING defaults for some attributes
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"playstep",0,"10"); // we need it lower, since it's for sequencing purposes also!

    
	CLASS_ATTR_DEFAULT(c, "patching_rect", 0, "0 0 280 280");
	
	CLASS_STICKY_ATTR(c, "category", 0, "Appearance"); 

	CLASS_ATTR_CHAR(c,"showspeed",0, t_bodies, show_speed);
	CLASS_ATTR_STYLE_LABEL(c, "showspeed", 0, "enumindex", "Show Planet Speed");
    CLASS_ATTR_ENUMINDEX(c,"showspeed", 0, "Don't Arrow Arrow And Value");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showspeed",0,"1");
    // @description Toggles the ability to display the particle speed vector (and possibly its numeric component also).

	CLASS_ATTR_CHAR(c,"showacceleration",0, t_bodies, show_acceleration);
	CLASS_ATTR_STYLE_LABEL(c, "showacceleration", 0, "enumindex", "Show Planet Acceleration");
    CLASS_ATTR_ENUMINDEX(c,"showacceleration", 0, "Don't Arrow Arrow And Value");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showacceleration",0,"0");
    // @description Toggles the ability to display the particle acceleration vector (and possibly its numeric component also).
	
    CLASS_ATTR_CHAR(c,"showdensity",0, t_bodies, show_density);
    CLASS_ATTR_STYLE_LABEL(c, "showdensity", 0, "onoff", "Show Density Value");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showdensity",0,"0");
    // @description Toggles the ability to display the density of each body.

    CLASS_ATTR_CHAR(c,"shownotes",0, t_bodies, show_notes);
    CLASS_ATTR_STYLE_LABEL(c, "shownotes", 0, "enumindex", "Show Notes");
    CLASS_ATTR_ENUMINDEX(c,"shownotes", 0, "Don't Note Names Staff");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"shownotes",0,"2");
    // @description Toggles the ability to display pitches for each body: <br />
    // • Don't: don't show pitches; <br />
    // • Note Names: show pitches as note names; <br />
    // • Staff: show pitches on a staff (default). <br />

    CLASS_ATTR_CHAR(c,"showstarid",0, t_bodies, show_bodies_id);
	CLASS_ATTR_STYLE_LABEL(c, "showstarid", 0, "onoff", "Show Star ID");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showstarid",0,"0");
    // @description Toggles the ability to display the ID next to each star.

	CLASS_ATTR_CHAR(c,"showplanetid",0, t_bodies, show_particles_id);
	CLASS_ATTR_STYLE_LABEL(c, "showplanetid", 0, "onoff", "Show Planet ID");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showplanetid",0,"0");
    // @description Toggles the ability to display the ID next to each planet.
	
	CLASS_STICKY_ATTR_CLEAR(c, "category");
	
	
	CLASS_STICKY_ATTR(c, "category", 0, "Settings"); 

	CLASS_ATTR_DOUBLE(c,"g",0, t_bodies, G);
	CLASS_ATTR_LABEL(c,"g",0,"G constant");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"g",0,"6674");
    // @description Sets the value for the G constant

    CLASS_ATTR_CHAR(c,"indexaschannel",0, t_bodies, use_idx_as_channel);
    CLASS_ATTR_STYLE_LABEL(c,"indexaschannel",0,"onoff","Use Index As Channel");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"indexaschannel",0,"0");
    // @description If active, the output MIDI channel is NOT the ball or body midichannel, rather their index.

	CLASS_ATTR_LONG(c, "tonedivision", 0, t_bodies, tone_division);
	CLASS_ATTR_STYLE_LABEL(c,"tonedivision",0,"text","Microtonal Division");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"tonedivision",0,"2");
    // @description @copy BACH_DOC_TONEDIVISION

	CLASS_ATTR_CHAR(c,"approxmethod",0, t_bodies, approx_method);
	CLASS_ATTR_STYLE_LABEL(c,"approxmethod",0,"enumindex","Approximation Method");
	CLASS_ATTR_ENUMINDEX(c,"approxmethod", 0, "Euler Leapfrog RungeKutta4");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"approxmethod",0,"1");
    // @description Sets the integration algorithm (approximation method). The choice is between
    // Euler, Leapfrog and Runge-Kutta 4.
	
	CLASS_ATTR_CHAR(c,"hidewhileplaying",0, t_bodies, hide_while_running);
	CLASS_ATTR_STYLE_LABEL(c,"hidewhileplaying",0,"onoff","Hide While Playing");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"hidewhileplaying",0,"0");
    // @description Toggles the ability to prevent the object from painting and displaying bodies and particles during playback.
    // This can be useful if one needs to save CPU time.
	
	CLASS_ATTR_CHAR(c,"usemidichannels",0, t_bodies, use_particle_midichannels);
	CLASS_ATTR_STYLE_LABEL(c,"usemidichannels",0,"enumindex","Use MIDI Channels Of");
	CLASS_ATTR_ENUMINDEX(c,"usemidichannels", 0, "Stars Planets");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"usemidichannels",0,"0");
    // @descriptions Sets the midichannels that will be used at playtime: either the stars' ones (0, default) or the planets' ones (1).
	
	CLASS_ATTR_ATOM_VARSIZE(c,"law",0, t_bodies, law_av, law_ac, 100);
	CLASS_ATTR_STYLE_LABEL(c,"law",0,"text","Gravitational Law");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"law",0,"default");
	CLASS_ATTR_ACCESSORS(c, "law", (method)NULL, (method)bodies_setattr_law);
    // @descriptions Sets a custom gravitational law. Usable variables and parameters are: "G" (gravitational constant), "m" (body mass),
    // "r" (body radius), "d" (distance from body). The default newtonian law is equivalent to setting <m>law -G*m/(d*d)</m>.

	
	CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	
	CLASS_STICKY_ATTR(c, "category", 0, "Play"); 

/*	CLASS_ATTR_CHAR(c,"play",0, t_bodies, playback);
	CLASS_ATTR_STYLE_LABEL(c, "play", 0, "onoff", "Play");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"play",0,"1");
    // @exclude all
    // @description Toggles the ability to play back the sequenced notes from the playout.
*/
    
    CLASS_ATTR_CHAR(c,"hitdata",0, t_bodies, sendhitdata);
    CLASS_ATTR_STYLE_LABEL(c, "hitdata", 0, "onoff", "Output Hit Data");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"hitdata",0,"1");
    // @description Toggles the ability to also output hit data for every played note from third outlet.
    // The data includes indices of planets, stars, notes involved in the hit, along with the note midicents.
    
    CLASS_ATTR_CHAR(c,"highlightplay",0, t_bodies, highlight_play);
    CLASS_ATTR_STYLE_LABEL(c, "highlightplay", 0, "onoff", "Highlight Play");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"highlightplay",0,"1");
    // @description Toggles the ability to highlight the played notes.

/*	CLASS_ATTR_CHAR(c,"toroll",0, t_bodies, playtoroll);
	CLASS_ATTR_STYLE_LABEL(c, "toroll", 0, "onoff", "Play To Roll");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"toroll",0,"0");
    // @exclude all
    // @description Toggles the ability to play back the sequenced notes as commands for a <o>bach.roll</o> object connected to the second outlet.
*/
    
	CLASS_ATTR_DOUBLE(c,"zeroveldist",0, t_bodies, zero_velocity_distance);
	CLASS_ATTR_STYLE_LABEL(c, "zeroveldist", 0, "text", "Zero-Velocity Distance");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"zeroveldist",0,"500");
    // @s Sets the distance which will be associated to zero-velocity notes. Planets moving farther than this distance, with respect to a
    // given star, will not trigger any of the star's notes.

	CLASS_ATTR_DOUBLE(c,"maxveldist",0, t_bodies, max_velocity_distance);
	CLASS_ATTR_STYLE_LABEL(c, "maxveldist", 0, "text", "Maximum-Velocity Distance");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"maxveldist",0,"0");
    // @description Sets the distance which will be associated to a 127 velocity. Planets moving nearer than this distance, with respect to a
    // given star, will always trigger star's notes with maximum velocity

//	CLASS_ATTR_DOUBLE(c,"maxvelrad",0, t_bodies, max_velocity_radius);
//	CLASS_ATTR_STYLE_LABEL(c, "maxvelrad", 0, "text", "Maximum-Velocity Radius");
//	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"maxvelrad",0,"50");
    // @exclude dada.bodies
	
	CLASS_ATTR_DOUBLE(c,"velslope",0, t_bodies, velocity_slope);
	CLASS_ATTR_STYLE_LABEL(c, "velslope", 0, "text", "Velocity Mapping Slope");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"velslope",0,"0.");
    // @description Sets a slope (-1 to 1, 0 being linear) for the velocity mapping (from <m>zeroveldist</m> to <m>maxveldist</m>).
	
	CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	

	s_bodies_class = c;
	class_register(CLASS_BOX, s_bodies_class);

	post("dada.bodies compiled %s %s", __DATE__, __TIME__);
	return 0;
}

t_max_err bodies_setattr_law(t_bodies *x, void *attr, long ac, t_atom *av)
{
    if (x->n_lexpr)
		object_free_debug(x->n_lexpr);

    if (ac == 1 && av && atom_gettype(av) == A_SYM && (atom_getsym(av) == gensym("Newton") || atom_getsym(av) == gensym("newton"))) {
        x->law_ac = 1;
        atom_setsym(x->law_av, gensym("Newton"));
        x->law_type = DADA_BODIES_LAW_NEWTON;
        x->n_lexpr = NULL;
    } else if (ac == 1 && av && atom_gettype(av) == A_SYM && (atom_getsym(av) == gensym("Default") || atom_getsym(av) == gensym("default"))) {
        x->law_ac = 1;
        atom_setsym(x->law_av, gensym("default"));
        x->law_type = DADA_BODIES_LAW_NEWTON_OUTSIDE;
        x->n_lexpr = NULL;
    } else if (ac && av) {
		long i;
        
		x->law_ac = ac;
		for (i = 0; i < ac && i < 100; i++)
			x->law_av [i] = av[i];
		
		x->n_lexpr = lexpr_new(ac, av, lexpr_subs_count, lexpr_subs, (t_object *)x);
        x->law_type = DADA_BODIES_LAW_CUSTOM;
	} else {
		x->law_ac = 0;
        x->n_lexpr = NULL;
        x->law_type = DADA_BODIES_LAW_NONE;
	}
	return MAX_ERR_NONE;
}




void bodies_iar(t_bodies *x) // invalidate and redraw
{
    jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
    jbox_redraw((t_jbox *)x);
}

void changed_bang(t_bodies *x, long val){
	// TO DO: undo and send bang
}



long add_particle(t_bodies *x, t_pt position, t_pt speed, t_jrgba color, long midichannel){
	long idx = x->num_particles;
	if (idx < DADA_BODIES_MAX_PARTICLES) {
		x->particle[idx].r_it.coord = position;
		x->particle[idx].speed = speed;
		x->particle[idx].acc = build_pt(0, 0);
        x->particle[idx].r_it.color = color;
        x->particle[idx].midichannel = midichannel;
		x->num_particles = idx + 1;
		return idx;
	}
	return -1;
}

void delete_particle(t_bodies *x, long id){
    if (id >= 0 && id < DADA_BODIES_MAX_PARTICLES - 1 && id < x->num_particles) {
        x->num_particles --;
		sysmem_copyptr(&x->particle[id+1], &x->particle[id], (DADA_BODIES_MAX_PARTICLES - 1 - id) * sizeof(t_particle));
    }
}

long sort_by_first_fn(void *dummy, t_llllelem *a, t_llllelem *b) {
	if (hatom_gettype(&a->l_hatom) == H_LLLL && hatom_gettype(&b->l_hatom) == H_LLLL) {
		t_llll *llll1 = hatom_getllll(&a->l_hatom);
		t_llll *llll2 = hatom_getllll(&b->l_hatom);
        if (llll1 && llll2 && llll1->l_head && llll2->l_head) {
			if (llll_leq_hatom(&llll1->l_head->l_hatom, &llll2->l_head->l_hatom))
				return 1;
			else
				return 0;
        }
		
		return 1;
	}
	return 1;
}

t_llll *get_arithm_ser(long from, long to){
	long i;
	t_llll *out = llll_get();
	for (i = from; i <= to; i++)
		llll_appendlong(out, i, 0, WHITENULL_llll);
	return out;
}

long find_long_in_llll(t_llll *ll, long num){
	t_llllelem *elem;
	long count;
	for (count = 0, elem = ll->l_head; elem; count++, elem = elem->l_next){
		if (hatom_gettype(&elem->l_hatom) == H_LONG && hatom_getlong(&elem->l_hatom) == num)
			return count;
	}
	return -1;
}

t_llll *sort_arrownotes_as_llll(t_bodies *x, t_llll *arrownotes_as_llll, long *idx_to_track){
	//1. taking modulo of angle
	t_llllelem *elem;
	t_llll *ll;
	for (elem = arrownotes_as_llll->l_head; elem; elem = elem->l_next)
		if (hatom_gettype(&elem->l_hatom) == H_LLLL && (ll = hatom_getllll(&elem->l_hatom))->l_size >= 1)
			hatom_setdouble(&ll->l_head->l_hatom, fmod(hatom_getdouble(&ll->l_head->l_hatom) + TWOPI, TWOPI));
	

	//2. sorting by angle
	t_llll *cloned = llll_clone(arrownotes_as_llll);
	
//	llll_mergesort(cloned, &out, sort_by_first_fn, NULL);	// this is destructive on <cloned>

	
	t_llll **lists_to_order = (t_llll **) sysmem_newptr(2 * sizeof(t_llll *));
	lists_to_order[0] = cloned;
	lists_to_order[1] = get_arithm_ser(0, arrownotes_as_llll->l_size - 1);
	llll_multisort(lists_to_order, lists_to_order, 2, sort_by_first_fn);

	if (idx_to_track){
		*idx_to_track = find_long_in_llll(lists_to_order[1], *idx_to_track);
	}
	llll_free(lists_to_order[1]);
	cloned = lists_to_order[0];
	
	sysmem_freeptr(lists_to_order);
	
	return cloned;
}

t_llll* get_arrownotes_as_llll(t_bodies *x, long body_id){
	t_llll *out = llll_get(); 
	if (body_id > -1 && body_id < DADA_BODIES_MAX_BODIES){
		long i;
		for (i = 0; i < x->body[body_id].num_arrownotes; i++){
			t_llll *this_arrow = llll_get();
			llll_appenddouble(this_arrow, x->body[body_id].arrownote[i].angle, 0, WHITENULL_llll);
			llll_appenddouble(this_arrow, x->body[body_id].arrownote[i].midicents, 0, WHITENULL_llll);
			llll_appendllll(out, this_arrow, 0, WHITENULL_llll);
		}
	}	
	return out;
}

void transpose_body_arrows(t_bodies *x, long body_id, long mc_to_add){
	long j;
	for (j = 0; j < x->body[body_id].num_arrownotes; j++)
		x->body[body_id].arrownote[j].midicents += mc_to_add;
	compute_label_for_all_arrownotes(x, body_id);
	jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
}


void compute_label_for_arrownote(t_bodies *x, long body_id, long arrownote_id){
	if (body_id > -1 && body_id < DADA_BODIES_MAX_BODIES){
		char *notename = NULL;
		long screen_mc = 6000;
		double height, width;
		t_jfont *jf_notes = jfont_create("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, 11);
		t_rational screen_acc = long2rat(0);
		mc_to_screen_approximations_do(x->tone_division, k_ACC_AUTO, x->body[body_id].arrownote[arrownote_id].midicents, &screen_mc, &screen_acc, NULL, NULL);
		midicents2notename(5, screen_mc, screen_acc, k_NOTE_NAMES_ANGLOSAXON, true, &notename);
		jfont_text_measure(jf_notes, notename, &width, &height);
		t_pt textpt = get_topleft_angle_for_writing_around_the_clock(build_pt(x->body[body_id].r_it.coord.x, x->body[body_id].r_it.coord.y),
																	 x->body[body_id].radius + DADA_BODIES_ARROWNOTE_ADDITIONAL_RADIUS + 2, x->body[body_id].arrownote[arrownote_id].angle, width, height);
		
		snprintf(x->body[body_id].arrownote[arrownote_id].label_text, 9, "%s", notename);
		x->body[body_id].arrownote[arrownote_id].label_center.x = textpt.x + width/2.;
		x->body[body_id].arrownote[arrownote_id].label_center.y = textpt.y - height/2.;
		x->body[body_id].arrownote[arrownote_id].label_width = width;
		x->body[body_id].arrownote[arrownote_id].label_height = height;
		
		sysmem_freeptr(notename);
		jfont_destroy(jf_notes);
	}
}


void set_equally_spaced_arrownotes_to_body(t_bodies *x, long body_id, t_llll *notearrows_as_llll){
	if (body_id > -1 && body_id < DADA_BODIES_MAX_BODIES && notearrows_as_llll){
		long i, num_notes = notearrows_as_llll->l_size;
		t_llllelem *elem;
		x->body[body_id].num_arrownotes = 0;
		for (i = 0, elem = notearrows_as_llll->l_head; elem; elem = elem->l_next, i++){
			if (is_hatom_number(&elem->l_hatom)){
				x->body[body_id].arrownote[x->body[body_id].num_arrownotes].midicents = hatom_getdouble(&elem->l_hatom);
				x->body[body_id].arrownote[x->body[body_id].num_arrownotes].angle = TWOPI * ((double) i)/num_notes;
				compute_label_for_arrownote(x, body_id, x->body[body_id].num_arrownotes);
				x->body[body_id].num_arrownotes++;
			}
		}
	}	
}


void set_arrownotes_to_body(t_bodies *x, long body_id, t_llll *notearrows_as_llll, long *idx_to_track){
	t_llll *ll;
    if (notearrows_as_llll && notearrows_as_llll->l_head) {
        t_llll *sorted = sort_arrownotes_as_llll(x, notearrows_as_llll, idx_to_track);
        if (body_id > -1 && body_id < DADA_BODIES_MAX_BODIES && sorted){
            t_llllelem *elem;
            x->body[body_id].num_arrownotes = 0;
            for (elem = sorted->l_head; elem; elem = elem->l_next){
                if (hatom_gettype(&elem->l_hatom) == H_LLLL && (ll = hatom_getllll(&elem->l_hatom))->l_size >= 2){
                    x->body[body_id].arrownote[x->body[body_id].num_arrownotes].angle = hatom_getdouble(&ll->l_head->l_hatom);
                    x->body[body_id].arrownote[x->body[body_id].num_arrownotes].midicents = hatom_getdouble(&ll->l_head->l_next->l_hatom);
                    compute_label_for_arrownote(x, body_id, x->body[body_id].num_arrownotes);
                    x->body[body_id].num_arrownotes++;
                }
            }
        }	
        llll_free(sorted);
    } else
        x->body[body_id].num_arrownotes = 0;
}

void delete_arrownote(t_bodies *x, long body_id, long arrownote_id){
	if (body_id > -1 && body_id < DADA_BODIES_MAX_BODIES){
		if (arrownote_id < DADA_BODIES_MAX_ARROWNOTES - 1)
			sysmem_copyptr(&x->body[body_id].arrownote[arrownote_id+1], &x->body[body_id].arrownote[arrownote_id], (DADA_BODIES_MAX_ARROWNOTES - 1 - arrownote_id) * sizeof(t_arrownote));
		x->body[body_id].num_arrownotes--;
	}
	jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
}

long add_arrownote(t_bodies *x, long body_id, double angle, double midicents){
	long idx = -1;
	if (body_id > -1 && body_id < DADA_BODIES_MAX_BODIES){
		idx = x->body[body_id].num_arrownotes;
		x->body[body_id].arrownote[idx].angle = angle; 
		x->body[body_id].arrownote[idx].midicents = midicents; 
		x->body[body_id].num_arrownotes = idx + 1;
	}
	
	t_llll *ll = get_arrownotes_as_llll(x, body_id);
	set_arrownotes_to_body(x, body_id, ll, NULL);		///< inside we sort them
	llll_free(ll);

	jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
	
	return idx;
}

long add_body_from_llll(t_bodies *x, t_llll *body_as_llll){
    long idx = add_body(x, build_pt(0, 0), 0.01, 100, DADA_BLACK, 1);
    bodies_set_body_state(x, idx, body_as_llll);
	return idx;
}

long add_particle_from_llll(t_bodies *x, t_llll *particle_as_llll){
    long idx = add_particle(x, build_pt(0, 0), build_pt(0, 0), DADA_BLACK, 1);
    bodies_set_particle_state(x, idx, particle_as_llll);
    return idx;
}

long add_body(t_bodies *x, t_pt position, double density, double radius, t_jrgba color, long midichannel){
	long idx = x->num_bodies;
	if (idx < DADA_BODIES_MAX_BODIES) {
		x->body[idx].density = density;
		x->body[idx].r_it.coord = position;
		x->body[idx].radius = radius;
		x->body[idx].num_arrownotes = 0;
        x->body[idx].r_it.color = color;
        x->body[idx].midichannel = midichannel;
		x->num_bodies = idx + 1;

        update_mass_from_density_and_radius_for_body(x, idx);

        jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
		return idx;
    }
	return -1;
}

void delete_body(t_bodies *x, long id){
    if (id >= 0 && id < DADA_BODIES_MAX_BODIES - 1 && id < x->num_bodies) {
		sysmem_copyptr(&x->body[id+1], &x->body[id], (DADA_BODIES_MAX_BODIES - 1 - id) * sizeof(t_body));
        x->num_bodies --;
    }
	jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
}

long duplicate_body(t_bodies *x, long id){
    long new_id = add_body_from_llll(x, get_body_info_as_llll(x, id));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
    return new_id;
}

long duplicate_particle(t_bodies *x, long id){
    long new_id = add_particle_from_llll(x, get_particle_info_as_llll(x, id));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
    return new_id;
}



t_llll *get_body_info_as_llll(t_bodies *x, long body_idx){
	t_llll *this_body = llll_get();
    llll_appendllll(this_body, symbol_and_llll_to_llll_chained(gensym("coord"), pt_to_llll(x->body[body_idx].r_it.coord, 0)));
    llll_appendllll(this_body, symbol_and_double_to_llll(gensym("density"), x->body[body_idx].density));
    llll_appendllll(this_body, symbol_and_double_to_llll(gensym("radius"), x->body[body_idx].radius));
    llll_appendllll(this_body, symbol_and_llll_to_llll_chained(gensym("notes"), get_arrownotes_as_llll(x, body_idx)));
    llll_appendllll(this_body, symbol_and_llll_to_llll_chained(gensym("color"), color_to_llll(&x->body[body_idx].r_it.color)));
    llll_appendllll(this_body, symbol_and_long_to_llll(gensym("channel"), x->body[body_idx].midichannel));
    dadaitem_append_flags_to_llll(this_body, &x->body[body_idx].r_it, true);

	return this_body;
}


t_llll *get_particle_info_as_llll(t_bodies *x, long particle_idx){
	t_llll *this_particle = llll_get();
    llll_appendllll(this_particle, symbol_and_llll_to_llll_chained(gensym("coord"), pt_to_llll(x->particle[particle_idx].r_it.coord, 0)));
    llll_appendllll(this_particle, symbol_and_llll_to_llll_chained(gensym("speed"), pt_to_llll(x->particle[particle_idx].speed, 0)));
    llll_appendllll(this_particle, symbol_and_llll_to_llll_chained(gensym("acc"), pt_to_llll(x->particle[particle_idx].acc, 0)));
    llll_appendllll(this_particle, symbol_and_llll_to_llll_chained(gensym("color"), color_to_llll(&x->particle[particle_idx].r_it.color)));
    llll_appendllll(this_particle, symbol_and_long_to_llll(gensym("channel"), x->particle[particle_idx].midichannel));
    dadaitem_append_flags_to_llll(this_particle, &x->particle[particle_idx].r_it, true);

	return this_particle;
}

t_llll *get_curr_state(t_bodies *x, char get_bodies, char get_particles)
{
	t_llll *out = llll_get();
	long i;
	
    if (get_bodies) {
        t_llll *bodies = llll_get();
        for (i = 0; i < x->num_bodies; i++)
            llll_appendllll(bodies, get_body_info_as_llll(x, i), 0, WHITENULL_llll);
        llll_prependsym(bodies, gensym("stars"));
        llll_appendllll(out, bodies, 0, WHITENULL_llll);
    }

    if (get_particles) {
        t_llll *particles = llll_get();
        for (i = 0; i < x->num_particles; i++)
            llll_appendllll(particles, get_particle_info_as_llll(x, i), 0, WHITENULL_llll);
        llll_prependsym(particles, gensym("planets"));
        llll_appendllll(out, particles, 0, WHITENULL_llll);
    }
    
    llll_prependsym(out, gensym("bodies"), 0, WHITENULL_llll);
	return out;
}

t_llll *bodies_get_state(t_bodies *x)
{
    return get_curr_state(x, true, true);
}

void set_equally_spaced_arrows_from_gimme(t_bodies *x, t_symbol *s, long argc, t_atom *argv){
	long id;
	t_llll *params = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, s == _llllobj_sym_llllconnect ? s : NULL, argc, argv, LLLL_PARSE_CLONE);
	if (params && params->l_head && hatom_gettype(&params->l_head->l_hatom) == H_LONG && (id = hatom_getlong(&params->l_head->l_hatom) - 1) >= 0 && id < x->num_bodies) {
		llll_behead(params);
		if (params->l_head && hatom_gettype(&params->l_head->l_hatom) == H_LLLL) {
			set_equally_spaced_arrownotes_to_body(x, id, hatom_getllll(&params->l_head->l_hatom));
			changed_bang(x, 1);
			jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
			jbox_redraw((t_jbox *) x);
		}
	}
	llll_free(params);
}


void set_arrows_from_gimme(t_bodies *x, t_symbol *s, long argc, t_atom *argv){
	long id;
	t_llll *params = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, s == _llllobj_sym_llllconnect ? s : NULL, argc, argv, LLLL_PARSE_CLONE);
	if (params && params->l_head && hatom_gettype(&params->l_head->l_hatom) == H_LONG && (id = hatom_getlong(&params->l_head->l_hatom) - 1) >= 0 && id < x->num_bodies) {
		llll_behead(params);
		set_arrownotes_to_body(x, id, params, NULL);
		changed_bang(x, 1);
		jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
		jbox_redraw((t_jbox *) x);
	}
	llll_free(params);
}

void bodies_set_state_from_gimme(t_bodies *x, t_symbol *s, long argc, t_atom *argv){
	t_llll *params = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, s == _llllobj_sym_llllconnect ? s : NULL, argc, argv, LLLL_PARSE_CLONE);
	if (params) {
		bodies_set_state(x, params);
		jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
		jbox_redraw((t_jbox *) x);
	}
	llll_free(params);
}

void update_mass_from_density_and_radius_for_body(t_bodies *x, long i)
{
    // D = M/V ---> M = D*V
    x->body[i].mass = (4./3.)* PI * x->body[i].radius * x->body[i].radius * x->body[i].radius * x->body[i].density;
}

void update_mass_from_density_and_radius(t_bodies *x)
{
    long i;
    for (i = 0; i < x->num_bodies; i++)
        update_mass_from_density_and_radius_for_body(x, i);
}


void bodies_set_body_state(t_bodies *x, long idx, t_llll *this_body)
{
    if (idx < 0 || idx >= DADA_BODIES_MAX_BODIES) return;

    t_llllelem *subelem;
    for (subelem = this_body->l_head; subelem; subelem = subelem->l_next) {
        if (hatom_gettype(&subelem->l_hatom) == H_LLLL) {
            t_llll *spec = hatom_getllll(&subelem->l_hatom);
            if (spec && spec->l_head && hatom_gettype(&spec->l_head->l_hatom) == H_SYM) {
                t_symbol *router = hatom_getsym(&spec->l_head->l_hatom);
                
                if (router == gensym("coord") && spec->l_size >= 3) {
                    x->body[idx].r_it.coord.x = hatom_getdouble(&spec->l_head->l_next->l_hatom);
                    x->body[idx].r_it.coord.y = hatom_getdouble(&spec->l_head->l_next->l_next->l_hatom);
                } else if (router == gensym("density") && spec->l_size >= 2) {
                    x->body[idx].density = hatom_getdouble(&spec->l_head->l_next->l_hatom);
                } else if (router == gensym("radius") && spec->l_size >= 2) {
                    x->body[idx].radius = hatom_getdouble(&spec->l_head->l_next->l_hatom);
                } else if (router == gensym("notes")) {
                    t_llll *arrows = llll_clone(spec);
                    llll_behead(arrows);
                    x->body[idx].num_arrownotes = 0;
                    set_arrownotes_to_body(x, idx, arrows, NULL);
                    llll_free(arrows);
                } else if (router == gensym("color") && spec->l_size >= 4) {
                    x->body[idx].r_it.color.red = hatom_getdouble(&spec->l_head->l_next->l_hatom);
                    x->body[idx].r_it.color.green = hatom_getdouble(&spec->l_head->l_next->l_next->l_hatom);
                    x->body[idx].r_it.color.blue = hatom_getdouble(&spec->l_head->l_next->l_next->l_next->l_hatom);
                    if (spec->l_size >= 5)
                        x->body[idx].r_it.color.alpha = hatom_getdouble(&spec->l_head->l_next->l_next->l_next->l_next->l_hatom);
                    else
                        x->body[idx].r_it.color.alpha = 1.;
                } else if (router == gensym("channel") && spec->l_size >= 2) {
                    x->body[idx].midichannel = hatom_getlong(&spec->l_head->l_next->l_hatom);
                } else if (router == gensym("flags")) {
                    dadaitem_set_flags_from_llll(dadaobj_cast(x), spec, &x->body[idx].r_it, false);
                }
            }
        }
    }
    
    update_mass_from_density_and_radius_for_body(x, idx);
}



void bodies_set_particle_state(t_bodies *x, long idx, t_llll *this_particle)
{
    if (idx < 0 || idx >= DADA_BODIES_MAX_PARTICLES) return;

    t_llllelem *subelem;
    for (subelem = this_particle->l_head; subelem; subelem = subelem->l_next) {
        if (hatom_gettype(&subelem->l_hatom) == H_LLLL) {
            t_llll *spec = hatom_getllll(&subelem->l_hatom);
            if (spec && spec->l_head && hatom_gettype(&spec->l_head->l_hatom) == H_SYM) {
                t_symbol *router = hatom_getsym(&spec->l_head->l_hatom);
                
                if (router == gensym("coord") && spec->l_size >= 3) {
                    x->particle[idx].r_it.coord.x = hatom_getdouble(&spec->l_head->l_next->l_hatom);
                    x->particle[idx].r_it.coord.y = hatom_getdouble(&spec->l_head->l_next->l_next->l_hatom);
                } else if (router == gensym("speed") && spec->l_size >= 3) {
                    x->particle[idx].speed.x = hatom_getdouble(&spec->l_head->l_next->l_hatom);
                    x->particle[idx].speed.y = hatom_getdouble(&spec->l_head->l_next->l_next->l_hatom);
                } else if (router == gensym("acc") && spec->l_size >= 3) {
                    x->particle[idx].acc.x = hatom_getdouble(&spec->l_head->l_next->l_hatom);
                    x->particle[idx].acc.y = hatom_getdouble(&spec->l_head->l_next->l_next->l_hatom);
                } else if (router == gensym("color") && spec->l_size >= 4) {
                    x->particle[idx].r_it.color.red = hatom_getdouble(&spec->l_head->l_next->l_hatom);
                    x->particle[idx].r_it.color.green = hatom_getdouble(&spec->l_head->l_next->l_next->l_hatom);
                    x->particle[idx].r_it.color.blue = hatom_getdouble(&spec->l_head->l_next->l_next->l_next->l_hatom);
                    if (spec->l_size >= 5)
                        x->particle[idx].r_it.color.alpha = hatom_getdouble(&spec->l_head->l_next->l_next->l_next->l_next->l_hatom);
                    else
                        x->particle[idx].r_it.color.alpha = 1.;
                } else if (router == gensym("channel") && spec->l_size >= 2) {
                    x->particle[idx].midichannel = hatom_getlong(&spec->l_head->l_next->l_hatom);
                } else if (router == gensym("flags")) {
                    dadaitem_set_flags_from_llll(dadaobj_cast(x), spec, &x->particle[idx].r_it, false);
                }
            }
        }
    }
}


void bodies_add_bodies(t_bodies *x, t_llll *bodies)
{
    t_llllelem *subelem;
    for (subelem = bodies->l_head; subelem; subelem = subelem->l_next){
        if (hatom_gettype(&subelem->l_hatom) == H_LLLL && x->num_bodies < DADA_BODIES_MAX_BODIES){
            t_llll *this_body = hatom_getllll(&subelem->l_hatom);
            bodies_set_body_state(x, x->num_bodies, this_body);
            x->num_bodies++;
        }
    }
}

void bodies_add_particles(t_bodies *x, t_llll *particles)
{
    t_llllelem *subelem;
    for (subelem = particles->l_head; subelem; subelem = subelem->l_next){
        if (hatom_gettype(&subelem->l_hatom) == H_LLLL && x->num_particles < DADA_BODIES_MAX_PARTICLES){
            t_llll *this_particle = hatom_getllll(&subelem->l_hatom);
            bodies_set_particle_state(x, x->num_particles, this_particle);
            x->num_particles++;
        }
    }
}

void bodies_set_state(t_bodies *x, t_llll *status)
{
	t_llllelem *elem = status->l_head;

    if (elem && hatom_gettype(&elem->l_hatom) == H_SYM && hatom_getsym(&elem->l_hatom) == gensym("bodies"))
        elem = elem->l_next;

    while (elem && hatom_gettype(&elem->l_hatom) == H_LLLL && hatom_getllll(&elem->l_hatom)->l_head &&
           hatom_gettype(&hatom_getllll(&elem->l_hatom)->l_head->l_hatom) == H_SYM){
        t_symbol *router = hatom_getsym(&hatom_getllll(&elem->l_hatom)->l_head->l_hatom);
        
        if (router == gensym("bodies") || router == gensym("stars")) {
            // set bodies
            x->num_bodies = 0;
            t_llll *bodies = hatom_getllll(&elem->l_hatom);
            bodies_add_bodies(x, bodies);
        }  else if (router == gensym("particles") || router == gensym("planets")) {
            // set particles
            x->num_particles = 0;
            t_llll *particles = hatom_getllll(&elem->l_hatom);
            bodies_add_particles(x, particles);
        }
        
        elem = elem->l_next;
    }


    update_mass_from_density_and_radius(x);
    recompute_solo_flag(x);
    bodies_iar(x);
}


void bodies_preset(t_bodies *x){
	t_llll *status = get_curr_state(x, true, true);
	t_atom *av = NULL;
	long ac = llll_deparse(status, &av, 0, 0);
		 
	void *preset_buf;// Binbuf that stores the preset 
	short atomCount = (short)(ac + 3); // number of atoms we’re storing 
	t_atom atomArray[atomCount];// array of atoms to be stored 
	// 1. prepare the preset "header" information 
	atom_setobj(atomArray,x); 
	atom_setsym(atomArray+1,ob_sym(x)); 
	atom_setsym(atomArray+2,gensym("set")); 
	memcpy(atomArray+3, av, ac*sizeof(t_atom));
	// fill atomArray+3 with object’s state here and set atomCount 
	// 2. find the Binbuf 
	preset_buf = gensym("_preset")->s_thing; 
	// 3. store the data 
	if (preset_buf) { 
		binbuf_insert(preset_buf,NULL,atomCount,atomArray); 
	} 
	
	if (av) 
		sysmem_freeptr(av);
}

/*
void bodies_begin_preset(t_bodies *x, t_symbol *s, long argc, t_atom *argv)
{
    dadaobj_begin_preset(dadaobj_cast(x), s, argc, argv);
}


void bodies_restore_preset(t_bodies *x, t_symbol *s, long argc, t_atom *argv)
{
    dadaobj_restore_preset(dadaobj_cast(x), s, argc, argv);
}

void bodies_end_preset(t_bodies *x)
{
    dadaobj_end_preset(dadaobj_cast(x));
}

void bodies_preset(t_bodies *x)
{
    dadaobj_preset(dadaobj_cast(x));
}
 */




void bodies_assist(t_bodies *x, void *b, long m, long a, char *s)
{
    if (m == ASSIST_INLET) { // @in 0 @type llll @digest Messages or state
			sprintf(s,"llll: Messages or state");
	} else {
        char *type = NULL;
        llllobj_get_llll_outlet_type_as_string((t_object *) x, LLLL_OBJ_UI, a, &type);
        if (a == 0) // @out 0 @type llll @digest Dump outlet
            sprintf(s,"llll (%s): Dump Outlet", type);
		else if (a == 1) // @out 1 @type llll @digest Queries and Notifications
            sprintf(s,"llll (%s): Queries and Notifications", type);
        else if (a == 2) // @out 2 @type llll @digest Hit data
            sprintf(s,"llll (%s): Hit Data", type); // @description Sends the hit data (planet, body, note) for any played note, if <m>hitdata</m> attribute is on.
		else if (a == 3)  // @out 3 @type llll @digest Playout
			sprintf(s,"llll (%s): Playout", type); // @description Outlet dedicated to send out playout data
		else // @out 4 @type bang @digest bang when something is changed via the interface
			sprintf(s,"bang when changed");
	}
}

void bodies_initialize_popup_menus(t_bodies *x){
	// create font
	x->popup_main_font = jfont_create("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, 12);
	x->popup_secondary_font = jfont_create("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, 12);
	x->popup_body = NULL;
	x->popup_body_midichannels = NULL;
	x->popup_body_transpose = NULL;
	x->popup_particle_midichannels = NULL;
	x->popup_particle_forceperiod = NULL;
	x->popup_particle = NULL;
	x->popup_background = NULL;
}



t_bodies* bodies_new(t_symbol *s, long argc, t_atom *argv)
{
	t_bodies* x = NULL;
	t_max_err err = MAX_ERR_GENERIC;
	t_dictionary *d;
	long flags;
	
	if (!(d=object_dictionaryarg(argc,argv)))
		return NULL;

	x = (t_bodies*) object_alloc(s_bodies_class);
	flags = 0 
			| JBOX_DRAWFIRSTIN 
			| JBOX_NODRAWBOX
			| JBOX_DRAWINLAST
			| JBOX_TRANSPARENT	
	//		| JBOX_NOGROW
	//		| JBOX_GROWY
			| JBOX_GROWBOTH
			| JBOX_HILITE
	//		| JBOX_BACKGROUND
	//		| JBOX_TEXTFIELD
			| JBOX_DRAWBACKGROUND
//			| JBOX_DEFAULTNAMES
//			| JBOX_MOUSEDRAGDELTA 
			;

	jbox_new((t_jbox *)x, flags, argc, argv);
	x->b_ob.r_ob.l_box.b_firstin = (t_object*) x;

    dadaobj_jbox_setup((t_dadaobj_jbox *)x, DADAOBJ_BBGIMAGE | DADAOBJ_GRID | DADAOBJ_AXES | DADAOBJ_ZOOM | DADAOBJ_CENTEROFFSET | DADAOBJ_UNDO | DADAOBJ_CHANGEDBANG | DADAOBJ_NOTIFICATIONS, build_pt(1., 1.), 3, 4, 1, (invalidate_and_redraw_fn)bodies_iar, "qnsr", 2, "b4444");
    dadaobj_addfunctions(dadaobj_cast(x), (dada_mousemove_fn)bodies_mousemove, (method)bodies_task,
                         (method)bodies_postprocess_undo, (get_state_fn)bodies_get_state, (set_state_fn)bodies_set_state,
                         NULL, NULL, NULL);

    x->playback = true;
    
    x->body = (t_body *)bach_newptrclear(DADA_BODIES_MAX_BODIES * sizeof(t_body));
    x->particle = (t_particle *)bach_newptrclear(DADA_BODIES_MAX_BODIES * sizeof(t_particle));
   
    x->law_type = DADA_BODIES_LAW_NEWTON_OUTSIDE; // default
	x->b_ob.d_ob.m_play.play_step_ms = 1;
	x->G = 6674; // .0000000000667384; // REAL g
	x->num_bodies = x->num_particles = 0;
	x->time = 0;
	x->n_lexpr = NULL;
	x->there_are_solo_bodies = x->there_are_solo_particles = x->there_are_solitary_bodies = false;
	
    object_obex_lookup(x, gensym("#P"), &(x->patcher_parent));

	t_atom *av =  NULL;
	long ac = 0;
	atom_setparse(&ac, &av, "sqrt($f1 * $f2)");
	x->n_lexpr2 = lexpr_new(ac, av, 0, NULL, (t_object *)x);
	if (av)
		sysmem_freeptr(av);
	
	
	x->proxy = proxy_new((t_object *) x, 1,&x->n_in);
	x->running = false;
	
	long i;
	for (i = 0; i < DADA_BODIES_MAX_BODIES; i++) {
		x->last_played_note[i] = -1;
        x->last_played_arrow[i] = -1;
	}
    
	attr_dictionary_process(x, d);

    x->num_bodies = 0;
    add_body(x, build_pt(0, 0), 0.01, 20, long_to_color(0), 1);
    t_llll *notearrows = llll_from_text_buf("7700 8200 8500 8850 8500 8850 8500 8200", false);
    set_equally_spaced_arrownotes_to_body(x, 0, notearrows);
    llll_free(notearrows);
    
    x->num_particles = 0;
    add_particle(x, build_pt(0, 60), build_pt(75, 0), long_to_color(1), 1);
    
    force_circular_motion_for_particle(x, 0, true);
    
    jbox_ready((t_jbox *)x);


    x->b_ob.d_ob.m_play.setclock = gensym("");

	if (x) {
		t_llll *llll_for_rebuild = llll_retrieve_from_dictionary(d, "whole_bodies_data");
		if (llll_for_rebuild) { // new method
			bodies_set_state(x, llll_for_rebuild);
			llll_free(llll_for_rebuild);
		}

		bodies_initialize_popup_menus(x);
		
        dadaobj_set_current_version_number(dadaobj_cast(x));
        
		return x;
	}

	object_free_debug(x);
	return NULL;
}


void bodies_postprocess_undo(t_bodies *x)
{
    jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
    jbox_redraw((t_jbox *)x);
}


void bodies_anything(t_bodies *x, t_symbol *s, long argc, t_atom *argv){
    
	long inlet = proxy_getinlet((t_object *) x);
	
	 if (inlet == 0) {
         t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, s, argc, argv, LLLL_PARSE_CLONE);
         if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
             t_symbol *router = hatom_getsym(&parsed->l_head->l_hatom);
             llll_behead(parsed);

             
             if (dadaobj_anything_handle_domain_or_range(dadaobj_cast(x), router, parsed)) {
                 // nothing to do!
             } else if (router == gensym("follow")) {
                 x->follow_particle = 0;
                 t_llllelem *elem;
                 for (elem = parsed->l_head; elem; elem = elem->l_next) {
                     if (hatom_gettype(&elem->l_hatom) == H_LONG){
                         long l = hatom_getlong(&elem->l_hatom);
                         if (l > 0 && l < DADA_BODIES_MAX_PARTICLES)
                             x->follow_particle |= (1 << (l - 1));
                     } else if (hatom_gettype(&elem->l_hatom) == H_SYM && hatom_getsym(&elem->l_hatom) == _sym_all) {
                         x->follow_particle = (t_uint64)-1;
                    }
                 }
             } else if (router == gensym("autozoom")) {
                 dadaobj_cast(x)->m_zoom.must_autozoom = true;
                 bodies_iar(x);
             } else if (router == gensym("distribute")) {
                 if (parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_LONG) {
                     long l = hatom_getlong(&parsed->l_head->l_hatom) - 1;
                     if (l >= 0 && l < x->num_bodies) {
                         bodies_undo_step_push(x, gensym("Uniformly Distribute Star Notes"));
                         uniformly_distribute_arrownotes(x, l, parsed->l_head->l_next && hatom_gettype(&parsed->l_head->l_next->l_hatom) == H_SYM && hatom_getsym(&parsed->l_head->l_next->l_hatom) == gensym("mirror"));
                         jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
                     }
                 }
                 
             } else if ((router == gensym("deletebody") || router == gensym("deletestar")) && parsed->l_head && is_hatom_number(&parsed->l_head->l_hatom)) {
                 bodies_undo_step_push(x, gensym("Delete Star"));
                 delete_body(x, hatom_getlong(&parsed->l_head->l_hatom) - 1);
                 bodies_iar(x);
             } else if ((router == gensym("deleteparticle") || router == gensym("deleteplanet")) && parsed->l_head && is_hatom_number(&parsed->l_head->l_hatom)) {
                 bodies_undo_step_push(x, gensym("Delete Planet"));
                 delete_particle(x, hatom_getlong(&parsed->l_head->l_hatom) - 1);
                 bodies_iar(x);
             } else if ((router == gensym("body") || router == gensym("star")) && parsed->l_head && is_hatom_number(&parsed->l_head->l_hatom)) {
                 bodies_undo_step_push(x, gensym("Change Star"));
                 bodies_set_body_state(x, hatom_getlong(&parsed->l_head->l_hatom) - 1, parsed);
                 recompute_solo_flag(x);
                 bodies_iar(x);
             } else if ((router == gensym("particle") || router == gensym("planet")) && parsed->l_head && is_hatom_number(&parsed->l_head->l_hatom)) {
                 bodies_undo_step_push(x, gensym("Change Planet"));
                 bodies_set_particle_state(x, hatom_getlong(&parsed->l_head->l_hatom) - 1, parsed);
                 recompute_solo_flag(x);
                 bodies_iar(x);
             } else if (router == gensym("addbodies") || router == gensym("addstars")) {
                 bodies_undo_step_push(x, gensym("Add Stars"));
                 bodies_add_bodies(x, parsed);
                 bodies_iar(x);
             } else if (router == gensym("addparticles") || router == gensym("addplanets")) {
                 bodies_undo_step_push(x, gensym("Add Planets"));
                 bodies_add_particles(x, parsed);
                 bodies_iar(x);
             } else if (router == gensym("bodies")) {
                 bodies_undo_step_push(x, gensym("Set State"));
                 bodies_set_state(x, parsed);
                 bodies_iar(x);
             } else if (router == _sym_dump) {
                 bodies_dump(x, parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("bodies")) || is_symbol_in_llll_first_level(parsed, gensym("stars")),
                                parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("particles")) || is_symbol_in_llll_first_level(parsed, gensym("planets")));
             
             }
         } else if (parsed) {
             bodies_undo_step_push(x, gensym("Set State"));
             bodies_set_state(x, parsed);
             bodies_iar(x);
         }
         llll_free(parsed);
     }
}

void bodies_clock(t_bodies *x, t_symbol *s)
{
	void *old = x->b_ob.d_ob.m_play.setclock->s_thing;
	void *c = 0; 
	
	// the line below can be restated as: 
	// if s is the empty symbol 
	// or s->s_thing is zero 
	// or s->s_thing is non-zero and a setclock object  
	if (s && (s == gensym("") || ((c = s->s_thing) && zgetfn((t_object *)c, gensym("unset"))))) { 
		if (old) 
            bodies_stop(x, NULL, 0, NULL); 
		x->b_ob.d_ob.m_play.setclock = s;
		/*		if (x->m_running) 
		 setclock_delay(c, x->r_clock, 0L); */
	} 
}

void bodies_play(t_bodies *x, t_symbol *s, long argc, t_atom *argv)
{
    if (x->b_ob.d_ob.m_undo.undo_before_play)
        bodies_undo_step_push(x, gensym("Play"));
    
    x->running = true;
    x->cycle_num = 0;
    setclock_fdelay(x->b_ob.d_ob.m_play.setclock->s_thing, x->b_ob.d_ob.m_play.m_clock, x->b_ob.d_ob.m_play.play_step_ms);
    //		setclock_getftime(x->setclock->s_thing, &x->start_play_time);
    jbox_redraw((t_jbox *)x);
    dadaobj_send_notification_sym(dadaobj_cast(x), _llllobj_sym_play);
}

void bodies_stop(t_bodies *x, t_symbol *s, long argc, t_atom *argv)
{
	x->running = false;
	setclock_unset(x->b_ob.d_ob.m_play.setclock->s_thing, x->b_ob.d_ob.m_play.m_clock);
    long i;
    for (i = 0; i < x->num_bodies; i++)
        x->last_played_arrow[i] = -1;
    for (i = 0; i < DADA_BODIES_MAX_BODIES; i++)
        send_noteoff(x, i);
    jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
	jbox_redraw((t_jbox *) x);
    dadaobj_send_notification_sym(dadaobj_cast(x), _llllobj_sym_stop);
}

double pt_dist(t_pt pt1, t_pt pt2){
	double deltax = pt1.x - pt2.x;
	double deltay = pt1.y - pt2.y;
	return sqrt(deltax * deltax + deltay * deltay);
}

double pt_length(t_pt pt){
	return sqrt(pt.x * pt.x + pt.y * pt.y);
}

t_pt4 pt_pt_sum4(t_pt4 pt1, t_pt4 pt2){
	t_pt4 out;
	out.x = pt1.x + pt2.x;
	out.y = pt1.y + pt2.y;
	out.z = pt1.z + pt2.z;
	out.w = pt1.w + pt2.w;
	return out;
}

t_pt4 pt_double_prod4(t_pt4 pt, double num){
	t_pt4 out;
	out.x = pt.x * num;
	out.y = pt.y * num;
	out.z = pt.z * num;
	out.w = pt.w * num;
	return out;
}


t_llll *three_longs_to_llll(long l1, long l2, long l3){
	t_llll *out = llll_get();
	llll_appendlong(out, l1, 0, WHITENULL_llll);
	llll_appendlong(out, l2, 0, WHITENULL_llll);
	llll_appendlong(out, l3, 0, WHITENULL_llll);
	return out;
}


void send_noteoff(t_bodies *x, long idx){
	if (x->last_played_note[idx] > 0) {
        
		if (x->playback) {
            t_llll *outr = three_longs_to_llll(x->last_played_note[idx], 0, x->use_particle_midichannels == 0 ? (x->use_idx_as_channel ? idx + 1 : x->body[idx].midichannel) : (x->use_idx_as_channel ? idx + 1 : x->particle[idx].midichannel));
			llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 3, outr);
			llll_free(outr);
		}
        
/*		if (x->playtoroll) {
			t_llll *outl = llll_get();
			llll_appendsym(outl, _llllobj_sym_unsel, 0, WHITENULL_llll);
			llll_appendllll(outl, llll_get(), 0, WHITENULL_llll);
			llll_appendllll(outl, llll_get(), 0, WHITENULL_llll);
			llll_appendllll(outl, llll_get(), 0, WHITENULL_llll);
			llll_appendllll(outl, llll_get(), 0, WHITENULL_llll);
			llll_appendlong(outl, idx + 1, 0, WHITENULL_llll);
			llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, outl);
			llll_free(outl);
		} */
	}
}

void play_arrownote(t_bodies *x, long body_idx, long arrow_idx, long velocity, long particle_idx)
{
	double mc = x->body[body_idx].arrownote[arrow_idx].midicents;

	send_noteoff(x, x->use_particle_midichannels == 0 ? body_idx : particle_idx);
	
    if (x->last_played_arrow[body_idx] != arrow_idx) {
        x->last_played_arrow[body_idx] = arrow_idx;
        if (x->highlight_play) {
            t_object *view;
            for (view = jpatcher_get_firstview(x->patcher_parent); view; view = patcherview_get_nextview(view))
                jbox_invalidate_layer((t_object *)x, view, gensym("room"));
            jbox_redraw((t_jbox *)x);
        }
    }

	if (x->playback) {
		// right:
        t_llll *outr = llll_get();
        llll_appenddouble(outr, mc);
        llll_appendlong(outr, velocity);
        llll_appendlong(outr, x->use_particle_midichannels == 0 ? (x->use_idx_as_channel ? body_idx + 1 : x->body[body_idx].midichannel) : (x->use_idx_as_channel ? particle_idx + 1 : x->particle[particle_idx].midichannel));
		llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 3, outr);
		x->last_played_note[x->use_particle_midichannels == 0 ? body_idx : particle_idx] = mc;
		llll_free(outr);
	}
    
    if (x->sendhitdata) {
        t_llll *hitinfo = llll_get();
        llll_appendllll(hitinfo, symbol_and_long_to_llll(gensym("planet"), particle_idx + 1));
        llll_appendllll(hitinfo, symbol_and_long_to_llll(gensym("star"), body_idx + 1));
        llll_appendllll(hitinfo, symbol_and_long_to_llll(gensym("noteidx"), arrow_idx + 1));
        llll_appendllll(hitinfo, symbol_and_double_to_llll(gensym("cents"), mc));
        llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 2, hitinfo);
        llll_free(hitinfo);
    }
	
/*	if (x->playtoroll) {
		// left
		t_llll *out = llll_get();
		t_llll *chord = llll_get();
		t_llll *note = llll_get();
		llll_appendsym(out, _llllobj_sym_addchord, 0, WHITENULL_llll);
		llll_appendlong(out, x->use_particle_midichannels == 0 ? body_idx + 1 : particle_idx + 1, 0, WHITENULL_llll);
		llll_appendlong(chord, x->time, 0, WHITENULL_llll);
		llll_appendlong(note, mc, 0, WHITENULL_llll);
		llll_appendlong(note, x->b_ob.d_ob.m_play.play_step_ms, 0, WHITENULL_llll);
		llll_appendlong(note, velocity, 0, WHITENULL_llll);
		llll_appendllll(chord, note, 0, WHITENULL_llll);
		llll_appendllll(out, chord, 0, WHITENULL_llll);
		llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, out);
		llll_free(out);
		
		t_llll *sel = llll_get();
		llll_appendsym(sel, _llllobj_sym_sel, 0, WHITENULL_llll);
		llll_appenddouble(sel, x->time, 0, WHITENULL_llll);
		llll_appenddouble(sel, x->time, 0, WHITENULL_llll);
		llll_appendlong(sel, mc, 0, WHITENULL_llll);
		llll_appendlong(sel, mc, 0, WHITENULL_llll);
		llll_appendlong(sel, x->use_particle_midichannels == 0 ? body_idx + 1 : particle_idx + 1, 0, WHITENULL_llll);
		llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, sel);
		llll_free(sel);

		t_llll *inscreenpos = llll_get();
		llll_appendsym(inscreenpos, gensym("inscreenpos"), 0, WHITENULL_llll);
		llll_appenddouble(inscreenpos, 0.7, 0, WHITENULL_llll);
		llll_appenddouble(inscreenpos, x->time, 0, WHITENULL_llll);
		llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, inscreenpos);
		llll_free(inscreenpos);
	} */
}

void fill_body_dist(t_bodies *x, t_pt pt, double *dist)
{
    long j;
    for (j = 0; j < x->num_bodies; j++) {
        t_pt r = pt_pt_diff(pt, x->body[j].r_it.coord);
        double this_dist = pt_length(r);
        dist[j] = this_dist;
    }
}

// at point pt
t_pt get_acceleration(t_bodies *x, t_pt pt, double *dist){
	t_pt acc = build_pt(0, 0);
	long j;
	for (j = 0; j < x->num_bodies; j++){
		
		if ((x->body[j].r_it.flags & D_INACTIVE) || (x->there_are_solitary_bodies && !(x->body[j].r_it.flags & D_SOLITARY))) {
			if (dist)
				dist[j] = pt_length(pt_pt_diff(pt, x->body[j].r_it.coord));
			continue;
		}

		t_pt r = pt_pt_diff(pt, x->body[j].r_it.coord);
		double this_dist = pt_length(r);
		if (dist)
			dist[j] = this_dist; 
		
		double fact = 1;
		if (x->law_type == DADA_BODIES_LAW_NEWTON)
			fact = - x->G * x->body[j].mass / (this_dist * this_dist);	// -GM/r^2  * (vec(r)/r) = -GM/r^2 * vers(r)
        else if (x->law_type == DADA_BODIES_LAW_NEWTON_OUTSIDE)
            fact = (this_dist > x->body[j].radius ? -x->G * x->body[j].mass / (this_dist * this_dist) : 0);	 // newton but only outside the radius
        else if (x->law_type == DADA_BODIES_LAW_NONE)
            fact = 0;
		else if (x->n_lexpr){
			// custom law
			t_hatom vars[LEXPR_MAX_VARS];
			t_hatom *res;
			hatom_setdouble(vars, x->G); 
			hatom_setdouble(vars+1, x->body[j].mass); 
			hatom_setdouble(vars+2, this_dist);
			hatom_setdouble(vars+3, x->body[j].radius);
			res = lexpr_eval(x->n_lexpr, vars);
			fact = hatom_getdouble(res);
			sysmem_freeptr(res);
		}
		fact /= this_dist;	// we divide by the distance, since we'll multiply by the vector r just after this line (so we get the unitary vector)
		acc = pt_pt_sum(acc, pt_number_prod(r, fact));
	}
	return acc;
}

t_pt4 rk_f(t_bodies *x, t_pt4 pt, double *dist){
	t_pt4 res;
	t_pt temp;
	res.x = pt.z;
	res.y = pt.w;
	temp = get_acceleration(x, build_pt(pt.x, pt.y), dist);
	res.z = temp.x;
	res.w = temp.y; 
	return res;
}

void bodies_autozoom(t_bodies *x, t_object *view, t_rect *rect)
{
    systhread_mutex_lock(x->b_ob.d_ob.l_mutex);
    
    double rect_width = rect->width;
    double rect_height = rect->height;
    t_pt min = x->particle[0].r_it.coord;
    t_pt max = min;
    long i;
    for (i = 0; i < x->num_particles; i++) {
        t_pt this_coord = x->particle[i].r_it.coord;
        if (this_coord.x < min.x) min.x = this_coord.x;
        if (this_coord.y < min.y) min.y = this_coord.y;
        if (this_coord.x > max.x) max.x = this_coord.x;
        if (this_coord.y > max.y) max.y = this_coord.y;
    }

    for (i = 0; i < x->num_bodies; i++) {
        t_pt this_coord = x->body[i].r_it.coord;
        if (this_coord.x - x->body[i].radius < min.x) min.x = this_coord.x - x->body[i].radius;
        if (this_coord.y - x->body[i].radius < min.y) min.y = this_coord.y - x->body[i].radius;
        if (this_coord.x + x->body[i].radius > max.x) max.x = this_coord.x + x->body[i].radius;
        if (this_coord.y + x->body[i].radius > max.y) max.y = this_coord.y + x->body[i].radius;
    }
    systhread_mutex_unlock(x->b_ob.d_ob.l_mutex);

    
    if (max.x == min.x) {
        max.x -= 0.5;
        min.x += 0.5;
    }
    if (max.y == min.y) {
        max.y -= 0.5;
        min.y += 0.5;
    }
    
    // adding pads
    max.x += (max.x - min.x) * 0.2;
    min.x -= (max.x - min.x) * 0.2;
    max.y += (max.y - min.y) * 0.2;
    min.y -= (max.y - min.y) * 0.2;
    
    // equalizing zooms
    double zoom_x = (max.x - min.x)/rect_width;
    double zoom_y = (max.y - min.y)/rect_height;

    if (zoom_y < zoom_x) {
        double diff = (zoom_x - zoom_y) * rect_height;
        max.y += diff/2.;
        min.y -= diff/2.;
    } else if (zoom_x < zoom_y) {
        double diff = (zoom_y - zoom_x) * rect_width;
        max.x += diff/2.;
        min.x -= diff/2.;
    }

    dadaobj_setdomain(dadaobj_cast(x), view, min.x, max.x);
    dadaobj_setrange(dadaobj_cast(x), view, min.y, max.y);
}

void bodies_follow(t_bodies *x, t_object *view, t_rect *rect)
{
    if (x->num_particles == 0)
        return;
    
    double rect_width = rect->width;
    double rect_height = rect->height;
    
    systhread_mutex_lock(x->b_ob.d_ob.l_mutex);
    t_pt min = x->particle[0].r_it.coord;
    t_pt max = min;

    long i, count = 0;
    t_pt global = build_pt(0, 0);
    for (i = 0; i < 63 && i < x->num_particles; i++) {
        if (x->follow_particle & (1 << i)) {
            t_pt this_coord = x->particle[i].r_it.coord;
            global = pt_pt_sum(global, this_coord);
            if (this_coord.x < min.x) min.x = this_coord.x;
            if (this_coord.y < min.y) min.y = this_coord.y;
            if (this_coord.x > max.x) max.x = this_coord.x;
            if (this_coord.y > max.y) max.y = this_coord.y;
            count++;
        }
    }
    systhread_mutex_unlock(x->b_ob.d_ob.l_mutex);

    if (count > 0) {
        global = pt_number_prod(global, -1./count);
        
        if (count > 1) {
            t_pt screen_min, screen_max;
            dadaobj_getdomain(dadaobj_cast(x), view, &screen_min.x, &screen_max.x);
            dadaobj_getrange(dadaobj_cast(x), view, &screen_min.x, &screen_max.x);
            
            
            if (max.x == min.x) {
                max.x -= 0.5;
                min.x += 0.5;
            }
            if (max.y == min.y) {
                max.y -= 0.5;
                min.y += 0.5;
            }
            
            // adding pads
            max.x += (max.x - min.x) * 0.2;
            min.x -= (max.x - min.x) * 0.2;
            max.y += (max.y - min.y) * 0.2;
            min.y -= (max.y - min.y) * 0.2;

            
            double xzoom_perc = (rect_width/(max.x - min.x)) * 100. / x->b_ob.d_ob.m_zoom.zoom_static_additional.x;
            double yzoom_perc = (rect_height/(max.y - min.y)) * 100. / x->b_ob.d_ob.m_zoom.zoom_static_additional.y;
            double zoom_perc = MIN(xzoom_perc, yzoom_perc);
            if (zoom_perc < x->b_ob.d_ob.m_zoom.zoom_perc)
                dadaobj_setzoom(dadaobj_cast(x), build_pt(zoom_perc, zoom_perc));
        }

        dadaobj_setcenteroffset(dadaobj_cast(x), global);

        bodies_iar(x);
    }
    

}


void bodies_task(t_bodies *x){ 
	double h = x->b_ob.d_ob.m_play.play_step_ms/1000.; // time in seconds
	long i, j, k;
    long num_bodies = x->num_bodies;
    
	x->cycle_num++;
	x->time += x->b_ob.d_ob.m_play.play_step_ms;
	
/*	if (x->playtoroll) {
		//tail message
		t_llll *tail = llll_get();
		llll_appendsym(tail, _llllobj_sym_tail, 0, WHITENULL_llll);
		llll_appenddouble(tail, x->time, 0, WHITENULL_llll);
		llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, tail);
		llll_free(tail);

		t_llll *inscreenpos = llll_get();
		llll_appendsym(inscreenpos, gensym("inscreenpos"), 0, WHITENULL_llll);
		llll_appenddouble(inscreenpos, 0.7, 0, WHITENULL_llll);
		llll_appenddouble(inscreenpos, x->time, 0, WHITENULL_llll);
		llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, inscreenpos);
		llll_free(inscreenpos);
	} */

    dadaobj_mutex_lock(dadaobj_cast(x));
    
    char no_playing_arrows[DADA_BODIES_MAX_BODIES];
    for (i = 0; i < x->num_bodies; i++)
        no_playing_arrows[i] = true;
    
    t_llll *ll_to_play = llll_get();

    for (i = 0; i < x->num_particles; i++){
		if ((x->particle[i].r_it.flags & D_MUTE) || (x->there_are_solo_particles && !(x->particle[i].r_it.flags & D_SOLO)))
			continue;
		
		t_particle *prt = &x->particle[i];
		t_pt prev_coord = prt->r_it.coord;
		double dist[DADA_BODIES_MAX_BODIES];
		
		// now we gotta solve the equation
		if (x->approx_method == k_METHOD_EULER) {
			// v'(t) = a -> (vf - vi)/h = a
			prt->acc = get_acceleration(x, x->particle[i].r_it.coord, dist);
			prt->speed = pt_pt_sum(prt->speed, pt_number_prod(prt->acc, h));
			prt->r_it.coord = pt_pt_sum(prt->r_it.coord, pt_number_prod(prt->speed, h));
		} else if (x->approx_method == k_METHOD_LEAPFROG) {
            if (x->cycle_num != 0) {
                prt->acc = prt->a_i1;
                fill_body_dist(x, x->particle[i].r_it.coord, dist);
            } else
                prt->acc = get_acceleration(x, x->particle[i].r_it.coord, dist);
			prt->r_it.coord = pt_pt_sum(pt_pt_sum(prt->r_it.coord, pt_number_prod(prt->speed, h)), pt_number_prod(prt->acc, h * h / 2.));
			prt->a_i1 = get_acceleration(x, x->particle[i].r_it.coord, NULL);	//a_i+1
			prt->speed = pt_pt_sum(prt->speed, pt_number_prod(pt_pt_sum(prt->a_i1, prt->acc), h/2.));
		} else if (x->approx_method == k_METHOD_RUNGE_KUTTA) {
			t_pt4 y_n = build_pt4(x->particle[i].r_it.coord.x, x->particle[i].r_it.coord.y, x->particle[i].speed.x, x->particle[i].speed.y);
			t_pt4 rkf = rk_f(x, y_n, dist);
			t_pt4 k1 = pt_double_prod4(rkf, h);
			t_pt4 k2 = pt_double_prod4(rk_f(x, pt_pt_sum4(y_n, pt_double_prod4(k1, 0.5)), NULL), h);
			t_pt4 k3 = pt_double_prod4(rk_f(x, pt_pt_sum4(y_n, pt_double_prod4(k2, 0.5)), NULL), h);
			t_pt4 k4 = pt_double_prod4(rk_f(x, pt_pt_sum4(y_n, k3), NULL), h);
			t_pt4 y_n1 = pt_pt_sum4(y_n, pt_double_prod4(pt_pt_sum4(pt_pt_sum4(pt_pt_sum4(k1, pt_double_prod4(k2, 2)), pt_double_prod4(k3, 2)), k4), 1./6.));
			prt->r_it.coord = build_pt(y_n1.x, y_n1.y);
			prt->speed = build_pt(y_n1.z, y_n1.w);
			prt->acc = build_pt(rkf.z, rkf.w);
		}
		
		// checking played notes
        for (j = 0; j < x->num_bodies; j++){
            if ((x->body[j].r_it.flags & D_MUTE) || (x->there_are_solo_bodies && !(x->body[j].r_it.flags & D_SOLO)))
                continue;
            
            if (dist[j] < x->zero_velocity_distance) {
                no_playing_arrows[j] = 0;
                
                // did we trespass some arrow?
                double old_angle = delta_coord_to_angle_from_the_top(x, x->body[j].r_it.coord, prev_coord);
                double new_angle = delta_coord_to_angle_from_the_top(x, x->body[j].r_it.coord, prt->r_it.coord);
                char across_zero_point = (fabs(old_angle - new_angle) > TWOPI - 2 * DADA_BODIES_THRESHOLD_FOR_ANGLES);
                char angles_are_near = (fabs(old_angle - new_angle) < DADA_BODIES_THRESHOLD_FOR_ANGLES);
                char direction = (new_angle > old_angle ? 1 : -1);
                for (k = 0; k < x->body[j].num_arrownotes; k++){
                    double this_angle = x->body[j].arrownote[k].angle;
                    char play_this = false;
                    if (angles_are_near) {
                        if (direction == 1){
                            if (this_angle >= old_angle && this_angle < new_angle)
                                play_this = true;
                            else if (this_angle > new_angle)
                                break;
                        }
                        if (direction == -1){
                            if (this_angle >= new_angle && this_angle < old_angle)
                                play_this = true;
                            else if (this_angle > old_angle)
                                break;
                        }
                    } else if (across_zero_point) {
                        if ((this_angle > TWOPI - 0.2 && this_angle >= MAX(old_angle, new_angle)) ||
                            (this_angle < 0.2 && this_angle < MIN(old_angle, new_angle)))
                            play_this = true;
                    }
                    
                    if (play_this) {
                        double vel;
                        if (x->velocity_slope == 0.)
                            vel = rescale(dist[j], x->zero_velocity_distance, x->max_velocity_distance, 0, CONST_MAX_VELOCITY);
                        else
                            vel = rescale_with_slope(dist[j], x->zero_velocity_distance, x->max_velocity_distance, 0, CONST_MAX_VELOCITY, x->velocity_slope);
                        
                        t_llll *this_arrownote_to_play = llll_get();
                        llll_appendlong(this_arrownote_to_play, j);
                        llll_appendlong(this_arrownote_to_play, k);
                        llll_appendlong(this_arrownote_to_play, CLAMP(round(vel), 0, CONST_MAX_VELOCITY));
                        llll_appendlong(this_arrownote_to_play, i);
                        llll_appendllll(ll_to_play, this_arrownote_to_play);
                    }
                }
            }
        }
	}
    
    dadaobj_mutex_unlock(dadaobj_cast(x));
    
    t_llllelem *elem;
    for (elem = ll_to_play->l_head; elem; elem = elem->l_next) {
        t_llll *ll = hatom_getllll(&elem->l_hatom);
        long j = hatom_getlong(&ll->l_head->l_hatom);
        long k = hatom_getlong(&ll->l_head->l_next->l_hatom);
        long vel = hatom_getlong(&ll->l_head->l_next->l_next->l_hatom);
        long i = hatom_getlong(&ll->l_head->l_next->l_next->l_next->l_hatom);
        play_arrownote(x, j, k, vel, i);
    }
    
    for (j = 0; j < num_bodies; j++)
        if (no_playing_arrows[j])
            send_noteoff(x, j);
    
	setclock_fdelay(x->b_ob.d_ob.m_play.setclock->s_thing, x->b_ob.d_ob.m_play.m_clock,  x->b_ob.d_ob.m_play.play_step_ms);
    
    if (x->follow_particle)
        x->must_follow = true;
    
    llll_free(ll_to_play);
	jbox_redraw((t_jbox *)x);
}


void bodies_undo_step_push(t_bodies *x, t_symbol *operation)
{
    undo_add_interface_step(dadaobj_cast(x), DADA_FUNC_v_oX, (method)bodies_set_state, NULL, DADA_FUNC_X_o, (method)bodies_get_state, NULL, DADA_UNDO_OP_MODIFICATION, operation);
}

void bodies_dump(t_bodies *x, char dump_bodies, char dump_particles)
{
	t_llll *out = get_curr_state(x, dump_bodies, dump_particles);
	llllobj_outlet_llll((t_object *) x, LLLL_OBJ_UI, 0, out);
	llll_free(out);
}

void bodies_settime(t_bodies *x, double time){
	x->time = time;
}

void bodies_restart(t_bodies *x){
	x->time = 0;
}




void bodies_int(t_bodies *x, long num){
	// on off;
	if (num) {
        bodies_play(x, NULL, 0, NULL);
	} else
		bodies_stop(x, NULL, 0, NULL);
}

void bodies_float(t_bodies *x, double num){
	t_atom argv[1]; atom_setfloat(argv, num);
	bodies_anything(x, _sym_float, 1, argv);
}

void bodies_destroy_popup_menus(t_bodies *x){
	if (x->popup_body)
		jpopupmenu_destroy(x->popup_body);
	if (x->popup_body_midichannels)
		jpopupmenu_destroy(x->popup_body_midichannels);
	if (x->popup_body_transpose)
		jpopupmenu_destroy(x->popup_body_transpose);
	if (x->popup_background)
		jpopupmenu_destroy(x->popup_background);
	if (x->popup_particle)
		jpopupmenu_destroy(x->popup_particle);
	if (x->popup_particle_midichannels)
		jpopupmenu_destroy(x->popup_particle_midichannels);
	if (x->popup_particle_forceperiod)
		jpopupmenu_destroy(x->popup_particle_forceperiod);
	jfont_destroy(x->popup_main_font);
	jfont_destroy(x->popup_secondary_font);
}


void bodies_free(t_bodies *x)
{
	bodies_destroy_popup_menus(x);
	sysmem_freeptr(x->proxy);
	if (x->n_lexpr)
		lexpr_free(x->n_lexpr);
	if (x->n_lexpr2)
		lexpr_free(x->n_lexpr2);
    dadaobj_jbox_free((t_dadaobj_jbox *)x); // jbox_free and llllobj_free are inside here
}


// IN COORDINATES
double delta_coord_to_angle_from_the_top(t_bodies *x, t_pt center, t_pt pt){
	return fmod(PIOVERTWO - delta_coord_to_angle(x, center, pt) + TWOPI, TWOPI);
}

double delta_coord_to_angle(t_bodies *x, t_pt center, t_pt pt){
	double alpha = atan((pt.y - center.y)/(pt.x - center.x));
	if (pt.x < center.x)
		alpha += PI;
	return fmod(alpha + TWOPI, TWOPI); // ORDINARY ANGLE (from right)
}
	
// IN PIXEL FOR SCREEN
double pt_to_angle(t_bodies *x, t_pt center, t_pt pt){
	double alpha = atan((center.y - pt.y)/(pt.x - center.x));
	if (pt.x < center.x)
		alpha += PI;
	return fmod(PIOVERTWO - alpha + TWOPI, TWOPI); // 0 is at top, and then clockwise
}

t_pt get_topleft_angle_for_writing_around_the_clock(t_pt center, double radius, double alpha, double label_width, double label_height){
	
	t_pt P;	// P is the point around the clock
	P.x = center.x + radius * sin(alpha);
	P.y = center.y + radius * cos(alpha);
	
	t_pt Q;	// Q is the top left corner of the label
	Q.y = P.y;
	if ((alpha >= 0 && alpha < PI/4) || (alpha < TWOPI && alpha > TWOPI * 7/8)) {
		Q.x = P.x - label_width * (1 - fmod(alpha + PI/4, TWOPI)/PIOVERTWO);
		Q.y = P.y + label_height;
	} else if (alpha >= PI/4 && alpha < PI * 3/4) {
		Q.y = P.y + label_height * fmod(PI * 3/4 - alpha, TWOPI)/PIOVERTWO;
		Q.x = P.x;
	} else if (alpha >= PI *3/4 && alpha < PI * 5/4) {
		Q.x = P.x - label_width * (1 -fmod(PI * 5/4 - alpha, TWOPI)/PIOVERTWO);
		Q.y = P.y;
	} else {
		Q.y = P.y + label_height * (1 - fmod(PI * 7/4 - alpha, TWOPI)/PIOVERTWO);
		Q.x = P.x - label_width;
	}
	return Q;
}


void paint_static_stuff(t_bodies *x, t_object *view, t_rect rect){
	
	t_jgraphics *g = jbox_start_layer((t_object *)x, view, gensym("room"), rect.width, rect.height);

	if (g){
		double zoom = x->b_ob.d_ob.m_zoom.zoom.x;
		t_jfont *jf_text = jfont_create("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, 10);
		t_jfont *jf_body_numbers = jfont_create("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_BOLD, 10);
		t_jfont *jf_densities = jfont_create("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, 10 * zoom);
		t_jfont *jf_notes = jfont_create("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, 10 * zoom);

        t_pt origin = get_center_pix(dadaobj_cast(x), view, NULL);

        if (false) {
            char zoomtxt[100];
            snprintf(zoomtxt, 99, "zoom %.2f %%", x->b_ob.d_ob.m_zoom.zoom.x * 100);
            write_text(g, jf_text, get_grey(0.5), zoomtxt, 1, 1, rect.width - 2, rect.height - 2, JGRAPHICS_TEXT_JUSTIFICATION_TOPRIGHT, true, false);
        }
		
		long i, j;
		for (i = 0; i < x->num_bodies; i++){
			t_jrgba bordercolor = x->body[i].r_it.color;
			t_jrgba fillcolor = change_alpha(x->body[i].r_it.color, x->body[i].r_it.color.alpha * 0.7);
			t_body *bd = &x->body[i];
			char density[1000];
			
			t_pt pos = coord_to_pix(dadaobj_cast(x), origin, bd->r_it.coord);
            double rad = bd->radius * zoom;
			
			paint_circle(g, bordercolor, fillcolor, pos.x, pos.y, rad, 1);
			
			// notearrows
			for (j = 0; j < bd->num_arrownotes; j++){
                t_jrgba arrowcolor = color_interp(bordercolor, get_grey(0.5), 0.1);
                double addrad = DADA_BODIES_ARROWNOTE_ADDITIONAL_RADIUS * zoom;
                double x1 = pos.x + rad * sin(bd->arrownote[j].angle);
                double y1 = pos.y - rad * cos(bd->arrownote[j].angle);
				double x2 = pos.x + (rad + addrad) * sin(bd->arrownote[j].angle);
				double y2 = pos.y - (rad + addrad) * cos(bd->arrownote[j].angle);
				paint_line(g, arrowcolor, x1, y1, x2, y2, 1.);
				
                if (x->show_notes == 2) {
                    double width = 25 * zoom;
                    double height = 16 * zoom;
                    t_pt boxpt = get_topleft_angle_for_writing_around_the_clock(build_pt(pos.x, -pos.y), rad + addrad + 2, bd->arrownote[j].angle, width, height);
                    t_rect noterect = build_rect(boxpt.x, -boxpt.y, width, height);
                    t_jrgba *color = (x->last_played_arrow[i] == j ? &x->b_ob.d_ob.m_play.play_color : &arrowcolor);
                    
//                    paint_rect(g, &noterect, &arrowcolor, NULL, 2, 0);

                    ezpaint_note_with_staff((t_object *)x, g, view, bd->arrownote[j].midicents, k_ACC_AUTO, x->tone_division, build_pt(noterect.x, noterect.y), noterect.width, 12 * zoom, noterect.x + 15 * zoom, false, color, color, color);
                } else if (x->show_notes == 1){
                    paint_circle_filled(g, arrowcolor, x2, y2, DADA_BODIES_ARROWNOTE_END_PT_RADIUS * zoom);

                    t_pt center = coord_to_pix(dadaobj_cast(x), origin, bd->arrownote[j].label_center);
                    write_text(g, jf_notes, arrowcolor, bd->arrownote[j].label_text, center.x - 20 * zoom, center.y - 20 * zoom, 40 * zoom, 40 * zoom, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, true, false);
                }
                
/*				if (x->b_ob.d_ob.m_interface.mouse_is_down && x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_BODIES_ARROWNOTE && x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx == i && x->b_ob.d_ob.m_interface.mousedown_item_identifier.secondary_idx == j){
					char text[20];
					snprintf(text, 20, "angle: %.2f°", rad2deg(bd->arrownote[j].angle));
					write_text(g, jf_notes, arrowcolor, text, pos.x + rad, pos.y - rad, 120 * zoom, 120 * zoom, JGRAPHICS_TEXT_JUSTIFICATION_TOPLEFT, true, false);
				} */
			}
			
            if (x->show_density) {
                snprintf(density, 999, "ẟ %.2f", bd->density);
                write_text(g, jf_densities, get_grey_to_write_over_color(fillcolor, 0.3), density, pos.x - 30 *zoom , pos.y - 10 * zoom, 60 *zoom, 20 *zoom, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, true, false);
            }

			if (x->body[i].r_it.flags & D_MUTE){
				// paint a X
				paint_line(g, DADA_GREY_50, pos.x-rad, pos.y-rad, pos.x+rad, pos.y+rad, 1);
				paint_line(g, DADA_GREY_50, pos.x-rad, pos.y+rad, pos.x+rad, pos.y-rad, 1);
			}
			if (x->body[i].r_it.flags & D_INACTIVE)
				paint_circle(g, bordercolor, change_alpha(DADA_GREY_50, 0.6), pos.x, pos.y, rad + 4, 1);
			if (x->body[i].r_it.flags & D_SOLITARY)
				paint_circle_stroken(g, bordercolor, pos.x, pos.y, rad + 4, 3);
			if (x->body[i].r_it.flags & D_SOLO){
				paint_circle_stroken(g, change_alpha(bordercolor, 0.9), pos.x, pos.y, rad + 3, 1);
				paint_circle_stroken(g, change_alpha(bordercolor, 0.7), pos.x, pos.y, rad + 6, 1);
				paint_circle_stroken(g, change_alpha(bordercolor, 0.45), pos.x, pos.y, rad + 10, 1);
				paint_circle_stroken(g, change_alpha(bordercolor, 0.2), pos.x, pos.y, rad + 15, 1);
			}
			
			if (x->show_bodies_id){
				char text[20];
				double width, height;
				sprintf(text, "%ld", i + 1);
				jfont_text_measure(jf_body_numbers, text, &width, &height);
				write_text(g, jf_body_numbers, DADA_GREY_25, text, pos.x - rad - width/2, pos.y - rad - height/2, 2 * width, 2 * height, JGRAPHICS_TEXT_JUSTIFICATION_TOPLEFT, true, false);
			}
		}
		
		jfont_destroy(jf_body_numbers);
		jfont_destroy(jf_text);
		jfont_destroy(jf_densities);
		jfont_destroy(jf_notes);
		jbox_end_layer((t_object*)x, view, gensym("room"));
	}
	jbox_paint_layer((t_object *)x, view, gensym("room"), 0., 0.);	// position of the layer
}

void recompute_solo_flag(t_bodies *x){
	long i;
	x->there_are_solo_bodies = false;
	for (i = 0; i < x->num_bodies; i++){
		if (x->body[i].r_it.flags & D_SOLO) {
			x->there_are_solo_bodies = true;
			break;
		}
	}
	x->there_are_solitary_bodies = false;
	for (i = 0; i < x->num_bodies; i++){
		if (x->body[i].r_it.flags & D_SOLITARY) {
			x->there_are_solitary_bodies = true;
			break;
		}
	}
	x->there_are_solo_particles = false;
	for (i = 0; i < x->num_particles; i++){
		if (x->particle[i].r_it.flags & D_SOLO) {
			x->there_are_solo_particles = true;
			break;
		}
	}	
}

t_max_err bodies_notify(t_bodies *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	recompute_solo_flag(x);
	jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
//	if (s == gensym("attr_modified")) {

		/*		t_symbol *name = (t_symbol *)object_method((t_object *)data, gensym("getname"));
		if (name == gensym("rectcolor"))
			jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));*/
//	}
	return jbox_notify((t_jbox *)x, s, msg, sender, data);
}

void bodies_paint(t_bodies *x, t_object *view)
{
	t_rect rect;
	long i;
    t_jgraphics *g = (t_jgraphics*) patcherview_get_jgraphics(view);
    jbox_get_rect_for_view((t_object *)x, view, &rect);

    dadaobj_paint_background(dadaobj_cast(x), g, &rect);

    if (x->running && x->hide_while_running) {
        dadaobj_paint_border(dadaobj_cast(x), g, &rect);
        return;
    }

    if (x->must_follow) {
        bodies_follow(x, view, &rect);
        x->must_follow = false;
    }
    
    if (dadaobj_cast(x)->m_zoom.must_autozoom) {
        bodies_autozoom(x, view, &rect);
        dadaobj_cast(x)->m_zoom.must_autozoom = false;
    }


    
    g = (t_jgraphics*) patcherview_get_jgraphics(view);
    t_pt center = get_center_pix(dadaobj_cast(x), view, &rect);
	double zoom = x->b_ob.d_ob.m_zoom.zoom.x;

    dadaobj_paint_grid(dadaobj_cast(x), view, rect, center);
    
	paint_static_stuff(x, view, rect);

	t_jfont *jf_vels = jfont_create("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, 10);
	for (i = 0; i < x->num_particles; i++){
        t_particle *prt = &x->particle[i];
		t_jrgba bordercolor = prt->r_it.color;
		t_jrgba fillcolor = prt->r_it.color;
		double rad = DADA_BODIES_PARTICLE_RADIUS * 2;

		t_pt pos = coord_to_pix(dadaobj_cast(x), center, prt->r_it.coord);
		
		paint_circle(g, bordercolor, fillcolor, pos.x, pos.y, DADA_BODIES_PARTICLE_RADIUS, 1);
		
		if (x->particle[i].r_it.flags & D_MUTE){
			// paint a X
			paint_line(g, bordercolor, pos.x-rad, pos.y-rad, pos.x+rad, pos.y+rad, 1);
			paint_line(g, bordercolor, pos.x-rad, pos.y+rad, pos.x+rad, pos.y-rad, 1);
		}
		if (x->particle[i].r_it.flags & D_SOLO){
			paint_circle_stroken(g, change_alpha(bordercolor, 0.9), pos.x, pos.y, DADA_BODIES_PARTICLE_RADIUS + 3, 1);
			paint_circle_stroken(g, change_alpha(bordercolor, 0.7), pos.x, pos.y, DADA_BODIES_PARTICLE_RADIUS + 6, 1);
			paint_circle_stroken(g, change_alpha(bordercolor, 0.45), pos.x, pos.y, DADA_BODIES_PARTICLE_RADIUS + 10, 1);
			paint_circle_stroken(g, change_alpha(bordercolor, 0.2), pos.x, pos.y, DADA_BODIES_PARTICLE_RADIUS + 15, 1);
		}
		

		if (x->show_speed){
            if (isnan(prt->speed.x) || isnan(prt->speed.y)) {
                // nothing to paint, speed is NaN!
            } else {
                double velx = zoom * prt->speed.x / 4;
                double vely = - zoom * prt->speed.y / 4;
                paint_arrow(g, bordercolor, pos.x, pos.y, pos.x + velx, pos.y + vely, 1, 5, 5);
                if (x->show_speed > 1) {
                    char veltext[100];
                    snprintf(veltext, 99, "v (%.1f, %.1f)", prt->speed.x, prt->speed.y);
                    write_text(g, jf_vels, bordercolor, veltext, pos.x+velx, pos.y+vely, 200, 200, JGRAPHICS_TEXT_JUSTIFICATION_LEFT + JGRAPHICS_TEXT_JUSTIFICATION_TOP, true, false);
                }
            }
		}
		
		if (x->show_acceleration){
			t_jrgba acccolor = build_jrgba(0.1, 0.5, 0.3, 1.);
			double accx = zoom * prt->acc.x / 25.;
			double accy = -zoom * prt->acc.y / 25.;
			paint_arrow(g, acccolor, pos.x, pos.y, pos.x + accx, pos.y + accy, 1, 5, 5);
            if (x->show_acceleration > 1) {
                char acctext[100];
                snprintf(acctext, 99, "a (%.1f, %.1f)", prt->acc.x, prt->acc.y);
                write_text(g, jf_vels, acccolor, acctext, pos.x+accx, pos.y+accy, 200, 200, JGRAPHICS_TEXT_JUSTIFICATION_LEFT + JGRAPHICS_TEXT_JUSTIFICATION_TOP, true, false);
            }
		}

		if (x->show_particles_id){
			char text[20];
			t_jfont *jf_particles_numbers = jfont_create("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_BOLD, 11);
			double width, height;
			sprintf(text, "%ld", i + 1);
			jfont_text_measure(jf_particles_numbers, text, &width, &height);
			write_text(g, jf_particles_numbers, DADA_GREY_25, text, pos.x - rad - width/2, pos.y - rad - height/2, 2 * width, 2 * height, JGRAPHICS_TEXT_JUSTIFICATION_TOPLEFT, true, false);
			jfont_destroy(jf_particles_numbers);
		}
	}
	jfont_destroy(jf_vels);
    
    dadaobj_paint_border(dadaobj_cast(x), g, &rect);
}


void send_values(t_bodies *x){
/*	t_atom av1[x->num_sliders];
	t_atom av2[x->num_sliders];
	long i;
	for (i = 0; i < x->num_sliders; i++) {
		if (x->float_output) {
			atom_setfloat(&av1[i], x->slider_val1[i]);
			atom_setfloat(&av2[i], x->slider_val2[i]);
		} else {
			atom_setlong(&av1[i], round(x->slider_val1[i]));
			atom_setlong(&av2[i], round(x->slider_val2[i]));
		}
	}
	outlet_list(x->out2, 0L, x->num_sliders, av2);
	outlet_list(x->out1, 0L, x->num_sliders, av1); */
}

void bodies_bang(t_bodies *x)
{
//	object_post((t_object *)x, "bang!");
}


void compute_label_for_all_arrownotes(t_bodies *x, long body_idx){
	if (body_idx > -1 && body_idx < DADA_BODIES_MAX_BODIES){
		long i;
		for (i = 0; i < x->body[body_idx].num_arrownotes; i++)
			compute_label_for_arrownote(x, body_idx, i);
	}
}


void snap_coord_to_grid(t_bodies *x, t_pt *coord){
	coord->x = round(coord->x/x->b_ob.d_ob.m_grid.grid_size.x) * x->b_ob.d_ob.m_grid.grid_size.x;
	coord->y = round(coord->y/x->b_ob.d_ob.m_grid.grid_size.y) * x->b_ob.d_ob.m_grid.grid_size.y;
}


void body_change_color(t_bodies *x, long idx, double delta_hue, double delta_lightness)
{
    if (idx >= 0 && idx < x->num_bodies) {
        change_hue_and_lightness(&x->body[idx].r_it.color, delta_hue, delta_lightness, DADA_BODIES_MIN_LIGHTNESS, DADA_BODIES_MAX_LIGHTNESS);
        jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
    }
}

void particle_change_color(t_bodies *x, long idx, double delta_hue, double delta_lightness)
{
    if (idx >= 0 && idx < x->num_bodies) {
        change_hue_and_lightness(&x->particle[idx].r_it.color, delta_hue, delta_lightness, DADA_BODIES_MIN_LIGHTNESS, DADA_BODIES_MAX_LIGHTNESS);
        jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
    }
}
void bodies_mousedrag(t_bodies *x, t_object *patcherview, t_pt pt, long modifiers)
{
    long dragged_index = x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx;
    long dragged_secondary_index = x->b_ob.d_ob.m_interface.mousedown_item_identifier.secondary_idx;
    char dragged_type = x->b_ob.d_ob.m_interface.mousedown_item_identifier.type;
    char tool = x->b_ob.d_ob.m_tools.curr_tool;
    t_pt mousedrag_pt = x->b_ob.d_ob.m_interface.mousedrag_pix;
    
    if (dadaobj_mousedrag(dadaobj_cast(x), patcherview, pt, modifiers))
        return;

    if (dragged_index >= 0) {
        t_pt center = get_center_pix(dadaobj_cast(x), patcherview, NULL);
        
        switch (dragged_type) {
            case DADAITEM_TYPE_BODIES_BODY:
            {
                if (modifiers & eControlKey && modifiers & eShiftKey) { // increase density
                    double scale_factor = pow(2, -x->b_ob.d_ob.m_interface.mousedrag_delta_pix.y/20.);
                    bodies_undo_step_push(x, gensym("Change Body Density"));
                    x->body[dragged_index].density = fabs(x->body[dragged_index].density * scale_factor);
                    update_mass_from_density_and_radius_for_body(x, dragged_index);
                } else if (tool == DADA_TOOL_SCALE) { // increase radius
                    bodies_undo_step_push(x, gensym("Change Body Radius"));
                    double scale_factor = pow(2, -x->b_ob.d_ob.m_interface.mousedrag_delta_pix.y/20.);
                    x->body[dragged_index].radius *= scale_factor;
                    compute_label_for_all_arrownotes(x, dragged_index);
                    update_mass_from_density_and_radius_for_body(x, dragged_index);
                } else if (tool == DADA_TOOL_ROTATE) { // increase radius
                    bodies_undo_step_push(x, gensym("Rotate Body Notes"));
                    double angle = -x->b_ob.d_ob.m_interface.mousedrag_delta_pix.y/20.; // pt_to_angle(x, body_center, pt);
                    long j;
                    for (j = 0; j < x->body[dragged_index].num_arrownotes; j++)
                        x->body[dragged_index].arrownote[j].angle += angle;
                    t_llll *ll = get_arrownotes_as_llll(x, dragged_index);
                    set_arrownotes_to_body(x, dragged_index, ll, &x->b_ob.d_ob.m_interface.mousedown_item_identifier.secondary_idx);	///< for inside we sort them
                    llll_free(ll);
                    compute_label_for_all_arrownotes(x, dragged_index);
                } else if (tool == DADA_TOOL_CHANGE_PITCH) { // increase radius
                    bodies_undo_step_push(x, gensym("Transpose Body"));
                    double how_much = -x->b_ob.d_ob.m_interface.mousedrag_delta_pix.y * 6;
                    long j;
                    for (j = 0; j < x->body[dragged_index].num_arrownotes; j++) {
                        x->body[dragged_index].arrownote[j].midicents += how_much;
                        compute_label_for_arrownote(x, dragged_index, j);
                    }
                } else if (tool == DADA_TOOL_CHANGE_COLOR) { // change color
                    bodies_undo_step_push(x, gensym("Change Body Color"));
                    body_change_color(x, dragged_index, x->b_ob.d_ob.m_interface.mousedrag_delta_pix.x/50, -x->b_ob.d_ob.m_interface.mousedrag_delta_pix.y/100);
                } else {
                    if ((modifiers & eAltKey) && !(x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag & DADAITEM_IDENTIFIER_FLAG_DUPLICATED)){
                        bodies_undo_step_push(x, gensym("Duplicate Body"));
                        long new_idx = duplicate_body(x, dragged_index);
                        if (new_idx < 0) {
                            object_error((t_object *)x, "Can't duplicate body.");
                            x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
                        } else {
                            x->body[new_idx].r_it.color = long_to_color(new_idx * 2);
                            x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx = x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx = new_idx;
                            x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag |= DADAITEM_IDENTIFIER_FLAG_DUPLICATED;
                            jbox_redraw((t_jbox *)x);
                        }
                    } else {
                        bodies_undo_step_push(x, gensym("Move Body"));
                        x->body[dragged_index].r_it.coord = pt_pt_sum(x->body[dragged_index].r_it.coord, delta_pix_to_delta_coord(dadaobj_cast(x), pt_pt_diff(pt, mousedrag_pt)));
                        compute_label_for_all_arrownotes(x, dragged_index);
                    }
                }
                jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
                break;
            }
                
            case DADAITEM_TYPE_BODIES_ARROWNOTE:
            {
                if (tool == DADA_TOOL_CHANGE_PITCH) {
                    bodies_undo_step_push(x, gensym("Change Body Note"));
                    double how_much = -x->b_ob.d_ob.m_interface.mousedrag_delta_pix.y * 6;
                    x->body[dragged_index].arrownote[dragged_secondary_index].midicents += how_much;
                    compute_label_for_arrownote(x, dragged_index, dragged_secondary_index);
                } else {
                    bodies_undo_step_push(x, gensym("Change Body Notes"));
                    t_pt body_center = coord_to_pix(dadaobj_cast(x), center, x->body[dragged_index].r_it.coord);
                    double angle = pt_to_angle(x, body_center, pt);
                    x->body[dragged_index].arrownote[dragged_secondary_index].angle = angle;
                    t_llll *ll = get_arrownotes_as_llll(x, dragged_index);
                    set_arrownotes_to_body(x, dragged_index, ll, &x->b_ob.d_ob.m_interface.mousedown_item_identifier.secondary_idx);	///< for inside we sort them
                    llll_free(ll);
                }
                jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
                break;
            }
                
            case DADAITEM_TYPE_BODIES_PARTICLE:
            {
                if (tool == DADA_TOOL_SCALE) {
                    bodies_undo_step_push(x, gensym("Scale Planet Velocity"));
                    if ((isnan(x->particle[dragged_index].speed.x) || isnan(x->particle[dragged_index].speed.y)) ||
                        (x->particle[dragged_index].speed.x == 0 && x->particle[dragged_index].speed.y == 0)){
                        x->particle[dragged_index].speed.x = 0.01 * isign(x->b_ob.d_ob.m_interface.mousedrag_delta_pix.y);
                        x->particle[dragged_index].speed.y = 0;
                    } else {
                        double scale_factor = pow(2, -x->b_ob.d_ob.m_interface.mousedrag_delta_pix.y/20.);
                        if (MAX(x->particle[dragged_index].speed.x, x->particle[dragged_index].speed.y) < 0.001)
                            x->particle[dragged_index].speed.x = x->particle[dragged_index].speed.x = 0.001;
                        else
                            x->particle[dragged_index].speed = pt_number_prod(x->particle[dragged_index].speed, scale_factor);
                    }
                    jbox_redraw((t_jbox *) x);
                } else if (tool == DADA_TOOL_ROTATE) {
                    bodies_undo_step_push(x, gensym("Rotate Planet Velocity"));
                    double angle = x->b_ob.d_ob.m_interface.mousedrag_delta_pix.y/20.;
                    x->particle[dragged_index].speed = pt_rotate(x->particle[dragged_index].speed, angle);
                } else if (tool == DADA_TOOL_CHANGE_COLOR) { // change color
                    bodies_undo_step_push(x, gensym("Change Planet Color"));
                    particle_change_color(x, dragged_index, x->b_ob.d_ob.m_interface.mousedrag_delta_pix.x/50, -x->b_ob.d_ob.m_interface.mousedrag_delta_pix.y/100);
                } else {
                    if ((modifiers & eAltKey) && !(x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag & DADAITEM_IDENTIFIER_FLAG_DUPLICATED)){
                        bodies_undo_step_push(x, gensym("Duplicate Planet"));
                        long new_idx = duplicate_particle(x, dragged_index);
                        if (new_idx < 0) {
                            object_error((t_object *)x, "Can't duplicate planet.");
                            x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
                        } else {
                            x->particle[new_idx].r_it.color = long_to_color(new_idx * 2 + 1);
                            x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx = x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx = new_idx;
                            x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag |= DADAITEM_IDENTIFIER_FLAG_DUPLICATED;
                            jbox_redraw((t_jbox *)x);
                        }
                    } else {
                        bodies_undo_step_push(x, gensym("Move Planet"));
                        t_pt coord = pix_to_coord(dadaobj_cast(x), center, pt);
                        x->particle[dragged_index].r_it.coord = coord;
                    }
                }
                break;
            }
            default:
                break;
        }
        
		jbox_redraw((t_jbox *) x);
	}
}


t_pt4 build_pt4(double x, double y, double z, double w){
	t_pt4 out;
	out.x = x;
	out.y = y;
	out.z = z;
	out.w = w;
	return out;
}



long get_nearest_body_idx(t_bodies *x, t_pt coord, double *dist){
	long i;
	double best_dist = -1;
	long best_idx = -1;
	for (i = 0; i < x->num_bodies; i++){
		double this_dist = pt_pt_distance_squared(x->body[i].r_it.coord, coord);
		if (best_idx < 0 || this_dist < best_dist){
			best_dist = this_dist;
			best_idx = i;
		}
	}
	if (dist)
		*dist = sqrt(best_dist);
	return best_idx;
}

void uniformly_distribute_arrownotes(t_bodies *x, long body_idx, char add_mirror){
	long i;
	long num = x->body[body_idx].num_arrownotes;
	long divider = (add_mirror ? 2 * num - 1 : num); 
	if ((add_mirror && 2 * num - 1 < DADA_BODIES_MAX_ARROWNOTES) || num < DADA_BODIES_MAX_ARROWNOTES){
		for (i = 0; i < num; i++){
			x->body[body_idx].arrownote[i].angle = TWOPI * i/divider;
			compute_label_for_arrownote(x, body_idx, i);
		}
		if (add_mirror)  {
			for (i = num - 1; i > 0; i--){
				x->body[body_idx].arrownote[x->body[body_idx].num_arrownotes].angle = TWOPI * (1 - ((double)i)/divider);
				x->body[body_idx].arrownote[x->body[body_idx].num_arrownotes].midicents = x->body[body_idx].arrownote[i].midicents;
				compute_label_for_arrownote(x, body_idx, x->body[body_idx].num_arrownotes);
				x->body[body_idx].num_arrownotes++;
			}
		}
	}
	jbox_redraw((t_jbox *) x);
}


long coord_to_body(t_bodies *x, t_pt coord)
{
    long i;
    double zoom = x->b_ob.d_ob.m_zoom.zoom.x;
    double pad = DADA_BODIES_SELECTION_PAD/ zoom;
    for (i = 0; i < x->num_bodies; i++)
        if (pt_pt_distance_squared(x->body[i].r_it.coord, coord) <= (x->body[i].radius + pad)*(x->body[i].radius + pad))
            return i;
    return -1;
}

long pixel_to_body(t_bodies *x, t_pt pt, t_object *view, t_pt *coordinates)
{
    t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), view, pt);
    if (coordinates)
        *coordinates = coord;
    return coord_to_body(x, coord);
}


long coord_to_particle(t_bodies *x, t_pt coord)
{
    long i;
    double zoom = x->b_ob.d_ob.m_zoom.zoom.x;
    double toll = (DADA_BODIES_PARTICLE_RADIUS + DADA_BODIES_SELECTION_PAD)/ zoom;
    for (i = 0; i < x->num_particles; i++)
        if (pt_pt_distance_squared(x->particle[i].r_it.coord, coord) <= toll * toll)
            return i;
    return -1;
}

long pixel_to_particle(t_bodies *x, t_pt pt, t_object *view, t_pt *coordinates)
{
    t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), view, pt);
    if (coordinates)
        *coordinates = coord;
    return coord_to_particle(x, coord);
}

long pixel_to_arrowhead(t_bodies *x, t_pt pt, t_object *view, t_pt *coordinates, long *body)
{
    t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), view, pt);
    if (coordinates)
        *coordinates = coord;

    double zoom = dadaobj_cast(x)->m_zoom.zoom.x;
    double arrownote_add_rad = DADA_BODIES_ARROWNOTE_ADDITIONAL_RADIUS * zoom;
    double arrownote_end_pt_rad = DADA_BODIES_ARROWNOTE_END_PT_RADIUS * zoom;
    double width = 25 * zoom;
    double height = 16 * zoom;

    *body = -1;
    
    long i, j;
    for (i = 0; i < x->num_bodies; i++){
        double radius_pix = x->body[i].radius * zoom;
        t_pt center_pix = coord_to_pix_from_view(dadaobj_cast(x), view, x->body[i].r_it.coord);
        
        if (fabs(pt.x - center_pix.x) > radius_pix + arrownote_end_pt_rad + width + arrownote_add_rad ||
            fabs(pt.y - center_pix.y) > radius_pix + arrownote_end_pt_rad + width + arrownote_add_rad)
            continue;
        
        for (j = 0; j < x->body[i].num_arrownotes; j++){
            if (x->show_notes == 2) {
                t_pt boxpt = get_topleft_angle_for_writing_around_the_clock(build_pt(center_pix.x, -center_pix.y), radius_pix + arrownote_add_rad + 2, x->body[i].arrownote[j].angle, width, height);
                t_rect noterect = build_rect(boxpt.x, -boxpt.y, width, height);
                
                if (is_pt_in_rectangle(pt, noterect)) {
                    *body = i;
                    return j;
                }
            } else if (x->show_notes == 1){
                
                double x2 = center_pix.x + (radius_pix + arrownote_add_rad) * sin(x->body[i].arrownote[j].angle);
                double y2 = center_pix.y - (radius_pix + arrownote_add_rad) * cos(x->body[i].arrownote[j].angle);
                if (fabs(pt.x - x2) <= arrownote_end_pt_rad + 2 && fabs(pt.y - y2) <= arrownote_end_pt_rad + 2){
                    *body = i;
                    return j;
                }
            }
        }
    }
    
    return -1;
}


void bodies_output_notification(t_bodies *x, t_dadaitem_identifier *ident, t_symbol *sym)
{
    t_llll *ll = llll_get();
    llll_appendsym(ll, sym);
    
    switch (ident->type) {
        case DADAITEM_TYPE_BODIES_PARTICLE:
            llll_appendsym(ll, gensym("planet"));
            llll_appendlong(ll, ident->idx + 1);
            if (dadaobj_cast(x)->m_interface.send_notifications == DADAOBJ_NOTIFY_VERBOSE)
                llll_appendllll(ll, get_particle_info_as_llll(x, ident->idx));
            break;
            
        case DADAITEM_TYPE_BODIES_ARROWNOTE:
            llll_appendsym(ll, gensym("note"));
            llll_appendlong(ll, ident->idx + 1);
            llll_appendlong(ll, ident->secondary_idx + 1);
            if (dadaobj_cast(x)->m_interface.send_notifications == DADAOBJ_NOTIFY_VERBOSE) {
                t_llll *this_arrow = llll_get();
                if (ident->idx >= 0 && ident->idx < x->num_bodies && ident->secondary_idx >= 0 && ident->secondary_idx < x->body[ident->idx].num_arrownotes) {
                    llll_appenddouble(this_arrow, x->body[ident->idx].arrownote[ident->secondary_idx].angle);
                    llll_appenddouble(this_arrow, x->body[ident->idx].arrownote[ident->secondary_idx].midicents);
                }
            }
            break;
            
        case DADAITEM_TYPE_BODIES_BODY:
            llll_appendsym(ll, gensym("star"));
            llll_appendlong(ll, ident->idx + 1);
            if (dadaobj_cast(x)->m_interface.send_notifications == DADAOBJ_NOTIFY_VERBOSE)
                llll_appendllll(ll, get_body_info_as_llll(x, ident->idx));
            break;
            
        default:
            llll_appendsym(ll, _llllobj_sym_none);
            break;
    }
    
    dadaobj_send_notification_llll(dadaobj_cast(x), ll);
}



t_dadaitem_identifier pixel_to_element(t_bodies *x, t_pt pt, t_object *view, t_pt *coordinates)
{
    t_dadaitem_identifier result;
    long idx = -1;
    result.type = DADAITEM_TYPE_NONE;
    result.flag = 0;
    result.idx = result.secondary_idx = result.tertiary_idx = -1;
    
    if ((idx = pixel_to_particle(x, pt, view, coordinates)) >= 0) {
        result.type = DADAITEM_TYPE_BODIES_PARTICLE;
        result.idx = idx;
    } else if ((idx = pixel_to_arrowhead(x, pt, view, coordinates, &result.idx)) >= 0) {
        result.type = DADAITEM_TYPE_BODIES_ARROWNOTE;
        result.secondary_idx = idx;
    } else if ((idx = pixel_to_body(x, pt, view, coordinates)) >= 0) {
        result.type = DADAITEM_TYPE_BODIES_BODY;
        result.idx = idx;
    }
    
    return result;
}



void bodies_mousemove(t_bodies *x, t_object *patcherview, t_pt pt, long modifiers)
{
    t_dadaitem_identifier old_ident = x->b_ob.d_ob.m_interface.mousemove_item_identifier;

    llll_format_modifiers(&modifiers, NULL);
    
    if (dadaobj_mousemove(dadaobj_cast(x), patcherview, pt, modifiers))
        return;
    
//    post("called bodies");
  //  return;
    
    
    if (x->b_ob.d_ob.m_interface.allow_mouse_hover) {
        if (!x->b_ob.d_ob.m_interface.mouse_is_down) {
            x->b_ob.d_ob.m_interface.mousemove_item_identifier = pixel_to_element(x, pt, patcherview, NULL);

            if (!dadaitem_identifier_eq(old_ident, x->b_ob.d_ob.m_interface.mousemove_item_identifier))
                bodies_output_notification(x, &x->b_ob.d_ob.m_interface.mousemove_item_identifier, gensym("hover"));

            jbox_redraw((t_jbox *)x);
        }
    } else {
        if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type != DADAITEM_TYPE_NONE) {
            x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
            dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
            jbox_redraw((t_jbox *)x);
        }
    }
    
    long type = x->b_ob.d_ob.m_interface.mousemove_item_identifier.type;
    char tool = x->b_ob.d_ob.m_tools.curr_tool;
    
    if (popup_menu_is_shown(dadaobj_cast(x))) {
        dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
    } else if ((type == DADAITEM_TYPE_BODIES_BODY || type == DADAITEM_TYPE_BODIES_ARROWNOTE) && tool == DADA_TOOL_CHANGE_PITCH) {
        dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_NOTE_UPDOWN);
    } else if ((type == DADAITEM_TYPE_BODIES_BODY || type == DADAITEM_TYPE_BODIES_PARTICLE) && tool == DADA_TOOL_CHANGE_COLOR) {
        dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_CHANGE_COLOR);
    } else if ((type == DADAITEM_TYPE_BODIES_BODY || type == DADAITEM_TYPE_BODIES_PARTICLE) && tool == DADA_TOOL_SCALE) {
        dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_SCALE);
    } else if ((type == DADAITEM_TYPE_BODIES_BODY || type == DADAITEM_TYPE_BODIES_PARTICLE) && tool == DADA_TOOL_ROTATE) {
        dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_ROTATION);
    } else if ((type == DADAITEM_TYPE_BODIES_BODY || type == DADAITEM_TYPE_BODIES_PARTICLE) && modifiers == eAltKey) {
        dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DUPLICATE);
    } else if ((type == DADAITEM_TYPE_BODIES_BODY || type == DADAITEM_TYPE_BODIES_PARTICLE) && modifiers == eCommandKey) {
        dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DELETE);
    } else if (type == DADAITEM_TYPE_BODIES_BODY && (modifiers & eControlKey && modifiers & eShiftKey)) {
        dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_RESIZE_UPDOWN);
    } else if (type == DADAITEM_TYPE_BODIES_BODY && modifiers == eShiftKey) {
        dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_NOTE);
    } else if (type == DADAITEM_TYPE_BODIES_ARROWNOTE && modifiers & eCommandKey) {
        dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DELETE);
    } else if (type == DADAITEM_TYPE_BODIES_ARROWNOTE) {
        dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_ROTATION);
    } else if (type != DADAITEM_TYPE_NONE && tool == DADA_TOOL_ARROW) {
        dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_MOVE);
    } else if (type == DADAITEM_TYPE_NONE && (modifiers & eCommandKey && modifiers & eAltKey)) {
        dada_set_cursor(dadaobj_cast(x), patcherview,  BACH_CURSOR_ADD_POINT);
    } else if (type == DADAITEM_TYPE_NONE && modifiers & eCommandKey) {
        dada_set_cursor(dadaobj_cast(x), patcherview,  BACH_CURSOR_CROSSHAIR);
    } else {
        dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
    }
    
}

void bodies_mousewheel(t_bodies *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc){
    llll_format_modifiers(&modifiers, NULL);
    
    if (dadaobj_mousewheel(dadaobj_cast(x), view, pt, modifiers, x_inc, y_inc)) {
        jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
        jbox_redraw((t_jbox *)x);
        return;
    }
}

void bodies_mousedoubleclick(t_bodies *x, t_object *patcherview, t_pt pt, long modifiers) {
/*    t_dadaitem_identifier id = pixel_to_element(x, pt, patcherview, NULL);
	if (modifiers & eCommandKey) {
		if (id.type == DADAITEM_TYPE_BODIES_BODY) {
            bodies_undo_step_push(x, gensym("Delete Star"));
			delete_body(x, id.idx);
        } else if (id.type == DADAITEM_TYPE_BODIES_PARTICLE) {
            bodies_undo_step_push(x, gensym("Delete Planet"));
			delete_particle(x, id.idx);
        } else if (id.type == DADAITEM_TYPE_BODIES_ARROWNOTE) {
            bodies_undo_step_push(x, gensym("Delete Body Note"));
            delete_arrownote(x, id.idx, id.secondary_idx);
        }
        x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADAITEM_TYPE_NONE;
        x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx = -1;
		jbox_redraw((t_jbox *) x);
	} */
}

double get_circular_motion_velocity(t_bodies *x, long body_idx, double dist){
	if (x->law_type == DADA_BODIES_LAW_NEWTON) {
		// standard newton's law: v = sqrt(G*M/r)
		return sqrt(x->G * x->body[body_idx].mass / dist);
    } else if (x->law_type == DADA_BODIES_LAW_NEWTON_OUTSIDE) {
        return (dist > x->body[body_idx].radius) ? sqrt(x->G * x->body[body_idx].mass / dist) : 0;
	} else if (x->n_lexpr && x->n_lexpr2) {
		// custom law: v = sqrt(f * r)
		t_hatom vars[LEXPR_MAX_VARS];
		t_hatom *res;
		t_hatom *res2;
		hatom_setdouble(vars, x->G); 
		hatom_setdouble(vars+1, x->body[body_idx].mass); 
		hatom_setdouble(vars+2, dist);
		hatom_setdouble(vars+3, x->body[body_idx].radius);
		res = lexpr_eval(x->n_lexpr, vars);

		double f = -hatom_getdouble(res);
		hatom_setdouble(vars, f); 
		hatom_setdouble(vars+1, dist); 
		res2 = lexpr_eval(x->n_lexpr2, vars);
		double out = hatom_getdouble(res2);
		sysmem_freeptr(res);
		sysmem_freeptr(res2);
		return out;
	}
	return 0;
}


void force_circular_motion_for_particle(t_bodies *x, long particle_idx, char also_put_to_zero_position){
	long i = particle_idx;
	double dist;
	long body_idx = get_nearest_body_idx(x, x->particle[i].r_it.coord, &dist);
	if (body_idx > -1) {
		// turn motion into circular motion
		if (also_put_to_zero_position) {
			x->particle[i].r_it.coord.x = x->body[body_idx].r_it.coord.x;
			x->particle[i].r_it.coord.y = x->body[body_idx].r_it.coord.y + dist;
		}
		double speed = get_circular_motion_velocity(x, body_idx, dist);
		double angle = delta_coord_to_angle(x, x->body[body_idx].r_it.coord, x->particle[i].r_it.coord);
		angle = PIOVERTWO - angle;
		x->particle[i].speed.x = speed * cos(angle);
		x->particle[i].speed.y = -speed * sin(angle);
		jbox_redraw((t_jbox *) x);
	}
}


void build_popup_bodies_background_menu(t_bodies *x){
	if (x->popup_background)
		jpopupmenu_destroy(x->popup_background);
	
	x->popup_background = jpopupmenu_create(); 
	
    jpopupmenu_additem(x->popup_background, 350, "Add Star", NULL, 0, 0, NULL);
    jpopupmenu_additem(x->popup_background, 351, "Add Planet", NULL, 0, 0, NULL);
    jpopupmenu_addseperator(x->popup_background);
	jpopupmenu_additem(x->popup_background, 191, "No Solo Elements", NULL, 0, 0, NULL);
	jpopupmenu_additem(x->popup_background, 192, "No Muted Elements", NULL, 0, 0, NULL);
	jpopupmenu_additem(x->popup_background, 193, "No Killed Bodies", NULL, 0, 0, NULL);
	jpopupmenu_additem(x->popup_background, 194, "No Solitary Bodies", NULL, 0, 0, NULL);
	jpopupmenu_addseperator(x->popup_background);
	if (x->use_particle_midichannels == 0)
		jpopupmenu_additem(x->popup_background, 205, "Use Planets Midichannels", NULL, 0, 0, NULL);
	else
		jpopupmenu_additem(x->popup_background, 206, "Use Stars Midichannels", NULL, 0, 0, NULL);
	jpopupmenu_addseperator(x->popup_background);
	jpopupmenu_additem(x->popup_background, 207, "Force All Circular Motions", NULL, 0, 0, NULL);
	jpopupmenu_additem(x->popup_background, 208, "Force All Circular Motions And Make Horizontal", NULL, 0, 0, NULL);
	jpopupmenu_addseperator(x->popup_background);
	jpopupmenu_additem(x->popup_background, 300, "Paste", NULL, 0, !clipboard.gathered_syntax, NULL);
	
	jpopupmenu_setfont(x->popup_background, x->popup_main_font);
}

char handle_bodies_background_popup(t_bodies *x, long modifiers, int *chosenelement, t_object *patcherview, t_pt pt){
	int screen_x, screen_y;
	t_pt screen; 
	int chosenelem = 0; 
	long i;
    t_pt center = get_center_pix(dadaobj_cast(x), patcherview, NULL);

	jmouse_getposition_global(&screen_x, &screen_y);
	screen.x = (double)screen_x;
	screen.y = (double)screen_y;
	build_popup_bodies_background_menu(x);
	chosenelem = jpopupmenu_popup(x->popup_background, screen, 0);
	if (chosenelement) *chosenelement = chosenelem;
	
	if (chosenelem == 191){ // no solo
		for (i = 0; i < DADA_BODIES_MAX_BODIES; i++)
			x->body[i].r_it.flags &= ~D_SOLO;
		for (i = 0; i < DADA_BODIES_MAX_PARTICLES; i++)
            x->particle[i].r_it.flags &= ~D_SOLO;
		return 1;
	} else if (chosenelem == 192){ // no mute
		for (i = 0; i < DADA_BODIES_MAX_BODIES; i++)
            x->body[i].r_it.flags &= ~D_MUTE;
		for (i = 0; i < DADA_BODIES_MAX_PARTICLES; i++)
            x->particle[i].r_it.flags &= ~D_MUTE;
		return 1;
	} else if (chosenelem == 193){ // no kill
		for (i = 0; i < DADA_BODIES_MAX_BODIES; i++)
            x->body[i].r_it.flags &= ~D_INACTIVE;
		return 1;
	} else if (chosenelem == 194){ // no solitary
		for (i = 0; i < DADA_BODIES_MAX_BODIES; i++)
            x->body[i].r_it.flags &= ~D_SOLITARY;
		return 1;
	} else if (chosenelem == 205){ 
		x->use_particle_midichannels = 1;
		return 1;
	} else if (chosenelem == 206){ 
		x->use_particle_midichannels = 0;
		return 1;
	} else if (chosenelem == 207){
		for (i = 0; i < x->num_particles; i++)	
			force_circular_motion_for_particle(x, i, false);
		return 1;
	} else if (chosenelem == 208){
		for (i = 0; i < x->num_particles; i++)	
			force_circular_motion_for_particle(x, i, true);
		return 1;
	} else if (chosenelem == 300){
		t_pt coord = pix_to_coord(dadaobj_cast(x), center, pt);
		paste(x, coord);
		return 1;
    } else if (chosenelem == 351){
        bodies_undo_step_push(x, gensym("Add Planet"));
        long part = add_particle(x, pix_to_coord(dadaobj_cast(x), center, pt), build_pt(DADA_BODIES_DEFAULT_X_SPEED, 0), long_to_color(x->num_particles * 2 + 1), x->num_particles + 1);
        if (part >= 0 && x->b_ob.d_ob.m_grid.snap_to_grid)
            snap_coord_to_grid(x, &x->particle[part].r_it.coord);
        return 1;
    } else if (chosenelem == 350){
        bodies_undo_step_push(x, gensym("Add Star"));
        long bod = add_body(x, pix_to_coord(dadaobj_cast(x), center, pt), 0.01, 10, long_to_color(x->num_bodies * 2), x->num_bodies + 1);
        if (bod >= 0 && x->b_ob.d_ob.m_grid.snap_to_grid)
            snap_coord_to_grid(x, &x->body[bod].r_it.coord);
        return 1;
	}
	
    recompute_solo_flag(x);
    
	return -1;
}




void build_popup_body_menu(t_bodies *x, long body_idx){
	long active_midichannel = x->body[body_idx].midichannel;
	
	if (x->popup_body)
		jpopupmenu_destroy(x->popup_body);
	if (x->popup_body_midichannels)
		jpopupmenu_destroy(x->popup_body_midichannels);
	if (x->popup_body_transpose)
		jpopupmenu_destroy(x->popup_body_transpose);

	x->popup_body = jpopupmenu_create(); 
	x->popup_body_midichannels = jpopupmenu_create(); 
	x->popup_body_transpose = jpopupmenu_create(); 
	
	// midichannels (150)
	jpopupmenu_additem(x->popup_body_midichannels, 151, "1", NULL, active_midichannel == 1, 0, NULL);
	jpopupmenu_additem(x->popup_body_midichannels, 152, "2", NULL, active_midichannel == 2, 0, NULL);
	jpopupmenu_additem(x->popup_body_midichannels, 153, "3", NULL, active_midichannel == 3, 0, NULL);
	jpopupmenu_additem(x->popup_body_midichannels, 154, "4", NULL, active_midichannel == 4, 0, NULL);
	jpopupmenu_additem(x->popup_body_midichannels, 155, "5", NULL, active_midichannel == 5, 0, NULL);
	jpopupmenu_additem(x->popup_body_midichannels, 156, "6", NULL, active_midichannel == 6, 0, NULL);
	jpopupmenu_additem(x->popup_body_midichannels, 157, "7", NULL, active_midichannel == 7, 0, NULL);
	jpopupmenu_additem(x->popup_body_midichannels, 158, "8", NULL, active_midichannel == 8, 0, NULL);
	jpopupmenu_additem(x->popup_body_midichannels, 159, "9", NULL, active_midichannel == 9, 0, NULL);
	jpopupmenu_additem(x->popup_body_midichannels, 160, "10", NULL, active_midichannel == 10, 0, NULL);
	jpopupmenu_additem(x->popup_body_midichannels, 161, "11", NULL, active_midichannel == 11, 0, NULL);
	jpopupmenu_additem(x->popup_body_midichannels, 162, "12", NULL, active_midichannel == 12, 0, NULL);
	jpopupmenu_additem(x->popup_body_midichannels, 163, "13", NULL, active_midichannel == 13, 0, NULL);
	jpopupmenu_additem(x->popup_body_midichannels, 164, "14", NULL, active_midichannel == 14, 0, NULL);
	jpopupmenu_additem(x->popup_body_midichannels, 165, "15", NULL, active_midichannel == 15, 0, NULL);
	jpopupmenu_additem(x->popup_body_midichannels, 166, "16", NULL, active_midichannel == 16, 0, NULL);
	
	jpopupmenu_addsubmenu(x->popup_body, "Midichannel", x->popup_body_midichannels, 0);
	
    jpopupmenu_addseperator(x->popup_body);
    jpopupmenu_additem(x->popup_body, 320, "Evenly Distribute Notes", NULL, 0, 0, NULL);
    jpopupmenu_additem(x->popup_body, 321, "Evenly Distribute And Mirror Notes", NULL, 0, 0, NULL);

    // lock/mute (180)
	jpopupmenu_addseperator(x->popup_body);
	if (!(x->body[body_idx].r_it.flags & D_MUTE))
		jpopupmenu_additem(x->popup_body, 183, "Mute", NULL, 0, 0, NULL);
	else
		jpopupmenu_additem(x->popup_body, 184, "Unmute", NULL, 0, 0, NULL);
	if (!(x->body[body_idx].r_it.flags & D_SOLO))
		jpopupmenu_additem(x->popup_body, 185, "Solo", NULL, 0, 0, NULL);
	else
		jpopupmenu_additem(x->popup_body, 186, "Unsolo", NULL, 0, 0, NULL);
	if (!(x->body[body_idx].r_it.flags & D_INACTIVE))
		jpopupmenu_additem(x->popup_body, 187, "Make Inactive", NULL, 0, 0, NULL);
	else
		jpopupmenu_additem(x->popup_body, 188, "Make Active", NULL, 0, 0, NULL);
	if (!(x->body[body_idx].r_it.flags & D_SOLITARY))
		jpopupmenu_additem(x->popup_body, 189, "Make Solitary", NULL, 0, 0, NULL);
	else
		jpopupmenu_additem(x->popup_body, 190, "Make Non-solitary", NULL, 0, 0, NULL);
	jpopupmenu_addseperator(x->popup_body);
	jpopupmenu_additem(x->popup_body, 191, "No Solo Bodies", NULL, 0, 0, NULL);
	jpopupmenu_additem(x->popup_body, 192, "No Muted Bodies", NULL, 0, 0, NULL);
	jpopupmenu_additem(x->popup_body, 193, "No Inactive Bodies", NULL, 0, 0, NULL);
	jpopupmenu_additem(x->popup_body, 194, "No Solitary Bodies", NULL, 0, 0, NULL);
	jpopupmenu_addseperator(x->popup_body);
	jpopupmenu_additem(x->popup_body, 300, "Copy", NULL, 0, 0, NULL);

	
	// transpose (400)
	long i;
	for (i = -12; i <= 12; i++) {
		char thisval[20];
		sprintf(thisval, "%ld cents", i * 100);
		jpopupmenu_additem(x->popup_body_transpose, 412 + i, thisval, NULL, 0, 0, NULL);
	}
	jpopupmenu_addsubmenu(x->popup_body, "Transpose", x->popup_body_transpose, 0);

	
	jpopupmenu_setfont(x->popup_body, x->popup_main_font);
	jpopupmenu_setfont(x->popup_body_midichannels, x->popup_secondary_font);
	jpopupmenu_setfont(x->popup_body_transpose, x->popup_secondary_font);
	
}


char handle_body_popup(t_bodies *x, long body_idx, long modifiers, int *chosenelement){
	int screen_x, screen_y;
	t_pt screen; 
	int chosenelem = 0; 
	
	jmouse_getposition_global(&screen_x, &screen_y);
	screen.x = (double)screen_x;
	screen.y = (double)screen_y;
	build_popup_body_menu(x, body_idx);
	chosenelem = jpopupmenu_popup(x->popup_body, screen, 0);
	if (chosenelement) *chosenelement = chosenelem;
	
	if (chosenelem >= 151 && chosenelem <= 166){ // midichannel
		x->body[body_idx].midichannel = chosenelem - 150;
		return 1;
	} else if (chosenelem == 183){ // mute
		x->body[body_idx].r_it.flags |= D_MUTE;
		return 1;
	} else if (chosenelem == 184){ // unmute
        x->body[body_idx].r_it.flags &= ~D_MUTE;
		return 1;
	} else if (chosenelem == 185){
        x->body[body_idx].r_it.flags |= D_SOLO;
		return 1;
	} else if (chosenelem == 186){
        x->body[body_idx].r_it.flags &= ~D_SOLO;
		return 1;
	} else if (chosenelem == 187){
        x->body[body_idx].r_it.flags |= D_INACTIVE;
		return 1;
	} else if (chosenelem == 188){
        x->body[body_idx].r_it.flags &= ~D_INACTIVE;
		return 1;
	} else if (chosenelem == 189){
        x->body[body_idx].r_it.flags |= D_SOLITARY;
		return 1;
	} else if (chosenelem == 190){
        x->body[body_idx].r_it.flags &= ~D_SOLITARY;
		return 1;
	} else if (chosenelem == 191){ // no solo
		long i;
		for (i = 0; i < DADA_BODIES_MAX_BODIES; i++)
            x->body[i].r_it.flags &= ~D_SOLO;
		return 1;
	} else if (chosenelem == 192){ // no mute
		long i;
		for (i = 0; i < DADA_BODIES_MAX_BODIES; i++)
            x->body[i].r_it.flags &= ~D_MUTE;
		return 1;
	} else if (chosenelem == 193){ // no killed
		long i;
		for (i = 0; i < DADA_BODIES_MAX_BODIES; i++)
            x->body[i].r_it.flags &= ~D_INACTIVE;
		return 1;
	} else if (chosenelem == 194){ // no solitary
		long i;
		for (i = 0; i < DADA_BODIES_MAX_BODIES; i++)
            x->body[i].r_it.flags &= ~D_SOLITARY;
		return 1;
	} else if (chosenelem == 300){ // copy
		copy_body(x, body_idx);
		return 0;
	} else if (chosenelem >= 400 && chosenelem <= 425){ // transpose
		transpose_body_arrows(x, body_idx, (chosenelem-412)*100);
		return 0;
    } else if (chosenelem == 320) {
        bodies_undo_step_push(x, gensym("Uniformly Distribute Body Notes"));
        uniformly_distribute_arrownotes(x, body_idx, false);
        jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
        return 0;
    } else if (chosenelem == 321) {
        bodies_undo_step_push(x, gensym("Uniformly Distribute Body Notes And Mirrors"));
        uniformly_distribute_arrownotes(x, body_idx, true);
        jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
        return 0;
	}

	return -1;
}


void build_popup_particle_menu(t_bodies *x, long particle_idx){
	long active_midichannel = x->particle[particle_idx].midichannel;
	
	if (x->popup_particle)
		jpopupmenu_destroy(x->popup_particle);
	if (x->popup_particle_midichannels)
		jpopupmenu_destroy(x->popup_particle_midichannels);
	if (x->popup_particle_forceperiod)
		jpopupmenu_destroy(x->popup_particle_forceperiod);
	
	x->popup_particle = jpopupmenu_create(); 
	x->popup_particle_midichannels = jpopupmenu_create(); 
	x->popup_particle_forceperiod = jpopupmenu_create(); 
	
	// midichannels (150)
	jpopupmenu_additem(x->popup_particle_midichannels, 151, "1", NULL, active_midichannel == 1, 0, NULL);
	jpopupmenu_additem(x->popup_particle_midichannels, 152, "2", NULL, active_midichannel == 2, 0, NULL);
	jpopupmenu_additem(x->popup_particle_midichannels, 153, "3", NULL, active_midichannel == 3, 0, NULL);
	jpopupmenu_additem(x->popup_particle_midichannels, 154, "4", NULL, active_midichannel == 4, 0, NULL);
	jpopupmenu_additem(x->popup_particle_midichannels, 155, "5", NULL, active_midichannel == 5, 0, NULL);
	jpopupmenu_additem(x->popup_particle_midichannels, 156, "6", NULL, active_midichannel == 6, 0, NULL);
	jpopupmenu_additem(x->popup_particle_midichannels, 157, "7", NULL, active_midichannel == 7, 0, NULL);
	jpopupmenu_additem(x->popup_particle_midichannels, 158, "8", NULL, active_midichannel == 8, 0, NULL);
	jpopupmenu_additem(x->popup_particle_midichannels, 159, "9", NULL, active_midichannel == 9, 0, NULL);
	jpopupmenu_additem(x->popup_particle_midichannels, 160, "10", NULL, active_midichannel == 10, 0, NULL);
	jpopupmenu_additem(x->popup_particle_midichannels, 161, "11", NULL, active_midichannel == 11, 0, NULL);
	jpopupmenu_additem(x->popup_particle_midichannels, 162, "12", NULL, active_midichannel == 12, 0, NULL);
	jpopupmenu_additem(x->popup_particle_midichannels, 163, "13", NULL, active_midichannel == 13, 0, NULL);
	jpopupmenu_additem(x->popup_particle_midichannels, 164, "14", NULL, active_midichannel == 14, 0, NULL);
	jpopupmenu_additem(x->popup_particle_midichannels, 165, "15", NULL, active_midichannel == 15, 0, NULL);
	jpopupmenu_additem(x->popup_particle_midichannels, 166, "16", NULL, active_midichannel == 16, 0, NULL);
	
	jpopupmenu_addsubmenu(x->popup_particle, "Midichannel", x->popup_particle_midichannels, 0);
	
	// lock/mute (180)
	jpopupmenu_addseperator(x->popup_particle);
	if (!(x->particle[particle_idx].r_it.flags & D_MUTE))
		jpopupmenu_additem(x->popup_particle, 183, "Mute", NULL, 0, 0, NULL);
	else
		jpopupmenu_additem(x->popup_particle, 184, "Unmute", NULL, 0, 0, NULL);
	if (!(x->particle[particle_idx].r_it.flags & D_SOLO))
		jpopupmenu_additem(x->popup_particle, 185, "Solo", NULL, 0, 0, NULL);
	else
		jpopupmenu_additem(x->popup_particle, 186, "Unsolo", NULL, 0, 0, NULL);
	jpopupmenu_addseperator(x->popup_particle);
	jpopupmenu_additem(x->popup_particle, 191, "No Solo Planets", NULL, 0, 0, NULL);
	jpopupmenu_additem(x->popup_particle, 192, "No Muted Planets", NULL, 0, 0, NULL);
	jpopupmenu_addseperator(x->popup_particle);
	jpopupmenu_additem(x->popup_particle, 200, "Force Circular Motion", NULL, 0, 0, NULL);
	jpopupmenu_additem(x->popup_particle, 201, "Force Circular Motion And Make Horizontal", NULL, 0, 0, NULL);
	
	
	jpopupmenu_additem(x->popup_particle_forceperiod, 247, "0.25 sec", NULL, 0, 0, NULL);
	jpopupmenu_additem(x->popup_particle_forceperiod, 248, "0.5 sec", NULL, 0, 0, NULL);
	jpopupmenu_additem(x->popup_particle_forceperiod, 249, "0.75 sec", NULL, 0, 0, NULL);
	jpopupmenu_additem(x->popup_particle_forceperiod, 250, "1 sec", NULL, 0, 0, NULL);
	jpopupmenu_additem(x->popup_particle_forceperiod, 251, "1.5 sec", NULL, 0, 0, NULL);
	
	long i;
	for (i = 2; i < 20; i++){
		// midichannels (150)
		char text[20];
		sprintf(text, "%ld sec", i);
		jpopupmenu_additem(x->popup_particle_forceperiod, 250+i, text, NULL, 0, 0, NULL);
		
	}
	jpopupmenu_addsubmenu(x->popup_particle, "Force Period", x->popup_particle_forceperiod, 0);
	
	jpopupmenu_setfont(x->popup_particle, x->popup_main_font);
	jpopupmenu_setfont(x->popup_particle_midichannels, x->popup_secondary_font);
	jpopupmenu_setfont(x->popup_particle_forceperiod, x->popup_secondary_font);
	
}



char handle_particle_popup(t_bodies *x, long particle_idx, long modifiers, int *chosenelement){
	int screen_x, screen_y;
	t_pt screen; 
	int chosenelem = 0; 
	
	jmouse_getposition_global(&screen_x, &screen_y);
	screen.x = (double)screen_x;
	screen.y = (double)screen_y;
	build_popup_particle_menu(x, particle_idx);
	chosenelem = jpopupmenu_popup(x->popup_particle, screen, 0);
	if (chosenelement) *chosenelement = chosenelem;
	
	if (chosenelem >= 151 && chosenelem <= 166){ // midichannel
		x->particle[particle_idx].midichannel = chosenelem - 150;
		return 1;
	} else if (chosenelem == 183){ // mute
		x->particle[particle_idx].r_it.flags |= D_MUTE;
		return 1;
	} else if (chosenelem == 184){ // unmute
        x->particle[particle_idx].r_it.flags &= ~D_MUTE;
		return 1;
	} else if (chosenelem == 185){
        x->particle[particle_idx].r_it.flags |= D_SOLO;
		return 1;
	} else if (chosenelem == 186){
        x->particle[particle_idx].r_it.flags &= ~D_SOLO;
		return 1;
	} else if (chosenelem == 191){ // no solo
		long i;
		for (i = 0; i < DADA_BODIES_MAX_BODIES; i++)
            x->particle[i].r_it.flags &= ~D_SOLO;
		return 1;
	} else if (chosenelem == 192){ // no mute
		long i;
		for (i = 0; i < DADA_BODIES_MAX_BODIES; i++)
            x->particle[i].r_it.flags &= ~D_MUTE;
		return 1;
	} else if (chosenelem == 200){
        bodies_undo_step_push(x, gensym("Force Circuluar Motion"));
		force_circular_motion_for_particle(x, particle_idx, false);
		return 1;
	} else if (chosenelem == 201){
        bodies_undo_step_push(x, gensym("Force Circuluar Motion And Make Horizontal"));
		force_circular_motion_for_particle(x, particle_idx, true);
		return 1;
	} else if (chosenelem >= 247 && chosenelem <= 270){
		double period;
		if (chosenelem == 247)
			period = 0.25;
		else if (chosenelem == 248)
			period = 0.5;
		else if (chosenelem == 249)
			period = 0.75;
		else if (chosenelem == 250)
			period = 1.;
		else if (chosenelem == 251)
			period = 1.5;
		else
			period = chosenelem - 250;
        bodies_undo_step_push(x, gensym("Force Period"));
		force_particle_period(x, particle_idx, period*1000.);
		return 1;
	}
    
    recompute_solo_flag(x);
	
	return -1;
}

void bodies_mousedown(t_bodies *x, t_object *patcherview, t_pt pt, long modifiers)
{
	char need_popup = modifiers & eRightButton;

    if (dadaobj_mousedown(dadaobj_cast(x), patcherview, pt, modifiers))
        return;

    
    x->b_ob.d_ob.m_interface.mousedown_item_identifier = pixel_to_element(x, pt, patcherview, NULL);
    long i = x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx;
    char elem_type = x->b_ob.d_ob.m_interface.mousedown_item_identifier.type;
    
	// popup menu?
	if (need_popup) {
		if (elem_type == DADAITEM_TYPE_BODIES_BODY) {
			// tries to find if one of the common commands has been selected, if not we use <chosenelem>
			int chosenelem = 0; 
			char res = handle_body_popup(x, i, modifiers, &chosenelem);
			
			if (res >= 0){ 
				recompute_solo_flag(x);
				changed_bang(x, res);
				jbox_redraw((t_jbox *) x);
			}
			jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
			return; 
		} else if (elem_type == DADAITEM_TYPE_BODIES_PARTICLE) {
			// tries to find if one of the common commands has been selected, if not we use <chosenelem>
			int chosenelem = 0; 
			char res = handle_particle_popup(x, i, modifiers, &chosenelem);
			
			if (res >= 0){ 
				recompute_solo_flag(x);
				changed_bang(x, res);
				jbox_redraw((t_jbox *) x);
			}
			jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
			return; 
		} else if (elem_type == DADAITEM_TYPE_NONE) {
			int chosenelem = 0; 
			char res = handle_bodies_background_popup(x, modifiers, &chosenelem, patcherview, pt);
			
			if (res >= 0){ 
				recompute_solo_flag(x);
				changed_bang(x, res);
				jbox_redraw((t_jbox *) x);
			}
			jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
			return; 
		}
	}
	
    bodies_output_notification(x, &x->b_ob.d_ob.m_interface.mousedown_item_identifier, gensym("click"));

	if (modifiers & eCommandKey){
		if (i == -1){
			t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), patcherview, pt);
			if (modifiers & eAltKey) {
                bodies_undo_step_push(x, gensym("Add Planet"));
				x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx = add_particle(x, coord, build_pt(DADA_BODIES_DEFAULT_X_SPEED, 0), long_to_color(x->num_particles * 2 + 1), x->num_particles + 1);
				x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADAITEM_TYPE_BODIES_PARTICLE;
				if (x->b_ob.d_ob.m_grid.snap_to_grid)
					snap_coord_to_grid(x, &x->particle[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx].r_it.coord);
			} else {
                bodies_undo_step_push(x, gensym("Add Star"));
				x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx = add_body(x, coord, 0.01, 10, long_to_color(x->num_bodies * 2), x->num_bodies + 1);
				x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADAITEM_TYPE_BODIES_BODY;
				if (x->b_ob.d_ob.m_grid.snap_to_grid)
					snap_coord_to_grid(x, &x->body[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx].r_it.coord);
			}
        } else {
            if (elem_type == DADAITEM_TYPE_BODIES_BODY) {
                bodies_undo_step_push(x, gensym("Delete Star"));
                delete_body(x, i);
            } else if (elem_type == DADAITEM_TYPE_BODIES_PARTICLE) {
                bodies_undo_step_push(x, gensym("Delete Planet"));
                delete_particle(x, i);
            } else if (elem_type == DADAITEM_TYPE_BODIES_ARROWNOTE) {
                bodies_undo_step_push(x, gensym("Delete Star Note"));
                delete_arrownote(x, i, x->b_ob.d_ob.m_interface.mousedown_item_identifier.secondary_idx);
            }
        }
		jbox_redraw((t_jbox *) x);
	} else if (modifiers & eShiftKey && !(modifiers & eAltKey) && !(modifiers & eControlKey) && i > -1 && elem_type == DADAITEM_TYPE_BODIES_BODY){
        bodies_undo_step_push(x, gensym("Add Star Note"));
		t_pt center = coord_to_pix_from_view(dadaobj_cast(x), patcherview, x->body[i].r_it.coord);
		double alpha = pt_to_angle(x, center, pt);
		add_arrownote(x, i, alpha, 6000);
	} else {
//		x->dragged_index = pt_to_elem_idx(x, patcherview, pt, &x->dragged_elem_type, &x->dragged_arrow_idx);
	}
}

void bodies_mouseup(t_bodies *x, t_object *patcherview, t_pt pt, long modifiers)
{
    t_dadaitem_identifier id = x->b_ob.d_ob.m_interface.mousedown_item_identifier;
    llll_format_modifiers(&modifiers, NULL);

    if (dadaobj_mouseup(dadaobj_cast(x), patcherview, pt, modifiers))
        return;
    
	if (x->b_ob.d_ob.m_grid.snap_to_grid) {
		if (id.type == DADAITEM_TYPE_BODIES_PARTICLE && id.idx > -1)
			snap_coord_to_grid(x, &x->particle[id.idx].r_it.coord);
		else if (id.type == DADAITEM_TYPE_BODIES_BODY && id.idx > -1){
			snap_coord_to_grid(x, &x->body[id.idx].r_it.coord);
			compute_label_for_all_arrownotes(x, id.idx);
			jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
		}
	}
	jbox_redraw((t_jbox *)x);
}


long bodies_keyup(t_bodies *x, t_object *patcherview, long keycode, long modifiers, long textcharacter){
    
    llll_format_modifiers(&modifiers, &keycode);
    
    if (dadaobj_keyup(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
        return 1;
    
    return 0;
}

long bodies_key(t_bodies *x, t_object *patcherview, long keycode, long modifiers, long textcharacter)
{

    
    llll_format_modifiers(&modifiers, &keycode);
    
    if (dadaobj_key(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter) || keycode == JKEY_ESC) {
        jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
        jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
        jbox_redraw((t_jbox *) x);
        return 1;
    }
    

    if (keycode == JKEY_SPACEBAR) {
		bodies_int(x, !x->running);
		return 1;
    } else if (keycode == JKEY_TAB) {
        t_rect rect;
        jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
        bodies_autozoom(x, patcherview, &rect);
        return 1;
	}
	return 0;
}

double get_distance_to_force_period(t_bodies *x, long body_idx, double period)
{
	// only standard newton's law: r^3/2 = period * sqrt(GM)/2 pi
	return pow(period*sqrt(x->G * x->body[body_idx].mass)/TWOPI, 2./3.);
}

void force_particle_period(t_bodies *x, long particle_idx, double period){
	double dist;
	long body_idx = get_nearest_body_idx(x, x->particle[particle_idx].r_it.coord, &dist);
	
	if (body_idx > -1) {
		// T = 2 pi r^(3/2) / sqrt(G * M)
		dist = get_distance_to_force_period(x, body_idx, period/1000.);
		x->particle[particle_idx].r_it.coord.x = x->body[body_idx].r_it.coord.x;
		x->particle[particle_idx].r_it.coord.y = x->body[body_idx].r_it.coord.y + dist;
		
		double vel = get_circular_motion_velocity(x, body_idx, dist);
		x->particle[particle_idx].speed.x = vel;
		x->particle[particle_idx].speed.y = 0;
		jbox_redraw((t_jbox *) x);
	}
}

void bodies_forceperiod(t_bodies *x, t_symbol *s, long argc, t_atom *argv){
	// force the period of a given 
	if (argc >= 2) {
		long i = atom_getlong(argv) - 1;
		double period = atom_getfloat(argv + 1);

		if (i >= 0 && i < DADA_BODIES_MAX_PARTICLES) {
			force_particle_period(x, i, period);
			changed_bang(x, 1);
		}
	}
}

void bodies_forcecircular(t_bodies *x, t_symbol *s, long argc, t_atom *argv){
    // force the period of a given
    if (argc >= 1) {
        long i = atom_getlong(argv) - 1;
        long put_to_zero = (argc > 1);
        
        if (i >= 0 && i < DADA_BODIES_MAX_PARTICLES) {
            force_circular_motion_for_particle(x, i, put_to_zero);
            changed_bang(x, 1);
        }
    }
}

