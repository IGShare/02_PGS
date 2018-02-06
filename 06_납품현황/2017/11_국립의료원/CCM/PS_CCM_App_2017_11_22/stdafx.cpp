// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// PS_CCM_App_SG.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"
unsigned short fnGetCrc16(unsigned char *nData, unsigned short wLength)
{
	static const unsigned short wCRCTable[] = {
		0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
		0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
		0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
		0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
		0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
		0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
		0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641, 
		0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
		0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
		0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
		0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
		0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
		0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
		0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
		0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
		0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
		0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
		0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
		0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
		0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
		0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
		0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
		0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
		0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
		0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
		0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
		0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
		0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
		0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
		0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
		0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
		0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040 };

	unsigned char nTemp;
	unsigned short wCRCWord = 0; //0: CRC16, 0xFFFF: CRC16(Modbus)
	while (wLength--) {
	nTemp = (unsigned char)(*nData++ ^ wCRCWord);
	wCRCWord >>= 8;
	wCRCWord ^= wCRCTable[nTemp];
	}
	return wCRCWord;
}

#define STR_GL_INFO_ITEM_SERV_ADDR						"# 서버 주소"
#define STR_GL_INFO_ITEM_CCM_DEV_ID						"# CCM 장치 제어 번호"
#define STR_GL_INFO_ITEM_SCM_COMM_PORT					"# SCM 통신 포트"
#define STR_GL_INFO_ITEM_SCM_COMM_BAUD_RATE				"# SCM 통신 BaudRate"
#define STR_GL_INFO_ITEM_SCM_COMM_NUM_RETRY				"# SCM 통신 재시도 횟수"
#define STR_GL_INFO_ITEM_SCM_COMM_RCV_TIMEOUT			"# SCM 통신 수신 타임아웃"
#define STR_GL_INFO_ITEM_SCM_COMM_WAIT_AFTER_RCV		"# SCM 통신 수신 후 기다림 시간"
#define STR_GL_INFO_ITEM_SDA_SNS_OFF_CMD_NUM_RETRY		"# 초기 장치 설정 SENSING OFF 커맨드 재시도 횟수"
#define STR_GL_INFO_ITEM_SDA_OTHER_CMD_CMD_NUM_RETRY	"# 초기 장치 설정 SENSING OFF 이외 커맨드 재시도 횟수"
#define STR_GL_INFO_ITEM_SDA_PROC_NUM_RETRY				"# 초기 장치 설정 전체 과정 재시도 횟수"
#define STR_GL_INFO_ITEM_SDA_CMD_WAIT_AFTER_FAIL		"# 초기 장치 설정 커맨드 실패 후 기다림 시간"
#define STR_GL_INFO_ITEM_SDA_TIMEOUT_CHECK_ZERO_STAT	"# 초기 장치 설정 장치 상태 검사 타임아웃"
#define STR_GL_INFO_ITEM_EBD1_COMM_PORT					"# 전광판1 통신 포트" // 층별
#define STR_GL_INFO_ITEM_EBD1_COMM_BAUD_RATE			"# 전광판1 통신 BaudRate"
#define STR_GL_INFO_ITEM_EBD1_COMM_SND_INTERVAL			"# 전광판1 통신 송신 인터벌"
#define STR_GL_INFO_ITEM_EBD2_COMM_PORT					"# 전광판2 통신 포트" // 입구
#define STR_GL_INFO_ITEM_EBD2_COMM_BAUD_RATE			"# 전광판2 통신 BaudRate"
#define STR_GL_INFO_ITEM_EBD2_COMM_SND_INTERVAL			"# 전광판2 통신 송신 인터벌"

