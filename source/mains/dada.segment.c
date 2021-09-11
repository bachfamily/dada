/**
	@file
	dada.segment.c
	
	@name 
	dada.segment
	
	@realname 
	dada.segment

	@type
	object
	
	@module
	dada

	@author
	Daniele Ghisi
	
	@digest 
	Score segmentation 
	
	@description
	Segments a <o>bach.roll</o> or <o>bach.score</o> into chunks
	
	@discussion
	
	@category
	dada segmentation, dada corpus-based tools

	@keywords
	score, segment, chunk, grain, split 
	
	@seealso
	dada.match, dada.cartesian, dada.base, dada.analysis.centroid, dada.analysis.energy, dada.analysis.count, dada.analysis.spread
	
	@owner
	Daniele Ghisi
*/

#include "dada.commons.h"
#include "dada.notation.h"
#include "dada.windows.h"
#include "ext.h"
#include "ext_obex.h"


#define DADA_SEGMENT_MAX_FEATURES_CUSTOM 256
#define DADA_SEGMENT_MAX_MEASURE_PRESEGM_PATTERN 128

// Data Structures


// algorithms
typedef enum _dada_segmentation_algorithm 
{
	DADA_SEGMENTATION_ALGORITHM_EQUATION = 0,
	DADA_SEGMENTATION_ALGORITHM_MARKERS,
	DADA_SEGMENTATION_ALGORITHM_LABELS,
	DADA_SEGMENTATION_ALGORITHM_LAMBDA,
} e_dada_segmentation_algorithm;


typedef struct _segment {
	t_llllobj_object	d_obj;
	
	char				algorithm;
    char                voicewise;
    
	t_symbol			*segmentsize_as_sym;
	t_lexpr				*segmentsize_lexpr;

    t_symbol			*hopsize_as_sym;
    t_lexpr				*hopsize_lexpr;

	long				measure_segm_pattern_size;
	long				measure_segm_pattern[DADA_SEGMENT_MAX_MEASURE_PRESEGM_PATTERN];
    
    long                window_type;
    
    char                use_tempo_markers_for_segmentation;
    char                copy_tempi_marker;
	
	// Meta information to be output for each chunk
	char				feature_index;
    char				feature_voice;
	char				feature_onset;
	char				feature_duration;
	char				feature_measure;
	char				feature_pim;
	char				feature_phase;
	char				feature_symduration;
    char				feature_symonset;
	char				feature_objtype;
	char				feature_label;
	char				feature_tempo;
	char				feature_bpm;

	t_symbol			*features_custom[DADA_SEGMENT_MAX_FEATURES_CUSTOM];
	long				features_custom_num;
    
    char                lambda_mode;

	
	void				*n_proxy;
	long				n_in;
} t_segment;


// Prototypes
t_segment*		segment_new(t_symbol *s, short argc, t_atom *argv);
void			segment_free(t_segment *x);
void			segment_anything(t_segment *x, t_symbol *msg, long ac, t_atom *av);
void			segment_assist(t_segment *x, void *b, long m, long a, char *s);
void            segment_inletinfo(t_segment *x, void *b, long a, char *t);


// Accessors
t_max_err segment_setattr_segmentsize(t_segment *x, t_object *attr, long ac, t_atom *av);
t_max_err segment_setattr_hopsize(t_segment *x, t_object *attr, long ac, t_atom *av);
t_max_err segment_setattr_algorithm(t_segment *x, t_object *attr, long ac, t_atom *av);


// Globals and Statics
static t_class	*s_segment_class = NULL;
static t_symbol	*ps_event = NULL;

/**********************************************************************/
// Class Definition and Life Cycle

