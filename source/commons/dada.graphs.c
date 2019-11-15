/**
	@file
	dada.graphs.c
	Graphs and networks utilities for dada library

	by Daniele Ghisi
*/

#include "dada.graphs.h"

t_llll *metadata_to_llll(t_dada_graph_metadata *data, e_dada_graph_metadata_type type)
{
	t_llll *metadata = llll_get();
	switch (type) {
		case DADA_GRAPH_METADATA_LONG:
			llll_appendllll(metadata, symbol_and_long_to_llll(gensym("value"), data->m_long), 0, WHITENULL_llll);
			break;
		case DADA_GRAPH_METADATA_DOUBLE:
			llll_appendllll(metadata, symbol_and_double_to_llll(gensym("value"), data->m_double), 0, WHITENULL_llll);
			break;
        case DADA_GRAPH_METADATA_WEIGHT:
            llll_appendllll(metadata, symbol_and_double_to_llll(gensym("weight"), data->m_double), 0, WHITENULL_llll);
            break;
		case DADA_GRAPH_METADATA_PITCHNVEL:
			llll_appendllll(metadata, symbol_and_double_to_llll(gensym("pitch"), data->m_pitchnvel.pitch_mc), 0, WHITENULL_llll);
			llll_appendllll(metadata, symbol_and_double_to_llll(gensym("velocity"), data->m_pitchnvel.velocity), 0, WHITENULL_llll);
			break;
        case DADA_GRAPH_METADATA_SCORE:
            llll_appendllll(metadata, symbol_and_symbol_to_llll(gensym("label"), data->m_llllscore.label));
            llll_appendllll(metadata, symbol_and_llll_to_llll_chained(gensym("score"), llll_clone(data->m_llllscore.ll)));
            break;
		case DADA_GRAPH_METADATA_OUTINNUM:
			llll_appendllll(metadata, symbol_and_long_to_llll(gensym("numin"), data->m_outinnum.num_in), 0, WHITENULL_llll);
			llll_appendllll(metadata, symbol_and_long_to_llll(gensym("numout"), data->m_outinnum.num_out), 0, WHITENULL_llll);
			break;
		case DADA_GRAPH_METADATA_VANILLABOX:
			llll_appendllll(metadata, symbol_and_symbol_to_llll(gensym("type"), data->m_vanillabox.type), 0, WHITENULL_llll);
			llll_appendllll(metadata, symbol_and_long_to_llll(gensym("numins"), data->m_vanillabox.num_ins), 0, WHITENULL_llll);
			llll_appendllll(metadata, symbol_and_long_to_llll(gensym("numouts"), data->m_vanillabox.num_outs), 0, WHITENULL_llll);
			break;
		case DADA_GRAPH_METADATA_LLLLNODE:
		{
			t_llll *label = llll_get();
			llll_appendsym(label, _llllobj_sym_label, 0, WHITENULL_llll);
			llll_chain_clone(label, data->m_llllnode.ll);
			llll_appendllll(metadata, label, 0, WHITENULL_llll);

            if (data->m_llllnode.bgcolor.red >= 0) {
                t_llll *bgcolor = llll_get();
                llll_appendsym(bgcolor, _sym_bgcolor, 0, WHITENULL_llll);
                llll_chain(bgcolor, color_to_llll(&data->m_llllnode.bgcolor));
                llll_appendllll(metadata, bgcolor, 0, WHITENULL_llll);
            }
            
            if (data->m_llllnode.bordercolor.red >= 0) {
                t_llll *bordercolor = llll_get();
                llll_appendsym(bordercolor, gensym("bordercolor"), 0, WHITENULL_llll);
                llll_chain(bordercolor, color_to_llll(&data->m_llllnode.bordercolor));
                llll_appendllll(metadata, bordercolor, 0, WHITENULL_llll);
            }
            
            if (data->m_llllnode.textcolor.red >= 0) {
                t_llll *textcolor = llll_get();
                llll_appendsym(textcolor, gensym("textcolor"), 0, WHITENULL_llll);
                llll_chain(textcolor, color_to_llll(&data->m_llllnode.textcolor));
                llll_appendllll(metadata, textcolor, 0, WHITENULL_llll);
            }
        }
            break;
        case DADA_GRAPH_METADATA_OBJ:
        {
            t_llll *objll = llll_get();
            llll_appendsym(objll, gensym("obj"));
            llll_appendobj(objll, data->m_obj);
            llll_appendllll(metadata, objll);
        }
            break;
		default:
			break;
	}
	return metadata;
}


void metadata_from_llll(t_llll *ll, t_dada_graph_metadata *data, e_dada_graph_metadata_type type)
{
	if (!ll) 
		return;
	
	switch (type) {
		case DADA_GRAPH_METADATA_LONG:
			llll_parseargs(NULL, ll, "i", gensym("value"), &data->m_long);
			break;
		case DADA_GRAPH_METADATA_DOUBLE:
			llll_parseargs(NULL, ll, "d", gensym("value"), &data->m_double);
			break;
        case DADA_GRAPH_METADATA_WEIGHT:
            llll_parseargs(NULL, ll, "d", gensym("weight"), &data->m_double);
            break;
		case DADA_GRAPH_METADATA_PITCHNVEL:
			llll_parseargs(NULL, ll, "di", gensym("pitch"), &data->m_pitchnvel.pitch_mc, gensym("velocity"), &data->m_pitchnvel.velocity);
			break;
        case DADA_GRAPH_METADATA_SCORE:
        {
            t_llll *score_ll = NULL;
            llll_parseargs(NULL, ll, "ls", gensym("score"), &score_ll, gensym("label"), &data->m_llllscore.label);
            if (score_ll)
                data->m_llllscore.ll = score_ll;
            else
                data->m_llllscore.ll = llll_get();
        }
            break;
		case DADA_GRAPH_METADATA_OUTINNUM:
			llll_parseargs(NULL, ll, "ii", gensym("numin"), &data->m_outinnum.num_in, gensym("numout"), &data->m_outinnum.num_out);
			break;
		case DADA_GRAPH_METADATA_VANILLABOX:
		{
			long j;
			llll_parseargs(NULL, ll, "sii", gensym("type"), &data->m_vanillabox.type, gensym("numins"), &data->m_vanillabox.num_ins, gensym("numouts"), &data->m_vanillabox.num_outs);
			for (j = 0; j < DADA_GRAPH_MAX_VANILLABOX_INS; j++)
				data->m_vanillabox.ins[j] = NULL;
		}
			break;
		case DADA_GRAPH_METADATA_LLLLNODE:
		{
			t_llll *label_ll = NULL, *bgcolor_ll = NULL, *bordercolor_ll = NULL, *textcolor_ll = NULL;
			llll_parseargs(NULL, ll, "llll", gensym("label"), &label_ll, gensym("bgcolor"), &bgcolor_ll, gensym("bordercolor"), &bordercolor_ll, gensym("textcolor"), &textcolor_ll);
			
			if (label_ll)
				data->m_llllnode.ll = label_ll;
			else 
				data->m_llllnode.ll = llll_get();
			
			if (bgcolor_ll)
				data->m_llllnode.bgcolor = llll_to_color(bgcolor_ll);
            else
                data->m_llllnode.bgcolor = build_jrgba(-1, -1, -1, 0); // meaning: default

			if (bordercolor_ll)
				data->m_llllnode.bordercolor = llll_to_color(bordercolor_ll);
            else
                data->m_llllnode.bordercolor = build_jrgba(-1, -1, -1, 0); // meaning: default

			if (textcolor_ll)
				data->m_llllnode.textcolor = llll_to_color(textcolor_ll);
            else
                data->m_llllnode.textcolor = build_jrgba(-1, -1, -1, 0); // meaning: default

			llll_free(bgcolor_ll);
			llll_free(bordercolor_ll);
			llll_free(textcolor_ll);
		}
			break;
		default:
			break;
	}
}


void graph_set_metadata_to_vertex_from_llll(t_dada_graph *graph, long vertex_id, t_llll *metadata_ll)
{
    if (vertex_id >= 0 && vertex_id < graph->num_vertices)
        metadata_from_llll(metadata_ll, &graph->vertices[vertex_id].data, graph->vertex_metadata_type);
}

void graph_set_metadata_to_edge_from_llll(t_dada_graph *graph, long edge_id, t_llll *metadata_ll)
{
    if (edge_id >= 0 && edge_id < graph->num_edges)
        metadata_from_llll(metadata_ll, &graph->edges[edge_id].data, graph->edge_metadata_type);
}


t_llll *graph_vertex_to_llll(t_dada_graph *graph, long vertex_id)
{
	t_llll *vr = llll_get();	
	
	t_llll *coord = llll_get();
	llll_appendsym(coord, gensym("coord"), 0, WHITENULL_llll);
	llll_chain(coord, pt_to_llll(graph->vertices[vertex_id].r_it.coord, 0));
	llll_appendllll(vr, coord, 0, WHITENULL_llll);
	
	if (graph->vertex_metadata_type != DADA_GRAPH_METADATA_NONE) 
		llll_chain(vr, metadata_to_llll(&graph->vertices[vertex_id].data, graph->vertex_metadata_type));
	return vr;
}

t_llll *graph_edge_to_llll(t_dada_graph *graph, long edge_id)
{
    t_llll *ed = llll_get();
    llll_appendlong(ed, graph->edges[edge_id].start + 1);
    llll_appendlong(ed, graph->edges[edge_id].end + 1);
    if (graph->edge_metadata_type != DADA_GRAPH_METADATA_NONE)
        llll_chain(ed, metadata_to_llll(&graph->edges[edge_id].data, graph->edge_metadata_type));
    if (graph->edges[edge_id].flag & DADA_GRAPH_EDGE_FLAG_PASSTHROUGH)
        llll_appendllll(ed, symbol_and_long_to_llll(gensym("passthrough"), 1));
    return ed;
}

