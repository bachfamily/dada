/**
	@file
	dada.platform.c
	
	@name
	dada.platform
	
	@realname 
	dada.platform

	@type
	object
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
	2D platform games interface
	
	@description
	Implements an scriptable and interactive interface for platform games
	
	@discussion
 
	@category
	dada, dada interfaces, dada rule-based systems

	@keywords
	platform, game, videogame, video, sprite, coin, block
	
	@seealso
	dada.kaleido
	
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
#include "dada.notation.h"
#include "dada.object.h"
#include <stdlib.h>
#ifdef WIN_VERSION
#include <windows.h>
HINSTANCE hinst;
#endif


#define DADA_PLATFORM_LEVEL_HAS_INSPECTOR

#define DADA_PLATFORM_MAX_SPRITES 200
#define	DADA_PLATFORM_MAX_PROTOTYPES 50
#define DADA_MAX_SLIDES_PER_SPRITE 10
#define DADA_PLATFORM_MAX_HEROES 1
#define DADA_PLATFORM_MAX_GAMECHARS 200
#define DADA_PLATFORM_MAX_BLOCKS 2000
#define DADA_PLATFORM_MAX_COINS 1000
#define DADA_PLATFORM_MAX_PORTALS 50

#define DADA_PLATFORM_NUMBERS_HOLD_TIME 100
#define DADA_PLATFORM_NUMBERS_FADE_TIME 2000
#define DADA_PLATFORM_NUMBERS_FADE_STEPS 40
#define DADA_PLATFORM_NUMBERS_FADE_STEP_ALPHA (1. / DADA_PLATFORM_NUMBERS_FADE_STEPS)
#define DADA_PLATFORM_NUMBERS_FADE_STEP_TIME (DADA_PLATFORM_NUMBERS_FADE_TIME / DADA_PLATFORM_NUMBERS_FADE_STEPS)


#define DADA_PLATFORM_CURTAIN_MOVE_STEP_AMOUNT 0.5
#define DADA_PLATFORM_CURTAIN_MOVE_STEP_TIME 50

#define DADA_PLATFORM_INTRO_TIME 2000

#define DADA_PLATFORM_BLOCKS_BUMP_SHIFT 0.1
#define DADA_PLATFORM_BLOCKS_BUMP_TIME 100
#define DADA_PLATFORM_BLOCKS_BREAK_TIME 600
#define DADA_PLATFORM_BLOCKS_BOUNCE_SPEED 3
#define DADA_PLATFORM_BLOCKS_BUMP_GAMECHAR_TOLERANCE 0.1

#define DADA_PLATFORM_GAMECHAR_JUMP_DEFAULT 5
#define DADA_PLATFORM_GAMECHAR_JUMP_FOR_KILLING 10

#define DADA_PLATFORM_PLAYROLL_OUTLET 2
#define DADA_PLATFORM_NOTIFICATION_OUTLET 1

#define DADA_NODES_NOTEPOPUP_WIDTH 50
#define DADA_NODES_NOTEPOPUP_HEIGHT 70

#define DADA_PLATFORM_DEFAULT_GRAVITY 15.


enum {
    DADA_PLATFORM_INSTRUCTION_RV_NONE = 0,
    DADA_PLATFORM_INSTRUCTION_RV_DONTDIE = 1
};

typedef t_uint64 t_platform_bitfield;		///< A bitfield with each bit corresponding to a pitch node


////////////////////////// structures


typedef struct _platform_sprite_manager
{
	long					num_sprites;
	t_dada_sprite		*sprite;
} t_platform_sprite_manager;



typedef struct _platform_prototype
{
	t_symbol	*name;
    long        type;
	t_llll		*attr;
} t_platform_prototype;


typedef struct _platform_prototype_manager
{
	long					num_prototypes;
	t_platform_prototype	prototypes[100];
} t_platform_prototype_manager;


enum {
    DADA_PLATFORM_PLAYSTATE_STANDARD,
    DADA_PLATFORM_PLAYSTATE_DYING,
    DADA_PLATFORM_PLAYSTATE_LEVELINTRO_PRE,
    DADA_PLATFORM_PLAYSTATE_LEVELINTRO,
    DADA_PLATFORM_PLAYSTATE_LEVELINTRO_POST,
    DADA_PLATFORM_PLAYSTATE_END_WIN_PRE,
    DADA_PLATFORM_PLAYSTATE_END_WIN,
    DADA_PLATFORM_PLAYSTATE_END_GAMEOVER_PRE,
    DADA_PLATFORM_PLAYSTATE_END_GAMEOVER,
};

enum {
    DADA_PLATFORM_PLAYMODE_CANT_PLAY = 0,
    DADA_PLATFORM_PLAYMODE_STANDARD = 1,
    DADA_PLATFORM_PLAYMODE_CANT_STOP = 2,
};


typedef struct _platform_loading_options
{
    t_symbol *goto_portal;
    char intro;
    char resettime;
    char keephero;
    long herovp;
    long heropoints;
} t_platform_loading_options;


typedef struct _levelinfo
{
    t_dadaitem      r_it;
    
    t_symbol        *background_sprite;
    t_symbol        *levelname;
    t_atom          maxtime;
    double			gravity;
    char            has_intro;
    double          level_height;
    double          level_width;
    double          ground_friction;
    double          air_friction;
    t_symbol        *hero_name;
    t_jrgba			j_textcolor;
} t_levelinfo;



typedef struct _dada_platform_resources
{
    t_jsurface *surface_gamechar;
    t_jsurface *surface_block;
    t_jsurface *surface_coin;
    t_jsurface *surface_portal;
    t_jsurface *surface_level;
} t_dada_platform_resources;





typedef struct _platform
{
	t_dadaobj_jbox		b_ob; // root object
	
	// elements
    t_llll              *blocks;
    t_llll              *gamechars;
    t_llll              *coins;
    t_llll              *portals;
    
    t_llll              *breakingblocks;
    
    t_symbol        *fontname;
    
	t_platform_sprite_manager		sprite_manager;
	t_platform_prototype_manager	prototype_manager;
    t_dada_sprite	*background;

    t_levelinfo     m_level;    /// level information
    
	// play
	double			global_time;
    long            play_state;
    double          curtain;
    
    // display
	char			show_hero;
	char			show_blocks;
	char			show_coins;
	char			show_legend_vp;
	char			show_legend_points;
	char			show_legend_hero;
    char			show_legend_title;
    char			show_legend_time;

    // characters
	long			hero_ID;
    t_dada_gamechar *hero;
    t_dada_gamechar *curr_killer;
    
    // behavior
    char            edit_mode;
    char            play_mode;
    double			die_y_line;				// y value under which we consider the character dead
	char			only_check_gamechar_collisions_for_user_gamechars;
	char			autoscroll;
    char			autozoom;
    char            save_fixed_states_only;
    
    t_llll          *fixed_state; //state before playing
	
	// notifications
	char			notify_coins;
	char			notify_blocks;
    char			notify_portals;
    char			notify_gamechars;
	char			notify_gamechar_pos;
    char			notify_usercontrol_actions;

	// display
	t_jrgba			j_selectioncolor;
	double			legend_font_size;
	t_rect			displayed_coord;		///< Displayed coordinates in main view
	t_llll			*floattext_to_be_displayed;
	double			floattext_font_size;

	// preset fields
	t_atom		*preset_av;		
	long		preset_ac;		

	// utilities
	char			firsttime;
	char			itsme;
	char			creating_new_obj;
	
	long			n_in;   // space for the inlet number used by all the proxies
    void			*n_proxy1;
	
	char			break_after_notification;
    t_platform_loading_options        goto_options;
    
	// outlets are declared in the dadaobj->llllobj structure, at the beginning
} t_platform;




///////////////////////// function prototypes
//// standard set
void *platform_new(t_symbol *s, long argc, t_atom *argv);
void platform_free(t_platform *x);
void platform_assist(t_platform *x, void *b, long m, long a, char *s);

//void platform_getdrawparams(t_platform *x, t_object *patcherview, t_jboxdrawparams *params);
void platform_paint(t_platform *x, t_object *view);
void platform_paint_ext(t_platform *x, t_object *view, t_dada_force_graphics *force_graphics);


void platform_int(t_platform *x, t_atom_long num);
void platform_float(t_platform *x, double num);
void platform_anything(t_platform *x, t_symbol *msg, long ac, t_atom *av);
void platform_bang(t_platform *x);


// get/set status
void platform_set_state(t_platform *x, t_llll *state);
t_llll *platform_get_state_ext(t_platform *x, char get_levelinfo, char get_sprites, char get_prototypes, char get_heroes, char get_blocks, char get_coins, char get_portals);
t_llll *platform_get_state(t_platform *x);

t_llll *platform_get_blocks(t_platform *x);
t_llll *platform_get_coins(t_platform *x);
void platform_set_blocks(t_platform *x, t_llll *blocks);
void platform_set_coins(t_platform *x, t_llll *coins);

void platform_clear_levelinfo(t_platform *x, long flags);
void platform_clear_prototypes(t_platform *x, long flags);
void platform_clear_sprites(t_platform *x, long flags);
void platform_clear_gamechars(t_platform *x, long flags);
void platform_clear_blocks(t_platform *x, long flags);
void platform_clear_coins(t_platform *x, long flags);
void platform_clear_portals(t_platform *x, long flags);
void platform_clear(t_platform *x, char clear_levelinfo, char clear_sprites, char clear_prototypes, char clear_gamechars, char clear_blocks, char clear_coins, char clear_portals, long flags);

void platform_check_autozoom(t_platform *x);

// interface
t_dadaitem *platform_pixel_to_dadaitem(t_dadaobj *r_ob, t_pt pt, t_object *view, long modifiers, t_pt *coordinates, double selection_pad, t_dadaitem_identifier *identifier);
void platform_focusgained(t_platform *x, t_object *patcherview);
void platform_focuslost(t_platform *x, t_object *patcherview);
void platform_mousedown(t_platform *x, t_object *patcherview, t_pt pt, long modifiers);
void platform_mousemove(t_platform *x, t_object *patcherview, t_pt pt, long modifiers);
void platform_mouseup(t_platform *x, t_object *patcherview, t_pt pt, long modifiers);
void platform_mousedrag(t_platform *x, t_object *patcherview, t_pt pt, long modifiers);
long platform_key(t_platform *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
long platform_keyup(t_platform *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
void platform_mousewheel(t_platform *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc);

void platform_mouseenter(t_platform *x, t_object *patcherview, t_pt pt, long modifiers);
void platform_mouseleave(t_platform *x, t_object *patcherview, t_pt pt, long modifiers);

t_max_err platform_notify(t_platform *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void platform_jsave(t_platform *x, t_dictionary *d);
void platform_preset(t_platform *x);
void platform_begin_preset(t_platform *x, t_symbol *s, long argc, t_atom *argv);
void platform_restore_preset(t_platform *x, t_symbol *s, long argc, t_atom *argv);
void platform_end_preset(t_platform *x);

void platform_undo_step_push(t_platform *x, t_symbol *operation);
void platform_undo_postprocess(t_platform *x);
void platform_undo_postprocess_levelheight(t_bach_inspector_manager *man, void *elem, void *attr);

void platform_restart(t_platform *x, long vp);

void postprocess_blocks(t_platform *x);
void postprocess_coins(t_platform *x);
void postprocess_gamechars(t_platform *x);


void process_change(t_platform *x);
double get_pitch_at_coord(t_platform *x, t_pt coord, double *velocity);

// sequencing
void platform_stop(t_platform *x, t_symbol *s, long argc, t_atom *argv);
void platform_play(t_platform *x, t_symbol *s, long argc, t_atom *argv);
void platform_resume(t_platform *x, t_symbol *s, long argc, t_atom *argv);
void platform_task(t_platform *x);
long platform_oksize(t_platform *x, t_rect *newrect);
void platform_clock(t_platform *x, t_symbol *s);
void platform_stop_do(t_platform *x);
void platform_play_do(t_platform *x, long start_hero_vp);
void platform_resume_do(t_platform *x);

void platform_sort_blocks(t_platform *x);
void platform_sort_coins(t_platform *x);
void platform_sort_portals(t_platform *x);
void platform_check_all_block_collisions(t_platform *x);


void platform_break_block(t_platform *x, t_dada_gamechar *gamechar, t_dada_block *block);
void platform_bump_block(t_platform *x, t_dada_gamechar *gamechar, t_dada_block *block, long direction);
void platform_hit_block(t_platform *x, t_dada_gamechar *gamechar, t_dada_block *block, long direction);
void platform_take_coin(t_platform *x, t_dada_gamechar *gamechar, t_dada_coin *coin);
void platform_take_points_from_block(t_platform *x, t_dada_gamechar *gamechar, t_dada_block *block, long points, long vp);

t_dada_gamechar *platform_get_hero(t_platform *x);

void platform_paint_sprite(t_platform *x, t_jgraphics *g, t_dada_sprite *sprite, t_rect source, t_rect dest, char direction, char invincibility = false);

t_llll *platform_symbol_to_dadaitems(t_platform *x, t_symbol *name, t_dadaitem *subject);
t_llll *platform_symbol_to_gamechars(t_platform *x, t_symbol *name, t_dadaitem *subject);
t_dadaitem *platform_symbol_to_single_dadaitem(t_platform *x, t_symbol *name, t_dadaitem *subject);
t_dada_gamechar *platform_symbol_to_single_gamechar(t_platform *x, t_symbol *name, t_dadaitem *subject);
t_dada_portal *platform_symbol_to_single_portal(t_platform *x, t_symbol *name, t_dadaitem *subject);

char platform_is_dadaitem_in_screen(t_platform *x, t_dadaitem *item, double pad);
long platform_gamechar_die(t_platform *x, t_dada_gamechar *gamechar, t_dada_gamechar *killer, char forced_because_of_time = false);
long platform_gamechar_get_default_movement_state(t_platform *x, t_dada_gamechar *gamechar);

void platform_portal_enter(t_platform *x, t_dada_gamechar *gamechar, t_dada_portal *portal, long direction);
void platform_portal_exit(t_platform *x, t_dada_gamechar *gamechar, t_dada_portal *portal);

void platform_gameover(t_platform *x);
void platform_win(t_platform *x);

void load_default_goto_options(t_platform *x);

t_rect gamechar_get_physics_rect_boundingbox(t_platform *x, t_dada_gamechar *gamechar);
long parse_instructions(t_platform *x, t_llll *instructions, t_dadaitem *subject);
long parse_instructions_char(t_platform *x, char *instructions, t_dadaitem *subject);

void send_notification(t_platform *x, t_llll *ll);
void send_notification_symbol(t_platform *x, t_symbol *s);
void send_notification_for_action(t_platform *x, t_dadaitem *subject, t_symbol *action, t_dadaitem *object, t_symbol *spec);


void remove_subllll_with_routers(t_llll *ll, long num_routers, t_symbol **router);
void platform_iar(t_platform *x);
void load_resources(t_dada_platform_resources *resources, void *moduleRef);
void free_resources(t_dada_platform_resources *resources);
t_jsurface *platform_inspector_get_icon_surface_fn(t_object *r_ob, t_bach_inspector_manager *man, void *obj, long elem_type);


///////////////////////// utility functions

void process_change(t_platform *x)
{
	jbox_redraw((t_jbox *)x);
}



void send_notification(t_platform *x, t_llll *ll)
{
    x->break_after_notification = 0;
    llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, DADA_PLATFORM_NOTIFICATION_OUTLET, ll);
}

void send_notification_symbol(t_platform *x, t_symbol *s)
{
    t_llll *ll = llll_get();
    llll_appendsym(ll, s);
    send_notification(x, ll);
    llll_free(ll);
}

t_symbol *itemtype_to_sym(long type)
{
    switch (type) {
        case DADAITEM_TYPE_BLOCK:
            return gensym("block");
            break;

        case DADAITEM_TYPE_COIN:
            return gensym("coin");
            break;

        case DADAITEM_TYPE_GAMECHAR:
            return gensym("gamechar");
            break;

        case DADAITEM_TYPE_PORTAL:
            return gensym("portal");
            break;

        case DADAITEM_TYPE_LEVEL:
            return gensym("levelinfo");
            break;

        default:
            return _llllobj_sym_none;
            break;
    }
}

long itemsym_to_type(t_symbol *sym)
{
    if (sym == gensym("block"))
        return DADAITEM_TYPE_BLOCK;

    if (sym == gensym("coin"))
        return DADAITEM_TYPE_COIN;

    if (sym == gensym("gamechar"))
        return DADAITEM_TYPE_GAMECHAR;

    if (sym == gensym("portal"))
        return DADAITEM_TYPE_PORTAL;

    if (sym == gensym("levelinfo"))
        return DADAITEM_TYPE_LEVEL;
    
    return DADAITEM_TYPE_NONE;
}

void send_notification_for_action(t_platform *x, t_dadaitem *subject, t_symbol *action, t_dadaitem *object, t_symbol *spec)
{
    t_llll *notify_ll = llll_get();
    llll_appendsym(notify_ll, itemtype_to_sym(subject->type));
    llll_appendsym(notify_ll, subject->name);
    llll_appendsym(notify_ll, action);
    if (object && object->type != DADAITEM_TYPE_NONE) {
        llll_appendsym(notify_ll, itemtype_to_sym(object->type));
        llll_appendsym(notify_ll, object->name);
    }
    send_notification(x, notify_ll);
	llll_free(notify_ll);
}


void send_notification_for_action_symobj(t_platform *x, t_dadaitem *subject, t_symbol *action, t_symbol *object_adj, t_symbol *object)
{
    t_llll *notify_ll = llll_get();
    llll_appendsym(notify_ll, itemtype_to_sym(subject->type));
    llll_appendsym(notify_ll, subject->name);
    llll_appendsym(notify_ll, action);
    if (object_adj)
        llll_appendsym(notify_ll, object_adj);
    if (object)
        llll_appendsym(notify_ll, object);
    send_notification(x, notify_ll);
    llll_free(notify_ll);
}

void send_notification_for_usercontrol(t_platform *x, t_dadaitem *subject, t_symbol *action, t_symbol *spec)
{
    t_llll *notify_ll = llll_get();
    llll_appendsym(notify_ll, gensym("usercontrol"));
    llll_appendsym(notify_ll, itemtype_to_sym(subject->type), 0, WHITENULL_llll);
    llll_appendsym(notify_ll, subject->name, 0, WHITENULL_llll);
    llll_appendsym(notify_ll, action, 0, WHITENULL_llll);
    if (spec)
        llll_appendsym(notify_ll, spec, 0, WHITENULL_llll);
    send_notification(x, notify_ll);
    llll_free(notify_ll);
}


void play_music(t_platform *x, t_llll *music)
{
    t_llll *ll = llll_clone(music);
    if (ll) {
        llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, DADA_PLATFORM_PLAYROLL_OUTLET, ll);
        llll_free(ll);
    }
}


//////////////////////// global class pointer variable
t_class *platform_class;




char platform_load_default_font(void)
{
#ifdef WIN_VERSION
    HINSTANCE hResInstance = hinst;
    
    HRSRC res = FindResource(hResInstance, "#1685", RT_RCDATA);
    if (res)
    {
        HGLOBAL mem = LoadResource(hResInstance, res);
        void *data = LockResource(mem);
        size_t len = SizeofResource(hResInstance, res);
        
        DWORD nFonts;
        HANDLE bachFont = AddFontMemResourceEx(
                                               data,       	// font resource
                                               len,       	// number of bytes in font resource
                                               NULL,          	// Reserved. Must be 0.
                                               &nFonts      	// number of fonts installed
                                               );
        
        if(bachFont == 0)
        {
            error("can't load font!");
        }
    }
#endif
    
#ifdef MAC_VERSION
    // MAC
    CFErrorRef error = NULL;
    CFBundleRef mainBundle = CFBundleGetBundleWithIdentifier(CFSTR("com.bachproject.dada.platform"));
    CFURLRef fontURL = mainBundle ? CFBundleCopyResourceURL(mainBundle, CFSTR("PressStart2P"), CFSTR("ttf"), NULL) : NULL;
    
    if (!mainBundle || !fontURL) {
        error("Failed to load Press Start 2P font. Please change textfont attribute.");
    } else if (!CTFontManagerRegisterFontsForURL(fontURL, kCTFontManagerScopeProcess, &error)) {
        
        // WE DON'T THROW AN ERROR HERE, since it could be that the font is already installed.
        
    }
    
    if (fontURL)
        CFRelease(fontURL);
    
#endif
    return 0;
    
}

void ext_main(void *moduleRef)
//int C74_EXPORT main(void)
{	
	t_class *c;
	
	common_symbols_init();
	llllobj_common_symbols_init();
	
	srand(time(NULL));

	if (dada_check_bach_version() || llllobj_test()) {
		dada_error_bachcheck();
		return;
	}

    platform_load_default_font();
    
    t_dada_platform_resources *resources = (t_dada_platform_resources *)sysmem_newptr(sizeof(t_dada_platform_resources));
    load_resources(resources, moduleRef);
    gensym("dadaplatformresources")->s_thing = (t_object *)resources;

	CLASS_NEW_CHECK_SIZE_EXT(c, "dada.platform", (method)platform_new, (method)platform_free, (long)sizeof(t_platform),
						 0L /* leave NULL!! */, A_GIMME, 0);
	
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, 0);
	
	// paint & utilities
//	class_addmethod(c, (method) platform_getdrawparams,	"getdrawparams", A_CANT, 0);
	class_addmethod(c, (method) platform_paint,			"paint", A_CANT, 0);
	class_addmethod(c, (method) platform_assist,			"assist",		A_CANT, 0);  
	class_addmethod(c, (method)	platform_notify,			"bachnotify",		A_CANT,		0);

	// save & preset
    class_addmethod(c, (method) platform_preset, "preset", 0);
    class_addmethod(c, (method) platform_begin_preset, "begin_preset", A_GIMME, 0);
    class_addmethod(c, (method) platform_restore_preset, "restore_preset", A_GIMME, 0);
    class_addmethod(c, (method) platform_end_preset, "end_preset", 0);
	CLASS_METHOD_ATTR_PARSE(c, "begin_preset", "undocumented", gensym("long"), 0L, "1");
	CLASS_METHOD_ATTR_PARSE(c, "restore_preset", "undocumented", gensym("long"), 0L, "1");
	CLASS_METHOD_ATTR_PARSE(c, "end_preset", "undocumented", gensym("long"), 0L, "1");
	class_addmethod(c, (method) platform_jsave, "jsave", A_CANT, 0);
	
	// interface
	class_addmethod(c, (method) platform_focusgained, "focusgained", A_CANT, 0);
	class_addmethod(c, (method) platform_focuslost, "focuslost", A_CANT, 0);
    
    // @method (mouse) @digest Edit content
    // @description
    // • <m>Alt+click+drag</m>: duplicate selected elements<br />
    // • <m>Cmd+click</m> (mac) or <m>Ctrl+click</m> (win) on an element to delete it<br />
    // • <m>right-click</m> or <m>two-fingers tap</m> on background: open contextual menu to add elements from prototypes<br />
	class_addmethod(c, (method) platform_mousedown, "mousedown", A_CANT, 0);
	class_addmethod(c, (method) platform_mousedrag, "mousedrag", A_CANT, 0);
	class_addmethod(c, (method) platform_mouseup, "mouseup", A_CANT, 0);
    
    // @method (keyboard) @digest Edit content or play
    // @description
    // @copy DADA_DOC_KEYBOARDS_COMMANDS_STANDARD_NAVIGATION
    // • <m>Cmd+Z</m> (mac) or <m>Ctrl+Z</m> (win): perform undo step<br />
    // • <m>Cmd+Shift+Z</m> (mac) or <m>Ctrl+Y</m> (win): perform redo step<br />
    // • <m>Cmd+S</m> (mac) or <m>Ctrl+S</m> (win): fix state for undo and save<br />
    // • <m>Cmd+A</m> (mac) or <m>Ctrl+A</m> (win): select all<br />
    // • <m>Backspace</m>: delete selection<br />
    // • <m>Cmd+I</m> (mac) or <m>Ctrl+I</m> (win): open inspector<br />
    // • <m>Spacebar</m>: toggle play<br />
    // • <m>↓</m>, <m>↑</m>, <m>←</m>, <m>→</m>: move hero (respectively) down, up (= jump), left, right<br />
    // • <m>Tab</m>: fire (shoot)<br />
    // • <m>Esc</m>: set domain start at 0 (beginning of level)<br />
  	class_addmethod(c, (method) platform_key, "key", A_CANT, 0);
  	class_addmethod(c, (method) platform_keyup, "keyup", A_CANT, 0);
    
    // @method (tools) @digest Navigate or select content
    // @description
    // @copy DADA_DOC_TOOLS_INTRO
    // @copy DADA_DOC_TOOLS_ZX
    // @copy DADA_DOC_TOOLS_A
	class_addmethod(c, (method) platform_mousemove, "mousemove", A_CANT, 0);
	class_addmethod(c, (method) platform_mouseenter, "mouseenter", A_CANT, 0);
	class_addmethod(c, (method) platform_mouseleave, "mouseleave", A_CANT, 0);
	class_addmethod(c, (method) platform_mousewheel, "mousewheel", A_CANT, 0); 
    class_addmethod(c, (method) platform_oksize, "oksize", A_CANT, 0);
	
	// @method bang @digest Output sampling information
	// @description Output the sampling information regarding the sampling points set via the <m>sample</m> message.
	class_addmethod(c, (method)platform_bang,			"bang",			0);

    
    // @method int @digest Play/Stop
    // @description A non-zero integer triggers a <m>play</m> message, a zero integer triggers a <m>stop</m> message
    class_addmethod(c, (method) platform_int, "int", A_LONG, 0);
    
    
    // @method dump @digest Output state
    // @description Outputs the current state of the object. The syntax is
    // <b>platform (levelinfo <m>LEVELINFO_SPECS</m>) (sprites <m>SPRITE1</m> <m>SPRITE2</m>...) (prototypes <m>PROTOTYPE1</m> <m>PROTOTYPE2</m>...)
    // (gamechars <m>GAMECHAR1</m> <m>GAMECHAR2</m>...) (blocks <m>BLOCK1</m> <m>BLOCK2</m>...) (coins <m>COIN1</m> <m>COIN2</m>...) (portals <m>PORTAL1</m> <m>PORTAL2</m>...)</b> <br />
    // Levelinfo specifiations have in the syntax:
    // <b>(title <m>title</m>) (hero <m>hero_name</m>) (bgsprite <m>background_sprite_name</m>) (gravity <m>gravity_coefficient</m>) (maxtime <m>maximum_time_ms_or_none</m>)
    // (height <m>level_height</m>) (width <m>total_level_width</m>) (groundfriction <m>ground_friction_coefficient</m>) (airfriction <m>air_friction_coefficient</m>) (textcolor <m>r</m> <m>g</m> <m>b</m> <m>a</m>) (intro <m>0/1:has_intro_screen?</m>)</b>. <br />
    // Each <m>SPRITE</m> has the syntax:
    // <b>[[name <m>name</m>] [pics <m>pic1_filename</m> <m>pic2_filename</m>...] [rect <m>x</m> <m>y</m> <m>width</m> <m>height</m>] [stretch <m>0/1:can_stretch?</m>] [slidetime <m>slide_time_in_ms</m>]]</b><br />
    // Each <m>PROTOTYPE</m> has the syntax:
    // <b>[<m>prototype_name</m> <m>prototype_type</m> [<m>spec1</m> <m>spec1_value</m>] [<m>spec2</m> <m>spec2_value</m>]...]</b><br />
    // where <m>prototype_type</m> is one of the following symbols: "block", "coin", "gamechar", "portal" and each <m>spec</m> is a specification belonging
    // to the corresponding category (see below). <br />
    // Each <m>GAMECHAR</m> has the syntax:
    // <b>((coord <m>x</m> <m>y</m>) (speed <m>x</m> <m>y</m>) (width <m>w</m>) (height <m>h</m>) (ext <m>left</m> <m>right</m> <m>top</m> <m>bottom</m>)
    // (name <m>name</m>) (type <m>gamechar_type</m>) (points <m>num_points</m>) (vp <m>num_vps</m>) (direction <m>1/-1:right/left</m>)
    // (state <m>state</m>) (ability <m>list_of_abilities</m>) (howdies <m>dying_ways</m>) (howkills <m>killing_ways</m>) (idlesprite <m>spritename</m>)
    // (walksprite <m>spritename</m>) (jumpsprite <m>spritename</m>) (glidesprite <m>spritename</m>) (flysprite <m>spritename</m>)
    // (deadsprite <m>spritename</m>) (deathseq <m>script_when_dying</m>) (resurrectpositions (<m>x1</m> <m>y1</m>) (<m>x2</m> <m>y2</m>)...))</b>,
    // where <m>gamechar_type</m> can be "idle", "usercontrol", "enemy", "food" or "bullet". <br />
    // where <m>dying_ways</m> and <m>killing_ways</m> represent the directions or movement allowing the element to die/kill, and
    // are a list containing a combination of: "left", "right", "top", "bottom", "bump", "bullet", "glide". In turns, <m>state</m> is one of the following
    // symbols: "idle", "walking", "jumping", "flying", "swimming", "running", "gliding", "dying", "dead", "generating", "enteringportal", "exitingportal", "elsewhere". <br />
    // Each <m>BLOCK</m> has the syntax:
    // <b>((coord <m>x</m> <m>y</m>) (width <m>w</m>) (height <m>h</m>) (name <m>name</m>) (sprite <m>spritename</m>) (solid <m>0/1:is_solid?</m>)
    // (howhit <m>hit_ways</m>) (hitseq <m>script_when_hit</m>) (loophitseq <m>0/1:is_hitseq_to_be_read_in_loop?</m>)
    // (breaksprite <m>breaking_sprite_name</m>) (state <m>state</m>) (pointsgiven <m>num_points</m>) (music <m>music_llll_when_hit</m>))</b><br />
    // Each <m>COIN</m> has the syntax:
    // <b>((coord <m>x</m> <m>y</m>) (width <m>w</m>) (height <m>h</m>) (name <m>name</m>) (sprite <m>spritename</m>) (takeable <m>0/1:is_takeable?</m>)
    // (taken <m>0/1:is_already_taken?</m>) (pointsgiven <m>num_points</m>) (vpgiven <m>num_vps</m>) (music <m>music_llll_when_taken</m>))</b><br />
    // Each <m>PORTAL</m> has the syntax:
    // <b>((coord <m>x</m> <m>y</m>) (width <m>w</m>) (height <m>h</m>) (name <m>name</m>) (sprite <m>spritename</m>) (open <m>0/1:is_open?</m>)
    // (howenter <m>entering_ways</m>) (howexit <m>exiting_ways</m>) (enterseq <m>script_when_entering</m>) (exitseq <m>script_when_exiting</m>)
    // (music <m>music_llll_when_used</m>) (heroonly <m>0/1:only_hero_can_use_it?</m>))</b>,
    // where <m>entering_ways</m> and <m>exiting_ways</m> can be a list containing a combination of: "left", "right", "top", "bottom". <br />
    // For all the scripting commands, refer to the <m>script</m> message, keeping in mind that you can use "hero" to refer to the hero and "me"
    // to refer to the subject of the action (e.g. "give me 10 vp").
    class_addmethod(c, (method)platform_anything,	"dump",			A_GIMME,	0);
    class_addmethod(c, (method)platform_anything,	"script",			A_GIMME,	0);
    class_addmethod(c, (method)platform_anything,	"resurrect",			A_GIMME,	0);
	class_addmethod(c, (method)platform_anything,	"anything",			A_GIMME,	0);
	class_addmethod(c, (method)platform_anything,	"setstoredstate",	A_GIMME, 0);
	
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
	
	// @method clock @digest Select a clock source
	// @description The word <m>clock</m>, followed by the name of an existing <m>setclock</m> objects, sets the <o>dada.bounce</o> 
	// object to be controlled by that <m>setclock</m> object rather than by Max's internal millisecond clock. 
	// The word <m>clock</m> by itself sets the object back to using Max's regular millisecond clock.
	class_addmethod(c, (method)platform_clock,	"clock", A_DEFSYM, 0);

	
	
	// @method play @digest Start sequencing
	// @description Starts the sequencing enginge
	class_addmethod(c, (method)platform_play,	"play",		A_GIMME,	0);

	// @method resume @digest Resume sequencing
	// @description Resumes the sequencing enginge
	class_addmethod(c, (method)platform_resume,	"resume",		A_GIMME,	0);
	
	// @method stop @digest Stop sequencing
	// @description Stops the sequencing enginge	
	class_addmethod(c, (method)platform_stop,	"stop",		A_GIMME,	0);

    
    // @method domain @digest Set the X domain
    // @description The <m>domain</m> message, followed by two numbers, sets minimum and maximum coordinates
    // to be displayed on the X axis.
    // The <m>domain</m> message,  followed by the "start" or "end" symbol and a number, sets the coordinate
    // to be displayed respectively at the left boundary or at the right boundary of the object box.
    // @marg 0 @name arguments @optional 0 @type list
    class_addmethod(c, (method)platform_anything,		"domain",		A_GIMME,	0);
    
    // @method range @digest Set the Y range
    // @description The <m>range</m> message, followed by two numbers, sets minimum and maximum coordinates
    // to be displayed on the Y axis
    // The <m>range</m> message,  followed by the "start" or "end" symbol and a number, sets the coordinate
    // to be displayed respectively at the bottom boundary or at top right boundary of the object box.
    // @marg 0 @name arguments @optional 0 @type list
    class_addmethod(c, (method)platform_anything,		"range",		A_GIMME,	0);

    
    // @method getdomain @digest Retrieve current X domain
    // @description The <m>getdomain</m> message outputs from the third outlet the minimum and maximum
    // coordinates displayed on the X axis, preceded by a <m>domain</m> symbol.
    class_addmethod(c, (method)platform_anything,		"getdomain",		A_GIMME,	0);
    
    // @method getrange @digest Retrieve current Y range
    // @description The <m>getrange</m> message outputs from the third outlet the minimum and maximum
    // coordinates displayed on the Y axis, preceded by a <m>range</m> symbol.
    class_addmethod(c, (method)platform_anything,		"getrange",		A_GIMME,	0);

    
    // @method break @digest Break after notification
    // @description The <m>break</m> message will stop any game actions to be performed
    // after a given notification has been sent. Trigger the message synchronously
    // with the notification in order to have it working (e.g. with no delays or deferring).
    class_addmethod(c, (method)platform_anything,		"break",		A_GIMME,	0);

    
    // @method resettime @digest Reset time to zero
    // @description The <m>resettime</m> message will set the current time to 0.
    class_addmethod(c, (method)platform_anything,		"resettime",		A_GIMME,	0);

    // @method fix @digest Fix state
    // @description The <m>fix</m> message will "fix" the current state, making it available
    // for undo (next undo action will revert to the last fixed state).
    class_addmethod(c, (method)platform_anything,		"fix",		A_GIMME,	0);

    // @method restart @digest Restart
    // @description The <m>restart</m> message will resume the level from the beginning;
    // the optional integer argument sets the hero victory points.
    // @marg 0 @name hero_vp @optional 1 @type int
    class_addmethod(c, (method)platform_anything,		"restart",		A_GIMME,	0);

    
    // @method addsprite @digest Add a sprite
    // @description The <m>addsprite</m> message will add a new sprite to the current level (see <m>dump</m> syntax).
    // @marg 0 @name specifications @optional 0 @type llll
    class_addmethod(c, (method)platform_anything,		"addsprite",		A_GIMME,	0);

    
    // @method addprototype @digest Add a prototype
    // @description The <m>addprototype</m> message will add a new prototype to the current level (see <m>dump</m> syntax).
    // @marg 0 @name specifications @optional 0 @type llll
    class_addmethod(c, (method)platform_anything,		"addprototype",		A_GIMME,	0);

    
    // @method script @digest Execute script
    // @description The <m>script</m> message will execute a sequence of actions,
    // contained in the argument llll. Scripts can be also set inside some specification fields (e.g. "dieseq") and automatically triggered
    // during playtime. Scripts must be a sequence of actions in the form <b>[<m>ACTION1</m>] [<m>ACTION2</m>]...</b>.
    // In all actions two keywords can be used: "me", referring to the subject of the action (if automatically triggered at playtime by
    // fields such as "breakseq" or "dieseq"), and "hero", referring to the current gamechar hero.
    // Actions can be the ones below (curly brackets refer to variables, while square brackets mean that the arguments are optional). <br />
    // • give {gamechar (symbol)} {howmany (int)} [{what (symbol)} [from {item (symbol)}]]: gives a gamechar either points or victory points (vp).
    //   The gamechar must be called via its name, and the {what} symbol must be either "points" (default) or "vp".
    //   You can additionally specify from which character or element points are given. <br />
    // • generate {gamecharprototype (symbol)} [from {item (symbol)}]: generates a gamechar from a given item (e.g. a block). If the item is not
    //   explicitly set, it is assumed to be the subject; otherwise it is assumed to be the item name. The character must be defined as prototype,
    //   and called via their its prototype name (and not its own name!). <br />
    // • add {gamechar (symbol)} ability {whichability (symbol)} [during {milliseconds (double)}]: add an ability to a given character, represented
    //   by its name. If the "during" part is also assigned, the addition only last for a given amount of time. <br />
    // • remove {gamechar (symbol)} ability {whichability (symbol)}  [during {milliseconds (double)}]: remove an ability to a given character,
    //   represented by its name.<br />
    // • change {item (symbol)} {attributes (llll)}: change some property of a given item (block, coin, game character or portal), according to an
    //   llll containing the new values for the attributes to be changed. <br />
    // • notify {anything (llll)}: send a given notification from the notification outlet. <br />
    // • goto [level {filename (symbol)} at] {portalname (symbol)} with {options (llll)}: go somewhere else, in the same level (defined by a portal name),
    //   or in a new level (defined by a symbol containing the filename, if in Max search path, or the file full path). Options can be given in llll form
    //   such as: ({option_name} {option_value}) ({option_name} {option_value})... Option names are: "intro" (whether or not the intro black screen should
    //   be shown; values are 0/1; if the option is not given, the level specification apply), "resettime" (whether or not the global time should be reset
    //   to zero; values are 0/1; 0 is the default). <br />
    // • break {block (sym)} [by {gamechar (symbol)}]: break a block, identified by its name; if the "By" clause is also set, the "responsible" for
    //   breaking will be a given game character, also identified by its name. You can use the simple "break" word (without outer level of parentheses)
    //   for default breaking of blocks. <br />
    // • wait {milliseconds (double)}: wait for some time before performing next action.
    // • dontdie: when used in a dying sequence, prevents the character from dying. <br />
    // • win: hero wins <br />
    // • gameover: hero loses <br />
    // @marg 0 @name script_actions @optional 0 @type llll
    class_addmethod(c, (method)platform_anything,		"script",		A_GIMME,	0);

    
    // @method count @digest Count items
    // @description The <m>count</m> message, followed by one of the symbols: "gamechars",
    // "blocks", "portals", "coins", "items", will return the number of corresponding items.
    // If the "item" symbol is input, then the number of all items is returned.
    // The symbol can be also followed by the "where" symbol and by a series of properties
    // The answer is output preceded by the "count" router from the
    // queries and notification outlet (second outlet).
    // @marg 0 @name what @optional 0 @type symbol
    // @marg 1 @name where_clause @optional 1 @type llll
    // @example count coins @caption count all coins
    // @example count coins where [pointsgiven 10] @caption only count coins giving 10 points
    // @example count items where [name Juan] @caption count all items named "Juan"
    // @example count gamechars where [vp 1] @caption count all gamechars with 1 VP
    class_addmethod(c, (method)platform_anything,		"count",		A_GIMME,	0);

    
    // @method clear @digest Delete items
    // @description The <m>clear</m> message will delete every item.
    // If followed by one of the symbols: "levelinfo", "sprites", "prototypes", "gamechars",
    // "blocks", "portals", "coins", only the corresponding category will be deleted.
    // @example clear @caption delete all items
    // @example clear coins @caption delete all coins
    // @marg 0 @name what @optional 1 @type symbol
    class_addmethod(c, (method)platform_anything,		"clear",		A_GIMME,	0);

    
    // @method add @digest Add items
    // @description The <m>add</m> message, followed by an item type ("coin", "gamechar", "block" or "portal") and an llll, will add an item in the level,
    // having specification set by the llll (see <m>dump</m> syntax).
    // @marg 0 @name item_type @optional 0 @type symbol
    // @marg 1 @name specifications @optional 0 @type llll
    class_addmethod(c, (method)platform_anything,		"add",		A_GIMME,	0);

    
    // @method delete @digest Delete items
    // @description The <m>delete</m> message, followed by an item type ("coin", "gamechar", "block" or "portal") and an integer <m>N</m>, will delete the <m>N</m>-th item in the level.
    // @marg 0 @name item_type @optional 0 @type symbol
    // @marg 1 @name item_index @optional 0 @type int
    class_addmethod(c, (method)platform_anything,		"delete",		A_GIMME,	0);

    
    // @method set @digest Modify items
    // @description The <m>set</m> message, followed by an item type ("coin", "gamechar", "block" or "portal") and an integer <m>N</m> and an llll, will modify the <m>N</m>-th item in the level,
    // according to the specifications set via the llll (see <m>dump</m> syntax).
    // @marg 0 @name item_type @optional 0 @type symbol
    // @marg 1 @name item_index @optional 0 @type int
    // @marg 2 @name new_specifications @optional 0 @type llll
    class_addmethod(c, (method)platform_anything,		"set",		A_GIMME,	0);

    
    
    DADAOBJ_JBOX_DECLARE_READWRITE_METHODS(c);
    DADAOBJ_JBOX_DECLARE_IMAGE_METHODS(c);
    DADAOBJ_JBOX_DECLARE_ACCEPTSDRAG_METHODS(c);

	llllobj_class_add_out_attr(c, LLLL_OBJ_UI);
	dadaobj_class_init(c, LLLL_OBJ_UI, DADAOBJ_BORDER | DADAOBJ_BORDER_SHOWDEFAULT | DADAOBJ_ZOOM | DADAOBJ_CENTEROFFSET | DADAOBJ_UNDO | DADAOBJ_EMBED | DADAOBJ_GRID | DADAOBJ_LABELS | DADAOBJ_SNAPTOGRID | DADAOBJ_MOUSEHOVER | DADAOBJ_PLAY | DADAOBJ_NOTIFICATIONS | DADAOBJ_EXPORTTOJITTER);

    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"grid",0,"1 1"); // finer grid by default.
    CLASS_ATTR_DEFAULT_SAVE(c,"snaptogrid",0,"1");  // snapped to grid by default.

    
	CLASS_ATTR_DEFAULT(c, "patching_rect", 0, "0 0 725 320");
	// @exclude dada.platform
	CLASS_ATTR_DEFAULT(c, "presentation_rect", 0, "0 0 725 320");
	// @exclude dada.platform
	

	CLASS_STICKY_ATTR(c,"category",0,"Color");
	
	CLASS_ATTR_RGBA(c, "selectioncolor", 0, t_platform, j_selectioncolor);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "selectioncolor", 0, "0.8 0. 0.8 1.");
	CLASS_ATTR_STYLE_LABEL(c, "selectioncolor", 0, "rgba", "Selection Color");
	// @description Sets the color of the selection.
	
	CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	
	CLASS_STICKY_ATTR(c,"category",0,"Behavior");
	
    CLASS_ATTR_CHAR(c, "editmode", 0, t_platform, edit_mode);
    CLASS_ATTR_STYLE_LABEL(c, "editmode", 0, "enumindex", "Edit Mode");
    CLASS_ATTR_ENUMINDEX(c,"editmode", 0, "Lock Not While Playing Always");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"editmode",0,"1");
    CLASS_ATTR_BASIC(c, "editmode", 0);
    // @description Sets the edit mode: Lock (0) doesn't allow editing, "Not While Playing" (1) only allows
    // editing while not playing, "Always" (2) also allows editing while playing

    CLASS_ATTR_CHAR(c, "playmode", 0, t_platform, play_mode);
    CLASS_ATTR_STYLE_LABEL(c, "playmode", 0, "enumindex", "Play Mode");
    CLASS_ATTR_ENUMINDEX(c,"playmode", 0, "Can't Play Standard Can't Stop");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"playmode",0,"1");
    CLASS_ATTR_BASIC(c, "playmode", 0);
    // @description Sets the play mode: Can't Play (0) doesn't allow playing, Standard (1) allows play toggling via
    // spacebar or messages, Can't Stop (2) doesn't allow stopping.

    
    CLASS_ATTR_CHAR(c, "autoscroll", 0, t_platform, autoscroll);
    CLASS_ATTR_STYLE_LABEL(c, "autoscroll", 0, "onoff", "Scroll Automatically");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"autoscroll",0,"1");
    CLASS_ATTR_BASIC(c, "autoscroll", 0);
    // @description Toggles the ability to scroll automatically according to the hero position.
    
    
    CLASS_ATTR_CHAR(c, "savefixed", 0, t_platform, save_fixed_states_only);
    CLASS_ATTR_STYLE_LABEL(c, "savefixed", 0, "onoff", "Only Save Fixed States");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"savefixed",0,"1");
    CLASS_ATTR_BASIC(c, "savefixed", 0);
    // @description Toggles the ability to only save states that had been "fixed" via <m>fix</m> message or via interface.

    
    CLASS_ATTR_CHAR(c, "constraintzoom", 0, t_platform, autozoom);
    CLASS_ATTR_STYLE_LABEL(c, "constraintzoom", 0, "onoff", "Constraint Zoom To Level Height");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"constraintzoom",0,"1");
    CLASS_ATTR_BASIC(c, "constraintzoom", 0);
    // @description Toggles the ability to constraint the zoom according to the level height.
    
    CLASS_ATTR_DOUBLE(c, "ydie", 0, t_platform, die_y_line);
    CLASS_ATTR_STYLE_LABEL(c, "ydie", 0, "text", "Y Value Under Which Characters Die");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"ydie",0,"-1");
    CLASS_ATTR_INVISIBLE(c, "ydie", ATTR_GET_OPAQUE | ATTR_SET_OPAQUE);
    // @exclude all
    // @description Sets the y value under which the characters will automatically die.

    CLASS_ATTR_CHAR(c, "collisionheroonly", 0, t_platform, only_check_gamechar_collisions_for_user_gamechars);
    CLASS_ATTR_STYLE_LABEL(c, "collisionheroonly", 0, "onoff", "Only Check Collision For Hero");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"collisionheroonly",0,"0");
    CLASS_ATTR_INVISIBLE(c, "collisionheroonly", ATTR_GET_OPAQUE | ATTR_SET_OPAQUE);
    // @exclude all
    // @description Toggles the ability to only check collisions for the hero (default: off).

    CLASS_STICKY_ATTR_CLEAR(c, "category");

    CLASS_STICKY_ATTR(c,"category",0,"Notifications");

	CLASS_ATTR_CHAR(c, "notifycoins", 0, t_platform, notify_coins);
    CLASS_ATTR_STYLE_LABEL(c, "notifycoins", 0, "onoff", "Notify Coin");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"notifycoins",0,"1");
    // @description Toggles the notifications for coins.

	CLASS_ATTR_CHAR(c, "notifyblocks", 0, t_platform, notify_blocks);
    CLASS_ATTR_STYLE_LABEL(c, "notifyblocks", 0, "onoff", "Notify Blocks");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"notifyblocks",0,"1");
    // @description Toggles the notifications for blocks.

    CLASS_ATTR_CHAR(c, "notifyportals", 0, t_platform, notify_portals);
    CLASS_ATTR_STYLE_LABEL(c, "notifyportals", 0, "onoff", "Notify Portals");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"notifyportals",0,"1");
    // @description Toggles the notifications for portals.

    CLASS_ATTR_CHAR(c, "notifyusercontrol", 0, t_platform, notify_usercontrol_actions);
    CLASS_ATTR_STYLE_LABEL(c, "notifyusercontrol", 0, "onoff", "Notify User Control Actions");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"notifyusercontrol",0,"1");
    // @description Toggles the notifications for user control actions.

    CLASS_ATTR_CHAR(c, "notifygamechar", 0, t_platform, notify_gamechars);
    CLASS_ATTR_STYLE_LABEL(c, "notifygamechar", 0, "onoff", "Notify Game Character Interactions");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"notifygamechar",0,"0");
    // @description Toggles the notifications for game characters.

    CLASS_ATTR_CHAR(c, "notifygamecharpos", 0, t_platform, notify_gamechar_pos);
    CLASS_ATTR_STYLE_LABEL(c, "notifygamecharpos", 0, "onoff", "Notify Characters Position");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"notifygamecharpos",0,"0");
    // @description Toggles the notifications for game characters positioning.

    CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	CLASS_STICKY_ATTR(c,"category",0,"Level");

    e_llllobj_obj_types type = LLLL_OBJ_ERR; //it's actually referred to ordinary object, no dadaobj header
    DADAOBJ_CLASS_ATTR_SYM_SUBSTRUCTURE(c, type, "bgsprite", 0, t_platform, m_level, t_levelinfo, background_sprite);
    CLASS_ATTR_STYLE_LABEL(c, "bgsprite", 0, "text", "Background Sprite");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"bgsprite",0,"background");
    // @description Sets the level background sprite.

    DADAOBJ_CLASS_ATTR_SYM_SUBSTRUCTURE(c, type, "title", 0, t_platform, m_level, t_levelinfo, levelname);
    CLASS_ATTR_STYLE_LABEL(c, "title", 0, "text", "Level Title");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"title",0,"\"Level 1\"");
    // @description Sets the level title.

    DADAOBJ_CLASS_ATTR_ATOM_SUBSTRUCTURE(c, type, "maxtime", 0, t_platform, m_level, t_levelinfo, maxtime);
    CLASS_ATTR_STYLE_LABEL(c, "maxtime", 0, "text", "Maximum Time");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"maxtime",0,"none");
    // @description Sets the level maximum time (use "none" to avoid setting it).

    DADAOBJ_CLASS_ATTR_SYM_SUBSTRUCTURE(c, type, "hero", 0, t_platform, m_level, t_levelinfo, hero_name);
    CLASS_ATTR_STYLE_LABEL(c, "hero", 0, "text", "Hero Character Name");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"hero",0,"Juan");
    // @description Sets the level hero name.
    
	DADAOBJ_CLASS_ATTR_DOUBLE_SUBSTRUCTURE(c, type, "gravity", 0, t_platform, m_level, t_levelinfo, gravity);
    CLASS_ATTR_STYLE_LABEL(c, "gravity", 0, "text", "Gravity");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"gravity",0,"15.");
    // @description Sets the level gravity coefficient.

    DADAOBJ_CLASS_ATTR_DOUBLE_SUBSTRUCTURE(c, type, "height", 0, t_platform, m_level, t_levelinfo, level_height);
    CLASS_ATTR_STYLE_LABEL(c, "height", 0, "text", "Level Height");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"height",0,"10");
    CLASS_ATTR_BASIC(c, "height", 0);
    // @description Sets the level height.
    
    DADAOBJ_CLASS_ATTR_DOUBLE_SUBSTRUCTURE(c, type, "width", 0, t_platform, m_level, t_levelinfo, level_width);
    CLASS_ATTR_STYLE_LABEL(c, "width", 0, "text", "Level Width");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"width",0,"100");
    CLASS_ATTR_BASIC(c, "width", 0);
    // @description Sets the level total width.

    DADAOBJ_CLASS_ATTR_DOUBLE_SUBSTRUCTURE(c, type, "groundfriction", 0, t_platform, m_level, t_levelinfo, ground_friction);
    CLASS_ATTR_STYLE_LABEL(c, "groundfriction", 0, "text", "Ground Friction");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"groundfriction",0,"5.");
    // @description Sets the level ground friction coefficient.

    DADAOBJ_CLASS_ATTR_DOUBLE_SUBSTRUCTURE(c, type, "airfriction", 0, t_platform, m_level, t_levelinfo, air_friction);
    CLASS_ATTR_STYLE_LABEL(c, "airfriction", 0, "text", "Air Friction");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"airfriction",0,"1.");
    // @description Sets the level air friction coefficient.

    DADAOBJ_CLASS_ATTR_RGBA_SUBSTRUCTURE(c, type, "textcolor", 0, t_platform, m_level, t_levelinfo, j_textcolor);
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "textcolor", 0, "0. 0. 0. 1.");
    CLASS_ATTR_STYLE_LABEL(c, "textcolor", 0, "rgba", "Text Color");
    // @description Sets the color of the text for the level

    DADAOBJ_CLASS_ATTR_CHAR_SUBSTRUCTURE(c, type, "intro", 0, t_platform, m_level, t_levelinfo, has_intro);
    CLASS_ATTR_STYLE_LABEL(c, "intro", 0, "onoff", "Show Level Intro");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"intro",0,"0");
    // @description Toggles the intro screen for the level.


    CLASS_STICKY_ATTR_CLEAR(c, "category");

    
    CLASS_STICKY_ATTR(c,"category",0,"Font");
	
    CLASS_ATTR_SYM(c,"textfont", 0, t_platform, fontname);
    CLASS_ATTR_STYLE_LABEL(c, "textfont",0,"font","Text Font");
    CLASS_ATTR_DEFAULTNAME_SAVE_PAINT(c,"textfont",0,"\"Press Start 2P\"");
    // @description Sets the level font.

    CLASS_STICKY_ATTR_CLEAR(c, "category");

    
	CLASS_STICKY_ATTR(c,"category",0,"Appearance");
    
	CLASS_ATTR_CHAR(c, "showgamechars", 0, t_platform, show_hero);
    CLASS_ATTR_STYLE_LABEL(c, "showgamechars", 0, "onoff", "Show Characters");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showgamechars",0,"1");
    // @description Shows/hides all game characters.

	CLASS_ATTR_CHAR(c, "showblocks", 0, t_platform, show_blocks);
    CLASS_ATTR_STYLE_LABEL(c, "showblocks", 0, "onoff", "Show Blocks");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showblocks",0,"1");
    // @description Shows/hides all blocks.

	CLASS_ATTR_CHAR(c, "showcoins", 0, t_platform, show_coins);
    CLASS_ATTR_STYLE_LABEL(c, "showcoins", 0, "onoff", "Show Coins");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showcoins",0,"1");
    // @description Shows/hides all coins.
	
	CLASS_ATTR_CHAR(c, "showvp", 0, t_platform, show_legend_vp);
    CLASS_ATTR_STYLE_LABEL(c, "showvp", 0, "onoff", "Show Victory Points");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showvp",0,"1");
    // @description Shows/hides victory points in legend.

	CLASS_ATTR_CHAR(c, "showpoints", 0, t_platform, show_legend_points);
    CLASS_ATTR_STYLE_LABEL(c, "showpoints", 0, "onoff", "Show Points");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showpoints",0,"1");
    // @description Shows/hides points in legend.

	CLASS_ATTR_CHAR(c, "showheroname", 0, t_platform, show_legend_hero);
    CLASS_ATTR_STYLE_LABEL(c, "showheroname", 0, "onoff", "Show Hero Name");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showheroname",0,"1");
    // @description Shows/hides hero name in legend.

    CLASS_ATTR_CHAR(c, "showleveltitle", 0, t_platform, show_legend_title);
    CLASS_ATTR_STYLE_LABEL(c, "showleveltitle", 0, "onoff", "Show Level Title");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showleveltitle",0,"0");
    // @description Shows/hides level title in legend.

    CLASS_ATTR_CHAR(c, "showtime", 0, t_platform, show_legend_time);
    CLASS_ATTR_STYLE_LABEL(c, "showtime", 0, "enumindex", "Show Time");
    CLASS_ATTR_ENUMINDEX(c,"showtime", 0, "Don't Forward Countdown");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showtime",0,"2");
    // @description Shows/hides remaining time in legend: Don't (0) doesn't show anything,
    // Forward (1) shows increasing time, Countdown (2) shows countdown time.

    
	CLASS_ATTR_DOUBLE(c, "legendfontsize", 0, t_platform, legend_font_size);
    CLASS_ATTR_STYLE_LABEL(c, "legendfontsize", 0, "text", "Legend Size");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"legendfontsize",0,"14");
    // @description Sets the legend font size.

	CLASS_ATTR_DOUBLE(c, "floattextfontsize", 0, t_platform, floattext_font_size);
    CLASS_ATTR_STYLE_LABEL(c, "floattextfontsize", 0, "text", "Floating Text Size");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"floattextfontsize",0,"11");
    // @description Sets the floating text font size.
	
	CLASS_STICKY_ATTR_CLEAR(c, "category");

		
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	platform_class = c;
	
	
	dev_post("dada.platform compiled %s %s", __DATE__, __TIME__);
	return;
}

