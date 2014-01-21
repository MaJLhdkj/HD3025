// ParaSetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Upper.h"
#include "ParaSetDlg.h"
#include "afxdialogex.h"

//获得参数设置对话框的初始大小
CRect ParaSetDlgRect;
// CParaSetDlg 对话框

IMPLEMENT_DYNAMIC(CParaSetDlg, CDialogEx)

CParaSetDlg::CParaSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CParaSetDlg::IDD, pParent)
{

}

CParaSetDlg::~CParaSetDlg()
{
}

void CParaSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CParaSetDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CParaSetDlg 消息处理程序


void CParaSetDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (nType==SIZE_RESTORED)
	{
		CSizeAdjust SizeAdj;
		SizeAdj.OnSizeAdjust(ParaSetDlgRect,this,cx,cy);
	}
}

HFONT hFont;
BOOL CParaSetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//获得参数设置对话框的大小
	GetClientRect(ParaSetDlgRect);
	//创建字体1
	m_ParaFont1.CreatePointFont(150,"黑体");
	m_ParaFont2.CreatePointFont(250,"黑体");
	for (int i=0;i<12;i++)
	{
		GetDlgItem(IDC_CHECK1+i)->SetFont(&m_ParaFont1);
	}
	GetDlgItem(IDC_PARA_STC0)->SetFont(&m_ParaFont2);
	return TRUE;
}