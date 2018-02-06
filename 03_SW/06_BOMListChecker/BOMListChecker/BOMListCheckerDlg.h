
// BOMListCheckerDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CBOMListCheckerDlg ��ȭ ����
class CBOMListCheckerDlg : public CDialog
{
// �����Դϴ�.
public:
	CBOMListCheckerDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_BOMLISTCHECKER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
