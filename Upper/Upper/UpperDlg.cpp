
// UpperDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Upper.h"
#include "UpperDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//存储对话框的大小
CRect DlgRect;
extern CRect TabRect;
extern CRect OutlookListRect;
//4个全局对话框变量，
CMeasureDlg MeasureDlg;
CParaSetDlg ParaDlg;
CSolidDlg SolidDlg;
CLiquidDlg LiquidDlg;
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


// CUpperDlg 对话框



CUpperDlg::CUpperDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUpperDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUpperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}

BEGIN_MESSAGE_MAP(CUpperDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CUpperDlg 消息处理程序

BOOL CUpperDlg::OnInitDialog()
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
	//列表框双击事件
	m_List.pItemDlbFun=OnItemDouble;
	//获得对话框大小
	GetClientRect(DlgRect);
	//创建图像列表
	m_Imagelist.Create(32,32,ILC_COLOR24|ILC_MASK,0,1);
	//载入4个ico图标
	for (int i=0;i<4;i++)
	{
		m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON1+i));
	}
	//向列表视图控件中添加按钮
	m_List.SetImageLists(&m_Imagelist);
	m_List.AddButton("样品测量",500);
	m_List.AddButton("仪器校验",501);
	m_List.AddButton("参数设置",502);
	//像列表控件中添加选项
	CString str;
	str="固体测量";
	m_List.AddButtonItems(0,str);
	str="液体测量";
	m_List.AddButtonItems(0,str);
	str="仪器校验";
	m_List.AddButtonItems(1,str);
	str="参数设置";
	m_List.AddButtonItems(2,str);
	//像TAB控件中添加4个分页
	m_Tab.InsertItem(0,"仪器校验",0);
	m_Tab.InsertItem(1,"参数设置",1);
	m_Tab.InsertItem(2,"固体测量",2);
	m_Tab.InsertItem(3,"液体测量",3);
	//创建4个对话框子窗口放在tab控件上
	MeasureDlg.Create(IDD_DLG_MEASURE,&m_Tab);
	ParaDlg.Create(IDD_DLG_PARASET,&m_Tab);
	SolidDlg.Create(IDD_DLG_SOLID,&m_Tab);
	LiquidDlg.Create(IDD_DLG_LIQUID,&m_Tab);
	//获得tab控件窗口大小
	m_Tab.GetClientRect(TabRect);
	//将4个子对话框与tab控件对齐
	MeasureDlg.MoveWindow(TabRect);
	ParaDlg.MoveWindow(TabRect);
	SolidDlg.MoveWindow(TabRect);
	LiquidDlg.MoveWindow(TabRect);
	//设置固体测量对话框显示
	SolidDlg.ShowWindow(SW_SHOW);
	//获得ListControl的窗口大小
	m_List.GetClientRect(OutlookListRect);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUpperDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUpperDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CUpperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CUpperDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (nType==SIZE_MAXIMIZED || 
		nType==SIZE_RESTORED
		)
	{
		CSizeAdjust SizeAdj;
		SizeAdj.OnSizeAdjust(DlgRect,this,cx,cy);
	}
}


void CUpperDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	lpMMI->ptMinTrackSize.x=800;
	lpMMI->ptMinTrackSize.y=600;
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


void CUpperDlg::OnItemDouble(const CListCtrl* pListCtrl, int nIndex)
{
	if (pListCtrl)
	{
		if (nIndex!=-1)
		{
			CString str=pListCtrl->GetItemText(nIndex,0);
			if (str=="固体测量")
			{
				SolidDlg.ShowWindow(SW_SHOW);
				LiquidDlg.ShowWindow(SW_HIDE);
				MeasureDlg.ShowWindow(SW_HIDE);
				ParaDlg.ShowWindow(SW_HIDE);
			} 
			else if (str=="液体测量")
			{
				SolidDlg.ShowWindow(SW_HIDE);
				LiquidDlg.ShowWindow(SW_SHOW);
				MeasureDlg.ShowWindow(SW_HIDE);
				ParaDlg.ShowWindow(SW_HIDE);
			}
			else if (str=="仪器校验")
			{
				SolidDlg.ShowWindow(SW_HIDE);
				LiquidDlg.ShowWindow(SW_HIDE);
				MeasureDlg.ShowWindow(SW_SHOW);
				ParaDlg.ShowWindow(SW_HIDE);
			}
			else if (str=="参数设置")
			{
				SolidDlg.ShowWindow(SW_HIDE);
				LiquidDlg.ShowWindow(SW_HIDE);
				MeasureDlg.ShowWindow(SW_HIDE);
				ParaDlg.ShowWindow(SW_SHOW);
			}
		}
	}
}
