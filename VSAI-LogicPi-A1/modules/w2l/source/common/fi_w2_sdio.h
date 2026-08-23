/* SPDX-License-Identifier: GPL-2.0 */
/*
* Copyright (C) 202X Original Author (retain original author information)
* Copyright (C) 202X Amlogic, Inc. All rights reserved.
*
* Description:
*/
#ifndef _FI_W2_SDIO_H
#define _FI_W2_SDIO_H

#define howmanypage(x,y) (((x - 12) + ((y - 12) -1) )/ (y - 12))

#ifdef CONFIG_SDIO_TX_ENH
#define SDIO_PAGE_MAX    61
#else
#define SDIO_PAGE_MAX    61
#endif

#define SDIO_TX_CKSUM_AMSDU_FLAG     1
#define SDIO_TX_CKSUM_VLAN_FLAG      2
#define SDIO_TX_CKSUM_FRAG_FLAG      4
#define SDIO_TX_CKSUM_ENABLE         8
#define SDIO_TX_CKSUM_VLAN_ENABLE    16
#define SDIO_TX_CKSUM_DATA_FLAG      32

#define SDIO_FRAME_TAIL_LEN    12
#define SDIO_PAGE_LEN    1568
#define AMSDU_LLC_LEN    22
#define LLC_LEN          8

#define SDIO_DATA_OFFSET   88 //12  + 4 + 72
#define SDIO_TXHEADER_LEN   80 //4  + 4 + 72
#define SDIO_TXDESC_OFFSET  16    //12 + 4
#define SDIO_CKSUM_OFFSET   12
#define AMSDU_LLC_OFFSET    94 // 4 + 4 + 72 + 14
#define SECOND_PAGE_DATA_OFFSET 12
#define TXDESC_OFFSET         8 // 4 + 4
#define USB_DATA_OFFSET    72 //payload offset

#define SDIO_TX_PAGE_SMALL_SKIP_NUM 203
#define SDIO_TX_PAGE_NUM_SMALL 53
#define SDIO_TX_PAGE_NUM_LARGE 255
#define SDIO_DYNA_PAGE_NUM  140

#if defined (USB_TX_USE_LARGE_PAGE) || defined (CONFIG_AML_USB_LARGE_PAGE)
#define USB_PAGE_MAX    25

#define USB_PAGE_LEN    4624

#define USB_TX_PAGE_SMALL_SKIP_NUM 56
#define USB_TX_PAGE_NUM_SMALL 21
#define USB_TX_PAGE_NUM_LARGE 77

#define USB_DYNA_PAGE_NUM 56
#define USB_LA_PAGE_NUM  15
#else
#define USB_PAGE_MAX    40

#define USB_TX_PAGE_SMALL_SKIP_NUM 147
#define USB_TX_PAGE_NUM_SMALL 53   //250 * 1024 / 1880
#define USB_TX_PAGE_NUM_LARGE 200

#define USB_DYNA_PAGE_NUM 147
#define USB_PAGE_LEN    1880
#define USB_LA_PAGE_NUM  35
#endif

#define SDIO_LA_PAGE_NUM  42
#define USB_WRITE_SRAM_LEN 480
#define USB_TX_ADDRESSTABLE_NUM  TX_PAGE_NUM_SMALL/2

#define WIFI_SDIO_IF    (0xa05000)

/*BIT(0): TX DONE intr, BIT(1): RX DONE intr*/
#define RG_SDIO_IF_INTR2CPU_ENABLE    (WIFI_SDIO_IF+0x30)


#endif


