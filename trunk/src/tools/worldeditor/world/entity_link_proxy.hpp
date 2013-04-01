#ifndef ENTITY_LINK_PROXY_HPP
#define ENTITY_LINK_PROXY_HPP


#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"
#include "worldeditor/world/items/editor_chunk_entity.hpp"
#include "gizmo/link_proxy.hpp"

/**
 *  This is a proxy that implements linking and testing of linking between an
 *  EditorChunkEntity and EditorChunkStationNodes.
 */
class EntityLinkProxy : public LinkProxy
{
public:
    explicit EntityLinkProxy
    (
        EditorChunkEntity       *entity
    );

    /*virtual*/ ~EntityLinkProxy();

    /*virtual*/ LinkType EDCALL linkType() const;

    /*virtual*/ MatrixProxyPtr EDCALL createCopyForLink();

    /*virtual*/ TargetState EDCALL canLinkAtPos(ToolLocatorPtr locator) const;

    /*virtual*/ void EDCALL createLinkAtPos(ToolLocatorPtr locator);

    /*virtual*/ ToolLocatorPtr EDCALL createLocator() const;

private:
    EntityLinkProxy(EntityLinkProxy const &);
    EntityLinkProxy &operator=(EntityLinkProxy const &);

private:
    EditorChunkEntityPtr        entity_;
};


#endif // ENTITY_LINK_PROXY_HPP
