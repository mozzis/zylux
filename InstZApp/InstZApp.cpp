// InstZApp.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <atlbase.h>
#include <io.h>
#include "InstZApp.h"
#include "DlgGetVer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CInstZAppApp

BEGIN_MESSAGE_MAP(CInstZAppApp, CWinApp)
	//{{AFX_MSG_MAP(CInstZAppApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInstZAppApp construction

CInstZAppApp::CInstZAppApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CInstZAppApp object

CInstZAppApp theApp;

// Version of CRegKey which throws exceptions on errors
////////////////////////////////////////////////////////
class CMyRegKey : public CRegKey
{
  public:
  LONG SetValue(DWORD dwValue, LPCTSTR lpszValueName)
    { 
    m_strLastValName = lpszValueName; 
    m_strLastVal.Format("%d", dwValue);
    LONG lRes = CRegKey::SetValue(dwValue, lpszValueName);
    if (ERROR_SUCCESS != lRes)
      throw new CUserException;
    m_strLastVal.Empty();
    return lRes;
    }
	LONG QueryValue(DWORD& dwValue, LPCTSTR lpszValueName)
    {
    m_strLastValName = lpszValueName; 
    LONG lRes = CRegKey::QueryValue(dwValue, lpszValueName);
    if (ERROR_SUCCESS != lRes)
      throw new CUserException;
    return lRes;
    }
	LONG QueryValue(LPTSTR szValue, LPCTSTR lpszValueName, DWORD* pdwCount)
    {
    m_strLastValName = lpszValueName; 
    LONG lRes = CRegKey::QueryValue(szValue, lpszValueName, pdwCount);
    if (ERROR_SUCCESS != lRes)
      throw new CUserException;
    return lRes;
    }
	LONG SetValue(LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL)
    {
    m_strLastValName = lpszValueName; 
    m_strLastVal = lpszValue; 
    LONG lRes = CRegKey::SetValue(lpszValue, lpszValueName);
    if (ERROR_SUCCESS != lRes)
      throw new CUserException;
    return lRes;
    }
	static LONG WINAPI SetValue(HKEY hKeyParent, LPCTSTR lpszKeyName,
		LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL)
    {
    LONG lRes = CRegKey::SetValue(hKeyParent, lpszKeyName, lpszValue, lpszValueName);
    if (ERROR_SUCCESS != lRes)
      throw new CUserException;
    return lRes;
    }

	LONG SetKeyValue(LPCTSTR lpszKeyName, LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL)
    {
    m_strSubKeyName = lpszKeyName;
    m_strLastValName = lpszValueName; 
    m_strLastVal = lpszValue; 
    LONG lRes = CRegKey::SetKeyValue(lpszKeyName, lpszValue, lpszValueName);
    if (ERROR_SUCCESS != lRes)
      throw new CUserException;
    return lRes;
    }

	LONG Create(HKEY hKeyParent, LPCTSTR lpszKeyName,
		LPTSTR lpszClass = REG_NONE, DWORD dwOptions = REG_OPTION_NON_VOLATILE,
		REGSAM samDesired = KEY_ALL_ACCESS,
		LPSECURITY_ATTRIBUTES lpSecAttr = NULL,
		LPDWORD lpdwDisposition = NULL)
    {
    m_strKeyName = lpszKeyName;
    LONG lRes = CRegKey::Create(hKeyParent, lpszKeyName, lpszClass, dwOptions, samDesired, lpSecAttr, lpdwDisposition);
    if (ERROR_SUCCESS != lRes)
      throw new CUserException;
    return lRes;
    }
	LONG Open(HKEY hKeyParent, LPCTSTR lpszKeyName, REGSAM samDesired = KEY_ALL_ACCESS)
    {
    m_strKeyName = lpszKeyName;
    LONG lRes = CRegKey::Open(hKeyParent, lpszKeyName, samDesired);
    if (ERROR_SUCCESS != lRes)
      throw new CUserException;
    return lRes;
    }
	LONG Close()
    {
    LONG lRes = CRegKey::Close();
    if (ERROR_SUCCESS != lRes)
      throw new CUserException;
    m_strLastValName.Empty();
    m_strLastVal.Empty();
    m_strKeyName.Empty();
    m_strSubKeyName.Empty();
    return lRes;
    }
//  protected:
  CString m_strLastValName;
  CString m_strLastVal;
  CString m_strKeyName;
  CString m_strSubKeyName;
};

