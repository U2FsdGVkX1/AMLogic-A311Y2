/* SPDX-License-Identifier: GPL-2.0 */
/*
* Copyright (C) 202X Original Author (retain original author information)
* Copyright (C) 202X Amlogic, Inc. All rights reserved.
*
* Description:
*/
#ifdef USB2_PHY_REG
#else
#define USB2_PHY_REG

#define USB2_PHY_REG_A0                           (0x20)
// Bit 0           rg_host_device                 U     RW        default = 'h1
// Bit 1           rg_power_ok                    U     RW        default = 'h1
// Bit 2           rg_hast_mode                   U     RW        default = 'h0
// Bit 3           rg_por                         U     RW        default = 'h1
// Bit 4           rg_idpullup0                   U     RW        default = 'h0
// Bit 5           rg_drvvbus0                    U     RW        default = 'h0
typedef union USB2_PHY_REG_A0_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rg_host_device : 1;
    unsigned int rg_power_ok : 1;
    unsigned int rg_hast_mode : 1;
    unsigned int rg_por : 1;
    unsigned int rg_idpullup0 : 1;
    unsigned int rg_drvvbus0 : 1;
    unsigned int rsvd_0 : 26;
  } b;
} USB2_PHY_REG_A0_FIELD_T;

#define USB2_PHY_REG_A1                           (0x24)
// Bit 0           ro_phy_rdy                     U     RO        default = 'h0
// Bit 1           ro_iddig0                      U     RO        default = 'h0
// Bit 2           ro_otgsessvld0                 U     RO        default = 'h0
// Bit 3           ro_vbusvalid0                  U     RO        default = 'h0
typedef union USB2_PHY_REG_A1_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int ro_phy_rdy : 1;
    unsigned int ro_iddig0 : 1;
    unsigned int ro_otgsessvld0 : 1;
    unsigned int ro_vbusvalid0 : 1;
    unsigned int rsvd_0 : 28;
  } b;
} USB2_PHY_REG_A1_FIELD_T;

#define USB2_PHY_REG_A2                           (0x80)
// Bit 0           pre_ls_bypass                  U     RW        default = 'h0
// Bit 8           u2p0_pb_oca                    U     RW        default = 'h0
// Bit 14  :13     vbus_ext                       U     RW        default = 'h0
typedef union USB2_PHY_REG_A2_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int pre_ls_bypass : 1;
    unsigned int rsvd_0 : 7;
    unsigned int u2p0_pb_oca : 1;
    unsigned int rsvd_1 : 4;
    unsigned int vbus_ext : 2;
    unsigned int rsvd_2 : 17;
  } b;
} USB2_PHY_REG_A2_FIELD_T;

#define USB2_PHY_REG_A3                           (0x84)
// Bit 1   :0      cfg1_reg                       U     RW        default = 'h0
// Bit 31  :24     divider_cnt                    U     RW        default = 'h9
typedef union USB2_PHY_REG_A3_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int cfg1_reg : 2;
    unsigned int rsvd_0 : 22;
    unsigned int divider_cnt : 8;
  } b;
} USB2_PHY_REG_A3_FIELD_T;

#define USB2_PHY_REG_A4                           (0x88)
typedef union USB2_PHY_REG_A4_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rsvd_0 : 32;
  } b;
} USB2_PHY_REG_A4_FIELD_T;

#define USB2_PHY_REG_A5                           (0x8c)
typedef union USB2_PHY_REG_A5_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rsvd_0 : 32;
  } b;
} USB2_PHY_REG_A5_FIELD_T;

#define USB2_PHY_REG_A6                           (0x90)
// Bit 4           phy_mux                        U     RW        default = 'h0
typedef union USB2_PHY_REG_A6_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rsvd_0 : 4;
    unsigned int phy_mux : 1;
    unsigned int rsvd_1 : 27;
  } b;
} USB2_PHY_REG_A6_FIELD_T;

#define USB2_PHY_REG_A7                           (0x94)
typedef union USB2_PHY_REG_A7_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rsvd_0 : 32;
  } b;
} USB2_PHY_REG_A7_FIELD_T;

#define USB2_PHY_REG_A8                           (0x98)
typedef union USB2_PHY_REG_A8_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rsvd_0 : 32;
  } b;
} USB2_PHY_REG_A8_FIELD_T;

#define USB2_PHY_REG_A9                           (0x9c)
typedef union USB2_PHY_REG_A9_FIELD
{
  unsigned int data;
  struct
  {
    unsigned int rsvd_0 : 32;
  } b;
} USB2_PHY_REG_A9_FIELD_T;

#endif

