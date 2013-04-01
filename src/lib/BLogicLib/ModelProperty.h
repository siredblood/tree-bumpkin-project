#pragma once
#include "DBHelper.h"
#include "BllHelp.h"

#define MapFields map<_bstr_t,_bstr_t,less<_bstr_t>>
#define BStrVector vector<_bstr_t>
typedef pair <CString, CString> CString_Pair;

class CModelProperty
{
public:
	CModelProperty(void);
	~CModelProperty(void);

private:
	//检查字段名是否存在
	bool CheckFieldNameExist(CString strFieldName);
	//将文字型的字段类型转化为数据库字段类型
	CString GetFieldTypeByString(CString strTypeString);
	//将数据类型转化为中文类型
	CString GetChianeseTypeByDataType(adoDataTypeEnum datatype);
	//得到表的所有字段用，隔开
	_bstr_t GetFieldNames();
public:
	//加载三维模型信息
	//传入参数：GUID
	std::map<CString,CString> LoadInfo(CString strGUID);
	//保存属性给三维模型
	//参数：模型GUID，字段的键值
	BOOL SaveInfo(CString strGuid, MapFields &mapFlds);
	//删除三维模型属性
	//传入参数：GUID
	BOOL Delete(CString strGuid);

	//查询所有三维模型属性列表
	_RecordsetPtr QueryModelProperty(CString strWhere);
	//查询所有三维模型属性列表,返回绑定列表使用
	void QueryModelProperty(CString strWhere,std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts);

	//////////////////////////////////////////////////////////////////////////

	//添加三维模型属性字段
	BOOL AddField(CString strFieldName, CString enumFieldType, int iFieldSize);
	//修改三维模型属性字段
	BOOL UpdateField(CString strOldFieldName,CString strNewFieldName,  CString enumFieldType, 
		int iFieldSize);
	//删除三维模型属性字段
	BOOL DeleteField(CString strFieldName);

	//查询三维模型属性表所有字段列表
	FieldsPtr  QueryPropertyFields();
	//查询所有三维模型属性列表,返回绑定列表使用
	void QueryPropertyFields(std::vector<CString> &vecField, std::vector<CString> &vecRecordSet, long &lFieldCounts);
};
