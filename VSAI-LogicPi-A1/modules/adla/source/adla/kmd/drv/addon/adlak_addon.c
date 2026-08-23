/*******************************************************************************
 * Copyright (C) 2024 Amlogic, Inc. All rights reserved.
 ******************************************************************************/

/*****************************************************************************/
/**
 *
 * @file adlak_addon.c
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

#include "adlak_typedef.h"
#include "adlak_addon.h"
#include "adlak_device.h"
#include "adlak_mm.h"
#include "adlak_submit.h"
#include "adlak_feature_addon.h"
int *adlak_dev_state;

int adlak_get_hw_info (struct adlak_device *padlak, char *buf, size_t size)
{
    struct adlak_caps_desc *uapi_caps = (struct adlak_caps_desc *)padlak->dev_caps.data;
    int count                       = 0;
    int buf_size                    = size;
    uint32_t cur_freq               = 0;
    adla_hw_info *hw_info           = NULL;
    uint32_t dev_hw_version         = 0xffffffff;

    dev_hw_version = uapi_caps->hw_ver;
    cur_freq = (uint32_t)padlak->clk_core_freq_set;

    switch (dev_hw_version) {
        case 0x00000000 :
            hw_info = &c3_hw_info;
            break;
        case 0x00000100 :
            hw_info = &s5_hw_info;
            break;
        case 0x00000200 :
            hw_info = &t7c_hw_info;
            break;
        case 0x00000300 :
            hw_info = &t3x_hw_info;
            break;
        case 0x00000301 :
            hw_info = &s6_hw_info;
            break;
        default :
            count = adlak_os_snprintf(buf, buf_size, "devices not support.\n");
            return count;
    }

    hw_info->sram_base = padlak->hw_res.adlak_sram_pa;
    hw_info->sram_size = padlak->hw_res.adlak_sram_size;

    count = adlak_os_snprintf(buf, buf_size, "npu hw info :\n");
    count += adlak_os_snprintf(buf + count, buf_size - count, "    adla hw version : %s\n", hw_info->hw_ver);
    count += adlak_os_snprintf(buf + count, buf_size - count, "    adla i8 mac_cnt : %d\n", hw_info->mac_no_i8);
    count += adlak_os_snprintf(buf + count, buf_size - count, "    adla max clk    : %d\n", hw_info->max_frq);
    count += adlak_os_snprintf(buf + count, buf_size - count, "    adla Gops       : %d\n", hw_info->GOPS);

    if (hw_info->kernel_vlc) {
        count += adlak_os_snprintf(buf + count, buf_size - count, "    adla kernel vlc : true\n");
    } else {
        count += adlak_os_snprintf(buf + count, buf_size - count, "    adla kernel vlc : false\n");
    }
    if (hw_info->feature_vlc) {
        count += adlak_os_snprintf(buf + count, buf_size - count, "    adla feature vlc: true\n");
    } else {
        count += adlak_os_snprintf(buf + count, buf_size - count, "    adla feature vlc: false\n");
    }
    count += adlak_os_snprintf(buf + count, buf_size - count, "    adla cur clk    : %d\n", (int)(cur_freq /1000 /1000));

    count += adlak_os_snprintf(buf + count, buf_size - count, "    adla sram base  : 0x%llx\n", hw_info->sram_base);
    count += adlak_os_snprintf(buf + count, buf_size - count, "    adla sram size  : 0x%llx\n", hw_info->sram_size);

    return count;
}

int adlak_set_clk_core(struct adlak_device *padlak, uint32_t value)
{
#if CONFIG_ADLAK_DPM_EN
    struct adlak_power_info *pdpm_info;
    pdpm_info = (struct adlak_power_info *)padlak->pdpm;
#endif
    padlak->clk_core_freq_set = value;


    /*set clk immediately*/
    if (!padlak->is_suspend) {
        adlak_platform_set_clock((void *)padlak, true, padlak->clk_core_freq_set, padlak->clk_axi_freq_set);
    } else {
        /*no task currently */
        adlak_platform_resume(padlak);
    }

#if CONFIG_ADLAK_DPM_EN

    pdpm_info->core_freq_expect = padlak->clk_core_freq_real;

    pdpm_info->freq_cfg_list[0][0] = padlak->clk_core_freq_set;
#endif
    padlak->clk_core_freq_set  = padlak->clk_core_freq_real;

    return 0;

}

