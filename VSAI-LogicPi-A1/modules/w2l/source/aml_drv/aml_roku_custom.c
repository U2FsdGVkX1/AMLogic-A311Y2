/* SPDX-License-Identifier: GPL-2.0 */
/*
* Copyright (C) 202X Original Author (retain original author information)
* Copyright (C) 202X Amlogic, Inc. All rights reserved.
*
* Description:
*/
#include "aml_debugfs.h"
#include "aml_defs.h"
//#include "aml_version_gen.h"
#include "linux/proc_fs.h"
#include "aml_main.h"
#include "aml_msg_tx.h"
#include "aml_rate.h"
#include "aml_regdom.h"
#include <linux/ctype.h>
#include "aml_roku_custom.h"

static struct BAND_INFO {
    unsigned char util_idle;
    unsigned char util_busy;
}g_bandInfo;

static int proc_get_dummy(struct seq_file *m, void *v)
{
    return 0;
}

static ssize_t aml_proc_drv_state_read(struct file *file,
                                       char __user *user_buf,
                                       size_t count, loff_t *ppos)
{
    char buf[20];
    int len = 0;
    int max_len = min_t(size_t, sizeof(buf) - 1, count);
    ssize_t read;

    if (!atomic_read(&g_wifi_pm.wifi_enable)) {
        len += scnprintf(&buf[len], max_len - len, "not_ready\n");
    }
#ifdef CONFIG_AML_RECOVERY
    else if (aml_recy_flags_chk(AML_RECY_STATE_ONGOING)) {
        len += scnprintf(&buf[len], max_len - len, "recovery\n");
    }
#endif
    else {
        len += scnprintf(&buf[len], max_len - len, "ready\n");
    }

    read = simple_read_from_buffer(user_buf, count, ppos, buf, len);

    return read;
}


/***********************************************************************
Temperature = a * | (dout/65536*m)/(1+dout/65536*n) - efuse/65536 | - b

in the above formula:
                     dout = fi_ahb_read(0x00a04940)
                     a = 727.8
                     b = 274.7
                     m = 5.05
                     n = 4.05
***********************************************************************/
void aml_get_temperature(unsigned int* temperature)
{
    struct aml_hw *aml_hw = g_aml_hw;
    TS_STAT0_FIELD_T ts_stat0;
    unsigned int dout;
    unsigned int bouts;
    unsigned int bouts_ptat;
    unsigned int temp_ts, temp_ts_int, temp_ts_dec, minus = 0;

    unsigned int a = 7278;
    unsigned int b = 2747;
    unsigned int m = 505;
    unsigned int n = 405;

    ts_stat0.data = AML_REG_READ(aml_hw->plat, 0, 0x00a04940);
    dout = ts_stat0.b.yout_d2;

    bouts = dout * 1000 / 65536;
    bouts_ptat = (bouts * m)* 1000 / (100000 + bouts * n);
    if (bouts_ptat * a >= b * 1000)
        temp_ts = (bouts_ptat * a - b * 1000) / 10;
    else
    {
        temp_ts = (b * 1000 - bouts_ptat * a) / 10;
        minus = 1;
    }

    temp_ts_int = temp_ts / 1000;
    temp_ts_dec = temp_ts % 1000;

    if (temp_ts_dec > 500)
        temp_ts_int += 1;

    if (minus == 1)
        temp_ts_int = 0 - temp_ts_int;
    *temperature =  temp_ts_int;
}

static ssize_t aml_proc_CurrentTempeature_read(struct file *file,
                                     char __user *user_buf,
                                     size_t count, loff_t *ppos)
{
    char buf[200];
    int len = 0;
    unsigned int temp = 0;
    ssize_t read;

    aml_get_temperature(&temp);
    len += scnprintf(&buf[len], min_t(size_t, sizeof(buf) - 1, count),
                     "CurrentTempeature:%d\n", temp);

    read = simple_read_from_buffer(user_buf, count, ppos, buf, len);
    return read;
}


static ssize_t aml_proc_driver_read(struct file *file,
                                     char __user *user_buf,
                                     size_t count, loff_t *ppos)
{
    struct aml_hw *aml_hw = g_aml_hw;   //file->private_data;
    struct wiphy *wiphy = aml_hw->wiphy;
    int i;
    char buf[1000];
    char dfs_buf[200] = {0};
    int max_len = min_t(size_t, sizeof(buf) - 1, count);
    int len = 0;
    int dfs_buf_len = 0;
    ssize_t read;
    int bw;

    len += scnprintf(&buf[len], max_len - len,
                     "drv_version:%s\n", aml_hw->customer_priv.drv_ver);

    len += scnprintf(&buf[len], max_len - len,
                     "country:%c%c\n", aml_hw->customer_priv.alpha2[0], aml_hw->customer_priv.alpha2[1]);

    if (wiphy->bands[NL80211_BAND_2GHZ] != NULL) {
        struct ieee80211_supported_band *b = wiphy->bands[NL80211_BAND_2GHZ];
        for (i = 0; i < b->n_channels; i++) {
            if (b->channels[i].flags & IEEE80211_CHAN_RADAR) {
                dfs_buf_len += scnprintf(&dfs_buf[dfs_buf_len], sizeof(dfs_buf) - dfs_buf_len,
                                 "%d,", ieee80211_frequency_to_channel(b->channels[i].center_freq));
            }
            else {
                bw = 160;
                if (b->channels[i].flags & IEEE80211_CHAN_NO_160MHZ)
                    bw = 80;
                if (b->channels[i].flags & IEEE80211_CHAN_NO_80MHZ)
                    bw = 40;
                if (b->channels[i].flags &
                    (IEEE80211_CHAN_NO_HT40PLUS | IEEE80211_CHAN_NO_HT40MINUS))
                    bw = 20;
                if (bw > 80)
                    bw = 40;
                if ((b->channels[i].flags & IEEE80211_CHAN_DISABLED) != IEEE80211_CHAN_DISABLED)
                    len += scnprintf(&buf[len], max_len - len, "CH-%d:\tBW_%dMHz\t(flag=0x%x)\n",
                                     ieee80211_frequency_to_channel(b->channels[i].center_freq),
                                     bw, b->channels[i].flags);
            }
        }
    }

    if (wiphy->bands[NL80211_BAND_5GHZ] != NULL) {
        struct ieee80211_supported_band *b = wiphy->bands[NL80211_BAND_5GHZ];
        for (i = 0; i < b->n_channels; i++) {
            if (b->channels[i].flags & IEEE80211_CHAN_RADAR) {
                dfs_buf_len += scnprintf(&dfs_buf[dfs_buf_len], sizeof(dfs_buf) - dfs_buf_len,
                                 "%d,", ieee80211_frequency_to_channel(b->channels[i].center_freq));
            }
            else {
                bw = 160;
                if (b->channels[i].flags & IEEE80211_CHAN_NO_160MHZ)
                    bw = 80;
                if (b->channels[i].flags & IEEE80211_CHAN_NO_80MHZ)
                    bw = 40;
                if (b->channels[i].flags &
                    (IEEE80211_CHAN_NO_HT40PLUS | IEEE80211_CHAN_NO_HT40MINUS))
                    bw = 20;
                if (bw > 80)
                    bw = 80;
                if ((b->channels[i].flags & IEEE80211_CHAN_DISABLED) != IEEE80211_CHAN_DISABLED)
                    len += scnprintf(&buf[len], max_len - len, "CH-%d:\tBW_%dMHz\t(flag=0x%x)\n",
                                     ieee80211_frequency_to_channel(b->channels[i].center_freq),
                                     bw, b->channels[i].flags);
            }
        }
    }

    len += scnprintf(&buf[len], max_len - len,
                     "bypassdfs:%d\n", aml_hw->customer_priv.dfs_on);

    if (aml_hw->customer_priv.dfs_on) {
        int tmp = strlen(dfs_buf);
        if (tmp > 0) {
            dfs_buf[tmp - 1] = '\n';    // '\n' replace ','
            len += scnprintf(&buf[len], max_len - len, "DFS channel:");
            len += scnprintf(&buf[len], max_len - len, "%s\n", dfs_buf);
        }
    }

    read = simple_read_from_buffer(user_buf, count, ppos, buf, len);

    return read;
}

static ssize_t aml_proc_driver_write(struct file *file,
                                     const char __user *user_buf,
                                     size_t count, loff_t *ppos)
{
    struct aml_hw *aml_hw = g_aml_hw; //file->private_data;
    char buf[300] = {0};
    bool is_change = false;

    if (count >= 300 || count < 2) {
        AML_INFO("length error\n");
        return -ENOMEM;
    }

    if (copy_from_user(buf , user_buf, count)) {
        AML_INFO("copy_from_user fail\n");
        return -EFAULT;
    }

    if (strncmp(buf, "bypassdfs", strlen("bypassdfs")) == 0) {
        if ((buf[count - 2] == '1') && (aml_hw->customer_priv.dfs_on == false)) {
            aml_hw->customer_priv.dfs_on = true;
            is_change = true;
        }
        else if ((buf[count - 2] == '0') && (aml_hw->customer_priv.dfs_on == true)) {
            aml_hw->customer_priv.dfs_on = false;
            is_change = true;
        }
        else {
            AML_ERR("bypassdfs info input error! or don't set again\n");
            return -EINVAL;
        }
    }

    if (is_change) {
        aml_send_me_chan_config_req(aml_hw);
    }

    return count;
}


static ssize_t aml_proc_country_read(struct file *file,
                                     char __user *user_buf,
                                     size_t count, loff_t *ppos)
{
    struct aml_hw *aml_hw = g_aml_hw; //file->private_data;
    char buf[200];
    int len = 0;
    ssize_t read;

    len += scnprintf(&buf[len], min_t(size_t, sizeof(buf) - 1, count),
                     "country %c%c\n", aml_hw->customer_priv.alpha2[0], aml_hw->customer_priv.alpha2[1]);

    read = simple_read_from_buffer(user_buf, count, ppos, buf, len);

    return read;
}

static ssize_t aml_proc_country_write(struct file *file,
                                       const char __user *user_buf,
                                       size_t count, loff_t *ppos)
{
    struct aml_hw *aml_hw = g_aml_hw;
    char buf[3] = {0};
    int len = min_t(size_t, sizeof(buf), count);

    if (copy_from_user(buf , user_buf, len)) {
        AML_INFO("copy_from_user fail\n");
        return -EFAULT;
    }

    AML_INFO("set new country:%s\n", buf);

    buf[2] = '\0';

    aml_apply_regdom(aml_hw, aml_hw->wiphy, buf);
    aml_send_me_chan_config_req(aml_hw);

    return len;
}

