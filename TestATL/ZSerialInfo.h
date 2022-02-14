// ZSerialInfo.h : Declaration of the CZSerialInfo

#ifndef __ZSERIALINFO_H_
#define __ZSERIALINFO_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CZSerialInfo
class ATL_NO_VTABLE CZSerialInfo : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CZSerialInfo, &CLSID_ZSerialInfo>,
	public IDispatchImpl<IZSerialInfo, &IID_IZSerialInfo, &LIBID_TestATL>
{
public:
	CZSerialInfo()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ZSERIALINFO)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CZSerialInfo)
	COM_INTERFACE_ENTRY(IZSerialInfo)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IZSerialInfo
public:
	STDMETHOD(get_FlowControl)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_FlowControl)(/*[in]*/ short newVal);
	STDMETHOD(get_PortNum)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_PortNum)(/*[in]*/ short newVal);
	STDMETHOD(get_Parity)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_Parity)(/*[in]*/ short newVal);
	STDMETHOD(get_StopBits)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_StopBits)(/*[in]*/ short newVal);
	STDMETHOD(get_DataBits)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_DataBits)(/*[in]*/ short newVal);
	STDMETHOD(get_BaudRate)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_BaudRate)(/*[in]*/ long newVal);
};

#endif //__ZSERIALINFO_H_
