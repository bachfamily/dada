/**
	@file
	dada.stage.c
	
	@name
	dada.stage
	
	@realname 
	dada.stage

	@type
	object
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
	Spatial mixer representation
	
	@description
	Interface for spatializing labels and icons, with mixing tools
	
	@discussion
 
	@category
	dada interfaces, dada geometry

	@keywords
	stage, spat, spatialization, label, text, icon, orchestra, instrument, mixer, mix
	
	@seealso
	bach.wordcloud
	
	@owner
	Daniele Ghisi
*/



#include "dada.interface.h"
#include "dada.geometry.h"
#include "dada.paint.h"
#include "notation/notation.h"
//#include "dada.cursors.data.c"
#include "dada.math.h"
#include "dada.graphs.h"
#include "dada.popupmenu.h"
#include "dada.undo.h"

#define DADA_STAGE_MAX_CARDS 64			///< Maximum number of cards allowed
///  Must be less than or equal to 64 (otherwise change the #t_stage_bitfield declaration) 

#define DADA_BOUNCE_ROTATION_INTERFACE_FACTOR (2 * TWO_PI)
#define DADA_BOUNCE_ROTATION_SCALE_FACTOR 100.

#define DADA_BOUNCE_CARD_SELECTION_PAD 4

#define DADA_BOUNCE_NOTEPOPUP_WIDTH 50
#define DADA_BOUNCE_NOTEPOPUP_HEIGHT 70

#define DADA_STAGE_CARD_HEIGHT 90 
#define DADA_STAGE_CARD_WIDTH 60


typedef t_uint64 t_stage_bitfield;		///< A bitfield with each bit corresponding to a bouncing ball


////////////////////////// structures



typedef enum _stage_text_valignment
{
	DADA_STAGE_TEXT_VALIGN_TOP = 0,
	DADA_STAGE_TEXT_VALIGN_MIDDLE = 1,
	DADA_STAGE_TEXT_VALIGN_BOTTOM = 2,
	DADA_STAGE_TEXT_VALIGN_ABOVE = 3,
	DADA_STAGE_TEXT_VALIGN_BELOW = 4,
} e_stage_text_valignment;

typedef enum _stage_text_halignment
{
	DADA_STAGE_TEXT_HALIGN_LEFT = 0,
	DADA_STAGE_TEXT_HALIGN_CENTER = 1,
	DADA_STAGE_TEXT_HALIGN_RIGHT = 2,
} e_stage_text_halignment;

typedef struct _collision
{
	long	edge_idx;
	t_pt	collision_pt;
} t_collision;



typedef struct _stage 
{
	t_dadaobj_jbox		b_ob; // root object
	
	// cards
	t_dada_card			*cards;
	
	// settings
	double			value_min;
	double			value_max;
	
	// display
	char			show_text;
	char			show_icons;
	char			show_faders;
	char			show_value;
	long			num_decimal_digits;
	double			faderslope;
	
	double			cardborder_width;
	
	char			text_valign;
	char			text_halign;

	t_jrgba			j_cardbordercolor;
	t_jrgba			j_textcolor;
	t_jrgba			j_fadercolor;
	t_jrgba			j_trianglecolor;
	t_jrgba			j_valuecolor;
	
	char			allow_deletion;
	
	// utilities
	char			firsttime;
	char			itsme;
	char			creating_new_obj;
	
	long			n_in;   // space for the inlet number used by all the proxies
    void			*n_proxy1;
	
	// outlets are declared in the dadaobj->llllobj structure, at the beginning
} t_stage;



///////////////////////// function prototypes
//// standard set
void *stage_new(t_symbol *s, long argc, t_atom *argv);
void stage_free(t_stage *x);
void stage_assist(t_stage *x, void *b, long m, long a, char *s);

void stage_paint(t_stage *x, t_object *view);
void stage_paint_ext(t_stage *x, t_object *view, t_dada_force_graphics *force_graphics);


void stage_int(t_stage *x, t_atom_long num);
void stage_float(t_stage *x, double num);
void stage_anything(t_stage *x, t_symbol *msg, long ac, t_atom *av);
//void stage_bang(t_stage *x);


// get/set status
void stage_set_state(t_stage *x, t_llll *state);
t_llll *stage_get_state_sel(t_stage *x, char get_stage, char get_testers);
t_llll *stage_get_state(t_stage *x);

t_llll *stage_get_cards(t_stage *x);
void stage_set_cards(t_stage *x, t_llll *shapes);


