//-----------------------------------------------------//
//	Í¨ÓÃº¯Êý										   //
//-----------------------------------------------------//

#include "pch.hpp"
#include "common_public.hpp"
#include "worldeditor/misc/world_editor_camera.hpp"
#include "CameraTravel/CustomWorldCamera.h"

CommonPublic::CommonPublic()
{

}

CommonPublic & CommonPublic::instance()
{
	static CommonPublic s_instance;
	return s_instance;
}

bool CommonPublic::containtString( const std::string &mainStr, const std::string &str )
{
	std::string::size_type pos;
	pos = mainStr.find( str );

	if (pos != std::string::npos)
		return true;
	else
		return false;
}