#pragma once
#include "SizeAdjust.h"

// CLiquidDlg �Ի���

class CLiquidDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLiquidDlg)

public:
	CLiquidDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLiquidDlg();

// �Ի�������
	enum { IDD = IDD_DLG_LIQUID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
};
