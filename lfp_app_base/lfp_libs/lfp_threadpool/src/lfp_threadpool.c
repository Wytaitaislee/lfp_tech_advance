/*
 * @FilePath: lfp_threadpool.c
 * @Description: threadpool libs.
 * @Author: wytaitaislee
 * @Date: 2021-08-27 23:29:52
 * @LastEditTime: 2022-03-20 15:52:13
 * @LastEditors: wytaitaislee
 * Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#include "lfp_threadpool/lfp_threadpool.h"

#include <errno.h>
#include <stdarg.h>

#include "lfp_arch_adapter.h"
#include "lfp_arch_adapter_mutex.h"
#include "lfp_arch_adapter_semaphore.h"
#include "lfp_arch_adapter_time.h"
#include "lfp_dlist/lfp_dlist.h"
#include "lfp_list.h"

/*@fn		  LFP_STATIC LFP_INT32 __queue_list_init(LFP_VOID)
 * @brief 	  work queue list init.
 * @param[in]  LFP_THPOOL_LIST_T *pThpoolList - threadpool list ptr
 * @return	  NULL
 */
LFP_STATIC LFP_INT32 __queue_list_init(LFP_THPOOL_LIST_T *pThpoolList) {
    LFP_RET_IF(pThpoolList, LFP_ERR);
    pThpoolList->uiCount = 0;
    if (LFP_OK != lfp_dlist_init(&pThpoolList->node)) {
        LFP_THREADPOOL_ERR("dlist init failed\n");
        return LFP_ERR;
    }
    return LFP_ERR;
}

/*@fn		  LFP_STATIC LFP_INT32 __queue_list_fini(LFP_VOID)
 * @brief 	  work queue list fini.
 * @param[in]  LFP_THPOOL_LIST_T *pThpoolList - threadpool list ptr
 * @return	  NULL
 */
LFP_STATIC LFP_INT32 __queue_list_fini(LFP_THPOOL_LIST_T *pThpoolList) {
    LFP_RET_IF(pThpoolList, LFP_ERR);
    pThpoolList->uiCount = 0;
    if (LFP_OK != lfp_dlist_destroy(&pThpoolList->node)) {
        LFP_THREADPOOL_ERR("dlist init failed\n");
        return LFP_ERR;
    }
    return LFP_OK;
}

/*@fn		  LFP_INT32 __work_queue_add(LFP_THPOOL_LIST_T *pstruWorkQueue,
 * WORK_ITEM_T *pstruWorkItem)
 * @brief 	  add a new work request to the tail of the work queue.
 * @param[in]  LFP_THPOOL_LIST_T *pstruWorkQueue - the work queue entry.
 * @param[in]  WORK_ITEM_T *pstruWorkItem - work entry.
 * @return	  LFP_OK / LFP_ERR
 */
LFP_STATIC LFP_INT32 __work_queue_add(LFP_THPOOL_LIST_T *pstruWorkQueue,
                                      WORK_ITEM_T *pstruWorkItem) {
    LFP_RET_IF(pstruWorkQueue && pstruWorkItem, LFP_ERR);
    if (LFP_OK !=
        lfp_dlist_add_tail(&pstruWorkQueue->node, &pstruWorkItem->node)) {
        return LFP_ERR;
    }
    pstruWorkQueue->uiCount++;
    return LFP_OK;
}

/*@fn		  LFP_STATIC WORK_ITEM_T* __work_queue_pop(LFP_THPOOL_LIST_T
 * *pstruWorkQueue)
 * @brief 	  get a work item form the head of the work queue.
 * @param[in]  LFP_THPOOL_LIST_T *pstruWorkQueue - the work queue entry.
 * @return	  WORK_ITEM_T* / LFP_NULL
 */