// Function to set up registry for the ZyluxCap app
// This way, install doesn't have to run the app to
// register the interfaces
//////////////////////////////////////////////////////////////////////
void SetupRegistry(LPCTSTR szDirInst)
{
  CMyRegKey cRK1, cRK2, cRK3, cRK4;
  CString csAppID("AppID"),
          csAppName("ZYLUXCAP.EXE"), 
          csAppProgID("ZyluxCap.Application"),
          csTLVer("1.0"),
          csAppClsID( "{F0CB6023-7876-11D2-88A4-00104BF194E2}"),
          csAppIfcID( "{F0CB6025-7876-11D2-88A4-00104BF194E2}"),
          csFormClsID("{EEF10E19-C379-11D2-88A4-00104BF194E2}"),
          csTypeLibID("{F0CB6024-7876-11D2-88A4-00104BF194E2}"),
          csNotIfcID( "{32FD1680-348C-41cf-BE53-B0148CAEC0BA}"),
          csOleClsID( "{00020420-0000-0000-C000-000000000046}"),
          csProxy("ProxyStubClsID"),
          csProxy32("ProxyStubClsID32"),
          csTypeLib("TypeLib"),
          csAppPath;

  csAppPath = szDirInst + csAppName;

  try
    {
    // HCR\AppID\ZYLUXCAP.EXE#AppID = {F0CB6023-7876-11D2-88A4-00104BF194E2}
    // HCR\AppID\{F0CB6023-7876-11D2-88A4-00104BF194E2} = ZyluxCap.Application
    cRK1.Open(HKEY_CLASSES_ROOT, csAppID, KEY_READ|KEY_WRITE);
    cRK1.SetKeyValue(csAppName,  csAppClsID,  csAppID);
    cRK1.SetKeyValue(csAppClsID, csAppProgID, 0);
    cRK1.Detach();

  // HCR\CLSID\{F0CB6023-7876-11D2-88A4-00104BF194E2} = ZyluxCap Application Class
  // HCR\CLSID\{F0CB6023-7876-11D2-88A4-00104BF194E2}#AppID = {F0CB6023-7876-11D2-88A4-00104BF194E2}
  // HCR\CLSID\{F0CB6023-7876-11D2-88A4-00104BF194E2}\InProcHandler32 = ole32.dll
  // HCR\CLSID\{F0CB6023-7876-11D2-88A4-00104BF194E2}\LocalServer32 = <INSTDIR>\ZYLUXCAP.EXE
  // HCR\CLSID\{F0CB6023-7876-11D2-88A4-00104BF194E2}\ProgID = ZyluxCap.Application
    cRK1.Open(HKEY_CLASSES_ROOT,  "CLSID", KEY_READ|KEY_WRITE);
    cRK1.SetKeyValue(csAppClsID,        "ZyluxCap Application Class", 0);
    cRK1.SetKeyValue(csAppClsID,        csAppClsID,                   "AppID");
    cRK2.Open(cRK1, csAppClsID, KEY_READ|KEY_WRITE);
    cRK2.SetKeyValue("InProcHandler32", "ole32.dll",                  0);
    cRK2.SetKeyValue("LocalServer32",   csAppPath,                    0);
    cRK2.SetKeyValue("ProgID",          csAppProgID,                  0);
    cRK2.Close();
  
  // HCR\CLSID\{EEF10E19-C379-11D2-88A4-00104BF194E2} = IZyluxForm
  // HCR\CLSID\{EEF10E19-C379-11D2-88A4-00104BF194E2}\ProxyStubClsid   = {00020420-0000-0000-C000-000000000046}
  // HCR\CLSID\{EEF10E19-C379-11D2-88A4-00104BF194E2}\ProxyStubClsid32 = {00020420-0000-0000-C000-000000000046}
  // HCR\CLSID\{EEF10E19-C379-11D2-88A4-00104BF194E2}\TypeLib = {F0CB6024-7876-11D2-88A4-00104BF194E2}
  // HCR\CLSID\{EEF10E19-C379-11D2-88A4-00104BF194E2}\TypeLib#Version = 1.0
    cRK1.SetKeyValue(csFormClsID,        "IZyluxForm", 0);
    cRK2.Open(cRK1, csFormClsID, KEY_READ|KEY_WRITE);
    cRK2.SetKeyValue(csProxy,   csOleClsID,   0);
    cRK2.SetKeyValue(csProxy32, csOleClsID,   0);
    cRK2.SetKeyValue(csTypeLib,          csTypeLibID,  0);
    cRK2.SetKeyValue(csTypeLib,          csTLVer,      "Version");
    cRK2.Close();
    cRK1.Detach();

  // HKEY_CLASSES_ROOT\Interface\{F0CB6025-7876-11D2-88A4-00104BF194E2} = IZyluxCap
  // HKEY_CLASSES_ROOT\Interface\{F0CB6025-7876-11D2-88A4-00104BF194E2}\ProxyStubClsid   = {00020420-0000-0000-C000-000000000046}
  // HKEY_CLASSES_ROOT\Interface\{F0CB6025-7876-11D2-88A4-00104BF194E2}\ProxyStubClsid32 = {00020420-0000-0000-C000-000000000046}
  // HKEY_CLASSES_ROOT\Interface\{F0CB6025-7876-11D2-88A4-00104BF194E2}\Typelib = {F0CB6024-7876-11D2-88A4-00104BF194E2}
  // HKEY_CLASSES_ROOT\Interface\{F0CB6025-7876-11D2-88A4-00104BF194E2}\Typelib#Version = 1.0
    cRK1.Open(HKEY_CLASSES_ROOT, "Interface", KEY_READ|KEY_WRITE);
    cRK1.SetKeyValue(csAppIfcID,         "IZyluxCap", 0);
    cRK2.Open(cRK1, csAppIfcID, KEY_READ|KEY_WRITE);
    cRK2.SetKeyValue(csProxy,   csOleClsID,  0);
    cRK2.SetKeyValue(csProxy32, csOleClsID,  0);
    cRK2.Close();
  
  // HKEY_CLASSES_ROOT\Interface\{32FD1680-348C-41cf-BE53-B0148CAEC0BA} = IZyluxNotify
  // HKEY_CLASSES_ROOT\Interface\{32FD1680-348C-41cf-BE53-B0148CAEC0BA}\ProxyStubClsid32 = {00020420-0000-0000-C000-000000000046}
  // HKEY_CLASSES_ROOT\Interface\{32FD1680-348C-41cf-BE53-B0148CAEC0BA}\TypeLib = {F0CB6024-7876-11D2-88A4-00104BF194E2}
    cRK1.SetKeyValue(csNotIfcID,         "IZyluxNotify", 0);
    cRK2.Open(cRK1, csNotIfcID, KEY_READ|KEY_WRITE);
    cRK2.SetKeyValue(csProxy32, csOleClsID,     0);
    cRK2.SetKeyValue(csTypeLib,          csTypeLibID,    0);
    cRK2.Close();
    cRK1.Detach();

  // HKEY_CLASSES_ROOT\TypeLib\{F0CB6024-7876-11D2-88A4-00104BF194E2}\1.0 = ZyluxCap
  // HKEY_CLASSES_ROOT\TypeLib\{F0CB6024-7876-11D2-88A4-00104BF194E2}\1.0\0\win32 = <INSTALLDIR>\ZyluxCap.exe
  // HKEY_CLASSES_ROOT\TypeLib\{F0CB6024-7876-11D2-88A4-00104BF194E2}\FLAGS = 0
  // HKEY_CLASSES_ROOT\TypeLib\{F0CB6024-7876-11D2-88A4-00104BF194E2}\HELPDIR = <INSTALLDIR>
    cRK1.Open(HKEY_CLASSES_ROOT, csTypeLib, KEY_READ|KEY_WRITE);
    cRK2.Create(cRK1, csTypeLibID);
    cRK2.SetKeyValue(csTLVer,   "ZyluxCap", 0);
    cRK3.Open(cRK2, csTLVer, KEY_READ|KEY_WRITE);
    cRK3.SetKeyValue("FLAGS",   "0",        0);
    cRK3.SetKeyValue("HELPDIR", szDirInst);
    cRK4.Create(cRK3, "0");
    cRK4.SetKeyValue("win32",   csAppPath, 0);
    cRK4.Close();
    cRK3.Close();
    cRK2.Close();
    cRK1.Detach();
 
  // HKEY_CLASSES_ROOT\ZyluxCap.Application = ZyluxCap.Application
  // HKEY_CLASSES_ROOT\ZyluxCap.Application\CLSID = {F0CB6023-7876-11D2-88A4-00104BF194E2}
    cRK1.Create(HKEY_CLASSES_ROOT, csAppProgID);
    cRK1.SetValue(csAppProgID);
    cRK1.SetKeyValue("CLSID", csAppClsID, 0);
    cRK1.Close();
    }
  catch (CUserException *)
    {
    CString csMsg;
    csMsg = "Error addressing registry:\n";
    csMsg += "Key   Name: ";
    csMsg += cRK1.m_strKeyName + "\n";
    csMsg += "Value Name: ";
    csMsg += cRK1.m_strLastValName;
    csMsg += "Value Name: ";
    csMsg += cRK1.m_strLastVal;
    }
}

