
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0280 */
/* at Wed Oct 04 12:07:12 2000
 */
/* Compiler settings for C:\Code\Zylux\TestATL\TestATL.odl:
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

#ifndef __TestATL_i_h__
#define __TestATL_i_h__

/* Forward Declarations */ 

#ifndef __ITestATL_FWD_DEFINED__
#define __ITestATL_FWD_DEFINED__
typedef interface ITestATL ITestATL;
#endif 	/* __ITestATL_FWD_DEFINED__ */


#ifndef __TestATL_FWD_DEFINED__
#define __TestATL_FWD_DEFINED__

#ifdef __cplusplus
typedef class TestATL TestATL;
#else
typedef struct TestATL TestATL;
#endif /* __cplusplus */

#endif 	/* __TestATL_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __TestATL_LIBRARY_DEFINED__
#define __TestATL_LIBRARY_DEFINED__

/* library TestATL */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_TestATL;

#ifndef __ITestATL_DISPINTERFACE_DEFINED__
#define __ITestATL_DISPINTERFACE_DEFINED__

/* dispinterface ITestATL */
/* [uuid] */ 


EXTERN_C const IID DIID_ITestATL;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("DC7B1C4A-0C45-480D-A53E-96F7AFED7404")
    ITestATL : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ITestATLVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITestATL __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITestATL __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITestATL __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITestATL __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITestATL __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITestATL __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITestATL __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ITestATLVtbl;

    interface ITestATL
    {
        CONST_VTBL struct ITestATLVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITestATL_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITestATL_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITestATL_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITestATL_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITestATL_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITestATL_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITestATL_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ITestATL_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TestATL;

#ifdef __cplusplus

class DECLSPEC_UUID("664565D7-CE94-4369-A177-6AC3784DD52E")
TestATL;
#endif
#endif /* __TestATL_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


