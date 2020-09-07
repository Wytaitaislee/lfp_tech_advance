/***************************************************************************************
File name: __lfp_util_timer.h																	
Description: time base implementation											
Author: wytaitaislee																	
Version: V1.0.0																			
Date: 2020-06-11																		
History: 1. create file. -- 2020-06-11
****************************************************************************************/
#ifndef __LFP_UTIL_TIMER_H__
#define __LFP_UTIL_TIMER_H__

/*@fn		  LFP_INT32 lfp_sleep_ms(LFP_UINT32 uiSleepMsSeconds);
* @brief 	  delay milliseconds
* @param[in]  LFP_UINT32 uiSleepMsSeconds - ms counts
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/	
LFP_INT32 lfp_sleep_ms(LFP_UINT32 uiSleepMsSeconds);

/*@fn		  LFP_INT32 lfp_sleep_s(LFP_UINT32 uiSleepSeconds);
* @brief 	  delay seconds
* @param[in]  LFP_UINT32 uiSleepSeconds - seconds counts
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_sleep_s(LFP_UINT32 uiSleepSeconds);

#endif /* end of __LFP_UTIL_TIMER_H__ */