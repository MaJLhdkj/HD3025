// MeasureDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Upper.h"
#include "MeasureDlg.h"
#include "afxdialogex.h"

CRect MeasureDlgRect;
// CMeasureDlg 对话框

IMPLEMENT_DYNAMIC(CMeasureDlg, CDialogEx)

CMeasureDlg::CMeasureDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMeasureDlg::IDD, pParent)
{

}

CMeasureDlg::~CMeasureDlg()
{
}

void CMeasureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMeasureDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMeasureDlg 消息处理程序


void CMeasureDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (nType==SIZE_RESTORED)
	{
		CSizeAdjust SizeAdj;
		SizeAdj.OnSizeAdjust(MeasureDlgRect,this,cx,cy);
	}
}


BOOL CMeasureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetClientRect(MeasureDlgRect);
	return TRUE;
}
