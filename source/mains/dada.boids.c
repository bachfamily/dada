/**
	@file
	dada.boids.c
	
	@name
	dada.boids
	
	@realname 
	dada.boids

	@type
	object
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
	Swarm intelligence modeling
	
	@description
	Controller for rule-based swarm-intelligence models
	
	@discussion
 
	@category
	dada, dada interfaces, dada rule-based systems

	@keywords
	boids, spat, spatialization, label, text, icon, orchestra, instrument, mixer, mix
	
	@seealso
	bach.wordcloud
	
	@owner
	Daniele Ghisi
*/



#include "dada.interface.h"
#include "dada.geometry.h"
#include "dada.paint.h"
#include "notation.h"
//#include "dada.cursors.data.c"
#include "dada.math.h"
#include "dada.graphs.h"
#include "dada.popupmenu.h"
#include "dada.undo.h"

#define DADA_BOIDS_MAX_SWARMS 64
#define DADA_BOIDS_MAX_PARTICLES_PER_SWARM 2048
#define DADA_BOIDS_MAX_RULES 32
#define DADA_BOIDS_MAX_PARAMS_PER_RULE 4
#define DADA_BOIDS_SWARM_SEL_THRESH 7

#define DADAITEM_TYPE_SWARM ((e_dadaitem_types)150)
#define DADAITEM_TYPE_RULEPARAM ((e_dadaitem_types)151)

#define DADA_BOIDS_ROTATION_INTERFACE_FACTOR (2 * TWO_PI)
#define DADA_BOIDS_ROTATION_SCALE_FACTOR 100.

typedef t_uint64 t_boids_swarm_bitfield;

////////////////////////// structures

typedef enum _boids_rule_param_types
{
    DADA_BOIDS_RULE_PARAM_NONE = 0,	///< No param
    DADA_BOIDS_RULE_PARAM_LONG,
    DADA_BOIDS_RULE_PARAM_DOUBLE,
    DADA_BOIDS_RULE_PARAM_PT
} e_boids_rule_param_types;


typedef enum _boids_rule_param_display
{
    DADA_BOIDS_RULE_PARAM_DISPLAY_NONE = 0,
    DADA_BOIDS_RULE_PARAM_DISPLAY_PT,
    DADA_BOIDS_RULE_PARAM_DISPLAY_VECTOR,
    DADA_BOIDS_RULE_PARAM_DISPLAY_VLINE,
    DADA_BOIDS_RULE_PARAM_DISPLAY_HLINE
} e_boids_rule_param_display;

typedef union ruleparamword
{
    long        w_long;
    double      w_double;
    t_pt        w_pt;
} t_ruleparamword;


typedef struct _boids_coord
{
    t_pt pt;
    double intensity;
} t_boids_coord;

typedef struct _boids_rule_param
{
    t_ruleparamword          r_param;
    int                      r_type; ///< one of the #e_boids_rule_param_types
    int                      r_display; ///< one of the #e_boids_rule_param_display
    t_symbol                 *r_name;
} t_boids_rule_param;


typedef t_boids_coord (*boids_rule_fn)(long num_boids, t_boids_coord *coord, t_boids_coord *speed, long boid_idx, long num_params, t_boids_rule_param *params);    // single rule, returns a velocity vector to be summed to the current velocity


typedef struct _boids_rule_ref
{
    t_symbol            *name;
    double              gain;
    long                num_params;
    t_boids_rule_param  param[DADA_BOIDS_MAX_PARAMS_PER_RULE];
    char                dummy_ref;     ///< If the rule named <name> has not been found, this will be 1, hence this will be a "dummy" rule reference, and hollow skeleton
} t_boids_rule_ref;


typedef struct _boids_swarm
{
    t_dadaitem  r_it;
    
	long	num_boids;
    t_boids_coord	coord[DADA_BOIDS_MAX_PARTICLES_PER_SWARM];
    t_boids_coord	speed[DADA_BOIDS_MAX_PARTICLES_PER_SWARM];
    
    t_symbol    *name;
    t_jrgba     color;

    double      max_speed;
    double      max_intensity;

    long             num_rule_refs;
    t_boids_rule_ref rule_ref[DADA_BOIDS_MAX_RULES];
    
} t_boids_swarm;


typedef struct _boids_rule_prototype
{
    t_symbol        *name;

    t_symbol        *fun_code;
    boids_rule_fn   fun;
    
    double          default_gain;
    long                num_params;
    t_boids_rule_param  param[DADA_BOIDS_MAX_PARAMS_PER_RULE]; ///< parameter types and default
    
    t_llllelem      *clang_elem;
    
    char            output_position_is_absolute; ///< Output data is not a speed, but a position
    char            output_intensity_is_absolute; ///< Output data is not a speed, but an absolute intensity
} t_boids_rule_prototype;



typedef struct _boids 
{
	t_dadaobj_jbox		b_ob; // root object
	
	// swarm
	t_boids_swarm	*swarm;
    
    // rules
    long                    num_rule_prototypes;
    t_boids_rule_prototype  rule_prototypes[DADA_BOIDS_MAX_RULES];
    t_llll                *clang_ll; // compilers, as H_OBJ
    long                    num_standard_rules; // set at startup, never changed
    
    // follower
    t_boids_swarm_bitfield    follow_swarm;

	
    char            use_intensity;
    char            show_speed;
    char            show_names;
    char            show_ruleparams;
    char            show_ruleparam_names;
    char            show_intensity;
    char            output_sequencing;
    
    // display
    char            use_separate_ruleparams_color;
    t_jrgba         ruleparams_color;
    	
	// utilities
	char			firsttime;
	char			itsme;
	char			creating_new_obj;
	
	long			n_in;   // space for the inlet number used by all the proxies
    void			*n_proxy1;
	
	// outlets are declared in the dadaobj->llllobj structure, at the beginning
} t_boids;



///////////////////////// function prototypes
//// standard set
void *boids_new(t_symbol *s, long argc, t_atom *argv);
void boids_free(t_boids *x);
void boids_assist(t_boids *x, void *b, long m, long a, char *s);

void boids_paint(t_boids *x, t_object *view);


void boids_int(t_boids *x, t_atom_long num);
void boids_float(t_boids *x, double num);
void boids_anything(t_boids *x, t_symbol *msg, long ac, t_atom *av);
void boids_bang(t_boids *x);


// get/set status
void boids_set_state(t_boids *x, t_llll *state);
t_llll *boids_get_state_sel(t_boids *x, char get_boids, char get_testers);
t_llll *boids_get_state(t_boids *x);

t_llll *boids_get_cards(t_boids *x);
void boids_set_cards(t_boids *x, t_llll *shapes);


