/*******************************************************************************
 * Copyright (C) 2024 Amlogic, Inc. All rights reserved.
 ******************************************************************************/

/*****************************************************************************/
/**
 *
 * @file adlak_tee.c
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

/***************************** Include Files *********************************/
#include "adlak_tee.h"

#include "adlak_api.h"
#include "adlak_common.h"
#include "adlak_context.h"
#include "adlak_device.h"
#include "adlak_dpm.h"
#include "adlak_hw.h"
#include "adlak_mm.h"
#include "adlak_queue.h"
#include "adlak_submit.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

struct adlak_mem_tee {
    struct adlak_mem_usage usage;
    adlak_os_mutex_t       mutex;
    struct adlak_device *  padlak;
    struct device *        dev;
    phys_addr_t            pa;
    size_t                 size;
};

struct adla_heap_buffer {
    struct dma_heap *heap;
    struct list_head attachments;
    struct mutex     lock;  // protect list operation
    unsigned long    len;
    struct sg_table  sg_table;
    int              vmap_cnt;
    void *           vaddr;
    bool             uncached;
    struct dma_buf * buf;
};

/***************** Macros (Inline Functions) Definitions *********************/

#if 0
/************************** Variable Definitions *****************************/

static struct adlak_mem_tee *ptr_mm_tee = NULL;

/************************** Function Prototypes ******************************/
#if defined(CONFIG_ADLAK_EMU_EN) && (CONFIG_ADLAK_EMU_EN == 1)
u32 tee_register_mem(u32 type, phys_addr_t pa, size_t size) { return 0; }
#else
extern u32 tee_register_mem(u32 type, phys_addr_t pa, size_t size);
#endif

static int tee_allocate_mem_pool(phys_addr_t *pa, size_t size) { return 0; }

void adlak_tee_mem_deinit(struct adlak_device *padlak) {
    AML_LOG_INFO("%s", __func__);
    if (ptr_mm_tee) {
        if (ptr_mm_tee->pa != ADLAK_INVALID_ADDR) {
            // TODO free mem pool
            ptr_mm_tee->pa = ADLAK_INVALID_ADDR;
        }
        adlak_os_free(ptr_mm_tee);
        ptr_mm_tee = NULL;
    }
}

int adlak_tee_mem_init(struct adlak_device *padlak) {
    int         ret = 0;
    phys_addr_t pa;
    size_t      size = 4 * 0x100000;  // 4MBytes
    AML_LOG_INFO("%s", __func__);
    if ((!ptr_mm_tee)) {
        ptr_mm_tee = adlak_os_zalloc(sizeof(struct adlak_mem_tee), ADLAK_GFP_KERNEL);
        if (unlikely(!ptr_mm_tee)) {
            ret = -1;
            goto end;
        }
    }

    adlak_os_mutex_init(&ptr_mm_tee->mutex);
    ptr_mm_tee->padlak = padlak;
    ptr_mm_tee->pa     = ADLAK_INVALID_ADDR;
    if (tee_allocate_mem_pool(&pa, size)) {
        ret = -1;
        AML_LOG_ERR("tee allocat pool failed.");
        goto end;
    }
    ptr_mm_tee->pa   = pa;
    ptr_mm_tee->size = size;
    //  register mem to tee
    tee_register_mem(0, ptr_mm_tee->pa, ptr_mm_tee->size);
    return 0;
end:
    return ret;
}

#endif

#ifdef CONFIG_ADLAK_TEE_DUMP_DRAM
#define CONFIG_ADLAK_TEE_MEM_PROTECT_EN (0)
#else
#define CONFIG_ADLAK_TEE_MEM_PROTECT_EN (1)
#endif

#if !(defined(CONFIG_ADLAK_EMU_EN) && (CONFIG_ADLAK_EMU_EN == 1))
extern void     tee_unprotect_mem(uint32_t handle);
extern int      tee_config_device_state(int dev_id, int secure);
extern uint32_t tee_protect_mem_by_type(uint32_t type, phys_addr_t start, size_t size,
                                        uint32_t *handle);
#else

void     tee_unprotect_mem(uint32_t handle) {}
int      tee_config_device_state(int dev_id, int secure) { return 0; }
uint32_t tee_protect_mem_by_type(uint32_t type, phys_addr_t start, size_t size, uint32_t *handle) {
    return 0;
}

