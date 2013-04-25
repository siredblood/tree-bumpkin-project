
//
//	��ע��Ϣ������
//	��ע��Ϣ������"scripts/MarkManage.xml"�ļ���
//
//

#ifndef __MARKMANAGE_H__
#define __MARKMANAGE_H__
#include "MarkObject.h"

class CMarkManage
{
	public:
		CMarkManage(void);
		~CMarkManage(void);
		
		static CMarkManage &Instance();
		
		//��ע���ƣ����꣬������Ϊ0��1��1��ʾ�Ѿ����ڵĶ���ı�ע��0��ʾ����λ�õı�ע��,��Ӧģ�͵�GUID
		//void AddMarkMessage( std::string strText, Vector3 pos ,std::string strType, std::string strGUID);	//����һ����ע��Ϣ
		void AddMarkMessage( MARKDATA markdata);			//��ӱ�ע
		void AddMarkMessage( const Vector3& pos, const std::string& name, const std::string& guid );
		void DeleteMarkByGUID(const std::string &strGUID);	                //��������ɾ����ע
		void LoadMarks();                                           //�������ݿ������еı�ע
		
		void SaveMarks();	//�������б�ע
		
		void ReleaseMark();	//ж�ر�ע
		
	private:
		static CMarkManage instance;
		void CStringToVector3(CString strOrg,Vector3 &v3Aim);
		/*char *m_szFile;*/
};

#endif