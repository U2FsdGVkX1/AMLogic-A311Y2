/* SPDX-License-Identifier: GPL-2.0 */
/*
* Copyright (C) 202X Original Author (retain original author information)
* Copyright (C) 202X Amlogic, Inc. All rights reserved.
*
* Description:
*/
#ifndef _AML_BT_NOTIFY_H_
#define _AML_BT_NOTIFY_H_

#include <linux/module.h>
#include <linux/notifier.h>

int notify_bt_event(int event);
int register_bt_event_notifier(struct notifier_block *nb);
int unregister_bt_event_notifier(struct notifier_block *nb);

#endif//_AML_BT_NOTIFY_H_
