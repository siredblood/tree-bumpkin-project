#include "Duty.h"

CDuty::CDuty(void)
{
	m_strAdress = "";
	m_strDate = "";
	m_strID = "";
	m_strPliceID = "";
	m_strTime = "";
	m_strAudit="";
	m_strRemark = "";
}

CDuty::~CDuty(void)
{
}


BOOL CDuty::Add()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("ִ�ڱ�"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�ִ�ڱ�ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strColumnsFormat= "", strValuesFormat= "", strSQL= "";
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case OracleType:
		strColumnsFormat = " (���,����ID,ִ�ڵص�,ִ������,ִ�ڰ��,������,��ע)";
		strValuesFormat = "(ִ�ڱ�����.NextVal,'" + m_strPliceID + "','"
			+ m_strAdress + "'," + "to_date('" + m_strDate + "','dd/mm/yyyy'),'"
			+ m_strTime + "','"+m_strAudit+"','" + m_strRemark + "')";
		break;
	case AccessType:
	case SqlServerType:
		strColumnsFormat = "(����ID,ִ�ڵص�,ִ������,ִ�ڰ��,������,��ע)";
		strValuesFormat = "('" + m_strPliceID + "','"+ m_strAdress 
			+ "','" + m_strDate + "','" + m_strTime + "','"+m_strAudit+"','" + m_strRemark + "')";
		break;
	default:
		return FALSE;
	}
	strSQL = "INSERT INTO ִ�ڱ� " + strColumnsFormat + " Values " + strValuesFormat;
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CDuty::Load(_bstr_t bstrID)
{
	if (bstrID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ���ص�ִ�ڱ�ţ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("ִ�ڱ�"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�ִ�ڱ�ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	BOOL bFlag=FALSE;
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL = "SELECT ���,����ID,ִ�ڵص�,ִ������,ִ�ڰ��,������,��ע FROM ִ�ڱ� WHERE ��� = " + bstrID;
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if (pRecordSet!=NULL)
	{
		if(!pRecordSet->adoEOF)//�����¼�����м�¼
		{
			bFlag = TRUE;
			_variant_t var;
			m_strID = bstrID;
			var=pRecordSet->GetCollect("����ID");
			m_strPliceID = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("ִ�ڵص�");
			m_strAdress = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("ִ������");
			m_strDate = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("ִ�ڰ��");
			m_strTime = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("������");
			m_strAudit = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("��ע");
			m_strRemark = (_bstr_t)(var.vt==1?"":var);
		}
		pRecordSet->Close();
		pRecordSet.Release();
	}
	return bFlag;
}

BOOL CDuty::Update()
{
	if (m_strID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ���¼�¼��"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("ִ�ڱ�"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�ִ�ڱ�ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}

	_bstr_t strSQL;
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case OracleType:
		strSQL = "UPDATE ִ�ڱ� SET ����ID = '" + m_strPliceID + "',ִ�ڵص� = '"
			+ m_strAdress + "',ִ������ = " + "to_date('" + m_strDate 
			+ "','yyyy/mm/dd')" + ",ִ�ڰ�� = '" + m_strTime + "',������='"+m_strAudit+"',��ע = '" 
			+ m_strRemark + "' WHERE ��� = " + m_strID;
		break;
	case AccessType:
	case SqlServerType:
		strSQL = "UPDATE ִ�ڱ� SET ����ID = '" + m_strPliceID + "',ִ�ڵص� = '"
			+ m_strAdress + "',ִ������ = '" + m_strDate + "',ִ�ڰ�� = '" 
			+ m_strTime + "',������='"+m_strAudit+"',��ע = '" 	+ m_strRemark + "' WHERE ��� = " 
			+ m_strID;
		break;
	default:
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CDuty::Delete()
{
	if (m_strID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫɾ���ļ�¼��"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("ִ�ڱ�"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�ִ�ڱ�ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "DELETE FROM ִ�ڱ� WHERE ��� = " + m_strID;
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CDuty::Delete(_bstr_t strIDS)
{
	if (strIDS.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫɾ���ļ�¼��"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("ִ�ڱ�"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�ִ�ڱ�ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}

	_bstr_t strSQL;
	strSQL = "DELETE FROM ִ�ڱ� WHERE ��� IN (" + strIDS + ")";
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

_RecordsetPtr CDuty::QueryAllDuty()
{
	return QueryDutyByCondit("");
}

void CDuty::QueryAllDuty(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryAllDuty();
	if (Rcst==NULL)
		return ;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit( Rcst,vecField,vecRecordSet,lFieldCounts);
}

_RecordsetPtr CDuty::QueryDutyByCondit(_bstr_t STRWhere)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("ִ�ڱ�"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�ִ�ڱ�ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "SELECT  ���,����ID,ִ�ڵص�,ִ������,ִ�ڰ��,������,��ע  FROM ִ�ڱ� WHERE 1=1 " + STRWhere;
	return theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
}

void CDuty::QueryDutyByCondit(_bstr_t bstrWhere,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryDutyByCondit(bstrWhere);
	if (Rcst==NULL)
		return;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
}
//��ѯ��¼
_RecordsetPtr CDuty::QueryDutyRcst(_bstr_t strBeginDate,_bstr_t strEndDate,_bstr_t strdutyTimes,_bstr_t strAddress)
{
	_bstr_t strSqlwhere=GetWhereSql(strBeginDate,strEndDate,strdutyTimes,strAddress);
	return QueryDutyByCondit( strSqlwhere );
}
//����GUID��ȡ
_RecordsetPtr CDuty::QueryRCSTPolCtlGUID(_bstr_t strBeginDate,_bstr_t strEndDate,_bstr_t strdutyTimes,_bstr_t strAddress)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("ִ�ڱ�"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�ִ�ڱ�ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL="select ����ID  from  ִ�ڱ�   where 1=1 ";
	strSQL+=GetWhereSql(strBeginDate,strEndDate,strdutyTimes,strAddress);
	strSQL+="  GROUP BY  ����ID";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	return pRecordSet;
}

//��������ؼ�GUID
vector<string> CDuty::QueryVectorPolCtlGUID(_bstr_t strBeginDate,_bstr_t strEndDate,_bstr_t strdutyTimes,_bstr_t strAddress)
{
	vector<string> polctlGUID;
	_RecordsetPtr rst=QueryRCSTPolCtlGUID(strBeginDate,strEndDate,strdutyTimes,strAddress);
	if (rst!=NULL)
	{
		string polid;
		while(!rst->adoEOF)
		{
			polid=(char *)((_bstr_t)rst->GetCollect("����ID"));
			polctlGUID.push_back(polid);
			rst->MoveNext();
		}
		rst->Close();
		rst.Release();
	}
	return polctlGUID;
}
//ͳ�ƾ���
long CDuty::SumDutyPol(_bstr_t strBeginDate,_bstr_t strEndDate,_bstr_t strdutyTimes,_bstr_t strAddress)
{
	long lRst=0;
	_RecordsetPtr Rst=QueryRCSTPolCtlGUID(strBeginDate,strEndDate,strdutyTimes,strAddress);
	if (Rst!=NULL)
		lRst=Rst->GetRecordCount();
	return lRst;
}
//ͳ�Ƽ�¼��
long CDuty::SumDutyRecords(_bstr_t strBeginDate,_bstr_t strEndDate,_bstr_t strdutyTimes,_bstr_t strAddress)
{
	long lRst=0;
	_RecordsetPtr Rst=QueryDutyRcst(strBeginDate,strEndDate,strdutyTimes,strAddress);
	if (Rst!=NULL)
		lRst=Rst->GetRecordCount();
	return lRst;
}
_bstr_t CDuty::GetWhereSql(_bstr_t strBeginDate,_bstr_t strEndDate,_bstr_t strdutyTimes,_bstr_t strAddress)
{
	_bstr_t strSQL="";
	if (strdutyTimes.length()>0)
	{
		strSQL+="  and  ִ�ڰ��='"+strdutyTimes+"'";
	}
	if (strAddress.length()>0)
	{
		strSQL+="  and  ִ�ڵص� like '%" + strAddress + "%'";
	}
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case AccessType:
		if (strBeginDate.length()>0 && strEndDate.length()>0)
		{
			strSQL+="  and ִ������ BETWEEN #"+ strBeginDate+"#  AND  #"+strEndDate+"#";
		}
		else if (strBeginDate.length()>0)
		{
			strSQL+="  and ִ������=#"+ strBeginDate+"#";
		}
		else if (strEndDate.length()>0)
		{
			strSQL+="  and ִ������=#"+strEndDate+"#";
		}
		break;
	case SqlServerType:
		if (strBeginDate.length()>0 && strEndDate.length()>0)
		{
			strSQL+="  and ִ������ BETWEEN '"+ strBeginDate+"'  AND  '"+strEndDate+"'";
		}
		else if (strBeginDate.length()>0)
		{
			strSQL+="  and ִ������='"+ strBeginDate+"'";
		}
		else if (strEndDate.length()>0)
		{
			strSQL+="  and ִ������='"+strEndDate+"'";
		}
		break;
	case OracleType:
		if (strBeginDate.length()>0 && strEndDate.length()>0)
		{
			strSQL+="  and ִ������ BETWEEN  to_date('" + strBeginDate + "','dd/mm/yyyy')  AND  to_date('" + strEndDate + "','dd/mm/yyyy')";
		}
		else if (strBeginDate.length()>0)
		{
			strSQL+="  and ִ������=to_date('" + strBeginDate + "','dd/mm/yyyy')";
		}
		else if (strEndDate.length()>0)
		{
			strSQL+="  and ִ������=to_date('" + strEndDate + "','dd/mm/yyyy')";
		}
		break;
	default:
		strSQL= "";
	}
	return strSQL;
}
bool CDuty::CheckCollision(_bstr_t strId,_bstr_t strPolId,_bstr_t strDate,_bstr_t strDutyTimes)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return true;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("ִ�ڱ�"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�ִ�ڱ�ҵ���"),_T("��ʾ"),0);
		return true;
	}
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL="select  ���  from  ִ�ڱ�   where ����ID='"+strPolId+"' and ִ�ڰ��='"+strDutyTimes+"'  ";
	if (strId.length()>0)
		strSQL+="   and ���<>"+strId;
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case AccessType:
		strSQL="  and ִ������=#" + strDate + "#";
		break;
	case SqlServerType:
		strSQL=" and ִ������='" +strDate+" '";
		break;
	case OracleType:
		strSQL=" and ִ������=to_date('" + strDate + "','dd/mm/yyyy')";
		break;
	default :
		return true;
	}

	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	return pRecordSet;
}

//////////////////////////////////////////////////////////////////////////

CDutyTime::CDutyTime()
{

}

CDutyTime::~CDutyTime()
{

}


BOOL CDutyTime::Add(_bstr_t strTime,_bstr_t strRemark)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("ִ�ڰ��"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�ִ�ڰ��ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strColumnsFormat= "", strValuesFormat= "", strSQL;
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case OracleType:
		strColumnsFormat = " (���,ִ��ʱ��,��ע)";
		strValuesFormat = "(ִ�ڰ������.NextVal,'" + strTime + "','"
			+ strRemark + "')";
		break;
	case AccessType:
	case SqlServerType:
		strColumnsFormat = "(ִ��ʱ��,��ע)";
		strValuesFormat = "('" + strTime + "','"
			+ strRemark + "')";
		break;
	default:
		return FALSE;
	}
	strSQL = "INSERT INTO ִ�ڰ�� " + strColumnsFormat + "  Values " + strValuesFormat;
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CDutyTime::Update(_bstr_t strID, _bstr_t strTime, _bstr_t strRemark)
{
	if (strID.length()<=0)
	{
		MessageBox(NULL,_T("�޸ı�Ų���Ϊ�գ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("ִ�ڰ��"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�ִ�ڰ��ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}

	_bstr_t strSQL;
	strSQL = "UPDATE ִ�ڰ�� SET ִ��ʱ�� = '" + strTime
		+ "',��ע = '" + strRemark + "' WHERE ��� = "+ strID;
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CDutyTime::Delete(_bstr_t strIDS)
{
	if (strIDS.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫɾ���ļ�¼��ţ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("ִ�ڰ��"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�ִ�ڰ��ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}

	_bstr_t strSQL;
	strSQL = "DELETE FROM ִ�ڰ�� WHERE ��� IN (" + strIDS + ")";
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

//�õ����԰��
std::vector<string> CDutyTime::QueryTimes()
{
	vector<string> v;
	_RecordsetPtr rcst=QueryDutyTimeByCondit("");
	if (rcst!=NULL&&!rcst->adoEOF)
	{
		string temp;
		while(!rcst->adoEOF)
		{
			temp=(char *)((_bstr_t)rcst->GetCollect("ִ��ʱ��"));
			v.push_back(temp);
			rcst->MoveNext();
		}
	}
	return v;

}

_RecordsetPtr CDutyTime::QueryAllDutyTime()
{
	return QueryDutyTimeByCondit("");
}

void CDutyTime::QueryAllDutyTime(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryAllDutyTime();
	if (Rcst==NULL)
		return;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
}

_RecordsetPtr CDutyTime::QueryDutyTimeByCondit(_bstr_t STRWhere)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("ִ�ڰ��"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�ִ�ڰ��ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSQL = "SELECT ���,ִ��ʱ��,��ע  FROM ִ�ڰ�� WHERE 1=1 " + STRWhere;
	return theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
}

void CDutyTime::QueryDutyTimeByCondit(_bstr_t bstrWhere, vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryDutyTimeByCondit(bstrWhere);
	if (Rcst==NULL)
		return;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
}