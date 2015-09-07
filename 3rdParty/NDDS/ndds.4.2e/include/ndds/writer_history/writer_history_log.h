/*
 * @(#)writer_history_log.h    generated by: makeheader    Mon Dec  3 23:08:12 2007
 *
 *		built from:	log.ifc
 */

#ifndef writer_history_log_h
#define writer_history_log_h



#ifndef log_common_h
  #include "log/log_common.h"
#endif
#ifndef transport_dll_h
  #include "writer_history/writer_history_dll.h"
#endif

#ifdef __cplusplus
    extern "C" {
#endif



  /*e \ingroup WriterHistoryLogModule
      \brief writer history plugin submodule identifier. For use in log 
      message numbers.
  */
  /* this is not a real submodule; just a way to get a unique number */
  #define SUBMODULE_NDDS_WRITERHISTORY  (0x1000)

  /*e \ingroup WriterHistoryLogModule
      \brief Common submodule identifier. For use in log message numbers.
  */
  #define SUBMODULE_NDDS_WRITERHISTORY_COMMON  (0x2000)

  /*e \ingroup WriterHistoryLogModule
      \brief Memory writer history plugin submodule identifier. For use in log 
      message numbers.
  */
  #define SUBMODULE_NDDS_WRITERHISTORY_MEMORY (0x4000)

  /*e \ingroup WriterHistoryLogModule
      \brief ODBC writer history plugin submodule identifier. For use in log 
      message numbers.
  */
  #define SUBMODULE_NDDS_WRITERHISTORY_ODBC (0x8000)

  /*e \ingroup WriterHistoryLogModule
    \brief Identfier used for enabling log messages in the common submodule.    
  */
  #define NDDS_WRITERHISTORY_SUBMODULE_MASK_COMMON  (0x0001)

  /*e \ingroup WriterHistoryLogModule
    \brief Memory writer history plugin identifier. Used for enabling log 
    messages in the memory writer history plugin.    
  */
  #define NDDS_WRITERHISTORY_SUBMODULE_MASK_MEMORY  (0x0002)

  /*e \ingroup WriterHistoryLogModule
    \brief ODBC writer history plugin identifier. Used for enabling log 
    messages in the ODBC writer history plugin.    
  */
  #define NDDS_WRITERHISTORY_SUBMODULE_MASK_ODBC  (0x0004)

  /*e \ingroup WriterHistoryLogModule
    \brief Convenient way to say "enable logging for all writer history 
    submodules".
  */
  #define NDDS_WRITERHISTORY_SUBMODULE_MASK_ALL (0xffff)

extern WRITERHISTORYDllExport void NDDS_WriterHistory_Log_set_verbosity(
    RTILogBitmap submodule_mask, int verbosity);

extern WRITERHISTORYDllExport void NDDS_WriterHistory_Log_set_bitmaps(
    RTILogBitmap submodule_mask, RTILogBitmap instrumentation_mask);

extern WRITERHISTORYDllExport void NDDS_WriterHistory_Log_get_bitmaps(
    RTILogBitmap *submodule_mask, RTILogBitmap * instrumentation_mask);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* writer_history_log_h */
