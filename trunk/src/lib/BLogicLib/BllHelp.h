#pragma once
#include "BllHead.h"

class CBllHelp
{
public:
	CBllHelp();
	~CBllHelp();
public:
	static CBllHelp & Instance();
	void QueryByCondit(_RecordsetPtr pRecordSet,vector<string>  &vecField, vector<string>  &vecRecordSet, long &lFieldCounts);
private:
	static CBllHelp instance;
	_bstr_t GetDataTypeString(adoDataTypeEnum enumType);
};