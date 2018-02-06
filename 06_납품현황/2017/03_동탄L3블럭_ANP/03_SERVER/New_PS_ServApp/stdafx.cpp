
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// PS_ServApp.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"
#include "math.h"
#include "WrapManNetComm.h"
#include "PaneBD.h"
#include "PS_ServAppDoc.h"
#include "PS_ServAppView.h"
#include "Shlwapi.h"


#define M_PI						(acos (-1.))
#define GET_ROUNDED_VAL(x)			(((x)>0) ? short((x) +0.5) : short((x) -0.5))

INFO_GLOBAL glInfoGlobal;


void ReadDebugData ();
void ReadDebugDataFromFile (int idxCCM, LPCTSTR strFilePath);


void ReadInitSettingsFromFile ()
{
	ReadDebugData ();
	ReadInfoBDA ();
}

void ReadDebugData ()
{
	int i;
	char strCurAppPath[MAX_PATH], strDebugDataFilePath[MAX_PATH], strTmp[MAX_PATH];

	GetCurrentDirectory (MAX_PATH, strCurAppPath);

	for (i=0; i<MAX_NUM_CCM; i++)
	{
		sprintf_s (strTmp, MAX_PATH, STR_DEBUG_DATA_FORMAT, MIN_DEV_ID_CCM +i);
		sprintf_s (strDebugDataFilePath, MAX_PATH, "%s\\%s", strCurAppPath, strTmp);

		if (::PathFileExists (strDebugDataFilePath) == TRUE)
		{
			ReadDebugDataFromFile (i, strDebugDataFilePath);
		}
  	}
}