// interface
void stage_focusgained(t_stage *x, t_object *patcherview);
void stage_focuslost(t_stage *x, t_object *patcherview);
void stage_mousedown(t_stage *x, t_object *patcherview, t_pt pt, long modifiers);
void stage_mousemove(t_stage *x, t_object *patcherview, t_pt pt, long modifiers);
void stage_mouseup(t_stage *x, t_object *patcherview, t_pt pt, long modifiers);
void stage_mousedrag(t_stage *x, t_object *patcherview, t_pt pt, long modifiers);
long stage_key(t_stage *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
long stage_keyup(t_stage *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
void stage_mousewheel(t_stage *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc);

void stage_mouseenter(t_stage *x, t_object *patcherview, t_pt pt, long modifiers);
void stage_mouseleave(t_stage *x, t_object *patcherview, t_pt pt, long modifiers);

t_max_err stage_notify(t_stage *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void stage_jsave(t_stage *x, t_dictionary *d);
void stage_preset(t_stage *x);
void stage_begin_preset(t_stage *x, t_symbol *s, long argc, t_atom *argv);
void stage_restore_preset(t_stage *x, t_symbol *s, long argc, t_atom *argv);
void stage_end_preset(t_stage *x);

t_max_err stage_setattr_tonedivision(t_stage *x, t_object *attr, long ac, t_atom *av);

// UNDO
void stage_undo_step_push_cards(t_stage *x, t_symbol *operation);
void stage_postprocess_undo(t_stage *x);

void stage_relocate_cards(t_stage *x, t_symbol *msg, long ac, t_atom *av);




////////////////////// INTERFACE FOR DADA ITEMS


///// CARDS:

void postprocess_card(t_stage *x)
{
	jbox_redraw((t_jbox *)x);
}


// returns the new ball index if succesful, -1 otherwise
long duplicate_card(t_stage *x, long idx)
{
/*	stage_undo_step_push_balls(x, gensym("Duplicate Ball"));
	long newidx = dadaitem_ball_duplicate(dadaobj_cast(x), idx, 0);
	if (newidx >= 0) {
		t_dada_ball *ball = (t_dada_ball *)dadaitem_from_type_and_idx(dadaobj_cast(x), DADAITEM_TYPE_BALL, newidx);
		if (ball) {
			ball->speed = x->balls[idx].speed;
			ball->channel = dadaitem_ball_find_max_channel(dadaobj_cast(x)) + 1;
			ball->r_it.color = dada_long_to_color(dadaitem_class_get_num_items(dadaobj_cast(x), DADAITEM_TYPE_BALL) - 1);
		}
	} 
	return newidx; */
	return 0;
}


void postprocess_cards(t_dadaobj *d_ob)
{
	jbox_redraw((t_jbox *)d_ob->orig_obj);
}




//////////////////////// global class pointer variable
t_class *stage_class;

int C74_EXPORT main(void)
{	
	t_class *c;
	
	common_symbols_init();
	llllobj_common_symbols_init();
	
	if (dada_check_bach_version() || llllobj_test()) {
		dada_error_bachcheck();
		return 1;
	}
	
	
	CLASS_NEW_CHECK_SIZE(c, "dada.stage", (method)stage_new, (method)stage_free, (long)sizeof(t_stage), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, 0);	// include textfield and Fonts attributes
	//	jbox_initclass(c, 0);
	
	// paint & utilities
	class_addmethod(c, (method) stage_paint,			"paint", A_CANT, 0);
	class_addmethod(c, (method) stage_assist,			"assist",		A_CANT, 0);  
	class_addmethod(c, (method)	stage_notify,			"bachnotify",		A_CANT,		0);
	
	// save & preset
    class_addmethod(c, (method) stage_preset, "preset", 0);
    class_addmethod(c, (method) stage_begin_preset, "begin_preset", A_GIMME, 0);
    class_addmethod(c, (method) stage_restore_preset, "restore_preset", A_GIMME, 0);
    class_addmethod(c, (method) stage_end_preset, "end_preset", 0);
	CLASS_METHOD_ATTR_PARSE(c, "begin_preset", "undocumented", gensym("long"), 0L, "1");
	CLASS_METHOD_ATTR_PARSE(c, "restore_preset", "undocumented", gensym("long"), 0L, "1");
	CLASS_METHOD_ATTR_PARSE(c, "end_preset", "undocumented", gensym("long"), 0L, "1");
	class_addmethod(c, (method) stage_jsave, "jsave", A_CANT, 0);
	
	// interface
	class_addmethod(c, (method) stage_focusgained, "focusgained", A_CANT, 0);
	class_addmethod(c, (method) stage_focuslost, "focuslost", A_CANT, 0);
    
    // @method (mouse) @digest Edit content
    // @description
    // @copy DADA_DOC_MOUSE_COMMANDS_STANDARD_NAVIGATION
    // Specific commands: <br />
    // • <m>click+drag</m>: move cards<br />
    // • <m>Cmd+click</m> (mac) or <m>Ctrl+click</m> (win) on a card to delete it<br />
    // • <m>Ctrl+click+drag</m> (mac) or <m>Shift+Ctrl+click+drag</m> (win): change card value<br />
	class_addmethod(c, (method) stage_mousedown, "mousedown", A_CANT, 0);
	class_addmethod(c, (method) stage_mousedrag, "mousedrag", A_CANT, 0);
	class_addmethod(c, (method) stage_mouseup, "mouseup", A_CANT, 0);

    // @method (keyboard) @digest Undo/Redo
    // @description
    // @copy DADA_DOC_KEYBOARDS_COMMANDS_STANDARD_NAVIGATION
    // • <m>Cmd+Z</m> (mac) or <m>Ctrl+Z</m> (win): perform undo step<br />
    // • <m>Cmd+Shift+Z</m> (mac) or <m>Ctrl+Y</m> (win): perform redo step<br />
    class_addmethod(c, (method) stage_key, "key", A_CANT, 0);
  	class_addmethod(c, (method) stage_keyup, "keyup", A_CANT, 0);
    
    // @method (tools) @digest Navigate
    // @description
    // @copy DADA_DOC_TOOLS_INTRO
    // @copy DADA_DOC_TOOLS_ZX
	class_addmethod(c, (method) stage_mousemove, "mousemove", A_CANT, 0);
	class_addmethod(c, (method) stage_mouseenter, "mouseenter", A_CANT, 0);
	class_addmethod(c, (method) stage_mouseleave, "mouseleave", A_CANT, 0);
	class_addmethod(c, (method) stage_mousewheel, "mousewheel", A_CANT, 0);
	class_addmethod(c, (method) stage_anything,	"move",		A_GIMME,	0);

	// @method relocate @digest Relocate images
	// @description The word <m>relocate</m> followed the symbol of a new image folder path, relocates all images in such folder.
	class_addmethod(c, (method)stage_relocate_cards,	"relocate",		A_GIMME,	0);
	
    // @method dump @digest Output state
    // @description Outputs the current state of the object. The syntax is
    // <b>stage [cards <m>CARD1</m> <m>CARD2</m>...]</b>,
    // each card being
    // <b>(coord <m>x</m> <m>y</m>) (speed <m>x</m> <m>y</m>) (color <m>r</m> <m>g</m> <m>b</m> <m>a</m>)
    // (channel <m>MIDIchannel</m>) (flags <m>flags</m>)</b>. <br />
    // A first argument limits the elements to be dumped.
    // The <m>dump room</m> message only dumps the room state; the <m>dump balls</m> message only dumps the balls state. <br />
    // @copy DADA_DOC_SYNTAX_GRAPH
    // @copy DADA_DOC_SYNTAX_FLAGS
    // @marg 0 @name what @optional 1 @type symbol
    class_addmethod(c, (method)stage_anything,	"dump",			A_GIMME,	0);
    
    
    // @method addcards @digest Add cards
    // @description Adds some cards to the existing stage. The <m>addcards</m> symbol must be followed by a sequence of lllls
    // <b><m>CARD1</m> <m>CARD2</m>...</b> whose syntax is the one explained in the <m>dump</m> message.
    class_addmethod(c, (method)stage_anything,	"addcards",			A_GIMME,	0);

    // @method deletecards @digest Delete cards
    // @description Deletes some cards to the existing stage. The <m>deletecards</m> symbol must be followed by a sequence of symbols,
    // each identifying the name of a card to be deleted.
    class_addmethod(c, (method)stage_anything,	"deletecards",			A_GIMME,	0);
    
    // @method clear @digest Clear stage
    // @description Clears all the cards on the stage.
    class_addmethod(c, (method)stage_anything,	"clear",			A_GIMME,	0);

    
    // @method llll @digest Set state
    // @description Sets the current state of the object. The syntax must follow the one described in the
    // <m>dump</m> message documentation.
	class_addmethod(c, (method)stage_anything,	"anything",			A_GIMME,	0);
    class_addmethod(c, (method)stage_anything,	"setstoredstate",	A_GIMME, 0);
	
    
    
    // @method domain @digest Set the X domain
    // @description The <m>domain</m> message, followed by two numbers, sets minimum and maximum coordinates
    // to be displayed on the X axis.
    // The <m>domain</m> message,  followed by the "start" or "end" symbol and a number, sets the coordinate
    // to be displayed respectively at the left boundary or at the right boundary of the object box.
    // @marg 0 @name arguments @optional 0 @type list
    class_addmethod(c, (method)stage_anything,		"domain",		A_GIMME,	0);
    
    // @method range @digest Set the Y range
    // @description The <m>range</m> message, followed by two numbers, sets minimum and maximum coordinates
    // to be displayed on the Y axis
    // The <m>range</m> message,  followed by the "start" or "end" symbol and a number, sets the coordinate
    // to be displayed respectively at the bottom boundary or at top right boundary of the object box.
    // @marg 0 @name arguments @optional 0 @type list
    class_addmethod(c, (method)stage_anything,		"range",		A_GIMME,	0);

    
    // @method getdomain @digest Retrieve current X domain
    // @description The <m>getdomain</m> message outputs from the third outlet the minimum and maximum
    // coordinates displayed on the X axis, preceded by a <m>domain</m> symbol.
    class_addmethod(c, (method)stage_anything,		"getdomain",		A_GIMME,	0);
    
    
    // @method getrange @digest Retrieve current Y range
    // @description The <m>getrange</m> message outputs from the third outlet the minimum and maximum
    // coordinates displayed on the Y axis, preceded by a <m>range</m> symbol.
    class_addmethod(c, (method)stage_anything,		"getrange",		A_GIMME,	0);
    
    DADAOBJ_JBOX_DECLARE_READWRITE_METHODS(c);
    DADAOBJ_JBOX_DECLARE_IMAGE_METHODS(c);
    DADAOBJ_JBOX_DECLARE_ACCEPTSDRAG_METHODS(c);

	llllobj_class_add_out_attr(c, LLLL_OBJ_UI);
	dadaobj_class_init(c, LLLL_OBJ_UI, DADAOBJ_BBGIMAGE | DADAOBJ_ZOOM | DADAOBJ_CENTEROFFSET | DADAOBJ_UNDO | DADAOBJ_EMBED | DADAOBJ_MOUSEHOVER | DADAOBJ_GRID | DADAOBJ_LABELS | DADAOBJ_AXES | DADAOBJ_NOTIFICATIONS | DADAOBJ_EXPORTTOJITTER);
	
	CLASS_ATTR_DEFAULT(c, "patching_rect", 0, "0 0 300 300");
	// @exclude dada.stage
	CLASS_ATTR_DEFAULT(c, "presentation_rect", 0, "0 0 300 300");
	// @exclude dada.stage
	
	
	CLASS_STICKY_ATTR(c,"category",0,"Color");
	
	CLASS_ATTR_RGBA(c, "textcolor", 0, t_stage, j_textcolor);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "textcolor", 0, "0.1 0.1 0.1 1.");
	CLASS_ATTR_STYLE_LABEL(c, "textcolor", 0, "rgba", "Text Color");
	CLASS_ATTR_BASIC(c, "textcolor", 0);
	// @description Color of the bouncing room
	
	CLASS_ATTR_RGBA(c, "fadercolor", 0, t_stage, j_fadercolor);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "fadercolor", 0, "0.1 0.1 0.1 1.");
	CLASS_ATTR_STYLE_LABEL(c, "fadercolor", 0, "rgba", "Fader Color");
	// @description Color of card faders

	CLASS_ATTR_RGBA(c, "trianglecolor", 0, t_stage, j_trianglecolor);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "trianglecolor", 0, "0.8 0. 0. 1.");
	CLASS_ATTR_STYLE_LABEL(c, "trianglecolor", 0, "rgba", "Fader Triangle Color");
	// @description Color of triangle of mixer faders

	CLASS_ATTR_RGBA(c, "valuecolor", 0, t_stage, j_valuecolor);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "valuecolor", 0, "0.1 0.1 0.1 1.");
	CLASS_ATTR_STYLE_LABEL(c, "valuecolor", 0, "rgba", "Value Text Color");
	// @description Color of text of card value
	
	CLASS_ATTR_RGBA(c, "cardbordercolor", 0, t_stage, j_cardbordercolor);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "cardbordercolor", 0, "0.2 0.2 0.2 1.");
	CLASS_ATTR_STYLE_LABEL(c, "cardbordercolor", 0, "rgba", "Card Border Color");
	// @description Color of the border of each card
	
	CLASS_STICKY_ATTR_CLEAR(c, "category");
	
	
	
	CLASS_STICKY_ATTR(c,"category",0,"Behavior");

	CLASS_ATTR_CHAR(c, "allowdeletion", 0, t_stage, allow_deletion);
    CLASS_ATTR_STYLE_LABEL(c, "allowdeletion", 0, "onoff", "Allow Card Deletion");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"allowdeletion",0,"1");
	
	CLASS_STICKY_ATTR_CLEAR(c, "category");
	
	
	CLASS_STICKY_ATTR(c,"category",0,"Settings");
	
	CLASS_ATTR_DOUBLE(c, "minimum", 0, t_stage, value_min);
    CLASS_ATTR_STYLE_LABEL(c, "minimum", 0, "text", "Minimum Card Value");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"minimum",0,"0");

	CLASS_ATTR_DOUBLE(c, "maximum", 0, t_stage, value_max);
    CLASS_ATTR_STYLE_LABEL(c, "maximum", 0, "text", "Maximum Card Value");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"maximum",0,"1");
	
	CLASS_ATTR_LONG(c, "numdigits", 0, t_stage, num_decimal_digits);
    CLASS_ATTR_STYLE_LABEL(c, "numdigits", 0, "text", "Number Of Displayed Value Decimal Digits");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"numdigits",0,"2");
	
	CLASS_STICKY_ATTR_CLEAR(c, "category");
	
	
	CLASS_STICKY_ATTR(c,"category",0,"Appearance");
	
	CLASS_ATTR_CHAR(c, "showtext", 0, t_stage, show_text);
    CLASS_ATTR_STYLE_LABEL(c, "showtext", 0, "onoff", "Show Text");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showtext",0,"1");

	CLASS_ATTR_CHAR(c, "textvalign", 0, t_stage, text_valign);
    CLASS_ATTR_STYLE_LABEL(c, "textvalign", 0, "enumindex", "Text Vertical Alignment");
	CLASS_ATTR_ENUMINDEX(c,"textvalign", 0, "Top Middle Bottom Above Below"); 
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"textvalign",0,"2");

	CLASS_ATTR_CHAR(c, "texthalign", 0, t_stage, text_halign);
    CLASS_ATTR_STYLE_LABEL(c, "texthalign", 0, "enumindex", "Text Horizontal Alignment");
	CLASS_ATTR_ENUMINDEX(c,"texthalign", 0, "Left Center Right"); 
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"texthalign",0,"1");
	
	CLASS_ATTR_CHAR(c, "showicons", 0, t_stage, show_icons);
    CLASS_ATTR_STYLE_LABEL(c, "showicons", 0, "onoff", "Show Icons");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showicons",0,"1");

	CLASS_ATTR_CHAR(c, "showfaders", 0, t_stage, show_faders);
    CLASS_ATTR_STYLE_LABEL(c, "showfaders", 0, "onoff", "Show Faders");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showfaders",0,"1");

	CLASS_ATTR_CHAR(c, "showvalue", 0, t_stage, show_value);
    CLASS_ATTR_STYLE_LABEL(c, "showvalue", 0, "onoff", "Show Card Value");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showvalue",0,"1");
	
	CLASS_ATTR_DOUBLE(c, "cardborder", 0, t_stage, cardborder_width);
    CLASS_ATTR_STYLE_LABEL(c, "cardborder", 0, "text", "Card Border Width");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"cardborder",0,"0");

	CLASS_ATTR_DOUBLE(c, "slope", 0, t_stage, faderslope);
    CLASS_ATTR_STYLE_LABEL(c, "slope", 0, "text", "Fader Slope Mapping");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"slope",0,"0.");
	
	CLASS_STICKY_ATTR_CLEAR(c, "category");
	
	
	
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	stage_class = c;
	
	dev_post("dada.stage compiled %s %s", __DATE__, __TIME__);
	return 0;
}

