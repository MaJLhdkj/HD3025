#pragma once
#include "SizeAdjust.h"

// CMeasureDlg �Ի���

class CMeasureDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMeasureDlg)

public:
	CMeasureDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMeasureDlg();

// �Ի�������
	enum { IDD = IDD_DLG_MEASURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
};
