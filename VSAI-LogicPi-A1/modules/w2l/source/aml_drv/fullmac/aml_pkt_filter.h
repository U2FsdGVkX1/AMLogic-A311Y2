/**
 ******************************************************************************
 *
 * @file aml_pkt_filter.h
 *
 * Copyright (C) Amlogic 2012-2021
 *
 ******************************************************************************
 */
#ifndef _AML_PKT_FILTER_H_
#define _AML_PKT_FILTER_H_

#define DHCP_SP_V4      0x0043
#define DHCP_CP_V4      0x0044
#define DHCP_SP_V6      0x0223
#define DHCP_CP_V6      0x0222
#define DHCP_MAGIC      0x63825363
#define DHCP_OPTION_TYPE        0x35
#define DHCP_SERVER_PORT 67
#define DHCP_CLIENT_PORT 68
#define MAC_SHORT_MAC_HDR_LEN   24
#define ACTION_CODE_VENDOR      0x09
#define ACTION_GAS_INIT_REQ        10
#define ACTION_GAS_INIT_RSP        11
#define ACTION_GAS_COMEBACK_REQ    12
#define ACTION_GAS_COMEBACK_RSP    13

#define ACTION_DPP_CONFIGURATION_RESULT     11
#define ACTION_DPP_CONNECT_STATUS_RESULT    12
#define PUBLIC_ACTION           0x04
#define VENDOR_SPEC             0x7f
#define OUI_TYPE_P2P            0x09
#define OUI_TYPE_DPP            0x1a
#define CATEGORY_OFFSET         MAC_SHORT_MAC_HDR_LEN
#define ACTION_CODE_OFFSET      (CATEGORY_OFFSET + 1)
#define OUI_OFFSET              (CATEGORY_OFFSET + 2)
#define OUI_TYPE_OFFSET         (CATEGORY_OFFSET + 5)
#define OUI_SUBTYPE_OFFSET      (CATEGORY_OFFSET + 6)
#define DPP_PUBLIC_ACTION_SUBTYPE_OFFSET      (CATEGORY_OFFSET + 7)
#define AUTH_ALGO_OFFSET        MAC_SHORT_MAC_HDR_LEN
#define WPA_REPLAY_COUNTER_LEN 8
#define WPA_NONCE_LEN 32
#define WPA_KEY_RSC_LEN 8
#define ATTR_MSG_TYPE   0x1022
/* IEEE 802.11, 8.5.2 EAPOL-Key frames */
#define WPA_KEY_INFO_TYPE_MASK ((u16)   (BIT(0) | BIT(1) | BIT(2)))
#define WPA_KEY_INFO_TYPE_AKM_DEFINED   0
#define WPA_KEY_INFO_TYPE_HMAC_MD5_RC4  BIT(0)
#define WPA_KEY_INFO_TYPE_HMAC_SHA1_AES BIT(1)
#define WPA_KEY_INFO_TYPE_AES_128_CMAC  3
#define WPA_KEY_INFO_KEY_TYPE           BIT(3) /* 1 = Pairwise, 0 = Group key */
/* bit4..5 is used in WPA, but is reserved in IEEE 802.11i/RSN */
#define WPA_KEY_INFO_KEY_INDEX_MASK     (BIT(4) | BIT(5))
#define WPA_KEY_INFO_KEY_INDEX_SHIFT    4
#define WPA_KEY_INFO_INSTALL    BIT(6) /* pairwise */
#define WPA_KEY_INFO_TXRX       BIT(6) /* group */
#define WPA_KEY_INFO_ACK        BIT(7)
#define WPA_KEY_INFO_MIC        BIT(8)
#define WPA_KEY_INFO_SECURE     BIT(9)
#define WPA_KEY_INFO_ERROR      BIT(10)
#define WPA_KEY_INFO_REQUEST    BIT(11)
#define WPA_KEY_INFO_ENCR_KEY_DATA  BIT(12) /* IEEE 802.11i/RSN only */
#define WPA_KEY_INFO_SMK_MESSAGE    BIT(13)

/* WAPI protocol */
#define WAPI_PROTOCOL_ID (0x88B4)
#define WAPI_PROTOCOL_TYPE 1

#define AML_PKT_SP_TX   (BIT(AML_PKT_EAPOL) | \
                         BIT(AML_PKT_ARP) | \
                         BIT(AML_PKT_DHCP) | BIT(AML_PKT_DHCP_V6) | \
                         BIT(AML_PKT_RTSP))

#define AML_PKT_SP_RX   (AML_PKT_SP_TX | BIT(AML_PKT_ICMP))

