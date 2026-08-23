/*******************************************************************************
 * Copyright (C) 2021 Amlogic, Inc. All rights reserved.
 ******************************************************************************/

/*****************************************************************************/
/**
 *
 * @file adlak_reg.h
 * @brief
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   	Who				Date				Changes
 * ----------------------------------------------------------------------------
 * 1.00a shiwei.sun@amlogic.com	2021/06/18	Initial release
 * </pre>
 *
 ******************************************************************************/

#ifndef __ADLAK_REG_H__
#define __ADLAK_REG_H__

/***************************** Include Files *********************************/
#include "adlak_typedef.h"
#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/

#define REG_ADLAK_REV (0x0) /* read,default=0x0 */

#define REG_ADLAK_WAIT_TIMER (0x4) /* read/write,default=0xff */
#define REG_ADLAK_SECURITY (0x8)   /* read */
// irq
#define REG_ADLAK_IRQ_MASKED (0x10) /* read,default=0x0 */
#define REG_ADLAK_IRQ_MASK (0x14)   /* read/write,default=0x0 */
#define REG_ADLAK_IRQ_RAW (0x18)    /* read/write,default=0x0 */
#define REG_ADLAK_STS_REPORT (0x1C) /* read,default=0x0 */
// power&clock
#define REG_ADLAK_SWRST (0x20)        /* read/write,default=0x0 */
#define REG_ADLAK_ADLAK_EN (0x24)     /* read/write,default=0x0 */
#define REG_ADLAK_CLK_AUTOCLK (0x28)  /* read/write,default=0x0 */
#define REG_ADLAK_CLK_IDLE_CNT (0x2c) /* read/write,default=0x1008 */
// debug
#define REG_ADLAK_DBG_EN (0x30)        /* read/write,default=0x0 */
#define REG_ADLAK_DBG_SEL (0x34)       /* read/write,default=0x0 */
#define REG_ADLAK_DBG_SUB_SEL (0x38)   /* read/write,default=0x0 */
#define REG_ADLAK_DBG_DAT (0x3c)       /* read,default=0x0 */
#define REG_ADLAK_DBG_SRAM_CTRL (0x40) /* read/write,default=0x0 */
#define REG_ADLAK_DBG_SRAM_ADDR (0x44) /* read/write,default=0x0 */
#define REG_ADLAK_DBG_SRAM_WDAT (0x48) /* read/write,default=0x0 */
#define REG_ADLAK_DBG_SRAM_RDAT (0x4c) /* read,default=0x0 */

