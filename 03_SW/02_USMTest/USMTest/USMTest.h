
// USMTest.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CUSMTestApp:
// �� Ŭ������ ������ ���ؼ��� USMTest.cpp�� �����Ͻʽÿ�.
//

class CUSMTestApp : public CWinAppEx
{
public:
	CUSMTestApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CUSMTestApp theApp;