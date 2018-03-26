#pragma once


// CComm

class CComm  
{
public:
	void CloseConnect();
	int IsConnect();
	CComm();
	~CComm();
	int ConnectComm(char Port, int BaudRate, int NumberBit, char Parity, char StopBit);
	int Status();
	int Send(BYTE *Buffer, int nBytes);
	int Receive(BYTE *Buffer, DWORD szRcv);

	HANDLE m_Com;
	int m_Connect;
	int m_Status;
};


