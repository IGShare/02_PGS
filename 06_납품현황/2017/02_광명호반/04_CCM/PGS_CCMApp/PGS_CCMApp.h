// PGS_CCMApp.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#ifdef STANDARDSHELL_UI_MODEL
#include "resource.h"
#endif

// CPGS_CCMApp:
// �� Ŭ������ ������ ���ؼ��� PGS_CCMApp.cpp�� �����Ͻʽÿ�.
//

class CPGS_CCMApp : public CWinApp
{
public:
	CPGS_CCMApp();
	
// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CPGS_CCMApp theApp;
