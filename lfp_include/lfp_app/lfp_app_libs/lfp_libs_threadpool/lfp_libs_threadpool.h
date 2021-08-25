/*
 * @fileName: lfp_libs_threadpool.h
 * @Description: threadpool libs
 * @Author: wytaitaislee
 * @Date: 2021-03-21 18:00:21
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-08-25 22:55:43
 */

#ifndef __LFP_LIBS_THREADPOOL_H__
#define __LFP_LIBS_THREADPOOL_H__

#include "lfp_arch_adapter.h"
#include "lfp_libs_dlist.h"

#define LFP_THREADPOOL_CRIT(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_CRIT, UTIL_MODULE_DLIST, MASK_DLIST, __VA_ARGS__)
#define LFP_THREADPOOL_ERR(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_ERR, UTIL_MODULE_DLIST, MASK_DLIST, __VA_ARGS__)
#define LFP_THREADPOOL_INFO(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_INFO, UTIL_MODULE_DLIST, MASK_DLIST, __VA_ARGS__) 

typedef struct work_item_t
{
    LFP_DLIST_T *list;
    LFP_VOID    *pWorkData;
}WORK_ITEM_T;

typedef struct work_queue_t
{
    LFP_UINT32  uiQueueCnt;
    WORK_ITEM_T *pWorkQueueHead;
}WORK_QUEUE_T;

typedef struct thread_queue_t
{
    LFP_SEM_T   semphore;
    LFP_TIME_T  uiWorkerTime;
    LFP_DLIST_T *pThreadQueueHead;
}THREAD_QUEUE_T;

typedef enum
{
    LFP_THREADPOOL_STATE_INVALID,
    LFP_THREADPOOL_STATE_WORKING,
    LFP_THREADPOOL_STATE_EXIT
}LFP_THREADPOOL_STATE_E;

typedef struct lfp_threadpool_t
{
    LFP_MUTEX_T mutex;
    LFP_THREADPOOL_STATE_E enumState;
    HPR_UINT32 uiThreadMax;
    HPR_UINT32 uiThreadAlive;
    HPR_UINT32 uiThreadIdle;
    HPR_UINT32 uiThreadTimeOut;
    LFP_VOID (*handler)(LFP_VOID*);
    WORK_QUEUE_T *pWorkQueue;
    THREAD_QUEUE_T *pThreadQueue;
}LFP_THREADPOOL_T;
#endif /* end of __LFP_APP_THREADPOOL_H__ */