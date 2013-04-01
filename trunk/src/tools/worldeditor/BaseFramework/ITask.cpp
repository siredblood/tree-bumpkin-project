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
	//fini�Ӻ���ǰִ��
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
	//����ָ�룬ͬ����ֻ����һ��ʵ�� insert( std::markpair(xx,xx) )
	taskMap_[ name ] = task;
	
	//�����ɱ����ָ��
	va_list ap;
	va_start( ap, name );
	
	/**
	 *	��ȡ�ɱ�������ݣ����ݶ����֪��
	 *	�ú���ڴ����sizeof(char*)λƫ��
	 */
	char* arg = va_arg( ap, char* );
	
	if ( NULL == arg )
	{
		ruleList_.resize( taskMap_.size() );
		ruleList_[ taskMap_.size() - 1 ] = arg;
	}
	
	while ( NULL != arg ) //������Ǻ�ΪNULL
	{	
		/**
		 *	������� '>'��'<'����洢�ṹ�е���Ŵ�С
		 *  '>'��ʾ�������п���
		 *  '<'��ʾ�������п�ǰ
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
 *	������� '>'��'<'����洢�ṹ�е���Ŵ�С
 *  '>'��ʾ�������п���
 *  '<'��ʾ�������п�ǰ
 */
void TaskManager::sort()
{
	//��ԭ
	if ( orderList_.size() != taskMap_.size() )
	{
		orderList_.resize( taskMap_.size() );
		for ( uint i = 0; i < taskMap_.size(); i++ )
		{
			orderList_[ i ] = i;
		}
	}
	
	OrderList ol = orderList_;

	//����
	for ( uint i = 0; i < orderList_.size(); i++ )
	{
		char* rule = ( char* )ruleList_[ i ];
		
		if ( NULL == rule )
			continue;
			
		if ( '<' == *rule )
		{
			//��ǰ�ƶ�һλ
			rule++;
			TaskMap::iterator it = taskMap_.find( rule );
			if ( it != taskMap_.end() )
			{
				/**
				 *	����������ָ�������������ĸ���
				 *	�����������֧�����ֲ������Զ�ת��Ϊ
				 *	( &p - &q ) / sizeof( type )
				 *	��ͬ�� &(*it) - &taskMap[0]��ִ��sar esi,5����ƫ��5λ
				 */
				int taskId = it - taskMap_.begin();
				int tmpID = ol[ i ];
				
				OrderList::iterator it2;
				
				//��ʵ�������Ƚ��ٵ�����£��������Բ���
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
				 *	����������ָ�������������ĸ���
				 *	�����������֧�����ֲ������Զ�ת��Ϊ
				 *	( &p - &q ) / sizeof( type )
				 *	��ͬ�� &(*it) - &taskMap[0]��ִ��sar esi,5����ƫ��5λ
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
 *	�ƶ��������
 */
bool TaskManager::Rules::operator()( const int& arg1, const int& arg2 )
{
	std::string t1 = ( tm_.begin() + arg1 )->first;
	std::string t2 = ( tm_.begin() + arg2 )->first;
	
	char* r1 = (char*)*( rl_.begin() + arg1 );
	
	return t1 > t2;	
}