#include "pch.hpp"
#include "CustomCollision.h"

int CustomCollision::operator()( const ChunkObstacle & obstacle,
							   const WorldTriangle & triangle, float dist )
{
	fDist_ = dist;
	
	obstacleItem_ = obstacle.pItem();
	
	// //INFO_MSG( "fDist_ = %f\n", fDist_ );
	return COLLIDE_BEFORE;

}