/* WAPI subtype field */
enum {
    WAPI_SUBTYPE_PREAUTH_START               = 1,
    WAPI_SUBTYPE_STAKEY_REQUEST              = 2,
    WAPI_SUBTYPE_AUTH_ACTIVATION             = 3,
    WAPI_SUBTYPE_AUTH_REQUEST                = 4,
    WAPI_SUBTYPE_AUTH_RESPONSE               = 5,
    WAPI_SUBTYPE_CERT_AUTH_REQUEST           = 6,
    WAPI_SUBTYPE_CERT_AUTH_RESPONSE          = 7,
    WAPI_SUBTYPE_UNICAST_KEY_REQUEST         = 8,
    WAPI_SUBTYPE_UNICAST_KEY_RESPONSE        = 9,
    WAPI_SUBTYPE_UNICAST_KEY_CONFIRM         = 10,
    WAPI_SUBTYPE_MULTICAST_KEY_ANNOUNCEMENT  = 11,
    WAPI_SUBTYPE_MULTICAST_KEY_RESPONSE      = 12
};

typedef enum {
    SP_STATUS_TX_START = 0,
    SP_STATUS_RX,
    SP_STATUS_TX_SUC,
    SP_STATUS_TX_FAIL,
} AML_SP_STATUS_E;

enum {
    AML_SP_FRAME = BIT(0),
    AML_P2P_ACTION_FRAME = BIT(1),
    AML_DPP_ACTION_FRAME = BIT(2),
    AML_CSA_ACTION_FRAME = BIT(3),
    AML_GAS_ACTION_FRAME = BIT(4),
    AML_GAS_INIT_REQ_FRAME = BIT(5),
    AML_GAS_INIT_RSP_FRAME = BIT(6),
    AML_REPORT_NO_ACKED = BIT(7),
    AML_MUST_TX_SUC = BIT(8),
    AML_DPP_CONNECT_STATUS_RESULT_FRAME = BIT(9),
};

enum aml_pkt_type {
    AML_PKT_80211 = 0,      /* reserved for 802.11 (management) frame */

    /* Ethernet protocol = ETH_P_PAE */
    AML_PKT_EAPOL,

    /* Ethernet protocol = ETH_P_ARP */
    AML_PKT_ARP,
    AML_PKT_ARP_REQ,
    AML_PKT_ARP_REPLY,

    /* Ethernet protocol = ETH_P_IP or ETH_P_IPV6 */
    AML_PKT_IP,
    AML_PKT_IPV6,
    AML_PKT_ICMP,
    AML_PKT_TCP,
    AML_PKT_UDP,
    AML_PKT_DHCP,
    AML_PKT_DHCP_V6,
    AML_PKT_RTSP,

    AML_PKT_LAST,
};

enum wsc_op_code {
    WSC_UPNP = 0 /* No OP Code in UPnP transport */,
    WSC_START = 0x01,
    WSC_ACK = 0x02,
    WSC_NACK = 0x03,
    WSC_MSG = 0x04,
    WSC_DONE = 0x05,
    WSC_FRAG_ACK = 0x06
};

enum {
    IEEE802_1X_TYPE_EAP_PACKET = 0,
    IEEE802_1X_TYPE_EAPOL_START = 1,
    IEEE802_1X_TYPE_EAPOL_LOGOFF = 2,
    IEEE802_1X_TYPE_EAPOL_KEY = 3,
    IEEE802_1X_TYPE_EAPOL_ENCAPSULATED_ASF_ALERT = 4
};

/* Message Type */
enum wps_msg_type {
    WPS_M1 = 0x04,
    WPS_M2 = 0x05,
    WPS_M2D = 0x06,
    WPS_M3 = 0x07,
    WPS_M4 = 0x08,
    WPS_M5 = 0x09,
    WPS_M6 = 0x0a,
    WPS_M7 = 0x0b,
    WPS_M8 = 0x0c,
    WPS_WSC_ACK = 0x0d,
    WPS_WSC_NACK = 0x0e,
    WPS_WSC_DONE = 0x0f
};

/*
 * EAP Method Types as allocated by IANA:
 * http://www.iana.org/assignments/eap-numbers
 */
