/* SPDX-License-Identifier: GPL-2.0 */
/*
* Copyright (C) 202X Original Author (retain original author information)
* Copyright (C) 202X Amlogic, Inc. All rights reserved.
*
* Description:
*/
#ifdef RF_D_BT_ADDA_ESTI_REG
#else
#define RF_D_BT_ADDA_ESTI_REG

#define RG_BT_ESTI_A0                             (0x0)
// Bit 31  :0      rg_esti_cfg0                   U     RW        default = 'h0
typedef union RG_BT_ESTI_A0_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_esti_cfg0 : 32;
  } b;
} RG_BT_ESTI_A0_FIELD_T;

#define RG_BT_ESTI_A1                             (0x4)
// Bit 31  :0      rg_esti_cfg1                   U     RW        default = 'h0
typedef union RG_BT_ESTI_A1_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_esti_cfg1 : 32;
  } b;
} RG_BT_ESTI_A1_FIELD_T;

#define RG_BT_ESTI_A2                             (0x8)
// Bit 0           rg_iqib_enable                 U     RW        default = 'h0
// Bit 1           rg_iqib_hold                   U     RW        default = 'h0
// Bit 7   :4      rg_iqib_period                 U     RW        default = 'h0
// Bit 11  :8      rg_iqib_step_a                 U     RW        default = 'h1
// Bit 15  :12     rg_iqib_step_b                 U     RW        default = 'h1
// Bit 18  :16     rg_iqib_shift                  U     RW        default = 'h0
// Bit 20          rg_iqib_man_en                 U     RW        default = 'h0
typedef union RG_BT_ESTI_A2_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_iqib_enable : 1;
    unsigned int rg_iqib_hold : 1;
    unsigned int rsvd_0 : 2;
    unsigned int rg_iqib_period : 4;
    unsigned int rg_iqib_step_a : 4;
    unsigned int rg_iqib_step_b : 4;
    unsigned int rg_iqib_shift : 3;
    unsigned int rsvd_1 : 1;
    unsigned int rg_iqib_man_en : 1;
    unsigned int rsvd_2 : 11;
  } b;
} RG_BT_ESTI_A2_FIELD_T;

#define RG_BT_ESTI_A3                             (0xc)
// Bit 21  :0      rg_set_b                       U     RW        default = 'h0
// Bit 31          rg_set_val                     U     RW        default = 'h0
typedef union RG_BT_ESTI_A3_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_set_b : 22;
    unsigned int rsvd_0 : 9;
    unsigned int rg_set_val : 1;
  } b;
} RG_BT_ESTI_A3_FIELD_T;

#define RG_BT_ESTI_A4                             (0x10)
// Bit 18  :0      rg_set_a                       U     RW        default = 'h0
typedef union RG_BT_ESTI_A4_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_set_a : 19;
    unsigned int rsvd_0 : 13;
  } b;
} RG_BT_ESTI_A4_FIELD_T;

#define RG_BT_ESTI_A5                             (0x14)
// Bit 3   :0      rg_dc_rm_leaky_factor          U     RW        default = 'h0
// Bit 28  :4      rg_spectrum_ana_angle_man      U     RW        default = 'h0
// Bit 31          rg_spectrum_ana_angle_man_en     U     RW        default = 'h0
typedef union RG_BT_ESTI_A5_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_dc_rm_leaky_factor : 4;
    unsigned int rg_spectrum_ana_angle_man : 25;
    unsigned int rsvd_0 : 2;
    unsigned int rg_spectrum_ana_angle_man_en : 1;
  } b;
} RG_BT_ESTI_A5_FIELD_T;

#define RG_BT_ESTI_A6                             (0x18)
// Bit 31  :0      rg_esti_cfg2                   U     RW        default = 'h0
typedef union RG_BT_ESTI_A6_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_esti_cfg2 : 32;
  } b;
} RG_BT_ESTI_A6_FIELD_T;

#define RG_BT_ESTI_A7                             (0x1c)
// Bit 31  :0      rg_esti_cfg3                   U     RW        default = 'h0
typedef union RG_BT_ESTI_A7_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_esti_cfg3 : 32;
  } b;
} RG_BT_ESTI_A7_FIELD_T;

