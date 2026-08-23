/*******************************************************************************
 * Copyright (C) 2021 Amlogic, Inc. All rights reserved.
 ******************************************************************************/

/*****************************************************************************/
/**
 *
 * @file adlak_platform_addon.c
 * @brief
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   	Who				Date				Changes
 * ----------------------------------------------------------------------------
 * 1.00a sh nn team 2024/04/09	Initial release
 * </pre>
 *
 ******************************************************************************/

/***************************** Include Files *********************************/
/* adjust nn voltage */
#include <linux/arm-smccc.h>
#include <linux/amlogic/media/registers/cpu_version.h>
#include <linux/regulator/consumer.h>

#include "adlak_platform_addon.h"
#include "adlak_os_base.h"
#include "adlak_device.h"
/**************************** Type Definitions *******************************/
typedef enum {
    Regulator_None = 0,
    Regulator_GPIO,
    Regulator_PWM
} nn_regulator_type_t;

typedef enum {
    Adla_Hw_Ver_Default = 0,
    Adla_Hw_Ver_r0p0,
    Adla_Hw_Ver_r1p0,
    Adla_Hw_Ver_r2p0,
} nn_hw_version_t;

typedef enum {
    Adla_Efuse_Type_disable = 0,
    Adla_Efuse_Type_SS = 1,
    Adla_Efuse_Type_TT = 2,
    Adla_Efuse_Type_FF = 3,
} nn_efuse_type_t;
/***************** Macros (Inline Functions) Definitions *********************/
#define GPIO_REGULATOR_NAME      "vdd_npu"
#define PWM_REGULATOR_NAME       "vddnpu"
/************************** Variable Definitions *****************************/
struct regulator            *nn_regulator;
int                         nn_regulator_flag;

/************************** Function Prototypes ******************************/

static unsigned int adlak_get_nn_efuse_chip_type(u64 function_id, u64 arg0, u64 arg1, u64 arg2)
{
    struct arm_smccc_res res;

    arm_smccc_smc((unsigned long)function_id,
              (unsigned long)arg0,
              (unsigned long)arg1,
              (unsigned long)arg2,
              0, 0, 0, 0, &res);
    return res.a0;
}

static nn_regulator_type_t adlak_regulator_nn_available(struct device *dev) {
#ifdef CONFIG_OF
    const char * regulator_name = NULL;
    if (of_property_read_string(dev->of_node, "nn_regulator", &regulator_name)) {
        return Regulator_None;
    }
    if (!strcmp(regulator_name, "gpio_regulator")) {
        return Regulator_GPIO;
    }
    if (!strcmp(regulator_name, "pwm_regulator")) {
        return Regulator_PWM;
    }
#endif
    return Regulator_None;
}

static int adlak_voltage_adjust_r1p0(struct adlak_device *padlak) {
    int ret = -1;
    nn_regulator_type_t         regulator_type;

    regulator_type = adlak_regulator_nn_available(padlak->dev);

    switch (regulator_type) {
    case Regulator_GPIO:
        nn_regulator = devm_regulator_get(padlak->dev, GPIO_REGULATOR_NAME);
        AML_LOG_INFO("ADLA KMD nna regulator by gpio.\n");
        break;
    case Regulator_PWM:
        nn_regulator = devm_regulator_get(padlak->dev, PWM_REGULATOR_NAME);
        AML_LOG_INFO("ADLA KMD nna regulator by pwm.\n");
        break;
    case Regulator_None:
        nn_regulator = NULL;
        ret = 0;
        AML_LOG_INFO("ADLA KMD voltage regulator disable\n");
        break;
    }

    if (!ret) {
        return ret;
    }

    if (IS_ERR(nn_regulator)) {
        ret = -1;
        nn_regulator = NULL;
        AML_LOG_ERR("regulator_get vddnpu fail!\n");
        return ret;
    }

    ret = regulator_enable(nn_regulator);
    if (ret < 0)
    {
        AML_LOG_ERR("regulator_enable error\n");
        devm_regulator_put(nn_regulator);
        nn_regulator = NULL;
        return ret;
    }

    return ret;
}

static int adlak_get_board_adj_vol_env(char *str)
{
    int ret;
    ret = kstrtouint(str, 10, &nn_regulator_flag);
    if (ret) {
        return -EINVAL;
    }
    return 0;
}
__setup("nn_adj_vol=", adlak_get_board_adj_vol_env);

