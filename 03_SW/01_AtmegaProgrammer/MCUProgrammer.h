
// MCUProgrammer.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMCUProgrammerApp:
// �� Ŭ������ ������ ���ؼ��� MCUProgrammer.cpp�� �����Ͻʽÿ�.
//

class CMCUProgrammerApp : public CWinAppEx
{
public:
	CMCUProgrammerApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMCUProgrammerApp theApp;