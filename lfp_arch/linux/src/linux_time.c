/***************************************************************************************
File name: linux_time.c
Description: the time revelant management on linux system
Author: wytaitaislee
Date: 2020-06-11
History: 1. create file. -- 2020-06-11
****************************************************************************************/

#include "linux_time.h"

/*@fn		  LFP_INT32 linux_sleep_ms(LFP_UINT32 uiSleepMsSeconds);
* @brief 	  delay milliseconds
* @param[in]  LFP_UINT32 uiSleepMsSeconds - ms counts
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/	
LFP_INT32 linux_sleep_ms(LFP_UINT32 uiSleepMsSeconds)
{
    usleep(uiSleepMsSeconds * 1000);
    return LFP_OK;
}

/*@fn		  LFP_INT32 linux_sleep_s(LFP_UINT32 uiSleepSeconds);
* @brief 	  delay seconds
* @param[in]  LFP_UINT32 uiSleepSeconds - seconds counts
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_sleep_s(LFP_UINT32 uiSleepSeconds)
{
    sleep(uiSleepSeconds);
    return LFP_OK;
}