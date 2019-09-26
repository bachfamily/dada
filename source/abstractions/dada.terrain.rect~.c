/**
	@file
	dada.terrain.rect~.c
	
	@name 
	dada.terrain.rect~
	
	@realname 
	dada.terrain.rect~

	@type
	abstraction
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
	Paths along rectangles
	
	@description
	Produces the coordinates of paths along rectangles at sample rate.
	
	@discussion

	@category
	dada, dada abstractions

	@keywords
	terrain, coordinate, rectangle, line, sample, path 

	@seealso
	dada.terrain~, dada.terrain.ellipse~, dada.terrain.segment~, dada.terrain.spiral~
	
	@owner
	Daniele Ghisi
*/

// ---------------
// METHODS
// ---------------

// @method signal @digest Compute path
// @description An incoming signal is usually the output of a <o>phasor~</o> object,
// i.e. the phase of the path (from 0 = beginning, to 1 = end). The corresponding
// point on the rectangle path is computed and output.



// ---------------
// ATTRIBUTES
// ---------------

void main_foo() {

llllobj_class_add_out_attr(c, LLLL_OBJ_VANILLA);


CLASS_ATTR_CHAR(c, "polar", 0, t_terrain_rectangle, polar); 
CLASS_ATTR_STYLE_LABEL(c,"polar",0,"onoff","Output Polar Coordinates");
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"polar",0,"1");
// @description Toggles the ability to output polar coordinates (radius, from left
// outlet, and angle, from right outlet). By default it is active; if it is
// turned off, the output is in cartesian coordinates (X, from left outlet, and Y
// from right outlet).

CLASS_ATTR_DOUBLE(c, "x", 0, t_terrain_rectangle, x); 
CLASS_ATTR_STYLE_LABEL(c,"x",0,"text","Start X");
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"x",0,"0");
// @description Sets the start X coordinate.

CLASS_ATTR_DOUBLE(c, "y", 0, t_terrain_rectangle, x); 
CLASS_ATTR_STYLE_LABEL(c,"y",0,"text","Start Y");
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"y",0,"0");
// @description Sets the start Y coordinate.

CLASS_ATTR_DOUBLE(c, "w", 0, t_terrain_rectangle, w); 
CLASS_ATTR_STYLE_LABEL(c,"w",0,"text","Rectangle Width");
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"w",0,"0");
// @description Sets the rectangle width.

CLASS_ATTR_DOUBLE(c, "h", 0, t_terrain_rectangle, h); 
CLASS_ATTR_STYLE_LABEL(c,"h",0,"text","Rectangle Height");
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"h",0,"0");
// @description Sets the rectangle height.


}

// ---------------
// INLETS
// ---------------

// @in 0 @type signal @digest Phase (0-1)



// ---------------
// OUTLETS
// ---------------

// @out 0 @type signal @digest X or radius
// @description Outputs the X coordinate (if <m>polar</m> is 0) 
// or the radius (if <m>polar</m> is 1)

// @out 1 @type signal @digest Y or angle
// @description Outputs the Y coordinate (if <m>polar</m> is 0) 
// or the angle (if <m>polar</m> is 1)


// ---------------
// ARGUMENTS
// ---------------

// @arg 0 @name x @optional 1 @type double @digest Start X 
// @description Sets the initial X coordinate of the starting point.

// @arg 1 @name y @optional 1 @type double @digest Start Y
// @description Sets the initial Y coordinate of the starting point.

// @arg 2 @name w @optional 1 @type double @digest Width
// @description Sets the initial rectangle width.

// @arg 3 @name h @optional 1 @type double @digest Height
// @description Sets the initial rectangle height.
