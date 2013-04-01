#include "AnalyseDemo.h"


CAnalyseDemo::CAnalyseDemo(void)
{
	m_strID = "";
	m_strName = "";
	m_targetPoint="";
	m_strToTarger = "";
	m_strRange = "0";
	m_strType = "";
	m_strTypeID = "0";
	m_strOuterColor = "0;0;0";
	m_strResultColor = "0;0;0";
	m_strPartResultColor="0;0;0";
	m_strCreator="";
	m_strCreateTime="2010-1-1";
	m_strRemark = "";
}

CAnalyseDemo::~CAnalyseDemo(void)
{
}

_bstr_t CAnalyseDemo::GetWhereString(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName)
{
	_bstr_t strSqlwhere="";
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case OracleType:
		if (strCreatorName.length()>0)
		{
			strSqlwhere+="and ������='"+strCreatorName+"'";
		}
		if (strBeginTime.length()>0&&strEndTime.length()>0)
			strSqlwhere+="  and ����ʱ�� = to_date('" + strBeginTime + "','dd/mm/yyyy') and  to_date('" + strEndTime + "','dd/mm/yyyy')";
		else if(strBeginTime.length()>0)
			strSqlwhere+="    and ����ʱ�� = to_date('" + strBeginTime + "','dd/mm/yyyy')";
		else if(strEndTime.length()>0)
			strSqlwhere+="    and ����ʱ�� = to_date('" + strEndTime + "','dd/mm/yyyy')";
		break;
	case SqlServerType:
		if (strCreatorName.length()>0)
		{
			strSqlwhere+="and ������='"+strCreatorName+"'";
		}
		if (strBeginTime.length()>0&&strEndTime.length()>0)
			strSqlwhere+="  and ����ʱ�� between '"+strBeginTime+"' and '"+strEndTime+"'";
		else if(strBeginTime.length()>0)
			strSqlwhere+="   and ����ʱ��='"+strBeginTime+"'";
		else if(strEndTime.length()>0)
			strSqlwhere+="   and ����ʱ��='"+strEndTime+"'";
		break;
	case AccessType:
		if (strCreatorName.length()>0)
		{
			strSqlwhere+="and ������='"+strCreatorName+"'";
		}
		if (strBeginTime.length()>0&&strEndTime.length()>0)
			strSqlwhere+="  and ����ʱ�� between #"+strBeginTime+"# and #"+strEndTime+"#";
		else if(strBeginTime.length()>0)
			strSqlwhere+="   and ����ʱ��=#"+strBeginTime+"#";
		else if(strEndTime.length()>0)
			strSqlwhere+="   and ����ʱ��=#"+strEndTime+"#";
		break;
	default:
		return "";
	}
	return strSqlwhere;
}
//���ŷ���
//�������������ݿ����

/************************************************************************/
/* ���ط���������Ϣ                                                     */
/************************************************************************/
//���ض���:����������������
BOOL CAnalyseDemo::LoadDemoInfo(_bstr_t bstrId)
{
	//���ݿ����ǰ�ж�
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	if (bstrId.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ���صķ�����ţ�"),_T("��ʾ"),0);
		return FALSE;
	}

	BOOL Brst=FALSE;
	_RecordsetPtr  prstInfo = theBllApp.m_pDB->ExcuteSqlRes("SELECT ���,����,Ŀ���,����Ŀ��,��Χ,����,�߱��,�����ɫ,�����ɫ,���ݽ����ɫ,������,����ʱ��,����  FROM ��������  where ���="+bstrId,adCmdText);
	if (prstInfo!=NULL)
	{
		if(!prstInfo->adoEOF)
		{
			_variant_t var;
			m_strID = bstrId  ;
			var=(prstInfo->GetCollect("����"));
			m_strName = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("Ŀ���"));
			m_targetPoint = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("����Ŀ��"));
			m_strToTarger = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("��Χ")) ;
			m_strRange = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("����")) ;
			m_strType = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("�߱��")) ;
			m_strTypeID = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("�����ɫ")) ;
			m_strOuterColor = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("�����ɫ")) ;
			m_strResultColor = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("���ݽ����ɫ")) ;
			m_strPartResultColor = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("������")) ;
			m_strCreator = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("����ʱ��")) ;
			m_strCreateTime = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("����")) ;
			m_strRemark = (_bstr_t)(var.vt==1?"":var) ;
			Brst=TRUE;
		}	
		prstInfo->Close();
		prstInfo.Release();
	}
	return Brst;

}