t_max_err stage_notify(t_stage *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	if (msg == _sym_attr_modified) {
		t_symbol *attr_name = (t_symbol *)object_method((t_object *)data, _sym_getname);
		if (attr_name == _llllobj_sym_zoom || attr_name == gensym("center")) {
			jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
			jbox_redraw((t_jbox *)x);
		} else if (attr_name == gensym("grid")) {
			jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
			jbox_redraw((t_jbox *)x);
		}
	}
	
	return MAX_ERR_NONE;
}

void stage_begin_preset(t_stage *x, t_symbol *s, long argc, t_atom *argv)
{
	dadaobj_begin_preset(dadaobj_cast(x), s, argc, argv);
}


void stage_restore_preset(t_stage *x, t_symbol *s, long argc, t_atom *argv)
{
	dadaobj_restore_preset(dadaobj_cast(x), s, argc, argv);
}

void stage_end_preset(t_stage *x)
{
	dadaobj_end_preset(dadaobj_cast(x));
}

void stage_preset(t_stage *x) {
	dadaobj_preset(dadaobj_cast(x));
}


void stage_jsave(t_stage *x, t_dictionary *d)
{
	if (x->b_ob.d_ob.save_data_with_patcher){
		if (x->b_ob.r_ob.l_dictll) {
			llll_store_in_dictionary(x->b_ob.r_ob.l_dictll, d, "stage_data", NULL);
		} else {
			t_llll *data = stage_get_state(x);
			llll_store_in_dictionary(data, d, "stage_data", NULL);
			llll_free(data);
		}
	} 
}


