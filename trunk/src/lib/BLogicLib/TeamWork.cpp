#include "TeamWork.h"

CTeamWork CTeamWork::instance;

CTeamWork::CTeamWork(void)
{
}

CTeamWork::~CTeamWork(void)
{
}

BOOL CTeamWork::IsConnectOk()
{
	if (!theBllApp.m_bConntSuccess || !theBllApp.m_pDB->CheckTableNameExist("专业队伍"))
		return FALSE;
	return TRUE;
}
std::vector<TEAMMENBER> CTeamWork::GetMenbers(_bstr_t bstrId)
{
	std::vector<TEAMMENBER> vmenbers;
	TEAMMENBER model;
	_RecordsetPtr RcstPrt;
	RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from 成员  where 所属组="+ bstrId,adCmdText);
	if ( RcstPrt!=NULL )	
	{
		while (!RcstPrt->adoEOF)
		{
			_variant_t var;
			model.iId=(int)RcstPrt->GetCollect("编号");
			model.iAge=(int)RcstPrt->GetCollect("年龄");
			model.iTeamId=(int)RcstPrt->GetCollect("所属组");
			var=RcstPrt->GetCollect("地址");
			model.strAddress=(char*)((_bstr_t)(var.vt==1?"":var));
			var=RcstPrt->GetCollect("所属公司");
			model.strCompany=(char*)((_bstr_t)(var.vt==1?"":var));
			var=RcstPrt->GetCollect("其它联系");
			model.strContacts=(char*)((_bstr_t)(var.vt==1?"":var));
			var=RcstPrt->GetCollect("详细信息");
			model.strDetails=(char*)((_bstr_t)(var.vt==1?"":var));
			var=RcstPrt->GetCollect("特长");
			model.strGoodAt=(char*)((_bstr_t)(var.vt==1?"":var));
			var=RcstPrt->GetCollect("GUID");
			model.strGuid=(char*)((_bstr_t)(var.vt==1?"":var));
			var=RcstPrt->GetCollect("职位");
			model.strJobPosition=(char*)((_bstr_t)(var.vt==1?"":var));
			var=RcstPrt->GetCollect("联系手机");
			model.strMobilePhone=(char*)((_bstr_t)(var.vt==1?"":var));
			var=RcstPrt->GetCollect("姓名");
			model.strName=(char*)((_bstr_t)(var.vt==1?"":var));
			var=RcstPrt->GetCollect("职业");
			model.strProfession=(char*)((_bstr_t)(var.vt==1?"":var));
			var=RcstPrt->GetCollect("备注");
			model.strRemark=(char*)((_bstr_t)(var.vt==1?"":var));
			var=RcstPrt->GetCollect("性别");
			model.strSex=(char*)((_bstr_t)(var.vt==1?"":var));
			var=RcstPrt->GetCollect("性别");
			vmenbers.push_back(model);
			RcstPrt->MoveNext();
		}
		RcstPrt->Close();
		RcstPrt.Release();
	}
	return vmenbers;
}

