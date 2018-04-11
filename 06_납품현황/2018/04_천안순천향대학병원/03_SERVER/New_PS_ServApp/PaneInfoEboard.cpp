// PaneInfoEboard.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "PS_ServApp.h"
#include "PaneInfoEboard.h"


// CPaneInfoEboard

enum {
	IDX_ML_COL_DEV_CCM,
	IDX_ML_COL_DEV_SCM,
	IDX_ML_COL_DEV_USM,
	IDX_ML_COL_DEV_LGM,
	NUM_MAIN_LIST_COLUMN
};

const int GL_SZ_ML_COL_HDR[NUM_MAIN_LIST_COLUMN] = {
	40, 40, 40, 100
};
const LPSTR GL_STR_ML_COL_HDR[NUM_MAIN_LIST_COLUMN] = {
	_T("CCM"),
	_T("SCM"),
	_T("USM"),
	_T("SN"),
};

const LPSTR GL_STR_FMT_EBD_0_OP_MODE[1] = {
	_T("현재 상태 표시"),
};

#define IDC_MAIN_LIST					1000

IMPLEMENT_DYNAMIC(CPaneInfoEboard, CDockablePane)

CPaneInfoEboard::CPaneInfoEboard()
{

}

CPaneInfoEboard::~CPaneInfoEboard()
{
}


BEGIN_MESSAGE_MAP(CPaneInfoEboard, CDockablePane)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_MAIN_LIST, OnItemClickedLicMain)
END_MESSAGE_MAP()



// CPaneInfoEboard 메시지 처리기입니다.

int CPaneInfoEboard::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	CRect rcClient;

	GetClientRect (&rcClient);

	m_pLicMain = new CListCtrl;
	m_pLicMain->Create (WS_CHILD |WS_VISIBLE |LVS_SINGLESEL |LVS_SHOWSELALWAYS |LVS_REPORT,
		rcClient, this, IDC_MAIN_LIST);

	m_pLicMain->SetExtendedStyle (LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES |LVS_EX_ONECLICKACTIVATE);

	int i;
	LVCOLUMN col;
	CString strTmp;

	col.mask = LVCF_FMT |LVCF_TEXT |LVCF_WIDTH;

	for (i=0; i<NUM_MAIN_LIST_COLUMN; i++)
	{
		col.cx = GL_SZ_ML_COL_HDR[i];
		col.pszText = GL_STR_ML_COL_HDR[i];
		col.fmt = LVCFMT_CENTER;

		m_pLicMain->InsertColumn (i, &col);
	}

	UpdateMainList (TRUE);

	return 0;
}

void CPaneInfoEboard::OnDestroy()
{
	CDockablePane::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	delete m_pLicMain;
}

void CPaneInfoEboard::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CRect rcClient;
	GetClientRect (&rcClient);

	m_pLicMain->MoveWindow (&rcClient);
}

void CPaneInfoEboard::UpdateMainList (BOOL bFullUpdate)
{
	return;/////////////////////////////////////////////////////////
	int i, j;
	BOOL noSelected = TRUE;
	INFO_CTRL_DEV_ALL *pICDA = &glInfoGlobal.iCDA;
	INFO_BACK_DRAWING_ALL *pIBDA = &glInfoGlobal.iBDA;
	INFO_BACK_DRAWING_ITEM *pIBDI;
	INFO_DISP_ITEM *pIDI;
	CString strTmp;

	for(j = 0; j<pIBDA->numBDI; j++)
	{
		pIBDI = &pIBDA->bufBDI[pIBDA->bufIdxMainBDI[j]];

		for (i=0; i<pIBDI->numDispItem; i++)
		{
			pIDI = &pIBDI->bufDispItem[i];
			if(pIDI->bSelected == TRUE)
			{
				noSelected = FALSE;
				m_pLicMain->DeleteAllItems ();

				strTmp.Format("%0.2d", pIDI->idxCCM+1);
				m_pLicMain->InsertItem (0, LPCTSTR(strTmp));
				strTmp.Format("%0.2d", pIDI->idxSCM+1);
				m_pLicMain->SetItem (0, IDX_ML_COL_DEV_SCM, LVIF_TEXT, LPCTSTR(strTmp), 0, 0, 0, 0);
				strTmp.Format("%0.3d", pIDI->idxUSM_LGM+1);
				m_pLicMain->SetItem (0, IDX_ML_COL_DEV_USM, LVIF_TEXT, LPCTSTR(strTmp), 0, 0, 0, 0);
				strTmp.Format("%0.3d", pICDA->bbbufICDevUSM[pIDI->idxCCM][pIDI->idxSCM][pIDI->idxUSM_LGM].iDev.nSN.nDevNum);
				m_pLicMain->SetItem (0, IDX_ML_COL_DEV_LGM, LVIF_TEXT, LPCTSTR(strTmp), 0, 0, 0, 0);

				//strTmp.Format("%s", _T("Serial"));
				//m_pLicMain->InsertItem (1, LPCTSTR(strTmp));
				//

				//strTmp.Format("%d", pICDA->bbbufICDevUSM[pIDI->idxCCM][pIDI->idxSCM][pIDI->idxUSM_LGM].iDev.nSN.nDevNum);
				//m_pLicMain->SetItem (1, IDX_ML_COL_DEV_USM, LVIF_TEXT, LPCTSTR(strTmp), 0, 0, 0, 0);
			}
		}
	}
	if(noSelected == TRUE)
	{
		m_pLicMain->DeleteAllItems ();
	}
}

void CPaneInfoEboard::OnItemClickedLicMain(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	*pResult = 0;

	if (pNMListView->uNewState == 0)
		return;	// No change
}
