/**
	@file
	dada.geometry.c
	Geometric utilities for dada library

	by Daniele Ghisi
*/

#include "dada.geometry.h"

t_pt pt_rotate(t_pt pt, double angle)
{
    t_pt out;
    double norm = pt_norm(pt);
    
    if (norm == 0)
        return pt;
    
    double this_angle = atan2(pt.y, pt.x);
    double out_angle = this_angle + angle;
    out.x = norm * cos(out_angle);
    out.y = norm * sin(out_angle);
    return out;
    
}

t_pt get_dadapolygon_barycenter(t_dadapolygon *poly)
{
	t_pt barycenter = build_pt(0, 0);
	long i;
	for (i = 0; i < poly->num_vertices; i++) 
		barycenter = pt_pt_sum(barycenter, poly->vertex[i]);
	barycenter = pt_number_prod(barycenter, 1./poly->num_vertices);
	return barycenter;
}


t_pt get_shape_barycenter(t_shape *shape)
{
	switch (shape->type) {
		case DADA_SHAPE_ELLIPSE:
			return shape->shape.ellipse.center;
			break;
		case DADA_SHAPE_POLYGON:
			return get_dadapolygon_barycenter(&shape->shape.polygon);
			break;
		default:
			return build_pt(0, 0);
			break;
	}
}

double get_shape_barycentric_outermost_radius(t_shape *shape, t_pt *barycenter)
{
    t_pt baryc = get_shape_barycenter(shape);
    if (barycenter)
        *barycenter = baryc;
    
    switch (shape->type) {
        case DADA_SHAPE_ELLIPSE:
            return MAX(shape->shape.ellipse.radius.x, shape->shape.ellipse.radius.y);
            break;
        case DADA_SHAPE_POLYGON:
        {
            double max_radius = 0;
            long i;
            for (i = 0; i < shape->shape.polygon.num_vertices; i++) {
                double this_dist = pt_pt_distance(baryc, shape->shape.polygon.vertex[i]);
                if (this_dist > max_radius)
                    max_radius = this_dist;
            }
            return max_radius;
        }
            break;
        default:
            return 0;
            break;
    }
}

double get_shape_barycentric_innermost_radius(t_shape *shape, t_pt *barycenter)
{
    t_pt baryc = get_shape_barycenter(shape);
    if (barycenter)
        *barycenter = baryc;

    switch (shape->type) {
        case DADA_SHAPE_ELLIPSE:
            return MIN(shape->shape.ellipse.radius.x, shape->shape.ellipse.radius.y);
            break;
        case DADA_SHAPE_POLYGON:
        {
            char undefined = true;
            double min_radius = 0;
            long i;
            for (i = 0; i < shape->shape.polygon.num_vertices; i++) {
                double this_dist = pt_line_distance(baryc.x, baryc.y, shape->shape.polygon.vertex[i].x, shape->shape.polygon.vertex[i].y, shape->shape.polygon.vertex[(i+1)%shape->shape.polygon.num_vertices].x, shape->shape.polygon.vertex[(i+1)%shape->shape.polygon.num_vertices].y);
                if (undefined || (this_dist < min_radius)) {
                    undefined = false;
                    min_radius = this_dist;
                }
            }
            return min_radius;
        }
            break;
        default:
            return 0;
            break;
    }
}

void shape_translate(t_shape *shape, t_pt delta)
{
	long i;
	switch (shape->type) {
		case DADA_SHAPE_ELLIPSE:
			shape->shape.ellipse.center = pt_pt_sum(shape->shape.ellipse.center, delta);
			break;
		case DADA_SHAPE_POLYGON:
			for (i = 0; i < shape->shape.polygon.num_vertices; i++) 
				shape->shape.polygon.vertex[i] = pt_pt_sum(shape->shape.polygon.vertex[i], delta);
			break;
		default:
			break;
	}			
}


double rotation_matrix_to_angle(t_jmatrix *rotation_matrix)
{
	double cx = 1, cy = 0;
	jgraphics_matrix_transform_point(rotation_matrix, &cx, &cy);
	return atan2(cy, cx);
}


void make_angle_standard(double *angle)
{
	*angle = fmod(*angle, TWO_PI);
	while (*angle < 0) 
		*angle += TWO_PI;
}

