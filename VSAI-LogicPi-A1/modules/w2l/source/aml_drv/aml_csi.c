/* SPDX-License-Identifier: GPL-2.0 */
/*
* Copyright (C) 202X Original Author (retain original author information)
* Copyright (C) 202X Amlogic, Inc. All rights reserved.
*
* Description:
*/
#define AML_MODULE     CSI

#include <aml_defs.h>
#include <net/sock.h>
#include "aml_csi.h"
#include "aml_iwpriv_cmds.h"
#include "aml_wq.h"
#include "aml_msg_tx.h"

#define AML_CSI_NL_PROTOCOL (29)

struct aml_csi_nl_info g_csi_nl_info = {0};
struct csi_all_data_ind csi_all_data = {0};
struct csi_link_info_ind g_csi_link_info = {0};
uint32_t g_csi_upload_num = 0;
uint32_t g_abnormal_csi_num = 0;

static inline int __aml_csi_status_handle(struct aml_hw *aml_hw,
                                          struct csi_complex *csi_sp_data,
                                          size_t csi_sp_data_num,
                                          struct csi_fw_status_ind *csi_fw_status)
{
    u8_l csi_ready = csi_fw_status->csi_ready_flag;
    u32_l Hindex[4] = {0x11, 0x12, 0x21, 0x22};
    int i = 0, j = 0;
    u8_l k = 0;
    u32_l csi_abnormal_debug = 0;

    if (csi_ready) {
        hi_random_read(aml_hw, &csi_all_data.csi_com_data,
                       (0x00D00000 | csi_fw_status->csi_com_data_addr),
                       sizeof(struct csi_com_status_get_ind));
        hi_random_read(aml_hw, csi_sp_data,
                       (0x00D00000 | csi_fw_status->csi_sp_data_addr),
                       sizeof(struct csi_complex) * csi_sp_data_num);

        aml_send_set_csi_data_done(aml_hw);

        if (csi_all_data.csi_com_data.protocol_mode <= FORMATMOD_NON_HT_DUP_OFDM) {
            csi_all_data.csi_sp_data[0].csi_mode = Hindex[0];
            csi_all_data.csi_sp_data[0].data_len = csi_all_data.csi_com_data.tones_num;
            memcpy(csi_all_data.csi_sp_data[0].csi, &csi_sp_data[2],
                csi_all_data.csi_com_data.tones_num * sizeof(struct csi_complex));
        }
        else {
            for (k = 0; k < 4; k = k + 1) {
                csi_all_data.csi_sp_data[k].csi_mode = Hindex[k];
                csi_all_data.csi_sp_data[k].data_len = csi_all_data.csi_com_data.tones_num;
                BUG_ON(k * csi_all_data.csi_com_data.tones_num >= csi_sp_data_num);
                memcpy(csi_all_data.csi_sp_data[k].csi,
                    &csi_sp_data[k * csi_all_data.csi_com_data.tones_num],
                    csi_all_data.csi_com_data.tones_num * sizeof(struct csi_complex));
            }
        }

        g_csi_upload_num ++;
        AML_INFO("csi_upload_num:%u seq:%u protocol_mode:%u frame_type:0x%x tones_num:%u \n",
            g_csi_upload_num, csi_all_data.csi_com_data.sequence_no,
            csi_all_data.csi_com_data.protocol_mode, csi_all_data.csi_com_data.frame_type, csi_all_data.csi_com_data.tones_num);

        AML_DBG("time_stamp: %llu \n", csi_all_data.csi_com_data.time_stamp);
        AML_DBG("mac_ra:     %pM \n", csi_all_data.csi_com_data.mac_ra);
        AML_DBG("mac_ta:     %pM \n", csi_all_data.csi_com_data.mac_ta);
        AML_DBG("freq_band:  %u \n", csi_all_data.csi_com_data.frequency_band);
        AML_DBG("bw:         %u \n", csi_all_data.csi_com_data.bw);
        AML_DBG("rssi:       %d %d \n", csi_all_data.csi_com_data.rssi[0], csi_all_data.csi_com_data.rssi[1]);
        AML_DBG("snr:        %u \n", csi_all_data.csi_com_data.snr);
        AML_DBG("noise:      %u \n", csi_all_data.csi_com_data.noise);
        AML_DBG("phase_incr: %d \n", csi_all_data.csi_com_data.phase_incr);
        AML_DBG("pro_mode:   0x%x \n", csi_all_data.csi_com_data.protocol_mode);
        AML_DBG("frame_type: 0x%x \n", csi_all_data.csi_com_data.frame_type);
        AML_DBG("chain_num:  %u \n", csi_all_data.csi_com_data.chain_num);
        AML_DBG("tones_num:  %u \n", csi_all_data.csi_com_data.tones_num);
        AML_DBG("chan_index: %u \n", csi_all_data.csi_com_data.primary_channel_index);
        AML_DBG("phyerr:------- \n");
        AML_DBG("rate:       %u \n", csi_all_data.csi_com_data.rate);
        AML_DBG("agc_code:   %u %u \n", csi_all_data.csi_com_data.agc_code[0], csi_all_data.csi_com_data.agc_code[1]);
        AML_DBG("channel:    %u \n", csi_all_data.csi_com_data.channel);
        AML_DBG("packet_idx:--- \n");
        AML_DBG("nrx:        %u \n", csi_all_data.csi_com_data.nrx);
        AML_DBG("ntx:        %u \n", csi_all_data.csi_com_data.ntx);
        AML_DBG("perm:--------- \n");
        AML_DBG("csi_len:    %u \n", csi_all_data.csi_com_data.csi_len);
        AML_DBG("payload_len:---\n");
        AML_DBG("extra_info:--- \n");
        AML_DBG("sequence_no:%u \n", csi_all_data.csi_com_data.sequence_no);
        AML_DBG("csi_ready  :%u \n", csi_all_data.csi_com_data.csi_ready);
        AML_DBG("abnormal_csi:%x\n", csi_all_data.csi_com_data.csi_abnormal_info);

        for (i = 0; i < 4; i = i + 1)
        {
            for (j = 0; j < csi_all_data.csi_com_data.tones_num; j = j + 1)
            {
                AML_DBG("index [0x%02x] 0x%02x: i=0x%04x, q=0x%04x\n", Hindex[i], j,
                        csi_all_data.csi_sp_data[i].csi[j].i, csi_all_data.csi_sp_data[i].csi[j].q);
            }

            if (csi_all_data.csi_com_data.protocol_mode <= FORMATMOD_NON_HT_DUP_OFDM)
                break;
        }

        aml_send_csi_data_to_user((char *)&csi_all_data, sizeof(csi_all_data), AML_CSI_DATA_UPLOAD);
        memset(&csi_all_data, 0, sizeof(struct csi_all_data_ind));
    }
    else {
        csi_abnormal_debug = csi_fw_status->csi_abnormal_debug;

        if (csi_fw_status->csi_abnormal_info & BIT(0))
            g_abnormal_csi_num += 1;
        else if (csi_fw_status->csi_abnormal_info & BIT(1))
            g_abnormal_csi_num += BIT(16);
        AML_INFO("idle:%d, not_ready:%d protocol_mode:%u rate:%u frame_type:0x%x tones_num:%u", (g_abnormal_csi_num >> 16), (g_abnormal_csi_num & 0xffff),
                    (csi_abnormal_debug >> 24), (csi_abnormal_debug >> 16) & 0xff, (csi_abnormal_debug >> 8) & 0xff, (csi_abnormal_debug & 0xff));
    }

