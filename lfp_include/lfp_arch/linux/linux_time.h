/*
 * @fileName: linux_time.h
 * @Description: the standard time management on linux system.
 * @Author: wytaitaislee
 * @Date: 2021-01-31 17:50:48
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-08-21 15:12:31
*/

#ifndef __LINUX_TIME_H__
#define __LINUX_TIME_H__

#include "lfp_base.h"

#define LFP_TIME_CRIT(...)   \
	LFP_UTIL_BASE(UTIL_LEVEL_CRIT, UTIL_MODULE_LINUX, MASK_TIME, __VA_ARGS__) 
#define LFP_TIME_ERR(...)   \
	LFP_UTIL_BASE(UTIL_LEVEL_ERR, UTIL_MODULE_LINUX, MASK_TIME, __VA_ARGS__) 
#define LFP_TIME_INFO(...)   \
	LFP_UTIL_BASE(UTIL_LEVEL_INFO, UTIL_MODULE_LINUX, MASK_TIME, __VA_ARGS__)

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

#endif	/*end of __LINUX_TIME_H__ */