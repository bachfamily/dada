/**
	@file
	dada.windows.h
	Windowing utilities header for dada library
 
	by Daniele Ghisi
 */

#ifndef _DADA_WINDOWS_H_
#define _DADA_WINDOWS_H_

#include "dada.h"

/** Window types.	@ingroup windows */
typedef enum _dada_windows
{
    DADA_WINDOW_NONE		= 0,
	DADA_WINDOW_RECTANGULAR,
	DADA_WINDOW_TRIANGULAR,
    DADA_WINDOW_COSINE,
    DADA_WINDOW_HANNING,
    DADA_WINDOW_BLACKMAN,
} e_dada_windows;


double dada_get_window_value(e_dada_windows type, double t);

e_dada_windows symbol_to_window(t_symbol *sym);
t_symbol *window_to_symbol(e_dada_windows win);

#endif // _DADA_WINDOWS_H_