#define RG_BT_ESTI_A8                             (0x20)
// Bit 7   :0      ro_txirr_dc_i                  U     RO        default = 'h0
// Bit 19  :12     ro_txirr_dc_q                  U     RO        default = 'h0
// Bit 24          ro_txirr_dc_ready              U     RO        default = 'h0
// Bit 25          ro_txirr_code_ready            U     RO        default = 'h0
// Bit 26          ro_txirr_mode_ready            U     RO        default = 'h0
// Bit 28          rg_txirr_code_continue         U     RW        default = 'h0
// Bit 29          rg_txirr_code_continue_bypass     U     RW        default = 'h1
// Bit 30          rg_txirr_mode_continue         U     RW        default = 'h0
// Bit 31          rg_txirr_mode_continue_bypass     U     RW        default = 'h1
typedef union RG_BT_ESTI_A8_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_txirr_dc_i : 8;
    unsigned int rsvd_0 : 4;
    unsigned int ro_txirr_dc_q : 8;
    unsigned int rsvd_1 : 4;
    unsigned int ro_txirr_dc_ready : 1;
    unsigned int ro_txirr_code_ready : 1;
    unsigned int ro_txirr_mode_ready : 1;
    unsigned int rsvd_2 : 1;
    unsigned int rg_txirr_code_continue : 1;
    unsigned int rg_txirr_code_continue_bypass : 1;
    unsigned int rg_txirr_mode_continue : 1;
    unsigned int rg_txirr_mode_continue_bypass : 1;
  } b;
} RG_BT_ESTI_A8_FIELD_T;

#define RG_BT_ESTI_A9                             (0x24)
// Bit 7   :0      ro_txirr_alpha                 U     RO        default = 'h0
// Bit 19  :12     ro_txirr_theta                 U     RO        default = 'h0
// Bit 24          ro_txirr_irr_ready             U     RO        default = 'h0
// Bit 28          rg_txirr_read_response_bypass     U     RW        default = 'h0
// Bit 31          rg_txirr_read_response         U     RW        default = 'h0
typedef union RG_BT_ESTI_A9_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_txirr_alpha : 8;
    unsigned int rsvd_0 : 4;
    unsigned int ro_txirr_theta : 8;
    unsigned int rsvd_1 : 4;
    unsigned int ro_txirr_irr_ready : 1;
    unsigned int rsvd_2 : 3;
    unsigned int rg_txirr_read_response_bypass : 1;
    unsigned int rsvd_3 : 2;
    unsigned int rg_txirr_read_response : 1;
  } b;
} RG_BT_ESTI_A9_FIELD_T;

#define RG_BT_ESTI_A10                            (0x28)
// Bit 7   :0      rg_tx_dcmax_i                  U     RW        default = 'h33
// Bit 15  :8      rg_tx_dcmax_q                  U     RW        default = 'h33
// Bit 23  :16     rg_tx_alpha_max                U     RW        default = 'h7b
// Bit 31  :24     rg_tx_theta_max                U     RW        default = 'h6b
typedef union RG_BT_ESTI_A10_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_dcmax_i : 8;
    unsigned int rg_tx_dcmax_q : 8;
    unsigned int rg_tx_alpha_max : 8;
    unsigned int rg_tx_theta_max : 8;
  } b;
} RG_BT_ESTI_A10_FIELD_T;

#define RG_BT_ESTI_A11                            (0x2c)
// Bit 7   :0      rg_tx_dcmin_i                  U     RW        default = 'hcd
// Bit 15  :8      rg_tx_dcmin_q                  U     RW        default = 'hcd
// Bit 23  :16     rg_tx_alpha_min                U     RW        default = 'h85
// Bit 31  :24     rg_tx_theta_min                U     RW        default = 'h95
typedef union RG_BT_ESTI_A11_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_dcmin_i : 8;
    unsigned int rg_tx_dcmin_q : 8;
    unsigned int rg_tx_alpha_min : 8;
    unsigned int rg_tx_theta_min : 8;
  } b;
} RG_BT_ESTI_A11_FIELD_T;

