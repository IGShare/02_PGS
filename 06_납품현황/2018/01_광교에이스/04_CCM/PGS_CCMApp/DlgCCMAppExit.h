#pragma once


// CDlgCCMAppExit 대화 상자입니다.

class CDlgCCMAppExit : public CDialog
{
	DECLARE_DYNAMIC(CDlgCCMAppExit)

public:
	CDlgCCMAppExit(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgCCMAppExit();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PGS_CCMAPP_EXIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonPgmExit();
};
