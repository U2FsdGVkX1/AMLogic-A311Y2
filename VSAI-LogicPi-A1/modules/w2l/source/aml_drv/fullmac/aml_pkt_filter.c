/**
 ******************************************************************************
 *
 * @file aml_pkt_filter.c
 *
 * Copyright (C) Amlogic 2012-2021
 *
 ******************************************************************************
 */

#define AML_MODULE   PKT

#include <net/ip.h>
#include <net/sock.h>
#include <linux/version.h>
#include <linux/byteorder/generic.h>
#include "aml_events.h"
#include "aml_log.h"
#include "aml_pkt_filter.h"
#include "aml_roku_custom.h"

static const char *sp_frame_status_trace[] = {
    [SP_STATUS_TX_START] = "[SP FRAME TX]",
    [SP_STATUS_RX] = "[SP FRAME RX]",
    [SP_STATUS_TX_SUC] = "[SP FRAME TX SUC]",
    [SP_STATUS_TX_FAIL] = "[SP FRAME TX FAIL]",
};

static const char *dpp_pub_action_trace_name(int type)
{
    /*Table 31-DPP Public Action Frame Type [easy connect v2.0]*/
    static const char *dpp_pub_action_trace[] = {
        "Authentication Request",
        "Authentication Response",
        "Authentication Confirm",
        "Reserved",
        "Reserved",
        "Peer Discovery Request",
        "Peer Discovery Response",
        "PKEX Version 1 Exchange Request",
        "PKEX Exchange Response",
        "PKEX Commit-Reveal Request",
        "PKEX Commit-Reveal Response",
        "Configuration Result",
        "Connection Status Result",
        "Presence Announcement",
        "Reconfiguration Announcement",
        "Reconfiguration Authentication Request",
        "Reconfiguration Authentication Response",
        "Reconfiguration Authentication Confirm",
        "PKEX Exchange Request"
    };
    return type < ARRAY_SIZE(dpp_pub_action_trace) ? dpp_pub_action_trace[type] : "dpp_pub NULL";
}

static const char *eap_type2name[] = {
    [EAP_TYPE_NONE]         = "EAP NONE",
    [EAP_TYPE_NOTIFICATION] = "EAP NOTIFICATION",
    [EAP_TYPE_NAK]          = "EAP NAK",
    [EAP_TYPE_MD5]          = "EAP MD5",
    [EAP_TYPE_OTP]          = "EAP OTP",
    [EAP_TYPE_GTC]          = "EAP GTC",
    [EAP_TYPE_TLS]          = "EAP TLS",
    [EAP_TYPE_LEAP]         = "EAP LEAP",
    [EAP_TYPE_SIM]          = "EAP SIM",
    [EAP_TYPE_TTLS]         = "EAP TTLS",
    [EAP_TYPE_AKA]          = "EAP AKA",
    [EAP_TYPE_PEAP]         = "EAP PEAP",
    [EAP_TYPE_MSCHAPV2]     = "EAP MSCHAPV2",
    [EAP_TYPE_TLV]          = "EAP TLV",
    [EAP_TYPE_TNC]          = "EAP INC",
    [EAP_TYPE_FAST]         = "EAP FAST",
    [EAP_TYPE_PAX]          = "EAP PAX",
    [EAP_TYPE_PSK]          = "EAP PSK",
    [EAP_TYPE_SAKE]         = "EAP SAKE",
    [EAP_TYPE_IKEV2]        = "EAP IKEV2",
    [EAP_TYPE_AKA_PRIME]    = "EAP AKA PRIME",
    [EAP_TYPE_GPSK]         = "EAP GPSK",
    [EAP_TYPE_PWD]          = "EAP PWD",
    [EAP_TYPE_EKE]          = "EAP EKE",
    [EAP_TYPE_TEAP]         = "EAP TEAP",
};

static const char *wps_msg2name[] = {
    [WPS_M1]         = "WPS M1",
    [WPS_M2]         = "WPS M2",
    [WPS_M2D]        = "WPS M2D",
    [WPS_M3]         = "WPS M3",
    [WPS_M4]         = "WPS M4",
    [WPS_M5]         = "WPS M5",
    [WPS_M6]         = "WPS M6",
    [WPS_M7]         = "WPS M7",
    [WPS_M8]         = "WPS M8",
    [WPS_WSC_ACK]    = "WPS WSC ACK",
    [WPS_WSC_NACK]   = "WPS WSC NACK",
    [WPS_WSC_DONE]   = "WPS WSC DONE",
};

