#include "pch.hpp"
#include "worldeditor/undo_redo/entity_array_undo.hpp"
#include "common/base_properties_helper.hpp"


EntityArrayUndo::EntityArrayUndo( BasePropertiesHelper* props, int index ) :
	UndoRedo::Operation(int(typeid(EntityArrayUndo).name())),
    props_( props ),
	index_( index )
{
	undoData_ = props_->propGet( index_ );
}


/*virtual*/ void EntityArrayUndo::undo()
{
    UndoRedo::instance().add(new EntityArrayUndo( props_, index_ ));
	props_->propSet( index_, undoData_ );
}


/*virtual*/ bool EntityArrayUndo::iseq( const UndoRedo::Operation& other ) const
{
	return false;
}
