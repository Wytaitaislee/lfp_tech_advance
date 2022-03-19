/*
 * @FilePath: lfp_arch_adapter.c
 * @Description: the system adapter functions implementations.
 * @Author: wytaitaislee
 * @Date: 2021-08-27 23:29:52
 * @LastEditTime: 2022-03-19 19:16:20
 * @LastEditors: wytaitaislee
 * Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#include "lfp_arch_adapter.h"

#include "lfp_arch_adapter_fileio.h"
#include "lfp_arch_adapter_mutex.h"
#include "lfp_arch_adapter_pthread.h"
#include "lfp_arch_adapter_semaphore.h"
#include "lfp_arch_adapter_socket.h"
#include "lfp_arch_adapter_stdio.h"
#include "lfp_arch_adapter_time.h"

LFP_ARCH_ADAPTER_OS_T g_ArchAdapter = {0};

/*@fn		  LFP_ARCH_ADAPTER_PTHREAD_T*
 * lfp_get_arch_adapter_pthread_entry(LFP_VOID)
 * @brief 	  get the pthread function ptr entry.
 * @param[in]      LFP_NULL
 * @param[out]     LFP_NULL
 * @return	  LFP_ARCH_ADAPTER_PTHREAD_T*
 */
LFP_ARCH_ADAPTER_PTHREAD_T* lfp_get_arch_adapter_pthread_entry(LFP_VOID) {
    return &g_ArchAdapter.struArchAdapterPthread;
}

/*@fn		  LFP_ARCH_ADAPTER_MUTEX_T*
 * lfp_get_arch_adapter_mutex_entry(LFP_VOID)
 * @brief 	  get the mutex function ptr entry.
 * @param[in]      LFP_NULL
 * @param[out]     LFP_NULL
 * @return	  LFP_ARCH_ADAPTER_MUTEX_T*
 */
LFP_ARCH_ADAPTER_MUTEX_T* lfp_get_arch_adapter_mutex_entry(LFP_VOID) {
    return &g_ArchAdapter.struArchAdapterMutex;
}

/*@fn		  LFP_ARCH_ADAPTER_SEMAPHORE_T*
 * lfp_get_arch_adapter_semaphore_entry(LFP_VOID)
 * @brief 	  get the semaphore function ptr entry.
 * @param[in]      LFP_NULL
 * @param[out]     LFP_NULL
 * @return	  LFP_ARCH_ADAPTER_SEMAPHORE_T*
 */
LFP_ARCH_ADAPTER_SEMAPHORE_T* lfp_get_arch_adapter_semaphore_entry(LFP_VOID) {
    return &g_ArchAdapter.struArchAdapterSem;
}

/*@fn		  LFP_ARCH_ADAPTER_FILEIO_T*
 * lfp_get_arch_adapter_fileio_entry(LFP_VOID)
 * @brief 	  get the fileio function ptr entry.
 * @param[in]      LFP_NULL
 * @param[out]     LFP_NULL
 * @return	  LFP_ARCH_ADAPTER_FILEIO_T*
 */
LFP_ARCH_ADAPTER_FILEIO_T* lfp_get_arch_adapter_fileio_entry(LFP_VOID) {
    return &g_ArchAdapter.struArchAdapterFileio;
}

/*@fn		  LFP_ARCH_ADAPTER_STDIO_T*
 * lfp_get_arch_adapter_stdio_entry(LFP_VOID)
 * @brief 	  get the stdio function ptr entry.
 * @param[in]      LFP_NULL
 * @param[out]     LFP_NULL
 * @return	  LFP_ARCH_ADAPTER_STDIO_T*
 */
LFP_ARCH_ADAPTER_STDIO_T* lfp_get_arch_adapter_stdio_entry(LFP_VOID) {
    return &g_ArchAdapter.struArchAdapterStdio;
}

/*@fn		  LFP_ARCH_ADAPTER_SOCKET_T*
 * lfp_get_arch_adapter_socket_entry(LFP_VOID)
 * @brief 	  get the socket function ptr entry.
 * @param[in]      LFP_NULL
 * @param[out]     LFP_NULL
 * @return	  LFP_ARCH_ADAPTER_SOCKET_T*
 */
LFP_ARCH_ADAPTER_SOCKET_T* lfp_get_arch_adapter_socket_entry(LFP_VOID) {
    return &g_ArchAdapter.struArchAdapterSocket;
}

/*@fn		  LFP_ARCH_ADAPTER_TIME_T*
 * lfp_get_arch_adapter_time_entry(LFP_VOID)
 * @brief 	  get the time function ptr entry.
 * @param[in]      LFP_NULL
 * @param[out]     LFP_NULL
 * @return	  LFP_ARCH_ADAPTER_TIME_T*
 */
LFP_ARCH_ADAPTER_TIME_T* lfp_get_arch_adapter_time_entry(LFP_VOID) {
    return &g_ArchAdapter.struArchAdapterTime;
}

/*@fn		  LFP_STATIC LFP_CODE LFP_INT32
 * (*lfp_adapter_register[])(LFP_VOID)...
 * @brief 	  the adapter layer register -- the main register entrance, all
 * register cluster.
 * @param[in]  LFP_NULL
 * @param[out] LFP_NULL
 * @return	  LFP_OK
 */
LFP_STATIC LFP_CODE LFP_INT32 (*lfp_adapter_register[])(LFP_VOID) = {
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
LFP_INT32 lfp_arch_adapter_init(LFP_VOID) {
    LFP_UINT32 uiRegisterModules = 0;

    for (uiRegisterModules = 0;
         uiRegisterModules < LFP_NELEMENTS(lfp_adapter_register);
         uiRegisterModules++) {
        if (LFP_NULL != lfp_adapter_register[uiRegisterModules]) {
            lfp_adapter_register[uiRegisterModules]();
        }
    }
    return LFP_OK;
}