void            dma_buf_put(struct dma_buf *dmabuf){};
struct dma_buf *dma_buf_get(int fd) {
    return NULL;
};

#endif
#define DMC_MEM_TYPE_NN (0x10)
#define DMC_DEV_ID_NN (20)
static int adlak_tee_protect_memory(struct adlak_context *context, phys_addr_t start, size_t size) {
#if CONFIG_ADLAK_TEE_MEM_PROTECT_EN
    ASSERT(size == ADLAK_ALIGN(size, 0x10000));
    if (!context->secure_heap_handle) {
        if (tee_protect_mem_by_type(DMC_MEM_TYPE_NN, start, size, &context->secure_heap_handle)) {
            AML_LOG_ERR("%s: tee protect for adla mem fail!\n", __func__);
        }
    }
#endif
    return ERR(NONE);
}

int adlak_tee_net_register_request(struct adlak_context *         context,
                                   struct adlak_tee_network_desc *psubmit_desc) {
    int                          ret             = 0;
    struct adlak_device *        padlak          = context->padlak;
    struct adlak_tee_model_attr *ptee_model_attr = NULL;
    AML_LOG_INFO("%s", __func__);
    ptee_model_attr = adlak_os_zalloc(sizeof(struct adlak_tee_model_attr), ADLAK_GFP_KERNEL);
    if (!ptee_model_attr) {
        return ERR(ENOMEM);
    }

    ptee_model_attr->context        = context;
    ptee_model_attr->tee_ctx_handle = psubmit_desc->tee_ctx_handle;
    context->ptee_model_attr        = ptee_model_attr;

    psubmit_desc->net_register_idx = context->net_id;

    ret = adlak_os_mutex_lock(&context->context_mutex);
    if (ret) {
        AML_LOG_ERR("mutex lock fail!");
        ret = -1;
        goto err;
    }

    padlak->all_task_num++;
    adlak_os_mutex_unlock(&context->context_mutex);

    return 0;
err:
    return ret;
}

int adlak_tee_net_unregister_request(struct adlak_context *         context,
                                     struct adlak_network_del_desc *submit_del) {
    int                  ret    = 0;
    struct adlak_device *padlak = context->padlak;

    AML_LOG_INFO("%s", __func__);

    if (context->ptee_model_attr) {
        ret = adlak_invoke_del_with_invokeid(padlak, submit_del->net_register_idx, -1);
        if (0 == ret) {
            adlak_os_free(context->ptee_model_attr);
            padlak->all_task_num--;
            context->ptee_model_attr = NULL;
        }
    }
    if (context->secure_heap_handle) {
        tee_unprotect_mem(context->secure_heap_handle);
    }

    return 0;
}

static struct adlak_task *adlak_tee_invoke_add_queue(
    struct adlak_context *context, struct adlak_tee_network_invoke_desc *pinvoke_desc) {
    int                          ret             = 0;
    struct adlak_device *        padlak          = context->padlak;
    struct adlak_tee_model_attr *ptee_model_attr = NULL;
    struct adlak_task *          pinvoke_attr    = NULL;

    AML_LOG_INFO("%s net_id[%d]", __func__, context->net_id);

    ptee_model_attr = context->ptee_model_attr;
    if (!ptee_model_attr) {
        AML_LOG_ERR("not found network!");
        ret = (ERR(ENXIO));
        goto err;
    }
    if (!ptee_model_attr->invoke_attr_rsv) {
        pinvoke_attr = adlak_os_zalloc(sizeof(struct adlak_task), ADLAK_GFP_KERNEL);
        if (!pinvoke_attr) {
            AML_LOG_ERR("adlak_os_zalloc fail!");
            ret = (ERR(ENOMEM));
            goto err;
        }
        ptee_model_attr->invoke_attr_rsv = pinvoke_attr;
    } else {
        pinvoke_attr = ptee_model_attr->invoke_attr_rsv;
    }

    pinvoke_attr->context = context;

    ++ptee_model_attr->invoke_count;
    if (ptee_model_attr->invoke_count < 0) {
        ptee_model_attr->invoke_count = 0;
    }
    pinvoke_attr->invoke_idx          = ptee_model_attr->invoke_count;
    pinvoke_desc->invoke_register_idx = pinvoke_attr->invoke_idx;  // return invoke index
    pinvoke_attr->invoke_start_idx    = 0;
    pinvoke_attr->invoke_end_idx      = 0;
    pinvoke_attr->invoke_section_id   = pinvoke_desc->invoke_section_id;

    INIT_LIST_HEAD(&pinvoke_attr->head);

    pinvoke_attr->state      = ADLAK_SUBMIT_STATE_PENDING;
    pinvoke_attr->error_code = ADLAK_SUCCESS;
    context->state           = CONTEXT_STATE_USED;
    context->invoke_cnt++;
    pinvoke_attr->hw_stat.hw_info = padlak->hw_info;

    return pinvoke_attr;
err:
    return NULL;
}

