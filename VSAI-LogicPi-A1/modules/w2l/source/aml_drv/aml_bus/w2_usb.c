/* SPDX-License-Identifier: GPL-2.0 */
/*
* Copyright (C) 202X Original Author (retain original author information)
* Copyright (C) 202X Amlogic, Inc. All rights reserved.
*
* Description:
*/
#define AML_MODULE          USB
#define AML_FMT             AML_FMT_M

#include "usb_common.h"
#include "chip_ana_reg.h"
#include "wifi_intf_addr.h"
#include "sg_common.h"
#include "fi_sdio.h"
#include "w2_usb.h"
#include "aml_static_buf.h"
#include "w2_sdio.h"
#include "aml_interface.h"
#include "aml_log.h"
#include "wifi_w2_shared_mem_cfg.h"
#include "lmac_msg.h"

#define AML_SIG_CBW                 0x43425355
#define AML_TAG_CBW                 0x5da729a0

#define BT_INTR_TRANS_FLAG          0xc6a780c2

#define UPDATE_FLAG                 0x11223344
#define USB_TXCMD_CARRY_RXRD_INDEX  401
#define WRITE_SRAM_DATA_LEN         477

enum aml_usb_dir {
    AML_XFER_TO_DEVICE = 0,
    AML_XFER_TO_HOST = 0x80,
};

#define WIFI_READ_CMD               0   // EP4
#define BT_READ_CMD                 1   // EP2

extern struct auc_hif_ops g_auc_hif_ops;
extern struct aml_hwif_usb g_hwif_usb;
extern struct usb_device *g_udev;
extern unsigned char auc_driver_insmoded;
extern struct crg_msc_cbw *g_cmd_buf;
extern struct aml_pm_type g_wifi_pm;

unsigned char *g_auc_kmalloc_buf = NULL;

static inline void __auc_cmd_rxrd_set(u32 flag, u32 rxrd)
{
    unsigned char *p = &g_cmd_buf->resv[USB_TXCMD_CARRY_RXRD_INDEX];

    *p++ = flag & 0xff;
    *p++ = (flag >> 8) & 0xff;
    *p++ = (flag >> 16) & 0xff;
    *p++ = (flag >> 24) & 0xff;

    *p++ = rxrd & 0xff;
    *p++ = (rxrd >> 8) & 0xff;
    *p++ = (rxrd >> 16) & 0xff;
    *p++ = (rxrd >> 24) & 0xff;
}

static inline void auc_cmd_rxrd_clear(void)
{
    __auc_cmd_rxrd_set(0, 0);
}

int auc_cmd_rxrd_set(u32 rxrd)
{
    USB_BEGIN_LOCK();
    /* RX read pointer (confirm) is already embedded in command? */
    if (*(u32 *)&g_cmd_buf->resv[USB_TXCMD_CARRY_RXRD_INDEX]) {
        USB_END_LOCK();
        return -1;
    }

    /* later send it to firmware with the next command */
    __auc_cmd_rxrd_set(UPDATE_FLAG, rxrd);
    USB_END_LOCK();
    return 0;
}
EXPORT_SYMBOL(auc_cmd_rxrd_set);

static void auc_build_cbw_add_data(struct crg_msc_cbw *cbw_buf,
                                   enum aml_usb_dir dir, unsigned int len,
                                   enum wifi_cmd cmd, u32 addr, u32 flag, u32 data_len,
                                   const unsigned char *data)
{
    cbw_buf->sig = AML_SIG_CBW;
    cbw_buf->tag = AML_TAG_CBW;
    cbw_buf->data_len = len;
    cbw_buf->flag = dir; //direction
    cbw_buf->len = 16; //command length
    cbw_buf->lun = 0;

    cbw_buf->cdb[0] = cmd;
    cbw_buf->cdb[1] = addr; // read or write addr
    cbw_buf->cdb[2] = flag;
    cbw_buf->cdb[3] = data_len; //read or write data length

    if (!data)
        return;

    BUG_ON(dir != AML_XFER_TO_DEVICE);
    BUG_ON(len >= USB_TXCMD_CARRY_RXRD_INDEX);
    memcpy(cbw_buf->resv + 1, (unsigned char *) data, len);
    /*in case call cmd and data mode but fw call cmd+data stage*/
    cbw_buf->resv[479] = cbw_buf->resv[480] = 0xFF;
}

static inline void auc_build_cbw(struct crg_msc_cbw *cbw_buf,
                                 enum aml_usb_dir dir, unsigned int len,
                                 enum wifi_cmd cmd, u32 addr, u32 flag, u32 data_len)
{
    return auc_build_cbw_add_data(cbw_buf, dir, len, cmd, addr, flag, data_len, NULL);
}

int auc_bulk_msg(struct usb_device *usb_dev, unsigned int pipe,
    void *data, int len, int *actual_length, int timeout)
{
    int ret = 0;
#ifdef CONFIG_PM
    if (atomic_read(&g_wifi_pm.bus_suspend_cnt) != 0) {
        AML_ERR("bus suspend (%d) ongoing, do not read/write now!\n",
            atomic_read(&g_wifi_pm.bus_suspend_cnt));
        return -ENOMEM;
    }
#endif
    if (atomic_read(&g_wifi_pm.is_shut_down) == 1) {
        AML_ERR("fw shut down(%d) , do not read/write now!\n",
            atomic_read(&g_wifi_pm.is_shut_down));
        return -ENOMEM;
    }

#ifdef CONFIG_AML_RECOVERY
    if (!usb_bus_available()) {
        AML_ERR("bus not available, do not read/write now!\n");
        return -ENOMEM;
    }
#endif
    ret = usb_bulk_msg(usb_dev, pipe, data, len, actual_length, timeout);
#ifdef CONFIG_AML_RECOVERY
    if (ret && !bus_state_detect.bus_err) {
    #ifdef CONFIG_USB_HOTPLUG
        if (bus_state_detect.usb_unplug)
            aml_usb_set_bus_err(1);
    #endif
        if ((bus_state_detect.is_drv_load_finished) && (!bus_state_detect.is_recy_ongoing)) {
            aml_usb_set_bus_err(1);
            AML_ERR("bus error(%d), will do reovery later\n", ret);
        }
    } else {
        aml_usb_set_bus_err(0);
    }
#endif

    return ret;
}

void usb_isoc_callback(struct urb * urb)
{
    AML_WARN("urb: 0x%p; iso callback is called!\n", urb);
}

int auc_write_reg_ep3(unsigned int addr, unsigned int value, unsigned int len)
{
    int ret = 0;
    struct usb_device *udev = g_udev;
    struct urb *urb;

    USB_BEGIN_LOCK();

    urb = usb_alloc_urb(1, GFP_ATOMIC);

    if (!urb) {
        AML_ERR("alloc urb failed!\n");
        USB_END_LOCK();
        return -ENOMEM;
    }

    auc_build_cbw(g_cmd_buf, AML_XFER_TO_DEVICE, 0, CMD_WRITE_REG, addr, value, len);

    urb->dev = udev;
    urb->pipe = usb_sndisocpipe(udev, USB_EP3);
    urb->transfer_flags = URB_ISO_ASAP;
    urb->transfer_buffer = g_cmd_buf;
    urb->transfer_buffer_length = sizeof(*g_cmd_buf);

    urb->complete = usb_isoc_callback;
    urb->number_of_packets = 1;
    urb->interval = 8;

    urb->iso_frame_desc[0].offset = 0;
    urb->iso_frame_desc[0].length = sizeof(*g_cmd_buf);

    /* cmd stage */
    ret = usb_submit_urb(urb, GFP_ATOMIC);//GFP_KERNEL
    if (ret) {
        AML_ERR("Failed to submit urb, ret %d,  addr: 0x%x, len: %d, value: 0x%x\n", ret, addr, len, value);
        usb_free_urb(urb);
        USB_END_LOCK();
        return ret;
    }
    usb_free_urb(urb);
    USB_END_LOCK();

    return ret;
}

