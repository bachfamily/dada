/**
	@file
	dada.object.h
	Header for the definition of a dada object
 
	by Daniele Ghisi
 */

#ifndef _DADA_OBJECT_H_
#define _DADA_OBJECT_H_

#include "dada.h"
#include "notation/notation.h"


#define	DADA_DEFAULT_MAX_DECIMALS 6

#define DADA_MAX_INLETS	256
#define DADA_MAX_OUTLETS	256

#define DADA_AXIS_ARROW_SIZE 8

#define DADA_MAX_NUM_POPUP_SUBMENUS 20	///< Maximum number of popup submenus (also counting the base popup menu)
#define DADA_MAX_DADAITEM_CLASSES 10	///< Maximum number of declared item types inside a dada objects

#define t_dada_atomic_lock t_int32_atomic


#define FOR_ALL_VIEWS(r_ob) for (t_object *view = dadaobj_get_firstview(r_ob); view; view = patcherview_get_nextview(view))

// Utility to cast a pointer to a class to the dadaobj (which is the second element, after the root object
#define dadaobj_cast(x) (&x->b_ob.d_ob)

// Utility to calculate the offset between the dadaobj class and a given structure
#define dadaobj_jbox_calcoffset(x,y) (calcoffset(x,y)-sizeof(t_llllobj_jbox))


// ATTRIBUTES MACROS WITH SUBSTRUCTURES
#define headersize(type) (type == LLLL_OBJ_UI ? sizeof(t_llllobj_jbox) : (type == LLLL_OBJ_UIMSP ? sizeof(t_llllobj_pxjbox) : (type == LLLL_OBJ_MSP ? sizeof(t_llllobj_pxobject) : (type == LLLL_OBJ_VANILLA ? sizeof(t_llllobj_object) : 0)))) 

#define DADAOBJ_CLASS_ATTR_DOUBLE(c,type,attrname,flags,structname,structmember) \
class_addattr((c),attr_offset_new(attrname,USESYM(float64),(flags),(method)0L,(method)0L,calcoffset(structname,structmember)+headersize(type)))

#define DADAOBJ_CLASS_ATTR_CHAR(c,type,attrname,flags,structname,structmember) \
class_addattr((c),attr_offset_new(attrname,USESYM(char),(flags),(method)0L,(method)0L,calcoffset(structname,structmember)+headersize(type)))

#define DADAOBJ_CLASS_ATTR_LONG(c,type,attrname,flags,structname,structmember) \
class_addattr((c),attr_offset_new(attrname,USESYM(long),(flags),(method)0L,(method)0L,calcoffset(structname,structmember)+headersize(type)))

#define DADAOBJ_CLASS_ATTR_DOUBLE_ARRAY(c,type,attrname,flags,structname,structmember,size) \
class_addattr((c),attr_offset_array_new(attrname,USESYM(float64),(size),(flags),(method)0L,(method)0L,0/*fix*/,calcoffset(structname,structmember)+headersize(type)))


    #define DADAOBJ_CLASS_ATTR_CHAR_SUBSTRUCTURE(c,type,attrname,flags,structname,structmember,substructname,substructmember) \
        class_addattr((c),attr_offset_new(attrname,USESYM(char),(flags),(method)0L,(method)0L,calcoffset(structname,structmember)+calcoffset(substructname,substructmember)+headersize(type)))

#define DADAOBJ_CLASS_ATTR_LONG_SUBSTRUCTURE(c,type,attrname,flags,structname,structmember,substructname,substructmember) \
	{		\
		C74_STATIC_ASSERT(structmembersize(substructname,substructmember)==sizeof(long), "structmember must be long type"); \
		class_addattr((c),attr_offset_new(attrname,USESYM(long),(flags),(method)0L,(method)0L,calcoffset(structname,structmember)+calcoffset(substructname,substructmember)+headersize(type))); \
	}

#define DADAOBJ_CLASS_ATTR_DOUBLE_SUBSTRUCTURE(c,type,attrname,flags,structname,structmember,substructname,substructmember) \
	class_addattr((c),attr_offset_new(attrname,USESYM(float64),(flags),(method)0L,(method)0L,calcoffset(structname,structmember) + calcoffset(substructname,substructmember)+headersize(type)))

#define DADAOBJ_CLASS_ATTR_DOUBLE_ARRAY_SUBSTRUCTURE(c,type,attrname,flags,structname,structmember,substructname,substructmember,size) \
	class_addattr((c),attr_offset_array_new(attrname,USESYM(float64),(size),(flags),(method)0L,(method)0L,0/*fix*/,calcoffset(structname,structmember)+calcoffset(substructname,substructmember)+headersize(type)))