static inline u32 aml_get_be16(const u8 *a)
{
    return (a[0] << 8) | a[1];
}

static inline u32 aml_get_be24(const u8 *a)
{
    return (a[0] << 16) | (a[1] << 8) | a[2];
}

static inline u32 aml_get_be32(const u8 *a)
{
    return (a[0] << 24) | (a[1] << 16) | (a[2] << 8) | a[3];
}

static inline u32 aml_get_le16(const u8 *a)
{
    return (a[1] << 8) | a[0];
}

static inline u32 aml_get_le24(const u8 *a)
{
    return (a[2] << 16) | (a[1] << 8) | a[0];
}

static inline u32 aml_get_le32(const u8 *a)
{
    return (a[3] << 24) | (a[2] << 16) | (a[1] << 8) | a[0];
}

static const char *aml_dhcp_message_type_to_str(__u8 type)
{
    switch (type) {
        case 1:
            return "DISCOVER";

        case 2:
            return "OFFER";

        case 3:
            return "REQUEST";

        case 4:
            return "DECLINE";

        case 5:
            return "ACK";

        case 6:
            return "NAK";

        case 7:
            return "RELEASE";

        case 8:
            return "INFORM";

        default:
            return "UNKNOWN";
    }
}

static const char *aml_wps_attr2str(u8 *attr, u16 attr_len)
{
    u16 type, len;
    int i = 0;

    /* TLV format parse, ensure read type + len is 4 bytes */
    while (i + 4 <= attr_len) {
        type = aml_get_be16(&attr[i]);
        i += 2;
        len = aml_get_be16(&attr[i]);
        i += 2;

        /* check for int overflow and valid TLV length */
        if (len > attr_len || i + len > attr_len) {
            AML_WARN("invalid TLV length: %u (max %u)\n", len, attr_len - i);
            return "WPS INVALID";
        }

        if (type == ATTR_MSG_TYPE) {
            u8 msg_type = attr[i];

            if (len < 1) {
                AML_WARN("empty WPS message type attribute\n");
                return "WPS INVALID";
            }

            if (msg_type >= WPS_M1 && msg_type <= WPS_WSC_DONE) {
                return wps_msg2name[msg_type];
            }
            else {
                AML_WARN("invalid WPS message type=%d\n", msg_type);
                return "WPS INVALID";
            }
        }

        i += len;
    }

    return "WPS N/A";
}

static const char *aml_parse_expanded_type(u8 *exp_data, u32 eap_len)
{
    u8 *pos = exp_data;
    int exp_vendor;
    u32 exp_type;
    exp_vendor = aml_get_be24(pos);
    pos += 3;
    exp_type = aml_get_be32(pos);
    pos += 4;

    if (exp_vendor != EAP_VENDOR_WFA || exp_type != 1) {
        return "WSC NOSUPP";
    }

    /* parse EAP-EXT WSC opcode */
    if (*pos == WSC_MSG) {
        /* WPS ATTR length, excluded
         * Expanded Type, vendor id, vendor type, opcode, flags */
        u32 attr_len = eap_len - 10;
        /* position to WSC ATTR TLV format */
        return aml_wps_attr2str(pos + 2, attr_len);
    }
    else if (*pos == WSC_START) {
        return "WSC Start";
    }
    else if (*pos == WSC_ACK) {
        return "WSC Ack";
    }
    else if (*pos == WSC_NACK) {
        return "WSC NACK";
    }
    else if (*pos == WSC_DONE) {
        return "WSC Done";
    }

    return "WSC N/A";
}

