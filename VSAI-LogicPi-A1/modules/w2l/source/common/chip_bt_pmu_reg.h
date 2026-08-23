/* SPDX-License-Identifier: GPL-2.0 */
/*
* Copyright (C) 202X Original Author (retain original author information)
* Copyright (C) 202X Amlogic, Inc. All rights reserved.
*
* Description:
*/
#ifdef CHIP_BT_PMU_REG
#else
#define CHIP_BT_PMU_REG


#define CHIP_BT_PMU_REG_BASE                      (0xf03000)

#define RG_BT_PMU_A0                              (CHIP_BT_PMU_REG_BASE + 0x0)
// Bit 15  :0      rg_pmu_pwr_xosc_bnd            U     RW        default = 'h6
typedef union RG_BT_PMU_A0_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_pmu_pwr_xosc_bnd : 16;
    unsigned int rsvd_0 : 16;
  } b;
} RG_BT_PMU_A0_FIELD_T;

#define RG_BT_PMU_A1                              (CHIP_BT_PMU_REG_BASE + 0x4)
// Bit 30  :0      rg_pmu_xosc_wait_bnd           U     RW        default = 'ha0
// Bit 31          rg_pmu_xosc_wait_man           U     RW        default = 'h1
typedef union RG_BT_PMU_A1_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_pmu_xosc_wait_bnd : 31;
    unsigned int rg_pmu_xosc_wait_man : 1;
  } b;
} RG_BT_PMU_A1_FIELD_T;

#define RG_BT_PMU_A2                              (CHIP_BT_PMU_REG_BASE + 0x8)
// Bit 15  :0      rg_pmu_xosc_dpll_bnd           U     RW        default = 'h6
typedef union RG_BT_PMU_A2_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_pmu_xosc_dpll_bnd : 16;
    unsigned int rsvd_0 : 16;
  } b;
} RG_BT_PMU_A2_FIELD_T;

#define RG_BT_PMU_A3                              (CHIP_BT_PMU_REG_BASE + 0xc)
// Bit 30  :0      rg_pmu_dpll_wait_bnd           U     RW        default = 'h10
// Bit 31          rg_pmu_dpll_wait_man           U     RW        default = 'h1
typedef union RG_BT_PMU_A3_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_pmu_dpll_wait_bnd : 31;
    unsigned int rg_pmu_dpll_wait_man : 1;
  } b;
} RG_BT_PMU_A3_FIELD_T;

#define RG_BT_PMU_A4                              (CHIP_BT_PMU_REG_BASE + 0x10)
// Bit 15  :0      rg_pmu_dpll_act_bnd            U     RW        default = 'h6
typedef union RG_BT_PMU_A4_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_pmu_dpll_act_bnd : 16;
    unsigned int rsvd_0 : 16;
  } b;
} RG_BT_PMU_A4_FIELD_T;


#define RG_BT_PMU_A6                              (CHIP_BT_PMU_REG_BASE + 0x18)
// Bit 15  :0      rg_pmu_act_sleep_bnd           U     RW        default = 'h10
typedef union RG_BT_PMU_A6_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_pmu_act_sleep_bnd : 16;
    unsigned int rsvd_0 : 16;
  } b;
} RG_BT_PMU_A6_FIELD_T;

#define RG_BT_PMU_A7                              (CHIP_BT_PMU_REG_BASE + 0x1c)
// Bit 30  :0      rg_pmu_sleep_mode_bnd          U     RW        default = 'h10
typedef union RG_BT_PMU_A7_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_pmu_sleep_mode_bnd : 31;
    unsigned int rsvd_0 : 1;
  } b;
} RG_BT_PMU_A7_FIELD_T;

#define RG_BT_PMU_A8                              (CHIP_BT_PMU_REG_BASE + 0x20)
// Bit 15  :0      rg_pmu_sleep_wake_bnd          U     RW        default = 'h6
// Bit 31  :16     rg_pmu_xosc_iso_en_bnd         U     RW        default = 'h5
typedef union RG_BT_PMU_A8_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_pmu_sleep_wake_bnd : 16;
    unsigned int rg_pmu_xosc_iso_en_bnd : 16;
  } b;
} RG_BT_PMU_A8_FIELD_T;