//���ض���:������������������
BOOL CAnalyseDemo::LoadDemoInfoByName(_bstr_t bstrName)
{
	//���ݿ����ǰ�ж�
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	if (bstrName.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ���صķ������ƣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	BOOL Brst=FALSE;
	_RecordsetPtr  prstInfo = theBllApp.m_pDB->ExcuteSqlRes("SELECT ���,����,Ŀ���,����Ŀ��,��Χ,����,�߱��,�����ɫ,�����ɫ,���ݽ����ɫ,������,����ʱ��,����  FROM ��������  where ����='"+bstrName+"'",adCmdText);
	if (prstInfo!=NULL)
	{
		if(!prstInfo->adoEOF)
		{
			_variant_t var;
			var=(prstInfo->GetCollect("���"));
			m_strID = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("����"));
			m_strName = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("Ŀ���"));
			m_targetPoint = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("����Ŀ��"));
			m_strToTarger = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("��Χ")) ;
			m_strRange = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("����")) ;
			m_strType = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("�߱��")) ;
			m_strTypeID = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("�����ɫ")) ;
			m_strOuterColor = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("�����ɫ")) ;
			m_strResultColor = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("���ݽ����ɫ")) ;
			m_strPartResultColor = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("������")) ;
			m_strCreator = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("����ʱ��")) ;
			m_strCreateTime = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("����")) ;
			m_strRemark = (_bstr_t)(var.vt==1?"":var) ;
			Brst=TRUE;
		}	
		prstInfo->Close();
		prstInfo.Release();
	}
	return Brst;
}
//�жϷ��������Ƿ����
BOOL CAnalyseDemo::ExistDemoName(_bstr_t bstrName)
{
	//���ݿ����ǰ�ж�
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	if (bstrName.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ���صķ������ƣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	BOOL Brst=FALSE;
	_RecordsetPtr  prstInfo = theBllApp.m_pDB->ExcuteSqlRes("SELECT *  FROM ��������  where ����='"+bstrName+"'",adCmdText);
	if (prstInfo!=NULL)
	{
		if(!prstInfo->adoEOF)
			Brst=TRUE;
		prstInfo->Close();
		prstInfo.Release();
	}
	return Brst;
}
/************************************************************************/
/* ���ط������꣬�������Χ                                             */
/************************************************************************/
//���ط����������Χ��ǰ�����ȼ��ط���
_RecordsetPtr CAnalyseDemo::LoadDemoRange()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("������Χ"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷�����Χҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	if (m_strID.length()==0)
		return FALSE;
	return theBllApp.m_pDB->ExcuteSqlRes("SELECT ���,���� FROM ������Χ WHERE �������= " + m_strID + " )",adCmdText);
}
//���ط����������Χ���������������
_RecordsetPtr CAnalyseDemo::LoadDemoRange( _bstr_t strDemoID )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("������Χ"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷�����Χҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	if (strDemoID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ���صķ�����ţ�"),_T("��ʾ"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSqlRes("SELECT ���,���� FROM ������Χ WHERE �������= " + strDemoID,adCmdText);
}
//���ط����������Χ����������������
vector<string> CAnalyseDemo::LoadDemoRangeByName(_bstr_t strDemoName)
{
	vector<string> vCoodis;
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return vCoodis;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("������Χ"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷�����Χҵ���"),_T("��ʾ"),0);
		return vCoodis;
	}
	if (m_strID.length()==0)
		return vCoodis;
	string strCoodis;
	_RecordsetPtr Rcst= theBllApp.m_pDB->ExcuteSqlRes("select ����  from ������Χ as t,�������� as a  where t.�������=a.��� and ����='"+strDemoName+"'",adCmdText);
	if (Rcst!=NULL&&!Rcst->adoEOF)
	{
		while(!Rcst->adoEOF)
		{
			strCoodis=(char *)(_bstr_t)Rcst->GetCollect("����");
			vCoodis.push_back(strCoodis);
			Rcst->MoveNext();
		}
	}
	return vCoodis;
}
//���ط������ͷ������ꡣǰ�����ȼ��ط���
_RecordsetPtr CAnalyseDemo::LoadDemoCoordinates()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("����������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷���������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	if (m_strID.length()==0)
		return FALSE;
	else
		return theBllApp.m_pDB->ExcuteSqlRes("SELECT ���,����,��ʶ FROM ���������� WHERE �������= " + m_strID + " )",adCmdText);
}
//���ط������ͷ������꣺�������������
_RecordsetPtr CAnalyseDemo::LoadDemoCoordinates( _bstr_t strDemoID)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("����������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷���������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	if (strDemoID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ���صķ�����ţ�"),_T("��ʾ"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSqlRes("SELECT ���,����,��ʶ FROM ���������� WHERE �������= " + strDemoID,adCmdText);
}

//���ط������ͷ������꣺��������������
std::vector<std::vector<string>> CAnalyseDemo::LoadDemoCoodis(_bstr_t strDemoName)
{
	vector<vector<string>> vIds;
	vector<string> vtemp;
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return vIds;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("����������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷���������ҵ���"),_T("��ʾ"),0);
		return vIds;
	}
	if (strDemoName.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ���صķ������ƣ�"),_T("��ʾ"),0);
		return vIds;
	}
	_bstr_t bstrIds,bstNewType="",bstrOldType="";
	string strCoodisTem;
	_RecordsetPtr Rcst= theBllApp.m_pDB->ExcuteSqlRes("select ����,��ʶ  from ���������� as t,�������� as a  where t.�������=a.��� and ����='" + strDemoName + "'  order by ��ʶ",adCmdText);
	if (Rcst!=NULL&&!Rcst->adoEOF)
	{
		bstNewType=(_bstr_t)Rcst->GetCollect("��ʶ");
		bstrOldType=bstNewType;
		while(!Rcst->adoEOF)
		{
			bstNewType=(_bstr_t)Rcst->GetCollect("��ʶ");
			strCoodisTem=(char*)(_bstr_t)Rcst->GetCollect("����");
			if (bstNewType==bstrOldType)
			{
				vtemp.push_back(strCoodisTem);
			}
			else
			{
				vIds.push_back(vtemp);
				vtemp.clear();
				vtemp.push_back(strCoodisTem);
			}
			bstrOldType=bstNewType;
			Rcst->MoveNext();
		}
		if (!vtemp.empty())
			vIds.push_back(vtemp);
	}
	return vIds;
}
vector<string> CAnalyseDemo::LoadDemoResult( _bstr_t strDemoName)
{
	vector<string> vIds;
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return vIds;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�������ͽ��"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷������ͽ��ҵ���"),_T("��ʾ"),0);
		return vIds;
	}
	if (strDemoName.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ���صķ������ƣ�"),_T("��ʾ"),0);
		return vIds;
	}
	string bstrIds;
	_RecordsetPtr Rcst= theBllApp.m_pDB->ExcuteSqlRes("select t.����ID  from �������ͽ�� as t,�������� as a  where t.�������=a.��� and ����='" + strDemoName + "'",adCmdText);
	if (Rcst!=NULL&&!Rcst->adoEOF)
	{
		while(!Rcst->adoEOF)
		{
			bstrIds=(char*)(_bstr_t)Rcst->GetCollect("����ID");
			vIds.push_back(bstrIds);
			Rcst->MoveNext();
		}
	}
	return vIds;
}
/************************************************************************/
/* ���ط���                                                             */
/************************************************************************/
//���������Ի��߼�ط���������¼
_RecordsetPtr CAnalyseDemo::LoadAllDrawLineDemo( _bstr_t bstrWhere )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSqlRes("SELECT * FROM ��������  WHERE ����='�Ի��߼��' "  + bstrWhere,adCmdText);
}

void CAnalyseDemo::LoadAllDrawLineDemo(_bstr_t bstrWhere ,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return ;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷�������ҵ���"),_T("��ʾ"),0);
		return ;
	}

	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(LoadAllDrawLineDemo(bstrWhere),vecField,vecRecordSet,lFieldCounts);
}
//�������������߼�ط���������¼
_RecordsetPtr CAnalyseDemo::LoadAllFRowLineDemo( _bstr_t bstrWhere )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSqlRes("SELECT * FROM ��������  WHERE ����='�����߼��'" + bstrWhere,adCmdText);
}

void CAnalyseDemo::LoadAllFRowLineDemo(_bstr_t bstrWhere ,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return ;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷�������ҵ���"),_T("��ʾ"),0);
		return ;
	}
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(LoadAllFRowLineDemo(bstrWhere),vecField,vecRecordSet,lFieldCounts);
}

//�������е㷽��������¼
_RecordsetPtr CAnalyseDemo::LoadAllPointDemo( _bstr_t bstrWhere )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSqlRes("SELECT * FROM ��������  WHERE ����='��'" + bstrWhere,adCmdText);
}

