#pragma once

#include <comutil.h> 
#include "DBHead.h"
using namespace std;

//数据库类型枚举
enum DatabaseType
{
	NullType,
	AccessType,
	SqlServerType,
	OracleType
};
//字段类型枚举
enum FieldType
{
	IntType,
	FloatType,
	CharType,
	DateType
};

#define CListFields list<_bstr_t> 
#define CMapFields map<_bstr_t,_bstr_t>

class CFields
{
public:
	CFields();
	~CFields();

public:
	//函数：AddField，添加字段，传入多个字段信息，通过GetFieldFormat获取格式化字符串
	//参数：
	//	strFieldName：	字段名
	//	enumFieldType：	字段类型
	//	iFieldSize：	字段大小
	//	bIsNull：		是否空
	//	strDefaultValue：缺省值
	//返回值：无
	void AddField(_bstr_t strFieldName, FieldType enumFieldType, 
		int iFieldSize, BOOL bIsNull = TRUE, _bstr_t strDefaultValue = "");
	//获取格式化字符串
	//例如：通过AddField添加了ID、NAME字段
	//返回值：ID CHAR(10) NOT NULL,NAME CHAR(20),NULL
	_bstr_t GetFieldFormat();

	//添加字段名称和字段值
	void AddFieldValue(_bstr_t strFieldColumn, _bstr_t strFieldValue);
	///获取字段名称和字段值的格式化字符串
	//例如：通过AddFieldValue添加了ID,NAME,AGE，及相应值100,NAME1,20
	//	strColumns=ID,NAME,AGE
	//	strValues=100,'NAME1',20
	void GetFieldValuesFormat(_bstr_t &strColumns, _bstr_t &strValues);
	///返回修改记录的格式化字符串
	_bstr_t GetFieldModifyFormat();

	///设置数据库类型
	static void SetDatabaseType(DatabaseType enumType);

	//清空List和Map容器内容，
	//再次调用AddField时使用ClearListFields
	//再次调用AddFieldValue时使用AddFieldValue
	void ClearListFields();
	void ClearMapFields();


private:
	//获取类型字符串
	_bstr_t GetType(FieldType enumFieldType);
	_bstr_t GetAccessType(FieldType enumFieldType);
	_bstr_t GetSqlServerType(FieldType enumFieldType);
	_bstr_t GetOracleType(FieldType enumFieldType);
private:
	CListFields m_listField;				//字段信息字符串
	CMapFields m_mapFields;					//字段列和值
	static DatabaseType m_enumDatabaseType;	//数据库类型
};