void ReadDebugDataFromFile (int idxCCM, LPCTSTR strFilePath)
{
	SYSTEMTIME curTime;
	GetLocalTime(&curTime);

	INFO_CTRL_DEV_ALL *pICDA = &glInfoGlobal.iCDA;

	if (pICDA->bufICDevCCM[idxCCM].bUse == FALSE)
	{
		pICDA->bufICDevCCM[idxCCM].bUse = TRUE;
		sprintf_s (pICDA->bufICDevCCM[idxCCM].strName, "CCM %d", idxCCM +MIN_DEV_ID_CCM);

		pICDA->bufICDevCCM[idxCCM].iDev.nSN.nRev = 1;
		pICDA->bufICDevCCM[idxCCM].iDev.nSN.nDevNum = idxCCM +MIN_DEV_ID_CCM;
		pICDA->bufICDevCCM[idxCCM].iDev.nDevID = idxCCM +MIN_DEV_ID_CCM;

		pICDA->numDevCCM++;
	}

	pICDA->bufNumDevSCM[idxCCM] = 0;
	memset (&pICDA->bbufNumDevUSM[idxCCM][0], 0, sizeof(int) *MAX_NUM_SCM);
	memset (&pICDA->bbufNumDevLGM[idxCCM][0], 0, sizeof(int) *MAX_NUM_SCM);

	memset (&pICDA->bbufICDevSCM[idxCCM][0], 0, sizeof(INFO_CTRL_DEV_SCM) *MAX_NUM_SCM);
	memset (&pICDA->bbbufICDevUSM[idxCCM][0][0], 0, sizeof(INFO_CTRL_DEV_USM) *MAX_NUM_SCM *MAX_NUM_USM);
	memset (&pICDA->bbbufICDevLGM[idxCCM][0][0], 0, sizeof(INFO_CTRL_DEV_LGM) *MAX_NUM_SCM *MAX_NUM_LGM);

	FILE *fp;
	char strLine[1024];
	int idxDevType, bufTmp[16], idxSCM;
	INFO_DEV_USM *pIDUSM;
	INFO_DEV_LGM *pIDLGM;

	fopen_s (&fp, strFilePath, "rt");

	if (fp == NULL)
	{
		return;
	}

	idxDevType = IDX_DEV_TYPE_USM;
	idxSCM = 0;

	while (fgets (strLine, 1023, fp) != 0)
	{
		if (strLine[0] == 'U' && strLine[1] == 'S' && strLine[2] == 'M')
		{
			idxDevType = IDX_DEV_TYPE_USM;
		}
		else if (strLine[0] == 'L' && strLine[1] == 'G' && strLine[2] == 'M')
		{
			idxDevType = IDX_DEV_TYPE_LGM;
		}
		else if (strLine[0] == 'S' && strLine[1] == 'C' && strLine[2] == 'M')
		{
			idxDevType = IDX_DEV_TYPE_SCM;
		}
		else
		{
			if (idxDevType == IDX_DEV_TYPE_USM)
			{
				if (sscanf_s (strLine, "%03d %08d %d %03d %03d %03d %02d %02d %03d",
					&bufTmp[0], &bufTmp[1], &bufTmp[2], &bufTmp[3], &bufTmp[4], &bufTmp[5], &bufTmp[6], &bufTmp[7], &bufTmp[8]) == 9)
				{
					if (bufTmp[0] > 0)
					{
						if (bufTmp[0] <= MAX_DEV_ID_USM)
						{
							pICDA->bbbufICDevUSM[idxCCM][idxSCM][bufTmp[0] -MIN_DEV_ID_USM].bUse = TRUE;
							sprintf_s (pICDA->bbbufICDevUSM[idxCCM][idxSCM][bufTmp[0] -MIN_DEV_ID_USM].strName, "USM %d", bufTmp[0] -MIN_DEV_ID_USM +1);

							pIDUSM = &pICDA->bbbufICDevUSM[idxCCM][idxSCM][bufTmp[0] -MIN_DEV_ID_USM].iDev;

							pIDUSM->nSN.nRev = 1;
							pIDUSM->nSN.nDevNum = bufTmp[1];
							pIDUSM->nDevID = bufTmp[0];
							pIDUSM->idxOpMode = IDX_OPM_SENS_LED_OFF;
							pIDUSM->bufParam[IDX_USM_PARAM_MAX_DET_DIST] = (bufTmp[4] -MIN_USMP_MAX_DET_DIST) /INC_USMP_MAX_DET_DIST;
							pIDUSM->bufParam[IDX_USM_PARAM_ADC_AMP_LV] = (bufTmp[5] -MIN_USMP_ADC_AMP_LV) /INC_USMP_ADC_AMP_LV;
							pIDUSM->bufParam[IDX_USM_PARAM_ADC_SNS_LV] = (bufTmp[6] -MIN_USMP_ADC_SNS_LV) /INC_USMP_ADC_SNS_LV;
							pIDUSM->bufParam[IDX_USN_PARAM_TX_BURST_CNT] = (bufTmp[7] -MIN_USMP_TX_BURST_CNT) /INC_USMP_TX_BURST_CNT;
							pIDUSM->nDevID_LGM = bufTmp[3];
							pIDUSM->nGroup = bufTmp[8];
							pIDUSM->nLTPTimeRef.wDay = curTime.wDay;
							pIDUSM->nLTPTimeRef.wHour = curTime.wHour;
							pIDUSM->nLTPTimeRef.wMinute = curTime.wMinute;
							pIDUSM->nLTPTimeRef.wSecond = curTime.wSecond;
							pIDUSM->bStartParkingF = 0;
							pIDUSM->bGreenCnt=0;


							pICDA->bbufNumDevUSM[idxCCM][idxSCM]++;
						}
						else
						{
							AfxMessageBox (_T("ERROR: Invalid USM device ID (1 to 127)"));
						}
					}
				}
			}
			else if (idxDevType == IDX_DEV_TYPE_LGM)
			{
				if (sscanf_s (strLine, "%03d %08d %d",
					&bufTmp[0], &bufTmp[1], &bufTmp[2]) == 3)
				{
					if (bufTmp[0] > 0)
					{
						if (bufTmp[0] >= MIN_DEV_ID_LGM)
						{
							pICDA->bbbufICDevLGM[idxCCM][idxSCM][bufTmp[0] -MIN_DEV_ID_LGM].bUse = TRUE;
							sprintf_s (pICDA->bbbufICDevLGM[idxCCM][idxSCM][bufTmp[0] -MIN_DEV_ID_LGM].strName, "LGM %d", bufTmp[0] -MIN_DEV_ID_LGM +1);

							pIDLGM = &pICDA->bbbufICDevLGM[idxCCM][idxSCM][bufTmp[0] -MIN_DEV_ID_LGM].iDev;

							pIDLGM->nSN.nRev = 1;
							pIDLGM->nSN.nDevNum = bufTmp[1];
							pIDLGM->nDevID = bufTmp[0];
							pIDLGM->idxOpMode = IDX_OPM_SENS_LED_OFF;;

							pICDA->bbufNumDevLGM[idxCCM][idxSCM]++;
						}
						else
						{
							AfxMessageBox (_T("ERROR: Invalid LGM device ID (129 to 255)"));
						}
					}
				}
			}
			else
			{
				if (sscanf_s (strLine, "%03d", &bufTmp[0]) == 1)
				{
					if (bufTmp[0] >= MIN_DEV_ID_SCM && bufTmp[0] <= MAX_DEV_ID_SCM)
					{
						idxSCM = bufTmp[0] -MIN_DEV_ID_SCM;

						if (pICDA->bbufICDevSCM[idxCCM][idxSCM].bUse == FALSE)
						{
							pICDA->bbufICDevSCM[idxCCM][idxSCM].bUse = TRUE;
							sprintf_s (pICDA->bbufICDevSCM[idxCCM][idxSCM].strName, "SCM %d - %d", idxCCM +MIN_DEV_ID_CCM, idxSCM +MIN_DEV_ID_SCM);

							pICDA->bbufICDevSCM[idxCCM][idxSCM].iDev.nSN.nRev = 1;
							pICDA->bbufICDevSCM[idxCCM][idxSCM].iDev.nSN.nDevNum = (idxCCM +MIN_DEV_ID_CCM) *100 +(idxSCM +MIN_DEV_ID_SCM);
							pICDA->bbufICDevSCM[idxCCM][idxSCM].iDev.nDevID = idxSCM +MIN_DEV_ID_SCM;

							pICDA->bufNumDevSCM[idxCCM]++;
						}
					}
					else
					{
						AfxMessageBox (_T("ERROR: Invalid SCM device ID (1 to 15)"));
					}
				}
			}
		}
	}

	fclose (fp);
}