void CAnalyseDemo::LoadAllPointDemo(_bstr_t bstrWhere ,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return ;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷�������ҵ���"),_T("��ʾ"),0);
		return;
	}
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(LoadAllPointDemo(bstrWhere),vecField,vecRecordSet,lFieldCounts);
}
//���������淽��������¼
_RecordsetPtr CAnalyseDemo::LoadAllRangDemo( _bstr_t bstrWhere )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSqlRes("SELECT * FROM ��������  WHERE ����='��'" + bstrWhere,adCmdText);
}

void CAnalyseDemo::LoadAllRangDemo(_bstr_t bstrWhere ,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷�������ҵ���"),_T("��ʾ"),0);
		return;
	}
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(LoadAllRangDemo(bstrWhere),vecField,vecRecordSet,lFieldCounts);
}


//���ط������ͷ�������


/************************************************************************/
/*     ���淽��                                                         */
/************************************************************************/

//�����Ի��߼�ط���������¼,
//������������ţ�����ͷ����б���������б�
//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
BOOL CAnalyseDemo::SaveDrawLineDemo(std::vector<_bstr_t> strCameraIds , std::vector<_bstr_t> strPoliceIds)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t bstrTempSql="";
	_bstr_t bstrValue="";
	std::vector<_bstr_t> vbstrSql;
	_RecordsetPtr prst;
	_CommandPtr m_pCommand=theBllApp.m_pDB->GetCommand();
	_ConnectionPtr m_pConnection=theBllApp.m_pDB->GetConnection();

	//����
	try
	{
		m_pCommand->ActiveConnection=m_pConnection;
		m_pConnection->BeginTrans();
		//�·���
		if (m_strID.length()==0)
		{
			switch(CDatabaseFactory::m_enumDatabaseType)
			{
			case AccessType:
				m_pCommand->CommandText = "INSERT INTO ��������(����,����Ŀ��,��Χ,����,�߱��,�����ɫ,�����ɫ,������,����ʱ��,����)VALUES('"+
					m_strName+"','"+ m_strToTarger +"',"+m_strRange+",'�Ի��߼��',"+ m_strTypeID +",'"+m_strOuterColor+"','"
					+m_strResultColor + "','"+m_strCreator+"',#"+m_strCreateTime+"#,'" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "SELECT MAX(���) AS ����� FROM �������� ";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break;
			case SqlServerType:
				m_pCommand->CommandText = "INSERT INTO ��������(����,����Ŀ��,��Χ,����,�߱��,�����ɫ,�����ɫ,������,����ʱ��,����)VALUES('"+
					m_strName+"','"+ m_strToTarger +"',"+m_strRange+",'�Ի��߼��',"+ m_strTypeID +",'"+m_strOuterColor+"','"
					 +m_strResultColor + "','" +m_strCreator+"','"+m_strCreateTime+"','"+ m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "SELECT MAX(���) AS ����� FROM �������� ";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break;
			case OracleType:
				m_pCommand->CommandText = "INSERT INTO ��������(���,����,����Ŀ��,��Χ,����,�߱��,�����ɫ,�����ɫ,������,����ʱ��,����)VALUES(������������.NextVal,'"
					+m_strName+"','"+ m_strToTarger +"',"+m_strRange+",'�Ի��߼��',"+ m_strTypeID +",'"+m_strOuterColor+"','"
					 +m_strResultColor + "','"+m_strCreator+"',to_date('" + m_strCreateTime + "','dd/mm/yyyy'),'" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "select ������������.currval as ����� from dual";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break ;
			default:
				break;
			}

			//���ñ��
			if (prst==NULL && prst->adoEOF)
			{
				m_pConnection->RollbackTrans();
				return FALSE;
			}
			prst->MoveFirst();
			_variant_t var;
			var=prst->GetCollect("�����");
			if (var.vt==1)
			{
				m_pConnection->RollbackTrans();
				return FALSE;
			}
			m_strID=((_bstr_t)prst->GetCollect("�����"));
			prst->Close();
			prst.Release();
		}
		else //�޸ķ���
		{
			//�޸ķ�����Ϣ
			m_pCommand->CommandText = "UPDATE �������� SET  ���� = '"+m_strName+"',����Ŀ�� = '"+m_strToTarger+"',��Χ = "+m_strRange+",���� = '"+m_strRemark+"' WHERE  ���=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
			//���ԭ���������
			m_pCommand->CommandText = "DELETE  FROM �������ͽ�� WHERE �������=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
		}

		//����ͷ���ͽ��
		for ( vector <_bstr_t>::iterator strSql = strCameraIds.begin(); strSql != strCameraIds.end(); strSql++ )
		{
			bstrValue=((_bstr_t)*strSql);
			bstrTempSql="INSERT INTO �������ͽ��(�������,����,����ID)VALUES("+m_strID+",'����ͷ','"+bstrValue+"')";
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			{
				bstrTempSql="INSERT INTO �������ͽ��(���,�������,����,����ID)VALUES(�������ͽ��.NextVal,"+m_strID+",'����ͷ','"+bstrValue+"')";
			}
			m_pCommand->CommandText = bstrTempSql;
			m_pCommand->Execute(NULL,NULL,adCmdText);
		}
		//�������ͽ��
		for ( vector <_bstr_t>::iterator strSql = strPoliceIds.begin(); strSql != strPoliceIds.end(); strSql++ )
		{
			bstrValue=((_bstr_t)*strSql);
			bstrTempSql="INSERT INTO �������ͽ��(�������,����,����ID)VALUES("+m_strID+",'����','"+bstrValue+"')";
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			{
				bstrTempSql="INSERT INTO �������ͽ��(���,�������,����,����ID)VALUES(�������ͽ��.NextVal,"+m_strID+",'����','"+bstrValue+"')";
			}
			m_pCommand->CommandText = bstrTempSql;
			m_pCommand->Execute(NULL,NULL,adCmdText);
		}
		m_pConnection->CommitTrans();
	}
	catch(_com_error e)
	{
		m_pConnection->RollbackTrans();
		return FALSE;
	}
	return TRUE;
}