void C74_EXPORT ext_main(void *moduleRef)
{
	common_symbols_init();
	llllobj_common_symbols_init();

	if (dada_check_bach_version() || llllobj_test()) {
		dada_error_bachcheck();
		return;
	}
	
	t_class *c; 
	
	CLASS_NEW_CHECK_SIZE(c, "dada.segment", 
				  (method)segment_new,
				  (method)segment_free,
				  sizeof(t_segment),
				  (method)NULL,
				  A_GIMME,
				  0L);
	
	// @method llll @digest Function depends on inlet
	// @description Any <m>llll</m> coming in first inlet is considered the gathered syntax of a <o>bach.roll</o> or a <o>bach.score</o>, and 
	// will trigger the segmentation. Grains are then output from the first outlet along with their metadata (second outlet). <br />
	// Any llll in second inlet is considered as the result of a computation for the feature being output from the lambda outlet.
	class_addmethod(c, (method)segment_anything,			"anything",			A_GIMME, 0);
	class_addmethod(c, (method)segment_anything,			"list",             A_GIMME, 0);
	class_addmethod(c, (method)segment_assist,              "assist",           A_CANT, 0);
    class_addmethod(c, (method)segment_inletinfo,			"inletinfo",		A_CANT, 0);
	
    llllobj_class_add_out_attr(c, LLLL_OBJ_VANILLA);

	CLASS_STICKY_ATTR(c,"category",0,"Settings");
	
	CLASS_ATTR_CHAR(c,"algorithm",0, t_segment, algorithm);
	CLASS_ATTR_STYLE_LABEL(c,"algorithm",0,"enumindex","Algorithm");
	CLASS_ATTR_ENUMINDEX(c,"algorithm", 0, "Equation Markers Labels"); 
    CLASS_ATTR_ACCESSORS(c, "algorithm", (method)NULL, (method)segment_setattr_algorithm);
	CLASS_ATTR_BASIC(c, "algorithm", 0);
	// @description Sets the segmentation algorithm: <br />
	// - Equation: a fixed number or an equation is set as <m>segmentsize</m> attribute in order to calculate grain size.
	// For a <o>bach.roll</o> this equation should yield a millisecond duration of the grain, and could have the "onset" symbol as variable.
	// For a <o>bach.score</o> this equation should yield the symbolic duration of the grain, and can have as variables: "measurenum" (measure number),
	// "measuresymdur" (the overall measure symbolic duration), "division" (the measure division) or "beat" (the measure beat). For instance
	// <b>beat/2</b> will yield a segmentation each half beat. <br />
	// - Markers: each marker is identified as a splitting point. Currently works for <o>bach.roll</o> only. <br />
	// - Labels: each label family (collection of elements sharing the same label) is considered as a grain. Currently works for <o>bach.roll</o> only.

    CLASS_ATTR_CHAR(c,"voicewise",0, t_segment, voicewise);
    CLASS_ATTR_STYLE_LABEL(c,"voicewise",0,"onoff","Voicewise Segmentation");
    CLASS_ATTR_BASIC(c, "voicewise", 0);
    // @descriptions Toggles the ability to cut each voice in each grain (i.e. to perform the segmentation on each voice independently, and then collect all results).

    
    CLASS_ATTR_CHAR(c,"tempomarkersseg",0, t_segment, use_tempo_markers_for_segmentation);
    CLASS_ATTR_STYLE_LABEL(c,"tempomarkersseg",0,"onoff","Use Tempo Markers For Segmentation");
    // @descriptions Toggles the ability to also use tempo markers for marker-based segmentation (see <m>algorithm</m>). Default is off.
    
    
    CLASS_ATTR_CHAR(c,"copytempi",0, t_segment, copy_tempi_marker);
    CLASS_ATTR_STYLE_LABEL(c,"copytempi",0,"onoff","Copy Tempi Marker");
    // @descriptions Toggles the ability to copy tempi markers when a <o>bach.roll</o> is segmented (if any). Default is on.
    
    
	CLASS_ATTR_SYM(c, "segmentsize", 0, t_segment, segmentsize_as_sym);
	CLASS_ATTR_STYLE_LABEL(c,"segmentsize",0,"text","Segmentation Equation");
	CLASS_ATTR_ACCESSORS(c, "segmentsize", (method)NULL, (method)segment_setattr_segmentsize);
	CLASS_ATTR_BASIC(c, "segmentsize", 0);
	// @descriptions Sets the equation for the segment size (for Equation algorithm only).
    // Can include as variables: "onset","measurenum","measuresymdur","division","beat".
    // Use "none" to skip segmentation.

    CLASS_ATTR_SYM(c, "hopsize", 0, t_segment, hopsize_as_sym);
    CLASS_ATTR_STYLE_LABEL(c,"hopsize",0,"text","Hop Equation");
    CLASS_ATTR_ACCESSORS(c, "hopsize", (method)NULL, (method)segment_setattr_hopsize);
    // @descriptions Sets the equation for the hop size (for Equation algorithm and <o>bach.roll</o>only).
    // Can include as variables: "onset","measurenum","measuresymdur","division","beat".

    CLASS_ATTR_LONG(c, "wintype", 0, t_segment, window_type);
    CLASS_ATTR_STYLE_LABEL(c,"wintype",0,"enumindex","Velocity Window Type");
    CLASS_ATTR_ENUMINDEX(c,"wintype", 0, "None Rectangular Triangular Cosine Hanning Blackman");
    // @descriptions Sets the type of windowing to be applied on velocities (if any).

    
	CLASS_ATTR_LONG_VARSIZE(c, "presegment", 0, t_segment, measure_segm_pattern, measure_segm_pattern_size, DADA_SEGMENT_MAX_MEASURE_PRESEGM_PATTERN);
    CLASS_ATTR_STYLE_LABEL(c, "presegment", 0, "text", "Measure Pre-Segmentation Pattern");
	// @description Sets an integer pattern for preliminar measure segmentation (for <o>bach.score</o> only). Defaults to 1 measure.

	CLASS_STICKY_ATTR_CLEAR(c, "category");
    
    
    CLASS_STICKY_ATTR(c,"category",0,"Behavior");

    CLASS_ATTR_CHAR(c,"lambdamode",0, t_segment, lambda_mode);
    CLASS_ATTR_STYLE_LABEL(c,"lambdamode",0,"onoff","Separate Features In Lambda Loop");
    CLASS_ATTR_BASIC(c, "lambdamode", 0);
    // @descriptions Toggles the ability to prepend the feature name in the grain llll output from the lambda outlet, so that each feature can be handled
    // by a separate module. An answer (without any router) is expected in the lambda inlet features by routers in the lambda loop.
    // This attribute on by default. If it is turned off, then the grain llll is only output through the right outlet preceded by a generic "features"
    // symbol, and a single llll of the kind <b>[<m>featurename</m> <m>featurevalue</m>] [<m>featurename</m> <m>featurevalue</m>]...</b> is expected
    // in return. This is very convenient for optimization purposes.
    
    
    
    CLASS_STICKY_ATTR_CLEAR(c, "category");

    


	CLASS_STICKY_ATTR(c,"category",0,"Features");

	CLASS_ATTR_CHAR(c,"ftidx",0, t_segment, feature_index);
	CLASS_ATTR_STYLE_LABEL(c,"ftidx",0,"onoff","Add Index To Features");
	// @description Toggles the ability to add the grain index (tagged with the <m>idx</m> symbol) to the grain metadata.

    CLASS_ATTR_CHAR(c,"ftvoice",0, t_segment, feature_voice);
    CLASS_ATTR_STYLE_LABEL(c,"ftvoice",0,"onoff","Add Voice Number To Features");
    // @description Toggles the ability to add the voice number of the topmost voice of the grain (tagged with the <m>voice</m> symbol) to the grain metadata.

	CLASS_ATTR_CHAR(c,"ftonset",0, t_segment, feature_onset);
	CLASS_ATTR_STYLE_LABEL(c,"ftonset",0,"onoff","Add Onset To Features");
	// @description Toggles the ability to add the onset in milliseconds to the grain metadata (only for <o>bach.roll</o> grains).

	CLASS_ATTR_CHAR(c,"ftduration",0, t_segment, feature_duration);
	CLASS_ATTR_STYLE_LABEL(c,"ftduration",0,"onoff","Add Duration To Features");
	// @description Toggles the ability to add the duration in milliseconds to the grain metadata (only for <o>bach.roll</o> grains).

	CLASS_ATTR_CHAR(c,"ftmeasure",0, t_segment, feature_measure);
	CLASS_ATTR_STYLE_LABEL(c,"ftmeasure",0,"onoff","Add Measure Number To Features");
	// @description Toggles the ability to add the measure number to the grain metadata (only for <o>bach.score</o> grains).

	CLASS_ATTR_CHAR(c,"ftpim",0, t_segment, feature_pim);
	CLASS_ATTR_STYLE_LABEL(c,"ftpim",0,"onoff","Add Point In Measure To Features");
	// @description Toggles the ability to add the grain starting point inside its measure (as a rational value) to the grain metadata (only for <o>bach.score</o> grains).

	CLASS_ATTR_CHAR(c,"ftphase",0, t_segment, feature_phase);
	CLASS_ATTR_STYLE_LABEL(c,"ftphase",0,"onoff","Add Beat Phase To Features");
	// @description Toggles the ability to add the beat phase to the grain metadata (only for <o>bach.score</o> grains).
	// Beat phase will be 0. at the beginning of the measure, 1. exactly on the first beat, and so on.

	CLASS_ATTR_CHAR(c,"ftsymduration",0, t_segment, feature_symduration);
	CLASS_ATTR_STYLE_LABEL(c,"ftsymduration",0,"onoff","Add Symbolic Duration To Features");
	// @description Toggles the ability to add the grain symbolic duration to the grain metadata (only for <o>bach.score</o> grains).

    CLASS_ATTR_CHAR(c,"ftsymonset",0, t_segment, feature_symonset);
    CLASS_ATTR_STYLE_LABEL(c,"ftsymonset",0,"onoff","Add Symbolic Onset To Features");
    // @description Toggles the ability to add the grain symbolic onset inside its measure to the grain metadata (only for <o>bach.score</o> grains).

	CLASS_ATTR_CHAR(c,"fttempo",0, t_segment, feature_tempo);
	CLASS_ATTR_STYLE_LABEL(c,"fttempo",0,"onoff","Add Tempo To Features");
	// @description Toggles the ability to add the grain tempo to the grain metadata (only for <o>bach.score</o> grains).

	CLASS_ATTR_CHAR(c,"ftbpm",0, t_segment, feature_bpm);
	CLASS_ATTR_STYLE_LABEL(c,"ftbpm",0,"onoff","Add BPM To Features");
	// @description Toggles the ability to add the grain tempo (in BPM) to the grain metadata (both for <o>bach.score</o> grains and for <o>bach.roll</o> grains, via tempo markers, if any).
	
	
	CLASS_ATTR_CHAR(c,"fttype",0, t_segment, feature_objtype);
	CLASS_ATTR_STYLE_LABEL(c,"fttype",0,"onoff","Add Notation Object Type To Features");
	// @description Toggles the ability to add the notation object type to the grain metadata (either the "roll" symbol or the "score" symbol).

	CLASS_ATTR_CHAR(c,"ftlabel",0, t_segment, feature_label);
	CLASS_ATTR_STYLE_LABEL(c,"ftlabel",0,"onoff","Add Label To Features");
	// @description Toggles the ability to add the label tag to the grain metadata (only when a Marker or Label segmentation <m>algorithm</m> is used).

	
	CLASS_ATTR_SYM_VARSIZE(c, "ftcustom", 0, t_segment, features_custom, features_custom_num, DADA_SEGMENT_MAX_FEATURES_CUSTOM);
	CLASS_ATTR_STYLE_LABEL(c,"ftcustom",0,"text","Custom Features");
	// @description Sets the list of custom feature names, which should then be implemented in the lambda loop.

	CLASS_STICKY_ATTR_CLEAR(c, "category");

	class_register(CLASS_BOX, c);
	s_segment_class = c;
	ps_event = gensym("event");
    dadaobj_class_add_fileusage_method(c);

	return;
}


void segment_assist(t_segment *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { // @in 0 @type llll @digest The roll or score to be segmented, in gathered syntax
		if (a == 0)
			sprintf(s, "llll: Roll or Score to Be Segmented");
		else  // @in 0 @type anything/llll @digest Lambda inlet
			sprintf(s, "anything/llll: Lambda Inlet"); // @description @copy BACH_DOC_LAMBDA_INLET_CALCULATION
	} 
	else {	
		char *type = NULL;
		llllobj_get_llll_outlet_type_as_string((t_object *) x, LLLL_OBJ_VANILLA, a, &type);
		if (a == 0)	// @out 0 @type llll @digest Segmented rolls or scores in gathered syntax
			sprintf(s, "llll (%s): Grains from Segmentation", type); 			
		else if (a == 1)	// @out 1 @type llll @digest Metadata
			sprintf(s, "llll (%s): Grains Metadata", type); 			
		else 	// @out 2 @type llll @digest Lambda Outlet
			sprintf(s, "llll (%s): Lambda outlet", type); // @description @copy BACH_DOC_LAMBDA_OUTLET_CALCULATION			
	}
}


void segment_inletinfo(t_segment *x, void *b, long a, char *t)
{
    if (a)
        *t = 1;
}




t_segment* segment_new(t_symbol *s, short argc, t_atom *argv)
{
	t_segment* x;
	
	long true_ac = attr_args_offset(argc, argv);

	x = (t_segment*)object_alloc(s_segment_class);
	if (x) {
		x->algorithm = DADA_SEGMENTATION_ALGORITHM_EQUATION;
		x->segmentsize_lexpr = NULL;
        x->hopsize_lexpr = NULL;
		x->features_custom_num = 0;
		x->measure_segm_pattern_size = 0;
		x->measure_segm_pattern[0] = 1;
        x->lambda_mode = 1;
		
		object_attr_setsym(x, gensym("segmentsize"), gensym("none"));
        object_attr_setsym(x, gensym("hopsize"), gensym(""));
		
		llllobj_obj_setup((t_llllobj_object *)x, 2, "444");
		
        // @arg 0 @name segmentsize @optional 1 @type symbol @digest Segment Size Equation
        // @discussion See <m>segmentsize</m> attribute.
        if (true_ac >= 1) {
            char *buf = NULL;
            long size = 0;
            atom_gettext_debug(true_ac, argv, &size, &buf, OBEX_UTIL_ATOM_GETTEXT_SYM_NO_QUOTE);
            if (size && buf) {
                object_attr_setsym((t_object *)x, gensym("segmentsize"), gensym(buf));
                bach_freeptr(buf);
            }
        }
        
		attr_args_process(x, argc, argv);

		x->n_proxy = proxy_new_debug((t_object *) x, 1, &x->n_in);
	}
	return x;
}


