#pragma once


// CBD_EditWnd

#define WM_BDEW_MSG_MOUSE_L_BTN_DN	(WM_USER +100)
#define WM_BDEW_MSG_MOUSE_MOVE		(WM_USER +101)
#define WM_BDEW_MSG_MOUSE_CLICK		(WM_USER +102)

class CxImage;

class CBD_EditWnd : public CWnd
{
	DECLARE_DYNAMIC(CBD_EditWnd)

public:
	CBD_EditWnd();
	virtual ~CBD_EditWnd();

	CxImage *m_pXImg;
	INFO_BACK_DRAWING_ITEM *m_pIBDI;
	int m_idxSelDI;

	BOOL m_bLButDn;
	CPoint m_ptMouseLButDn;
	CPoint m_ptLastMouseMove;
	int m_idxPickedDI;

	CDC m_dcBack;
	CBitmap m_biBack, *m_pOldBiBack;

	CDC m_dcDrawDI;
	CBitmap m_biDrawDI, *m_pOldBiDrawDI;

	CRect m_rcClient;
	CSize m_szBack;
	CPoint m_ptBackDispStart;

	void SetBDI (INFO_BACK_DRAWING_ITEM *pBDI);
	void SetIdxSelDI (int idxSelDI);

	void GetSzBackImg (CSize &szBackImg);

private:
	int GetIdxDI_fromPt (CPoint ptClient, CPoint &ptCorrected);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


