/*
 * @(#)clock_highResolution.h    generated by: makeheader    Mon Dec  3 23:07:52 2007
 *
 *		built from:	highResolution.ifc
 */

#ifndef clock_highResolution_h
#define clock_highResolution_h


  #ifndef clock_interface_h
    #include "clock/clock_interface.h"
  #endif
  #ifndef clock_dll_h
    #include "clock/clock_dll.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif

extern RTIClockDllExport void
RTIHighResolutionClock_delete(struct RTIClock *me);

extern RTIClockDllExport struct RTIClock *RTIHighResolutionClock_new();


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* clock_highResolution_h */
