#include "pch.hpp"
#include "SectorizationDatabase.h"
#include "DataBaseLib/DBHelper.h"
#include "GeneralClass/Common.h"

SectorizationDatabase::SectorizationDatabase()
{

}

SectorizationDatabase::~SectorizationDatabase()
{

}

void SectorizationDatabase::loadSectorization( std::vector<SECTORIZATIONDATA>& vData )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("���ܷ���"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڹ��ܷ���ҵ���"),_T("��ʾ"),0);
		return;
	}

	SECTORIZATIONDATA data;

	_RecordsetPtr pRecordSet;
	_bstr_t strSQL="SELECT * FROM ���ܷ���";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if (pRecordSet!=NULL)
	{
		while(!pRecordSet->adoEOF)
		{
			CString strName = (LPCSTR)(_bstr_t)pRecordSet->GetCollect("����");
			CString strPos = (LPCSTR)(_bstr_t)pRecordSet->GetCollect("�ӽ�λ��");
			CString strDir = (LPCSTR)(_bstr_t)pRecordSet->GetCollect("�ӽǷ���");
			Vector3 pos = ConvertStrToVec3( strPos.GetBuffer(0) );
			Vector3 dir = ConvertStrToVec3( strDir.GetBuffer(0) );
			data.strName = strName;
			data.viewpos = pos;
			data.viewdir = dir;
			data.vGuids.clear();
			_bstr_t strSubSql = "SELECT * FROM ���ܷ������� WHERE ��������='" + strName + "'";
			_RecordsetPtr pSubRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSubSql,adCmdText);
			if(pSubRecordSet!=NULL)
			{
				while(!pSubRecordSet->adoEOF)
				{
					CString strGUID = (LPCSTR)(_bstr_t)pSubRecordSet->GetCollect("����");
					data.vGuids.push_back(strGUID);
					pSubRecordSet->MoveNext();
				}
				pSubRecordSet->Close();
				pSubRecordSet.Release();
			}
			vData.push_back(data);

			pRecordSet->MoveNext();
		}
		pRecordSet->Close();
		pRecordSet.Release();
	}
	

}

BOOL SectorizationDatabase::addSectorization( CString strName, Vector3 viewpos, Vector3 viewdir )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("���ܷ���"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڹ��ܷ���ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	CString strpos = ConvertVec3ToStr(viewpos);
	CString strdir = ConvertVec3ToStr(viewdir);

	_bstr_t strSQL;
	strSQL = "INSERT INTO ���ܷ���(����,�ӽ�λ��,�ӽǷ���) values('" + strName +"','" + strpos
		+"','" + strdir + "')";

	//INFO_MSG(strSQL);
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL SectorizationDatabase::editSectorization( CString strName, Vector3 viewpos, Vector3 viewdir )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("���ܷ���"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڹ��ܷ���ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	CString strpos = ConvertVec3ToStr(viewpos);
	CString strdir = ConvertVec3ToStr(viewdir);
	
	_bstr_t strSQL;
	strSQL = "UPDATE ���ܷ��� SET �ӽ�λ�� ='" + strpos + "', �ӽǷ���='" + strdir + "' WHERE ����='" + strName + "'";
	//INFO_MSG(strSQL);

	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL SectorizationDatabase::addSectorizationObject( CString strName, CString strGuid )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("���ܷ�������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڹ��ܷ�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "INSERT INTO ���ܷ�������(��������,����) values('" + strName +"','" + strGuid + "')";

	//INFO_MSG(strSQL);
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL SectorizationDatabase::deleteSectorization( CString strName )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("���ܷ���"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڹ��ܷ�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "DELETE FROM ���ܷ��� WHERE ����='" + strName + "'";
	theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);

	strSQL = "DELETE FROM ���ܷ������� WHERE ��������='" + strName + "'";

	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL SectorizationDatabase::deleteSectorizationObject( CString strName, CString strGuid )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("���ܷ�������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڹ��ܷ�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "DELETE FROM ���ܷ������� WHERE ��������='" + strName + "' AND ����='" + strGuid + "'";
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}