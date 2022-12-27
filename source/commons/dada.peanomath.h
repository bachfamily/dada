/**
	@file
	dada.math.h
	Mathematic functions for peano mapping
 
	by Daniele Ghisi
 */

#ifndef _DADA_PEANOMATH_H_
#define _DADA_PEANOMATH_H_

#include "math.h"
#include <mpfr.h>
#include <gmp.h>

void cartesianToSpherical(double *cartesian, double *spherical, long N);
void sphericalToCartesian(double *spherical, double *cartesian, long N);

// somewhat internal version
void sphericalToCartesianNoRadiusWithStep(double *spherical, double *cartesian, long N, int step);

void ternaryDigitsToHyperCube(short *ternary_digits, long N, double *output_coord, long precision);

void unitIntervalToTernaryRepresentation(double input, long numdigits, short *ternary_digits);
void unitIntervalToTernaryRepresentation(mpfr_t input, long numdigits, short *ternary_digits);

void unitIntervalToHyperCube(double input, long N, double *output_coord, long precision);
void unitIntervalToHyperCube(mpfr_t input, long N, double *output_coord, long precision);

#endif // _DADA_PEANOMATH_H_

