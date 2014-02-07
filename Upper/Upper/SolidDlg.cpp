// SolidDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Upper.h"
#include "SolidDlg.h"
#include "afxdialogex.h"

//��ù�������Ի���ĳ�ʼ��С
CRect SolidDlgRect;
// CSolidDlg �Ի���

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


// CSolidDlg ��Ϣ�������

//////////////////////
void CSolidDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
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
	//��������
	m_SolidFont1.CreatePointFont(250,"����");
	m_SolidFont2.CreatePointFont(120,"����");
	m_SolidFont3.CreatePointFont(100,"����");
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
