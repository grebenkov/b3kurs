// b3kursView.h : interface of the Cb3kursView class
//


#pragma once


class Cb3kursView : public CHtmlView
{
protected: // create from serialization only
	Cb3kursView();
	DECLARE_DYNCREATE(Cb3kursView)

// Attributes
public:
	Cb3kursDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~Cb3kursView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnAddItem();
	afx_msg void OnDelItem();
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};

#ifndef _DEBUG  // debug version in b3kursView.cpp
inline Cb3kursDoc* Cb3kursView::GetDocument() const
   { return reinterpret_cast<Cb3kursDoc*>(m_pDocument); }
#endif