void ReadInfoBDA ()
{
	CFile fp;
	DWORD szRead;
	int i;
	char strCurAppPath[MAX_PATH], strTmp[MAX_PATH];

	GetCurrentDirectory (MAX_PATH, strCurAppPath);
	sprintf_s (strTmp, MAX_PATH, "%s\\%s", strCurAppPath, STR_INFO_BDA_FILE_NAME);
	if (fp.Open (strTmp, CFile::modeRead) == FALSE)
	{
INIT_IBDA:
		memset (&glInfoGlobal.iBDA, 0, sizeof(INFO_BACK_DRAWING_ALL));
		return;
	}

	szRead = sizeof(INFO_BACK_DRAWING_ALL);
	if (fp.Read (&glInfoGlobal.iBDA, szRead) != szRead)
	{
		fp.Close ();
		goto INIT_IBDA;
	}

	// Read INFO_BACK_DRAWING_ITEM[S]
	if (glInfoGlobal.iBDA.maxBDI == 0)
	{
		return;
	}

	glInfoGlobal.iBDA.bufBDI = new INFO_BACK_DRAWING_ITEM[glInfoGlobal.iBDA.maxBDI];

	szRead = glInfoGlobal.iBDA.maxBDI *sizeof(INFO_BACK_DRAWING_ITEM);
	if (fp.Read (&glInfoGlobal.iBDA.bufBDI[0], szRead) != szRead)
	{
		fp.Close ();
		goto INIT_IBDA;
	}
	// Read INFO_BACK_DRAWING_ITEM[E]

	// Read INFO_DISP_ITEM[S]
	for (i=0; i<glInfoGlobal.iBDA.maxBDI; i++)
	{
		if (glInfoGlobal.iBDA.bufBDI[i].maxDispItem > 0)
		{
			glInfoGlobal.iBDA.bufBDI[i].bufDispItem = new INFO_DISP_ITEM[glInfoGlobal.iBDA.bufBDI[i].maxDispItem];
			szRead = glInfoGlobal.iBDA.bufBDI[i].maxDispItem *sizeof(INFO_DISP_ITEM);
			if (fp.Read (&glInfoGlobal.iBDA.bufBDI[i].bufDispItem[0], szRead) != szRead)
			{
				fp.Close ();
				goto INIT_IBDA;
			}
		}
	}
	// Read INFO_DISP_ITEM[E]

	fp.Close ();
}

void WriteInfoBDA ()
{
	CFile fp;
	int i;
	char strCurAppPath[MAX_PATH], strTmp[MAX_PATH];

	GetCurrentDirectory (MAX_PATH, strCurAppPath);
	sprintf_s (strTmp, MAX_PATH, "%s\\%s", strCurAppPath, STR_INFO_BDA_FILE_NAME);
	if (fp.Open (strTmp, CFile::modeCreate |CFile::modeWrite) == FALSE)
	{
		return;
	}

	fp.Write (&glInfoGlobal.iBDA, sizeof(INFO_BACK_DRAWING_ALL));

	// Write INFO_BACK_DRAWING_ITEM[S]
	if (glInfoGlobal.iBDA.maxBDI > 0)
	{
		fp.Write (&glInfoGlobal.iBDA.bufBDI[0], glInfoGlobal.iBDA.maxBDI *sizeof(INFO_BACK_DRAWING_ITEM));

		// Write INFO_DISP_ITEM[S]
		for (i=0; i<glInfoGlobal.iBDA.maxBDI; i++)
		{
			if (glInfoGlobal.iBDA.bufBDI[i].maxDispItem > 0)
			{
				fp.Write (&glInfoGlobal.iBDA.bufBDI[i].bufDispItem[0], glInfoGlobal.iBDA.bufBDI[i].maxDispItem *sizeof(INFO_DISP_ITEM));
			}
		}
		// Write INFO_DISP_ITEM[E]
	}
	// Write INFO_BACK_DRAWING_ITEM[E]

	fp.Close ();
}