LFP_STATIC WORK_ITEM_T *__work_queue_pop(LFP_THPOOL_LIST_T *pstruWorkQueue) {
    WORK_ITEM_T *pstruWorkItem = LFP_NULL;

    LFP_RET_IF(pstruWorkQueue, LFP_NULL);
    pstruWorkItem =
        LFP_LIST_FIRST_ENTRY(&pstruWorkQueue->node, WORK_ITEM_T, node);
    LFP_RET_IF(pstruWorkItem, LFP_NULL);
    (LFP_VOID) lfp_dlist_delete(pstruWorkQueue->node.pNext);
    pstruWorkQueue->uiCount--;
    return pstruWorkItem;
}

/*@fn		  LFP_STATIC LFP_INT32 __work_queue_destroy(LFP_THPOOL_LIST_T
 * *pstruWorkQueue)
 * @brief 	  destroy the specified work queue .
 * @param[in]  LFP_THPOOL_LIST_T *pstruWorkQueue - the work queue entry.
 * @return	  LFP_OK / LFP_ERR
 */
LFP_STATIC LFP_INT32 __work_queue_destroy(LFP_THPOOL_LIST_T *pstruWorkQueue) {
    WORK_ITEM_T *pstruWorkItem = NULL;

    LFP_RET_IF(pstruWorkQueue, LFP_ERR);
    pstruWorkQueue->uiCount = 0;
    LFP_LIST_FOR_EACH_ENTRY(pstruWorkItem, &pstruWorkQueue->node, node) {
        pstruWorkItem->workHandle = LFP_NULL;
        LFP_SAFE_FREE(pstruWorkItem);
    }
    (LFP_VOID) lfp_dlist_destroy(&pstruWorkQueue->node);
    LFP_SAFE_FREE(pstruWorkQueue);
    return LFP_OK;
}

/*@fn		  LFP_STATIC THREAD_ITEM_T* __thread_queue_add(LFP_THPOOL_LIST_T
 * *pstruThreadQueue)
 * @brief 	  add a new thread request to the tail of the thread queue.
 * @param[in]  LFP_THPOOL_LIST_T *pstruThreadQueue - the thread queue entry.
 * @return	  THREAD_ITEM_T* / LFP_NULL
 */
LFP_STATIC THREAD_ITEM_T *__thread_queue_add(
    LFP_THPOOL_LIST_T *pstruThreadQueue) {
    THREAD_ITEM_T *pThreadItem = LFP_NULL;

    LFP_RET_IF(pstruThreadQueue, LFP_NULL);
    pThreadItem = (THREAD_ITEM_T *)LFP_MALLOC(sizeof(THREAD_ITEM_T));
    LFP_RET_IF(pThreadItem, LFP_NULL);
    pThreadItem->bWorking = LFP_FALSE;
    if (LFP_OK != lfp_semaphore_init(&pThreadItem->semphore, 0, 0)) {
        LFP_THREADPOOL_ERR("thread semphore init failed\n");
        LFP_SAFE_FREE(pThreadItem);
        return LFP_NULL;
    }
    pThreadItem->uiWorkerTime = 0;
    if (LFP_OK !=
        lfp_dlist_add_tail(&pstruThreadQueue->node, &pThreadItem->node)) {
        LFP_SAFE_FREE(pThreadItem);
        return LFP_NULL;
    }
    pstruThreadQueue->uiCount++;
    return pThreadItem;
}

/*@fn		  LFP_STATIC LFP_INT32 __thread_queue_delete(THREAD_ITEM_T
 * *pThreadItem)
 * @brief 	  delete a specified threadinfo from the head of the thread
 * queue.
 * @param[in]  THREAD_ITEM_T *pThreadItem - the thread queue entry.
 * @return	  LFP_OK / LFP_ERR
 */
LFP_STATIC LFP_INT32 __thread_queue_delete(THREAD_ITEM_T *pThreadItem) {
    LFP_RET_IF(pThreadItem, LFP_ERR);
    lfp_semaphore_destroy(&pThreadItem->semphore);
    (LFP_VOID) lfp_dlist_delete(&pThreadItem->node);
    LFP_SAFE_FREE(pThreadItem);
    return LFP_OK;
}

