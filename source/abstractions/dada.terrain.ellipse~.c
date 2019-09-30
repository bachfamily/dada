/**
	@file
	dada.terrain.ellipse~.c
	
	@name 
	dada.terrain.ellipse~
	
	@realname 
	dada.terrain.ellipse~

	@type
	abstraction
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
	Paths along circles or ellipses
	
	@description
	Produces the coordinates of paths along ellipses at sample rate.
	
	@discussion

	@category
	dada, dada abstractions

	@keywords
	terrain, coordinate, ellipse, line, sample, path, circle

	@seealso
	dada.terrain~, dada.terrain.rect~, dada.terrain.segment~, dada.terrain.spiral~
	
	@owner
	Daniele Ghisi
*/

// ---------------
// METHODS
// ---------------

// @method signal @digest Compute path
// @description An incoming signal is usually the output of a <o>phasor~</o> object,
// i.e. the phase of the path (from 0 = beginning, to 1 = end). The corresponding
// point on the ellipse path is computed and output.



// ---------------
// ATTRIBUTES
// ---------------

void main_foo() {

llllobj_class_add_out_attr(c, LLLL_OBJ_VANILLA);


CLASS_ATTR_CHAR(c, "polar", 0, t_terrain_ellipse, polar); 
CLASS_ATTR_STYLE_LABEL(c,"polar",0,"onoff","Output Polar Coordinates");
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"polar",0,"1");
// @description Toggles the ability to output polar coordinates (radius, from left
// outlet, and angle, from right outlet). By default it is active; if it is
// turned off, the output is in cartesian coordinates (X, from left outlet, and Y
// from right outlet).

CLASS_ATTR_DOUBLE_ARRAY(c, "center", 0, t_terrain_ellipse, center, 2); 
CLASS_ATTR_STYLE_LABEL(c,"center",0,"text","Ellipse Center");
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"center",0,"0 0");
// @description Sets the cartesian coordinates of the ellipse center.

CLASS_ATTR_DOUBLE(c, "a", 0, t_terrain_ellipse, a); 
CLASS_ATTR_STYLE_LABEL(c,"a",0,"text","First Axis Size");
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"a",0,"1");
// @description Sets the size of the first ellipse axis.

CLASS_ATTR_DOUBLE(c, "b", 0, t_terrain_ellipse, b); 
CLASS_ATTR_STYLE_LABEL(c,"b",0,"text","Second Axis size");
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"b",0,"1");
// @description Sets the size of the second ellipse axis.

CLASS_ATTR_DOUBLE(c, "rot", 0, t_terrain_ellipse, rot); 
CLASS_ATTR_STYLE_LABEL(c,"rot",0,"text","Rotation");
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"rot",0,"0");
// @description Sets the ellipse rotation angle, in radians.


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

// @arg 0 @name a @optional 1 @type double @digest First axis size
// @description Sets the initial size of the first ellipse axis.

// @arg 1 @name b @optional 1 @type double @digest Second axis size
// @description Sets the initial size of the second ellipse axis.

// @arg 2 @name rot @optional 1 @type double @digest Rotation angle
// @description Sets the initial ellipse rotation angle, in radians.

// @arg 3 @name xc @optional 1 @type double @digest Center X 
// @description Sets the initial X coordinate of the ellipse center.

// @arg 4 @name yc @optional 1 @type double @digest Center Y
// @description Sets the initial Y coordinate of the ellipse center.

