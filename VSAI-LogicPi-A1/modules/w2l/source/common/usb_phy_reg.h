/* SPDX-License-Identifier: GPL-2.0 */
/*
* Copyright (C) 202X Original Author (retain original author information)
* Copyright (C) 202X Amlogic, Inc. All rights reserved.
*
* Description:
*/
#ifdef USB_PHY_REG
#else
#define USB_PHY_REG

#define PMA_CFG_IN_A0                             (0x0)
// Bit 11  :0      rg_pd                          U     RW        default = 'h0
// Bit 12          rg_rstn_fls_cdr                U     RW        default = 'h1
// Bit 13          rg_rstn_hs_cdr                 U     RW        default = 'h1
// Bit 14          rg_clkdiv_rstn                 U     RW        default = 'h1
// Bit 31  :15     rg_pll_cfg                     U     RW        default = 'h800a
typedef union PMA_CFG_IN_A0_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_pd : 12;
    unsigned int rg_rstn_fls_cdr : 1;
    unsigned int rg_rstn_hs_cdr : 1;
    unsigned int rg_clkdiv_rstn : 1;
    unsigned int rg_pll_cfg : 17;
  } b;
} PMA_CFG_IN_A0_FIELD_T;

#define PMA_CFG_IN_A1                             (0x4)
// Bit 9   :0      rg_tx_cfg                      U     RW        default = 'h3
typedef union PMA_CFG_IN_A1_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_tx_cfg : 10;
    unsigned int rsvd_0 : 22;
  } b;
} PMA_CFG_IN_A1_FIELD_T;

#define PMA_CFG_IN_A2                             (0x8)
// Bit 23  :0      ro_status_calcode              U     RO        default = 'h0
// Bit 24          ro_prbs_rslt                   U     RO        default = 'h0
// Bit 25          ro_hs_squelch                  U     RO        default = 'h0
// Bit 26          ro_hs_disc                     U     RO        default = 'h0
// Bit 30          ro_cal_en_flag                 U     RO        default = 'h0
// Bit 31          ro_phy_rdy_sync                U     RO        default = 'h0
typedef union PMA_CFG_IN_A2_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_status_calcode : 24;
    unsigned int ro_prbs_rslt : 1;
    unsigned int ro_hs_squelch : 1;
    unsigned int ro_hs_disc : 1;
    unsigned int rsvd_0 : 3;
    unsigned int ro_cal_en_flag : 1;
    unsigned int ro_phy_rdy_sync : 1;
  } b;
} PMA_CFG_IN_A2_FIELD_T;

#define PMA_CFG_IN_A3                             (0xc)
// Bit 9   :0      rg_rx_cfg                      U     RW        default = 'h0
typedef union PMA_CFG_IN_A3_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_rx_cfg : 10;
    unsigned int rsvd_0 : 22;
  } b;
} PMA_CFG_IN_A3_FIELD_T;

#define PMA_CFG_IN_A4                             (0x10)
// Bit 23  :0      rg_cal_code                    U     RW        default = 'h0
// Bit 24          rg_cal_en                      U     RW        default = 'h0
// Bit 25          rg_cal_rstn                    U     RW        default = 'h0
// Bit 27          rg_byp_pu_mode                 U     RW        default = 'h0
// Bit 31  :28     rg_bias_trim                   U     RW        default = 'h0
typedef union PMA_CFG_IN_A4_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_cal_code : 24;
    unsigned int rg_cal_en : 1;
    unsigned int rg_cal_rstn : 1;
    unsigned int rsvd_0 : 1;
    unsigned int rg_byp_pu_mode : 1;
    unsigned int rg_bias_trim : 4;
  } b;
} PMA_CFG_IN_A4_FIELD_T;

#define PMA_CFG_IN_A5                             (0x14)
// Bit 21  :0      rg_pll_perfcfg                 U     RW        default = 'h8037c
// Bit 31  :24     rg_obs                         U     RW        default = 'h0
typedef union PMA_CFG_IN_A5_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_pll_perfcfg : 22;
    unsigned int rsvd_0 : 2;
    unsigned int rg_obs : 8;
  } b;
} PMA_CFG_IN_A5_FIELD_T;