BOOL ReadInfoGlobal ()
{
	FILE *fp;
	char strLine1[1024], strLine2[1024];
	CString cstrTmp;
	int nTmp;

	memset (&glIGlobal, 0, sizeof(INFO_GLOBAL));

	fopen_s (&fp, STR_INFO_GLOBAL_FILE_PATH, "rt");

	if (fp == NULL)
	{
		return FALSE;
	}

	while (fgets (strLine1, 1023, fp) != 0)
	{
		if (!(strLine1[0] == '#' && strLine1[1] == ' '))
		{
			continue;
		}

		fgets (strLine2, 1023, fp);

		cstrTmp = strLine2;
		cstrTmp.Delete (cstrTmp.Find ('\n'), 1);
		sscanf_s (strLine2, "%d", &nTmp);

		if (memcmp (strLine1, STR_GL_INFO_ITEM_SERV_ADDR, strlen (STR_GL_INFO_ITEM_SERV_ADDR)) == 0)
		{
			wcscpy_s (glIGlobal.strServAddr, SZ_STR_SERV_ADDR, LPCTSTR(cstrTmp));
		}
		else if (memcmp (strLine1, STR_GL_INFO_ITEM_CCM_DEV_ID, strlen (STR_GL_INFO_ITEM_CCM_DEV_ID)) == 0)
		{
			glIGlobal.nDevID_CCM = nTmp;
		}
		else if (memcmp (strLine1, STR_GL_INFO_ITEM_SCM_COMM_PORT, strlen (STR_GL_INFO_ITEM_SCM_COMM_PORT)) == 0)
		{
			glIGlobal.iSCS.nPort = nTmp;
		}
		else if (memcmp (strLine1, STR_GL_INFO_ITEM_SCM_COMM_BAUD_RATE, strlen (STR_GL_INFO_ITEM_SCM_COMM_BAUD_RATE)) == 0)
		{
			glIGlobal.iSCS.nBaudrate = nTmp;
		}
		else if (memcmp (strLine1, STR_GL_INFO_ITEM_SCM_COMM_NUM_RETRY, strlen (STR_GL_INFO_ITEM_SCM_COMM_NUM_RETRY)) == 0)
		{
			glIGlobal.iSCS.nRetryCount = nTmp;
		}
		else if (memcmp (strLine1, STR_GL_INFO_ITEM_SCM_COMM_RCV_TIMEOUT, strlen (STR_GL_INFO_ITEM_SCM_COMM_RCV_TIMEOUT)) == 0)
		{
			glIGlobal.iSCS.timeRcvTimeout = nTmp;
		}
		else if (memcmp (strLine1, STR_GL_INFO_ITEM_SCM_COMM_WAIT_AFTER_RCV, strlen (STR_GL_INFO_ITEM_SCM_COMM_WAIT_AFTER_RCV)) == 0)
		{
			glIGlobal.iSCS.timeWaitAfterRcv = nTmp;
		}
		else if (memcmp (strLine1, STR_GL_INFO_ITEM_SDA_SNS_OFF_CMD_NUM_RETRY, strlen (STR_GL_INFO_ITEM_SDA_SNS_OFF_CMD_NUM_RETRY)) == 0)
		{
			glIGlobal.SetAD_nRetrySnsOffCmd = nTmp;
		}
		else if (memcmp (strLine1, STR_GL_INFO_ITEM_SDA_OTHER_CMD_CMD_NUM_RETRY, strlen (STR_GL_INFO_ITEM_SDA_OTHER_CMD_CMD_NUM_RETRY)) == 0)
		{
			glIGlobal.SetAD_nRetryOtherCmd = nTmp;
		}
		else if (memcmp (strLine1, STR_GL_INFO_ITEM_SDA_PROC_NUM_RETRY, strlen (STR_GL_INFO_ITEM_SDA_PROC_NUM_RETRY)) == 0)
		{
			glIGlobal.SetAD_nRetryProc = nTmp;
		}
		else if (memcmp (strLine1, STR_GL_INFO_ITEM_SDA_CMD_WAIT_AFTER_FAIL, strlen (STR_GL_INFO_ITEM_SDA_CMD_WAIT_AFTER_FAIL)) == 0)
		{
			glIGlobal.SetAD_timeWaitAfterCmdFail = nTmp;
		}
		else if (memcmp (strLine1, STR_GL_INFO_ITEM_SDA_TIMEOUT_CHECK_ZERO_STAT, strlen (STR_GL_INFO_ITEM_SDA_TIMEOUT_CHECK_ZERO_STAT)) == 0)
		{
			glIGlobal.SetAD_timeoutCheckNoZeroStat = nTmp;
		}
		else if (memcmp (strLine1, STR_GL_INFO_ITEM_EBD1_COMM_PORT, strlen (STR_GL_INFO_ITEM_EBD1_COMM_PORT)) == 0)
		{
			glIGlobal.EBD1Comm_nPort = nTmp;
		}
		else if (memcmp (strLine1, STR_GL_INFO_ITEM_EBD1_COMM_BAUD_RATE, strlen (STR_GL_INFO_ITEM_EBD1_COMM_BAUD_RATE)) == 0)
		{
			glIGlobal.EBD1Comm_nBaudRate = nTmp;
		}
		else if (memcmp (strLine1, STR_GL_INFO_ITEM_EBD1_COMM_SND_INTERVAL, strlen (STR_GL_INFO_ITEM_EBD1_COMM_SND_INTERVAL)) == 0)
		{
			glIGlobal.EBD1Comm_timeSendInterval = nTmp;
		}
		else if (memcmp (strLine1, STR_GL_INFO_ITEM_EBD2_COMM_PORT, strlen (STR_GL_INFO_ITEM_EBD2_COMM_PORT)) == 0)
		{
			glIGlobal.EBD2Comm_nPort = nTmp;
		}
		else if (memcmp (strLine1, STR_GL_INFO_ITEM_EBD2_COMM_BAUD_RATE, strlen (STR_GL_INFO_ITEM_EBD2_COMM_BAUD_RATE)) == 0)
		{
			glIGlobal.EBD2Comm_nBaudRate = nTmp;
		}
		else if (memcmp (strLine1, STR_GL_INFO_ITEM_EBD2_COMM_SND_INTERVAL, strlen (STR_GL_INFO_ITEM_EBD2_COMM_SND_INTERVAL)) == 0)
		{
			glIGlobal.EBD2Comm_timeSendInterval = nTmp;
		}
	}

	fclose (fp);

//	glIGlobal.EBD1Comm_bufDstID[IDX_EBD1_ENTRANCE_01] = 1;
//	glIGlobal.EBD1Comm_bufDstID[IDX_EBD1_ENTRANCE_02] = 2;

	glIGlobal.EBD1Comm_bufDstID[IDX_EBD1_STAIR_1F_01] =  1;
	//glIGlobal.EBD1Comm_bufDstID[IDX_EBD1_STAIR_1F_02] =  2;
	//glIGlobal.EBD1Comm_bufDstID[IDX_EBD1_STAIR_1F_03] =  3;
	//
	//glIGlobal.EBD1Comm_bufDstID[IDX_EBD1_ENTRANCE_01] =  4;
	//glIGlobal.EBD1Comm_bufDstID[IDX_EBD1_ENTRANCE_02] =  5;

	return TRUE;
}

