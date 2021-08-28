/*
 * @file name: lfp_app_threadpool.c
 * @Description: threadpool libs
 * @Author: wytaitaislee
 * @Date: 2021-03-21 17:59:18
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-08-28 23:02:09
 */

#include "lfp_base.h"
#include "lfp_libs_dlist.h"
#include "lfp_libs_list.h"
#include "lfp_libs_threadpool.h"

WORK_QUEUE_T *work_queue_init(LFP_VOID)
{
    LFP_INT32 iRet = LFP_ERR;
    WORK_QUEUE_T *pWorkQueue = NULL;

    pWorkQueue = (WORK_QUEUE_T*)LFP_MALLOC(sizeof(WORK_QUEUE_T));
    LFP_ASSERT_NULL_RET(pWorkQueue);
    pWorkQueue->uiQueueCnt = 0;
    iRet = lfp_dlist_init(&pWorkQueue->listHead);
    if(LFP_OK != iRet)
    {
        LFP_SAFE_FREE(pWorkQueue);
        return LFP_NULL;
    }
    return pWorkQueue;
}

/* add to the tail */
LFP_INT32 work_queue_add(WORK_QUEUE_T *pWorkQueue, LFP_VOID *pData)
{
    WORK_ITEM_T *pWorkItem = LFP_NULL;

    LFP_ASSERT_ERR_RET(pWorkQueue);
    pWorkItem = (WORK_ITEM_T*)LFP_MALLOC(sizeof(WORK_ITEM_T));
    LFP_ASSERT_ERR_RET(pWorkItem);
    pWorkItem->pWorkData = pData;
    if(LFP_OK != lfp_dlist_add_tail(&pWorkQueue->listHead, &pWorkItem->list))
    {
        LFP_SAFE_FREE(pWorkItem);
        return LFP_ERR;
    }
    pWorkQueue->uiQueueCnt++;
    return LFP_OK;
}

/* pop from the head */
LFP_STATIC WORK_ITEM_T* work_queue_pop(WORK_QUEUE_T *pWorkQueue)
{
    WORK_ITEM_T *pWorkItem = LFP_NULL;

    LFP_ASSERT_ERR_RET(pWorkQueue);
    pWorkItem = LFP_LIST_FIRST_ENTRY(pWorkQueue->listHead, WORK_ITEM_T, list);
    (LFP_VOID)lfp_dlist_delete(&pWorkQueue->listHead, pWorkQueue->listHead.pNext);
    return pWorkItem;
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