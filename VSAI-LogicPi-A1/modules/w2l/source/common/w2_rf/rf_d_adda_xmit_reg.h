/* SPDX-License-Identifier: GPL-2.0 */
/*
* Copyright (C) 202X Original Author (retain original author information)
* Copyright (C) 202X Amlogic, Inc. All rights reserved.
*
* Description:
*/
#ifdef RF_D_ADDA_XMIT_REG
#else
#define RF_D_ADDA_XMIT_REG

#define RG_XMIT_A0                                (0x0)
// Bit 31  :0      rg_xmit_cfg0                   U     RW        default = 'h0
typedef union RG_XMIT_A0_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_xmit_cfg0 : 32;
  } b;
} RG_XMIT_A0_FIELD_T;

#define RG_XMIT_A1                                (0x4)
// Bit 31  :0      rg_xmit_cfg1                   U     RW        default = 'h0
typedef union RG_XMIT_A1_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_xmit_cfg1 : 32;
  } b;
} RG_XMIT_A1_FIELD_T;

#define RG_XMIT_A2                                (0x8)
// Bit 24  :0      rg_tg1_f_sel                   U     RW        default = 'h200000
// Bit 28  :25     rg_tg1_tone_gain               U     RW        default = 'h4
// Bit 29          rg_tg1_enable                  U     RW        default = 'h0
// Bit 30          rg_tg1_tone_40                 U     RW        default = 'h0
// Bit 31          rg_tg1_tone_man_en             U     RW        default = 'h1
typedef union RG_XMIT_A2_FIELD
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
} RG_XMIT_A2_FIELD_T;

#define RG_XMIT_A3                                (0xc)
// Bit 24  :0      rg_tg2_f_sel                   U     RW        default = 'h200000
// Bit 28  :25     rg_tg2_tone_gain               U     RW        default = 'h4
// Bit 29          rg_tg2_enable                  U     RW        default = 'h0
// Bit 30          rg_tg2_tone_40                 U     RW        default = 'h0
// Bit 31          rg_tg2_tone_man_en             U     RW        default = 'h1
typedef union RG_XMIT_A3_FIELD
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
} RG_XMIT_A3_FIELD_T;

#define RG_XMIT_A4                                (0x10)
// Bit 1   :0      rg_tx_signal_sel               U     RW        default = 'h0
// Bit 15  :4      rg_tx_const_i                  U     RW        default = 'h0
// Bit 27  :16     rg_tx_const_q                  U     RW        default = 'h0
// Bit 31          rg_tx_const_v                  U     RW        default = 'h0
typedef union RG_XMIT_A4_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_signal_sel : 2;
    unsigned int rsvd_0 : 2;
    unsigned int rg_tx_const_i : 12;
    unsigned int rg_tx_const_q : 12;
    unsigned int rsvd_1 : 3;
    unsigned int rg_tx_const_v : 1;
  } b;
} RG_XMIT_A4_FIELD_T;

#define RG_XMIT_A5                                (0x14)
// Bit 31  :0      rg_tim_ratio                   U     RW        default = 'h0
typedef union RG_XMIT_A5_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tim_ratio : 32;
  } b;
} RG_XMIT_A5_FIELD_T;

#define RG_XMIT_A6                                (0x18)
// Bit 7   :0      rg_txirr_comp_theta0           U     RW        default = 'h0
// Bit 15  :8      rg_txirr_comp_theta1           U     RW        default = 'h0
// Bit 23  :16     rg_txirr_comp_theta2           U     RW        default = 'h0
// Bit 31  :24     rg_txirr_comp_theta3           U     RW        default = 'h0
typedef union RG_XMIT_A6_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txirr_comp_theta0 : 8;
    unsigned int rg_txirr_comp_theta1 : 8;
    unsigned int rg_txirr_comp_theta2 : 8;
    unsigned int rg_txirr_comp_theta3 : 8;
  } b;
} RG_XMIT_A6_FIELD_T;

#define RG_XMIT_A7                                (0x1c)
// Bit 7   :0      rg_txirr_comp_theta4           U     RW        default = 'h0
// Bit 15  :8      rg_txirr_comp_theta5           U     RW        default = 'h0
// Bit 23  :16     rg_txirr_comp_theta6           U     RW        default = 'h0
// Bit 31  :24     rg_txirr_comp_theta7           U     RW        default = 'h0
typedef union RG_XMIT_A7_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txirr_comp_theta4 : 8;
    unsigned int rg_txirr_comp_theta5 : 8;
    unsigned int rg_txirr_comp_theta6 : 8;
    unsigned int rg_txirr_comp_theta7 : 8;
  } b;
} RG_XMIT_A7_FIELD_T;

#define RG_XMIT_A8                                (0x20)
// Bit 7   :0      rg_txirr_comp_theta8           U     RW        default = 'h0
// Bit 15  :8      rg_txirr_comp_theta9           U     RW        default = 'h0
// Bit 23  :16     rg_txirr_comp_thetaa           U     RW        default = 'h0
// Bit 31  :24     rg_txirr_comp_thetab           U     RW        default = 'h0
typedef union RG_XMIT_A8_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txirr_comp_theta8 : 8;
    unsigned int rg_txirr_comp_theta9 : 8;
    unsigned int rg_txirr_comp_thetaa : 8;
    unsigned int rg_txirr_comp_thetab : 8;
  } b;
} RG_XMIT_A8_FIELD_T;

#define RG_XMIT_A9                                (0x24)
// Bit 7   :0      rg_txirr_comp_thetac           U     RW        default = 'h0
// Bit 15  :8      rg_txirr_comp_thetad           U     RW        default = 'h0
// Bit 23  :16     rg_txirr_comp_thetae           U     RW        default = 'h0
// Bit 31  :24     rg_txirr_comp_thetaf           U     RW        default = 'h0
typedef union RG_XMIT_A9_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txirr_comp_thetac : 8;
    unsigned int rg_txirr_comp_thetad : 8;
    unsigned int rg_txirr_comp_thetae : 8;
    unsigned int rg_txirr_comp_thetaf : 8;
  } b;
} RG_XMIT_A9_FIELD_T;

#define RG_XMIT_A10                               (0x28)
// Bit 7   :0      rg_txirr_comp_alpha0           U     RW        default = 'h0
// Bit 15  :8      rg_txirr_comp_alpha1           U     RW        default = 'h0
// Bit 23  :16     rg_txirr_comp_alpha2           U     RW        default = 'h0
// Bit 31  :24     rg_txirr_comp_alpha3           U     RW        default = 'h0
typedef union RG_XMIT_A10_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txirr_comp_alpha0 : 8;
    unsigned int rg_txirr_comp_alpha1 : 8;
    unsigned int rg_txirr_comp_alpha2 : 8;
    unsigned int rg_txirr_comp_alpha3 : 8;
  } b;
} RG_XMIT_A10_FIELD_T;

#define RG_XMIT_A11                               (0x2c)
// Bit 7   :0      rg_txirr_comp_alpha4           U     RW        default = 'h0
// Bit 15  :8      rg_txirr_comp_alpha5           U     RW        default = 'h0
// Bit 23  :16     rg_txirr_comp_alpha6           U     RW        default = 'h0
// Bit 31  :24     rg_txirr_comp_alpha7           U     RW        default = 'h0
typedef union RG_XMIT_A11_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txirr_comp_alpha4 : 8;
    unsigned int rg_txirr_comp_alpha5 : 8;
    unsigned int rg_txirr_comp_alpha6 : 8;
    unsigned int rg_txirr_comp_alpha7 : 8;
  } b;
} RG_XMIT_A11_FIELD_T;

#define RG_XMIT_A12                               (0x30)
// Bit 7   :0      rg_txirr_comp_alpha8           U     RW        default = 'h0
// Bit 15  :8      rg_txirr_comp_alpha9           U     RW        default = 'h0
// Bit 23  :16     rg_txirr_comp_alphaa           U     RW        default = 'h0
// Bit 31  :24     rg_txirr_comp_alphab           U     RW        default = 'h0
typedef union RG_XMIT_A12_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txirr_comp_alpha8 : 8;
    unsigned int rg_txirr_comp_alpha9 : 8;
    unsigned int rg_txirr_comp_alphaa : 8;
    unsigned int rg_txirr_comp_alphab : 8;
  } b;
} RG_XMIT_A12_FIELD_T;

#define RG_XMIT_A13                               (0x34)
// Bit 7   :0      rg_txirr_comp_alphac           U     RW        default = 'h0
// Bit 15  :8      rg_txirr_comp_alphad           U     RW        default = 'h0
// Bit 23  :16     rg_txirr_comp_alphae           U     RW        default = 'h0
// Bit 31  :24     rg_txirr_comp_alphaf           U     RW        default = 'h0
typedef union RG_XMIT_A13_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txirr_comp_alphac : 8;
    unsigned int rg_txirr_comp_alphad : 8;
    unsigned int rg_txirr_comp_alphae : 8;
    unsigned int rg_txirr_comp_alphaf : 8;
  } b;
} RG_XMIT_A13_FIELD_T;

#define RG_XMIT_A18                               (0x48)
// Bit 25  :0      rg_tx_pwrlvl0                  U     RW        default = 'h800000
typedef union RG_XMIT_A18_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_pwrlvl0 : 26;
    unsigned int rsvd_0 : 6;
  } b;
} RG_XMIT_A18_FIELD_T;

#define RG_XMIT_A19                               (0x4c)
// Bit 25  :0      rg_tx_pwrlvl1                  U     RW        default = 'h800000
typedef union RG_XMIT_A19_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_pwrlvl1 : 26;
    unsigned int rsvd_0 : 6;
  } b;
} RG_XMIT_A19_FIELD_T;

#define RG_XMIT_A20                               (0x50)
// Bit 25  :0      rg_tx_pwrlvl2                  U     RW        default = 'h800000
typedef union RG_XMIT_A20_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_pwrlvl2 : 26;
    unsigned int rsvd_0 : 6;
  } b;
} RG_XMIT_A20_FIELD_T;

#define RG_XMIT_A21                               (0x54)
// Bit 25  :0      rg_tx_pwrlvl3                  U     RW        default = 'h800000
typedef union RG_XMIT_A21_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_pwrlvl3 : 26;
    unsigned int rsvd_0 : 6;
  } b;
} RG_XMIT_A21_FIELD_T;

#define RG_XMIT_A22                               (0x58)
// Bit 25  :0      rg_tx_pwrlvl4                  U     RW        default = 'h800000
typedef union RG_XMIT_A22_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_pwrlvl4 : 26;
    unsigned int rsvd_0 : 6;
  } b;
} RG_XMIT_A22_FIELD_T;

#define RG_XMIT_A23                               (0x5c)
// Bit 25  :0      rg_tx_pwrlvl5                  U     RW        default = 'h800000
typedef union RG_XMIT_A23_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_pwrlvl5 : 26;
    unsigned int rsvd_0 : 6;
  } b;
} RG_XMIT_A23_FIELD_T;

#define RG_XMIT_A24                               (0x60)
// Bit 25  :0      rg_tx_pwrlvl6                  U     RW        default = 'h800000
typedef union RG_XMIT_A24_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_pwrlvl6 : 26;
    unsigned int rsvd_0 : 6;
  } b;
} RG_XMIT_A24_FIELD_T;

#define RG_XMIT_A25                               (0x64)
// Bit 25  :0      rg_tx_pwrlvl7                  U     RW        default = 'h800000
typedef union RG_XMIT_A25_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_pwrlvl7 : 26;
    unsigned int rsvd_0 : 6;
  } b;
} RG_XMIT_A25_FIELD_T;

#define RG_XMIT_A26                               (0x68)
// Bit 25  :0      rg_tx_pwrlvl8                  U     RW        default = 'h800000
typedef union RG_XMIT_A26_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_pwrlvl8 : 26;
    unsigned int rsvd_0 : 6;
  } b;
} RG_XMIT_A26_FIELD_T;

#define RG_XMIT_A27                               (0x6c)
// Bit 25  :0      rg_tx_pwrlvl9                  U     RW        default = 'h800000
typedef union RG_XMIT_A27_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_pwrlvl9 : 26;
    unsigned int rsvd_0 : 6;
  } b;
} RG_XMIT_A27_FIELD_T;

#define RG_XMIT_A28                               (0x70)
// Bit 25  :0      rg_tx_pwrlvla                  U     RW        default = 'h800000
typedef union RG_XMIT_A28_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_pwrlvla : 26;
    unsigned int rsvd_0 : 6;
  } b;
} RG_XMIT_A28_FIELD_T;

#define RG_XMIT_A29                               (0x74)
// Bit 25  :0      rg_tx_pwrlvlb                  U     RW        default = 'h800000
typedef union RG_XMIT_A29_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_pwrlvlb : 26;
    unsigned int rsvd_0 : 6;
  } b;
} RG_XMIT_A29_FIELD_T;

#define RG_XMIT_A30                               (0x78)
// Bit 25  :0      rg_tx_pwrlvlc                  U     RW        default = 'h800000
typedef union RG_XMIT_A30_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_pwrlvlc : 26;
    unsigned int rsvd_0 : 6;
  } b;
} RG_XMIT_A30_FIELD_T;

#define RG_XMIT_A31                               (0x7c)
// Bit 25  :0      rg_tx_pwrlvld                  U     RW        default = 'h800000
typedef union RG_XMIT_A31_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_pwrlvld : 26;
    unsigned int rsvd_0 : 6;
  } b;
} RG_XMIT_A31_FIELD_T;

#define RG_XMIT_A32                               (0x80)
// Bit 25  :0      rg_tx_pwrlvle                  U     RW        default = 'h800000
typedef union RG_XMIT_A32_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_pwrlvle : 26;
    unsigned int rsvd_0 : 6;
  } b;
} RG_XMIT_A32_FIELD_T;

#define RG_XMIT_A33                               (0x84)
// Bit 25  :0      rg_tx_pwrlvlf                  U     RW        default = 'h800000
typedef union RG_XMIT_A33_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_pwrlvlf : 26;
    unsigned int rsvd_0 : 6;
  } b;
} RG_XMIT_A33_FIELD_T;

#define RG_XMIT_A34                               (0x88)
// Bit 0           rg_tx_iqmm_bypass              U     RW        default = 'h1
// Bit 4           rg_tx_negate_msb               U     RW        default = 'h1
// Bit 8           rg_tx_iq_swap                  U     RW        default = 'h0
// Bit 13  :12     rg_tx_dout_sel                 U     RW        default = 'h0
// Bit 19  :16     rg_tx_async_wgap               U     RW        default = 'ha
typedef union RG_XMIT_A34_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_iqmm_bypass : 1;
    unsigned int rsvd_0 : 3;
    unsigned int rg_tx_negate_msb : 1;
    unsigned int rsvd_1 : 3;
    unsigned int rg_tx_iq_swap : 1;
    unsigned int rsvd_2 : 3;
    unsigned int rg_tx_dout_sel : 2;
    unsigned int rsvd_3 : 2;
    unsigned int rg_tx_async_wgap : 4;
    unsigned int rsvd_4 : 12;
  } b;
} RG_XMIT_A34_FIELD_T;

