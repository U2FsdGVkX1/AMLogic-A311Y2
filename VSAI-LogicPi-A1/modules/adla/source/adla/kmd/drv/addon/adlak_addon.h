/*******************************************************************************
 * Copyright (C) 2024 Amlogic, Inc. All rights reserved.
 ******************************************************************************/

/*****************************************************************************/
/**
 *
 * @file adlak_addon.h
 * @brief
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   	Who				Date				Changes
 * ----------------------------------------------------------------------------
 * 1.00a sh nn team@amlogic.com	2024/04/06	Initial release
 * </pre>
 *
 ******************************************************************************/

#include "adlak_context.h"
#include "adlak_api.h"

#define CONFIG_ADLAK_FREQ_ADJUST_NO (5)
/**************************** Type Definitions *******************************/

struct adlak_power_info {
    int32_t freq_cfg_idx;
    int32_t freq_cfg_list[2][CONFIG_ADLAK_FREQ_ADJUST_NO];  // 0:core freq; 1:axi freq
    int32_t core_freq_cur;
    int32_t axi_freq_cur;
    int32_t core_freq_expect;
    int32_t axi_freq_expect;
};

enum ADLAK_DEV_INFO_STATE {
    /* refer enum ADLAK_DEVICE_STATE */
    ADLAK_DEV_INFO_INIT = 1,
    ADLAK_DEV_INFO_ERR,
    ADLAK_DEV_INFO_IDLE,
    ADLAK_DEV_INFO_BUSY,
    ADLAK_DEV_INFO_POWEROFF,
};

enum adlak_info_type {
    ADLAK_DEV_INFO_TYPE_ALL = 0,
    ADLAK_DEV_INFO_TYPE_CLK,
    ADLAK_DEV_INFO_TYPE_STAT,
    ADLAK_DEV_INFO_TYPE_DPM,
    ADLAK_DEV_INFO_TYPE_HW,
    ADLAK_DEV_INFO_TYPE_MEM,
    ADLAK_DEV_INFO_TYPE_MACC_COUNT,

};

int adlak_get_hw_info (struct adlak_device *padlak, char *buf, size_t size);
int adlak_set_clk_core(struct adlak_device *padlak, uint32_t value);
int adlak_get_utilization(struct adlak_device *padlak, char *buf, size_t size);


int adlak_get_dev_info(struct adlak_context *         context,
                         struct adlak_dev_info_get_req *info_req);

int adlak_set_dev_info(struct adlak_context *         context,
                         struct adlak_dev_info_set_req *info_req);