void WriteInfoGlobal ()
{
	FILE *fp;
	char strTmp[1024];
	size_t nConv;

	fopen_s (&fp, STR_INFO_GLOBAL_FILE_PATH, "wt");

	if (fp == NULL)
	{
		return;
	}

	wcstombs_s (&nConv, strTmp, 1024, glIGlobal.strServAddr, wcslen (glIGlobal.strServAddr));
	fprintf (fp, "%s\n%s\n", STR_GL_INFO_ITEM_SERV_ADDR, strTmp);
	fprintf (fp, "%s\n%d\n", STR_GL_INFO_ITEM_CCM_DEV_ID, glIGlobal.nDevID_CCM);
	fprintf (fp, "\n");

	fprintf (fp, "%s\n%d\n", STR_GL_INFO_ITEM_SCM_COMM_PORT, glIGlobal.iSCS.nPort);
	fprintf (fp, "%s\n%d\t// 19200, 38400\n", STR_GL_INFO_ITEM_SCM_COMM_BAUD_RATE, glIGlobal.iSCS.nBaudrate);
	fprintf (fp, "%s\n%d\n", STR_GL_INFO_ITEM_SCM_COMM_NUM_RETRY, glIGlobal.iSCS.nRetryCount);
	fprintf (fp, "%s\n%d\n", STR_GL_INFO_ITEM_SCM_COMM_RCV_TIMEOUT, glIGlobal.iSCS.timeRcvTimeout);
	fprintf (fp, "%s\n%d\n", STR_GL_INFO_ITEM_SCM_COMM_WAIT_AFTER_RCV, glIGlobal.iSCS.timeWaitAfterRcv);
	fprintf (fp, "\n");

	fprintf (fp, "%s\n%d\n", STR_GL_INFO_ITEM_SDA_SNS_OFF_CMD_NUM_RETRY, glIGlobal.SetAD_nRetrySnsOffCmd);
	fprintf (fp, "%s\n%d\n", STR_GL_INFO_ITEM_SDA_OTHER_CMD_CMD_NUM_RETRY, glIGlobal.SetAD_nRetryOtherCmd);
	fprintf (fp, "%s\n%d\n", STR_GL_INFO_ITEM_SDA_PROC_NUM_RETRY, glIGlobal.SetAD_nRetryProc);
	fprintf (fp, "%s\n%d\n", STR_GL_INFO_ITEM_SDA_CMD_WAIT_AFTER_FAIL, glIGlobal.SetAD_timeWaitAfterCmdFail);
	fprintf (fp, "%s\n%d\n", STR_GL_INFO_ITEM_SDA_TIMEOUT_CHECK_ZERO_STAT, glIGlobal.SetAD_timeoutCheckNoZeroStat);
	fprintf (fp, "\n");

	fprintf (fp, "%s\n%d\n", STR_GL_INFO_ITEM_EBD1_COMM_PORT, glIGlobal.EBD1Comm_nPort);
	fprintf (fp, "%s\n%d\t// 9600, 115200\n", STR_GL_INFO_ITEM_EBD1_COMM_BAUD_RATE, glIGlobal.EBD1Comm_nBaudRate);
	fprintf (fp, "%s\n%d\n", STR_GL_INFO_ITEM_EBD1_COMM_SND_INTERVAL, glIGlobal.EBD1Comm_timeSendInterval);

	fprintf (fp, "%s\n%d\n", STR_GL_INFO_ITEM_EBD2_COMM_PORT, glIGlobal.EBD2Comm_nPort);
	fprintf (fp, "%s\n%d\t// 9600, 115200\n", STR_GL_INFO_ITEM_EBD2_COMM_BAUD_RATE, glIGlobal.EBD2Comm_nBaudRate);
	fprintf (fp, "%s\n%d\n", STR_GL_INFO_ITEM_EBD2_COMM_SND_INTERVAL, glIGlobal.EBD2Comm_timeSendInterval);

	fclose (fp);
}