unsigned int auc_read_reg_ep3(unsigned int addr, unsigned int len)
{
    unsigned int reg_data;
    int ret = 0;
    struct usb_device *udev = g_udev;
    unsigned char *kmalloc_buf = NULL;
    struct urb *urb;

    USB_BEGIN_LOCK();

    urb= usb_alloc_urb(1, GFP_ATOMIC);

    if (!urb) {
        AML_ERR("alloc urb failed!\n");
        USB_END_LOCK();
        return -ENOMEM;
    }

    kmalloc_buf = (unsigned char *)ZMALLOC(len, "usb_read_sram", GFP_DMA|GFP_ATOMIC);

    if (kmalloc_buf == NULL)
    {
        AML_ERR("kmalloc buf fail, len: %d\n", len);
        USB_END_LOCK();
        return -1;
    }

    auc_build_cbw(g_cmd_buf, AML_XFER_TO_HOST, len, CMD_READ_REG, addr, 0, len);

    urb->dev = udev;
    urb->pipe = usb_sndisocpipe(udev, USB_EP3);
    urb->transfer_flags = URB_ISO_ASAP;
    urb->transfer_buffer = g_cmd_buf;
    urb->transfer_buffer_length = sizeof(*g_cmd_buf);

    urb->complete = usb_isoc_callback;
    urb->number_of_packets = 1;
    urb->interval = 8;

    urb->iso_frame_desc[0].offset = 0;
    urb->iso_frame_desc[0].length = sizeof(*g_cmd_buf);

    ret = usb_submit_urb(urb, GFP_ATOMIC); //GFP_KERNEL
    if (ret) {
        AML_ERR("EP3: Failed to submit urb, ret %d,  addr: 0x%x, len: %d\n", ret, addr, len);
        FREE(kmalloc_buf, "usb_read_sram");
        usb_free_urb(urb);
        USB_END_LOCK();
        return ret;
    }

    usb_free_urb(urb);
    usleep_range(1000,1200);

    urb = usb_alloc_urb(1, GFP_ATOMIC);

    if (!urb) {
        AML_ERR("alloc urb failed!\n");
        FREE(kmalloc_buf, "usb_read_sram");
        USB_END_LOCK();
        return -ENOMEM;
    }

    urb->dev= udev;
    urb->pipe = usb_rcvisocpipe(udev, USB_EP3);
    urb->transfer_flags = URB_ISO_ASAP;
    urb->transfer_buffer = kmalloc_buf;
    urb->transfer_buffer_length = len;
    urb->number_of_packets = 1;
    urb->interval = 8;
    urb->complete = usb_isoc_callback;

    urb->iso_frame_desc[0].offset = 0;
    urb->iso_frame_desc[0].length = len;

    ret = usb_submit_urb(urb, GFP_ATOMIC); //GFP_KERNEL
    if (ret) {
        AML_ERR("EP3: Failed to submit urb, ret %d, addr: 0x%x, len: %d\n", ret, addr, len);
        FREE(kmalloc_buf, "usb_read_sram");
        usb_free_urb(urb);
        USB_END_LOCK();
        return ret;
    }

    memcpy(&reg_data, kmalloc_buf, len);
    FREE(kmalloc_buf, "usb_read_sram");
    usb_free_urb(urb);
    USB_END_LOCK();

    return reg_data;
}

void auc_write_sram_ep3(unsigned char *pdata, unsigned int addr, unsigned int len)
{
    int ret = 0;
    struct usb_device *udev = g_udev;
    unsigned char *kmalloc_buf = NULL;
    struct urb *urb;

    USB_BEGIN_LOCK();

    urb = usb_alloc_urb(1, GFP_ATOMIC);

    if (!urb) {
        AML_ERR("alloc urb failed!\n");
        USB_END_LOCK();
        return;
    }

    kmalloc_buf = (unsigned char *)ZMALLOC(len, "usb_write_sram", GFP_DMA | GFP_ATOMIC);//virt_to_phys(fwICCM);
    if (kmalloc_buf == NULL)
    {
        AML_ERR("kmalloc buf fail, len: %d\n", len);
        USB_END_LOCK();
        return;
    }

    memcpy(kmalloc_buf, pdata, len);

    auc_build_cbw(g_cmd_buf, AML_XFER_TO_DEVICE, len + 4, CMD_WRITE_SRAM, addr, 0, len + 4);

    urb->dev = udev;
    urb->pipe = usb_sndisocpipe(udev, USB_EP3);
    urb->transfer_flags = URB_ISO_ASAP;
    urb->transfer_buffer = g_cmd_buf;
    urb->transfer_buffer_length = sizeof(*g_cmd_buf);

    urb->complete = usb_isoc_callback;
    urb->number_of_packets = 1;
    urb->interval = 8;

    urb->iso_frame_desc[0].offset = 0;
    urb->iso_frame_desc[0].length = sizeof(*g_cmd_buf);

    /* cmd stage */
    ret = usb_submit_urb(urb, GFP_ATOMIC);
    if (ret) {
        AML_ERR("Failed to usb_bulk_msg, ret %d, addr: 0x%x, len: %d\n", ret, addr, len);
        FREE(kmalloc_buf, "usb_read_sram");
        usb_free_urb(urb);
        USB_END_LOCK();
        return;
    }

    usb_free_urb(urb);
    usleep_range(1000,1200);
    urb = usb_alloc_urb(1, GFP_ATOMIC);

    if (!urb) {
        AML_ERR("alloc urb failed!\n");
        FREE(kmalloc_buf, "usb_read_sram");
        USB_END_LOCK();
        return;
    }

    urb->dev = udev;
    urb->pipe = usb_sndisocpipe(udev, USB_EP3);
    urb->transfer_flags = URB_ISO_ASAP;
    urb->transfer_buffer = kmalloc_buf;
    urb->transfer_buffer_length = len;

    urb->complete = usb_isoc_callback;
    urb->number_of_packets = 1;
    urb->interval = 8;

    urb->iso_frame_desc[0].offset = 0;
    urb->iso_frame_desc[0].length = len;

    /* data stage */
    ret = usb_submit_urb(urb, GFP_ATOMIC);//GFP_KERNEL
    if (ret) {
        AML_ERR("EP3: Failed to submit urb, ret %d, addr: 0x%x, len: %d\n", ret, addr, len);
        FREE(kmalloc_buf, "usb_read_sram");
        usb_free_urb(urb);
        USB_END_LOCK();
        return;
    }

    FREE(kmalloc_buf, "usb_write_sram");
    usb_free_urb(urb);
    USB_END_LOCK();
}

