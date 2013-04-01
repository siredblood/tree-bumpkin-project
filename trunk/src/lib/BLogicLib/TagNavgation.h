#pragma once
#include "BllHelp.h"

struct TAGNAVIGATION
{
	string iId;			 //���
	string strName;		 //����
	string strCondinate; //����
	string strType;		 //����
	string strTarger;	 //����Ŀ��
	string strRemark;    //��ע
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
