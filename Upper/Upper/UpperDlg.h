
// UpperDlg.h : ͷ�ļ�
//

#pragma once
#include "OutlookList.h"
#include "newtabctrl.h"
#include "SizeAdjust.h"
#include "LiquidDlg.h"
#include "ParaSetDlg.h"
#include "SolidDlg.h"
#include "MeasureDlg.h"
// CUpperDlg �Ի���
class CUpperDlg : public CDialogEx
{
// ����
public:
	CUpperDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_UPPER_DIALOG };

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
	COutlookList m_List;
	CNewTabCtrl m_Tab;
	CImageList m_Imagelist;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	static void OnItemDouble(const CListCtrl* pListCtrl, int nIndex);
};