#define RG_XMIT_A45                               (0xb4)
// Bit 25  :0      rg_man_tx_pwrlvl               U     RW        default = 'h800000
// Bit 31          rg_tx_pwr_sel_man_en           U     RW        default = 'h0
typedef union RG_XMIT_A45_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_man_tx_pwrlvl : 26;
    unsigned int rsvd_0 : 5;
    unsigned int rg_tx_pwr_sel_man_en : 1;
  } b;
} RG_XMIT_A45_FIELD_T;

#define RG_XMIT_A46                               (0xb8)
// Bit 7   :0      rg_man_txirr_comp_theta        U     RW        default = 'h0
// Bit 15  :8      rg_man_txirr_comp_alpha        U     RW        default = 'h0
// Bit 16          rg_txpwc_comp_man_sel          U     RW        default = 'h1
// Bit 31  :24     rg_txpwc_comp_man              U     RW        default = 'h80
typedef union RG_XMIT_A46_FIELD
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
} RG_XMIT_A46_FIELD_T;

#define RG_XMIT_A47                               (0xbc)
// Bit 15  :0      rg_tx_ex_gain0                 U     RW        default = 'h9
// Bit 31  :16     rg_tx_ex_gain1                 U     RW        default = 'ha
typedef union RG_XMIT_A47_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_ex_gain0 : 16;
    unsigned int rg_tx_ex_gain1 : 16;
  } b;
} RG_XMIT_A47_FIELD_T;

#define RG_XMIT_A48                               (0xd0)
// Bit 15  :0      rg_tx_ex_gain2                 U     RW        default = 'h9
// Bit 31  :16     rg_tx_ex_gain3                 U     RW        default = 'ha
typedef union RG_XMIT_A48_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_ex_gain2 : 16;
    unsigned int rg_tx_ex_gain3 : 16;
  } b;
} RG_XMIT_A48_FIELD_T;

#define RG_XMIT_A49                               (0xd4)
// Bit 15  :0      rg_tx_ex_gain4                 U     RW        default = 'h9
// Bit 31  :16     rg_tx_ex_gain5                 U     RW        default = 'ha
typedef union RG_XMIT_A49_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_ex_gain4 : 16;
    unsigned int rg_tx_ex_gain5 : 16;
  } b;
} RG_XMIT_A49_FIELD_T;

#define RG_XMIT_A50                               (0xd8)
// Bit 15  :0      rg_tx_ex_gain6                 U     RW        default = 'h9
// Bit 31  :16     rg_tx_ex_gain7                 U     RW        default = 'ha
typedef union RG_XMIT_A50_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_ex_gain6 : 16;
    unsigned int rg_tx_ex_gain7 : 16;
  } b;
} RG_XMIT_A50_FIELD_T;

#define RG_XMIT_A51                               (0xdc)
// Bit 15  :0      rg_tx_ex_gain8                 U     RW        default = 'h9
// Bit 31  :16     rg_tx_ex_gain9                 U     RW        default = 'ha
typedef union RG_XMIT_A51_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_ex_gain8 : 16;
    unsigned int rg_tx_ex_gain9 : 16;
  } b;
} RG_XMIT_A51_FIELD_T;

#define RG_XMIT_A52                               (0xe0)
// Bit 15  :0      rg_tx_ex_gaina                 U     RW        default = 'h9
// Bit 31  :16     rg_tx_ex_gainb                 U     RW        default = 'ha
typedef union RG_XMIT_A52_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_ex_gaina : 16;
    unsigned int rg_tx_ex_gainb : 16;
  } b;
} RG_XMIT_A52_FIELD_T;

#define RG_XMIT_A53                               (0xe4)
// Bit 15  :0      rg_tx_ex_gainc                 U     RW        default = 'h9
// Bit 31  :16     rg_tx_ex_gaind                 U     RW        default = 'ha
typedef union RG_XMIT_A53_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_ex_gainc : 16;
    unsigned int rg_tx_ex_gaind : 16;
  } b;
} RG_XMIT_A53_FIELD_T;

#define RG_XMIT_A54                               (0xe8)
// Bit 15  :0      rg_tx_ex_gaine                 U     RW        default = 'h9
// Bit 31  :16     rg_tx_ex_gainf                 U     RW        default = 'ha
typedef union RG_XMIT_A54_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_ex_gaine : 16;
    unsigned int rg_tx_ex_gainf : 16;
  } b;
} RG_XMIT_A54_FIELD_T;

#define RG_XMIT_A55                               (0xec)
// Bit 15  :0      rg_tx_gain                     U     RW        default = 'h0
// Bit 16          rg_tx_set                      U     RW        default = 'h0
typedef union RG_XMIT_A55_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_gain : 16;
    unsigned int rg_tx_set : 1;
    unsigned int rsvd_0 : 15;
  } b;
} RG_XMIT_A55_FIELD_T;

#define RG_XMIT_A56                               (0xf0)
// Bit 7   :0      rg_txdpd_comp_in_gain          U     RW        default = 'h80
// Bit 18  :8      rg_txdpd_comp_out_gain         U     RW        default = 'h80
// Bit 26          rg_txdpd_comp_bypass           U     RW        default = 'h1
// Bit 28          rg_txdpd_comp_bypass_man       U     RW        default = 'h1
// Bit 31          rg_txdpd_comp_coef_man_sel     U     RW        default = 'h0
typedef union RG_XMIT_A56_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_in_gain : 8;
    unsigned int rg_txdpd_comp_out_gain : 11;
    unsigned int rsvd_0 : 7;
    unsigned int rg_txdpd_comp_bypass : 1;
    unsigned int rsvd_1 : 1;
    unsigned int rg_txdpd_comp_bypass_man : 1;
    unsigned int rsvd_2 : 2;
    unsigned int rg_txdpd_comp_coef_man_sel : 1;
  } b;
} RG_XMIT_A56_FIELD_T;

#define RG_XMIT_A57                               (0xf4)
// Bit 11  :0      rg_txdpd_comp_coef_i_00_man     U     RW        default = 'hff9
// Bit 27  :16     rg_txdpd_comp_coef_q_00_man     U     RW        default = 'h46
typedef union RG_XMIT_A57_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_00_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_00_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A57_FIELD_T;

#define RG_XMIT_A58                               (0xf8)
// Bit 11  :0      rg_txdpd_comp_coef_i_01_man     U     RW        default = 'hff8
// Bit 27  :16     rg_txdpd_comp_coef_q_01_man     U     RW        default = 'h13
typedef union RG_XMIT_A58_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_01_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_01_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A58_FIELD_T;

#define RG_XMIT_A59                               (0xfc)
// Bit 11  :0      rg_txdpd_comp_coef_i_02_man     U     RW        default = 'h10
// Bit 27  :16     rg_txdpd_comp_coef_q_02_man     U     RW        default = 'h8
typedef union RG_XMIT_A59_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_02_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_02_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A59_FIELD_T;

#define RG_XMIT_A60                               (0x100)
// Bit 11  :0      rg_txdpd_comp_coef_i_03_man     U     RW        default = 'h0
// Bit 27  :16     rg_txdpd_comp_coef_q_03_man     U     RW        default = 'h0
typedef union RG_XMIT_A60_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_03_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_03_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A60_FIELD_T;

#define RG_XMIT_A61                               (0x104)
// Bit 11  :0      rg_txdpd_comp_coef_i_04_man     U     RW        default = 'he
// Bit 27  :16     rg_txdpd_comp_coef_q_04_man     U     RW        default = 'h93
typedef union RG_XMIT_A61_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_04_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_04_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A61_FIELD_T;

#define RG_XMIT_A62                               (0x108)
// Bit 11  :0      rg_txdpd_comp_coef_i_05_man     U     RW        default = 'h16
// Bit 27  :16     rg_txdpd_comp_coef_q_05_man     U     RW        default = 'h1f
typedef union RG_XMIT_A62_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_05_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_05_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A62_FIELD_T;

#define RG_XMIT_A63                               (0x10c)
// Bit 11  :0      rg_txdpd_comp_coef_i_06_man     U     RW        default = 'hfe1
// Bit 27  :16     rg_txdpd_comp_coef_q_06_man     U     RW        default = 'hff9
typedef union RG_XMIT_A63_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_06_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_06_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A63_FIELD_T;

#define RG_XMIT_A64                               (0x110)
// Bit 11  :0      rg_txdpd_comp_coef_i_07_man     U     RW        default = 'h0
// Bit 27  :16     rg_txdpd_comp_coef_q_07_man     U     RW        default = 'h0
typedef union RG_XMIT_A64_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_07_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_07_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A64_FIELD_T;

#define RG_XMIT_A65                               (0x114)
// Bit 11  :0      rg_txdpd_comp_coef_i_08_man     U     RW        default = 'hf79
// Bit 27  :16     rg_txdpd_comp_coef_q_08_man     U     RW        default = 'hc7f
typedef union RG_XMIT_A65_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_08_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_08_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A65_FIELD_T;

#define RG_XMIT_A66                               (0x118)
// Bit 11  :0      rg_txdpd_comp_coef_i_09_man     U     RW        default = 'h9
// Bit 27  :16     rg_txdpd_comp_coef_q_09_man     U     RW        default = 'hf51
typedef union RG_XMIT_A66_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_09_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_09_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A66_FIELD_T;

#define RG_XMIT_A67                               (0x11c)
// Bit 11  :0      rg_txdpd_comp_coef_i_10_man     U     RW        default = 'hff1
// Bit 27  :16     rg_txdpd_comp_coef_q_10_man     U     RW        default = 'h27
typedef union RG_XMIT_A67_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_10_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_10_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A67_FIELD_T;

#define RG_XMIT_A68                               (0x120)
// Bit 11  :0      rg_txdpd_comp_coef_i_11_man     U     RW        default = 'h0
// Bit 27  :16     rg_txdpd_comp_coef_q_11_man     U     RW        default = 'h0
typedef union RG_XMIT_A68_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_11_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_11_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A68_FIELD_T;

#define RG_XMIT_A69                               (0x124)
// Bit 11  :0      rg_txdpd_comp_coef_i_12_man     U     RW        default = 'hfeb
// Bit 27  :16     rg_txdpd_comp_coef_q_12_man     U     RW        default = 'hf4d
typedef union RG_XMIT_A69_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_12_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_12_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A69_FIELD_T;

#define RG_XMIT_A70                               (0x128)
// Bit 11  :0      rg_txdpd_comp_coef_i_13_man     U     RW        default = 'h5
// Bit 27  :16     rg_txdpd_comp_coef_q_13_man     U     RW        default = 'hfe4
typedef union RG_XMIT_A70_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_13_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_13_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A70_FIELD_T;

#define RG_XMIT_A71                               (0x12c)
// Bit 11  :0      rg_txdpd_comp_coef_i_14_man     U     RW        default = 'h6
// Bit 27  :16     rg_txdpd_comp_coef_q_14_man     U     RW        default = 'hfee
typedef union RG_XMIT_A71_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_14_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_14_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A71_FIELD_T;

#define RG_XMIT_A72                               (0x130)
// Bit 11  :0      rg_tx_coeff_20m_0              U     RW        default = 'h2
// Bit 27  :16     rg_tx_coeff_20m_1              U     RW        default = 'h6
typedef union RG_XMIT_A72_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_20m_0 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_20m_1 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A72_FIELD_T;

#define RG_XMIT_A73                               (0x134)
// Bit 11  :0      rg_tx_coeff_20m_2              U     RW        default = 'hb
// Bit 27  :16     rg_tx_coeff_20m_3              U     RW        default = 'h10
typedef union RG_XMIT_A73_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_20m_2 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_20m_3 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A73_FIELD_T;

#define RG_XMIT_A74                               (0x138)
// Bit 11  :0      rg_tx_coeff_20m_4              U     RW        default = 'h12
// Bit 27  :16     rg_tx_coeff_20m_5              U     RW        default = 'he
typedef union RG_XMIT_A74_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_20m_4 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_20m_5 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A74_FIELD_T;

#define RG_XMIT_A75                               (0x13c)
// Bit 11  :0      rg_tx_coeff_20m_6              U     RW        default = 'h0
// Bit 27  :16     rg_tx_coeff_20m_7              U     RW        default = 'hfe5
typedef union RG_XMIT_A75_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_20m_6 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_20m_7 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A75_FIELD_T;

#define RG_XMIT_A76                               (0x140)
// Bit 11  :0      rg_tx_coeff_20m_8              U     RW        default = 'hfbf
// Bit 27  :16     rg_tx_coeff_20m_9              U     RW        default = 'hf96
typedef union RG_XMIT_A76_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_20m_8 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_20m_9 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A76_FIELD_T;

#define RG_XMIT_A77                               (0x144)
// Bit 11  :0      rg_tx_coeff_20m_10             U     RW        default = 'hf76
// Bit 27  :16     rg_tx_coeff_20m_11             U     RW        default = 'hf6f
typedef union RG_XMIT_A77_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_20m_10 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_20m_11 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A77_FIELD_T;

#define RG_XMIT_A78                               (0x148)
// Bit 11  :0      rg_tx_coeff_20m_12             U     RW        default = 'hf92
// Bit 27  :16     rg_tx_coeff_20m_13             U     RW        default = 'hfed
typedef union RG_XMIT_A78_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_20m_12 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_20m_13 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A78_FIELD_T;

#define RG_XMIT_A79                               (0x14c)
// Bit 11  :0      rg_tx_coeff_20m_14             U     RW        default = 'h84
// Bit 27  :16     rg_tx_coeff_20m_15             U     RW        default = 'h14f
typedef union RG_XMIT_A79_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_20m_14 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_20m_15 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A79_FIELD_T;

#define RG_XMIT_A80                               (0x150)
// Bit 11  :0      rg_tx_coeff_20m_16             U     RW        default = 'h23b
// Bit 27  :16     rg_tx_coeff_20m_17             U     RW        default = 'h328
typedef union RG_XMIT_A80_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_20m_16 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_20m_17 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A80_FIELD_T;

#define RG_XMIT_A81                               (0x154)
// Bit 11  :0      rg_tx_coeff_20m_18             U     RW        default = 'h3f5
// Bit 27  :16     rg_tx_coeff_20m_19             U     RW        default = 'h47f
typedef union RG_XMIT_A81_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_20m_18 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_20m_19 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A81_FIELD_T;

#define RG_XMIT_A82                               (0x158)
// Bit 11  :0      rg_tx_coeff_20m_20             U     RW        default = 'h4b0
typedef union RG_XMIT_A82_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_20m_20 : 12;
    unsigned int rsvd_0 : 20;
  } b;
} RG_XMIT_A82_FIELD_T;

#define RG_XMIT_A83                               (0x15c)
// Bit 11  :0      rg_tx_coeff_40m_0              U     RW        default = 'h0
// Bit 27  :16     rg_tx_coeff_40m_1              U     RW        default = 'h2
typedef union RG_XMIT_A83_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_40m_0 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_40m_1 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A83_FIELD_T;

#define RG_XMIT_A84                               (0x160)
// Bit 11  :0      rg_tx_coeff_40m_2              U     RW        default = 'h4
// Bit 27  :16     rg_tx_coeff_40m_3              U     RW        default = 'h2
typedef union RG_XMIT_A84_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_40m_2 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_40m_3 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A84_FIELD_T;

