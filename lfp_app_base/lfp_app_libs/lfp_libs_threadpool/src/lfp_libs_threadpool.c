/*
 * @file name: lfp_app_threadpool.c
 * @Description: threadpool libs
 * @Author: wytaitaislee
 * @Date: 2021-03-21 17:59:18
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-09-21 18:15:24
 */

#include <errno.h>
#include <stdarg.h>
#include "lfp_base.h"
#include "lfp_libs_dlist.h"
#include "lfp_libs_list.h"
#include "lfp_arch_abstract.h"
#include "lfp_arch_adapter_mutex.h"
#include "lfp_arch_adapter_time.h"
#include "lfp_arch_adapter_semaphore.h"
#include "lfp_libs_threadpool.h"

/*@fn		  WORK_QUEUE_T *work_queue_init(LFP_VOID)
* @brief 	  work queue init.
* @param[in]  LFP_VOID
* @return	  WORK_QUEUE_T* / LFP_NULL
*/
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

/*@fn		  LFP_INT32 work_queue_add(WORK_QUEUE_T *pstruWorkQueue, WORK_ITEM_T *pstruWorkItem)
* @brief 	  add a new work request to the tail of the work queue.
* @param[in]  WORK_QUEUE_T *pstruWorkQueue - the work queue entry.
* @param[in]  WORK_ITEM_T *pstruWorkItem - work entry.
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 work_queue_add(WORK_QUEUE_T *pstruWorkQueue, WORK_ITEM_T *pstruWorkItem)
/*work_queue_t*, int argc, work_item_t* */
{
    LFP_ASSERT_ERR_RET(pstruWorkQueue && pstruWorkItem);
    if(LFP_OK != lfp_dlist_add_tail(&pstruWorkQueue->listHead, &pstruWorkItem->node))
    {
        return LFP_ERR;
    }
    pstruWorkQueue->uiWorkQueueCnt++;
    return LFP_OK;
}

/*@fn		  LFP_STATIC WORK_ITEM_T* work_queue_pop(WORK_QUEUE_T *pstruWorkQueue)
* @brief 	  get a work item form the head of the work queue.
* @param[in]  WORK_QUEUE_T *pstruWorkQueue - the work queue entry.
* @return	  WORK_ITEM_T* / LFP_NULL
*/
LFP_STATIC WORK_ITEM_T* work_queue_pop(WORK_QUEUE_T *pstruWorkQueue)/*work_queue_t *, int *argc, work_item_t** */
{
    WORK_ITEM_T *pstruWorkItem = LFP_NULL;

    LFP_ASSERT_NULL_RET(pstruWorkQueue);
    pstruWorkItem = LFP_LIST_FIRST_ENTRY(&pstruWorkQueue->listHead, WORK_ITEM_T, node);
    LFP_ASSERT_NULL_RET(pstruWorkItem);
    pstruWorkQueue->uiWorkQueueCnt--;
    (LFP_VOID)lfp_dlist_delete(pstruWorkQueue->listHead.pNext);
    return pstruWorkItem;
}

/*@fn		  LFP_STATIC LFP_INT32 work_queue_destroy(WORK_QUEUE_T *pstruWorkQueue)
* @brief 	  destroy the specified work queue .
* @param[in]  WORK_QUEUE_T *pstruWorkQueue - the work queue entry.
* @return	  LFP_OK / LFP_ERR
*/
LFP_STATIC LFP_INT32 work_queue_destroy(WORK_QUEUE_T *pstruWorkQueue)
{
    WORK_ITEM_T *pstruWorkItem = NULL;

    LFP_ASSERT_ERR_RET(pstruWorkQueue);
    pstruWorkQueue->uiWorkQueueCnt = 0;
    LFP_LIST_FOR_EACH_ENTRY(pstruWorkItem, &pstruWorkQueue->listHead, node)
    {
        pstruWorkItem->workHandle = LFP_NULL;
        LFP_SAFE_FREE(pstruWorkItem);
    }
    (LFP_VOID)lfp_dlist_destroy(&pstruWorkQueue->listHead);
    LFP_SAFE_FREE(pstruWorkQueue);
    return LFP_OK;
}

