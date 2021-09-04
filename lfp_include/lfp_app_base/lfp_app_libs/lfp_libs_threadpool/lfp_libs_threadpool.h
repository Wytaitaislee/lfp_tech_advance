/*
 * @fileName: lfp_libs_threadpool.h
 * @Description: threadpool libs
 * @Author: wytaitaislee
 * @Date: 2021-03-21 18:00:21
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-09-04 20:05:10
 */

#ifndef __LFP_LIBS_THREADPOOL_H__
#define __LFP_LIBS_THREADPOOL_H__

#include "lfp_arch_adapter.h"
#include "lfp_libs_dlist.h"
#include "lfp_base.h"

#define LFP_THREADPOOL_CRIT(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_CRIT, UTIL_MODULE_DLIST, MASK_DLIST, __VA_ARGS__)
#define LFP_THREADPOOL_ERR(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_ERR, UTIL_MODULE_DLIST, MASK_DLIST, __VA_ARGS__)
#define LFP_THREADPOOL_INFO(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_INFO, UTIL_MODULE_DLIST, MASK_DLIST, __VA_ARGS__) 

typedef LFP_VOID* (work_handle)(LFP_VOID*, ...);

typedef struct work_item_t
{
    work_handle *pWorkHandle;
    LFP_VOID    *pWorkData;
    LFP_DLIST_T node;
}WORK_ITEM_T;

typedef struct work_queue_t
{
    LFP_UINT32  uiWorkQueueCnt;
    LFP_DLIST_T listHead;
}WORK_QUEUE_T;

typedef struct thread_item_t
{
    LFP_SEM_T   semphore;
    LFP_BOOL    bWorking;
    LFP_TIME_T  uiWorkerTime;
    LFP_DLIST_T node;
}THREAD_ITEM_T;

typedef struct thread_queue_t
{
    LFP_UINT32 uiThreadQueueCnt;
    LFP_DLIST_T listHead;
}THREAD_QUEUE_T;

typedef enum
{
    LFP_THREADPOOL_STATE_INVALID = 0,
    LFP_THREADPOOL_STATE_WORKING,
    LFP_THREADPOOL_STATE_EXIT
}LFP_THREADPOOL_STATE_E;

typedef struct lfp_threadpool_t
{
    LFP_MUTEX_T mutex;
    LFP_THREADPOOL_STATE_E enumState;
    LFP_UINT32 uiThreadMax;
    LFP_UINT32 uiThreadAlive;
    LFP_UINT32 uiThreadIdle;
    LFP_UINT32 uiThreadTimeOut;
    LFP_VOID (*threadpool_worker)(LFP_VOID*);
    WORK_QUEUE_T *pstruWorkQueue;
    THREAD_QUEUE_T *pstruThreadQueue;
}LFP_THREADPOOL_T;

#endif /* end of __LFP_APP_THREADPOOL_H__ */