#define RG_XMIT_A85                               (0x164)
// Bit 11  :0      rg_tx_coeff_40m_4              U     RW        default = 'hff8
// Bit 27  :16     rg_tx_coeff_40m_5              U     RW        default = 'hfea
typedef union RG_XMIT_A85_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_40m_4 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_40m_5 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A85_FIELD_T;

#define RG_XMIT_A86                               (0x168)
// Bit 11  :0      rg_tx_coeff_40m_6              U     RW        default = 'hfe2
// Bit 27  :16     rg_tx_coeff_40m_7              U     RW        default = 'hfea
typedef union RG_XMIT_A86_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_40m_6 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_40m_7 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A86_FIELD_T;

#define RG_XMIT_A87                               (0x16c)
// Bit 11  :0      rg_tx_coeff_40m_8              U     RW        default = 'h10
// Bit 27  :16     rg_tx_coeff_40m_9              U     RW        default = 'h48
typedef union RG_XMIT_A87_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_40m_8 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_40m_9 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A87_FIELD_T;

#define RG_XMIT_A88                               (0x170)
// Bit 11  :0      rg_tx_coeff_40m_10             U     RW        default = 'h70
// Bit 27  :16     rg_tx_coeff_40m_11             U     RW        default = 'h56
typedef union RG_XMIT_A88_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_40m_10 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_40m_11 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A88_FIELD_T;

#define RG_XMIT_A89                               (0x174)
// Bit 11  :0      rg_tx_coeff_40m_12             U     RW        default = 'hfe6
// Bit 27  :16     rg_tx_coeff_40m_13             U     RW        default = 'hf3a
typedef union RG_XMIT_A89_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_40m_12 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_40m_13 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A89_FIELD_T;

#define RG_XMIT_A90                               (0x178)
// Bit 11  :0      rg_tx_coeff_40m_14             U     RW        default = 'hebc
// Bit 27  :16     rg_tx_coeff_40m_15             U     RW        default = 'heea
typedef union RG_XMIT_A90_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_40m_14 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_40m_15 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A90_FIELD_T;

#define RG_XMIT_A91                               (0x17c)
// Bit 11  :0      rg_tx_coeff_40m_16             U     RW        default = 'h24
// Bit 27  :16     rg_tx_coeff_40m_17             U     RW        default = 'h256
typedef union RG_XMIT_A91_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_40m_16 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_40m_17 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A91_FIELD_T;

#define RG_XMIT_A92                               (0x180)
// Bit 11  :0      rg_tx_coeff_40m_18             U     RW        default = 'h4ee
// Bit 27  :16     rg_tx_coeff_40m_19             U     RW        default = 'h70a
typedef union RG_XMIT_A92_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_40m_18 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_40m_19 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A92_FIELD_T;

#define RG_XMIT_A93                               (0x184)
// Bit 11  :0      rg_tx_coeff_40m_20             U     RW        default = 'h7da
typedef union RG_XMIT_A93_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_40m_20 : 12;
    unsigned int rsvd_0 : 20;
  } b;
} RG_XMIT_A93_FIELD_T;

#define RG_XMIT_A94                               (0x188)
// Bit 11  :0      rg_tx_coeff_80m_0              U     RW        default = 'hfff
// Bit 27  :16     rg_tx_coeff_80m_1              U     RW        default = 'hffc
typedef union RG_XMIT_A94_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_80m_0 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_80m_1 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A94_FIELD_T;

#define RG_XMIT_A95                               (0x18c)
// Bit 11  :0      rg_tx_coeff_80m_2              U     RW        default = 'hffe
// Bit 27  :16     rg_tx_coeff_80m_3              U     RW        default = 'h6
typedef union RG_XMIT_A95_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_80m_2 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_80m_3 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A95_FIELD_T;

#define RG_XMIT_A96                               (0x190)
// Bit 11  :0      rg_tx_coeff_80m_4              U     RW        default = 'h3
// Bit 27  :16     rg_tx_coeff_80m_5              U     RW        default = 'hff6
typedef union RG_XMIT_A96_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_80m_4 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_80m_5 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A96_FIELD_T;

#define RG_XMIT_A97                               (0x194)
// Bit 11  :0      rg_tx_coeff_80m_6              U     RW        default = 'hffa
// Bit 27  :16     rg_tx_coeff_80m_7              U     RW        default = 'h11
typedef union RG_XMIT_A97_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_80m_6 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_80m_7 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A97_FIELD_T;

#define RG_XMIT_A98                               (0x198)
// Bit 11  :0      rg_tx_coeff_80m_8              U     RW        default = 'h9
// Bit 27  :16     rg_tx_coeff_80m_9              U     RW        default = 'hfe4
typedef union RG_XMIT_A98_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_80m_8 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_80m_9 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A98_FIELD_T;

#define RG_XMIT_A99                               (0x19c)
// Bit 11  :0      rg_tx_coeff_80m_10             U     RW        default = 'hff4
// Bit 27  :16     rg_tx_coeff_80m_11             U     RW        default = 'h2c
typedef union RG_XMIT_A99_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_80m_10 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_80m_11 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A99_FIELD_T;

#define RG_XMIT_A100                              (0x1a0)
// Bit 11  :0      rg_tx_coeff_80m_12             U     RW        default = 'hf
// Bit 27  :16     rg_tx_coeff_80m_13             U     RW        default = 'hfbb
typedef union RG_XMIT_A100_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_80m_12 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_80m_13 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A100_FIELD_T;

#define RG_XMIT_A101                              (0x1a4)
// Bit 11  :0      rg_tx_coeff_80m_14             U     RW        default = 'hfee
// Bit 27  :16     rg_tx_coeff_80m_15             U     RW        default = 'h70
typedef union RG_XMIT_A101_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_80m_14 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_80m_15 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A101_FIELD_T;

#define RG_XMIT_A102                              (0x1a8)
// Bit 11  :0      rg_tx_coeff_80m_16             U     RW        default = 'h14
// Bit 27  :16     rg_tx_coeff_80m_17             U     RW        default = 'hf32
typedef union RG_XMIT_A102_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_80m_16 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_80m_17 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A102_FIELD_T;

#define RG_XMIT_A103                              (0x1ac)
// Bit 11  :0      rg_tx_coeff_80m_18             U     RW        default = 'hfea
// Bit 27  :16     rg_tx_coeff_80m_19             U     RW        default = 'h288
typedef union RG_XMIT_A103_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_80m_18 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_80m_19 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A103_FIELD_T;

#define RG_XMIT_A104                              (0x1b0)
// Bit 11  :0      rg_tx_coeff_80m_20             U     RW        default = 'h416
typedef union RG_XMIT_A104_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_80m_20 : 12;
    unsigned int rsvd_0 : 20;
  } b;
} RG_XMIT_A104_FIELD_T;

#define RG_XMIT_A105                              (0x1b4)
// Bit 0           rg_txdpd_comp_in_320           U     RW        default = 'h0
typedef union RG_XMIT_A105_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_in_320 : 1;
    unsigned int rsvd_0 : 31;
  } b;
} RG_XMIT_A105_FIELD_T;

#define RG_XMIT_A106                              (0x1b8)
// Bit 31  :12     rg_txdpd_coef_update_en        U     RW        default = 'hddddd
typedef union RG_XMIT_A106_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rsvd_0 : 12;
    unsigned int rg_txdpd_coef_update_en : 20;
  } b;
} RG_XMIT_A106_FIELD_T;

#define RG_XMIT_A111                              (0x1cc)
// Bit 1   :0      rg_txirr_theta_step            U     RW        default = 'h0
// Bit 27  :8      rg_txdpd_powr_update_en        U     RW        default = 'h55555
typedef union RG_XMIT_A111_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txirr_theta_step : 2;
    unsigned int rsvd_0 : 6;
    unsigned int rg_txdpd_powr_update_en : 20;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A111_FIELD_T;

#define RG_XMIT_A112                              (0x1d0)
// Bit 11  :0      rg_hc_thr_mcs0                 U     RW        default = 'h0
// Bit 23  :12     rg_hc_thr_mcs1                 U     RW        default = 'h0
// Bit 24          rg_hc_bypass_11n               U     RW        default = 'h1
// Bit 28          rg_hc_dly_bypass_11n           U     RW        default = 'h1
typedef union RG_XMIT_A112_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_hc_thr_mcs0 : 12;
    unsigned int rg_hc_thr_mcs1 : 12;
    unsigned int rg_hc_bypass_11n : 1;
    unsigned int rsvd_0 : 3;
    unsigned int rg_hc_dly_bypass_11n : 1;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A112_FIELD_T;

#define RG_XMIT_A113                              (0x1d4)
// Bit 11  :0      rg_hc_thr_mcs2                 U     RW        default = 'h0
// Bit 23  :12     rg_hc_thr_mcs3                 U     RW        default = 'h0
// Bit 24          rg_hc_bypass_11b               U     RW        default = 'h1
// Bit 28          rg_hc_dly_bypass_11b           U     RW        default = 'h1
typedef union RG_XMIT_A113_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_hc_thr_mcs2 : 12;
    unsigned int rg_hc_thr_mcs3 : 12;
    unsigned int rg_hc_bypass_11b : 1;
    unsigned int rsvd_0 : 3;
    unsigned int rg_hc_dly_bypass_11b : 1;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A113_FIELD_T;

#define RG_XMIT_A114                              (0x1d8)
// Bit 11  :0      rg_hc_thr_mcs4                 U     RW        default = 'h0
// Bit 23  :12     rg_hc_thr_mcs5                 U     RW        default = 'h0
typedef union RG_XMIT_A114_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_hc_thr_mcs4 : 12;
    unsigned int rg_hc_thr_mcs5 : 12;
    unsigned int rsvd_0 : 8;
  } b;
} RG_XMIT_A114_FIELD_T;

#define RG_XMIT_A115                              (0x1dc)
// Bit 11  :0      rg_hc_thr_mcs6                 U     RW        default = 'h0
// Bit 23  :12     rg_hc_thr_mcs7                 U     RW        default = 'h0
typedef union RG_XMIT_A115_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_hc_thr_mcs6 : 12;
    unsigned int rg_hc_thr_mcs7 : 12;
    unsigned int rsvd_0 : 8;
  } b;
} RG_XMIT_A115_FIELD_T;

#define RG_XMIT_A116                              (0x1e0)
// Bit 11  :0      rg_hc_thr_mcs8                 U     RW        default = 'h0
// Bit 23  :12     rg_hc_thr_mcs9                 U     RW        default = 'h0
typedef union RG_XMIT_A116_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_hc_thr_mcs8 : 12;
    unsigned int rg_hc_thr_mcs9 : 12;
    unsigned int rsvd_0 : 8;
  } b;
} RG_XMIT_A116_FIELD_T;

#define RG_XMIT_A117                              (0x1e4)
// Bit 11  :0      rg_hc_thr_mcs10                U     RW        default = 'h0
// Bit 23  :12     rg_hc_thr_mcs11                U     RW        default = 'h0
typedef union RG_XMIT_A117_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_hc_thr_mcs10 : 12;
    unsigned int rg_hc_thr_mcs11 : 12;
    unsigned int rsvd_0 : 8;
  } b;
} RG_XMIT_A117_FIELD_T;

#define RG_XMIT_A118                              (0x1e8)
// Bit 11  :0      rg_hc_thr_mcs_man              U     RW        default = 'h0
// Bit 12          rg_hc_thr_mcs_man_mode         U     RW        default = 'h0
// Bit 16          rg_hc_bypass_man               U     RW        default = 'h1
// Bit 17          rg_hc_bypass_man_mode          U     RW        default = 'h0
// Bit 18          rg_hc_dly_bypass_man           U     RW        default = 'h1
// Bit 19          rg_hc_dly_bypass_man_mode      U     RW        default = 'h0
typedef union RG_XMIT_A118_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_hc_thr_mcs_man : 12;
    unsigned int rg_hc_thr_mcs_man_mode : 1;
    unsigned int rsvd_0 : 3;
    unsigned int rg_hc_bypass_man : 1;
    unsigned int rg_hc_bypass_man_mode : 1;
    unsigned int rg_hc_dly_bypass_man : 1;
    unsigned int rg_hc_dly_bypass_man_mode : 1;
    unsigned int rsvd_1 : 12;
  } b;
} RG_XMIT_A118_FIELD_T;

#define RG_XMIT_A119                              (0x1ec)
// Bit 0           rg_tx_80m_ddc_bypass           U     RW        default = 'h0
// Bit 9   :8      rg_tx_ch_bw                    U     RW        default = 'h0
// Bit 12          rg_tx_ch_bw_man_mode           U     RW        default = 'h0
// Bit 16          rg_tx_bn_sel                   U     RW        default = 'h0
// Bit 20          rg_tx_bn_sel_man_mode          U     RW        default = 'h0
// Bit 25  :24     rg_tx_coeff_width_11b          U     RW        default = 'h0
// Bit 27  :26     rg_tx_coeff_width_20m          U     RW        default = 'h0
// Bit 29  :28     rg_tx_coeff_width_40m          U     RW        default = 'h0
// Bit 31  :30     rg_tx_coeff_width_80m          U     RW        default = 'h2
typedef union RG_XMIT_A119_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_80m_ddc_bypass : 1;
    unsigned int rsvd_0 : 7;
    unsigned int rg_tx_ch_bw : 2;
    unsigned int rsvd_1 : 2;
    unsigned int rg_tx_ch_bw_man_mode : 1;
    unsigned int rsvd_2 : 3;
    unsigned int rg_tx_bn_sel : 1;
    unsigned int rsvd_3 : 3;
    unsigned int rg_tx_bn_sel_man_mode : 1;
    unsigned int rsvd_4 : 3;
    unsigned int rg_tx_coeff_width_11b : 2;
    unsigned int rg_tx_coeff_width_20m : 2;
    unsigned int rg_tx_coeff_width_40m : 2;
    unsigned int rg_tx_coeff_width_80m : 2;
  } b;
} RG_XMIT_A119_FIELD_T;

#define RG_XMIT_A120                              (0x1f0)
// Bit 11  :0      rg_tx_coeff_11b_0              U     RW        default = 'hfa3
// Bit 27  :16     rg_tx_coeff_11b_1              U     RW        default = 'hf8c
typedef union RG_XMIT_A120_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_11b_0 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_11b_1 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A120_FIELD_T;

#define RG_XMIT_A121                              (0x1f4)
// Bit 11  :0      rg_tx_coeff_11b_2              U     RW        default = 'hf7c
// Bit 27  :16     rg_tx_coeff_11b_3              U     RW        default = 'hf76
typedef union RG_XMIT_A121_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_11b_2 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_11b_3 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A121_FIELD_T;

#define RG_XMIT_A122                              (0x1f8)
// Bit 11  :0      rg_tx_coeff_11b_4              U     RW        default = 'hf7b
// Bit 27  :16     rg_tx_coeff_11b_5              U     RW        default = 'hf8b
typedef union RG_XMIT_A122_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_11b_4 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_11b_5 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A122_FIELD_T;

