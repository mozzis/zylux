// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// CZyluxCap wrapper class

class CZyluxCap : public COleDispatchDriver
{
public:
	CZyluxCap() {}		// Calls COleDispatchDriver default constructor
	CZyluxCap(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CZyluxCap(const CZyluxCap& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
};
/////////////////////////////////////////////////////////////////////////////
// CZyluxForm wrapper class

class CZyluxForm : public COleDispatchDriver
{
public:
	CZyluxForm() {}		// Calls COleDispatchDriver default constructor
	CZyluxForm(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CZyluxForm(const CZyluxForm& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	SCODE Advise(LPUNKNOWN pNotifier);
	SCODE UnAdvise(LPUNKNOWN pNotifier);
  void SetWindowPosition(long left, long top, long right, long bottom);
  void CenterOnRect(long left, long top, long right, long bottom);
};
