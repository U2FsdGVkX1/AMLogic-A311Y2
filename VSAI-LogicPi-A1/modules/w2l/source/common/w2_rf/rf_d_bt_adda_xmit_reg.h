/* SPDX-License-Identifier: GPL-2.0 */
/*
* Copyright (C) 202X Original Author (retain original author information)
* Copyright (C) 202X Amlogic, Inc. All rights reserved.
*
* Description:
*/
#ifdef RF_D_BT_ADDA_XMIT_REG
#else
#define RF_D_BT_ADDA_XMIT_REG

#define RG_BT_XMIT_A0                             (0x0)
// Bit 31  :0      rg_xmit_cfg0                   U     RW        default = 'h0
typedef union RG_BT_XMIT_A0_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_xmit_cfg0 : 32;
  } b;
} RG_BT_XMIT_A0_FIELD_T;

#define RG_BT_XMIT_A1                             (0x4)
// Bit 31  :0      rg_xmit_cfg1                   U     RW        default = 'h0
typedef union RG_BT_XMIT_A1_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_xmit_cfg1 : 32;
  } b;
} RG_BT_XMIT_A1_FIELD_T;

#define RG_BT_XMIT_A2                             (0x8)
// Bit 24  :0      rg_tg1_f_sel                   U     RW        default = 'h200000
// Bit 28  :25     rg_tg1_tone_gain               U     RW        default = 'h0
// Bit 29          rg_tg1_enable                  U     RW        default = 'h0
// Bit 30          rg_tg1_tone_40                 U     RW        default = 'h0
// Bit 31          rg_tg1_tone_man_en             U     RW        default = 'h1
typedef union RG_BT_XMIT_A2_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tg1_f_sel : 25;
    unsigned int rg_tg1_tone_gain : 4;
    unsigned int rg_tg1_enable : 1;
    unsigned int rg_tg1_tone_40 : 1;
    unsigned int rg_tg1_tone_man_en : 1;
  } b;
} RG_BT_XMIT_A2_FIELD_T;

#define RG_BT_XMIT_A3                             (0xc)
// Bit 24  :0      rg_tg2_f_sel                   U     RW        default = 'h200000
// Bit 28  :25     rg_tg2_tone_gain               U     RW        default = 'h0
// Bit 29          rg_tg2_enable                  U     RW        default = 'h0
// Bit 30          rg_tg2_tone_40                 U     RW        default = 'h0
// Bit 31          rg_tg2_tone_man_en             U     RW        default = 'h1
typedef union RG_BT_XMIT_A3_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tg2_f_sel : 25;
    unsigned int rg_tg2_tone_gain : 4;
    unsigned int rg_tg2_enable : 1;
    unsigned int rg_tg2_tone_40 : 1;
    unsigned int rg_tg2_tone_man_en : 1;
  } b;
} RG_BT_XMIT_A3_FIELD_T;

#define RG_BT_XMIT_A4                             (0x10)
// Bit 1   :0      rg_tx_signal_sel               U     RW        default = 'h0
// Bit 14  :4      rg_tx_const_i                  U     RW        default = 'h0
// Bit 26  :16     rg_tx_const_q                  U     RW        default = 'h0
// Bit 31          rg_tx_const_v                  U     RW        default = 'h0
typedef union RG_BT_XMIT_A4_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_signal_sel : 2;
    unsigned int rsvd_0 : 2;
    unsigned int rg_tx_const_i : 11;
    unsigned int rsvd_1 : 1;
    unsigned int rg_tx_const_q : 11;
    unsigned int rsvd_2 : 4;
    unsigned int rg_tx_const_v : 1;
  } b;
} RG_BT_XMIT_A4_FIELD_T;

#define RG_BT_XMIT_A6                             (0x18)
// Bit 7   :0      rg_txirr_comp_theta0           U     RW        default = 'h0
// Bit 15  :8      rg_txirr_comp_theta1           U     RW        default = 'h0
// Bit 23  :16     rg_txirr_comp_theta2           U     RW        default = 'h0
// Bit 31  :24     rg_txirr_comp_theta3           U     RW        default = 'h0
typedef union RG_BT_XMIT_A6_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txirr_comp_theta0 : 8;
    unsigned int rg_txirr_comp_theta1 : 8;
    unsigned int rg_txirr_comp_theta2 : 8;
    unsigned int rg_txirr_comp_theta3 : 8;
  } b;
} RG_BT_XMIT_A6_FIELD_T;