void auc_read_sram_ep3(unsigned char *pdata, unsigned int addr, unsigned int len)
{
    int ret = 0;
    struct usb_device *udev = g_udev;
    unsigned char *kmalloc_buf = NULL;
    struct urb *urb;

    USB_BEGIN_LOCK();

    urb = usb_alloc_urb(1, GFP_ATOMIC);

    if (!urb) {
        AML_ERR("alloc urb failed!\n");
        USB_END_LOCK();
        return;
    }

    kmalloc_buf = (unsigned char *)ZMALLOC(len, "usb_read_sram", GFP_DMA|GFP_ATOMIC);
    if (kmalloc_buf == NULL)
    {
        AML_ERR("kmalloc buf fail, len: %d\n", len);
        USB_END_LOCK();
        return;
    }

    auc_build_cbw(g_cmd_buf,  AML_XFER_TO_HOST, len, CMD_READ_SRAM, addr, 0, len);

    urb->dev = udev;
    urb->pipe = usb_sndisocpipe(udev, USB_EP3);
    urb->transfer_flags = URB_ISO_ASAP;

    urb->transfer_buffer = g_cmd_buf;
    urb->transfer_buffer_length = sizeof(*g_cmd_buf);

    urb->complete = usb_isoc_callback;
    urb->number_of_packets = 1;
    urb->interval = 8;

    urb->iso_frame_desc[0].offset = 0;
    urb->iso_frame_desc[0].length = sizeof(*g_cmd_buf);

    /* cmd stage */
    ret = usb_submit_urb(urb, GFP_ATOMIC);
    if (ret) {
        AML_ERR("Failed to usb_bulk_msg, ret %d, addr: 0x%x, len: %d\n", ret, addr, len);
        FREE(kmalloc_buf, "usb_read_sram");
        usb_free_urb(urb);
        USB_END_LOCK();
        return;
    }

    usb_free_urb(urb);
    usleep_range(1000,1200);

    urb = usb_alloc_urb(1, GFP_ATOMIC);

    if (!urb) {
        AML_ERR("alloc urb failed!\n");
        FREE(kmalloc_buf, "usb_read_sram");
        USB_END_LOCK();
        return;
    }

    urb->dev = udev;
    urb->pipe = usb_rcvisocpipe(udev, USB_EP3);
    urb->transfer_flags = URB_ISO_ASAP;
    urb->transfer_buffer = kmalloc_buf;
    urb->transfer_buffer_length = len;

    urb->complete = usb_isoc_callback;
    urb->number_of_packets = 1;
    urb->interval = 8;
    urb->iso_frame_desc[0].offset = 0;
    urb->iso_frame_desc[0].length = len;

    /* data stage */
    ret = usb_submit_urb(urb, GFP_ATOMIC); //GFP_KERNEL
    if (ret) {
        AML_ERR("Failed to submit urb, ret %d, addr: 0x%x, len: %d\n", ret, addr, len);
        FREE(kmalloc_buf, "usb_read_sram");
        usb_free_urb(urb);
        USB_END_LOCK();
        return;
    }

    usleep_range(1000,1200);
    memcpy(pdata, kmalloc_buf, /*urb->actual_length*/len);
    usleep_range(1000,1200);

    FREE(kmalloc_buf, "usb_read_sram");
    usb_free_urb(urb);

    USB_END_LOCK();
}

int auc_write_reg_by_ep(unsigned int addr, unsigned int value, unsigned int len, unsigned int ep)
{
    int ret = 0;
    int actual_length = 0;
    struct usb_device *udev = g_udev;

    USB_BEGIN_LOCK();
    auc_build_cbw(g_cmd_buf, AML_XFER_TO_DEVICE, 0, CMD_WRITE_REG, addr, value, len);
    /* cmd stage */
    ret = auc_bulk_msg(udev, (unsigned int)usb_sndbulkpipe(udev, ep),(void *) g_cmd_buf, sizeof(*g_cmd_buf), &actual_length, AML_USB_CONTROL_MSG_TIMEOUT);
    if (ret) {
        AML_ERR("Failed to usb_bulk_msg, ret %d, ep: %d, addr: 0x%x, len: %d, value: 0x%x\n", ret, ep, addr, len, value);
        USB_END_LOCK();
        return ret;
    }
    USB_END_LOCK();

    return actual_length; //bt write maybe use the value
}

unsigned int auc_read_reg_by_ep(unsigned int addr, unsigned int len, unsigned int ep, unsigned int mode)
{
    int ret = 0;
    int actual_length = 0;
    unsigned int reg_data;
    struct usb_device *udev = g_udev;
    unsigned char *data = NULL;

    USB_BEGIN_LOCK();

    if (g_auc_kmalloc_buf) {
        data = g_auc_kmalloc_buf;
    } else {
        data = (unsigned char *)ZMALLOC(len,"reg tmp",GFP_DMA | GFP_ATOMIC);

        if (!data) {
            AML_ERR("data malloc fail, ep: %d, addr: 0x%x, len: %d, mode: %d\n", ep, addr, len, mode);
            USB_END_LOCK();
            return -ENOMEM;
        }
    }

    auc_build_cbw(g_cmd_buf, AML_XFER_TO_HOST, len, CMD_READ_REG, addr, 0, len);

    /* cmd stage */
    ret = auc_bulk_msg(udev, usb_sndbulkpipe(udev, ep),(void *)g_cmd_buf, sizeof(*g_cmd_buf), &actual_length, AML_USB_CONTROL_MSG_TIMEOUT);
    if (ret) {
        AML_ERR("Failed to usb_bulk_msg, ret %d, ep: %d, addr: 0x%x, len: %d, mode: %d\n", ret, ep, addr, len, mode);
        if (data != g_auc_kmalloc_buf) {
            FREE(data, "reg tmp");
        }
        USB_END_LOCK();
        return ret;
    }

    /* data stage */
    ret = auc_bulk_msg(udev, usb_rcvbulkpipe(udev, ep), (void *)data, len, &actual_length, AML_USB_CONTROL_MSG_TIMEOUT);
    if (ret) {
        AML_ERR("Failed to usb_bulk_msg, ret %d, ep: %d, addr: 0x%x, len: %d, mode: %d\n", ret ,ep, addr, len, mode);
        if (data != g_auc_kmalloc_buf) {
            FREE(data,"reg tmp");
        }
        USB_END_LOCK();
        return ret;
    }

    memcpy(&reg_data, data, actual_length);
    if (data != g_auc_kmalloc_buf) {
        FREE(data,"reg tmp");
    }
    USB_END_LOCK();

    return reg_data;
}

