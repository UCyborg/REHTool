// REODlg.cpp : implementation file    ::LoadImage
//

#include "stdafx.h"
#include "REO.h"
#include "REODlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CREODlg dialog

CREODlg::~CREODlg()
{
	int i,j;
	delete RabFont;
	if(S!=NULL)  delete[] S;
	if(NewMat!=NULL) delete[] NewMat;
	if(masBMP!=NULL) delete[] masBMP;
	if(Ver!=NULL) delete[] Ver;
	if(Pol!=NULL) delete[] Pol;
	if(newPol!=NULL) delete[] newPol;
	if(BmpInf!=NULL) delete[] BmpInf;

	if(InfOptim.kPolMat!=NULL) delete[] InfOptim.kPolMat;
	if(InfOptim.masPolMat!=NULL)
	{
		for(i=0;i<OLDkMat;i++) if(InfOptim.masPolMat[i]!=NULL) delete[] InfOptim.masPolMat[i];
		delete[] InfOptim.masPolMat;
	};
	if(NewNumMat!=NULL)
	{
		for(i=0;i<OLDkMat;i++) if(NewNumMat[i]!=NULL) delete[] NewNumMat[i];
		delete[] NewNumMat;
	};

	if(RezREO.Podgrup!=NULL) 
	{
		for(i=0;i<OLDkMat;i++)
		{
			if(RezREO.Podgrup[i]!=NULL)
			{
				for(j=0;j<OLDkPol;j++) if(RezREO.Podgrup[i][j]!=NULL) delete[] RezREO.Podgrup[i][j];
				delete[] RezREO.Podgrup[i];
			};
		};
		delete[] RezREO.Podgrup;
	};
	if(RezREO.kPodgrup!=NULL) delete[] RezREO.kPodgrup;
	if(RezREO.kElemPod!=NULL)
	{
		for(i=0;i<OLDkMat;i++) if(RezREO.kElemPod[i]!=NULL) delete[] RezREO.kElemPod[i];
		delete[] RezREO.kElemPod;
	};

};

CREODlg::CREODlg(CWnd* pParent /*=NULL*/)
	: CDialog(CREODlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CREODlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CREODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CREODlg)
	DDX_Control(pDX, IDC_POISK, m_PoskKn);
	DDX_Control(pDX, IDC_EDITPOISK, m_Poisk);
	DDX_Control(pDX, IDC_MYEDIT, m_MyRic);
	DDX_Control(pDX, IDC_UDALENIE, m_Udal);
	DDX_Control(pDX, IDC_PUT, m_Put);
	DDX_Control(pDX, IDC_NEWIMA, m_NewIma);
	DDX_Control(pDX, IDC_TYPEFILE, m_TypeFile);
	DDX_Control(pDX, IDC_RIS, m_Ris);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CREODlg, CDialog)
	//{{AFX_MSG_MAP(CREODlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_OPEN_FILE, OnOpenFile)
	ON_COMMAND(IDC_ABOUT, OnAbout)
	ON_BN_CLICKED(IDC_RASKOD, OnRaskod)
	ON_BN_CLICKED(IDC_VYVOD, OnVyvod)
	ON_BN_CLICKED(IDC_OPTIMIZ, OnOptimiz)
	ON_BN_CLICKED(IDC_Luminaire, OnLuminaire)
	ON_BN_CLICKED(IDC_tBaker, OntBaker)
	ON_BN_CLICKED(IDC_SAVEISX, OnSaveisx)
	ON_BN_CLICKED(IDC_NEWTYPE, OnNewtype)
	ON_COMMAND(ID_SAVE_FILE_AS, OnSaveFileAs)
	ON_COMMAND(ID_SAVE_FILE, OnSaveFile)
	ON_COMMAND(IDC_COPY, OnCopy)
	ON_COMMAND(IDC_DELETE, OnDelete)
	ON_COMMAND(IDC_PASTE, OnPaste)
	ON_COMMAND(IDC_SEARCH, OnSearch)
	ON_BN_CLICKED(IDC_POISK, OnPoisk)
	ON_EN_CHANGE(IDC_EDITPOISK, OnChangeEditpoisk)
	ON_BN_CLICKED(IDC_PREOBRAZMATR, OnPreobrazmatr)
	ON_BN_CLICKED(IDC_REOVREC, OnReovrec)
	ON_BN_CLICKED(IDC_DELPUTI, OnDelputi)
	ON_COMMAND(ID_NEW_FILE, OnNewFile)
	ON_BN_CLICKED(IDC_materials, Onmaterials)
	ON_BN_CLICKED(IDC_faces, Onfaces)
	ON_BN_CLICKED(IDC_bboxes, Onbboxes)
	ON_BN_CLICKED(IDC_bspheres, Onbspheres)
	ON_BN_CLICKED(IDC_POLYGON, OnPolygon)
	ON_COMMAND(IDC_FONT, OnFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CREODlg message handlers

BOOL CREODlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
//	m_MyRic.SetReadOnly();
//	m_PoskKn.SetWindowText("Найти сначала");
	m_PoskKn.SetWindowText("Find");
	m_Poisk.SetWindowText("texture");
	PosPoiska=0;PravPreobr=false;IsRec=false;EstReo=false;
	masBMP=NULL;Ver=NULL;S=NULL;
	newPol=NULL;Pol=NULL;BmpInf=NULL;
	InfOptim.kPolMat=NULL;
	InfOptim.masPolMat=NULL;
	RezREO.Podgrup=NULL;
	RezREO.kPodgrup=NULL;
	RezREO.kElemPod=NULL;
	NewNumMat=NULL;
	NewMat=NULL;
	m_MyRic.LimitText(5000000);

//	LOGFONT lf1;
	CFont font1;
	RabFont=new LOGFONT;
	memset(RabFont, 0, sizeof(LOGFONT));       // zero out structure
	RabFont->lfHeight = -16;                      // request a 12-pixel-height font
	RabFont->lfWeight=400;
	RabFont->lfCharSet=255;
	RabFont->lfQuality=1;
	RabFont->lfClipPrecision=2;
	RabFont->lfEscapement=0;
	RabFont->lfPitchAndFamily=33;
	RabFont->lfOutPrecision=1;
	RabFont->lfOrientation=0;
	RabFont->lfItalic=0;
	RabFont->lfWidth=0;
	RabFont->lfUnderline=0;
	RabFont->lfStrikeOut=0;
	strcpy(RabFont->lfFaceName, "Terminal"); 
	if(font1.CreateFontIndirect(RabFont))  // create the font
		m_MyRic.SetFont(&font1);
//	m_MyRic.SetOptions(ECOOP_OR, ECO_AUTOVSCROLL|ECO_AUTOHSCROLL);

//	char buf[100];
//	sprintf(buf,"LimitText(5000000)=%d",m_MyRic.GetLimitText());
//	AfxMessageBox(buf);
	OLDkMat=-1;OLDkPol=-1;process=false;
	NewType=false;ImNewType="";
	CheckRadioButton(IDC_Luminaire,IDC_tBaker,IDC_tBaker);
	TypeFile=1;
    IsFile=FALSE;Prav=FALSE;Optimum=FALSE;
	Npol=-1;Kpol=-1;
//	m_NewIma.SetWindowText("НЕТ ИМЕНИ");
	m_NewIma.SetWindowText("no name");
//	m_Ris.ShowWindow(SW_HIDE);
//	m_MyRic.SetOptions(ECOOP_OR,ECO_NOHIDESEL);
	m_MyRic.HideSelection(FALSE, TRUE);

//m_Ris.ShowWindow(SW_SHOWNORMAL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CREODlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CREODlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CREODlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CREODlg::OnOpenFile() 
{
	// TODO: Add your command handler code here
//	CString Ric="";
	Optimum=FALSE;Prav=FALSE;
	CFileDialog fd(true,NULL,NULL, OFN_HIDEREADONLY+
		OFN_OVERWRITEPROMPT,NULL,NULL);
//fd.m_ofn.lpstrTitle="Открытие файла REO";
fd.m_ofn.lpstrTitle="Open";
//fd.m_ofn.lpstrFilter="REO файлы(*.reo)\0*.reo\0REC файлы(*.rec)\0*.rec\0Все файлы(*.*)\0*.*\0\0";
fd.m_ofn.lpstrFilter="RE Objects(*.reo)\0*.reo\0RE Characters(*.rec)\0*.rec\0All Files(*.*)\0*.*\0\0";
//fd.m_ofn.nFilterIndex=2;
//fd.m_ofn.lpstrInitialDir="D:\\VC++\\Мои проекты\\REO1\\sq_ma_obj_src";
fd.m_ofn.lpstrInitialDir="D:\\VC++\\Мои проекты\\Проекты REO\\REO3";
//fd.m_ofn.lpstrInitialDir="C:\\";

    if (fd.DoModal()==IDOK)
	{
		CString s;//int k0;
//		CStdioFile f;
		CFile f;
		if(f.Open(fd.GetFileName(),CFile::modeRead)==0)
		{
			//AfxMessageBox("Ошибка открытия выбранного файла");return;
			AfxMessageBox("File opening error");return;
		};
		char buf[1000],fname[1000],ext[1000];long dlinaF; char *fff;
		dlinaF=f.GetLength();fff=NULL;fff=new char[dlinaF+10];
		if(fff==NULL)
		{
			//AfxMessageBox("Ошибка выделения памяти для открытого выбранного файла");return;
			AfxMessageBox("Memory allocation error for selected file");return;
		};
		if(f.Read(fff,dlinaF)!=(UINT)dlinaF)
		{
			//AfxMessageBox("Ошибка чтения открытого файла");return;
			AfxMessageBox("File reading error");return;
		};
		fff[dlinaF]=0;m_MyRic.SetWindowText(fff);
		IsFile=true;delete[] fff;
		PatREO=fd.GetPathName();
		SetWindowText(fd.GetPathName());
		strcpy(buf,PatREO);
		_splitpath(buf,Drive,Dir,fname,ext );
		ImFile[0]=fname;ImFile[1]=ext;
		m_NewIma.SetWindowText(ImFile[0]+"_ALT");
		f.Close();
		Optimum=FALSE;
		if(fd.m_ofn.nFilterIndex==2)
		{
//			AfxMessageBox("REC");
			IsRec=true;
		}
		else
		{
//			AfxMessageBox("не REC");
			IsRec=false;
		};
	};
}

void CREODlg::OnAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg ab;
	ab.DoModal();
}

