
// FWDownLoader.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CFWDownLoaderApp:
// �� Ŭ������ ������ ���ؼ��� FWDownLoader.cpp�� �����Ͻʽÿ�.
//

class CFWDownLoaderApp : public CWinAppEx
{
public:
	CFWDownLoaderApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CFWDownLoaderApp theApp;