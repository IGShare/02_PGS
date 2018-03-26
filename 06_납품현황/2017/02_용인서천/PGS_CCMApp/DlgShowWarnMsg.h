#pragma once


// CDlgShowWarnMsg 대화 상자입니다.

class CDlgShowWarnMsg : public CDialog
{
	DECLARE_DYNAMIC(CDlgShowWarnMsg)

public:
	CDlgShowWarnMsg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgShowWarnMsg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PGS_CCMAPP_WARN_MSG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
