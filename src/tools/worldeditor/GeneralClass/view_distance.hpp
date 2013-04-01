#ifndef VIEW_DISTANCE_HPP
#define VIEW_DISTANCE_HPP

#include "worldeditor/BaseFramework/ITask.hpp"

class ViewDistance  : public ITask
{
public:
	ViewDistance();
	~ViewDistance();
	
	void init();
	void tick( float dTime );

	static ViewDistance &instance();

private:
	float fDistance_;
	static ViewDistance instance_;
};

#endif	//VIEW_DISTANCE_HPP