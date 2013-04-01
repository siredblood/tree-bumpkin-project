//#include "stdafx.h"
#include "LableMarker.h"

CLableMarker CLableMarker::instance;
CLableMarker::CLableMarker(void)
{
	m_strID="";         //编号
	m_strGUID="";       //GUID
	m_strCoordinate=""; //坐标
	m_strTarget="";     //所属目标
	m_strName="";       //名称
	m_strType="1";       //类型
	m_strCreator="";     //创建人
	m_strCreateTime="2010-1-1";  //创建时间
	m_strRemark="";     //描述
}

CLableMarker::~CLableMarker(void)
{
}

CLableMarker & CLableMarker::Instance()
{
	return instance;
}
//判断标注是否存在
BOOL CLableMarker::CheckLableExist(_bstr_t bstrGUID)
{
	if (bstrGUID.length()<=0)
	{
		MessageBox(NULL,_T("请输入标注模型GUID！"),_T("提示"),0);
		return FALSE;
	}
	//数据库操作前判断
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("标注"))
	{
		MessageBox(NULL,_T("数据库中不存在标注业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t bstrSql="SELECT * FROM 标注 WHERE [GUID] = '" + bstrGUID+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="SELECT * FROM 标注 WHERE GUID = '" + bstrGUID+"'";
	_RecordsetPtr rst=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (rst!=NULL && !rst->adoEOF)
		return TRUE;
	else 
		return FALSE;
}
//标识保存
BOOL CLableMarker::Save(LABLESTRUCT modle)
{
	//数据库操作前判断
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("标注"))
	{
		MessageBox(NULL,_T("数据库中不存在标注业务表！"),_T("提示"),0);
		return FALSE;
	}
	//增加
	m_strGUID=modle.strGUID.c_str();
	m_strName=modle.strText.c_str();
	m_strType=modle.strType.c_str();
	m_strTarget=modle.strTarget.c_str();
	m_strCoordinate=modle.strPos.c_str();
	m_strCreator=modle.strCreator.c_str();
	m_strCreateTime=modle.strCreatTime.c_str();
	if (m_strGUID.length()<=0)
	{
		MessageBox(NULL,_T("请输入标注模型的GUID！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	if (CheckLableExist(m_strGUID))
	{
		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		{
			strSQL = "UPDATE 标注 SET  创建人='"+m_strCreator+"',创建时间=to_date('" + m_strCreateTime + "','dd/mm/yyyy'), 所属目标='"+m_strTarget+"', 坐标 = '" + m_strCoordinate + "',名称 = '"
				+ m_strName + "',类型 = '" + m_strType + "',描述 = '" 
				+ m_strRemark + "'  WHERE GUID = '" + m_strGUID+"'";
		} 
		else
		{
			strSQL = "UPDATE 标注 SET  创建人='"+m_strCreator+"',创建时间='"+m_strCreateTime+"',所属目标='"+m_strTarget+"',坐标 = '" + m_strCoordinate + "',名称 = '"
				+ m_strName + "',类型 = '" + m_strType + "',描述 = '" 
				+ m_strRemark + "'  WHERE  [GUID] = '" + m_strGUID+"'";
		}
	}
	else
	{
		switch(CDatabaseFactory::m_enumDatabaseType)
		{
		case OracleType:
				strSQL="INSERT INTO 标注  (编号,GUID,坐标,名称,所属目标,类型,创建人,创建时间,描述) values (标注序列.NextVal,'"+m_strGUID+"','" + m_strCoordinate + "','"
				+ m_strName+"','" +m_strTarget+ "','" +  m_strType + "','"+m_strCreator+"',"+"to_date('" + m_strCreateTime + "','dd/mm/yyyy'),'" + m_strRemark + "')";
			break;
		case AccessType:
			strSQL="INSERT INTO 标注  ([GUID],坐标,名称,所属目标,类型,创建人,创建时间,描述) values ('"+m_strGUID+"','" + m_strCoordinate + "','"
				+ m_strName +"','" +m_strTarget+ "','" +  m_strType + "','" +m_strCreator+"',#"+m_strCreateTime+"#,'"+ m_strRemark + "')";
			break;
		case SqlServerType:
			strSQL="INSERT INTO 标注  ([GUID],坐标,名称,所属目标,类型,创建人,创建时间,描述) values ('"+m_strGUID+"','" + m_strCoordinate + "','"
				+ m_strName +"','" +m_strTarget+ "','" +  m_strType + "','" +m_strCreator+"','"+m_strCreateTime+"','"+ m_strRemark + "')";
			break;
		default:
			return FALSE;
		}
	}
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CLableMarker::Save(vector<LABLESTRUCT> models)
{
	//数据库操作前判断
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("标注"))
	{
		MessageBox(NULL,_T("数据库中不存在标注业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	vector<_bstr_t> vbstrSqls;
	LABLESTRUCT modle;

	strSQL = "DELETE FROM 标注";//先删除，后插入
	vbstrSqls.push_back(strSQL);
	for (vector<LABLESTRUCT>::iterator item=models.begin();item!=models.end();item++)
	{
		modle=*item;
		m_strGUID=modle.strGUID.c_str();
		m_strName=modle.strText.c_str();
		m_strType=modle.strType.c_str();
		m_strTarget=modle.strTarget.c_str();
		m_strCoordinate=modle.strPos.c_str();
		m_strCreator=modle.strCreator.c_str();
		m_strCreateTime=modle.strCreatTime.c_str();
		CString strEyeable;
		strEyeable.Format("%f",modle.fEyeable);
		m_strEyeable = strEyeable.GetBuffer(0);

		if (m_strGUID.length()>=0)
		{
			switch(CDatabaseFactory::m_enumDatabaseType)
			{
			case OracleType:
				strSQL="INSERT INTO 标注  (编号,GUID,坐标,名称,所属目标,类型,创建人,创建时间,描述,可视范围) values (标注序列.NextVal,'"+m_strGUID+"','" + m_strCoordinate + "','"
					+ m_strName+"','" +m_strTarget+ "','" +  m_strType + "','"+m_strCreator+"',"+"to_date('" + m_strCreateTime + "','dd/mm/yyyy'),'" + m_strRemark 
					+ "'," + m_strEyeable +")";
				break;
			case AccessType:
				strSQL="INSERT INTO 标注  ([GUID],坐标,名称,所属目标,类型,创建人,创建时间,描述,可视范围) values ('"+m_strGUID+"','" + m_strCoordinate + "','"
					+ m_strName +"','" +m_strTarget+ "','" +  m_strType + "','" +m_strCreator+"',#"+m_strCreateTime+"#,'"+ m_strRemark 
					+ "'," + m_strEyeable +")";
				break;
			case SqlServerType:
				strSQL="INSERT INTO 标注  ([GUID],坐标,名称,所属目标,类型,创建人,创建时间,描述,可视范围) values ('"+m_strGUID+"','" + m_strCoordinate + "','"
					+ m_strName +"','" +m_strTarget+ "','" +  m_strType + "','" +m_strCreator+"','"+m_strCreateTime+"','"+ m_strRemark
					+ "'," + m_strEyeable +")";
				break;
			default:
				return FALSE;
			}
			vbstrSqls.push_back(strSQL);
		}
	}
	if (vbstrSqls.size()>0)
		return theBllApp.m_pDB->ExcuteTrans(vbstrSqls,adCmdText);
	else 
		return FALSE;
}


//BOOL CLableMarker::Save(vector<LABLESTRUCT> models)
//{
//	//数据库操作前判断
//	if (!theBllApp.m_bConntSuccess)
//	{
//		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
//		return FALSE;
//	}
//	if (!theBllApp.m_pDB->CheckTableNameExist("标注"))
//	{
//		MessageBox(NULL,_T("数据库中不存在标注业务表！"),_T("提示"),0);
//		return FALSE;
//	}
//	_bstr_t strSQL;
//	vector<_bstr_t> vbstrSqls;
//	LABLESTRUCT modle;
//	for (vector<LABLESTRUCT>::iterator item=models.begin();item!=models.end();item++)
//	{
//		modle=*item;
//		m_strGUID=modle.strGUID.c_str();
//		m_strName=modle.strText.c_str();
//		m_strType=modle.strType.c_str();
//		m_strTarget=modle.strTarget.c_str();
//		m_strCoordinate=modle.strPos.c_str();
//		m_strCreator=modle.strCreator.c_str();
//		m_strCreateTime=modle.strCreatTime.c_str();
//		CString strEyeable;
//		strEyeable.Format("%f",modle.fEyeable);
//		m_strEyeable = strEyeable.GetBuffer(0);
//
//		if (m_strGUID.length()>=0)
//		{
//			if (CheckLableExist(m_strGUID))
//			{
//				if (CDatabaseFactory::m_enumDatabaseType==OracleType)
//				{
//					strSQL = "UPDATE 标注 SET  创建人='"+m_strCreator+"',创建时间=to_date('" + m_strCreateTime + "','dd/mm/yyyy'), 所属目标='"+m_strTarget+"', 坐标 = '" + m_strCoordinate + "',名称 = '"
//						+ m_strName + "',类型 = '" + m_strType + "',描述 = '" 
//						+ m_strRemark + "',可视范围="+ m_strEyeable + " WHERE GUID = '" + m_strGUID+"'";
//				} 
//				else
//				{
//					strSQL = "UPDATE 标注 SET  创建人='"+m_strCreator+"',创建时间='"+m_strCreateTime+"',所属目标='"+m_strTarget+"',坐标 = '" + m_strCoordinate + "',名称 = '"
//						+ m_strName + "',类型 = '" + m_strType + "',描述 = '" 
//						+ m_strRemark + "',可视范围="+ m_strEyeable + " WHERE  [GUID] = '" + m_strGUID+"'";
//				}
//			}
//			else
//			{
//				switch(CDatabaseFactory::m_enumDatabaseType)
//				{
//				case OracleType:
//					strSQL="INSERT INTO 标注  (编号,GUID,坐标,名称,所属目标,类型,创建人,创建时间,描述,可视范围) values (标注序列.NextVal,'"+m_strGUID+"','" + m_strCoordinate + "','"
//						+ m_strName+"','" +m_strTarget+ "','" +  m_strType + "','"+m_strCreator+"',"+"to_date('" + m_strCreateTime + "','dd/mm/yyyy'),'" + m_strRemark 
//						+ "'," + m_strEyeable +")";
//					break;
//				case AccessType:
//					strSQL="INSERT INTO 标注  ([GUID],坐标,名称,所属目标,类型,创建人,创建时间,描述,可视范围) values ('"+m_strGUID+"','" + m_strCoordinate + "','"
//						+ m_strName +"','" +m_strTarget+ "','" +  m_strType + "','" +m_strCreator+"',#"+m_strCreateTime+"#,'"+ m_strRemark 
//						+ "'," + m_strEyeable +")";
//					break;
//				case SqlServerType:
//					strSQL="INSERT INTO 标注  ([GUID],坐标,名称,所属目标,类型,创建人,创建时间,描述,可视范围) values ('"+m_strGUID+"','" + m_strCoordinate + "','"
//						+ m_strName +"','" +m_strTarget+ "','" +  m_strType + "','" +m_strCreator+"','"+m_strCreateTime+"','"+ m_strRemark
//						+ "'," + m_strEyeable +")";
//					break;
//				default:
//					return FALSE;
//				}
//			}
//			vbstrSqls.push_back(strSQL);
//		}
//	}
//	if (vbstrSqls.size()>0)
//		return theBllApp.m_pDB->ExcuteTrans(vbstrSqls,adCmdText);
//	else 
//		return FALSE;
//}


//加载对象模型
BOOL CLableMarker::Load(_bstr_t bstrGUID)
{
	if (bstrGUID.length()<=0)
	{
		MessageBox(NULL,_T("请选择要加载标注！"),_T("提示"),0);
		return FALSE;
	}
	//数据库操作前判断
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("标注"))
	{
		MessageBox(NULL,_T("数据库中不存在标注业务表！"),_T("提示"),0);
		return FALSE;
	}
	BOOL bFlag;
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL="SELECT [编号],[GUID],[坐标],[名称],[所属目标],[类型],[创建人],[创建时间],[描述]  FROM 标注 WHERE [GUID] = '" +bstrGUID+"'" ;
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
	{
		strSQL="SELECT 编号,GUID,坐标,名称,所属目标,类型,创建人,创建时间,描述 FROM 标注 WHERE GUID = '" +bstrGUID+"'" ;
	}
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if (pRecordSet!=NULL)
	{
		if(!pRecordSet->adoEOF)
		{
			bFlag = TRUE;
			_variant_t var;
			var=pRecordSet->GetCollect("编号");
			m_strID = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("GUID");
			m_strGUID = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("坐标");
			m_strCoordinate = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("名称");
			m_strName = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("类型");
			m_strType = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("所属目标");
			m_strTarget = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("创建人");
			m_strCreator = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("创建时间");
			m_strCreateTime = (_bstr_t)(var.vt==1?"2010-1-1":var);
			var=pRecordSet->GetCollect("描述");
			m_strRemark = (_bstr_t)(var.vt==1?"":var);
		}
		pRecordSet->Close();
		pRecordSet.Release();
	}
	return bFlag;
}

//删除标注记录，通过传递GUID
BOOL CLableMarker::Delete(_bstr_t strGUID)
{
	if (strGUID.length()<=0)
	{
		MessageBox(NULL,_T("请选择要删除的标注！"),_T("提示"),0);
		return FALSE;
	}
	//数据库操作前判断
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("标注"))
	{
		MessageBox(NULL,_T("数据库中不存在标注业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL = "DELETE  FROM  标注  WHERE [GUID] = '" + strGUID+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSQL  = "DELETE  FROM  标注  WHERE GUID = '" + strGUID+"'";
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

_RecordsetPtr CLableMarker::QueryAllLableMarker()
{
	return QueryLableMarkerByCondit("");
}

void CLableMarker::QueryAllLableMarker(std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr prst=QueryAllLableMarker();
	if (prst==NULL)
		return;
	CBllHelp::Instance().QueryByCondit(prst,vecField,vecRecordSet,lFieldCounts);
}

_RecordsetPtr CLableMarker::QueryLableMarkerByCondit(_bstr_t STRWhere)
{
	//数据库操作前判断
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("标注"))
	{
		MessageBox(NULL,_T("数据库中不存在标注业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL = "SELECT *  FROM 标注 WHERE 1=1  " + STRWhere;
	return theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
}

void CLableMarker::QueryLableMarkerByCondit(_bstr_t bstrWhere, std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr prst=QueryLableMarkerByCondit(bstrWhere);
	if(prst==NULL)
		return;
	CBllHelp::Instance().QueryByCondit(prst,vecField,vecRecordSet,lFieldCounts);
}
vector<LABLESTRUCT> CLableMarker::LoadLableMark()
{
	std::vector<LABLESTRUCT> te;
	_RecordsetPtr	rst=QueryAllLableMarker();
	if (rst!=NULL)
	{
		_variant_t var;
		while(!rst->adoEOF)
		{
			LABLESTRUCT data;
			var=rst->GetCollect("GUID");
			data.strGUID = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("坐标");
			data.strPos = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("名称");
			data.strText = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("类型");
			data.strType = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("所属目标");
			data.strTarget = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("创建人");
			data.strCreator = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("创建时间");
			data.strCreatTime = (_bstr_t)(var.vt==1?"2010-1-1":var);
			te.push_back(data);
			rst->MoveNext();
		}
	}
	return te;
}
//根据重点目标得到标注
vector<LABLESTRUCT> CLableMarker::LoadLableMark(_bstr_t strTarget)
{
	std::vector<LABLESTRUCT> te;
	_RecordsetPtr	rst=QueryLableMarkerByCondit("  and 所属目标='"+strTarget+"'");
	if (rst!=NULL)
	{
		_variant_t var;
		while(!rst->adoEOF)
		{
			LABLESTRUCT data;
			var=rst->GetCollect("GUID");
			data.strGUID = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("坐标");
			data.strPos = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("名称");
			data.strText = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("类型");
			data.strType = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("所属目标");
			data.strTarget = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("创建人");
			data.strCreator = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("创建时间");
			data.strCreatTime = (_bstr_t)(var.vt==1?"2010-1-1":var);
			var=rst->GetCollect("可视范围");
			data.fEyeable = (float)(var.vt==1?300.f:var);
			te.push_back(data);
			rst->MoveNext();
		}
	}
	return te;
}
/************************************************************************/
/* 创建人和创建时间查询                                                 */
/************************************************************************/
//查询创建人和创建时间记录,查询开始时间strBeginTime和结束时间strEndTime和创建人为strCreatorName的标注,如果忽略时间则时间值为"",如果忽略创建人则值为"";
_RecordsetPtr  CLableMarker::QueryCreateMarker(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName)
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
	return QueryLableMarkerByCondit(strSqlwhere);
}
//查询创建人和创建时间记录,查询开始时间strBeginTime和结束时间strEndTime和创建人为strCreatorName的标注,如果忽略时间则时间值为"",如果忽略创建人则值为"";
void CLableMarker::QueryCreateMarker(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName, std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr prst=QueryCreateMarker( strBeginTime, strEndTime, strCreatorName );
	if(prst==NULL)
		return;
	CBllHelp::Instance().QueryByCondit(prst,vecField,vecRecordSet,lFieldCounts);
}
//查询创建人和创建时间标注名称,查询开始时间strBeginTime和结束时间strEndTime和创建人为strCreatorName的标注,如果忽略时间则时间值为"",如果忽略创建人则值为"";
vector<LABLESTRUCT> CLableMarker::LoadCreateMark(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName)
{
	std::vector<LABLESTRUCT> te;
	_RecordsetPtr	rst=QueryCreateMarker( strBeginTime, strEndTime, strCreatorName );
	if (rst!=NULL)
	{
		while(!rst->adoEOF)
		{
			LABLESTRUCT data;
			data.strText = ((char *)(_bstr_t)rst->GetCollect("名称"));
			data.strGUID = ((char *)(_bstr_t)rst->GetCollect("GUID"));
			data.strPos = ((char *)(_bstr_t)rst->GetCollect("坐标"));
			data.strType = ((char *)(_bstr_t)rst->GetCollect("类型"));
			data.strCreator=((char *)(_bstr_t)rst->GetCollect("创建人"));
			data.strCreatTime=((char *)(_bstr_t)rst->GetCollect("创建时间"));
			te.push_back(data);
			rst->MoveNext();
		}
	}
	return te;
}

void CLableMarker::LoadMarks( const _bstr_t &strCondit, std::vector< LABLESTRUCT > &vMark )
{
	_RecordsetPtr	rst=QueryLableMarkerByCondit( strCondit );
	if (rst!=NULL)
	{
		_variant_t var;
		while(!rst->adoEOF)
		{
			LABLESTRUCT data;
			var=rst->GetCollect("GUID");
			data.strGUID = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("坐标");
			data.strPos = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("名称");
			data.strText = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("类型");
			data.strType = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("所属目标");
			data.strTarget = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("创建人");
			data.strCreator = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("创建时间");
			data.strCreatTime = (_bstr_t)(var.vt==1?"2010-1-1":var);
			var=rst->GetCollect("可视范围");
			data.fEyeable = (float)(var.vt==1?300.f:var);
			vMark.push_back(data);
			rst->MoveNext();
		}
	}
}