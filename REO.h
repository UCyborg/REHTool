// REO.h : main header file for the REO application
//

#if !defined(AFX_REO_H__1FA16BC5_D791_11D5_8C27_C46B1940A128__INCLUDED_)
#define AFX_REO_H__1FA16BC5_D791_11D5_8C27_C46B1940A128__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CREOApp:
// See REO.cpp for the implementation of this class
//

class CREOApp : public CWinApp
{
public:
	CREOApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CREOApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CREOApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REO_H__1FA16BC5_D791_11D5_8C27_C46B1940A128__INCLUDED_)
