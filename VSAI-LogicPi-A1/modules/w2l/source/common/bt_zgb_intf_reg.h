/* SPDX-License-Identifier: GPL-2.0 */
/*
* Copyright (C) 202X Original Author (retain original author information)
* Copyright (C) 202X Amlogic, Inc. All rights reserved.
*
* Description:
*/
#ifdef BT_ZGB_INTF_REG
#else
#define BT_ZGB_INTF_REG


#define BT_ZGB_INTF_REG_BASE                      (0xad0000)

#define DF_INTF_REG_A18                           (BT_ZGB_INTF_REG_BASE + 0x48)
// Bit 15  :0      cntl_gate_tcnt                 U     RW        default = 'h3e7
// Bit 16          cntl_enable                    U     RW        default = 'h0
// Bit 17          cntl_cont_en                   U     RW        default = 'h0
// Bit 18          one_shot_enable                U     RW        default = 'h0
// Bit 19          clk_to_msr_en                  U     RW        default = 'h0
// Bit 26  :20     clk_to_msr_sel                 U     RW        default = 'h0
// Bit 28          limit_error                    U     RO        default = 'h0
// Bit 30  :29     process_count                  U     RO        default = 'h0
// Bit 31          busy                           U     RO        default = 'h0
typedef union DF_INTF_REG_A18_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int cntl_gate_tcnt : 16;
    unsigned int cntl_enable : 1;
    unsigned int cntl_cont_en : 1;
    unsigned int one_shot_enable : 1;
    unsigned int clk_to_msr_en : 1;
    unsigned int clk_to_msr_sel : 7;
    unsigned int rsvd_0 : 1;
    unsigned int limit_error : 1;
    unsigned int process_count : 2;
    unsigned int busy : 1;
  } b;
} DF_INTF_REG_A18_FIELD_T;

#define DF_INTF_REG_A19                           (BT_ZGB_INTF_REG_BASE + 0x4c)
// Bit 7   :0      clk_to_msr_div                 U     RW        default = 'h0
// Bit 27  :20     cntl_dcycle_tcnt               U     RW        default = 'h9
// Bit 28          clk_to_msr_hs_en               U     RW        default = 'h0
// Bit 29          cntl_dcycle_enable             U     RW        default = 'h0
// Bit 31          dcycle_msr_done                U     RO        default = 'h0
typedef union DF_INTF_REG_A19_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int clk_to_msr_div : 8;
    unsigned int rsvd_0 : 12;
    unsigned int cntl_dcycle_tcnt : 8;
    unsigned int clk_to_msr_hs_en : 1;
    unsigned int cntl_dcycle_enable : 1;
    unsigned int rsvd_1 : 1;
    unsigned int dcycle_msr_done : 1;
  } b;
} DF_INTF_REG_A19_FIELD_T;

#define DF_INTF_REG_A20                           (BT_ZGB_INTF_REG_BASE + 0x50)
// Bit 19  :0      ext_cnt_val                    U     RO        default = 'h0
typedef union DF_INTF_REG_A20_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ext_cnt_val : 20;
    unsigned int rsvd_0 : 12;
  } b;
} DF_INTF_REG_A20_FIELD_T;

#define DF_INTF_REG_A21                           (BT_ZGB_INTF_REG_BASE + 0x54)
// Bit 19  :0      min_exp                        U     RW        default = 'h0
typedef union DF_INTF_REG_A21_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int min_exp : 20;
    unsigned int rsvd_0 : 12;
  } b;
} DF_INTF_REG_A21_FIELD_T;

#define DF_INTF_REG_A22                           (BT_ZGB_INTF_REG_BASE + 0x58)
// Bit 19  :0      max_exp                        U     RW        default = 'h0
typedef union DF_INTF_REG_A22_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int max_exp : 20;
    unsigned int rsvd_0 : 12;
  } b;
} DF_INTF_REG_A22_FIELD_T;

#define DF_INTF_REG_A23                           (BT_ZGB_INTF_REG_BASE + 0x5c)
// Bit 0           start_p                        U     RW        default = 'h0
typedef union DF_INTF_REG_A23_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int start_p : 1;
    unsigned int rsvd_0 : 31;
  } b;
} DF_INTF_REG_A23_FIELD_T;

