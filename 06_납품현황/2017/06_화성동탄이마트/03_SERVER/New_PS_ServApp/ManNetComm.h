#pragma once

enum {
	IDX_NC_ERR_NO_ERROR,
	IDX_NC_ERR_RCV_INVALID,
	IDX_NC_ERR_RCV_TIMEOUT,
	IDX_NC_ERR_SOCK_ERR,
	IDX_NC_ERR_SOCK_CLOSED,
};

struct INFO_IN_PROC_NET_REQ {
	int idxDT_Req;
	int nDevID_SCM;
	int numItem;

	ITEM_REQM_SET_ADDR *pIReqM_SET_ADDR;
	ITEM_REQM_SET_OP_MODE *pIReqM_SET_OP_MODE;
	ITEM_REQM_SET_PARAM *pIReqM_SET_PARAM;
	ITEM_REQM_SET_USM2LGM *pIReqM_SET_USM2LGM;
};

struct INFO_OUT_PROC_NET_REQ {
	int idxNC_Err;
	BYTE statSCM;
	ITEM_RESM_USM_LGM_STAT *pIResM_USM_LGM_STAT;
};

class CManNetComm
{
public:
	BOOL InitNetCommManager ();
	void DestroyNetCommManager ();

	BOOL IsNetCommReady ();
	BOOL IsClientConnected ();

	BOOL ProcessNetReq (INFO_IN_PROC_NET_REQ *pIIn, INFO_OUT_PROC_NET_REQ *pIOut);
		// "TRUE" when receive "ACK or RES_XXX" from SCM (including "SCM data mismatch")
	void SetNetCommSettings (INFO_NET_COMM_SETTINGS *pINCS);

public:
	CManNetComm(int nDevID_CCM, INFO_NET_COMM_SETTINGS *pINCS);
	~CManNetComm(void);

	friend UINT TH_NetCommProc (LPVOID pParam);

	BOOL PktSnd ();
	BOOL PktRcv (DWORD timeRcvTimeout, BOOL &bNAck, BOOL &bRcvTimeout);

	void LogPrintSocketError (int idxFunc, int idxErrCode);

	volatile BOOL m_bEndThread;
	volatile BOOL m_bSockReady;
	volatile BOOL m_bConnected;
	volatile int m_nDevID_CCM;

	CAsyncSocket *m_pSockListen;
	CAsyncSocket *m_pSockComm;
	CAsyncSocket *m_pSockDummy;

	int m_idxReqCmd;
	volatile BOOL m_bCommOk;
	HANDLE m_hEvtWaitNetComm;
	BYTE *m_bufSnd;
	BYTE *m_bufRcv;
	int m_idxLastNC_Err;
	int m_posRcvStart;

	INFO_NET_COMM_SETTINGS m_iNCS;
	CCriticalSection m_crtAccSock;
};