#define RG_BT_PMU_A9                              (CHIP_BT_PMU_REG_BASE + 0x24)
// Bit 30  :0      rg_pmu_wake_wait_bnd           U     RW        default = 'h20
typedef union RG_BT_PMU_A9_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_pmu_wake_wait_bnd : 31;
    unsigned int rsvd_0 : 1;
  } b;
} RG_BT_PMU_A9_FIELD_T;

#define RG_BT_PMU_A10                             (CHIP_BT_PMU_REG_BASE + 0x28)
// Bit 30  :0      rg_pmu_wake_xosc_bnd           U     RW        default = 'h6
typedef union RG_BT_PMU_A10_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_pmu_wake_xosc_bnd : 31;
    unsigned int rsvd_0 : 1;
  } b;
} RG_BT_PMU_A10_FIELD_T;

#define RG_BT_PMU_A11                             (CHIP_BT_PMU_REG_BASE + 0x2c)
// Bit 30  :0      rg_pmu_start_cpu_bnd           U     RW        default = 'h10
typedef union RG_BT_PMU_A11_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_pmu_start_cpu_bnd : 31;
    unsigned int rsvd_0 : 1;
  } b;
} RG_BT_PMU_A11_FIELD_T;

#define RG_BT_PMU_A12                             (CHIP_BT_PMU_REG_BASE + 0x30)
// Bit 0           rg_rtc_mode_val                U     RW        default = 'h0
// Bit 1           rg_rtc_mode_man                U     RW        default = 'h0
// Bit 2           rg_osc_mode_val                U     RW        default = 'h1
// Bit 3           rg_osc_mode_man                U     RW        default = 'h1
// Bit 4           rg_gated_mode_val              U     RW        default = 'h0
// Bit 5           rg_gated_mode_man              U     RW        default = 'h1
// Bit 6           rg_bb_reset_val                U     RW        default = 'h0
// Bit 7           rg_bb_reset_man                U     RW        default = 'h0
// Bit 8           rg_iso_en_m_val                U     RW        default = 'h0
// Bit 9           rg_iso_en_m_man                U     RW        default = 'h0
// Bit 10          rg_wake_int_val                U     RW        default = 'h0
// Bit 11          rg_wake_int_man                U     RW        default = 'h1
// Bit 12          rg_start_cpu_val               U     RW        default = 'h0
// Bit 13          rg_start_cpu_man               U     RW        default = 'h0
// Bit 14          rg_ana_osc_val                 U     RW        default = 'h0
// Bit 15          rg_ana_osc_man                 U     RW        default = 'h0
// Bit 16          rg_ana_dpll_val                U     RW        default = 'h0
// Bit 17          rg_ana_dpll_man                U     RW        default = 'h0
// Bit 18          rg_efuse_read_val              U     RW        default = 'h0
// Bit 19          rg_efuse_read_man              U     RW        default = 'h0
// Bit 20          rg_ana_osc_sleep_val           U     RW        default = 'h0
// Bit 21          rg_ana_osc_sleep_man           U     RW        default = 'h0
// Bit 22          rg_xosc_iso_en_m_val           U     RW        default = 'h0
// Bit 23          rg_xosc_iso_en_m_man           U     RW        default = 'h0
typedef union RG_BT_PMU_A12_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_rtc_mode_val : 1;
    unsigned int rg_rtc_mode_man : 1;
    unsigned int rg_osc_mode_val : 1;
    unsigned int rg_osc_mode_man : 1;
    unsigned int rg_gated_mode_val : 1;
    unsigned int rg_gated_mode_man : 1;
    unsigned int rg_bb_reset_val : 1;
    unsigned int rg_bb_reset_man : 1;
    unsigned int rg_iso_en_m_val : 1;
    unsigned int rg_iso_en_m_man : 1;
    unsigned int rg_wake_int_val : 1;
    unsigned int rg_wake_int_man : 1;
    unsigned int rg_start_cpu_val : 1;
    unsigned int rg_start_cpu_man : 1;
    unsigned int rg_ana_osc_val : 1;
    unsigned int rg_ana_osc_man : 1;
    unsigned int rg_ana_dpll_val : 1;
    unsigned int rg_ana_dpll_man : 1;
    unsigned int rg_efuse_read_val : 1;
    unsigned int rg_efuse_read_man : 1;
    unsigned int rg_ana_osc_sleep_val : 1;
    unsigned int rg_ana_osc_sleep_man : 1;
    unsigned int rg_xosc_iso_en_m_val : 1;
    unsigned int rg_xosc_iso_en_m_man : 1;
    unsigned int rsvd_0 : 8;

  } b;
} RG_BT_PMU_A12_FIELD_T;