void update_hero_fields(t_platform *x)
{
    x->hero_ID = dadaitem_get_ID_from_name(dadaobj_cast(x), x->m_level.hero_name);
    x->hero = platform_get_hero(x);
}

t_max_err platform_notify(t_platform *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	if (msg == _sym_attr_modified) {
		t_symbol *attr_name = (t_symbol *)object_method((t_object *)data, _sym_getname);
        if (attr_name == gensym("hero")) 
            update_hero_fields(x);

        if (attr_name == gensym("levelheight")) {
            dadaobj_setrange(dadaobj_cast(x), jpatcher_get_firstview((t_object *)gensym("#P")->s_thing), 0, x->m_level.level_height);
        } else if (strncmp(attr_name->s_name, "notify", 6)) {
			x->break_after_notification = 0;
		} 
		
        if (!x->b_ob.d_ob.m_paint.dont_repaint && !x->itsme)
            platform_iar(x);
	}
	
	return MAX_ERR_NONE;
}


void platform_begin_preset(t_platform *x, t_symbol *s, long argc, t_atom *argv)
{
	x->preset_ac = atom_getlong(argv) ;
	x->preset_av = (t_atom *)bach_newptr(x->preset_ac * sizeof(t_atom));
	
	// could allocate memory here etc.
	//	post("begin_preset %ld values will be arriving",x->b_ob.d_ob.preset_ac);
}


void platform_restore_preset(t_platform *x, t_symbol *s, long argc, t_atom *argv)
{
	long start, size;
	
	start = atom_getlong(argv);
	size = atom_getlong(argv + 1);
	//	post("restore_preset start %ld size %ld", start,size);
	
	sysmem_copyptr(argv+2, x->preset_av+start, size*sizeof(t_atom));
}

void platform_end_preset(t_platform *x)
{
	//	post("end_preset received");
	platform_anything(x, NULL, x->preset_ac,x->preset_av);
	bach_freeptr(x->preset_av);
}

void platform_preset(t_platform *x){
	t_atom temp[256];
	void *buf;
	long i, index, size;
	char wrote = false, begin = true, done = false;
	
	t_llll *data = platform_get_state(x);
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


void platform_jsave(t_platform *x, t_dictionary *d)
{
	if (x->b_ob.d_ob.save_data_with_patcher){
		if (x->b_ob.r_ob.l_dictll) {
			llll_store_in_dictionary(x->b_ob.r_ob.l_dictll, d, "platform_data", NULL);
		} else {
            t_llll *data = x->save_fixed_states_only ? llll_clone(x->fixed_state) : platform_get_state(x);
			llll_store_in_dictionary(data, d, "platform_data", NULL);
			llll_free(data);
		}
	} 
}


t_dada_sprite *label_to_sprite(t_platform *x, t_symbol *label)
{
	long i;
	for (i = 0; i < x->sprite_manager.num_sprites; i++)
		if (x->sprite_manager.sprite[i].name == label)
			return &x->sprite_manager.sprite[i];
	return NULL;
}


t_platform_prototype *label_to_prototype(t_platform *x, t_symbol *label)
{
	long i;
	for (i = 0; i < x->prototype_manager.num_prototypes; i++)
		if (x->prototype_manager.prototypes[i].name == label)
			return &x->prototype_manager.prototypes[i];
	return NULL;
}


t_llll *platform_get_levelinfo(t_platform *x)
{
    t_llll *ll = llll_get();
    llll_appendsym(ll, gensym("levelinfo"));
    llll_appendllll(ll, symbol_and_symbol_to_llll(gensym("title"), x->m_level.levelname ? x->m_level.levelname : _llllobj_sym_none));
    llll_appendllll(ll, symbol_and_symbol_to_llll(gensym("hero"), x->m_level.hero_name ? x->m_level.hero_name : _llllobj_sym_none));
    llll_appendllll(ll, symbol_and_symbol_to_llll(gensym("bgsprite"), x->m_level.background_sprite ? x->m_level.background_sprite : _llllobj_sym_none));
    llll_appendllll(ll, symbol_and_double_to_llll(gensym("gravity"), x->m_level.gravity));
    if (is_atom_number(&x->m_level.maxtime))
        llll_appendllll(ll, symbol_and_double_to_llll(gensym("maxtime"), atom_getfloat(&x->m_level.maxtime)));
    else
        llll_appendllll(ll, symbol_and_symbol_to_llll(gensym("maxtime"), _llllobj_sym_none));
    llll_appendllll(ll, symbol_and_double_to_llll(gensym("height"), x->m_level.level_height));
    llll_appendllll(ll, symbol_and_double_to_llll(gensym("width"), x->m_level.level_width));
    llll_appendllll(ll, symbol_and_double_to_llll(gensym("groundfriction"), x->m_level.ground_friction));
    llll_appendllll(ll, symbol_and_double_to_llll(gensym("airfriction"), x->m_level.air_friction));
    llll_appendllll(ll, symbol_and_llll_to_llll_chained(gensym("textcolor"), color_to_llll(&x->m_level.j_textcolor)));
    llll_appendllll(ll, symbol_and_long_to_llll(gensym("intro"), x->m_level.has_intro));

    return ll;
}

t_llll *platform_get_sprites(t_platform *x)
{
	long i, j;
	t_llll *out_ll = llll_get();
	for (i = 0; i < x->sprite_manager.num_sprites; i++) {
        t_llll *ll = llll_get(), *pics = llll_get();
        llll_appendllll(ll, symbol_and_symbol_to_llll(_llllobj_sym_name, x->sprite_manager.sprite[i].name));
		for (j = 0; j < x->sprite_manager.sprite[i].num_slides; j++)
			llll_appendsym(pics, x->sprite_manager.sprite[i].slide_path[j]);
        llll_appendllll(ll, symbol_and_llll_to_llll_chained(gensym("pics"), pics));
        llll_appendllll(ll, symbol_and_llll_to_llll_chained(gensym("rect"), rect_to_llll(x->sprite_manager.sprite[i].source_rect)));
		llll_appendllll(ll, symbol_and_long_to_llll(gensym("stretch"), x->sprite_manager.sprite[i].allow_stretch));
        llll_appendllll(ll, symbol_and_double_to_llll(gensym("slidetime"), x->sprite_manager.sprite[i].slide_time));
		llll_appendllll(out_ll, ll, 0, WHITENULL_llll);
	}
	llll_prependsym(out_ll, gensym("sprites"), 0, WHITENULL_llll);
	return out_ll;
}

t_llll *platform_get_prototypes(t_platform *x)
{
	long i;
	t_llll *out_ll = llll_get();
	for (i = 0; i < x->prototype_manager.num_prototypes; i++) {
		t_llll *ll = llll_get();
		llll_appendsym(ll, x->prototype_manager.prototypes[i].name);
        llll_appendsym(ll, itemtype_to_sym(x->prototype_manager.prototypes[i].type));
		llll_chain_clone(ll, x->prototype_manager.prototypes[i].attr);
		llll_appendllll(out_ll, ll, 0, WHITENULL_llll);
	}
	llll_prependsym(out_ll, gensym("prototypes"), 0, WHITENULL_llll);
	return out_ll;
}


t_llll *platform_get_gamechars(t_platform *x)
{
	return dadaitem_class_get_as_llll(dadaobj_cast(x), DADAITEM_TYPE_GAMECHAR);
} 


t_llll *platform_get_blocks(t_platform *x)
{
	
	return dadaitem_class_get_as_llll(dadaobj_cast(x), DADAITEM_TYPE_BLOCK);
}


t_llll *platform_get_coins(t_platform *x)
{
	return dadaitem_class_get_as_llll(dadaobj_cast(x), DADAITEM_TYPE_COIN);
}

t_llll *platform_get_portals(t_platform *x)
{
    return dadaitem_class_get_as_llll(dadaobj_cast(x), DADAITEM_TYPE_PORTAL);
}



t_llll *platform_get_state_ext(t_platform *x, char get_levelinfo, char get_sprites, char get_prototypes, char get_gamechars, char get_blocks, char get_coins, char get_portals)
{
	// How do we save the information?
	// Different sublists: 1) sprites, 2) prototypes 3) hero, 4) blocks, 5) coins
	// 1) sprites: (sprites SPRITE1 SPRITE2...) with SPRITE equal to (name (slide1_path slide2_path...) source_rect stretchable slide_time)
	// 3)4)5) in the standard attribute-based dictionary llll
	
	t_llll *data = llll_get();
	
    llll_appendsym(data, gensym("platform"));

    if (get_levelinfo)
        llll_appendllll(data, platform_get_levelinfo(x), 0, WHITENULL_llll);
	if (get_sprites)
		llll_appendllll(data, platform_get_sprites(x), 0, WHITENULL_llll);
	if (get_prototypes)
		llll_appendllll(data, platform_get_prototypes(x), 0, WHITENULL_llll);
	if (get_gamechars)
		llll_appendllll(data, platform_get_gamechars(x), 0, WHITENULL_llll);
	if (get_blocks)
		llll_appendllll(data, platform_get_blocks(x), 0, WHITENULL_llll);
	if (get_coins)
		llll_appendllll(data, platform_get_coins(x), 0, WHITENULL_llll);
    if (get_portals)
        llll_appendllll(data, platform_get_portals(x), 0, WHITENULL_llll);
	
	return data;
}

t_llll *platform_get_state(t_platform *x)
{
    return platform_get_state_ext(x, true, true, true, true, true, true, true);
}

void platform_ezadd_sprite(t_platform *x, t_symbol *name, t_rect source_rect, char allow_stretch, double slide_time, long num_slides, ...)
{
	va_list arguments;                     
    va_start (arguments, num_slides);           
	t_symbol *sprites[num_slides];

	long i;
	for (i = 0; i < num_slides; i++)
		sprites[i] = va_arg (arguments, t_symbol *);
	
	if (x->sprite_manager.num_sprites < DADA_PLATFORM_MAX_SPRITES) {
		long n = x->sprite_manager.num_sprites;
		sprite_init(&x->sprite_manager.sprite[n], name, &source_rect, allow_stretch, slide_time, num_slides, sprites);
		x->sprite_manager.num_sprites++;
	}
	
    va_end ( arguments ); 
	
	/*
	va_list arguments;                     
	
    va_start (arguments, num_slides);           
	
	if (x->sprite_manager.num_sprites < DADA_PLATFORM_MAX_SPRITES) {
		long n = x->sprite_manager.num_sprites;
		x->sprite_manager.sprite[n].name = name;
		x->sprite_manager.sprite[n].source_rect = source_rect;
		x->sprite_manager.sprite[n].slide_time = slide_time;
		x->sprite_manager.sprite[n].num_slides = 0;
		x->sprite_manager.sprite[n].allow_stretch = allow_stretch;
		
		long j;
		for (j = 0; j < num_slides && j < DADA_MAX_SLIDES_PER_SPRITE; j++) {
			x->sprite_manager.sprite[n].slide_path[x->sprite_manager.sprite[n].num_slides] = va_arg (arguments, t_symbol *);
			x->sprite_manager.sprite[n].slide_right[x->sprite_manager.sprite[n].num_slides] = get_surface_from_file(x->sprite_manager.sprite[n].slide_path[x->sprite_manager.sprite[n].num_slides]);
			x->sprite_manager.sprite[n].slide_left[x->sprite_manager.sprite[n].num_slides] = clone_surface(x->sprite_manager.sprite[n].slide_right[x->sprite_manager.sprite[n].num_slides], true, false);
			x->sprite_manager.sprite[n].num_slides++;
		}
		
		x->sprite_manager.num_sprites++;
	}

    va_end ( arguments ); 
	 */
}

void platform_add_sprite(t_platform *x, t_llll *sprite)
{
	t_symbol *name = _llllobj_sym_none;
	t_rect source_rect = build_rect(0, 0, 0, 0);
	double slide_time = 150;
	t_llll *slides = NULL;
	long allow_stretch = 0;
    
    dadaobj_parseargs(dadaobj_cast(x), sprite, (char *)"s4Rld", gensym("name"), &name, gensym("pics"), &slides, gensym("rect"), &source_rect, gensym("stretch"), &allow_stretch, gensym("slidetime"), &slide_time);

//	dadaobj_parse_llll(dadaobj_cast(x), sprite, (char *)"s4Rld", &name, &slides, &source_rect, &allow_stretch, &slide_time);
	
	long n = x->sprite_manager.num_sprites;
	if (n < DADA_PLATFORM_MAX_SPRITES) {
		x->sprite_manager.sprite[n].name = name;
		x->sprite_manager.sprite[n].source_rect = source_rect;
		x->sprite_manager.sprite[n].slide_time = slide_time;
		x->sprite_manager.sprite[n].num_slides = 0;
		x->sprite_manager.sprite[n].allow_stretch = allow_stretch;
		
		if (slides) {
			t_llllelem *subelem;
			long j;
			for (subelem = slides->l_head, j = 0; j < (long)slides->l_size && j < DADA_MAX_SLIDES_PER_SPRITE && subelem; j++, subelem = subelem->l_next) {
				if (hatom_gettype(&subelem->l_hatom) == H_SYM) {
					t_symbol *s = hatom_getsym(&subelem->l_hatom);
					x->sprite_manager.sprite[n].slide_path[x->sprite_manager.sprite[n].num_slides] = s;
					x->sprite_manager.sprite[n].slide_right[x->sprite_manager.sprite[n].num_slides] = get_surface_from_file(s);
					x->sprite_manager.sprite[n].slide_left[x->sprite_manager.sprite[n].num_slides] = clone_surface(x->sprite_manager.sprite[n].slide_right[x->sprite_manager.sprite[n].num_slides], true, false);
					x->sprite_manager.sprite[n].num_slides++;
				}
			}
		}
		
		x->sprite_manager.num_sprites++;
	}
}

void platform_free_sprite(t_platform *x, t_dada_sprite *sprite)
{
    long i;
    for (i = 0; i < sprite->num_slides; i++) {
        if (sprite->slide_left[i])
            jgraphics_surface_destroy(sprite->slide_left[i]);
        if (sprite->slide_right[i])
            jgraphics_surface_destroy(sprite->slide_right[i]);
    }
}

void platform_free_all_sprites(t_platform *x)
{
    long i;
    for (i = 0; i < x->sprite_manager.num_sprites; i++)
        platform_free_sprite(x, &(x->sprite_manager.sprite[i]));
}


void platform_set_sprites(t_platform *x, t_llll *sprites)
{
	long i;
	t_llllelem *elem;
	
    platform_free_all_sprites(x);
	x->sprite_manager.num_sprites = 0;
	
	for (i = 0, elem = sprites->l_head ? sprites->l_head->l_next : NULL; elem && i < DADA_PLATFORM_MAX_SPRITES; elem = elem->l_next, i++) {
		if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
			t_llll *ll = hatom_getllll(&elem->l_hatom);
			platform_add_sprite(x, ll);
		}
	}
}




void platform_ezadd_prototype(t_platform *x, t_symbol *name, t_llll *attr)
{
	long n = x->prototype_manager.num_prototypes;
	if (n < DADA_PLATFORM_MAX_PROTOTYPES) {
		x->prototype_manager.prototypes[n].name = name;
		x->prototype_manager.prototypes[n].attr = attr;
		
		x->prototype_manager.num_prototypes++;
	}
}

void platform_ezadd_prototype_from_dadaitem(t_platform *x, t_symbol *name, t_dadaitem *item)
{
	platform_ezadd_prototype(x, name, dadaitem_get_as_llll(dadaobj_cast(x), item));
}

void platform_add_items_from_prototype(t_platform *x, t_symbol *prototype_name, e_dadaitem_types type, char *positions, long flags)
{
	t_llll *pos = llll_from_text_buf(positions, false);
	t_llllelem *elem;
	t_platform_prototype *prototype = label_to_prototype(x, prototype_name);
	
	for (elem = pos->l_head; elem; elem = elem->l_next) {
		if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
			t_dadaitem *item = dadaitem_add_from_llll(dadaobj_cast(x), type, prototype->attr, flags);
			dadaitem_set_attr_from_llll(dadaobj_cast(x), item, get_bach_attribute(x->b_ob.d_ob.m_inspector.attr_manager, dadaitem_class_get_id(&x->b_ob.d_ob.m_classes, type), gensym("coord")), hatom_getllll(&elem->l_hatom), false);
		}
	}
	
    llll_free(pos);  
}

t_dadaitem *platform_add_single_item_from_prototype(t_platform *x, t_symbol *prototype_name, e_dadaitem_types type, t_pt coord, long flags)
{
    t_platform_prototype *prototype = label_to_prototype(x, prototype_name);
    
    t_dadaitem *item = dadaitem_add_from_llll(dadaobj_cast(x), type, prototype->attr, flags);
    if (item)
        item->coord = coord;
    return item;
}


t_dadaitem *platform_change_single_item_from_prototype(t_platform *x, t_dadaitem *item, t_symbol *prototype_name, long flags)
{
    t_platform_prototype *prototype = label_to_prototype(x, prototype_name);
    if (prototype) {
        t_pt coord = item->coord;
        dadaitem_set_from_llll(dadaobj_cast(x), item, prototype->attr, flags);
        item->coord = coord;
    }
    return item;
}


t_symbol *infer_prototype_type_from_name(t_symbol *name)
{
    if (name == gensym("block") || name == gensym("ground") || name == gensym("note") || name == gensym("brick") || name == gensym("wood"))
        return gensym("block");

    if (name == gensym("coin"))
        return gensym("coin");

    if (name == gensym("pipe") || name == gensym("piperev") || name == gensym("door") || name == gensym("portal"))
        return gensym("portal");
        
    return gensym("gamechar");
}

void platform_add_prototype(t_platform *x, t_llll *prototype)
{
	if (prototype && prototype->l_size >= 2 && hatom_gettype(&prototype->l_head->l_hatom) == H_SYM) {
		t_symbol *name = hatom_getsym(&prototype->l_head->l_hatom);
        t_symbol *type;
        t_llll *attr;

        if (hatom_gettype(&prototype->l_head->l_next->l_hatom) == H_SYM) {
            type = hatom_getsym(&prototype->l_head->l_next->l_hatom);
            attr = llll_behead(llll_behead(llll_clone(prototype)));
        } else {
            type = infer_prototype_type_from_name(name);
            attr = llll_behead(llll_clone(prototype));
        }
        
		long n = x->prototype_manager.num_prototypes;
		if (n < DADA_PLATFORM_MAX_PROTOTYPES) {
			x->prototype_manager.prototypes[n].name = name;
            x->prototype_manager.prototypes[n].type = itemsym_to_type(type);
			x->prototype_manager.prototypes[n].attr = attr;
			x->prototype_manager.num_prototypes++;
		}
	}
}

void platform_free_prototype(t_platform *x, t_platform_prototype *proto)
{
    llll_free(proto->attr);
}

void platform_free_all_prototypes(t_platform *x)
{
    long i;
    for (i = 0; i < x->prototype_manager.num_prototypes; i++)
        platform_free_prototype(x, &(x->prototype_manager.prototypes[i]));
}


void platform_set_prototypes(t_platform *x, t_llll *sprites)
{
	long i;
	t_llllelem *elem;
	
    platform_free_all_prototypes(x);
    
	x->prototype_manager.num_prototypes = 0;
	
	for (i = 0, elem = sprites->l_head ? sprites->l_head->l_next : NULL; elem && i < DADA_PLATFORM_MAX_SPRITES; elem = elem->l_next, i++) {
		if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
			t_llll *ll = hatom_getllll(&elem->l_hatom);
			platform_add_prototype(x, ll);
		}
	}
}


void platform_set_levelinfo(t_platform *x, t_llll *levelinfo)
{
    t_symbol *title = NULL, *bgsprite = NULL, *hero = NULL;
    t_jrgba textcolor = DADA_BLACK;
    double gravity = DADA_PLATFORM_DEFAULT_GRAVITY, height = 10, width = 100, ground_friction = 5, air_friction = 1;
    t_llll *maxtime = NULL;
    long intro = false;
    
    dadaobj_parseargs(dadaobj_cast(x), levelinfo, (char *)"sssd4ddddCl", gensym("title"), &title, gensym("hero"), &hero, gensym("bgsprite"), &bgsprite, gensym("gravity"), &gravity, gensym("maxtime"), &maxtime, gensym("height"), &height, gensym("width"), &width, gensym("groundfriction"), &ground_friction, gensym("airfriction"), &air_friction, gensym("textcolor"), &textcolor, gensym("intro"), &intro);

    x->m_level.levelname = title;
    x->m_level.background_sprite = bgsprite;
    x->m_level.gravity = gravity;
    if (maxtime) {
        if (maxtime->l_head && is_hatom_number(&maxtime->l_head->l_hatom))
            atom_setfloat(&x->m_level.maxtime, hatom_getdouble(&maxtime->l_head->l_hatom));
        else
            atom_setsym(&x->m_level.maxtime, _llllobj_sym_none);
    }
    object_attr_setsym((t_object *)x, gensym("hero"), hero);
    x->m_level.level_height = height;
    x->m_level.level_width = width;
    x->m_level.ground_friction = ground_friction;
    x->m_level.air_friction = air_friction;
    x->m_level.j_textcolor = textcolor;
    x->m_level.has_intro = intro;
    
    platform_check_autozoom(x);

    update_hero_fields(x);
}


void platform_set_gamechars(t_platform *x, t_llll *gamechars)
{
    platform_clear_gamechars(x, 0);
	dadaitem_class_set_from_llll(dadaobj_cast(x), DADAITEM_TYPE_GAMECHAR, gamechars, DIA_USE_ATTR_DEFAULTS);
}