/*@fn		  LFP_STATIC THREAD_QUEUE_T* thread_queue_init(LFP_VOID)
* @brief 	  thread queue init.
* @param[in]  LFP_VOID
* @return	  THREAD_QUEUE_T* / LFP_NULL
*/
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

/*@fn		  LFP_STATIC THREAD_ITEM_T* thread_queue_add(THREAD_QUEUE_T *pstruThreadQueue)
* @brief 	  add a new thread request to the tail of the thread queue.
* @param[in]  THREAD_QUEUE_T *pstruThreadQueue - the thread queue entry.
* @return	  THREAD_ITEM_T* / LFP_NULL
*/
LFP_STATIC THREAD_ITEM_T* thread_queue_add(THREAD_QUEUE_T *pstruThreadQueue)
{
    THREAD_ITEM_T *pThreadItem = LFP_NULL;

    LFP_ASSERT_NULL_RET(pstruThreadQueue);
    pThreadItem = (THREAD_ITEM_T*)LFP_MALLOC(sizeof(THREAD_ITEM_T));
    LFP_ASSERT_NULL_RET(pThreadItem);
    pThreadItem->bWorking = LFP_FALSE;
    if(LFP_OK != lfp_semaphore_init(&pThreadItem->semphore, 0, 0))
    {
        LFP_THREADPOOL_ERR("thread semphore init failed\n");
        LFP_SAFE_FREE(pThreadItem); 
        return LFP_NULL;
    }
    pThreadItem->uiWorkerTime = 0;
    if(LFP_OK != lfp_dlist_add_tail(&pstruThreadQueue->listHead, &pThreadItem->node))
    {
        LFP_SAFE_FREE(pThreadItem);
        return LFP_NULL;
    }
    pstruThreadQueue->uiThreadQueueCnt++;
    return pThreadItem;
}

/*@fn		  LFP_STATIC LFP_INT32 thread_queue_delete(THREAD_ITEM_T *pThreadItem)
* @brief 	  delete a specified threadinfo from the head of the thread queue.
* @param[in]  THREAD_ITEM_T *pThreadItem - the thread queue entry.
* @return	  LFP_OK / LFP_ERR
*/
LFP_STATIC LFP_INT32 thread_queue_delete(THREAD_ITEM_T *pThreadItem)
{
    LFP_ASSERT_ERR_RET(pThreadItem);
    lfp_semaphore_destroy(&pThreadItem->semphore);
    (LFP_VOID)lfp_dlist_delete(&pThreadItem->node);
    LFP_SAFE_FREE(pThreadItem);
    return LFP_OK;
}

/*@fn		  LFP_STATIC LFP_INT32 thread_queue_destroy(THREAD_QUEUE_T *pstruThreadQueue)
* @brief 	  destroy the specified thread queue .
* @param[in]  WORK_QUEUE_T *pstruWorkQueue - the thread queue entry.
* @return	  LFP_OK / LFP_ERR
*/
LFP_STATIC LFP_INT32 thread_queue_destroy(THREAD_QUEUE_T *pstruThreadQueue)
{
    THREAD_ITEM_T *pThreadEntry = LFP_NULL;

    LFP_ASSERT_ERR_RET(pstruThreadQueue);
    LFP_LIST_FOR_EACH_ENTRY(pThreadEntry, &pstruThreadQueue->listHead, node)
    {
        lfp_semaphore_destroy(&pThreadEntry->semphore);
        LFP_SAFE_FREE(pThreadEntry);
    }
    lfp_dlist_destroy(&pstruThreadQueue->listHead);
    LFP_SAFE_FREE(pstruThreadQueue);
    pstruThreadQueue = LFP_NULL;
    return LFP_OK;
}

