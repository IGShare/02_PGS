
// FWDownLoaderDlg.h : ��� ����
//

#pragma once
#include "Comm.h"
#include "afxwin.h"


// CFWDownLoaderDlg ��ȭ ����
class CFWDownLoaderDlg : public CDialog
{
// �����Դϴ�.
public:
	CFWDownLoaderDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_FWDOWNLOADER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

	// CComm Ŭ�������� ������ �޽����� �޾Ƽ� ó���ϱ� ���� ���� �Լ� ����
	afx_msg LONG OnReceiveData(UINT, LONG);
// �����Դϴ�.
protected:
	HICON m_hIcon;

	CComm m_Comm;

	int	m_nBaudRate;
	int	m_nComPort;
	int m_nFlowControl;
	int m_nStopBits;
	int m_nDataBits;
	int m_nParity;

	// ������ �޽��� �� �Լ�
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