int adlak_tee_invoke_request(struct adlak_context *                context,
                             struct adlak_tee_network_invoke_desc *pinvoke_desc) {
    int                     ret    = 0;
    struct adlak_device *   padlak = context->padlak;
    struct adlak_task *     ptask;
    struct adlak_workqueue *pwq = NULL;
    AML_LOG_DEBUG("%s", __func__);
#ifdef CONFIG_ADLAK_DEBUG_INNNER
    adlak_dbg_inner_update(context, "invoke_request");
#endif

    adlak_os_mutex_lock(&context->context_mutex);
    ptask = adlak_tee_invoke_add_queue(context, pinvoke_desc);
    adlak_os_mutex_unlock(&context->context_mutex);
    if (ADLAK_IS_ERR_OR_NULL(ptask)) {
        AML_LOG_ERR("adlak task create fail!");
        ret = -1;
        goto err;
    }

    pwq = &padlak->queue;
    adlak_os_mutex_lock(&pwq->wq_mutex);
    list_add_tail(&ptask->head, &pwq->pending_list);
    pwq->pending_num++;

    AML_LOG_INFO("pend++,pwq->pending_num = %d\n", pwq->pending_num);
    adlak_os_mutex_unlock(&pwq->wq_mutex);

#ifdef CONFIG_ADLAK_DEBUG_INNNER
    adlak_dbg_inner_update(context, "invoke_request done");
#endif
    adlak_os_sema_give(pwq->wk_update);
    adlak_os_thread_yield();

    return 0;
err:
    return ret;
}

void adlak_tee_model_destroy(struct adlak_tee_model_attr *ptee_model_attr) {
    struct adlak_device *padlak = ptee_model_attr->context->padlak;
    AML_LOG_DEBUG("%s", __func__);

#ifdef CONFIG_ADLAK_DEBUG_INNNER
    adlak_dbg_inner_update(ptee_model_attr->context, "task destroy");
#endif
    adlak_os_free(ptee_model_attr);
    padlak->all_task_num--;
}

int meson_dmabuf_fd_to_phys(int fd, phys_addr_t *addr, size_t *len) {
    struct dma_buf *         dmabuf;
    struct adla_heap_buffer *buffer;
    struct sg_table *        sg_table;
    struct page *            page;

    dmabuf = dma_buf_get(fd);
    if (IS_ERR_OR_NULL(dmabuf)) return PTR_ERR(dmabuf);

    buffer = (struct adla_heap_buffer *)dmabuf->priv;
    if (buffer) {
        sg_table = &buffer->sg_table;
        page     = sg_page(sg_table->sgl);
        *addr    = PFN_PHYS(page_to_pfn(page));
        *len     = buffer->len;
    }

    dma_buf_put(dmabuf);

    return 0;
}

int adlak_tee_query_addr(struct adlak_context *       context,
                         struct adlak_tee_query_addr *tee_query_addr) {
    int ret = 0;

    AML_LOG_DEBUG("%s", __func__);
    adlak_os_mutex_lock(&context->context_mutex);

    ret = meson_dmabuf_fd_to_phys((int)tee_query_addr->fd, (phys_addr_t *)&tee_query_addr->ret_addr,
                                  (size_t *)&tee_query_addr->ret_size);

    if (ret < 0) {
        AML_LOG_ERR("adlak tee query addr by fd fail!");
        ret = ERR(EINVAL);
        goto err;
    }
    adlak_os_mutex_unlock(&context->context_mutex);
    return ERR(NONE);
err:
    return ret;
}

