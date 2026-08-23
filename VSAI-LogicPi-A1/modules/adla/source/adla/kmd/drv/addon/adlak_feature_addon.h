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
#include <linux/types.h>

typedef enum Adla_HW_Version {
    r0p0            = 0,
    r1p0            = 1,
    r2p0            = 2,
    r3p0            = 3,
    r3p1            = 4,
}adla_hw_version;

typedef struct Adla_hw_info {
    char *                      hw_ver;
    uint32_t                    hw_release_id;
    uint32_t                    hw_patch_id;
    uint32_t                    mac_no_i8;
    uint32_t                    mac_no_i16;
    uint32_t                    max_frq;
    uint32_t                    GOPS;
    bool                        kernel_vlc;
    bool                        feature_vlc;
    uint64_t                    sram_base;
    uint64_t                    sram_size;
}adla_hw_info;

static adla_hw_info c3_hw_info = {
    .hw_ver             = "r0p0",
    .hw_release_id      = 0,
    .hw_patch_id        = 0,
    .mac_no_i8          = 512,
    .mac_no_i16         = 128,
    .max_frq            = 800,
    .GOPS               = 800,
    .kernel_vlc         = true,
    .feature_vlc        = true,
};
static adla_hw_info s5_hw_info = {
    .hw_ver             = "r1p0",
    .hw_release_id      = 1,
    .hw_patch_id        = 0,
    .mac_no_i8          = 2048,
    .mac_no_i16         = 512,
    .max_frq            = 800,
    .GOPS               = 3200,
    .kernel_vlc         = false,
    .feature_vlc        = false,
};
static adla_hw_info t7c_hw_info = {
    .hw_ver             = "r2p0",
    .hw_release_id      = 2,
    .hw_patch_id        = 0,
    .mac_no_i8          = 2048,
    .mac_no_i16         = 512,
    .max_frq            = 800,
    .GOPS               = 3200,
    .kernel_vlc         = false,
    .feature_vlc        = false,
};
static adla_hw_info t3x_hw_info = {
    .hw_ver             = "r3p0",
    .hw_release_id      = 3,
    .hw_patch_id        = 0,
    .mac_no_i8          = 2048,
    .mac_no_i16         = 512,
    .max_frq            = 800,
    .GOPS               = 3200,
    .kernel_vlc         = true,
    .feature_vlc        = true,
};
static adla_hw_info s6_hw_info = {
    .hw_ver             = "r3p1",
    .hw_release_id      = 3,
    .hw_patch_id        = 1,
    .mac_no_i8          = 2048,
    .mac_no_i16         = 512,
    .max_frq            = 1000,
    .GOPS               = 4000,
    .kernel_vlc         = true,
    .feature_vlc        = true,
};
