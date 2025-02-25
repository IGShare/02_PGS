#pragma once

#define DEF_SCM_COMM_PORT				1
#define DEF_SCM_COMM_BAUDRATE			19200
#define DEF_SCM_COMM_RETRY_CNT			12
#define DEF_SCM_COMM_RCV_TIMEOUT		100
#define DEF_SCM_COMM_WAIT_AFTER_RCV		100
struct INFO_SCM_COMM_SETTINGS {
	int nPort;
	int nBaudrate;

	int nRetryCount;
	DWORD timeRcvTimeout;
	DWORD timeWaitAfterRcv;
};

struct STAT_SCM_COMM {
	BOOL isInit;
	BOOL bDataMismatch;

	BOOL bSet_USM_ADDR_EEPROM;
	BOOL bSet_USM_ADDR_PLC;
	BOOL bSet_LGM_ADDR_EEPROM;
	BOOL bSet_LGM_ADDR_PLC;

	BOOL bSet_USM2LGM_EEPROM;
	BOOL bSet_USM_OPMODE_EEPROM;
	BOOL bSet_LGM_OPMODE_EEPROM;
	BOOL bSet_USM_PARAM_EEPROM;
	
	int numRcvNAck;

	int numFailErrUnknownData;
	int numFailErrDevID_SCM;
	int numFailErrDataType;
	int numFailErrCRC16;
	int numFailErrRcvTimeout;

	int numPassErrUnknownData;
	int numPassErrDevID_SCM;
	int numPassErrDataType;
	int numPassErrCRC16;
	int numPassErrRcvTimeout;

	int idxLastError;
};

class CManSCM_Comm
{
public:
	CManSCM_Comm(void);
	~CManSCM_Comm(void);

	BOOL ProcessReq_REQ_USM_STAT (int nDevID_SCM, ITEM_RESM_USM_LGM_STAT *pIResM_USM_LGM_STAT);
	BOOL ProcessReq_REQ_LGM_STAT (int nDevID_SCM, ITEM_RESM_USM_LGM_STAT *pIResM_USM_LGM_STAT);
	BOOL ProcessReq_REQ_SET_USM_ADDRESS (int nDevID_SCM, int numUSM, ITEM_REQM_SET_ADDR *pBufIReqM_SET_ADDR);
	BOOL ProcessReq_REQ_SET_LGM_ADDRESS (int nDevID_SCM, int numLGM, ITEM_REQM_SET_ADDR *pBufIReqM_SET_ADDR);
	BOOL ProcessReq_REQ_SET_USM_OP_MODE (int nDevID_SCM, int numUSM, ITEM_REQM_SET_OP_MODE *pBufIReqM_SET_OP_MODE);
	BOOL ProcessReq_REQ_SET_LGM_OP_MODE (int nDevID_SCM, int numLGM, ITEM_REQM_SET_OP_MODE *pBufIReqM_SET_OP_MODE);
	BOOL ProcessReq_REQ_SET_USM_PARAM (int nDevID_SCM, int numUSM, ITEM_REQM_SET_PARAM *pBufIReqM_SET_PARAM);
	BOOL ProcessReq_REQ_SET_USM_TO_LGM (int nDevID_SCM, int numUSM, ITEM_REQM_SET_USM2LGM *pBufIReqM_SET_USM2LGM);
	BOOL ProcessReq_REQ_SENSING_ON (int nDevID_SCM);
	BOOL ProcessReq_REQ_SENSING_OFF (int nDevID_SCM);

	void SetCommSettings (INFO_SCM_COMM_SETTINGS *pISCMCS);
	const STAT_SCM_COMM *GetCommStat (int nDevID_SCM);

public:
	BOOL ProcessReq ();
	void ClearStatSCMC (int idxDevID_SCM, BOOL bClearNumRcvNAck, BOOL bClearNumFailErr, BOOL bClearNumPassErr);

	CComm m_comm;
	CCriticalSection m_crtAccComm;

	BYTE *m_bufSnd;
	BYTE *m_bufRcv;

	INFO_SCM_COMM_SETTINGS m_iSCMCS;
	STAT_SCM_COMM m_bufStatSCMC[MAX_NUM_SCM];
	ITEM_RESM_USM_LGM_STAT *m_pISCMA;
};