// parser
#define REG_ADLAK_PS_CTRL (0x50)            /* read/write,default=0x0 */
#define REG_ADLAK_PS_STS (0x54)             /* read,default=0x0 */
#define REG_ADLAK_PS_ERR_DAT (0x58)         /* read,default=0x0 */
#define REG_ADLAK_PS_IDLE_STS (0x5c)        /* read,default=0x0 */
#define REG_ADLAK_PS_TIME_STAMP (0x60)      /* read,default=0x0 */
#define REG_ADLAK_PS_RBF_BASE (0x64)        /* read/write,default=0x0 */
#define REG_ADLAK_PS_RBF_SIZE (0x68)        /* read/write,default=0x0 */
#define REG_ADLAK_PS_RBF_WPT (0x6c)         /* read/write,default=0x0 */
#define REG_ADLAK_PS_RBF_RPT (0x70)         /* read,default=0x0 */
#define REG_ADLAK_PS_RBF_PPT (0x74)         /* read,default=0x0 */
#define REG_ADLAK_PS_FINISH_ID (0x78)       /* read,default=0x0 */
#define REG_ADLAK_PS_HCNT (0x7c)            /* read,default=0x0 */
#define REG_ADLAK_PS_OST (0x80)             /* read/write,default=0x4 */
#define REG_ADLAK_PS_PEND_EN (0x84)         /* read/write,default=0x0 */
#define REG_ADLAK_PS_PEND_VAL (0x88)        /* read/write,default=0x0 */
#define REG_ADLAK_PS_MODULE_IDLE_STS (0x8c) /* read,default=0x0 */
#define REG_ADLAK_PS_DBG_SW_ID (0x90)       /* read,default=0x0 */
#define REG_ADLAK_AB_AXI_PADDR (0x9C)       /* read/write,default=0x0 */
#define REG_ADLAK_AB_CTL (0xa0)             /* read/write,default=0x0 */
#define REG_ADLAK_AB_AXI_SADDR (0xa4)       /* read/write,default=0x0 */
#define REG_ADLAK_AB_AXI_EADDR (0xa8)       /* read/write,default=0x0 */
#define REG_ADLAK_AB_R_CS_PRIO (0xac)       /* read/write,default=0x30011111 */
#define REG_ADLAK_AB_R_LS_PRIO (0xb0)       /* read/write,default=0x11111 */
#define REG_ADLAK_AB_R_L2_PRIO (0xb4)       /* read/write,default=0x211 */
#define REG_ADLAK_AB_W_PRIO (0xb8)          /* read/write,default=0x0 */
#define REG_ADLAK_AB_AXI_USER (0xbc)        /* read/write,default=0x440044 */
// smmu
#define REG_ADLAK_SMMU_EN (0xc0)          /* read/write,default=0x0 */
#define REG_ADLAK_SMMU_TTBR_L (0xc4)      /* read/write,default=0x0 */
#define REG_ADLAK_SMMU_TTBR_H (0xc8)      /* read/write,default=0x0 */
#define REG_ADLAK_SMMU_PRIO_POW2_0 (0xcc) /* read/write,default=0x11111111 */
#define REG_ADLAK_SMMU_PRIO_POW2_1 (0xd0) /* read/write,default=0x111111 */
#define REG_ADLAK_SMMU_INV_CTL (0xd4)     /* read/write,default=0x0 */
#define REG_ADLAK_SMMU_INV_VA (0xd8)      /* read/write,default=0x0 */
#define REG_ADLAK_SMMU_DFT (0xdc)         /* read/write,default=0x0 */
#define REG_ADLAK_SMMU_IVD_MDL (0xe0)     /* read,default=0x0 */
#define REG_ADLAK_SMMU_IVD_VA (0xe4)      /* read,default=0x0 */
// pm
#define REG_ADLAK_PM_EN (0xf0)       /* read/write,default=0x0 */
#define REG_ADLAK_PM_RBF_BASE (0xf4) /* read/write,default=0x0 */
#define REG_ADLAK_PM_RBF_SIZE (0xf8) /* read/write,default=0x0 */
#define REG_ADLAK_PM_RBF_WPT (0xfc)  /* read,default=0x0 */
#define REG_ADLAK_PM_RBF_RPT (0x100) /* read/write,default=0x0 */
#define REG_ADLAK_PM_STS (0x104)     /* read/write,default=0x0 */
#define REG_ADLAK_PM_UNIT (0x108)    /* read/write,default=0x0 */
// AXI DRAM
#define REG_ADLAK_AXIBRG_DX_CTL (0x110)  /* read/write,default=0x0 */
#define REG_ADLAK_AXIBRG_DX_HOLD (0x114) /* read/write,default=0x80808080 */
// AXI SRAM
#define REG_ADLAK_AXIBRG_SX_CTL (0x118)  /* read/write,default=0x0 */
#define REG_ADLAK_AXIBRG_SX_HOLD (0x11c) /* read/write,default=0x80808080 */

#define REG_ADLAK_MC_CTL (0x120)       /* read/write,default=0x0 */
#define REG_ADLAK_MC_CLK_PHASE (0x124) /* read/write,default=0x0 */

#define REG_ADLAK_NUM_MAX (68)
// irq mask
#define ADLAK_IRQ_MASK_PARSER_STOP_CMD (1 << 0) /* [0]: parser stop for command*/
#define ADLAK_IRQ_MASK_PARSER_STOP_ERR (1 << 1) /* [1]: parser stop for error*/
#define ADLAK_IRQ_MASK_PARSER_STOP_PMT (1 << 2) /* [2]: parser stop for preempt*/
#define ADLAK_IRQ_MASK_PEND_TIMEOUT (1 << 3)     /* [3]: pending timer timeout*/
#define ADLAK_IRQ_MASK_LAYER_END (1 << 4)       /* [4]: layer end event*/
#define ADLAK_IRQ_MASK_TIM_STAMP (1 << 5)       /* [5]: time_stamp irq event*/
#define ADLAK_IRQ_MASK_APB_WAIT_TIMEOUT (1 << 6) /* [6]: apb wait timer timeout*/
#define ADLAK_IRQ_MASK_PM_DRAM_OVF (1 << 7)     /* [7]: pm dram overflow*/
#define ADLAK_IRQ_MASK_PM_FIFO_OVF (1 << 8)     /* [8]: pm fifo overflow*/
#define ADLAK_IRQ_MASK_PM_ARBITER_OVF (1 << 9)  /* [9]: pm arbiter overflow*/
#define ADLAK_IRQ_MASK_INVALID_IOVA (1 << 10)   /* [10]: smmu has an invalid-va*/
#define ADLAK_IRQ_MASK_SW_TIMEOUT (1 << 20)     /*user define : software timeout*/

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/

