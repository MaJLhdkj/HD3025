// LiquidDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Upper.h"
#include "LiquidDlg.h"
#include "afxdialogex.h"
//����Һ������Ի����С
CRect LiquidDlgRect;
// CLiquidDlg �Ի���

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


// CLiquidDlg ��Ϣ�������


void CLiquidDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
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