void platform_set_coins(t_platform *x, t_llll *coins)
{
    platform_clear_coins(x, 0);
	dadaitem_class_set_from_llll(dadaobj_cast(x), DADAITEM_TYPE_COIN, coins, DIA_USE_ATTR_DEFAULTS);
}

void platform_set_portals(t_platform *x, t_llll *portals)
{
    platform_clear_portals(x, 0);
    dadaitem_class_set_from_llll(dadaobj_cast(x), DADAITEM_TYPE_PORTAL, portals, DIA_USE_ATTR_DEFAULTS);
}


void platform_set_blocks(t_platform *x, t_llll *blocks)
{
    platform_clear_blocks(x, 0);
	dadaitem_class_set_from_llll(dadaobj_cast(x), DADAITEM_TYPE_BLOCK, blocks, DIA_USE_ATTR_DEFAULTS);
}


// see platform_get_state about the codification of info
void platform_set_state(t_platform *x, t_llll *state)
{
	t_llllelem *elem;
    t_llll *levelinfo = NULL;
	x->itsme = true;
	
    t_llll *hero_as_llll = NULL;
    if (x->hero && x->goto_options.keephero)
        hero_as_llll = dadaitem_get_as_llll(dadaobj_cast(x), (t_dadaitem *)x->hero);

	for (elem = state->l_head; elem; elem = elem->l_next) {
		if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
			t_llll *ll = hatom_getllll(&elem->l_hatom);
			if (ll && ll->l_head && hatom_gettype(&ll->l_head->l_hatom) == H_SYM) {
				t_symbol *sym = hatom_getsym(&ll->l_head->l_hatom);
                if (sym == gensym("levelinfo"))
                    levelinfo = ll;
				else if (sym == gensym("sprites"))
					platform_set_sprites(x, ll);
				else if (sym == gensym("prototypes"))
					platform_set_prototypes(x, ll);
				else if (sym == gensym("gamechars"))
					platform_set_gamechars(x, ll);
				else if (sym == gensym("blocks"))
					platform_set_blocks(x, ll);
				else if (sym == gensym("coins")) 
					platform_set_coins(x, ll);
                else if (sym == gensym("portals"))
                    platform_set_portals(x, ll);
			}
		}
	}
    
    if (levelinfo) // must be done later, because it defines the hero
        platform_set_levelinfo(x, levelinfo);


	x->itsme = false;

	// reprocess stuff
    jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));

    // charging options
    if (x->goto_options.intro > 0 || x->m_level.has_intro) {
        x->play_state = DADA_PLATFORM_PLAYSTATE_LEVELINTRO_PRE;
    } else {
        x->play_state = DADA_PLATFORM_PLAYSTATE_STANDARD;
    }
    
    if (x->goto_options.resettime > 0)
        x->global_time = 0;

    if (x->hero && hero_as_llll) {
        const long NUM_ROUTERS_TO_REMOVE = 10;
        t_symbol *ROUTERS_TO_REMOVE[10];
        ROUTERS_TO_REMOVE[0] = gensym("coord");
        ROUTERS_TO_REMOVE[1] = gensym("speed");
        ROUTERS_TO_REMOVE[2] = gensym("direction");
        ROUTERS_TO_REMOVE[3] = gensym("state");
        ROUTERS_TO_REMOVE[4] = gensym("idlesprite");
        ROUTERS_TO_REMOVE[5] = gensym("walksprite");
        ROUTERS_TO_REMOVE[6] = gensym("jumpsprite");
        ROUTERS_TO_REMOVE[7] = gensym("glidesprite");
        ROUTERS_TO_REMOVE[8] = gensym("flysprite");
        ROUTERS_TO_REMOVE[9] = gensym("deadsprite");
        remove_subllll_with_routers(hero_as_llll, NUM_ROUTERS_TO_REMOVE, ROUTERS_TO_REMOVE);
        dadaitem_set_from_llll(dadaobj_cast(x), (t_dadaitem *)x->hero, hero_as_llll, 0);
        
        llll_free(hero_as_llll);
    } else {
        if (x->hero && x->goto_options.herovp >= 0)
            x->hero->vp = x->goto_options.herovp;
        if (x->hero && x->goto_options.heropoints >= 0)
            x->hero->points = x->goto_options.heropoints;
    }

    if (x->goto_options.goto_portal)
        platform_portal_exit(x, x->hero, platform_symbol_to_single_portal(x, x->goto_options.goto_portal, (t_dadaitem *)x->hero));

    process_change(x);
}

void platform_undo_step_push(t_platform *x, t_symbol *operation)
{
    undo_add_interface_step(dadaobj_cast(x), DADA_FUNC_v_oX, (method)platform_set_state, NULL, DADA_FUNC_X_o, (method)platform_get_state, NULL, DADA_UNDO_OP_MODIFICATION, operation);
}


void platform_levelinfo_undo_step_push(t_platform *x, t_symbol *operation)
{
    undo_add_interface_step(dadaobj_cast(x), DADA_FUNC_v_oX, (method)platform_set_levelinfo, NULL, DADA_FUNC_X_o, (method)platform_get_levelinfo, NULL, DADA_UNDO_OP_MODIFICATION, operation);
}

void platform_sprites_undo_step_push(t_platform *x, t_symbol *operation)
{
    undo_add_interface_step(dadaobj_cast(x), DADA_FUNC_v_oX, (method)platform_set_sprites, NULL, DADA_FUNC_X_o, (method)platform_get_sprites, NULL, DADA_UNDO_OP_MODIFICATION, operation);
}

void platform_prototypes_undo_step_push(t_platform *x, t_symbol *operation)
{
    undo_add_interface_step(dadaobj_cast(x), DADA_FUNC_v_oX, (method)platform_set_prototypes, NULL, DADA_FUNC_X_o, (method)platform_get_prototypes, NULL, DADA_UNDO_OP_MODIFICATION, operation);
}

void platform_clear_sprites(t_platform *x, long flags)
{
    platform_sprites_undo_step_push(x, gensym("Clear Sprites"));
    platform_free_all_sprites(x);
    x->sprite_manager.num_sprites = 0;
}

void platform_clear_prototypes(t_platform *x, long flags)
{
    if (flags & DIA_UNDO)
        platform_sprites_undo_step_push(x, gensym("Clear Prototypes"));
    platform_free_all_prototypes(x);
    x->prototype_manager.num_prototypes = 0;
}

void platform_clear_levelinfo(t_platform *x, long flags)
{
    if (flags & DIA_UNDO)
        platform_levelinfo_undo_step_push(x, gensym("Clear Levelinfo"));
    x->m_level.background_sprite = gensym("none");
    x->m_level.levelname = gensym("none");
    x->m_level.gravity = DADA_PLATFORM_DEFAULT_GRAVITY;
    atom_setsym(&x->m_level.maxtime, _llllobj_sym_none);
    x->m_level.has_intro = false;
}

void platform_clear_portals(t_platform *x, long flags)
{
    dadaitem_class_clear(dadaobj_cast(x), &x->b_ob.d_ob.m_classes, &x->b_ob.d_ob.m_interface, &x->b_ob.d_ob.m_undo, DADAITEM_TYPE_PORTAL, flags);
}

void platform_clear_coins(t_platform *x, long flags)
{
    dadaitem_class_clear(dadaobj_cast(x), &x->b_ob.d_ob.m_classes, &x->b_ob.d_ob.m_interface, &x->b_ob.d_ob.m_undo, DADAITEM_TYPE_COIN, flags);
 }

void platform_clear_blocks(t_platform *x, long flags)
{
    dadaitem_class_clear(dadaobj_cast(x), &x->b_ob.d_ob.m_classes, &x->b_ob.d_ob.m_interface, &x->b_ob.d_ob.m_undo, DADAITEM_TYPE_BLOCK, flags);
}

void platform_clear_gamechars(t_platform *x, long flags)
{
    dadaitem_class_clear(dadaobj_cast(x), &x->b_ob.d_ob.m_classes, &x->b_ob.d_ob.m_interface, &x->b_ob.d_ob.m_undo, DADAITEM_TYPE_GAMECHAR, flags);
    x->hero = NULL;
    x->hero_ID = 0;
}

void platform_clear(t_platform *x, char clear_levelinfo, char clear_sprites, char clear_prototypes, char clear_gamechars, char clear_blocks, char clear_coins, char clear_portals, long flags)
{
    if (clear_levelinfo)
        platform_clear_levelinfo(x, flags);
    if (clear_sprites)
        platform_clear_sprites(x, flags);
    if (clear_prototypes)
        platform_clear_prototypes(x, flags);
    if (clear_gamechars)
        platform_clear_gamechars(x, flags);
    if (clear_blocks)
        platform_clear_blocks(x, flags);
    if (clear_coins)
        platform_clear_coins(x, flags);
    if (clear_portals)
        platform_clear_portals(x, flags);
}




void platform_assist(t_platform *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type anything @digest Incoming symbol or list
		sprintf(s, "Incoming symbol or list");
	} 
	else {	
		if (a == 0)	// @out 0 @type llll @digest Dump outlet
			sprintf(s, "Dump Outlet"); 			
		else if (a == 1)	// @out 1 @type llll @digest Queries and notifications
			sprintf(s, "Queries and Notifications"); 			
        else if (a == 2)	// @out 2 @type llll @digest Playout
            sprintf(s, "Playout");
		else 	// @out 3 @type bang @digest bang when object is changed via the interface
			sprintf(s, "bang when Changed"); 			
	}
}

void platform_free(t_platform *x)
{
	long i;
	
	llll_free(x->floattext_to_be_displayed);
    llll_free(x->breakingblocks);
    llll_free(x->fixed_state);
    
	// freeing sprites 
	for (i = 0; i < x->sprite_manager.num_sprites; i++) 
		sprite_free(&x->sprite_manager.sprite[i]);
	
	// freeing prototypes
	for (i = 0; i < x->prototype_manager.num_prototypes; i++) 
		llll_free(x->prototype_manager.prototypes[i].attr);
	
	object_free_debug(x->n_proxy1);
	dadaobj_jbox_free((t_dadaobj_jbox *)x); // jbox_free and llllobj_free are inside here
}

void platform_iar(t_platform *x)
{
    jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
    jbox_redraw((t_jbox *)x);
}

void remove_subllll_with_routers(t_llll *ll, long num_routers, t_symbol **router)
{
    t_llllelem *elem, *nextelem;
    for (elem = ll->l_head; elem; elem = nextelem) {
        nextelem = elem->l_next;
        if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
            t_llll *subll = hatom_getllll(&elem->l_hatom);
            for (long i = 0; i < num_routers; i++) {
                if (subll && subll->l_head && hatom_gettype(&subll->l_head->l_hatom) == H_SYM && hatom_getsym(&subll->l_head->l_hatom) == router[i]) {
                    llll_destroyelem(elem);
                    break;
                }
            }
        }
    }
}

void platform_dadaitem_getattr_prototype(t_bach_inspector_manager *man, void *obj, t_bach_attribute *attr, long *ac, t_atom **av)
{
    if (ac && av) {
        // check if coincides with prototype
        t_platform *x = (t_platform *)man->owner;
        t_dadaitem *item = (t_dadaitem *)obj;
        *av = (t_atom *)bach_newptr(sizeof(t_atom));
        *ac = 1;
        
        long i;
        const long NUM_ROUTERS_TO_REMOVE = 6;
        t_symbol *ROUTERS_TO_REMOVE[6];
        ROUTERS_TO_REMOVE[0] = gensym("coord");
        ROUTERS_TO_REMOVE[1] = gensym("speed");
        ROUTERS_TO_REMOVE[2] = gensym("hitcount");
        ROUTERS_TO_REMOVE[3] = gensym("points");
        ROUTERS_TO_REMOVE[4] = gensym("vp");
        ROUTERS_TO_REMOVE[5] = gensym("direction");

        t_llll *this_attrs = dadaitem_get_as_llll(dadaobj_cast(x), item);
        remove_subllll_with_routers(this_attrs, NUM_ROUTERS_TO_REMOVE, ROUTERS_TO_REMOVE);
        for (i = 0; i < x->prototype_manager.num_prototypes; i++) {
            t_llll *prototype_attrs = llll_clone(x->prototype_manager.prototypes[i].attr);
            remove_subllll_with_routers(prototype_attrs, NUM_ROUTERS_TO_REMOVE, ROUTERS_TO_REMOVE);
            if (llll_eq_ignoretype(prototype_attrs, this_attrs)) {
                atom_setsym(*av, x->prototype_manager.prototypes[i].name);
                llll_free(prototype_attrs);
                return;
            }
            llll_free(prototype_attrs);
        }
        llll_free(this_attrs);
        
        atom_setsym(*av, _llllobj_sym_none);
        return;
    }
}


void platform_dadaitem_setattr_prototype(t_bach_inspector_manager *man, void *obj, t_bach_attribute *attr, long ac, t_atom *av)
{
    t_platform *x = (t_platform *)man->owner;
    if (ac && av && atom_gettype(av) == A_SYM && atom_getsym(av) != _llllobj_sym_none) {
        platform_change_single_item_from_prototype(x, (t_dadaitem *)obj, atom_getsym(av), 0);
    }
}




void platform_gamechar_getattr_state(t_bach_inspector_manager *man, void *obj, t_bach_attribute *attr, long *ac, t_atom **av)
{
    if (ac && av) {
        t_dada_gamechar *gamechar = (t_dada_gamechar *)obj;
        t_llll *ll = dadaitem_gamechar_state_to_llll(gamechar->state);
        *ac = llll_deparse(ll, av, 0, 0);
        llll_free(ll);
    }
}


void platform_gamechar_setattr_state(t_bach_inspector_manager *man, void *obj, t_bach_attribute *attr, long ac, t_atom *av)
{
    t_llll *ll = llll_parse(ac, av);
    t_dada_gamechar *gamechar = (t_dada_gamechar *)obj;
    gamechar->state = dadaitem_gamechar_llll_to_state(ll);
    llll_free(ll);
}

void platform_gamechar_getattr_ability(t_bach_inspector_manager *man, void *obj, t_bach_attribute *attr, long *ac, t_atom **av)
{
    if (ac && av) {
        t_dada_gamechar *gamechar = (t_dada_gamechar *)obj;
        t_llll *ll = dadaitem_gamechar_ability_to_llll(gamechar->abilities);
        *ac = llll_deparse(ll, av, 0, 0);
        llll_free(ll);
    }
}


void platform_gamechar_setattr_ability(t_bach_inspector_manager *man, void *obj, t_bach_attribute *attr, long ac, t_atom *av)
{
    t_llll *ll = llll_parse(ac, av);
    t_dada_gamechar *gamechar = (t_dada_gamechar *)obj;
    gamechar->abilities = dadaitem_gamechar_llll_to_ability(ll);
    llll_free(ll);
}

void platform_gamechar_getattr_type(t_bach_inspector_manager *man, void *obj, t_bach_attribute *attr, long *ac, t_atom **av)
{
    if (ac && av) {
        t_dada_gamechar *gamechar = (t_dada_gamechar *)obj;
        *av = (t_atom *)bach_newptr(sizeof(t_atom));
        *ac = 1;
        atom_setsym(*av, dadaitem_gamechar_type_to_symbol(gamechar->type));
    }
}


void platform_gamechar_setattr_type(t_bach_inspector_manager *man, void *obj, t_bach_attribute *attr, long ac, t_atom *av)
{
    if (ac && av) {
        t_dada_gamechar *gamechar = (t_dada_gamechar *)obj;
        if (atom_gettype(av) == A_SYM)
            gamechar->type = dadaitem_gamechar_symbol_to_type(atom_getsym(av));
        else if (atom_gettype(av) == A_LONG)
            gamechar->type = atom_getlong(av);
    }
}



void platform_gamechar_getattr_howdies(t_bach_inspector_manager *man, void *obj, t_bach_attribute *attr, long *ac, t_atom **av)
{
    if (ac && av) {
        t_dada_gamechar *gamechar = (t_dada_gamechar *)obj;
        t_llll *ll = dadaitem_gamechar_via_to_llll(gamechar->how_dies);
        *ac = llll_deparse(ll, av, 0, 0);
        llll_free(ll);
    }
}


void platform_gamechar_setattr_howdies(t_bach_inspector_manager *man, void *obj, t_bach_attribute *attr, long ac, t_atom *av)
{
    t_llll *ll = llll_parse(ac, av);
    t_dada_gamechar *gamechar = (t_dada_gamechar *)obj;
    gamechar->how_dies = dadaitem_llll_to_via(ll);
    llll_free(ll);
}


void platform_gamechar_getattr_howkills(t_bach_inspector_manager *man, void *obj, t_bach_attribute *attr, long *ac, t_atom **av)
{
    if (ac && av) {
        t_dada_gamechar *gamechar = (t_dada_gamechar *)obj;
        t_llll *ll = dadaitem_gamechar_via_to_llll(gamechar->how_kills);
        *ac = llll_deparse(ll, av, 0, 0);
        llll_free(ll);
    }
}


void platform_gamechar_setattr_howkills(t_bach_inspector_manager *man, void *obj, t_bach_attribute *attr, long ac, t_atom *av)
{
    t_llll *ll = llll_parse(ac, av);
    t_dada_gamechar *gamechar = (t_dada_gamechar *)obj;
    gamechar->how_kills = dadaitem_llll_to_via(ll);
    llll_free(ll);
}




void platform_gamechar_getattr_howhit(t_bach_inspector_manager *man, void *obj, t_bach_attribute *attr, long *ac, t_atom **av)
{
    if (ac && av) {
        t_dada_block *block = (t_dada_block*)obj;
        t_llll *ll = dadaitem_gamechar_via_to_llll(block->how_bumpeable);
        *ac = llll_deparse(ll, av, 0, 0);
        llll_free(ll);
    }
}


void platform_gamechar_setattr_howhit(t_bach_inspector_manager *man, void *obj, t_bach_attribute *attr, long ac, t_atom *av)
{
    t_llll *ll = llll_parse(ac, av);
    t_dada_block *block = (t_dada_block *)obj;
    block->how_bumpeable = dadaitem_llll_to_via(ll);
    llll_free(ll);
}


void platform_gamechar_getattr_howenter(t_bach_inspector_manager *man, void *obj, t_bach_attribute *attr, long *ac, t_atom **av)
{
    if (ac && av) {
        t_dada_portal *block = (t_dada_portal*)obj;
        t_llll *ll = dadaitem_gamechar_via_to_llll(block->how_enter);
        *ac = llll_deparse(ll, av, 0, 0);
        llll_free(ll);
    }
}


void platform_gamechar_setattr_howenter(t_bach_inspector_manager *man, void *obj, t_bach_attribute *attr, long ac, t_atom *av)
{
    t_llll *ll = llll_parse(ac, av);
    t_dada_portal *block = (t_dada_portal *)obj;
    block->how_enter = dadaitem_llll_to_via(ll);
    llll_free(ll);
}


void platform_gamechar_getattr_howexit(t_bach_inspector_manager *man, void *obj, t_bach_attribute *attr, long *ac, t_atom **av)
{
    if (ac && av) {
        t_dada_portal *block = (t_dada_portal*)obj;
        t_llll *ll = dadaitem_gamechar_via_to_llll(block->how_exit);
        *ac = llll_deparse(ll, av, 0, 0);
        llll_free(ll);
    }
}


void platform_gamechar_setattr_howexit(t_bach_inspector_manager *man, void *obj, t_bach_attribute *attr, long ac, t_atom *av)
{
    t_llll *ll = llll_parse(ac, av);
    t_dada_portal *block = (t_dada_portal *)obj;
    block->how_exit = dadaitem_llll_to_via(ll);
    llll_free(ll);
}






