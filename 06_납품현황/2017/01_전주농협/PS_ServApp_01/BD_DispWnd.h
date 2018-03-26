#pragma once


enum {
	IDX_INDC_BACK_ORG,
	IDX_INDC_BACK_ZOOMED,
	IDX_INDC_BACK_PLUS_ITEMS,
	NUM_INTERNAL_DC
};

#define CLR_EMPTY_BACK					RGB(0, 0, 0)

enum {
	IDX_BI_FOR_BR_FORC_LED_OFF,
	IDX_BI_FOR_BR_FORC_LED_ON_GREEN,
	IDX_BI_FOR_BR_FORC_LED_ON_RED,
	IDX_BI_FOR_BR_FORC_LED_BLINKING,

	IDX_BI_FOR_BR_LT_COLOR_VIOLET,
	IDX_BI_FOR_BR_LT_COLOR_PINK,
	IDX_BI_FOR_BR_LT_COLOR_YELLOW,
	IDX_BI_FOR_BR_LT_COLOR_SKYBLUE,
	IDX_BI_FOR_BR_LT_COLOR_BLUE,

	NUM_BITMAP_FOR_BRUSH
};
enum {
	IDX_BRUSH_GREEN,
	IDX_BRUSH_RED,
	IDX_BRUSH_WHITE,
	IDX_BRUSH_BLACK,
	IDX_BRUSH_W_GRAY,
	IDX_BRUSH_B_GRAY,
	IDX_BRUSH_W_BLUE,

	IDX_BRUSH_VIOLET,
	IDX_BRUSH_PINK,
	IDX_BRUSH_YELLOW,
	IDX_BRUSH_SKYBLUE,
	IDX_BRUSH_BLUE,

	IDX_BRUSH_FORC_LED_OFF,
	IDX_BRUSH_FORC_LED_ON_GREEN,
	IDX_BRUSH_FORC_LED_ON_RED,
	IDX_BRUSH_FORC_LED_BLINKING,

	NUM_BRUSH
};

#define BDDW_BR_COLOR_GREEN				RGB(  0, 255,   0)
#define BDDW_BR_COLOR_RED				RGB(255,   0,   0)
#define BDDW_BR_COLOR_WHITE				RGB(255, 255, 255)
#define BDDW_BR_COLOR_BLACK				RGB(  0,   0,   0)
#define BDDW_BR_COLOR_W_GRAY			RGB(180, 180, 180)
#define BDDW_BR_COLOR_B_GRAY			RGB( 70,  70,  70)
#define BDDW_BR_COLOR_VIOLET			RGB(138,  43, 225)
#define BDDW_BR_COLOR_PINK				RGB(255,   0, 255)
#define BDDW_BR_COLOR_YELLOW			RGB(255, 255,   0)
#define BDDW_BR_COLOR_SKYBLUE			RGB(127, 255, 212)
#define BDDW_BR_COLOR_W_BLUE			RGB(  0,   0, 255)
#define BDDW_BR_COLOR_BLUE				RGB(  0,   0, 255)


class CxImage;

struct INFO_LONG_TERM_PARKING{
	BYTE bStartOccupied;
	BYTE bStartEmpty;

	SYSTEMTIME m_nLTPTimeRef;
	SYSTEMTIME m_nLTPTimeCur;
};

// CBD_DispWnd

class CBD_DispWnd : public CWnd
{
	DECLARE_DYNAMIC(CBD_DispWnd)

public:
	CBD_DispWnd();
	virtual ~CBD_DispWnd();

	void SetIBDI (INFO_BACK_DRAWING_ITEM *pIBDI);
	void InvalidateWithResetPos ();
	void SetUpdateFlag ();

	void Zoom_FitToScr ();
	void Zoom_1To1 (CPoint *pPtMouse);
	void Zoom_Mul_2 (CPoint *pPtMouse);
	void Zoom_Div_2 (CPoint *pPtMouse);

	void DrawDI (CDC *pDC);

private:
	CxImage *m_pXImg;
	CRect m_rcClient;
	INFO_BACK_DRAWING_ITEM *m_pIBDI;

	CDC m_bufInDC[NUM_INTERNAL_DC];
	CBitmap m_bufBitmap_InDC[NUM_INTERNAL_DC], *m_bufPBitmapOld_InDC[NUM_INTERNAL_DC];
	volatile BOOL m_idxStatInDC;

	int m_nZoom;
	BOOL m_bZoomChanged;

	CSize m_szBackOrg;
	CRect m_rcBackZoom;		// 원본에서 Zoom 할 영역의 위치
	CRect m_rcDstBlt;		// Dst DC 에 BLT 될 영역 좌표 (Zoom 된 이미지가 m_rcClient 보다 작은 경우에 필요)
	CPoint m_ptZoomDraw;	// Zoom 된 화면에서의 그리기 시작 위치

	CBitmap m_bufBiForBr[NUM_BITMAP_FOR_BRUSH];
	CBrush m_bufBrush[NUM_BRUSH];

	BOOL m_bLButDn;
	CPoint m_ptLButDn;

	BOOL m_bRButDn;
	CPoint m_ptRButDn;

	BOOL m_bMouseMoved;	// L버튼 DOWN 이후 마우스 움직임 여부

	int m_numSelDI;
	int m_idxFirstSelDevType;

	BOOL m_bNeedUpdate;

	//SYSTEMTIME m_nLTPTimeRef;
	//SYSTEMTIME m_nLTPTimeCur;

	BOOL OpenImageFile (CString strImgFilePath);
	CString FindExtension (const CString& name);

	void ChangeZoomRatio (int nZoomRatio, CPoint *pPtMouse);
	void MoveZoomWnd (CPoint *pPtDiff, BOOL bInvalidate);
	void RecalcRcBackZoom ();

	void DeSelectDI_All ();
	void OnPopMenu_USMLGM_SetOpMode (int idxDevType, int idxOpMode);


	INFO_LONG_TERM_PARKING * m_ltParking;
	void SetRefTime();
	int GetCurTimeIndex();

	int TimeStartF;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);


};


