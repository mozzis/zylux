// TestATLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestATL.h"
#include "TestATLDlg.h"
#include "DlgProxy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#import <mso9.dll> no_namespace rename("DocumentProperties", "DocumentPropertiesXL")   
#import <vbe6ext.olb> no_namespace   
#import <excel9.olb> rename("DialogBox", "DialogBoxXL") rename("RGB", "RBGXL") rename("DocumentProperties", "DocumentPropertiesXL")

//#include "mso97.tlh"
//#include "vbeext1.tlh"
//#include "excel8.tlh"


IID LIBID_Excel = { 0x00020813, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46  };
CLSID CLSID_MyAppEvents = 
{ 0xfa57d322, 0x86a6, 0x4772, { 0xbb, 0xe3, 0x8c, 0x5f, 0x9e, 0x64, 0xc8, 0xd9 } };

namespace Excel {
  class CAppEvents : 
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CAppEvents, &CLSID_MyAppEvents>,
    public IDispatchImpl<AppEvents, &__uuidof(AppEvents), &LIBID_Excel>,
    public IDispatchImpl<IAppEvents, &__uuidof(IAppEvents), &LIBID_Excel>
  {
    public:
      CAppEvents() { }

    BEGIN_COM_MAP(CAppEvents)
      COM_INTERFACE_ENTRY(IAppEvents)
      COM_INTERFACE_ENTRY(AppEvents)
      COM_INTERFACE_ENTRY2(IDispatch, AppEvents)
    END_COM_MAP()

    DECLARE_PROTECT_FINAL_CONSTRUCT()
  
  // AppEvents
    STDMETHOD(Invoke)(DISPID idm, REFIID riid, LCID lcid, WORD wflags, 
                      DISPPARAMS* pd, VARIANT* pvarresult,
                      EXCEPINFO* pexcep, UINT* argerr);
  public:
    // Raw methods provided by interface
    STDMETHOD(raw_NewWorkbook)(struct _Workbook * Wb);
    STDMETHOD(raw_SheetSelectionChange)(IDispatch * Sh, struct Range * Target);
    STDMETHOD(raw_SheetBeforeDoubleClick)(IDispatch * Sh, struct Range * Target, VARIANT_BOOL * Cancel);
    STDMETHOD(raw_SheetBeforeRightClick)(IDispatch * Sh, struct Range * Target, VARIANT_BOOL * Cancel);
    STDMETHOD(raw_SheetActivate)(IDispatch * Sh);
    STDMETHOD(raw_SheetDeactivate)(IDispatch * Sh);
    STDMETHOD(raw_SheetCalculate)(IDispatch * Sh);
    STDMETHOD(raw_SheetChange)(IDispatch * Sh, struct Range * Target);
    STDMETHOD(raw_WorkbookOpen)(struct _Workbook * Wb);
    STDMETHOD(raw_WorkbookActivate)(struct _Workbook * Wb);
    STDMETHOD(raw_WorkbookDeactivate)(struct _Workbook * Wb);
    STDMETHOD(raw_WorkbookBeforeClose)(struct _Workbook * Wb, VARIANT_BOOL * Cancel);
    STDMETHOD(raw_WorkbookBeforeSave)(struct _Workbook * Wb, VARIANT_BOOL SaveAsUI, VARIANT_BOOL * Cancel);
    STDMETHOD(raw_WorkbookBeforePrint)(struct _Workbook * Wb, VARIANT_BOOL * Cancel);
    STDMETHOD(raw_WorkbookNewSheet)(struct _Workbook * Wb, IDispatch * Sh);
    STDMETHOD(raw_WorkbookAddinInstall)(struct _Workbook * Wb);
    STDMETHOD(raw_WorkbookAddinUninstall)(struct _Workbook * Wb);
    STDMETHOD(raw_WindowResize)(struct _Workbook * Wb, struct Window * Wn);
    STDMETHOD(raw_WindowActivate)(struct _Workbook * Wb, struct Window * Wn);
    STDMETHOD(raw_WindowDeactivate)(struct _Workbook * Wb, struct Window * Wn);
    STDMETHOD(raw_SheetFollowHyperlink)(IDispatch * Sh, struct Hyperlink * Target );
  };
}

