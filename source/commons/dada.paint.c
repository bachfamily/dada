/**
	@file
	dada.paint.c
	Paint and display utilities for dada library

	by Daniele Ghisi
*/

#include "dada.paint.h"
#include "dada.geometry.h"

void ezpaint_note_with_staff(t_object *x, t_jgraphics *g, t_object *view, double midicents, e_accidentals_preferences accpref, long tonedivision, t_pt staff_topleft, double staff_width, double fontsize, double note_x_pos, char shift_note_for_accidentals, t_jrgba *staffcolor, t_jrgba *clefcolor, t_jrgba *notecolor)
{
	double step_size = fontsize / 8.;
	double fontzoom = fontsize / 24.;
	t_jfont *jf = jfont_create_debug("November for bach", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, fontsize);
	
	// 1. get screen representation (midicents + accidentals)
	long screen_mc;
	t_rational screen_acc;
	double screen_acc_double;
	mc_to_screen_approximations_do(tonedivision, accpref, midicents, &screen_mc, &screen_acc, NULL, NULL);
	screen_acc_double = rat2double(screen_acc);
	
	// 2. find suitable clef
	e_clefs clef; 
	if (screen_mc < 2400)
		clef = k_CLEF_F15mb;
	else if (screen_mc < 3600)
		clef = k_CLEF_F8vb;
	else if (screen_mc < 6000)
		clef = k_CLEF_F;
	else if (screen_mc < 8400)
		clef = k_CLEF_G;
	else if (screen_mc < 9600)
		clef = k_CLEF_G8va;
	else 
		clef = k_CLEF_G15ma;
	
	// 3. paint staff
	long i;
	double liney = staff_topleft.y;
	for (i = 0; i < 5; i++, liney += 2 * step_size)
		paint_line(g, *staffcolor, staff_topleft.x, liney, staff_topleft.x + staff_width, liney, 1);
	
	// 4. paint clef
	long outlen_clef;
	unsigned short clef_char = (clef == k_CLEF_F || clef == k_CLEF_F8vb || clef == k_CLEF_F15mb) ? '?' : 'A';
	char *clefchar_utf = charset_unicodetoutf8_debug(&clef_char, 1, &outlen_clef);
	double y_pt = staff_topleft.y + 9.35 * step_size - fontsize * 1.5;
	if (clef == k_CLEF_F || clef == k_CLEF_F8vb || clef == k_CLEF_F15mb)
		y_pt -= 4 * step_size;
	write_text(g, jf, *clefcolor, clefchar_utf, staff_topleft.x, y_pt, 50 * fontsize, 10 * fontsize, JGRAPHICS_TEXT_JUSTIFICATION_TOPLEFT, true, false);
	if (clef == k_CLEF_F8vb || clef == k_CLEF_F15mb || clef == k_CLEF_G8va || clef == k_CLEF_G15ma) {
		t_jfont *jf_number = jfont_create_debug("Arial", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, fontsize * 0.4);
		write_text(g, jf_number, *clefcolor, clef == k_CLEF_F8vb || clef == k_CLEF_G8va ? "8" : "15", staff_topleft.x,
				   clef == k_CLEF_F8vb || clef == k_CLEF_F15mb ? staff_topleft.y + 5 * step_size : staff_topleft.y - 5.65 * step_size, 0.8 * fontsize, 40, JGRAPHICS_TEXT_JUSTIFICATION_TOP | JGRAPHICS_TEXT_JUSTIFICATION_HCENTERED, true, false);
		jfont_destroy_debug(jf_number);
	}
	bach_freeptr(clefchar_utf);

	
	// 5. find note position
	double note_y_pos = 0;
	long scalepos = midicents_to_diatsteps_from_middleC(NULL, screen_mc), scalepos_min, scalepos_max;
	switch (clef) {
		case k_CLEF_F:	note_y_pos = staff_topleft.y - (scalepos - (-2)) * step_size; break;
		case k_CLEF_F8vb:	note_y_pos = staff_topleft.y - (scalepos - (-9)) * step_size; break;
		case k_CLEF_F15mb:	note_y_pos = staff_topleft.y - (scalepos - (-16)) * step_size; break;
		case k_CLEF_G8va:	note_y_pos = staff_topleft.y - (scalepos - 17) * step_size; break;
		case k_CLEF_G15ma:	note_y_pos = staff_topleft.y - (scalepos - 24) * step_size; break;
		default:	note_y_pos = staff_topleft.y - (scalepos - 10) * step_size; break;
	}
	note_y_pos += (-26.7 + 1) * fontzoom;
    
	// 6. paint accidental, if any
	unsigned short accidental_char = get_default_accidental_char(screen_acc_double);
	if (accidental_char != 0) {
		t_jfont *jf_acc = jfont_create_debug("November for bach", JGRAPHICS_FONT_SLANT_NORMAL, JGRAPHICS_FONT_WEIGHT_NORMAL, fontsize);
		long outlen_acc;
		double w, h;
		char *accchar_utf = charset_unicodetoutf8_debug(&accidental_char, 1, &outlen_acc);
		double acc_y_pos = note_y_pos;
		double temp = note_x_pos;
		
		jfont_text_measure(jf_acc, accchar_utf, &w, &h);
		
		if (shift_note_for_accidentals)
			note_x_pos += w + CONST_UX_ACC_SEPARATION_FROM_NOTE * fontzoom;
		else
			temp -= w + CONST_UX_ACC_SEPARATION_FROM_NOTE * fontzoom;
		
		write_text(g, jf_acc, *notecolor, accchar_utf, temp, acc_y_pos, w + 20, h + 20, JGRAPHICS_TEXT_JUSTIFICATION_TOPLEFT, true, false);
		
		bach_freeptr(accchar_utf);
		jfont_destroy_debug(jf_acc);
	}
	
	// 7. paint ledger lines
	long mc_min, mc_max, temp;
	get_staff_range_mc(clef, &mc_min, &mc_max);
	scalepos_min = midicents_to_diatsteps_from_middleC(NULL, mc_min);
	scalepos_max = midicents_to_diatsteps_from_middleC(NULL, mc_max);
	temp = scalepos;
	while (temp - scalepos_max >= 2) {
		double ledgerline_y = staff_topleft.y - ((temp - scalepos_max) / 2) * (2 * step_size);
		paint_line(g, *staffcolor, note_x_pos - 3 * fontzoom, ledgerline_y, note_x_pos + 10 * fontzoom, ledgerline_y, 1);
		temp -= 2;
	}
	while (scalepos_min - temp >= 2) {
		double ledgerline_y = staff_topleft.y + 8 * step_size + ((scalepos_min - temp) / 2) * (2 * step_size);
		paint_line(g, *staffcolor, note_x_pos - 3 * fontzoom, ledgerline_y, note_x_pos + 10 * fontzoom, ledgerline_y, 1);
		temp += 2;
	}
	
	// 8. paint note
	long outlen_note;
	unsigned short note_char = 'U';
	char *notechar_utf = charset_unicodetoutf8_debug(&note_char, 1, &outlen_note);
	write_text(g, jf, *notecolor, notechar_utf, note_x_pos - 0.7 * fontzoom, note_y_pos, 10 * fontsize, 10 * fontsize, JGRAPHICS_TEXT_JUSTIFICATION_TOPLEFT, true, false);
	bach_freeptr(notechar_utf);

	
	jfont_destroy_debug(jf);
}