#define REG_A6                                    (0x18)
// Bit 7   :0      rg_us_cntr_thresh              U     RW        default = 'h17
// Bit 11  :8      rg_bypass_disc_ctrl            U     RW        default = 'h0
// Bit 20          rg_rstn_rx_sm                  U     RW        default = 'h0
// Bit 21          rg_rstn_tx_sm                  U     RW        default = 'h0
// Bit 22          rg_lpbk_dis_xmit               U     RW        default = 'h0
// Bit 23          rg_lpbk                        U     RW        default = 'h0
// Bit 31          rg_hub_extra_bit_ctrl          U     RW        default = 'h1
typedef union REG_A6_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_us_cntr_thresh : 8;
    unsigned int rg_bypass_disc_ctrl : 4;
    unsigned int rsvd_0 : 8;
    unsigned int rg_rstn_rx_sm : 1;
    unsigned int rg_rstn_tx_sm : 1;
    unsigned int rg_lpbk_dis_xmit : 1;
    unsigned int rg_lpbk : 1;
    unsigned int rsvd_1 : 7;
    unsigned int rg_hub_extra_bit_ctrl : 1;
  } b;
} REG_A6_FIELD_T;

#define REG_A7                                    (0x1c)
// Bit 3   :0      rg_hs_cdr_tap_sel              U     RW        default = 'h0
// Bit 11  :4      rg_rxerr_to_val                U     RW        default = 'hff
// Bit 14  :12     rg_fls_sync_mask_val           U     RW        default = 'h4
// Bit 15          rg_host_tristate               U     RW        default = 'h0
// Bit 20  :17     rg_rxerr_ta_val                U     RW        default = 'hf
typedef union REG_A7_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_hs_cdr_tap_sel : 4;
    unsigned int rg_rxerr_to_val : 8;
    unsigned int rg_fls_sync_mask_val : 3;
    unsigned int rg_host_tristate : 1;
    unsigned int rsvd_0 : 1;
    unsigned int rg_rxerr_ta_val : 4;
    unsigned int rsvd_1 : 11;
  } b;
} REG_A7_FIELD_T;

#define REG_A8                                    (0x20)
// Bit 4   :0      rg_prbs_cfg_tmp                U     RW        default = 'h0
// Bit 5           rg_prbs_err_inj_reg_to_24m     U     RW        default = 'h0
// Bit 7           rg_en_rxerr_to_mode            U     RW        default = 'h0
// Bit 31  :8      rg_prbs_00                     U     RW        default = 'h4
typedef union REG_A8_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_prbs_cfg_tmp : 5;
    unsigned int rg_prbs_err_inj_reg_to_24m : 1;
    unsigned int rsvd_0 : 1;
    unsigned int rg_en_rxerr_to_mode : 1;
    unsigned int rg_prbs_00 : 24;
  } b;
} REG_A8_FIELD_T;

#define REG_A9                                    (0x24)
// Bit 31  :0      rg_prbs_01                     U     RW        default = 'h0
typedef union REG_A9_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_prbs_01 : 32;
  } b;
} REG_A9_FIELD_T;

#define REG_A10                                   (0x28)
// Bit 31  :0      rg_prbs_02                     U     RW        default = 'h0
typedef union REG_A10_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_prbs_02 : 32;
  } b;
} REG_A10_FIELD_T;

#define REG_A11                                   (0x2c)
// Bit 31  :0      rg_prbs_03                     U     RW        default = 'h0
typedef union REG_A11_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_prbs_03 : 32;
  } b;
} REG_A11_FIELD_T;

#define REG_A12                                   (0x30)
// Bit 31  :0      rg_prbs_04                     U     RW        default = 'h0
typedef union REG_A12_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_prbs_04 : 32;
  } b;
} REG_A12_FIELD_T;

