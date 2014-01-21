
// UpperDlg.h : 头文件
//

#pragma once
#include "OutlookList.h"
#include "newtabctrl.h"
#include "SizeAdjust.h"
#include "LiquidDlg.h"
#include "ParaSetDlg.h"
#include "SolidDlg.h"
#include "MeasureDlg.h"
// CUpperDlg 对话框
class CUpperDlg : public CDialogEx
{
// 构造
public:
	CUpperDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_UPPER_DIALOG };

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
	COutlookList m_List;
	CNewTabCtrl m_Tab;
	CImageList m_Imagelist;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	static void OnItemDouble(const CListCtrl* pListCtrl, int nIndex);
};
