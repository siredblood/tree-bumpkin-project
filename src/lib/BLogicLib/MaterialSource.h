#pragma once
#include "BllHelp.h"

struct MATERIALSOURCE
{
	int iId;//编号
	string strGuid;//GUID
	string strType;//物质类型
	string strName; //物质名称
	string strCompany;//储存公司
	string strAddress; //储存地址
	double strReserves;//储备量
	string strProduceArea; //物质产地
	string strPurpose;//物质用途
	string strInstruct;//使用说明
	string strDescipt;//描述信息
	string strRemark;//备注 
};
class CMaterialSource
{
public:
	CMaterialSource(void);
	~CMaterialSource(void);
private:
	static CMaterialSource instance;
	BOOL IsConnectOk();
public:
	//单体初始化
	static CMaterialSource & Instance();
	//保存物质
	BOOL Save(std::vector<MATERIALSOURCE> vSource);
	//用编号删除物质
	BOOL Delete(_bstr_t bstrId);
	//用编号批量删除物质
	BOOL Detele(std::vector<_bstr_t> vBstrIds);
	//查询所有物质
	std::vector<MATERIALSOURCE> GetAllMaterial();
	//分类查询物质
	std::vector<MATERIALSOURCE> GetMaterialByType(_bstr_t bstrTypeName);
	//条件查询物质
	std::vector<MATERIALSOURCE> GetMaterialByCondt(_bstr_t bstrCondt);
};
