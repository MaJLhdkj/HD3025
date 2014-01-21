
// UpperDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Upper.h"
#include "UpperDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//�洢�Ի���Ĵ�С
CRect DlgRect;
extern CRect TabRect;
extern CRect OutlookListRect;
//4��ȫ�ֶԻ��������
CMeasureDlg MeasureDlg;
CParaSetDlg ParaDlg;
CSolidDlg SolidDlg;
CLiquidDlg LiquidDlg;
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


// CUpperDlg �Ի���



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


// CUpperDlg ��Ϣ�������

BOOL CUpperDlg::OnInitDialog()
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
	//�б��˫���¼�
	m_List.pItemDlbFun=OnItemDouble;
	//��öԻ����С
	GetClientRect(DlgRect);
	//����ͼ���б�
	m_Imagelist.Create(32,32,ILC_COLOR24|ILC_MASK,0,1);
	//����4��icoͼ��
	for (int i=0;i<4;i++)
	{
		m_Imagelist.Add(AfxGetApp()->LoadIcon(IDI_ICON1+i));
	}
	//���б���ͼ�ؼ�����Ӱ�ť
	m_List.SetImageLists(&m_Imagelist);
	m_List.AddButton("��Ʒ����",500);
	m_List.AddButton("����У��",501);
	m_List.AddButton("��������",502);
	//���б�ؼ������ѡ��
	CString str;
	str="�������";
	m_List.AddButtonItems(0,str);
	str="Һ�����";
	m_List.AddButtonItems(0,str);
	str="����У��";
	m_List.AddButtonItems(1,str);
	str="��������";
	m_List.AddButtonItems(2,str);
	//��TAB�ؼ������4����ҳ
	m_Tab.InsertItem(0,"����У��",0);
	m_Tab.InsertItem(1,"��������",1);
	m_Tab.InsertItem(2,"�������",2);
	m_Tab.InsertItem(3,"Һ�����",3);
	//����4���Ի����Ӵ��ڷ���tab�ؼ���
	MeasureDlg.Create(IDD_DLG_MEASURE,&m_Tab);
	ParaDlg.Create(IDD_DLG_PARASET,&m_Tab);
	SolidDlg.Create(IDD_DLG_SOLID,&m_Tab);
	LiquidDlg.Create(IDD_DLG_LIQUID,&m_Tab);
	//���tab�ؼ����ڴ�С
	m_Tab.GetClientRect(TabRect);
	//��4���ӶԻ�����tab�ؼ�����
	MeasureDlg.MoveWindow(TabRect);
	ParaDlg.MoveWindow(TabRect);
	SolidDlg.MoveWindow(TabRect);
	LiquidDlg.MoveWindow(TabRect);
	//���ù�������Ի�����ʾ
	SolidDlg.ShowWindow(SW_SHOW);
	//���ListControl�Ĵ��ڴ�С
	m_List.GetClientRect(OutlookListRect);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CUpperDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CUpperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CUpperDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
			if (str=="�������")
			{
				SolidDlg.ShowWindow(SW_SHOW);
				LiquidDlg.ShowWindow(SW_HIDE);
				MeasureDlg.ShowWindow(SW_HIDE);
				ParaDlg.ShowWindow(SW_HIDE);
			} 
			else if (str=="Һ�����")
			{
				SolidDlg.ShowWindow(SW_HIDE);
				LiquidDlg.ShowWindow(SW_SHOW);
				MeasureDlg.ShowWindow(SW_HIDE);
				ParaDlg.ShowWindow(SW_HIDE);
			}
			else if (str=="����У��")
			{
				SolidDlg.ShowWindow(SW_HIDE);
				LiquidDlg.ShowWindow(SW_HIDE);
				MeasureDlg.ShowWindow(SW_SHOW);
				ParaDlg.ShowWindow(SW_HIDE);
			}
			else if (str=="��������")
			{
				SolidDlg.ShowWindow(SW_HIDE);
				LiquidDlg.ShowWindow(SW_HIDE);
				MeasureDlg.ShowWindow(SW_HIDE);
				ParaDlg.ShowWindow(SW_SHOW);
			}
		}
	}
}