t_llll *graph_to_llll(t_dada_graph *graph)
{
	t_llll *out = llll_get();
	t_llll *vertices = llll_get();
	t_llll *edges = llll_get();
	
	llll_appendsym(vertices, gensym("vertices"), 0, WHITENULL_llll);
	llll_appendsym(edges, gensym("edges"), 0, WHITENULL_llll);
	
    for (long i = 0; i < graph->num_vertices; i++)
		llll_appendllll(vertices, graph_vertex_to_llll(graph, i));

	for (long i = 0; i < graph->num_edges; i++)
		llll_appendllll(edges, graph_edge_to_llll(graph, i));

	llll_appendllll(out, vertices);
	llll_appendllll(out, edges);
	return out;
}



void graph_from_llll(t_llll *graph_as_llll, t_dada_graph *graph, double node_width, double node_height)
{
	t_llllelem *elem;
	t_llll *ll;
	long i;
	
	// First of all, we free the memory of the existing graph
	graph_free_all_metadata_lllls(graph);
	
	graph->num_vertices = graph->num_edges = 0;

	for (elem = graph_as_llll->l_head; elem; elem = elem->l_next) {
		if (hatom_gettype(&elem->l_hatom) == H_LLLL &&
			(ll = hatom_getllll(&elem->l_hatom)) && ll->l_head &&
			hatom_gettype(&ll->l_head->l_hatom) == H_SYM) {
			t_symbol *router = hatom_getsym(&ll->l_head->l_hatom);
			
			if (router == gensym("vertices")) {
				
				// set vertices
				t_llllelem *vert_el;
				long num_verts = ll->l_size - 1;
				
				if (num_verts > graph->num_allocated_vertices) {
					bach_freeptr(graph->vertices);
					graph->num_allocated_vertices = ceil((double)num_verts/DADA_GRAPH_ALLOC_STEP) * DADA_GRAPH_ALLOC_STEP;
					graph->vertices = (t_dada_graph_vertex *)bach_newptrclear(graph->num_allocated_vertices * sizeof(t_dada_graph_vertex));
				}
				
				for (i = 0, vert_el = ll->l_head->l_next; vert_el && i < num_verts; vert_el = vert_el->l_next, i++) {
					if (hatom_gettype(&vert_el->l_hatom) == H_LLLL) {
						t_llll *vr = hatom_getllll(&vert_el->l_hatom);
						dadaitem_init(NULL, (t_dadaitem *)&graph->vertices[i], DADAITEM_TYPE_VERTEX, 0, false, 0);
                        graph->vertices[i].flag = 0;
                        graph->vertices[i].r_it.width = node_width;
                        graph->vertices[i].r_it.height = node_height;
                        
						if (vr->l_depth == 1)
							graph->vertices[i].r_it.coord = llll_to_pt(hatom_getllll(&vert_el->l_hatom));
						else {
							t_llll *coords = NULL;
							llll_parseargs(NULL, vr, "l", gensym("coord"), &coords);
							if (coords)
								graph->vertices[i].r_it.coord = llll_to_pt(coords);
							llll_free(coords);
							metadata_from_llll(vr, &graph->vertices[i].data, graph->vertex_metadata_type);
						}
                    } else {
                        // this is a simple label!
                        dadaitem_init(NULL, (t_dadaitem *)&graph->vertices[i], DADAITEM_TYPE_VERTEX, 0, false, 0);
                        graph->vertices[i].r_it.width = node_width;
                        graph->vertices[i].r_it.height = node_height;
                        graph->vertices[i].r_it.coord = build_pt(0, 0);
                        
                        // label
                        graph->vertices[i].data.m_llllnode.ll = llll_get();
                        llll_appendhatom_clone(graph->vertices[i].data.m_llllnode.ll, &vert_el->l_hatom);
                        
                        graph->vertices[i].data.m_llllnode.bgcolor = build_jrgba(-1, -1, -1, 0); // meaning: default
                        graph->vertices[i].data.m_llllnode.bordercolor = build_jrgba(-1, -1, -1, 0); // meaning: default
                        graph->vertices[i].data.m_llllnode.textcolor = build_jrgba(-1, -1, -1, 0); // meaning: default
                    }
				}
				
				graph->num_vertices = num_verts;
				
			} else if (router == gensym("edges")) {

				// set edges
				t_llllelem *edge_el;
				long num_edges = ll->l_size - 1;
				
				if (num_edges > graph->num_allocated_edges) {
					bach_freeptr(graph->edges);
					graph->num_allocated_edges = ceil((double)num_edges/DADA_GRAPH_ALLOC_STEP) * DADA_GRAPH_ALLOC_STEP;
					graph->edges = (t_dada_graph_edge *)bach_newptrclear(graph->num_allocated_edges * sizeof(t_dada_graph_edge));
				}
				
				for (i = 0, edge_el = ll->l_head->l_next; edge_el && i < num_edges; edge_el = edge_el->l_next, i++) {
					if (hatom_gettype(&edge_el->l_hatom) == H_LLLL) {
						t_llll *ll = hatom_getllll(&edge_el->l_hatom);
						if (ll && ll->l_size >= 2 && is_hatom_number(&ll->l_head->l_hatom) &&
							is_hatom_number(&ll->l_head->l_next->l_hatom)) {
							long idx1 = hatom_getlong(&ll->l_head->l_hatom) - 1;
							long idx2 = hatom_getlong(&ll->l_head->l_next->l_hatom) - 1;
							if (idx1 >= 0 && idx1 < graph->num_vertices && idx2 >= 0 && idx2 < graph->num_vertices) {
								graph->edges[i].start = idx1;
								graph->edges[i].end = idx2;
							}
							
                            graph->edges[i].flag = 0;
                            
                            long passthrough = 0;
                            llll_parseargs(NULL, ll, "i", gensym("passthrough"), &passthrough);
                            if (passthrough)
                                graph->edges[i].flag |= DADA_GRAPH_EDGE_FLAG_PASSTHROUGH;
                            
							// edge metadata
							if (ll->l_head->l_next->l_next && hatom_gettype(&ll->l_head->l_next->l_next->l_hatom) == H_LLLL)
								metadata_from_llll(ll, &graph->edges[i].data, graph->edge_metadata_type);
						}
					}
				}

				graph->num_edges = num_edges;
				
			}
		}
	}
	
	if (graph->flags & DADA_GRAPH_FLAG_CONNECTED_COMPONENTS)
		graph_parse_connected_components(graph);
}



void graph_new(t_dada_graph *graph, long flags, e_dada_graph_metadata_type vertex_metadata_type, 
			   e_dada_graph_metadata_type edge_metadata_type, e_dada_line_style line_style)
{
	graph->flags = flags;
	graph->vertices = (t_dada_graph_vertex *)bach_newptrclear(DADA_GRAPH_ALLOC_STEP * sizeof(t_dada_graph_vertex));
	graph->edges = (t_dada_graph_edge *)bach_newptrclear(DADA_GRAPH_ALLOC_STEP * sizeof(t_dada_graph_edge));
	graph->num_allocated_edges = graph->num_allocated_vertices = DADA_GRAPH_ALLOC_STEP; 
	graph->edge_metadata_type = edge_metadata_type;
	graph->vertex_metadata_type = vertex_metadata_type;
	graph->line_style = line_style;
	
	if (flags & DADA_GRAPH_FLAG_CONNECTED_COMPONENTS) {
		graph->connected_components = (t_dada_graph_connected_component *)bach_newptr(DADA_GRAPH_ALLOC_STEP * sizeof(t_dada_graph_connected_component));
		graph->num_allocated_connected_components = DADA_GRAPH_ALLOC_STEP;
	} else {
		graph->connected_components = (t_dada_graph_connected_component *)bach_newptr(1 * sizeof(t_dada_graph_connected_component));
		graph->num_allocated_connected_components = 1;
	}

	graph->num_vertices = graph->num_edges = graph->num_connected_components = 0;
	
	graph->dont_reparse_or_update_connected_components = false;
}


void graph_free_connected_components(t_dada_graph *graph)
{
	long i;
	for (i = 0; i < graph->num_connected_components; i++)
		bach_freeptr(graph->connected_components[i].vertices);
}

void vertex_free(t_dada_graph *graph, long vertex_id)
{
	long j;
	switch (graph->vertex_metadata_type) {
		case DADA_GRAPH_METADATA_VANILLABOX:
			for (j = 0; j < DADA_GRAPH_MAX_VANILLABOX_INS; j++)
				llll_free(graph->vertices[vertex_id].data.m_vanillabox.ins[j]);
			break;
		case DADA_GRAPH_METADATA_LLLLNODE:
			llll_free(graph->vertices[vertex_id].data.m_llllnode.ll);
			break;
        case DADA_GRAPH_METADATA_SCORE:
            llll_free(graph->vertices[vertex_id].data.m_llllscore.ll);
            break;
		default:
			break;
	}
}

void edge_free(t_dada_graph *graph, long edge_id)
{
	long j;
	switch (graph->edge_metadata_type) {
		case DADA_GRAPH_METADATA_VANILLABOX:
			for (j = 0; j < DADA_GRAPH_MAX_VANILLABOX_INS; j++)
				llll_free(graph->edges[edge_id].data.m_vanillabox.ins[j]);
			break;
		case DADA_GRAPH_METADATA_LLLLNODE:
			llll_free(graph->edges[edge_id].data.m_llllnode.ll);
			break;
        case DADA_GRAPH_METADATA_SCORE:
            llll_free(graph->edges[edge_id].data.m_llllscore.ll);
            break;
		default:
			break;
	}
}

