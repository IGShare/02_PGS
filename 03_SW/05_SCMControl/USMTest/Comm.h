//Comm.h
//Rs232c를 하기위한 클래스 헤더
// 2001년 3월 26일 (주) 마이크로 로보트  S/W팀 정웅식
//

#ifndef __COMM_H__
#define __COMM_H__

#define COM_MAXBLOCK     65536
#define COM_MAXPORTS        13


// Flow control flags

#define FC_DTRDSR       0x01
#define FC_RTSCTS       0x02
#define FC_XONXOFF      0x04

// ascii definitions

#define ASCII_BEL       0x07
#define ASCII_BS        0x08
#define ASCII_LF        0x0A
#define ASCII_CR        0x0D
#define ASCII_XON       0x11
#define ASCII_XOFF      0x13
#define ASCII_STX		0x02
#define ASCII_ETX		0xFE

#define WM_RECEIVEDATA WM_USER+1024

/////////////////////////////////////////////////////////////////////////////
// CComm window
#define ZERO_MEMORY(s)	::ZeroMemory(&s, sizeof(s))

// flow control
#define FC_DTRDSR	0x01
#define FC_RTSCTS	0x02
#define FC_XONXOFF	0x04
#define	FC_NONE		0x00

#define ASCII_XON	0x11
#define ASCII_XOFF	0x13

// registry stuff
#define CS_REGKEY_SETTINGS     _T("통신환경")
#define CS_REGENTRY_PORT       _T("PORT")
#define CS_REGENTRY_PARITY     _T("PARITY")
#define CS_REGENTRY_BAUD       _T("BAUD")
#define CS_REGENTRY_DATABITS   _T("DATABITS")
#define CS_REGENTRY_STOPBITS   _T("STOPBITS")
#define CS_REGENTRY_FLOW       _T("FLOW")

#pragma  pack(push,1)

typedef struct _TTYSTRUCT
{
   BYTE		byCommPort;  // zero based port - 3 or higher implies TELNET
   BYTE		byXonXoff;
   BYTE		byByteSize;
   BYTE		byFlowCtrl;
   BYTE		byParity;
   BYTE		byStopBits;
   DWORD	dwBaudRate;

} TTYSTRUCT, *LPTTYSTRUCT;

#pragma  pack(pop,1)

// 통신프로토콜 Table
extern BYTE _nFlow[4];

// 통신 데이타 사이즈 테이블
extern int _nDataValues[2];

// 통신 속도 Table
extern int _nBaudRates[12];

// 통신 정지 비트 Table
extern BYTE _nStopBits[2];

class CComm : public CObject
{

   DECLARE_DYNCREATE( CComm )
public:	
	HANDLE      idComDev ;	//컴포트 디바이스 연결 핸들
	BOOL        fConnected;	//컴포트가 연결되면 1로 설정
	BYTE        abIn[ COM_MAXBLOCK + 1] ;	//컴포트에서 들어오는 데이타
	HWND		m_hwnd;	//메세지를 전달할 윈도우 플러그
	BOOL		bTxEmpty;	// TX용 데이터가 모두 송신 되었을 경우 TRUE로 전환된다.

// Construction
public:
	CComm( );
	//컴포트를 열고 연결을 시도한다.
	BOOL OpenCommPort(LPTTYSTRUCT lpTTY);
	//comm 포트를 해제한다.
	BOOL DestroyComm();
	//컴포트에서 데이타를 받는다.
	int  ReadCommBlock( LPSTR data, int len);
	//컴포트에 데이타를 넣는다.
	BOOL WriteCommBlock( LPSTR data, DWORD len);   
	//포트를 연결한다.
	BOOL SetupConnection(LPTTYSTRUCT lpTTY);
	//연결을 해제한다.
	BOOL CloseConnection( );
	//읽은 데이타를 버퍼에 저장한다.
	void SetReadData(LPSTR data, int nLen);
	//메시지를 보낼 윈도우 핸들을 설정한다.
	void SetHwnd(HWND hwnd);
	void EscapeCommFunction(DWORD dwFunc) ;
	

// Attributes
public:   
	OVERLAPPED  osWrite, osRead;		
// Operations
public:	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComm)
	//}}AFX_VIRTUAL

// Implementation
public:
		
	virtual ~CComm();

	// Generated message map functions
//	DECLARE_MESSAGE_MAP()
protected:
};


/////////////////////////////////////////////////////////////////////////////
#endif