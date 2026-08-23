/* SPDX-License-Identifier: GPL-2.0 */
/*
* Copyright (C) 202X Original Author (retain original author information)
* Copyright (C) 202X Amlogic, Inc. All rights reserved.
*
* Description:
*/
#ifndef _AML_CSI_H_
#define _AML_CSI_H_

#include <linux/mutex.h>
#include <linux/wait.h>
#include <linux/workqueue.h>

enum {
    AML_CSI_FUNC_START = 0xFF01,
    AML_CSI_FUNC_STOP,
    AML_CSI_DATA_UPLOAD,
    AML_CSI_LINK_CHANGE,
    AML_CSI_LINK_INFO,
};

struct aml_csi_nl_info {
    struct sock * fw_csi_sock;
    int user_pid;
    int enable;
};

struct csi_nl_msg_info {
    int msg_type;
    int msg_len;
};

int aml_csi_nl_init(void);
void aml_csi_nl_destroy(void);
int aml_send_csi_data_to_user(char *pbuf, uint16_t len, int msg_type);
int aml_csi_ready_ind(struct aml_hw *aml_hw, struct aml_cmd *cmd, struct ipc_e2a_msg *msg);

int aml_get_csi_debug_info(struct net_device *dev, union iwreq_data *wrqu, char *extra);
int aml_get_csi_link_info(struct net_device *dev, union iwreq_data *wrqu);

extern uint32_t g_csi_upload_num;
extern uint32_t g_abnormal_csi_num;
extern struct csi_link_info_ind g_csi_link_info;
extern struct aml_csi_nl_info g_csi_nl_info;

#endif /* _AML_CSI_H_ */
