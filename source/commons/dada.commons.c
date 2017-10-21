/**
	@file
	dada.commons.c
	Common utilities for dada library

	by Daniele Ghisi
*/

#include "dada.commons.h"							// standard Max include, always required
#include "dada.undo.h"

unsigned short get_default_accidental_char(double screen_acc_double)
{
	if (screen_acc_double == 0)
		return  0;
	if (screen_acc_double == 0.5)
		return 'r';
	if (screen_acc_double == -0.5) 
		return  'f';
	if (screen_acc_double == 0.25)
		return  'o';
	if (screen_acc_double == -0.25)
		return  'i';
	if (screen_acc_double == 0.75)
		return  'u';
	if (screen_acc_double == -0.75)
		return  'd';
	if (screen_acc_double == 0.125)
		return  'm';
	if (screen_acc_double == 0.375)
		return  'q';
	if (screen_acc_double == 0.625)
		return  's';
	if (screen_acc_double == 0.875)
		return  'v';
	if (screen_acc_double == -0.125)
		return  'k';
	if (screen_acc_double == -0.375)
		return  'g';
	if (screen_acc_double == -0.625)
		return  'e';
	if (screen_acc_double == -0.875)
		return  'b';
	if (screen_acc_double == 1.)
		return 'w';
	if (screen_acc_double == -1.) 
		return  'a';
	
	
	return 0;
}


t_jrgba dada_long_to_color(long i)
{
	long i_mod = i % 6;
	if (i_mod < 0)
		i_mod += 6;
	switch (i_mod) {
		case 0: return DADA_RED;
		case 1: return DADA_GREEN;
		case 2: return DADA_BLUE;
		case 3: return DADA_YELLOW;
		case 4: return DADA_ORANGE;
		case 5: return DADA_VIOLET;
		default: return DADA_BLACK; // will never happen
	}
}



long shaper_iter_fn(t_llll *plain_out_ll, long list, t_llll *ll, char isaddress) //  never called for address
{
	if (list == 1 && ll->l_head)
		llll_appendhatom_clone(plain_out_ll, &ll->l_head->l_hatom, 0, WHITENULL_llll);
	return 0;
}