void shape_rotate_from_matrix(t_shape *shape, t_pt rotation_center, t_jmatrix *rotation_matrix)
{
	long i;
	switch (shape->type) {
		case DADA_SHAPE_ELLIPSE:
		{
			t_pt circle_center = shape->shape.ellipse.center;
			circle_center = pt_pt_diff(circle_center, rotation_center);
			jgraphics_matrix_transform_point(rotation_matrix, &circle_center.x, &circle_center.y);
			circle_center = pt_pt_sum(circle_center, rotation_center);
			shape->shape.ellipse.center = circle_center;	
			shape->shape.ellipse.rotation += rotation_matrix_to_angle(rotation_matrix);
			make_angle_standard(&shape->shape.ellipse.rotation);
			break;
		}
		case DADA_SHAPE_POLYGON:
			for (i = 0; i < shape->shape.polygon.num_vertices; i++) {
				t_pt vertex = shape->shape.polygon.vertex[i];
				vertex = pt_pt_diff(vertex, rotation_center);
				jgraphics_matrix_transform_point(rotation_matrix, &vertex.x, &vertex.y);
				vertex = pt_pt_sum(vertex, rotation_center);
				shape->shape.polygon.vertex[i] = vertex;
			}
			break;
		default:
			break;
	}			
}

void shape_scale(t_shape *shape, t_pt scale_center, double factor_x, double factor_y)
{
	long i;
	switch (shape->type) {
		case DADA_SHAPE_ELLIPSE:
		{
			t_pt circle_center = shape->shape.ellipse.center;
			circle_center = pt_pt_diff(circle_center, scale_center);
			circle_center.x *= factor_x;
			circle_center.y *= factor_y;
			circle_center = pt_pt_sum(circle_center, scale_center);
			shape->shape.ellipse.center = circle_center;			
			shape->shape.ellipse.radius.x *= factor_x;
			shape->shape.ellipse.radius.y *= factor_y; // DOESN'T WORK: THIS IS WRONG
			// TO DO: Right formula for scaling, not sure the codification is the best
			break;
		}
		case DADA_SHAPE_POLYGON:
			for (i = 0; i < shape->shape.polygon.num_vertices; i++) {
				t_pt vertex = shape->shape.polygon.vertex[i];
				vertex = pt_pt_diff(vertex, scale_center);
				vertex.x *= factor_x;
				vertex.y *= factor_y;
				vertex = pt_pt_sum(vertex, scale_center);
				shape->shape.polygon.vertex[i] = vertex;
			}
			break;
		default:
			break;
	}			
}


void shape_shake(t_shape *shape, double min_abs_shift, double max_abs_shift, 
				 double min_abs_angle, double max_abs_angle, t_pt region_center, double region_radius)
{
	long i;
	double shift_abs = rescale((float)rand()/(float)RAND_MAX, 0., 1., min_abs_shift, max_abs_shift);
	double angle = deg2rad(rescale((float)rand()/(float)RAND_MAX, 0., 1., min_abs_angle, max_abs_angle) * ((float)rand() > RAND_MAX / 2 ? 1 : -1));
	
	t_pt shift_vector, barycenter = get_shape_barycenter(shape);
	
	t_jmatrix rotmat;
	jgraphics_matrix_init_rotate(&rotmat, angle);

	double pt_center_dist = pt_pt_distance(barycenter, region_center);
	if (pt_center_dist > region_radius) {
		// was already outside the region: we'll shift it towards the barycenter
		t_pt dist = pt_pt_diff(region_center, barycenter);
		double norm = sqrt(dist.x * dist.x + dist.y * dist.y);
		shift_vector = pt_number_prod(dist, shift_abs / norm);
	} else if (pt_center_dist + max_abs_shift > region_radius) {
		// might go outside the region after shaking: 
		double shift_dir = rescale((float)rand()/(float)RAND_MAX, 0., 1., 0., TWO_PI);
		shift_vector = build_pt(shift_abs * cos(shift_dir), shift_abs * sin(shift_dir));
		if (pt_pt_distance(pt_pt_sum(barycenter, shift_vector), region_center) > region_radius) {
			// it falls outside! let's force it inside
			t_pt dist = pt_pt_diff(region_center, barycenter);
			double norm = sqrt(dist.x * dist.x + dist.y * dist.y);
			shift_vector = pt_number_prod(dist, shift_abs / norm);
		}
	} else {
		// will in any case stay inside the region
		double shift_dir = rescale((float)rand()/(float)RAND_MAX, 0., 1., 0., TWO_PI);
		shift_vector = build_pt(shift_abs * cos(shift_dir), shift_abs * sin(shift_dir));
	}
	
	shape_rotate_from_matrix(shape, barycenter, &rotmat);

	switch (shape->type) {
		case DADA_SHAPE_ELLIPSE:
			shape->shape.ellipse.center = pt_pt_sum(shape->shape.ellipse.center, shift_vector);
			break;
		case DADA_SHAPE_POLYGON:
			for (i = 0; i < shape->shape.polygon.num_vertices; i++)
				shape->shape.polygon.vertex[i] = pt_pt_sum(shape->shape.polygon.vertex[i], shift_vector);
			break;
		default:
			break;
	}
}