void CREODlg::OnRaskod() 
{
	// TODO: Add your control notification handler code here
	Optimum=FALSE;Prav=FALSE;
	if(!IsFile)
	{
		//AfxMessageBox("Файл не открыт");return;
		AfxMessageBox("No file");return;
	};
	if(IsRec)
	{
		//AfxMessageBox("Раскодируются только файлы REO.");return;
		AfxMessageBox("Only for REO files");return;
	};
	if(ReadEdit()<=0)
	{
		//AfxMessageBox("Редактор пуст"); return;
		AfxMessageBox("Editor is empty"); return;
	};
	int i,j,k,n;char buf[1000];int count;CString s;
// Чтение секции материалов  (feof(stream))
	n=-1;count=0;bool est=FALSE;
	for(i=0;i<kS;i++)
		if (strncmp((LPCTSTR)S[i], "materials", 9) == 0){n=i;break;};
	if(n>=0)
	{
		if(!est){est=TRUE;Nmat=n;};
		if(sscanf((LPCTSTR)S[n],"materials %d", &kMat)<1)
		{
			//AfxMessageBox("Секция материалы - не найдено количество материалов");
			AfxMessageBox("Number of materials not found");
			UstEdit(i);
			Prav=FALSE;return;
		};    
		if((n+kMat)>kS)
		{
			//AfxMessageBox("Секция материалы не найдена(выходит за границу файла)");
			AfxMessageBox("Can not find materials section");
			Prav=FALSE;return;
		};
		if(masBMP!=NULL) delete[] masBMP;
		masBMP=new CString[kMat];s="";
		for(i=n+1;i<=n+kMat;i++)
		{
			strcpy(buf,S[i]);
			if(sscanf((LPCTSTR)S[i], "%d texture %100s", &count, buf)<2)
			{
				//AfxMessageBox("Строка в секции материалов не полна");
				AfxMessageBox("Incomplete string");
				UstEdit(i);
				Prav=FALSE;return;
			};
			strcpy(buf, S[i].Mid(S[i].Find("texture")+7));
			if((count>=0)&(count<kMat)) masBMP[count]=buf;
			else
			{
				//AfxMessageBox("В секции материалов номер материала больше количества материалов");
				AfxMessageBox("Number of material exceeds number of materials");
				UstEdit(i);
				Prav=FALSE;return;
			};
			while(masBMP[count].GetAt(0)==' ') masBMP[count].Delete(0);
			itoa(count,buf,10);
			s=s+buf+" "+masBMP[count]+"     ";
		};
		for(i=0;i<kMat;i++)
			if(masBMP[i].GetLength()<=0)
			{
				//AfxMessageBox("В секции материалов название миниммум одного файла отсутствует");
				AfxMessageBox("Can not find at least one material's filename");
				UstEdit(i);
				Prav=FALSE;return;
			};
			Kmat=Nmat+kMat;
//			sprintf(buf,"Секция материалов  %d %d", Nmat, Kmat);
//			AfxMessageBox(buf);
			if(BmpInf!=NULL) delete[] BmpInf;
			BmpInf=new BMPINF[kMat];
//			m_Ris.ShowWindow(SW_SHOWNORMAL);
//			::TranslateMessage(NULL);
			for(i=0;i<kMat;i++)
			{
				char drive[1000],dir[1000],fname[1000],ext[1000];
				strcpy(buf,masBMP[i]);
				_splitpath(buf,drive,dir,fname,ext );
				if((drive[0]=='\0')||((m_Udal.GetState()&0x0003)==1))
					_makepath(buf,Drive,Dir,fname,ext);
				BmpInf[i].ImFile[0]=fname;
				BmpInf[i].ImFile[1]=ext;
				BmpInf[i].ris.DeleteObject();
				if(!ReadBMP(&BmpInf[i].ris, buf))
				{
					//sprintf(buf,"В секции материалов не читается файл иатериала %d  %s", i, masBMP[i]);
					sprintf(buf,"Can not read material's file %d  %s", i, masBMP[i]);
					UstEdit(i);
					AfxMessageBox(buf);
					Prav=FALSE;return;
				};
				//::Sleep(1000);
				
//				m_Ris.SetBitmap(BmpInf[i].ris);
//				Zadergka(500);
//				AfxMessageBox("Выведен битмап?");

			};
//			m_Ris.ShowWindow(SW_HIDE);
		
	}
	//else {AfxMessageBox("Секция материалы не найдена");Prav=FALSE;return;};
	else {AfxMessageBox("Can not find materials section");Prav=FALSE;return;};

//   Чтение секции вершин в трехмерном пространстве
	n=-1;count=0;
	for(i=0;i<kS;i++)
		if (strncmp((LPCTSTR)S[i], "vertices", 8) == 0){n=i;break;};
	if(n>=0)
	{
		if(sscanf((LPCTSTR)S[n],"vertices %d", &kVer)<1)
		{
			//AfxMessageBox("Секция вершин - не найдено количество вершин");
			AfxMessageBox("Can not find number of vertices");
			UstEdit(i);
			Prav=FALSE;return;
		};    
		if((n+kVer)>kS)
		{
			//AfxMessageBox("Секция вершин не полна(выходит за границу файла)");
			AfxMessageBox("Vertices section incomplete");
			Prav=FALSE;return;
		};
//		itoa(kVer,buf,10);
//		s="Секция вершин найдена  ";s=s+buf;
//		AfxMessageBox(s);
		if(Ver!=NULL) delete[] Ver;
		Ver=new TREUG[kVer];
		for(i=0;i<kVer;i++) Ver[i].pr=FALSE;
		float x,y,z;
		for(i=n+1;i<=n+kVer;i++)
		{
			if(sscanf((LPCTSTR)S[i], "%d %f %f %f", &count, &x, &y, &z)<4)
			{
				//AfxMessageBox("В секции вершин неверная информайия");
				AfxMessageBox("Invalid data in the vertices section");
				UstEdit(i);
				Prav=FALSE;return;
			};
			if((count>=0)&(count<kVer)) 
			{
				Ver[count].x=x;Ver[count].y=y;
				Ver[count].z=z;Ver[count].pr=TRUE;
//				sprintf(buf,"%d %f %f %f", count, x, y, z);
//				AfxMessageBox(buf);
			}
			else
			{
				//AfxMessageBox("В секции вершин номер вершины больше количества вершин");
				AfxMessageBox("Number of vertex exceeds total number of vertices");
				UstEdit(i);
				Prav=FALSE;return;
			};
//			itoa(count,buf,10);
//			s=s+buf+" "+masBMP[count]+"     ";
		};
		for(j=0;j<kVer;j++)
			if(Ver[j].pr==FALSE)
			{
				//sprintf(buf,"В секции вершин вершина номер %d отсутсрвует",j);
				sprintf(buf,"Vertex number %d not found",j);
				AfxMessageBox(buf);
				Prav=FALSE;return;
			};
//		itoa(kMat,buf,10);
//		s="Секция материалы  ";
//		s=s+buf;
//		AfxMessageBox(s);
		
	}
	//else {AfxMessageBox("Секция вершин не найдена");Prav=FALSE;return;};
	else {AfxMessageBox("Can not found vertices section");Prav=FALSE;return;};

//  Чтение секции полигонов.
	n=-1;count=0;bool perv=FALSE;
	for(i=0;i<kS;i++)
		if (strncmp((LPCTSTR)S[i], "faces", 5) == 0){n=i;break;};
	if(n>=0)
	{
		if(!perv){perv=TRUE;Npol=n;};
		char dummy[100];
		if(sscanf((LPCTSTR)S[n], "%s %d", dummy, &kPol)<2)
		{
			//AfxMessageBox("Секция полигонов - не найдено количество полигонов");
			AfxMessageBox("Can not find number of polygons");
			UstEdit(i);
			Prav=FALSE;return;
		};
//		sprintf(buf," всего полигонов %d", kPol);
//		AfxMessageBox(buf);
		if(Pol!=NULL) delete[] Pol;
		Pol=new POLYGON[kPol];
		if(newPol!=NULL) delete[] newPol;
		newPol=new POLYGON[kPol];
		for(i=0;i<kPol;i++) Pol[i].pr=FALSE;
		i=n+1;bool vyx=FALSE;int kolpol=0,numpol,t;
		while(i<kS)
		{
			if(S[i].GetLength()==0) {i++;continue;}
			if(S[i][0]=='#') {i++;continue;}
			if (strncmp((LPCTSTR)S[i], "polygon", 7) != 0) 
			{
				if(kolpol!=kPol)
				{
					//AfxMessageBox("Ошибка, полигонов меньше, чем указано.");
					AfxMessageBox("Error - number of polygons less than total polygons number");
					Prav=FALSE;return;
				};
				Kpol=i-1;vyx=TRUE;break;
			};
			if(sscanf((LPCTSTR)S[i], "polygon %d", &numpol)<1)
			{
				//AfxMessageBox("В секции полтгонов неверная информайия");
				AfxMessageBox("Wrong data in the polygons section");
				UstEdit(i);
				Prav=FALSE;return;
			};
//		sprintf(buf," Полигон номер %d", numpol);
//		AfxMessageBox(buf);
			if((numpol>=0)&(numpol<kPol)) 
			{
				i++;
				if(i>=kS)
				{
					//AfxMessageBox("Неожиданный конец файла при чтении полигонов.");
					AfxMessageBox("Unexpected end of file at polygons section processing");
					Prav=FALSE;return;
				};
				if (strncmp((LPCTSTR)S[i], "vt", 2)	!= 0)
				{
					//sprintf(buf,"");
					//AfxMessageBox("Неверная структура одного из полигонов - нет секции vt.");
					AfxMessageBox("Wrong polygon's structure - can not find 'vt' section");
					UstEdit(i);
					Prav=FALSE;return;
				};
				if(sscanf((LPCTSTR)S[i], "vt %d:", &t)<1)
				{
					//sprintf(buf,"секция vt не полна %s",(LPCTSTR)S[i]);
					sprintf(buf,"section 'vt' incomplete %s",(LPCTSTR)S[i]);
					//AfxMessageBox("Неверная структура одного из полигонов - секция vt не полна.");
					AfxMessageBox("Wrong polygon's structure - section 'vt' incomplete");
					AfxMessageBox(buf);
					UstEdit(i);
					Prav=FALSE;return;
				};
				if (t == 3)
				{
					Pol[numpol].kv= t;
					if(sscanf((LPCTSTR)S[i], "vt %d:%d %d %d", &t, &Pol[numpol].xyz[0], &Pol[numpol].xyz[1], &Pol[numpol].xyz[2])<4)
					{
					//AfxMessageBox("Неверная структура одного из полигонов - секция vt не полна.");
					AfxMessageBox("Wrong polygon's structure - section 'vt' incomplete");
					sprintf(buf,"секция vt не полна %s",(LPCTSTR)S[i]);
					AfxMessageBox(buf);
					UstEdit(i);
					Prav=FALSE;return;
					};
				}
				else if (t == 4)
					{
						Pol[numpol].kv= t;
						if(sscanf((LPCTSTR)S[i], "vt %d:%d %d %d %d", &t, &Pol[numpol].xyz[0], &Pol[numpol].xyz[1], &Pol[numpol].xyz[2], &Pol[numpol].xyz[3])<5)
						{
							//AfxMessageBox("Неверная структура одного из полигонов - секция vt не полна.");
							AfxMessageBox("Wrong polygon's structure - section 'vt' incomplete");
							sprintf(buf,"секция vt не полна %s",(LPCTSTR)S[i]);
							AfxMessageBox(buf);
							UstEdit(i);
							Prav=FALSE;return;
						};
					}
					else
					{
						//AfxMessageBox("Неверная структура одного из полигонов - секция vt не верна.");
						AfxMessageBox("Wrong polygon's structure - section 'vt' invalid");
						UstEdit(i);
						Prav=FALSE;return;
					};
				i++;
				if(i>=kS)
				{
					//AfxMessageBox("Неожиданный конец файла при чтении полигонов.");
					AfxMessageBox("Unexpected end of file at polygons processing");
					Prav=FALSE;return;
				};
				if (strncmp((LPCTSTR)S[i], "ma", 2) != 0)
				{
					//AfxMessageBox("В полигоне отсутствует секция материалы.");
					AfxMessageBox("Can not find 'ma' section");
					UstEdit(i);
					Prav=FALSE;return;
				};
				if(sscanf((LPCTSTR)S[i], "ma %d:", &Pol[numpol].ma)<1)
				{
					//AfxMessageBox("В полигоне секция материалы не полна.");
					AfxMessageBox("'ma' section incomplete");
					UstEdit(i);
					Prav=FALSE;return;
				};
				i++;
				if(i>=kS)
				{
					//AfxMessageBox("Неожиданный конец файла при чтении полигонов.");
					AfxMessageBox("Unexpected end of file at polygons processing");
					Prav=FALSE;return;
				};
				if (strncmp((LPCTSTR)S[i], "tu", 2) != 0)
				{
					//AfxMessageBox("В полигоне отсутствует секция tu.");
					AfxMessageBox("Can not find 'tu' section");
					UstEdit(i);
					Prav=FALSE;return;
				};
				if (t == 3)
				{
					if(sscanf((LPCTSTR)S[i], "tu %f %f %f", &Pol[numpol].vh[0].x, &Pol[numpol].vh[1].x, &Pol[numpol].vh[2].x)<3)
					{
						//AfxMessageBox("В полигоне  секция tu не полна.");
						AfxMessageBox("Section 'tu' incomplete");
						UstEdit(i);
						Prav=FALSE;return;
					};
				}
				else
					if(sscanf((LPCTSTR)S[i], "tu %f %f %f %f", &Pol[numpol].vh[0].x, &Pol[numpol].vh[1].x, &Pol[numpol].vh[2].x, &Pol[numpol].vh[3].x)<4)
					{
						//AfxMessageBox("В полигоне  секция tu не полна.");
						AfxMessageBox("Section 'tu' incomplete");
						UstEdit(i);
						Prav=FALSE;return;
					};
					for(int u=0;u<Pol[numpol].kv;u++)
						if((Pol[numpol].vh[u].x<0)||(Pol[numpol].vh[u].x>1))
						{
							char buf4[100];
							//sprintf(buf4,"Среди полигонов парамерт tu неверен, строка файла номер %d",i);
							sprintf(buf4,"Wrong 'tu', string number %d",i);
							AfxMessageBox(buf4);
							UstEdit(i);
							Prav=FALSE;return;
						};
		
				i++;
				if(i>=kS)
				{
					//AfxMessageBox("Неожиданный конец файла при чтении полигонов.");
					AfxMessageBox("Unexpected end of file at polygons processing");
					Prav=FALSE;return;
				};
				if (strncmp((LPCTSTR)S[i], "tv", 2) != 0)
				{
					//AfxMessageBox("В полигоне отсутствует секция tv.");
					AfxMessageBox("Can not find 'tv' section");
					UstEdit(i);
					Prav=FALSE;return;
				};
				if (t == 3)
				{
					if(sscanf((LPCTSTR)S[i], "tv %f %f %f", &Pol[numpol].vh[0].y, &Pol[numpol].vh[1].y, &Pol[numpol].vh[2].y)<3)
					{
						//AfxMessageBox("В полигоне  секция tv не полна.");
						AfxMessageBox("Section 'tv' incomplete");
						UstEdit(i);
						Prav=FALSE;return;
					};
				}
				else
					if(sscanf((LPCTSTR)S[i], "tv %f %f %f %f", &Pol[numpol].vh[0].y, &Pol[numpol].vh[1].y, &Pol[numpol].vh[2].y, &Pol[numpol].vh[3].y)<4)
					{
						//AfxMessageBox("В полигоне  секция tv не полна.");
						AfxMessageBox("Section 'tv' incomplete");
						UstEdit(i);
						Prav=FALSE;return;
					};
					for(u=0;u<Pol[numpol].kv;u++)
						if((Pol[numpol].vh[u].y<0)||(Pol[numpol].vh[u].y>1))
						{
							char buf4[100];
							//sprintf(buf4,"Среди полигонов парамерт tv неверен, строка файла номер %d",i);
							sprintf(buf4,"Wrong 'tv', string number %d",i);
							AfxMessageBox(buf4);
							UstEdit(i);
							Prav=FALSE;return;
						};

				i++;
				if(i>=kS)
				{
					//AfxMessageBox("Неожиданный конец файла при чтении полигонов.");
					AfxMessageBox("Unexpected end of file at polygons processing");
					Prav=FALSE;return;
				};
				if (strncmp((LPCTSTR)S[i], "fl 2S", 5) == 0)
				{
					Pol[numpol].dv=TRUE;i++;
				}
				else Pol[numpol].dv=FALSE;
				Pol[numpol].pr=TRUE;
				kolpol++;		
//				sprintf(buf,"%d %f %f %f", count, x, y, z);
//				AfxMessageBox(buf);
			}
			else
			{
				//AfxMessageBox("В секции полигонов номер полигона больше количества полигонов");
				AfxMessageBox("Polygon's number exceeds total number of polygons");
				UstEdit(i);
				Prav=FALSE;return;
			};
		};
//		sprintf(buf,"Прочитано полигонов %d %d", Npol, Kpol);
//		AfxMessageBox(buf);
		if((!vyx)&(kolpol<kPol))
		{
			//AfxMessageBox("Неожиданный конец файла при чтении полигонов.");
			AfxMessageBox("Unexpected end of file at polygons processing");
			Prav=FALSE;return;
		};
		for(j=0;j<kPol;j++)
			if(Pol[j].pr==FALSE)
			{
				//sprintf(buf,"Средт полигона нет полигоан номер %d",j);
				sprintf(buf,"Can not find polygon number %d",j);
				AfxMessageBox(buf);
				Prav=FALSE;return;
			};
	}
	 //else  {AfxMessageBox("Секция полтгонов не найдена");Prav=FALSE;return;};
	 else  {AfxMessageBox("Can not find polygons section");Prav=FALSE;return;};
// Определение новых значений структуры пераспределения полигонов.

	if(NewNumMat!=NULL)
	{
		for(i=0;i<OLDkMat;i++) if(NewNumMat[i]!=NULL) delete[] NewNumMat[i];
		delete[] NewNumMat;
	};
	 
	if(InfOptim.kPolMat!=NULL) delete[] InfOptim.kPolMat;
	if(InfOptim.masPolMat!=NULL)
	{
		for(i=0;i<OLDkMat;i++) if(InfOptim.masPolMat[i]!=NULL) delete[] InfOptim.masPolMat[i];
		delete[] InfOptim.masPolMat;
	};
	if(RezREO.Podgrup!=NULL) 
	{
		for(i=0;i<OLDkMat;i++)
		{
			if(RezREO.Podgrup[i]!=NULL)
			{
				for(j=0;j<OLDkPol;j++) if(RezREO.Podgrup[i][j]!=NULL) delete[] RezREO.Podgrup[i][j];
				delete[] RezREO.Podgrup[i];
			};
		};
		delete[] RezREO.Podgrup;
	};
	if(RezREO.kPodgrup!=NULL) delete[] RezREO.kPodgrup;
	if(RezREO.kElemPod!=NULL)
	{
		for(i=0;i<OLDkMat;i++) if(RezREO.kElemPod[i]!=NULL) delete[] RezREO.kElemPod[i];
		delete[] RezREO.kElemPod;
	};

	NewNumMat=new MASINT[kMat];
	for(i=0;i<kMat;i++) NewNumMat[i]=new int[kPol];

	
	InfOptim.kPolMat=new int[kMat];
	InfOptim.masPolMat=new MASINT[kMat];//[ckPol];
	for(i=0;i<kMat;i++) InfOptim.masPolMat[i]=new int[kPol];
//	RezREO.Podgrup=new int[kMat][kPol][kPol];
	RezREO.Podgrup=new MASMASINT[kMat];
	for(i=0;i<kMat;i++)
	{
		RezREO.Podgrup[i]=new MASINT[kPol];
		for(j=0;j<kPol;j++) RezREO.Podgrup[i][j]=new int[kPol];
	};
//	RezREO.kElemPod=new int[kMat][kPol];
	RezREO.kElemPod=new MASINT[kMat];
	for(i=0;i<kMat;i++) RezREO.kElemPod[i]=new int[kPol];
	RezREO.kPodgrup=new int[kMat];

	for(i=0;i<kMat;i++) 
	{
		InfOptim.kPolMat[i]=0;
		RezREO.kPodgrup[i]=0;
		for(j=0;j<kPol;j++)
		{
			InfOptim.masPolMat[i][j]=0;
			RezREO.kElemPod[i][j]=0;
			for(k=0;k<kPol;k++) RezREO.Podgrup[i][j][k]=0;
		};
	}
	for(i=0;i<kPol;i++)
	{
		InfOptim.masPolMat[Pol[i].ma][InfOptim.kPolMat[Pol[i].ma]]=i;
		InfOptim.kPolMat[Pol[i].ma]++;
	};
	OLDkMat=kMat;OLDkPol=kPol;
//	sprintf(buf,"распределение по материалам %d %d %d %d %d", InfOptim.kPolMat[0], InfOptim.kPolMat[1], InfOptim.kPolMat[2], InfOptim.kPolMat[3], InfOptim.kPolMat[4]);
//	AfxMessageBox(buf);
    //AfxMessageBox("Файл раскодирован успешно");
	AfxMessageBox("Object has been loaded sucessfully");
	EstReo=true;Prav=TRUE;Optimum=FALSE;
}