void SetPtDrawDisp_from_ZoomParam (INFO_DISP_ITEM *pIDI, INFO_ZOOM_PARAM *pZP)
{
	int i, posX, posY, szH, szV, szTmpH, szTmpV;

	if (pZP->nZoom == NUM_ZOOM_FIT_TO_SCR)
	{
		posX = pIDI->ptDrawOrgX *pZP->szWndClient.cx /pZP->szBackDrawing.cx;
		posY = pIDI->ptDrawOrgY *pZP->szWndClient.cy /pZP->szBackDrawing.cy;

		szH = pIDI->szDI_Hor *pZP->szWndClient.cx /pZP->szBackDrawing.cx;
		szV = pIDI->szDI_Ver *pZP->szWndClient.cy /pZP->szBackDrawing.cy;
	}
	else
	{
		if (pZP->nZoom >= NUM_ZOOM_1_TO_1)
		{
			posX = pIDI->ptDrawOrgX *(pZP->nZoom /NUM_ZOOM_1_TO_1);
			posY = pIDI->ptDrawOrgY *(pZP->nZoom /NUM_ZOOM_1_TO_1);

			szH = pIDI->szDI_Hor *(pZP->nZoom /NUM_ZOOM_1_TO_1);
			szV = pIDI->szDI_Ver *(pZP->nZoom /NUM_ZOOM_1_TO_1);
		}
		else
		{
			posX = pIDI->ptDrawOrgX /(NUM_ZOOM_1_TO_1 /pZP->nZoom);
			posY = pIDI->ptDrawOrgY /(NUM_ZOOM_1_TO_1 /pZP->nZoom);

			szH = pIDI->szDI_Hor /(NUM_ZOOM_1_TO_1 /pZP->nZoom);
			szV = pIDI->szDI_Ver /(NUM_ZOOM_1_TO_1 /pZP->nZoom);
		}
	}

	if (szH < MIN_SZ_DI_HOR)
	{
		szH = MIN_SZ_DI_HOR;
	}
	if (szV < MIN_SZ_DI_VER)
	{
		szV = MIN_SZ_DI_VER;
	}

	pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_ITEM][IDX_DISPI_PT_UL].x = 0;
	pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_ITEM][IDX_DISPI_PT_UL].y = 0;

	pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_ITEM][IDX_DISPI_PT_UR].x = GET_ROUNDED_VAL(szH *cos (double(pIDI->nDI_Angle) /180 *M_PI) -0 *sin (double(pIDI->nDI_Angle) /180 *M_PI));
	pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_ITEM][IDX_DISPI_PT_UR].y = GET_ROUNDED_VAL(szH *sin (double(pIDI->nDI_Angle) /180 *M_PI) +0 *cos (double(pIDI->nDI_Angle) /180 *M_PI));
	pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_ITEM][IDX_DISPI_PT_DR].x = GET_ROUNDED_VAL(szH *cos (double(pIDI->nDI_Angle) /180 *M_PI) -szV *sin (double(pIDI->nDI_Angle) /180 *M_PI));
	pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_ITEM][IDX_DISPI_PT_DR].y = GET_ROUNDED_VAL(szH *sin (double(pIDI->nDI_Angle) /180 *M_PI) +szV *cos (double(pIDI->nDI_Angle) /180 *M_PI));
	pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_ITEM][IDX_DISPI_PT_DL].x = GET_ROUNDED_VAL(0 *cos (double(pIDI->nDI_Angle) /180 *M_PI) -szV *sin (double(pIDI->nDI_Angle) /180 *M_PI));
	pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_ITEM][IDX_DISPI_PT_DL].y = GET_ROUNDED_VAL(0 *sin (double(pIDI->nDI_Angle) /180 *M_PI) +szV *cos (double(pIDI->nDI_Angle) /180 *M_PI));

	szTmpH = szH +2;
	szTmpV = szV +2;

	pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_SEL][IDX_DISPI_PT_UL].x = 0;
	pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_SEL][IDX_DISPI_PT_UL].y = 0;

	pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_SEL][IDX_DISPI_PT_UR].x = GET_ROUNDED_VAL(szTmpH *cos (double(pIDI->nDI_Angle) /180 *M_PI) -0 *sin (double(pIDI->nDI_Angle) /180 *M_PI));
	pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_SEL][IDX_DISPI_PT_UR].y = GET_ROUNDED_VAL(szTmpH *sin (double(pIDI->nDI_Angle) /180 *M_PI) +0 *cos (double(pIDI->nDI_Angle) /180 *M_PI));
	pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_SEL][IDX_DISPI_PT_DR].x = GET_ROUNDED_VAL(szTmpH *cos (double(pIDI->nDI_Angle) /180 *M_PI) -szTmpV *sin (double(pIDI->nDI_Angle) /180 *M_PI));
	pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_SEL][IDX_DISPI_PT_DR].y = GET_ROUNDED_VAL(szTmpH *sin (double(pIDI->nDI_Angle) /180 *M_PI) +szTmpV *cos (double(pIDI->nDI_Angle) /180 *M_PI));
	pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_SEL][IDX_DISPI_PT_DL].x = GET_ROUNDED_VAL(0 *cos (double(pIDI->nDI_Angle) /180 *M_PI) -szTmpV *sin (double(pIDI->nDI_Angle) /180 *M_PI));
	pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_SEL][IDX_DISPI_PT_DL].y = GET_ROUNDED_VAL(0 *sin (double(pIDI->nDI_Angle) /180 *M_PI) +szTmpV *cos (double(pIDI->nDI_Angle) /180 *M_PI));

	szTmpH = szH +6;
	szTmpV = szV +6;

	pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_LTPM][IDX_DISPI_PT_UL].x = 0;
	pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_LTPM][IDX_DISPI_PT_UL].y = 0;

	pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_LTPM][IDX_DISPI_PT_UR].x = GET_ROUNDED_VAL(szTmpH *cos (double(pIDI->nDI_Angle) /180 *M_PI) -0 *sin (double(pIDI->nDI_Angle) /180 *M_PI));
	pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_LTPM][IDX_DISPI_PT_UR].y = GET_ROUNDED_VAL(szTmpH *sin (double(pIDI->nDI_Angle) /180 *M_PI) +0 *cos (double(pIDI->nDI_Angle) /180 *M_PI));
	pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_LTPM][IDX_DISPI_PT_DR].x = GET_ROUNDED_VAL(szTmpH *cos (double(pIDI->nDI_Angle) /180 *M_PI) -szTmpV *sin (double(pIDI->nDI_Angle) /180 *M_PI));
	pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_LTPM][IDX_DISPI_PT_DR].y = GET_ROUNDED_VAL(szTmpH *sin (double(pIDI->nDI_Angle) /180 *M_PI) +szTmpV *cos (double(pIDI->nDI_Angle) /180 *M_PI));
	pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_LTPM][IDX_DISPI_PT_DL].x = GET_ROUNDED_VAL(0 *cos (double(pIDI->nDI_Angle) /180 *M_PI) -szTmpV *sin (double(pIDI->nDI_Angle) /180 *M_PI));
	pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_LTPM][IDX_DISPI_PT_DL].y = GET_ROUNDED_VAL(0 *sin (double(pIDI->nDI_Angle) /180 *M_PI) +szTmpV *cos (double(pIDI->nDI_Angle) /180 *M_PI));

	for (i=0; i<NUM_DISPI_PT; i++)
	{
		pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_ITEM][i].x += short(posX +pZP->ptOffset.x);
		pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_ITEM][i].y += short(posY +pZP->ptOffset.y);

		pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_SEL][i].x += short(posX +pZP->ptOffset.x -1);
		pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_SEL][i].y += short(posY +pZP->ptOffset.y -1);

		pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_LTPM][i].x += short(posX +pZP->ptOffset.x -3);
		pIDI->bbufPtDrawDisp[IDX_DISPI_RGN_LTPM][i].y += short(posY +pZP->ptOffset.y -3);
	}
}

