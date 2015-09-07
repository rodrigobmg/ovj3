/*
 * @(#)pres_common_impl.h    generated by: makeheader    Mon Dec  3 23:08:14 2007
 *
 *		built from:	common_impl.ifc
 */

#ifndef pres_common_impl_h
#define pres_common_impl_h


#ifdef __cplusplus
    extern "C" {
#endif



#define PRESInstanceHandle_compare(handle1, handle2)                         \
 (((handle1)->isValid - (handle2)->isValid)                                    \
  ? ((handle1)->isValid - (handle2)->isValid)                                  \
  : (((handle1)->guid.prefix.hostId > (handle2)->guid.prefix.hostId) ? 1 :                   \
     (((handle1)->guid.prefix.hostId < (handle2)->guid.prefix.hostId) ? -1 :                 \
      (((handle1)->guid.prefix.appId > (handle2)->guid.prefix.appId) ? 1 :                   \
       (((handle1)->guid.prefix.appId < (handle2)->guid.prefix.appId) ? -1 :                 \
        (((handle1)->guid.prefix.instanceId > (handle2)->guid.prefix.instanceId) ? 1 :      \
         (((handle1)->guid.prefix.instanceId < (handle2)->guid.prefix.instanceId) ? -1 :                 \
	  (((handle1)->guid.objectId > (handle2)->guid.objectId) ? 1 :           \
	   (((handle1)->guid.objectId < (handle2)->guid.objectId) ? -1 : 0)))))))))

/* TODO: this should be enough as PRES_INSTANCE_HANDLE_NIL should be used
    everywhere and it sets the boolean to false */
  #define PRESInstanceHandle_isNil(__me)                         \
    (!(__me)->isValid)

/* --------------------------------------------------------- */
  #define PRESGroupSuffix_getRWType(osx) \
    (((osx) & 0x0F) == 0x08 ? MIG_RTPS_RW_TYPE_WRITER :  \
    (((osx) & 0x0F) == 0x09 ? MIG_RTPS_RW_TYPE_READER :  \
    (((osx) == PRES_GROUP_SUFFIX_NORMAL_USER_VIRTUAL_READER_GROUP) ? \
      MIG_RTPS_RW_TYPE_READER : MIG_RTPS_RW_TYPE_UNKNOWN)))

/* --------------------------------------------------------- */

  #define PRESTopicSuffix_isTopic(osx) \
    (((osx) == PRES_TOPIC_SUFFIX_NORMAL_USER_TOPIC   || \
        (osx) == PRES_TOPIC_SUFFIX_RESERVED_USER_TOPIC || \
        (osx) == PRES_TOPIC_SUFFIX_NORMAL_META_TOPIC   || \
        (osx) == PRES_TOPIC_SUFFIX_RESERVED_META_TOPIC || \
        (osx) == PRES_TOPIC_SUFFIX_NORMAL_USER_VIRTUAL_TOPIC) ? \
        RTI_TRUE : RTI_FALSE)
/* --------------------------------------------------------- */
  #define PRESIeeeTime_compare(time1, time2) \
    ((((time1).sec) > ((time2).sec)) ? 1 : \
     ((((time1).sec) < ((time2).sec)) ? -1 : \
      ((((time1).nanosec) > ((time2).nanosec)) ? 1 : \
       ((((time1).nanosec) < ((time2).nanosec)) ? -1 : 0))))

/* --------------------------------------------------------- */
  #define PRESEntity_isEnabled(entity) \
    ((entity).state == PRES_ENTITY_STATE_ENABLED)

/* --------------------------------------------------------- */
  #define PRESEntity_isDestroyed(entity) \
    ((entity).state == PRES_ENTITY_STATE_DESTROYED)

/* --------------------------------------------------------- */
  #define PRESResourceLimitQos_limitExceeded(maximal, x) \
    (((maximal) >= 0) && (((x) < 0) || ((x) > (maximal))))

/* --------------------------------------------------------- */
  #define PRESResourceLimitQos_limitReached(maximal, x) \
    (((maximal) >= 0) && (((x) < 0) || ((x) >= (maximal))))



#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* pres_common_impl_h */
