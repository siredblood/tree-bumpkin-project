
//
//	Åö×²¼ì²â»Øµ÷Àà
//

#pragma once
#include "chunk/chunk_obstacle.hpp"
#include "chunk/chunk_manager.hpp"
#include "chunk/chunk_space.hpp"
#include "chunk/chunk.hpp"

class CustomCollision : public CollisionCallback
{
public:
	virtual int operator()( const ChunkObstacle & obstacle,
		const WorldTriangle & triangle, float dist );

	float getCollideDist()
	{
		return fDist_;
	}
	
	ChunkItemPtr getCollideObstacle()
	{
		return obstacleItem_;
	}
	
private:
	float fDist_;
	ChunkItemPtr obstacleItem_;
};
