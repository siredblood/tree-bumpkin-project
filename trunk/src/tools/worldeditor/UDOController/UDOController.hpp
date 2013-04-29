/************************************************************************/
/* �Զ���UserDataObject���ƣ������ڵ�ı����ͻ�ȡ��                     */
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

	// ���ô���������
	void setHandle( bool bHandle ) { m_bHandle = bHandle; }

	// �����ݿ��ȡ���ݴ���UDO
	void makeUdoFromDB( int pid, int firstid );

	// ������갴���¼�
	void handleMouseEvent( const MouseEvent & event );

	// ͨ����һ��UDO��GUID��������
	void saveUdoData();

	// ɾ������
	void delUdo( const std::string &guid );

	// ��ȡ
	void getUdoData( std::vector< UDOCameraNode > &vUdo );

	// �������UDO����
	void clearUdo();

	// ���Է���
	void Fly( const UDOCamera &udoCamera, bool bDiffer );

	// �����ٶ�
	void updateSpeed( const std::map<std::string, TempStruct> &mapSpeed  );

	// ����PID
	void setPID( int pid );

	// �ж�·���Ƿ��Ѿ�����,�����һ���ڵ�ID
	bool isUdoExist( int id );
	
	//��̨���ض���
	void tick( float dTime );

	// ���ݿ����
	/**
	* ��ԭ�е�����ɾ��������ָ���Ľڵ㵽���ݿ�
	* pid ���ݿ��ID
	*/ 
	BOOL saveToDB( int pid, const std::vector< UDOCameraNode >& nodes );

	/**
	* ����ָ��ID�Ľڵ����ݲ�������ά����
	*/
	BOOL loadFromDB( int pid, std::vector< UDOCameraNode >& nodes );

	// ɾ���ڵ�
	// ������
	//		id	- �ڵ�ID
	//		pid	- ���ڵ�Ϊpid�����нڵ�
	BOOL delNodeFromDB( int id );
	BOOL delNodesFromDB( int pid );

	// ��ȡGUID����Ӧ�ı��
	int getID( const std::string &strGuid );

	// ��ȡ�������Ӧ��GUID
	std::string getGuid( int id );
	
	//�Ƿ��̨������
	void setCanLoad( bool can ) { canLoad_ = can; }
	bool getCanLoad() { return canLoad_; }
	
	//���ü���״̬ 
	void stopLoading();
	
	//�������ݿ���صĶ���
	void getDBNodes( std::vector< UDOCameraNode >& dbNodes ) { dbNodes = dbNodes_; }

	//����ȫ���ڵ��Ƿ�����ɹ�
	bool getLoadedStatus() { return m_bSuccess; }
	
private:
	UDOController();
	UDOController( const UDOController &rhs );
	UDOController &operator=( const UDOController &rhs );
	
	/**
	*	ָ����һ���ڵ��guid��ͨ����guid����ȡ�������Ľڵ����ݡ�
	*  udo���ݵ���һ����ַ��ͨ���õ�ַ����������
	*/ 
	void getLinkObjects( std::vector< UDOCameraNode > &vUdoCN, const std::string& firstGUID );

	/**
	 *	�ݹ����ӽڵ�
	 */ 
	void getLinkObject( std::vector< UDOCameraNode > &vUdoCN, const std::string& guid );	

	// ��Ա����
	std::map<std::string, EditorChunkUserDataObject* > m_objects;
	std::string		m_strGuid;	// ��һ���ڵ��GUID
	int				m_iPathId;	// ·��ID
	int				m_iPid;		// ��ǰ·�������нڵ��PID
	bool			m_bHandle;	// ����������¼����
	bool			m_bSuccess; // �ڵ��Ƿ�������

	std::map<std::string, TempStruct>	m_mapTemp;	// ��ʱ���ݽṹ
	
	static UDOController s_instance_;
	
	//��ʱ�洢δ���صĶ���
	std::set< UDOCameraNode* > nodes_; 
	bool canLoad_;
	
	//���ݿ����洢��
	std::vector< UDOCameraNode > dbNodes_;
	
};


#endif // UDOController_h__