t_llll *stage_get_single_card(t_stage *x, long idx)
{
	t_llll *ll = llll_get();
	llll_appendllll(ll, symbol_and_llll_to_llll_chained(gensym("coord"), pt_to_llll(x->cards[idx].r_it.coord, false)));
	llll_appendllll(ll, symbol_and_symbol_to_llll(gensym("name"), x->cards[idx].text), 0, WHITENULL_llll);
	llll_appendllll(ll, symbol_and_double_to_llll(gensym("value"), x->cards[idx].value), 0, WHITENULL_llll);
	llll_appendllll(ll, symbol_and_symbol_to_llll(gensym("icon"), x->cards[idx].icon_path), 0, WHITENULL_llll);
    llll_appendllll(ll, symbol_and_double_to_llll(gensym("height"), x->cards[idx].r_it.height), 0, WHITENULL_llll);
    llll_appendllll(ll, symbol_and_double_to_llll(gensym("width"), x->cards[idx].r_it.width), 0, WHITENULL_llll);
	dadaitem_append_flags_to_llll(ll, (t_dadaitem*)(&x->cards[idx]), false);
	return ll;
}

t_llll *stage_get_cards(t_stage *x)
{
	long i;
	t_llll *out_ll = llll_get();
	long num_cards = dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_CARD);
	for (i = 0; i < num_cards; i++) 
		llll_appendllll(out_ll, stage_get_single_card(x, i), 0, WHITENULL_llll);
	llll_prependsym(out_ll, gensym("cards"), 0, WHITENULL_llll);
	return out_ll;
}


t_llll *stage_get_state_sel(t_stage *x, char get_cards)
{
	t_llll *data = llll_get();
	
    llll_appendsym(data, gensym("stage"));
    
	if (get_cards)
		llll_appendllll(data, stage_get_cards(x), 0, WHITENULL_llll);
	
	return data;
}

t_llll *stage_get_state(t_stage *x)
{
	return stage_get_state_sel(x, true);
}


void stage_iar(t_stage *x)
{
    jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
    jbox_redraw((t_jbox *)x);
}


void stage_delete_cards(t_stage *x, t_llll *cards)
{
    long i;
    t_llllelem *elem;
    for (elem = cards->l_head; elem; elem = elem->l_next) {
        if (hatom_gettype(&elem->l_hatom) == H_SYM) {
            t_symbol *name = hatom_getsym(&elem->l_hatom);
            long num_cards = dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_CARD);
            for (i = 0; i < num_cards; i++)
                if (x->cards[i].text == name) {
                    dadaitem_card_delete(dadaobj_cast(x), i, 0);
                    break;
                }
        }
    }
    stage_iar(x);
}

