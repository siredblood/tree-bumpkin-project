#ifndef COLLISION_CALLBACKS_HPP
#define COLLISION_CALLBACKS_HPP


#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"
#include "chunk/chunk_obstacle.hpp"
#include "physics2/worldtri.hpp"


/**
 *	This class finds the first collision with a forward
 *	facing polygon
 */
class ObstacleLockCollisionCallback : public CollisionCallback
{
public:
	virtual int operator()( const ChunkObstacle & obstacle,
		const WorldTriangle & triangle, float dist );

	virtual void clear();

	float dist_;
	Vector3 normal_;
	ChunkItemPtr pItem_;
	Vector3 triangleNormal_;
	static ObstacleLockCollisionCallback s_default;
};


#endif // COLLISION_CALLBACKS_HPP
