//#include "pch.hpp"
#include "DrawTrackLine.h"

CDrawTrackLine::CDrawTrackLine(void)
{
	m_strGUID="";
	m_strSpeed=0;
	m_strName="";
	m_strRemark="";
}

CDrawTrackLine::~CDrawTrackLine(void)
{
}

//���غ�����Ϣ��
//���������߱��
BOOL CDrawTrackLine::LoadInfo( CString bstrGUID)
{
	if (bstrGUID.GetLength()==0)
	{
		return FALSE;
	}
	_bstr_t myguid=bstrGUID.GetBuffer(0);
	_RecordsetPtr  prstInfo = theBllApp.m_pDB->ExcuteSqlRes("select [GUID],[����],[�ٶ�],[��ע]  from  [����]  where [GUID]='"+ myguid +"'",adCmdText);
	if (prstInfo!=NULL && !prstInfo->adoEOF)
	{
		m_strGUID = bstrGUID  ;
		m_strName = (CString)(prstInfo->GetCollect("����")) ;
		m_strSpeed = (double)(prstInfo->GetCollect("�ٶ�")) ;
		m_strRemark = (CString)(prstInfo->GetCollect("��ע")) ;

		prstInfo->Close();
		prstInfo.Release();
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
}


//���غ��߽ڵ��¼����
//���������߱��
_RecordsetPtr CDrawTrackLine::LoadNodesRCS( CString bstrGUID )
{
	if (bstrGUID.GetLength()==0)
	{
		return FALSE;
	}
	_bstr_t myguid=bstrGUID.GetBuffer(0);
	return theBllApp.m_pDB->ExcuteSqlRes("select [GUID],[����]  from  [�ڵ�]  where [GUID]='"+ myguid +"'",adCmdText);
}
//���غ��߽ڵ��б�
//���������߱��
void CDrawTrackLine::LoadNodesVetors( CString bstrGUID ,std::vector<CString> &coodinates)
{
	if (bstrGUID.GetLength()==0)
	{
		return;
	}
	_RecordsetPtr prst=LoadNodesRCS(bstrGUID);

	while(!prst->adoEOF)
	{
		coodinates.push_back((CString)(prst->GetCollect("����")));
		prst->MoveNext();
	}
	prst->Close();
	prst.Release();
}

//���Ӻ��߼�¼,
//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
BOOL CDrawTrackLine::Add()
{
	if (m_strGUID.GetLength()==0||m_strName.GetLength()==0)
	{
		return FALSE;
	}

	CString strspeed;
	strspeed.Format("%f",m_strSpeed);

	_bstr_t bstrSQL="INSERT INTO ����([GUID],[����],[�ٶ�],[��ע])VALUES('"+m_strGUID+"','"+m_strName+"',"+ strspeed +",'"+m_strRemark+"')";
	return theBllApp.m_pDB->ExcuteSql( bstrSQL , adCmdText );
}
//�༭���߼�¼��Ϣ,
//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
BOOL CDrawTrackLine::UpdateLineInfo()
{
	if (m_strGUID.GetLength()==0||m_strName.GetLength()==0)
	{
		return FALSE;
	}

	CString strspeed;
	strspeed.Format("%f",m_strSpeed);
	_bstr_t bstrSQL="UPDATE  ����  SET [����] ='"+m_strName+"',[�ٶ�] = "+strspeed+",[��ע] ='"+m_strRemark+"'  WHERE GUID='"+m_strGUID+"' ";
	return theBllApp.m_pDB->ExcuteSql( bstrSQL , adCmdText );
}
//������߽ڵ�:���������߱��
BOOL CDrawTrackLine::ClearLineNodes(CString strGUID)
{
	if (strGUID.GetLength()==0)
	{
		return FALSE;
	}
	_bstr_t myguid=strGUID.GetBuffer(0);
	return theBllApp.m_pDB->ExcuteSql("DELETE FROM �ڵ� WHERE GUID='"+ myguid +"'",adCmdText);
}

//�༭���߼�¼��Ϣ,
//�����������б�
//����ʵ����һ�������������������
BOOL CDrawTrackLine::SaveLineNodes( std::vector<CString> vbstrCoordinates ,CString strGUID)
{
	if (strGUID.GetLength()==0)
		return FALSE;
	std::vector<_bstr_t> vbstrSql;
	_bstr_t myguid=strGUID.GetBuffer(0);
	vbstrSql.push_back( "DELETE FROM [�ڵ�] WHERE  [GUID]='"+ myguid + "'");
	
	_bstr_t bstrSQL="" , coodinate="";

	for ( std::vector<CString>::iterator item = vbstrCoordinates.begin() ; item != vbstrCoordinates.end() ; item ++ )
	{
		coodinate=((CString)*item);
		bstrSQL="INSERT INTO [�ڵ�] ([GUID],[����]) VALUES('" + myguid + " ','" + coodinate + "')";
		vbstrSql.push_back(bstrSQL);
	}
	return theBllApp.m_pDB->ExcuteTrans(vbstrSql ,adCmdText );
}
//ɾ�����߼�¼��
//���������߱��
BOOL CDrawTrackLine::Delete(CString strGUID)
{
	if (strGUID.GetLength()==0)
		return FALSE;
	std::vector<_bstr_t> vbstrSql;
	_bstr_t myguid=strGUID.GetBuffer(0) ;
	vbstrSql.push_back( "DELETE FROM �ڵ� WHERE GUID='" + myguid + " '");
	vbstrSql.push_back( "DELETE FROM ���� WHERE GUID='" + myguid + " '");
	return theBllApp.m_pDB->ExcuteTrans( vbstrSql  ,adCmdText );
}

//��ѯ���к����б�
_RecordsetPtr CDrawTrackLine::QueryAllLines()
{
	return theBllApp.m_pDB->ExcuteSqlRes("select GUID,����,�ٶ�,��ע  FROM  ���� ",adCmdText);
}
//��ѯ���к����б�,���ذ��б�ʹ��
void CDrawTrackLine::QueryAllLines(std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts)
{
	CBllHelp *help = new CBllHelp();
	help->QueryByCondit(QueryAllLines(),vecField,vecRecordSet,lFieldCounts);
}
//������ѯ���߼�¼����������ѯ����
_RecordsetPtr  CDrawTrackLine::QueryLinesByCondit(CString bstrWhere)
{
	_bstr_t myguid=bstrWhere.GetBuffer(0);
	return theBllApp.m_pDB->ExcuteSqlRes("select select GUID,����,�ٶ�,��ע  FROM  ����  WHERE 1=1 " + myguid,adCmdText);
}
//������ѯ���߼�¼����������ѯ���������ذ��б�ʹ��
void CDrawTrackLine::QueryLinesByCondit(CString bstrWhere, std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts)
{
	CBllHelp *help = new CBllHelp();
	help->QueryByCondit(QueryLinesByCondit(bstrWhere),vecField,vecRecordSet,lFieldCounts);
}
//���س���ʱ�������к���
std::vector<DRAWLINESTRUCT> CDrawTrackLine::QueryDrawLineForLoad( CString  bstrWhere)
{
	std::vector<DRAWLINESTRUCT> vlines;

	_RecordsetPtr pRecordSet;
	pRecordSet = QueryLinesByCondit(bstrWhere);
	while(!pRecordSet->adoEOF)
	{
		DRAWLINESTRUCT lines;
		CString strGuid=(CString)(pRecordSet->GetCollect("GUID")) ;
		lines.GUID = strGuid;
		lines.Name= (CString)(pRecordSet->GetCollect("����")) ;
		lines.Speed = (double)(pRecordSet->GetCollect("�ٶ�")) ;
		lines.Remark = (CString)(pRecordSet->GetCollect("��ע")) ;
		LoadNodesVetors(strGuid,lines.coodinates);
		pRecordSet->MoveNext();
	}
	return vlines;
}
