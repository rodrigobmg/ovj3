/*
 * @(#)dds_c_infrastructure_impl.h    generated by: makeheader    Mon Dec  3 23:08:26 2007
 *
 *		built from:	infrastructure_impl.ifc
 */

#ifndef dds_c_infrastructure_impl_h
#define dds_c_infrastructure_impl_h



/* Must be explicitly included to include the definition of size_t when
 * compiling under gcc 2.71 (e.g. Vx 5.4 architectures).
 */
#include <stddef.h>

#include "log/log_makeheader.h"

#ifndef pres_common_h
  #include "pres/pres_common.h"
#endif
#ifndef dds_c_infrastructure_h
  #include "dds_c/dds_c_infrastructure.h"
#endif
#ifndef dds_c_dll_h
  #include "dds_c/dds_c_dll.h"
#endif

#ifdef __cplusplus
    extern "C" {
#endif

extern DDSCDllExport void* DDS_Entity_get_user_dataI(DDS_Entity* self);

/*i @ingroup DDSConditionModule
 * 
 * @brief   set user object pointer
 */    
extern DDSCDllExport void DDS_Condition_set_user_objectI(DDS_Condition* self,
                                                         void *userObject);

/*i @ingroup DDSConditionModule
 * 
 * @brief   set user object pointer
 */    
extern DDSCDllExport void* DDS_Condition_get_user_objectI(DDS_Condition* self);

extern DDSCDllExport DDS_GuardCondition* DDS_GuardCondition_newI(void *userObject);

 extern DDSCDllVariable const int DDS_WAITSET_EXCLUSIVE_AREA_LEVEL;

 extern DDSCDllVariable const int DDS_CONDITION_EXCLUSIVE_AREA_LEVEL;

extern DDSCDllExport void DDS_WaitSet_set_user_objectI(DDS_WaitSet* self,
                                                         void *userObject);

/*i @ingroup DDSWaitSetModule
 * 
 * @brief   set user object pointer
 */    
extern DDSCDllExport void* DDS_WaitSet_get_user_objectI(DDS_WaitSet* self);

extern  DDSCDllExport
DDS_ReturnCode_t DDS_WaitSet_waitI(DDS_WaitSet* self,
        struct DDS_ConditionSeq* active_conditions,
        const struct DDS_Duration_t* timeout);

extern DDSCDllExport
int DDS_WaitSet_start_conditions_iteratorI(DDS_WaitSet* self,
                                           RTIBool activeConditions);

extern DDSCDllExport
void DDS_WaitSet_end_conditions_iteratorI(DDS_WaitSet* self);

extern DDSCDllExport
DDS_Condition* DDS_WaitSet_get_next_conditionI(DDS_WaitSet*self,
                                     RTIBool activeConditions);

extern DDSCDllExport
void DDS_WaitSet_end_waitI(DDS_WaitSet *self);

struct REDAWorker;

extern DDSCDllExport struct REDAWorker* DDS_DomainEntity_get_workerI(
    DDS_Entity* self);

struct REDAWorker;

extern DDSCDllExport DDS_ReturnCode_t DDS_Entity_lockI(
    DDS_Entity* self);

struct REDAWorker;

extern DDSCDllExport DDS_ReturnCode_t DDS_Entity_unlockI(
    DDS_Entity* self);

extern RTIBool DDS_Entity_is_enabled(DDS_Entity* self);

extern DDSCDllExport DDS_Boolean
DDS_ProtocolVersion_equals(const DDS_ProtocolVersion_t *a, const DDS_ProtocolVersion_t *b);

extern DDSCDllExport DDS_Boolean
DDS_VendorId_equals(const struct DDS_VendorId_t *a, const struct DDS_VendorId_t *b);

extern DDSCDllExport DDS_Boolean 
DDS_ContentFilterProperty_equals(
    const struct DDS_ContentFilterProperty_t* left,
    const struct DDS_ContentFilterProperty_t* right);

extern DDSCDllExport DDS_Boolean 
DDS_DeadlineQosPolicy_equals(
    const struct DDS_DeadlineQosPolicy* left,
    const struct DDS_DeadlineQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_DestinationOrderQosPolicy_equals(
    const struct DDS_DestinationOrderQosPolicy* left,
    const struct DDS_DestinationOrderQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_DurabilityQosPolicy_equals(
    const struct DDS_DurabilityQosPolicy* left,
    const struct DDS_DurabilityQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_DurabilityServiceQosPolicy_equals(
    const struct DDS_DurabilityServiceQosPolicy* left,
    const struct DDS_DurabilityServiceQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_EntityNameQosPolicy_equals(
    const struct DDS_EntityNameQosPolicy* left,
    const struct DDS_EntityNameQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_GroupDataQosPolicy_equals(
    const struct DDS_GroupDataQosPolicy* left,
    const struct DDS_GroupDataQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_LifespanQosPolicy_equals(
    const struct DDS_LifespanQosPolicy* left,
    const struct DDS_LifespanQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_LivelinessQosPolicy_equals(
    const struct DDS_LivelinessQosPolicy* left,
    const struct DDS_LivelinessQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_LocatorSeq_equals(
    const struct DDS_LocatorSeq* left,
    const struct DDS_LocatorSeq* right);

extern DDSCDllExport DDS_Boolean 
DDS_OwnershipQosPolicy_equals(
    const struct DDS_OwnershipQosPolicy* left,
    const struct DDS_OwnershipQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_OwnershipStrengthQosPolicy_equals(
    const struct DDS_OwnershipStrengthQosPolicy* left,
    const struct DDS_OwnershipStrengthQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_PartitionQosPolicy_equals(
    const struct DDS_PartitionQosPolicy* left,
    const struct DDS_PartitionQosPolicy* right);

extern DDSCDllExport DDS_Boolean DDS_PresentationQosPolicy_equals(
    const struct DDS_PresentationQosPolicy* left,
    const struct DDS_PresentationQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_ProductVersion_equals(
    const struct DDS_ProductVersion_t* left,
    const struct DDS_ProductVersion_t* right);

extern DDSCDllExport DDS_Boolean 
DDS_PropertyQosPolicy_equals(
    const struct DDS_PropertyQosPolicy* left,
    const struct DDS_PropertyQosPolicy* right,
    DDS_Boolean remote);

extern DDSCDllExport DDS_Boolean 
DDS_ReliabilityQosPolicy_equals(
    const struct DDS_ReliabilityQosPolicy* left,
    const struct DDS_ReliabilityQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_ServiceQosPolicy_equals(
    const struct DDS_ServiceQosPolicy* left,
    const struct DDS_ServiceQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_TimeBasedFilterQosPolicy_equals(
    const struct DDS_TimeBasedFilterQosPolicy* left,
    const struct DDS_TimeBasedFilterQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_TopicDataQosPolicy_equals(
    const struct DDS_TopicDataQosPolicy* left,
    const struct DDS_TopicDataQosPolicy* right);

extern DDSCDllExport DDS_Boolean 
DDS_UserDataQosPolicy_equals(
    const struct DDS_UserDataQosPolicy* left,
    const struct DDS_UserDataQosPolicy* right);

extern DDSCDllExport RTIBool
DDS_LatencyBudgetQosPolicy_equalI(
    const struct DDS_LatencyBudgetQosPolicy *dst,
    const struct DDS_LatencyBudgetQosPolicy *src);

extern DDSCDllExport DDS_ReturnCode_t 
DDS_StringSeq_from_delimited_string(
    struct DDS_StringSeq* self, const char* src, char delim);



#define DDS_ProtocolVersion_equals(a, b)   \
    ((a)->major == (b)->major && \
     (a)->minor == (b)->minor)

#define DDS_VendorId_equals(a, b)   \
    ((a)->vendorId[0] == (b)->vendorId[0] && \
     (a)->vendorId[1] == (b)->vendorId[1])


extern DDSCDllExport
void DDS_GUID_copy_to_pres_guid(const struct DDS_GUID_t* self,
                                struct MIGRtpsGuid * other);

extern DDSCDllExport
void DDS_GUID_copy_from_pres_guid(struct DDS_GUID_t* self,
                                  const struct MIGRtpsGuid * other);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* dds_c_infrastructure_impl_h */
