#include "StdAfx.h"
#include "SizeAdjust.h"

CSizeAdjust::CSizeAdjust(void)
{

}

CSizeAdjust::~CSizeAdjust(void)
{

}

void CSizeAdjust::OnSizeAdjust(CRect& myrect, CDialog* dlg, int cx, int cy)
{
	CRect rect;
	dlg->GetClientRect(&rect);
	if (0 == rect.Width())
		return;

	CWnd* pWnd;
	//获取第一个子窗口，即第一个控件
	pWnd = dlg->GetWindow(GW_CHILD);
	while (NULL != pWnd)
	{
		if(pWnd)//判断是否为空，因为对话框创建时会调用此函数，而当时控件还未创建
		{
			CRect rectActive;   //获取控件变化前大小
			pWnd->GetWindowRect(rectActive);
			dlg->ScreenToClient(rectActive);//将控件大小转换为在对话框中的区域坐标
			// cx/m_rect.Width()为对话框在横向的变化比例
			rectActive.left=rectActive.left*cx/myrect.Width();/////调整控件大小
			rectActive.right=rectActive.right*cx/myrect.Width();
			rectActive.top=rectActive.top*cy/myrect.Height();
			rectActive.bottom=rectActive.bottom*cy/myrect.Height();
			pWnd->MoveWindow(rectActive);//设置控件大小
		}

		//获取下一个控件
		pWnd = pWnd->GetNextWindow();
	}

	dlg->GetClientRect(myrect);
}