// interface
void boids_focusgained(t_boids *x, t_object *patcherview);
void boids_focuslost(t_boids *x, t_object *patcherview);
void boids_mousedown(t_boids *x, t_object *patcherview, t_pt pt, long modifiers);
void boids_mousemove(t_boids *x, t_object *patcherview, t_pt pt, long modifiers);
void boids_mouseup(t_boids *x, t_object *patcherview, t_pt pt, long modifiers);
void boids_mousedrag(t_boids *x, t_object *patcherview, t_pt pt, long modifiers);
long boids_key(t_boids *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
long boids_keyup(t_boids *x, t_object *patcherview, long keycode, long modifiers, long textcharacter);
void boids_mousewheel(t_boids *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc);

void boids_mouseenter(t_boids *x, t_object *patcherview, t_pt pt, long modifiers);
void boids_mouseleave(t_boids *x, t_object *patcherview, t_pt pt, long modifiers);

t_max_err boids_notify(t_boids *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
void boids_jsave(t_boids *x, t_dictionary *d);
void boids_preset(t_boids *x);
void boids_begin_preset(t_boids *x, t_symbol *s, long argc, t_atom *argv);
void boids_restore_preset(t_boids *x, t_symbol *s, long argc, t_atom *argv);
void boids_end_preset(t_boids *x);

// UNDO
void boids_undo_step_push_swarms(t_boids *x, t_symbol *operation);
void boids_undo_step_push(t_boids *x, t_symbol *operation);
void boids_undo_step_push_rules(t_boids *x, t_symbol *operation);
void boids_postprocess_undo(t_boids *x);


// sequencing
void boids_stop(t_boids *x, t_symbol *s, long argc, t_atom *argv);
void boids_play(t_boids *x, t_symbol *s, long argc, t_atom *argv);
void boids_task(t_boids *x);
void boids_clock(t_boids *x, t_symbol *s);

void boids_add_single_rule(t_boids *x, t_llll *rule, t_symbol *def_name, t_symbol *def_code);

void boids_add_rule_prototype(t_boids *x, t_symbol *name, boids_rule_fn fun, double default_gain, char output_position_is_absolute, char output_intensity_is_absolute, long num_params, t_boids_rule_param *param);
void boids_ezadd_rule_prototype(t_boids *x, t_symbol *name, boids_rule_fn fun, double default_gain, char output_position_is_absolute, char output_intensity_is_absolute, long num_params, ...);

t_max_err boids_setattr_bgimage(t_boids *x, t_object *attr, long ac, t_atom *av);


void swarm_rotate(t_boids *x, t_boids_swarm *sw, double angle, t_pt *rot_center);
void swarm_move_delta(t_boids *x, t_boids_swarm *sw, t_pt delta);
void swarm_scale(t_boids *x, t_boids_swarm *sw, double factor_x, double factor_y, t_pt *scaling_center);



////////////////////// INTERFACE FOR DADA ITEMS


void boids_postprocess(t_boids *x)
{
	jbox_redraw((t_jbox *)x);
}


void postprocess_boids(t_dadaobj *d_ob)
{
	jbox_redraw((t_jbox *)d_ob->orig_obj);
}






long boids_get_num_swarms(t_boids *x)
{
    return dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_SWARM);
}



void boids_autozoom(t_boids *x, t_object *view, t_rect *rect)
{
    systhread_mutex_lock(x->b_ob.d_ob.l_mutex);
    long num_swarms = boids_get_num_swarms(x);
    double rect_width = rect->width;
    double rect_height = rect->height;

    t_pt min = build_pt(0, 0);
    t_pt max = min;
    if (num_swarms >= 1) {
        long i;
        min = x->swarm[0].coord[0].pt;
        max = min;
        for (long s = 0; s < num_swarms; s++) {
            t_boids_swarm *sw = &x->swarm[s];
            for (i = 0; i < sw->num_boids; i++) {
                t_pt this_coord = sw->coord[i].pt;
                if (this_coord.x < min.x) min.x = this_coord.x;
                if (this_coord.y < min.y) min.y = this_coord.y;
                if (this_coord.x > max.x) max.x = this_coord.x;
                if (this_coord.y > max.y) max.y = this_coord.y;
            }
        }
    }

    systhread_mutex_unlock(x->b_ob.d_ob.l_mutex);
        
    
    if (max.x == min.x) {
        max.x -= 0.5;
        min.x += 0.5;
    }
    if (max.y == min.y) {
        max.y -= 0.5;
        min.y += 0.5;
    }
    
    // adding pads
    max.x += (max.x - min.x) * 0.2;
    min.x -= (max.x - min.x) * 0.2;
    max.y += (max.y - min.y) * 0.2;
    min.y -= (max.y - min.y) * 0.2;
    
    // equalizing zooms
    double zoom_x = (max.x - min.x)/rect_width;
    double zoom_y = (max.y - min.y)/rect_height;
    
    if (zoom_y < zoom_x) {
        double diff = (zoom_x - zoom_y) * rect_height;
        max.y += diff/2.;
        min.y -= diff/2.;
    } else if (zoom_x < zoom_y) {
        double diff = (zoom_y - zoom_x) * rect_width;
        max.x += diff/2.;
        min.x -= diff/2.;
    }
    
    dadaobj_setdomain(dadaobj_cast(x), view, min.x, max.x);
    dadaobj_setrange(dadaobj_cast(x), view, min.y, max.y);
}


///// RULES INTERFACE

void boids_add_rule_prototype(t_boids *x, t_symbol *name, t_symbol *fun_code, boids_rule_fn fun, double default_gain, char output_position_is_absolute, char output_intensity_is_absolute, long num_params, t_boids_rule_param *param, t_llllelem *clang_elem)
{
    if (x->num_rule_prototypes < DADA_BOIDS_MAX_RULES) {
        x->rule_prototypes[x->num_rule_prototypes].name = name;
        x->rule_prototypes[x->num_rule_prototypes].fun_code = fun_code;
        x->rule_prototypes[x->num_rule_prototypes].fun = fun;
        x->rule_prototypes[x->num_rule_prototypes].default_gain = default_gain;
        x->rule_prototypes[x->num_rule_prototypes].num_params = num_params;
        for (long i = 0; i < num_params; i++)
            x->rule_prototypes[x->num_rule_prototypes].param[i] = param[i];
        x->rule_prototypes[x->num_rule_prototypes].clang_elem = clang_elem;
        x->rule_prototypes[x->num_rule_prototypes].output_position_is_absolute = output_position_is_absolute;
        x->rule_prototypes[x->num_rule_prototypes].output_intensity_is_absolute = output_intensity_is_absolute;
        x->num_rule_prototypes++;
    }
}

void boids_substitute_rule_prototype(t_boids *x, long index, t_symbol *name, t_symbol *fun_code, boids_rule_fn fun, double default_gain, char output_position_is_absolute, char output_intensity_is_absolute, long num_params, t_boids_rule_param *param, t_llllelem *clang_elem)
{
    if (x->rule_prototypes[index].clang_elem) {
        object_free_debug(hatom_getobj(&x->rule_prototypes[index].clang_elem->l_hatom));
        llll_destroyelem(x->rule_prototypes[index].clang_elem);
    }
    
    if (index < DADA_BOIDS_MAX_RULES) {
        x->rule_prototypes[index].name = name;
        x->rule_prototypes[index].fun = fun;
        x->rule_prototypes[index].fun_code = fun_code;
        x->rule_prototypes[index].default_gain = default_gain;
        x->rule_prototypes[index].num_params = num_params;
        for (long i = 0; i < num_params; i++)
            x->rule_prototypes[index].param[i] = param[i];
        x->rule_prototypes[index].output_position_is_absolute = output_position_is_absolute;
        x->rule_prototypes[index].output_intensity_is_absolute = output_intensity_is_absolute;
        // we only change hatom content, not the element itself
        x->rule_prototypes[index].clang_elem = clang_elem;
    }
}


void boids_ezadd_rule_prototype(t_boids *x, t_symbol *name, boids_rule_fn fun, double default_gain, char output_position_is_absolute, char output_intensity_is_absolute, long num_params, ...)
{
    if (num_params <= 0) {
        boids_add_rule_prototype(x, name, NULL, fun, default_gain, output_position_is_absolute, output_intensity_is_absolute, 0, NULL, NULL);
        return;
    }
    
    va_list argptr;
    t_boids_rule_param *param = (t_boids_rule_param *)bach_newptr(num_params * sizeof(t_boids_rule_param));
    long i;
    va_start(argptr, num_params);
    
    for (i = 0; i < num_params; i++) {
        param[i].r_name = (t_symbol *)va_arg(argptr, t_symbol *);
        param[i].r_type = (long)va_arg(argptr, long);
        param[i].r_display = (long)va_arg(argptr, long);
        switch (param[i].r_type) {
            case DADA_BOIDS_RULE_PARAM_LONG:
                param[i].r_param.w_long = va_arg(argptr, long);
                break;
            case DADA_BOIDS_RULE_PARAM_DOUBLE:
                param[i].r_param.w_double = va_arg(argptr, double);
                break;
            case DADA_BOIDS_RULE_PARAM_PT:
                param[i].r_param.w_pt = va_arg(argptr, t_pt);
                break;
            default:
                param[i].r_param.w_long = va_arg(argptr, long);
                break;
        }
    }
    va_end(argptr);
    
    boids_add_rule_prototype(x, name, NULL, fun, default_gain, output_position_is_absolute, output_intensity_is_absolute, num_params, param, NULL);
    bach_freeptr(param);
}

t_boids_coord get_null_boids_coord()
{
    t_boids_coord s;
    s.pt = build_pt(0, 0);
    s.intensity = 0;
    return s;
}

t_boids_coord boids_center_fn(long num_boids, t_boids_coord *coord, t_boids_coord *vels, long boid_idx, long num_params, t_boids_rule_param *params)
{
    t_boids_coord res = get_null_boids_coord();
    if (num_boids > 1) {
        for (long i = 0; i < num_boids; i++) {
            if (i == boid_idx) continue;
            res.pt = pt_pt_sum(res.pt, coord[i].pt);
        }
        res.pt = pt_pt_diff(pt_number_prod(res.pt, 1./(num_boids - 1)), coord[boid_idx].pt);
    }
    return res;
}

t_boids_coord boids_avoid_fn(long num_boids, t_boids_coord *coord, t_boids_coord *vels, long boid_idx, long num_params, t_boids_rule_param *params)
{
    t_boids_coord res = get_null_boids_coord();
    double amount_start_repulsion = (num_params >= 1 ? params[0].r_param.w_double : 0);
    double amount_max_repulsion = (num_params >= 2 ? params[1].r_param.w_double : 0);
    if (num_boids > 1) {
        for (long i = 0; i < num_boids; i++) {
            if (i == boid_idx) continue;
            double d = pt_pt_distance(coord[i].pt, coord[boid_idx].pt);
            if (d < amount_start_repulsion) {
                t_pt diff = pt_pt_diff(coord[i].pt, coord[boid_idx].pt);
                double factor = CLAMP(rescale(d, amount_start_repulsion, amount_max_repulsion, 0., 1.), 0., 1.);
                if (fabs(diff.x) <= 0.01 && fabs(diff.y) < 0.01) // essentially the two points coincide
                    diff = build_pt(random_double_in_range(-1., 1.), random_double_in_range(-1., 1.));
                res.pt = pt_pt_diff(res.pt, pt_number_prod(diff, factor));
            }
        }
    }
    return res;
}


t_boids_coord boids_align_fn(long num_boids, t_boids_coord *coord, t_boids_coord *vels, long boid_idx, long num_params, t_boids_rule_param *params)
{
    t_boids_coord res = get_null_boids_coord();
    if (num_boids > 1) {
        for (long i = 0; i < num_boids; i++) {
            if (i == boid_idx) continue;
            res.pt = pt_pt_sum(res.pt, vels[i].pt);
        }
        res.pt = pt_number_prod(res.pt, 1./(num_boids - 1));
    }
    return res;
}

t_boids_coord boids_wind_fn(long num_boids, t_boids_coord *coord, t_boids_coord *vels, long boid_idx, long num_params, t_boids_rule_param *params)
{
    t_boids_coord res = get_null_boids_coord();
    if (num_params >= 1)
        res.pt = params[0].r_param.w_pt;
    return res;
}

t_boids_coord boids_leftbarrier_fn(long num_boids, t_boids_coord *coord, t_boids_coord *vels, long boid_idx, long num_params, t_boids_rule_param *params)
{
    t_boids_coord res = get_null_boids_coord();
    if (num_params >= 1 && coord[boid_idx].pt.x < params[0].r_param.w_double)
        res.pt.x = params[1].r_param.w_double;
    return res;
}

t_boids_coord boids_rightbarrier_fn(long num_boids, t_boids_coord *coord, t_boids_coord *vels, long boid_idx, long num_params, t_boids_rule_param *params)
{
    t_boids_coord res = get_null_boids_coord();
    if (num_params >= 1 && coord[boid_idx].pt.x > params[0].r_param.w_double)
        res.pt.x = -params[1].r_param.w_double;
    return res;
}


t_boids_coord boids_topbarrier_fn(long num_boids, t_boids_coord *coord, t_boids_coord *vels, long boid_idx, long num_params, t_boids_rule_param *params)
{
    t_boids_coord res = get_null_boids_coord();
    if (num_params >= 1 && coord[boid_idx].pt.y > params[0].r_param.w_double)
        res.pt.y = -params[1].r_param.w_double;
    return res;
}

t_boids_coord boids_bottombarrier_fn(long num_boids, t_boids_coord *coord, t_boids_coord *vels, long boid_idx, long num_params, t_boids_rule_param *params)
{
    t_boids_coord res = get_null_boids_coord();
    if (num_params >= 1 && coord[boid_idx].pt.y < params[0].r_param.w_double)
        res.pt.y = params[1].r_param.w_double;
    return res;
}


void boids_add_standard_rules(t_boids *x)
{
    boids_ezadd_rule_prototype(x, gensym("center"), boids_center_fn, 0.01, false, false, 0);
    boids_ezadd_rule_prototype(x, gensym("avoid"), boids_avoid_fn, 1., false, false, 2, gensym("thresh"), (long)DADA_BOIDS_RULE_PARAM_DOUBLE, (long)DADA_BOIDS_RULE_PARAM_DISPLAY_NONE, 15., gensym("maxthresh"), (long)DADA_BOIDS_RULE_PARAM_DOUBLE, DADA_BOIDS_RULE_PARAM_DISPLAY_NONE, 0.);
    boids_ezadd_rule_prototype(x, gensym("align"), boids_align_fn, 0.125, false, false, 0);
    boids_ezadd_rule_prototype(x, gensym("wind"), boids_wind_fn, 1., false, false, 1, gensym("speed"), (long)DADA_BOIDS_RULE_PARAM_PT, DADA_BOIDS_RULE_PARAM_DISPLAY_VECTOR, build_pt(4, 0));
    boids_ezadd_rule_prototype(x, gensym("leftbarrier"), boids_leftbarrier_fn, 1., false, false, 2, gensym("position"), (long)DADA_BOIDS_RULE_PARAM_DOUBLE, (long)DADA_BOIDS_RULE_PARAM_DISPLAY_VLINE, -100., gensym("repulsion"), (long)DADA_BOIDS_RULE_PARAM_DOUBLE, (long)DADA_BOIDS_RULE_PARAM_DISPLAY_NONE, 10.);
    boids_ezadd_rule_prototype(x, gensym("rightbarrier"), boids_rightbarrier_fn, 1., false, false, 2, gensym("position"), (long)DADA_BOIDS_RULE_PARAM_DOUBLE, (long)DADA_BOIDS_RULE_PARAM_DISPLAY_VLINE, 100., gensym("repulsion"), (long)DADA_BOIDS_RULE_PARAM_DOUBLE, (long)DADA_BOIDS_RULE_PARAM_DISPLAY_NONE, 10.);
    boids_ezadd_rule_prototype(x, gensym("topbarrier"), boids_topbarrier_fn, 1., false, false, 2, gensym("position"), (long)DADA_BOIDS_RULE_PARAM_DOUBLE, (long)DADA_BOIDS_RULE_PARAM_DISPLAY_HLINE, -100., gensym("repulsion"), (long)DADA_BOIDS_RULE_PARAM_DOUBLE, (long)DADA_BOIDS_RULE_PARAM_DISPLAY_NONE, 10.);
    boids_ezadd_rule_prototype(x, gensym("bottombarrier"), boids_bottombarrier_fn, 1., false, false, 2, gensym("position"), (long)DADA_BOIDS_RULE_PARAM_DOUBLE, (long)DADA_BOIDS_RULE_PARAM_DISPLAY_HLINE, 100., gensym("repulsion"), (long)DADA_BOIDS_RULE_PARAM_DOUBLE, (long)DADA_BOIDS_RULE_PARAM_DISPLAY_NONE, 10.);
    x->num_standard_rules = x->num_rule_prototypes;
}




///////// RULE "ON THE FLY" COMPILING

boids_rule_fn get_rule_prototype_from_code(t_boids *x, t_symbol *fun_name, t_symbol *code, t_llllelem **clang_elem)
{
    
    t_atom ret, fun, str;
    t_object *string;
    
    if (!code) {
        object_error((t_object *)x, "No custom rule defined!");
        return NULL;
    }
    
    // Set rule, by appending
    long size = strlen(code->s_name) + 10000;
    char *buf = (char *)bach_newptr(size * sizeof(char)); // buf + 100
    char *fun_name_pad_buf = (char *)bach_newptr((strlen(fun_name->s_name) + 20) * sizeof(char));
    sprintf(fun_name_pad_buf, "boids_%s_fn", fun_name->s_name);
    t_symbol *fun_name_pad = gensym(fun_name_pad_buf);
    
    snprintf_zero(buf, size, "%s \n"
                  "typedef struct _pt \n"
                  "{ \n"
                  "    double x; \n"
                  "    double y; \n"
                  "} t_pt; \n"
                  "typedef union ruleparamword \n"
                  "{ \n"
                  "    long        w_long; \n"
                  "    double      w_double; \n"
                  "    t_pt        w_pt; \n"
                  "} t_ruleparamword; \n"
                  " \n"
                  "typedef struct _boids_coord \n"
                  "{\n"
                  "    t_pt pt;\n"
                  "    double intensity;\n"
                  "} t_boids_coord;\n"
                  " \n"
                  "typedef struct _boids_rule_param \n"
                  "{ \n"
                  "    t_ruleparamword          r_param; \n"
                  "    int                      r_type; \n"
                  "    void                     *r_name; \n" // TO DO: can't substitute with t_symbol *...
                  "} t_boids_rule_param; \n"
                  " \n"
                  "t_boids_coord %s(long num_boids, t_boids_coord *coord, t_boids_coord *vels, long boid_idx, long num_params, t_boids_rule_param *params); \n"
                  "t_boids_coord %s(long num_boids, t_boids_coord *coord, t_boids_coord *vels, long boid_idx, long num_params, t_boids_rule_param *params) { \n"
/*                  "t_boids_coord res = get_null_boids_coord();"
                  "if (num_params >= 1 && coord[boid_idx].pt.y > params[0].r_param.w_double)"
                  "res.pt.y = -params[1].r_param.w_double;"
                  "return res;" */
                  "%s \n"
//                  " t_boids_coord b; b.pt.x = 0; b.pt.y=0; b.intensity=0; return b; \n"
                  "}", dada_get_default_include(), fun_name_pad->s_name, fun_name_pad->s_name, code->s_name);
    
    // recreate clang object
    t_object *clang = (t_object *)object_new(CLASS_NOBOX, gensym("clang"), gensym("mycoolmodule"));
    
    //dg: enabling cpp doesn't work; nothing compiles any longer
    //    object_attr_setlong(x->clang, gensym("cpp"), 1); //-- enabling C++ causes a hang when using addsymbol, need to investigate...
    
    // make a new string object (alternative to symbol that avoids post)
    string = (t_object *)object_new(CLASS_NOBOX, gensym("string"), buf);
    atom_setobj(&str, string);
    
    t_symbol *ps_addsymbol = gensym("addsymbol");
    object_method(clang, ps_addsymbol, gensym("acosh"), &acosh);
    object_method(clang, ps_addsymbol, gensym("asinh"), &asinh);
    object_method(clang, ps_addsymbol, gensym("atanh"), &atanh);
    object_method(clang, ps_addsymbol, gensym("modf"), &modf);
    object_method(clang, ps_addsymbol, gensym("hypot"), &hypot);
    object_method(clang, ps_addsymbol, gensym("trunc"), &trunc);
    object_method(clang, ps_addsymbol, gensym("round"), &round);
    
    // compile the string
    object_method_typed(clang, gensym("compile"), 1, &str, &ret);
    
    // obtain the function (executable code)
    object_method_sym(clang, gensym("getfunction"), fun_name_pad, &fun);
    
    // get the function pointer
    boids_rule_fn rule_fn = (boids_rule_fn)atom_getobj(&fun);
    
    // must check that there is code, otherwise there was a compile error
    if (!rule_fn)
        object_error((t_object *)x, "Syntax error in custom rule!");
    else {
        /*		// test rule
         t_cell cell = 0;
         int neighbors_size = 5;
         t_cell **neighbors = NULL;
         int sum_neighbors = 1;
         int nonzero_neighbors = 1;
         t_cell res = (x->custom_rule)(cell, neighbors_size, neighbors, sum_neighbors, nonzero_neighbors);
         post("%d", (int) res); */
    }
    
    bach_freeptr(buf);
    bach_freeptr(fun_name_pad_buf);
    
    // Destroy the string (but not the clang: we need the compiled function!)
    object_free(string);
    
    *clang_elem = llll_appendobj(x->clang_ll, clang);
    return rule_fn;
}

void boids_add_rule_prototype_from_code(t_boids *x, t_symbol *name, t_symbol *fun_code, double default_gain, char output_position_is_absolute, char output_intensity_is_absolute, long num_params, t_boids_rule_param *param)
{
    t_llllelem *clang_elem = NULL;
    boids_rule_fn fun = get_rule_prototype_from_code(x, name, fun_code, &clang_elem);
    if (fun)
        boids_add_rule_prototype(x, name, fun_code, fun, default_gain, output_position_is_absolute, output_intensity_is_absolute, num_params, param, clang_elem);
}

void boids_substitute_rule_prototype_from_code(t_boids *x, long index, t_symbol *name, t_symbol *fun_code, double default_gain, char output_position_is_absolute, char output_intensity_is_absolute, long num_params, t_boids_rule_param *param)
{
    t_llllelem *clang_elem = NULL;
    boids_rule_fn fun = get_rule_prototype_from_code(x, name, fun_code, &clang_elem);
    if (fun)
        boids_substitute_rule_prototype(x, index, name, fun_code, fun, default_gain, output_position_is_absolute, output_intensity_is_absolute, num_params, param, clang_elem);
}





long boids_ruleprototype_name_to_idx(t_boids *x, t_symbol *name)
{
    for (long i = 0; i < x->num_rule_prototypes; i++)
        if (x->rule_prototypes[i].name == name)
            return i;
    return -1;
}

long boids_rulereference_name_to_idx(t_boids *x, t_boids_swarm *sw, t_symbol *name)
{
    for (long i = 0; i < sw->num_rule_refs; i++)
        if (sw->rule_ref[i].name == name)
            return i;
    return -1;
}


void boids_delete_rule_prototype(t_boids *x, t_symbol *name)
{
    long idx = boids_ruleprototype_name_to_idx(x, name);
    if (idx >= 0) {
        
        if (x->rule_prototypes[idx].clang_elem) {
            object_free_debug((t_object *)hatom_getobj(&x->rule_prototypes[idx].clang_elem->l_hatom));
            llll_destroyelem(x->rule_prototypes[idx].clang_elem);
        }
        
        if (idx < DADA_BOIDS_MAX_RULES - 1) {
            // shift array
            sysmem_copyptr(x->rule_prototypes + idx + 1, x->rule_prototypes + idx, (DADA_BOIDS_MAX_RULES - 1 - idx) * sizeof(t_boids_rule_prototype));
        }
        x->num_rule_prototypes--;
    } else
        object_error((t_object *)x, "There is no rule named %s!", name->s_name);
}


//////////////////////// global class pointer variable
t_class *boids_class;

int C74_EXPORT main(void)
{	
	t_class *c;
	
	common_symbols_init();
	llllobj_common_symbols_init();
	
	if (llllobj_check_version(BACH_LLLL_VERSION) || llllobj_test()) {
		error("bach: bad installation");
		return 1;
	}
	
	
	CLASS_NEW_CHECK_SIZE(c, "dada.boids", (method)boids_new, (method)boids_free, (long)sizeof(t_boids), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
	c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
	jbox_initclass(c, JBOX_FONTATTR);	// include fonts
	//	jbox_initclass(c, 0);
	
	// paint & utilities
	class_addmethod(c, (method) boids_paint,			"paint", A_CANT, 0);
	class_addmethod(c, (method) boids_assist,			"assist",		A_CANT, 0);  
	class_addmethod(c, (method)	boids_notify,			"bachnotify",		A_CANT,		0);
	
	// save & preset
    class_addmethod(c, (method) boids_preset, "preset", 0);
    class_addmethod(c, (method) boids_begin_preset, "begin_preset", A_GIMME, 0);
    class_addmethod(c, (method) boids_restore_preset, "restore_preset", A_GIMME, 0);
    class_addmethod(c, (method) boids_end_preset, "end_preset", 0);
	CLASS_METHOD_ATTR_PARSE(c, "begin_preset", "undocumented", gensym("long"), 0L, "1");
	CLASS_METHOD_ATTR_PARSE(c, "restore_preset", "undocumented", gensym("long"), 0L, "1");
	CLASS_METHOD_ATTR_PARSE(c, "end_preset", "undocumented", gensym("long"), 0L, "1");
	class_addmethod(c, (method) boids_jsave, "jsave", A_CANT, 0);
	
	// interface
	class_addmethod(c, (method) boids_focusgained, "focusgained", A_CANT, 0);
	class_addmethod(c, (method) boids_focuslost, "focuslost", A_CANT, 0);
    
    // @method (mouse) @digest Edit content
    // @description
    // @copy DADA_DOC_MOUSE_COMMANDS_STANDARD_NAVIGATION
	class_addmethod(c, (method) boids_mousedown, "mousedown", A_CANT, 0);
	class_addmethod(c, (method) boids_mousedrag, "mousedrag", A_CANT, 0);
	class_addmethod(c, (method) boids_mouseup, "mouseup", A_CANT, 0);

    // @method (keyboard) @digest Undo/redo or play
    // @description
    // @copy DADA_DOC_KEYBOARDS_COMMANDS_STANDARD_NAVIGATION
    // • <m>Cmd+Z</m> (mac) or <m>Ctrl+Z</m> (win): perform undo step<br />
    // • <m>Cmd+Shift+Z</m> (mac) or <m>Ctrl+Y</m> (win): perform redo step<br />
    // • <m>Spacebar</m>: toggle play<br />
    class_addmethod(c, (method) boids_key, "key", A_CANT, 0);
  	class_addmethod(c, (method) boids_keyup, "keyup", A_CANT, 0);
    
    // @method (tools) @digest Navigate or edit content
    // @description
    // @copy DADA_DOC_TOOLS_INTRO
    // @copy DADA_DOC_TOOLS_ZX
    // @copy DADA_DOC_TOOLS_Q
	class_addmethod(c, (method) boids_mousemove, "mousemove", A_CANT, 0);
	class_addmethod(c, (method) boids_mouseenter, "mouseenter", A_CANT, 0);
	class_addmethod(c, (method) boids_mouseleave, "mouseleave", A_CANT, 0);
	class_addmethod(c, (method) boids_mousewheel, "mousewheel", A_CANT, 0);
	class_addmethod(c, (method) boids_anything,	"move",		A_GIMME,	0);

    // @method int @digest Play/Stop
    // @description A non-zero integer triggers a <m>play</m> message, a zero integer triggers a <m>stop</m> message
    class_addmethod(c, (method) boids_int, "int", A_LONG, 0);

    // @method dump @digest Output state
    // @description Outputs the current state of the object. The syntax is
    // <b>boids (rules <m>CUSTOMRULE1</m> <m>CUSTOMRULE2</m>...) (swarms <m>SWARM1</m> <m>2</m>...) </b>.
    // Each <m>CUSTOMRULE</m> element represents a custom rule and is in the form
    // <b>((name <m>rule_name</m>) (code <m>function_code</m>) (defaultgain <m>gain</m>) (abscoord <m>ac</m>) (absintensity <m>ai</m>) (params <m>PARAM1</m> <m>PARAM2</m> <m>PARAM3</m>...)</b>,
    // where the <m>function_code</m> must be a single symbol, and <m>ai</m> and <m>ac</m> are 1/0 values telling respectively if the function will return absolute
    // coordinates or absolute intensity instead of a coordinate difference, and intensity difference (speed). These two last values both default to 0:
    // functions return by default a vector which will be added to the current speed to modify it. <br />
    // Each parameter is in the form
    // <b>(<m>name</m> <m>type</m> <m>value</m>)</b>, where <m>type</m> is a symbol among: "int", "float", "pt", and value is the corresponding value (or couple of
    // x and y values, without parentheses, in the case of "pt" type). <br />
    // Each <m>SWARM</m> element represents a swarm is in the form
    // <b>((name <m>name</m>) (size <m>num_boids</m>) (coord <m>COORD_BOID1</m> <m>COORD_BOID2</m>...) (speed <m>SPEED_BOID1</m> <m>SPEED_BOID2</m>...)
    // (intensity <m>intensity_boid1</m> <m>intensity_boid2</m>...) (intensityspeed <m>intensityspeed_boid1</m> <m>intensityspeed_boid2</m>...)
    // (maxspeed <m>maximum_swarm_speed</m>) (maxintensity <m>maximum_swarm_intensity</m>) (color <m>red</m> <m>green</m> <m>blue</m> <m>alpha</m>)
    // (applyrule <m>RULE1</m> <m>RULE2</m> <m>RULE3</m>...))</b>,
    // where each <m>COORD_BOID</m> and <m>SPEED_BOID</m> is in the form <b>(<m>x</m> <m>y</m>)</b>, where each <m>intensityspeed_boid</m> is
    // the difference between successive intensities (derivative), and where each <m>RULE</m> represents a rule to be applied to the swarm, and is in the form
    // <b>(<m>rule_name</m> (gain <m>gain_value</m>) (<m>param_name</m> <m>param_value</m>) (<m>param_name</m> <m>param_value</m>) ...)</b>, <br />
    // where, in turn, each <m>param_name</m> is one of the parameters defined for the given rule "int", "float" or "pt", i.e. float couple (see the "rules" llll, above).
    // <br />
    // A first argument limits the elements to be dumped: the <m>dump rules</m> message only dumps the rules; the <m>dump swarms</m> message only dumps the swarms. <br />
    // @copy DADA_DOC_SYNTAX_FLAGS
    // @marg 0 @name what @optional 1 @type symbol
    class_addmethod(c, (method)boids_anything,	"dump",			A_GIMME,	0);
    
    
    // @method autozoom @digest Set domain and range automatically
    // @description Adapts view and zoom automatically according to the current stars' and planets' positions.
    class_addmethod(c, (method) boids_anything, "autozoom", A_GIMME, 0);

    
    // @method rotate @digest Rotate swarms
    // @description The word <m>rotate</m> followed the index of a swarm, and an angle (in radians), rotates
    // the swarm. The angle can be set in degrees by appending the degrees ° symbol after the number (without any spaces) or by
    // replacing the number with an llll in the form <b>(<m>amount_in_degrees</m> deg)</b>.
    // If the index of the shape is <m>0</m> or the <m>all</m> symbol, all shapes will be rotated.
    // If a third argument is added, in the form <b>(<m>x</m> <m>y</m>)</b>, it sets the coordinates of the origin for the rotation.
    // If no third argument is added, the default center of rotation is the shape barycenter (if a single swarm is being rotated)
    // or the origin <b>(0 0)</b> if all swarms are being rotated.
    // The center of rotation llll can be replaced by the <m>barycenter</m> symbol, to specify that rotation must happen around individuals barycenters.
    // Alternatively you can add the "barycenter" symbol as third element in order to specify that coordinates are barycentric coordinates.
    // @marg 0 @name swarm_index @optional 0 @type int/all
    // @marg 1 @name angle @optional 0 @type number/llll
    // @marg 2 @name origin @optional 1 @type llll/barycenter
    class_addmethod(c, (method)boids_anything,	"rotate",		A_GIMME,	0);
    
    // @method move @digest Translate swarms
    // @description The word <m>move</m> followed the index of a swarm and a vector in wrapped <b>(<m>x</m> <m>y</m>)</b> syntax,
    // translates the swarm by the given vector. If the index of the swarm is <m>0</m> or the <m>all</m> symbol, all swarms will be translated.
    // @marg 0 @name swarm_index @optional 0 @type int/all
    // @marg 1 @name amount @optional 0 @type llll
    class_addmethod(c, (method)boids_anything,	"move",		A_GIMME,	0);
    
    // @method scale @digest Scale swarms
    // @description The word <m>scale</m> followed the index of a swarm and a number, scales the given swarm of the factor
    // specified by the number.
    // If the index of the swarm is <m>0</m> or the <m>all</m> symbol, all swarms will be scaled.
    // If, instead of a single factor, a list in the form <b>(<m>x_scale</m> <m>y_scale</m>)</b> is given,
    // two different scale factors are applied for the X and Y axis.
    // You can provide as third argument the scaling center, in <b>(<m>x</m> <m>y</m>)</b> form. If no center is provided,
    // by default the barycenter is used for single swarms scaling, while the origin <b>(0, 0)</b> is used when all swarms are to be scaled
    // The scaling center llll can be replaced by the <m>barycenter</m> symbol, to specify that scaling must happen with respect to individuals baricenters.
    // Alternatively you can add the "barycenter" symbol as third element in order to specify that coordinates are barycentric coordinates.
    // @marg 0 @name swarm_index @optional 0 @type int/all
    // @marg 1 @name factor @optional 0 @type number
    // @marg 2 @name origin @optional 1 @type llll/barycenter
    class_addmethod(c, (method)boids_anything,	"scale",		A_GIMME,	0);
    
    
    
    // @method clear @digest Clear elements
    // @description Deletes all the swarms and the custom rules.
    // If a first argument is given this might be the "swarms" symbol (to clear swarms only), or the "rules" symbol (to clear rules only).
    // @marg 0 @name what @optional 1 @type symbol
    class_addmethod(c, (method)boids_anything,	"clear",			A_GIMME,	0);

    
    // @method llll @digest Set state
    // @description Sets the current state of the object. The syntax must follow the one described in the
    // <m>dump</m> message documentation.
	class_addmethod(c, (method)boids_anything,	"anything",			A_GIMME,	0);
    class_addmethod(c, (method)boids_anything,	"setstoredstate",	A_GIMME, 0);
	
    
    // @method domain @digest Set the X domain
    // @description The <m>domain</m> message, followed by two numbers, sets minimum and maximum coordinates
    // to be displayed on the X axis.
    // The <m>domain</m> message,  followed by the "start" or "end" symbol and a number, sets the coordinate
    // to be displayed respectively at the left boundary or at the right boundary of the object box.
    // @marg 0 @name arguments @optional 0 @type list
    class_addmethod(c, (method)boids_anything,		"domain",		A_GIMME,	0);
    
    // @method range @digest Set the Y range
    // @description The <m>range</m> message, followed by two numbers, sets minimum and maximum coordinates
    // to be displayed on the Y axis
    // The <m>range</m> message,  followed by the "start" or "end" symbol and a number, sets the coordinate
    // to be displayed respectively at the bottom boundary or at top right boundary of the object box.
    // @marg 0 @name arguments @optional 0 @type list
    class_addmethod(c, (method)boids_anything,		"range",		A_GIMME,	0);
    
    
    // @method getdomain @digest Retrieve current X domain
    // @description The <m>getdomain</m> message outputs from the third outlet the minimum and maximum
    // coordinates displayed on the X axis, preceded by a <m>domain</m> symbol.
    class_addmethod(c, (method)boids_anything,		"getdomain",		A_GIMME,	0);
    
    
    // @method getrange @digest Retrieve current Y range
    // @description The <m>getrange</m> message outputs from the third outlet the minimum and maximum
    // coordinates displayed on the Y axis, preceded by a <m>range</m> symbol.
    class_addmethod(c, (method)boids_anything,		"getrange",		A_GIMME,	0);
    

    // @method play @digest Start sequencing
    // @description Starts the sequencing engine.
    class_addmethod(c, (method)boids_play,	"play",		A_GIMME,	0);
    
    // @method stop @digest Stop sequencing
    // @description Stops the sequencing engine.
    class_addmethod(c, (method)boids_stop,	"stop",		A_GIMME,	0);
    
    
    // @method clock @digest Select a clock source
    // @description The word <m>clock</m>, followed by the name of an existing <m>setclock</m> objects, sets the <o>dada.bounce</o>
    // object to be controlled by that <m>setclock</m> object rather than by Max's internal millisecond clock.
    // The word <m>clock</m> by itself sets the object back to using Max's regular millisecond clock.
    class_addmethod(c, (method) boids_clock,	"clock", A_DEFSYM, 0);
    
    // @method bang @digest Perform single step
    // @description Performs a single sequencing step.
    class_addmethod(c, (method) boids_bang,			"bang",			0);



    DADAOBJ_JBOX_DECLARE_READWRITE_METHODS(c);
    DADAOBJ_JBOX_DECLARE_ACCEPTSDRAG_METHODS(c);

    llllobj_class_add_out_attr(c, LLLL_OBJ_UI);
    dadaobj_class_init(c, LLLL_OBJ_UI, DADAOBJ_BBGIMAGE | DADAOBJ_ZOOM | DADAOBJ_CENTEROFFSET | DADAOBJ_EMBED | DADAOBJ_MOUSEHOVER | DADAOBJ_GRID | DADAOBJ_GRID_SHOWDEFAULT | DADAOBJ_AXES | DADAOBJ_LABELS | DADAOBJ_LABELS | DADAOBJ_UNDO | DADAOBJ_PLAY | DADAOBJ_NOTIFICATIONS);

    
    
	CLASS_ATTR_DEFAULT(c, "patching_rect", 0, "0 0 300 300");
	// @exclude dada.boids
	CLASS_ATTR_DEFAULT(c, "presentation_rect", 0, "0 0 300 300");
	// @exclude dada.boids
	
	
	
	CLASS_STICKY_ATTR(c,"category",0,"Behavior");

    CLASS_ATTR_CHAR(c,"seq",0, t_boids, output_sequencing);
    CLASS_ATTR_STYLE_LABEL(c, "seq", 0, "onoff", "Output Parameters While Sequencing");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"seq",0,"1");
    CLASS_ATTR_BASIC(c, "seq", 0);
    // @description Toggles the ability to output the parameters of all boids and swarms while sequencing, in the form
    // <b><m>swarm_name</m> <m>boid_id</m> <m>x</m> <m>y</m> <m>intensity</m></b>.
    
	
	CLASS_STICKY_ATTR_CLEAR(c, "category");
	

	
	CLASS_STICKY_ATTR(c,"category",0,"Appearance");
    
    CLASS_ATTR_CHAR(c,"showspeed",0, t_boids, show_speed);
    CLASS_ATTR_STYLE_LABEL(c, "showspeed", 0, "onoff", "Show Boid Speed");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showspeed",0,"1");
    CLASS_ATTR_BASIC(c, "showspeed", 0);
    // @description Toggles the ability to display the boids speed vector.

    CLASS_ATTR_CHAR(c,"shownames",0, t_boids, show_names);
    CLASS_ATTR_STYLE_LABEL(c, "shownames", 0, "onoff", "Show Swarm Names");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"shownames",0,"1");
    CLASS_ATTR_BASIC(c, "shownames", 0);
    // @description Toggles the ability to display the swarm names.

    CLASS_ATTR_CHAR(c,"showruleparams",0, t_boids, show_ruleparams);
    CLASS_ATTR_STYLE_LABEL(c, "showruleparams", 0, "onoff", "Show Rule Parameters");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showruleparams",0,"1");
    // @description Toggles the ability to display the rule parameters (if displayable).
    
    CLASS_ATTR_CHAR(c,"showruleparamnames",0, t_boids, show_ruleparam_names);
    CLASS_ATTR_STYLE_LABEL(c, "showruleparamnames", 0, "onoff", "Show Rule Parameter Names");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showruleparamnames",0,"1");
    // @description Toggles the ability to display the names of the displayable rule parameters.

    
    CLASS_ATTR_CHAR(c,"showintensity",0, t_boids, show_intensity);
    CLASS_ATTR_STYLE_LABEL(c, "showintensity", 0, "enumindex", "Show Boid Intensity");
    CLASS_ATTR_ENUMINDEX(c,"showintensity", 0, "None Colorscale Colorspectrum Alpha");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"showintensity",0,"3");
    CLASS_ATTR_BASIC(c, "showintensity", 0);
    // @description Toggles the ability to display the boid intensity in one of the following ways: <br />
    // None: no intensity display. <br />
    // Colorscale: fade swarm color to white. <br />
    // Colorspectrum: use full color spectrum (red to violet). <br />
    // Alpha: use transparency. <br />

    CLASS_STICKY_ATTR_CLEAR(c, "category");

    
    CLASS_STICKY_ATTR(c,"category",0,"Color");

    CLASS_ATTR_CHAR(c,"fixedruleparamscolor",0, t_boids, use_separate_ruleparams_color);
    CLASS_ATTR_STYLE_LABEL(c, "fixedruleparamscolor", 0, "onoff", "Use Fixed Color for Rule Parameter");
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c,"fixedruleparamscolor",0,"1");
    // @description Toggles the ability to use a fixed color, instead of swarm colors, to display rule parameters.
    // Such color is defined via the <m>ruleparamscolor</m> attribute.

    CLASS_ATTR_RGBA(c, "ruleparamscolor", 0, t_boids, ruleparams_color);
    CLASS_ATTR_DEFAULT_SAVE_PAINT(c, "ruleparamscolor", 0, "0. 0. 0. 1.");
    CLASS_ATTR_STYLE_LABEL(c, "ruleparamscolor", 0, "rgba", "Rule Parameters Color");
    CLASS_ATTR_BASIC(c, "ruleparamscolor", 0);
    // @description Sets the color used to display rule parameters, but only if <m>fixedruleparamscolor</m> is active; otherwise
    // this color is overridden by the defined swarm colors.

    CLASS_STICKY_ATTR_CLEAR(c, "category");

    
    srand(time(NULL));
	
	class_register(CLASS_BOX, c); /* CLASS_NOBOX */
	boids_class = c;
	
	dev_post("dada.boids compiled %s %s", __DATE__, __TIME__);
	return 0;
}

