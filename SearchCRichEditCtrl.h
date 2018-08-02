#if !defined(AFX_SEARCHCRICHEDITCTRL_H__678CAC61_F7A3_11D5_8C27_A12253491529__INCLUDED_)
#define AFX_SEARCHCRICHEDITCTRL_H__678CAC61_F7A3_11D5_8C27_A12253491529__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchCRichEditCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSearchCRichEditCtrl dialog

class CSearchCRichEditCtrl : public CDialog
{
// Construction
public:
	long PosPoiska;
	CRichEditCtrl *RE;
	CSearchCRichEditCtrl(CRichEditCtrl *re,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSearchCRichEditCtrl)
	enum { IDD = IDD_SEARCH };
	CEdit	m_IskomText;
	CButton	m_SearchString;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchCRichEditCtrl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSearchCRichEditCtrl)
	virtual BOOL OnInitDialog();
	afx_msg void OnSearchstring();
	afx_msg void OnChangeIskomtext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHCRICHEDITCTRL_H__678CAC61_F7A3_11D5_8C27_A12253491529__INCLUDED_)
