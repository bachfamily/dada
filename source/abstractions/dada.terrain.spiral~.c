/**
	@file
	dada.terrain.spiral~.c
	
	@name 
	dada.terrain.spiral~
	
	@realname 
	dada.terrain.spiral~

	@type
	abstraction
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
	Paths along spirals
	
	@description
	Produces the coordinates of paths along Archimedean spirals at sample rate.
	
	@discussion
	The spiral equation is <m>r=a+b*theta</m>.

	@category
	dada, dada abstractions

	@keywords
	terrain, coordinate, spiral, line, sample, path, circle

	@seealso
	dada.terrain~, dada.terrain.rect~, dada.terrain.segment~, dada.terrain.ellipse~
	
	@owner
	Daniele Ghisi
*/

// ---------------
// METHODS
// ---------------

// @method signal @digest Compute path
// @description An incoming signal is usually the output of a <o>phasor~</o> object,
// i.e. the phase of the path (from 0 = beginning, to 1 = end). The corresponding
// point on the spiral path is computed and output.



// ---------------
// ATTRIBUTES
// ---------------

void main_foo() {

llllobj_class_add_out_attr(c, LLLL_OBJ_VANILLA);


CLASS_ATTR_CHAR(c, "polar", 0, t_terrain_spiral, polar); 
CLASS_ATTR_STYLE_LABEL(c,"polar",0,"onoff","Output Polar Coordinates");
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"polar",0,"1");
// @description Toggles the ability to output polar coordinates (radius, from left
// outlet, and angle, from right outlet). By default it is active; if it is
// turned off, the output is in cartesian coordinates (X, from left outlet, and Y
// from right outlet).

CLASS_ATTR_DOUBLE_ARRAY(c, "center", 0, t_terrain_spiral, center, 2); 
CLASS_ATTR_STYLE_LABEL(c,"center",0,"text","Spiral Center");
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"center",0,"0 0");
// @description Sets the cartesian coordinates of the spiral center.

CLASS_ATTR_DOUBLE(c, "a", 0, t_terrain_spiral, a); 
CLASS_ATTR_STYLE_LABEL(c,"a",0,"text","Turn Parameter");
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"a",0,"0");
// @description Parameter controlling the angle of the spiral turn.
// It corresponds to the parameter <m>a</m> in the equation <m>r=a+b*theta</m>.

CLASS_ATTR_DOUBLE(c, "b", 0, t_terrain_spiral, b); 
CLASS_ATTR_STYLE_LABEL(c,"b",0,"text","Distance Parameter");
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"b",0,"1");
// @description Parameter controlling the distance between successive turnings.
// It corresponds to the parameter <m>b</m> in the equation <m>r=a+b*theta</m>.

CLASS_ATTR_DOUBLE(c, "n", 0, t_terrain_spiral, n); 
CLASS_ATTR_STYLE_LABEL(c,"n",0,"text","Number Of Turnings");
CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"n",0,"1");
// @description Sets the number of spiral turnings.


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

// @arg 0 @name a @optional 1 @type double @digest Turn Parameter
// @description Sets the initial value for the turn parameter <m>a</m>.

// @arg 1 @name b @optional 1 @type double @digest Distance parameter
// @description Sets the initial value for the distance parameter <m>b</m>.

// @arg 2 @name num_turns @optional 1 @type double @digest Number of turnings
// @description Sets the initial number of turnings.

// @arg 3 @name xc @optional 1 @type double @digest Center X 
// @description Sets the initial X coordinate of the spiral center.

// @arg 4 @name yc @optional 1 @type double @digest Center Y
// @description Sets the initial Y coordinate of the spiral center.