t_max_err boids_notify(t_boids *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	if (msg == _sym_attr_modified) {
		t_symbol *attr_name = (t_symbol *)object_method((t_object *)data, _sym_getname);
		if (attr_name == _llllobj_sym_zoom || attr_name == gensym("center")) {
			jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
			jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
			jbox_redraw((t_jbox *)x);
		} else if (attr_name == gensym("grid")) {
			jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
			jbox_redraw((t_jbox *)x);
		}
	}
	
	return MAX_ERR_NONE;
}

void boids_begin_preset(t_boids *x, t_symbol *s, long argc, t_atom *argv)
{
	dadaobj_begin_preset(dadaobj_cast(x), s, argc, argv);
}


void boids_restore_preset(t_boids *x, t_symbol *s, long argc, t_atom *argv)
{
	dadaobj_restore_preset(dadaobj_cast(x), s, argc, argv);
}

void boids_end_preset(t_boids *x)
{
	dadaobj_end_preset(dadaobj_cast(x));
}

void boids_preset(t_boids *x) {
	dadaobj_preset(dadaobj_cast(x));
}


void boids_jsave(t_boids *x, t_dictionary *d)
{
	if (x->b_ob.d_ob.save_data_with_patcher){
		if (x->b_ob.r_ob.l_dictll) {
			llll_store_in_dictionary(x->b_ob.r_ob.l_dictll, d, "boids_data", NULL);
		} else {
			t_llll *data = boids_get_state(x);
			llll_store_in_dictionary(data, d, "boids_data", NULL);
			llll_free(data);
		}
	} 
}



t_llll *boids_get_single_swarm(t_boids *x, long idx)
{
	t_llll *ll = llll_get();
    t_llll *speed = llll_get();
    t_llll *coord = llll_get();
    t_llll *rules = llll_get();
    long i;
    
    llll_appendllll(ll, symbol_and_symbol_to_llll(gensym("name"), x->swarm[idx].name));
    llll_appendllll(ll, symbol_and_long_to_llll(gensym("size"), x->swarm[idx].num_boids));
    
    llll_appendsym(coord, gensym("coord"));
    llll_appendsym(speed, gensym("speed"));
    for (i = 0; i < x->swarm[idx].num_boids; i++) {
        llll_appendllll(coord, pt_to_llll(x->swarm[idx].coord[i].pt, false));
        llll_appendllll(speed, pt_to_llll(x->swarm[idx].speed[i].pt, false));
    }

    llll_appendllll(ll, coord);
    llll_appendllll(ll, speed);
    
    if (x->use_intensity) {
        t_llll *intensity = llll_get();
        t_llll *intensityspeed = llll_get();
        llll_appendsym(intensity, gensym("intensity"));
        llll_appendsym(intensityspeed, gensym("intensityspeed"));
        for (i = 0; i < x->swarm[idx].num_boids; i++) {
            llll_appenddouble(intensity, x->swarm[idx].coord[i].intensity);
            llll_appenddouble(intensityspeed, x->swarm[idx].speed[i].intensity);
        }
        llll_appendllll(ll, intensity);
        llll_appendllll(ll, intensityspeed);
    }
    
    llll_appendllll(ll, symbol_and_double_to_llll(gensym("maxspeed"), x->swarm[idx].max_speed));
    llll_appendllll(ll, symbol_and_double_to_llll(gensym("maxintensity"), x->swarm[idx].max_intensity));
    llll_appendllll(ll, symbol_and_llll_to_llll_chained(gensym("color"), color_to_llll(&x->swarm[idx].color)));
    
    // rules
    llll_appendsym(rules, gensym("applyrule"));
    for (i = 0; i < x->swarm[idx].num_rule_refs; i++) {
        t_llll *this_rule = llll_get();
        llll_appendsym(this_rule, x->swarm[idx].rule_ref[i].name);
        // append parameters
        llll_appendllll(this_rule, symbol_and_double_to_llll(gensym("gain"), x->swarm[idx].rule_ref[i].gain));
        for (long j = 0; j < x->swarm[idx].rule_ref[i].num_params; j++) {
            switch (x->swarm[idx].rule_ref[i].param[j].r_type) {
                case DADA_BOIDS_RULE_PARAM_LONG:
                    llll_appendllll(this_rule, symbol_and_long_to_llll(x->swarm[idx].rule_ref[i].param[j].r_name, x->swarm[idx].rule_ref[i].param[j].r_param.w_long));
                    break;
                case DADA_BOIDS_RULE_PARAM_DOUBLE:
                    llll_appendllll(this_rule, symbol_and_double_to_llll(x->swarm[idx].rule_ref[i].param[j].r_name, x->swarm[idx].rule_ref[i].param[j].r_param.w_double));
                    break;
                case DADA_BOIDS_RULE_PARAM_PT:
                    llll_appendllll(this_rule, symbol_and_llll_to_llll_chained(x->swarm[idx].rule_ref[i].param[j].r_name, pt_to_llll(x->swarm[idx].rule_ref[i].param[j].r_param.w_pt, false)));
                    break;
                default:
                    break;
            }
        }
        llll_appendllll(rules, this_rule);
    }

    llll_appendllll(ll, rules);

    dadaitem_append_flags_to_llll(ll, (t_dadaitem *)(&x->swarm[idx]), false);
	return ll;
}



t_llll *boids_get_swarms(t_boids *x)
{
	long i;
	t_llll *out_ll = llll_get();
	long num_swarms = dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, (e_dadaitem_types)DADAITEM_TYPE_SWARM);
	for (i = 0; i < num_swarms; i++)
		llll_appendllll(out_ll, boids_get_single_swarm(x, i), 0, WHITENULL_llll);
	llll_prependsym(out_ll, gensym("swarms"), 0, WHITENULL_llll);
	return out_ll;
}


