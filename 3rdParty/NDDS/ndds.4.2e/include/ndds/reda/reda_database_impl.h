/*
 * @(#)reda_database_impl.h    generated by: makeheader    Mon Dec  3 23:07:54 2007
 *
 *		built from:	database_impl.ifc
 */

#ifndef reda_database_impl_h
#define reda_database_impl_h



  #ifndef reda_cursor_h
    #include "reda/reda_worker.h"
  #endif
  #ifndef reda_cursor_h
    #include "reda/reda_cursor.h"
  #endif
  #ifndef reda_weakReference_h
    #include "reda/reda_weakReference.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif

 
struct REDACursorPerWorker {
    struct REDAObjectPerWorker *_objectPerWorker;
    struct REDADatabase        *_database;
    struct REDAWeakReference    _tableReference;
};


/* ----------------------------------------------------------------- */
  #define REDACursorPerWorker_assertCursorMacro(cursorPerWorker,             \
                                                cursorPtr, worker)           \
  ((*(cursorPtr)) =                                                          \
       REDAWorker_assertObjectMacro(worker,                                  \
                                    (cursorPerWorker)->_objectPerWorker))

  #define REDACursorPerWorker_assertCursor REDACursorPerWorker_assertCursorMacro


/* ----------------------------------------------------------------- */
  #define REDACursorPerWorker_assertAndStartCursorMacro(              \
      cursorPerWorker, cursorPtr, failReasonPtr, worker)              \
  ( (REDACursorPerWorker_assertCursor(cursorPerWorker, cursorPtr, worker) \
     != NULL) \
    ? REDACursor_startMacro(*(cursorPtr), failReasonPtr) : RTI_FALSE )

#ifdef RTI_PRECONDITION_TEST
  #define REDACursorPerWorker_assertAndStartCursor \
    REDACursorPerWorker_assertAndStartCursorFnc
#else
  #define REDACursorPerWorker_assertAndStartCursor \
    REDACursorPerWorker_assertAndStartCursorMacro
#endif

/* ----------------------------------------------------------------- */
  #define REDACursorPerWorker_assertAndStartCursorSafeMacro( \
      cursorPerWorker, cursorPtr, failReasonPtr,        \
      cursorStack, cursorStackIndexPtr, worker)         \
  (                                                     \
    (REDACursorPerWorker_assertCursorMacro(cursorPerWorker, cursorPtr, \
                                           worker) != NULL) ?          \
    (REDACursor_startSafe(*(cursorPtr), failReasonPtr,                 \
                          cursorStack, cursorStackIndexPtr) != NULL) : \
    RTI_FALSE                                                          \
  )

  #define REDACursorPerWorker_assertAndStartCursorSafeFnc( \
      cursorPerWorker, cursorPtr, failReasonPtr,        \
      cursorStack, cursorStackIndexPtr, worker)         \
  (                                                     \
    (REDACursorPerWorker_assertCursorMacro(cursorPerWorker, cursorPtr, \
                                           worker) != NULL) ?          \
    (REDACursor_startSafeFnc(*(cursorPtr), failReasonPtr,              \
                             cursorStack, cursorStackIndexPtr) != NULL) : \
    RTI_FALSE                                                          \
  )
#ifdef RTI_PRECONDITION_TEST
  #define REDACursorPerWorker_assertAndStartCursorSafe \
    REDACursorPerWorker_assertAndStartCursorSafeFnc
#else
  #define REDACursorPerWorker_assertAndStartCursorSafe \
    REDACursorPerWorker_assertAndStartCursorSafeMacro
#endif



#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* reda_database_impl_h */
