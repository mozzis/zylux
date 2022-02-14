
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0280 */
/* at Thu Mar 14 21:37:36 2002
 */
/* Compiler settings for C:\Code\Zylux\ZyluxZip\ZyluxZip.odl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32 (32b run), ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __ZyluxZip_i_h__
#define __ZyluxZip_i_h__

/* Forward Declarations */ 

#ifndef __IZyluxZip_FWD_DEFINED__
#define __IZyluxZip_FWD_DEFINED__
typedef interface IZyluxZip IZyluxZip;
#endif 	/* __IZyluxZip_FWD_DEFINED__ */


#ifndef __ZyluxZip_FWD_DEFINED__
#define __ZyluxZip_FWD_DEFINED__

#ifdef __cplusplus
typedef class ZyluxZip ZyluxZip;
#else
typedef struct ZyluxZip ZyluxZip;
#endif /* __cplusplus */

#endif 	/* __ZyluxZip_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __ZyluxZip_LIBRARY_DEFINED__
#define __ZyluxZip_LIBRARY_DEFINED__

/* library ZyluxZip */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_ZyluxZip;

#ifndef __IZyluxZip_DISPINTERFACE_DEFINED__
#define __IZyluxZip_DISPINTERFACE_DEFINED__

/* dispinterface IZyluxZip */
/* [uuid] */ 


EXTERN_C const IID DIID_IZyluxZip;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("AB3992C6-C2A0-4617-902B-B9A7007A0728")
    IZyluxZip : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IZyluxZipVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IZyluxZip __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IZyluxZip __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IZyluxZip __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IZyluxZip __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IZyluxZip __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IZyluxZip __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IZyluxZip __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IZyluxZipVtbl;

    interface IZyluxZip
    {
        CONST_VTBL struct IZyluxZipVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IZyluxZip_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IZyluxZip_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IZyluxZip_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IZyluxZip_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IZyluxZip_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IZyluxZip_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IZyluxZip_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IZyluxZip_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ZyluxZip;

#ifdef __cplusplus

class DECLSPEC_UUID("B0FBB7DF-CC6F-4D82-89DB-9008D0AE6BED")
ZyluxZip;
#endif
#endif /* __ZyluxZip_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