static ssize_t aml_proc_dbglevel_read(struct file *file,
                                     char __user *user_buf,
                                     size_t count, loff_t *ppos)
{
    struct aml_hw *aml_hw = g_aml_hw; //file->private_data;
    char buf[30];
    int len = 0;
    ssize_t read;

    len += scnprintf(&buf[len], min_t(size_t, sizeof(buf) - 1, count),
                     "dbglevel:%d\n", aml_hw->customer_priv.dbg_level);

    read = simple_read_from_buffer(user_buf, count, ppos, buf, len);

    return read;
}

static ssize_t aml_proc_dbglevel_write(struct file *file,
                                       const char __user *user_buf,
                                       size_t count, loff_t *ppos)
{
    struct aml_hw *priv = g_aml_hw; //file->private_data;
    char buf[32];
    int idx = 0;
    size_t len = min_t(size_t, count, sizeof(buf) - 1);

    buf[0] = '\0';
    if (copy_from_user(buf, user_buf, len))
        return -EFAULT;
    buf[len] = '\0';

#define AML_DBG_TOKEN(str, val)                                \
    if (strncmp(&buf[idx], str, sizeof(str) - 1) == 0) {        \
        idx += sizeof(str) - 1;                                 \
        dbg = val;                                              \
        goto dbg_done;                                          \
    }

    while ((idx + 4) < len) {
        if (strncmp(&buf[idx], "DBG:", 4) == 0) {
            u32 dbg = 0;
            idx += 4;
            AML_DBG_TOKEN("NONE", 0);
            AML_DBG_TOKEN("CRT",  1);
            AML_DBG_TOKEN("ERR",  2);
            AML_DBG_TOKEN("WRN",  3);
            AML_DBG_TOKEN("INF",  4);
            AML_DBG_TOKEN("VRB",  5);
            idx++;
            continue;
          dbg_done:
            aml_send_dbg_set_sev_filter_req(priv, dbg);
        } else {
            idx++;
        }
    }

    return count;
}

static ssize_t aml_proc_cfg_read(struct file *file,
                                     char __user *user_buf,
                                     size_t count, loff_t *ppos)
{
    struct aml_hw *aml_hw = g_aml_hw; //file->private_data;
    char buf[100];
    int len = 0;
    ssize_t read;

    // TODO : get driver capability or link information ?
    len += scnprintf(&buf[len], min_t(size_t, sizeof(buf) - 1, count),
                     "StaHTBfee|0\n");
    len += scnprintf(&buf[len], min_t(size_t, sizeof(buf) - 1, count),
                     "StaVHTBfee|%d\n", aml_hw->mod_params->bfmee);
    len += scnprintf(&buf[len], min_t(size_t, sizeof(buf) - 1, count),
                     "StaVHTMuBfee|%d\n", aml_hw->mod_params->murx);
    len += scnprintf(&buf[len], min_t(size_t, sizeof(buf) - 1, count),
                     "Sta5gBw|%d\n", aml_hw->mod_params->use_80 ? 2 : (aml_hw->mod_params->use_2040 ? 1 : 0));
    len += scnprintf(&buf[len], min_t(size_t, sizeof(buf) - 1, count),
                     "TxRetryLimit|%d\n", aml_hw->customer_priv.retry_cnt);


    read = simple_read_from_buffer(user_buf, count, ppos, buf, len);

    return read;
}

size_t aml_get_value_from_str(unsigned char *str, size_t len, int base, u16 *out)
{
    unsigned char *endptr = NULL;
    unsigned char *startstr = str;
    unsigned long result;

    while (len) {
        if (isspace(*str)) {
            str++;
            len--;
        }
        else
            break;
    }
    AML_INFO("aml_get_value_from_str:%s\n", str);
    result = simple_strtoul(str, (char **)&endptr, base);

    *out = result;

    AML_INFO("aml_get_value_from_str:%s, value:%d, result:%ld\n", str, *out, result);

    return endptr - startstr;
}

static ssize_t aml_proc_cfg_write(struct file *file,
                                    const char __user *user_buf,
                                    size_t count, loff_t *ppos)
{
    struct aml_hw *aml_hw = g_aml_hw; //file->private_data;
    char buf[100] = {0};
    size_t len = min_t(size_t, count, sizeof(buf) - 1);
    u16 retry = 0xffff;
    u16 bfmee = 0xffff;
    u16 bw = 0xffff;
    char *pos = buf;
    char *endptr = buf + len;

    if (copy_from_user(buf, user_buf, len))
        return -EFAULT;

    if (strncmp(buf, "StaHTBfee", strlen("StaHTBfee")) == 0) {
        return count;
    }

    while (len) {
        if (isspace(*pos)) {
            pos++;
            len--;
            continue;
        }
        if (strncmp(pos, "StaVHTMuBfee", strlen("StaVHTMuBfee")) == 0) {
            int offset = strlen("StaVHTMuBfee");
            size_t add_len;
            pos += offset;
            add_len = aml_get_value_from_str(pos, endptr - pos, 10, &bfmee);     // 10 is decimalism
            if (bfmee == 1)
                aml_hw->mod_params->murx = true;
            else if (bfmee == 0)
                aml_hw->mod_params->murx = false;
            else {
                AML_ERR("error param %d : %s, expect: 1 or 0, actuality: %d,\n", __LINE__, pos, bfmee);
                return -EINVAL;
            }
            pos += add_len;
            len -= (offset + add_len);
        }
        else if (strncmp(pos, "StaVHTBfee", strlen("StaVHTBfee")) == 0) {
            int offset = strlen("StaVHTBfee");
            size_t add_len;
            pos += offset;
            add_len = aml_get_value_from_str(pos, endptr - pos, 10, &bfmee);     // 10 is decimalism
            if (bfmee == 1)
                aml_hw->mod_params->bfmee = true;
            else if (bfmee == 0)
                aml_hw->mod_params->bfmee = false;
            else {
                AML_ERR("error param %d : %s, expect: 1 or 0, actuality: %d,\n", __LINE__, pos, bfmee);
                return -EINVAL;
            }
            pos += add_len;
            len -= (offset + add_len);
        }
        else if (strncmp(pos, "Sta5gBw", strlen("Sta5gBw")) == 0) {
            int offset = strlen("Sta5gBw");
            size_t add_len;
            pos += offset;
            add_len= aml_get_value_from_str(pos, endptr - pos, 10, &bw);     // 10 is decimalism
            if (bw == 2) {
                aml_hw->mod_params->use_80 = true;
                aml_hw->mod_params->use_2040 = true;
            } else if (bw == 1) {
                aml_hw->mod_params->use_80 = false;
                aml_hw->mod_params->use_2040 = true;
            } else if (bw == 0) {
                aml_hw->mod_params->use_80 = false;
                aml_hw->mod_params->use_2040 = false;
            } else {
                AML_ERR("error param %d : %s, expect: 0 or 1 or 2, actuality: %d,\n", __LINE__, pos, bw);
                return -EINVAL;
            }
            pos += add_len;
            len -= (offset + add_len);
        }
        else if (strncmp(pos, "TxRetryLimit", strlen("TxRetryLimit")) == 0) {
            int offset = strlen("TxRetryLimit");
            size_t add_len;
            pos += offset;
            add_len = aml_get_value_from_str(pos, endptr - pos, 10, &retry);     // 10 is decimalism
            if (aml_hw->customer_priv.retry_cnt == retry) {
                AML_INFO("TxRetryLimit has already be :%d\n", retry);
                retry = 0xff;
            } else {
                if (retry >= 32) {
                    AML_INFO("TxRetryLimit should litter than 32\n");
                    retry = 0xff;
                }
                else
                    aml_hw->customer_priv.retry_cnt = retry;
            }
            pos += add_len;
            len -= (offset + add_len);
        }
        else{
            int error_len = strlen(pos);
            AML_ERR("error param : %s\n", pos);
            AML_INFO("expect:"    \
                   "echo \"StaVHTBfee 0|1 StaVHTMuBfee 0|1 Sta5gBw 0|1|2 TxRetryLimit [0~15]\" > cfg\n");
            pos += error_len;
            len -= error_len;
        }
    }
    AML_INFO("retry:%d bfmee:%d, bw:%d, buf:%s\n", retry, bfmee, bw, buf);

    if (aml_send_cfg_req(aml_hw, bfmee, bfmee, bw, retry) == 0) {
        aml_hw->customer_priv.retry_cnt = retry;
    }

    return count;
}

static ssize_t aml_proc_scan_param_read(struct file *file,
                                     char __user *user_buf,
                                     size_t count, loff_t *ppos)
{
    struct aml_hw *aml_hw = g_aml_hw;
    struct aml_vif *aml_vif = aml_hw->vif_table[VIF_STA];
    char buf[250];
    int len = 0;
    ssize_t read;

    len += scnprintf(&buf[len], min_t(size_t, sizeof(buf) - 1, count),
                     "scan_ch_ms|%d\n", aml_vif->sta.non_dfs_chan_scan_duration);
    len += scnprintf(&buf[len], min_t(size_t, sizeof(buf) - 1, count),
                     "dfs_scan_ch_ms|%d\n", aml_vif->sta.dfs_chan_scan_duration);
    len += scnprintf(&buf[len], min_t(size_t, sizeof(buf) - 1, count),
                     "rx_ampdu_accept|%d\n", RX_AMPDU_ACCEPT);
    len += scnprintf(&buf[len], min_t(size_t, sizeof(buf) - 1, count),
                     "rx_ampdu_size|%d\n", RX_AMPDU_SIZE);
    len += scnprintf(&buf[len], min_t(size_t, sizeof(buf) - 1, count),
                     "backop_ms|%d\n", BACKOP_MS);
    len += scnprintf(&buf[len], min_t(size_t, sizeof(buf) - 1, count),
                     "scan_cnt_max |%d\n", MAX_CHAN_SCAN_CNT);
    len += scnprintf(&buf[len], min_t(size_t, sizeof(buf) - 1, count),
                     "scan_num_each_ch|%d\n", SCAN_NUM_EACH_CH);
    len += scnprintf(&buf[len], min_t(size_t, sizeof(buf) - 1, count),
                     "probe_num_each_scan|%d\n", aml_vif->sta.probe_num);
    len += scnprintf(&buf[len], min_t(size_t, sizeof(buf) - 1, count),
                     "probe_ssid_num_each_scan|%d\n", PROBE_SSID_NUM_EACH_SCAN);

    read = simple_read_from_buffer(user_buf, count, ppos, buf, len);

    return read;

}

