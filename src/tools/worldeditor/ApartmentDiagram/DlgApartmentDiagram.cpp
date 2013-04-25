#include "pch.hpp"
#include "DlgApartmentDiagram.h"
#include "ApartmentDiagramMgr.h"


std::auto_ptr<CDlgApartmentDiagram> CDlgApartmentDiagram::s_pInstance;

// CDlgApartmentDiagram 对话框

IMPLEMENT_DYNAMIC(CDlgApartmentDiagram, CXTPDialogBase<CXTResizeDialog>)

CDlgApartmentDiagram::CDlgApartmentDiagram(CWnd* pParent /*=NULL*/)
: CXTPDialogBase<CXTResizeDialog>(CDlgApartmentDiagram::IDD, pParent)
, m_bInRepositionControls(FALSE)
, m_bInitDone(FALSE)
, m_rcBorders(CRect(0, 0, 0, 0))
{
}

CDlgApartmentDiagram::~CDlgApartmentDiagram(void)
{
}

CDlgApartmentDiagram &CDlgApartmentDiagram::Instance()
{
	if( s_pInstance.get() == NULL )
	{
		std::auto_ptr<CDlgApartmentDiagram> pDlg( new CDlgApartmentDiagram() );
		s_pInstance = pDlg;
		s_pInstance->Create( CDlgApartmentDiagram::IDD );
	}

	return *s_pInstance;
}

void CDlgApartmentDiagram::DoDataExchange(CDataExchange* pDX)
{
	CXTPDialogBase<CXTResizeDialog>::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlgApartmentDiagram, CXTPDialogBase<CXTResizeDialog>)
	//ON_COMMAND(ID_AD_FIRST, &CDlgApartmentDiagram::OnBnClickedFirst)
	//ON_UPDATE_COMMAND_UI(ID_AD_FIRST, &CDlgApartmentDiagram::OnUpdateFirst)
	ON_COMMAND(ID_AD_NEXT, &CDlgApartmentDiagram::OnBnClickedNext)
	ON_UPDATE_COMMAND_UI(ID_AD_NEXT, &CDlgApartmentDiagram::OnUpdateNext)
	ON_COMMAND(ID_AD_PREV, &CDlgApartmentDiagram::OnBnClickedPrev)
	ON_UPDATE_COMMAND_UI(ID_AD_PREV, &CDlgApartmentDiagram::OnUpdatePrev)
	//ON_COMMAND(ID_AD_LAST, &CDlgApartmentDiagram::OnBnClickedLast)
	//ON_UPDATE_COMMAND_UI(ID_AD_LAST, &CDlgApartmentDiagram::OnUpdateLast)
	ON_COMMAND(ID_AD_ADD, &CDlgApartmentDiagram::OnBnClickedAdd)
	ON_UPDATE_COMMAND_UI(ID_AD_ADD, &CDlgApartmentDiagram::OnUpdateAdd)
	ON_COMMAND(ID_AD_DEL, &CDlgApartmentDiagram::OnBnClickedDel)
	ON_UPDATE_COMMAND_UI(ID_AD_DEL, &CDlgApartmentDiagram::OnUpdateDel)

	ON_COMMAND(ID_AD_ALL, OnBnClickedAll)
	ON_MESSAGE(WM_KICKIDLE, &CDlgApartmentDiagram::OnKickIdle)
	ON_WM_SIZE()
	ON_WM_CLOSE()

	ON_WM_PAINT()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	//ID_INDICATOR_CAPS,
	//ID_INDICATOR_NUM,
	//ID_INDICATOR_SCRL,
};

