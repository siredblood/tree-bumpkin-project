
//
//	��ע��ʾ��
//	�Ա�ע��Ϣ���л�����ʾ�����ܴ����ע��Ϣ�����Ұ���ά����תΪ��ά����
//
//

#ifndef __MARKOBJECT_H_
#define __MARKOBJECT_H_

#include "ChineseFont.h"
#include "worldeditor/BaseFramework/ITask.hpp"

struct MARKDATA				//��ע�ṹ�������ı�������
{
	std::string strText;		//��ע
	std::string strGUID;		//����GUID
	Vector3 pos;				//λ��
	std::string strType;		//����
	std::string strCreator;		//������
	std::string strCreateTime;	//����ʱ��
	float       fViewDist;      //���Ӿ���
	bool bHaveObject;			//�Ƿ��Ѿ��ж���
};

class CMarkObject : public ITask
{
	public:
		CMarkObject(void);
		~CMarkObject(void);

#define MARK_MODEL	"sets/items/information.model"

		virtual void init();
		virtual void fini();
		virtual void tick( float dTime );
		virtual void draw();
		
		void AddDrawMessage(MARKDATA markdata);					//����һ����ע��Ϣ
		void DeleteMark(std::string strGUID);   //ͨ��GUIDɾ����ע
		void ClearAllMark();                    //������������б�ע
		void SetDrawMessage(std::vector<MARKDATA> vMarkdata);	//�����ע��Ϣ
		std::vector<MARKDATA> GetDrawMessage( );				//��ȡ��ע��Ϣ
		
		void ShowMark(bool bDraw);	//�����Ƿ���Ʊ�ע
		bool IsShowMark();			//��ȡ�Ƿ���Ʊ�ע
		
		// ����ֵΪ�޸ı�ע����
		int ModifyMark(std::string strGUID, Vector3 pos);	//�޸ı�ע��λ��
		int ModifyMark(std::string strGUID, std::string strText);	//�޸ı�ע�ı�ע����
		int ModifyMark(std::string strGUID, std::string strText,float fviewDist);	//�޸ı�ע�ı�ע���ֺͿ��Ӿ���

		//MARKDATA GetMark(int index);
		
		static CMarkObject & Instance();
	
private:
		//�Ƿ���ʾ��עģ��
		void ShowMarkModel( bool bType );

		void Conver3DTo2D(Vector3 pos, int &x, int &y);	//��3ά����ת����2ά����
		bool IsPositionInView(Vector3 pos);				//�ж������Ƿ�ɼ�
		bool CheckExistByPosition(Vector3 pos, int &index, std::string &strText);			//���������жϱ�ע�Ƿ����
		bool CheckExistbyText( std::string strText );	//����Ƿ��Ѿ���������
		bool CheckExistByGUID(std::string strGUID,int &iindex);  //����GUID�ж��Ƿ��б�ע
		void DeleteMark(int index);
		
		void SortByDis();	//����������
		
	private:
		static CMarkObject instance;
		
		CChineseFont m_ChineseFont;
		std::vector<MARKDATA> m_vMarkData;	//��ע��Ϣ
		bool m_bDraw;
		
		Vector3 m_LastPos;
		Vector3 m_LastDir;
		
	public:
		std::vector<ChunkItemPtr> m_vAllMarkIcon;	//��עͼ��
};

#endif