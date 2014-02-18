
// UpperCtrlDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "NewTabCtrl.h"
#include "SolidDlg.h"
#include "LiquidDlg.h"
#include "CheckDlg.h"
#include "ParaSetDlg.h"
#include "DataQueryDlg.h"
#include "SizeAdjust.h"
#include "afxbutton.h"
// CUpperCtrlDlg 对话框
class CUpperCtrlDlg : public CDialogEx
{
// 构造
public:
	CUpperCtrlDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_UPPERCTRL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CNewTabCtrl m_TabCtrl;
	CSolidDlg m_SolidDlg;
	CLiquidDlg m_LiquidDlg;
	CParaSetDlg m_ParaSetDlg;
	CCheckDlg m_CheckDlg;
	CDataQueryDlg m_DataQueryDlg;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	CFont m_DlgFont;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	CFont m_DlgFont1;
	CStatusBar  m_StausBar;
	afx_msg void OnBnClickedBtnDlg1();
	afx_msg void OnBnClickedBtnDlg5();
protected:
	afx_msg LRESULT OnSolidshow(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnLiquidshow(WPARAM wParam, LPARAM lParam);
	virtual void OnCancel();
public:
	afx_msg void OnClose();
	CProgressCtrl m_Progress;
//	CImage m_Image;
//	CMFCButton m_Btn1;
	CMFCButton m_Btn_Dlg1;
	CMFCButton m_Btn_Dlg2;
	CMFCButton m_Btn_Dlg3;
	CMFCButton m_Btn_Dlg4;
	CMFCButton m_Btn_Dlg5;
	CMFCButton m_Btn_Dlg6;
//	CMFCButton m;
	CMFCButton m_Btn_Dlg7;
	CMFCButton m_Btn_Dlg8;
	BOOL RegisterDevice(void);
	BOOL CloseHD3025Device(void);
	Uint8 ConnectHD3025(HSProtocal *HsP);
public:
//	HSProtocal m_Protocal[1];
	BOOL OpenHD3025Device(void);
	Uint8 WriteParameters(Uint8 Cmd);
	CMFCButton m_Btn_Dlg9;
	CString m_DefaultPath;
	CString m_strPath;
	afx_msg void OnBnClickedBtnDlg9();
};
