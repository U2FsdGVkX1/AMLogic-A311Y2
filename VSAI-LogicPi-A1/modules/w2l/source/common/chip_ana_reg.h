/* SPDX-License-Identifier: GPL-2.0 */
/*
* Copyright (C) 202X Original Author (retain original author information)
* Copyright (C) 202X Amlogic, Inc. All rights reserved.
*
* Description:
*/
#ifdef CHIP_ANA_REG
#else
#define CHIP_ANA_REG


#define CHIP_ANA_REG_BASE                         (0xf05000)

#define RG_DPLL_A0                                (CHIP_ANA_REG_BASE + 0x0)
// Bit 8   :0      rg_bbpll_div_n                 U     RW        default = 'h60
// Bit 31  :16     rg_bbpll_reve                  U     RW        default = 'h0
typedef union RG_DPLL_A0_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_bbpll_div_n : 9;
    unsigned int rsvd_0 : 7;
    unsigned int rg_bbpll_reve : 16;
  } b;
} RG_DPLL_A0_FIELD_T;

#define RG_DPLL_A1                                (CHIP_ANA_REG_BASE + 0x4)
// Bit 0           rg_bbpll_en                    U     RW        default = 'h0
// Bit 1           rg_bbpll_rst                   U     RW        default = 'h1
// Bit 8           rg_bbpll_fr_en                 U     RW        default = 'h0
// Bit 10  :9      rg_bbpll_fr_adj                U     RW        default = 'h2
// Bit 11          rg_bbpll_cp_en                 U     RW        default = 'h1
typedef union RG_DPLL_A1_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_bbpll_en : 1;
    unsigned int rg_bbpll_rst : 1;
    unsigned int rsvd_0 : 6;
    unsigned int rg_bbpll_fr_en : 1;
    unsigned int rg_bbpll_fr_adj : 2;
    unsigned int rg_bbpll_cp_en : 1;
    unsigned int rsvd_1 : 20;
  } b;
} RG_DPLL_A1_FIELD_T;

#define RG_DPLL_A2                                (CHIP_ANA_REG_BASE + 0x8)
// Bit 5   :0      rg_bbpll_ibn_adj               U     RW        default = 'h10
// Bit 13  :8      rg_bbpll_ibp_adj               U     RW        default = 'h10
// Bit 19  :16     rg_bbpll_r2_cnt                U     RW        default = 'h2
// Bit 24          rg_bbpll_vref_adj              U     RW        default = 'h0
// Bit 26  :25     rg_bbpll_dt_sel                U     RW        default = 'h0
typedef union RG_DPLL_A2_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_bbpll_ibn_adj : 6;
    unsigned int rsvd_0 : 2;
    unsigned int rg_bbpll_ibp_adj : 6;
    unsigned int rsvd_1 : 2;
    unsigned int rg_bbpll_r2_cnt : 4;
    unsigned int rsvd_2 : 4;
    unsigned int rg_bbpll_vref_adj : 1;
    unsigned int rg_bbpll_dt_sel : 2;
    unsigned int rsvd_3 : 5;
  } b;
} RG_DPLL_A2_FIELD_T;

#define RG_DPLL_A3                                (CHIP_ANA_REG_BASE + 0xc)
// Bit 1   :0      rg_bbpll_lk_w_sel              U     RW        default = 'h0
// Bit 2           rg_bbpll_lk_clk_gate           U     RW        default = 'h0
// Bit 3           rg_bbpll_lk_lock_long          U     RW        default = 'h0
// Bit 4           rg_bbpll_lk_lock_f             U     RW        default = 'h0
// Bit 5           rg_bbpll_lk_rst                U     RW        default = 'h1
// Bit 26  :8      rg_bbpll_sdm_fra               U     RW        default = 'h0
typedef union RG_DPLL_A3_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_bbpll_lk_w_sel : 2;
    unsigned int rg_bbpll_lk_clk_gate : 1;
    unsigned int rg_bbpll_lk_lock_long : 1;
    unsigned int rg_bbpll_lk_lock_f : 1;
    unsigned int rg_bbpll_lk_rst : 1;
    unsigned int rsvd_0 : 2;
    unsigned int rg_bbpll_sdm_fra : 19;
    unsigned int rsvd_1 : 5;
  } b;
} RG_DPLL_A3_FIELD_T;

#define RG_DPLL_A4                                (CHIP_ANA_REG_BASE + 0x10)
// Bit 0           rg_bbpll_wadc_clk_en           U     RW        default = 'h1
// Bit 1           rg_bbpll_wdac_clk_en           U     RW        default = 'h1
// Bit 2           rg_bbpll_wdac_clk_sel          U     RW        default = 'h0
// Bit 3           rg_bbpll_btadc_clk_en          U     RW        default = 'h1
// Bit 4           rg_bbpll_test_en               U     RW        default = 'h0
typedef union RG_DPLL_A4_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_bbpll_wadc_clk_en : 1;
    unsigned int rg_bbpll_wdac_clk_en : 1;
    unsigned int rg_bbpll_wdac_clk_sel : 1;
    unsigned int rg_bbpll_btadc_clk_en : 1;
    unsigned int rg_bbpll_test_en : 1;
    unsigned int rsvd_0 : 27;
  } b;
} RG_DPLL_A4_FIELD_T;

