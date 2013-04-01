#include "pch.hpp"
#include "worldeditor/collisions/collision_terrain_only.hpp"


CollisionTerrainOnly CollisionTerrainOnly::s_default;


/*virtual*/ int CollisionTerrainOnly::operator()(
	const ChunkObstacle& /*obstacle*/, const WorldTriangle& triangle,
	float /*dist*/ )
{
	if (triangle.flags() & TRIANGLE_TERRAIN)
		return COLLIDE_BEFORE;
	else
		return COLLIDE_ALL;
}   