void graph_free_all_metadata_lllls(t_dada_graph *graph)
{
	long i, j;
	switch (graph->vertex_metadata_type) {
		case DADA_GRAPH_METADATA_VANILLABOX:
			for (i = 0; i < graph->num_vertices; i++)
				for (j = 0; j < DADA_GRAPH_MAX_VANILLABOX_INS; j++)
					llll_free(graph->vertices[i].data.m_vanillabox.ins[j]);
			break;
		case DADA_GRAPH_METADATA_LLLLNODE:
			for (i = 0; i < graph->num_vertices; i++)
				llll_free(graph->vertices[i].data.m_llllnode.ll);
			break;
        case DADA_GRAPH_METADATA_SCORE:
            for (i = 0; i < graph->num_vertices; i++)
                llll_free(graph->vertices[i].data.m_llllscore.ll);
            break;
		default:
			break;
	}
	switch (graph->edge_metadata_type) {
		case DADA_GRAPH_METADATA_VANILLABOX:
			for (i = 0; i < graph->num_edges; i++)
				for (j = 0; j < DADA_GRAPH_MAX_VANILLABOX_INS; j++)
					llll_free(graph->edges[i].data.m_vanillabox.ins[j]);
			break;
		case DADA_GRAPH_METADATA_LLLLNODE:
			for (i = 0; i < graph->num_edges; i++)
				llll_free(graph->edges[i].data.m_llllnode.ll);
			break;
        case DADA_GRAPH_METADATA_SCORE:
            for (i = 0; i < graph->num_edges; i++)
                llll_free(graph->edges[i].data.m_llllscore.ll);
            break;
		default:
			break;
	}
}




void graph_assign_all_default_metadata(t_dada_graph *graph)
{
    long i;
    for (i = 0; i < graph->num_vertices; i++)
        graph->vertices[i].data = get_default_vertex_metadata(graph);
    for (i = 0; i < graph->num_edges; i++)
        graph->edges[i].data = get_default_edge_metadata(graph);
}




void graph_free(t_dada_graph *graph)
{
	// depending on the metadata, we might need to free stuff!!!
	graph_free_all_metadata_lllls(graph);
	bach_freeptr(graph->vertices);
	bach_freeptr(graph->edges);
	graph_free_connected_components(graph);
	bach_freeptr(graph->connected_components);
}


void graph_paint_edge(t_dadaobj *r_ob, t_jgraphics *g, t_rect rect, t_pt center, t_dada_graph *graph,
					  t_jrgba graph_color, long edge_index,
					  double fixed_vertex_width, double fixed_vertex_height, vertex_to_properties_fn vertex_to_properties,
					  double edge_width, char edge_retouch_mode, edge_to_properties_fn edge_to_properties, char paint_hover,
                      t_jfont *jf_label, char show_arrows)
{
	long i = edge_index;
	t_dada_graph_vertex *v1 = &graph->vertices[graph->edges[i].start];
	t_dada_graph_vertex *v2 = &graph->vertices[graph->edges[i].end];
	t_pt pix1 = coord_to_pix(r_ob, center, v1->r_it.coord);
	t_pt pix2 = coord_to_pix(r_ob, center, v2->r_it.coord);
	t_pt start = pix1, end = pix2;
	
	if (edge_retouch_mode != DADA_GRAPH_EDGERETOUCH_NONE) {
		double width1 = fixed_vertex_width, height1 = fixed_vertex_height;
		double width2 = width1, height2 = height1;
		
		if (vertex_to_properties) {
			(vertex_to_properties)(v1, &width1, &height1);
			(vertex_to_properties)(v2, &width2, &height2);
		}
		
        if (edge_retouch_mode == DADA_GRAPH_EDGERETOUCH_SNAP_TO_BORDER && (fabs(pix1.x - pix2.x) < CONST_EPSILON1 || fabs(pix1.y - pix2.y) < CONST_EPSILON1))
            edge_retouch_mode = DADA_GRAPH_EDGERETOUCH_SNAP_TO_MIDPOINTS;
        
        if (edge_retouch_mode == DADA_GRAPH_EDGERETOUCH_SNAP_TO_BORDER) {
            // intersection between line y = pix1.y - height1/2 and the border
            // (y - pix1.y)/(pix2.y - pix1.y) = (x - pix1.x)/(pix2.x - pix1.x)
            // yielding
            t_rect r1 = build_rect(pix1.x - width1/2., pix1.y - height1/2., width1, height1);
            t_rect r2 = build_rect(pix2.x - width2/2., pix2.y - height2/2., width2, height2);

            rect_linetorect_intersect(pix2, r1, &start);
            rect_linetorect_intersect(pix1, r2, &end);
            
        } else if (edge_retouch_mode == DADA_GRAPH_EDGERETOUCH_SNAP_TO_MIDPOINTS) {
            // retouch start and end point
            if (fabs(pix1.x - pix2.x) > fabs(pix1.y - pix2.y)) { // delta x larger than delta y
                if (pix2.x > pix1.x) {
                    start.x = pix1.x + width1 / 2.;
                    end.x = pix2.x - width2 / 2.;
                    start.y = pix1.y;
                    end.y = pix2.y;
                } else {
                    start.x = pix1.x - width1 / 2.;
                    end.x = pix2.x + width2 / 2.;
                    start.y = pix1.y;
                    end.y = pix2.y;
                }
            } else {
                if (pix1.y > pix2.y) {
                    start.y = pix1.y - height1 / 2.;
                    end.y = pix2.y + height2 / 2.;
                    start.x = pix1.x;
                    end.x = pix2.x;
                } else {
                    start.y = pix1.y + height1 / 2.;
                    end.y = pix2.y - height2 / 2.;
                    start.x = pix1.x;
                    end.x = pix2.x;
                }
            }
        }
	}
	
	char label[256];
	label[0] = 0;
	if (edge_to_properties && jf_label)
		(edge_to_properties)(&graph->edges[i], label);
    
    // debug
/*    if (jf_label){
        char buf[20];
        t_pt middle = pt_pt_sum(start, pt_number_prod(pt_pt_diff(end, start), 0.5));
        snprintf(buf, 20, "%ld: %ld > %ld", i + 1, graph->edges[i].start + 1, graph->edges[i].end + 1);
        write_text_simple(g, jf_label, DADA_RED, buf, middle.x-20, middle.y -20, 200, 200);
    }
*/
    if (graph->edges[i].flag & DADA_GRAPH_EDGE_FLAG_PASSTHROUGH)
        graph_color = change_alpha(graph_color, 0.1);
    
	paint_line_advanced(g, graph_color, start, end, edge_width, graph->line_style, show_arrows && !(graph->flags & DADA_GRAPH_FLAG_SYMMETRIC), DADA_GRAPH_ARROW_SIZE, label, jf_label, DADA_GRAPH_CURVE_AMOUNT * r_ob->m_zoom.zoom.x);
	
	if (paint_hover && r_ob->m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_EDGE && r_ob->m_interface.mousemove_item_identifier.idx == i)
		paint_line_advanced(g, change_alpha(graph_color, 0.3), start, end, edge_width + DADA_GRAPH_EDGE_DEFAULT_SELECTION_PAD, graph->line_style, 
							!(graph->flags & DADA_GRAPH_FLAG_SYMMETRIC), DADA_GRAPH_ARROW_SIZE, label, jf_label, DADA_GRAPH_CURVE_AMOUNT * r_ob->m_zoom.zoom.x);
}


void graph_paint(t_dadaobj *r_ob, t_jgraphics *g, t_rect rect, t_pt center, t_dada_graph *graph,
				 t_jrgba graph_color, char paint_vertices, char paint_edges, 
				 double fixed_vertex_width, double fixed_vertex_height, vertex_to_properties_fn vertex_to_properties,
				 double edge_width, char edge_retouch_mode, edge_to_properties_fn edge_to_properties, char paint_hover, t_jfont *jf_label, char show_arrows)
{
	long i;
	
	// painting sides
	if (paint_edges) {
		for (i = 0; i < graph->num_edges; i++) 
			graph_paint_edge(r_ob, g, rect, center, graph, graph_color, i, fixed_vertex_width, fixed_vertex_height, vertex_to_properties,
							 edge_width, edge_retouch_mode, edge_to_properties, paint_hover, jf_label, show_arrows);
	}
	
	// painting vertices
	if (paint_vertices) {
		for (i = 0; i < graph->num_vertices; i++) {
			t_pt pix = coord_to_pix(r_ob, center, graph->vertices[i].r_it.coord);
			double width = fixed_vertex_width, height = fixed_vertex_height;
			if (vertex_to_properties) 
				(vertex_to_properties)(&graph->vertices[i], &width, &height);
			paint_rectangle(g, graph_color, graph_color, pix.x - width/2., pix.y - height/2., width, height, 0);

			if (paint_hover && r_ob->m_interface.mousemove_item_identifier.type == DADAITEM_TYPE_VERTEX && r_ob->m_interface.mousemove_item_identifier.idx == i)
				paint_rectangle(g, graph_color, change_alpha(graph_color, 0.3), pix.x - width/2. - DADA_GRAPH_VERTEX_DEFAULT_SELECTION_PAD/2., pix.y - height/2. - DADA_GRAPH_VERTEX_DEFAULT_SELECTION_PAD/2., width + DADA_GRAPH_VERTEX_DEFAULT_SELECTION_PAD, height + DADA_GRAPH_VERTEX_DEFAULT_SELECTION_PAD, 0);
		}
	}
}


void graph_change_line_style(t_dada_graph *graph, e_dada_line_style new_style)
{
	graph->line_style = new_style;
}



