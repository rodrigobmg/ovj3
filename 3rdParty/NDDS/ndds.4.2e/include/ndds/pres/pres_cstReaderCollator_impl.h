/*
 * @(#)pres_cstReaderCollator_impl.h    generated by: makeheader    Mon Dec  3 23:08:14 2007
 *
 *		built from:	cstReaderCollator_impl.ifc
 */

#ifndef pres_cstReaderCollator_impl_h
#define pres_cstReaderCollator_impl_h


#ifdef __cplusplus
    extern "C" {
#endif



#define PRESCstReaderCollator_pruneLifespanExpiredEntries(me, now,      \
        requiredEntryCount, alwaysCalculateState, readConditionState)   \
    (PRESCstReaderCollator_pruneAndUpdate(me, now, requiredEntryCount,  \
        RTI_FALSE, NULL, PRES_INSTANCE_STATE_INVALID, NULL,             \
        alwaysCalculateState, readConditionState))



#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* pres_cstReaderCollator_impl_h */
