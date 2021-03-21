/***************************************************************************************
 * @fileName: lfp_arch_adapter_stdio.h
 * @Description: System adaptation layer, matching different arch.
 * @Author: wytaitaislee
 * @Date: 2020-08-16 16:05:58
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-03-21 20:04:36
****************************************************************************************/

#ifndef __LFP_ARCH_ADAPTER_STDIO_H__
#define __LFP_ARCH_ADAPTER_STDIO_H__

#include "lfp_base.h"

/*@fn		  LFP_INT32 lfp_arch_adapter_stdio_register(LFP_VOID)
* @brief 	  the adapter layer register -- stdio cluster register
* @param[in]  LFP_NULL
* @param[out] LFP_NULL
* @return	  LFP_OK
*/
LFP_INT32 lfp_arch_adapter_stdio_register(LFP_VOID);
#endif	/*end of __LFP_ARCH_ADAPTER_STDIO_H__ */