#define RG_XMIT_A123                              (0x1fc)
// Bit 11  :0      rg_tx_coeff_11b_6              U     RW        default = 'hfa7
// Bit 27  :16     rg_tx_coeff_11b_7              U     RW        default = 'hfce
typedef union RG_XMIT_A123_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_11b_6 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_11b_7 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A123_FIELD_T;

#define RG_XMIT_A124                              (0x200)
// Bit 11  :0      rg_tx_coeff_11b_8              U     RW        default = 'h1
// Bit 27  :16     rg_tx_coeff_11b_9              U     RW        default = 'h3d
typedef union RG_XMIT_A124_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_11b_8 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_11b_9 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A124_FIELD_T;

#define RG_XMIT_A125                              (0x204)
// Bit 11  :0      rg_tx_coeff_11b_10             U     RW        default = 'h81
// Bit 27  :16     rg_tx_coeff_11b_11             U     RW        default = 'hca
typedef union RG_XMIT_A125_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_11b_10 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_11b_11 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A125_FIELD_T;

#define RG_XMIT_A126                              (0x208)
// Bit 11  :0      rg_tx_coeff_11b_12             U     RW        default = 'h117
// Bit 27  :16     rg_tx_coeff_11b_13             U     RW        default = 'h163
typedef union RG_XMIT_A126_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_11b_12 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_11b_13 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A126_FIELD_T;

#define RG_XMIT_A127                              (0x20c)
// Bit 11  :0      rg_tx_coeff_11b_14             U     RW        default = 'h1ae
// Bit 27  :16     rg_tx_coeff_11b_15             U     RW        default = 'h1f2
typedef union RG_XMIT_A127_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_11b_14 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_11b_15 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A127_FIELD_T;

#define RG_XMIT_A128                              (0x210)
// Bit 11  :0      rg_tx_coeff_11b_16             U     RW        default = 'h22f
// Bit 27  :16     rg_tx_coeff_11b_17             U     RW        default = 'h261
typedef union RG_XMIT_A128_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_11b_16 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_11b_17 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A128_FIELD_T;

#define RG_XMIT_A129                              (0x214)
// Bit 11  :0      rg_tx_coeff_11b_18             U     RW        default = 'h286
// Bit 27  :16     rg_tx_coeff_11b_19             U     RW        default = 'h29d
typedef union RG_XMIT_A129_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_11b_18 : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_tx_coeff_11b_19 : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A129_FIELD_T;

#define RG_XMIT_A130                              (0x218)
// Bit 11  :0      rg_tx_coeff_11b_20             U     RW        default = 'h2a4
typedef union RG_XMIT_A130_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_coeff_11b_20 : 12;
    unsigned int rsvd_0 : 20;
  } b;
} RG_XMIT_A130_FIELD_T;

#define RG_XMIT_A132                              (0x220)
// Bit 11  :0      rg_txdpd_comp_coef_i_15_man     U     RW        default = 'h0
// Bit 27  :16     rg_txdpd_comp_coef_q_15_man     U     RW        default = 'h0
typedef union RG_XMIT_A132_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_15_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_15_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A132_FIELD_T;

#define RG_XMIT_A133                              (0x224)
// Bit 11  :0      rg_txdpd_comp_coef_i_16_man     U     RW        default = 'h17
// Bit 27  :16     rg_txdpd_comp_coef_q_16_man     U     RW        default = 'ha3
typedef union RG_XMIT_A133_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_16_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_16_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A133_FIELD_T;

#define RG_XMIT_A134                              (0x228)
// Bit 11  :0      rg_txdpd_comp_coef_i_17_man     U     RW        default = 'hffc
// Bit 27  :16     rg_txdpd_comp_coef_q_17_man     U     RW        default = 'h16
typedef union RG_XMIT_A134_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_17_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_17_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A134_FIELD_T;

#define RG_XMIT_A135                              (0x22c)
// Bit 11  :0      rg_txdpd_comp_coef_i_18_man     U     RW        default = 'hfff
// Bit 27  :16     rg_txdpd_comp_coef_q_18_man     U     RW        default = 'h5
typedef union RG_XMIT_A135_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_18_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_18_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A135_FIELD_T;

#define RG_XMIT_A136                              (0x230)
// Bit 11  :0      rg_txdpd_comp_coef_i_19_man     U     RW        default = 'h0
// Bit 27  :16     rg_txdpd_comp_coef_q_19_man     U     RW        default = 'h0
typedef union RG_XMIT_A136_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_19_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_19_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A136_FIELD_T;

#define RG_XMIT_A145                              (0x254)
// Bit 1   :0      rg_tone_single_path_sel        U     RW        default = 'h0
typedef union RG_XMIT_A145_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tone_single_path_sel : 2;
    unsigned int rsvd_0 : 30;
  } b;
} RG_XMIT_A145_FIELD_T;

#define RG_XMIT_A146                              (0x258)
// Bit 9   :0      rg_customer_offset_db          U     RW        default = 'h0
// Bit 24  :12     rg_loop_gain                   U     RW        default = 'h0
typedef union RG_XMIT_A146_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_customer_offset_db : 10;
    unsigned int rsvd_0 : 2;
    unsigned int rg_loop_gain : 13;
    unsigned int rsvd_1 : 7;
  } b;
} RG_XMIT_A146_FIELD_T;

#define RG_XMIT_A147                              (0x25c)
// Bit 0           rg_en_cal_table_man_mode       U     RW        default = 'h0
// Bit 4           rg_en_cal_table_man            U     RW        default = 'h0
// Bit 8           rg_en_man_gain_mode            U     RW        default = 'h0
// Bit 19  :12     rg_dig_gain_man                U     RW        default = 'h0
// Bit 22  :20     rg_slice_man                   U     RW        default = 'h0
typedef union RG_XMIT_A147_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_en_cal_table_man_mode : 1;
    unsigned int rsvd_0 : 3;
    unsigned int rg_en_cal_table_man : 1;
    unsigned int rsvd_1 : 3;
    unsigned int rg_en_man_gain_mode : 1;
    unsigned int rsvd_2 : 3;
    unsigned int rg_dig_gain_man : 8;
    unsigned int rg_slice_man : 3;
    unsigned int rsvd_3 : 9;
  } b;
} RG_XMIT_A147_FIELD_T;

#define RG_XMIT_A148                              (0x260)
// Bit 7   :0      rg_olpc_dig_gain_0             U     RW        default = 'h0
// Bit 15  :8      rg_olpc_dig_gain_1             U     RW        default = 'h0
// Bit 23  :16     rg_olpc_dig_gain_2             U     RW        default = 'h0
// Bit 31  :24     rg_olpc_dig_gain_3             U     RW        default = 'h0
typedef union RG_XMIT_A148_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_dig_gain_0 : 8;
    unsigned int rg_olpc_dig_gain_1 : 8;
    unsigned int rg_olpc_dig_gain_2 : 8;
    unsigned int rg_olpc_dig_gain_3 : 8;
  } b;
} RG_XMIT_A148_FIELD_T;

#define RG_XMIT_A149                              (0x264)
// Bit 7   :0      rg_olpc_dig_gain_4             U     RW        default = 'h0
// Bit 15  :8      rg_olpc_dig_gain_5             U     RW        default = 'h0
// Bit 23  :16     rg_olpc_dig_gain_6             U     RW        default = 'h0
// Bit 31  :24     rg_olpc_dig_gain_7             U     RW        default = 'h0
typedef union RG_XMIT_A149_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_dig_gain_4 : 8;
    unsigned int rg_olpc_dig_gain_5 : 8;
    unsigned int rg_olpc_dig_gain_6 : 8;
    unsigned int rg_olpc_dig_gain_7 : 8;
  } b;
} RG_XMIT_A149_FIELD_T;

#define RG_XMIT_A150                              (0x268)
// Bit 7   :0      rg_olpc_dig_gain_8             U     RW        default = 'h0
// Bit 15  :8      rg_olpc_dig_gain_9             U     RW        default = 'h0
// Bit 23  :16     rg_olpc_dig_gain_10            U     RW        default = 'h0
// Bit 31  :24     rg_olpc_dig_gain_11            U     RW        default = 'h0
typedef union RG_XMIT_A150_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_dig_gain_8 : 8;
    unsigned int rg_olpc_dig_gain_9 : 8;
    unsigned int rg_olpc_dig_gain_10 : 8;
    unsigned int rg_olpc_dig_gain_11 : 8;
  } b;
} RG_XMIT_A150_FIELD_T;

#define RG_XMIT_A151                              (0x26c)
// Bit 7   :0      rg_olpc_dig_gain_12            U     RW        default = 'h0
// Bit 15  :8      rg_olpc_dig_gain_13            U     RW        default = 'h0
// Bit 23  :16     rg_olpc_dig_gain_14            U     RW        default = 'h0
// Bit 31  :24     rg_olpc_dig_gain_15            U     RW        default = 'h0
typedef union RG_XMIT_A151_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_dig_gain_12 : 8;
    unsigned int rg_olpc_dig_gain_13 : 8;
    unsigned int rg_olpc_dig_gain_14 : 8;
    unsigned int rg_olpc_dig_gain_15 : 8;
  } b;
} RG_XMIT_A151_FIELD_T;

#define RG_XMIT_A152                              (0x270)
// Bit 7   :0      rg_olpc_dig_gain_16            U     RW        default = 'h0
// Bit 15  :8      rg_olpc_dig_gain_17            U     RW        default = 'h0
// Bit 23  :16     rg_olpc_dig_gain_18            U     RW        default = 'h0
// Bit 31  :24     rg_olpc_dig_gain_19            U     RW        default = 'h0
typedef union RG_XMIT_A152_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_dig_gain_16 : 8;
    unsigned int rg_olpc_dig_gain_17 : 8;
    unsigned int rg_olpc_dig_gain_18 : 8;
    unsigned int rg_olpc_dig_gain_19 : 8;
  } b;
} RG_XMIT_A152_FIELD_T;

#define RG_XMIT_A153                              (0x274)
// Bit 7   :0      rg_olpc_dig_gain_20            U     RW        default = 'h0
// Bit 15  :8      rg_olpc_dig_gain_21            U     RW        default = 'h0
// Bit 23  :16     rg_olpc_dig_gain_22            U     RW        default = 'h0
// Bit 31  :24     rg_olpc_dig_gain_23            U     RW        default = 'h0
typedef union RG_XMIT_A153_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_dig_gain_20 : 8;
    unsigned int rg_olpc_dig_gain_21 : 8;
    unsigned int rg_olpc_dig_gain_22 : 8;
    unsigned int rg_olpc_dig_gain_23 : 8;
  } b;
} RG_XMIT_A153_FIELD_T;

#define RG_XMIT_A154                              (0x278)
// Bit 7   :0      rg_olpc_dig_gain_24            U     RW        default = 'h0
// Bit 15  :8      rg_olpc_dig_gain_25            U     RW        default = 'h0
// Bit 23  :16     rg_olpc_dig_gain_26            U     RW        default = 'h0
// Bit 31  :24     rg_olpc_dig_gain_27            U     RW        default = 'h0
typedef union RG_XMIT_A154_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_dig_gain_24 : 8;
    unsigned int rg_olpc_dig_gain_25 : 8;
    unsigned int rg_olpc_dig_gain_26 : 8;
    unsigned int rg_olpc_dig_gain_27 : 8;
  } b;
} RG_XMIT_A154_FIELD_T;

#define RG_XMIT_A155                              (0x27c)
// Bit 7   :0      rg_olpc_dig_gain_28            U     RW        default = 'h0
// Bit 15  :8      rg_olpc_dig_gain_29            U     RW        default = 'h0
typedef union RG_XMIT_A155_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_dig_gain_28 : 8;
    unsigned int rg_olpc_dig_gain_29 : 8;
    unsigned int rsvd_0 : 16;
  } b;
} RG_XMIT_A155_FIELD_T;

#define RG_XMIT_A156                              (0x280)
// Bit 2   :0      rg_olpc_slice_0                U     RW        default = 'h0
// Bit 5   :3      rg_olpc_slice_1                U     RW        default = 'h0
// Bit 8   :6      rg_olpc_slice_2                U     RW        default = 'h0
// Bit 11  :9      rg_olpc_slice_3                U     RW        default = 'h0
// Bit 14  :12     rg_olpc_slice_4                U     RW        default = 'h0
// Bit 17  :15     rg_olpc_slice_5                U     RW        default = 'h0
// Bit 20  :18     rg_olpc_slice_6                U     RW        default = 'h0
// Bit 23  :21     rg_olpc_slice_7                U     RW        default = 'h0
// Bit 26  :24     rg_olpc_slice_8                U     RW        default = 'h0
// Bit 29  :27     rg_olpc_slice_9                U     RW        default = 'h0
typedef union RG_XMIT_A156_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_slice_0 : 3;
    unsigned int rg_olpc_slice_1 : 3;
    unsigned int rg_olpc_slice_2 : 3;
    unsigned int rg_olpc_slice_3 : 3;
    unsigned int rg_olpc_slice_4 : 3;
    unsigned int rg_olpc_slice_5 : 3;
    unsigned int rg_olpc_slice_6 : 3;
    unsigned int rg_olpc_slice_7 : 3;
    unsigned int rg_olpc_slice_8 : 3;
    unsigned int rg_olpc_slice_9 : 3;
    unsigned int rsvd_0 : 2;
  } b;
} RG_XMIT_A156_FIELD_T;

#define RG_XMIT_A157                              (0x284)
// Bit 2   :0      rg_olpc_slice_10               U     RW        default = 'h0
// Bit 5   :3      rg_olpc_slice_11               U     RW        default = 'h0
// Bit 8   :6      rg_olpc_slice_12               U     RW        default = 'h0
// Bit 11  :9      rg_olpc_slice_13               U     RW        default = 'h0
// Bit 14  :12     rg_olpc_slice_14               U     RW        default = 'h0
// Bit 17  :15     rg_olpc_slice_15               U     RW        default = 'h0
// Bit 20  :18     rg_olpc_slice_16               U     RW        default = 'h0
// Bit 23  :21     rg_olpc_slice_17               U     RW        default = 'h0
// Bit 26  :24     rg_olpc_slice_18               U     RW        default = 'h0
// Bit 29  :27     rg_olpc_slice_19               U     RW        default = 'h0
typedef union RG_XMIT_A157_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_slice_10 : 3;
    unsigned int rg_olpc_slice_11 : 3;
    unsigned int rg_olpc_slice_12 : 3;
    unsigned int rg_olpc_slice_13 : 3;
    unsigned int rg_olpc_slice_14 : 3;
    unsigned int rg_olpc_slice_15 : 3;
    unsigned int rg_olpc_slice_16 : 3;
    unsigned int rg_olpc_slice_17 : 3;
    unsigned int rg_olpc_slice_18 : 3;
    unsigned int rg_olpc_slice_19 : 3;
    unsigned int rsvd_0 : 2;
  } b;
} RG_XMIT_A157_FIELD_T;