#define REG_A13                                   (0x34)
// Bit 7   :0      rg_prbs_05                     U     RW        default = 'h0
// Bit 14          rg_load_stat_sync_0            U     RW        default = 'h0
// Bit 15          rg_load_pma_sync_0             U     RW        default = 'h0
// Bit 20  :16     rg_hs_sync_mask_val            U     RW        default = 'h8
// Bit 21          rg_clear_hold_hs_dis           U     RW        default = 'h0
// Bit 22          rg_bypass_host_disc_val        U     RW        default = 'h0
// Bit 23          rg_bypass_host_disc_en         U     RW        default = 'h0
// Bit 31  :24     rg_bypass_reg_0                U     RW        default = 'h0
typedef union REG_A13_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_prbs_05 : 8;
    unsigned int rsvd_0 : 6;
    unsigned int rg_load_stat_sync_0 : 1;
    unsigned int rg_load_pma_sync_0 : 1;
    unsigned int rg_hs_sync_mask_val : 5;
    unsigned int rg_clear_hold_hs_dis : 1;
    unsigned int rg_bypass_host_disc_val : 1;
    unsigned int rg_bypass_host_disc_en : 1;
    unsigned int rg_bypass_reg_0 : 8;
  } b;
} REG_A13_FIELD_T;

#define REG_A14                                   (0x38)
// Bit 7   :0      rg_bypass_reg_1                U     RW        default = 'h0
// Bit 23  :8      rg_bypass_ctrl                 U     RW        default = 'h3000
// Bit 31  :24     rg_pma_reg_cfg                 U     RW        default = 'h0
typedef union REG_A14_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_bypass_reg_1 : 8;
    unsigned int rg_bypass_ctrl : 16;
    unsigned int rg_pma_reg_cfg : 8;
  } b;
} REG_A14_FIELD_T;

#define PLL_A16                                   (0x40)
// Bit 1   :0      rg_usbpll_bias_cp_adj          U     RW        default = 'h0
// Bit 2           rg_usbpll_cp_en                U     RW        default = 'h1
// Bit 6   :3      rg_usbpll_cp_icp_adj           U     RW        default = 'he
// Bit 9   :7      rg_usbpll_cp_iea_adj           U     RW        default = 'h5
// Bit 10          rg_usbpll_cp_offset_enb        U     RW        default = 'h1
// Bit 11          rg_usbpll_en                   U     RW        default = 'h0
// Bit 20  :12     rg_usbpll_fbdiv_m              U     RW        default = 'h60
// Bit 22  :21     rg_usbpll_fr_adj               U     RW        default = 'h0
// Bit 23          rg_usbpll_fr_en                U     RW        default = 'h0
// Bit 24          rg_usbpll_ldo_ref_sel          U     RW        default = 'h0
// Bit 25          rg_usbpll_lk_lock_f            U     RW        default = 'h0
// Bit 27  :26     rg_usbpll_lk_locklong          U     RW        default = 'h1
// Bit 28          rg_usbpll_lk_rst               U     RW        default = 'h0
// Bit 30  :29     rg_usbpll_lk_w_sel             U     RW        default = 'h0
// Bit 31          rg_usbpll_lock                 U     RO        default = 'h0
typedef union PLL_A16_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_usbpll_bias_cp_adj : 2;
    unsigned int rg_usbpll_cp_en : 1;
    unsigned int rg_usbpll_cp_icp_adj : 4;
    unsigned int rg_usbpll_cp_iea_adj : 3;
    unsigned int rg_usbpll_cp_offset_enb : 1;
    unsigned int rg_usbpll_en : 1;
    unsigned int rg_usbpll_fbdiv_m : 9;
    unsigned int rg_usbpll_fr_adj : 2;
    unsigned int rg_usbpll_fr_en : 1;
    unsigned int rg_usbpll_ldo_ref_sel : 1;
    unsigned int rg_usbpll_lk_lock_f : 1;
    unsigned int rg_usbpll_lk_locklong : 2;
    unsigned int rg_usbpll_lk_rst : 1;
    unsigned int rg_usbpll_lk_w_sel : 2;
    unsigned int rg_usbpll_lock : 1;
  } b;
} PLL_A16_FIELD_T;