#define RG_BT_XMIT_A10                            (0x28)
// Bit 7   :0      rg_txirr_comp_alpha0           U     RW        default = 'h0
// Bit 15  :8      rg_txirr_comp_alpha1           U     RW        default = 'h0
// Bit 23  :16     rg_txirr_comp_alpha2           U     RW        default = 'h0
// Bit 31  :24     rg_txirr_comp_alpha3           U     RW        default = 'h0
typedef union RG_BT_XMIT_A10_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txirr_comp_alpha0 : 8;
    unsigned int rg_txirr_comp_alpha1 : 8;
    unsigned int rg_txirr_comp_alpha2 : 8;
    unsigned int rg_txirr_comp_alpha3 : 8;
  } b;
} RG_BT_XMIT_A10_FIELD_T;

#define RG_BT_XMIT_A14                            (0x38)
// Bit 23  :0      rg_tx_pwrlvl0                  U     RW        default = 'h800000
typedef union RG_BT_XMIT_A14_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_pwrlvl0 : 24;
    unsigned int rsvd_0 : 8;
  } b;
} RG_BT_XMIT_A14_FIELD_T;

#define RG_BT_XMIT_A15                            (0x3c)
// Bit 23  :0      rg_tx_pwrlvl1                  U     RW        default = 'h800000
typedef union RG_BT_XMIT_A15_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_pwrlvl1 : 24;
    unsigned int rsvd_0 : 8;
  } b;
} RG_BT_XMIT_A15_FIELD_T;

#define RG_BT_XMIT_A16                            (0x40)
// Bit 23  :0      rg_tx_pwrlvl2                  U     RW        default = 'h800000
typedef union RG_BT_XMIT_A16_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_pwrlvl2 : 24;
    unsigned int rsvd_0 : 8;
  } b;
} RG_BT_XMIT_A16_FIELD_T;

#define RG_BT_XMIT_A17                            (0x44)
// Bit 23  :0      rg_tx_pwrlvl3                  U     RW        default = 'h800000
typedef union RG_BT_XMIT_A17_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_pwrlvl3 : 24;
    unsigned int rsvd_0 : 8;
  } b;
} RG_BT_XMIT_A17_FIELD_T;

#define RG_BT_XMIT_A30                            (0x78)
// Bit 0           rg_tx_iqmm_bypass              U     RW        default = 'h1
// Bit 4           rg_tx_negate_msb               U     RW        default = 'h1
// Bit 8           rg_tx_iq_swap                  U     RW        default = 'h0
// Bit 19  :16     rg_tx_async_wgap               U     RW        default = 'ha
typedef union RG_BT_XMIT_A30_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_iqmm_bypass : 1;
    unsigned int rsvd_0 : 3;
    unsigned int rg_tx_negate_msb : 1;
    unsigned int rsvd_1 : 3;
    unsigned int rg_tx_iq_swap : 1;
    unsigned int rsvd_2 : 7;
    unsigned int rg_tx_async_wgap : 4;
    unsigned int rsvd_3 : 12;
  } b;
} RG_BT_XMIT_A30_FIELD_T;

#define RG_BT_XMIT_A66                            (0x108)
// Bit 23  :0      rg_man_tx_pwrlvl               U     RW        default = 'h800000
// Bit 31          rg_tx_pwr_sel_man_en           U     RW        default = 'h0
typedef union RG_BT_XMIT_A66_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_man_tx_pwrlvl : 24;
    unsigned int rsvd_0 : 7;
    unsigned int rg_tx_pwr_sel_man_en : 1;
  } b;
} RG_BT_XMIT_A66_FIELD_T;

#define RG_BT_XMIT_A67                            (0x10c)
// Bit 7   :0      rg_man_txirr_comp_theta        U     RW        default = 'h0
// Bit 15  :8      rg_man_txirr_comp_alpha        U     RW        default = 'h0
// Bit 16          rg_txpwc_comp_man_sel          U     RW        default = 'h0
// Bit 31  :24     rg_txpwc_comp_man              U     RW        default = 'h80
typedef union RG_BT_XMIT_A67_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_man_txirr_comp_theta : 8;
    unsigned int rg_man_txirr_comp_alpha : 8;
    unsigned int rg_txpwc_comp_man_sel : 1;
    unsigned int rsvd_0 : 7;
    unsigned int rg_txpwc_comp_man : 8;
  } b;
} RG_BT_XMIT_A67_FIELD_T;

#define RG_BT_XMIT_A68                            (0x110)
// Bit 7   :0      rg_tx_atten_factor             U     RW        default = 'h8
typedef union RG_BT_XMIT_A68_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_atten_factor : 8;
    unsigned int rsvd_0 : 24;
  } b;
} RG_BT_XMIT_A68_FIELD_T;

#define RG_BT_XMIT_A69                            (0x114)
// Bit 1   :0      rg_xmit_tb_sel                 U     RW        default = 'h0
typedef union RG_BT_XMIT_A69_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_xmit_tb_sel : 2;
    unsigned int rsvd_0 : 30;
  } b;
} RG_BT_XMIT_A69_FIELD_T;

#endif

