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
		return "";
	}
	return strSqlwhere;
}
//开放方法
//方案分析的数据库操作

/************************************************************************/
/* 加载方案基本信息                                                     */
/************************************************************************/
//加载对象:参数：方案对象编号
BOOL CAnalyseDemo::LoadDemoInfo(_bstr_t bstrId)
{
	//数据库操作前判断
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析方案"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析方案业务表！"),_T("提示"),0);
		return FALSE;
	}
	if (bstrId.length()<=0)
	{
		MessageBox(NULL,_T("请选择要加载的方案编号！"),_T("提示"),0);
		return FALSE;
	}

	BOOL Brst=FALSE;
	_RecordsetPtr  prstInfo = theBllApp.m_pDB->ExcuteSqlRes("SELECT 编号,名称,目标点,所属目标,范围,类型,线编号,外框颜色,结果颜色,部份结果颜色,创建人,创建时间,描述  FROM 分析方案  where 编号="+bstrId,adCmdText);
	if (prstInfo!=NULL)
	{
		if(!prstInfo->adoEOF)
		{
			_variant_t var;
			m_strID = bstrId  ;
			var=(prstInfo->GetCollect("名称"));
			m_strName = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("目标点"));
			m_targetPoint = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("所属目标"));
			m_strToTarger = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("范围")) ;
			m_strRange = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("类型")) ;
			m_strType = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("线编号")) ;
			m_strTypeID = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("外框颜色")) ;
			m_strOuterColor = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("结果颜色")) ;
			m_strResultColor = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("部份结果颜色")) ;
			m_strPartResultColor = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("创建人")) ;
			m_strCreator = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("创建时间")) ;
			m_strCreateTime = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("描述")) ;
			m_strRemark = (_bstr_t)(var.vt==1?"":var) ;
			Brst=TRUE;
		}	
		prstInfo->Close();
		prstInfo.Release();
	}
	return Brst;

}