#define RG_XMIT_A158                              (0x288)
// Bit 2   :0      rg_olpc_slice_20               U     RW        default = 'h0
// Bit 5   :3      rg_olpc_slice_21               U     RW        default = 'h0
// Bit 8   :6      rg_olpc_slice_22               U     RW        default = 'h0
// Bit 11  :9      rg_olpc_slice_23               U     RW        default = 'h0
// Bit 14  :12     rg_olpc_slice_24               U     RW        default = 'h0
// Bit 17  :15     rg_olpc_slice_25               U     RW        default = 'h0
// Bit 20  :18     rg_olpc_slice_26               U     RW        default = 'h0
// Bit 23  :21     rg_olpc_slice_27               U     RW        default = 'h0
// Bit 26  :24     rg_olpc_slice_28               U     RW        default = 'h0
// Bit 29  :27     rg_olpc_slice_29               U     RW        default = 'h0
typedef union RG_XMIT_A158_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_slice_20 : 3;
    unsigned int rg_olpc_slice_21 : 3;
    unsigned int rg_olpc_slice_22 : 3;
    unsigned int rg_olpc_slice_23 : 3;
    unsigned int rg_olpc_slice_24 : 3;
    unsigned int rg_olpc_slice_25 : 3;
    unsigned int rg_olpc_slice_26 : 3;
    unsigned int rg_olpc_slice_27 : 3;
    unsigned int rg_olpc_slice_28 : 3;
    unsigned int rg_olpc_slice_29 : 3;
    unsigned int rsvd_0 : 2;
  } b;
} RG_XMIT_A158_FIELD_T;

#define RG_XMIT_A159                              (0x28c)
// Bit 0           rg_tx_olpc_lut_enable          U     RW        default = 'h0
typedef union RG_XMIT_A159_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_olpc_lut_enable : 1;
    unsigned int rsvd_0 : 31;
  } b;
} RG_XMIT_A159_FIELD_T;

#define RG_XMIT_A163                              (0x29c)
// Bit 12  :0      ro_olpc_lut_pow_0              U     RO        default = 'h0
// Bit 28  :16     ro_olpc_lut_pow_1              U     RO        default = 'h0
typedef union RG_XMIT_A163_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_olpc_lut_pow_0 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int ro_olpc_lut_pow_1 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A163_FIELD_T;

#define RG_XMIT_A164                              (0x2a0)
// Bit 12  :0      ro_olpc_lut_pow_2              U     RO        default = 'h0
// Bit 28  :16     ro_olpc_lut_pow_3              U     RO        default = 'h0
typedef union RG_XMIT_A164_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_olpc_lut_pow_2 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int ro_olpc_lut_pow_3 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A164_FIELD_T;

#define RG_XMIT_A165                              (0x2a4)
// Bit 12  :0      ro_olpc_lut_pow_4              U     RO        default = 'h0
// Bit 28  :16     ro_olpc_lut_pow_5              U     RO        default = 'h0
typedef union RG_XMIT_A165_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_olpc_lut_pow_4 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int ro_olpc_lut_pow_5 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A165_FIELD_T;

#define RG_XMIT_A166                              (0x2a8)
// Bit 12  :0      ro_olpc_lut_pow_6              U     RO        default = 'h0
// Bit 28  :16     ro_olpc_lut_pow_7              U     RO        default = 'h0
typedef union RG_XMIT_A166_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_olpc_lut_pow_6 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int ro_olpc_lut_pow_7 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A166_FIELD_T;

#define RG_XMIT_A167                              (0x2ac)
// Bit 12  :0      ro_olpc_lut_pow_8              U     RO        default = 'h0
// Bit 28  :16     ro_olpc_lut_pow_9              U     RO        default = 'h0
typedef union RG_XMIT_A167_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_olpc_lut_pow_8 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int ro_olpc_lut_pow_9 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A167_FIELD_T;

#define RG_XMIT_A168                              (0x2b0)
// Bit 12  :0      ro_olpc_lut_pow_10             U     RO        default = 'h0
// Bit 28  :16     ro_olpc_lut_pow_11             U     RO        default = 'h0
typedef union RG_XMIT_A168_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_olpc_lut_pow_10 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int ro_olpc_lut_pow_11 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A168_FIELD_T;

#define RG_XMIT_A169                              (0x2b4)
// Bit 12  :0      ro_olpc_lut_pow_12             U     RO        default = 'h0
// Bit 28  :16     ro_olpc_lut_pow_13             U     RO        default = 'h0
typedef union RG_XMIT_A169_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_olpc_lut_pow_12 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int ro_olpc_lut_pow_13 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A169_FIELD_T;

#define RG_XMIT_A170                              (0x2b8)
// Bit 12  :0      ro_olpc_lut_pow_14             U     RO        default = 'h0
// Bit 28  :16     ro_olpc_lut_pow_15             U     RO        default = 'h0
typedef union RG_XMIT_A170_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_olpc_lut_pow_14 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int ro_olpc_lut_pow_15 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A170_FIELD_T;

#define RG_XMIT_A171                              (0x2bc)
// Bit 12  :0      ro_olpc_lut_pow_16             U     RO        default = 'h0
// Bit 28  :16     ro_olpc_lut_pow_17             U     RO        default = 'h0
typedef union RG_XMIT_A171_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_olpc_lut_pow_16 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int ro_olpc_lut_pow_17 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A171_FIELD_T;

#define RG_XMIT_A172                              (0x2c0)
// Bit 12  :0      ro_olpc_lut_pow_18             U     RO        default = 'h0
// Bit 28  :16     ro_olpc_lut_pow_19             U     RO        default = 'h0
typedef union RG_XMIT_A172_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_olpc_lut_pow_18 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int ro_olpc_lut_pow_19 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A172_FIELD_T;

#define RG_XMIT_A173                              (0x2c4)
// Bit 12  :0      ro_olpc_lut_pow_20             U     RO        default = 'h0
// Bit 28  :16     ro_olpc_lut_pow_21             U     RO        default = 'h0
typedef union RG_XMIT_A173_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_olpc_lut_pow_20 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int ro_olpc_lut_pow_21 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A173_FIELD_T;

#define RG_XMIT_A174                              (0x2c8)
// Bit 12  :0      ro_olpc_lut_pow_22             U     RO        default = 'h0
// Bit 28  :16     ro_olpc_lut_pow_23             U     RO        default = 'h0
typedef union RG_XMIT_A174_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_olpc_lut_pow_22 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int ro_olpc_lut_pow_23 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A174_FIELD_T;

#define RG_XMIT_A175                              (0x2cc)
// Bit 12  :0      ro_olpc_lut_pow_24             U     RO        default = 'h0
// Bit 28  :16     ro_olpc_lut_pow_25             U     RO        default = 'h0
typedef union RG_XMIT_A175_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_olpc_lut_pow_24 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int ro_olpc_lut_pow_25 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A175_FIELD_T;

#define RG_XMIT_A176                              (0x2d0)
// Bit 12  :0      ro_olpc_lut_pow_26             U     RO        default = 'h0
// Bit 28  :16     ro_olpc_lut_pow_27             U     RO        default = 'h0
typedef union RG_XMIT_A176_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_olpc_lut_pow_26 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int ro_olpc_lut_pow_27 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A176_FIELD_T;

#define RG_XMIT_A177                              (0x2d4)
// Bit 12  :0      ro_olpc_lut_pow_28             U     RO        default = 'h0
// Bit 28  :16     ro_olpc_lut_pow_29             U     RO        default = 'h0
typedef union RG_XMIT_A177_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_olpc_lut_pow_28 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int ro_olpc_lut_pow_29 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A177_FIELD_T;

#define RG_XMIT_A178                              (0x2d8)
// Bit 0           ro_olpc_lut_pow_ready          U     RO        default = 'h0
typedef union RG_XMIT_A178_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_olpc_lut_pow_ready : 1;
    unsigned int rsvd_0 : 31;
  } b;
} RG_XMIT_A178_FIELD_T;

#define RG_XMIT_A179                              (0x2dc)
// Bit 7   :0      ro_gain_used                   U     RO        default = 'h0
// Bit 10  :8      ro_slice_used                  U     RO        default = 'h0
typedef union RG_XMIT_A179_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_gain_used : 8;
    unsigned int ro_slice_used : 3;
    unsigned int rsvd_0 : 21;
  } b;
} RG_XMIT_A179_FIELD_T;

#define RG_XMIT_A180                              (0x2e0)
// Bit 24  :0      rg_tg160_1_f_sel               U     RW        default = 'h100000
// Bit 28  :25     rg_tg160_1_tone_gain           U     RW        default = 'h4
// Bit 29          rg_tg160_1_enable              U     RW        default = 'h0
// Bit 30          rg_tg160_1_tone_40             U     RW        default = 'h0
typedef union RG_XMIT_A180_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tg160_1_f_sel : 25;
    unsigned int rg_tg160_1_tone_gain : 4;
    unsigned int rg_tg160_1_enable : 1;
    unsigned int rg_tg160_1_tone_40 : 1;
    unsigned int rsvd_0 : 1;
  } b;
} RG_XMIT_A180_FIELD_T;

#define RG_XMIT_A181                              (0x2e4)
// Bit 24  :0      rg_tg160_2_f_sel               U     RW        default = 'h100000
// Bit 28  :25     rg_tg160_2_tone_gain           U     RW        default = 'h4
// Bit 29          rg_tg160_2_enable              U     RW        default = 'h0
// Bit 30          rg_tg160_2_tone_40             U     RW        default = 'h0
typedef union RG_XMIT_A181_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tg160_2_f_sel : 25;
    unsigned int rg_tg160_2_tone_gain : 4;
    unsigned int rg_tg160_2_enable : 1;
    unsigned int rg_tg160_2_tone_40 : 1;
    unsigned int rsvd_0 : 1;
  } b;
} RG_XMIT_A181_FIELD_T;

#define RG_XMIT_A182                              (0x2e8)
// Bit 9   :0      rg_cf_cw2mod_11b               U     RW        default = 'h0
// Bit 21  :12     rg_cf_cw2mod_11n               U     RW        default = 'h0
typedef union RG_XMIT_A182_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_cf_cw2mod_11b : 10;
    unsigned int rsvd_0 : 2;
    unsigned int rg_cf_cw2mod_11n : 10;
    unsigned int rsvd_1 : 10;
  } b;
} RG_XMIT_A182_FIELD_T;

#define RG_XMIT_A183                              (0x2ec)
// Bit 15  :0      rg_xmit_soft_rst_ctrl          U     RW        default = 'h0
typedef union RG_XMIT_A183_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_xmit_soft_rst_ctrl : 16;
    unsigned int rsvd_0 : 16;
  } b;
} RG_XMIT_A183_FIELD_T;

#define RG_XMIT_A184                              (0x2f0)
// Bit 12  :0      rg_olpc_lut_pow_0              U     RW        default = 'h0
// Bit 28  :16     rg_olpc_lut_pow_1              U     RW        default = 'h0
typedef union RG_XMIT_A184_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_lut_pow_0 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int rg_olpc_lut_pow_1 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A184_FIELD_T;

#define RG_XMIT_A185                              (0x2f4)
// Bit 12  :0      rg_olpc_lut_pow_2              U     RW        default = 'h0
// Bit 28  :16     rg_olpc_lut_pow_3              U     RW        default = 'h0
typedef union RG_XMIT_A185_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_lut_pow_2 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int rg_olpc_lut_pow_3 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A185_FIELD_T;

#define RG_XMIT_A186                              (0x2f8)
// Bit 12  :0      rg_olpc_lut_pow_4              U     RW        default = 'h0
// Bit 28  :16     rg_olpc_lut_pow_5              U     RW        default = 'h0
typedef union RG_XMIT_A186_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_lut_pow_4 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int rg_olpc_lut_pow_5 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A186_FIELD_T;

#define RG_XMIT_A187                              (0x2fc)
// Bit 12  :0      rg_olpc_lut_pow_6              U     RW        default = 'h0
// Bit 28  :16     rg_olpc_lut_pow_7              U     RW        default = 'h0
typedef union RG_XMIT_A187_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_lut_pow_6 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int rg_olpc_lut_pow_7 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A187_FIELD_T;

#define RG_XMIT_A188                              (0x300)
// Bit 12  :0      rg_olpc_lut_pow_8              U     RW        default = 'h0
// Bit 28  :16     rg_olpc_lut_pow_9              U     RW        default = 'h0
typedef union RG_XMIT_A188_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_lut_pow_8 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int rg_olpc_lut_pow_9 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A188_FIELD_T;

#define RG_XMIT_A189                              (0x304)
// Bit 12  :0      rg_olpc_lut_pow_10             U     RW        default = 'h0
// Bit 28  :16     rg_olpc_lut_pow_11             U     RW        default = 'h0
typedef union RG_XMIT_A189_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_lut_pow_10 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int rg_olpc_lut_pow_11 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A189_FIELD_T;

#define RG_XMIT_A190                              (0x308)
// Bit 12  :0      rg_olpc_lut_pow_12             U     RW        default = 'h0
// Bit 28  :16     rg_olpc_lut_pow_13             U     RW        default = 'h0
typedef union RG_XMIT_A190_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_lut_pow_12 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int rg_olpc_lut_pow_13 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A190_FIELD_T;

#define RG_XMIT_A191                              (0x30c)
// Bit 12  :0      rg_olpc_lut_pow_14             U     RW        default = 'h0
// Bit 28  :16     rg_olpc_lut_pow_15             U     RW        default = 'h0
typedef union RG_XMIT_A191_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_lut_pow_14 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int rg_olpc_lut_pow_15 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A191_FIELD_T;

#define RG_XMIT_A192                              (0x310)
// Bit 12  :0      rg_olpc_lut_pow_16             U     RW        default = 'h0
// Bit 28  :16     rg_olpc_lut_pow_17             U     RW        default = 'h0
typedef union RG_XMIT_A192_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_lut_pow_16 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int rg_olpc_lut_pow_17 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A192_FIELD_T;

#define RG_XMIT_A193                              (0x314)
// Bit 12  :0      rg_olpc_lut_pow_18             U     RW        default = 'h0
// Bit 28  :16     rg_olpc_lut_pow_19             U     RW        default = 'h0
typedef union RG_XMIT_A193_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_lut_pow_18 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int rg_olpc_lut_pow_19 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A193_FIELD_T;

#define RG_XMIT_A194                              (0x318)
// Bit 12  :0      rg_olpc_lut_pow_20             U     RW        default = 'h0
// Bit 28  :16     rg_olpc_lut_pow_21             U     RW        default = 'h0
typedef union RG_XMIT_A194_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_lut_pow_20 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int rg_olpc_lut_pow_21 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A194_FIELD_T;

#define RG_XMIT_A195                              (0x31c)
// Bit 12  :0      rg_olpc_lut_pow_22             U     RW        default = 'h0
// Bit 28  :16     rg_olpc_lut_pow_23             U     RW        default = 'h0
typedef union RG_XMIT_A195_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_lut_pow_22 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int rg_olpc_lut_pow_23 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A195_FIELD_T;

#define RG_XMIT_A196                              (0x320)
// Bit 12  :0      rg_olpc_lut_pow_24             U     RW        default = 'h0
// Bit 28  :16     rg_olpc_lut_pow_25             U     RW        default = 'h0
typedef union RG_XMIT_A196_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_lut_pow_24 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int rg_olpc_lut_pow_25 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A196_FIELD_T;