long graph_coord_to_vertex(t_dadaobj *r_ob, t_dada_graph *graph, t_pt coord, double vertex_size_in_coord, double tolerance)
{
	long i;
    double tolerance_coord = delta_pix_to_delta_coord(r_ob, build_pt(tolerance, 0)).x;
	if (vertex_size_in_coord < 0 && graph->vertex_metadata_type == DADA_GRAPH_METADATA_LLLLNODE) {
		for (i = 0; i < graph->num_vertices; i++) {
			double width_pix = graph->vertices[i].data.m_llllnode.width;
			double height_pix = graph->vertices[i].data.m_llllnode.height;
            t_pt wh = delta_pix_to_delta_coord(r_ob, build_pt(width_pix, -height_pix));
			if (is_pt_in_rectangle(coord, build_rect(graph->vertices[i].r_it.coord.x - wh.x/2. - tolerance_coord,
													 graph->vertices[i].r_it.coord.y - wh.y/2. - tolerance_coord,
													 wh.x + 2 * tolerance_coord, wh.y + 2 * tolerance_coord)))
				return i;
		}
	} else {
		for (i = 0; i < graph->num_vertices; i++) {
			if (is_pt_in_rectangle(coord, build_rect(graph->vertices[i].r_it.coord.x - vertex_size_in_coord/2. - tolerance_coord,
													 graph->vertices[i].r_it.coord.y - vertex_size_in_coord/2. - tolerance_coord,
													 vertex_size_in_coord + 2 * tolerance_coord, vertex_size_in_coord + 2 *tolerance_coord)))
				return i;
		}
	}
	return -1;
}

long graph_coord_to_edge(t_dadaobj *r_ob, t_dada_graph *graph, t_pt coord, double edge_width_in_coord, double tolerance)
{
	long i;
	for (i = 0; i < graph->num_edges; i++) {
		t_pt start = graph->vertices[graph->edges[i].start].r_it.coord;
		t_pt end = graph->vertices[graph->edges[i].end].r_it.coord;
        double tolerance_coord = delta_pix_to_delta_coord(r_ob, build_pt(tolerance, 0)).x;
		switch (graph->line_style) {
			case DADA_LINE_SEGMENTED:
				if (is_pt_in_segmented_line_shape(coord.x, coord.y, start.x, start.y, end.x, end.y, edge_width_in_coord + 2 * tolerance_coord))
					return i;
				break;
			case DADA_LINE_CURVE:
				if (is_pt_in_curve_advanced_shape(coord, start, end, edge_width_in_coord, DADA_GRAPH_CURVE_AMOUNT * r_ob->m_zoom.zoom.x))
					return i;
			default:
				if (is_pt_in_line_shape_improved(coord.x, coord.y, start.x, start.y, end.x, end.y, edge_width_in_coord + 2 * tolerance_coord))
					return i;
				break;
		}
	}
	return -1;
}



void graph_clear(t_dada_graph *graph)
{
    graph_free_all_metadata_lllls(graph);
	graph->num_vertices = 0;
	graph->num_edges = 0;
    graph->num_connected_components = 0;
}


long graph_add_vertex(t_dada_graph *graph, t_pt coord, t_dada_graph_metadata metadata, double width, double height, long flag)
{
	if (graph->num_vertices >= graph->num_allocated_vertices) {
		graph->num_allocated_vertices += DADA_GRAPH_ALLOC_STEP;
		graph->vertices = (t_dada_graph_vertex *)bach_resizeptrclear(graph->vertices, graph->num_allocated_vertices * sizeof(t_dada_graph_vertex));
	}

	graph->vertices[graph->num_vertices].connected_component_idx = -1;
	graph->vertices[graph->num_vertices].flag = flag;
	graph->vertices[graph->num_vertices].data = metadata;
	graph->vertices[graph->num_vertices].r_it.coord = coord;
    graph->vertices[graph->num_vertices].r_it.width = width;
    graph->vertices[graph->num_vertices].r_it.height = height;
	dadaitem_init(NULL, (t_dadaitem *)&graph->vertices[graph->num_vertices], DADAITEM_TYPE_VERTEX, 0, false, 0);

	graph->num_vertices++;
	
	if ((graph->flags & DADA_GRAPH_FLAG_CONNECTED_COMPONENTS) && (!graph->dont_reparse_or_update_connected_components)) {
		long l = graph->num_vertices - 1;
		graph_add_connected_component(graph, 1, &l);
	}

	return graph->num_vertices - 1;
}


/// 0 based indices
long graph_add_edge(t_dada_graph *graph, long idx1, long idx2, t_dada_graph_metadata metadata, long flag)
{
	if (idx1 >= 0 && idx1 < graph->num_vertices && idx2 >= 0 && idx2 < graph->num_vertices) {
		if (graph->num_edges >= graph->num_allocated_edges) {
			graph->num_allocated_edges += DADA_GRAPH_ALLOC_STEP;
			graph->edges = (t_dada_graph_edge *)bach_resizeptr(graph->edges, graph->num_allocated_edges * sizeof(t_dada_graph_edge));
		}
		
		graph->edges[graph->num_edges].start = idx1;
		graph->edges[graph->num_edges].end = idx2;
		graph->edges[graph->num_edges].data = metadata;
		graph->edges[graph->num_edges].flag = flag;
		
		graph->num_edges ++;

		if ((graph->flags & DADA_GRAPH_FLAG_CONNECTED_COMPONENTS) && (!graph->dont_reparse_or_update_connected_components)) 
			graph_parse_connected_components(graph);

		return graph->num_edges - 1;
	}
	
	return -1;
}

long graph_add_edge_symmetric(t_dada_graph *graph, long idx1, long idx2, t_dada_graph_metadata metadata)
{
    char temp = graph->dont_reparse_or_update_connected_components;
	graph->dont_reparse_or_update_connected_components = true;

	long res = graph_add_edge(graph, idx1, idx2, metadata);
	graph_add_edge(graph, idx2, idx1, clone_metadata(graph->edge_metadata_type, metadata));
	
    graph->dont_reparse_or_update_connected_components = temp;

    if ((graph->flags & DADA_GRAPH_FLAG_CONNECTED_COMPONENTS) && (!graph->dont_reparse_or_update_connected_components))
		graph_parse_connected_components(graph);
	
	return res;
}

long graph_import_dadapolygon(t_dada_graph *graph, t_dadapolygon *poly, t_dada_graph_metadata vertex_metadata, 
						  t_dada_graph_metadata edge_metadata, char sides_in_harm_series, double node_width, double node_height)
{
	long i, curr_num_vertices = graph->num_vertices;
	double base_freq = sides_in_harm_series ? mc_to_freq(edge_metadata.m_pitchnvel.pitch_mc, 440) : 0;
	
    char temp = graph->dont_reparse_or_update_connected_components;
	graph->dont_reparse_or_update_connected_components = true;

	for (i = 0; i < poly->num_vertices; i++)
		graph_add_vertex(graph, poly->vertex[i], clone_metadata(graph->vertex_metadata_type, vertex_metadata), node_width, node_height);
	
	if (poly->num_vertices > 1) {
		for (i = 0; i < poly->num_vertices - 1; i++) {
			if (sides_in_harm_series)
				edge_metadata.m_pitchnvel.pitch_mc = freq_to_mc(base_freq * (i + 1), 440);
			graph_add_edge(graph, curr_num_vertices + i, curr_num_vertices + i + 1, edge_metadata);
		}
		
		if (sides_in_harm_series)
			edge_metadata.m_pitchnvel.pitch_mc = freq_to_mc(base_freq * poly->num_vertices, 440);
		graph_add_edge(graph, curr_num_vertices + poly->num_vertices - 1, curr_num_vertices, edge_metadata);
	}
	
	graph->dont_reparse_or_update_connected_components = temp;

	if ((graph->flags & DADA_GRAPH_FLAG_CONNECTED_COMPONENTS) && (!graph->dont_reparse_or_update_connected_components)) {
		long *vertices = (long *)bach_newptr(poly->num_vertices * sizeof(long));
		for (i = 0; i < poly->num_vertices; i++)
			vertices[i] = curr_num_vertices + i;
		graph_add_connected_component(graph, poly->num_vertices, vertices);
		bach_freeptr(vertices);
	}

	return curr_num_vertices;
}


void graph_move_vertex(t_dada_graph *graph, long idx, t_pt new_coord)
{
	if (idx >= 0 && idx < graph->num_vertices)  
		graph->vertices[idx].r_it.coord = new_coord;
	
	if ((graph->flags & DADA_GRAPH_FLAG_CONNECTED_COMPONENTS) && (!graph->dont_reparse_or_update_connected_components)) 
		graph_update_connected_component_convex_hull(graph, graph->vertices[idx].connected_component_idx);
}


void graph_move_vertex_delta(t_dada_graph *graph, long idx, t_pt delta_coord)
{
	if (idx >= 0 && idx < graph->num_vertices)  
		graph->vertices[idx].r_it.coord = pt_pt_sum(graph->vertices[idx].r_it.coord, delta_coord);

	if ((graph->flags & DADA_GRAPH_FLAG_CONNECTED_COMPONENTS) && (!graph->dont_reparse_or_update_connected_components)) 
		graph_update_connected_component_convex_hull(graph, graph->vertices[idx].connected_component_idx);
}

void graph_move_edge(t_dada_graph *graph, long idx, t_pt new_barycenter_coord)
{
	if (idx >= 0 && idx < graph->num_edges) {
		t_pt *start = &graph->vertices[graph->edges[idx].start].r_it.coord;
		t_pt *end = &graph->vertices[graph->edges[idx].end].r_it.coord;
		t_pt avg = pt_number_prod(pt_pt_sum(*start, *end), 0.5);
		*start = pt_pt_diff(*start, avg);
		*end = pt_pt_diff(*end, avg);
		*start = pt_pt_sum(*start, new_barycenter_coord);
		*end = pt_pt_sum(*end, new_barycenter_coord);

		if ((graph->flags & DADA_GRAPH_FLAG_CONNECTED_COMPONENTS) && (!graph->dont_reparse_or_update_connected_components)) 
			graph_update_connected_component_convex_hull(graph, graph->vertices[graph->edges[idx].start].connected_component_idx);
	}
}