#define DADAOBJ_CLASS_ATTR_SYM_SUBSTRUCTURE(c,type,attrname,flags,structname,structmember,substructname,substructmember) \
class_addattr((c),attr_offset_new(attrname,USESYM(symbol),(flags),(method)0L,(method)0L,calcoffset(structname,structmember)+calcoffset(substructname,substructmember)+headersize(type)))

#define DADAOBJ_CLASS_ATTR_ATOM_SUBSTRUCTURE(c,type,attrname,flags,structname,structmember,substructname,substructmember) \
class_addattr((c),attr_offset_new(attrname,USESYM(atom),(flags),(method)0L,(method)0L,calcoffset(structname,structmember)+calcoffset(substructname,substructmember)+headersize(type)))


#define DADAOBJ_CLASS_ATTR_RGBA_SUBSTRUCTURE(c,type,attrname,flags,structname,structmember,substructname,substructmember) \
	{	DADAOBJ_CLASS_ATTR_DOUBLE_ARRAY_SUBSTRUCTURE(c,type,attrname,flags,structname,structmember,substructname,substructmember,4); \
		CLASS_ATTR_ACCESSORS(c,attrname,NULL,jgraphics_attr_setrgba); \
		CLASS_ATTR_PAINT(c,attrname,0); }


#define DADAOBJ_JBOX_DECLARE_READWRITE_METHODS(c) \
class_addmethod(c, (method) dadaobj_jbox_read, "read", A_GIMME, 0); \
class_addmethod(c, (method) dadaobj_jbox_write, "write", A_GIMME, 0); \
class_addmethod(c, (method) dadaobj_jbox_writetxt, "writetxt", A_GIMME, 0); \
class_addmethod(c, (method) dadaobj_jbox_readsinglesymbol, "readsinglesymbol", A_GIMME, 0);

#define DADAOBJ_JBOX_DECLARE_ACCEPTSDRAG_METHODS(c) \
class_addmethod(c, (method) dadaobj_jbox_acceptsdrag,	"acceptsdrag_unlocked", A_CANT, 0); \
class_addmethod(c, (method) dadaobj_jbox_acceptsdrag,	"acceptsdrag_locked", A_CANT, 0);

#define DADAOBJ_JBOX_DECLARE_IMAGE_METHODS(c) \
class_addmethod(c, (method) dadaobj_jbox_exportimage, "exportimage", A_GIMME, 0); \
class_addmethod(c, (method) dadaobj_jbox_paintjit, "paintjit", A_SYM, 0); \
class_addmethod(c, (method) dadaobj_jbox_mt, "mt", A_GIMME, 0);



/** A thread-safe storage cache for lists, in GIMME signature form */
/*typedef struct _dadaobj_store
{
	long				ac;
	t_atom				*av;
	t_sy_atomic_lock	s_lock;
} t_dadaobj_store;
*/



typedef enum _dadaobj_flags 
{
	DADAOBJ_ZOOMX			= 0x00001,	///< Can zoom in the X direction
	DADAOBJ_ZOOMY			= 0x00002,	///< Can zoom in the Y direction
	DADAOBJ_CENTEROFFSETX	= 0x00004,	///< Can offset the center in the X direction
	DADAOBJ_CENTEROFFSETY	= 0x00008,	///< Can offset the center in the Y direction
	DADAOBJ_UNDO			= 0x00010,	///< Can perform undo/redo
	DADAOBJ_EMBED			= 0x00020,	///< Can save with patcher
	DADAOBJ_MOUSEHOVER		= 0x00040,	///< Has mouseover capabilities
	DADAOBJ_GRID			= 0x00080,	///< Can show grid
	DADAOBJ_PLAY			= 0x00100,	///< Has sequencing capabilities
	DADAOBJ_SELECTION		= 0x00200,	///< Has high-level selection handling
	DADAOBJ_SPLITXYZOOM		= 0x00400,	///< Can zoom independently in X and Y direction
	DADAOBJ_INSPECTOR		= 0x00800,	///< Has inspector
	DADAOBJ_CHANGEDBANG		= 0x01000,	///< Can send changed bang
    DADAOBJ_GRID_SHOWDEFAULT= 0x02000,	///< Will show grid by default
    DADAOBJ_BORDER          = 0x04000,	///< Has border
    DADAOBJ_BG              = 0x08000,	///< Has background
    DADAOBJ_BGIMAGE         = 0x10000,	///< Supports background image
    DADAOBJ_AXES            = 0x20000,	///< Can show axes
    DADAOBJ_AXES_SHOWDEFAULT= 0x40000,	///< Show axes is the default
    DADAOBJ_SNAPTOGRID      = 0x80000,	///< Can snap to grid
    DADAOBJ_NOTIFICATIONS	= 0x100000,	///< Can send notifications
	DADAOBJ_ZOOM			= DADAOBJ_ZOOMX + DADAOBJ_ZOOMY, //< Can zoom in both directions
	DADAOBJ_CENTEROFFSET	= DADAOBJ_CENTEROFFSETX + DADAOBJ_CENTEROFFSETY,	///< Can offset the center in any direction
    DADAOBJ_BBG             = DADAOBJ_BORDER + DADAOBJ_BG, //< Has border and background
    DADAOBJ_BBGIMAGE        = DADAOBJ_BORDER + DADAOBJ_BG + DADAOBJ_BGIMAGE, //< Has border, background and image
    DADAOBJ_LABELS            = 0x200000,	///< Can show labels
    DADAOBJ_LABELS_SHOWDEFAULT= 0x400000,	///< Show labels is the default
    DADAOBJ_BORDER_SHOWDEFAULT= 0x800000,	///< Show border by default
    DADAOBJ_EXPORTTOJITTER    = 0x1000000,    ///< Supports export to Jitter
    DADAOBJ_GRID_FIXEDDEFAULT  = 0x2000000,    ///< Use fixed grid by default
} e_dadaobj_flags;