t_llll *boids_get_single_rule(t_boids *x, long idx)
{
    t_llll *ll = llll_get();
    
    llll_appendllll(ll, symbol_and_symbol_to_llll(gensym("name"), x->rule_prototypes[idx].name));
    llll_appendllll(ll, symbol_and_symbol_to_llll(gensym("code"), x->rule_prototypes[idx].fun_code ? x->rule_prototypes[idx].fun_code : gensym("private")));
    llll_appendllll(ll, symbol_and_double_to_llll(gensym("defaultgain"), x->rule_prototypes[idx].default_gain));
    llll_appendllll(ll, symbol_and_long_to_llll(gensym("abscoord"), x->rule_prototypes[idx].output_position_is_absolute));
    llll_appendllll(ll, symbol_and_long_to_llll(gensym("absintensity"), x->rule_prototypes[idx].output_intensity_is_absolute));
    
    long i;
    t_llll *params = llll_get();
    llll_appendsym(params, gensym("params"));
    for (i = 0; i < x->rule_prototypes[idx].num_params; i++) {
        // add parameter
        t_llll *this_param = llll_get();
        llll_appendsym(this_param, x->rule_prototypes[idx].param[i].r_name);
        switch (x->rule_prototypes[idx].param[i].r_type) {
            case DADA_BOIDS_RULE_PARAM_NONE:
                llll_appendsym(this_param, _llllobj_sym_none);
                break;

            case DADA_BOIDS_RULE_PARAM_LONG:
                llll_appendsym(this_param, gensym("int"));
                llll_appendlong(this_param, x->rule_prototypes[idx].param[i].r_param.w_long);
                break;

            case DADA_BOIDS_RULE_PARAM_DOUBLE:
                llll_appendsym(this_param, gensym("float"));
                llll_appendlong(this_param, x->rule_prototypes[idx].param[i].r_param.w_double);
                break;

            case DADA_BOIDS_RULE_PARAM_PT:
                llll_appendsym(this_param, gensym("pt"));
                llll_appenddouble(this_param, x->rule_prototypes[idx].param[i].r_param.w_pt.x);
                llll_appenddouble(this_param, x->rule_prototypes[idx].param[i].r_param.w_pt.y);
                break;

            default:
                break;
        }
        llll_appendllll(params, this_param);
    }
    
    llll_appendllll(ll, params);
    
    return ll;
}


t_llll *boids_get_rules(t_boids *x)
{
    long i;
    t_llll *out_ll = llll_get();
    for (i = x->num_standard_rules; i < x->num_rule_prototypes; i++)
        llll_appendllll(out_ll, boids_get_single_rule(x, i));
    llll_prependsym(out_ll, gensym("rules"), 0, WHITENULL_llll);
    return out_ll;
}


t_llll *boids_get_state_sel(t_boids *x, char get_rules, char get_swarms)
{
	t_llll *data = llll_get();

    llll_prependsym(data, gensym("boids"), 0, WHITENULL_llll);

    if (get_rules)
        llll_appendllll(data, boids_get_rules(x), 0, WHITENULL_llll);

	if (get_swarms)
		llll_appendllll(data, boids_get_swarms(x), 0, WHITENULL_llll);
	
	return data;
}

t_llll *boids_get_state(t_boids *x)
{
	return boids_get_state_sel(x, true, true);
}


void boids_iar(t_boids *x)
{
    jbox_invalidate_layer((t_object *)x, NULL, gensym("room"));
    jbox_invalidate_layer((t_object *)x, NULL, gensym("grid"));
    jbox_redraw((t_jbox *)x);
}


void boids_delete_swarm(t_boids *x, long idx)
{
    long num_swarms = dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_SWARM);
    if (idx >= 0 && idx < num_swarms)
        dadaitem_delete(dadaobj_cast(x), DADAITEM_TYPE_SWARM, idx, 0);
    boids_iar(x);
}

void boids_delete_swarms(t_boids *x, t_llll *swarms)
{
    t_llllelem *elem;
    for (elem = swarms->l_head; elem; elem = elem->l_next)
        if (is_hatom_number(&elem->l_hatom))
            dadaitem_delete(dadaobj_cast(x), DADAITEM_TYPE_SWARM, hatom_getlong(&elem->l_hatom) - 1, 0);
    boids_iar(x);
}


t_pt boids_get_coord_barycenter(long num_coords, t_boids_coord *coords)
{
    long i;
    t_pt sum = build_pt(0, 0);
    if (num_coords >= 1) {
        for (i = 0; i < num_coords; i++)
            sum = pt_pt_sum(sum, coords[i].pt);
        sum = pt_number_prod(sum, 1./num_coords);
    }
    return sum;
}



long boids_param_name_to_idx(t_boids *x, t_boids_swarm *sw, long rule_idx, t_symbol *param_name)
{
    long i;
    for (i = 0; i < x->rule_prototypes[rule_idx].num_params; i++)
        if (x->rule_prototypes[rule_idx].param[i].r_name == param_name)
            return i;
    return -1;
}

long boids_swarm_parse_param(t_boids *x, t_boids_swarm *sw, long rule_idx, long rule_ref_idx, t_llllelem *par_elem)
{
    long found = 0;
    t_llll *ll;
    if (par_elem && hatom_gettype(&par_elem->l_hatom) == H_LLLL && (ll = hatom_getllll(&par_elem->l_hatom)) && ll->l_head && hatom_gettype(&ll->l_head->l_hatom) == H_SYM) {
        t_symbol *router = hatom_getsym(&ll->l_head->l_hatom);
        t_llllelem *elem = ll->l_head->l_next;
        if (router == gensym("gain")) {
            sw->rule_ref[rule_ref_idx].gain = elem && is_hatom_number(&elem->l_hatom) ? hatom_getdouble(&elem->l_hatom) : 1.;
            found = 1;
        } else {
            long param_idx = boids_param_name_to_idx(x, sw, rule_idx, router);
            if (param_idx >= 0) {
                t_llllelem *elem = ll->l_head->l_next;
                found = 2;
                switch (x->rule_prototypes[rule_idx].param[param_idx].r_type) {
                    case DADA_BOIDS_RULE_PARAM_LONG:
                        sw->rule_ref[rule_ref_idx].param[param_idx].r_type = DADA_BOIDS_RULE_PARAM_LONG;
                        sw->rule_ref[rule_ref_idx].param[param_idx].r_param.w_long = elem && is_hatom_number(&elem->l_hatom) ? hatom_getlong(&elem->l_hatom) : x->rule_prototypes[rule_idx].param[param_idx].r_param.w_long;
                        break;
                        
                    case DADA_BOIDS_RULE_PARAM_DOUBLE:
                        sw->rule_ref[rule_ref_idx].param[param_idx].r_type = DADA_BOIDS_RULE_PARAM_DOUBLE;
                        sw->rule_ref[rule_ref_idx].param[param_idx].r_param.w_double = elem && is_hatom_number(&elem->l_hatom) ? hatom_getdouble(&elem->l_hatom) : x->rule_prototypes[rule_idx].param[param_idx].r_param.w_double;
                        break;
                        
                    case DADA_BOIDS_RULE_PARAM_PT:
                        sw->rule_ref[rule_ref_idx].param[param_idx].r_type = DADA_BOIDS_RULE_PARAM_PT;
                        sw->rule_ref[rule_ref_idx].param[param_idx].r_param.w_pt.x = elem && is_hatom_number(&elem->l_hatom) ? hatom_getdouble(&elem->l_hatom) : x->rule_prototypes[rule_idx].param[param_idx].r_param.w_pt.x;
                        sw->rule_ref[rule_ref_idx].param[param_idx].r_param.w_pt.y = elem && elem->l_next && is_hatom_number(&elem->l_next->l_hatom) ? hatom_getdouble(&elem->l_next->l_hatom) : x->rule_prototypes[rule_idx].param[param_idx].r_param.w_pt.y;
                        break;
                        
                    default:
                        break;
                }
            }
        }
    }
    
    return found;
}


void boids_change_rule_params(t_boids *x, long swarm_idx, t_symbol *rule, t_llll *params)
{
    if (swarm_idx >= 0 && swarm_idx < boids_get_num_swarms(x)) {
        t_llllelem *elem;
        t_boids_swarm *sw = &x->swarm[swarm_idx];
        long rule_idx = boids_ruleprototype_name_to_idx(x, rule);
        long rule_ref_idx = boids_rulereference_name_to_idx(x, sw, rule);
        for (elem = params->l_head; sw && elem; elem = elem->l_next)
            boids_swarm_parse_param(x, sw, rule_idx, rule_ref_idx, elem);
    }
}

void import_pt(t_boids *x, t_llll *coords_ll, t_llll *intensities_ll, long size, t_boids_coord *coords)
{
    long j;
    /// IMPORTING POSITIONS
    if (coords_ll && coords_ll->l_head && hatom_gettype(&coords_ll->l_head->l_hatom) == H_SYM) {
        t_symbol *distrib = hatom_getsym(&coords_ll->l_head->l_hatom);
        if (distrib == gensym("uniform")) {
            t_llll *temp = llll_clone(coords_ll);
            if (temp->l_head) llll_behead(temp);
            t_rect rect = llll_to_rect(temp);
            for (j = 0; j < size; j++)
                coords[j].pt = build_pt(rand_f(rect.x, rect.x + rect.width), rand_f(rect.y, rect.y + rect.height));
        }
    } else if (coords_ll && coords_ll->l_depth == 2) {
        t_llllelem *tmp;
        for (j = 0, tmp = coords_ll->l_head; tmp && j < size; tmp = tmp->l_next ? tmp->l_next : tmp, j++)
            if (hatom_gettype(&tmp->l_hatom) == H_LLLL)
                coords[j].pt = llll_to_pt(hatom_getllll(&tmp->l_hatom));
    }
    
    /// IMPORTING INTENSITIES
    if (intensities_ll && intensities_ll->l_head && hatom_gettype(&intensities_ll->l_head->l_hatom) == H_SYM) {
        t_symbol *distrib = hatom_getsym(&intensities_ll->l_head->l_hatom);
        if (distrib == gensym("uniform")) {
            double from = (intensities_ll->l_head->l_next && is_hatom_number(&intensities_ll->l_head->l_next->l_hatom)) ? hatom_getdouble(&intensities_ll->l_head->l_next->l_hatom) : 0;
            double to = (intensities_ll->l_head->l_next && intensities_ll->l_head->l_next->l_next && is_hatom_number(&intensities_ll->l_head->l_next->l_next->l_hatom)) ? hatom_getdouble(&intensities_ll->l_head->l_next->l_next->l_hatom) : 0;
            for (j = 0; j < size; j++)
                coords[j].intensity = rand_f(from, to);
        }
    } else if (intensities_ll) {
        t_llllelem *tmp;
        for (j = 0, tmp = intensities_ll->l_head; tmp && j < size; tmp = tmp->l_next ? tmp->l_next : tmp, j++)
            coords[j].intensity = hatom_getdouble(&tmp->l_hatom);
    } else {
        for (j = 0; j < size; j++)
            coords[j].intensity = 1.;
    }
}


void boids_change_swarm(t_boids *x, long idx, t_llll *params)
{
    dadaobj_mutex_lock(dadaobj_cast(x));
    long num_swarms = dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_SWARM);
    if (idx >= 0 && idx < num_swarms) {
        t_dadaitem *item = dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&dadaobj_cast(x)->m_classes, DADAITEM_TYPE_SWARM), idx);
        t_boids_swarm *sw = ((t_boids_swarm *)item);
        t_llllelem *elem;
        for (elem = params->l_head; elem; elem = elem->l_next) {
            if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
                t_llll *ll = hatom_getllll(&elem->l_hatom);
                if (ll && ll->l_size >= 2 && hatom_gettype(&ll->l_head->l_hatom) == H_SYM) {
                    t_symbol *router = hatom_getsym(&ll->l_head->l_hatom);
                    llll_behead(ll);
                    if (router == gensym("size")) {
                        long new_num_boids = MIN(DADA_BOIDS_MAX_PARTICLES_PER_SWARM, hatom_getlong(&ll->l_head->l_hatom));
                        if (new_num_boids > sw->num_boids) {
                            // creating the new elements. Where? around the barycenter
                            long j;
                            t_pt bc = boids_get_coord_barycenter(sw->num_boids, sw->coord);
                            for (j = sw->num_boids; j < new_num_boids; j++) {
                                sw->coord[j].pt = bc;
                                sw->coord[j].intensity = 1.;
                            }
                        }
                        sw->num_boids = new_num_boids;
                    } else if (router == gensym("name")) {
                        sw->name = hatom_getsym(&ll->l_head->l_hatom);
                    } else if (router == gensym("maxspeed")) {
                        sw->max_speed = hatom_getdouble(&ll->l_head->l_hatom);
                    } else if (router == gensym("maxintensity")) {
                        sw->max_intensity = hatom_getdouble(&ll->l_head->l_hatom);
                    } else if (router == gensym("color")) {
                        sw->color = llll_to_color(ll);
                    }
                }
            }
        }
    }
    dadaobj_mutex_unlock(dadaobj_cast(x));
}

// use idx < 0 to ADD the swarm
void boids_add_single_swarm(t_boids *x, t_llll *params)
{
    t_llll *coords_ll = NULL, *speeds_ll = NULL, *intensity_ll = NULL, *intensity_speed_ll = NULL, *rules_ref_ll = NULL;
    long size = 0;
    t_boids_coord coords[DADA_BOIDS_MAX_PARTICLES_PER_SWARM], speeds[DADA_BOIDS_MAX_PARTICLES_PER_SWARM];
    t_jrgba color = long_to_color(dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_SWARM) + 1);
    t_symbol *name = NULL;
    long flags = 0;
    double maxspeed = 0, maxintensity = 1;
    dadaobj_parseargs(dadaobj_cast(x), params, (char *)"l4444sC4ddF", gensym("size"), &size, gensym("coord"), &coords_ll, gensym("speed"), &speeds_ll, gensym("intensity"), &intensity_ll, gensym("intensityspeed"), &intensity_speed_ll, gensym("name"), &name, gensym("color"), &color, gensym("applyrule"), &rules_ref_ll, gensym("maxspeed"), &maxspeed, gensym("maxintensity"), &maxintensity, gensym("flags"), &flags);
    
    long j;
    CLIP_ASSIGN(size, 0, DADA_BOIDS_MAX_PARTICLES_PER_SWARM);
    for (j = 0; j < size; j++)
        coords[j] = speeds[j] = get_null_boids_coord();
    
    
    import_pt(x, coords_ll, intensity_ll, size, coords);
    import_pt(x, speeds_ll, intensity_speed_ll, size, speeds);
    
    long idx = dadaitem_add(dadaobj_cast(x), DADAITEM_TYPE_SWARM, build_pt(0, 0), 0, 0, color, NULL, flags, DIA_POSTPROCESS);
    
    if (idx >= 0) {
        t_dadaobj *r_ob = dadaobj_cast(x);
        t_dadaitem *item = dadaitem_class_get_nth_item(r_ob, dadaitem_class_get_id(&r_ob->m_classes, DADAITEM_TYPE_SWARM), idx);
        t_boids_swarm *sw = ((t_boids_swarm *)item);
        sw->num_boids = size;
        sw->color = color;
        sw->name = name ? name : symbol_unique();
        sysmem_copyptr(coords, sw->coord, size * sizeof(t_boids_coord));
        sysmem_copyptr(speeds, sw->speed, size * sizeof(t_boids_coord));
        
        sw->max_speed = maxspeed;
        sw->max_intensity = maxintensity;
        
        /// IMPORTING RULE REFERENCES for swarm
        
        sw->num_rule_refs = 0;
        if (rules_ref_ll) {
            t_llllelem *tmp;
            for (tmp = rules_ref_ll->l_head; tmp; tmp = tmp->l_next) {
                if (hatom_gettype(&tmp->l_hatom) == H_LLLL) {
                    t_llll *ll = hatom_getllll(&tmp->l_hatom);
                    if (ll && ll->l_head && hatom_gettype(&ll->l_head->l_hatom) == H_SYM) {
                        t_symbol *rule_name = hatom_getsym(&ll->l_head->l_hatom);
                        long rule_idx = boids_ruleprototype_name_to_idx(x, rule_name);
                        if (rule_idx >= 0) {
                            t_llllelem *tmp2;
                            sw->rule_ref[sw->num_rule_refs].name = rule_name;
                            tmp2 = ll->l_head->l_next;
                            sw->rule_ref[sw->num_rule_refs].gain = x->rule_prototypes[rule_idx].default_gain;
                            if (tmp2 && tmp2 && is_hatom_number(&tmp2->l_hatom))
                                sw->rule_ref[sw->num_rule_refs].gain = hatom_getdouble(&tmp2->l_hatom);
                            
                            // setting all rule parameters to default one
                            sw->rule_ref[sw->num_rule_refs].num_params = x->rule_prototypes[rule_idx].num_params;
                            for (long k = 0; k < x->rule_prototypes[rule_idx].num_params; k++)
                                sw->rule_ref[sw->num_rule_refs].param[k] = x->rule_prototypes[rule_idx].param[k]; // default
                            
                            // parsing all rule parameters
                            for (; tmp2; tmp2 = tmp2->l_next)
                                boids_swarm_parse_param(x, sw, rule_idx, sw->num_rule_refs, tmp2);
                            sw->num_rule_refs++;
                            
                        } else {
                            // rule not found: we keep the "dummy" skeleton anyway, for saving/syncing issues
                            // (i.e.: what if we create this swarm before entering the actual rule?
                            sw->rule_ref[sw->num_rule_refs].name = rule_name;
                            sw->rule_ref[sw->num_rule_refs].gain = 0.;
                            sw->rule_ref[sw->num_rule_refs].num_params = 0.;
                            sw->rule_ref[sw->num_rule_refs].dummy_ref = 1;
                            sw->num_rule_refs++;
                            object_warn((t_object *)x, "Rule %s has not been found. Beware: swarm will not behave according to such rule.", rule_name ? rule_name->s_name : "");
                        }
                    }
                } else if (hatom_gettype(&tmp->l_hatom) == H_SYM) {
                    t_symbol *rule_name = hatom_getsym(&tmp->l_hatom);
                    long rule_idx = boids_ruleprototype_name_to_idx(x, rule_name);
                    if (rule_idx >= 0) {
                        sw->rule_ref[sw->num_rule_refs].name = rule_name;
                        sw->rule_ref[sw->num_rule_refs].gain = x->rule_prototypes[rule_idx].default_gain;
                        sw->rule_ref[sw->num_rule_refs].num_params = x->rule_prototypes[rule_idx].num_params;
                        for (long k = 0; k < x->rule_prototypes[rule_idx].num_params; k++)
                            sw->rule_ref[sw->num_rule_refs].param[k] = x->rule_prototypes[rule_idx].param[k]; // default
                        sw->rule_ref[sw->num_rule_refs].dummy_ref = 0;
                        sw->num_rule_refs++;
                    } else {
                        // rule not found: we keep the "dummy" skeleton anyway, for saving/syncing issues
                        // (i.e.: what if we create this swarm before entering the actual rule?
                        sw->rule_ref[sw->num_rule_refs].name = rule_name;
                        sw->rule_ref[sw->num_rule_refs].gain = 0.;
                        sw->rule_ref[sw->num_rule_refs].num_params = 0.;
                        sw->rule_ref[sw->num_rule_refs].dummy_ref = 1;
                        sw->num_rule_refs++;
                        object_warn((t_object *)x, "Rule %s has not been found. Beware: swarm will not behave according to such rule.", rule_name ? rule_name->s_name : "");
                    }
                }
            }
        }
        
    }
    
    llll_free(coords_ll);
    llll_free(speeds_ll);
    llll_free(intensity_ll);
    llll_free(intensity_speed_ll);
    llll_free(rules_ref_ll);
}


