/*
 * @file name: lfp_app_threadpool.c
 * @Description: threadpool libs
 * @Author: wytaitaislee
 * @Date: 2021-03-21 17:59:18
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-09-04 16:04:00
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
    pstruWorkQueue->uiQueueCnt = 0;
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
    if(LFP_OK != lfp_dlist_add_tail(&pstruWorkQueue->listHead, &pWorkItem->listNode))
    {
        LFP_SAFE_FREE(pWorkItem);
        return LFP_ERR;
    }
    pstruWorkQueue->uiQueueCnt++;
    return LFP_OK;
}

/* pop from the head */
LFP_STATIC WORK_ITEM_T* work_queue_pop(WORK_QUEUE_T *pstruWorkQueue)
{
    WORK_ITEM_T *pWorkItem = LFP_NULL;
    LFP_VOID *pData = LFP_NULL;

    LFP_ASSERT_NULL_RET(pstruWorkQueue);
    pWorkItem = LFP_LIST_FIRST_ENTRY(&pstruWorkQueue->listHead, WORK_ITEM_T, listNode);
    LFP_ASSERT_NULL_RET(pWorkItem);
    (LFP_VOID)lfp_dlist_delete(pstruWorkQueue->listHead.pNext);
    return pWorkItem;
}

LFP_STATIC LFP_INT32 work_queue_destory(WORK_QUEUE_T *pstruWorkQueue)
{
    LFP_INT32 iRet = LFP_ERR;
    WORK_ITEM_T *pstruWorkItem = NULL;

    LFP_ASSERT_ERR_RET(pstruWorkQueue);
    pstruWorkQueue->uiQueueCnt = 0;
    LFP_LIST_FOR_EACH_ENTRY(pstruWorkItem, &pstruWorkQueue->listHead, listNode)
    {
        pstruWorkItem->pWorkData = LFP_NULL;
        pstruWorkItem->pWorkHandle = LFP_NULL;
    }
    iRet = lfp_dlist_init(&pstruWorkQueue->listHead);
    if(LFP_OK != iRet)
    {
        LFP_SAFE_FREE(pstruWorkQueue);
        return LFP_NULL;
    }
    return pstruWorkQueue;
}

/* pop from the head */
LFP_STATIC THREAD_QUEUE_T* thread_queue_init(LFP_VOID)
{
    LFP_INT32 iRet = LFP_ERR;
    THREAD_QUEUE_T *pstruThreadQueue = NULL;

    pstruThreadQueue = (THREAD_QUEUE_T*)LFP_MALLOC(sizeof(*pstruThreadQueue));
    LFP_ASSERT_NULL_RET(pstruThreadQueue);
    pstruThreadQueue->bWorking = 0;
    iRet = lfp_dlist_init(&pstruThreadQueue->listHead);
    if(LFP_OK != iRet)
    {
        LFP_SAFE_FREE(pstruThreadQueue);
        return LFP_NULL;
    }
    return pstruThreadQueue;
}

LFP_STATIC THREAD_QUEUE_T* thread_queue_destory(THREAD_QUEUE_T *pstruThreadQueue)
{
    THREAD_QUEUE_T *pThreadEntry = LFP_NULL;

    LFP_ASSERT_ERR_RET(pstruThreadQueue);
    LFP_LIST_FOR_EACH_ENTRY(pThreadEntry, &pstruThreadQueue->listHead, listHead)
    {
        lfp_mutex_destory(pThreadEntry->semphore);
    }
    lfp_dlist_destory(pstruThreadQueue->listHead);
    pstruThreadQueue = LFP_NULL;
    return LFP_OK;
}

LFP_STATIC LFP_INLINE LFP_INT32 lfp_threadpool_lock(LFP_MUTEX_T *pMutex)
{
    LFP_ASSERT_ERR_RET(pMutex);
    lfp_mutex_lock(pMutex);
    return LFP_OK;
}
LFP_STATIC LFP_INLINE LFP_INT32 lfp_threadpool_unlock(LFP_MUTEX_T *pMutex)
{
    LFP_ASSERT_ERR_RET(pMutex);
    lfp_mutex_unlock(pMutex);
    return LFP_OK;
}

/* only in lfp_threadpool_worker , no need to lock again */
LFP_STATIC LFP_INLINE LFP_VOID lfp_threadpool_set_thread_idle()
{

}