/*@fn		  LFP_STATIC LFP_INT32 __thread_queue_destroy(LFP_THPOOL_LIST_T
 * *pstruThreadQueue)
 * @brief 	  destroy the specified thread queue .
 * @param[in]  LFP_THPOOL_LIST_T *pstruThreadQueue - the thread queue entry.
 * @return	  LFP_OK / LFP_ERR
 */
LFP_STATIC LFP_INT32 __thread_queue_destroy(LFP_THPOOL_LIST_T *pstruThreadQueue) {
    THREAD_ITEM_T *pThreadEntry = LFP_NULL;

    LFP_RET_IF(pstruThreadQueue, LFP_ERR);
    LFP_LIST_FOR_EACH_ENTRY(pThreadEntry, &pstruThreadQueue->node, node) {
        lfp_semaphore_destroy(&pThreadEntry->semphore);
        LFP_SAFE_FREE(pThreadEntry);
    }
    lfp_dlist_destroy(&pstruThreadQueue->node);
    LFP_SAFE_FREE(pstruThreadQueue);
    pstruThreadQueue = LFP_NULL;
    return LFP_OK;
}

/*@fn		  LFP_STATIC LFP_INLINE LFP_VOID
 * __lfp_threadpool_set_thread_idle(THREAD_ITEM_T *pstruThreadItem)
 * @brief 	  set a thread worker to be idle .
 * @param[out] THREAD_ITEM_T *pstruThreadItem - the threadinfo entry.
 * @return	  LFP_VOID
 * @note       only in lfp_threadpool_worker , no need to lock again
 */
LFP_STATIC LFP_INLINE LFP_VOID
__lfp_threadpool_set_thread_idle(THREAD_ITEM_T *pstruThreadItem) {
    pstruThreadItem->bWorking = LFP_FALSE;
    pstruThreadItem->uiWorkerTime = 0;
}

/*@fn		  LFP_STATIC LFP_INLINE LFP_VOID
 * __lfp_threadpool_set_thread_working(THREAD_ITEM_T *pstruThreadItem)
 * @brief 	  set a thread worker to be working .
 * @param[out] THREAD_ITEM_T *pstruThreadItem - the threadinfo entry.
 * @return	  LFP_VOID
 * @note       only in lfp_threadpool_worker , no need to lock again
 */
LFP_STATIC LFP_INLINE LFP_VOID
__lfp_threadpool_set_thread_working(THREAD_ITEM_T *pstruThreadItem) {
    pstruThreadItem->bWorking = LFP_TRUE;
    pstruThreadItem->uiWorkerTime = lfp_get_time(NULL);
}

LFP_STATIC LFP_INT32
__lfp_threadpool_work_handle_proc(WORK_ITEM_T *pstruWorkItem) {
    LFP_RET_IF(pstruWorkItem, LFP_ERR);

    switch (pstruWorkItem->iArgc) {
    case 0:
        pstruWorkItem->workHandle(NULL);
        break;
    case 1:
        pstruWorkItem->workHandle(pstruWorkItem->pArg[0]);
        break;
    case 2:
        pstruWorkItem->workHandle(pstruWorkItem->pArg[0], pstruWorkItem->pArg[1]);
        break;
    case 3:
        pstruWorkItem->workHandle(pstruWorkItem->pArg[0], pstruWorkItem->pArg[1],
                                  pstruWorkItem->pArg[2]);
        break;
    case 4:
        pstruWorkItem->workHandle(pstruWorkItem->pArg[0], pstruWorkItem->pArg[1],
                                  pstruWorkItem->pArg[2], pstruWorkItem->pArg[3]);
        break;
    case 5:
        pstruWorkItem->workHandle(pstruWorkItem->pArg[0], pstruWorkItem->pArg[1],
                                  pstruWorkItem->pArg[2], pstruWorkItem->pArg[3],
                                  pstruWorkItem->pArg[4]);
        break;
    default:
        return LFP_ERR;
    }
    return LFP_OK;
}