typedef union { /* OFFSET:0x0 ADLAK_REV */
    struct {
        uint32_t minor_rev : 8; /* Hardware minor revision number */
        uint32_t major_rev : 8; /* Hardware major revision number */
        uint32_t : 16;
    } bitc;
    uint32_t all;
} HAL_ADLAK_REV_S;
typedef union { /* OFFSET:0x14 ADLAK_IRQ_MASK */
    struct {
        uint32_t irqsts_mask : 16; /* Interrupt status mask
                                              0:disable IRQ
                                              1:enable IRQ
                                              [0]: parser stop for command
                                              [1]: parser stop for error
                                              [2]: parser stop for preempt
                                              [3]: pending timer timeout
                                              [4]: layer end event
                                              [5]: time_stamp irq event
                                              [6]: apb wait timer timeout
                                              [7]: pm dram overflow
                                              [8]: pm fifo overflow
                                              [9]: smmu has an invalid-va */
        uint32_t : 16;
    } bitc;
    uint32_t all;
} HAL_ADLAK_IRQ_MASK_S;
typedef union { /* OFFSET:0x50 ADLAK_PS_CTRL */
    struct {
        uint32_t ps_rst : 1;      /* parser reset (also reset dependence information) */
        uint32_t ps_dep_rst : 1;  /* reset dependence information */
        uint32_t ps_start : 1;    /* parser start to work */
        uint32_t ps_preempt : 1;  /* parser preempt to stop */
        uint32_t ps_pend_rst : 1; /* reset pending timer */
        uint32_t : 27;
    } bitc;
    uint32_t all;
} HAL_ADLAK_PS_CTRL_S;
typedef union { /* OFFSET:0x54 ADLAK_PS_STS */
    struct {
        uint32_t ps_stop_cmd : 1; /* parser status report: stop command */
        uint32_t ps_stop_err : 1; /* parser status report: stop error */
        uint32_t ps_stop_pmt : 1; /* parser status report: stop preempt */
        uint32_t ps_busy : 1;     /* parser status report:  busy */
        uint32_t ps_pmt_busy : 1; /* parser status report:  preempt_busy */
        uint32_t : 27;
    } bitc;
    uint32_t all;
} HAL_ADLAK_PS_STS_S;

typedef union { /* OFFSET:0x1C ADLAK_REPORT_STATUS */
    struct {
        uint32_t hang_dw_sramf : 1;    /* [0]: dw sramf hang*/
        uint32_t hang_dw_sramw : 1;    /* [1]: dw sramw hang*/
        uint32_t hang_pe_srama : 1;    /* [2]: pe srama hang*/
        uint32_t hang_pe_sramm : 1;    /* [3]: pe sramm hang*/
        uint32_t hang_px_srama : 1;    /* [4]: px srama hang*/
        uint32_t hang_px_sramm : 1;    /* [5]: px sramm hang*/
        uint32_t rsv1 : 1;             /* [6]: reserved*/
        uint32_t hang_vlc_decoder : 1; /* [7]: vlc decoder hang*/
        uint32_t vlc_decoder_rpid : 8; /* [15:8] : vlc decoder rpid*/
        uint32_t hang_ps_dep : 1;      /*[16]: ps dependence hang*/
        uint32_t hang_mc_dep : 1;      /*[17]: mc dependence hang*/
        uint32_t hang_dw_f_dep : 1;    /*[18]: dw_f dependence hang*/
        uint32_t hang_dw_w_dep : 1;    /*[19]: dw_w dependence hang*/
        uint32_t hang_rs_dep : 1;      /*[20]: rs dependence hang*/
        uint32_t : 11;
    } bitc;
    uint32_t all;
} HAL_ADLAK_REPORT_STATUS_S;

typedef union { /* OFFSET:0x20 ADLAK_SWRST */
    struct {
        uint32_t adlak_swrst : 1; /* ADLAK asynchronous reset from software.
                                            Subsequent software resets require ‘1’ followed by ‘0’
                               to be written. */
        uint32_t : 31;
    } bitc;
    uint32_t all;
} HAL_ADLAK_SWRST_S;
typedef union { /* OFFSET:0x24 ADLAK_ADLAK_EN */
    struct {
        uint32_t adlak_en : 1; /* adlak enable */
        uint32_t : 31;
    } bitc;
    uint32_t all;
} HAL_ADLAK_ADLAK_EN_S;
typedef union { /* OFFSET:0x28 ADLAK_CLK_AUTOCLK */
    struct {
        uint32_t adlak_autoclk_en : 32; /* auto gating clock enable */
    } bitc;
    uint32_t all;
} HAL_ADLAK_CLK_AUTOCLK_S;