void paint_rectangle_fast(t_jgraphics *g, t_jrgba *bordercolor, t_jrgba *fillcolor, double x, double y, double width, double height, double borderwidth)
{
	jgraphics_set_source_jrgba(g, fillcolor);
	jgraphics_rectangle_fill_fast(g, x, y, width, height);
	jgraphics_set_source_jrgba(g, bordercolor);
	jgraphics_rectangle_draw_fast(g, x, y, width, height, borderwidth);
}

void paint_square_fast(t_jgraphics *g, t_jrgba *bordercolor, t_jrgba *fillcolor, t_pt center, double halfside, double borderwidth)
{
	paint_rectangle_fast(g, bordercolor, fillcolor, center.x - halfside, center.y - halfside, halfside * 2, halfside * 2, borderwidth);
}

void paint_square(t_jgraphics *g, t_jrgba *bordercolor, t_jrgba *fillcolor, t_pt center, double halfside, double borderwidth)
{
	paint_rectangle(g, *bordercolor, *fillcolor, center.x - halfside, center.y - halfside, halfside * 2, halfside * 2, borderwidth);
}




void paint_hexagon(t_jgraphics *g, t_jrgba *bordercolor, t_jrgba *fillcolor, t_pt center, double circumradius, double borderwidth, char pointy_topped)
{
	double circumradius_over_2 = circumradius / 2.;
	double circumradius_sqrt3_2 = circumradius * SQRT3OVER2;
	if (fillcolor) 
		jgraphics_set_source_jrgba(g, fillcolor);
	if (pointy_topped) {
		jgraphics_move_to(g, center.x + circumradius_sqrt3_2, center.y - circumradius_over_2);
		jgraphics_line_to(g, center.x, center.y - circumradius);
		jgraphics_line_to(g, center.x - circumradius_sqrt3_2, center.y - circumradius_over_2);
		jgraphics_line_to(g, center.x - circumradius_sqrt3_2, center.y + circumradius_over_2);
		jgraphics_line_to(g, center.x, center.y + circumradius);
		jgraphics_line_to(g, center.x + circumradius_sqrt3_2, center.y + circumradius_over_2);
	} else {
		jgraphics_move_to(g, center.x + circumradius, center.y);
		jgraphics_line_to(g, center.x + circumradius_over_2, center.y - circumradius_sqrt3_2);
		jgraphics_line_to(g, center.x - circumradius_over_2, center.y - circumradius_sqrt3_2);
		jgraphics_line_to(g, center.x - circumradius, center.y);
		jgraphics_line_to(g, center.x - circumradius_over_2, center.y + circumradius_sqrt3_2);
		jgraphics_line_to(g, center.x + circumradius_over_2, center.y + circumradius_sqrt3_2);
	}
	jgraphics_close_path(g); 
	if (fillcolor) 
		jgraphics_fill_preserve(g);
	jgraphics_set_line_width(g, borderwidth);
	if (bordercolor)
		jgraphics_set_source_jrgba(g, bordercolor);
	jgraphics_stroke(g);
}

