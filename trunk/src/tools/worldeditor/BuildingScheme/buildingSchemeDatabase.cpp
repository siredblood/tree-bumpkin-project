#include "pch.hpp"
#include "buildingSchemeDatabase.h"
#include "DataBaseLib/DBHelper.h"

BuildingSchemeDatabase::BuildingSchemeDatabase()
{

}

BuildingSchemeDatabase::~BuildingSchemeDatabase()
{

}

void BuildingSchemeDatabase::loadScheme( std::map<CString, std::map<CString, CString>> &vScheme )
{
	INFO_MSG("loadScheme\n");
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�����滻����"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڽ����滻����ҵ���"),_T("��ʾ"),0);
		return;
	}

	_RecordsetPtr pRecordSet;
	_bstr_t strSQL="SELECT * FROM �����滻����";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if (pRecordSet!=NULL)
	{
		while(!pRecordSet->adoEOF)
		{
			CString strName = (LPCSTR)(_bstr_t)pRecordSet->GetCollect("��������");
			CString strBeReplace = (LPCSTR)(_bstr_t)pRecordSet->GetCollect("ԭģ��");
			CString strNewModel = (LPCSTR)(_bstr_t)pRecordSet->GetCollect("�滻ģ��");

			//INFO_MSG("%s,%s,%s\n", strName,strBeReplace,strNewModel);
			std::map<CString, std::map<CString, CString>>::iterator itr = vScheme.find(strName);
			if(itr==vScheme.end())
			{
				//INFO_MSG("������\n");
				std::map<CString, CString> list;
				list.insert( std::pair<CString, CString>(strBeReplace, strNewModel) );
				vScheme.insert( std::pair<CString, std::map<CString, CString>>(strName, list) );
			}
			else
			{
				itr->second.insert( std::pair<CString, CString>(strBeReplace, strNewModel) );
			}
			pRecordSet->MoveNext();
		}
		pRecordSet->Close();
		pRecordSet.Release();
	}
}

BOOL BuildingSchemeDatabase::addScheme( CString strScheme, CString strBeReplacedModel, CString strNewModel )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�����滻����"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڽ����滻����ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "INSERT INTO �����滻����(��������,ԭģ��,�滻ģ��) values('" + strScheme +"','" + strBeReplacedModel
		+"','" + strNewModel + "')";
	
	//INFO_MSG(strSQL);
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL BuildingSchemeDatabase::deleteScheme( CString strScheme )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�����滻����"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڽ����滻����ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "DELETE FROM �����滻���� WHERE ��������='" + strScheme + "'";
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL BuildingSchemeDatabase::deleteScheme( CString strScheme, CString strBeReplacedModel )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�����滻����"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڽ����滻����ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "DELETE FROM �����滻���� WHERE ��������='" + strScheme + "' and ԭģ��='" + strBeReplacedModel + "'";
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}
