/**
	@file
	dada.life.c
	
	@name 
	dada.life
	
	@realname 
	dada.life

	@type
	object
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
	2D cellular automata 
	
	@description
	Graphic interface for 2D cellular automata
	
	@discussion
	
	@category
	dada, dada interfaces, dada rule-based systems

	@keywords
	life, Conway, cellular automaton, cellular automata
	
	@seealso
	dada.life.info, bach.tonnetz, cage.life, dada.kaleido
	
	@owner
	Daniele Ghisi
*/


#include "dada.interface.h"
#include "dada.geometry.h"
#include "dada.paint.h"
#include "dada.popupmenu.h"
//#include "dada.cursors.data.c"
#include "dada.undo.h"


#define DADA_LIFE_MAX_SIZE 1000

#define DADA_LIFE_MAX_NUM_BORN_SIZE 10
#define DADA_LIFE_MAX_NUM_STAY_ALIVE_SIZE 10

#define DADA_LIFE_DEFAULT_RANDOM_DENSITY 0.1
#define DADA_LIFE_PEN_SIZE 5

#define coord_to_idx(x, coord_x, coord_y) ((-(coord_y) + x->offset) * x->size + (((coord_x) + x->offset)))
#define are_coord_in_matrix(x, coord_x, coord_y) ((-(coord_y) + x->offset >= 0) && (-(coord_y) + x->offset < x->size) && ((coord_x) + x->offset >= 0) && ((coord_x) + x->offset < x->size))

typedef unsigned char t_cell;

//typedef t_cell (*life_custom_rule_fn)(t_cell cell, int neighbors_size, t_cell **neighbors, int sum_neighbors, int nonzero_neighbors);
typedef t_cell (*life_custom_rule_fn)(t_cell cell, int neighbors_size, t_cell **neighbors, int sum_neighbors, int nonzero_neighbors);

typedef struct life_metadata
{
	double	pitch_mc;
	char	velocity;
} t_life_metadata;


typedef enum _life_states {
	DEAD, LIVE
} e_life_states;

e_life_states state[1 << 9];

typedef enum _dada_life_border_behavior {
	DADA_LIFE_BORDER_DEADOUTSIDE = 0,
	DADA_LIFE_BORDER_WRAP = 1,
	DADA_LIFE_BORDER_KILL = 2,
	DADA_LIFE_BORDER_LIVE = 3,
} e_dada_life_border_behavior;


typedef enum _dada_life_shapes {
	DADA_LIFE_SHAPE_SQUARE = 0,
	DADA_LIFE_SHAPE_HEXAGON = 1,
	DADA_LIFE_SHAPE_CIRCLE = 2,
	DADA_LIFE_SHAPE_SPRITE = 3,
} e_dada_life_shapes;

typedef enum _dada_life_color_mapping {
	DADA_LIFE_COLORMAP_NONE = 0,
	DADA_LIFE_COLORMAP_CANDYCANE = 1,
	DADA_LIFE_COLORMAP_COLORSCALE = 2,
	DADA_LIFE_COLORMAP_COLORSPECTRUM = 3,
	DADA_LIFE_COLORMAP_RANDOM = 4,
	DADA_LIFE_COLORMAP_CUSTOM = 5,
} e_dada_life_color_mapping;

typedef enum _dada_life_size_mapping {
	DADA_LIFE_SIZEMAP_NONE = 0,
	DADA_LIFE_SIZEMAP_MULTIPLY = 1,
	DADA_LIFE_SIZEMAP_MULTIPLYBUTREDUCEALPHA = 2
} e_dada_life_size_mapping;



////////////////////////// structures
typedef struct _life 
{
	t_dadaobj_jbox	b_ob; // root object
	
	char			mode;
	long			size;
	long			offset;
	
	long			num_born[DADA_LIFE_MAX_NUM_BORN_SIZE];
	long			num_born_size;
	t_uint64		num_born_bitfield;
	long			num_stay_alive[DADA_LIFE_MAX_NUM_STAY_ALIVE_SIZE];
	long			num_stay_alive_size;
	t_uint64		num_stay_alive_bitfield;
	long			neighborhood_size; // how "far" do we consider the neighbors to be?

    double          default_random_density;
    
	long			border; // border behavior, one of the e_dada_life_border_behavior border
	
	// world
	t_cell			*n_world[2];	// we use 2 worlds, one for the current, one for the previous step, to ease copying
	long			n_thisworld;
	t_life_metadata	*n_world_metadata;
	
	// custom rule
	char				use_custom_rule;
	life_custom_rule_fn	custom_rule;
	t_cell				**neighborhood_callback;
	t_object			*clang;	// rule compiler

	// play and pitches
	char			play;
	char			extended_playout_data;	///< Send extended playout data
	t_symbol		*cents_eq_as_sym;
	t_lexpr			*cents_lexpr;
	t_symbol		*vels_eq_as_sym;
	t_lexpr			*vels_lexpr;
	t_symbol		*size_eq_as_sym;
	t_lexpr			*size_lexpr;
	t_symbol		*alpha_eq_as_sym;
	t_lexpr			*alpha_lexpr;
	t_symbol		*red_eq_as_sym;
	t_lexpr			*red_lexpr;
	t_symbol		*green_eq_as_sym;
	t_lexpr			*green_lexpr;
	t_symbol		*blue_eq_as_sym;
	t_lexpr			*blue_lexpr;
	
	// display
	t_jrgba			j_cellcolor;
	t_jrgba			j_playcolor;
	char			show_focus;
	char			show_notes;
	double			min_pitch;
	double			max_pitch;
	char			show_velocity;
	char			shape; // one of the e_dada_life_point_shape
	char			color_mapping; // one of the e_dada_life_color_mapping
	double			size_factor; // fixed factor
	t_symbol		*sprite_sym;
	t_dada_sprite	sprite;
	long			max_val_for_mapping;
	
	// candycane colors
	long			num_candycane;
	t_jrgba			j_candycane2;
	t_jrgba			j_candycane3;
	t_jrgba			j_candycane4;
	t_jrgba			j_candycane5;
	t_jrgba			j_candycane6;
	t_jrgba			j_candycane7;
	t_jrgba			j_candycane8;

	// interface
	long			hovered_idx;
	
	// utilities
	char			firsttime;
	char			justgainedfocus;
	char			itsme;
	char			creating_new_obj;

	long			n_in;   // space for the inlet number used by all the proxies
    void			*n_proxy1;
	
	// outlets are declared in the dadaobj->llllobj structure, at the beginning
} t_life;


///////////////////////// function prototypes
//// standard set
void *life_new(t_symbol *s, long argc, t_atom *argv);
void life_free(t_life *x);
void life_assist(t_life *x, void *b, long m, long a, char *s);

void life_paint(t_life *x, t_object *view);
void life_paint_ext(t_life *x, t_object *view, t_dada_force_graphics *force_graphics);


void life_int(t_life *x, t_atom_long num);
void life_float(t_life *x, double num);
void life_anything(t_life *x, t_symbol *msg, long ac, t_atom *av);
void life_bang(t_life *x);


// get/set status
void life_set_state(t_life *x, t_llll *state);
t_llll *life_get_state(t_life *x);
void life_set_cents(t_life *x, t_llll *cents);
void life_set_velocity(t_life *x, t_llll *velocity);


// interface
void life_focusgained(t_life *x, t_object *patcherview);
void life_focuslost(t_life *x, t_object *patcherview);
void life_mousedown(t_life *x, t_object *patcherview, t_pt pt, long modifiers);
void life_mousemove(t_life *x, t_object *patcherview, t_pt pt, long modifiers);
void life_mouseup(t_life *x, t_object *patcherview, t_pt pt, long modifiers);
void life_mousedrag(t_life *x, t_object *patcherview, t_pt pt, long modifiers);
long life_key(t_life *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
long life_keyup(t_life *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
void life_mousewheel(t_life *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc);	
void life_mouseleave(t_life *x, t_object *patcherview, t_pt pt, long modifiers); 
void life_mouseenter(t_life *x, t_object *patcherview, t_pt pt, long modifiers);
t_max_err life_notify(t_life *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void life_jsave(t_life *x, t_dictionary *d);
void life_preset(t_life *x);
void life_begin_preset(t_life *x, t_symbol *s, long argc, t_atom *argv);
void life_restore_preset(t_life *x, t_symbol *s, long argc, t_atom *argv);
void life_end_preset(t_life *x);

void build_cents_grid(t_life *x);
void build_velocity_grid(t_life *x);

void life_clear(t_life *x, char also_outside_world);
void life_random(t_life *x, char distribution, double density, char add_to_existing);
void life_set_custom_rule(t_life *x, t_symbol *rule);
void life_shift(t_life *x, long x_shift, long y_shift);

void life_exportpng(t_life *x, t_symbol *file, long dpi, double width, double height, t_pt exportcenteroffset);


t_max_err life_setattr_play(t_life *x, t_object *attr, long ac, t_atom *av);
t_max_err life_setattr_cents(t_life *x, t_object *attr, long ac, t_atom *av);
t_max_err life_setattr_velocity(t_life *x, t_object *attr, long ac, t_atom *av);
t_max_err life_setattr_size(t_life *x, t_object *attr, long ac, t_atom *av);
t_max_err life_setattr_cellsize(t_life *x, t_object *attr, long ac, t_atom *av);
t_max_err life_setattr_cellred(t_life *x, t_object *attr, long ac, t_atom *av);
t_max_err life_setattr_cellgreen(t_life *x, t_object *attr, long ac, t_atom *av);
t_max_err life_setattr_cellblue(t_life *x, t_object *attr, long ac, t_atom *av);
t_max_err life_setattr_cellalpha(t_life *x, t_object *attr, long ac, t_atom *av);

void send_all_noteons(t_life *x);
void send_all_noteoffs(t_life *x);
void process_change(t_life *x);

void life_undo_postprocess(t_life *x);



///////////////////////// utility functions



void send_playout_data(t_life *x, double midicents, long velocity, long MIDIchannel, long idx)
{
	t_llll *ll = llll_get();
	llll_appenddouble(ll, midicents, 0, WHITENULL_llll);
	llll_appendlong(ll, velocity, 0, WHITENULL_llll);
	llll_appendlong(ll, MIDIchannel, 0, WHITENULL_llll);
	if (x->extended_playout_data) {
		t_llll *coord = llll_get();
		llll_appendlong(coord, -x->offset + (idx % x->size), 0, WHITENULL_llll);
		llll_appendlong(coord, x->offset - (idx / x->size), 0, WHITENULL_llll);
		llll_appendllll(ll, coord, 0, WHITENULL_llll);
	}
	llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 2, ll);
	llll_free(ll);
}

void send_noteoff(t_life *x, long idx)
{
	send_playout_data(x, x->n_world_metadata[idx].pitch_mc, 0, 1, idx);
}

void send_noteon(t_life *x, long idx)
{
	send_playout_data(x, x->n_world_metadata[idx].pitch_mc, x->n_world_metadata[idx].velocity, 1, idx);
}

void send_all_noteoffs(t_life *x)
{
	long i, j;
	for (i = 0; i < x->size; i++) {
		for (j = 0; j < x->size; j++) {
			long idx = j * x->size + i;
			if (x->n_world[x->n_thisworld][idx])
				send_noteoff(x, idx);
		}
	}
}

void send_all_noteons(t_life *x)
{
	long i, j;
	for (i = 0; i < x->size; i++) {
		for (j = 0; j < x->size; j++) {
			long idx = i * x->size + j;
			if (x->n_world[x->n_thisworld][idx])
				send_noteon(x, idx);
		}
	}
}



void life_play_step(t_life *x)
{
	long i, j;
	for (i = 0; i < x->size; i++) {
		for (j = 0; j < x->size; j++) {
			long idx = j * x->size + i;
			char val1 = x->n_world[x->n_thisworld][idx];
			char val2 = x->n_world[1 - x->n_thisworld][idx];
			if (val1 != val2) {
				if (val1 == 0) // noteoff
					send_noteoff(x, idx);
				else
					send_noteon(x, idx);
			}
		}
	}
}

// process any change which has happened for the shapes
void process_change(t_life *x)
{
	jbox_redraw((t_jbox *)x);
}



/////////////////////// LIFE ALGORITHM

/*!
 * \brief Compute the next generation of the Game of Life.
 * \param this The current state of the known universe.
 * \param new Where to put the replacement universe.
 * \note \c new must have three times the space used by \c this.
 */
void life_step(int *this_world, int *new_world)
{
	unsigned bitmap;
	int *next, *prev;
	int x, y;
	static enum {
		DEAD, LIVE
	} state[1 << 9];
	
	if(state[007] == 0) {
		for(bitmap = 0; bitmap < 1<<9; bitmap++) {
			for(x = y = 0; y < 9; y++)
				if(bitmap & 1<<y)
					x += 1;
			if(bitmap & 020) {
				if(x == 2 || x == 3)
					state[bitmap] = LIVE;
				else
					state[bitmap] = DEAD;
			} else {
				if(x == 3)
					state[bitmap] = LIVE;
				else
					state[bitmap] = DEAD;
			}
		}
	}
	
	prev = next = this_world;
	bitmap = 0;
	*new_world = 0;
	for(;;) {
		/* did we write an X co-ordinate? */
		if(*new_world < 0)
			new_world++;
		if(prev == next) {
			/* start a new group of rows */
			if(*next == 0) {
				*new_world = 0;
				return;
			}
			y = *next++ + 1;
		} else {
			/* move to next row and work out which ones to scan */
			if(*prev == y--)
				prev++;
			if(*this_world == y)
				this_world++;
			if(*next == y-1)
				next++;
		}
		/* write new row co-ordinate */
		*new_world = y;
		for(;;) {
			/* skip to the leftmost cell */
			x = *prev;
			if(x > *this_world)
				x = *this_world;
			if(x > *next)
				x = *next;
			/* end of line? */
			if(x >= 0)
				break;
			for(;;) {
				/* add a column to the bitmap */
				if(*prev == x) {
					bitmap |= 0100;
					prev++;
				}
				if(*this_world == x) {
					bitmap |= 0200;
					this_world++;
				}
				if(*next == x) {
					bitmap |= 0400;
					next++;
				}
				/* what does this bitmap indicate? */
				if(state[bitmap] == LIVE)
					*++new_world = x - 1;
				else if(bitmap == 000)
					break;
				/* move right */
				bitmap >>= 3;
				x += 1;
			}
		}
	}
}



/// THIS FUNCTION IS THE ONE ACTUALLY USED

void life_ezstep(t_cell *this_world, t_cell *new_world, int size, int neighborhood_size, e_dada_life_border_behavior border, e_dada_lattice_types lattice, t_uint64 num_born_bitfield, t_uint64 num_stay_alive_bitfield)
{
	// TO DO : OPTIMIZE borders: no need to check border == ...
	int i, j;
	int nj, ni, ci, cj;
	for (i = 0; i < size; i++) { // i is the column number
		for (j = 0; j < size; j++) { // j is the row number
			if ((border == DADA_LIFE_BORDER_KILL || border == DADA_LIFE_BORDER_LIVE) && (i == 0 || j == 0 || i == size - 1 || j == size - 1)) {
				*(new_world + j * size + i) = (border == DADA_LIFE_BORDER_KILL ? 0 : 1);
			} else {
				int count = 0;
				for (ni = i - neighborhood_size, ci = 0; ni <= i + neighborhood_size; ni++, ci++) {
					for (nj = j - neighborhood_size, cj = 0; nj <= j + neighborhood_size; nj++, cj++) {
						if (nj == j && ni == i)
							continue;
						if (lattice == DADA_LATTICE_TRIANGLE && (ci-cj > neighborhood_size || ci-cj < -neighborhood_size))
							continue;
						if (ni < 0 || ni >= size || nj < 0 || nj >= size) {
							if (border == DADA_LIFE_BORDER_WRAP)
								count += *(this_world + ((nj + size) % size) * size + ((ni + size) % size));
							else
								continue;
						} else
							count += *(this_world + nj * size + ni);
					}
				}
				if (*(this_world + j * size + i) == 0) {
					*(new_world + j * size + i) = ((num_born_bitfield & (1 << count)) > 0);
				} else {
					*(new_world + j * size + i) = ((num_stay_alive_bitfield & (1 << count)) > 0);
				}
			}
		}
	}
}

void life_customstep(t_cell *this_world, t_cell *new_world, int size, int neighborhood_size, t_cell **neighborhood_matrix,
					 e_dada_life_border_behavior border, e_dada_lattice_types lattice, life_custom_rule_fn rule)
{
	int i, j;
	int nj, ni, ci, cj;
	int neighbor_matrix_size = 2 * neighborhood_size + 1;

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if ((border == DADA_LIFE_BORDER_KILL || border == DADA_LIFE_BORDER_LIVE) && (i == 0 || j == 0 || i == size - 1 || j == size - 1)) {
				*(new_world + j * size + i) = (border == DADA_LIFE_BORDER_KILL ? 0 : 1);
			} else {
				int count = 0, nonzero_neighbors = 0;
				t_cell this_cell = 0;
				for (ni = i - neighborhood_size, ci = 0; ni <= i + neighborhood_size && ci < neighbor_matrix_size; ci++, ni++) {
					for (nj = j - neighborhood_size, cj = 0; nj <= j + neighborhood_size && cj < neighbor_matrix_size; cj++, nj++) {
						char this_val;
						if (lattice == DADA_LATTICE_TRIANGLE && (ci-cj > neighborhood_size || ci-cj < -neighborhood_size))
							this_val = 0;
						else {
							if (ni < 0 || ni >= size || nj < 0 || nj >= size) {
								if (border == DADA_LIFE_BORDER_WRAP)
									this_val = *(this_world + ((nj + size) % size) * size + ((ni + size) % size));
								else
									this_val = 0;
							} else {
								this_val = *(this_world + nj * size + ni);
							}
						}
						
						neighborhood_matrix[ci][cj] = this_val;
						
						if (nj == j && ni == i) {
							this_cell = this_val;
							continue;
						}
						count += this_val;
						nonzero_neighbors += (this_val > 0);
					}
				} 
				*(new_world + j * size + i) = (rule)(this_cell, neighbor_matrix_size, neighborhood_matrix, count, nonzero_neighbors);
			}
		}
	}
}