//���������߼�ط���������¼,
//������������ţ�����ͷ����б���������б�
//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
BOOL CAnalyseDemo::SaveFRowLineDemo(std::vector<_bstr_t> strCameraIds , std::vector<_bstr_t> strPoliceIds)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t bstrTempSql="";
	_bstr_t bstrValue="";
	_RecordsetPtr prst;
	_CommandPtr m_pCommand=theBllApp.m_pDB->GetCommand();
	_ConnectionPtr m_pConnection=theBllApp.m_pDB->GetConnection();

	//����
	try
	{
		m_pCommand->ActiveConnection=m_pConnection;
		m_pConnection->BeginTrans();
		if (m_strID.length()==0)
		{
			switch(CDatabaseFactory::m_enumDatabaseType)
			{
			case AccessType:
				m_pCommand->CommandText = "INSERT INTO ��������(����,����Ŀ��,��Χ,����,�߱��,�����ɫ,�����ɫ,������,����ʱ��,����)VALUES('"
					+m_strName+"','"+ m_strToTarger +"',"+m_strRange+",'�����߼��',"+ m_strTypeID +",'"+m_strOuterColor+"','"
					 +m_strResultColor + "','"+m_strCreator+"',#"+m_strCreateTime+"#,'" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "SELECT MAX(���) AS ����� FROM �������� ";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break;
			case SqlServerType:
				m_pCommand->CommandText = "INSERT INTO ��������(����,����Ŀ��,��Χ,����,�߱��,�����ɫ,�����ɫ,������,����ʱ��,����)VALUES('"
					+m_strName+"','"+ m_strToTarger +"',"+m_strRange+",'�����߼��',"+ m_strTypeID +",'"+m_strOuterColor+"','"
					 +m_strResultColor +"','"+m_strCreator+"','"+m_strCreateTime+ "','" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "SELECT MAX(���) AS ����� FROM �������� ";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break;
			case OracleType:
				m_pCommand->CommandText = "INSERT INTO ��������(���,����,����Ŀ��,��Χ,����,�߱��,�����ɫ,�����ɫ,������,����ʱ��,����)VALUES(������������.NextVal,'"
					+m_strName+"','"+ m_strToTarger +"',"+m_strRange+",'�����߼��',"+ m_strTypeID +",'"+m_strOuterColor+"','"
					 +m_strResultColor +"','"+m_strCreator+"',to_date('" + m_strCreateTime + "','dd/mm/yyyy'),'" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "select ������������.currval as ����� from dual";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break ;
			default:
				break;
			}
			//���ñ��
			if (prst==NULL && prst->MoveFirst())
			{
				m_pConnection->RollbackTrans();
				return FALSE;
			}
			prst->MoveFirst();
			_variant_t var;
			var=prst->GetCollect("�����");
			if (var.vt==1)
			{
				m_pConnection->RollbackTrans();
				return FALSE;
			}
			m_strID=((_bstr_t)prst->GetCollect("�����"));
			prst->Close();
			prst.Release();
		} 
		else
		{
			//�޸ķ�����Ϣ
			m_pCommand->CommandText = "UPDATE �������� SET  ���� = '"+m_strName+"',����Ŀ�� = '"+m_strToTarger+"',��Χ = "+m_strRange+",���� = '"+m_strRemark+"' WHERE  ���=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
			//���ԭ���������
			m_pCommand->CommandText = "DELETE  FROM �������ͽ�� WHERE �������=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
		}
		//����ͷ���ͽ��
		for ( vector <_bstr_t>::iterator strSql = strCameraIds.begin(); strSql != strCameraIds.end(); strSql++ )
		{
			bstrValue=((_bstr_t)*strSql);
			bstrTempSql="INSERT INTO �������ͽ��(�������,����,����ID)VALUES("+m_strID+",'����ͷ','"+bstrValue+"')";
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			{
				bstrTempSql="INSERT INTO �������ͽ��(���,�������,����,����ID)VALUES(�������ͽ��.NextVal,"+m_strID+",'����ͷ','"+bstrValue+"')";
			}
			m_pCommand->CommandText = bstrTempSql;
			m_pCommand->Execute(NULL,NULL,adCmdText);
		}
		//�������ͽ��
		for ( vector <_bstr_t>::iterator strSql = strPoliceIds.begin(); strSql != strPoliceIds.end(); strSql++ )
		{
			bstrValue=((_bstr_t)*strSql);
			bstrTempSql="INSERT INTO �������ͽ��(�������,����,����ID)VALUES("+m_strID+",'����','"+bstrValue+"')";
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			{
				bstrTempSql="INSERT INTO �������ͽ��(���,�������,����,����ID)VALUES(�������ͽ��.NextVal,"+m_strID+",'����','"+bstrValue+"')";
			}
			m_pCommand->CommandText = bstrTempSql;
			m_pCommand->Execute(NULL,NULL,adCmdText);
		}
		m_pConnection->CommitTrans();
	}
	catch(_com_error e)
	{
		m_pConnection->RollbackTrans();
		return FALSE;
	}
	return TRUE;
}


