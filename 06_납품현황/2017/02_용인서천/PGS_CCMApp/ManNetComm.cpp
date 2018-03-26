#include "StdAfx.h"
#include "ManNetComm.h"


#define SZ_BUF_NET_RCV				(4 *1024)
#define SZ_BUF_NET_SND				(4 *1024)

UINT TH_NetCommProc (LPVOID pParam)
{
	CManNetComm *pMan = (CManNetComm *)pParam;


	if (!AfxSocketInit ())
	{
		AfxMessageBox (STR_MSG_SOCK_INIT_FAIL);

		while (pMan->m_bEndThread == FALSE)	{	Sleep (10);	}
		pMan->m_bEndThread = FALSE;

		return 0;
	}

	while (pMan->m_bEndThread == FALSE)
	{
		if (pMan->m_bEnable == FALSE)
		{
			if (pMan->m_bConnected == TRUE)
			{
				if (pMan->NetCommRcvAndSkipProc () == FALSE)
				{
					pMan->ResetSockComm ();

					pMan->m_bConnected = FALSE;
					//AddReport ("Disconnected [enable=0]\n");
				}
			}

			Sleep (50);
			continue;
		}

		if (pMan->m_bConnected == TRUE)
		{
			if (pMan->NetCommRcv () == FALSE ||
				pMan->ProcRcvPkt () == FALSE)
			{
				pMan->ResetSockComm ();

				pMan->m_bConnected = FALSE;
				//AddReport ("Disconnected\n");
				Sleep (100);
			}
			else
			{

				Sleep (50);
			}
		}
		else
		{
			if (pMan->m_nDevID_CCM < MIN_DEV_ID_CCM || pMan->m_nDevID_CCM > MAX_DEV_ID_CCM)
			{
				Sleep (100);
				continue;
			}

			if (pMan->m_pSockComm != NULL)
			{
				pMan->ResetSockComm ();
			}

			pMan->m_pSockComm = new CAsyncSocket;
			if (pMan->m_pSockComm == NULL)
			{
				Sleep (100);
				continue;
			}
			if (pMan->m_pSockComm->Create (0, SOCK_STREAM, 0) == FALSE)
			{
				pMan->ResetSockComm ();

				Sleep (100);
				continue;
			}

			DWORD idxErr;

			while (pMan->m_pSockComm->Connect (pMan->m_strServAddr, NUM_ICCS_NET_COMM_BASE_PORT +pMan->m_nDevID_CCM) == FALSE)
			{
				idxErr = GetLastError ();

				if (idxErr == WSAEISCONN)
				{
					break;
				}
				else if (idxErr == WSAEWOULDBLOCK)
				{
					Sleep (50);
				}
				else
				{
					pMan->ResetSockComm ();

					Sleep (100);
					break;
				}
			}

			if (pMan->m_pSockComm != NULL)
			{
				pMan->m_bConnected = TRUE;
				//AddReport ("Connected\n");
			}
		}
	}

	if (pMan->m_pSockComm != NULL)
	{
		pMan->ResetSockComm ();
	}

	pMan->m_bEndThread = FALSE;

	return 0;
}

__inline void CManNetComm::ResetSockComm ()
{
	m_pSockComm->Close ();
	delete m_pSockComm;
	m_pSockComm = NULL;
}

CManNetComm::CManNetComm(ITEM_RESM_USM_LGM_STAT *pBufOldStatUSM_LGM)
{
	m_pSockComm = NULL;
	m_bEndThread = FALSE;
	m_bConnected = FALSE;
	m_bEnable = TRUE;

	m_bufRcv = new BYTE[SZ_BUF_NET_RCV];
	m_bufSnd = new BYTE[SZ_BUF_NET_SND];
	m_posPkt = -1;
	m_posRcv = 0;

	memcpy (&m_bufSnd[0], GL_ICCS_BUF_STX, SZ_ICCS_PKT_ITEM_STX);

	m_nDevID_CCM = MIN_DEV_ID_CCM -1;
	m_strServAddr[0] = 0;

	m_pManSCM_Comm = NULL;

	m_bufStatUSM_LGM = new ITEM_RESM_USM_LGM_STAT[MAX_NUM_SCM];
	if (pBufOldStatUSM_LGM != NULL)
	{
		memcpy (&m_bufStatUSM_LGM[0], pBufOldStatUSM_LGM, sizeof(ITEM_RESM_USM_LGM_STAT) *MAX_NUM_SCM);
	}
	else
	{
		memset (&m_bufStatUSM_LGM[0], 0, sizeof(ITEM_RESM_USM_LGM_STAT) *MAX_NUM_SCM);
	}

	//AfxBeginThread (TH_NetCommProc, this);
}