#define RG_XMIT_A197                              (0x324)
// Bit 12  :0      rg_olpc_lut_pow_26             U     RW        default = 'h0
// Bit 28  :16     rg_olpc_lut_pow_27             U     RW        default = 'h0
typedef union RG_XMIT_A197_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_lut_pow_26 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int rg_olpc_lut_pow_27 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A197_FIELD_T;

#define RG_XMIT_A198                              (0x328)
// Bit 12  :0      rg_olpc_lut_pow_28             U     RW        default = 'h0
// Bit 28  :16     rg_olpc_lut_pow_29             U     RW        default = 'h0
typedef union RG_XMIT_A198_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_olpc_lut_pow_28 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int rg_olpc_lut_pow_29 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A198_FIELD_T;

#define RG_XMIT_A199                              (0x32c)
// Bit 0           rg_tx_increase_wave_en         U     RW        default = 'h0
// Bit 9   :4      rg_tx_increase_wave_length     U     RW        default = 'h0
// Bit 12          rg_tx_increase_wave_mux        U     RW        default = 'h0
typedef union RG_XMIT_A199_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_increase_wave_en : 1;
    unsigned int rsvd_0 : 3;
    unsigned int rg_tx_increase_wave_length : 6;
    unsigned int rsvd_1 : 2;
    unsigned int rg_tx_increase_wave_mux : 1;
    unsigned int rsvd_2 : 19;
  } b;
} RG_XMIT_A199_FIELD_T;

#define RG_XMIT_A200                              (0x330)
// Bit 0           rg_dpd_mcs_man_mode            U     RW        default = 'h0
// Bit 7   :4      rg_dpd_mcs_man                 U     RW        default = 'h0
// Bit 8           rg_use_dpd_bypass_mcs0         U     RW        default = 'h0
// Bit 9           rg_use_dpd_bypass_mcs1         U     RW        default = 'h0
// Bit 10          rg_use_dpd_bypass_mcs2         U     RW        default = 'h0
// Bit 11          rg_use_dpd_bypass_mcs3         U     RW        default = 'h0
// Bit 12          rg_use_dpd_bypass_mcs4         U     RW        default = 'h0
// Bit 13          rg_use_dpd_bypass_mcs5         U     RW        default = 'h0
// Bit 14          rg_use_dpd_bypass_mcs6         U     RW        default = 'h0
// Bit 15          rg_use_dpd_bypass_mcs7         U     RW        default = 'h0
// Bit 16          rg_use_dpd_bypass_mcs8         U     RW        default = 'h0
// Bit 17          rg_use_dpd_bypass_mcs9         U     RW        default = 'h0
// Bit 18          rg_use_dpd_bypass_mcsa         U     RW        default = 'h0
// Bit 19          rg_use_dpd_bypass_mcsb         U     RW        default = 'h0
typedef union RG_XMIT_A200_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_dpd_mcs_man_mode : 1;
    unsigned int rsvd_0 : 3;
    unsigned int rg_dpd_mcs_man : 4;
    unsigned int rg_use_dpd_bypass_mcs0 : 1;
    unsigned int rg_use_dpd_bypass_mcs1 : 1;
    unsigned int rg_use_dpd_bypass_mcs2 : 1;
    unsigned int rg_use_dpd_bypass_mcs3 : 1;
    unsigned int rg_use_dpd_bypass_mcs4 : 1;
    unsigned int rg_use_dpd_bypass_mcs5 : 1;
    unsigned int rg_use_dpd_bypass_mcs6 : 1;
    unsigned int rg_use_dpd_bypass_mcs7 : 1;
    unsigned int rg_use_dpd_bypass_mcs8 : 1;
    unsigned int rg_use_dpd_bypass_mcs9 : 1;
    unsigned int rg_use_dpd_bypass_mcsa : 1;
    unsigned int rg_use_dpd_bypass_mcsb : 1;
    unsigned int rsvd_1 : 12;
  } b;
} RG_XMIT_A200_FIELD_T;

#define RG_XMIT_A201                              (0x334)
// Bit 11  :0      rg_txdpd_comp_coef_i_2_00_man     U     RW        default = 'hff1
// Bit 27  :16     rg_txdpd_comp_coef_q_2_00_man     U     RW        default = 'h27
typedef union RG_XMIT_A201_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_2_00_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_2_00_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A201_FIELD_T;

#define RG_XMIT_A202                              (0x338)
// Bit 11  :0      rg_txdpd_comp_coef_i_2_01_man     U     RW        default = 'hfeb
// Bit 27  :16     rg_txdpd_comp_coef_q_2_01_man     U     RW        default = 'hf4d
typedef union RG_XMIT_A202_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_2_01_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_2_01_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A202_FIELD_T;

#define RG_XMIT_A203                              (0x33c)
// Bit 11  :0      rg_txdpd_comp_coef_i_2_02_man     U     RW        default = 'h5
// Bit 27  :16     rg_txdpd_comp_coef_q_2_02_man     U     RW        default = 'hfe4
typedef union RG_XMIT_A203_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_2_02_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_2_02_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A203_FIELD_T;

#define RG_XMIT_A204                              (0x340)
// Bit 11  :0      rg_txdpd_comp_coef_i_2_03_man     U     RW        default = 'h0
// Bit 27  :16     rg_txdpd_comp_coef_q_2_03_man     U     RW        default = 'h0
typedef union RG_XMIT_A204_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_2_03_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_2_03_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A204_FIELD_T;

#define RG_XMIT_A205                              (0x344)
// Bit 11  :0      rg_txdpd_comp_coef_i_2_04_man     U     RW        default = 'h6
// Bit 27  :16     rg_txdpd_comp_coef_q_2_04_man     U     RW        default = 'hfee
typedef union RG_XMIT_A205_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_2_04_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_2_04_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A205_FIELD_T;

#define RG_XMIT_A206                              (0x348)
// Bit 11  :0      rg_txdpd_comp_coef_i_2_05_man     U     RW        default = 'h17
// Bit 27  :16     rg_txdpd_comp_coef_q_2_05_man     U     RW        default = 'ha3
typedef union RG_XMIT_A206_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_2_05_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_2_05_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A206_FIELD_T;

#define RG_XMIT_A207                              (0x34c)
// Bit 11  :0      rg_txdpd_comp_coef_i_2_06_man     U     RW        default = 'hffc
// Bit 27  :16     rg_txdpd_comp_coef_q_2_06_man     U     RW        default = 'h16
typedef union RG_XMIT_A207_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_2_06_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_2_06_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A207_FIELD_T;

#define RG_XMIT_A208                              (0x350)
// Bit 11  :0      rg_txdpd_comp_coef_i_2_07_man     U     RW        default = 'h0
// Bit 27  :16     rg_txdpd_comp_coef_q_2_07_man     U     RW        default = 'h0
typedef union RG_XMIT_A208_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_2_07_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_2_07_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A208_FIELD_T;

#define RG_XMIT_A209                              (0x354)
// Bit 11  :0      rg_txdpd_comp_coef_i_2_08_man     U     RW        default = 'hfff
// Bit 27  :16     rg_txdpd_comp_coef_q_2_08_man     U     RW        default = 'h5
typedef union RG_XMIT_A209_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_2_08_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_2_08_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A209_FIELD_T;

#define RG_XMIT_A210                              (0x358)
// Bit 11  :0      rg_txdpd_comp_coef_i_2_09_man     U     RW        default = 'h9
// Bit 27  :16     rg_txdpd_comp_coef_q_2_09_man     U     RW        default = 'hf51
typedef union RG_XMIT_A210_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_2_09_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_2_09_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A210_FIELD_T;

#define RG_XMIT_A211                              (0x35c)
// Bit 11  :0      rg_txdpd_comp_coef_i_2_10_man     U     RW        default = 'hff9
// Bit 27  :16     rg_txdpd_comp_coef_q_2_10_man     U     RW        default = 'h46
typedef union RG_XMIT_A211_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_2_10_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_2_10_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A211_FIELD_T;

#define RG_XMIT_A212                              (0x360)
// Bit 11  :0      rg_txdpd_comp_coef_i_2_11_man     U     RW        default = 'h0
// Bit 27  :16     rg_txdpd_comp_coef_q_2_11_man     U     RW        default = 'h0
typedef union RG_XMIT_A212_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_2_11_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_2_11_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A212_FIELD_T;

#define RG_XMIT_A213                              (0x364)
// Bit 11  :0      rg_txdpd_comp_coef_i_2_12_man     U     RW        default = 'hff8
// Bit 27  :16     rg_txdpd_comp_coef_q_2_12_man     U     RW        default = 'h13
typedef union RG_XMIT_A213_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_2_12_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_2_12_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A213_FIELD_T;

#define RG_XMIT_A214                              (0x368)
// Bit 11  :0      rg_txdpd_comp_coef_i_2_13_man     U     RW        default = 'h10
// Bit 27  :16     rg_txdpd_comp_coef_q_2_13_man     U     RW        default = 'h8
typedef union RG_XMIT_A214_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_2_13_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_2_13_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A214_FIELD_T;

#define RG_XMIT_A215                              (0x36c)
// Bit 11  :0      rg_txdpd_comp_coef_i_2_14_man     U     RW        default = 'he
// Bit 27  :16     rg_txdpd_comp_coef_q_2_14_man     U     RW        default = 'h93
typedef union RG_XMIT_A215_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_2_14_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_2_14_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A215_FIELD_T;

#define RG_XMIT_A216                              (0x370)
// Bit 11  :0      rg_txdpd_comp_coef_i_2_15_man     U     RW        default = 'h0
// Bit 27  :16     rg_txdpd_comp_coef_q_2_15_man     U     RW        default = 'h0
typedef union RG_XMIT_A216_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_2_15_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_2_15_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A216_FIELD_T;

#define RG_XMIT_A217                              (0x374)
// Bit 11  :0      rg_txdpd_comp_coef_i_2_16_man     U     RW        default = 'h16
// Bit 27  :16     rg_txdpd_comp_coef_q_2_16_man     U     RW        default = 'h1f
typedef union RG_XMIT_A217_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_2_16_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_2_16_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A217_FIELD_T;

#define RG_XMIT_A218                              (0x378)
// Bit 11  :0      rg_txdpd_comp_coef_i_2_17_man     U     RW        default = 'hfe1
// Bit 27  :16     rg_txdpd_comp_coef_q_2_17_man     U     RW        default = 'hff9
typedef union RG_XMIT_A218_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_2_17_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_2_17_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A218_FIELD_T;

#define RG_XMIT_A219                              (0x37c)
// Bit 11  :0      rg_txdpd_comp_coef_i_2_18_man     U     RW        default = 'hf79
// Bit 27  :16     rg_txdpd_comp_coef_q_2_18_man     U     RW        default = 'hc7f
typedef union RG_XMIT_A219_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_2_18_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_2_18_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A219_FIELD_T;

#define RG_XMIT_A220                              (0x380)
// Bit 11  :0      rg_txdpd_comp_coef_i_2_19_man     U     RW        default = 'h0
// Bit 27  :16     rg_txdpd_comp_coef_q_2_19_man     U     RW        default = 'h0
typedef union RG_XMIT_A220_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdpd_comp_coef_i_2_19_man : 12;
    unsigned int rsvd_0 : 4;
    unsigned int rg_txdpd_comp_coef_q_2_19_man : 12;
    unsigned int rsvd_1 : 4;
  } b;
} RG_XMIT_A220_FIELD_T;

#define RG_XMIT_A221                              (0x384)
// Bit 12  :0      rg_tx_target_max_pwrlvl_mcs0     U     RW        default = 'h0
// Bit 28  :16     rg_tx_target_max_pwrlvl_mcs1     U     RW        default = 'h0
typedef union RG_XMIT_A221_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_target_max_pwrlvl_mcs0 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int rg_tx_target_max_pwrlvl_mcs1 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A221_FIELD_T;

#define RG_XMIT_A222                              (0x388)
// Bit 12  :0      rg_tx_target_max_pwrlvl_mcs2     U     RW        default = 'h0
// Bit 28  :16     rg_tx_target_max_pwrlvl_mcs3     U     RW        default = 'h0
typedef union RG_XMIT_A222_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_target_max_pwrlvl_mcs2 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int rg_tx_target_max_pwrlvl_mcs3 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A222_FIELD_T;

#define RG_XMIT_A223                              (0x38c)
// Bit 12  :0      rg_tx_target_max_pwrlvl_mcs4     U     RW        default = 'h0
// Bit 28  :16     rg_tx_target_max_pwrlvl_mcs5     U     RW        default = 'h0
typedef union RG_XMIT_A223_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_target_max_pwrlvl_mcs4 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int rg_tx_target_max_pwrlvl_mcs5 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A223_FIELD_T;

#define RG_XMIT_A224                              (0x390)
// Bit 12  :0      rg_tx_target_max_pwrlvl_mcs6     U     RW        default = 'h0
// Bit 28  :16     rg_tx_target_max_pwrlvl_mcs7     U     RW        default = 'h0
typedef union RG_XMIT_A224_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_target_max_pwrlvl_mcs6 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int rg_tx_target_max_pwrlvl_mcs7 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A224_FIELD_T;

#define RG_XMIT_A225                              (0x394)
// Bit 12  :0      rg_tx_target_max_pwrlvl_mcs8     U     RW        default = 'h0
// Bit 28  :16     rg_tx_target_max_pwrlvl_mcs9     U     RW        default = 'h0
typedef union RG_XMIT_A225_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_target_max_pwrlvl_mcs8 : 13;
    unsigned int rsvd_0 : 3;
    unsigned int rg_tx_target_max_pwrlvl_mcs9 : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A225_FIELD_T;

#define RG_XMIT_A226                              (0x398)
// Bit 12  :0      rg_tx_target_max_pwrlvl_mcsa     U     RW        default = 'h0
// Bit 28  :16     rg_tx_target_max_pwrlvl_mcsb     U     RW        default = 'h0
typedef union RG_XMIT_A226_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_target_max_pwrlvl_mcsa : 13;
    unsigned int rsvd_0 : 3;
    unsigned int rg_tx_target_max_pwrlvl_mcsb : 13;
    unsigned int rsvd_1 : 3;
  } b;
} RG_XMIT_A226_FIELD_T;

#define RG_XMIT_A227                              (0x39c)
// Bit 0           rg_tx_target_max_pwrlvl_bypass     U     RW        default = 'h1
typedef union RG_XMIT_A227_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_target_max_pwrlvl_bypass : 1;
    unsigned int rsvd_0 : 31;
  } b;
} RG_XMIT_A227_FIELD_T;

#define RG_XMIT_A228                              (0x3a0)
// Bit 3   :0      rg_wf2g_11b_tpwr_0             U     RW        default = 'h0
// Bit 7   :4      rg_wf2g_11b_tpwr_1             U     RW        default = 'h0
// Bit 11  :8      rg_wf2g_11b_tpwr_2             U     RW        default = 'h0
// Bit 15  :12     rg_wf2g_11b_tpwr_3             U     RW        default = 'h0
typedef union RG_XMIT_A228_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_wf2g_11b_tpwr_0 : 4;
    unsigned int rg_wf2g_11b_tpwr_1 : 4;
    unsigned int rg_wf2g_11b_tpwr_2 : 4;
    unsigned int rg_wf2g_11b_tpwr_3 : 4;
    unsigned int rsvd_0 : 16;
  } b;
} RG_XMIT_A228_FIELD_T;

