#pragma once


// CDlgSetDevSN 대화 상자입니다.

struct ITEM_SCM_DEV_SETTINGS;
class CPS_CCM_App_SGDlg;

class CDlgSetDevSN : public CDialog
{
	DECLARE_DYNAMIC(CDlgSetDevSN)

public:
	CDlgSetDevSN(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgSetDevSN();

	BOOL m_bSetUSM;
	ITEM_SCM_DEV_SETTINGS *m_bufSCM_DevSettings;
	CPS_CCM_App_SGDlg *m_pDlgPParent;

	int m_idxSCM;
	int m_idxUSM_LGM;
	int m_numSN;

	void SetData (BOOL bSetUSM, CPS_CCM_App_SGDlg *pDlgPParent, ITEM_SCM_DEV_SETTINGS *pISCMDevS);
	void UpdateDlgItemFromDevInfo (BOOL bUpdateNumSN = FALSE);
	void SetSNumFromDlgValue ();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_SET_DEV_SN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_stacIdxSCM;
	CStatic m_stacIdxUSM_LGM;
	CStatic m_stacNumSN;
	afx_msg void OnBnClickedButScmLeft();
	afx_msg void OnBnClickedButScmRight();
	afx_msg void OnBnClickedButUsmLeft();
	afx_msg void OnBnClickedButUsmRight();
	afx_msg void OnBnClickedButSetNewSn();
	afx_msg void OnBnClickedButInc100000();
	afx_msg void OnBnClickedButDec100000();
	afx_msg void OnBnClickedButInc10000();
	afx_msg void OnBnClickedButDec10000();
	afx_msg void OnBnClickedButInc1000();
	afx_msg void OnBnClickedButDec1000();
	afx_msg void OnBnClickedButInc100();
	afx_msg void OnBnClickedButDec100();
	afx_msg void OnBnClickedButInc10();
	afx_msg void OnBnClickedButDec10();
	afx_msg void OnBnClickedButInc1();
	afx_msg void OnBnClickedButDec1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