void life_set_custom_rule(t_life *x, t_symbol *rule)
{
	t_atom ret, fun, str;	
	t_object *string;
	
	if (!rule) {
		object_error((t_object *)x, "No custom rule defined!");
		return;
	}
	
	// Set rule, by appending
	long size = strlen(rule->s_name) + 2000;
	char *buf = (char *)bach_newptr(size * sizeof(char)); // buf + 100
	
	
	snprintf_zero(buf, size, "%s \n"
				  "typedef unsigned char t_cell; \n "
				  "t_cell life_customstep_one(t_cell cell, int neighbors_size, t_cell **neighbors, int sum_neighbors, int nonzero_neighbors); \n"
				  "t_cell life_customstep_one(t_cell cell, int neighbors_size, t_cell **neighbors, int sum_neighbors, int nonzero_neighbors) { \n"
                  "%s \n"
				  "}", dada_get_default_include(), rule->s_name);
	
	// recreate clang object
	object_free(x->clang);
	x->clang = (t_object *)object_new(CLASS_NOBOX, gensym("clang"), gensym("dadalife"));

    //dg: enabling cpp doesn't work; nothing compiles any longer
//    object_attr_setlong(x->clang, gensym("cpp"), 1); //-- enabling C++ causes a hang when using addsymbol, need to investigate...

	// make a new string object (alternative to symbol that avoids post)
	string = (t_object *)object_new(CLASS_NOBOX, gensym("string"), buf);
	atom_setobj(&str, string);
	
    /*
    t_symbol *ps_addsymbol = gensym("addsymbol");
    object_method(x->clang, ps_addsymbol, gensym("acosh"), &acosh);
    object_method(x->clang, ps_addsymbol, gensym("asinh"), &asinh);
    object_method(x->clang, ps_addsymbol, gensym("atanh"), &atanh);
    object_method(x->clang, ps_addsymbol, gensym("modf"), &modf);
    object_method(x->clang, ps_addsymbol, gensym("hypot"), &hypot);
    object_method(x->clang, ps_addsymbol, gensym("trunc"), &trunc);
    object_method(x->clang, ps_addsymbol, gensym("round"), &round);
    */
    
	// compile the string
	object_method_typed(x->clang, gensym("compile"), 1, &str, &ret);
	
	// obtain the function (executable code)
	object_method_sym(x->clang, gensym("getfunction"), gensym("life_customstep_one"), &fun);
	
	// get the function pointer
	x->custom_rule = (life_custom_rule_fn)atom_getobj(&fun);
	
	// must check that there is code, otherwise there was a compile error
	if (!x->custom_rule)
		object_error((t_object *)x, "Syntax error in custom rule!");
	else {
/*		// test rule
		t_cell cell = 0;
		int neighbors_size = 5;
		t_cell **neighbors = NULL;
		int sum_neighbors = 1;
		int nonzero_neighbors = 1;
		t_cell res = (x->custom_rule)(cell, neighbors_size, neighbors, sum_neighbors, nonzero_neighbors);
		post("%d", (int) res); */
	}
	
	bach_freeptr(buf);
	
	// Destroy the string (but not the clang: we need the compiled function!)
	object_free(string);
}


//////////////////////// global class pointer variable
t_class *life_class;