int GetCurOpModeFromDI (INFO_DISP_ITEM *pIDI)
{
	BYTE nStat, nGroup;
	INFO_CTRL_DEV_ALL *pICDA = &glInfoGlobal.iCDA;
	ITEM_STAT_CCM *pBufISC = glInfoGlobal.unGVA.iGVA.pWMNC->GetBasePtrStatCCM ();

	

	if (pIDI->idxDevType == IDX_DEV_TYPE_USM)
	{
		
		nStat = pBufISC[pIDI->idxCCM].bufItem[pIDI->idxSCM].iStat.bufUSM_Stat[pIDI->idxUSM_LGM] &MASK_FOR_ICCS_USM_LGM_STAT;
		
		//장애인 구역은 파란색으로 표시 [S] 
		nGroup = pICDA->bbbufICDevUSM[pIDI->idxCCM][pIDI->idxSCM][pIDI->idxUSM_LGM].iDev.nGroup;
		if(nStat == IDX_OPM_SENS_LED_ON_GREEN){
			if(nGroup > 200 && nGroup < 216) nStat = IDX_OPM_SENS_LED_ON_BLUE;
		//장애인 구역은 파란색으로 표시 [E] 
		}
	}
	else if (pIDI->idxDevType == IDX_DEV_TYPE_LGM)
	{
		nStat = pBufISC[pIDI->idxCCM].bufItem[pIDI->idxSCM].iStat.bufLGM_Stat[pIDI->idxUSM_LGM] &MASK_FOR_ICCS_USM_LGM_STAT;
	}
	else
	{
		nStat = IDX_OPM_SENS_LED_OFF;
	}

	return nStat;
}
int ResetTimeForLTPM(INFO_DISP_ITEM *pIDI) // Long Term Parking Monitoring
{
	INFO_DEV_USM  *pInfoDevUsm = &glInfoGlobal.iCDA.bbbufICDevUSM[pIDI->idxCCM][pIDI->idxSCM][pIDI->idxUSM_LGM].iDev;

	if (pIDI->idxDevType == IDX_DEV_TYPE_USM)
	{
		if(pInfoDevUsm->bGreenCnt > 1){
			pInfoDevUsm->bStartParkingF = 0;
			pInfoDevUsm->bGreenCnt = 0;
			return 1;
		}
		else{
			pInfoDevUsm->bGreenCnt++;
			return 0;
		}

	}
	else return 0;

}
int GetTimeIndexForLTPM(INFO_DISP_ITEM *pIDI) // Long Term Parking Monitoring
{
	BYTE nStat;
	int timeIndex;
	SYSTEMTIME curTime;
	GetLocalTime(&curTime);
	int ndYear, ndMonth, npMonth, ndDay, npDay, ndHour, npHour , ndMinute, npMinute ;// npMonth = Plus Month

	INFO_DEV_USM  *pInfoDevUsm = &glInfoGlobal.iCDA.bbbufICDevUSM[pIDI->idxCCM][pIDI->idxSCM][pIDI->idxUSM_LGM].iDev;

	if (pIDI->idxDevType == IDX_DEV_TYPE_USM)
	{
		if(pInfoDevUsm->bStartParkingF == 0)
		{

			pInfoDevUsm->nLTPTimeRef = curTime;
			pInfoDevUsm->bStartParkingF = 1;
			return 0;
		}
		else
		{
			ndYear = curTime.wYear - pInfoDevUsm->nLTPTimeRef.wYear;
			npMonth = 12 * ndYear;
			ndMonth = npMonth + curTime.wMonth - pInfoDevUsm->nLTPTimeRef.wMonth ;
			npDay = 30 * ndMonth;
			ndDay = npDay + curTime.wDay  - pInfoDevUsm->nLTPTimeRef.wDay ;
			npHour = 24 *ndDay;
			ndHour = npHour + curTime.wHour - pInfoDevUsm->nLTPTimeRef.wHour;
			npMinute = 60 * ndHour;
			ndMinute = npMinute + curTime.wMinute - pInfoDevUsm->nLTPTimeRef.wMinute;

			// 3시간 : 180분, 6시간 : 360분, 9시간 : 540분, 12시간 : 720분, 24시간 : 1440분
			// 2시간 : 120분, 4시간 : 240분, 6시간 : 360분
			if(ndMinute < 180)
				return 0;
			else if (ndMinute < 360)
				return 1;
			else if (ndMinute < 540)
				return 2;
			else if (ndMinute < 720)
				return 3;
			else if (ndMinute < 1440)
				return 4;
			else if (ndMinute >= 1440)
				return 5;
			else
				return 0;


		}
	}

	return 0;
}