void segment_free(t_segment *x)
{
	object_free_debug(x->n_proxy);
	if (x->segmentsize_lexpr)
		lexpr_free(x->segmentsize_lexpr);
    if (x->hopsize_lexpr)
        lexpr_free(x->hopsize_lexpr);
}


/**********************************************************************/
// Methods


void process_custom_features(t_segment *x, t_llll *features, t_llll *gs)
{
    long i;
    char lambda_mode = x->lambda_mode;
    if (lambda_mode) {
        for (i = 0; i < x->features_custom_num; i++) {
            t_llll *to_out = llll_get();
            llll_appendsym(to_out, gensym("feature"));
            llll_appendsym(to_out, x->features_custom[i]);
            llll_chain_clone(to_out, gs);
            llllobj_store_llll((t_object *) x, LLLL_OBJ_VANILLA, llll_get(), 1);
            llllobj_outlet_llll((t_object *)x, LLLL_OBJ_VANILLA, 2, to_out);
            llll_free(to_out);
            
            // retrieving data
            t_llll *lambda_ll = llllobj_get_store_contents((t_object *) x, LLLL_OBJ_VANILLA, 1, true);
            llll_prependsym(lambda_ll, x->features_custom[i]);
            llll_appendllll(features, lambda_ll);
        }
    } else {
        t_llll *to_out = llll_get();
        llll_appendsym(to_out, gensym("features"));
        llll_chain_clone(to_out, gs);
        llllobj_store_llll((t_object *) x, LLLL_OBJ_VANILLA, llll_get(), 1);
        llllobj_outlet_llll((t_object *)x, LLLL_OBJ_VANILLA, 2, to_out);
        llll_free(to_out);
        
        // retrieving data
        t_llll *lambda_ll = llllobj_get_store_contents((t_object *) x, LLLL_OBJ_VANILLA, 1, true);
        llll_chain(features, lambda_ll);
    }
}

void process_standard_features_roll(t_segment *x, t_llll *features, t_llll *gs, long index, double onset, long duration, t_symbol *label, long voicenum, double phase)
{
	if (x->feature_index) 
		llll_appendllll(features, symbol_and_long_to_llll(gensym("idx"), index), 0, WHITENULL_llll);
	
    if (x->feature_voice)
        llll_appendllll(features, symbol_and_long_to_llll(_llllobj_sym_voice, voicenum), 0, WHITENULL_llll);

    if (x->feature_onset)
		llll_appendllll(features, symbol_and_double_to_llll(_llllobj_sym_onset, onset), 0, WHITENULL_llll);
	
	if (x->feature_duration) 
		llll_appendllll(features, symbol_and_double_to_llll(_llllobj_sym_duration, duration), 0, WHITENULL_llll);
	
	if (x->feature_bpm) {
		t_tempo *tempo = dada_get_first_marker_tempo(gs);
		llll_appendllll(features, symbol_and_double_to_llll(gensym("bpm"), tempo ? rat2double(tempo->tempo_value) : 60.), 0, WHITENULL_llll);
		bach_freeptr(tempo);
	}
    
    if (x->feature_phase) {
        t_llll *ll = llll_get();
        llll_appendsym(ll, gensym("phase"), 0, WHITENULL_llll);
        llll_appenddouble(ll, phase, 0, WHITENULL_llll);
        llll_appendllll(features, ll, 0, WHITENULL_llll);
    }

	if (x->feature_label && label) {
		t_llll *ll = llll_get();
		llll_appendsym(ll, _llllobj_sym_label, 0, WHITENULL_llll);
		llll_appendsym(ll, label, 0, WHITENULL_llll);
		llll_appendllll(features, ll, 0, WHITENULL_llll);
	}
	
	if (x->feature_objtype) {
		t_llll *ll = llll_get();
		llll_appendsym(ll, _llllobj_sym_type, 0, WHITENULL_llll);
		llll_appendsym(ll, _llllobj_sym_roll, 0, WHITENULL_llll);
		llll_appendllll(features, ll, 0, WHITENULL_llll);
	}
}

// measure_num is 0-based, but 1-based at output
void process_standard_features_score(t_segment *x, t_llll *features, long index, long measure_num, t_rational division, t_tempo *tempo,
									 t_rational pim, t_rational phase, t_rational sym_dur, long voice_number)
{
	if (x->feature_index) 
		llll_appendllll(features, symbol_and_long_to_llll(gensym("idx"), index), 0, WHITENULL_llll); // can't use "index": Sqlite doesn't like that

    if (x->feature_voice)
        llll_appendllll(features, symbol_and_long_to_llll(gensym("voice"), voice_number), 0, WHITENULL_llll);
    
	if (x->feature_measure)
		llll_appendllll(features, symbol_and_long_to_llll(_llllobj_sym_measure, measure_num + 1), 0, WHITENULL_llll);

	if (x->feature_pim) {
		t_llll *ll = llll_get();
		llll_appendsym(ll, _llllobj_sym_pim, 0, WHITENULL_llll);
		llll_appenddouble(ll, rat2double(pim), 0, WHITENULL_llll);
		llll_appendllll(features, ll, 0, WHITENULL_llll);
	}

	if (x->feature_phase) {
		t_llll *ll = llll_get();
		llll_appendsym(ll, gensym("phase"), 0, WHITENULL_llll);
		llll_appenddouble(ll, rat2double(phase), 0, WHITENULL_llll);
		llll_appendllll(features, ll, 0, WHITENULL_llll);
	}	
	
	if (x->feature_symduration) {
		t_llll *ll = llll_get();
		llll_appendsym(ll, _llllobj_sym_symduration, 0, WHITENULL_llll);
		llll_appendrat(ll, sym_dur, 0, WHITENULL_llll);
		llll_appendllll(features, ll, 0, WHITENULL_llll);
	}	

    if (x->feature_symonset) {
        t_llll *ll = llll_get();
        llll_appendsym(ll, _llllobj_sym_symonset, 0, WHITENULL_llll);
        llll_appendrat(ll, pim, 0, WHITENULL_llll);
        llll_appendllll(features, ll, 0, WHITENULL_llll);
    }	

	if (x->feature_objtype) {
		t_llll *ll = llll_get();
		llll_appendsym(ll, _llllobj_sym_type, 0, WHITENULL_llll);
		llll_appendsym(ll, _llllobj_sym_score, 0, WHITENULL_llll);
		llll_appendllll(features, ll, 0, WHITENULL_llll);
	}

	if (x->feature_bpm) {
		t_llll *ll = llll_get();
		llll_appendsym(ll, gensym("bpm"), 0, WHITENULL_llll);
		llll_appenddouble(ll, tempo ? rat2double(rat_rat_prod(tempo->figure_tempo_value, rat_rat_div(tempo->tempo_figure, division))) : 60., 0, WHITENULL_llll);
		llll_appendllll(features, ll, 0, WHITENULL_llll);
	}	
	
	if (x->feature_tempo) {
		t_llll *ll = llll_get();
		llll_appendsym(ll, _llllobj_sym_tempo, 0, WHITENULL_llll);
		if (tempo) {
			t_llll *inner = llll_get();
			llll_appendrat(inner, tempo->tempo_figure, 0, WHITENULL_llll);
			llll_appendrat(inner, tempo->tempo_value, 0, WHITENULL_llll);
			llll_appendllll(ll, inner, 0, WHITENULL_llll);
		}
		llll_appendllll(features, ll, 0, WHITENULL_llll);
	}	
	
}


