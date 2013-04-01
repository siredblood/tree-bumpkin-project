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

//加载航线信息。
//参数：航线编号
BOOL CDrawTrackLine::LoadInfo( CString bstrGUID)
{
	if (bstrGUID.GetLength()==0)
	{
		return FALSE;
	}
	_bstr_t myguid=bstrGUID.GetBuffer(0);
	_RecordsetPtr  prstInfo = theBllApp.m_pDB->ExcuteSqlRes("select [GUID],[名称],[速度],[备注]  from  [航线]  where [GUID]='"+ myguid +"'",adCmdText);
	if (prstInfo!=NULL && !prstInfo->adoEOF)
	{
		m_strGUID = bstrGUID  ;
		m_strName = (CString)(prstInfo->GetCollect("名称")) ;
		m_strSpeed = (double)(prstInfo->GetCollect("速度")) ;
		m_strRemark = (CString)(prstInfo->GetCollect("备注")) ;

		prstInfo->Close();
		prstInfo.Release();
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
}


//加载航线节点记录集。
//参数：航线编号
_RecordsetPtr CDrawTrackLine::LoadNodesRCS( CString bstrGUID )
{
	if (bstrGUID.GetLength()==0)
	{
		return FALSE;
	}
	_bstr_t myguid=bstrGUID.GetBuffer(0);
	return theBllApp.m_pDB->ExcuteSqlRes("select [GUID],[坐标]  from  [节点]  where [GUID]='"+ myguid +"'",adCmdText);
}
//加载航线节点列表
//参数：航线编号
void CDrawTrackLine::LoadNodesVetors( CString bstrGUID ,std::vector<CString> &coodinates)
{
	if (bstrGUID.GetLength()==0)
	{
		return;
	}
	_RecordsetPtr prst=LoadNodesRCS(bstrGUID);

	while(!prst->adoEOF)
	{
		coodinates.push_back((CString)(prst->GetCollect("坐标")));
		prst->MoveNext();
	}
	prst->Close();
	prst.Release();
}

//增加航线记录,
//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
BOOL CDrawTrackLine::Add()
{
	if (m_strGUID.GetLength()==0||m_strName.GetLength()==0)
	{
		return FALSE;
	}

	CString strspeed;
	strspeed.Format("%f",m_strSpeed);

	_bstr_t bstrSQL="INSERT INTO 航线([GUID],[名称],[速度],[备注])VALUES('"+m_strGUID+"','"+m_strName+"',"+ strspeed +",'"+m_strRemark+"')";
	return theBllApp.m_pDB->ExcuteSql( bstrSQL , adCmdText );
}
//编辑航线记录信息,
//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
BOOL CDrawTrackLine::UpdateLineInfo()
{
	if (m_strGUID.GetLength()==0||m_strName.GetLength()==0)
	{
		return FALSE;
	}

	CString strspeed;
	strspeed.Format("%f",m_strSpeed);
	_bstr_t bstrSQL="UPDATE  航线  SET [名称] ='"+m_strName+"',[速度] = "+strspeed+",[备注] ='"+m_strRemark+"'  WHERE GUID='"+m_strGUID+"' ";
	return theBllApp.m_pDB->ExcuteSql( bstrSQL , adCmdText );
}
//清除航线节点:参数：航线编号
BOOL CDrawTrackLine::ClearLineNodes(CString strGUID)
{
	if (strGUID.GetLength()==0)
	{
		return FALSE;
	}
	_bstr_t myguid=strGUID.GetBuffer(0);
	return theBllApp.m_pDB->ExcuteSql("DELETE FROM 节点 WHERE GUID='"+ myguid +"'",adCmdText);
}

//编辑航线记录信息,
//参数：坐标列表
//首先实例化一个对象最后调用这个函数
BOOL CDrawTrackLine::SaveLineNodes( std::vector<CString> vbstrCoordinates ,CString strGUID)
{
	if (strGUID.GetLength()==0)
		return FALSE;
	std::vector<_bstr_t> vbstrSql;
	_bstr_t myguid=strGUID.GetBuffer(0);
	vbstrSql.push_back( "DELETE FROM [节点] WHERE  [GUID]='"+ myguid + "'");
	
	_bstr_t bstrSQL="" , coodinate="";

	for ( std::vector<CString>::iterator item = vbstrCoordinates.begin() ; item != vbstrCoordinates.end() ; item ++ )
	{
		coodinate=((CString)*item);
		bstrSQL="INSERT INTO [节点] ([GUID],[坐标]) VALUES('" + myguid + " ','" + coodinate + "')";
		vbstrSql.push_back(bstrSQL);
	}
	return theBllApp.m_pDB->ExcuteTrans(vbstrSql ,adCmdText );
}
//删除航线记录，
//参数：航线编号
BOOL CDrawTrackLine::Delete(CString strGUID)
{
	if (strGUID.GetLength()==0)
		return FALSE;
	std::vector<_bstr_t> vbstrSql;
	_bstr_t myguid=strGUID.GetBuffer(0) ;
	vbstrSql.push_back( "DELETE FROM 节点 WHERE GUID='" + myguid + " '");
	vbstrSql.push_back( "DELETE FROM 航线 WHERE GUID='" + myguid + " '");
	return theBllApp.m_pDB->ExcuteTrans( vbstrSql  ,adCmdText );
}

//查询所有航线列表
_RecordsetPtr CDrawTrackLine::QueryAllLines()
{
	return theBllApp.m_pDB->ExcuteSqlRes("select GUID,名称,速度,备注  FROM  航线 ",adCmdText);
}
//查询所有航线列表,返回绑定列表使用
void CDrawTrackLine::QueryAllLines(std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts)
{
	CBllHelp *help = new CBllHelp();
	help->QueryByCondit(QueryAllLines(),vecField,vecRecordSet,lFieldCounts);
}
//条件查询航线记录：参数：查询条件
_RecordsetPtr  CDrawTrackLine::QueryLinesByCondit(CString bstrWhere)
{
	_bstr_t myguid=bstrWhere.GetBuffer(0);
	return theBllApp.m_pDB->ExcuteSqlRes("select select GUID,名称,速度,备注  FROM  航线  WHERE 1=1 " + myguid,adCmdText);
}
//条件查询航线记录：参数：查询条件，返回绑定列表使用
void CDrawTrackLine::QueryLinesByCondit(CString bstrWhere, std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts)
{
	CBllHelp *help = new CBllHelp();
	help->QueryByCondit(QueryLinesByCondit(bstrWhere),vecField,vecRecordSet,lFieldCounts);
}
//加载场景时加载所有航线
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
		lines.Name= (CString)(pRecordSet->GetCollect("名称")) ;
		lines.Speed = (double)(pRecordSet->GetCollect("速度")) ;
		lines.Remark = (CString)(pRecordSet->GetCollect("备注")) ;
		LoadNodesVetors(strGuid,lines.coodinates);
		pRecordSet->MoveNext();
	}
	return vlines;
}