static void aml_parse_eapol(u8 *eapol, u16 eapol_len, char *str, u32 strlen)
{
    struct ieee802_1x_hdr *i8021x_hdr = (struct ieee802_1x_hdr *)eapol;
    u16 len = 0;

    if (i8021x_hdr->type == IEEE802_1X_TYPE_EAP_PACKET) {
        struct eap_hdr *eap = (struct eap_hdr *)(i8021x_hdr + 1);
        u8 *eap_type = (u8 *)(eap + 1);
        u16 eap_len = eapol_len - sizeof(struct eap_hdr);

        if (eap->code == EAP_CODE_REQUEST) {
            len = scnprintf(str, strlen, "EAP REQUEST ");
        }
        else if (eap->code == EAP_CODE_RESPONSE) {
            len = scnprintf(str, strlen, "EAP RESPONSE ");
        }
        else if (eap->code == EAP_CODE_SUCCESS) {
            len = scnprintf(str, strlen, "EAP SUCCESS");
        }
        else if (eap->code == EAP_CODE_FAILURE) {
            len = scnprintf(str, strlen, "EAP FAILURE");
        }
        else if (eap->code == EAP_CODE_INITIATE) {
            len = scnprintf(str, strlen, "EAP INITIATE");
        }
        else if (eap->code == EAP_CODE_FINISH) {
            len = scnprintf(str, strlen, "EAP FINISH");
        }

        if (eap->code == EAP_CODE_REQUEST || eap->code == EAP_CODE_RESPONSE) {
            if (*eap_type == EAP_TYPE_IDENTITY) {
                len += scnprintf(&str[len], strlen - len, "Identity");
            }
            else if (*eap_type == EAP_TYPE_EXPANDED) {
                len += scnprintf(&str[len], strlen - len, "Expanded Type - %s",
                                 aml_parse_expanded_type(eap_type + 1, eap_len));
            }
            else {
                len += scnprintf(&str[len], strlen - len, "%s",
                                 eap_type2name[*eap_type]);
            }
        }
    }
    else if (i8021x_hdr->type == IEEE802_1X_TYPE_EAPOL_KEY) {
        struct eapol_key *key = (struct eapol_key *)(i8021x_hdr + 1);
        u16 key_info;

        if (key->type == EAPOL_KEY_TYPE_WPA) {
            len = scnprintf(str, strlen, "WPA ");
        }
        else if (key->type == EAPOL_KEY_TYPE_RSN) {
            len = scnprintf(str, strlen, "WPA2/RSN ");
        }

        key_info = aml_get_be16(key->key_info);

        if (key_info & WPA_KEY_INFO_KEY_TYPE) {
            if (key_info & WPA_KEY_INFO_ACK) {
                if (key_info & (WPA_KEY_INFO_MIC | WPA_KEY_INFO_ENCR_KEY_DATA)) {
                    len += scnprintf(&str[len], strlen - len, "EAPOL Key(3/4)");
                }
                else {
                    len += scnprintf(&str[len], strlen - len, "EAPOL Key(1/4)");
                }
            }
            else {
                if (key_info & WPA_KEY_INFO_SECURE) {
                    len += scnprintf(&str[len], strlen - len, "EAPOL Key(4/4)");
                }
                else {
                    len += scnprintf(&str[len], strlen - len, "EAPOL Key(2/4)");
                }
            }
        }
        else {
            if (key_info & WPA_KEY_INFO_ACK) {
                len += scnprintf(&str[len], strlen - len, "EAPOL Group Key(1/2)");
            }
            else {
                len += scnprintf(&str[len], strlen - len, "EAPOL Group Key(2/2)");
            }
        }
    }
    else if (i8021x_hdr->type == IEEE802_1X_TYPE_EAPOL_START) {
        len = scnprintf(str, strlen, "EAPOL START");
    }
    else if (i8021x_hdr->type == IEEE802_1X_TYPE_EAPOL_LOGOFF) {
        len = scnprintf(str, strlen, "EAPOL LOGOFF");
    }
    else if (i8021x_hdr->type == IEEE802_1X_TYPE_EAPOL_ENCAPSULATED_ASF_ALERT) {
        len = scnprintf(str, strlen, "EAPOL ENCAPSULATED ASF ALERT");
    }
    else {
        len = scnprintf(str, strlen, "EAPOL N/A");
    }

    str[len] = '\0';
}

static const char *aml_process_dhcp_options(const __u8 *options, int options_len)
{
    const __u8 *ptr = options;
    const __u8 *end = options + options_len;

    while (ptr < end) {
        struct dhcp_option *opt = (struct dhcp_option *)ptr;

        if (opt->code == 255) {
            break;
        }

        if (opt->code == 0) {
            ptr++;
            continue;
        }

        if (ptr + offsetof(struct dhcp_option, data) > end) {
            break;
        }

        if (ptr + offsetof(struct dhcp_option, data) + opt->len > end) {
            break;
        }

        switch (opt->code) {
            case DHCP_OPTION_TYPE:
                return aml_dhcp_message_type_to_str(opt->data[0]);

            default:
                break;
        }

        ptr += offsetof(struct dhcp_option, data) + opt->len;
    }

    return "DHCP N/A";
}