void stage_add_cards(t_stage *x, t_llll *cards)
{
    long i;
    t_llllelem *elem;
    for (i = 0, elem = cards->l_head; elem && i < DADA_STAGE_MAX_CARDS; elem = elem->l_next, i++) {
        if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
            t_llll *ll = hatom_getllll(&elem->l_hatom);
            t_pt coord = build_pt(0, 0);
            t_symbol *text = NULL, *iconpath = NULL;
            double value = 0;
            double height = -1;
            double width = -1;
            long flags = 0;
            dadaobj_parseargs(dadaobj_cast(x), ll, (char *)"PsdsddF", gensym("coord"), &coord, gensym("name"), &text, gensym("value"), &value, gensym("icon"), &iconpath, gensym("height"), &height, gensym("width"), &width, gensym("flags"), &flags);
            dadaitem_card_add(dadaobj_cast(x), coord, width, height, DADA_BLACK, text, iconpath, value, flags, 0);
        }
    }
    
    stage_iar(x);
}

void stage_set_cards(t_stage *x, t_llll *cards)
{
	dadaitem_card_clear(dadaobj_cast(x), 0);
    stage_add_cards(x, cards);


/* 
    for (i = 0, elem = cards->l_head ? cards->l_head->l_next : NULL; elem && i < DADA_STAGE_MAX_CARDS; elem = elem->l_next, i++) {
        if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
			t_llll *ll = hatom_getllll(&elem->l_hatom);
			t_pt coord = build_pt(0, 0);
			t_symbol *text = NULL, *iconpath = NULL;
			double value = 0;
			long flags = 0;
			t_pt height_and_width = build_pt(0, 0);
			dadaobj_parse_llll(dadaobj_cast(x), ll, (char *)"PsdsPF", &coord, &text, &value, &iconpath, &height_and_width, &flags);
			dadaitem_card_add(dadaobj_cast(x), coord, height_and_width.x, height_and_width.y, DADA_BLACK, text, iconpath, value, flags, 0);
		}
	}*/
}


// see stage_get_state about the codification of info
void stage_set_state(t_stage *x, t_llll *state)
{
	x->itsme = true;
	
    t_llllelem *el;
    for (el = state->l_head; el; el = el->l_next) {
        if (hatom_gettype(&el->l_hatom) == H_LLLL) {
            t_llll *ll = hatom_getllll(&el->l_hatom);
            if (ll && ll->l_head && hatom_gettype(&ll->l_head->l_hatom) == H_SYM) {
                t_symbol *router = hatom_getsym(&ll->l_head->l_hatom);
                if (router == gensym("cards"))
                    stage_set_cards(x, ll);
            }
        }
    }
    
	x->itsme = false;
	
	postprocess_cards(dadaobj_cast(x));
}



void stage_iterator_fn(t_stage *x, dadaitem_iterfn iterator_fn, void *data)
{
	long i;
	long num_cards = dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_CARD);
	for (i = 0; i < num_cards; i++)
		if (iterator_fn(dadaobj_cast(x), (t_dadaitem *)&x->cards[i], data))
			return;
}





void stage_assist(t_stage *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type anything @digest Incoming symbol or list
		sprintf(s, "Incoming symbol or list");
	} 
	else {	
		if (a == 0)	// @out 0 @type llll @digest Dump outlet
			sprintf(s, "Dump Outlet"); 			
		else if (a == 1)	// @out 1 @type llll @digest Queries and notifications
			sprintf(s, "Queries and Notifications"); 			
		else 	// @out 2 @type bang @digest bang when object is changed via the interface
			sprintf(s, "bang when Changed"); 			
	}
}

void card_free(t_dadaobj *r_ob, t_dadaitem *item, void *data)
{
    t_dada_card *card = (t_dada_card *)item;
    if (card->icon_surface)
        jgraphics_surface_destroy(card->icon_surface);
}

void stage_free(t_stage *x)
{
	object_free_debug(x->n_proxy1);
	dadaobj_jbox_free((t_dadaobj_jbox *)x); // jbox_free and llllobj_free are inside here
}


void *stage_new(t_symbol *s, long argc, t_atom *argv)
{
	t_stage *x = NULL;
	t_dictionary *d = NULL;
	long boxflags;
	t_llll *llll_for_rebuild = NULL;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;    
	
	if ((x = (t_stage *)object_alloc_debug(stage_class))) {
		
		x->creating_new_obj = true;
		
		x->b_ob.d_ob.m_tools.curr_tool = DADA_TOOL_ARROW;
		x->firsttime = true;
		x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
		
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
		
        dadaobj_jbox_setup((t_dadaobj_jbox *)x, DADAOBJ_BBGIMAGE | DADAOBJ_ZOOM | DADAOBJ_CENTEROFFSET | DADAOBJ_UNDO | DADAOBJ_CHANGEDBANG | DADAOBJ_NOTIFICATIONS, build_pt(1., 1.), -1, 2, 1, (dada_paint_ext_fn)stage_paint_ext, (invalidate_and_redraw_fn)stage_iar, "", 2, "b44");
		dadaobj_addfunctions(dadaobj_cast(x), (dada_mousemove_fn)stage_mousemove, NULL, (method)stage_postprocess_undo, (get_state_fn)stage_get_state, (set_state_fn)stage_set_state, NULL, NULL, NULL);

		dadaobj_dadaitem_class_alloc(dadaobj_cast(x), DADAITEM_TYPE_CARD, gensym("card"), gensym("Card"), DADA_ITEM_ALLOC_ARRAY, 0, false, sizeof(t_dada_card), calcoffset(t_stage, cards), DADA_STAGE_MAX_CARDS, NULL, DADA_FUNC_v_oX, (method)stage_set_cards, NULL, DADA_FUNC_X_o, (method)stage_get_cards, NULL, (method)postprocess_cards, NULL, (method)card_free, false, false);
		
		dadaitem_card_add(dadaobj_cast(x), build_pt(0, 0), -1, 45, DADA_BLACK, gensym("Tuba"), gensym("Tb.png"), 0.5, 0, 0);
		
		
		attr_dictionary_process(x,d);
		
		if ((llll_for_rebuild = llll_retrieve_from_dictionary(d, "stage_data"))) { // new method
			llllobj_manage_dict_llll((t_object *)x, LLLL_OBJ_UI, llll_for_rebuild);
			stage_set_state(x, llll_for_rebuild);
			llll_free(llll_for_rebuild);
		}
		
		jbox_ready((t_jbox *)x);
		
        dadaobj_set_current_version_number(dadaobj_cast(x));

		x->creating_new_obj = false;
	}
	return x;
}

