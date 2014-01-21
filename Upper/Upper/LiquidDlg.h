#pragma once
#include "SizeAdjust.h"

// CLiquidDlg 对话框

class CLiquidDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLiquidDlg)

public:
	CLiquidDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLiquidDlg();

// 对话框数据
	enum { IDD = IDD_DLG_LIQUID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
};