void C74_EXPORT ext_main(void *moduleRef)
{	
	t_class *c;
	
	common_symbols_init();
	llllobj_common_symbols_init();
	

	if (dada_check_bach_version() || llllobj_test()) {
		dada_error_bachcheck();
		return;
	}

	srand(time(NULL)); // needed for the random function

	CLASS_NEW_CHECK_SIZE(c, "dada.life", (method)life_new, (method)life_free, (long)sizeof(t_life), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, 0);	// include textfield and Fonts attributes
	//	jbox_initclass(c, 0);
	
	// paint & utilities
	class_addmethod(c, (method) life_paint,			"paint", A_CANT, 0);
	class_addmethod(c, (method) life_assist,			"assist",		A_CANT, 0);  
	class_addmethod(c, (method)	life_notify,			"bachnotify",		A_CANT,		0);

	// save & preset
    class_addmethod(c, (method) life_preset, "preset", 0);
    class_addmethod(c, (method) life_begin_preset, "begin_preset", A_GIMME, 0);
    class_addmethod(c, (method) life_restore_preset, "restore_preset", A_GIMME, 0);
    class_addmethod(c, (method) life_end_preset, "end_preset", 0);
	CLASS_METHOD_ATTR_PARSE(c, "begin_preset", "undocumented", gensym("long"), 0L, "1");
	CLASS_METHOD_ATTR_PARSE(c, "restore_preset", "undocumented", gensym("long"), 0L, "1");
	CLASS_METHOD_ATTR_PARSE(c, "end_preset", "undocumented", gensym("long"), 0L, "1");
	class_addmethod(c, (method) life_jsave, "jsave", A_CANT, 0);
	
	// interface
	class_addmethod(c, (method) life_focusgained, "focusgained", A_CANT, 0);
	class_addmethod(c, (method) life_focuslost, "focuslost", A_CANT, 0);
    
    
    // @method (keyboard) @digest Edit content
    // @description
    // • <m>Enter</m>: perform automaton step (go to next generation)<br />
    // • <m>↓</m>, <m>↑</m>, <m>←</m>, <m>→</m>: move all cells (respectively) down, up, left, right<br />
    // • <m>Tab</m>: set automaton to a gaussian-distributed random configuration<br />
    //    ↪ Add the <m>Shift</m> key to keep previously live cells. <br />
    // • <m>Backspace</m>: clear all cells<br />
    // • <m>Spacebar</m>: Toggle playback (i.e. toggle <m>play</m> attribute)<br />
    // • <m>Esc</m>: send all notes-off and reset center to (0, 0) position <br />
    class_addmethod(c, (method) life_key, "key", A_CANT, 0);
    class_addmethod(c, (method) life_keyup, "keyup", A_CANT, 0);

    // @method (mouse) @digest Edit content
    // @description
    // • <m>click+drag</m>: create new live cells<br />
    // • <m>Cmd+click+drag</m> (mac) or <m>Ctrl+click+drag</m> (win): erase living cells<br />
    // • <m>right-click</m> or <m>two-fingers tap</m>: open contextual menu for basic operations<br />
    class_addmethod(c, (method) life_mousedown, "mousedown", A_CANT, 0);
	class_addmethod(c, (method) life_mousedrag, "mousedrag", A_CANT, 0);
	class_addmethod(c, (method) life_mouseup, "mouseup", A_CANT, 0);
    
    // @method (tools) @digest Navigate
    // @description
    // @copy DADA_DOC_TOOLS_INTRO
    // @copy DADA_DOC_TOOLS_ZX
    // @copy DADA_DOC_TOOLS_NV
    class_addmethod(c, (method) life_mousemove, "mousemove", A_CANT, 0);
	class_addmethod(c, (method) life_mousewheel, "mousewheel", A_CANT, 0);
	class_addmethod(c, (method) life_mouseenter, "mouseenter", A_CANT, 0);
	class_addmethod(c, (method) life_mouseleave, "mouseleave", A_CANT, 0);

	// @method bang @digest Perform automaton step
	// @description Performs a step of the automaton rule, possibly sending the played content through the play outlet
    // (if <m>play</m> attribute is set to 1).
	class_addmethod(c, (method)life_bang,			"bang",			0);


    // @method flush @digest Send all note-offs
	// @description The word <m>flush</m> force all the note-offs for notes being played to be sent. 
	// This is effective only when the <m>play</m> attribute is set to 1.
	class_addmethod(c, (method)life_anything,	"flush",		A_GIMME,	0);
    
    // @method rule @digest Set C code for custom rule
    // @description Any portion of C code is considered the code for a custom rule to be implemented.
    // This code is run for every cell, and should return the new state of the cell
    // (in the typical 1-bit case: 1 if the cell will be alive at the next generation, 0 otherwise).
    // Knowing that a <m>t_cell</m> is defined as: <br />
    // <m>typedef unsigned char t_cell;</m> <br />
    // some variables can be used inside the code: <br />
    // • <m>cell</m>: a <m>t_cell</m> containing the current state of the cellM <br />
    // • <m>neighbors_size</m>: an int containing the neighbors size; <br />
    // • <m>neighbors</m>: an double array of <m>neighbors_size</m> by <m>neighbors_size</m> cells containing each a <m>t_cell</m> element; <br />
    // • <m>sum_neighbors</m>: the sum of all the value of the neighbors of the current cell; <br />
    // • <m>nonzero_neighbors</m>: the number of all the non-zero neighbors of the current cell. <br />
    // More precisely, the prototype of the function being written is thus: <br />
    // <m>t_cell life_customstep_one(t_cell cell, int neighbors_size, t_cell **neighbors, int sum_neighbors, int nonzero_neighbors);</m> <br />
    // This code is compiled on the fly, so that users can take advantage of native speed for complex rules.
    class_addmethod(c, (method)life_anything,	"rule",			A_GIMME,	0);

    
    // @method dump @digest Dump current state
    // @description The word <m>dump</m> dumps the state of all the cells in the form
    // <b>life [world <m>CELLS</m>]</b>, where <m>CELLS</m> is an llll containing <m>N</m> sub-lllls, each containing <m>N</m> integers
    // (i.e. it is a <m>N</m>-by-<m>N</m> matrix). Each integer represents the state of a cell, and <m>N</m> equals exactly the world <m>size</m>
    // (see <m>size</m> attribute). The state of the cell must be an integer from 0 to 255.
	class_addmethod(c, (method)life_anything,		"dump",		A_GIMME,	0);

    
    // @method clear @digest Clear cells
    // @description The word <m>clear</m> sets the state of all cells to 0 (= dead).
    class_addmethod(c, (method)life_anything,		"clear",	A_GIMME,	0);

    
    // @method clearall @digest Ultimately clear cells
    // @description The word <m>clearall</m> sets the state of all cells to 0 (= dead), even if the cells are outside
    // the current world (so that if, at any moment, the world becomes bigger, its newly added cells are 0's). Also see the <m>size</m> attribute.
    class_addmethod(c, (method)life_anything,		"clearall",	A_GIMME,	0);

    
    // @method random @digest Create random active cells
    // @description The word <m>random</m> sets the state of some random cells to 1, by default setting all other cells to 0.
    // The word can be further followed by a list formatted as:
    // <b>[<m>specification</m> <m>value</m>] [<m>specification</m> <m>value</m>]...</b>. <br />
    // Each specification can be one of the followings: <br />
    // • "distribution": the value is expected to be either "gaussian" or "uniform"; <br />
    // • "density": the floating point density of cells for the distribution; <br />
    // • "append": set 1 if you need to append the random cells to the existing cells, set 0 if you need to replace all current cells with random cells. <br />
    // @marg 0 @name params @optional 1 @type llll
    class_addmethod(c, (method)life_anything,		"random",	A_GIMME,	0);

    
    // @method shift @digest Shift cells
    // @description The word <m>shift</m> followed by two integers (say, <m>X</m> and <m>Y</m>) shifts all the cells by <m>X</m> horizontal steps
    // and <m>Y</m> vertical steps (positive values move right and upward, negative values move left and downward).
    // @marg 0 @name x_shift @optional 0 @type int
    // @marg 1 @name y_shift @optional 0 @type int
    class_addmethod(c, (method)life_anything,		"shift",	A_GIMME,	0);

    // @method exportpng @digest Export PNG image
    // @description The word <m>exportpng</m>, followed by an file path, exports the current canvas as a PNG image.
    // This can be further followed by a list formatted as:
    // <b>[<m>specification</m> <m>value</m>] [<m>specification</m> <m>value</m>]...</b>. <br />
    // Each specification can be one of the followings: <br />
    // • "dpi": the value is expected to be the dpi resolution of the exported image; <br />
    // • "width": the value is expected to be the width of the exported image in pixels; <br />
    // • "height": the value is expected to be the height of the exported image in pixels; <br />
    // • "center": the value is expected to be an llll containing the coordinates of the center; <br />
    // @marg 0 @name filename @optional 0 @type symbol
    // @marg 1 @name params @optional 1 @type llll
    class_addmethod(c, (method)life_anything,		"exportpng",	A_GIMME,	0);

    
    // @method getsize @digest Get world size
    // @description Queries the current size of the world. Output is sent through the second outlet, preceded by the "size" symbol.
    class_addmethod(c, (method)life_anything,	"getsize",			A_GIMME,	0);

    // @method getnumliving @digest Get the number of living cells
    // @description Queries the current number of living cells. Output is sent through the second outlet, preceded by the "numliving" symbol.
    class_addmethod(c, (method)life_anything,	"getnumliving",			A_GIMME,	0);

    // @method getnumliving @digest Get the number of dead cells
    // @description Queries the current number of dead cells. Output is sent through the second outlet, preceded by the "numdead" symbol.
    class_addmethod(c, (method)life_anything,	"getnumdead",			A_GIMME,	0);

    // @method getcellsum @digest Get the sum of all cells
    // @description Queries the sum of the values of all cells. Output is sent through the second outlet, preceded by the "cellsum" symbol.
    // In the standard 0-1 valued case, this coincides with <m>getnumliving</m>; it does not coincide with it in the case of a general rule.
    class_addmethod(c, (method)life_anything,	"getcellsum",			A_GIMME,	0);

    
    class_addmethod(c, (method)life_anything,	"anything",			A_GIMME,	0);
	class_addmethod(c, (method)life_anything,	"setstoredstate",	A_GIMME, 0);

    
    DADAOBJ_JBOX_DECLARE_READWRITE_METHODS(c);
    DADAOBJ_JBOX_DECLARE_IMAGE_METHODS(c);
    DADAOBJ_JBOX_DECLARE_ACCEPTSDRAG_METHODS(c);

	llllobj_class_add_out_attr(c, LLLL_OBJ_UI);
	dadaobj_class_init(c, LLLL_OBJ_UI, DADAOBJ_BBG | DADAOBJ_ZOOM | DADAOBJ_CENTEROFFSET | DADAOBJ_EMBED | DADAOBJ_MOUSEHOVER | DADAOBJ_NOTIFICATIONS | DADAOBJ_EXPORTTOJITTER);
	CLASS_ATTR_FILTER_CLIP(c, "zoom", 10, 1000);

	
	CLASS_ATTR_DEFAULT(c, "patching_rect", 0, "0 0 300 300");
	// @exclude dada.life
	CLASS_ATTR_DEFAULT(c, "presentation_rect", 0, "0 0 300 300");
	// @exclude dada.life
	

	CLASS_STICKY_ATTR(c,"category",0,"Color");
	
	CLASS_ATTR_RGBA(c, "cellcolor", 0, t_life, j_cellcolor);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "cellcolor", 0, "0.4 0. 0. 1.");
	CLASS_ATTR_STYLE_LABEL(c, "cellcolor", 0, "rgba", "Cell Color");
	CLASS_ATTR_BASIC(c, "cellcolor", 0);
	// @description Sets the color of the "living" cells
	
	CLASS_ATTR_RGBA(c, "candycane2", 0, t_life, j_candycane2);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "candycane2", 0, "0.705882 0.624879 0. 1.");
	CLASS_ATTR_STYLE_LABEL(c, "candycane2", 0, "rgba", "Candycane Color 1");
    // @description Specifies the 2nd cell color in candycane mode.

	CLASS_ATTR_RGBA(c, "candycane3", 0, t_life, j_candycane3);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "candycane3", 0, "0.481517 0.686275 0. 1.");
	CLASS_ATTR_STYLE_LABEL(c, "candycane3", 0, "rgba", "Candycane Color 2");
    // @description Specifies the 3rd cell color in candycane mode.

	CLASS_ATTR_RGBA(c, "candycane4", 0, t_life, j_candycane4);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "candycane4", 0, "0. 0.647059 0.093346 1.");
	CLASS_ATTR_STYLE_LABEL(c, "candycane4", 0, "rgba", "Candycane Color 3");
    // @description Specifies the 4th cell color in candycane mode.

	CLASS_ATTR_RGBA(c, "candycane5", 0, t_life, j_candycane5);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "candycane5", 0, "0. 0.63388 0.666667 1.");
	CLASS_ATTR_STYLE_LABEL(c, "candycane5", 0, "rgba", "Candycane Color 4");
    // @description Specifies the 5th cell color in candycane mode.

	CLASS_ATTR_RGBA(c, "candycane6", 0, t_life, j_candycane6);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "candycane6", 0, "0. 0.214208 0.666667 1.");
	CLASS_ATTR_STYLE_LABEL(c, "candycane6", 0, "rgba", "Candycane Color 5");
    // @description Specifies the 6th cell color in candycane mode.

	CLASS_ATTR_RGBA(c, "candycane7", 0, t_life, j_candycane7);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "candycane7", 0, "0.447445 0. 0.588235 1.");
	CLASS_ATTR_STYLE_LABEL(c, "candycane7", 0, "rgba", "Candycane Color 6");
    // @description Specifies the 7th cell color in candycane mode.

	CLASS_ATTR_RGBA(c, "candycane8", 0, t_life, j_candycane8);
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "candycane8", 0, "0.54902 0. 0.29161 1.");
	CLASS_ATTR_STYLE_LABEL(c, "candycane8", 0, "rgba", "Candycane Color 7");
    // @description Specifies the 8th cell color in candycane mode.

	CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	
	CLASS_STICKY_ATTR(c,"category",0,"Behavior");
	
	CLASS_ATTR_CHAR(c, "play", 0, t_life, play);
    CLASS_ATTR_STYLE_LABEL(c, "play", 0, "onoff", "Play");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"play",0,"0");
	CLASS_ATTR_ACCESSORS(c, "play", (method)NULL, (method)life_setattr_play);
	CLASS_ATTR_BASIC(c, "play", 0);
    // @description Toggles the sequencing of every newly created cell, as well as
    // the proper note-offs for no-longer-active cells.

	CLASS_ATTR_CHAR(c, "extendedplay", 0, t_life, extended_playout_data);
    CLASS_ATTR_STYLE_LABEL(c, "extendedplay", 0, "onoff", "Send Extended Playout Data");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"extendedplay",0,"0");
    // @description Toggles the ability to send extended playout information about cells.

	CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	CLASS_STICKY_ATTR(c,"category",0,"Settings");
	
	CLASS_ATTR_LONG(c, "size", 0, t_life, size);
    CLASS_ATTR_STYLE_LABEL(c, "size", 0, "text", "World Size");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"size",0,"101");
	CLASS_ATTR_FILTER_MIN(c, "size", 1);
	CLASS_ATTR_ACCESSORS(c, "size", (method)NULL, (method)life_setattr_size);
	CLASS_ATTR_BASIC(c, "size", 0);
    // @description Sets the world horizontal and vertical size (in cells)
	
	DADAOBJ_CLASS_ATTR_CHAR_SUBSTRUCTURE(c, LLLL_OBJ_UI, "lattice", 0, t_dadaobj, m_geometry, t_geometry_manager, lattice);
    CLASS_ATTR_STYLE_LABEL(c, "lattice", 0, "enumindex", "Lattice Type");
	CLASS_ATTR_ENUMINDEX(c,"lattice", 0, "Square Triangular"); 
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"lattice",0,"0");
    CLASS_ATTR_BASIC(c, "lattice", 0);
    // @description Sets the lattice type (either 0 = square, which is the default, or 1 = triangular)

	CLASS_ATTR_LONG_VARSIZE (c, "born", 0, t_life, num_born, num_born_size, DADA_LIFE_MAX_NUM_BORN_SIZE);
    CLASS_ATTR_STYLE_LABEL(c, "born", 0, "text", "Born");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"born",0,"3");
	// @description Lists all the possibilities for the number of neighbours a dead cell must have in order to be born

	CLASS_ATTR_LONG_VARSIZE (c, "stayalive", 0, t_life, num_stay_alive, num_stay_alive_size, DADA_LIFE_MAX_NUM_STAY_ALIVE_SIZE);
    CLASS_ATTR_STYLE_LABEL(c, "stayalive", 0, "text", "Stay Alive");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"stayalive",0,"2 3");
	// @description Lists all the possibilities for the number a living cell must have in order to stay alive
	
	CLASS_ATTR_LONG (c, "border", 0, t_life, border);
    CLASS_ATTR_STYLE_LABEL(c, "border", 0, "enumindex", "Border Handling");
	CLASS_ATTR_ENUMINDEX(c,"border", 0, "Dead Outside Wrap Kill Live"); 
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"border",0,"0");
	// @description Sets the border conditions, establishing how the cells just beyond the world limits should be considered

	
	CLASS_ATTR_SYM(c, "cents", 0, t_life, cents_eq_as_sym);
	CLASS_ATTR_STYLE_LABEL(c,"cents",0,"text","Cents Equation");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"cents",0,"\"6000 + 100 * x + 100 * y\"");
	CLASS_ATTR_ACCESSORS(c, "cents", (method)NULL, (method)life_setattr_cents);
	// @description Sets the equation for the cents associated to each cell.
    // For instance, "6000 + 700 * x, + 500 * y" represents a standard Tonnetz. <br />
    // You can substitute this equation with an explicit llll containing the pitch of each cell in the world matrix, in this case
    // <o>dada.life</o> expects an llll containing a matrix with <m>size</m> rows and <m>size</m> columns
    // (see <m>size</m> attribute). <br />

	CLASS_ATTR_SYM(c, "velocity", 0, t_life, vels_eq_as_sym);
	CLASS_ATTR_STYLE_LABEL(c,"velocity",0,"text","Velocity Equation");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"velocity",0,"\"100\"");
	CLASS_ATTR_ACCESSORS(c, "velocity", (method)NULL, (method)life_setattr_velocity);
	// @description Sets the equation for the velocity associated to each cell
	
	CLASS_ATTR_CHAR(c, "customrule", 0, t_life, use_custom_rule);
    CLASS_ATTR_STYLE_LABEL(c, "customrule", 0, "onoff", "Use Custom Rule");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"customrule",0,"0");
    // @description Toggles the usage of the possibly defined custom rule for the automaton.
    // The custom rule must be written in C and sent via the <m>rule</m> message.

	CLASS_ATTR_LONG(c, "neighborhood", 0, t_life, neighborhood_size);
    CLASS_ATTR_STYLE_LABEL(c, "neighborhood", 0, "text", "Neighborhood Range");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"neighborhood",0,"1");
	CLASS_ATTR_FILTER_MIN(c, "neighborhood", 0);
    // @description Sets the neighborhood size (for the <m>born</m> and <m>stayalive</m> attributes,
    // as well as for the custom rule).
	
    CLASS_ATTR_DOUBLE(c, "randomdensity", 0, t_life, default_random_density);
    CLASS_ATTR_STYLE_LABEL(c, "randomdensity", 0, "text", "Default Random Point Density");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"randomdensity",0,"0.5");
    CLASS_ATTR_FILTER_MIN(c, "randomdensity", 0);
    // @description Sets the default density for random generation of points on the lattice (in response to a <m>random</m> message,
    // or to popup or keyboard requests).
	
    
    
	CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	CLASS_STICKY_ATTR(c,"category",0,"Appearance");

	CLASS_ATTR_LONG(c, "numcandycane", 0, t_life, num_candycane);
    CLASS_ATTR_STYLE_LABEL(c, "numcandycane", 0, "text", "Alternating Candycane Colors");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"numcandycane",0,"8");
    // @description Sets the number of alternating candycane colors.
    // Only pertinent if <m>colormap</m> is set to Candycane.
	
	CLASS_ATTR_CHAR(c, "showfocus", 0, t_life, show_focus);
    CLASS_ATTR_STYLE_LABEL(c, "showfocus", 0, "onoff", "Show Focus");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showfocus",0,"1");
    // @description Toggles the ability to display a thicker border when the object has focus.
	
	CLASS_ATTR_CHAR(c,"shownotes",0, t_life, show_notes);
	CLASS_ATTR_STYLE_LABEL(c,"shownotes",0,"onoff","Show Pitches As Colors");
    CLASS_ATTR_ENUMINDEX(c,"shownotes", 0, "Don't Colors Wrapped Colors");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"shownotes", 0, "1");
	CLASS_ATTR_BASIC(c, "shownotes", 0);
    // @description Toggles the ability to display the pitches by coloring the cells background. Three modes are available:
    // Don't: don't show notes as colors; <br />
    // Colors: show notes as colors red to violet (the defined <m>minpitch</m> is mapped to red, the defined <m>maxpitch</m> is mapped to violet,
    // anything in between is interpolated; anything beyond is clipped); <br />
    // Wrapped Colors: show notes as colors, where the color spectrum correspond to each musical octave, and octaves are mapped to different saturation.

	CLASS_ATTR_DOUBLE(c, "minpitch", 0, t_life, min_pitch);
    CLASS_ATTR_STYLE_LABEL(c, "minpitch", 0, "text", "Minimum Pitch");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"minpitch",0,"1200");
    // @description Sets the minimum pitch (in midicents) representable by a color.
    // Such pitch will be associated to the red color.
 	
	CLASS_ATTR_DOUBLE(c, "maxpitch", 0, t_life, max_pitch);
    CLASS_ATTR_STYLE_LABEL(c, "maxpitch", 0, "text", "Maximum Pitch");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"maxpitch",0,"10800");
    // @description Sets the maximum pitch (in midicents) representable by a color.
    // Such pitch will be associated to the violet color.
	
	CLASS_ATTR_CHAR(c,"showvelocity",0, t_life, show_velocity);
	CLASS_ATTR_STYLE_LABEL(c,"showvelocity",0,"enumindex","Show Velocity");
	CLASS_ATTR_ENUMINDEX(c,"showvelocity", 0, "None Transparency Darkness Lightness"); 
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showvelocity", 0, "1");
	CLASS_ATTR_BASIC(c, "showvelocity", 0);
    // @description Toggles the way in which velocities are displayed: <br />
    // None: velocities are not displayed; <br />
    // Transparency: small velocities are mapped on more transparent colors; <br />
    // Lightness: small velocities are mapped on lighter colors; <br />
    // Darkness: small velocities are mapped on darker colors. <br />

	CLASS_ATTR_CHAR(c,"shape",0, t_life, shape);
	CLASS_ATTR_STYLE_LABEL(c,"shape",0,"enumindex","Shape");
	CLASS_ATTR_ENUMINDEX(c,"shape", 0, "Square Hexagon Circle Sprite"); 
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"shape", 0, "0");
    // @description Sets the shape of the cells. If "Sprite" is chosen, then the <m>sprite</m> attribute must point to a valid image file.

	CLASS_ATTR_SYM(c,"sprite",0, t_life, sprite_sym);
	CLASS_ATTR_STYLE_LABEL(c,"sprite",0,"file","Sprite");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"sprite", 0, "");
    // @description Sets the filename of an image to be used as a sprite shape (see <m>shape</m> attribute).
	
	CLASS_ATTR_CHAR(c,"colormap",0, t_life, color_mapping);
	CLASS_ATTR_STYLE_LABEL(c,"colormap",0,"enumindex","Value To Color Mapping");
	CLASS_ATTR_ENUMINDEX(c,"colormap", 0, "None Candycane Color Scale Color Spectrum Random Custom"); 
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"colormap", 0, "1");
    // @descriptions Sets the mapping between cell values and corresponding color: <br />
    // None: no mapping: cell color is always the one defined by <m>cellcolor</m>; <br />
    // Candycane: colors are chosen via the candycane; <br />
    // Color Scale: cell color is the one defined by <m>cellcolor</m>, but rescaled so that it is lighter for small cells value (range is from 1 to <m>mapmax</m>); <br />
    // Color Spectrum: cell color ranges from red to violet (for cells values from 1 to <m>mapmax</m>);<br />
    // Random: cell color is chosen randomly;<br />
    // Custom: cell color is defined via <m>cellred</m>, <m>cellgreen</m>, <m>cellblue</m>, <m>cellalpha</m>.<br />

	CLASS_ATTR_SYM(c, "cellsize", 0, t_life, size_eq_as_sym);
	CLASS_ATTR_STYLE_LABEL(c,"cellsize",0,"text","Cell Size Equation");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"cellsize",0,"");
	CLASS_ATTR_ACCESSORS(c, "cellsize", (method)NULL, (method)life_setattr_cellsize);
	// @descriptions Sets the equation for the size of each cell. You can have "cell" (cell value), "x" and "y" (coordinates) as variables.
	
	CLASS_ATTR_SYM(c, "cellalpha", 0, t_life, alpha_eq_as_sym);
	CLASS_ATTR_STYLE_LABEL(c,"cellalpha",0,"text","Cell Alpha Equation");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"cellalpha",0,"");
	CLASS_ATTR_ACCESSORS(c, "cellalpha", (method)NULL, (method)life_setattr_cellalpha);
	// @descriptions Sets the equation for the transparency of each cell. You can have "cell" (cell value), "x" and "y" (coordinates) as variables.
    // Only accessible if <m>colormap</m> is set to custom.

	
	CLASS_ATTR_SYM(c, "cellred", 0, t_life, red_eq_as_sym);
	CLASS_ATTR_STYLE_LABEL(c,"cellred",0,"text","Cell Red Equation");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"cellred",0,"");
	CLASS_ATTR_ACCESSORS(c, "cellred", (method)NULL, (method)life_setattr_cellred);
	// @descriptions Sets the equation for the red component of each cell. You can have "cell" (cell value), "x" and "y" (coordinates) as variables.
    // Only accessible if <m>colormap</m> is set to custom.

	
	CLASS_ATTR_SYM(c, "cellgreen", 0, t_life, green_eq_as_sym);
	CLASS_ATTR_STYLE_LABEL(c,"cellgreen",0,"text","Cell Green Equation");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"cellgreen",0,"");
	CLASS_ATTR_ACCESSORS(c, "cellgreen", (method)NULL, (method)life_setattr_cellgreen);
	// @descriptions Sets the equation for the green component of each cell. You can have "cell" (cell value), "x" and "y" (coordinates) as variables.
    // Only accessible if <m>colormap</m> is set to custom.


	CLASS_ATTR_SYM(c, "cellblue", 0, t_life, blue_eq_as_sym);
	CLASS_ATTR_STYLE_LABEL(c,"cellblue",0,"text","Cell Blue Equation");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"cellblue",0,"");
	CLASS_ATTR_ACCESSORS(c, "cellblue", (method)NULL, (method)life_setattr_cellblue);
	// @descriptions Sets the equation for the blue component of each cell. You can have "cell" (cell value), "x" and "y" (coordinates) as variables.
    // Only accessible if <m>colormap</m> is set to custom.

	
	CLASS_ATTR_DOUBLE(c,"sizefactor",0, t_life, size_factor);
	CLASS_ATTR_STYLE_LABEL(c,"sizefactor",0,"text","Cell Size Factor");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"sizefactor", 0, "0.75");
    // @description Sets a factor for the cell coverage when a cell is "full".
	
	CLASS_ATTR_LONG(c,"mapmax",0, t_life, max_val_for_mapping);
	CLASS_ATTR_STYLE_LABEL(c,"mapmax",0,"text","Maximum Color Mapping Value");
	CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"mapmax", 0, "100");
    // @description Sets the maximum color mapping value for custom mapping rules (see <m>colormap</m>).
	
	
	CLASS_STICKY_ATTR_CLEAR(c, "category");

	
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	life_class = c;
    dadaobj_class_add_fileusage_method(c);

	dev_post("dada.life compiled %s %s", __DATE__, __TIME__);
	return;
}