extern int coex_flag;
void auc_write_sram_by_ep(const unsigned char *pdata, unsigned int addr, unsigned int len, unsigned int ep)
{
    int ret = 0;
    int actual_length = 0;
    struct usb_device *udev = g_udev;
    unsigned char *kmalloc_buf = NULL;

    USB_BEGIN_LOCK();
    /* NB: original code may overwrite RXRD at USB_TXCMD_CARRY_RXRD_INDEX(401) */
    if (coex_flag && len < min(USB_TXCMD_CARRY_RXRD_INDEX, WRITE_SRAM_DATA_LEN)) {
        auc_build_cbw_add_data(g_cmd_buf, AML_XFER_TO_DEVICE, len, CMD_WRITE_SRAM, addr, 0, len, pdata);
        /* cmd stage */
        ret = auc_bulk_msg(udev, usb_sndbulkpipe(udev, ep), (void*)g_cmd_buf, sizeof(*g_cmd_buf), &actual_length, AML_USB_CONTROL_MSG_TIMEOUT);
        if (ret) {
            AML_ERR("Failed to usb_bulk_msg, ret %d, ep: %d, addr: 0x%x, len: %d\n", ret, ep, addr, len);
            AML_ERR("usb command transmit fail,g_cmd_buf->add is %d,len is %d\n", addr, len);
            USB_END_LOCK();
            return;
        }
        auc_cmd_rxrd_clear();
        g_cmd_buf->resv[479] = g_cmd_buf->resv[480] = 0;
    } else {
        auc_build_cbw(g_cmd_buf, AML_XFER_TO_DEVICE, len, CMD_WRITE_SRAM, addr, 0, len);
        /* cmd stage */
        ret = auc_bulk_msg(udev, usb_sndbulkpipe(udev, ep), (void*)g_cmd_buf, sizeof(*g_cmd_buf), &actual_length, AML_USB_CONTROL_MSG_TIMEOUT);
        if (ret) {
            AML_ERR("Failed to usb_bulk_msg, ret %d, ep: %d, addr: 0x%x, len: %d\n", ret, ep, addr, len);
            AML_ERR("usb command transmit fail,g_cmd_buf->add is %d,len is %d\n",addr,len);
            USB_END_LOCK();
            return;
        }

        auc_cmd_rxrd_clear();

        if (g_auc_kmalloc_buf) {
            kmalloc_buf = g_auc_kmalloc_buf;
        } else {
            kmalloc_buf = (unsigned char *)ZMALLOC(len, "usb_write_sram", GFP_DMA | GFP_ATOMIC);//virt_to_phys(fwICCM);
            if (kmalloc_buf == NULL)
            {
                AML_ERR("kmalloc buf fail, ep: %d, addr: 0x%x, len: %d\n", ep, addr, len);
                USB_END_LOCK();
                return;
            }
        }

        memcpy(kmalloc_buf, pdata, len);
        /* data stage */
        ret = auc_bulk_msg(udev, usb_sndbulkpipe(udev, ep), (void *)kmalloc_buf, len, &actual_length, AML_USB_CONTROL_MSG_TIMEOUT);
        if (ret) {
            AML_ERR("Failed to usb_bulk_msg, ret %d, ep: %d,  addr: 0x%x, len: %d\n", ret, ep, addr, len);
            if (g_auc_kmalloc_buf != kmalloc_buf) {
                FREE(kmalloc_buf, "usb_read_sram");
            }
            USB_END_LOCK();
            return;
        }
        if (g_auc_kmalloc_buf != kmalloc_buf) {
            FREE(kmalloc_buf, "usb_read_sram");
        }
    }

    USB_END_LOCK();
}

void auc_read_sram_by_ep(unsigned char *pdata, unsigned int addr, unsigned int len, unsigned int ep, unsigned int mode)
{
    int ret = 0;
    int actual_length = 0;
    struct usb_device *udev = g_udev;
    unsigned char *kmalloc_buf = NULL;

    USB_BEGIN_LOCK();

    auc_build_cbw(g_cmd_buf,  AML_XFER_TO_HOST, len, CMD_READ_SRAM, addr, 0, len);
    /* cmd stage */
    ret = auc_bulk_msg(udev, usb_sndbulkpipe(udev, ep), (void *)g_cmd_buf, sizeof(*g_cmd_buf), &actual_length, AML_USB_CONTROL_MSG_TIMEOUT);
    if (ret) {
        AML_ERR("Failed to usb_bulk_msg, ret %d, ep: %d, addr: 0x%x, len: %d, mode: %d\n", ret, ep, addr, len, mode);
        AML_ERR("usb command transmit fail,g_cmd_buf->add is %d,len is %d\n",addr,len);
        USB_END_LOCK();
        return;
    }

    if (g_auc_kmalloc_buf) {
        kmalloc_buf = g_auc_kmalloc_buf;
    } else {
        kmalloc_buf = (unsigned char *)ZMALLOC(len, "usb_read_sram", GFP_DMA|GFP_ATOMIC);
        if (kmalloc_buf == NULL)
        {
            AML_ERR("kmalloc buf fail, ep: %d, len: %d\n", ep, len);
            USB_END_LOCK();
            return;
        }
    }

    /* data stage */
    ret = auc_bulk_msg(udev, usb_rcvbulkpipe(udev, ep),(void *)kmalloc_buf, len, &actual_length, AML_USB_CONTROL_MSG_TIMEOUT);
    if (ret) {
        AML_ERR("Failed to usb_bulk_msg, ret %d, ep: %d, addr: 0x%x, len: %d, mode: %d\n", ret, ep, addr, len, mode);
        if (g_auc_kmalloc_buf != kmalloc_buf) {
            FREE(kmalloc_buf, "usb_read_sram");
        }
        USB_END_LOCK();
        return;
    }

    memcpy(pdata, kmalloc_buf, actual_length);
    if (g_auc_kmalloc_buf != kmalloc_buf) {
        FREE(kmalloc_buf, "usb_read_sram");
    }

    USB_END_LOCK();
}

static int rx_read(unsigned char *pdata, u32 addr, unsigned int len, unsigned int ep, unsigned int mode)
{
    int ret = 0;
    int actual_length = 0;
    struct usb_device *udev = g_udev;

    USB_BEGIN_LOCK();
    auc_build_cbw(g_cmd_buf, AML_XFER_TO_HOST, len, CMD_READ_SRAM, addr, 0, len);
    /* cmd stage */
    ret = auc_bulk_msg(udev, usb_sndbulkpipe(udev, ep), (void *)g_cmd_buf, sizeof(*g_cmd_buf), &actual_length, AML_USB_CONTROL_MSG_TIMEOUT);
    if (ret) {
        AML_ERR("Failed to usb_bulk_msg, ret %d, ep: %d, addr: 0x%x, len: %d, mode: %d\n", ret, ep, addr, len, mode);
        USB_END_LOCK();
        return ret;
    }

    /* data stage */
    ret = auc_bulk_msg(udev, usb_rcvbulkpipe(udev, ep),(void *)pdata, len, &actual_length, AML_USB_CONTROL_MSG_TIMEOUT);
    if (ret) {
        AML_ERR("Failed to usb_bulk_msg, ret %d, ep: %d,  addr: 0x%x, len: %d, mode: %d\n", ret, ep, addr, len, mode);
        USB_END_LOCK();
        return ret;
    }

    USB_END_LOCK();
    return actual_length;
}

void auc_write_word_by_ep_for_wifi(unsigned int addr,unsigned int data, unsigned int ep)
{
    int len = 4;

#ifdef CONFIG_AML_RECOVERY
    if (!usb_bus_available()) {
        AML_ERR("EP-%d bus not available, do not read/write now!\n", ep);
        return;
    }
#endif

    if ((ep == USB_EP1) || (ep == USB_EP4) || (ep == USB_EP5) || (ep == USB_EP6) || (ep == USB_EP7)) {
        auc_write_reg_by_ep(addr, data, len, ep);
    } else {
        AML_ERR("write_word: ep-%d unsupported\n", ep);
    }
}

unsigned int auc_read_word_by_ep_for_wifi(unsigned int addr, unsigned int ep)
{
    int len = 4;
    unsigned int value = 0;

#ifdef CONFIG_AML_RECOVERY
    if (!usb_bus_available()) {
        AML_ERR("EP-%d bus not available, do not read/write now!\n", ep);
        return 0;
    }
#endif

    if ((ep == USB_EP2) || (ep == USB_EP4) || (ep == USB_EP5) || (ep == USB_EP6) || (ep == USB_EP7)) {
        value = auc_read_reg_by_ep(addr, len, ep, WIFI_READ_CMD);
    } else {
        AML_ERR("Read_word: ep-%d unsupported!\n", ep);
    }

    return value;
}