bool CREODlg::Vyvod(int tp)
{

	return true;
}

void CREODlg::OnVyvod() 
{
	// TODO: Add your control notification handler code here
	if((!Prav)||(!IsFile)||(!Optimum))
	{
		//AfxMessageBox("Нечего выводить!");
		AfxMessageBox("Nothing for output!");
		return;
	};
int i;CString sss,P,P2;char buf[1000];
CFileDialog fd(false,NULL,NULL, OFN_HIDEREADONLY+
		OFN_OVERWRITEPROMPT,NULL,NULL);
//fd.m_ofn.lpstrTitle="Сохранение файла REO";
fd.m_ofn.lpstrTitle="Save";
//fd.m_ofn.lpstrFilter="REO файлы(*.reo)\0*.reo\0Все файлы(*.*)\0*.*\0\0";
fd.m_ofn.lpstrFilter="RE Objects(*.reo)\0*.reo\0All Files(*.*)\0*.*\0\0";
//fd.m_ofn.nFilterIndex=2;
//fd.m_ofn.lpstrInitialDir="D:\\VC++\\Мои проекты\\REO1\\sq_ma_obj_src";
fd.m_ofn.lpstrInitialDir="C:\\";
sss=ImFile[0];sss=sss+"_ALT";sss=sss+".reo";
P2=ImFile[0];P2=P2+"_ALTlm";//P2=P2+".reo";
strcpy(buf,(LPCTSTR)sss);
//for(i=0;i<sss.GetLength();i++) buf[i]=sss.GetAt(i);
//buf[sss.GetLength()]='\0';
fd.m_ofn.lpstrFile=buf;
 if (fd.DoModal()==IDOK)
 {
	CStdioFile f,f2;CString s;int kol;
	char driver[300],path[300],im[300],ext[300],p2[300], buf5[100];
	kol=m_NewIma.GetLine(0,buf5,100); 
	buf5[kol]='\0';
	ImNewType=buf5;
//	ImNewType=ImNewType;
	P=fd.GetPathName();
	_splitpath((LPCTSTR)P,driver,path,im,ext);
	ImVyvodFile=im;
	if(ext[0]=='\0') 
	{
		_makepath(p2,driver,path,im,".reo");P=p2;
	};
	P2=im;P2=P2+"lm";
	_makepath(p2,driver,path,(LPCTSTR)P2,".reo");
	if(f.Open(P,CFile::modeCreate | CFile::modeWrite)==0)
	{
		//AfxMessageBox("Ошибка открытия выбранного файла");return;
		AfxMessageBox("I/O Error at _ALT");return;
	};
	if(f2.Open(p2,CFile::modeCreate | CFile::modeWrite)==0)
	{
		//AfxMessageBox("Ошибка открытия второго файла");return;
		AfxMessageBox("I/O Error at _ALTlm");return;
	};
	if(Kmat<Npol)
	{
		for(i=0;i<Nmat;i++) 
		{
			s=S[i]+"\n"; 
			f.WriteString((LPCTSTR)s);
			f2.WriteString((LPCTSTR)s);
		};
		SeveMat(&f,&f2,&P);
		for(i=Kmat+1;i<Npol;i++) 
		{
			s=S[i]+"\n";
			f.WriteString((LPCTSTR)s);
			f2.WriteString((LPCTSTR)s);
		};
		SavePol(&f,&f2);
		for(i=Kpol+1;i<kS;i++) 
		{
			s=S[i]+"\n";
			f.WriteString((LPCTSTR)s);
			f2.WriteString((LPCTSTR)s);
		};
	}
	else
	{
		for(i=0;i<Npol;i++) 
		{
			s=S[i]+"\n";
			f.WriteString((LPCTSTR)s);
			f2.WriteString((LPCTSTR)s);
		};
		SavePol(&f,&f2);
		for(i=Kpol+1;i<Nmat;i++) 
		{
			s=S[i]+"\n";
			f.WriteString((LPCTSTR)s);
			f2.WriteString((LPCTSTR)s);
		};
		SeveMat(&f,&f2,&P);
		for(i=Kmat+1;i<kS;i++) 
		{
			s=S[i]+"\n";
			f.WriteString((LPCTSTR)s);
			f2.WriteString((LPCTSTR)s);
		};

	};
	//AfxMessageBox("Вывод произведен.");
	AfxMessageBox("Output OK");
 };
}

bool CREODlg::SeveMat(CStdioFile *ff,CStdioFile *ff2,CString *pp)
{
	int i;char buf[3000],d[1000],puti[1000],im[1000],ras[1000];CString s;
	_splitpath((LPCTSTR)(*pp),d,puti,im,ras);
	sprintf(buf,"materials %d\n",kNewMat);
	ff->WriteString(buf);
	ff2->WriteString(buf);
	for(i=0;i<kNewMat;i++) 
	{
		s="";
		UINT rez=m_Put.GetState()&0x0003;
		if(rez==1) 
		{
			s=d;s=s+puti;
		};
		s=s+NewMat[i].ImFile[0]+NewMat[i].ImFile[1];
		strcpy(buf,(LPCTSTR)s);
		sprintf(buf,"%d texture %s\n",i,s);
		ff->WriteString(buf);
		CString ni;
		if(NewType) ni=ImNewType; else ni=ImVyvodFile;
		if(TypeFile==0)
		{
			s="T_";s=s+ni;//+"_ALT";
			sprintf(buf,"_%d_X1",i+1);
			s=s+buf;s=s+".bmp";
		}
		else
		{
			s=ni;//s=s+"_ALT";;
			sprintf(buf,"_L&T_%dID0000",i+1);
			s=s+buf;s=s+".bmp";
		};
		sprintf(buf,"%d texture %s\n",i,s);
		ff2->WriteString(buf);
		sprintf(buf,"%s%s",(LPCTSTR)NewMat[i].ImFile[0],(LPCTSTR)NewMat[i].ImFile[1]);
		SaveBMP((HBITMAP)NewMat[i].ris,buf);
	};
	return TRUE;
}