void graph_move_edge_delta(t_dada_graph *graph, long idx, t_pt delta_coord)
{
	if (idx >= 0 && idx < graph->num_edges) {
		t_pt *start = &graph->vertices[graph->edges[idx].start].r_it.coord;
		t_pt *end = &graph->vertices[graph->edges[idx].end].r_it.coord;
		*start = pt_pt_sum(*start, delta_coord);
		*end = pt_pt_sum(*end, delta_coord);

		if ((graph->flags & DADA_GRAPH_FLAG_CONNECTED_COMPONENTS) && (!graph->dont_reparse_or_update_connected_components)) 
			graph_update_connected_component_convex_hull(graph, graph->vertices[graph->edges[idx].start].connected_component_idx);
	}
}




////// ******** METADATA ***********

t_dada_graph_metadata get_default_vertex_metadata(t_dada_graph *graph)
{
	switch (graph->edge_metadata_type) {
		case DADA_GRAPH_METADATA_PITCHNVEL:
			return DADA_DEFAULT_VERTEX_PITCHNVEL_METADATA;
		case DADA_GRAPH_METADATA_VANILLABOX:
			return DADA_DEFAULT_VERTEX_VANILLABOX_METADATA;
		case DADA_GRAPH_METADATA_OUTINNUM:
			return DADA_DEFAULT_VERTEX_OUTINNUM_METADATA;
        case DADA_GRAPH_METADATA_WEIGHT:
		case DADA_GRAPH_METADATA_DOUBLE:
			return DADA_DEFAULT_VERTEX_DOUBLE_METADATA;
        case DADA_GRAPH_METADATA_SCORE:
            return DADA_DEFAULT_VERTEX_SCORE_METADATA;
		default:
			return DADA_DEFAULT_VERTEX_LONG_METADATA;
	}
}

t_dada_graph_metadata get_default_edge_metadata(t_dada_graph *graph)
{
	switch (graph->edge_metadata_type) {
		case DADA_GRAPH_METADATA_PITCHNVEL:
			return DADA_DEFAULT_EDGE_PITCHNVEL_METADATA;
		case DADA_GRAPH_METADATA_VANILLABOX:
			return DADA_DEFAULT_EDGE_VANILLABOX_METADATA;
		case DADA_GRAPH_METADATA_OUTINNUM:
			return DADA_DEFAULT_EDGE_OUTINNUM_METADATA;
		case DADA_GRAPH_METADATA_DOUBLE:
        case DADA_GRAPH_METADATA_WEIGHT:
			return DADA_DEFAULT_EDGE_DOUBLE_METADATA;
        case DADA_GRAPH_METADATA_SCORE:
            return DADA_DEFAULT_VERTEX_SCORE_METADATA;
		default:
			return DADA_DEFAULT_EDGE_LONG_METADATA;
	}
}

t_dada_graph_metadata build_obj_metadata(void *obj)
{
    t_dada_graph_metadata p;
    p.m_obj = obj;
    return p;
}


t_dada_graph_metadata build_double_metadata(double num)
{
	t_dada_graph_metadata p;
	p.m_double = num;
	return p;
}

t_dada_graph_metadata build_long_metadata(long num)
{
	t_dada_graph_metadata p;
	p.m_long = num;
	return p;
}

t_dada_graph_metadata build_outinnum_metadata(long num_out, long num_in)
{
	t_dada_graph_metadata p;
	p.m_outinnum.num_in = num_in;
	p.m_outinnum.num_out = num_out;
	return p;
}

t_dada_graph_metadata build_vanillabox_metadata(t_symbol *type, long num_ins, long num_outs)
{
	t_dada_graph_metadata p;
	long i;
	p.m_vanillabox.type = type;
	p.m_vanillabox.num_ins = num_ins;
	p.m_vanillabox.num_outs = num_outs;
	for (i = 0; i < DADA_GRAPH_MAX_VANILLABOX_INS; i++)
		p.m_vanillabox.ins[i] = NULL;
//	for (i = 0; i < DADA_GRAPH_MAX_VANILLABOX_OUTS; i++)
//		p.m_vanillabox.outs[i] = NULL;
	return p;
}

t_dada_graph_metadata build_score_metadata(t_llll *score)
{
    t_dada_graph_metadata p;
    if (score)
        p.m_llllscore.ll = score;
    else
        p.m_llllscore.ll = llll_get();
    p.m_llllscore.label = _llllobj_sym_score;
    return p;
}


t_dada_graph_metadata build_pitchnvel_metadata(double pitch_mc, long vel)
{
	t_dada_graph_metadata p;
	p.m_pitchnvel.pitch_mc = pitch_mc;
	p.m_pitchnvel.velocity = vel;
	return p;
}


t_dada_graph_metadata build_llllnode_metadata(t_llll *ll, t_jrgba bgcolor, t_jrgba bordercolor, t_jrgba textcolor)
{
	t_dada_graph_metadata p;
	p.m_llllnode.ll = llll_clone(ll);
	p.m_llllnode.bgcolor = bgcolor;
	p.m_llllnode.bordercolor = bordercolor;
	p.m_llllnode.textcolor = textcolor;
	return p;
}

t_dada_graph_metadata clone_metadata(e_dada_graph_metadata_type type, t_dada_graph_metadata in)
{
	t_dada_graph_metadata out;
	long j;
	out = in;
	switch (type) {
		case DADA_GRAPH_METADATA_VANILLABOX:
			for (j = 0; j < DADA_GRAPH_MAX_VANILLABOX_INS; j++)
				out.m_vanillabox.ins[j] = llll_clone(in.m_vanillabox.ins[j]);
			break;
		case DADA_GRAPH_METADATA_LLLLNODE:
			out.m_llllnode.ll = llll_clone(in.m_llllnode.ll);
			break;
        case DADA_GRAPH_METADATA_SCORE:
            out.m_llllscore.ll = llll_clone(in.m_llllscore.ll);
            out.m_llllscore.label = in.m_llllscore.label;
            break;
		default:
			break;
	}
	return out;
}

char graph_change_edge_pitch(t_dada_graph *graph, long idx, double delta_mc) 
{
	if (idx >= 0 && idx < graph->num_edges)  {
		graph->edges[idx].data.m_pitchnvel.pitch_mc += delta_mc;
		return 0;
	}
	return 1;
}

char graph_change_edge_velocity(t_dada_graph *graph, long idx, double delta_vel) 
{
	if (idx >= 0 && idx < graph->num_edges)  {
		graph->edges[idx].data.m_pitchnvel.velocity = CLAMP(round(graph->edges[idx].data.m_pitchnvel.velocity + delta_vel), DADA_MIN_VELOCITY, DADA_MAX_VELOCITY);
		return 0;
	}
	return 1;
}

char graph_change_vertex_pitch(t_dada_graph *graph, long idx, double delta_mc) 
{
	if (idx >= 0 && idx < graph->num_vertices)  {
		graph->vertices[idx].data.m_pitchnvel.pitch_mc += delta_mc;
		return 0;
	}
	return 1;
}

char graph_change_vertex_velocity(t_dada_graph *graph, long idx, double delta_vel) 
{
	if (idx >= 0 && idx < graph->num_vertices)  {
		graph->vertices[idx].data.m_pitchnvel.velocity = CLAMP(round(graph->vertices[idx].data.m_pitchnvel.velocity + delta_vel), DADA_MIN_VELOCITY, DADA_MAX_VELOCITY);
		return 0;
	}
	return 1;
}

// deprecated: doesn't handle the case where a single box goes into multiple inlets of another box
long graph_vertices_to_edge(t_dada_graph *graph, long idx1, long idx2)
{
	long j;
	for (j = 0; j < graph->num_edges; j++)
		if ((graph->edges[j].start == idx1 && graph->edges[j].end == idx2) ||
			(graph->flags & DADA_GRAPH_FLAG_SYMMETRIC && graph->edges[j].start == idx2 && graph->edges[j].end == idx1))
			return j;
	
	return -1;
}

void graph_vertices_to_edges(t_dada_graph *graph, long idx1, long idx2, long *edges, long *num_edges, long max_num_edges)
{
	long j, num_ed = 0;
	for (j = 0; j < graph->num_edges && num_ed < max_num_edges; j++)
		if ((graph->edges[j].start == idx1 && graph->edges[j].end == idx2) ||
			(graph->flags & DADA_GRAPH_FLAG_SYMMETRIC && graph->edges[j].start == idx2 && graph->edges[j].end == idx1))
			edges[num_ed++] = j;
	
	*num_edges = num_ed;
}


char graph_are_vertices_connected(t_dada_graph *graph, long idx1, long idx2)
{
	return (graph_vertices_to_edge(graph, idx1, idx2) >= 0 ? true : false); 
}


t_llll *graph_vertex_get_vertices_adj_list(t_dada_graph *graph, long idx)
{
	t_llll *out = llll_get();
	long i;
	for (i = 0; i < graph->num_vertices; i++)
		if (graph_are_vertices_connected(graph, idx, i))
			llll_appendlong(out, i, 0, WHITENULL_llll);
	return out;
}

t_llll *graph_vertex_get_outgoing_edges_list(t_dada_graph *graph, long idx)
{
    t_llll *out = llll_get();
    long i;
    for (i = 0; i < graph->num_vertices; i++) {
        long j, num_edges = 0;
        long edges[10];
        graph_vertices_to_edges(graph, idx, i, edges, &num_edges, 10);
        for (j = 0; j < num_edges; j++)
            llll_appendlong(out, edges[j], 0, WHITENULL_llll);
    }
    return out;
}

