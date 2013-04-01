#ifndef SCREEN_SHOT_HPP
#define SCREEN_SHOT_HPP

#include "worldeditor/BaseFramework/ITask.hpp"

class ScreenShot : public ITask
{
public:
	ScreenShot(void);
	~ScreenShot(void);
	
	static ScreenShot &Instance();
	
	/*virtual*/ void tick( float dTime );
	/*virtual*/ void handleKeyEvent( const KeyEvent & event );	
	
	/**
	 *	��ʼ¼��
	 */
	void BeginScreen();		
	
	/**
	 *	����¼��
	 */
	void EndScreen();
	
private:
	/**
	 *	��鲢�Զ�������Ŀ¼
	 */
	void CheckAndCreateFolder();		
	
private:
	static ScreenShot instance_;
	
	/**
	 *	ͼƬ��ŵ��ļ���(Ĭ�ϴ����"ִ���ļ�Ŀ¼\ScreenShot\"��)
	 */
	std::string strSaveFolder_;
	
	/**
	 *	���ɵ�ͼƬ��ʽ��Ĭ��Ϊjpg��
	 */
	std::string strPicType_;
	
	bool bSreen_;
	
	/**
	 *	���ɵ�ͼƬ���ļ����ƣ�Ĭ����1��ʼ��
	 */
	int  index_;
};

#endif