void boids_add_swarms(t_boids *x, t_llll *swarms)
{
    long i;
    t_llllelem *elem;
    for (i = 0, elem = swarms->l_head; elem && i < DADA_BOIDS_MAX_SWARMS; elem = elem->l_next, i++) {
        if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
            t_llll *ll = hatom_getllll(&elem->l_hatom);
            boids_add_single_swarm(x, ll);
        }
    }
    
    boids_iar(x);
}

void boids_add_single_rule(t_boids *x, t_llll *rule, t_symbol *def_name, t_symbol *def_code)
{
    
    if (rule->l_size >= 2) {
        t_symbol *rule_name = def_name;
        t_symbol *rule_code = def_code;
        
        long output_position_is_absolute = 0, output_intensity_is_absolute = 0;
        double default_gain = 1.;
        dadaobj_parseargs(dadaobj_cast(x), rule, (char *)"sslld", gensym("name"), &rule_name, gensym("code"), &rule_code, gensym("abscoord"), &output_position_is_absolute, gensym("absintensity"), &output_intensity_is_absolute, gensym("defaultgain"), &default_gain);
        
        if (rule_name && rule_code) {
            long idx = boids_ruleprototype_name_to_idx(x, rule_name);
            if (idx >= 0) {
                if (idx < x->num_standard_rules) {
                    object_error((t_object *)x, "Cannot re-define built-in rule %s: use another rule name.", rule_name->s_name);
                } else {
                    boids_substitute_rule_prototype_from_code(x, idx, rule_name, rule_code, default_gain, output_position_is_absolute, output_intensity_is_absolute, 0, NULL);
                    object_warn((t_object *)x, "Rule %s was already defined: it has been updated.", rule_name->s_name);
                }
            } else
                boids_add_rule_prototype_from_code(x, rule_name, rule_code, default_gain, output_position_is_absolute, output_intensity_is_absolute, 0, NULL);
        }
    }
    
}

void boids_add_rules(t_boids *x, t_llll *rules)
{
    long i;
    t_llllelem *elem;
    for (i = 0, elem = rules->l_head; elem && i < DADA_BOIDS_MAX_SWARMS; elem = elem->l_next, i++) {
        if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
            t_llll *ll = hatom_getllll(&elem->l_hatom);
            boids_add_single_rule(x, ll, NULL, NULL);
        }
    }
}


void boids_clear_rules(t_boids *x)
{
    // free all clangs
    t_llllelem *elem;
    for (elem = x->clang_ll->l_head; elem; elem = elem->l_next)
        object_free_debug((t_object *)hatom_getobj(&elem->l_hatom));
    llll_clear(x->clang_ll);

    x->num_rule_prototypes = x->num_standard_rules;
}

void boids_set_rules(t_boids *x, t_llll *customrules)
{
    boids_clear_rules(x);
    boids_add_rules(x, customrules);
}



void boids_clear_swarms(t_boids *x)
{
    t_dadaobj *r_ob = dadaobj_cast(x);
    dadaitem_class_clear(r_ob, &r_ob->m_classes, &r_ob->m_interface, &r_ob->m_undo, (e_dadaitem_types)DADAITEM_TYPE_SWARM, 0);
}


void boids_set_swarms(t_boids *x, t_llll *swarms)
{
    boids_clear_swarms(x);
    boids_add_swarms(x, swarms);
}

void boids_clear(t_boids *x, char rules, char swarms)
{
    if (rules)
        boids_clear_rules(x);
    if (swarms)
        boids_clear_swarms(x);
}


// see boids_get_state about the codification of info
void boids_set_state(t_boids *x, t_llll *state)
{
    t_llllelem *elem = state->l_head;
    
    x->itsme = true;
    if (elem && hatom_gettype(&elem->l_hatom) == H_SYM && hatom_getsym(&elem->l_hatom) == gensym("boids"))
        elem = elem->l_next;
    
    while (elem && hatom_gettype(&elem->l_hatom) == H_LLLL && hatom_getllll(&elem->l_hatom)->l_head &&
           hatom_gettype(&hatom_getllll(&elem->l_hatom)->l_head->l_hatom) == H_SYM){
        
        if (hatom_getsym(&hatom_getllll(&elem->l_hatom)->l_head->l_hatom) == gensym("rules"))
            boids_set_rules(x, hatom_getllll(&elem->l_hatom));

        if (hatom_getsym(&hatom_getllll(&elem->l_hatom)->l_head->l_hatom) == gensym("swarms"))
            boids_set_swarms(x, hatom_getllll(&elem->l_hatom));

        elem = elem->l_next;
    }
    x->itsme = false;

	boids_postprocess(x);
}





void boids_assist(t_boids *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type anything @digest Incoming symbol or list
		sprintf(s, "Incoming symbol or list");
	} 
	else {	
        char *type = NULL;
        llllobj_get_llll_outlet_type_as_string((t_object *) x, LLLL_OBJ_UI, a, &type);
		if (a == 0)	// @out 0 @type llll @digest Dump outlet
			sprintf(s, "llll (%s): Dump Outlet", type);
		else if (a == 1)	// @out 1 @type llll @digest Queries and notifications
			sprintf(s, "llll (%s): Queries and Notifications", type);
        else if (a == 2)	// @out 2 @type list @digest Sequencing data
            sprintf(s, "list: Sequencing Data");
		else 	// @out 3 @type bang @digest bang when object is changed via the interface
			sprintf(s, "bang when Changed"); 			
	}
}


void swarm_free(t_dadaobj *r_ob, t_dadaitem *item, void *data)
{
    ;
//    t_boids_swarm *swarm = (t_boids_swarm *)item;
}

void boids_free(t_boids *x)
{
    // free all clangs!
    t_llllelem *elem;
    for (elem = x->clang_ll->l_head; elem; elem = elem->l_next)
        object_free_debug((t_object *)hatom_getobj(&elem->l_hatom));
    llll_free(x->clang_ll);
    
	object_free_debug(x->n_proxy1);
	dadaobj_jbox_free((t_dadaobj_jbox *)x); // jbox_free and llllobj_free are inside here
}


void *boids_new(t_symbol *s, long argc, t_atom *argv)
{
	t_boids *x = NULL;
	t_dictionary *d = NULL;
	long boxflags;
	t_llll *llll_for_rebuild = NULL;
	
	if (!(d = object_dictionaryarg(argc,argv)))
		return NULL;    
	
	if ((x = (t_boids *)object_alloc_debug(boids_class))) {
		
		x->creating_new_obj = true;
        x->use_intensity = true;
        
		x->b_ob.d_ob.m_tools.curr_tool = DADA_TOOL_ARROW;
		x->firsttime = true;
		x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
		
		boxflags = 0 
		| JBOX_DRAWFIRSTIN 
		| JBOX_NODRAWBOX
		| JBOX_DRAWINLAST
		| JBOX_TRANSPARENT  
//      | JBOX_NOGROW
//		| JBOX_GROWY
		| JBOX_GROWBOTH
		| JBOX_HILITE
//      | JBOX_BACKGROUND
		| JBOX_DRAWBACKGROUND
//      | JBOX_NOFLOATINSPECTOR
//      | JBOX_MOUSEDRAGDELTA
//      | JBOX_TEXTFIELD
		;
		
		jbox_new((t_jbox *)x, boxflags, argc, argv);
		x->b_ob.r_ob.l_box.b_firstin = (t_object *)x;
		x->n_proxy1 = proxy_new((t_object *) x, 1, &x->n_in);
        
        x->clang_ll = llll_get();
		
        dadaobj_jbox_setup((t_dadaobj_jbox *)x, DADAOBJ_BBGIMAGE | DADAOBJ_ZOOM | DADAOBJ_CENTEROFFSET | DADAOBJ_UNDO | DADAOBJ_CHANGEDBANG | DADAOBJ_NOTIFICATIONS, build_pt(1., 1.), -1, 3, 1, (invalidate_and_redraw_fn)boids_iar, "qsr", 2, "bl44");
		dadaobj_addfunctions(dadaobj_cast(x), (dada_mousemove_fn)boids_mousemove, (method)boids_task, (method)boids_postprocess_undo, (get_state_fn)boids_get_state, (set_state_fn)boids_set_state, NULL, NULL, NULL);

		dadaobj_dadaitem_class_alloc(dadaobj_cast(x), DADAITEM_TYPE_SWARM, gensym("swarm"), gensym("Swarm"), DADA_ITEM_ALLOC_ARRAY, 0, false, sizeof(t_boids_swarm), calcoffset(t_boids, swarm), DADA_BOIDS_MAX_SWARMS, NULL, DADA_FUNC_v_oX, (method)boids_set_swarms, NULL, DADA_FUNC_X_o, (method)boids_get_swarms, NULL, (method)postprocess_boids, NULL, (method)swarm_free, false, false);
		
        
//        boids_add_swarms
//		dadaitem_card_add(dadaobj_cast(x), build_pt(0, 0), -1, 45, DADA_BLACK, gensym("Tuba"), gensym("Tb.png"), 0.5, 0, 0);
		
        boids_add_standard_rules(x);

		attr_dictionary_process(x,d);
		
		if ((llll_for_rebuild = llll_retrieve_from_dictionary(d, "boids_data"))) { // new method
			llllobj_manage_dict_llll((t_object *)x, LLLL_OBJ_UI, llll_for_rebuild);
			boids_set_state(x, llll_for_rebuild);
			llll_free(llll_for_rebuild);
		}
		
		jbox_ready((t_jbox *)x);
		
		x->creating_new_obj = false;
	}
	return x;
}

void boids_int(t_boids *x, t_atom_long num)
{
    if (num == 0)
        boids_stop(x, NULL, 0, NULL);
    else
        boids_play(x, NULL, 0, NULL);
/*	t_atom argv[1];
	atom_setlong(argv, num);
	boids_anything(x, _sym_list, 1, argv);*/
}

void boids_float(t_boids *x, double num)
{
	t_atom argv[1]; 
	atom_setfloat(argv, num);
	boids_anything(x, _sym_list, 1, argv);
}


void boids_dump(t_boids *x, char get_rules, char get_swarms)
{	
	t_llll *ll = boids_get_state_sel(x, get_rules, get_swarms);
	llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 0, ll);
	llll_free(ll);
}

long boids_swarm_name_to_idx(t_boids *x, t_symbol *name)
{
    long i;
    long num_swarms = boids_get_num_swarms(x);
    for (i = 0; i < num_swarms; i++)
        if (x->swarm[i].name == name)
            return i;
    return -1;
}


void boids_rotate(t_boids *x, t_llll *args)
{
    dadaobj_mutex_lock(dadaobj_cast(x));
    boids_undo_step_push(x, gensym("Rotate"));

    t_pt center = build_pt(0, 0);
    char center_is_user_specified = false;
    char center_is_wr_to_baricenter = false;
    double angle = 0;
    long num_swarms = boids_get_num_swarms(x);

    // custom origin for rotation
    if (args->l_size >= 3) {
        long type = hatom_gettype(&args->l_head->l_next->l_next->l_hatom);
        if (type == H_LLLL) {
            t_llll *pt_ll = hatom_getllll(&args->l_head->l_next->l_next->l_hatom);
            center = llll_to_pt(pt_ll);
            if (pt_ll->l_size >= 3 && hatom_gettype(&pt_ll->l_head->l_next->l_next->l_next->l_hatom) == H_SYM &&
                hatom_getsym(&args->l_head->l_next->l_next->l_next->l_hatom) == gensym("barycenter"))
                center_is_wr_to_baricenter = true;
        } else if (type == H_SYM && hatom_getsym(&args->l_head->l_next->l_next->l_hatom) == gensym("barycenter")) {
            center_is_wr_to_baricenter = true;
        }
        center_is_user_specified = true;
    }
    
    if (args->l_size >= 2) {
        // rotation angle
        angle = hatom_to_angle_in_rad(&args->l_head->l_next->l_hatom);
        
        // which shapes do we want to rotate?
        if (hatom_gettype(&args->l_head->l_hatom) != H_LONG) {
            for (long s = 0; s < num_swarms; s++)
                swarm_rotate(x, &x->swarm[s], angle, center_is_wr_to_baricenter ? NULL : &center);
        } else {
            long idx = hatom_getlong(&args->l_head->l_hatom);
            if (idx <= 0) {
                for (long s = 0; s < num_swarms; s++)
                    swarm_rotate(x, &x->swarm[s], angle, center_is_wr_to_baricenter ? NULL : &center);
            } else if (idx > 0 && idx <= num_swarms)
                swarm_rotate(x, &x->swarm[idx-1], angle, (center_is_wr_to_baricenter || !center_is_user_specified) ? NULL : &center);
        }
    }
    
    dadaobj_mutex_unlock(dadaobj_cast(x));
    boids_iar(x);
}

void boids_move(t_boids *x, t_llll *args)
{
    dadaobj_mutex_lock(dadaobj_cast(x));
    boids_undo_step_push(x, gensym("Move"));

    t_pt vector = build_pt(0, 0);
    long num_swarms = boids_get_num_swarms(x);
    
    // vector for moving
    if (args->l_size >= 2 && hatom_gettype(&args->l_head->l_next->l_hatom) == H_LLLL)
        vector = llll_to_pt(hatom_getllll(&args->l_head->l_next->l_hatom));
    
    if (args->l_size >= 1) {
        // which shapes do we want to move?
        if (hatom_gettype(&args->l_head->l_hatom) != H_LONG) {
            for (long s = 0; s < num_swarms; s++)
                swarm_move_delta(x, &x->swarm[s], vector);
        } else {
            long idx = hatom_getlong(&args->l_head->l_hatom);
            if (idx <= 0) {
                for (long s = 0; s < num_swarms; s++)
                    swarm_move_delta(x, &x->swarm[s], vector);
            } else if (idx > 0 && idx <= num_swarms)
                swarm_move_delta(x, &x->swarm[idx-1], vector);
        }
    }

    dadaobj_mutex_unlock(dadaobj_cast(x));
    boids_iar(x);
}



void boids_scale(t_boids *x, t_llll *args)
{
    dadaobj_mutex_lock(dadaobj_cast(x));
    boids_undo_step_push(x, gensym("Scale"));

    double factor_x = 1., factor_y = 1.;
    t_pt center = build_pt(0, 0);
    char center_is_user_specified = false;
    char center_is_wr_to_baricenter = false;
    long num_swarms = boids_get_num_swarms(x);

    
    // custom origin for scaling
    if (args->l_size >= 3) {
        long type = hatom_gettype(&args->l_head->l_next->l_next->l_hatom);
        if (type == H_LLLL) {
            t_llll *pt_ll = hatom_getllll(&args->l_head->l_next->l_next->l_hatom);
            center = llll_to_pt(pt_ll);
            if (pt_ll->l_size >= 3 && hatom_gettype(&pt_ll->l_head->l_next->l_next->l_next->l_hatom) == H_SYM &&
                hatom_getsym(&args->l_head->l_next->l_next->l_next->l_hatom) == gensym("barycenter"))
                center_is_wr_to_baricenter = true;
        } else if (type == H_SYM && hatom_getsym(&args->l_head->l_next->l_next->l_hatom) == gensym("barycenter")) {
            center_is_wr_to_baricenter = true;
        }
        center_is_user_specified = true;
    }
				
    // custom origin for rotation
    if (args->l_size >= 2) {
        if (hatom_gettype(&args->l_head->l_next->l_hatom) == H_LLLL) {
            t_llll *ll = hatom_getllll(&args->l_head->l_next->l_hatom);
            if (ll && ll->l_depth == 1 && ll->l_size >= 2) {
                if (is_hatom_number(&ll->l_head->l_hatom))
                    factor_x = hatom_getdouble(&ll->l_head->l_hatom);
                if (is_hatom_number(&ll->l_head->l_next->l_hatom))
                    factor_y = hatom_getdouble(&ll->l_head->l_next->l_hatom);
            }
        } else if (is_hatom_number(&args->l_head->l_next->l_hatom)) {
            factor_x = factor_y = hatom_getdouble(&args->l_head->l_next->l_hatom);
        }
    }
    
    if (args->l_size >= 1) {
        // which swarms do we want to scale?
        if (hatom_gettype(&args->l_head->l_hatom) != H_LONG) {
            for (long s = 0; s < num_swarms; s++)
                swarm_scale(x, &x->swarm[s], factor_x, factor_y, center_is_wr_to_baricenter ? NULL : &center);
        } else {
            long idx = hatom_getlong(&args->l_head->l_hatom);
            if (idx <= 0) {
                for (long s = 0; s < num_swarms; s++)
                    swarm_scale(x, &x->swarm[s], factor_x, factor_y, center_is_wr_to_baricenter ? NULL : &center);
            } else if (idx > 0 && idx <= num_swarms) {
                swarm_scale(x, &x->swarm[idx - 1], factor_x, factor_y, (center_is_wr_to_baricenter || !center_is_user_specified) ? NULL : &center);
            }
        }
    }

    dadaobj_mutex_unlock(dadaobj_cast(x));
    boids_iar(x);
}




