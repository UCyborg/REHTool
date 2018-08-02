// SpisDobVer.cpp : implementation file
//

#include "stdafx.h"
#include "reo.h"
#include "SpisDobVer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SpisDobVer dialog


SpisDobVer::SpisDobVer(CString sST, CString sRT, CWnd* pParent /*=NULL*/)
	: CDialog(SpisDobVer::IDD, pParent)
{
	//{{AFX_DATA_INIT(SpisDobVer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
	sRE=sRT;sStTe=sST;

}


void SpisDobVer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SpisDobVer)
	DDX_Control(pDX, IDC_SPISDOBVER, m_SpisDobVer);
	DDX_Control(pDX, IDC_DOBVER, m_DobVer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SpisDobVer, CDialog)
	//{{AFX_MSG_MAP(SpisDobVer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SpisDobVer message handlers

BOOL SpisDobVer::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_DobVer.SetWindowText((LPCTSTR)sStTe);
	m_SpisDobVer.SetWindowText((LPCTSTR)sRE);
	m_SpisDobVer.LimitText(5000000);

	LOGFONT lf1;CFont font1;
	memset(&lf1, 0, sizeof(LOGFONT));       // zero out structure
	lf1.lfHeight = 16;                      // request a 12-pixel-height font
	strcpy(lf1.lfFaceName, "Courier"); 
	lf1.lfPitchAndFamily=DEFAULT_PITCH;//FIXED_PITCH;// request a face name "Arial"
	if(font1.CreateFontIndirect(&lf1))  // create the font
		m_SpisDobVer.SetFont(&font1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