void stage_int(t_stage *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	stage_anything(x, _sym_list, 1, argv);
}

void stage_float(t_stage *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	stage_anything(x, _sym_list, 1, argv);
}


void stage_dump(t_stage *x, char get_cards)
{	
	t_llll *ll = stage_get_state_sel(x, get_cards);
	llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 0, ll);
	llll_free(ll);
}


void stage_anything(t_stage *x, t_symbol *msg, long ac, t_atom *av)
{
	dadaobj_anything(dadaobj_cast(x), msg, ac, av);

	t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, msg, ac, av, LLLL_PARSE_CLONE);
	if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
		t_symbol *router = hatom_getsym(&parsed->l_head->l_hatom);
		llll_behead(parsed);
		
        if (dadaobj_anything_handle_domain_or_range(dadaobj_cast(x), router, parsed)) {
            // nothing to do!
        } else if (router == gensym("setstoredstate") || router == gensym("stage")) {
			stage_undo_step_push_cards(x, gensym("Set Cards"));
			stage_set_state(x, parsed);
        } else if (router == _sym_dump) {
            stage_dump(x, true);
        } else if (router == gensym("addcards")) {
            stage_undo_step_push_cards(x, gensym("Add Cards"));
            stage_add_cards(x, parsed);
        } else if (router == gensym("deletecards")) {
            stage_undo_step_push_cards(x, gensym("Delete Cards"));
            stage_delete_cards(x, parsed);
        } else if (router == gensym("clear")) {
            stage_undo_step_push_cards(x, gensym("Clear Stage"));
            dadaitem_card_clear(dadaobj_cast(x), 0);
            stage_iar(x);
        }
		
	} else if (parsed) {
		stage_undo_step_push_cards(x, gensym("Set Cards"));
		stage_set_state(x, parsed);
	}
	llll_free(parsed);
}


void stage_relocate_cards(t_stage *x, t_symbol *msg, long ac, t_atom *av)
{
	long i;
	if (ac && av && atom_gettype(av) == A_SYM) {
		t_symbol *new_folder = atom_getsym(av);
		long num_cards = dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_CARD);
		for (i = 0; i < num_cards; i++) {
			if (x->cards[i].icon_path) {
				char newpath[MAX_PATH_CHARS];
				char *last_slash = strrchr(x->cards[i].icon_path->s_name, '/');
				if (last_slash)
					snprintf_zero(newpath, MAX_PATH_CHARS, "%s/%s", new_folder->s_name, last_slash + 1);
					else
						snprintf_zero(newpath, MAX_PATH_CHARS, "%s/%s", new_folder->s_name, x->cards[i].icon_path->s_name);
						
						// re-creating surface
						if (x->cards[i].icon_surface)
							jgraphics_surface_destroy(x->cards[i].icon_surface);
				x->cards[i].icon_width = x->cards[i].icon_height = 0;
				x->cards[i].icon_path = gensym(newpath);
				x->cards[i].icon_surface = get_surface_from_file(x->cards[i].icon_path);
				
				if (x->cards[i].icon_surface){
					x->cards[i].icon_width = jgraphics_image_surface_get_width(x->cards[i].icon_surface);
					x->cards[i].icon_height = jgraphics_image_surface_get_height(x->cards[i].icon_surface);
				}
			}
		}
		t_llll *ll = llll_get();
		llll_appendsym(ll, gensym("located"), 0, WHITENULL_llll);
		llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, ll);
		llll_free(ll);
	}
}


long coord_to_card(t_stage *x, t_pt coord)
{
	long i;
	long num_cards = dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_CARD);
	for (i = num_cards - 1; i >= 0; i--)
		if (is_pt_in_rectangle_extended(coord, dadaitem_card_get_rect(dadaobj_cast(x), &x->cards[i])))
			return i;
	return -1;
}

long pixel_to_card(t_stage *x, t_pt pt, t_object *view, t_pt *coordinates)
{
	t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), view, pt);
	if (coordinates)
		*coordinates = coord;
	return coord_to_card(x, coord);
}

t_dadaitem_identifier pixel_to_element(t_stage *x, t_pt pt, t_object *view, t_pt *coordinates)
{
	t_dadaitem_identifier result;
	long idx = -1;
	result.type = DADAITEM_TYPE_NONE;
	result.flag = 0;
	result.idx = result.secondary_idx = result.tertiary_idx = -1;
	
	if ((idx = pixel_to_card(x, pt, view, coordinates)) >= 0) {
		result.type = DADAITEM_TYPE_CARD;
		result.idx = idx;
	}
	
	return result;
}



//// GRAPHIC DRAWING



