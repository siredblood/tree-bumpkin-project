#include "pch.hpp"
#include "worldeditor/collisions/closest_obstacle_no_edit_stations.hpp"


ClosestObstacleNoEditStations ClosestObstacleNoEditStations::s_default;


/*virtual*/ int ClosestObstacleNoEditStations::operator()
( 
    ChunkObstacle   const &obstacle,
    WorldTriangle   const &/*triangle*/, 
    float           /*dist*/ 
)
{
    if 
    (
        obstacle.pItem()->isEditorChunkStationNode()
        ||
        obstacle.pItem()->isEditorChunkLink()
		||
		obstacle.pItem()->isEditorUserDataObject()
		||
		obstacle.pItem()->isEditorEntity()
    )
    {
        return COLLIDE_ALL;
    }
    else
    {
        return COLLIDE_BEFORE;
    }
}   
