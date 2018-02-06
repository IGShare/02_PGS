#pragma once


#define WM_DOO_NOTIFY_UPDATE_DLG_SG		WM_USER +100

// CDlgSettingGeneral 대화 상자입니다.

struct ITEM_SCM_DEV_SETTINGS;
class CPS_CCM_App_SGDlg;

class CDlgSettingGeneral : public CDialog
{
	DECLARE_DYNAMIC(CDlgSettingGeneral)

public:
	CDlgSettingGeneral(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgSettingGeneral();

	ITEM_SCM_DEV_SETTINGS *m_pBufSCM_DevSettings;
	CPS_CCM_App_SGDlg *m_pDlgParent;

	void SetData (CPS_CCM_App_SGDlg *pDlgParent, ITEM_SCM_DEV_SETTINGS *pISCMDevS);

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_SETTING_GENERAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButHideDlg();
	afx_msg void OnBnClickedButAppExit();
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedButSetMaxDetAll();
	afx_msg void OnBnClickedButSetMaxDetInd();
	afx_msg void OnBnClickedButSetUsmSn();
	afx_msg void OnBnClickedButSetLgmSn();
};
