/*******************************************************************************
 * Copyright (C) 2024 Amlogic, Inc. All rights reserved.
 ******************************************************************************/

/*****************************************************************************/
/**
 *
 * @file adlak_tee.h
 * @brief
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   	Who				Date				Changes
 * ----------------------------------------------------------------------------
 * 1.00a shiwei.sun@amlogic.com	2024/07/17	Initial release
 * </pre>
 *
 ******************************************************************************/

#ifndef __ADLAK_TEE_H_4A1B2B57EDE1CC6D__
#define __ADLAK_TEE_H_4A1B2B57EDE1CC6D__

/***************************** Include Files *********************************/

#include "adlak_api.h"
#include "adlak_common.h"
#include "adlak_context.h"
#include "adlak_device.h"
#include "adlak_hw.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************** Constant Definitions *****************************/

/**************************Global Variable************************************/

/**************************Type Definition and Structure**********************/

struct adlak_tee_model_attr {
    struct adlak_context *context;
    uint32_t              hw_timeout_ms;
    int32_t               invoke_count;

    struct adlak_task
        *invoke_attr_rsv;  // In order to avoid continuous application and release of task memory

    uint64_t tee_ctx_handle;
    uint32_t priority;  // submit priority
};

/************************** Function Prototypes ******************************/
int adlak_tee_mem_init(struct adlak_device *padlak);

void adlak_tee_mem_deinit(struct adlak_device *padlak);

int adlak_tee_net_register_request(struct adlak_context *         context,
                                   struct adlak_tee_network_desc *psubmit_desc);

int adlak_tee_net_unregister_request(struct adlak_context *         context,
                                     struct adlak_network_del_desc *submit_del);

int adlak_tee_invoke_request(struct adlak_context *                context,
                             struct adlak_tee_network_invoke_desc *pinvoke_desc);
int adlak_tee_query_addr(struct adlak_context *       context,
                         struct adlak_tee_query_addr *tee_query_addr);

int adlak_tee_protect_addr(struct adlak_context *         context,
                           struct adlak_tee_protect_addr *tee_protect_addr);

void adlak_tee_model_destroy(struct adlak_tee_model_attr *ptee_model_attr);

int adlak_submit_tee_task(struct adlak_task *ptask, uint64_t smmu_entry);

#ifdef __cplusplus
}
#endif

#endif /* __ADLAK_TEE_H_4A1B2B57EDE1CC6D__ end define*/