LFP_STATIC LFP_VOID lfp_threadpool_worker(LFP_VOID *pArgs)
{
    LFP_INT32 iRet = LFP_ERR;
    WORK_ITEM_T *pWorkItem = LFP_NULL; 
    LFP_THREADPOOL_T *pThreadPool = (LFP_THREADPOOL_T *)pArgs;
    THREAD_QUEUE_T *pstruThreadInfo = LFP_NULL;

    LFP_ASSERT_ERR_RET(pThreadPool);
    pstruThreadInfo = (THREAD_QUEUE_T *)LFP_MALLOC(sizeof*(pstruThreadInfo));
    LFP_ASSERT_ERR_RET(pstruThreadInfo);
    LFP_BUFF_BEZERO(pstruThreadInfo, sizeof(*pstruThreadInfo));
    if(LFP_OK != lfp_semphore_create(pstruThreadInfo->semphore, 0, 0))
    {

    }
    pstruThreadInfo->uiWorkerTime = 0;
    pstruThreadInfo->bWorking = 0;
    lfp_threadpool_lock(&pThreadPool->mutex);
    lfp_dlist_add_tail(&pThreadPool->pstruThreadQueue->listHead, &pstruThreadInfo->listHead);
    lfp_threadpool_unlock(&pThreadPool->mutex);

    while(LFP_THREADPOOL_STATE_EXIT != pThreadPool->enumState)
    {
        lfp_threadpool_lock(&pThreadPool->mutex);
        pThreadPool->uiThreadIdle++;
        lfp_threadpool_unlock(&pThreadPool->mutex);
        iRet = lfp_semphore_wait(&pThreadPool->pstruThreadQueue->semphore, pThreadPool->uiThreadTimeOut);
        if(LFP_OK != iRet)
        {
            //timeout
        }
        lfp_threadpool_lock(&pThreadPool->mutex);
        pThreadPool->uiThreadIdle--;
        pWorkItem = work_queue_pop(pThreadPool->pstruWorkQueue);
        if(pWorkItem)
        {
            pstruThreadInfo->bWorking = LFP_FALSE;
            pstruThreadInfo->uiWorkerTime = 0;    
            continue;        
        }
        else
        {
            pstruThreadInfo->bWorking = LFP_TRUE;
            pstruThreadInfo->uiWorkerTime = lfp_get_time(NULL);

        }
        lfp_threadpool_unlock(&pThreadPool->mutex);

        pWorkItem->pWorkHandle(pWorkItem->pWorkData);
    }

    LFP_SAFE_FREE(pstruThreadInfo);
    return;
}

LFP_INT32 lfp_threadpool_create(LFP_UINT32 uiMaxThreads, LFP_UINT32 uiThreadTimeout)
{
    LFP_INT32 iRet = LFP_ERR;
    LFP_THREADPOOL_T *pThreadPool = LFP_NULL;

    pThreadPool = (LFP_THREADPOOL_T*)LFP_MALLOC(sizeof(*pThreadPool));
    LFP_ASSERT_ERR_RET(pThreadPool);
    LFP_BUFF_BEZERO(pThreadPool, sizeof(*pThreadPool));
    pThreadPool->enumState = LFP_THREADPOOL_STATE_WORKING;
    iRet = lfp_mutex_init(&pThreadPool->mutex, LFP_NULL);
    if(LFP_OK != iRet)
    {
        LFP_THREADPOOL_ERR("pthreadpool mutex init failed, iRet[%d], err[%s]", iRet, strerror(errno));
        goto freeAllRes;
    }
    pThreadPool->pstruThreadQueue = thread_queue_init();
    pThreadPool->pstruWorkQueue = work_queue_init();
    pThreadPool->threadpool_worker = lfp_threadpool_worker;
    pThreadPool->uiThreadMax = uiMaxThreads;
    pThreadPool->uiThreadTimeOut = uiThreadTimeout;
    pThreadPool->uiThreadAlive = 0;
    pThreadPool->uiThreadIdle = 0;
    return LFP_OK;
freeAllRes:
    (LFP_VOID)thread_queue_destory(pThreadPool->pstruThreadQueue);
    (LFP_VOID)work_queue_destory(pThreadPool->pstruWorkQueue);
    (LFP_VOID)lfp_mutex_destory(&pThreadPool->mutex);
    LFP_SAFE_FREE(pThreadPool);
    retrun LFP_ERR;
}


LFP_INT32 lfp_threadpool_dispatch(LFP_THREADPOOL_T *pThreadPool, LFP_VOID* pUsrData)
{
    (LFP_VOID)pThreadPool;
    (LFP_VOID)pUsrData;
    return LFP_OK;
}

LFP_INT32 lfp_threadpool_destory(LFP_THREADPOOL_T *pThreadPool)
{
    (LFP_VOID)pThreadPool;
    return LFP_OK;
}
