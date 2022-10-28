/**
	@file
	dada.h
	Header for the dada library
 
	by Daniele Ghisi
 */

#ifndef _DADA_H_
#define _DADA_H_


#include "foundation/bach.h"
#include "ext.h"							// standard Max include, always required
#include "ext_obex.h"						// required for new style Max object
#include "ext_atomic.h"						// atomic operations
#include "jpatcher_api.h"
#include "jgraphics.h"
#include "graphics/bach_graphics.h"
#include "graphics/llll_modifiers.h"
#include "foundation/llll_commons.h"
#include "foundation/llllobj.h"
#include "math/bach_math_utilities.h"
#include "foundation/llll_commons_ext.h"
#include "graphics/bach_jit.h"

#ifdef WIN_VERSION
#define DADA_VERSION "0.2.6"
#endif

// DEBUG FLAGS
// #define DADA_DEBUG_UNDO

#endif // _DADA_H_
