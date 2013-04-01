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
	 *	开始录制
	 */
	void BeginScreen();		
	
	/**
	 *	结束录制
	 */
	void EndScreen();
	
private:
	/**
	 *	检查并自动创建新目录
	 */
	void CheckAndCreateFolder();		
	
private:
	static ScreenShot instance_;
	
	/**
	 *	图片存放的文件夹(默认存放于"执行文件目录\ScreenShot\"下)
	 */
	std::string strSaveFolder_;
	
	/**
	 *	生成的图片格式（默认为jpg）
	 */
	std::string strPicType_;
	
	bool bSreen_;
	
	/**
	 *	生成的图片的文件名称（默认由1开始）
	 */
	int  index_;
};

#endif