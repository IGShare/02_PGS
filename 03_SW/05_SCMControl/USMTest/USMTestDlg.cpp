
// USMTestDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "USMTest.h"
#include "USMTestDlg.h"
#include "crc16.h"
#include "define.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CUSMTestDlg ��ȭ ����




CUSMTestDlg::CUSMTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUSMTestDlg::IDD, pParent)
	, m_editSerialNumOfUSM(1)
	, m_editCtrlIDOfUSM(1)
	, m_editSCMID(1)
	, m_editSerialNumOfLGM(1)
	, m_editCtrlIDOfLGM(129)
	, m_editPLCReturnVal(_T(""))
	, m_radioUSMAutoIncrease(FALSE)
	, m_radioLGMAutoIncrease(FALSE)
	, m_systemDataReadF(FALSE)
	, m_reditStatus(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUSMTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PORT, m_ctrlComboPort);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_ctrlComboBaudRate);
	DDX_Text(pDX, IDC_EDIT_SERIAL_NUM_USM, m_editSerialNumOfUSM);
	DDX_Text(pDX, IDC_EDIT_CTRL_NUM_USM, m_editCtrlIDOfUSM);
	DDX_Text(pDX, IDC_EDIT_SCM_ID, m_editSCMID);
	DDV_MinMaxInt(pDX, m_editSCMID, 1, 15);
	DDX_Text(pDX, IDC_EDIT_SERIAL_NUM_LGM, m_editSerialNumOfLGM);
	DDX_Text(pDX, IDC_EDIT_CTRL_NUM_LGM, m_editCtrlIDOfLGM);
	DDX_Control(pDX, IDC_COMBO_USM_OP_MODE, m_ctrlComboUSMOPMode);
	DDX_Control(pDX, IDC_COMBO_LGM_OP_MODE, m_ctrlComboLGMOPMODE);
	DDX_Text(pDX, IDC_EDIT_PLC_RETURN_VAL, m_editPLCReturnVal);
	DDX_Radio(pDX, IDC_RADIO_AUTO_INCREASE_USM_1, m_radioUSMAutoIncrease);
	DDX_Radio(pDX, IDC_RADIO_AUTO_INCREASE_LGM_1, m_radioLGMAutoIncrease);
	DDX_Text(pDX, IDC_RICHEDIT21, m_reditStatus);
}

BEGIN_MESSAGE_MAP(CUSMTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_RECEIVEDATA, OnReceiveData)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_MANAGER, &CUSMTestDlg::OnBnClickedButtonDeviceManager)
		ON_BN_CLICKED(IDC_BUTTON_COMPORT_OPEN, &CUSMTestDlg::OnBnClickedButtonComportOpen)
		ON_BN_CLICKED(IDC_BUTTON_COMPORT_CLOSE, &CUSMTestDlg::OnBnClickedButtonComportClose)
		ON_BN_CLICKED(IDC_BUTTON_SET_SERIAL_NUM, &CUSMTestDlg::OnBnClickedButtonSetSerialNum)
		ON_BN_CLICKED(IDC_BUTTON1, &CUSMTestDlg::OnBnClickedButton1)
		ON_BN_CLICKED(IDC_BUTTON_SET_SERIAL_NUM_LGM, &CUSMTestDlg::OnBnClickedButtonSetSerialNumLgm)
		ON_BN_CLICKED(IDC_BUTTON_SENSING_ON, &CUSMTestDlg::OnBnClickedButtonSensingOn)
		ON_BN_CLICKED(IDC_BUTTON_USM_TO_LGM, &CUSMTestDlg::OnBnClickedButtonUsmToLgm)
		ON_BN_CLICKED(IDC_BUTTON_SET_OP_MODE_USM, &CUSMTestDlg::OnBnClickedButtonSetOpModeUsm)
		ON_BN_CLICKED(IDC_BUTTON_SET_OP_MODE_LGM, &CUSMTestDlg::OnBnClickedButtonSetOpModeLgm)
		ON_BN_CLICKED(IDC_BUTTON6, &CUSMTestDlg::OnBnClickedButton6)
		ON_BN_CLICKED(IDC_BUTTON_PARAM_UPDATE, &CUSMTestDlg::OnBnClickedButtonParamUpdate)
		ON_BN_CLICKED(IDC_BUTTON_PARAM_UPDATE_LGM, &CUSMTestDlg::OnBnClickedButtonParamUpdateLgm)
		ON_BN_CLICKED(IDC_BUTTON2, &CUSMTestDlg::OnBnClickedButton2)
		ON_BN_CLICKED(IDC_BUTTON_DATA_RESET, &CUSMTestDlg::OnBnClickedButtonDataReset)
		ON_BN_CLICKED(IDC_BUTTON3, &CUSMTestDlg::OnBnClickedButton3)
		ON_BN_CLICKED(IDC_BUTTON_RD_SYS_INFO, &CUSMTestDlg::OnBnClickedButtonRdSysInfo)
END_MESSAGE_MAP()


// CUSMTestDlg �޽��� ó����

