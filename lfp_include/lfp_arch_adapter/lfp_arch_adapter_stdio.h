/***************************************************************************************
File name: lfp_arch_adapter_stdio.h
Description: System adaptation layer, matching different arch.
Author: wytaitaislee
Version: V1.0.0
Date: 2020-06-07
History: 1. create file. -- 2020-06-07
****************************************************************************************/

#ifndef __LFP_ARCH_ADAPTER_STDIO_H__
#define __LFP_ARCH_ADAPTER_STDIO_H__

#include "lfp_arch_abstract.h"

/*@fn		  LFP_INT32 lfp_arch_adapter_stdio_register(LFP_VOID)
* @brief 	  the adapter layer register -- stdio cluster register
* @param[in]  LFP_NULL
* @param[out] LFP_NULL
* @return	  LFP_OK
*/
LFP_INT32 lfp_arch_adapter_stdio_register(LFP_VOID);
#endif	/*end of __LFP_ARCH_ADAPTER_STDIO_H__ */