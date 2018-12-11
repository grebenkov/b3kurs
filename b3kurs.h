// b3kurs.h : main header file for the b3kurs application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// Cb3kursApp:
// See b3kurs.cpp for the implementation of this class
//

class Cb3kursApp : public CWinApp
{
public:
	Cb3kursApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Cb3kursApp theApp;