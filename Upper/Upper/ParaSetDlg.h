#pragma once
#include "SizeAdjust.h"

// CParaSetDlg �Ի���

class CParaSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CParaSetDlg)

public:
	CParaSetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CParaSetDlg();

// �Ի�������
	enum { IDD = IDD_DLG_PARASET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	CFont m_ParaFont1;
	CFont m_ParaFont2;
};