CManNetComm::~CManNetComm(void)
{
	m_bEndThread = TRUE;
	while (m_bEndThread == TRUE)
	{
		Sleep (10);
	}

	delete[] m_bufRcv;
	delete[] m_bufSnd;
	delete[] m_bufStatUSM_LGM;
}

void CManNetComm::ReqConnect (int nDevID_CCM, const wchar_t *strServAddr)
{
	m_nDevID_CCM = nDevID_CCM;
	wcscpy_s (m_strServAddr, SZ_STR_SERV_ADDR, strServAddr);

	m_bConnected = FALSE;
}

void CManNetComm::SetSCM_Comm (CManSCM_Comm *pManSCM_Comm)
{
	m_pManSCM_Comm = pManSCM_Comm;
}

BOOL CManNetComm::IsConnected ()
{
	return m_bConnected;
}

void CManNetComm::EnableManNetComm (BOOL bEnable)
{
	m_bEnable = bEnable;
}

BOOL CManNetComm::NetCommRcv ()
{
	int i, numRcv, nLength;
	WORD nCRC16;

	numRcv = m_pSockComm->Receive (&m_bufRcv[m_posRcv], SZ_BUF_NET_RCV -m_posRcv);

	if (numRcv == 0)
	{
		//AddReport ("NetCommRcv(): numRcv = 0\n");
		return FALSE;
	}
	else if (numRcv == SOCKET_ERROR)
	{
		int nErrCode = m_pSockComm->GetLastError ();

		if (nErrCode != WSAEWOULDBLOCK)
		{
			LogPrintSocketError (0, nErrCode);
			return FALSE;
		}

		Sleep (50);
	}
	else
	{
		m_posRcv += numRcv;

		for (i=0; i<m_posRcv -SZ_ICCS_PKT_ITEM_STX -SZ_ICCS_PKT_ITEM_LENGTH; i++)
		{
			if (m_bufRcv[i +0] == GL_ICCS_BUF_STX[0] && m_bufRcv[i +1] == GL_ICCS_BUF_STX[1] &&
				m_bufRcv[i +2] == GL_ICCS_BUF_STX[2] && m_bufRcv[i +3] == GL_ICCS_BUF_STX[3] &&
				m_posRcv >= SZ_ICCS_PKT_HDR_ALL +((m_bufRcv[i +4] <<8) +m_bufRcv[i +5]))	// Packet detection
			{
				nLength = (m_bufRcv[i +4] <<8) +m_bufRcv[i +5];

				// Check CRC16[S]
				nCRC16 = CRC16_GenCode (&m_bufRcv[i +SZ_ICCS_PKT_ITEM_STX], SZ_ICCS_PKT_ITEM_LENGTH +nLength);
				if (m_bufRcv[i +SZ_ICCS_PKT_ITEM_STX +SZ_ICCS_PKT_ITEM_LENGTH +nLength +0] != ((nCRC16 >>8) &0xff) ||
					m_bufRcv[i +SZ_ICCS_PKT_ITEM_STX +SZ_ICCS_PKT_ITEM_LENGTH +nLength +1] != ((nCRC16 >>0) &0xff))
				{
					continue;
				}
				// Check CRC16[E]

				// Check ETX[S]
				if (m_bufRcv[i +SZ_ICCS_PKT_ITEM_STX +SZ_ICCS_PKT_ITEM_LENGTH +nLength +SZ_ICCS_PKT_ITEM_CRC16 +0] != GL_ICCS_BUF_ETX[0] ||
					m_bufRcv[i +SZ_ICCS_PKT_ITEM_STX +SZ_ICCS_PKT_ITEM_LENGTH +nLength +SZ_ICCS_PKT_ITEM_CRC16 +1] != GL_ICCS_BUF_ETX[1] ||
					m_bufRcv[i +SZ_ICCS_PKT_ITEM_STX +SZ_ICCS_PKT_ITEM_LENGTH +nLength +SZ_ICCS_PKT_ITEM_CRC16 +2] != GL_ICCS_BUF_ETX[2] ||
					m_bufRcv[i +SZ_ICCS_PKT_ITEM_STX +SZ_ICCS_PKT_ITEM_LENGTH +nLength +SZ_ICCS_PKT_ITEM_CRC16 +3] != GL_ICCS_BUF_ETX[3])
				{
					continue;
				}
				// Check ETX[E]

				m_posPkt = i;
				i = -1;
				break;
			}
		}

		if (m_posPkt == -1 && m_posRcv >= SZ_BUF_NET_RCV *3 /4)
		{
			m_posRcv = 0;
		}
	}

	return TRUE;
}

