/**
	@file
	dada.analysis.energy.c
	
	@name 
	dada.analysis.energy
	
	@realname 
	dada.analysis.energy

	@type
	abstraction
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
	Symbolic energy
	
	@description
	Finds the average velocity of a score.
	
	@discussion
	The energy is computed as the sum of all relative durations in the score
	(i.e. duration of notes, divided by the duration of the whole score), weighted
	by the corresponding velocities.

	@category
	dada, dada abstractions, dada analysis

	@keywords
	analysis, loudness, energy, velocity, duration, sum

	@seealso
	dada.segment, dada.catart, dada.analysis.centroid, dada.analysis.spread
	
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

// @out 0 @type llll @digest Score energy
// @description Outputs the energy of the score, intended as the sum of all 
// relative durations in the score (i.e. duration of notes, divided by the duration 
// of the whole score), weighted by the corresponding velocities. 


// ---------------
// ARGUMENTS
// ---------------

// (none)