/*@fn		  LFP_STATIC LFP_VOID __lfp_threadpool_worker(LFP_VOID *pArgs)
 * @brief 	  the thread worker.
 * @param[in]  LFP_VOID *pArgs - thread worker args.
 * @return	  LFP_VOID
 */
LFP_STATIC LFP_VOID __lfp_threadpool_worker(LFP_VOID *pArgs) {
    WORK_ITEM_T *pstruWorkItem = LFP_NULL;
    LFP_THREADPOOL_T *pstruThreadPool = (LFP_THREADPOOL_T *)pArgs;
    THREAD_ITEM_T *pstruThreadItem = LFP_NULL;

    LFP_RET_VOID_IF(pstruThreadPool);
    lfp_mutex_lock(&pstruThreadPool->mutex);
    pstruThreadItem = __thread_queue_add(&pstruThreadPool->struThreadQueueList);
    if (!pstruThreadItem) {
        lfp_mutex_unlock(&pstruThreadPool->mutex);
        goto worker_exit;
    }
    //   (LFP_VOID) wo_queue_add(&pstruThreadPool->struWorkQueueList,
    //                             &pstruThreadItem->node);
    lfp_mutex_unlock(&pstruThreadPool->mutex);

    while (LFP_THREADPOOL_STATE_EXIT != pstruThreadPool->enumState) {
        lfp_mutex_lock(&pstruThreadPool->mutex);
        __lfp_threadpool_set_thread_idle(pstruThreadItem);
        pstruThreadPool->uiThreadIdle++;
        lfp_mutex_unlock(&pstruThreadPool->mutex);
        if (LFP_OK != lfp_semaphore_wait(&pstruThreadItem->semphore,
                                         pstruThreadPool->uiThreadTimeOut)) {
            LFP_THREADPOOL_INFO("pthread wait timeout, exit\n");
            goto worker_exit;
        }
        lfp_mutex_lock(&pstruThreadPool->mutex);
        pstruThreadPool->uiThreadIdle--;
        pstruWorkItem = __work_queue_pop(&pstruThreadPool->struWorkQueueList);
        if (!pstruWorkItem) {
            lfp_mutex_unlock(&pstruThreadPool->mutex);
            continue;
        }
        __lfp_threadpool_set_thread_working(pstruThreadItem);
        lfp_mutex_unlock(&pstruThreadPool->mutex);
        __lfp_threadpool_work_handle_proc(pstruWorkItem);
    }
worker_exit:
    if (pstruThreadItem) {
        lfp_mutex_lock(&pstruThreadPool->mutex);
        lfp_dlist_delete(&pstruThreadItem->node);
        lfp_mutex_unlock(&pstruThreadPool->mutex);
        __thread_queue_delete(pstruThreadItem);
    }
    LFP_SAFE_FREE(pstruThreadItem);
    return;
}

/*@fn		  LFP_STATIC  LFP_INT32 __lfp_threadpool_destroy(LFP_THREADPOOL_T
 * *pstruThreadPool)
 * @brief 	  destory the specified threadpool entry.
 * @param[in]  LFP_THREADPOOL_T *pstruThreadPool - threadpool entrty
 * @return	  LFP_OK / LFP_ERR
 */
LFP_STATIC LFP_INT32 __lfp_threadpool_destroy(LFP_THREADPOOL_T *pstruThreadPool) {
    lfp_mutex_lock(&pstruThreadPool->mutex);
    __queue_list_fini(&pstruThreadPool->struThreadQueueList);
    __queue_list_fini(&pstruThreadPool->struWorkQueueList);
    lfp_mutex_unlock(&pstruThreadPool->mutex);
    lfp_mutex_destroy(&pstruThreadPool->mutex);
    LFP_SAFE_FREE(pstruThreadPool);
    return LFP_OK;
}

