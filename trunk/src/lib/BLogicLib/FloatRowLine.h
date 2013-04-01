#pragma once
#include "BllHelp.h"


/************************************************************************/
/* 流行线类                                                             */
/************************************************************************/
class CFloatRowLine
{
public:
	CFloatRowLine(void);
	~CFloatRowLine(void);
private:
	//流行线字段
	_bstr_t m_strID;         //编号
	_bstr_t m_strName;       //名称
	_bstr_t m_strToTarger;   //所属目标
	_bstr_t m_strColor;		 //颜色
	_bstr_t m_strLineType;   //实线与虚线
	_bstr_t m_strDerection;  //是否有箭头
	_bstr_t m_strWidth;      //线宽度
	_bstr_t m_strCreator;     //创建人
	_bstr_t m_strCreateTime;  //创建时间
	_bstr_t m_strRemark;     //备注

	static CFloatRowLine instance;
public:
	//流行线属性获取和设置

	//返回编号
	_bstr_t GetID() const { return m_strID; }
	////设置编号
	//void SetID(_bstr_t val) { m_strID = val; }

	//返回名称
	_bstr_t GetName() const { return m_strName; }
	//设置名称
	void SetName(_bstr_t val) { m_strName = val; }

	//返回所属目标
	_bstr_t GetToTarger() const { return m_strToTarger; }
	//设置所属目标
	void SetToTarger(_bstr_t val) { m_strToTarger = val; }

	//返回颜色
	_bstr_t GetColor() const { return m_strColor; }
	//设置颜色
	void SetColor(_bstr_t val) { m_strColor = val; }

	//返回虚实线
	_bstr_t GetLineType() const { return m_strLineType; }
	//设置虚实线
	void SetLineType(_bstr_t val) { m_strLineType = val; }

	//返回是否带箭头
	_bstr_t GetDerection() const { return m_strDerection; }
	//设置是否带箭头
	void SetDerection(_bstr_t val) { m_strDerection = val; }

	//返回线宽度
	_bstr_t GetWidth() const { return m_strWidth; }
	//设置线宽度
	void SetWidth(_bstr_t val) { m_strWidth = val; }

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


	static CFloatRowLine & Instance();
	//流行线的数据库操作

	//加载流行线信息
	BOOL LoadInfo( _bstr_t bstrID);
	//加载流行线节点数据集
	_RecordsetPtr LoadNodesRCS( _bstr_t bstrID);
	//加载流行线节点列表
	std::vector<string> LoadNodesVetor( _bstr_t bstrID);
	////使用名称加载流行线
	//BOOL LoadInfoByName(_bstr_t bstrName);
	//_RecordsetPtr LoadByNameRCS(_bstr_t bstrName);
	//std::vector<string> LoadNodesByName(_bstr_t bstrName);
	//加载流行线属性列表
	_RecordsetPtr Loadproperties( _bstr_t bstrID );
	void Loadproperties(_bstr_t bstrID, std::vector<string> &vecField, std::vector<string> &vecRecordSet, long &lFieldCounts);

	//判断名字是否已经存在
	bool CheckNameExiest(_bstr_t strName);

	//增加流行线记录,
	//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL Add();
	int AddGetID();
	//编辑流行线记录,
	//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL Update();

	//清除流行线节点
	BOOL ClearLineNodes( _bstr_t bstrIDs );
	//编辑流行线记录信息,
	//参数：坐标列表
	//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL SaveLineNodes( std::vector<_bstr_t> vbstrCoordinates );

	//删除流行线记录，
	//通过传递编号（用“，"隔开）
	BOOL Delete(_bstr_t bstrIDS);
	
	
	//查询所有流行线目标列表
	_RecordsetPtr QueryAllLines();
	std::vector<_bstr_t> QueryAllLinesID();
	void QueryAllLines(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//查询所属目标流行线
	_RecordsetPtr QueryTargetLines(_bstr_t strTarget);
	std::vector<_bstr_t> QueryTargetinesID(_bstr_t strTarget);
	void QueryTargetLines(_bstr_t strTarget,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//条件查询流行线记录
	_RecordsetPtr  QueryLinesByCondit(_bstr_t bstrWhere);
	std::vector<_bstr_t> QueryLinesIDByCondit(_bstr_t bstrWhere);
	void QueryLinesByCondit(_bstr_t bstrWhere,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	
	//查询时间段内有效的流行线
	_RecordsetPtr QueryValidateLines(_bstr_t bstrBeginDate,_bstr_t bstrEndDate);
	//查询时间段内有效的流行线
	void QueryValidateLines( _bstr_t bstrBeginDate,_bstr_t bstrEndDate,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//创建查询
	_RecordsetPtr QueryCreateLines(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName);
	void QueryCreateLines(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
};
/************************************************************************/
/* 流行线属性类                                                                     */
/************************************************************************/
class CFRowLineProperty
{
public:
	CFRowLineProperty(void);
	~CFRowLineProperty(void);

private:
	//流行线属性字段
	_bstr_t m_strID;         //编号
	_bstr_t m_strLineID;     //所属流行线编号
	_bstr_t m_strBeginDate;  //启用时间
	_bstr_t m_strEndDate;    //结束时间
	_bstr_t m_strRemark;     //备注
public:
	//流行线属性获取和设置

	//返回编号
	_bstr_t GetID() const { return m_strID; }
	//设置编号
	void SetID(_bstr_t val) { m_strID = val; }

	//返回所属流行线编号
	_bstr_t GetLineID() const { return m_strLineID; }
	//设置所属流行线编号
	void SetLineID(_bstr_t val) { m_strLineID = val; }

	//返回启用时间
	_bstr_t GetBeginDate() const { return m_strBeginDate; }
	//设置启用时间
	void SetBeginDate(_bstr_t val) { m_strBeginDate = val; }

	//返回结束时间
	_bstr_t GetEndDate() const { return m_strEndDate; }
	//设置结束时间
	void SetToEndDate(_bstr_t val) { m_strEndDate = val; }

	//返回备注
	_bstr_t GetRemark() const { return m_strRemark; }
	//设置备注
	void SetRemark(_bstr_t val) { m_strRemark = val; }


	//流行线属性的数据库操作

	//加载属性:参数：属性表中的编号
	BOOL LoadInfo( _bstr_t bstrID );
	//检测流行线属性录入的冲突
	BOOL CheckLnPrptyColn(_bstr_t bstrID, _bstr_t bstrLineid,_bstr_t bstrBeginDate,_bstr_t bstrEndDate);
	//增加流行线属性记录,首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL Add();
	//编辑流行线属性记录,首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL Update();
	//删除流行线属性记录,首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL Delete();
	//删除流行线属性记录，通过传递编号（用“，"隔开）
	BOOL Delete(_bstr_t strIDS);
};