void auc_write_sram_by_ep_for_wifi(const unsigned char *buf, unsigned char *sram_addr, unsigned int len, unsigned int ep)
{
    if (len == 0) {
        AML_ERR("EP-%d write len err!\n", ep);
        return;
    }
#ifdef CONFIG_AML_RECOVERY
    if (!usb_bus_available()) {
        AML_ERR("EP-%d bus not available, do not read/write now!\n", ep);
        return;
    }
#endif

    auc_write_sram_by_ep(buf, (unsigned int)(unsigned long)sram_addr, len, ep);
}

void auc_read_sram_by_ep_for_wifi(unsigned char *buf,unsigned char *sram_addr, unsigned int len, unsigned int ep)
{
    if (len == 0) {
        AML_ERR("EP-%d read len err!\n", ep);
        return;
    }
#ifdef CONFIG_AML_RECOVERY
    if (!usb_bus_available()) {
        AML_ERR("EP-%d bus not available, do not read/write now!\n", ep);
        return;
    }
#endif

    auc_read_sram_by_ep(buf, (unsigned int)(unsigned long)sram_addr, len, ep, WIFI_READ_CMD);
}

static int auc_rx_buffer_read(void *buf, u32 sram_addr, unsigned int len, unsigned int ep)
{
    if ((ep == USB_EP4) || (ep == USB_EP5) || (ep == USB_EP6) || (ep == USB_EP7))
        return rx_read(buf, sram_addr, len, ep, WIFI_READ_CMD);

    AML_ERR("write_word: ep-%d unsupported\n", ep);
    return -1;
}

void auc_write_word_by_ep_for_bt(unsigned int addr,unsigned int data, unsigned int ep)
{
    int len = 4;

#ifdef CONFIG_AML_RECOVERY
    if (!usb_bus_available()) {
        AML_ERR("EP-%d bus not available, do not read/write now!\n", ep);
        return;
    }
#endif
    switch (ep) {
        case USB_EP2:
            auc_write_reg_by_ep(addr, data, len, ep);
            break;
        case USB_EP3:
            auc_write_reg_ep3(addr, data, len);
            break;
        default:
            AML_ERR("EP-%d unsupported!\n", ep);
            break;
    }
}

unsigned int auc_read_word_by_ep_for_bt(unsigned int addr, unsigned int ep)
{
    int len = 4;
    unsigned int value = 0;

#ifdef CONFIG_AML_RECOVERY
    if (!usb_bus_available()) {
        AML_ERR("EP-%d bus not available, do not read/write now!\n", ep);
        return 0;
    }
#endif
    switch (ep) {
        case USB_EP2:
            value = auc_read_reg_by_ep(addr, len, ep, BT_READ_CMD);
            break;
        case USB_EP3:
            value = auc_read_reg_ep3(addr, len);
            break;
        default:
            AML_ERR("EP-%d unsupported!\n", ep);
            break;
    }
    return value;
}

void auc_write_sram_by_ep_for_bt(unsigned char *buf, unsigned char *sram_addr, unsigned int len, unsigned int ep)
{
    if (len == 0) {
        AML_ERR("EP-%d write len err!\n", ep);
        return;
    }
#ifdef CONFIG_AML_RECOVERY
    if (!usb_bus_available()) {
        AML_ERR("EP-%d bus not available, do not read/write now!\n", ep);
        return;
    }
#endif
    switch (ep) {
        case USB_EP2:
            auc_write_sram_by_ep(buf, (unsigned int)(unsigned long)sram_addr, len, ep);
            break;
        case USB_EP3:
            auc_write_sram_ep3(buf, (unsigned int)(unsigned long)sram_addr, len);
            break;
        default:
            AML_ERR("EP-%d unsupported!\n", ep);
            break;
    }
}
void auc_read_sram_by_ep_for_bt(unsigned char *buf,unsigned char *sram_addr, unsigned int len, unsigned int ep)
{
    if (len == 0) {
        AML_ERR("EP-%d read len err!\n", ep);
        return;
    }
#ifdef CONFIG_AML_RECOVERY
    if (!usb_bus_available()) {
        AML_ERR("EP-%d bus not available, do not read/write now!\n", ep);
        return;
    }
#endif
    switch (ep) {
        case USB_EP2:
            auc_read_sram_by_ep(buf, (unsigned int)(unsigned long)sram_addr, len, ep, BT_READ_CMD);
            break;
        case USB_EP3:
            auc_read_sram_ep3(buf, (unsigned int)(unsigned long)sram_addr, len);
            break;
        default:
            AML_ERR("EP-%d unsupported!\n", ep);
            break;
    }
}

struct aml_hwif_usb *aml_usb_priv(void)
{
    return &g_hwif_usb;
}

int w2_usb_enable_scatter(void)
{
    struct aml_hwif_usb *hif_usb = aml_usb_priv();
    struct amlw_hif_scatter_req *scat_req = NULL;

    BUG_ON(!hif_usb);

    if (hif_usb->scatter_enabled) {
        return 0;
    }

    hif_usb->scatter_enabled = true;

    /* allocate the scatter request */
    scat_req = ZMALLOC(sizeof(struct amlw_hif_scatter_req), "usb_alloc_prep_scat_req", GFP_ATOMIC|GFP_DMA);
    if (scat_req == NULL)
    {
        AML_ERR("[usb sg alloc_scat_req]: no mem\n");
        return 1;
    }

    scat_req->free = true;
    hif_usb->scat_req = scat_req;

    return 0;

}

struct amlw_hif_scatter_req *aml_usb_scatter_req_get(void)
{
    struct aml_hwif_usb *hif_usb = aml_usb_priv();
    struct amlw_hif_scatter_req *scat_req = NULL;

    BUG_ON(!hif_usb);

    scat_req = hif_usb->scat_req;

    if (scat_req->free)
    {
        scat_req->free = false;
    }
    else if (scat_req->scat_count != 0) // get scat_req, but not build scatter list
    {
        scat_req = NULL;
    }

    return scat_req;
}

void aml_usb_cleanup_scatter(void)
{
    struct aml_hwif_usb *hif_usb = aml_usb_priv();

    AML_FN_ENTRY();
    BUG_ON(!hif_usb);

    if (!hif_usb->scatter_enabled)
        return;

    hif_usb->scatter_enabled = false;

    /* empty the free list */
    FREE(hif_usb->scat_req, "usb_alloc_prep_scat_req");

    AML_FN_EXIT();

    return;
}

void w2_usb_scat_complete (struct amlw_hif_scatter_req * scat_req)
{
    int  i;

    BUG_ON(!scat_req);

    if (scat_req->complete)
    {
        for (i = 0; i < scat_req->scat_count; i++)
        {
            (scat_req->complete)(scat_req->scat_list[i].skbbuf);
            scat_req->scat_list[i].skbbuf = NULL;
        }
    }
    scat_req->free = true;
    scat_req->scat_count = 0;
    scat_req->len = 0;
    scat_req->addr = 0;
    memset(scat_req->sgentries, 0, MAX_SG_ENTRIES * sizeof(struct scatterlist));

}

