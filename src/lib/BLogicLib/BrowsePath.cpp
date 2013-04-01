#include "BrowsePath.h"

CBrowsePath CBrowsePath::instance;

CBrowsePath::CBrowsePath(void)
{
}

CBrowsePath::~CBrowsePath(void)
{
}
//单体初始化
CBrowsePath & CBrowsePath::Instance()
{
	return instance;
}
//判断连接
BOOL CBrowsePath::IsConnectOk()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("路径浏览"))
	{
		MessageBox(NULL,_T("数据库中不存在该流行线业务表！"),_T("提示"),0);
		return FALSE;
	}
	return TRUE;
}
//判断名称是否存在
BOOL CBrowsePath::IsNameExiste(_bstr_t strName)
{
	BOOL bIs=FALSE;
	if (!IsConnectOk())
		return FALSE;
	_bstr_t strSQL = "SELECT * FROM 路径浏览 WHERE 名称 = '" + strName+"'";
	_RecordsetPtr pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if (pRecordSet==NULL)
		return FALSE;
	if (pRecordSet!=NULL && !pRecordSet->adoEOF)
		bIs=TRUE;
	pRecordSet->Close();
	pRecordSet.Release();
	return bIs;
}
//保存
int CBrowsePath::Save(_bstr_t bstrId,_bstr_t bstrName,_bstr_t bstrSpeed,_bstr_t strTarget,_bstr_t strLoop)
{
	//判断连接
	if (!IsConnectOk())
		return -1;
	//判断数据有效性
	if (bstrName.length()<1 || bstrSpeed.length()<1 || strTarget.length()<1)
	{
		MessageBox(NULL,_T("请将填写完整信息！"),0,0);
		return -1;
	}
	_bstr_t bstrSql;
	if (bstrId.length()>0) //修改
	{
		bstrSql="update 路径浏览 set 是否循环= "+strLoop+", 名称= '"+bstrName+"', 速度= " + bstrSpeed + ", 所属目标= '"+strTarget+"'  where 编号= "+bstrId;

		if (theBllApp.m_pDB->ExcuteSql(bstrSql,adCmdText))
			return atoi((char *)bstrId);
	}
	else     //新建
	{
		bstrSql="insert into 路径浏览(名称,速度,所属目标,是否循环) values('"+bstrName+"',"+bstrSpeed+",'"+strTarget+"',"+strLoop+")";
		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			bstrSql="insert into 路径浏览(编号,名称,速度,所属目标,是否循环) values(路径浏览序列.NextVal,'"+bstrName+"',"+bstrSpeed+",'"+strTarget+"',"+strLoop+")";
		if (theBllApp.m_pDB->ExcuteSql(bstrSql,adCmdText))
		{
			bstrSql="SELECT MAX(编号) AS 最大编号  FROM 路径浏览";
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
				bstrSql="select 路径浏览序列.currval as 最大编号 from dual";
			_RecordsetPtr rcst=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
			if (rcst!=NULL && !rcst->adoEOF)
				return atoi((char *)(_bstr_t)rcst->GetCollect("最大编号"));
		}
	}
	return -1;
}
//保存坐标
BOOL CBrowsePath::SaveNodes(_bstr_t bstrId,std::vector<_bstr_t> vpos)
{
	if (bstrId.length()<1)
	{
		MessageBox(NULL,_T("请选择要保存坐标的路径！"),0,0);
		return FALSE;
	}
	std::vector<_bstr_t> vstrSql;
	//删除原来
	_bstr_t bstPos,bstrSql="delete from 路径浏览节点 where 路径编号="+bstrId;
	vstrSql.push_back(bstrSql);
	//保存现在
	for(std::vector<_bstr_t>::iterator item=vpos.begin();item!=vpos.end();item++)
	{
		bstPos=*item;
		bstrSql="insert into 路径浏览节点 (路径编号,坐标) values ("+bstrId+",'"+bstPos+"')";
		vstrSql.push_back(bstrSql);
	}
	return theBllApp.m_pDB->ExcuteTrans(vstrSql,adCmdText);
}
//用编号删除
BOOL CBrowsePath::DeleteById(_bstr_t bstrId)
{
	//判断连接
	BOOL bIs=FALSE;
	if (!IsConnectOk())
		return FALSE;
	if (bstrId.length()<0)
	{
		MessageBox(NULL,_T("删除记录编号不能为空！"),0,0);
		return FALSE;
	}
	std::vector<_bstr_t> vbstrSql;
	vbstrSql.push_back( "DELETE FROM 路径浏览节点 WHERE 路径编号=" + bstrId );
	vbstrSql.push_back( "DELETE FROM 路径浏览 WHERE 编号="+bstrId);
	return theBllApp.m_pDB->ExcuteTrans( vbstrSql  ,adCmdText );
}
//用名称删除
BOOL CBrowsePath::DeleteByName(_bstr_t bstrName)
{
	//判断连接
	BOOL bIs=FALSE;
	if (!IsConnectOk())
		return FALSE;

	if (bstrName.length()<0)
	{
		MessageBox(NULL,_T("删除记录名称不能为空！"),0,0);
		return FALSE;
	}

	_RecordsetPtr Rcst=theBllApp.m_pDB->ExcuteSqlRes("select * from 路径浏览 where 名称='"+bstrName+"'",adCmdText);
	if (Rcst!=NULL)
	{
		if ( !Rcst->adoEOF )
		{
			_bstr_t bstrId=(_bstr_t)Rcst->GetCollect("编号");
			std::vector<_bstr_t> vbstrSql;
			vbstrSql.push_back( "DELETE FROM 路径浏览节点 WHERE 路径编号=" + bstrId );
			vbstrSql.push_back( "DELETE FROM 路径浏览 WHERE 编号="+bstrId);
			bIs= theBllApp.m_pDB->ExcuteTrans( vbstrSql  ,adCmdText );
		}
		Rcst->Close();
		Rcst.Release();
	}
	return bIs;
}
//用编号加载
PATHMODEL CBrowsePath::LoadById(_bstr_t bstrId)
{
	//判断连接
	PATHMODEL model;
	if (!IsConnectOk())
		return model;
	if (bstrId.length()<0)
	{
		MessageBox(NULL,_T("删除记录编号不能为空！"),0,0);
		return model;
	}
	
	_RecordsetPtr Rcst=theBllApp.m_pDB->ExcuteSqlRes("select * from 路径浏览 where 编号=" + bstrId,adCmdText);
	if (Rcst!=NULL)
	{
		if (!Rcst->adoEOF)
		{
			model.iId=(int)Rcst->GetCollect("编号");
			model.strName=(char *)((_bstr_t)Rcst->GetCollect("名称"));
			model.dSpeed=(double)Rcst->GetCollect("速度");
			model.strTarget=(char *)((_bstr_t)Rcst->GetCollect("所属目标"));
			model.bLoop=(bool)Rcst->GetCollect("是否循环");
			model.vNodes=LoadNodes((_bstr_t)Rcst->GetCollect("编号"));
		}
		Rcst->Close();
		Rcst.Release();
	}
	return model;
}
//用名称加载
PATHMODEL CBrowsePath::LoadByName(_bstr_t bstrName)
{
	//判断连接
	PATHMODEL model;
	if (!IsConnectOk())
		return model;
	if (bstrName.length()<0)
	{
		MessageBox(NULL,_T("删除记录名称不能为空！"),0,0);
		return model;
	}
	_RecordsetPtr Rcst=theBllApp.m_pDB->ExcuteSqlRes("select * from 路径浏览 where 名称='" + bstrName+"'",adCmdText);
	if (Rcst!=NULL)
	{
		if (!Rcst->adoEOF)
		{
			model.iId=(int)Rcst->GetCollect("编号");
			model.strName=(char *)((_bstr_t)Rcst->GetCollect("名称"));
			model.dSpeed=(double)Rcst->GetCollect("速度");
			model.strTarget=(char *)((_bstr_t)Rcst->GetCollect("所属目标"));
			model.bLoop=(bool)Rcst->GetCollect("是否循环");
			model.vNodes=LoadNodes((_bstr_t)Rcst->GetCollect("编号"));
		}
		Rcst->Close();
		Rcst.Release();
	}
	return model;
}
//用编号得到节点坐标
std::vector<string> CBrowsePath::LoadNodes(_bstr_t bstrId)
{
	std::vector<string> vNodes;
	if (!IsConnectOk())
		return vNodes;
	if (bstrId.length()<0)
	{
		MessageBox(NULL,_T("加载记录编号不能为空！"),0,0);
		return vNodes;
	}
	
	_RecordsetPtr rcst=theBllApp.m_pDB->ExcuteSqlRes("select * from 路径浏览节点 where 路径编号="+bstrId,adCmdText);
	if (rcst!=NULL)
	{
		string strTemp;
		while(!rcst->adoEOF)
		{
			strTemp=(char *)((_bstr_t)rcst->GetCollect("坐标"));
			vNodes.push_back(strTemp);
			rcst->MoveNext();
		}
		rcst->Close();
		rcst.Release();
	}
	return vNodes;
}
//查询所有路径浏览
std::vector<PATHMODEL> CBrowsePath::QueryAllPath()
{
	return QueryPathByCondition("");
}
//按重点目标查询所有路径浏览
std::vector<PATHMODEL> CBrowsePath::QueryPathByTarget(_bstr_t strTarget)
{
	vector<PATHMODEL> v;
	if (strTarget.length()<1)
	{
		MessageBox(NULL,_T("请选择重点目标！"),0,0);
		return v;
	}
	return QueryPathByCondition("  and 所属目标='" + strTarget + "'");
}
//查询条件路径浏览
std::vector<PATHMODEL> CBrowsePath::QueryPathByCondition(_bstr_t bstrConditions)
{
	//判断连接
	std::vector<PATHMODEL> vModel;
	if (!IsConnectOk())
		return vModel;
	_RecordsetPtr rcst=theBllApp.m_pDB->ExcuteSqlRes("select * from 路径浏览 where 1=1 "+bstrConditions,adCmdText);
	if (rcst!=NULL)
	{
		PATHMODEL model;
		while(!rcst->adoEOF)
		{
			model.iId=(int)rcst->GetCollect("编号");
			model.strName=(char *)((_bstr_t)rcst->GetCollect("名称"));
			model.dSpeed=(double)rcst->GetCollect("速度");
			model.strTarget=(char *)((_bstr_t)rcst->GetCollect("所属目标"));
			model.bLoop=(bool)rcst->GetCollect("是否循环");
			model.vNodes=LoadNodes((_bstr_t)rcst->GetCollect("编号"));
			vModel.push_back(model);
			rcst->MoveNext();
		}
		rcst->Close();
		rcst.Release();
	}
	return vModel;
}