#pragma once
#include "BllHelp.h"
#define MapFld map<_bstr_t,_bstr_t>

class CModelInfo
{
private:
	_bstr_t m_strModID;//GUID
	_bstr_t m_strModPath;//ģ��·��
	_bstr_t m_strPosX;//λ��X
	_bstr_t m_strPosY;//λ��Y
	_bstr_t m_strPosZ;//λ��Z
	_bstr_t m_strCirX;//��תX
	_bstr_t m_strCirY;//��תY
	_bstr_t m_strCirZ;//��תZ
	_bstr_t m_strZoomX;//����X
	_bstr_t m_strZoomY;//����Y
	_bstr_t m_strZoomZ;//����Z
	_bstr_t m_strCreator; //������
	_bstr_t m_strCreateTime; //����ʱ��
public:
	CModelInfo(void);
	~CModelInfo(void);
public:
	//����GUID
	_bstr_t GetID() const { return m_strModID; }

	//����ģ��·��
	_bstr_t GetModPath() const { return m_strModPath; }
	//����ģ��·��
	void SetModPath(_bstr_t val) { m_strModPath = val; }

	//����λ��X
	_bstr_t GetPosX() const { return m_strPosX; }
	//����λ��X
	void SetPosX(_bstr_t val) { m_strPosX = val; }

	//����λ��Y
	_bstr_t GetPosY() const { return m_strPosY; }
	//����λ��Y
	void SetPosY(_bstr_t val) { m_strPosY = val; }

	//����λ��Z
	_bstr_t GetPosZ() const { return m_strPosZ; }
	//����λ��X
	void SetPosZ(_bstr_t val) { m_strPosZ = val; }

	//������תX
	_bstr_t GetCirX() const { return m_strCirX; }
	//������תX
	void SetCirX(_bstr_t val) { m_strCirX = val; }

	//������תY
	_bstr_t GetCirY() const { return m_strCirY; }
	//������תY
	void SetCirY(_bstr_t val) { m_strCirY = val; }

	//������תZ
	_bstr_t GetCirZ() const { return m_strCirZ; }
	//������תZ
	void SetCirZ(_bstr_t val) { m_strCirZ = val; }

	//��������X
	_bstr_t GetZoomX() const { return m_strZoomX; }
	//��������X
	void SetZoomX(_bstr_t val) { m_strZoomX = val; }

	//��������Y
	_bstr_t GetZoomY() const { return m_strZoomY; }
	//��������Y
	void SetZoomY(_bstr_t val) { m_strZoomY = val; }

	//��������Z
	_bstr_t GetZoomZ() const { return m_strZoomZ; }
	//��������Z
	void SetZoomZ(_bstr_t val) { m_strZoomZ = val; }
	//���ش�����
	_bstr_t GetCreator() const { return m_strCreator; }
	//���ô�����
	void SetCreator(_bstr_t val) { m_strCreator = val; }
	//���ش���ʱ��
	_bstr_t GetCreateTime() const { return m_strCreateTime; }
	//���ô���ʱ��
	void SetCreateTime(_bstr_t val) { m_strCreateTime = val; }


	//ģ�ͻ�����Ϣ�����ݿ����

	//���ض���ģ��
	BOOL Load(_bstr_t strGUID);
	_RecordsetPtr LoadInfo(std::vector<_bstr_t> vbstrFieldName);
	//���ַ������ض���ģ��
	_RecordsetPtr LoadStr(_bstr_t strField);
	//����ֶ�
	void CModelInfo::AddField(_bstr_t strFieldName, FieldType enumFieldType,int iFieldSize);

	//ɾ���ֶ�
	BOOL DelFiled(_bstr_t strTableName, _bstr_t strFieldName);

	//��Ӽ�¼
	BOOL Add(std::map<_bstr_t,_bstr_t> &mapFlds);
	BOOL Add(_bstr_t GUID);

	//�޸ļ�¼
	BOOL Update();

	//ɾ����¼
	BOOL Delete();
	BOOL Delete(CString strGUIDS);

	//��ѯ��¼
	_RecordsetPtr QueryAllModel();
	void QueryAllModel(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);

	_RecordsetPtr QueryModelByCondit(_bstr_t STRWhere);
	void QueryModelByCondit(_bstr_t bstrWhere,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//������ѯ
	_RecordsetPtr QueryCreateModel(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName);
	void QueryCreateModel(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
};