/************************************************************************************
 * @fileName: lfp_arch_adapter.c
 * @Description: the system adapter functions implementations.
 * @Author: wytaitaislee
 * @Date: 2020-08-16 16:05:58
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-03-21 19:34:45
 ************************************************************************************/
#include "lfp_arch_adapter.h"
#include "lfp_arch_adapter_fileio.h"
#include "lfp_arch_adapter_mutex.h"
#include "lfp_arch_adapter_pthread.h"
#include "lfp_arch_adapter_semaphore.h"
#include "lfp_arch_adapter_socket.h"
#include "lfp_arch_adapter_stdio.h"
#include "lfp_arch_adapter_time.h"

LFP_ARCH_ADAPTER_OS_T g_ArchAdapter = {0};

LFP_ARCH_ADAPTER_PTHREAD_T* lfp_get_arch_adapter_pthread_entry(LFP_VOID)
{
    return &g_ArchAdapter.struArchAdapterPthread;
}

LFP_ARCH_ADAPTER_MUTEX_T* lfp_get_arch_adapter_mutex_entry(LFP_VOID)
{
    return &g_ArchAdapter.struArchAdapterMutex;
}

LFP_ARCH_ADAPTER_SEMAPHORE_T* lfp_get_arch_adapter_semaphore_entry(LFP_VOID)
{
    return &g_ArchAdapter.struArchAdapterSem;
}

LFP_ARCH_ADAPTER_FILEIO_T* lfp_get_arch_adapter_fileio_entry(LFP_VOID)
{
    return &g_ArchAdapter.struArchAdapterFileio;
}

LFP_ARCH_ADAPTER_STDIO_T* lfp_get_arch_adapter_stdio_entry(LFP_VOID)
{
    return &g_ArchAdapter.struArchAdapterStdio;
}

LFP_ARCH_ADAPTER_SOCKET_T* lfp_get_arch_adapter_socket_entry(LFP_VOID)
{
    return &g_ArchAdapter.struArchAdapterSocket;
}

LFP_ARCH_ADAPTER_TIME_T* lfp_get_arch_adapter_time_entry(LFP_VOID)
{
    return &g_ArchAdapter.struArchAdapterTime;
}

/*@fn		  LFP_STATIC LFP_CODE LFP_INT32 (*lfp_adapter_register[])(LFP_VOID)...
* @brief 	  the adapter layer register -- the main register entrance, all register cluster.
* @param[in]  LFP_NULL
* @param[out] LFP_NULL
* @return	  LFP_OK
*/
LFP_STATIC LFP_CODE LFP_INT32 (*lfp_adapter_register[])(LFP_VOID) = 
{
    lfp_arch_adapter_pthread_register,
    lfp_arch_adapter_mutex_register,
    lfp_arch_adapter_semaphore_register,
    lfp_arch_adapter_fileio_register,
    lfp_arch_adapter_stdio_register,
    lfp_arch_adapter_socket_register,
    lfp_arch_adapter_time_register,
};

/*@fn		  LFP_INT32 lfp_arch_adapter_init(LFP_VOID)
* @brief 	  the adapter layer register.
* @param[in]  LFP_NULL
* @param[out] LFP_NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_arch_adapter_init(LFP_VOID)
{
    LFP_INT32 iRegisterModules = 0;

    for(iRegisterModules = 0; iRegisterModules < LFP_NELEMENTS(lfp_adapter_register); iRegisterModules++)
    {
        if(LFP_NULL != lfp_adapter_register[iRegisterModules])
        {
            lfp_adapter_register[iRegisterModules]();
        }
    }
    return LFP_OK;
}
