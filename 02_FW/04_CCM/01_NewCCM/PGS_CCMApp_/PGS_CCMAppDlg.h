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

	DWORD m_idTimer;
	CComm m_commEbd;

	CBitmap m_biBack;
	CBitmap m_biMainSkin;
	CBitmap *m_pbiOldSrcDC;
	CBitmap *m_pBiOldTmpDC;
	CDC m_srcDC, m_tmpDC;

	int m_nOldGreen1F;
	int m_nOldGreen2F;
	int m_bufNOldGrGrp[NUM_EBD_GROUP];

	int m_nOldGreen1B_EBD;
	int m_nOldGreen2B_EBD;
	int m_nOldGreen5B_EBD;
	int m_nOldGreen6B_EBD;

	int m_nOldGreen1SBD_L;
	int m_nOldGreen1SBD_R;
	int m_nOldGreen2SBD_L;
	int m_nOldGreen2SBD_R;
	int m_nOldGreen3SBD_L;
	int m_nOldGreen3SBD_R;
	int m_nOldGreen4SBD_L;
	int m_nOldGreen4SBD_R;
	int m_nOldGreen5SBD_L;
	int m_nOldGreen5SBD_R;
	int m_nOldGreen6SBD_L;
	int m_nOldGreen6SBD_R;

	int m_nOldGreen7SBD_L;
	int m_nOldGreen7SBD_R;
	int m_nOldGreen8SBD_L;
	int m_nOldGreen8SBD_R;
	int m_nOldGreen9SBD_L;
	int m_nOldGreen9SBD_R;
	int m_nOldGreen10SBD_L;
	int m_nOldGreen10SBD_R;
	int m_nOldGreen11SBD_L;
	int m_nOldGreen11SBD_R;
	int m_nOldGreen12SBD_L;
	int m_nOldGreen12SBD_R;

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
	void SendEBoardMessage ();
	void SendSBoardMessage (BYTE TYPE, int DATA);

	BYTE getCheckSum(BYTE * data, int length);

	BOOL ReadDebugDataFromFile ();
	void WriteDebugDataFromFile (ITEM_SCM_DEV_SETTINGS *pISCMDevS);

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
};