#define RG_BT_PMU_A13                             (CHIP_BT_PMU_REG_BASE + 0x34)
// Bit 15  :0      rg_pmu_power_en_th             U     RW        default = 'h6
// Bit 30          rg_pmu_power_en_val            U     RW        default = 'h1
// Bit 31          rg_pmu_power_en_man            U     RW        default = 'h0
typedef union RG_BT_PMU_A13_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_pmu_power_en_th : 16;
    unsigned int rsvd_0 : 14;
    unsigned int rg_pmu_power_en_val : 1;
    unsigned int rg_pmu_power_en_man : 1;
  } b;
} RG_BT_PMU_A13_FIELD_T;

#define RG_BT_PMU_A14                             (CHIP_BT_PMU_REG_BASE + 0x38)
// Bit 0           rg_pmu_work_flg                U     RW        default = 'h1
// Bit 1           rg_pmu_ana_xosc_msk            U     RW        default = 'h1
// Bit 2           rg_pmu_ana_dpll_msk            U     RW        default = 'h1
// Bit 3           rg_pmu_power_en_msk            U     RW        default = 'h1
// Bit 4           rg_pmu_aon_iso_en_msk          U     RW        default = 'h1
// Bit 5           rg_pmu_ana_xosc_sleep_msk      U     RW        default = 'h1
// Bit 6           rg_pmu_aldo_en_msk             U     RW        default = 'h1
// Bit 7           rg_pmu_aon_xosc_iso_en_msk     U     RW        default = 'h1
// Bit 9   :8      rg_xosc_sleep_mode             U     RW        default = 'h2
typedef union RG_BT_PMU_A14_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_pmu_work_flg : 1;
    unsigned int rg_pmu_ana_xosc_msk : 1;
    unsigned int rg_pmu_ana_dpll_msk : 1;
    unsigned int rg_pmu_power_en_msk : 1;
    unsigned int rg_pmu_aon_iso_en_msk : 1;
    unsigned int rg_pmu_ana_xosc_sleep_msk : 1;
    unsigned int rg_pmu_aldo_en_msk : 1;
    unsigned int rg_pmu_aon_xosc_iso_en_msk : 1;
    unsigned int rg_xosc_sleep_mode : 2;
    unsigned int rsvd_0 : 22;
  } b;
} RG_BT_PMU_A14_FIELD_T;

#define RG_BT_PMU_A15                             (CHIP_BT_PMU_REG_BASE + 0x3c)
// Bit 3   :0      ro_pmu_cur_obs                 U     RO        default = 'h0
// Bit 4           ro_pmu_ext_en                  U     RO        default = 'h0
typedef union RG_BT_PMU_A15_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_pmu_cur_obs : 4;
    unsigned int ro_pmu_ext_en : 1;
    unsigned int rsvd_0 : 27;
  } b;
} RG_BT_PMU_A15_FIELD_T;

#define RG_BT_PMU_A16                             (CHIP_BT_PMU_REG_BASE + 0x40)
// Bit 31  :0      rg_pmu_power_cfg               U     RW        default = 'h0
typedef union RG_BT_PMU_A16_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_pmu_power_cfg : 32;
  } b;
} RG_BT_PMU_A16_FIELD_T;

#define RG_BT_PMU_A17                             (CHIP_BT_PMU_REG_BASE + 0x44)
// Bit 7   :0      rg_pwr_off_sw                  U     RW        default = 'h0
// Bit 15  :8      rg_pwr_off_hw                  U     RW        default = 'hff
typedef union RG_BT_PMU_A17_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_pwr_off_sw : 8;
    unsigned int rg_pwr_off_hw : 8;
    unsigned int rsvd_0 : 16;
  } b;
} RG_BT_PMU_A17_FIELD_T;

#define RG_BT_PMU_A18                             (CHIP_BT_PMU_REG_BASE + 0x48)
// Bit 7   :0      rg_iso_en_sw                   U     RW        default = 'h0
// Bit 15  :8      rg_iso_en_hw                   U     RW        default = 'hff
// Bit 16          rg_xosc_iso_en_sw              U     RW        default = 'h0
// Bit 20          rg_xosc_iso_en_hw              U     RW        default = 'h1
typedef union RG_BT_PMU_A18_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_iso_en_sw : 8;
    unsigned int rg_iso_en_hw : 8;
    unsigned int rg_xosc_iso_en_sw : 1;
    unsigned int rsvd_0 : 3;
    unsigned int rg_xosc_iso_en_hw : 1;
    unsigned int rsvd_1 : 11;
  } b;
} RG_BT_PMU_A18_FIELD_T;