static ssize_t aml_proc_scan_param_write(struct file *file,
                                    const char __user *user_buf,
                                    size_t count, loff_t *ppos)
{
    struct aml_hw *aml_hw = g_aml_hw;
    struct aml_vif *aml_vif = aml_hw->vif_table[VIF_STA];
    char buf[100] = {0};
    size_t len = min_t(size_t, count, sizeof(buf) - 1);
    u16 non_dfs_chan_scan_ms = 0;
    u16 dfs_chan_scan_ms = 0;
    u16 probe_num = 0;
    char *pos = buf;
    char *endptr = buf + len;

    if (copy_from_user(buf, user_buf, len))
        return -EFAULT;

    while (len) {
        if (isspace(*pos)) {
            pos++;
            len--;
            continue;
        }
        if (strncmp(pos, "scan_ch_ms", strlen("scan_ch_ms")) == 0) {
            int offset = strlen("scan_ch_ms");
            size_t add_len;
            pos += offset;
            add_len = aml_get_value_from_str(pos, endptr - pos, 10, &non_dfs_chan_scan_ms);     // 10 is decimalism
            if (non_dfs_chan_scan_ms > 10 && non_dfs_chan_scan_ms < 200) {
                aml_vif->sta.non_dfs_chan_scan_duration = non_dfs_chan_scan_ms;
            }
            else {
                AML_ERR("error param %d : %s, expect: (10, 200)\n", __LINE__, pos);
                return -EINVAL;
            }
            pos += add_len;
            len -= (offset + add_len);
        }
        else if (strncmp(pos, "dfs_scan_ch_ms", strlen("dfs_scan_ch_ms")) == 0) {
            int offset = strlen("dfs_scan_ch_ms");
            size_t add_len;
            pos += offset;
            add_len = aml_get_value_from_str(pos, endptr - pos, 10, &dfs_chan_scan_ms);     // 10 is decimalism
            if (dfs_chan_scan_ms > 10 && dfs_chan_scan_ms < 200) {
                aml_vif->sta.dfs_chan_scan_duration = dfs_chan_scan_ms;
            }
            else {
                AML_ERR("error param %d : %s, expect: (10, 200)\n", __LINE__, pos);
                return -EINVAL;
            }
            pos += add_len;
            len -= (offset + add_len);
        }
        else if (strncmp(pos, "probe_num_each_scan", strlen("probe_num_each_scan")) == 0) {
            int offset = strlen("probe_num_each_scan");
            size_t add_len;
            pos += offset;
            add_len = aml_get_value_from_str(pos, endptr - pos, 10, &probe_num);     // 10 is decimalism
            if (probe_num > 0 && probe_num < 4) {
                aml_vif->sta.probe_num = probe_num;
            }
            else {
                AML_ERR("error param %d : %s, expect: (0, 4)\n", __LINE__, pos);
                return -EINVAL;
            }
            pos += add_len;
            len -= (offset + add_len);
        }
        else {
            AML_ERR("error param : %s\n", pos);
            return -EINVAL;
        }
    }

    aml_send_scan_param_req(aml_hw, aml_vif->sta.non_dfs_chan_scan_duration, aml_vif->sta.dfs_chan_scan_duration, aml_vif->sta.probe_num);

    return count;
}

static ssize_t aml_proc_disconnect_info_read(struct file *file,
                                     char __user *user_buf,
                                     size_t count, loff_t *ppos)
{
    struct aml_hw *aml_hw = g_aml_hw;
    char buf[200];
    int len = 0;
    ssize_t read;

    len += scnprintf(&buf[len], min_t(size_t, sizeof(buf) - 1, count),
                                "Trigger:%d\n", aml_hw->customer_priv.disconnect_info.trigger);
    len += scnprintf(&buf[len], min_t(size_t, sizeof(buf) - 1, count),
                                "Disconnect time:%lu\n", aml_hw->customer_priv.disconnect_info.time);
    len += scnprintf(&buf[len], min_t(size_t, sizeof(buf) - 1, count),
                                "Disconnect reason:%d\n", aml_hw->customer_priv.disconnect_info.disconnect_reason);
    len += scnprintf(&buf[len], min_t(size_t, sizeof(buf) - 1, count),
                                "Disconnect spec code:%d\n", aml_hw->customer_priv.disconnect_info.wifi_spec_code);

    read = simple_read_from_buffer(user_buf, count, ppos, buf, len);

    return read;
}

static ssize_t aml_proc_wow_reason_read(struct file *file,
                                     char __user *user_buf,
                                     size_t count, loff_t *ppos)
{
    struct aml_hw *aml_hw = g_aml_hw; //file->private_data;
    char buf[30];
    int len = 0;
    ssize_t read;

    if (aml_hw->customer_priv.wake_reason != 0xff)
        len += scnprintf(&buf[len], min_t(size_t, sizeof(buf) - 1, count),
                         "wakeup_reason:%d\n", aml_hw->customer_priv.wake_reason);

    read = simple_read_from_buffer(user_buf, count, ppos, buf, len);

    return read;
}

static ssize_t aml_proc_rvrinfo_read(struct file *file, char __user *user_buf,
                                           size_t count, loff_t *ppos)
{
    struct aml_hw *aml_hw = g_aml_hw; //file->private_data;
    struct aml_vif *aml_vif;
    char buf[200];
    int len = 0;
    int buf_size = sizeof(buf);
    ssize_t read;
    uint32_t reg_data;
    struct aml_rate_info info;

    list_for_each_entry(aml_vif, &aml_hw->vifs, list) {
        if (aml_vif->up && (aml_vif->ndev != NULL) && (AML_VIF_TYPE(aml_vif) == NL80211_IFTYPE_STATION)) {
            if (aml_vif->sta.ap != NULL) {
                struct aml_sta *sta = aml_vif->sta.ap;
                uint16_t idx;
                struct rx_vector_1 *last_rx = &aml_vif->sta.ap->stats.last_rx.rx_vect1;
                struct me_rc_stats_cfm me_rc_stats_cfm;

                reg_data = AML_REG_READ(aml_hw->plat, AML_ADDR_MAC_PHY, REG_OF_SYNC_RSSI); // & 0xffff0000) >> 16) - 256)
                len += scnprintf(&buf[len], min_t(size_t, buf_size - len - 1, count),
                    "avg_rssi:%d\n", sta->stats.data_rssi.data_avg_rssi);
                len += scnprintf(&buf[len], min_t(size_t, buf_size - len - 1, count),
                    "avg_bcn_rssi:%d\n", (reg_data & 0x0000ffff) - 256);
                len += scnprintf(&buf[len], min_t(size_t, buf_size - len - 1, count),
                    "avg_snr:%d\n", AML_REG_READ(aml_hw->plat, AML_ADDR_MAC_PHY, REG_OF_SYNC_SNR) & 0xffff);
                len += scnprintf(&buf[len], min_t(size_t, buf_size - len - 1, count),
                    "snr_qdb:%d\n", 0);   // TODO
                len += scnprintf(&buf[len], min_t(size_t, buf_size - len - 1, count),
                    "noise_f:%d\n", 0);   // TODO

                // get txrate
                if (0 == aml_send_me_rc_stats(aml_hw, sta->sta_idx, &me_rc_stats_cfm)) {
                    len += scnprintf(&buf[len], min_t(size_t, buf_size - len - 1, count), "txRate:");
                    idx = me_rc_stats_cfm.retry_step_idx[me_rc_stats_cfm.sw_retry_step];
                    len += print_rate_from_cfg(&buf[len], min_t(size_t, buf_size - len - 1, count),
                                              me_rc_stats_cfm.rate_stats[idx].rate_config, NULL, 0);
                    len += scnprintf(&buf[len], min_t(size_t, buf_size - len - 1, count), "\n");
                }

                // get rxrate
                len += scnprintf(&buf[len], min_t(size_t, buf_size - len - 1, count), "rxRate:");
                rate_idx_of_rx_vector(last_rx, &info);

                if (info.format < FORMATMOD_HT_MF) {
                    BUG_ON((info.mcs = legrates_lut[last_rx->leg_rate].idx) == -1);
                    info.nss = 0;
                    info.sgi = 0;
                }
                len += print_rate(&buf[len], 30, info.format, info.nss, info.mcs, info.bw, info.sgi, last_rx->pre_type, last_rx->he.dcm, NULL);
                len += scnprintf(&buf[len], min_t(size_t, buf_size - len - 1, count), "\n");

                len += scnprintf(&buf[len], min_t(size_t, buf_size - len - 1, count),
                    "BW:%dMHz\n", ((sta->stats.bw_max == PHY_CHNL_BW_80) ? 80 : (sta->stats.bw_max == PHY_CHNL_BW_40) ? 40 : 20));
            }
        }
    }

    read = simple_read_from_buffer(user_buf, count, ppos, buf, len);

    return read;
}

static ssize_t aml_proc_power_table_read(struct file *file, char __user *user_buf,
                                           size_t count, loff_t *ppos)
{
    unsigned int len = 0;
    char buf[1000];
    ssize_t read;
    struct aml_hw *aml_hw = g_aml_hw;
    unsigned char sep = '\0';
    struct priv_custom *customer_priv = &aml_hw->customer_priv;
    int offset = 0;
    unsigned char power_count_all[17] = {4, 8, 8, 8, 9, 10, 12, 12, 8, 8, 8, 9, 10, 10, 12, 12, 12};
    unsigned char pwr_idx_name[17][20] = {"wf2g_11b_tpwr:", "wf2g_11g_tpwr:", "wf2g_ht20_tpwr:", "wf2g_ht40_tpwr:", "wf2g_vht20_tpwr:",
                                   "wf2g_vht40_tpwr:", "wf2g_he20_tpwr:", "wf2g_he40_tpwr:", "wf5g_11a_tpwr:", "wf5g_ht20_tpwr:",
                                   "wf5g_ht40_tpwr:", "wf5g_vht20_tpwr:", "wf5g_vht40_tpwr:", "wf5g_vht80_tpwr:", "wf5g_he20_tpwr:",
                                   "wf5g_he40_tpwr:", "wf5g_he80_tpwr:"};
    int idx = 0;
    int item_idx = 0;

    for (idx = 0; idx < 17; idx ++) {
        len += scnprintf(&buf[len], min_t(size_t, sizeof(buf) - 1, count),
                             "%s", pwr_idx_name[idx]);
        for (item_idx = 0; item_idx < power_count_all[idx]; item_idx ++) {
            len += scnprintf(&buf[len], min_t(size_t, sizeof(buf) - 1, count),
                                 "%d", *((unsigned char *)customer_priv->cali_param.wf2g_11b_tpwr  + offset + item_idx));

            if (item_idx < power_count_all[idx] - 1) {
                sep = ',';
            } else {
                sep = '\n';
            }
            len += scnprintf(&buf[len], min_t(size_t, sizeof(buf) - 1, count),
                             "%c", sep);

        }
        offset += power_count_all[idx];
    }
    read = simple_read_from_buffer(user_buf, count, ppos, buf, len);

    return read;
}