void boids_anything(t_boids *x, t_symbol *msg, long ac, t_atom *av)
{
	dadaobj_anything(dadaobj_cast(x), msg, ac, av);

	t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_UI, msg, ac, av, LLLL_PARSE_CLONE);
	if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
		t_symbol *router = hatom_getsym(&parsed->l_head->l_hatom);
		llll_behead(parsed);
		
        if (dadaobj_anything_handle_domain_or_range(dadaobj_cast(x), router, parsed)) {
            // nothing to do!
        } else if (router == gensym("autozoom")) {
            dadaobj_cast(x)->m_zoom.must_autozoom = true;
            boids_iar(x);
        } else if (router == gensym("follow")) {
            x->follow_swarm = 0;
            t_llllelem *elem;
            for (elem = parsed->l_head; elem; elem = elem->l_next) {
                if (hatom_gettype(&elem->l_hatom) == H_LONG){
                    long l = hatom_getlong(&elem->l_hatom);
                    if (l > 0 && l < DADA_BOIDS_MAX_SWARMS)
                        x->follow_swarm |= (1 << (l - 1));
                } else if (hatom_gettype(&elem->l_hatom) == H_SYM && hatom_getsym(&elem->l_hatom) == _sym_all) {
                    x->follow_swarm = (t_uint64)-1;
                }
            }
        } else if (router == gensym("setstoredstate") || router == gensym("boids")) {
			boids_undo_step_push(x, gensym("Set State"));
			boids_set_state(x, parsed);
        } else if (router == _sym_dump) {
            boids_dump(x, true, true);
        } else if (router == gensym("addswarms") || router == gensym("addswarm")) {
            boids_undo_step_push_swarms(x, gensym("Add Swarms"));
            boids_add_swarms(x, parsed);
        } else if (router == gensym("deleteswarms") || router == gensym("deleteswarms")) {
            boids_undo_step_push_swarms(x, gensym("Delete Swarms"));
            boids_delete_swarms(x, parsed);
        } else if (router == gensym("swarm")) {
            long idx = 0;
            long num_swarms = dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_SWARM);;
            boids_undo_step_push_swarms(x, gensym("Change Swarm"));
            if (parsed->l_size >= 1 && hatom_gettype(&parsed->l_head->l_hatom) == H_LONG) {
                idx = hatom_getlong(&parsed->l_head->l_hatom);
                llll_behead(parsed);
            }
            if (idx > 0 && idx <= num_swarms) {
                boids_change_swarm(x, idx - 1, parsed);
                boids_iar(x);
            }
            
        } else if (router == gensym("rotate")) {
            boids_rotate(x, parsed);
        } else if (router == gensym("move")) {
            boids_move(x, parsed);
        }else if (router == gensym("scale")) {
            boids_scale(x, parsed);

        } else if (router == gensym("addrule")) {
            boids_undo_step_push_rules(x, gensym("Add Rule"));
            boids_add_single_rule(x, parsed, parsed->l_head ? hatom_getsym(&parsed->l_head->l_hatom) : NULL, parsed->l_tail ? hatom_getsym(&parsed->l_tail->l_hatom) : NULL);

        } else if (router == gensym("deleterule")) {
            boids_undo_step_push_rules(x, gensym("Delete Rule"));
            if (parsed->l_size >= 1) {
                t_symbol *rule_name = hatom_getsym(&parsed->l_head->l_hatom);
                if (rule_name) {
                    boids_delete_rule_prototype(x, rule_name);
                }
            }
        } else if (router == gensym("changeruleparams")) {
            long swarm_id = 0;
            t_symbol *rule_name = _llllobj_sym_none;
            if (parsed->l_head && is_hatom_number(&parsed->l_head->l_hatom)) {
                swarm_id = hatom_getlong(&parsed->l_head->l_hatom) - 1;
                llll_behead(parsed);
            } else if (parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
                swarm_id = boids_swarm_name_to_idx(x, hatom_getsym(&parsed->l_head->l_hatom));
                llll_behead(parsed);
            }
            if (parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
                rule_name = hatom_getsym(&parsed->l_head->l_hatom);
                llll_behead(parsed);
            }
            boids_undo_step_push_swarms(x, gensym("Change Swarm Rule Parameters"));
            boids_change_rule_params(x, swarm_id, rule_name, parsed);
            if (x->show_ruleparams)
                boids_iar(x);
        } else if (router == gensym("clear")) {
            boids_undo_step_push(x, gensym("Clear"));
            boids_clear(x, parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("rules")), parsed->l_size == 0 || is_symbol_in_llll_first_level(parsed, gensym("swarms")));
            boids_iar(x);
        }
		
	} else if (parsed) {
		boids_undo_step_push_swarms(x, gensym("Set Swarms"));
		boids_set_state(x, parsed);
    }
	llll_free(parsed);
}

/*

long coord_to_card(t_boids *x, t_pt coord)
{
	long i;
	long num_cards = dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_CARD);
	for (i = num_cards - 1; i >= 0; i--)
		if (is_pt_in_rectangle_extended(coord, dadaitem_card_get_rect(dadaobj_cast(x), &x->cards[i])))
			return i;
	return -1;
}

long pixel_to_card(t_boids *x, t_pt pt, t_object *view, t_pt *coordinates)
{
	t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), view, pt);
	if (coordinates)
		*coordinates = coord;
	return coord_to_card(x, coord);
}

t_dadaitem_identifier pixel_to_element(t_boids *x, t_pt pt, t_object *view, t_pt *coordinates)
{
	t_dadaitem_identifier result;
	long idx = -1;
	result.type = DADAITEM_TYPE_NONE;
	result.flag = 0;
	result.idx = -1;
	
	if ((idx = pixel_to_card(x, pt, view, coordinates)) >= 0) {
		result.type = DADAITEM_TYPE_CARD;
		result.idx = idx;
	}
	
	return result;
}

*/

//// GRAPHIC DRAWING


void get_ruleparam_text(t_boids *x, t_boids_swarm *sw, long i, long j, long k, char *buf, long buf_size)
{
    buf[0] = 0;
    if (x->show_ruleparam_names && sw->rule_ref[j].name && sw->rule_ref[j].param[k].r_name) {
        if (x->show_names) {
            if (sw->name)
                snprintf_zero(buf, buf_size, "%s\n%s: %s", sw->name->s_name, sw->rule_ref[j].name->s_name, sw->rule_ref[j].param[k].r_name->s_name);
            else
                snprintf_zero(buf, buf_size, "swarm %ld\n%s: %s", i+1, sw->rule_ref[j].name->s_name, sw->rule_ref[j].param[k].r_name->s_name);
        } else
            snprintf_zero(buf, buf_size, "%s: %s", sw->rule_ref[j].name->s_name, sw->rule_ref[j].param[k].r_name->s_name);
    }
}

void boids_paint(t_boids *x, t_object *view)
{
	t_rect rect;
    t_dadaobj *r_ob = dadaobj_cast(x);
	t_pt center = get_center_pix(r_ob, view, &rect);
	long i, j;
    
    
    if (dadaobj_cast(x)->m_zoom.must_autozoom) {
        boids_autozoom(x, view, &rect);
        dadaobj_cast(x)->m_zoom.must_autozoom = false;
    }
    
	t_jgraphics *g = (t_jgraphics*) patcherview_get_jgraphics(view);
    double zoom = r_ob->m_zoom.zoom.x;
	
    
	t_jfont *jf = jfont_create_debug(jbox_get_fontname((t_object *)x)->s_name, (t_jgraphics_font_slant)jbox_get_font_slant((t_object *)x), (t_jgraphics_font_weight)jbox_get_font_weight((t_object *)x), jbox_get_fontsize((t_object *)x));

    dadaobj_paint_background(dadaobj_cast(x), g, &rect);

    jgraphics_set_source_rgba(g, 0, 0, 0, 1); // alpha = 1;
    
    dadaobj_mutex_lock(dadaobj_cast(x));

    dadaobj_paint_grid(dadaobj_cast(x), view, rect, center);

    // paint swarms
    const double PAD = 20;
    t_rect rect_00_pad = build_rect(-PAD, -PAD, rect.width + 2*PAD, rect.height + 2*PAD);
    long num_swarm = dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_SWARM);
    for (i = 0; i < num_swarm; i++) {
        // paint swarm
        t_boids_swarm *sw = (t_boids_swarm *)dadaitem_class_get_nth_item(r_ob, dadaitem_class_get_id(&r_ob->m_classes, DADAITEM_TYPE_SWARM), i);

        // stuff for positioning the name later
        t_pt topmost = build_pt(0, 0);
        char topmost_defined = false;
        double min_x = rect.width, max_x = 0;
        double min_y = rect.height, max_y = 0;
        char any_in_rect = false;
        t_jrgba color = sw->color;

        for (j = 0; j < sw->num_boids; j++) {
            t_pt pt = coord_to_pix(r_ob, center, sw->coord[j].pt);
            if (is_pt_in_rectangle(pt, rect_00_pad)) {
                any_in_rect = true;
                // stuff for positioning the name later
                if (pt.x < min_x) min_x = pt.x;
                if (pt.x > max_x) max_x = pt.x;
                if (pt.y < min_y) min_y = pt.y;
                if (pt.y > max_y) max_y = pt.y;
                if (!topmost_defined || pt.y < topmost.y) {
                    topmost_defined = true;
                    topmost = pt;
                }
                switch (x->show_intensity) {
                    case 1:
                    {
                        double temp = 1. - ((sw->coord[j].intensity - 0.)/(sw->max_intensity - 0.));
                        //rescaling the temp
                        temp = temp * 0.8;
                        color.red = (1. - temp) * color.red + temp;
                        color.blue = (1. - temp) * color.blue + temp;
                        color.green = (1. - temp) * color.green + temp;
                    }
                        break;

                    case 2:
                        color = double_to_color(sw->coord[j].intensity, 0, sw->max_intensity, false);
                        break;
                        
                    case 3:
                    {
                        double factor = ((sw->coord[j].intensity - 0.)/(sw->max_intensity - 0.));
                        color.alpha = (0.7 * factor + 0.3) * color.alpha;
                    }
                        break;

                    default:
                        break;
                }
                
                // actually paint circle
//                post("%ld --- x, y: %.2f, %.2f", j, pt.x, pt.y);
                paint_circle(g, color, color, pt.x, pt.y, 2, 1);
                
                if (x->show_speed) {
                    if (isnan(sw->speed[j].pt.x) || isnan(sw->speed[j].pt.y)) {
                        // nothing to paint, speed is NaN!
                    } else {
                        double velx = zoom * sw->speed[j].pt.x / 4;
                        double vely = - zoom * sw->speed[j].pt.y / 4;
                        double arrow_size = 5;
                        double speed_val = pt_norm(sw->speed[j].pt);
                        if (speed_val < 1)
                            arrow_size *= speed_val;
                        paint_arrow(g, color, pt.x, pt.y, pt.x + velx, pt.y + vely, 1, arrow_size, arrow_size);
                    }
                }
            }
        }
        
        char hovered = (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_SWARM && x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx == i);
        char inactive = (x->swarm[i].r_it.flags & D_INACTIVE);
        char solo = (x->swarm[i].r_it.flags & D_SOLO);
        char should_not_be_played = (!(dadaitem_should_be_played(dadaobj_cast(x), (t_dadaitem *)&x->swarm[i])));
        
        if (hovered | inactive | solo | should_not_be_played) {
            t_pt coord[DADA_BOIDS_MAX_PARTICLES_PER_SWARM];
            for (j = 0; j < sw->num_boids; j++)
                coord[j] = sw->coord[j].pt;
            
            t_polygon *p = get_convex_hull(sw->num_boids, coord);

            if (hovered) {
                t_jrgba fillcolor = color;
                fillcolor.alpha *= 0.2;
                dadaobj_paint_polygon(dadaobj_cast(x), center, g, p, &color, &fillcolor, 1.);
            }
            
            if (inactive) {
                t_jrgba fillcolor = DADA_COLOR_INACTIVE;
                dadaobj_paint_polygon(dadaobj_cast(x), center, g, p, NULL, &fillcolor, 1.);
            }

            if (solo) {
                dadaobj_paint_dashed_polygon_contour(dadaobj_cast(x), center, g, p, &color, 2., 2.);
            }
            
            if (should_not_be_played) {
                t_jrgba color = (x->swarm[i].r_it.flags & D_MUTE) ? x->swarm[i].color : change_alpha(x->swarm[i].color, 0.4);
                paint_cross(g, &color, build_pt((min_x + max_x)/2., (min_y + max_y)/2.), MIN(max_x - min_x, max_y - min_y)/2., 1);
            }

            polygon_free(p);
        }
        
        if (x->show_names && sw->name && sw->name->s_name[0] && min_x <= max_x) {
            double text_width, text_height;
            jfont_text_measure(jf, sw->name->s_name, &text_width, &text_height);
            write_text_simple(g, jf, sw->color, sw->name->s_name, (min_x + max_x)/2. - text_width/2., topmost.y - text_height - 2, rect.width, rect.height);
        }
        
        // painting rule params, if any
        if (x->show_ruleparams) {
            char buf[2000];
            for (j = 0; j < sw->num_rule_refs; j++) {
                long k;
                t_jrgba color = x->use_separate_ruleparams_color ? x->ruleparams_color : sw->color;
                for (k = 0; k < sw->rule_ref[j].num_params; k++) {
                    switch (sw->rule_ref[j].param[k].r_display) {
                        case DADA_BOIDS_RULE_PARAM_DISPLAY_PT:
                        {
                            t_pt pix = coord_to_pix(dadaobj_cast(x), center, sw->rule_ref[j].param[k].r_param.w_pt);
                            paint_circle_filled(g, color, pix.x, pix.y, 2);
                            if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_RULEPARAM && x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx == i && x->b_ob.d_ob.m_interface.mousemove_item_identifier.secondary_idx == j && x->b_ob.d_ob.m_interface.mousemove_item_identifier.tertiary_idx == k)
                                paint_circle_stroken(g, color, pix.x, pix.y, 4, 1);
                            get_ruleparam_text(x, sw, i, j, k, buf, 2000);
                            if (buf[0])
                                write_text(g, jf, color, buf, pix.x + 2, pix.y + 2, 200, 200, JGRAPHICS_TEXT_JUSTIFICATION_TOPLEFT, false, true);
                        }
                            break;
                            
                        case DADA_BOIDS_RULE_PARAM_DISPLAY_VECTOR:
                        {
                            t_pt pix = coord_to_pix(dadaobj_cast(x), center, sw->rule_ref[j].param[k].r_param.w_pt);
                            paint_arrow(g, color, center.x, center.y, pix.x, pix.y, 1, 4, 4);
                            if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_RULEPARAM && x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx == i && x->b_ob.d_ob.m_interface.mousemove_item_identifier.secondary_idx == j && x->b_ob.d_ob.m_interface.mousemove_item_identifier.tertiary_idx == k)
                                paint_circle_stroken(g, color, pix.x, pix.y, 4, 1);
                            get_ruleparam_text(x, sw, i, j, k, buf, 2000);
                            if (buf[0])
                                write_text(g, jf, color, buf, pix.x + 2, pix.y + 2, 200, 200, JGRAPHICS_TEXT_JUSTIFICATION_TOPLEFT, false, true);
                        }
                            break;
                            
                        case DADA_BOIDS_RULE_PARAM_DISPLAY_VLINE:
                        {
                            double xpix = coord_to_pix(dadaobj_cast(x), center, build_pt(sw->rule_ref[j].param[k].r_param.w_double, 0)).x;
                            if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_RULEPARAM && x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx == i && x->b_ob.d_ob.m_interface.mousemove_item_identifier.secondary_idx == j && x->b_ob.d_ob.m_interface.mousemove_item_identifier.tertiary_idx == k)
                                paint_line(g, color, xpix, 0, xpix, rect.height, 0.5);
                            paint_dashed_y_line(g, color, xpix, 0, rect.height, 1, 4);
                            get_ruleparam_text(x, sw, i, j, k, buf, 2000);
                            if (buf[0])
                                write_text(g, jf, color, buf, xpix + 2, 2, 200, 200, JGRAPHICS_TEXT_JUSTIFICATION_TOPLEFT, false, true);
                        }
                            break;
                            
                        case DADA_BOIDS_RULE_PARAM_DISPLAY_HLINE:
                        {
                            double ypix = coord_to_pix(dadaobj_cast(x), center, build_pt(0, sw->rule_ref[j].param[k].r_param.w_double)).y;
                            if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_RULEPARAM && x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx == i && x->b_ob.d_ob.m_interface.mousemove_item_identifier.secondary_idx == j && x->b_ob.d_ob.m_interface.mousemove_item_identifier.tertiary_idx == k)
                                paint_line(g, color, 0, ypix, rect.width, ypix, 0.5);
                            paint_dashed_x_line(g, color, 0, rect.width, ypix, 1, 4);
                            get_ruleparam_text(x, sw, i, j, k, buf, 2000);
                            if (buf[0])
                                write_text(g, jf, color, buf, 2, ypix + 2, 200, 200, JGRAPHICS_TEXT_JUSTIFICATION_TOPLEFT, false, true);
                        }
                            break;
                            
                        default:
                            break;
                    }
                }
            }
        }
    }
    
    dadaobj_mutex_unlock(dadaobj_cast(x));

	jfont_destroy_debug(jf);
	
    dadaobj_paint_border(dadaobj_cast(x), g, &rect);
}






///////// POPUP MENU FUNCTIONS



////////// INTERFACE FUNCTIONS

void boids_focusgained(t_boids *x, t_object *patcherview) {
	if (dadaobj_focusgained(dadaobj_cast(x), patcherview))
		return;
}

void boids_focuslost(t_boids *x, t_object *patcherview) {
	if (dadaobj_focuslost(dadaobj_cast(x), patcherview))
		return;
}

void send_mouseover_info(t_boids *x)
{
	t_llll *ll = llll_get();
	llll_appendsym(ll, gensym("hover"), 0, WHITENULL_llll);
	if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_SWARM) {
		llll_appendlong(ll, x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx + 1, 0, WHITENULL_llll);
		llll_appendllll(ll, boids_get_single_swarm(x, x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx), 0, WHITENULL_llll);
	} else {
		llll_appendsym(ll, _sym_none, 0, WHITENULL_llll);
	}
	llllobj_outlet_llll((t_object *)x, LLLL_OBJ_UI, 1, ll);
	llll_free(ll);
}


