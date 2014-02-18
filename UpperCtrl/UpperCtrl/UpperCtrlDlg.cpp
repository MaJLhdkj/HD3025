
// UpperCtrlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UpperCtrl.h"
#include "UpperCtrlDlg.h"
#include "afxdialogex.h"
#include "intrface.h"
#include <Dbt.h>
#include "UserMsg.h"
#include "usbdriver.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HANDLE m_cFD3025Device=INVALID_HANDLE_VALUE;		//设备的句柄
GUID m_cUsbGuid=GUID_DEVINTERFACE_HD3025;		//打开设备的GUID
const Uint8 UsbCmdFill[8]  = {0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00};
DWORD dwDisControlTimes=0;//超时次数
DWORD dwTimes24=0;
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
	char CurrentPath[260];
	memset(CurrentPath,0,260);
	GetCurrentDirectory(260,CurrentPath);
	m_DefaultPath = CurrentPath;
	TRACE("m_DefaultPath is %s\r\n",CurrentPath);
	m_strPath = _T("");
}

void CUpperCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
	DDX_Control(pDX, IDC_DLG_PROGRESS1, m_Progress);
	//  DDX_Control(pDX, IDC_BTN_DLG1, m_Btn1);
	DDX_Control(pDX, IDC_BTN_DLG1, m_Btn_Dlg1);
	DDX_Control(pDX, IDC_BTN_DLG2, m_Btn_Dlg2);
	DDX_Control(pDX, IDC_BTN_DLG3, m_Btn_Dlg3);
	DDX_Control(pDX, IDC_BTN_DLG4, m_Btn_Dlg4);
	DDX_Control(pDX, IDC_BTN_DLG5, m_Btn_Dlg5);
	DDX_Control(pDX, IDC_BTN_DLG6, m_Btn_Dlg6);
	//  DDX_Control(pDX, IDC_BTN_DLG7, m);
	DDX_Control(pDX, IDC_BTN_DLG7, m_Btn_Dlg7);
	DDX_Control(pDX, IDC_BTN_DLG8, m_Btn_Dlg8);
	DDX_Control(pDX, IDC_BTN_DLG9, m_Btn_Dlg9);
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
	ON_MESSAGE(WM_SOLIDSHOW, &CUpperCtrlDlg::OnSolidshow)
	ON_MESSAGE(WM_LIQUIDSHOW, &CUpperCtrlDlg::OnLiquidshow)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_DLG9, &CUpperCtrlDlg::OnBnClickedBtnDlg9)
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

	//初始化窗口时设置4个小按钮不可见
	for (int i=0;i<4;i++)
	{
		(CButton*)GetDlgItem(IDC_BTN_DLG6+i)->ShowWindow(SW_HIDE);
	}
	//
	m_Btn_Dlg1.SetIcon(LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON1)));
	m_Btn_Dlg2.SetIcon(LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON2)));
	m_Btn_Dlg3.SetIcon(LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON3)));
	m_Btn_Dlg4.SetIcon(LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)));
	m_Btn_Dlg5.SetIcon(LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON4)));
	m_Btn_Dlg6.SetIcon(LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON5)));
	m_Btn_Dlg7.SetIcon(LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON6)));
	m_Btn_Dlg8.SetIcon(LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON7)));
	m_Btn_Dlg9.SetIcon(LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON12)));
	//创建状态栏
	m_StausBar.Create(this);
	const UINT nIDS[4]={2016,2017,2018,2019};
	m_StausBar.SetIndicators(nIDS,4);
	m_StausBar.SetPaneInfo(0,nIDS[0],SBPS_NORMAL,DlgRect.Width()*0.1);
	m_StausBar.SetPaneInfo(1,nIDS[1],SBPS_NORMAL,DlgRect.Width()*0.1);
	m_StausBar.SetPaneInfo(2,nIDS[2],SBPS_NORMAL,DlgRect.Width()*0.6);
	m_StausBar.SetPaneInfo(3,nIDS[3],SBPS_NORMAL,DlgRect.Width()*0.2);
	m_StausBar.SetPaneText(0,"当前状态：");
	m_StausBar.SetPaneText(1,"远程控制未连接");
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
	//
	CTime time;
	time=CTime::GetCurrentTime();
	CString str=time.Format("%Y-%m-%d-%H:%M:%S");
	m_StausBar.SetPaneText(3,str);
	//设置一个定时器显示时间
	SetTimer(2014,1000,NULL);//ID=2014
	//初始化进度条，并将其父窗口设为状态栏
	m_Progress.SetRange(0,256);
	m_Progress.SetPos(100);
	m_Progress.SetParent(&m_StausBar);
	CRect StatusRect;
	m_StausBar.GetItemRect(2,StatusRect);
	m_Progress.MoveWindow(StatusRect);
	m_Progress.ShowWindow(SW_SHOW);
	//注册设备
	RegisterDevice();
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
		if (IsWindow(m_StausBar.m_hWnd))
		{
			const UINT nIDS[4]={2016,2017,2018,2019};
			m_StausBar.SetPaneInfo(0,nIDS[0],SBPS_NORMAL,cx*0.1);
			m_StausBar.SetPaneInfo(1,nIDS[1],SBPS_NORMAL,cx*0.1);
			m_StausBar.SetPaneInfo(2,nIDS[2],SBPS_NORMAL,cx*0.6);
			m_StausBar.SetPaneInfo(3,nIDS[1],SBPS_NORMAL,cx*0.2);
			CRect rect;
			m_StausBar.GetItemRect(2,rect);
			m_Progress.MoveWindow(rect);
		}
		//RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
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
		CString str=time.Format("%Y-%m-%d-%H:%M:%S");
		m_StausBar.SetPaneText(3,str);
	}
	else if (nIDEvent==3002)//待机超时检查定时到
	{
		Uint8 uResult=WriteParameters(USB_STANDARDBY_CMD);
		if (uResult==USB_IN_CONTROL)
		{
			TRACE("待机通信正常!\r\n");
			return;
		}
		else
		{
			TRACE("下位机未开启远程模式!\r\n");
			dwDisControlTimes++;
			TRACE("dwDisControlTimes=%d\r\n",dwDisControlTimes);
			if (dwDisControlTimes>=10)
			{
				MessageBox("远程控制失败！请回到参数设置界面重新连接，并检查USB！");
				dwDisControlTimes=0;
				KillTimer(3002);
				return;
			}
		}
	}
	else if(nIDEvent==3003)//24s检查
	{
		dwTimes24++;
		TRACE("dwTimes24=%d\r\n",dwTimes24);
		if (dwTimes24>=24)
		{

		}
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
	for (int i=0;i<4;i++)
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
	//设置3个小按钮可见
	for (int i=0;i<3;i++)
	{
		(CButton*)GetDlgItem(IDC_BTN_DLG6+i)->ShowWindow(SW_SHOW);
	}
	(CButton*)GetDlgItem(IDC_BTN_DLG9)->ShowWindow(SW_HIDE);
}