void aml_destroy_proc_dir(struct aml_hw *aml_hw)
{
    if (aml_hw->customer_priv.proc_dir)
        proc_remove(aml_hw->customer_priv.proc_dir);
}

const struct aml_proc_hdl drv_proc_hdls[] = {
    AML_PROC_HDL_SSEQ("cfg", aml_proc_cfg_read, NULL),
    AML_PROC_HDL_SSEQ("driver", aml_proc_driver_read, NULL),
    AML_PROC_HDL_SSEQ("dbglevel", aml_proc_dbglevel_read, NULL),
    AML_PROC_HDL_SSEQ("country", aml_proc_country_read, NULL),
};


static int aml_drv_proc_open(struct inode *inode, struct file *file)
{
    /* struct net_device *dev = proc_get_parent_data(inode); */
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,16,0)
    ssize_t index = (ssize_t)PDE_DATA(inode);
#else
    ssize_t index = (ssize_t)pde_data(inode);
#endif
    const struct aml_proc_hdl *hdl = drv_proc_hdls + index;
    void *private = NULL;

    if (hdl->type == AML_PROC_HDL_TYPE_SEQ) {
        int res = seq_open(file, hdl->u.seq_op);

        if (res == 0)
            ((struct seq_file *)file->private_data)->private = private;

        return res;
    } else if (hdl->type == AML_PROC_HDL_TYPE_SSEQ) {
        int (*show)(struct seq_file *, void *) = hdl->u.show ? hdl->u.show : proc_get_dummy;

        return single_open(file, show, private);
    } else if (hdl->type == AML_PROC_HDL_TYPE_SZSEQ) {
        int (*show)(struct seq_file *, void *) = hdl->u.sz.show ? hdl->u.sz.show : proc_get_dummy;
        #if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 0))
        return single_open_size(file, show, private, hdl->u.sz.size);
        #else
        return single_open(file, show, private);
        #endif
    } else {
        return -EROFS;
    }
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0))
static int aml_drv_proc_release(struct inode *inode, struct file *file)
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,16,0)
    ssize_t index = (ssize_t)PDE_DATA(inode);
#else
    ssize_t index = (ssize_t)pde_data(inode);
#endif

    const struct aml_proc_hdl *hdl = drv_proc_hdls + index;

    if (hdl->type == AML_PROC_HDL_TYPE_SEQ) {
        return seq_release(inode, file);
    }

    if ((hdl->type == AML_PROC_HDL_TYPE_SSEQ) ||
        (hdl->type == AML_PROC_HDL_TYPE_SZSEQ)) {
        return single_release(inode, file);
    }

    AML_ERR("hdl->type:%d err\n",hdl->type);
    return -EROFS;
}
#endif

static const struct aml_proc_ops aml_proc_cfg_ops = {

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0))
        .proc_open = aml_drv_proc_open,
        .proc_read = aml_proc_cfg_read,
        .proc_lseek = seq_lseek,
        .proc_release = aml_drv_proc_release,
        .proc_write = aml_proc_cfg_write,
#else
        .owner = THIS_MODULE,
        .open = aml_drv_proc_open,
        .read = aml_proc_cfg_read,
        .write = aml_proc_cfg_write,
#endif
};

static const struct aml_proc_ops aml_proc_driver_ops = {

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0))
        .proc_open = aml_drv_proc_open,
        .proc_read = aml_proc_driver_read,
        .proc_lseek = seq_lseek,
        .proc_release = aml_drv_proc_release,
        .proc_write = aml_proc_driver_write,
#else
        .owner = THIS_MODULE,
        .open = aml_drv_proc_open,
        .read = aml_proc_driver_read,
        .write = aml_proc_driver_write,
#endif
};

static const struct aml_proc_ops aml_proc_dbglevel_ops = {

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0))
        .proc_open = aml_drv_proc_open,
        .proc_read = aml_proc_dbglevel_read,
        .proc_lseek = seq_lseek,
        .proc_release = aml_drv_proc_release,
        .proc_write = aml_proc_dbglevel_write,
#else
        .owner = THIS_MODULE,
        .open = aml_drv_proc_open,
        .read = aml_proc_dbglevel_read,
        .write = aml_proc_dbglevel_write,
#endif
};

static const struct aml_proc_ops aml_proc_country_ops = {

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0))
        .proc_open = aml_drv_proc_open,
        .proc_read = aml_proc_country_read,
        .proc_lseek = seq_lseek,
        .proc_release = aml_drv_proc_release,
        .proc_write = aml_proc_country_write,
#else
        .owner = THIS_MODULE,
        .open = aml_drv_proc_open,
        .read = aml_proc_country_read,
        .write = aml_proc_country_write,
#endif
};

static const struct aml_proc_ops aml_proc_drv_state_ops = {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0))
        .proc_open = aml_drv_proc_open,
        .proc_read = aml_proc_drv_state_read,
        .proc_lseek = seq_lseek,
        .proc_release = aml_drv_proc_release,
#else
        .owner = THIS_MODULE,
        .open = aml_drv_proc_open,
        .read = aml_proc_drv_state_read,
#endif
};
static const struct aml_proc_ops aml_proc_CurrentTempeature_ops = {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0))
        .proc_open = aml_drv_proc_open,
        .proc_read = aml_proc_CurrentTempeature_read,
        .proc_lseek = seq_lseek,
        .proc_release = aml_drv_proc_release,
#else
        .owner = THIS_MODULE,
        .open = aml_drv_proc_open,
        .read = aml_proc_CurrentTempeature_read,
#endif
};
static const struct aml_proc_ops aml_proc_disconnect_info_ops = {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0))
        .proc_open = aml_drv_proc_open,
        .proc_read = aml_proc_disconnect_info_read,
        .proc_lseek = seq_lseek,
        .proc_release = aml_drv_proc_release,
#else
        .owner = THIS_MODULE,
        .open = aml_drv_proc_open,
        .read = aml_proc_disconnect_info_read,
#endif
};
static const struct aml_proc_ops aml_proc_rvrinfo_ops = {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0))
        .proc_open = aml_drv_proc_open,
        .proc_read = aml_proc_rvrinfo_read,
        .proc_lseek = seq_lseek,
        .proc_release = aml_drv_proc_release,
#else
        .owner = THIS_MODULE,
        .open = aml_drv_proc_open,
        .read = aml_proc_rvrinfo_read,
#endif
};
static const struct aml_proc_ops aml_proc_wow_reason_ops = {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0))
        .proc_open = aml_drv_proc_open,
        .proc_read = aml_proc_wow_reason_read,
        .proc_lseek = seq_lseek,
        .proc_release = aml_drv_proc_release,
#else
        .owner = THIS_MODULE,
        .open = aml_drv_proc_open,
        .read = aml_proc_wow_reason_read,
#endif
};
static const struct aml_proc_ops aml_proc_power_table_ops = {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0))
        .proc_open = aml_drv_proc_open,
        .proc_read = aml_proc_power_table_read,
        .proc_lseek = seq_lseek,
        .proc_release = aml_drv_proc_release,
#else
        .owner = THIS_MODULE,
        .open = aml_drv_proc_open,
        .read = aml_proc_power_table_read,
#endif
};
static const struct aml_proc_ops aml_proc_scan_param_ops = {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0))
        .proc_open = aml_drv_proc_open,
        .proc_read = aml_proc_scan_param_read,
        .proc_lseek = seq_lseek,
        .proc_release = aml_drv_proc_release,
        .proc_write = aml_proc_scan_param_write,
#else
        .owner = THIS_MODULE,
        .open = aml_drv_proc_open,
        .read = aml_proc_scan_param_read,
        .write = aml_proc_scan_param_write,
#endif
};

#define AML_PROC_ADD_FILE(name, parent, mode) do {                          \
        struct proc_dir_entry *__tmp;                                       \
        __tmp = proc_create(#name, mode, parent, &aml_proc_##name##_ops);   \
        if (IS_ERR_OR_NULL(__tmp))                                          \
            goto err;                                                       \
    } while (0)


int32_t aml_create_proc_dir(struct aml_hw *aml_hw)
{
    struct proc_dir_entry *proc_dir = aml_hw->customer_priv.proc_dir;
    umode_t mode = S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH;
    umode_t read_mode = S_IRUSR | S_IRGRP | S_IROTH;

    AML_PROC_ADD_FILE(cfg, proc_dir, mode);
    AML_PROC_ADD_FILE(driver, proc_dir, mode);
    AML_PROC_ADD_FILE(dbglevel, proc_dir, mode);
    AML_PROC_ADD_FILE(drv_state, proc_dir, read_mode);
    AML_PROC_ADD_FILE(CurrentTempeature, proc_dir, read_mode);
    AML_PROC_ADD_FILE(country, proc_dir, mode);
    AML_PROC_ADD_FILE(disconnect_info, proc_dir, read_mode);
    AML_PROC_ADD_FILE(rvrinfo, proc_dir, read_mode);
    //AML_PROC_ADD_FILE(AML_SCANPARAM_NAME, proc_dir, mode);
    AML_PROC_ADD_FILE(wow_reason, proc_dir, read_mode);
    AML_PROC_ADD_FILE(power_table, proc_dir, read_mode);
    AML_PROC_ADD_FILE(scan_param, proc_dir, mode);
    return 0;

err:
    AML_INFO("create proc error\n");
    aml_destroy_proc_dir(aml_hw);
    return -1;
}