void life_sprite_reinit(t_life *x)
{
	sprite_free(&x->sprite);
	sprite_init(&x->sprite, gensym("lifesprite"), NULL, true, 10, 1, &x->sprite_sym);
}



t_max_err life_notify(t_life *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	if (msg == _sym_attr_modified) {
		t_symbol *attr_name = (t_symbol *)object_method((t_object *)data, _sym_getname);
		if (attr_name == gensym("lattice") || attr_name == gensym("center") || attr_name == gensym("shownotes") || attr_name == gensym("showvelocity")) {
			jbox_invalidate_layer((t_object *)x, NULL, gensym("notes"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("world"));
			jbox_redraw((t_jbox *)x);
			
		} else if (attr_name == _llllobj_sym_zoom || attr_name == gensym("sizefactor")) {
			if (attr_name == _llllobj_sym_zoom && x->sprite_sym)
				life_sprite_reinit(x);
            jbox_invalidate_layer((t_object *)x, NULL, gensym("world"));
            jbox_redraw((t_jbox *)x);
			
		} else if (attr_name == gensym("sprite_sym") && x->sprite_sym) {
			life_sprite_reinit(x);
			jbox_invalidate_layer((t_object *)x, NULL, gensym("notes"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("world"));
			jbox_redraw((t_jbox *)x);
			
		} else if (attr_name == gensym("size")) {
			build_cents_grid(x);
			build_velocity_grid(x);
			jbox_invalidate_layer((t_object *)x, NULL, gensym("notes"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("world"));
			jbox_redraw((t_jbox *)x);
			
		} else if (attr_name == gensym("born")) {
			long i;
			x->num_born_bitfield = 0;
			for (i = 0; i < x->num_born_size; i++) {
				long this_n = x->num_born[i];
				if (this_n >= 0 && this_n < 64)
					x->num_born_bitfield |= (1 << this_n);
			}
			jbox_redraw((t_jbox *)x);
			
		} else if (attr_name == gensym("stayalive")) {
			long i;
			x->num_stay_alive_bitfield = 0;
			for (i = 0; i < x->num_stay_alive_size; i++) {
				long this_n = x->num_stay_alive[i];
				if (this_n >= 0 && this_n < 64)
					x->num_stay_alive_bitfield |= (1 << this_n);
			}
			jbox_redraw((t_jbox *)x);
			
		} else if (attr_name == gensym("neighborhood")) {
			long i;
			long matrix_size = x->neighborhood_size * 2 + 1;
			bach_freeptr(x->neighborhood_callback);
			x->neighborhood_callback = (t_cell **)bach_newptr(matrix_size * sizeof(t_cell *));
			for (i = 0; i < matrix_size; i++)
				x->neighborhood_callback[i] = (t_cell *)bach_newptr(matrix_size * sizeof(t_cell));
			
		} else if (attr_name == gensym("colormap")) {
			object_attr_setdisabled((t_object *)x, gensym("cellred"), x->color_mapping != DADA_LIFE_COLORMAP_CUSTOM);
			object_attr_setdisabled((t_object *)x, gensym("cellgreen"), x->color_mapping != DADA_LIFE_COLORMAP_CUSTOM);
			object_attr_setdisabled((t_object *)x, gensym("cellblue"), x->color_mapping != DADA_LIFE_COLORMAP_CUSTOM);
			jbox_invalidate_layer((t_object *)x, NULL, gensym("world"));

		} else if (attr_name == gensym("customrule")) {
			object_attr_setdisabled((t_object *)x, gensym("numcandycane"), x->use_custom_rule == 0);
			object_attr_setdisabled((t_object *)x, gensym("candycane2"), x->use_custom_rule == 0);
			object_attr_setdisabled((t_object *)x, gensym("candycane3"), x->use_custom_rule == 0);
			object_attr_setdisabled((t_object *)x, gensym("candycane4"), x->use_custom_rule == 0);
			object_attr_setdisabled((t_object *)x, gensym("candycane5"), x->use_custom_rule == 0);
			object_attr_setdisabled((t_object *)x, gensym("candycane6"), x->use_custom_rule == 0);
			object_attr_setdisabled((t_object *)x, gensym("candycane7"), x->use_custom_rule == 0);
			object_attr_setdisabled((t_object *)x, gensym("candycane8"), x->use_custom_rule == 0);
			object_attr_setdisabled((t_object *)x, gensym("colormap"), x->use_custom_rule == 0);
			object_attr_setdisabled((t_object *)x, gensym("sizemap"), x->use_custom_rule == 0);

			jbox_invalidate_layer((t_object *)x, NULL, gensym("notes"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("world"));
		} else
			jbox_invalidate_layer((t_object *)x, NULL, gensym("world"));

		
		if (!x->itsme)
			process_change(x);
	}
	
	return MAX_ERR_NONE;
}


t_max_err life_setattr_play(t_life *x, t_object *attr, long ac, t_atom *av)
{
	if (ac && av && is_atom_number(av)) {
		char old_play = x->play, new_play = (atom_getlong(av) == 0 ? 0 : 1);
		if (old_play != new_play) {
			x->play = new_play;
			if (!x->creating_new_obj) {
                dadaobj_send_notification_sym(dadaobj_cast(x), new_play ? _llllobj_sym_play : _llllobj_sym_stop);
				if (old_play)
					send_all_noteoffs(x);
				else
					send_all_noteons(x);
			}
		}
	}
	return MAX_ERR_NONE;
}

void build_cents_grid(t_life *x)
{
	long i, j;
	if (x->cents_lexpr) {
		for (i = -x->offset; i + x->offset < x->size; i++) {
			for (j = x->offset; j - x->offset > -x->size; j--) {
				long idx = coord_to_idx(x, i, j);
				t_hatom vars[2];
				t_hatom *res = NULL;
				hatom_setlong(vars, i);
				hatom_setlong(vars + 1, j);
				res = lexpr_eval(x->cents_lexpr, vars);
				x->n_world_metadata[idx].pitch_mc = hatom_getdouble(res);
				bach_freeptr(res);
			}
		}
	}	
}


void copy_world(t_cell *src, t_cell *dest, long src_start_i, long src_start_j, 
				long dest_start_i, long dest_start_j,
				long old_size, long new_size, long copy_size)
{
	long i, j;
	for (i = 0; i < copy_size; i++)
		for (j = 0; j < copy_size; j++)
			dest[(dest_start_i + i) * new_size + dest_start_j + j] = src[(src_start_i + i) * old_size + src_start_j + j];
}

t_max_err life_setattr_size(t_life *x, t_object *attr, long ac, t_atom *av)
{
	if (ac > 0) {
		// preserve world
		long old_size = x->size;
		long new_size = MIN(DADA_LIFE_MAX_SIZE, MAX(1, atom_getlong(av)));
		long old_offset = x->offset;
		long new_offset = (new_size - 1)/2;
		
		if (old_size > new_size) {
			copy_world(x->n_world[x->n_thisworld], x->n_world[1 - x->n_thisworld], 
					   old_offset - new_offset, old_offset - new_offset, 0, 0, old_size, new_size, new_size);
		} else if (new_size > old_size) {
			long i, max = new_size * new_size;
			for (i = 0; i < max; i++)
				x->n_world[1 - x->n_thisworld][i] = 0;
			copy_world(x->n_world[x->n_thisworld], x->n_world[1 - x->n_thisworld], 
					   0, 0, new_offset - old_offset, new_offset - old_offset, old_size, new_size, old_size);
		}
		
		x->size = new_size;
		x->n_thisworld = 1 - x->n_thisworld;
		x->offset = new_offset;
	}
	return MAX_ERR_NONE;
}


t_max_err life_setattr_cellsize(t_life *x, t_object *attr, long ac, t_atom *av)
{
	if (ac > 0) {
		char *text = NULL;
		const char *subs[] = {"cell", "x", "y"};		
		long size;
		
		t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, NULL, ac, av, LLLL_PARSE_CLONE);
		atom_gettext(ac, av, &size, &text, OBEX_UTIL_ATOM_GETTEXT_SYM_NO_QUOTE | LLLL_D_PARENS);
		
		if (text && *text) {
			// Equation introduced
			x->size_eq_as_sym = gensym(text);
			
			if (x->size_lexpr)
				lexpr_free(x->size_lexpr);
			
			if (!(x->size_lexpr = lexpr_new(ac, av, 3, subs, (t_object *)x)))
				object_error((t_object *)x, "Error: wrong cellsize expression introduced!");
		} else {
			x->size_eq_as_sym = gensym("");
			if (x->size_lexpr)
				lexpr_free(x->size_lexpr);
		}
		
		llll_free(parsed);
		bach_freeptr(text);
		jbox_invalidate_layer((t_object *)x, NULL, gensym("world"));
		jbox_redraw((t_jbox *)x);
		
	} else {
		x->size_eq_as_sym = gensym("");
		if (x->size_lexpr)
			lexpr_free(x->size_lexpr);
	}
	
	return MAX_ERR_NONE;
}

t_max_err life_setattr_cellalpha(t_life *x, t_object *attr, long ac, t_atom *av)
{
	if (ac > 0) {
		char *text = NULL;
		const char *subs[] = {"cell", "x", "y"};		
		long size;
		
		t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, NULL, ac, av, LLLL_PARSE_CLONE);
		atom_gettext(ac, av, &size, &text, OBEX_UTIL_ATOM_GETTEXT_SYM_NO_QUOTE | LLLL_D_PARENS);
		
		if (text && *text) {
			// Equation introduced
			x->alpha_eq_as_sym = gensym(text);
			
			if (x->alpha_lexpr)
				lexpr_free(x->alpha_lexpr);
			
			if (!(x->alpha_lexpr = lexpr_new(ac, av, 3, subs, (t_object *)x)))
				object_error((t_object *)x, "Error: wrong cellalpha expression introduced!");
		} else {
			x->alpha_eq_as_sym = gensym("");
			if (x->alpha_lexpr)
				lexpr_free(x->alpha_lexpr);
		}
			
		llll_free(parsed);
		bach_freeptr(text);
		jbox_invalidate_layer((t_object *)x, NULL, gensym("world"));
		jbox_redraw((t_jbox *)x);
		
	} else { 
		
		x->alpha_eq_as_sym = gensym("");
		if (x->alpha_lexpr)
			lexpr_free(x->alpha_lexpr);
	}
	return MAX_ERR_NONE;
}

t_max_err life_setattr_cellred(t_life *x, t_object *attr, long ac, t_atom *av)
{
	if (ac > 0) {
		char *text = NULL;
		const char *subs[] = {"cell", "x", "y"};		
		long size;
		
		t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, NULL, ac, av, LLLL_PARSE_CLONE);
		atom_gettext(ac, av, &size, &text, OBEX_UTIL_ATOM_GETTEXT_SYM_NO_QUOTE | LLLL_D_PARENS);
		
		if (text && *text) {
			// Equation introduced
			x->red_eq_as_sym = gensym(text);
			
			if (x->red_lexpr)
				lexpr_free(x->red_lexpr);
			
			if (!(x->red_lexpr = lexpr_new(ac, av, 3, subs, (t_object *)x)))
				object_error((t_object *)x, "Error: wrong cellred expression introduced!");
		} else {
			x->red_eq_as_sym = gensym("");
			if (x->red_lexpr)
				lexpr_free(x->red_lexpr);
		}
		
		llll_free(parsed);
		bach_freeptr(text);
		jbox_invalidate_layer((t_object *)x, NULL, gensym("world"));
		jbox_redraw((t_jbox *)x);
		
	} else { 
		
		x->red_eq_as_sym = gensym("");
		if (x->red_lexpr)
			lexpr_free(x->red_lexpr);
	}
	return MAX_ERR_NONE;
}


t_max_err life_setattr_cellgreen(t_life *x, t_object *attr, long ac, t_atom *av)
{
	if (ac > 0) {
		char *text = NULL;
		const char *subs[] = {"cell", "x", "y"};		
		long size;
		
		t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, NULL, ac, av, LLLL_PARSE_CLONE);
		atom_gettext(ac, av, &size, &text, OBEX_UTIL_ATOM_GETTEXT_SYM_NO_QUOTE | LLLL_D_PARENS);
		
		if (text && *text) {
			// Equation introduced
			x->green_eq_as_sym = gensym(text);
			
			if (x->green_lexpr)
				lexpr_free(x->green_lexpr);
			
			if (!(x->green_lexpr = lexpr_new(ac, av, 3, subs, (t_object *)x)))
				object_error((t_object *)x, "Error: wrong cellgreen expression introduced!");
		} else {
			x->green_eq_as_sym = gensym("");
			if (x->green_lexpr)
				lexpr_free(x->green_lexpr);
		}
		
		llll_free(parsed);
		bach_freeptr(text);
		jbox_invalidate_layer((t_object *)x, NULL, gensym("world"));
		jbox_redraw((t_jbox *)x);
		
	} else { 
		
		x->green_eq_as_sym = gensym("");
		if (x->green_lexpr)
			lexpr_free(x->green_lexpr);
	}
	return MAX_ERR_NONE;
}