#define RG_DPLL_A5                                (CHIP_ANA_REG_BASE + 0x14)
// Bit 0           rg_bbpll_ssc_en                U     RW        default = 'h0
// Bit 3   :1      rg_bbpll_ssc_fref              U     RW        default = 'h0
// Bit 5   :4      rg_bbpll_ssc_os                U     RW        default = 'h0
// Bit 6           rg_bbpll_ssc_load_en           U     RW        default = 'h1
// Bit 7           rg_bbpll_ssc_load              U     RW        default = 'h1
// Bit 8           rg_bbpll_ssc_shift_en          U     RW        default = 'h0
// Bit 12  :9      rg_bbpll_ssc_str_m             U     RW        default = 'h0
// Bit 14  :13     rg_bbpll_ssc_mode              U     RW        default = 'h0
// Bit 16  :15     rg_bbpll_ssc_shift_v           U     RW        default = 'h0
// Bit 20  :17     rg_bbpll_ssc_dep               U     RW        default = 'h0
// Bit 21          rg_bbpll_sdm_en                U     RW        default = 'h0
typedef union RG_DPLL_A5_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_bbpll_ssc_en : 1;
    unsigned int rg_bbpll_ssc_fref : 3;
    unsigned int rg_bbpll_ssc_os : 2;
    unsigned int rg_bbpll_ssc_load_en : 1;
    unsigned int rg_bbpll_ssc_load : 1;
    unsigned int rg_bbpll_ssc_shift_en : 1;
    unsigned int rg_bbpll_ssc_str_m : 4;
    unsigned int rg_bbpll_ssc_mode : 2;
    unsigned int rg_bbpll_ssc_shift_v : 2;
    unsigned int rg_bbpll_ssc_dep : 4;
    unsigned int rg_bbpll_sdm_en : 1;
    unsigned int rsvd_0 : 10;
  } b;
} RG_DPLL_A5_FIELD_T;

#define RG_DPLL_A6                                (CHIP_ANA_REG_BASE + 0x1c)
// Bit 28          ro_bbpll_fb_clk_done           U     RO        default = 'h0
// Bit 29          ro_bbpll_ref_clk_done          U     RO        default = 'h0
// Bit 30          ro_bbpll_vco_clk_done          U     RO        default = 'h0
// Bit 31          ro_bbpll_done                  U     RO        default = 'h0
typedef union RG_DPLL_A6_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rsvd_0 : 28;
    unsigned int ro_bbpll_fb_clk_done : 1;
    unsigned int ro_bbpll_ref_clk_done : 1;
    unsigned int ro_bbpll_vco_clk_done : 1;
    unsigned int ro_bbpll_done : 1;
  } b;
} RG_DPLL_A6_FIELD_T;

#define RG_EFUSE_A7                               (CHIP_ANA_REG_BASE + 0x20)
// Bit 31  :0      ro_efuse_rd0                   U     RO        default = 'h0
typedef union RG_EFUSE_A7_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_efuse_rd0 : 32;
  } b;
} RG_EFUSE_A7_FIELD_T;

#define RG_EFUSE_A8                               (CHIP_ANA_REG_BASE + 0x24)
// Bit 31  :0      ro_efuse_rd1                   U     RO        default = 'h0
typedef union RG_EFUSE_A8_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_efuse_rd1 : 32;
  } b;
} RG_EFUSE_A8_FIELD_T;

#define RG_EFUSE_A9                               (CHIP_ANA_REG_BASE + 0x28)
// Bit 31  :0      ro_efuse_rd2                   U     RO        default = 'h0
typedef union RG_EFUSE_A9_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_efuse_rd2 : 32;
  } b;
} RG_EFUSE_A9_FIELD_T;

#define RG_EFUSE_A10                              (CHIP_ANA_REG_BASE + 0x2c)
// Bit 31  :0      ro_efuse_rd3                   U     RO        default = 'h0
typedef union RG_EFUSE_A10_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_efuse_rd3 : 32;
  } b;
} RG_EFUSE_A10_FIELD_T;

#define RG_EFUSE_A11                              (CHIP_ANA_REG_BASE + 0x30)
// Bit 31  :0      ro_efuse_rd4                   U     RO        default = 'h0
typedef union RG_EFUSE_A11_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_efuse_rd4 : 32;
  } b;
} RG_EFUSE_A11_FIELD_T;

#define RG_EFUSE_A12                              (CHIP_ANA_REG_BASE + 0x34)
// Bit 31  :0      ro_efuse_rd5                   U     RO        default = 'h0
typedef union RG_EFUSE_A12_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_efuse_rd5 : 32;
  } b;
} RG_EFUSE_A12_FIELD_T;

#define RG_EFUSE_A13                              (CHIP_ANA_REG_BASE + 0x38)
// Bit 31  :0      ro_efuse_rd6                   U     RO        default = 'h0
typedef union RG_EFUSE_A13_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_efuse_rd6 : 32;
  } b;
} RG_EFUSE_A13_FIELD_T;

#define RG_EFUSE_A14                              (CHIP_ANA_REG_BASE + 0x3c)
// Bit 31  :0      ro_efuse_rd7                   U     RO        default = 'h0
typedef union RG_EFUSE_A14_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_efuse_rd7 : 32;
  } b;
} RG_EFUSE_A14_FIELD_T;

#endif