static ssize_t aml_sysfs_hal_spec_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    u32_l phy_feat = aml_hw->version_cfm.version_phy_1;
    u32_l sys_feat = aml_hw->version_cfm.features;
    int bw = (phy_feat & MDM_CHBW_MASK) >> MDM_CHBW_LSB;
    int len = 0;

    len += sprintf(buf, "Tx_Nss:%d\n", aml_hw->mod_params->nss);
    len += sprintf(&buf[len], "Rx_Nss:%d\n", aml_hw->mod_params->nss);

    // Check supported BW
    bw = (phy_feat & MDM_CHBW_MASK) >> MDM_CHBW_LSB;
    // Check if 80MHz BW is supported
    if (bw == 2) {
        len += sprintf(&buf[len], "2gBW:40M\n");
        len += sprintf(&buf[len], "5gBW:80M\n");
    }
    else if (bw == 1) {
        len += sprintf(&buf[len], "2gBW:40M\n");
        len += sprintf(&buf[len], "5gBW:40M\n");
    }
    else {
        len += sprintf(&buf[len], "2gBW:20M\n");
        len += sprintf(&buf[len], "5gBW:20M\n");
    }

    // Check if HE is supported
    if (sys_feat & BIT(MM_FEAT_HE_BIT)) {
        len += sprintf(&buf[len], "max_proto:ax\n");
    }
    else if (sys_feat & BIT(MM_FEAT_VHT_BIT)) {
        len += sprintf(&buf[len], "max_proto:ac\n");
    }
    else {
        len += sprintf(&buf[len], "max_proto:n\n");
    }

    return len;
}
static SYSFS_RO_FILE_OPS(hal_spec);

bool g_band_query_flag = false;
static ssize_t aml_sysfs_band_query_flag_read(struct device *d, struct device_attribute *attr,char *buf)
{
    return sprintf(buf,"%d\n",g_band_query_flag);
}
static SYSFS_RO_FILE_OPS(band_query_flag);

static ssize_t show_band_info(struct device *dev, struct device_attribute *attr,char *buf)
{
    char *out = buf;

    if (g_band_query_flag) {
       out += sprintf(buf, "channel_busy:%d\nchannel_idle:%d\n",g_bandInfo.util_busy,g_bandInfo.util_idle);
       return (out - buf);
    } else {
       out += sprintf(buf, "Show_band_info failed\n");
       return (out - buf);
    }

    return 0;
}

static ssize_t  store_band_info(struct device *dev, struct device_attribute *attr,const char *buf, size_t count)
{
#define MAC_EDCA_CCA_BUSY_ADDR   0x60B00220
    int input_parameter = 0;
    ssize_t result = 0;
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    uint32_t chan_time_busy_ms;

    if (kstrtouint(buf, 0, &input_parameter)) {
        return result;
    }

    if (input_parameter == 1) {
        AML_REG_WRITE(0, aml_hw->plat, 0, MAC_EDCA_CCA_BUSY_ADDR);
        g_band_query_flag = false;
        msleep(1000);
        chan_time_busy_ms = AML_REG_READ(aml_hw->plat, 0, MAC_EDCA_CCA_BUSY_ADDR) / 1000;
        g_bandInfo.util_busy = chan_time_busy_ms / 10;
        g_bandInfo.util_idle =  100 - g_bandInfo.util_busy;
        g_band_query_flag = true;
    }

    return count;
}

static DEVICE_ATTR(band_info, S_IWUSR|S_IWGRP|S_IRUGO, show_band_info, store_band_info);


static ssize_t aml_sysfs_cur_channel_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    int len = 0;

    if (vif->up && (vif->ch_index != AML_CH_NOT_SET) && (AML_VIF_TYPE(vif) == NL80211_IFTYPE_STATION))
        len += sprintf(&buf[len], "cur_channel:%d\n",
                     ieee80211_frequency_to_channel(vif->sta.ap->center_freq)); // prim20
    else
        len += snprintf(&buf[len], 25, "dev:%s channel:error\n", vif->ndev->name);

    return len;
}
static SYSFS_RO_FILE_OPS(cur_channel);

static ssize_t aml_sysfs_bandwidth_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    int len = 0;
    const char bw_info[3][4] = {"20M", "40M", "80M"};

    if (vif->up && (vif->ch_index != AML_CH_NOT_SET) && (AML_VIF_TYPE(vif) == NL80211_IFTYPE_STATION) &&
        ((aml_hw->chanctx_table[vif->ch_index].chan_def.width - NL80211_CHAN_WIDTH_20) < 3))
    {
        len += snprintf(&buf[len], 25, "bandwidth:%s\n",
                       bw_info[aml_hw->chanctx_table[vif->ch_index].chan_def.width - NL80211_CHAN_WIDTH_20]);
    }
    else
        len += sprintf(&buf[len], "bandwidth:error\n");

    return len;
}
static SYSFS_RO_FILE_OPS(bandwidth);

static ssize_t aml_sysfs_rRssi_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_sta *sta = vif->sta.ap;
    int len = 0;

    if (sta != NULL)
        len += sprintf(&buf[len], "Rssi:%d\n", sta->stats.data_rssi.data_avg_rssi);

    return len;
}
static SYSFS_RO_FILE_OPS(rRssi);

static ssize_t aml_sysfs_iNoise_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    int len = 0;
    u32 agc_state;
    u32 agc1, agc2;
    s32 noise1, noise2;

    // W2 donot support, W2L support
    agc_state = AML_REG_READ(aml_hw->plat, AML_ADDR_SYSTEM, 0xc0b7d4);
    AML_REG_WRITE(0x29, aml_hw->plat, AML_ADDR_SYSTEM, 0xc0b7d4);
    agc1 = AML_REG_READ(aml_hw->plat, AML_ADDR_SYSTEM, 0xc0b7d8);
    agc2 = AML_REG_READ(aml_hw->plat, AML_ADDR_SYSTEM, 0xc0b7dc);
    AML_REG_WRITE(agc_state, aml_hw->plat, AML_ADDR_SYSTEM, 0xc0b7d4);

    noise1 = (agc1 >> 21) - 2048;
    noise2 = (agc2 >> 21) - 2048;
    len += sprintf(&buf[len], "Noise:%d\n", (noise1 + noise2) / 2);

    return len;
}
static SYSFS_RO_FILE_OPS(iNoise);

static ssize_t aml_sysfs_iSnr_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    int len = 0;

    len += sprintf(&buf[len], "Snr:%d\n",
                   AML_REG_READ(aml_hw->plat, AML_ADDR_MAC_PHY, REG_OF_SYNC_SNR) & 0xffff);

    return len;
}
static SYSFS_RO_FILE_OPS(iSnr);

static ssize_t aml_sysfs_ssid_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    int len = 0;

    if (vif->up && (vif->sta.ap != NULL) && (AML_VIF_TYPE(vif) == NL80211_IFTYPE_STATION))
        len += snprintf(&buf[len], MAC_SSID_LEN + 5, "SSID:%s\n", vif->sta.assoc_ssid);

    return len;
}
static SYSFS_RO_FILE_OPS(ssid);

static ssize_t aml_sysfs_bssid_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    int len = 0;

    if (vif->up && (vif->sta.ap != NULL) && (AML_VIF_TYPE(vif) == NL80211_IFTYPE_STATION))
        len += sprintf(&buf[len], "BSSID:"MACFMT"\n", MACARG(vif->sta.ap->mac_addr));

    return len;
}
static SYSFS_RO_FILE_OPS(bssid);

static ssize_t aml_sysfs_TxPktNum_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    int len = 0;

    if (vif->up && (vif->sta.ap != NULL) &&
        (AML_VIF_TYPE(vif) == NL80211_IFTYPE_STATION)) {
        len += sprintf(&buf[len], "TxPktNum:%d\n", vif->sta.ap->stats.tx_pkts);
    }

    return len;
}
static SYSFS_RO_FILE_OPS(TxPktNum);

static ssize_t aml_sysfs_TxFailNum_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    int len = 0;

    if (vif->up && (vif->sta.ap != NULL) &&
        (AML_VIF_TYPE(vif) == NL80211_IFTYPE_STATION)) {
        len += sprintf(&buf[len], "TxFailNum:%d\n", vif->sta.ap->stats.tx_fails);
    }

    return len;
}
static SYSFS_RO_FILE_OPS(TxFailNum);


static ssize_t aml_sysfs_TxRate_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    int len = 0;
    struct aml_sta *sta;
    struct aml_sta_stats *stats = NULL;

    if (vif->up && (vif->sta.ap != NULL) && (AML_VIF_TYPE(vif) == NL80211_IFTYPE_STATION)) {
        sta = vif->sta.ap;
        stats = &sta->stats;
        aml_sta_rate_info(vif, sta, &stats->mcs_max, &stats->no_ss);
        switch (stats->format_mod) {
            case FORMATMOD_NON_HT:
            case FORMATMOD_NON_HT_DUP_OFDM:
                len += sprintf(&buf[len], "TX:%d.%dMBPS\n", legrates_lut[stats->leg_rate].rate / 10, legrates_lut[stats->leg_rate].rate % 10);
                break;
            case FORMATMOD_HT_MF:
            case FORMATMOD_HT_GF:
                len += sprintf(&buf[len], "TX:HTMCS%dBW%d\n", stats->mcs_max, ((stats->bw_max == PHY_CHNL_BW_80) ? 80 : (stats->bw_max == PHY_CHNL_BW_40) ? 40 : 20));
                break;
            case FORMATMOD_VHT:
                len += sprintf(&buf[len], "TX:VHTSS%dMCS%dBW%d\n", stats->no_ss + 1, stats->mcs_max,
                    ((stats->bw_max == PHY_CHNL_BW_80) ? 80 : (stats->bw_max == PHY_CHNL_BW_40) ? 40 : 20));
                break;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0) || (defined CONFIG_KERNEL_AX_PATCH)
            case FORMATMOD_HE_MU:
            case FORMATMOD_HE_SU:
            case FORMATMOD_HE_ER:
            case FORMATMOD_HE_TB:
                len += sprintf(&buf[len], "TX:HESS%dMCS%dBW%d\n", stats->no_ss + 1, stats->mcs_max,
                    ((stats->bw_max == PHY_CHNL_BW_80) ? 80 : (stats->bw_max == PHY_CHNL_BW_40) ? 40 : 20));
            break;
#endif
            default :
                return -EFAULT;
        }
    }
    return len;
}
static SYSFS_RO_FILE_OPS(TxRate);

