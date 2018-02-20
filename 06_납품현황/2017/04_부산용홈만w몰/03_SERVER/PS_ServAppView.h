
// PS_ServAppView.h : CPS_ServAppView 클래스의 인터페이스
//


#pragma once

enum {
	ID_BD_DISP_WND = 2000,
};

class CBD_DispWnd;

class CPS_ServAppView : public CView
{
protected: // serialization에서만 만들어집니다.
	CPS_ServAppView();
	DECLARE_DYNCREATE(CPS_ServAppView)

// 특성입니다.
public:
	CPS_ServAppDoc* GetDocument() const;

// 작업입니다.
public:
	int m_idxMainBDI;
	int m_idxSubBDI;

	CBD_DispWnd *m_pBD_DispWnd;

	void UpdateBD_DispWnd ();
	void SetBD_DispWndUpdateFlag ();

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CPS_ServAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // PS_ServAppView.cpp의 디버그 버전
inline CPS_ServAppDoc* CPS_ServAppView::GetDocument() const
   { return reinterpret_cast<CPS_ServAppDoc*>(m_pDocument); }
#endif