t_llll *segment_roll_standard(t_segment *x, t_llll *roll, t_llll **meta, long voice_number)
{
	if (!x->segmentsize_lexpr)  {
		object_error((t_object *)x, "No valid segment size expression introduced");
		return NULL;
	}
	
	t_hatom vars[6];
	long i = 1;
	double curr_onset = 0;
    char dont_segment = (x->segmentsize_as_sym == _llllobj_sym_empty_symbol || x->segmentsize_as_sym == _llllobj_sym_none);
    
	t_llll *temp = llll_clone(roll);
	t_llll *result = llll_get();
	double tot_length = dada_roll_get_length(roll);

	if (meta)
		*meta = llll_get();
	
	// computing this size
	while (curr_onset < tot_length && temp) {
        t_llll *right = NULL;
        t_llll *to_append = NULL;
        double this_duration = tot_length;
        double this_hop = this_duration;

        if (!dont_segment) {
            t_hatom *res = NULL;
            hatom_setdouble(vars, curr_onset);
            hatom_setlong(vars + 1, 0);
            hatom_setlong(vars + 2, 0);
            hatom_setlong(vars + 3, 0);
            hatom_setlong(vars + 4, 0);
            hatom_setlong(vars + 5, 0);

            // get duration
            res = lexpr_eval(x->segmentsize_lexpr, vars);
            if (!res)  {
                object_error((t_object *)x, "Can't compute segment size");
                return NULL;
            }
            this_duration = hatom_getdouble(res);
            bach_freeptr(res);
            
            // get hop
            this_hop = this_duration;
            if (x->hopsize_lexpr) {
                res = lexpr_eval(x->hopsize_lexpr, vars);
                
                if (!res)  {
                    object_error((t_object *)x, "Can't compute hop size, using segment size as hop size");
                    curr_onset += this_duration;
                } else {
                    this_hop = hatom_getdouble(res);
                }
                
                bach_freeptr(res);
            }
            
            if (x->hopsize_lexpr) { // could overlap!
                right = llll_clone(temp);
                dada_roll_shift(right, -this_hop);
                t_llll *freeme = dada_roll_split_preserve(temp, this_duration, false, false, x->copy_tempi_marker);
                to_append = temp;
                llll_free(freeme);
            } else { // faster standard non-overlap method
                right = dada_roll_split_preserve(temp, this_duration, false, false, x->copy_tempi_marker);
                dada_roll_shift(right, -this_duration);
                to_append = temp;
            }
        } else
            to_append = temp;
        
        if (x->window_type != DADA_WINDOW_NONE)
            dada_roll_apply_window_on_velocities(to_append, (e_dada_windows)x->window_type, &this_duration);
        
        llll_appendllll(result, to_append);
        
		// meta-information
		if (meta) {
			t_llll *this_meta = llll_get();

			process_standard_features_roll(x, this_meta, temp, i, curr_onset, this_duration, NULL, voice_number, 0);
			process_custom_features(x, this_meta, temp);
			
			llll_appendllll(*meta, this_meta, 0, WHITENULL_llll);
		}
		
        if (dont_segment)
            break;
        
        curr_onset += this_hop;
		
        temp = right;
		i++;
	}
	
	return result;
}



t_llll *segment_roll_markers(t_segment *x, t_llll *roll, t_llll **meta, long voice_number)
{
	t_llll *markers = dada_get_markers(roll);
	t_llll *durations = llll_get();
	t_llll *names = llll_get();
    
    if (!x->use_tempo_markers_for_segmentation)
        dada_markers_delete_tempo_markers(markers);

	double curr_onset = 0;
	t_llll *temp = llll_clone(roll);
	t_llll *result = llll_get();
	double tot_length = dada_roll_get_length(roll);
	
	// get durations
	t_llllelem *mk_elem;
	if (markers && markers->l_head) {
		double curr_marker_ms = hatom_getdouble(&markers->l_head->l_hatom.h_w.w_llll->l_head->l_hatom);
		if (curr_marker_ms > 0)
			llll_appenddouble(durations, curr_marker_ms, 0, WHITENULL_llll);
		for (mk_elem = markers->l_head; mk_elem; mk_elem = mk_elem->l_next) {
			double this_marker_ms = hatom_getdouble(&mk_elem->l_hatom.h_w.w_llll->l_head->l_hatom);
			llll_appendhatom_clone(names, &mk_elem->l_hatom.h_w.w_llll->l_head->l_next->l_hatom, 0, WHITENULL_llll); // marker name

			if (this_marker_ms > curr_marker_ms) 
				llll_appenddouble(durations, this_marker_ms - curr_marker_ms, 0, WHITENULL_llll);
			curr_marker_ms = this_marker_ms;
		}
		if (curr_marker_ms < tot_length)
			llll_appenddouble(durations, tot_length - curr_marker_ms, 0, WHITENULL_llll);
	} else {
		llll_appenddouble(durations, tot_length, 0, WHITENULL_llll);
	}
	
	if (meta)
		*meta = llll_get();

	t_llllelem *dur_elem = durations->l_head, *name_elem = names->l_head;
	long i = 1;
    double phase = 0;
	while (dur_elem && curr_onset < tot_length) {
		double this_duration = hatom_getdouble(&dur_elem->l_hatom);
		t_symbol *label = NULL;
		if (name_elem) {
			if (hatom_gettype(&name_elem->l_hatom) == H_SYM)
				label = hatom_getsym(&name_elem->l_hatom);
			else if (hatom_gettype(&name_elem->l_hatom) == H_LLLL) {
				t_llll *ll = hatom_getllll(&name_elem->l_hatom);
				if (ll && ll->l_head && hatom_gettype(&ll->l_head->l_hatom) == H_SYM)
					label = hatom_getsym(&ll->l_head->l_hatom);
			}
		}
		
		t_llll *right = dada_roll_split_preserve(temp, this_duration, false, false, x->copy_tempi_marker);
		dada_roll_shift(right, -this_duration);
        
        if (x->window_type != DADA_WINDOW_NONE)
            dada_roll_apply_window_on_velocities(temp, (e_dada_windows)x->window_type, &this_duration);

		llll_appendllll(result, temp, 0, WHITENULL_llll);
		
		// meta-information
		if (meta) {
			t_llll *this_meta = llll_get();
            if (x->feature_phase) {
                char is_division = 0;
                dada_get_first_marker_division_or_barline(temp, &is_division);
                if (is_division)
                    phase+=1;
            }
            
			process_standard_features_roll(x, this_meta, temp, i, curr_onset, this_duration, label, voice_number, phase);
			process_custom_features(x, this_meta, temp);

			llll_appendllll(*meta, this_meta, 0, WHITENULL_llll);
		}
		
		curr_onset += this_duration;
		temp = right;
		dur_elem = dur_elem->l_next;
		name_elem = name_elem ? name_elem->l_next : NULL;
		i++;
	}
	
	llll_free(markers);
	llll_free(names);
	llll_free(durations);
	return result;
}



t_llll *segment_roll_labels(t_segment *x, t_llll *roll, t_llll **meta, long voice_number)
{
	t_llll *labels = dada_roll_get_labels(roll);
	double curr_onset = 0;
	t_llll *result = llll_get();
	
	if (meta)
		*meta = llll_get();
	
	t_llllelem *label_el;
	long i;
	for (label_el = labels->l_head, i = 0; label_el; label_el = label_el->l_next, i++) {
		t_llll *this_label_ll = hatom_getllll(&hatom_getllll(&label_el->l_hatom)->l_head->l_hatom); // labels are arranged by (label count) (label count)...
	
        t_llll *temp = dada_roll_extract_label(llll_clone(roll), &this_label_ll->l_head->l_hatom, &curr_onset);
        
		double curr_duration = dada_roll_get_length(temp);
		t_symbol *label = (this_label_ll->l_head && hatom_gettype(&this_label_ll->l_head->l_hatom) == H_SYM) ? hatom_getsym(&this_label_ll->l_head->l_hatom) : NULL;
		
        if (x->window_type != DADA_WINDOW_NONE)
            dada_roll_apply_window_on_velocities(temp, (e_dada_windows)x->window_type, &curr_duration);
        
		llll_appendllll(result, temp, 0, WHITENULL_llll);
		
		// meta-information
		if (meta) {
			t_llll *this_meta = llll_get();
			
			process_standard_features_roll(x, this_meta, temp, i, curr_onset, curr_duration, label, voice_number, 0);
			process_custom_features(x, this_meta, temp);
			
			llll_appendllll(*meta, this_meta, 0, WHITENULL_llll);
		}
	}
	
	llll_free(labels);
	
	return result;
}


t_llll *segment_roll_do(t_segment *x, t_llll *roll, t_llll **meta, long voice_number)
{
	t_llll *result = NULL;
	switch (x->algorithm) {
		case DADA_SEGMENTATION_ALGORITHM_EQUATION:
			result = segment_roll_standard(x, roll, meta, voice_number);
			break;
		case DADA_SEGMENTATION_ALGORITHM_MARKERS:
			result = segment_roll_markers(x, roll, meta, voice_number);
			break;
		case DADA_SEGMENTATION_ALGORITHM_LABELS:
			result = segment_roll_labels(x, roll, meta, voice_number);
			break;
		default:
			object_error((t_object *)x, "Can't use the defined segmentation algorithm for bach.roll.");
			break;
	}
	return result;
}