static void aml_parse_dhcp(const u8 *frame, char *str, u32 strlen)
{
    struct iphdr *iph;
    struct udphdr *udph;
    struct dhcp_header *dhcph;
    unsigned int iphdr_len;
    unsigned int udp_len;
    int options_len;
    u16 len = 0;
    iph = (struct iphdr *)(frame + ETH_HLEN);
    iphdr_len = iph->ihl * 4;
    udph = (struct udphdr *)(frame + ETH_HLEN + iphdr_len);
    dhcph = (struct dhcp_header *)(frame + ETH_HLEN + iphdr_len + sizeof(struct udphdr));

    if (dhcph->magic != htonl(DHCP_MAGIC)) {
        return;
    }

    udp_len = ntohs(udph->len);
    options_len = udp_len - sizeof(struct udphdr) - offsetof(struct dhcp_header, options);

    if (options_len < 0) {
        return;
    }

    len += scnprintf(&str[len], strlen - len,
                     udph->dest == htons(DHCP_SERVER_PORT) ? "C->S " : "S->C ");

    if (options_len > 0) {
        const __u8 *options = (const __u8 *)dhcph + offsetof(struct dhcp_header, options);
        len += scnprintf(&str[len], strlen - len, "options:%s", aml_process_dhcp_options(options, options_len));
    }

    str[len] = '\0';
    return;
}

u32 aml_filter_sp_data_frame(const u8 *frame, int len, const struct aml_vif *aml_vif,
                             AML_SP_STATUS_E sp_status)
{
    static const struct aml_vif vif_dummy = { .vif_index = 0x1f /* magic vif index */ };
    const struct ethhdr *ethhdr = NULL;
    const void *nethdr;
    u8 net_prot = 0;
    u32 pkt_types = 0;

    if (!aml_vif) {
        aml_vif = &vif_dummy;
    }

    if (!frame) {
        return pkt_types;
    }

    ethhdr = (const struct ethhdr *)frame;

    //filter eapol
    if (ethhdr->h_proto == htons(ETH_P_PAE)) {
#define EAPOL_STRLEN   128
        char str[EAPOL_STRLEN];
        u8 *eapol = (u8 *)(ethhdr + 1);
        u32 eapol_len = len - sizeof(struct ethhdr);
        aml_parse_eapol(eapol, eapol_len, str, EAPOL_STRLEN);
        AML_WARN("%s[%d] %s\n", sp_frame_status_trace[sp_status], aml_vif->vif_index, str);
        return BIT(AML_PKT_EAPOL);
    }

    //filter arp
    if (ethhdr->h_proto == htons(ETH_P_ARP)) {
        const struct arphdr *arphdr = (const void *)(ethhdr + 1);
        const struct {  /* Ethernet ARP payload */
            unsigned char sha[ETH_ALEN]; /* sender hardware address  */
            unsigned char sip[4];        /* sender IP address        */
            unsigned char tha[ETH_ALEN]; /* target hardware address  */
            unsigned char tip[4];        /* target IP address        */
        } *ar = (const void *)(arphdr + 1);
        const u16 op = ntohs(arphdr->ar_op);
        const char *op_name = "???";
        pkt_types |= BIT(AML_PKT_ARP);

        switch (op) {
            case ARPOP_REQUEST:
                pkt_types |= BIT(AML_PKT_ARP_REQ);
                op_name = "req";
                break;

            case ARPOP_REPLY:
                pkt_types |= BIT(AML_PKT_ARP_REPLY);
                op_name = "rsp";
                break;

            default:
                op_name = "???";
                break;
        }

        if (aml_vif == &vif_dummy || sp_status != SP_STATUS_RX ||
                aml_vif->vif_index != AML_STA_VIF_IDX ||
                memcmp(ar->tip, &aml_vif->ipv4_addr, IPV4_ADDR_LEN) == 0) {
            AML_WARN("%s[%d] ARP %s(0x%x) sender:[%pM %pI4] receiver:[%pM %pI4]\n",
                     sp_frame_status_trace[sp_status], aml_vif->vif_index, op_name, op,
                     ar->sha, ar->sip, ar->tha, ar->tip);
        }

        return pkt_types;
    }

    if (ethhdr->h_proto == htons(ETH_P_IPV6)) {
        const struct ipv6hdr *ipv6hdr = (const struct ipv6hdr *)(ethhdr + 1);
        pkt_types |= BIT(AML_PKT_IPV6);
        net_prot = ipv6hdr->nexthdr;
        nethdr = (const void *)(ipv6hdr + 1);
    }
    else if (ethhdr->h_proto == htons(ETH_P_IP)) {
        const struct iphdr *iphdr = (const struct iphdr *)(ethhdr + 1);
        pkt_types |= BIT(AML_PKT_IP);
        net_prot = iphdr->protocol;
        nethdr = (const void *)iphdr + (iphdr->ihl << 2);
    }
    else {
        return pkt_types;
    }

    switch (net_prot) {
        case IPPROTO_ICMP:
            pkt_types |= BIT(AML_PKT_ICMP);
            break;

        case IPPROTO_TCP:
            pkt_types |= BIT(AML_PKT_TCP);

            if (aml_filter_rtsp_frame(aml_vif, len, frame, sp_status)) {
                pkt_types |= BIT(AML_PKT_RTSP);
            }

            break;

        case IPPROTO_UDP: {
#define DHCP_STRLEN   128
            char str[DHCP_STRLEN];
            u16 sport = ntohs(((const struct udphdr *)nethdr)->source);
            pkt_types |= BIT(AML_PKT_UDP);

            if ((pkt_types & BIT(AML_PKT_IP)) && (sport == DHCP_SP_V4 || sport == DHCP_CP_V4)) {
                pkt_types |= BIT(AML_PKT_DHCP);
                aml_parse_dhcp(frame, str, DHCP_STRLEN);
            }

            if ((pkt_types & BIT(AML_PKT_IPV6)) && (sport == DHCP_SP_V6 || sport == DHCP_CP_V6)) {
                pkt_types |= BIT(AML_PKT_DHCP_V6);
                scnprintf(str, DHCP_STRLEN, "v6");
            }

            if (pkt_types & (BIT(AML_PKT_DHCP) | BIT(AML_PKT_DHCP_V6))) {
                AML_WARN("%s[%d] DHCP %s\n", sp_frame_status_trace[sp_status], aml_vif->vif_index, str);
            }

            break;
        }

        default:
            break;
    }

    return pkt_types;
}