void aml_usb_build_tx_packet_info(struct crg_msc_cbw *cbw_buf, unsigned char cdb1,
    struct tx_trb_info_ex * trb_info)
{
    cbw_buf->sig = trb_info->buffer_size[0] | trb_info->buffer_size[1] << 16;
    cbw_buf->tag = trb_info->buffer_size[2] | trb_info->buffer_size[3] << 16;
    cbw_buf->data_len = trb_info->buffer_size[4] | trb_info->buffer_size[5] << 16;
    cbw_buf->flag = trb_info->packet_num; //packet nums 1byte
    cbw_buf->len = trb_info->buffer_size[13] & 0xff;
    cbw_buf->lun = (trb_info->buffer_size[13] >> 8) & 0xff;
    cbw_buf->cdb[0] = cdb1 | trb_info->buffer_size[12] << 16;
    cbw_buf->cdb[1] = trb_info->buffer_size[6] | trb_info->buffer_size[7] << 16;
    cbw_buf->cdb[2] = trb_info->buffer_size[8] | trb_info->buffer_size[9] << 16;
    cbw_buf->cdb[3] = trb_info->buffer_size[10] | trb_info->buffer_size[11] << 16;

    {
        int i=0,j;
        if (trb_info->packet_num >= 15) {
            for (j=14;j<trb_info->packet_num;j++) {
                cbw_buf->resv[i] = trb_info->buffer_size[j] & 0xff;
                cbw_buf->resv[i+1] = (trb_info->buffer_size[j]>> 8) & 0xff;
                i=i+2;
            }
        }
    }
}

int w2_usb_send_packet(struct amlw_hif_scatter_req * scat_req)
{
    struct usb_device *udev = g_udev;
    struct scatterlist *sg;
    struct usb_sg_request sgr = {0};
    int sg_count, sgitem_count;
    unsigned int max_req_size;
    int ttl_len, pkt_offset, page_num;
    //struct txdesc_host *txdesc_host;

    unsigned int last_page_size ;
    unsigned int ttl_page_num = 0;
    int ret;
    //int i;

    /* fill SG entries */
    sg = scat_req->sgentries;
    pkt_offset = 0; // reminder
    sgitem_count = 0; // count of scatterlist
    max_req_size = USB_MAX_TRANS_SIZE;
    udev->bus->sg_tablesize = MAXSG_SIZE;

    while (sgitem_count < scat_req->scat_count)
    {
        ttl_len = 0;
        sg_count = 0;
        page_num = 0;
        sg_init_table(sg, MAXSG_SIZE);
        /* assemble SG list */
        while (sgitem_count < scat_req->scat_count)
        {
            int packet_len = 0;
            unsigned char *pdata = NULL;
            /* coverity[MISSING_LOCK] --miss aml_hw.tx_desc_lock*/
            packet_len = scat_req->scat_list[sgitem_count].len;
            /* coverity[MISSING_LOCK] --miss aml_hw.tx_desc_lock*/
            pdata = scat_req->scat_list[sgitem_count].packet;
            /* coverity[value_overwrite] --Overwriting previous write to "page_num"*/
            page_num = scat_req->scat_list[sgitem_count].page_num;

            if (sg_count > (MAXSG_SIZE - page_num))
            {
                AML_ERR("sg_count > MAXSG_SIZE, sg_count:%d, page_num:%d, scat_count:%d\n", sg_count, page_num, scat_req->scat_count);
                break;
            }
            ttl_page_num += page_num;
            last_page_size = packet_len - (page_num - 1) * USB_PAGE_LEN;

            if (page_num == 1)
            {
                //AML_INFO("sg_count:%d, page_num:%d, scat_count:%d\n", sg_count, page_num, scat_req->scat_count);
                sg_set_buf(&scat_req->sgentries[sg_count], pdata, packet_len);
                sg_count++;
                ttl_len += packet_len;
            }
            sgitem_count++;
        }

        ret = usb_sg_init(&sgr, udev, usb_sndbulkpipe(udev, USB_EP1), 0, scat_req->sgentries,
            sg_count, 0, GFP_NOIO);

        if (ret)
        {
            AML_ERR("usb_sg_init fail ret = %d\n", ret);
            return ret;
        }

        usb_sg_wait(&sgr);
        if (sgr.status != 0)
        {
            AML_ERR("usb_sg_wait fail  %d\n", sgr.status);
            return -1;
        }

    }
    return 0;
}

int w2_usb_send_frame(struct amlw_hif_scatter_req * pframe)
{
    int ret;
    int i;
    unsigned int actual_length = 0;
    struct usb_device *udev = g_udev;


    memset(&pframe->page, 0, sizeof(struct tx_trb_info_ex));
#ifdef CONFIG_AML_RECOVERY
    if (!usb_bus_available()) {
        AML_ERR("bus not available, do not read/write now!\n");
        w2_usb_scat_complete(pframe);
        return 0;
    }
#endif
    USB_BEGIN_LOCK();
    /* build page_info array */
    pframe->page.packet_num = pframe->scat_count;

    for (i = 0; i < pframe->scat_count; i++)
    {
        /* coverity[MISSING_LOCK] --miss aml_hw.tx_desc_lock*/
        pframe->page.buffer_size[i] = pframe->scat_list[i].len;
    }
    aml_usb_build_tx_packet_info(g_cmd_buf, CMD_WRITE_PACKET, &(pframe->page));
    /* cmd stage */
    ret = auc_bulk_msg(udev, usb_sndbulkpipe(udev, USB_EP1),
        g_cmd_buf, sizeof(*g_cmd_buf), &actual_length, AML_USB_CONTROL_MSG_TIMEOUT);
    if (ret) {
        AML_ERR("Failed to usb_bulk_msg, ret %d\n",ret);
        w2_usb_scat_complete(pframe);
        USB_END_LOCK();
        return 1;
    }

    auc_cmd_rxrd_clear();
    w2_usb_send_packet(pframe);

    w2_usb_scat_complete(pframe);

    USB_END_LOCK();
    return actual_length;
}

//EP5 read tx cfm when irq indicate, no need to lock
int w2_usb_read_tx_cfm(unsigned char *pdata, unsigned int len, unsigned int *actual_length)
{
    int ret = 0;
    struct usb_device *udev = g_udev;

    /* data stage */
    //ret = auc_bulk_msg(udev, usb_rcvbulkpipe(udev, USB_EP5), (void *)pdata, len, actual_length, 100);
    ret = usb_bulk_msg(udev, usb_rcvbulkpipe(udev, USB_EP5), (void *)pdata, len, actual_length, 100);
    if (ret) {
        AML_ERR("Failed to usb_bulk_msg, ret %d, len: %d, addr:%px\n", ret, len, pdata);
        return -1;
    }

    return 0;
}

void auc_w2_ops_init(void)
{
    struct auc_hif_ops *ops = &g_auc_hif_ops;
    if (!g_auc_kmalloc_buf) {
        g_auc_kmalloc_buf = (unsigned char *)aml_mem_prealloc(PREALLOC_BUF_BUS, PREALLOC_BUF_BUS_SIZE);
        if (!g_auc_kmalloc_buf) {
             AML_ERR(">>>usb kmalloc failed!");
        }
    }

    ops->hi_write_word = auc_write_word_by_ep_for_wifi;
    ops->hi_read_word = auc_read_word_by_ep_for_wifi;
    ops->hi_write_sram = auc_write_sram_by_ep_for_wifi;
    ops->hi_read_sram = auc_read_sram_by_ep_for_wifi;
    ops->hi_rx_buffer_read = auc_rx_buffer_read;
    ops->hi_get_scatreq = aml_usb_scatter_req_get;
    ops->hi_cleanup_scat = aml_usb_cleanup_scatter;
    ops->hi_enable_scat = w2_usb_enable_scatter;
    ops->hi_write_word_for_bt = auc_write_word_by_ep_for_bt;
    ops->hi_read_word_for_bt = auc_read_word_by_ep_for_bt;
    ops->hi_write_sram_for_bt = auc_write_sram_by_ep_for_bt;
    ops->hi_read_sram_for_bt = auc_read_sram_by_ep_for_bt;
    ops->hi_send_frame = w2_usb_send_frame;
    ops->hi_read_tx_cfm = w2_usb_read_tx_cfm;
    auc_driver_insmoded = 1;
}