#define SZ_EBD_SND_BUF		512

// 0xe0 0x18	: _u	: 위쪽 화살표
// 0xe0 0x19	: _d	: 아래쪽 화살표
// 0xe0 0x1a	: _r	: 오른쪽 화살표
// 0xe0 0x1b	: _l	: 왼쪽 화살표

void SendTxtToEBoard (int nDST, char *strSndA, char *strSndB, int *bufClrA, int *bufClrB, CComm *pComm)
{
	int szTxt;
	BYTE bufSnd[SZ_EBD_SND_BUF], *pBufSnd;
	int i, nLEN;

	//// Message A[S]
	szTxt = strlen (strSndA);
	pBufSnd = &bufSnd[0];

	*pBufSnd++ = 0x10;	// DLE
	*pBufSnd++ = 0x02;	// STX
	*pBufSnd++ = nDST;	// DST

	nLEN = 17 +szTxt +szTxt;
	*pBufSnd++ = (nLEN >>8) &0xff;	// LEN(H)
	*pBufSnd++ = (nLEN >>0) &0xff;	// LEN(L)

//	10 02 01 00 1B -
//	94 00 01 63 00 00 03 01 01 00 00 02 00 00 10 04 00 02 02 02 02 02 71 77 65 72 74 10 03 

	*pBufSnd++ = 0x94;	// CMD
	*pBufSnd++ = 0x00;	// Param 페이지 번호(1)
	*pBufSnd++ = 0x01;	// Param 섹션 번호(1)
	*pBufSnd++ = 0x63;	// Param 표시 제어(1)
	*pBufSnd++ = 0x00;	// Param 표시 방법(1)
	*pBufSnd++ = 0x00;	// Param 문자 코드(1)
	*pBufSnd++ = 0x03;	// Param 폰트 크기(1)
	*pBufSnd++ = 0x01;	// Param 입장 효과(1)
	*pBufSnd++ = 0x01;	// Param 퇴장 효과(1)
	*pBufSnd++ = 0x00;	// Param 보조 효과(1)
	*pBufSnd++ = 0x00;	// Param 효과 속도(1)
	*pBufSnd++ = 0x02;	// Param 유지 시간(1)
	*pBufSnd++ = 0x00;	// Param X축 시작점(1)
	*pBufSnd++ = 0x00;	// Param Y축 시작점(1)
	*pBufSnd++ = 0x10;	// Param X축 종료점(1)
	*pBufSnd++ = 0x04;	// Param Y축 종료점(1)
	*pBufSnd++ = 0x00;	// Param 배경 이미지(1)

	// Param 글자 색상[S]
	for (i=0; i<szTxt; i++)
	{
		*pBufSnd++ = bufClrA[i];
	}
	// Param 글자 색상[E]

	// Param 문구[S]
	for (i=0; i<szTxt; i++)
	{
		if (i < szTxt -1)
		{
			if (strSndA[i] == '_' &&
				(strSndA[i +1] == 'u' || strSndA[i +1] == 'd' || strSndA[i +1] == 'l' || strSndA[i +1] == 'r' || strSndA[i +1] == 'h' || strSndA[i +1] == 'x' || strSndA[i +1] == 'e'))
			{
				*pBufSnd++ = 0xe0;

				switch (strSndA[i +1])
				{
				case 'u':
					*pBufSnd++ = 0x18;
					break;
				case 'd':
					*pBufSnd++ = 0x19;
					break;
				case 'r':
					*pBufSnd++ = 0x1a;
					break;
				case 'l':
					*pBufSnd++ = 0x1b;
					break;
				case 'h':
					*pBufSnd++ = 0x1c;
					break;
				}
				i++;

				continue;
			}
			else
			{
				*pBufSnd++ = strSndA[i];
			}
		}
		else
		{
			*pBufSnd++ = strSndA[i];
		}
	}
	// Param 문구[E]

	*pBufSnd++ = 0x10;	// DLE
	*pBufSnd++ = 0x03;	// STX

	pComm->Send (bufSnd, 5 +nLEN +2);

	Sleep (100);
	//// Message A[E]

	//// Message B[S]
	szTxt = strlen (strSndB);
	pBufSnd = &bufSnd[0];

	*pBufSnd++ = 0x10;	// DLE
	*pBufSnd++ = 0x02;	// STX
	*pBufSnd++ = nDST;	// DST

	nLEN = 17 +szTxt +szTxt;
	*pBufSnd++ = (nLEN >>8) &0xff;	// LEN(H)
	*pBufSnd++ = (nLEN >>0) &0xff;	// LEN(L)

	//	10 02 01 00 1B -
	//	94 00 00 63 00 00 03 06 01 00 14 04 10 00 20 04 00 02 02 02 02 02 71 77 65 72 74 10 03

	if (szTxt <= 8)
	{
		*pBufSnd++ = 0x94;	// CMD
		*pBufSnd++ = 0x00;	// Param 페이지 번호(1)
		*pBufSnd++ = 0x00;	// Param 섹션 번호(1)
		*pBufSnd++ = 0x63;	// Param 표시 제어(1)
		*pBufSnd++ = 0x00;	// Param 표시 방법(1)
		*pBufSnd++ = 0x00;	// Param 문자 코드(1)
		*pBufSnd++ = 0x03;	// Param 폰트 크기(1)
		*pBufSnd++ = 0x01;	// Param 입장 효과(1)
		*pBufSnd++ = 0x01;	// Param 퇴장 효과(1)
		*pBufSnd++ = 0x00;	// Param 보조 효과(1)
		*pBufSnd++ = 0x00;	// Param 효과 속도(1)
		*pBufSnd++ = 0x02;	// Param 유지 시간(1)
		*pBufSnd++ = 0x10;	// Param X축 시작점(1)
		*pBufSnd++ = 0x00;	// Param Y축 시작점(1)
		*pBufSnd++ = 0x20;	// Param X축 종료점(1)
		*pBufSnd++ = 0x04;	// Param Y축 종료점(1)
		*pBufSnd++ = 0x00;	// Param 배경 이미지(1)
	}
	else
	{
		*pBufSnd++ = 0x94;	// CMD
		*pBufSnd++ = 0x00;	// Param 페이지 번호(1)
		*pBufSnd++ = 0x00;	// Param 섹션 번호(1)
		*pBufSnd++ = 0x63;	// Param 표시 제어(1)
		*pBufSnd++ = 0x00;	// Param 표시 방법(1)
		*pBufSnd++ = 0x00;	// Param 문자 코드(1)
		*pBufSnd++ = 0x03;	// Param 폰트 크기(1)
		*pBufSnd++ = 0x06;	// Param 입장 효과(1)
		*pBufSnd++ = 0x06;	// Param 퇴장 효과(1)
		*pBufSnd++ = 0x00;	// Param 보조 효과(1)
		*pBufSnd++ = 0x1e;	// Param 효과 속도(1)
		*pBufSnd++ = 0x00;	// Param 유지 시간(1)
		*pBufSnd++ = 0x10;	// Param X축 시작점(1)
		*pBufSnd++ = 0x00;	// Param Y축 시작점(1)
		*pBufSnd++ = 0x20;	// Param X축 종료점(1)
		*pBufSnd++ = 0x04;	// Param Y축 종료점(1)
		*pBufSnd++ = 0x00;	// Param 배경 이미지(1)
	}

	// Param 글자 색상[S]
	for (i=0; i<szTxt; i++)
	{
		*pBufSnd++ = bufClrB[i];
	}
	// Param 글자 색상[E]

	// Param 문구[S]
	for (i=0; i<szTxt; i++)
	{
		if (i < szTxt -1)
		{
			if (strSndB[i] == '_' &&
				(strSndB[i +1] == 'u' || strSndB[i +1] == 'd' || strSndB[i +1] == 'l' || strSndB[i +1] == 'r' || strSndB[i +1] == 'e'))
			{
				*pBufSnd++ = 0xe0;

				switch (strSndB[i +1])
				{
				case 'u':
					*pBufSnd++ = 0x18;
					break;
				case 'd':
					*pBufSnd++ = 0x19;
					break;
				case 'r':
					*pBufSnd++ = 0x1a;
					break;
				case 'l':
					*pBufSnd++ = 0x1b;
					break;
				}
				i++;

				continue;
			}
			else
			{
				*pBufSnd++ = strSndB[i];
			}
		}
		else
		{
			*pBufSnd++ = strSndB[i];
		}
	}
	// Param 문구[E]

	*pBufSnd++ = 0x10;	// DLE
	*pBufSnd++ = 0x03;	// STX

	pComm->Send (bufSnd, 5 +nLEN +2);

	Sleep (100);
	//// Message B[E]
}