int adlak_tee_protect_addr(struct adlak_context *         context,
                           struct adlak_tee_protect_addr *tee_protect_addr) {
    int ret = 0;

    AML_LOG_DEBUG("%s", __func__);
    adlak_os_mutex_lock(&context->context_mutex);
    ret = adlak_tee_protect_memory(context, (phys_addr_t)tee_protect_addr->phys_addr,
                                   (size_t)tee_protect_addr->size);

    AML_LOG_INFO("tee protect phys addr %X ~ %X", (size_t)tee_protect_addr->phys_addr,
                 (size_t)tee_protect_addr->phys_addr + (size_t)tee_protect_addr->size);
    adlak_os_mutex_unlock(&context->context_mutex);
    return ret;
}

#ifdef CONFIG_AMLOGIC_ION_DEV
int adlak_tee_dump_addr(uintptr_t phys_addr, size_t size) {
#ifdef CONFIG_ADLAK_TEE_DUMP_DRAM

    uint32_t      start, end;
    uint32_t *    pcmq_buf = NULL;
    void *        vaddr;
    struct page **pages;
    unsigned long pfn;
    size_t        size_align;
    int           num_pages;
    int           i;

    // Calculate the aligned size, rounding up to the nearest multiple of 4096 bytes
    size_align = ADLAK_ALIGN(size, 4096);

    // Calculate the number of pages needed
    num_pages = size_align / 4096;

    // Allocate memory for the array of page pointers
    pages = adlak_os_malloc(sizeof(struct page *) * num_pages, ADLAK_GFP_KERNEL);
    if (!pages) {
        pr_err("Failed to allocate memory for page array\n");
        return -ENOMEM;
    }

    // Get each page from PFN and store it in the pages array
    for (i = 0; i < num_pages; i++) {
        pfn      = PHYS_PFN(phys_addr + i * 4096);
        pages[i] = pfn_to_page(pfn);
        if (!pages[i]) {
            pr_err("Failed to get page from PFN\n");
            adlak_os_free(pages);
            return -ENOMEM;
        }
    }

    // Map the pages to virtual address space
    vaddr = vmap(pages, num_pages, VM_IOREMAP, PAGE_KERNEL);

    if (!vaddr) {
        pr_err("Failed to vmap physical memory\n");
        return -ENOMEM;
    }
    adlak_os_printf("Dump dram: 0x%08X ~ 0x%08X", phys_addr, phys_addr + size - 1);
    pcmq_buf = vaddr;
    end      = size / sizeof(uint32_t);
    start    = 0;

    adlak_os_printf("cmd_offset_start: 0x%08X\t;cmd_offset_end: 0x%08X \n",
                    start * sizeof(uint32_t), end * sizeof(uint32_t));
    if (start < end) {
        while (start < end) {
            adlak_os_printf("offset:0x%08X\t0x%08X 0x%08X 0x%08X 0x%08X \n",
                            (uint32_t)(start * sizeof(uint32_t)), pcmq_buf[start + 0],
                            pcmq_buf[start + 1], pcmq_buf[start + 2], pcmq_buf[start + 3]);
            start += 4;
        }

    } else {
        // don't need support
    }
    adlak_os_printf("\n");

    vunmap(vaddr);
    adlak_os_free(pages);
#endif
    return 0;
}
#else

int             adlak_tee_dump_addr(uintptr_t phys_addr, size_t size) { return 0; }

#endif

