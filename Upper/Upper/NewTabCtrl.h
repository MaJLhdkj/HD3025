#pragma once
#include "SizeAdjust.h"
// CNewTabCtrl

class CNewTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CNewTabCtrl)

public:
	CNewTabCtrl();
	virtual ~CNewTabCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	virtual void OnFinalRelease();
};


