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
	//��ȡ��һ���Ӵ��ڣ�����һ���ؼ�
	pWnd = dlg->GetWindow(GW_CHILD);
	while (NULL != pWnd)
	{
		if(pWnd)//�ж��Ƿ�Ϊ�գ���Ϊ�Ի��򴴽�ʱ����ô˺���������ʱ�ؼ���δ����
		{
			CRect rectActive;   //��ȡ�ؼ��仯ǰ��С
			pWnd->GetWindowRect(rectActive);
			dlg->ScreenToClient(rectActive);//���ؼ���Сת��Ϊ�ڶԻ����е���������
			// cx/m_rect.Width()Ϊ�Ի����ں���ı仯����
			rectActive.left=rectActive.left*cx/myrect.Width();/////�����ؼ���С
			rectActive.right=rectActive.right*cx/myrect.Width();
			rectActive.top=rectActive.top*cy/myrect.Height();
			rectActive.bottom=rectActive.bottom*cy/myrect.Height();
			pWnd->MoveWindow(rectActive);//���ÿؼ���С
		}

		//��ȡ��һ���ؼ�
		pWnd = pWnd->GetNextWindow();
	}

	dlg->GetClientRect(myrect);
}