static int adlak_voltage_adjust_r2p0(struct adlak_device *padlak) {
/*****************************************************************************
 * pwm              0%    %5    %10   15%   20%   25%   30%   35%   40%   45%
 * board v1 vol(v)  0.89  0.88  0.87  0.86  0.85  0.84  0.83  0.82  0.81  0.80
 * board v2 vol(v)  0.93  0.92  0.91  0.90  0.89  0.88  0.87  0.86  0.85  0.84
 * reg value
 *****************************************************************************/
/*****************************************************************************
 * pwm              50%   55%   60%   65%   70%   75%   80%   85%   90%   95%
 * board v1 vol(v)  0.79  0.78  0.77  0.76  0.75  0.74  0.73  0.72  0.71  0.70
 * board v2 vol(v)  0.83  0.82  0.81  0.80  0.79  0.78  0.77  0.76  0.75  0.74
 * reg value
 *****************************************************************************/
#define NN_T7C_BOARD_V1_ID         1
#define NN_T7C_BOARD_V2_ID         2
#define NN_T7C_BOARD_V1_890MV      890000
#define NN_T7C_BOARD_V1_870MV      870000
#define NN_T7C_BOARD_V2_910MV      870000
#define NN_T7C_BOARD_V2_890MV      850000
#define NN_T7C_BOARD_V2_870MV      830000
#define NN_T7C_BOARD_V2_850MV      810000
#define NN_EFUSE_TYPE_NPU          2
#define NN_GET_DVFS_TABLE_INDEX    0x82000088
#define NN_MESON_CPU_VERSION_LVL_PACK 2
#define NN_T7C_PACKAGE_TYPE_A311D2 1
#define NN_T7C_PACKAGE_TYPE_POP1   2
#define NN_T7C_PACKAGE_TYPE_V918D  3
#define NN_T7C_PACKAGE_TYPE_A311D2J 4
    int          ret = 0;
    int          nn_voltage_value = 0;
    unsigned int nn_package_id;
    unsigned int nn_efuse_type = 0;

    nn_package_id = get_meson_cpu_version(NN_MESON_CPU_VERSION_LVL_PACK);
    nn_efuse_type = adlak_get_nn_efuse_chip_type(NN_GET_DVFS_TABLE_INDEX, NN_EFUSE_TYPE_NPU, 0, 0);
    adlak_os_printf("ADLA KMD nn_adj_vol = %d, nn_package_id = %u, nn_efuse_type = %u\n", nn_regulator_flag, nn_package_id, nn_efuse_type);

    nn_regulator = devm_regulator_get(padlak->dev, PWM_REGULATOR_NAME);
    if (IS_ERR(nn_regulator)) {
        ret = -1;
        nn_regulator = NULL;
        AML_LOG_ERR("regulator_get vddnpu fail!\n");
        return ret;
    }

    ret = regulator_enable(nn_regulator);
    if (ret < 0)
    {
        AML_LOG_ERR("regulator_enable error\n");
        devm_regulator_put(nn_regulator);
        nn_regulator = NULL;
        return ret;
    }

    /* nn_regulator_flag == 0 board version is v1(old legacy board) */
    if (!nn_regulator_flag) {
        if (nn_package_id == NN_T7C_PACKAGE_TYPE_A311D2J) {
            nn_voltage_value = NN_T7C_BOARD_V1_870MV;
        }
        else {
            nn_voltage_value = NN_T7C_BOARD_V1_890MV;
        }
    }
    /* nn_regulator_flag == 1 board version is v2 or other customer ver (new type board)*/
    else {
        if (nn_package_id == NN_T7C_PACKAGE_TYPE_A311D2J) {
            nn_voltage_value = NN_T7C_BOARD_V2_870MV;
        }
        else {
            switch ((nn_efuse_type_t)nn_efuse_type) {
            case Adla_Efuse_Type_SS:
                nn_voltage_value = NN_T7C_BOARD_V2_910MV;
                break;
            case Adla_Efuse_Type_TT:
                nn_voltage_value = NN_T7C_BOARD_V2_870MV;
                break;
            case Adla_Efuse_Type_FF:
                nn_voltage_value = NN_T7C_BOARD_V2_850MV;
                break;
            default:
                /* if no efuse id, PDVFS is disable, we set default voltage to 890mv*/
                nn_voltage_value = NN_T7C_BOARD_V2_890MV;
                break;
            }
        }
    }
    if (nn_voltage_value) {
        ret = regulator_set_voltage(nn_regulator, nn_voltage_value, nn_voltage_value);
    }
    if (ret < 0) {
        regulator_disable(nn_regulator);
        devm_regulator_put(nn_regulator);
        nn_regulator = NULL;
        AML_LOG_ERR("regulator_set_voltage %dmv Error\n", nn_voltage_value);
    }
    else {
        AML_LOG_DEBUG("regulator_set_voltage %dmv OK\n", nn_voltage_value);
    }

    return ret;
}

static int adlak_voltage_adjust_default(struct adlak_device *padlak) {
    nn_regulator = NULL;
    return 0;
}

