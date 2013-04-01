#ifndef ENTITY_USER_DATA_OBJECT_LINK_OPERATION_HPP
#define ENTITY_USER_DATA_OBJECT_LINK_OPERATION_HPP


#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"
#include "worldeditor/world/items/editor_chunk_entity.hpp"
#include "gizmo/undoredo.hpp"
#include <string>


/**
 *  This class saves the link information for an entity with this
 *  property and undoes changes to this link information.
 */
class EntityUserDataObjectLinkOperation : public UndoRedo::Operation
{
public:
    explicit EntityUserDataObjectLinkOperation
    (
        EditorChunkEntityPtr        entity,
		const std::string&					linkName
    );

	/*virtual*/ void undo();

    /*virtual*/ bool iseq(UndoRedo::Operation const &other) const;

private:
    EntityUserDataObjectLinkOperation(EntityUserDataObjectLinkOperation const &);
    EntityUserDataObjectLinkOperation &operator=(EntityUserDataObjectLinkOperation const &);

protected:
    std::string                 linkName_;
    std::string                 entityLink_;
    EditorChunkEntityPtr        entity_;
};


#endif // ENTITY_USER_DATA_OBJECT_LINK_OPERATION_HPP