#define DF_INTF_REG_A24                           (BT_ZGB_INTF_REG_BASE + 0x60)
// Bit 31  :0      clk_duty                       U     RO        default = 'h0
typedef union DF_INTF_REG_A24_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int clk_duty : 32;
  } b;
} DF_INTF_REG_A24_FIELD_T;

#define DF_INTF_REG_A25                           (BT_ZGB_INTF_REG_BASE + 0x64)
// Bit 31  :0      rg_ram_pd_shutdown_sw          U     RW        default = 'h0
typedef union DF_INTF_REG_A25_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_ram_pd_shutdown_sw : 32;
  } b;
} DF_INTF_REG_A25_FIELD_T;

#define DF_INTF_REG_A26                           (BT_ZGB_INTF_REG_BASE + 0x68)
// Bit 31  :0      rg_ram_pd_disb_gate_sw         U     RW        default = 'h0
typedef union DF_INTF_REG_A26_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_ram_pd_disb_gate_sw : 32;
  } b;
} DF_INTF_REG_A26_FIELD_T;

#define DF_INTF_REG_A27                           (BT_ZGB_INTF_REG_BASE + 0x6c)
// Bit 31  :0      rg_ram_pd_shutdown_hw          U     RW        default = 'hffffffff
typedef union DF_INTF_REG_A27_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_ram_pd_shutdown_hw : 32;
  } b;
} DF_INTF_REG_A27_FIELD_T;

#define DF_INTF_REG_A28                           (BT_ZGB_INTF_REG_BASE + 0x70)
// Bit 31  :0      rg_ram_pd_disb_gate_hw         U     RW        default = 'hffffffff
typedef union DF_INTF_REG_A28_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_ram_pd_disb_gate_hw : 32;
  } b;
} DF_INTF_REG_A28_FIELD_T;

#define DF_INTF_REG_A49                           (BT_ZGB_INTF_REG_BASE + 0xc4)
// Bit 11  :4      bt_dig_timebase                U     RW        default = 'h28
// Bit 12          cntl_tst_clk_oen               U     RW        default = 'h0
// Bit 26  :16     cntl_tst_clk                   U     RW        default = 'h7c3
typedef union DF_INTF_REG_A49_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rsvd_0 : 4;
    unsigned int bt_dig_timebase : 8;
    unsigned int cntl_tst_clk_oen : 1;
    unsigned int rsvd_1 : 3;
    unsigned int cntl_tst_clk : 11;
    unsigned int rsvd_2 : 5;
  } b;
} DF_INTF_REG_A49_FIELD_T;

#define DF_INTF_REG_A57                           (BT_ZGB_INTF_REG_BASE + 0xe4)
// Bit 7   :0      ahbbus_pause_sel               U     RW        default = 'h7f
typedef union DF_INTF_REG_A57_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ahbbus_pause_sel : 8;
    unsigned int rsvd_0 : 24;
  } b;
} DF_INTF_REG_A57_FIELD_T;

#define DF_INTF_REG_A58                           (BT_ZGB_INTF_REG_BASE + 0xe8)
// Bit 31  :0      reg_prod_adc_dac               U     RW        default = 'ha0a0a0a0
typedef union DF_INTF_REG_A58_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int reg_prod_adc_dac : 32;
  } b;
} DF_INTF_REG_A58_FIELD_T;

#define DF_INTF_REG_A59                           (BT_ZGB_INTF_REG_BASE + 0xec)
// Bit 31  :0      watchdog_cntl                  U     RW        default = 'h0
typedef union DF_INTF_REG_A59_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int watchdog_cntl : 32;
  } b;
} DF_INTF_REG_A59_FIELD_T;

#define DF_INTF_REG_A60                           (BT_ZGB_INTF_REG_BASE + 0xf0)
// Bit 31  :0      watchdog_count                 U     RO        default = 'h0
typedef union DF_INTF_REG_A60_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int watchdog_count : 32;
  } b;
} DF_INTF_REG_A60_FIELD_T;