typedef enum e_dadaobj_notify_type
{
    DADAOBJ_NOTIFY_DONT = 0,
    DADAOBJ_NOTIFY_BASIC = 1,
    DADAOBJ_NOTIFY_VERBOSE = 2
} e_dadaobj_notify_type;



typedef enum _dadaobj_tools
{
	DADA_TOOL_ARROW = 0,				///< Standard pointer
	DADA_TOOL_ROTATE = 'r',				///< Rotation tool
	DADA_TOOL_SCALE = 's',				///< Scale tool
	DADA_TOOL_CHANGE_COLOR = 'q',		///< Change color tool
	DADA_TOOL_CHANGE_PITCH = 'n',		///< Change pitch tool
	DADA_TOOL_CHANGE_VELOCITY = 'v',	///< Change velocity tool
	DADA_TOOL_ZOOM = 'z',				///< Change zoom
	DADA_TOOL_MOVE_CENTER = 'x',		///< Move display center
	DADA_TOOL_CREATE_LINE = 'l',		///< Connect points, create line
	DADA_TOOL_WRITE = 'w',				///< Write
	DADA_TOOL_ERASE = 'e',				///< Erase
	DADA_TOOL_SELECT = 'a',				///< Select
	DADA_TOOL_FADE = 'f',				///< Fade
	DADA_TOOL_CURVE = 'c',				///< Curve tool
	DADA_TOOL_MOVE_UP_DOWN = 'd',		///< Move up/down
} e_dadaobj_tools;



typedef struct dada_force_graphics
{
    t_jgraphics             *graphic_context;
    t_rect                  rect;
    
    t_pt                    zoom;
    t_pt                    center_offset;
    t_pt                    center_pix;
} t_dada_force_graphics;



typedef void (*invalidate_and_redraw_fn)(t_object *r_ob);
typedef long (*dada_mousemove_fn)(t_object *r_ob, t_object *patcherview, t_pt pt, long modifiers);
typedef t_llll *(*get_state_fn)(t_object *r_ob);
typedef void (*set_state_fn)(t_object *r_ob, t_llll *ll);
typedef void *(*pixel_to_dadaitem_fn)(void *dadaobj, t_pt pt, t_object *view, long modifiers, t_pt *coordinates, double selection_pad, void *dadaitem_identifier);
typedef void *(*preselect_items_in_rectangle_fn)(void *dadaobj, t_object *view, t_rect coord);
typedef void (*update_solos_fn)(t_object *r_ob);
typedef void (*dada_paint_ext_fn)(t_object *x, t_object *view, t_dada_force_graphics *force_graphics);

//// DADA ITEMS




