#include "pch.hpp"
#include "ITask.hpp"

//System va
#include <stdarg.h>

TaskManager::TaskManager() : initted_( false )
{ }

TaskManager::~TaskManager()
{ }

TaskManager& TaskManager::instance()
{
	static TaskManager instance_;
	return instance_;
}

void TaskManager::init()
{
	OrderList::iterator it = orderList_.begin();
	OrderList::iterator end = orderList_.end();
	while ( it != end )
	{
		( taskMap_.begin() + (*it) )->second->init();
		++it;
	}
	
	initted_ = true;
}

void TaskManager::fini()
{
	//fini从后往前执行
	OrderList::reverse_iterator it = orderList_.rbegin();
	OrderList::reverse_iterator end = orderList_.rend();
	
	while ( it != end )
	{
		( taskMap_.begin() + (*it) )->second->fini();
		it++;
	}
}

void TaskManager::tick( float dTime )
{
	OrderList::iterator it = orderList_.begin();
	OrderList::iterator end = orderList_.end();
	while ( it != end )
	{
		( taskMap_.begin() + (*it) )->second->tick( dTime );
		++it;
	}
}

void TaskManager::draw()
{
	OrderList::iterator it = orderList_.begin();
	OrderList::iterator end = orderList_.end();
	while ( it != end )
	{
		( taskMap_.begin() + (*it) )->second->draw();
		++it;
	}
}

void TaskManager::handleKeyEvent( const KeyEvent & event )
{
	OrderList::iterator it = orderList_.begin();
	OrderList::iterator end = orderList_.end();
	while ( it != end )
	{
		( taskMap_.begin() + (*it) )->second->handleKeyEvent( event );
		++it;
	}
}

void TaskManager::handleMouseEvent( const MouseEvent & event )
{
	OrderList::iterator it = orderList_.begin();
	OrderList::iterator end = orderList_.end();
	while ( it != end )
	{
		( taskMap_.begin() + (*it) )->second->handleMouseEvent( event );
		++it;
	}
}

void TaskManager::add( ITask* task, const char* name, ... )
{
	//插入指针，同名将只保存一个实例 insert( std::markpair(xx,xx) )
	taskMap_[ name ] = task;
	
	//声明可变参数指针
	va_list ap;
	va_start( ap, name );
	
	/**
	 *	获取可变参数内容，根据定义可知，
	 *	该宏对内存进行sizeof(char*)位偏移
	 */
	char* arg = va_arg( ap, char* );
	
	if ( NULL == arg )
	{
		ruleList_.resize( taskMap_.size() );
		ruleList_[ taskMap_.size() - 1 ] = arg;
	}
	
	while ( NULL != arg ) //结束标记号为NULL
	{	
		/**
		 *	排序规则 '>'、'<'代表存储结构中的序号大小
		 *  '>'表示在排序中靠后
		 *  '<'表示在排序中靠前
		 */
		//if ( '>' == *arg )
		//{
		//	arg++;
		//		
		//}
		//else if ( '<' == *arg )
		//{
		//	arg++;
		//}
	
		ruleList_.push_back( arg );
		
		arg = va_arg( ap, char* );
	}
	
	va_end( ap );
	
	sort();
}

void TaskManager::del( ITask* task )
{
	TaskMap::iterator it;
	for ( it = taskMap_.begin(); it != taskMap_.end(); it++ )
	{
		if ( it->second == task )
			break;
	}
	
	if ( it != taskMap_.end() )
	{
		int taskId = it - taskMap_.begin();
		taskMap_.erase( it );
		
		//ruleList
		ruleList_.erase( ruleList_.begin() + taskId );
		
		sort();	
	}
}

void TaskManager::del( const char* name )
{
	TaskMap::iterator it = taskMap_.find( name );
	if ( it != taskMap_.end() )
	{
		int taskId = it - taskMap_.begin();
		bool erased = taskMap_.erase( name );
		if ( erased )
		{
			//ruleList
			ruleList_.erase( ruleList_.begin() + taskId );

			sort();
		}
	} 
}

ITask* TaskManager::getTask( const char* name )
{
	TaskMap::iterator it = taskMap_.find( name );
	if ( it != taskMap_.end() )
	{	
		return it->second;
	}
	
	return NULL;
}


/**
 *	排序规则 '>'、'<'代表存储结构中的序号大小
 *  '>'表示在排序中靠后
 *  '<'表示在排序中靠前
 */
void TaskManager::sort()
{
	//复原
	if ( orderList_.size() != taskMap_.size() )
	{
		orderList_.resize( taskMap_.size() );
		for ( uint i = 0; i < taskMap_.size(); i++ )
		{
			orderList_[ i ] = i;
		}
	}
	
	OrderList ol = orderList_;

	//排序
	for ( uint i = 0; i < orderList_.size(); i++ )
	{
		char* rule = ( char* )ruleList_[ i ];
		
		if ( NULL == rule )
			continue;
			
		if ( '<' == *rule )
		{
			//向前移动一位
			rule++;
			TaskMap::iterator it = taskMap_.find( rule );
			if ( it != taskMap_.end() )
			{
				/**
				 *	数组中两个指针相减等于相隔的个数
				 *	大多数编译器支持这种操作并自动转换为
				 *	( &p - &q ) / sizeof( type )
				 *	等同于 &(*it) - &taskMap[0]，执行sar esi,5向右偏移5位
				 */
				int taskId = it - taskMap_.begin();
				int tmpID = ol[ i ];
				
				OrderList::iterator it2;
				
				//类实例数量比较少的情况下，采用线性查找
				for ( it2 = orderList_.begin(); it2 != orderList_.end(); it2++ )
				{
					if ( tmpID == *it2 )
						break;
				}
				orderList_.erase( it2 );
				
				taskId = ( taskId == 0 ) ? 0 : ( taskId - 1 );
				orderList_.insert( orderList_.begin() + taskId, tmpID );
			}
		}
		else if ( '>' == *rule )
		{
			rule++;
			TaskMap::iterator it = taskMap_.find( rule );
			if ( it != taskMap_.end() )
			{
				/**
				 *	数组中两个指针相减等于相隔的个数
				 *	大多数编译器支持这种操作并自动转换为
				 *	( &p - &q ) / sizeof( type )
				 *	等同于 &(*it) - &taskMap[0]，执行sar esi,5向右偏移5位
				 */
				int taskId = it - taskMap_.begin();
				int tmpID = ol[ i ];
				
				OrderList::iterator it2;
				for ( it2 = orderList_.begin(); it2 != orderList_.end(); it2++ )
				{
					if ( tmpID == *it2 )
						break;
				}
				orderList_.erase( it2 );
				orderList_.insert( orderList_.begin() + taskId, tmpID );
			}
		}
	}
	
	/*
	Rules rule( taskMap_, ruleList_ );
	std::sort( orderList_.begin(), orderList_.end(), rule ); 
	*/
}

/**
 *	制定排序规则
 */
bool TaskManager::Rules::operator()( const int& arg1, const int& arg2 )
{
	std::string t1 = ( tm_.begin() + arg1 )->first;
	std::string t2 = ( tm_.begin() + arg2 )->first;
	
	char* r1 = (char*)*( rl_.begin() + arg1 );
	
	return t1 > t2;	
}