int adlak_enable_save_context_time;
int adlak_get_utilization(struct adlak_device *padlak, char *buf, size_t size) {
    struct adlak_workqueue *pwq             = &padlak->queue;
    struct adlak_task *ptask = NULL, *ptask_tmp = NULL;
    struct adlak_caps_desc *uapi_caps       = (struct adlak_caps_desc *)padlak->dev_caps.data;
    struct adlak_model_attr *pmodel_attr    = NULL;
    int32_t utilization                     = 0;
    int count                               = 0;
    int buf_size                            = size;
    uint32_t time                           = 0;
    uint32_t dev_hw_version                 = 0xffffffff;
    uint64_t dev_macc_count                 = 0;
    uint32_t cur_freq                       = 0;
    uint64_t n, base;

    cur_freq = (uint32_t)padlak->clk_core_freq_set / 1000000; //MHz

    dev_hw_version = uapi_caps->hw_ver;

    switch (dev_hw_version) {
        case 0x00000000 :
            dev_macc_count = 512 * cur_freq; //Mops
            break;
        case 0x00000100 :
        case 0x00000200 :
        case 0x00000300 :
            dev_macc_count = 2048 * cur_freq; //Mops
            break;
        case 0x00000301 :
            dev_macc_count = 2048 * cur_freq; //Mops
            break;
        default :
            count += adlak_os_snprintf(buf + count, buf_size - count, "dev hw version error,please check!\n");
            return count;
    }
    if (adlak_enable_save_context_time == 0) {
        count += adlak_os_snprintf(buf + count, buf_size - count, "please [ echo 1 >utilization ] first\n");
        return count;
    }
    if (pwq->sched_num > 0) {
        list_for_each_entry_safe(ptask, ptask_tmp, &pwq->scheduled_list, head) {
            pmodel_attr                 = adlak_get_model_attr(ptask->context, ptask->sub_tasks_idx);

            time = ptask->context->invoke_time_elapsed_total;
            if ((0 == time) || (pmodel_attr == NULL)) {
                count += adlak_os_snprintf(buf + count, buf_size - count, "please wait ...\n");
            } else {
                // nn utilization formula is
                // utilization = (model_macc/1000/1000 * 1000000/time)/(dev_macc_count)*100;
                // model_macc unit is '1 op', represent model sum macc, div 1000 twice which convert the unit to 'Mop'
                // time unit is 'us', represent model inference time, mul 1000000 which convert the unit to 's'
                // the result of "model_macc/1000/1000 * 1000000 /time" unit is 'Mops'
                // dev_macc_count unit is 'Mops', represent adla computing power
                // the final result represent unitilization of the current model running on adla, mul 100 which convert to percentage
                n = pmodel_attr->macc_count *100;
                base = dev_macc_count * time;
                utilization = div64_u64(n + base -1, base); //round up
            }
        }
    }
    count += adlak_os_snprintf(buf + count, buf_size - count, "    adla utilization : %d %% \n", utilization);

    return count;
}

int adlak_get_dev_info(struct adlak_context *         context,
                         struct adlak_dev_info_get_req *info_req) {
    int     ret = 0;
    struct adlak_device *padlak = context->padlak;
    struct adlak_mem_usage  mem_usage;
    struct adlak_caps_desc *uapi_caps = (struct adlak_caps_desc *)padlak->dev_caps.data;

    switch (info_req->info_type) {
        case ADLAK_DEV_INFO_TYPE_ALL :
            info_req->clk_core_freq_real = padlak->clk_core_freq_real;
            info_req->clk_core_freq_set = padlak->clk_core_freq_set;

             if (padlak->is_suspend) {
                info_req->device_stat = ADLAK_DEV_INFO_POWEROFF;
            } else {
                info_req->device_stat = *adlak_dev_state;
            }

            info_req->dpm_period_set = padlak->dpm_period_set;
            info_req->dev_hw_version = uapi_caps->hw_ver;
            adlak_mem_get_usage(&mem_usage);
            info_req->mem_used =
                mem_usage.alloced_kmd + mem_usage.alloced_umd + mem_usage.share_buf_size;
            break;
        case ADLAK_DEV_INFO_TYPE_CLK :
            info_req->clk_core_freq_real = padlak->clk_core_freq_real;
            info_req->clk_core_freq_set = padlak->clk_core_freq_set;
            break;
        case ADLAK_DEV_INFO_TYPE_STAT :
            if (padlak->is_suspend) {
                info_req->device_stat = ADLAK_DEV_INFO_POWEROFF;
            } else {
                info_req->device_stat = *adlak_dev_state;
            }
            break;
        case ADLAK_DEV_INFO_TYPE_DPM :
            info_req->dpm_period_set = padlak->dpm_period_set;
            break;
        case ADLAK_DEV_INFO_TYPE_HW :
            info_req->dev_hw_version = uapi_caps->hw_ver;
            break;
        case ADLAK_DEV_INFO_TYPE_MEM :
            adlak_mem_get_usage(&mem_usage);
            info_req->mem_used =
                mem_usage.alloced_kmd + mem_usage.alloced_umd + mem_usage.share_buf_size;
            break;
        default :
            AML_LOG_ERR("not support get %d info.",info_req->info_type);
            break;

    }

    return ret;
}

int adlak_set_dev_info(struct adlak_context *         context,
                         struct adlak_dev_info_set_req *info_req) {
    struct adlak_device *padlak = context->padlak;
    uint32_t            clk_value = 0;
    uint32_t            dpm_period_value = 0;
    int64_t             macc_count_value = 0;

    switch (info_req->info_type) {
        case ADLAK_DEV_INFO_TYPE_CLK :
            clk_value = (uint32_t)info_req->value;
            adlak_set_clk_core(padlak,clk_value);
            break;
        case ADLAK_DEV_INFO_TYPE_DPM :
            dpm_period_value = (uint32_t) info_req->value;
            padlak->queue.dev_inference.dpm_period_set = dpm_period_value;
            padlak->dpm_period_set = dpm_period_value;
            break;
        case ADLAK_DEV_INFO_TYPE_MACC_COUNT :
            macc_count_value = (int64_t) info_req->value;
            // context->macc_count = macc_count_value;
            break;
        default :
            AML_LOG_ERR("not support set %d info.",info_req->info_type);
            break;
    }

    return 0;
}

