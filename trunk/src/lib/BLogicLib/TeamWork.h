#pragma once
#include "BllHelp.h"
//��Ա
struct TEAMMENBER
{
		int iId;			 //���
		string strGuid;		 //GUID
		string strName;		 //����
		string strSex;		 //�Ա�
		int iAge;			 //����
		string strProfession;//ְҵ
		string strJobPosition;//ְλ
		string strCompany;	  //������˾
		string strAddress;    //��ַ
		string strMobilePhone; //��ϵ�ֻ�
		string strContacts;    //������ϵ��ʽ
		string strGoodAt;     //�س�
		string strDetails;    //��ϸ��Ϣ
		string strRemark;     //��ע
		int iTeamId;          //������
};
//רҵ�����ר����
struct TEAMWORKMODEL
{
	int iID;			//���
	string strTeamId;	//������
	string strName;		//����
	string strType;     //����
	string strArea;     //����
	string strAddress;  //��ַ
	string strDetail;   //��ϸ��Ϣ
	string strRemark;   //��ע
	string strMark;     //��ʶ
	std::vector<TEAMMENBER> vMenbers; //��Ա
};
class CTeamWork
{
public:
	CTeamWork(void);
	~CTeamWork(void);
private:
	static CTeamWork instance;
	BOOL IsConnectOk();
	std::vector<TEAMMENBER> GetMenbers(_bstr_t bstrId);

public:
	//�����ʼ��
	static CTeamWork & Instance();

///////////////////////////////�ж�///////////////////////////////////////////
	//�ж϶��������Ƿ����
	BOOL CheckTeamName(_bstr_t bstrName);
	//�ж�ר���������Ƿ����
	BOOL CheckExpertName(_bstr_t bstrName);
////////////////////////////����//////////////////////////////////////////////
	//���������Ϣ���ر��
	int SaveTeam(TEAMWORKMODEL tmodel);
	//����ר����Ϣ���ر��
	int SaveExpert(TEAMWORKMODEL tmodel);
	//�����Ա
	BOOL SaveMenbers(int iId, std::vector<TEAMMENBER> vmenber);
//////////////////////////////ɾ��////////////////////////////////////////////
	//�ñ��ɾ��
	BOOL Delete(_bstr_t bstrId);
	//�ñ������ɾ��
	BOOL Delete(std::vector<_bstr_t> vstrId);
//////////////////////////////��ѯ////////////////////////////////////////////	
	//�ñ�ż��ض������ר������Ϣ
	TEAMWORKMODEL LoadInfoById(_bstr_t bstrId);
	//�����Ƽ��ض�����Ϣ
	TEAMWORKMODEL LoadTeamByName(_bstr_t bstrName);
	//�����Ƽ���ר������Ϣ
	TEAMWORKMODEL LoadExpertByName(_bstr_t bstrName);
	//������ѯ�����鼯��
	std::vector<TEAMWORKMODEL> QueryTeamWork(_bstr_t bstrConditions);
	//������ѯר���鼯��
	std::vector<TEAMWORKMODEL> QueryExperts(_bstr_t bstrConditions);
};
