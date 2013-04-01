#pragma once

#include <comutil.h> 
#include "DBHead.h"
using namespace std;

//���ݿ�����ö��
enum DatabaseType
{
	NullType,
	AccessType,
	SqlServerType,
	OracleType
};
//�ֶ�����ö��
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
	//������AddField������ֶΣ��������ֶ���Ϣ��ͨ��GetFieldFormat��ȡ��ʽ���ַ���
	//������
	//	strFieldName��	�ֶ���
	//	enumFieldType��	�ֶ�����
	//	iFieldSize��	�ֶδ�С
	//	bIsNull��		�Ƿ��
	//	strDefaultValue��ȱʡֵ
	//����ֵ����
	void AddField(_bstr_t strFieldName, FieldType enumFieldType, 
		int iFieldSize, BOOL bIsNull = TRUE, _bstr_t strDefaultValue = "");
	//��ȡ��ʽ���ַ���
	//���磺ͨ��AddField�����ID��NAME�ֶ�
	//����ֵ��ID CHAR(10) NOT NULL,NAME CHAR(20),NULL
	_bstr_t GetFieldFormat();

	//����ֶ����ƺ��ֶ�ֵ
	void AddFieldValue(_bstr_t strFieldColumn, _bstr_t strFieldValue);
	///��ȡ�ֶ����ƺ��ֶ�ֵ�ĸ�ʽ���ַ���
	//���磺ͨ��AddFieldValue�����ID,NAME,AGE������Ӧֵ100,NAME1,20
	//	strColumns=ID,NAME,AGE
	//	strValues=100,'NAME1',20
	void GetFieldValuesFormat(_bstr_t &strColumns, _bstr_t &strValues);
	///�����޸ļ�¼�ĸ�ʽ���ַ���
	_bstr_t GetFieldModifyFormat();

	///�������ݿ�����
	static void SetDatabaseType(DatabaseType enumType);

	//���List��Map�������ݣ�
	//�ٴε���AddFieldʱʹ��ClearListFields
	//�ٴε���AddFieldValueʱʹ��AddFieldValue
	void ClearListFields();
	void ClearMapFields();


private:
	//��ȡ�����ַ���
	_bstr_t GetType(FieldType enumFieldType);
	_bstr_t GetAccessType(FieldType enumFieldType);
	_bstr_t GetSqlServerType(FieldType enumFieldType);
	_bstr_t GetOracleType(FieldType enumFieldType);
private:
	CListFields m_listField;				//�ֶ���Ϣ�ַ���
	CMapFields m_mapFields;					//�ֶ��к�ֵ
	static DatabaseType m_enumDatabaseType;	//���ݿ�����
};