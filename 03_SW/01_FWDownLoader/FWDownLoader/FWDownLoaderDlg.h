
// FWDownLoaderDlg.h : 헤더 파일
//

#pragma once
#include "Comm.h"
#include "afxwin.h"


// CFWDownLoaderDlg 대화 상자
class CFWDownLoaderDlg : public CDialog
{
// 생성입니다.
public:
	CFWDownLoaderDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_FWDOWNLOADER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	// CComm 클래스에서 보내는 메시지를 받아서 처리하기 위한 응용 함수 선언
	afx_msg LONG OnReceiveData(UINT, LONG);
// 구현입니다.
protected:
	HICON m_hIcon;

	CComm m_Comm;

	int	m_nBaudRate;
	int	m_nComPort;
	int m_nFlowControl;
	int m_nStopBits;
	int m_nDataBits;
	int m_nParity;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	TTYSTRUCT Int2TTY();
	afx_msg void OnBnClickedButtonOpenDevmgr();
	CComboBox m_ctrlComboPort;
	CComboBox m_ctrlComboBaudRate;
	afx_msg void OnBnClickedButtonComOpen();
	CString m_editReport;
	afx_msg void OnBnClickedButtonComClose();
	afx_msg void OnBnClickedButtonComTest();
	afx_msg void OnBnClickedButtonAutosynch();
	afx_msg void OnBnClickedButtonGetStatus();
	afx_msg void OnBnClickedButtonSectorProtectOfCcfg();
	afx_msg void OnBnClickedButtonBackdoorEn();
	afx_msg void OnBnClickedButtonBackdoorPin();
	afx_msg void OnBnClickedButtonBackdoorLevel();
};
