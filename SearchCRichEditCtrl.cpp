// SearchCRichEditCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "REO.h"
#include "SearchCRichEditCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchCRichEditCtrl dialog


CSearchCRichEditCtrl::CSearchCRichEditCtrl(CRichEditCtrl *re,CWnd* pParent /*=NULL*/)
	: CDialog(CSearchCRichEditCtrl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchCRichEditCtrl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	RE=re;
}


void CSearchCRichEditCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchCRichEditCtrl)
	DDX_Control(pDX, IDC_ISKOMTEXT, m_IskomText);
	DDX_Control(pDX, IDC_SEARCHSTRING, m_SearchString);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchCRichEditCtrl, CDialog)
	//{{AFX_MSG_MAP(CSearchCRichEditCtrl)
	ON_BN_CLICKED(IDC_SEARCHSTRING, OnSearchstring)
	ON_EN_CHANGE(IDC_ISKOMTEXT, OnChangeIskomtext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchCRichEditCtrl message handlers

BOOL CSearchCRichEditCtrl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_SearchString.SetWindowText("Найти сначала");
	m_IskomText.SetWindowText("texture");
	PosPoiska=0;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSearchCRichEditCtrl::OnSearchstring() 
{
	// TODO: Add your control notification handler code here
		FINDTEXTEX ft;long n;char buf[1000], *is;
		ft.chrg.cpMax=RE->GetTextLength();ft.chrg.cpMin=PosPoiska;
//		ft.chrg.cpMax=2200;ft.chrg.cpMin=m_MyRic.GetTextLength();
//		ft.chrgText.cpMax=m_MyRic.GetTextLength();ft.chrgText.cpMin=2200;//m_MyRic.GetTextLength();
		is=new char[m_IskomText.GetLimitText()+10];
		m_IskomText.GetWindowText(is,m_IskomText.GetLimitText());
		ft.lpstrText=is;
		n=RE->FindText( FR_MATCHCASE, &ft);
//		sprintf(buf,"n=%d",n);
//		AfxMessageBox(buf);
		if (n != -1)
		{
			PosPoiska=ft.chrgText.cpMax;
			RE->SetSel(ft.chrgText);
			long nl=RE->LineFromChar(PosPoiska);
			RE->LineScroll(-RE->GetLineCount());
			RE->LineScroll(nl-1);
		}
		else 
		{
			sprintf(buf,"Текст '%s' не найден.",is);
			AfxMessageBox(buf);
		};
		delete[] is;
		if(PosPoiska>0) m_SearchString.SetWindowText("Найти далее");
	
}

void CSearchCRichEditCtrl::OnChangeIskomtext() 
{
	// TODO: Add your control notification handler code here
	m_SearchString.SetWindowText("Найти сначала");
	RE->LineScroll(-RE->GetLineCount());
	PosPoiska=0;
}
