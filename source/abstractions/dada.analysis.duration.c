/**
	@file
	dada.analysis.duration.c
	
	@name 
	dada.analysis.duration
	
	@realname 
	dada.analysis.duration

	@type
	abstraction
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
	Duration
	
	@description
	Finds the duration of a score in milliseconds
	
	@discussion

	@category
	dada, dada abstractions, dada analysis

	@keywords
	analysis, duration, milliseconds, total, time

	@seealso
	dada.segment, dada.cartesian, dada.analysis.count
	
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

// @out 0 @type llll @digest Score duration
// @description Outputs the duration of the score, in milliseconds. 


// ---------------
// ARGUMENTS
// ---------------

// (none)