void shape_offset(t_shape *shape, double how_much)
{
    switch (shape->type) {
        case DADA_SHAPE_ELLIPSE:
            shape->shape.ellipse.radius.x += how_much;
            shape->shape.ellipse.radius.y += how_much;
            break;
            
        case DADA_SHAPE_POLYGON:
        {
            t_polygon *p = NULL;
            dadapolygon_to_polygon(&shape->shape.polygon, &p);
            //            polygon_offset_smart_inplace(&p, how_much, 0, NULL, 0, NULL, false, 0, NULL, NULL);
            t_polygon *p_offset = polygon_offset_simple(p, how_much);
            polygon_free(p);
            polygon_to_dadapolygon(p_offset, &shape->shape.polygon);
            polygon_free(p);
        }
            break;
        default:
            break;
    }
}



void dadapolygon_to_polygon(t_dadapolygon *dp, t_polygon **p)
{
    *p = polygon_build(dp->num_vertices, dp->vertex);
}

void polygon_to_dadapolygon(t_polygon *p, t_dadapolygon *dp)
{
    long i;
    dp->num_vertices = MIN(p->num_vertices, DADA_POLYGON_MAX_VERTICES);
    for (i = 0; i < p->num_vertices && i < DADA_POLYGON_MAX_VERTICES; i++)
        dp->vertex[i] = p->vertices[i];
}

// version for non-translated, non-rotated ellipses
char is_pt_in_ellipse_easy(t_pt pt, t_ellipse *ellipse)
{
    if ((pt.x * pt.x) / (ellipse->radius.x * ellipse->radius.x) + (pt.y * pt.y) / (ellipse->radius.y * ellipse->radius.y) <= 1)
        return true;
    return false;
}

char is_pt_in_ellipse(t_pt pt, t_ellipse *ellipse)
{
	double temp1 = (pt.x - ellipse->center.x);
	double temp2 = (pt.y - ellipse->center.y);
	
	t_jmatrix mat;
	jgraphics_matrix_init_rotate(&mat, -ellipse->rotation);
	jgraphics_matrix_transform_point(&mat, &temp1, &temp2);
	
	if ((temp1 * temp1) / (ellipse->radius.x * ellipse->radius.x) + (temp2 * temp2) / (ellipse->radius.y * ellipse->radius.y) <= 1)
		return true;
	return false;
}

