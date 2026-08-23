/**
 ****************************************************************************************
 *
 * @file aml_nan.h
 *
 * @brief nan api
 *
 * Copyright (C) Amlogic 2024-2034
 *
 ****************************************************************************************
 */

#ifndef _AML_NAN_H_
#define _AML_NAN_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <linux/types.h>


/*
 * CONSTANTS
 ****************************************************************************************
 */
#define AML_NAN_PUB_PATH "w2l/publish.conf"
#define AML_NAN_SUB_PATH "w2l/subscribe.conf"

#ifndef MAC2STR
#define MAC2STR(a) (a)[0], (a)[1], (a)[2], (a)[3], (a)[4], (a)[5]
#define MACSTR "%02x:%02x:%02x:%02x:%02x:%02x"
#endif

/* Definitions for error constants. */
#define AML_OK          (0)       /* value indicating success (no error) */
#define AML_FAIL        (-1)      /* indicating failure */

#define NAN_WIFI_NAN_MAX_SVC_SUPPORTED  (2)
#define NAN_WIFI_MAX_SVC_NAME_LEN       (32)
#define NAN_WIFI_MAX_FILTER_LEN         (64)
#define NAN_WIFI_MAX_SVC_INFO_LEN       (255)
#define NAN_SUBSCRIBE_MAX_ADDRESS       (8)
#define HASH_STR_LEN                    (7)

/*Max publish + subscribe numbers 4*/
#define NAN_MAX_PUBLISH_NUM 2
#define NAN_MAX_SUBSCRIBE_NUM 2

/* NAN Service Name Hash Length */
#define NAN_SERVICE_HASH_LENGTH 6

#define NAN_MAX_PEERS_RECORD    15
#define NAN_PUBLISH         2
#define NAN_SUBSCRIBE       1

#define NAN_SDA_SERVICE_CONTROL_TYPE_PUBLISH 0
#define NAN_SDA_SERVICE_CONTROL_TYPE_SUBSCRIBE BIT(0)
#define NAN_SDA_SERVICE_CONTROL_TYPE_FOLLOWUP BIT(1)

/*
 * TYPE and STRUCT DEFINITIONS
 ****************************************************************************************
 */

/**
  * @brief NAN Discovery enable configuration
  *
  */
typedef struct  {
    //uint8_t vif_idx;
    uint8_t op_channel;    /* NAN Discovery operating channel */
    uint8_t master_pref;   /* Device's preference value to serve as NAN Master */
    uint8_t random_factor;
    uint8_t scan_time;     /* Scan time in seconds while searching for a NAN cluster */
    uint16_t warm_up_sec;  /* Warm up time before assuming NAN Anchor Master role */
} wifi_nan_cfg;

typedef struct {
    uint8_t match_filter_len;
    uint8_t match_filter[NAN_WIFI_MAX_FILTER_LEN];
} match_filter;

typedef struct {
    uint8_t publish_id;
    uint8_t publish_type;
    uint8_t inst_id;                                /**< Own service instance id */
    uint8_t peer_inst_id;                           /**< Peer's service instance id */
    uint8_t peer_mac[6];
    uint8_t service_name[NAN_WIFI_MAX_SVC_NAME_LEN];
    uint8_t service_name_hash[NAN_SERVICE_HASH_LENGTH];
    uint8_t service_specific_info[NAN_WIFI_MAX_SVC_INFO_LEN];
    match_filter match_filter_tx;
    match_filter match_filter_rx;
} publish_config;

/* NAN Service Response Filter Attribute Bit */
enum nan_srf_type {
    NAN_SRF_ATTR_PARTIAL_MAC_ADDR = 0,
    NAN_SRF_ATTR_BLOOM_FILTER,
};

