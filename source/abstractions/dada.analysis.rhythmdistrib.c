/**
	@file
	dada.analysis.rhythmdistrib.c
	
	@name 
	dada.analysis.rhythmdistrib
	
	@realname 
	dada.analysis.rhythmdistrib

	@type
	abstraction
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
	Rhythmic energy distribution
	
	@description
	Finds the rhythmic energy distribution of a score
	
	@discussion
	The onsets are quantized into N uniformly spaced regions 
	(where N is the <m>numdiv</m> attribute); then the velocities
	of the corresponding notes are summed, and finally normalized.

	@category
	dada, dada abstractions, dada analysis

	@keywords
	analysis, onset, rhythm, distribution, normalize, region, energy, velocity

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
// score is divided into N (which is the <m>numdiv</m> attribute) equally spaced
// regions and each note is then quantized to the nearest one of the N+1 corresponding
// onsets. Such onsets are output through the second outlet, and then the 
// corresponding energy distribution is output through the left outlet.

// @method bang @digest Output result
// @description Outputs the result of the analysis performed on the most recently received input data.



// ---------------
// ATTRIBUTES
// ---------------

void main_foo() {

llllobj_class_add_out_attr(c, LLLL_OBJ_VANILLA);

CLASS_ATTR_LONG(c, "numdiv", 0, t_analysis_rhythmdistrib, numdiv); 
CLASS_ATTR_STYLE_LABEL(c,"numdiv",0,"text","Number of Regions");
CLASS_ATTR_BASIC(c,"numdiv",0);
// @description Sets the number N of equally spaced regions into which
// will serve as grid for the quantization (the grid will contain hence
// N+1 onsets, considering the first and last one).

}

// ---------------
// INLETS
// ---------------

// @in 0 @type llll @digest Score gathered syntax



// ---------------
// OUTLETS
// ---------------

// @out 0 @type llll @digest Energy distribution
// @description Outputs the energy distribution corresponding to each one of the
// onsets.
// @out 1 @type llll @digest Onsets
// @description Outputs the quantized onsets. 


// ---------------
// ARGUMENTS
// ---------------

// @arg 0 @name numdiv @optional 1 @type int @digest Number of Regions
// @description Sets the number N of equally spaced regions into which
// will serve as grid for the quantization (the grid will contain hence
// N+1 onsets, considering the first and last one).