char is_pt_in_dadapolygon(t_pt pt, t_dadapolygon *poly) {
	// We handle the easy cases first
	switch (poly->num_vertices) {
		case 0:
			return false;
			break;
		case 1:
			return (fabs(poly->vertex[0].x - pt.x) < CONST_EPSILON_ALIGNMENTS && fabs(poly->vertex[0].y - pt.y) < CONST_EPSILON_ALIGNMENTS ? true : false);
			break;
		case 2:
			return is_pt_in_segment(pt.x, pt.y, poly->vertex[0].x, poly->vertex[0].y, poly->vertex[1].x, poly->vertex[1].y);
			break;
		case 3:
			return is_pt_in_triangle(pt.x, pt.y, poly->vertex[0].x, poly->vertex[0].y, poly->vertex[1].x, poly->vertex[1].y, poly->vertex[2].x, poly->vertex[2].y);
			break;
		case 4:
			return is_pt_in_quadrilater(pt.x, pt.y, poly->vertex[0].x, poly->vertex[0].y, poly->vertex[1].x, poly->vertex[1].y, poly->vertex[2].x, poly->vertex[2].y, poly->vertex[3].x, poly->vertex[3].y);
			break;
		default:
			break;
	}
	
	// otherwise:
	
	// First we check whether the point is inside the bounded box of the polygon
	double min_x = poly->vertex[0].x, max_x = poly->vertex[0].x;
	double min_y = poly->vertex[0].y, max_y = poly->vertex[0].y;
	long i;
	for (i = 1; i < poly->num_vertices; i++) {
		if (poly->vertex[i].x < min_x)
			min_x = poly->vertex[i].x;
		if (poly->vertex[i].x > max_x)
			max_x = poly->vertex[i].x;
		if (poly->vertex[i].y < min_y)
			min_y = poly->vertex[i].y;
		if (poly->vertex[i].y > max_y)
			max_y = poly->vertex[i].y;
	}
	
	// if the point is not in the bounded box of the polygon, it cannot be inside the polygon either
	if (!is_pt_in_rectangle(pt, build_rect(min_x, min_y, max_x - min_x, max_y - min_y)))
		return false;
	
	
	// ... then we use the ray cast algorithm
	// http://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html
	long j, c = 0;
	for (i = 0, j = poly->num_vertices - 1; i < poly->num_vertices; j = i++) {
		if ( ((poly->vertex[i].y > pt.y) != (poly->vertex[j].y > pt.y)) &&
			(pt.x < (poly->vertex[j].x - poly->vertex[i].x) * (pt.y - poly->vertex[i].y) / (poly->vertex[j].y - poly->vertex[i].y) + poly->vertex[i].x))
			c = !c;
	}
	return c;
}



char is_pt_in_shape(t_pt pt, t_shape *shape)
{
	switch (shape->type) {
		case DADA_SHAPE_POLYGON:
			return is_pt_in_dadapolygon(pt, &shape->shape.polygon);
			break;
		case DADA_SHAPE_ELLIPSE:
			return is_pt_in_ellipse(pt, &shape->shape.ellipse);
			break;
		default:
			return false;
			break;
	}
}


double pt_dadapolygon_distance(t_pt pt, t_dadapolygon *poly)
{
    long i;
    double min_dist = -1;
    long n = poly->num_vertices;
    for (i = 0; i < n; i++) {
        double this_dist = pt_segment_distance(pt, poly->vertex[i], poly->vertex[(i+1)%n]);
        if (this_dist < min_dist || min_dist < 0)
            min_dist = this_dist;
    }
    
    if (min_dist < 0)
        min_dist = 0; // should never happen, unless poly has no points. We might even want to set NaN here.
    
    return (is_pt_in_dadapolygon(pt, poly) ? -min_dist : min_dist);
}


double pt_circle_distance_easy(t_pt pt, double radius)
{
    return pt_norm(pt) - radius;
}

// only for ellipses with (0, 0) center and no rotation.
// Thanks Íñigo Quílez for your great web article! www.iquilezles.org
double pt_ellipse_distance_easy(t_pt pt, t_ellipse *ell)
{
    t_pt orig_pt = pt;
    t_pt ab = build_pt(ell->radius.x, ell->radius.y);
    //    vec3 pt = abs( z );
    pt = build_pt(fabs(pt.x), fabs(pt.y));
    
    if (pt.x > pt.y) { pt = build_pt(pt.y, pt.x); ab = build_pt(ab.y, ab.x); } // swap elements
    
    double l = ab.y*ab.y - ab.x*ab.x;
    
    if (fabs(l) < 0.001) // it's essentially a circle, c'mon...
        return pt_circle_distance_easy(pt, 0.5*(ab.y + ab.x));
    
    double m = ab.x*pt.x/l; double m2 = m*m;
    double n = ab.y*pt.y/l; double n2 = n*n;
    double c = (m2 + n2 - 1.0)/3.0; double c3 = c*c*c;
    double q = c3 + m2*n2*2.0;
    double d = c3 + m2*n2;
    double g = m + m*n2;
    
    double co;
    
    if (d < 0) {
        double p = acos(q/c3)/3.0;
        double s = cos(p);
        double t = sin(p)*sqrt(3.0);
        double rx = sqrt( -c*(s + t + 2.0) + m2 );
        double ry = sqrt( -c*(s - t + 2.0) + m2 );
        co = ( ry + fsign(l)*rx + fabs(g)/(rx*ry) - m)/2.0;
    }
    else
    {
        float h = 2.0*m*n*sqrt( d );
        float s = fsign(q+h)*pow( fabs(q+h), 1.0/3.0 );
        float u = fsign(q-h)*pow( fabs(q-h), 1.0/3.0 );
        float rx = -s - u - c*4.0 + 2.0*m2;
        float ry = (s - u)*sqrt(3.0);
        float rm = sqrt( rx*rx + ry*ry );
        float p = ry/sqrt(rm-rx);
        co = (p + 2.0*g/rm - m)/2.0;
    }
    
    float si = sqrt( 1.0 - co*co );
    
    t_pt closestPoint = build_pt(ab.x*co, ab.y*si);
    
    return (is_pt_in_ellipse_easy(orig_pt, ell) ? -1 : 1) * pt_pt_distance(pt, closestPoint);
}