void *platform_new(t_symbol *s, long argc, t_atom *argv)
{
	t_platform *x = NULL;
	t_dictionary *d = NULL;
	long boxflags;
	t_llll *llll_for_rebuild = NULL;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;    
	
	if ((x = (t_platform *)object_alloc_debug(platform_class))) {
		
		x->creating_new_obj = true;
        x->play_state = DADA_PLATFORM_PLAYSTATE_LEVELINTRO;
		
		x->floattext_to_be_displayed = llll_get();
        x->breakingblocks = llll_get();
		x->firsttime = true;

        load_default_goto_options(x);
        
        x->die_y_line = -1;
		
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

		dadaobj_jbox_setup((t_dadaobj_jbox *)x, DADAOBJ_BORDER | DADAOBJ_ZOOM | DADAOBJ_CENTEROFFSETX | DADAOBJ_UNDO | DADAOBJ_SELECTION | DADAOBJ_CHANGEDBANG | DADAOBJ_INSPECTOR | DADAOBJ_NOTIFICATIONS | DADAOBJ_PLAY, build_pt(16., 16.), 2, 3, DADA_PLATFORM_NOTIFICATION_OUTLET, (dada_paint_ext_fn)platform_paint_ext, (invalidate_and_redraw_fn)platform_iar, "a", 2, "b444");
		dadaobj_addfunctions(dadaobj_cast(x), (dada_mousemove_fn)platform_mousemove, (method)platform_task, (method)platform_undo_postprocess, (get_state_fn)platform_get_state, (set_state_fn)platform_set_state, (pixel_to_dadaitem_fn)platform_pixel_to_dadaitem, NULL, NULL);

		x->b_ob.d_ob.m_tools.curr_tool = DADA_TOOL_ARROW;
		x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;

		x->sprite_manager.sprite = (t_dada_sprite *)bach_newptrclear(DADA_PLATFORM_MAX_SPRITES * sizeof(t_dada_sprite));
		
//		long l1 = calcoffset(t_platform, blocks);
//		long l2 = dadaobj_jbox_calcoffset(t_platform, blocks);
		
        dadaobj_dadaitem_class_ezalloc(dadaobj_cast(x), DADAITEM_TYPE_GAMECHAR, gensym("gamechar"), gensym("Game Character"), DADA_ITEM_ALLOC_OBJLLLL, 0, true, sizeof(t_dada_gamechar), calcoffset(t_platform, gamechars), DADA_PLATFORM_MAX_GAMECHARS, NULL, NULL, (method)dadaitem_gamechar_free, true, false);
		dadaobj_dadaitem_class_ezalloc(dadaobj_cast(x), DADAITEM_TYPE_BLOCK, gensym("block"), gensym("Block"), DADA_ITEM_ALLOC_OBJLLLL, 0, true, sizeof(t_dada_block), calcoffset(t_platform, blocks), DADA_PLATFORM_MAX_BLOCKS, NULL, NULL, (method)dadaitem_block_free, true, false);
		dadaobj_dadaitem_class_ezalloc(dadaobj_cast(x), DADAITEM_TYPE_COIN, gensym("coin"), gensym("Coin"), DADA_ITEM_ALLOC_OBJLLLL, 0, true, sizeof(t_dada_coin), calcoffset(t_platform, coins), DADA_PLATFORM_MAX_COINS, NULL, NULL, (method)dadaitem_coin_free, true, false);
        dadaobj_dadaitem_class_ezalloc(dadaobj_cast(x), DADAITEM_TYPE_PORTAL, gensym("portal"), gensym("Portal"), DADA_ITEM_ALLOC_OBJLLLL, 0, true, sizeof(t_dada_portal), calcoffset(t_platform, portals), DADA_PLATFORM_MAX_PORTALS, NULL, NULL, (method)dadaitem_portal_free, true, false);

        dadaitem_init(dadaobj_cast(x), &x->m_level.r_it, DADAITEM_TYPE_LEVEL, 0, false, 0);
#ifdef DADA_PLATFORM_LEVEL_HAS_INSPECTOR
        dadaobj_dadaitem_class_alloc(dadaobj_cast(x), DADAITEM_TYPE_LEVEL, gensym("level"), gensym("Level"), DADA_ITEM_ALLOC_DONT, 0, 0, sizeof(t_levelinfo), calcoffset(t_platform, m_level), 1, NULL, DADA_FUNC_v_oX, (method)platform_set_levelinfo, NULL, DADA_FUNC_X_o, (method)platform_get_levelinfo, NULL, NULL, NULL, NULL, false, true);
//        dadaobj_dadaitem_class_ezalloc(dadaobj_cast(x), DADAITEM_TYPE_LEVEL, gensym("level"), gensym("Level"), DADA_ITEM_ALLOC_DONT, 0, false, sizeof(t_levelinfo), calcoffset(t_platform, m_level), 1, NULL, NULL, NULL, false, true);
#endif
        
		dadaobj_dadaitem_class_add_single_set_get_func(dadaobj_cast(x), DADAITEM_TYPE_BLOCK, DADA_FUNC_v_diX, (method)dadaitem_set_from_llll_ID, NULL, DADA_FUNC_X_di, (method)dadaitem_get_as_llll_ID, NULL);
        dadaobj_dadaitem_class_add_single_set_get_func(dadaobj_cast(x), DADAITEM_TYPE_COIN, DADA_FUNC_v_diX, (method)dadaitem_set_from_llll_ID, NULL, DADA_FUNC_X_di, (method)dadaitem_get_as_llll_ID, NULL);
        dadaobj_dadaitem_class_add_single_set_get_func(dadaobj_cast(x), DADAITEM_TYPE_GAMECHAR, DADA_FUNC_v_diX, (method)dadaitem_set_from_llll_ID, NULL, DADA_FUNC_X_di, (method)dadaitem_get_as_llll_ID, NULL);

		
		t_bach_attr_manager *man = x->b_ob.d_ob.m_inspector.attr_manager;
        t_bach_attribute *prototype_attr;
        
#ifdef DADA_PLATFORM_LEVEL_HAS_INSPECTOR
        // LEVEL
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("title"), (char *)"Title", DADAITEM_TYPE_LEVEL, t_levelinfo, levelname, k_BACH_ATTR_SYM, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("width"), (char *)"Width", DADAITEM_TYPE_LEVEL, t_levelinfo, level_width, k_BACH_ATTR_DOUBLE, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("height"), (char *)"Height", DADAITEM_TYPE_LEVEL, t_levelinfo, level_height, k_BACH_ATTR_DOUBLE, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        get_dada_attribute(dadaobj_cast(x), (e_dadaitem_types)DADAITEM_TYPE_LEVEL, gensym("height"))->postprocess = (bach_attr_process_fn)platform_undo_postprocess_levelheight;
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("bgsprite"), (char *)"Background Sprite", DADAITEM_TYPE_LEVEL, t_levelinfo, background_sprite, k_BACH_ATTR_SYM, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("hero"), (char *)"Hero Name", DADAITEM_TYPE_LEVEL, t_levelinfo, hero_name, k_BACH_ATTR_SYM, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("maxtime"), (char *)"Maximum Time", DADAITEM_TYPE_LEVEL, t_levelinfo, maxtime, k_BACH_ATTR_ATOM, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("gravity"), (char *)"Gravity", DADAITEM_TYPE_LEVEL, t_levelinfo, gravity, k_BACH_ATTR_DOUBLE, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("groundfriction"), (char *)"Ground Friction", DADAITEM_TYPE_LEVEL, t_levelinfo, ground_friction, k_BACH_ATTR_DOUBLE, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("airfriction"), (char *)"Air Friction", DADAITEM_TYPE_LEVEL, t_levelinfo, air_friction, k_BACH_ATTR_DOUBLE, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("intro"), (char *)"Has Intro", DADAITEM_TYPE_LEVEL, t_levelinfo, has_intro, k_BACH_ATTR_CHAR, 1, k_BACH_ATTR_DISPLAY_ONOFF, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("textcolor"), (char *)"Text Color", DADAITEM_TYPE_LEVEL, t_levelinfo, j_textcolor, k_BACH_ATTR_COLOR, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
#endif
 
        // BLOCKS
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("coord"), (char *)"Position", DADAITEM_TYPE_BLOCK, t_dadaitem, coord, k_BACH_ATTR_DOUBLE_ARRAY, 2, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("width"), (char *)"Width", DADAITEM_TYPE_BLOCK, t_dadaitem, width, k_BACH_ATTR_DOUBLE, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("height"), (char *)"Height", DADAITEM_TYPE_BLOCK, t_dadaitem, height, k_BACH_ATTR_DOUBLE, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("name"), (char *)"Name", DADAITEM_TYPE_BLOCK, t_dadaitem, name, k_BACH_ATTR_SYM, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, "none");
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("sprite"), (char *)"Sprite", DADAITEM_TYPE_BLOCK, t_dada_block, sprite, k_BACH_ATTR_SYM, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("solid"), (char *)"Solid", DADAITEM_TYPE_BLOCK, t_dada_block, solid, k_BACH_ATTR_CHAR, 1, k_BACH_ATTR_DISPLAY_ONOFF, 0, 0, "1");
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("howhit"), (char *)"Hitting Ways", DADAITEM_TYPE_BLOCK, t_dada_block, how_bumpeable, k_BACH_ATTR_LONG, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        bach_attribute_add_functions(get_dada_attribute(dadaobj_cast(x), (e_dadaitem_types)DADAITEM_TYPE_BLOCK, gensym("howhit")), (bach_getter_fn)platform_gamechar_getattr_howhit, (bach_setter_fn)platform_gamechar_setattr_howhit, NULL, NULL, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("hitcount"), (char *)"Hit Count", DADAITEM_TYPE_BLOCK, t_dada_block, hit_count, k_BACH_ATTR_LONG, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        get_dada_attribute(dadaobj_cast(x), (e_dadaitem_types)DADAITEM_TYPE_BLOCK, gensym("hitcount"))->flags = DADA_ATTRIBUTE_FLAG_DONTRETRIEVE;
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("hitseq"), (char *)"Hit Sequence", DADAITEM_TYPE_BLOCK, t_dada_block, hit_sequence, k_BACH_ATTR_LLLL, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("loophitseq"), (char *)"Loop Hit Sequence", DADAITEM_TYPE_BLOCK, t_dada_block, loop_hit_sequence, k_BACH_ATTR_CHAR, 1, k_BACH_ATTR_DISPLAY_ONOFF, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("breaksprite"), (char *)"Fragment Sprite", DADAITEM_TYPE_BLOCK, t_dada_block, fragment_sprite, k_BACH_ATTR_SYM, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("state"), (char *)"State", DADAITEM_TYPE_BLOCK, t_dada_block, state, k_BACH_ATTR_LONG, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("pointsgiven"), (char *)"Points Given", DADAITEM_TYPE_BLOCK, t_dada_block, points, k_BACH_ATTR_DOUBLE, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("music"), (char *)"Music", DADAITEM_TYPE_BLOCK, t_dada_block, music, k_BACH_ATTR_LLLL, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("prototype"), (char *)"Prototype", DADAITEM_TYPE_BLOCK, t_dada_block, prototype_dummy_for_attr, k_BACH_ATTR_SYM, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        prototype_attr = get_dada_attribute(dadaobj_cast(x), (e_dadaitem_types)DADAITEM_TYPE_BLOCK, gensym("prototype"));
        bach_attribute_add_functions(prototype_attr, (bach_getter_fn)platform_dadaitem_getattr_prototype, (bach_setter_fn)platform_dadaitem_setattr_prototype, NULL, NULL, NULL);
        prototype_attr->flags = DADA_ATTRIBUTE_FLAG_DONTRETRIEVE;
        
        // COINS
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("coord"), (char *)"Position", DADAITEM_TYPE_COIN, t_dadaitem, coord, k_BACH_ATTR_DOUBLE_ARRAY, 2, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("width"), (char *)"Width", DADAITEM_TYPE_COIN, t_dadaitem, width, k_BACH_ATTR_DOUBLE, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("height"), (char *)"Height", DADAITEM_TYPE_COIN, t_dadaitem, height, k_BACH_ATTR_DOUBLE, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("name"), (char *)"Name", DADAITEM_TYPE_COIN, t_dadaitem, name, k_BACH_ATTR_SYM, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, "none");
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("sprite"), (char *)"Sprite", DADAITEM_TYPE_COIN, t_dada_coin, sprite, k_BACH_ATTR_SYM, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("takeable"), (char *)"Takeable", DADAITEM_TYPE_COIN, t_dada_coin, takeable, k_BACH_ATTR_CHAR, 1, k_BACH_ATTR_DISPLAY_ONOFF, 0, 0, "1");
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("taken"), (char *)"Taken", DADAITEM_TYPE_COIN, t_dada_coin, taken, k_BACH_ATTR_CHAR, 1, k_BACH_ATTR_DISPLAY_ONOFF, 0, 0, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("pointsgiven"), (char *)"Points Given", DADAITEM_TYPE_COIN, t_dada_coin, points, k_BACH_ATTR_DOUBLE, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("vpgiven"), (char *)"Victory Points Given", DADAITEM_TYPE_COIN, t_dada_coin, vp, k_BACH_ATTR_LONG, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("music"), (char *)"Music", DADAITEM_TYPE_COIN, t_dada_coin, music, k_BACH_ATTR_LLLL, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("prototype"), (char *)"Prototype", DADAITEM_TYPE_COIN, t_dada_coin, prototype_dummy_for_attr, k_BACH_ATTR_SYM, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        prototype_attr = get_dada_attribute(dadaobj_cast(x), (e_dadaitem_types)DADAITEM_TYPE_COIN, gensym("prototype"));
        bach_attribute_add_functions(prototype_attr, (bach_getter_fn)platform_dadaitem_getattr_prototype, (bach_setter_fn)platform_dadaitem_setattr_prototype, NULL, NULL, NULL);
        prototype_attr->flags = DADA_ATTRIBUTE_FLAG_DONTRETRIEVE;

        t_symbol *gamechartypes[5];
        gamechartypes[0] = gensym("Idle");
        gamechartypes[1] = gensym("User Control");
        gamechartypes[2] = gensym("Enemy");
        gamechartypes[3] = gensym("Food");
        gamechartypes[4] = gensym("Bullet");

		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("coord"), (char *)"Position", DADAITEM_TYPE_GAMECHAR, t_dadaitem, coord, k_BACH_ATTR_DOUBLE_ARRAY, 2, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("speed"), (char *)"Speed", DADAITEM_TYPE_GAMECHAR, t_dada_gamechar, speed, k_BACH_ATTR_DOUBLE_ARRAY, 2, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("width"), (char *)"Width", DADAITEM_TYPE_GAMECHAR, t_dadaitem, width, k_BACH_ATTR_DOUBLE, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("height"), (char *)"Height", DADAITEM_TYPE_GAMECHAR, t_dadaitem, height, k_BACH_ATTR_DOUBLE, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("ext"), (char *)"Physics Left/Right/Top/Bottom Extensions", DADAITEM_TYPE_GAMECHAR, t_dada_gamechar, physics_ext, k_BACH_ATTR_DOUBLE_ARRAY, 4, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("name"), (char *)"Name", DADAITEM_TYPE_GAMECHAR, t_dadaitem, name, k_BACH_ATTR_SYM, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, "none");
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, _llllobj_sym_type, (char *)"Type", DADAITEM_TYPE_GAMECHAR, t_dada_gamechar, type, k_BACH_ATTR_LONG, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
//        bach_attribute_add_enumindex(get_dada_attribute(dadaobj_cast(x), (e_dadaitem_types)DADAITEM_TYPE_GAMECHAR, _llllobj_sym_type), 5, gamechartypes);
        bach_attribute_add_functions(get_dada_attribute(dadaobj_cast(x), (e_dadaitem_types)DADAITEM_TYPE_GAMECHAR, _llllobj_sym_type), (bach_getter_fn)platform_gamechar_getattr_type, (bach_setter_fn)platform_gamechar_setattr_type, NULL, NULL, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("points"), (char *)"Points", DADAITEM_TYPE_GAMECHAR, t_dada_gamechar, points, k_BACH_ATTR_DOUBLE, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("vp"), (char *)"Victory Points", DADAITEM_TYPE_GAMECHAR, t_dada_gamechar, vp, k_BACH_ATTR_LONG, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("direction"), (char *)"Direction", DADAITEM_TYPE_GAMECHAR, t_dada_gamechar, direction, k_BACH_ATTR_CHAR, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("state"), (char *)"Current State", DADAITEM_TYPE_GAMECHAR, t_dada_gamechar, state, k_BACH_ATTR_LONG, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        bach_attribute_add_functions(get_dada_attribute(dadaobj_cast(x), (e_dadaitem_types)DADAITEM_TYPE_GAMECHAR, gensym("state")), (bach_getter_fn)platform_gamechar_getattr_state, (bach_setter_fn)platform_gamechar_setattr_state, NULL, NULL, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("ability"), (char *)"Abilities", DADAITEM_TYPE_GAMECHAR, t_dada_gamechar, abilities, k_BACH_ATTR_LONG, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        bach_attribute_add_functions(get_dada_attribute(dadaobj_cast(x), (e_dadaitem_types)DADAITEM_TYPE_GAMECHAR, gensym("ability")), (bach_getter_fn)platform_gamechar_getattr_ability, (bach_setter_fn)platform_gamechar_setattr_ability, NULL, NULL, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("howdies"), (char *)"Dying Ways", DADAITEM_TYPE_GAMECHAR, t_dada_gamechar, how_dies, k_BACH_ATTR_LONG, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        bach_attribute_add_functions(get_dada_attribute(dadaobj_cast(x), (e_dadaitem_types)DADAITEM_TYPE_GAMECHAR, gensym("howdies")), (bach_getter_fn)platform_gamechar_getattr_howdies, (bach_setter_fn)platform_gamechar_setattr_howdies, NULL, NULL, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("howkills"), (char *)"Killing Ways", DADAITEM_TYPE_GAMECHAR, t_dada_gamechar, how_kills, k_BACH_ATTR_LONG, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        bach_attribute_add_functions(get_dada_attribute(dadaobj_cast(x), (e_dadaitem_types)DADAITEM_TYPE_GAMECHAR, gensym("howkills")), (bach_getter_fn)platform_gamechar_getattr_howkills, (bach_setter_fn)platform_gamechar_setattr_howkills, NULL, NULL, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("idlesprite"), (char *)"Idle Sprite", DADAITEM_TYPE_GAMECHAR, t_dada_gamechar, sprite_idle, k_BACH_ATTR_SYM, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("walksprite"), (char *)"Walk Sprite", DADAITEM_TYPE_GAMECHAR, t_dada_gamechar, sprite_walk, k_BACH_ATTR_SYM, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("jumpsprite"), (char *)"Jump Sprite", DADAITEM_TYPE_GAMECHAR, t_dada_gamechar, sprite_jump, k_BACH_ATTR_SYM, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("glidesprite"), (char *)"Glide Sprite", DADAITEM_TYPE_GAMECHAR, t_dada_gamechar, sprite_glide, k_BACH_ATTR_SYM, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("flysprite"), (char *)"Fly Sprite", DADAITEM_TYPE_GAMECHAR, t_dada_gamechar, sprite_fly, k_BACH_ATTR_SYM, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("deadsprite"), (char *)"Dead Sprite", DADAITEM_TYPE_GAMECHAR, t_dada_gamechar, sprite_dead, k_BACH_ATTR_SYM, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("deathseq"), (char *)"Death Sequence", DADAITEM_TYPE_GAMECHAR, t_dada_gamechar, kill_sequence, k_BACH_ATTR_LLLL, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
		DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("resurrectpositions"), (char *)"Resurrection Positions", DADAITEM_TYPE_GAMECHAR, t_dada_gamechar, resurrectpositions, k_BACH_ATTR_LLLL, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("prototype"), (char *)"Prototype", DADAITEM_TYPE_GAMECHAR, t_dada_gamechar, prototype_dummy_for_attr, k_BACH_ATTR_SYM, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        prototype_attr = get_dada_attribute(dadaobj_cast(x), (e_dadaitem_types)DADAITEM_TYPE_GAMECHAR, gensym("prototype"));
        bach_attribute_add_functions(prototype_attr, (bach_getter_fn)platform_dadaitem_getattr_prototype, (bach_setter_fn)platform_dadaitem_setattr_prototype, NULL, NULL, NULL);
        prototype_attr->flags = DADA_ATTRIBUTE_FLAG_DONTRETRIEVE;

		
        
        // Portals
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("coord"), (char *)"Position", DADAITEM_TYPE_PORTAL, t_dadaitem, coord, k_BACH_ATTR_DOUBLE_ARRAY, 2, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("width"), (char *)"Width", DADAITEM_TYPE_PORTAL, t_dadaitem, width, k_BACH_ATTR_DOUBLE, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("height"), (char *)"Height", DADAITEM_TYPE_PORTAL, t_dadaitem, height, k_BACH_ATTR_DOUBLE, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("name"), (char *)"Name", DADAITEM_TYPE_PORTAL, t_dadaitem, name, k_BACH_ATTR_SYM, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, "none");
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("sprite"), (char *)"Sprite", DADAITEM_TYPE_PORTAL, t_dada_portal, sprite, k_BACH_ATTR_SYM, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("open"), (char *)"Open", DADAITEM_TYPE_PORTAL, t_dada_portal, open, k_BACH_ATTR_CHAR, 1, k_BACH_ATTR_DISPLAY_ONOFF, 0, 0, "1");
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("howenter"), (char *)"Entering Ways", DADAITEM_TYPE_PORTAL, t_dada_portal, how_enter, k_BACH_ATTR_LONG, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        bach_attribute_add_functions(get_dada_attribute(dadaobj_cast(x), (e_dadaitem_types)DADAITEM_TYPE_PORTAL, gensym("howenter")), (bach_getter_fn)platform_gamechar_getattr_howenter, (bach_setter_fn)platform_gamechar_setattr_howenter, NULL, NULL, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("howexit"), (char *)"Exiting Ways", DADAITEM_TYPE_PORTAL, t_dada_portal, how_exit, k_BACH_ATTR_LONG, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        bach_attribute_add_functions(get_dada_attribute(dadaobj_cast(x), (e_dadaitem_types)DADAITEM_TYPE_PORTAL, gensym("howexit")), (bach_getter_fn)platform_gamechar_getattr_howexit, (bach_setter_fn)platform_gamechar_setattr_howexit, NULL, NULL, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("enterseq"), (char *)"Entering Sequence", DADAITEM_TYPE_PORTAL, t_dada_portal, enter_sequence, k_BACH_ATTR_LLLL, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("exitseq"), (char *)"Exiting Sequence", DADAITEM_TYPE_PORTAL, t_dada_portal, exit_sequence, k_BACH_ATTR_LLLL, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("music"), (char *)"Music", DADAITEM_TYPE_PORTAL, t_dada_portal, music, k_BACH_ATTR_LLLL, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("heroonly"), (char *)"For Hero Only", DADAITEM_TYPE_PORTAL, t_dada_portal, hero_only, k_BACH_ATTR_CHAR, 1, k_BACH_ATTR_DISPLAY_ONOFF, 0, 0, NULL);
        DECLARE_DADA_ATTR(dadaobj_cast(x), man, -1, gensym("prototype"), (char *)"Prototype", DADAITEM_TYPE_PORTAL, t_dada_portal, prototype_dummy_for_attr, k_BACH_ATTR_SYM, 1, k_BACH_ATTR_DISPLAY_TEXT, 0, 0, NULL);
        prototype_attr = get_dada_attribute(dadaobj_cast(x), (e_dadaitem_types)DADAITEM_TYPE_PORTAL, gensym("prototype"));
        bach_attribute_add_functions(prototype_attr, (bach_getter_fn)platform_dadaitem_getattr_prototype, (bach_setter_fn)platform_dadaitem_setattr_prototype, NULL, NULL, NULL);
        prototype_attr->flags = DADA_ATTRIBUTE_FLAG_DONTRETRIEVE;
  
 
        
        x->b_ob.d_ob.m_inspector.attr_manager->inspector_image = (bach_inspector_image_fn)platform_inspector_get_icon_surface_fn;
        
        
		// STANDARD INITIAL THINGS
		
/*		long idx;
		
		// blocks
        idx = dadaitem_block_add(dadaobj_cast(x), build_pt(0, 0), 1, 1, DADA_BLACK, gensym("Ground"), true, 0, 0, gensym("ground"), NULL, false, 0, NULL, NULL, 0, 0);
        platform_ezadd_prototype_from_dadaitem(x, gensym("ground"), dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_BLOCK), idx));
        platform_add_items_from_prototype(x, gensym("ground"), DADAITEM_TYPE_BLOCK, (char *)"(-1 0) (1 0) (2 0) (3 0) (4 0) (5 0) (6 0) (7 0) (8 0) (9 0) (10 0) (11 0) (12 0) (13 0) (14 0) (15 0) (16 0) (17 0) (18 0) (19 0) (20 0) (21 0) (22 0) (23 0) (24 0) (25 0) (26 0) (27 0) (31 0) (32 0) (33 0) (34 0) (35 0) (36 0) (37 0) (38 0) (39 0) (40 0) (41 0) (42 0) (43 0) (44 0) (45 0) (46 0) (47 0) (48 0)", 0);

        idx = dadaitem_block_add(dadaobj_cast(x), build_pt(-1, 1), 1, 1, DADA_BLACK, gensym("Brick"), true, DADA_GAMECHAR_VIA_SIDE_BOTTOM + DADA_GAMECHAR_VIA_GLIDE, 0, gensym("brick"), gensym("breakbrick"), 0, NULL, llll_from_text_buf("break", false), true, 0, 0);
		platform_ezadd_prototype_from_dadaitem(x, gensym("brick"), dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_BLOCK), idx));
        platform_add_items_from_prototype(x, gensym("brick"), DADAITEM_TYPE_BLOCK, (char *)"(14 1) (15 1) (15 2) (21 4) (23 4) (26 2) (26 1) (27 1) (34 1) (34 2) (35 1) (35 2) (49 1) (50 1) (51 1) (51 2) (51 3)", 0);

        idx = dadaitem_block_add(dadaobj_cast(x), build_pt(11, 6), 1, 1, DADA_BLACK, gensym("Wood"), true, 0, 0, gensym("wood"), NULL, 0, NULL, NULL, false, 0, 0);
        platform_ezadd_prototype_from_dadaitem(x, gensym("wood"), dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_BLOCK), idx));
        platform_add_items_from_prototype(x, gensym("wood"), DADAITEM_TYPE_BLOCK, (char *)"(13 6)", 0);

        idx = dadaitem_block_add(dadaobj_cast(x), build_pt(12, 6), 1, 1, DADA_BLACK, gensym("Note"), true, DADA_GAMECHAR_VIA_SIDE_ANY, 0, gensym("note"), NULL, 0, dada_roll_gen(0, rand_range(3600, 8400), 500, 100), NULL, false, 0, 0);
        platform_ezadd_prototype_from_dadaitem(x, gensym("note"), dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_BLOCK), idx));

        idx = dadaitem_block_add(dadaobj_cast(x), build_pt(22, 4), 1, 1, DADA_BLACK, gensym("MushroomQuestionMark"), true, DADA_GAMECHAR_VIA_SIDE_BOTTOM + DADA_GAMECHAR_VIA_GLIDE, 0, gensym("questionmark"), NULL, 0, dada_roll_gen(0, rand_range(3600, 8400), 500, 100), llll_from_text_buf("((generate mushroom from me) (change me (sprite questionidle) (howhit)))", false), false, 0, 0);

        idx = dadaitem_block_add(dadaobj_cast(x), build_pt(32, 4), 1, 1, DADA_BLACK, gensym("CoinsStarQuestionMark"), true, DADA_GAMECHAR_VIA_SIDE_BOTTOM + DADA_GAMECHAR_VIA_GLIDE, 0, gensym("questionmark"), NULL, 0, dada_roll_gen(0, rand_range(3600, 8400), 500, 100), llll_from_text_buf("(give hero 10 points) (give hero 10 points) (give hero 10 points) (give hero 10 points) ((generate star) (change me (sprite questionidle) (howhit)))", false), false, 0, 0);

        
		// coins
		idx = dadaitem_coin_add(dadaobj_cast(x), build_pt(5, 6), 0.75, 1, DADA_BLACK, gensym("Coin"), true, false, gensym("coin"), 10, 0,
                                llll_from_text_buf("roll ((0 (7900 100 100)) (100 (8400 100 100)))", false), 0, 0);
		platform_ezadd_prototype_from_dadaitem(x, gensym("coin"), dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_COIN), idx));
		platform_add_items_from_prototype(x, gensym("coin"), DADAITEM_TYPE_COIN, (char *)"(6 6) (5 7) (6 7) (16 9) (17 9)", 0);
		
        
		// Juan
        double physics_ext[] = { 0.3, 0.3, 0.5, 0.5 };
		dadaitem_gamechar_add(dadaobj_cast(x), build_pt(2, 1), 1, 1, DADA_BLACK, build_pt(0, 0), gensym(""), DADA_GAMECHAR_TYPE_USERCONTROL, 0, 3,
							  DADA_GAMECHAR_STATE_IDLE, DADA_GAMECHAR_ABILITY_WALK + DADA_GAMECHAR_ABILITY_JUMP + DADA_GAMECHAR_ABILITY_KILL + DADA_GAMECHAR_ABILITY_DIE, DADA_GAMECHAR_VIA_SIDE_ANY + DADA_GAMECHAR_VIA_BULLET + DADA_GAMECHAR_VIA_GLIDE, DADA_GAMECHAR_VIA_SIDE_BOTTOM, 0, NULL, gensym("juanidle"), gensym("juanwalk"), gensym("juanjump"), gensym("juanfly"), gensym("juanidle"), gensym("juandead"), gensym("firebullet"), llll_from_text_buf("(2 1) (17 1)", false), llll_from_text_buf("die", false), physics_ext, 0, 0);

		// plants
		idx = dadaitem_gamechar_add(dadaobj_cast(x), build_pt(18, 1.25), 1., 1.5, DADA_BLACK, build_pt(0, 0), gensym("Plant"), DADA_GAMECHAR_TYPE_ENEMY, 0, 1,
							  DADA_GAMECHAR_STATE_IDLE, DADA_GAMECHAR_ABILITY_KILL, DADA_GAMECHAR_VIA_SIDE_NONE, DADA_GAMECHAR_VIA_SIDE_TOP, 0, NULL, gensym("plant"), NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0);
        platform_ezadd_prototype_from_dadaitem(x, gensym("plant"), dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_GAMECHAR), idx));
		platform_add_items_from_prototype(x, gensym("plant"), DADAITEM_TYPE_GAMECHAR, (char *)"(38 1.25) (39 1.25)", 0);

		
		// evilmushrooms
		idx = dadaitem_gamechar_add(dadaobj_cast(x), build_pt(8, 1.), 1., 1., DADA_BLACK, build_pt(1, 0), gensym("Evilmushroom"), DADA_GAMECHAR_TYPE_ENEMY, 0, 1,
							  DADA_GAMECHAR_STATE_WALKING, DADA_GAMECHAR_ABILITY_WALK + DADA_GAMECHAR_ABILITY_KILL + DADA_GAMECHAR_ABILITY_DIE, DADA_GAMECHAR_VIA_SIDE_TOP + DADA_GAMECHAR_VIA_BUMP + DADA_GAMECHAR_VIA_BULLET + DADA_GAMECHAR_VIA_GLIDE, DADA_GAMECHAR_VIA_SIDE_BOTTOM_LEFT_RIGHT, 1,
							  NULL, gensym("evilmushroom"), gensym("evilmushroom"), NULL, NULL, NULL, gensym("evilmushroomdead"), NULL, NULL, llll_from_text_buf("(give hero 10 points)", false), NULL, 0, 0);
		platform_ezadd_prototype_from_dadaitem(x, gensym("evilmushroom"), dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_GAMECHAR), idx));
		platform_add_items_from_prototype(x, gensym("evilmushroom"), DADAITEM_TYPE_GAMECHAR, (char *)"(9 1.) (23 1.)", 0);

		
		// ducks
		idx = dadaitem_gamechar_add(dadaobj_cast(x), build_pt(46, 1.5), 1, 1.6875, DADA_BLACK, build_pt(1, 0), gensym("Duck"), DADA_GAMECHAR_TYPE_ENEMY, 0, 1,
									DADA_GAMECHAR_STATE_WALKING, DADA_GAMECHAR_ABILITY_WALK + DADA_GAMECHAR_ABILITY_KILL + DADA_GAMECHAR_ABILITY_DIE, DADA_GAMECHAR_VIA_SIDE_TOP + DADA_GAMECHAR_VIA_BUMP + DADA_GAMECHAR_VIA_BULLET + DADA_GAMECHAR_VIA_GLIDE, DADA_GAMECHAR_VIA_SIDE_BOTTOM_LEFT_RIGHT, 1, NULL, gensym("duck"), gensym("duckwalk"), NULL, NULL, gensym("duckdead"), gensym("duckdead"), NULL, NULL, llll_from_text_buf("(dontdie) (give hero 10 points) (add me ability glide) (remove me ability walk) (remove me ability die during 200) (change me (sprite duckdead) (ext 0.5 0.5 0.1 0.84375) (speed 8 0) (state gliding) (deathseq))", false), NULL, 0, 0);
		platform_ezadd_prototype_from_dadaitem(x, gensym("duck"), dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_GAMECHAR), idx));
		platform_add_items_from_prototype(x, gensym("duck"), DADAITEM_TYPE_GAMECHAR, (char *)"(48 1.5)", 0);
		
        
        // FEEDING ELEMENTS:
        // mushroom
        idx = dadaitem_gamechar_add(dadaobj_cast(x), build_pt(8, 1.), 1., 1., DADA_BLACK, build_pt(1, 0), gensym("Mushroom"), DADA_GAMECHAR_TYPE_FOOD, 0, 1,
                                    DADA_GAMECHAR_STATE_WALKING, DADA_GAMECHAR_ABILITY_WALK + DADA_GAMECHAR_ABILITY_DIE, DADA_GAMECHAR_VIA_SIDE_ANY, DADA_GAMECHAR_VIA_SIDE_NONE, 1,
                                    NULL, gensym("mushroom"), gensym("mushroom"), NULL, NULL, NULL, NULL, NULL, NULL, llll_from_text_buf("(change hero (name SuperJuan) (idlesprite superjuanidle) (walksprite superjuanwalk) (jumpsprite superjuanjump) (height 1.625) (ext 0.35 0.35 0.825 0.825) (deathseq (dontdie) (remove hero ability die during 2000) (change hero (name Juan) (idlesprite juanidle) (walksprite juanwalk) (jumpsprite juanjump) (height 1) (ext 0.4 0.4 0.5 0.5) (deathseq)) (remove hero ability break))) (add hero ability break)", false), NULL, 0, 0);
        platform_ezadd_prototype_from_dadaitem(x, gensym("mushroom"), dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_GAMECHAR), idx));
        dadaitem_gamechar_delete(dadaobj_cast(x), idx, 0);

        
        // VP-mushroom
        idx = dadaitem_gamechar_add(dadaobj_cast(x), build_pt(8, 1.), 1., 1., DADA_BLACK, build_pt(1, 0), gensym("VP Mushroom"), DADA_GAMECHAR_TYPE_FOOD, 0, 1,
                                    DADA_GAMECHAR_STATE_WALKING, DADA_GAMECHAR_ABILITY_WALK + DADA_GAMECHAR_ABILITY_DIE, DADA_GAMECHAR_VIA_SIDE_ANY, DADA_GAMECHAR_VIA_SIDE_NONE, 1,
                                    NULL, gensym("vpmushroom"), gensym("vpmushroom"), NULL, NULL, NULL, NULL, NULL, NULL, llll_from_text_buf("(give hero 1 vp)", false), NULL, 0, 0);
        platform_ezadd_prototype_from_dadaitem(x, gensym("vpmushroom"), dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_GAMECHAR), idx));
        dadaitem_gamechar_delete(dadaobj_cast(x), idx, 0);

        
        // star
        idx = dadaitem_gamechar_add(dadaobj_cast(x), build_pt(8, 1.), 1., 1., DADA_BLACK, build_pt(1, 0), gensym("Star"), DADA_GAMECHAR_TYPE_FOOD, 0, 1,
                                    DADA_GAMECHAR_STATE_JUMPING, DADA_GAMECHAR_ABILITY_JUMP + DADA_GAMECHAR_ABILITY_DIE, DADA_GAMECHAR_VIA_SIDE_ANY, DADA_GAMECHAR_VIA_SIDE_NONE, 1,
                                    NULL, gensym("star"), gensym("star"), NULL, NULL, NULL, NULL, NULL, NULL, llll_from_text_buf("(remove hero ability die during 15000)", false), NULL, 0, 0);
        platform_ezadd_prototype_from_dadaitem(x, gensym("star"), dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_GAMECHAR), idx));
        dadaitem_gamechar_delete(dadaobj_cast(x), idx, 0);

        
        /// BULLET CHARACTERS
        idx = dadaitem_gamechar_add(dadaobj_cast(x), build_pt(8, 1.), 0.625, 0.625, DADA_BLACK, build_pt(10, 0), gensym("Fire Bullet"), DADA_GAMECHAR_TYPE_BULLET, 0, 1,
                                    DADA_GAMECHAR_STATE_FLYING, DADA_GAMECHAR_ABILITY_FLY + DADA_GAMECHAR_ABILITY_KILL + DADA_GAMECHAR_ABILITY_DIE, DADA_GAMECHAR_VIA_TOUCH_GROUND, DADA_GAMECHAR_VIA_SIDE_ANY, 1,
                                    NULL, gensym("superjuanfirebullet"), NULL, NULL, gensym("superjuanfirebullet"), NULL, NULL, NULL, NULL, NULL, NULL, 0, 0);
        platform_ezadd_prototype_from_dadaitem(x, gensym("firebullet"), dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_GAMECHAR), idx));
        dadaitem_gamechar_delete(dadaobj_cast(x), idx, 0);
        
		
        // PORTALS
        idx = dadaitem_portal_add(dadaobj_cast(x), build_pt(5, 1.), 2, 2, DADA_BLACK, gensym("Pipe"), gensym("pipe"), true, DADA_GAMECHAR_VIA_SIDE_TOP, 0, llll_from_text_buf("(goto level juanlevelswim.txt at PipeRev)", false), NULL, NULL, true, 0, 0);
        platform_ezadd_prototype_from_dadaitem(x, gensym("pipe"), dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_PORTAL), idx));

        idx = dadaitem_portal_add(dadaobj_cast(x), build_pt(55, 1.), 1, 2, DADA_BLACK, gensym("Door"), gensym("door"), true, DADA_GAMECHAR_VIA_SIDE_LEFT, 0, llll_from_text_buf("(win)", false), NULL, NULL, true, 0, 0);
        platform_ezadd_prototype_from_dadaitem(x, gensym("door"), dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_PORTAL), idx));

 
        
		// sprites
		platform_ezadd_sprite(x, gensym("background"), build_rect(0, 0, 2560, 215), true, 150, 1, gensym("bg.png"));
		platform_ezadd_sprite(x, gensym("brick"), build_rect(0, 0, 16, 16), true, 150, 4, gensym("altblock1.png"), gensym("altblock2.png"), gensym("altblock3.png"), gensym("altblock4.png"));
        platform_ezadd_sprite(x, gensym("breakbrick"), build_rect(0, 0, 16, 16), true, 150, 1, gensym("breakbrick.png"));
        platform_ezadd_sprite(x, gensym("ground"), build_rect(0, 0, 16, 16), true, 150, 1, gensym("ground.png"));
        platform_ezadd_sprite(x, gensym("wood"), build_rect(0, 0, 16, 16), true, 150, 1, gensym("wood.png"));
        platform_ezadd_sprite(x, gensym("note"), build_rect(0, 0, 16, 16), true, 300, 2, gensym("note1.png"), gensym("note2.png"));
        platform_ezadd_sprite(x, gensym("questionmark"), build_rect(0, 0, 16, 16), true, 300, 4, gensym("question1.png"), gensym("question2.png"), gensym("question3.png"), gensym("question4.png"));
        platform_ezadd_sprite(x, gensym("questionidle"), build_rect(0, 0, 16, 16), true, 300, 1, gensym("questionidle.png"));
		platform_ezadd_sprite(x, gensym("coin"), build_rect(0, 0, 12, 16), true, 300, 4, gensym("coin0.png"), gensym("coin1.png"), gensym("coin2.png"), gensym("coin3.png"));

        platform_ezadd_sprite(x, gensym("juanidle"), build_rect(0, 0, 16, 16), true, 150., 1, gensym("juan_r.png"));
		platform_ezadd_sprite(x, gensym("juanwalk"), build_rect(0, 0, 16, 16), true, 150., 2, gensym("juan_r.png"), gensym("juan_walk_r.png"));
		platform_ezadd_sprite(x, gensym("juanjump"), build_rect(0, 0, 16, 16), true, 150., 1, gensym("juan_jump_r.png"));
		platform_ezadd_sprite(x, gensym("juandead"), build_rect(0, 0, 16, 16), true, 150., 1, gensym("juan_dead.png"));
		
        platform_ezadd_sprite(x, gensym("superjuanidle"), build_rect(0, 0, 16, 26), true, 150., 1, gensym("superjuan_r.png"));
        platform_ezadd_sprite(x, gensym("superjuanwalk"), build_rect(0, 0, 16, 26), true, 150., 2, gensym("superjuan_r.png"), gensym("superjuan_walk_r.png"));
        platform_ezadd_sprite(x, gensym("superjuanjump"), build_rect(0, 0, 16, 26), true, 150., 1, gensym("superjuan_jump_r.png"));

        platform_ezadd_sprite(x, gensym("superjuanfireidle"), build_rect(0, 0, 16, 26), true, 150., 1, gensym("superjuanfire_r.png"));
        platform_ezadd_sprite(x, gensym("superjuanfirewalk"), build_rect(0, 0, 16, 26), true, 150., 2, gensym("superjuanfire_r.png"), gensym("superjuanfire_walk_r.png"));
        platform_ezadd_sprite(x, gensym("superjuanfirejump"), build_rect(0, 0, 16, 26), true, 150., 1, gensym("superjuanfire_jump_r.png"));
        platform_ezadd_sprite(x, gensym("superjuanfirefire"), build_rect(0, 0, 16, 26), true, 150., 1, gensym("superjuanfire_fire_r.png"));
        platform_ezadd_sprite(x, gensym("superjuanfirebullet"), build_rect(0, 0, 10, 10), true, 150., 4, gensym("firebullet1.png"), gensym("firebullet2.png"), gensym("firebullet3.png"), gensym("firebullet4.png"));

        platform_ezadd_sprite(x, gensym("plant"), build_rect(0, 0, 18, 25), true, 150., 2, gensym("carnivorousplant1.png"), gensym("carnivorousplant2.png"));
		platform_ezadd_sprite(x, gensym("duckwalk"), build_rect(0, 0, 16, 27), true, 150., 2, gensym("duck1.png"), gensym("duck2.png"));
		platform_ezadd_sprite(x, gensym("duckdead"), build_rect(0, 0, 16, 27), true, 150., 1, gensym("duckdead.png"));
		platform_ezadd_sprite(x, gensym("toad"), build_rect(0, 0, 16, 16), true, 150., 2, gensym("toad1.png"), gensym("toad2.png"));
		platform_ezadd_sprite(x, gensym("toaddead"), build_rect(0, 0, 16, 16), true, 150., 1, gensym("toaddead.png"));
        platform_ezadd_sprite(x, gensym("mushroom"), build_rect(0, 0, 16, 16), true, 150., 1, gensym("mushroom.png"));
        platform_ezadd_sprite(x, gensym("vpmushroom"), build_rect(0, 0, 16, 16), true, 150., 1, gensym("vpmushroom.png"));
        platform_ezadd_sprite(x, gensym("star"), build_rect(0, 0, 16, 16), true, 150., 2, gensym("star1.png"), gensym("star2.png"));
        platform_ezadd_sprite(x, gensym("pipe"), build_rect(0, 0, 32, 32), true, 150., 1, gensym("pipe.png"));
        platform_ezadd_sprite(x, gensym("door"), build_rect(0, 0, 16, 32), true, 150., 1, gensym("door.png"));
		
		*/
        
        char retrieved_from_saved_state = true;
        llll_for_rebuild = llll_retrieve_from_dictionary(d, "platform_data");
        
        if (!llll_for_rebuild) {
            retrieved_from_saved_state = false;
            llll_for_rebuild = llll_from_text_buf("platform \
                                                  ( levelinfo ( title \"Level 1: Mushroom World\" ) ( hero Juan ) ( bgsprite background ) ( gravity 15.0 ) ( maxtime none ) ( height 10.0 ) ( width 100.0 ) ( groundfriction 5.0 ) ( airfriction 1.0 ) ( textcolor 0 0 0 1 ) ( intro 1 ) ) \
                                                  ( sprites ( ( name background ) ( pics bg.png ) ( rect 0.0 0.0 2560.0 215.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name brick ) ( pics altblock1.png altblock2.png altblock3.png altblock4.png ) ( rect 0.0 0.0 16.0 16.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name breakbrick ) ( pics breakbrick.png ) ( rect 0.0 0.0 16.0 16.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name ground ) ( pics ground.png ) ( rect 0.0 0.0 16.0 16.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name wood ) ( pics wood.png ) ( rect 0.0 0.0 16.0 16.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name note ) ( pics note1.png note2.png ) ( rect 0.0 0.0 16.0 16.0 ) ( stretch 1 ) ( slidetime 300.0 ) ) ( ( name questionmark ) ( pics question1.png question2.png question3.png question4.png ) ( rect 0.0 0.0 16.0 16.0 ) ( stretch 1 ) ( slidetime 300.0 ) ) ( ( name questionidle ) ( pics questionidle.png ) ( rect 0.0 0.0 16.0 16.0 ) ( stretch 1 ) ( slidetime 300.0 ) ) ( ( name coin ) ( pics coin0.png coin1.png coin2.png coin3.png ) ( rect 0.0 0.0 12.0 16.0 ) ( stretch 1 ) ( slidetime 300.0 ) ) ( ( name juanidle ) ( pics juan_r.png ) ( rect 0.0 0.0 16.0 16.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name juanwalk ) ( pics juan_r.png juan_walk_r.png ) ( rect 0.0 0.0 16.0 16.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name juanjump ) ( pics juan_jump_r.png ) ( rect 0.0 0.0 16.0 16.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name juandead ) ( pics juan_dead.png ) ( rect 0.0 0.0 16.0 16.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name superjuanidle ) ( pics superjuan_r.png ) ( rect 0.0 0.0 16.0 26.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name superjuanwalk ) ( pics superjuan_r.png superjuan_walk_r.png ) ( rect 0.0 0.0 16.0 26.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name superjuanjump ) ( pics superjuan_jump_r.png ) ( rect 0.0 0.0 16.0 26.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name superjuanswim ) ( pics superjuanswim1.png superjuanswim2.png superjuanswim3.png superjuanswim4.png ) ( rect 0.0 0.0 20.0 26.0 ) ( stretch 1 ) ( slidetime 150.0 ) )  ( ( name superjuanfireidle ) ( pics superjuanfire_r.png ) ( rect 0.0 0.0 16.0 26.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name superjuanfirewalk ) ( pics superjuanfire_r.png superjuanfire_walk_r.png ) ( rect 0.0 0.0 16.0 26.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name superjuanfirejump ) ( pics superjuanfire_jump_r.png ) ( rect 0.0 0.0 16.0 26.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name superjuanfirefire ) ( pics superjuanfire_fire_r.png ) ( rect 0.0 0.0 16.0 26.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name superjuanfirebullet ) ( pics firebullet1.png firebullet2.png firebullet3.png firebullet4.png ) ( rect 0.0 0.0 10.0 10.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name plant ) ( pics carnivorousplant1.png carnivorousplant2.png ) ( rect 0.0 0.0 18.0 25.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name duckwalk ) ( pics duck1.png duck2.png ) ( rect 0.0 0.0 16.0 27.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name duckdead ) ( pics duckdead.png ) ( rect 0.0 0.0 16.0 27.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name evilmushroom ) ( pics evilmushroom1.png evilmushroom2.png ) ( rect 0.0 0.0 16.0 16.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name evilmushroomdead ) ( pics evilmushroomdead.png ) ( rect 0.0 0.0 16.0 16.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name mushroom ) ( pics mushroom.png ) ( rect 0.0 0.0 16.0 16.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name star ) ( pics star1.png star2.png ) ( rect 0.0 0.0 16.0 16.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name pipetop ) ( pics pipetop.png ) ( rect 0.0 0.0 32.0 16.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name pipemiddle ) ( pics pipemiddle.png ) ( rect 0.0 0.0 32.0 16.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name pipe ) ( pics pipe.png ) ( rect 0.0 0.0 32.0 32.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name piperev ) ( pics piperev.png ) ( rect 0.0 0.0 32.0 32.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name door ) ( pics door.png ) ( rect 0.0 0.0 16.0 32.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name vpmushroom ) ( pics vpmushroom.png ) ( rect 0.0 0.0 16.0 16.0 ) ( stretch 1 ) ( slidetime 150.0 ) ) ( ( name pipetop ) ( pics pipetop.png ) ( rect 0. 0. 32. 16. ) ( stretch 1 ) ( slidetime 150. ) ) ( ( name pipemiddle ) ( pics pipemiddle.png ) ( rect 0. 0. 32. 16. ) ( stretch 1 ) ( slidetime 150. ) ) ( ( name pipe ) ( pics pipe.png ) ( rect 0. 0. 32. 32. ) ( stretch 1 ) ( slidetime 150. ) ) ( ( name piperev ) ( pics piperev.png ) ( rect 0. 0. 32. 32. ) ( stretch 1 ) ( slidetime 150. ) ) ( ( name door ) ( pics door.png ) ( rect 0. 0. 16. 32. ) ( stretch 1 ) ( slidetime 150. ) ) ) \
                                                  ( prototypes ( ground block ( coord 0.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( upbumpeable 0 ) ( downbumpeable 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ( mute 0 ) ( solo 0 ) ( lock 0 ) ) ( brick block ( coord -1.0 1.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( upbumpeable 1 ) ( downbumpeable 0 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ( mute 0 ) ( solo 0 ) ( lock 0 ) ) ( wood block ( coord 11.0 6.0 ) ( width 1.0 ) ( height 1.0 ) ( name Wood ) ( sprite wood ) ( upbumpeable 0 ) ( downbumpeable 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ( mute 0 ) ( solo 0 ) ( lock 0 ) ) ( note block ( coord 12.0 6.0 ) ( width 1.0 ) ( height 1.0 ) ( name Note ) ( sprite note ) ( upbumpeable 1 ) ( downbumpeable 1 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ( ( 0.0 ( 5111.6601562911 500.0 100 ) ) ) ) ( mute 0 ) ( solo 0 ) ( lock 0 ) ) ( coin coin ( coord 5.0 6.0 ) ( width 0.75 ) ( height 1.0 ) ( name Coin ) ( sprite coin ) ( takeable 1 ) ( taken 0 ) ( pointsgiven 10.0 ) ( vpgiven 0 ) ( music roll ( ( 0 ( 7900 100 100 ) ) ( 100 ( 8400 100 100 ) ) ) ) ( mute 0 ) ( solo 0 ) ( lock 0 ) ) ( plant gamechar ( coord 18.0 1.25 ) ( speed 0.0 0.0 ) ( width 1.0 ) ( height 1.5 ) ( ext 0.5 0.5 0.75 0.75 ) ( name Plant ) ( type 2 ) ( points 0.0 ) ( vp 1 ) ( direction 0 ) ( state 0 ) ( ability 128 ) ( howdies 0 ) ( howkills 1 ) ( idlesprite plant ) ( walksprite none ) ( jumpsprite none ) ( glidesprite none ) ( flysprite none ) ( deadsprite none ) ( deathseq ) ( resurrectpositions ) ) ( evilmushroom gamechar ( coord 8.0 1.0 ) ( speed 1.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( ext 0.5 0.5 0.5 0.5 ) ( name EvilMushroom ) ( type 2 ) ( points 0.0 ) ( vp 1 ) ( direction 1 ) ( state 1 ) ( ability 1153 ) ( howdies 209 ) ( howkills 14 ) ( idlesprite evilmushroom ) ( walksprite evilmushroom ) ( jumpsprite none ) ( glidesprite none ) ( flysprite none ) ( deadsprite evilmushroomdead ) ( deathseq ( give hero 10 points ) ) ( resurrectpositions ) ) ( duck gamechar ( coord 46.0 1.5 ) ( speed 1.0 0.0 ) ( width 1.0 ) ( height 1.6875 ) ( ext 0.5 0.5 0.84375 0.84375 ) ( name Duck ) ( type 2 ) ( points 0.0 ) ( vp 1 ) ( direction 1 ) ( state 1 ) ( ability 1153 ) ( howdies 209 ) ( howkills 14 ) ( idlesprite duck ) ( walksprite duckwalk ) ( jumpsprite none ) ( glidesprite duckdead ) ( flysprite none ) ( deadsprite duckdead ) ( deathseq ( dontdie ) ( give hero 10 points ) ( add me ability glide ) ( add me ability break ) ( remove me ability walk ) ( remove me ability die during 200 ) ( change me ( sprite duckdead ) ( ext 0.5 0.5 0.099999845 0.84375 ) ( speed 8 0 ) ( state gliding ) ( deathseq ) ) ) ( resurrectpositions ) ) ( mushroom gamechar ( coord 8.0 1.0 ) ( speed 1.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( ext 0.5 0.5 0.5 0.5 ) ( name Mushroom ) ( type 3 ) ( points 0.0 ) ( vp 1 ) ( direction 1 ) ( state 1 ) ( ability 1025 ) ( howdies 15 ) ( howkills 0 ) ( idlesprite mushroom ) ( walksprite mushroom ) ( jumpsprite none ) ( glidesprite none ) ( flysprite none ) ( deadsprite none ) ( deathseq ( change hero ( name SuperJuan ) ( idlesprite superjuanidle ) ( walksprite superjuanwalk ) ( jumpsprite superjuanjump ) ( flysprite superjuanswim ) ( height 1.625 ) ( ext 0.3499994278 0.3499994278 0.8249998093 0.8249998093 ) ( deathseq ( dontdie ) ( remove hero ability die during 2000 ) ( change hero ( name Juan ) ( idlesprite juanidle ) ( walksprite juanwalk ) ( jumpsprite juanjump ) ( height 1 ) ( ext 0.3999996185 0.3999996185 0.5 0.5 ) ( deathseq ) ) ( remove hero ability break ) ) ) ( add hero ability break ) ) ( resurrectpositions ) ) ( vpmushroom gamechar ( coord 8.0 1.0 ) ( speed 1.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( ext 0.5 0.5 0.5 0.5 ) ( name VPMushroom ) ( type 3 ) ( points 0.0 ) ( vp 1 ) ( direction 1 ) ( state 1 ) ( ability 1025 ) ( howdies 15 ) ( howkills 0 ) ( idlesprite vpmushroom ) ( walksprite vpmushroom ) ( jumpsprite none ) ( glidesprite none ) ( flysprite none ) ( deadsprite none ) ( deathseq ( give hero 1 vp ) ) ( resurrectpositions ) ) ( star gamechar ( coord 8.0 1.0 ) ( speed 1.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( ext 0.5 0.5 0.5 0.5 ) ( name Star ) ( type 3 ) ( points 0.0 ) ( vp 1 ) ( direction 1 ) ( state 2 ) ( ability 1026 ) ( howdies 15 ) ( howkills 0 ) ( idlesprite star ) ( walksprite star ) ( jumpsprite star ) ( glidesprite star ) ( flysprite star ) ( deadsprite none ) ( deathseq ( remove hero ability die during 15000 ) ) ( resurrectpositions ) ) ( firebullet gamechar ( coord 8.0 1.0 ) ( speed 10.0 0.0 ) ( width 0.625 ) ( height 0.625 ) ( ext 0.3125 0.3125 0.3125 0.3125 ) ( name FireBullet ) ( type 4 ) ( points 0.0 ) ( vp 1 ) ( direction 1 ) ( state 4 ) ( ability 1156 ) ( howdies 32 ) ( howkills 15 ) ( idlesprite superjuanfirebullet ) ( walksprite none ) ( jumpsprite none ) ( glidesprite none ) ( flysprite superjuanfirebullet ) ( deadsprite none ) ( deathseq ) ( resurrectpositions ) ) ( pipe portal ( coord 5. 1. ) ( width 2. ) ( height 2. ) ( name Pipe ) ( sprite pipe ) ( open 1 ) ( howenter 1 ) ( howexit 0 ) ( enterseq ( goto level juanlevelswim.txt at PipeRev ) ) ( exitseq ) ( music ) ( heroonly 1 ) ) ( door portal ( coord 55. 1. ) ( width 1. ) ( height 2. ) ( name Door ) ( sprite door ) ( open 1 ) ( howenter 4 ) ( howexit 0 ) ( enterseq ( win ) ) ( exitseq ) ( music ) ( heroonly 1 ) ) ) \
                                                  ( gamechars ( ( coord 1.0 1.0 ) ( speed 0.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( ext 0.3 0.3 0.5 0.5 ) ( name Juan ) ( type 1 ) ( points 0.0 ) ( vp 3 ) ( direction 0 ) ( state 0 ) ( ability 1155 ) ( howdies 207 ) ( howkills 2 ) ( idlesprite juanidle ) ( walksprite juanwalk ) ( jumpsprite juanjump ) ( glidesprite juanidle ) ( flysprite juanfly ) ( deadsprite juandead ) ( deathseq die ) ( resurrectpositions ( 2 1 ) ( 17 1 ) ) ) ( ( coord 18.0 1.25 ) ( speed 0.0 0.0 ) ( width 1.0 ) ( height 1.5 ) ( ext 0.5 0.5 0.75 0.75 ) ( name Plant ) ( type 2 ) ( points 0.0 ) ( vp 1 ) ( direction 0 ) ( state 0 ) ( ability 128 ) ( howdies 0 ) ( howkills 1 ) ( idlesprite plant ) ( walksprite none ) ( jumpsprite none ) ( glidesprite none ) ( flysprite none ) ( deadsprite none ) ( deathseq ) ( resurrectpositions ) ) ( ( coord 38.0 1.25 ) ( speed 0.0 0.0 ) ( width 1.0 ) ( height 1.5 ) ( ext 0.5 0.5 0.75 0.75 ) ( name Plant ) ( type 2 ) ( points 0.0 ) ( vp 1 ) ( direction 0 ) ( state 0 ) ( ability 128 ) ( howdies 0 ) ( howkills 1 ) ( idlesprite plant ) ( walksprite none ) ( jumpsprite none ) ( glidesprite none ) ( flysprite none ) ( deadsprite none ) ( deathseq ) ( resurrectpositions ) ) ( ( coord 39.0 1.25 ) ( speed 0.0 0.0 ) ( width 1.0 ) ( height 1.5 ) ( ext 0.5 0.5 0.75 0.75 ) ( name Plant ) ( type 2 ) ( points 0.0 ) ( vp 1 ) ( direction 0 ) ( state 0 ) ( ability 128 ) ( howdies 0 ) ( howkills 1 ) ( idlesprite plant ) ( walksprite none ) ( jumpsprite none ) ( glidesprite none ) ( flysprite none ) ( deadsprite none ) ( deathseq ) ( resurrectpositions ) ) ( ( coord 20.55 1.0 ) ( speed -1.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( ext 0.5 0.5 0.5 0.5 ) ( name EvilMushroom ) ( type 2 ) ( points 0.0 ) ( vp 1 ) ( direction -1 ) ( state 1 ) ( ability 1153 ) ( howdies 209 ) ( howkills 14 ) ( idlesprite evilmushroom ) ( walksprite evilmushroom ) ( jumpsprite none ) ( glidesprite none ) ( flysprite none ) ( deadsprite evilmushroomdead ) ( deathseq ( give hero 10 points ) ) ( resurrectpositions ) ) ( ( coord 46.299988 1.34375 ) ( speed -1.0 0.0 ) ( width 1.0 ) ( height 1.6875 ) ( ext 0.5 0.5 0.84375 0.84375 ) ( name Duck ) ( type 2 ) ( points 0.0 ) ( vp 1 ) ( direction -1 ) ( state 1 ) ( ability 1153 ) ( howdies 209 ) ( howkills 14 ) ( idlesprite duck ) ( walksprite duckwalk ) ( jumpsprite none ) ( glidesprite duckdead ) ( flysprite none ) ( deadsprite duckdead ) ( deathseq ( dontdie ) ( give hero 10 points ) ( add me ability glide ) ( add me ability break ) ( remove me ability walk ) ( remove me ability die during 200 ) ( change me ( sprite duckdead ) ( ext 0.5 0.5 0.1 0.84375 ) ( speed 8 0 ) ( state gliding ) ( deathseq ) ) ) ( resurrectpositions ) ) ( ( coord 48.299988 1.34375 ) ( speed 1.0 0.0 ) ( width 1.0 ) ( height 1.6875 ) ( ext 0.5 0.5 0.84375 0.84375 ) ( name Duck ) ( type 2 ) ( points 0.0 ) ( vp 1 ) ( direction 1 ) ( state 1 ) ( ability 1153 ) ( howdies 209 ) ( howkills 14 ) ( idlesprite duck ) ( walksprite duckwalk ) ( jumpsprite none ) ( glidesprite duckdead ) ( flysprite none ) ( deadsprite duckdead ) ( deathseq ( dontdie ) ( give hero 10 points ) ( add me ability glide ) ( add me ability break ) ( remove me ability walk ) ( remove me ability die during 200 ) ( change me ( sprite duckdead ) ( ext 0.5 0.5 0.1 0.84375 ) ( speed 8 0 ) ( state gliding ) ( deathseq ) ) ) ( resurrectpositions ) ) ( ( coord 56.0 7.0 ) ( speed 1.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( ext 0.5 0.5 0.5 0.5 ) ( name EvilMushroom ) ( type 2 ) ( points 0.0 ) ( vp 1 ) ( direction 1 ) ( state 1 ) ( ability 1153 ) ( howdies 209 ) ( howkills 14 ) ( idlesprite evilmushroom ) ( walksprite evilmushroom ) ( jumpsprite none ) ( glidesprite none ) ( flysprite none ) ( deadsprite evilmushroomdead ) ( deathseq ( give hero 10 points ) ) ( resurrectpositions ) ) ( ( coord 59.299988 0.0 ) ( speed 1.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( ext 0.5 0.5 0.5 0.5 ) ( name EvilMushroom ) ( type 2 ) ( points 0.0 ) ( vp 1 ) ( direction 1 ) ( state 1 ) ( ability 1153 ) ( howdies 209 ) ( howkills 14 ) ( idlesprite evilmushroom ) ( walksprite evilmushroom ) ( jumpsprite none ) ( glidesprite none ) ( flysprite none ) ( deadsprite evilmushroomdead ) ( deathseq ( give hero 10 points ) ) ( resurrectpositions ) ) ( ( coord 61.0 1.0 ) ( speed 1.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( ext 0.5 0.5 0.5 0.5 ) ( name EvilMushroom ) ( type 2 ) ( points 0.0 ) ( vp 1 ) ( direction 1 ) ( state 1 ) ( ability 1153 ) ( howdies 209 ) ( howkills 14 ) ( idlesprite evilmushroom ) ( walksprite evilmushroom ) ( jumpsprite none ) ( glidesprite none ) ( flysprite none ) ( deadsprite evilmushroomdead ) ( deathseq ( give hero 10 points ) ) ( resurrectpositions ) ) ( ( coord 10.05 1.0 ) ( speed -1.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( ext 0.5 0.5 0.5 0.5 ) ( name EvilMushroom ) ( type 2 ) ( points 0.0 ) ( vp 1 ) ( direction -1 ) ( state 1 ) ( ability 1153 ) ( howdies 209 ) ( howkills 14 ) ( idlesprite evilmushroom ) ( walksprite evilmushroom ) ( jumpsprite none ) ( glidesprite none ) ( flysprite none ) ( deadsprite evilmushroomdead ) ( deathseq ( give hero 10 points ) ) ( resurrectpositions ) ) ( ( coord 80.0 1.0 ) ( speed 1.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( ext 0.5 0.5 0.5 0.5 ) ( name EvilMushroom ) ( type 2 ) ( points 0.0 ) ( vp 1 ) ( direction 1 ) ( state 1 ) ( ability 1153 ) ( howdies 209 ) ( howkills 14 ) ( idlesprite evilmushroom ) ( walksprite evilmushroom ) ( jumpsprite none ) ( glidesprite none ) ( flysprite none ) ( deadsprite evilmushroomdead ) ( deathseq ( give hero 10 points ) ) ( resurrectpositions ) ) ( ( coord 79.0 1.0 ) ( speed 1.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( ext 0.5 0.5 0.5 0.5 ) ( name EvilMushroom ) ( type 2 ) ( points 0.0 ) ( vp 1 ) ( direction 1 ) ( state 1 ) ( ability 1153 ) ( howdies 209 ) ( howkills 14 ) ( idlesprite evilmushroom ) ( walksprite evilmushroom ) ( jumpsprite none ) ( glidesprite none ) ( flysprite none ) ( deadsprite evilmushroomdead ) ( deathseq ( give hero 10 points ) ) ( resurrectpositions ) ) ( ( coord 77.0 1.0 ) ( speed 1.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( ext 0.5 0.5 0.5 0.5 ) ( name EvilMushroom ) ( type 2 ) ( points 0.0 ) ( vp 1 ) ( direction 1 ) ( state 1 ) ( ability 1153 ) ( howdies 209 ) ( howkills 14 ) ( idlesprite evilmushroom ) ( walksprite evilmushroom ) ( jumpsprite none ) ( glidesprite none ) ( flysprite none ) ( deadsprite evilmushroomdead ) ( deathseq ( give hero 10 points ) ) ( resurrectpositions ) ) ( ( coord 75.0 1.0 ) ( speed 1.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( ext 0.5 0.5 0.5 0.5 ) ( name EvilMushroom ) ( type 2 ) ( points 0.0 ) ( vp 1 ) ( direction 1 ) ( state 1 ) ( ability 1153 ) ( howdies 209 ) ( howkills 14 ) ( idlesprite evilmushroom ) ( walksprite evilmushroom ) ( jumpsprite none ) ( glidesprite none ) ( flysprite none ) ( deadsprite evilmushroomdead ) ( deathseq ( give hero 10 points ) ) ( resurrectpositions ) ) ) \
                                                  ( blocks ( ( coord -1.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord -1.0 1.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 0 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 0.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 1.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 2.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 3.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 4.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 5.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 6.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 7.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 8.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 9.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 10.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 11.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 11.0 6.0 ) ( width 1.0 ) ( height 1.0 ) ( name Wood ) ( sprite wood ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 12.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 12.0 6.0 ) ( width 1.0 ) ( height 1.0 ) ( name Note ) ( sprite note ) ( howhit 15 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ( ( 0.0 ( 5111.65625 500.0 100 ) ) ) ) ) ( ( coord 13.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 13.0 6.0 ) ( width 1.0 ) ( height 1.0 ) ( name Wood ) ( sprite wood ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 14.0 1.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 14.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 15.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 15.0 2.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 15.0 1.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 16.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 17.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 18.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 19.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 20.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 21.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 21.0 4.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 22.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 22.0 4.0 ) ( width 1.0 ) ( height 1.0 ) ( name MushroomQuestionMark ) ( sprite questionmark ) ( howhit 130 ) ( hitseq ( ( generate mushroom from me ) ( change me ( sprite questionidle ) ( howhit ) ) ) ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ( ( 0.0 ( 3732.228516 500.0 100 ) ) ) ) ) ( ( coord 23.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 23.0 4.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 24.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 25.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 26.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 26.0 1.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 26.0 2.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 27.0 1.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 27.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 31.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 32.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 33.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 33.0 4.0 ) ( width 1.0 ) ( height 1.0 ) ( name CoinsStarQuestionMark ) ( sprite questionmark ) ( howhit 130 ) ( hitseq ( give hero 10 points ) ( give hero 10 points ) ( give hero 10 points ) ( give hero 10 points ) ( change me ( sprite questionidle ) ( howhit ) ) ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ( ( 0.0 ( 8376.171875 500.0 100 ) ) ) ) ) ( ( coord 34.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 35.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 36.0 1.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 36.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 36.0 2.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 36.0 3.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 37.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 38.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 39.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 40.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 41.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 42.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 43.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 44.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 45.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 46.0 4.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 46.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 47.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 47.0 4.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 48.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 48.0 4.0 ) ( width 1.0 ) ( height 1.0 ) ( name CoinsStarQuestionMark ) ( sprite questionmark ) ( howhit 130 ) ( hitseq ( give hero 10 points ) ( give hero 10 points ) ( give hero 10 points ) ( give hero 10 points ) ( ( generate star ) ( change me ( sprite questionidle ) ( howhit ) ) ) ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ( ( 0.0 ( 8376.171875 500.0 100 ) ) ) ) ) ( ( coord 49.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 49.0 4.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 50.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 51.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 52.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 53.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 54.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 55.0 6.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 55.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 56.0 6.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 56.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 57.0 6.0 ) ( width 1.0 ) ( height 1.0 ) ( name Wood ) ( sprite wood ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 57.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 57.0 2.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 57.0 1.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 58.0 6.0 ) ( width 1.0 ) ( height 1.0 ) ( name Wood ) ( sprite wood ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 58.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 58.0 2.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 59.0 6.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 59.0 2.0 ) ( width 1.0 ) ( height 1.0 ) ( name Note ) ( sprite note ) ( howhit 15 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ( ( 0.0 ( 5111.65625 500.0 100 ) ) ) ) ) ( ( coord 59.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 60.0 2.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 60.0 6.0 ) ( width 1.0 ) ( height 1.0 ) ( name CoinsStarQuestionMark ) ( sprite questionmark ) ( howhit 130 ) ( hitseq ( ( generate mushroom ) ( change me ( sprite questionidle ) ( howhit ) ) ) ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ( ( 0.0 ( 8376.171875 500.0 100 ) ) ) ) ) ( ( coord 60.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 61.0 6.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 61.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 61.0 2.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 62.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 62.0 2.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 62.0 1.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 63.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 64.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 65.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 66.0 8.0 ) ( width 1.0 ) ( height 1.0 ) ( name CoinsStarQuestionMark ) ( sprite questionmark ) ( howhit 130 ) ( hitseq ( ( generate vpmushroom ) ( change me ( sprite questionidle ) ( howhit ) ) ) ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ( ( 0.0 ( 8376.171875 500.0 100 ) ) ) ) ) ( ( coord 66.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 67.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 68.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 69.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 70.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 70.0 4.0 ) ( width 1.0 ) ( height 1.0 ) ( name CoinsStarQuestionMark ) ( sprite questionmark ) ( howhit 130 ) ( hitseq ( give hero 10 points ) ( give hero 10 points ) ( give hero 10 points ) ( give hero 10 points ) ( ( generate star ) ( change me ( sprite questionidle ) ( howhit ) ) ) ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ( ( 0.0 ( 8376.171875 500.0 100 ) ) ) ) ) ( ( coord 71.0 4.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 71.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 72.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 72.0 4.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 73.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 73.0 4.0 ) ( width 1.0 ) ( height 1.0 ) ( name Brick ) ( sprite brick ) ( howhit 130 ) ( hitseq break ) ( loophitseq 1 ) ( breaksprite breakbrick ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 74.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 75.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 76.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 77.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 78.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 79.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 80.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 81.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 82.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 83.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 84.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 85.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 86.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 87.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 88.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 89.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 90.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 91.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 92.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 93.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 94.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 95.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 96.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 97.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 98.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 99.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 100.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 101.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ( ( coord 102.0 0.0 ) ( width 1.0 ) ( height 1.0 ) ( name Ground ) ( sprite ground ) ( howhit 0 ) ( hitseq ) ( loophitseq 0 ) ( breaksprite none ) ( state 0 ) ( pointsgiven 0.0 ) ( music ) ) ) \
                                                  ( coins ( ( coord 5.0 6.0 ) ( width 0.75 ) ( height 1.0 ) ( name Coin ) ( sprite coin ) ( takeable 1 ) ( taken 0 ) ( pointsgiven 10.0 ) ( vpgiven 0 ) ( music roll ( ( 0 ( 7900 100 100 ) ) ( 100 ( 8400 100 100 ) ) ) ) ) ( ( coord 5.0 7.0 ) ( width 0.75 ) ( height 1.0 ) ( name Coin ) ( sprite coin ) ( takeable 1 ) ( taken 0 ) ( pointsgiven 10.0 ) ( vpgiven 0 ) ( music roll ( ( 0 ( 7900 100 100 ) ) ( 100 ( 8400 100 100 ) ) ) ) ) ( ( coord 6.0 6.0 ) ( width 0.75 ) ( height 1.0 ) ( name Coin ) ( sprite coin ) ( takeable 1 ) ( taken 0 ) ( pointsgiven 10.0 ) ( vpgiven 0 ) ( music roll ( ( 0 ( 7900 100 100 ) ) ( 100 ( 8400 100 100 ) ) ) ) ) ( ( coord 6.0 7.0 ) ( width 0.75 ) ( height 1.0 ) ( name Coin ) ( sprite coin ) ( takeable 1 ) ( taken 0 ) ( pointsgiven 10.0 ) ( vpgiven 0 ) ( music roll ( ( 0 ( 7900 100 100 ) ) ( 100 ( 8400 100 100 ) ) ) ) ) ( ( coord 16.0 9.0 ) ( width 0.75 ) ( height 1.0 ) ( name Coin ) ( sprite coin ) ( takeable 1 ) ( taken 0 ) ( pointsgiven 10.0 ) ( vpgiven 0 ) ( music roll ( ( 0 ( 7900 100 100 ) ) ( 100 ( 8400 100 100 ) ) ) ) ) ( ( coord 17.0 9.0 ) ( width 0.75 ) ( height 1.0 ) ( name Coin ) ( sprite coin ) ( takeable 1 ) ( taken 0 ) ( pointsgiven 10.0 ) ( vpgiven 0 ) ( music roll ( ( 0 ( 7900 100 100 ) ) ( 100 ( 8400 100 100 ) ) ) ) ) ( ( coord 72.0 8.0 ) ( width 0.75 ) ( height 1.0 ) ( name Coin ) ( sprite coin ) ( takeable 1 ) ( taken 0 ) ( pointsgiven 10.0 ) ( vpgiven 0 ) ( music roll ( ( 0 ( 7900 100 100 ) ) ( 100 ( 8400 100 100 ) ) ) ) ) ( ( coord 73.0 9.0 ) ( width 0.75 ) ( height 1.0 ) ( name Coin ) ( sprite coin ) ( takeable 1 ) ( taken 0 ) ( pointsgiven 10.0 ) ( vpgiven 0 ) ( music roll ( ( 0 ( 7900 100 100 ) ) ( 100 ( 8400 100 100 ) ) ) ) ) ( ( coord 74.0 8.0 ) ( width 0.75 ) ( height 1.0 ) ( name Coin ) ( sprite coin ) ( takeable 1 ) ( taken 0 ) ( pointsgiven 10.0 ) ( vpgiven 0 ) ( music roll ( ( 0 ( 7900 100 100 ) ) ( 100 ( 8400 100 100 ) ) ) ) ) ( ( coord 75.0 9.0 ) ( width 0.75 ) ( height 1.0 ) ( name Coin ) ( sprite coin ) ( takeable 1 ) ( taken 0 ) ( pointsgiven 10.0 ) ( vpgiven 0 ) ( music roll ( ( 0 ( 7900 100 100 ) ) ( 100 ( 8400 100 100 ) ) ) ) ) ( ( coord 76.0 8.0 ) ( width 0.75 ) ( height 1.0 ) ( name Coin ) ( sprite coin ) ( takeable 1 ) ( taken 0 ) ( pointsgiven 10.0 ) ( vpgiven 0 ) ( music roll ( ( 0 ( 7900 100 100 ) ) ( 100 ( 8400 100 100 ) ) ) ) ) ( ( coord 77.0 9.0 ) ( width 0.75 ) ( height 1.0 ) ( name Coin ) ( sprite coin ) ( takeable 1 ) ( taken 0 ) ( pointsgiven 10.0 ) ( vpgiven 0 ) ( music roll ( ( 0 ( 7900 100 100 ) ) ( 100 ( 8400 100 100 ) ) ) ) ) ( ( coord 84.0 7.0 ) ( width 0.75 ) ( height 1.0 ) ( name Coin ) ( sprite coin ) ( takeable 1 ) ( taken 0 ) ( pointsgiven 10.0 ) ( vpgiven 0 ) ( music roll ( ( 0 ( 7900 100 100 ) ) ( 100 ( 8400 100 100 ) ) ) ) ) ( ( coord 85.0 9.0 ) ( width 0.75 ) ( height 1.0 ) ( name Coin ) ( sprite coin ) ( takeable 1 ) ( taken 0 ) ( pointsgiven 10.0 ) ( vpgiven 0 ) ( music roll ( ( 0 ( 7900 100 100 ) ) ( 100 ( 8400 100 100 ) ) ) ) ) ( ( coord 86.0 8.0 ) ( width 0.75 ) ( height 1.0 ) ( name Coin ) ( sprite coin ) ( takeable 1 ) ( taken 0 ) ( pointsgiven 10.0 ) ( vpgiven 0 ) ( music roll ( ( 0 ( 7900 100 100 ) ) ( 100 ( 8400 100 100 ) ) ) ) ) ( ( coord 87.0 7.0 ) ( width 0.75 ) ( height 1.0 ) ( name Coin ) ( sprite coin ) ( takeable 1 ) ( taken 0 ) ( pointsgiven 10.0 ) ( vpgiven 0 ) ( music roll ( ( 0 ( 7900 100 100 ) ) ( 100 ( 8400 100 100 ) ) ) ) ) ( ( coord 88.0 9.0 ) ( width 0.75 ) ( height 1.0 ) ( name Coin ) ( sprite coin ) ( takeable 1 ) ( taken 0 ) ( pointsgiven 10.0 ) ( vpgiven 0 ) ( music roll ( ( 0 ( 7900 100 100 ) ) ( 100 ( 8400 100 100 ) ) ) ) ) ( ( coord 89.0 8.0 ) ( width 0.75 ) ( height 1.0 ) ( name Coin ) ( sprite coin ) ( takeable 1 ) ( taken 0 ) ( pointsgiven 10.0 ) ( vpgiven 0 ) ( music roll ( ( 0 ( 7900 100 100 ) ) ( 100 ( 8400 100 100 ) ) ) ) ) ( ( coord 90.0 7.0 ) ( width 0.75 ) ( height 1.0 ) ( name Coin ) ( sprite coin ) ( takeable 1 ) ( taken 0 ) ( pointsgiven 10.0 ) ( vpgiven 0 ) ( music roll ( ( 0 ( 7900 100 100 ) ) ( 100 ( 8400 100 100 ) ) ) ) ) ) \
                                                  ( portals ( ( coord 88.0 1.0 ) ( width 2.0 ) ( height 2.0 ) ( name Pipe ) ( sprite pipe ) ( open 1 ) ( howenter 1 ) ( howexit 0 ) ( enterseq ( goto portal PipeFromAbove ) ) ( exitseq ) ( music ) ( heroonly 1 ) ) ( ( coord 94.0 9.0 ) ( width 2.0 ) ( height 2.0 ) ( name PipeFromAbove ) ( sprite piperev ) ( open 1 ) ( howenter 0 ) ( howexit 2 ) ( enterseq ) ( exitseq ) ( music ) ( heroonly 1 ) ) ( ( coord 97.0 1.0 ) ( width 2.0 ) ( height 2.0 ) ( name Pipe ) ( sprite pipe ) ( open 1 ) ( howenter 1 ) ( howexit 0 ) ( enterseq ( add hero ability fly ) ( goto level juanlevelswim.txt at PipeRev with ( keephero 1 ) ) ) ( exitseq ) ( music ) ( heroonly 1 ) ) )", true);
        }
        
        if (retrieved_from_saved_state) {
            attr_dictionary_process(x,d);
            platform_set_state(x, llll_for_rebuild);
            llllobj_manage_dict_llll((t_object *)x, LLLL_OBJ_UI, llll_for_rebuild);
        } else {
            platform_set_state(x, llll_for_rebuild);
            attr_dictionary_process(x,d);
        }
        
/*        // PORTALS
        long idx = dadaitem_portal_add(dadaobj_cast(x), build_pt(5, 1.), 2, 2, DADA_BLACK, gensym("Pipe"), gensym("pipe"), true, DADA_GAMECHAR_VIA_SIDE_TOP, 0, llll_from_text_buf("(goto level juanlevelswim.txt at PipeRev)", false), NULL, NULL, true, 0, 0);
        platform_ezadd_prototype_from_dadaitem(x, gensym("pipe"), dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_PORTAL), idx));
        
        idx = dadaitem_portal_add(dadaobj_cast(x), build_pt(55, 1.), 1, 2, DADA_BLACK, gensym("Door"), gensym("door"), true, DADA_GAMECHAR_VIA_SIDE_LEFT, 0, llll_from_text_buf("(win)", false), NULL, NULL, true, 0, 0);
        platform_ezadd_prototype_from_dadaitem(x, gensym("door"), dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_PORTAL), idx));
*/
        
        llll_free(llll_for_rebuild);
        
        if (!x->m_level.has_intro)
            x->play_state = DADA_PLATFORM_PLAYSTATE_STANDARD;
		else if (x->play_state == DADA_PLATFORM_PLAYSTATE_LEVELINTRO || DADA_PLATFORM_PLAYSTATE_LEVELINTRO_PRE)
            x->play_state = DADA_PLATFORM_PLAYSTATE_LEVELINTRO_POST; // just the first time
        
        x->fixed_state = platform_get_state(x);
        
		platform_sort_blocks(x);
		platform_sort_coins(x);
        platform_sort_portals(x);

        jbox_ready((t_jbox *)x);
        
        dadaobj_set_current_version_number(dadaobj_cast(x));
        
        x->creating_new_obj = false;
    }
	return x;
}

void platform_int(t_platform *x, t_atom_long num)
{
    if (num)
        platform_play(x, NULL, 0, NULL);
    else
        platform_stop(x, NULL, 0, NULL);
/*	t_atom argv[1];
	atom_setlong(argv, num);
	platform_anything(x, _sym_list, 1, argv);*/
}

void platform_float(t_platform *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	platform_anything(x, _sym_list, 1, argv);
}

void platform_dump(t_platform *x, char get_levelinfo, char get_sprites, char get_prototypes, char get_gamechars, char get_blocks, char get_coins, char get_portals)
{	
	t_llll *ll = platform_get_state_ext(x, get_levelinfo, get_sprites, get_prototypes, get_gamechars, get_blocks, get_coins, get_portals);
	llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 0, ll);
	llll_free(ll);
}




void platform_anything(t_platform *x, t_symbol *msg, long ac, t_atom *av)
{
	dadaobj_anything(dadaobj_cast(x), msg, ac, av);

	long num_inlet = proxy_getinlet((t_object *)x);
	t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, msg, ac, av, LLLL_PARSE_CLONE);
	if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
		t_symbol *router = hatom_getsym(&parsed->l_head->l_hatom);
		llll_behead(parsed);
		
        if (dadaobj_anything_handle_domain_or_range(dadaobj_cast(x), router, parsed)) {
            // nothing to do!
        } else if (router == gensym("break"))
			x->break_after_notification = 1;
        else if (router == gensym("resettime"))
            x->global_time = 0;
        else if (router == gensym("fix") || router == gensym("fixlevel")) {
            llll_free(x->fixed_state);
            x->fixed_state = platform_get_state(x);
        } else if (router == gensym("restart"))
            platform_restart(x, (parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_LONG ? hatom_getlong(&parsed->l_head->l_hatom) : 3));
        else if (router == gensym("addsprite"))
            platform_add_sprite(x, parsed);
        else if (router == gensym("addprototype"))
            platform_add_prototype(x, parsed);
        else if (router == gensym("script")) {
            t_llll *instructions = llll_clone(parsed);
            if (instructions && instructions->l_head && hatom_gettype(&instructions->l_head->l_hatom) != H_LLLL)
                llll_wrap_once(&instructions);
            parse_instructions(x, instructions, NULL);
            llll_free(instructions);
        } else if (router == gensym("count")) {
            t_llllelem *temp = parsed->l_head;
            if (temp && hatom_gettype(&temp->l_hatom) == H_SYM) {
                t_symbol *what = hatom_getsym(&temp->l_hatom);
                t_llll *elems = NULL;
                
                if (what == gensym("gamechars"))
                    elems = llll_clone(x->gamechars);
                else if (what == gensym("blocks"))
                    elems = llll_clone(x->blocks);
                else if (what == gensym("portals"))
                    elems = llll_clone(x->portals);
                else if (what == gensym("coins"))
                    elems = llll_clone(x->coins);
                else {
                    elems = llll_clone(x->blocks);
                    llll_chain_clone(elems, x->coins);
                    llll_chain_clone(elems, x->gamechars);
                    llll_chain_clone(elems, x->portals);
                }
                
                temp = temp->l_next;
                if (temp && hatom_gettype(&temp->l_hatom) == H_SYM && hatom_getsym(&temp->l_hatom) == gensym("where")) {
                    temp = temp->l_next;
                    while (temp) {
                        if (hatom_gettype(&temp->l_hatom) == H_LLLL) {
                            t_llll *attrll = hatom_getllll(&temp->l_hatom);
                            if (attrll && attrll->l_head && hatom_gettype(&attrll->l_head->l_hatom) == H_SYM) {
                                t_symbol *attrname = hatom_getsym(&attrll->l_head->l_hatom);
                                t_llllelem *el, *nextel;
                                for (el = elems->l_head; el; el = nextel) {
                                    nextel = el->l_next;
                                    t_dadaitem *item = (t_dadaitem *)hatom_getobj(&el->l_hatom);
                                    t_bach_attribute *attr = get_dada_attribute(dadaobj_cast(x), item->type, attrname);
                                    if (attr) {
                                        t_llll *actual_attr_val = dadaitem_get_attr_as_llll(dadaobj_cast(x), item, attr);
                                        if (!llll_eq_ignoretype(attrll, actual_attr_val))
                                            llll_destroyelem(el);
                                        llll_free(actual_attr_val);
                                    } else
                                        llll_destroyelem(el);
                                }
                            }
                        }
                        temp = temp->l_next;
                    }
                }
                
                t_llll *outll = llll_get();
                llll_appendsym(outll, gensym("count"));
                llll_appendlong(outll, elems->l_size);
                send_notification(x, outll);
                llll_free(outll);
                
                llll_free(elems);
            }
        } else if (router == gensym("clear")) {
            platform_undo_step_push(x, gensym("Clear"));
            platform_clear(x, parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("levelinfo")),
                           parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("sprites")),
                           parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("prototypes")),
                           parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("gamechars")),
                           parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("blocks")),
                           parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("coins")),
                           parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("portals")), DIA_UNDO_POSTPROCESS);
            platform_iar(x);
        } else if (router == gensym("setstoredstate") || router == gensym("platform")) {
            load_default_goto_options(x);
            platform_set_state(x, parsed);
        } else if (router == _sym_dump)
			platform_dump(x,
                          parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("levelinfo")),
                          parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("sprites")),
						  parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("prototypes")),
						  parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("gamechars")),
						  parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("blocks")),
						  parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("coins")),
                          parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("portals")));
		else if (router == gensym("add"))
			dadaitem_add_from_message(dadaobj_cast(x), parsed, DIA_UNDO_POSTPROCESS);
		else if (router == gensym("delete"))
			dadaitem_delete_from_message(dadaobj_cast(x), parsed, DIA_UNDO_POSTPROCESS);
		else if (router == gensym("set"))
			dadaitem_set_from_message(dadaobj_cast(x), parsed, DIA_UNDO_POSTPROCESS);
		
	} else if (parsed) {
        load_default_goto_options(x);
		platform_set_state(x, parsed);
	}
	llll_free(parsed);
	jbox_redraw((t_jbox *)x);
}



