/*
 * @fileName: lfp_libs_threadpool.h
 * @Description: threadpool libs
 * @Author: wytaitaislee
 * @Date: 2021-03-21 18:00:21
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-12-11 16:11:06
 */

#ifndef __LFP_LIBS_THREADPOOL_H__
#define __LFP_LIBS_THREADPOOL_H__

#include "lfp_arch_adapter.h"
#include "lfp_libs_dlist.h"
#include "lfp_base.h"

#define LFP_THREADPOOL_MAX_ARGS_NUM (5)    /* Maximum number of thread pool work task parameters */

#define LFP_THREADPOOL_CRIT(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_CRIT, UTIL_MODULE_DLIST, MASK_DLIST, __VA_ARGS__)
#define LFP_THREADPOOL_ERR(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_ERR, UTIL_MODULE_DLIST, MASK_DLIST, __VA_ARGS__)
#define LFP_THREADPOOL_INFO(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_INFO, UTIL_MODULE_DLIST, MASK_DLIST, __VA_ARGS__) 

typedef LFP_VOID* (*work_handle)(LFP_VOID*, ...);

typedef struct lfp_thpool_list_t
{
    LFP_UINT32 uiCount;
    LFP_DLIST_T node;
}LFP_THPOOL_LIST_T;

typedef struct work_item_t
{
    work_handle workHandle;
    LFP_INT32   iArgc;
    va_list     vaList;
    LFP_DLIST_T node;
}WORK_ITEM_T;

typedef struct thread_item_t
{
    LFP_SEM_T   semphore;
    LFP_BOOL    bWorking;
    LFP_TIME_T  uiWorkerTime;
    LFP_DLIST_T node;
}THREAD_ITEM_T;

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
    LFP_THPOOL_LIST_T struWorkQueueList;
    LFP_THPOOL_LIST_T struThreadQueueList;
}LFP_THREADPOOL_T;

#endif /* end of __LFP_APP_THREADPOOL_H__ */