static void adlak_tee_irq_status_decode(uint32_t state) {
    if (state & ADLAK_IRQ_MASK_PARSER_STOP_CMD) {
        AML_LOG_WARN(" [0]: parser stop for command");
    }
    if (state & ADLAK_IRQ_MASK_PARSER_STOP_ERR) {
        AML_LOG_WARN(" [1]: parser stop for error");
    }
    if (state & ADLAK_IRQ_MASK_PARSER_STOP_PMT) {
        AML_LOG_WARN(" [2]: parser stop for preempt");
    }
    if (state & ADLAK_IRQ_MASK_PEND_TIMEOUT) {
        AML_LOG_WARN(" [3]: pending timer timeout");
    }
    if (state & ADLAK_IRQ_MASK_LAYER_END) {
        AML_LOG_WARN(" [4]: layer end event");
    }
    if (state & ADLAK_IRQ_MASK_TIM_STAMP) {
        AML_LOG_WARN(" [5]: time_stamp irq event");
    }
    if (state & ADLAK_IRQ_MASK_APB_WAIT_TIMEOUT) {
        AML_LOG_WARN(" [6]: apb wait timer timeout");
    }
    if (state & ADLAK_IRQ_MASK_PM_DRAM_OVF) {
        AML_LOG_WARN(" [7]: pm dram overflow");
    }
    if (state & ADLAK_IRQ_MASK_PM_FIFO_OVF) {
        AML_LOG_WARN(" [8]: pm fifo overflow");
    }
    if (state & ADLAK_IRQ_MASK_PM_ARBITER_OVF) {
        AML_LOG_WARN(" [9]: pm arbiter overflow");
    }
    if (state & ADLAK_IRQ_MASK_INVALID_IOVA) {
        AML_LOG_WARN(" [10]: smmu has an invalid-va");
    }
    if (state & (1 << 11)) {
        AML_LOG_WARN(" [11]: ab has response error");
    }
}

#if 1

#include <linux/delay.h>
#include <linux/hw_random.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/slab.h>
#include <linux/tee_drv.h>
#include <linux/uuid.h>

static int optee_ctx_match(struct tee_ioctl_version_data *ver, const void *data) {
    if (ver->impl_id == TEE_IMPL_ID_OPTEE)
        return 1;
    else
        return 0;
}

#define TA_ADLA_CMD_INVOKE_HW (0x10 + 3)
#ifndef TA_ADLA_UUID
#define TA_ADLA_UUID \
    UUID_INIT(0x5dc33b6a, 0x216d, 0x4641, 0xa8, 0x34, 0xb3, 0xf3, 0xaa, 0x1a, 0xcc, 0xb8)
#endif

uint32_t adla_submit_through_tadla(uint64_t tee_ctx_handle, uint32_t invoke_section_id) {
    uint32_t                          hw_ret = 0;
    int                               ret = 0, err = -ENODEV;
    static const uuid_t               uuid     = TA_ADLA_UUID;
    struct tee_param                  param[4] = {0};
    struct tee_context *              ctx      = NULL;
    struct tee_ioctl_open_session_arg sess_arg;

    /* Open context with TEE driver */
    ctx = tee_client_open_context(NULL, optee_ctx_match, NULL, NULL);
    if (IS_ERR(ctx)) {
        AML_LOG_ERR("%s open context failed\n", __func__);
        hw_ret = 1;
        return hw_ret;
    }

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 15, 0)
    export_uuid(sess_arg.uuid, &uuid);
#else
    memcpy(sess_arg.uuid, &uuid, sizeof(uuid_t));
#endif

    sess_arg.clnt_login = TEE_IOCTL_LOGIN_PUBLIC;
    sess_arg.num_params = 2;
    /* Fill open cmd params */
    param[0].attr      = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT;
    param[0].u.value.a = (uint32_t)TA_ADLA_CMD_INVOKE_HW;  // command type
    param[0].u.value.b = invoke_section_id;
    param[1].attr      = TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INPUT;
    param[1].u.value.a = (uint32_t)(tee_ctx_handle);        // low
    param[1].u.value.b = (uint32_t)(tee_ctx_handle >> 32);  // high

    ret = tee_client_open_session(ctx, &sess_arg, param);
    if ((ret < 0) || (sess_arg.ret != 0)) {
        AML_LOG_ERR("tee_client_open_session failed, err: %x\n", sess_arg.ret);
        err    = -EINVAL;
        hw_ret = 1;
        goto out_ctx;
    }
    AML_LOG_INFO("new tee_session_id %d\n", sess_arg.session);
    if (param[0].u.value.a == 0) {
        hw_ret = param[0].u.value.b;
    } else {
        AML_LOG_ERR("invoke hw failed, err: %llx\n", param[0].u.value.a);
        hw_ret = 0x1234;
    }

    tee_client_close_session(ctx, sess_arg.session);
out_ctx:
    tee_client_close_context(ctx);
    return hw_ret;
}

#else
extern uint32_t adla_submit_through_tadla(uint64_t tee_ctx_handle, uint32_t invoke_section_id);

#endif

