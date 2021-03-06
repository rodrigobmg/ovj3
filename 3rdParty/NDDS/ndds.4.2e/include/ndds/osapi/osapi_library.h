/*
 * @(#)osapi_library.h    generated by: makeheader    Mon Dec  3 23:07:48 2007
 *
 *		built from:	library.ifc
 */

#ifndef osapi_library_h
#define osapi_library_h



#ifndef osapi_type_h
  #include "osapi/osapi_type.h"
#endif
#ifndef osapi_dll_h
  #include "osapi/osapi_dll.h"
#endif

#if (defined(RTI_LINUX) || defined(RTI_SOL2))
  #include <dlfcn.h>
#endif

#if (defined(RTI_LINUX) || defined(RTI_SOL2))
  /* RTLD_LAZY and RTLD_NOW are already defined */
#else
  #define RTLD_LAZY   1
  #define RTLD_NOW    2
#endif

/*e \ingroup RTIOsapiLibraryClass
    \brief Whith this mode, the references to the library symbols are
    resolved when the code that references them is executed.
*/
#define RTI_OSAPI_LIBRARY_RTLD_LAZY RTLD_LAZY
/*e \ingroup RTIOsapiLibraryClass
    \brief Whith this mode, all the undefined symbols in the library 
    are resolved before RTIOsapiLibrary_open returns.
*/
#define RTI_OSAPI_LIBRARY_RTLD_NOW RTLD_NOW

#ifdef __cplusplus
    extern "C" {
#endif


extern RTIOsapiDllExport void *
RTIOsapiLibrary_open(const char *fileName,int mode);

extern RTIOsapiDllExport int
RTIOsapiLibrary_close(void * handle);

extern RTIOsapiDllExport void *
RTIOsapiLibrary_getSymbolAddress(void * handle,const char * symbol);


#ifdef __cplusplus
    }	/* extern "C" */
#endif


#endif /* osapi_library_h */