//// GRAPHIC DRAWING


void platform_paint_sprite(t_platform *x, t_jgraphics *g, t_dada_sprite *sprite, t_rect source, t_rect dest, char direction, char invincibility)
{
    char apply_deltacolor = false;
    t_jhsla deltacolor;
    long slide_idx = sprite->slide_time == 0 ? 0 : positive_mod((long)floor(x->global_time/sprite->slide_time), MAX(1, sprite->num_slides));
    if (invincibility && (long)floor(x->global_time/150) % 2) {
        deltacolor.alpha = 1.;
        deltacolor.hue = 0.4;
        deltacolor.saturation = 0.5;
        deltacolor.lightness = 1.2;
        apply_deltacolor = true;
    }
    paint_sprite(g, sprite, slide_idx, source, dest, direction, apply_deltacolor ? &deltacolor : NULL);
}

void platform_paint_background(t_platform *x, t_jgraphics *g, t_rect rect, t_pt center, double zoom)
{
    t_dada_sprite *bgsprite = label_to_sprite(x, x->m_level.background_sprite);
    if (bgsprite) {
        t_pt anchor_coord = build_pt(0, x->m_level.level_height);
        t_pt anchor_pix = coord_to_pix(dadaobj_cast(x), center, anchor_coord);
        double ah = -delta_coord_to_delta_pix(dadaobj_cast(x), build_pt(0, x->m_level.level_height)).y;
        platform_paint_sprite(x, g, bgsprite, bgsprite->source_rect, build_rect(anchor_pix.x, anchor_pix.y, ah * bgsprite->source_rect.width/bgsprite->source_rect.height, ah), 0);
    } else {
        dadaobj_paint_background(dadaobj_cast(x), g, &rect);
    }
}


void platform_paint_blocks(t_platform *x, t_jgraphics *g, t_rect rect, t_pt center, double zoom)
{
    t_llllelem *blockelem;
    t_jrgba inner_rect_color = change_alpha(x->j_selectioncolor, 0.2);
    for (blockelem = x->blocks->l_head; blockelem; blockelem = blockelem->l_next) {
        t_dada_block *block = (t_dada_block *)hatom_getobj(&blockelem->l_hatom);

        if (!platform_is_dadaitem_in_screen(x, (t_dadaitem *)block, 1))
            continue;

        switch (block->state) {
            case DADA_BLOCK_INVISIBLE:
                break;

            case DADA_BLOCK_BREAKING:
            {
                t_dada_sprite *fragment_sprite = label_to_sprite(x, block->fragment_sprite);
                
                if (fragment_sprite) {
                    t_rect display_rect1 = rect_coord_to_pix(dadaobj_cast(x), center, rect_baricentric_to_boundingbox(build_rect(block->r_it.coord.x + block->broken_slice_delta_coord.x, block->r_it.coord.y + block->broken_slice_delta_coord.y, block->r_it.width, block->r_it.height)), true);
                    t_rect display_rect2 = rect_coord_to_pix(dadaobj_cast(x), center, rect_baricentric_to_boundingbox(build_rect(block->r_it.coord.x - block->broken_slice_delta_coord.x, block->r_it.coord.y + block->broken_slice_delta_coord.y, block->r_it.width, block->r_it.height)), true);
                    platform_paint_sprite(x, g, fragment_sprite, fragment_sprite->source_rect, display_rect1, 0);
                    platform_paint_sprite(x, g, fragment_sprite, fragment_sprite->source_rect, display_rect2, 0);
                }
            }
                break;

            default:
            {
                t_dada_sprite *sprite = label_to_sprite(x, block->sprite);
                
                if (sprite) {
                    t_rect display_rect = rect_coord_to_pix(dadaobj_cast(x), center, rect_baricentric_to_boundingbox(build_rect(block->r_it.coord.x, block->r_it.coord.y, block->r_it.width, block->r_it.height)), true);
                    platform_paint_sprite(x, g, sprite, sprite->source_rect, display_rect, 0);
                }
            }
                break;
        }

        if ((block->r_it.selected != NULL) ^ (block->r_it.preselected != NULL)) {
            t_rect display_rect = rect_coord_to_pix(dadaobj_cast(x), center, rect_baricentric_to_boundingbox(build_rect(block->r_it.coord.x, block->r_it.coord.y, block->r_it.width, block->r_it.height)), true);
            paint_rect(g, &display_rect, &x->j_selectioncolor, &inner_rect_color, 1, 0);
        }
	}
}


void platform_paint_coins(t_platform *x, t_jgraphics *g, t_rect rect, t_pt center, double zoom)
{
	
    t_llllelem *coinelem;
    t_jrgba inner_rect_color = change_alpha(x->j_selectioncolor, 0.2);
    for (coinelem = x->coins->l_head; coinelem; coinelem = coinelem->l_next) {
        t_dada_coin *coin = (t_dada_coin *)hatom_getobj(&coinelem->l_hatom);
        
        if (!platform_is_dadaitem_in_screen(x, (t_dadaitem *)coin, 1))
            continue;

		if (coin->taken)
			continue;

		t_dada_sprite *sprite = label_to_sprite(x, coin->sprite);
		
		if (sprite) {
			t_rect display_rect = rect_coord_to_pix(dadaobj_cast(x), center, dadaitem_get_rect_boundingbox(&coin->r_it), true);
			platform_paint_sprite(x, g, sprite, sprite->source_rect, display_rect, 0);
			if ((coin->r_it.selected != NULL) ^ (coin->r_it.preselected != NULL))
				paint_rect(g, &display_rect, &x->j_selectioncolor, &inner_rect_color, 1, 0);
		}
	}
}

void platform_paint_portals(t_platform *x, t_jgraphics *g, t_rect rect, t_pt center, double zoom)
{
    
    t_llllelem *portalelem;
    t_jrgba inner_rect_color = change_alpha(x->j_selectioncolor, 0.2);
    for (portalelem = x->portals->l_head; portalelem; portalelem = portalelem->l_next) {
        t_dada_portal *portal = (t_dada_portal *)hatom_getobj(&portalelem->l_hatom);
        
        if (!platform_is_dadaitem_in_screen(x, (t_dadaitem *)portal, 1))
            continue;
        
        t_dada_sprite *sprite = label_to_sprite(x, portal->sprite);
        
        if (sprite) {
            t_rect display_rect = rect_coord_to_pix(dadaobj_cast(x), center, dadaitem_get_rect_boundingbox(&portal->r_it), true);
            platform_paint_sprite(x, g, sprite, sprite->source_rect, display_rect, 0);
            if ((portal->r_it.selected != NULL) ^ (portal->r_it.preselected != NULL))
                paint_rect(g, &display_rect, &x->j_selectioncolor, &inner_rect_color, 1, 0);
        }
    }
}


void platform_paint_gamechars(t_platform *x, t_jgraphics *g, t_rect rect, t_pt center, double zoom)
{
	
    t_llllelem *gamecharelem;
    t_jrgba inner_rect_color = change_alpha(x->j_selectioncolor, 0.2);
    
    for (gamecharelem = x->gamechars->l_head; gamecharelem; gamecharelem = gamecharelem->l_next) {
        t_dada_gamechar *gamechar = (t_dada_gamechar *)hatom_getobj(&gamecharelem->l_hatom);

        if (!platform_is_dadaitem_in_screen(x, (t_dadaitem *)gamechar, 1))
            continue;

        t_symbol *spritelabel = NULL;
		switch (gamechar->state) {
			case DADA_GAMECHAR_STATE_DYING:
			case DADA_GAMECHAR_STATE_DEAD:
				spritelabel = gamechar->sprite_dead;
				break;
			case DADA_GAMECHAR_STATE_JUMPING:
				spritelabel = gamechar->sprite_jump;
				break;
			case DADA_GAMECHAR_STATE_WALKING:
				spritelabel = gamechar->sprite_walk;
				break;
            case DADA_GAMECHAR_STATE_GLIDING:
                spritelabel = gamechar->sprite_glide;
                break;
            case DADA_GAMECHAR_STATE_FLYING:
                spritelabel = gamechar->sprite_fly;
                break;
			case DADA_GAMECHAR_STATE_IDLE:
            case DADA_GAMECHAR_STATE_GENERATING:
            case DADA_GAMECHAR_STATE_ENTERINGPORTAL:
            case DADA_GAMECHAR_STATE_EXITINGPORTAL:
				spritelabel = gamechar->sprite_idle;
				break;
			default:
				break;
		}
		
//        post("spritelabel: %s", spritelabel ? spritelabel->s_name : "none");
		t_dada_sprite *sprite = label_to_sprite(x, spritelabel);
		
		if (sprite) {
			t_rect display_rect = rect_coord_to_pix(dadaobj_cast(x), center, dadaitem_get_rect_boundingbox(&gamechar->r_it), true);
			platform_paint_sprite(x, g, sprite, sprite->source_rect, display_rect, gamechar->direction, gamechar->type == DADA_GAMECHAR_TYPE_USERCONTROL && !(gamechar->abilities & DADA_GAMECHAR_ABILITY_DIE));
	 		if ((gamechar->r_it.selected != NULL) ^ (gamechar->r_it.preselected != NULL))
				paint_rect(g, &display_rect, &x->j_selectioncolor, &inner_rect_color, 1, 0);
		}
	}
}

