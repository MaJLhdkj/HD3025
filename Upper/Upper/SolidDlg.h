#pragma once
#include "SizeAdjust.h"

// CSolidDlg �Ի���

class CSolidDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSolidDlg)

public:
	CSolidDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSolidDlg();

// �Ի�������
	enum { IDD = IDD_DLG_SOLID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	CFont m_SolidFont1;
	CFont m_SolidFont2;
	CFont m_SolidFont3;
};
