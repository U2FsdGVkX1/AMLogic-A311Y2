/* SPDX-License-Identifier: GPL-2.0 */
/*
* Copyright (C) 202X Original Author (retain original author information)
* Copyright (C) 202X Amlogic, Inc. All rights reserved.
*
* Description:
*/
#ifndef __WIFI_W2_SHARED_MEM_CFG_H__
#define __WIFI_W2_SHARED_MEM_CFG_H__

/* original patch_rxdesc bigger than mini patch_rxdesc 136 byte */
/* reference code patch_fwmain.c line 400 */
#define SHARED_MEM_BASE_ADDR             (0x60000000)
#define TXPAGE_DESC_ADDR                 (0x6000d07c) /* size 0x114  */
#define TXL_TBD_START                    (0x6000d190) /* size 0x2d00 */
#define TXLBUF_TAG_SDIO                  (0x6000fe90) /* size 0x3a00 */

#define HW_RXBUF2_START_ADDR             (0x60013890) /* size 0x2BC */
#if defined (APF)
#define BUF_FOR_SUSPEND_USE_ADDR         (0x60013b4c)
#endif
#define HW_RXBUF1_START_ADDR             (0x6001534C) /* 0x60013b4c + 6K(for apf)*/

/*
LA OFF: rx buffer large size 0x40000, small size: 0x10000;
LA ON: rx buffer large size 0x30000, small size: 0x20000
*/
#define RXBUF_START_ADDR                 (0x6001534C) /* 0x60013b4c + 6K(for apf)*/

#define RXBUF_END_ADDR_SMALL             (0x6001e000) /*rx buf size: (0xA4B4)*/
#define RXBUF_END_ADDR_LARGE             (0x6006bb4c) /*rx buf size: (352K)*/
#define RXBUF_END_ADDR_LA_LARGE          (0x6005b400) //rx small + 160 tx page

#define TXBUF_START_ADDR                 (RXBUF_END_ADDR_SMALL)
#define USB_RXBUF_END_ADDR_SMALL         (0x60029130) /*rx buf size:0x1D454 (117.08K)*/
#define USB_TXBUF_START_ADDR             (USB_RXBUF_END_ADDR_SMALL)

#if defined (USB_TX_USE_LARGE_PAGE) || defined (CONFIG_AML_USB_LARGE_PAGE)
#define USB_RXBUF_END_ADDR_LARGE         (0x600684b0) /*rx buf size:(256K)*/
#define USB_RXBUF_END_ADDR_LA_LARGE      (0x600575c0) // rx small + 41 tx page
#define USB_RXBUF_END_ADDR_TRACE_LARGE   (0x60061850) // rx small + 50 tx page

#else
#define USB_RXBUF_END_ADDR_LARGE         (0x60053b4c) /*rx buf size:(256K)*/
#endif

#define RX_BUFFER_LEN_SMALL              (RXBUF_END_ADDR_SMALL - RXBUF_START_ADDR)
#define RX_BUFFER_LEN_LARGE              (RXBUF_END_ADDR_LARGE - RXBUF_START_ADDR)
#define RX_BUFFER_LEN_LA_LARGE           (RXBUF_END_ADDR_LA_LARGE - RXBUF_START_ADDR)
#define USB_RX_BUFFER_LEN_SMALL          (USB_RXBUF_END_ADDR_SMALL - RXBUF_START_ADDR)
#define USB_RX_BUFFER_LEN_LARGE          (USB_RXBUF_END_ADDR_LARGE - RXBUF_START_ADDR)
#define USB_RX_BUFFER_LEN_LA_LARGE       (USB_RXBUF_END_ADDR_LA_LARGE - RXBUF_START_ADDR)

#define TRX_BUF_SIZE        (0x60080000 - RXBUF_START_ADDR)

#define DCCM_TRACE_MID_ADDR         (0X828BF0)
#define DCCM_TRACE_START_ADDR       (0x828BF4)
#define HOST_DCCM_TRACE_SAME_ADDR   (0xd28BF8)
#define DCCM_TRACE_SAME_ADDR        (0x828BF8)
#define DCCM_TRACE_END_ADDR         (0x828BFC)
#define HOST_DCCM_TRACE_END_ADDR    (0xd28BFC)

/* trace use dccm 20K size */
#define TRACE_START_ADDR             (0x828c00)
#define TRACE_END_ADDR               (0x82dc00)

#define TRACE_COMPLETE_INFO          (0xC0DEACCE)

#define TRACE_TOTAL_SIZE    (TRACE_END_ADDR - TRACE_START_ADDR)
#define TRACE_MAX_SIZE      (TRACE_TOTAL_SIZE >> 1) /* trace max size is total size 1/2 */

#define LA_START_ADDR       (0x60070000)
#define LA_LENGTH           (0x10000)

#define SDIO_USB_EXTEND_E2A_IRQ_STATUS CMD_DOWN_FIFO_FDN_ADDR

#define USB_2T_MODE             (1)
#define USB_2T_MODE_REG         (0x141784)
#define HOST_USB_2T_MODE_REG    (MAC_ICCM_AHB_BASE + ICCM_ROM_LEN + 0x1784)

/* SDIO USB E2A EXTEND IRQ TYPE */
enum sdio_usb_e2a_irq_type {
    DYNAMIC_BUF_HOST_TX_STOP  = 1,
    DYNAMIC_BUF_HOST_TX_START,
    DYNAMIC_BUF_NOTIFY_FW_TX_STOP,
    DYNAMIC_BUF_LA_SWITCH_FINISH,
    DBG_REPORT_IRQ,
    DBG_DUMP_MEM_IRQ,
    SDIO_DETECT_IRQ,
    SDIO_FW_RST_IRQ,
};

