#include "pch.hpp"
#include "BuildingPropertyMgr.h"

CBuildingPropertyMgr CBuildingPropertyMgr::s_instance;

CBuildingPropertyMgr::CBuildingPropertyMgr()
{

}

CBuildingPropertyMgr::~CBuildingPropertyMgr()
{

}

CBuildingPropertyMgr &CBuildingPropertyMgr::Instance()
{
	return s_instance;
}

void CBuildingPropertyMgr::GetColumns(std::vector<std::string> &vColumns)
{
	LinkedStringMap mapProperty;
	CDBBuildingProperty::Query("1", mapProperty);
	// µ¹Ðð·ÃÎÊ
	for(LinkedStringMap::reverse_iterator citr=mapProperty.rbegin();
		citr!=mapProperty.rend(); ++citr)
	{
		vColumns.push_back((*citr).first);
	}
}

bool CBuildingPropertyMgr::Load(std::vector<LinkedStringMap> &vProperties)
{
	return CDBBuildingProperty::Query(vProperties);
}

bool CBuildingPropertyMgr::Save(const std::vector<LinkedStringMap> &vProperties)
{
	return CDBBuildingProperty::Save(vProperties);
}

bool CBuildingPropertyMgr::Delete(const std::vector<std::string> &vIds)
{
	return CDBBuildingProperty::Delete(vIds);
}