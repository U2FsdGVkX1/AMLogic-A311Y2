/* SPDX-License-Identifier: GPL-2.0 */
/*
* Copyright (C) 202X Original Author (retain original author information)
* Copyright (C) 202X Amlogic, Inc. All rights reserved.
*
* Description:
*/
#define AML_MODULE  USB

#include <linux/version.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 11, 0)
#include <linux/sched/clock.h>
#endif

#include "usb_common.h"
#include "chip_ana_reg.h"
#include "wifi_intf_addr.h"
#include "sg_common.h"
#include "fi_sdio.h"
#include "w2_usb.h"
#include "aml_interface.h"
#include "fi_w2_sdio.h"
#include "chip_intf_reg.h"
#include "aml_interface.h"
#include "aml_log.h"
#include "chip_bt_pmu_reg.h"

struct auc_hif_ops g_auc_hif_ops;
struct usb_device *g_udev = NULL;
struct aml_hwif_usb g_hwif_usb;
unsigned char auc_driver_insmoded;
unsigned char auc_wifi_in_insmod;
unsigned char g_usb_after_probe;
unsigned char g_chip_function_ctrl = 0;
unsigned int auc_prob_cnt = 0;
bool suspend_need_fill_urb = false;

struct crg_msc_cbw *g_cmd_buf = NULL;
unsigned char *g_kmalloc_buf = NULL;
struct mutex auc_usb_mutex;

struct wakeup_source *aml_wifi_wakeup_source;

extern unsigned char wifi_drv_rmmod_ongoing;
extern struct aml_bus_state_detect bus_state_detect;
extern struct aml_pm_type g_wifi_pm;
extern void auc_w2_ops_init(void);
/*for bluetooth get read/write point*/
int bt_wt_ptr = 0;
int bt_rd_ptr = 0;
/*co-exist flag for bt/wifi mode*/
int coex_flag = 0;

#define EP4_INIT_FLAG_ADDR (0xd2e778)

//use for suspend(kill)/resume(submit) usb_urb
static struct urb *g_usb_urb = NULL;
void auc_irq_urb_set(struct urb *urb)
{
    g_usb_urb = urb;
}
EXPORT_SYMBOL(auc_irq_urb_set);

void chip_function_select_usb(void) {
    switch (g_udev->descriptor.idProduct) {
        case W2lu_W265U2_PRODUCT_B_AMLOGIC_EFUSE:
            g_chip_function_ctrl |= CHIP_FUNCTION_DISABLE_154;
            break;

        case W2lu_W255U1_PRODUCT_B_AMLOGIC_EFUSE:
            g_chip_function_ctrl |= CHIP_FUNCTION_DISABLE_154;
            break;

        case W2lu_W265U2M_PRODUCT_B_AMLOGIC_EFUSE:
        default:
            g_chip_function_ctrl = 0;//full function
            break;
    }
}

bool usb_bus_available(void)
{
    if (bus_state_detect.bus_err) {
        AML_ERR("bus err\n");
        return false;
    }

    if (bus_state_detect.usb_disconnect) {
        AML_ERR("usb bus disconnect\n");
        return false;
    }

    if (bus_state_detect.bus_reset_ongoing) {
        AML_ERR("bus reset ongoing\n");
        return false;
    }

    return true;
}


static int auc_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    g_udev = usb_get_dev(interface_to_usbdev(interface));
    memset(g_kmalloc_buf, 0,  1024*20);
    memset(g_cmd_buf, 0, sizeof(struct crg_msc_cbw ));

    auc_prob_cnt++;

    auc_w2_ops_init();
    g_auc_hif_ops.hi_enable_scat();

#ifdef CONFIG_PM
    if (atomic_read(&g_wifi_pm.bus_suspend_cnt) != 0) {
        atomic_set(&g_wifi_pm.bus_suspend_cnt, 0);
    }
#endif

    if ((auc_prob_cnt > 1) && g_usb_urb) {
        AML_INFO("update udev new:%px , old: %px, auc prob cnt %d\n", g_udev, g_usb_urb->dev, auc_prob_cnt);

        if (bus_state_detect.usb_suspend)
            suspend_need_fill_urb = true;
        else
            /*host recovery set 0, fw recovery set 1.*/
            bus_state_detect.bus_err = 0;

        g_usb_urb->dev = g_udev;
    }

    g_usb_after_probe = 1;
    bus_state_detect.usb_disconnect = 0;
    bus_state_detect.bus_reset_ongoing = 0;
    chip_function_select_usb();

    AML_INFO("pid is %04x, function ctrl:%02x\n",
        g_udev->descriptor.idProduct, g_chip_function_ctrl);

