
// UpperCtrl.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUpperCtrlApp:
// �йش����ʵ�֣������ UpperCtrl.cpp
//

class CUpperCtrlApp : public CWinApp
{
public:
	CUpperCtrlApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CUpperCtrlApp theApp;