BOOL CDlgApartmentDiagram::OnInitDialog()
{
	SetFlag(xtpResizeNoSizeIcon);
	CXTPDialogBase<CXTResizeDialog>::OnInitDialog();

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// 工具栏初始化
	VERIFY(InitCommandBars());

	CXTPPaintManager::SetTheme(xtpThemeOffice2003);
	CXTPCommandBars* pCommandBars = GetCommandBars();

	// 编辑
	CXTPToolBar* pBar = (CXTPToolBar*) pCommandBars->Add( _T("户型图"), xtpBarTop);
	if( !pBar )
		return -1;

	CXTPControl *pControl = NULL;

	pControl = pBar->GetControls()->Add(xtpControlButton, ID_AD_ADD);
	pControl->SetCaption(_T("增加"));
	pControl = pBar->GetControls()->Add(xtpControlButton, ID_AD_DEL);
	pControl->SetCaption(_T("删除"));

	pBar->GetControls()->Add(xtpControlLabel, 0)->SetCaption( _T("|") );

	CXTPControlPopup* pPopup = (CXTPControlPopup*)pControl->GetControls()->Add(xtpControlPopup, 0);
	pBar->GetControls()->Add(xtpControlLabel, 0)->SetCaption( _T("|") );

	pPopup->SetCaption(_T("户型图列表"));
	pListBox = (CXTPControlListBox*)pPopup->GetCommandBar()->GetControls()->Add(new CXTPControlListBox(), ID_AD_ALL);
	pListBox->SetWidth(200);
	pListBox->SetLinesMinMax(0,6);
	resetDiagramList();

	//pControl = pBar->GetControls()->Add(xtpControlButton, ID_AD_FIRST);
	//pControl->SetCaption( _T("第一张") );
	pControl = pBar->GetControls()->Add(xtpControlButton, ID_AD_NEXT);
	pControl->SetCaption( _T("下一张") );
	pControl = pBar->GetControls()->Add(xtpControlButton, ID_AD_PREV);
	pControl->SetCaption( _T("上一张") );
	//pControl = pBar->GetControls()->Add(xtpControlButton, ID_AD_LAST);
	//pControl->SetCaption( _T("最后一张") );

	// 不能移动啊
	pBar->EnableDocking( xtpFlagAlignTop  );

	SetControlStyle();

	// 调整工具栏位置
	m_bInitDone = TRUE;
	RepositionControls();

	pCommandBars->UpdateCommandBars();

	OnBnClickedFirst();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
LRESULT CDlgApartmentDiagram::OnKickIdle(WPARAM, LPARAM)
{
	updateCommandBar();

	return 0;
}

void CDlgApartmentDiagram::updateCommandBar()
{
	if ( GetCommandBars() ) 
		GetCommandBars()->UpdateCommandBars();
}

void CDlgApartmentDiagram::RepositionControls(void)
{
	if (m_bInRepositionControls || !m_bInitDone)
		return;

	CRect rcClientStart;
	CRect rcClientNow;
	GetClientRect(rcClientStart);

	if ((GetStyle() & WS_MINIMIZE) || (rcClientStart.IsRectEmpty()))
		return;

	m_bInRepositionControls = TRUE;

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0, reposQuery, rcClientNow);

	CRect rcBorders(rcClientNow.left - rcClientStart.left, rcClientNow.top - rcClientStart.top,  rcClientStart.right - rcClientNow.right, 
		rcClientStart.bottom - rcClientNow.bottom);

	if (rcBorders != m_rcBorders)
	{

		CPoint ptOffset(rcBorders.left - m_rcBorders.left, rcBorders.top - m_rcBorders.top);
		CSize szOffset(rcBorders.left + rcBorders.right - m_rcBorders.left - m_rcBorders.right,
			rcBorders.top + rcBorders.bottom - m_rcBorders.top - m_rcBorders.bottom);

		CRect rcWindow;
		GetWindowRect(rcWindow);
		rcWindow.BottomRight() += szOffset;

		Offset(ptOffset);
		m_szWindow += szOffset;
		m_szMin += szOffset;

		MoveWindow(rcWindow, TRUE);
	}

	m_rcBorders = rcBorders;

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	m_bInRepositionControls = FALSE;
}

void CDlgApartmentDiagram::OnSize(UINT nType, int cx, int cy)
{
	CXTPDialogBase<CXTPResizeDialog>::OnSize(nType, cx, cy);

	// 调整工具栏
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
}