t_llll *segment_roll(t_segment *x, t_llll *roll, t_llll **meta)
{
    if (x->voicewise) { // voice-wise
        t_llll *result = llll_get();
        t_llllelem *elem, *first_nonheader_elem = get_first_nonheader_elem(roll);
        t_llll *header = llll_get();
        t_llll *voicenames_ll = NULL;
        
        if (meta)
            *meta = llll_get();
        
        for (elem = roll->l_head; elem && elem != first_nonheader_elem; elem = elem->l_next) {
            // should not clone
            t_llll *templl = NULL;
            if (hatom_gettype(&elem->l_hatom) == H_LLLL && (templl = hatom_getllll(&elem->l_hatom)) &&
                templl->l_head && hatom_getsym(&templl->l_head->l_hatom) == _llllobj_sym_voicenames) {
                voicenames_ll= templl;
            } else {
                llll_appendhatom_clone(header, &elem->l_hatom);
            }
        }
        
        long i = 1;
        for (; elem; elem = elem->l_next, i++)
            if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
                t_llll *this_ll = llll_clone(header);
                t_llll *this_meta = NULL;
                t_llll *this_result = NULL;
                
                if (this_ll && voicenames_ll) {
                    t_llllelem *el = llll_getindex(voicenames_ll, i+1, I_STANDARD);
                    if (el) {
                        t_llll *temp = llll_get();
                        llll_appendsym(temp, _llllobj_sym_voicenames);
                        llll_appendhatom_clone(temp, &el->l_hatom);
                        llll_appendllll(this_ll, temp);
                    }
                }
                
                llll_appendllll_clone(this_ll, hatom_getllll(&elem->l_hatom));
                this_result = segment_roll_do(x, this_ll, &this_meta, i);
                llll_chain(result, this_result);
                if (meta)
                    llll_chain(*meta, this_meta);
                llll_free(this_ll);
            }
        
        llll_free(header);
        return result;
    } else
        return segment_roll_do(x, roll, meta, 1);
}