STDMETHODIMP Excel::CAppEvents::Invoke(DISPID idm, REFIID riid, LCID lcid, WORD wflags,
                       DISPPARAMS* pd, VARIANT* pvarresult,
                       EXCEPINFO* pexcep, UINT* argerr)
{
  LPCTSTR ptr = "Unknown-Event";

  switch(idm) 
    {
    case 0x61d: ptr = "NewWorkbook"; break;
    case 0x616: ptr = "SheetSelectionChange"; break;
    case 0x617: ptr = "SheetBeforeDoubleClick"; break;
    case 0x618: ptr = "SheetBeforeRightClick"; break;
    case 0x619: ptr = "SheetActivate"; break;
    case 0x61a: ptr = "SheetDeactivate"; break;
    case 0x61b: ptr = "SheetCalculate"; break;
    case 0x61c: 
      {
      ptr = "SheetChange";
      _variant_t vt = pd->rgvarg[0];
      IDispatch *pSh = (IDispatch *)vt;
      vt.Detach();
      vt = pd->rgvarg[1];
      CComQIPtr<Range, &__uuidof(Range)> pR((IDispatch *)vt);
//      struct Range *pR = (Range *)(IDispatch *)vt;
      vt.Detach();
      raw_SheetChange(pSh, pR);
      }
    break;
    case 0x61f:
      ptr = "WorkbookOpen";
    break;
    case 0x620: ptr = "WorkbookActivate"; break;
    case 0x621: ptr = "WorkbookDeactivate"; break;
    case 0x622: ptr = "WorkbookBeforeClose"; break;
    case 0x623: ptr = "WorkbookBeforeSave"; break;
    case 0x624: ptr = "WorkbookBeforePrint"; break;
    case 0x625: ptr = "WorkbookNewSheet"; break;
    case 0x626: ptr = "WorkbookAddinInstall"; break;
    case 0x627: ptr = "WorkbookAddinUninstall"; break;
    case 0x612: ptr = "WindowResize"; break;
    case 0x614: ptr = "WindowActivate"; break;
    case 0x615: ptr = "WindowDeactivate"; break;
    }
  TRACE("%s was fired!!!\n", ptr);
  return S_OK;
}

