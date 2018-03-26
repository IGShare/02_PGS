#pragma once
#include "afxwin.h"


// CDlgSetMaxDetAll 대화 상자입니다.

struct ITEM_SCM_DEV_SETTINGS;
class CPS_CCM_App_SGDlg;

class CDlgSetMaxDetAll : public CDialog
{
	DECLARE_DYNAMIC(CDlgSetMaxDetAll)

public:
	CDlgSetMaxDetAll(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgSetMaxDetAll();

	ITEM_SCM_DEV_SETTINGS *m_bufSCM_DevSettings;
	CPS_CCM_App_SGDlg *m_pDlgPParent;

	int m_idxSCM;
	int m_idxMaxDet;

	void SetData (CPS_CCM_App_SGDlg *pDlgPParent, ITEM_SCM_DEV_SETTINGS *pISCMDevS);
	void UpdateDlgItemFromIdxSCM ();
	void SetMaxDetFromDlgValue ();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_SET_MAX_DET_ALL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_stacIdxSCM;
	CStatic m_stacNumMaxDet;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButScmLeft();
	afx_msg void OnBnClickedButScmRight();
	afx_msg void OnBnClickedButInc10();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButDec10();
};