#define DF_INTF_REG_A61                           (BT_ZGB_INTF_REG_BASE + 0xf4)
// Bit 31  :0      reg_ram_bist_cntl              U     RW        default = 'h2
typedef union DF_INTF_REG_A61_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int reg_ram_bist_cntl : 32;
  } b;
} DF_INTF_REG_A61_FIELD_T;

#define DF_INTF_REG_A64                           (BT_ZGB_INTF_REG_BASE + 0x100)
// Bit 6   :0      reg_phy_ema_cfg                U     RW        default = 'h77
// Bit 22  :16     reg_mac_ema_cfg                U     RW        default = 'h77
// Bit 30  :24     reg_cpu_ema_cfg                U     RW        default = 'h77
typedef union DF_INTF_REG_A64_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int reg_phy_ema_cfg : 7;
    unsigned int rsvd_0 : 9;
    unsigned int reg_mac_ema_cfg : 7;
    unsigned int rsvd_1 : 1;
    unsigned int reg_cpu_ema_cfg : 7;
    unsigned int rsvd_2 : 1;
  } b;
} DF_INTF_REG_A64_FIELD_T;

#define DF_INTF_REG_A66                           (BT_ZGB_INTF_REG_BASE + 0x108)
// Bit 0           cpu_clk_en                     U     RW        default = 'h1
// Bit 7   :4      cpu_osc_sel                    U     RW        default = 'h0
// Bit 27  :16     cpu_clk_div                    U     RW        default = 'h244
typedef union DF_INTF_REG_A66_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int cpu_clk_en : 1;
    unsigned int rsvd_0 : 3;
    unsigned int cpu_osc_sel : 4;
    unsigned int rsvd_1 : 8;
    unsigned int cpu_clk_div : 12;
    unsigned int rsvd_2 : 4;
  } b;
} DF_INTF_REG_A66_FIELD_T;

#define DF_INTF_REG_A67                           (BT_ZGB_INTF_REG_BASE + 0x10c)
// Bit 0           uart_clk_en                    U     RW        default = 'h1
// Bit 5   :4      bt24m_osc_sel                  U     RW        default = 'h2
typedef union DF_INTF_REG_A67_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int uart_clk_en : 1;
    unsigned int rsvd_0 : 3;
    unsigned int bt24m_osc_sel : 2;
    unsigned int rsvd_1 : 26;
  } b;
} DF_INTF_REG_A67_FIELD_T;

#define DF_INTF_REG_A68                           (BT_ZGB_INTF_REG_BASE + 0x110)
// Bit 0           btdem_clk_en                   U     RW        default = 'h1
// Bit 7   :4      btdem_clk_inv                  U     RW        default = 'h0
// Bit 27  :16     btdem_clk_div                  U     RW        default = 'ha14
typedef union DF_INTF_REG_A68_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int btdem_clk_en : 1;
    unsigned int rsvd_0 : 3;
    unsigned int btdem_clk_inv : 4;
    unsigned int rsvd_1 : 8;
    unsigned int btdem_clk_div : 12;
    unsigned int rsvd_2 : 4;
  } b;
} DF_INTF_REG_A68_FIELD_T;

#define DF_INTF_REG_A69                           (BT_ZGB_INTF_REG_BASE + 0x114)
// Bit 0           reg_15p4_mode                  U     RW        default = 'h0
// Bit 1           reg_zgb_mac_clk_en             U     RW        default = 'h1
typedef union DF_INTF_REG_A69_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int reg_15p4_mode : 1;
    unsigned int reg_zgb_mac_clk_en : 1;
    unsigned int rsvd_0 : 30;
  } b;
} DF_INTF_REG_A69_FIELD_T;

#define DF_INTF_REG_A71                           (BT_ZGB_INTF_REG_BASE + 0x11c)
// Bit 31  :0      reg_bt_soft_rst_cfg            U     RW        default = 'h0
typedef union DF_INTF_REG_A71_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int reg_bt_soft_rst_cfg : 32;
  } b;
} DF_INTF_REG_A71_FIELD_T;

#endif