typedef struct {
    enum nan_srf_type srf_type;
    bool    srf_include;
    uint8_t srf_bf_len;
    uint8_t srf_bf_idx;
    uint8_t srf_bf[32];
    uint8_t srf_num_macs;
    uint8_t srf_mac_addresses[NAN_SUBSCRIBE_MAX_ADDRESS][MAC_ADDR_LEN];
} srf_info;

typedef struct {
    uint8_t subscribe_id;
    uint8_t subscribe_type;
    uint8_t service_name[NAN_WIFI_MAX_SVC_NAME_LEN];
    uint8_t service_specific_info[NAN_WIFI_MAX_SVC_INFO_LEN];
    match_filter match_filter_tx;
    match_filter match_filter_rx;
    srf_info srf;
} subscribe_config;

typedef struct {
    publish_config publish;
    subscribe_config subscribe;
} svc_config;

/**
  * @brief NAN Services types
  *
  */
typedef enum {
    NAN_PUBLISH_SOLICITED,  /* Send unicast Publish frame to Subscribers that match the requirement */
    NAN_PUBLISH_UNSOLICITED,/* Send broadcast Publish frames in every Discovery Window(DW) */
    NAN_SUBSCRIBE_ACTIVE,   /* Send broadcast Subscribe frames in every DW */
    NAN_SUBSCRIBE_PASSIVE,  /* Passively listens to Publish frames */
} wifi_nan_service_type_t;

/**
  * @brief NAN Publish service configuration parameters
  *
  */
typedef struct {
    uint8_t publish_id;
    uint8_t inst_id;                                /**< Own service instance id */
    uint8_t peer_inst_id;                           /**< Peer's service instance id */
    wifi_nan_service_type_t type;                   /**< Service type */
    uint8_t service_name_len;
    uint8_t service_name[NAN_WIFI_MAX_SVC_NAME_LEN];   /* Service name identifier */
    uint8_t svc_info_len;
    uint8_t svc_info[NAN_WIFI_MAX_SVC_INFO_LEN];       /* Service info shared in Subscribe frame */
    match_filter mf;
    uint8_t service_name_hash[NAN_SERVICE_HASH_LENGTH];
    uint8_t peer_mac[6];
    bool cancel;
} wifi_nan_publish_cfg;

/**
  * @brief NAN Subscribe service configuration parameters
  *
  */
typedef struct {
    uint8_t subscribe_id;
    wifi_nan_service_type_t type;                   /* Service type */
    uint8_t service_name_len;
    uint8_t service_name[NAN_WIFI_MAX_SVC_NAME_LEN];   /* Service name identifier */
    uint8_t svc_info_len;
    uint8_t svc_info[NAN_WIFI_MAX_SVC_INFO_LEN];       /* Service info shared in Subscribe frame */
    match_filter mf;
    uint8_t service_name_hash[NAN_SERVICE_HASH_LENGTH];
    srf_info srf;
    bool cancel;
} wifi_nan_subscribe_cfg;

/**
  * @brief NAN Follow-up parameters
  *
  */
typedef struct {
    uint8_t inst_id;                         /* Own service instance id */
    uint8_t peer_inst_id;                    /* Peer's service instance id */
    uint8_t peer_mac[6];                     /* Peer's MAC address */
    uint8_t svc_info_len;
    uint8_t svc_info[NAN_WIFI_MAX_SVC_INFO_LEN];/* Service info(or message) to be shared */
    uint8_t service_name_hash[NAN_SERVICE_HASH_LENGTH];
} wifi_nan_followup_cfg;


/** Parameters of a peer service record */
typedef struct {
    uint8_t peer_svc_id;   /**< Identifier of Peer's service */
    uint8_t own_svc_id;    /**< Identifier of own service associated with Peer */
    uint8_t peer_svc_type; /**< Peer's service type (Publish/Subscribe) */
} nan_peer_record;

