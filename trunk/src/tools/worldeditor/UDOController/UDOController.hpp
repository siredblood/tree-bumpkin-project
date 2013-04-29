/************************************************************************/
/* 自定义UserDataObject控制，包括节点的遍历和获取等                     */
/************************************************************************/

#ifndef UDOController_h__
#define UDOController_h__

#include "UDOHeader.hpp"
#include "worldeditor/world/items/editor_chunk_user_data_object.hpp"
#include "worldeditor/world/editor_chunk.hpp"

#include "worldeditor/BaseFramework/ITask.hpp"


class UDOController : public ITask
{
public:
	~UDOController();
	static UDOController& instance();

	// 设置处理鼠标左键
	void setHandle( bool bHandle ) { m_bHandle = bHandle; }

	// 从数据库读取数据创建UDO
	void makeUdoFromDB( int pid, int firstid );

	// 处理鼠标按键事件
	void handleMouseEvent( const MouseEvent & event );

	// 通过第一个UDO的GUID保存数据
	void saveUdoData();

	// 删除对象
	void delUdo( const std::string &guid );

	// 获取
	void getUdoData( std::vector< UDOCameraNode > &vUdo );

	// 清空所有UDO对象
	void clearUdo();

	// 测试飞行
	void Fly( const UDOCamera &udoCamera, bool bDiffer );

	// 更新速度
	void updateSpeed( const std::map<std::string, TempStruct> &mapSpeed  );

	// 设置PID
	void setPID( int pid );

	// 判断路径是否已经存在,传入第一个节点ID
	bool isUdoExist( int id );
	
	//后台加载对象
	void tick( float dTime );

	// 数据库操作
	/**
	* 将原有的数据删除，存入指定的节点到数据库
	* pid 数据库的ID
	*/ 
	BOOL saveToDB( int pid, const std::vector< UDOCameraNode >& nodes );

	/**
	* 加载指定ID的节点数据并载入三维场景
	*/
	BOOL loadFromDB( int pid, std::vector< UDOCameraNode >& nodes );

	// 删除节点
	// 参数：
	//		id	- 节点ID
	//		pid	- 父节点为pid的所有节点
	BOOL delNodeFromDB( int id );
	BOOL delNodesFromDB( int pid );

	// 获取GUID所对应的编号
	int getID( const std::string &strGuid );

	// 获取编号所对应的GUID
	std::string getGuid( int id );
	
	//是否后台加载中
	void setCanLoad( bool can ) { canLoad_ = can; }
	bool getCanLoad() { return canLoad_; }
	
	//设置加载状态 
	void stopLoading();
	
	//返回数据库加载的对象
	void getDBNodes( std::vector< UDOCameraNode >& dbNodes ) { dbNodes = dbNodes_; }

	//返回全部节点是否载入成功
	bool getLoadedStatus() { return m_bSuccess; }
	
private:
	UDOController();
	UDOController( const UDOController &rhs );
	UDOController &operator=( const UDOController &rhs );
	
	/**
	*	指定第一个节点的guid，通过该guid来获取整个链的节点数据。
	*  udo传递的是一个地址，通过该地址来返回数据
	*/ 
	void getLinkObjects( std::vector< UDOCameraNode > &vUdoCN, const std::string& firstGUID );

	/**
	 *	递归链接节点
	 */ 
	void getLinkObject( std::vector< UDOCameraNode > &vUdoCN, const std::string& guid );	

	// 成员声明
	std::map<std::string, EditorChunkUserDataObject* > m_objects;
	std::string		m_strGuid;	// 第一个节点的GUID
	int				m_iPathId;	// 路径ID
	int				m_iPid;		// 当前路径的所有节点的PID
	bool			m_bHandle;	// 处理鼠标点击事件标记
	bool			m_bSuccess; // 节点是否加载完成

	std::map<std::string, TempStruct>	m_mapTemp;	// 临时数据结构
	
	static UDOController s_instance_;
	
	//临时存储未加载的对象
	std::set< UDOCameraNode* > nodes_; 
	bool canLoad_;
	
	//数据库对象存储器
	std::vector< UDOCameraNode > dbNodes_;
	
};


#endif // UDOController_h__