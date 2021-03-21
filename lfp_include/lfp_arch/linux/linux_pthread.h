/***************************************************************************************
 * @fileName: linux_pthread.h
 * @Description: the pthread management on linux system.
 * @Author: wytaitaislee
 * @Date: 2020-09-26 18:43:32
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-03-21 19:58:50
****************************************************************************************/

#ifndef __LINUX_PTHREAD_H__
#define __LINUX_PTHREAD_H__

#include "lfp_base.h"
#include <pthread.h>

typedef pthread_t 			LINUX_PTHREAD_HANDLE_T;
typedef pthread_attr_t		LINUX_PTHREAD_ATTR_T;
#define LINUX_PTHREAD_ESRCH	ESRCH

#define LFP_PTHREAD_CRIT(...)   \
	LFP_UTIL_BASE(UTIL_LEVEL_CRIT, UTIL_MODULE_LINUX, MASK_PTHREAD, __VA_ARGS__) 
#define LFP_PTHREAD_ERR(...)   \
	LFP_UTIL_BASE(UTIL_LEVEL_ERR, UTIL_MODULE_LINUX, MASK_PTHREAD, __VA_ARGS__) 
#define LFP_PTHREAD_INFO(...)   \
	LFP_UTIL_BASE(UTIL_LEVEL_INFO, UTIL_MODULE_LINUX, MASK_PTHREAD, __VA_ARGS__)

/*@fn		  LFP_INT32 linux_pthread_create(LINUX_PTHREAD_HANDLE_T *pThreadHandle, LFP_INT32 iPrority,
                                LFP_UINT32 uiStackSize, LFP_VOID* pStartTask, LFP_UINT32 uiArgs, LFP_VOID* pParams)
* @brief 	  create a new thread.
* @param[in]  LINUX_PTHREAD_HANDLE_T *pThreadHandle - the thread identifier
* @param[in]  LFP_INT32 iPrority - the thread execute priority
* @param[in]  LFP_INT32 uiStackSize - the thread stack size
* @param[in]  LFP_VOID *pStartTask - the start function
* @param[in]  LFP_VOID* pParams - the params num of the start function
* @param[out] NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_pthread_create(LINUX_PTHREAD_HANDLE_T *pThreadHandle, LFP_INT32 iPrority,			\
                                LFP_UINT32 uiStackSize, LFP_VOID* pStartTask, LFP_VOID* pParams);

/*@fn		  LFP_INT32 linux_pthread_cancel(LINUX_PTHREAD_HANDLE_T hThreadHandle)
* @brief 	  send a cancellation request to a thread
* @param[in]  LINUX_PTHREAD_HANDLE_T hThreadHandle - the thread identifier
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_pthread_cancel(LINUX_PTHREAD_HANDLE_T hThreadHandle);

/*@fn		  LFP_INT32 linux_pthread_kill(LINUX_PTHREAD_HANDLE_T hThreadHandle, LFP_INT32 iSig)
* @brief 	  send a signal to a thread
* @param[in]  LINUX_PTHREAD_HANDLE_T hThreadHandle - the thread identifier
* @param[in]  LFP_INT32 iSig - signal type
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_pthread_kill(LINUX_PTHREAD_HANDLE_T hThreadHandle, LFP_INT32 iSig);

#endif	/*end of __LINUX_PTHREAD_H__ */