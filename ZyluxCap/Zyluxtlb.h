/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Sep 25 14:35:07 2000
 */
/* Compiler settings for C:\Code\Zylux\ZyluxCap\ZyluxCap.odl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __Zyluxtlb_h__
#define __Zyluxtlb_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IZyluxCap_FWD_DEFINED__
#define __IZyluxCap_FWD_DEFINED__
typedef interface IZyluxCap IZyluxCap;
#endif 	/* __IZyluxCap_FWD_DEFINED__ */


#ifndef __ZyluxCap_FWD_DEFINED__
#define __ZyluxCap_FWD_DEFINED__

#ifdef __cplusplus
typedef class ZyluxCap ZyluxCap;
#else
typedef struct ZyluxCap ZyluxCap;
#endif /* __cplusplus */

#endif 	/* __ZyluxCap_FWD_DEFINED__ */


#ifndef __IZyluxNotify_FWD_DEFINED__
#define __IZyluxNotify_FWD_DEFINED__
typedef interface IZyluxNotify IZyluxNotify;
#endif 	/* __IZyluxNotify_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __ZyluxCap_LIBRARY_DEFINED__
#define __ZyluxCap_LIBRARY_DEFINED__

/* library ZyluxCap */
/* [helpstring][version][uuid] */ 

typedef /* [helpstring][uuid] */ 
enum ZYNOTIFYCAT
    {	ZYNOTIFY_APP	= 0,
	ZYNOTIFY_CAPTURE	= ZYNOTIFY_APP + 1
    }	ZYNOTIFYCAT;

typedef /* [helpstring][uuid] */ 
enum ZYNOTIFYCODE
    {	ZYCODE_COMPLETE	= 0,
	ZYCODE_CANCELED	= ZYCODE_COMPLETE + 1
    }	ZYNOTIFYCODE;


EXTERN_C const IID LIBID_ZyluxCap;

#ifndef __IZyluxCap_DISPINTERFACE_DEFINED__
#define __IZyluxCap_DISPINTERFACE_DEFINED__

/* dispinterface IZyluxCap */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID_IZyluxCap;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("F0CB6025-7876-11D2-88A4-00104BF194E2")
    IZyluxCap : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IZyluxCapVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IZyluxCap __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IZyluxCap __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IZyluxCap __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IZyluxCap __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IZyluxCap __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IZyluxCap __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IZyluxCap __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IZyluxCapVtbl;

    interface IZyluxCap
    {
        CONST_VTBL struct IZyluxCapVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IZyluxCap_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IZyluxCap_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IZyluxCap_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IZyluxCap_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IZyluxCap_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IZyluxCap_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IZyluxCap_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IZyluxCap_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ZyluxCap;

#ifdef __cplusplus

class DECLSPEC_UUID("F0CB6023-7876-11D2-88A4-00104BF194E2")
ZyluxCap;
#endif

#ifndef __IZyluxNotify_INTERFACE_DEFINED__
#define __IZyluxNotify_INTERFACE_DEFINED__

/* interface IZyluxNotify */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IZyluxNotify;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("32FD1680-348C-41cf-BE53-B0148CAEC0BA")
    IZyluxNotify : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Notify( 
            /* [in] */ long lCategory,
            /* [in] */ long lReason,
            /* [in] */ IUnknown __RPC_FAR *pUnk) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IZyluxNotifyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IZyluxNotify __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IZyluxNotify __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IZyluxNotify __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IZyluxNotify __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IZyluxNotify __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IZyluxNotify __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IZyluxNotify __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Notify )( 
            IZyluxNotify __RPC_FAR * This,
            /* [in] */ long lCategory,
            /* [in] */ long lReason,
            /* [in] */ IUnknown __RPC_FAR *pUnk);
        
        END_INTERFACE
    } IZyluxNotifyVtbl;

    interface IZyluxNotify
    {
        CONST_VTBL struct IZyluxNotifyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IZyluxNotify_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IZyluxNotify_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IZyluxNotify_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IZyluxNotify_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IZyluxNotify_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IZyluxNotify_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IZyluxNotify_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IZyluxNotify_Notify(This,lCategory,lReason,pUnk)	\
    (This)->lpVtbl -> Notify(This,lCategory,lReason,pUnk)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IZyluxNotify_Notify_Proxy( 
    IZyluxNotify __RPC_FAR * This,
    /* [in] */ long lCategory,
    /* [in] */ long lReason,
    /* [in] */ IUnknown __RPC_FAR *pUnk);


void __RPC_STUB IZyluxNotify_Notify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IZyluxNotify_INTERFACE_DEFINED__ */

#endif /* __ZyluxCap_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
