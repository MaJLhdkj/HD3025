
// UpperCtrlDlg.cpp : ʵ���ļ�
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
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CUpperCtrlDlg �Ի���



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
	ON_BN_CLICKED(IDC_BUTTON1, &CUpperCtrlDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUpperCtrlDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CUpperCtrlDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CUpperCtrlDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CUpperCtrlDlg::OnBnClickedButton5)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CUpperCtrlDlg ��Ϣ�������

BOOL CUpperCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//GetClientRect(DlgRect);
	//��TAB�ؼ������4����ҳ
	m_TabCtrl.InsertItem(0,"�������",0);
	m_TabCtrl.InsertItem(1,"Һ�����",1);
	m_TabCtrl.InsertItem(2,"��������",2);
	m_TabCtrl.InsertItem(3,"����У��",3);
	m_TabCtrl.InsertItem(4,"���ݲ�ѯ",4);
	//���tab�ؼ����ڴ�С
	m_TabCtrl.GetClientRect(TabCtrlRect);
	//��tab�ϴ���5���ӶԻ���
	m_SolidDlg.Create(IDD_DLG_SOLID,&m_TabCtrl);
	m_LiquidDlg.Create(IDD_DLG_LIQUID,&m_TabCtrl);
	m_ParaSetDlg.Create(IDD_DLG_PARASET,&m_TabCtrl);
	m_CheckDlg.Create(IDD_DLG_CHECK,&m_TabCtrl);
	m_DataQueryDlg.Create(IDD_DLG_DATAQUERY,&m_TabCtrl);
	//�ӶԻ�����tab����
	m_SolidDlg.MoveWindow(TabCtrlRect);
	m_LiquidDlg.MoveWindow(TabCtrlRect);
	m_ParaSetDlg.MoveWindow(TabCtrlRect);
	m_CheckDlg.MoveWindow(TabCtrlRect);
	m_DataQueryDlg.MoveWindow(TabCtrlRect);
	//
	m_SolidDlg.ShowWindow(SW_SHOW);
	//���ð�ť����
	m_DlgFont.CreatePointFont(120,"΢���ź�");
	//m_DlgFont1.CreatePointFont(100,"΢���ź�");
	for (int i=0;i<5;i++)
	{
		GetDlgItem(IDC_BUTTON1+i)->SetFont(&m_DlgFont);
	}
	m_DlgFont.Detach();
	m_DlgFont.CreatePointFont(100,"΢���ź�");
	//������ʾʱ�侲̬�ı�����
	GetDlgItem(IDC_STC_TIMER)->SetFont(&m_DlgFont);
	m_DlgFont.Detach();
	CTime time;
	time=CTime::GetCurrentTime();
	CString str1=time.Format("%Y��%m��%d��");
	CString str2=time.Format("%H��%M��%S��");
	GetDlgItem(IDC_STC_TIMER)->SetWindowText(str1+"\n"+str2);
	//����һ����ʱ����ʾʱ��
	SetTimer(2014,1000,NULL);
	//��ʼ������ʱ����3��С��ť���ɼ�
	for (int i=0;i<3;i++)
	{
		(CButton*)GetDlgItem(IDC_BUTTON6+i)->ShowWindow(SW_HIDE);
	}
	//����״̬��
	m_StausBar.Create(this);
	const UINT nIDS[4]={2016,2017,2018,2019};
	m_StausBar.SetIndicators(nIDS,4);
	m_StausBar.SetPaneInfo(0,nIDS[0],SBPS_NORMAL,200);
	m_StausBar.SetPaneInfo(1,nIDS[1],SBPS_NORMAL,200);
	m_StausBar.SetPaneInfo(2,nIDS[2],SBPS_NORMAL,200);
	m_StausBar.SetPaneInfo(3,nIDS[3],SBPS_NORMAL,200);
	//m_StausBar.SetPaneText(0,"Զ�̿���״̬��");
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CUpperCtrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); 
		CRect rect;
		GetClientRect(rect);
		CFont myFont,*OldFont;
		LOGFONT font;
		memset(&font,0,sizeof(LOGFONT));
		font.lfHeight=rect.Height()*0.06;
		font.lfWidth=rect.Width()*0.02;
		strcpy(font.lfFaceName,"����");
		myFont.CreateFontIndirect(&font);
		OldFont=dc.SelectObject(&myFont);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(0,38,142));
		dc.TextOut(rect.Width()*0.3,rect.Height()*0.03,"HD3025��λ������ϵͳ");
		dc.SelectObject(OldFont);
		UpdateWindow();
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CUpperCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUpperCtrlDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (nType==SIZE_MAXIMIZED || nType==SIZE_RESTORED)
	{
		CSizeAdjust SizeAdj;
		SizeAdj.OnSizeAdjust(DlgRect,this,cx,cy);
	}
}


void CUpperCtrlDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int x=::GetSystemMetrics(SM_CXSCREEN)*0.5;
	int y=::GetSystemMetrics(SM_CYSCREEN)*0.5;
	//����һ����С����
	lpMMI->ptMinTrackSize.x=x;
	lpMMI->ptMinTrackSize.y=y;
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


void CUpperCtrlDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_SolidDlg.ShowWindow(SW_SHOW);
	m_LiquidDlg.ShowWindow(SW_HIDE);
	m_ParaSetDlg.ShowWindow(SW_HIDE);
	m_CheckDlg.ShowWindow(SW_HIDE);
	m_DataQueryDlg.ShowWindow(SW_HIDE);
	//����3��С��ť���ɼ�
	for (int i=0;i<3;i++)
	{
		(CButton*)GetDlgItem(IDC_BUTTON6+i)->ShowWindow(SW_HIDE);
	}
	//
}


void CUpperCtrlDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_SolidDlg.ShowWindow(SW_HIDE);
	m_LiquidDlg.ShowWindow(SW_SHOW);
	m_ParaSetDlg.ShowWindow(SW_HIDE);
	m_CheckDlg.ShowWindow(SW_HIDE);
	m_DataQueryDlg.ShowWindow(SW_HIDE);
	//����3��С��ť���ɼ�
	for (int i=0;i<3;i++)
	{
		(CButton*)GetDlgItem(IDC_BUTTON6+i)->ShowWindow(SW_HIDE);
	}
}


void CUpperCtrlDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_SolidDlg.ShowWindow(SW_HIDE);
	m_LiquidDlg.ShowWindow(SW_HIDE);
	m_ParaSetDlg.ShowWindow(SW_SHOW);
	m_CheckDlg.ShowWindow(SW_HIDE);
	m_DataQueryDlg.ShowWindow(SW_HIDE);
	//����3��С��ť���ɼ�
	for (int i=0;i<3;i++)
	{
		(CButton*)GetDlgItem(IDC_BUTTON6+i)->ShowWindow(SW_HIDE);
	}
}


void CUpperCtrlDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_SolidDlg.ShowWindow(SW_HIDE);
	m_LiquidDlg.ShowWindow(SW_HIDE);
	m_ParaSetDlg.ShowWindow(SW_HIDE);
	m_CheckDlg.ShowWindow(SW_SHOW);
	m_DataQueryDlg.ShowWindow(SW_HIDE);
	//����3��С��ť���ɼ�
	for (int i=0;i<3;i++)
	{
		(CButton*)GetDlgItem(IDC_BUTTON6+i)->ShowWindow(SW_HIDE);
	}
}


void CUpperCtrlDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_SolidDlg.ShowWindow(SW_HIDE);
	m_LiquidDlg.ShowWindow(SW_HIDE);
	m_ParaSetDlg.ShowWindow(SW_HIDE);
	m_CheckDlg.ShowWindow(SW_HIDE);
	m_DataQueryDlg.ShowWindow(SW_SHOW);
	//����3��С��ť���ɼ�
	for (int i=0;i<3;i++)
	{
		(CButton*)GetDlgItem(IDC_BUTTON6+i)->ShowWindow(SW_SHOW);
	}
}


void CUpperCtrlDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nIDEvent==2014)
	{
		CTime time;
		time=CTime::GetCurrentTime();
		CString str1=time.Format("%Y��%m��%d��");
		CString str2=time.Format("%H��%M��%S��");
		GetDlgItem(IDC_STC_TIMER)->SetWindowText(str1+"\n"+str2);
	}
	CDialogEx::OnTimer(nIDEvent);
}
