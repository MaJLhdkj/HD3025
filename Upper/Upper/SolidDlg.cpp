// SolidDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Upper.h"
#include "SolidDlg.h"
#include "afxdialogex.h"

//获得固体测量对话框的初始大小
CRect SolidDlgRect;
// CSolidDlg 对话框

IMPLEMENT_DYNAMIC(CSolidDlg, CDialogEx)

CSolidDlg::CSolidDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSolidDlg::IDD, pParent)
{

}

CSolidDlg::~CSolidDlg()
{
}

void CSolidDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSolidDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CSolidDlg 消息处理程序

//////////////////////
void CSolidDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (nType==SIZE_RESTORED)
	{
		CSizeAdjust SizeAdj;
		SizeAdj.OnSizeAdjust(SolidDlgRect,this,cx,cy);
	}
}


BOOL CSolidDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetClientRect(SolidDlgRect);
	//设置字体
	m_SolidFont1.CreatePointFont(250,"黑体");
	m_SolidFont2.CreatePointFont(120,"黑体");
	m_SolidFont3.CreatePointFont(100,"黑体");
	GetDlgItem(IDC_SOLID_STC0)->SetFont(&m_SolidFont1);
	for (int i=0;i<6;i++)
	{
		GetDlgItem(IDC_SOLID_STC2+i)->SetFont(&m_SolidFont2);
	}
	//
	GetDlgItem(IDC_SOLID_STC1)->SetFont(&m_SolidFont3);
	for (int i=0;i<3;i++)
	{
		GetDlgItem(IDC_BUTTON1+i)->SetFont(&m_SolidFont3);
	}
	return TRUE;
}
