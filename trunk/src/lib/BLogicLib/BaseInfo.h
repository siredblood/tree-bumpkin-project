#pragma once
#include "BllHelp.h"
//各种表字段的操作
class CBaseInfo
{
public:
	CBaseInfo(void);
	~CBaseInfo(void);
public:
	//属性
	//方法
	BOOL AddField(_bstr_t strTableName, _bstr_t strFieldName, string enumFieldType, int iFieldSize);
	BOOL UpdateFiled(_bstr_t strTableName,_bstr_t strFieldName, string enumFieldType, int iFieldSize);
	BOOL DeleteFiled(_bstr_t strTableName,_bstr_t strFieldName);
	void QueryFileds(_bstr_t strTableName, std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts);
	FieldType GetDataTypeByString(string strType);
};
