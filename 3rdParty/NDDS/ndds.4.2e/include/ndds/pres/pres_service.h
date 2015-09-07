/*
 * @(#)pres_service.h    generated by: makeheader    Mon Dec  3 23:08:15 2007
 *
 *		built from:	service.ifc
 */

#ifndef pres_service_h
#define pres_service_h


  #ifndef mig_rtps_h
    #include "mig/mig_rtps.h"
  #endif
  #ifndef pres_common_h
    #include "pres/pres_common.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif

struct PRESService;

struct PRESLocalEndpointListener;

struct PRESLocalEndpointStatisticsListener;

struct PRESGroupListener;

struct PRESServiceListener;

struct PRESTypePlugin;

struct REDAWorker;

typedef struct PRESLocalEndpoint *
(*PRESServiceLocalEndpointCreateFunction)(
    struct PRESService *me, int *failReason,
    RTIBool* autoenableContainedEntities, struct PRESGroup *group, 
    const struct REDAWeakReference *localTopicWR,
    const struct PRESTypePlugin *typePlugin,
    MIGRtpsObjectId oid, const struct PRESLocalEndpointProperty *p,
    const struct PRESLocalEndpointListener *listener, 
    PRESStatusKindMask listenerMask,
    struct REDAWorker *worker);

typedef RTIBool
(*PRESServiceLocalEndpointEnableFunction)(
    struct PRESService *me, int *failReason, struct PRESLocalEndpoint *endpoint,
    struct REDAWorker *worker);

typedef RTIBool (*PRESServiceLocalEndpointDestroyFunction)(
    struct PRESService *me, int *failReason, struct PRESGroup *group,
    struct PRESLocalEndpoint *endpoint,
    struct REDAWorker *worker);

typedef RTIBool (*PRESServiceRemoteEndpointAssertFunction)(
    struct PRESService *me, int *failReason, const struct MIGRtpsGuid *guid,
    const struct PRESRemoteEndpointProperty *p, struct REDAWorker *worker);

typedef RTIBool (*PRESServiceRemoteEndpointRemoveFunction)(
    struct PRESService *me, int *failReason,
    const struct MIGRtpsGuid *guid,
    struct REDAWorker *worker);

typedef PRESServiceRemoteEndpointRemoveFunction
PRESServiceRemoteEndpointUnregisterFunction;

typedef RTIBool (*PRESServiceRemoteEndpointsRemoveByTopicFunction)(
    struct PRESService *me, int *failReason,
    int *removeCount, const struct REDAWeakReference *topicTypeWR,
    struct REDAWorker *worker);

typedef RTIBool (*PRESServiceMatchingRemoteEndpointsRemoveFunction)(
    struct PRESService *me,  const struct MIGRtpsGuid *remoteGuid,
    struct REDAWorker *worker);

typedef PRESServiceMatchingRemoteEndpointsRemoveFunction
PRESServiceMatchingRemoteEndpointsUnregisterFunction;

typedef RTIBool (*PRESServiceLocalEndpointConfigListenerSetFunction)(
    struct PRESService *me,
    const struct PRESLocalEndpointConfigListener *listener, 
    struct REDAWorker *worker);

typedef const struct PRESLocalEndpointConfigListener* 
(*PRESServiceLocalEndpointConfigListenerGetFunction)(
    struct PRESService *me, struct REDAWorker *worker);

typedef RTIBool (*PRESServiceRemoteEndpointConfigListenerSetFunction)(
    struct PRESService *me,
    const struct PRESRemoteEndpointConfigListener *listener, 
    struct REDAWorker *worker);

typedef const struct PRESRemoteEndpointConfigListener *
(*PRESServiceRemoteEndpointConfigListenerGetFunction)(
    struct PRESService *me, struct REDAWorker *worker);

typedef RTIBool
(*PRESServiceNotifyOfContentFilterPolicyChangeFunction)(
        struct PRESService *me,
	struct PRESLocalEndpoint *endpoint,
	int    numValidEndpoints, 
	struct PRESContentFilterQosPolicy *policy,
	struct PRESContentFilterProperty *property ,
	struct REDAWorker *worker);

typedef struct PRESEntity* (*PRESServiceLookupEntityFunction)(
        struct PRESService *me,
	int *failReason,
	struct MIGRtpsGuid *guid,
	struct REDAWorker *worker);

