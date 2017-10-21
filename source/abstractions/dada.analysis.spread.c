/**
	@file
	dada.analysis.spread.c
	
	@name 
	dada.analysis.spread
	
	@realname 
	dada.analysis.spread

	@type
	abstraction
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
	Symbolic spread
	
	@description
	Finds the pitch spread of a score.
	
	@discussion
	The symbolic spread is the standard deviation of the pitches in the score.

	@category
	dada, dada abstractions

	@keywords
	spread, analysis, pitch, standard deviation, variance

	@seealso
	dada.segment, dada.catart, dada.analysis.centroid
	
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

// @out 0 @type llll @digest Pitch spread
// @description Outputs the standard deviation of all pitches.


// ---------------
// ARGUMENTS
// ---------------

// (none)