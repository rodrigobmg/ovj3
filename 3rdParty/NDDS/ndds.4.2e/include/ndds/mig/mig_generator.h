/*
 * @(#)mig_generator.h    generated by: makeheader    Mon Dec  3 23:08:07 2007
 *
 *		built from:	generator.ifc
 */

#ifndef mig_generator_h
#define mig_generator_h


  #ifndef osapi_ntptime_h
    #include "osapi/osapi_ntptime.h"
  #endif
  #ifndef reda_buffer_h
    #include "reda/reda_buffer.h"
  #endif
  #ifndef netio_common_h
    #include "netio/netio_common.h"
  #endif
  #ifndef mig_dll_h
    #include "mig/mig_dll.h"
  #endif
  #ifndef mig_rtps_h
    #include "mig/mig_rtps.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif

struct RTIClock;

struct REDAWorker;

struct REDAWeakReference;

struct RTINetioSender;

struct REDAWorkerFactory;

struct RTINetioSenderDestinationGroup;

struct MIGGenerator;

struct MIGGeneratorSampleInlineParams {
    struct REDABuffer params;

    struct REDAFastBufferPool *paramsPool;

    struct RTICdrStream *paramsStream;

    RTI_INT32 signatureOffset;

    /*i Used for timestamp only */
    RTI_UINT32 _bitmap;
};

struct MIGGeneratorSample {
    /*e \brief Sequence number assigned to the sample; this will be the "key" */
    struct REDASequenceNumber sn;
    /*e \brief Sequence number of first sample in set to which this sample
      belongs; will be UNKNOWN if this sample does not belong to a set */
    struct REDASequenceNumber setFirstSn;
    /*e \brief For CST use only */
    struct MIGRtpsGuid objectGuid;
    /*e \brief time when sample created; optional */
    struct RTINtpTime timestamp;
    /*e \brief directed reader GUID; optional */
    struct MIGRtpsGuid readerGuid;
    /*e \brief sample deadline (time when sample created + writer latency budget); optional */
    struct RTINtpTime deadline;
    /*e \brief Issue/Var flags */
    char flags;
    /*e \brief Var status info */
    MIGRtpsStatusInfo statusInfo; /*RTPS.2.0*/
    /*e Raw user data (include user parameters as well),
      serialized and aligned STRONG reference.
    */
    struct REDABuffer userData;
    /*e \brief Raw protocol parameters,
      serialized and aligned STRONG reference. */

    struct REDABuffer protocolParameters;
    /*e \brief CDR Stream used to encode the
         protocol parameters. Passed from the highest
        layer that allocated the protocol buffer
     */
    struct RTICdrStream *protocolStream;
    /*e \brief Fastbuffer pool used to allocate
        and free buffers to store protocol parameters
        from. Passed from the layer the allcated the
        protocol buffer
     */
    struct REDAFastBufferPool *protocolPool;

    /*e \brief mutable inline qos. 
    */
    struct REDABuffer *mutableParameters;
    /*e \brief immutable inline qos. 
    requested by stateless readers 
    that expect all inline qos. */
    struct REDABuffer *expectedParameters;
    /*e \brief flag indicating whether reader 
    expects all inline qos. 
    */
    RTIBool useExpectedInlineQos;
    /*e \brief location of the first signature in the
     * inline parameter. This is used to
     * rewrite the signature in case an issue needs
     * to be resent. The reaosn for adding this variable
     * is to speed up the rewrite. The alternative is
     * to not rewrite (not very useful) and to search
     * for it (more overhead).
     */
    RTI_INT32 signatureOffset;

    /*i Used for timestamp only */
    RTI_UINT32 _bitmap;

    /*e \brief extra flags of data submessage 
    */
    MIGRtpsDataFlags extraFlags;

    /*e \brief location where all COMMEND inline-params 
        are serialized after.  Corresponds to length
        of PRES inline-params. 
    */
    RTI_INT32 inlineQosOffset;
};


  #define MIG_GENERATOR_SAMPLE_DEFAULT { \
     REDA_SEQUENCE_NUMBER_UNKNOWN, /* sn */ \
     REDA_SEQUENCE_NUMBER_UNKNOWN, /* setFirstSn */ \
     MIG_RTPS_GUID_UNKNOWN, /* object */ \
     RTI_NTP_TIME_ZERO, /* timestamp */ \
     MIG_RTPS_GUID_UNKNOWN, /* readerGuid */ \
     RTI_NTP_TIME_ZERO, /* deadline */ \
     MIG_RTPS_NO_FLAG, /* flags */ \
     MIG_RTPS_NO_STATUS_INFO, /* statusInfo */ \
     {0, NULL}, /* userData */ \
     {0, NULL}, /* protocolParameters */ \
     NULL, /* protocolStream */ \
     NULL, /* protocolPool */ \
     NULL, /*mutableParameters*/ \
     NULL, /*expectedParameters*/ \
     RTI_FALSE, /*useExpectedInlineQos*/ \
     0, /* signatureOffset */ \
     0, /* bitmap */ \
     MIG_RTPS_DATA_FLAGS_NONE, /* extraFlags */ \
     0 /* inlineQosOffset */ }

