

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Mon Feb 27 22:30:51 2012
 */
/* Compiler settings for CopyUncPath.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __CopyUncPath_i_h__
#define __CopyUncPath_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICopyUncPathContextMenu_FWD_DEFINED__
#define __ICopyUncPathContextMenu_FWD_DEFINED__
typedef interface ICopyUncPathContextMenu ICopyUncPathContextMenu;
#endif 	/* __ICopyUncPathContextMenu_FWD_DEFINED__ */


#ifndef __CopyUncPathContextMenu_FWD_DEFINED__
#define __CopyUncPathContextMenu_FWD_DEFINED__

#ifdef __cplusplus
typedef class CopyUncPathContextMenu CopyUncPathContextMenu;
#else
typedef struct CopyUncPathContextMenu CopyUncPathContextMenu;
#endif /* __cplusplus */

#endif 	/* __CopyUncPathContextMenu_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ICopyUncPathContextMenu_INTERFACE_DEFINED__
#define __ICopyUncPathContextMenu_INTERFACE_DEFINED__

/* interface ICopyUncPathContextMenu */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_ICopyUncPathContextMenu;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("622BD82E-2B29-40D1-85D9-DC10F6EDD122")
    ICopyUncPathContextMenu : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ICopyUncPathContextMenuVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICopyUncPathContextMenu * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICopyUncPathContextMenu * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICopyUncPathContextMenu * This);
        
        END_INTERFACE
    } ICopyUncPathContextMenuVtbl;

    interface ICopyUncPathContextMenu
    {
        CONST_VTBL struct ICopyUncPathContextMenuVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICopyUncPathContextMenu_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICopyUncPathContextMenu_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICopyUncPathContextMenu_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICopyUncPathContextMenu_INTERFACE_DEFINED__ */



#ifndef __CopyUncPathLib_LIBRARY_DEFINED__
#define __CopyUncPathLib_LIBRARY_DEFINED__

/* library CopyUncPathLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_CopyUncPathLib;

EXTERN_C const CLSID CLSID_CopyUncPathContextMenu;

#ifdef __cplusplus

class DECLSPEC_UUID("A2FF774B-F6C1-4172-850F-AB337132967D")
CopyUncPathContextMenu;
#endif
#endif /* __CopyUncPathLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


