/*******************************************************************************
 * Copyright (C) 2021 Amlogic, Inc. All rights reserved.
 ******************************************************************************/

/*****************************************************************************/
/**
 *
 * @file adlak_errcode.h
 * @brief
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   	Who				Date				Changes
 * ----------------------------------------------------------------------------
 * 1.00a shiwei.sun@amlogic.com	2021/06/05	Initial release
 * </pre>
 *
 ******************************************************************************/

#ifndef __ADLAK_ERRCODE_H__
#define __ADLAK_ERRCODE_H__

/***************************** Include Files *********************************/
#ifdef __cplusplus
extern "C" {
#endif

/************************** Constant Definitions *****************************/

/**************************Global Variable************************************/

/**************************Type Definition and Structure**********************/

enum adlak_enum_error_code {
    ADLAK_FAIL               = 1001, /*generate error code*/
    ADLAK_HARDWARE_TIMEOUT   = 1002, /*pending timer timeout*/
    ADLAK_SOFTWARE_TIMEOUT   = 1003, /*software timer timeout when inference*/
    ADLAK_INVOKE_TIMEOUT     = 1004, /*invoke wait time out*/
    ADLAK_ALLOCATE_MEM_FAIL  = 1005, /*allocate memory failed*/
    ADLAK_INVALID_PARAMS     = 1006, /* invalid params*/
    ADLAK_TASK_NUMS_EXCEEDS  = 1007, /* The task total number exceeds the preset limit*/
    ADLAK_PREPARE_CMQ_FAIL   = 1008, /* fail to prepare command queue*/
    ADLAK_CONTEXT_BUSY       = 1009, /* context is busy */
    ADLAK_INVALID_MEM_HANDLE = 1010, /* invalid mem handle*/
};
/************************** Function Prototypes ******************************/

#ifdef __cplusplus
}
#endif

#endif /* __ADLAK_ERRCODE_H__ end define*/
