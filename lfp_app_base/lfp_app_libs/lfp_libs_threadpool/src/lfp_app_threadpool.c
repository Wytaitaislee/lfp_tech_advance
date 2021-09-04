/*
 * @file name: lfp_app_threadpool.c
 * @Description: threadpool libs
 * @Author: wytaitaislee
 * @Date: 2021-03-21 17:59:18
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-09-04 20:25:35
 */

#include <errno.h>
#include "lfp_base.h"
#include "lfp_libs_dlist.h"
#include "lfp_libs_list.h"
#include "lfp_libs_threadpool.h"

WORK_QUEUE_T *work_queue_init(LFP_VOID)
{
    LFP_INT32 iRet = LFP_ERR;
    WORK_QUEUE_T *pstruWorkQueue = NULL;

    pstruWorkQueue = (WORK_QUEUE_T*)LFP_MALLOC(sizeof(WORK_QUEUE_T));
    LFP_ASSERT_NULL_RET(pstruWorkQueue);
    pstruWorkQueue->uiWorkQueueCnt = 0;
    iRet = lfp_dlist_init(&pstruWorkQueue->listHead);
    if(LFP_OK != iRet)
    {
        LFP_SAFE_FREE(pstruWorkQueue);
        return LFP_NULL;
    }
    return pstruWorkQueue;
}

/* add to the tail */
LFP_INT32 work_queue_add(WORK_QUEUE_T *pstruWorkQueue, work_handle *pWorkHandle, LFP_VOID *pData)
{
    WORK_ITEM_T *pWorkItem = LFP_NULL;

    LFP_ASSERT_ERR_RET(pstruWorkQueue && pWorkHandle && pData);
    pWorkItem = (WORK_ITEM_T*)LFP_MALLOC(sizeof(WORK_ITEM_T));
    LFP_ASSERT_ERR_RET(pWorkItem);
    pWorkItem->pWorkData = pData;
    pWorkItem->pWorkHandle = pWorkHandle;
    if(LFP_OK != lfp_dlist_add_tail(&pstruWorkQueue->listHead, &pWorkItem->node))
    {
        LFP_SAFE_FREE(pWorkItem);
        return LFP_ERR;
    }
    pstruWorkQueue->uiWorkQueueCnt++;
    return LFP_OK;
}

/* pop from the head */
LFP_STATIC WORK_ITEM_T* work_queue_pop(WORK_QUEUE_T *pstruWorkQueue)
{
    WORK_ITEM_T *pWorkItem = LFP_NULL;
    LFP_VOID *pData = LFP_NULL;

    LFP_ASSERT_NULL_RET(pstruWorkQueue);
    pWorkItem = LFP_LIST_FIRST_ENTRY(&pstruWorkQueue->listHead, WORK_ITEM_T, node);
    LFP_ASSERT_NULL_RET(pWorkItem);
    pstruWorkQueue->uiWorkQueueCnt--;
    (LFP_VOID)lfp_dlist_delete(pstruWorkQueue->listHead.pNext);
    return pWorkItem;
}

LFP_STATIC LFP_INT32 work_queue_destory(WORK_QUEUE_T *pstruWorkQueue)
{
    LFP_INT32 iRet = LFP_ERR;
    WORK_ITEM_T *pstruWorkItem = NULL;

    LFP_ASSERT_ERR_RET(pstruWorkQueue);
    pstruWorkQueue->uiWorkQueueCnt = 0;
    LFP_LIST_FOR_EACH_ENTRY(pstruWorkItem, &pstruWorkQueue->listHead, node)
    {
        pstruWorkItem->pWorkData = LFP_NULL;
        pstruWorkItem->pWorkHandle = LFP_NULL;
    }
    iRet = lfp_dlist_init(&pstruWorkQueue->listHead);
    if(LFP_OK != iRet)
    {
        LFP_SAFE_FREE(pstruWorkQueue);
        return LFP_ERR;
    }
    return LFP_OK;
}

/* pop from the head */
LFP_STATIC THREAD_QUEUE_T* thread_queue_init(LFP_VOID)
{
    LFP_INT32 iRet = LFP_ERR;
    THREAD_QUEUE_T *pstruThreadQueue = NULL;

    pstruThreadQueue = (THREAD_QUEUE_T*)LFP_MALLOC(sizeof(THREAD_QUEUE_T));
    LFP_ASSERT_NULL_RET(pstruThreadQueue);
    pstruThreadQueue->uiThreadQueueCnt = 0;
    iRet = lfp_dlist_init(&pstruThreadQueue->listHead);
    if(LFP_OK != iRet)
    {
        LFP_SAFE_FREE(pstruThreadQueue);
        return LFP_NULL;
    }
    return pstruThreadQueue;
}

LFP_STATIC THREAD_QUEUE_T* thread_queue_destroy(THREAD_QUEUE_T *pstruThreadQueue)
{
    THREAD_ITEM_T *pThreadEntry = LFP_NULL;

    LFP_ASSERT_ERR_RET(pstruThreadQueue);
    LFP_LIST_FOR_EACH_ENTRY(pThreadEntry, &pstruThreadQueue->listHead, node)
    {
        lfp_mutex_destroy(pThreadEntry->semphore);
    }
    lfp_dlist_destroy(&pstruThreadQueue->listHead);
    pstruThreadQueue = LFP_NULL;
    return LFP_OK;
}

/* only in lfp_threadpool_worker , no need to lock again */
LFP_STATIC LFP_INLINE LFP_VOID lfp_threadpool_set_thread_idle(THREAD_ITEM_T *pstruThreadItem)
{
    pstruThreadItem->bWorking = LFP_FALSE;
    pstruThreadItem->uiWorkerTime = 0; 
}