t_llll *graph_vertex_get_incoming_edges_list(t_dada_graph *graph, long idx)
{
    t_llll *out = llll_get();
    long i;
    for (i = 0; i < graph->num_vertices; i++) {
        long j, num_edges = 0;
        long edges[10];
        graph_vertices_to_edges(graph, i, idx, edges, &num_edges, 10);
        for (j = 0; j < num_edges; j++)
            llll_appendlong(out, edges[j], 0, WHITENULL_llll);
    }

	return out;
}

char graph_delete_edge(t_dada_graph *graph, long j)
{
	if (j >= 0 && j < graph->num_edges) {

		if (j < graph->num_edges - 1) {
			edge_free(graph, j);
			sysmem_copyptr(&graph->edges[j + 1], &graph->edges[j], (graph->num_edges - j - 1) * sizeof(t_dada_graph_edge));
		}
		graph->num_edges --;

		if ((graph->flags & DADA_GRAPH_FLAG_CONNECTED_COMPONENTS) && (!graph->dont_reparse_or_update_connected_components)) 
			graph_parse_connected_components(graph);

		return 0;
	}
	
	
	return 1;
}

char graph_reverse_edge(t_dada_graph *graph, long j)
{
	if (j >= 0 && j < graph->num_edges) {
		
		if (!graph_are_vertices_connected(graph, graph->edges[j].end, graph->edges[j].start))
			graph_add_edge(graph, graph->edges[j].end, graph->edges[j].start, graph->edges[j].data);
		graph_delete_edge(graph, j);
		
		return 0;
	}
	
	return 1;
}


char graph_delete_edge_from_vertices(t_dada_graph *graph, long idx1, long idx2)
{
	if (idx1 >= 0 && idx1 < graph->num_edges && idx2 >= 0 && idx2 < graph->num_edges) {
		long j = graph_vertices_to_edge(graph, idx1, idx2);
		graph_delete_edge(graph, j);
		return 0;
	}
	return 1;
}

void update_indices_for_vertex_deletion(t_dada_graph *graph, long deleted_idx)
{
	long i, j;
	for (i = 0; i < graph->num_edges; i++) {
		if (graph->edges[i].start > deleted_idx)
			graph->edges[i].start --;
		if (graph->edges[i].end > deleted_idx)
			graph->edges[i].end --;
	}
	
	for (i = 0; i < graph->num_connected_components; i++) {
		for (j = 0; j < graph->connected_components[i].num_vertices; j++)
			if (graph->connected_components[i].vertices[j] > deleted_idx)
				graph->connected_components[i].vertices[j]--;
	}
}


char graph_delete_vertex(t_dada_graph *graph, long idx, char preserve_edges)
{
	if (idx >= 0 && idx < graph->num_vertices) {
		long i, j;

        char temp = graph->dont_reparse_or_update_connected_components;
        graph->dont_reparse_or_update_connected_components = true;
        
		if (preserve_edges) {
			for (i = 0; i < graph->num_edges; i++) {
				if (graph->edges[i].end == idx) {
					for (j = 0; j < graph->num_edges; j++) {
						if (graph->edges[j].start == idx)
							if (!graph_are_vertices_connected(graph, graph->edges[i].start, graph->edges[j].end))
								graph_add_edge(graph, graph->edges[i].start, graph->edges[j].end, graph->edges[i].data);
					}
				}
			}
		}
		
		for (i = 0; i < graph->num_edges; i++) 
			if (graph->edges[i].end == idx || graph->edges[i].start == idx) {
				graph_delete_edge(graph, i);
				i--;
			}

		if (idx < graph->num_vertices - 1) {
			update_indices_for_vertex_deletion(graph, idx);

			// overwriting memory
			vertex_free(graph, idx);
			sysmem_copyptr(&graph->vertices[idx + 1], &graph->vertices[idx], (graph->num_vertices - idx - 1) * sizeof(t_dada_graph_vertex));
		}
		
		graph->num_vertices --;

        graph->dont_reparse_or_update_connected_components = temp;
		
		if ((graph->flags & DADA_GRAPH_FLAG_CONNECTED_COMPONENTS) && (!graph->dont_reparse_or_update_connected_components)) 
			graph_parse_connected_components(graph);

		return 0;
	}
	return 1;
}


// point is between 0 and 1
t_dada_graph_metadata graph_metadata_interp(t_dada_graph *graph, e_dada_graph_metadata_type type, t_dada_graph_metadata m1, t_dada_graph_metadata m2, double point)
{
	t_dada_graph_metadata res;
	switch (type) {
		case DADA_GRAPH_METADATA_PITCHNVEL:
			res.m_pitchnvel.pitch_mc = rescale(point, 0., 1., m1.m_pitchnvel.pitch_mc, m2.m_pitchnvel.pitch_mc);
			res.m_pitchnvel.velocity = CLAMP(round(rescale(point, 0., 1., m1.m_pitchnvel.velocity, m2.m_pitchnvel.velocity)), DADA_MIN_VELOCITY, DADA_MAX_VELOCITY);
			break;
		default:
			res = clone_metadata(type, m1);
			break;
	}
	return res;
}


char graph_split_edge(t_dada_graph *graph, long idx, t_pt split_point, long *edge1_idx, long *edge2_idx, double vertex_width, double vertex_height)
{
    if (idx >= 0 && idx < graph->num_edges) {
        long vert1 = graph->edges[idx].start;
        long vert2 = graph->edges[idx].end;
        t_pt pt1 = graph->vertices[vert1].r_it.coord;
        t_pt pt2 = graph->vertices[vert2].r_it.coord;
        t_pt diff = pt_pt_diff(pt2, pt1);
        double norm_diff = pt_norm(diff);
        long old_num_verts = graph->num_vertices;
        t_dada_graph_metadata m = graph->edges[idx].data;
        
        char temp = graph->dont_reparse_or_update_connected_components;
        graph->dont_reparse_or_update_connected_components = true;
        
        // adding vertex
        long new_idx = graph_add_vertex(graph, split_point,
                                        (norm_diff != 0 ? graph_metadata_interp(graph, graph->vertex_metadata_type, graph->vertices[vert1].data, graph->vertices[vert2].data, pt_pt_distance(split_point, pt1) / pt_norm(diff)) : graph->vertices[vert2].data));
        graph->vertices[new_idx].r_it.width = vertex_width;
        graph->vertices[new_idx].r_it.height = vertex_height;
        if (graph->flags & DADA_GRAPH_FLAG_CONNECTED_COMPONENTS)
            graph_append_vertex_to_connected_component(graph, graph->vertices[vert1].connected_component_idx, new_idx);
        
        
        // modifying original edge
        graph->edges[idx].end = old_num_verts;
    
        // adding new edge
        long new_edge = graph_add_edge(graph, old_num_verts, vert2, clone_metadata(graph->edge_metadata_type, m));
        
        if (edge1_idx) *edge1_idx = idx;
        if (edge2_idx) *edge2_idx = new_edge;
        
        graph->dont_reparse_or_update_connected_components = temp;
        
        if ((graph->flags & DADA_GRAPH_FLAG_CONNECTED_COMPONENTS) && (!graph->dont_reparse_or_update_connected_components))
            graph_update_connected_component_convex_hull(graph, graph->vertices[vert1].connected_component_idx);
        
        return 0;
    }
    return 1;
}

char graph_subdivide_edge(t_dada_graph *graph, long idx, long num_parts, long *new_edge_start_idx, long *new_edge_end_idx, double vertex_width, double vertex_height)
{
	if (idx >= 0 && idx < graph->num_edges && num_parts >= 2) {
		long vert1 = graph->edges[idx].start;
		long vert2 = graph->edges[idx].end;
		t_pt pt1 = graph->vertices[vert1].r_it.coord;
		t_pt pt2 = graph->vertices[vert2].r_it.coord;
		t_pt diff = pt_pt_diff(pt2, pt1);
		long i;
		long old_num_verts = graph->num_vertices;
		t_dada_graph_metadata m = graph->edges[idx].data;
		
        char temp = graph->dont_reparse_or_update_connected_components;
		graph->dont_reparse_or_update_connected_components = true;

		// adding vertices
        for (i = 1; i < num_parts; i++) {
            long new_idx = graph_add_vertex(graph, pt_pt_sum(pt1, pt_number_prod(diff, (double)i/num_parts)),
                                            graph_metadata_interp(graph, graph->vertex_metadata_type, graph->vertices[vert1].data, graph->vertices[vert2].data, (double)i/num_parts));
            graph->vertices[new_idx].r_it.width = vertex_width;
            graph->vertices[new_idx].r_it.height = vertex_height;
            if (graph->flags & DADA_GRAPH_FLAG_CONNECTED_COMPONENTS)
                graph_append_vertex_to_connected_component(graph, graph->vertices[vert1].connected_component_idx, new_idx);
		}
			
		// modifying original edge
		graph->edges[idx].end = old_num_verts;
        if (graph->edge_metadata_type == DADA_GRAPH_METADATA_OUTINNUM) graph->edges[idx].data.m_outinnum.num_in = 0;
			
        long new_edge_idx, first_new_edge_idx = -1;
        
		// adding edges
        for (i = 1; i < num_parts - 1; i++) {
			new_edge_idx = graph_add_edge(graph, old_num_verts + i - 1, old_num_verts + i, clone_metadata(graph->edge_metadata_type, m));
            if (first_new_edge_idx < 0) first_new_edge_idx = new_edge_idx;
            if (graph->edge_metadata_type == DADA_GRAPH_METADATA_OUTINNUM) graph->edges[new_edge_idx].data.m_outinnum.num_in = 0;
        }

		new_edge_idx = graph_add_edge(graph, old_num_verts + num_parts - 2, vert2, clone_metadata(graph->edge_metadata_type, m));
        if (graph->edge_metadata_type == DADA_GRAPH_METADATA_OUTINNUM) graph->edges[new_edge_idx].data.m_outinnum.num_in = 0;

        if (first_new_edge_idx < 0) first_new_edge_idx = new_edge_idx;
        if (new_edge_start_idx) *new_edge_start_idx = first_new_edge_idx;
        if (new_edge_end_idx) *new_edge_end_idx = new_edge_idx;

		graph->dont_reparse_or_update_connected_components = temp;

		if ((graph->flags & DADA_GRAPH_FLAG_CONNECTED_COMPONENTS) && (!graph->dont_reparse_or_update_connected_components)) 
			graph_update_connected_component_convex_hull(graph, graph->vertices[vert1].connected_component_idx);
		
		return 0;
	}
	return 1;
}