static ssize_t aml_sysfs_RxPktNum_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    int len = 0;

    if (vif->up && (vif->sta.ap != NULL) && (AML_VIF_TYPE(vif) == NL80211_IFTYPE_STATION))
        len += sprintf(&buf[len], "RxPktNum:%d\n", vif->sta.ap->stats.rx_pkts);
    else
        len += sprintf(&buf[len], "RxPktNum:not connect\n");

    return len;
}
static SYSFS_RO_FILE_OPS(RxPktNum);

static ssize_t aml_sysfs_RxFailNum_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    int len = 0;
    uint32_t rxfailnum = aml_send_get_rxfail_cnt(aml_hw, vif->vif_index);

    len += sprintf(&buf[len], "RxFailNum:%d\n", rxfailnum);

    return len;
}
static SYSFS_RO_FILE_OPS(RxFailNum);

static ssize_t aml_sysfs_Average_RxRate_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    int len = 0;

    if (vif->up && (vif->sta.ap != NULL) &&
        (AML_VIF_TYPE(vif) == NL80211_IFTYPE_STATION)) {
        len += sprintf(&buf[len], "average_rxrate:%d\n", aml_hw->customer_priv.rx_average_rate);
    }

    return len;
}
static SYSFS_RO_FILE_OPS(Average_RxRate);

static ssize_t aml_sysfs_Data_RxRate_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct rx_vector_1 *last_rx;
    int len = 0;
    struct aml_rate_info info;

    if (vif->up && (vif->sta.ap != NULL) &&
        (AML_VIF_TYPE(vif) == NL80211_IFTYPE_STATION)) {
        last_rx = &vif->sta.ap->stats.last_rx.rx_vect1;
        rate_idx_of_rx_vector(last_rx, &info);

        if (info.format >= FORMATMOD_HE_SU) {
            len += sprintf(&buf[len], "RX:HESS%dMCS%dBW%d\n", info.nss + 1, info.mcs, ((info.bw == PHY_CHNL_BW_80) ? 80 : (info.bw == PHY_CHNL_BW_40) ? 40 : 20));
        } else if (info.format == FORMATMOD_VHT) {
            len += sprintf(&buf[len], "RX:VHTSS%dMCS%dBW%d\n", info.nss + 1, info.mcs, ((info.bw == PHY_CHNL_BW_80) ? 80 : (info.bw == PHY_CHNL_BW_40) ? 40 : 20));
        } else if (info.format >= FORMATMOD_HT_MF) {
            len += sprintf(&buf[len], "RX:HTMCS%dBW%d\n", info.mcs, ((info.bw == PHY_CHNL_BW_80) ? 80 : (info.bw == PHY_CHNL_BW_40) ? 40 : 20));
        } else {
            len += sprintf(&buf[len], "RX:%d.%dMBPS\n", legrates_lut[last_rx->leg_rate].rate / 10, legrates_lut[last_rx->leg_rate].rate % 10);
        }

    }
    return len;
}
static SYSFS_RO_FILE_OPS(Data_RxRate);

static ssize_t aml_sysfs_connected_status_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    u8 connect_status = 0;
    int len = 0;

    if (vif && vif->up && (AML_VIF_TYPE(vif) == NL80211_IFTYPE_STATION)) {
        if ((aml_connect_flags_chk(vif, AML_DISCONNECTING)) || (vif->sta.ap == NULL)) {
            connect_status = 0;
        } else if (aml_connect_flags_chk(vif, AML_CONNECTING)) {
            connect_status = 1;
        } else if (vif->sta.ap != NULL) {
            connect_status = 2;
        } else {
            connect_status = 0;
        }
        len += sprintf(&buf[len], "%d\n", connect_status);
    }
    return len;
}
static SYSFS_RO_FILE_OPS(connected_status);


static ssize_t aml_sysfs_i4RSSI0_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    struct aml_sta *sta;
    struct aml_txq *txq;
    int i = 20;
    int len = 0;
    int rssi;
    uint32_t agcpow_ct2;

    if (vif->up && (vif->sta.ap != NULL) && (AML_VIF_TYPE(vif) == NL80211_IFTYPE_STATION)) {
        sta = vif->sta.ap;
        txq = aml_txq_sta_get(sta, 0, aml_hw);
        while (i-- > 0) {
            if (txq->status & AML_TXQ_STOP_CHAN) {
                msleep(10);
            } else {
                // make sure cur_channel is vif when get rssi
                agcpow_ct2 = AML_REG_READ(aml_hw->plat, AML_ADDR_SYSTEM, 0xc0b7d8);
                rssi = (agcpow_ct2 >> 21) - 2048;
                len += sprintf(&buf[len], "i4RSSI0:%d\n", rssi);
                break;
            }
        }
    }

    return len;
}
static SYSFS_RO_FILE_OPS(i4RSSI0);

static ssize_t aml_sysfs_i4RSSI1_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    struct aml_sta *sta;
    struct aml_txq *txq;
    int i = 20;
    int len = 0;
    int rssi;
    uint32_t agcpow_ct2;

    if (vif->up && (vif->sta.ap != NULL) && (AML_VIF_TYPE(vif) == NL80211_IFTYPE_STATION)) {
        sta = vif->sta.ap;
        txq = aml_txq_sta_get(sta, 0, aml_hw);
        while (i-- > 0) {
            if (txq->status & AML_TXQ_STOP_CHAN) {
                msleep(10);
            } else {
                msleep(10);
                // make sure cur_channel is vif when get rssi
                agcpow_ct2 = AML_REG_READ(aml_hw->plat, AML_ADDR_SYSTEM, 0xc0b7dc);
                rssi = (agcpow_ct2 >> 21) - 2048;
                len += sprintf(&buf[len], "i4RSSI1:%d\n", rssi);
                break;
            }
        }
    }

    return len;
}
static SYSFS_RO_FILE_OPS(i4RSSI1);


static ssize_t aml_sysfs_iSnrR0Phase2_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    int len = 0;

    len += sprintf(&buf[len], "iSnrR0Phase2:%d\n", AML_REG_READ(aml_hw->plat, AML_ADDR_MAC_PHY, REG_OF_SYNC_SNR) & 0xffff);

    return len;
}
static SYSFS_RO_FILE_OPS(iSnrR0Phase2);

static ssize_t aml_sysfs_iSnrR1Phase2_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    int len = 0;

    len += sprintf(&buf[len], "iSnrR1Phase2:%d\n", AML_REG_READ(aml_hw->plat, AML_ADDR_MAC_PHY, REG_OF_SYNC_SNR) & 0xffff);

    return len;
}
static SYSFS_RO_FILE_OPS(iSnrR1Phase2);

static ssize_t aml_sysfs_Glitch_Total_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    int len = 0;

    len += sprintf(&buf[len], "\n");

    return len; //len;
}
static SYSFS_RO_FILE_OPS(Glitch_Total);

static ssize_t aml_sysfs_Glitch_Diff_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    int len = 0;

    len += sprintf(&buf[len], "\n");

    return len; //len;
}
static SYSFS_RO_FILE_OPS(Glitch_Diff);

static ssize_t aml_sysfs_wake_on_pno_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    int len = 0;

    len += sprintf(&buf[len], "wake_on_pno:%d\n", aml_hw->customer_priv.wake_on_pno);

    return len;
}

static ssize_t aml_sysfs_wake_on_pno_write(struct device *dev, struct device_attribute *attr,
                                            const char *user_buf, size_t count)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    u8 new_state = *user_buf - 48;;

    AML_INFO("new_state:%d, old_state:%d\n", new_state, aml_hw->customer_priv.wake_on_pno);
    aml_hw->customer_priv.wake_on_pno = new_state;

    return count;
}
static SYSFS_RW_FILE_OPS(wake_on_pno);

static ssize_t aml_sysfs_pno_sec_mode_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;

    AML_INFO("pno_sec_mode = %d\n", aml_hw->customer_priv.pno_sec_mode);
    return sprintf(buf, "pno_sec_mode: %d\n", aml_hw->customer_priv.pno_sec_mode);
}

static ssize_t aml_sysfs_pno_sec_mode_write(struct device *dev, struct device_attribute *attr,
                                const char *user_buf, size_t count)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    unsigned char sec_mode = *user_buf - 48;

    if (sec_mode >= PNO_SEC_MODE_MAX) {
        AML_INFO("error input, pno_sec_mode = %d\n", sec_mode);
        return -EFAULT;
    }

    aml_hw->customer_priv.pno_sec_mode = sec_mode;
    return count;
}
static SYSFS_RW_FILE_OPS(pno_sec_mode);


/************************ P2P *********************************/

static ssize_t aml_sysfs_p2p_channel_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    int len = 0;

    list_for_each_entry(vif, &aml_hw->vifs, list) {
        if (!vif->up || (vif->ch_index == AML_CH_NOT_SET))
            continue;
        if ((AML_VIF_TYPE(vif) == NL80211_IFTYPE_P2P_GO) &&
            (aml_hw->chanctx_table[vif->ch_index].chan_def.chan != NULL)) {
            len += sprintf(&buf[len], "p2p_channel:%d\n",
                ieee80211_frequency_to_channel(aml_hw->chanctx_table[vif->ch_index].chan_def.chan->center_freq));
        }
    }

    return len;
}
static SYSFS_RO_FILE_OPS(p2p_channel);

static ssize_t aml_sysfs_p2p_DevNum_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_sta *sta, *tmp;
    int len = 0;
    int devnum = 0;

    if (AML_VIF_TYPE(vif) == NL80211_IFTYPE_P2P_GO) {
        list_for_each_entry_safe(sta, tmp, &vif->ap.sta_list, list) {
            devnum++;
        }
    }

    len += sprintf(&buf[len], "DevNum:%d\n", devnum);

    return len;
}
static SYSFS_RO_FILE_OPS(p2p_DevNum);

