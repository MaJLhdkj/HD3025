// OutlookList.cpp : implementation file
//

#include "stdafx.h"
#include "OutlookList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//����һ��CRect���洢OutlookList�Ĵ��ڴ�С
CRect OutlookListRect;
/////////////////////////////////////////////////////////////////////////////
// COutlookList

COutlookList::COutlookList()
	: m_ButtonHeight (60),m_ButtonCount(0)
{
	m_LeftMargin = 70;
	pItemDlbFun = NULL;
}

COutlookList::~COutlookList()
{
	//m_pButton.RemoveAll();
	int m = m_pButton.GetSize();
	for (int i = 0; i<m_pButton.GetSize();i++)
	{
		((CButton*)m_pButton[i])->DestroyWindow();
		delete ((CButton*)m_pButton[i]);
	}
}

BEGIN_MESSAGE_MAP(COutlookList, CListCtrl)
	//{{AFX_MSG_MAP(COutlookList)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutlookList message handlers

void COutlookList::AddButton(LPCSTR Btntext,UINT uID)
{
	int index =  m_pButton.Add(new CListButton);
	((CListButton*)m_pButton[m_pButton.GetSize()-1])->Create(Btntext,WS_CHILD,GetAddButtonRect(),this,uID);
	((CListButton*)m_pButton[m_pButton.GetSize()-1])->m_Index = index;
	((CListButton*)m_pButton[m_pButton.GetSize()-1])->ShowWindow(SW_SHOW);
	m_ButtonCount+=1;
}

//��ȡ��Ҫ��Ӱ�ť�Ŀͻ�����
CRect COutlookList::GetAddButtonRect()
{
	int count = m_pButton.GetSize();
	int sumheight = 0;
	CRect rect;
	GetClientRect(rect);
	if (count>1)
	{
		CRect rect1;
		for (int m=0; m<count-1;m++)
		{
			((CListButton*)m_pButton[m])->GetClientRect(rect1);
			sumheight+=rect1.Height();
		}
		return CRect(0,sumheight,rect.Width(),sumheight+m_ButtonHeight);		
	}
	else
		return CRect(0,0,rect.Width(),m_ButtonHeight);
}

int COutlookList::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}		
	return 0;
}

void COutlookList::PreSubclassWindow() 
{
	CListCtrl::PreSubclassWindow();
	m_ClientList.Create(LVS_ICON,CRect(0,0,0,0),this,101);
	
	//m_ClientList.MoveWindow(GetListClientRect());
	SetBkColor(RGB(192,192,192));

	SetTextBkColor(RGB(192,192,192));
	//�б��������ɫ��
	SetTextColor(RGB(0,0,255));


	m_ClientList.SetExtendedStyle(LVS_EX_FLATSB);

	m_ClientList.SetBkColor(RGB(192,192,192));

	m_ClientList.SetTextBkColor(RGB(192,192,192));
	m_ClientList.SetTextColor(RGB(0,0,255));

	m_ClientList.Arrange(LVA_ALIGNLEFT );
	m_ClientList.ShowWindow(SW_SHOW);
}

BOOL COutlookList::PreTranslateMessage(MSG* pMsg) 
{	
	if ((pMsg->hwnd==m_ClientList.m_hWnd)&&(pMsg->message==WM_LBUTTONDBLCLK))//˫����Ϊ����
	{
		int index;
		index = m_ClientList.GetSelectionMark();
		if (pItemDlbFun!= NULL)
			pItemDlbFun(&m_ClientList,index);
	}
	return CListCtrl::PreTranslateMessage(pMsg);
}

BOOL COutlookList::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	int index =  CommandToIndex(nID);
	if (index != -1)
	{
		OnButtonDown(index,nID);
	}
	m_ClientList.OnCmdMsg(nID,nCode,pExtra,pHandlerInfo);
	return CListCtrl::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

//��ť�ĵ�������
void COutlookList::OnButtonDown(UINT bIndex, UINT nID)
{
	CRect listrect,buttonrect;
	int height = 0;
	
	CListButton* temp;
	GetClientRect(listrect);
	if (m_ButtonCount!=1)
	{	
		temp = (CListButton*)m_pButton[bIndex];
		if (temp->m_Toped) //�û��������㰴ť
		{
			for (int i= m_ButtonCount-1; i>bIndex;i--)
			{
				temp = (CListButton*)m_pButton[i];
				temp->GetClientRect(buttonrect);			
				CRect rect(0,listrect.bottom-buttonrect.Height()-height,buttonrect.Width(),listrect.bottom-height);				
				height+= buttonrect.Height();
				temp->MoveWindow(rect);
				temp->m_Toped = FALSE;
			}			
		}
		else //���ڵ����ײ㰴ť
		{
			int bottomindex = GetBtmTopIndex();
			for (int i = bottomindex; i <=bIndex;i++)
			{
				int topheight = GetTopButtonHeight();//��ȡ���㰴ť�߶�

				temp = (CListButton*)m_pButton[i];
				temp->GetClientRect(buttonrect);

				CRect rect(0,topheight,buttonrect.Width(),topheight+buttonrect.Height());
				temp->MoveWindow(rect);
				temp->m_Toped = TRUE;			
			}
		}
		CRect rectclt =GetListClientRect();
		m_ClientList.MoveWindow(rectclt);
		ShowButtonItems(bIndex);
	}	
}

