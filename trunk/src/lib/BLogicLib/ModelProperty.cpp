//#include "pch.hpp"
#include "ModelProperty.h"

CModelProperty::CModelProperty(void)
{
}

CModelProperty::~CModelProperty(void)
{
}


//////////////////////////////////////////////////////////////////////////
//����ֶ����Ƿ����
bool CModelProperty::CheckFieldNameExist(CString strFieldName)
{
	bool havename=false;

	_RecordsetPtr prst;
	prst=theBllApp.m_pDB->ExcuteSqlRes("select *  FROM  ���� ",adCmdText);
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
//�������͵��ֶ�����ת��Ϊ���ݿ��ֶ�����
CString CModelProperty::GetFieldTypeByString(CString strTypeString)
{
	CString  strDBType="";
	if (strTypeString=="����")
	{
		strDBType="DATETIME";
	} 
	else if (strTypeString=="��ע")
	{
		strDBType="MEMO";
	}
	else if(strTypeString=="����")
	{
		strDBType="LONG";
	}
	else if (strTypeString=="����")
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
		strChianeseType="����";
		break;
	case ADODB::adSingle:
	case ADODB::adDouble:
	case ADODB::adCurrency :
	case ADODB::adDecimal:
	case ADODB::adNumeric:
		strChianeseType="������";
		break;
	case ADODB::adDate:
	case ADODB::adDBDate:
		strChianeseType="������";
		break;
	case ADODB::adChar :
	case ADODB::adVarChar:
	case ADODB::adLongVarChar:
		strChianeseType="�ı�";
		break;
	case ADODB::adWChar :
	case ADODB::adVarWChar :
	case ADODB::adLongVarWChar :
		strChianeseType="��ע";
		break;
	}
	return strChianeseType;
}
//�õ���������ֶ��ã�����
_bstr_t  CModelProperty::GetFieldNames()
{
	_RecordsetPtr prst;
	prst=theBllApp.m_pDB->ExcuteSqlRes("select *  FROM  ���� ",adCmdText);
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

//������άģ����Ϣ
//���������GUID
std::map<CString,CString> CModelProperty::LoadInfo(CString strGUID)
{
	std::map<CString,CString> info;
	if (strGUID.GetLength()!=0)
	{
		_bstr_t myguid=strGUID.GetBuffer(0);
		_RecordsetPtr  prstInfo = theBllApp.m_pDB->ExcuteSqlRes("select *  from  ����  where GUID='"+ myguid +"'",adCmdText);
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
//�������Ը���άģ��
//������ģ��GUID���ֶεļ�ֵ
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

	//�޸�
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
		bstrSql = "UPDATE  ����  SET " + strUpdateFormat+"  WHERE GUID='"+strGuid+"'";
	}
	else /*����*/
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

		bstrSql = "INSERT INTO ����  ( " +  strColumns + " ) VALUES (" + strValues + ")";
	}
	return theBllApp.m_pDB->ExcuteSql(bstrSql,adCmdText);
}
//ɾ����άģ������
//���������GUID
BOOL CModelProperty::Delete(CString strGuid)
{
	if (strGuid.GetLength()==0)
	{
		return FALSE;
	}
	_bstr_t myguid=strGuid.GetBuffer(0);
	return theBllApp.m_pDB->ExcuteSql("DELETE FROM ���� WHERE GUID='"+ myguid +"'",adCmdText);
}

//��ѯ������άģ�������б�
_RecordsetPtr CModelProperty::QueryModelProperty(CString strWhere)
{
	_bstr_t mywhere=strWhere.GetBuffer(0);
	return theBllApp.m_pDB->ExcuteSqlRes("select *  FROM  ���� WHERE 1=1 "+mywhere ,adCmdText);
}
//��ѯ������άģ�������б�,���ذ��б�ʹ��
void CModelProperty::QueryModelProperty(CString strWhere,std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts)
{
	CBllHelp *help = new CBllHelp();
	help->QueryByCondit(QueryModelProperty(strWhere),vecField,vecRecordSet,lFieldCounts);
}
//////////////////////////////////////////////////////////////////////////

//�����άģ�������ֶ�
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

	if (enumFieldType=="�ı�")
	{
		strSql="ALTER TABLE ���� ADD ��"+strField+ "] "+strType+"("+strSize+")"+"  NULL  ";
	}
	else
	{
		strSql="ALTER TABLE ���� ADD ��"+strField+ "] "+strType+"  NULL  ";
	}
	return theBllApp.m_pDB->ExcuteSql(strSql,adCmdText);
}
//�޸���άģ�������ֶ�
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
		if (enumFieldType=="�ı�")
		{
			strSql="ALTER TABLE ����  ALTER ��"+strField+ "] "+strType+"("+strSize+")"+"  NULL  ";
		}
		else
		{
			strSql="ALTER TABLE ����  ALTER ��"+strField+ "] "+strType+"  NULL  ";
		}
	}
	else
	{
		return FALSE;
		/*if (CheckFieldNameExist(strNewFieldName))
		{
			return FALSE;
		}*/
		//���ֶ������д������
	}
	return theBllApp.m_pDB->ExcuteSql(strSql,adCmdText);
}
//ɾ����άģ�������ֶ�
BOOL CModelProperty::DeleteField(CString strFieldName)
{
	if (strFieldName=="GUID"||strFieldName=="����")
	{
		return FALSE;
	}
	_bstr_t strfield=strFieldName.GetBuffer(0);
	_bstr_t strSql="ALTER TABLE ���� DROP COLUMN  "+strfield;
	return theBllApp.m_pDB->ExcuteSql(strSql,adCmdText);
}
//��ѯ��άģ�����Ա������ֶ��б�
FieldsPtr  CModelProperty::QueryPropertyFields()
{
	_RecordsetPtr prst;
	prst=theBllApp.m_pDB->ExcuteSqlRes("select *  FROM  ���� ",adCmdText);
	FieldsPtr fpts=prst->GetFields();
	return fpts;
}
//��ѯ������άģ�������б�,���ذ��б�ʹ��
void CModelProperty::QueryPropertyFields(std::vector<CString> &vecField, std::vector<CString> &vecRecordSet, long &lFieldCounts)
{
	//lFieldCounts
	lFieldCounts=3;

	//vecField
	vecField.push_back("�ֶ�����");
	vecField.push_back("�ı�");
	vecField.push_back("255");

	vecField.push_back("�ֶ�����");
	vecField.push_back("�ı�");
	vecField.push_back("255");

	vecField.push_back("�ֶδ�С");
	vecField.push_back("����");
	vecField.push_back("");

	//vecRecordSet
	_RecordsetPtr prst;
	prst=theBllApp.m_pDB->ExcuteSqlRes("select *  FROM  ���� ",adCmdText);
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