void platform_get_legend(t_platform *x, char *buf)
{
	char *cur = buf;
	long num_gamechars = dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_GAMECHAR);
    t_dada_gamechar *herochar = x->hero;
    
	buf[0] = 0;
	if (herochar) {
        
        if (x->show_legend_title && x->m_level.levelname && x->m_level.levelname != _llllobj_sym_none)
            cur += sprintf(cur, "%s    ", x->m_level.levelname->s_name);

        if (x->show_legend_hero && herochar->r_it.name && herochar->r_it.name != _llllobj_sym_none)
			cur += sprintf(cur, "%s    ", herochar->r_it.name->s_name);
		
		if (x->show_legend_vp) {
			if (herochar->vp > 0)
				cur += sprintf(cur, "%ld VP    ", herochar->vp);
			else
				cur += sprintf(cur, "GAME OVER!    ");
		}

		if (x->show_legend_points)
			cur += sprintf(cur, "%ld pts", (long)round(herochar->points));
		
		*cur = 0;
	}
}

t_rect get_displayed_coord(t_platform *x, t_pt center, t_rect rect)
{
	t_pt p1 = pix_to_coord(dadaobj_cast(x), center, build_pt(0, rect.height));
	t_pt p2 = pix_to_coord(dadaobj_cast(x), center, build_pt(rect.width, 0));
	return build_rect(p1.x, p1.y, p2.x - p1.x, p2.y - p1.y);
}

void fade_hatom(t_platform *x, t_symbol *s, long ac, t_atom *av)
{
	t_llllelem *elem = (t_llllelem *)atom_getobj(av);
	double alpha = atom_getfloat(av + 1);
	
	if (alpha <= 0.)
		llll_destroyelem(elem);
	else {
		t_llll *ll = hatom_getllll(&elem->l_hatom);
		hatom_setdouble(&ll->l_tail->l_prev->l_hatom, alpha);

        hatom_setdouble(&ll->l_tail->l_prev->l_prev->l_hatom.h_w.w_llll->l_tail->l_hatom, hatom_getdouble(&ll->l_tail->l_prev->l_prev->l_hatom.h_w.w_llll->l_tail->l_hatom) - -0.01);

        t_atom a[2];
		atom_setobj(a, elem);
		atom_setfloat(a+1, alpha - DADA_PLATFORM_NUMBERS_FADE_STEP_ALPHA);
		schedule_delay((t_object *)x, (method)fade_hatom, DADA_PLATFORM_NUMBERS_FADE_STEP_TIME, NULL, 2, a);
	}
		
	jbox_redraw((t_jbox *)x);
}

void display_number_temp(t_platform *x, long number, t_pt pos, char are_numbers_vp)
{
	t_llll *this_ll = llll_get();
	llll_appendlong(this_ll, number);
	llll_appendllll(this_ll, pt_to_llll(pos, false));
	llll_appendlong(this_ll, 100);
    llll_appendlong(this_ll, are_numbers_vp);
	t_llllelem *appended = llll_appendllll(x->floattext_to_be_displayed, this_ll, 0, WHITENULL_llll);
	
	t_atom a[2];
	atom_setobj(a, appended);
	atom_setfloat(a+1, 1.);
	schedule_delay((t_object *)x, (method)fade_hatom, DADA_PLATFORM_NUMBERS_HOLD_TIME, NULL, 2, a);
}




void platform_paint_floattext(t_platform *x, t_jgraphics *g, t_jfont *jf, t_jrgba textcolor, t_rect rect, t_pt center, double zoom){
	t_llllelem *elem;
	for (elem = x->floattext_to_be_displayed->l_head; elem; elem = elem->l_next) {
		t_llll *ll = hatom_getllll(&elem->l_hatom);
		t_pt pt = coord_to_pix(dadaobj_cast(x), center, llll_to_pt(hatom_getllll(&ll->l_head->l_next->l_hatom)));
		double alpha = hatom_getdouble(&ll->l_tail->l_prev->l_hatom);
        char is_vp = hatom_getlong(&ll->l_tail->l_hatom);
		if (hatom_gettype(&ll->l_head->l_hatom) == H_LONG) {
			char buf[100];
            double w, h;
            snprintf_zero(buf, 100, "%ld%s", hatom_getlong(&ll->l_head->l_hatom), is_vp ? "VP" : "");
            jfont_text_measure(jf, buf, &w, &h);
			write_text_simple(g, jf, change_alpha(textcolor, alpha), buf, pt.x  - w/2, pt.y - h/2., 1000, 1000);
		}
	}
}

void platform_paint_curtain(t_platform *x, t_jgraphics *g, t_jfont *jf, t_rect rect, t_pt center, double zoom)
{
    switch (x->play_state) {
        case DADA_PLATFORM_PLAYSTATE_LEVELINTRO:
        case DADA_PLATFORM_PLAYSTATE_LEVELINTRO_PRE:
        case DADA_PLATFORM_PLAYSTATE_LEVELINTRO_POST:
        case DADA_PLATFORM_PLAYSTATE_END_GAMEOVER_PRE:
        case DADA_PLATFORM_PLAYSTATE_END_GAMEOVER:
        case DADA_PLATFORM_PLAYSTATE_END_WIN_PRE:
        case DADA_PLATFORM_PLAYSTATE_END_WIN:
            
            if (x->curtain < x->m_level.level_height) {
                t_pt pt = coord_to_pix(dadaobj_cast(x), center, build_pt(0, x->curtain));
                t_rect curtain_rect = build_rect(0, 0, rect.width, pt.y);
                t_jrgba rect_color = DADA_BLACK;
                paint_rect(g, &curtain_rect, &rect_color, &rect_color, 0, 0);
                
                if (x->curtain < x->m_level.level_height/2.) {
                    double w, h;
                    t_symbol *s = NULL;
                    switch (x->play_state) {
                        case DADA_PLATFORM_PLAYSTATE_LEVELINTRO:
                        case DADA_PLATFORM_PLAYSTATE_LEVELINTRO_PRE:
                        case DADA_PLATFORM_PLAYSTATE_LEVELINTRO_POST:
                            s = x->m_level.levelname && x->m_level.levelname != _llllobj_sym_none ? x->m_level.levelname : NULL;
                            break;
                        case DADA_PLATFORM_PLAYSTATE_END_GAMEOVER_PRE:
                        case DADA_PLATFORM_PLAYSTATE_END_GAMEOVER:
                            s = gensym("Game Over!");
                            break;
                        case DADA_PLATFORM_PLAYSTATE_END_WIN_PRE:
                        case DADA_PLATFORM_PLAYSTATE_END_WIN:
                            s = gensym("You Win!");
                            break;
                            
                        default:
                            break;
                    }
                    if (s) {
                        jfont_text_measure(jf, s->s_name, &w, &h);
                        write_text(g, jf, DADA_WHITE, s->s_name, 0, 0, rect.width, rect.height, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, false, false);
                    }
                }
            }
            break;
            
        default:
            break;
    }
}



t_dada_gamechar *platform_get_hero(t_platform *x)
{
    t_dada_gamechar *hero = (t_dada_gamechar *)dadaitem_get_from_ID(dadaobj_cast(x), x->hero_ID);
    return hero;
}

t_pt platform_get_hero_coords(t_platform *x)
{
    t_dada_gamechar *herochar = x->hero;
    if (herochar)
        return herochar->r_it.coord;
    return build_pt(0, 0);
}


void platform_paint_ext(t_platform *x, t_object *view, t_dada_force_graphics *force_graphics)
{
    t_dadaobj *r_ob = dadaobj_cast(x);
    t_rect rect = force_graphics->rect;
	double zoom = force_graphics->zoom.x;
	t_jgraphics *g = force_graphics->graphic_context;

    t_dada_gamechar *hero = x->hero;
	t_jfont *jf_floattext = jfont_create_debug(x->fontname->s_name, JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, x->floattext_font_size);
    t_jfont *jf_legend = jfont_create_debug(x->fontname->s_name, JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, x->legend_font_size);

    dadaobj_mutex_lock(r_ob);

    r_ob->m_paint.dont_repaint = true;

    // Checking domain!
	if (view && x->autoscroll && x->b_ob.d_ob.m_play.is_playing && hero) {
        t_pt herocoord = hero->r_it.coord;
		double domain_coord = delta_pix_to_delta_coord(dadaobj_cast(x), build_pt(rect.width, rect.height)).x;
        double new_domain_start = MAX(0, herocoord.x - domain_coord/2.);
        dadaobj_setdomain(dadaobj_cast(x), view, new_domain_start, new_domain_start + domain_coord);
        jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
	}
    
    double domain_min, domain_max, domain_diff;
    char entered = false;
    dadaobj_getdomain(r_ob, view, &domain_min, &domain_max, force_graphics);
    domain_diff = domain_max - domain_min;
    if (view && domain_min < 0) {
        dadaobj_setdomain(dadaobj_cast(x), view, 0, domain_diff);
        jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
        entered = true;
    }
    
    if (view) {
        if (domain_max > x->m_level.level_width && domain_diff < x->m_level.level_width) {
            dadaobj_setdomain(dadaobj_cast(x), view, x->m_level.level_width - domain_diff, x->m_level.level_width);
            jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
        } else if (domain_max < x->m_level.level_width && domain_diff > x->m_level.level_width && !entered){
            dadaobj_setdomain(dadaobj_cast(x), view, 0, domain_diff);
            jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
        }
    }
    
    r_ob->m_paint.dont_repaint = false;

	t_pt center = force_graphics->center_pix;
	x->displayed_coord = get_displayed_coord(x, center, rect);
	
	jgraphics_set_source_rgba(g, 0, 0, 0, 1); // alpha = 1;
    
    dadaobj_paint_background(dadaobj_cast(x), g, &rect);
    

    if (view && x->firsttime || x->play_state == DADA_PLATFORM_PLAYSTATE_STANDARD || x->play_state == DADA_PLATFORM_PLAYSTATE_DYING) {
        jbox_invalidate_layer((t_object *)x, view, gensym("game"));
        x->firsttime = false;
    }


    t_jgraphics *g_game = view ? jbox_start_layer(r_ob->orig_obj, view, gensym("game"), rect.width, rect.height) : force_graphics->graphic_context;
    if (g_game) {
        platform_paint_background(x, g_game, rect, center, zoom);
        platform_paint_coins(x, g_game, rect, center, zoom);
        platform_paint_gamechars(x, g_game, rect, center, zoom);
        platform_paint_blocks(x, g_game, rect, center, zoom);
        platform_paint_portals(x, g_game, rect, center, zoom);
        platform_paint_floattext(x, g_game, jf_floattext, x->m_level.j_textcolor, rect, center, zoom);
        if (view)
            jbox_end_layer((t_object *)x, view, gensym("game"));
    }
    if (view)
        jbox_paint_layer((t_object *)x, view, gensym("game"), 0., 0.);	// position of the layer

    platform_paint_curtain(x, g, jf_legend, rect, center, zoom);
    
    if (x->b_ob.d_ob.m_interface.mouse_is_down && x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_SELECT) {
        t_jrgba border = change_alpha(x->j_selectioncolor, 0.5);
        t_jrgba inner = change_alpha(x->j_selectioncolor, 0.1);
        dadaobj_paint_selection_rectangle(dadaobj_cast(x), g, &border, &inner);
    }
    
    if (x->play_state == DADA_PLATFORM_PLAYSTATE_STANDARD) {
        // painting legend
        char buf[1000];
        platform_get_legend(x, buf);
        if (buf[0]) {
            write_text_simple(g, jf_legend, x->m_level.j_textcolor, buf, 10, 10, rect.width - 20, rect.height - 20);
        }
        
        // painting time
        if (x->show_legend_time > 0) {
            char buf[1024];
            buf[0] = 0;
            if (x->show_legend_time == 1) {
                long num_secs = (long)x->global_time/1000.;
                snprintf_zero(buf, 1024, "%.2d:%.2d", num_secs/60, num_secs%60);
            } else {
                if (is_atom_number(&x->m_level.maxtime)) {
                    long num_secs = (long)(atom_getfloat(&x->m_level.maxtime)-x->global_time)/1000.;
                    snprintf_zero(buf, 1024, "%.2d:%.2d", num_secs/60, num_secs%60);
                }
            }
            write_text(g, jf_legend, x->m_level.j_textcolor, buf, 10, 10, rect.width - 20, rect.height - 20, JGRAPHICS_TEXT_JUSTIFICATION_TOPRIGHT, true, true);
        }
    }
		
    // paint grid if any
    dadaobj_paint_grid(dadaobj_cast(x), view, force_graphics);
    
	// paint border
    dadaobj_paint_border(dadaobj_cast(x), g, &rect);
    dadaobj_mutex_unlock(r_ob);

	jfont_destroy(jf_floattext);
    jfont_destroy(jf_legend);
}

void platform_paint(t_platform *x, t_object *view)
{
    dadaobj_paint(dadaobj_cast(x), view);
}


///////// POPUP MENU FUNCTIONS

void popup_add_block(t_object *o, t_symbol *label, const t_llll *address)
{
    t_dadaobj *r_ob = (t_dadaobj *)o;
    platform_add_single_item_from_prototype((t_platform *)r_ob->orig_obj, label, DADAITEM_TYPE_BLOCK, r_ob->m_interface.mousedown_coord, DIA_UNDO_POSTPROCESS_INTERFACE);
}


void popup_add_coin(t_object *o, t_symbol *label, const t_llll *address)
{
    t_dadaobj *r_ob = (t_dadaobj *)o;
    platform_add_single_item_from_prototype((t_platform *)r_ob->orig_obj, label, DADAITEM_TYPE_COIN, r_ob->m_interface.mousedown_coord, DIA_UNDO_POSTPROCESS_INTERFACE);
}

void popup_add_gamechar(t_object *o, t_symbol *label, const t_llll *address)
{
    t_dadaobj *r_ob = (t_dadaobj *)o;
    platform_add_single_item_from_prototype((t_platform *)r_ob->orig_obj, label, DADAITEM_TYPE_GAMECHAR, r_ob->m_interface.mousedown_coord, DIA_UNDO_POSTPROCESS_INTERFACE);
}

void popup_add_portal(t_object *o, t_symbol *label, const t_llll *address)
{
    t_dadaobj *r_ob = (t_dadaobj *)o;
    platform_add_single_item_from_prototype((t_platform *)r_ob->orig_obj, label, DADAITEM_TYPE_PORTAL, r_ob->m_interface.mousedown_coord, DIA_UNDO_POSTPROCESS_INTERFACE);
}


void show_bg_popup_menu(t_platform *x, t_object *patcherview, t_pt pt, long modifiers)
{
    /*
    t_llll *structure = llll_get();
    t_llll *structure_block = llll_get();
    t_llll *structure_coin = llll_get();
    t_llll *structure_gamechar = llll_get();
    t_llll *structure_portal = llll_get();
    t_llll *fun = llll_get();
    t_llll *fun_block = llll_get();
    t_llll *fun_coin = llll_get();
    t_llll *fun_gamechar = llll_get();
    t_llll *fun_portal = llll_get();
    
    
    long i;
    for (i = 0; i < x->prototype_manager.num_prototypes; i++) {
        switch (x->prototype_manager.prototypes[i].type) {
            case DADAITEM_TYPE_BLOCK:
                llll_appendsym(structure_block, x->prototype_manager.prototypes[i].name);
                llll_appendobj(fun_block, (void *)popup_add_block);
                break;

            case DADAITEM_TYPE_COIN:
                llll_appendsym(structure_coin, x->prototype_manager.prototypes[i].name);
                llll_appendobj(fun_block, (void *)popup_add_coin);
                break;

            case DADAITEM_TYPE_GAMECHAR:
                llll_appendsym(structure_gamechar, x->prototype_manager.prototypes[i].name);
                llll_appendobj(fun_block, (void *)popup_add_gamechar);
                break;

            case DADAITEM_TYPE_PORTAL:
                llll_appendsym(structure_portal, x->prototype_manager.prototypes[i].name);
                llll_appendobj(fun_block, (void *)popup_add_portal);
                break;

            default:
                break;
        }
    }
    
    llll_appendllll(structure, structure_block);
    llll_appendllll(structure, structure_coin);
    llll_appendllll(structure, structure_gamechar);
    llll_appendllll(structure, structure_portal);

    llll_appendllll(fun, fun_block);
    llll_appendllll(fun, fun_coin);
    llll_appendllll(fun, fun_gamechar);
    llll_appendllll(fun, fun_portal);

    display_popup_menu(dadaobj_cast(x), patcherview, structure, fun, llll_get(), llll_get(), llll_get(), llll_get(), 0);
*/

    t_llll *structure = llll_get();
    t_llll *structure_block = llll_get();
    t_llll *structure_coin = llll_get();
    t_llll *structure_gamechar = llll_get();
    t_llll *structure_portal = llll_get();
    
    llll_appendsym(structure_block, gensym("Add Block"));
    llll_appendsym(structure_coin, gensym("Add Coin"));
    llll_appendsym(structure_gamechar, gensym("Add Game Character"));
    llll_appendsym(structure_portal, gensym("Add Portal"));
    
    long i;
    for (i = 0; i < x->prototype_manager.num_prototypes; i++) {
        switch (x->prototype_manager.prototypes[i].type) {
            case DADAITEM_TYPE_BLOCK:
                llll_appendsym(structure_block, x->prototype_manager.prototypes[i].name);
                break;
                
            case DADAITEM_TYPE_COIN:
                llll_appendsym(structure_coin, x->prototype_manager.prototypes[i].name);
                break;
                
            case DADAITEM_TYPE_GAMECHAR:
                llll_appendsym(structure_gamechar, x->prototype_manager.prototypes[i].name);
                break;
                
            case DADAITEM_TYPE_PORTAL:
                llll_appendsym(structure_portal, x->prototype_manager.prototypes[i].name);
                break;
                
            default:
                break;
        }
    }
    
    llll_appendllll(structure, structure_block);
    llll_appendllll(structure, structure_coin);
    llll_appendllll(structure, structure_gamechar);
    llll_appendllll(structure, structure_portal);

    char *buf = NULL;
    llll_to_text_buf(structure, &buf, 0, BACH_DEFAULT_MAXDECIMALS, LLLL_T_NONE, LLLL_TE_SMART, LLLL_TB_SMART, NULL);
    
    ezdisplay_popup_menu(dadaobj_cast(x), patcherview,
                         buf, "0 0 0 0", "", "", "", "",
                         (void *)popup_add_block, (void *)popup_add_coin, (void *)popup_add_gamechar, (void *)popup_add_portal, WHITENULL);
    
    bach_freeptr(buf);
}




////////// INTERFACE FUNCTIONS

void platform_focusgained(t_platform *x, t_object *patcherview) {
	if (dadaobj_focusgained(dadaobj_cast(x), patcherview))
		return;
}

void platform_focuslost(t_platform *x, t_object *patcherview) {
	if (dadaobj_focuslost(dadaobj_cast(x), patcherview))
		return;
}

void platform_mousemove(t_platform *x, t_object *patcherview, t_pt pt, long modifiers) {

    if (x->play_state != DADA_PLATFORM_PLAYSTATE_STANDARD && x->play_state != DADA_PLATFORM_PLAYSTATE_DYING) {
        return;
    }
    
	llll_format_modifiers(&modifiers, NULL);
	
	if (dadaobj_mousemove(dadaobj_cast(x), patcherview, pt, modifiers))
		return;

	if (popup_menu_is_shown(dadaobj_cast(x))) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
	} else if (x->b_ob.d_ob.m_interface.mousedown_item || x->b_ob.d_ob.m_interface.mousemove_item) {
		if (modifiers == eAltKey)
			dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DUPLICATE);
		else if (modifiers == eCommandKey)
			dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DELETE);
		else
			dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_RESIZE_FOURWAY);
	} else if (x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_SELECT) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_CROSSHAIR);
	} else  {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
	} 
}



t_dadaitem *platform_pixel_to_dadaitem(t_dadaobj *r_ob, t_pt pt, t_object *view, long modifiers, t_pt *coordinates, double selection_pad, t_dadaitem_identifier *identifier)
{
    t_dadaitem *res = pixel_to_dadaitem(r_ob, pt, view, modifiers, coordinates, selection_pad, identifier);
#ifdef DADA_PLATFORM_LEVEL_HAS_INSPECTOR
    if (!res) {
        t_platform *x = (t_platform *)r_ob->orig_obj;
        res = &(x->m_level.r_it);
        identifier->idx = 1;
        identifier->type = DADAITEM_TYPE_LEVEL;
    }
#endif
    return res;
}

char platform_can_edit(t_platform *x)
{
    if (x->edit_mode == 0)
        return false;
    if (x->edit_mode && x->b_ob.d_ob.m_play.is_playing)
        return false;
    
    return true;
}

void platform_mousedown(t_platform *x, t_object *patcherview, t_pt pt, long modifiers)
{

    if (!platform_can_edit(x) || (x->play_state != DADA_PLATFORM_PLAYSTATE_STANDARD && x->play_state != DADA_PLATFORM_PLAYSTATE_DYING)) {
        jbox_redraw((t_jbox *)x);
        return;
    }
    
	if (dadaobj_mousedown(dadaobj_cast(x), patcherview, pt, modifiers))
		return;

	if (modifiers & ePopupMenu) {
		if (!x->b_ob.d_ob.m_interface.mousedown_item || x->b_ob.d_ob.m_interface.mousedown_item->type == DADAITEM_TYPE_LEVEL)
            show_bg_popup_menu(x, patcherview, pt, modifiers);

    } else {
		llll_format_modifiers(&modifiers, NULL);
        if (modifiers & eCommandKey)  {
            if (x->b_ob.d_ob.m_interface.mousedown_item)
            dadaitem_delete_direct(dadaobj_cast(x), x->b_ob.d_ob.m_interface.mousedown_item, DIA_UNDO_TICK | DIA_POSTPROCESS | DIA_INTERFACE);
//            dadaobj_selection_delete(dadaobj_cast(x), DIA_UNDO_TICK | DIA_POSTPROCESS | DIA_INTERFACE);
//            dadaobj_add_undo_marker_if_needed(dadaobj_cast(x));
            undo_redo_post_debug(dadaobj_cast(x));

        }
	}
	
	jbox_redraw((t_jbox *)x);
	
}

char platform_snap_selection_to_grid_fn(t_dadaobj *r_ob, t_dadaitem *item, void *data)
{
    t_pt grid_size = dadaobj_get_grid_size(r_ob);
	dadaitem_move(r_ob, item, build_pt(round(item->coord.x / grid_size.x) * grid_size.x, round(item->coord.y / grid_size.y) * grid_size.y), DIA_INTERFACE + DIA_UNDO);
	return 0;
}


void platform_snap_selection_to_grid(t_platform *x)
{
	dadaobj_selection_iterate(dadaobj_cast(x), platform_snap_selection_to_grid_fn, NULL);
}


void platform_mouseup(t_platform *x, t_object *patcherview, t_pt pt, long modifiers)
{
    
    if (!platform_can_edit(x)) {
        jbox_redraw((t_jbox *)x);
        return;
    }
    
    char dirty = undo_are_there_free_undo_ticks(&x->b_ob.d_ob.m_undo);
	char block_dirty = dadaitem_class_get_dirty(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_BLOCK);
    char coin_dirty = dadaitem_class_get_dirty(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_COIN);
    char portals_dirty = dadaitem_class_get_dirty(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_PORTAL);
	llll_format_modifiers(&modifiers, NULL);
	
    x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag &= ~DADAITEM_IDENTIFIER_FLAG_DUPLICATED;
    
    if (x->b_ob.d_ob.m_grid.snap_to_grid && x->b_ob.d_ob.m_interface.has_been_modified_while_mousedown) {
		platform_snap_selection_to_grid(x);
		if (block_dirty)
			platform_sort_blocks(x);
		if (coin_dirty)
			platform_sort_coins(x);
        if (portals_dirty)
            platform_sort_portals(x);
		jbox_redraw((t_jbox *)x);
	}

    if (dadaobj_mouseup(dadaobj_cast(x), patcherview, pt, modifiers))
        return;
    

/*	x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADA_NODES_ELEMENT_NONE;
	x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag = 0;

	if (x->b_ob.d_ob.m_cursors.curr_cursor == BACH_CURSOR_NONE) { 
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
		platform_mousemove(x, patcherview, pt, modifiers);
	}
  */
}


