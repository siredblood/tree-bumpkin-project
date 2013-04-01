#ifndef WORLD_EDITOR_SCRIPT_HPP
#define WORLD_EDITOR_SCRIPT_HPP


#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"
#include <Python.h>


/**
 *	This namespace contains functions relating to scripting WorldEditor.
 */
namespace WorldEditorScript
{
	bool init( DataSectionPtr pDataSection );
	void fini();
}


#ifdef CODE_INLINE
#include "world_editor_script.ipp"
#endif


#endif // WORLD_EDITOR_SCRIPT_HPP