typedef enum _dadaitem_types 
{
	DADAITEM_TYPE_CUSTOM = -1,				///< A custom element
	DADAITEM_TYPE_NONE = 0,
	DADAITEM_TYPE_BALL,					///< A #t_dada_ball, a ball having coordinates, speed, color and MIDIchannel
	DADAITEM_TYPE_NODE,					///<
	DADAITEM_TYPE_VERTEX,				///< A #t_dada_graph_vertex, a vertex of a graph
	DADAITEM_TYPE_EDGE,					///< An edge of a graph
	DADAITEM_TYPE_CONNECTED_COMPONENT,	///< A connected component of a graph
	DADAITEM_TYPE_CARD,					///< Some text with posibly an icon
	DADAITEM_TYPE_GAMECHAR,				///< A videogame character
	DADAITEM_TYPE_BLOCK,				///< A rectangular block, as in platform games
	DADAITEM_TYPE_COIN,					///< A coin, as in platform games
    DADAITEM_TYPE_PORTAL,				///< A "portal", as in platform games
    DADAITEM_TYPE_LEVEL,				///< A game level
	
	//	DADAITEM_TYPE_TESTER,				///< A generic tester
} e_dadaitem_types;


typedef enum _dadaitem_flags 
{
	D_NONE		= 0x00,	///< No flag
	D_SOLO		= 0x01,	///< Solo
	D_MUTE		= 0x02,	///< Mute
	D_LOCK		= 0x04,	///< Lock
	D_INACTIVE	= 0x08,	///< Inactive
    D_SOLITARY	= 0x10,	///< Solitary
} e_dadaitem_flags;

typedef enum _dadaitem_internal_flags
{
    DADAITEM_FLAG_NONE          = 0x00,	///< No flag
    DADAITEM_FLAG_TOPROCESS		= 0x01,	///< Item must be processed
} e_dadaitem_internal_flags;


typedef enum _dada_attribute_flags
{
    DADA_ATTRIBUTE_FLAG_NONE            = 0x00,	///< No flag
    DADA_ATTRIBUTE_FLAG_DONTRETRIEVE	= 0x01,	///< Attribute will not be retrieven
    DADA_ATTRIBUTE_FLAG_DONTSET         = 0x02,	///< Attribute will not be set
} e_dada_attribute_flags;



typedef struct _dadaitem
{
	long				ID;				///< Currently unused
	e_dadaitem_types	type;			
	
    t_symbol            *name;          ///< Name (or NULL if none)
    
	t_pt				coord;			///< Coordinates of the center, or in any case of the "hotspot"
	double				height;
	double				width;
	
	t_jrgba				color;			///< Color of the item
	
	long				flags;			///< A combination of #e_dadaitem_flags
    long				internal_flags;	///< A combination of #e_dadaitem_internal_flags, typically for internal operations and flagging
	
	t_llllelem			*pos;			///< Pointer to the element in the class llll (if allocation is DADA_ITEM_ALLOC_OBJLLLL)
	struct _dadaitem	*parent;		///< Parent, if any 

	t_llllelem			*selected;		///< Pointer to the element in the selection llll (if selected, or NULL if unselected)
	t_llllelem			*preselected;	///< Pointer to the element in the preselection llll (if selected, or NULL if unselected)
	
	char				dirty;			///< (INTERNAL) Has been modified before undo step
} t_dadaitem;


typedef t_max_err (*dadanotify_fn)(void *dadaobj, t_symbol *s, t_symbol *modified, t_dadaitem *it, void *data);


typedef enum _dadaitem_identifier_flags
{
	DADAITEM_IDENTIFIER_FLAG_NONE = 0,			///< No shape
	DADAITEM_IDENTIFIER_FLAG_DUPLICATED = 1,	///< Identified element has been duplicated
} e_dadaitem_identifier_flags;


typedef struct _dadaitem_identifier
{
	long	type;	// one of the #e_dadaitem_types or a custom type, if customly defined
					// USE NEGATIVE VALUES WHEN YOU DEFINE CUSTOM TYPES
	long	idx;
	long	secondary_idx;		//< Used mostly for points of shapes, or "sons" of something
    long	tertiary_idx;		//< Almost never used
	long	flag;
} t_dadaitem_identifier;


//// MANAGERS



typedef struct _popupmenu_manager
{
	long			num_popup_menus;
	t_jpopupmenu	*popup_menus[DADA_MAX_NUM_POPUP_SUBMENUS];
	t_llll			*pointers_to_func;	// plain list of pointers to function (places corresponding to element IDs in submenus)
	t_llll			*labels;			// plain list of labels (places corresponding to element IDs in submenus)
	t_llll			*addresses;			// 2-depth list containing all the addresses of elements in the menus (places corresponding to element IDs in submenus)
	char			popup_is_shown;
	struct _dadaitem		*curr_popup_item;
} t_popupmenu_manager;


