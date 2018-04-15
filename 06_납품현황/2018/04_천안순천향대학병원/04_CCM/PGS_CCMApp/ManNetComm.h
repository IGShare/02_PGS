#pragma once

#define SZ_STR_SERV_ADDR			1024
class CManSCM_Comm;

class CManNetComm
{
public:
	CManNetComm(ITEM_RESM_USM_LGM_STAT *pBufOldStatUSM_LGM = NULL);
	~CManNetComm(void);

	void ReqConnect (int nDevID_CCM, const wchar_t *strServAddr);
	void SetSCM_Comm (CManSCM_Comm *pManSCM_Comm);
	BOOL IsConnected ();
	void EnableManNetComm (BOOL bEnable);

	friend UINT TH_NetCommProc (LPVOID pParam);

	BOOL NetCommRcv ();
	BOOL ProcRcvPkt ();
	BOOL NetCommRcvAndSkipProc ();

	void LogPrintSocketError (int idxFunc, int idxErrCode);
	void UpdateSCM_Stat (int nDevID_SCM, int idxReq, BOOL bAck);
	__inline void ResetSockComm ();

	CAsyncSocket *m_pSockComm;
	volatile BOOL m_bEndThread;
	volatile BOOL m_bConnected;
	volatile BOOL m_bEnable;

	volatile int m_CentralMonitorGreenCnt;

	BYTE *m_bufRcv;
	BYTE *m_bufSnd;
	volatile int m_posPkt;
	volatile int m_posRcv;

	int m_nDevID_CCM;
	wchar_t m_strServAddr[SZ_STR_SERV_ADDR];

	CManSCM_Comm *m_pManSCM_Comm;
	ITEM_RESM_USM_LGM_STAT *m_bufStatUSM_LGM;
	CCriticalSection m_crtAccStatUSM_LGM;
};