// e.g. if model is 1 2 (3 4 (5 6 7) 8) and ll is a b (c d e f), it becomes a b (c d (e e e) f)
// DESTRUCTIVE: *ll is freed and replaced
void llll_reshape_scalarmode(t_llll **ll, t_llll *model)
{
	if (!ll || !*ll) 
		return;
	
	t_llll *list[2];
	t_llll *out_ll = llll_get();
	list[0] = model;
	list[1] = *ll;
	llll_iter(2, list, -1, 0, 1, 0, 2, 0, NULL, (iter_datafn) shaper_iter_fn, out_ll, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	llll_reshape(out_ll, model, NULL);
	llll_free(*ll);
	*ll = out_ll;
}



void hatom_subs(t_llll *ll, long pos, t_hatom *h)
{
	t_llll *address = llll_get();
	t_llll *subsmodel = llll_get();
	t_llll *sizes = llll_get();
	t_llll *temp = llll_get();
	llll_appendlong(sizes, 1, 0, WHITENULL_llll);
	llll_appendlong(address, pos, 0, WHITENULL_llll);
	llll_appendhatom_clone(temp, h, 0, WHITENULL_llll);
	llll_appendllll(subsmodel, temp, 0, WHITENULL_llll);
	llll_multisubs(ll, address, subsmodel, sizes);
}




t_llll *color_to_llll(t_jrgba *color)
{
	return double_quadruplet_to_llll(color->red, color->green, color->blue, color->alpha);
}

t_jrgba llll_to_color(t_llll *ll)
{
	t_jrgba outcolor = build_jrgba(0, 0, 0, 1);

    t_llllelem *temp = ll ? ll->l_head : NULL;
	if (temp && is_hatom_number(&temp->l_hatom))
		outcolor.red = hatom_getdouble(&temp->l_hatom);

	if (temp && (temp = temp->l_next) && is_hatom_number(&temp->l_hatom))
		outcolor.green = hatom_getdouble(&temp->l_hatom);

	if (temp && (temp = temp->l_next) && is_hatom_number(&temp->l_hatom))
		outcolor.blue = hatom_getdouble(&temp->l_hatom);

	if (temp && (temp = temp->l_next) && is_hatom_number(&temp->l_hatom))
		outcolor.alpha = hatom_getdouble(&temp->l_hatom);

	return outcolor;
}



void change_hue_and_lightness(t_jrgba *color, double delta_hue, double delta_lightness, double min_lightness, double max_lightness)
{	
	t_jhsla color_hsla = rgba_to_hsla(*color);
	color_hsla.hue = positive_fmod(color_hsla.hue + delta_hue, TWOPI);
	color_hsla.lightness = CLAMP(color_hsla.lightness + delta_lightness, min_lightness, max_lightness);
	*color = hsla_to_rgba(color_hsla);
}





t_pt get_center_pix(t_dadaobj *r_ob, t_object *patcherview, t_rect *drawrect)
{
	t_rect rect;
	jbox_get_rect_for_view(r_ob->orig_obj, patcherview, &rect);

	if (drawrect)
		*drawrect = rect;

	return coord_to_pix(r_ob, build_pt(rect.width/2., rect.height/2.), r_ob->m_zoom.center_offset);
}



t_pt coord_to_pix(t_dadaobj *r_ob, t_pt center, t_pt coord)
{
	t_pt pixel;
	switch (r_ob->m_geometry.lattice) {
		case DADA_LATTICE_TRIANGLE:
			pixel.y = center.y - (SQRT3OVER2 * r_ob->m_zoom.zoom.y) * coord.y;
			pixel.x = center.x + (r_ob->m_zoom.zoom.x * coord.x + r_ob->m_zoom.zoom.y * coord.y/2.);
			break;
		default:
			pixel.x = center.x + coord.x * r_ob->m_zoom.zoom.x; 
			pixel.y = center.y - coord.y * r_ob->m_zoom.zoom.y; 
			break;
	}
	return pixel;
}

t_pt pix_to_coord(t_dadaobj *r_ob, t_pt center, t_pt pixel)
{
	t_pt coord;
	switch (r_ob->m_geometry.lattice) {
		case DADA_LATTICE_TRIANGLE:
			coord.y = (center.y - pixel.y) / (SQRT3OVER2 * r_ob->m_zoom.zoom.y);
			coord.x = (pixel.x - center.x) / r_ob->m_zoom.zoom.x - coord.y / 2.;
			break;
		default:
			coord.x = (pixel.x - center.x) / r_ob->m_zoom.zoom.x; 
			coord.y = (center.y - pixel.y) / r_ob->m_zoom.zoom.y; 
			break;
	}
	return coord;
}


t_rect rect_coord_to_pix(t_dadaobj *r_ob, t_pt center, t_rect coord, char autoflip_height)
{
	t_pt pix = coord_to_pix(r_ob, center, build_pt(coord.x, coord.y));
	t_pt delta = delta_coord_to_delta_pix(r_ob, build_pt(coord.width, coord.height));
	if (autoflip_height && delta.y < 0) 
		return build_rect(pix.x, pix.y + delta.y, delta.x, -delta.y);
	else
		return build_rect(pix.x, pix.y, delta.x, delta.y);
}

t_rect rect_pix_to_coord(t_dadaobj *r_ob, t_pt center, t_rect pixel, char autoflip_height)
{
	t_pt coord = pix_to_coord(r_ob, center, build_pt(pixel.x, pixel.y));
	t_pt delta = delta_pix_to_delta_coord(r_ob, build_pt(pixel.width, pixel.height));
	if (autoflip_height && delta.y < 0) 
		return build_rect(coord.x, coord.y + delta.y, delta.x, -delta.y);
	else
		return build_rect(coord.x, coord.y, delta.x, delta.y);
}
					  

// obtain the minimum X and Y coordinates so that by incrementing X++ and Y++ one
// covers the whole rectangle
t_pt get_min_displayed_coord(t_dadaobj *r_ob, t_pt center, t_rect rect)
{
    if (r_ob->m_geometry.lattice == DADA_LATTICE_TRIANGLE) {
			t_pt pt1 = pix_to_coord(r_ob, center, build_pt(0, 0)); // this has minimum X			
			t_pt pt2 = pix_to_coord(r_ob, center, build_pt(0, rect.height)); // this has minimum Y
			return build_pt(pt1.x, pt2.y);
    } else {
			return pix_to_coord(r_ob, center, build_pt(0, rect.height));
	}
}

t_pt get_max_displayed_coord(t_dadaobj *r_ob, t_pt center, t_rect rect)
{
    if (r_ob->m_geometry.lattice == DADA_LATTICE_TRIANGLE) {
			t_pt pt1 = pix_to_coord(r_ob, center, build_pt(rect.width, rect.height)); // this has maximum X			
			t_pt pt2 = pix_to_coord(r_ob, center, build_pt(0, 0)); // this has maximum Y
			return build_pt(pt1.x, pt2.y);
    } else {
			return pix_to_coord(r_ob, center, build_pt(rect.width, 0));
	}
}

t_pt pix_to_coord_from_view(t_dadaobj *r_ob, t_object *view, t_pt pixel)
{
	t_pt center = get_center_pix(r_ob, view, NULL);
	return pix_to_coord(r_ob, center, pixel);
}

t_pt coord_to_pix_from_view(t_dadaobj *r_ob, t_object *view, t_pt coord)
{
	t_pt center = get_center_pix(r_ob, view, NULL);
	return coord_to_pix(r_ob, center, coord);
}


t_pt delta_pix_to_delta_coord(t_dadaobj *r_ob, t_pt delta_pixel)
{
	switch (r_ob->m_geometry.lattice) {
		case DADA_LATTICE_TRIANGLE:
		{
			t_pt res;
			res.y = -delta_pixel.y/(SQRT3OVER2 * r_ob->m_zoom.zoom.y);
			res.x = delta_pixel.x/r_ob->m_zoom.zoom.x - res.y / 2.;
			return res;
		}
		default:
			return build_pt(delta_pixel.x/r_ob->m_zoom.zoom.x, -delta_pixel.y/r_ob->m_zoom.zoom.x);
	}
}


t_pt delta_coord_to_delta_pix(t_dadaobj *r_ob, t_pt delta_coord)
{
	switch (r_ob->m_geometry.lattice) {
		case DADA_LATTICE_TRIANGLE: // NOT SURE THIS WORKS: need to be tested!
		{
			t_pt res;
			res.y = -delta_coord.y * (SQRT3OVER2 * r_ob->m_zoom.zoom.y);
			res.x = delta_coord.x * r_ob->m_zoom.zoom.y + delta_coord.y * r_ob->m_zoom.zoom.y / 2.;
			return res;
		}
		default:
			return build_pt(delta_coord.x * r_ob->m_zoom.zoom.x, -delta_coord.y * r_ob->m_zoom.zoom.y);
	}
}


void round_cubic_coordinates_for_hex_grid(double *x, double *y, double *z)
{
	double rx = round(*x);
	double ry = round(*y);
	double rz = round(*z);
	double x_diff = fabs(rx - *x);
	double y_diff = fabs(ry - *y);
	double z_diff = fabs(rz - *z);
	
    if (x_diff > y_diff && x_diff > z_diff) 
        rx = -ry - rz;
	else if (y_diff > z_diff)
		ry = -rx-rz;
	else
		rz = -rx-ry;
	*x = rx;
	*y = ry;
	*z = rz;
}



double freq_to_mc(double freq, double diapason)
{
	return 6900 + 1200 * log(freq/diapason)/log(2);
}

double mc_to_freq(double mc, double diapason)
{
	return exp((mc - 6900)/(1200 / log(2))) * diapason;
}


double rand_f(double min, double max)
{
	double r3 = min + static_cast <double> (rand()) /( static_cast <double> (RAND_MAX)/(max-min));
	return r3;
}



t_jrgba symbol_to_color(t_symbol *sym)
{
	t_jrgba color;
	if (sym == gensym("Red"))
		color = DADA_RED;
	else if (sym == gensym("Green"))
		color = DADA_GREEN;
	else if (sym == gensym("Blue"))
		color = DADA_BLUE;
	else if (sym == gensym("Yellow"))
		color = DADA_YELLOW;
	else if (sym == gensym("Orange"))
		color = DADA_ORANGE;
	else if (sym == gensym("Violet"))
		color = DADA_VIOLET;
	else
		color = DADA_BLACK;
	return color;
}


void dadaobj_parse_llll(t_dadaobj *r_ob, t_llll *ll, char *model, ...)
{
	va_list argptr;
	char *cur = model;
	t_llllelem *elem = ll->l_head;
	
	va_start(argptr, model);
	while (*cur) {
		void *this_ptr = va_arg(argptr, void *);
		long type = elem ? hatom_gettype(&elem->l_hatom) : H_NULL;
		switch (*cur) {
			case 'l': // long
				if (type == H_LONG || type == H_RAT || type == H_DOUBLE)
					*((long *)this_ptr) = hatom_getlong(&elem->l_hatom);
				else
					*((long *)this_ptr) = 0;
				break;
			case 'd': // double
				if (type == H_LONG || type == H_RAT || type == H_DOUBLE)
					*((double *)this_ptr) = hatom_getdouble(&elem->l_hatom);
				else
					*((double *)this_ptr) = 0;
				break;
			case 'r': // rational
				if (type == H_LONG || type == H_RAT || type == H_DOUBLE)
					*((t_rational *)this_ptr) = hatom_getrational(&elem->l_hatom);
				else
					*((t_rational *)this_ptr) = long2rat(0);
				break;
			case 's': // symbol
				if (type == H_SYM)
					*((t_symbol **)this_ptr) = hatom_getsym(&elem->l_hatom);
				else
					*((t_symbol **)this_ptr) = _llllobj_sym_none;
				break;
			case 'P': // POINT: t_pt
				if (type == H_LLLL)
					*((t_pt *)this_ptr) = llll_to_pt(hatom_getllll(&elem->l_hatom));
				else
					*((t_pt *)this_ptr) = build_pt(0, 0);
				break;
			case 'R': // RECTANGLE: t_rect
				if (type == H_LLLL)
					*((t_rect *)this_ptr) = llll_to_rect(hatom_getllll(&elem->l_hatom));
				else
					*((t_rect *)this_ptr) = build_rect(0, 0, 0, 0);
				break;
			case 'C': // COLOR: t_jrgba
				if (type == H_LLLL)
					*((t_jrgba *)this_ptr) = llll_to_color(hatom_getllll(&elem->l_hatom));
				else
					*((t_jrgba *)this_ptr) = DADA_BLACK;
				break;
			case 'F': // Dadaitem Flags
				if (type == H_LLLL)
					*((long *)this_ptr) = dadaitem_get_flags_from_llll(hatom_getllll(&elem->l_hatom), NULL);
				else
					*((long *)this_ptr) = 0;
				break;
			case '4': // llll
				if (type == H_LLLL)
					*((t_llll **)this_ptr) = llll_clone(hatom_getllll(&elem->l_hatom));
				else
					*((t_llll **)this_ptr) = NULL;
				break;
			default:
				break;
		}
		if (elem) 
			elem = elem->l_next;
		cur++;
	}
	va_end(argptr);
}

void dadaobj_parseargs(t_dadaobj *r_ob, t_llll *ll, char *model, ...)
{
    const long DADA_MAX_PARSEARGS_ARGS = 100;
    t_symbol *router[DADA_MAX_PARSEARGS_ARGS];
    char    type[DADA_MAX_PARSEARGS_ARGS];
    void    *ptr[DADA_MAX_PARSEARGS_ARGS];
    
    // 1. build router list to be searched
    va_list argptr;
    char *cur = model;
    long i = 0;
    t_llllelem *elem = ll->l_head;
    
    va_start(argptr, model);
    while (*cur && i < DADA_MAX_PARSEARGS_ARGS) {
        router[i] = va_arg(argptr, t_symbol *);
        type[i] = *cur;
        ptr[i] = va_arg(argptr, void *);
        i++;
        cur++;
    }
    va_end(argptr);

    
    long n = i;
    t_llll *subll;
    for (elem = ll->l_head; elem; elem = elem->l_next) {
        if (hatom_gettype(&elem->l_hatom) == H_LLLL && (subll = hatom_getllll(&elem->l_hatom)) && subll->l_head && hatom_gettype(&subll->l_head->l_hatom) == H_SYM) {
            t_symbol *this_router = hatom_getsym(&subll->l_head->l_hatom);
            for (i = 0; i < n; i++) {
                if (this_router == router[i]) {
                    switch (type[i]) {
                        case 'l': // long
                            if (subll->l_head->l_next && is_hatom_number(&subll->l_head->l_next->l_hatom))
                                *((long *)ptr[i]) = hatom_getlong(&subll->l_head->l_next->l_hatom);
                            else
                                *((long *)ptr[i]) = 0;
                            break;
                        case 'd': // double
                            if (subll->l_head->l_next && is_hatom_number(&subll->l_head->l_next->l_hatom))
                                *((double *)ptr[i]) = hatom_getdouble(&subll->l_head->l_next->l_hatom);
                            else
                                *((double *)ptr[i]) = 0;
                            break;
                        case 'r': // rational
                            if (subll->l_head->l_next && is_hatom_number(&subll->l_head->l_next->l_hatom))
                                *((t_rational *)ptr[i]) = hatom_getrational(&subll->l_head->l_next->l_hatom);
                            else
                                *((t_rational *)ptr[i]) = long2rat(0);
                            break;
                        case 's': // symbol
                            if (subll->l_head->l_next && hatom_gettype(&subll->l_head->l_next->l_hatom) == H_SYM)
                                *((t_symbol **)ptr[i]) = hatom_getsym(&subll->l_head->l_next->l_hatom);
                            else
                                *((t_symbol **)ptr[i]) = _llllobj_sym_none;
                            break;
                        case 'P': // POINT: t_pt
                        {
                            t_llll *temp = llll_clone(subll);
                            llll_behead(temp);
                            *((t_pt *)ptr[i]) = llll_to_pt(temp);
                            llll_free(temp);
                        }
                            break;
                        case 'R': // RECTANGLE: t_rect
                        {
                            t_llll *temp = llll_clone(subll);
                            llll_behead(temp);
                            *((t_rect *)ptr[i]) = llll_to_rect(temp);
                            llll_free(temp);
                        }
                            break;
                        case 'C': // COLOR: t_jrgba
                        {
                            t_llll *temp = llll_clone(subll);
                            llll_behead(temp);
                            *((t_jrgba *)ptr[i]) = llll_to_color(temp);
                            llll_free(temp);
                        }
                            break;
                        case 'F': // Dadaitem Flags
                            *((long *)ptr[i]) = dadaitem_get_flags_from_llll(subll, NULL);
                            break;
                        case '4': // llll
                        {
                            t_llll *temp = llll_clone(subll);
                            llll_behead(temp);
                            if (*((t_llll **)ptr[i]))
                                llll_free(*((t_llll **)ptr[i]));
                            *((t_llll **)ptr[i]) = temp;
                        }
                            break;
                        default:
                            break;
                    }
                    
                    continue;
                }
            }
        }
    }
}

void change_color_for_velocity_alpha(t_jrgba *color, long velocity)
{
	double temp = (double)velocity/DADA_MAX_VELOCITY;
	*color = change_alpha(*color, temp);
}

void change_color_for_velocity_darken(t_jrgba *color, long velocity)
{
	t_jhsla color_hsla = rgba_to_hsla(*color);
	color_hsla.lightness = rescale(velocity, 0, DADA_MAX_VELOCITY, 0.1, 0.6);
	*color = hsla_to_rgba(color_hsla);
}

void change_color_for_velocity_lighten(t_jrgba *color, long velocity)
{
	t_jhsla color_hsla = rgba_to_hsla(*color);
	color_hsla.lightness = rescale(velocity, 0, DADA_MAX_VELOCITY, 0.6, 0.1);
	*color = hsla_to_rgba(color_hsla);
}

// locates file in search path also if needed
t_jsurface *get_surface_from_file(t_symbol *file_path)
{
	if (file_path && file_path->s_name[0]) {
		char filename[MAX_FILENAME_CHARS];
		short path = 0;
//        cpost("Get_surface_from_file path: %s", file_path->s_name);
		if (path_frompathname(file_path->s_name, &path, filename)) {
			t_fourcc type;
			char file_path_str[MAX_FILENAME_CHARS]; 
			strncpy_zero(file_path_str, file_path->s_name, MAX_FILENAME_CHARS); 
			if (!locatefile_extended(file_path_str, &path, &type, &type, -1)) 
				return jgraphics_image_surface_create_from_file(file_path_str, path);
		} else {
			return jgraphics_image_surface_create_from_file(filename, path);
		}
	}
	return NULL;
}

t_jsurface *clone_surface(t_jsurface *orig, char mirror_x, char mirror_y)
{
	int w = jgraphics_image_surface_get_width(orig);
	int h = jgraphics_image_surface_get_height(orig);
	t_jsurface *mirrored = jgraphics_image_surface_create(JGRAPHICS_FORMAT_ARGB32, w, h);
	t_jpattern *pat = jgraphics_pattern_create_for_surface(orig);
	t_jgraphics *g = jgraphics_create(mirrored);
	
	t_jmatrix m;
	jgraphics_matrix_init_identity(&m);
	if (mirror_x) {
		jgraphics_matrix_scale(&m, -1, 1);
		jgraphics_matrix_translate(&m, w, 0);
	}
	if (mirror_y) {
		jgraphics_matrix_scale(&m, 1, -1);
		jgraphics_matrix_translate(&m, 0, h);
	}
	jgraphics_pattern_set_matrix(pat, &m);
	
	jgraphics_set_source(g, pat);
	jgraphics_rectangle(g, 0, 0, w, h);
	jgraphics_fill(g);
	
	jgraphics_destroy(g);
	jgraphics_pattern_destroy(pat);
	return mirrored;
}


/*
t_jsurface *dada_quick_surface_from_file(char *file_name)
{
    t_fourcc outtype;
    t_fourcc filetype = 'PNG';
    char filename[MAX_PATH_CHARS];
    short path;
    strcpy(filename, file_name);    // must copy symbol before calling locatefile_extended
    t_jsurface *temp = NULL;
    
    if (locatefile_extended(filename, &path, &outtype, &filetype, 1))
        temp = jgraphics_image_surface_create_from_file(filename, path);
    
    return temp;
}

t_jpattern *dada_quick_pattern_from_file(char *file_name)
{
    t_fourcc outtype;
    t_fourcc filetype = 'PNG';
    char filename[MAX_PATH_CHARS];
    short path;
    strcpy(filename, file_name);    // must copy symbol before calling locatefile_extended
    t_jpattern *pattern = NULL;
    
    if (locatefile_extended(filename, &path, &outtype, &filetype, 1)) {
        t_jsurface *temp = jgraphics_image_surface_create_from_file(filename, path);
        pattern = jgraphics_pattern_create_for_surface(temp);
        jgraphics_surface_destroy(temp);
    }
    
    return pattern;
}*/


t_symbol *dada_ezlocate_folder(t_symbol *foldername)
{
    char name[MAX_FILENAME_CHARS];
    short path;
    t_fourcc type;
    
    strncpy_zero(name, foldername->s_name, MAX_FILENAME_CHARS);
    if (locatefile_extended(name, &path, &type, NULL, 0)) {
		//        error("folder %s not found", name);
		return NULL;
    } else {
		char pathname[MAX_PATH_CHARS];
		short err;
        // post("folder %s, path %d", name, path);
		if (path_topathname(path, name, pathname) != MAX_ERR_NONE)
			return NULL;
		return gensym(pathname);
    }
}


t_symbol *dada_ezlocate_file(t_symbol *file_name, t_fourcc *file_type)
{
	char filename[MAX_FILENAME_CHARS];
	short path = 0;
	
	if (!file_name)
		return NULL;
	
	if (file_type) *file_type = 0;
	
	if (path_frompathname(file_name->s_name, &path, filename)) {
		t_fourcc type;
		char file_path_str[MAX_FILENAME_CHARS]; 
		strncpy_zero(file_path_str, file_name->s_name, MAX_FILENAME_CHARS); 
		if (!locatefile_extended(file_path_str, &path, &type, &type, -1))  {
			char filenameok2[MAX_FILENAME_CHARS];
			path_topathname(path, file_path_str, filename);
			path_nameconform(filename, filenameok2, PATH_STYLE_MAX, PATH_TYPE_BOOT);
			if (file_type) *file_type = type;
			return gensym(filenameok2);
		}
	} else {
		char filenameok[MAX_FILENAME_CHARS];
		char filenameok2[MAX_FILENAME_CHARS];
		path_topathname(path, filename, filenameok);
		path_nameconform(filenameok, filenameok2, PATH_STYLE_MAX, PATH_TYPE_BOOT);
		return gensym(filenameok2);
	}
	
	return NULL;
}

t_symbol *dada_ezresolve_file(t_symbol *file_name, short *outpath)
{
    char tempfile[MAX_PATH_CHARS];
    char outfile[MAX_PATH_CHARS];
    short path = path_getdefault();
    
    snprintf_zero(tempfile, MAX_PATH_CHARS, "%s", file_name ? file_name->s_name : "Untitled.txt");

    path_topotentialname(path, tempfile, outfile, false);
    
    return gensym(outfile);
}

long dada_llll_check(t_llll *ll)
{
	long res = llll_check(ll);
	if (res) {
		long foo = 0;
		foo++;
	}
	return res;
}


t_llll *llll_comb_fix(t_llll *ll, t_atom_long startk, t_atom_long endk, t_atom_long max_gap)
{
	t_llll *klist, *comblist;
	t_llll *outlist;
	t_atom_long inc, k, i;
	t_atom_long ll_size;
	t_atom_long *indices;
	t_atom_long dontreachthisk;
	t_hatom **hatoms, **this_hatoms;
	t_llllelem *el;
	
	if (!ll)
		return NULL;
	outlist = llll_get();
	
	ll_size = ll->l_size;
	if (ll_size == 0)
		return outlist;
	
	indices = (t_atom_long *) bach_newptr(ll_size * sizeof(t_atom_long));
	hatoms = (t_hatom **) bach_newptr(ll_size * sizeof(t_hatom *));
	
	startk = CLAMP(startk, 0, (long)ll->l_size);
	if (endk < 0)
		endk = ll->l_size;
	else
		endk = MIN(endk, (long)ll->l_size);
	
	inc = startk > endk ? -1 : 1;
	
	for (el = ll->l_head, this_hatoms = hatoms; el; el = el->l_next, this_hatoms++)
		*this_hatoms = &el->l_hatom;
	
	dontreachthisk = endk + inc;
	
	for (k = startk; k != dontreachthisk; k += inc) {
		klist = llll_get();
		llll_appendllll(outlist, klist, 0, WHITENULL_llll);
		
		if (k == 0) {
			llll_appendllll(klist, llll_get(), 0, WHITENULL_llll);
			continue;
		} else if (k == 1) {
			// TO DO
			continue;
		}
		
		for (i = 0; i < k-1; i++)
			indices[i] = i;
		indices[k-1] = ll_size - 1;
		
		while (1) {
			t_atom_long maxofthemin;
			
			if (indices[1] - indices[0] > max_gap + 1)
				break;
			
			if (indices[k-1] - indices[k-2] > max_gap + 1) {
				//nothing to do
			} else {
				comblist = llll_get();
				llll_appendllll(klist, comblist, 0, WHITENULL_llll);
				
				for (i = 0; i < k; i++)
					llll_appendhatom_clone(comblist, hatoms[indices[i]], 0, WHITENULL_llll);
			}
			
			i = k - 2;
			
			if (i == 0)
				break; // easy way out
			
			maxofthemin = ll_size - k;
				
			indices[i] ++;
			while (indices[i+1] - indices[i] > max_gap + 1)
				indices[i] ++;
			
			while (i > 1 && (indices[i] > maxofthemin + i || indices[i] - indices[i-1] > max_gap + 1)) {
				i--;
				indices[i]++;
			}
			
			if (indices[1] > maxofthemin + 1)
				break;
			
			/* comb now looks like (..., x, n, n, n, ..., n).
			 Turn it into (..., x, x + 1, x + 2, ...) */
			for (i++; i < k-1; i++)
				indices[i] = indices[i - 1] + 1;
			
		}
	}
	
	bach_freeptr(hatoms);
	bach_freeptr(indices);
	pedantic_llll_check(outlist);
	
	return outlist;
}


t_llll *symbol_and_llll_to_llll(t_symbol *sym, t_llll *ll)
{
    t_llll *out = llll_get();
    llll_appendsym(out, sym);
    llll_appendllll(out, ll);
    return out;
}

t_llll *symbol_and_llll_to_llll_chained(t_symbol *sym, t_llll *ll)
{
    t_llll *out = llll_get();
    llll_appendsym(out, sym);
    llll_chain(out, ll);
    return out;
}




long find_symbol_in_symbol_array(t_symbol *elem, t_symbol **array, long array_length)
{
    long i;
    for (i = 0; i < array_length; i++)
        if (elem == array[i])
            return i;
    return -1;
}


const char *dada_get_default_include()
{
    return "#ifndef PI \n"
    "#define PI 3.14159265358979323846 \n"
    "#endif \n"
    "#ifndef TWOPI \n"
    "#define TWOPI 6.28318530717958647692 \n"
    "#endif \n"
    "#ifndef PIOVERTWO \n"
    "#define PIOVERTWO 1.57079632679489661923 \n"
    "#endif \n"
    " \n"
    " extern double acos( double ); \n"
    " extern double asin( double ); \n"
    " extern double atan( double ); \n"
    " extern double atan2( double, double ); \n"
    " extern double cos( double ); \n"
    " extern double sin( double ); \n"
    " extern double tan( double ); \n"
    " extern double acosh( double ); \n"
    " extern double asinh( double ); \n"
    " extern double atanh( double ); \n"
    " extern double cosh( double ); \n"
    " extern double sinh( double ); \n"
    " extern double tanh( double ); \n"
    " extern double exp ( double ); \n"
    " extern double exp2 ( double ); \n"
    " extern double log ( double ); \n"
    " extern double log2 ( double ); \n"
    " extern double log10 ( double ); \n"
    " extern double fmod ( double, double ); \n"
    " extern double modf ( double, double * ); \n"
    " extern double fabs( double ); \n"
    " extern double hypot ( double, double ); \n"
    " extern double pow ( double, double ); \n"
    " extern double sqrt( double ); \n"
    " extern double ceil ( double ); \n"
    " extern double floor ( double ); \n"
    " extern double round ( double ); \n"
    " \n";
}




double hatom_to_angle_in_rad(t_hatom *h)
{
    // rotation angle
    if (is_hatom_number(h))
        return hatom_getdouble(h);
    else if (hatom_gettype(h) == H_LLLL) {
        t_llll *ll = hatom_getllll(h);
        if (hatom_gettype(&ll->l_tail->l_hatom) == H_SYM && hatom_getsym(&ll->l_tail->l_hatom) == gensym("deg") && is_hatom_number(&ll->l_head->l_hatom)) {
            return deg2rad(hatom_getdouble(&ll->l_head->l_hatom));
        }
    }
    else if (hatom_gettype(h) == H_SYM) {
        t_symbol *s = hatom_getsym(h);
        if (s && s->s_name) {
            long len = strlen(s->s_name);
            if (len >= 3 && (strcmp(s->s_name + len - 2, "°") == 0 || strcmp(s->s_name + len - 2, "º") == 0)) {
                char temp[4096];
                snprintf_zero(temp, 4096, s->s_name);
                if (len - 2 < 4096)
                    temp[len - 2] = 0;
                return deg2rad(atof(temp));
            } else
                return 0;
        } else
            return 0;
    }
    
    return 0;
}