#ifdef ICCM_CHECK
extern unsigned char buf_iccm_rd[ICCM_BUFFER_RD_LEN];
#endif

int wifi_iccm_download(unsigned char* addr, unsigned int len)
{
    unsigned int base_addr = MAC_ICCM_AHB_BASE + ICCM_ROM_LEN;
    unsigned int offset = 0;
    unsigned int trans_len = 0;
    int ret = 0;
    int actual_length = 0;
    struct usb_device *udev = g_udev;
#ifdef ICCM_CHECK
    unsigned char *buf_tmp = buf_iccm_rd;
    memset(buf_iccm_rd, 0, ICCM_BUFFER_RD_LEN);
#endif

    USB_BEGIN_LOCK();
    auc_build_cbw(g_cmd_buf, AML_XFER_TO_DEVICE, len, CMD_DOWNLOAD_WIFI, base_addr, 0, len);

    /* cmd stage */
    ret = auc_bulk_msg(udev, usb_sndbulkpipe(udev, USB_EP1), (void *)g_cmd_buf, sizeof(*g_cmd_buf), &actual_length, AML_USB_CONTROL_MSG_TIMEOUT);
    if (ret) {
        AML_ERR("Failed to usb_bulk_msg, ret %d\n", ret);
        USB_END_LOCK();
        return 1;
    }

    while (offset < len) {
        if ((len - offset) > USB_MAX_TRANS_SIZE) {
            trans_len = USB_MAX_TRANS_SIZE;
        } else {
            trans_len = len - offset;
        }

        /* data stage */
        ret = auc_bulk_msg(udev, usb_sndbulkpipe(udev, USB_EP1), (void*)addr+offset, trans_len, &actual_length, AML_USB_CONTROL_MSG_TIMEOUT);
        if (ret) {
            AML_ERR("Failed to usb_bulk_msg, ret %d\n", ret);
            USB_END_LOCK();
            return 1;
        }

        AML_INFO("wifi_iccm_download actual_length = 0x%x; len: 0x%x; offset: 0x%x\n", actual_length, len, offset);
        offset += actual_length;
    }

    USB_END_LOCK();
#ifdef ICCM_CHECK
    auc_read_sram_by_ep_for_wifi(buf_tmp, (void*)(uintptr_t)base_addr, len, USB_EP2);

    if (memcmp(buf_tmp, addr, len)) {
        AML_ERR("write ICCM ERROR!!!! \n");
    } else {
        AML_INFO("write ICCM SUCCESS!!!! \n");
    }
#endif
    return 0;
}

int wifi_dccm_download(unsigned char* addr, unsigned int len, unsigned int start)
{
    unsigned int base_addr = 0x00d00000 + start;
    unsigned int offset = 0;
    unsigned int trans_len = 0;
    int ret = 0;
    int actual_length = 0;
    struct usb_device *udev = g_udev;
#ifdef ICCM_CHECK
    unsigned char *buf_tmp = buf_iccm_rd;
    memset(buf_iccm_rd, 0, ICCM_BUFFER_RD_LEN);
#endif

    AML_INFO("dccm_downed, addr 0x%p, len %d \n", addr, len);
    USB_BEGIN_LOCK();
    auc_build_cbw(g_cmd_buf, AML_XFER_TO_DEVICE, len, CMD_DOWNLOAD_WIFI, base_addr, 0, len);
    /* cmd stage */
    ret = auc_bulk_msg(udev, usb_sndbulkpipe(udev, USB_EP1), (void*)g_cmd_buf,sizeof(*g_cmd_buf),&actual_length, AML_USB_CONTROL_MSG_TIMEOUT);
    if (ret) {
        AML_ERR("Failed to usb_bulk_msg, ret %d\n", ret);
        USB_END_LOCK();
        return 1;
    }

    while (offset < len) {
        if ((len - offset) > USB_MAX_TRANS_SIZE) {
            trans_len = USB_MAX_TRANS_SIZE;
        } else {
            trans_len = len - offset;
        }

        /* data stage */
        ret = auc_bulk_msg(udev, usb_sndbulkpipe(udev, USB_EP1),(void *)addr+offset, trans_len, &actual_length, AML_USB_CONTROL_MSG_TIMEOUT);
        if (ret) {
            AML_ERR("Failed to usb_bulk_msg, ret %d\n",ret);
            USB_END_LOCK();
            return 1;
        }

        AML_INFO("wifi_dccm_download actual_length = 0x%x; len: 0x%x; offset: 0x%x\n", actual_length, len, offset);
        offset += actual_length;
    }

    USB_END_LOCK();
#ifdef ICCM_CHECK
    auc_read_sram_by_ep_for_wifi(buf_tmp, (void*)(uintptr_t)base_addr, len, USB_EP2);
    if (memcmp(buf_tmp, addr, len)) {
        AML_ERR("write DCCM ERROR!!!! \n");
    } else {
        AML_INFO("write DCCM SUCCESS!!!! \n");
    }
#endif

    return 0;
}

int aml_usb_download_suspend_or_rf_fw(unsigned char fw_type, unsigned int fw_download_timeout)
{
    unsigned int len = WIFI_SUSPEND_CODE_LEN;
    unsigned char *kmalloc_buf = NULL;
    struct auc_hif_ops *hif_ops = &g_auc_hif_ops;

    kmalloc_buf = (unsigned char *)aml_mem_prealloc(PREALLOC_BUF_FW_DL, len);
    if (kmalloc_buf == NULL) {
        AML_ERR("kmalloc buf fail\n");
        return -ENOMEM;
    }

    if (fw_type)
        kmalloc_buf += len;

    //test kmalloc buf content
    AML_INFO("start fw:%d download, data:%08x, timeout:%d\n", fw_type, *(unsigned int *)&kmalloc_buf[0], fw_download_timeout);
    hif_ops->hi_write_sram((unsigned char *)kmalloc_buf, (unsigned char *)WIFI_SUSPEND_CODE_ADDR, len, USB_EP4);

#if 0
    memset(buf_iccm_rd, 0, ICCM_BUFFER_RD_LEN);
    hif_ops->hi_read_sram(buf_iccm_rd, (unsigned char*)(SYS_TYPE)base_addr, len, USB_EP4);
    if (memcmp(buf_iccm_rd, kmalloc_buf, len - 8)) {
        if (fw_type) {
            AML_ERR("suspend fw download fail!\n");
        } else {
            AML_ERR("rf fw download fail!\n");
        }
        //return -1;
    } else {
        if (fw_type) {
            AML_INFO("suspend fw download success!\n");
        } else {
            AML_INFO("rf fw download success!\n");
        }
    }
#endif

    return 0;
}