void paint_regular_polygon(t_jgraphics *g, long num_vertices, t_jrgba *bordercolor, t_jrgba *fillcolor, t_pt center, double circumradius, double borderwidth)
{
    // x[n] = r * cos(2*pi*n/N)
    // y[n] = r * sin(2*pi*n/N)
    long j;
    jgraphics_move_to(g, center.x, center.y - circumradius);
    if (fillcolor)
        jgraphics_set_source_jrgba(g, fillcolor);
    for (j = 1; j < num_vertices; j++)
        jgraphics_line_to(g, center.x + circumradius * sin(j * TWOPI / num_vertices), center.y - circumradius * cos(j * TWOPI / num_vertices));
    jgraphics_close_path(g);
    if (fillcolor) {
        if (bordercolor)
            jgraphics_fill_preserve(g);
        else
            jgraphics_fill(g);
    }
    jgraphics_set_line_width(g, borderwidth);
    if (bordercolor) {
        jgraphics_set_source_jrgba(g, bordercolor);
        jgraphics_stroke(g);
    }
}

void paint_cross(t_jgraphics *g, t_jrgba *color, t_pt center, double size, double linewidth)
{
	paint_line(g, *color, center.x - size, center.y - size, center.x + size, center.y + size, linewidth);
	paint_line(g, *color, center.x - size, center.y + size, center.x + size, center.y - size, linewidth);
}


void paint_pointed_corolla(t_jgraphics *g, t_jrgba *color, t_pt center, double radius, double num_points, double pointradius)
{
	long i;
	double angle = TWOPI/num_points;
	for (i = 0; i < num_points; i++)
		paint_circle_filled(g, *color, center.x + radius * cos(i * angle), center.y + radius * sin(i * angle), pointradius);
}