void stage_paint_ext(t_stage *x, t_object *view, t_dada_force_graphics *force_graphics)
{
    long i;
	t_rect rect = force_graphics->rect;
	t_pt center = force_graphics->center_pix;
	t_jgraphics *g = force_graphics->graphic_context;
	jgraphics_set_source_rgba(g, 0, 0, 0, 1); // alpha = 1;
	
	t_jfont *jf = jfont_create_debug("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, 12 * x->b_ob.d_ob.m_zoom.zoom.x);
	t_jfont *jf_value = jfont_create_debug("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_BOLD, 9 * x->b_ob.d_ob.m_zoom.zoom.x);

    dadaobj_paint_background(dadaobj_cast(x), g, &rect);

    dadaobj_paint_grid(dadaobj_cast(x), view, force_graphics);
	
	if (x->show_text || x->show_icons || x->show_faders) {
		long num_cards = dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_CARD);
		for (i = 0; i < num_cards; i++) {
			t_rect card_rect = rect_coord_to_pix(dadaobj_cast(x), center, dadaitem_card_get_rect(dadaobj_cast(x), &x->cards[i]), false);
			
			if (x->show_icons && x->cards[i].icon_surface) {
				t_rect orig_rect = build_rect(0, 0, jgraphics_image_surface_get_width(x->cards[i].icon_surface), jgraphics_image_surface_get_height(x->cards[i].icon_surface));
				jgraphics_image_surface_draw(g, x->cards[i].icon_surface, orig_rect, card_rect);
			}
			
			if (x->cardborder_width > 0) 
				paint_rectangle(g, x->j_cardbordercolor, build_jrgba(0, 0, 0, 0), card_rect.x, card_rect.y, card_rect.width, card_rect.height, x->cardborder_width);

			if (x->show_text && x->cards[i].text) {
				t_jgraphics_text_justification hjust = (x->text_halign == DADA_STAGE_TEXT_HALIGN_LEFT ?  JGRAPHICS_TEXT_JUSTIFICATION_LEFT : (x->text_halign == DADA_STAGE_TEXT_HALIGN_RIGHT ? JGRAPHICS_TEXT_JUSTIFICATION_RIGHT : JGRAPHICS_TEXT_JUSTIFICATION_HCENTERED));
				t_jgraphics_text_justification vjust = (x->text_valign == DADA_STAGE_TEXT_VALIGN_TOP || x->text_valign == DADA_STAGE_TEXT_VALIGN_BELOW ?  JGRAPHICS_TEXT_JUSTIFICATION_TOP : (x->text_valign == DADA_STAGE_TEXT_VALIGN_BOTTOM || x->text_valign == DADA_STAGE_TEXT_VALIGN_ABOVE ? JGRAPHICS_TEXT_JUSTIFICATION_BOTTOM : JGRAPHICS_TEXT_JUSTIFICATION_VCENTERED));

				if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_CARD && x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx == i)
					jfont_set_underline(jf, 1);
				
				switch (x->text_valign) {
					case DADA_STAGE_TEXT_VALIGN_ABOVE:
						write_text(g, jf, x->j_textcolor, x->cards[i].text->s_name, card_rect.x, 0, card_rect.width, card_rect.y, hjust | vjust, true, false);
						break;
					case DADA_STAGE_TEXT_VALIGN_BELOW:
						write_text(g, jf, x->j_textcolor, x->cards[i].text->s_name, card_rect.x, card_rect.y + card_rect.height, card_rect.width, rect.height, hjust | vjust, true, false);
						break;
					default:
						write_text(g, jf, x->j_textcolor, x->cards[i].text->s_name, card_rect.x, card_rect.y, card_rect.width, card_rect.height, hjust | vjust, true, false);
						break;
				}

				jfont_set_underline(jf, 0);
			}
			
			
			if (x->show_faders) {
				double tri_height = 5 * x->b_ob.d_ob.m_zoom.zoom.x;
				double tri_y = rescale_with_slope(CLAMP(x->cards[i].value, x->value_min, x->value_max), x->value_min, x->value_max, card_rect.y + card_rect.height, card_rect.y, x->faderslope);
				paint_line(g, x->j_fadercolor, card_rect.x + card_rect.width, card_rect.y, card_rect.x + card_rect.width, 
						   card_rect.y + card_rect.height, 2);
				
				paint_triangle(g, x->j_trianglecolor, x->j_trianglecolor, card_rect.x + card_rect.width, tri_y, 
							   card_rect.x + card_rect.width + tri_height, tri_y - tri_height/2., 
							   card_rect.x + card_rect.width + tri_height, tri_y + tri_height/2., 0);
			}
				
			if (x->show_value) {
				char buf[200];
				if (x->num_decimal_digits <= 0)
					snprintf_zero(buf, 200, "%d", (long)round(x->cards[i].value));
				else
					snprintf_zero(buf, 200, "%.*f", x->num_decimal_digits, x->cards[i].value);
				double xp = card_rect.x + card_rect.width + 2 * x->b_ob.d_ob.m_zoom.zoom.x;
				write_text(g, jf_value, x->j_valuecolor, buf, xp, card_rect.y, rect.width - xp, card_rect.height, JGRAPHICS_TEXT_JUSTIFICATION_LEFT | JGRAPHICS_TEXT_JUSTIFICATION_BOTTOM, true, false);
			}
			
		}
	}
	
	jfont_destroy_debug(jf);
	jfont_destroy_debug(jf_value);
	
    dadaobj_paint_border(dadaobj_cast(x), g, &rect);

//	if (x->b_ob.d_ob.m_tools.curr_tool != DADA_TOOL_ZOOM && x->b_ob.d_ob.m_tools.curr_tool != DADA_TOOL_MOVE_CENTER)
//		repaint_hovered_elements(x, g, view, rect, center);
}


void stage_paint(t_stage *x, t_object *view)
{
    dadaobj_paint(dadaobj_cast(x), view);
}



///////// POPUP MENU FUNCTIONS



////////// INTERFACE FUNCTIONS

void stage_focusgained(t_stage *x, t_object *patcherview) {
	if (dadaobj_focusgained(dadaobj_cast(x), patcherview))
		return;
}

void stage_focuslost(t_stage *x, t_object *patcherview) {
	if (dadaobj_focuslost(dadaobj_cast(x), patcherview))
		return;
}

void send_mouseover_info(t_stage *x)
{
	t_llll *ll = llll_get();
	llll_appendsym(ll, gensym("hover"), 0, WHITENULL_llll);
	if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_CARD) {
		llll_appendlong(ll, x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx + 1, 0, WHITENULL_llll);
		llll_appendllll(ll, stage_get_single_card(x, x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx), 0, WHITENULL_llll);
	} else {
		llll_appendsym(ll, _sym_none, 0, WHITENULL_llll);
	}
	llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, ll);
	llll_free(ll);
}


void stage_output_notification(t_stage *x, t_dadaitem_identifier *ident, t_symbol *sym)
{
    t_llll *ll = llll_get();
    llll_appendsym(ll, sym);
    
    switch (ident->type) {
        case DADAITEM_TYPE_CARD:
            llll_appendsym(ll, gensym("card"));
            llll_appendlong(ll, ident->idx + 1);
            if (dadaobj_cast(x)->m_interface.send_notifications == DADAOBJ_NOTIFY_VERBOSE)
                llll_appendllll(ll, stage_get_single_card(x, x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx));
            break;
            
        default:
            llll_appendsym(ll, _llllobj_sym_none);
            break;
    }
    
    dadaobj_send_notification_llll(dadaobj_cast(x), ll);
}