long coord_to_swarm(t_boids *x, t_pt coord, long *swarm_elem)
{
    long i, j;
    double thresh = (DADA_BOIDS_SWARM_SEL_THRESH/x->b_ob.d_ob.m_zoom.zoom.x)*(DADA_BOIDS_SWARM_SEL_THRESH/x->b_ob.d_ob.m_zoom.zoom.x);
    long num_swarms = dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, (e_dadaitem_types)DADAITEM_TYPE_SWARM);
    for (i = 0; i < num_swarms; i++) {
        t_dadaitem *item = dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&dadaobj_cast(x)->m_classes, DADAITEM_TYPE_SWARM), i);
        t_boids_swarm *sw = ((t_boids_swarm *)item);
        for (j = 0; j < sw->num_boids; j++)
            if (pt_pt_distance_squared(sw->coord[j].pt, coord) <= thresh) {
                if (swarm_elem)
                    *swarm_elem = j;
                return i;
            }
    }
    return -1;
}

long pixel_to_swarm(t_boids *x, t_pt pt, t_object *view, t_pt *coordinates, long *swarm_elem)
{
    t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), view, pt);
    if (coordinates)
        *coordinates = coord;
    return coord_to_swarm(x, coord, swarm_elem);
}

long coord_to_ruleparam(t_boids *x, t_pt coord, long *rule_idx, long *param_idx)
{
    long i, j, k;
    double thresh = (DADA_BOIDS_SWARM_SEL_THRESH/x->b_ob.d_ob.m_zoom.zoom.x);
    long num_swarms = dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, (e_dadaitem_types)DADAITEM_TYPE_SWARM);
    for (i = 0; i < num_swarms; i++) {
        t_dadaitem *item = dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&dadaobj_cast(x)->m_classes, DADAITEM_TYPE_SWARM), i);
        t_boids_swarm *sw = ((t_boids_swarm *)item);
        for (j = 0; j < sw->num_rule_refs; j++) {
            for (k = 0; k < sw->rule_ref[j].num_params; k++) {
                switch (sw->rule_ref[j].param[k].r_display) {
                    case DADA_BOIDS_RULE_PARAM_DISPLAY_VLINE:
                        if (fabs(coord.x - sw->rule_ref[j].param[k].r_param.w_double) < thresh) {
                            if (rule_idx) *rule_idx = j;
                            if (param_idx) *param_idx = k;
                            return i;
                        }
                        break;

                    case DADA_BOIDS_RULE_PARAM_DISPLAY_HLINE:
                        if (fabs(coord.y - sw->rule_ref[j].param[k].r_param.w_double) < thresh) {
                            if (rule_idx) *rule_idx = j;
                            if (param_idx) *param_idx = k;
                            return i;
                        }
                        break;

                    case DADA_BOIDS_RULE_PARAM_DISPLAY_PT:
                    case DADA_BOIDS_RULE_PARAM_DISPLAY_VECTOR:
                        if (pt_pt_distance_squared(coord, sw->rule_ref[j].param[k].r_param.w_pt) < thresh*thresh) {
                            if (rule_idx) *rule_idx = j;
                            if (param_idx) *param_idx = k;
                            return i;
                        }
                        break;

                    default:
                        break;
                }
            }
        }
    }
    return -1;
}

long pixel_to_ruleparam(t_boids *x, t_pt pt, t_object *view, t_pt *coordinates, long *rule_idx, long *param_idx)
{
    t_pt coord = pix_to_coord_from_view(dadaobj_cast(x), view, pt);
    if (coordinates)
        *coordinates = coord;
    return coord_to_ruleparam(x, coord, rule_idx, param_idx);
}


void boids_output_notification(t_boids *x, t_dadaitem_identifier *ident, t_symbol *sym)
{
    t_llll *ll = llll_get();
    llll_appendsym(ll, sym);
    
    switch (ident->type) {
        case DADAITEM_TYPE_SWARM:
            llll_appendsym(ll, gensym("swarm"));
            llll_appendlong(ll, ident->idx + 1);
            if (dadaobj_cast(x)->m_interface.send_notifications == DADAOBJ_NOTIFY_VERBOSE)
                llll_appendllll(ll, boids_get_single_swarm(x, ident->idx));
            break;
            
        case DADAITEM_TYPE_RULEPARAM:
            llll_appendsym(ll, gensym("ruleparam"));
            llll_appendlong(ll, ident->idx + 1);
            llll_appendlong(ll, ident->secondary_idx + 1);
            llll_appendlong(ll, ident->tertiary_idx + 1);
            if (dadaobj_cast(x)->m_interface.send_notifications == DADAOBJ_NOTIFY_VERBOSE)
                llll_appendllll(ll, boids_get_single_rule(x, ident->secondary_idx));
            break;
            
        default:
            llll_appendsym(ll, _llllobj_sym_none);
            break;
    }
    
    dadaobj_send_notification_llll(dadaobj_cast(x), ll);
}


t_dadaitem_identifier pixel_to_element(t_boids *x, t_pt pt, t_object *view, t_pt *coordinates)
{
    t_dadaitem_identifier result;
    long idx = -1;
    result.type = DADAITEM_TYPE_NONE;
    result.flag = 0;
    result.idx = result.secondary_idx = result.tertiary_idx = -1;
    
    if ((idx = pixel_to_swarm(x, pt, view, coordinates, &result.secondary_idx)) >= 0) {
        result.type = DADAITEM_TYPE_SWARM;
        result.idx = idx;
    } else if ((idx = pixel_to_ruleparam(x, pt, view, coordinates, &result.secondary_idx, &result.tertiary_idx)) >= 0) {
         result.type = DADAITEM_TYPE_RULEPARAM;
         result.idx = idx;
    }
    
    return result;
}


void boids_mousemove(t_boids *x, t_object *patcherview, t_pt pt, long modifiers)
{
    t_dadaitem_identifier old_ident = x->b_ob.d_ob.m_interface.mousemove_item_identifier;
	llll_format_modifiers(&modifiers, NULL);
	
	if (dadaobj_mousemove(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
	
	if (x->b_ob.d_ob.m_interface.allow_mouse_hover) {
		if (!x->b_ob.d_ob.m_interface.mouse_is_down) {
			x->b_ob.d_ob.m_interface.mousemove_item_identifier = pixel_to_element(x, pt, patcherview, NULL);
            
            if (!dadaitem_identifier_eq(old_ident, x->b_ob.d_ob.m_interface.mousemove_item_identifier))
                boids_output_notification(x, &x->b_ob.d_ob.m_interface.mousemove_item_identifier, gensym("hover"));
            
            jbox_redraw((t_jbox *)x);
		}
	} else {
		if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type != DADAITEM_TYPE_NONE) {
			x->b_ob.d_ob.m_interface.mousemove_item_identifier.type = DADAITEM_TYPE_NONE;
			dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
			jbox_redraw((t_jbox *)x);
		}
	}
	
	
	if (popup_menu_is_shown(dadaobj_cast(x))) {
        dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
    } else if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_SWARM) {
        switch (x->b_ob.d_ob.m_tools.curr_tool) {
            case DADA_TOOL_CHANGE_COLOR:
                dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_CHANGE_COLOR);
                break;
            case DADA_TOOL_SCALE:
                dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_SCALE);
                break;
            case DADA_TOOL_ROTATE:
                dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_ROTATION);
                break;
            default:
                if (modifiers == eCommandKey)
                    dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DELETE);
                else
                    dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DRAGGINGHAND);
                break;
        }
	} else if (x->b_ob.d_ob.m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_RULEPARAM) {
        dadaobj_mutex_lock(dadaobj_cast(x));
        long i = x->b_ob.d_ob.m_interface.mousemove_item_identifier.idx;
        long j = x->b_ob.d_ob.m_interface.mousemove_item_identifier.secondary_idx;
        long k = x->b_ob.d_ob.m_interface.mousemove_item_identifier.tertiary_idx;
        t_dadaitem *item = dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&dadaobj_cast(x)->m_classes, DADAITEM_TYPE_SWARM), i);
        t_boids_swarm *sw = (t_boids_swarm *)item;
        if (sw && j < sw->num_rule_refs && k < sw->rule_ref[j].num_params) {
            switch (sw->rule_ref[j].param[k].r_display) {
                case DADA_BOIDS_RULE_PARAM_DISPLAY_VLINE:
                    dadaobj_mutex_unlock(dadaobj_cast(x));
                    dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_RESIZE_LEFTRIGHT);
                    break;

                case DADA_BOIDS_RULE_PARAM_DISPLAY_HLINE:
                    dadaobj_mutex_unlock(dadaobj_cast(x));
                    dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_RESIZE_UPDOWN);
                    break;

                default:
                    dadaobj_mutex_unlock(dadaobj_cast(x));
                    dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_RESIZE_FOURWAY);
                    break;
            }
        } else {
            dadaobj_mutex_unlock(dadaobj_cast(x));
            dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_RESIZE_FOURWAY);
        }
	} else {
		dada_set_cursor(dadaobj_cast(x), patcherview, BACH_CURSOR_DEFAULT);
	}
}




void popup_delete_swarm(t_dadaobj *d_ob, t_symbol *label, const t_llll *address)
{
    t_boids *x = (t_boids *)d_ob->orig_obj;
    if (d_ob->m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_SWARM) {
        boids_undo_step_push_swarms(x, gensym("Delete Swarm"));
        boids_delete_swarm(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx);
        boids_iar(x);
    }
}


void popup_set_swarm_color(t_dadaobj *d_ob, t_symbol *label, const t_llll *address)
{
    t_boids *x = (t_boids *)d_ob->orig_obj;
    if (d_ob->m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_SWARM) {
        boids_undo_step_push_swarms(x, gensym("Change Swarm Color"));
        t_jrgba color = symbol_to_color(label);
        
        t_dadaitem *item = dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&dadaobj_cast(x)->m_classes, DADAITEM_TYPE_SWARM), x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx);
        t_boids_swarm *sw = (t_boids_swarm *)item;

        sw->color = color;
        boids_iar(x);
    }
}

void show_swarm_popup_menu(t_boids *x, t_object *patcherview, t_pt pt, long modifiers)
{
/*    // what will be checked
    t_llll *checked = llll_from_text_buf((char *)"0 0 0 (0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0) 0", false);
    char *checked_buf = NULL;
    long num_balls = dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_BALL);
    if (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type == DADAITEM_TYPE_BALL && x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx >= 0 && x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx < num_balls) {
        long channel = x->balls[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx].channel;
        if (channel >= 1 && channel <= 16) {
            t_llllelem *elem = llll_getindex(hatom_getllll(&checked->l_head->l_next->l_next->l_next->l_hatom), channel + 1, I_NON_NEGATIVE); // +1 is for the first MIDIchannel symbol
            if (elem)
                hatom_setlong(&elem->l_hatom, 1);
        }
    }
    llll_to_text_buf(checked, &checked_buf, 0, 0, 0, NULL);
    
    ezdisplay_popup_menu_for_dadaitem(dadaobj_cast(x), patcherview, (t_dadaitem *)&x->balls[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx], D_SOLO | D_MUTE | D_INACTIVE,
                                      (char *)"Delete separator ( Speed Direction 0° 45° 90° 145° 180° 225° 270° 315° ) ( MIDIchannel 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 ) ( Color Red Green Blue Yellow Orange Violet )",
                                      "0 0 0 0 0", checked_buf, "", "", "",
                                      (void *)popup_delete_ball, NULL, (void *)popup_set_ball_speed_direction, (void *)popup_set_ball_channel, (void *)popup_set_ball_color, WHITENULL);
    
    llll_free(checked);
    bach_freeptr(checked_buf);
    bounce_mousemove(x, patcherview, pt, modifiers); */

    long idx = x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx;
    if (idx >= 0 && idx < boids_get_num_swarms(x)) {
        ezdisplay_popup_menu_for_dadaitem(dadaobj_cast(x), patcherview, (t_dadaitem *)&x->swarm[x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx], D_SOLO | D_MUTE | D_INACTIVE,
                                          (char *)"Delete separator ( Color Red Green Blue Yellow Orange Violet )",
                                          "0 0 0", "", "", "", "",
                                          (void *)popup_delete_swarm, NULL, (void *)popup_set_swarm_color, WHITENULL);
        boids_mousemove(x, patcherview, pt, modifiers);
    }
}


void boids_ezaddswarm(t_boids *x, long size, t_pt center_coord, double height, double width, double speed)
{
    boids_undo_step_push_swarms(x, gensym("Add Swarm"));
    long new_idx = boids_get_num_swarms(x) + 1;
    t_jrgba new_color = long_to_color(new_idx);
    char params_buf[2048];
    snprintf_zero(params_buf, 2048, "( size %ld ) ( coord uniform %.2f %.2f %.2f %.2f ) ( speed %.2f ) ( intensity 1 ) ( intensityspeed 0 ) ( name swarm%ld ) ( color %.2f %.2f %.2f ) ( maxintensity 1 )", size, center_coord.x - width/2, center_coord.y - height/2, width, height, speed, new_idx, new_color.red, new_color.green, new_color.blue);
    
    t_llll *params_ll = llll_from_text_buf(params_buf, false);
    boids_add_single_swarm(x, params_ll);
    llll_free(params_ll);
}

void popup_new_swarm(t_dadaobj *d_ob, t_symbol *label, const t_llll *address)
{
    t_boids *x = (t_boids *)d_ob->orig_obj;
    long size = 100;
    if (label) {
        char *ptr;
        size = strtol(label->s_name, &ptr, 10);
    }
    
    boids_ezaddswarm(x, size, d_ob->m_interface.mousedown_coord, size, size, 2);
    
    dadaobj_send_changedbang(d_ob);
}

void show_background_popup_menu(t_boids *x, t_object *patcherview, t_pt pt, long modifiers)
{
    ezdisplay_popup_menu(dadaobj_cast(x), patcherview,
                         (char *)"( New Swarm 5 boids 10 boids 25 boids 50 boids 100 boids 250 boids 500 boids 1000 boids ) separator No Solo No Mute No Inactive",
                         "", "", "", "", "",
                         (void *)popup_new_swarm, NULL, (void *)popup_unset_flags_for_all_dadaitems_fn, (void *)popup_unset_flags_for_all_dadaitems_fn, (void *)popup_unset_flags_for_all_dadaitems_fn, WHITENULL);
}