bool CREODlg::SavePol(CStdioFile *ff, CStdioFile *ff2)
{
	int i; char buf[300];
	sprintf(buf,"\n\nfaces %d\n",kPol);
	ff->WriteString(buf);
	ff2->WriteString(buf);
	for(i=0;i<kPol;i++) 
	{
		sprintf(buf,"\npolygon %d\n",i);
		ff->WriteString(buf);
		ff2->WriteString(buf);
		if(newPol[i].kv==3)
			sprintf(buf,"vt %d:%d %d %d\n", newPol[i].kv,newPol[i].xyz[0],newPol[i].xyz[1],newPol[i].xyz[2]);
		else 
			sprintf(buf,"vt %d:%d %d %d %d\n", newPol[i].kv,newPol[i].xyz[0],newPol[i].xyz[1],newPol[i].xyz[2],newPol[i].xyz[3]);
		ff->WriteString(buf);
		ff2->WriteString(buf);
		sprintf(buf,"ma %d\n",newPol[i].ma);
		ff->WriteString(buf);
		ff2->WriteString(buf);
		if(newPol[i].kv==3)
			sprintf(buf,"tu %f %f %f\n",newPol[i].vh[0].x,newPol[i].vh[1].x,newPol[i].vh[2].x);
		else
			sprintf(buf,"tu %f %f %f %f\n",newPol[i].vh[0].x,newPol[i].vh[1].x,newPol[i].vh[2].x,newPol[i].vh[3].x);
		ff->WriteString(buf);
		ff2->WriteString(buf);
		if(newPol[i].kv==3)
			sprintf(buf,"tv %f %f %f\n",newPol[i].vh[0].y,newPol[i].vh[1].y,newPol[i].vh[2].y);
		else
			sprintf(buf,"tv %f %f %f %f\n",newPol[i].vh[0].y,newPol[i].vh[1].y,newPol[i].vh[2].y,newPol[i].vh[3].y);
		ff->WriteString(buf);
		ff2->WriteString(buf);
		if(newPol[i].dv=true)
		{
			sprintf(buf,"fl 2S\n");
			ff->WriteString(buf);
			ff2->WriteString(buf);
		};

	};
		sprintf(buf,"\n");ff->WriteString(buf);
		ff2->WriteString(buf);

	return TRUE;
}

bool CREODlg::ReadBMP(CBitmap *b, CString name)
{
	char buf[300];
//	name.Delete(0);
	strcpy(buf,(LPCTSTR)name);
	HBITMAP hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
			buf, IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if(hBitmap==NULL) return FALSE;
	b->Detach();
	b->Attach(hBitmap); 
	return TRUE;
}

/*
bool CREODlg::Zadergka(int t)
{
	int i,j=0;
	i=::GetTickCount();j=i;
	while((j-i)<t) j=::GetTickCount();
	return true;

}
*/

void CREODlg::OnOptimiz() 
{
	// TODO: Add your control notification handler code here
	char buf[300];int i,j,k,u;//n,m,u;
//	MSG msg;
	if((Prav==FALSE)||(IsFile==FALSE)) 
	{
		//AfxMessageBox("Файл не раскодирован или не прочитан.");
		AfxMessageBox("File is not loaded or opened");
		return;
	};
	for(i=0;i<kMat;i++)
	{
		if(InfOptim.kPolMat[i]<=0) continue;
		//n=0;// Номер подгруппы


		while(InfOptim.kPolMat[i]>0)
		{


			//m=0;// Номер полигона в подгруппе
			RezREO.Podgrup[i][RezREO.kPodgrup[i]][RezREO.kElemPod[i][RezREO.kPodgrup[i]]]=InfOptim.masPolMat[i][0];
			for(j=0;j<InfOptim.kPolMat[i]-1;j++) InfOptim.masPolMat[i][j]=InfOptim.masPolMat[i][j+1];
			InfOptim.kPolMat[i]--;
			RezREO.kElemPod[i][RezREO.kPodgrup[i]]++;
			if(InfOptim.kPolMat[i]<=0) {RezREO.kPodgrup[i]++;break;}
//			for(u=o;u<InfOptim.kPolMat[i];u++)
			u=0;
			while(u<InfOptim.kPolMat[i])
			{


				bool pr=true;
				for(k=0;k<RezREO.kElemPod[i][RezREO.kPodgrup[i]];k++)
				{
					if(Peres(RezREO.Podgrup[i][RezREO.kPodgrup[i]][k],InfOptim.masPolMat[i][u]))
					{
						pr=false;break;
					};
				};
				if(pr)
				{
					RezREO.Podgrup[i][RezREO.kPodgrup[i]][RezREO.kElemPod[i][RezREO.kPodgrup[i]]]=InfOptim.masPolMat[i][u];
					for(j=u;j<InfOptim.kPolMat[i]-1;j++) InfOptim.masPolMat[i][j]=InfOptim.masPolMat[i][j+1];
					InfOptim.kPolMat[i]--;
					RezREO.kElemPod[i][RezREO.kPodgrup[i]]++;//m++;
				}
				else u++;

			};
			if(i==3)
			i=i;
			RezREO.kPodgrup[i]++;//m++;

		};

	};
	k=0;// Матрица NewNumMat[i][j] содержит для каждого исходного материала и его подгруппы новый номер материала
	for(i=0;i<kMat;i++)
	  for(j=0;j<RezREO.kPodgrup[i];j++) 
		{NewNumMat[i][j]=k;k++;};
	if(NewMat!=NULL) delete[] NewMat;
	kNewMat=k;NewMat=new BMPINF[k];// массив новых материалов
	k=0;int uu;
	for(i=0;i<kMat;i++)
	  for(j=0;j<RezREO.kPodgrup[i];j++) 
	  { 


		  BITMAP bp;
		if(BmpInf[i].ris.GetBitmap(&bp)<=0)
		{
			//sprintf(buf,"Ошибка получения ВМР. Обратитесь к разработчику");
			sprintf(buf,"Error with ВМР. Consult developer");
			AfxMessageBox(buf);return;
		};

		  if(RezREO.Podgrup[i][j][0]==0)
			k=k;
		sprintf(buf,"_%d",RezREO.Podgrup[i][j][0]);// Прибавка к имени исх. файла
		NewMat[k].ImFile[0]=BmpInf[i].ImFile[0]+buf;// Имя
		NewMat[k].ImFile[1]=BmpInf[i].ImFile[1];// Расширение
		// Расчет размеров новой ВМР
		float maxX=-1,minX=10,maxY=-1,minY=10, rabx,raby;
		for(uu=0;uu<RezREO.kElemPod[i][j];uu++)
		for(u=0;u<Pol[RezREO.Podgrup[i][j][uu]].kv;u++)
		{	


			if(((RezREO.Podgrup[i][j][uu])==2)&(u==2))
			{
				rabx=Pol[RezREO.Podgrup[i][j][uu]].vh[u].x*(bp.bmWidth*MNOG-1);
				raby=Pol[RezREO.Podgrup[i][j][uu]].vh[u].y*(bp.bmHeight*MNOG-1);
				i=i;
			};

			if(maxX<Pol[RezREO.Podgrup[i][j][uu]].vh[u].x) maxX=Pol[RezREO.Podgrup[i][j][uu]].vh[u].x;
			if(minX>Pol[RezREO.Podgrup[i][j][uu]].vh[u].x) minX=Pol[RezREO.Podgrup[i][j][uu]].vh[u].x;
			if(maxY<Pol[RezREO.Podgrup[i][j][uu]].vh[u].y) maxY=Pol[RezREO.Podgrup[i][j][uu]].vh[u].y;
			if(minY>Pol[RezREO.Podgrup[i][j][uu]].vh[u].y) minY=Pol[RezREO.Podgrup[i][j][uu]].vh[u].y;
		};
		int rX,rY,Xmax, Xmin, Ymax, Ymin;
		int masR[6]={16*MNOG,16*MNOG,32*MNOG,64*MNOG,128*MNOG,256*MNOG};// integer
//		int masR[6]={16,16,32,64,128,256};// integer


		Xmax=Okrugl((maxX*(bp.bmWidth*MNOG-1)));
		Xmin=Okrugl((minX*(bp.bmWidth*MNOG-1)));
		Ymax=Okrugl((maxY*(bp.bmHeight*MNOG-1)));
		Ymin=Okrugl((minY*(bp.bmHeight*MNOG-1)));

		rX=0;for(u=0;u<6;u++) if((Xmax-Xmin+1)<=masR[u]) {rX=masR[u]; break;};
		if(rX==0)
		{
			sprintf(buf,"Ошибка расчета размера ВМР Xmax=%d Xmin=%d  Обратитесь к разработчику",Xmax,Xmin);
			sprintf(buf,"Error calculating ВМР's size. Xmax=%d Xmin=%d  Consult developer",Xmax,Xmin);
			AfxMessageBox(buf);return;
		};
		rY=0;for(u=0;u<6;u++) if((Ymax-Ymin+1)<=masR[u]) {rY=masR[u]; break;};
		if(rY==0)
		{
			//sprintf(buf,"Ошибка расчета размера ВМР Ymax=%d Ymin=%d  Обратитесь к разработчику",Ymax,Ymin);
			sprintf(buf,"Error calculating ВМР's size Ymax=%d Ymin=%d  Consult developer",Ymax,Ymin);
			AfxMessageBox(buf);return;
		};
		if(rY>rX) rX=rY; else rY=rX;
		// Копирование ВМР
//			NewMat[k].ris.CreateBitmapIndirect(&bp);

		if(((rX/MNOG)==bp.bmWidth)&((rY/MNOG)==bp.bmHeight))
		{
//			int rez;
//			NewMat[k].ris.DeleteObject();
//			rez=NewMat[k].ris.CreateBitmapIndirect(&bp);
			{
//				char buf2[100];
				CPaintDC dc(this);
				 BITMAP bp;
				CBitmap *old;
				CBitmap *old1;
				 CDC ndc,ndc1;
				BmpInf[i].ris.GetBitmap(&bp);
//			sprintf(buf2," Выведен старый ВМР номер %d",i);
//			m_Ris.SetBitmap(BmpInf[i].ris);
//			AfxMessageBox(buf2);

				ndc1.CreateCompatibleDC(&dc);
				 ndc.CreateCompatibleDC(&dc);
				old=ndc.SelectObject(&BmpInf[i].ris);
				NewMat[k].ris.DeleteObject();
				NewMat[k].ris.CreateCompatibleBitmap(&dc,bp.bmWidth,bp.bmHeight);
				old1=ndc1.SelectObject(&NewMat[k].ris);
				ndc1.BitBlt(0,0,bp.bmWidth,bp.bmHeight, &ndc,0,0,SRCCOPY);
				ndc1.SelectObject(old1);
				ndc.SelectObject(old);
/*			if(k==48)
			{
				sprintf(buf2," Выведен новый ВМР номер %d",k);
			m_Ris.SetBitmap(NewMat[k].ris);
			AfxMessageBox(buf2);
			};
*/				ndc.DeleteDC();
				ndc1.DeleteDC();
			};

//			char buf2[100];
//			sprintf(buf2," Выведен новый ВМР номер %d",k);
//			m_Ris.SetBitmap(NewMat[k].ris);
//			AfxMessageBox(buf2);
			NewMat[k].n.x=-1;NewMat[k].n.y=-1;
			NewMat[k].k.x=-1;NewMat[k].k.y=-1;
			NewMat[k].z.x=-1;NewMat[k].z.y=-1;
		}
		else
		{// Определение положение вырезки на исх. ВМР
			int nX=0,kX=rX-1,nY=0,kY=rY-1;
			while((nX<(Xmin-(MNOG-1)))&(kX<Xmax)) {nX=nX+MNOG;kX=kX+MNOG;};
			while((nY<(Ymin-(MNOG-1)))&(kY<Ymax)) {nY=nY+MNOG;kY=kY+MNOG;};
//			while((nX<Xmin)&(kX<Xmax)) {nX++;kX++;};
//			while((nY<Ymin)&(kY<Ymax)) {nY++;kY++;};
		if((nX==0)&(nY==0))
			k=k;
			NewMat[k].n.x=nX;NewMat[k].n.y=nY;
			NewMat[k].k.x=kX;NewMat[k].k.y=kY;
			NewMat[k].z.x=kX-nX+1;NewMat[k].z.y=kY-nY+1;
			// Вырезка из исх. ВМР результирующей.
			{
				CPaintDC dc(this);
				 BITMAP bp;
				CBitmap *old;
				CBitmap *old1;
				 CDC ndc,ndc1;
				BmpInf[i].ris.GetBitmap(&bp);
				ndc1.CreateCompatibleDC(&dc);
				 ndc.CreateCompatibleDC(&dc);
				old=ndc.SelectObject(&BmpInf[i].ris);
				NewMat[k].ris.DeleteObject();
				NewMat[k].ris.CreateCompatibleBitmap(&dc,(kX+1)/MNOG-nX/MNOG,(kY+1)/MNOG-nY/MNOG);
				old1=ndc1.SelectObject(&NewMat[k].ris);
				ndc1.BitBlt(0,0,(kX+1)/MNOG-nX/MNOG,(kY+1)/MNOG-nY/MNOG, &ndc,nX/MNOG,bp.bmHeight-(kY+1)/MNOG,SRCCOPY);
				ndc1.SelectObject(old1);
				ndc.SelectObject(old);
				ndc.DeleteDC();
				ndc1.DeleteDC();

			};
		};

		k++;
	  };
//  Формирование  выходного массива полигонов.	
	  for(i=0;i<kMat;i++)
	  for(j=0;j<RezREO.kPodgrup[i];j++) 
		  for(k=0;k<RezREO.kElemPod[i][j];k++)
	  {
//		  char buf1[100]; 


			  BITMAP bp1,bp2;
//		  if((i==0)&(j==0)&(k==2))
//			  k=k;
//		  sprintf(buf1,"старый рисунок NewNumMat[i][j]=%d",NewNumMat[i][j]);
//		  AfxMessageBox(buf1);
		  BmpInf[Pol[RezREO.Podgrup[i][j][k]].ma].ris.GetBitmap(&bp1);
//		  sprintf(buf1,"новый рисунок kNewMat=%d",kNewMat);
//		  AfxMessageBox(buf1);
//		  sprintf(buf1,"Есть новый рисунок? i=%d  j=%d  NewNumMat[i][j]=%d",i,j/*,NewNumMat[i][j]*/);
//		  m_Ris.SetBitmap(NewMat[NewNumMat[i][j]].ris);
//		  AfxMessageBox(buf1);
		  if(RezREO.Podgrup[i][j][k]==14)
			  i=i;
		  NewMat[NewNumMat[i][j]].ris.GetBitmap(&bp2);
		  newPol[RezREO.Podgrup[i][j][k]].ma=NewNumMat[i][j];
		  newPol[RezREO.Podgrup[i][j][k]].dv=Pol[RezREO.Podgrup[i][j][k]].dv;
		  newPol[RezREO.Podgrup[i][j][k]].kv=Pol[RezREO.Podgrup[i][j][k]].kv;
		  newPol[RezREO.Podgrup[i][j][k]].pr=true;
		  for(u=0;u<Pol[RezREO.Podgrup[i][j][k]].kv;u++)
		  {


			  if((bp1.bmWidth==bp2.bmWidth)&(bp1.bmHeight==bp2.bmHeight))
			  {
				newPol[RezREO.Podgrup[i][j][k]].vh[u].x=Pol[RezREO.Podgrup[i][j][k]].vh[u].x;
				newPol[RezREO.Podgrup[i][j][k]].vh[u].y=Pol[RezREO.Podgrup[i][j][k]].vh[u].y;
			  }
			  else
			  {
					int Xold,Yold,newX,newY,rX,rY;float xx,yy;
					Xold=Okrugl(((MNOG*bp1.bmWidth-1)*Pol[RezREO.Podgrup[i][j][k]].vh[u].x));
					Yold=Okrugl(((MNOG*bp1.bmHeight-1)*Pol[RezREO.Podgrup[i][j][k]].vh[u].y));
					newX=Xold-NewMat[newPol[RezREO.Podgrup[i][j][k]].ma].n.x;
					newY=Yold-NewMat[newPol[RezREO.Podgrup[i][j][k]].ma].n.y;
					rX=NewMat[newPol[RezREO.Podgrup[i][j][k]].ma].z.x;
					rY=NewMat[newPol[RezREO.Podgrup[i][j][k]].ma].z.y;
					yy=((float)newY)/((float)rY);
					xx=((float)newX)/((float)rX);
					if((xx>1)||(yy>1)||(xx<0)||(yy<0))
					{
						//AfxMessageBox("Внутренняя ошибка, кооординаты больше 1, обратитесь к разработчику");
						AfxMessageBox("Internal error, coordinates exceeds 1, Consult developer");
						Optimum=false;return; 
					};
					newPol[RezREO.Podgrup[i][j][k]].vh[u].x=xx;
					newPol[RezREO.Podgrup[i][j][k]].vh[u].y=yy;
			  };
		  };
		  for(u=0;u<4;u++)
			  newPol[RezREO.Podgrup[i][j][k]].xyz[u]=Pol[RezREO.Podgrup[i][j][k]].xyz[u];
	  };

//	  sprintf(buf,"k=%d",k);
//	  AfxMessageBox(buf);
	Optimum=TRUE; int sumgrup=0,sum=0;//CString s="";
//	s="Оптимизация закончена ";

	for(i=0;i<kMat;i++) 
	{
	  sumgrup=sumgrup+RezREO.kPodgrup[i];
		for(j=0;j<RezREO.kPodgrup[i];j++) 
		  sum=sum+RezREO.kElemPod[i][j];// .kPodgrup[i];
	};
//	sprintf(buf,"Оптимизация закончена %d %d %d %d %d %d", RezREO.kPodgrup[0], RezREO.kPodgrup[1], RezREO.kPodgrup[2], RezREO.kPodgrup[3], RezREO.kPodgrup[4], RezREO.kPodgrup[5]);
	//sprintf(buf,"Оптимизация закончена, обработано  %d полигонов,   %d групп  ",sum, sumgrup);
	sprintf(buf,"Optimisation complete, proceded %d polygons, %d groups",sum, sumgrup);
	AfxMessageBox(buf);

}



