/***************************************************************************************
File name: lfp_arch_adapter_pthread.h
Description: System adaptation layer, matching different arch.
Author: wytaitaislee
Version: V1.0.0
Date: 2020-06-07
History: 1. create file. -- 2020-06-07
****************************************************************************************/

#ifndef __LFP_ARCH_ADAPTER_PTHREAD_H__
#define __LFP_ARCH_ADAPTER_PTHREAD_H__

#include "lfp_arch_abstract.h"

/*@fn		  LFP_INT32 lfp_pthread_create(LFP_PTHREAD_HADLE_T *pThreadHandle, LFP_INT32 iPrority,
                                LFP_UINT32 uiStackSize, LFP_VOID* pStartTask, LFP_UINT32 uiArgs, LFP_VOID* pParams)
* @brief 	  create a new thread.
* @param[in]  LFP_PTHREAD_HADLE_T *pThreadHandle - the thread identifier
* @param[in]  LFP_INT32 iPrority - the thread execute priority
* @param[in]  LFP_INT32 uiStackSize - the thread stack size
* @param[in]  LFP_VOID *pStartTask - the start function
* @param[in]  LFP_VOID* pParams - the params
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_pthread_create(LFP_PTHREAD_HADLE_T *pThreadHandle, LFP_INT32 iPrority, LFP_UINT32 uiStackSize, LFP_VOID* pStartTask, LFP_VOID* pParams);


/*@fn		  LFP_INT32 lfp_pthread_cancel(LFP_PTHREAD_HADLE_T hThreadHandle)
* @brief 	  send a cancellation request to a thread
* @param[in]  LFP_PTHREAD_HADLE_T hThreadHandle - the thread identifier
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_pthread_cancel(LFP_PTHREAD_HADLE_T hThreadHandle);

/*@fn		  LFP_INT32 lfp_pthread_kill(LFP_PTHREAD_HADLE_T hThreadHandle, LFP_INT32 iSig)
* @brief 	  send a signal to a thread
* @param[in]  LFP_PTHREAD_HADLE_T hThreadHandle - the thread identifier
* @param[in]  LFP_INT32 iSig - signal type
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_pthread_kill(LFP_PTHREAD_HADLE_T hThreadHandle, LFP_INT32 iSig);

/*@fn		  LFP_INT32 lfp_arch_adapter_pthread_register(LFP_VOID)
* @brief 	  the adapter layer register -- pthread cluster register
* @param[in]  LFP_NULL
* @param[out] LFP_NULL
* @return	  LFP_OK
*/
LFP_INT32 lfp_arch_adapter_pthread_register(LFP_VOID);
#endif	/*end of __LFP_ARCH_ADAPTER_PTHREAD_H__ */