#define RG_BT_PMU_A19                             (CHIP_BT_PMU_REG_BASE + 0x4c)
// Bit 7   :0      ro_pwrup_ack                   U     RO        default = 'h0
typedef union RG_BT_PMU_A19_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_pwrup_ack : 8;
    unsigned int rsvd_0 : 24;
  } b;
} RG_BT_PMU_A19_FIELD_T;

#define RG_BT_PMU_A22                             (CHIP_BT_PMU_REG_BASE + 0x58)
// Bit 15  :0      rg_dev_reset_sw                U     RW        default = 'h4
// Bit 31  :16     rg_dev_reset_hw                U     RW        default = 'hffff
typedef union RG_BT_PMU_A22_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_dev_reset_sw : 16;
    unsigned int rg_dev_reset_hw : 16;
  } b;
} RG_BT_PMU_A22_FIELD_T;

#define RG_BT_PMU_A23                             (CHIP_BT_PMU_REG_BASE + 0x5c)
// Bit 5   :0      ro_pmu_sdio_cfg                U     RO        default = 'h0
typedef union RG_BT_PMU_A23_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_pmu_sdio_cfg : 6;
    unsigned int rsvd_0 : 26;
  } b;
} RG_BT_PMU_A23_FIELD_T;

#define RG_BT_PMU_A26                             (CHIP_BT_PMU_REG_BASE + 0x68)
// Bit 7   :0      rg_mem_pd_en_th                U     RW        default = 'h6
typedef union RG_BT_PMU_A26_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_mem_pd_en_th : 8;
    unsigned int rsvd_0 : 24;
  } b;
} RG_BT_PMU_A26_FIELD_T;

#define RG_BT_PMU_A28                             (CHIP_BT_PMU_REG_BASE + 0x70)
// Bit 1           rg_if_reset_man                U     RW        default = 'h0
// Bit 2           rg_efuse_reset_val             U     RW        default = 'h0
// Bit 3           rg_efuse_reset_man             U     RW        default = 'h0
// Bit 4           rg_coexist_reset_val           U     RW        default = 'h0
// Bit 5           rg_coexist_reset_man           U     RW        default = 'h0
// Bit 8           rg_pmu_efuse_reset_n_msk       U     RW        default = 'h0
// Bit 9           rg_pmu_coexist_reset_n_msk     U     RW        default = 'h0
// Bit 11  :10     rg_hif_mode_val                U     RW        default = 'h0
// Bit 12          rg_hif_mode_man                U     RW        default = 'h0
// Bit 13          rg_pmu_rtc_mode_en_msk         U     RW        default = 'h0
// Bit 18  :16     rg_if_reset_val                U     RW        default = 'h0
typedef union RG_BT_PMU_A28_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rsvd_0 : 1;
    unsigned int rg_if_reset_man : 1;
    unsigned int rg_efuse_reset_val : 1;
    unsigned int rg_efuse_reset_man : 1;
    unsigned int rg_coexist_reset_val : 1;
    unsigned int rg_coexist_reset_man : 1;
    unsigned int rsvd_1 : 2;
    unsigned int rg_pmu_efuse_reset_n_msk : 1;
    unsigned int rg_pmu_coexist_reset_n_msk : 1;
    unsigned int rg_hif_mode_val : 2;
    unsigned int rg_hif_mode_man : 1;
    unsigned int rg_pmu_rtc_mode_en_msk : 1;
    unsigned int rsvd_2 : 2;
    unsigned int rg_if_reset_val : 3;
    unsigned int rsvd_3 : 13;
  } b;
} RG_BT_PMU_A28_FIELD_T;

#define RG_BT_PMU_A29                             (CHIP_BT_PMU_REG_BASE + 0x74)
// Bit 30  :0      ro_pmu_cnt                     U     RO        default = 'h0
typedef union RG_BT_PMU_A29_FIELD
{
    unsigned int data;
    struct
    {
        unsigned int ro_pmu_cnt : 31;
        unsigned int rsvd_0 : 1;
    } b;
} RG_BT_PMU_A29_FIELD_T;