#define RG_XMIT_A229                              (0x3a4)
// Bit 3   :0      rg_wf2g_11g_tpwr_0             U     RW        default = 'h0
// Bit 7   :4      rg_wf2g_11g_tpwr_1             U     RW        default = 'h0
// Bit 11  :8      rg_wf2g_11g_tpwr_2             U     RW        default = 'h0
// Bit 15  :12     rg_wf2g_11g_tpwr_3             U     RW        default = 'h0
// Bit 19  :16     rg_wf2g_11g_tpwr_4             U     RW        default = 'h0
// Bit 23  :20     rg_wf2g_11g_tpwr_5             U     RW        default = 'h0
// Bit 27  :24     rg_wf2g_11g_tpwr_6             U     RW        default = 'h0
// Bit 31  :28     rg_wf2g_11g_tpwr_7             U     RW        default = 'h0
typedef union RG_XMIT_A229_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_wf2g_11g_tpwr_0 : 4;
    unsigned int rg_wf2g_11g_tpwr_1 : 4;
    unsigned int rg_wf2g_11g_tpwr_2 : 4;
    unsigned int rg_wf2g_11g_tpwr_3 : 4;
    unsigned int rg_wf2g_11g_tpwr_4 : 4;
    unsigned int rg_wf2g_11g_tpwr_5 : 4;
    unsigned int rg_wf2g_11g_tpwr_6 : 4;
    unsigned int rg_wf2g_11g_tpwr_7 : 4;
  } b;
} RG_XMIT_A229_FIELD_T;

#define RG_XMIT_A230                              (0x3a8)
// Bit 3   :0      rg_wf2g_ht20_tpwr_0            U     RW        default = 'h0
// Bit 7   :4      rg_wf2g_ht20_tpwr_1            U     RW        default = 'h0
// Bit 11  :8      rg_wf2g_ht20_tpwr_2            U     RW        default = 'h0
// Bit 15  :12     rg_wf2g_ht20_tpwr_3            U     RW        default = 'h0
// Bit 19  :16     rg_wf2g_ht20_tpwr_4            U     RW        default = 'h0
// Bit 23  :20     rg_wf2g_ht20_tpwr_5            U     RW        default = 'h0
// Bit 27  :24     rg_wf2g_ht20_tpwr_6            U     RW        default = 'h0
// Bit 31  :28     rg_wf2g_ht20_tpwr_7            U     RW        default = 'h0
typedef union RG_XMIT_A230_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_wf2g_ht20_tpwr_0 : 4;
    unsigned int rg_wf2g_ht20_tpwr_1 : 4;
    unsigned int rg_wf2g_ht20_tpwr_2 : 4;
    unsigned int rg_wf2g_ht20_tpwr_3 : 4;
    unsigned int rg_wf2g_ht20_tpwr_4 : 4;
    unsigned int rg_wf2g_ht20_tpwr_5 : 4;
    unsigned int rg_wf2g_ht20_tpwr_6 : 4;
    unsigned int rg_wf2g_ht20_tpwr_7 : 4;
  } b;
} RG_XMIT_A230_FIELD_T;

#define RG_XMIT_A231                              (0x3ac)
// Bit 3   :0      rg_wf2g_ht40_tpwr_0            U     RW        default = 'h0
// Bit 7   :4      rg_wf2g_ht40_tpwr_1            U     RW        default = 'h0
// Bit 11  :8      rg_wf2g_ht40_tpwr_2            U     RW        default = 'h0
// Bit 15  :12     rg_wf2g_ht40_tpwr_3            U     RW        default = 'h0
// Bit 19  :16     rg_wf2g_ht40_tpwr_4            U     RW        default = 'h0
// Bit 23  :20     rg_wf2g_ht40_tpwr_5            U     RW        default = 'h0
// Bit 27  :24     rg_wf2g_ht40_tpwr_6            U     RW        default = 'h0
// Bit 31  :28     rg_wf2g_ht40_tpwr_7            U     RW        default = 'h0
typedef union RG_XMIT_A231_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_wf2g_ht40_tpwr_0 : 4;
    unsigned int rg_wf2g_ht40_tpwr_1 : 4;
    unsigned int rg_wf2g_ht40_tpwr_2 : 4;
    unsigned int rg_wf2g_ht40_tpwr_3 : 4;
    unsigned int rg_wf2g_ht40_tpwr_4 : 4;
    unsigned int rg_wf2g_ht40_tpwr_5 : 4;
    unsigned int rg_wf2g_ht40_tpwr_6 : 4;
    unsigned int rg_wf2g_ht40_tpwr_7 : 4;
  } b;
} RG_XMIT_A231_FIELD_T;

#define RG_XMIT_A232                              (0x3b0)
// Bit 3   :0      rg_wf2g_vht20_tpwr_0           U     RW        default = 'h0
// Bit 7   :4      rg_wf2g_vht20_tpwr_1           U     RW        default = 'h0
// Bit 11  :8      rg_wf2g_vht20_tpwr_2           U     RW        default = 'h0
// Bit 15  :12     rg_wf2g_vht20_tpwr_3           U     RW        default = 'h0
// Bit 19  :16     rg_wf2g_vht20_tpwr_4           U     RW        default = 'h0
// Bit 23  :20     rg_wf2g_vht20_tpwr_5           U     RW        default = 'h0
// Bit 27  :24     rg_wf2g_vht20_tpwr_6           U     RW        default = 'h0
// Bit 31  :28     rg_wf2g_vht20_tpwr_7           U     RW        default = 'h0
typedef union RG_XMIT_A232_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_wf2g_vht20_tpwr_0 : 4;
    unsigned int rg_wf2g_vht20_tpwr_1 : 4;
    unsigned int rg_wf2g_vht20_tpwr_2 : 4;
    unsigned int rg_wf2g_vht20_tpwr_3 : 4;
    unsigned int rg_wf2g_vht20_tpwr_4 : 4;
    unsigned int rg_wf2g_vht20_tpwr_5 : 4;
    unsigned int rg_wf2g_vht20_tpwr_6 : 4;
    unsigned int rg_wf2g_vht20_tpwr_7 : 4;
  } b;
} RG_XMIT_A232_FIELD_T;

#define RG_XMIT_A233                              (0x3b4)
// Bit 3   :0      rg_wf2g_vht40_tpwr_0           U     RW        default = 'h0
// Bit 7   :4      rg_wf2g_vht40_tpwr_1           U     RW        default = 'h0
// Bit 11  :8      rg_wf2g_vht40_tpwr_2           U     RW        default = 'h0
// Bit 15  :12     rg_wf2g_vht40_tpwr_3           U     RW        default = 'h0
// Bit 19  :16     rg_wf2g_vht40_tpwr_4           U     RW        default = 'h0
// Bit 23  :20     rg_wf2g_vht40_tpwr_5           U     RW        default = 'h0
// Bit 27  :24     rg_wf2g_vht40_tpwr_6           U     RW        default = 'h0
// Bit 31  :28     rg_wf2g_vht40_tpwr_7           U     RW        default = 'h0
typedef union RG_XMIT_A233_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_wf2g_vht40_tpwr_0 : 4;
    unsigned int rg_wf2g_vht40_tpwr_1 : 4;
    unsigned int rg_wf2g_vht40_tpwr_2 : 4;
    unsigned int rg_wf2g_vht40_tpwr_3 : 4;
    unsigned int rg_wf2g_vht40_tpwr_4 : 4;
    unsigned int rg_wf2g_vht40_tpwr_5 : 4;
    unsigned int rg_wf2g_vht40_tpwr_6 : 4;
    unsigned int rg_wf2g_vht40_tpwr_7 : 4;
  } b;
} RG_XMIT_A233_FIELD_T;

#define RG_XMIT_A234                              (0x3b8)
// Bit 3   :0      rg_wf2g_he20_tpwr_0            U     RW        default = 'h0
// Bit 7   :4      rg_wf2g_he20_tpwr_1            U     RW        default = 'h0
// Bit 11  :8      rg_wf2g_he20_tpwr_2            U     RW        default = 'h0
// Bit 15  :12     rg_wf2g_he20_tpwr_3            U     RW        default = 'h0
// Bit 19  :16     rg_wf2g_he20_tpwr_4            U     RW        default = 'h0
// Bit 23  :20     rg_wf2g_he20_tpwr_5            U     RW        default = 'h0
// Bit 27  :24     rg_wf2g_he20_tpwr_6            U     RW        default = 'h0
// Bit 31  :28     rg_wf2g_he20_tpwr_7            U     RW        default = 'h0
typedef union RG_XMIT_A234_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_wf2g_he20_tpwr_0 : 4;
    unsigned int rg_wf2g_he20_tpwr_1 : 4;
    unsigned int rg_wf2g_he20_tpwr_2 : 4;
    unsigned int rg_wf2g_he20_tpwr_3 : 4;
    unsigned int rg_wf2g_he20_tpwr_4 : 4;
    unsigned int rg_wf2g_he20_tpwr_5 : 4;
    unsigned int rg_wf2g_he20_tpwr_6 : 4;
    unsigned int rg_wf2g_he20_tpwr_7 : 4;
  } b;
} RG_XMIT_A234_FIELD_T;

#define RG_XMIT_A235                              (0x3bc)
// Bit 3   :0      rg_wf2g_he40_tpwr_0            U     RW        default = 'h0
// Bit 7   :4      rg_wf2g_he40_tpwr_1            U     RW        default = 'h0
// Bit 11  :8      rg_wf2g_he40_tpwr_2            U     RW        default = 'h0
// Bit 15  :12     rg_wf2g_he40_tpwr_3            U     RW        default = 'h0
// Bit 19  :16     rg_wf2g_he40_tpwr_4            U     RW        default = 'h0
// Bit 23  :20     rg_wf2g_he40_tpwr_5            U     RW        default = 'h0
// Bit 27  :24     rg_wf2g_he40_tpwr_6            U     RW        default = 'h0
// Bit 31  :28     rg_wf2g_he40_tpwr_7            U     RW        default = 'h0
typedef union RG_XMIT_A235_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_wf2g_he40_tpwr_0 : 4;
    unsigned int rg_wf2g_he40_tpwr_1 : 4;
    unsigned int rg_wf2g_he40_tpwr_2 : 4;
    unsigned int rg_wf2g_he40_tpwr_3 : 4;
    unsigned int rg_wf2g_he40_tpwr_4 : 4;
    unsigned int rg_wf2g_he40_tpwr_5 : 4;
    unsigned int rg_wf2g_he40_tpwr_6 : 4;
    unsigned int rg_wf2g_he40_tpwr_7 : 4;
  } b;
} RG_XMIT_A235_FIELD_T;

#define RG_XMIT_A236                              (0x3c0)
// Bit 3   :0      rg_wf2g_vht20_tpwr_8           U     RW        default = 'h0
// Bit 7   :4      rg_wf2g_vht40_tpwr_8           U     RW        default = 'h0
// Bit 11  :8      rg_wf2g_vht40_tpwr_9           U     RW        default = 'h0
// Bit 15  :12     rg_wf2g_he20_tpwr_8            U     RW        default = 'h0
// Bit 19  :16     rg_wf2g_he20_tpwr_9            U     RW        default = 'h0
// Bit 23  :20     rg_wf2g_he20_tpwr_10           U     RW        default = 'h0
// Bit 27  :24     rg_wf2g_he20_tpwr_11           U     RW        default = 'h0
typedef union RG_XMIT_A236_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_wf2g_vht20_tpwr_8 : 4;
    unsigned int rg_wf2g_vht40_tpwr_8 : 4;
    unsigned int rg_wf2g_vht40_tpwr_9 : 4;
    unsigned int rg_wf2g_he20_tpwr_8 : 4;
    unsigned int rg_wf2g_he20_tpwr_9 : 4;
    unsigned int rg_wf2g_he20_tpwr_10 : 4;
    unsigned int rg_wf2g_he20_tpwr_11 : 4;
    unsigned int rsvd_0 : 4;
  } b;
} RG_XMIT_A236_FIELD_T;

#define RG_XMIT_A237                              (0x3c4)
// Bit 3   :0      rg_wf2g_he40_tpwr_8            U     RW        default = 'h0
// Bit 7   :4      rg_wf2g_he40_tpwr_9            U     RW        default = 'h0
// Bit 11  :8      rg_wf2g_he40_tpwr_10           U     RW        default = 'h0
// Bit 15  :12     rg_wf2g_he40_tpwr_11           U     RW        default = 'h0
typedef union RG_XMIT_A237_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_wf2g_he40_tpwr_8 : 4;
    unsigned int rg_wf2g_he40_tpwr_9 : 4;
    unsigned int rg_wf2g_he40_tpwr_10 : 4;
    unsigned int rg_wf2g_he40_tpwr_11 : 4;
    unsigned int rsvd_0 : 16;
  } b;
} RG_XMIT_A237_FIELD_T;

#define RG_XMIT_A238                              (0x3c8)
// Bit 3   :0      rg_wf5g_11a_tpwr_0             U     RW        default = 'h0
// Bit 7   :4      rg_wf5g_11a_tpwr_1             U     RW        default = 'h0
// Bit 11  :8      rg_wf5g_11a_tpwr_2             U     RW        default = 'h0
// Bit 15  :12     rg_wf5g_11a_tpwr_3             U     RW        default = 'h0
// Bit 19  :16     rg_wf5g_11a_tpwr_4             U     RW        default = 'h0
// Bit 23  :20     rg_wf5g_11a_tpwr_5             U     RW        default = 'h0
// Bit 27  :24     rg_wf5g_11a_tpwr_6             U     RW        default = 'h0
// Bit 31  :28     rg_wf5g_11a_tpwr_7             U     RW        default = 'h0
typedef union RG_XMIT_A238_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_wf5g_11a_tpwr_0 : 4;
    unsigned int rg_wf5g_11a_tpwr_1 : 4;
    unsigned int rg_wf5g_11a_tpwr_2 : 4;
    unsigned int rg_wf5g_11a_tpwr_3 : 4;
    unsigned int rg_wf5g_11a_tpwr_4 : 4;
    unsigned int rg_wf5g_11a_tpwr_5 : 4;
    unsigned int rg_wf5g_11a_tpwr_6 : 4;
    unsigned int rg_wf5g_11a_tpwr_7 : 4;
  } b;
} RG_XMIT_A238_FIELD_T;

#define RG_XMIT_A239                              (0x3cc)
// Bit 3   :0      rg_wf5g_ht20_tpwr_0            U     RW        default = 'h0
// Bit 7   :4      rg_wf5g_ht20_tpwr_1            U     RW        default = 'h0
// Bit 11  :8      rg_wf5g_ht20_tpwr_2            U     RW        default = 'h0
// Bit 15  :12     rg_wf5g_ht20_tpwr_3            U     RW        default = 'h0
// Bit 19  :16     rg_wf5g_ht20_tpwr_4            U     RW        default = 'h0
// Bit 23  :20     rg_wf5g_ht20_tpwr_5            U     RW        default = 'h0
// Bit 27  :24     rg_wf5g_ht20_tpwr_6            U     RW        default = 'h0
// Bit 31  :28     rg_wf5g_ht20_tpwr_7            U     RW        default = 'h0
typedef union RG_XMIT_A239_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_wf5g_ht20_tpwr_0 : 4;
    unsigned int rg_wf5g_ht20_tpwr_1 : 4;
    unsigned int rg_wf5g_ht20_tpwr_2 : 4;
    unsigned int rg_wf5g_ht20_tpwr_3 : 4;
    unsigned int rg_wf5g_ht20_tpwr_4 : 4;
    unsigned int rg_wf5g_ht20_tpwr_5 : 4;
    unsigned int rg_wf5g_ht20_tpwr_6 : 4;
    unsigned int rg_wf5g_ht20_tpwr_7 : 4;
  } b;
} RG_XMIT_A239_FIELD_T;

