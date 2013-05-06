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

	// ��ʼ�����������
	void init(HWND hWnd);

	// ��ȡ���в����ļ�
	std::vector<std::string> getFiles(){ return m_vAllFiles; }

	bool isPause(){ return m_bPause; }

	DWORD playDefault();
	DWORD play(const std::vector<std::string> &vFiles);
	DWORD pause();
	DWORD resume();
	DWORD stop();

	DWORD next();
	DWORD prev();

	// ���
	bool add(const std::vector<std::string> &vFiles);
	// ɾ��
	bool del(const std::vector<std::string> &vFiles);

	// ��ȡ��ǰ��Ŀ
	std::string getCurrentName();

private:
	// �ļ�����
	void findFiles(const std::string &strFolder, std::vector<std::string> &vFiles);
	int copyFile(const std::string &fromFile, const std::string &toFile);
	int copyFiles(const std::string &fromPath, const std::string &toPath, 
		const std::vector<std::string> &vFileNames);
	int delFile(const std::string &file);
	int delFiles(const std::vector<std::string> &vFiles);
	// ��ȡ��ȷ��·����ĩβ��'\'
	std::string getRightPath(const std::string &path);

	// ��ȡ�ļ�ȫ·��
	std::vector<std::string> getFilesPath(const std::vector<std::string> &vFiles);

private:
	CMCIPlayer m_mciPlayer;
	std::string m_strRoot;
	std::vector<std::string> m_vAllFiles;
	bool m_bPause;
};

#endif