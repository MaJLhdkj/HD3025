
// UpperCtrlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UpperCtrl.h"
#include "UpperCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CRect DlgRect;
extern CRect TabCtrlRect;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CUpperCtrlDlg 对话框



CUpperCtrlDlg::CUpperCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUpperCtrlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUpperCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
}

BEGIN_MESSAGE_MAP(CUpperCtrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_DLG1, &CUpperCtrlDlg::OnBnClickedBtnDlg1)
	ON_BN_CLICKED(IDC_BTN_DLG5, &CUpperCtrlDlg::OnBnClickedBtnDlg5)
END_MESSAGE_MAP()


// CUpperCtrlDlg 消息处理程序

BOOL CUpperCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetClientRect(DlgRect);
	//向TAB控件中添加4个分页
	m_TabCtrl.InsertItem(0,"固体测量",0);
	m_TabCtrl.InsertItem(1,"液体测量",1);
	m_TabCtrl.InsertItem(2,"参数设置",2);
	m_TabCtrl.InsertItem(3,"仪器校验",3);
	m_TabCtrl.InsertItem(4,"数据查询",4);
	//获得tab控件窗口大小
	m_TabCtrl.GetClientRect(TabCtrlRect);
	//在tab上创建5个子对话框
	m_SolidDlg.Create(IDD_DLG_SOLID,&m_TabCtrl);
	m_LiquidDlg.Create(IDD_DLG_LIQUID,&m_TabCtrl);
	m_ParaSetDlg.Create(IDD_DLG_PARASET,&m_TabCtrl);
	m_CheckDlg.Create(IDD_DLG_CHECK,&m_TabCtrl);
	m_DataQueryDlg.Create(IDD_DLG_DATAQUERY,&m_TabCtrl);
	//子对话框与tab对齐
	m_SolidDlg.MoveWindow(TabCtrlRect);
	m_LiquidDlg.MoveWindow(TabCtrlRect);
	m_ParaSetDlg.MoveWindow(TabCtrlRect);
	m_CheckDlg.MoveWindow(TabCtrlRect);
	m_DataQueryDlg.MoveWindow(TabCtrlRect);
	//将参数设置界面设为默认界面
	m_ParaSetDlg.ShowWindow(SW_SHOW);
	//设置按钮字体
	m_DlgFont.CreatePointFont(120,"微软雅黑");
	//m_DlgFont1.CreatePointFont(100,"微软雅黑");
	for (int i=0;i<5;i++)
	{
		GetDlgItem(IDC_BTN_DLG1+i)->SetFont(&m_DlgFont);
	}
	m_DlgFont.Detach();
	m_DlgFont.CreatePointFont(100,"微软雅黑");
	//设置显示时间静态文本字体
	GetDlgItem(IDC_STC_TIMER)->SetFont(&m_DlgFont);
	m_DlgFont.Detach();
	CTime time;
	time=CTime::GetCurrentTime();
	CString str1=time.Format("%Y年%m月%d日");
	CString str2=time.Format("%H点%M分%S秒");
	GetDlgItem(IDC_STC_TIMER)->SetWindowText(str1+"\n"+str2);
	//设置一个定时器显示时间
	SetTimer(2014,1000,NULL);
	//初始化窗口时设置3个小按钮不可见
	for (int i=0;i<3;i++)
	{
		(CButton*)GetDlgItem(IDC_BTN_DLG6+i)->ShowWindow(SW_HIDE);
	}
	//创建状态栏
	m_StausBar.Create(this);
	const UINT nIDS[3]={2016,2017,2018};
	m_StausBar.SetIndicators(nIDS,3);
	m_StausBar.SetPaneInfo(0,nIDS[0],SBPS_NORMAL,100);
	m_StausBar.SetPaneInfo(1,nIDS[1],SBPS_NORMAL,200);
	m_StausBar.SetPaneInfo(2,nIDS[2],SBPS_NORMAL,200);