char graph_extrude_edge(t_dada_graph *graph, long idx, long *new_edge_start_idx, long *new_edge_end_idx, double vertex_width, double vertex_height)
{
	if (idx >= 0 && idx < graph->num_edges) {
		long vert1 = graph->edges[idx].start;
		long vert2 = graph->edges[idx].end;
		t_pt pt1 = graph->vertices[vert1].r_it.coord;
		t_pt pt2 = graph->vertices[vert2].r_it.coord;
		t_pt diff = pt_pt_diff(pt2, pt1);
		t_dada_graph_metadata m = graph->edges[idx].data;
		
		t_pt middle_pt1 = pt_pt_sum(pt1, pt_number_prod(diff, 1./3.));
		t_pt middle_pt2 = pt_pt_sum(pt1, pt_number_prod(diff, 2./3.));
		
        char temp = graph->dont_reparse_or_update_connected_components;
		graph->dont_reparse_or_update_connected_components = true;

		t_dada_graph_metadata m1 = graph_metadata_interp(graph, graph->vertex_metadata_type, graph->vertices[vert1].data, graph->vertices[vert2].data, 1./3.);
		t_dada_graph_metadata m2 = graph_metadata_interp(graph, graph->vertex_metadata_type, graph->vertices[vert1].data, graph->vertices[vert2].data, 2./3.);
		long v1a = graph_add_vertex(graph, middle_pt1, m1);
		long v1b = graph_add_vertex(graph, middle_pt1, clone_metadata(graph->vertex_metadata_type, m1));
		long v2a = graph_add_vertex(graph, middle_pt2, m2);
		long v2b = graph_add_vertex(graph, middle_pt2, clone_metadata(graph->vertex_metadata_type, m2));

        graph->vertices[v1a].r_it.width = graph->vertices[v1b].r_it.width = graph->vertices[v2a].r_it.width = graph->vertices[v2b].r_it.width = vertex_width;
        graph->vertices[v1a].r_it.height = graph->vertices[v1b].r_it.height = graph->vertices[v2a].r_it.height = graph->vertices[v2b].r_it.height = vertex_height;
        
		if (graph->flags & DADA_GRAPH_FLAG_CONNECTED_COMPONENTS) {
			long con_cmp = graph->vertices[vert1].connected_component_idx;
			graph_append_vertex_to_connected_component(graph, con_cmp, v1a);
			graph_append_vertex_to_connected_component(graph, con_cmp, v1b);
			graph_append_vertex_to_connected_component(graph, con_cmp, v2a);
			graph_append_vertex_to_connected_component(graph, con_cmp, v2b);
		}

		// modifying original edge
		graph->edges[idx].end = v1a;

		// adding edges
        long new_edge_start, new_edge_end;
        new_edge_start = graph_add_edge(graph, v1a, v1b, clone_metadata(graph->edge_metadata_type, m));
		graph_add_edge(graph, v1b, v2a, clone_metadata(graph->edge_metadata_type, m));
		graph_add_edge(graph, v2a, v2b, clone_metadata(graph->edge_metadata_type, m));
		new_edge_end = graph_add_edge(graph, v2b, vert2, clone_metadata(graph->edge_metadata_type, m));

        if (new_edge_start_idx) *new_edge_start_idx = new_edge_start;
        if (new_edge_end_idx) *new_edge_end_idx = new_edge_end;

		graph->dont_reparse_or_update_connected_components = temp;

		if ((graph->flags & DADA_GRAPH_FLAG_CONNECTED_COMPONENTS) && (!graph->dont_reparse_or_update_connected_components)) 
			graph_update_connected_component_convex_hull(graph, graph->vertices[vert1].connected_component_idx);
		

		return 0;
	}
	return 1;
}


/// 0 based indices
long graph_add_connected_component(t_dada_graph *graph, long num_vertices, long *vertices)
{
	if (graph->num_connected_components >= graph->num_allocated_connected_components) {
		graph->num_allocated_connected_components += DADA_GRAPH_ALLOC_STEP;
		graph->connected_components = (t_dada_graph_connected_component *)bach_resizeptr(graph->connected_components, graph->num_allocated_connected_components * sizeof(t_dada_graph_connected_component));
	}
	
	graph->connected_components[graph->num_connected_components].num_vertices = num_vertices;
	graph->connected_components[graph->num_connected_components].flag = 0;
	graph->connected_components[graph->num_connected_components].vertices = (long *)bach_newptr(num_vertices * sizeof(long));
		
	long i;
	for (i = 0; i < num_vertices; i++) {
		graph->connected_components[graph->num_connected_components].vertices[i] = vertices[i];
		graph->vertices[vertices[i]].connected_component_idx = graph->num_connected_components;
	}
		
	graph->num_connected_components ++;

	graph_update_connected_component_convex_hull(graph, graph->num_connected_components - 1);

	return graph->num_connected_components - 1;
}


void dfs(t_dada_graph *graph, long vert, long comp_num)
{
	long i;
	for (i = 0; i < graph->num_edges; i++) {
		if (graph->edges[i].start == vert) {
			if (graph->vertices[graph->edges[i].end].connected_component_idx < 0) {
				graph->vertices[graph->edges[i].end].connected_component_idx = comp_num;
				dfs(graph, graph->edges[i].end, comp_num);
			}
		} else if ((graph->flags & DADA_GRAPH_FLAG_SYMMETRIC) && graph->edges[i].end == vert) {
			if (graph->vertices[graph->edges[i].start].connected_component_idx < 0) {
				graph->vertices[graph->edges[i].start].connected_component_idx = comp_num;
				dfs(graph, graph->edges[i].start, comp_num);
			}
		}
	}
}


// within this framework, this can be a "heavy" operation
void graph_parse_connected_components(t_dada_graph *graph)
{
	long i, j, curr_comp = 0; // depth-first search

	for (i = 0; i < graph->num_vertices; i++) 
		graph->vertices[i].connected_component_idx = -1;

	for (i = 0; i < graph->num_vertices; i++) {
		if (graph->vertices[i].connected_component_idx < 0) {
			graph->vertices[i].connected_component_idx = curr_comp;
			dfs(graph, i, curr_comp);
			curr_comp++;
		}
	}
	
	graph_free_connected_components(graph);
	graph->num_connected_components = 0;
	
	for (j = 0; j < curr_comp; j++) {
		long count_i = 0;
		for (i = 0; i < graph->num_vertices; i++) 
			if (graph->vertices[i].connected_component_idx == j) 
				count_i++;
		
		if (count_i > 0) {
			long *vertices = (long *)bach_newptr(count_i * sizeof(long));
			
			count_i = 0;
			for (i = 0; i < graph->num_vertices; i++) 
				if (graph->vertices[i].connected_component_idx == j)
					vertices[count_i++] = i;
			
			graph_add_connected_component(graph, count_i, vertices);
			
			bach_freeptr(vertices);
		}
	}
}


void graph_update_connected_component_convex_hull(t_dada_graph *graph, long idx)
{
	if (idx >= 0 && idx < graph->num_connected_components) {
		t_pt *pt = (t_pt *)bach_newptr(graph->connected_components[idx].num_vertices * sizeof(t_pt));
		long i;
		for (i = 0; i < graph->connected_components[idx].num_vertices; i++)
			pt[i] = graph->vertices[graph->connected_components[idx].vertices[i]].r_it.coord;
        
		find_convex_hull(graph->connected_components[idx].num_vertices, pt, &graph->connected_components[idx].poly);
		bach_freeptr(pt);
	}
}

long graph_coord_to_connected_component(t_dada_graph *graph, t_pt coord)
{
	long i;
	// 0-th component is the lowest one, so we run from the top to the bottom
	for (i = graph->num_connected_components - 1; i >= 0; i--) {
		if (is_pt_in_dadapolygon(coord, &graph->connected_components[i].poly))
			return i;
	}
	return -1;
}


char graph_delete_connected_component(t_dada_graph *graph, long idx)
{

	if (idx >= 0 && idx < graph->num_connected_components) {
		long i;

        char temp = graph->dont_reparse_or_update_connected_components;
		graph->dont_reparse_or_update_connected_components = true;

		for (i = 0; i < graph->connected_components[idx].num_vertices; i++)
			graph_delete_vertex(graph, graph->connected_components[idx].vertices[i], false);

		graph->dont_reparse_or_update_connected_components = temp;
			
		if (idx < graph->num_connected_components - 1) 
			sysmem_copyptr(&graph->connected_components[idx + 1], &graph->connected_components[idx], (graph->num_connected_components - idx - 1) * sizeof(t_dada_graph_connected_component));

		// renumber connected components
		for (i = 0; i < graph->num_vertices; i++)
			if (graph->vertices[i].connected_component_idx > idx)
				graph->vertices[i].connected_component_idx--;
		
		graph->num_connected_components --;

		return 0;
	}
	
	return 1;
}