static ssize_t aml_sysfs_p2p_bandwidth_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_sta *sta, *tmp;
    int len = 0;
    int count = 0;
    const char bw_info[3][4] = {"20", "40", "80"};

    if (vif->up && (vif->ch_index != AML_CH_NOT_SET) && (AML_VIF_TYPE(vif) == NL80211_IFTYPE_P2P_GO)) {
        list_for_each_entry_safe(sta, tmp, &vif->ap.sta_list, list) {
            len += snprintf(&buf[len], sizeof(bw_info) + 6, "p2p%d: %s\n", count,
                       bw_info[sta->width - NL80211_CHAN_WIDTH_20]);
        }

    }

    return len;
}
static SYSFS_RO_FILE_OPS(p2p_bandwidth);

static ssize_t aml_sysfs_p2p_rRssi_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_sta *sta, *tmp;
    int len = 0;
    int count = 0;

    if (vif->up && (AML_VIF_TYPE(vif) == NL80211_IFTYPE_P2P_GO)) {
        list_for_each_entry_safe(sta, tmp, &vif->ap.sta_list, list) {
            len += sprintf(&buf[len], "p2p%d:%d\n", count,
                   sta->stats.data_rssi.data_avg_rssi);
            count++;
        }
    }

    return len;
}
static SYSFS_RO_FILE_OPS(p2p_rRssi);

static ssize_t aml_sysfs_p2p_iNoise_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    int len = 0;
    int count = 0;
    struct aml_sta *sta, *tmp;
    u32 agc_state;
    u32 agc1, agc2;
    s32 noise1, noise2;

    // W2 donot support, W2L support
    agc_state = AML_REG_READ(aml_hw->plat, AML_ADDR_SYSTEM, 0xc0b7d4);
    AML_REG_WRITE(0x29, aml_hw->plat, AML_ADDR_SYSTEM, 0xc0b7d4);
    agc1 = AML_REG_READ(aml_hw->plat, AML_ADDR_SYSTEM, 0xc0b7d8);
    agc2 = AML_REG_READ(aml_hw->plat, AML_ADDR_SYSTEM, 0xc0b7dc);
    AML_REG_WRITE(agc_state, aml_hw->plat, AML_ADDR_SYSTEM, 0xc0b7d4);

    noise1 = (agc1 >> 21) - 2048;
    noise2 = (agc2 >> 21) - 2048;

    if (vif->up && (AML_VIF_TYPE(vif) == NL80211_IFTYPE_P2P_GO )) {
        list_for_each_entry_safe(sta, tmp, &vif->ap.sta_list, list) {
            len += sprintf(&buf[len], "p2p%d:%d\n", count, (noise1 + noise2) / 2);
            count++;
        }
    }

    return len;
}
static SYSFS_RO_FILE_OPS(p2p_iNoise);

static ssize_t aml_sysfs_p2p_iSnr_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    struct aml_sta *sta, *tmp;
    int len = 0;
    int count = 0;

    if (vif->up && (AML_VIF_TYPE(vif) == NL80211_IFTYPE_P2P_GO)) {
        list_for_each_entry_safe(sta, tmp, &vif->ap.sta_list, list) {
            len += sprintf(&buf[len],  "p2p%d:%d\n", count,
                           AML_REG_READ(aml_hw->plat, AML_ADDR_MAC_PHY, REG_OF_SYNC_SNR) >> 16);
            count++;
        }
    }


    return len;
}
static SYSFS_RO_FILE_OPS(p2p_iSnr);

static ssize_t aml_sysfs_p2p_i4Rssi0_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    int len = 0;
    int rssi;
    uint32_t agcpow_ct2 = AML_REG_READ(aml_hw->plat, AML_ADDR_SYSTEM, 0xc0b7d8);

    // TODO get and save in fw
    rssi = (agcpow_ct2 >> 21) - 2048;
    len += sprintf(&buf[len], "p2p_i4Rssi0:%d\n", rssi);

    return len;
}
static SYSFS_RO_FILE_OPS(p2p_i4Rssi0);

static ssize_t aml_sysfs_p2p_i4Rssi1_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    int len = 0;
    int rssi;
    uint32_t agcpow_ct2 = AML_REG_READ(aml_hw->plat, AML_ADDR_SYSTEM, 0xc0b7dc);

    rssi = (agcpow_ct2 >> 21) - 2048;
    len += sprintf(&buf[len], "p2p_i4Rssi1:%d\n", rssi);

    return len;
}
static SYSFS_RO_FILE_OPS(p2p_i4Rssi1);

static ssize_t aml_sysfs_p2p_iSnrR0Phase2_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    int len = 0;

    len += sprintf(&buf[len], "p2p_iSnrR0Phase2:%d\n", AML_REG_READ(aml_hw->plat, AML_ADDR_MAC_PHY, REG_OF_SYNC_SNR) >> 16);

    return len;
}
static SYSFS_RO_FILE_OPS(p2p_iSnrR0Phase2);

static ssize_t aml_sysfs_p2p_iSnrR1Phase2_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    int len = 0;

    len += sprintf(&buf[len], "p2p_iSnrR1Phase2:%d\n", AML_REG_READ(aml_hw->plat, AML_ADDR_MAC_PHY, REG_OF_SYNC_SNR) >> 16);

    return len;
}
static SYSFS_RO_FILE_OPS(p2p_iSnrR1Phase2);

static ssize_t aml_sysfs_p2p_TxPkt_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_sta *sta, *tmp;
    int len = 0;
    int count = 0;


    if (vif->up && (AML_VIF_TYPE(vif) == NL80211_IFTYPE_P2P_GO)) {
        list_for_each_entry_safe(sta, tmp, &vif->ap.sta_list, list) {
            len += sprintf(&buf[len],  "p2p%d:%d\n", count,
                           sta->stats.tx_pkts);
            count++;
        }
    }

    return len;
}
static SYSFS_RO_FILE_OPS(p2p_TxPkt);

static ssize_t aml_sysfs_p2p_TxFailPkt_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_sta *sta, *tmp;
    int len = 0;
    int count = 0;

    if (vif->up && (AML_VIF_TYPE(vif) == NL80211_IFTYPE_P2P_GO)) {
        list_for_each_entry_safe(sta, tmp, &vif->ap.sta_list, list) {
            len += sprintf(&buf[len],  "p2p%d:%d\n", count,
                           sta->stats.tx_fails);
            count++;
        }
    }

    return len;
}
static SYSFS_RO_FILE_OPS(p2p_TxFailPkt);

static ssize_t aml_sysfs_p2p_RxPkt_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_sta *sta, *tmp;
    int len = 0;
    int count = 0;

    if (vif->up && (AML_VIF_TYPE(vif) == NL80211_IFTYPE_P2P_GO)) {
        list_for_each_entry_safe(sta, tmp, &vif->ap.sta_list, list) {
            len += sprintf(&buf[len],  "p2p%d:%d\n", count,
                           sta->stats.rx_pkts);
            count++;
        }
    }

    return len;
}
static SYSFS_RO_FILE_OPS(p2p_RxPkt);

static ssize_t aml_sysfs_p2p_RxFail_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    struct aml_sta *sta, *tmp;
    int len = 0;
    int count = 0;

    uint32_t rxfailnum = aml_send_get_rxfail_cnt(aml_hw, vif->vif_index);

    if (vif->up && (AML_VIF_TYPE(vif) == NL80211_IFTYPE_P2P_GO)) {
        list_for_each_entry_safe(sta, tmp, &vif->ap.sta_list, list) {
            len += sprintf(&buf[len],  "p2p%d:%d\n", count,
                           rxfailnum);
            count++;
        }
    }

    return len;
}
static SYSFS_RO_FILE_OPS(p2p_RxFail);

static ssize_t aml_sysfs_p2p_Glitch_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    int len = 0;

    len += sprintf(&buf[len], "\n");

    return len; //len;
}
static SYSFS_RO_FILE_OPS(p2p_Glitch);

static ssize_t aml_sysfs_p2p_Mac_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_sta *sta, *tmp;
    int len = 0;
    int count = 0;

    if (vif->up && (AML_VIF_TYPE(vif) == NL80211_IFTYPE_P2P_GO)) {
        list_for_each_entry_safe(sta, tmp, &vif->ap.sta_list, list) {
            len += sprintf(&buf[len], "p2p%d: %02x:%02x:%02x:%02x:%02x:%02x\n", count,
                           sta->mac_addr[0], sta->mac_addr[1], sta->mac_addr[2],
                           sta->mac_addr[3], sta->mac_addr[4], sta->mac_addr[5]);
            count++;
        }
    }

    return len;
}
static SYSFS_RO_FILE_OPS(p2p_Mac);

static ssize_t aml_sysfs_p2p_RxRate_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct rx_vector_1 *last_rx;
    struct aml_sta *sta, *tmp, *last_rx_sta = NULL;
    int len = 0;
    int count = 0;
    struct aml_rate_info info;

    if (vif->up && (AML_VIF_TYPE(vif) == NL80211_IFTYPE_P2P_GO)) {
        list_for_each_entry_safe(sta, tmp, &vif->ap.sta_list, list) {
            last_rx_sta = sta;
            if (last_rx_sta == NULL)
                break;

            last_rx = &last_rx_sta->stats.last_rx.rx_vect1;
            rate_idx_of_rx_vector(last_rx, &info);
            if (info.format >= FORMATMOD_HE_SU) {
                len += sprintf(&buf[len], "p2p%d:HESS%dMCS%dBW%d\n", count, info.nss + 1,
                                   info.mcs, ((info.bw == PHY_CHNL_BW_80) ? 80 : (info.bw == PHY_CHNL_BW_40) ? 40 : 20));
            } else if (info.format == FORMATMOD_VHT) {
                len += sprintf(&buf[len], "p2p%d:VHTSS%dMCS%dBW%d\n",count, info.nss + 1,
                                   info.mcs, ((info.bw == PHY_CHNL_BW_80) ? 80 : (info.bw == PHY_CHNL_BW_40) ? 40 : 20));
            } else if (info.format >= FORMATMOD_HT_MF) {
                len += sprintf(&buf[len], "p2p%d:HTMCS%dBW%d\n",count, info.mcs, ((info.bw == PHY_CHNL_BW_80) ? 80 : (info.bw == PHY_CHNL_BW_40) ? 40 : 20));
            } else {
                len += sprintf(&buf[len], "p2p%d:%d.%dMBPS\n",count, legrates_lut[last_rx->leg_rate].rate / 10, legrates_lut[last_rx->leg_rate].rate % 10);
            }
            count ++;
        }
    }

    return len;
}
static SYSFS_RO_FILE_OPS(p2p_RxRate);

