/***
 * @FilePath: lfp_busybox.h
 * @Description: Simulate the realization of busybox function for debugging
 interaction of app code.
 * @Author: wytaitaislee
 * @Date: 2021-08-27 23:29:52
 * @LastEditTime: 2022-03-05 21:57:13
 * @LastEditors: wytaitaislee
 * @Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#ifndef __LFP_APP_BUSYBOX_H__
#define __LFP_APP_BUSYBOX_H__

#include "lfp_base.h"

#define LFP_BUSYBOX_CRIT(...) \
  LFP_LOG_BASE(LOG_LEVEL_ERR, LOG_MODULE_BUSYBOX, MASK_BUSYBOX, __VA_ARGS__)
#define LFP_BUSYBOX_ERR(...) \
  LFP_LOG_BASE(LOG_LEVEL_ERR, LOG_MODULE_BUSYBOX, MASK_BUSYBOX, __VA_ARGS__)
#define LFP_BUSYBOX_INFO(...) \
  LFP_LOG_BASE(LOG_LEVEL_ERR, LOG_MODULE_BUSYBOX, MASK_BUSYBOX, __VA_ARGS__)

typedef LFP_INT32 (*lfp_busybox_proc_ptr)(LFP_INT8 iArgs,
                                          LFP_CONST LFP_INT8 **ppArgv);

typedef struct lfp_busybox_t {
  LFP_CONST LFP_INT8 *pCmdName;
  LFP_CONST LFP_INT8 *pCmdHelpInfo;
  LFP_INT8 iAuthority;
  lfp_busybox_proc_ptr pCallbackBusybox;
  LFP_INT8 iArgs;
  LFP_CONST LFP_INT8 **ppArgv;
} LFP_BUSYBOX_T;

/*@fn		  LFP_INT32 lfp_busybox_init(LFP_VOID)
 * @brief 	  loading command modules
 * @param[in]  LFP_VOID
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 lfp_busybox_init(LFP_VOID);

#endif /* end of __LFP_APP_BUSYBOX_H__ */