//���ӵ㷽��������¼,
//������key����ID,value�����б�
//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
BOOL CAnalyseDemo::SavePointDemo(std::map<_bstr_t,std::vector<vector<_bstr_t>>> mBuilding)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t bstrTempSql="";
	_bstr_t bstrValue="";
	_bstr_t bstrCoodinate="";
	vector<vector<_bstr_t>> vvcoodis;
	std::vector<_bstr_t> vcoodis;
	_RecordsetPtr prst;
	_CommandPtr m_pCommand=theBllApp.m_pDB->GetCommand();
	_ConnectionPtr m_pConnection=theBllApp.m_pDB->GetConnection();

	//����
	try
	{
		m_pCommand->ActiveConnection=m_pConnection;
		m_pConnection->BeginTrans();
		if (m_strID.length() == 0 )
		{
			switch(CDatabaseFactory::m_enumDatabaseType)
			{
			case AccessType:
				m_pCommand->CommandText = "INSERT INTO ��������(����,Ŀ���,����Ŀ��,��Χ,����,�߱��,�����ɫ,�����ɫ,������,����ʱ��,����)VALUES('"
					+m_strName+"','"+m_targetPoint+"','"+ m_strToTarger +"',"+m_strRange+",'��',"+ m_strTypeID +",'"+m_strOuterColor+"','"
					 +m_strResultColor + "','"+m_strCreator+"',#"+m_strCreateTime+"#,'" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "SELECT MAX(���) AS ����� FROM �������� ";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break;
			case SqlServerType:
				m_pCommand->CommandText = "INSERT INTO ��������(����,Ŀ���,����Ŀ��,��Χ,����,�߱��,�����ɫ,�����ɫ,������,����ʱ��,����)VALUES('"
					+m_strName+"','"+m_targetPoint+"','"+ m_strToTarger +"',"+m_strRange+",'��',"+ m_strTypeID +",'"+m_strOuterColor+"','"
					+m_strResultColor + "','"+m_strCreator+"','"+m_strCreateTime+"','" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "SELECT MAX(���) AS ����� FROM �������� ";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break;
			case OracleType:
				m_pCommand->CommandText = "INSERT INTO ��������(���,����,Ŀ���,����Ŀ��,��Χ,����,�߱��,�����ɫ,�����ɫ,������,����ʱ��,����)VALUES(������������.NextVal,'"
					+m_strName+"','"+m_targetPoint+"','"+ m_strToTarger +"',"+m_strRange+",'��',"+ m_strTypeID +",'"+m_strOuterColor
					+"','" +m_strResultColor + "','"+m_strCreator+"',to_date('" + m_strCreateTime + "','dd/mm/yyyy'),'" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "select ������������.currval as ����� from dual";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break ;
			default:
				break;
			}

			//���ñ��
			if (prst==NULL && prst->adoEOF)
			{
				m_pConnection->RollbackTrans();
				return FALSE;
			}
			prst->MoveFirst();
			_variant_t var;
			var=prst->GetCollect("�����");
			if (var.vt==1)
			{
				m_pConnection->RollbackTrans();
				return FALSE;
			}
			m_strID=((_bstr_t)prst->GetCollect("�����"));
			prst->Close();
			prst.Release();
		} 
		else
		{
			//�޸ķ�����Ϣ
			m_pCommand->CommandText = "UPDATE �������� SET  ���� = '"+m_strName+"',����Ŀ�� = '"+m_strToTarger+"',��Χ = "+m_strRange+",�����ɫ ='"+m_strOuterColor+"',�����ɫ = '"+m_strResultColor+"',���� = '"+m_strRemark+"'  WHERE  ���=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
			//���ԭ���������
			m_pCommand->CommandText = "DELETE  FROM �������ͽ�� WHERE �������=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
			m_pCommand->CommandText = "DELETE  FROM ���������� WHERE �������=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
		}
		int iflag=0;
		_bstr_t strFlag;
		char strFlagTemp[8];
		for ( map <_bstr_t,std::vector<vector<_bstr_t>>> :: iterator item = mBuilding.begin() ; item != mBuilding.end() ; item++ )
		{
			iflag++;
			_itoa_s(iflag,strFlagTemp,10);
			strFlag=strFlagTemp;

			bstrValue=item->first;
			vvcoodis=item->second;
			bstrTempSql="INSERT INTO �������ͽ��(�������,����,����ID)VALUES("+m_strID+",'����','"+bstrValue+"')";
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			{
				bstrTempSql="INSERT INTO �������ͽ��(���,�������,����,����ID)VALUES(�������ͽ��.NextVal,"+m_strID+",'����','"+bstrValue+"')";
			}
			m_pCommand->CommandText = bstrTempSql;
			m_pCommand->Execute(NULL,NULL,adCmdText);

			for ( vector <vector<_bstr_t>>::iterator vvSql = vvcoodis.begin(); vvSql != vvcoodis.end(); vvSql++ )
			{
				vcoodis=*vvSql;
				for (vector<_bstr_t>::iterator vsql=vcoodis.begin();vsql!=vcoodis.end();vsql++)
				{
					bstrCoodinate=(*vsql);
					bstrTempSql="INSERT INTO ����������(�������,����,��ʶ)VALUES(" + m_strID + ",'"  + bstrCoodinate + "','" + strFlag + "')";
					if (CDatabaseFactory::m_enumDatabaseType==OracleType)
					{
						bstrTempSql="INSERT INTO ����������(���,�������,����,��ʶ)VALUES(����������.NextVal," + m_strID + ",'"  + bstrCoodinate + "','" + strFlag + "')";
					}
					m_pCommand->CommandText = bstrTempSql;
					m_pCommand->Execute(NULL,NULL,adCmdText);
				}
			}
		}
		m_pConnection->CommitTrans();
	}
	catch(_com_error e)
	{
		m_pConnection->RollbackTrans();
		return FALSE;
	}
	return TRUE;
}
//�²���

