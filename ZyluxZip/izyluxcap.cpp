// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "izyluxcap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// IZyluxCap properties

/////////////////////////////////////////////////////////////////////////////
// IZyluxCap operations


/////////////////////////////////////////////////////////////////////////////
// IZyluxForm properties

/////////////////////////////////////////////////////////////////////////////
// IZyluxForm operations

SCODE CZyluxForm::Advise(LPUNKNOWN pNotifier)
{
	SCODE result;
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_ERROR, (void*)&result, parms,
		pNotifier);
	return result;
}

SCODE CZyluxForm::UnAdvise(LPUNKNOWN pNotifier)
{
	SCODE result;
	static BYTE parms[] =
		VTS_UNKNOWN;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_ERROR, (void*)&result, parms,
		pNotifier);
	return result;
}

void CZyluxForm::SetWindowPosition(long left, long top, long right, long bottom)
{
	static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,	left, top, right, bottom);
}

void CZyluxForm::CenterOnRect(long left, long top, long right, long bottom)
{
	static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,	left, top, right, bottom);
}