/*@fn		  LFP_STATIC LFP_INLINE LFP_VOID lfp_threadpool_set_thread_idle(THREAD_ITEM_T *pstruThreadItem)
* @brief 	  set a thread worker to be idle .
* @param[out] THREAD_ITEM_T *pstruThreadItem - the threadinfo entry.
* @return	  LFP_VOID
* @note       only in lfp_threadpool_worker , no need to lock again
*/
LFP_STATIC LFP_INLINE LFP_VOID lfp_threadpool_set_thread_idle(THREAD_ITEM_T *pstruThreadItem)
{
    pstruThreadItem->bWorking = LFP_FALSE;
    pstruThreadItem->uiWorkerTime = 0; 
}

/*@fn		  LFP_STATIC LFP_INLINE LFP_VOID lfp_threadpool_set_thread_working(THREAD_ITEM_T *pstruThreadItem)
* @brief 	  set a thread worker to be working .
* @param[out] THREAD_ITEM_T *pstruThreadItem - the threadinfo entry.
* @return	  LFP_VOID
* @note       only in lfp_threadpool_worker , no need to lock again
*/
LFP_STATIC LFP_INLINE LFP_VOID lfp_threadpool_set_thread_working(THREAD_ITEM_T *pstruThreadItem)
{
    pstruThreadItem->bWorking = LFP_TRUE;
    pstruThreadItem->uiWorkerTime = lfp_get_time(NULL);
}

LFP_STATIC LFP_INT32 lfp_threadpool_work_handle_proc(WORK_ITEM_T *pstruWorkItem)
{
    LFP_INT32 iArgc = 0, iArgCnt = 0;
    LFP_VOID*pArgs[LFP_THREADPOOL_MAX_ARGS_NUM]= {LFP_NULL};

    LFP_ASSERT_ERR_RET(pstruWorkItem);
    va_start(pstruWorkItem->vaList, pstruWorkItem->iArgc);
    for(iArgCnt = 0; iArgCnt < pstruWorkItem->iArgc; iArgCnt++)
    {
        pArgs[iArgCnt] = va_arg(pstruWorkItem->vaList, LFP_VOID*);
    }
    switch(pstruWorkItem->iArgc)
    {
        case 1:
            pstruWorkItem->workHandle(pArgs[0]);
            break;
        case 2:
            pstruWorkItem->workHandle(pArgs[0], pArgs[1]);
            break;
        case 3:
            pstruWorkItem->workHandle(pArgs[0], pArgs[1], pArgs[2]);
            break;
    }
    return LFP_OK;
}

/*@fn		  LFP_STATIC LFP_VOID lfp_threadpool_worker(LFP_VOID *pArgs)
* @brief 	  the thread worker.
* @param[in]  LFP_VOID *pArgs - thread worker args.
* @return	  LFP_VOID
*/
LFP_STATIC LFP_VOID lfp_threadpool_worker(LFP_VOID *pArgs)
{
    WORK_ITEM_T *pstruWorkItem = LFP_NULL; 
    LFP_THREADPOOL_T *pstruThreadPool = (LFP_THREADPOOL_T *)pArgs;
    THREAD_ITEM_T *pstruThreadItem = LFP_NULL;

    LFP_ASSERT_VOID_RET(pstruThreadPool);
    lfp_mutex_lock(&pstruThreadPool->mutex);
    pstruThreadItem = thread_queue_add(pstruThreadPool->pstruThreadQueue);
    if(!pstruThreadItem)
    {
        lfp_mutex_unlock(&pstruThreadPool->mutex);
        goto worker_exit;
    }
    (LFP_VOID)lfp_dlist_add_tail(&pstruThreadPool->pstruThreadQueue->listHead, &pstruThreadItem->node);
    lfp_mutex_unlock(&pstruThreadPool->mutex);

    while(LFP_THREADPOOL_STATE_EXIT != pstruThreadPool->enumState)
    {
        lfp_mutex_lock(&pstruThreadPool->mutex);
        lfp_threadpool_set_thread_idle(pstruThreadItem);
        pstruThreadPool->uiThreadIdle++;
        lfp_mutex_unlock(&pstruThreadPool->mutex);
        if(LFP_OK != lfp_semaphore_wait(&pstruThreadItem->semphore, pstruThreadPool->uiThreadTimeOut))
        {
            LFP_THREADPOOL_INFO("pthread wait timeout, exit\n");
            goto worker_exit;
        }
        lfp_mutex_lock(&pstruThreadPool->mutex);
        pstruThreadPool->uiThreadIdle--;
        pstruWorkItem = work_queue_pop(pstruThreadPool->pstruWorkQueue);
        if(!pstruWorkItem)
        {
            lfp_mutex_unlock(&pstruThreadPool->mutex);
            continue;        
        }
        lfp_threadpool_set_thread_working(pstruThreadItem);
        lfp_mutex_unlock(&pstruThreadPool->mutex);
        lfp_threadpool_work_handle_proc(pstruWorkItem);
    }
worker_exit:
    if(pstruThreadItem)
    {
        lfp_mutex_lock(&pstruThreadPool->mutex);
        lfp_dlist_delete(&pstruThreadItem->node);
        lfp_mutex_unlock(&pstruThreadPool->mutex);
        thread_queue_delete(pstruThreadItem);
    }
    LFP_SAFE_FREE(pstruThreadItem);
    return;
}

