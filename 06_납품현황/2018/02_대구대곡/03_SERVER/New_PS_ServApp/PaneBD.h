#pragma once


// CPaneBD

class CPaneBD : public CDockablePane
{
	DECLARE_DYNAMIC(CPaneBD)

public:
	CPaneBD();
	virtual ~CPaneBD();

	CListCtrl *m_pLicMain;
	BOOL m_bNeedUpdateStat;

	void UpdateCurStat ();
	void UpdateMainList (BOOL bFullUpdate);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnItemClickedLicMain(NMHDR* pNMHDR, LRESULT* pResult);
};