bool CREODlg::Peres(int n1, int n2)
{
	int i,j,rez;
	int kol1=0,kol2=0;
	CRgn rg1,rg2,rgRez;
	CPoint p1[4],p2[4];

	if(((n1==5)&(n2==6))||((n1==6)&(n2==5)))
		n1=n1;
	
	rgRez.CreateRectRgn(0,0,100,100);
//	rgRez.CreateRectRgn(0,0,40,40);
	for(i=0;i<Pol[n1].kv;i++)
	{
		BITMAP bp;
		if(BmpInf[Pol[n1].ma].ris.GetBitmap(&bp)==0)
		{
			//AfxMessageBox("В функции пересечения возникла ошибка в if(BmpInf[n2].ris.GetBitmap(&bp)==0), обратитесь к разработчику");
			AfxMessageBox("Error in if(BmpInf[n2].ris.GetBitmap(&bp)==0), Consult developer");
			return true;
		};
//		p1[i].x=Okrugl((Pol[n1].vh[i].x*(bp.bmHeight-1)));
//		p1[i].y=Okrugl((Pol[n1].vh[i].y*(bp.bmWidth-1)));
		p1[i].x=Okrugl((Pol[n1].vh[i].x)*((bp.bmHeight*MNOG-1)));
		p1[i].y=Okrugl((Pol[n1].vh[i].y)*(bp.bmWidth*MNOG-1));
	};
	for(i=0;i<Pol[n2].kv;i++)
	{
		BITMAP bp;
		if(BmpInf[Pol[n2].ma].ris.GetBitmap(&bp)==0)
		{
			//AfxMessageBox("В функции пересечения возникла ошибка в if(BmpInf[n2].ris.GetBitmap(&bp)==0), обратитесь к разработчику");
			AfxMessageBox("Error in if(BmpInf[n2].ris.GetBitmap(&bp)==0), Consult developer");
			return true;
		};
//		p2[i].x=Okrugl((Pol[n2].vh[i].x*(bp.bmHeight-1)));
//		p2[i].y=Okrugl((Pol[n2].vh[i].y*(bp.bmWidth-1)));
		p2[i].x=Okrugl((Pol[n2].vh[i].x)*(bp.bmHeight*MNOG-1));
		p2[i].y=Okrugl((Pol[n2].vh[i].y)*(bp.bmWidth*MNOG-1));

	};

	rg2.CreatePolygonRgn(p2,Pol[n2].kv,ALTERNATE);
	rg1.CreatePolygonRgn(p1,Pol[n1].kv,ALTERNATE);

	rez=rgRez.CombineRgn(&rg1,&rg2,RGN_AND);
	switch(rez)
	{
	case COMPLEXREGION:
		//AfxMessageBox("COMPLEXREGION");
		return true;
		break;
	case ERROR:
		//AfxMessageBox("В функции пересечения полигонов произошла ошибка ERROR, обратитесь к разработчику.");
		AfxMessageBox("ERROR in overlaping function, consult developer");
		return true;
		break;
	case NULLREGION:
		//AfxMessageBox("NULLREGION");
		kol1=0;kol2=0;
		for(i=0;i<Pol[n1].kv;i++)
			for(j=0;j<Pol[n2].kv;j++)
				if((p1[i].x==p2[j].x)&(p1[i].y==p2[j].y)) 
				{
					kol1++;
					if(Pol[n1].xyz[i]==Pol[n2].xyz[j]) kol2++;
				}

//		for(i=0;i<Pol[n1].kv;i++)
//			for(j=0;j<Pol[n2].kv;j++)
//				if(Pol[n1].xyz[i]==Pol[n2].xyz[j])
//					kol2++;
//		if(kol1>1)
//		{
//			if(kol2>1) return false; else return true;
//			if(kol2>1) return false; else return true;
//			char buf[100];
//			sprintf(buf,"kol1=%d   kol2=%d",kol1,kol2);
//			AfxMessageBox(buf);
			if(kol1>0)
			{
				if(kol1==kol2) 
					return false; 
				else 
					return true;
			}
			else 
				return false;
///		}
//		else return false;
//		break;
	case SIMPLEREGION:
		//AfxMessageBox("SIMPLEREGION");
		return true;
//		break;
	default:
		//AfxMessageBox("В функции пересечения полигонов произошла ошибка default, обратитесь к разработчику.");
		AfxMessageBox("default error in overlapping function, consult developer");
		return true;
//		break;
	};
//	return true;

}

//DEL void CREODlg::OnRgn() 
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL 	Peres(0,0);
//DEL }

bool CREODlg::SaveBMP(HBITMAP hbmp, LPCSTR filename)
{
 if (!hbmp) return TRUE;
 BITMAP info;

 ::GetObject(hbmp,sizeof(BITMAP),&info);
 int aSizeX = (info.bmWidth*sizeof(RGBTRIPLE)+3)&(~3);

 BITMAPFILEHEADER fHeader;
 BITMAPINFO bminf;

 LPBYTE rgb =(LPBYTE)malloc(aSizeX*info.bmHeight);
 if(!rgb) {
  TRACE("SaveBMP() : memory allocation error!\n");
  return FALSE;
 }

 HDC tmpdc=::CreateDC("DISPLAY",NULL,NULL,NULL);

 memset(&fHeader,0,sizeof(BITMAPFILEHEADER));
 fHeader.bfType = *((WORD*)"BM");
 fHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
aSizeX*info.bmHeight;
 fHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

 memset(&bminf,0,sizeof(BITMAPINFOHEADER));
 bminf.bmiHeader.biSize   = sizeof(BITMAPINFOHEADER);
 bminf.bmiHeader.biWidth  = info.bmWidth;
 bminf.bmiHeader.biHeight = info.bmHeight;
 bminf.bmiHeader.biPlanes = 1;
 bminf.bmiHeader.biBitCount = 24;
 bminf.bmiHeader.biCompression = BI_RGB;

 CFile f;
 if(!f.Open(filename,CFile::modeCreate|CFile::modeWrite)) {
  free(rgb);
  return FALSE;
 }

 ::GetDIBits(tmpdc,hbmp,0,info.bmHeight,rgb,&bminf,DIB_RGB_COLORS);
 f.WriteHuge(&fHeader,sizeof(BITMAPFILEHEADER));
 f.WriteHuge(&bminf.bmiHeader,sizeof(BITMAPINFOHEADER));
 f.WriteHuge(rgb,aSizeX*info.bmHeight);
 f.Close();

 free(rgb);
 ::DeleteDC(tmpdc);
 return TRUE;
}

int CREODlg::Okrugl(double a)
{
	int b;
	b=(int)a;
//	if((a-b)>0.5) return b+1; else return b;
	return b;

}

void CREODlg::OnLuminaire() 
{
	// TODO: Add your control notification handler code here
	TypeFile=0;
}

void CREODlg::OntBaker() 
{
	// TODO: Add your control notification handler code here
	TypeFile=1;
}

