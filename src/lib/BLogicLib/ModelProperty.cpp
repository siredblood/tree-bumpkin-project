//#include "pch.hpp"
#include "ModelProperty.h"

CModelProperty::CModelProperty(void)
{
}

CModelProperty::~CModelProperty(void)
{
}


//////////////////////////////////////////////////////////////////////////
//检查字段名是否存在
bool CModelProperty::CheckFieldNameExist(CString strFieldName)
{
	bool havename=false;

	_RecordsetPtr prst;
	prst=theBllApp.m_pDB->ExcuteSqlRes("select *  FROM  属性 ",adCmdText);
	FieldsPtr fptr=prst->GetFields();

	CString fieldname=strFieldName.MakeLower();
	CString strTemp;
	for (long i=0;i<fptr->GetCount();i++)
	{
		strTemp=(LPSTR)fptr->GetItem(i)->GetName();

		if (strTemp.MakeLower()==fieldname)
		{
			havename=true;
			break;
		}
	}
	return havename;
}
//将文字型的字段类型转化为数据库字段类型
CString CModelProperty::GetFieldTypeByString(CString strTypeString)
{
	CString  strDBType="";
	if (strTypeString=="日期")
	{
		strDBType="DATETIME";
	} 
	else if (strTypeString=="备注")
	{
		strDBType="MEMO";
	}
	else if(strTypeString=="整型")
	{
		strDBType="LONG";
	}
	else if (strTypeString=="浮点")
	{
		strDBType="DOUBLE";
	}
	else
	{
		strDBType="VARCHAR";
	}
	return strDBType;
}


CString CModelProperty::GetChianeseTypeByDataType(adoDataTypeEnum datatype)
{
	CString strChianeseType;
	switch(datatype)
	{
	case ADODB::adInteger:
	case ADODB::adBigInt:
	case ADODB::adSmallInt:
		strChianeseType="整型";
		break;
	case ADODB::adSingle:
	case ADODB::adDouble:
	case ADODB::adCurrency :
	case ADODB::adDecimal:
	case ADODB::adNumeric:
		strChianeseType="浮点型";
		break;
	case ADODB::adDate:
	case ADODB::adDBDate:
		strChianeseType="日期型";
		break;
	case ADODB::adChar :
	case ADODB::adVarChar:
	case ADODB::adLongVarChar:
		strChianeseType="文本";
		break;
	case ADODB::adWChar :
	case ADODB::adVarWChar :
	case ADODB::adLongVarWChar :
		strChianeseType="备注";
		break;
	}
	return strChianeseType;
}
//得到表的所有字段用，隔开
_bstr_t  CModelProperty::GetFieldNames()
{
	_RecordsetPtr prst;
	prst=theBllApp.m_pDB->ExcuteSqlRes("select *  FROM  属性 ",adCmdText);
	FieldsPtr fptr=prst->GetFields();
	_bstr_t strFieldNames;
	long lFieldCounts=fptr->GetCount();

	for (long i=0;i<lFieldCounts;i++)
	{
		if (i<lFieldCounts-1)
		{
			strFieldNames+=fptr->GetItem(i)->GetName()+",";
		}
		else
		{
			strFieldNames+=fptr->GetItem(i)->GetName();
		}
	}
	return strFieldNames;
}
//////////////////////////////////////////////////////////////////////////

