/*
 * @fileName: lfp_arch_adapter_time.c
 * @Description: System adaptation layer. Adapter to different time on different OS.
 * @Author: wytaitaislee
 * @Date: 2020-08-16 16:05:59
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-04-04 16:03:18
*/

#include "lfp_arch_adapter_typesdef.h"
#include "lfp_arch_abstract.h"
#include "lfp_arch_adapter.h"

#define LFP_GET_TIME_ENTRY()             (*(LFP_ARCH_ADAPTER_TIME_T*)LFP_GET_CLASS_ENTRY(time))
#define LFP_ADAPTER_TIME_INIT(FUNC)      LFP_ADAPTER_INIT(LFP_GET_TIME_ENTRY(), FUNC)

/* the definition of time cluster */
LFP_ARCH_ADAPTER1(LFP_GET_TIME_ENTRY(), sleep_ms, LFP_INT32, LFP_UINT32);
LFP_ARCH_ADAPTER1(LFP_GET_TIME_ENTRY(), sleep_s, LFP_INT32, LFP_UINT32);

/*@fn		  LFP_INT32 lfp_arch_adapter_time_register(LFP_VOID)
* @brief 	  the adapter layer register -- time cluster register
* @param[in]  LFP_NULL
* @param[out] LFP_NULL
* @return	  LFP_OK
*/
LFP_INT32 lfp_arch_adapter_time_register(LFP_VOID)
{
    LFP_ADAPTER_TIME_INIT(sleep_ms);
    LFP_ADAPTER_TIME_INIT(sleep_s);
    return LFP_OK;
}
