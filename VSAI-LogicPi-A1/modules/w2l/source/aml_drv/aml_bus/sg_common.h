/* SPDX-License-Identifier: GPL-2.0 */
/*
* Copyright (C) 202X Original Author (retain original author information)
* Copyright (C) 202X Amlogic, Inc. All rights reserved.
*
* Description:
*/
#include <linux/skbuff.h>
#include <linux/mmc/sdio_func.h>
#include "fi_sdio.h"

#define HIF_READ        0x00000001
#define HIF_WRITE       0x00000002
#define HIF_SYNCHRONOUS  0x00000010
#define HIF_ASYNCHRONOUS 0x00000020

/* max page num while process a sdio write operation*/
#define SG_PAGE_MAX 80
#define MAXSG_SIZE        (SG_PAGE_MAX * 2)
#define MAX_SG_ENTRIES    (MAXSG_SIZE+2)
#define SG_NUM_MAX 16
#define SG_WRITE 1 //MMC_DATA_WRITE
#define SG_FRAME_MAX (1 * SG_NUM_MAX)

struct tx_trb_info_ex
{
    /* The number of pages needed for a single transfer */
    unsigned int packet_num;
    /* Actual size used for each page */
    unsigned short buffer_size[128];
};

struct amlw_hif_scatter_item {
    struct sk_buff *skbbuf;
    int len;
    int page_num;
    void *packet;
};

struct amlw_hif_scatter_req {
    /* address for the read/write operation */
    unsigned int addr;
    /* request flags */
    unsigned int req;
    /* total length of entire transfer */
    unsigned int len;

    void (*complete) (struct sk_buff *);

    bool free;
    int result;
    int scat_count;

    struct scatterlist sgentries[MAX_SG_ENTRIES];
    struct amlw_hif_scatter_item scat_list[MAX_SG_ENTRIES];
    struct tx_trb_info_ex page;
};

