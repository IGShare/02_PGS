#pragma once


// CParkingStatus ��ȭ �����Դϴ�.

class CParkingStatus : public CDialog
{
	DECLARE_DYNAMIC(CParkingStatus)

public:
	CParkingStatus(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CParkingStatus();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_PARKING_STATUS_DESCRIPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
