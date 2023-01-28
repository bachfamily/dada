/**
	@file
	dada.peanomath.c
	Mathematic functions for peano mapping

	by Daniele Ghisi
*/

#include "dada.peanomath.h"

void sphericalToCartesian(double *spherical, double *cartesian, long N)
{
    double r = spherical[0];
    double temp = 1.;
    for (long i = 0; i < N-1; i++) {
        cartesian[i] = r * temp * cos(spherical[i+1]);
        temp *= sin(spherical[i+1]);
    }
    cartesian[N-1] = r * temp;
}

// spherical is assumed to be of dimension step*(N-1), with unexplicited radius = 1
void sphericalToCartesianNoRadiusWithStep(double *spherical, double *cartesian, long N, int step)
{
    double temp = 1.;
    long s = 0;
    for (long i = 0; i < N-1; i++, s += step) {
        cartesian[i] = temp * cos(spherical[s]);
        temp *= sin(spherical[s]);
    }
    cartesian[N-1] = temp;
}


void cartesianToSpherical(double *cartesian, double *spherical, long N)
{
    double temp = 0.;
    for (long i = 0; i < N; i++)
        temp += cartesian[i] * cartesian[i];
    spherical[0] = sqrt(temp);
    
    temp = cartesian[N-1]*cartesian[N-1];
    for (long i = N-2; i >= 0; i--) {
        temp += cartesian[i] * cartesian[i];
        spherical[i+1] = (temp == 0 ? 0 : cartesian[i]/sqrt(temp));
    }
}


// PEANO INVERSO: prendo un numero tra 0 e 1 e lo butto su [0, 1]^N
void ternaryDigitsToHyperCube(short *ternary_digits, long N, double *output_coord, long precision)
{
    for (long i = 0; i < N; i++)
        output_coord[i] = 0;
    
    // building partial sum array, for optimization
    double *ternary_digits_sum = (double *)malloc((N*precision) * sizeof(double)); // TODO: avoid this allocation
    double *ternary_digits_colsum = (double *)malloc(precision * sizeof(double)); // TODO: avoid this allocation
    double temp = 0;
    for (long i = 0; i < N*precision; i++) {
        temp += ternary_digits[i];
        ternary_digits_sum[i] = temp;
    }

    for (long i = 1; i <= N; i++) {
        
        // building partial sum array, for optimization
        double temp = 0;
        for (long s = 0; s < precision; s++) {
            temp += ternary_digits[i+s*N-1];
            ternary_digits_colsum[s] = temp;
        }
  
        long div = 3;
        for (long j = 0; j < precision; j++) {
            long partialsum = 0;
            long ijn1 = i+j*N-1;
            
// Naive version:
//            long partialsum_naive = 0;
//            for (long s = 1; s <= i+j*N; s++) partialsum_naive += ternary_digits[s-1];
//            for (long s = 0; s <= j; s++) partialsum_naive -= ternary_digits[i+s*N-1];


// Optimized version:
            partialsum = ternary_digits_sum[ijn1];
            partialsum -= ternary_digits_colsum[j];
//            assert(partialsum == partialsum_naive);

            if (partialsum % 2 == 0)
                output_coord[i-1] += (double)ternary_digits[ijn1]/div;
            else
                output_coord[i-1] += (double)(2 - ternary_digits[ijn1])/div;

            div *= 3;
        }
    }
    
    free(ternary_digits_sum);
    free(ternary_digits_colsum);
}

void unitIntervalToTernaryRepresentation(mpfr_t input, long numdigits, short *ternary_digits)
{
    if (mpfr_cmp_d(input, 1.) >= 0) {
        for (long i = 0; i < numdigits; i++)
            ternary_digits[i] = 2;
    } else {
        mpz_t div;
        mpz_init(div);
        mpz_set_ui(div, 3);

        mpfr_t temp, d;
        mpfr_init2(d, mpfr_get_prec(input) * 2);
        mpfr_init2(temp, mpfr_get_prec(input) * 2);
        mpfr_set(temp, input, MPFR_RNDN);
        for (long i = 0; i < numdigits; i++) {
            mpfr_mul_z(d, temp, div, MPFR_RNDN);
            mpfr_floor(d, d);
            long digit = mpfr_get_ui(d, MPFR_RNDN);
            mpfr_div_z(d, d, div, MPFR_RNDN);
            mpfr_sub(temp, temp, d, MPFR_RNDN);
            mpz_mul_ui(div, div, 3);
            ternary_digits[i] = (digit < 0 ? 0 : (digit > 2 ? 2 : digit));
        }
        mpfr_clear(temp);
        mpfr_clear(d);
        mpz_clear(div);
    }
}

void unitIntervalToTernaryRepresentation(double input, long numdigits, short *ternary_digits)
{
    if (input >= 1.) {
        for (long i = 0; i < numdigits; i++)
            ternary_digits[i] = 2;
    } else {
        long div = 3;
        double temp = input;
        for (long i = 0; i < numdigits; i++) {
            long digit = (int)(temp*div);
            temp -= (double)digit/div;
            div *= 3;
            ternary_digits[i] = (digit < 0 ? 0 : (digit > 2 ? 2 : digit));
        }
    }
}

// Map a number between [0, 1] in a number in [0,1]^n via a Peano curve
void unitIntervalToHyperCube(mpfr_t input, long N, double *output_coord, long precision)
{
    short *ternary_digits = (short *)malloc((N*precision) * sizeof(short)); // TODO: avoid this allocation
    unitIntervalToTernaryRepresentation(input, N*precision, ternary_digits);
    ternaryDigitsToHyperCube(ternary_digits, N, output_coord, precision);
    free(ternary_digits);
}

void unitIntervalToHyperCube(double input, long N, double *output_coord, long precision)
{
    short *ternary_digits = (short *)malloc((N*precision) * sizeof(short)); // TODO: avoid this allocation
    unitIntervalToTernaryRepresentation(input, N*precision, ternary_digits);
    ternaryDigitsToHyperCube(ternary_digits, N, output_coord, precision);
    free(ternary_digits);
}