void GetCurStatFromBDI (
	INFO_BACK_DRAWING_ITEM *pIBDI
	, STAT_PARKING_AREA &stPaAll
	, STAT_PARKING_AREA &stPaB1F
	, STAT_PARKING_AREA &stPaB2F
	, STAT_PARKING_AREA &stPaB3F
	, STAT_PARKING_AREA &stPaB4F
)
{
	int i;
	BYTE nStat;
	INFO_DISP_ITEM *pIDI;
	ITEM_STAT_CCM *pBufISC = glInfoGlobal.unGVA.iGVA.pWMNC->GetBasePtrStatCCM ();

	//stPaAll.nTotal = 0;
	//stPaAll.nParked = 0;
	//stPaAll.nFree = 0;

	stPaB1F.nTotal = 0;
	stPaB1F.nParked = 0;
	stPaB1F.nFree = 0;

	stPaB2F.nTotal = 0;
	stPaB2F.nParked = 0;
	stPaB2F.nFree = 0;

	stPaB3F.nTotal = 0;
	stPaB3F.nParked = 0;
	stPaB3F.nFree = 0;

	stPaB4F.nTotal = 0;
	stPaB4F.nParked = 0;
	stPaB4F.nFree = 0;

	for (i=0; i<pIBDI->numDispItem; i++)
	{
		pIDI = &pIBDI->bufDispItem[i];

		if (pIDI->idxDevType != IDX_DEV_TYPE_USM)
		{
			continue;
		}

		
		//stPaAll.nTotal++;

		if(pIDI->idxCCM == 0){
			if (pIDI->idxSCM == 0 || pIDI->idxSCM == 1 || pIDI->idxSCM == 2 || pIDI->idxSCM == 3)
			{
				stPaB1F.nTotal++;
			}
			else if (pIDI->idxSCM == 4 || pIDI->idxSCM == 5 || pIDI->idxSCM == 6 || pIDI->idxSCM == 7 || pIDI->idxSCM == 8)
			{
				stPaB2F.nTotal++;
			}
		}
		//else if(pIDI->idxCCM == 1){
		//	stPaB2F.nTotal++;
		//}
		//else if(pIDI->idxCCM == 2){
		//	stPaB3F.nTotal++;
		//}
		//else if(pIDI->idxCCM == 3){
		//	stPaB4F.nTotal++;
		//}
		

		//else if(pIDI->idxCCM == 1){
		//	if (pIDI->idxSCM == 0 || pIDI->idxSCM == 1 || pIDI->idxSCM == 2)
		//	{
		//		stPa3F.nTotal++;
		//	}
		//	else if (pIDI->idxSCM == 3 || pIDI->idxSCM == 4 || pIDI->idxSCM == 5 )
		//	{
		//		stPa4F.nTotal++;
		//	}
		//	else if (pIDI->idxSCM == 6 || pIDI->idxSCM == 7 || pIDI->idxSCM == 8)
		//	{
		//		stPa5F.nTotal++;
		//	}
		//	////else if (pIDI->idxSCM == 9)
		//	//{
		//	//	stPa6F.nTotal = 196;
		//	//}
		//}

		nStat = pBufISC[pIDI->idxCCM].bufItem[pIDI->idxSCM].iStat.bufUSM_Stat[pIDI->idxUSM_LGM] & MASK_FOR_ICCS_USM_LGM_STAT;

		if (nStat == IDX_OPM_SENS_LED_ON_GREEN ||
			nStat == IDX_OPM_FORC_LED_ON_GREEN)
		{
			//stPaAll.nFree++;
			if(pIDI->idxCCM == 0){
				if (pIDI->idxSCM == 0 || pIDI->idxSCM == 1 || pIDI->idxSCM == 2 || pIDI->idxSCM == 3)
				{
					stPaB1F.nFree++;
				}
				else if (pIDI->idxSCM == 4 || pIDI->idxSCM == 5 || pIDI->idxSCM == 6 || pIDI->idxSCM == 7 || pIDI->idxSCM == 8)
				{
					stPaB2F.nFree++;
				}
				//stPaB1F.nFree++;
			}
	/*		else if(pIDI->idxCCM == 1){
				stPaB2F.nFree++;
			}
			else if(pIDI->idxCCM == 2){
				stPaB3F.nFree++;
			}
			else if(pIDI->idxCCM == 3){
				stPaB4F.nFree++;
			}*/
			//else if(pIDI->idxCCM == 1){
			//	if (pIDI->idxSCM == 0 || pIDI->idxSCM == 1 || pIDI->idxSCM == 2)
			//	{
			//		stPa3F.nFree++;
			//	}
			//	else if (pIDI->idxSCM == 3 || pIDI->idxSCM == 4 || pIDI->idxSCM == 5 )
			//	{
			//		stPa4F.nFree++;
			//	}
			//	else if (pIDI->idxSCM == 6 || pIDI->idxSCM == 7 || pIDI->idxSCM == 8)
			//	{
			//		stPa5F.nFree++;
			//	}
			//	//else if (pIDI->idxSCM == 9)
			//	//{
			//	//	stPa6F.nFree++;
			//	//}
			//}

		}
		else
		{
			//stPaAll.nParked++;

			if(pIDI->idxCCM == 0){
				if (pIDI->idxSCM == 0 || pIDI->idxSCM == 1 || pIDI->idxSCM == 2 || pIDI->idxSCM == 3)
				{
					stPaB1F.nParked++;
				}
				else if (pIDI->idxSCM == 4 || pIDI->idxSCM == 5 || pIDI->idxSCM == 6 || pIDI->idxSCM == 7 || pIDI->idxSCM == 8)
				{
					stPaB2F.nParked++;
				}
				
			}
			//else if(pIDI->idxCCM == 1){
			//	stPaB2F.nParked++;
			//}
			//else if(pIDI->idxCCM == 2){
			//	stPaB3F.nParked++;
			//}
			//else if(pIDI->idxCCM == 3){
			//	stPaB4F.nParked++;
			//}
			//else if(pIDI->idxCCM == 1){
			//	if (pIDI->idxSCM == 0 || pIDI->idxSCM == 1 || pIDI->idxSCM == 2)
			//	{
			//		stPa3F.nParked++;
			//	}
			//	else if (pIDI->idxSCM == 3 || pIDI->idxSCM == 4 || pIDI->idxSCM == 5 )
			//	{
			//		stPa4F.nParked++;
			//	}
			//	else if (pIDI->idxSCM == 6 || pIDI->idxSCM == 7 || pIDI->idxSCM == 8)
			//	{
			//		stPa5F.nParked++;
			//	}
			//	//else if (pIDI->idxSCM == 9)
			//	//{
			//	//	stPa6F.nParked++;
			//	//}
			//}
		}
	}
}


