/**
	@file
	dada.analysis.chroma.c
	
	@name 
	dada.analysis.chroma
	
	@realname 
	dada.analysis.chroma

	@type
	abstraction
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
	Symbolic chroma
	
	@description
	Finds the chroma vector of a score.
	
	@discussion
	Each note's pitch class is weighted via its duration and velocity in order 
	to account for the chroma vector. All the components are then normalized
	so that they sum up to 1.

	@category
	dada, dada abstractions, dada analysis

	@keywords
	analysis, chroma, vector, pitch class

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
// @in 1 @type int @digest Modulo
// @description @copy BACH_DOC_SETTHEORY_MODULO



// ---------------
// OUTLETS
// ---------------

// @out 0 @type llll @digest Chroma vector
// @description Outputs the chroma vector 


// ---------------
// ARGUMENTS
// ---------------

// @arg 0 @name modulo @optional 1 @type int @digest Modulo  
// @description @copy BACH_DOC_SETTHEORY_MODULO
