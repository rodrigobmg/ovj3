/*
 * @(#)cdr_typeCode.h    generated by: makeheader    Mon Dec  3 23:08:01 2007
 *
 *		built from:	typeCode.ifc
 */

#ifndef cdr_typeCode_h
#define cdr_typeCode_h


 #ifndef osapi_type_h
    #include "osapi/osapi_type.h"
 #endif
 #ifndef cdr_dll_h
    #include "cdr/cdr_dll.h"
 #endif
 #ifndef cdr_type_h
    #include "cdr/cdr_type.h"
 #endif
#ifndef cdr_stream_h
    #include "cdr/cdr_stream.h"
#endif
#ifndef reda_fastBuffer_h
    #include "reda/reda_fastBuffer.h"
#endif

#ifdef __cplusplus
    extern "C" {
#endif


/* Value assigned to the label DEFAULT in a union.
 * This value should not be used to determine if a label is the default label
 * or not. Use the function RTICdrTypeCode_get_default_index instead.
 */
 
#define RTI_CDR_TYPE_CODE_UNION_DEFAULT_LABEL 0x40000001

typedef enum {
    RTI_CDR_TK_NULL,
    RTI_CDR_TK_SHORT,
    RTI_CDR_TK_LONG,
    RTI_CDR_TK_USHORT,
    RTI_CDR_TK_ULONG, 
    RTI_CDR_TK_FLOAT,
    RTI_CDR_TK_DOUBLE,
    RTI_CDR_TK_BOOLEAN,
    RTI_CDR_TK_CHAR,
    RTI_CDR_TK_OCTET,
    RTI_CDR_TK_STRUCT,
    RTI_CDR_TK_UNION,
    RTI_CDR_TK_ENUM,
    RTI_CDR_TK_STRING,
    RTI_CDR_TK_SEQUENCE,
    RTI_CDR_TK_ARRAY,
    RTI_CDR_TK_ALIAS,
    RTI_CDR_TK_LONGLONG,
    RTI_CDR_TK_ULONGLONG,     
    RTI_CDR_TK_LONGDOUBLE,
    RTI_CDR_TK_WCHAR,    
    RTI_CDR_TK_WSTRING,
    RTI_CDR_TK_VALUE
} RTICdrTCKind;

typedef short RTICdrValueModifier;


#define RTI_CDR_VM_NONE 0
#define RTI_CDR_VM_CUSTOM 1
#define RTI_CDR_VM_ABSTRACT 2
#define RTI_CDR_VM_TRUNCATABLE 3

typedef short RTICdrVisibility;


#define RTI_CDR_PRIVATE_MEMBER 0
#define RTI_CDR_PUBLIC_MEMBER 1

struct RTICdrTypeCode;

typedef struct RTICdrTypeCodeMember {
    char * _name; /* struct, union, enum, value */
    RTICdrBoolean _isPointer; /* struct, union, value */
    RTICdrShort _bits; /* struct, value */
    struct RTICdrTypeCode * _typeCode; /* struct, union, value */
    RTICdrLong _ordinal; /* enum */
    RTICdrUnsignedLong _labelsCount; /* union */
    RTICdrLong _label; /* union */
    RTICdrLong * _labels; /* union */
    RTICdrBoolean _isKey; /* struct, value */
    RTICdrVisibility _visibility; /* value */
} RTICdrTypeCodeMember;

typedef struct RTICdrTypeCode {
    RTICdrLong _kind;  /* All types */
    RTICdrBoolean _isPointer; /* alias */
    RTICdrLong _default_index; /* unions */              
    char * _name; /* struct, union, enum, alias, value */
    struct RTICdrTypeCode * _typeCode; /* alias, sequence, array, union, value */
    RTICdrUnsignedLong _maximumLength; /* string, wstring, sequence */
    RTICdrUnsignedLong _dimensionsCount; /* array */    
    RTICdrUnsignedLong * _dimensions; /* array */       
    RTICdrUnsignedLong _memberCount; /* atruct, union, value and enum */        
    struct RTICdrTypeCodeMember * _members; /* struct, union, enum and value */ 
    RTICdrValueModifier _typeModifier; /* value */
} RTICdrTypeCode;

extern RTICdrDllExport RTIBool RTICdrTypeCode_get_kind(RTICdrTypeCode * self,RTICdrTCKind * kind);

extern RTICdrDllExport RTIBool RTICdrTypeCode_equal(RTICdrTypeCode * self,
                                                    RTICdrTypeCode * typeCode,
                                                    RTICdrBoolean * equal);

extern RTICdrDllExport const char * RTICdrTypeCode_get_name(RTICdrTypeCode * self);

extern RTICdrDllExport RTIBool RTICdrTypeCode_get_member_count(RTICdrTypeCode * self,
                                                               RTICdrUnsignedLong * count);

extern RTICdrDllExport const char * RTICdrTypeCode_get_member_name(RTICdrTypeCode * self,
                                                                   RTICdrUnsignedLong index);

extern RTICdrDllExport RTICdrTypeCode * RTICdrTypeCode_get_member_type(RTICdrTypeCode * self,
                                                                       RTICdrUnsignedLong index);

extern RTICdrDllExport RTIBool RTICdrTypeCode_get_member_label_count(RTICdrTypeCode * self,
                                                                     RTICdrUnsignedLong index,
                                                                     RTICdrUnsignedLong * labelCount);

extern RTICdrDllExport RTIBool RTICdrTypeCode_get_member_label(RTICdrTypeCode * self,
                                                               RTICdrUnsignedLong memberIndex,
                                                               RTICdrUnsignedLong labelIndex,
                                                               RTICdrLong * label);

extern RTICdrDllExport RTIBool RTICdrTypeCode_get_member_ordinal(RTICdrTypeCode * self,
                                                                 RTICdrUnsignedLong index,
                                                                 RTICdrLong * ordinal);

extern RTICdrDllExport RTIBool RTICdrTypeCode_is_member_key(RTICdrTypeCode * self,
                                                            RTICdrUnsignedLong index,
                                                            RTICdrBoolean * isKey);

extern RTICdrDllExport RTIBool RTICdrTypeCode_is_member_pointer(RTICdrTypeCode * self,
                                                                RTICdrUnsignedLong index,
                                                                RTICdrBoolean * isPointer);

extern RTICdrDllExport RTIBool RTICdrTypeCode_is_member_bitfield(RTICdrTypeCode * self,
                                                                 RTICdrUnsignedLong index,
                                                                 RTICdrBoolean * isBitField);

extern RTICdrDllExport RTIBool RTICdrTypeCode_get_member_bitfield_bits(RTICdrTypeCode * self,
                                                                       RTICdrUnsignedLong index,
                                                                       RTICdrShort * bits);

extern RTICdrDllExport RTIBool RTICdrTypeCode_get_member_visibility(RTICdrTypeCode * self,
                                                                    RTICdrUnsignedLong index,
                                                                    RTICdrVisibility * visibility);

extern RTICdrDllExport RTICdrTypeCode * RTICdrTypeCode_get_discriminator_type(RTICdrTypeCode * self);

extern RTICdrDllExport RTIBool RTICdrTypeCode_get_length(RTICdrTypeCode * self,
                                                         RTICdrUnsignedLong * length);

extern RTICdrDllExport RTIBool RTICdrTypeCode_get_array_dimension_count(RTICdrTypeCode * self,
                                                                        RTICdrUnsignedLong * dimensionCount);

extern RTICdrDllExport RTIBool RTICdrTypeCode_get_array_dimension(RTICdrTypeCode * self,
                                                                  RTICdrUnsignedLong index,                                        
                                                                  RTICdrUnsignedLong * dimension);

extern RTICdrDllExport RTICdrTypeCode * RTICdrTypeCode_get_content_type(RTICdrTypeCode * self);

extern RTICdrDllExport RTIBool RTICdrTypeCode_is_alias_pointer(RTICdrTypeCode * self,
                                                               RTICdrBoolean * isPointer);

extern RTICdrDllExport RTIBool RTICdrTypeCode_get_default_index(RTICdrTypeCode * self,
                                                                RTICdrLong * index);

extern RTICdrDllExport RTICdrTypeCode * RTICdrTypeCode_get_concrete_base_type(RTICdrTypeCode * self);

extern RTICdrDllExport RTIBool RTICdrTypeCode_get_type_modifier(RTICdrTypeCode * self,
                                                                RTICdrValueModifier * typeModifier);

extern RTICdrDllExport RTIBool RTICdrTypeCode_print_IDL(RTICdrTypeCode * self,RTICdrUnsignedLong indent);

extern RTICdrDllExport RTICdrLong RTICdrTypeCode_get_stream_length(RTICdrTypeCode * self);

extern RTICdrDllExport RTICdrTypeCode * RTICdrTypeCode_create_stream(RTICdrUnsignedShort length);

extern RTICdrDllExport RTIBool RTICdrTypeCode_initialize_stream(RTICdrTypeCode * typeCode,
                                                                RTICdrUnsignedShort length); 
extern RTICdrDllExport RTIBool RTICdrTypeCode_copy_stream(RTICdrTypeCode * dst,RTICdrTypeCode * src);

extern RTICdrDllExport RTIBool 
RTICdrTypeCode_serialize(
    struct RTICdrStream *stream,
    const struct RTICdrTypeCode * typeCode,
    void *serializeOption);

extern RTICdrDllExport RTIBool 
RTICdrTypeCode_deserialize(
    struct RTICdrStream *stream,
    struct RTICdrTypeCode ** typeCode,
    struct REDAFastBufferPool *pool);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* cdr_typeCode_h */
