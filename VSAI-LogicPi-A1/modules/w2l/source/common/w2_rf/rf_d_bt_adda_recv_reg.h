/* SPDX-License-Identifier: GPL-2.0 */
/*
* Copyright (C) 202X Original Author (retain original author information)
* Copyright (C) 202X Amlogic, Inc. All rights reserved.
*
* Description:
*/
#ifdef RF_D_BT_ADDA_RECV_REG
#else
#define RF_D_BT_ADDA_RECV_REG

#define RG_BT_RECV_A0                             (0x0)
// Bit 31  :0      rg_recv_cfg0                   U     RW        default = 'hf
typedef union RG_BT_RECV_A0_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_recv_cfg0 : 32;
  } b;
} RG_BT_RECV_A0_FIELD_T;

#define RG_BT_RECV_A1                             (0x4)
// Bit 31  :0      rg_recv_cfg1                   U     RW        default = 'h0
typedef union RG_BT_RECV_A1_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_recv_cfg1 : 32;
  } b;
} RG_BT_RECV_A1_FIELD_T;

#define RG_BT_RECV_A2                             (0x8)
// Bit 0           rg_rxneg_msb                   U     RW        default = 'h0
// Bit 1           rg_rxiq_swap                   U     RW        default = 'h0
// Bit 11  :4      rg_rxi_dcoft                   U     RW        default = 'h0
// Bit 19  :12     rg_rxq_dcoft                   U     RW        default = 'h0
// Bit 24          rg_to_agc_en                   U     RW        default = 'h1
typedef union RG_BT_RECV_A2_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_rxneg_msb : 1;
    unsigned int rg_rxiq_swap : 1;
    unsigned int rsvd_0 : 2;
    unsigned int rg_rxi_dcoft : 8;
    unsigned int rg_rxq_dcoft : 8;
    unsigned int rsvd_1 : 4;
    unsigned int rg_to_agc_en : 1;
    unsigned int rsvd_2 : 7;
  } b;
} RG_BT_RECV_A2_FIELD_T;

#define RG_BT_RECV_A3                             (0xc)
// Bit 6   :0      rg_cwr_sel_freq_point0         U     RW        default = 'h0
// Bit 14  :8      rg_cwr_sel_freq_point1         U     RW        default = 'h0
// Bit 22  :16     rg_cwr_sel_freq_point2         U     RW        default = 'h0
// Bit 30  :24     rg_cwr_sel_freq_point3         U     RW        default = 'h0
typedef union RG_BT_RECV_A3_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_cwr_sel_freq_point0 : 7;
    unsigned int rsvd_0 : 1;
    unsigned int rg_cwr_sel_freq_point1 : 7;
    unsigned int rsvd_1 : 1;
    unsigned int rg_cwr_sel_freq_point2 : 7;
    unsigned int rsvd_2 : 1;
    unsigned int rg_cwr_sel_freq_point3 : 7;
    unsigned int rsvd_3 : 1;
  } b;
} RG_BT_RECV_A3_FIELD_T;

#define RG_BT_RECV_A4                             (0x10)
// Bit 24  :0      rg_cwr_hard_angle_base0        U     RW        default = 'h0
typedef union RG_BT_RECV_A4_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_cwr_hard_angle_base0 : 25;
    unsigned int rsvd_0 : 7;
  } b;
} RG_BT_RECV_A4_FIELD_T;

#define RG_BT_RECV_A5                             (0x14)
// Bit 24  :0      rg_cwr_hard_angle_base1        U     RW        default = 'h0
typedef union RG_BT_RECV_A5_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_cwr_hard_angle_base1 : 25;
    unsigned int rsvd_0 : 7;
  } b;
} RG_BT_RECV_A5_FIELD_T;

#define RG_BT_RECV_A6                             (0x18)
// Bit 24  :0      rg_cwr_hard_angle_base2        U     RW        default = 'h0
typedef union RG_BT_RECV_A6_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_cwr_hard_angle_base2 : 25;
    unsigned int rsvd_0 : 7;
  } b;
} RG_BT_RECV_A6_FIELD_T;

#define RG_BT_RECV_A7                             (0x1c)
// Bit 24  :0      rg_cwr_hard_angle_base3        U     RW        default = 'h0
typedef union RG_BT_RECV_A7_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_cwr_hard_angle_base3 : 25;
    unsigned int rsvd_0 : 7;
  } b;
} RG_BT_RECV_A7_FIELD_T;

#define RG_BT_RECV_A8                             (0x20)
// Bit 8   :0      rg_cwr_thr_pow                 U     RW        default = 'h0
typedef union RG_BT_RECV_A8_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_cwr_thr_pow : 9;
    unsigned int rsvd_0 : 23;
  } b;
} RG_BT_RECV_A8_FIELD_T;

#define RG_BT_RECV_A9                             (0x24)
// Bit 0           rg_cwr_man_mode                U     RW        default = 'h0
// Bit 2           rg_cwr_bypass                  U     RW        default = 'h0
// Bit 28  :4      rg_cwr_man_angle_base          U     RW        default = 'h0
// Bit 31          rg_dcloop_bypass               U     RW        default = 'h0
typedef union RG_BT_RECV_A9_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_cwr_man_mode : 1;
    unsigned int rsvd_0 : 1;
    unsigned int rg_cwr_bypass : 1;
    unsigned int rsvd_1 : 1;
    unsigned int rg_cwr_man_angle_base : 25;
    unsigned int rsvd_2 : 2;
    unsigned int rg_dcloop_bypass : 1;
  } b;
} RG_BT_RECV_A9_FIELD_T;

#define RG_BT_RECV_A10                            (0x28)
// Bit 0           rg_agc_gain_bypass_man_mode     U     RW        default = 'h0
// Bit 4           rg_agc_gain_bypass             U     RW        default = 'h0
typedef union RG_BT_RECV_A10_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_agc_gain_bypass_man_mode : 1;
    unsigned int rsvd_0 : 3;
    unsigned int rg_agc_gain_bypass : 1;
    unsigned int rsvd_1 : 27;
  } b;
} RG_BT_RECV_A10_FIELD_T;

#define RG_BT_RECV_A11                            (0x2c)
// Bit 0           ro_dc_loop_esti_v              U     RO        default = 'h0
// Bit 11  :4      ro_dc_loop_esti_i              U     RO        default = 'h0
// Bit 23  :16     ro_dc_loop_esti_q              U     RO        default = 'h0
typedef union RG_BT_RECV_A11_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_dc_loop_esti_v : 1;
    unsigned int rsvd_0 : 3;
    unsigned int ro_dc_loop_esti_i : 8;
    unsigned int rsvd_1 : 4;
    unsigned int ro_dc_loop_esti_q : 8;
    unsigned int rsvd_2 : 8;
  } b;
} RG_BT_RECV_A11_FIELD_T;

#define RG_BT_RECV_A12                            (0x30)
// Bit 9   :0      rg_cwr_cnt                     U     RW        default = 'h201
// Bit 25  :16     rg_dcloop_cnt                  U     RW        default = 'h201
typedef union RG_BT_RECV_A12_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_cwr_cnt : 10;
    unsigned int rsvd_0 : 6;
    unsigned int rg_dcloop_cnt : 10;
    unsigned int rsvd_1 : 6;
  } b;
} RG_BT_RECV_A12_FIELD_T;

#endif