void platform_mousedrag(t_platform *x, t_object *patcherview, t_pt pt, long modifiers){
	
    
    if (!platform_can_edit(x)) {
        jbox_redraw((t_jbox *)x);
        return;
    }

	llll_format_modifiers(&modifiers, NULL);
	
	if (dadaobj_mousedrag(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
	
	if (x->b_ob.d_ob.m_interface.mousedown_item && !dadaitem_is_in_background(dadaobj_cast(x), x->b_ob.d_ob.m_interface.mousedown_item)) {
        if ((modifiers & eAltKey) && !(x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag & DADAITEM_IDENTIFIER_FLAG_DUPLICATED)){
            // duplicate selection
            dadaobj_selection_duplicate(dadaobj_cast(x), DIA_UNDO_POSTPROCESS_INTERFACE);
            x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag |= DADAITEM_IDENTIFIER_FLAG_DUPLICATED;
        }
        
        dadaobj_selection_move_delta(dadaobj_cast(x), x->b_ob.d_ob.m_interface.mousedrag_delta_coord, DIA_UNDO_POSTPROCESS_INTERFACE);
        if (dadaobj_selection_contains_type(dadaobj_cast(x), DADAITEM_TYPE_BLOCK)) // extremely important, or the characters might fall down!
            platform_sort_blocks(x);
        if (dadaobj_selection_contains_type(dadaobj_cast(x), DADAITEM_TYPE_COIN)) // although this is less important: we might even just do that at mouseup
            platform_sort_coins(x);
        if (dadaobj_selection_contains_type(dadaobj_cast(x), DADAITEM_TYPE_PORTAL))
            platform_sort_portals(x);
		jbox_redraw((t_jbox *)x);
	}
}



void platform_mousewheel(t_platform *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc)
{

    if (!platform_can_edit(x)) {
        jbox_redraw((t_jbox *)x);
        return;
    }

    llll_format_modifiers(&modifiers, NULL);

	if (dadaobj_mousewheel(dadaobj_cast(x), view, pt, modifiers, x_inc, y_inc)) {
        jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
		jbox_redraw((t_jbox *)x);
		return;
	} 
}



long platform_keyup(t_platform *x, t_object *patcherview, long keycode, long modifiers, long textcharacter){
			
	llll_format_modifiers(&modifiers, &keycode);

	if (dadaobj_keyup(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
		return 1;
	

	if (x->b_ob.d_ob.m_play.is_playing) {
		switch (keycode) {
			case JKEY_LEFTARROW:
			case JKEY_RIGHTARROW:
            {
                t_dada_gamechar *hero = x->hero;
                if (hero)
                    hero->forced_hdirection = 0;
				jbox_redraw((t_jbox *)x);
				return 1;
            }
		}
	}
	
	return 0;
}

void platform_gamechar_hshift(t_platform *x, t_dada_gamechar *gamechar, double amount, long direction)
{
	if (gamechar->abilities & DADA_GAMECHAR_ABILITY_WALK || x->m_level.gravity == 0.) {
        if (x->notify_usercontrol_actions)
            send_notification_for_usercontrol(x, (t_dadaitem *)gamechar, gensym("moves"), direction < 0 ? gensym("left") : gensym("right"));

        if (!x->break_after_notification) {
            gamechar->speed.x = (direction < 0 ? -amount : amount);
            gamechar->direction = (direction < 0 ? -1 : 1);
            gamechar->forced_hdirection = (direction < 0 ? -1 : 1);
            if (gamechar->state == DADA_GAMECHAR_STATE_IDLE && x->m_level.gravity > 0.)
                gamechar->state = DADA_GAMECHAR_STATE_WALKING;
            jbox_redraw((t_jbox *)x);
        }
	}
}

void platform_gamechar_vshift(t_platform *x, t_dada_gamechar *gamechar, double amount, long direction)
{
    if (gamechar->abilities & DADA_GAMECHAR_ABILITY_FLY || x->m_level.gravity == 0.) {
        if (x->notify_usercontrol_actions)
            send_notification_for_usercontrol(x, (t_dadaitem *)gamechar, gensym("moves"), direction < 0 ? gensym("down") : gensym("up"));
        
        if (!x->break_after_notification) {
            gamechar->speed.y = (direction < 0 ? -amount : amount);
            gamechar->on_ground = false;
/*            gamechar->direction = (direction < 0 ? -1 : 1);
            gamechar->forced_vdirection = (direction < 0 ? -1 : 1); */
            if (gamechar->state == DADA_GAMECHAR_STATE_IDLE)
                gamechar->state = DADA_GAMECHAR_STATE_FLYING;
            jbox_redraw((t_jbox *)x);
        }
    }
}

void platform_gamechar_jump(t_platform *x, t_dada_gamechar *gamechar, double amount)
{
	if (gamechar->abilities & DADA_GAMECHAR_ABILITY_JUMP) {
		if (gamechar->on_ground || (gamechar->abilities & DADA_GAMECHAR_ABILITY_FLY)) {
            if (x->notify_usercontrol_actions)
                send_notification_for_usercontrol(x, (t_dadaitem *)gamechar, gensym("jumps"), NULL);

            gamechar->speed.y = amount;
			gamechar->on_ground = false;
			if (gamechar->abilities & DADA_GAMECHAR_ABILITY_FLY)
				gamechar->state = DADA_GAMECHAR_STATE_FLYING;
			else
				gamechar->state = DADA_GAMECHAR_STATE_JUMPING;
		} 
	}
}

void platform_gamechar_shoot(t_platform *x, t_dada_gamechar *gamechar)
{
    if (gamechar->abilities & DADA_GAMECHAR_ABILITY_SHOOT && gamechar->bullet_gamechar) {
        if (x->notify_usercontrol_actions)
            send_notification_for_usercontrol(x, (t_dadaitem *)gamechar, gensym("shoots"), NULL);
        
        char buf[2000];
        snprintf(buf, 2000, "(generate %s from me)", gamechar->bullet_gamechar->s_name);
        parse_instructions_char(x, buf, (t_dadaitem *)gamechar);
    }
}

long platform_key(t_platform *x, t_object *patcherview, long keycode, long modifiers, long textcharacter)
{
	llll_format_modifiers(&modifiers, &keycode);

    
    if (platform_can_edit(x) && keycode == 115 && modifiers == eCommandKey) {
        // special case: Cmd+S. User of course wants to save the patch, but probably wants also to fix the object (if the object has focus, which
        // is the case, since this method has been called)
        x->fixed_state = platform_get_state(x);
        return 0; // we pass it through
    }
    
	if (platform_can_edit(x) && dadaobj_key(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
		return 1;

	// handle user keys
    t_dada_gamechar *hero = x->hero;
	if (x->b_ob.d_ob.m_play.is_playing && hero && hero->state != DADA_GAMECHAR_STATE_DEAD && hero->state != DADA_GAMECHAR_STATE_DYING) {
		switch (keycode) {
			case JKEY_LEFTARROW:
			case JKEY_RIGHTARROW:
				platform_gamechar_hshift(x, hero, modifiers == eShiftKey ? 6 : 3, keycode == JKEY_LEFTARROW ? -1 : 1);
				return 1;
            case JKEY_UPARROW:
			case JKEY_DOWNARROW:
                if (x->m_level.gravity == 0.)
                    platform_gamechar_vshift(x, hero, modifiers == eShiftKey ? 6 : 3, keycode == JKEY_DOWNARROW ? -1 : 1);
                else if (keycode == JKEY_UPARROW)
                    platform_gamechar_jump(x, hero, 9 + 0.5 * fabs(hero->speed.x));
                return 1;
            case JKEY_TAB: // firing
                platform_gamechar_shoot(x, hero);
                return 1;
		}
	}
	
	switch (keycode) {
		case JKEY_SPACEBAR:	// play/stop
            if (x->b_ob.d_ob.m_play.is_playing) {
                    platform_stop_do(x);
            } else {
                    platform_resume_do(x);
            }
			return 1;
            break;
        case JKEY_BACKSPACE:
            if (platform_can_edit(x)) {
                dadaobj_selection_delete(dadaobj_cast(x), DIA_UNDO_TICK | DIA_POSTPROCESS | DIA_INTERFACE);
                dadaobj_add_undo_marker_if_needed(dadaobj_cast(x));
                undo_redo_post_debug(dadaobj_cast(x));
                jbox_redraw((t_jbox *)x);
                return 1;
            }
            break;
		case JKEY_ESC:
            if (platform_can_edit(x)) {
                t_object *view = jpatcher_get_firstview((t_object *)gensym("#P")->s_thing);
                dadaobj_setrange(dadaobj_cast(x), view, 0, x->m_level.level_height);
                dadaobj_setdomain_start(dadaobj_cast(x), view, 0);
                x->play_state = DADA_PLATFORM_PLAYSTATE_STANDARD;
                jbox_redraw((t_jbox *)x);
            }
            return 1;
            break;
		default:
			break;
	}

	return 0;
}


void platform_mouseenter(t_platform *x, t_object *patcherview, t_pt pt, long modifiers) 
{
	if (dadaobj_mouseenter(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
}

void platform_mouseleave(t_platform *x, t_object *patcherview, t_pt pt, long modifiers) 
{
	if (dadaobj_mouseleave(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
}

/// POSTPROCESS

void postprocess_blocks(t_platform *x)
{
	jbox_redraw((t_jbox *)x);
}


void postprocess_coins(t_platform *x)
{
	jbox_redraw((t_jbox *)x);
}



void postprocess_gamechars(t_platform *x)
{
	jbox_redraw((t_jbox *)x);
}


////// UNDO HANDLING


void platform_undo_postprocess(t_platform *x)
{
    
    jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
	jbox_redraw((t_jbox *)x);
}


void platform_undo_postprocess_levelheight(t_bach_inspector_manager *man, void *elem, void *attr)
{
    t_platform *x = (t_platform *)man->owner;
    platform_check_autozoom(x);
    platform_iar(x);
}




/////////////// SEQUENCING SYSTEM

void platform_clock(t_platform *x, t_symbol *s) 
{
	void *old = x->b_ob.d_ob.m_play.setclock->s_thing; 
	t_object *c = 0; 
	
	// the line below can be restated as: 
	// if s is the empty symbol 
	// or s->s_thing is zero 
	// or s->s_thing is non-zero and a setclock object  
	if (s && (s == gensym("") || ((c = (t_object *) s->s_thing) && zgetfn(c, gensym("unset"))))) { 
		if (old) 
            platform_stop(x, NULL, 0, NULL); 
		x->b_ob.d_ob.m_play.setclock = s; 
	} 
}


long sort_by_x_coord(void *data, t_llllelem *a, t_llllelem *b)
{
    t_pt coord_a = ((t_dada_block *)hatom_getobj(&a->l_hatom))->r_it.coord;
    t_pt coord_b = ((t_dada_block *)hatom_getobj(&b->l_hatom))->r_it.coord;
    
    if (coord_a.x <= coord_b.x)
        return 1;
    else
        return 0;
}

void platform_sort_portals(t_platform *x)
{
    llll_inplacesort(x->portals, (sort_fn) sort_by_x_coord);
    dadaobj_selection_force_rebuild_llll(dadaobj_cast(x));
    dadaobj_preselection_force_rebuild_llll(dadaobj_cast(x));
}

void platform_sort_blocks(t_platform *x)
{
    llll_inplacesort(x->blocks, (sort_fn) sort_by_x_coord);
	dadaobj_selection_force_rebuild_llll(dadaobj_cast(x));
	dadaobj_preselection_force_rebuild_llll(dadaobj_cast(x));
}

void platform_sort_coins(t_platform *x)
{
    llll_inplacesort(x->coins, (sort_fn) sort_by_x_coord);
	dadaobj_selection_force_rebuild_llll(dadaobj_cast(x));
	dadaobj_preselection_force_rebuild_llll(dadaobj_cast(x));
}


void platform_resume_do(t_platform *x) 
{
    if (x->play_mode != DADA_PLATFORM_PLAYMODE_CANT_PLAY) {
        send_notification_symbol(x, _llllobj_sym_play);
        if (x->b_ob.d_ob.m_undo.undo_before_play)
            platform_undo_step_push(x, gensym("Play"));
        x->b_ob.d_ob.m_play.is_playing = true;
        setclock_fdelay(x->b_ob.d_ob.m_play.setclock->s_thing, x->b_ob.d_ob.m_play.m_clock, x->b_ob.d_ob.m_play.play_step_ms);
        jbox_redraw((t_jbox *)x);
    }
}

void platform_play_do(t_platform *x, long start_hero_vp)
{
    t_dada_gamechar *hero = x->hero;
	if (hero)
		hero->vp = start_hero_vp;

	platform_sort_blocks(x);
	platform_sort_coins(x);
    platform_sort_portals(x);
//	platform_check_all_block_collisions(x);
	
    x->global_time = 0;
	platform_resume_do(x);
}

void platform_play(t_platform *x, t_symbol *s, long argc, t_atom *argv)
{
    long start_hero_vp = argc && argv ? atom_getlong(argv) : (x->hero ? x->hero->vp : 0);
	platform_play_do(x, start_hero_vp);
}

void platform_resume(t_platform *x, t_symbol *s, long argc, t_atom *argv)
{
	platform_resume_do(x);
}


void platform_stop_do(t_platform *x)
{
    if (x->play_mode != DADA_PLATFORM_PLAYMODE_CANT_STOP) {
        send_notification_symbol(x, _llllobj_sym_stop);
        setclock_unset(x->b_ob.d_ob.m_play.setclock->s_thing, x->b_ob.d_ob.m_play.m_clock);
        x->b_ob.d_ob.m_play.is_playing = false;
        jbox_redraw((t_jbox *)x);
    }
}

void platform_stop(t_platform *x, t_symbol *s, long argc, t_atom *argv)
{
	platform_stop_do(x);
}



void platform_bang(t_platform *x)
{
	x->global_time += x->b_ob.d_ob.m_play.play_step_ms;
	jbox_redraw((t_jbox *)x);
}

long baricentric_rect_rect_relative_position(t_rect *test_rect, t_rect *reference_rect)
{
    double const PIOVERSIX = PIOVERTWO/3.;
    double angle = atan2(test_rect->y - reference_rect->y, test_rect->x - reference_rect->x);
    if (angle < 0) angle += TWOPI;
    if (angle < PIOVERSIX)
        return DADA_GAMECHAR_VIA_SIDE_RIGHT;
    else if (angle < 5 * PIOVERSIX)
        return DADA_GAMECHAR_VIA_SIDE_TOP;
    else if (angle < 7 * PIOVERSIX)
        return DADA_GAMECHAR_VIA_SIDE_LEFT;
    else if (angle < 11 * PIOVERSIX)
        return DADA_GAMECHAR_VIA_SIDE_BOTTOM;
    else
        return DADA_GAMECHAR_VIA_SIDE_RIGHT;
}

char gamechar_can_only_jump(t_dada_gamechar *gamechar)
{
    if (!(gamechar->abilities & (DADA_GAMECHAR_ABILITY_WALK | DADA_GAMECHAR_ABILITY_FLY | DADA_GAMECHAR_ABILITY_RUN | DADA_GAMECHAR_ABILITY_GLIDE)) && gamechar->abilities & DADA_GAMECHAR_ABILITY_JUMP)
        return 1;
    else
        return 0;
}

// returns 1 if gamechar dies
char platform_gamechar_handle_obstacle(t_platform *x, t_dada_gamechar *gamechar, long direction, t_dadaitem *obstacle)
{
    t_pt obstacle_coord = obstacle->coord;
    double obstacle_width = obstacle->width;
    double obstacle_height = obstacle->height;
    e_dadaitem_types obstacle_type = obstacle->type;
    double threshold_speed_y = x->m_level.gravity * x->b_ob.d_ob.m_play.play_step_ms / 1000. + 0.001;
    double threshold_speed_x = 0.001;
    
    if (gamechar->how_dies & DADA_GAMECHAR_VIA_TOUCH_GROUND) {
        platform_gamechar_die(x, gamechar, NULL);
        return 1;
    }
    
	switch (direction) {
		case DADA_GAMECHAR_VIA_SIDE_TOP: // TOP
			gamechar->r_it.coord.y = obstacle_coord.y + (obstacle_height / 2. + gamechar->r_it.height / 2.);
            if (gamechar_can_only_jump(gamechar)) {
                gamechar->speed.y = MAX(-gamechar->speed.y, DADA_PLATFORM_GAMECHAR_JUMP_DEFAULT);
                gamechar->state = DADA_GAMECHAR_STATE_JUMPING;
            } else {
                if (obstacle_type == DADAITEM_TYPE_PORTAL) {
                    gamechar->on_ground = true;
                } else if (obstacle_type == DADAITEM_TYPE_BLOCK) {
                    t_dada_block *block = (t_dada_block *)obstacle;
                    gamechar->on_ground = true;
                    if (block->how_bumpeable & DADA_GAMECHAR_VIA_SIDE_TOP && gamechar->speed.y < -threshold_speed_y)
                        platform_hit_block(x, gamechar, block, DADA_GAMECHAR_VIA_SIDE_TOP);
                    else
                        gamechar->speed.y = 0;
                } else
                    gamechar->speed.y = 0;
                gamechar->r_it.coord.y = MAX(gamechar->r_it.coord.y, obstacle->coord.y + obstacle->height/2. + gamechar->r_it.height/2.);
                gamechar->state &= ~DADA_GAMECHAR_STATE_JUMPING;
            }
			break;
		case DADA_GAMECHAR_VIA_SIDE_BOTTOM:
			gamechar->r_it.coord.y = obstacle_coord.y - (obstacle_height / 2. + gamechar->r_it.height / 2.);
            if (obstacle_type == DADAITEM_TYPE_BLOCK) {
                t_dada_block *block = (t_dada_block *)obstacle;
                if (block->how_bumpeable & DADA_GAMECHAR_VIA_SIDE_BOTTOM && fabs(gamechar->speed.y) > threshold_speed_y)
                    platform_hit_block(x, gamechar, block, DADA_GAMECHAR_VIA_SIDE_BOTTOM);
            }
            gamechar->speed.y = 0;
			break;
		case DADA_GAMECHAR_VIA_SIDE_LEFT: 
			gamechar->r_it.coord.x = obstacle_coord.x - (obstacle_width / 2. + gamechar->r_it.width / 2.);
			if (gamechar->type == DADA_GAMECHAR_TYPE_USERCONTROL)
				gamechar->speed.x = 0;
			else {
				gamechar->speed.x *= -1;
				gamechar->direction *= -1;
			}
            if (obstacle_type == DADAITEM_TYPE_BLOCK) {
                t_dada_block *block = (t_dada_block *)obstacle;
                if ((block->how_bumpeable & DADA_GAMECHAR_VIA_SIDE_LEFT && fabs(gamechar->speed.x) > threshold_speed_x) ||
                    (block->how_bumpeable & DADA_GAMECHAR_VIA_GLIDE && gamechar->state & DADA_GAMECHAR_STATE_GLIDING))
                    platform_hit_block(x, gamechar, block, DADA_GAMECHAR_VIA_SIDE_LEFT);
            }

			break;
		case DADA_GAMECHAR_VIA_SIDE_RIGHT:
			gamechar->r_it.coord.x = obstacle_coord.x + (obstacle_width / 2. + gamechar->r_it.width / 2.);
			if (gamechar->type == DADA_GAMECHAR_TYPE_USERCONTROL)
				gamechar->speed.x = 0;
			else {
				gamechar->speed.x *= -1;
				gamechar->direction *= -1;
			}
            if (obstacle_type == DADAITEM_TYPE_BLOCK) {
                t_dada_block *block = (t_dada_block *)obstacle;
                if ((block->how_bumpeable & DADA_GAMECHAR_VIA_SIDE_RIGHT && fabs(gamechar->speed.x) > threshold_speed_x) ||
                    (block->how_bumpeable & DADA_GAMECHAR_VIA_GLIDE && gamechar->state & DADA_GAMECHAR_STATE_GLIDING))
                    platform_hit_block(x, gamechar, block, DADA_GAMECHAR_VIA_SIDE_RIGHT);
            }
			break;
		default:
			break;
	}
    
    return 0;
}

long sort_by_x_dist(void *data, t_llllelem *a, t_llllelem *b)
{
    t_pt coord_a = ((t_dada_block *)hatom_getobj(&a->l_hatom))->r_it.coord;
    t_pt coord_b = ((t_dada_block *)hatom_getobj(&b->l_hatom))->r_it.coord;
    t_pt coord_ref = *(t_pt *)data;
    
    if (fabs(coord_a.x - coord_ref.x) <= fabs(coord_b.x - coord_ref.x) )
        return 1;
    else
        return 0;
}

t_rect platform_center_and_ext_to_boundingbox(t_platform *x, t_pt center, double *ext)
{
    double left = center.x - ext[0];
    double right = center.x + ext[1];
    double top = center.y + ext[2];
    double bottom = center.y - ext[3];
    return build_rect(left, bottom, right-left, top-bottom);
}

t_rect platform_center_and_ext_to_rect_baricentric(t_platform *x, t_pt center, double *ext)
{
    double left = center.x - ext[0];
    double right = center.x + ext[1];
    double top = center.y + ext[2];
    double bottom = center.y - ext[3];
    return build_rect((right+left)/2., (top+bottom)/2., right-left, top-bottom);
}

void platform_check_block_collisions(t_platform *x, t_dada_gamechar *gamechar, t_pt old_gamechar_coord)
{	
	// need to set .on_ground field
    t_rect r1_old_baric = platform_center_and_ext_to_rect_baricentric(x, old_gamechar_coord, gamechar->physics_ext);
    t_rect r1 = gamechar_get_physics_rect_boundingbox(x, gamechar); // dadaitem_get_rect_boundingbox(&gamechar->r_it);

	double start_x_to_check = gamechar->r_it.coord.x - gamechar->r_it.width / 2.;
	double end_x_to_check = gamechar->r_it.coord.x + gamechar->r_it.width / 2.;
	
	// check collisions
    t_llllelem *blockelem;
    t_llll *blocks_to_be_checked = llll_get();
    for (blockelem = x->blocks->l_head; blockelem; blockelem = blockelem->l_next) {

        t_dada_block *block = (t_dada_block *)hatom_getobj(&blockelem->l_hatom);
		
		if (block->state != DADA_BLOCK_IDLE)
			continue;

        if (!block->solid)
            continue;

		if (block->r_it.coord.x + block->r_it.width / 2. < start_x_to_check)
			continue;

		if (block->r_it.coord.x - block->r_it.width / 2. > end_x_to_check)
            break;
        
        llll_appendobj(blocks_to_be_checked, block);
    }

    llll_inplacesort(blocks_to_be_checked, (sort_fn)sort_by_x_dist, &old_gamechar_coord);
    
    for (blockelem = blocks_to_be_checked->l_head; blockelem; blockelem = blockelem->l_next) {
        t_dada_block *block = (t_dada_block *)hatom_getobj(&blockelem->l_hatom);
        
		t_rect r2_baric = build_rect(block->r_it.coord.x, block->r_it.coord.y, block->r_it.width, block->r_it.height);
		t_rect r2 = rect_baricentric_to_boundingbox(r2_baric);
		
		if (jgraphics_rectintersectsrect(&r1, &r2)) {
            long pos = baricentric_rect_rect_relative_position(&r1_old_baric, &r2_baric);
			if (platform_gamechar_handle_obstacle(x, gamechar, pos, (t_dadaitem *)block))
                break;
            r1 = gamechar_get_physics_rect_boundingbox(x, gamechar); // dadaitem_get_rect_boundingbox(&gamechar->r_it);
 		}
	}
	
    llll_free(blocks_to_be_checked);
}

char platform_do_dadaitems_intersect(t_platform *x, t_dadaitem *d1, t_dadaitem *d2)
{
    t_rect r1_baric = build_rect(d1->coord.x, d1->coord.y, d1->width, d1->height);
    t_rect r1 = rect_baricentric_to_boundingbox(r1_baric);
    t_rect r2_baric = build_rect(d2->coord.x, d2->coord.y, d2->width, d2->height);
    t_rect r2 = rect_baricentric_to_boundingbox(r2_baric);
    
    if (jgraphics_rectintersectsrect(&r1, &r2)) {
        return 1;
    }
    return 0;
}


void platform_check_all_block_collisions(t_platform *x)
{	
    for (t_llllelem *gamecharelem = x->gamechars->l_head; gamecharelem; gamecharelem = gamecharelem->l_next) {
        t_dada_gamechar *gamechar = (t_dada_gamechar *)hatom_getobj(&gamecharelem->l_hatom);
		platform_check_block_collisions(x, gamechar, gamechar->r_it.coord);
    }
}




void platform_break_block(t_platform *x, t_dada_gamechar *gamechar, t_dada_block *block)
{
    if (gamechar->abilities & DADA_GAMECHAR_ABILITY_BREAK) {
        // notification
        if (x->notify_blocks)
            send_notification_for_action(x, (t_dadaitem *)gamechar, gensym("breaks"), (t_dadaitem *)block, NULL);
        
        if (!x->break_after_notification) {
            gamechar->points += block->points;
            
            block->broken_slice_delta_coord = build_pt(0.1, 0.1);
            block->broken_slice_speed = build_pt(2, 2);
            block->state = DADA_BLOCK_BREAKING;
            llll_appendobj(x->breakingblocks, block);
            
            
            // play music?
        }
    }
}


// direction is one of the e_dada_gamechar_via
void platform_portal_enter(t_platform *x, t_dada_gamechar *gamechar, t_dada_portal *portal, long direction)
{
    if (x->notify_blocks)
        send_notification_for_action(x, (t_dadaitem *)gamechar, gensym("enters"), (t_dadaitem *)portal, NULL);
    
    if (!x->break_after_notification) {
        gamechar->state = DADA_GAMECHAR_STATE_ENTERINGPORTAL;
        gamechar->portal = portal;
        gamechar->speed = build_pt(0, 0);
        gamechar->generation_or_portal_direction = direction;
        play_music(x, portal->music);
    }
}

// direction is one of the e_dada_gamechar_via
void platform_portal_exit(t_platform *x, t_dada_gamechar *gamechar, t_dada_portal *portal)
{
    if (!portal)
        return;
    
    if (x->notify_blocks)
        send_notification_for_action(x, (t_dadaitem *)gamechar, gensym("exits"), (t_dadaitem *)portal, NULL);
    
    if (!x->break_after_notification) {
        gamechar->r_it.coord = portal->r_it.coord;
        gamechar->speed = build_pt(0, 0);
        gamechar->state = DADA_GAMECHAR_STATE_EXITINGPORTAL;
        gamechar->portal = portal;
        play_music(x, portal->music);
    }
}

char platform_check_portal_collisions(t_platform *x, t_dada_gamechar *gamechar, t_pt old_gamechar_coord)
{
    // need to set .on_ground field
    char res = false;
    t_rect r1_old_baric = platform_center_and_ext_to_rect_baricentric(x, old_gamechar_coord, gamechar->physics_ext);
    t_rect r1 = gamechar_get_physics_rect_boundingbox(x, gamechar); // dadaitem_get_rect_boundingbox(&gamechar->r_it);
    
    double start_x_to_check = gamechar->r_it.coord.x - gamechar->r_it.width / 2.;
    double end_x_to_check = gamechar->r_it.coord.x + gamechar->r_it.width / 2.;
    double threshold_speed_gravity = x->m_level.gravity * x->b_ob.d_ob.m_play.play_step_ms / 1000. + 0.001;
    double threshold_speed_nogravity = 0.001;

    // check collisions
    t_llllelem *portalelem;
    t_llll *portals_to_be_checked = llll_get();
    for (portalelem = x->portals->l_head; portalelem; portalelem = portalelem->l_next) {
        
        t_dada_portal *portal = (t_dada_portal *)hatom_getobj(&portalelem->l_hatom);
        
        if (portal->r_it.coord.x + portal->r_it.width / 2. < start_x_to_check)
            continue;
        
        if (portal->r_it.coord.x - portal->r_it.width / 2. > end_x_to_check)
            break;
        
        llll_appendobj(portals_to_be_checked, portal);
    }
    
    llll_inplacesort(portals_to_be_checked, (sort_fn)sort_by_x_dist, &old_gamechar_coord);
    
    for (portalelem = portals_to_be_checked->l_head; portalelem; portalelem = portalelem->l_next) {
        t_dada_portal *portal = (t_dada_portal *)hatom_getobj(&portalelem->l_hatom);
        
        t_rect r2_baric = build_rect(portal->r_it.coord.x, portal->r_it.coord.y, portal->r_it.width, portal->r_it.height);
        t_rect r2 = rect_baricentric_to_boundingbox(r2_baric);
        
        if (jgraphics_rectintersectsrect(&r1, &r2)) {
            long pos = baricentric_rect_rect_relative_position(&r1_old_baric, &r2_baric);
            if (pos & portal->how_enter && portal->open && (!portal->hero_only || gamechar == x->hero) &&
                ((pos & DADA_GAMECHAR_VIA_SIDE_LEFT_RIGHT && fabs(gamechar->speed.x) > threshold_speed_nogravity) ||
                 (pos & DADA_GAMECHAR_VIA_SIDE_TOP && gamechar->speed.y < -threshold_speed_gravity) ||
                 (pos & DADA_GAMECHAR_VIA_SIDE_BOTTOM && gamechar->speed.y > threshold_speed_nogravity))) {
                    platform_portal_enter(x, gamechar, portal, pos);
                    res = true;
                    break;
            } else if (platform_gamechar_handle_obstacle(x, gamechar, pos, (t_dadaitem *)portal))
                break;

            r1 = gamechar_get_physics_rect_boundingbox(x, gamechar); // dadaitem_get_rect_boundingbox(&gamechar->r_it);
        }
    }
    
    llll_free(portals_to_be_checked);
    return res;
}






t_symbol *prototype_to_item_name(t_platform *x, t_symbol *prototype)
{
    t_platform_prototype *proto = label_to_prototype(x, prototype);
    if (proto) {
        t_llllelem *elem;
        for (elem = proto->attr->l_head; elem; elem = elem->l_next) {
            if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
                t_llll *ll = hatom_getllll(&elem->l_hatom);
                if (ll && ll->l_head && hatom_gettype(&ll->l_head->l_hatom) == H_SYM && hatom_getsym(&ll->l_head->l_hatom) == _llllobj_sym_name) {
                    if (ll->l_head->l_next && hatom_gettype(&ll->l_head->l_next->l_hatom) == H_SYM)
                        return hatom_getsym(&ll->l_head->l_next->l_hatom);
                    else
                        return _llllobj_sym_none;
                }
            }
        }
    }
    return _llllobj_sym_none;
}

void platform_gen_gamechar(t_platform *x, t_symbol *gencharprototype, t_dadaitem *from_me, t_llll *attrs)
{
    if (true) {
        if (from_me && from_me->type == DADAITEM_TYPE_BLOCK && x->notify_blocks)
            send_notification_for_action_symobj(x, (t_dadaitem *)from_me, gensym("generates"), gensym("gamechar"), prototype_to_item_name(x, gencharprototype));
        
        if (!x->break_after_notification) {
            t_dada_gamechar *newgamechar = (t_dada_gamechar *)platform_add_single_item_from_prototype(x, gencharprototype, DADAITEM_TYPE_GAMECHAR, from_me ? from_me->coord : build_pt(x->displayed_coord.x + x->displayed_coord.width/2., x->displayed_coord.y + x->displayed_coord.height/2.), 0);
            if (from_me) {
                if (from_me->type == DADAITEM_TYPE_BLOCK) {
                    newgamechar->speed = build_pt(0, 2);
                    newgamechar->state = DADA_GAMECHAR_STATE_GENERATING;
                } else if (from_me->type == DADAITEM_TYPE_GAMECHAR) {
                    char from_me_dir = ((t_dada_gamechar *)from_me)->direction;
                    newgamechar->r_it.coord = build_pt(from_me->coord.x + from_me_dir * from_me->width/2. + newgamechar->r_it.width/2. + 0.0001, from_me->coord.y);
                    newgamechar->state = platform_gamechar_get_default_movement_state(x, newgamechar);
                    newgamechar->speed = build_pt(fabs(newgamechar->speed.x) * from_me_dir, newgamechar->speed.y);
                }
                newgamechar->generated_from = (t_dadaitem *)from_me;
                newgamechar->generation_or_portal_direction = DADA_GAMECHAR_VIA_SIDE_TOP;
            }
            
            if (attrs && newgamechar)
                dadaitem_set_from_llll(dadaobj_cast(x), (t_dadaitem *)newgamechar, attrs, 0);
        }
    }
}




void bump_block_do(t_platform *x, t_symbol *s, long ac, t_atom *av)
{
    t_dadaitem *item = (t_dadaitem *)atom_getobj(av);
    double new_x = atom_getfloat(av + 1);
    double new_y = atom_getfloat(av + 2);
    
    item->coord.x = new_x;
    item->coord.y = new_y;
    jbox_redraw((t_jbox *)x);
}

char platform_is_gamechar_on_block(t_platform *x, t_dada_gamechar *gamechar, t_dada_block *block)
{
    if (gamechar->r_it.coord.x > block->r_it.coord.x - block->r_it.width/2. && gamechar->r_it.coord.x < block->r_it.coord.x + block->r_it.width/2.) {
        if (gamechar->r_it.coord.y > block->r_it.coord.y && gamechar->r_it.coord.y < block->r_it.coord.y + block->r_it.height/2. + gamechar->r_it.height/2. + DADA_PLATFORM_BLOCKS_BUMP_GAMECHAR_TOLERANCE)
            return true;
    }
    
    return false;
}

char platform_is_gamechar_alive(t_platform *x, t_dada_gamechar *gamechar)
{
    if (gamechar->state & DADA_GAMECHAR_STATE_DYING || gamechar->state & DADA_GAMECHAR_STATE_DEAD)
        return false;
    return true;
}

t_symbol *direction_to_sym(long direction)
{
    switch (direction) {
        case DADA_GAMECHAR_VIA_SIDE_BOTTOM:
            return gensym("down");
            break;

        case DADA_GAMECHAR_VIA_SIDE_TOP:
            return gensym("up");
            break;
        
        case DADA_GAMECHAR_VIA_SIDE_LEFT:
            return gensym("left");
            break;
        
        case DADA_GAMECHAR_VIA_SIDE_RIGHT:
            return gensym("right");
            break;
            
        default:
            return NULL;
            break;
    }
}


long reverse_position(long pos)
{
    long res = pos;
    if (pos & DADA_GAMECHAR_VIA_SIDE_RIGHT) {
        res &= ~DADA_GAMECHAR_VIA_SIDE_RIGHT;
        res |= DADA_GAMECHAR_VIA_SIDE_LEFT;
    }
    if (pos & DADA_GAMECHAR_VIA_SIDE_LEFT) {
        res &= ~DADA_GAMECHAR_VIA_SIDE_LEFT;
        res |= DADA_GAMECHAR_VIA_SIDE_RIGHT;
    }
    if (pos & DADA_GAMECHAR_VIA_SIDE_TOP) {
        res &= ~DADA_GAMECHAR_VIA_SIDE_TOP;
        res |= DADA_GAMECHAR_VIA_SIDE_BOTTOM;
    }
    if (pos & DADA_GAMECHAR_VIA_SIDE_BOTTOM) {
        res &= ~DADA_GAMECHAR_VIA_SIDE_BOTTOM;
        res |= DADA_GAMECHAR_VIA_SIDE_TOP;
    }
    return res;
}


void platform_bump_block(t_platform *x, t_dada_gamechar *gamechar, t_dada_block *block, long direction)
{
    
    if (x->notify_blocks)
        send_notification_for_action(x, (t_dadaitem *)gamechar, gensym("bumps"), (t_dadaitem *)block, direction_to_sym(reverse_position(direction)));
    
    if (!x->break_after_notification) {
        t_atom a[3];
        atom_setobj(a, block);
        atom_setfloat(a+1, block->r_it.coord.x + DADA_PLATFORM_BLOCKS_BUMP_SHIFT * (direction & DADA_GAMECHAR_VIA_SIDE_LEFT ? -1 : (direction & DADA_GAMECHAR_VIA_SIDE_RIGHT ? 1 : 0)));
        atom_setfloat(a+2, block->r_it.coord.y + DADA_PLATFORM_BLOCKS_BUMP_SHIFT * (direction & DADA_GAMECHAR_VIA_SIDE_TOP ? 1 : (direction & DADA_GAMECHAR_VIA_SIDE_BOTTOM ? -1 : 0)));
        
        schedule_delay((t_object *)x, (method)bump_block_do, DADA_PLATFORM_BLOCKS_BUMP_TIME, NULL, 3, a);
        
        atom_setfloat(a+1, block->r_it.coord.x);
        atom_setfloat(a+2, block->r_it.coord.y);
        schedule_delay((t_object *)x, (method)bump_block_do, 2 * DADA_PLATFORM_BLOCKS_BUMP_TIME, NULL, 3, a);

        play_music(x, block->music);
    }
    
    // checking if some character dies!
    for (t_llllelem *el = x->gamechars->l_head; el; el = el->l_next) {
        t_dada_gamechar *temp = (t_dada_gamechar *)hatom_getobj(&el->l_hatom);
        if (platform_is_gamechar_alive(x, temp) && platform_is_gamechar_on_block(x, temp, block)) {
            if (temp->how_dies & DADA_GAMECHAR_VIA_BUMP)
                platform_gamechar_die(x, temp, gamechar);
            else
                temp->speed.x = fabs(temp->speed.x) * (temp->r_it.coord.x > gamechar->r_it.coord.x ? 1 : -1); // possibly switch direction
        }
    }
}

void platform_hit_block(t_platform *x, t_dada_gamechar *gamechar, t_dada_block *block, long direction)
{
    t_llllelem *el;
    
    block->hit_count++;
    el = llll_getindex(block->hit_sequence, block->hit_count, block->loop_hit_sequence ? I_MODULO : I_STANDARD);
//    el = direction > 0 ? llll_getindex(block->hit_sequence, block->hit_count, block->loop_hit_sequence ? I_MODULO : I_STANDARD) : NULL;
    if (el) {
        if (hatom_gettype(&el->l_hatom) == H_LLLL) {
            t_llll *ll = llll_clone(hatom_getllll(&el->l_hatom));
            if (ll->l_head && hatom_gettype(&ll->l_head->l_hatom) != H_LLLL)
                llll_wrap_once(&ll);
            parse_instructions(x, ll, (t_dadaitem *)block);
            llll_free(ll);
        } else {
            if (hatom_gettype(&el->l_hatom) == H_SYM)
            {
                t_symbol *sym = hatom_getsym(&el->l_hatom);
                if (sym == gensym("break")) {
                    if (gamechar->abilities & DADA_GAMECHAR_ABILITY_BREAK) {
                        platform_break_block(x, gamechar, block);
                        return; // no bumping
                    }
                }
            }
        }
    }
    
    platform_bump_block(x, gamechar, block, reverse_position(direction));
    if (direction == DADA_GAMECHAR_VIA_SIDE_TOP)
        platform_gamechar_jump(x, gamechar, -gamechar->speed.y); // bounce!
}

void platform_take_coin(t_platform *x, t_dada_gamechar *gamechar, t_dada_coin *coin)
{

	if (x->notify_coins)
		send_notification_for_action(x, (t_dadaitem *)gamechar, gensym("takes"), (t_dadaitem *)coin, NULL);

	if (!x->break_after_notification) {
		coin->taken = true;
		gamechar->points += coin->points;
		gamechar->vp += coin->vp;
		
		if (coin->points)
			display_number_temp(x, coin->points, coin->r_it.coord, false);
        if (coin->vp)
            display_number_temp(x, coin->vp, coin->r_it.coord, true);

        play_music(x, coin->music);
	}
}


void platform_take_points_from_block(t_platform *x, t_dada_gamechar *gamechar, t_dada_block *block, long points, long vp)
{
    if (x->notify_coins)
        send_notification_for_action(x, (t_dadaitem *)gamechar, gensym("earns"), (t_dadaitem *)block, NULL);
    
    if (!x->break_after_notification) {
        gamechar->points += points;
        gamechar->vp += vp;
        
        if (points)
            display_number_temp(x, points, build_pt(block->r_it.coord.x, block->r_it.coord.y + 1), false);
        
        play_music(x, block->music);
    }
}


t_pt platform_find_resurrection_position(t_platform *x, t_dada_gamechar *gamechar, double dead_x)
{
	t_llllelem *elem;
	t_llll *best_ll = NULL;
	double best_diff = -1; 
	if (gamechar->resurrectpositions) {
		for (elem = gamechar->resurrectpositions->l_head; elem; elem = elem->l_next) {
			if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
				t_llll *ll = hatom_getllll(&elem->l_hatom);
				if (ll && ll->l_head && is_hatom_number(&ll->l_head->l_hatom)) {
					double this_x = hatom_getdouble(&ll->l_head->l_hatom);
					if (this_x <= dead_x) {
						double diff = dead_x - this_x;
						if (!best_ll || diff < best_diff) {
							best_diff = diff;
							best_ll = ll; 
						}
					}
				}
			}
		}
	}
	
	if (best_ll) {
		return llll_to_pt(best_ll);
	} else 
		return build_pt(dead_x, 10);
}

void platform_gamechar_resurrect(t_platform *x, t_symbol *s, long ac, t_atom *av)
{
	t_dada_gamechar *gamechar = (t_dada_gamechar *)atom_getobj(av);
	double x_pos = atom_getfloat(av + 1);
	
    x->play_state = DADA_PLATFORM_PLAYSTATE_STANDARD;
	gamechar->state = DADA_GAMECHAR_STATE_IDLE;
	gamechar->direction = 1;
	gamechar->r_it.coord = platform_find_resurrection_position(x, gamechar, x_pos);
	gamechar->speed = build_pt(0, 0);
//	platform_resume_do(x);
 
	jbox_redraw((t_jbox *)x);
}


void platform_restart(t_platform *x, long hero_vp)
{
    x->goto_options.herovp = hero_vp;
    if (x->fixed_state)
        platform_set_state(x, x->fixed_state);
    platform_iar(x);
}


t_dadaitem *platform_symbol_to_single_dadaitem(t_platform *x, t_symbol *name, t_dadaitem *subject)
{
    if (!name)
        return NULL;
    
    if (name == gensym("hero")) {
        return (t_dadaitem *)x->hero;
    } else if (name == gensym("me")) {
        return subject;
    } else {
        return dadaitem_get_from_name(dadaobj_cast(x), name);
    }
    
    return NULL;
}

t_dada_gamechar *platform_symbol_to_single_gamechar(t_platform *x, t_symbol *name, t_dadaitem *subject)
{
    t_dadaitem *item = platform_symbol_to_single_dadaitem(x, name, subject);
    if (item && item->type != DADAITEM_TYPE_GAMECHAR) {
        object_warn((t_object *)x, "%s is not a game character!", name->s_name);
        return NULL;
    }
    
    return (t_dada_gamechar *)item;
}

t_dada_portal *platform_symbol_to_single_portal(t_platform *x, t_symbol *name, t_dadaitem *subject)
{
    t_dadaitem *item = platform_symbol_to_single_dadaitem(x, name, subject);
    if (item && item->type != DADAITEM_TYPE_PORTAL) {
        object_warn((t_object *)x, "%s is not a portal!", name->s_name);
        return NULL;
    }
    
    return (t_dada_portal *)item;
}

t_dada_block *platform_symbol_to_single_block(t_platform *x, t_symbol *name, t_dadaitem *subject)
{
    t_dadaitem *item = platform_symbol_to_single_dadaitem(x, name, subject);
    if (item && item->type != DADAITEM_TYPE_BLOCK) {
        object_warn((t_object *)x, "%s is not a block!", name->s_name);
        return NULL;
    }
    
    return (t_dada_block *)item;
}


t_llll *platform_symbol_to_dadaitems(t_platform *x, t_symbol *name, t_dadaitem *subject)
{
    t_llll *ll = llll_get();
    
    if (!name)
        return ll;
    
    if (name == gensym("hero")) {
        llll_appendobj(ll, x->hero);
    } else if (name == gensym("me")) {
        llll_appendobj(ll, subject);
    } else {
        llll_chain(ll, dadaitem_get_all_from_name(dadaobj_cast(x), name));
    }
    
    return ll;
}

t_llll *platform_symbol_to_gamechars(t_platform *x, t_symbol *name, t_dadaitem *subject)
{
    t_llll *ll = platform_symbol_to_dadaitems(x, name, subject);
    t_llllelem *elem, *nextelem;
    for (elem = ll->l_head; elem; elem = nextelem) {
        t_dadaitem *item = (t_dadaitem *)hatom_getobj(&elem->l_hatom);
        nextelem = elem->l_next;
        if (item->type != DADAITEM_TYPE_GAMECHAR)
            llll_destroyelem(elem);
    }
    return ll;
}



void parse_instructions_fn(t_platform *x, t_symbol *s, long ac, t_atom *av)
{
    t_dadaitem *subject = (t_dadaitem *)atom_getobj(av);
    t_llll *ll = llll_parse(ac-1, av+1);
    parse_instructions(x, ll, subject);
    llll_free(ll);
}


t_llll *parse_instructions_get_who(t_platform *x, t_llllelem **temp, t_dadaitem *subject, char gamechars_only, t_llll **who_ll)
{
    long all = false;
    
    if (who_ll && !*who_ll)
        *who_ll = llll_get();
    
    if (*temp && hatom_gettype(&(*temp)->l_hatom) == H_SYM) {
        if (hatom_getsym(&(*temp)->l_hatom) == _llllobj_sym_all) {
            all = true;
            if (who_ll && *who_ll)
                llll_appendsym(*who_ll, _llllobj_sym_all);
            (*temp) = (*temp)->l_next;
            if ((*temp) && hatom_gettype(&(*temp)->l_hatom) == H_SYM) {
                t_symbol *who = hatom_getsym(&(*temp)->l_hatom);
                if (who_ll && *who_ll)
                    llll_appendsym(*who_ll, who);
                (*temp) = (*temp)->l_next;
                if (gamechars_only)
                    return platform_symbol_to_gamechars(x, who, subject);
                else
                    return platform_symbol_to_dadaitems(x, who, subject);
            }
        } else {
            t_symbol *who = hatom_getsym(&(*temp)->l_hatom);
            if (who_ll && *who_ll)
                llll_appendsym(*who_ll, who);
            t_llll *ll = llll_get();
            t_dadaitem *item = NULL;
            if (gamechars_only)
                item = (t_dadaitem *)platform_symbol_to_single_gamechar(x, who, subject);
            else
                item = platform_symbol_to_single_dadaitem(x, who, subject);

            (*temp) = (*temp)->l_next;
            if (item)
                llll_appendobj(ll, item);
            return ll;
        }
    }
    return NULL;
}


void load_default_goto_options(t_platform *x)
{
    x->goto_options.goto_portal = NULL;
    x->goto_options.intro = 0;
    x->goto_options.resettime = 0;
    x->goto_options.heropoints = -1;
    x->goto_options.herovp = -1;
    x->goto_options.keephero = 0;
}


long parse_instructions(t_platform *x, t_llll *instructions, t_dadaitem *subject)
{
    long res = DADA_PLATFORM_INSTRUCTION_RV_NONE;
    
    if (!instructions)
        return res;
    
    // WE NEED TO MAKE A LOCAL COPY OF THE INSTRUCTIONS;
    // because the instruction might change the field containing the instructions themselves!!
    t_llll *instructions_local = llll_clone(instructions);
    
    t_llllelem *el, *temp;
    for (el = instructions_local->l_head; el; el = el->l_next) {
        if (hatom_gettype(&el->l_hatom) == H_LLLL) {
            t_llll *ll = hatom_getllll(&el->l_hatom);
            if (ll && ll->l_head && hatom_gettype(&ll->l_head->l_hatom) == H_SYM) {
                t_symbol *router = hatom_getsym(&ll->l_head->l_hatom);
                temp = ll->l_head->l_next;
                
                if (router == gensym("wait")) {
                    if (temp && is_hatom_number(&temp->l_hatom)) {
                        double for_how_long = hatom_getdouble(&temp->l_hatom);
                        
                        // schedule another instruction in <for_how_long> ms.
                        t_llll *newll = llll_get();
                        t_llllelem *eltmp;
                        for (eltmp = el->l_next; eltmp; eltmp = eltmp->l_next)
                            llll_appendhatom_clone(newll, &eltmp->l_hatom);
                        t_atom *av = NULL;
                        long ac = llll_deparse(newll, &av, 1, 0);
                        atom_setobj(av, subject);
                        llll_free(newll);
                        schedule_delay(x, (method)parse_instructions_fn, for_how_long, 0, ac, av);
                        break;
                    }
                } else if (router == gensym("generate")) {
                    if (temp && hatom_gettype(&temp->l_hatom) == H_SYM) {
                        t_symbol *what = hatom_getsym(&temp->l_hatom);
                        t_dadaitem *from_whom = subject;
                        t_llll *attrs = NULL;

                        temp = temp->l_next;
                        
                        if (temp && temp->l_next && hatom_gettype(&temp->l_hatom) == H_SYM && hatom_getsym(&temp->l_hatom) == gensym("from") && hatom_gettype(&temp->l_next->l_hatom) == H_SYM) {
                            t_symbol *whom = hatom_getsym(&temp->l_next->l_hatom);
                            from_whom = platform_symbol_to_single_dadaitem(x, whom, subject);
                            temp = temp->l_next->l_next;
                        }
                        if (temp && hatom_gettype(&temp->l_hatom) == H_SYM && hatom_getsym(&temp->l_hatom) == gensym("with")) {
                            temp = temp->l_next;
                            if (temp) {
                                attrs = llll_get();
                                for ( ; temp; temp = temp->l_next)
                                    llll_appendhatom_clone(attrs, &temp->l_hatom);
                                if (attrs->l_depth == 1)
                                    llll_wrap_once(&attrs);
                            }
                        }

                        if (what)
                            platform_gen_gamechar(x, what, from_whom, attrs);
                        
                        llll_free(attrs);
                    }
                
                } else if (router == gensym("dontdie")) {
                    res = DADA_PLATFORM_INSTRUCTION_RV_DONTDIE;

                } else if (router == gensym("gameover")) {
                    platform_gameover(x);

                } else if (router == gensym("win")) {
                    platform_win(x);

                } else if (router == gensym("break")) {
                    
                    if (temp && hatom_gettype(&temp->l_hatom) == H_SYM) {
                        t_dada_block *what = platform_symbol_to_single_block(x, hatom_getsym(&temp->l_hatom), subject);
                        t_dada_gamechar *by_whom = NULL;
                        if (temp->l_next && temp->l_next->l_next && hatom_gettype(&temp->l_next->l_hatom) == H_SYM && hatom_getsym(&temp->l_next->l_hatom) == gensym("by") && hatom_gettype(&temp->l_next->l_next->l_hatom) == H_SYM) {
                            t_symbol *whom = hatom_getsym(&temp->l_next->l_next->l_hatom);
                            by_whom = platform_symbol_to_single_gamechar(x, whom, subject);
                        }
                        
                        if (by_whom && what)
                            platform_break_block(x, by_whom, what);
                    }
                    
                    
                } else if (router == gensym("notify")) {
                    t_llll *notification = llll_clone(ll);
                    llll_behead(ll);
                    llll_behead(ll);
                    send_notification(x, notification);
                    llll_free(ll);

                } else if (router == gensym("goto")) { // open new level
                    if (temp && hatom_gettype(&temp->l_hatom) == H_SYM) {
                        t_symbol *level = NULL, *portal = NULL;
                        if (hatom_getsym(&temp->l_hatom) == gensym("level") && temp->l_next && hatom_gettype(&temp->l_next->l_hatom) == H_SYM) {
                            level = hatom_getsym(&temp->l_next->l_hatom);
                            temp = temp->l_next->l_next;
                        }
                        
                        if (temp && hatom_gettype(&temp->l_hatom) == H_SYM && (hatom_getsym(&temp->l_hatom) == gensym("at") || hatom_getsym(&temp->l_hatom) == gensym("portal")))
                            temp = temp->l_next;
                        
                        if (temp && hatom_gettype(&temp->l_hatom) == H_SYM) {
                            portal = hatom_getsym(&temp->l_hatom);
                            temp = temp->l_next;
                        }
                        
                        load_default_goto_options(x);
                        
                        if (hatom_getsym(&temp->l_hatom) == gensym("with")) {
                            temp = temp->l_next;
                            while (temp && hatom_gettype(&temp->l_hatom) == H_LLLL) {
                                t_llll *temp_ll = hatom_getllll(&temp->l_hatom);
                                if (temp_ll && temp_ll->l_size >= 2 && hatom_gettype(&temp_ll->l_head->l_hatom) == H_SYM) {
                                    t_symbol *temp_router = hatom_getsym(&temp_ll->l_head->l_hatom);
                                    if (temp_router == gensym("portal") && hatom_gettype(&temp_ll->l_head->l_next->l_hatom) == H_SYM)
                                        portal = hatom_getsym(&temp_ll->l_head->l_next->l_hatom);
                                    else if (temp_router == gensym("intro") && hatom_gettype(&temp_ll->l_head->l_next->l_hatom) == H_LONG)
                                        x->goto_options.intro = hatom_getlong(&temp_ll->l_head->l_next->l_hatom);
                                    else if (temp_router == gensym("resettime") && hatom_gettype(&temp_ll->l_head->l_next->l_hatom) == H_LONG)
                                        x->goto_options.resettime = hatom_getlong(&temp_ll->l_head->l_next->l_hatom);
                                    else if (temp_router == gensym("keephero") && hatom_gettype(&temp_ll->l_head->l_next->l_hatom) == H_LONG)
                                        x->goto_options.keephero = hatom_getlong(&temp_ll->l_head->l_next->l_hatom);
                                    else if (temp_router == gensym("herovp") && hatom_gettype(&temp_ll->l_head->l_next->l_hatom) == H_LONG)
                                        x->goto_options.herovp = hatom_getlong(&temp_ll->l_head->l_next->l_hatom);
                                    else if (temp_router == gensym("heropoints") && hatom_gettype(&temp_ll->l_head->l_next->l_hatom) == H_LONG)
                                        x->goto_options.heropoints = hatom_getlong(&temp_ll->l_head->l_next->l_hatom);
                                }
                                temp = temp->l_next;
                            }
                        }
                        
                        
                        if (level) {
                            t_atom av;
                            if (portal)
                                x->goto_options.goto_portal = portal;
                            atom_setsym(&av, level);
                            dadaobj_jbox_read((t_dadaobj_jbox *)x, NULL, 1, &av);
                            break;
                        } else {
                            if (portal)
                                platform_portal_exit(x, x->hero, platform_symbol_to_single_portal(x, portal, (t_dadaitem *)x->hero));
                        }
                    }

                } else if (router == gensym("give")) { // give points or vp
                    if (temp && hatom_gettype(&temp->l_hatom) == H_SYM) {
                        t_llll *gamechars = parse_instructions_get_who(x, &temp, subject, true, NULL);
                        for (t_llllelem *gamecharel = gamechars->l_head; gamecharel; gamecharel = gamecharel->l_next) {
                            t_dada_gamechar *gamechar = (t_dada_gamechar *)hatom_getobj(&gamecharel->l_hatom);
                            t_dadaitem *from_whom = subject;
                            long how_many = 0;
                            if (temp && hatom_gettype(&temp->l_hatom) == H_LONG)
                                how_many = hatom_getlong(&temp->l_hatom);
                            if (how_many > 0) {
                                if (temp->l_next && temp->l_next->l_next && temp->l_next->l_next->l_next && hatom_gettype(&temp->l_next->l_next->l_hatom) == H_SYM && hatom_getsym(&temp->l_next->l_next->l_hatom) == gensym("from") && hatom_gettype(&temp->l_next->l_next->l_next->l_hatom) == H_SYM) {
                                    t_symbol *whom = hatom_getsym(&temp->l_next->l_next->l_next->l_hatom);
                                    from_whom = platform_symbol_to_single_dadaitem(x, whom, subject);
                                }
                                
                                t_pt coord = build_pt(from_whom->coord.x, from_whom->coord.y + from_whom->height/2. + 0.7);
                                
                                if (temp && temp->l_next && hatom_gettype(&temp->l_next->l_hatom) == H_SYM && hatom_getsym(&temp->l_next->l_hatom) == gensym("vp")) {
                                    gamechar->vp += how_many;
                                    display_number_temp(x, how_many, coord, true);
                                } else {
                                    gamechar->points += how_many;
                                    display_number_temp(x, how_many, coord, false);
                                }
                            }
                        }
                        llll_free(gamechars);
                    }
                    

                } else if (router == gensym("add") || router == gensym("remove")) {
                    temp = ll->l_head->l_next;
                    if (temp && hatom_gettype(&temp->l_hatom) == H_SYM) {
                        t_llll *who_ll = NULL;
                        t_llll *gamechars = parse_instructions_get_who(x, &temp, subject, true, &who_ll);
                        for (t_llllelem *gamecharel = gamechars->l_head; gamecharel; gamecharel = gamecharel->l_next) {
                            t_dada_gamechar *gamechar = (t_dada_gamechar *)hatom_getobj(&gamecharel->l_hatom);

                            if (temp && hatom_gettype(&temp->l_hatom) == H_SYM) {
                                t_symbol *what = hatom_getsym(&temp->l_hatom);
                                temp = temp->l_next;
                                if (what == gensym("ability")) {
                                    long ability = dadaitem_gamechar_llllelem_to_ability(temp);
                                    double for_how_long = -1; // always
                                    if (temp && temp->l_next && temp->l_next->l_next && hatom_gettype(&temp->l_next->l_hatom) == H_SYM && hatom_getsym(&temp->l_next->l_hatom) == gensym("during") && is_hatom_number(&temp->l_next->l_next->l_hatom)) {
                                        for_how_long = hatom_getdouble(&temp->l_next->l_next->l_hatom);
                                    }
                                    
                                    if (router == gensym("add"))
                                        gamechar->abilities |= ability;
                                    else
                                        gamechar->abilities &= ~ability;
                                    
                                    if (temp && ability > 0 && for_how_long > 0) {
                                        // schedule another instruction in <for_how_long> ms.
                                        t_llll *newll = llll_get();
                                        llll_appendsym(newll, router == gensym("add") ? gensym("remove") : gensym("add"));
                                        llll_chain_clone(newll, who_ll);
                                        llll_appendsym(newll, gensym("ability"));
                                        llll_appendhatom_clone(newll, &temp->l_hatom);
                                        llll_wrap_once(&newll);
                                        t_atom *av = NULL;
                                        long ac = llll_deparse(newll, &av, 1, 0);
                                        atom_setobj(av, subject);
                                        llll_free(newll);
                                        schedule_delay(x, (method)parse_instructions_fn, for_how_long, 0, ac, av);
                                    }
                                }
                            }
                        }
                        
                        llll_free(gamechars);
                        llll_free(who_ll);
                    }

                } else if (router == gensym("change")) {
                    temp = ll->l_head->l_next;
                    if (temp && hatom_gettype(&temp->l_hatom) == H_SYM) {
                        t_llll *who_ll = NULL;
                        t_llll *items = parse_instructions_get_who(x, &temp, subject, false, NULL);
                        for (t_llllelem *itemsel = items->l_head; itemsel; itemsel = itemsel->l_next) {
                            t_dadaitem *item = (t_dadaitem *)hatom_getobj(&itemsel->l_hatom);
                            
                            if (temp) {
                                t_llll *attrs = llll_get();
                                for ( ; temp; temp = temp->l_next)
                                    llll_appendhatom_clone(attrs, &temp->l_hatom);
                                if (attrs->l_depth == 1)
                                    llll_wrap_once(&attrs);
                                dadaitem_set_from_llll(dadaobj_cast(x), item, attrs, 0);
                                llll_free(attrs);
                            }
                        }
                        llll_free(who_ll);
                        llll_free(items);
                    }
                }
            }
        }
    }
    
    llll_free(instructions_local);
    
    return res;
}

long parse_instructions_char(t_platform *x, char *instructions, t_dadaitem *subject)
{
    t_llll *ll = llll_from_text_buf(instructions, false);
    long res = parse_instructions(x, ll, subject);
    llll_free(ll);
    return res;
}


void platform_gameover_fn(t_platform *x, t_symbol *s, long ac, t_atom *av)
{
    platform_gameover(x);
}


void platform_gameover(t_platform *x)
{
    if (x->notify_gamechars)
        send_notification_symbol(x, gensym("gameover"));
    
    if (x->hero)
        x->hero->vp = 0;
    
    x->play_state = DADA_PLATFORM_PLAYSTATE_END_GAMEOVER_PRE;
}

void platform_win(t_platform *x)
{
    if (x->notify_gamechars)
        send_notification_symbol(x, gensym("win"));
    
    x->play_state = DADA_PLATFORM_PLAYSTATE_END_WIN_PRE;
}



long platform_gamechar_die(t_platform *x, t_dada_gamechar *gamechar, t_dada_gamechar *killer, char forced_because_of_time)
{
	long res = 0;
	
    if (forced_because_of_time || parse_instructions(x, gamechar->kill_sequence, (t_dadaitem *)gamechar) != DADA_PLATFORM_INSTRUCTION_RV_DONTDIE) {

        if (x->notify_gamechars) {
            if (killer)
                send_notification_for_action(x, (t_dadaitem *)killer, gamechar->type == DADA_GAMECHAR_TYPE_FOOD ? gensym("eats") : gensym("kills"), (t_dadaitem *)gamechar, NULL);

            send_notification_for_action(x, (t_dadaitem *)gamechar, gamechar->type == DADA_GAMECHAR_TYPE_FOOD ? gensym("eaten") : (killer && killer->abilities & DADA_GAMECHAR_ABILITY_KILL ? gensym("killed") : gensym("died")), NULL, NULL);
        }
        
        if (!x->break_after_notification) {
            if (forced_because_of_time)
                gamechar->vp = 0;
            else
                gamechar->vp -= 1;
            gamechar->state = DADA_GAMECHAR_STATE_DYING;
            
            t_dada_gamechar *hero = x->hero;
            if (gamechar == hero) {
                if (gamechar->vp <= 0) {
                    // game over
                    schedule_delay(x, (method)platform_gameover_fn, 1000, NULL, 0, NULL);
                    res = 0;
                } else {
                    x->play_state = DADA_PLATFORM_PLAYSTATE_DYING;
                    gamechar->speed = build_pt(0, x->m_level.level_height);
                    
                    // schedule resurrection
                    t_atom av[2];
                    atom_setobj(av, gamechar);
                    atom_setfloat(av + 1, gamechar->r_it.coord.x);
                    schedule_delay(x, (method)platform_gamechar_resurrect, 2000, 0, 2, av);
                    res = 0; 
                }
            } else {
                gamechar->speed = build_pt(0, 4);
            }
        }
    }
	
	jbox_redraw((t_jbox *)x);
	return res;
}


t_rect gamechar_get_physics_rect_boundingbox(t_platform *x, t_dada_gamechar *gamechar)
{
    return platform_center_and_ext_to_boundingbox(x, gamechar->r_it.coord, gamechar->physics_ext);
}


void platform_check_coin_collisions(t_platform *x, t_dada_gamechar *gamechar)
{	
//	t_rect r1 = rect_baricentric_to_boundingbox(build_rect(x->gamechars[i].r_it.coord.x, x->gamechars[i].r_it.coord.y, x->gamechars[i].width, x->gamechars[i].height));
    t_rect r1 = gamechar_get_physics_rect_boundingbox(x, gamechar); //dadaitem_get_rect_boundingbox(&gamechar->r_it);
	
	
	double start_x_to_check = gamechar->r_it.coord.x - gamechar->r_it.width / 2.;
	double end_x_to_check = gamechar->r_it.coord.x + gamechar->r_it.width / 2.;
	
	// check collisions
    for (t_llllelem *coinelem = x->coins->l_head; coinelem; coinelem = coinelem->l_next) {
        t_dada_coin *coin = (t_dada_coin *)hatom_getobj(&coinelem->l_hatom);
        
        if (coin->taken || !coin->takeable)
            continue;
        
        if (coin->r_it.coord.x + coin->r_it.width / 2. < start_x_to_check)
            continue;
        
        if (coin->r_it.coord.x - coin->r_it.width / 2. > end_x_to_check)
            break;
        
        //		t_rect r2_baric = build_rect(x->coins[j].r_it.coord.x, x->coins[j].r_it.coord.y, x->coins[j].width, x->coins[j].height);
        t_rect r2 = dadaitem_get_rect_boundingbox(&coin->r_it);
        if (jgraphics_rectintersectsrect(&r1, &r2))
            platform_take_coin(x, gamechar, coin);
    }
}
long platform_check_gamechar_collisions(t_platform *x, t_dada_gamechar *gamechar)
{
	long check_pad = 4;
	t_rect r1_baric = build_rect(gamechar->r_it.coord.x, gamechar->r_it.coord.y, gamechar->r_it.width, gamechar->r_it.height);
	t_rect r1 = rect_baricentric_to_boundingbox(r1_baric);
	
	double start_x_to_check = gamechar->r_it.coord.x - gamechar->r_it.width / 2. - check_pad;
	double end_x_to_check = gamechar->r_it.coord.x + gamechar->r_it.width / 2. + check_pad;
	
//    post("Checking collision of %s...", gamechar->r_it.name->s_name);

    // check collisions
    for (t_llllelem *gamecharelem = x->gamechars->l_head; gamecharelem; gamecharelem = gamecharelem->l_next) {
        t_dada_gamechar *gamechar_tmp = (t_dada_gamechar *)hatom_getobj(&gamecharelem->l_hatom);

		if (gamechar_tmp == gamechar)
			continue;

		if (gamechar_tmp->r_it.flags & D_INACTIVE || gamechar_tmp->state == DADA_GAMECHAR_STATE_DEAD || gamechar_tmp->state == DADA_GAMECHAR_STATE_DYING)
			continue;
		
		if (gamechar_tmp->r_it.coord.x + gamechar_tmp->r_it.width / 2. < start_x_to_check )
			continue;

		if (gamechar_tmp->r_it.coord.x - gamechar_tmp->r_it.width / 2. > end_x_to_check)
			continue;

//        post("   ...with %s", gamechar_tmp->r_it.name->s_name);

		t_rect r2_baric = build_rect(gamechar_tmp->r_it.coord.x, gamechar_tmp->r_it.coord.y, gamechar_tmp->r_it.width, gamechar_tmp->r_it.height);
//		t_rect r2 = rect_baricentric_to_boundingbox(r2_baric);
        t_rect r2 = gamechar_get_physics_rect_boundingbox(x, gamechar_tmp); // dadaitem_get_rect_boundingbox(&gamechar_tmp->r_it);
		if (jgraphics_rectintersectsrect(&r1, &r2)) {
			long posbase = baricentric_rect_rect_relative_position(&r1_baric, &r2_baric);
            
            // situation between gamechar and gamechar_tmp is symmetric
            t_dada_gamechar *gc[2];
            long pos[2];
            long h, i, j, offset = 0;
            gc[0] = gamechar; gc[1] = gamechar_tmp;
            pos[1] = posbase; pos[0] = reverse_position(posbase);
            
            if (gc[0]->type != DADA_GAMECHAR_TYPE_USERCONTROL)
                offset = 1; // this is needed in order to first check that an enemy has been killed by Juan, and only LATER that Juan has been killed
            
            for (h = offset; h < 2 + offset; h++) {
                char j_dies = false;
                char i_dies = false; // could be a bullet! if it hits someone, the bullet dies too.
                i = h % 2;
                j = (h + 1) % 2;
                
                // Does i kill j?
                if (gc[i]->abilities & DADA_GAMECHAR_ABILITY_KILL && gc[j]->abilities & DADA_GAMECHAR_ABILITY_DIE) {
                    
                    if (gc[j]->type == DADA_GAMECHAR_TYPE_FOOD) {
                        // j is food for user-controlled characters
                        if (gc[i]->type == DADA_GAMECHAR_TYPE_USERCONTROL)
                            j_dies = true;
                    
                    } else if (gc[i]->type == DADA_GAMECHAR_TYPE_BULLET) {
                        if (gc[j]->how_dies & DADA_GAMECHAR_VIA_BULLET && gc[i]->generated_from != (t_dadaitem *)gc[j])
                            j_dies = i_dies = true;
/*
                    } else if (gc[j]->type == DADA_GAMECHAR_TYPE_ENEMY) {
                        if (pos[j] & gc[j]->how_dies ||
                            (pos[j] & DADA_GAMECHAR_VIA_SIDE_LEFT_RIGHT && gc[j]->how_dies & DADA_GAMECHAR_VIA_GLIDE && gc[i]->state == DADA_GAMECHAR_STATE_GLIDING))
                            j_dies = true;

                    } else if (gc[j]->type == DADA_GAMECHAR_TYPE_USERCONTROL) { */
                    } else if (gc[j]->type == DADA_GAMECHAR_TYPE_ENEMY || gc[j]->type == DADA_GAMECHAR_TYPE_USERCONTROL) {
                        if ((pos[j] & gc[j]->how_dies && pos[i] & gc[i]->how_kills) ||
                            (pos[j] & DADA_GAMECHAR_VIA_SIDE_LEFT_RIGHT && gc[j]->how_dies & DADA_GAMECHAR_VIA_GLIDE && gc[i]->state == DADA_GAMECHAR_STATE_GLIDING))
                            j_dies = true;
                    }
                }
            
                long res = 0;
                if (j_dies) {
                    res |= platform_gamechar_die(x, gc[j], gc[i]);
                    if (pos[i] & DADA_GAMECHAR_VIA_SIDE_BOTTOM) {
                        gc[i]->speed.y = DADA_PLATFORM_GAMECHAR_JUMP_FOR_KILLING;
                    }
                    if (i_dies)
                        res |= platform_gamechar_die(x, gc[i], NULL);
                    return res;
                }
            }

            platform_gamechar_handle_obstacle(x, gamechar, posbase, (t_dadaitem *)gamechar_tmp);

/*
            if (gamechar->abilities & DADA_GAMECHAR_ABILITY_KILL && pos & gamechar_tmp->how_dies && gamechar_tmp->abilities & DADA_GAMECHAR_ABILITY_DIE && !(gamechar_tmp->abilities & DADA_GAMECHAR_ABILITY_FEED)) {
				return platform_gamechar_die(x, gamechar_tmp, gamechar);
			} else if (gamechar_tmp->abilities & DADA_GAMECHAR_ABILITY_KILL && gamechar->abilities & DADA_GAMECHAR_ABILITY_DIE && gamechar->user_control > 0 && pos & gamechar_tmp->how_kills  && !(gamechar->abilities & DADA_GAMECHAR_ABILITY_FEED)) {
				return platform_gamechar_die(x, gamechar, gamechar_tmp);
            } else if (gamechar_tmp->abilities & DADA_GAMECHAR_ABILITY_FEED && gamechar_tmp->abilities & DADA_GAMECHAR_ABILITY_DIE && gamechar->user_control > 0 && pos) {
                return platform_gamechar_die(x, gamechar_tmp, gamechar);
            } else if (gamechar->abilities & DADA_GAMECHAR_ABILITY_FEED && gamechar->abilities & DADA_GAMECHAR_ABILITY_DIE && gamechar_tmp->user_control > 0 && pos) {
                return platform_gamechar_die(x, gamechar, gamechar_tmp);
			} else {
				platform_gamechar_handle_obstacle(x, gamechar, pos, (t_dadaitem *)gamechar_tmp);
			} */
		}
	}	
	return 0;
}

long platform_check_gamechar_death(t_platform *x, t_dada_gamechar *gamechar)
{	
	long res = 0;
	if (gamechar->r_it.coord.y < x->die_y_line)
		res |= platform_gamechar_die(x, gamechar, NULL);
	return res;
}

char platform_is_dadaitem_in_screen(t_platform *x, t_dadaitem *item, double pad)
{
	if (is_pt_in_rectangle_tolerance(item->coord, x->displayed_coord, pad))
		return true;
	return false;
}

long platform_gamechar_get_default_movement_state(t_platform *x, t_dada_gamechar *gamechar)
{
    if (gamechar->abilities & DADA_GAMECHAR_ABILITY_WALK)
        return DADA_GAMECHAR_STATE_WALKING;

    if (gamechar->abilities & DADA_GAMECHAR_ABILITY_JUMP)
        return DADA_GAMECHAR_STATE_JUMPING;

    if (gamechar->abilities & DADA_GAMECHAR_ABILITY_FLY)
        return DADA_GAMECHAR_STATE_FLYING;

    if (gamechar->abilities & DADA_GAMECHAR_ABILITY_GLIDE)
        return DADA_GAMECHAR_STATE_GLIDING;

    if (gamechar->abilities & DADA_GAMECHAR_ABILITY_RUN)
        return DADA_GAMECHAR_STATE_RUNNING;
    
    if (gamechar->abilities & DADA_GAMECHAR_ABILITY_SWIM)
        return DADA_GAMECHAR_STATE_SWIMMING;

    return DADA_GAMECHAR_STATE_IDLE;
}

char platform_gamechar_cant_move(t_platform *x, t_dada_gamechar *gamechar)
{
    if (!(gamechar->abilities & (DADA_GAMECHAR_ABILITY_WALK | DADA_GAMECHAR_ABILITY_RUN | DADA_GAMECHAR_ABILITY_JUMP | DADA_GAMECHAR_ABILITY_SWIM | DADA_GAMECHAR_ABILITY_GLIDE | DADA_GAMECHAR_ABILITY_FLY)))
        return true;
    return false;
}

char platform_gamechar_delete(t_platform *x, t_dada_gamechar *gamechar)
{
    return dadaitem_delete_direct(dadaobj_cast(x), (t_dadaitem *)gamechar, 0);
}


t_pt get_direction_unit_vector(long direction)
{
    if (direction & DADA_GAMECHAR_VIA_SIDE_LEFT)
        return build_pt(-1, 0);

    if (direction & DADA_GAMECHAR_VIA_SIDE_RIGHT)
        return build_pt(1, 0);

    if (direction & DADA_GAMECHAR_VIA_SIDE_TOP)
        return build_pt(0, 1);
    
    if (direction & DADA_GAMECHAR_VIA_SIDE_BOTTOM)
        return build_pt(0, -1);
    
    return build_pt(0, 0);
}

long platform_handle_physics_task(t_platform *x)
{
    dadaobj_mutex_lock(dadaobj_cast(x));
    
    t_dada_gamechar *hero = platform_get_hero(x);
	double delta_t = x->b_ob.d_ob.m_play.play_step_ms / 1000.;
    
    // breaking blocks
    t_llllelem *nextbreakingblockelem;
    for (t_llllelem *breakingblockelem = x->breakingblocks->l_head; breakingblockelem; breakingblockelem = nextbreakingblockelem) {
        t_dada_block *block = (t_dada_block *)hatom_getobj(&breakingblockelem->l_hatom);
        t_pt accel = build_pt(0, -x->m_level.gravity);
        nextbreakingblockelem = breakingblockelem->l_next;
        block->broken_slice_speed = pt_pt_sum(block->broken_slice_speed, pt_number_prod(accel, delta_t));
        block->broken_slice_delta_coord = pt_pt_sum(block->broken_slice_delta_coord, pt_number_prod(block->broken_slice_speed, delta_t));
        if (block->r_it.coord.y + block->broken_slice_delta_coord.y < x->die_y_line) {
            block->state = DADA_BLOCK_INVISIBLE;
            llll_destroyelem(breakingblockelem);
        }
    }
    
	
    for (t_llllelem *gamecharelem = x->gamechars->l_head; gamecharelem; gamecharelem = gamecharelem->l_next) {
        t_dada_gamechar *gamechar = (t_dada_gamechar *)hatom_getobj(&gamecharelem->l_hatom);
		
		if (gamechar->r_it.flags & D_INACTIVE || gamechar->state == DADA_GAMECHAR_STATE_DEAD)
			continue;
        
		if (!platform_is_dadaitem_in_screen(x, (t_dadaitem *)gamechar, 1) && gamechar != hero)
			continue;
        
        if (platform_gamechar_cant_move(x, gamechar)) {
            gamechar->state = DADA_GAMECHAR_STATE_IDLE;
            continue;
        }
        
        if (x->play_state == DADA_PLATFORM_PLAYSTATE_DYING && gamechar != x->hero)
            continue;
        
        if (gamechar->state == DADA_GAMECHAR_STATE_GENERATING) {
//            long direction = gamechar->generation_or_portal_direction;
            switch (gamechar->generated_from->type) {
                case DADAITEM_TYPE_BLOCK:
                    if (gamechar->generated_from && gamechar->r_it.coord.y - gamechar->r_it.height/2. < gamechar->generated_from->coord.y + gamechar->generated_from->height/2.) {
                        gamechar->r_it.coord.y += 0.1;
                        continue;
                    } else {
                        gamechar->state = DADA_GAMECHAR_STATE_IDLE;
                        gamechar->speed = rand_range(0, 1) < 0.5 ? build_pt(1, 0) : build_pt(-1, 0);
                    }
                    break;
                    
                default:
                    gamechar->state = DADA_GAMECHAR_STATE_IDLE;
                    gamechar->speed = rand_range(0, 1) < 0.5 ? build_pt(1, 0) : build_pt(-1, 0);
                    break;
            }
        }
        
        if (gamechar->portal && gamechar->state == DADA_GAMECHAR_STATE_ENTERINGPORTAL) {
            long direction = gamechar->generation_or_portal_direction;
            t_pt delta = pt_pt_diff(gamechar->portal->r_it.coord, gamechar->r_it.coord);
            double norm = pt_norm(delta);
            if (norm < 0.001) {
                // done entering
                gamechar->state = DADA_GAMECHAR_STATE_ELSEWHERE;
                parse_instructions(x, gamechar->portal->enter_sequence, (t_dadaitem *)gamechar->portal);
                continue;
            } else {
                gamechar->r_it.coord = pt_pt_sum(gamechar->r_it.coord, pt_number_prod(pt_normalize(delta), MIN(norm, 0.1)));
                continue;
            }
        } else if (gamechar->portal && gamechar->state == DADA_GAMECHAR_STATE_EXITINGPORTAL) {
            long direction = gamechar->portal->how_exit;
            char intersect = platform_do_dadaitems_intersect(x, (t_dadaitem *)gamechar, (t_dadaitem *)gamechar->portal);
            if (!intersect) {
                // done exiting
                gamechar->state = DADA_GAMECHAR_STATE_IDLE;
                parse_instructions(x, gamechar->portal->exit_sequence, (t_dadaitem *)gamechar->portal);
            } else {
                gamechar->r_it.coord = pt_pt_sum(gamechar->r_it.coord, pt_number_prod(get_direction_unit_vector(direction), 0.1));
                continue;
            }
        }

		t_pt old_coord = gamechar->r_it.coord;
		t_pt old_speed = gamechar->speed;
		t_pt new_coord, new_speed;
		t_pt accel = build_pt(0, -x->m_level.gravity);
		
		if (gamechar->type != DADA_GAMECHAR_TYPE_USERCONTROL) { // automatic
            new_speed = pt_pt_sum(old_speed, pt_number_prod(accel, delta_t));
		} else {
			t_pt friction_accel; // friction
			
			// Computing acceleration including friction
			if (gamechar->forced_hdirection)
				friction_accel = build_pt(0, 0); // no friction
            else if (gamechar->on_ground && gamechar->abilities & DADA_GAMECHAR_ABILITY_GLIDE) {
                 friction_accel = build_pt(0, 0); // no friction
                gamechar->state = DADA_GAMECHAR_STATE_GLIDING;
            } else
                friction_accel = build_pt(gamechar->speed.x * (-1) * (gamechar->on_ground ? x->m_level.ground_friction : x->m_level.air_friction), gamechar->speed.y * -1 * x->m_level.air_friction); // air friction is much softer than terrain friction
			
			new_speed = pt_pt_sum(pt_pt_sum(old_speed, pt_number_prod(accel, delta_t)), pt_number_prod(friction_accel, delta_t));
		}
		
		new_coord = pt_pt_sum(old_coord, pt_number_prod(new_speed, delta_t));
		
		gamechar->r_it.coord = new_coord;
		gamechar->speed = new_speed;

		if (!(gamechar->state & DADA_GAMECHAR_STATE_DYING)) {
            if (pt_pt_cmp(old_coord, new_coord)) {
				platform_check_block_collisions(x, gamechar, old_coord);
                if (platform_check_portal_collisions(x, gamechar, old_coord))
                    continue;
            } else
				gamechar->speed = build_pt(0, 0);
			
			if ((fabs(gamechar->speed.x) < 0.2 && fabs(gamechar->speed.y) < 0.2)) {
				gamechar->state = DADA_GAMECHAR_STATE_IDLE;
				gamechar->speed = build_pt(0, 0);
			}
            
            
            // Checking coordinates
            if (gamechar->r_it.coord.x < 0) {
                gamechar->r_it.coord.x = 0;
                gamechar->speed = gamechar->type == DADA_GAMECHAR_TYPE_USERCONTROL ? build_pt(0, 0) : build_pt(-gamechar->speed.x, gamechar->speed.y);
            }
            if (gamechar->r_it.coord.x > x->m_level.level_width) {
                gamechar->r_it.coord.x = x->m_level.level_width;
                gamechar->speed = gamechar->type == DADA_GAMECHAR_TYPE_USERCONTROL ? build_pt(0, 0) : build_pt(-gamechar->speed.x, gamechar->speed.y);
            }
            if (gamechar->r_it.coord.y < 0) {
                gamechar->r_it.coord.y = 0;
                gamechar->speed = gamechar->type == DADA_GAMECHAR_TYPE_USERCONTROL ? build_pt(0, 0) : build_pt(-gamechar->speed.x, gamechar->speed.y);
            }
            if (gamechar->r_it.coord.y > x->m_level.level_height) {
                gamechar->r_it.coord.y = x->m_level.level_height;
                gamechar->speed = gamechar->type == DADA_GAMECHAR_TYPE_USERCONTROL ? build_pt(0, 0) : build_pt(-gamechar->speed.x, gamechar->speed.y);
            }
            
            

			if (pt_pt_cmp(old_coord, gamechar->r_it.coord)) {
				if (x->notify_gamechar_pos) {
					t_llll *notify_ll = llll_get();
					t_llll *coord_ll = llll_get();
					t_llll *speed_ll = llll_get();
					llll_appendsym(notify_ll, gensym("gamechar"), 0, WHITENULL_llll);
					llll_appendsym(notify_ll, gamechar->r_it.name, 0, WHITENULL_llll);
					llll_appendsym(coord_ll, gensym("coord"), 0, WHITENULL_llll);
					llll_appendllll(coord_ll, pt_to_llll(gamechar->r_it.coord, false), 0, WHITENULL_llll);
					llll_appendsym(speed_ll, gensym("speed"), 0, WHITENULL_llll);
					llll_appendllll(speed_ll, pt_to_llll(gamechar->speed, false), 0, WHITENULL_llll);
					llll_appendllll(notify_ll, coord_ll, 0, WHITENULL_llll);
					llll_appendllll(notify_ll, speed_ll, 0, WHITENULL_llll);
					llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, DADA_PLATFORM_NOTIFICATION_OUTLET, notify_ll);
					llll_free(notify_ll);
				}
				
				platform_check_coin_collisions(x, gamechar);
                if (platform_check_gamechar_death(x, gamechar)) {
                    dadaobj_mutex_unlock(dadaobj_cast(x));
                    return 1; // stop for somebody's death
                }
                
                if (!x->only_check_gamechar_collisions_for_user_gamechars || gamechar->type == DADA_GAMECHAR_TYPE_USERCONTROL)
                    if (platform_check_gamechar_collisions(x, gamechar)) {
                        dadaobj_mutex_unlock(dadaobj_cast(x));
						return 1; // stop for somebody's death
                    }
			}
		} else {
            if (gamechar->r_it.coord.y < x->die_y_line - 10) {
                gamechar->state = DADA_GAMECHAR_STATE_DEAD;
                if (gamechar->type != DADA_GAMECHAR_TYPE_USERCONTROL)
                    platform_gamechar_delete(x, gamechar);
            }
		}
	}
	
    dadaobj_mutex_unlock(dadaobj_cast(x));
	jbox_redraw((t_jbox *)x);
	return 0;
}

void push_curtain_up(t_platform *x, t_symbol *s, long ac, t_atom *av)
{
    x->curtain += DADA_PLATFORM_CURTAIN_MOVE_STEP_AMOUNT;
    
    if (x->curtain <= x->m_level.level_height)
        schedule_delay((t_object *)x, (method)push_curtain_up, DADA_PLATFORM_CURTAIN_MOVE_STEP_TIME, NULL, ac, av);
    else {
        x->play_state = atom_getlong(av);
        platform_task(x);
    }
    
    jbox_redraw((t_jbox *)x);
}

void push_curtain_down(t_platform *x, t_symbol *s, long ac, t_atom *av)
{
    x->curtain -= DADA_PLATFORM_CURTAIN_MOVE_STEP_AMOUNT;
    
    if (x->curtain >= 0)
        schedule_delay((t_object *)x, (method)push_curtain_down, DADA_PLATFORM_CURTAIN_MOVE_STEP_TIME, NULL, ac, av);
    else {
        x->play_state = atom_getlong(av);
        platform_task(x);
    }

    jbox_redraw((t_jbox *)x);
}

void set_playstate_fn(t_platform *x, t_symbol *s, long ac, t_atom *av)
{
    x->play_state = atom_getlong(av);
    platform_task(x);
    
    jbox_redraw((t_jbox *)x);
}



void platform_task(t_platform *x)
{
    t_atom av;
    
    // death by time
    if (is_atom_number(&x->m_level.maxtime) && x->global_time > atom_getfloat(&x->m_level.maxtime))
        platform_gamechar_die(x, x->hero, NULL, true);
    
    switch (x->play_state) {
        case DADA_PLATFORM_PLAYSTATE_LEVELINTRO_PRE:
            if (!x->m_level.has_intro)
                x->play_state = DADA_PLATFORM_PLAYSTATE_STANDARD;
            else {
                atom_setlong(&av, DADA_PLATFORM_PLAYSTATE_LEVELINTRO);
                push_curtain_down(x, NULL, 1, &av);
            }
            return; // no physics task handling
            break;
            
        case DADA_PLATFORM_PLAYSTATE_LEVELINTRO:
            atom_setlong(&av, DADA_PLATFORM_PLAYSTATE_LEVELINTRO_POST);
            jbox_invalidate_layer((t_object *)x, NULL, gensym("game"));
            schedule_delay((t_object *)x, (method)set_playstate_fn, DADA_PLATFORM_INTRO_TIME, NULL, 1, &av);
            return; // no physics task handling
            break;

        case DADA_PLATFORM_PLAYSTATE_LEVELINTRO_POST:
            if (!x->m_level.has_intro)
                x->play_state = DADA_PLATFORM_PLAYSTATE_STANDARD;
            else {
                t_atom av;
                atom_setlong(&av, DADA_PLATFORM_PLAYSTATE_STANDARD);
                push_curtain_up(x, NULL, 1, &av);
            }
            return; // no physics task handling
            break;

        case DADA_PLATFORM_PLAYSTATE_DYING:
            atom_setlong(&av, DADA_PLATFORM_PLAYSTATE_STANDARD);
            schedule_delay((t_object *)x, (method)set_playstate_fn, DADA_PLATFORM_INTRO_TIME, NULL, 1, &av);
            break;
            
        case DADA_PLATFORM_PLAYSTATE_END_GAMEOVER_PRE:
            atom_setlong(&av, DADA_PLATFORM_PLAYSTATE_END_GAMEOVER);
            push_curtain_down(x, NULL, 1, &av);
            return; // no physics task handling
            break;
            
        case DADA_PLATFORM_PLAYSTATE_END_WIN_PRE:
            atom_setlong(&av, DADA_PLATFORM_PLAYSTATE_END_WIN);
            push_curtain_down(x, NULL, 1, &av);
            return; // no physics task handling
            break;

        default:
            x->global_time += x->b_ob.d_ob.m_play.play_step_ms;
            break;
    }
    
    // game physics engine
	if (!platform_handle_physics_task(x))
		setclock_fdelay(x->b_ob.d_ob.m_play.setclock->s_thing, x->b_ob.d_ob.m_play.m_clock, x->b_ob.d_ob.m_play.play_step_ms);
}


void platform_check_autozoom(t_platform *x)
{
    if (x->autozoom)
        dadaobj_setrange(dadaobj_cast(x), jpatcher_get_firstview((t_object *)gensym("#P")->s_thing), 0, x->m_level.level_height);
}

long platform_oksize(t_platform *x, t_rect *newrect)
{
    platform_check_autozoom(x);
    
    return 0;
}




void load_resources(t_dada_platform_resources *resources, void *moduleRef)
{
    resources->surface_block = jgraphics_image_surface_create_from_resource(moduleRef, "icon_block");
    resources->surface_coin = jgraphics_image_surface_create_from_resource(moduleRef, "icon_coin");
    resources->surface_gamechar = jgraphics_image_surface_create_from_resource(moduleRef, "icon_gamechar");
    resources->surface_level = jgraphics_image_surface_create_from_resource(moduleRef, "icon_level");
    resources->surface_portal = jgraphics_image_surface_create_from_resource(moduleRef, "icon_portal");
}

void free_resources(t_dada_platform_resources *resources)
{
    // THIS FUNCTION IS NEVER CALLED; we know: since we loaded the resources in the main() cycle, the resources are NEVER released - until you close Max
    if (resources->surface_block)
        jgraphics_surface_destroy(resources->surface_block);
    if (resources->surface_coin)
        jgraphics_surface_destroy(resources->surface_coin);
    if (resources->surface_gamechar)
        jgraphics_surface_destroy(resources->surface_gamechar);
    if (resources->surface_level)
        jgraphics_surface_destroy(resources->surface_level);
    if (resources->surface_portal)
        jgraphics_surface_destroy(resources->surface_portal);
}

t_dada_sprite *get_default_sprite(t_platform *x, t_dadaitem *item)
{
    t_symbol *sprite_sym = NULL;
    switch (item->type) {
        case DADAITEM_TYPE_GAMECHAR:
            if (!sprite_sym) sprite_sym = ((t_dada_gamechar *)item)->sprite_idle;
            if (!sprite_sym) sprite_sym = ((t_dada_gamechar *)item)->sprite_walk;
            if (!sprite_sym) sprite_sym = ((t_dada_gamechar *)item)->sprite_jump;
            if (!sprite_sym) sprite_sym = ((t_dada_gamechar *)item)->sprite_glide;
            if (!sprite_sym) sprite_sym = ((t_dada_gamechar *)item)->sprite_fly;
            if (!sprite_sym) sprite_sym = ((t_dada_gamechar *)item)->sprite_dead;
            break;

        case DADAITEM_TYPE_BLOCK:
            if (!sprite_sym) sprite_sym = ((t_dada_block *)item)->sprite;
            break;

        case DADAITEM_TYPE_COIN:
            if (!sprite_sym) sprite_sym = ((t_dada_coin *)item)->sprite;
            break;

        case DADAITEM_TYPE_PORTAL:
            if (!sprite_sym) sprite_sym = ((t_dada_portal *)item)->sprite;
            break;

        case DADAITEM_TYPE_LEVEL:
            if (!sprite_sym) sprite_sym = ((t_levelinfo *)item)->background_sprite;
            break;

        default:
            break;
    }
    
    if (sprite_sym)
        return label_to_sprite(x, sprite_sym);
    
    return NULL;
}

t_jsurface *get_default_jsurface(t_platform *x, t_dadaitem *item)
{
    t_dada_sprite *spr = get_default_sprite(x, item);
    if (spr && spr->num_slides > 0)
        return spr->slide_right[0];
    return NULL;
}


t_jsurface *platform_inspector_get_icon_surface_fn(t_object *r_ob, t_bach_inspector_manager *man, void *obj, long elem_type)
{
    t_dadaitem *item = (t_dadaitem *)obj;
    t_platform *x = (t_platform *)man->owner;
    if (item) {
        return get_default_jsurface(x, item);
    }
    
    t_dada_platform_resources *resources = (t_dada_platform_resources *)gensym("dadaplatformresources")->s_thing;
    if (resources) {
        if (elem_type >= 0 && elem_type < x->b_ob.d_ob.m_classes.num_di_classes) {
            switch (x->b_ob.d_ob.m_classes.di_class[elem_type].type) {
                case DADAITEM_TYPE_BLOCK: return resources->surface_block;
                case DADAITEM_TYPE_GAMECHAR: return resources->surface_gamechar;
                case DADAITEM_TYPE_COIN: return resources->surface_coin;
                case DADAITEM_TYPE_PORTAL: return resources->surface_portal;
                case DADAITEM_TYPE_LEVEL: return resources->surface_level;
                default: return NULL;
            }
        }
    }
    return NULL;
}

