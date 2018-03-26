
// BOMListCheckerDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"


// CBOMListCheckerDlg 대화 상자
class CBOMListCheckerDlg : public CDialog
{
// 생성입니다.
public:
	CBOMListCheckerDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_BOMLISTCHECKER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMFCButton m_ctrlButtonTest;
	afx_msg void OnBnClickedButtonTored();
	afx_msg void OnBnClickedButtonToblue();
	afx_msg void OnBnClickedButtonTogreen();
	afx_msg void OnBnClickedButtonImgLoad();

	CImage Image;
	CPoint m_ptMouse;
	CPoint m_ptMouse_down;
	CPoint m_ptMouse_up;
	bool m_imageloadF;
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	CButton m_ctrlButton;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