struct sdio_buffer_control
{
    unsigned char flag;
    unsigned char need_update_edca;
    unsigned char rx_idle_chk_en;
    unsigned int tx_start_time;
    unsigned int tx_total_len;
    unsigned int rx_start_time;
    unsigned int rx_total_len;
    unsigned int tx_rate;
    unsigned int rx_rate;
    unsigned int buffer_status;
    unsigned int hwwr_switch_addr;
};
extern struct sdio_buffer_control sdio_buffer_ctrl;

//buffer_status
#define BUFFER_TX_USED             BIT(0)
#define BUFFER_RX_USED             BIT(1)
#define BUFFER_TX_NEED_ENLARGE     BIT(2)
#define BUFFER_RX_NEED_ENLARGE     BIT(3)
#define BUFFER_RX_WAIT_READ_DATA   BIT(4)
#define BUFFER_TX_STOP_FLAG        BIT(5)
#define BUFFER_RX_REDUCE_FLAG      BIT(6)
#define BUFFER_RX_ENLARGE_FLAG     BIT(7)
#define BUFFER_RX_FORCE_REDUCE     BIT(8)
#define BUFFER_RX_FORCE_ENLARGE    BIT(9)
#define BUFFER_RX_FORBID_REDUCE    BIT(10)
#define BUFFER_RX_FORBID_ENLARGE   BIT(11)
#define BUFFER_LA_USED             BIT(12)
#define BUFFER_LA_FREE             BIT(13)
#define DYNAMIC_BUF_IS_ON_TX  ((sdio_buffer_ctrl.buffer_status) & (BUFFER_TX_USED))
#define DYNAMIC_BUF_IS_ON_RX  ((sdio_buffer_ctrl.buffer_status) & (BUFFER_RX_USED))

//RG_WIFI_IF_FW2HST_IRQ_CFG buffer flag for firmware to host
#define RX_WRAP_TEMP_FLAG             BIT(19)
#define FW_BUFFER_NARROW              BIT(20)
#define FW_BUFFER_EXPAND              BIT(21)
#define FW_BUFFER_ERROR               BIT(22)

//CMD_DOWN_FIFO_FDH_ADDR + 4 buffer flag for host to firmware
#define RX_ENLARGE_READ_RX_DATA_FINISH BIT(25)
#define HOST_RXBUF_ENLARGE_FINISH      BIT(26)
#define RX_REDUCE_READ_RX_DATA_FINISH  BIT(27)
#define HOST_RXBUF_REDUCE_FINISH       BIT(28)

#define RX_WRAP_FLAG                  BIT(31)
#define FW_BUFFER_STATUS              (FW_BUFFER_NARROW | FW_BUFFER_EXPAND | FW_BUFFER_ERROR)
#define FW_BUFFER_ERROR_PATTERN       (0xC0DEDEAD)

#define RX_HAS_DATA        BIT(0)

// For debug exception and assert_err
#define DBG_INFO_LEN                   (1024)
#define DBG_EXCEPTION_PATTERN          (0xC0DEEACE)
#define DBG_ASSERT_PATTERN             (0xC0DEDEAD)

#define EXCEPTION_INFO_ADDR            (0x82dc14)
#define ASSERT_INFO_ADDR               (0x82dc00)
#define ASSERT_INFO_HOST_ADDR          (0xd2dc00)

struct exception_info
{
    uint32_t pattern;
    uint32_t mstatus_mps_bits;
    uint32_t mepc;
    uint32_t mtval;
    uint32_t mcause;
    uint32_t sp;
    uint8_t  type;
    uint8_t  reserve[3];
};

enum assert_type
{
    ASSERT_ERR_TYPE,
    ASSERT_REC_TYPE,
};

struct assert_info
{
    uint32_t pattern;
    uint32_t ts;
    uint32_t func_reg;
    uint16_t trace_file_id;
    uint16_t line;
    uint8_t  type;
    uint8_t  reserve[3];
};

#define SDIO_IRQ_E2A_CHAN_SWITCH_IND_MSG           CO_BIT(15)

#define UNWRAP_SIZE (56)

//some common define
#define SUSPEND_FW_TYPE_SIGN (0x6f7fc)
#define SUSPEND_FW_LOCK_SIGN (0x6f7f8)
#define SUSPEND_FW_TYPE (0xfefefefe)
#define RF_FW_TYPE (0xefefefef)
#define SUSPEND_FW_LOCK (0xeeffeeff)
#define SUSPEND_FW_UNLOCK (0xffeeffee)

#if 0
#define WIFI_SUSPEND_CODE_ADDR (0x060070000)
#define WIFI_SUSPEND_CODE_LEN (21668)
#else
#define WIFI_SUSPEND_CODE_ADDR (0x000066800)
#define WIFI_SUSPEND_CODE_LEN (36864)
#define WIFI_CMD_CODE_LEN (2048)
#endif

#define HOST_CMD_COUNT 16
#define HOST_CMD_SIZE (2048)
#define HOST_CMD_CODE_ADDR (0x0006f800)
#define CMD_FW_LOCK_SIGN (0x6fffc)
#define CMD_FW_LOCK (0xeeffeeff)
#define CMD_FW_UNLOCK (0xffeeffee)

enum host_cmd_download_tag {
    MM_SUB_SET_SUSPEND_REQ_INDEX,
    MM_SUB_SCANU_CANCEL_REQ_INDEX,
    MM_SUB_CALIBRATION_INDEX,
    MM_SUB_SHOW_TX_MSG_INDEX,
};

#endif
