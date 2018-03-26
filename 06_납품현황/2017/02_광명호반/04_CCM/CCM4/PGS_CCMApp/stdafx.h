// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.

#pragma once

#pragma comment(linker, "/nodefaultlib:libc.lib")
#pragma comment(linker, "/nodefaultlib:libcd.lib")

// 참고 - 이 값은 대상 Windows CE OS 버전과 밀접한 관련은 없습니다.
#define WINVER _WIN32_WCE

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// 일부 CString 생성자는 명시적으로 선언됩니다.
#ifdef _CE_DCOM
#define _ATL_APARTMENT_THREADED
#endif

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <ceconfig.h>
#if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
#define SHELL_AYGSHELL
#endif

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif



#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC 소켓 확장입니다.


#if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
#ifndef _DEVICE_RESOLUTION_AWARE
#define _DEVICE_RESOLUTION_AWARE
#endif
#endif

#ifdef _DEVICE_RESOLUTION_AWARE
#include "DeviceResolutionAware.h"
#endif


#if (_WIN32_WCE < 0x500) && ( defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP) )
	#pragma comment(lib, "ccrtrtti.lib")
	#ifdef _X86_	
		#if defined(_DEBUG)
			#pragma comment(lib, "libcmtx86d.lib")
		#else
			#pragma comment(lib, "libcmtx86.lib")
		#endif
	#endif
#endif

#include <altcecrt.h>

#include "afxmt.h"
#include "GlobalDef.h"
#include "InfoComm_CCM_Serv.h"
#include "crc16.h"
#include "Comm.h"
#include "Xdefine.h"
#include "ManNetComm.h"
#include "ManSCM_Comm.h"

//#define __PRINT_LOG_DATA__
//#define __ALWAYS_AUTO_INIT_RET_OK__
#define __SHOW_DLG_SETTING_GENERAL__
#define __RST_WHEN_WRITE_DEBUG_DATA__

#define STR_LOG_FILE_PATH				"EZPARK\\Log_PS_CCM_App_SG.txt"

#define SZ_APP_WND_H				800
#define SZ_APP_WND_V				480

#define STR_MSG_SOCK_INIT_FAIL			_T("CCM 장치의 네트웍 설정에 문제가 있습니다.\n관리 업체에 문의해 주세요.")

#define STR_INFO_GLOBAL_FILE_PATH		"EZPARK\\InfoGlobalData.txt"
#define STR_INFO_DEBUG_DATA_FILE_PATH	"EZPARK\\DebugData.txt"
#define STR_INIT_DEBUG_DATA_FILE_PATH	"EZPARK\\InitDebugData.txt"
#define STR_INFO_USM_LGM_DATA_PATH	    "EZPARK\\SystemDataInfo.txt"


#define NUM_EBD_GROUP			100

enum {
	//입구
	IDX_EBD1_ENTRANCE_01,
	////층별
	//IDX_EBD1_STAIR_ID_01,
	IDX_EBD1_STAIR_ID_02,
	IDX_EBD1_STAIR_ID_03,
	IDX_EBD1_STAIR_ID_04,
	IDX_EBD1_STAIR_ID_05,
	IDX_EBD1_STAIR_ID_06,
	IDX_EBD1_STAIR_ID_07,
	IDX_EBD1_STAIR_ID_08,
	IDX_EBD1_STAIR_ID_09,
	IDX_EBD1_STAIR_ID_10,
	IDX_EBD1_STAIR_ID_11,
	IDX_EBD1_STAIR_ID_12,
	IDX_EBD1_STAIR_ID_13,
	IDX_EBD1_STAIR_ID_14,
	IDX_EBD1_STAIR_ID_15,

	//입구
//	IDX_EBD1_ENTRANCE_01,


	NUM_EBD1_DEV
};

enum {
	IDX_EBD1_ENTRANCE_001,
//	IDX_EBD1_ENTRANCE_02,

	NUM_EBD2_DEV
};

enum {
	IDX_SBD_01,
//	IDX_EBD1_ENTRANCE_02,

	NUM_SBD_DEV
};

enum {
	IDX_EBD_CLR_BLACK,
	IDX_EBD_CLR_RED,
	IDX_EBD_CLR_GREEN,
	IDX_EBD_CLR_YELLOW,
	IDX_EBD_CLR_PURPLE,
	IDX_EBD_CLR_MARGENTA,
	IDX_EBD_CLR_CYAN,
	IDX_EBD_CLR_WHITE,

	NUM_EBD_TXT_CLR
};
#define MAX_NUM_STR_IN_EBD			32

#define NUM_PORT_CMS_RCV_INFO		2		 // Central Monitoring System PORT
#define NUM_BAUD_RATE_CMS_RCV_INFO	2400	 // Central Monitoring System BAUDRATE

void SendTxtToEBoard (int nDST, char *strSndA, char *strSndB, int *bufClrA, int *bufClrB, CComm *pComm);
void SendTxtToEBoard (int nDST, char *strSnd, int *bufClr, CComm *pComm);


struct INFO_GLOBAL {
	wchar_t strServAddr[SZ_STR_SERV_ADDR];
	int nDevID_CCM;
	int nIsServerUsed;

	INFO_SCM_COMM_SETTINGS iSCS;

	int SetUSMParam;
	int SetUSMLGMOPMode;
	int SetAD_nRetrySnsOffCmd;
	int SetAD_nRetryOtherCmd;
	int SetAD_nRetryProc;
	DWORD SetAD_timeWaitAfterCmdFail;
	DWORD SetAD_timeoutCheckNoZeroStat;

	int EBD1Comm_nPort;
	int EBD1Comm_nBaudRate;
	int EBD1Comm_timeSendInterval;
	int EBD1Comm_bufDstID[NUM_EBD1_DEV];
	int nIsEBD1Used;

	int EBD2Comm_nPort;
	int EBD2Comm_nBaudRate;
	int EBD2Comm_timeSendInterval;
	int EBD2Comm_bufDstID[NUM_EBD2_DEV];
	int nIsEBD2Used;

	int SBDComm_nPort;
	int SBDComm_nBaudRate;
	int SBDComm_timeSendInterval;
	int SBDComm_bufDstID[NUM_SBD_DEV];
	int nIsSBDUsed;

	int CMSComm_nPort;
	int CMSComm_nBaudRate;
	int CMSComm_timeSendInterval;
	int CMSComm_bufDstID[NUM_SBD_DEV];
	int nIsCMSUsed;

	volatile int EBDComm_numFreeCMS;
};

extern INFO_GLOBAL glIGlobal;

BOOL ReadInfoGlobal ();
void WriteInfoGlobal ();

int GetNumUSM (ITEM_RESM_USM_LGM_STAT *pISCMA);
int GetNumLGM (ITEM_RESM_USM_LGM_STAT *pISCMA);

// HANJIN P4793 CRC16[S]
unsigned short HJ_P4793_CRC16_GenCode (const unsigned char* message, unsigned long length);
// HANJIN P4793 CRC16[E]

