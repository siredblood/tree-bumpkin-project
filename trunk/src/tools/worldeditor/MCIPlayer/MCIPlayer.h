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

	// ��ʼ�����������
	void init(HWND  hWnd);

	//����
	DWORD play(const std::vector<std::string> &vFiles);
	DWORD replay();

	//��ͣ
	DWORD pause();

	//�ָ�
	DWORD resume();

	//ֹͣ
	DWORD stop();

	// ��һ��
	DWORD next();

	// ��һ��
	DWORD prev();

	//�Ƿ񲥷Ž���
	bool isFinish();

	// ��ȡ������Ϣ
	std::string getErrorMsg(DWORD dwError);  

	// ��ȡ��Ŀ����
	std::string getCurrentName();

	// ���²����б�
	void updatePlayList(const std::vector<std::string> &vFiles);

private:

	MCIDEVICEID m_uiDeviceID;// �豸��
	MCIDEVICEID m_uiElementID; // ��Ŀ��

	HWND m_hWnd;
	std::vector<std::string> m_vFiles;
	size_t m_iCurrent;

	// �򿪡��ر��豸
	DWORD openDevice();
	DWORD closeDevice();

	// ����
	DWORD play(const std::string &strMusicPath="");

	// ���¿�ʼ����
	DWORD repeat();

	//��ȡ��Ŀ��Ϣ
	void getMusicInfo(DWORD dwParam, DWORD &info);
};