typedef struct _cursor_resources
{
	t_jsurface *s_cursor_changecolor;
	t_jsurface *s_cursor_rotate;
	t_jsurface *s_cursor_scale;
	t_jsurface *s_cursor_delete;
	t_jsurface *s_cursor_addpoint;
	t_jsurface *s_cursor_deletepoint;
	t_jsurface *s_cursor_duplicatepoint;
	t_jsurface *s_cursor_changepitch;
	t_jsurface *s_cursor_changevelocity;
	t_jsurface *s_cursor_pencil;
	t_jsurface *s_cursor_eraser;
	t_jsurface *s_cursor_glue;
} t_cursor_resources;


typedef struct _cursor_manager
{
	int							curr_cursor;	///< Current cursor
	t_cursor_resources			resources;		///< Embedded surfaces
} t_cursor_manager;


typedef struct _tool_manager
{
	char				curr_tool;			///< Current tool
	char				allowed_tools[50];	///< String with the allowed tool keys
	dada_mousemove_fn	mousemove_fn;		///< Pointer to the object's mousemove function, 
											///  used to customly modify mousepointer when keys are pressed, or whenever the
											///  cursor pointer reparsing has to be done
} t_tool_manager;


typedef struct _play_manager
{
	double		play_step_ms;						///< Duration in milliseconds of one of the <play_num_steps> steps to schedule
	char		is_playing;
	void		*m_clock;							///< The clock for the play and task routine
	t_symbol	*setclock;							///< The setclock, to handle the change of clock speed

    t_jrgba     play_color;                         ///< Color for playing
	long		play_out_num;

	char		has_solos;							///< Some dada item has been marked as solo
} t_play_manager;


typedef struct _undo_manager
{
	// attributes
	long		max_num_steps;
	char		verbose_undo;
    char        undo_before_play;       ///< Do we add an undo step just before playing?
	
	// content
	t_llll		*undo;
	t_llll		*redo;
	long		num_undo_steps;
	long		num_redo_steps;
	
	method		post_process_fn;
	
	// internal
	t_llll		*dirty_items;			///< Items on which undo tick has already been added
	t_symbol*	need_push_marker;
} t_undo_manager;




typedef struct _interface_manager
{
    char			allow_mouse_hover;
    char			send_notifications;
    
	char			has_focus;
	char			has_been_dragged;
    char			has_been_modified_while_mousedown;
	char			main_drag_direction; ///< 1 = horizontal, -1 = vertical
	char			mouse_is_over;
	char			mouse_is_down;
	
	t_pt					mousedown_coord;
	t_pt					mousedown_pix;
	t_dadaitem				*mousedown_item;
    t_dadaitem				*last_mousedown_item;
	struct _dadaitem_identifier	mousedown_item_identifier;

	t_pt					mousedrag_coord;
	t_pt					mousedrag_pix;
	t_pt					mousedrag_delta_coord;
	t_pt					mousedrag_delta_pix;

	t_pt					mousemove_coord;
	t_pt					mousemove_pix;
	t_dadaitem				*mousemove_item;
	struct _dadaitem_identifier	mousemove_item_identifier;

	t_llll			*preselection;
	t_llll			*selection;
    
    double          selection_tolerance;
	
    long			notifications_out_num;
	long			changebang_out_num;
	char			continuously_send_changebang; // upon drag
	char			send_bang_from_messages;
	char			send_bang_upon_undo;

    pixel_to_dadaitem_fn                pixel_to_dadaitem;
    preselect_items_in_rectangle_fn        preselect_items_in_rectangle;
    
} t_interface_manager;



// x stands for llll, capital letters are the get-set variable
typedef enum _dada_func_types {
	// versions with object as pointer ( o = t_object*)
    DADA_FUNC_NONE = 0,
    
	DADA_FUNC_X_o,
	DADA_FUNC_X_d,
	DADA_FUNC_v_oX,
	DADA_FUNC_v_dX,
	DADA_FUNC_v_otX,
	DADA_FUNC_v_dtX,
    DADA_FUNC_v_dtXf, // f = flag
	DADA_FUNC_X_ot,	// t_llll* = f(t_object*, type)
	DADA_FUNC_X_dt,	// t_llll* = f(t_object*, type)

	// versions with dada-object as pointer (d = t_dadaobj*)
	DADA_FUNC_v_diX, // i = item ID (long)
	DADA_FUNC_X_di,	// t_llll* = f(t_object*, long iD)
} e_dada_func_types;


typedef enum _dada_lattice_types {
	DADA_LATTICE_SQUARE = 0,
	DADA_LATTICE_TRIANGLE = 1,
} e_dada_lattice_types;