void CDlgApartmentDiagram::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CXTPDialogBase<CXTPResizeDialog>::OnPaint()
	// 绘制背景
	CWnd *pWnd = GetDlgItem( IDC_DIAGRAM );
	CDC *pDC = pWnd->GetDC();
	CDC memDC;
	CBitmap memBitmap;
	memDC.CreateCompatibleDC( NULL );
	CRect rcContainer, rcDraw;
	pWnd->GetWindowRect( &rcContainer );
	pWnd->ScreenToClient( &rcContainer );
	int iDrawWidth = rcContainer.Width();
	int iDrawHeight = rcContainer.Height();
	memBitmap.CreateCompatibleBitmap( pDC, iDrawWidth, iDrawHeight );
	CBitmap *pOldBitmap = memDC.SelectObject( &memBitmap );
	memDC.FillSolidRect( 0, 0, iDrawWidth, iDrawHeight, RGB(128,128,128) );

	if( !m_imgDiagram.IsNull() )
	{
		//设置模式，可以避免失真，这点很重要
		SetStretchBltMode(memDC.m_hDC, STRETCH_HALFTONE);	
		float fDrawRate = (float)iDrawWidth / (float)iDrawHeight;
		float fImageRate = (float)m_imgDiagram.GetWidth() / (float)m_imgDiagram.GetHeight();
		int iOffset;
		if( fImageRate > fDrawRate )
		{	//高度进行缩放
			rcDraw.left = rcContainer.left;
			rcDraw.right = rcContainer.right;
			iOffset = (iDrawHeight - (int)(iDrawWidth / fImageRate)) / 2;
			rcDraw.top = rcContainer.top + iOffset;
			rcDraw.bottom = rcContainer.bottom - iOffset;
			m_imgDiagram.Draw( memDC.m_hDC, 0, iOffset , rcDraw.Width(), rcDraw.Height());
		}
		else
		{	//宽度进行缩放
			rcDraw.top = rcContainer.top;
			rcDraw.bottom = rcContainer.bottom;
			iOffset = (iDrawWidth - (int)(iDrawHeight * fImageRate)) / 2;
			rcDraw.left = rcContainer.left + iOffset;
			rcDraw.right = rcContainer.right - iOffset;
			m_imgDiagram.Draw( memDC.m_hDC, iOffset, 0, rcDraw.Width(), rcDraw.Height());
		}
	}
	pDC->BitBlt( rcContainer.left, rcContainer.top, iDrawWidth, iDrawHeight, 
		&memDC, 0, 0, SRCCOPY );

	memBitmap.DeleteObject();
	memDC.DeleteDC();
}

void CDlgApartmentDiagram::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DestroyWindow();
	// 用于销毁对象
	std::auto_ptr<CDlgApartmentDiagram> pDlg( s_pInstance );
}

void CDlgApartmentDiagram::SetControlStyle()
{
	SetResize(IDC_DIAGRAM, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);
}

void CDlgApartmentDiagram::OnBnClickedFirst()
{
	CApartmentDiagramMgr::Instance().first();
	loadDiagram();
	this->Invalidate(TRUE);
}