void GetCurStat_B1_Upper (int &nTotal, int &nParked, int &nFree)
{
	int i, j;
	BYTE nStat;
	ITEM_STAT_CCM *pBufISC = glInfoGlobal.unGVA.iGVA.pWMNC->GetBasePtrStatCCM ();

	nTotal = 0;
	nParked = 0;
	nFree = 0;

	for (i=13; i<=14; i++)
	{
		for (j=0; j<MAX_NUM_USM; j++)
		{
			if ((pBufISC[0].bufItem[i].iStat.bufUSM_Stat[j] &FLAG_ICCS_USM_USED) != 0)
			{
				nTotal++;
				nStat = pBufISC[0].bufItem[i].iStat.bufUSM_Stat[j] &MASK_FOR_ICCS_USM_LGM_STAT;

				if (nStat == IDX_OPM_SENS_LED_ON_GREEN ||
					nStat == IDX_OPM_FORC_LED_ON_GREEN)
				{
					nFree++;
				}
				else
				{
					nParked++;
				}
			}
		}
	}
}

void GetCurStat_B1_Lower (int &nTotal, int &nParked, int &nFree)
{
	int i, j;
	BYTE nStat;
	ITEM_STAT_CCM *pBufISC = glInfoGlobal.unGVA.iGVA.pWMNC->GetBasePtrStatCCM ();

	nTotal = 0;
	nParked = 0;
	nFree = 0;

	for (i=10; i<=12; i++)
	{
		for (j=0; j<MAX_NUM_USM; j++)
		{
			if ((pBufISC[0].bufItem[i].iStat.bufUSM_Stat[j] &FLAG_ICCS_USM_USED) != 0)
			{
				nTotal++;
				nStat = pBufISC[0].bufItem[i].iStat.bufUSM_Stat[j] &MASK_FOR_ICCS_USM_LGM_STAT;

				if (nStat == IDX_OPM_SENS_LED_ON_RED ||
					nStat == IDX_OPM_FORC_LED_ON_RED)
				{
					nParked++;
				}
				else
				{
					nFree++;
				}
			}
		}
	}
}

void UpdateCurDispStat ()
{
	int i;

	for (i=0; i<glInfoGlobal.iBDA.numBDI; i++)
	{
		if (glInfoGlobal.iBDA.bufBDI[i].iVS.pView != NULL)
		{
			glInfoGlobal.iBDA.bufBDI[i].iVS.pView->SetBD_DispWndUpdateFlag ();
		}
	}

	if (glInfoGlobal.unGVA.iGVA.pPaneBD != NULL)
	{
		glInfoGlobal.unGVA.iGVA.pPaneBD->UpdateCurStat ();
	}
}