void paint_line_advanced(t_jgraphics *g, t_jrgba color, t_pt start, t_pt end, double linewidth, e_dada_line_style style, 
						 char show_arrows, double arrow_size, char *label, t_jfont *jf_label, double curve_amount)
{
	t_pt diff = pt_pt_diff(end, start);
	t_pt middle;
	
	switch (style) {
		case DADA_LINE_CURVE:
			paint_curve_advanced(g, color, start, end, linewidth, curve_amount, show_arrows, arrow_size, label, jf_label);
			break;

		case DADA_LINE_SEGMENTED:
			middle = pt_pt_sum(start, pt_number_prod(diff, 0.5));
			if (fabs(diff.x) > fabs(diff.y)) {
				paint_line(g, color, start.x, start.y, middle.x, start.y, linewidth);
				paint_line(g, color, middle.x, start.y, middle.x, end.y, linewidth);
				paint_line(g, color, middle.x, end.y, end.x, end.y, linewidth);
				diff = build_pt(diff.x/2., 0);
				middle = pt_pt_sum(build_pt(middle.x, end.y), pt_number_prod(diff, 0.1));
			} else {
				paint_line(g, color, start.x, start.y, start.x, middle.y, linewidth);
				paint_line(g, color, start.x, middle.y, end.x, middle.y, linewidth);
				paint_line(g, color, end.x, middle.y, end.x, end.y, linewidth);
				// for the arrow
				diff = build_pt(0, diff.y/2.);
				middle = pt_pt_sum(build_pt(end.x, middle.y), pt_number_prod(diff, 0.1));
			}

			if (label && jf_label) 
				write_text(g, jf_label, color, label, middle.x-500, middle.y-500 - 14, 1000, 1000, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, true, false);

			break;
		default:
			middle = pt_pt_sum(start, pt_number_prod(diff, 0.53)); // for the arrow
			paint_line(g, color, start.x, start.y, end.x, end.y, linewidth);

			if (label && jf_label) 
				write_text(g, jf_label, color, label, middle.x-500, middle.y-500 - 14, 1000, 1000, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, true, false);
			
			break;
	}
	
	if (show_arrows && style != DADA_LINE_CURVE) { // for curves we have already painted the arrow
		// paint arrow
		t_jmatrix mat;
		jgraphics_matrix_init_rotate(&mat, PIOVERTWO);
		
		t_pt normalized_diff = pt_number_prod(pt_normalize(diff), arrow_size);
		t_pt tip = pt_pt_sum(middle, normalized_diff);
		t_pt semibase = normalized_diff;
		
		jgraphics_matrix_transform_point(&mat, &semibase.x, &semibase.y);
		semibase.x /=2.;
		semibase.y /=2.;
		
		t_pt base1 = pt_pt_sum(middle, semibase);
		t_pt base2 = pt_pt_diff(middle, semibase);
		
		paint_triangle(g, color, color, tip.x, tip.y, base1.x, base1.y, base2.x, base2.y, 0);
	}	
}


char is_pt_in_curve_advanced_shape(t_pt pt, t_pt start, t_pt end, double linewidth, double curve_height)
{
	t_pt diff = pt_pt_diff(end, start);
	t_pt cp1, cp2;
	
	// getting control points.
	cp1 = pt_pt_sum(start, pt_number_prod(diff, 0.33));
	cp2 = pt_pt_sum(start, pt_number_prod(diff, 0.67));
	t_pt perpendicular = pt_normalize(build_pt(diff.y, -diff.x));
	cp1 = pt_pt_sum(cp1, pt_number_prod(perpendicular, curve_height));
	cp2 = pt_pt_sum(cp2, pt_number_prod(perpendicular, curve_height));

	t_pt subd1 = get_single_bezier_subdivision_point(start, cp1, cp2, end, 0.25);
	t_pt subd2 = get_single_bezier_subdivision_point(start, cp1, cp2, end, 0.5);
	t_pt subd3 = get_single_bezier_subdivision_point(start, cp1, cp2, end, 0.75);
	
	return (is_pt_in_line_shape_improved(pt.x, pt.y, start.x, start.y, subd1.x, subd1.y, linewidth) ||
			is_pt_in_line_shape_improved(pt.x, pt.y, subd1.x, subd1.y, subd2.x, subd2.y, linewidth) ||
			is_pt_in_line_shape_improved(pt.x, pt.y, subd2.x, subd2.y, subd3.x, subd3.y, linewidth) ||
			is_pt_in_line_shape_improved(pt.x, pt.y, subd3.x, subd3.y, end.x, end.y, linewidth));
}