int adlak_submit_tee_task(struct adlak_task *ptask, uint64_t smmu_entry) {
    struct adlak_device *        padlak          = ptask->context->padlak;
    struct adlak_tee_model_attr *ptee_model_attr = NULL;
    uint32_t                     irq_raw         = 0;
    uint32_t                     invoke_section_id;
    uint64_t                     tee_ctx_handle;

    ptee_model_attr = ptask->context->ptee_model_attr;
    AML_LOG_INFO("%s", __func__);
#ifdef CONFIG_ADLAK_DEBUG_INNNER
    adlak_dbg_inner_update(ptask->context, "tee_submit_start");
#endif
    {
        ptask->blocking = 1;
#if defined(CONFIG_ADLAK_EMU_EN) && (CONFIG_ADLAK_EMU_EN == 1)
        tee_ctx_handle    = ptee_model_attr->tee_ctx_handle;
        invoke_section_id = ptask->invoke_section_id;
        AML_LOG_INFO("adla_submit_through_tadla tee_ctx_handle 0x%X , invoke_section_id 0x%X\n",
                     tee_ctx_handle, invoke_section_id);
        adlak_os_udelay(100000);
        irq_raw = adla_submit_through_tadla(tee_ctx_handle, invoke_section_id);
        AML_LOG_INFO("IRQ RAW[0x%08X] \n", irq_raw);
        irq_raw = irq_raw & (~ADLAK_IRQ_MASK_LAYER_END);
        if ((~ADLAK_IRQ_MASK_TIM_STAMP) & irq_raw) {
            ptask->state      = ADLAK_SUBMIT_STATE_FAIL;
            ptask->error_code = ADLAK_HARDWARE_TIMEOUT;
            AML_LOG_ERR("IRQ RAW[0x%08X]", irq_raw);
            adlak_tee_irq_status_decode(irq_raw);
        } else {
            ptask->state      = ADLAK_SUBMIT_STATE_FINISHED;
            ptask->error_code = ADLAK_SUCCESS;
        }
#else
        if (ptee_model_attr) {
            invoke_section_id = ptask->invoke_section_id;
            tee_ctx_handle    = ptee_model_attr->tee_ctx_handle;
        } else {
            AML_LOG_ERR("Invalid args!");
            ASSERT(0);
            invoke_section_id = 0;
            tee_ctx_handle    = 0;
        }
        //    will blocking in teeos

        AML_LOG_INFO("adla_submit_through_tadla  tee_ctx_handle 0x%X , invoke_section_id 0x%X\n",
                     tee_ctx_handle, invoke_section_id);

#if CONFIG_ADLAK_TEE_MEM_PROTECT_EN
        // ADLA can only access the protected section of memory.
        // tee_config_device_state(DMC_DEV_ID_NN, 1); // this func will be handle in PTA
#endif
        irq_raw = adla_submit_through_tadla(tee_ctx_handle, invoke_section_id);
        AML_LOG_INFO("IRQ RAW[0x%08X] \n", irq_raw);
        irq_raw = irq_raw & (~ADLAK_IRQ_MASK_LAYER_END);
        if ((~ADLAK_IRQ_MASK_TIM_STAMP) & irq_raw) {
            ptask->state      = ADLAK_SUBMIT_STATE_FAIL;
            ptask->error_code = ADLAK_HARDWARE_TIMEOUT;
            AML_LOG_ERR("IRQ RAW[0x%08X]", irq_raw);
            adlak_tee_irq_status_decode(irq_raw);
        } else {
            ptask->state      = ADLAK_SUBMIT_STATE_FINISHED;
            ptask->error_code = ADLAK_SUCCESS;
        }
#if CONFIG_ADLAK_TEE_MEM_PROTECT_EN
        // ADLA can only access the un-protected section of memory.
        // tee_config_device_state(DMC_DEV_ID_NN, 0);// this func will be handle in PTA
#endif
#endif
    }

#ifdef CONFIG_ADLAK_DEBUG_INNNER
    adlak_dbg_inner_update(ptask->context, "tee_submit_end");
#endif

    ptask->hw_stat.irq_status.timeout = false;
    adlak_hal_reset_and_start(padlak);
    AML_LOG_DEBUG("%s End", __func__);
    return ERR(NONE);
}
