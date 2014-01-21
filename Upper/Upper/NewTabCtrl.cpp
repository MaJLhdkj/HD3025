// NewTabCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "Upper.h"
#include "NewTabCtrl.h"


// CNewTabCtrl
//存放tab控件窗口大小
CRect TabRect;
IMPLEMENT_DYNAMIC(CNewTabCtrl, CTabCtrl)

CNewTabCtrl::CNewTabCtrl()
{

}

CNewTabCtrl::~CNewTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CNewTabCtrl, CTabCtrl)
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CNewTabCtrl 消息处理程序




void CNewTabCtrl::OnSize(UINT nType, int cx, int cy)
{
	CTabCtrl::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (nType==SIZE_RESTORED)
	{
		CSizeAdjust SizeAdj;
		SizeAdj.OnSizeAdjust(TabRect,(CDialog*)this,cx,cy);
	}
}


//void CNewTabCtrl::OnFinalRelease()
//{
//	// TODO: 在此添加专用代码和/或调用基类
//
//	CTabCtrl::OnFinalRelease();
//}
