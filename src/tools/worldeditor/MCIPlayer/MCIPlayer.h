#pragma once 
#include <string>
#include <vector>
#include <mmsystem.h>
#pragma comment (lib,"winmm.lib")

#ifndef DWORD
#define DWORD unsigned long
#endif

class CMCIPlayer
{
public:
	CMCIPlayer();
	~CMCIPlayer();

	// 初始化，必须调用
	void init(HWND  hWnd);

	//播放
	DWORD play(const std::vector<std::string> &vFiles);
	DWORD replay();

	//暂停
	DWORD pause();

	//恢复
	DWORD resume();

	//停止
	DWORD stop();

	// 下一个
	DWORD next();

	// 上一个
	DWORD prev();

	//是否播放结束
	bool isFinish();

	// 获取错误信息
	std::string getErrorMsg(DWORD dwError);  

	// 获取曲目名称
	std::string getCurrentName();

	// 更新播放列表
	void updatePlayList(const std::vector<std::string> &vFiles);

private:

	MCIDEVICEID m_uiDeviceID;// 设备号
	MCIDEVICEID m_uiElementID; // 曲目号

	HWND m_hWnd;
	std::vector<std::string> m_vFiles;
	size_t m_iCurrent;

	// 打开、关闭设备
	DWORD openDevice();
	DWORD closeDevice();

	// 播放
	DWORD play(const std::string &strMusicPath="");

	// 重新开始播放
	DWORD repeat();

	//获取曲目信息
	void getMusicInfo(DWORD dwParam, DWORD &info);
};