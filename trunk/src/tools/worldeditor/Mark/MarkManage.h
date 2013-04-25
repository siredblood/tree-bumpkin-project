
//
//	标注信息管理类
//	标注信息保存在"scripts/MarkManage.xml"文件中
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
		
		//标注名称，坐标，（类型为0和1，1表示已经存在的对象的标注，0表示任意位置的标注）,对应模型的GUID
		//void AddMarkMessage( std::string strText, Vector3 pos ,std::string strType, std::string strGUID);	//保存一个标注信息
		void AddMarkMessage( MARKDATA markdata);			//添加标注
		void AddMarkMessage( const Vector3& pos, const std::string& name, const std::string& guid );
		void DeleteMarkByGUID(const std::string &strGUID);	                //根据名字删除标注
		void LoadMarks();                                           //加载数据库里所有的标注
		
		void SaveMarks();	//保存所有标注
		
		void ReleaseMark();	//卸载标注
		
	private:
		static CMarkManage instance;
		void CStringToVector3(CString strOrg,Vector3 &v3Aim);
		/*char *m_szFile;*/
};

#endif