unsigned char aml_usb_download_host_cmd_fw(unsigned char cmd_index)
{
    unsigned int len = HOST_CMD_SIZE;
    unsigned char *kmalloc_buf = NULL;
    struct auc_hif_ops *hif_ops = &g_auc_hif_ops;

    kmalloc_buf = ((unsigned char *)aml_mem_prealloc(PREALLOC_BUF_FW_DL, len) + (2 * WIFI_SUSPEND_CODE_LEN));
    if (kmalloc_buf == NULL) {
        AML_ERR("kmalloc buf fail\n");
        return -ENOMEM;
    }

    kmalloc_buf += cmd_index * len;

    //test kmalloc buf content
    //AML_INFO("start host cmd download, kmalloc buf:%08x, data:%08x, cmd_index:%d\n",
    //    kmalloc_buf, *(unsigned int *)&kmalloc_buf[0], cmd_index);
    hif_ops->hi_write_sram((unsigned char *)kmalloc_buf, (unsigned char *)HOST_CMD_CODE_ADDR, len, USB_EP4);

#if 0
    memset(buf_iccm_rd, 0, ICCM_BUFFER_RD_LEN);
    hif_ops->hi_read_sram(buf_iccm_rd, (unsigned char*)(SYS_TYPE)base_addr, len, USB_EP4);
    if (memcmp(buf_iccm_rd, kmalloc_buf, len - 8)) {
        AML_ERR("host cmd download fail!\n");
        //return -1;

    } else {
        AML_ERR("host cmd download success!\n");
    }
#endif

    return 0;
}


int wifi_fw_download(char * firmware_filename)
{
    int i = 0, err = 0;
    unsigned int tmp_val = 0;
    unsigned int len = ICCM_RAM_LEN;
    char tmp_buf[9] = {0};
    unsigned char *src = NULL;
    unsigned char *kmalloc_buf = NULL;
    const struct firmware *fw = NULL;
    unsigned int offset = 0;
    unsigned int fw_info_len = 0;
    unsigned char fw_branch_len = 0;
    unsigned char fw_author_len = 0;
    unsigned char fw_date_len = 0;

    AML_FN_ENTRY();
    err = request_firmware(&fw, firmware_filename, &g_udev->dev);
    if (err) {
        AML_ERR("request firmware fail!\n");
        return err;
    }

    src = (unsigned char *)fw->data + (offset / 4) * BYTE_IN_LINE;
    kmalloc_buf = (unsigned char *)aml_mem_prealloc(PREALLOC_BUF_FW_DL, len);
    if (kmalloc_buf == NULL) {
        AML_ERR("kmalloc buf fail\n");
        release_firmware(fw);
        return -ENOMEM;
    }

    for (i = 0; i < len /4; i++) {
        tmp_buf[8] = 0;
        strncpy(tmp_buf, (char *)src, 8);
        if ((err = kstrtouint(tmp_buf, 16, &tmp_val))) {
            release_firmware(fw);
            return err;
        }
        *(unsigned int *)&kmalloc_buf[4 * i] = __swab32(tmp_val);
        src += BYTE_IN_LINE;
    }

    AML_INFO("start iccm download!, kmalloc_buf:%px\n", kmalloc_buf);
    wifi_iccm_download(kmalloc_buf, len);

    memset(kmalloc_buf, 0, len);
    src = (unsigned char *)fw->data + (ICCM_ALL_LEN / 4) * BYTE_IN_LINE;

    /* download dccm section1, 0 - usb_data_start */
    len = ALIGN(DCCM_ALL_LEN, 4) - (6 * 1024/*stack*/ + 2 * 1024/*usb data*/);
    for (i = 0; i < len / 4; i++) {
        tmp_buf[8] = 0;
        strncpy(tmp_buf, (char *)src, 8);
        if ((err = kstrtouint(tmp_buf, 16, &tmp_val))) {
            release_firmware(fw);
            return err;
        }
        *(unsigned int *)&kmalloc_buf[4 * i] = __swab32(tmp_val);
        src += BYTE_IN_LINE;
    }

    AML_INFO("start dccm download!\n");

    wifi_dccm_download(kmalloc_buf, len, 0);

    memset(kmalloc_buf, 0, len);
    offset = ICCM_ALL_LEN - WIFI_SUSPEND_CODE_LEN - WIFI_CMD_CODE_LEN;
    len = WIFI_SUSPEND_CODE_LEN;
    src = (unsigned char *)fw->data + (offset / 4) * BYTE_IN_LINE;

    for (i = 0; i < len /4; i++) {
        tmp_buf[8] = 0;
        strncpy(tmp_buf, (char *)src, 8);
        if ((err = kstrtouint(tmp_buf, 16, &tmp_val))) {
            release_firmware(fw);
            return err;
        }
        *(unsigned int *)&kmalloc_buf[4 * i] = __swab32(tmp_val);
        src += BYTE_IN_LINE;
    }

    AML_INFO("save rf fw :%08x!\n", *(unsigned int *)&kmalloc_buf[0]);

    src = (unsigned char *)fw->data + ((ICCM_ALL_LEN + DCCM_ALL_LEN) / 4) * BYTE_IN_LINE;
    kmalloc_buf += len;
    len += (HOST_CMD_COUNT * HOST_CMD_SIZE) + 8;

    for (i = 0; i < len /4; i++) {
        tmp_buf[8] = 0;
        strncpy(tmp_buf, (char *)src, 8);
        if ((err = kstrtouint(tmp_buf, 16, &tmp_val))) {
            release_firmware(fw);
            AML_INFO("download fail, i:%d, len:%d\n", i, len);
            return err;
        }
        *(unsigned int *)&kmalloc_buf[4 * i] = __swab32(tmp_val);
        src += BYTE_IN_LINE;
    }

    kmalloc_buf += len - 4;
    fw_info_len = *(unsigned int *)kmalloc_buf;
    fw_branch_len = (fw_info_len >> 8) & 0xff;
    fw_author_len = (fw_info_len >> 16) & 0xff;
    fw_date_len = (fw_info_len >> 24) & 0xff;
    //AML_INFO("fw_info_len:%02x, fw_branch_len:%02x, fw_author_len:%02x, fw_date_len:%02x\n",
    //    fw_info_len, fw_branch_len, fw_author_len, fw_date_len);

    fw_info_len = fw_branch_len + fw_author_len + fw_date_len + 2;
    src = (unsigned char *)fw->data + ((ICCM_ALL_LEN + DCCM_ALL_LEN + len) / 4) * BYTE_IN_LINE;
    kmalloc_buf += 4;
    strncpy(kmalloc_buf, (char *)src, fw_info_len);
    release_firmware(fw);

    AML_INFO("finished fw downloading!\n");
    return 0;
}

int start_wifi(void)
{
    int ret = 0;
    int actual_length = 0;
    struct usb_device *udev = g_udev;

    USB_BEGIN_LOCK();
    auc_build_cbw(g_cmd_buf, AML_XFER_TO_DEVICE, 0, CMD_START_WIFI, 0, 0, 0);
    /* cmd stage */
    ret = auc_bulk_msg(udev, usb_sndbulkpipe(udev, USB_EP1),(void *) g_cmd_buf, sizeof(*g_cmd_buf), &actual_length, AML_USB_CONTROL_MSG_TIMEOUT);
    USB_END_LOCK();
    if (ret) {
        AML_ERR("Failed to usb_bulk_msg, ret %d\n", ret);
        return 1;
    }

    AML_INFO("start_wifi finished!\n");

    return 0;
}

EXPORT_SYMBOL(wifi_fw_download);
EXPORT_SYMBOL(start_wifi);
EXPORT_SYMBOL(aml_usb_download_suspend_or_rf_fw);
EXPORT_SYMBOL(aml_usb_download_host_cmd_fw);
EXPORT_SYMBOL(w2_usb_scat_complete);
