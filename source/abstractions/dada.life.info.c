/**
	@file
	dada.life.info.c
	
	@name 
	dada.life.info
	
	@realname 
	dada.life.info

	@type
	abstraction
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
	Pattern information in 2D cellular automata
	
	@description
	Reports information about <o>dada.life</o> configurations.
	
	@discussion
	This module is an abstraction, the algorithms it implements are the naive algorithms.
	Hence it will not be the most efficient implementation, nor the most powerful one.

	@category
	dada, dada abstractions

	@keywords
	life, Conway, cellular automaton, cellular automata, pattern, information

	@seealso
	dada.life
	
	@owner
	Daniele Ghisi
*/

// ---------------
// METHODS
// ---------------

// @method llll @digest Report information for configuration
// @description An <m>llll</m> in the first inlet is considered as a <o>dada.life</o> dump
// (i.e. the llll one obtains when sending a <m>dump</m> message to <o>dada.life</o>.
// Information about patterns, periodicity and translation is reported from all outlets
// (see the documentation for each one of the outlets).

// @method bang @digest Output result
// @description Outputs the information on the most recently received input data.



// ---------------
// ATTRIBUTES
// ---------------

void main_foo() {

llllobj_class_add_out_attr(c, LLLL_OBJ_VANILLA);

CLASS_ATTR_LONG(c, "maxiter", 0, t_life_info, maxiter); 
CLASS_ATTR_STYLE_LABEL(c,"maxiter",0,"text","Maximum Number of Iterations");
CLASS_ATTR_BASIC(c,"maxiter",0);
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"maxiter",0,"100");
// @description Set the maximum number of iteration for the analysis algorithm.
// (If an oscillator or spaceship is detected, the pattern is stopped before <m>maxiter</m>
// is reached.)

CLASS_ATTR_CHAR(c, "orbit", 0, t_life_info, orbit); 
CLASS_ATTR_STYLE_LABEL(c,"orbit",0,"text","Outputs Pattern Orbit");
CLASS_ATTR_BASIC(c,"orbit",0);
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"orbit",0,"1");
// @description Toggles the ability to also output the pattern orbit (defaults to 1).

DADA_CLASS_ATTR_CHAR_SUBSTRUCTURE(c, LLLL_OBJ_UI, "lattice", 0, t_dadaobj, m_geometry, t_geometry_manager, lattice);
CLASS_ATTR_STYLE_LABEL(c, "lattice", 0, "enumindex", "Lattice Type");
CLASS_ATTR_ENUMINDEX(c,"lattice", 0, "Square Triangular"); 
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"lattice",0,"0");
CLASS_ATTR_BASIC(c, "lattice", 0);
// @description Sets the lattice type (either 0 = square, which is the default, or 1 = triangular)

CLASS_ATTR_LONG_VARSIZE (c, "born", 0, t_life_info, num_born, num_born_size, DADA_LIFE_MAX_NUM_BORN_SIZE);
CLASS_ATTR_STYLE_LABEL(c, "born", 0, "text", "Born");
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"born",0,"3");
// @description Lists all the possibilities for the number of neighbours a dead cell must have in order to be born

CLASS_ATTR_LONG_VARSIZE (c, "stayalive", 0, t_life_info, num_stay_alive, num_stay_alive_size, DADA_LIFE_MAX_NUM_STAY_ALIVE_SIZE);
CLASS_ATTR_STYLE_LABEL(c, "stayalive", 0, "text", "Stay Alive");
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"stayalive",0,"2 3");
// @description Lists all the possibilities for the number a living cell must have in order to stay alive

CLASS_ATTR_LONG (c, "border", 0, t_life_info, border);
CLASS_ATTR_STYLE_LABEL(c, "border", 0, "enumindex", "Border Handling");
CLASS_ATTR_ENUMINDEX(c,"border", 0, "Dead Outside Wrap Kill Live"); 
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"border",0,"0");
// @description Sets the border conditions, establishing how the cells just beyond the world limits should be considered

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


}

// ---------------
// INLETS
// ---------------

// @in 0 @type llll @digest Pattern from <o>dada.life</o>'s dump



// ---------------
// OUTLETS
// ---------------

// @out 0 @type int/inf @digest Pattern periodicity 
// @description Outputs the pattern period, or "inf" if no periodicity is detected (until <m>maxiter</m>).

// @out 1 @type llll @digest Pattern period delta 
// @description If a periodicity is detected, outputs the displacement of the pattern after one full period, in the form
// <m>delta_x</m> <m>delta_y</m>. If no periodicity is detected, <b>null</b> is output. 
// For instance, the standard life glider will have as displacement <b>1 -1</b>, since it
// will appear again after one period 1 cell at right and 1 cell down with respect to the original pattern.

// @out 2 @type int/inf @digest Annihilation time 
// @description Outputs the number of step before pattern becomes an empty matrix (every cell dies); "inf" if no annihilation is detected
// (until <m>maxiter</m>).

// @out 3 @type llll @digest Trimmed pattern 
// @description Outputs the pattern matrix, where all the empty rows and columns at left, right, top and bottom are removed; in other words
// the pattern is output in its "minimal matrix".

// @out 4 @type llll @digest Trimmed pattern coordinates 
// @description Outputs the coordinates of the "minimal matrix" with respect to the full world matrix, in the form
// <m>start_row</m> <m>end_row</m> <m>start_col</m> <m>end_col</m>.

// @out 5 @type llll @digest Pattern orbit 
// @description If the <m>orbit</m> attribute is non-zero, 
// outputs the sequence of patterns that follows the incoming one, each wrapped in a level of parenthesis.

// @out 6 @type llll @digest Trimmed pattern orbit 
// @description If the <m>orbit</m> attribute is non-zero, 
// outputs the trimmed pattern orbit, i.e. the pattern orbit (see previous outlet), but trimmed in its "minimal matrix", i.e. all the empty rows
// at left, right, top and bottom are removed.


// ---------------
// ARGUMENTS
// ---------------

// (none)