typedef enum _dadaitem_alloc_type {
	DADA_ITEM_ALLOC_DONT = 0,
	DADA_ITEM_ALLOC_ARRAY = 1,
	DADA_ITEM_ALLOC_OBJLLLL = 2,
    DADA_ITEM_ALLOC_ARRAY_DONT = 3, // already array-allocated, but don't need epxlicit memory allocation
} e_dadaitem_alloc_type;

typedef struct _dadaitem_class
{
	e_dadaitem_types	type;
	
	t_symbol			*name;			//< A lower case identifier, e.g.: "gamechar"
	t_symbol			*label;			//< An upper case label, e.g. "Game Character"
	
	long					element_have_ID;	//< Do class items have IDs?
	e_dadaitem_alloc_type	alloc_type;
	long					parent_class_id;	//< Currently unsupported

	long					element_size;
	long					struct_offset;
	long					max_num_items;
    long                    *num_items_field;   //< If this is not null, this has the precedence on the num_items statically assigned
	long					num_items;
	
    char                selectable;
    char                include_in_background;

	// Whole class set/get
	e_dada_func_types	data_set_type;
	method				data_set_fn;
	t_llll				*data_set_args;
	
	e_dada_func_types	data_get_type;
	method				data_get_fn;
	t_llll				*data_get_args;

	// Set/get of single class elements
	e_dada_func_types	data_single_set_type;
	method				data_single_set_fn;
	t_llll				*data_single_set_args;
	
	e_dada_func_types	data_single_get_type;
	method				data_single_get_fn;
	t_llll				*data_single_get_args;

	method				free_fn;		// Function to free the single dada item, if needed (or NULL)
	method				identifier_to_dadaitem_fn;
    method              postprocess_fn; // process after modification

	char				dirty; // utility flag for undo
} t_dadaitem_class;


typedef struct _item_class_manager
{
	long				num_di_classes;
	t_dadaitem_class	di_class[DADA_MAX_DADAITEM_CLASSES];
} t_item_class_manager;


typedef struct _grid_manager
{
	char			snap_to_grid;

    char            grid_mode; // 0 = fixed, 1 = auto;
	t_pt			grid_size_fixed; // only meaningful if grid_mode == 0
    t_pt            grid_size_curr;  // current grid size, used if grid_mode == 1
    char            must_update_grid_size;
    
    char			show_grid;
	t_jrgba			j_gridcolor;

    char			show_axes;
    t_jrgba			j_axescolor;

    char			show_axes_labels;
    t_jrgba			j_axeslabelscolor;
    t_symbol		*x_label;
    t_symbol		*y_label;
    double          axeslabelsfontsize;

    char			show_labels;
    t_jrgba			j_labelscolor;
    double          labelsfontsize;
} t_grid_manager;



typedef struct _geometry_manager
{
    double                  last_used_view_width_pix;
    double                  last_used_view_height_pix;
    
	e_dada_lattice_types	lattice;
} t_geometry_manager;


typedef struct _zoom_manager
{
	// Zoom and offset
	double			zoom_perc;				///< Zoom as percentage, 100 means: 1 pixel = 1 coord (up to the additional zoom factor)
	double			zoom_y_perc;			///< Y Zoom as percentage (only used if X and Y zooms are uncorrelated)
	t_pt			zoom_static_additional;	///< Additional static zoom factor (for each dada object, x and y components)
	t_pt			zoom;					///< Zoom as ratio (x and y), 1. means 1 pixel = 1 coord. This is a resulting zoom of zoom_perc and zoom_static_additional
	t_pt			center_offset;			///< Offset of the center
	char			allow_zoom;				///< Allow interface zooming
	char			allow_center_shifting;	///< Allow interface center shifting
	
	t_pt			max_zoom_perc;			///< Maximum allowed zoom percentage
	t_pt			min_zoom_perc;			///< Minimum allowed zoom percentage
    
    
    // utility flag
    char            must_autozoom;          ///< Must autozoom at next paint cycle
} t_zoom_manager;


typedef struct _bg_manager
{
    t_jsurface		*bg_surface;
    t_symbol		*bg_image;
    t_jrgba         bgcolor;
    t_jrgba         bordercolor;
    char            show_border;
    char            show_focus;
} t_bg_manager;


typedef struct _paint_manager
{
    t_symbol                    *jit_destination_matrix;
    char                        dont_repaint;            ///< When this flag is 1, the object is not repainted from dada API
    char                        notify_when_painted;

    invalidate_and_redraw_fn    invalidate_and_redraw;
    dada_paint_ext_fn           paint_ext;              ///< Actual generalized paint function
} t_paint_manager;

