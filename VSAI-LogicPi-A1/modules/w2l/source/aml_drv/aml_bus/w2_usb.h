/* SPDX-License-Identifier: GPL-2.0 */
/*
* Copyright (C) 202X Original Author (retain original author information)
* Copyright (C) 202X Amlogic, Inc. All rights reserved.
*
* Description:
*/
#ifndef _W2_USB_H_
#define _W2_USB_H_

#include "usb_common.h"

#define W2_PRODUCT  0x4c55
#define W2_VENDOR  0x414D

#define W2u_VENDOR_AMLOGIC_EFUSE 0x1B8E
#define W2u_PRODUCT_A_AMLOGIC_EFUSE 0x0601
#define W2u_PRODUCT_B_AMLOGIC_EFUSE 0x0641
#define W2lu_W265U2M_PRODUCT_A_AMLOGIC_EFUSE 0x0801
#define W2lu_W265U2_PRODUCT_A_AMLOGIC_EFUSE 0x0809
#define W2lu_W255U1_PRODUCT_A_AMLOGIC_EFUSE 0x0811
#define W2lu_W265U2M_PRODUCT_B_AMLOGIC_EFUSE 0x0841
#define W2lu_W265U2_PRODUCT_B_AMLOGIC_EFUSE 0x0849
#define W2lu_W255U1_PRODUCT_B_AMLOGIC_EFUSE 0x0851

/*auc--amlogic usb common*/
struct auc_hif_ops {
    int (*hi_read_tx_cfm)(unsigned char* buf, unsigned int len, unsigned int *actual_length);

    void (*hi_write_word)(unsigned int addr,unsigned int data, unsigned int ep);
    unsigned int (*hi_read_word)(unsigned int addr, unsigned int ep);
    void (*hi_write_sram)(const unsigned char* buf, unsigned char* addr, unsigned int len, unsigned int ep);
    void (*hi_read_sram)(unsigned char* buf, unsigned char* addr, unsigned int len, unsigned int ep);

    int (*hi_rx_buffer_read)(void *buf, u32 addr, unsigned int len, unsigned int ep);

    /*bt use*/
    void (*hi_write_word_for_bt)(unsigned int addr,unsigned int data, unsigned int ep);
    unsigned int (*hi_read_word_for_bt)(unsigned int addr, unsigned int ep);
    void (*hi_write_sram_for_bt)(unsigned char* buf, unsigned char* addr, unsigned int len, unsigned int ep);
    void (*hi_read_sram_for_bt)(unsigned char* buf, unsigned char* addr, unsigned int len, unsigned int ep);

    int (*hi_enable_scat)(void);
    void (*hi_cleanup_scat)(void);
    struct amlw_hif_scatter_req * (*hi_get_scatreq)(void);
    int (*hi_scat_rw)(struct scatterlist *sg_list, unsigned int sg_num, unsigned int blkcnt,
        unsigned char func_num, unsigned int addr, unsigned char write);

    int (*hi_send_frame)(struct amlw_hif_scatter_req *scat_req);
    void (*hi_rcv_frame)(unsigned char* buf, unsigned char* addr, unsigned long len);
};

int auc_cmd_rxrd_set(u32 rxrd);

int wifi_fw_download(char *firmware_filename);
int start_wifi(void);
int aml_usb_download_suspend_or_rf_fw(unsigned char fw_type, unsigned int fw_download_timeout);
unsigned char aml_usb_download_host_cmd_fw(unsigned char cmd_index);

void auc_write_word_by_ep_for_wifi(unsigned int addr,unsigned int data, unsigned int ep);
unsigned int auc_read_word_by_ep_for_wifi(unsigned int addr, unsigned int ep);
unsigned int auc_read_word_by_ep_for_bt(unsigned int addr, unsigned int ep);
#endif
