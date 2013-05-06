#ifndef _MCI_PLAYER_MGR_H_
#define _MCI_PLAYER_MGR_H_

#include <vector>
#include <string>
#include <algorithm>
#include "MCIPlayer.h"

class CMCIPlayerMgr
{
private:
	CMCIPlayerMgr();
	CMCIPlayerMgr(const CMCIPlayerMgr &rhs);
	CMCIPlayerMgr &operator=(const CMCIPlayerMgr &rhs);
	static CMCIPlayerMgr s_instance;

public:
	~CMCIPlayerMgr();
	static CMCIPlayerMgr &Instance();

	// 初始化，必须调用
	void init(HWND hWnd);

	// 获取所有播放文件
	std::vector<std::string> getFiles(){ return m_vAllFiles; }

	bool isPause(){ return m_bPause; }

	DWORD playDefault();
	DWORD play(const std::vector<std::string> &vFiles);
	DWORD pause();
	DWORD resume();
	DWORD stop();

	DWORD next();
	DWORD prev();

	// 添加
	bool add(const std::vector<std::string> &vFiles);
	// 删除
	bool del(const std::vector<std::string> &vFiles);

	// 获取当前曲目
	std::string getCurrentName();

private:
	// 文件操作
	void findFiles(const std::string &strFolder, std::vector<std::string> &vFiles);
	int copyFile(const std::string &fromFile, const std::string &toFile);
	int copyFiles(const std::string &fromPath, const std::string &toPath, 
		const std::vector<std::string> &vFileNames);
	int delFile(const std::string &file);
	int delFiles(const std::vector<std::string> &vFiles);
	// 获取正确的路径，末尾含'\'
	std::string getRightPath(const std::string &path);

	// 获取文件全路径
	std::vector<std::string> getFilesPath(const std::vector<std::string> &vFiles);

private:
	CMCIPlayer m_mciPlayer;
	std::string m_strRoot;
	std::vector<std::string> m_vAllFiles;
	bool m_bPause;
};

#endif