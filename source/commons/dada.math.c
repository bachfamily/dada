/**
	@file
	dada.math.c
	Mathematic utilities for dada library

	by Daniele Ghisi
*/

#include "dada.math.h"
#include <math.h>
#include <stdlib.h>

double fast_pow(double a, double b) {
	union {
		double d;
		int x[2];
	} u = { a };
	u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
	u.x[0] = 0;
	return u.d;
}

double rand_range(double min, double max)
{
	double val = ((double)rand()/(double)RAND_MAX) * (max - min) + min;
	return val;
}


void normalize_array(double *val, long num_vals, double norm)
{
    long i;
    if (norm < 0) {
        // infinty norm (sup)
        double max = -1;
        long max_i = -1;
        for (i = 0; i < num_vals; i++) {
            if (fabs(val[i]) > max) {
                max_i = i;
                max = fabs(val[i]);
            }
        }
        
        for (i = 0; i < num_vals; i++)
            val[i] = 0;
        if (max_i >= 0)
            val[max_i] = 1;
        return;
    }
    
    // l^p norms
    
    double tot = 0;
    
    for (i = 0; i < num_vals; i++)
        tot += pow(val[i], norm);
    
    for (i = 0; i < num_vals; i++)
        val[i] = pow(val[i], norm) / tot;
}