typedef struct _mt_manager
{
    // mira/miraweb: stuff designed to work with mira.multitouch
    char finger_state[10];                   ///< State of each finger
    t_pt finger_pos[10];                     ///< Positions of each finger (in pixels)
    char pinching;                           ///< Flag telling whether there's pinching going on
    t_pt zoom_at_pinch_start;                ///< Zoom at the moment the pinch started (X and Y)
} t_mt_manager;


/** The structure for a generic UI object in the dada library */
typedef struct dadaobj
{
	t_object				*orig_obj;		///< Pointer to the original object
    e_llllobj_obj_types     llllobj_type;  ///< Type of llll object
    
	long					flags;			///< A combination of the #e_dadaobj_flags
    
    t_atom_long                 m_version_number;
	
	t_item_class_manager		m_classes;	
	t_bach_inspector_manager	m_inspector;
	t_popupmenu_manager			m_popup_menu;
	t_cursor_manager			m_cursors;
	t_tool_manager				m_tools;
	t_play_manager				m_play;
	t_undo_manager				m_undo;
	t_interface_manager			m_interface;
	t_grid_manager				m_grid;
	t_geometry_manager			m_geometry;
	t_zoom_manager				m_zoom;
    t_bg_manager                m_bg;
    t_paint_manager             m_paint;
    t_mt_manager                m_mt;
	
    t_dada_atomic_lock        l_lock;
    t_systhread_mutex        l_mutex;        ///< Generic mutex for the object
    
    t_shashtable    *IDtable;                ///< A simple hash table containing item hash
    
	// Behavior
	char			save_data_with_patcher;
    char            curr_change_is_from_message;

	// Preset fields 
    t_atom           *preset_av;
    long            preset_ac;
	get_state_fn	get_state;
	set_state_fn	set_state;
	
	// Notifications
	dadanotify_fn	    dadanotify;
    update_solos_fn     update_solos;

} t_dadaobj;

typedef struct dadaobj_jbox
{
	t_llllobj_jbox			r_ob;
	t_dadaobj				d_ob;
} t_dadaobj_jbox;

typedef struct dadaobj_pxjbox
{
	t_llllobj_pxjbox		r_ob;
	t_dadaobj				d_ob;
} t_dadaobj_pxjbox;








/// handling version numbers
long dada_check_bach_version();
void dada_error_bachcheck();

long dada_get_current_version_number();
void dadaobj_set_version_number(t_dadaobj *d_ob, long version_number);
void dadaobj_set_current_version_number(t_dadaobj *d_ob);

/// atomic locks
void dada_atomic_lock(t_dadaobj *r_ob);
void dada_atomic_unlock(t_dadaobj *r_ob);


void dadaobj_setup(t_object *ob, t_dadaobj *r_ob, long flags, t_pt zoom_static_additional,
				   long playout_outlet, long changebang_outlet, long notification_outlet, dada_paint_ext_fn paint_ext, invalidate_and_redraw_fn invalidate_and_redraw, const char *tools);
void dadaobj_pxjbox_setup(t_dadaobj_pxjbox *b_ob, long flags, t_pt zoom_static_additional,
						  long playout_outlet, long changebang_outlet, long notification_outlet, dada_paint_ext_fn paint_ext, invalidate_and_redraw_fn invalidate_and_redraw,
						  const char *tools, long stores, const char *outlets, ...);
void dadaobj_jbox_setup(t_dadaobj_jbox *b_ob, long flags, t_pt zoom_static_additional,
						long playout_outlet, long changed_bang_outlet, long notification_outlet, dada_paint_ext_fn paint_ext, invalidate_and_redraw_fn invalidate_and_redraw,
						const char *tools, long stores, const char *outlets, ...);
void dadaobj_addfunctions(t_dadaobj *d_ob, dada_mousemove_fn mousemove_fn, method clock_task, method undo_postprocess, 
						  get_state_fn get_state, set_state_fn set_state, pixel_to_dadaitem_fn pixel_to_dadaitem, 
						  preselect_items_in_rectangle_fn preselect_items_in_rectangle, dadanotify_fn dadanotify);
void dadaobj_free(t_dadaobj *r_ob);
void dadaobj_jbox_free(t_dadaobj_jbox *b_ob);
void dadaobj_pxjbox_free(t_dadaobj_pxjbox *r_ob);
void dadaobj_send_changedbang(t_dadaobj *r_ob);
void dadaobj_send_notification_sym(t_dadaobj *r_ob, t_symbol *sym);
void dadaobj_send_notification_llll(t_dadaobj *r_ob, t_llll *ll);
void dadaobj_send_painted_notification(t_dadaobj *r_ob);

