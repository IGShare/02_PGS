#pragma once


// CParkingStatus 대화 상자입니다.

class CParkingStatus : public CDialog
{
	DECLARE_DYNAMIC(CParkingStatus)

public:
	CParkingStatus(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CParkingStatus();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_PARKING_STATUS_DESCRIPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