void CREODlg::OnSaveisx() 
{
	// TODO: Add your control notification handler code here
//	char buf[1000];//int i;
	char dr[100000],dir[10000],im[10000],ras[10000],buf[50000];;
	CFileDialog fd(false,NULL,NULL, OFN_HIDEREADONLY+
		OFN_OVERWRITEPROMPT,NULL,NULL);
//fd.m_ofn.lpstrTitle="Сохранение файла REO";
fd.m_ofn.lpstrTitle="Save";
//fd.m_ofn.lpstrFilter="REO файлы(*.reo)\0*.reo\0REC файлы(*.rec)\0*.rec\0Все файлы(*.*)\0*.*\0\0";
fd.m_ofn.lpstrFilter="RE Objects(*.reo)\0*.reo\0RE Characters(*.rec)\0*.rec\0All Files(*.*)\0*.*\0\0";
//fd.m_ofn.nFilterIndex=2;
//fd.m_ofn.lpstrInitialDir="D:\\VC++\\Мои проекты\\REO1\\sq_ma_obj_src";
fd.m_ofn.lpstrInitialDir="C:\\";

    if (fd.DoModal()==IDOK)
	{
		CString P,s;
		CFile f;
//		P=fd.GetFileName();
		P=fd .GetPathName();//.GetFileName();
		if(fd.m_ofn.nFilterIndex<3)
		{
//			strcpy(buf,P);
			_splitpath((LPCTSTR)P,dr,dir,im,ras );
			if(ras[0]==0)
			{
				if(fd.m_ofn.nFilterIndex==1)
					_makepath(buf,dr,dir,im,"reo");
				else _makepath(buf,dr,dir,im,"rec");
				P=buf;
			};
		};
		if(f.Open(P,CFile::modeCreate | CFile::modeWrite)==0)
		{
			//AfxMessageBox("Ошибка открытия выбранного файла");return;
			AfxMessageBox("I/O Error at selected file");return;
		};
		CString sr="";
		sr=GetSodEdit();
//		sprintf(buf,"dlsr=%d",sr.GetLength());
//		AfxMessageBox(buf);
		f.Write((LPCTSTR)sr,sr.GetLength());
		f.Close();
		AfxMessageBox("File save OK");
		SetWindowText(P);
	};
	
};

void CREODlg::UstEdit(int num) 
 {
 	m_MyRic.LineScroll(-kS);
 	m_MyRic.LineScroll(num);
 }


void CREODlg::OnNewtype() 
{
	// TODO: Add your control notification handler code here
	NewType=!NewType;
	
}


CString  CREODlg::GetSodEdit()
{
		int kol,dl,i;char buf[1000];//, soob[100];
		long obdl=0; CString s="";
		kol=m_MyRic.GetLineCount();
		for(i=0;i<kol;i++) 
		{
			dl=m_MyRic.GetLine(i,buf,1000);
			buf[dl]='\0';
			s=s+buf;
		};
		return s;
};


int CREODlg::ReadEdit(bool PrRead/*=true*/)
{
		int kol,dl/*,a*/,i;char buf[1000];//, soob[100];
		kS=0;
		kol=m_MyRic.GetLineCount();
		if(S!=NULL) delete[] S;
		S=new CString[kol];
		for(i=0;i<kol;i++) 
		{
			dl=m_MyRic.GetLine(i,buf,1000);
			if(PrRead)
				while((dl>0)&((buf[dl-1]=='\n')||(buf[dl-1]=='\r'))) dl--;
			buf[dl]='\0';
			S[i]=buf;kS++;
		};
		return kS;
}


BOOL CREODlg::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
//	cs.style=cs.style&(!DS_MODALFRAME);
//	cs.style=cs.style|WS_SYSMENU;
//	cs.style=WS_SYSMENU;
//	cs.style=WS_THICKFRAME;
	return CDialog::PreCreateWindow(cs);
}

void CREODlg::OnSaveFileAs() 
{
	// TODO: Add your command handler code here
	OnSaveisx();	
}

void CREODlg::OnSaveFile() 
{
	// TODO: Add your command handler code here
//		CStdioFile f;CString P,s;
		CFile f;//long razmer,dl;char *fff=NULL;
		if(f.Open(PatREO,CFile::modeCreate | CFile::modeWrite)==0)
		{
			//AfxMessageBox("Ошибка открытия выбранного файла");return;
			AfxMessageBox("I/O error at selected file");return;
		};
		CString sr="";
		sr=GetSodEdit();
//		sprintf(buf,"dlsr=%d",sr.GetLength());
//		AfxMessageBox(buf);
		f.Write((LPCTSTR)sr,sr.GetLength());
		f.Close();
		//AfxMessageBox("Файл записан.");
		AfxMessageBox("File save OK");

	
}

void CREODlg::OnCopy() 
{
	// TODO: Add your command handler code here
	if(m_MyRic.m_hWnd==m_MyRic.GetFocus()->m_hWnd)
	{
		m_MyRic.Copy();
	}
	 else
	 {
		 //AfxMessageBox("Установите фокус ввода на окно редактора.");
		 AfxMessageBox("Point to the editor's window");
	 };
}

void CREODlg::OnDelete() 
{
	// TODO: Add your command handler code here
	if(m_MyRic.m_hWnd==m_MyRic.GetFocus()->m_hWnd)
	{
		m_MyRic.Cut();
	}
	 else
	 {
		 //AfxMessageBox("Установите фокус ввода на окно редактора.");
		 AfxMessageBox("Point to the editor's window");
	 };
	
}

void CREODlg::OnPaste() 
{
	// TODO: Add your command handler code here
	if(m_MyRic.m_hWnd==m_MyRic.GetFocus()->m_hWnd)
	{
		m_MyRic.Paste();
	}
	 else
	 {
		 //AfxMessageBox("Установите фокус ввода на окно редактора.");
		 AfxMessageBox("Point to the editor's window");
	 };
	
}

UINT SearhString(LPVOID Param)
{
	CREODlg* pD = (CREODlg*)Param;
	CSearchCRichEditCtrl sd(&pD->m_MyRic);
	pD->process=true;
	sd.DoModal();
	pD->process=false;
	return 0;
};

void CREODlg::OnSearch() 
{
	// TODO: Add your command handler code here
//	if(m_MyRic.m_hWnd==m_MyRic.GetFocus()->m_hWnd)
//	{
	if(!process) AfxBeginThread(SearhString, this);

//	CSearchCRichEditCtrl sd(&m_MyRic, this);
//	sd.DoModal();


/*
		FINDTEXTEX ft;long n;char buf[100];
		ft.chrg.cpMax=m_MyRic.GetTextLength();ft.chrg.cpMin=2200;
//		ft.chrg.cpMax=2200;ft.chrg.cpMin=m_MyRic.GetTextLength();
//		ft.chrgText.cpMax=m_MyRic.GetTextLength();ft.chrgText.cpMin=2200;//m_MyRic.GetTextLength();
		ft.lpstrText="polygon";
		n=m_MyRic.FindText( FR_WHOLEWORD, &ft);
		sprintf(buf,"n=%d",n);
		AfxMessageBox(buf);
		if (n != -1)
		   m_MyRic.SetSel(ft.chrgText);
		else 
			AfxMessageBox("Текст 'polygon' не найден.");
*/

//	}
//	 else
//	 {
//		 AfxMessageBox("Установите фокус ввода на окно редактора.");
//	 };
	
}

void CREODlg::OnPoisk() 
{
	// TODO: Add your control notification handler code here
		FINDTEXTEX ft;long n;char buf[1000], *is;
		ft.chrg.cpMax=m_MyRic.GetTextLength();ft.chrg.cpMin=PosPoiska;
		is=new char[m_Poisk.GetLimitText()+10];
		m_Poisk.GetWindowText(is,m_Poisk.GetLimitText());
		ft.lpstrText=is;
		n=m_MyRic.FindText( FR_MATCHCASE, &ft);
//		sprintf(buf,"n=%d",n);
//		AfxMessageBox(buf);
		if (n != -1)
		{
			PosPoiska=ft.chrgText.cpMax;
//			char buf[100];
//			sprintf(buf,"begin=%d   end=%d",ft.chrgText.cpMin,ft.chrgText.cpMax);
//			AfxMessageBox(buf);
			m_MyRic.SetSel(ft.chrgText);
			long nl=m_MyRic.LineFromChar(PosPoiska);
			m_MyRic.LineScroll(-m_MyRic.GetLineCount());
			m_MyRic.LineScroll(nl-1);
		}
		else 
		{
			//sprintf(buf,"Текст '%s' не найден.",is);
			sprintf(buf,"Text '%s' not found",is);
			AfxMessageBox(buf);PosPoiska=0;
			m_PoskKn.SetWindowText("Find сначала");
		};
		delete[] is;
		//if(PosPoiska>0) m_PoskKn.SetWindowText("Найти далее");
		if(PosPoiska>0) m_PoskKn.SetWindowText("Find next");
	
};

void CREODlg::OnChangeEditpoisk() 
{
	// TODO: Add your control notification handler code here
	//m_PoskKn.SetWindowText("Найти сначала");
	m_PoskKn.SetWindowText("Find");
	m_MyRic.LineScroll(-m_MyRic.GetLineCount());
	PosPoiska=0;
	
}

void CREODlg::OnPreobrazmatr() 
{
	// TODO: Add your control notification handler code here
	int n,count,i,j;
	PravPreobr=false;
	m_MyRic.SetReadOnly();
	float vx,vy,vz,tx,ty,tz;char buf[10000];
	if(!IsFile)
	{
		//AfxMessageBox("Файл не открыт");return;
		AfxMessageBox("No object");return;
	};
	if(IsRec)
	{
		//AfxMessageBox("Преобразуются только файлы REO.");
		AfxMessageBox("Only REO for today");
		m_MyRic.SetReadOnly(false);return;
	};
	if(ReadEdit()<=0)
	{
		//AfxMessageBox("Редактор пуст");
		AfxMessageBox("Editor is empty");
		m_MyRic.SetReadOnly(false); return;
	};
//============Чтение секции матрицы преобразования вершин==========
	n=-1;count=0;N_M_P=-1;
	for(i=0;i<kS;i++)
		if (strncmp((LPCTSTR)S[i], "transform", 9) == 0){n=i;break;};
	if(n>=0)
	{
		if((n+3)>=kS)
		{
			//AfxMessageBox("Секция матрицы преобразования вершин не полна(выходит за границу файла)");
			AfxMessageBox("Transform section incomplete");
			m_MyRic.SetReadOnly(false);PravPreobr=false;return;
		};
		N_M_P=n+1;
		for(i=n+1;i<=n+3;i++)
		{
			if(sscanf((LPCTSTR)S[i], "%f %f %f %f", &MasPrebr[i-(n+1)][0], &MasPrebr[i-(n+1)][1], &MasPrebr[i-(n+1)][2], &MasPrebr[3][i-(n+1)])<4)
			{
				//AfxMessageBox("В секции матрицы преобразования вершин неверная информайия");
				AfxMessageBox("Wrong data in Transform section");
				UstEdit(i);m_MyRic.SetReadOnly(false);
				PravPreobr=false;return;
			};
		};
	}
	else 
	{
		//AfxMessageBox("Секция матрицы преобразования вершин не найдена");
		AfxMessageBox("Transform section not found");
		m_MyRic.SetReadOnly(false);Prav=FALSE;return;
	};

//============Конец чтения секции матрицы преобразования вершин==========
//   Чтение секции вершин в трехмерном пространстве
	n=-1;count=0;
	for(i=0;i<kS;i++)
		if (strncmp((LPCTSTR)S[i], "vertices", 8) == 0){n=i;break;};
	if(n>=0)
	{
		if(sscanf((LPCTSTR)S[n],"vertices %d", &kVer)<1)
		{
			//AfxMessageBox("Секция вершин - не найдено количество вершин");
			AfxMessageBox("Can not find total number of vertices");
			UstEdit(i);m_MyRic.SetReadOnly(false);
			PravPreobr=false;return;
		};    
		if((n+kVer)>kS)
		{
			//AfxMessageBox("Секция вершин не полна(выходит за границу файла)");
			AfxMessageBox("Vertices section incomplete");
			PravPreobr=false;m_MyRic.SetReadOnly(false);return;
		};
		if(Ver!=NULL) delete[] Ver;
		Ver=new TREUG[kVer];
		for(i=0;i<kVer;i++) Ver[i].pr=FALSE;
		float x,y,z;
		for(i=n+1;i<=n+kVer;i++)
		{
			if(sscanf((LPCTSTR)S[i], "%d %f %f %f", &count, &x, &y, &z)<4)
			{
				//AfxMessageBox("В секции вершин неверная информайия");
				AfxMessageBox("Wrong data in the vertices section");
				UstEdit(i);m_MyRic.SetReadOnly(false);
				PravPreobr=false;return;
			};
			if((count>=0)&(count<kVer)) 
			{
				Ver[count].x=x;Ver[count].y=y;
				Ver[count].z=z;Ver[count].pr=TRUE;
			}
			else
			{
				//AfxMessageBox("В секции вершин номер вершины больше количества вершин");
				AfxMessageBox("Vertex's number exceeds total number of vertices");
				UstEdit(i);m_MyRic.SetReadOnly(false);
				PravPreobr=false;return;
			};
		};
		for(j=0;j<kVer;j++)
			if(Ver[j].pr==FALSE)
			{
				//sprintf(buf,"В секции вершин вершина номер %d отсутсрвует",j);
				sprintf(buf,"Can not find vertex number %d",j);
				AfxMessageBox(buf);m_MyRic.SetReadOnly(false);
				PravPreobr=false;return;
			};
	}
	else 
	{
		//AfxMessageBox("Секция вершин не найдена");
		AfxMessageBox("Can not find vertices section");
		m_MyRic.SetReadOnly(false);Prav=FALSE;return;
	};

//=======Преобразование координат вершин======================
	n=-1;count=0;
	for(i=0;i<kS;i++)
		if (strncmp((LPCTSTR)S[i], "vertices", 8) == 0){n=i;break;};
	if(n>=0)
	{
		for(i=n+1;i<=n+kVer;i++)
		{
			if(sscanf((LPCTSTR)S[i], "%d %f %f %f", &count, &vx, &vy, &vz)<4)
			{
				//AfxMessageBox("В секции вершин неверная информайия");
				AfxMessageBox("Wrong data in the vertices section");
				UstEdit(i);m_MyRic.SetReadOnly(false);
				PravPreobr=false;return;
			};
			//Пересчет координат вершин
			tx=MasPrebr[0][0]*vx+MasPrebr[0][1]*vy+MasPrebr[0][2]*vz+MasPrebr[3][0];
			ty=MasPrebr[1][0]*vx+MasPrebr[1][1]*vy+MasPrebr[1][2]*vz+MasPrebr[3][1];
			tz=MasPrebr[2][0]*vx+MasPrebr[2][1]*vy+MasPrebr[2][2]*vz+MasPrebr[3][2];
			// Формирование новой строки вершин
			sprintf(buf,"%d %f %f %f",count,tx,ty,tz);
			// Поиск в редакторе исходной строки
			FINDTEXTEX ft;long n;char psk[100];//, *is;
			ft.chrg.cpMax=m_MyRic.GetTextLength();ft.chrg.cpMin=0;
			//is=new char[m_Poisk.GetLimitText()+10];
			//m_Poisk.GetWindowText(is,m_Poisk.GetLimitText());
			strcpy(psk,(LPCTSTR)S[i]);
			ft.lpstrText=psk;
			n=m_MyRic.FindText( FR_MATCHCASE, &ft);
			if (n != -1)
			{
				m_MyRic.SetSel(ft.chrgText);
				m_MyRic.ReplaceSel(buf);
			}
			else 
			{
				//sprintf(buf,"Текст '%s' не найден.",psk);
				sprintf(buf,"Text '%s' not found",psk);
				AfxMessageBox(buf);m_MyRic.SetReadOnly(false);
				PravPreobr=false;return;
			};

		};
	}
	else 
	{
		//AfxMessageBox("Секция вершин не найдена");
		AfxMessageBox("Vertices section not found");
		m_MyRic.SetReadOnly(false);Prav=FALSE;return;
	};
	for(i=N_M_P;i<N_M_P+3;i++)
	{
			FINDTEXTEX ft;long n;char psk[100];//,*ch[3];//, *is;
			CString ch[3];
			ch[0]="1 0 0 0";
			ch[1]="0 1 0 0";
			ch[2]="0 0 1 0";
			ft.chrg.cpMax=m_MyRic.GetTextLength();ft.chrg.cpMin=0;
			//is=new char[m_Poisk.GetLimitText()+10];
			//m_Poisk.GetWindowText(is,m_Poisk.GetLimitText());
			strcpy(psk,(LPCTSTR)S[i]);
			ft.lpstrText=psk;
			n=m_MyRic.FindText( FR_MATCHCASE, &ft);
			if (n != -1)
			{
				m_MyRic.SetSel(ft.chrgText);
				m_MyRic.ReplaceSel((LPCTSTR)ch[i-N_M_P]);
			}
			else 
			{
				//sprintf(buf,"Текст '%s' не найден.",psk);
				sprintf(buf,"Text '%s' not found",psk);
				AfxMessageBox(buf);m_MyRic.SetReadOnly(false);
				PravPreobr=false;return;
			};
	};
//=======Конец преобразования координат вершин======================
   //AfxMessageBox("Трансформация вершин закончена.");
   AfxMessageBox("Vertices transformation OK");
   PravPreobr=true;
   m_MyRic.SetReadOnly(false);

};

