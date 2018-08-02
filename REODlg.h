// REODlg.h : header file
//

#if !defined(AFX_REODLG_H__1FA16BC7_D791_11D5_8C27_C46B1940A128__INCLUDED_)
#define AFX_REODLG_H__1FA16BC7_D791_11D5_8C27_C46B1940A128__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CREODlg dialog

#include "MyType.h"
#include "SpisDobVer.h"
#include "SearchCRichEditCtrl.h"
#define MAXSTRING 99999

class CREODlg : public CDialog
{
// Construction
public:
	LOGFONT *RabFont;
	bool ZadPoisk(CString s);
	bool EstReo;
	bool IsRec;
	bool PravPreobr;
	int N_M_P;
	float MasPrebr[4][3];
	volatile bool process;
	CString ImIsxFile;
	void UstEdit(int num);
	CString GetSodEdit();
	int ReadEdit(bool PrRead=true);
	CString ImVyvodFile;
	CString ImNewType;
	bool NewType;
	CString ImFile[2];
	bool Vyvod(int tp);
//	int KolNeperesPeres;
//	int KolNeperes;
//	int KolPeres;
	int TypeFile;
	int Okrugl(double a);
	bool SaveBMP(HBITMAP hbmp, LPCSTR filename);
	POLYGON *newPol;
	int kNewMat;
	BMPINF *NewMat;
	MASINT *NewNumMat;
	bool Peres(int n1 ,  int n2);
	bool Optimum;
	int OLDkPol;
	int OLDkMat;
	REZ RezREO;
	INFOPTIM InfOptim;
	long PosPoiska;
	char Dir[100];
	char Drive[100];
	CString PatREO;
	bool ReadBMP(CBitmap *b, CString name);
	BMPINF *BmpInf;
	bool SavePol(CStdioFile *ff, CStdioFile *ff2);
	bool SeveMat(CStdioFile *ff, CStdioFile *ff2, CString *pp);
	int Kmat;
	int Nmat;
	int Npol;
	int Kpol;
	POLYGON *Pol;
	int kPol;
	bool IsFile;
	TREUG *Ver;
	int kVer;
	CString *masBMP;
	int kMat;
	bool Prav;
	int kS;
	CString *S;
	CREODlg(CWnd* pParent = NULL);	// standard constructor
	~CREODlg();

// Dialog Data
	//{{AFX_DATA(CREODlg)
	enum { IDD = IDD_REO_DIALOG };
	CButton	m_PoskKn;
	CEdit	m_Poisk;
	CRichEditCtrl	m_MyRic;
	CButton	m_Udal;
	CButton	m_Put;
	CEdit	m_NewIma;
	CButton	m_TypeFile;
	CStatic	m_Ris;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CREODlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CREODlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpenFile();
	afx_msg void OnAbout();
	afx_msg void OnRaskod();
	afx_msg void OnVyvod();
	afx_msg void OnOptimiz();
	afx_msg void OnLuminaire();
	afx_msg void OntBaker();
	afx_msg void OnSaveisx();
	afx_msg void OnNewtype();
	afx_msg void OnSaveFileAs();
	afx_msg void OnSaveFile();
	afx_msg void OnCopy();
	afx_msg void OnDelete();
	afx_msg void OnPaste();
	afx_msg void OnSearch();
	afx_msg void OnPoisk();
	afx_msg void OnChangeEditpoisk();
	afx_msg void OnPreobrazmatr();
	afx_msg void OnReovrec();
	afx_msg void OnDelputi();
	afx_msg void OnNewFile();
	afx_msg void Onmaterials();
	afx_msg void Onfaces();
	afx_msg void Onbboxes();
	afx_msg void Onbspheres();
	afx_msg void OnPolygon();
	afx_msg void OnFont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REODLG_H__1FA16BC7_D791_11D5_8C27_C46B1940A128__INCLUDED_)