//���ݰ�ť���������
UINT COutlookList::CommandToIndex(UINT nID)
{
	for (int i = 0;i< m_pButton.GetSize();i++)
	{
		if ( ((CListButton*)m_pButton[i])->GetDlgCtrlID()==nID)
		{
			return ((CListButton*)m_pButton[i])->m_Index;
		}
	}
	return -1;
}

//���ض��㰴ť�ĸ߶�
UINT COutlookList::GetTopButtonHeight()
{
	UINT result = 0;
	CListButton* temp;
	CRect rect;
	for (int i = 0; i< m_ButtonCount;i++)
	{
		temp = (CListButton*)m_pButton[i];
		if (temp->m_Toped)
		{
			temp->GetClientRect(rect);
			result += rect.Height();
		}
	}
	return result;
}

UINT COutlookList::GetBtmBtnHeight()
{
	UINT result = 0;
	CListButton* temp;
	CRect rect;
	for (int i = 0; i< m_ButtonCount;i++)
	{
		temp = (CListButton*)m_pButton[i];
		if (temp->m_Toped==FALSE)
		{
			temp->GetClientRect(rect);
			result += rect.Height();
		}
	}
	return result;
}


//��ȡ��ǰ�ײ㰴ť�����Ϸ��ĵײ㰴ť������
UINT COutlookList::GetNumCurToBtmBtn(UINT nIndex)
{
	UINT result = 0;
	CListButton* temp;
	for (int i = 0; i<nIndex;i++)
	{
		temp = (CListButton*)m_pButton[i];		
		if (temp->m_Toped==FALSE)
			result+=1;
	}
	return (result);
}

//��ȡ�·���ť�Ķ�������
int COutlookList::GetBtmTopIndex()
{
	CListButton* temp;
	for (int i = 0; i<m_ButtonCount;i++)
	{
		temp = (CListButton*)m_pButton[i];		
		if (temp->m_Toped==FALSE)
			return i;
	}
	return -1;	
}
  

CRect COutlookList::GetListClientRect()
{
	int TopHeight = GetTopButtonHeight(); //��ȡ�Ϸ���ť�ĸ߶�
	int BtmHeight = GetBtmBtnHeight();	//��ȡ�·���ť�ĸ߶�
	
	CRect rect;
	GetClientRect(rect); //��ȡ�б��ܵĿͻ�����

	CRect ClientRect(0,TopHeight,rect.Width(),rect.Height()-BtmHeight);
	return ClientRect;

}

void COutlookList::AddButtonItems(UINT nIndex, CString &strItem)
{
	CListButton* temp;
	temp = (CListButton*)m_pButton[nIndex];

	temp->m_ButtonItems.AddTail(strItem);
}
CString COutlookList::GetButtonItems(UINT nIndex)
{
	CListButton* temp;
	temp = (CListButton*)m_pButton[nIndex];
	return temp->m_ButtonItems.GetAt(temp->m_ButtonItems.FindIndex(nIndex));
}
//��ʾָ����ť�������б���ͼ��
void COutlookList::ShowButtonItems(UINT nIndex)
{
	CListButton* temp;
	temp = (CListButton*)m_pButton[nIndex];
	m_ClientList.DeleteAllItems();

	CRect showrect = GetListClientRect();

	if (temp->m_ButtonItems.GetCount()>0)
	{
		POSITION pos;
		pos = temp->m_ButtonItems.GetHeadPosition();
		CString str= temp->m_ButtonItems.GetHead();
		CRect ClientRect;
		ClientRect= GetListClientRect();
		int m = 0;

		m_ClientList.InsertItem(m,str,m);
		m_ClientList.SetItemPosition(m,CPoint(m_LeftMargin,20+m*48));

		while (pos != temp->m_ButtonItems.GetTailPosition())
		{

			str = temp->m_ButtonItems.GetNext(pos);
			m_ClientList.InsertItem(m,str,m);

			m_ClientList.SetItemPosition(m,CPoint(m_LeftMargin,20+m*48));
			m+=1;
		}
		str = temp->m_ButtonItems.GetAt(pos);
		m_ClientList.InsertItem(m,str,m);
		m_ClientList.SetItemPosition(m,CPoint(m_LeftMargin,20+m*48));
	}
}

void COutlookList::SetImageLists(CImageList *pImagelist)
{
	if (pImagelist)
		m_ClientList.SetImageList(pImagelist,LVSIL_NORMAL);
}

void COutlookList::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{

	*pResult = 0;
}

void COutlookList::OnItemDblClick()
{

}

void COutlookList::OnSize(UINT nType, int cx, int cy)
{
	CListCtrl::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (nType==SIZE_RESTORED)
	{
		CSizeAdjust SizeAdj;
		SizeAdj.OnSizeAdjust(OutlookListRect,(CDialog*)this,cx,cy);
	}
}
