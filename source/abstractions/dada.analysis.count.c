/**
	@file
	dada.analysis.count.c
	
	@name 
	dada.analysis.count
	
	@realname 
	dada.analysis.count

	@type
	abstraction
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
	Count items
	
	@description
	Counts the items of a score.
	
	@discussion

	@category
	dada, dada abstractions, dada analysis

	@keywords
	analysis, count, notes, chords, measures, voices, items

	@seealso
	dada.segment, dada.catart
	
	@owner
	Daniele Ghisi
*/

// ---------------
// METHODS
// ---------------

// @method llll @digest Perform analysis
// @description An <m>llll</m> in the first inlet is considered as a <o>bach.roll</o> or
// <o>bach.score</o> gathered syntax on which the analysis should be performed. The
// result is then output through the outlet.

// @method bang @digest Output result
// @description Outputs the result of the analysis performed on the most recently received input data.



// ---------------
// ATTRIBUTES
// ---------------

void main_foo() {

llllobj_class_add_out_attr(c, LLLL_OBJ_VANILLA);


}

// ---------------
// INLETS
// ---------------

// @in 0 @type llll @digest Score gathered syntax



// ---------------
// OUTLETS
// ---------------

// @out 0 @type llll @digest Item count
// @description Outputs the number of the counted items (see arguments). 


// ---------------
// ARGUMENTS
// ---------------

// @arg 0 @name item_type @optional 1 @type symbol @digest Item type
// @description Sets the type of the items to be counted. Could be one of the following
// symbols: "notes", "chords", "measures", "voices".