//加载三维模型信息
//传入参数：GUID
std::map<CString,CString> CModelProperty::LoadInfo(CString strGUID)
{
	std::map<CString,CString> info;
	if (strGUID.GetLength()!=0)
	{
		_bstr_t myguid=strGUID.GetBuffer(0);
		_RecordsetPtr  prstInfo = theBllApp.m_pDB->ExcuteSqlRes("select *  from  属性  where GUID='"+ myguid +"'",adCmdText);
		if (prstInfo==NULL && !prstInfo->adoEOF)
		{
			FieldsPtr fptr=prstInfo->GetFields();
			CString strFieldName;
			CString strFieldValue;
			for (long i=0;i<fptr->GetCount();i++)
			{
				strFieldName=(LPSTR)fptr->GetItem(i)->GetName();
				strFieldValue=(CString)prstInfo->GetCollect(strFieldName.GetBuffer(0));
				info.insert(CString_Pair(strFieldName,strFieldValue));
			}
			prstInfo->Close();
			prstInfo.Release();

		} 
	}
	return info;
}
//保存属性给三维模型
//参数：模型GUID，字段的键值
BOOL CModelProperty::SaveInfo(CString strGuid, MapFields &mapFlds)
{
	if (strGuid.GetLength()==0)
	{
		return FALSE;
	}

	_bstr_t bstrmyguid="  and GUID='"+strGuid+"'";
	CString strWhere=(LPSTR)bstrmyguid;
	_RecordsetPtr prst=QueryModelProperty(strWhere);

	_bstr_t bstrSql;

	//修改
	if (prst==NULL && !prst->adoEOF)
	{
		MapFields::iterator itr1, itr2;
		_bstr_t strUpdateFormat="";
		itr1 = mapFlds.begin();
		itr2 = --mapFlds.end();
		while(itr1 != itr2)
		{
			strUpdateFormat += (*itr1).first + "='" + (*itr1).second + "',";
			itr1++;
		}
		strUpdateFormat += (*itr1).first + "='" + (*itr1).second + "'";
		bstrSql = "UPDATE  属性  SET " + strUpdateFormat+"  WHERE GUID='"+strGuid+"'";
	}
	else /*增加*/
	{
		MapFields::iterator itr1, itr2;
		_bstr_t strColumns,strValues;
		itr1 = mapFlds.begin();
		itr2 = --mapFlds.end();
		while(itr1 != itr2)
		{
			strColumns +="[" +(*itr1).first + "],";
			strValues += "'" + (*itr1).second + "'" + ",";
			itr1++;
		}
		strColumns += (*itr1).first;
		strValues += "'" + (*itr1).second + "'";

		bstrSql = "INSERT INTO 属性  ( " +  strColumns + " ) VALUES (" + strValues + ")";
	}
	return theBllApp.m_pDB->ExcuteSql(bstrSql,adCmdText);
}
//删除三维模型属性
//传入参数：GUID
BOOL CModelProperty::Delete(CString strGuid)
{
	if (strGuid.GetLength()==0)
	{
		return FALSE;
	}
	_bstr_t myguid=strGuid.GetBuffer(0);
	return theBllApp.m_pDB->ExcuteSql("DELETE FROM 属性 WHERE GUID='"+ myguid +"'",adCmdText);
}

//查询所有三维模型属性列表
_RecordsetPtr CModelProperty::QueryModelProperty(CString strWhere)
{
	_bstr_t mywhere=strWhere.GetBuffer(0);
	return theBllApp.m_pDB->ExcuteSqlRes("select *  FROM  属性 WHERE 1=1 "+mywhere ,adCmdText);
}
//查询所有三维模型属性列表,返回绑定列表使用
void CModelProperty::QueryModelProperty(CString strWhere,std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts)
{
	CBllHelp *help = new CBllHelp();
	help->QueryByCondit(QueryModelProperty(strWhere),vecField,vecRecordSet,lFieldCounts);
}
//////////////////////////////////////////////////////////////////////////