void CDlgApartmentDiagram::OnUpdateFirst(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CDlgApartmentDiagram::OnBnClickedNext()
{
	CApartmentDiagramMgr::Instance().next();
	loadDiagram();
	this->Invalidate(TRUE);
}

void CDlgApartmentDiagram::OnUpdateNext(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CDlgApartmentDiagram::OnBnClickedPrev()
{
	CApartmentDiagramMgr::Instance().prev();
	loadDiagram();
	this->Invalidate(TRUE);
}

void CDlgApartmentDiagram::OnUpdatePrev(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CDlgApartmentDiagram::OnBnClickedLast()
{
	CApartmentDiagramMgr::Instance().last();
	loadDiagram();
	this->Invalidate(TRUE);
}

void CDlgApartmentDiagram::OnUpdateLast(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CDlgApartmentDiagram::OnBnClickedAdd()
{
	CFileDialog fileDlg(TRUE, "", NULL, 
		OFN_ALLOWMULTISELECT | OFN_ENABLESIZING | OFN_HIDEREADONLY, 
		"JPG文件(*.jpg)|*.jpg|BMP文件(*.bmp)|*.bmp||",
		AfxGetMainWnd());
	// 最多打开50个文件
	fileDlg.m_ofn.nMaxFile = 50 * MAX_PATH;
	fileDlg.m_ofn.lpstrFile = new TCHAR[fileDlg.m_ofn.nMaxFile]; 

	//对内存块清零   
	ZeroMemory(fileDlg.m_ofn.lpstrFile,sizeof(TCHAR) * fileDlg.m_ofn.nMaxFile); 
	std::vector<std::string> vFiles;
	if (fileDlg.DoModal () == IDOK){
		//获取第一个文件的位置
		POSITION filePos;
		filePos = fileDlg.GetStartPosition();
		//std::string fromPath = fileDlg.GetPathName()+"\\";
		//循环读出每个路径并存放在数组中
		while(filePos != NULL){

			//获取文件路径
			std::string pathName = fileDlg.GetNextPathName(filePos).GetBuffer(0);
			//获取文件名 
			//std::string fileName = pathName.substr(pathName.find_last_of('\\')+1, pathName.length());
			vFiles.push_back(pathName);
		}
	}
	if(vFiles.empty()) return;

	// 添加文件
	if(CApartmentDiagramMgr::Instance().add(vFiles)){
		MessageBox("成功添加文件！", "提示", MB_OK);
	}else{
		MessageBox("添加文件失败！", "提示", MB_OK);
	}
	resetDiagramList();
	OnBnClickedLast();
}

void CDlgApartmentDiagram::OnUpdateAdd(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CDlgApartmentDiagram::OnBnClickedDel()
{

	std::string diagram = CApartmentDiagramMgr::Instance().getCurrentDiagramPath();
	if(diagram.empty()){
		MessageBox("当前没有可删除文件", "提示", MB_OK);
		return;
	}

	if(MessageBox("删除文件将不可恢复，确定删除？","警告", MB_YESNO)!=IDYES)
		return;

	if(CApartmentDiagramMgr::Instance().del()){
		MessageBox("成功删除文件！", "提示", MB_OK);
	}else{
		MessageBox("删除文件失败！", "提示", MB_OK);
	}
	resetDiagramList();
	OnBnClickedFirst();
}

void CDlgApartmentDiagram::OnUpdateDel(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CDlgApartmentDiagram::loadDiagram()
{
	std::string diagram = CApartmentDiagramMgr::Instance().getCurrentDiagramPath();
	if(!m_imgDiagram.IsNull()){
		m_imgDiagram.Destroy();
	}
	if(diagram!=""){
		m_imgDiagram.Load(diagram.c_str());
	}
	updateDialogTitle();
}

void CDlgApartmentDiagram::updateDialogTitle()
{
	this->SetWindowText(("户型图 "+CApartmentDiagramMgr::Instance().getCurrentDiagram()).c_str());
}

void CDlgApartmentDiagram::OnBnClickedAll()
{
	int sel = pListBox->GetListCtrl()->GetCurSel();
	CString rString;
	pListBox->GetListCtrl()->GetText(sel, rString);
	CApartmentDiagramMgr::Instance().setCurrentDiagram(rString.GetBuffer(0));
	loadDiagram();
	this->Invalidate(TRUE);
}

void CDlgApartmentDiagram::resetDiagramList()
{
	std::list<std::string> diagrams = CApartmentDiagramMgr::Instance().getCurrentDiagrams();
	pListBox->GetListCtrl()->ResetContent();
	for(std::list<std::string>::iterator itr=diagrams.begin(); itr!=diagrams.end(); itr++){
		pListBox->GetListCtrl()->AddString((*itr).c_str());
	}
}