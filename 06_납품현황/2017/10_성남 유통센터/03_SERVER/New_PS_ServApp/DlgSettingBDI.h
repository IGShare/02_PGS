#pragma once
#include "afxcmn.h"
#include "afxwin.h"

const RECT GL_RC_BD_EDIT_WND = {
	333, 17, 333 +927, 17 +625
};
#define ID_BD_EDIT_WND		1001

#define DEF_DI_SZ_H			32
#define MIN_DI_SZ_H			0
#define MAX_DI_SZ_H			255
#define DEF_DI_SZ_V			32
#define MIN_DI_SZ_V			0
#define MAX_DI_SZ_V			255
#define DEF_DI_ANG			0
#define MIN_DI_ANG			0
#define MAX_DI_ANG			359

#define MIN_LTPM_DAY		0
#define MAX_LTPM_DAY		200
#define MIN_LTPM_HOUR		0
#define MAX_LTPM_HOUR		23
#define MIN_LTPM_MIN		0
#define MAX_LTPM_MIN		59

// CDlgSettingBDI 대화 상자입니다.

class CBD_EditWnd;
class CDlgSettingBDI : public CDialog
{
	DECLARE_DYNAMIC(CDlgSettingBDI)

	static void UpdateIBDA_FromICDA ();

public:
	CDlgSettingBDI(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgSettingBDI();

	CBD_EditWnd *m_pBD_EditWnd;
	HTREEITEM m_hSelTI;
	int m_idxSelDevType;
	INFO_BACK_DRAWING_ITEM *m_pSelIBDI;
	int m_idxSelDI;
	int m_idxOldSelDI;

	CPoint m_offPickDI;

	int m_SS_idxComDevID_CCM;
	int m_SS_idxComDevID_SCM;
	int m_SS_idxComDevID_USM_LGM;
	int m_SS_idxDevType;

	int m_bufIdxCCM_fromComboIdx[MAX_NUM_CCM];
	int m_bufIdxSCM_fromComboIdx[MAX_NUM_SCM];
	int m_bufIdxUSM_LGM_fromComboIdx[MAX_NUM_USM];

	void UpdateTrcBDI (BOOL bFullUpdate);
	void UpdateComDevID_SCM ();
	void UpdateComDevID_USM_LGM ();
	void ResetComDevID_SCM ();
	void ResetComDevID_USM_LGM ();
	void SaveStateComDevIDs ();
	void RestoreStateComDevIDs ();
	void CheckComDevIDs_and_SetSelDI_by_ComDevIDs ();

	void SetDevPosCtrlRange (int szImgH, int szImgV);
	void SetDevPosCtrlCurPos (int posX, int posY);

	void SetDlgItemState_by_SelDI ();
	void SetDlgItem_RadDevType_by_idxDevType (int idxDevType);

	BOOL SetDI_by_ComDevIDs_IdxDevType (int idxDI);
	void SetDI_by_SzAngPosLTPM (int idxDI);
	void SetDI_by_PtOrg (int idxDI, int ptOrgX, int ptOrgY);
	void ResetDI_BufPtDrawDisp ();

	BOOL IsNamePathEmpty ();
	void GetItemIdxFromTreeSel (int &idxMain, int &idxSub);

	int AddDispItemToSelIBDI ();
	void DeleteSelDispItemFromSelIBDI ();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_SETTING_BDI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CTreeCtrl m_trcBDI;
	CString m_edStrBD_Name;
	CString m_edStrBD_ImgPath;
	afx_msg void OnBnClickedButOpenBdImgPath();
	afx_msg void OnBnClickedButBdMainAdd();
	afx_msg void OnBnClickedButBdSubAdd();
	afx_msg void OnBnClickedButBdModify();
	afx_msg void OnBnClickedButBdDelete();
	afx_msg void OnBnClickedButBdPosUp();
	afx_msg void OnBnClickedButBdPosDn();
	afx_msg void OnBnClickedRadDevType0();
	afx_msg void OnBnClickedRadDevType1();
	CSliderCtrl m_sliDI_SzH;
	CSliderCtrl m_sliDI_SzV;
	CSliderCtrl m_sliDI_Ang;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CStatic m_stacDevCapUSM_LGM;
	CComboBox m_comDevID_CCM;
	CComboBox m_comDevID_SCM;
	CComboBox m_comDevID_USM_LGM;
	afx_msg void OnCbnSelchangeComDevIdCcm();
	afx_msg void OnCbnSelchangeComDevIdScm();
	afx_msg void OnCbnSelchangeComDevIdUsmLgm();
	BOOL m_chUseLTPM;
	CComboBox m_comLTPM_TimeDay;
	CComboBox m_comLTPM_TimeHour;
	CComboBox m_comLTPM_TimeMin;
	afx_msg void OnBnClickedChUseLtpm();
	afx_msg void OnCbnSelchangeComLtpmTimeDay();
	afx_msg void OnCbnSelchangeComLtpmTimeHour();
	afx_msg void OnCbnSelchangeComLtpmTimeMin();
	afx_msg void OnTvnSelchangedTrBdi(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg LRESULT OnBDEW_MouseLBtnDn(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBDEW_MouseMove(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBDEW_MouseLBtnClick(WPARAM wParam, LPARAM lParam);

	CSliderCtrl m_sliDI_PosX;
	CSliderCtrl m_sliDI_PosY;
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
