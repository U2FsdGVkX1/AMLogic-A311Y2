/**
 ******************************************************************************
 *
 * @file aml_roku_custom.h
 *
 * Copyright (C) Amlogic 2012-2021
 *
 ******************************************************************************
 */

#ifndef _AML_ROKU_CUSTOM_H_
#define _AML_ROKU_CUSTOM_H_

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0))
#define aml_proc_ops proc_ops
#else
#define aml_proc_ops file_operations
#endif

#define AML_PROC_HDL_TYPE_SEQ 0
#define AML_PROC_HDL_TYPE_SSEQ 1
#define AML_PROC_HDL_TYPE_SZSEQ 2

#define RX_AMPDU_ACCEPT 255
#define RX_AMPDU_SIZE 255
#define BACKOP_MS 100
#define MAX_CHAN_SCAN_CNT 1
#define SCAN_NUM_EACH_CH 255
#define PROBE_SSID_NUM_EACH_SCAN 2

/// Duration on channel (in ms) when scanning For ROKU
#define ROKU_SCAN_ACTIVE_DURATION    40
#define ROKU_SCAN_PASSIVE_DURATION   110
/// Probe num when scan For ROKU
#define ROKU_PROBE_NUM_EACH_SCAN 2

#define ROKU_PROBE_VENDOR_IE 0xB83E59
#define ROKU_PROBE_VENDOR_TYPE 2
#define ROKU_ASOC_VENDOR_IE 0xC83A6B
#define ROKU_ASOC_VENDOR_TYPE 0
#define ROKU_LEGACY_PROBE_LEN 50
#define ROKU_WFD_PROBE_LEN 80

struct aml_proc_hdl {
    char *name;
    u8 type;
    union {
        int (*show)(struct seq_file *, void *);
        struct seq_operations *seq_op;
        struct {
            int (*show)(struct seq_file *, void *);
            size_t size;
            } sz;
        } u;
    ssize_t (*write)(struct file *file, const char __user *buffer, size_t count, loff_t *pos, void *data);
};

enum {
    PNO_SEC_MODE_NONE = 0,
    PNO_SEC_MODE_OPEN,
    PNO_SEC_MODE_WEP,
    PNO_SEC_MODE_WPA,
    PNO_SEC_MODE_WPA2,
    PNO_SEC_MODE_MAX
};

#define AML_PROC_HDL_SSEQ(_name, _show, _write) \
        { .name = _name, .type = AML_PROC_HDL_TYPE_SSEQ, .u.show = (int (*)(struct seq_file *, void *))_show, .write = _write }

#define PROC_FILE_READ_FUNC(name)                                       \
    static ssize_t aml_proc_##name##_read(struct file *file,            \
                                          char __user *user_buf,        \
                                          size_t count, loff_t *ppos);

#define PROC_FILE_WRITE_FUNC(name)                                      \
    static ssize_t aml_proc_##name##_write(struct file *file,           \
                                           const char __user *user_buf, \
                                           size_t count, loff_t *ppos)
#define AML_PROC_FILE_R_OPS(name)                           \
    PROC_FILE_READ_FUNC(name);                              \
static const struct file_operations aml_proc_##name##_ops = {  \
    .owner = THIS_MODULE,                                   \
    .read = aml_proc_##name##_read,                         \
};

#define SYSFS_RO_FILE_OPS(name) DEVICE_ATTR(name, S_IRUGO, aml_sysfs_##name##_read, NULL)
#define SYSFS_WO_FILE_OPS(name) DEVICE_ATTR(name, S_IWUSR|S_IWGRP, NULL, aml_sysfs_##name##_write)
#define SYSFS_RW_FILE_OPS(name)     \
    DEVICE_ATTR(name, S_IWUSR|S_IWGRP|S_IRUGO, aml_sysfs_##name##_read, aml_sysfs_##name##_write)

extern struct aml_hw *g_aml_hw;
extern struct aml_pm_type g_wifi_pm;

#endif