typedef RTIBool (*PRESServiceServiceListenerSetFunction)(
    struct PRESService *me, const struct PRESServiceListener *listener,
    PRESStatusKindMask mask, struct REDAWorker *worker);

typedef const struct PRESServiceListener *
(*PRESServiceServiceListenerGetFunction)(
    struct PRESService *me, struct REDAWorker *worker);

typedef RTIBool (*PRESServiceTopicDataChangeNotifyFunction)(
    struct PRESService *me,
    struct REDAWeakReference *topicTypeWR,
    const struct PRESTopicDataQosPolicy *topicData, struct REDAWorker *worker);

typedef struct PRESGroup *(*PRESServiceGroupCreateFunction)(
    struct PRESService *me, int *failReason,
    RTIBool *autoenableCreatedEntities, MIGRtpsObjectId oid, 
    const struct PRESGroupProperty *property,
    const struct PRESGroupListener *listener, PRESStatusKindMask listenerMask,
    struct REDAExclusiveArea *groupEa, struct REDAWorker *worker);

typedef RTIBool
(*PRESServiceGroupEnableFunction)(
    struct PRESService *me, int *failReason, struct PRESGroup *group,
    struct REDAWorker *worker);

typedef RTIBool (*PRESServiceGroupDestroyFunction)(
    struct PRESService *me, int *failReason, struct PRESGroup *group,
    struct REDAWorker *worker);

typedef RTIBool (*PRESServiceHasGroupFunction)(
    struct PRESService *me, struct REDAWorker *worker);

typedef RTIBool (*PRESServiceAllEntitiesDestroyFunction)
    (struct PRESService *me, int *failReason, struct REDAWorker *worker);

typedef RTIBool (*PRESServiceEnableFunction)
    (struct PRESService *me, int *failReason, struct REDAWorker *worker);

typedef RTIBool (*PRESServiceAllEntitiesEnableFunction)
    (struct PRESService *me, int *failReason, struct REDAWorker *worker);

typedef void (*PRESServiceDeletionFunction)
    (struct PRESService *me, struct REDAWorker *worker);

typedef RTIBool (*PRESServiceShutdownFunction)
    (struct PRESService *me, int *failReason, struct REDAWorker *worker);

typedef RTIBool (*PRESServiceLocalEndpointPropertySetFunction)(
    struct PRESService *me, int *failReason, struct PRESLocalEndpoint *endpoint,
    const struct PRESLocalEndpointProperty *p, struct REDAWorker *worker);

typedef RTIBool (*PRESServiceLocalEndpointPropertyGetFunction)(
    struct PRESService *me, struct PRESLocalEndpointProperty *p,
    const struct PRESLocalEndpoint *endpoint, struct REDAWorker *worker);

typedef RTIBool (*PRESServiceLocalEndpointListenerSetFunction)(
    struct PRESService *me, int *failResaon, struct PRESLocalEndpoint *endpoint,
    const struct PRESLocalEndpointListener *listener, PRESStatusKindMask mask, 
    struct REDAWorker *worker);

typedef struct PRESLocalEndpointListener *
(*PRESServiceLocalEndpointListenerGetFunction)(
    struct PRESService *me, struct PRESLocalEndpoint *endpoint, 
    struct REDAWorker *worker);

typedef RTIBool (*PRESServiceLocalEndpointStatisticsListenerSetFunction)(
    struct PRESService *me, int *failReason, struct PRESLocalEndpoint *endpoint,
    const struct PRESLocalEndpointStatisticsListener *listener,  
    struct REDAWorker *worker);

typedef RTIBool (*PRESServiceGroupPropertySetFunction)(
    struct PRESService *me, int *failResaon, struct PRESGroup *group, 
    const struct PRESGroupProperty *property, struct REDAWorker *worker);

typedef RTIBool (*PRESServiceGroupPropertyGetFunction)(
    struct PRESService *me,  struct PRESGroupProperty *property, 
    struct PRESGroup *group, struct REDAWorker *worker);

typedef RTIBool (*PRESServiceGroupListenerSetFunction)(
    struct PRESService *me, int *failResaon, struct PRESGroup *group,
    const struct PRESGroupListener *listener, PRESStatusKindMask mask, 
    struct REDAWorker *worker);

typedef struct PRESGroupListener *(*PRESServiceGroupListenerGetFunction)(
    struct PRESService *me, struct PRESGroup *group, struct REDAWorker *worker);

