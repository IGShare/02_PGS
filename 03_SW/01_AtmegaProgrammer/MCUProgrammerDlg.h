
// MCUProgrammerDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CMCUProgrammerDlg ��ȭ ����
class CMCUProgrammerDlg : public CDialog
{
// �����Դϴ�.
public:
	CMCUProgrammerDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MCUPROGRAMMER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBnOpenelf();
	afx_msg void OnBnClickedBnScmProgramming();
	afx_msg void OnBnClickedBnDeviceApply();
	int RunMCUProgrammer(CString strPath, CString strCmd, CString strBatchFileName);
	void GetOneLineFromResultFile(wchar_t *strTmp, wchar_t *FileName);

	CString m_edElfFilePath;

	CComboBox m_comDeviceName;
	
	CComboBox m_comToolName;
	CComboBox m_comInterfaceName;
	// CCM :1, SCM:2, USM:3, LGM:4
	BYTE m_edModuleID;
	BYTE m_edRevision;
	// Default value : 0
	BYTE m_edReserved;
	UINT m_edSerialNumber;
	BYTE m_edControlID;


	CComboBox m_comSensingDistance;
	CComboBox m_comADCAmplitude;
	CComboBox m_comADCSensitivity;
	CComboBox m_comTxBurstCount;

	CRichEditCtrl m_RichEditResult;


public:

	CString m_strElfFileName;
	CString m_strElfFilePath;

	CString m_strDeviceName;
	CString m_strToolName;
	CString m_strInterfaceName;

	CString m_strModuleID;
	CString m_strRevision;
	CString m_strReserved;
	CString m_strSerialNumber;
	CString m_strControlID;

	CString m_strSensingDistance;
	CString m_strADCAmplitude;
	CString m_strADCSensitivity;
	CString m_strTxBurstCount;


	CString m_strWorkingELFFolder;
	CString m_strWorkingRootFolder;
	CString m_strCurrentFolder;
	CString m_strRichEditString;

	CString m_strComPort;


	afx_msg void OnBnClickedBnEewrite();

	afx_msg void OnBnClickedBnEereset();
	CString m_edFusesValue;
	afx_msg void OnBnClickedBnFuseRead();
	afx_msg void OnBnClickedBnFuseWrite();
	
	afx_msg void OnBnClickedBnEeread();
	int m_radioAutoIncrease;
	afx_msg void OnBnClickedButtonOneClickProgram();
	CComboBox m_comComport;
};
