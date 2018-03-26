#pragma once


// CDlgSetMaxDetInd 대화 상자입니다.

struct ITEM_SCM_DEV_SETTINGS;
class CPS_CCM_App_SGDlg;

class CDlgSetMaxDetInd : public CDialog
{
	DECLARE_DYNAMIC(CDlgSetMaxDetInd)

public:
	CDlgSetMaxDetInd(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgSetMaxDetInd();

	ITEM_SCM_DEV_SETTINGS *m_bufSCM_DevSettings;
	CPS_CCM_App_SGDlg *m_pDlgPParent;

	int m_idxSCM;
	int m_idxUSM;
	int m_idxMaxDet;

	void SetData (CPS_CCM_App_SGDlg *pDlgPParent, ITEM_SCM_DEV_SETTINGS *pISCMDevS);
	void UpdateDlgItemFromDevInfo ();
	void SetMaxDetFromDlgValue ();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_SET_MAX_DET_IND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_stacIdxSCM;
	CStatic m_stacIdxUSM;
	CStatic m_stacNumMaxDet;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButScmLeft();
	afx_msg void OnBnClickedButScmRight();
	afx_msg void OnBnClickedButUsmLeft();
	afx_msg void OnBnClickedButUsmRight();
	afx_msg void OnBnClickedButDec10();
	afx_msg void OnBnClickedButInc10();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
