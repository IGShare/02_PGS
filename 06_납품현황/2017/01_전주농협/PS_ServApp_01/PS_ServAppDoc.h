
// PS_ServAppDoc.h : CPS_ServAppDoc Ŭ������ �������̽�
//


#pragma once


class CPS_ServAppDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CPS_ServAppDoc();
	DECLARE_DYNCREATE(CPS_ServAppDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �����Դϴ�.
public:
	virtual ~CPS_ServAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};


