#include "Other.h"
//#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////
DatabaseType CFields::m_enumDatabaseType = NullType;

CFields::CFields()
{
}

CFields::~CFields()
{
	ClearListFields();
	ClearMapFields();
}

void CFields::AddField(_bstr_t strFieldName, FieldType enumFieldType, int iFieldSize, BOOL bIsNull /* = TRUE */, _bstr_t strDefaultValue /* = */ )
{
	_bstr_t strField, strFieldType, strFieldSize, strIsNull;
	strFieldType = GetType(enumFieldType);
	char ch[20];
	_itoa_s(iFieldSize,ch,10);
	strFieldSize = ch;

	if(bIsNull)
		strIsNull = "NULL";
	else 
		strIsNull = "NOT NULL";
	if(m_enumDatabaseType == OracleType)
	{
		if(enumFieldType == CharType)
			strField = strFieldName + " " + strFieldType + "(" + strFieldSize + ") " 
			+ strIsNull;
		else
			strField = strFieldName + " " + strFieldType + " " + strIsNull;
	}
	else
	{
		if(enumFieldType == CharType && m_enumDatabaseType == SqlServerType)
			strField = "[" + strFieldName + "] " + strFieldType + "(" + strFieldSize + ") " 
			+ strIsNull;
		else
			strField = "[" + strFieldName + "] " + strFieldType + " " + strIsNull;
	}
	if(strDefaultValue.length() != 0)
		strField += " " + strDefaultValue;
	m_listField.push_back(strField);
}
_bstr_t CFields::GetFieldFormat()
{
	_bstr_t strFields;
	
	list<_bstr_t>::iterator itr, itr2;
	itr = m_listField.begin();
	itr2 = --m_listField.end();
	while(itr != itr2)
	{
		strFields += (*itr) + ",";
		itr++;
	}
	strFields += (*itr);

	return strFields;
}

void CFields::AddFieldValue(_bstr_t strFieldColumn, _bstr_t strFieldValue)
{
	pair<_bstr_t, _bstr_t> pairField;
	pairField.first = strFieldColumn;
	pairField.second = strFieldValue;
	m_mapFields.insert(pairField);
}

void CFields::GetFieldValuesFormat(_bstr_t &strColumns, _bstr_t &strValues)
{
	CMapFields::iterator itr1, itr2;
	itr1 = m_mapFields.begin();
	itr2 = --m_mapFields.end();
	while(itr1 != itr2)
	{
		strColumns += (*itr1).first + ",";
		strValues += "'" + (*itr1).second + "'" + ",";
		itr1++;
	}
	strColumns += (*itr1).first;
	strValues += "'" + (*itr1).second + "'";
}

_bstr_t CFields::GetFieldModifyFormat()
{
	_bstr_t strResult;
	CMapFields::iterator itr1, itr2;
	itr1 = m_mapFields.begin();
	itr2 = --m_mapFields.end();
	while(itr1 != itr2)
	{
		strResult += (*itr1).first + "='" + (*itr1).second + "',";
		itr1++;
	}
	strResult += (*itr1).first + "='" + (*itr1).second + "'";

	if(!m_mapFields.empty())
		m_mapFields.clear();

	return strResult;
}

_bstr_t CFields::GetType(FieldType enumFieldType)
{
	_bstr_t strType;
	switch(m_enumDatabaseType)
	{
	case AccessType:
		return GetAccessType(enumFieldType);
	case SqlServerType:
		return GetSqlServerType(enumFieldType);
	case OracleType:
		return GetOracleType(enumFieldType);
	default:
		return "";
	}
}

_bstr_t CFields::GetAccessType(FieldType enumFieldType)
{
	switch(enumFieldType)
	{
	case IntType:
		return "LONG";
	case CharType:
		return "MEMO";
	case FloatType:
		return "DOUBLE";
	case DateType:
		return "SMALLDATETIME";
	default:
		return "";
	}
}

_bstr_t CFields::GetSqlServerType(FieldType enumFieldType)
{
	switch(enumFieldType)
	{
	case IntType:
		return "INT";
	case CharType:
		return "VARCHAR";
	case FloatType:
		return "FLOAT";
	case DateType:
		return "DATETIME";
	default:
		return "";
	}
}

_bstr_t CFields::GetOracleType(FieldType enumFieldType)
{
	switch(enumFieldType)
	{
	case IntType:
		return "Number(10,0)";
	case CharType:
		return "VARCHAR2";
	case FloatType:
		return "REAL";
	case DateType:
		return "DATE";
	default:
		return "";
	}
}

void CFields::SetDatabaseType(DatabaseType enumType)
{
	m_enumDatabaseType = enumType;
}

void CFields::ClearListFields()
{
	if(!m_listField.empty())
		m_listField.clear();
}

void CFields::ClearMapFields()
{
	if(!m_mapFields.empty())
		m_mapFields.clear();
}