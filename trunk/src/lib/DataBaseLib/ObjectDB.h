#pragma once
#include "DBHead.h"

//////////////////////////////////////////////////////////////////////////
//查询模式
enum QueryModeEnum
{
	EqualMode,			//=
	LikeMode,			//LIKE
	BiggerMode,			//>
	BiggerEqualMode,	//>=
	SmallerMode,		//<
	SmallerEqualMode	//<=
};
//////////////////////////////////////////////////////////////////////////
//数据库基类
class CObjectDB
{
public:
	CObjectDB();
	~CObjectDB();

public:
	//函数：ConnectDB，各个具体数据库实现不一样。
	//参数：
	//  strServer:服务器
	//	strDatabaseName：数据库名
	//	strUID：用户名
	//	strPwd：用户密码
	//	iOptions：连接模式，ConnectOptionEnum或ConnectModeEnum枚举类型
	//返回值：BOOL
	virtual BOOL ConnectDB(_bstr_t strServer, _bstr_t strDatabaseName, _bstr_t strUID, 
		_bstr_t strPwd, int iOptions = 0)
	{ return TRUE; }
	//关闭连接
	virtual void Close();
	//获取连接
	virtual _ConnectionPtr GetConnection();
	//获取命令
	virtual _CommandPtr GetCommand();

	//判断表名是否存在
	virtual bool CheckTableNameExist(_bstr_t bstrTableName);
	//函数：CreateTable，创建表
	//参数：
	//	strTableName：表名
	//	strFieldsFormat：字段格式化字符串
	//	strExtended：扩展信息，一般是表空间
	//	例如：CREATE TABLE MYTB(ID CHAR(10) NOT NULL,NAME CHAR(20),NULL)
	//		strTableName=MYTB
	//		strFieldsFormat=ID CHAR(10) NOT NULL,NAME CHAR(20),NULL
	//返回值：BOOL
	virtual BOOL CreateTable(_bstr_t strTableName, _bstr_t strFieldsFormat, _bstr_t strExtended = "");

	//函数：DropTable，删除表
	//参数：
	//	strTableName：表名
	//返回值：BOOL
	virtual BOOL DropTable(_bstr_t strTableName);

	//函数：RenameTable，重命名表
	//参数：
	//	strOldTableName：旧表名
	//	strNewTableName：新表名
	//返回值：BOOL
	virtual BOOL RenameTable(_bstr_t strOldTableName, _bstr_t strNewTableName);

	//函数：CreateField，创建字段
	//参数：
	//	strTableName：表名
	//	strFieldsFormat：字段格式化字符串
	//注：strFieldsFormat与CreateTable的参数strFieldsFormat格式一样
	//返回值：BOOL
	virtual BOOL CreateField(_bstr_t strTableName, _bstr_t strFieldsFormat);

	//函数：DropField，删除字段
	//参数：
	//	strTableName：表名
	//	strFieldName：字段名
	//返回值：BOOL
	virtual BOOL DropField(_bstr_t strTableName, _bstr_t strFieldName);

	//函数：ModifyField，修改字段
	//参数：
	//	strTableName：表名
	//	strFieldsFormat：字段格式化字符串
	//注：strFieldsFormat与CreateTable的参数strFieldsFormat格式一样
	//返回值：BOOL
	virtual BOOL ModifyField(_bstr_t strTableName, _bstr_t strFieldsFormat);

	//函数：AddRecord，添加记录
	//参数：
	//	strTableName：表名
	//	strColumnsFormat：字段格式化字符串
	//	strValuesFormat：字段值格式化字符串
	//	例如：INSERT INTO MYTB(ID,NAME,AGE) VALUES (100,'NAME1',20)
	//		strColumnsFormat=ID,NAME
	//		AGE,strValuesFormat=100,'NAME1',20
	//返回值：BOOL
	virtual BOOL AddRecord(_bstr_t strTableName, _bstr_t strColumnsFormat, _bstr_t strValuesFormat);

	//函数：ModifyRecord，修改记录
	//参数：
	//	strTableName：表名
	//	strSelectItemName：选择记录ID
	//	strSelectItemValue：选择记录ID值
	//	strModifyItemsFormat：修改字段值组
	//	例如：UPDATE MYTB SET NAME = 'NEWNAME',AGE = 15 WHERE ID = 100
	//		strModifyItemsFormat = NAME = 'NEWNAME',AGE = 15
	//返回值：BOOL
	virtual BOOL ModifyRecord(_bstr_t strTableName, _bstr_t strSelectItemName, _bstr_t strSelectItemValue,
		_bstr_t strModifyItemsFormat);

	//函数：ModifyRecords，修改所有记录
	//参数：
	//	strTableName：表名
	//	strModifyColumnName：修改记录字段名
	//	strModifyColumnValue：修改记录字段值
	//返回值：BOOL
	virtual BOOL ModifyRecords(_bstr_t strTableName, _bstr_t strModifyColumnName, _bstr_t strModifyColumnValue);

	//函数：DropRecord，删除记录
	//参数：
	//	strTableName：表名
	//	strColumnName：删除记录ID 
	//	strColumnValue：删除记录值
	//返回值：BOOL
	virtual BOOL DropRecord(_bstr_t strTableName, _bstr_t strColumnName, _bstr_t strColumnValue);

	//函数：Query，查询操作
	//参数：
	//	strTableName：表名
	//	strSelectItems：选择显示的字段，默认为"*"
	//	strOrderByItem：查询后记录按什么排序，默认为""，不排序
	//	strKeyItem：选择记录ID 
	//	strKeyValue：选择记录值
	//	enumMode：查询模式，=、like、>等，enumMode枚举类型
	//返回值：_RecordsetPtr
	virtual _RecordsetPtr Query(_bstr_t strTableName,_bstr_t strSelectItems = "*",_bstr_t strOrderByItem = "");
	virtual _RecordsetPtr Query(_bstr_t strTableName, _bstr_t strKeyItem, _bstr_t strKeyValue, QueryModeEnum enumMode, _bstr_t strSelectItems = "*",_bstr_t strOrderByItem = "");

	///执行SQL语句
	//函数：ExcuteSql：无返回记录
	//		ExcuteSqlRes：返回记录
	//参数：	
	//	strSql：SQL语句
	//	enumTyp：CommandTypeEnum枚举类型
	//返回值：略
	virtual BOOL ExcuteSql(_bstr_t strSql, CommandTypeEnum enumType);
	virtual _RecordsetPtr ExcuteSqlRes(_bstr_t strSql, CommandTypeEnum enumType);

	//事务
	virtual BOOL ExcuteTrans(std::vector<_bstr_t> &strSqls, CommandTypeEnum enumType);
	///数据备份还原
	virtual BOOL Backup(_bstr_t strFullPath)
	{ return TRUE; }
	virtual BOOL Restore(_bstr_t strFullPath)
	{ return TRUE; }

	///通过表名获取记录集指针
	_RecordsetPtr GetRecordSet(_bstr_t strTableName);

protected:
	_bstr_t GetQueryModeString(QueryModeEnum enumMode);
protected:
	_CommandPtr m_pCommand;			//命令指针
	_ConnectionPtr m_pConnection;	//连接指针

	_bstr_t m_strServer;		//服务器
	_bstr_t m_strDatabaseName;	//数据库名
	_bstr_t m_strUID;			//用户
	_bstr_t m_strPwd;			//密码
};