/*@fn		  LFP_THREADPOOL_T *__lfp_threadpool_create(LFP_UINT32 uiMaxThreads,
 * LFP_UINT32 uiThreadTimeout)
 * @brief 	  create a threadpool entry.
 * @param[in]  LFP_UINT32 uiMaxThreads - the maximum of the threadpool threads.
 * @param[in]  LFP_UINT32 uiThreadTimeout - work thread timeout
 * @return	  LFP_OK / LFP_ERR
 */
LFP_THREADPOOL_T *__lfp_threadpool_create(LFP_UINT32 uiMaxThreads,
                                          LFP_UINT32 uiThreadTimeout) {
    LFP_INT32 iRet = LFP_ERR;
    LFP_THREADPOOL_T *pstruThreadPool = LFP_NULL;

    pstruThreadPool = (LFP_THREADPOOL_T *)LFP_MALLOC(sizeof(*pstruThreadPool));
    LFP_RET_IF(pstruThreadPool, LFP_NULL);
    LFP_BUFF_BEZERO(pstruThreadPool, sizeof(*pstruThreadPool));
    pstruThreadPool->enumState = LFP_THREADPOOL_STATE_INVALID;
    iRet = lfp_mutex_init(&pstruThreadPool->mutex, LFP_NULL);
    if (LFP_OK != iRet) {
        LFP_THREADPOOL_ERR("pthreadpool mutex init failed, iRet[%d], err[%s]\n",
                           iRet, strerror(errno));
        LFP_SAFE_FREE(pstruThreadPool);
        return LFP_NULL;
    }
    if (LFP_OK != __queue_list_init(&pstruThreadPool->struThreadQueueList)) {
        LFP_THREADPOOL_ERR("pthreadpool threadqueue init failed\n");
        goto freeResMutex;
    }
    if (LFP_OK != __queue_list_init(&pstruThreadPool->struWorkQueueList)) {
        LFP_THREADPOOL_ERR("pthreadpool workqueue init failed\n");
        goto freeResThreadQ;
    }
    pstruThreadPool->threadpool_worker = __lfp_threadpool_worker;
    pstruThreadPool->uiThreadMax = uiMaxThreads;
    pstruThreadPool->uiThreadTimeOut = uiThreadTimeout;
    pstruThreadPool->uiThreadAlive = 0;
    pstruThreadPool->uiThreadIdle = 0;
    pstruThreadPool->enumState = LFP_THREADPOOL_STATE_WORKING;
    return pstruThreadPool;
freeResThreadQ:
    __queue_list_fini(&pstruThreadPool->struThreadQueueList);
freeResMutex:
    lfp_mutex_destroy(&pstruThreadPool->mutex);
    LFP_SAFE_FREE(pstruThreadPool);
    return LFP_NULL;
}

/*@fn		  LFP_STATIC LFP_INLINE LFP_INT32
 * __lfp_threadpool_active_the_latest_idle_worker(LFP_THPOOL_LIST_T
 * *pstruThreadQueue)
 * @brief 	  find and activate the most idle thread recently.
 * @param[in]  THREAD_QUEUE_T *pstruThreadQueue - the thread queue.
 * @return	  LFP_OK / LFP_ERR
 */
LFP_STATIC LFP_INLINE LFP_INT32 __lfp_threadpool_active_the_latest_idle_worker(
    LFP_THPOOL_LIST_T *pstruThreadQueue) {
    THREAD_ITEM_T *pstruThreadItem = LFP_NULL;
    THREAD_ITEM_T *pstruThreadTmp = LFP_NULL;
    LFP_RET_IF(pstruThreadQueue, LFP_ERR);

    LFP_LIST_FOR_EACH_ENTRY(pstruThreadTmp, &pstruThreadQueue->node, node) {
        if (!pstruThreadTmp->bWorking &&
            pstruThreadTmp->uiWorkerTime > pstruThreadItem->uiWorkerTime) {
            pstruThreadItem = pstruThreadTmp;
            break;
        }
    }
    LFP_RET_IF(pstruThreadItem, LFP_ERR);
    lfp_semaphore_post(&pstruThreadItem->semphore);
    return LFP_OK;
}