BOOL CManNetComm::ProcRcvPkt ()
{
	if (m_posPkt == -1 || m_pManSCM_Comm == NULL)
	{
		return TRUE;
	}

	ITEM_HDR_REQM *pIHdrReqM_Rcv = (ITEM_HDR_REQM *)&m_bufRcv[m_posPkt];

	ITEM_REQM_SET_ADDR *pIReqM_SetAddr = (ITEM_REQM_SET_ADDR *)&m_bufRcv[m_posPkt +sizeof(ITEM_HDR_REQM)];
	ITEM_REQM_SET_OP_MODE *pIReqM_SetOpMode = (ITEM_REQM_SET_OP_MODE *)&m_bufRcv[m_posPkt +sizeof(ITEM_HDR_REQM)];
	ITEM_REQM_SET_PARAM *pIReqM_SetParam = (ITEM_REQM_SET_PARAM *)&m_bufRcv[m_posPkt +sizeof(ITEM_HDR_REQM)];
	ITEM_REQM_SET_USM2LGM *pIReqM_SetUSM2LGM = (ITEM_REQM_SET_USM2LGM *)&m_bufRcv[m_posPkt +sizeof(ITEM_HDR_REQM)];

	ITEM_HDR_REQM *pIHdrReqM_Snd = (ITEM_HDR_REQM *)&m_bufSnd[0];
	ITEM_RESM_USM_LGM_STAT *pIResM_USM_LGM_Stat = (ITEM_RESM_USM_LGM_STAT *)&m_bufSnd[sizeof(ITEM_HDR_REQM)];
	ITEM_TRL_REQM *pITrlReqM;

	ITEM_RESM_USM_LGM_STAT *pStatUSM_LGM;

	int nLength;
	BOOL bRetOk;

	// Initializing RcvPkt related parameters[S]
	m_posPkt = -1;
	m_posRcv = 0;
	// Initializing RcvPkt related parameters[E]

	if (pIHdrReqM_Rcv->devID_SCM < MIN_DEV_ID_SCM || pIHdrReqM_Rcv->devID_SCM > MAX_DEV_ID_SCM)
	{
		return FALSE;
	}

	// Processing RcvPkt[S]
	m_crtAccStatUSM_LGM.Lock ();

	pIHdrReqM_Snd->devID_SCM = pIHdrReqM_Rcv->devID_SCM;
	pStatUSM_LGM = &m_bufStatUSM_LGM[pIHdrReqM_Rcv->devID_SCM -MIN_DEV_ID_SCM];
	pITrlReqM = (ITEM_TRL_REQM *)&m_bufSnd[sizeof(ITEM_HDR_REQM)];

	switch (pIHdrReqM_Rcv->nDataType)
	{
	case IDX_ICCS_DT_REQ_USM_LGM_STAT:
		UpdateSCM_Stat (pIHdrReqM_Rcv->devID_SCM, IDX_ICCS_DT_REQ_USM_LGM_STAT, TRUE);

		memcpy (&m_bufSnd[sizeof(ITEM_HDR_REQM)], pStatUSM_LGM, sizeof(ITEM_RESM_USM_LGM_STAT));

		nLength = 3 +sizeof(ITEM_RESM_USM_LGM_STAT);
		pIHdrReqM_Snd->nDataType = IDX_ICCS_DT_RES_USM_LGM_STAT;
		pIHdrReqM_Snd->numItem = 0;

		pITrlReqM = (ITEM_TRL_REQM *)&m_bufSnd[sizeof(ITEM_HDR_REQM) +sizeof(ITEM_RESM_USM_LGM_STAT)];
		break;
	case IDX_ICCS_DT_REQ_SET_USM_OP_MODE:
		bRetOk = m_pManSCM_Comm->ProcessReq_REQ_SET_USM_OP_MODE (pIHdrReqM_Rcv->devID_SCM, pIHdrReqM_Rcv->numItem, pIReqM_SetOpMode);

		UpdateSCM_Stat (pIHdrReqM_Rcv->devID_SCM, IDX_ICCS_DT_REQ_SET_USM_OP_MODE, bRetOk);

		nLength = 3;
		pIHdrReqM_Snd->nDataType = (bRetOk == TRUE) ? IDX_ICCS_DT_ACK : IDX_ICCS_DT_NACK;
		pIHdrReqM_Snd->numItem = m_bufStatUSM_LGM[pIHdrReqM_Rcv->devID_SCM -MIN_DEV_ID_SCM].statSCM;
		break;
	case IDX_ICCS_DT_REQ_SET_LGM_OP_MODE:
		bRetOk = m_pManSCM_Comm->ProcessReq_REQ_SET_LGM_OP_MODE (pIHdrReqM_Rcv->devID_SCM, pIHdrReqM_Rcv->numItem, pIReqM_SetOpMode);

		UpdateSCM_Stat (pIHdrReqM_Rcv->devID_SCM, IDX_ICCS_DT_REQ_SET_LGM_OP_MODE, bRetOk);

		nLength = 3;
		pIHdrReqM_Snd->nDataType = (bRetOk == TRUE) ? IDX_ICCS_DT_ACK : IDX_ICCS_DT_NACK;
		pIHdrReqM_Snd->numItem = m_bufStatUSM_LGM[pIHdrReqM_Rcv->devID_SCM -MIN_DEV_ID_SCM].statSCM;
		break;

	default:	// Invalid packet
		nLength = 3;
		pIHdrReqM_Snd->nDataType = IDX_ICCS_DT_NACK;
		pIHdrReqM_Snd->numItem = FLAG_ICCS_SCM_COMM_ERROR |IDX_ICCS_NACK_ERR_SCM_RX_INVALID_DATA;
		break;
	}

	m_crtAccStatUSM_LGM.Unlock ();
	// Processing RcvPkt[E]

	// Send ResPkt[S]
	WORD nCRC16;
	int posSnd, numSend, szSnd;

	pIHdrReqM_Snd->bufLength[0] = (nLength >>8) &0xff;
	pIHdrReqM_Snd->bufLength[1] = (nLength >>0) &0xff;

	nCRC16 = CRC16_GenCode (&m_bufSnd[SZ_ICCS_PKT_ITEM_STX], 2 +nLength);
	pITrlReqM->bufCRC[0] = (nCRC16 >>8) &0xff;
	pITrlReqM->bufCRC[1] = (nCRC16 >>0) &0xff;
	memcpy (pITrlReqM->bufETX, GL_ICCS_BUF_ETX, SZ_ICCS_PKT_ITEM_ETX);

	posSnd = 0;
	szSnd = SZ_ICCS_PKT_HDR_ALL +nLength;
	while (1)
	{
		numSend = m_pSockComm->Send (&m_bufSnd[posSnd], szSnd -posSnd);

		if (numSend == SOCKET_ERROR)
		{
			int nErrCode = m_pSockComm->GetLastError ();

			if (nErrCode != WSAEWOULDBLOCK)
			{
				LogPrintSocketError (1, nErrCode);
				return FALSE;
			}
		}
		else
		{
			posSnd += numSend;
			if (posSnd >= szSnd)
			{
				break;
			}
		}
	}
	// Send ResPkt[E]

	return TRUE;
}