t_max_err life_setattr_cellblue(t_life *x, t_object *attr, long ac, t_atom *av)
{
	if (ac > 0) {
		char *text = NULL;
		const char *subs[] = {"cell", "x", "y"};		
		long size;
		
		t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, NULL, ac, av, LLLL_PARSE_CLONE);
		atom_gettext(ac, av, &size, &text, OBEX_UTIL_ATOM_GETTEXT_SYM_NO_QUOTE | LLLL_D_PARENS);
		
		if (text && *text) {
			// Equation introduced
			x->blue_eq_as_sym = gensym(text);
			
			if (x->blue_lexpr)
				lexpr_free(x->blue_lexpr);
			
			if (!(x->blue_lexpr = lexpr_new(ac, av, 2, subs, (t_object *)x)))
				object_error((t_object *)x, "Error: wrong cellblue expression introduced!");
		} else {
			x->blue_eq_as_sym = gensym("");
			if (x->blue_lexpr)
				lexpr_free(x->blue_lexpr);
		}
		
		llll_free(parsed);
		bach_freeptr(text);
		jbox_invalidate_layer((t_object *)x, NULL, gensym("world"));
		jbox_redraw((t_jbox *)x);
		
	} else { 
		
		x->blue_eq_as_sym = gensym("");
		if (x->blue_lexpr)
			lexpr_free(x->blue_lexpr);
	}
	return MAX_ERR_NONE;
}



t_max_err life_setattr_cents(t_life *x, t_object *attr, long ac, t_atom *av)
{
	if (ac > 0) {
		char *text = NULL;
		const char *subs[] = {"x", "y"};
		long size;
		
		t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, NULL, ac, av, LLLL_PARSE_CLONE);
		atom_gettext(ac, av, &size, &text, OBEX_UTIL_ATOM_GETTEXT_SYM_NO_QUOTE | LLLL_D_PARENS);

		if (parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM && hatom_getsym(&parsed->l_head->l_hatom) == gensym("custom")) {
			// nothing to do
		} else if (strchr(text, 'x') || strchr(text, 'y') || parsed->l_depth != 2) {
			// Equation introduced
			x->cents_eq_as_sym = gensym(text);
			
			if (x->cents_lexpr)
				lexpr_free(x->cents_lexpr);
			
			if (!(x->cents_lexpr = lexpr_new(ac, av, 2, subs, (t_object *)x)))
				object_error((t_object *)x, "Error: wrong cents expression introduced!");
			
			build_cents_grid(x);
		} else {
			// explicit llll introduced
			x->vels_eq_as_sym = gensym("custom");
			life_set_cents(x, parsed);
			if (x->cents_lexpr)
				lexpr_free(x->cents_lexpr);
		}
			
		llll_free(parsed);
		bach_freeptr(text);
		jbox_invalidate_layer((t_object *)x, NULL, gensym("notes"));
		jbox_redraw((t_jbox *)x);
	}
	return MAX_ERR_NONE;
}

void build_velocity_grid(t_life *x)
{
	long i, j;
	if (x->vels_lexpr) {
		for (i = -x->offset; i + x->offset < x->size; i++) {
			for (j = x->offset; j - x->offset > -x->size; j--) {
				t_hatom vars[2];
				t_hatom *res = NULL;
				hatom_setlong(vars, i);
				hatom_setlong(vars + 1, j);
				res = lexpr_eval(x->vels_lexpr, vars);
				x->n_world_metadata[coord_to_idx(x, i, j)].velocity = CLAMP(round(hatom_getdouble(res)), DADA_MIN_VELOCITY, DADA_MAX_VELOCITY);
				bach_freeptr(res);
			}
		}
	}
}


t_max_err life_setattr_velocity(t_life *x, t_object *attr, long ac, t_atom *av)
{
	if (ac > 0) {
		char *text = NULL;
		const char *subs[] = {"x","y"};		
		long size;
		
		t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, NULL, ac, av, LLLL_PARSE_CLONE);
		atom_gettext(ac, av, &size, &text, OBEX_UTIL_ATOM_GETTEXT_SYM_NO_QUOTE | LLLL_D_PARENS);
		
		if (parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM && hatom_getsym(&parsed->l_head->l_hatom) == gensym("custom")) {
			// nothing to do
		} else if (strchr(text, 'x') || strchr(text, 'y') || parsed->l_depth != 2) {
			// Equation introduced
			x->vels_eq_as_sym = gensym(text);
			
			if (x->vels_lexpr)
				lexpr_free(x->vels_lexpr);
			
			if (!(x->vels_lexpr = lexpr_new(ac, av, 2, subs, (t_object *)x)))
				object_error((t_object *)x, "Error: wrong velocity expression introduced!");
			
			
			build_velocity_grid(x);
		} else {
			// explicit llll introduced
			x->vels_eq_as_sym = gensym("custom");
			life_set_velocity(x, parsed);
			if (x->vels_lexpr)
				lexpr_free(x->vels_lexpr);
		}
		
		llll_free(parsed);
		bach_freeptr(text);
		jbox_invalidate_layer((t_object *)x, NULL, gensym("notes"));
		jbox_redraw((t_jbox *)x);
	}
	return MAX_ERR_NONE;
}





void life_begin_preset(t_life *x, t_symbol *s, long argc, t_atom *argv)
{
	dadaobj_begin_preset(dadaobj_cast(x), s, argc, argv);
}

void life_restore_preset(t_life *x, t_symbol *s, long argc, t_atom *argv)
{
	dadaobj_restore_preset(dadaobj_cast(x), s, argc, argv);
}

void life_end_preset(t_life *x)
{
	dadaobj_end_preset(dadaobj_cast(x));
}

void life_preset(t_life *x) {
	dadaobj_preset(dadaobj_cast(x));
}


void life_jsave(t_life *x, t_dictionary *d)
{
	if (x->b_ob.d_ob.save_data_with_patcher){
		if (x->b_ob.r_ob.l_dictll) {
			llll_store_in_dictionary(x->b_ob.r_ob.l_dictll, d, "life_data", NULL);
		} else {
			t_llll *data = life_get_state(x);
			llll_store_in_dictionary(data, d, "life_data", NULL);
			llll_free(data);
		}
	} 
}
		

t_llll *life_get_world(t_life *x)
{
	t_llll *out_ll = llll_get();
	t_cell *this_new_world = x->n_world[x->n_thisworld];
	long row_count;
	for (row_count = 0; row_count < x->size; row_count++) {
		t_llll *row_ll = llll_get();
		long col_count;
		for (col_count = 0; col_count < x->size; col_count++) 
			llll_appendlong(row_ll, *this_new_world++, 0, WHITENULL_llll);
		llll_appendllll(out_ll, row_ll, 0, WHITENULL_llll);
	}
	llll_prependsym(out_ll, gensym("world"), 0, WHITENULL_llll);
	return out_ll;
}