void boids_mousedown(t_boids *x, t_object *patcherview, t_pt pt, long modifiers){
	
	if (dadaobj_mousedown(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
	
	x->b_ob.d_ob.m_interface.mousedown_item_identifier = pixel_to_element(x, pt, patcherview, &x->b_ob.d_ob.m_interface.mousedown_coord);
	
	if (modifiers & ePopupMenu) {
		
        switch (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type) {
            case DADAITEM_TYPE_SWARM:
                show_swarm_popup_menu(x, patcherview, pt, modifiers);
                break;
            case DADAITEM_TYPE_RULEPARAM:
                break;
            default: // background
                show_background_popup_menu(x, patcherview, pt, modifiers);
                break;
        }
		
	} else {

        boids_output_notification(x, &x->b_ob.d_ob.m_interface.mousedown_item_identifier, gensym("click"));


		llll_format_modifiers(&modifiers, NULL);
		switch (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type) {
			case DADAITEM_TYPE_SWARM:
				if (modifiers == eCommandKey) {
                    boids_undo_step_push_swarms(x, gensym("Delete Swarm"));
                    boids_delete_swarm(x, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx);
				}
				break;
				
			default:
				//				x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADAITEM_TYPE_NONE;
				//				x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx = 0;
				break;
		}
	}
	
	jbox_redraw((t_jbox *)x);
	
}

void boids_mouseup(t_boids *x, t_object *patcherview, t_pt pt, long modifiers){
	
	llll_format_modifiers(&modifiers, NULL);
	
	if (dadaobj_mouseup(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
	
	x->b_ob.d_ob.m_interface.mousedown_item_identifier.type = DADAITEM_TYPE_NONE;
	x->b_ob.d_ob.m_interface.mousedown_item_identifier.flag = 0;
}

void swarm_scale(t_boids *x, t_boids_swarm *sw, double factor_x, double factor_y, t_pt *scaling_center)
{
    long j;
    if (!sw)
        return;
    
    t_pt center = scaling_center ? *scaling_center : boids_get_coord_barycenter(sw->num_boids, sw->coord);
    for (j = 0; j < sw->num_boids; j++) {
        t_pt diff = pt_pt_diff(sw->coord[j].pt, center);
        sw->coord[j].pt = pt_pt_sum(center, build_pt(diff.x * factor_x, diff.y * factor_y));
    }
}

void swarm_rotate(t_boids *x, t_boids_swarm *sw, double angle, t_pt *rot_center)
{
    long j;
    double s = sin(angle);
    double c = cos(angle);
    
    if (!sw)
        return;
    
    t_pt center = rot_center ? *rot_center : boids_get_coord_barycenter(sw->num_boids, sw->coord);
    for (j = 0; j < sw->num_boids; j++) {
        t_pt diff = pt_pt_diff(sw->coord[j].pt, center);
        t_pt new_diff = build_pt(diff.x * c - diff.y * s, diff.x * s + diff.y * c);
        sw->coord[j].pt = pt_pt_sum(center, new_diff);
    }
}


void swarm_move_delta(t_boids *x, t_boids_swarm *sw, t_pt delta)
{
    long j;
    if (!sw)
        return;
    for (j = 0; j < sw->num_boids; j++) {
        sw->coord[j].pt = pt_pt_sum(sw->coord[j].pt, delta);
    }
}

void boids_mousedrag(t_boids *x, t_object *patcherview, t_pt pt, long modifiers){
	
	llll_format_modifiers(&modifiers, NULL);
	
	if (dadaobj_mousedrag(dadaobj_cast(x), patcherview, pt, modifiers)) {
		jbox_redraw((t_jbox *)x);
		return;
	}

	switch (x->b_ob.d_ob.m_interface.mousedown_item_identifier.type) {
        case DADAITEM_TYPE_SWARM:
        {
            switch (x->b_ob.d_ob.m_tools.curr_tool) {
                case DADA_TOOL_ROTATE:
                {
                    dadaobj_mutex_lock(dadaobj_cast(x));
                    boids_undo_step_push_swarms(x, gensym("Scale Swarm"));
                    t_dadaitem *item = dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&dadaobj_cast(x)->m_classes, DADAITEM_TYPE_SWARM), x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx);
                    t_boids_swarm *sw = (t_boids_swarm *)item;
                    swarm_rotate(x, sw, x->b_ob.d_ob.m_interface.mousedrag_delta_pix.y/DADA_BOIDS_ROTATION_INTERFACE_FACTOR, NULL);
                    dadaobj_mutex_unlock(dadaobj_cast(x));
                    dadaobj_send_changedbang(dadaobj_cast(x));
                    boids_iar(x);
                }
                    break;
                case DADA_TOOL_CHANGE_COLOR:
                {
                    dadaobj_mutex_lock(dadaobj_cast(x));
                    t_dadaitem *item = dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&dadaobj_cast(x)->m_classes, DADAITEM_TYPE_SWARM), x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx);
                    t_boids_swarm *sw = (t_boids_swarm *)item;
                    change_hue_and_lightness(&sw->color, x->b_ob.d_ob.m_interface.mousedrag_delta_pix.x/50, -x->b_ob.d_ob.m_interface.mousedrag_delta_pix.y/100, 0.05, 0.8);
                    dadaobj_mutex_unlock(dadaobj_cast(x));
                    dadaobj_send_changedbang(dadaobj_cast(x));
                    boids_iar(x);
                }
                    break;
                case DADA_TOOL_SCALE: // scale positions
                {
                    double scale_factor = pow(2, -x->b_ob.d_ob.m_interface.mousedrag_delta_pix.y/DADA_BOIDS_ROTATION_SCALE_FACTOR);
                    dadaobj_mutex_lock(dadaobj_cast(x));
                    boids_undo_step_push_swarms(x, gensym("Scale Swarm"));
                    t_dadaitem *item = dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&dadaobj_cast(x)->m_classes, DADAITEM_TYPE_SWARM), x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx);
                    t_boids_swarm *sw = (t_boids_swarm *)item;
                    swarm_scale(x, sw, scale_factor, scale_factor, NULL);
                    dadaobj_mutex_unlock(dadaobj_cast(x));
                    dadaobj_send_changedbang(dadaobj_cast(x));
                    boids_iar(x);
                }
                    break;
                default:
                    dadaobj_mutex_lock(dadaobj_cast(x));
                    boids_undo_step_push_swarms(x, gensym("Move Swarm"));
                    t_dadaitem *item = dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&dadaobj_cast(x)->m_classes, DADAITEM_TYPE_SWARM), x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx);
                    t_boids_swarm *sw = (t_boids_swarm *)item;
                    swarm_move_delta(x, sw, x->b_ob.d_ob.m_interface.mousedrag_delta_coord);
                    dadaobj_mutex_unlock(dadaobj_cast(x));
                    dadaobj_send_changedbang(dadaobj_cast(x));
                    boids_iar(x);
                    break;
            }
        }
            break;
            
        case DADAITEM_TYPE_RULEPARAM:
        {
            dadaobj_mutex_lock(dadaobj_cast(x));
            boids_undo_step_push_rules(x, gensym("Change Rule Parameter"));
            long i = x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx;
            long j = x->b_ob.d_ob.m_interface.mousedown_item_identifier.secondary_idx;
            long k = x->b_ob.d_ob.m_interface.mousedown_item_identifier.tertiary_idx;
            t_dadaitem *item = dadaitem_class_get_nth_item(dadaobj_cast(x), dadaitem_class_get_id(&dadaobj_cast(x)->m_classes, DADAITEM_TYPE_SWARM), i);
            t_boids_swarm *sw = (t_boids_swarm *)item;
            if (sw && j < sw->num_rule_refs && k < sw->rule_ref[j].num_params) {
                switch (sw->rule_ref[j].param[k].r_display) {
                    case DADA_BOIDS_RULE_PARAM_DISPLAY_VLINE:
                        sw->rule_ref[j].param[k].r_param.w_double += x->b_ob.d_ob.m_interface.mousedrag_delta_coord.x;
                        break;
                        
                    case DADA_BOIDS_RULE_PARAM_DISPLAY_HLINE:
                        sw->rule_ref[j].param[k].r_param.w_double += x->b_ob.d_ob.m_interface.mousedrag_delta_coord.y;
                        break;

                    case DADA_BOIDS_RULE_PARAM_DISPLAY_PT:
                    case DADA_BOIDS_RULE_PARAM_DISPLAY_VECTOR:
                        sw->rule_ref[j].param[k].r_param.w_pt = pt_pt_sum(sw->rule_ref[j].param[k].r_param.w_pt, x->b_ob.d_ob.m_interface.mousedrag_delta_coord);
                        break;

                    default:
                        break;
                }
            }
            dadaobj_mutex_unlock(dadaobj_cast(x));
            dadaobj_send_changedbang(dadaobj_cast(x));
            boids_iar(x);
        }
            break;
            
        default:
            break;
    }
/*		case DADAITEM_TYPE_CARD:
			switch (modifiers) {
				case eControlKey:
				{
					// change value
					t_dada_card *card = (t_dada_card *)dadaitem_from_type_and_idx(dadaobj_cast(x), DADAITEM_TYPE_CARD, x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx);
					t_pt delta_coord = delta_pix_to_delta_coord(dadaobj_cast(x), x->b_ob.d_ob.m_interface.mousedrag_delta_pix);
					double delta_val = delta_coord.y * (x->value_max - x->value_min) / card->icon_height;
					dadaitem_card_change_value_delta(dadaobj_cast(x), x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, delta_val, DIA_UNDO_POSTPROCESS_INTERFACE);
					card->value = CLAMP(card->value, x->value_min, x->value_max);
					jbox_redraw((t_jbox *)x);
				}
					break;
				case eAltKey:
					break;
				default:
					switch (x->b_ob.d_ob.m_tools.curr_tool) {
						default:
							t_pt delta_coord = delta_pix_to_delta_coord(dadaobj_cast(x), x->b_ob.d_ob.m_interface.mousedrag_delta_pix);
							dadaitem_card_move_delta(dadaobj_cast(x), x->b_ob.d_ob.m_interface.mousedown_item_identifier.idx, delta_coord, DIA_UNDO_POSTPROCESS_INTERFACE);
							jbox_redraw((t_jbox *)x);
							break;
					} 
					break;
			}
			break;
			
		default:
			break;
	} */
}



void boids_mousewheel(t_boids *x, t_object *view, t_pt pt, long modifiers, double x_inc, double y_inc){
	llll_format_modifiers(&modifiers, NULL);  
	
	if (dadaobj_mousewheel(dadaobj_cast(x), view, pt, modifiers, x_inc, y_inc)) {
		jbox_redraw((t_jbox *)x);
		return;
	}
}



long boids_keyup(t_boids *x, t_object *patcherview, long keycode, long modifiers, long textcharacter){
	
	llll_format_modifiers(&modifiers, &keycode);
	
	if (dadaobj_keyup(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
		return 1;
	
	return 0;
}

long boids_key(t_boids *x, t_object *patcherview, long keycode, long modifiers, long textcharacter)
{
	llll_format_modifiers(&modifiers, &keycode);
	
	if (dadaobj_key(dadaobj_cast(x), patcherview, keycode, modifiers, textcharacter))
		return 1;
	
	switch (keycode) {
        case JKEY_SPACEBAR:
            if (x->b_ob.d_ob.m_play.is_playing)
                boids_stop(x, NULL, 0, NULL);
            else
                boids_play(x, NULL, 0, NULL);
            return 1;
		case JKEY_ESC:
			jbox_redraw((t_jbox *)x);
			return 1;
        case JKEY_TAB:
        {
            t_rect rect;
            jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
            boids_autozoom(x, patcherview, &rect);
        }
        return 1;
		default:
			break;
	}
	
	return 0;
}


void boids_mouseenter(t_boids *x, t_object *patcherview, t_pt pt, long modifiers) 
{
	if (dadaobj_mouseenter(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
}

void boids_mouseleave(t_boids *x, t_object *patcherview, t_pt pt, long modifiers) 
{
	if (dadaobj_mouseleave(dadaobj_cast(x), patcherview, pt, modifiers))
		return;
}



//// UNDO

void boids_postprocess_undo(t_boids *x)
{
	jbox_redraw((t_jbox *)x);
}


void boids_undo_step_push_rules(t_boids *x, t_symbol *operation)
{
    undo_add_interface_step(dadaobj_cast(x), DADA_FUNC_v_oX, (method)boids_set_rules, NULL, DADA_FUNC_X_o, (method)boids_get_rules, NULL, DADA_UNDO_OP_MODIFICATION, operation);
}

void boids_undo_step_push_swarms(t_boids *x, t_symbol *operation)
{
	undo_add_interface_step(dadaobj_cast(x), DADA_FUNC_v_oX, (method)boids_set_swarms, NULL, DADA_FUNC_X_o, (method)boids_get_swarms, NULL, DADA_UNDO_OP_MODIFICATION, operation);
}

void boids_undo_step_push(t_boids *x, t_symbol *operation)
{
    undo_add_interface_step(dadaobj_cast(x), DADA_FUNC_v_oX, (method)boids_set_state, NULL, DADA_FUNC_X_o, (method)boids_get_state, NULL, DADA_UNDO_OP_MODIFICATION, operation);
}

//// SEQUENCING


/////////////// SEQUENCING SYSTEM

void boids_clock(t_boids *x, t_symbol *s)
{
    void *old = x->b_ob.d_ob.m_play.setclock->s_thing;
    t_object *c = 0;
    
    // the line below can be restated as:
    // if s is the empty symbol
    // or s->s_thing is zero
    // or s->s_thing is non-zero and a setclock object
    if (s && (s == gensym("") || ((c = (t_object *) s->s_thing) && zgetfn(c, gensym("unset"))))) {
        if (old)
            boids_stop(x, NULL, 0, NULL);
        x->b_ob.d_ob.m_play.setclock = s;
    }
}

void boids_play(t_boids *x, t_symbol *s, long argc, t_atom *argv)
{
    if (x->b_ob.d_ob.m_undo.undo_before_play)
        boids_undo_step_push_swarms(x, gensym("Play"));

    x->b_ob.d_ob.m_play.is_playing = true;
    setclock_fdelay(x->b_ob.d_ob.m_play.setclock->s_thing, x->b_ob.d_ob.m_play.m_clock, x->b_ob.d_ob.m_play.play_step_ms);
    jbox_redraw((t_jbox *)x);
    dadaobj_send_notification_sym(dadaobj_cast(x), _llllobj_sym_play);
}


void boids_stop(t_boids *x, t_symbol *s, long argc, t_atom *argv)
{
    setclock_unset(x->b_ob.d_ob.m_play.setclock->s_thing, x->b_ob.d_ob.m_play.m_clock);
    x->b_ob.d_ob.m_play.is_playing = false;
    jbox_redraw((t_jbox *)x);
    dadaobj_send_notification_sym(dadaobj_cast(x), _llllobj_sym_stop);
}

////// STANDARD BOIDS RULES


void boids_seqstep(t_boids *x)
{
    // compute new positions for each swarm, and for each particle inside the swarm
    long s, i, j, r;
    double delta_t = x->b_ob.d_ob.m_play.play_step_ms;
    long num_swarms = boids_get_num_swarms(x);
    
    for (s = 0; s < num_swarms; s++) {
        t_boids_swarm *sw = &x->swarm[s];
        
        if (sw->r_it.flags & D_INACTIVE)
            continue;
        
        long num_boids = sw->num_boids;

        // locally copying coord and speeds
        t_boids_coord	loc_coord[DADA_BOIDS_MAX_PARTICLES_PER_SWARM];
        t_boids_coord	loc_speed[DADA_BOIDS_MAX_PARTICLES_PER_SWARM];
        sysmem_copyptr(sw->coord, loc_coord, num_boids * sizeof(t_boids_coord));
        sysmem_copyptr(sw->speed, loc_speed, num_boids * sizeof(t_boids_coord));
        
        for (i = 0; i < num_boids; i++) {
            // iterate on defined rules
            for (r = 0; r < sw->num_rule_refs; r++) {
                long proto_idx = boids_ruleprototype_name_to_idx(x, sw->rule_ref[r].name); // to be optimized with an hash table
                if (proto_idx >= 0) {
                    t_boids_coord rule_res = (x->rule_prototypes[proto_idx].fun)(num_boids, loc_coord, loc_speed, i, sw->rule_ref[r].num_params, sw->rule_ref[r].param);
                    
                    if (x->rule_prototypes[proto_idx].output_position_is_absolute)
                        sw->coord[i].pt = pt_pt_sum(sw->coord[i].pt, pt_number_prod(pt_pt_diff(rule_res.pt, sw->coord[i].pt), sw->rule_ref[r].gain));
                    else
                        sw->speed[i].pt = pt_pt_sum(sw->speed[i].pt, pt_number_prod(rule_res.pt, sw->rule_ref[r].gain));
                    
                    if (x->rule_prototypes[proto_idx].output_intensity_is_absolute)
                        sw->coord[i].intensity = rule_res.intensity * sw->rule_ref[r].gain;
                    else
                        sw->speed[i].intensity = sw->speed[i].intensity + (rule_res.intensity - sw->speed[i].intensity) * sw->rule_ref[r].gain;
                }
            }
            
            // limit speed
            if (sw->max_speed > 0 && pt_norm(sw->speed[i].pt) > sw->max_speed)
                sw->speed[i].pt = pt_number_prod(pt_normalize(sw->speed[i].pt), sw->max_speed);

            // calculate new position and intensity
            double delta = delta_t/1000.;
            x->swarm[s].coord[i].pt = pt_pt_sum(x->swarm[s].coord[i].pt, pt_number_prod(x->swarm[s].speed[i].pt, delta));
            x->swarm[s].coord[i].intensity = x->swarm[s].coord[i].intensity + x->swarm[s].speed[i].intensity * delta;

            // limit intensity
            if (sw->max_intensity > 0 && sw->coord[i].intensity > sw->max_intensity)
                sw->coord[i].intensity = sw->max_intensity;
            if (sw->coord[i].intensity < 0)
                sw->coord[i].intensity = 0.;
            
        }
    }
    jbox_redraw((t_jbox *)x);
}

void boids_output_sequencing(t_boids *x)
{
    t_atom av[5];
    long s, i, num_swarms = boids_get_num_swarms(x);
    
    for (s = 0; s < num_swarms; s++) {
        t_boids_swarm *sw = &x->swarm[s];
        atom_setsym(av, sw->name);
        
        if (!dadaitem_should_be_played(dadaobj_cast(x), (t_dadaitem *)&x->swarm[s]))
            continue;
        
        for (i = 0; i < sw->num_boids; i++) {
            atom_setlong(av+1, i + 1);
            atom_setfloat(av+2, sw->coord[i].pt.x);
            atom_setfloat(av+3, sw->coord[i].pt.y);
            atom_setfloat(av+4, sw->coord[i].intensity);
            llllobj_outlet_anything((t_object *)x, LLLL_OBJ_UI, 2, _sym_list, 5, av);
        }
    }
}

void boids_bang(t_boids *x)
{
    systhread_mutex_lock(x->b_ob.d_ob.l_mutex);
    boids_seqstep(x);
    systhread_mutex_unlock(x->b_ob.d_ob.l_mutex);
    if (x->output_sequencing)
        boids_output_sequencing(x);
}

void boids_follow(t_boids *x)
{
    t_object *view = jpatcher_get_firstview((t_object *)gensym("#P")->s_thing);
    t_rect rect;
    jbox_get_rect_for_view((t_object *)x, view, &rect);
    
    long num_swarms = dadaitem_class_get_num_items(&x->b_ob.d_ob.m_classes, DADAITEM_TYPE_SWARM);
    if (num_swarms == 0)
        return;
    
    double rect_width = rect.width;
    double rect_height = rect.height;
    
    t_pt min = boids_get_coord_barycenter(x->swarm[0].num_boids, x->swarm[0].coord);
    t_pt max = min;
    
    long i, count = 0;
    t_pt global = build_pt(0, 0);
    for (i = 0; i < 63 && i < num_swarms; i++) {
        if (x->follow_swarm & (1 << i)) {
            t_pt this_coord = boids_get_coord_barycenter(x->swarm[i].num_boids, x->swarm[i].coord);
            global = pt_pt_sum(global, this_coord);
            if (this_coord.x < min.x) min.x = this_coord.x;
            if (this_coord.y < min.y) min.y = this_coord.y;
            if (this_coord.x > max.x) max.x = this_coord.x;
            if (this_coord.y > max.y) max.y = this_coord.y;
            count++;
        }
    }
    
    if (count > 0) {
        global = pt_number_prod(global, -1./count);
        
        if (count > 1) {
            t_pt screen_min, screen_max;
            dadaobj_getdomain(dadaobj_cast(x), view, &screen_min.x, &screen_max.x);
            dadaobj_getrange(dadaobj_cast(x), view, &screen_min.x, &screen_max.x);
            
            
            if (max.x == min.x) {
                max.x -= 0.5;
                min.x += 0.5;
            }
            if (max.y == min.y) {
                max.y -= 0.5;
                min.y += 0.5;
            }
            
            // adding pads
            max.x += (max.x - min.x) * 0.2;
            min.x -= (max.x - min.x) * 0.2;
            max.y += (max.y - min.y) * 0.2;
            min.y -= (max.y - min.y) * 0.2;
            
            
            double xzoom_perc = (rect_width/(max.x - min.x)) * 100. / x->b_ob.d_ob.m_zoom.zoom_static_additional.x;
            double yzoom_perc = (rect_height/(max.y - min.y)) * 100. / x->b_ob.d_ob.m_zoom.zoom_static_additional.y;
            double zoom_perc = MIN(xzoom_perc, yzoom_perc);
            if (zoom_perc < x->b_ob.d_ob.m_zoom.zoom_perc)
                dadaobj_setzoom(dadaobj_cast(x), build_pt(zoom_perc, zoom_perc));
        }
        dadaobj_setcenteroffset(dadaobj_cast(x), global);
    }
}


void boids_task(t_boids *x)
{	
    systhread_mutex_lock(x->b_ob.d_ob.l_mutex);
    boids_seqstep(x);
    if (x->follow_swarm)
        boids_follow(x);
    systhread_mutex_unlock(x->b_ob.d_ob.l_mutex);
    
    if (x->output_sequencing)
        boids_output_sequencing(x);
    
    setclock_fdelay(x->b_ob.d_ob.m_play.setclock->s_thing, x->b_ob.d_ob.m_play.m_clock, x->b_ob.d_ob.m_play.play_step_ms);
}




