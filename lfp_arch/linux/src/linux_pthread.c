/*
 * @FilePath: linux_pthread.c
 * @Description: Operating system adaptation layer, matching different
 architecture platforms. pthread implement.
 * @Author: wytaitaislee
 * @Date: 2022-03-05 16:42:26
 * @LastEditTime: 2022-03-20 15:20:11
 * @LastEditors: wytaitaislee
 * Copyright 2022 wytaitaislee, All Rights Reserved.
 */
#include "linux_pthread.h"

#include <signal.h>
#include <unistd.h>

#include "linux_typesdef.h"

/*@fn		  LFP_INT32 linux_pthread_create(LINUX_PTHREAD_HANDLE_T
*pThreadHandle, LFP_INT32 iPrority, LFP_UINT32 uiStackSize, LFP_VOID*
pStartTask, LFP_UINT32 uiArgs, LFP_VOID* pParams)
* @brief 	  create a new thread.
* @param[in]  LINUX_PTHREAD_HANDLE_T *pThreadHandle - the thread identifier
* @param[in]  LFP_INT32 iPrority - the thread execute priority
* @param[in]  LFP_INT32 uiStackSize - the thread stack size
* @param[in]  LFP_VOID *pStartTask - the start function
* @param[in]  LFP_VOID* pParams - the params num of the start function
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_pthread_create(LINUX_PTHREAD_HANDLE_T* pThreadHandle,
                               LFP_INT32 iPrority, LFP_UINT32 uiStackSize,
                               LFP_VOID* pStartTask, LFP_VOID* pParams) {
    LFP_INT32 iRet = LFP_ERR;
    LINUX_PTHREAD_HANDLE_T iHandle = 0, *pHandle = LFP_NULL;

    (LFP_VOID) iPrority;
    (LFP_VOID) uiStackSize;
    if (!pThreadHandle) {
        pHandle = &iHandle;
    } else {
        pHandle = pThreadHandle;
    }
    iRet = pthread_create(pHandle, LFP_NULL, pStartTask, pParams);
    return (0 == iRet) ? LFP_OK : LFP_ERR;
}

/*@fn		  LFP_INT32 linux_pthread_cancel(LINUX_PTHREAD_HANDLE_T
 * hThreadHandle)
 * @brief 	  send a cancellation request to a thread
 * @param[in]  LINUX_PTHREAD_HANDLE_T hThreadHandle - the thread identifier
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 linux_pthread_cancel(LINUX_PTHREAD_HANDLE_T hThreadHandle) {
    LFP_INT32 iRet = LFP_ERR;

    iRet = pthread_cancel(hThreadHandle);
    return (0 == iRet) ? LFP_OK : LFP_ERR;
}

/*@fn		  LFP_INT32 linux_pthread_kill(LINUX_PTHREAD_HANDLE_T hThreadHandle, LFP_INT32 iSig)
 * @brief 	  send a signal to a thread
 * @param[in]  LINUX_PTHREAD_HANDLE_T hThreadHandle - the thread identifier
 * @param[in]  LFP_INT32 iSig - signal type
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 linux_pthread_kill(LINUX_PTHREAD_HANDLE_T hThreadHandle,
                             LFP_INT32 iSig) {
    /* no assert here, for pthread status test */
    return pthread_kill(hThreadHandle, iSig);
}

/*@fn		  LFP_INT32 linux_pthread_attr_init(LINUX_PTHREAD_ATTR_T* pAttr)
 * @brief 	  initialize thread attributes object
 * @param[in]  LINUX_PTHREAD_ATTR_T* pAttr - the thread identifier
 * @param[in]  LFP_INT32 iSig - signal type
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 linux_pthread_attr_init(LINUX_PTHREAD_ATTR_T* pAttr) {
    LFP_INT32 iRet = LFP_ERR;

    LFP_RET_IF(pAttr, LFP_ERR);

    iRet = pthread_attr_init(pAttr);

    return (0 == iRet) ? LFP_OK : LFP_ERR;
}

/*@fn		  LFP_INT32 linux_pthread_attr_setdetachstate(LINUX_PTHREAD_ATTR_T* pAttr, LFP_INT32 iDetacheState)
 * @brief 	  set detach state attribute in thread attributes object
 * @param[in]  LINUX_PTHREAD_ATTR_T* pAttr - the attr
 * @param[in]  LFP_INT32 iDetacheState -  detachstate
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 linux_pthread_attr_setdetachstate(LINUX_PTHREAD_ATTR_T* pAttr, LFP_INT32 iDetacheState) {
    LFP_INT32 iRet = LFP_ERR;

    LFP_RET_IF(pAttr, LFP_ERR);

    iRet = pthread_attr_setdetachstate(pAttr, iDetacheState);

    return (0 == iRet) ? LFP_OK : LFP_ERR;
}

/*@fn		  LFP_INT32 linux_pthread_attr_getdetachstate(LINUX_PTHREAD_ATTR_T* pAttr, LFP_INT32 *piDetacheState)
 * @brief 	  get detach state attribute in thread attributes object
 * @param[in]  LINUX_PTHREAD_ATTR_T* pAttr - the attr
 * @param[in]  LFP_INT32* piDetacheState -  detachstate
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 linux_pthread_attr_getdetachstate(LINUX_PTHREAD_ATTR_T* pAttr, LFP_INT32* piDetacheState) {
    LFP_INT32 iRet = LFP_ERR;

    LFP_RET_IF(pAttr && piDetacheState, LFP_ERR);

    iRet = pthread_attr_setdetachstate(pAttr, piDetacheState);

    return (0 == iRet) ? LFP_OK : LFP_ERR;
}

/*@fn		  LFP_INT32 linux_pthread_attr_destroy(LINUX_PTHREAD_ATTR_T* pAttr)
 * @brief 	  destroy thread attributes object
 * @param[in]  LINUX_PTHREAD_ATTR_T* pAttr - the attr
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 linux_pthread_attr_destroy(LINUX_PTHREAD_ATTR_T* pAttr) {
    LFP_RET_IF(pAttr, LFP_ERR);

    LFP_INT32 iRet = LFP_ERR;

    iRet = pthread_attr_destroy(pAttr);

    return (0 == iRet) ? LFP_OK : LFP_ERR;
}