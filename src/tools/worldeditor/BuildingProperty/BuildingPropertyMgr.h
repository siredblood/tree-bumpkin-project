#ifndef _BUILDING_PROPERTY_MGR_H_
#define _BUILDING_PROPERTY_MGR_H_

#include "DBBuildingProperty.h"

class CBuildingPropertyMgr
{
private:
	CBuildingPropertyMgr();
	static CBuildingPropertyMgr s_instance;

public:
	static CBuildingPropertyMgr &Instance();
	~CBuildingPropertyMgr();

public:
	void GetColumns(std::vector<std::string> &vColumns);
	bool Load(std::vector<LinkedStringMap> &vProperties);
	bool Save(const std::vector<LinkedStringMap> &vProperties);
	bool Delete(const std::vector<std::string> &vIds);
};

#endif