double pt_ellipse_distance(t_pt pt, t_ellipse *ell)
{
    t_pt new_pt = pt_pt_diff(pt, ell->center);
    t_jmatrix mat;
    jgraphics_matrix_init_rotate(&mat, -ell->rotation);
    jgraphics_matrix_transform_point(&mat, &new_pt.x, &new_pt.y);
    
    return pt_ellipse_distance_easy(new_pt, ell);
}

double pt_shape_distance(t_pt pt, t_shape *shape)
{
    
    switch (shape->type) {
        case DADA_SHAPE_POLYGON:
            return pt_dadapolygon_distance(pt, &shape->shape.polygon);
            break;
        case DADA_SHAPE_ELLIPSE:
            return pt_ellipse_distance(pt, &shape->shape.ellipse);
            break;
        default:
            return 0.;
            break;
    }
}


t_dadapolygon build_regular_dadapolygon(long num_vertices, t_pt center, double circumradius)
{			
	t_dadapolygon poly;
	long i;
	poly.num_vertices = num_vertices;
	for (i = 0; i < num_vertices; i++) 
		poly.vertex[i] = pt_pt_sum(center, pt_number_prod(build_pt(cos(TWO_PI * i/num_vertices), sin(TWO_PI * i/num_vertices)), circumradius));
	return poly;
}

double get_dadapolygon_perimeter(t_dadapolygon *poly)
{
	long i;
	double res = 0;
	for (i = 0; i < poly->num_vertices - 1; i++) 
		res += pt_pt_distance(poly->vertex[i], poly->vertex[i+1]);
	res += pt_pt_distance(poly->vertex[poly->num_vertices - 1], poly->vertex[0]);
	return res;
}

double get_average_vertex_distance_from_barycenter(t_dadapolygon *poly)
{
	t_pt barycenter = get_dadapolygon_barycenter(poly);
	long i;
	double tot = 0;
	for (i = 0; i < poly->num_vertices; i++) 
		tot += pt_pt_distance(poly->vertex[i], barycenter);
	tot /= poly->num_vertices;
	return tot;
}


// idx == 0 -> X radiuspoint
// idx == 1 -> Y radiuspoing
t_pt get_ellipse_radiuspoint_coord(t_ellipse *ellipse, long idx)
{
	t_jmatrix rotmat;
	jgraphics_matrix_init_rotate(&rotmat, ellipse->rotation);
	t_pt point = build_pt(0, 0);
	if (idx == 0)
		point = build_pt(ellipse->radius.x, 0);
	else if (idx == 1)
		point = build_pt(0, ellipse->radius.y);
	jgraphics_matrix_transform_point(&rotmat, &point.x, &point.y);
	point = pt_pt_sum(point, ellipse->center);
	return point;
}


