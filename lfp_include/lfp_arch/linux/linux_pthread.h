/***
 * @FilePath: linux_pthread.h
 * @Description: the pthread management on linux system.
 * @Author: wytaitaislee
 * @Date: 2021-08-27 23:29:52
 * @LastEditTime: 2022-03-05 21:21:47
 * @LastEditors: wytaitaislee
 * @Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#ifndef __LINUX_PTHREAD_H__
#define __LINUX_PTHREAD_H__

#include <pthread.h>

#include "lfp_base.h"

typedef pthread_t LINUX_PTHREAD_HANDLE_T;
typedef pthread_attr_t LINUX_PTHREAD_ATTR_T;
#define LINUX_PTHREAD_ESRCH ESRCH

#define LFP_PTHREAD_CRIT(...) \
  LFP_LOG_BASE(LOG_LEVEL_CRIT, LOG_MODULE_LINUX, MASK_PTHREAD, __VA_ARGS__)
#define LFP_PTHREAD_ERR(...) \
  LFP_LOG_BASE(LOG_LEVEL_ERR, LOG_MODULE_LINUX, MASK_PTHREAD, __VA_ARGS__)
#define LFP_PTHREAD_INFO(...) \
  LFP_LOG_BASE(LOG_LEVEL_INFO, LOG_MODULE_LINUX, MASK_PTHREAD, __VA_ARGS__)

/*@fn		  LFP_INT32 linux_pthread_create(LINUX_PTHREAD_HANDLE_T
*pThreadHandle, LFP_INT32 iPrority, LFP_UINT32 uiStackSize, LFP_VOID*
pStartTask, LFP_UINT32 uiArgs, LFP_VOID* pParams)
* @brief 	  create a new thread.
* @param[in]  LINUX_PTHREAD_HANDLE_T *pThreadHandle - the thread identifier
* @param[in]  LFP_INT32 iPrority - the thread execute priority
* @param[in]  LFP_INT32 uiStackSize - the thread stack size
* @param[in]  LFP_VOID *pStartTask - the start function
* @param[in]  LFP_VOID* pParams - the params num of the start function
* @param[out] NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_pthread_create(LINUX_PTHREAD_HANDLE_T* pThreadHandle,
                               LFP_INT32 iPrority, LFP_UINT32 uiStackSize,
                               LFP_VOID* pStartTask, LFP_VOID* pParams);

/*@fn		  LFP_INT32 linux_pthread_cancel(LINUX_PTHREAD_HANDLE_T
 * hThreadHandle)
 * @brief 	  send a cancellation request to a thread
 * @param[in]  LINUX_PTHREAD_HANDLE_T hThreadHandle - the thread identifier
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 linux_pthread_cancel(LINUX_PTHREAD_HANDLE_T hThreadHandle);

/*@fn		  LFP_INT32 linux_pthread_kill(LINUX_PTHREAD_HANDLE_T
 * hThreadHandle, LFP_INT32 iSig)
 * @brief 	  send a signal to a thread
 * @param[in]  LINUX_PTHREAD_HANDLE_T hThreadHandle - the thread identifier
 * @param[in]  LFP_INT32 iSig - signal type
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 linux_pthread_kill(LINUX_PTHREAD_HANDLE_T hThreadHandle,
                             LFP_INT32 iSig);

#endif /*end of __LINUX_PTHREAD_H__ */