/**
	@file
	dada.analysis.minmax.c
	
	@name 
	dada.analysis.minmax
	
	@realname 
	dada.analysis.minmax

	@type
	abstraction
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
	Minimum and maximum of a parameter
	
	@description
	Finds the minimum and maximum of a parameter inside the score
	
	@discussion

	@category
	dada, dada abstractions, dada analysis

	@keywords
	analysis, minimum, maximum, min, max, minima, maxima, cents, pitch, velocity, velocities, duration, onset

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
// maximum is then output through the right outlet, and the minimum fromt the left one.

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

// @out 0 @type llll @digest Minimum
// @description Outputs the minimum of the parameter set as argument. 
// @out 1 @type llll @digest Maximum
// @description Outputs the maximum of the parameter set as argument. 


// ---------------
// ARGUMENTS
// ---------------

// @arg 0 @name parameter_name @optional 1 @type symbol @digest Parameter name
// @description Sets the name of the parameter to be considered. Could be one of the following
// symbols: "onsets" (<o>bach.roll</o> only), "cents", "durations", "velocities".
