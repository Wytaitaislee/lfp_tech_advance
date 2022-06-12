

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

#ifndef __LFP_APP_BUSYBOX_SERVER_H__
#define __LFP_APP_BUSYBOX_SERVER_H__

#include "lfp_base.h"
#include "lfp_busybox.h"

/*@fn		  LFP_INT32 lfp_busybox_server(LFP_VOID)
 * @brief 	  busybox server init
 * @param[in]  LFP_VOID
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 lfp_busybox_server(LFP_VOID);

#endif /* end of __LFP_APP_BUSYBOX_SERVER_H__ */
