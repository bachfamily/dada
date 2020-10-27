/**
	@file
	dada.math.h
	Mathematic functions for peano mapping
 
	by Daniele Ghisi
 */

#ifndef _DADA_PEANOMATH_H_
#define _DADA_PEANOMATH_H_

#include <mpfr.h>
#include <gmp.h>

void cartesianToSpherical(double *cartesian, double *spherical, long N);
void sphericalToCartesian(double *spherical, double *cartesian, long N);

void ternaryDigitsToHyperCube(short *ternary_digits, long N, long precision, double *output_coord);

void unitIntervalToTernaryRepresentation(double input, long numdigits, short *ternary_digits);
void unitIntervalToTernaryRepresentation(mpfr_t input, long numdigits, short *ternary_digits);

void unitIntervalToHyperCube(double input, long N, long precision, double *output_coord);
void unitIntervalToHyperCube(mpfr_t input, long N, long precision, double *output_coord);

#endif // _DADA_PEANOMATH_H_

