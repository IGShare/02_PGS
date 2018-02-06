
// CCMSTBDTestDlg.h : ��� ����
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

// CCCMSTBDTestDlg ��ȭ ����
class CCCMSTBDTestDlg : public CDialog
{
// �����Դϴ�.
public:
	CCCMSTBDTestDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CCMSTBDTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
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
	// ������ �޽��� �� �Լ�
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
