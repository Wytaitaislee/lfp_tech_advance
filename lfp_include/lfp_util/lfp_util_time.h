/***************************************************************************************
File name: lfp_util_time.h																	
Description: time base implementation											
Author: wytaitaislee																																			
Date: 2020-06-11																		
History: 1. create file. -- 2020.11.07
****************************************************************************************/
#ifndef __LFP_UTIL_TIME_H__
#define __LFP_UTIL_TIME_H__

#include "__lfp_base_typesdef.h"

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

#endif /* end of __LFP_UTIL_TIME_H__ */