/*
 * @(#)pres_writerStatistics.h    generated by: makeheader    Mon Dec  3 23:08:15 2007
 *
 *		built from:	writerStatistics.ifc
 */

#ifndef pres_writerStatistics_h
#define pres_writerStatistics_h


#include "osapi/osapi_type.h"
#include "commend/commend_writerStatistics.h"

#ifdef __cplusplus
    extern "C" {
#endif

struct PRESPsWriterStatistics {
    RTI_UINT32 entryCountPeak;
};


#define PRES_PS_WRITER_STATISTICS_INITIALIZER { \
    0 /* entryCountPeak */ \
}

struct PRESPsWriterLocalWriterStatistics {
    struct PRESPsWriterStatistics presStats;
    struct COMMENDWriterServiceLocalWriterStatistics commendStats;
};


#define PRES_PS_WRITER_LOCAL_WRITER_STATISTICS_INITIALIZER { \
PRES_PS_WRITER_STATISTICS_INITIALIZER, \
COMMEND_WRITER_SERVICE_LOCAL_WRITER_STATISTICS_INITIALIZER \
}

struct PRESPsWriterMatchedReaderStatistics {
    struct COMMENDWriterServiceMatchedReaderStatistics commendStats;
};

struct PRESPsWriterMatchedDestinationStatistics {
    struct COMMENDWriterServiceMatchedDestinationStatistics commendStats;
};


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* pres_writerStatistics_h */
