/*
 * @FilePath: linux_time.c
 * @Description: the time revelant management on linux system.
 * @Author: wytaitaislee
 * @Date: 2022-03-05 16:42:26
 * @LastEditTime: 2022-03-05 21:54:36
 * @LastEditors: wytaitaislee
 * Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#include "linux_time.h"

#include <time.h>
#include <unistd.h>

#include "linux_typesdef.h"

/*@fn		  LFP_INT32 linux_sleep_ms(LFP_UINT32 uiSleepMsSeconds)
 * @brief 	  delay milliseconds
 * @param[in]  LFP_UINT32 uiSleepMsSeconds - ms counts
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 linux_sleep_ms(LFP_UINT32 uiSleepMsSeconds) {
  usleep(uiSleepMsSeconds * 1000);
  return LFP_OK;
}

/*@fn		  LFP_INT32 linux_sleep_s(LFP_UINT32 uiSleepSeconds)
 * @brief 	  delay seconds
 * @param[in]  LFP_UINT32 uiSleepSeconds - seconds counts
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 linux_sleep_s(LFP_UINT32 uiSleepSeconds) {
  sleep(uiSleepSeconds);
  return LFP_OK;
}

/*@fn		   LFP_TIME_T linux_get_time(LFP_TIME_T *ptTime)
 * @brief 	   get the system time
 * @param[out]  LFP_TIME_T *ptTime - system time
 * @return	   LFP_TIME_T
 */
LFP_TIME_T linux_get_time(LFP_TIME_T *ptTime) {
  LFP_TIME_T tTime = time(NULL);

  if (ptTime) {
    *ptTime = tTime;
  }
  return tTime;
}