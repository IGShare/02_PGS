#pragma once


#define WM_DOO_NOTIFY_UPDATE_DLG_SG		WM_USER +100

// CDlgSettingGeneral ��ȭ �����Դϴ�.

struct ITEM_SCM_DEV_SETTINGS;
class CPS_CCM_App_SGDlg;

class CDlgSettingGeneral : public CDialog
{
	DECLARE_DYNAMIC(CDlgSettingGeneral)

public:
	CDlgSettingGeneral(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgSettingGeneral();

	ITEM_SCM_DEV_SETTINGS *m_pBufSCM_DevSettings;
	CPS_CCM_App_SGDlg *m_pDlgParent;

	void SetData (CPS_CCM_App_SGDlg *pDlgParent, ITEM_SCM_DEV_SETTINGS *pISCMDevS);

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_SETTING_GENERAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