afx_msg LRESULT CUpperCtrlDlg::OnSolidshow(WPARAM wParam, LPARAM lParam)
{
	m_SolidDlg.ShowWindow(SW_SHOW);
	m_LiquidDlg.ShowWindow(SW_HIDE);
	m_ParaSetDlg.ShowWindow(SW_HIDE);
	m_CheckDlg.ShowWindow(SW_HIDE);
	m_DataQueryDlg.ShowWindow(SW_HIDE);
	(CButton*)GetDlgItem(IDC_BTN_DLG9)->ShowWindow(SW_SHOW);
	return 0;
}


afx_msg LRESULT CUpperCtrlDlg::OnLiquidshow(WPARAM wParam, LPARAM lParam)
{
	m_SolidDlg.ShowWindow(SW_HIDE);
	m_LiquidDlg.ShowWindow(SW_SHOW);
	m_ParaSetDlg.ShowWindow(SW_HIDE);
	m_CheckDlg.ShowWindow(SW_HIDE);
	m_DataQueryDlg.ShowWindow(SW_HIDE);
	(CButton*)GetDlgItem(IDC_BTN_DLG9)->ShowWindow(SW_SHOW);
	return 0;
}


void CUpperCtrlDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	//避免ESC键
	//CDialogEx::OnCancel();
}


void CUpperCtrlDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//代替OnClose，直接退出进程，不经过各种消息处理
	::ExitProcess(0);
	//CDialogEx::OnClose();
}
//
const GUID GUID_DEVINTERFACE_LIST[] = { 
	{ 0xA5DCBF10, 0x6530, 0x11D2, { 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED } },
	{ 0x53f56307, 0xb6bf, 0x11d0, { 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b } },
	{ 0x4D1E55B2, 0xF16F, 0x11CF, { 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 } },
	{ 0xad498944, 0x762f, 0x11d0, { 0x8d, 0xcb, 0x00, 0xc0, 0x4f, 0xc3, 0x35, 0x8c } },
	{ 0x36fc9e60, 0xc465, 0x11fc, { 0x80, 0x56, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 } },	//Jlink
	{ 0x48A91D4C, 0x756A, 0x4EAC, { 0x8A, 0xDC, 0x5A, 0x34, 0x04, 0xA4, 0x1E, 0x59 } },	//HD3025
};
BOOL CUpperCtrlDlg::RegisterDevice(void)
{
	TRACE("开始注册设备...\r\n");
	HDEVNOTIFY hDevNotify = NULL;     
	DEV_BROADCAST_DEVICEINTERFACE NotificationFilter;
	TRACE("清空DEV_BROADCAST_DEVICEINTERFACE结构...\r\n");
	ZeroMemory( &NotificationFilter, sizeof(NotificationFilter) );     
	NotificationFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);     
	NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;     
	for(int i = 0; i < sizeof(GUID_DEVINTERFACE_LIST) / sizeof(GUID); i++){         
		NotificationFilter.dbcc_classguid = GUID_DEVINTERFACE_LIST[i];         
		hDevNotify = RegisterDeviceNotification(this->GetSafeHwnd(), &NotificationFilter, DEVICE_NOTIFY_WINDOW_HANDLE);         
		if(!hDevNotify ){             
			AfxMessageBox(CString("设备不能注册: ")                  
				+ _com_error(GetLastError()).ErrorMessage(), MB_ICONEXCLAMATION);             
			return FALSE;         
		}     
	}    
	TRACE("设备注册成功...\r\n");
	return TRUE;  
}


BOOL CUpperCtrlDlg::CloseHD3025Device(void)
{
	UINT Instance=0;	//需要打开的设备实例，0表示第一个设备，1表示第二个设备，依次类推
	if (m_cFD3025Device == INVALID_HANDLE_VALUE)//设备未打开
	{
		return TRUE;
	}
	else //设备打开
	{
		m_cFD3025Device = INVALID_HANDLE_VALUE;
		return CloseUSBDevice(m_cFD3025Device);
	}
}

//const Uint8 UsbCmdFill[8]  = {0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00};
Uint8 CUpperCtrlDlg::ConnectHD3025(HSProtocal *HsP)
{
	DWORD dwReturned;
	if (OpenHD3025Device())
	{
		TRACE("OpenHD3025Device 成功...\r\n");
		HSProtocal Protocal[1];
		memset(&Protocal[0],0,sizeof(HSProtocal));//清0
		Protocal[0].Cmd=USB_LINK_CMD;
		Protocal[0].CmdPar[0]=0xaa;
		Protocal[0].CmdPar[1]=0xbb;
		Protocal[0].CmdPar[2]=0xcc;
		Protocal[0].CmdPar[3]=0xdd;
		Protocal[0].CmdPar[4]=0xee;
		Protocal[0].CmdPar[5]=0xff;
		Protocal[0].CmdPar[6]=0x00;
		if (WriteDataCode(m_cFD3025Device,EP2_WRITE,&Protocal[0],sizeof(HSProtocal),NULL,0,&dwReturned,NULL))
		{
			if (ReadDataCode(m_cFD3025Device,EP2_READ,NULL,0,HsP,sizeof(HSProtocal),&dwReturned,NULL))
			{
				//如果CmdPar都按位取反的化，
				if ((*HsP).CmdPar[0]==0xbb)
				{
						return USB_IN_CONTROL;
				}
				return USB_IN_CONNECT;
			}
			return USB_IN_CONNECT;
		}
	}
	return ERROR;
}


