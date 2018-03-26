
// CCMSTBDTestDlg.h : 헤더 파일
//

#pragma once
#include "Comm.h"
#include "afxwin.h"

typedef struct txPacket{
	int stx;
	char type;
	unsigned short data_length;
	char buf[128];
	char check_sum;
	int etx;
}txPacket;

// CCCMSTBDTestDlg 대화 상자
class CCCMSTBDTestDlg : public CDialog
{
// 생성입니다.
public:
	CCCMSTBDTestDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CCMSTBDTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	TTYSTRUCT Int2TTY();
	CComm m_Comm;

	int	m_nBaudRate;
	int	m_nComPort;
	int m_nFlowControl;
	int m_nStopBits;
	int m_nDataBits;
	int m_nParity;

	int m_isComPortOpen;
	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg LONG OnReceiveData(UINT, LONG);
	afx_msg void OnBnClickedButtonDeviceManager();
	afx_msg void OnBnClickedButtonComportOpen();
	afx_msg void OnBnClickedButtonComportClose();
	CComboBox m_ctrlComboPort;
	CComboBox m_ctrlComboBaudRate;
	CString m_editSTX;
	BYTE m_editTYPE;
	short m_editLENGTH;
	BYTE m_editDATA;
	BYTE m_editCHECKSUM;
	CString m_editETX;
	afx_msg void OnBnClickedButtonSend();

	BYTE getCheckSum(BYTE * data, int length);
};