static nn_hw_version_t adlak_get_nn_hw_version(struct device *dev) {
#ifdef CONFIG_OF
    const char * adla_hw_ver_name = NULL;
    if (of_property_read_string(dev->of_node, "nn_hw_version", &adla_hw_ver_name)) {
        return Adla_Hw_Ver_Default;
    }
    if (!strcmp(adla_hw_ver_name, "r2p0")) {
        return Adla_Hw_Ver_r2p0;
    }
    if (!strcmp(adla_hw_ver_name, "r1p0")) {
        return Adla_Hw_Ver_r1p0;
    }
#endif
    return Adla_Hw_Ver_Default;
}

static int adlak_voltage_init(void *data) {
    int ret = 0;
    struct adlak_device *padlak = (struct adlak_device *)data;
    nn_hw_version_t             hw_ver;

    hw_ver = adlak_get_nn_hw_version(padlak->dev);

    switch (hw_ver) {
    case Adla_Hw_Ver_r2p0:
        ret = adlak_voltage_adjust_r2p0(padlak);
        break;
    case Adla_Hw_Ver_r1p0:
        ret = adlak_voltage_adjust_r1p0(padlak);
        break;
    case Adla_Hw_Ver_r0p0:
    case Adla_Hw_Ver_Default:
        ret = adlak_voltage_adjust_default(padlak);
        break;
    }

    if (!ret)
        AML_LOG_DEBUG("ADLA KMD voltage init success ");

    return ret;
}

static int adlak_voltage_deinit(void *data) {
    int ret = 0;

    if (nn_regulator)
    {
        ret = regulator_disable(nn_regulator);
        if (ret < 0)
        {
            AML_LOG_ERR("regulator_disable error\n");
        }

        devm_regulator_put(nn_regulator);
    }

    if (!ret)
        AML_LOG_DEBUG("ADLA KMD voltage uninit success ");

    return ret;
}
static int adlak_clk_parent_init(void *data) {
    struct adlak_device *padlak = (struct adlak_device *)data;
    nn_hw_version_t             hw_ver;

    hw_ver = adlak_get_nn_hw_version(padlak->dev);

    switch (hw_ver) {
    case Adla_Hw_Ver_r2p0:
        /*
            if clk tree power off,it will switch adla_clk to adla_clk_parent1 auto;
            adla_core_clk -->adla_clk -->adla_clk_parent0/adla_clk_parent1;
        */
        padlak->clk = devm_clk_get(padlak->dev, "adla_clk");
        if (IS_ERR(padlak->clk)) {
            AML_LOG_ERR("Failed to get clk\n");
        }
        padlak->clk_parent0 = devm_clk_get(padlak->dev, "adla_clk_parent0");
        if (IS_ERR(padlak->clk_parent0)) {
            AML_LOG_ERR("Failed to get clk_parent0\n");
        }
        padlak->clk_parent1 = devm_clk_get(padlak->dev, "adla_clk_parent1");
        if (IS_ERR(padlak->clk_parent1)) {
            AML_LOG_ERR("Failed to get clk_parent1\n");
        }
        break;
    case Adla_Hw_Ver_r1p0:
    case Adla_Hw_Ver_r0p0:
    case Adla_Hw_Ver_Default:
        AML_LOG_DEBUG("ADLA don't need multi clk parent init");
        break;
    }

    return 0;
}

static void adlak_clk_parent_deinit(void *data) {
    /* do noting */
}

static long adlak_axi_sram_setup(unsigned long function_id, unsigned long arg0) {
    struct arm_smccc_res res;

    arm_smccc_smc(function_id, arg0, 0, 0, 0, 0, 0, 0, &res);
    return res.a0;
}

static int adlak_axi_sram_init(void *data) {
    struct adlak_device *padlak = (struct adlak_device *)data;
    u32 adlak_smc_cmd = 0;
    int ret = -1;

#ifdef CONFIG_OF
    of_property_read_u32(padlak->dev->of_node, "adla_smc_cmd", &adlak_smc_cmd);
#endif

    AML_LOG_WARN("adlak_smc_cmd: 0x%x\n", adlak_smc_cmd);
    if (adlak_smc_cmd != 0) {
        ret = adlak_axi_sram_setup((unsigned long)adlak_smc_cmd, 0);
        if (ret != 0) {
            return -1;
        }
    }
    return 0;
}

static void adlak_axi_sram_deinit(void *data) {
    /* do noting */
}

int adlak_sys_init(void *data) {
    int ret = 0;

    ret = adlak_voltage_init(data);
    if (ret < 0)
    {
        AML_LOG_ERR("voltage init fail!\n");
        return ret;
    }

    /* init adla axi sram access */
    ret = adlak_axi_sram_init(data);
    if (ret < 0) {
        AML_LOG_ERR("axi sram init fail!\n");
        //return ret;
    }

    /* init adla multi clk parent soc(T7c) */
    ret = adlak_clk_parent_init(data);
    return ret;
}

int adlak_sys_deinit(void *data) {
    int ret = 0;

    adlak_clk_parent_deinit(data);
    adlak_axi_sram_deinit(data);
    ret = adlak_voltage_deinit(data);
    return ret;
}