/*@fn		  LFP_INT32 lfp_threadpool_create(LFP_UINT32 uiMaxThreads, LFP_UINT32 uiThreadTimeout)
* @brief 	  create a threadpool entry.
* @param[in]  LFP_UINT32 uiMaxThreads - the maximum of the threadpool threads.
* @param[in]  LFP_UINT32 uiThreadTimeout - work thread timeout
* @return	  LFP_OK / LFP_ERR
*/
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
    if(!pstruThreadPool->pstruThreadQueue || !pstruThreadPool->pstruWorkQueue)
    {
        LFP_THREADPOOL_ERR("pthreadpool mutex init failed, iRet[%d], err[%s]", iRet, strerror(errno));
        goto freeAllRes;
    }
    pstruThreadPool->threadpool_worker = lfp_threadpool_worker;
    pstruThreadPool->uiThreadMax = uiMaxThreads;
    pstruThreadPool->uiThreadTimeOut = uiThreadTimeout;
    pstruThreadPool->uiThreadAlive = 0;
    pstruThreadPool->uiThreadIdle = 0;
    return LFP_OK;
freeAllRes:
    (LFP_VOID)thread_queue_destroy(pstruThreadPool->pstruThreadQueue);
    (LFP_VOID)work_queue_destroy(pstruThreadPool->pstruWorkQueue);
    (LFP_VOID)lfp_mutex_destroy(&pstruThreadPool->mutex);
    LFP_SAFE_FREE(pstruThreadPool);
    return LFP_ERR;
}

