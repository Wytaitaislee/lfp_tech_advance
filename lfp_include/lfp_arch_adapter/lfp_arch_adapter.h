/***************************************************************************************
File name: lfp_arch_adapter.h
Description: System adaptation layer, matching different arch.
Author: wytaitaislee
Date: 2020-03-10
History: 1. create file. -- 2020-03-10
****************************************************************************************/
#ifndef __LFP_ARCH_ADAPTER_H__
#define __LFP_ARCH_ADAPTER_H__

#include "lfp_base.h"
#include "include/lfp_arch_abstract.h"

#define LFP_ADAPTER_INIT(ENTRY, FUNC)       ENTRY.FUNC = DEFINE_ARCH_ADAPTER(FUNC)
#define LFP_GET_CLASS_ENTRY(classname)    lfp_get_arch_adapter_##classname##_entry()

#define LFP_ARCH_ADAPTER_CRIT(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_CRIT, UTIL_MODULE_ADAPTER, MASK_ADAPTER, __VA_ARGS__) 
#define LFP_ARCH_ADAPTER_ERR(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_ERR, UTIL_MODULE_ADAPTER, MASK_ADAPTER, __VA_ARGS__)
#define LFP_ARCH_ADAPTER_INFO(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_INFO, UTIL_MODULE_ADAPTER, MASK_ADAPTER, __VA_ARGS__) 

/*@fn		  LFP_INT32 lfp_arch_adapter_init(LFP_VOID)
* @brief 	  the adapter layer register.
* @param[in]  LFP_NULL
* @param[out] LFP_NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_arch_adapter_init(LFP_VOID);

/*@fn		  LFP_ARCH_ADAPTER_PTHREAD_T* lfp_get_arch_adapter_pthread_entry(LFP_VOID)
* @brief 	  get the pthread function ptr entry.
* @param[in]      LFP_NULL
* @param[out]     LFP_NULL
* @return	  LFP_ARCH_ADAPTER_PTHREAD_T*
*/
LFP_ARCH_ADAPTER_PTHREAD_T* lfp_get_arch_adapter_pthread_entry(LFP_VOID);

/*@fn		  LFP_ARCH_ADAPTER_MUTEX_T* lfp_get_arch_adapter_mutex_entry(LFP_VOID)
* @brief 	  get the mutex function ptr entry.
* @param[in]      LFP_NULL
* @param[out]     LFP_NULL
* @return	  LFP_ARCH_ADAPTER_MUTEX_T*
*/
LFP_ARCH_ADAPTER_MUTEX_T* lfp_get_arch_adapter_mutex_entry(LFP_VOID);

/*@fn		  LFP_ARCH_ADAPTER_SEMAPHORE_T* lfp_get_arch_adapter_semaphore_entry(LFP_VOID)
* @brief 	  get the semaphore function ptr entry.
* @param[in]      LFP_NULL
* @param[out]     LFP_NULL
* @return	  LFP_ARCH_ADAPTER_SEMAPHORE_T*
*/
LFP_ARCH_ADAPTER_SEMAPHORE_T* lfp_get_arch_adapter_semaphore_entry(LFP_VOID);

/*@fn		  LFP_ARCH_ADAPTER_FILEIO_T* lfp_get_arch_adapter_fileio_entry(LFP_VOID)
* @brief 	  get the fileio function ptr entry.
* @param[in]      LFP_NULL
* @param[out]     LFP_NULL
* @return	  LFP_ARCH_ADAPTER_FILEIO_T*
*/
LFP_ARCH_ADAPTER_FILEIO_T* lfp_get_arch_adapter_fileio_entry(LFP_VOID);

/*@fn		  LFP_ARCH_ADAPTER_STDIO_T* lfp_get_arch_adapter_stdio_entry(LFP_VOID)
* @brief 	  get the stdio function ptr entry.
* @param[in]      LFP_NULL
* @param[out]     LFP_NULL
* @return	  LFP_ARCH_ADAPTER_STDIO_T*
*/
LFP_ARCH_ADAPTER_STDIO_T* lfp_get_arch_adapter_stdio_entry(LFP_VOID);

/*@fn		  LFP_ARCH_ADAPTER_SOCKET_T* lfp_get_arch_adapter_socket_entry(LFP_VOID)
* @brief 	  get the socket function ptr entry.
* @param[in]      LFP_NULL
* @param[out]     LFP_NULL
* @return	  LFP_ARCH_ADAPTER_SOCKET_T*
*/
LFP_ARCH_ADAPTER_SOCKET_T* lfp_get_arch_adapter_socket_entry(LFP_VOID);
#endif /*end of __LFP_ARCH_ADAPTER_H__ */