#define RG_BT_ESTI_A12                            (0x30)
// Bit 3   :0      rg_tx_dc_i_step                U     RW        default = 'h5
// Bit 7   :4      rg_tx_dc_q_step                U     RW        default = 'h5
// Bit 11  :8      rg_tx_alpha_step               U     RW        default = 'h3
// Bit 15  :12     rg_tx_theta_step               U     RW        default = 'h4
// Bit 19  :16     rg_txirr_oper_bnd              U     RW        default = 'h1
// Bit 20          rg_txirr_dyna_step_en          U     RW        default = 'h1
typedef union RG_BT_ESTI_A12_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_dc_i_step : 4;
    unsigned int rg_tx_dc_q_step : 4;
    unsigned int rg_tx_alpha_step : 4;
    unsigned int rg_tx_theta_step : 4;
    unsigned int rg_txirr_oper_bnd : 4;
    unsigned int rg_txirr_dyna_step_en : 1;
    unsigned int rsvd_0 : 11;
  } b;
} RG_BT_ESTI_A12_FIELD_T;

#define RG_BT_ESTI_A13                            (0x34)
// Bit 24  :0      rg_spectrum_ana_angle_txirr     U     RW        default = 'h1e00000
typedef union RG_BT_ESTI_A13_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_spectrum_ana_angle_txirr : 25;
    unsigned int rsvd_0 : 7;
  } b;
} RG_BT_ESTI_A13_FIELD_T;

#define RG_BT_ESTI_A14                            (0x38)
// Bit 24  :0      rg_spectrum_ana_angle_txdc     U     RW        default = 'h1f00000
typedef union RG_BT_ESTI_A14_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_spectrum_ana_angle_txdc : 25;
    unsigned int rsvd_0 : 7;
  } b;
} RG_BT_ESTI_A14_FIELD_T;

#define RG_BT_ESTI_A15                            (0x3c)
// Bit 24  :0      rg_spectrum_ana_angle_dpd      U     RW        default = 'h0
typedef union RG_BT_ESTI_A15_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_spectrum_ana_angle_dpd : 25;
    unsigned int rsvd_0 : 7;
  } b;
} RG_BT_ESTI_A15_FIELD_T;

#define RG_BT_ESTI_A16                            (0x40)
// Bit 24  :0      rg_spectrum_ana_angle_pwc      U     RW        default = 'h0
typedef union RG_BT_ESTI_A16_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_spectrum_ana_angle_pwc : 25;
    unsigned int rsvd_0 : 7;
  } b;
} RG_BT_ESTI_A16_FIELD_T;

#define RG_BT_ESTI_A17                            (0x44)
// Bit 23  :0      rg_adda_wait_count             U     RW        default = 'h50
typedef union RG_BT_ESTI_A17_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_adda_wait_count : 24;
    unsigned int rsvd_0 : 8;
  } b;
} RG_BT_ESTI_A17_FIELD_T;

#define RG_BT_ESTI_A18                            (0x48)
// Bit 14  :0      rg_adda_calc_count             U     RW        default = 'h50
typedef union RG_BT_ESTI_A18_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_adda_calc_count : 15;
    unsigned int rsvd_0 : 17;
  } b;
} RG_BT_ESTI_A18_FIELD_T;

#define RG_BT_ESTI_A19                            (0x4c)
// Bit 31  :0      ro_txirr_dc_pow_low            U     RO        default = 'h0
typedef union RG_BT_ESTI_A19_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_txirr_dc_pow_low : 32;
  } b;
} RG_BT_ESTI_A19_FIELD_T;

#define RG_BT_ESTI_A20                            (0x50)
// Bit 22  :0      ro_txirr_dc_pow_high           U     RO        default = 'h0
typedef union RG_BT_ESTI_A20_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_txirr_dc_pow_high : 23;
    unsigned int rsvd_0 : 9;
  } b;
} RG_BT_ESTI_A20_FIELD_T;

#define RG_BT_ESTI_A21                            (0x54)
// Bit 24  :0      rg_txdc_iq_tone                U     RW        default = 'h99999
typedef union RG_BT_ESTI_A21_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_txdc_iq_tone : 25;
    unsigned int rsvd_0 : 7;
  } b;
} RG_BT_ESTI_A21_FIELD_T;

