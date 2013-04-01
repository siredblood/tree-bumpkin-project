#include "EmphasesTarget.h"

CEmphasesTarget CEmphasesTarget::instance;

CEmphasesTarget::CEmphasesTarget(void)
{
}

CEmphasesTarget::~CEmphasesTarget(void)
{
}

CEmphasesTarget & CEmphasesTarget::Instance()
{
	return instance;
}
BOOL CEmphasesTarget::Add()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�ص�Ŀ��"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ��ص�Ŀ��ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strColumnsFormat= "", strValuesFormat= "", strSQL="";
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case OracleType:
		strColumnsFormat = " (���,����,����,��������,��ַ,����,����)";
		strValuesFormat = "(�ص�Ŀ������.NextVal,'" + m_strName + "','"
			+ m_strType +  "','" + m_strArea + "','"+m_strAddress+"','" + m_strCoordinate
			+  "','" + m_strRemark + "')";
		break;
	case AccessType:
	case SqlServerType:
		strColumnsFormat = "(����,����,��������,��ַ,����,����)";
		strValuesFormat = "('" + m_strName + "','" + m_strType +  "','" 
			+ m_strArea +"','"+m_strAddress+"','" + m_strCoordinate +  "','" + m_strRemark + "')";
		break;
	default:
		break;
	}
	strSQL = "INSERT INTO  �ص�Ŀ�� "+strColumnsFormat+"  Values " + strValuesFormat;
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CEmphasesTarget::Load(_bstr_t bstrID)
{
	if (bstrID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ�����ص�Ŀ���ţ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�ص�Ŀ��"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ��ص�Ŀ��ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	BOOL bFlag=FALSE;
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL;
	strSQL = "SELECT ���,����,����,��������,��ַ,����,���� FROM �ص�Ŀ�� WHERE ��� = " + bstrID;
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if (pRecordSet!=NULL)
	{
		if (!pRecordSet->adoEOF)
		{
			m_strID = bstrID;
			_variant_t var;
			var=pRecordSet->GetCollect("����");
			m_strName = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("����");
			m_strType = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("��������");
			m_strArea = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("��ַ");
			m_strAddress = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("����");
			m_strCoordinate = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("����");
			m_strRemark = (_bstr_t)(var.vt==1?"":var);
			bFlag=TRUE;
		}
		pRecordSet->Close();
		pRecordSet.Release();
	}
	return bFlag;
}

BOOL CEmphasesTarget::LoadByName(_bstr_t bstrName)
{
	if (bstrName.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ�����ص�Ŀ�����ƣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�ص�Ŀ��"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ��ص�Ŀ��ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	BOOL bFlag=FALSE;
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL;
	strSQL = "SELECT ���,����,����,��������,��ַ,����,���� FROM �ص�Ŀ�� WHERE ���� = '" + bstrName+"'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if (pRecordSet!=NULL)
	{
		if (!pRecordSet->adoEOF)
		{
			_variant_t var;
			var=pRecordSet->GetCollect("���");
			m_strID = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("����");
			m_strName = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("����");
			m_strType = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("��������");
			m_strArea = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("��ַ");
			m_strAddress = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("����");
			m_strCoordinate = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("����");
			m_strRemark = (_bstr_t)(var.vt==1?"":var);
			bFlag=TRUE;
		}
		pRecordSet->Close();
		pRecordSet.Release();
	}
	return bFlag;
}
//����ص�Ŀ�������Ƿ����
BOOL CEmphasesTarget::CheckNameExist(_bstr_t bstrName)
{
	if (bstrName.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ�����ص�Ŀ�����ƣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�ص�Ŀ��"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ��ص�Ŀ��ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL;
	strSQL = "SELECT ���,����,����,��������,��ַ,����,���� FROM �ص�Ŀ�� WHERE ���� = '" + bstrName+"'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if (pRecordSet==NULL)
		return FALSE;
	if (pRecordSet!=NULL && !pRecordSet->adoEOF)
		return TRUE;
	pRecordSet->Close();
	pRecordSet.Release();
	return FALSE;
}
//����ص�Ŀ�����Ƹ���
BOOL CEmphasesTarget::NameValidate(_bstr_t bstrName,_bstr_t bstrID)
{
	if (bstrName.length()<=0 || bstrID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ�����ص�Ŀ�꣡"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�ص�Ŀ��"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ��ص�Ŀ��ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL;
	strSQL = "SELECT ���,����,����,��������,��ַ,����,���� FROM �ص�Ŀ�� WHERE ���<>"+bstrID+" and  ���� = '" + bstrName+"'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if (pRecordSet!=NULL && !pRecordSet->adoEOF)
		return FALSE;
	pRecordSet->Close();
	pRecordSet.Release();
	return TRUE;
}
BOOL CEmphasesTarget::Update()
{
	if (m_strID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ������ص�Ŀ���ţ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�ص�Ŀ��"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ��ص�Ŀ��ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "UPDATE �ص�Ŀ�� SET ���� = '" + m_strName + "',���� = '"
		+ m_strType + "',��ַ='"+ m_strAddress +"',�������� = '" + m_strArea + "',���� = '"
		+ m_strCoordinate + "',���� = '" + m_strRemark + 
		"' WHERE ��� = " + m_strID;
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CEmphasesTarget::Delete()
{
	if (m_strID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫɾ���ص�Ŀ�꣡"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�ص�Ŀ��"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ��ص�Ŀ��ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "DELETE FROM �ص�Ŀ�� WHERE ��� = " + m_strID;
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}
//������ʵ��ɾ��
BOOL CEmphasesTarget::DeleteByName(_bstr_t strName)
{
	if (strName.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫɾ���ص�Ŀ�꣡"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�ص�Ŀ��"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ��ص�Ŀ��ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "DELETE FROM �ص�Ŀ�� WHERE strName = '" + strName+"'";
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CEmphasesTarget::Delete(_bstr_t strIDS)
{
	if (strIDS.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫɾ���ص�Ŀ�꣡"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�ص�Ŀ��"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ��ص�Ŀ��ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "DELETE FROM �ص�Ŀ�� WHERE ��� IN (" + strIDS + ")";
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

_RecordsetPtr CEmphasesTarget::QueryAllEmphTarg()
{
	return QueryEmphTargByCondit("");
}
std::vector<TARGETMODEL> CEmphasesTarget::QueryAllTarget()
{
	std::vector<TARGETMODEL> vModels;
	TARGETMODEL model;
	_RecordsetPtr pRecordSet=QueryEmphTargByCondit("");
	if (pRecordSet==NULL)
		return vModels;
	if (pRecordSet!=NULL && !pRecordSet->adoEOF)
	{
		_variant_t var;
		while(!pRecordSet->adoEOF)
		{
			var=pRecordSet->GetCollect("���");
			model.m_strID =(char *)((_bstr_t)(var.vt==1?"":var)) ;
			var=pRecordSet->GetCollect("����");
			model.m_strName = (char *)((_bstr_t)(var.vt==1?"":var)) ;
			var=pRecordSet->GetCollect("����");
			model.m_strType = (char *)((_bstr_t)(var.vt==1?"":var)) ;
			var=pRecordSet->GetCollect("��������");
			model.m_strArea = (char *)((_bstr_t)(var.vt==1?"":var)) ;
			var=pRecordSet->GetCollect("��ַ");
			model.m_strAddress =(char *)((_bstr_t)(var.vt==1?"":var)) ;
			var=pRecordSet->GetCollect("����");
			model.m_strCoordinate = (char *)((_bstr_t)(var.vt==1?"":var)) ;
			var=pRecordSet->GetCollect("����");
			model.m_strRemark = (char *)((_bstr_t)(var.vt==1?"":var)) ;
			vModels.push_back(model);
			pRecordSet->MoveNext();
		}
	}
	pRecordSet->Close();
	pRecordSet.Release();
	return vModels;
}
vector<string> CEmphasesTarget::GetAllTargetName()
{
	vector<string> v;
	string strTemp;
	_RecordsetPtr Rcst=QueryAllEmphTarg();
	if (Rcst==NULL)
		return v;
	if (Rcst!=NULL&&!Rcst->adoEOF)
	{
		while(!Rcst->adoEOF)
		{
			strTemp= (char *)((_bstr_t)Rcst->GetCollect("����"));
			v.push_back(strTemp);
			Rcst->MoveNext();
		}
	}
	Rcst->Close();
	Rcst.Release();
	return v;
}
//����
std::vector<string> CEmphasesTarget::GetAreas()
{
	std::vector<string> v;
	string strTemp;
	_RecordsetPtr Rcst=theBllApp.m_pDB->ExcuteSqlRes("select distinct �������� from �ص�Ŀ��",adCmdText);
	if (Rcst==NULL)
		return v;
	if (!Rcst->adoEOF)
	{
		_variant_t var;
		while(!Rcst->adoEOF)
		{
			var=Rcst->GetCollect("��������");
			strTemp = (char *)((_bstr_t)(var.vt==1?"":var));
			v.push_back(strTemp);
			Rcst->MoveNext();
		}
	}
	Rcst->Close();
	Rcst.Release();
	return v;
}
//�����ص�Ŀ��
std::vector<string> CEmphasesTarget::GetTargetByArea(string strArea)
{
	std::vector<string> v;
	string strTemp;
	strTemp="select distinct ���� from �ص�Ŀ��  where ��������='"+strArea+"'";
	_RecordsetPtr Rcst=theBllApp.m_pDB->ExcuteSqlRes(strTemp.c_str(),adCmdText);
	if (Rcst==NULL)
		return v;
	if (!Rcst->adoEOF)
	{
		_variant_t var;
		while(!Rcst->adoEOF)
		{
			var=Rcst->GetCollect("����");
			strTemp = (char *)((_bstr_t)(var.vt==1?"":var));
			v.push_back(strTemp);
			Rcst->MoveNext();
		}
	}
	Rcst->Close();
	Rcst.Release();
	return v;
}

void CEmphasesTarget::QueryAllEmphTarg(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryAllEmphTarg();
	if (Rcst==NULL)
		return;
	CBllHelp::Instance().QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
}

_RecordsetPtr CEmphasesTarget::QueryEmphTargByCondit(_bstr_t STRWhere)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�ص�Ŀ��"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ��ص�Ŀ��ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "SELECT ���,����,����,��������,��ַ,����,���� FROM �ص�Ŀ�� WHERE 1=1 " + STRWhere;
	return theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
}

void CEmphasesTarget::QueryEmphTargByCondit(_bstr_t bstrWhere, vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryEmphTargByCondit(bstrWhere);
	if(Rcst==NULL)
		return ;
	CBllHelp::Instance().QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
}