int MakeEBoardSendData (int nDST, CString strSnd, int *bufClr, BYTE *bufSnd)
{
	INFO_BACK_DRAWING_ITEM *pIBDI;
	STAT_PARKING_AREA stPaAll, stPaB1F,stPaB2F, stPaB3F, stPaB4F;
	int bufClr2[MAX_PATH];
	int szTxt = strSnd.GetLength ();
	BYTE *pBufSnd;
	int i, nLEN;

	pIBDI = &glInfoGlobal.iBDA.bufBDI[glInfoGlobal.iBDA.bufIdxMainBDI[1]];
	GetCurStatFromBDI (pIBDI, stPaAll, stPaB1F,stPaB2F, stPaB3F, stPaB4F);


	for (i=0; i<MAX_PATH; i++)
	{
		bufClr[i] = IDX_EBD_CLR_GREEN;
	}

	//if(stPa6F.nFree<10){
	//	for(i=0; i<6; i++)
	//		bufClr[i] = IDX_EBD_CLR_RED;

	//}
	//if(stPa5F.nFree<10){
	//	for(i=6; i<12; i++)
	//		bufClr[i] = IDX_EBD_CLR_RED;

	//}
	//if(stPa4F.nFree<10){
	//	for(i=12; i<18; i++)
	//		bufClr[i] = IDX_EBD_CLR_RED;

	//}
	//if(stPa3F.nFree<10){
	//	for(i=18; i<24; i++)
	//		bufClr[i] = IDX_EBD_CLR_RED;

	//}
	//if(stPaB2F.nFree<10){
	//	for(i=24; i<30; i++)
	//		bufClr[i] = IDX_EBD_CLR_RED;
	//}

	pBufSnd = &bufSnd[0];

	*pBufSnd++ = 0x10;	// DLE
	*pBufSnd++ = 0x02;	// STX
	*pBufSnd++ = nDST;	// DST

	nLEN = 12 +szTxt +szTxt;
	*pBufSnd++ = (nLEN >>8) &0xff;	// LEN(H)
	*pBufSnd++ = (nLEN >>0) &0xff;	// LEN(L)

	*pBufSnd++ = 0x54;	// CMD
	*pBufSnd++ = 0x00;	// Param 문구블록
	*pBufSnd++ = 0x01;	// Param 표시방법, 배경이미지
	*pBufSnd++ = 0xf0;	// Param 반복횟수
	*pBufSnd++ = 0x93;	// Param 문구 폰트크기, 문구 표시방법, 문구 전송방법
	*pBufSnd++ = 0x00;	// Param 화면분할위치
	*pBufSnd++ = 0x00;	// Param 문구 글자코드
	*pBufSnd++ = 0x00;	// Param 분할화면 효과
	*pBufSnd++ = 0x00;	// Param 메인화면 효과
	*pBufSnd++ = 0xff;	// Param 효과속도
	*pBufSnd++ = 0xff;	// Param 표시시간
	*pBufSnd++ = 0x00;	// Param 문구 수직위치

	// Param 글자 색상[S]
	for (i=0; i<szTxt; i++)
	{
		*pBufSnd++ = bufClr[i];
	}
	// Param 글자 색상[E]

	// Param 문구[S]
	for (i=0; i<szTxt; i++)
	{
		*pBufSnd++ = strSnd[i];
	}
	// Param 문구[E]

	*pBufSnd++ = 0x10;	// DLE
	*pBufSnd++ = 0x03;	// STX

//	pComm->Send (bufSnd, 5 +nLEN +2);

	// Write Debug Data[S]
	char strDbg[256];
	for (i=0; i<strSnd.GetLength (); i++)
	{
		strDbg[i] = strSnd[i];
	}
	strDbg[i +0] = '\n';
	strDbg[i +1] = 0;
//	AddReport (strDbg);
	// Write Debug Data[E]

	return (5 +nLEN +2);
}

int GetNumOfAllSCM ()
{
	int numSCM, i, j;
	INFO_CTRL_DEV_ALL *pICDA = &glInfoGlobal.iCDA;

	numSCM = 0;
	for (i=0; i<MAX_NUM_CCM; i++)
	{
		if (pICDA->bufICDevCCM[i].bUse == TRUE)
		{
			for (j=0; j<MAX_NUM_SCM; j++)
			{
				if (pICDA->bbufICDevSCM[i][j].bUse == TRUE)
				{
					numSCM++;
				}
			}
		}
	}

	return numSCM;
}

int GetNumOfAllUSM ()
{
	int numUSM, i, j, k;
	INFO_CTRL_DEV_ALL *pICDA = &glInfoGlobal.iCDA;

	numUSM = 0;
	for (i=0; i<MAX_NUM_CCM; i++)
	{
		if (pICDA->bufICDevCCM[i].bUse == TRUE)
		{
			for (j=0; j<MAX_NUM_SCM; j++)
			{
				if (pICDA->bbufICDevSCM[i][j].bUse == TRUE)
				{
					for (k=0; k<MAX_NUM_USM; k++)
					{
						if (pICDA->bbbufICDevUSM[i][j][k].bUse == TRUE)
						{
							numUSM++;
						}
					}
				}
			}
		}
	}

	return numUSM;
}

int GetNumOfAllLGM ()
{
	int numLGM, i, j, k;
	INFO_CTRL_DEV_ALL *pICDA = &glInfoGlobal.iCDA;

	numLGM = 0;
	for (i=0; i<MAX_NUM_CCM; i++)
	{
		if (pICDA->bufICDevCCM[i].bUse == TRUE)
		{
			for (j=0; j<MAX_NUM_SCM; j++)
			{
				if (pICDA->bbufICDevSCM[i][j].bUse == TRUE)
				{
					for (k=0; k<MAX_NUM_LGM; k++)
					{
						if (pICDA->bbbufICDevLGM[i][j][k].bUse == TRUE)
						{
							numLGM++;
						}
					}
				}
			}
		}
	}

	return numLGM;
}
