#pragma once
#include "ListButton.h"
#include "SizeAdjust.h"

#define LISTID = 2014;

//����˫���б���ͼ��Ļص�����
typedef void(ItemDlbFun)(const CListCtrl* pListCtrl,int nItemIndex);

class COutlookList : public CListCtrl
{
// Construction
public:
	COutlookList();
	CPtrArray m_pButton; //��ť����
	UINT m_ButtonCount ; //��ť����

	UINT m_LeftMargin; //ͼ���б���ʾ����߾�
	CListCtrl m_ClientList; //�ڿͻ�������ʾ��ͼ��
	ItemDlbFun* pItemDlbFun; //��ͼ���˫���¼�
// Attributes
public:

// Operations

private:
	UINT m_ButtonHeight; //��ť�߶�
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutlookList)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnItemDblClick();
	void SetImageLists(CImageList* pImagelist);
	void ShowButtonItems(UINT nIndex);
	void AddButtonItems(UINT nIndex,CString& strItem);
	CString GetButtonItems(UINT nIndex);//���ӵĺ�������ȡָ��Index��Button����
	UINT GetBtmBtnHeight();
	CRect GetListClientRect();
	int GetBtmTopIndex();
	UINT GetNumCurToBtmBtn(UINT nIndex);
	UINT GetTopButtonHeight();
	UINT CommandToIndex(UINT nID);
	void OnButtonDown(UINT bIndex, UINT nID);
	CRect GetAddButtonRect();
	void AddButton(LPCSTR text,UINT uID);
	virtual ~COutlookList();

	// Generated message map functions
protected:
	//{{AFX_MSG(COutlookList)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

