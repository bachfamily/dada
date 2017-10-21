/**
	@file	dada_doc_commons_dg.h
	@brief	Common documentation about some basic concepts and syntaxes of dada.
	
	by Daniele Ghisi
*/

	
#define DADA_DOC_SYNTAX_GRAPH
	//	Graph syntax in dada is the following one <b>(<m>VERTEX1</m> <m>VERTEX2</m>...) (<m>EDGE1</m> <m>EDGE2</m>...)</b>.
    //  Each vertex is an llll shaped as <b>((coord <m>x</m> <m>y</m>) <m>METADATA1</m> <m>METADATA2</m>...)</b>.
    //  Each edge is an llll shaped as <b>(<m>edge_start_vertex_index</m> <m>edge_end_vertex_index</m> <m>METADATA1</m> <m>METADATA2</m>...)</b>,
    //  where the indices of the vertices are 1-based, and correspond to the position on the vertices in the corresponding vertices llll.
    //  The <m>METADATA</m> llll may depend on the graph metadata type. For instance, if the edges or vertices contain information about pitch
    //  and velocity, they might be something like <b>(pitch <m>midicents_value</m>)</b> and/or <b>(velocity <m>velocity_value</m>)</b>.
	//  <br /> <br />

#define DADA_DOC_SYNTAX_FLAGS
    //	Item flags syntax in dada is the following one <b>(flags <m>flag1</m> <m>flag2</m>...)</b>, where each flag is one of the following symbols:
    // <b>lock</b>, <b>mute</b>, <b>solo</b>, <b>inactive</b>.
    //  <br /> <br />

#define DADA_DOC_SYNTAX_BALL
	// 	The
	//  <br /> <br />


#define DADA_DOC_MOUSE_COMMANDS_STANDARD_NAVIGATION
    // • <m>mousewheel scroll</m>: move the visible region <br />
    // • <m>Cmd+mousewheel scroll</m> (mac) or <m>Ctrl+mousewheel scroll</m> (win): change zoom <br />
    // • <m>right-click</m> or <m>two-fingers tap</m>: open contextual menu for basic operations<br />

#define DADA_DOC_KEYBOARDS_COMMANDS_STANDARD_NAVIGATION
    // • <m>Esc</m>: reset center to (0, 0) and zoom to 100%<br />
    // • <m>Tab</m>: autozoom<br />


#define DADA_DOC_TOOLS_INTRO
    // Tools are combination of a specific key pressed and some mouse action. Whenever you press the key, if the tool is available,
    // the mouse cursor will switch to the tool specific one. <br />
    // Available tools are: <br />

#define DADA_DOC_TOOLS_Z
    // • Keep the <m>Z</m> key pressed, then click and drag on the canvas to change the zoom <br />

#define DADA_DOC_TOOLS_X
    // • Keep the <m>X</m> key pressed, then click and drag on the canvas to move the displayed center <br />

#define DADA_DOC_TOOLS_ZX
    // @copy DADA_DOC_TOOLS_Z
    // @copy DADA_DOC_TOOLS_X

#define DADA_DOC_TOOLS_N
    // • Keep the <m>N</m> key pressed, click on the desired element and drag up or down in order to modify its pitch. <br />

#define DADA_DOC_TOOLS_V
    // • Keep the <m>V</m> key pressed, click on the desired element and drag up or down in order to modify its velocity. <br />

#define DADA_DOC_TOOLS_S
    // • Keep the <m>S</m> key pressed, click on the desired element and drag up or down in order to scale its magnitude or value. <br />

#define DADA_DOC_TOOLS_R
    // • Keep the <m>R</m> key pressed, click on the desired element and drag up or down in order to rotate it. <br />

#define DADA_DOC_TOOLS_L
    // • Keep the <m>L</m> key pressed, click on an element, keep the mouse down and release the mouse on another element to connect the two elements. <br />

#define DADA_DOC_TOOLS_Q
    // • Keep the <m>Q</m> key pressed, click on an element, drag up or down to modify the color hue or saturation. <br />

#define DADA_DOC_TOOLS_A
    // • Keep the <m>A</m> key pressed, click on the background, and drag to create a selection rectangle. <br />
    //    ↪ Add the <m>Shift</m> key to preserve previous selection<br />

#define DADA_DOC_TOOLS_NV
    // @copy DADA_DOC_TOOLS_N
    // @copy DADA_DOC_TOOLS_V

#define DADA_DOC_TOOLS_SR
    // @copy DADA_DOC_TOOLS_S
    // @copy DADA_DOC_TOOLS_R