void paint_curve_advanced(t_jgraphics *g, t_jrgba color, t_pt start, t_pt end, double linewidth, double curve_height, char paint_arrow, 
						  double arrow_size, char *label, t_jfont *jf)
{
	t_pt diff = pt_pt_diff(end, start);
	t_pt cp1, cp2;
	
	// getting control points.
	cp1 = pt_pt_sum(start, pt_number_prod(diff, 0.33));
	cp2 = pt_pt_sum(start, pt_number_prod(diff, 0.67));
	t_pt perpendicular = pt_normalize(build_pt(diff.y, -diff.x));
	cp1 = pt_pt_sum(cp1, pt_number_prod(perpendicular, curve_height));
	cp2 = pt_pt_sum(cp2, pt_number_prod(perpendicular, curve_height));
	
//	paint_circle_filled(g, color, cp1.x, cp1.y, 2);
//	paint_circle_filled(g, color, cp2.x, cp2.y, 2);
	
	jgraphics_set_source_jrgba(g, &color); 
	jgraphics_set_line_width(g, linewidth);
	jgraphics_move_to(g, start.x, start.y);
	jgraphics_curve_to(g, cp1.x, cp1.y, cp2.x, cp2.y, end.x, end.y);
	jgraphics_stroke(g);

	if (label && jf) {
		t_pt middle = pt_pt_sum(start, pt_number_prod(diff, 0.5));
		middle = pt_pt_sum(middle, pt_number_prod(perpendicular, curve_height));
		write_text(g, jf, color, label, middle.x-500, middle.y-500, 1000, 1000, JGRAPHICS_TEXT_JUSTIFICATION_CENTERED, true, false);
	}

	
	if (paint_arrow) {
		// paint arrow
		t_jmatrix mat;
		jgraphics_matrix_init_rotate(&mat, PIOVERTWO);
		
		diff = pt_pt_diff(end, cp2);
		
		t_pt normalized_diff = pt_number_prod(pt_normalize(diff), arrow_size);
		t_pt tip = end; // pt_pt_sum(middle, normalized_diff);
		t_pt middle = pt_pt_diff(tip, normalized_diff);
		t_pt semibase = normalized_diff;
		
		jgraphics_matrix_transform_point(&mat, &semibase.x, &semibase.y);
		semibase.x /=2.;
		semibase.y /=2.;
		
		t_pt base1 = pt_pt_sum(middle, semibase);
		t_pt base2 = pt_pt_diff(middle, semibase);
		
		paint_triangle(g, color, color, tip.x, tip.y, base1.x, base1.y, base2.x, base2.y, 0);
	}	
}