// returns 0 if successful, -1 if not
char delete_dadapolygon_vertex(t_dadapolygon *poly, long idx, char min_number_of_vertices_to_remain) 
{
	if (idx >= 0 && idx < poly->num_vertices && poly->num_vertices > min_number_of_vertices_to_remain) {
		if (idx < poly->num_vertices - 1)
			sysmem_copyptr(&poly->vertex[idx + 1], &poly->vertex[idx], (poly->num_vertices - idx - 1) * sizeof(t_pt));
		poly->num_vertices--;
		return 0;
	}
	return -1;
}


// returns the index of the new vertex, or -1 if unsuccessful
char duplicate_dadapolygon_vertex(t_dadapolygon *poly, long idx, t_pt new_pt) 
{
	if (idx >= 0 && idx < poly->num_vertices && poly->num_vertices + 1 < DADA_POLYGON_MAX_VERTICES) {

		// 1. determining if the new vertex should be placed BEFORE or AFTER idx, depending on the position of new_pt w.r. to the idx pt
		long before_this_idx;
		long prev_idx = idx == 0 ? poly->num_vertices - 1 : idx - 1;
		long next_idx = (idx + 1) % poly->num_vertices;
		t_pt delta = pt_pt_diff(new_pt, poly->vertex[idx]);
		t_pt prev_side = pt_pt_diff(poly->vertex[prev_idx], poly->vertex[idx]);
		t_pt next_side = pt_pt_diff(poly->vertex[next_idx], poly->vertex[idx]);

		if (pt_pt_scalarprod(delta, prev_side) > pt_pt_scalarprod(delta, next_side))
			before_this_idx = idx;
		else
			before_this_idx = next_idx;
		
		// 2. inserting data
		if (before_this_idx > 0)
			sysmem_copyptr(&poly->vertex[before_this_idx], &poly->vertex[before_this_idx + 1], (poly->num_vertices - before_this_idx) * sizeof(t_pt));
		poly->vertex[before_this_idx] = new_pt;
		poly->num_vertices++;
		return before_this_idx;
	}
	return -1;
}

// returns 0 if successful, -1 if not
char move_dadapolygon_vertex(t_dadapolygon *poly, long idx, t_pt new_pt, char given_as_delta) 
{
	if (idx >= 0 && idx < poly->num_vertices) 
		poly->vertex[idx] = given_as_delta ? pt_pt_sum(poly->vertex[idx], new_pt) : new_pt;
	return 0;
}

void clone_shape(t_shape *giver, t_shape *cloned)
{
	cloned->type = giver->type;
	cloned->color = giver->color;
	cloned->channel = giver->channel;
	switch (cloned->type) {
		case DADA_SHAPE_POLYGON:
			cloned->shape.polygon = giver->shape.polygon;
			break;
		case DADA_SHAPE_ELLIPSE:
			cloned->shape.ellipse = giver->shape.ellipse;
			break;
		default:
			break;
	}
}


t_rect get_rect_near_pt_inside_rect(t_pt pt, double width, double height, t_rect rect, t_pt delta, t_pt pad, t_pt *nearest_corner)
{
	double x, y;

	if (pt.x + width + delta.x + pad.x < rect.x + rect.width) {
		x = pt.x + delta.x; 
		if (nearest_corner)
			nearest_corner->x = x;
	} else {
		x = pt.x - width - delta.x;
		if (nearest_corner)
			nearest_corner->x = pt.x - delta.x;
	}
	
	if (pt.y - height - delta.y - pad.y > 0) {
		y = pt.y - height - delta.y;
		if (nearest_corner)
			nearest_corner->y = pt.y - delta.y;
	} else {
		y = pt.y + delta.y;
		if (nearest_corner)
			nearest_corner->y = y;
	}
	
	return build_rect(x, y, width, height);
}


t_shape build_dadapolygon(t_jrgba color, long MIDIchannel, long num_vertices, t_pt *vertices)
{
	t_shape p;
	long i;
	
	p.type = DADA_SHAPE_POLYGON;
	p.shape.polygon.num_vertices = MIN(num_vertices, DADA_POLYGON_MAX_VERTICES);
	for (i = 0; i < num_vertices && i < DADA_POLYGON_MAX_VERTICES; i++)
		p.shape.polygon.vertex[i] = vertices[i];
	p.color = color;
	p.channel = MIDIchannel;
	
	return p;
}