STDMETHODIMP Excel::CAppEvents::raw_NewWorkbook( struct _Workbook * Wb) 
{ 
  return S_OK; 
}
STDMETHODIMP Excel::CAppEvents::raw_SheetSelectionChange(IDispatch * Sh, struct Range * Target)
{ 
  return S_OK; 
}
STDMETHODIMP Excel::CAppEvents::raw_SheetBeforeDoubleClick(IDispatch * Sh, struct Range * Target, VARIANT_BOOL * Cancel)
{ 
  return S_OK; 
}
STDMETHODIMP Excel::CAppEvents::raw_SheetBeforeRightClick(IDispatch * Sh, struct Range * Target, VARIANT_BOOL * Cancel)
{ 
  return S_OK; 
}
STDMETHODIMP Excel::CAppEvents::raw_SheetActivate(IDispatch * Sh)
{ 
  return S_OK; 
}
STDMETHODIMP Excel::CAppEvents::raw_SheetDeactivate(IDispatch * Sh)
{ 
  return S_OK; 
}
STDMETHODIMP Excel::CAppEvents::raw_SheetCalculate(IDispatch * Sh)
{ 
  return S_OK; 
}
STDMETHODIMP Excel::CAppEvents::raw_SheetChange(IDispatch *Sh, struct Range *pR)
{ 
   CComQIPtr<_Worksheet, &__uuidof(_Worksheet)> pSheet(Sh);
   CComQIPtr<IRange, &__uuidof(IRange)> pRange(pR);
   return S_OK; 
}
STDMETHODIMP Excel::CAppEvents::raw_WorkbookOpen(struct _Workbook * Wb)
{ 
  return S_OK; 
}
STDMETHODIMP Excel::CAppEvents::raw_WorkbookActivate(struct _Workbook * Wb)
{ 
  return S_OK; 
}
STDMETHODIMP Excel::CAppEvents::raw_WorkbookDeactivate(struct _Workbook * Wb)
{ 
  return S_OK; 
}
STDMETHODIMP Excel::CAppEvents::raw_WorkbookBeforeClose(struct _Workbook * Wb, VARIANT_BOOL * Cancel)
{ 
  return S_OK; 
}
STDMETHODIMP Excel::CAppEvents::raw_WorkbookBeforeSave(struct _Workbook * Wb, VARIANT_BOOL SaveAsUI, VARIANT_BOOL * Cancel)
{ 
  return S_OK; 
}
STDMETHODIMP Excel::CAppEvents::raw_WorkbookBeforePrint(struct _Workbook * Wb, VARIANT_BOOL * Cancel)
{ 
  return S_OK; 
}
STDMETHODIMP Excel::CAppEvents::raw_WorkbookNewSheet(struct _Workbook * Wb, IDispatch * Sh)
{ 
  return S_OK; 
}
STDMETHODIMP Excel::CAppEvents::raw_WorkbookAddinInstall(struct _Workbook * Wb)
{ 
  return S_OK; 
}
STDMETHODIMP Excel::CAppEvents::raw_WorkbookAddinUninstall(struct _Workbook * Wb)
{ 
  return S_OK; 
}
STDMETHODIMP Excel::CAppEvents::raw_WindowResize(struct _Workbook * Wb, struct Window * Wn)
{ 
  return S_OK; 
}
STDMETHODIMP Excel::CAppEvents::raw_WindowActivate(struct _Workbook * Wb, struct Window * Wn)
{ 
  return S_OK; 
}
STDMETHODIMP Excel::CAppEvents::raw_WindowDeactivate(struct _Workbook * Wb, struct Window * Wn)
{ 
  return S_OK; 
}

STDMETHODIMP Excel::CAppEvents::raw_SheetFollowHyperlink(IDispatch * Sh, struct Hyperlink * Target)
{ 
  return S_OK; 
}

Excel::CAppEvents *g_pAppEvent = 0;
Excel::_ApplicationPtr g_pXL = 0;
DWORD g_dwEvtClass = 0;
BOOL g_bExcelAlready = FALSE;

// handles exceptions from COM (OLE) system calls
void dump_com_error(_com_error &e)
{
  _bstr_t bstrSource(e.Source());
  _bstr_t bstrDescription(e.Description());
  CString csMsg;
  csMsg.Format(_T("Error in OLE automation:\n"
                  "\tCode = %08lx\n"
                  "\tCode meaning = %s\n"
                  "\tSource = %s\n"
                  "\tDescription = %s\n"),
  e.Error(), e.ErrorMessage(), (LPCTSTR) bstrSource, (LPCTSTR) bstrDescription);
  AfxMessageBox(csMsg, MB_ICONEXCLAMATION);
}

IConnectionPoint *cPoints[256];