void dadaobj_paint_shape(t_dadaobj *r_ob, t_shape *sh, t_pt center, t_jgraphics *g, t_jrgba *bordercolor, t_jrgba *fillcolor, double linewidth)
{
    t_pt zoom = r_ob->m_zoom.zoom;
    switch (sh->type) {
        case DADA_SHAPE_ELLIPSE:
        {
            t_pt center_pix = build_pt(center.x + sh->shape.ellipse.center.x * zoom.x, center.y - sh->shape.ellipse.center.y * zoom.y);
            jgraphics_translate(g, center_pix.x, center_pix.y);
            jgraphics_rotate(g, -sh->shape.ellipse.rotation);
            jgraphics_ovalarc(g, 0, 0, sh->shape.ellipse.radius.x * zoom.x, sh->shape.ellipse.radius.y * zoom.y, 0., 6.29);
            jgraphics_rotate(g, +sh->shape.ellipse.rotation);
            jgraphics_translate(g, -center_pix.x, -center_pix.y);
        }
            break;
            
        case DADA_SHAPE_POLYGON:
        {
            long j;
            t_pt coord = coord_to_pix(r_ob, center, sh->shape.polygon.vertex[0]);
            jgraphics_move_to(g, coord.x, coord.y);
            for (j = 1; j < sh->shape.polygon.num_vertices; j++) {
                coord = coord_to_pix(r_ob, center, sh->shape.polygon.vertex[j]);
                jgraphics_line_to(g, coord.x, coord.y);
            }
            jgraphics_close_path(g); 
        }
            break;
        default:
            break;
    }
    
    if (fillcolor) {
        jgraphics_set_source_jrgba(g, fillcolor);
        if (bordercolor)
            jgraphics_fill_preserve(g);
        else
            jgraphics_fill(g);
    }
    if (bordercolor) {
        jgraphics_set_source_jrgba(g, bordercolor);
        jgraphics_set_line_width(g, linewidth);
        jgraphics_stroke(g);
    }
}


void paint_line_dotted(t_jgraphics *g, t_jrgba *color, t_pt start, t_pt end, double dot_distance, double dot_radius, double *start_offset)
{
    double r = pt_pt_distance(start, end);
    double theta = atan2(end.y-start.y, end.x-start.x);
    double r_temp;
    for (r_temp = (start_offset ? *start_offset : 0); r_temp <= r; r_temp += dot_distance)
        paint_circle_filled(g, *color, start.x + r_temp * cos(theta), start.y + r_temp * sin(theta), dot_radius);
    if (start_offset)
        *start_offset = r_temp - r;
}

void dadaobj_paint_shape_dotted(t_dadaobj *r_ob, t_shape *sh, t_pt center, t_jgraphics *g, t_jrgba *color, double dot_distance, double dot_radius)
{
    switch (sh->type) {
        case DADA_SHAPE_ELLIPSE:
        {
            double a = sh->shape.ellipse.radius.x, b = sh->shape.ellipse.radius.y;
            double coord = delta_pix_to_delta_coord(r_ob, build_pt(dot_distance, dot_distance)).x;
            double d, delta_angle = coord / (0.5 * (a+b));
            long i, n = floor(TWOPI/delta_angle);
            delta_angle = TWOPI / n;
            for (i = 0, d = 0; i < n; i++, d += delta_angle) {
                // we know that for an ellipse r(theta) = a*b/sqrt(cos(theta)^2 * b^2 + sin(theta)^2 * a^s)
                double cos_d = cos(d), sin_d = sin(d);
                double this_r = a*b/sqrt(cos_d*cos_d*b*b + sin_d*sin_d*a*a);

                t_pt coord = coord_to_pix(r_ob, center, build_pt(sh->shape.ellipse.center.x + this_r * cos(d + sh->shape.ellipse.rotation), sh->shape.ellipse.center.y + this_r * sin(d + sh->shape.ellipse.rotation)));
                paint_circle_filled(g, *color, coord.x, coord.y, dot_radius);
            }
        }
            break;
            
        case DADA_SHAPE_POLYGON:
        {
            long j, n = sh->shape.polygon.num_vertices;
            double start_offset = 0;
            for (j = 0; j < n; j++) {
                paint_line_dotted(g, color, coord_to_pix(r_ob, center, sh->shape.polygon.vertex[j]),
                                  coord_to_pix(r_ob, center, sh->shape.polygon.vertex[(j+1) % n]), dot_distance, dot_radius, &start_offset);
            }
        }
            break;
        default:
            break;
    }
}



void dadaobj_paint_shape_from_view(t_dadaobj *r_ob, t_shape *sh, t_object *view, t_jgraphics *g, t_jrgba *bordercolor, t_jrgba *fillcolor, double linewidth)
{
    t_pt center = get_center_pix(r_ob, view, NULL);
    dadaobj_paint_shape(r_ob, sh, center, g, bordercolor, fillcolor, linewidth);
}