/*@fn		  LFP_STATIC LFP_INLINE LFP_INT32 lfp_threadpool_active_the_latest_idle_worker(THREAD_QUEUE_T *pstruThreadQueue)
* @brief 	  find and activate the most idle thread recently.
* @param[in]  THREAD_QUEUE_T *pstruThreadQueue - the thread queue.
* @return	  LFP_OK / LFP_ERR
*/
LFP_STATIC LFP_INLINE LFP_INT32 lfp_threadpool_active_the_latest_idle_worker(THREAD_QUEUE_T *pstruThreadQueue)
{
    THREAD_ITEM_T *pstruThreadItem = LFP_NULL;
    THREAD_ITEM_T *pstruThreadTmp = LFP_NULL;
    LFP_ASSERT_ERR_RET(pstruThreadQueue);

    LFP_LIST_FOR_EACH_ENTRY(pstruThreadTmp, &pstruThreadQueue->listHead, node)
    {
        if(!pstruThreadTmp->bWorking && pstruThreadTmp->uiWorkerTime > pstruThreadItem->uiWorkerTime)
        {
            pstruThreadItem = pstruThreadTmp;
        }
    }
    LFP_ASSERT_ERR_RET(pstruThreadItem);
    lfp_semaphore_post(&pstruThreadItem->semphore);
    return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_threadpool_dispatch(LFP_THREADPOOL_T *pstruThreadPool, 
                                  work_handle workHandle, 
                                  LFP_VOID* pUsrData)
* @brief 	  thread dispatch, 1. manage thread worker; 2. activate the most idle thread recently
* @param[in]  LFP_THREADPOOL_T *pstruThreadPool - threadpool entrty
* @param[in]  work_handle workHandle - work function ptr entry.
* @param[in]  LFP_VOID *pUsrData - work data.
* @return	  LFP_OK / LFP_ERR
*/

/*threadpool*, *pstruTid, *tid, priority, cpuno, work_handle, argc, ...*/
/* LFP_INT32 lfp_threadpool_dispatch(LFP_THREADPOOL_T *pstruThreadPool, 
                                  work_handle workHandle, 
                                  LFP_VOID* pUsrData) */
LFP_INT32 lfp_threadpool_dispatch(LFP_THREADPOOL_T *pstruThreadPool, 
                                  LFP_PTHREAD_HANDLE_T *pPthreadHandle,
                                  LFP_INT32 iPriority,
                                  LFP_INT32 iCpuNo,
                                  work_handle workHandle, 
                                  LFP_INT32 iArgc, ...)
{
    LFP_INT32 iArgCnt = 0;
    WORK_ITEM_T *pstruWorkItem = LFP_NULL;
    
    LFP_ASSERT_ERR_RET(pstruThreadPool && workHandle);
    pstruWorkItem = (WORK_ITEM_T*)LFP_MALLOC(sizeof(WORK_ITEM_T));
    LFP_ASSERT_ERR_RET(pstruWorkItem);
    pstruWorkItem->workHandle = workHandle;
    va_start(pstruWorkItem->vaList, iArgc);
    for(iArgCnt = 0; iArgCnt < iArgc; iArgCnt++)
    {
        va_arg(pstruWorkItem->vaList, LFP_VOID*);
    }
    va_end(pstruWorkItem->vaList); 
    
    lfp_mutex_lock(&pstruThreadPool->mutex);
    work_queue_add(pstruThreadPool->pstruWorkQueue, pstruWorkItem);
    
    if(0 == pstruThreadPool->uiThreadIdle && pstruThreadPool->uiThreadAlive < pstruThreadPool->uiThreadMax)
    {
        /*thread_detached_create(th-worker, threadpool*, stack, priority)*/
        //if(LFP_OK != lfp_pthread_create())
        //{
        //    LFP_PTHREAD_ERR("create a new worker failed\n");
        //}
        //else
        {
            pstruThreadPool->uiThreadAlive++;
        }
    }
    if(lfp_threadpool_active_the_latest_idle_worker(pstruThreadPool->pstruThreadQueue))
    {
        LFP_THREADPOOL_ERR("active the latest idle worker failed\n");
    }
    lfp_mutex_unlock(&pstruThreadPool->mutex);
    
    return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_threadpool_destroy(LFP_THREADPOOL_T *pstruThreadPool)
* @brief 	  destory the specified threadpool entry.
* @param[in]  LFP_THREADPOOL_T *pstruThreadPool - threadpool entrty
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_threadpool_destroy(LFP_THREADPOOL_T *pstruThreadPool)
{
    (LFP_VOID)pstruThreadPool;
    lfp_dlist_destroy(&pstruThreadPool->pstruWorkQueue->listHead);
    lfp_dlist_destroy(&pstruThreadPool->pstruThreadQueue->listHead);
    lfp_mutex_destroy(&pstruThreadPool->mutex);
    LFP_SAFE_FREE(pstruThreadPool);
    return LFP_OK;
}
