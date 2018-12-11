// b3kursDoc.h : interface of the Cb3kursDoc class
//
#include "btreedump.h"
#include <string>

#pragma once

class Cb3kursDoc : public CDocument
{
protected: // create from serialization only
	Cb3kursDoc();
	DECLARE_DYNCREATE(Cb3kursDoc)

// Attributes
public:
	btreedump::b_treedump *bt;

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~Cb3kursDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


