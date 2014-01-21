#pragma once
#include "SizeAdjust.h"

// CParaSetDlg 对话框

class CParaSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CParaSetDlg)

public:
	CParaSetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CParaSetDlg();

// 对话框数据
	enum { IDD = IDD_DLG_PARASET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	CFont m_ParaFont1;
	CFont m_ParaFont2;
};