BOOL CUpperCtrlDlg::OpenHD3025Device(void)
{
	DWORD	Error;
	UINT Instance=0;	//需要打开的设备实例，0表示第一个设备，1表示第二个设备，依次类推
	if (m_cFD3025Device==INVALID_HANDLE_VALUE)//设备未打开
	{
		m_cFD3025Device=OpenUSBDevice(&m_cUsbGuid,Instance,&Error);
		//说明：
		//m_cUsbGuid：打开设备的句柄 在驱动生成文件中可以找到并保持一致
		//m_cUsbGuid：
		if (m_cFD3025Device==INVALID_HANDLE_VALUE)
		{
			TRACE("OpenUSBDevice 失败...\r\n");
			return FALSE;
		} 
		else
		{
			//MessageBox(_T("恭喜，设备打开成功！"));
			TRACE("OpenUSBDevice 成功...\r\n");
			return TRUE;
		}
	}
	else //设备打开
	{
		TRACE("设备已经打开过...\r\n");
		return TRUE;
	}
}


Uint8 CUpperCtrlDlg::WriteParameters(Uint8 Cmd)
{
	ULONG BytesReturned;
	USBCmd SendCmd;
	USBCmd RcvCmd;
	SendCmd.Cmd = Cmd;
	SendCmd.CmdPar[0] = UsbCmdFill[0];
	SendCmd.CmdPar[1] = UsbCmdFill[1];
	SendCmd.CmdPar[2] = UsbCmdFill[2];
	SendCmd.CmdPar[3] = UsbCmdFill[3];
	SendCmd.CmdPar[4] = UsbCmdFill[4];
	SendCmd.CmdPar[5] = UsbCmdFill[5];
	SendCmd.CmdPar[6] = UsbCmdFill[6];

	//使用IoControl往端点2发送8字节数据
	if (WriteDataCode(m_cFD3025Device,EP2_WRITE,&SendCmd,8,NULL,0,&BytesReturned,NULL))
	{
		if (ReadDataCode(m_cFD3025Device,EP2_READ,NULL,0,&RcvCmd,8,&BytesReturned,NULL))
		{
			if ((RcvCmd.CmdPar[1] | RcvCmd.CmdPar[2]) == 0xaa)
			{
				return USB_IN_CONTROL;
			}
			return USB_IN_CONNECT;
		}
	}
	return ERROR;
}


void CUpperCtrlDlg::OnBnClickedBtnDlg9()
{
	// TODO: 在此添加控件通知处理程序代码
	CTime time;
	time=CTime::GetCurrentTime();
	CString str_FileName=time.Format("%Y-%m-%d-%H-%M-%S");
	CFileDialog filedlg(FALSE,_T(".txt"),str_FileName,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("文本文档(.txt)|*.txt||"),this);
	if (filedlg.DoModal()==IDOK)
	{
		m_strPath=filedlg.GetPathName();
		TRACE("m_strPath is %s\r\n",m_strPath);
		HANDLE hFile=::CreateFile(m_strPath,
			GENERIC_READ|GENERIC_WRITE,
			FILE_SHARE_READ,
			NULL,
			CREATE_NEW,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (hFile==INVALID_HANDLE_VALUE)
		{
			MessageBox("创建文本文档失败");
			TRACE("LastError is 0x%x\r\n",GetLastError());
		}
		::CloseHandle(hFile);
	}
}
