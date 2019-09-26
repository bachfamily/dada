/**
	@file
	dada.terrain.segment~.c
	
	@name 
	dada.terrain.segment~
	
	@realname 
	dada.terrain.segment~

	@type
	abstraction
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
	Paths along lines
	
	@description
	Produces the coordinates of segment paths at sample rate.
	
	@discussion

	@category
	dada, dada abstractions

	@keywords
	terrain, coordinate, segment, line, sample, path 

	@seealso
	dada.terrain~, dada.terrain.ellipse~, dada.terrain.rect~, dada.terrain.spiral~
	
	@owner
	Daniele Ghisi
*/

// ---------------
// METHODS
// ---------------

// @method signal @digest Compute path
// @description An incoming signal is usually the output of a <o>phasor~</o> object,
// i.e. the phase of the path (from 0 = beginning, to 1 = end). The corresponding
// point on the segment path is computed and output.



// ---------------
// ATTRIBUTES
// ---------------

void main_foo() {

llllobj_class_add_out_attr(c, LLLL_OBJ_VANILLA);


CLASS_ATTR_CHAR(c, "polar", 0, t_terrain_segment, polar); 
CLASS_ATTR_STYLE_LABEL(c,"polar",0,"onoff","Output Polar Coordinates");
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"polar",0,"1");
// @description Toggles the ability to output polar coordinates (radius, from left
// outlet, and angle, from right outlet). By default it is active; if it is
// turned off, the output is in cartesian coordinates (X, from left outlet, and Y
// from right outlet).

CLASS_ATTR_DOUBLE_ARRAY(c, "start", 0, t_terrain_segment, start, 2); 
CLASS_ATTR_STYLE_LABEL(c,"start",0,"text","Start Point Cartesian Coordinates");
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"start",0,"0 0");
// @description Sets the cartesian coordinates (X, Y) of the starting point of the segment.

CLASS_ATTR_DOUBLE_ARRAY(c, "end", 0, t_terrain_segment, end, 2); 
CLASS_ATTR_STYLE_LABEL(c,"end",0,"text","End Point Cartesian Coordinates");
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"end",0," 0 0");
// @description Sets the cartesian coordinates (X, Y) of the ending point of the segment.

CLASS_ATTR_DOUBLE_ARRAY(c, "polarstart", 0, t_terrain_segment, start, 2); 
CLASS_ATTR_STYLE_LABEL(c,"polarstart",0,"text","Start Point Polar Coordinates");
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"polarstart",0,"0 0");
// @description Sets the polar coordinates (radius, angle) of the starting point of the segment.

CLASS_ATTR_DOUBLE_ARRAY(c, "polarend", 0, t_terrain_segment, end, 2); 
CLASS_ATTR_STYLE_LABEL(c,"polarend",0,"text","End Point Polar Coordinates");
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"polarend",0,"0 0");
// @description Sets the polar coordinates (radius, angle) of the ending point of the segment.


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

// @arg 0 @name polar @optional 1 @type symbol @digest Polar coordinates  
// @description If the first argument is the "polar" symbol, the following arguments
// are considered to be set in polar coordinates.

// @arg 1 @name startpoint @optional 1 @type list @digest Starting point  
// @description Sets the starting point of the segment path.
// If the first argument is the "polar" symbol, then the radius and angle
// are expected, otherwise the X and Y cartesian coordinates are expected.

// @arg 2 @name endpoint @optional 1 @type list @digest Ending point  
// @description Sets the ending point of the segment path.
// If the first argument is the "polar" symbol, then the radius and angle
// are expected, otherwise the X and Y cartesian coordinates are expected.