// Function exported to Install Shield
// It will make sure the most recent version of ZyluxCap is installed, and also
// that it is the proper UK/US version
////////////////////////////////////////////////////////////////////////////////////
INSTZAPP_API CHAR WINAPI fnInstZApp(HWND hWnd, LPSTR, LPSTR szDirSupp, LPSTR szDirInst, LPSTR)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());

  CString csAppName = "ZyluxCap.Application\\CLSID";
  CRegKey crCLSID, crAppPath;
  CString csVersion = "<Not found>";

  TCHAR szAppPath[_MAX_PATH];
  ULONG ulAppPath = sizeof(szAppPath);
  
  memset(szAppPath, 0, sizeof(szAppPath));

  bool bUpdate = true;

  // get the path to ZyluxCap.exe it it's installed
  // look up the program's CLSID in the registry
  if (ERROR_SUCCESS == crCLSID.Open(HKEY_CLASSES_ROOT, csAppName, KEY_READ))
    {
    TCHAR szCLSID[80];
    ULONG ulCLSID = sizeof(szCLSID);
    // found the CLSID key, get its default value
    if (ERROR_SUCCESS == crCLSID.QueryValue(szCLSID, "", &ulCLSID))
      {
      CString csCLSID = "CLSID\\";
      csCLSID += szCLSID;
      csCLSID += "\\LocalServer32";
      // now open the key for the CLSID value found
      if (ERROR_SUCCESS == crAppPath.Open(HKEY_CLASSES_ROOT, csCLSID, KEY_READ))
        {
        // the program's path and filename are stored in the LocalServer32 value
        if (ERROR_SUCCESS == crAppPath.QueryValue(szAppPath, "", &ulAppPath))
          {
          if (!_taccess(szAppPath, 0)) // see if the file exists; returns 0 if success
            {
            DWORD dwDummy, dwSize = GetFileVersionInfoSize(szAppPath, &dwDummy);
            if (dwSize) // if present, get the file version info resource
              {
              BYTE *pVerInfo = new BYTE[dwSize];
              if (GetFileVersionInfo(szAppPath, 0, dwSize, pVerInfo))
                {
                UINT cbTranslate = 0;
                LPTSTR pvInfo = 0;
                // 040904b0 means English(US)
                LPTSTR pStrQuery = TEXT("\\StringFileInfo\\040904b0\\FileVersion");
                // convert the version to a string for the dialog to display
                if (VerQueryValue(pVerInfo, pStrQuery, (LPVOID*)&pvInfo, &cbTranslate))
                  {
                  CString csCopy = pvInfo;
                  LPCTSTR pDel = TEXT(" ,");
                  LPTSTR pCh1 = _tcstok(csCopy.GetBuffer(0), pDel),
                         pCh2 = _tcstok(0, pDel),
                         pCh3 = _tcstok(0, pDel);

                  if ( 2 > _ttoi(pCh1) ||
                       1 > _ttoi(pCh2) ||
                       6 > _ttoi(pCh3))
                    {
                    csVersion.Format("%s.%s.%s", pCh1, pCh2, pCh3);
                    }
                  else // don't update if correct version is present
                    bUpdate = false;
                  } // if file version field was found
                } // if version info read successfully
              delete [] pVerInfo;
              } // if file had version info
            } // if file was there
          else // file wasn't there
            szAppPath[0] = 0;
          } // if LocalServer32 value found
        } // if CLSID/progname\localserver32 key opened
      } // if progname/clsid read successfully
    } // if progname/clsid key found
  
  if (bUpdate)
    {
    CDlgGetVer dlg(CWnd::FromHandle(hWnd));
    dlg.SetVersion(csVersion);
    dlg.SetPrevVerPresent(0 != szAppPath[0]);
    dlg.DoModal();
    switch (dlg.GetUserChoice())
      {
      case CDlgGetVer::UPGRADE_US:
        csAppName = "ZYLUXCAP.EXE";
      break;
      case CDlgGetVer::UPGRADE_UK:
        csAppName = "ZyluxCapB.EXE";
      break;
      case CDlgGetVer::UPGRADE_NO:
        csAppName = "";
      default:
      break;
      }
    if (!csAppName.IsEmpty())
      {
      CString csNewApp = szDirSupp;
      csNewApp += "\\";
      csNewApp += csAppName;
      if (!szAppPath[0]) // no dest path from registry, use the install-to path
        {
         _tcscpy(szAppPath, szDirInst);
         _tcscat(szAppPath, "\\ZYLUXCAP.EXE");
        }

      ::CopyFile(csNewApp, szAppPath, FALSE);
        {
        CString csDrive, csDir;
        _tsplitpath(szAppPath, csDrive.GetBuffer(_MAX_DRIVE), csDir.GetBuffer(_MAX_DIR), 0, 0);
        csDir.ReleaseBuffer(); csDrive.ReleaseBuffer();
        csDrive += csDir;
        SetupRegistry(csDrive); // need just the path, not the filename
        }
      DWORD dwErr = GetLastError();
      }
    }
	return 1; // return non-zero to make InstallShield continue (finish) installing
}