BOOL CManNetComm::NetCommRcvAndSkipProc ()
{
	if (NetCommRcv () == FALSE)
	{
		return FALSE;
	}
	m_posPkt = -1;
	m_posRcv = 0;

	return TRUE;
}

void CManNetComm::LogPrintSocketError (int idxFunc, int idxErrCode)
{
	return;

	char strTmp[MAX_PATH];

	if (idxFunc == 0)
	{
		strcpy_s (strTmp, MAX_PATH, "NetCommRcv()");
	}
	else
	{
		strcpy_s (strTmp, MAX_PATH, "ProcRcvPkt()");
	}

	switch (idxErrCode)
	{
	case WSAENETDOWN:
		AddReport ("[%2d] %s : ERROR: WSAENETDOWN\n", m_nDevID_CCM, strTmp);
		break;
	case WSAENOTCONN:
		AddReport ("[%2d] %s : ERROR: WSAENOTCONN\n", m_nDevID_CCM, strTmp);
		break;
	case WSAEINPROGRESS:
		AddReport ("[%2d] %s : ERROR: WSAEINPROGRESS\n", m_nDevID_CCM, strTmp);
		break;
	case WSAESHUTDOWN:
		AddReport ("[%2d] %s : ERROR: WSAESHUTDOWN\n", m_nDevID_CCM, strTmp);
		break;
/*	case WSAEWOULDBLOCK:
		AddReport ("[%2d] %s : WSAEWOULDBLOCK\n", m_nDevID_CCM, strTmp);
		break;*/
	case WSAEMSGSIZE:
		AddReport ("[%2d] %s : ERROR: WSAEMSGSIZE\n", m_nDevID_CCM, strTmp);
		break;
	case WSAEINVAL:
		AddReport ("[%2d] %s : ERROR: WSAEINVAL\n", m_nDevID_CCM, strTmp);
		break;
	case WSAECONNABORTED:
		AddReport ("[%2d] %s : ERROR: WSAECONNABORTED\n", m_nDevID_CCM, strTmp);
		break;
	case WSAECONNRESET:
		AddReport ("[%2d] %s : ERROR: WSAECONNRESET\n", m_nDevID_CCM, strTmp);
		break;
	}
}