    return 0;
}

static int aml_csi_status_handle(struct aml_hw *aml_hw, void *ptr)
{
    int n = 1024;
    struct csi_complex *csi_sp_data = kzalloc(sizeof(struct csi_complex) * n, GFP_KERNEL);
    int ret;

    if (!csi_sp_data)
        return -ENOMEM;

    ret = __aml_csi_status_handle(aml_hw, csi_sp_data, n, (struct csi_fw_status_ind *)ptr);

    kfree(csi_sp_data);
    return ret;
}

int aml_get_csi_debug_info(struct net_device *dev, union iwreq_data *wrqu, char *extra)
{
    wrqu->data.length = scnprintf(extra, IW_PRIV_SIZE_MASK, "idle:%d, not_ready:%d, up_num:%d",
        (g_abnormal_csi_num >> 16), (g_abnormal_csi_num & 0xffff), g_csi_upload_num);
    wrqu->data.length++;
    return 0;
}

int aml_get_csi_link_info(struct net_device *dev, union iwreq_data *wrqu)
{
    unsigned int ret_copy = 0;
    struct csi_link_info_ind ind;

    memset(&ind, 0, sizeof(struct csi_link_info_ind));

    ind.bw = g_csi_link_info.bw;
    ind.nss = g_csi_link_info.nss;
    ind.protocol_mode = g_csi_link_info.protocol_mode;
    ind.link_state = g_csi_link_info.link_state;

    AML_INFO("link_info bw:%d nss:%d format:%d link_state:%d\n", ind.bw, ind.nss, ind.protocol_mode, ind.link_state);

    wrqu->data.length = sizeof(ind);
    ret_copy = copy_to_user(wrqu->data.pointer, (void*)&ind, wrqu->data.length);
    if (ret_copy != 0)
        AML_INFO("copy csi linkinfo to user failed, failed num:%d%%%d", ret_copy, wrqu->data.length);
    wrqu->data.length = 0;

    return 0;
}

int aml_csi_ready_ind(struct aml_hw *aml_hw,
                                         struct aml_cmd *cmd,
                                         struct ipc_e2a_msg *msg)
{
    struct csi_fw_status_ind *csi_fw_status = (struct csi_fw_status_ind *)msg->param;

    aml_wq_do_ptr(aml_csi_status_handle, aml_hw, csi_fw_status);

    return 0;
}

