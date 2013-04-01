#include "pch.hpp"
#include "view_distance.hpp"
#include "appmgr/options.hpp"
#include "worldeditor/misc/world_editor_camera.hpp"

ViewDistance ViewDistance::instance_;

ViewDistance::ViewDistance()
{
	TaskManager::instance().add( this, "ViewDistance", NULL );
}

ViewDistance::~ViewDistance()
{}

void ViewDistance::init()
{
	fDistance_ = Options::getOptionFloat( "viewDistance", 1800 );
}

void ViewDistance::tick( float dTime )
{
	Matrix tmpView = WorldEditorCamera::instance().currentCamera().view();
	tmpView.invert();
	Vector3 pos = tmpView.applyToUnitAxisVector(3);
	if ( pos.y > fDistance_ )
	Options::setOptionInt( "render/scenery", 0 );
	else
	Options::setOptionInt( "render/scenery", 1 );
}

ViewDistance & ViewDistance::instance()
{
	return instance_;
}

