#ifndef EDITOR_CHUNK_TERRAIN_CACHE_HPP
#define EDITOR_CHUNK_TERRAIN_CACHE_HPP


#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"


/**
 *  This class maintains a cache of EditorChunkTerrains.
 */
class EditorChunkTerrainCache
{
public:
	static EditorChunkTerrainCache& instance();

	EditorChunkTerrainPtr findChunkFromPoint(const Vector3& pos) const;

	size_t 
    findChunksWithinBox
    (
		BoundingBox             const &bb,
		EditorChunkTerrainPtrs  &outVector 
    ) const;

private:
	EditorChunkTerrainCache();
};


#endif // EDITOR_CHUNK_TERRAIN_CACHE_HPP
