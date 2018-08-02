#if !defined(AFX_SPISDOBVER_H__9113FC24_00F2_11D6_8C27_809C0D68C62F__INCLUDED_)
#define AFX_SPISDOBVER_H__9113FC24_00F2_11D6_8C27_809C0D68C62F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SpisDobVer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SpisDobVer dialog

class SpisDobVer : public CDialog
{
// Construction
public:
	CString sStTe;
	CString sRE;
	SpisDobVer(CString sST, CString sRT, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SpisDobVer)
	enum { IDD = IDD_SPISDOBVER };
	CRichEditCtrl	m_SpisDobVer;
	CStatic	m_DobVer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SpisDobVer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SpisDobVer)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPISDOBVER_H__9113FC24_00F2_11D6_8C27_809C0D68C62F__INCLUDED_)