int aml_send_csi_data_to_user(char *pbuf, uint16_t len, int msg_type)
{
    struct sk_buff *nl_skb;
    struct nlmsghdr *nlh = NULL;   //msg head
    struct csi_nl_msg_info * nl_csi_info = NULL;
    int ret;
    static int seq_num = 0;
    int buf_len = NLMSG_SPACE(len + sizeof(struct csi_nl_msg_info));

    if (!g_csi_nl_info.fw_csi_sock || !g_csi_nl_info.user_pid ||
        !g_csi_nl_info.enable) {
        AML_ERR("kernel trace nl sock para invalid , can not upload msg to user\n");
        return -1;
    }
    //create sk_buff
    nl_skb = nlmsg_new(buf_len, GFP_ATOMIC);
    if (!nl_skb)
    {
        AML_ERR("netlink alloc failure\n");
        return -1;
    }

    /* build netlink msg head */
    nlh = nlmsg_put(nl_skb, 0, 0, AML_CSI_NL_PROTOCOL, buf_len, 0);
    if (nlh == NULL)
    {
        AML_ERR("nlmsg_put failure\n");
        nlmsg_free(nl_skb);
        /* coverity[leaked_storage] - nl_skb is freed */
        return -1;
    }
    NETLINK_CB(nl_skb).portid = 0;
    NETLINK_CB(nl_skb).dst_group = 0;
    nl_csi_info = (struct csi_nl_msg_info*)nlmsg_data(nlh);
    nl_csi_info->msg_len = len;
    nl_csi_info->msg_type = msg_type;
    nlh->nlmsg_seq = seq_num++;

    /* copy data and send it */
    if (pbuf) {
        memcpy(nlmsg_data(nlh) + sizeof(struct csi_nl_msg_info), pbuf, len);
    }
    ret = netlink_unicast(g_csi_nl_info.fw_csi_sock, nl_skb, g_csi_nl_info.user_pid, 0);

    AML_DBG("==== kernel upload csi data to user result: %d, seq: %d msg_type:0x%x\n", ret, seq_num - 1, msg_type);
    /* coverity[leaked_storage] - nl_skb will be freed later */
    return ret;
}

// recv msg handl function
static void aml_recv_csi_netlink(struct sk_buff *skb)
{
    struct nlmsghdr *nlh;
    struct csi_nl_msg_info * nl_log_info = NULL;
    nlh = nlmsg_hdr(skb); // get msg body
    AML_INFO("kernel rcv msg type: %d, pid: %d, len: %d, flag: %d, seq: %d\n",
        nlh->nlmsg_type, nlh->nlmsg_pid, nlh->nlmsg_len, nlh->nlmsg_flags, nlh->nlmsg_seq);
    AML_INFO("receive data from user process: %s\n", (char *)NLMSG_DATA(nlh));

    nl_log_info = (struct csi_nl_msg_info*)NLMSG_DATA(nlh);
    switch (nl_log_info->msg_type) {
        case AML_CSI_FUNC_START:
            g_csi_nl_info.user_pid = nlh->nlmsg_pid;
            g_csi_nl_info.enable = 1;
            AML_INFO("user space process (pid: %d) start recv csi data !!!!\n", g_csi_nl_info.user_pid);
            break;
        case AML_CSI_FUNC_STOP:
            g_csi_nl_info.enable = 0;
            AML_INFO("user space process (pid: %d) stop recv csi data !!!!\n", g_csi_nl_info.user_pid);
            break;
        case AML_CSI_LINK_INFO:
            aml_send_csi_data_to_user((char *)&g_csi_link_info, sizeof(g_csi_link_info), AML_CSI_LINK_INFO);
            AML_INFO("CSI_LINK_INFO bw: %d nss: %d mode: %d state: %d",
               g_csi_link_info.bw, g_csi_link_info.nss, g_csi_link_info.protocol_mode, g_csi_link_info.link_state);
            break;
        default:
            AML_ERR("unknown msg (0x%x) from user space process (pid: %d), ignore !!!!\n",
                nl_log_info->msg_type, g_csi_nl_info.user_pid);
            break;
    }

    return;
}

int aml_csi_nl_init(void)
{
    struct netlink_kernel_cfg cfg = {
        .input = aml_recv_csi_netlink,
    };
    memset(&g_csi_nl_info, 0, sizeof(struct aml_csi_nl_info));
    g_csi_nl_info.fw_csi_sock = netlink_kernel_create(&init_net, AML_CSI_NL_PROTOCOL, &cfg);
    if (!g_csi_nl_info.fw_csi_sock) {
        AML_ERR("aml csi netlink init failed");
        return -1;
    }

    AML_INFO("aml csi netlink init OK!\n");
    return 0;
}

void aml_csi_nl_destroy(void)
{
    if (g_csi_nl_info.fw_csi_sock) {
        netlink_kernel_release(g_csi_nl_info.fw_csi_sock);
    }
    AML_INFO("fw csi upload socket destroy!!!\n");

    return;
}

