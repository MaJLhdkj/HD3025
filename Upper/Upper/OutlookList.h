#pragma once
#include "ListButton.h"
#include "SizeAdjust.h"

#define LISTID = 2014;

//定义双击列表视图项的回调函数
typedef void(ItemDlbFun)(const CListCtrl* pListCtrl,int nItemIndex);

class COutlookList : public CListCtrl
{
// Construction
public:
	COutlookList();
	CPtrArray m_pButton; //按钮数组
	UINT m_ButtonCount ; //按钮数量

	UINT m_LeftMargin; //图像列表显示的左边距
	CListCtrl m_ClientList; //在客户区域显示视图项
	ItemDlbFun* pItemDlbFun; //视图项的双击事件
// Attributes
public:

// Operations

private:
	UINT m_ButtonHeight; //按钮高度
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
	CString GetButtonItems(UINT nIndex);//增加的函数，获取指定Index的Button内容
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