typedef struct PRESLocalEndpoint *(*PRESPsServiceEndpointLookupFunction)(
    struct PRESService *me, struct PRESGroup *group, const char *topicName,
    struct REDAWorker *worker);

typedef struct PRESLocalEndpoint *(*PRESPsServiceEndpointLookupByGuidFunction)(
    struct PRESService *me, struct PRESGroup *group,
    const struct MIGRtpsGuid *guid,
    struct REDAWorker *worker);

typedef RTIBool (*PRESPsServiceAllEndpointsInGroupDestroyFunction)(
    struct PRESService *me, int *failReason, struct PRESGroup *group,
    struct REDAWorker *worker);

typedef void
(*PRESPsServiceCleanupFunction)(struct PRESService* me,
				struct REDAWorker* worker);

typedef RTIBool
(*PRESPsFinalizeFilteredRemoteReaderFunction)(struct PRESService *self,
					      struct REDAWeakReference *contentFilterWR,
					      struct REDAWorker *worker);

struct PRESService {

    /* all these are required by participant */

    PRESServiceGroupCreateFunction createGroup;
    PRESServiceGroupDestroyFunction destroyGroup;
    PRESServiceHasGroupFunction hasGroup;
    PRESServiceLocalEndpointCreateFunction createLocalEndpoint;
    PRESServiceLocalEndpointDestroyFunction destroyLocalEndpoint;
    PRESServiceRemoteEndpointAssertFunction assertRemoteEndpoint;
    PRESServiceRemoteEndpointRemoveFunction removeRemoteEndpoint;
    PRESServiceRemoteEndpointsRemoveByTopicFunction
    removeRemoteEndpointsByTopic;
    PRESServiceMatchingRemoteEndpointsRemoveFunction
    removeMatchingRemoteEndpoints;
    PRESServiceRemoteEndpointUnregisterFunction unregisterRemoteEndpoint;
    PRESServiceMatchingRemoteEndpointsUnregisterFunction
    unregisterMatchingRemoteEndpoints;
    PRESServiceTopicDataChangeNotifyFunction notifyOfTopicDataChange;
    PRESServiceLocalEndpointConfigListenerSetFunction
    setLocalEndpointConfigListener;
    PRESServiceLocalEndpointConfigListenerGetFunction
    getLocalEndpointConfigListener;
    PRESServiceRemoteEndpointConfigListenerSetFunction
    setRemoteEndpointConfigListener;
    PRESServiceRemoteEndpointConfigListenerGetFunction
    getRemoteEndpointConfigListener;
    PRESServiceNotifyOfContentFilterPolicyChangeFunction
    notifyOfContentFilterPolicyChange;
    PRESServiceLookupEntityFunction lookupEntity;

    /* these are not required by participant */

    PRESServiceGroupEnableFunction enableGroup;
    PRESServiceLocalEndpointEnableFunction enableLocalEndpoint;
    PRESServiceServiceListenerSetFunction setServiceListener;
    PRESServiceServiceListenerGetFunction getServiceListener;
    PRESServiceEnableFunction enableService;
    PRESServiceAllEntitiesEnableFunction enableAllEntities;
    PRESServiceAllEntitiesDestroyFunction destroyAllEntities;
    PRESServiceDeletionFunction deleteService;
    PRESServiceShutdownFunction shutdownService;
    PRESServiceLocalEndpointPropertySetFunction setLocalEndpointProperty;
    PRESServiceLocalEndpointPropertyGetFunction getLocalEndpointProperty;
    PRESServiceLocalEndpointListenerSetFunction setLocalEndpointListener;
    PRESServiceLocalEndpointListenerGetFunction getLocalEndpointListener;

    PRESServiceGroupPropertySetFunction setGroupProperty;
    PRESServiceGroupPropertyGetFunction getGroupProperty;
    PRESServiceGroupListenerSetFunction setGroupListener;
    PRESServiceGroupListenerGetFunction getGroupListener;
    PRESPsServiceEndpointLookupFunction lookupEndpointFromGroup;
    PRESPsServiceEndpointLookupByGuidFunction lookupEndpointByGuidFromGroup;
    PRESPsServiceAllEndpointsInGroupDestroyFunction 
    destroyAllLocalEndpointsInGroup;

    PRESPsServiceCleanupFunction cleanup;
    PRESPsFinalizeFilteredRemoteReaderFunction finalizeFilteredRemoteReader;
};


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* pres_service_h */