void graph_move_connected_component_delta(t_dada_graph *graph, long idx, t_pt delta_coord)
{
	if (idx >= 0 && idx < graph->num_connected_components) {
		long i;
		for (i = 0; i < graph->connected_components[idx].num_vertices; i++) {
			t_pt *pt = &graph->vertices[graph->connected_components[idx].vertices[i]].r_it.coord;
			*pt = pt_pt_sum(*pt, delta_coord);
		}
		
		if (graph->flags & DADA_GRAPH_FLAG_CONNECTED_COMPONENTS)
			graph_update_connected_component_convex_hull(graph, idx);
	}
}

char graph_change_connected_component_pitch(t_dada_graph *graph, long idx, double delta_mc) 
{
	if (idx >= 0 && idx < graph->num_connected_components) {
		long j;
		for (j = 0; j < graph->num_edges; j++) 
			if (graph->vertices[graph->edges[j].start].connected_component_idx == idx)
				graph->edges[j].data.m_pitchnvel.pitch_mc += delta_mc;
		for (j = 0; j < graph->num_vertices; j++) 
			if (graph->vertices[j].connected_component_idx == idx)
				graph->vertices[j].data.m_pitchnvel.pitch_mc += delta_mc;
		return 0;
	}
	return 1;
}

char graph_change_connected_component_velocity(t_dada_graph *graph, long idx, double delta_vel) 
{
	if (idx >= 0 && idx < graph->num_connected_components) {
		long j;
		for (j = 0; j < graph->num_edges; j++) 
			if (graph->vertices[graph->edges[j].start].connected_component_idx == idx)
				graph->edges[j].data.m_pitchnvel.velocity = CLAMP(round(graph->edges[j].data.m_pitchnvel.velocity + delta_vel), DADA_MIN_VELOCITY, DADA_MAX_VELOCITY);
		for (j = 0; j < graph->num_vertices; j++) 
			if (graph->vertices[j].connected_component_idx == idx)
				graph->vertices[j].data.m_pitchnvel.velocity = CLAMP(round(graph->vertices[j].data.m_pitchnvel.velocity + delta_vel), DADA_MIN_VELOCITY, DADA_MAX_VELOCITY);
		return 0;
	}
	return 1;
}



long graph_append_vertex_to_connected_component(t_dada_graph *graph, long connected_component_idx, long vertex_idx)
{
	if (connected_component_idx >= 0 && connected_component_idx < graph->num_connected_components) {
		long curr_num_vert = graph->connected_components[connected_component_idx].num_vertices;
		graph->connected_components[connected_component_idx].vertices = (long *)bach_resizeptr(graph->connected_components[connected_component_idx].vertices, (curr_num_vert + 1) * sizeof(long));
		graph->connected_components[connected_component_idx].vertices[curr_num_vert] = vertex_idx;
		graph->connected_components[connected_component_idx].num_vertices++;
		
		graph->vertices[vertex_idx].connected_component_idx = connected_component_idx;
		
		if ((graph->flags & DADA_GRAPH_FLAG_CONNECTED_COMPONENTS) && (!graph->dont_reparse_or_update_connected_components)) 
			graph_update_connected_component_convex_hull(graph, connected_component_idx);
		
		return vertex_idx;
	}
	return -1;
}

long graph_duplicate_vertex(t_dada_graph *graph, long idx, t_pt new_coords, char add_edge_from_old_to_new) 
{
	if (idx >= 0 && idx < graph->num_vertices) {
		long new_idx = graph_add_vertex(graph, new_coords, clone_metadata(graph->vertex_metadata_type, graph->vertices[idx].data));
		graph->vertices[new_idx].flag = 0;
        graph->vertices[new_idx].r_it.width = graph->vertices[idx].r_it.width;
        graph->vertices[new_idx].r_it.height = graph->vertices[idx].r_it.height;

        char temp = graph->dont_reparse_or_update_connected_components;
		graph->dont_reparse_or_update_connected_components = true;
		graph_append_vertex_to_connected_component(graph, graph->vertices[idx].connected_component_idx, new_idx);

		//add edge
		if (add_edge_from_old_to_new)
			graph_add_edge(graph, idx, new_idx, get_default_edge_metadata(graph));

        graph->dont_reparse_or_update_connected_components = temp;
		
		if ((graph->flags & DADA_GRAPH_FLAG_CONNECTED_COMPONENTS) && (!graph->dont_reparse_or_update_connected_components)) 
			graph_update_connected_component_convex_hull(graph, graph->vertices[idx].connected_component_idx);
		return new_idx;
	}
	return -1;
}


char graph_rotate_connected_component(t_dada_graph *graph, long idx, double angle) 
{
	if (idx >= 0 && idx < graph->num_connected_components) {
		long j;
		t_pt center = get_dadapolygon_barycenter(&graph->connected_components[idx].poly);
		t_jmatrix rot;

		jgraphics_matrix_init_rotate(&rot, angle);
		
		for (j = 0; j < graph->connected_components[idx].num_vertices; j++)  {
			t_pt *this_pt = &graph->vertices[graph->connected_components[idx].vertices[j]].r_it.coord;
			*this_pt = pt_pt_diff(*this_pt, center);
			jgraphics_matrix_transform_point(&rot, &this_pt->x, &this_pt->y);
			*this_pt = pt_pt_sum(*this_pt, center);
		}

		graph_update_connected_component_convex_hull(graph, idx);

		return 0;
	}
	return 1;
}


char graph_scale_connected_component(t_dada_graph *graph, long idx, double factor) 
{
	if (idx >= 0 && idx < graph->num_connected_components) {
		long j;
		t_pt center = get_dadapolygon_barycenter(&graph->connected_components[idx].poly);
		for (j = 0; j < graph->connected_components[idx].num_vertices; j++)  {
			t_pt *this_pt = &graph->vertices[graph->connected_components[idx].vertices[j]].r_it.coord;
			*this_pt = pt_pt_diff(*this_pt, center);
			*this_pt = pt_number_prod(*this_pt, factor);
			*this_pt = pt_pt_sum(*this_pt, center);
		}
		
		graph_update_connected_component_convex_hull(graph, idx);
		
		return 0;
	}
	return 1;
}


long graph_duplicate_connected_component(t_dada_graph *graph, long idx, t_pt delta_pt)
{
	if (idx >= 0 && idx < graph->num_connected_components) {
		long i;
		long num_verts = graph->connected_components[idx].num_vertices;
		long *new_verts = (long *)bach_newptrclear(num_verts * sizeof(long));		
		long *mapsto_idx = (long *)bach_newptrclear(graph->num_vertices * sizeof(long));
		
        char temp = graph->dont_reparse_or_update_connected_components;
		graph->dont_reparse_or_update_connected_components = true;
		
		for (i = 0; i < num_verts; i++) {
			long this_vert = graph->connected_components[idx].vertices[i];
			mapsto_idx[this_vert] = new_verts[i] = graph_add_vertex(graph, pt_pt_sum(graph->vertices[this_vert].r_it.coord, delta_pt), clone_metadata(graph->vertex_metadata_type, graph->vertices[this_vert].data));
		}
		
		for (i = 0; i < graph->num_edges; i++)
			if (graph->vertices[graph->edges[i].start].connected_component_idx == idx) 
				graph_add_edge(graph, mapsto_idx[graph->edges[i].start], mapsto_idx[graph->edges[i].end], graph->edges[i].data, graph->edges[i].flag);
		
		graph->dont_reparse_or_update_connected_components = temp;
		
		graph_add_connected_component(graph, num_verts, new_verts);
		
		bach_freeptr(mapsto_idx);
		bach_freeptr(new_verts);
		
		return graph->num_connected_components - 1;
	}
	return -1;
}


// sets the index to 0 (= bottommost one)
long graph_connected_component_send_to_back(t_dada_graph *graph, long idx)
{
	if (idx >= 0 && idx < graph->num_connected_components) {
		if (idx != 0 && graph->num_connected_components > 1) {
			t_dada_graph_connected_component cc = graph->connected_components[idx];
			sysmem_copyptr(&graph->connected_components[0], &graph->connected_components[1], idx * sizeof(t_dada_graph_connected_component));
			graph->connected_components[0] = cc;
			
			// adjust all values
			long i;
			for (i = 0; i < graph->num_vertices; i++) {
				if (graph->vertices[i].connected_component_idx == idx)
					graph->vertices[i].connected_component_idx = 0;
				else if (graph->vertices[i].connected_component_idx < idx)
					graph->vertices[i].connected_component_idx++;
			}
		}
		return 0;
	}
	return 1;
}


// Sets the index to the highmost one (= front)
long graph_connected_component_bring_to_front(t_dada_graph *graph, long idx)
{
	if (idx >= 0 && idx < graph->num_connected_components) {
		if (idx != graph->num_connected_components - 1 && graph->num_connected_components > 1) {
			t_dada_graph_connected_component cc = graph->connected_components[idx];
			sysmem_copyptr(&graph->connected_components[idx + 1], &graph->connected_components[idx], (graph->num_connected_components - idx - 1) * sizeof(t_dada_graph_connected_component));
			graph->connected_components[graph->num_connected_components - 1] = cc;
			
			// adjust all values
			long i;
			for (i = 0; i < graph->num_vertices; i++) {
				if (graph->vertices[i].connected_component_idx == idx)
					graph->vertices[i].connected_component_idx = graph->num_connected_components - 1;
				else if (graph->vertices[i].connected_component_idx > idx)
					graph->vertices[i].connected_component_idx--;
			}
		}
		return 0;
	}
	return 1;
}
