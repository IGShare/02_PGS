
// PS_ServApp.h : PS_ServApp ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CPS_ServAppApp:
// �� Ŭ������ ������ ���ؼ��� PS_ServApp.cpp�� �����Ͻʽÿ�.
//

class CPS_ServAppApp : public CWinAppEx
{
public:
	CPS_ServAppApp();

	void DoFileNew ();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPS_ServAppApp theApp;