enum eap_type {
    EAP_TYPE_NONE = 0,
    EAP_TYPE_IDENTITY = 1 /* RFC 3748 */,
    EAP_TYPE_NOTIFICATION = 2 /* RFC 3748 */,
    EAP_TYPE_NAK = 3 /* Response only, RFC 3748 */,
    EAP_TYPE_MD5 = 4, /* RFC 3748 */
    EAP_TYPE_OTP = 5 /* RFC 3748 */,
    EAP_TYPE_GTC = 6, /* RFC 3748 */
    EAP_TYPE_TLS = 13 /* RFC 2716 */,
    EAP_TYPE_LEAP = 17 /* Cisco proprietary */,
    EAP_TYPE_SIM = 18 /* RFC 4186 */,
    EAP_TYPE_TTLS = 21 /* RFC 5281 */,
    EAP_TYPE_AKA = 23 /* RFC 4187 */,
    EAP_TYPE_PEAP = 25 /* draft-josefsson-pppext-eap-tls-eap-06.txt */,
    EAP_TYPE_MSCHAPV2 = 26 /* draft-kamath-pppext-eap-mschapv2-00.txt */,
    EAP_TYPE_TLV = 33 /* draft-josefsson-pppext-eap-tls-eap-07.txt */,
    EAP_TYPE_TNC = 38 /* TNC IF-T v1.0-r3; note: tentative assignment;
               * type 38 has previously been allocated for
               * EAP-HTTP Digest, (funk.com) */,
    EAP_TYPE_FAST = 43 /* RFC 4851 */,
    EAP_TYPE_PAX = 46 /* RFC 4746 */,
    EAP_TYPE_PSK = 47 /* RFC 4764 */,
    EAP_TYPE_SAKE = 48 /* RFC 4763 */,
    EAP_TYPE_IKEV2 = 49 /* RFC 5106 */,
    EAP_TYPE_AKA_PRIME = 50 /* RFC 5448 */,
    EAP_TYPE_GPSK = 51 /* RFC 5433 */,
    EAP_TYPE_PWD = 52 /* RFC 5931 */,
    EAP_TYPE_EKE = 53 /* RFC 6124 */,
    EAP_TYPE_TEAP = 55 /* RFC 7170 */,
    EAP_TYPE_EXPANDED = 254 /* RFC 3748 */
};

/* SMI Network Management Private Enterprise Code for vendor specific types */
enum {
    EAP_VENDOR_IETF = 0,
    EAP_VENDOR_MICROSOFT = 0x000137 /* Microsoft */,
    EAP_VENDOR_WFA = 0x00372A /* Wi-Fi Alliance (moved to WBA) */,
    EAP_VENDOR_HOSTAP = 39068 /* hostapd/wpa_supplicant project */,
    EAP_VENDOR_WFA_NEW = 40808 /* Wi-Fi Alliance */
};

enum eap_code {
    EAP_CODE_REQUEST = 1,
    EAP_CODE_RESPONSE = 2,
    EAP_CODE_SUCCESS = 3,
    EAP_CODE_FAILURE = 4,
    EAP_CODE_INITIATE = 5,
    EAP_CODE_FINISH = 6,
};

enum {
    EAPOL_KEY_TYPE_RC4 = 1,
    EAPOL_KEY_TYPE_RSN = 2,
    EAPOL_KEY_TYPE_WPA = 254
};

struct eap_hdr {
    u8 code;
    u8 identifier;
    u16 length; /* including code and identifier */
    /* followed by length-4 octets of data */
} __packed;

struct ieee802_1x_hdr {
    u8 version;
    u8 type;
    u16 length;
    /* followed by length octets of data */
} __packed;

struct eapol_key {
    u8 type;
    /* Note: key_info, key_length, and key_data_length are unaligned */
    u8 key_info[2]; /* big endian */
    u8 key_length[2]; /* big endian */
    u8 replay_counter[WPA_REPLAY_COUNTER_LEN];
    u8 key_nonce[WPA_NONCE_LEN];
    u8 key_iv[16];
    u8 key_rsc[WPA_KEY_RSC_LEN];
    u8 key_id[8]; /* Reserved in IEEE 802.11i/RSN */
    /* variable length Key MIC field */
    /* big endian 2-octet Key Data Length field */
    /* followed by Key Data Length bytes of Key Data */
} __packed;

/* WAPI IE info */
struct wapi_hdr {
    u16 version;
    u8  type;
    u8  subtype;
    u16 reserved;
    u16 length;
    u16 seq_num;
    u8  frag_seq_num;
    u8  flag;
} __packed;

struct dhcp_header {
    __u8 op;
    __u8 htype;
    __u8 hlen;
    __u8 hops;
    __be32 xid;
    __be16 secs;
    __be16 flags;
    __be32 ciaddr;
    __be32 yiaddr;
    __be32 siaddr;
    __be32 giaddr;
    __u8 chaddr[16];
    __u8 sname[64];
    __u8 file[128];
    __be32 magic;
    __u8 options[];
} __packed;

struct dhcp_option {
    __u8 code;
    __u8 len;
    __u8 data[];
} __packed;

u32 aml_filter_sp_data_frame(const u8 *frame, int len, const struct aml_vif *aml_vif,
                             AML_SP_STATUS_E sp_status);
uint32_t aml_filter_sp_mgmt_frame(struct aml_vif *vif, u8 *buf, AML_SP_STATUS_E sp_status, u32 frame_len, u32 *len_diff, u64 cookie);
uint32_t aml_handle_action_frame(struct aml_vif *vif, u8 *buf, AML_SP_STATUS_E sp_status, u32 frame_len, u32 *len_diff, u64 cookie);

#endif /* _AML_PKT_FILTER_H_ */
