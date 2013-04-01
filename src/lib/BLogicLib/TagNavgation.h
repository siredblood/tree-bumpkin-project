#pragma once
#include "BllHelp.h"

struct TAGNAVIGATION
{
	string iId;			 //编号
	string strName;		 //名称
	string strCondinate; //坐标
	string strType;		 //类型
	string strTarger;	 //所属目标
	string strRemark;    //备注
};

class CTagNavgation
{
public:
	CTagNavgation(void);
	~CTagNavgation(void);
	
	BOOL ConnectValidate();
	BOOL CheckName(string strName,string id);
	BOOL Save();
	BOOL SaveList();
	BOOL Delete(string strIds);
	std::vector<TAGNAVIGATION> GetList(string strCondition);
};