void stage_mousemove(t_stage *x, t_object *patcherview, t_pt pt, long modifiers)
{
    t_dadaitem_identifier old_ident = x->b_ob.d_ob.m_interface.mousemove_item_identifier;
	
	llll_format_modifiers(&modifiers, NULL);
	
	if (dadaobj_mousemove(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
	
	if (x->b_ob.d_ob.m_interface.allow_mouse_hover) {
		if (!x->b_ob.d_ob.m_interface.mouse_is_down) {
			x->b_ob.d_ob.m_interface.mousemove_item_identifier = pixel_to_element(x, pt, patcherview, NULL);
            if (!dadaitem_identifier_eq(old_ident, x->b_ob.d_ob.m_interface.mousemove_item_identifier))
                stage_output_notification(x, &x->b_ob.d_ob.m_interface.mousemove_item_identifier, gensym("hover"));
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
	} else if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_CARD && modifiers == eControlKey) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_CHANGE_VELOCITY);
    } else if (x->allow_deletion && x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_CARD && modifiers == eCommandKey) {
        dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DELETE);
	} else if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_CARD) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DRAGGINGHAND);
	} else {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
	}
}


void stage_mousedown(t_stage *x, t_object *patcherview, t_pt pt, long modifiers){
	
	if (dadaobj_mousedown(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
	
	x->b_ob.d_ob.m_interface.mousedown_item_identifier = pixel_to_element(x, pt, patcherview, &x->b_ob.d_ob.m_interface.mousedown_coord);
	
	if (modifiers & ePopupMenu) {
		
		
	} else {
		
		llll_format_modifiers(&modifiers, NULL);
        
        stage_output_notification(x, &x->b_ob.d_ob.m_interface.mousemove_item_identifier, gensym("click"));
		
        switch (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type) {
			case DADAITEM_TYPE_CARD:
				if (x->allow_deletion && modifiers == eCommandKey) {
					if (dadaitem_card_delete(dadaobj_cast(x), x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, DIA_UNDO_POSTPROCESS_INTERFACE))
						object_error((t_object *)x, "Can't delete card.");
				}
				break;
				
			default:
				//				x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADAITEM_TYPE_NONE;
				//				x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx = 0;
				break;
		}
	}
	
	jbox_redraw((t_jbox *)x);
	
}

void stage_mouseup(t_stage *x, t_object *patcherview, t_pt pt, long modifiers){
	
	llll_format_modifiers(&modifiers, NULL);
	
	if (dadaobj_mouseup(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
	
	x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADAITEM_TYPE_NONE;
	x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag = 0;
}

void stage_mousedrag(t_stage *x, t_object *patcherview, t_pt pt, long modifiers){
	
	llll_format_modifiers(&modifiers, NULL);
	
	if (dadaobj_mousedrag(dadaobj_cast(x), patcherview, pt, modifiers)) {
		jbox_redraw((t_jbox *)x);
		return;
	}
	
	switch (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type) {
		case DADAITEM_TYPE_CARD:
			switch (modifiers) {
				case eControlKey:
				{
					// change value
					t_dada_card *card = (t_dada_card *)dadaitem_from_type_and_idx(dadaobj_cast(x), DADAITEM_TYPE_CARD, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx);
					t_pt delta_coord = delta_pix_to_delta_coord(dadaobj_cast(x), x->b_ob.d_ob.m_interface.mousedrag_delta_pix);
					double delta_val = delta_coord.y * (x->value_max - x->value_min) / card->icon_height;
					dadaitem_card_change_value_delta(dadaobj_cast(x), x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, delta_val, DIA_UNDO_POSTPROCESS_INTERFACE);
					card->value = CLAMP(card->value, x->value_min, x->value_max);
					jbox_redraw((t_jbox *)x);
				}
					break;
				case eAltKey:
/*					if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag & DADAITEM_IDENTIFIER_FLAG_DUPLICATED) {
						t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), patcherview, pt);
						dadaitem_ball_move(dadaobj_cast(x), x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, coord, DIA_UNDO_POSTPROCESS_INTERFACE);
					} else {
						t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), patcherview, pt);
						long new_idx = duplicate_ball(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx);
						if (new_idx < 0) {
							object_error((t_object *)x, "Can't duplicate ball.");
							x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
						} else {
							x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx = x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx = new_idx;
							x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag |= DADAITEM_IDENTIFIER_FLAG_DUPLICATED;
							jbox_redraw((t_jbox *)x);
						}
					} */
					break;
				default:
					switch (x->b_ob.d_ob.m_tools.curr_tool) {
						default:
							t_pt delta_coord = delta_pix_to_delta_coord(dadaobj_cast(x), x->b_ob.d_ob.m_interface.mousedrag_delta_pix);
							dadaitem_card_move_delta(dadaobj_cast(x), x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, delta_coord, DIA_UNDO_POSTPROCESS_INTERFACE);
							jbox_redraw((t_jbox *)x);
							break;
					} 
					break;
			}
			break;
			
		default:
			break;
	}
}



void stage_mousewheel(t_stage *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc){
	llll_format_modifiers(&modifiers, NULL);  
	
	if (dadaobj_mousewheel(dadaobj_cast(x), view, pt, modifiers, x_inc, y_inc)) {
		jbox_redraw((t_jbox *)x);
		return;
	}
}



long stage_keyup(t_stage *x, t_object *patcherview, long keycode, long modifiers, long textcharacter){
	
	llll_format_modifiers(&modifiers, &keycode);
	
	if (dadaobj_keyup(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
		return 1;
	
	return 0;
}

long stage_key(t_stage *x, t_object *patcherview, long keycode, long modifiers, long textcharacter)
{
	llll_format_modifiers(&modifiers, &keycode);
	
	if (dadaobj_key(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
		return 1;
	
	switch (keycode) {
		case JKEY_ESC:
			jbox_redraw((t_jbox *)x);
			return 1;
		default:
			break;
	}
	
	return 0;
}


void stage_mouseenter(t_stage *x, t_object *patcherview, t_pt pt, long modifiers) 
{
	if (dadaobj_mouseenter(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
}

void stage_mouseleave(t_stage *x, t_object *patcherview, t_pt pt, long modifiers) 
{
	if (dadaobj_mouseleave(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
}



//// UNDO

void stage_postprocess_undo(t_stage *x)
{
	jbox_redraw((t_jbox *)x);
}


void stage_undo_step_push_cards(t_stage *x, t_symbol *operation)
{
	undo_add_interface_step(dadaobj_cast(x), DADA_FUNC_v_oX, (method)stage_set_cards, NULL, DADA_FUNC_X_o, (method)stage_get_cards, NULL, DADA_UNDO_OP_MODIFICATION, operation);
}