t_shape ezbuild_dadapolygon(t_jrgba color, long MIDIchannel, long count, ...)
{
	va_list argptr;
	long i;
	
	va_start(argptr,count);
	
	t_pt v[DADA_POLYGON_MAX_VERTICES];
	for (i = 0; i < count; i++) {
		double x = va_arg(argptr, double);
		double y = va_arg(argptr, double);
		v[i].x = x;
		v[i].y = y;
	}
	
	va_end(argptr);
	
	return build_dadapolygon(color, MIDIchannel, count, v);
}

t_shape build_ellipse(t_jrgba color, long MIDIchannel, t_pt center, t_pt radius, double rotation)
{
	t_shape s;
	s.color = color;
	s.channel = MIDIchannel;
	s.type = DADA_SHAPE_ELLIPSE;
	s.shape.ellipse.center = center;
	s.shape.ellipse.radius.x = radius.x;
	s.shape.ellipse.radius.y = radius.y;
	s.shape.ellipse.rotation = rotation;
	return s;
}



// Returns 1 if the lines intersect, otherwise 0. In addition, if the lines 
// intersect the intersection point may be stored in the floats i_x and i_y.
char get_segment_intersection(t_pt line1_start, t_pt line1_end, t_pt line2_start, t_pt line2_end, t_pt *collision_pt)
{
	double p0_x = line1_start.x, p0_y = line1_start.y, p1_x = line1_end.x, p1_y = line1_end.y;
	double p2_x = line2_start.x, p2_y = line2_start.y, p3_x = line2_end.x, p3_y = line2_end.y;
    double s1_x, s1_y, s2_x, s2_y;
    s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
    s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;
	
    double s, t;
    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);
	
    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        // Collision detected
        if (collision_pt) {
            collision_pt->x = p0_x + (t * s1_x);
            collision_pt->y = p0_y + (t * s1_y);
		}
		
        return 1;
    }
	
    return 0; // No collision
}


int is_pt_in_horizontal_line_shape(double point_x, double point_y, double line_y, double start_x, double end_x, double line_width){
	double min_x = MIN(start_x, end_x);
	double max_x = MAX(start_x, end_x);
	if (point_y >= line_y - line_width /2. && point_y <= line_y + line_width /2. && point_x >= min_x && point_x <= max_x)
		return 1;
	return 0;
}

int is_pt_in_vertical_line_shape(double point_x, double point_y, double line_x, double start_y, double end_y, double line_width){
	double min_y = MIN(start_y, end_y);
	double max_y = MAX(start_y, end_y);
	if (point_x >= line_x - line_width /2. && point_x <= line_x + line_width /2. && point_y >= min_y && point_y <= max_y)
		return 1;
	return 0;
}

int is_pt_in_segmented_line_shape(double point_x, double point_y, double start_x, double start_y, double end_x, double end_y, double line_width){
	double delta_x = end_x - start_x;
	double delta_y = end_y - start_y;
	double middle_x = start_x + delta_x * 0.5;
	double middle_y = start_y + delta_y * 0.5;
	if (fabs(delta_x) > fabs(delta_y)) {
		return (is_pt_in_horizontal_line_shape(point_x, point_y, start_y, start_x, middle_x, line_width) 
				|| is_pt_in_vertical_line_shape(point_x, point_y, middle_x, start_y, end_y, line_width)
				|| is_pt_in_horizontal_line_shape(point_x, point_y, end_y, middle_x, end_x, line_width));
	} else {
		return (is_pt_in_vertical_line_shape(point_x, point_y, start_x, start_y, middle_y, line_width) 
				|| is_pt_in_horizontal_line_shape(point_x, point_y, middle_y, start_x, end_x, line_width)
				|| is_pt_in_vertical_line_shape(point_x, point_y, end_x, middle_y, end_y, line_width));
	}
}

int is_pt_in_line_shape_improved(double point_x, double point_y, double start_x, double start_y, double end_x, double end_y, double line_width){
	if (fabs(start_x - end_x) < fabs(start_y - end_y)) {
		// on the X
		double supposed_pt_x = rescale(point_y, start_y, end_y, start_x, end_x);
		double min_y = MIN(start_y, end_y);
		double max_y = MAX(start_y, end_y);
		if (point_y >= min_y && point_y <= max_y && fabs(supposed_pt_x - point_x) < line_width/2.)
			return 1;
		return 0;
	} else {
		// on the Y
		double supposed_pt_y = rescale(point_x, start_x, end_x, start_y, end_y);
		double min_x = MIN(start_x, end_x);
		double max_x = MAX(start_x, end_x);
		if (point_x >= min_x && point_x <= max_x && fabs(supposed_pt_y - point_y) < line_width/2.)
			return 1;
		return 0;
	}
}

