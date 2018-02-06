
// MainFrm.h : CMainFrame Ŭ������ �������̽�
//

#pragma once

#include "PaneBD.h"
#include "PaneInfoEboard.h"
#include "ManClNetComm.h"

enum {
	IDX_PANE_BD,
	IDX_PANE_INFO_EBOARD,
	NUM_CHILD_PANE
};
enum {
	ID_PANE_BD = 1000,
	ID_PANE_INFO_EBOARD,
	ID_PANE_WARNING,
};
const char *const GL_BUF_STR_CHILD_PANE[NUM_CHILD_PANE] = {
	"���� ��Ȳ",
	"��ġ ����",
};
const RECT GL_BUF_RC_CHILD_PANE[NUM_CHILD_PANE] = {
	0,   0, 0 +220,   0 +140,
	0,   0, 0 + 400,   0 +100,
};

class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// EBoard[S]
	CManClNetComm m_EBD_bufManClNetComm[NUM_EBOARD_DEV];
	volatile BOOL m_EBD_bufBEndThread[NUM_EBOARD_DEV];

	volatile int m_EBD_CHK_idxEBoard;
	// EBoard[E]

public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	CPaneInfoEboard m_paneInfoEbd;
protected:  // ��Ʈ�� ������ ���Ե� ����Դϴ�.
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;

	CPaneBD m_paneBD;
	

	void CreateDockingWnd ();

// ������ �޽��� �� �Լ�
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDestroy();
	afx_msg void OnSettingBackDrawingInfo();
	afx_msg void OnWindowLeftRight();
	afx_msg void OnSettingEboard();
	afx_msg void OnSettingCtrlDev();
};


