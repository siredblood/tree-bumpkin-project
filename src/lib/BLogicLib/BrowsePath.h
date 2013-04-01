#pragma once
#include "BllHelp.h"
//路径浏览
struct PATHMODEL
{
	int iId;
	string strName;
	string strTarget;
	double dSpeed;
	bool bLoop;
	std::vector<string> vNodes;
};
class CBrowsePath
{
public:
	CBrowsePath(void);
	~CBrowsePath(void);
private:
	static CBrowsePath instance;
	//判断连接
	BOOL IsConnectOk();
public:
	//单体初始化
	static CBrowsePath & Instance();
	//判断名称是否存在
	BOOL IsNameExiste(_bstr_t bstrName);
	//保存基本信息返回保存编号
	int Save(_bstr_t bstrId,_bstr_t bstrName,_bstr_t bstrSpeed,_bstr_t strTarget,_bstr_t strLoop);
	//保存坐标
	BOOL SaveNodes(_bstr_t bstrId,std::vector<_bstr_t> vpos);
	//用编号删除
	BOOL DeleteById(_bstr_t bstrId);
	//用名称删除
	BOOL DeleteByName(_bstr_t bstrName);
	//用编号加载
	PATHMODEL LoadById(_bstr_t bstrId);
	//用名称加载
	PATHMODEL LoadByName(_bstr_t bstrName);
	//用编号得到节点坐标
	std::vector<string> LoadNodes(_bstr_t bstrId);
	//查询所有路径浏览
	std::vector<PATHMODEL> QueryAllPath();
	//按重点目标查询所有路径浏览
	std::vector<PATHMODEL> QueryPathByTarget(_bstr_t strTarget);
	//查询条件路径浏览
	std::vector<PATHMODEL> QueryPathByCondition(_bstr_t bstrConditions);
};

