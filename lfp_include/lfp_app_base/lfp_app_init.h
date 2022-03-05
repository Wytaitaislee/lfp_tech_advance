/***
 * @FilePath: lfp_app_init.h
 * @Description: Application init.
 * @Author: wytaitaislee
 * @Date: 2021-08-27 23:29:52
 * @LastEditTime: 2022-03-05 21:58:01
 * @LastEditors: wytaitaislee
 * @Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#ifndef __LFP_APP_INIT_H__
#define __LFP_APP_INIT_H__
/**
 * @fn: LFP_INT32 lfp_app_init(LFP_VOID)
 * @breif: Application init main entrance.
 * @param[in] LFP_VOID
 * @param[out] NULL
 * @return {*} LFP_OK
 */
LFP_INT32 lfp_app_init(LFP_VOID);

/**
 * @fn: LFP_INT32 lfp_app_test_init(LFP_VOID)
 * @breif: app unity test main entrance.
 * @param[in] LFP_VOID
 * @param[out] NULL
 * @return {*} LFP_OK
 */
LFP_INT32 lfp_app_test_init(LFP_VOID);

#endif /* end of __LFP_APP_REGISTER_H__ */