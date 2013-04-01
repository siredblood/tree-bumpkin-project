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
//加载流行线信息
BOOL CFloatRowLine::LoadInfo( _bstr_t bstrID)
{
	if (bstrID.length()<=0)
	{
		MessageBox(NULL,_T("请选择要加载的流行线！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("流行线"))
	{
		MessageBox(NULL,_T("数据库中不存在该流行线业务表！"),_T("提示"),0);
		return FALSE;
	}
	_RecordsetPtr  prstInfo = theBllApp.m_pDB->ExcuteSqlRes("select 编号,名称,所属目标,颜色,实线,箭头,宽度,创建人,创建时间,描述  from  流行线  where 编号="+bstrID,adCmdText);
	BOOL bFlag=FALSE;

	if (prstInfo!=NULL)
	{
		if (!prstInfo->adoEOF)
		{
			m_strID = bstrID  ;
			_variant_t var;
			var=(prstInfo->GetCollect("名称")) ;
			m_strName = (_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("所属目标")) ;
			m_strToTarger=(_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("颜色")) ;
			m_strColor=(_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("实线")) ;
			m_strLineType=(_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("箭头")) ;
			m_strDerection=(_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("宽度")) ;
			m_strWidth=(_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("创建人")) ;
			m_strCreator = (_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("创建时间")) ;
			m_strCreateTime = (_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("描述")) ;
			m_strRemark = (_bstr_t)(var.vt==1?"":var);
			bFlag=TRUE;
		}
		prstInfo->Close();
		prstInfo.Release();
	} 
	return bFlag;
}
//加载流行线节点数据集
_RecordsetPtr CFloatRowLine::LoadNodesRCS( _bstr_t bstrID)
{
	if (bstrID.length()<=0)
	{
		MessageBox(NULL,_T("请选择要加载的流行线！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("流行线"))
	{
		MessageBox(NULL,_T("数据库中不存在该流行线业务表！"),_T("提示"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSqlRes("select 编号,坐标  from  线节点  where 线类型='流行线' and  所属线编号="+bstrID+"  order by 编号",adCmdText);
}
//加载流行线节点列表
std::vector<string> CFloatRowLine::LoadNodesVetor( _bstr_t bstrID)
{
	vector<string> coodinates;
	if (bstrID.length()<=0)
	{
		MessageBox(NULL,_T("请选择要加载的流行线！"),_T("提示"),0);
		return coodinates;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return coodinates;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("流行线"))
	{
		MessageBox(NULL,_T("数据库中不存在该流行线业务表！"),_T("提示"),0);
		return coodinates;
	}
	
	_RecordsetPtr prst=LoadNodesRCS(bstrID);
	if (prst!=NULL)
	{
		_variant_t var;
		while(!prst->adoEOF)
		{
			var=prst->GetCollect("坐标");
			coodinates.push_back(((char *)((_bstr_t)(var.vt==1?"":var))));
			prst->MoveNext();
		}
		prst->Close();
		prst.Release();
	}
	return coodinates;
}

//加载流行线属性列表
_RecordsetPtr CFloatRowLine::Loadproperties( _bstr_t bstrID )
{
	if (bstrID.length()<=0)
	{
		MessageBox(NULL,_T("请选择要加载属性的流行线！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("流行线"))
	{
		MessageBox(NULL,_T("数据库中不存在该流行线业务表！"),_T("提示"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSqlRes("select 编号,启用时间,结束时间,备注  from  流行线属性  where 所属流行线 = "+bstrID,adCmdText);
}

void CFloatRowLine::Loadproperties(_bstr_t bstrID, std::vector<string> &vecField, std::vector<string> &vecRecordSet, long &lFieldCounts)
{
	if (bstrID.length()<=0)
	{
		MessageBox(NULL,_T("请选择要加载属性的流行线！"),_T("提示"),0);
		return;
	}
	_RecordsetPtr res = Loadproperties(bstrID);
	if(res==NULL)
		return;

	CBllHelp::Instance().QueryByCondit(res,vecField,vecRecordSet,lFieldCounts);
}

//增加流行线记录,
//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
BOOL CFloatRowLine::Add()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("流行线"))
	{
		MessageBox(NULL,_T("数据库中不存在该流行线业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t bstrSQL;
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case OracleType:
		bstrSQL="insert into 流行线(编号,名称,所属目标,颜色,实线,箭头,宽度,创建人,创建时间,描述) values(流行线序列.NextVal,'" + m_strName + "','" + m_strToTarger + "','" + m_strColor + "',"+m_strLineType+","+m_strDerection+","+m_strWidth+",'" +m_strCreator+"',to_date('" + m_strCreateTime + "','dd/mm/yyyy'),'"+ m_strRemark + "')";
		break;
	case SqlServerType:
		bstrSQL="insert into 流行线(名称,所属目标,颜色,实线,箭头,宽度,创建人,创建时间,描述) values('" + m_strName + "','" + m_strToTarger + "','" + m_strColor + "',"+m_strLineType+","+m_strDerection+","+m_strWidth+",'"+m_strCreator+"','"+m_strCreateTime+"','" + m_strRemark + "')";
		break;
	case AccessType:
		bstrSQL="insert into 流行线(名称,所属目标,颜色,实线,箭头,宽度,创建人,创建时间,描述) values('" + m_strName + "','" + m_strToTarger + "','" + m_strColor + "',"+m_strLineType+","+m_strDerection+","+m_strWidth+",'"+m_strCreator+"',#"+m_strCreateTime+"#,'" + m_strRemark + "')";
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
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return -1;
		}
	if (!theBllApp.m_pDB->CheckTableNameExist("流行线"))
		{
		MessageBox(NULL,_T("数据库中不存在该流行线业务表！"),_T("提示"),0);
		return -1;
		}
	_bstr_t bstrSQL;
	switch(CDatabaseFactory::m_enumDatabaseType)
		{
		case OracleType:
			bstrSQL="insert into 流行线(编号,名称,所属目标,颜色,实线,箭头,宽度,创建人,创建时间,描述) values(流行线序列.NextVal,'" + m_strName + "','" + m_strToTarger + "','" + m_strColor + "',"+m_strLineType+","+m_strDerection+","+m_strWidth+",'" +m_strCreator+"',to_date('" + m_strCreateTime + "','dd/mm/yyyy'),'"+ m_strRemark + "')";
			break;
		case SqlServerType:
			bstrSQL="insert into 流行线(名称,所属目标,颜色,实线,箭头,宽度,创建人,创建时间,描述) values('" + m_strName + "','" + m_strToTarger + "','" + m_strColor + "',"+m_strLineType+","+m_strDerection+","+m_strWidth+",'"+m_strCreator+"','"+m_strCreateTime+"','" + m_strRemark + "')";
			break;
		case AccessType:
			bstrSQL="insert into 流行线(名称,所属目标,颜色,实线,箭头,宽度,创建人,创建时间,描述) values('" + m_strName + "','" + m_strToTarger + "','" + m_strColor + "',"+m_strLineType+","+m_strDerection+","+m_strWidth+",'"+m_strCreator+"',#"+m_strCreateTime+"#,'" + m_strRemark + "')";
			break;
		default :
			return -1;
		}

	if (theBllApp.m_pDB->ExcuteSql( bstrSQL , adCmdText ))
		{
		bstrSQL="select max(编号) as 最大编号 from 流行线";
		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			bstrSQL="select 流行线序列.currval as 最大编号 from dual";
		_RecordsetPtr rPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSQL,adCmdText);
		if (rPtr!=NULL&&!rPtr->adoEOF)
			return atoi((char *)((_bstr_t)rPtr->GetCollect("最大编号")));
		}
	return -1;
}

//编辑流行线记录,
//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
BOOL CFloatRowLine::Update()
{
	if (m_strID.length()==0)
	{
		MessageBox(NULL,_T("请选择要修改流行线！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("流行线"))
	{
		MessageBox(NULL,_T("数据库中不存在该流行线业务表！"),_T("提示"),0);
		return FALSE;
	}
	
	_bstr_t bstrSQL="UPDATE 流行线 SET 名称='" + m_strName + "',所属目标='" + m_strToTarger +"',颜色='"+ m_strColor +"',实线="+ m_strLineType +",箭头="+ m_strDerection +",宽度="+ m_strWidth + ",描述='" + m_strRemark + "'  WHERE 编号=" + m_strID;
	return theBllApp.m_pDB->ExcuteSql( bstrSQL , adCmdText );
}


//清除流行线节点
BOOL CFloatRowLine::ClearLineNodes( _bstr_t bstrIDs )
{
	if (bstrIDs.length()==0)
	{
		MessageBox(NULL,_T("请选择清除节点的流行线！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("流行线"))
	{
		MessageBox(NULL,_T("数据库中不存在该流行线业务表！"),_T("提示"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSql("DELETE FROM 线节点 WHERE 线类型='流行线' and  所属线编号 IN ( " + bstrIDs + " )",adCmdText);
}
//编辑流行线记录信息,
//参数：坐标列表
//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
BOOL CFloatRowLine::SaveLineNodes( std::vector<_bstr_t> vbstrCoordinates )
{
	if (m_strID.length()==0)
	{
		MessageBox(NULL,_T("请选择要保存节点的流行线！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("流行线"))
	{
		MessageBox(NULL,_T("数据库中不存在该流行线业务表！"),_T("提示"),0);
		return FALSE;
	}
	
	std::vector<_bstr_t> vbstrSql;
	vbstrSql.push_back( "DELETE FROM 线节点 WHERE 线类型='流行线' and  所属线编号 =" + m_strID );
	_bstr_t bstrSQL="";
	_bstr_t coodinate="";
	for ( vector<_bstr_t>::iterator item = vbstrCoordinates.begin() ; item != vbstrCoordinates.end() ; item ++ )
	{
		coodinate=((_bstr_t)*item);
		bstrSQL="INSERT INTO 线节点(所属线编号,线类型,坐标) VALUES(" + m_strID + ",'流行线','" + coodinate + "')";
		if ( CDatabaseFactory::m_enumDatabaseType == OracleType )
		{
			bstrSQL="INSERT INTO 线节点(编号,所属线编号,线类型,坐标) VALUES(线节点序列.NextVal," + m_strID + ",'流行线','" + coodinate + "')";
		}
		vbstrSql.push_back(bstrSQL);
	}
	return theBllApp.m_pDB->ExcuteTrans(vbstrSql ,adCmdText );
}

//删除流行线记录，
//通过传递编号（用“，"隔开）
BOOL CFloatRowLine::Delete(_bstr_t bstrIDS)
{
	if (bstrIDS.length()<=0)
	{
		MessageBox(NULL,_T("请选择要删除的流行线！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("流行线"))
	{
		MessageBox(NULL,_T("数据库中不存在该流行线业务表！"),_T("提示"),0);
		return FALSE;
	}
	std::vector<_bstr_t> vbstrSql;
	vbstrSql.push_back( "DELETE FROM 线节点 WHERE 线类型='流行线' and  所属线编号 IN ( " + bstrIDS + " )");
	vbstrSql.push_back( "DELETE FROM 流行线 WHERE 编号 IN ( " + bstrIDS + " )");
	return theBllApp.m_pDB->ExcuteTrans( vbstrSql  ,adCmdText );
}


//查询所有流行线目标列表
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
//查询重点目标流行线
_RecordsetPtr CFloatRowLine::QueryTargetLines(_bstr_t strTarget)
{
	return QueryLinesByCondit(" and 所属目标='"+strTarget+"'");
}
std::vector<_bstr_t> CFloatRowLine::QueryTargetinesID(_bstr_t strTarget)
{
	return QueryLinesIDByCondit(" and 所属目标='"+strTarget+"'");
}
void CFloatRowLine::QueryTargetLines(_bstr_t strTarget,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr prst=QueryTargetLines(strTarget);
	if (prst==NULL)
		return;
	CBllHelp::Instance().QueryByCondit(prst,vecField,vecRecordSet,lFieldCounts);
}

//条件查询流行线记录
_RecordsetPtr  CFloatRowLine::QueryLinesByCondit(_bstr_t bstrWhere)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("流行线"))
	{
		MessageBox(NULL,_T("数据库中不存在该流行线业务表！"),_T("提示"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSqlRes("select 编号,名称,所属目标,颜色,实线,箭头,宽度,创建人,创建时间,描述  from  流行线 WHERE 1=1 "+bstrWhere,adCmdText);
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
		var=(prst->GetCollect("编号"));
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
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return ;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("流行线"))
	{
		MessageBox(NULL,_T("数据库中不存在该流行线业务表！"),_T("提示"),0);
		return ;
	}
	_RecordsetPtr prst;
	prst=QueryLinesByCondit(bstrWhere);
	if (prst==NULL)
		return;
	CBllHelp::Instance().QueryByCondit(prst,vecField,vecRecordSet,lFieldCounts);
}

//查询时间段内有效的流行线
_RecordsetPtr CFloatRowLine::QueryValidateLines(_bstr_t bstrBeginDate,_bstr_t bstrEndDate)
{
	if (bstrBeginDate.length()<=0||bstrEndDate.length()<=0)
	{
		MessageBox(NULL,_T("请输入有效时间间隔！"),_T("提示"),0);
		return FALSE;
	}

	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("流行线"))
	{
		MessageBox(NULL,_T("数据库中不存在该流行线业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t bstrSql;
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case AccessType:
		bstrSql="select 流行线.编号,名称,所属目标,启用时间,结束时间  from 流行线,流行线属性   where  流行线.编号=流行线属性.所属流行线 and (启用时间<=#"+bstrBeginDate+"# and  结束时间>=#"+bstrBeginDate+"#) or(启用时间>=#"+bstrBeginDate+"# and  结束时间<=#"+bstrEndDate+"#)  or(启用时间<=#"+bstrEndDate+"# and  结束时间>=#"+bstrEndDate+"#)  order by 流行线.编号";
		break;
	case SqlServerType:
		bstrSql="select  流行线.编号,名称,所属目标,启用时间,结束时间  from 流行线,流行线属性  where 流行线.编号=流行线属性.所属流行线 and (启用时间<='"+bstrBeginDate+"' and  结束时间>='"+bstrBeginDate+"') or(启用时间>='"+bstrBeginDate+"' and  结束时间<='"+bstrEndDate+"')  or(启用时间<='"+bstrEndDate+"' and  结束时间>='"+bstrEndDate+"')  order by 流行线.编号";
		break;
	case OracleType:
		bstrSql="select  流行线.编号,名称,所属目标,启用时间,结束时间  from 流行线,流行线属性  where 流行线.编号=流行线属性.所属流行线 and (启用时间<=to_date('" + bstrBeginDate + "','dd/mm/yyyy') and  结束时间>=to_date('" + bstrBeginDate + "','dd/mm/yyyy')) or(启用时间>=to_date('" + bstrBeginDate + "','dd/mm/yyyy') and  结束时间<=to_date('" + bstrEndDate + "','dd/mm/yyyy'))  or(启用时间<=to_date('" + bstrEndDate + "','dd/mm/yyyy') and  结束时间>=to_date('" + bstrEndDate + "','dd/mm/yyyy'))  order by 流行线.编号";
		break;
	default:
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
}
//查询时间段内有效的流行线
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
	_RecordsetPtr prst = theBllApp.m_pDB->ExcuteSqlRes("SELECT 名称 FROM 流行线 WHERE 名称='"+tempName+"'",adCmdText);
	if (prst!=NULL && !prst->adoEOF)
		return true;
	else
		return false;
}

//创建查询
_RecordsetPtr CFloatRowLine::QueryCreateLines(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName)
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
void CFloatRowLine::QueryCreateLines(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr prst=QueryCreateLines( strBeginTime, strEndTime, strCreatorName );
	if(prst==NULL)
		return;
	CBllHelp::Instance().QueryByCondit(prst,vecField,vecRecordSet,lFieldCounts);
}
/************************************************************************/
/* 流行线属性                                                           */
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

//加载属性:参数：属性表中的编号
BOOL CFRowLineProperty::LoadInfo( _bstr_t bstrID )
{
	if (bstrID.length()<=0)
	{
		MessageBox(NULL,_T("请选择加载流行线属性！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("流行线属性"))
	{
		MessageBox(NULL,_T("数据库中不存在该流行线属性业务表！"),_T("提示"),0);
		return FALSE;
	}
	_RecordsetPtr  prstInfo = theBllApp.m_pDB->ExcuteSqlRes("select 编号,所属流行线,启用时间,结束时间,备注  from  流行线属性  where 编号="+bstrID,adCmdText);
	BOOL Bflag=FALSE;

	if (prstInfo!=NULL)
	{
		if(!prstInfo->adoEOF)
		{
			m_strID = bstrID ;
			_variant_t var;
			var=prstInfo->GetCollect("所属流行线") ;
			m_strLineID=(_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("启用时间")) ;
			m_strBeginDate=(_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("结束时间")) ;
			m_strEndDate=(_bstr_t)(var.vt==1?"":var);
			var=(prstInfo->GetCollect("备注")) ;
			m_strRemark = (_bstr_t)(var.vt==1?"":var);
			Bflag=TRUE;
		}
		prstInfo->Close();
		prstInfo.Release();
	} 
	return Bflag;
}
//检测流行线属性录入的冲突
//参数：bstrID，修改则bstrID为流行线属性编号，添加则为“”
//		bstrLineid为流行线编号
BOOL CFRowLineProperty::CheckLnPrptyColn(_bstr_t bstrID, _bstr_t bstrLineid,_bstr_t bstrBeginDate,_bstr_t bstrEndDate)
{
	_bstr_t bstrSql="";
	if (bstrID.length()==0)
	{
		switch(CDatabaseFactory::m_enumDatabaseType)
		{
		case AccessType:
			bstrSql="select *  from  流行线属性   where  所属流行线=" + bstrLineid + "  and  (启用时间<=#"+bstrBeginDate+"# and  结束时间>=#"+bstrBeginDate+"#) or (启用时间>=#"+bstrBeginDate+"#  and  结束时间<=#"+bstrEndDate+"#)  or (启用时间<=#"+bstrEndDate+"#  and  结束时间>=#"+bstrEndDate+"#)";
			break;
		case SqlServerType:
			bstrSql="select  *  from  流行线属性  where  所属流行线=" + bstrLineid + "  and  (启用时间<='"+bstrBeginDate+"' and  结束时间>='"+bstrBeginDate+"') or (启用时间>='"+bstrBeginDate+"' and  结束时间<='"+bstrEndDate+"')  or (启用时间<='"+bstrEndDate+"' and  结束时间>='"+bstrEndDate+"')";
			break;
		case OracleType:
			bstrSql="select  *  from  流行线属性  where  所属流行线=" + bstrLineid + "  and  (启用时间<=to_date('" + bstrBeginDate + "','dd/mm/yyyy')  and  结束时间>=to_date('" + bstrBeginDate + "','dd/mm/yyyy')) or (启用时间>=to_date('" + bstrBeginDate + "','dd/mm/yyyy') and  结束时间<=to_date('" + bstrEndDate + "','dd/mm/yyyy'))  or (启用时间<=to_date('" + bstrEndDate + "','dd/mm/yyyy') and  结束时间>=to_date('" + bstrEndDate + "','dd/mm/yyyy'))";
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
			bstrSql="select *  from  流行线属性   where  所属流行线=" + bstrLineid + "  and  编号<>"+bstrID+"   and  ((启用时间<=#"+bstrBeginDate+"# and  结束时间>=#"+bstrBeginDate+"#) or(启用时间>=#"+bstrBeginDate+"# and  结束时间<=#"+bstrEndDate+"#)  or(启用时间<=#"+bstrEndDate+"# and  结束时间>=#"+bstrEndDate+"#))";
			break;
		case SqlServerType:
			bstrSql="select  *  from  流行线属性  where  所属流行线=" + bstrLineid + "  and  编号<>"+bstrID+"   and  ((启用时间<='"+bstrBeginDate+"' and  结束时间>='"+bstrBeginDate+"') or(启用时间>='"+bstrBeginDate+"' and  结束时间<='"+bstrEndDate+"')  or(启用时间<='"+bstrEndDate+"' and  结束时间>='"+bstrEndDate+"'))";
			break;
		case OracleType:
			bstrSql="select  *  from  流行线属性  where  所属流行线=" + bstrLineid + "  and  编号<>"+bstrID+"   and  ((启用时间<=to_date('" + bstrBeginDate + "','dd/mm/yyyy')  and  结束时间>=to_date('" + bstrBeginDate + "','dd/mm/yyyy')) or (启用时间>=to_date('" + bstrBeginDate + "','dd/mm/yyyy') and  结束时间<=to_date('" + bstrEndDate + "','dd/mm/yyyy'))  or (启用时间<=to_date('" + bstrEndDate + "','dd/mm/yyyy') and  结束时间>=to_date('" + bstrEndDate + "','dd/mm/yyyy')))";
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
//增加流行线属性记录,
//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
BOOL CFRowLineProperty::Add()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("流行线属性"))
	{
		MessageBox(NULL,_T("数据库中不存在该流行线属性业务表！"),_T("提示"),0);
		return FALSE;
	}
	if (CheckLnPrptyColn("",m_strLineID,m_strBeginDate,m_strEndDate))
	{
		MessageBox(NULL,_T("同流行线同时间内不能启用二次！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t bstrSQL="insert into 流行线属性(所属流行线,启用时间,结束时间,备注) values(" + m_strLineID + ",'" + m_strBeginDate + "','" + m_strEndDate + "','" + m_strRemark + "')";
	if ( CDatabaseFactory::m_enumDatabaseType == OracleType )
	{
		bstrSQL="insert into 流行线属性(编号,所属流行线,启用时间,结束时间,备注) values(流行线属性序列.NextVal," + m_strLineID + ",to_date('" + m_strBeginDate + "','dd/mm/yyyy'),to_date('" + m_strEndDate + "','dd/mm/yyyy'),'" + m_strRemark + "')";
	}
	return theBllApp.m_pDB->ExcuteSql( bstrSQL , adCmdText );
}
//编辑流行线属性记录,首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
BOOL CFRowLineProperty::Update()
{
	if ( m_strID.length() == 0)
	{
		MessageBox(NULL,_T("请选择要更新流行线属性！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("流行线属性"))
	{
		MessageBox(NULL,_T("数据库中不存在该流行线属性业务表！"),_T("提示"),0);
		return FALSE;
	}
	
	if (CheckLnPrptyColn(m_strID,m_strLineID,m_strBeginDate,m_strEndDate))
	{
		MessageBox(NULL,_T("修改时间冲突！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t bstrSQL;
	bstrSQL="UPDATE  流行线属性  SET  所属流行线=" + m_strLineID + ",启用时间='" + m_strBeginDate +"',结束时间='"+ m_strEndDate + "',备注='" + m_strRemark + "' WHERE 编号=" +m_strID;
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
	{
		bstrSQL="UPDATE  流行线属性  SET  所属流行线=" + m_strLineID + ",启用时间=to_date('" + m_strBeginDate + "','dd/mm/yyyy'),结束时间=to_date('" + m_strEndDate + "','dd/mm/yyyy'),备注='" + m_strRemark + "'  WHERE 编号=" +m_strID;
	}
	return theBllApp.m_pDB->ExcuteSql( bstrSQL , adCmdText );
}
//删除流行线属性记录，通过传递编号（用“，"隔开）
BOOL CFRowLineProperty::Delete(_bstr_t bstrIDS)
{
	if (bstrIDS.length()<=0)
	{
		MessageBox(NULL,_T("请选择要删除流行线属性！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("流行线属性"))
	{
		MessageBox(NULL,_T("数据库中不存在该流行线属性业务表！"),_T("提示"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSql("DELETE FROM 流行线属性 WHERE 编号 IN ( " + bstrIDS + " )",adCmdText);
}
