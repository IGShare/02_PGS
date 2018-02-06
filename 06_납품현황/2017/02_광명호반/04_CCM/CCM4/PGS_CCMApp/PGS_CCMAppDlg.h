// PGS_CCMAppDlg.h : 헤더 파일
//

#pragma once
#include "Comm.h"

class CManNetComm;
class CManSCM_Comm;
class CDlgCCMAppExit;

struct ITEM_USM_DEV_SETTINGS {
	BOOL bUse;
	int nSN;
	BYTE idxOpMode;
	BYTE idxLGM;
	BYTE nParam1;
	BYTE nParam2;
	BYTE nParam3;
	BYTE nParam4;
	BYTE idxGroup1;
	BYTE idxGroup2;
};
struct ITEM_LGM_DEV_SETTINGS {
	BOOL bUse;
	int nSN;
	BYTE idxOpMode;
};
struct ITEM_SCM_DEV_SETTINGS {
	BOOL bUse;
	BOOL bSetOK;

	int numUSM;
	int numLGM;
	ITEM_USM_DEV_SETTINGS bufUSM[MAX_NUM_USM];
	ITEM_LGM_DEV_SETTINGS bufLGM[MAX_NUM_LGM];
};

typedef struct txPacket{
	int stx;
	char type;
	unsigned short data_length;
	char buf[128];
	char check_sum;
	int etx;
}txPacket;

// CPGS_CCMAppDlg 대화 상자
class CPGS_CCMAppDlg : public CDialog
{
// 생성입니다.
public:
	CPGS_CCMAppDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PGS_CCMAPP_DIALOG };

	CDlgCCMAppExit *m_pDlgSG;
	CManNetComm *m_pManNetComm;
	CManSCM_Comm *m_pManSCM_Comm;
	ITEM_SCM_DEV_SETTINGS *m_bufSCM_DevSettings;

	volatile BOOL m_bEndThread;
	BOOL m_bufBAutoInitOK[MAX_NUM_SCM];
	DWORD m_bufTimeAutoInitOK[MAX_NUM_SCM];
	DWORD m_bufNumGetStatFail[MAX_NUM_SCM];
	volatile int m_idxAutoInitDCM;

	volatile BOOL m_bEndThread_CMS_InfoRcv;

	DWORD m_idTimer;
	DWORD m_timeStart;
	CComm m_commEbd1;
	CComm m_commEbd2;
	CComm m_commSbd;
	CComm m_commCMS;

	CBitmap m_biBack;
	CBitmap m_biMainSkin;
	CBitmap *m_pbiOldSrcDC;
	CBitmap *m_pBiOldTmpDC;
	CDC m_srcDC, m_tmpDC;

	int m_bufNOldGrGrp[NUM_EBD_GROUP];

	int m_nOld_EBD2_Green1;
	int m_nOld_EBD2_Green2;
	int m_nOld_EBD2_Green3;
	int m_nOld_EBD2_Green4;
	int m_nOld_EBD2_Green5;
	int m_nOld_EBD2_Green6;

	int m_nOld_EBD1_Green1_1;
	int m_nOld_EBD1_Green1_2;
	int m_nOld_EBD1_Green1_3;

	int m_nOld_EBD1_Green2_L;
	int m_nOld_EBD1_Green2_R;
	int m_nOld_EBD1_Green3_L;
	int m_nOld_EBD1_Green3_R;
	int m_nOld_EBD1_Green4_L;
	int m_nOld_EBD1_Green4_R;
	int m_nOld_EBD1_Green5_L;
	int m_nOld_EBD1_Green5_R;
	int m_nOld_EBD1_Green6_L;
	int m_nOld_EBD1_Green6_R;
	int m_nOld_EBD1_Green7_L;
	int m_nOld_EBD1_Green7_R;
	int m_nOld_EBD1_Green8_L;
	int m_nOld_EBD1_Green8_R;
	int m_nOld_EBD1_Green9_L;
	int m_nOld_EBD1_Green9_R;
	int m_nOld_EBD1_Green10_L;
	int m_nOld_EBD1_Green10_R;
	int m_nOld_EBD1_Green11_L;
	int m_nOld_EBD1_Green11_R;
	int m_nOld_EBD1_Green12_L;
	int m_nOld_EBD1_Green12_R;
	int m_nOld_EBD1_Green13_L;
	int m_nOld_EBD1_Green13_R;
	int m_nOld_EBD1_Green14_L;
	int m_nOld_EBD1_Green14_R;
	int m_nOld_EBD1_Green15_L;
	int m_nOld_EBD1_Green15_R;

	BOOL GetAutoInitStat ();
	BOOL ReqSetLgmAddr (int idxSCM);
	BOOL ReqSetUsmAddr (int idxSCM);
	BOOL ReqSetUsmParam (int idxSCM);
	BOOL ReqSetUsmToLgm (int idxSCM);
	BOOL ReqSensingOn (int idxSCM);
	BOOL ReqSensingOff (int idxSCM);
	BOOL ReqDevStat (int idxSCM);
	BOOL ReqSetOpMode(int idxSCM);

	int AutoInitSCM (int idxSCM);
	void GetDevStatFromSCM (int idxSCM);
	BOOL SendEBoard1Message ();
	BOOL SendEBoard2Message ();
	void SendSBoardMessage (BYTE TYPE, int DATA);

	BYTE getCheckSum(BYTE * data, int length);

	BOOL ReadDebugDataFromFile ();
	void WriteDebugDataFromFile (ITEM_SCM_DEV_SETTINGS *pISCMDevS);
	int m_ComRetrayCnt;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	char strTmp[MAX_PATH];
	int bufClrGreen[MAX_NUM_STR_IN_EBD];
	int bufClrRed[MAX_NUM_STR_IN_EBD];
	int bufClrColor_leftFULL[MAX_NUM_STR_IN_EBD];
	int bufClrColor_rightFULL[MAX_NUM_STR_IN_EBD];
	BYTE sendBuf[128];
};