void CManNetComm::UpdateSCM_Stat (int nDevID_SCM, int idxReq, BOOL bAck)
{
	ITEM_RESM_USM_LGM_STAT *pStatUSM_LGM = &m_bufStatUSM_LGM[nDevID_SCM -MIN_DEV_ID_SCM];
	const STAT_SCM_COMM *pStatSCM_Comm = m_pManSCM_Comm->GetCommStat (nDevID_SCM);

	if (bAck == TRUE)
	{
		pStatUSM_LGM->statSCM &= ~(FLAG_ICCS_SCM_INIT |FLAG_ICCS_SCM_COMM_ERROR |MASK_FOR_ICCS_SCM_ERR_CODE);
		switch (idxReq)
		{
		case IDX_ICCS_DT_REQ_USM_LGM_STAT:
			if (pStatSCM_Comm->bDataMismatch == TRUE)
			{
				pStatUSM_LGM->statSCM |= FLAG_ICCS_SCM_STAT_MISMATCH;
			}
			else
			{
				pStatUSM_LGM->statSCM &= ~FLAG_ICCS_SCM_STAT_MISMATCH;
			}
			break;
		case IDX_ICCS_DT_REQ_SENSING_ON:
			pStatUSM_LGM->statSCM |= FLAG_ICCS_SCM_SENSING_ON;
			break;
		case IDX_ICCS_DT_REQ_SENSING_OFF:
			pStatUSM_LGM->statSCM &= ~FLAG_ICCS_SCM_SENSING_ON;
			break;
		}
	}
	else
	{
		if (pStatSCM_Comm == NULL)
		{
			pStatUSM_LGM->statSCM |= FLAG_ICCS_SCM_COMM_ERROR;
			pStatUSM_LGM->statSCM = (pStatUSM_LGM->statSCM &MASK_FOR_ICCS_SCM_FLAG) |IDX_ICCS_NACK_ERR_SCM_NOT_CONNECTED;
		}
		else if (pStatSCM_Comm->isInit == TRUE)
		{
			pStatUSM_LGM->statSCM |= FLAG_ICCS_SCM_INIT;
			pStatUSM_LGM->statSCM &= ~(FLAG_ICCS_SCM_COMM_ERROR |MASK_FOR_ICCS_SCM_ERR_CODE);
		}
		else
		{
			pStatUSM_LGM->statSCM |= FLAG_ICCS_SCM_COMM_ERROR;
			pStatUSM_LGM->statSCM = (pStatUSM_LGM->statSCM &MASK_FOR_ICCS_SCM_FLAG) |pStatSCM_Comm->idxLastError;
		}
	}
}
