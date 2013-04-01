#pragma once
#include "DBHead.h"

//////////////////////////////////////////////////////////////////////////
//��ѯģʽ
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
//���ݿ����
class CObjectDB
{
public:
	CObjectDB();
	~CObjectDB();

public:
	//������ConnectDB�������������ݿ�ʵ�ֲ�һ����
	//������
	//  strServer:������
	//	strDatabaseName�����ݿ���
	//	strUID���û���
	//	strPwd���û�����
	//	iOptions������ģʽ��ConnectOptionEnum��ConnectModeEnumö������
	//����ֵ��BOOL
	virtual BOOL ConnectDB(_bstr_t strServer, _bstr_t strDatabaseName, _bstr_t strUID, 
		_bstr_t strPwd, int iOptions = 0)
	{ return TRUE; }
	//�ر�����
	virtual void Close();
	//��ȡ����
	virtual _ConnectionPtr GetConnection();
	//��ȡ����
	virtual _CommandPtr GetCommand();

	//�жϱ����Ƿ����
	virtual bool CheckTableNameExist(_bstr_t bstrTableName);
	//������CreateTable��������
	//������
	//	strTableName������
	//	strFieldsFormat���ֶθ�ʽ���ַ���
	//	strExtended����չ��Ϣ��һ���Ǳ�ռ�
	//	���磺CREATE TABLE MYTB(ID CHAR(10) NOT NULL,NAME CHAR(20),NULL)
	//		strTableName=MYTB
	//		strFieldsFormat=ID CHAR(10) NOT NULL,NAME CHAR(20),NULL
	//����ֵ��BOOL
	virtual BOOL CreateTable(_bstr_t strTableName, _bstr_t strFieldsFormat, _bstr_t strExtended = "");

	//������DropTable��ɾ����
	//������
	//	strTableName������
	//����ֵ��BOOL
	virtual BOOL DropTable(_bstr_t strTableName);

	//������RenameTable����������
	//������
	//	strOldTableName���ɱ���
	//	strNewTableName���±���
	//����ֵ��BOOL
	virtual BOOL RenameTable(_bstr_t strOldTableName, _bstr_t strNewTableName);

	//������CreateField�������ֶ�
	//������
	//	strTableName������
	//	strFieldsFormat���ֶθ�ʽ���ַ���
	//ע��strFieldsFormat��CreateTable�Ĳ���strFieldsFormat��ʽһ��
	//����ֵ��BOOL
	virtual BOOL CreateField(_bstr_t strTableName, _bstr_t strFieldsFormat);

	//������DropField��ɾ���ֶ�
	//������
	//	strTableName������
	//	strFieldName���ֶ���
	//����ֵ��BOOL
	virtual BOOL DropField(_bstr_t strTableName, _bstr_t strFieldName);

	//������ModifyField���޸��ֶ�
	//������
	//	strTableName������
	//	strFieldsFormat���ֶθ�ʽ���ַ���
	//ע��strFieldsFormat��CreateTable�Ĳ���strFieldsFormat��ʽһ��
	//����ֵ��BOOL
	virtual BOOL ModifyField(_bstr_t strTableName, _bstr_t strFieldsFormat);

	//������AddRecord����Ӽ�¼
	//������
	//	strTableName������
	//	strColumnsFormat���ֶθ�ʽ���ַ���
	//	strValuesFormat���ֶ�ֵ��ʽ���ַ���
	//	���磺INSERT INTO MYTB(ID,NAME,AGE) VALUES (100,'NAME1',20)
	//		strColumnsFormat=ID,NAME
	//		AGE,strValuesFormat=100,'NAME1',20
	//����ֵ��BOOL
	virtual BOOL AddRecord(_bstr_t strTableName, _bstr_t strColumnsFormat, _bstr_t strValuesFormat);

	//������ModifyRecord���޸ļ�¼
	//������
	//	strTableName������
	//	strSelectItemName��ѡ���¼ID
	//	strSelectItemValue��ѡ���¼IDֵ
	//	strModifyItemsFormat���޸��ֶ�ֵ��
	//	���磺UPDATE MYTB SET NAME = 'NEWNAME',AGE = 15 WHERE ID = 100
	//		strModifyItemsFormat = NAME = 'NEWNAME',AGE = 15
	//����ֵ��BOOL
	virtual BOOL ModifyRecord(_bstr_t strTableName, _bstr_t strSelectItemName, _bstr_t strSelectItemValue,
		_bstr_t strModifyItemsFormat);

	//������ModifyRecords���޸����м�¼
	//������
	//	strTableName������
	//	strModifyColumnName���޸ļ�¼�ֶ���
	//	strModifyColumnValue���޸ļ�¼�ֶ�ֵ
	//����ֵ��BOOL
	virtual BOOL ModifyRecords(_bstr_t strTableName, _bstr_t strModifyColumnName, _bstr_t strModifyColumnValue);

	//������DropRecord��ɾ����¼
	//������
	//	strTableName������
	//	strColumnName��ɾ����¼ID 
	//	strColumnValue��ɾ����¼ֵ
	//����ֵ��BOOL
	virtual BOOL DropRecord(_bstr_t strTableName, _bstr_t strColumnName, _bstr_t strColumnValue);

	//������Query����ѯ����
	//������
	//	strTableName������
	//	strSelectItems��ѡ����ʾ���ֶΣ�Ĭ��Ϊ"*"
	//	strOrderByItem����ѯ���¼��ʲô����Ĭ��Ϊ""��������
	//	strKeyItem��ѡ���¼ID 
	//	strKeyValue��ѡ���¼ֵ
	//	enumMode����ѯģʽ��=��like��>�ȣ�enumModeö������
	//����ֵ��_RecordsetPtr
	virtual _RecordsetPtr Query(_bstr_t strTableName,_bstr_t strSelectItems = "*",_bstr_t strOrderByItem = "");
	virtual _RecordsetPtr Query(_bstr_t strTableName, _bstr_t strKeyItem, _bstr_t strKeyValue, QueryModeEnum enumMode, _bstr_t strSelectItems = "*",_bstr_t strOrderByItem = "");

	///ִ��SQL���
	//������ExcuteSql���޷��ؼ�¼
	//		ExcuteSqlRes�����ؼ�¼
	//������	
	//	strSql��SQL���
	//	enumTyp��CommandTypeEnumö������
	//����ֵ����
	virtual BOOL ExcuteSql(_bstr_t strSql, CommandTypeEnum enumType);
	virtual _RecordsetPtr ExcuteSqlRes(_bstr_t strSql, CommandTypeEnum enumType);

	//����
	virtual BOOL ExcuteTrans(std::vector<_bstr_t> &strSqls, CommandTypeEnum enumType);
	///���ݱ��ݻ�ԭ
	virtual BOOL Backup(_bstr_t strFullPath)
	{ return TRUE; }
	virtual BOOL Restore(_bstr_t strFullPath)
	{ return TRUE; }

	///ͨ��������ȡ��¼��ָ��
	_RecordsetPtr GetRecordSet(_bstr_t strTableName);

protected:
	_bstr_t GetQueryModeString(QueryModeEnum enumMode);
protected:
	_CommandPtr m_pCommand;			//����ָ��
	_ConnectionPtr m_pConnection;	//����ָ��

	_bstr_t m_strServer;		//������
	_bstr_t m_strDatabaseName;	//���ݿ���
	_bstr_t m_strUID;			//�û�
	_bstr_t m_strPwd;			//����
};