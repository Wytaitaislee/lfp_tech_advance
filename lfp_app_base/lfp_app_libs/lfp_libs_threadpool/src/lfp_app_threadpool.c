/*
 * @file name: lfp_app_threadpool.c
 * @Description: threadpool libs
 * @Author: wytaitaislee
 * @Date: 2021-03-21 17:59:18
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-08-22 19:04:04
 */

#include "lfp_base.h"
#include "lfp_libs_threadpool.h"

WORK_QUEUE_T *work_queue_create(LFP_VOID)
{
    WORK_QUEUE_T *pWorkQueue = NULL;

    pWorkQueue = (WORK_QUEUE_T*)LFP_MALLOC(sizeof(WORK_QUEUE_T)));
    LFP_ASSERT_NULL_RET(pWorkQueue);
    pWorkQueue->uiQueueCnt = 0;
    pWorkQueue->pWorkList = LFP_NULL;
    return pWorkQueue;
}

LFP_INT32 work_queue_add(WORK_QUEUE_T *pWorkQueue, WORK_QUEUE_T *pEntry)
{
    LFP_ASSERT_ERR_RET(pWorkQueue && pEntry);

    lfp_dlist_add(pWorkQueue->, pEntry);
}

LFP_INT32 work_queue_pop()
{

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