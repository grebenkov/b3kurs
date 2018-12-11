// b3kursView.cpp : implementation of the Cb3kursView class
//

#include "stdafx.h"
#include "b3kurs.h"

#include "MainFrm.h"
#include "b3kursDoc.h"
#include "b3kursView.h"
#include <string>
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cb3kursView

IMPLEMENT_DYNCREATE(Cb3kursView, CHtmlView)

BEGIN_MESSAGE_MAP(Cb3kursView, CHtmlView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
	ON_BN_CLICKED(IDC_ADDITEM, OnAddItem)
	ON_BN_CLICKED(IDC_DELITEM, OnDelItem)
END_MESSAGE_MAP()

// Cb3kursView construction/destruction

Cb3kursView::Cb3kursView()
{
	// TODO: add construction code here

}

Cb3kursView::~Cb3kursView()
{
}

BOOL Cb3kursView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

void Cb3kursView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();
}

void Cb3kursView::OnAddItem()
{
	int it;
	CString val;
	static_cast<CMainFrame*>(AfxGetMainWnd())->m_wndDlgBar.GetDlgItem(IDC_ELEM)->GetWindowText(val);
	it = atoi(val);
	if (!GetDocument()->bt->insert(it)) {
		AfxMessageBox("Такой ключ уже имеется!");
	}
	GetDocument()->UpdateAllViews(NULL);
}

void Cb3kursView::OnDelItem()
{
	int it;
	CString val;
	static_cast<CMainFrame*>(AfxGetMainWnd())->m_wndDlgBar.GetDlgItem(IDC_ELEM)->GetWindowText(val);
	it = atoi(val);
	if (!GetDocument()->bt->remove(it)) {
		AfxMessageBox("Такого ключа в дереве нет!");
	}
	GetDocument()->UpdateAllViews(NULL);
}


// Cb3kursView printing



// Cb3kursView diagnostics

#ifdef _DEBUG
void Cb3kursView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void Cb3kursView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

Cb3kursDoc* Cb3kursView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cb3kursDoc)));
	return (Cb3kursDoc*)m_pDocument;
}
#endif //_DEBUG


// Cb3kursView message handlers

void Cb3kursView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// TODO: Add your specialized code here and/or call the base class
	std::string d;
	d = GetDocument()->bt->dump();
	CString tmp;
	tmp.GetEnvironmentVariable("TEMP");
	tmp += "\\btree.htm";
	std::ofstream of(tmp);
	of << d;
	of.close();
	Navigate2(tmp);
}
