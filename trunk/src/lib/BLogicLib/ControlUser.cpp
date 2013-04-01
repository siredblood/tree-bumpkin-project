#include "ControlUser.h"

CControlUser::CControlUser(void)
{
}

CControlUser::~CControlUser(void)
{
}


BOOL CControlUser::Add()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("����û�"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸü���û�ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strColumnsFormat = "", strValuesFormat= "" , strSQL;
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case OracleType:
		strColumnsFormat = " (���,������,�û���,����)";
		strValuesFormat = "(����û�����.NextVal,'" + m_strServer + "','"+ m_strUserName +  "','" + m_strPassWord + "')";
		break;
	case AccessType:
	case SqlServerType:
		strColumnsFormat = "(������,�û���,����)";
		strValuesFormat = "('" + m_strServer + "','" + m_strUserName +  "','" + m_strPassWord + "')";
		break;
	default:
		return FALSE;
	}
	strSQL = "INSERT INTO ����û� " + strColumnsFormat + " Values " + strValuesFormat;
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CControlUser::Load(_bstr_t bstrID)
{
	if (bstrID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ���ؼ���û���ţ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("����û�"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸü���û�ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	BOOL bFlag=FALSE;
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL;
	strSQL = "SELECT ���,������,�û���,���� FROM ����û� WHERE ��� = " + bstrID;
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);

	if(pRecordSet!=NULL)//�����¼�����м�¼
	{
		if (!pRecordSet->adoEOF)
		{
			bFlag = TRUE;
			_variant_t var;
			m_strID = bstrID;
			var=pRecordSet->GetCollect("������");
			m_strServer = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("�û���");
			m_strUserName = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("����");
			m_strPassWord = (_bstr_t)(var.vt==1?"":var);
		}
		pRecordSet->Close();
		pRecordSet.Release();
	}
	return bFlag;
}


BOOL CControlUser::Update()
{
	if (m_strID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ���¼���û���"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("����û�"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸü���û�ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}

	_bstr_t strSQL;
	strSQL = "UPDATE ����û� SET ������ = '" + m_strServer + "',�û��� = '"
		+ m_strUserName + "',���� = '" + m_strPassWord+ "' WHERE ��� = " 
		+ m_strID;
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CControlUser::Delete()
{
	if (m_strID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫɾ������û���ţ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("����û�"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸü���û�ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "DELETE FROM ����û� WHERE ��� = " + m_strID;
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CControlUser::Delete(_bstr_t strIDS)
{
	if (strIDS.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫɾ������û���ţ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("����û�"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸü���û�ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "DELETE FROM ����û� WHERE ��� IN (" + strIDS + ")";
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

_RecordsetPtr CControlUser::QueryAllUser()
{
	return QueryUserByCondit("");
}
vector<string> CControlUser::GetAllUserName()
{
	vector<string> v;
	string strTemp;
	_RecordsetPtr Rcst=QueryAllUser();
	if (Rcst!=NULL&&!Rcst->adoEOF)
	{
		while(!Rcst->adoEOF)
		{
			strTemp=(char *)((_bstr_t)Rcst->GetCollect("�û���"));
			v.push_back(strTemp);
			Rcst->MoveNext();
		}
	}
	return v;
}

void CControlUser::QueryAllUser(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryAllUser();
	if ( Rcst == NULL)
		return;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
}

_RecordsetPtr CControlUser::QueryUserByCondit(_bstr_t STRWhere)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("����û�"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸü���û�ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL = "SELECT ���,������,�û���,����  FROM ����û� WHERE 1=1 " + STRWhere;
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	return pRecordSet;
}

void CControlUser::QueryUserByCondit(_bstr_t bstrWhere,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryUserByCondit(bstrWhere);
	if (Rcst == NULL)
		return;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
}