#define PLL_A17                                   (0x44)
// Bit 3   :0      rg_usbpll_r2_cnt               U     RW        default = 'h2
// Bit 9   :5      rg_usbpll_refdiv_n             U     RW        default = 'h1
// Bit 17  :10     rg_usbpll_reve                 U     RW        default = 'h0
// Bit 18          rg_usbpll_rst                  U     RW        default = 'h0
// Bit 20  :19     rg_usbpll_vref_adj_in          U     RW        default = 'h0
// Bit 22  :21     rg_usbpll_pfd_dt_adj           U     RW        default = 'h0
// Bit 23          rg_usb2_mpll_en_ctrl           U     RW        default = 'h0
typedef union PLL_A17_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_usbpll_r2_cnt : 4;
    unsigned int rsvd_0 : 1;
    unsigned int rg_usbpll_refdiv_n : 5;
    unsigned int rg_usbpll_reve : 8;
    unsigned int rg_usbpll_rst : 1;
    unsigned int rg_usbpll_vref_adj_in : 2;
    unsigned int rg_usbpll_pfd_dt_adj : 2;
    unsigned int rg_usb2_mpll_en_ctrl : 1;
    unsigned int rsvd_1 : 8;
  } b;
} PLL_A17_FIELD_T;

#define PLL_A19                                   (0x4c)
// Bit 9   :0      ro_usb2_mppll_reg_out          U     RO        default = 'h0
// Bit 30          ro_usb2_mppll_lock_1           U     RO        default = 'h0
// Bit 31          ro_usb2_mppll_lock_dig_1       U     RO        default = 'h0
typedef union PLL_A19_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_usb2_mppll_reg_out : 10;
    unsigned int rsvd_0 : 20;
    unsigned int ro_usb2_mppll_lock_1 : 1;
    unsigned int ro_usb2_mppll_lock_dig_1 : 1;
  } b;
} PLL_A19_FIELD_T;

#define USB_PHY_CFG0_A20                          (0x50)
// Bit 0           rg_orw_usb2_otg_iddet_en       U     RW        default = 'h0
// Bit 3   :1      rg_orw_usb2_otg_vbus_trim      U     RW        default = 'h4
// Bit 4           rg_orw_usb2_otg_vbusdet_en     U     RW        default = 'h1
// Bit 5           rg_orw_usb2_amon_en            U     RW        default = 'h0
// Bit 6           rg_orw_usb2_cal_code_r5        U     RW        default = 'h0
// Bit 7           rg_orw_bypass_otg_det          U     RW        default = 'h0
// Bit 8           rg_orw_usb2_dmon_en            U     RW        default = 'h0
// Bit 12  :9      rg_orw_usb2_dmon_sel           U     RW        default = 'hf
// Bit 13          rg_orw_usb2_edgedrv_en         U     RW        default = 'h0
// Bit 15  :14     rg_orw_usb2_edgedrv_trim       U     RW        default = 'h0
// Bit 20  :16     rg_orw_usb2_bgr_adj            U     RW        default = 'h0
// Bit 21          rg_orw_usb2_bgr_start          U     RW        default = 'h0
// Bit 23  :22     rg_squelch_sel                 U     RW        default = 'h0
// Bit 28  :24     rg_orw_usb2_bgr_vref           U     RW        default = 'h0
// Bit 30  :29     rg_orw_usb2_bgr_dbg            U     RW        default = 'h0
// Bit 31          rg_orw_bypass_cal_code_r5      U     RW        default = 'h0
typedef union USB_PHY_CFG0_A20_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_orw_usb2_otg_iddet_en : 1;
    unsigned int rg_orw_usb2_otg_vbus_trim : 3;
    unsigned int rg_orw_usb2_otg_vbusdet_en : 1;
    unsigned int rg_orw_usb2_amon_en : 1;
    unsigned int rg_orw_usb2_cal_code_r5 : 1;
    unsigned int rg_orw_bypass_otg_det : 1;
    unsigned int rg_orw_usb2_dmon_en : 1;
    unsigned int rg_orw_usb2_dmon_sel : 4;
    unsigned int rg_orw_usb2_edgedrv_en : 1;
    unsigned int rg_orw_usb2_edgedrv_trim : 2;
    unsigned int rg_orw_usb2_bgr_adj : 5;
    unsigned int rg_orw_usb2_bgr_start : 1;
    unsigned int rg_squelch_sel : 2;
    unsigned int rg_orw_usb2_bgr_vref : 5;
    unsigned int rg_orw_usb2_bgr_dbg : 2;
    unsigned int rg_orw_bypass_cal_code_r5 : 1;
  } b;
} USB_PHY_CFG0_A20_FIELD_T;