static ssize_t aml_sysfs_p2p_TxRate_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_sta *sta, *tmp;
    int len = 0;
    int count = 0;
    struct aml_sta_stats *stats = NULL;

    if (vif->up && (AML_VIF_TYPE(vif) == NL80211_IFTYPE_P2P_GO)) {
        list_for_each_entry_safe(sta, tmp, &vif->ap.sta_list, list) {
            sta = vif->sta.ap;
            stats = &sta->stats;
            aml_sta_rate_info(vif, sta, &stats->mcs_max, &stats->no_ss);
            switch (stats->format_mod) {
                case FORMATMOD_NON_HT:
                case FORMATMOD_NON_HT_DUP_OFDM:
                    len += sprintf(&buf[len], "p2p%d:%d.%dMBPS\n",count, legrates_lut[stats->leg_rate].rate / 10, legrates_lut[stats->leg_rate].rate % 10);
                    break;
                case FORMATMOD_HT_MF:
                case FORMATMOD_HT_GF:
                    len += sprintf(&buf[len], "p2p%d:HTMCS%dBW%d\n",count, stats->mcs_max, ((stats->bw_max == PHY_CHNL_BW_80) ? 80 : (stats->bw_max == PHY_CHNL_BW_40) ? 40 : 20));
                    break;
                case FORMATMOD_VHT:
                    len += sprintf(&buf[len], "p2p%d:VHTSS%dMCS%dBW%d\n",count, stats->no_ss + 1, stats->mcs_max,
                        ((stats->bw_max == PHY_CHNL_BW_80) ? 80 : (stats->bw_max == PHY_CHNL_BW_40) ? 40 : 20));
                    break;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 19, 0) || (defined CONFIG_KERNEL_AX_PATCH)
                case FORMATMOD_HE_MU:
                case FORMATMOD_HE_SU:
                case FORMATMOD_HE_ER:
                case FORMATMOD_HE_TB:
                    len += sprintf(&buf[len], "p2p%d:HESS%dMCS%dBW%d\n",count, stats->no_ss + 1, stats->mcs_max,
                        ((stats->bw_max == PHY_CHNL_BW_80) ? 80 : (stats->bw_max == PHY_CHNL_BW_40) ? 40 : 20));
                break;
#endif
                default :
                    return -EFAULT;
            }
            count ++;
        }
    }

    return len;
}
static SYSFS_RO_FILE_OPS(p2p_TxRate);


static ssize_t aml_sysfs_bypass_dfs_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    int len = 0;

    len += sprintf(&buf[len], "bypass_dfs:%d\n", aml_hw->customer_priv.dfs_on);

    return len;
}

static ssize_t aml_sysfs_bypass_dfs_write(struct device *dev, struct device_attribute *attr,
			 const char *user_buf, size_t count)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    u8 new_state = *user_buf - '0';

    if (new_state > 1) {
        AML_INFO("param error\n");
        return -EINVAL;
    }

    if (aml_hw->customer_priv.dfs_on == new_state) {
        AML_INFO("already set\n");
        return count;
    }
    else {
        aml_hw->customer_priv.dfs_on = new_state;
        aml_send_me_chan_config_req(aml_hw);
    }

    return count;
}
static SYSFS_RW_FILE_OPS(bypass_dfs);

static ssize_t aml_sysfs_go_hidden_mode_read(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    int len = 0;

    len += sprintf(&buf[len], "go_hidden_mode:%d\n", aml_hw->customer_priv.go_hidden_mode);

    return len;
}
static ssize_t aml_sysfs_go_hidden_mode_write(struct device *dev, struct device_attribute *attr,
			 const char *user_buf, size_t count)
{
    struct net_device *ndev = container_of(dev, struct net_device, dev);
    struct aml_vif *vif = netdev_priv(ndev);
    struct aml_hw *aml_hw = vif->aml_hw;
    u8 new_state = *user_buf - '0';

    if (new_state > 1) {
        AML_INFO("param error\n");
        return -EINVAL;
    }

    if (aml_hw->customer_priv.go_hidden_mode == new_state) {
        AML_INFO("already set\n");
        return count;
    }

    // TODO update beacon
    AML_INFO("plz use wpa_cli cmd\n");

    return count;
}
static SYSFS_RW_FILE_OPS(go_hidden_mode);

static struct attribute *aml_sysfs_sta_entries[] = {
    &dev_attr_hal_spec.attr,
    &dev_attr_cur_channel.attr,
    &dev_attr_bandwidth.attr,
    &dev_attr_rRssi.attr,
    &dev_attr_iNoise.attr,
    &dev_attr_iSnr.attr,
    &dev_attr_ssid.attr,
    &dev_attr_bssid.attr,
    &dev_attr_TxPktNum.attr,
    &dev_attr_TxFailNum.attr,
    &dev_attr_TxRate.attr,
    &dev_attr_RxPktNum.attr,
    &dev_attr_RxFailNum.attr,
    &dev_attr_Average_RxRate.attr,
    &dev_attr_Data_RxRate.attr,
    &dev_attr_i4RSSI0.attr,
    &dev_attr_i4RSSI1.attr,
    &dev_attr_iSnrR0Phase2.attr,
    &dev_attr_iSnrR1Phase2.attr,
    &dev_attr_Glitch_Total.attr,
    &dev_attr_Glitch_Diff.attr,
    &dev_attr_band_info.attr,
    &dev_attr_band_query_flag.attr,
    &dev_attr_wake_on_pno.attr,
    &dev_attr_pno_sec_mode.attr,
    &dev_attr_connected_status.attr,
    NULL,
};

static struct attribute *aml_sysfs_p2p_entries[] = {
    &dev_attr_p2p_DevNum.attr,
    &dev_attr_p2p_channel.attr,
    &dev_attr_p2p_bandwidth.attr,
    &dev_attr_p2p_rRssi.attr,
    &dev_attr_p2p_iNoise.attr,
    &dev_attr_p2p_iSnr.attr,
    &dev_attr_p2p_i4Rssi0.attr,
    &dev_attr_p2p_i4Rssi1.attr,
    &dev_attr_p2p_iSnrR0Phase2.attr,
    &dev_attr_p2p_iSnrR1Phase2.attr,
    &dev_attr_p2p_TxPkt.attr,
    &dev_attr_p2p_TxFailPkt.attr,
    &dev_attr_p2p_RxPkt.attr,
    &dev_attr_p2p_RxFail.attr,
    &dev_attr_p2p_RxRate.attr,
    &dev_attr_p2p_Glitch.attr,
    &dev_attr_p2p_TxRate.attr,
    &dev_attr_p2p_Mac.attr,
    &dev_attr_bypass_dfs.attr,
    &dev_attr_go_hidden_mode.attr,
    NULL,
};

static struct attribute_group aml_sta_attribute_group = {
        .attrs = aml_sysfs_sta_entries,
};

static struct attribute_group aml_p2p_attribute_group = {
        .attrs = aml_sysfs_p2p_entries,
};

int aml_register_netdevice_sysfs(struct net_device *ndev, enum nl80211_iftype type)
{
    struct attribute_group *temp;
    int ret;

    AML_INFO("name :%s\n", ndev->name);

    if (memcmp(ndev->name, "wlan", 4) == 0)
        temp = &aml_sta_attribute_group;
    else if (memcmp(ndev->name, "p2p", 3) == 0)
        temp = &aml_p2p_attribute_group;
    else
        return 0;

    ret = sysfs_create_group(&ndev->dev.kobj, temp);
    if (ret < 0)
        AML_INFO("ERROR init sysfs failed\n");

    return ret;
}

int aml_unregister_netdevice_sysfs(struct net_device *ndev, enum nl80211_iftype type)
{
    struct kobject *kobj = &ndev->dev.kobj;
    AML_INFO("sd:%p\n", kobj->sd);
/*
    if (type == NL80211_IFTYPE_STATION)
        sysfs_remove_group(&ndev->dev.kobj, &aml_sta_attribute_group);

    if (type == NL80211_IFTYPE_P2P_GO)
        sysfs_remove_group(&ndev->dev.kobj, &aml_p2p_attribute_group);
*/
    return 0;
}

int customer_dbgfs_unregister(struct aml_hw *aml_hw)
{
    aml_destroy_proc_dir(aml_hw);
    return 0;
}

int customer_dbgfs_register(struct aml_hw *aml_hw, const char *name)
{
    int ret = 0;

    if (init_net.proc_net == (struct proc_dir_entry *)NULL) {
        AML_ERR("init proc fail: proc_net == NULL\n");
        return -ENOENT;
    }

    aml_hw->customer_priv.proc_dir = proc_mkdir("wlan", init_net.proc_net);
    if (!aml_hw->customer_priv.proc_dir) {
        AML_ERR("aml_hw->customer_priv.proc_dir == NULL, ERROR\n");
        return -ENOENT;
    }

    ret = aml_create_proc_dir(aml_hw);
    if (ret)
        goto err;
    g_aml_hw = aml_hw;

    aml_hw->customer_priv.registering = true;
    aml_hw->customer_priv.dfs_on = 0; // invalid;
    aml_hw->customer_priv.retry_cnt = 7; // invalid;
    aml_hw->customer_priv.disconnect_info.disconnect_reason = 65535; // invalid;
    aml_hw->customer_priv.disconnect_info.wifi_spec_code = 255; // invalid;
    aml_hw->customer_priv.dbg_level = 2; // default;
    aml_hw->customer_priv.wake_reason = 0xff; // invalid;
    aml_hw->customer_priv.wake_on_pno = 0;

    return 0;
err:
    customer_dbgfs_unregister(aml_hw);
    return -ENOMEM;
}

u32 aml_get_band_info(struct aml_hw *aml_hw, char *buf)
{
    uint32_t chan_time_busy_ms;

    AML_REG_WRITE(0, aml_hw->plat, 0, MAC_EDCA_CCA_BUSY_ADDR);
    g_band_query_flag = false;
    msleep(1000);
    chan_time_busy_ms = AML_REG_READ(aml_hw->plat, 0, MAC_EDCA_CCA_BUSY_ADDR) / 1000;
    g_bandInfo.util_busy = chan_time_busy_ms / 10;
    g_bandInfo.util_idle =  100 - g_bandInfo.util_busy;
    g_band_query_flag = true;
    return (sprintf(buf, "cca_busy:%d                          cca_idle:%d\n",
                    g_bandInfo.util_busy,g_bandInfo.util_idle));
}

