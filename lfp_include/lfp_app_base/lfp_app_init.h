/*
 * @fileName: lfp_app_init.h
 * @Description: Application init
 * @Author: wytaitaislee
 * @Date: 2021-04-04 17:29:57
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-04-04 17:50:36
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