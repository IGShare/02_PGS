//Comm.h
//Rs232c�� �ϱ����� Ŭ���� ���
// 2001�� 3�� 26�� (��) ����ũ�� �κ�Ʈ  S/W�� ������
//

#ifndef __COMM_H__
#define __COMM_H__

#define COM_MAXBLOCK     65535
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
#define CS_REGKEY_SETTINGS     _T("���ȯ��")
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

// ����������� Table
extern BYTE _nFlow[4];

// ��� ����Ÿ ������ ���̺�
extern int _nDataValues[2];

// ��� �ӵ� Table
extern int _nBaudRates[12];

// ��� ���� ��Ʈ Table
extern BYTE _nStopBits[2];

class CComm : public CObject
{

   DECLARE_DYNCREATE( CComm )
public:	
	HANDLE      idComDev ;	//����Ʈ ����̽� ���� �ڵ�
	BOOL        fConnected;	//����Ʈ�� ����Ǹ� 1�� ����
	BYTE        abIn[ COM_MAXBLOCK + 1] ;	//����Ʈ���� ������ ����Ÿ
	HWND		m_hwnd;	//�޼����� ������ ������ �÷���
	BOOL		bTxEmpty;	// TX�� �����Ͱ� ��� �۽� �Ǿ��� ��� TRUE�� ��ȯ�ȴ�.

// Construction
public:
	CComm( );
	//����Ʈ�� ���� ������ �õ��Ѵ�.
	BOOL OpenCommPort(LPTTYSTRUCT lpTTY);
	//comm ��Ʈ�� �����Ѵ�.
	BOOL DestroyComm();
	//����Ʈ���� ����Ÿ�� �޴´�.
	int  ReadCommBlock( LPSTR data, int len);
	//����Ʈ�� ����Ÿ�� �ִ´�.
	BOOL WriteCommBlock( LPSTR data, DWORD len);   
	//��Ʈ�� �����Ѵ�.
	BOOL SetupConnection(LPTTYSTRUCT lpTTY);
	//������ �����Ѵ�.
	BOOL CloseConnection( );
	//���� ����Ÿ�� ���ۿ� �����Ѵ�.
	void SetReadData(LPSTR data, int nLen);
	//�޽����� ���� ������ �ڵ��� �����Ѵ�.
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