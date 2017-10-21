/**
	@file
	dada.windows.c
	Windowing utilities for dada library

	by Daniele Ghisi
*/

#include "dada.windows.h"

e_dada_windows symbol_to_window(t_symbol *sym)
{
    if (sym == gensym("rectangular") || sym == gensym("rect"))
        return DADA_WINDOW_RECTANGULAR;
    
    if (sym == gensym("triangular") || sym == gensym("tri"))
        return DADA_WINDOW_TRIANGULAR;

    if (sym == gensym("cosine") || sym == gensym("sine"))
        return DADA_WINDOW_COSINE;

    if (sym == gensym("hanning"))
        return DADA_WINDOW_HANNING;

    if (sym == gensym("blackman"))
        return DADA_WINDOW_BLACKMAN;
    
    return DADA_WINDOW_NONE;
}

t_symbol *window_to_symbol(e_dada_windows win)
{
    switch (win) {
        case DADA_WINDOW_RECTANGULAR: return gensym("rectangular");
        case DADA_WINDOW_TRIANGULAR: return gensym("triangular");
        case DADA_WINDOW_COSINE: return gensym("cosine");
        case DADA_WINDOW_HANNING: return gensym("hanning");
        case DADA_WINDOW_BLACKMAN: return gensym("blackman");
            
        default: return _llllobj_sym_none;
    }
}

// t is from 0 to 1
double dada_get_window_value(e_dada_windows type, double t)
{
    switch (type) {
        case DADA_WINDOW_RECTANGULAR:
            return (t >= 0 && t <= 1) ? 1. : 0.;
            break;

        case DADA_WINDOW_TRIANGULAR:
            if (t < 0 || t > 1)
                return 0.;
            else
                return 1 - 2 * fabs(t - 0.5);
            break;

        case DADA_WINDOW_COSINE:
            if (t < 0 || t > 1)
                return 0.;
            else
                return cos(PI * (t - 0.5));
            break;

        case DADA_WINDOW_HANNING:
            if (t < 0 || t > 1)
                return 0.;
            else
                return 0.5 * (1 - cos(TWOPI * t));
            break;

        case DADA_WINDOW_BLACKMAN:
            if (t < 0 || t > 1)
                return 0.;
            else
                return 0.42 - 0.5 * cos(TWOPI * t) + 0.06 * cos(2 * TWOPI * t);
            break;

            
        default:
            return 1.;
            break;
    }
}
