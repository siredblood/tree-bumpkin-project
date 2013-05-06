// DlgMusicMgr.cpp : ʵ���ļ�
//

#include "pch.hpp"
#include "DlgMusicMgr.h"
#include "MCIPlayerMgr.h"

std::auto_ptr<CDlgMusicMgr> CDlgMusicMgr::s_pInstance;
// CDlgMusicMgr �Ի���

IMPLEMENT_DYNAMIC(CDlgMusicMgr, CXTPResizeDialog)

CDlgMusicMgr::CDlgMusicMgr(CWnd* pParent /*=NULL*/)
	: CXTPResizeDialog(CDlgMusicMgr::IDD, pParent)
{

}

CDlgMusicMgr::~CDlgMusicMgr()
{
}

CDlgMusicMgr &CDlgMusicMgr::Instance()
{
	if( s_pInstance.get() == NULL )
	{
		std::auto_ptr<CDlgMusicMgr> pDlg( new CDlgMusicMgr() );
		s_pInstance = pDlg;
		s_pInstance->Create( CDlgMusicMgr::IDD );
	}

	return *s_pInstance;
}

void CDlgMusicMgr::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizeDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_checkList);
}

BEGIN_MESSAGE_MAP(CDlgMusicMgr, CXTPResizeDialog)
	ON_BN_CLICKED(IDC_BTN_ADD, &CDlgMusicMgr::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, &CDlgMusicMgr::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_PLAY, &CDlgMusicMgr::OnBnClickedBtnPlay)
	ON_BN_CLICKED(IDC_BTN_PAUSECONTINUE, &CDlgMusicMgr::OnBnClickedBtnPausecontinue)
	ON_BN_CLICKED(IDC_BTN_STOP, &CDlgMusicMgr::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CDlgMusicMgr::OnBnClickedBtnClose)
	ON_BN_CLICKED(IDC_CHECK, &CDlgMusicMgr::OnBnClickedCheck)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_NEXT, &CDlgMusicMgr::OnBnClickedBtnNext)
	ON_BN_CLICKED(IDC_BTN_PREV, &CDlgMusicMgr::OnBnClickedBtnPrev)
END_MESSAGE_MAP()

BOOL CDlgMusicMgr::OnInitDialog()
{
	CXTPResizeDialog::OnInitDialog();

	// initialize the list box.
	m_checkList.Initialize();
	InitCheckListBox();

	((CButton *)GetDlgItem(IDC_CHECK))->SetCheck(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgMusicMgr::InitCheckListBox()
{
	m_checkList.ResetContent();
	std::vector<std::string> vFiles = CMCIPlayerMgr::Instance().getFiles();
	for(size_t i=0; i<vFiles.size(); i++){
		m_checkList.InsertString(i, vFiles[i].c_str());
		m_checkList.SetCheck(i, 1);
	}
}

void CDlgMusicMgr::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CXTPResizeDialog::OnClose();
}

// CDlgMusicMgr ��Ϣ�������

void CDlgMusicMgr::OnBnClickedBtnAdd()
{
	CFileDialog fileDlg(TRUE, "", NULL, 
		OFN_ALLOWMULTISELECT | OFN_ENABLESIZING | OFN_HIDEREADONLY, 
		"wav�ļ�(*.wav)|*.wav||",
		AfxGetMainWnd());
	// ����50���ļ�
	fileDlg.m_ofn.nMaxFile = 50 * MAX_PATH;
	fileDlg.m_ofn.lpstrFile = new TCHAR[fileDlg.m_ofn.nMaxFile]; 

	//���ڴ������   
	ZeroMemory(fileDlg.m_ofn.lpstrFile,sizeof(TCHAR) * fileDlg.m_ofn.nMaxFile); 
	std::vector<std::string> vFiles;
	if (fileDlg.DoModal () == IDOK){
		//��ȡ��һ���ļ���λ��
		POSITION filePos;
		filePos = fileDlg.GetStartPosition();
		//std::string fromPath = fileDlg.GetPathName()+"\\";
		//ѭ������ÿ��·���������������
		while(filePos != NULL){

			//��ȡ�ļ�·��
			std::string pathName = fileDlg.GetNextPathName(filePos).GetBuffer(0);
			//��ȡ�ļ��� 
			//std::string fileName = pathName.substr(pathName.find_last_of('\\')+1, pathName.length());
			vFiles.push_back(pathName);
		}
	}
	if(vFiles.empty()) return;

	// ����ļ�
	if(CMCIPlayerMgr::Instance().add(vFiles)){
		MessageBox("�ɹ�����ļ���", "��ʾ", MB_OK);
	}else{
		MessageBox("����ļ�ʧ�ܣ�", "��ʾ", MB_OK);
	}
	InitCheckListBox();
}

void CDlgMusicMgr::OnBnClickedBtnDel()
{
	if(MessageBox("ɾ���ļ������ɻָ���ȷ��ɾ����","����", MB_YESNO)!=IDYES)
		return;

	if(CMCIPlayerMgr::Instance().del(getCheckedItems())){
		MessageBox("�ɹ�ɾ���ļ���", "��ʾ", MB_OK);
	}else{
		MessageBox("ɾ���ļ�ʧ�ܣ�", "��ʾ", MB_OK);
	}
	InitCheckListBox();
}

void CDlgMusicMgr::OnBnClickedBtnPlay()
{
	CMCIPlayerMgr::Instance().play(getCheckedItems());
	updateState();
}

void CDlgMusicMgr::OnBnClickedBtnPausecontinue()
{
	if(CMCIPlayerMgr::Instance().isPause()){
		CMCIPlayerMgr::Instance().resume();
	}else{
		CMCIPlayerMgr::Instance().pause();
	}
	updateState();
}

void CDlgMusicMgr::OnBnClickedBtnStop()
{
	CMCIPlayerMgr::Instance().stop();
	updateState();
}

void CDlgMusicMgr::OnBnClickedBtnClose()
{
	s_pInstance->ShowWindow(SW_HIDE);
}

void CDlgMusicMgr::OnBnClickedCheck()
{
	static bool s_selected = true;
	s_selected = !s_selected;
	int checked = s_selected ? 1 : 0;
	for(int i=0; i<m_checkList.GetCount(); i++){
		m_checkList.SetCheck(i, checked);
	}
}

std::vector<std::string> CDlgMusicMgr::getCheckedItems()
{
	std::vector<std::string> vFiles;
	for(int i=0; i<m_checkList.GetCount(); i++){
		if(m_checkList.GetCheck(i)==1){
			CString strText;
			m_checkList.GetText( i, strText );
			vFiles.push_back(strText.GetBuffer());
		}
	}
	return vFiles;
}

void CDlgMusicMgr::OnBnClickedBtnNext()
{
	CMCIPlayerMgr::Instance().next();
	updateState();
}

void CDlgMusicMgr::OnBnClickedBtnPrev()
{
	CMCIPlayerMgr::Instance().prev();
	updateState();
}

void CDlgMusicMgr::updateState()
{
	if(CMCIPlayerMgr::Instance().isPause()){
		GetDlgItem(IDC_BTN_PAUSECONTINUE)->SetWindowText("��ͣ");
	}else{
		GetDlgItem(IDC_BTN_PAUSECONTINUE)->SetWindowText("����");
	}
	std::string title("��ǰ���� ");
	title += CMCIPlayerMgr::Instance().getCurrentName().c_str();
	SetWindowText(title.c_str());
}
