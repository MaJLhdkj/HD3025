#pragma once
#include "SizeAdjust.h"

// CMeasureDlg 对话框

class CMeasureDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMeasureDlg)

public:
	CMeasureDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMeasureDlg();

// 对话框数据
	enum { IDD = IDD_DLG_MEASURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
};