extern MIGDllExport RTIBool
MIGGeneratorSample_set(struct MIGGeneratorSample *me,
		       const struct REDASequenceNumber *sn,
		       const struct REDASequenceNumber *setFirstSn,
                       const struct MIGRtpsGuid *srcGuid,
                       const struct RTINtpTime *timestamp,
                       const struct MIGRtpsGuid *readerGuid,
		       char flags, 
                       MIGRtpsDataFlags extraFlags,
                       MIGRtpsStatusInfo statusInfo, 
		       const struct REDABuffer *userData,
		       const struct REDABuffer *parameter,
                       const struct REDABuffer *mutableParameter,
                       const struct REDABuffer *expectedParameter);


#define  MIGGeneratorSample_setParameterLength(__sampleParams,__length) \
(__sampleParams)->length = (__length)


#define  MIGGeneratorSample_getParameterLength(__sample) \
(__sample)->protocolParameters.length


#define  MIGGeneratorSample_getExpectedParameterLength(__sample) \
(__sample)->expectedParameters->length


#define  MIGGeneratorSample_setExpectedParameterLength(__sample,__length) \
(__sample)->expectedParameters->length = (__length)


#define  MIGGeneratorSample_adjustParameterLength(__sampleParam,__delta) \
(__sampleParam)->length += (__delta)


#define  MIGGeneratorSample_adjustExpectedParameterLength(__sample,__delta) \
(__sample)->expectedParameters->length += (__delta)


#define  MIGGeneratorSample_initializeInlineParameter(__sample,__pool,__stream) \
(__sample)->protocolPool = (__pool); \
(__sample)->protocolStream = (__stream);


#define  MIGGeneratorSample_setParameterStream(__sample,__stream) \
(__sample)->protocolStream = (__stream)


#define  MIGGeneratorSample_getParameterStream(__sample) \
(__sample)->protocolStream

extern MIGDllExport RTIBool
MIGGeneratorSample_isValid(const struct MIGGeneratorSample *me);

extern MIGDllExport RTIBool
MIGGeneratorSample_isTimestamped(const struct MIGGeneratorSample *me);

extern MIGDllExport int MIGGeneratorSample_compare(const void *l,
						   const void *r);

extern MIGDllExport void
MIGGeneratorSample_copy(struct MIGGeneratorSample *me,
			const struct MIGGeneratorSample *src);

struct MIGGeneratorProperty {
    /*e \brief Total gather buffer count to use to form the message.

      The generator needs
      the maximum iovec count supported across the transports.  Must be
      greater than or equal to
       NDDS_Transport_Property_t#gatherSendBuffercountMax for all
      transport to be used.
    */
    int gatherSendBufferCountMax;
};


  #define MIG_GENERATOR_GATHER_SEND_BUFFER_COUNT_MAX_DEFAULT (128)


  #define MIG_GENERATOR_PROPERTY_DEFAULT { \
    MIG_GENERATOR_GATHER_SEND_BUFFER_COUNT_MAX_DEFAULT}

extern MIGDllExport struct MIGGenerator *
MIGGenerator_new(MIGRtpsHostId hostId, MIGRtpsAppId appId, 
                 MIGRtpsInstanceId instanceId, /*RTPS.2.0*/
		 struct RTINetioSender *sender,
		 const struct MIGGeneratorProperty *property,
		 struct RTIClock *clock,
		 struct REDAWorkerFactory *workerFactory);

extern MIGDllExport void MIGGenerator_delete(struct MIGGenerator *me);

struct MIGGeneratorWorkerStat {
    /* begin message generation. */
    struct RTINtpTime timeBegun;
    /* generator handed over the formed message to  RTINetioSender. */
    struct RTINtpTime timeFinished;
};

extern MIGDllExport RTIBool
MIGGeneratorWorkerStat_init(struct REDAWorkerFactory *workerFactory);

extern MIGDllExport void
MIGGeneratorWorkerStat_finalize(struct REDAWorkerFactory *workerFactory);


  #define MIG_GENERATOR_STAT_STRING_LENGTH (46)

