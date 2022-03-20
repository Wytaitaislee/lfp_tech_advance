/***
 * @FilePath: lfp_arch_adapter_pthread.h
 * @Description: System adaptation layer, matching different arch.
 * @Author: wytaitaislee
 * @Date: 2021-08-27 23:29:52
 * @LastEditTime: 2022-03-05 21:18:29
 * @LastEditors: wytaitaislee
 * @Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#ifndef __LFP_ARCH_ADAPTER_PTHREAD_H__
#define __LFP_ARCH_ADAPTER_PTHREAD_H__

#include "include/lfp_arch_abstract.h"
#include "lfp_base.h"

/*@fn		  LFP_INT32 lfp_pthread_create(LFP_PTHREAD_HANDLE_T
*pThreadHandle, LFP_INT32 iPrority, LFP_UINT32 uiStackSize, LFP_VOID*
pStartTask, LFP_UINT32 uiArgs, LFP_VOID* pParams)
* @brief 	  create a new thread.
* @param[in]  LFP_PTHREAD_HANDLE_T *pThreadHandle - the thread identifier
* @param[in]  LFP_INT32 iPrority - the thread execute priority
* @param[in]  LFP_INT32 uiStackSize - the thread stack size
* @param[in]  LFP_VOID *pStartTask - the start function
* @param[in]  LFP_VOID* pParams - the params
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_pthread_create(LFP_PTHREAD_HANDLE_T* pThreadHandle,
                             LFP_INT32 iPrority, LFP_UINT32 uiStackSize,
                             LFP_VOID* pStartTask, LFP_VOID* pParams);

/*@fn		  LFP_INT32 lfp_pthread_cancel(LFP_PTHREAD_HANDLE_T
 * hThreadHandle)
 * @brief 	  send a cancellation request to a thread
 * @param[in]  LFP_PTHREAD_HANDLE_T hThreadHandle - the thread identifier
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 lfp_pthread_cancel(LFP_PTHREAD_HANDLE_T hThreadHandle);

/*@fn		  LFP_INT32 lfp_pthread_kill(LFP_PTHREAD_HANDLE_T
 * hThreadHandle, LFP_INT32 iSig)
 * @brief 	  send a signal to a thread
 * @param[in]  LFP_PTHREAD_HANDLE_T hThreadHandle - the thread identifier
 * @param[in]  LFP_INT32 iSig - signal type
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 lfp_pthread_kill(LFP_PTHREAD_HANDLE_T hThreadHandle, LFP_INT32 iSig);

/*@fn		  LFP_INT32 lfp_pthread_attr_init(LFP_PTHREAD_ATTR_T* pAttr)
 * @brief 	  initialize thread attributes object
 * @param[in]  LFP_PTHREAD_ATTR_T* pAttr - the thread identifier
 * @param[in]  LFP_INT32 iSig - signal type
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 lfp_pthread_attr_init(LFP_PTHREAD_ATTR_T* pAttr);

/*@fn		  LFP_INT32 lfp_pthread_attr_setdetachstate(LFP_PTHREAD_ATTR_T* pAttr, LFP_INT32 iDetacheState)
 * @brief 	  set detach state attribute in thread attributes object
 * @param[in]  LFP_PTHREAD_ATTR_T* pAttr - the attr
 * @param[in]  LFP_INT32 iDetacheState -  detachstate
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 lfp_pthread_attr_setdetachstate(LFP_PTHREAD_ATTR_T* pAttr, LFP_INT32 iDetacheState);

/*@fn		  LFP_INT32 lfp_pthread_attr_getdetachstate(LFP_PTHREAD_ATTR_T* pAttr, LFP_INT32 *piDetacheState)
 * @brief 	  get detach state attribute in thread attributes object
 * @param[in]  LFP_PTHREAD_ATTR_T* pAttr - the attr
 * @param[in]  LFP_INT32* piDetacheState -  detachstate
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 lfp_pthread_attr_getdetachstate(LFP_PTHREAD_ATTR_T* pAttr, LFP_INT32* piDetacheState);

/*@fn		  LFP_INT32 lfp_pthread_attr_destroy(LFP_PTHREAD_ATTR_T* pAttr)
 * @brief 	  destroy thread attributes object
 * @param[in]  LFP_PTHREAD_ATTR_T* pAttr - the attr
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 lfp_pthread_attr_destroy(LFP_PTHREAD_ATTR_T* pAttr);

/*@fn		  LFP_INT32 lfp_arch_adapter_pthread_register(LFP_VOID)
 * @brief 	  the adapter layer register -- pthread cluster register
 * @param[in]  LFP_NULL
 * @param[out] LFP_NULL
 * @return	  LFP_OK
 */
LFP_INT32 lfp_arch_adapter_pthread_register(LFP_VOID);
#endif /*end of __LFP_ARCH_ADAPTER_PTHREAD_H__ */