// ParaSetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Upper.h"
#include "ParaSetDlg.h"
#include "afxdialogex.h"

//��ò������öԻ���ĳ�ʼ��С
CRect ParaSetDlgRect;
// CParaSetDlg �Ի���

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


// CParaSetDlg ��Ϣ�������


void CParaSetDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
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
	//��ò������öԻ���Ĵ�С
	GetClientRect(ParaSetDlgRect);
	//��������1
	m_ParaFont1.CreatePointFont(150,"����");
	m_ParaFont2.CreatePointFont(250,"����");
	for (int i=0;i<12;i++)
	{
		GetDlgItem(IDC_CHECK1+i)->SetFont(&m_ParaFont1);
	}
	GetDlgItem(IDC_PARA_STC0)->SetFont(&m_ParaFont2);
	return TRUE;
}