BOOL CAnalyseDemo::SavePointDemo(_bstr_t strNewName,vector<_bstr_t> vGuid,vector<vector<_bstr_t>> vvCoodints)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_RecordsetPtr prst;
	_CommandPtr m_pCommand=theBllApp.m_pDB->GetCommand();
	_ConnectionPtr m_pConnection=theBllApp.m_pDB->GetConnection();
	//����
	try
	{
		m_pCommand->ActiveConnection=m_pConnection;
		m_pConnection->BeginTrans();
		//������Ϣ¼�� begin
		if (m_strID.length() == 0 )
		{
			switch(CDatabaseFactory::m_enumDatabaseType)
			{
			case AccessType:
				m_pCommand->CommandText = "INSERT INTO ��������(����,Ŀ���,����Ŀ��,��Χ,����,�߱��,�����ɫ,�����ɫ,������,����ʱ��,����)VALUES('"
					+m_strName+"','"+m_targetPoint+"','"+ m_strToTarger +"',"+m_strRange+",'��',"+ m_strTypeID +",'"+m_strOuterColor+"','"
					+m_strResultColor + "','"+m_strCreator+"',#"+m_strCreateTime+"#,'" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "SELECT MAX(���) AS ����� FROM �������� ";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break;
			case SqlServerType:
				m_pCommand->CommandText = "INSERT INTO ��������(����,Ŀ���,����Ŀ��,��Χ,����,�߱��,�����ɫ,�����ɫ,������,����ʱ��,����)VALUES('"
					+m_strName+"','"+m_targetPoint+"','"+ m_strToTarger +"',"+m_strRange+",'��',"+ m_strTypeID +",'"+m_strOuterColor+"','"
					+m_strResultColor + "','"+m_strCreator+"','"+m_strCreateTime+"','" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "SELECT MAX(���) AS ����� FROM �������� ";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break;
			case OracleType:
				m_pCommand->CommandText = "INSERT INTO ��������(���,����,Ŀ���,����Ŀ��,��Χ,����,�߱��,�����ɫ,�����ɫ,������,����ʱ��,����)VALUES(������������.NextVal,'"
					+m_strName+"','"+m_targetPoint+"','"+ m_strToTarger +"',"+m_strRange+",'��',"+ m_strTypeID +",'"+m_strOuterColor
					+"','" +m_strResultColor + "','"+m_strCreator+"',to_date('" + m_strCreateTime + "','dd/mm/yyyy'),'" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "select ������������.currval as ����� from dual";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break ;
			default:
				break;
			}//end switch

			//���ñ��
			if (prst==NULL && prst->adoEOF)
			{
				m_pConnection->RollbackTrans();
				return FALSE;
			}
			prst->MoveFirst();
			_variant_t var;
			var=prst->GetCollect("�����");
			if (var.vt==1)
			{
				m_pConnection->RollbackTrans();
				return FALSE;
			}
			m_strID=((_bstr_t)prst->GetCollect("�����"));
			prst->Close();
			prst.Release();
		} //end if insert
		else
		{
			//�޸ķ�����Ϣ
			m_pCommand->CommandText = "UPDATE �������� SET  ���� = '"+m_strName+"',Ŀ���='"+m_targetPoint+"',����Ŀ�� = '"+m_strToTarger+"',��Χ = "+m_strRange+",�����ɫ ='"+m_strOuterColor+"',�����ɫ = '"+m_strResultColor+"',���� = '"+m_strRemark+"'  WHERE  ���=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
			//���ԭ���������
			m_pCommand->CommandText = "DELETE  FROM �������ͽ�� WHERE �������=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
			m_pCommand->CommandText = "DELETE  FROM ���������� WHERE �������=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
		} //end else update  //������Ϣ¼��end

		//�������¼�� begin
		_bstr_t bstrTempSql="",bstrGuid="";
		for (std::vector<_bstr_t>::iterator myGuid=vGuid.begin();myGuid!=vGuid.end();myGuid++)
		{
			bstrGuid=*myGuid;
			bstrTempSql="INSERT INTO �������ͽ��(�������,����,����ID)VALUES("+m_strID+",'����','"+bstrGuid+"')";
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			{
				bstrTempSql="INSERT INTO �������ͽ��(���,�������,����,����ID)VALUES(�������ͽ��.NextVal,"+m_strID+",'����','"+bstrGuid+"')";
			}
			m_pCommand->CommandText = bstrTempSql;
			m_pCommand->Execute(NULL,NULL,adCmdText);
		}//end for     //�������¼�� end

		//��������¼��begin
		std::vector<_bstr_t> vcoondnt;
		int iflag=0;
		_bstr_t strFlag;
		char strFlagTemp[8];
		for ( std::vector <std::vector<_bstr_t>>::iterator vvSql = vvCoodints.begin(); vvSql != vvCoodints.end(); vvSql++ )
		{
			vcoondnt=*vvSql;
			iflag++;
			_itoa_s(iflag,strFlagTemp,10);
			strFlag=strFlagTemp;
			for (vector<_bstr_t>::iterator vsql=vcoondnt.begin();vsql!=vcoondnt.end();vsql++)
			{
				bstrGuid=*vsql;
				bstrTempSql="INSERT INTO ����������(�������,����,��ʶ)VALUES(" + m_strID + ",'"  + bstrGuid + "','" + strFlag + "')";
				if (CDatabaseFactory::m_enumDatabaseType==OracleType)
				{
					bstrTempSql="INSERT INTO ����������(���,�������,����,��ʶ)VALUES(����������.NextVal," + m_strID + ",'"  + bstrGuid + "','" + strFlag + "')";
				}
				m_pCommand->CommandText = bstrTempSql;
				m_pCommand->Execute(NULL,NULL,adCmdText);
			}
		}// end for ��������¼�� end
		
		//�ύ����
		m_pConnection->CommitTrans();
	} //end try 
	catch(_com_error e)
	{
		m_pConnection->RollbackTrans();
		return FALSE;
	}
	return TRUE;
}
//�����淽��������¼,
//������key����ID,value�����б�,
//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
BOOL CAnalyseDemo::SaveRangDemo(std::map<_bstr_t,std::vector<vector<_bstr_t>>> mBuilding ,std::vector<_bstr_t> strRanges )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t bstrTempSql="";
	_bstr_t bstrValue="";
	_bstr_t bstrCoodinate="";
	vector<vector<_bstr_t>> vvcoodis;
	std::vector<_bstr_t> vcoodis;
	_RecordsetPtr prst;
	_CommandPtr m_pCommand=theBllApp.m_pDB->GetCommand();
	_ConnectionPtr m_pConnection=theBllApp.m_pDB->GetConnection();

	//����
	try
	{
		m_pCommand->ActiveConnection=m_pConnection;
		m_pConnection->BeginTrans();
		if (m_strID.length()==0)
		{
			switch(CDatabaseFactory::m_enumDatabaseType)
			{
			case AccessType:
				m_pCommand->CommandText = "INSERT INTO ��������(����,����Ŀ��,��Χ,����,�߱��,�����ɫ,�����ɫ,������,����ʱ��,����)VALUES('"
					+m_strName+"','"+ m_strToTarger +"',"+m_strRange+",'��',"+ m_strTypeID +",'"+m_strOuterColor
					+"','" +m_strResultColor + "','"+m_strCreator+"',#"+m_strCreateTime+"#,'" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "SELECT MAX(���) AS ����� FROM �������� ";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break;
			case SqlServerType:
				m_pCommand->CommandText = "INSERT INTO ��������(����,����Ŀ��,��Χ,����,�߱��,�����ɫ,�����ɫ,������,����ʱ��,����)VALUES('"
					+m_strName+"','"+ m_strToTarger +"',"+m_strRange+",'��',"+ m_strTypeID +",'"+m_strOuterColor
					+"','" +m_strResultColor + "','" +m_strCreator+"','"+m_strCreateTime+"','"+ m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "SELECT MAX(���) AS ����� FROM �������� ";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break;
			case OracleType:
				m_pCommand->CommandText = "INSERT INTO ��������(���,����,����Ŀ��,��Χ,����,�߱��,�����ɫ,�����ɫ,������,����ʱ��,����)VALUES(������������.NextVal,'"
					+m_strName+"','"+ m_strToTarger +"',"+m_strRange+",'��',"+ m_strTypeID +",'"+m_strOuterColor
					+"','" +m_strResultColor + "','" +m_strCreator+"',to_date('" + m_strCreateTime + "','dd/mm/yyyy'),'"+ m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "select ������������.currval as ����� from dual";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break ;
			default:
				break;
			}

			//���ñ��
			if (prst==NULL || prst->adoEOF)
			{
				m_pConnection->RollbackTrans();
				return FALSE;
			}
			prst->MoveFirst();
			_variant_t var;
			var=prst->GetCollect("�����");
			if (var.vt==1)
			{
				m_pConnection->RollbackTrans();
				return FALSE;
			}

			m_strID=((_bstr_t)prst->GetCollect("�����"));
			prst->Close();
			prst.Release();
		} 
		else
		{
			//�޸ķ�����Ϣ
			m_pCommand->CommandText = "UPDATE �������� SET  ���� = '"+m_strName+"',����Ŀ�� = '"+m_strToTarger+"',��Χ = "+m_strRange+",�����ɫ ='"+m_strOuterColor+"',�����ɫ = '"+m_strResultColor+"',���� = '"+m_strRemark+"'  WHERE  ���=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
			//���ԭ���������
			m_pCommand->CommandText = "DELETE  FROM �������ͽ�� WHERE �������=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
			m_pCommand->CommandText = "DELETE  FROM ���������� WHERE �������=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
			m_pCommand->CommandText = "DELETE  FROM ������Χ WHERE �������=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
		}

		//�������ͺͷ�������
		int iflag=0;
		_bstr_t strFlag;
		char strFlagTemp[8];

		for ( map <_bstr_t,std::vector<vector<_bstr_t>>> :: iterator item = mBuilding.begin() ; item != mBuilding.end() ; item++ )
		{
			iflag++;
			_itoa_s(iflag,strFlagTemp,10);
			strFlag=strFlagTemp;

			bstrValue=item->first;
			vvcoodis=item->second;
			bstrTempSql="INSERT INTO �������ͽ��(�������,����,����ID)VALUES("+m_strID+",'����','"+bstrValue+"')";
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			{
				bstrTempSql="INSERT INTO �������ͽ��(���,�������,����,����ID)VALUES(�������ͽ��.NextVal,"+m_strID+",'����','"+bstrValue+"')";
			}
			m_pCommand->CommandText = bstrTempSql;
			m_pCommand->Execute(NULL,NULL,adCmdText);

			for ( vector <vector<_bstr_t>>::iterator vvSql = vvcoodis.begin(); vvSql != vvcoodis.end(); vvSql++ )
			{
				vcoodis=*vvSql;
				for (vector<_bstr_t>::iterator strSql=vcoodis.begin();strSql!=vcoodis.end();strSql++)
				{
					bstrCoodinate=((_bstr_t)*strSql);
					bstrTempSql="INSERT INTO ����������(�������,����,��ʶ)VALUES(" + m_strID + ",'"  + bstrCoodinate + "','" + strFlag + "')";
					if (CDatabaseFactory::m_enumDatabaseType==OracleType)
					{
						bstrTempSql="INSERT INTO ����������(���,�������,����,��ʶ)VALUES(����������.NextVal," + m_strID + ",'"  + bstrCoodinate + "','" + strFlag + "')";
					}
					m_pCommand->CommandText = bstrTempSql;
					m_pCommand->Execute(NULL,NULL,adCmdText);
				}
			}
		}
		//������Χ
		for ( vector <_bstr_t>::iterator strSql = strRanges.begin(); strSql != strRanges.end(); strSql++ )
		{
			bstrCoodinate=((_bstr_t)*strSql);
			bstrTempSql="INSERT INTO ������Χ(�������,����)VALUES("+m_strID+",'" + bstrCoodinate + "')";
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			{
				bstrTempSql="INSERT INTO ������Χ(���,�������,����)VALUES(������Χ.NextVal,"+m_strID+",'" + bstrCoodinate + "')";
			}
			m_pCommand->CommandText = bstrTempSql;
			m_pCommand->Execute(NULL,NULL,adCmdText);
		}

		m_pConnection->CommitTrans();
	}
	catch(_com_error e)
	{
		m_pConnection->RollbackTrans();
		return FALSE;
	}
	return TRUE;
}
BOOL  CAnalyseDemo::SaveRangDemo(_bstr_t strNewName,std::vector<_bstr_t> vGuid,std::vector<std::vector<_bstr_t>> vvCoodints,std::vector<_bstr_t> strRanges )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	if (m_strName.length()==0)
	{
		MessageBox(NULL,_T("�����뷽�����ƣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (m_strRange.length()==0)
	{
		MessageBox(NULL,_T("�����������Χ��"),_T("��ʾ"),0);
		return FALSE;
	}
	_RecordsetPtr prst;
	_CommandPtr m_pCommand=theBllApp.m_pDB->GetCommand();
	_ConnectionPtr m_pConnection=theBllApp.m_pDB->GetConnection();
	//������Ϣ
	try
	{
		m_pCommand->ActiveConnection=m_pConnection;
		m_pConnection->BeginTrans();
		if (m_strID.length()==0)
		{
			switch(CDatabaseFactory::m_enumDatabaseType)
			{
			case AccessType:
				m_pCommand->CommandText = "INSERT INTO ��������(����,����Ŀ��,��Χ,����,�߱��,�����ɫ,�����ɫ,������,����ʱ��,����)VALUES('"
					+m_strName+"','"+ m_strToTarger +"',"+m_strRange+",'��',"+ m_strTypeID +",'"+m_strOuterColor
					+"','" +m_strResultColor + "','"+m_strCreator+"',#"+m_strCreateTime+"#,'" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "SELECT MAX(���) AS ����� FROM �������� ";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break;
			case SqlServerType:
				m_pCommand->CommandText = "INSERT INTO ��������(����,����Ŀ��,��Χ,����,�߱��,�����ɫ,�����ɫ,������,����ʱ��,����)VALUES('"
					+m_strName+"','"+ m_strToTarger +"',"+m_strRange+",'��',"+ m_strTypeID +",'"+m_strOuterColor
					+"','" +m_strResultColor + "','" +m_strCreator+"','"+m_strCreateTime+"','"+ m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "SELECT MAX(���) AS ����� FROM �������� ";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break;
			case OracleType:
				m_pCommand->CommandText = "INSERT INTO ��������(���,����,����Ŀ��,��Χ,����,�߱��,�����ɫ,�����ɫ,������,����ʱ��,����)VALUES(������������.NextVal,'"
					+m_strName+"','"+ m_strToTarger +"',"+m_strRange+",'��',"+ m_strTypeID +",'"+m_strOuterColor
					+"','" +m_strResultColor + "','" +m_strCreator+"',to_date('" + m_strCreateTime + "','dd/mm/yyyy'),'"+ m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "select ������������.currval as ����� from dual";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break ;
			default:
				break;
			}//end switch
			//���ñ��
			if (prst==NULL || prst->adoEOF)
			{
				m_pConnection->RollbackTrans();
				return FALSE;
			}
			prst->MoveFirst();
			_variant_t var;
			var=prst->GetCollect("�����");
			if (var.vt==1)
			{
				m_pConnection->RollbackTrans();
				return FALSE;
			}
			m_strID=((_bstr_t)prst->GetCollect("�����"));
			prst->Close();
			prst.Release();
		} //end if ���뷽��������Ϣ
		else
		{
			//�޸ķ�����Ϣ
			m_pCommand->CommandText = "UPDATE �������� SET  ���� = '"+m_strName+"',����Ŀ�� = '"+m_strToTarger+"',��Χ = "+m_strRange+",�����ɫ ='"+m_strOuterColor+"',�����ɫ = '"+m_strResultColor+"',���� = '"+m_strRemark+"'  WHERE  ���=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
			//���ԭ���������
			m_pCommand->CommandText = "DELETE  FROM �������ͽ�� WHERE �������=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
			m_pCommand->CommandText = "DELETE  FROM ���������� WHERE �������=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
			m_pCommand->CommandText = "DELETE  FROM ������Χ WHERE �������=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
		}//end else �������·�������
		_bstr_t bstrTempSql="";
		_bstr_t bstrValue="";
		//�����������
		for (std::vector<_bstr_t>::iterator vitem=vGuid.begin();vitem!=vGuid.end();vitem++)
		{
			bstrValue=*vitem;
			bstrTempSql="INSERT INTO �������ͽ��(�������,����,����ID)VALUES("+m_strID+",'����','"+bstrValue+"')";
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			{
				bstrTempSql="INSERT INTO �������ͽ��(���,�������,����,����ID)VALUES(�������ͽ��.NextVal,"+m_strID+",'����','"+bstrValue+"')";
			}
			m_pCommand->CommandText = bstrTempSql;
			m_pCommand->Execute(NULL,NULL,adCmdText);
		}
		//���������� 
		int iflag=0;
		_bstr_t strFlag;
		char strFlagTemp[8];
		std::vector<_bstr_t> vcoodis;
		_bstr_t bstrCoodinate="";
		for ( vector <vector<_bstr_t>>::iterator vvSql = vvCoodints.begin(); vvSql != vvCoodints.end(); vvSql++ )
		{
			iflag++;
			_itoa_s(iflag,strFlagTemp,10);
			strFlag=strFlagTemp;
			vcoodis=*vvSql;
			for (vector<_bstr_t>::iterator strSql=vcoodis.begin();strSql!=vcoodis.end();strSql++)
			{
				bstrCoodinate=*strSql;
				bstrTempSql="INSERT INTO ����������(�������,����,��ʶ)VALUES(" + m_strID + ",'"  + bstrCoodinate + "','" + strFlag + "')";
				if (CDatabaseFactory::m_enumDatabaseType==OracleType)
				{
					bstrTempSql="INSERT INTO ����������(���,�������,����,��ʶ)VALUES(����������.NextVal," + m_strID + ",'"  + bstrCoodinate + "','" + strFlag + "')";
				}
				m_pCommand->CommandText = bstrTempSql;
				m_pCommand->Execute(NULL,NULL,adCmdText);
			}
		}
		//������Χ���
		for ( vector <_bstr_t>::iterator strSql = strRanges.begin(); strSql != strRanges.end(); strSql++ )
		{
			bstrCoodinate=*strSql;
			bstrTempSql="INSERT INTO ������Χ(�������,����)VALUES("+m_strID+",'" + bstrCoodinate + "')";
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			{
				bstrTempSql="INSERT INTO ������Χ(���,�������,����)VALUES(������Χ.NextVal,"+m_strID+",'" + bstrCoodinate + "')";
			}
			m_pCommand->CommandText = bstrTempSql;
			m_pCommand->Execute(NULL,NULL,adCmdText);
		}
		//�ύ����
		m_pConnection->CommitTrans();
	}// end try
	catch(_com_error e)
	{
		m_pConnection->RollbackTrans();
		return FALSE;
	}
	return TRUE;
}




/************************************************************************/
/*    ɾ������                                                          */
/************************************************************************/
//ɾ������������¼,ǰ����ط���
//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
BOOL CAnalyseDemo::Delete()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	if (m_strID.length()==0)
	{
		return FALSE;
	}
	std::vector<_bstr_t> vbstrSql;
	vbstrSql.push_back( "DELETE FROM ������Χ WHERE �������=" + m_strID);
	vbstrSql.push_back( "DELETE FROM ���������� WHERE �������=" + m_strID);
	vbstrSql.push_back( "DELETE FROM �������ͽ�� WHERE �������=" + m_strID);
	vbstrSql.push_back( "DELETE FROM �������� WHERE ���=" + m_strID);
	return theBllApp.m_pDB->ExcuteTrans( vbstrSql  ,adCmdText );
}

//ɾ������������¼��
//����ʵ��������ͨ�����ݱ�ţ��á���"������
BOOL CAnalyseDemo::Delete(_bstr_t strIDS)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ÷�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	if (strIDS.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫɾ���ķ�����¼��ţ�"),_T("��ʾ"),0);
		return FALSE;
	}
	std::vector<_bstr_t> vbstrSql;
	vbstrSql.push_back( "DELETE FROM ������Χ WHERE ������� in(" + strIDS+")");
	vbstrSql.push_back( "DELETE FROM ���������� WHERE ������� in(" + strIDS+")");
	vbstrSql.push_back( "DELETE FROM �������ͽ�� WHERE ������� in(" + strIDS+")");
	vbstrSql.push_back( "DELETE FROM �������� WHERE ��� in(" + strIDS+")");
	return theBllApp.m_pDB->ExcuteTrans( vbstrSql  ,adCmdText );
}


