#pragma once


// CDlgShowWarnMsg ��ȭ �����Դϴ�.

class CDlgShowWarnMsg : public CDialog
{
	DECLARE_DYNAMIC(CDlgShowWarnMsg)

public:
	CDlgShowWarnMsg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgShowWarnMsg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PGS_CCMAPP_WARN_MSG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
