
// UpperCtrlDlg.h : ͷ�ļ�
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
// CUpperCtrlDlg �Ի���
class CUpperCtrlDlg : public CDialogEx
{
// ����
public:
	CUpperCtrlDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_UPPERCTRL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
};