BOOL CUSMTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_Comm.SetHwnd(this->m_hWnd); // CComm Ŭ�������� ���� �޽����� ����� �� �ֵ��� window �ڵ��� �����Ѵ�.

	m_nComPort = 0; // COM 1
	m_nParity = 0; // no parity bit
	m_nBaudRate = 0; // 1200 baud rates
	m_nDataBits = 1; //8bits
	m_nStopBits = 0; //one stop ibt
	m_nFlowControl = 0; // No control

	//Comport �ʱ�ȭ
	CString portName, boardId;
	for(int i=1; i<30; i++){
		portName.Format(_T("COM%d"),i);
		m_ctrlComboPort.AddString(portName);
	}

	m_ctrlComboPort.SetCurSel(6);
	m_ctrlComboBaudRate.SetCurSel(6);

	m_ctrlComboUSMOPMode.SetCurSel(0);
	m_ctrlComboLGMOPMODE.SetCurSel(0);

	//CheckDlgButton(IDC_CHECK_AUTO_INCREASE_USM_1, TRUE);
	//CheckDlgButton(IDC_CHECK_AUTO_INCREASE_LGM_1, TRUE);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CUSMTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CUSMTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);


	}
	else
	{
		//CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ
		//CDC MemDC;
		//BITMAP bmpInfo;
		//MemDC.CreateCompatibleDC(&dc);
		//CBitmap bmp;
		//CBitmap *pOldBmp = NULL;
		//bmp.LoadBitmap(IDB_BI_SUCCESS);
		//bmp.GetBitmap(&bmpInfo);
		//pOldBmp = MemDC.SelectObject(&bmp);
		//dc.BitBlt(200, 200, bmpInfo.bmWidth, bmpInfo.bmHeight, &MemDC, 0, 0, SRCCOPY);
		//MemDC.SelectObject(pOldBmp);


		//CFont Font;
		//CFont *pOldFont;

		//LOGFONT lf;
		//::ZeroMemory(&lf, sizeof(lf));
		//wsprintf(lf.lfFaceName, TEXT("%s"), TEXT("Arial"));

		//lf.lfHeight = 30;
		//Font.CreateFontIndirect(&lf);
		//pOldFont = dc.SelectObject(&Font);
		//dc.TextOut(260, 200, TEXT("SUCCESS !!"));
		//dc.SelectObject(pOldFont);
		//Font.DeleteObject();


		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CUSMTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

TTYSTRUCT CUSMTestDlg::Int2TTY()
{
	//���� �ڵ��� �κ�(3)
	//COM port �� �������� �Ķ���� �� ����
	TTYSTRUCT tty;
	ZERO_MEMORY(tty);

	tty.byCommPort = (BYTE)m_nComPort + 1;
	tty.byXonXoff = FALSE;
	tty.byByteSize = (BYTE)_nDataValues[m_nDataBits];
	tty.byFlowCtrl = (BYTE)_nFlow[m_nFlowControl];
	tty.byParity = (BYTE)m_nParity;
	tty.byStopBits = (BYTE)_nStopBits[m_nStopBits];
	tty.dwBaudRate = (DWORD)_nBaudRates[m_nBaudRate];

	return tty;
}
LONG CUSMTestDlg::OnReceiveData(UINT WParam, LONG a)
{
	int i;
	int nLen = WParam;
	int num = 1;
	CString str;
	static char sData[4096] = {0,};
	char pData[4096] = {0, };
	int dataLength = 0;
	int low=0, high=0;
	static int index = 0;

	//UpdateData(TRUE);
	BYTE ch;
	int temp;
	// ���ŵ� �����͸� ���ڷ� ����Ѵ�.
	for (i=0; i<nLen; i++)
	{
		ch=m_Comm.abIn[i];
		str.Format("%02x", ch);
		//m_editReport += str;
		sData[index] = ch;
		index++;
	}

	int idxSTX = 0;
	int stxCnt = 0;
	int stxOffset = 0;

	int scmID, pType, pLength;
	unsigned short pCRC=0, pCRC_high=0, pCRC_low=0, dCRC;

	if(index>8){
		while(1){
			if(sData[idxSTX] == (m_editSCMID & 0xff)){
				if((sData[idxSTX-1] == 0x00) & (sData[idxSTX-2] == 0x00) & (sData[idxSTX-3] == 0x00)){
					stxCnt = idxSTX;
					break;
				}
				else{
					index = 0;
					return 0;
				}
					

			}
			else{
				idxSTX++;
			}
			if(idxSTX > index)
			{
				SetDlgItemText(IDC_STATIC_STATUS_MESSAGE, _T("STX Error"));
				index = 0;
				return 0;
			}
		}
		scmID = sData[idxSTX++];
		pType = sData[idxSTX++];
		pLength = (sData[idxSTX]<<8) | sData[idxSTX+1];
		idxSTX++;idxSTX++;

		if(stxCnt+4+pLength+2 > index) return 0;
		if(pLength > 0)
		{
			memcpy(pData, &sData[idxSTX], sizeof(char) * pLength);
			idxSTX +=pLength; 

			pCRC = (sData[idxSTX]&0x00ff) << 8 | sData[idxSTX+1]&0x00ff;
			dCRC = crcsum((unsigned char *)(sData+stxCnt), pLength+4, CRC_INIT);
			if(pCRC != dCRC)
			{
				SetDlgItemText(IDC_STATIC_STATUS_MESSAGE, _T("CRC Error"));
				index = 0;
				return 0;
			}
			else{
				SetDlgItemText(IDC_STATIC_STATUS_MESSAGE, _T("ACK SUCCESS"));
			}

			int tmp_high, tmp_low;
			CString sHigh_Low;

			m_editPLCReturnVal.Empty();
			
			for(int i=1; i<pLength; i++)
			{
				tmp_high = (pData[i] & 0xF0)>>4;
				tmp_low = (pData[i] & 0x0F);

				m_usmINFO[2*(i-1)].status =  tmp_high;
				m_usmINFO[2*(i-1)+1].status =  tmp_low;
				sHigh_Low.Format(_T("%02x %02x "), tmp_high, tmp_low);
				m_editPLCReturnVal += sHigh_Low;
			}

			UpdateData(false);


		}
		else if( pLength == 0)
		{
			pCRC = (sData[idxSTX]&0x00ff) << 8 | sData[idxSTX+1]&0x00ff;
			dCRC = crcsum((unsigned char *)(sData+stxCnt), pLength+4, CRC_INIT);
			if(pCRC != dCRC)
			{
				SetDlgItemText(IDC_STATIC_STATUS_MESSAGE, _T("CRC Error"));
				index = 0;
				return 0;
			}
			else{
				SetDlgItemText(IDC_STATIC_STATUS_MESSAGE, _T("ACK SUCCESS"));
			}
		}
		else return 0;


		index = 0;

	}
	
	//m_editReport += _T("\r\n");
	//UpdateData(false);
	return 0;

}
void CUSMTestDlg::OnBnClickedButtonDeviceManager()
{
	system("hdwwiz.cpl");
}

void CUSMTestDlg::OnBnClickedButtonComportOpen()
{
	UpdateData(TRUE);

	m_nComPort = m_ctrlComboPort.GetCurSel();
	m_nBaudRate = m_ctrlComboBaudRate.GetCurSel();

	if(m_Comm.OpenCommPort(&Int2TTY()) != TRUE)
	{
		SetDlgItemText(IDC_STATIC_STATUS_MESSAGE, _T("COM Port Open Fail."));
		UpdateData(FALSE);

		return;
	}
	SetDlgItemText(IDC_STATIC_STATUS_MESSAGE, _T("COM Port Open Success."));
	m_isComPortOpen = 1;
	UpdateData(FALSE);
}

void CUSMTestDlg::OnBnClickedButtonComportClose()
{
	m_Comm.CloseConnection();
	SetDlgItemText(IDC_STATIC_STATUS_MESSAGE, _T("COM Port Closed."));
	m_isComPortOpen = 0;
}

void CUSMTestDlg::OnBnClickedButtonSetSerialNum()
{
	UpdateData(TRUE);

	int nUsmCnt;
	int SCMID = m_editSCMID;
	unsigned char	sendData[INFO_MAX_RX_TX_PACKET_SIZE] = {0,};

	if(!m_systemDataReadF){
		switch(m_radioUSMAutoIncrease){
			case 0 : nUsmCnt = 1 +1; break;
			case 1 : nUsmCnt = 8 +2; break;
			case 2 : nUsmCnt = 16+2; break;
		}
		int usmInfo[18][3] = {
			 { 1, 1,     129}
			,{ 2, 50000, 130}
			,{ 3, 50001, 130}
			,{ 4, 50002, 130}
			,{ 5, 50002, 130}
			,{ 6, 50002, 130}
			,{ 7, 50002, 130}
			,{ 8, 50002, 130}
			,{ 9, 50002, 130}
			,{10, 50002, 130}
			,{11, 50002, 130}
			,{12, 50002, 130}
			,{13, 50002, 130}
			,{14, 50002, 130}
			,{15, 50002, 130}
			,{16, 50002, 130}
			,{17, 50002, 130}
			,{18, 50002, 130}
		};


		if(nUsmCnt == 2){
			for(int i=0; i<nUsmCnt-1; i++){
				usmInfo[i][0] = m_editCtrlIDOfUSM+i;
				usmInfo[i][1] = m_editSerialNumOfUSM+i;
			}
		}
		else{
			for(int i=0; i<nUsmCnt-2; i++){
				usmInfo[i][0] = m_editCtrlIDOfUSM+i;
				usmInfo[i][1] = m_editSerialNumOfUSM+i;
			}
		}
	

		memset(sendData, 0, sizeof(sendData));

		for(int i=0; i<nUsmCnt; i++)
		{
			int tmp;
			tmp = usmInfo[i][0];
			sendData[7+INFO_SET_USM_ADDR_UNIT_SIZE*i] = tmp & 0xFF;
			tmp = usmInfo[i][1];
			sendData[7+INFO_SET_USM_ADDR_UNIT_SIZE*i+1] = (unsigned char)((tmp>>16) & 0xFF);
			sendData[7+INFO_SET_USM_ADDR_UNIT_SIZE*i+2] = (unsigned char)((tmp>>8) & 0xFF);
			sendData[7+INFO_SET_USM_ADDR_UNIT_SIZE*i+3] = (unsigned char)((tmp) & 0xFF);

		}
	}
	else{
		nUsmCnt = m_usmCnt;
		memset(sendData, 0, sizeof(sendData));
		for(int i=0; i<m_usmCnt; i++)
		{
			int tmp;
			tmp = m_usmINFO[i].cID;
			sendData[7+INFO_SET_USM_ADDR_UNIT_SIZE*i] = tmp & 0xFF;
			tmp = m_usmINFO[i].sID;
			sendData[7+INFO_SET_USM_ADDR_UNIT_SIZE*i+1] = (unsigned char)((tmp>>16) & 0xFF);
			sendData[7+INFO_SET_USM_ADDR_UNIT_SIZE*i+2] = (unsigned char)((tmp>>8) & 0xFF);
			sendData[7+INFO_SET_USM_ADDR_UNIT_SIZE*i+3] = (unsigned char)((tmp) & 0xFF);
		}
	}

	txPacket packet;
	packet.stx = 0;
	packet.scm_id = SCMID;
	packet.data_type = IDX_DT_SET_USM_ADDRESS;
	packet.data_length = nUsmCnt*INFO_SET_USM_ADDR_UNIT_SIZE;

	sendData[0] = (packet.stx >> 16	) &0xFF;
	sendData[1] = (packet.stx >> 8	) &0xFF;
	sendData[2] = (packet.stx		) &0xFF;

	sendData[3] = (packet.scm_id		) &0xFF;
	sendData[4] = (packet.data_type		) &0xFF;
	sendData[5] = (packet.data_length>>8) &0xFF;
	sendData[6] = (packet.data_length	) &0xFF;

	packet.crc16 = crcsum((unsigned char *)(sendData+3), packet.data_length+4, CRC_INIT);

	sendData[packet.data_length+7] = (packet.crc16 >> 8	) &0xFF;
	sendData[packet.data_length+8] = (packet.crc16		) &0xFF;

	m_Comm.WriteCommBlock((char*)sendData,packet.data_length+9);
}

void CUSMTestDlg::OnBnClickedButton1()
{
	UpdateData(true);
}

void CUSMTestDlg::OnBnClickedButtonSetSerialNumLgm()
{
	UpdateData(TRUE);

	int SCMID = m_editSCMID;
	int nLgmCnt;
	unsigned char	sendData[INFO_MAX_RX_TX_PACKET_SIZE] = {0,};

	if(!m_systemDataReadF){
		switch(m_radioLGMAutoIncrease){
			case 0 : nLgmCnt = 1 +1; break;
			case 1 : nLgmCnt = 8 +2; break;
			case 2 : nLgmCnt = 16+2; break;
		}
		int usmInfo[12][3] = {
			 { 1, 1,     129}
			,{ 2, 50000, 130}
			,{ 3, 50001, 131}
			,{ 4, 50002, 132}
			,{ 5, 50002, 133}
			,{ 6, 50002, 134}
			,{ 7, 50002, 135}
			,{ 8, 50002, 136}
			,{ 9, 50002, 137}
			,{10, 50002, 138}
			,{11, 50002, 139}
			,{12, 50002, 130}
		};
		int lgmInfo[12][2] = {
			 {129, 70000}
			,{130, 70001}
			,{131, 70002}
			,{132, 70003}
			,{133, 70004}
			,{134, 70005}
			,{135, 70006}
			,{136, 70007}
			,{137, 70008}
			,{138, 70009}
			,{139, 70010}
			,{140, 70011}
		};

		for(int i=0; i<nLgmCnt; i++){
			lgmInfo[i][0] = m_editCtrlIDOfLGM+i;
			lgmInfo[i][1] = m_editSerialNumOfLGM+i;
		}

		memset(sendData, 0, sizeof(sendData));

		for(int i=0; i<nLgmCnt; i++)
		{
			int tmp;
			tmp = lgmInfo[i][0];
			sendData[7+INFO_SET_LGM_ADDR_UNIT_SIZE*i] = tmp & 0xFF;
			tmp = lgmInfo[i][1];
			sendData[7+INFO_SET_LGM_ADDR_UNIT_SIZE*i+1] = (unsigned char)((tmp>>16) & 0xFF);
			sendData[7+INFO_SET_LGM_ADDR_UNIT_SIZE*i+2] = (unsigned char)((tmp>>8) & 0xFF);
			sendData[7+INFO_SET_LGM_ADDR_UNIT_SIZE*i+3] = (unsigned char)((tmp) & 0xFF);

		}
	} // [E] if(!m_systemDataReadF){
	else{
		nLgmCnt = m_lgmCnt;

		memset(sendData, 0, sizeof(sendData));

		for(int i=0; i<m_lgmCnt; i++)
		{
			int tmp;
			tmp = m_lgmINFO[i].cID;
			sendData[7+INFO_SET_LGM_ADDR_UNIT_SIZE*i] = tmp & 0xFF;
			tmp = m_lgmINFO[i].sID;
			sendData[7+INFO_SET_LGM_ADDR_UNIT_SIZE*i+1] = (unsigned char)((tmp>>16) & 0xFF);
			sendData[7+INFO_SET_LGM_ADDR_UNIT_SIZE*i+2] = (unsigned char)((tmp>>8) & 0xFF);
			sendData[7+INFO_SET_LGM_ADDR_UNIT_SIZE*i+3] = (unsigned char)((tmp) & 0xFF);

		}
	}//[E] else

	txPacket packet;
	packet.stx = 0;
	packet.scm_id = SCMID;
	packet.data_type = IDX_DT_SET_LGM_ADDRESS;
	packet.data_length = nLgmCnt*INFO_SET_LGM_ADDR_UNIT_SIZE;

	sendData[0] = (packet.stx >> 16	) &0xFF;
	sendData[1] = (packet.stx >> 8	) &0xFF;
	sendData[2] = (packet.stx		) &0xFF;

	sendData[3] = (packet.scm_id		) &0xFF;
	sendData[4] = (packet.data_type		) &0xFF;
	sendData[5] = (packet.data_length>>8) &0xFF;
	sendData[6] = (packet.data_length	) &0xFF;

	packet.crc16 = crcsum((unsigned char *)(sendData+3), packet.data_length+4, CRC_INIT);

	sendData[packet.data_length+7] = (packet.crc16 >> 8	) &0xFF;
	sendData[packet.data_length+8] = (packet.crc16		) &0xFF;

	m_Comm.WriteCommBlock((char*)sendData,packet.data_length+9);
}

void CUSMTestDlg::OnBnClickedButtonSensingOn()
{
	int SCMID = m_editSCMID;

	unsigned char	sendData[INFO_MAX_RX_TX_PACKET_SIZE];
	for(int i=0; i<INFO_MAX_RX_TX_PACKET_SIZE; i++)
	{
		sendData[i]= 0;
	}

	txPacket packet;
	packet.stx = 0;
	packet.scm_id = SCMID;
	packet.data_type = IDX_DT_SENSING_ON;
	packet.data_length = INFO_SET_SENSING_ON_UNIT_SIZE;

	sendData[0] = (packet.stx >> 16	) &0xFF;
	sendData[1] = (packet.stx >> 8	) &0xFF;
	sendData[2] = (packet.stx		) &0xFF;

	sendData[3] = (packet.scm_id		) &0xFF;
	sendData[4] = (packet.data_type		) &0xFF;
	sendData[5] = (packet.data_length>>8) &0xFF;
	sendData[6] = (packet.data_length	) &0xFF;

	packet.crc16 = crcsum((unsigned char *)(sendData+3), packet.data_length+4, CRC_INIT);

	sendData[packet.data_length+7] = (packet.crc16 >> 8	) &0xFF;
	sendData[packet.data_length+8] = (packet.crc16		) &0xFF;

	m_Comm.WriteCommBlock((char*)sendData,packet.data_length+9);
	//m_SerialPort.WritePort((unsigned char*)sendData, packet.data_length+9);
}

void CUSMTestDlg::OnBnClickedButtonUsmToLgm()
{
	int nUsmCnt;
	int SCMID = m_editSCMID;
	unsigned char	sendData[INFO_MAX_RX_TX_PACKET_SIZE];

	if(!m_systemDataReadF){

		switch(m_radioUSMAutoIncrease){
			case 0 : nUsmCnt = 1 +1; break;
			case 1 : nUsmCnt = 8 +2; break;
			case 2 : nUsmCnt = 16+2; break;
		}

		
		int usmInfo[18][3] = {
			 { 1, 1,     129}
			,{ 2, 50000, 130}
			,{ 3, 50001, 131}
			,{ 4, 50002, 132}
			,{ 5, 50002, 133}
			,{ 6, 50002, 134}
			,{ 7, 50002, 135}
			,{ 8, 50002, 136}
			,{ 9, 50002, 137}
			,{10, 50002, 138}
			,{11, 50002, 139}
			,{12, 50002, 140}
			,{13, 50002, 141}
			,{14, 50002, 142}
			,{15, 50002, 143}
			,{16, 50002, 144}
			,{17, 50002, 145}
			,{18, 50002, 146}
		};
		int lgmInfo[12][2] = {
			 {129, 70000}
			,{130, 70001}
			,{131, 70002}
			,{132, 70003}
			,{133, 70004}
			,{134, 70005}
			,{135, 70006}
			,{136, 70007}
			,{137, 70008}
			,{138, 70009}
			,{139, 70010}
			,{140, 70011}
		};


		
		memset(sendData, 0, sizeof(sendData));

		for(int i=0; i<nUsmCnt; i++)
		{
			int tmp;
			tmp = usmInfo[i][0];
			sendData[7+INFO_SET_USM_TO_LGM_UNIT_SIZE*i] = tmp & 0xFF;
			tmp = usmInfo[i][2]; // USM to LGM
			sendData[7+INFO_SET_USM_TO_LGM_UNIT_SIZE*i+1] = tmp & 0xFF;
		}
	}// [E] if(!m_systemDataReadF){
	else{
		nUsmCnt = m_usmCnt;

		memset(sendData, 0, sizeof(sendData));

		for(int i=0; i<nUsmCnt; i++)
		{
			int tmp;
			tmp = m_usmINFO[i].cID;
			sendData[7+INFO_SET_USM_TO_LGM_UNIT_SIZE*i] = tmp & 0xFF;
			tmp = m_usmINFO[i].uTol; // USM to LGM
			sendData[7+INFO_SET_USM_TO_LGM_UNIT_SIZE*i+1] = tmp & 0xFF;
		}
	} //[E] else

	txPacket packet;
	packet.stx = 0;
	packet.scm_id = SCMID;
	packet.data_type = IDX_DT_SET_USM_TO_LGM;
	packet.data_length = nUsmCnt*INFO_SET_USM_TO_LGM_UNIT_SIZE;

	sendData[0] = (packet.stx >> 16	) &0xFF;
	sendData[1] = (packet.stx >> 8	) &0xFF;
	sendData[2] = (packet.stx		) &0xFF;

	sendData[3] = (packet.scm_id		) &0xFF;
	sendData[4] = (packet.data_type		) &0xFF;
	sendData[5] = (packet.data_length>>8) &0xFF;
	sendData[6] = (packet.data_length	) &0xFF;

	packet.crc16 = crcsum((unsigned char *)(sendData+3), packet.data_length+4, CRC_INIT);

	sendData[packet.data_length+7] = (packet.crc16 >> 8	) &0xFF;
	sendData[packet.data_length+8] = (packet.crc16		) &0xFF;

	m_Comm.WriteCommBlock((char*)sendData,packet.data_length+9);
	//m_SerialPort.WritePort((unsigned char*)sendData, packet.data_length+9);
}

void CUSMTestDlg::OnBnClickedButtonSetOpModeUsm()
{
	UpdateData(TRUE);

	int SCMID = m_editSCMID;
	int usmInfo[2][4] = {
		 {1, 1, 0, 129}
		,{2, 50000, 0, 130}
		//,{3, 50001, 130}
		//,{4, 50002, 130}
	
	};
	int lgmInfo[2][3] = {
		 {129, 70000, 0}
		,{130, 70001, 0}
	};

	int opmode;

	switch(m_ctrlComboUSMOPMode.GetCurSel())
	{
		case 0:opmode = 8;break;
		case 1:opmode = 3;break;
		case 2:opmode = 4;break;
		case 3:opmode = 5;break;
		case 4:opmode = 6;break;
	}

	unsigned char	sendData[INFO_MAX_RX_TX_PACKET_SIZE];
	for(int i=0; i<INFO_MAX_RX_TX_PACKET_SIZE; i++)
	{
		sendData[i]= 0;
	}

	for(int i=0; i<2; i++)
	{
		int tmp;
		tmp = usmInfo[i][0];
		sendData[7+INFO_SET_USM_TO_LGM_UNIT_SIZE*i] = tmp & 0xFF;
		tmp = opmode; // USM OP MODE
		sendData[7+INFO_SET_USM_TO_LGM_UNIT_SIZE*i+1] = tmp & 0xFF;

	}

	txPacket packet;
	packet.stx = 0;
	packet.scm_id = SCMID;
	packet.data_type = IDX_DT_SET_USM_OP_MODE;
	packet.data_length = 2*INFO_SET_USM_TO_LGM_UNIT_SIZE;

	sendData[0] = (packet.stx >> 16	) &0xFF;
	sendData[1] = (packet.stx >> 8	) &0xFF;
	sendData[2] = (packet.stx		) &0xFF;

	sendData[3] = (packet.scm_id		) &0xFF;
	sendData[4] = (packet.data_type		) &0xFF;
	sendData[5] = (packet.data_length>>8) &0xFF;
	sendData[6] = (packet.data_length	) &0xFF;

	packet.crc16 = crcsum((unsigned char *)(sendData+3), packet.data_length+4, CRC_INIT);

	sendData[packet.data_length+7] = (packet.crc16 >> 8	) &0xFF;
	sendData[packet.data_length+8] = (packet.crc16		) &0xFF;

	m_Comm.WriteCommBlock((char*)sendData,packet.data_length+9);
}

void CUSMTestDlg::OnBnClickedButtonSetOpModeLgm()
{
	UpdateData(TRUE);

	int SCMID = m_editSCMID;
	int nLgmCnt;

	switch(m_radioLGMAutoIncrease){
		case 0 : nLgmCnt = 1 +1; break;
		case 1 : nLgmCnt = 8 +2; break;
		case 2 : nLgmCnt = 16+2; break;
	}
	int usmInfo[2][4] = {
		 {1, 1, 0, 129}
		,{2, 50000, 0, 130}
		//,{3, 50001, 130}
		//,{4, 50002, 130}
	
	};
	int lgmInfo[18][3] = {
		 {129, 70000, 0}
		,{130, 70001, 0}
		,{131, 70001, 0}
		,{132, 70001, 0}
		,{133, 70001, 0}
		,{134, 70001, 0}
		,{135, 70001, 0}
		,{136, 70001, 0}
		,{137, 70001, 0}
		,{138, 70001, 0}
		,{139, 70001, 0}
		,{140, 70001, 0}
		,{141, 70001, 0}
		,{142, 70001, 0}
		,{143, 70001, 0}
		,{144, 70001, 0}
		,{145, 70001, 0}
		,{146, 70001, 0}
	};

	int opmode;

	switch(m_ctrlComboLGMOPMODE.GetCurSel())
	{
		case 0:opmode = 8;break;
		case 1:opmode = 3;break;
		case 2:opmode = 4;break;
		case 3:opmode = 5;break;
		case 4:opmode = 6;break;
	}

	unsigned char	sendData[INFO_MAX_RX_TX_PACKET_SIZE];
	for(int i=0; i<INFO_MAX_RX_TX_PACKET_SIZE; i++)
	{
		sendData[i]= 0;
	}

	for(int i=0; i<nLgmCnt; i++)
	{
		int tmp;
		tmp = lgmInfo[i][0];
		sendData[7+INFO_SET_USM_TO_LGM_UNIT_SIZE*i] = tmp & 0xFF;
		tmp = opmode; // LGM OP MODE
		sendData[7+INFO_SET_USM_TO_LGM_UNIT_SIZE*i+1] = tmp & 0xFF;

	}

	txPacket packet;
	packet.stx = 0;
	packet.scm_id = SCMID;
	packet.data_type = IDX_DT_SET_LGM_OP_MODE;
	packet.data_length = 2*INFO_SET_USM_TO_LGM_UNIT_SIZE;

	sendData[0] = (packet.stx >> 16	) &0xFF;
	sendData[1] = (packet.stx >> 8	) &0xFF;
	sendData[2] = (packet.stx		) &0xFF;

	sendData[3] = (packet.scm_id		) &0xFF;
	sendData[4] = (packet.data_type		) &0xFF;
	sendData[5] = (packet.data_length>>8) &0xFF;
	sendData[6] = (packet.data_length	) &0xFF;

	packet.crc16 = crcsum((unsigned char *)(sendData+3), packet.data_length+4, CRC_INIT);

	sendData[packet.data_length+7] = (packet.crc16 >> 8	) &0xFF;
	sendData[packet.data_length+8] = (packet.crc16		) &0xFF;

	m_Comm.WriteCommBlock((char*)sendData,packet.data_length+9);
}

void CUSMTestDlg::OnBnClickedButton6()
{
	int SCMID = m_editSCMID;
	char	sendData[INFO_MAX_RX_TX_PACKET_SIZE];
	for(int i=0; i<INFO_MAX_RX_TX_PACKET_SIZE; i++)
	{
		sendData[i]= 0;
	}
	txPacket packet;
	packet.stx = 0;
	packet.scm_id =SCMID;
	packet.data_type = IDX_DT_REQ_USM_STAT;
	packet.data_length = 0;

	sendData[2] = (packet.stx >> 16	) &0xFF;
	sendData[1] = (packet.stx >> 8	) &0xFF;
	sendData[0] = (packet.stx		) &0xFF;

	sendData[3] = (packet.scm_id		) &0xFF;
	sendData[4] = (packet.data_type		) &0xFF;
	sendData[5] = (packet.data_length>>8) &0xFF;
	sendData[6] = (packet.data_length	) &0xFF;

	packet.crc16 = crcsum((unsigned char *)(sendData+3), packet.data_length+4, CRC_INIT);

	sendData[packet.data_length+7] = (packet.crc16 >> 8	) &0xFF;
	sendData[packet.data_length+8] = (packet.crc16		) &0xFF;


	m_Comm.WriteCommBlock((char*)sendData,packet.data_length+9);
}

void CUSMTestDlg::OnBnClickedButtonParamUpdate()
{
	int nUsmCnt;

	switch(m_radioUSMAutoIncrease){
		case 0 : m_editSerialNumOfUSM += 1;  break;
		case 1 : m_editSerialNumOfUSM += 8;  break;
		case 2 : m_editSerialNumOfUSM += 16; break;
	}

	UpdateData(FALSE);
}

void CUSMTestDlg::OnBnClickedButtonParamUpdateLgm()
{
	int nLgmCnt;

	switch(m_radioLGMAutoIncrease){
		case 0 : m_editSerialNumOfLGM += 1; break;
		case 1 : m_editSerialNumOfLGM += 5; break;
		case 2 : m_editSerialNumOfLGM += 10;break;
	}

	UpdateData(FALSE);
}

void CUSMTestDlg::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	int nUsmCnt;


	switch(m_radioUSMAutoIncrease){
		case 0 : nUsmCnt = 1 +1; break;
		case 1 : nUsmCnt = 8 +2; break;
		case 2 : nUsmCnt = 16+2; break;
	}
	OnBnClickedButtonSetSerialNum();
	Sleep(100*nUsmCnt);
	OnBnClickedButtonSetSerialNumLgm();
	Sleep(100*nUsmCnt);
	OnBnClickedButtonUsmToLgm();
	Sleep(100*nUsmCnt);
	OnBnClickedButtonSensingOn();

	OnBnClickedButtonDataReset();
	UpdateData(FALSE);
	
}

