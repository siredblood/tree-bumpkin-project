#pragma once
#include "BllHelp.h"
#define MapFld map<_bstr_t,_bstr_t>

class CModelInfo
{
private:
	_bstr_t m_strModID;//GUID
	_bstr_t m_strModPath;//模型路径
	_bstr_t m_strPosX;//位置X
	_bstr_t m_strPosY;//位置Y
	_bstr_t m_strPosZ;//位置Z
	_bstr_t m_strCirX;//旋转X
	_bstr_t m_strCirY;//旋转Y
	_bstr_t m_strCirZ;//旋转Z
	_bstr_t m_strZoomX;//缩放X
	_bstr_t m_strZoomY;//缩放Y
	_bstr_t m_strZoomZ;//缩放Z
	_bstr_t m_strCreator; //创建人
	_bstr_t m_strCreateTime; //创建时间
public:
	CModelInfo(void);
	~CModelInfo(void);
public:
	//返回GUID
	_bstr_t GetID() const { return m_strModID; }

	//返回模型路径
	_bstr_t GetModPath() const { return m_strModPath; }
	//设置模型路径
	void SetModPath(_bstr_t val) { m_strModPath = val; }

	//返回位置X
	_bstr_t GetPosX() const { return m_strPosX; }
	//设置位置X
	void SetPosX(_bstr_t val) { m_strPosX = val; }

	//返回位置Y
	_bstr_t GetPosY() const { return m_strPosY; }
	//设置位置Y
	void SetPosY(_bstr_t val) { m_strPosY = val; }

	//返回位置Z
	_bstr_t GetPosZ() const { return m_strPosZ; }
	//设置位置X
	void SetPosZ(_bstr_t val) { m_strPosZ = val; }

	//返回旋转X
	_bstr_t GetCirX() const { return m_strCirX; }
	//设置旋转X
	void SetCirX(_bstr_t val) { m_strCirX = val; }

	//返回旋转Y
	_bstr_t GetCirY() const { return m_strCirY; }
	//设置旋转Y
	void SetCirY(_bstr_t val) { m_strCirY = val; }

	//返回旋转Z
	_bstr_t GetCirZ() const { return m_strCirZ; }
	//设置旋转Z
	void SetCirZ(_bstr_t val) { m_strCirZ = val; }

	//返回缩放X
	_bstr_t GetZoomX() const { return m_strZoomX; }
	//设置缩放X
	void SetZoomX(_bstr_t val) { m_strZoomX = val; }

	//返回缩放Y
	_bstr_t GetZoomY() const { return m_strZoomY; }
	//设置缩放Y
	void SetZoomY(_bstr_t val) { m_strZoomY = val; }

	//返回缩放Z
	_bstr_t GetZoomZ() const { return m_strZoomZ; }
	//设置缩放Z
	void SetZoomZ(_bstr_t val) { m_strZoomZ = val; }
	//返回创建人
	_bstr_t GetCreator() const { return m_strCreator; }
	//设置创建人
	void SetCreator(_bstr_t val) { m_strCreator = val; }
	//返回创建时间
	_bstr_t GetCreateTime() const { return m_strCreateTime; }
	//设置创建时间
	void SetCreateTime(_bstr_t val) { m_strCreateTime = val; }


	//模型基本信息的数据库操作

	//加载对象模型
	BOOL Load(_bstr_t strGUID);
	_RecordsetPtr LoadInfo(std::vector<_bstr_t> vbstrFieldName);
	//用字符串加载对象模型
	_RecordsetPtr LoadStr(_bstr_t strField);
	//添加字段
	void CModelInfo::AddField(_bstr_t strFieldName, FieldType enumFieldType,int iFieldSize);

	//删除字段
	BOOL DelFiled(_bstr_t strTableName, _bstr_t strFieldName);

	//添加记录
	BOOL Add(std::map<_bstr_t,_bstr_t> &mapFlds);
	BOOL Add(_bstr_t GUID);

	//修改记录
	BOOL Update();

	//删除记录
	BOOL Delete();
	BOOL Delete(CString strGUIDS);

	//查询记录
	_RecordsetPtr QueryAllModel();
	void QueryAllModel(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);

	_RecordsetPtr QueryModelByCondit(_bstr_t STRWhere);
	void QueryModelByCondit(_bstr_t bstrWhere,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//创建查询
	_RecordsetPtr QueryCreateModel(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName);
	void QueryCreateModel(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
};