//	m_StausBar.SetPaneInfo(3,nIDS[3],SBPS_NORMAL,200);
	m_StausBar.SetPaneText(0,"当前状态：");
	m_StausBar.SetPaneText(1,"远程控制未连接");
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
	//检测软件是否第一次使用，不是的话读取配置数据，否则将第一次标志置0
	char str[128]={0};
	::GetPrivateProfileString("Flag",
		"FirstStatus",
		NULL,
		str,
		10,
		".\\Init.ini");
	if (str[0]=='0')
	{
		TRACE("读取配置数据\r\n");
	}
	else
	{
		::WritePrivateProfileString("Flag",
			"FirstStatus",
			"0",
			".\\Init.ini");
		::WritePrivateProfileString("Data",
			"DataNumber",
			"000000",
			".\\Init.ini");
		TRACE("软件第一次使用\r\n");
	}
	//



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUpperCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUpperCtrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
// 		CPaintDC dc(this); 
// 		CRect rect;
// 		GetClientRect(rect);
// 		CFont myFont,*OldFont;
// 		LOGFONT font;
// 		memset(&font,0,sizeof(LOGFONT));
// 		font.lfHeight=rect.Height()*0.06;
// 		font.lfWidth=rect.Width()*0.02;
// 		strcpy(font.lfFaceName,"黑体");
// 		myFont.CreateFontIndirect(&font);
// 		OldFont=dc.SelectObject(&myFont);
// 		dc.SetBkMode(TRANSPARENT);
// 		dc.SetTextColor(RGB(0,38,142));
// 		dc.TextOut(rect.Width()*0.3,rect.Height()*0.03,"HD3025上位机控制系统");
// 		dc.SelectObject(OldFont);
// 		//UpdateWindow();
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CUpperCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUpperCtrlDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (nType==SIZE_MAXIMIZED || nType==SIZE_RESTORED)
	{
		CSizeAdjust SizeAdj;
		SizeAdj.OnSizeAdjust(DlgRect,this,cx,cy);
	}
}


void CUpperCtrlDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int x=::GetSystemMetrics(SM_CXSCREEN)*0.5;
	int y=::GetSystemMetrics(SM_CYSCREEN)*0.5;
	//限制一下最小窗口
	lpMMI->ptMinTrackSize.x=x;
	lpMMI->ptMinTrackSize.y=y;
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}
void CUpperCtrlDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent==2014)
	{
		CTime time;
		time=CTime::GetCurrentTime();
		CString str1=time.Format("%Y年%m月%d日");
		CString str2=time.Format("%H点%M分%S秒");
		GetDlgItem(IDC_STC_TIMER)->SetWindowText(str1+"\n"+str2);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CUpperCtrlDlg::OnBnClickedBtnDlg1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_SolidDlg.ShowWindow(SW_HIDE);
	m_LiquidDlg.ShowWindow(SW_HIDE);
	m_ParaSetDlg.ShowWindow(SW_SHOW);
	m_CheckDlg.ShowWindow(SW_HIDE);
	m_DataQueryDlg.ShowWindow(SW_HIDE);
	//设置3个小按钮不可见
	for (int i=0;i<3;i++)
	{
		(CButton*)GetDlgItem(IDC_BTN_DLG6+i)->ShowWindow(SW_HIDE);
	}
}


void CUpperCtrlDlg::OnBnClickedBtnDlg5()
{
	// TODO: 在此添加控件通知处理程序代码
	m_SolidDlg.ShowWindow(SW_HIDE);
	m_LiquidDlg.ShowWindow(SW_HIDE);
	m_ParaSetDlg.ShowWindow(SW_HIDE);
	m_CheckDlg.ShowWindow(SW_HIDE);
	m_DataQueryDlg.ShowWindow(SW_SHOW);
	//设置3个小按钮不可见
	for (int i=0;i<3;i++)
	{
		(CButton*)GetDlgItem(IDC_BTN_DLG6+i)->ShowWindow(SW_SHOW);
	}
}