//添加三维模型属性字段
BOOL CModelProperty::AddField(CString strFieldName, CString enumFieldType, int iFieldSize)
{
	if (CheckFieldNameExist(strFieldName))
	{
		return FALSE;
	}
	int irealsize=iFieldSize;
	if (irealsize<=0||irealsize>255)
	{
		irealsize=64;
	}

	_bstr_t strSql,strField,strType,strSize;
	strSql="";
	strField=strFieldName.GetBuffer(0);
	strType=GetFieldTypeByString(enumFieldType).GetBuffer(0);
	CString strtosize;
	strtosize.Format("%s",irealsize);
	strSize=strtosize.GetBuffer(0);

	if (enumFieldType=="文本")
	{
		strSql="ALTER TABLE 属性 ADD ［"+strField+ "] "+strType+"("+strSize+")"+"  NULL  ";
	}
	else
	{
		strSql="ALTER TABLE 属性 ADD ［"+strField+ "] "+strType+"  NULL  ";
	}
	return theBllApp.m_pDB->ExcuteSql(strSql,adCmdText);
}
//修改三维模型属性字段
BOOL CModelProperty::UpdateField(CString strOldFieldName,CString strNewFieldName,  CString enumFieldType, int iFieldSize)
{
	int irealsize=iFieldSize;
	if (irealsize<=0||irealsize>255)
	{
		irealsize=64;
	}
	_bstr_t strSql,strField,strType,strSize;
	strSql="";
	strField=strNewFieldName.GetBuffer(0);
	strType=GetFieldTypeByString(enumFieldType).GetBuffer(0);
	CString strtosize;
	strtosize.Format("%s",irealsize);
	strSize=strtosize.GetBuffer(0);

	if (strOldFieldName==strNewFieldName)
	{
		if (enumFieldType=="文本")
		{
			strSql="ALTER TABLE 属性  ALTER ［"+strField+ "] "+strType+"("+strSize+")"+"  NULL  ";
		}
		else
		{
			strSql="ALTER TABLE 属性  ALTER ［"+strField+ "] "+strType+"  NULL  ";
		}
	}
	else
	{
		return FALSE;
		/*if (CheckFieldNameExist(strNewFieldName))
		{
			return FALSE;
		}*/
		//改字段名语句写在这里
	}
	return theBllApp.m_pDB->ExcuteSql(strSql,adCmdText);
}
//删除三维模型属性字段
BOOL CModelProperty::DeleteField(CString strFieldName)
{
	if (strFieldName=="GUID"||strFieldName=="名称")
	{
		return FALSE;
	}
	_bstr_t strfield=strFieldName.GetBuffer(0);
	_bstr_t strSql="ALTER TABLE 属性 DROP COLUMN  "+strfield;
	return theBllApp.m_pDB->ExcuteSql(strSql,adCmdText);
}
//查询三维模型属性表所有字段列表
FieldsPtr  CModelProperty::QueryPropertyFields()
{
	_RecordsetPtr prst;
	prst=theBllApp.m_pDB->ExcuteSqlRes("select *  FROM  属性 ",adCmdText);
	FieldsPtr fpts=prst->GetFields();
	return fpts;
}
//查询所有三维模型属性列表,返回绑定列表使用
void CModelProperty::QueryPropertyFields(std::vector<CString> &vecField, std::vector<CString> &vecRecordSet, long &lFieldCounts)
{
	//lFieldCounts
	lFieldCounts=3;

	//vecField
	vecField.push_back("字段名称");
	vecField.push_back("文本");
	vecField.push_back("255");

	vecField.push_back("字段类型");
	vecField.push_back("文本");
	vecField.push_back("255");

	vecField.push_back("字段大小");
	vecField.push_back("整型");
	vecField.push_back("");

	//vecRecordSet
	_RecordsetPtr prst;
	prst=theBllApp.m_pDB->ExcuteSqlRes("select *  FROM  属性 ",adCmdText);
	FieldsPtr fptr=prst->GetFields();
	long lFieldSize;
	CString strFileSize;
	
	for (long i=0;i<fptr->GetCount();i++)
	{
		vecRecordSet.push_back((LPSTR)fptr->GetItem(i)->GetName());
		vecRecordSet.push_back(GetChianeseTypeByDataType(fptr->GetItem(i)->GetType()));
		lFieldSize = fptr->GetItem(i)->GetDefinedSize();
		strFileSize.Format("%ld", lFieldSize);
		vecRecordSet.push_back( strFileSize );
	}
}
