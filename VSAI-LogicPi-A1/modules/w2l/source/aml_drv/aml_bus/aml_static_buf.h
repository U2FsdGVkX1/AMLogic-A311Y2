/**
****************************************************************************************
*
* @file aml_static_buf.h
*
* Copyright (C) Amlogic, Inc. All rights reserved (2022).
*
* @brief Declaration of the preallocing buffer.
*
****************************************************************************************
*/

#ifndef __AML_STATIC_BUF__
#define __AML_STATIC_BUF__

#define PREALLOC_BUF_FW_DL_SIZE         (260 * 1024)
#define PREALLOC_BUF_BUS_SIZE           (320 * 1024)
#ifdef LIGHT_WEIGHT_MEM
// 2k > sizeof(struct dbg_debug_info_tag) = 1572
#define PREALLOC_BUF_TYPE_DUMP_SIZE     (2 * 1024)
#else
// 1290k > sizeof(struct dbg_debug_dump_tag) = 1111588
#define PREALLOC_BUF_TYPE_DUMP_SIZE     (1290 * 1024)
#endif
#define PREALLOC_BUF_TYPE_RXBUF_SIZE    (5 * 340 * 1024)
#define PREALLOC_BUF_TYPE_TXQ_SIZE      (36 * 1024)
#define PREALLOC_BUF_TYPE_AMSDU_SIZE    (388 * 1024)
#define PREALLOC_TRACE_PTR_EXPEND_SIZE  (21 * 1024)
#define PREALLOC_TRACE_STR_EXPEND_SIZE  (84 * 1024)
#define PREALLOC_TRACE_BUF_EXPEND_SIZE  (63 * 1024)
#define PREALLOC_ASSERT_PTR_EXPEND_SIZE (21 * 1024)

enum prealloc_buf_type {
    PREALLOC_BUF_FW_DL = 0,
    PREALLOC_BUF_BUS,

    /* used by Wi-Fi */
    PREALLOC_BUF_TYPE_DUMP,
    PREALLOC_BUF_TYPE_RXBUF,
    PREALLOC_BUF_TYPE_TXQ,
    PREALLOC_BUF_TYPE_AMSDU,
    PREALLOC_TRACE_PTR_EXPEND,
    PREALLOC_TRACE_STR_EXPEND,
    PREALLOC_TRACE_BUF_EXPEND,
    PREALLOC_ASSERT_PTR_EXPEND,

    PREALLOC_BUF_TYPE_MAX,
};

void *__aml_mem_prealloc(enum prealloc_buf_type buf_type, size_t req_size, size_t *actual_size);

static inline void *aml_mem_prealloc(enum prealloc_buf_type buf_type, size_t req_size)
{
    return __aml_mem_prealloc(buf_type, req_size, NULL);
}

int aml_init_wlan_mem(void);
void aml_deinit_wlan_mem(void);

#endif
