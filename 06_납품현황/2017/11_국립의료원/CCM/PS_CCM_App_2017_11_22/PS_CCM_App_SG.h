// PS_CCM_App_SG.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#ifdef STANDARDSHELL_UI_MODEL
#include "resource.h"
#endif

// CPS_CCM_App_SGApp:
// �� Ŭ������ ������ ���ؼ��� PS_CCM_App_SG.cpp�� �����Ͻʽÿ�.
//

class CPS_CCM_App_SGApp : public CWinApp
{
public:
	CPS_CCM_App_SGApp();
	
// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CPS_CCM_App_SGApp theApp;
