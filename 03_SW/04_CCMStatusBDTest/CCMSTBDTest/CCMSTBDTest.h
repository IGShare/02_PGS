
// CCMSTBDTest.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CCCMSTBDTestApp:
// �� Ŭ������ ������ ���ؼ��� CCMSTBDTest.cpp�� �����Ͻʽÿ�.
//

class CCCMSTBDTestApp : public CWinAppEx
{
public:
	CCCMSTBDTestApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CCCMSTBDTestApp theApp;