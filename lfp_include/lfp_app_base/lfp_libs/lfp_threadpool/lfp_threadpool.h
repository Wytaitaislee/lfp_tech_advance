/***
 * @FilePath: lfp_threadpool.h
 * @Description: threadpool libs.
 * @Author: wytaitaislee
 * @Date: 2021-08-27 23:29:52
 * @LastEditTime: 2022-03-05 21:24:05
 * @LastEditors: wytaitaislee
 * @Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#ifndef __LFP_LIBS_THREADPOOL_H__
#define __LFP_LIBS_THREADPOOL_H__

#include "lfp_arch_adapter.h"
#include "lfp_base.h"
#include "lfp_dlist/lfp_dlist.h"

#define LFP_THREADPOOL_MAX_ARGS_NUM \
    (5) /* Maximum number of thread pool work task parameters */

#define LFP_THREADPOOL_CRIT(...) \
    LFP_LOG_BASE(LOG_LEVEL_CRIT, LOG_MODULE_THPOOL, MASK_THPOOL, ##__VA_ARGS__)
#define LFP_THREADPOOL_ERR(...) \
    LFP_LOG_BASE(LOG_LEVEL_ERR, LOG_MODULE_THPOOL, MASK_THPOOL, ##__VA_ARGS__)
#define LFP_THREADPOOL_INFO(...) \
    LFP_LOG_BASE(LOG_LEVEL_INFO, LOG_MODULE_THPOOL, MASK_THPOOL, ##__VA_ARGS__)

#define LFP_THREADPOOL_MAX_PARAM_NUM (5)

typedef LFP_VOID* (*work_handle)(LFP_VOID*, ...);

typedef struct lfp_thpool_list_t {
    LFP_UINT32 uiCount;
    LFP_DLIST_T node;
} LFP_THPOOL_LIST_T;

typedef struct work_item_t {
    work_handle workHandle;
    LFP_INT32 iArgc;
    LFP_VOID* pArg[LFP_THREADPOOL_MAX_PARAM_NUM];
    va_list vaList;
    LFP_DLIST_T node;
} WORK_ITEM_T;

typedef struct thread_item_t {
    LFP_SEM_T semphore;
    LFP_BOOL bWorking;
    LFP_TIME_T uiWorkerTime;
    LFP_DLIST_T node;
} THREAD_ITEM_T;

typedef enum {
    LFP_THREADPOOL_STATE_INVALID = 0,
    LFP_THREADPOOL_STATE_WORKING,
    LFP_THREADPOOL_STATE_EXIT
} LFP_THREADPOOL_STATE_E;

typedef struct lfp_threadpool_t {
    LFP_MUTEX_T mutex;
    LFP_THREADPOOL_STATE_E enumState;
    LFP_UINT32 uiThreadMax;
    LFP_UINT32 uiThreadAlive;
    LFP_UINT32 uiThreadIdle;
    LFP_UINT32 uiThreadTimeOut;
    LFP_VOID(*threadpool_worker)
    (LFP_VOID*);
    LFP_THPOOL_LIST_T struWorkQueueList;
    LFP_THPOOL_LIST_T struThreadQueueList;
} LFP_THREADPOOL_T;

#endif /* end of __LFP_APP_THREADPOOL_H__ */