void CREODlg::OnReovrec() 
{
	// TODO: Add your control notification handler code here
	m_MyRic.SetReadOnly();
	if(!IsFile)
	{
		//AfxMessageBox("Никакой файл не открыт");
		AfxMessageBox("No one file to process");
		m_MyRic.SetReadOnly(false);return;
	};
	if(!IsRec)
	{
		//AfxMessageBox("В редактор должен быть загружен файл REC.");
		AfxMessageBox("You need REC to be loaded in the editor");
		m_MyRic.SetReadOnly(false);return;
	};
	if(!EstReo)
	{
		//AfxMessageBox("Предварительно не раскодирован добавляемый файл REO.");
		AfxMessageBox("Load REO, you want to combine before action");
		m_MyRic.SetReadOnly(false);return;
	};
	if(ReadEdit(false)<=0)
	{
		//AfxMessageBox("Редактор пуст");
		AfxMessageBox("Editor is empty");
		m_MyRic.SetReadOnly(false); return;
	};
// Поиск и считывание количества материалов из REC
	int n=-1,count=0,kMatRec,NmatRec,i; char buf[300];
	for(i=0;i<kS;i++)
		if (strncmp((LPCTSTR)S[i], "materials", 9) == 0){n=i;break;};
	if(n>=0)
	{
		if(sscanf((LPCTSTR)S[n],"materials %d", &kMatRec)<1)
		{
			//AfxMessageBox("Секция материалы - не найдено количество материалов");
			AfxMessageBox("Can not find total number of materials");
			UstEdit(i);m_MyRic.SetReadOnly(false);
			return;
		};    
		if((n+kMat)>kS)
		{
			//AfxMessageBox("Секция материалы не найдена(выходит за границу файла)");
			AfxMessageBox("Can not find materials section");
			m_MyRic.SetReadOnly(false);return;
		};
		NmatRec=n+kMatRec;
	}
	else
	{
		//AfxMessageBox("Секция материалов не найдена.");
		AfxMessageBox("Can not find materials section");
		m_MyRic.SetReadOnly(false); return;
	};
// Конец поиска и считывания количества материалов из REC
//	sprintf(buf,"Закончено чтение секции материалов в REC, всего материалов %d",kMatRec);
//	AfxMessageBox(buf);
// Добавление списка материалов в REC
	// Заменить количество материалов в REC
	sprintf(buf,"materials %d\n",kMatRec+kMat);
	// Поиск и замена количества материалов в REC
		FINDTEXTEX ft;char psk[100];long rez;
		ft.chrg.cpMax=m_MyRic.GetTextLength();ft.chrg.cpMin=0;
		strcpy(psk,(LPCTSTR)S[n]);
		ft.lpstrText=psk;
		rez=m_MyRic.FindText( FR_MATCHCASE, &ft);
		if (rez != -1)
		{
			m_MyRic.SetSel(ft.chrgText);
			m_MyRic.ReplaceSel(buf);
		}
		else 
		{
			//sprintf(buf,"При попытке замены количества материалов в REC, текст '%s' не найден.Работа прервана.",psk);
			sprintf(buf,"At time of materials replacing in REC, text '%s' not found. Stopping",psk);
			AfxMessageBox(buf);m_MyRic.SetReadOnly(false);
			return;
		};

	CString s;
	s=S[NmatRec];
	for(i=0;i<kMat;i++)
	{
		sprintf(buf,"%d texture %s",i+kMatRec,(LPCTSTR)masBMP[i]);
		s=s+buf;s=s+"\n";
	};
	// Поиск последней строки материалов в редакторе.
		ft.chrg.cpMax=m_MyRic.GetTextLength();ft.chrg.cpMin=0;
		strcpy(psk,(LPCTSTR)S[NmatRec]);
		ft.lpstrText=psk;
		rez=m_MyRic.FindText( FR_MATCHCASE, &ft);
		if (rez != -1)
		{
			m_MyRic.SetSel(ft.chrgText);
			m_MyRic.ReplaceSel((LPCTSTR)s);
		}
		else 
		{
			//sprintf(buf,"При попытке материалов материалов в REC, текст '%s' не найден.Работа прервана.",psk);
			sprintf(buf,"At time of processing REC, text '%s' not found. Stopping",psk);
			AfxMessageBox(buf);m_MyRic.SetReadOnly(false);
			return;
		};
// Конец добавления списка материалов в REC
// Добавление списков вершин и полигонов
		// Поиск секции иерархии
		int kVerRec,kPolRec,rab,j;
		for(i=0;i<kS;i++)
		if (strncmp((LPCTSTR)S[i], "HIERARCHY:", 10) == 0){n=i;break;};
	if(n>=0)
	{
		if((n+1)>kS)
		{
			//AfxMessageBox("Секция вершин и полигонов не найдена(выходит за границу файла)");
			AfxMessageBox("Can not find vertices and polygons section in REC");
			m_MyRic.SetReadOnly(false);return;
		};
		if(sscanf((LPCTSTR)S[n+1],"Meshes:%d, Total vertices:%d, Total polygons:%d", &rab,&kVerRec,&kPolRec)<1)
		{
			//AfxMessageBox("Секция материалы - не найдено количество материалов");
			AfxMessageBox("Can not find total number of materials");
			UstEdit(i);m_MyRic.SetReadOnly(false);
			return;
		};    
		if((n+1+kVerRec+kPolRec)>kS)
		{
			//AfxMessageBox("Секция вершин и полигонов не найдена(выходит за границу файла)");
			AfxMessageBox("Can not find vertices and polygons section in REC");
			m_MyRic.SetReadOnly(false);return;
		};
//		NmatRec=n+kMatRec;
	}
	else
	{
		//AfxMessageBox("Секция иерархии не найдена."); 
		AfxMessageBox("Can not ind hierarchy section");
		m_MyRic.SetReadOnly(false); return;
	};
	// Конец поиска секции иерархии
	// Замена количества вершин и полигонов
	sprintf(buf,"Meshes:%2d, Total vertices:%4d, Total polygons:%4d\n",rab,kVerRec+kVer,kPolRec+kPol);
		ft.chrg.cpMax=m_MyRic.GetTextLength();ft.chrg.cpMin=0;
		strcpy(psk,(LPCTSTR)S[n+1]);
		ft.lpstrText=psk;
		rez=m_MyRic.FindText( FR_MATCHCASE, &ft);
		if (rez != -1)
		{
			m_MyRic.SetSel(ft.chrgText);
			m_MyRic.ReplaceSel(buf);
		}
		else 
		{
			//sprintf(buf,"При попытке материалов материалов в REC, текст '%s' не найден.Работа прервана.",psk);
			sprintf(buf,"At time of REC procesing, text '%s' not found. Stopping.",psk);
			AfxMessageBox(buf);m_MyRic.SetReadOnly(false);
			return;
		};
	// Конец замены количества вершин и полигонов
		// Поиск секции   MESH:
		for(i=0;i<kS;i++)
		if (strncmp((LPCTSTR)S[i], "  MESH:", 7) == 0){n=i;break;};
	if(n>=0)
	{
		if((n+kVerRec+kPolRec)>kS)
		{
			//AfxMessageBox("Секция вершин и полигонов не найдена(выходит за границу файла)");
			AfxMessageBox("Section vertices and polygons not found");
			m_MyRic.SetReadOnly(false);return;
		};
//		NmatRec=n+kMatRec;
	}
	else
	{
		//AfxMessageBox("Секция иерархии не найдена.");
		AfxMessageBox("Hierarchy section not found");
		m_MyRic.SetReadOnly(false); return;
	};
	// Конец поиска секции   MESH:
	// Замена количества вершин и полигонов
	sprintf(buf,"  MESH: DEPENDENT, Vertices:%4d, Polygons:%4d\n",kVerRec+kVer,kPolRec+kPol);
		ft.chrg.cpMax=m_MyRic.GetTextLength();ft.chrg.cpMin=0;
		strcpy(psk,(LPCTSTR)S[n]);
		ft.lpstrText=psk;
		rez=m_MyRic.FindText( FR_MATCHCASE, &ft);
		if (rez != -1)
		{
			m_MyRic.SetSel(ft.chrgText);
			m_MyRic.ReplaceSel(buf);
		}
		else 
		{
			//sprintf(buf,"При попытке материалов материалов в REC, текст '%s' не найден.Работа прервана.",psk);
			sprintf(buf,"At time of REC processing, text '%s' not found. Stopping",psk);
			AfxMessageBox(buf);m_MyRic.SetReadOnly(false);
			return;
		};
	// Конец замены количества вершин и полигонов
	// Добавление полигонов
	CString ss;char buf1[100];
	s=S[n+kVerRec+kPolRec+1];
	for(i=0;i<kPol;i++)
	{
//		sprintf(buf,"%d texture %s",i+kMatRec,(LPCTSTR)masBMP[i]);
		sprintf(buf,"    p[%4d]: M:%2d (%1d) ",i+kPolRec,Pol[i].ma+kMatRec,Pol[i].kv);
		ss=buf;
		for(j=0;j<Pol[i].kv;j++)
		{
			sprintf(buf1,"%4d (%9.6f,%9.6f)",Pol[i].xyz[j]+kVerRec,Pol[i].vh[j].x,Pol[i].vh[j].y);
			ss=ss+buf1;
		};
		if(Pol[i].dv) ss=ss+" F:2S";
		ss=ss+"\n";s=s+ss;
	};
	// Поиск последней строки полигонов в редакторе.
		ft.chrg.cpMax=m_MyRic.GetTextLength();ft.chrg.cpMin=0;
		strcpy(psk,(LPCTSTR)S[n+kVerRec+kPolRec+1]);
		ft.lpstrText=psk;
		rez=m_MyRic.FindText( FR_MATCHCASE, &ft);
		if (rez != -1)
		{
			m_MyRic.SetSel(ft.chrgText);
			m_MyRic.ReplaceSel((LPCTSTR)s);
		}
		else 
		{
			//sprintf(buf,"При попытке поиска последнего полигона в REC, текст '%s' не найден.Работа прервана.",psk);
			sprintf(buf,"At time of looking for last polygon in REC, text '%s' not found. Stopping",psk);
			AfxMessageBox(buf);m_MyRic.SetReadOnly(false);
			return;
		};
	// Конец добавления полигонов.
	// Добавление вершин
	//CString ss;
//	char buf1[100];
	s=S[n+kVerRec];
	for(i=0;i<kVer;i++)
	{
		sprintf(buf,"    v[%4d]:",i+kVerRec);
		ss=buf;
//		for(j=0;j<3;j++)
//		{
			sprintf(buf1," %9.6f %9.6f %9.6f",Ver[i].x,Ver[i].y,Ver[i].z);
			ss=ss+buf1;
//		};
//		if(Pol[i].dv) ss=ss+" F:2S";
		ss=ss+"\n";s=s+ss;
	};
	// Поиск последней строки вершин в редакторе.
		ft.chrg.cpMax=m_MyRic.GetTextLength();ft.chrg.cpMin=0;
		strcpy(psk,(LPCTSTR)S[n+kVerRec]);
		ft.lpstrText=psk;
		rez=m_MyRic.FindText( FR_MATCHCASE, &ft);
		if (rez != -1)
		{
			m_MyRic.SetSel(ft.chrgText);
			m_MyRic.ReplaceSel((LPCTSTR)s);
		}
		else 
		{
			//sprintf(buf,"При попытке поиска последнего полигона в REC, текст '%s' не найден.Работа прервана.",psk);
			sprintf(buf,"At time of looking for last polygon in REC, text '%s' not found. Stopping",psk);
			AfxMessageBox(buf);m_MyRic.SetReadOnly(false);
			return;
		};
	// Конец добавления вершин.
// Конец добавления списков вершин и полигонов
// Вывод диалога с сообщением о добавленных вершинах
	//sprintf(buf,"Добавлено %d вершин.",kVer);
	sprintf(buf,"Added %d vertices",kVer);
	ss=buf;
//	sdv.m_DobVer.SetWindowText(buf);
	s="";
	for(i=0;i<kVer;i++)
	{
		sprintf(buf,"    V:%4d W:%5.2f\n",i+kVerRec,1.0);
		s=s+buf;
	};
//	sdv.m_SpisDobVer.SetWindowText((LPCTSTR)s);
	m_MyRic.SetReadOnly(false);
	SpisDobVer sdv(ss,s,this);
	sdv.DoModal();
// Конец вывода диалога с сообщением о добавленных вершинах
}

