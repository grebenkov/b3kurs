// b3kursDoc.cpp : implementation of the Cb3kursDoc class
//

#include "stdafx.h"
#include "b3kurs.h"

#include "b3kursDoc.h"
#include "btreedump.h"
#include <string>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cb3kursDoc

IMPLEMENT_DYNCREATE(Cb3kursDoc, CDocument)

BEGIN_MESSAGE_MAP(Cb3kursDoc, CDocument)
END_MESSAGE_MAP()


// Cb3kursDoc construction/destruction

Cb3kursDoc::Cb3kursDoc()
{
	// TODO: add one-time construction code here
	bt = NULL;
}

Cb3kursDoc::~Cb3kursDoc()
{
	delete bt;
}

BOOL Cb3kursDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	delete bt;
	bt = new btreedump::b_treedump;

	return TRUE;
}




// Cb3kursDoc serialization

void Cb3kursDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// Cb3kursDoc diagnostics

#ifdef _DEBUG
void Cb3kursDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cb3kursDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cb3kursDoc commands
