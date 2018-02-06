#pragma once

class CExternalNetComm
{
public:
	CExternalNetComm(void);
	virtual ~CExternalNetComm(void);
	BOOL InitExternalNetCommManager ();
	void DestroyExternalNetCommManager ();

	BOOL PktRcv ();
public:
	int m_iPort;
	CAsyncSocket *m_sConnectSocket;
	CAsyncSocket *m_sListenSocket;
	CAsyncSocket *m_pSockDummy;
public:
	CString	m_strMessage;
	volatile BOOL m_bConnected;
	volatile BOOL m_bEndThread;
	volatile BOOL m_bSockReady;

	BYTE *m_bufSnd;
	BYTE *m_bufRcv;


	//virtual void OnAccept(int nErrorCode);
};
