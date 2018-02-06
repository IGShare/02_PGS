#pragma once


class CManClNetComm  
{
public:
	CManClNetComm();
	virtual ~CManClNetComm();

	BOOL Connect (LPCTSTR strServAddr, int nPort);
	void Close ();
	__inline BOOL IsConnected ()	{	return m_bConnected;	}

	int SendData (BYTE *bufData, DWORD szData);
	int ReceiveData (BYTE *bufData, DWORD szData);

private:
	CAsyncSocket *m_pSockClient;
	volatile BOOL m_bConnected;
};