#define USB_PHY_CFG1_A21                          (0x54)
// Bit 0           rg_orw_usb2_bgr_force          U     RW        default = 'h0
// Bit 1           rg_orw_usb2_cal_ack_en         U     RW        default = 'h1
// Bit 2           rg_orw_usb2_otg_aca_en         U     RW        default = 'h1
// Bit 3           rg_orw_usb2_tx_strg_pd         U     RW        default = 'h0
// Bit 5   :4      rg_orw_usb2_otg_aca_trim       U     RW        default = 'h2
// Bit 7           rg_hs_cdr_sel                  U     RW        default = 'h0
// Bit 15  :8      rg_hs_cdr_ctrl                 U     RW        default = 'h0
// Bit 19  :16     rg_bypass_utmi_ctrl            U     RW        default = 'h0
// Bit 25  :20     rg_bypass_utmi_reg             U     RW        default = 'h0
// Bit 29  :28     rg_bypass_chirp_ctrl           U     RW        default = 'h0
// Bit 31  :30     rg_bypass_chirp_reg            U     RW        default = 'h0
typedef union USB_PHY_CFG1_A21_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_orw_usb2_bgr_force : 1;
    unsigned int rg_orw_usb2_cal_ack_en : 1;
    unsigned int rg_orw_usb2_otg_aca_en : 1;
    unsigned int rg_orw_usb2_tx_strg_pd : 1;
    unsigned int rg_orw_usb2_otg_aca_trim : 2;
    unsigned int rsvd_0 : 1;
    unsigned int rg_hs_cdr_sel : 1;
    unsigned int rg_hs_cdr_ctrl : 8;
    unsigned int rg_bypass_utmi_ctrl : 4;
    unsigned int rg_bypass_utmi_reg : 6;
    unsigned int rsvd_1 : 2;
    unsigned int rg_bypass_chirp_ctrl : 2;
    unsigned int rg_bypass_chirp_reg : 2;
  } b;
} USB_PHY_CFG1_A21_FIELD_T;

#define USB_PHY_STATUS_A22                        (0x58)
// Bit 0           ro_iro_usb2_otg_id_dig         U     RO        default = 'h0
// Bit 1           ro_iro_usb2_otg_sess_vld       U     RO        default = 'h0
// Bit 2           ro_iro_usb2_otg_vbus_vld       U     RO        default = 'h0
// Bit 3           ro_iro_usb2_otg_aca_iddig      U     RO        default = 'h0
// Bit 11  :4      ro_hs_cdr_state                U     RO        default = 'h0
typedef union USB_PHY_STATUS_A22_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_iro_usb2_otg_id_dig : 1;
    unsigned int ro_iro_usb2_otg_sess_vld : 1;
    unsigned int ro_iro_usb2_otg_vbus_vld : 1;
    unsigned int ro_iro_usb2_otg_aca_iddig : 1;
    unsigned int ro_hs_cdr_state : 8;
    unsigned int rsvd_0 : 20;
  } b;
} USB_PHY_STATUS_A22_FIELD_T;

#define REG_A23                                   (0x5c)
// Bit 0           rg_orw_usb2_bgr_en             U     RW        default = 'h0
// Bit 6   :1      rg_orw_test_bus_sel            U     RW        default = 'h0
// Bit 7           rg_orw_test_bus_en             U     RW        default = 'h0
// Bit 8           rg_pcs_sel                     U     RW        default = 'h0
// Bit 9           rg_sel_cdr                     U     RW        default = 'h0
// Bit 11  :10     rg_new_hs_disc_ctrl            U     RW        default = 'h0
// Bit 15  :12     rg_ldo_ctrl                    U     RW        default = 'h8
// Bit 21  :16     rg_disc_debounce_cfg           U     RW        default = 'h1
// Bit 22          usb2_otg_id_sel                U     RW        default = 'h1
typedef union REG_A23_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_orw_usb2_bgr_en : 1;
    unsigned int rg_orw_test_bus_sel : 6;
    unsigned int rg_orw_test_bus_en : 1;
    unsigned int rg_pcs_sel : 1;
    unsigned int rg_sel_cdr : 1;
    unsigned int rg_new_hs_disc_ctrl : 2;
    unsigned int rg_ldo_ctrl : 4;
    unsigned int rg_disc_debounce_cfg : 6;
    unsigned int usb2_otg_id_sel : 1;
    unsigned int rsvd_0 : 9;
  } b;
} REG_A23_FIELD_T;

#endif

