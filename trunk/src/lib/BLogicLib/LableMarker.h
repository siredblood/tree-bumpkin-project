#pragma once
#include "BllHelp.h"

struct LABLESTRUCT
{
	std::string strText;
	std::string strGUID;
	std::string strPos;
	std::string	strType; 
	std::string strTarget;
	std::string strCreator;
	std::string strCreatTime;
	std::string strRemark;
	float fEyeable;
};

class CLableMarker
{
public:
	CLableMarker(void);
	~CLableMarker(void);
private:
	//标注字段
	_bstr_t m_strID;         //编号
	_bstr_t m_strGUID;       //GUID
	_bstr_t m_strCoordinate; //坐标
	_bstr_t m_strTarget;     //所属目标 
	_bstr_t m_strName;       //名称
	_bstr_t m_strType;       //类型
	_bstr_t m_strCreator;     //创建人
	_bstr_t m_strCreateTime;  //创建时间
	_bstr_t m_strRemark;     //描述
	_bstr_t m_strEyeable;   //可视范围

	static CLableMarker instance;
public:
	//标注属性获取和设置

	//返回编号
	_bstr_t GetID() const { return m_strID; }
	////设置编号
	//void SetID(_bstr_t val) { m_strID = val; }

	//返回编号
	_bstr_t GetGUID() const { return m_strGUID; }
	//设置编号
	void SetGUID(_bstr_t val) { m_strGUID = val; }
	//返回坐标
	_bstr_t GetCoordinate() const { return m_strCoordinate; }
	//设置坐标
	void SetCoordinate(_bstr_t val) { m_strCoordinate = val; }
	//返回重点目标
	_bstr_t GetTarget() const { return m_strTarget; }
	//设置重点目标
	void SetTarget(_bstr_t val) { m_strTarget = val; }

	//返回名称
	_bstr_t GetName() const { return m_strName; }
	//设置名称
	void SetName(_bstr_t val) { m_strName = val; }

	//返回类型
	_bstr_t GetType() const { return m_strType; }
	//设置类型
	void SetType(_bstr_t val) { m_strType = val; }
	//返回创建人
	_bstr_t GetCreator() const { return m_strCreator; }
	//设置创建人
	void SetCreator(_bstr_t val) { m_strCreator = val; }
	//返回创建时间
	_bstr_t GetCreateTime() const { return m_strCreateTime; }
	//设置创建时间
	void SetCreateTime(_bstr_t val) { m_strCreateTime = val; }

	//返回备注
	_bstr_t GetRemark() const { return m_strRemark; }
	//设置备注
	void SetRemark(_bstr_t val) { m_strRemark = val; }


	CLableMarker & Instance();
	//标注的数据库操作
	//判断标注是否存在
	BOOL CheckLableExist(_bstr_t bstrGUID);
	//加载对象模型
	BOOL Load(_bstr_t bstrGUID);
	//标识保存
	BOOL Save(LABLESTRUCT modle);
	//标识保存所有列表
	BOOL Save(vector<LABLESTRUCT> models);
	//删除标注记录，通过传递GUID
	BOOL Delete(_bstr_t strGUID);
	//查询所有标注记录
	_RecordsetPtr QueryAllLableMarker();
	void QueryAllLableMarker(std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts);
	
	//查询创建人和创建时间记录,查询开始时间strBeginTime和结束时间strEndTime和创建人为strCreatorName的标注,如果忽略时间则时间值为"",如果忽略创建人则值为"";
	_RecordsetPtr  QueryCreateMarker(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName);
	//查询创建人和创建时间记录,查询开始时间strBeginTime和结束时间strEndTime和创建人为strCreatorName的标注,如果忽略时间则时间值为"",如果忽略创建人则值为"";
	void QueryCreateMarker(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName, std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts);
	//查询创建人和创建时间标注名称,查询开始时间strBeginTime和结束时间strEndTime和创建人为strCreatorName的标注,如果忽略时间则时间值为"",如果忽略创建人则值为"";
	vector<LABLESTRUCT> LoadCreateMark(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName);
	
	//条件查询标注记录
	_RecordsetPtr  QueryLableMarkerByCondit(_bstr_t STRWhere);
	void QueryLableMarkerByCondit(_bstr_t bstrWhere, std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts);
	vector<LABLESTRUCT> LoadLableMark();
	//根据重点目标得到标注
	vector<LABLESTRUCT> LoadLableMark(_bstr_t strTarget);
	
	void LoadMarks( const _bstr_t &strCondit, std::vector< LABLESTRUCT > &vMark );
};
