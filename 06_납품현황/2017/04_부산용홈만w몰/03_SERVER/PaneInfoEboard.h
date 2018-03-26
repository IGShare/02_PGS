#pragma once


// CPaneInfoEboard

class CPaneInfoEboard : public CDockablePane
{
	DECLARE_DYNAMIC(CPaneInfoEboard)

public:
	CPaneInfoEboard();
	virtual ~CPaneInfoEboard();

	CListCtrl *m_pLicMain;

	void UpdateMainList ();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnItemClickedLicMain(NMHDR* pNMHDR, LRESULT* pResult);
};