double pt_norm_squared(t_pt pt)
{
	return pt.x * pt.x + pt.y * pt.y;
}


t_pt pt_normalize(t_pt pt)
{
	double norm = pt_norm(pt);
	if (norm <= 0)
		return pt;
	return pt_number_prod(pt, 1./norm);
}


// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int pt_orientation(t_pt p, t_pt q, t_pt r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	
    if (val == 0) return 0;  // colinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// Prints convex hull of a set of n points.
void find_convex_hull(long num_points, t_pt *points, t_dadapolygon *poly)
{
	long n = num_points;
	
    // There must be at least 3 points
    if (n < 3) {
		long i;
		poly->num_vertices = n;
		for (i = 0; i < n; i++)
			poly->vertex[i] = points[i];
		return;
	}
	
    // Initialize Result
    // TO DO: this allocation is slow, one may check that if n < THRESHOLD, static allocation may be used instead
    int *next = (int *)bach_newptr(n* sizeof(int));
    int *done = (int *)bach_newptr(n* sizeof(int));
    for (int i = 0; i < n; i++) {
        next[i] = -1;
        done[i] = 0;
    }
	
    // Find the leftmost point
    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[l].x)
            l = i;
	
    // Start from leftmost point, keep moving counterclockwise
    // until reach the start point again
    int p = l, q;
    do
    {
        // Search for a point 'q' such that orientation(p, i, q) is
        // counterclockwise for all points 'i'
        q = (p+1)%n;
        for (int i = 0; i < n; i++)
			if (!done[i] && pt_orientation(points[p], points[i], points[q]) == 2)
				q = i;
		
        next[p] = q;  // Add q to result as a next point of p
        done[q] = 1;
        p = q; // Set p as q for next iteration
    } while (p != l);
	
    // Get Result
	long i = l;
	
	poly->num_vertices = 0;
	poly->vertex[poly->num_vertices++] = points[l];
										  
	while (next[i] != -1 && next[i] != l) {
		poly->vertex[poly->num_vertices++] = points[next[i]];
		i = next[i];
	}
    bach_freeptr(next);
    bach_freeptr(done);
}


t_pt get_random_pt_near_pt(t_pt pt, double min_dist, double max_dist)
{
	double dist = rand_range(min_dist, max_dist);
	double alpha = rand_range(0, TWO_PI);
	return build_pt(pt.x + dist * cos(alpha), pt.y + dist * sin(alpha));
}

t_pt get_random_pt_in_rect(t_rect rect)
{
	return build_pt(rand_range(rect.x, rect.x + rect.width), rand_range(rect.y, rect.y + rect.height));
}



char is_pt_in_rectangle_extended(t_pt pt, t_rect rect) 
{
	double min_y = MIN(rect.y, rect.y + rect.height);
	double max_y = MAX(rect.y, rect.y + rect.height);
	double min_x = MIN(rect.x, rect.x + rect.width);
	double max_x = MAX(rect.x, rect.x + rect.width);
	if (pt.x >= min_x && pt.x <= max_x && pt.y >= min_y && pt.y <= max_y)
		return 1;
	return 0;
}


t_rect rect_baricentric_to_boundingbox(t_rect baricentric)
{
	t_rect boundingbox;
	boundingbox.width = baricentric.width;
	boundingbox.height = baricentric.height;
	boundingbox.x = baricentric.x - baricentric.width/2.;
	boundingbox.y = baricentric.y - baricentric.height/2.;
	return boundingbox;
}

t_rect rect_boundingbox_to_baricentric(t_rect boundingbox)
{
	t_rect baricentric;
	baricentric.width = boundingbox.width;
	baricentric.height = boundingbox.height;
	baricentric.x = boundingbox.x + boundingbox.width/2.;
	baricentric.y = boundingbox.y + boundingbox.height/2.;
	return baricentric;
}