//单体初始化
CTeamWork & CTeamWork::Instance()
{
	return instance;
}
///////////////////////////////判断///////////////////////////////////////////
//判断队伍名称是否存在
BOOL CTeamWork::CheckTeamName(_bstr_t bstrName)
{
	_RecordsetPtr RcstPrt;
	BOOL BExist=FALSE;
	if (IsConnectOk())
	{
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from 专业队伍  where 标识='专业队伍' and  名称='"+ bstrName+"'",adCmdText);
		if (RcstPrt!=NULL )
		{
			if (!RcstPrt->adoEOF)
				BExist=TRUE;
			RcstPrt->Close();
			RcstPrt.Release();
		}	
	}
	else
		MessageBox(NULL,"数据库访问失败！",0,0);
	return BExist;
}
//判断专家组名称是否存在
BOOL CTeamWork::CheckExpertName(_bstr_t bstrName)
{
	_RecordsetPtr RcstPrt;
	BOOL BExist=FALSE;
	if (IsConnectOk())
	{
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from 专业队伍  where 标识='专家组' and  名称='"+ bstrName+"'",adCmdText);
		if (RcstPrt!=NULL )
		{
			if (!RcstPrt->adoEOF)
				BExist=TRUE;
			RcstPrt->Close();
			RcstPrt.Release();
		}	
	}
	else
		MessageBox(NULL,"数据库访问失败！",0,0);
	return BExist;
}
////////////////////////////保存//////////////////////////////////////////////
//保存队伍信息返回编号
int CTeamWork::SaveTeam(TEAMWORKMODEL tmodel)
{
	CString strId;
	strId.Format("%d",tmodel.iID);
	CString strAddress=tmodel.strAddress.c_str();
	CString strArea= tmodel.strArea.c_str();
	CString strDetail = tmodel.strDetail.c_str();
	CString strMark = tmodel.strMark.c_str();
	CString strName = tmodel.strName.c_str();
	CString strRemark = tmodel.strRemark.c_str();
	CString strTeamId= tmodel.strTeamId.c_str();
	CString strType = tmodel.strType.c_str();
	CString strSql;

	if (tmodel.iID>0) //更新
			strSql="UPDATE 专业队伍 SET 组编号 = '"+strTeamId+"',名称 ='"+strName+"',类型 = '"+ strType+"',区域 = '"+strArea+"',地址 = '"+strAddress+"',详细信息 = '"+strDetail+"',备注 = '"+strRemark+"'  WHERE 编号="+strId;
	else //新增
		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			strSql="INSERT INTO 专业队伍(编号,组编号,名称,类型,区域,地址,详细信息,备注,标识)VALUES(专业队伍序列.NextVal,'"+strTeamId+"','"+strName+"','"+strType+"','"+strArea+"','"+strAddress+"','"+strDetail+"','"+strRemark+"','专业队伍')";
		else
			strSql="INSERT INTO 专业队伍([组编号],[名称],[类型],[区域],[地址],[详细信息],[备注],[标识])VALUES('"+strTeamId+"','"+strName+"','"+strType+"','"+strArea+"','"+strAddress+"','"+strDetail+"','"+strRemark+"','专业队伍')";
		
	theBllApp.m_pDB->ExcuteSql(strSql.GetBuffer(0),adCmdText);
	strSql="select MAX(编号) as 最大编号 from 专业队伍";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSql="select 分析方案序列.currval as 最大编号 from dual";
	_RecordsetPtr Ptr=theBllApp.m_pDB->ExcuteSqlRes(strSql.GetBuffer(),adCmdText);
	int thisId=-1;
	if (Ptr!=NULL)
	{
		if (!Ptr->adoEOF)
		{
			_variant_t var;
			var=Ptr->GetCollect("最大编号");
			thisId= (int)((var.vt==1?"-1":var));
		}
		Ptr->Close();
		Ptr.Release();
	}	
	return thisId;
}
//保存专家信息返回编号
int CTeamWork::SaveExpert(TEAMWORKMODEL tmodel)
{
	CString strId;
	strId.Format("%d",tmodel.iID);
	CString strAddress=tmodel.strAddress.c_str();
	CString strArea= tmodel.strArea.c_str();
	CString strDetail = tmodel.strDetail.c_str();
	CString strMark = tmodel.strMark.c_str();
	CString strName = tmodel.strName.c_str();
	CString strRemark = tmodel.strRemark.c_str();
	CString strTeamId= tmodel.strTeamId.c_str();
	CString strType = tmodel.strType.c_str();
	CString strSql;

	if (tmodel.iID>0) //更新
		strSql="UPDATE 专业队伍 SET 组编号 = '"+strTeamId+"',名称 ='"+strName
		+"',类型 = '"+ strType+"',区域 = '"+strArea+"',地址 = '"+strAddress
		+"',详细信息 = '"+strDetail+"',备注 = '"+strRemark+"'  WHERE 编号="+strId;
	else //新增
		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			strSql="INSERT INTO 专业队伍(编号,组编号,名称,类型,区域,地址,详细信息,备注,标识)VALUES(专业队伍序列.NextVal,'"+
			strTeamId+"','"+strName+"','"+strType+"','"+strArea+"','"+strAddress+"','"+strDetail
			+"','"+strRemark+"','专家组')";
		else
			strSql="INSERT INTO 专业队伍([组编号],[名称],[类型],[区域],[地址],[详细信息],[备注],[标识])VALUES('"+
			strTeamId+"','"+strName+"','"+strType+"','"+strArea+"','"+strAddress+"','"+strDetail
			+"','"+strRemark+"','专家组')";

	theBllApp.m_pDB->ExcuteSql(strSql.GetBuffer(0),adCmdText);
	strSql="select MAX(编号) as 最大编号 from 专业队伍";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSql="select 分析方案序列.currval as 最大编号 from dual";
	_RecordsetPtr Ptr=theBllApp.m_pDB->ExcuteSqlRes(strSql.GetBuffer(),adCmdText);
	int IthisId = -1;
	if (Ptr!=NULL)
	{
		if (!Ptr->adoEOF)
		{
			_variant_t var;
			var=Ptr->GetCollect("最大编号");
			IthisId = (int)((var.vt==1?"-1":var));
		}
		Ptr->Close();
		Ptr.Release();
	}
	return IthisId;
}
//保存成员
BOOL CTeamWork::SaveMenbers(int iId, std::vector<TEAMMENBER> vmenber)
{
	if (iId>0 && vmenber.size()>0 )
	{
		CString strSql,strId,strGuid,strName,strSex,strAge,strJob,strPosition,strCompany,strAddress,strPhone,strContact,strGoodAt,strDetails,strRemark;
		strId.Format("%d",iId);

		std::vector<_bstr_t> vSql;

		strSql="delete from 成员 where 所属组="+strId;
		vSql.push_back(strSql.GetBuffer(0));

		TEAMMENBER model;

		for (std::vector<TEAMMENBER>::iterator it=vmenber.begin();it!=vmenber.end();it++)
		{
			model=*it;
			strGuid=model.strGuid.c_str();
			strName=model.strName.c_str();
			strSex=model.strSex.c_str();
			strAge.Format("%d",model.iAge);
			strJob=model.strProfession.c_str();
			strPosition=model.strJobPosition.c_str();
			strCompany=model.strCompany.c_str();
			strAddress=model.strAddress.c_str();
			strPhone=model.strMobilePhone.c_str();
			strContact=model.strContacts.c_str();
			strGoodAt=model.strGoodAt.c_str();
			strDetails=model.strDetails.c_str();
			strRemark=model.strRemark.c_str();

			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
				strSql="INSERT INTO 成员(编号,GUID,姓名,性别,年龄,职业,职位,所属公司,地址,联系手机,其它联系,特长,详细信息,备注,所属组)VALUES(成员序列.NextVal,'"+ 
				strGuid +"','"+ strName +"','"+strSex+"',"+strAge+",'"+strJob+"','"+strPosition+"','"+strCompany+"','"+
				strAddress+"','"+strPhone+"','"+strContact+"','"+strGoodAt+"','"+strDetails+"','"+strRemark+"',"+strId+")";
			else
				strSql="INSERT INTO 成员([GUID],[姓名],[性别],[年龄],[职业],[职位],[所属公司],[地址],[联系手机],[其它联系],[特长],[详细信息],[备注],[所属组])VALUES('"+ 
				strGuid +"','"+ strName +"','"+strSex+"',"+strAge+",'"+strJob+"','"+strPosition+"','"+strCompany+"','"+
				strAddress+"','"+strPhone+"','"+strContact+"','"+strGoodAt+"','"+strDetails+"','"+strRemark+"',"+strId+")";
			vSql.push_back(strSql.GetBuffer());
		}
		return theBllApp.m_pDB->ExcuteTrans(vSql,adCmdText);
	}
	return FALSE;
}
//////////////////////////////删除////////////////////////////////////////////
//用编号删除
BOOL CTeamWork::Delete(_bstr_t bstrId)
{
	if (IsConnectOk())
	{
		std::vector<_bstr_t> vSql;
		_bstr_t bstrSql="delete  专业队伍  where 编号=" + bstrId ;
		vSql.push_back(bstrSql);
		bstrSql = "delete  成员  where 所属组=" + bstrId ;
		vSql.push_back(bstrSql);
		return theBllApp.m_pDB->ExcuteTrans(vSql,adCmdText);
	}
	else
		MessageBox(NULL,"数据库访问失败！",0,0);
	return FALSE;
}
//用编号批量删除
BOOL CTeamWork::Delete(std::vector<_bstr_t> vstrId)
{
	if (vstrId.size()<1)
		return FALSE;
	if (IsConnectOk())
	{
		_bstr_t  bstrIds;
		std::vector<_bstr_t>::iterator it=vstrId.begin();
		bstrIds=*it;
		it++;
		for (;it!=vstrId.end();it++)
		{
			bstrIds+=",";
			bstrIds+=*it;
		}

		std::vector<_bstr_t> vSql;
		_bstr_t bstrSql="delete  专业队伍  where 编号 in(" + bstrIds +")";
		vSql.push_back(bstrSql);
		bstrSql = "delete  成员  where 所属组 in(" + bstrIds +")";
		vSql.push_back(bstrSql);
		return theBllApp.m_pDB->ExcuteTrans(vSql,adCmdText);
	}
	else
		MessageBox(NULL,"数据库访问失败！",0,0);
	return FALSE;
}
//////////////////////////////查询////////////////////////////////////////////	
//用编号加载队伍组或专家组信息
TEAMWORKMODEL CTeamWork::LoadInfoById(_bstr_t bstrId)
{
	TEAMWORKMODEL model;
	if (IsConnectOk())
	{
		_RecordsetPtr RcstPrt;
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from 专业队伍  where 编号="+ bstrId,adCmdText);
		if ( RcstPrt!=NULL )	
		{
			if (!RcstPrt->adoEOF)
			{
				_variant_t var;
				model.iID=(int)RcstPrt->GetCollect("编号");
				var=RcstPrt->GetCollect("地址");
				model.strAddress=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("区域");
				model.strArea=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("详细信息");
				model.strDetail=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("名称");
				model.strName=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("备注");
				model.strRemark=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("队伍");
				model.strTeamId=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("类型");
				model.strType=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("标识");
				model.strMark=(char*)((_bstr_t)(var.vt==1?"":var));
				model.vMenbers=GetMenbers((_bstr_t)RcstPrt->GetCollect("编号"));
			}
			RcstPrt->Close();
			RcstPrt.Release();
		}
	}
	else
		MessageBox(NULL,"数据库访问失败！",0,0);
	return model;
}
//用名称加载队伍信息
TEAMWORKMODEL CTeamWork::LoadTeamByName(_bstr_t bstrName)
{
	TEAMWORKMODEL model;
	if (IsConnectOk())
	{
		_RecordsetPtr RcstPrt;
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from 专业队伍  where 标识='专业队伍' and 名称='"+ bstrName+"'",adCmdText);
		if ( RcstPrt!=NULL )	
		{
			if (!RcstPrt->adoEOF)
			{
				_variant_t var;
				model.iID=(int)RcstPrt->GetCollect("编号");
				var=RcstPrt->GetCollect("地址");
				model.strAddress=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("区域");
				model.strArea=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("详细信息");
				model.strDetail=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("名称");
				model.strName=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("备注");
				model.strRemark=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("队伍");
				model.strTeamId=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("类型");
				model.strType=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("标识");
				model.strMark=(char*)((_bstr_t)(var.vt==1?"":var));
				model.vMenbers=GetMenbers((_bstr_t)RcstPrt->GetCollect("编号"));
			}
			RcstPrt->Close();
			RcstPrt.Release();
		}
	}
	else
		MessageBox(NULL,"数据库访问失败！",0,0);
	return model;
}
//用名称加载专家组信息
TEAMWORKMODEL CTeamWork::LoadExpertByName(_bstr_t bstrName)
{
	TEAMWORKMODEL model;
	if (IsConnectOk())
	{
		_RecordsetPtr RcstPrt;
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from 专业队伍  where 标识='专家组' and 名称='"+ bstrName+"'",adCmdText);
		if ( RcstPrt!=NULL )	
		{
			if (!RcstPrt->adoEOF)
			{
				_variant_t var;
				model.iID=(int)RcstPrt->GetCollect("编号");
				var=RcstPrt->GetCollect("地址");
				model.strAddress=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("区域");
				model.strArea=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("详细信息");
				model.strDetail=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("名称");
				model.strName=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("备注");
				model.strRemark=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("队伍");
				model.strTeamId=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("类型");
				model.strType=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("标识");
				model.strMark=(char*)((_bstr_t)(var.vt==1?"":var));
				model.vMenbers=GetMenbers((_bstr_t)RcstPrt->GetCollect("编号"));
			}
			RcstPrt->Close();
			RcstPrt.Release();
		}
	}
	else
		MessageBox(NULL,"数据库访问失败！",0,0);
	return model;
}
//条件查询队伍组集合
std::vector<TEAMWORKMODEL> CTeamWork::QueryTeamWork(_bstr_t bstrConditions)
{
	std::vector<TEAMWORKMODEL> vteams;
	if (IsConnectOk())
	{
		_RecordsetPtr RcstPrt;
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from 专业队伍  where 标识='专业队伍'  "+ bstrConditions,adCmdText);
		if ( RcstPrt!=NULL )	
		{
			_variant_t var;
			TEAMWORKMODEL model;
			while (!RcstPrt->adoEOF)
			{
				model.iID=(int)RcstPrt->GetCollect("编号");
				var=RcstPrt->GetCollect("地址");
				model.strAddress=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("区域");
				model.strArea=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("详细信息");
				model.strDetail=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("名称");
				model.strName=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("备注");
				model.strRemark=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("队伍");
				model.strTeamId=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("类型");
				model.strType=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("标识");
				model.strMark=(char*)((_bstr_t)(var.vt==1?"":var));
				model.vMenbers=GetMenbers((_bstr_t)RcstPrt->GetCollect("编号"));
				vteams.push_back(model);
				RcstPrt->MoveNext();
			}
			RcstPrt->Close();
			RcstPrt.Release();
		}
	}
	else
		MessageBox(NULL,"数据库访问失败！",0,0);
	return vteams;
}
//条件查询专家组集合
std::vector<TEAMWORKMODEL> CTeamWork::QueryExperts(_bstr_t bstrConditions)
{
	std::vector<TEAMWORKMODEL> vExperts;
	if (IsConnectOk())
	{
		_RecordsetPtr RcstPrt;
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from 专业队伍  where 标识='专家组' "+ bstrConditions,adCmdText);
		if ( RcstPrt!=NULL )	
		{
			TEAMWORKMODEL model;
			_variant_t var;
			while (!RcstPrt->adoEOF)
			{
				model.iID=(int)RcstPrt->GetCollect("编号");
				var=RcstPrt->GetCollect("地址");
				model.strAddress=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("区域");
				model.strArea=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("详细信息");
				model.strDetail=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("名称");
				model.strName=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("备注");
				model.strRemark=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("队伍");
				model.strTeamId=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("类型");
				model.strType=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("标识");
				model.strMark=(char*)((_bstr_t)(var.vt==1?"":var));
				model.vMenbers=GetMenbers((_bstr_t)RcstPrt->GetCollect("编号"));
				vExperts.push_back(model);
				RcstPrt->MoveNext();
			}
			RcstPrt->Close();
			RcstPrt.Release();
		}
	}
	else
		MessageBox(NULL,"数据库访问失败！",0,0);
	return vExperts;
}