uint32_t aml_handle_action_frame(struct aml_vif *vif, u8 *buf, AML_SP_STATUS_E sp_status,
                                 u32 frame_len, u32 *len_diff, u64 cookie)
{
    u32 offset = 0;
    u8 str[140];
    u8 *p = str;
    uint32_t ret = 0;
    u8 category;
    u8 action_code;
    u8 oui_type;
    u8 oui_subtype;
    offset += sprintf(p + offset, sp_frame_status_trace[sp_status]);
    offset += sprintf(p + offset, "vif:%d ", vif->vif_index);
    category = *(buf + CATEGORY_OFFSET);

    if (category == PUBLIC_ACTION) {
        action_code = *(buf + ACTION_CODE_OFFSET);
        oui_type = *(buf + OUI_TYPE_OFFSET);
        oui_subtype = *(buf + OUI_SUBTYPE_OFFSET);

        if ((action_code == ACTION_CODE_VENDOR)
                && (*(buf + OUI_OFFSET) == 0x50)
                && (*(buf + OUI_OFFSET + 1) == 0x6f)
                && (*(buf + OUI_OFFSET + 2) == 0x9a)) {
            if (oui_type == OUI_TYPE_P2P) {
                offset += snprintf(p + offset, sizeof(str) - offset, "PUB ACT->%-24s ", p2p_pub_action_trace_name(oui_subtype));

                if (cookie) {
                    offset += snprintf(p + offset, sizeof(str) - offset, " 0x%llx ", cookie);
                }

                ret |= AML_P2P_ACTION_FRAME;

                //P2P_ACTION_GO_NEG_RSP & P2P_ACTION_GO_NEG_CFM & P2P_ACTION_INVIT_RSP:need sw retry
                if ((oui_subtype == P2P_ACTION_GO_NEG_RSP)
                        || (oui_subtype == P2P_ACTION_GO_NEG_CFM)
                        || (oui_subtype == P2P_ACTION_INVIT_RSP)
                        || (oui_subtype == P2P_ACTION_INVIT_REQ)
                        || (oui_subtype == P2P_ACTION_GO_NEG_REQ)) {
                    ret |= AML_SP_FRAME;

                    if ((oui_subtype == P2P_ACTION_GO_NEG_CFM) || (oui_subtype == P2P_ACTION_INVIT_RSP)) {
                        ret |= AML_MUST_TX_SUC;
                    }
                }

                if (oui_subtype == P2P_ACTION_GO_NEG_REQ) {
                    vif->p2p_negotiation_state = P2P_NEG_SEND_NEG_REQ;
                }
                else if (oui_subtype == P2P_ACTION_GO_NEG_RSP) {
                    vif->p2p_negotiation_state = P2P_NEG_SEND_NEG_RSP;
                }
                else if (oui_subtype == P2P_ACTION_GO_NEG_CFM) {
                    vif->p2p_negotiation_state = P2P_NEG_SEND_NEG_CFM;
                }

                if ((oui_subtype != P2P_ACTION_GO_NEG_CFM) && (oui_subtype != P2P_ACTION_INVIT_RSP)) {
                    ret |= AML_REPORT_NO_ACKED;
                }

#ifdef DRV_P2P_SCC_MODE

                if ((sp_status == SP_STATUS_TX_START) && (len_diff != NULL)) {
                    if ((oui_subtype == P2P_ACTION_GO_NEG_REQ) || (oui_subtype == P2P_ACTION_INVIT_REQ)) {
                        AML_SCC_SET_P2P_PEER_5G_SUPPORT(false);    //rest 5g support flag
                    }

                    if ((oui_subtype == P2P_ACTION_GO_NEG_REQ) || (oui_subtype == P2P_ACTION_GO_NEG_RSP) || (oui_subtype == P2P_ACTION_INVIT_REQ)) {
                        struct aml_vif *sta_vif ;
                        sta_vif = vif->aml_hw->vif_table[0];

                        if (sta_vif && sta_vif->sta.ap && (sta_vif->sta.ap->valid)) {
                            struct cfg80211_chan_def target_chdef;
                            target_chdef = vif->aml_hw->chanctx_table[sta_vif->ch_index].chan_def;

                            if ((target_chdef.chan->flags & IEEE80211_CHAN_RADAR)) {
                                AML_WARN("dfs chan, skip change ie");
                            }
                            else {
                                if (frame_len > MAX_P2P_SAVE_LEN) {
                                    AML_WARN("[P2P SCC] p2p frame len error:%d", frame_len);
                                }
                                else if (g_scc_p2p_len_before) {
                                    AML_WARN("[P2P SCC] p2p pre frame not cfm:%d", g_scc_p2p_len_before);
                                }
                                else {
                                    AML_RLMT_WARN("[P2P SCC] p2p channel to:%d", aml_ieee80211_freq_to_chan(target_chdef.chan->center_freq, target_chdef.chan->band));
                                    AML_SCC_SAVE_P2P_ACTION_FRAME(buf, frame_len);
                                    AML_SCC_SAVE_P2P_ACTION_LEN(frame_len);
                                    aml_change_p2p_chanlist(vif, buf, frame_len, len_diff, target_chdef);
                                    aml_change_p2p_operchan(vif, buf, frame_len, target_chdef);
                                    AML_SCC_SAVE_P2P_ACTION_LEN_DIFF(*len_diff);
                                }
                            }
                        }
                    }
                }

                if (((sp_status == SP_STATUS_TX_SUC) || (sp_status == SP_STATUS_TX_FAIL)) && (len_diff != NULL)) {
                    if ((oui_subtype == P2P_ACTION_GO_NEG_REQ) || (oui_subtype == P2P_ACTION_GO_NEG_RSP) || (oui_subtype == P2P_ACTION_INVIT_REQ) || (oui_subtype == P2P_ACTION_INVIT_RSP)) {
                        aml_scc_p2p_action_restore(buf, len_diff);
                    }
                }

#endif
#if 0    //code for change p2p go intent

                if ((oui_subtype == P2P_ACTION_GO_NEG_REQ) || (oui_subtype == P2P_ACTION_GO_NEG_RSP)) {
                    aml_change_p2p_intent(vif, buf, frame_len, frame_len_offset);
                }

#endif
            }
            else if (oui_type == OUI_TYPE_DPP) {
                u8 dpp_action_subtype = *(buf + DPP_PUBLIC_ACTION_SUBTYPE_OFFSET);
                offset += sprintf(p + offset, "DPP ACTION->%-48s ", dpp_pub_action_trace_name(dpp_action_subtype));
                ret |= AML_SP_FRAME | AML_DPP_ACTION_FRAME;

                if ((dpp_action_subtype == ACTION_DPP_CONNECT_STATUS_RESULT) || (dpp_action_subtype == ACTION_DPP_CONFIGURATION_RESULT)) {
                    ret |= AML_DPP_CONNECT_STATUS_RESULT_FRAME;
                }
            }
            else {
                offset += sprintf(p + offset, "oui type:%d ", oui_type);
            }
        }
        else if ((action_code == ACTION_GAS_INIT_REQ)
                 || (action_code == ACTION_GAS_INIT_RSP)) {
            u8 tag_len = *(buf + CATEGORY_OFFSET + 4);
            offset += sprintf(p + offset, "GAS ACTION,action code:%d ", action_code);
            ret |= AML_SP_FRAME | AML_GAS_ACTION_FRAME;

            if (action_code == ACTION_GAS_INIT_REQ) {
                ret |= AML_GAS_INIT_REQ_FRAME;
            }
            else if (action_code == ACTION_GAS_INIT_RSP) {
                ret |= AML_GAS_INIT_RSP_FRAME;
            }

            if ((tag_len >= 8)
                    && (*(buf + CATEGORY_OFFSET + 6) == 0xdd)
                    && (*(buf + CATEGORY_OFFSET + 7) == 0x05)
                    && (*(buf + CATEGORY_OFFSET + 8) == 0x50)
                    && (*(buf + CATEGORY_OFFSET + 9) == 0x6f)
                    && (*(buf + CATEGORY_OFFSET + 10) == 0x9a)
                    && (*(buf + CATEGORY_OFFSET + 11) == 0x1a)
                    && (*(buf + CATEGORY_OFFSET + 12) == 0x01)) {
                offset += sprintf(p + offset, "[DPP Configuration]");
                ret |= AML_DPP_ACTION_FRAME;
            }
        }
        else if (action_code == WLAN_PUB_ACTION_EXT_CHANSW_ANN) {
            struct ieee80211_mgmt *mgmt = (struct ieee80211_mgmt *)buf;
            ret |= AML_CSA_ACTION_FRAME;
            offset += snprintf(p + offset, sizeof(str) - offset, "csa action, da:%pM", mgmt->da);
        }
        else {
            offset += snprintf(p + offset, sizeof(str) - offset, "action code:%d ", action_code);
        }

        p[offset] = '\0';
        AML_WARN("%s\n", p);
    }
    else if ((category == VENDOR_SPEC)
             && (*(buf + CATEGORY_OFFSET + 1) == 0x50)
             && (*(buf + CATEGORY_OFFSET + 2) == 0x6f)
             && (*(buf + CATEGORY_OFFSET + 3) == 0x9a)) {
        oui_subtype = *(buf + CATEGORY_OFFSET + 5);
        offset += sprintf(p + offset, "P2P ACTION->%-24s ", p2p_action_trace_name(oui_subtype));
        p[offset] = '\0';
        AML_WARN("%s\n", p);
    }

    return ret;
}

