/*
 * @(#)cdr_stream.h    generated by: makeheader    Mon Dec  3 23:08:01 2007
 *
 *		built from:	stream.ifc
 */

#ifndef cdr_stream_h
#define cdr_stream_h


 #ifndef cdr_dll_h
    #include "cdr/cdr_dll.h"
 #endif
 #ifndef osapi_type_h
    #include "osapi/osapi_type.h"
 #endif
 #ifndef osapi_type_h
    #include "osapi/osapi_type.h"
 #endif
 #ifndef cdr_type_h
    #include "cdr/cdr_type.h"
 #endif 
 #ifndef cdr_encapsulation_h
    #include "cdr/cdr_encapsulation.h"
 #endif

/* For VxWorks defines */
#ifdef RTI_VXWORKS
	#include <vxWorks.h>
#endif

#ifdef __cplusplus
    extern "C" {
#endif

struct REDABuffer;

struct RTICdrStream; /* forward declare to appease the compiler */



/*e \ingroup RTICdrStreamModule
  Endian.
*/
typedef RTI_UINT8 RTICdrEndian;

/*e \ingroup RTICdrStreamModule
  Big endian in CDR.
*/
#define RTI_CDR_ENDIAN_BIG (0)

/*e \ingroup RTICdrStreamModule
  Little endian in CDR
*/
#define RTI_CDR_ENDIAN_LITTLE (1)

/*e \ingroup RTICdrStreamModule
  Default endian in CDR
*/
#ifdef RTI_ENDIAN_LITTLE
  #define RTI_CDR_ENDIAN_DEFAULT RTI_CDR_ENDIAN_LITTLE
#else
  #define RTI_CDR_ENDIAN_DEFAULT RTI_CDR_ENDIAN_BIG
#endif

/*e \ingroup RTICdrStreamModule
  Used with RTICdrStream_set()
*/
#define RTI_CDR_STREAM_ALIGNMENT (8)


extern RTICdrDllExport
struct RTICdrStream * RTICdrStream_new();

extern RTICdrDllExport
void RTICdrStream_delete(struct RTICdrStream *me);

extern RTICdrDllExport
void RTICdrStream_set(struct RTICdrStream *me, char *buffer,
		      unsigned int bufferLength);

extern RTICdrDllExport
void RTICdrStream_setEndian(struct RTICdrStream *me, RTICdrEndian endian);

extern RTICdrDllExport
RTICdrEndian RTICdrStream_getEndian(struct RTICdrStream *me);

extern RTICdrDllExport
void RTICdrStream_resetPosition(struct RTICdrStream *me);

extern RTICdrDllExport
void RTICdrStream_clearAndReset(struct RTICdrStream *me);

extern RTICdrDllExport
void RTICdrStream_print(const struct RTICdrStream *me);

extern RTICdrDllExport
RTIBool RTICdrStream_setCurrentPositionOffset(struct RTICdrStream *me,
					      int offset);

extern RTICdrDllExport
RTIBool RTICdrStream_incrementCurrentPosition(struct RTICdrStream *me,
					      int amount);

extern RTICdrDllExport
int RTICdrStream_getRemainder(const struct RTICdrStream *me);

extern RTICdrDllExport
int RTICdrStream_getCurrentPositionOffset(const struct RTICdrStream *me);

extern RTICdrDllExport
RTIBool RTICdrStream_append(struct RTICdrStream *me,
			    const struct RTICdrStream *copyFrom,
			    int bytesToCopy);

extern RTICdrDllExport
RTIBool RTICdrStream_appendFull(struct RTICdrStream *me,
				const struct RTICdrStream *copy);

extern RTICdrDllExport
RTIBool RTICdrStream_checkSize(const struct RTICdrStream *me,
			       unsigned int size);

extern RTICdrDllExport
void RTICdrStream_popState(struct RTICdrStream *me,
			   struct REDABuffer *state);

extern RTICdrDllExport
void RTICdrStream_pushState(struct RTICdrStream *me,
			    struct REDABuffer *state);

extern RTICdrDllExport
char* RTICdrStream_getCurrentPosition(const struct RTICdrStream *me);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeChar(struct RTICdrStream *me,
				   const RTICdrChar *in);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeChar(struct RTICdrStream *me, 
                                     RTICdrChar *out);

extern RTICdrDllExport
RTIBool RTICdrStream_skipChar(struct RTICdrStream *me);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeWchar(struct RTICdrStream *me, 
				    const RTICdrWchar *in);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeWchar(struct RTICdrStream *me,
				      RTICdrWchar *out);

extern RTICdrDllExport
RTIBool RTICdrStream_skipWchar(struct RTICdrStream *me);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeCORBAWChar(struct RTICdrStream *me,
                                         const void *in,
					 RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeCORBAWChar(struct RTICdrStream *me,
				           void *out,
					   RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_skipCORBAWChar(struct RTICdrStream *me,
					   RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeOctet(struct RTICdrStream *me,
				    const RTICdrOctet *in);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeOctet(struct RTICdrStream *me,
				      RTICdrOctet *out);

extern RTICdrDllExport
RTIBool RTICdrStream_skipOctet(struct RTICdrStream *me);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeShort(struct RTICdrStream *me,
				    const RTICdrShort *in );

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeShort(struct RTICdrStream *me,
				      RTICdrShort *out);

extern RTICdrDllExport
RTIBool RTICdrStream_skipShort(struct RTICdrStream *me);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeUnsignedShort(struct RTICdrStream *me,
					    const RTICdrUnsignedShort *in );

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeUnsignedShort(struct RTICdrStream *me,
					      RTICdrUnsignedShort *out);

extern RTICdrDllExport
RTIBool RTICdrStream_skipUnsignedShort(struct RTICdrStream *me);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeLong(struct RTICdrStream *me,
				   const RTICdrLong *in);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeLong(struct RTICdrStream *me, 
                                     RTICdrLong *out);

extern RTICdrDllExport
RTIBool RTICdrStream_skipLong(struct RTICdrStream *me);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeUnsignedLong(struct RTICdrStream *me,
					   const RTICdrUnsignedLong *in );

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeUnsignedLong(struct RTICdrStream *me,
					     RTICdrUnsignedLong *out);

extern RTICdrDllExport
RTIBool RTICdrStream_skipUnsignedLong(struct RTICdrStream *me);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeLongLong(struct RTICdrStream *me,
				       const RTICdrLongLong *in );

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeLongLong(struct RTICdrStream *me,
					 RTICdrLongLong *out);

extern RTICdrDllExport
RTIBool RTICdrStream_skipLongLong(struct RTICdrStream *me);

extern RTICdrDllExport RTIBool
RTICdrStream_serializeUnsignedLongLong(struct RTICdrStream *me,
				       const RTICdrUnsignedLongLong *in );

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeUnsignedLongLong(struct RTICdrStream *me,
						 RTICdrUnsignedLongLong *out);

extern RTICdrDllExport
RTIBool RTICdrStream_skipUnsignedLongLong(struct RTICdrStream *me);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeFloat(struct RTICdrStream *me,
				    const RTICdrFloat *in);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeFloat(struct RTICdrStream *me,
				      RTICdrFloat *out);

extern RTICdrDllExport
RTIBool RTICdrStream_skipFloat(struct RTICdrStream *me);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeDouble(struct RTICdrStream *me,
				     const RTICdrDouble *in);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeDouble(struct RTICdrStream *me,
				       RTICdrDouble *out);

extern RTICdrDllExport
RTIBool RTICdrStream_skipDouble(struct RTICdrStream *me);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeLongDouble(struct RTICdrStream *me,
					 const RTICdrLongDouble *in);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeLongDouble(struct RTICdrStream *me,
					   RTICdrLongDouble *out);

extern RTICdrDllExport
RTIBool RTICdrStream_skipLongDouble(struct RTICdrStream *me);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeBoolean(struct RTICdrStream *me, 
				      const RTICdrBoolean *in);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeBoolean(struct RTICdrStream *me, 
					RTICdrBoolean *out);

extern RTICdrDllExport
RTIBool RTICdrStream_skipBoolean(struct RTICdrStream *me);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeEnum(struct RTICdrStream *me,
				   const RTICdrEnum *in);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeEnum(struct RTICdrStream *me,
				     RTICdrEnum *out);

extern RTICdrDllExport
RTIBool RTICdrStream_skipEnum(struct RTICdrStream *me);

extern RTICdrDllExport
RTIBool RTICdrStream_serializePrimitiveArray(
    struct RTICdrStream *me,
    const void *in, RTICdrUnsignedLong length,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializePrimitiveArray(
    struct RTICdrStream *me,
    void *out, RTICdrUnsignedLong length,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_skipPrimitiveArray(
    struct RTICdrStream *me,
    RTICdrUnsignedLong length,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_serializePrimitivePointerArray(
    struct RTICdrStream *me,
    const void **in,
    RTICdrUnsignedLong length,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializePrimitivePointerArray(
    struct RTICdrStream *me,
    void ** out, RTICdrUnsignedLong length,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_skipPrimitivePointerArray(
    struct RTICdrStream *me,
    RTICdrUnsignedLong length,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeCORBAWCharArray(
    struct RTICdrStream *me,
    const void *in, RTICdrUnsignedLong length,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeCORBAWCharArray(
    struct RTICdrStream *me,
    void *out, RTICdrUnsignedLong length,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_skipCORBAWCharArray(
    struct RTICdrStream *me,
    RTICdrUnsignedLong length,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_serializePrimitiveSequence(
    struct RTICdrStream *me,
    const void *in,
    RTICdrUnsignedLong numberOfElements,
    RTICdrUnsignedLong maximumLength,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializePrimitiveSequence(
    struct RTICdrStream *me,
    void *out,
    RTICdrUnsignedLong *numberOfElements,
    RTICdrUnsignedLong maximumLength,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_skipPrimitiveSequence(
    struct RTICdrStream *me,
    RTICdrUnsignedLong *numberOfElements,
    RTICdrUnsignedLong maximumLength,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeCORBAWCharSequence(
    struct RTICdrStream *me,
    const void *in,
    RTICdrUnsignedLong numberOfElements,
    RTICdrUnsignedLong maximumLength,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeCORBAWCharSequence(
    struct RTICdrStream *me,
    void *out,
    RTICdrUnsignedLong *numberOfElements,
    RTICdrUnsignedLong maximumLength,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_skipCORBAWCharSequence(
    struct RTICdrStream *me,
    RTICdrUnsignedLong *numberOfElements,
    RTICdrUnsignedLong maximumLength,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_serializePrimitivePointerSequence(
    struct RTICdrStream *me,
    const void **in,
    RTICdrUnsignedLong numberOfElements,
    RTICdrUnsignedLong maximumLength,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializePrimitivePointerSequence(
    struct RTICdrStream *me,
    void **out,
    RTICdrUnsignedLong *numberOfElements,
    RTICdrUnsignedLong maximumLength,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_skipPrimitivePointerSequence(
    struct RTICdrStream *me,
    RTICdrUnsignedLong *numberOfElements,
    RTICdrUnsignedLong maximumLength,
    RTICdrPrimitiveType type);


typedef RTIBool (*RTICdrStreamSerializeFunction)(struct RTICdrStream *me,
						 const void *in,
						 void *serializeParameter);


typedef RTIBool (*RTICdrStreamSerializeEncapsulationFunction)(struct RTICdrStream *me,
                                                              void *serializeParameter);


typedef RTIBool (*RTICdrStreamDeserializeFunction)(struct RTICdrStream *me,
						   void *out,
						   void *deserializeParameter);


typedef RTIBool (*RTICdrStreamDeserializeEncapsulationFunction)(struct RTICdrStream *me,
                                                                void *deserializeParameter);


typedef RTIBool (*RTICdrStreamSkipFunction)(struct RTICdrStream *me,
                                            void *skipParameter);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeNonPrimitiveArray(
    struct RTICdrStream *me, const void *in, RTICdrUnsignedLong length,
    unsigned int elementSize, RTICdrStreamSerializeFunction serializeFunction,
    void *serializeparameter);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeNonPrimitiveArray(
    struct RTICdrStream *me, void *out, RTICdrUnsignedLong length,
    unsigned int elementSize,
    RTICdrStreamDeserializeFunction deserializeFunction,
    void *deserializeParameter);

extern RTICdrDllExport
RTIBool RTICdrStream_skipNonPrimitiveArray(
    struct RTICdrStream *me, RTICdrUnsignedLong length,
    unsigned int elementSize,
    RTICdrStreamSkipFunction skipFunction,
    void *skipParameter);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeNonPrimitivePointerArray(
    struct RTICdrStream *me, const void ** in, RTICdrUnsignedLong length,
    unsigned int elementSize, RTICdrStreamSerializeFunction serializeFunction,
    void *serializeparameter);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeNonPrimitivePointerArray(
    struct RTICdrStream *me, void **out, RTICdrUnsignedLong length,
    unsigned int elementSize,
    RTICdrStreamDeserializeFunction deserializeFunction,
    void *deserializeParameter);

extern RTICdrDllExport
RTIBool RTICdrStream_skipNonPrimitivePointerArray(
    struct RTICdrStream *me, 
    RTICdrUnsignedLong length,
    unsigned int elementSize,
    RTICdrStreamSkipFunction skipFunction,
    void *skipParameter);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeNonPrimitiveSequence(
    struct RTICdrStream *me, const void *in,
    RTICdrUnsignedLong numberOfElements, RTICdrUnsignedLong maximumLength,
    unsigned int elementSize,
    RTICdrStreamSerializeFunction serializeFunction,
    void *serializeParameter);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeNonPrimitiveSequence(
    struct RTICdrStream *me, void *out, RTICdrUnsignedLong *numberOfElements,
    RTICdrUnsignedLong maximumLength, unsigned int elementSize,
    RTICdrStreamDeserializeFunction deserializeFunction,
    void *deserializeParameter);

extern RTICdrDllExport
RTIBool RTICdrStream_skipNonPrimitiveSequence(
    struct RTICdrStream *me, 
    RTICdrUnsignedLong *numberOfElements,
    RTICdrUnsignedLong maximumLength, 
    unsigned int elementSize,
    RTICdrStreamSkipFunction skipFunction,
    void *skipParameter);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeNonPrimitivePointerSequence(
    struct RTICdrStream *me, const void **in,
    RTICdrUnsignedLong numberOfElements, RTICdrUnsignedLong maximumLength,
    RTICdrStreamSerializeFunction serializeFunction,
    void *serializeParameter);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeNonPrimitivePointerSequence(
    struct RTICdrStream *me, void **out, RTICdrUnsignedLong *numberOfElements,
    RTICdrUnsignedLong maximumLength,
    RTICdrStreamDeserializeFunction deserializeFunction,
    void *deserializeParameter);

extern RTICdrDllExport
RTIBool RTICdrStream_skipNonPrimitivePointerSequence(
    struct RTICdrStream *me, 
    RTICdrUnsignedLong *numberOfElements,
    RTICdrUnsignedLong maximumLength,
    RTICdrStreamSkipFunction skipFunction,
    void *skipParameter);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeString(struct RTICdrStream *me,
				     const RTICdrChar *in,
				     RTICdrUnsignedLong maximumLength);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeString(struct RTICdrStream *me,
				       RTICdrChar *out,
				       RTICdrUnsignedLong maximumLength);

extern RTICdrDllExport
RTIBool RTICdrStream_skipString(struct RTICdrStream *me,
                                       RTICdrUnsignedLong maximumLength);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeWstring(struct RTICdrStream *me,
				      const RTICdrWchar *in,
				      RTICdrUnsignedLong maximumLength);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeWstring(struct RTICdrStream *me,
					RTICdrWchar *out,
					RTICdrUnsignedLong maximumLength);

extern RTICdrDllExport
RTIBool RTICdrStream_skipWstring(struct RTICdrStream *me,
                                 RTICdrUnsignedLong maximumLength);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeStringArray(struct RTICdrStream *me,
                                          const void* in, 
                                          RTICdrUnsignedLong length,
                                          RTICdrUnsignedLong maximumStringLength,
                                          RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeStringArray(struct RTICdrStream *me,
                                            void *out,
                                            RTICdrUnsignedLong length,
                                            RTICdrUnsignedLong maximumStringLength,
                                            RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_skipStringArray(struct RTICdrStream *me,
                                     RTICdrUnsignedLong length,
                                     RTICdrUnsignedLong maximumStringLength,
                                     RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeStringPointerArray(struct RTICdrStream *me,
                                                 const void** in, 
                                                 RTICdrUnsignedLong length,
                                                 RTICdrUnsignedLong maximumStringLength,
                                                 RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeStringPointerArray(struct RTICdrStream *me,
                                                   void **out,
                                                   RTICdrUnsignedLong length,
                                                   RTICdrUnsignedLong maximumStringLength,
                                                   RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_skipStringPointerArray(struct RTICdrStream *me,
                                            RTICdrUnsignedLong length,
                                            RTICdrUnsignedLong maximumStringLength,
                                            RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeStringSequence(
    struct RTICdrStream *me,
    const void *in,
    RTICdrUnsignedLong numberOfElements,
    RTICdrUnsignedLong maximumLength,
    RTICdrUnsignedLong maximumStringLength,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeStringSequence(
    struct RTICdrStream *me,
    void *out,
    RTICdrUnsignedLong *numberOfElements,
    RTICdrUnsignedLong maximumLength,
    RTICdrUnsignedLong maximumStringLength,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_skipStringSequence(
    struct RTICdrStream *me,
    RTICdrUnsignedLong *numberOfElements,
    RTICdrUnsignedLong maximumLength,
    RTICdrUnsignedLong maximumStringLength,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeStringPointerSequence(
    struct RTICdrStream *me,
    const void **in,
    RTICdrUnsignedLong numberOfElements,
    RTICdrUnsignedLong maximumLength,
    RTICdrUnsignedLong maximumStringLength,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeStringPointerSequence(
    struct RTICdrStream *me,
    void **out,
    RTICdrUnsignedLong *numberOfElements,
    RTICdrUnsignedLong maximumLength,
    RTICdrUnsignedLong maximumStringLength,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_skipStringPointerSequence(
    struct RTICdrStream *me,
    RTICdrUnsignedLong *numberOfElements,
    RTICdrUnsignedLong maximumLength,
    RTICdrUnsignedLong maximumStringLength,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrStream_serializeBits(struct RTICdrStream *me,
                                   const RTICdrUnsignedLong *val, 
                                   RTICdrLong bitSize);

extern RTICdrDllExport
RTIBool RTICdrStream_deserializeBits(struct RTICdrStream *me,
                                     RTICdrUnsignedLong *out, 
                                     RTICdrLong bitSize);

extern RTICdrDllExport
RTIBool RTICdrStream_skipBits(struct RTICdrStream *me,
                              RTICdrLong bitSize);

extern RTICdrDllExport
RTIBool RTICdrStream_flushBitsBuffer(struct RTICdrStream *me);

extern RTICdrDllExport
RTIBool RTICdrStream_resetBitsBuffer(struct RTICdrStream *me);

extern RTICdrDllExport
void RTICdrStream_serializeCharFast(struct RTICdrStream *me,
				    const RTICdrChar *in);

extern RTICdrDllExport
void RTICdrStream_deserializeCharFast(struct RTICdrStream *me, RTICdrChar *out);

extern RTICdrDllExport
void RTICdrStream_skipCharFast(struct RTICdrStream *me);

extern RTICdrDllExport
void RTICdrStream_serializeWcharFast(struct RTICdrStream *me,
				     const RTICdrWchar *in);

extern RTICdrDllExport
void RTICdrStream_deserializeWcharFast(struct RTICdrStream *me,
				       RTICdrWchar *out);

extern RTICdrDllExport
void RTICdrStream_skipWcharFast(struct RTICdrStream *me);

extern RTICdrDllExport
void RTICdrStream_serializeOctetFast(struct RTICdrStream *me,
				     const RTICdrOctet *in);

extern RTICdrDllExport
void RTICdrStream_deserializeOctetFast(struct RTICdrStream *me,
				       RTICdrOctet *out);

extern RTICdrDllExport
void RTICdrStream_skipOctetFast(struct RTICdrStream *me);

extern RTICdrDllExport
void RTICdrStream_serializeShortFast(struct RTICdrStream *me,
				     const RTICdrShort *in);

extern RTICdrDllExport
void RTICdrStream_deserializeShortFast(struct RTICdrStream *me,
				       RTICdrShort *out);

extern RTICdrDllExport
void RTICdrStream_skipShortFast(struct RTICdrStream *me);

extern RTICdrDllExport
void RTICdrStream_serializeUnsignedShortFast(struct RTICdrStream *me,
					     const RTICdrUnsignedShort *in);

extern RTICdrDllExport
void RTICdrStream_deserializeUnsignedShortFast(struct RTICdrStream *me,
					       RTICdrUnsignedShort *out);

extern RTICdrDllExport
void RTICdrStream_skipUnsignedShortFast(struct RTICdrStream *me);

extern RTICdrDllExport
void RTICdrStream_serializeLongFast(struct RTICdrStream *me,
				    const RTICdrLong *in);

extern RTICdrDllExport
void RTICdrStream_deserializeLongFast(struct RTICdrStream *me, 
                                      RTICdrLong *out);

extern RTICdrDllExport
void RTICdrStream_skipLongFast(struct RTICdrStream *me);

extern RTICdrDllExport
void RTICdrStream_serializeUnsignedLongFast(struct RTICdrStream *me,
					    const RTICdrUnsignedLong *in);

extern RTICdrDllExport
void RTICdrStream_deserializeUnsignedLongFast(struct RTICdrStream *me,
					      RTICdrUnsignedLong *out);

extern RTICdrDllExport
void RTICdrStream_skipUnsignedLongFast(struct RTICdrStream *me);

extern RTICdrDllExport
void RTICdrStream_serializeLongLongFast(struct RTICdrStream *me,
					const RTICdrLongLong *in);

extern RTICdrDllExport
void RTICdrStream_deserializeLongLongFast(struct RTICdrStream *me,
					  RTICdrLongLong *out);

extern RTICdrDllExport
void RTICdrStream_skipLongLongFast(struct RTICdrStream *me);

extern RTICdrDllExport
void RTICdrStream_serializeUnsignedLongLongFast(
    struct RTICdrStream *me, const RTICdrUnsignedLongLong *in);

extern RTICdrDllExport
void RTICdrStream_deserializeUnsignedLongLongFast(struct RTICdrStream *me,
						  RTICdrUnsignedLongLong *out);

extern RTICdrDllExport
void RTICdrStream_skipUnsignedLongLongFast(struct RTICdrStream *me);

extern RTICdrDllExport
void RTICdrStream_serializeFloatFast(struct RTICdrStream *me,
				     const RTICdrFloat *in);

extern RTICdrDllExport
void RTICdrStream_deserializeFloatFast(struct RTICdrStream *me,
				       RTICdrFloat *out);

extern RTICdrDllExport
void RTICdrStream_skipFloatFast(struct RTICdrStream *me);

extern RTICdrDllExport
void RTICdrStream_serializeDoubleFast(struct RTICdrStream *me,
				      const RTICdrDouble *in);

extern RTICdrDllExport
void RTICdrStream_deserializeDoubleFast(struct RTICdrStream *me,
					RTICdrDouble *out);

extern RTICdrDllExport
void RTICdrStream_skipDoubleFast(struct RTICdrStream *me);

extern RTICdrDllExport
void RTICdrStream_serializeLongDoubleFast(struct RTICdrStream *me,
					  const RTICdrLongDouble *in);

extern RTICdrDllExport
void RTICdrStream_deserializeLongDoubleFast(struct RTICdrStream *me,
					    RTICdrLongDouble *out);

extern RTICdrDllExport
void RTICdrStream_skipLongDoubleFast(struct RTICdrStream *me);

extern RTICdrDllExport
void RTICdrStream_serializeBooleanFast(struct RTICdrStream *me,
				       const RTICdrBoolean *in);

extern RTICdrDllExport
void RTICdrStream_deserializeBooleanFast(struct RTICdrStream *me,
					 RTICdrBoolean *out);

extern RTICdrDllExport
void RTICdrStream_skipBooleanFast(struct RTICdrStream *me);

extern RTICdrDllExport
void RTICdrStream_serializeEnumFast(struct RTICdrStream *me,
				    const RTICdrEnum *in);

extern RTICdrDllExport
void RTICdrStream_deserializeEnumFast(struct RTICdrStream *me,
				      RTICdrEnum *out);

extern RTICdrDllExport
void RTICdrStream_skipEnumFast(struct RTICdrStream *me);

extern RTICdrDllExport
RTIBool RTICdrStream_align(struct RTICdrStream *me, int alignment);

extern RTICdrDllExport
void RTICdrStream_alignFast(struct RTICdrStream *me, int alignment);

extern RTICdrDllExport
void RTICdrStream_serializeUnsignedShortToBigEndianFast(struct RTICdrStream *me, 
                                                        const RTICdrUnsignedShort *in);

extern RTICdrDllExport
void RTICdrStream_deserializeUnsignedShortFromBigEndianFast(struct RTICdrStream *me, 
                                                            RTICdrUnsignedShort *out);

extern RTICdrDllExport
void RTICdrStream_serializeUnsignedLongToBigEndianFast(struct RTICdrStream *me, 
                                                       const RTICdrUnsignedLong *in);

extern RTICdrDllExport
void RTICdrStream_deserializeUnsignedLongFromBigEndianFast(struct RTICdrStream *me, 
                                                           RTICdrUnsignedLong *out);

extern RTICdrDllExport
void RTICdrStream_serializeBigEndianToUnsignedLongFast(struct RTICdrStream *me, 
                                                       const RTICdrOctet *in);

extern RTICdrDllExport
void RTICdrStream_deserializeBigEndianFromUnsignedLongFast(struct RTICdrStream *me, 
                                                           RTICdrOctet *out);

extern RTICdrDllExport 
RTIBool RTICdrStream_serializeUnsignedShortToBigEndian(struct RTICdrStream *me, 
                                                       const RTICdrUnsignedShort *in);

extern RTICdrDllExport 
RTIBool RTICdrStream_deserializeUnsignedShortFromBigEndian(struct RTICdrStream *me, 
                                                           RTICdrUnsignedShort *out);

extern RTICdrDllExport 
RTIBool RTICdrStream_serializeUnsignedLongToBigEndian(struct RTICdrStream *me, 
                                                      const RTICdrUnsignedLong *in);

extern RTICdrDllExport 
RTIBool RTICdrStream_deserializeUnsignedLongFromBigEndian(struct RTICdrStream *me, 
                                                          RTICdrUnsignedLong *out);

extern RTICdrDllExport 
RTIBool RTICdrStream_setEndianFromEncapsulationDefault(
    struct RTICdrStream *me);

extern RTICdrDllExport 
RTIBool RTICdrStream_serializeCdrEncapsulationDefault(
    struct RTICdrStream *me);

extern RTICdrDllExport 
RTIBool RTICdrStream_serializeCdrEncapsulation(
    struct RTICdrStream *me, unsigned short *kind, unsigned short options);

extern RTICdrDllExport 
RTIBool RTICdrStream_deserializeCdrEncapsulationAndSetDefault(
    struct RTICdrStream *me);

extern RTICdrDllExport 
RTIBool RTICdrStream_deserializeCdrEncapsulation(
    struct RTICdrStream *me, unsigned short *kind, unsigned short *options);

extern RTICdrDllExport 
RTIBool RTICdrStream_deserializeParameterCdrEncapsulationAndSetDefault(
    struct RTICdrStream *me);

extern RTICdrDllExport
void RTICdrStream_pushEndian(
    struct RTICdrStream *me, RTICdrEndian *endian, RTIBool *needByteSwap);

extern RTICdrDllExport
void RTICdrStream_popEndian(
    struct RTICdrStream *me, RTICdrEndian *endian, RTIBool *needByteSwap);

extern RTICdrDllExport 
RTIBool RTICdrStream_isNativeLittleEndian(struct RTICdrStream *me);

extern RTICdrDllExport
RTIBool RTICdrStream_setEncapsulationKind(
    struct RTICdrStream *me, unsigned short kind, unsigned short options);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

  #include "cdr/cdr_stream_impl.h"

#endif /* cdr_stream_h */
