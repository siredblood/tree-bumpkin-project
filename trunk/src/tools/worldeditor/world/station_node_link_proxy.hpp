#ifndef STATION_NODE_LINK_PROXY_HPP
#define STATION_NODE_LINK_PROXY_HPP


#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"
#include "gizmo/link_proxy.hpp"


/**
 *  This is a proxy that implements linking and testing of linking between
 *  EditorChunkStationNode's.
 */
class StationNodeLinkProxy : public LinkProxy
{
public:
    explicit StationNodeLinkProxy
    (
        EditorChunkStationNode      &node
    );

    /*virtual*/ ~StationNodeLinkProxy();

    /*virtual*/ LinkType EDCALL linkType() const;

    /*virtual*/ MatrixProxyPtr EDCALL createCopyForLink();

    /*virtual*/ TargetState EDCALL canLinkAtPos(ToolLocatorPtr locator) const;

    /*virtual*/ void EDCALL createLinkAtPos(ToolLocatorPtr locator);

    /*virtual*/ ToolLocatorPtr EDCALL createLocator() const;

private:
    StationNodeLinkProxy(StationNodeLinkProxy const &);
    StationNodeLinkProxy &operator=(StationNodeLinkProxy const &);

	void relinkEntities( StationGraph* oldGraph, StationGraph* newGraph );
	void relinkEntitiesInChunk( ChunkStationNode* node,
								StationGraph* graph,
								std::string& chunkID );
private:
    EditorChunkStationNode          *node_;
};


#endif // STATION_NODE_LINK_PROXY_HPP