LFP_STATIC LFP_INLINE LFP_VOID lfp_threadpool_set_thread_working(THREAD_ITEM_T *pstruThreadItem)
{
    pstruThreadItem->bWorking = LFP_TRUE;
    pstruThreadItem->uiWorkerTime = lfp_get_time(NULL);
}

LFP_STATIC LFP_VOID lfp_threadpool_worker(LFP_VOID *pArgs)
{
    LFP_INT32 iRet = LFP_ERR;
    WORK_ITEM_T *pWorkItem = LFP_NULL; 
    LFP_THREADPOOL_T *pstruThreadPool = (LFP_THREADPOOL_T *)pArgs;
    THREAD_ITEM_T *pstruThreadItem = LFP_NULL;

    LFP_ASSERT_ERR_RET(pstruThreadPool);
    pstruThreadItem = (THREAD_ITEM_T *)LFP_MALLOC(sizeof(THREAD_ITEM_T));
    LFP_ASSERT_ERR_RET(pstruThreadItem);
    LFP_BUFF_BEZERO(pstruThreadItem, sizeof(THREAD_ITEM_T));
    if(LFP_OK != lfp_semaphore_init(pstruThreadItem->semphore, 0, 0))
    {
        LFP_THREADPOOL_ERR("pthread semphore init failed\n");
        return LFP_ERR;
    }
    pstruThreadItem->uiWorkerTime = 0;
    pstruThreadItem->bWorking = 0;
    lfp_mutex_lock(&pstruThreadPool->mutex);
    lfp_dlist_add_tail(&pstruThreadPool->pstruThreadQueue->listHead, &pstruThreadItem->node);
    lfp_mutex_unlock(&pstruThreadPool->mutex);

    while(LFP_THREADPOOL_STATE_EXIT != pstruThreadPool->enumState)
    {
        lfp_mutex_lock(&pstruThreadPool->mutex);
        lfp_threadpool_set_thread_idle(pstruThreadItem);
        pstruThreadPool->uiThreadIdle++;
        lfp_mutex_unlock(&pstruThreadPool->mutex);
        iRet = lfp_semphore_wait(&pstruThreadItem->semphore, pstruThreadPool->uiThreadTimeOut);
        if(LFP_OK != iRet)
        {
            LFP_THREADPOOL_INFO("pthread wait timeout, exit\n");
            goto worker_exit;
        }
        lfp_mutex_lock(&pstruThreadPool->mutex);
        pstruThreadPool->uiThreadIdle--;
        pWorkItem = work_queue_pop(pstruThreadPool->pstruWorkQueue);
        if(!pWorkItem)
        {
            lfp_mutex_unlock(&pstruThreadPool->mutex);
            continue;        
        }
        lfp_threadpool_set_thread_working(pstruThreadItem);
        lfp_mutex_unlock(&pstruThreadPool->mutex);

        pWorkItem->pWorkHandle(pWorkItem->pWorkData);
    }
worker_exit:
    lfp_mutex_lock(&pstruThreadPool->mutex);
    lfp_dlist_delete(&pstruThreadItem->node);
    lfp_mutex_unlock(&pstruThreadPool->mutex);
    LFP_SAFE_FREE(pstruThreadItem);
    return;
}

LFP_INT32 lfp_threadpool_create(LFP_UINT32 uiMaxThreads, LFP_UINT32 uiThreadTimeout)
{
    LFP_INT32 iRet = LFP_ERR;
    LFP_THREADPOOL_T *pstruThreadPool = LFP_NULL;

    pstruThreadPool = (LFP_THREADPOOL_T*)LFP_MALLOC(sizeof(*pstruThreadPool));
    LFP_ASSERT_ERR_RET(pstruThreadPool);
    LFP_BUFF_BEZERO(pstruThreadPool, sizeof(*pstruThreadPool));
    pstruThreadPool->enumState = LFP_THREADPOOL_STATE_WORKING;
    iRet = lfp_mutex_init(&pstruThreadPool->mutex, LFP_NULL);
    if(LFP_OK != iRet)
    {
        LFP_THREADPOOL_ERR("pthreadpool mutex init failed, iRet[%d], err[%s]", iRet, strerror(errno));
        goto freeAllRes;
    }
    pstruThreadPool->pstruThreadQueue = thread_queue_init();
    pstruThreadPool->pstruWorkQueue = work_queue_init();
    pstruThreadPool->threadpool_worker = lfp_threadpool_worker;
    pstruThreadPool->uiThreadMax = uiMaxThreads;
    pstruThreadPool->uiThreadTimeOut = uiThreadTimeout;
    pstruThreadPool->uiThreadAlive = 0;
    pstruThreadPool->uiThreadIdle = 0;
    return LFP_OK;
freeAllRes:
    (LFP_VOID)thread_queue_destory(pstruThreadPool->pstruThreadQueue);
    (LFP_VOID)work_queue_destory(pstruThreadPool->pstruWorkQueue);
    (LFP_VOID)lfp_mutex_destory(&pstruThreadPool->mutex);
    LFP_SAFE_FREE(pstruThreadPool);
    retrun LFP_ERR;
}


LFP_INT32 lfp_threadpool_dispatch(LFP_THREADPOOL_T *pstruThreadPool, LFP_VOID* pUsrData)
{
    (LFP_VOID)pstruThreadPool;
    (LFP_VOID)pUsrData;
    return LFP_OK;
}

LFP_INT32 lfp_threadpool_destory(LFP_THREADPOOL_T *pstruThreadPool)
{
    (LFP_VOID)pstruThreadPool;
    return LFP_OK;
}