void SendTxtToEBoard (int nDST, char *strSnd, int *bufClr, CComm *pComm)
{
	int szTxt = strlen (strSnd);
	BYTE bufSnd[SZ_EBD_SND_BUF], *pBufSnd;
	int i, nLEN;
	unsigned short CRC16;
	unsigned char crcMask = 0x40;
	int crc16F = 1;

	pBufSnd = &bufSnd[0];

	*pBufSnd++ = 0x10;	// DLE
	*pBufSnd++ = 0x02;	// STX
	*pBufSnd++ = nDST;	// DST

	if(crc16F == true)
	{
		nLEN = 17 +szTxt +szTxt + 2;
		*pBufSnd++ = ((nLEN >>8) &0xff) | crcMask ;	// LEN(H)
	}
	else{
		nLEN = 17 +szTxt +szTxt;
		*pBufSnd++ = (nLEN >>8) &0xff;	// LEN(H)
	}
	//*pBufSnd++ = (nLEN >>8) &0xff;	// LEN(H)
	*pBufSnd++ = (nLEN >>0) &0xff;	// LEN(L)

	//	10 02 01 00 1B -
	//	94 00 01 63 00 00 03 01 01 00 00 02 00 00 10 04 00 02 02 02 02 02 71 77 65 72 74 10 03 

	*pBufSnd++ = 0x94;	// CMD
	*pBufSnd++ = 0x00;	// Param 페이지 번호(1)
	*pBufSnd++ = 0x00;	// Param 섹션 번호(1)
	*pBufSnd++ = 0x63;	// Param 표시 제어(1)
	*pBufSnd++ = 0x01;	// Param 표시 방법(1)
	*pBufSnd++ = 0x00;	// Param 문자 코드(1)
	*pBufSnd++ = 0x03;	// Param 폰트 크기(1)
	*pBufSnd++ = 0x01;	// Param 입장 효과(1)
	*pBufSnd++ = 0x01;	// Param 퇴장 효과(1)
	*pBufSnd++ = 0x00;	// Param 보조 효과(1)
	*pBufSnd++ = 0x00;	// Param 효과 속도(1)
	*pBufSnd++ = 0xf8;	// Param 유지 시간(1)
	*pBufSnd++ = 0x00;	// Param X축 시작점(1)
	*pBufSnd++ = 0x00;	// Param Y축 시작점(1)
	*pBufSnd++ = 0x00;	// Param X축 종료점(1)
	*pBufSnd++ = 0x00;	// Param Y축 종료점(1)
	*pBufSnd++ = 0x00;	// Param 배경 이미지(1)

	// Param 글자 색상[S]
	for (i=0; i<szTxt; i++)
	{
		*pBufSnd++ = bufClr[i];
	}
	// Param 글자 색상[E]

	// Param 문구[S]
	for (i=0; i<szTxt; i++)
	{
		if (i < szTxt -1)
		{
			if (strSnd[i] == '_' &&
				(strSnd[i +1] == 'u' || strSnd[i +1] == 'd' || strSnd[i +1] == 'l' || strSnd[i +1] == 'r' || strSnd[i +1] == 'h' || strSnd[i +1] == 'b' || strSnd[i +1] == 'x' || strSnd[i +1] == 'e'))
			{
				*pBufSnd++ = 0xe0;

				switch (strSnd[i +1])
				{
				case 'u':
					*pBufSnd++ = 0x18;
					break;
				case 'd':
					*pBufSnd++ = 0x19;
					break;
				case 'r':
					*pBufSnd++ = 0x1a;
					break;
				case 'l':
					*pBufSnd++ = 0x1b;
					break;
				case 'h':
					*pBufSnd++ = 0x1c;
					break;
				case 'b':
					*pBufSnd++ = 0x7f;
					break;
				}
				i++;

				continue;
			}
			else
			{
				*pBufSnd++ = strSnd[i];
			}
		}
		else
		{
			*pBufSnd++ = strSnd[i];
		}
	}
	// Param 문구[E]

	if(crc16F == true)
	{
		CRC16 = fnGetCrc16(bufSnd +2, 17+szTxt +szTxt+3);

		*pBufSnd++ =  CRC16     & 0xFF;	// CRC HIGH
		*pBufSnd++ = (CRC16>>8) & 0xFF;	// CRC LOW	
		*pBufSnd++ = 0x10;	// DLE
		*pBufSnd++ = 0x03;	// STX	
		pComm->Send (bufSnd, 5 + nLEN +2 + 2);
	}
	else{
		*pBufSnd++ = 0x10;	// DLE
		*pBufSnd++ = 0x03;	// STX
		pComm->Send (bufSnd, 5 + nLEN +2);
	}

	pComm->Send (bufSnd, 5 +nLEN +2);

	// Write Debug Data[S]
	char strDbg[256];
	for (i=0; i<szTxt; i++)
	{
		strDbg[i] = strSnd[i];
	}
	strDbg[i +0] = '\n';
	strDbg[i +1] = 0;
	AddReport (strDbg);
	// Write Debug Data[E]
}

// HANJIN P4793 CRC16[S]
static const unsigned short HJ_P4793_crc_table[256] = {
	0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
	0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
	0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
	0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
	0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
	0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
	0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
	0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
	0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
	0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
	0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
	0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
	0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
	0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
	0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
	0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
	0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
	0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
	0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
	0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
	0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
	0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
	0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
	0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
	0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
	0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
	0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
	0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
	0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
	0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
	0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
	0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};

#define HJ_P4793_CRC_INIT 0xFFFF
#define HJ_P4793_CRC16(crcval,newchar) crcval = (crcval >> 8) ^ \
	HJ_P4793_crc_table[(crcval ^ newchar) & 0x00ff]

unsigned short HJ_P4793_CRC16_GenCode (const unsigned char* message, unsigned long length)
{
	unsigned long i;
	unsigned short crc = HJ_P4793_CRC_INIT;

	for(i = 0; i < length; i++)
	{
		HJ_P4793_CRC16(crc, message[i]);
	}

	return crc;
}
// HANJIN P4793 CRC16[E]
