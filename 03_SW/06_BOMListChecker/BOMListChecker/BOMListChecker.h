
// BOMListChecker.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CBOMListCheckerApp:
// �� Ŭ������ ������ ���ؼ��� BOMListChecker.cpp�� �����Ͻʽÿ�.
//

class CBOMListCheckerApp : public CWinAppEx
{
public:
	CBOMListCheckerApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CBOMListCheckerApp theApp;