// if cut_points is NULL, they are calculated via segmentsize and hopsize
t_llll *segment_segment_presegmented_score_and_append_standard(t_segment *x, t_llll *score, t_llll *result, t_llll **meta, long measure_offset, long *idx_offset, long voice_number, t_llll *cut_points)
{
    char dont_segment = ((cut_points == NULL) && (x->segmentsize_as_sym == _llllobj_sym_empty_symbol || x->segmentsize_as_sym == _llllobj_sym_none));

    if (!dont_segment && !x->segmentsize_lexpr && cut_points == NULL)  {
		object_error((t_object *)x, "No valid segment size expression introduced");
		return NULL;
	}
    
    char hop_defined = (x->hopsize_lexpr ? 1 : 0);
	
	t_hatom vars[6];
	
	t_llll *temp = llll_clone(score);
	

    if (dont_segment) {

        if (x->window_type != DADA_WINDOW_NONE)
            dada_score_apply_window_on_velocities(temp, (e_dada_windows)x->window_type, NULL);
        
        llll_appendllll(result, temp, 0, WHITENULL_llll);

        // meta-information
        if (meta) {
            t_llll *this_meta = llll_get();
            t_rational this_beat_phase = long2rat(0);
            t_rational this_segm_size = dada_score_get_totsymduration(score);
            t_rational this_div = long2rat(0);
            t_tempo *this_tempo = NULL;
            
            if (x->feature_bpm || x->feature_tempo)  // no need to compute tempo otherwise
                this_tempo = dada_score_get_first_tempo(temp);
            
            process_standard_features_score(x, this_meta, 0 + (*idx_offset) + 1, measure_offset, this_div, this_tempo,
                                            long2rat(0), this_beat_phase, this_segm_size, voice_number);
            process_custom_features(x, this_meta, temp);

            (*idx_offset) += 1;
            
            llll_appendllll(*meta, this_meta, 0, WHITENULL_llll);
            
            if (this_tempo)
                bach_freeptr(this_tempo);
        }
    
    } else {
        
        
        // getting time signatures
        t_llll *ts = dada_score_get_ts(score);
        t_llll *divs = dada_score_getdivisions(score);
        
        int cut_points_curr_idx = 0;
        t_rational cut_points_curr_onset = long2rat(0);
        
        if (divs && divs->l_head && hatom_gettype(&divs->l_head->l_hatom) == H_LLLL) {
            
            t_llll *divs_wk = llll_get();
            t_llll *segm_size = llll_get();
            t_llll *timepoints_start = llll_get();
            t_llll *timepoints_end = llll_get();
            t_llll *beat_phases = llll_get();
            t_llll *divs_out = llll_get();
            
            t_llllelem *elem, *ts_elem = ts->l_head;
            if (ts_elem && hatom_gettype(&ts_elem->l_hatom) == H_LLLL)
                ts_elem = hatom_getllll(&ts_elem->l_hatom)->l_head;
            
            // building divs_wk
            t_timesignature *this_ts = ts ? (t_timesignature *)hatom_getobj(&ts_elem->l_hatom) : NULL;
            for (elem = hatom_getllll(&divs->l_head->l_hatom)->l_head; elem; elem = elem->l_next) {
                if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
                    t_llll *temp_ll = hatom_getllll(&elem->l_hatom);
                    llll_chain_clone(divs_wk, temp_ll);
                    llll_appendobj(divs_wk, WHITENULL, 0, WHITENULL_llll); // measure separator
                }
            }
            
            if (divs_wk->l_head && is_hatom_number(&divs_wk->l_head->l_hatom)) {
                t_timepoint tp = build_timepoint(0, long2rat(0));
                t_rational tp_global_sym_onset = long2rat(0);
                t_rational global_sym_onset = long2rat(0), size_accum = long2rat(0);
                t_rational measure_sym_onset = long2rat(0);
                long beat_num = 0;
                double approx_error = 0;
                
                t_llll *first_tp_as_ll = llll_get();
                llll_appendlong(first_tp_as_ll, 0);
                llll_appendrat(first_tp_as_ll, long2rat(0));
                llll_appendrat(first_tp_as_ll, long2rat(0));
                llll_appendlong(first_tp_as_ll, 0);
                llll_appendllll(timepoints_start, first_tp_as_ll);
                
                elem = divs_wk->l_head;
                while (elem) {
                    t_rational div = hatom_getrational(&elem->l_hatom);
                    t_rational measure_sym_dur = this_ts ? genrat(this_ts->numerator, this_ts->denominator) : long2rat(0);
                    
                    
                    // get segment size
                    t_rational hop_size, seg_size;
                    if (cut_points) { // markers are given
                        t_rational cut_points_new_onset = cut_points_curr_onset;
                        while (cut_points_new_onset == cut_points_curr_onset) {
                            cut_points_curr_idx++;
                            t_llllelem *el = llll_getindex(cut_points, cut_points_curr_idx, I_STANDARD);
                            cut_points_new_onset = hatom_getrational(&el->l_hatom);
                        }
                        seg_size = cut_points_new_onset - cut_points_curr_onset;
                        hop_size = seg_size;
                        cut_points_curr_onset = cut_points_new_onset;
                    } else {
                        t_hatom *res = NULL;
                        hatom_setlong(vars, 0);
                        hatom_setlong(vars + 1, tp.measure_num + 1 + measure_offset);
                        hatom_setrational(vars + 2, measure_sym_dur);
                        hatom_setrational(vars + 3, div);
                        hatom_setrational(vars + 4, div);
                        hatom_setlong(vars + 5, 0);
                        res = lexpr_eval(x->segmentsize_lexpr, vars);
                        if (!res)  {
                            object_error((t_object *)x, "Can't compute segment size");
                            return NULL;
                        }
                        switch (hatom_gettype(res)) {
                            case H_LONG:
                            case H_RAT:
                                seg_size = hatom_getrational(res);
                                break;
                            case H_DOUBLE:
                                seg_size = approx_double_with_rat_best_match(hatom_getdouble(res), 32, 0, &approx_error);
                                break;
                            default:
                                seg_size = div;
                                break;
                        }
                        bach_freeptr(res);
                        
                        if (rat_long_cmp(seg_size, 0) <= 0) {
                            object_error((t_object *)x, "Non-positive segment size introduced. The division will be used instead.");
                            seg_size = div;
                        }
                        
                        
                        // get hop size size
                        hop_size = seg_size;
                        if (x->hopsize_lexpr) {
                            hatom_setlong(vars, 0);
                            hatom_setlong(vars + 1, tp.measure_num + 1 + measure_offset);
                            hatom_setrational(vars + 2, measure_sym_dur);
                            hatom_setrational(vars + 3, div);
                            hatom_setrational(vars + 4, div);
                            res = lexpr_eval(x->hopsize_lexpr, vars);
                            if (!res)  {
                                object_error((t_object *)x, "Can't compute segment size");
                                return NULL;
                            }
                            switch (hatom_gettype(res)) {
                                case H_LONG:
                                case H_RAT:
                                    hop_size = hatom_getrational(res);
                                    break;
                                case H_DOUBLE:
                                    hop_size = approx_double_with_rat_best_match(hatom_getdouble(res), 32, 0, &approx_error);
                                    break;
                                default:
                                    hop_size = div;
                                    break;
                            }
                            bach_freeptr(res);
                        }
                    }
                    
                    
                    llll_appendrat(segm_size, seg_size, 0, WHITENULL_llll);
                    llll_appendrat(beat_phases, rat_long_sum(rat_rat_div(rat_rat_diff(tp.pt_in_measure, size_accum), div), beat_num), 0, WHITENULL_llll);
                    llll_appendrat(divs_out, div, 0, WHITENULL_llll);
                    
                    
                    // Computing timepoint end
                    if (hop_defined) {
                        t_rational new_global_sym_onset_end = rat_rat_sum(global_sym_onset, seg_size);
                        t_rational temp_end = global_sym_onset;
                        t_timepoint tp_end = tp;
                        t_llllelem *elem_end = elem;
                        t_llllelem *ts_elem_end = ts_elem;
                        t_timesignature *this_ts_end = this_ts;
                        t_rational size_accum_end = size_accum, tp_global_sym_onset_end = tp_global_sym_onset;
                        char double_break = false;
                        while (elem_end) {
                            if (hatom_gettype(&elem_end->l_hatom) == H_OBJ) { // new measure
                                tp_end.measure_num ++;
                                measure_sym_onset = long2rat(0);
                                tp_end.pt_in_measure = long2rat(0);
                                ts_elem_end = ts_elem_end ? ts_elem_end->l_next : NULL;
                                this_ts_end = ts_elem_end ? (t_timesignature *)hatom_getobj(&ts_elem_end->l_hatom) : NULL;
                                if (!elem_end->l_next) {
                                    double_break = true;
                                    break; // we're done
                                }
                            } else {
                                t_rational this_size_end = hatom_getrational(&elem->l_hatom);
                                temp_end = rat_rat_sum(size_accum_end, this_size_end);
                                long cmp = rat_rat_cmp(temp_end, new_global_sym_onset_end);
                                if (cmp < 0) {
                                    tp_end.pt_in_measure = rat_rat_sum(tp_end.pt_in_measure, this_size_end);
                                    tp_global_sym_onset_end = rat_rat_sum(tp_global_sym_onset_end, this_size_end);
                                    size_accum_end = temp_end;
                                    // nothing to do
                                } else if (cmp == 0) {
                                    // precise cut
                                    tp_end.pt_in_measure = rat_rat_sum(rat_rat_sum(tp_end.pt_in_measure, this_size_end), rat_rat_diff(size_accum_end, tp_global_sym_onset_end));
                                    tp_global_sym_onset_end = temp_end;
                                    elem_end = elem_end->l_next;
                                    size_accum_end = temp_end;
                                    break;
                                } else if (cmp > 0) {
                                    // overflow
                                    tp_end.pt_in_measure = rat_rat_sum(rat_rat_sum(tp_end.pt_in_measure, this_size_end), rat_rat_diff(size_accum_end, tp_global_sym_onset_end)); // tp_end.pt_in_measure + this_size_end
                                    tp_end.pt_in_measure = rat_rat_diff(tp_end.pt_in_measure, rat_rat_diff(temp_end, new_global_sym_onset_end));
                                    tp_global_sym_onset_end = new_global_sym_onset_end;
                                    break;
                                }
                            }
                            elem_end = elem_end->l_next;
                        }
                        
                        if (double_break)
                            break; // done.
                        
                        // converting timepoint to llll
                        t_llll *tp_as_ll_end = llll_get();
                        llll_appendlong(tp_as_ll_end, tp_end.measure_num);
                        llll_appendrat(tp_as_ll_end, tp_end.pt_in_measure);
                        llll_appendrat(tp_as_ll_end, tp_global_sym_onset_end);
                        
                        if (hatom_gettype(&elem_end->l_hatom) == H_OBJ) { // measure barline
                            llll_appendlong(tp_as_ll_end, 1);
                        } else
                            llll_appendlong(tp_as_ll_end, 0);
                        
                        llll_appendllll(timepoints_end, tp_as_ll_end); // actually timepoints + global sym onset + is_on_barline?
                    }
                    
                    
                    //				t_rational new_global_sym_onset = rat_rat_sum(global_sym_onset, seg_size);
                    t_rational new_global_sym_onset = rat_rat_sum(global_sym_onset, hop_size);
                    t_rational temp = global_sym_onset;
                    while (elem) {
                        if (hatom_gettype(&elem->l_hatom) == H_OBJ) { // new measure
                            tp.measure_num ++;
                            beat_num = 0;
                            measure_sym_onset = long2rat(0);
                            tp.pt_in_measure = long2rat(0);
                            ts_elem = ts_elem ? ts_elem->l_next : NULL;
                            this_ts = ts_elem ? (t_timesignature *)hatom_getobj(&ts_elem->l_hatom) : NULL;
                        } else {
                            t_rational this_size = hatom_getrational(&elem->l_hatom);
                            temp = rat_rat_sum(size_accum, this_size);
                            long cmp = rat_rat_cmp(temp, new_global_sym_onset);
                            if (cmp < 0) { // division is still within the ending point of the segment
                                tp.pt_in_measure = rat_rat_sum(tp.pt_in_measure, this_size);
                                tp_global_sym_onset = rat_rat_sum(rat_rat_sum(tp_global_sym_onset, this_size), rat_rat_diff(size_accum, tp_global_sym_onset));
                                size_accum = temp;
                                // nothing to do
                            } else if (cmp == 0) {
                                // precise cut
                                //                            tp.pt_in_measure = temp;
                                tp.pt_in_measure = rat_rat_sum(rat_rat_sum(tp.pt_in_measure, this_size), rat_rat_diff(size_accum, tp_global_sym_onset));
                                tp_global_sym_onset = temp;
                                elem = elem->l_next;
                                beat_num++;
                                size_accum = temp;
                                break;
                            } else if (cmp > 0) {
                                // division overflows with respect to ending point
                                //                            tp.pt_in_measure = new_global_sym_onset; //rat_rat_sum(tp.pt_in_measure, rat_rat_diff(new_global_sym_onset, temp));
                                tp.pt_in_measure = rat_rat_sum(rat_rat_sum(tp.pt_in_measure, this_size), rat_rat_diff(size_accum, tp_global_sym_onset));
                                tp.pt_in_measure = rat_rat_diff(tp.pt_in_measure, rat_rat_diff(temp, new_global_sym_onset));
                                tp_global_sym_onset = new_global_sym_onset;
                                break;
                            }
                        }
                        elem = elem->l_next;
                        beat_num++;
                    }
                    
                    // converting timepoint to llll
                    t_llll *tp_as_ll = llll_get();
                    llll_appendlong(tp_as_ll, tp.measure_num);
                    llll_appendrat(tp_as_ll, tp.pt_in_measure);
                    llll_appendrat(tp_as_ll, tp_global_sym_onset);
                    
                    global_sym_onset = new_global_sym_onset;
                    
                    if (hatom_gettype(&elem->l_hatom) == H_OBJ) { // measure barline
                        tp.measure_num ++;
                        beat_num = 0;
                        measure_sym_onset = long2rat(0);
                        tp.pt_in_measure = long2rat(0);
                        ts_elem = ts_elem ? ts_elem->l_next : NULL;
                        this_ts = ts ? (t_timesignature *)hatom_getobj(&ts_elem->l_hatom) : NULL;
                        
                        llll_appendlong(tp_as_ll, 1);
                        
                        elem = elem->l_next;
                    } else
                        llll_appendlong(tp_as_ll, 0);
                    
                    if (!hop_defined)
                        llll_appendllll_clone(timepoints_end, tp_as_ll); // actually timepoints + global sym onset + is_on_barline?
                    llll_appendllll(timepoints_start, tp_as_ll); // actually timepoints + global sym onset + is_on_barline?
                }
            }
            
//            llll_print(timepoints_start);
//            llll_print(timepoints_end);
            
            t_llllelem *temp_seg, *temp_tp_start, *temp_tp_end, *temp_beatphase, *temp_div;
            long count;
            t_timepoint prev_tp_start = build_timepoint(0, long2rat(0));
            for (count = 0, temp_seg = segm_size->l_head, temp_tp_start = timepoints_start->l_head, temp_tp_end = timepoints_end->l_head, temp_beatphase = beat_phases->l_head, temp_div = divs_out->l_head;
                 temp_seg && temp_tp_start && temp_tp_end && temp_beatphase && temp_div;
                 temp_seg = temp_seg->l_next, temp_tp_start = temp_tp_start->l_next, temp_tp_end = temp_tp_end->l_next, temp_beatphase = temp_beatphase->l_next, temp_div = temp_div->l_next, count++) {
                t_timesignature ts;
                t_tempo tempo;
                t_timepoint this_tp_start = build_timepoint(temp_tp_start->l_hatom.h_w.w_llll->l_head->l_hatom.h_w.w_long, hatom_getrational(&temp_tp_start->l_hatom.h_w.w_llll->l_head->l_next->l_hatom));
                t_timepoint this_tp_end = build_timepoint(temp_tp_end->l_hatom.h_w.w_llll->l_head->l_hatom.h_w.w_long, hatom_getrational(&temp_tp_end->l_hatom.h_w.w_llll->l_head->l_next->l_hatom));
                //            t_rational this_tp_global_sym_onset = temp_tp->l_hatom.h_w.w_llll->l_head->l_next->l_next->l_hatom.h_w.w_rat;
                
                long is_on_barline = temp_tp_start->l_hatom.h_w.w_llll->l_head->l_next->l_next->l_next->l_hatom.h_w.w_long;
                if (is_on_barline) {
                    this_tp_start.measure_num++;
                    this_tp_start.pt_in_measure = long2rat(0);
                }
                
                t_timepoint tp_diff = timepoints_diff(this_tp_end, this_tp_start);
                
                t_llll *right = NULL;
                if (hop_defined) {
                    if (temp_tp_start->l_next) {
                        t_timepoint next_tp_start = build_timepoint(temp_tp_start->l_next->l_hatom.h_w.w_llll->l_head->l_hatom.h_w.w_long, hatom_getrational(&temp_tp_start->l_next->l_hatom.h_w.w_llll->l_head->l_next->l_hatom));
                        
                        t_timepoint tp_diff_hop = timepoints_diff(next_tp_start, this_tp_start);
                        
                        t_llll *freeme1 = llll_clone(temp);
                        right = dada_score_split(freeme1, tp_diff_hop, NULL, NULL, true);
                        t_llll *freeme2 = dada_score_split(temp, tp_diff, &ts, &tempo, true);
                        llll_free(freeme1);
                        llll_free(freeme2);
                    } else
                        right = dada_score_split(temp, tp_diff, &ts, &tempo, true);
                } else
                    right = dada_score_split(temp, tp_diff, &ts, &tempo, true);
                
                //            post("---");
                //            llll_print(temp, NULL, 0, 6, NULL);
                //            llll_print(right, NULL, 0, 6, NULL);
                //            post("---");
                
                if (x->window_type != DADA_WINDOW_NONE)
                    dada_score_apply_window_on_velocities(temp, (e_dada_windows)x->window_type, NULL);
                
                llll_appendllll(result, temp, 0, WHITENULL_llll);
                
                // meta-information
                if (meta) {
                    t_llll *this_meta = llll_get();
                    t_rational this_beat_phase = hatom_getrational(&temp_beatphase->l_hatom);
                    t_rational this_segm_size = hatom_getrational(&temp_seg->l_hatom);
                    t_rational this_div = hatom_getrational(&temp_div->l_hatom);
                    t_tempo *this_tempo = NULL;
                    
                    if (x->feature_bpm || x->feature_tempo)  // no need to compute tempo otherwise
                        this_tempo = dada_score_get_first_tempo(temp);
                    
                    process_standard_features_score(x, this_meta, count + (*idx_offset) + 1, measure_offset + prev_tp_start.measure_num, this_div, this_tempo,
                                                    this_tp_start.pt_in_measure, this_beat_phase, this_segm_size, voice_number);
                    process_custom_features(x, this_meta, temp);
                    
                    llll_appendllll(*meta, this_meta, 0, WHITENULL_llll);
                    
                    if (this_tempo)
                        bach_freeptr(this_tempo);
                }
                
                prev_tp_start = this_tp_start;
                
                temp = right;
            }
            
            (*idx_offset) += count;
            
            llll_free(divs_wk);
            llll_free(timepoints_start);
            llll_free(timepoints_end);
            llll_free(segm_size);
            llll_free(beat_phases);
            llll_free(divs_out);
        }
        
        // freeing ts
        t_llllelem *elem;
        llll_flatten(ts, 0, 0);
        for (elem = ts->l_head; elem; elem = elem->l_next) 
            bach_freeptr((t_timesignature *)hatom_getobj(&elem->l_hatom));
        llll_free(ts);
    }
	
	return result;
}


