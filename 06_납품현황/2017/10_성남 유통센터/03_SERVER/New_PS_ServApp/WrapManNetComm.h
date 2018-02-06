#pragma once

class CManNetComm;

struct ITEM_STAT_SCM {
	BOOL bRcvStat;
	ITEM_RESM_USM_LGM_STAT iStat;
};
struct ITEM_STAT_CCM {
	ITEM_STAT_SCM bufItem[MAX_NUM_SCM];
	int idxNC_Err;
};

typedef void (*UpdateNotifyFunc) ();

class CWrapManNetComm
{
public:
	CWrapManNetComm(void);
	~CWrapManNetComm(void);

	void SetUpdateNotifyFunc (UpdateNotifyFunc fpUN);
	void UpdateInfoCCM ();

	ITEM_STAT_CCM *GetBasePtrStatCCM ();
	BOOL IsNetCommReady (int idxCCM);
	BOOL IsClientConnected (int idxCCM);
	BOOL IsNetErrorExist (int idxCCM);

private:
	volatile BOOL m_bEndThread;

	CManNetComm *m_bufPManNetComm[MAX_NUM_CCM];
	INFO_NET_COMM_SETTINGS m_bufINCS[MAX_NUM_CCM];
	BOOL m_bufBInitCCM[MAX_NUM_CCM];

	ITEM_STAT_CCM *m_bufCurStatCCM;

	UpdateNotifyFunc m_fnUN;

	friend UINT TH_AppReqProc (LPVOID pParam);
};
