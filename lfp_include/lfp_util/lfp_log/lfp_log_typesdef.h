/***
 * @FilePath     : lfp_log_typesdef.h
 * @Description  : Log information control module, define the log switch of each
 * module.
 * @Author       : wytaitaislee
 * @Date         : 2021-08-27 23:29:52
 * @LastEditTime : 2022-03-05 19:48:04
 * @LastEditors  : wytaitaislee
 * @Copyright 2022 wytaitaislee, All Rights Reserved.
 */

/***************the dbg util design rules****************************
 * 1. every module has it's own idx(LOG_MODULE_DEF_E)
 * 2. if a module is too large , you can use MODULE_MASK to split it, such as:
 *		LFP_LOG_BASE(LOG_LEVEL, LOG_PRINTF, LOG_MODULE_MASK1, ...)
 *		LFP_LOG_BASE(LOG_LEVEL, LOG_PRINTF, LOG_MODULE_MASK2, ...)
 ********************************************************************/

#ifndef __LFP_LOG_TYPESDEF_H__
#define __LFP_LOG_TYPESDEF_H__

#include "__include/lfp_typesdef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LFP_LOG_MAX_BUFF_SIZE (4 * 1024)

#define LFP_LOG_DEFAULT_LEVEL ((1 << LOG_LEVEL_CRIT) | (1 << LOG_LEVEL_ERR))
#define LFP_LOG_DEFAULT_IDX ((LFP_UINT64)~0)
#define LFP_LOG_DEFAULT_MASK ((LFP_UINT64)~0)

#define LOG_MASK_NUM \
    (sizeof(LFP_UINT64) * 8) /* the max mask size every single module. */
#define LOG_BIT_0 (0)

typedef enum {
    LOG_LEVEL_CRIT = 0x1,
    LOG_LEVEL_ERR = 0x2,
    LOG_LEVEL_INFO = 0x4,
    LOG_LEVEL_MAX,
} LFP_LOG_LEVEL_E;

typedef enum {
    LOG_MODULE_SLIST = 0x1,
    LOG_MODULE_DLIST = 0x2,
    LOG_MODULE_SOCKET = 0x4,
    LOG_MODULE_ADAPTER = 0x8,
    LOG_MODULE_LINUX = 0x10,
    LOG_MODULE_BUSYBOX = 0x20,
    LOG_MODULE_THPOOL = 0x40,
    LOG_MODULE_INVALID = (LFP_INT64)(-1),
} LOG_MODULE_DEF_E;

/* 1. LOG_MODULE_LIBS_SLIST(0x1) module idx .*/
#define MASK_SLIST (1 < LOG_BIT_0)
#define MASK_SLIST_TEST (1 < MASK_SLIST)
#define MASK_SLIST_INVALID (1 < MASK_SLIST_TEST)

/* 2. LOG_MODULE_DLIST(0x2) module idx .*/
#define MASK_DLIST (1 < LOG_BIT_0)

/* 3. LOG_MODULE_SOCKET(0x4) module idx .*/
#define MASK_SOCKET_SERVER (1 < LOG_BIT_0)
#define MASK_SOCKET_CLIENT (1 < MASK_SOCKET_SERVER)
#define MASK_SOCKET_CTRL (1 < MASK_SOCKET_CLIENT)

/* 4. LOG_MODULE_ADAPTER(0x8) module idx .*/
#define MASK_ADAPTER (1 < LOG_BIT_0)

/* 5. LOG_MODULE_LINUX(0x10) module idx .*/
#define MASK_MUTEX (1 < LOG_BIT_0)
#define MASK_PTHREAD (1 < MASK_MUTEX)
#define MASK_SEM (1 < MASK_PTHREAD)
#define MASK_SOCKET (1 < MASK_SEM)
#define MASK_FILEIO (1 < MASK_SOCKET)
#define MASK_STDIO (1 < MASK_FILEIO)
#define MASK_TIME (1 < MASK_STDIO)

/* 6. LOG_MODEL_BUSYBOX(0x20) module idx .*/
#define MASK_BUSYBOX (1 < LOG_BIT_0)

/* 6. LOG_MODULE_THPOOL(0x40) module idx .*/
#define MASK_THPOOL (1 < LOG_BIT_0)

#endif /* end of __LFP_LOG_TYPESDEF_H__ */