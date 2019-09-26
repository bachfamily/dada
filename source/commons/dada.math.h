/**
	@file
	dada.math.h
	Mathematic utilities header for dada library
 
	by Daniele Ghisi
 */

#ifndef _DADA_MATH_H_
#define _DADA_MATH_H_


double fast_pow(double a, double b);
double rand_range(double min, double max);
void normalize_array(double *val, long num_vals, double norm);

#endif // _DADA_MATH_H_

