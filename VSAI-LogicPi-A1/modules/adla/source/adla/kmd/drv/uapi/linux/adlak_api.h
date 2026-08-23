/*******************************************************************************
 * Copyright (C) 2021 Amlogic, Inc. All rights reserved.
 ******************************************************************************/

/*****************************************************************************/
/**
 *
 * @file adlak_api.h
 * @brief
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   	Who				Date				Changes
 * ----------------------------------------------------------------------------
 * 1.00a shiwei.sun@amlogic.com	2021/06/05	Initial release
 * </pre>
 *
 ******************************************************************************/

#ifndef __ADLAK_API_H__
#define __ADLAK_API_H__

/***************************** Include Files *********************************/
#include <linux/ioctl.h>
#include <linux/types.h>

#ifndef __KERNEL__
#define __user
#define __packed __attribute__((__packed__))
#include <sys/ioctl.h>
#endif

/*********This dividing line is for avoid clang-format adjusting the order ***/
#include "adlak_api_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************** Constant Definitions *****************************/

/**************************Global Variable************************************/

/**************************Type Definition and Structure**********************/

#define ADLAK_IOCTL_MAGIC 'X'

#define ADLAK_IOCTL_QUERYCAP _IOWR(ADLAK_IOCTL_MAGIC, 0, struct adlak_caps_desc)
#define ADLAK_IOCTL_REQBUF _IOWR(ADLAK_IOCTL_MAGIC, 1, struct adlak_buf_req)
#define ADLAK_IOCTL_FREEBUF _IOWR(ADLAK_IOCTL_MAGIC, 2, uint64_t)
#define ADLAK_IOCTL_REGISTER_NETWORK _IOWR(ADLAK_IOCTL_MAGIC, 3, struct adlak_network_desc)
#define ADLAK_IOCTL_DESTROY_NETWORK _IOWR(ADLAK_IOCTL_MAGIC, 4, struct adlak_network_del_desc)
#define ADLAK_IOCTL_INVOKE _IOWR(ADLAK_IOCTL_MAGIC, 5, struct adlak_network_invoke_desc)
#define ADLAK_IOCTL_INVOKE_CANCEL _IOWR(ADLAK_IOCTL_MAGIC, 6, struct adlak_network_invoke_del_desc)
#define ADLAK_IOCTL_GET_STAT _IOWR(ADLAK_IOCTL_MAGIC, 7, struct adlak_get_stat_desc)
#define ADLAK_IOCTL_FLUSH_CACHE _IOW(ADLAK_IOCTL_MAGIC, 8, struct adlak_buf_flush)

// #define ADLAK_IOCTL_REQIO _IOWR(ADLAK_IOCTL_MAGIC, 9, struct adlak_io_req)
#define ADLAK_IOCTL_TEST _IOWR(ADLAK_IOCTL_MAGIC, 10, struct adlak_test_desc)
#define ADLAK_IOCTL_DEBUG_MEM_COPY _IOW(ADLAK_IOCTL_MAGIC, 11, uint64_t)

#define ADLAK_IOCTL_ATTACH_EXTERN_BUF _IOWR(ADLAK_IOCTL_MAGIC, 12, struct adlak_extern_buf_info)
#define ADLAK_IOCTL_DETTACH_EXTERN_BUF _IOW(ADLAK_IOCTL_MAGIC, 13, uint64_t)
#define ADLAK_IOCTL_PROFILE_CFG _IOWR(ADLAK_IOCTL_MAGIC, 14, struct adlak_profile_cfg_desc)
#define ADLAK_IOCTL_WAIT_UNTIL_FINISH _IOWR(ADLAK_IOCTL_MAGIC, 15, struct adlak_get_stat_desc)

#define ADLAK_IOCTL_REGISTER_NETWORKS _IOWR(ADLAK_IOCTL_MAGIC, 25, struct adlak_networks_desc)

#define ADLAK_IOCTL_SET_CONTEXT_ATTRIBUTE \
    _IOWR(ADLAK_IOCTL_MAGIC, 16, struct adlak_context_attribute)

#define ADLAK_IOCTL_REGISTER_TEE_NETWORK _IOWR(ADLAK_IOCTL_MAGIC, 17, struct adlak_tee_network_desc)
#define ADLAK_IOCTL_DESTROY_TEE_NETWORK _IOWR(ADLAK_IOCTL_MAGIC, 18, struct adlak_network_del_desc)
#define ADLAK_IOCTL_TEE_INVOKE _IOWR(ADLAK_IOCTL_MAGIC, 19, struct adlak_tee_network_invoke_desc)
#define ADLAK_IOCTL_TEE_QUERY_ADDR _IOWR(ADLAK_IOCTL_MAGIC, 20, struct adlak_tee_query_addr)
#define ADLAK_IOCTL_TEE_PROTECT_ADDR _IOWR(ADLAK_IOCTL_MAGIC, 21, struct adlak_tee_protect_addr)

#define ADLAK_IOCTL_SET_INFO _IOWR(ADLAK_IOCTL_MAGIC, 50, struct adlak_dev_info_set_req)
#define ADLAK_IOCTL_GET_INFO _IOWR(ADLAK_IOCTL_MAGIC, 51, struct adlak_dev_info_get_req)
/************************** Function Prototypes ******************************/

#ifdef __cplusplus
}
#endif

#endif /* __ADLAK_API_H__ end define*/
