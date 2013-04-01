/******************************************************************************
 作用：统一类的渲染更新和键盘操作，可制定派生类执行的先后顺序。		
 主要根据引擎中MainLoopTask的思路搭建。由于MainLoopTask源码不可见
 且无键盘事件的控制，为避免不必要的麻烦自己重写类似的管理类。		
******************************************************************************/

#ifndef ITask_h__
#define ITask_h__

/**
 * 基类接口，定义了渲染、更新等接口
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
 * 接口管理类，对所有的派生类进行管理
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
	 *	在各派生类的构造函数中调用类似
	 *  TaskManager::instance().add( this, "b", ">a", NULL )
	 *  方法，将各类添加到管理类的存储结构。
	 *	根据反汇编可知该处调用约定为__cdecl，参数从右至左进入栈。
	 *	这里应用到C/C++的可变参数特征(比较麻烦！)，根据上述调用
	 *	约定，参数依次由右至左进入栈，内存对应偏移sizeof(type)位
	 *	即可获取可变参数的内容。
	 *
	 *	注意：派生类必须在类cpp前声明该类的static xxx instance_，
	 *		  程序运行时将自动绑定并构造该类。如果没有先行声明，
	 *		  则将手动运行xxx::instance().xxx()时进行绑定，但init()
	 *		  将无法起作用
	 *
	 *	@param task	派生类指针(this)
	 *	
	 *	@param name	唯一固定的类名称，如
	 *
	 *	@param ...	可变参数，这里固定为字符串传递。其中'>xxx'是将排序靠XXX后，
	 *				'<xxx'是将排序靠xxx前面，以NULL为结束标记
	 *		
	 */
	void add( ITask* task, const char* name, ... );
	
	/**
	 * 根据指针删除
	 */
	void del( ITask* task );
	
	/**
	 * 根据名称删除
	 */
	void del( const char* name );
	
	/**
	 * 根据名称索引返回相应的指针
	 */
	ITask* getTask( const char* name );
	
	/**
	 * 是否已初始化完成
	 */
	bool initted() { return initted_; }
	
private:

	/**
	 * 私有化拷贝函数和赋值函数，防止外部误调用引起的不可测问题
	 */
	TaskManager( const TaskManager& ) {}
	TaskManager& operator=( const TaskManager& ) {}
	
	/**
	 * 排序调用列表
	 */
	void sort();
	
	/**
	 * 这里使用的StringMap为引擎本身的类型，结合了hashmap和vector。
	 * 根据引擎的描述，该类型对中文的支持效率较高，且更安全可靠!你信么？反正我信了！
	 */
	typedef StringMap< ITask* > TaskMap;
	
	//存储调用顺序列表
	typedef std::vector< int > OrderList;
	
	//存储规则列表
	typedef std::vector< const char* > RuleList;
	
	TaskMap taskMap_;
	OrderList orderList_;
	RuleList ruleList_;
	
	bool initted_;	
	
	/**
	 *	制定规则
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
	 *	声明为友元，做为TaskManager私有类
	 */
	friend class Rules;
};

#endif // ITask_h__