#define RG_BT_ESTI_A22                            (0x58)
// Bit 0           rg_snr_esti_en                 U     RW        default = 'h1
// Bit 6   :4      rg_snr_esti_calctime           U     RW        default = 'h0
// Bit 10  :8      rg_snr_alpha                   U     RW        default = 'h0
typedef union RG_BT_ESTI_A22_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_snr_esti_en : 1;
    unsigned int rsvd_0 : 3;
    unsigned int rg_snr_esti_calctime : 3;
    unsigned int rsvd_1 : 1;
    unsigned int rg_snr_alpha : 3;
    unsigned int rsvd_2 : 21;
  } b;
} RG_BT_ESTI_A22_FIELD_T;

#define RG_BT_ESTI_A23                            (0x5c)
// Bit 8   :0      ro_adda_snr_db                 U     RO        default = 'h0
// Bit 12          ro_adda_db_vld                 U     RO        default = 'h0
// Bit 24  :16     ro_adda_pwr_db                 U     RO        default = 'h0
typedef union RG_BT_ESTI_A23_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_adda_snr_db : 9;
    unsigned int rsvd_0 : 3;
    unsigned int ro_adda_db_vld : 1;
    unsigned int rsvd_1 : 3;
    unsigned int ro_adda_pwr_db : 9;
    unsigned int rsvd_2 : 7;
  } b;
} RG_BT_ESTI_A23_FIELD_T;

#define RG_BT_ESTI_A24                            (0x60)
// Bit 7   :0      ro_txirr_fsm_st                U     RO        default = 'h0
typedef union RG_BT_ESTI_A24_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_txirr_fsm_st : 8;
    unsigned int rsvd_0 : 24;
  } b;
} RG_BT_ESTI_A24_FIELD_T;

#define RG_BT_ESTI_A25                            (0x64)
// Bit 1   :0      rg_snr_single_path_sel         U     RW        default = 'h0
// Bit 4           rg_snr_sig_alpha_double        U     RW        default = 'h0
typedef union RG_BT_ESTI_A25_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_snr_single_path_sel : 2;
    unsigned int rsvd_0 : 2;
    unsigned int rg_snr_sig_alpha_double : 1;
    unsigned int rsvd_1 : 27;
  } b;
} RG_BT_ESTI_A25_FIELD_T;

#define RG_BT_ESTI_A26                            (0x68)
// Bit 2   :0      ro_txlctank_esti_code          U     RO        default = 'h0
// Bit 8           ro_txlctank_esti_code_ready     U     RO        default = 'h0
// Bit 16          ro_txlctank_esti_finish        U     RO        default = 'h0
// Bit 28          rg_txlctank_read_response_bypass     U     RW        default = 'h0
// Bit 31          rg_txlctank_read_response      U     RW        default = 'h0
typedef union RG_BT_ESTI_A26_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_txlctank_esti_code : 3;
    unsigned int rsvd_0 : 5;
    unsigned int ro_txlctank_esti_code_ready : 1;
    unsigned int rsvd_1 : 7;
    unsigned int ro_txlctank_esti_finish : 1;
    unsigned int rsvd_2 : 11;
    unsigned int rg_txlctank_read_response_bypass : 1;
    unsigned int rsvd_3 : 2;
    unsigned int rg_txlctank_read_response : 1;
  } b;
} RG_BT_ESTI_A26_FIELD_T;

#define RG_BT_ESTI_A27                            (0x6c)
// Bit 31  :0      ro_txlctank_esti_pow           U     RO        default = 'h0
typedef union RG_BT_ESTI_A27_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_txlctank_esti_pow : 32;
  } b;
} RG_BT_ESTI_A27_FIELD_T;

#define RG_BT_ESTI_A28                            (0x70)
// Bit 24  :0      rg_spectrum_ana_angle_txlc     U     RW        default = 'h0
typedef union RG_BT_ESTI_A28_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_spectrum_ana_angle_txlc : 25;
    unsigned int rsvd_0 : 7;
  } b;
} RG_BT_ESTI_A28_FIELD_T;

#define RG_BT_ESTI_A29                            (0x74)
// Bit 1   :0      rg_esti_tb_sel                 U     RW        default = 'h0
typedef union RG_BT_ESTI_A29_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_esti_tb_sel : 2;
    unsigned int rsvd_0 : 30;
  } b;
} RG_BT_ESTI_A29_FIELD_T;

#endif

