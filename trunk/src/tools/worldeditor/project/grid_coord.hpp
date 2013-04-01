#ifndef GRID_COORD_HPP
#define GRID_COORD_HPP

#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"
#include "math/vector2.hpp"


/** Basically an int vector */
class GridCoord
{
public:
	GridCoord( int xc, int yc );
	GridCoord( Vector2 v );

	int x;
	int y;

	GridCoord operator+ (const GridCoord& rhs ) const;

	static GridCoord zero();
	static GridCoord invalid();
};

class GridRect
{
public:
	GridRect( GridCoord bl, GridCoord tr );

	GridCoord bottomLeft;
	GridCoord topRight;

	bool valid() const;
	void clamp( int minX, int minY, int maxX, int maxY );

	GridRect operator+ (const GridCoord& rhs ) const;

	static GridRect zero();
	/** Create a GridRect from any two points */
	static GridRect fromCoords( GridCoord a, GridCoord b);
};


#endif // GRID_COORD_HPP
