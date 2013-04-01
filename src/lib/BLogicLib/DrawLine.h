#pragma once
#include "BllHelp.h"

class CDrawLine
{
public:
	CDrawLine(void);
	~CDrawLine(void);
private:
	//自画线字段
	_bstr_t m_strID;         //编号
	_bstr_t m_strName;       //名称
	_bstr_t m_strColor;      //颜色
	_bstr_t m_strCreator;    //创建人
	_bstr_t m_strCreateTime; //创建时间
	_bstr_t m_strRemark;     //备注
public:
	//自画线属性获取和设置

	//返回编号
	_bstr_t GetID() const { return m_strID; }
	////设置编号
	//void SetID(_bstr_t val) { m_strID = val; }

	//返回名称
	_bstr_t GetName() const { return m_strName; }
	//设置名称
	void SetName(_bstr_t val) { m_strName = val; }

	//返回颜色
	_bstr_t GetColor() const { return m_strColor; }
	//设置颜色
	void SetColor(_bstr_t val) { m_strColor = val; }

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


	//自画线的数据库操作,先有自画线再有节点

	//加载自画线信息。
	//参数：自画线编号
	BOOL LoadInfo( _bstr_t bstrID);
	//加载自画线节点记录集。
	//参数：自画线编号
	_RecordsetPtr LoadNodesRCS( _bstr_t bstrID );
	//加载自画线节点列表
	//参数：自画线编号
	std::vector<_bstr_t> LoadNodesVetors( _bstr_t bstrID );

	//增加自画线记录,
	//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL Add();
	//编辑自画线记录信息,
	//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL UpdateLineInfo();

	//清除自画线节点
	BOOL ClearLineNodes( _bstr_t bstrIDs );
	//编辑自画线记录信息,
	//参数：坐标列表
	//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL SaveLineNodes( std::vector<_bstr_t> vbstrCoordinates );

	//删除自画线记录，
	//通过传递编号（用“，"隔开）：参数自画线编号
	BOOL Delete(_bstr_t bstrIDS);

	//查询所有自画线列表
	_RecordsetPtr QueryAllLines();
	void QueryAllLines(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//条件查询自画线记录：参数：查询条件
	_RecordsetPtr  QueryLinesByCondit(_bstr_t bstrWhere);
	void QueryLinesByCondit(_bstr_t bstrWhere, vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);	
	//创建查询
	_RecordsetPtr  QueryCreateLines(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName);
	void QueryCreateLines(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName, vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);	
};