t_llll *life_get_notes(t_life *x)
{
	t_llll *out_ll = llll_get();
	t_llll *pitch = llll_get(), *vel = llll_get();
	long i, j;
	t_life_metadata *this_metadata = x->n_world_metadata;
	for (i = 0; i < x->size; i++) {
		t_llll *pitch_row = llll_get();
		t_llll *vel_row = llll_get();
		for (j = 0; j < x->size; j++) {
			llll_appenddouble(pitch_row, this_metadata->pitch_mc, 0, WHITENULL_llll);
			llll_appendlong(vel_row, this_metadata->velocity, 0, WHITENULL_llll);
			this_metadata++;
		}
		llll_appendllll(pitch, pitch_row, 0, WHITENULL_llll);
		llll_appendllll(vel, vel_row, 0, WHITENULL_llll);
	}
	llll_prependsym(pitch, gensym("cents"), 0, WHITENULL_llll);
	llll_prependsym(vel, gensym("velocity"), 0, WHITENULL_llll);

	llll_appendllll(out_ll, pitch, 0, WHITENULL_llll);
	llll_appendllll(out_ll, vel, 0, WHITENULL_llll);
	
	llll_prependsym(out_ll, gensym("notes"), 0, WHITENULL_llll);
	return out_ll;
}


t_llll *life_get_state_sel(t_life *x, char get_world, char get_notes)
{
	t_llll *data = llll_get();
	
    llll_appendsym(data, gensym("life"));
    
	if (get_world)
		llll_appendllll(data, life_get_world(x), 0, WHITENULL_llll);
	if (get_notes)
		llll_appendllll(data, life_get_notes(x), 0, WHITENULL_llll);
	
	return data;
}

t_llll *life_get_state(t_life *x)
{
	return life_get_state_sel(x, true, true);
}


void life_set_cents(t_life *x, t_llll *cents)
{
	long i, j;
	if (cents && cents->l_head) {
		t_llllelem *elem = cents->l_head, *cell;
		if (hatom_gettype(&elem->l_hatom) == H_SYM)
			elem = elem->l_next;
		
		for (i = 0; i < x->size && elem; i++, elem = elem->l_next) {
			if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
				t_llll *row = hatom_getllll(&elem->l_hatom);
				for (j = 0, cell = row->l_head; j < x->size && cell; j++, cell = cell->l_next) {
					if (is_hatom_number(&cell->l_hatom)) {
						x->n_world_metadata[i * x->size + j].pitch_mc = hatom_getdouble(&cell->l_hatom);
					}
				}
			}
		}
	}
}

void life_set_velocity(t_life *x, t_llll *velocity)
{
	long i, j;
	if (velocity && velocity->l_head) {
		t_llllelem *elem = velocity->l_head, *cell;
		if (hatom_gettype(&elem->l_hatom) == H_SYM)
			elem = elem->l_next;
		
		for (i = 0; i < x->size && elem; i++, elem = elem->l_next) {
			if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
				t_llll *row = hatom_getllll(&elem->l_hatom);
				for (j = 0, cell = row->l_head; j < x->size && cell; j++, cell = cell->l_next) {
					if (is_hatom_number(&cell->l_hatom))
						x->n_world_metadata[i * x->size + j].velocity = CLAMP(hatom_getlong(&cell->l_hatom), DADA_MIN_VELOCITY, DADA_MAX_VELOCITY);
				}
			}
		}
	}
}

void life_set_notes(t_life *x, t_llll *notes)
{
	if (notes && notes->l_head && notes->l_head->l_next) {
		t_llllelem *temp = notes->l_head->l_next;
		t_llll *ll;
		for (; temp; temp = temp->l_next) {
			if (hatom_gettype(&temp->l_hatom) == H_LLLL && (ll = hatom_getllll(&temp->l_hatom)) && ll->l_head &&
				hatom_gettype(&ll->l_head->l_hatom) == H_SYM) {
				t_symbol *sym = hatom_getsym(&ll->l_head->l_hatom);
				if (sym == gensym("cents")) 
					life_set_cents(x, ll);
				else if (sym == gensym("velocity"))
					life_set_velocity(x, ll);
			}
		}
	}
	jbox_invalidate_layer((t_object *)x, NULL, gensym("notes"));
}


void life_set_world(t_life *x, t_llll *world)
{
	life_clear(x, false);
	
	if (x->play && !x->creating_new_obj && !x->itsme)
		send_all_noteoffs(x);
	
	if (world && world->l_head && world->l_head->l_next) {
		t_llllelem *elem, *elem2;
		long row, col;
		for (row = 0, elem = world->l_head->l_next; elem && row < x->size; row++, elem = elem->l_next) {
			if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
				t_llll *row_ll = hatom_getllll(&elem->l_hatom);
				for (col = 0, elem2 = row_ll->l_head; elem2 && col < x->size; col++, elem2 = elem2->l_next) {
					if (is_hatom_number(&elem2->l_hatom)) 
						x->n_world[x->n_thisworld][row * x->size + col] = hatom_getlong(&elem2->l_hatom);
				}
			}
		}
	}
	jbox_invalidate_layer((t_object *)x, NULL, gensym("world"));
}

void life_set_state(t_life *x, t_llll *state)
{
	if (!state)
		return;

    x->itsme = true;

    t_llllelem *el;
    for (el = state->l_head; el; el = el->l_next) {
        if (hatom_gettype(&el->l_hatom) == H_LLLL) {
            t_llll *ll = hatom_getllll(&el->l_hatom);
            if (ll && ll->l_head && hatom_gettype(&ll->l_head->l_hatom) == H_SYM) {
                t_symbol *router = hatom_getsym(&ll->l_head->l_hatom);
                if (router == gensym("world"))
                    life_set_world(x, ll);
                else if (router == gensym("notes"))
                    life_set_notes(x, ll);
            }
        }
    }
	
	x->itsme = false;
	jbox_redraw((t_jbox *)x);
}


void life_assist(t_life *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type bang/llll/anything @digest Incoming messages or state or bang to evolve
		sprintf(s, "llll/anything: Incoming messages or state or bang to evolve");
	} 
	else {
        char *type = NULL;
        llllobj_get_llll_outlet_type_as_string((t_object *) x, LLLL_OBJ_UI, a, &type);
        if (a == 0)	// @out 0 @type llll @digest Dump outlet
            sprintf(s, "llll (%s): Dump Outlet", type);
        else if (a == 1)	// @out 1 @type llll @digest Queries and notifications
            sprintf(s, "llll (%s): Queries and Notifications", type);
        else if (a == 2)	// @out 2 @type llll @digest Playout
            sprintf(s, "llll (%s): Playout", type);
        else 	// @out 3 @type bang @digest bang when object is changed via the interface
            sprintf(s, "bang when Changed");
	}
}

void life_free(t_life *x)
{
	
	object_free_debug(x->clang);
	if (x->cents_lexpr)
		lexpr_free(x->cents_lexpr);
	if (x->vels_lexpr)
		lexpr_free(x->vels_lexpr);
	if (x->alpha_lexpr)
		lexpr_free(x->alpha_lexpr);
	if (x->size_lexpr)
		lexpr_free(x->size_lexpr);
	if (x->red_lexpr)
		lexpr_free(x->red_lexpr);
	if (x->green_lexpr)
		lexpr_free(x->green_lexpr);
	if (x->blue_lexpr)
		lexpr_free(x->blue_lexpr);
	bach_freeptr(x->n_world[0]);
	bach_freeptr(x->n_world[1]);
	bach_freeptr(x->n_world_metadata);

	object_free_debug(x->n_proxy1);
dadaobj_jbox_free((t_dadaobj_jbox *)x); // jbox_free and llllobj_free are inside here
}

void life_iar(t_life *x)
{
    jbox_invalidate_layer((t_object *)x, NULL, gensym("notes"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("world"));
    jbox_redraw((t_jbox *)x);
}


void *life_new(t_symbol *s, long argc, t_atom *argv)
{
	t_life *x = NULL;
	t_dictionary *d = NULL;
	long boxflags;
	t_llll *llll_for_rebuild = NULL;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;    
	
	if ((x = (t_life *)object_alloc_debug(life_class))) {
        x->default_random_density = DADA_LIFE_DEFAULT_RANDOM_DENSITY;
		x->creating_new_obj = true;
		x->hovered_idx = -1;
		x->cents_lexpr = x->vels_lexpr = NULL;
		
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

		dadaobj_jbox_setup((t_dadaobj_jbox *)x, DADAOBJ_BBG | DADAOBJ_ZOOM | DADAOBJ_CENTEROFFSET | DADAOBJ_CHANGEDBANG | DADAOBJ_NOTIFICATIONS, build_pt(10., 10.), 2, 3, 2, (dada_paint_ext_fn)life_paint_ext, (invalidate_and_redraw_fn)life_iar, "vn", 2, "b444");
		dadaobj_addfunctions(dadaobj_cast(x), (dada_mousemove_fn)life_mousemove, NULL, NULL, (get_state_fn)life_get_state, (set_state_fn)life_set_state, NULL, NULL, NULL);


		x->n_world[0] = (t_cell *) bach_newptrclear(DADA_LIFE_MAX_SIZE * DADA_LIFE_MAX_SIZE * sizeof(t_cell));
		x->n_world[1] = (t_cell *) bach_newptrclear(DADA_LIFE_MAX_SIZE * DADA_LIFE_MAX_SIZE * sizeof(t_cell));
		x->n_world_metadata = (t_life_metadata *) bach_newptrclear(DADA_LIFE_MAX_SIZE * DADA_LIFE_MAX_SIZE * sizeof(t_life_metadata));
		x->n_thisworld = 0;

		long i;
		x->neighborhood_callback = (t_cell **) bach_newptrclear(3 * sizeof(t_cell *));
		for (i = 0; i < 3; i++)
			x->neighborhood_callback[i] = (t_cell *) bach_newptrclear(3 * sizeof(t_cell));
		
		x->size = 101;
		x->offset = 50;
		
		x->n_world[0][coord_to_idx(x, 0, 0)] = 1;
		x->n_world[0][coord_to_idx(x, 1, 0)] = 1;
		x->n_world[0][coord_to_idx(x, 2, 0)] = 1;
		x->n_world[0][coord_to_idx(x, 2, 1)] = 1;
		x->n_world[0][coord_to_idx(x, 1, 2)] = 1;
		
		
		// create clang object
		x->clang = (t_object *)object_new(CLASS_NOBOX, gensym("clang"), gensym("dadalife"));
		
		attr_dictionary_process(x,d);
		
		if ((llll_for_rebuild = llll_retrieve_from_dictionary(d, "life_data"))) { // new method
			llllobj_manage_dict_llll((t_object *)x, LLLL_OBJ_UI, llll_for_rebuild);
			life_set_state(x, llll_for_rebuild);
			llll_free(llll_for_rebuild);
		}
		
		jbox_ready((t_jbox *)x);
        
        dadaobj_set_current_version_number(dadaobj_cast(x));
		
		x->creating_new_obj = false;
	}
	return x;
}

void life_int(t_life *x, t_atom_long num)
{
	t_atom argv[1]; 
	atom_setlong(argv, num);
	life_anything(x, _sym_list, 1, argv);
}

void life_float(t_life *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	life_anything(x, _sym_list, 1, argv);
}




void life_step(t_life *x)
{
	t_cell *this_world = x->n_world[x->n_thisworld];
	t_cell *new_world = x->n_world[1 - x->n_thisworld];
	
	if (!x->use_custom_rule) {
		life_ezstep(this_world, new_world, x->size, x->neighborhood_size, (e_dada_life_border_behavior)x->border, (e_dada_lattice_types)x->b_ob.d_ob.m_geometry.lattice, x->num_born_bitfield, x->num_stay_alive_bitfield);
		x->n_thisworld = 1 - x->n_thisworld;
	} else if (x->custom_rule) {
		life_customstep(this_world, new_world, x->size, x->neighborhood_size, x->neighborhood_callback, (e_dada_life_border_behavior)x->border, (e_dada_lattice_types)x->b_ob.d_ob.m_geometry.lattice, x->custom_rule);
		x->n_thisworld = 1 - x->n_thisworld;
	} else {
		object_error((t_object *)x, "No custom rule defined!");
	}
}




/*
void life_patterninfo(t_life *x)
{
    t_cell *temp_world[2];
    temp_world[0] = (t_cell *) bach_newptrclear(DADA_LIFE_MAX_SIZE * DADA_LIFE_MAX_SIZE * sizeof(t_cell));
    temp_world[1] = (t_cell *) bach_newptrclear(DADA_LIFE_MAX_SIZE * DADA_LIFE_MAX_SIZE * sizeof(t_cell));
    long thisworld = 0;

    copy_world(x->n_world[x->n_thisworld], temp_world[thisworld], 0, 0, 0, 0, DADA_LIFE_MAX_SIZE, DADA_LIFE_MAX_SIZE, x->size);
    
    long world_history;
    
    t_cell *this_world = temp_world[thisworld];
    t_cell *new_world = temp_world[1 - thisworld];
    
    
    if (!x->use_custom_rule) {
        life_ezstep(this_world, new_world, x->size, x->neighborhood_size, (e_dada_life_border_behavior)x->border, (e_dada_lattice_types)x->b_ob.d_ob.m_geometry.lattice, x->num_born_bitfield, x->num_stay_alive_bitfield);
        x->n_thisworld = 1 - x->n_thisworld;
    } else if (x->custom_rule) {
        life_customstep(this_world, new_world, x->size, x->neighborhood_size, x->neighborhood_callback, (e_dada_life_border_behavior)x->border, (e_dada_lattice_types)x->b_ob.d_ob.m_geometry.lattice, x->custom_rule);
        x->n_thisworld = 1 - x->n_thisworld;
    } else {
        object_error((t_object *)x, "No custom rule defined!");
    }
}
 */


void life_bang(t_life *x)
{	
	life_step(x);
	if (x->play)
		life_play_step(x);
	
	jbox_invalidate_layer((t_object *)x, NULL, gensym("world"));
	jbox_redraw((t_jbox *)x);
}

void life_clear(t_life *x, char also_outside_current_world)
{	
	long i;
	long max = also_outside_current_world ? DADA_LIFE_MAX_SIZE * DADA_LIFE_MAX_SIZE : x->size * x->size;
	if (x->play)
		send_all_noteoffs(x);
	for (i = 0; i < max; i++)
		x->n_world[x->n_thisworld][i] = 0;
	jbox_invalidate_layer((t_object *)x, NULL, gensym("world"));
	jbox_redraw((t_jbox *)x);
}

// distribution = 0 -> uniform , 1 -> gaussian
void life_random(t_life *x, char distribution, double density, char add_to_existing)
{	

	long i, j;
	char take = false;
	for (i = -x->offset; i + x->offset < x->size; i++) {
		for (j = x->offset; j - x->offset > -x->size; j--) {
			long idx = coord_to_idx(x, i, j);
			double rand_val = rand_f(0, 1); // we exclude the possibility to have 1 as outcome
			if (distribution == 1) { //gaussian
				double std_coord_i = (double)i / x->offset;
				double std_coord_j = (double)j / x->offset;
                double sigma = density;
                double two_sigma_squared = 2 * sigma * sigma;
				double exp_val = exp(- (MAX(std_coord_i * std_coord_i, std_coord_j * std_coord_j)) / two_sigma_squared);
                double rand_exp_val = rand_f(0, exp_val);
				take = (rand_val < rand_exp_val);
			} else {
				take = (rand_val < density);
			}
			if (take) {
				if (x->play && !x->n_world[x->n_thisworld][idx])
					send_noteon(x, idx);
				x->n_world[x->n_thisworld][idx] = 1;
			} else if (!add_to_existing) {
				if (x->play && x->n_world[x->n_thisworld][idx])
					send_noteoff(x, idx);
				x->n_world[x->n_thisworld][idx] = 0;
			}
		}
	}

	dadaobj_send_changedbang(dadaobj_cast(x));

	jbox_invalidate_layer((t_object *)x, NULL, gensym("world"));
	jbox_redraw((t_jbox *)x);
}

void life_dump(t_life *x, char get_world, char get_notes)
{	
	t_llll *ll = life_get_state_sel(x, get_world, get_notes);
	llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 0, ll);
	llll_free(ll);
}


