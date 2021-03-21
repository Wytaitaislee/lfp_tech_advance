/***************************************************************************************
 * @fileName: lfp_app_busybox.h
 * @Description: Simulate the realization of busybox function for debugging interaction 
                  of app code.
 * @Author: wytaitaislee
 * @Date: 2020-11-07 23:34:24
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-03-21 19:51:37
****************************************************************************************/

#ifndef __LFP_APP_BUSYBOX_H__
#define __LFP_APP_BUSYBOX_H__

#include "lfp_base.h"

#define LFP_APP_BUSYBOX_CRIT(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_CRIT, UTIL_MODULE_APP_BUSYBOX, MASK_APP_BUSYBOX, __VA_ARGS__)
#define LFP_APP_BUSYBOX_ERR(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_ERR, UTIL_MODULE_APP_BUSYBOX, MASK_APP_BUSYBOX, __VA_ARGS__)
#define LFP_APP_BUSYBOX_INFO(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_INFO, UTIL_MODULE_APP_BUSYBOX, MASK_APP_BUSYBOX, __VA_ARGS__)  

typedef LFP_INT32 (*lfp_app_busybox_proc_ptr)(LFP_INT8 iArgs, LFP_CONST LFP_INT8 **ppArgv);

typedef struct lfp_app_busybox_t
{
    LFP_CONST LFP_INT8      *pCmdName;
    LFP_CONST LFP_INT8      *pCmdHelpInfo;
    LFP_INT8                 iAuthority;
    lfp_app_busybox_proc_ptr pCallbackBusybox;
    LFP_INT8                 iArgs;
    LFP_CONST LFP_INT8       **ppArgv;
}LFP_APP_BUSYBOX_T;

/*@fn		  LFP_INT32 lfp_busybox_init(LFP_VOID)
* @brief 	  loading command modules
* @param[in]  LFP_VOID
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_busybox_init(LFP_VOID);

#endif /* end of __LFP_APP_BUSYBOX_H__ */