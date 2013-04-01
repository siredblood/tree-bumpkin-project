#ifndef CLOSEST_OBSTACLE_NO_EDIT_STATIONS_HPP
#define CLOSEST_OBSTACLE_NO_EDIT_STATIONS_HPP


#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"
#include "chunk/chunk_obstacle.hpp"


/**
 *  This callback is used to filter out collisions with 
 *  EditorChunkStationNodes and EditorChunkLinks.
 */
class ClosestObstacleNoEditStations : public CollisionCallback
{   
public:
    virtual int operator()
    ( 
        ChunkObstacle   const &obstacle,
	    WorldTriangle   const &/*triangle*/, 
        float           /*dist*/ 
    ); 

    static ClosestObstacleNoEditStations s_default;
};

#endif // CLOSEST_OBSTACLE_NO_EDIT_STATIONS_HPP