void CREODlg::OnDelputi() 
{
	// TODO: Add your control notification handler code here
	if(!IsFile)
	{
		//AfxMessageBox("Файл не открыт");return;
		AfxMessageBox("No file");return;
	};
/*
	if(IsRec)
	{
		//AfxMessageBox("Пути удаляются только в файлах REO.");return;
		AfxMessageBox("Only for REO for today");return;
	};
*/
	if(ReadEdit()<=0)
	{
		//AfxMessageBox("Редактор пуст"); return;
		AfxMessageBox("Editor is empty"); return;
	};
	int i/*,j,k*/,n;char buf[1000];int count;CString s;
// Чтение секции материалов  (feof(stream))
	n=-1;count=0;bool est=FALSE;
	for(i=0;i<kS;i++)
		if (strncmp((LPCTSTR)S[i], "materials", 9) == 0){n=i;break;};
	if(n>=0)
	{
		if(!est){est=TRUE;Nmat=n;};
		if(sscanf((LPCTSTR)S[n],"materials %d", &kMat)<1)
		{
			//AfxMessageBox("Секция материалы - не найдено количество материалов");
			AfxMessageBox("Can not find total number of materials");
			UstEdit(i);
			Prav=FALSE;return;
		};    
		if((n+kMat)>kS)
		{
			//AfxMessageBox("Секция материалы не найдена(выходит за границу файла)");
			AfxMessageBox("Can not find materials section");
			Prav=FALSE;return;
		};
		if(masBMP!=NULL) delete[] masBMP;
		masBMP=new CString[kMat];s="";
		for(i=n+1;i<=n+kMat;i++)
		{
			strcpy(buf,S[i]);
			if(sscanf((LPCTSTR)S[i], "%d texture %100s", &count, buf)<2)
			{
				//AfxMessageBox("Строка в секции материалов не полна");
				AfxMessageBox("Incomplete string");
				UstEdit(i);
				Prav=FALSE;return;
			};
			strcpy(buf, S[i].Mid(S[i].Find("texture")+7));
			if((count>=0)&(count<kMat)) masBMP[count]=buf;
			else
			{
				//AfxMessageBox("В секции материалов номер материала больше количества материалов");
				AfxMessageBox("Material's number exceeds total number of materials");
				UstEdit(i);
				Prav=FALSE;return;
			};
			while(masBMP[count].GetAt(0)==' ') masBMP[count].Delete(0);
			itoa(count,buf,10);
			s=s+buf+" "+masBMP[count]+"     ";
		};
		for(i=0;i<kMat;i++)
			if(masBMP[i].GetLength()<=0)
			{
				//AfxMessageBox("В секции материалов название миниммум одного файла отсутствует");
				AfxMessageBox("Can not find at least one material's filename");
				UstEdit(i);
				Prav=FALSE;return;
			};
			Kmat=Nmat+kMat;
/*
//			sprintf(buf,"Секция материалов  %d %d", Nmat, Kmat);
//			AfxMessageBox(buf);
			if(BmpInf!=NULL) delete[] BmpInf;
			BmpInf=new BMPINF[kMat];
//			m_Ris.ShowWindow(SW_SHOWNORMAL);
//			::TranslateMessage(NULL);
			for(i=0;i<kMat;i++)
			{
				char drive[1000],dir[1000],fname[1000],ext[1000];
				strcpy(buf,masBMP[i]);
				_splitpath(buf,drive,dir,fname,ext );
				if((drive[0]=='\0')||((m_Udal.GetState()&0x0003)==1))
					_makepath(buf,Drive,Dir,fname,ext);
				BmpInf[i].ImFile[0]=fname;
				BmpInf[i].ImFile[1]=ext;
				BmpInf[i].ris.DeleteObject();
				if(!ReadBMP(&BmpInf[i].ris, buf))
				{
					sprintf(buf,"В секции материалов не читается файл иатериала %d  %s", i, masBMP[i]);
					UstEdit(i);
					AfxMessageBox(buf);
					Prav=FALSE;return;
				};
				//::Sleep(1000);
				
//				m_Ris.SetBitmap(BmpInf[i].ris);
//				Zadergka(500);
//				AfxMessageBox("Выведен битмап?");

			};
//			m_Ris.ShowWindow(SW_HIDE);
*/		
	}
	//else {AfxMessageBox("Секция материалы не найдена");Prav=FALSE;return;};
	else {AfxMessageBox("Can not find materials section");Prav=FALSE;return;};

	char buf1[10000],d[10000],dir[10000],im[10000],ex[10000];
	FINDTEXTEX ft;char psk[1000];long rez;
	for(i=n+1;i<=n+kMat;i++)
	{
		_splitpath((LPCTSTR)masBMP[i-(n+1)],d,dir,im,ex);
		_makepath(buf1,"","",im,ex);
		sprintf(buf,"%d texture %s",i-(n+1),buf1);
	// Поиск и замена записей в материалах
		ft.chrg.cpMax=m_MyRic.GetTextLength();ft.chrg.cpMin=0;
		strcpy(psk,(LPCTSTR)S[i]);
		ft.lpstrText=psk;
		rez=m_MyRic.FindText( FR_MATCHCASE, &ft);
		if (rez != -1)
		{
			m_MyRic.SetSel(ft.chrgText);
			m_MyRic.ReplaceSel(buf);
		}
		else 
		{
			//sprintf(buf,"При попытке замены строки материала, текст '%s' не найден.Работа прервана.",psk);
			sprintf(buf,"At time of processing material's string, text '%s' not found. Stopping",psk);
			AfxMessageBox(buf);m_MyRic.SetReadOnly(false);
			return;
		};

	};
	//AfxMessageBox("Удаление путей завершено.");
	AfxMessageBox("Paths removing OK");
}

void CREODlg::OnNewFile() 
{
	// TODO: Add your command handler code here
		PatREO="Без_имени.reo";
		SetWindowText(PatREO);
		ImFile[0]="Без_имени";ImFile[1]=".reo";
		m_NewIma.SetWindowText(ImFile[0]+"_ALT");
		Optimum=FALSE;Prav=FALSE;
		m_MyRic.SetWindowText("");IsRec=false;
	
}

void CREODlg::Onmaterials() 
{
	// TODO: Add your control notification handler code here
	ZadPoisk("materials");
}

void CREODlg::Onfaces() 
{
	// TODO: Add your control notification handler code here
	ZadPoisk("faces");
}

void CREODlg::Onbboxes() 
{
	// TODO: Add your control notification handler code here
	ZadPoisk("bboxes");
}

void CREODlg::Onbspheres() 
{
	// TODO: Add your control notification handler code here
	ZadPoisk("bspheres");
}

void CREODlg::OnPolygon() 
{
	// TODO: Add your control notification handler code here
	ZadPoisk("[POLYGON]");
}

bool CREODlg::ZadPoisk(CString s)
{
		FINDTEXTEX ft;long n,pp;char buf[1000], *is;
		ft.chrg.cpMax=m_MyRic.GetTextLength();
		ft.chrg.cpMin=0;
		is=new char[s.GetLength()+10];
		strcpy(is,s);ft.lpstrText=is;
		n=m_MyRic.FindText( FR_MATCHCASE, &ft);
		if (n != -1)
		{
			pp=ft.chrgText.cpMax;
			m_MyRic.SetSel(ft.chrgText);
			long nl=m_MyRic.LineFromChar(pp);
			m_MyRic.LineScroll(-m_MyRic.GetLineCount());
			m_MyRic.LineScroll(nl-1);
		}
		else 
		{
			//sprintf(buf,"Текст '%s' не найден.",is);
			sprintf(buf,"Text '%s' not found",is);
			AfxMessageBox(buf);return false;
		};
		delete[] is;
		return true;
}

void CREODlg::OnFont() 
{
	// TODO: Add your command handler code here
	char buf[300];
    CFontDialog dlgFont;CFont *OldF=NULL;//LOGFONT Old_lp;
//	OldF=m_MyRic.GetFont();
//	if(!OldF)
//	{
//		AfxMessageBox("Фонт не получен.");
//	}
//	else
//	{
	dlgFont.m_cf.lpLogFont=RabFont;
//	};
	dlgFont.m_cf.nFontType=SCREEN_FONTTYPE;
//	dlgFont.m_cf.lStructSize=sizeof(CHOOSEFONT);
	dlgFont.m_cf.Flags=dlgFont.m_cf.Flags|CF_INITTOLOGFONTSTRUCT|CF_EFFECTS;

    if (dlgFont.DoModal()==IDOK)
	{
//	 if(RabFont) delete RabFont;
//	 RabFont= new LOGFONT;
 	 dlgFont.GetCurrentFont(RabFont);
//	 sprintf(buf,"lfWidth=%d  lfUnderline=%d  lfStrikeOut=%d  lfQuality=%d",RabFont->lfWidth,RabFont->lfUnderline,RabFont->lfStrikeOut,RabFont->lfQuality);
//	 AfxMessageBox(buf);
 	 CFont cf;
	 if(cf.CreateFontIndirect(RabFont))  // create the font
	 {
		 m_MyRic.SetFont(&cf,true);
		 m_MyRic.Invalidate();
//		 AfxMessageBox("Фонт установлен.");
	 }
	 else
	 {
		//sprintf(buf,"Ошибка. Фонт не создан. Обратитесь к разработчику.");
		sprintf(buf,"Error. Can not create font. Contact developer.");
		AfxMessageBox(buf);
	 };
	}
//	else
//		AfxMessageBox("Вышли из выбора фонта");
	
}
