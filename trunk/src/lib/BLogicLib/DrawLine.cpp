#include "DrawLine.h"


CDrawLine::CDrawLine(void)
{
	m_strID="";
	m_strColor="";
	m_strName="";
	m_strRemark="";
	m_strCreator="";
	m_strCreateTime="2010-1-1";
}

CDrawLine::~CDrawLine(void)
{
}

//�����Ի�����Ϣ��
//�������Ի��߱��
BOOL CDrawLine::LoadInfo( _bstr_t bstrID)
{
	if (bstrID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ�����Ի��߱�ţ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�Ի���"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ��Ի���ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_RecordsetPtr  prstInfo = theBllApp.m_pDB->ExcuteSqlRes("select ���,����,��ɫ,������,����ʱ��,����  from  �Ի���  where ���="+bstrID,adCmdText);
	BOOL BRst=FALSE;
	if (prstInfo!=NULL)
	{
		if (!prstInfo->adoEOF)
		{
			BRst=TRUE;
			_variant_t var;
			m_strID = bstrID  ;
			var=(prstInfo->GetCollect("����")) ;
			m_strName = (_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("��ɫ")) ;
			m_strColor = (_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("������")) ;
			m_strCreator = (_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("����ʱ��")) ;
			m_strCreateTime = (_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("����")) ;
			m_strRemark = (_bstr_t)(var.vt==1?"":var);
		}
		prstInfo->Close();
		prstInfo.Release();
	} 
	return BRst;
}


//�����Ի��߽ڵ��¼����
//�������Ի��߱��
_RecordsetPtr CDrawLine::LoadNodesRCS( _bstr_t bstrID )
{
	if (bstrID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ�����Ի��߱�ţ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�߽ڵ�"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ��߽ڵ�ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSqlRes("select ���,����  from  �߽ڵ�  where ������='�Ի���' and  �����߱��="+bstrID,adCmdText);
}
//�����Ի��߽ڵ��б�
//�������Ի��߱��
std::vector<_bstr_t> CDrawLine::LoadNodesVetors( _bstr_t bstrID )
{
	vector<_bstr_t> coodinates;
	_RecordsetPtr prst=LoadNodesRCS(bstrID);
	if (prst!=NULL)
	{
		while(!prst->adoEOF)
		{
			coodinates.push_back((_bstr_t)(prst->GetCollect("����")));
			prst->MoveNext();
		}
		prst->Close();
		prst.Release();
	}
	return coodinates;
}

//�����Ի��߼�¼,
//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
BOOL CDrawLine::Add()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�Ի���"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ��Ի���ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t bstrSQL;
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case OracleType:
		bstrSQL="insert into �Ի���(���,����,��ɫ,������,����ʱ��,����) values(�Ի�������.NextVal,'" + m_strName + "','" + m_strColor + "','" +m_strCreator+"',to_date('" + m_strCreateTime + "','dd/mm/yyyy'),'"+ m_strRemark + "')";
		break;
	case SqlServerType:
		bstrSQL="insert into �Ի���(����,��ɫ,������,����ʱ��,����) values('" + m_strName + "','" + m_strColor + "','"+m_strCreator+"','"+m_strCreateTime+"','" + m_strRemark + "')";
		break;
	case AccessType:
		bstrSQL="insert into �Ի���(����,��ɫ,������,����ʱ��,����) values('" + m_strName + "','" + m_strColor + "','"+m_strCreator+"',#"+m_strCreateTime+"#,'" + m_strRemark + "')";
		break;
	default:
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSql( bstrSQL , adCmdText );
}
//�༭�Ի��߼�¼��Ϣ,
//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
BOOL CDrawLine::UpdateLineInfo()
{
	if (m_strID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ�����Ի��߱�ţ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�Ի���"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ��Ի���ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t bstrSQL="UPDATE �Ի��� SET ����='" + m_strName + "',��ɫ='" + m_strColor  + "',����='" + m_strRemark + "' WHERE ���=" + m_strID;
	return theBllApp.m_pDB->ExcuteSql( bstrSQL , adCmdText );
}
//����Ի��߽ڵ�:�������Ի��߱�ţ�����ö��Ÿ���
BOOL CDrawLine::ClearLineNodes( _bstr_t bstrIDs )
{
	if (bstrIDs.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ����ڵ���Ի��߱�ţ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�߽ڵ�"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ��߽ڵ�ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSql("DELETE FROM �߽ڵ� WHERE ������='�Ի���' and  �����߱�� IN ( " + bstrIDs + " )",adCmdText);
}

//�༭�Ի��߼�¼��Ϣ,
//�����������б�
//����ʵ����һ�������٣��������������
BOOL CDrawLine::SaveLineNodes( std::vector<_bstr_t> vbstrCoordinates )
{
	if (m_strID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ�񱣴�ڵ���Ի��߱�ţ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�߽ڵ�"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ��߽ڵ�ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}

	std::vector<_bstr_t> vbstrSql;
	vbstrSql.push_back( "DELETE FROM �߽ڵ� WHERE ������='�Ի���' and  �����߱��=" + m_strID);
	_bstr_t bstrSQL="";
	_bstr_t coodinate="";
	for ( vector<_bstr_t>::iterator item = vbstrCoordinates.begin() ; item != vbstrCoordinates.end() ; item ++ )
	{
		coodinate=((_bstr_t)*item);
		bstrSQL="INSERT INTO �߽ڵ�(�����߱��,������,����) VALUES(" + m_strID + ",'�Ի���','" + coodinate + "')";
		if ( CDatabaseFactory::m_enumDatabaseType == OracleType )
		{
			bstrSQL="INSERT INTO �߽ڵ�(���,�����߱��,������,����) VALUES(�߽ڵ�����.NextVal," + m_strID + ",'�Ի���','" + coodinate + "')";
		}
		vbstrSql.push_back(bstrSQL);
	}
	return theBllApp.m_pDB->ExcuteTrans(vbstrSql ,adCmdText );
}
//ɾ���Ի��߼�¼��
//ͨ�����ݱ�ţ��á���"�������������Ի��߱��
BOOL CDrawLine::Delete(_bstr_t bstrIDS)
{
	if (bstrIDS.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫɾ���Ի��߱�ţ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�Ի���"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ��Ի���ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	std::vector<_bstr_t> vbstrSql;
	vbstrSql.push_back( "DELETE FROM �߽ڵ� WHERE ������='�Ի���' and  �����߱�� IN ( " + bstrIDS + " )");
	vbstrSql.push_back( "DELETE FROM �Ի��� WHERE ��� IN ( " + bstrIDS + " )");
	return theBllApp.m_pDB->ExcuteTrans( vbstrSql  ,adCmdText );
}

//��ѯ�����Ի����б�
_RecordsetPtr CDrawLine::QueryAllLines()
{
	return QueryLinesByCondit("");
}

void CDrawLine::QueryAllLines(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryAllLines();
	if (Rcst ==NULL)
		return;
	CBllHelp *help = new CBllHelp();
	help->QueryByCondit( Rcst , vecField , vecRecordSet , lFieldCounts );
}
//������ѯ�Ի��߼�¼����������ѯ����
_RecordsetPtr  CDrawLine::QueryLinesByCondit(_bstr_t bstrWhere)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�Ի���"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ��Ի���ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSqlRes("select ���,����,��ɫ,������,����ʱ��,����  from  �Ի��� WHERE 1=1 " + bstrWhere,adCmdText);
}

void CDrawLine::QueryLinesByCondit(_bstr_t bstrWhere, vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryLinesByCondit(bstrWhere);
	if ( Rcst ==NULL )
		return;
	CBllHelp *help = new CBllHelp();
	help->QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
}
//������ѯ
_RecordsetPtr  CDrawLine::QueryCreateLines(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName)
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
void CDrawLine::QueryCreateLines(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName, vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr prst=QueryCreateLines( strBeginTime, strEndTime, strCreatorName );
	if(prst==NULL)
		return;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(prst,vecField,vecRecordSet,lFieldCounts);
}
