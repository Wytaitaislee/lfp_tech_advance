/*
 * @file name: lfp_app_threadpool.c
 * @Description: threadpool libs
 * @Author: wytaitaislee
 * @Date: 2021-03-21 17:59:18
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-08-25 23:05:49
 */

#include "lfp_base.h"
#include "lfp_libs_dlist.h"
#include "lfp_libs_threadpool.h"

WORK_QUEUE_T *work_queue_create(LFP_VOID)
{
    WORK_QUEUE_T *pWorkQueue = NULL;

    pWorkQueue = (WORK_QUEUE_T*)LFP_MALLOC(sizeof(WORK_QUEUE_T)));
    LFP_ASSERT_NULL_RET(pWorkQueue);
    pWorkQueue->uiQueueCnt = 0;
    pWorkQueue->pWorkHead = (WORK_ITEM_T*)LFP_MALLOC(sizeof(WORK_ITEM_T)));
    if(!pWorkQueue->pWorkHead)
    {
        LFP_SAFE_FREE(pWorkQueue);
        return LFP_NULL;
    }
    pWorkQueue->pWorkHead->pWorkData = LFP_NULL;
    iRet = lfp_dlist_init(&pWorkQueue->pWorkHead->list);
    if(LFP_OK != iRet)
    {
        LFP_SAFE_FREE(pWorkQueue->pWorkHead);
        LFP_SAFE_FREE(pWorkQueue);
        return LFP_NULL;
    }
    return pWorkQueue;
}

LFP_INT32 work_queue_add(WORK_QUEUE_T *pWorkQueue, LFP_VOID *pData)
{
    WORK_ITEM_T *pWorkItem = LFP_NULL;

    LFP_ASSERT_ERR_RET(pWorkQueue && pWorkQueue->pWorkHead);
    pWorkItem = (WORK_ITEM_T*)LFP_MALLOC(sizeof(WORK_ITEM_T));
    LFP_ASSERT_ERR_RET(pWorkItem);
    pWorkItem->pWorkData = pData;
    if(LFP_OK != lfp_dlist_add(pWorkQueue->pWorkHead->list, pWorkItem->list))
    {
        LFP_SAFE_FREE(pWorkItem);
        return LFP_ERR;
    }
    pWorkQueue->uiQueueCnt++;
    return LFP_OK;
}

LFP_STATIC WORK_ITEM_T* work_queue_pop(WORK_QUEUE_T *pWorkQueue)
{
    WORK_ITEM_T *pWorkItem = LFP_NULL;

    LFP_ASSERT_ERR_RET(pWorkQueue);
    pWorkItem = pWorkQueue->pWorkQueueHead;
}

LFP_INT32 lfp_threadpool_create(LFP_UINT32 uiMaxThreads, LFP_UINT32 uiThreadTimeout, 
                                LFP_VOID (*handler)(LFP_VOID*))
{
    
}


LFP_INT32 lfp_threadpool_dispatch(LFP_THREADPOOL_T *pThreadPool, LFP_VOID* pUsrData)
{

}

LFP_INT32 lfp_threadpool_destory(LFP_THREADPOOL_T *pThreadPool)
{

}