struct peer_svc_info_list {
    struct list_head list;
    uint8_t peer_svc_info[NAN_WIFI_MAX_SVC_INFO_LEN];   /**< Information for followup message */
    uint8_t svc_id;                                     /**< Identifier of peer's service */
    uint8_t own_svc_id;                                 /**< Identifier for own service  */
    uint8_t type;                                       /**< Service type (Publish/Subscribe) */
    uint8_t peer_nmi[6];                                /**< Peer's NAN Management Interface address */
};

struct peer_svc_info {
    uint8_t peer_svc_info[NAN_WIFI_MAX_SVC_INFO_LEN];   /**< Information for followup message */
    uint8_t svc_id;                                     /**< Identifier of peer's service */
    uint8_t own_svc_id;                                 /**< Identifier for own service  */
    uint8_t type;                                       /**< Service type (Publish/Subscribe) */
    uint8_t peer_nmi[6];                                /**< Peer's NAN Management Interface address */
    uint8_t service_name_hash[NAN_SERVICE_HASH_LENGTH];
    match_filter mf;
    srf_info srf;
};

struct own_svc_info {
    struct list_head peer_list;                         /**< List of peers matched for specific service */
    uint8_t svc_name[NAN_WIFI_MAX_SVC_NAME_LEN];        /**< Name identifying a service */
    uint8_t svc_id;                                     /**< Identifier for a service */
    uint8_t type;                                       /**< Service type (Publish/Subscribe) */
    uint8_t num_peer_records;                           /**< Count of peer records associated with svc_id */
    match_filter mf_tx;
    match_filter mf_rx;
};

typedef struct {
    uint8_t state;
    uint8_t instance_id;
    uint8_t nan_svc_num;
    spinlock_t peer_list_lock;
    struct own_svc_info own_svc[NAN_WIFI_NAN_MAX_SVC_SUPPORTED]; /**< Record of own service(s) */
} nan_ctx_t;

/// Structure containing the parameters of the @ref PRIV_NAN_ENABLE_CFM message.
struct nan_enable_cfm
{
    /// Status of the AP starting procedure
    uint8_t status;
    /// Index of the VIF for which the AP is started
    uint8_t vif_idx;
};

/*
 * FUNCTION PROTOTYPES
 ****************************************************************************************
 */

/**
  * @brief      Start NAN Discovery with provided configuration
  *
  * @attention  This API should be called after aml_cfg80211_init().
  *
  * @param      nan_conf  NAN related parameters to be configured.
  *
  * @return
  *    - non-zero: failed
  *    - zero: succeed
  */
int aml_nan_enable(struct aml_hw *aml_hw, wifi_nan_cfg *nan_conf);

/**
  * @brief      Stop NAN Discovery, end NAN Services
  *
  * @return
  *    - non-zero: failed
  *    - zero: succeed
  */
int aml_nan_disable(struct aml_hw *aml_hw);

/**
  * @brief      Start Publishing a service to the NAN Peers in vicinity
  *
  * @attention  This API should be called after aml_nan_enable().
  *
  * @param      pub_cfg  Configuration parameters for publishing a service.
  *             service_id Service identifier
  *             cancel   Is cancel service
  *
  * @return
  *    - Greater than zero: Publish service identifier
  *    - Less than or equal to zero: failed
  */
int aml_nan_publish_service(struct aml_hw *aml_hw, publish_config *pub_cfg, uint8_t service_id, bool cancel);

/**
  * @brief      Subscribe for a service within the NAN cluster
  *
  * @attention  This API should be called after aml_wifi_nan_start().
  *
  * @param      sub_cfg  Configuration parameters for subscribing for a service.
  *             service_id Service identifier
  *             cancel   Is cancel service
  *
  * @return
  *    - Greater than zero: Subscribe service identifier
  *    - Less than or equal to zero: failed
  */
int aml_nan_subscribe_service(struct aml_hw *aml_hw, subscribe_config *sub_cfg,  uint8_t service_id, bool cancel);