static BOOL DoExcelConnect()
{
  BOOL bRet = FALSE;
  
  IConnectionPointContainer    *pCPC = NULL;
  IConnectionPoint             *pCP = NULL;
  IEnumConnectionPoints        *pECP = NULL;
  try // allow local handling of COM (OLE) errors
    {
    g_pXL.GetActiveObject(L"Excel.Application");
    if (g_pXL)
      g_bExcelAlready = TRUE;
    else // if not running yet
      g_pXL.CreateInstance(L"Excel.Application"); // start it up!
    if (0 /* still! */ == g_pXL)
      throw _com_error(CO_E_CREATEPROCESS_FAILURE); // couldn't start Excel

    g_pAppEvent = new CComObject<Excel::CAppEvents>;
    if(g_pAppEvent == NULL) return FALSE;
    g_pXL->Visible[0] = -1;
    g_pXL->EnableEvents = -1;

    HRESULT hr = g_pXL->QueryInterface(IID_IConnectionPointContainer, (void **)&pCPC);
    if(FAILED(hr))
      throw _com_error(hr);
    // fails here!
    hr = pCPC->FindConnectionPoint(__uuidof(Excel::AppEvents), &pCP);

    pCPC->Release();    // Always Release now, even before checking.
    if(FAILED(hr))
      throw _com_error(hr);

    hr = pCP->Advise((Excel::AppEvents *)g_pAppEvent, &g_dwEvtClass);   //Turn on event support.
    pCP->Release();

    if(FAILED(hr))
      throw _com_error(hr);
    }
  catch (_com_error &e) // here if there was an OLE exception
    {
    dump_com_error(e); // display the error
    bRet = FALSE;      // signal problem
    }
  return bRet;
}

static BOOL DoExcelDisconnect()
{
  IConnectionPointContainer    *pCPC = NULL;
  IConnectionPoint             *pCP = NULL;
  if (0 == g_pXL || 0 == g_pAppEvent)
    return TRUE;
  HRESULT hr = g_pXL->QueryInterface(IID_IConnectionPointContainer, (void **)&pCPC);
  if(FAILED(hr)) return FALSE;
  hr = pCPC->FindConnectionPoint(__uuidof(Excel::AppEvents), &pCP);
  pCPC->Release();    // Always Release now, even before checking.
  if(FAILED(hr)) return FALSE;
  hr = pCP->Unadvise(g_dwEvtClass);    //Turn off event support.
  pCP->Release();
  if(FAILED(hr)) return FALSE;
  g_pAppEvent = 0;
  if (g_bExcelAlready)
    g_pXL->Quit();
  else
    g_pXL = 0;
  return TRUE;
}

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
// CTestATLDlg dialog

IMPLEMENT_DYNAMIC(CTestATLDlg, CDialog);

CTestATLDlg::CTestATLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestATLDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestATLDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CTestATLDlg::~CTestATLDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CTestATLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestATLDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestATLDlg, CDialog)
	//{{AFX_MSG_MAP(CTestATLDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, OnConnect)
	ON_BN_CLICKED(IDC_BUTTON2, OnDisconnect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestATLDlg message handlers

BOOL CTestATLDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestATLDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestATLDlg::OnPaint() 
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
HCURSOR CTestATLDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CTestATLDlg::OnClose() 
{
	if (CanExit())
		CDialog::OnClose();
}

void CTestATLDlg::OnOK() 
{
	if (CanExit())
    {
    DoExcelDisconnect();
		CDialog::OnOK();
    }
}

void CTestATLDlg::OnCancel() 
{
	if (CanExit())
		CDialog::OnCancel();
}

BOOL CTestATLDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}

void CTestATLDlg::OnConnect() 
{
  DoExcelConnect();	
}

void CTestATLDlg::OnDisconnect() 
{
  DoExcelDisconnect();	
}

//    hr = pCPC->EnumConnectionPoints(&pECP);
//  if(FAILED(hr))
//  throw _com_error(hr);
//
//    ULONG ucbPoints = 0;
//    memset(cPoints, 0, sizeof(cPoints));
//    hr = pECP->Next(sizeof(cPoints), cPoints, &ucbPoints);
//
//    for (ULONG i = 0; i < ucbPoints; i++)
//      {
//      if (cPoints[i])
//        cPoints[i]->Release();
//      }
//    pECP->Release();
//
