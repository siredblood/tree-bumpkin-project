#pragma once
#include "BllHelp.h"
//成员
struct TEAMMENBER
{
		int iId;			 //编号
		string strGuid;		 //GUID
		string strName;		 //姓名
		string strSex;		 //性别
		int iAge;			 //年龄
		string strProfession;//职业
		string strJobPosition;//职位
		string strCompany;	  //所属公司
		string strAddress;    //地址
		string strMobilePhone; //联系手机
		string strContacts;    //其它联系方式
		string strGoodAt;     //特长
		string strDetails;    //详细信息
		string strRemark;     //备注
		int iTeamId;          //所属组
};
//专业队伍或专家组
struct TEAMWORKMODEL
{
	int iID;			//编号
	string strTeamId;	//队伍编号
	string strName;		//名称
	string strType;     //类型
	string strArea;     //区域
	string strAddress;  //地址
	string strDetail;   //详细信息
	string strRemark;   //备注
	string strMark;     //标识
	std::vector<TEAMMENBER> vMenbers; //成员
};
class CTeamWork
{
public:
	CTeamWork(void);
	~CTeamWork(void);
private:
	static CTeamWork instance;
	BOOL IsConnectOk();
	std::vector<TEAMMENBER> GetMenbers(_bstr_t bstrId);

public:
	//单体初始化
	static CTeamWork & Instance();

///////////////////////////////判断///////////////////////////////////////////
	//判断队伍名称是否存在
	BOOL CheckTeamName(_bstr_t bstrName);
	//判断专家组名称是否存在
	BOOL CheckExpertName(_bstr_t bstrName);
////////////////////////////保存//////////////////////////////////////////////
	//保存队伍信息返回编号
	int SaveTeam(TEAMWORKMODEL tmodel);
	//保存专家信息返回编号
	int SaveExpert(TEAMWORKMODEL tmodel);
	//保存成员
	BOOL SaveMenbers(int iId, std::vector<TEAMMENBER> vmenber);
//////////////////////////////删除////////////////////////////////////////////
	//用编号删除
	BOOL Delete(_bstr_t bstrId);
	//用编号批量删除
	BOOL Delete(std::vector<_bstr_t> vstrId);
//////////////////////////////查询////////////////////////////////////////////	
	//用编号加载队伍组或专家组信息
	TEAMWORKMODEL LoadInfoById(_bstr_t bstrId);
	//用名称加载队伍信息
	TEAMWORKMODEL LoadTeamByName(_bstr_t bstrName);
	//用名称加载专家组信息
	TEAMWORKMODEL LoadExpertByName(_bstr_t bstrName);
	//条件查询队伍组集合
	std::vector<TEAMWORKMODEL> QueryTeamWork(_bstr_t bstrConditions);
	//条件查询专家组集合
	std::vector<TEAMWORKMODEL> QueryExperts(_bstr_t bstrConditions);
};