typedef union { /* OFFSET:0x84 ADLAK_PS_PEND_EN */
    struct {
        uint32_t ps_pend_timer_en : 1; /* pending timer enable */
        uint32_t : 31;
    } bitc;
    uint32_t all;
} HAL_ADLAK_PS_PEND_EN_S;
typedef union { /* OFFSET:0x88 ADLAK_PS_PEND_VAL */
    struct {
        uint32_t ps_pend_timer_val : 32; /* pending timer setting value */
    } bitc;
    uint32_t all;
} HAL_ADLAK_PS_PEND_VAL_S;

typedef union { /* OFFSET:0xa0 ADLAK_AB_CTL */
    struct {
        uint32_t ab_force_stop_en : 1;    /* Enable AB force stop */
        uint32_t ab_force_stop_idle : 1;  /* Bus idle of AB force stop */
        uint32_t ab_axi_addr_wrap_en : 1; /* Enable the address wrap for AXI SRAM */
        uint32_t : 28;
        uint32_t ab_cmp_cache_dis : 1; /* Disable compress header cache */
    } bitc;
    uint32_t all;
} HAL_ADLAK_AB_CTL_S;
typedef union { /* OFFSET:0xa4 ADLAK_AB_AXI_SADDR */
    struct {
        uint32_t
            ab_axi_saddr : 21; /* Start address of AXI SRAM. saddr * 0x1000<= Byte Range. Unit: 4KB
                                */
        uint32_t : 11;
    } bitc;
    uint32_t all;
} HAL_ADLAK_AB_AXI_SADDR_S;
typedef union { /* OFFSET:0xa8 ADLAK_AB_AXI_EADDR */
    struct {
        uint32_t
            ab_axi_eaddr : 21; /* End address of AXI SRAM. Byte range < eaddr* 0x1000. Unit: 4KB */
        uint32_t : 11;
    } bitc;
    uint32_t all;
} HAL_ADLAK_AB_AXI_EADDR_S;

typedef union { /* OFFSET:0xc0 ADLAK_SMMU_EN */
    struct {
        uint32_t smmu_en : 1;    /* smmu enable */
        uint32_t smmu_swrst : 1; /* None */
        uint32_t : 30;
    } bitc;
    uint32_t all;
} HAL_ADLAK_SMMU_EN_S;

typedef union { /* OFFSET:0xd4 ADLAK_SMMU_INV_CTL */
    struct {
        uint32_t smmu_invalid_rdy : 1; /* smmu invalid ready */
        uint32_t : 3;
        uint32_t smmu_invalid_all : 4; /* [0] : tlb_l1
                                          [1] : tlb_l2
                                          [2] : wlk_l1
                                          [3] : wlk_l2 */
        uint32_t smmu_invalid_one : 4; /* [0] : tlb_l1
                                          [1] : tlb_l2
                                          [2] : wlk_l1
                                          [3] : wlk_l2 */
        uint32_t : 20;
    } bitc;
    uint32_t all;
} HAL_ADLAK_SMMU_INV_CTL_S;

typedef union { /* OFFSET:0xf0 ADLAK_PM_EN */
    struct {
        uint32_t pm_en : 2;    /* pm enable
                                                  [0]: turn on half function, printing for simulation
                                                  [1]: turn-on full function, include printing for
                             simulation, axi write */
        uint32_t pm_swrst : 1; /* reset wall clock & stop count */
        uint32_t : 29;
    } bitc;
    uint32_t all;
} HAL_ADLAK_PM_EN_S;

typedef union { /* OFFSET:0xf8 ADLAK_PM_RBF_SIZE */
    struct {
        uint32_t pm_rbf_size : 28; /* memory size, unit: byte, need 256 byte aligned, max 256M */
        uint32_t : 4;
    } bitc;
    uint32_t all;
} HAL_ADLAK_PM_RBF_SIZE_S;

typedef union { /* OFFSET:0xfc ADLAK_PM_RBF_WPT */
    struct {
        uint32_t
            pm_rbf_wpt_ofst : 28; /* write pointer offset, unit: byte, will be 256 byte aligned */
        uint32_t : 4;
    } bitc;
    uint32_t all;
} HAL_ADLAK_PM_RBF_WPT_S;
typedef union { /* OFFSET:0x100 ADLAK_PM_RBF_RPT */
    struct {
        uint32_t pm_rbf_rpt_ofst : 28; /* read pointer offset, unit: byte, need 256 byte aligned */
        uint32_t : 4;
    } bitc;
    uint32_t all;
} HAL_ADLAK_PM_RBF_RPT_S;
typedef union { /* OFFSET:0x104 ADLAK_PM_STS */
    struct {
        uint32_t pm_flush : 1;      /* flush fifo to dram */
        uint32_t pm_fifo_empty : 1; /* fifo status */
        uint32_t : 30;
    } bitc;
    uint32_t all;
} HAL_ADLAK_PM_STS_S;

#ifdef __cplusplus
}
#endif

#endif /* __ADLAK_REG_H__ end define*/
