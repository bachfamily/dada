/**
	@file
	dada.analysis.centroid.c
	
	@name 
	dada.analysis.centroid
	
	@realname 
	dada.analysis.centroid

	@type
	abstraction
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
	Symbolic centroid
	
	@description
	Finds the pitch centroid of a score.
	
	@discussion
	The symbolic centroid is the average of the pitches in the score,
	each weighted with its own duration.

	@category
	dada, dada abstractions, dada analysis

	@keywords
	centroid, analysis, pitch, average

	@seealso
	dada.segment, dada.catart, dada.analysis.spread
	
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

// @out 0 @type llll @digest Pitch centroid
// @description Outputs the average of all pitches, weighted with their duration.


// ---------------
// ARGUMENTS
// ---------------

// (none)