#define RG_XMIT_A240                              (0x3d0)
// Bit 3   :0      rg_wf5g_ht40_tpwr_0            U     RW        default = 'h0
// Bit 7   :4      rg_wf5g_ht40_tpwr_1            U     RW        default = 'h0
// Bit 11  :8      rg_wf5g_ht40_tpwr_2            U     RW        default = 'h0
// Bit 15  :12     rg_wf5g_ht40_tpwr_3            U     RW        default = 'h0
// Bit 19  :16     rg_wf5g_ht40_tpwr_4            U     RW        default = 'h0
// Bit 23  :20     rg_wf5g_ht40_tpwr_5            U     RW        default = 'h0
// Bit 27  :24     rg_wf5g_ht40_tpwr_6            U     RW        default = 'h0
// Bit 31  :28     rg_wf5g_ht40_tpwr_7            U     RW        default = 'h0
typedef union RG_XMIT_A240_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_wf5g_ht40_tpwr_0 : 4;
    unsigned int rg_wf5g_ht40_tpwr_1 : 4;
    unsigned int rg_wf5g_ht40_tpwr_2 : 4;
    unsigned int rg_wf5g_ht40_tpwr_3 : 4;
    unsigned int rg_wf5g_ht40_tpwr_4 : 4;
    unsigned int rg_wf5g_ht40_tpwr_5 : 4;
    unsigned int rg_wf5g_ht40_tpwr_6 : 4;
    unsigned int rg_wf5g_ht40_tpwr_7 : 4;
  } b;
} RG_XMIT_A240_FIELD_T;

#define RG_XMIT_A241                              (0x3d4)
// Bit 3   :0      rg_wf5g_vht20_tpwr_0           U     RW        default = 'h0
// Bit 7   :4      rg_wf5g_vht20_tpwr_1           U     RW        default = 'h0
// Bit 11  :8      rg_wf5g_vht20_tpwr_2           U     RW        default = 'h0
// Bit 15  :12     rg_wf5g_vht20_tpwr_3           U     RW        default = 'h0
// Bit 19  :16     rg_wf5g_vht20_tpwr_4           U     RW        default = 'h0
// Bit 23  :20     rg_wf5g_vht20_tpwr_5           U     RW        default = 'h0
// Bit 27  :24     rg_wf5g_vht20_tpwr_6           U     RW        default = 'h0
// Bit 31  :28     rg_wf5g_vht20_tpwr_7           U     RW        default = 'h0
typedef union RG_XMIT_A241_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_wf5g_vht20_tpwr_0 : 4;
    unsigned int rg_wf5g_vht20_tpwr_1 : 4;
    unsigned int rg_wf5g_vht20_tpwr_2 : 4;
    unsigned int rg_wf5g_vht20_tpwr_3 : 4;
    unsigned int rg_wf5g_vht20_tpwr_4 : 4;
    unsigned int rg_wf5g_vht20_tpwr_5 : 4;
    unsigned int rg_wf5g_vht20_tpwr_6 : 4;
    unsigned int rg_wf5g_vht20_tpwr_7 : 4;
  } b;
} RG_XMIT_A241_FIELD_T;

#define RG_XMIT_A242                              (0x3d8)
// Bit 3   :0      rg_wf5g_vht40_tpwr_0           U     RW        default = 'h0
// Bit 7   :4      rg_wf5g_vht40_tpwr_1           U     RW        default = 'h0
// Bit 11  :8      rg_wf5g_vht40_tpwr_2           U     RW        default = 'h0
// Bit 15  :12     rg_wf5g_vht40_tpwr_3           U     RW        default = 'h0
// Bit 19  :16     rg_wf5g_vht40_tpwr_4           U     RW        default = 'h0
// Bit 23  :20     rg_wf5g_vht40_tpwr_5           U     RW        default = 'h0
// Bit 27  :24     rg_wf5g_vht40_tpwr_6           U     RW        default = 'h0
// Bit 31  :28     rg_wf5g_vht40_tpwr_7           U     RW        default = 'h0
typedef union RG_XMIT_A242_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_wf5g_vht40_tpwr_0 : 4;
    unsigned int rg_wf5g_vht40_tpwr_1 : 4;
    unsigned int rg_wf5g_vht40_tpwr_2 : 4;
    unsigned int rg_wf5g_vht40_tpwr_3 : 4;
    unsigned int rg_wf5g_vht40_tpwr_4 : 4;
    unsigned int rg_wf5g_vht40_tpwr_5 : 4;
    unsigned int rg_wf5g_vht40_tpwr_6 : 4;
    unsigned int rg_wf5g_vht40_tpwr_7 : 4;
  } b;
} RG_XMIT_A242_FIELD_T;

#define RG_XMIT_A243                              (0x3dc)
// Bit 3   :0      rg_wf5g_vht80_tpwr_0           U     RW        default = 'h0
// Bit 7   :4      rg_wf5g_vht80_tpwr_1           U     RW        default = 'h0
// Bit 11  :8      rg_wf5g_vht80_tpwr_2           U     RW        default = 'h0
// Bit 15  :12     rg_wf5g_vht80_tpwr_3           U     RW        default = 'h0
// Bit 19  :16     rg_wf5g_vht80_tpwr_4           U     RW        default = 'h0
// Bit 23  :20     rg_wf5g_vht80_tpwr_5           U     RW        default = 'h0
// Bit 27  :24     rg_wf5g_vht80_tpwr_6           U     RW        default = 'h0
// Bit 31  :28     rg_wf5g_vht80_tpwr_7           U     RW        default = 'h0
typedef union RG_XMIT_A243_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_wf5g_vht80_tpwr_0 : 4;
    unsigned int rg_wf5g_vht80_tpwr_1 : 4;
    unsigned int rg_wf5g_vht80_tpwr_2 : 4;
    unsigned int rg_wf5g_vht80_tpwr_3 : 4;
    unsigned int rg_wf5g_vht80_tpwr_4 : 4;
    unsigned int rg_wf5g_vht80_tpwr_5 : 4;
    unsigned int rg_wf5g_vht80_tpwr_6 : 4;
    unsigned int rg_wf5g_vht80_tpwr_7 : 4;
  } b;
} RG_XMIT_A243_FIELD_T;

#define RG_XMIT_A244                              (0x3e0)
// Bit 3   :0      rg_wf5g_he20_tpwr_0            U     RW        default = 'h0
// Bit 7   :4      rg_wf5g_he20_tpwr_1            U     RW        default = 'h0
// Bit 11  :8      rg_wf5g_he20_tpwr_2            U     RW        default = 'h0
// Bit 15  :12     rg_wf5g_he20_tpwr_3            U     RW        default = 'h0
// Bit 19  :16     rg_wf5g_he20_tpwr_4            U     RW        default = 'h0
// Bit 23  :20     rg_wf5g_he20_tpwr_5            U     RW        default = 'h0
// Bit 27  :24     rg_wf5g_he20_tpwr_6            U     RW        default = 'h0
// Bit 31  :28     rg_wf5g_he20_tpwr_7            U     RW        default = 'h0
typedef union RG_XMIT_A244_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_wf5g_he20_tpwr_0 : 4;
    unsigned int rg_wf5g_he20_tpwr_1 : 4;
    unsigned int rg_wf5g_he20_tpwr_2 : 4;
    unsigned int rg_wf5g_he20_tpwr_3 : 4;
    unsigned int rg_wf5g_he20_tpwr_4 : 4;
    unsigned int rg_wf5g_he20_tpwr_5 : 4;
    unsigned int rg_wf5g_he20_tpwr_6 : 4;
    unsigned int rg_wf5g_he20_tpwr_7 : 4;
  } b;
} RG_XMIT_A244_FIELD_T;

#define RG_XMIT_A245                              (0x3e4)
// Bit 3   :0      rg_wf5g_he40_tpwr_0            U     RW        default = 'h0
// Bit 7   :4      rg_wf5g_he40_tpwr_1            U     RW        default = 'h0
// Bit 11  :8      rg_wf5g_he40_tpwr_2            U     RW        default = 'h0
// Bit 15  :12     rg_wf5g_he40_tpwr_3            U     RW        default = 'h0
// Bit 19  :16     rg_wf5g_he40_tpwr_4            U     RW        default = 'h0
// Bit 23  :20     rg_wf5g_he40_tpwr_5            U     RW        default = 'h0
// Bit 27  :24     rg_wf5g_he40_tpwr_6            U     RW        default = 'h0
// Bit 31  :28     rg_wf5g_he40_tpwr_7            U     RW        default = 'h0
typedef union RG_XMIT_A245_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_wf5g_he40_tpwr_0 : 4;
    unsigned int rg_wf5g_he40_tpwr_1 : 4;
    unsigned int rg_wf5g_he40_tpwr_2 : 4;
    unsigned int rg_wf5g_he40_tpwr_3 : 4;
    unsigned int rg_wf5g_he40_tpwr_4 : 4;
    unsigned int rg_wf5g_he40_tpwr_5 : 4;
    unsigned int rg_wf5g_he40_tpwr_6 : 4;
    unsigned int rg_wf5g_he40_tpwr_7 : 4;
  } b;
} RG_XMIT_A245_FIELD_T;

#define RG_XMIT_A246                              (0x3e8)
// Bit 3   :0      rg_wf5g_he80_tpwr_0            U     RW        default = 'h0
// Bit 7   :4      rg_wf5g_he80_tpwr_1            U     RW        default = 'h0
// Bit 11  :8      rg_wf5g_he80_tpwr_2            U     RW        default = 'h0
// Bit 15  :12     rg_wf5g_he80_tpwr_3            U     RW        default = 'h0
// Bit 19  :16     rg_wf5g_he80_tpwr_4            U     RW        default = 'h0
// Bit 23  :20     rg_wf5g_he80_tpwr_5            U     RW        default = 'h0
// Bit 27  :24     rg_wf5g_he80_tpwr_6            U     RW        default = 'h0
// Bit 31  :28     rg_wf5g_he80_tpwr_7            U     RW        default = 'h0
typedef union RG_XMIT_A246_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_wf5g_he80_tpwr_0 : 4;
    unsigned int rg_wf5g_he80_tpwr_1 : 4;
    unsigned int rg_wf5g_he80_tpwr_2 : 4;
    unsigned int rg_wf5g_he80_tpwr_3 : 4;
    unsigned int rg_wf5g_he80_tpwr_4 : 4;
    unsigned int rg_wf5g_he80_tpwr_5 : 4;
    unsigned int rg_wf5g_he80_tpwr_6 : 4;
    unsigned int rg_wf5g_he80_tpwr_7 : 4;
  } b;
} RG_XMIT_A246_FIELD_T;

#define RG_XMIT_A247                              (0x3ec)
// Bit 3   :0      rg_wf5g_vht20_tpwr_8           U     RW        default = 'h0
// Bit 7   :4      rg_wf5g_vht40_tpwr_8           U     RW        default = 'h0
// Bit 11  :8      rg_wf5g_vht40_tpwr_9           U     RW        default = 'h0
// Bit 15  :12     rg_wf5g_vht80_tpwr_8           U     RW        default = 'h0
// Bit 19  :16     rg_wf5g_vht80_tpwr_9           U     RW        default = 'h0
typedef union RG_XMIT_A247_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_wf5g_vht20_tpwr_8 : 4;
    unsigned int rg_wf5g_vht40_tpwr_8 : 4;
    unsigned int rg_wf5g_vht40_tpwr_9 : 4;
    unsigned int rg_wf5g_vht80_tpwr_8 : 4;
    unsigned int rg_wf5g_vht80_tpwr_9 : 4;
    unsigned int rsvd_0 : 12;
  } b;
} RG_XMIT_A247_FIELD_T;

#define RG_XMIT_A248                              (0x3f0)
// Bit 3   :0      rg_wf5g_he20_tpwr_8            U     RW        default = 'h0
// Bit 7   :4      rg_wf5g_he20_tpwr_9            U     RW        default = 'h0
// Bit 11  :8      rg_wf5g_he20_tpwr_10           U     RW        default = 'h0
// Bit 15  :12     rg_wf5g_he20_tpwr_11           U     RW        default = 'h0
// Bit 19  :16     rg_wf5g_he40_tpwr_8            U     RW        default = 'h0
// Bit 23  :20     rg_wf5g_he40_tpwr_9            U     RW        default = 'h0
// Bit 27  :24     rg_wf5g_he40_tpwr_10           U     RW        default = 'h0
// Bit 31  :28     rg_wf5g_he40_tpwr_11           U     RW        default = 'h0
typedef union RG_XMIT_A248_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_wf5g_he20_tpwr_8 : 4;
    unsigned int rg_wf5g_he20_tpwr_9 : 4;
    unsigned int rg_wf5g_he20_tpwr_10 : 4;
    unsigned int rg_wf5g_he20_tpwr_11 : 4;
    unsigned int rg_wf5g_he40_tpwr_8 : 4;
    unsigned int rg_wf5g_he40_tpwr_9 : 4;
    unsigned int rg_wf5g_he40_tpwr_10 : 4;
    unsigned int rg_wf5g_he40_tpwr_11 : 4;
  } b;
} RG_XMIT_A248_FIELD_T;

#define RG_XMIT_A249                              (0x3f4)
// Bit 3   :0      rg_wf5g_he80_tpwr_8            U     RW        default = 'h0
// Bit 7   :4      rg_wf5g_he80_tpwr_9            U     RW        default = 'h0
// Bit 11  :8      rg_wf5g_he80_tpwr_10           U     RW        default = 'h0
// Bit 15  :12     rg_wf5g_he80_tpwr_11           U     RW        default = 'h0
typedef union RG_XMIT_A249_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_wf5g_he80_tpwr_8 : 4;
    unsigned int rg_wf5g_he80_tpwr_9 : 4;
    unsigned int rg_wf5g_he80_tpwr_10 : 4;
    unsigned int rg_wf5g_he80_tpwr_11 : 4;
    unsigned int rsvd_0 : 16;
  } b;
} RG_XMIT_A249_FIELD_T;

#define RG_XMIT_A250                              (0x3f8)
// Bit 0           rg_tpwr_offset_man_sel         U     RW        default = 'h0
// Bit 7   :4      rg_tpwr_offset_man             U     RW        default = 'h0
typedef union RG_XMIT_A250_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tpwr_offset_man_sel : 1;
    unsigned int rsvd_0 : 3;
    unsigned int rg_tpwr_offset_man : 4;
    unsigned int rsvd_1 : 24;
  } b;
} RG_XMIT_A250_FIELD_T;

#endif