void life_shift(t_life *x, long x_shift, long y_shift)
{
    y_shift = -y_shift;
	long i, j;
	for (i = -x->offset; i + x->offset < x->size; i++) {
		for (j = x->offset; j - x->offset > -x->size; j--) {
			long idx = coord_to_idx(x, i, j);
			if (are_coord_in_matrix(x, i - x_shift, j + y_shift)) {
				long newidx = coord_to_idx(x, i - x_shift, j + y_shift);
				x->n_world[1 - x->n_thisworld][idx] = x->n_world[x->n_thisworld][newidx];
			} else {
				x->n_world[1 - x->n_thisworld][idx] = 0;
			}
		}
	}
	
	x->n_thisworld = 1 - x->n_thisworld;
	
	dadaobj_send_changedbang(dadaobj_cast(x));
	
	jbox_invalidate_layer((t_object *)x, NULL, gensym("world"));
	jbox_redraw((t_jbox *)x);
}

long life_getcellsum(t_life *x)
{
    t_cell *this_new_world = x->n_world[x->n_thisworld];
    long i;
    long count = 0;
    for (i = 0; i < x->size * x->size; i++, this_new_world++)
        count += *this_new_world;
    return count;
}


long life_getnumliving(t_life *x)
{
    t_cell *this_new_world = x->n_world[x->n_thisworld];
    long i;
    long count = 0;
    for (i = 0; i < x->size * x->size; i++, this_new_world++)
        if (*this_new_world)
            count++;
    return count;
}

long life_getnumdead(t_life *x)
{
    return x->size * x->size - life_getnumliving(x);
}

void life_anything(t_life *x, t_symbol *msg, long ac, t_atom *av)
{
	dadaobj_anything(dadaobj_cast(x), msg, ac, av);
	
	t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, msg, ac, av, LLLL_PARSE_CLONE);
	if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
		t_symbol *router = hatom_getsym(&parsed->l_head->l_hatom);
		llll_behead(parsed);
		
		if (router == gensym("setstoredstate") || router == gensym("life"))
			life_set_state(x, parsed);
		
        else if (router == gensym("flush") && x->play)
			send_all_noteoffs(x);
		
        else if (router == _sym_dump)
			life_dump(x, parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("world")), 
					  parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("notes")));

        else if (router == _sym_clear)
			life_clear(x, false);
		
        else if (router == _llllobj_sym_clearall)
			life_clear(x, true);
        
        else if (router == gensym("random")) {
            t_symbol *distribution = NULL;
            double density = x->default_random_density;
            long append = 0;
            llll_parseargs((t_object *)x, parsed, "sdi", gensym("distribution"), &distribution, gensym("density"), &density, gensym("append"), &append);
            life_random(x, distribution == gensym("uniform") ? 0 : 1, density, append);
        
        } else if (router == gensym("shift")) {
			long x_shift = (parsed->l_head && is_hatom_number(&parsed->l_head->l_hatom)) ? hatom_getlong(&parsed->l_head->l_hatom) : 0;
			long y_shift = (parsed->l_head && parsed->l_head->l_next && is_hatom_number(&parsed->l_head->l_next->l_hatom)) ? hatom_getlong(&parsed->l_head->l_next->l_hatom) : 0;
			life_shift(x, x_shift, y_shift);
		
        } else if (router == gensym("getsize")) {
            t_llll *ll = symbol_and_long_to_llll(_sym_size, x->size);
            llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, ll);

        } else if (router == gensym("getnumliving")) {
            t_llll *ll = symbol_and_long_to_llll(gensym("numliving"), life_getnumliving(x));
            llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, ll);

        } else if (router == gensym("getnumdead")) {
            t_llll *ll = symbol_and_long_to_llll(gensym("numdead"), life_getnumdead(x));
            llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, ll);
            
        } else if (router == gensym("getcellsum")) {
            t_llll *ll = symbol_and_long_to_llll(gensym("cellsum"), life_getcellsum(x));
            llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, ll);

/*        } else if (router == gensym("exportpng")) {
            long dpi;
            t_symbol *filename;
            double width, height;
            t_pt exportcenter;
            if (!dadaobj_parse_export_png_syntax(dadaobj_cast(x), NULL, parsed, &filename, &dpi, &width, &height, &exportcenter))
                life_exportpng(x, filename, dpi, width, height, exportcenter); */
		} else if (router == gensym("rule")) {
            char *buf = NULL;
            llll_to_text_buf(parsed, &buf);
            life_set_custom_rule(x, gensym(buf));
//			if (parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM)
//				life_set_custom_rule(x, hatom_getsym(&parsed->l_head->l_hatom));
            bach_freeptr(buf);
		}
		
	} else if (parsed) {
		life_set_state(x, parsed);
	}
	llll_free(parsed);
}




//// GRAPHIC DRAWING



void life_paint_notes(t_life *x, t_jgraphics *g, t_object *view, t_rect rect, t_pt center, char low_alpha)
{
	
	char use_layers = false;
	if (!g) {
		use_layers = true;
		g = jbox_start_layer((t_object *)x, view, gensym("notes"), rect.width, rect.height);
	}
	
	if (g && x->show_notes > 0){
		long row, col;
		t_pt min_coord = get_min_displayed_coord(dadaobj_cast(x), center, rect);
		t_pt max_coord = get_max_displayed_coord(dadaobj_cast(x), center, rect);
		long col_min = MAX(0, floor(min_coord.x) + x->offset), col_max =  MIN(x->size -1, ceil(max_coord.x) + x->offset);
		long row_min = MAX(0, x->offset - ceil(max_coord.y)), row_max = MIN(x->size -1, x->offset - floor(min_coord.y));
		for (row = row_min; row <= row_max; row++) {
			for (col = col_min; col <= col_max; col++) {
				t_life_metadata m = x->n_world_metadata[row * x->size + col];
                t_jrgba color;
                if (x->show_notes == 2) {
                    color = double_to_color(CLAMP(positive_fmod(m.pitch_mc, 1200.), 0., 1200.), 0., 1200., true);
                    t_jhsla hslacolor;
                    hslacolor.hue = rescale(positive_fmod(m.pitch_mc, 1200.), 0., 1200., 0., TWOPI);
                    hslacolor.lightness = rescale(floor(CLAMP(m.pitch_mc, x->min_pitch, x->max_pitch)/1200.), floor(x->min_pitch/1200.), floor(x->max_pitch/1200.), 0.2, 0.8);
                    hslacolor.saturation = rescale(floor(CLAMP(m.pitch_mc, x->min_pitch, x->max_pitch)/1200.), floor(x->min_pitch/1200.), floor(x->max_pitch/1200.), 0.2, 0.8);
                    hslacolor.alpha = 1.;
                    color = hsla_to_rgba(hslacolor);
                } else
                    color = double_to_color(CLAMP(m.pitch_mc, x->min_pitch, x->max_pitch), x->min_pitch, x->max_pitch, false);
				switch (x->show_velocity) {
					case 1:
						change_color_for_velocity_alpha(&color, m.velocity);
						break;
					case 2:
						change_color_for_velocity_darken(&color, m.velocity);
						break;
					case 3:
						change_color_for_velocity_lighten(&color, m.velocity);
						break;
					default:
						break;
				}
                
                if (low_alpha)
                    color.alpha *= 0.3;
				
				t_pt pix = coord_to_pix(dadaobj_cast(x), center, build_pt((col - x->offset), -(row - x->offset)));
				switch (x->b_ob.d_ob.m_geometry.lattice) {
					case DADA_LATTICE_TRIANGLE:
						paint_hexagon(g, &color, &color, pix, 0.5 * x->b_ob.d_ob.m_zoom.zoom.x / SQRT3OVER2, 0, true);
						break;
					default:
						paint_square(g, &color, &color, pix, 0.5 * x->b_ob.d_ob.m_zoom.zoom.x, 0);
						break;
				}
				
			}
		}
		
		if (use_layers && view)
			jbox_end_layer((t_object *)x, view, gensym("notes"));
	}

	if (use_layers && view)
		jbox_paint_layer((t_object *)x, view, gensym("notes"), 0., 0.);	// position of the layer
}


void life_paint_world(t_life *x, t_jgraphics *g, t_object *view, t_rect rect, t_pt center){
	
	char use_layers = false;
	
	if (!g) {
 		use_layers = true;
		g = jbox_start_layer((t_object *)x, view, gensym("world"), rect.width, rect.height);
	}
	
	if (g){
		long row, col;
		t_pt min_coord = get_min_displayed_coord(dadaobj_cast(x), center, rect);
		t_pt max_coord = get_max_displayed_coord(dadaobj_cast(x), center, rect);
		long col_min = MAX(0, floor(min_coord.x) + x->offset), col_max =  MIN(x->size -1, ceil(max_coord.x) + x->offset);
		long row_min = MAX(0, x->offset - ceil(max_coord.y)), row_max = MIN(x->size -1, x->offset - floor(min_coord.y));
		for (row = row_min; row <= row_max; row++) {
			for (col = col_min; col <= col_max; col++) {
				char val = x->n_world[x->n_thisworld][row * x->size + col];
				if (val) {
					t_pt pix = coord_to_pix(dadaobj_cast(x), center, build_pt((col - x->offset), -(row - x->offset)));
					t_jrgba color = x->j_cellcolor;
					double size = 0.5 * x->b_ob.d_ob.m_zoom.zoom.x * x->size_factor;
					
					// color
					if (x->use_custom_rule) {
						switch (x->color_mapping) {
							case DADA_LIFE_COLORMAP_CANDYCANE:
							{
								long val2 = (val - 1) % (MIN(8, x->num_candycane));
								switch (val2) {
									case 1: color = x->j_candycane2; break;
									case 2: color = x->j_candycane3; break;
									case 3: color = x->j_candycane4; break;
									case 4: color = x->j_candycane5; break;
									case 5: color = x->j_candycane6; break;
									case 6: color = x->j_candycane7; break;
									case 7: color = x->j_candycane8; break;
									default: break;
								}
								break;
							}
							
							case DADA_LIFE_COLORMAP_COLORSCALE:
							{
								t_jhsla color_hsla = rgba_to_hsla(color);
								color_hsla.lightness = rescale(CLAMP(val, 1, x->max_val_for_mapping), 1, x->max_val_for_mapping, 0.6, 0.1);
								color = hsla_to_rgba(color_hsla);
								break;
							}
								
							case DADA_LIFE_COLORMAP_COLORSPECTRUM:
								color = double_to_color(CLAMP(val, 1, x->max_val_for_mapping), 1, x->max_val_for_mapping, false);
								break;
							
							case DADA_LIFE_COLORMAP_RANDOM:
							{
								t_jhsla color_hsla;
								color_hsla.lightness = 0.5;
								color_hsla.saturation = 0.95;
								color_hsla.hue = rand_f(0., TWOPI);
								color_hsla.alpha = 1.;
								color = hsla_to_rgba(color_hsla);
								break;
							}
								
							case DADA_LIFE_COLORMAP_CUSTOM:
							{
								if (x->red_lexpr) {
									t_hatom vars[3];
									t_hatom *res = NULL;
									hatom_setlong(vars, val);
									hatom_setlong(vars + 1, col - x->offset);
									hatom_setlong(vars + 2, -(row - x->offset));
									res = lexpr_eval(x->red_lexpr, vars);
									color.red = hatom_getdouble(res);
									bach_freeptr(res);
								}
								if (x->green_lexpr) {
									t_hatom vars[3];
									t_hatom *res = NULL;
									hatom_setlong(vars, val);
									hatom_setlong(vars + 1, col - x->offset);
									hatom_setlong(vars + 2, -(row - x->offset));
									res = lexpr_eval(x->green_lexpr, vars);
									color.green = hatom_getdouble(res);
									bach_freeptr(res);
								}
								if (x->blue_lexpr) {
									t_hatom vars[3];
									t_hatom *res = NULL;
									hatom_setlong(vars, val);
									hatom_setlong(vars + 1, col - x->offset);
									hatom_setlong(vars + 2, -(row - x->offset));
									res = lexpr_eval(x->blue_lexpr, vars);
									color.blue = hatom_getdouble(res);
									bach_freeptr(res);
								}
								break;
							}
							default:
								break;
						}
						
						
						// size
						if (x->size_lexpr) {
							t_hatom vars[3];
							t_hatom *res = NULL;
							hatom_setlong(vars, val);
							hatom_setlong(vars + 1, col - x->offset);
							hatom_setlong(vars + 2, -(row - x->offset));
							res = lexpr_eval(x->size_lexpr, vars);
							size *= hatom_getdouble(res);
							bach_freeptr(res);
						}

						// alpha
						if (x->alpha_lexpr) {
							t_hatom vars[3];
							t_hatom *res = NULL;
							hatom_setlong(vars, val);
							hatom_setlong(vars + 1, col - x->offset);
							hatom_setlong(vars + 2, -(row - x->offset));
							res = lexpr_eval(x->alpha_lexpr, vars);
							color.alpha = hatom_getdouble(res);
							bach_freeptr(res);
						}
					}
					
					t_jrgba color_inner = change_alpha(color, color.alpha * 0.7);
					
					// paint shape
					switch (x->shape) {
						case DADA_LIFE_SHAPE_CIRCLE:
							paint_circle(g, color, color_inner, pix.x, pix.y, size, 1);
							break;
						case DADA_LIFE_SHAPE_HEXAGON:
							paint_hexagon(g, &color, &color_inner, pix, size / SQRT3OVER2, 1, true);
							break;
						case DADA_LIFE_SHAPE_SPRITE:
						{
							char colorize = (jrgba_compare(&color, &x->j_cellcolor) == 0);
							t_jhsla c1, c2, deltacolor;
							if (colorize) {
								c1 = rgba_to_hsla(color);
								c2 = rgba_to_hsla(x->j_cellcolor);
								deltacolor.hue = c1.hue - c2.hue;
								deltacolor.lightness = c1.lightness / c2.lightness;
								deltacolor.saturation = c1.saturation / c2.saturation;
								deltacolor.alpha = c1.alpha / c2.alpha;
							}
								
							paint_sprite(g, &x->sprite, 0, x->sprite.source_rect, build_rect(pix.x - size, pix.y - size, 2*size, 2*size), 0, colorize ? &deltacolor : NULL);
						}
							break;
						default:
							paint_square_fast(g, &color, &color_inner, pix, size, 1);
							break;
					}
				}
			}
		}
		
		if (use_layers)
			jbox_end_layer((t_object *)x, view, gensym("world"));
	}
	
	if (use_layers)
		jbox_paint_layer((t_object *)x, view, gensym("world"), 0., 0.);	// position of the layer
}




