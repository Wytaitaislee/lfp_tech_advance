/*
 * @fileName: linux_time.c
 * @Description: the time revelant management on linux system
 * @Author: wytaitaislee
 * @Date: 2021-01-31 14:52:35
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-09-05 17:03:28
*/

#include "linux_time.h"
#include "linux_typesdef.h"
#include <unistd.h>
#include <time.h>

/*@fn		  LFP_INT32 linux_sleep_ms(LFP_UINT32 uiSleepMsSeconds)
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

/*@fn		  LFP_INT32 linux_sleep_s(LFP_UINT32 uiSleepSeconds)
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

/*@fn		   LFP_TIME_T linux_get_time(LFP_TIME_T *ptTime)
* @brief 	   get the system time
* @param[out]  LFP_TIME_T *ptTime - system time 
* @return	   LFP_TIME_T
*/
LFP_TIME_T linux_get_time(LFP_TIME_T *ptTime)
{
    LFP_TIME_T tTime = time(NULL);

    if(ptTime)
    {
        *ptTime = tTime;
    }
    return tTime;
}