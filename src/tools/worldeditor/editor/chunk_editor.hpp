#ifndef CHUNK_EDITOR_HPP
#define CHUNK_EDITOR_HPP


#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"
#include "gizmo/general_editor.hpp"


/**
 *	This class facilitates and controls the editing of a chunk itself,
 *	as opposed to the items within it.
 */
class ChunkEditor : public GeneralEditor
{
	Py_Header( ChunkEditor, GeneralEditor )

public:
	ChunkEditor( Chunk * pChunk, PyTypePlus * pType = &s_type_ );
	~ChunkEditor();

	PyObject *		pyGetAttribute( const char * attr );
	int				pySetAttribute( const char * attr, PyObject * value );

	PyObject * pyGet_contents();
	PY_RO_ATTRIBUTE_SET( contents )

	PyObject * pyGet_isWriteable();
	PY_RO_ATTRIBUTE_SET( isWriteable )

	PY_FACTORY_DECLARE()

private:
	ChunkEditor( const ChunkEditor& );
	ChunkEditor& operator=( const ChunkEditor& );

	Chunk * pChunk_;
};


#endif // CHUNK_EDITOR_HPP
