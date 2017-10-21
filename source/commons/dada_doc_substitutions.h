/**
	@file	dada_doc_substitutions.h
	@brief	Line substitutions for documentation with Doctor Max
	
	by Daniele Ghisi
*/

	
#define DADAOBJ_JBOX_DECLARE_READWRITE_METHODS
// @method read @digest Load from disk
// @description The specified file is read from disk and the llll it contains loaded as current state.
// Syntax is expected to be in the format explained in the <m>dump</m> message documentation.
// @marg 0 @name file_name @optional 1 @type symbol
class_addmethod(c, (method) dadaobj_read,     "read", A_CANT, 0);
// @method write @digest Save in native format
// @description A <m>write</m> message will save the current state (as llll) in a file, in native format.
// If an argument is given, this is the filename (if the file is in the search path
// or in the same folder) or the full file path. If no argument is given, a dialog window pops up.
// Syntax is expected to be in the format explained in the <m>dump</m> message documentation.
// @marg 0 @name file @optional 1 @type symbol
class_addmethod(c, (method) dadaobj_write,	"write", A_CANT, 0);
// @method writetxt @digest Save in text format
// @description A <m>write</m> message will save the current state (as llll) in a file,
// in a human-readable text format.
// If an argument is given, this is the filename (if the file is in the search path
// or in the same folder) or the full file path. If no argument is given, a dialog window pops up.
// Syntax is expected to be in the format explained in the <m>dump</m> message documentation.
// @marg 0 @name file @optional 1 @type symbol
class_addmethod(c, (method) dadaobj_writetxt,	"writetxt", A_CANT, 0);


#define DADAOBJ_JBOX_DECLARE_ACCEPTSDRAG_METHODS
// @method (drag) @digest Load file or set background image
// @description Dragging an llll or text file on the object will load its content, if a proper readable format is recognized.
// If the file is an image, it will be loaded as object background (whenever meaningful)
class_addmethod(c, (method) dadaobj_jbox_acceptsdrag_unlocked,	"acceptsdrag_unlocked", A_CANT, 0);
class_addmethod(c, (method) dadaobj_jbox_acceptsdrag_unlocked,	"acceptsdrag_locked", A_CANT, 0);