#ifdef CONFIG_USB_HOTPLUG
    if (bus_state_detect.auc_wifi_enable_func)
        bus_state_detect.auc_wifi_enable_func();
    bus_state_detect.usb_unplug = 0;
#endif

    return 0;
}


static void auc_disconnect(struct usb_interface *interface)
{
    usb_set_intfdata(interface, NULL);
    usb_put_dev(g_udev);
    g_usb_after_probe = 0;
    bus_state_detect.usb_disconnect = 1;
    atomic_set(&g_wifi_pm.bus_suspend_cnt, 0);
    atomic_set(&g_wifi_pm.drv_suspend_cnt, 0);
    AML_INFO("--------aml_usb:disconnect-------\n");

#ifdef CONFIG_USB_HOTPLUG
    if (bus_state_detect.auc_wifi_disable_func)
        bus_state_detect.auc_wifi_disable_func();
#endif
}

#ifdef CONFIG_PM
static int auc_reset_resume(struct usb_interface *interface)
{
    int ret = 0;
    atomic_set(&g_wifi_pm.bus_suspend_cnt, 0);

    if (atomic_read(&g_wifi_pm.wifi_enable))
    {
        if (g_usb_urb)
        {
            USB_BEGIN_LOCK();
            ret = usb_submit_urb(g_usb_urb, GFP_ATOMIC);
            USB_END_LOCK();
            if (ret < 0) {
                AML_ERR("usb_submit_urb failed %d\n", ret);
            }
        }
    }

    //reset ep4
    auc_write_word_by_ep_for_wifi(EP4_INIT_FLAG_ADDR, 0 , USB_EP1);
    bus_state_detect.usb_suspend = 0;

    AML_INFO("--------aml_usb:reset done-------\n");
    return 0;
}

static int auc_suspend(struct usb_interface *interface,pm_message_t state)
{
    u64 start_time_ns;
    u64 elapsed_time_ns = 0;
    u64 wait_wifi_time_ns = 12000000000; //wait wifi 12s

    AML_INFO("auc_suspend!! \n");
    elapsed_time_ns = 0;
    if (atomic_read(&g_wifi_pm.wifi_enable))
    {
        start_time_ns = sched_clock();
        while ((atomic_read(&g_wifi_pm.drv_suspend_cnt) == 0) &&
                (usb_bus_available()) &&
                (bus_state_detect.is_recy_ongoing == 0) &&
                (elapsed_time_ns < wait_wifi_time_ns))
        {
            elapsed_time_ns = sched_clock() - start_time_ns;
            msleep(10);
        }

        if (elapsed_time_ns >= wait_wifi_time_ns)
        {
            AML_INFO("wifi suspend fail, return\n");
        }

        // Detect a bus error or ongoing recovery,
        // exit immediately to prevent blocking the kernel USB resume call.
        if (!usb_bus_available() || bus_state_detect.is_recy_ongoing)
        {
            AML_ERR("Detect a bus error or ongoing recovery, return\n");
            return 0;
        }

        USB_BEGIN_LOCK();
        if (g_usb_urb)
        {
            if (g_usb_urb && g_usb_urb->status != 0) {
                AML_ERR("usb_kill_urb\n");
                usb_kill_urb((g_usb_urb));
            }
        }
        USB_END_LOCK();
    }

    atomic_set(&g_wifi_pm.bus_suspend_cnt, 1);
    bus_state_detect.usb_suspend = 1;

    AML_INFO("---------aml_usb suspend-------\n");
    return 0;
}

static int auc_resume(struct usb_interface *interface)
{
    int ret = 0;

    if (atomic_read(&g_wifi_pm.wifi_enable))
    {
        if (g_usb_urb)
        {
            USB_BEGIN_LOCK();
            ret = usb_submit_urb(g_usb_urb, GFP_ATOMIC);
            USB_END_LOCK();
            if (ret < 0) {
            AML_ERR("usb_submit_urb failed %d\n", ret);
            }
        }
    }

    atomic_set(&g_wifi_pm.bus_suspend_cnt, 0);
    bus_state_detect.usb_suspend = 0;
    AML_INFO("---------aml_usb auc_resume -------\n");
    return 0;
}
#endif

