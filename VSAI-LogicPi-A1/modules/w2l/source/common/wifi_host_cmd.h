/* SPDX-License-Identifier: GPL-2.0 */
/*
* Copyright (C) 202X Original Author (retain original author information)
* Copyright (C) 202X Amlogic, Inc. All rights reserved.
*
* Description:
*/
#ifndef __WIFI_HOST_CMD_H__
#define __WIFI_HOST_CMD_H__

struct get_fw_wifi_info
{
    uint8_t vif_idx;
};

struct info_rc_stats_cfm {
    uint8_t valid;
    // Current step 0 of the retry chain
    uint8_t sw_retry_step;
    /// Retry chain steps
    uint16_t retry_step_idx[4];
    /// RC statistics - Max number of RC samples, plus one for the HE TB statistics
    struct rc_rate_stats rate_stats[RC_MAX_N_SAMPLE + 1];
};

struct wifi_info
{
    uint32_t pattern;
    uint32_t temp;
    uint32_t initial_gain;
    uint32_t gain;
    uint32_t bfmee_state;
    uint32_t bt_state; //bt tdd or fdd
    uint32_t bt_coex_state;
    uint32_t frame_fcs_rx_end;
    uint32_t frame_fcs_rx_ok;
    uint32_t frame_fcs_rx_bad;
    uint32_t frame_rx_err;
    uint32_t rx_error;
    uint32_t phy_error;
    uint32_t cca_check;
    uint32_t cca_prim_20;
    uint32_t cca_sec_prim_20;
    uint32_t cca_sec_prim_40;
    uint32_t rx_buf_state;
    uint32_t queue_be_info;
    uint32_t queue_bk_info;
    uint32_t queue_vi_info;
    uint32_t queue_vo_info;
    uint32_t mac_hw_state;
    uint32_t bcn_rssi;
    uint32_t snr;
    uint32_t hw_rx_fail_cnt;
    struct info_rc_stats_cfm wifi_info_rc_cfm;
};

/// Structure containing the parameters of the @ref MM_SUB_SET_LINKLOSS_THRESHOLD message.
struct linkloss_threshold_req {
    uint32_t threshold;
};

/// Structure containing the parameters of the @ref MM_SUB_SET_2G4_BANDWIDTH message.
struct mm_2g4_bandwidth {
    uint8_t enable_2g4_20m;
};

struct extra_ssid_param
{
    /// Number of SSIDs to scan for
    uint8_t ssid_cnt;
    /// List of SSIDs to be scanned
    struct mac_ssid ssid[EXTRA_SCAN_SSID_MAX];
};

#endif