void CUSMTestDlg::OnBnClickedButtonDataReset()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	m_editPLCReturnVal=_T("");
	m_reditStatus = _T("");
	UpdateData(FALSE);
}

void CUSMTestDlg::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnBnClickedButton6();

	UpdateData(TRUE);
	m_reditStatus = _T("");
	m_reditStatus.Format(_T("SCM ID : %0.3d \r\n"), m_editSCMID);
	m_reditStatus += _T("USM STATUS SUMMARY \r\n");
	m_reditStatus += _T("========================\r\n");
	m_reditStatus += _T("ID | Serial Num | USM to LGM | Status\r\n");
	m_reditStatus += _T("========================\r\n");

	for(int i=0; i<m_usmCnt; i++)
	{
		CString tStr;
		tStr.Format(_T("%0.3d%10.8d%18.3d%10.1d \r\n"), m_usmINFO[i].cID, m_usmINFO[i].sID, m_usmINFO[i].uTol, m_usmINFO[i].status);
		m_reditStatus += tStr;
	
	}
	UpdateData(FALSE);
}

void CUSMTestDlg::OnBnClickedButtonRdSysInfo()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	m_systemDataReadF = TRUE;


	CString lineBuf;
	CStdioFile pFile;
	CFileDialog dlgFile(TRUE);
	if(IDOK == dlgFile.DoModal()){
		CString strPathName = dlgFile.GetPathName();
		pFile.Open(strPathName, CFile::modeRead);
		
		int i=0, numCnt = 0;
		int scmID = 0, scmIDOK = 0;;

		
		while(pFile.ReadString(lineBuf)){
			if(lineBuf[0] == _T('S') && lineBuf[1] == _T('C') && lineBuf[2] == _T('M') ){
				pFile.ReadString(lineBuf);
				i=0;scmID=0;
				scmID += (lineBuf.GetAt(i++)-48)*100;
				scmID += (lineBuf.GetAt(i++)-48)* 10;
				scmID += (lineBuf.GetAt(i++)-48)*  1;
				if(m_editSCMID == scmID){scmIDOK = 1; break;}
			}
		}

		if(scmIDOK == 0){
			pFile.Close();

			AfxMessageBox(_T("There is not SCM Information for the set SCM ID"));
			return;
		}

		pFile.ReadString(lineBuf);

		if(lineBuf[0] == _T('U') && lineBuf[1] == _T('S') && lineBuf[2] == _T('M')){
			while(pFile.ReadString(lineBuf)){
				if (lineBuf[0] == _T('L') && lineBuf[1] == _T('G') && lineBuf[2] == _T('M')){ goto lgm;}
				if (lineBuf.GetAt(0) == 0 || lineBuf.GetAt(0) == 32 || lineBuf.GetAt(0) == 9) continue; // Space or horizontal tab
				i=0;
				m_usmINFO[numCnt].cID = 0;
				m_usmINFO[numCnt].cID += (lineBuf.GetAt(i++)-48)*100;
				m_usmINFO[numCnt].cID += (lineBuf.GetAt(i++)-48)* 10;
				m_usmINFO[numCnt].cID += (lineBuf.GetAt(i++)-48)*  1;

				i++;
				m_usmINFO[numCnt].sID = 0;
				m_usmINFO[numCnt].sID += (lineBuf.GetAt(i++)-48)*10000000;
				m_usmINFO[numCnt].sID += (lineBuf.GetAt(i++)-48)*1000000;
				m_usmINFO[numCnt].sID += (lineBuf.GetAt(i++)-48)*100000;
				m_usmINFO[numCnt].sID += (lineBuf.GetAt(i++)-48)*10000;
				m_usmINFO[numCnt].sID += (lineBuf.GetAt(i++)-48)*1000;
				m_usmINFO[numCnt].sID += (lineBuf.GetAt(i++)-48)*100;
				m_usmINFO[numCnt].sID += (lineBuf.GetAt(i++)-48)*10;
				m_usmINFO[numCnt].sID += (lineBuf.GetAt(i++)-48)*1;


				i++;
				m_usmINFO[numCnt].mode = (lineBuf.GetAt(i++)-48)*1;

				i++;
				m_usmINFO[numCnt].uTol=0;
				m_usmINFO[numCnt].uTol += (lineBuf.GetAt(i++)-48)*100;
				m_usmINFO[numCnt].uTol += (lineBuf.GetAt(i++)-48)*10;
				m_usmINFO[numCnt].uTol += (lineBuf.GetAt(i++)-48)*1;

				i++;
				m_usmINFO[numCnt].mxDist=0;
				m_usmINFO[numCnt].mxDist += (lineBuf.GetAt(i++)-48)*100;
				m_usmINFO[numCnt].mxDist += (lineBuf.GetAt(i++)-48)*10;
				m_usmINFO[numCnt].mxDist += (lineBuf.GetAt(i++)-48)*1;

				i++;
				m_usmINFO[numCnt].ySens=0;
				m_usmINFO[numCnt].ySens += (lineBuf.GetAt(i++)-48)*100;
				m_usmINFO[numCnt].ySens += (lineBuf.GetAt(i++)-48)*10;
				m_usmINFO[numCnt].ySens += (lineBuf.GetAt(i++)-48)*1;

				i++;
				m_usmINFO[numCnt].xSens=0;
				m_usmINFO[numCnt].xSens += (lineBuf.GetAt(i++)-48)*10;
				m_usmINFO[numCnt].xSens += (lineBuf.GetAt(i++)-48)*1;

				i++;
				m_usmINFO[numCnt].nPulse=0;
				m_usmINFO[numCnt].nPulse += (lineBuf.GetAt(i++)-48)*10;
				m_usmINFO[numCnt].nPulse += (lineBuf.GetAt(i++)-48)*1;

				i++;
				m_usmINFO[numCnt++].group = (lineBuf.GetAt(i++)-48)*1;
				m_usmCnt = numCnt;
			}
		}else if (lineBuf[0] == _T('L') && lineBuf[1] == _T('G') && lineBuf[2] == _T('M')){
lgm:		
			{
				numCnt = 0;
				while(pFile.ReadString(lineBuf)){
					if(lineBuf[0] == _T('S') && lineBuf[1] == _T('C') && lineBuf[2] == _T('M') ){break;}
					if (lineBuf.GetAt(0) == 0 || lineBuf.GetAt(0) == 32 || lineBuf.GetAt(0) == 9) continue; // Space or horizontal tab
					i=0;
					m_lgmINFO[numCnt].cID = 0;
					m_lgmINFO[numCnt].cID += (lineBuf.GetAt(i++)-48)*100;
					m_lgmINFO[numCnt].cID += (lineBuf.GetAt(i++)-48)* 10;
					m_lgmINFO[numCnt].cID += (lineBuf.GetAt(i++)-48)*  1;

					i++;
					m_lgmINFO[numCnt].sID = 0;
					m_lgmINFO[numCnt].sID += (lineBuf.GetAt(i++)-48)*10000000;
					m_lgmINFO[numCnt].sID += (lineBuf.GetAt(i++)-48)*1000000;
					m_lgmINFO[numCnt].sID += (lineBuf.GetAt(i++)-48)*100000;
					m_lgmINFO[numCnt].sID += (lineBuf.GetAt(i++)-48)*10000;
					m_lgmINFO[numCnt].sID += (lineBuf.GetAt(i++)-48)*1000;
					m_lgmINFO[numCnt].sID += (lineBuf.GetAt(i++)-48)*100;
					m_lgmINFO[numCnt].sID += (lineBuf.GetAt(i++)-48)*10;
					m_lgmINFO[numCnt].sID += (lineBuf.GetAt(i++)-48)*1;


					i++;
					m_lgmINFO[numCnt++].mode = (lineBuf.GetAt(i++)-48)*1;
					m_lgmCnt = numCnt;

				}
			}
		
		} // [E] else if (lineBuf == _T("LGM")){
	} // [E] if(lineBuf == _T("USM")){

	SetDlgItemText(IDC_STATIC_STATUS_MESSAGE, _T("Systemdata information loading success"));
	UpdateData(FALSE);
}

