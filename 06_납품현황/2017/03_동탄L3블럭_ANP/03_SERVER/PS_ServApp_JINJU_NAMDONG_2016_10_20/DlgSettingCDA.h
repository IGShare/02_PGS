#pragma once


enum {
	IDX_LIC_CCM_COL_DEV_ID,
	IDX_LIC_CCM_COL_DEV_NAME,
	IDX_LIC_CCM_COL_SN,
	IDX_LIC_CCM_COL_NUM_SCM,

	NUM_LIC_CCM_COLUMN
};
const int GL_SZ_CX_LIC_CCM_COLUMN[NUM_LIC_CCM_COLUMN] = {
	60, 100, 100, 60
};
char *const GL_STR_LIC_CCM_COLUMN[NUM_LIC_CCM_COLUMN] = {
	"DevID",
	"Name",
	"S/N",
	"NumSCM",
};

enum {
	IDX_LIC_SCM_COL_DEV_ID,
	IDX_LIC_SCM_COL_DEV_NAME,
	IDX_LIC_SCM_COL_SN,
	IDX_LIC_SCM_COL_NUM_USM,
	IDX_LIC_SCM_COL_NUM_LGM,

	NUM_LIC_SCM_COLUMN
};
const int GL_SZ_CX_LIC_SCM_COLUMN[NUM_LIC_SCM_COLUMN] = {
	60, 100, 100, 60, 60
};
char *const GL_STR_LIC_SCM_COLUMN[NUM_LIC_SCM_COLUMN] = {
	"DevID",
	"Name",
	"S/N",
	"NumUSM",
	"NumLGM",
};

enum {
	IDX_LIC_USM_COL_DEV_ID,
	IDX_LIC_USM_COL_DEV_NAME,
	IDX_LIC_USM_COL_SN,
	IDX_LIC_USM_COL_DEV_ID_LGM,
	IDX_LIC_USM_COL_MAX_DET_DIST,
	IDX_LIC_USM_COL_ADC_AMP_LV,
	IDX_LIC_USM_COL_ADC_SNS_LV,
	IDX_LIC_USM_COL_TX_BURST_CNT,

	NUM_LIC_USM_COLUMN
};
const int GL_SZ_CX_LIC_USM_COLUMN[NUM_LIC_USM_COLUMN] = {
	60, 100, 100, 75, 60, 60, 60, 60
};
char *const GL_STR_LIC_USM_COLUMN[NUM_LIC_USM_COLUMN] = {
	"DevID",
	"Name",
	"S/N",
	"Linked LGM",
	"Max Dist",
	"ADC Amp",
	"ADC Sns",
	"TX Cnt",
};

enum {
	IDX_LIC_LGM_COL_DEV_ID,
	IDX_LIC_LGM_COL_DEV_NAME,
	IDX_LIC_LGM_COL_SN,

	NUM_LIC_LGM_COLUMN
};
const int GL_SZ_CX_LIC_LGM_COLUMN[NUM_LIC_LGM_COLUMN] = {
	60, 100, 100
};
char *const GL_STR_LIC_LGM_COLUMN[NUM_LIC_LGM_COLUMN] = {
	"DevID",
	"Name",
	"S/N",
};

enum {
	IDX_LIC_BI_IDLE,
	IDX_LIC_BI_OK,
	IDX_LIC_BI_NOT_CONN,
	IDX_LIC_BI_NOT_INIT,
	IDX_LIC_BI_COMM_ERROR,
	IDX_LIC_BI_LED_SENS_OFF,
	IDX_LIC_BI_LED_SENS_GREEN,
	IDX_LIC_BI_LED_SENS_RED,
	IDX_LIC_BI_LED_FORC_OFF,
	IDX_LIC_BI_LED_FORC_GREEN,
	IDX_LIC_BI_LED_FORC_RED,
	IDX_LIC_BI_LED_FORC_BLINKING,

	NUM_LIC_BITMAP
};
#define COLOR_LIC_MASK		RGB(255, 255, 255)

enum {
	IDX_POPM_SETTING_USM,
	IDX_POPM_SETTING_LGM,
	IDX_POPM_SETTING_USM_OP_ONLY,
	IDX_POPM_SENSING_ON_OFF_SCM,

	NUM_POPUP_MENU
};

class CWrapManNetComm;
struct ITEM_STAT_CCM;

// CDlgSettingCDA 대화 상자입니다.

class CDlgSettingCDA : public CDialog
{
	DECLARE_DYNAMIC(CDlgSettingCDA)

public:
	CDlgSettingCDA(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgSettingCDA();

	CWrapManNetComm *m_pWMNC;
	ITEM_STAT_CCM *m_pBufStatCCM;

	int m_idxSelCCM;
	int m_idxSelSCM;

	int m_numSel_USM;
	int m_numSel_LGM;
	int *m_bufIdxSel_USM;
	int *m_bufIdxSel_LGM;

	CImageList m_ilAllLC;

	int m_idxCCM_from_idxList[MAX_NUM_CCM];
	int m_idxSCM_from_idxList[MAX_NUM_SCM];
	int m_idxUSM_from_idxList[MAX_NUM_USM];
	int m_idxLGM_from_idxList[MAX_NUM_LGM];

	void UpdateLiC_CCM (BOOL bFullUpdate);
	void UpdateLiC_SCM (BOOL bFullUpdate);
	void UpdateLiC_USM (BOOL bFullUpdate);
	void UpdateLiC_LGM (BOOL bFullUpdate);

	int m_bufIdxImgState_CCM[MAX_NUM_CCM];
	int m_bufIdxImgState_SCM[MAX_NUM_SCM];
	int m_bufIdxImgState_USM[MAX_NUM_USM];
	int m_bufIdxImgState_LGM[MAX_NUM_LGM];

	void AddUSM (BOOL bMultiAdd);
	void AddLGM (BOOL bMultiAdd);

	void GetCurSelUSM ();
	void GetCurSelLGM ();

	int GetLicIdxImg_CCM (int idxCCM);
	int GetLicIdxImg_SCM (int idxCCM, int idxSCM);
	int GetLicIdxImg_USM (int idxCCM, int idxSCM, int idxUSM);
	int GetLicIdxImg_LGM (int idxCCM, int idxSCM, int idxLGM);

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_SETTING_CDA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CListCtrl m_licCCM;
	CListCtrl m_licSCM;
	CListCtrl m_licUSM;
	CListCtrl m_licLGM;
	CStatic m_staBoxCCM;
	CStatic m_staBoxSCM;
	CStatic m_staBoxUSM;
	CStatic m_staBoxLGM;
	afx_msg void OnLvnItemchangedLicCcm(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedLicScm(NMHDR *pNMHDR, LRESULT *pResult);
};
