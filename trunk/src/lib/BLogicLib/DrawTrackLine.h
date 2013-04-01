#pragma once
#include "DBHelper.h"
#include "BllHelp.h"

//航线结构
struct DRAWLINESTRUCT
{
	CString GUID;       //编号
	CString Name;       //名称
	double  Speed;      //速度
	CString Remark;     //备注
	std::vector<CString> coodinates; //航线节点坐标列表
};

class CDrawTrackLine
{
public:
	CDrawTrackLine(void);
	~CDrawTrackLine(void);
private:
	//航线字段
	CString m_strGUID;       //编号
	CString m_strName;       //名称
	double m_strSpeed;       //速度
	CString m_strRemark;     //备注
public:
	//航线属性获取和设置

	//返回编号
	CString GetGUID() const { return m_strGUID; }
	//设置编号
	void SetGUID(CString val){ m_strGUID = val;}
	//返回名称
	CString GetName() const { return m_strName; }
	//设置名称
	void SetName(CString val) { m_strName = val; }
	//返回速度
	double GetSpeed() const { return m_strSpeed; }
	//设置速度
	void SetSpeed(double val) { m_strSpeed = val; }
	//返回备注
	CString GetRemark() const { return m_strRemark; }
	//设置备注
	void SetRemark(CString val) { m_strRemark = val; }


	//航线数据库操作,先有线再有节点

	//加载航线信息。
	//参数：航线编号
	BOOL LoadInfo( CString bstrGUID);

	//加载航线节点记录集。
	//参数：航线编号
	_RecordsetPtr LoadNodesRCS( CString bstrGUID );
	//加载航线节点列表
	//参数：航线编号
	void LoadNodesVetors( CString bstrGUID ,std::vector<CString> &coodinate);

	//增加航线记录,
	//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL Add();
	//编辑航线记录信息,
	//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL UpdateLineInfo();

	//清除航线节点
	BOOL ClearLineNodes( CString bstrGUID );
	//编辑航线记录信息,
	//参数：坐标列表
	//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL SaveLineNodes( std::vector<CString> vbstrCoordinates , CString strGUID );

	//删除航线记录，
	BOOL Delete(CString bstrGUID);

	//查询所有航线列表
	_RecordsetPtr QueryAllLines();
	//查询所有航线列表,返回绑定列表
	void QueryAllLines(std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts);
	//条件查询航线记录：参数：查询条件
	_RecordsetPtr  QueryLinesByCondit(CString bstrWhere);
	//条件查询航线记录：参数：查询条件,返回绑定列表
	void QueryLinesByCondit(CString bstrWhere, std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts);	

	//加载场景时加载航线
	std::vector<DRAWLINESTRUCT> QueryDrawLineForLoad(CString bstrWhere);
};