#define RG_BT_PMU_A30                             (CHIP_BT_PMU_REG_BASE + 0x78)
// Bit 3   :0      ro_pmu_curr_st                 U     RO        default = 'h0
// Bit 13  :8      ro_pmu_wake_mode               U     RO        default = 'h0
typedef union RG_BT_PMU_A30_FIELD
{
    unsigned int data;
    struct
    {
        unsigned int ro_pmu_curr_st : 4;
        unsigned int rsvd_0 : 4;
        unsigned int ro_pmu_wake_mode : 6;
        unsigned int rsvd_1 : 18;
    } b;
} RG_BT_PMU_A30_FIELD_T;

#define RG_BT_PMU_A35                             (CHIP_BT_PMU_REG_BASE + 0x8c)
// Bit 31  :0      rg_ao_ram_pd_shutdown_sw       U     RW        default = 'h0
typedef union RG_BT_PMU_A35_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_ao_ram_pd_shutdown_sw : 32;
  } b;
} RG_BT_PMU_A35_FIELD_T;

#define RG_BT_PMU_A36                             (CHIP_BT_PMU_REG_BASE + 0x90)
// Bit 31  :0      rg_ao_ram_pd_disb_gate_sw      U     RW        default = 'h0
typedef union RG_BT_PMU_A36_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_ao_ram_pd_disb_gate_sw : 32;
  } b;
} RG_BT_PMU_A36_FIELD_T;

#define RG_BT_PMU_A37                             (CHIP_BT_PMU_REG_BASE + 0x94)
// Bit 31  :0      rg_ao_ram_pd_sel0_sw           U     RW        default = 'h0
typedef union RG_BT_PMU_A37_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_ao_ram_pd_sel0_sw : 32;
  } b;
} RG_BT_PMU_A37_FIELD_T;

#define RG_BT_PMU_A38                             (CHIP_BT_PMU_REG_BASE + 0x98)
// Bit 31  :0      rg_ao_ram_pd_sel1_sw           U     RW        default = 'h0
typedef union RG_BT_PMU_A38_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_ao_ram_pd_sel1_sw : 32;
  } b;
} RG_BT_PMU_A38_FIELD_T;

#define RG_BT_PMU_A39                             (CHIP_BT_PMU_REG_BASE + 0x9c)
// Bit 31  :0      rg_ao_ram_pd_shutdown_hw       U     RW        default = 'hffffffff
typedef union RG_BT_PMU_A39_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_ao_ram_pd_shutdown_hw : 32;
  } b;
} RG_BT_PMU_A39_FIELD_T;

#define RG_BT_PMU_A40                             (CHIP_BT_PMU_REG_BASE + 0xa0)
// Bit 31  :0      rg_ao_ram_pd_disb_gate_hw      U     RW        default = 'hffffffff
typedef union RG_BT_PMU_A40_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_ao_ram_pd_disb_gate_hw : 32;
  } b;
} RG_BT_PMU_A40_FIELD_T;

#define RG_BT_PMU_A41                             (CHIP_BT_PMU_REG_BASE + 0xa4)
// Bit 31  :0      rg_ao_ram_pd_sel0_hw           U     RW        default = 'h0
typedef union RG_BT_PMU_A41_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_ao_ram_pd_sel0_hw : 32;
  } b;
} RG_BT_PMU_A41_FIELD_T;

#define RG_BT_PMU_A42                             (CHIP_BT_PMU_REG_BASE + 0xa8)
// Bit 31  :0      rg_ao_ram_pd_sel1_hw           U     RW        default = 'hffff0000
typedef union RG_BT_PMU_A42_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_ao_ram_pd_sel1_hw : 32;
  } b;
} RG_BT_PMU_A42_FIELD_T;

#define RG_BT_PMU_A43                             (CHIP_BT_PMU_REG_BASE + 0xac)
// Bit 15  :0      rg_pmu_aldo_en_th              U     RW        default = 'h6
// Bit 30          rg_pmu_aldo_en_val             U     RW        default = 'h1
// Bit 31          rg_pmu_aldo_en_man             U     RW        default = 'h0
typedef union RG_BT_PMU_A43_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_pmu_aldo_en_th : 16;
    unsigned int rsvd_0 : 14;
    unsigned int rg_pmu_aldo_en_val : 1;
    unsigned int rg_pmu_aldo_en_man : 1;
  } b;
} RG_BT_PMU_A43_FIELD_T;

#endif