void dadaobj_paint_selection_rectangle(t_dadaobj *r_ob, t_jgraphics *g, t_jrgba *border_color, t_jrgba *fill_color)
{
	t_rect sel = build_rect(r_ob->m_interface.mousedown_pix.x, r_ob->m_interface.mousedown_pix.y, r_ob->m_interface.mousedrag_pix.x - r_ob->m_interface.mousedown_pix.x, r_ob->m_interface.mousedrag_pix.y - r_ob->m_interface.mousedown_pix.y);
	paint_rect(g, &sel, border_color, fill_color, 1, 0);
}	


void sprite_init(t_dada_sprite *sprite, t_symbol *name, t_rect *source_rect, char allow_stretch, double slide_time, long num_slides, t_symbol **slides)
{
	sprite->name = name;
	sprite->slide_time = slide_time;
	sprite->num_slides = 0;
	sprite->allow_stretch = allow_stretch;
	
	sprite->source_rect = source_rect ? *source_rect : build_rect(0, 0, 0, 0);
	
	long j;
	for (j = 0; j < num_slides && j < DADA_MAX_SLIDES_PER_SPRITE; j++) {
		sprite->slide_path[sprite->num_slides] = slides[j];
		sprite->slide_right[sprite->num_slides] = get_surface_from_file(sprite->slide_path[sprite->num_slides]);
		sprite->slide_left[sprite->num_slides] = clone_surface(sprite->slide_right[sprite->num_slides], true, false);
		if (j == 0 && !source_rect)
			sprite->source_rect = build_rect(0, 0, jgraphics_image_surface_get_width(sprite->slide_right[sprite->num_slides]), 
											 jgraphics_image_surface_get_height(sprite->slide_right[sprite->num_slides]));
		sprite->num_slides++;
	}
}

void sprite_free(t_dada_sprite *sprite)
{
	long j;
	for (j = 0; j < sprite->num_slides; j++) {
		if (sprite->slide_left)
			jgraphics_surface_destroy(sprite->slide_left[j]);
		if (sprite->slide_right)
			jgraphics_surface_destroy(sprite->slide_right[j]);
	}	
}


t_jsurface *colorize_surface(t_jsurface *surf, t_jhsla *deltacolor)
{
	long width = jgraphics_image_surface_get_width(surf);
	long height = jgraphics_image_surface_get_height(surf);
	t_jsurface *out = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, width, height);
	long i, j;
	t_jrgba this_color, orig_color;
	t_jhsla this_color_hsla;
	for (i = 0; i < width; i++)
		for (j = 0; j < height; j++) {
			jgraphics_image_surface_get_pixel(surf, i, j, &orig_color);
			this_color_hsla = rgba_to_hsla(orig_color);
			this_color_hsla.hue = positive_fmod(this_color_hsla.hue + deltacolor->hue, TWOPI);
			this_color_hsla.saturation *= deltacolor->saturation;
			this_color_hsla.lightness *= deltacolor->lightness;
			this_color_hsla.alpha *= deltacolor->alpha;
			this_color = hsla_to_rgba(this_color_hsla);
			jgraphics_image_surface_set_pixel(out, i, j, this_color.alpha < CONST_EPSILON1 ? this_color : this_color); //build_jrgba(1, 0, 0, 0.1));
		}
	return out;
}


void paint_sprite(t_jgraphics *g, t_dada_sprite *sprite, long slide_idx, t_rect source, t_rect dest, char direction, t_jhsla *deltacolor)
{			
	if (!sprite)
		return;
	
	t_jsurface *surf = direction < 0 ? sprite->slide_left[slide_idx] : sprite->slide_right[slide_idx];

	/// colorize
	if (deltacolor) 
		surf = colorize_surface(surf, deltacolor);
	
	if (!sprite->allow_stretch) {
		t_jpattern *pattern = jgraphics_pattern_create_for_surface(surf);
		jgraphics_rectangle (g, dest.x, dest.y, dest.width, dest.height);
		jgraphics_set_source (g, pattern);
		jgraphics_fill (g);
		jgraphics_pattern_destroy(pattern);
	} else  {
		jgraphics_image_surface_draw(g, surf, source, dest);
	}
	
	if (deltacolor)
		jgraphics_surface_destroy(surf);
}


