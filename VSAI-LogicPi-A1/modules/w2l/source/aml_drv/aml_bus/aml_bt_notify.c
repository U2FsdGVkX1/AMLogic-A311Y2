/* SPDX-License-Identifier: GPL-2.0 */
/*
* Copyright (C) 202X Original Author (retain original author information)
* Copyright (C) 202X Amlogic, Inc. All rights reserved.
*
* Description:
*/
#include "aml_bt_notify.h"

static BLOCKING_NOTIFIER_HEAD(bt_event_notifier_list);

int notify_bt_event(int event)
{
    return blocking_notifier_call_chain(&bt_event_notifier_list, event, NULL);
}
EXPORT_SYMBOL_GPL(notify_bt_event);

int register_bt_event_notifier(struct notifier_block *nb)
{
    return blocking_notifier_chain_register(&bt_event_notifier_list, nb);
}
EXPORT_SYMBOL_GPL(register_bt_event_notifier);

int unregister_bt_event_notifier(struct notifier_block *nb)
{
    return blocking_notifier_chain_unregister(&bt_event_notifier_list, nb);
}
EXPORT_SYMBOL_GPL(unregister_bt_event_notifier);