extern lp_shutdown_func g_lp_wifi_shutdown_func;
extern bt_shutdown_func g_bt_shutdown_func;
#if LINUX_VERSION_CODE <= KERNEL_VERSION(6, 8, 0)
void auc_shutdown(struct device *dev)
#else
void auc_shutdown(struct usb_interface *interface)
#endif
{
    //Mask interrupt reporting to the host
    atomic_set(&g_wifi_pm.is_shut_down, 2);
    AML_INFO("aml_usb_shutdown begin \n" );

    // Notify fw to enter shutdown mode
    if (g_bt_shutdown_func != NULL)
    {
        g_bt_shutdown_func();
    }
    if (g_lp_wifi_shutdown_func != NULL)
    {
        g_lp_wifi_shutdown_func();
    }
    //notify fw shutdown
    auc_write_word_by_ep_for_wifi(RG_AON_A16, auc_read_word_by_ep_for_wifi(RG_AON_A16, USB_EP1)|BIT(28) ,USB_EP1);

    atomic_set(&g_wifi_pm.is_shut_down, 1);
}


static const struct usb_device_id auc_devices[] =
{
    {USB_DEVICE(W2_VENDOR,W2_PRODUCT)},
    {USB_DEVICE(W2u_VENDOR_AMLOGIC_EFUSE,W2u_PRODUCT_A_AMLOGIC_EFUSE)},
    {USB_DEVICE(W2u_VENDOR_AMLOGIC_EFUSE,W2u_PRODUCT_B_AMLOGIC_EFUSE)},
    {USB_DEVICE(W2u_VENDOR_AMLOGIC_EFUSE,W2lu_W265U2M_PRODUCT_A_AMLOGIC_EFUSE)},
    {USB_DEVICE(W2u_VENDOR_AMLOGIC_EFUSE,W2lu_W265U2_PRODUCT_A_AMLOGIC_EFUSE)},
    {USB_DEVICE(W2u_VENDOR_AMLOGIC_EFUSE,W2lu_W255U1_PRODUCT_A_AMLOGIC_EFUSE)},
    {USB_DEVICE(W2u_VENDOR_AMLOGIC_EFUSE,W2lu_W265U2M_PRODUCT_B_AMLOGIC_EFUSE)},
    {USB_DEVICE(W2u_VENDOR_AMLOGIC_EFUSE,W2lu_W265U2_PRODUCT_B_AMLOGIC_EFUSE)},
    {USB_DEVICE(W2u_VENDOR_AMLOGIC_EFUSE,W2lu_W255U1_PRODUCT_B_AMLOGIC_EFUSE)},
    {}
};

MODULE_DEVICE_TABLE(usb, auc_devices);

static struct usb_driver aml_usb_common_driver = {

    .name = "aml_usb_common",
    .id_table = auc_devices,
    .probe = auc_probe,
    .disconnect = auc_disconnect,
#ifdef CONFIG_PM
    .reset_resume = auc_reset_resume,
    .suspend = auc_suspend,
    .resume = auc_resume,
#endif
#if LINUX_VERSION_CODE <= KERNEL_VERSION(6, 8, 0)
    .drvwrap.driver.shutdown = auc_shutdown,
#else
    .shutdown = auc_shutdown,
#endif
};

/**
 * aml_usb_set_bus_err - Set the bus error state and handle system wakeup
 *
 * Updates the bus error state. If `bus_err` is non-zero, and if the
 * wakeup source is initialized but not active, the system is kept awake
 * to prevent suspend during recovery.
 *
 * @bus_err: The bus error state. A non-zero value indicates an error.
 */
void aml_usb_set_bus_err(unsigned char bus_err)
{
    if (bus_err) {
        // Wake up the system and prevent it from entering
        // suspend during the upcoming recovery process.
        if (aml_wifi_wakeup_source && (!aml_wifi_wakeup_source->active)) {
            __pm_stay_awake(aml_wifi_wakeup_source);
        } else {
            AML_INFO("aml_wifi_wakeup_source is not initialized or active already\n");
        }
    }

    bus_state_detect.bus_err = bus_err;

    if (bus_err)
        AML_ERR("Bus error state updated: %d\n", bus_err);
}
EXPORT_SYMBOL(aml_usb_set_bus_err);

int aml_usb_insmod(void)
{
    int err = 0;

    g_cmd_buf = ZMALLOC(sizeof(*g_cmd_buf), "cmd stage", GFP_DMA | GFP_ATOMIC);
    if (!g_cmd_buf) {
        AML_ERR("g_cmd_buf malloc fail\n");
        return -ENOMEM;
    }
    g_kmalloc_buf = (unsigned char *)ZMALLOC(20*1024, "reg tmp", GFP_DMA | GFP_ATOMIC);
    if (!g_kmalloc_buf) {
        AML_ERR("data malloc fail\n");
        FREE(g_cmd_buf, "cmd stage");
        return -ENOMEM;
    }
    err = usb_register(&aml_usb_common_driver);
    if (err) {
        AML_ERR("failed to register usb driver: %d \n", err);
    }

    auc_driver_insmoded = 1;
    auc_wifi_in_insmod = 0;
    USB_LOCK_INIT();
    aml_wifi_wakeup_source = wakeup_source_register(
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 4, 0)
                 NULL,
#endif
                 "bus_wakeup_source");

    if (!aml_wifi_wakeup_source) {
        AML_ERR("Failed to create wakeup source\n");
        return -ENOMEM;
    }
    AML_INFO("aml common driver insmod\n");

    return err;
}
EXPORT_SYMBOL(aml_usb_insmod);

