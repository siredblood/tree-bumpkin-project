#include "CityCamera.h"


CCityCamera::CCityCamera(void)
{
}

CCityCamera::~CCityCamera(void)
{
}

BOOL CCityCamera::Add()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��������ͷ"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸó�������ͷҵ���"),_T("��ʾ"),0);
		return FALSE;
	}

	_bstr_t strColumnsFormat;
	_bstr_t strValuesFormat;
	_bstr_t strSQL;
	strColumnsFormat = "";
	strValuesFormat = "";
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case OracleType:
		strColumnsFormat = " (���,����ͷ���,λ��,����,����)";
		strValuesFormat = "(��������ͷ����.NextVal,'" + m_strCameraID + "','"
			+ m_strPosition +  "','" + m_strType + "','" + m_strRemark +"')";
		break;
	case AccessType:
	case SqlServerType:
		strColumnsFormat = "(����ͷ���,λ��,����,����)";
		strValuesFormat = "('" + m_strCameraID + "','" + m_strPosition +  
			"','" + m_strType + "','" + m_strRemark + "')";
		break;
	default:
		return FALSE;
	}
	strSQL = "INSERT INTO  ��������ͷ " + strColumnsFormat + " Values " + strValuesFormat;

	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CCityCamera::Load(_bstr_t bstrID)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��������ͷ"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸó�������ͷҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	if (bstrID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ���صĳ�������ͷ��ţ�"),_T("��ʾ"),0);
		return FALSE;
	}

	BOOL bFlag;
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL;
	strSQL = "SELECT ���,����ͷ���,λ��,����,���� FROM ��������ͷ WHERE ��� = " + bstrID;
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if(pRecordSet!=NULL && !pRecordSet->adoEOF)//�����¼�����м�¼
	{
		bFlag = TRUE;
		m_strID = (_bstr_t)pRecordSet->GetCollect("���");
		m_strCameraID = (_bstr_t)pRecordSet->GetCollect("����ͷ���");
		m_strPosition = (_bstr_t)pRecordSet->GetCollect("λ��");
		m_strType = (_bstr_t)pRecordSet->GetCollect("����");
		m_strRemark = (_bstr_t)pRecordSet->GetCollect("����");

		pRecordSet->Close();
		pRecordSet.Release();
	}
	return bFlag;
}

BOOL CCityCamera::Update()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��������ͷ"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸó�������ͷҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	if (m_strID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ���µļ�¼��ţ�"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "UPDATE ��������ͷ SET ����ͷ��� = '" + m_strCameraID 
		+ "',λ�� = '" + m_strPosition + "',���� = '" + m_strType 
		+ "',���� = '" + m_strRemark + "' WHERE ��� = " 
		+ m_strID;
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CCityCamera::Delete()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��������ͷ"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸó�������ͷҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	if (m_strID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ���µļ�¼��ţ�"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "DELETE FROM ��������ͷ WHERE ��� = " + m_strID;
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CCityCamera::Delete(_bstr_t strIDS)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��������ͷ"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸó�������ͷҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	if (strIDS.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ���µļ�¼��ţ�"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "DELETE FROM ��������ͷ WHERE ��� IN (" + strIDS + ")";
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

_RecordsetPtr CCityCamera::QueryAllCamera()
{
	return QueryCameraByCondit("");
}

void CCityCamera::QueryAllCamera(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryAllCamera();
	if (Rcst==NULL)
		return;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
}

_RecordsetPtr CCityCamera::QueryCameraByCondit(_bstr_t STRWhere)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��������ͷ"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸó�������ͷҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL;
	strSQL = "SELECT  ���,����ͷ���,λ��,����,����  FROM ��������ͷ WHERE 1=1 " + STRWhere;
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	return pRecordSet;
}

void CCityCamera::QueryCameraByCondit(_bstr_t bstrWhere, vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryCameraByCondit(bstrWhere);
	if (Rcst==NULL)
		return;
	CBllHelp *help = new CBllHelp();
	help->QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
}