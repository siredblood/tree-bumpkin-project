/******************************************************************************
 ���ã�ͳһ�����Ⱦ���ºͼ��̲��������ƶ�������ִ�е��Ⱥ�˳��		
 ��Ҫ����������MainLoopTask��˼·�������MainLoopTaskԴ�벻�ɼ�
 ���޼����¼��Ŀ��ƣ�Ϊ���ⲻ��Ҫ���鷳�Լ���д���ƵĹ����ࡣ		
******************************************************************************/

#ifndef ITask_h__
#define ITask_h__

/**
 * ����ӿڣ���������Ⱦ�����µȽӿ�
 */
class ITask
{
public:
	ITask() : enableDraw( true ) {}
	virtual ~ITask() {}
	
	virtual void init() {}
	virtual void fini() {}
	
	virtual void tick( float dTime ) {}
	virtual void draw() {}
	
	virtual void handleKeyEvent( const KeyEvent & event ) {}
	virtual void handleMouseEvent( const MouseEvent & event ) {}
	
private:
	bool enableDraw;
};

/**
 * �ӿڹ����࣬�����е���������й���
 */
class TaskManager : ITask
{
public:
	TaskManager();
	virtual ~TaskManager();
	
	static TaskManager& instance();
	
	virtual void init();
	virtual void fini();
	
	virtual void tick( float dTime );
	virtual void draw();
	
	virtual void handleKeyEvent( const KeyEvent & event );
	virtual void handleMouseEvent( const MouseEvent & event );
	
	/**
	 *	�ڸ�������Ĺ��캯���е�������
	 *  TaskManager::instance().add( this, "b", ">a", NULL )
	 *  ��������������ӵ�������Ĵ洢�ṹ��
	 *	���ݷ�����֪�ô�����Լ��Ϊ__cdecl�����������������ջ��
	 *	����Ӧ�õ�C/C++�Ŀɱ��������(�Ƚ��鷳��)��������������
	 *	Լ�����������������������ջ���ڴ��Ӧƫ��sizeof(type)λ
	 *	���ɻ�ȡ�ɱ���������ݡ�
	 *
	 *	ע�⣺�������������cppǰ���������static xxx instance_��
	 *		  ��������ʱ���Զ��󶨲�������ࡣ���û������������
	 *		  ���ֶ�����xxx::instance().xxx()ʱ���а󶨣���init()
	 *		  ���޷�������
	 *
	 *	@param task	������ָ��(this)
	 *	
	 *	@param name	Ψһ�̶��������ƣ���
	 *
	 *	@param ...	�ɱ����������̶�Ϊ�ַ������ݡ�����'>xxx'�ǽ�����XXX��
	 *				'<xxx'�ǽ�����xxxǰ�棬��NULLΪ�������
	 *		
	 */
	void add( ITask* task, const char* name, ... );
	
	/**
	 * ����ָ��ɾ��
	 */
	void del( ITask* task );
	
	/**
	 * ��������ɾ��
	 */
	void del( const char* name );
	
	/**
	 * ������������������Ӧ��ָ��
	 */
	ITask* getTask( const char* name );
	
	/**
	 * �Ƿ��ѳ�ʼ�����
	 */
	bool initted() { return initted_; }
	
private:

	/**
	 * ˽�л����������͸�ֵ��������ֹ�ⲿ���������Ĳ��ɲ�����
	 */
	TaskManager( const TaskManager& ) {}
	TaskManager& operator=( const TaskManager& ) {}
	
	/**
	 * ��������б�
	 */
	void sort();
	
	/**
	 * ����ʹ�õ�StringMapΪ���汾������ͣ������hashmap��vector��
	 * ��������������������Ͷ����ĵ�֧��Ч�ʽϸߣ��Ҹ���ȫ�ɿ�!����ô�����������ˣ�
	 */
	typedef StringMap< ITask* > TaskMap;
	
	//�洢����˳���б�
	typedef std::vector< int > OrderList;
	
	//�洢�����б�
	typedef std::vector< const char* > RuleList;
	
	TaskMap taskMap_;
	OrderList orderList_;
	RuleList ruleList_;
	
	bool initted_;	
	
	/**
	 *	�ƶ�����
	 */
	class Rules
	{
	public:
		Rules( const TaskMap& tm, const RuleList& rl ) : tm_( tm ), rl_( rl ) {}
		bool operator()( const int& arg1, const int& arg2 );
	
	private:
		const TaskMap& tm_;
		const RuleList& rl_;
	};
	
	/**
	 *	����Ϊ��Ԫ����ΪTaskManager˽����
	 */
	friend class Rules;
};

#endif // ITask_h__