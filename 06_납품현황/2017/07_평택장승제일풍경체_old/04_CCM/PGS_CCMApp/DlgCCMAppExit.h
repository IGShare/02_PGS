#pragma once


// CDlgCCMAppExit ��ȭ �����Դϴ�.

class CDlgCCMAppExit : public CDialog
{
	DECLARE_DYNAMIC(CDlgCCMAppExit)

public:
	CDlgCCMAppExit(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgCCMAppExit();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PGS_CCMAPP_EXIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonPgmExit();
};