t_llll *segment_score_standard(t_segment *x, t_llll *score, t_llll **meta, long voice_number)
{
    if (x->measure_segm_pattern_size == 0 || (x->measure_segm_pattern_size == 1 && x->measure_segm_pattern[0] == 0)) {
        // no pre-segmentation
        t_llll *res = llll_get();
        long idx_offset = 0;
        if (meta)
            *meta = llll_get();
        segment_segment_presegmented_score_and_append_standard(x, score, res, meta, 0, &idx_offset, voice_number, NULL);
        return res;

    } else {
        // first of all pre-segmenting by measure pattern
        long num_measures = dada_score_get_nummeas(score);
        
        long i = 0, n = 0;
        long *splits = (long *)bach_newptr(num_measures * sizeof(long));
        while (i < num_measures) {
            splits[i] = (i == 0 ? 0 : splits[i-1]) + x->measure_segm_pattern[i % x->measure_segm_pattern_size];
            if (splits[i] >= num_measures) {
                break;
            }
            i++;
        }
        n = i;
        
        if (meta)
            *meta = llll_get();
        
        t_llll *presegm_scores = dada_score_multisplit_measures(score, n, splits, true);
        t_llll *res = llll_get();
        t_llllelem *elem;
        i = -1;
        
        
        long idx_offset = 0;
        for (elem = presegm_scores->l_head; elem && i < num_measures; elem = elem->l_next, i++) {
            if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
                segment_segment_presegmented_score_and_append_standard(x, hatom_getllll(&elem->l_hatom), res, meta, i < 0 ? 0 : splits[i], &idx_offset, voice_number, NULL);
            }
        }
        
        bach_freeptr(splits);
        
        return res;
    }
}

//	TO DO
t_llll *segment_score_labels(t_segment *x, t_llll *score, t_llll **meta)
{
/*	t_llll *labels = dada_roll_get_labels(roll);
	double curr_onset = 0;
	t_llll *result = llll_get();
	
	if (meta)
		*meta = llll_get();
	
	t_llllelem *label_el;
	long i;
	for (label_el = labels->l_head, i = 0; label_el; label_el = label_el->l_next, i++) {
		t_llll *this_label_ll = hatom_getllll(&hatom_getllll(&label_el->l_hatom)->l_head->l_hatom); // labels are arranged by (label count) (label count)...
		t_llll *temp = dada_roll_extract_label(llll_clone(roll), &this_label_ll->l_head->l_hatom, &curr_onset);
		double curr_duration = dada_roll_get_length(temp);
		t_symbol *label = (this_label_ll->l_head && hatom_gettype(&this_label_ll->l_head->l_hatom) == H_SYM) ? hatom_getsym(&this_label_ll->l_head->l_hatom) : NULL;
		
		llll_appendllll(result, temp, 0, WHITENULL_llll);
		
		// meta-information
		if (meta) {
			t_llll *this_meta = llll_get();
			
			process_standard_features_roll(x, this_meta, temp, i, curr_onset, curr_duration, label);
			process_custom_features(x, this_meta, temp);
			
			llll_appendllll(*meta, this_meta, 0, WHITENULL_llll);
		}
	}
	
	llll_free(labels);
	
	return result;*/
	return NULL;
}



t_llll *segment_score_markers(t_segment *x, t_llll *score, t_llll **meta, long voice_number)
{
    t_llll *markers = dada_get_markers(score);
    t_llll *measuresymdurs = dada_score_get_measuresymdurs(score);
    t_llll *res = llll_get();

    // building cumulative measure symdurs
    t_llll *measuresymdurs_cumulative = llll_get();
    for (t_llllelem *el = measuresymdurs->l_head; el; el = el->l_next) {
        t_llll *measuresymdurs_voice = hatom_getllll(&el->l_hatom);
        t_llll *measuresymdurs_cumulative_voice = llll_get();
        t_rational cur = long2rat(0);
        llll_appendrat(measuresymdurs_cumulative_voice, cur);
        for (t_llllelem *el = measuresymdurs_voice->l_head; el; el = el->l_next) {
            t_rational r = hatom_getrational(&el->l_hatom);
            llll_appendrat(measuresymdurs_cumulative_voice, cur+r);
        }
        llll_appendllll(measuresymdurs_cumulative, measuresymdurs_cumulative_voice);
    }

//    llll_print(measuresymdurs_cumulative);
    
    if (measuresymdurs_cumulative && measuresymdurs_cumulative->l_head && markers) {
        // getting cut_points from markers
        t_llll *cut_points = llll_get();
        
        for (t_llllelem *el = markers->l_head; el; el = el->l_next) {
            if (hatom_gettype(&el->l_hatom) == H_LLLL) {
                t_llll *mk_llll = hatom_getllll(&el->l_hatom);
                if (mk_llll && mk_llll->l_head) {
                    t_llll *position = hatom_getllll(&mk_llll->l_head->l_hatom);
                    if (position && position->l_size >= 3) {
                        long voice_num = hatom_getlong(&position->l_head->l_hatom);
                        long measure_num = hatom_getlong(&position->l_head->l_next->l_hatom);
                        t_rational mk_onset = hatom_getrational(&position->l_head->l_next->l_next->l_hatom);
                        
                        t_llllelem *voice_el = llll_getindex(measuresymdurs_cumulative, voice_num, I_STANDARD);
                        if (voice_el) {
                            t_llll *voice_ll = hatom_getllll(&voice_el->l_hatom);
                            if (voice_ll) {
                                t_llllelem *measure_onset_el = llll_getindex(voice_ll, measure_num, I_STANDARD);
                                if (measure_onset_el) {
                                    t_rational measure_onset = measure_onset_el ? hatom_getrational(&measure_onset_el->l_hatom) : long2rat(0);
                                    llll_appendrat(cut_points, measure_onset + mk_onset);
                                }
                            }
                        }
                    }
                }
            }
        }
        
        long idx_offset = 0;
        if (meta)
            *meta = llll_get();
        
//        llll_print(cut_points);
        
        segment_segment_presegmented_score_and_append_standard(x, score, res, meta, 0, &idx_offset, voice_number, cut_points);
    }
    
    
    llll_free(measuresymdurs);
    llll_free(markers);
    
    return res;
}