void aml_usb_rmmod(void)
{
    usb_deregister(&aml_usb_common_driver);
    auc_driver_insmoded = 0;
    wifi_drv_rmmod_ongoing = 0;
    auc_prob_cnt = 0;
    if (g_auc_hif_ops.hi_cleanup_scat)
        g_auc_hif_ops.hi_cleanup_scat();
    FREE(g_cmd_buf, "cmd stage");
    FREE(g_kmalloc_buf, "reg tmp");
    USB_LOCK_DESTROY();

    aml_wifi_power_on(0);
    msleep(100);
    aml_wifi_power_on(1);

    if (aml_wifi_wakeup_source) {
        wakeup_source_unregister(aml_wifi_wakeup_source);
        aml_wifi_wakeup_source = NULL;
    } else {
       AML_INFO("aml_wifi_wakeup_source is not initialized, unregistering is not required.\n");
    }

   AML_INFO("aml common driver rmsmod\n");
}
EXPORT_SYMBOL(aml_usb_rmmod);

int aml_usb_reset(void)
{
    uint32_t count = 0;
    uint32_t try_cnt = 0;

try_again:
    AML_INFO("******* usb reset begin ******* :%d\n", g_usb_after_probe);

#ifndef CONFIG_PT_MODE
    aml_wifi_power_on(0);
    auc_prob_cnt = 0;

#ifdef CONFIG_USB_HOTPLUG
    while ((g_usb_after_probe)) {
        if (try_cnt >= 2)
            break;
        msleep(5);
        count++;
        if (count > 100) {
            count = 0;
            try_cnt++;
            aml_wifi_power_on(1);
            msleep(50);
            AML_ERR("usb reset fail, try again1(%d)\n", try_cnt);
            goto try_again;
        }
    }
    aml_wifi_power_on(1);

    count = 0;
    while ((!g_usb_after_probe) && try_cnt < 2) {
        msleep(5);
        count++;
        if (count > 100) {
            count = 0;
            try_cnt++;
            AML_ERR("usb reset fail, try again2(%d)\n", try_cnt);
            goto try_again;
        }
    }

    if ((g_usb_after_probe == 0) || (try_cnt >= 2)) {
        AML_ERR("usb reset fail, usb may be unplug\n");
        return -ETIMEDOUT;
    }
#else
    while (g_usb_after_probe) {
        msleep(5);
        count++;
        if (count > 40 && try_cnt <= 3) {
            count = 0;
            try_cnt++;
            aml_wifi_power_on(1);
            msleep(50);
            AML_ERR("usb reset fail, try again(%d)\n", try_cnt);
            goto try_again;
        }
    }
    aml_wifi_power_on(1);

    count = 0;
    try_cnt = 0;
    while ((!g_usb_after_probe) && try_cnt <= 3) {
        msleep(5);
        count++;
        if (count > 200) {
            count = 0;
            try_cnt++;
            AML_ERR("usb reset fail, try again(%d)\n", try_cnt);
            goto try_again;
        }
    };
#endif

    bus_state_detect.bus_reset_ongoing = 0;
    bus_state_detect.bus_err = 0;
    AML_INFO("******* usb reset end *******\n");
#endif

    return 0;
}
EXPORT_SYMBOL(aml_usb_reset);

EXPORT_SYMBOL(g_auc_hif_ops);
EXPORT_SYMBOL(g_udev);
EXPORT_SYMBOL(auc_driver_insmoded);
EXPORT_SYMBOL(auc_wifi_in_insmod);
EXPORT_SYMBOL(auc_usb_mutex);
EXPORT_SYMBOL(g_usb_after_probe);
EXPORT_SYMBOL(bt_wt_ptr);
EXPORT_SYMBOL(bt_rd_ptr);
EXPORT_SYMBOL(coex_flag);
EXPORT_SYMBOL(g_chip_function_ctrl);
EXPORT_SYMBOL(aml_wifi_wakeup_source);
EXPORT_SYMBOL(suspend_need_fill_urb);