void dadaobj_invalidate_and_redraw(t_dadaobj *d_ob);
t_max_err dadaobj_setattr_zoom(t_dadaobj *d_ob, t_object *attr, long ac, t_atom *av);
t_max_err dadaobj_setattr_vzoom(t_dadaobj *d_ob, t_object *attr, long ac, t_atom *av);

void dadaobj_class_init(t_class *c, e_llllobj_obj_types type, long flags);


long dadaitem_identifier_eq(t_dadaitem_identifier id1, t_dadaitem_identifier id2);


/// PAINT STUFF
t_dada_force_graphics dadaobj_get_forced_graphics_from_view(t_dadaobj *r_ob, t_object *view);
void dadaobj_paint(t_dadaobj *r_ob, t_object *view); // High level wrapper for all the _paint_ext( functions

void dadaobj_paint_background(t_dadaobj *r_ob, t_jgraphics *g, t_rect *rect);
void dadaobj_paint_border(t_dadaobj *r_ob, t_jgraphics *g, t_rect *rect);
void dadaobj_paint_grid(t_dadaobj *r_ob, t_object *view, t_dada_force_graphics *force_graphics);


// ATTRIBUTES
t_max_err dadaobj_jbox_setattr_zoom(t_dadaobj_jbox *d_ob, t_object *attr, long ac, t_atom *av);
t_max_err dadaobj_jbox_setattr_vzoom(t_dadaobj_jbox *d_ob, t_object *attr, long ac, t_atom *av);
t_max_err dadaobj_jbox_setattr_maxundosteps(t_dadaobj_jbox *d_ob, t_object *attr, long ac, t_atom *av);
t_max_err dadaobj_pxjbox_setattr_zoom(t_dadaobj_pxjbox *d_ob, t_object *attr, long ac, t_atom *av);
t_max_err dadaobj_pxjbox_setattr_vzoom(t_dadaobj_pxjbox *d_ob, t_object *attr, long ac, t_atom *av);
t_max_err dadaobj_pxjbox_setattr_maxundosteps(t_dadaobj_pxjbox *d_ob, t_object *attr, long ac, t_atom *av);
void dadaobj_class_add_zoom_attr(t_class *c, double min_zoom, double max_zoom);
void dadaobj_class_add_center_attr(t_class *c);
void dadaobj_class_add_embed_attr(t_class *c);
void dadaobj_class_add_mousehover_attr(t_class *c);
void dadaobj_class_add_playstep_attr(t_class *c);
void dadaobj_class_add_grid_attrs(t_class *c);
void dadaobj_class_add_undo_attrs(t_class *c);


// READ/WRITE
void dadaobj_jbox_read(t_dadaobj_jbox *x, t_symbol *s, long argc, t_atom *argv);
void dadaobj_jbox_write(t_dadaobj_jbox *x, t_symbol *s, long argc, t_atom *argv);
void dadaobj_jbox_writetxt(t_dadaobj_jbox *x, t_symbol *s, long argc, t_atom *argv);
void dadaobj_jbox_readsinglesymbol(t_dadaobj_jbox *x, t_symbol *s, long argc, t_atom *argv);

// DRAG'n'DROP
t_atom_long dadaobj_jbox_acceptsdrag(t_dadaobj_jbox *x, t_object *drag, t_object *view);

// PATCHER STUFF
t_object *dadaobj_get_patcher(t_dadaobj *r_ob);
t_object *dadaobj_get_firstview(t_dadaobj *r_ob);


void dadaobj_jbox_exportimage(t_dadaobj_jbox *x, t_symbol *s, long argc, t_atom *argv);
void dadaobj_jbox_paintjit(t_dadaobj_jbox *x, t_symbol *matrix_name);


// MUTEXES
void dadaobj_mutex_lock(t_dadaobj *r_ob);
void dadaobj_mutex_unlock(t_dadaobj *r_ob);

long dadaobj_anything_handle_domain_or_range(t_dadaobj *r_ob, t_symbol *router, t_llll *args, long outletnum = -1); // -1 means: use notification outlet

long dadaobj_parse_export_png_syntax(t_dadaobj *r_ob, t_object *view, t_llll *ll, t_symbol **filename, long *dpi, double *width, double *height, t_pt *exportcenter);
#endif // _DADA_OBJECT_H_