/**
  * @brief      Send a follow-up message to the NAN Peer with matched service
  *
  * @attention  This API should be called after a NAN service is discovered due to a match.
  *
  * @param      followup_conf Configuration parameters for sending a Follow-up message.
  *
  * @return
  *    - AML_OK: succeed
  *    - others: failed
  */
int aml_nan_send_message(struct aml_hw *aml_hw, wifi_nan_followup_cfg *followup_conf);

/**
  * @brief      Cancel a NAN service
  *
  * @param      service_id Publish/Subscribe service id to be cancelled.
  *
  * @return
  *    - AML_OK: succeed
  *    - others: failed
  */
int aml_nan_cancel_service(struct aml_hw *aml_hw, uint8_t service_id);

/**
 * brief         Get own Service information from Service ID
 *
 * @param        svc_id It indicates Service ID to search for.
 * @return
 *   - !NULL: succeed
 *   - NULL: failed
 */
struct own_svc_info *aml_nan_find_own_svc(uint8_t svc_id);

/**
 * brief         Find Peer's Service information using Peer MAC and Service ID.
 *
 * @param        own_svc_id   Owner service ID of the published/subscribed service.
 * @param        peer_svc_id  Peer service ID of the published/subscribed service.
 * @param        peer_nmi     Peer's NAN Management Interface MAC address.
 * @return
 *   - !NULL: succeed
 *   - NULL: failed
 */
struct peer_svc_info_list *aml_nan_find_peer_svc(uint8_t own_svc_id, uint8_t peer_svc_id, uint8_t peer_nmi[]);

/**
 * brief         Record Peer's Service information.
 *
 * @param        own_svc_id   Owner service ID of the published/subscribed service.
 * @param        peer_svc_id  Peer service ID of the published/subscribed service.
 * @param        peer_nmi     Peer's NAN Management Interface MAC address.
 * @return
 *   - AML_OK: succeed
 *   - AML_FAIL: failed
 */
bool aml_nan_record_peer_svc(uint8_t own_svc_id, uint8_t peer_svc_id, uint8_t peer_nmi[]);

/**
 * brief         Convert ASCII string to MAC address
 *
 * @param        txt MAC address as a string(e.g., 00:11:22:33:44:55 or 0011.2233.4455)
 * @param        addr Buffer for the MAC address (ETH_ALEN = 6 bytes).
 * @return
 *   - Characters used (> 0): success
 *   - -1: failure
 */
int hwaddr_aton2(const char *txt, uint8_t *addr);

/**
 * brief          Get nan unsolcoted publish config
 *
 * @param[out]    publish_req publish request config
 * @param[in]     pub_cfg publish config
 * @return
 *    - non-zero: succeed
 *    - zero: failed
 */
uint8_t aml_nan_get_unsolcoted_pub_cfg(struct aml_hw *aml_hw, wifi_nan_publish_cfg *publish_req, publish_config* pub_cfg);

/**
 * brief          Get nan solcoted publish config
 *
 * @param[out]    publish_req publish request config
 * @param[in]     pub_cfg publish config
 * @return
 *    - non-zero: succeed
 *    - zero: failed
 */
uint8_t aml_nan_get_solcoted_pub_cfg(wifi_nan_publish_cfg *publish_req, publish_config* pub_cfg);

/**
 * brief          Get nan subscribe config
 *
 * @param[out]    subscribe_req subscribe request config
 * @param[in]     sub_cfg subscribe config
 * @return
 *    - non-zero: succeed
 *    - zero: failed
 */
uint8_t aml_nan_get_sub_cfg(struct aml_hw *aml_hw, wifi_nan_subscribe_cfg *subscribe_req, subscribe_config *sub_cfg);

/**
 * brief          Get nan follow up config
 *
 * @param[out]    fup_params follow up params
 * @return
 *    - Greater than zero: succeed
 *    - Less than or equal to zero: failed
 */
int32_t aml_nan_get_followup_cfg(wifi_nan_followup_cfg *fup_params);

#endif
