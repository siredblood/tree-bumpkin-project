#pragma once
#include "DBHelper.h"
#include "BllHelp.h"

//���߽ṹ
struct DRAWLINESTRUCT
{
	CString GUID;       //���
	CString Name;       //����
	double  Speed;      //�ٶ�
	CString Remark;     //��ע
	std::vector<CString> coodinates; //���߽ڵ������б�
};

class CDrawTrackLine
{
public:
	CDrawTrackLine(void);
	~CDrawTrackLine(void);
private:
	//�����ֶ�
	CString m_strGUID;       //���
	CString m_strName;       //����
	double m_strSpeed;       //�ٶ�
	CString m_strRemark;     //��ע
public:
	//�������Ի�ȡ������

	//���ر��
	CString GetGUID() const { return m_strGUID; }
	//���ñ��
	void SetGUID(CString val){ m_strGUID = val;}
	//��������
	CString GetName() const { return m_strName; }
	//��������
	void SetName(CString val) { m_strName = val; }
	//�����ٶ�
	double GetSpeed() const { return m_strSpeed; }
	//�����ٶ�
	void SetSpeed(double val) { m_strSpeed = val; }
	//���ر�ע
	CString GetRemark() const { return m_strRemark; }
	//���ñ�ע
	void SetRemark(CString val) { m_strRemark = val; }


	//�������ݿ����,���������нڵ�

	//���غ�����Ϣ��
	//���������߱��
	BOOL LoadInfo( CString bstrGUID);

	//���غ��߽ڵ��¼����
	//���������߱��
	_RecordsetPtr LoadNodesRCS( CString bstrGUID );
	//���غ��߽ڵ��б�
	//���������߱��
	void LoadNodesVetors( CString bstrGUID ,std::vector<CString> &coodinate);

	//���Ӻ��߼�¼,
	//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL Add();
	//�༭���߼�¼��Ϣ,
	//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL UpdateLineInfo();

	//������߽ڵ�
	BOOL ClearLineNodes( CString bstrGUID );
	//�༭���߼�¼��Ϣ,
	//�����������б�
	//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL SaveLineNodes( std::vector<CString> vbstrCoordinates , CString strGUID );

	//ɾ�����߼�¼��
	BOOL Delete(CString bstrGUID);

	//��ѯ���к����б�
	_RecordsetPtr QueryAllLines();
	//��ѯ���к����б�,���ذ��б�
	void QueryAllLines(std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts);
	//������ѯ���߼�¼����������ѯ����
	_RecordsetPtr  QueryLinesByCondit(CString bstrWhere);
	//������ѯ���߼�¼����������ѯ����,���ذ��б�
	void QueryLinesByCondit(CString bstrWhere, std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts);	

	//���س���ʱ���غ���
	std::vector<DRAWLINESTRUCT> QueryDrawLineForLoad(CString bstrWhere);
};