LFP_STATIC LFP_INT32 __lfp_threadpool_detached_create(LFP_VOID *(*workcptr)(LFP_VOID *),
                                                      LFP_VOID *pHandle) {
    LFP_PTHREAD_ATTR_T struAttr;
    LFP_RET_IF(workcptr && pHandle, LFP_ERR);

    LFP_BUFF_BEZERO(&struAttr, sizeof(struAttr));

    if (LFP_OK != lfp_pthread_attr_init(&struAttr)) {
        return LFP_ERR;
    }

    if (LFP_OK != lfp_pthread_attr_setdetachstate(&struAttr, LFP_PTHREAD_CREATE_DETACHED)) {
        goto exit;
    }

    if (LFP_OK != lfp_pthread_create(LFP_NULL, &struAttr, workcptr, pHandle)) {
        goto exit;
    }

    return LFP_OK;
exit:
    lfp_pthread_attr_destory(&struAttr);
    return LFP_ERR;
}

/*@fn		  LFP_INT32 lfp_threadpool_dispatch(LFP_THREADPOOL_T
*pstruThreadPool, work_handle workHandle, LFP_VOID* pUsrData)
* @brief 	  thread dispatch, 1. manage thread worker; 2. activate the most
idle thread recently
* @param[in]  LFP_THREADPOOL_T *pstruThreadPool - threadpool entrty
* @param[in]  work_handle workHandle - work function ptr entry.
* @param[in]  LFP_VOID *pUsrData - work data.
* @return	  LFP_OK / LFP_ERR
*/

LFP_INT32 lfp_threadpool_dispatch(LFP_VOID *pHandle,
                                  LFP_INT32 iPriority,
                                  LFP_INT32 iCpuNo,
                                  work_handle workHandle,
                                  LFP_INT32 iArgc, ...) {
    LFP_INT32 iArgCnt = 0;
    va_list ap;
    WORK_ITEM_T *pstruWorkItem = LFP_NULL;
    LFP_THREADPOOL_T *pstruThpool = (LFP_THREADPOOL_T *)(pHandle);

    (LFP_VOID) iPriority;
    (LFP_VOID) iCpuNo;
    LFP_RET_IF(pstruThpool && workHandle, LFP_ERR);
    LFP_RET_IF((iArgc <= LFP_THREADPOOL_MAX_ARGS_NUM), LFP_ERR);

    pstruWorkItem = (WORK_ITEM_T *)LFP_MALLOC(sizeof(WORK_ITEM_T));
    LFP_RET_IF(pstruWorkItem, LFP_ERR);
    LFP_BUFF_BEZERO(pstruWorkItem, sizeof(*pstruWorkItem));
    pstruWorkItem->workHandle = workHandle;

    va_start(ap, iArgc);
    for (iArgCnt = 0; iArgCnt < iArgc; iArgCnt++) {
        pstruWorkItem->pArg[iArgCnt] = va_arg(ap, LFP_VOID *);
    }
    va_end(ap);

    lfp_mutex_lock(&pstruThpool->mutex);
    __work_queue_add(&pstruThpool->struWorkQueueList, pstruWorkItem);

    if (0 == pstruThpool->uiThreadIdle &&
        pstruThpool->uiThreadAlive < pstruThpool->uiThreadMax) {
        if (LFP_OK != __lfp_threadpool_detached_create(__lfp_threadpool_worker, pHandle)) {
            LFP_PTHREAD_ERR("create a new worker failed\n");
        } else {
            pstruThpool->uiThreadAlive++;
        }
    }
    if (__lfp_threadpool_active_the_latest_idle_worker(
            &pstruThpool->struThreadQueueList)) {
        LFP_THREADPOOL_ERR("active the latest idle worker failed\n");
    }
    lfp_mutex_unlock(&pstruThpool->mutex);

    return LFP_OK;
}
