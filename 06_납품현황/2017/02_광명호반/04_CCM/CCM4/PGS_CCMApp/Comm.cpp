// cComm.cpp: implementation of the cComm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Comm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CComm::CComm()
{
	m_Connect = FALSE;
	m_Status = 0;
}

CComm::~CComm()
{
	CloseConnect ();
}

int CComm::ConnectComm(char Port,int BaudRate, int NumberBit, char Parity, char StopBit)
{
	COMMTIMEOUTS timeouts;
	DCB dcb;
	wchar_t Def[30];

	m_Status = 0;

	if (Port >= 10)
	{
		swprintf_s (Def, 30, L"\\\\.\\COM%d:", Port);
	}
	else
	{
		swprintf_s (Def, 30, L"COM%d:", Port);
	}
	m_Com = CreateFile (Def, 
		GENERIC_READ |GENERIC_WRITE, 
		FILE_SHARE_READ |FILE_SHARE_WRITE, 
		NULL,
		OPEN_EXISTING, 
		0, 
		NULL);

	if (m_Com == INVALID_HANDLE_VALUE)
	{
		m_Status = 1;
		return m_Status;
	}

//	SetCommMask (m_Com, EV_RXCHAR);	
	SetupComm (m_Com, 4096, 4096);	
	PurgeComm (m_Com, PURGE_TXABORT |PURGE_TXCLEAR |PURGE_RXABORT |PURGE_RXCLEAR);

	timeouts.ReadIntervalTimeout = 0;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;
	timeouts.WriteTotalTimeoutMultiplier = 0;
	timeouts.WriteTotalTimeoutConstant = 0;
	SetCommTimeouts (m_Com, &timeouts);

	dcb.DCBlength = sizeof(DCB);
	GetCommState (m_Com, &dcb);	
	dcb.BaudRate = BaudRate;
	dcb.ByteSize = 8;
	dcb.Parity = 0;
	dcb.StopBits = 0;

	dcb.fBinary = TRUE;				// 바이너리모드, EOF체크 안함
	dcb.fParity = FALSE;				// 패리티 체크의 사용 여부	
	dcb.fOutxCtsFlow = FALSE;			// CTS 출력 흐름제어 사용 여부
	dcb.fOutxDsrFlow = FALSE;			// DSR 출력 흐름제어 사용 여부
	dcb.fDtrControl = DTR_CONTROL_DISABLE;	// DTR 흐름제어 형태
	dcb.fDsrSensitivity = FALSE;			// DSR 감도
	dcb.fTXContinueOnXoff = FALSE;		// XOFF continues Tx 
	dcb.fOutX = FALSE;				// XON/XOFF 출력 흐름제어 사용 여부
	dcb.fInX = FALSE;				// XON/XOFF 입력 흐름제어 사용 여부
	dcb.fErrorChar = FALSE;			// Disable error replacement 
	dcb.fNull = FALSE;				// Disable null stripping 
	dcb.fRtsControl = RTS_CONTROL_DISABLE;	// RTS 흐름제어
	dcb.fAbortOnError = TRUE;			// 에러 무시


	if (!SetCommState (m_Com, &dcb))	
	{
		m_Status = 3;
		return m_Status;
	}

	m_Connect = TRUE;
	return m_Status;
}

void CComm::CloseConnect()
{
	if (m_Connect == TRUE)
	{
		m_Connect = FALSE;
//		SetCommMask (m_Com, 0);
		PurgeComm (m_Com, PURGE_TXABORT |PURGE_TXCLEAR |PURGE_RXABORT |PURGE_RXCLEAR);
		CloseHandle (m_Com);
	}
}

int CComm::Status(void)
{
	return m_Status;
}

int CComm::Send (BYTE *Buffer, int nBytes)
{
	if (m_Connect == FALSE)
	{
		return 0;
	}

	DWORD dwWritten, dwErrorFlags;
	COMSTAT	comstat;

	BYTE bufTmp[1024];
	memcpy (bufTmp, Buffer, nBytes);

	if (!WriteFile (m_Com, Buffer, nBytes, &dwWritten, 0))
	{
		ClearCommError (m_Com, &dwErrorFlags, &comstat);
	}

	Sleep (30);

	return dwWritten;
}

int CComm::Receive (BYTE *Buffer, DWORD szRcv)
{
	if (m_Connect == FALSE)
	{
		return 0;
	}

	DWORD dwRead, dwErrorFlags;
	COMSTAT comstat;
	ClearCommError (m_Com, &dwErrorFlags, &comstat);
	dwRead = comstat.cbInQue;

	if (dwRead > szRcv)
	{
		dwRead = szRcv;
	}

	if (dwRead > 0)
	{
		if (!ReadFile (m_Com, Buffer, dwRead, &dwRead, 0))
		{
			ClearCommError (m_Com, &dwErrorFlags, &comstat);
		}
		else 
		{
		}
	}
	return dwRead;
}

int CComm::IsConnect ()
{
	return m_Connect;
}
