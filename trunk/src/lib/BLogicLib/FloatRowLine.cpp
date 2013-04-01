//#include "stdafx.h"
#include "FloatRowLine.h"

CFloatRowLine CFloatRowLine::instance;

CFloatRowLine::CFloatRowLine(void)
{
	m_strID="";        
	m_strName="";           
	m_strToTarger="";   
	m_strColor="";
	m_strLineType="1";
	m_strDerection="1";
	m_strWidth="1";
	m_strRemark="";
	m_strCreator="";
	m_strCreateTime="2010-1-1";
}

CFloatRowLine::~CFloatRowLine(void)
{ 
}

CFloatRowLine &CFloatRowLine::Instance()
{
	return instance;
}
//������������Ϣ
BOOL CFloatRowLine::LoadInfo( _bstr_t bstrID)
{
	if (bstrID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ���ص������ߣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_RecordsetPtr  prstInfo = theBllApp.m_pDB->ExcuteSqlRes("select ���,����,����Ŀ��,��ɫ,ʵ��,��ͷ,���,������,����ʱ��,����  from  ������  where ���="+bstrID,adCmdText);
	BOOL bFlag=FALSE;

	if (prstInfo!=NULL)
	{
		if (!prstInfo->adoEOF)
		{
			m_strID = bstrID  ;
			_variant_t var;
			var=(prstInfo->GetCollect("����")) ;
			m_strName = (_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("����Ŀ��")) ;
			m_strToTarger=(_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("��ɫ")) ;
			m_strColor=(_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("ʵ��")) ;
			m_strLineType=(_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("��ͷ")) ;
			m_strDerection=(_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("���")) ;
			m_strWidth=(_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("������")) ;
			m_strCreator = (_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("����ʱ��")) ;
			m_strCreateTime = (_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("����")) ;
			m_strRemark = (_bstr_t)(var.vt==1?"":var);
			bFlag=TRUE;
		}
		prstInfo->Close();
		prstInfo.Release();
	} 
	return bFlag;
}
//���������߽ڵ����ݼ�
_RecordsetPtr CFloatRowLine::LoadNodesRCS( _bstr_t bstrID)
{
	if (bstrID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ���ص������ߣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSqlRes("select ���,����  from  �߽ڵ�  where ������='������' and  �����߱��="+bstrID+"  order by ���",adCmdText);
}
//���������߽ڵ��б�
std::vector<string> CFloatRowLine::LoadNodesVetor( _bstr_t bstrID)
{
	vector<string> coodinates;
	if (bstrID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ���ص������ߣ�"),_T("��ʾ"),0);
		return coodinates;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return coodinates;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�������ҵ���"),_T("��ʾ"),0);
		return coodinates;
	}
	
	_RecordsetPtr prst=LoadNodesRCS(bstrID);
	if (prst!=NULL)
	{
		_variant_t var;
		while(!prst->adoEOF)
		{
			var=prst->GetCollect("����");
			coodinates.push_back(((char *)((_bstr_t)(var.vt==1?"":var))));
			prst->MoveNext();
		}
		prst->Close();
		prst.Release();
	}
	return coodinates;
}

//���������������б�
_RecordsetPtr CFloatRowLine::Loadproperties( _bstr_t bstrID )
{
	if (bstrID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ�������Ե������ߣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSqlRes("select ���,����ʱ��,����ʱ��,��ע  from  ����������  where ���������� = "+bstrID,adCmdText);
}

void CFloatRowLine::Loadproperties(_bstr_t bstrID, std::vector<string> &vecField, std::vector<string> &vecRecordSet, long &lFieldCounts)
{
	if (bstrID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ�������Ե������ߣ�"),_T("��ʾ"),0);
		return;
	}
	_RecordsetPtr res = Loadproperties(bstrID);
	if(res==NULL)
		return;

	CBllHelp::Instance().QueryByCondit(res,vecField,vecRecordSet,lFieldCounts);
}

//���������߼�¼,
//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
BOOL CFloatRowLine::Add()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t bstrSQL;
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case OracleType:
		bstrSQL="insert into ������(���,����,����Ŀ��,��ɫ,ʵ��,��ͷ,���,������,����ʱ��,����) values(����������.NextVal,'" + m_strName + "','" + m_strToTarger + "','" + m_strColor + "',"+m_strLineType+","+m_strDerection+","+m_strWidth+",'" +m_strCreator+"',to_date('" + m_strCreateTime + "','dd/mm/yyyy'),'"+ m_strRemark + "')";
		break;
	case SqlServerType:
		bstrSQL="insert into ������(����,����Ŀ��,��ɫ,ʵ��,��ͷ,���,������,����ʱ��,����) values('" + m_strName + "','" + m_strToTarger + "','" + m_strColor + "',"+m_strLineType+","+m_strDerection+","+m_strWidth+",'"+m_strCreator+"','"+m_strCreateTime+"','" + m_strRemark + "')";
		break;
	case AccessType:
		bstrSQL="insert into ������(����,����Ŀ��,��ɫ,ʵ��,��ͷ,���,������,����ʱ��,����) values('" + m_strName + "','" + m_strToTarger + "','" + m_strColor + "',"+m_strLineType+","+m_strDerection+","+m_strWidth+",'"+m_strCreator+"',#"+m_strCreateTime+"#,'" + m_strRemark + "')";
		break;
	default :
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSql( bstrSQL , adCmdText );
}

int CFloatRowLine::AddGetID()
{
	if (!theBllApp.m_bConntSuccess)
		{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return -1;
		}
	if (!theBllApp.m_pDB->CheckTableNameExist("������"))
		{
		MessageBox(NULL,_T("���ݿ��в����ڸ�������ҵ���"),_T("��ʾ"),0);
		return -1;
		}
	_bstr_t bstrSQL;
	switch(CDatabaseFactory::m_enumDatabaseType)
		{
		case OracleType:
			bstrSQL="insert into ������(���,����,����Ŀ��,��ɫ,ʵ��,��ͷ,���,������,����ʱ��,����) values(����������.NextVal,'" + m_strName + "','" + m_strToTarger + "','" + m_strColor + "',"+m_strLineType+","+m_strDerection+","+m_strWidth+",'" +m_strCreator+"',to_date('" + m_strCreateTime + "','dd/mm/yyyy'),'"+ m_strRemark + "')";
			break;
		case SqlServerType:
			bstrSQL="insert into ������(����,����Ŀ��,��ɫ,ʵ��,��ͷ,���,������,����ʱ��,����) values('" + m_strName + "','" + m_strToTarger + "','" + m_strColor + "',"+m_strLineType+","+m_strDerection+","+m_strWidth+",'"+m_strCreator+"','"+m_strCreateTime+"','" + m_strRemark + "')";
			break;
		case AccessType:
			bstrSQL="insert into ������(����,����Ŀ��,��ɫ,ʵ��,��ͷ,���,������,����ʱ��,����) values('" + m_strName + "','" + m_strToTarger + "','" + m_strColor + "',"+m_strLineType+","+m_strDerection+","+m_strWidth+",'"+m_strCreator+"',#"+m_strCreateTime+"#,'" + m_strRemark + "')";
			break;
		default :
			return -1;
		}

	if (theBllApp.m_pDB->ExcuteSql( bstrSQL , adCmdText ))
		{
		bstrSQL="select max(���) as ����� from ������";
		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			bstrSQL="select ����������.currval as ����� from dual";
		_RecordsetPtr rPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSQL,adCmdText);
		if (rPtr!=NULL&&!rPtr->adoEOF)
			return atoi((char *)((_bstr_t)rPtr->GetCollect("�����")));
		}
	return -1;
}

//�༭�����߼�¼,
//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
BOOL CFloatRowLine::Update()
{
	if (m_strID.length()==0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ�޸������ߣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	
	_bstr_t bstrSQL="UPDATE ������ SET ����='" + m_strName + "',����Ŀ��='" + m_strToTarger +"',��ɫ='"+ m_strColor +"',ʵ��="+ m_strLineType +",��ͷ="+ m_strDerection +",���="+ m_strWidth + ",����='" + m_strRemark + "'  WHERE ���=" + m_strID;
	return theBllApp.m_pDB->ExcuteSql( bstrSQL , adCmdText );
}


//��������߽ڵ�
BOOL CFloatRowLine::ClearLineNodes( _bstr_t bstrIDs )
{
	if (bstrIDs.length()==0)
	{
		MessageBox(NULL,_T("��ѡ������ڵ�������ߣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSql("DELETE FROM �߽ڵ� WHERE ������='������' and  �����߱�� IN ( " + bstrIDs + " )",adCmdText);
}
//�༭�����߼�¼��Ϣ,
//�����������б�
//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
BOOL CFloatRowLine::SaveLineNodes( std::vector<_bstr_t> vbstrCoordinates )
{
	if (m_strID.length()==0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ����ڵ�������ߣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	
	std::vector<_bstr_t> vbstrSql;
	vbstrSql.push_back( "DELETE FROM �߽ڵ� WHERE ������='������' and  �����߱�� =" + m_strID );
	_bstr_t bstrSQL="";
	_bstr_t coodinate="";
	for ( vector<_bstr_t>::iterator item = vbstrCoordinates.begin() ; item != vbstrCoordinates.end() ; item ++ )
	{
		coodinate=((_bstr_t)*item);
		bstrSQL="INSERT INTO �߽ڵ�(�����߱��,������,����) VALUES(" + m_strID + ",'������','" + coodinate + "')";
		if ( CDatabaseFactory::m_enumDatabaseType == OracleType )
		{
			bstrSQL="INSERT INTO �߽ڵ�(���,�����߱��,������,����) VALUES(�߽ڵ�����.NextVal," + m_strID + ",'������','" + coodinate + "')";
		}
		vbstrSql.push_back(bstrSQL);
	}
	return theBllApp.m_pDB->ExcuteTrans(vbstrSql ,adCmdText );
}

//ɾ�������߼�¼��
//ͨ�����ݱ�ţ��á���"������
BOOL CFloatRowLine::Delete(_bstr_t bstrIDS)
{
	if (bstrIDS.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫɾ���������ߣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	std::vector<_bstr_t> vbstrSql;
	vbstrSql.push_back( "DELETE FROM �߽ڵ� WHERE ������='������' and  �����߱�� IN ( " + bstrIDS + " )");
	vbstrSql.push_back( "DELETE FROM ������ WHERE ��� IN ( " + bstrIDS + " )");
	return theBllApp.m_pDB->ExcuteTrans( vbstrSql  ,adCmdText );
}


//��ѯ����������Ŀ���б�
_RecordsetPtr CFloatRowLine::QueryAllLines()
{
	return QueryLinesByCondit("");
}

std::vector<_bstr_t> CFloatRowLine::QueryAllLinesID()
{
	return QueryLinesIDByCondit("");
}

void CFloatRowLine::QueryAllLines(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr prst=QueryAllLines();
	if (prst==NULL)
		return;
	CBllHelp::Instance().QueryByCondit(prst,vecField,vecRecordSet,lFieldCounts);
}
//��ѯ�ص�Ŀ��������
_RecordsetPtr CFloatRowLine::QueryTargetLines(_bstr_t strTarget)
{
	return QueryLinesByCondit(" and ����Ŀ��='"+strTarget+"'");
}
std::vector<_bstr_t> CFloatRowLine::QueryTargetinesID(_bstr_t strTarget)
{
	return QueryLinesIDByCondit(" and ����Ŀ��='"+strTarget+"'");
}
void CFloatRowLine::QueryTargetLines(_bstr_t strTarget,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr prst=QueryTargetLines(strTarget);
	if (prst==NULL)
		return;
	CBllHelp::Instance().QueryByCondit(prst,vecField,vecRecordSet,lFieldCounts);
}

//������ѯ�����߼�¼
_RecordsetPtr  CFloatRowLine::QueryLinesByCondit(_bstr_t bstrWhere)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSqlRes("select ���,����,����Ŀ��,��ɫ,ʵ��,��ͷ,���,������,����ʱ��,����  from  ������ WHERE 1=1 "+bstrWhere,adCmdText);
}
std::vector<_bstr_t> CFloatRowLine::QueryLinesIDByCondit(_bstr_t bstrWhere)
{
	std::vector<_bstr_t> vLineID;
	_RecordsetPtr prst = QueryLinesByCondit(bstrWhere);
	if(prst==NULL)
		return vLineID;
	_variant_t var;
	while(!prst->adoEOF)
	{
		var=(prst->GetCollect("���"));
		vLineID.push_back((_bstr_t)(var.vt==1?"":var));
		prst->MoveNext();
	}
	prst->Close();
	prst.Release();

	return vLineID;
}
void CFloatRowLine::QueryLinesByCondit(_bstr_t bstrWhere,vector<string> &vecField,vector<string> &vecRecordSet, long &lFieldCounts)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return ;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�������ҵ���"),_T("��ʾ"),0);
		return ;
	}
	_RecordsetPtr prst;
	prst=QueryLinesByCondit(bstrWhere);
	if (prst==NULL)
		return;
	CBllHelp::Instance().QueryByCondit(prst,vecField,vecRecordSet,lFieldCounts);
}

//��ѯʱ�������Ч��������
_RecordsetPtr CFloatRowLine::QueryValidateLines(_bstr_t bstrBeginDate,_bstr_t bstrEndDate)
{
	if (bstrBeginDate.length()<=0||bstrEndDate.length()<=0)
	{
		MessageBox(NULL,_T("��������Чʱ������"),_T("��ʾ"),0);
		return FALSE;
	}

	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t bstrSql;
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case AccessType:
		bstrSql="select ������.���,����,����Ŀ��,����ʱ��,����ʱ��  from ������,����������   where  ������.���=����������.���������� and (����ʱ��<=#"+bstrBeginDate+"# and  ����ʱ��>=#"+bstrBeginDate+"#) or(����ʱ��>=#"+bstrBeginDate+"# and  ����ʱ��<=#"+bstrEndDate+"#)  or(����ʱ��<=#"+bstrEndDate+"# and  ����ʱ��>=#"+bstrEndDate+"#)  order by ������.���";
		break;
	case SqlServerType:
		bstrSql="select  ������.���,����,����Ŀ��,����ʱ��,����ʱ��  from ������,����������  where ������.���=����������.���������� and (����ʱ��<='"+bstrBeginDate+"' and  ����ʱ��>='"+bstrBeginDate+"') or(����ʱ��>='"+bstrBeginDate+"' and  ����ʱ��<='"+bstrEndDate+"')  or(����ʱ��<='"+bstrEndDate+"' and  ����ʱ��>='"+bstrEndDate+"')  order by ������.���";
		break;
	case OracleType:
		bstrSql="select  ������.���,����,����Ŀ��,����ʱ��,����ʱ��  from ������,����������  where ������.���=����������.���������� and (����ʱ��<=to_date('" + bstrBeginDate + "','dd/mm/yyyy') and  ����ʱ��>=to_date('" + bstrBeginDate + "','dd/mm/yyyy')) or(����ʱ��>=to_date('" + bstrBeginDate + "','dd/mm/yyyy') and  ����ʱ��<=to_date('" + bstrEndDate + "','dd/mm/yyyy'))  or(����ʱ��<=to_date('" + bstrEndDate + "','dd/mm/yyyy') and  ����ʱ��>=to_date('" + bstrEndDate + "','dd/mm/yyyy'))  order by ������.���";
		break;
	default:
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
}
//��ѯʱ�������Ч��������
void CFloatRowLine::QueryValidateLines( _bstr_t bstrBeginDate,_bstr_t bstrEndDate,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Prst;
	Prst=QueryValidateLines(bstrBeginDate,bstrEndDate);
	if (Prst==NULL)
		return;
	CBllHelp::Instance().QueryByCondit(Prst,vecField,vecRecordSet,lFieldCounts);
}

bool CFloatRowLine::CheckNameExiest(_bstr_t strName)
{
	_bstr_t tempName=strName;
	_RecordsetPtr prst = theBllApp.m_pDB->ExcuteSqlRes("SELECT ���� FROM ������ WHERE ����='"+tempName+"'",adCmdText);
	if (prst!=NULL && !prst->adoEOF)
		return true;
	else
		return false;
}

//������ѯ
_RecordsetPtr CFloatRowLine::QueryCreateLines(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName)
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
		return NULL;
	}
	return QueryLinesByCondit(strSqlwhere);
}
void CFloatRowLine::QueryCreateLines(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr prst=QueryCreateLines( strBeginTime, strEndTime, strCreatorName );
	if(prst==NULL)
		return;
	CBllHelp::Instance().QueryByCondit(prst,vecField,vecRecordSet,lFieldCounts);
}
/************************************************************************/
/* ����������                                                           */
/************************************************************************/
CFRowLineProperty::CFRowLineProperty(void)
{
	m_strID = "";         
	m_strLineID = "";         
	m_strBeginDate = "";         
	m_strEndDate = "";         
	m_strRemark = "";         
}
CFRowLineProperty::~CFRowLineProperty(void)
{

}

//��������:���������Ա��еı��
BOOL CFRowLineProperty::LoadInfo( _bstr_t bstrID )
{
	if (bstrID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��������������ԣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("����������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�����������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_RecordsetPtr  prstInfo = theBllApp.m_pDB->ExcuteSqlRes("select ���,����������,����ʱ��,����ʱ��,��ע  from  ����������  where ���="+bstrID,adCmdText);
	BOOL Bflag=FALSE;

	if (prstInfo!=NULL)
	{
		if(!prstInfo->adoEOF)
		{
			m_strID = bstrID ;
			_variant_t var;
			var=prstInfo->GetCollect("����������") ;
			m_strLineID=(_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("����ʱ��")) ;
			m_strBeginDate=(_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("����ʱ��")) ;
			m_strEndDate=(_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("��ע")) ;
			m_strRemark = (_bstr_t)(var.vt==1?"":var);
			Bflag=TRUE;
		}
		prstInfo->Close();
		prstInfo.Release();
	} 
	return Bflag;
}
//�������������¼��ĳ�ͻ
//������bstrID���޸���bstrIDΪ���������Ա�ţ������Ϊ����
//		bstrLineidΪ�����߱��
BOOL CFRowLineProperty::CheckLnPrptyColn(_bstr_t bstrID, _bstr_t bstrLineid,_bstr_t bstrBeginDate,_bstr_t bstrEndDate)
{
	_bstr_t bstrSql="";
	if (bstrID.length()==0)
	{
		switch(CDatabaseFactory::m_enumDatabaseType)
		{
		case AccessType:
			bstrSql="select *  from  ����������   where  ����������=" + bstrLineid + "  and  (����ʱ��<=#"+bstrBeginDate+"# and  ����ʱ��>=#"+bstrBeginDate+"#) or (����ʱ��>=#"+bstrBeginDate+"#  and  ����ʱ��<=#"+bstrEndDate+"#)  or (����ʱ��<=#"+bstrEndDate+"#  and  ����ʱ��>=#"+bstrEndDate+"#)";
			break;
		case SqlServerType:
			bstrSql="select  *  from  ����������  where  ����������=" + bstrLineid + "  and  (����ʱ��<='"+bstrBeginDate+"' and  ����ʱ��>='"+bstrBeginDate+"') or (����ʱ��>='"+bstrBeginDate+"' and  ����ʱ��<='"+bstrEndDate+"')  or (����ʱ��<='"+bstrEndDate+"' and  ����ʱ��>='"+bstrEndDate+"')";
			break;
		case OracleType:
			bstrSql="select  *  from  ����������  where  ����������=" + bstrLineid + "  and  (����ʱ��<=to_date('" + bstrBeginDate + "','dd/mm/yyyy')  and  ����ʱ��>=to_date('" + bstrBeginDate + "','dd/mm/yyyy')) or (����ʱ��>=to_date('" + bstrBeginDate + "','dd/mm/yyyy') and  ����ʱ��<=to_date('" + bstrEndDate + "','dd/mm/yyyy'))  or (����ʱ��<=to_date('" + bstrEndDate + "','dd/mm/yyyy') and  ����ʱ��>=to_date('" + bstrEndDate + "','dd/mm/yyyy'))";
			break;
		default:
			return FALSE;
		}
	}
	else
	{
		switch(CDatabaseFactory::m_enumDatabaseType)
		{
		case AccessType:
			bstrSql="select *  from  ����������   where  ����������=" + bstrLineid + "  and  ���<>"+bstrID+"   and  ((����ʱ��<=#"+bstrBeginDate+"# and  ����ʱ��>=#"+bstrBeginDate+"#) or(����ʱ��>=#"+bstrBeginDate+"# and  ����ʱ��<=#"+bstrEndDate+"#)  or(����ʱ��<=#"+bstrEndDate+"# and  ����ʱ��>=#"+bstrEndDate+"#))";
			break;
		case SqlServerType:
			bstrSql="select  *  from  ����������  where  ����������=" + bstrLineid + "  and  ���<>"+bstrID+"   and  ((����ʱ��<='"+bstrBeginDate+"' and  ����ʱ��>='"+bstrBeginDate+"') or(����ʱ��>='"+bstrBeginDate+"' and  ����ʱ��<='"+bstrEndDate+"')  or(����ʱ��<='"+bstrEndDate+"' and  ����ʱ��>='"+bstrEndDate+"'))";
			break;
		case OracleType:
			bstrSql="select  *  from  ����������  where  ����������=" + bstrLineid + "  and  ���<>"+bstrID+"   and  ((����ʱ��<=to_date('" + bstrBeginDate + "','dd/mm/yyyy')  and  ����ʱ��>=to_date('" + bstrBeginDate + "','dd/mm/yyyy')) or (����ʱ��>=to_date('" + bstrBeginDate + "','dd/mm/yyyy') and  ����ʱ��<=to_date('" + bstrEndDate + "','dd/mm/yyyy'))  or (����ʱ��<=to_date('" + bstrEndDate + "','dd/mm/yyyy') and  ����ʱ��>=to_date('" + bstrEndDate + "','dd/mm/yyyy')))";
			break;
		default:
			return FALSE;
		}
	}
	_RecordsetPtr rst=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (rst!=NULL&& !rst->adoEOF)
	{
		return TRUE;
	}
	else 
		return FALSE;
	
}
//�������������Լ�¼,
//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
BOOL CFRowLineProperty::Add()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("����������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�����������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	if (CheckLnPrptyColn("",m_strLineID,m_strBeginDate,m_strEndDate))
	{
		MessageBox(NULL,_T("ͬ������ͬʱ���ڲ������ö��Σ�"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t bstrSQL="insert into ����������(����������,����ʱ��,����ʱ��,��ע) values(" + m_strLineID + ",'" + m_strBeginDate + "','" + m_strEndDate + "','" + m_strRemark + "')";
	if ( CDatabaseFactory::m_enumDatabaseType == OracleType )
	{
		bstrSQL="insert into ����������(���,����������,����ʱ��,����ʱ��,��ע) values(��������������.NextVal," + m_strLineID + ",to_date('" + m_strBeginDate + "','dd/mm/yyyy'),to_date('" + m_strEndDate + "','dd/mm/yyyy'),'" + m_strRemark + "')";
	}
	return theBllApp.m_pDB->ExcuteSql( bstrSQL , adCmdText );
}
//�༭���������Լ�¼,����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
BOOL CFRowLineProperty::Update()
{
	if ( m_strID.length() == 0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ�������������ԣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("����������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�����������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	
	if (CheckLnPrptyColn(m_strID,m_strLineID,m_strBeginDate,m_strEndDate))
	{
		MessageBox(NULL,_T("�޸�ʱ���ͻ��"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t bstrSQL;
	bstrSQL="UPDATE  ����������  SET  ����������=" + m_strLineID + ",����ʱ��='" + m_strBeginDate +"',����ʱ��='"+ m_strEndDate + "',��ע='" + m_strRemark + "' WHERE ���=" +m_strID;
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
	{
		bstrSQL="UPDATE  ����������  SET  ����������=" + m_strLineID + ",����ʱ��=to_date('" + m_strBeginDate + "','dd/mm/yyyy'),����ʱ��=to_date('" + m_strEndDate + "','dd/mm/yyyy'),��ע='" + m_strRemark + "'  WHERE ���=" +m_strID;
	}
	return theBllApp.m_pDB->ExcuteSql( bstrSQL , adCmdText );
}
//ɾ�����������Լ�¼��ͨ�����ݱ�ţ��á���"������
BOOL CFRowLineProperty::Delete(_bstr_t bstrIDS)
{
	if (bstrIDS.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫɾ�����������ԣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("����������"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�����������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSql("DELETE FROM ���������� WHERE ��� IN ( " + bstrIDS + " )",adCmdText);
}