t_llll *segment_score_do(t_segment *x, t_llll *score, t_llll **meta, long voice_number)
{
	t_llll *result = NULL;
	switch (x->algorithm) {
		case DADA_SEGMENTATION_ALGORITHM_EQUATION:
			result = segment_score_standard(x, score, meta, voice_number);
			break;
        case DADA_SEGMENTATION_ALGORITHM_MARKERS:
            result = segment_score_markers(x, score, meta, voice_number);
            break;
		default:
			object_error((t_object *)x, "Can't use the defined segmentation algorithm for bach.score.");
			break;
	}
	return result;
}


t_llll *segment_score(t_segment *x, t_llll *score, t_llll **meta)
{
    if (x->voicewise) { // voice-wise
        t_llll *result = llll_get();
        t_llllelem *elem, *first_nonheader_elem = get_first_nonheader_elem(score);
        t_llll *header = llll_get();
        t_llll *voicenames_ll = NULL;
        
        if (meta)
            *meta = llll_get();
        
        for (elem = score->l_head; elem && elem != first_nonheader_elem; elem = elem->l_next) {
            t_llll *templl = NULL;
            if (hatom_gettype(&elem->l_hatom) == H_LLLL && (templl = hatom_getllll(&elem->l_hatom)) &&
                templl->l_head && hatom_getsym(&templl->l_head->l_hatom) == _llllobj_sym_voicenames) {
                // don't copy voicenames
                voicenames_ll = templl;
            } else {
                llll_appendhatom_clone(header, &elem->l_hatom);
            }
        }
        
        // substitute 1 to all markers' voices
        for (t_llllelem *tmp_elem = header->l_head; tmp_elem; tmp_elem = tmp_elem->l_next) {
            if (hatom_gettype(&tmp_elem->l_hatom) == H_LLLL) {
                t_llll *tmp_elem_ll = hatom_getllll(&tmp_elem->l_hatom);
                if (tmp_elem_ll && tmp_elem_ll->l_head && hatom_gettype(&tmp_elem_ll->l_head->l_hatom) == H_SYM && hatom_getsym(&tmp_elem_ll->l_head->l_hatom) == _llllobj_sym_markers) {
                    for (t_llllelem *mkel = tmp_elem_ll->l_head->l_next; mkel; mkel = mkel->l_next) {
                        if (hatom_gettype(&mkel->l_hatom) == H_LLLL) {
                            t_llll *mkll = hatom_getllll(&mkel->l_hatom);
                            if (mkll && mkll->l_head && hatom_gettype(&mkll->l_head->l_hatom) == H_LLLL) {
                                t_llll *mkposll = hatom_getllll(&mkll->l_head->l_hatom);
                                if (mkposll->l_size >= 3 && mkposll->l_depth == 1)
                                    hatom_setlong(&mkposll->l_head->l_hatom, 1);
                            }
                        }
                    }
                }
            }
        }
//        llll_print(header);
        
        long i = 1;
        for (; elem; elem = elem->l_next, i++)
            if (hatom_gettype(&elem->l_hatom) == H_LLLL) {
                t_llll *this_ll = llll_clone(header);
                t_llll *this_meta = NULL;
                t_llll *this_result = NULL;
                
                if (this_ll && voicenames_ll) {
                    t_llllelem *el = llll_getindex(voicenames_ll, i+1, I_STANDARD);
                    if (el) {
                        t_llll *temp = llll_get();
                        llll_appendsym(temp, _llllobj_sym_voicenames);
                        llll_appendhatom_clone(temp, &el->l_hatom);
                        llll_appendllll(this_ll, temp);
                    }
                }
                
                llll_appendllll_clone(this_ll, hatom_getllll(&elem->l_hatom));
                this_result = segment_score_do(x, this_ll, &this_meta, i);
                llll_chain(result, this_result);
                if (meta)
                    llll_chain(*meta, this_meta);
                llll_free(this_ll);
            }
        
        llll_free(header);
        return result;
    } else
        return segment_score_do(x, score, meta, 1);
}



void segment_anything(t_segment *x, t_symbol *msg, long ac, t_atom *av)
{
	long inlet = proxy_getinlet((t_object *) x);
	
	if (inlet == 0) {
		// segment data
		t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_VANILLA, msg, ac, av, LLLL_PARSE_RETAIN);
		t_llll *result = NULL;
		t_llll *meta = NULL;
		
		
		// roll or score?
		if (parsed && parsed->l_head && hatom_gettype(&parsed->l_head->l_hatom) == H_SYM) {
			t_symbol *scoretype = hatom_getsym(&parsed->l_head->l_hatom);
			if (scoretype == _llllobj_sym_roll) {
				result = segment_roll(x, parsed, &meta);
			} else if (scoretype == _llllobj_sym_score) {
				result = segment_score(x, parsed, &meta);
			}
		}
		
		if (result) {
			llllobj_outlet_llll((t_object *)x, LLLL_OBJ_VANILLA, 1, meta);
			llllobj_outlet_llll((t_object *)x, LLLL_OBJ_VANILLA, 0, result);
		}
		llll_free(result);
		llll_free(meta);
		llll_free(parsed);

	} else  if (inlet == 1) {
		// lambda inlet
		llllobj_parse_and_store((t_object *) x, LLLL_OBJ_VANILLA, msg, ac, av, 1);
	}
}



///////// ACCESSORS

t_max_err segment_setattr_algorithm(t_segment *x, t_object *attr, long ac, t_atom *av)
{
    if (ac > 0) {
        x->algorithm = CLAMP(atom_getlong(av), 0, 2);
        
        object_attr_setdisabled((t_object *)x, gensym("tempomarkersseg"), x->algorithm != DADA_SEGMENTATION_ALGORITHM_MARKERS);
        object_attr_setdisabled((t_object *)x, gensym("segmentsize"), x->algorithm != DADA_SEGMENTATION_ALGORITHM_EQUATION);
        object_attr_setdisabled((t_object *)x, gensym("hopsize"), x->algorithm != DADA_SEGMENTATION_ALGORITHM_EQUATION);

        object_attr_setdisabled((t_object *)x, gensym("ftlabel"), x->algorithm != DADA_SEGMENTATION_ALGORITHM_MARKERS && x->algorithm != DADA_SEGMENTATION_ALGORITHM_LABELS);
    }
    return MAX_ERR_NONE;
}

t_max_err segment_setattr_segmentsize(t_segment *x, t_object *attr, long ac, t_atom *av)
{
	if (ac > 0) {
		char *text = NULL;
		const char *subs[] = {"onset","measurenum","measuresymdur","division","beat", "none"};
		long size;
		
		t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_VANILLA, NULL, ac, av, LLLL_PARSE_CLONE);
		atom_gettext(ac, av, &size, &text, OBEX_UTIL_ATOM_GETTEXT_SYM_NO_QUOTE | LLLL_D_PARENS);
		
		x->segmentsize_as_sym = gensym(text);
		
		if (x->segmentsize_lexpr)
			lexpr_free(x->segmentsize_lexpr);
		
		if (!(x->segmentsize_lexpr = lexpr_new(ac, av, 6, subs, (t_object *)x)))
            object_error((t_object *)x, "Error: wrong segment size expression introduced!");
		
		
		llll_free(parsed);
		bach_freeptr(text);
	}
	return MAX_ERR_NONE;
}



t_max_err segment_setattr_hopsize(t_segment *x, t_object *attr, long ac, t_atom *av)
{
    if (ac > 0) {
        char *text = NULL;
        const char *subs[] = {"onset","measurenum","measuresymdur","division","beat"};
        long size;
        
        t_llll *parsed = llllobj_parse_llll((t_object *) x, LLLL_OBJ_VANILLA, NULL, ac, av, LLLL_PARSE_CLONE);
        atom_gettext(ac, av, &size, &text, OBEX_UTIL_ATOM_GETTEXT_SYM_NO_QUOTE | LLLL_D_PARENS);
        
        x->hopsize_as_sym = gensym(text);
        
        if (x->hopsize_as_sym && strlen(x->hopsize_as_sym->s_name) > 0) {
            
            if (x->hopsize_lexpr)
                lexpr_free(x->hopsize_lexpr);
            
            if (!(x->hopsize_lexpr = lexpr_new(ac, av, 5, subs, (t_object *)x)))
                object_error((t_object *)x, "Error: wrong segment size expression introduced!");
            
            llll_free(parsed);
            bach_freeptr(text);
        } else {
            if (x->hopsize_lexpr)
                lexpr_free(x->hopsize_lexpr);
            x->hopsize_lexpr = NULL;
        }
    } else {
        x->hopsize_as_sym = gensym("");
        
        if (x->hopsize_lexpr)
            lexpr_free(x->hopsize_lexpr);
        x->hopsize_lexpr = NULL;
    }
    return MAX_ERR_NONE;
}

