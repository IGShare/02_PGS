
// PS_ServAppView.h : CPS_ServAppView Ŭ������ �������̽�
//


#pragma once

enum {
	ID_BD_DISP_WND = 2000,
};

class CBD_DispWnd;

class CPS_ServAppView : public CView
{
protected: // serialization������ ��������ϴ�.
	CPS_ServAppView();
	DECLARE_DYNCREATE(CPS_ServAppView)

// Ư���Դϴ�.
public:
	CPS_ServAppDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	int m_idxMainBDI;
	int m_idxSubBDI;

	CBD_DispWnd *m_pBD_DispWnd;

	void UpdateBD_DispWnd ();
	void SetBD_DispWndUpdateFlag ();

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CPS_ServAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // PS_ServAppView.cpp�� ����� ����
inline CPS_ServAppDoc* CPS_ServAppView::GetDocument() const
   { return reinterpret_cast<CPS_ServAppDoc*>(m_pDocument); }
#endif

