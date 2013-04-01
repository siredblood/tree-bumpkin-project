#include "TagNavgation.h"

CTagNavgation::CTagNavgation(void)
{
}

CTagNavgation::~CTagNavgation(void)
{
}
BOOL CTagNavgation::ConnectValidate()
{
	return FALSE;
}
BOOL CTagNavgation::CheckName(string strName,string id)
{
	return FALSE;
}
BOOL CTagNavgation::Save()
{
	return FALSE;
}
BOOL CTagNavgation::SaveList()
{
	return FALSE;
}
BOOL CTagNavgation::Delete(string strIds)
{
	return FALSE;
}
std::vector<TAGNAVIGATION> CTagNavgation::GetList(string strCondition)
{
	std::vector<TAGNAVIGATION> list;
	return list;
}