void dadaobj_paint_polygon(t_dadaobj *r_ob, t_pt center, t_jgraphics *g, t_polygon *p, t_jrgba *bordercolor, t_jrgba *fillcolor, double linewidth)
{
    jgraphics_set_line_width(g, linewidth);
    
    if (fillcolor)
        jgraphics_set_source_jrgba(g, fillcolor);
    else if (bordercolor)
        jgraphics_set_source_jrgba(g, bordercolor);
    
    for (long j = 0; j < p->num_vertices; j++) {
        t_pt pix = coord_to_pix(r_ob, center, p->vertices[j]);
        if (j == 0)
            jgraphics_move_to(g, pix.x, pix.y);
        else
            jgraphics_line_to(g, pix.x, pix.y);
    }
    jgraphics_close_path(g);
    if (bordercolor) {
        if (fillcolor) {
            jgraphics_fill_preserve(g);
            jgraphics_set_source_jrgba(g, bordercolor);
        }
        jgraphics_stroke(g);
    } else {
        if (fillcolor)
            jgraphics_fill(g);
    }
}

void dadaobj_paint_dashed_polygon_contour(t_dadaobj *r_ob, t_pt center, t_jgraphics *g, t_polygon *p, t_jrgba *bordercolor, double linewidth, double dashlength)
{
    
    if (p->num_vertices > 1) {
        t_pt prev = coord_to_pix(r_ob, center, p->vertices[0]);
        t_pt first = prev;
        
        for (long j = 1; j < p->num_vertices; j++) {
            t_pt curr = coord_to_pix(r_ob, center, p->vertices[j]);
            paint_dashed_line(g, *bordercolor, prev.x, prev.y, curr.x, curr.y, linewidth, dashlength);
            prev = curr;
        }
        paint_dashed_line(g, *bordercolor, prev.x, prev.y, first.x, first.y, linewidth, dashlength);
    }
}


// Finds the intersection point between a rectangle <r> and the line pointing towards point <p> originating from the middle of the rectangle
// return 1 if found (and fills <intersection>), 0 otherwise
long rect_linetorect_intersect(t_pt p, t_rect r, t_pt *intersection)
{
    //assert minX <= maxX;
    //assert minY <= maxY;
    double x = p.x;
    double y = p.y;
    double minX = r.x;
    double minY = r.y;
    double maxX = minX + r.width;
    double maxY = minY + r.height;
    double midX = (minX + maxX) / 2;
    double midY = (minY + maxY) / 2;
    
    // if (midX - x == 0) -> m == ±Inf -> minYx/maxYx == x (because value / ±Inf = ±0)
    double m = (midY - y) / (midX - x);
    
    if (x <= midX) { // check "left" side
        double minXy = m * (minX - x) + y;
        if (minY <= minXy && minXy <= maxY) {
            intersection->x = minX; intersection->y = minXy;
            return 1;
        }
    }
    
    if (x >= midX) { // check "right" side
        double maxXy = m * (maxX - x) + y;
        if (minY <= maxXy && maxXy <= maxY) {
            intersection->x = maxX; intersection->y = maxXy;
            return 1;
        }
    }
    
    if (y <= midY) { // check "top" side
        double minYx = (minY - y) / m + x;
        if (minX <= minYx && minYx <= maxX) {
            intersection->x = minYx; intersection->y = minY;
            return 1;
        }
    }
    
    if (y >= midY) { // check "bottom" side
        double maxYx = (maxY - y) / m + x;
        if (minX <= maxYx && maxYx <= maxX) {
            intersection->x = maxYx; intersection->y = maxY;
            return 1;
        }
    }
    
    // edge case when finding midpoint intersection: m = 0/0 = NaN
    if (x == midX && y == midY) {
        intersection->x = x; intersection->y = y;
        return 1;
    }
    
    return 0;  // Should never happen
}

