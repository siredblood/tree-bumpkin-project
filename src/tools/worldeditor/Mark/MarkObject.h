
//
//	标注显示类
//	对标注信息进行绘制显示，接受传入标注信息，并且把三维坐标转为二维坐标
//
//

#ifndef __MARKOBJECT_H_
#define __MARKOBJECT_H_

#include "ChineseFont.h"
#include "worldeditor/BaseFramework/ITask.hpp"

struct MARKDATA				//标注结构，包含文本和坐标
{
	std::string strText;		//标注
	std::string strGUID;		//对象GUID
	Vector3 pos;				//位置
	std::string strType;		//类型
	std::string strCreator;		//创建人
	std::string strCreateTime;	//创建时间
	float       fViewDist;      //可视距离
	bool bHaveObject;			//是否已经有对象
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
		
		void AddDrawMessage(MARKDATA markdata);					//加入一个标注信息
		void DeleteMark(std::string strGUID);   //通过GUID删除标注
		void ClearAllMark();                    //清除场景中所有标注
		void SetDrawMessage(std::vector<MARKDATA> vMarkdata);	//传入标注信息
		std::vector<MARKDATA> GetDrawMessage( );				//获取标注信息
		
		void ShowMark(bool bDraw);	//设置是否绘制标注
		bool IsShowMark();			//获取是否绘制标注
		
		// 返回值为修改标注索引
		int ModifyMark(std::string strGUID, Vector3 pos);	//修改标注的位置
		int ModifyMark(std::string strGUID, std::string strText);	//修改标注的标注文字
		int ModifyMark(std::string strGUID, std::string strText,float fviewDist);	//修改标注的标注文字和可视距离

		//MARKDATA GetMark(int index);
		
		static CMarkObject & Instance();
	
private:
		//是否显示标注模型
		void ShowMarkModel( bool bType );

		void Conver3DTo2D(Vector3 pos, int &x, int &y);	//把3维坐标转换成2维坐标
		bool IsPositionInView(Vector3 pos);				//判断坐标是否可见
		bool CheckExistByPosition(Vector3 pos, int &index, std::string &strText);			//根据坐标判断标注是否存在
		bool CheckExistbyText( std::string strText );	//检查是否已经存在名称
		bool CheckExistByGUID(std::string strGUID,int &iindex);  //根据GUID判断是否有标注
		void DeleteMark(int index);
		
		void SortByDis();	//按距离排序
		
	private:
		static CMarkObject instance;
		
		CChineseFont m_ChineseFont;
		std::vector<MARKDATA> m_vMarkData;	//标注信息
		bool m_bDraw;
		
		Vector3 m_LastPos;
		Vector3 m_LastDir;
		
	public:
		std::vector<ChunkItemPtr> m_vAllMarkIcon;	//标注图标
};

#endif