// LiquidDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Upper.h"
#include "LiquidDlg.h"
#include "afxdialogex.h"
//储存液体测量对话框大小
CRect LiquidDlgRect;
// CLiquidDlg 对话框

IMPLEMENT_DYNAMIC(CLiquidDlg, CDialogEx)

CLiquidDlg::CLiquidDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLiquidDlg::IDD, pParent)
{

}

CLiquidDlg::~CLiquidDlg()
{
}

void CLiquidDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLiquidDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CLiquidDlg 消息处理程序


void CLiquidDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (nType==SIZE_RESTORED)
	{
		CSizeAdjust SizeAdj;
		SizeAdj.OnSizeAdjust(LiquidDlgRect,this,cx,cy);
	}
}


BOOL CLiquidDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetClientRect(LiquidDlgRect);
	return TRUE;
}
