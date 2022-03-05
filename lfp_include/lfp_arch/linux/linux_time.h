/***
 * @FilePath: linux_time.h
 * @Description: the standard time management on linux system.
 * @Author: wytaitaislee
 * @Date: 2021-08-27 23:29:52
 * @LastEditTime: 2022-03-05 21:20:49
 * @LastEditors: wytaitaislee
 * @Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#ifndef __LINUX_TIME_H__
#define __LINUX_TIME_H__

#include "lfp_base.h"

#define LFP_TIME_CRIT(...) \
  LFP_LOG_BASE(LOG_LEVEL_CRIT, LOG_MODULE_LINUX, MASK_TIME, __VA_ARGS__)
#define LFP_TIME_ERR(...) \
  LFP_LOG_BASE(LOG_LEVEL_ERR, LOG_MODULE_LINUX, MASK_TIME, __VA_ARGS__)
#define LFP_TIME_INFO(...) \
  LFP_LOG_BASE(LOG_LEVEL_INFO, LOG_MODULE_LINUX, MASK_TIME, __VA_ARGS__)

/*@fn		  LFP_INT32 linux_sleep_ms(LFP_UINT32 uiSleepMsSeconds);
 * @brief 	  delay milliseconds
 * @param[in]  LFP_UINT32 uiSleepMsSeconds - ms counts
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 linux_sleep_ms(LFP_UINT32 uiSleepMsSeconds);

/*@fn		  LFP_INT32 linux_sleep_s(LFP_UINT32 uiSleepSeconds);
 * @brief 	  delay seconds
 * @param[in]  LFP_UINT32 uiSleepSeconds - seconds counts
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 linux_sleep_s(LFP_UINT32 uiSleepSeconds);

/*@fn		   LFP_TIME_T linux_get_time(LFP_TIME_T *ptTime)
 * @brief 	   get the system time
 * @param[out]  LFP_TIME_T *ptTime - system time
 * @return	   LFP_TIME_T
 */
LFP_TIME_T linux_get_time(LFP_TIME_T *ptTime);

#endif /*end of __LINUX_TIME_H__ */