//加载对象:参数：方案对象名称
BOOL CAnalyseDemo::LoadDemoInfoByName(_bstr_t bstrName)
{
	//数据库操作前判断
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析方案"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析方案业务表！"),_T("提示"),0);
		return FALSE;
	}
	if (bstrName.length()<=0)
	{
		MessageBox(NULL,_T("请选择要加载的方案名称！"),_T("提示"),0);
		return FALSE;
	}
	BOOL Brst=FALSE;
	_RecordsetPtr  prstInfo = theBllApp.m_pDB->ExcuteSqlRes("SELECT 编号,名称,目标点,所属目标,范围,类型,线编号,外框颜色,结果颜色,部份结果颜色,创建人,创建时间,描述  FROM 分析方案  where 名称='"+bstrName+"'",adCmdText);
	if (prstInfo!=NULL)
	{
		if(!prstInfo->adoEOF)
		{
			_variant_t var;
			var=(prstInfo->GetCollect("编号"));
			m_strID = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("名称"));
			m_strName = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("目标点"));
			m_targetPoint = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("所属目标"));
			m_strToTarger = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("范围")) ;
			m_strRange = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("类型")) ;
			m_strType = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("线编号")) ;
			m_strTypeID = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("外框颜色")) ;
			m_strOuterColor = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("结果颜色")) ;
			m_strResultColor = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("部份结果颜色")) ;
			m_strPartResultColor = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("创建人")) ;
			m_strCreator = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("创建时间")) ;
			m_strCreateTime = (_bstr_t)(var.vt==1?"":var) ;
			var=(prstInfo->GetCollect("描述")) ;
			m_strRemark = (_bstr_t)(var.vt==1?"":var) ;
			Brst=TRUE;
		}	
		prstInfo->Close();
		prstInfo.Release();
	}
	return Brst;
}
//判断方案名称是否存在
BOOL CAnalyseDemo::ExistDemoName(_bstr_t bstrName)
{
	//数据库操作前判断
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析方案"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析方案业务表！"),_T("提示"),0);
		return FALSE;
	}
	if (bstrName.length()<=0)
	{
		MessageBox(NULL,_T("请选择要加载的方案名称！"),_T("提示"),0);
		return FALSE;
	}
	BOOL Brst=FALSE;
	_RecordsetPtr  prstInfo = theBllApp.m_pDB->ExcuteSqlRes("SELECT *  FROM 分析方案  where 名称='"+bstrName+"'",adCmdText);
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
/* 加载方案坐标，结果，范围                                             */
/************************************************************************/
//加载方案面分析范围。前提是先加载方案
_RecordsetPtr CAnalyseDemo::LoadDemoRange()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析范围"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析范围业务表！"),_T("提示"),0);
		return FALSE;
	}
	if (m_strID.length()==0)
		return FALSE;
	return theBllApp.m_pDB->ExcuteSqlRes("SELECT 编号,坐标 FROM 分析范围 WHERE 方案编号= " + m_strID + " )",adCmdText);
}
//加载方案面分析范围：参数：方案编号
_RecordsetPtr CAnalyseDemo::LoadDemoRange( _bstr_t strDemoID )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析范围"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析范围业务表！"),_T("提示"),0);
		return FALSE;
	}
	if (strDemoID.length()<=0)
	{
		MessageBox(NULL,_T("请选择要加载的方案编号！"),_T("提示"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSqlRes("SELECT 编号,坐标 FROM 分析范围 WHERE 方案编号= " + strDemoID,adCmdText);
}
//加载方案面分析范围：参数：方案名称
vector<string> CAnalyseDemo::LoadDemoRangeByName(_bstr_t strDemoName)
{
	vector<string> vCoodis;
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return vCoodis;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析范围"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析范围业务表！"),_T("提示"),0);
		return vCoodis;
	}
	if (m_strID.length()==0)
		return vCoodis;
	string strCoodis;
	_RecordsetPtr Rcst= theBllApp.m_pDB->ExcuteSqlRes("select 坐标  from 分析范围 as t,分析方案 as a  where t.方案编号=a.编号 and 名称='"+strDemoName+"'",adCmdText);
	if (Rcst!=NULL&&!Rcst->adoEOF)
	{
		while(!Rcst->adoEOF)
		{
			strCoodis=(char *)(_bstr_t)Rcst->GetCollect("坐标");
			vCoodis.push_back(strCoodis);
			Rcst->MoveNext();
		}
	}
	return vCoodis;
}
//加载方案类型分析坐标。前提是先加载方案
_RecordsetPtr CAnalyseDemo::LoadDemoCoordinates()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析坐标结果"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析坐标结果业务表！"),_T("提示"),0);
		return FALSE;
	}
	if (m_strID.length()==0)
		return FALSE;
	else
		return theBllApp.m_pDB->ExcuteSqlRes("SELECT 编号,坐标,标识 FROM 分析坐标结果 WHERE 方案编号= " + m_strID + " )",adCmdText);
}
//加载方案类型分析坐标：参数：方案编号
_RecordsetPtr CAnalyseDemo::LoadDemoCoordinates( _bstr_t strDemoID)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析坐标结果"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析坐标结果业务表！"),_T("提示"),0);
		return FALSE;
	}
	if (strDemoID.length()<=0)
	{
		MessageBox(NULL,_T("请选择要加载的方案编号！"),_T("提示"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSqlRes("SELECT 编号,坐标,标识 FROM 分析坐标结果 WHERE 方案编号= " + strDemoID,adCmdText);
}

//加载方案类型分析坐标：参数：方案名称
std::vector<std::vector<string>> CAnalyseDemo::LoadDemoCoodis(_bstr_t strDemoName)
{
	vector<vector<string>> vIds;
	vector<string> vtemp;
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return vIds;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析坐标结果"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析坐标结果业务表！"),_T("提示"),0);
		return vIds;
	}
	if (strDemoName.length()<=0)
	{
		MessageBox(NULL,_T("请选择要加载的方案名称！"),_T("提示"),0);
		return vIds;
	}
	_bstr_t bstrIds,bstNewType="",bstrOldType="";
	string strCoodisTem;
	_RecordsetPtr Rcst= theBllApp.m_pDB->ExcuteSqlRes("select 坐标,标识  from 分析坐标结果 as t,分析方案 as a  where t.方案编号=a.编号 and 名称='" + strDemoName + "'  order by 标识",adCmdText);
	if (Rcst!=NULL&&!Rcst->adoEOF)
	{
		bstNewType=(_bstr_t)Rcst->GetCollect("标识");
		bstrOldType=bstNewType;
		while(!Rcst->adoEOF)
		{
			bstNewType=(_bstr_t)Rcst->GetCollect("标识");
			strCoodisTem=(char*)(_bstr_t)Rcst->GetCollect("坐标");
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
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return vIds;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析类型结果"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析类型结果业务表！"),_T("提示"),0);
		return vIds;
	}
	if (strDemoName.length()<=0)
	{
		MessageBox(NULL,_T("请选择要加载的方案名称！"),_T("提示"),0);
		return vIds;
	}
	string bstrIds;
	_RecordsetPtr Rcst= theBllApp.m_pDB->ExcuteSqlRes("select t.类型ID  from 分析类型结果 as t,分析方案 as a  where t.方案编号=a.编号 and 名称='" + strDemoName + "'",adCmdText);
	if (Rcst!=NULL&&!Rcst->adoEOF)
	{
		while(!Rcst->adoEOF)
		{
			bstrIds=(char*)(_bstr_t)Rcst->GetCollect("类型ID");
			vIds.push_back(bstrIds);
			Rcst->MoveNext();
		}
	}
	return vIds;
}
/************************************************************************/
/* 加载方案                                                             */
/************************************************************************/
//加载所有自画线监控方案分析记录
_RecordsetPtr CAnalyseDemo::LoadAllDrawLineDemo( _bstr_t bstrWhere )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析方案"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析方案业务表！"),_T("提示"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSqlRes("SELECT * FROM 分析方案  WHERE 类型='自画线监控' "  + bstrWhere,adCmdText);
}

void CAnalyseDemo::LoadAllDrawLineDemo(_bstr_t bstrWhere ,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return ;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析方案"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析方案业务表！"),_T("提示"),0);
		return ;
	}

	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(LoadAllDrawLineDemo(bstrWhere),vecField,vecRecordSet,lFieldCounts);
}
//加载所有流行线监控方案分析记录
_RecordsetPtr CAnalyseDemo::LoadAllFRowLineDemo( _bstr_t bstrWhere )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析方案"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析方案业务表！"),_T("提示"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSqlRes("SELECT * FROM 分析方案  WHERE 类型='流行线监控'" + bstrWhere,adCmdText);
}

void CAnalyseDemo::LoadAllFRowLineDemo(_bstr_t bstrWhere ,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return ;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析方案"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析方案业务表！"),_T("提示"),0);
		return ;
	}
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(LoadAllFRowLineDemo(bstrWhere),vecField,vecRecordSet,lFieldCounts);
}

//加载所有点方案分析记录
_RecordsetPtr CAnalyseDemo::LoadAllPointDemo( _bstr_t bstrWhere )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析方案"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析方案业务表！"),_T("提示"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSqlRes("SELECT * FROM 分析方案  WHERE 类型='点'" + bstrWhere,adCmdText);
}

void CAnalyseDemo::LoadAllPointDemo(_bstr_t bstrWhere ,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return ;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析方案"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析方案业务表！"),_T("提示"),0);
		return;
	}
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(LoadAllPointDemo(bstrWhere),vecField,vecRecordSet,lFieldCounts);
}
//加载所有面方案分析记录
_RecordsetPtr CAnalyseDemo::LoadAllRangDemo( _bstr_t bstrWhere )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析方案"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析方案业务表！"),_T("提示"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSqlRes("SELECT * FROM 分析方案  WHERE 类型='面'" + bstrWhere,adCmdText);
}

