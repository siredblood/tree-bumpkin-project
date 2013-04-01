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

//加载自画线信息。
//参数：自画线编号
BOOL CDrawLine::LoadInfo( _bstr_t bstrID)
{
	if (bstrID.length()<=0)
	{
		MessageBox(NULL,_T("请选择要加载自画线编号！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("自画线"))
	{
		MessageBox(NULL,_T("数据库中不存在该自画线业务表！"),_T("提示"),0);
		return FALSE;
	}
	_RecordsetPtr  prstInfo = theBllApp.m_pDB->ExcuteSqlRes("select 编号,名称,颜色,创建人,创建时间,描述  from  自画线  where 编号="+bstrID,adCmdText);
	BOOL BRst=FALSE;
	if (prstInfo!=NULL)
	{
		if (!prstInfo->adoEOF)
		{
			BRst=TRUE;
			_variant_t var;
			m_strID = bstrID  ;
			var=(prstInfo->GetCollect("名称")) ;
			m_strName = (_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("颜色")) ;
			m_strColor = (_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("创建人")) ;
			m_strCreator = (_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("创建时间")) ;
			m_strCreateTime = (_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("描述")) ;
			m_strRemark = (_bstr_t)(var.vt==1?"":var);
		}
		prstInfo->Close();
		prstInfo.Release();
	} 
	return BRst;
}


//加载自画线节点记录集。
//参数：自画线编号
_RecordsetPtr CDrawLine::LoadNodesRCS( _bstr_t bstrID )
{
	if (bstrID.length()<=0)
	{
		MessageBox(NULL,_T("请选择要加载自画线编号！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("线节点"))
	{
		MessageBox(NULL,_T("数据库中不存在该线节点业务表！"),_T("提示"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSqlRes("select 编号,坐标  from  线节点  where 线类型='自画线' and  所属线编号="+bstrID,adCmdText);
}
//加载自画线节点列表
//参数：自画线编号
std::vector<_bstr_t> CDrawLine::LoadNodesVetors( _bstr_t bstrID )
{
	vector<_bstr_t> coodinates;
	_RecordsetPtr prst=LoadNodesRCS(bstrID);
	if (prst!=NULL)
	{
		while(!prst->adoEOF)
		{
			coodinates.push_back((_bstr_t)(prst->GetCollect("坐标")));
			prst->MoveNext();
		}
		prst->Close();
		prst.Release();
	}
	return coodinates;
}

//增加自画线记录,
//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
BOOL CDrawLine::Add()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("自画线"))
	{
		MessageBox(NULL,_T("数据库中不存在该自画线业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t bstrSQL;
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case OracleType:
		bstrSQL="insert into 自画线(编号,名称,颜色,创建人,创建时间,描述) values(自画线序列.NextVal,'" + m_strName + "','" + m_strColor + "','" +m_strCreator+"',to_date('" + m_strCreateTime + "','dd/mm/yyyy'),'"+ m_strRemark + "')";
		break;
	case SqlServerType:
		bstrSQL="insert into 自画线(名称,颜色,创建人,创建时间,描述) values('" + m_strName + "','" + m_strColor + "','"+m_strCreator+"','"+m_strCreateTime+"','" + m_strRemark + "')";
		break;
	case AccessType:
		bstrSQL="insert into 自画线(名称,颜色,创建人,创建时间,描述) values('" + m_strName + "','" + m_strColor + "','"+m_strCreator+"',#"+m_strCreateTime+"#,'" + m_strRemark + "')";
		break;
	default:
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSql( bstrSQL , adCmdText );
}
//编辑自画线记录信息,
//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
BOOL CDrawLine::UpdateLineInfo()
{
	if (m_strID.length()<=0)
	{
		MessageBox(NULL,_T("请选择要更新自画线编号！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("自画线"))
	{
		MessageBox(NULL,_T("数据库中不存在该自画线业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t bstrSQL="UPDATE 自画线 SET 名称='" + m_strName + "',颜色='" + m_strColor  + "',描述='" + m_strRemark + "' WHERE 编号=" + m_strID;
	return theBllApp.m_pDB->ExcuteSql( bstrSQL , adCmdText );
}
//清除自画线节点:参数：自画线编号，多个用逗号隔开
BOOL CDrawLine::ClearLineNodes( _bstr_t bstrIDs )
{
	if (bstrIDs.length()<=0)
	{
		MessageBox(NULL,_T("请选择要清除节点的自画线编号！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("线节点"))
	{
		MessageBox(NULL,_T("数据库中不存在该线节点业务表！"),_T("提示"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSql("DELETE FROM 线节点 WHERE 线类型='自画线' and  所属线编号 IN ( " + bstrIDs + " )",adCmdText);
}

//编辑自画线记录信息,
//参数：坐标列表
//首先实例化一个对象再，最后调用这个函数
BOOL CDrawLine::SaveLineNodes( std::vector<_bstr_t> vbstrCoordinates )
{
	if (m_strID.length()<=0)
	{
		MessageBox(NULL,_T("请选择保存节点的自画线编号！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("线节点"))
	{
		MessageBox(NULL,_T("数据库中不存在该线节点业务表！"),_T("提示"),0);
		return FALSE;
	}

	std::vector<_bstr_t> vbstrSql;
	vbstrSql.push_back( "DELETE FROM 线节点 WHERE 线类型='自画线' and  所属线编号=" + m_strID);
	_bstr_t bstrSQL="";
	_bstr_t coodinate="";
	for ( vector<_bstr_t>::iterator item = vbstrCoordinates.begin() ; item != vbstrCoordinates.end() ; item ++ )
	{
		coodinate=((_bstr_t)*item);
		bstrSQL="INSERT INTO 线节点(所属线编号,线类型,坐标) VALUES(" + m_strID + ",'自画线','" + coodinate + "')";
		if ( CDatabaseFactory::m_enumDatabaseType == OracleType )
		{
			bstrSQL="INSERT INTO 线节点(编号,所属线编号,线类型,坐标) VALUES(线节点序列.NextVal," + m_strID + ",'自画线','" + coodinate + "')";
		}
		vbstrSql.push_back(bstrSQL);
	}
	return theBllApp.m_pDB->ExcuteTrans(vbstrSql ,adCmdText );
}
//删除自画线记录，
//通过传递编号（用“，"隔开）：参数自画线编号
BOOL CDrawLine::Delete(_bstr_t bstrIDS)
{
	if (bstrIDS.length()<=0)
	{
		MessageBox(NULL,_T("请选择要删除自画线编号！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("自画线"))
	{
		MessageBox(NULL,_T("数据库中不存在该自画线业务表！"),_T("提示"),0);
		return FALSE;
	}
	std::vector<_bstr_t> vbstrSql;
	vbstrSql.push_back( "DELETE FROM 线节点 WHERE 线类型='自画线' and  所属线编号 IN ( " + bstrIDS + " )");
	vbstrSql.push_back( "DELETE FROM 自画线 WHERE 编号 IN ( " + bstrIDS + " )");
	return theBllApp.m_pDB->ExcuteTrans( vbstrSql  ,adCmdText );
}

//查询所有自画线列表
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
//条件查询自画线记录：参数：查询条件
_RecordsetPtr  CDrawLine::QueryLinesByCondit(_bstr_t bstrWhere)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("自画线"))
	{
		MessageBox(NULL,_T("数据库中不存在该自画线业务表！"),_T("提示"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSqlRes("select 编号,名称,颜色,创建人,创建时间,描述  from  自画线 WHERE 1=1 " + bstrWhere,adCmdText);
}

void CDrawLine::QueryLinesByCondit(_bstr_t bstrWhere, vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryLinesByCondit(bstrWhere);
	if ( Rcst ==NULL )
		return;
	CBllHelp *help = new CBllHelp();
	help->QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
}
//创建查询
_RecordsetPtr  CDrawLine::QueryCreateLines(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName)
{
	_bstr_t strSqlwhere="";
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case OracleType:
		if (strCreatorName.length()>0)
		{
			strSqlwhere+="and 创建人='"+strCreatorName+"'";
		}
		if (strBeginTime.length()>0&&strEndTime.length()>0)
			strSqlwhere+="  and 创建时间 = to_date('" + strBeginTime + "','dd/mm/yyyy') and  to_date('" + strEndTime + "','dd/mm/yyyy')";
		else if(strBeginTime.length()>0)
			strSqlwhere+="    and 创建时间 = to_date('" + strBeginTime + "','dd/mm/yyyy')";
		else if(strEndTime.length()>0)
			strSqlwhere+="    and 创建时间 = to_date('" + strEndTime + "','dd/mm/yyyy')";
		break;
	case SqlServerType:
		if (strCreatorName.length()>0)
		{
			strSqlwhere+="and 创建人='"+strCreatorName+"'";
		}
		if (strBeginTime.length()>0&&strEndTime.length()>0)
			strSqlwhere+="  and 创建时间 between '"+strBeginTime+"' and '"+strEndTime+"'";
		else if(strBeginTime.length()>0)
			strSqlwhere+="   and 创建时间='"+strBeginTime+"'";
		else if(strEndTime.length()>0)
			strSqlwhere+="   and 创建时间='"+strEndTime+"'";
		break;
	case AccessType:
		if (strCreatorName.length()>0)
		{
			strSqlwhere+="and 创建人='"+strCreatorName+"'";
		}
		if (strBeginTime.length()>0&&strEndTime.length()>0)
			strSqlwhere+="  and 创建时间 between #"+strBeginTime+"# and #"+strEndTime+"#";
		else if(strBeginTime.length()>0)
			strSqlwhere+="   and 创建时间=#"+strBeginTime+"#";
		else if(strEndTime.length()>0)
			strSqlwhere+="   and 创建时间=#"+strEndTime+"#";
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
