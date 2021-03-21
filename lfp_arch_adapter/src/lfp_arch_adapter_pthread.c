/***************************************************************************************
File name: lfp_arch_adapter_pthread.h
Description: System adaptation layer. Adapter to different pthread on different OS.
Author: wytaitaislee
Date: 2020-03-12
History: 1. create file. -- 2020-03-12
****************************************************************************************/
#include "lfp_arch_adapter_typesdef.h"
#include "lfp_arch_abstract.h"
#include "lfp_arch_adapter.h"

#define LFP_GET_PTHREAD_ENTRY()             (*(LFP_ARCH_ADAPTER_PTHREAD_T*)LFP_GET_CLASS_ENTRY(pthread))
#define LFP_ADAPTER_PTHREAD_INIT(FUNC)      LFP_ADAPTER_INIT(LFP_GET_PTHREAD_ENTRY(), FUNC)

/* the definition of pthread cluster */
LFP_ARCH_ADAPTER5(LFP_GET_PTHREAD_ENTRY(), pthread_create, LFP_INT32, LINUX_PTHREAD_HANDLE_T*, LFP_INT32, LFP_UINT32, LFP_VOID*, LFP_VOID*);
LFP_ARCH_ADAPTER1(LFP_GET_PTHREAD_ENTRY(), pthread_cancel, LFP_INT32, LINUX_PTHREAD_HANDLE_T);
LFP_ARCH_ADAPTER2(LFP_GET_PTHREAD_ENTRY(), pthread_kill, LFP_INT32, LINUX_PTHREAD_HANDLE_T, LFP_INT32);

/*@fn		  LFP_INT32 lfp_arch_adapter_pthread_register(LFP_VOID)
* @brief 	  the adapter layer register -- pthread cluster register
* @param[in]  LFP_NULL
* @param[out] LFP_NULL
* @return	  LFP_OK
*/
LFP_INT32 lfp_arch_adapter_pthread_register(LFP_VOID)
{
    LFP_ADAPTER_PTHREAD_INIT(pthread_create);
    LFP_ADAPTER_PTHREAD_INIT(pthread_cancel);
    LFP_ADAPTER_PTHREAD_INIT(pthread_kill);
    return LFP_OK;
}