void CAnalyseDemo::LoadAllRangDemo(_bstr_t bstrWhere ,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析方案"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析方案业务表！"),_T("提示"),0);
		return;
	}
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(LoadAllRangDemo(bstrWhere),vecField,vecRecordSet,lFieldCounts);
}


//加载方案类型分析类型


/************************************************************************/
/*     保存方案                                                         */
/************************************************************************/

//增加自画线监控方案分析记录,
//参数：方案编号，摄像头编号列表，警力编号列表
//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
BOOL CAnalyseDemo::SaveDrawLineDemo(std::vector<_bstr_t> strCameraIds , std::vector<_bstr_t> strPoliceIds)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析方案"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析方案业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t bstrTempSql="";
	_bstr_t bstrValue="";
	std::vector<_bstr_t> vbstrSql;
	_RecordsetPtr prst;
	_CommandPtr m_pCommand=theBllApp.m_pDB->GetCommand();
	_ConnectionPtr m_pConnection=theBllApp.m_pDB->GetConnection();

	//方案
	try
	{
		m_pCommand->ActiveConnection=m_pConnection;
		m_pConnection->BeginTrans();
		//新方案
		if (m_strID.length()==0)
		{
			switch(CDatabaseFactory::m_enumDatabaseType)
			{
			case AccessType:
				m_pCommand->CommandText = "INSERT INTO 分析方案(名称,所属目标,范围,类型,线编号,外框颜色,结果颜色,创建人,创建时间,描述)VALUES('"+
					m_strName+"','"+ m_strToTarger +"',"+m_strRange+",'自画线监控',"+ m_strTypeID +",'"+m_strOuterColor+"','"
					+m_strResultColor + "','"+m_strCreator+"',#"+m_strCreateTime+"#,'" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "SELECT MAX(编号) AS 最大编号 FROM 分析方案 ";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break;
			case SqlServerType:
				m_pCommand->CommandText = "INSERT INTO 分析方案(名称,所属目标,范围,类型,线编号,外框颜色,结果颜色,创建人,创建时间,描述)VALUES('"+
					m_strName+"','"+ m_strToTarger +"',"+m_strRange+",'自画线监控',"+ m_strTypeID +",'"+m_strOuterColor+"','"
					 +m_strResultColor + "','" +m_strCreator+"','"+m_strCreateTime+"','"+ m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "SELECT MAX(编号) AS 最大编号 FROM 分析方案 ";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break;
			case OracleType:
				m_pCommand->CommandText = "INSERT INTO 分析方案(编号,名称,所属目标,范围,类型,线编号,外框颜色,结果颜色,创建人,创建时间,描述)VALUES(分析方案序列.NextVal,'"
					+m_strName+"','"+ m_strToTarger +"',"+m_strRange+",'自画线监控',"+ m_strTypeID +",'"+m_strOuterColor+"','"
					 +m_strResultColor + "','"+m_strCreator+"',to_date('" + m_strCreateTime + "','dd/mm/yyyy'),'" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "select 分析方案序列.currval as 最大编号 from dual";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break ;
			default:
				break;
			}

			//设置编号
			if (prst==NULL && prst->adoEOF)
			{
				m_pConnection->RollbackTrans();
				return FALSE;
			}
			prst->MoveFirst();
			_variant_t var;
			var=prst->GetCollect("最大编号");
			if (var.vt==1)
			{
				m_pConnection->RollbackTrans();
				return FALSE;
			}
			m_strID=((_bstr_t)prst->GetCollect("最大编号"));
			prst->Close();
			prst.Release();
		}
		else //修改方案
		{
			//修改方案信息
			m_pCommand->CommandText = "UPDATE 分析方案 SET  名称 = '"+m_strName+"',所属目标 = '"+m_strToTarger+"',范围 = "+m_strRange+",描述 = '"+m_strRemark+"' WHERE  编号=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
			//清除原来分析结果
			m_pCommand->CommandText = "DELETE  FROM 分析类型结果 WHERE 方案编号=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
		}

		//摄像头类型结果
		for ( vector <_bstr_t>::iterator strSql = strCameraIds.begin(); strSql != strCameraIds.end(); strSql++ )
		{
			bstrValue=((_bstr_t)*strSql);
			bstrTempSql="INSERT INTO 分析类型结果(方案编号,类型,类型ID)VALUES("+m_strID+",'摄像头','"+bstrValue+"')";
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			{
				bstrTempSql="INSERT INTO 分析类型结果(编号,方案编号,类型,类型ID)VALUES(分析类型结果.NextVal,"+m_strID+",'摄像头','"+bstrValue+"')";
			}
			m_pCommand->CommandText = bstrTempSql;
			m_pCommand->Execute(NULL,NULL,adCmdText);
		}
		//警力类型结果
		for ( vector <_bstr_t>::iterator strSql = strPoliceIds.begin(); strSql != strPoliceIds.end(); strSql++ )
		{
			bstrValue=((_bstr_t)*strSql);
			bstrTempSql="INSERT INTO 分析类型结果(方案编号,类型,类型ID)VALUES("+m_strID+",'警力','"+bstrValue+"')";
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			{
				bstrTempSql="INSERT INTO 分析类型结果(编号,方案编号,类型,类型ID)VALUES(分析类型结果.NextVal,"+m_strID+",'警力','"+bstrValue+"')";
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

//增加流行线监控方案分析记录,
//参数：方案编号，摄像头编号列表，警力编号列表
//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
BOOL CAnalyseDemo::SaveFRowLineDemo(std::vector<_bstr_t> strCameraIds , std::vector<_bstr_t> strPoliceIds)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析方案"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析方案业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t bstrTempSql="";
	_bstr_t bstrValue="";
	_RecordsetPtr prst;
	_CommandPtr m_pCommand=theBllApp.m_pDB->GetCommand();
	_ConnectionPtr m_pConnection=theBllApp.m_pDB->GetConnection();

	//方案
	try
	{
		m_pCommand->ActiveConnection=m_pConnection;
		m_pConnection->BeginTrans();
		if (m_strID.length()==0)
		{
			switch(CDatabaseFactory::m_enumDatabaseType)
			{
			case AccessType:
				m_pCommand->CommandText = "INSERT INTO 分析方案(名称,所属目标,范围,类型,线编号,外框颜色,结果颜色,创建人,创建时间,描述)VALUES('"
					+m_strName+"','"+ m_strToTarger +"',"+m_strRange+",'流行线监控',"+ m_strTypeID +",'"+m_strOuterColor+"','"
					 +m_strResultColor + "','"+m_strCreator+"',#"+m_strCreateTime+"#,'" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "SELECT MAX(编号) AS 最大编号 FROM 分析方案 ";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break;
			case SqlServerType:
				m_pCommand->CommandText = "INSERT INTO 分析方案(名称,所属目标,范围,类型,线编号,外框颜色,结果颜色,创建人,创建时间,描述)VALUES('"
					+m_strName+"','"+ m_strToTarger +"',"+m_strRange+",'流行线监控',"+ m_strTypeID +",'"+m_strOuterColor+"','"
					 +m_strResultColor +"','"+m_strCreator+"','"+m_strCreateTime+ "','" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "SELECT MAX(编号) AS 最大编号 FROM 分析方案 ";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break;
			case OracleType:
				m_pCommand->CommandText = "INSERT INTO 分析方案(编号,名称,所属目标,范围,类型,线编号,外框颜色,结果颜色,创建人,创建时间,描述)VALUES(分析方案序列.NextVal,'"
					+m_strName+"','"+ m_strToTarger +"',"+m_strRange+",'流行线监控',"+ m_strTypeID +",'"+m_strOuterColor+"','"
					 +m_strResultColor +"','"+m_strCreator+"',to_date('" + m_strCreateTime + "','dd/mm/yyyy'),'" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "select 分析方案序列.currval as 最大编号 from dual";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break ;
			default:
				break;
			}
			//设置编号
			if (prst==NULL && prst->MoveFirst())
			{
				m_pConnection->RollbackTrans();
				return FALSE;
			}
			prst->MoveFirst();
			_variant_t var;
			var=prst->GetCollect("最大编号");
			if (var.vt==1)
			{
				m_pConnection->RollbackTrans();
				return FALSE;
			}
			m_strID=((_bstr_t)prst->GetCollect("最大编号"));
			prst->Close();
			prst.Release();
		} 
		else
		{
			//修改方案信息
			m_pCommand->CommandText = "UPDATE 分析方案 SET  名称 = '"+m_strName+"',所属目标 = '"+m_strToTarger+"',范围 = "+m_strRange+",描述 = '"+m_strRemark+"' WHERE  编号=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
			//清除原来分析结果
			m_pCommand->CommandText = "DELETE  FROM 分析类型结果 WHERE 方案编号=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
		}
		//摄像头类型结果
		for ( vector <_bstr_t>::iterator strSql = strCameraIds.begin(); strSql != strCameraIds.end(); strSql++ )
		{
			bstrValue=((_bstr_t)*strSql);
			bstrTempSql="INSERT INTO 分析类型结果(方案编号,类型,类型ID)VALUES("+m_strID+",'摄像头','"+bstrValue+"')";
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			{
				bstrTempSql="INSERT INTO 分析类型结果(编号,方案编号,类型,类型ID)VALUES(分析类型结果.NextVal,"+m_strID+",'摄像头','"+bstrValue+"')";
			}
			m_pCommand->CommandText = bstrTempSql;
			m_pCommand->Execute(NULL,NULL,adCmdText);
		}
		//警力类型结果
		for ( vector <_bstr_t>::iterator strSql = strPoliceIds.begin(); strSql != strPoliceIds.end(); strSql++ )
		{
			bstrValue=((_bstr_t)*strSql);
			bstrTempSql="INSERT INTO 分析类型结果(方案编号,类型,类型ID)VALUES("+m_strID+",'警力','"+bstrValue+"')";
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			{
				bstrTempSql="INSERT INTO 分析类型结果(编号,方案编号,类型,类型ID)VALUES(分析类型结果.NextVal,"+m_strID+",'警力','"+bstrValue+"')";
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


//增加点方案分析记录,
//参数：key建筑ID,value坐标列表
//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
BOOL CAnalyseDemo::SavePointDemo(std::map<_bstr_t,std::vector<vector<_bstr_t>>> mBuilding)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析方案"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析方案业务表！"),_T("提示"),0);
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

	//方案
	try
	{
		m_pCommand->ActiveConnection=m_pConnection;
		m_pConnection->BeginTrans();
		if (m_strID.length() == 0 )
		{
			switch(CDatabaseFactory::m_enumDatabaseType)
			{
			case AccessType:
				m_pCommand->CommandText = "INSERT INTO 分析方案(名称,目标点,所属目标,范围,类型,线编号,外框颜色,结果颜色,创建人,创建时间,描述)VALUES('"
					+m_strName+"','"+m_targetPoint+"','"+ m_strToTarger +"',"+m_strRange+",'点',"+ m_strTypeID +",'"+m_strOuterColor+"','"
					 +m_strResultColor + "','"+m_strCreator+"',#"+m_strCreateTime+"#,'" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "SELECT MAX(编号) AS 最大编号 FROM 分析方案 ";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break;
			case SqlServerType:
				m_pCommand->CommandText = "INSERT INTO 分析方案(名称,目标点,所属目标,范围,类型,线编号,外框颜色,结果颜色,创建人,创建时间,描述)VALUES('"
					+m_strName+"','"+m_targetPoint+"','"+ m_strToTarger +"',"+m_strRange+",'点',"+ m_strTypeID +",'"+m_strOuterColor+"','"
					+m_strResultColor + "','"+m_strCreator+"','"+m_strCreateTime+"','" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "SELECT MAX(编号) AS 最大编号 FROM 分析方案 ";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break;
			case OracleType:
				m_pCommand->CommandText = "INSERT INTO 分析方案(编号,名称,目标点,所属目标,范围,类型,线编号,外框颜色,结果颜色,创建人,创建时间,描述)VALUES(分析方案序列.NextVal,'"
					+m_strName+"','"+m_targetPoint+"','"+ m_strToTarger +"',"+m_strRange+",'点',"+ m_strTypeID +",'"+m_strOuterColor
					+"','" +m_strResultColor + "','"+m_strCreator+"',to_date('" + m_strCreateTime + "','dd/mm/yyyy'),'" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "select 分析方案序列.currval as 最大编号 from dual";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break ;
			default:
				break;
			}

			//设置编号
			if (prst==NULL && prst->adoEOF)
			{
				m_pConnection->RollbackTrans();
				return FALSE;
			}
			prst->MoveFirst();
			_variant_t var;
			var=prst->GetCollect("最大编号");
			if (var.vt==1)
			{
				m_pConnection->RollbackTrans();
				return FALSE;
			}
			m_strID=((_bstr_t)prst->GetCollect("最大编号"));
			prst->Close();
			prst.Release();
		} 
		else
		{
			//修改方案信息
			m_pCommand->CommandText = "UPDATE 分析方案 SET  名称 = '"+m_strName+"',所属目标 = '"+m_strToTarger+"',范围 = "+m_strRange+",外框颜色 ='"+m_strOuterColor+"',结果颜色 = '"+m_strResultColor+"',描述 = '"+m_strRemark+"'  WHERE  编号=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
			//清除原来分析结果
			m_pCommand->CommandText = "DELETE  FROM 分析类型结果 WHERE 方案编号=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
			m_pCommand->CommandText = "DELETE  FROM 分析坐标结果 WHERE 方案编号=" + m_strID ;
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
			bstrTempSql="INSERT INTO 分析类型结果(方案编号,类型,类型ID)VALUES("+m_strID+",'建筑','"+bstrValue+"')";
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			{
				bstrTempSql="INSERT INTO 分析类型结果(编号,方案编号,类型,类型ID)VALUES(分析类型结果.NextVal,"+m_strID+",'建筑','"+bstrValue+"')";
			}
			m_pCommand->CommandText = bstrTempSql;
			m_pCommand->Execute(NULL,NULL,adCmdText);

			for ( vector <vector<_bstr_t>>::iterator vvSql = vvcoodis.begin(); vvSql != vvcoodis.end(); vvSql++ )
			{
				vcoodis=*vvSql;
				for (vector<_bstr_t>::iterator vsql=vcoodis.begin();vsql!=vcoodis.end();vsql++)
				{
					bstrCoodinate=(*vsql);
					bstrTempSql="INSERT INTO 分析坐标结果(方案编号,坐标,标识)VALUES(" + m_strID + ",'"  + bstrCoodinate + "','" + strFlag + "')";
					if (CDatabaseFactory::m_enumDatabaseType==OracleType)
					{
						bstrTempSql="INSERT INTO 分析坐标结果(编号,方案编号,坐标,标识)VALUES(分析坐标结果.NextVal," + m_strID + ",'"  + bstrCoodinate + "','" + strFlag + "')";
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
//新补充

BOOL CAnalyseDemo::SavePointDemo(_bstr_t strNewName,vector<_bstr_t> vGuid,vector<vector<_bstr_t>> vvCoodints)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析方案"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析方案业务表！"),_T("提示"),0);
		return FALSE;
	}
	_RecordsetPtr prst;
	_CommandPtr m_pCommand=theBllApp.m_pDB->GetCommand();
	_ConnectionPtr m_pConnection=theBllApp.m_pDB->GetConnection();
	//方案
	try
	{
		m_pCommand->ActiveConnection=m_pConnection;
		m_pConnection->BeginTrans();
		//方案信息录入 begin
		if (m_strID.length() == 0 )
		{
			switch(CDatabaseFactory::m_enumDatabaseType)
			{
			case AccessType:
				m_pCommand->CommandText = "INSERT INTO 分析方案(名称,目标点,所属目标,范围,类型,线编号,外框颜色,结果颜色,创建人,创建时间,描述)VALUES('"
					+m_strName+"','"+m_targetPoint+"','"+ m_strToTarger +"',"+m_strRange+",'点',"+ m_strTypeID +",'"+m_strOuterColor+"','"
					+m_strResultColor + "','"+m_strCreator+"',#"+m_strCreateTime+"#,'" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "SELECT MAX(编号) AS 最大编号 FROM 分析方案 ";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break;
			case SqlServerType:
				m_pCommand->CommandText = "INSERT INTO 分析方案(名称,目标点,所属目标,范围,类型,线编号,外框颜色,结果颜色,创建人,创建时间,描述)VALUES('"
					+m_strName+"','"+m_targetPoint+"','"+ m_strToTarger +"',"+m_strRange+",'点',"+ m_strTypeID +",'"+m_strOuterColor+"','"
					+m_strResultColor + "','"+m_strCreator+"','"+m_strCreateTime+"','" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "SELECT MAX(编号) AS 最大编号 FROM 分析方案 ";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break;
			case OracleType:
				m_pCommand->CommandText = "INSERT INTO 分析方案(编号,名称,目标点,所属目标,范围,类型,线编号,外框颜色,结果颜色,创建人,创建时间,描述)VALUES(分析方案序列.NextVal,'"
					+m_strName+"','"+m_targetPoint+"','"+ m_strToTarger +"',"+m_strRange+",'点',"+ m_strTypeID +",'"+m_strOuterColor
					+"','" +m_strResultColor + "','"+m_strCreator+"',to_date('" + m_strCreateTime + "','dd/mm/yyyy'),'" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "select 分析方案序列.currval as 最大编号 from dual";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break ;
			default:
				break;
			}//end switch

			//设置编号
			if (prst==NULL && prst->adoEOF)
			{
				m_pConnection->RollbackTrans();
				return FALSE;
			}
			prst->MoveFirst();
			_variant_t var;
			var=prst->GetCollect("最大编号");
			if (var.vt==1)
			{
				m_pConnection->RollbackTrans();
				return FALSE;
			}
			m_strID=((_bstr_t)prst->GetCollect("最大编号"));
			prst->Close();
			prst.Release();
		} //end if insert
		else
		{
			//修改方案信息
			m_pCommand->CommandText = "UPDATE 分析方案 SET  名称 = '"+m_strName+"',目标点='"+m_targetPoint+"',所属目标 = '"+m_strToTarger+"',范围 = "+m_strRange+",外框颜色 ='"+m_strOuterColor+"',结果颜色 = '"+m_strResultColor+"',描述 = '"+m_strRemark+"'  WHERE  编号=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
			//清除原来分析结果
			m_pCommand->CommandText = "DELETE  FROM 分析类型结果 WHERE 方案编号=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
			m_pCommand->CommandText = "DELETE  FROM 分析坐标结果 WHERE 方案编号=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
		} //end else update  //方案信息录入end

		//方案结果录入 begin
		_bstr_t bstrTempSql="",bstrGuid="";
		for (std::vector<_bstr_t>::iterator myGuid=vGuid.begin();myGuid!=vGuid.end();myGuid++)
		{
			bstrGuid=*myGuid;
			bstrTempSql="INSERT INTO 分析类型结果(方案编号,类型,类型ID)VALUES("+m_strID+",'建筑','"+bstrGuid+"')";
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			{
				bstrTempSql="INSERT INTO 分析类型结果(编号,方案编号,类型,类型ID)VALUES(分析类型结果.NextVal,"+m_strID+",'建筑','"+bstrGuid+"')";
			}
			m_pCommand->CommandText = bstrTempSql;
			m_pCommand->Execute(NULL,NULL,adCmdText);
		}//end for     //方案结果录入 end

		//方案坐标录入begin
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
				bstrTempSql="INSERT INTO 分析坐标结果(方案编号,坐标,标识)VALUES(" + m_strID + ",'"  + bstrGuid + "','" + strFlag + "')";
				if (CDatabaseFactory::m_enumDatabaseType==OracleType)
				{
					bstrTempSql="INSERT INTO 分析坐标结果(编号,方案编号,坐标,标识)VALUES(分析坐标结果.NextVal," + m_strID + ",'"  + bstrGuid + "','" + strFlag + "')";
				}
				m_pCommand->CommandText = bstrTempSql;
				m_pCommand->Execute(NULL,NULL,adCmdText);
			}
		}// end for 方案坐标录入 end
		
		//提交事务
		m_pConnection->CommitTrans();
	} //end try 
	catch(_com_error e)
	{
		m_pConnection->RollbackTrans();
		return FALSE;
	}
	return TRUE;
}
//增加面方案分析记录,
//参数：key建筑ID,value坐标列表,
//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
BOOL CAnalyseDemo::SaveRangDemo(std::map<_bstr_t,std::vector<vector<_bstr_t>>> mBuilding ,std::vector<_bstr_t> strRanges )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析方案"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析方案业务表！"),_T("提示"),0);
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

	//方案
	try
	{
		m_pCommand->ActiveConnection=m_pConnection;
		m_pConnection->BeginTrans();
		if (m_strID.length()==0)
		{
			switch(CDatabaseFactory::m_enumDatabaseType)
			{
			case AccessType:
				m_pCommand->CommandText = "INSERT INTO 分析方案(名称,所属目标,范围,类型,线编号,外框颜色,结果颜色,创建人,创建时间,描述)VALUES('"
					+m_strName+"','"+ m_strToTarger +"',"+m_strRange+",'面',"+ m_strTypeID +",'"+m_strOuterColor
					+"','" +m_strResultColor + "','"+m_strCreator+"',#"+m_strCreateTime+"#,'" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "SELECT MAX(编号) AS 最大编号 FROM 分析方案 ";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break;
			case SqlServerType:
				m_pCommand->CommandText = "INSERT INTO 分析方案(名称,所属目标,范围,类型,线编号,外框颜色,结果颜色,创建人,创建时间,描述)VALUES('"
					+m_strName+"','"+ m_strToTarger +"',"+m_strRange+",'面',"+ m_strTypeID +",'"+m_strOuterColor
					+"','" +m_strResultColor + "','" +m_strCreator+"','"+m_strCreateTime+"','"+ m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "SELECT MAX(编号) AS 最大编号 FROM 分析方案 ";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break;
			case OracleType:
				m_pCommand->CommandText = "INSERT INTO 分析方案(编号,名称,所属目标,范围,类型,线编号,外框颜色,结果颜色,创建人,创建时间,描述)VALUES(分析方案序列.NextVal,'"
					+m_strName+"','"+ m_strToTarger +"',"+m_strRange+",'面',"+ m_strTypeID +",'"+m_strOuterColor
					+"','" +m_strResultColor + "','" +m_strCreator+"',to_date('" + m_strCreateTime + "','dd/mm/yyyy'),'"+ m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "select 分析方案序列.currval as 最大编号 from dual";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break ;
			default:
				break;
			}

			//设置编号
			if (prst==NULL || prst->adoEOF)
			{
				m_pConnection->RollbackTrans();
				return FALSE;
			}
			prst->MoveFirst();
			_variant_t var;
			var=prst->GetCollect("最大编号");
			if (var.vt==1)
			{
				m_pConnection->RollbackTrans();
				return FALSE;
			}

			m_strID=((_bstr_t)prst->GetCollect("最大编号"));
			prst->Close();
			prst.Release();
		} 
		else
		{
			//修改方案信息
			m_pCommand->CommandText = "UPDATE 分析方案 SET  名称 = '"+m_strName+"',所属目标 = '"+m_strToTarger+"',范围 = "+m_strRange+",外框颜色 ='"+m_strOuterColor+"',结果颜色 = '"+m_strResultColor+"',描述 = '"+m_strRemark+"'  WHERE  编号=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
			//清除原来分析结果
			m_pCommand->CommandText = "DELETE  FROM 分析类型结果 WHERE 方案编号=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
			m_pCommand->CommandText = "DELETE  FROM 分析坐标结果 WHERE 方案编号=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
			m_pCommand->CommandText = "DELETE  FROM 分析范围 WHERE 方案编号=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
		}

		//分析类型和分析坐标
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
			bstrTempSql="INSERT INTO 分析类型结果(方案编号,类型,类型ID)VALUES("+m_strID+",'建筑','"+bstrValue+"')";
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			{
				bstrTempSql="INSERT INTO 分析类型结果(编号,方案编号,类型,类型ID)VALUES(分析类型结果.NextVal,"+m_strID+",'建筑','"+bstrValue+"')";
			}
			m_pCommand->CommandText = bstrTempSql;
			m_pCommand->Execute(NULL,NULL,adCmdText);

			for ( vector <vector<_bstr_t>>::iterator vvSql = vvcoodis.begin(); vvSql != vvcoodis.end(); vvSql++ )
			{
				vcoodis=*vvSql;
				for (vector<_bstr_t>::iterator strSql=vcoodis.begin();strSql!=vcoodis.end();strSql++)
				{
					bstrCoodinate=((_bstr_t)*strSql);
					bstrTempSql="INSERT INTO 分析坐标结果(方案编号,坐标,标识)VALUES(" + m_strID + ",'"  + bstrCoodinate + "','" + strFlag + "')";
					if (CDatabaseFactory::m_enumDatabaseType==OracleType)
					{
						bstrTempSql="INSERT INTO 分析坐标结果(编号,方案编号,坐标,标识)VALUES(分析坐标结果.NextVal," + m_strID + ",'"  + bstrCoodinate + "','" + strFlag + "')";
					}
					m_pCommand->CommandText = bstrTempSql;
					m_pCommand->Execute(NULL,NULL,adCmdText);
				}
			}
		}
		//分析范围
		for ( vector <_bstr_t>::iterator strSql = strRanges.begin(); strSql != strRanges.end(); strSql++ )
		{
			bstrCoodinate=((_bstr_t)*strSql);
			bstrTempSql="INSERT INTO 分析范围(方案编号,坐标)VALUES("+m_strID+",'" + bstrCoodinate + "')";
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			{
				bstrTempSql="INSERT INTO 分析范围(编号,方案编号,坐标)VALUES(分析范围.NextVal,"+m_strID+",'" + bstrCoodinate + "')";
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
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析方案"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析方案业务表！"),_T("提示"),0);
		return FALSE;
	}
	if (m_strName.length()==0)
	{
		MessageBox(NULL,_T("请输入方案名称！"),_T("提示"),0);
		return FALSE;
	}
	if (m_strRange.length()==0)
	{
		MessageBox(NULL,_T("请输入分析范围！"),_T("提示"),0);
		return FALSE;
	}
	_RecordsetPtr prst;
	_CommandPtr m_pCommand=theBllApp.m_pDB->GetCommand();
	_ConnectionPtr m_pConnection=theBllApp.m_pDB->GetConnection();
	//方案信息
	try
	{
		m_pCommand->ActiveConnection=m_pConnection;
		m_pConnection->BeginTrans();
		if (m_strID.length()==0)
		{
			switch(CDatabaseFactory::m_enumDatabaseType)
			{
			case AccessType:
				m_pCommand->CommandText = "INSERT INTO 分析方案(名称,所属目标,范围,类型,线编号,外框颜色,结果颜色,创建人,创建时间,描述)VALUES('"
					+m_strName+"','"+ m_strToTarger +"',"+m_strRange+",'面',"+ m_strTypeID +",'"+m_strOuterColor
					+"','" +m_strResultColor + "','"+m_strCreator+"',#"+m_strCreateTime+"#,'" + m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "SELECT MAX(编号) AS 最大编号 FROM 分析方案 ";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break;
			case SqlServerType:
				m_pCommand->CommandText = "INSERT INTO 分析方案(名称,所属目标,范围,类型,线编号,外框颜色,结果颜色,创建人,创建时间,描述)VALUES('"
					+m_strName+"','"+ m_strToTarger +"',"+m_strRange+",'面',"+ m_strTypeID +",'"+m_strOuterColor
					+"','" +m_strResultColor + "','" +m_strCreator+"','"+m_strCreateTime+"','"+ m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "SELECT MAX(编号) AS 最大编号 FROM 分析方案 ";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break;
			case OracleType:
				m_pCommand->CommandText = "INSERT INTO 分析方案(编号,名称,所属目标,范围,类型,线编号,外框颜色,结果颜色,创建人,创建时间,描述)VALUES(分析方案序列.NextVal,'"
					+m_strName+"','"+ m_strToTarger +"',"+m_strRange+",'面',"+ m_strTypeID +",'"+m_strOuterColor
					+"','" +m_strResultColor + "','" +m_strCreator+"',to_date('" + m_strCreateTime + "','dd/mm/yyyy'),'"+ m_strRemark +"')";
				m_pCommand->Execute(NULL,NULL,adCmdText);
				m_pCommand->CommandText = "select 分析方案序列.currval as 最大编号 from dual";
				prst=m_pCommand->Execute(NULL,NULL,adCmdText);
				break ;
			default:
				break;
			}//end switch
			//设置编号
			if (prst==NULL || prst->adoEOF)
			{
				m_pConnection->RollbackTrans();
				return FALSE;
			}
			prst->MoveFirst();
			_variant_t var;
			var=prst->GetCollect("最大编号");
			if (var.vt==1)
			{
				m_pConnection->RollbackTrans();
				return FALSE;
			}
			m_strID=((_bstr_t)prst->GetCollect("最大编号"));
			prst->Close();
			prst.Release();
		} //end if 插入方案分析信息
		else
		{
			//修改方案信息
			m_pCommand->CommandText = "UPDATE 分析方案 SET  名称 = '"+m_strName+"',所属目标 = '"+m_strToTarger+"',范围 = "+m_strRange+",外框颜色 ='"+m_strOuterColor+"',结果颜色 = '"+m_strResultColor+"',描述 = '"+m_strRemark+"'  WHERE  编号=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
			//清除原来分析结果
			m_pCommand->CommandText = "DELETE  FROM 分析类型结果 WHERE 方案编号=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
			m_pCommand->CommandText = "DELETE  FROM 分析坐标结果 WHERE 方案编号=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
			m_pCommand->CommandText = "DELETE  FROM 分析范围 WHERE 方案编号=" + m_strID ;
			m_pCommand->Execute(NULL,NULL,adCmdText);
		}//end else 结束更新方案分析
		_bstr_t bstrTempSql="";
		_bstr_t bstrValue="";
		//分析建筑结果
		for (std::vector<_bstr_t>::iterator vitem=vGuid.begin();vitem!=vGuid.end();vitem++)
		{
			bstrValue=*vitem;
			bstrTempSql="INSERT INTO 分析类型结果(方案编号,类型,类型ID)VALUES("+m_strID+",'建筑','"+bstrValue+"')";
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			{
				bstrTempSql="INSERT INTO 分析类型结果(编号,方案编号,类型,类型ID)VALUES(分析类型结果.NextVal,"+m_strID+",'建筑','"+bstrValue+"')";
			}
			m_pCommand->CommandText = bstrTempSql;
			m_pCommand->Execute(NULL,NULL,adCmdText);
		}
		//分析坐标结果 
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
				bstrTempSql="INSERT INTO 分析坐标结果(方案编号,坐标,标识)VALUES(" + m_strID + ",'"  + bstrCoodinate + "','" + strFlag + "')";
				if (CDatabaseFactory::m_enumDatabaseType==OracleType)
				{
					bstrTempSql="INSERT INTO 分析坐标结果(编号,方案编号,坐标,标识)VALUES(分析坐标结果.NextVal," + m_strID + ",'"  + bstrCoodinate + "','" + strFlag + "')";
				}
				m_pCommand->CommandText = bstrTempSql;
				m_pCommand->Execute(NULL,NULL,adCmdText);
			}
		}
		//分析范围结果
		for ( vector <_bstr_t>::iterator strSql = strRanges.begin(); strSql != strRanges.end(); strSql++ )
		{
			bstrCoodinate=*strSql;
			bstrTempSql="INSERT INTO 分析范围(方案编号,坐标)VALUES("+m_strID+",'" + bstrCoodinate + "')";
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			{
				bstrTempSql="INSERT INTO 分析范围(编号,方案编号,坐标)VALUES(分析范围.NextVal,"+m_strID+",'" + bstrCoodinate + "')";
			}
			m_pCommand->CommandText = bstrTempSql;
			m_pCommand->Execute(NULL,NULL,adCmdText);
		}
		//提交事务
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
/*    删除方案                                                          */
/************************************************************************/
//删除方案分析记录,前提加载方案
//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
BOOL CAnalyseDemo::Delete()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析方案"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析方案业务表！"),_T("提示"),0);
		return FALSE;
	}
	if (m_strID.length()==0)
	{
		return FALSE;
	}
	std::vector<_bstr_t> vbstrSql;
	vbstrSql.push_back( "DELETE FROM 分析范围 WHERE 方案编号=" + m_strID);
	vbstrSql.push_back( "DELETE FROM 分析坐标结果 WHERE 方案编号=" + m_strID);
	vbstrSql.push_back( "DELETE FROM 分析类型结果 WHERE 方案编号=" + m_strID);
	vbstrSql.push_back( "DELETE FROM 分析方案 WHERE 编号=" + m_strID);
	return theBllApp.m_pDB->ExcuteTrans( vbstrSql  ,adCmdText );
}

//删除方案分析记录，
//不用实例化对象，通过传递编号（用“，"隔开）
BOOL CAnalyseDemo::Delete(_bstr_t strIDS)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("分析方案"))
	{
		MessageBox(NULL,_T("数据库中不存在该分析方案业务表！"),_T("提示"),0);
		return FALSE;
	}
	if (strIDS.length()<=0)
	{
		MessageBox(NULL,_T("请选择要删除的方案记录编号！"),_T("提示"),0);
		return FALSE;
	}
	std::vector<_bstr_t> vbstrSql;
	vbstrSql.push_back( "DELETE FROM 分析范围 WHERE 方案编号 in(" + strIDS+")");
	vbstrSql.push_back( "DELETE FROM 分析坐标结果 WHERE 方案编号 in(" + strIDS+")");
	vbstrSql.push_back( "DELETE FROM 分析类型结果 WHERE 方案编号 in(" + strIDS+")");
	vbstrSql.push_back( "DELETE FROM 分析方案 WHERE 编号 in(" + strIDS+")");
	return theBllApp.m_pDB->ExcuteTrans( vbstrSql  ,adCmdText );
}


/************************************************************************/
/* 创建查询                                                             */
/************************************************************************/
//创建查询
//自画线按创建查询
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