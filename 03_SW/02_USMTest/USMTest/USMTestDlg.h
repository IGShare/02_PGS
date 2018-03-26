
// USMTestDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "Comm.h"
#include "afxcmn.h"

typedef struct txPacket{
	int stx;
	char scm_id;
	char data_type;
	unsigned short data_length;
	char buf[1024];
	unsigned short crc16;
}txPacket;

// CUSMTestDlg ��ȭ ����
class CUSMTestDlg : public CDialog
{
// �����Դϴ�.
public:
	CUSMTestDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_USMTEST_DIALOG };

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
	afx_msg LONG OnReceiveData(UINT, LONG);
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ctrlComboPort;
	CComboBox m_ctrlComboBaudRate;
	afx_msg void OnBnClickedButtonDeviceManager();
	afx_msg void OnBnClickedButtonComportOpen();
	afx_msg void OnBnClickedButtonComportClose();
	int m_editSerialNumOfUSM;
	int m_editCtrlIDOfUSM;
	afx_msg void OnBnClickedButtonSetSerialNum();
	int m_editSCMID;
	afx_msg void OnBnClickedButton1();
	int m_editSerialNumOfLGM;
	int m_editCtrlIDOfLGM;
	CComboBox m_ctrlComboUSMOPMode;
	CComboBox m_ctrlComboLGMOPMODE;
	afx_msg void OnBnClickedButtonSetSerialNumLgm();
	afx_msg void OnBnClickedButtonSensingOn();
	afx_msg void OnBnClickedButtonUsmToLgm();
	afx_msg void OnBnClickedButtonSetOpModeUsm();
	afx_msg void OnBnClickedButtonSetOpModeLgm();

	CString m_editPLCReturnVal;
	afx_msg void OnBnClickedButton6();
	BOOL m_radioUSMAutoIncrease;
	BOOL m_radioLGMAutoIncrease;
	afx_msg void OnBnClickedButtonParamUpdate();
	afx_msg void OnBnClickedButtonParamUpdateLgm();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButtonDataReset();
	afx_msg void OnBnClickedButton3();
};