uint32_t aml_filter_sp_mgmt_frame(struct aml_vif *vif, u8 *buf, AML_SP_STATUS_E sp_status, u32 frame_len, u32 *len_diff, u64 cookie)
{
    u32 subtype = (*buf) & IEEE80211_FCTL_STYPE;
    uint32_t ret = 0;
    u32 offset = 0;

    switch (subtype) {
        case IEEE80211_STYPE_ACTION:
            return aml_handle_action_frame(vif, buf, sp_status, frame_len, len_diff, cookie);

        case IEEE80211_STYPE_AUTH: {
            u8 str[100];
            u8 *p = str;
            u16 auth_algo = *(buf + AUTH_ALGO_OFFSET);
            ret |= AML_SP_FRAME;
            offset += sprintf(p + offset, sp_frame_status_trace[sp_status]);
            offset += sprintf(p + offset, "vif:%d, auth algo:%d ", vif->vif_index, auth_algo);

            if (sp_status == SP_STATUS_TX_START) {
                offset += sprintf(p + offset, "DA: %pM", ieee80211_get_DA((struct ieee80211_hdr *)buf));
            }
            else if (sp_status == SP_STATUS_RX) {
                offset += sprintf(p + offset, "SA: %pM", ieee80211_get_SA((struct ieee80211_hdr *)buf));
            }

            p[offset] = '\0';
            AML_WARN("%s\n", p);

            if ((AML_VIF_TYPE(vif) == NL80211_IFTYPE_STATION) && (vif->sta.flags & AML_STA_EXT_AUTH)) {
                u8 *data = buf + AUTH_ALGO_OFFSET;
                vif->sta.auth_status = (*(data + 4) | *(data + 5) << 8);
                AML_WARN("auth status %d\n", vif->sta.auth_status);
            }

            return ret;
        }

        case IEEE80211_STYPE_ASSOC_RESP: {
            u8 str[100];
            u8 *p = str;
            ret |= AML_SP_FRAME;
            offset += sprintf(p + offset, sp_frame_status_trace[sp_status]);
            offset += sprintf(p + offset, "vif:%d, ASSOC_RSP, DA: %pM",
                              vif->vif_index, ieee80211_get_DA((struct ieee80211_hdr *)buf));
            p[offset] = '\0';
            AML_WARN("%s\n", p);
            return ret;
        }

        case IEEE80211_STYPE_PROBE_RESP: {
            if (sp_status == SP_STATUS_TX_START) {
                aml_scc_save_probe_rsp(vif, (u8 *)buf, frame_len);
            }

            if ((vif->vif_index == AML_P2P_DEVICE_VIF_IDX) && (sp_status == SP_STATUS_TX_START)) {
                if (aml_get_p2p_ie_offset(buf, frame_len, MAC_SHORT_MAC_HDR_LEN + PROBE_RSP_HDR_LEN)) {
                    vif->aml_hw->wfd_present = true;
                }
            }

            return ret;
        }

        case IEEE80211_STYPE_PROBE_REQ: {
            if (((aml_partner_cust == ROKU_DONGLE_VER) || (aml_partner_cust == ROKU_TV_VER)) &&
                    (sp_status == SP_STATUS_RX) &&
                    (frame_len < ROKU_WFD_PROBE_LEN)) {
                u8 *sa = ieee80211_get_SA((struct ieee80211_hdr *)buf);

                if (cfg80211_find_vendor_ie(ROKU_PROBE_VENDOR_IE, ROKU_PROBE_VENDOR_TYPE,
                                            &buf[MAC_SHORT_MAC_HDR_LEN], frame_len - MAC_SHORT_MAC_HDR_LEN)) {
                    AML_WARN("ROKU probe req, len:%d sa:%pM", frame_len, sa);
                }

                if (frame_len < ROKU_LEGACY_PROBE_LEN) {
                    AML_WARN("legacy probe req, len:%d sa:%pM", frame_len, sa);
                }
            }

            return ret;
        }

        case IEEE80211_STYPE_DEAUTH: {
            struct ieee80211_mgmt *mgmt = (struct ieee80211_mgmt *)buf;
            u8 str[100];
            u8 *p = str;
            ret |= AML_SP_FRAME;
            offset += sprintf(p + offset, sp_frame_status_trace[sp_status]);
            offset += sprintf(p + offset, "vif:%d, DEAUTH, reason:%d", vif->vif_index, mgmt->u.deauth.reason_code);
            p[offset] = '\0';
            AML_WARN("%s\n", p);
            return ret;
        }

        case IEEE80211_STYPE_DISASSOC: {
            struct ieee80211_mgmt *mgmt = (struct ieee80211_mgmt *)buf;
            u8 str[100];
            u8 *p = str;
            ret |= AML_SP_FRAME;
            offset += sprintf(p + offset, sp_frame_status_trace[sp_status]);
            offset += sprintf(p + offset, "vif:%d, DISASSOC, reason:%d", vif->vif_index, mgmt->u.disassoc.reason_code);
            p[offset] = '\0';
            AML_WARN("%s\n", p);
            return ret;
        }

        default:
            break;
    }

    return ret;
}

