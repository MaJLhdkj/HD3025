// NewTabCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Upper.h"
#include "NewTabCtrl.h"


// CNewTabCtrl
//���tab�ؼ����ڴ�С
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



// CNewTabCtrl ��Ϣ�������




void CNewTabCtrl::OnSize(UINT nType, int cx, int cy)
{
	CTabCtrl::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (nType==SIZE_RESTORED)
	{
		CSizeAdjust SizeAdj;
		SizeAdj.OnSizeAdjust(TabRect,(CDialog*)this,cx,cy);
	}
}


//void CNewTabCtrl::OnFinalRelease()
//{
//	// TODO: �ڴ����ר�ô����/����û���
//
//	CTabCtrl::OnFinalRelease();
//}