/************************************************************************/
/* ������ѯ                                                             */
/************************************************************************/
//������ѯ
//�Ի��߰�������ѯ
_RecordsetPtr CAnalyseDemo::QueryCreateDrawLineDemo(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName)
{
	_bstr_t strSqlwhere=GetWhereString(strBeginTime,strEndTime,strCreatorName);
	return LoadAllDrawLineDemo(strSqlwhere);
}
void CAnalyseDemo::QueryCreateDrawLineDemo(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr prst=QueryCreateDrawLineDemo( strBeginTime, strEndTime, strCreatorName );
	if(prst==NULL)
		return;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(prst,vecField,vecRecordSet,lFieldCounts);
}

_RecordsetPtr CAnalyseDemo::QueryCreateFRowLineDemo(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName)
{
	_bstr_t strSqlwhere=GetWhereString(strBeginTime,strEndTime,strCreatorName);
	return LoadAllFRowLineDemo(strSqlwhere);
}
void CAnalyseDemo::QueryCreateFRowLineDemo(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr prst=QueryCreateFRowLineDemo( strBeginTime, strEndTime, strCreatorName );
	if(prst==NULL)
		return;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(prst,vecField,vecRecordSet,lFieldCounts);
}

_RecordsetPtr CAnalyseDemo::QueryCreatePointDemo(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName)
{
	_bstr_t strSqlwhere=GetWhereString(strBeginTime,strEndTime,strCreatorName);
	return LoadAllPointDemo(strSqlwhere);
}
void CAnalyseDemo::QueryCreatePointDemo(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr prst=QueryCreatePointDemo( strBeginTime, strEndTime, strCreatorName );
	if(prst==NULL)
		return;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(prst,vecField,vecRecordSet,lFieldCounts);
}

_RecordsetPtr CAnalyseDemo::QueryCreateRangeDemo(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName)
{
	_bstr_t strSqlwhere=GetWhereString(strBeginTime,strEndTime,strCreatorName);
	return LoadAllRangDemo(strSqlwhere);
}
void CAnalyseDemo::QueryCreateRangeDemo(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr prst=QueryCreateRangeDemo( strBeginTime, strEndTime, strCreatorName );
	if(prst==NULL)
		return;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(prst,vecField,vecRecordSet,lFieldCounts);
}