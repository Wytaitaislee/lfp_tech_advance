/***************************************************************************************
File name: lfp_arch_adapter_semaphore.h
Description: System adaptation layer, matching different arch.
Author: wytaitaislee
Version: V1.0.0
Date: 2020-06-07
History: 1. create file. -- 2020-06-07
****************************************************************************************/

#ifndef __LFP_ARCH_ADAPTER_SEMAPHORE_H__
#define __LFP_ARCH_ADAPTER_SEMAPHORE_H__

#include "lfp_base.h"

/*@fn		   LFP_INT32 lfp_semaphore_init(LFP_SEM_T *pSem, LFP_INT32 iShared, LFP_UINT32 uInitValue)
* @brief 	   semaphore init on lfp system.
* @param[in]   LFP_INT32 iShared - if whether to share between processes
* @param[in]   LFP_INT32 iInitValue - initialization value
* @param[out]  LFP_SEM_T *pSem - pointer to semaphore structure entry 
* @return	   LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_semaphore_init(LFP_SEM_T *pSem, LFP_INT32 iShared, LFP_UINT32 uiInitValue);

/*@fn		   LFP_INT32 lfp_semaphore_wait(LFP_SEM_T *pSem, LFP_INT32 iWaitTime)
* @brief 	   semaphore wait on lfp system.
* @param[out]  LFP_SEM_T *pSem - pointer to semaphore structure entry 
* @param[in]   LFP_UINT32 iWaitTime - initialization value
* @return	   LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_semaphore_wait(LFP_SEM_T *pSem, LFP_INT32 iWaitTime);

/*@fn		   LFP_INT32 lfp_semaphore_post(LFP_SEM_T *pSem)
* @brief 	   semaphore post on lfp system.
* @param[out]  LFP_SEM_T *pSem - pointer to semaphore structure entry 
* @return	   LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_semaphore_post(LFP_SEM_T *pSem);

/*@fn		   LFP_INT32 lfp_semaphore_destroy(LFP_SEM_T *pSem)
* @brief 	   semaphore post on lfp system.
* @param[out]  LFP_SEM_T *pSem - pointer to semaphore structure entry 
* @return	   LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_semaphore_destroy(LFP_SEM_T *pSem);

/*@fn		  LFP_INT32 lfp_arch_adapter_semaphore_register(LFP_VOID)
* @brief 	  the adapter layer register -- semaphore cluster register
* @param[in]  LFP_NULL
* @param[out] LFP_NULL
* @return	  LFP_OK
*/
LFP_INT32 lfp_arch_adapter_semaphore_register(LFP_VOID);

#endif	/*end of __LFP_ARCH_ADAPTER_SEMAPHORE_H__ */