void life_paint_ext(t_life *x, t_object *view, t_dada_force_graphics *force_graphics)
{
	
	t_jgraphics *g = force_graphics->graphic_context;
	t_rect rect = force_graphics->rect;
	t_pt center = force_graphics->center_pix;

    dadaobj_paint_background(dadaobj_cast(x), g, &rect);
    
	jgraphics_set_source_rgba(g, 0, 0, 0, 0.3);
    life_paint_notes(x, view ? NULL : force_graphics->graphic_context, view, rect, center, false); // paint notes, but with 0.3 alpha channel
	jgraphics_set_source_rgba(g, 0, 0, 0, 1.);
	
	life_paint_world(x, view ? NULL : force_graphics->graphic_context, view, rect, center);
	
	if (!x->b_ob.d_ob.m_interface.mouse_is_down && x->hovered_idx >= 0) {
		char buf[100];
		double h = 27, w = 70;
		t_jfont *jf = jfont_create_debug("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, 12);
		t_pt text_pt = build_pt(x->b_ob.d_ob.m_interface.mousemove_pix.x + 7, x->b_ob.d_ob.m_interface.mousemove_pix.y - 7);  
		snprintf_zero(buf, 100, "Cents %d\nVelocity %d", (long)round(x->n_world_metadata[x->hovered_idx].pitch_mc), (long)x->n_world_metadata[x->hovered_idx].velocity);
		paint_rectangle(g, DADA_GREY_25, change_alpha(DADA_WHITE, 0.6), text_pt.x-2, text_pt.y-2 - h, w +4, h+4, 1);
		write_text_standard_singleline(g, jf, DADA_GREY_25, buf, text_pt.x, text_pt.y - h, w + 4, h + 4);
		jfont_destroy_debug(jf);
	}
    
    dadaobj_paint_border(dadaobj_cast(x), g, &rect);
}

void life_paint(t_life *x, t_object *view)
{
    dadaobj_paint(dadaobj_cast(x), view);
}

void life_exportpng(t_life *x, t_symbol *file, long dpi, double width, double height, t_pt exportcenteroffset)
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
		life_paint_notes(x, g_studio, NULL, exportrect, exportcenter, true); // paint notes, but with 0.3 alpha channel > ALPHA DOESN'T WORK!
		life_paint_world(x, g_studio, NULL, exportrect, exportcenter);
		jgraphics_image_surface_writepng(s_studio, filename, path, dpi);
		jgraphics_destroy(g_studio);
		jgraphics_surface_destroy(s_studio);
	}
}



///////// POPUP MENU FUNCTIONS


void popup_clear(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_life *x = (t_life *)d_ob->orig_obj;
	life_clear(x, false);
}

void popup_evolve(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_life *x = (t_life *)d_ob->orig_obj;
	life_bang(x);
}

void popup_random(t_dadaobj *d_ob, t_symbol *label, const t_llll *address) 
{
	t_life *x = (t_life *)d_ob->orig_obj;
	life_random(x, hatom_getlong(&address->l_tail->l_hatom) == 3 ? 1 : 0, x->default_random_density, false) ;
}

void show_bg_popup_menu(t_life *x, t_object *patcherview, t_pt pt, long modifiers)
{
	ezdisplay_popup_menu(dadaobj_cast(x), patcherview,
						 (char *)"Center View Reset Zoom Clear separator Next Generation separator (Random Configuration Uniform Gaussian)", 
						 "0 0 0 0 0 0 0", "", "", "", "", 
						 (void *)popup_center_view, (void *)popup_reset_zoom, (void *)popup_clear, NULL, (void *)popup_evolve, NULL, (void *)popup_random, WHITENULL);
}


////////// INTERFACE FUNCTIONS


void life_focusgained(t_life *x, t_object *patcherview) {
	x->justgainedfocus = true;
	if (dadaobj_focusgained(dadaobj_cast(x), patcherview))
		return;
}

void life_focuslost(t_life *x, t_object *patcherview) {
	if (dadaobj_focuslost(dadaobj_cast(x), patcherview))
		return;
	dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
}

void life_mousemove(t_life *x, t_object *patcherview, t_pt pt, long modifiers) {

	llll_format_modifiers(&modifiers, NULL);
	if (dadaobj_mousemove(dadaobj_cast(x), patcherview, pt, modifiers))
		return;

	if (popup_menu_is_shown(dadaobj_cast(x))) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
	} else if (x->b_ob.d_ob.m_interface.has_focus && modifiers == eCommandKey) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_ERASER);
	} else if (x->b_ob.d_ob.m_interface.has_focus) {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_PENCIL);
	}
	
	x->hovered_idx = -1;
	if (x->b_ob.d_ob.m_interface.allow_mouse_hover) {
		t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), patcherview, pt);
		long coord_x = round(coord.x);
		long coord_y = round(coord.y);
		
		if (are_coord_in_matrix(x, coord_x, coord_y)) {
			long idx = coord_to_idx(x, coord_x, coord_y);
			x->hovered_idx = idx;
		}
		jbox_redraw((t_jbox *)x);
	}
}


void life_mousedown(t_life *x, t_object *patcherview, t_pt pt, long modifiers){

	if (dadaobj_mousedown(dadaobj_cast(x), patcherview, pt, modifiers))
		return;

	if (modifiers & ePopupMenu)
		show_bg_popup_menu(x, patcherview, pt, modifiers);
	else
		life_mousedrag(x, patcherview, pt, modifiers);

}

void life_mouseup(t_life *x, t_object *patcherview, t_pt pt, long modifiers){
	
	llll_format_modifiers(&modifiers, NULL);
	
	if (dadaobj_mouseup(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
	
/*	if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADA_KALEIDO_ELEMENT_SAMPLINGPOINT && x->b_ob.d_ob.m_tools.curr_tool == DADA_TOOL_CHANGE_PITCH) 
		x->sampling_points[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx].pitch_mc = snap_to_microtonal_grid_do(x->sampling_points[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx].pitch_mc, x->tonedivision);
	
	x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADA_KALEIDO_ELEMENT_NONE;
	x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag = 0;*/
}

void life_set_cell_from_mousedrag(t_life *x, long coord_x, long coord_y, long modifiers)
{
    char changed = false;
	if (are_coord_in_matrix(x, coord_x, coord_y)) {
		long idx = coord_to_idx(x, coord_x, coord_y);
		if (modifiers == eCommandKey && x->n_world[x->n_thisworld][idx]) {
			x->n_world[x->n_thisworld][idx] = 0;
            changed = true;
			if (x->play)
				send_noteoff(x, idx);
		} else if (modifiers == 0 && !x->n_world[x->n_thisworld][idx]) {
			x->n_world[x->n_thisworld][idx] = 1;
            changed = true;
            if (x->play)
				send_noteon(x, idx);
		}
	}
    if (changed)
        llllobj_outlet_bang((t_object *)x, LLLL_OBJ_UI, 3);
}

void life_mousedrag(t_life *x, t_object *patcherview, t_pt pt, long modifiers){

	llll_format_modifiers(&modifiers, NULL);
	
	if (dadaobj_mousedrag(dadaobj_cast(x), patcherview, pt, modifiers))
		return;

	
	if (x->justgainedfocus){
		x->justgainedfocus = 0;
		return;
	}
	
	if (!modifiers || modifiers == eCommandKey) {
		t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), patcherview, pt);
		long pen_size = round(DADA_LIFE_PEN_SIZE / x->b_ob.d_ob.m_zoom.zoom.x);
		
		if (pen_size > 1) {
			long min_x, max_x, min_y, max_y, i, j;
			if (pen_size % 2) {
				min_x = round(coord.x) - ((pen_size - 1) / 2);
				min_y = round(coord.y) - ((pen_size - 1) / 2);
			} else {
				min_x = floor(coord.x) - (pen_size / 2 - 1);
				min_y = floor(coord.y) - (pen_size / 2 - 1);
			}
			max_x = min_x + pen_size - 1;
			max_y = min_y + pen_size - 1;
			for (i = min_x; i <= max_x; i++)
				for (j = min_y; j <= max_y; j++)
					life_set_cell_from_mousedrag(x, i, j, modifiers);
		} else
			life_set_cell_from_mousedrag(x, round(coord.x), round(coord.y), modifiers);
		
			jbox_invalidate_layer((t_object *)x, NULL, gensym("world"));
		jbox_redraw((t_jbox *)x);
	}

}

long life_keyup(t_life *x, t_object *patcherview, long keycode, long modifiers, long textcharacter){
			
	llll_format_modifiers(&modifiers, &keycode);

	if (dadaobj_keyup(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
		return 1;
	
	return 0;
}

long life_key(t_life *x, t_object *patcherview, long keycode, long modifiers, long textcharacter){
	llll_format_modifiers(&modifiers, &keycode);
	
	if (dadaobj_key(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
		return 1;

	switch (keycode) {
		case JKEY_ENTER:
            dadaobj_send_notification_sym(dadaobj_cast(x), gensym("step"));
			life_bang(x);
			return 1;
		case JKEY_ESC:
			if (x->play)
				send_all_noteoffs(x);
			return 1;
		case JKEY_TAB:
            dadaobj_send_notification_sym(dadaobj_cast(x), gensym("random"));
			life_random(x, 1, x->default_random_density, modifiers & eShiftKey);
			return 1;
		case JKEY_BACKSPACE:
            dadaobj_send_notification_sym(dadaobj_cast(x), _llllobj_sym_clear);
			life_clear(x, false);
			return 1;
		case JKEY_LEFTARROW:
			life_shift(x, -1, 0);
			return 1;
		case JKEY_RIGHTARROW:
			life_shift(x, 1, 0);
			return 1;
		case JKEY_UPARROW:
			life_shift(x, 0, 1);
			return 1;
		case JKEY_DOWNARROW:
			life_shift(x, 0, -1);
			return 1;
		case JKEY_SPACEBAR:
			if (modifiers == eCommandKey) {
				object_attr_setchar(x, _llllobj_sym_play, !x->play);
				jbox_redraw((t_jbox *)x);
				return 1;
			}
			break;
		default:
			break;
	} 

	return 0;
}

void life_mousewheel(t_life *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc){
	llll_format_modifiers(&modifiers, NULL);  
	
	if (dadaobj_mousewheel(dadaobj_cast(x), view, pt, modifiers, x_inc, y_inc)) {
		jbox_invalidate_layer((t_object *)x, NULL, gensym("notes"));
		jbox_invalidate_layer((t_object *)x, NULL, gensym("world"));
		jbox_redraw((t_jbox *)x);
		return;
	}
}

void life_mouseenter(t_life *x, t_object *patcherview, t_pt pt, long modifiers) 
{
	if (dadaobj_mouseenter(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
}

void life_mouseleave(t_life *x, t_object *patcherview, t_pt pt, long modifiers) 
{
	x->hovered_idx = -1;
	if (dadaobj_mouseleave(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
}



////////////////// UNDO HANDLING

/*
void life_undo_postprocess(t_life *x)
{
	jbox_invalidate_layer((t_object *)x, NULL, gensym("sampling_points"));
	process_change(x);
	jbox_redraw((t_jbox *)x);
}


void life_undo_step_push_sampling_points(t_life *x, t_symbol *operation)
{
	undo_add_interface_step(dadaobj_cast(x), DADA_FUNC_v_oX, (method)life_set_sampling , NULL, DADA_FUNC_X_o, (method)life_get_sampling, NULL, operation);
}
*/