extern MIGDllExport char *
MIGGeneratorWorkerStat_toString(const void *me, struct REDABuffer *buffer);

typedef enum {
    /*e use this machine's own endianness, as defined by RTI_ENDIAN_LITTLE
      define during compile time. */
    MIG_GENERATOR_ENDIAN_UNKNOWN = -1,
    /*e Use big endian, regardless of the machine's true endianness */
    MIG_GENERATOR_ENDIAN_BIG     =  0,
    /*e Use little endian, regardless of the machine's true endianness */
    MIG_GENERATOR_ENDIAN_LITTLE  =  1
} MIGGeneratorEndian;

extern MIGDllExport RTIBool MIGGenerator_beginMessage(
    struct MIGGenerator *me, MIGGeneratorEndian endian,
    const struct RTINetioSenderDestinationGroup *destinationGroup,
    const struct REDAWeakReference *destinationArray, int destinationCount,
    int transportPriority, struct REDAWorker *worker);

extern MIGDllExport RTIBool
MIGGenerator_finishMessage(struct MIGGenerator *me, struct REDAWorker *worker);

extern MIGDllExport RTIBool
MIGGenerator_setEndian(struct MIGGenerator *me,
		       MIGGeneratorEndian endian, struct REDAWorker *worker);

extern MIGDllExport RTIBool
MIGGenerator_addAck(struct MIGGenerator *me, int *size, char flags,
		    MIGRtpsObjectId readerObjectId,
		    const struct MIGRtpsGuid *writerGuidIn,
		    const struct MIGRtpsBitmap *bitmap,
                    REDAEpoch epoch,
		    struct REDAWorker *worker);

extern MIGDllExport RTIBool
MIGGenerator_addNackFrag(struct MIGGenerator *me, char flags,
                     MIGRtpsObjectId readerObjectId,
                     const struct MIGRtpsGuid *writerGuidIn,
                     const struct REDASequenceNumber *sequenceNumber,
                     const struct MIGRtpsBitmap *bitmap,
                     REDAEpoch epoch,
                     struct REDAWorker *worker);

extern MIGDllExport RTIBool
MIGGenerator_addGap(struct MIGGenerator *me, 
                    int *size, char flags,
		    const struct MIGRtpsGuid *readerGuidIn,
		    MIGRtpsObjectId writerObjectId,
		    const struct REDASequenceNumber *sequenceNumber,
		    const struct MIGRtpsBitmap *bitmap,
		    struct REDAWorker *worker);

extern MIGDllExport RTIBool
MIGGenerator_addHeartbeat(struct MIGGenerator *me, char flags,
			  const struct MIGRtpsGuid *readerGuidIn,
			  MIGRtpsObjectId writerObjectId,
			  const struct REDASequenceNumber *firstSequenceNumber,
			  const struct REDASequenceNumber *lastSequenceNumber,
                          REDAEpoch epoch, 
			  struct REDAWorker *worker);

extern MIGDllExport RTIBool
MIGGenerator_addHeartbeatFrag(struct MIGGenerator *me, char flags,
                          const struct MIGRtpsGuid *readerGuidIn,
                          MIGRtpsObjectId writerObjectId,
                          const struct REDASequenceNumber *sequenceNumber,
                          RTI_UINT32 lastFragmentNum,
                          REDAEpoch epoch,
                          struct REDAWorker *worker);

extern MIGDllExport RTIBool
MIGGenerator_addInfoDestination(struct MIGGenerator *me,
                                char flags,
                                const struct MIGRtpsGuidPrefix *destGuidPrefix, /*RTPS.2.0*/
                                struct REDAWorker *worker);

extern MIGDllExport RTIBool
MIGGenerator_addData(struct MIGGenerator *me,
                     int *size,
                     const struct MIGRtpsGuid *readerGuidIn,
                     MIGRtpsObjectId writerObjectId,
                     const struct MIGGeneratorSample *sample,
                     struct REDAWorker *worker);

extern MIGDllExport RTIBool MIGGenerator_addDataFrag(
             struct MIGGenerator *me,
             int *size,
	     const struct MIGRtpsGuid *readerGuidIn,
	     MIGRtpsObjectId writerObjectId,
	     const struct MIGGeneratorSample *sample,
	     int numFragsToAdd,
	     int firstFragNumber,
	     int fragSize,
	     int *numFragsAdded,
	     struct REDAWorker *worker);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

  #include "mig/mig_generator_impl.h"

#endif /* mig_generator_h */
