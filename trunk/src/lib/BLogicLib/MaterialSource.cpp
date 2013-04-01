#include "MaterialSource.h"

CMaterialSource CMaterialSource::instance;

CMaterialSource::CMaterialSource(void)
{
}

CMaterialSource::~CMaterialSource(void)
{
}
BOOL CMaterialSource::IsConnectOk()
{
	if (!theBllApp.m_bConntSuccess || !theBllApp.m_pDB->CheckTableNameExist("物质"))
		return FALSE;
	return TRUE;
}

//单体初始化
CMaterialSource & CMaterialSource::Instance()
{
	return instance;
}
//保存物质
BOOL CMaterialSource::Save(std::vector<MATERIALSOURCE> vSource)
{
	if (vSource.size()<1)
		return FALSE;

	std::vector<_bstr_t> vSql;
	MATERIALSOURCE model;
	CString strSQL,strId,strGuid,strType,strName,strCompany,strAddress,strReserves,strProduceArea,strPurpose,strInstruct,strDescipt,strRemark; 
	for (std::vector<MATERIALSOURCE>::iterator it=vSource.begin();it!=vSource.end();it++)
	{
		model=*it;
		strId.Format("%d",model.iId);
		strGuid=model.strGuid.c_str();
		strType=model.strType.c_str();
		strName=model.strName.c_str();
		strCompany=model.strCompany.c_str();
		strAddress=model.strAddress.c_str();
		strReserves.Format("%f",model.strReserves);
		strProduceArea=model.strProduceArea.c_str();
		strPurpose=model.strPurpose.c_str();
		strInstruct=model.strInstruct.c_str();
		strDescipt=model.strDescipt.c_str();
		strRemark=model.strRemark.c_str();

		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			strSQL="INSERT INTO 物质(编号,GUID,物质类型,物质名称,储存公司,储存地址,储备量,物质产地,物质用途,使用说明,描述信息,备注)VALUES(物质序列.NextVal,'"+
			strGuid+"','"+strType+"','"+strName+"','"+strCompany+"','"+strAddress+"',"+strReserves+",'"+strProduceArea
			+"','"+strPurpose+"','"+strInstruct+"','"+strDescipt+"','"+strRemark+"')";
		else
			strSQL="INSERT INTO 物质([GUID],[物质类型],[物质名称],[储存公司],[储存地址],[储备量],[物质产地],[物质用途],[使用说明],[描述信息],[备注])VALUES('"+
			strGuid+"','"+strType+"','"+strName+"','"+strCompany+"','"+strAddress+"',"+strReserves+",'"+strProduceArea
			+"','"+strPurpose+"','"+strInstruct+"','"+strDescipt+"','"+strRemark+"')";
		vSql.push_back(strSQL.GetBuffer(0));
	}
	return theBllApp.m_pDB->ExcuteTrans(vSql,adCmdText);
}
//用编号删除物质
BOOL CMaterialSource::Delete(_bstr_t bstrId)
{
	if (IsConnectOk())
		return theBllApp.m_pDB->ExcuteSql("delete  物质  where 编号=" + bstrId,adCmdText);
	else
		MessageBox(NULL,"数据库访问失败！",0,0);
	return FALSE;
}
//用编号批量删除物质
BOOL CMaterialSource::Detele(std::vector<_bstr_t> vBstrIds)
{
	if (vBstrIds.size()<1)
		return FALSE;
	if (IsConnectOk())
	{
		_bstr_t  bstrIds;
		std::vector<_bstr_t>::iterator it=vBstrIds.begin();
		bstrIds=*it;
		it++;
		for (;it!=vBstrIds.end();it++)
		{
			bstrIds+=",";
			bstrIds+=*it;
		}
		return theBllApp.m_pDB->ExcuteSql("delete  专业队伍  where 编号 in(" + bstrIds +")",adCmdText);
	}
	else
		MessageBox(NULL,"数据库访问失败！",0,0);
	return FALSE;
}
//查询所有物质
std::vector<MATERIALSOURCE> CMaterialSource::GetAllMaterial()
{
	return GetMaterialByCondt("");
}
//分类查询物质
std::vector<MATERIALSOURCE> CMaterialSource::GetMaterialByType(_bstr_t bstrTypeName)
{
	return GetMaterialByCondt("  and 物质类型='"+ bstrTypeName +"'");
}
//条件查询物质
std::vector<MATERIALSOURCE> CMaterialSource::GetMaterialByCondt(_bstr_t bstrCondt)
{
	std::vector<MATERIALSOURCE> vSource;
	MATERIALSOURCE model;
	_RecordsetPtr Ptr=theBllApp.m_pDB->ExcuteSqlRes("SELECT  * FROM 物质  WHERE 1=1 " + bstrCondt ,adCmdText);
	if (Ptr!=NULL)
	{
		_variant_t var;
		while(!Ptr->adoEOF)
		{
			model.iId=(int)Ptr->GetCollect("编号");
			var=Ptr->GetCollect("GUID");
			model.strGuid=(char *)(_bstr_t)(var.vt==1?"":var);
			var=Ptr->GetCollect("储存地址");
			model.strAddress=(char *)(_bstr_t)(var.vt==1?"":var);
			var=Ptr->GetCollect("储存公司");
			model.strCompany=(char *)(_bstr_t)(var.vt==1?"":var);
			var=Ptr->GetCollect("描述信息");
			model.strDescipt=(char *)(_bstr_t)(var.vt==1?"":var);
			var=Ptr->GetCollect("使用说明");
			model.strInstruct=(char *)(_bstr_t)(var.vt==1?"":var);
			var=Ptr->GetCollect("物质名称");
			model.strName=(char *)(_bstr_t)(var.vt==1?"":var);
			var=Ptr->GetCollect("物质产地");
			model.strProduceArea=(char *)(_bstr_t)(var.vt==1?"":var);
			var=Ptr->GetCollect("物质用途");
			model.strPurpose=(char *)(_bstr_t)(var.vt==1?"":var);
			var=Ptr->GetCollect("备注");
			model.strRemark=(char *)(_bstr_t)(var.vt==1?"":var);
			var=Ptr->GetCollect("储备量");
			model.strReserves=(double)(var.vt==1?"0":var);
			var=Ptr->GetCollect("物质类型");
			model.strType==(char *)(_bstr_t)(var.vt==1?"":var);

			vSource.push_back(model);
			Ptr->MoveNext();
		}
		Ptr->Close();
		Ptr.Release();
	}
	return vSource;
}
