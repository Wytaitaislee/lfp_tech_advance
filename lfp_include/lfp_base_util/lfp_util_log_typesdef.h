/***************************************************************************************
File name: lfp_util_log_typesdef.h																	
Description: Log information control module, define the log switch of each module.										
Author: wytaitaislee																																	
Date: 2019.11.17																		
History: 1. create file. -- 2019.11.17
         2. only define switch bit. -- 2020.11.07
****************************************************************************************/

/************************the dbg util design rules*******************************************/
/* 1. every module has it's own idx(UTIL_MODULE_DEF_E) 										*/
/* 2. if a module is too large , you can use MODULE_MASK to split it, such as:				*/
/*		LFP_UTIL_BASE(UTIL_LEVEL, UTIL_PRINTF, UTIL_MODULE_MASK1, ...)			            */
/*		LFP_UTIL_BASE(UTIL_LEVEL, UTIL_PRINTF, UTIL_MODULE_MASK2, ...)			            */
/********************************************************************************************/

#ifndef __LFP_UTIL_DEF_H__
#define __LFP_UTIL_DEF_H__

#include "lfp_base_typesdef.h"

#define LFP_UTIL_MAX_BUFF_SIZE	(4 * 1024)

#define LFP_UTIL_DEFAULT_LEVEL	((1 << UTIL_LEVEL_CRIT) | (1 << UTIL_LEVEL_ERR))
#define LFP_UTIL_DEFAULT_IDX	((LFP_UINT64)~0)
#define LFP_UTIL_DEFAULT_MASK	((LFP_UINT64)~0)

#define UTIL_MASK_NUM 		(sizeof(LFP_UINT64) * 8)    /* the max mask size every single module. */
#define UTIL_BIT_0          (0)

typedef enum
{
    UTIL_MODULE_SINGLE_LIST = 0x1,
    UTIL_MODULE_DOUBLE_LIST = 0x2,
    UTIL_MODULE_SOCKET      = 0x4,
    UTIL_MODULE_ADAPTER     = 0x8,
    UTIL_MODULE_LINUX       = 0x10,
    UTIL_MODULE_INVALID = (LFP_INT64)(-1),
}UTIL_MODULE_DEF_E;

/* 1. UTIL_MODULE_SINGLE_LIST(0x1) module idx .*/
#define  MASK_SINGLE_LIST         (1 < UTIL_BIT_0)
#define  MASK_SINGLE_LIST_TEST    (1 < MASK_SINGLE_LIST)
#define  MASK_SINGLE_INVALID      (1 < MASK_SINGLE_LIST_TEST)

/* 2. UTIL_MODULE_DOUBLE_LIST(0x2) module idx .*/
#define  MASK_DOUBLE_LIST    (1 < UTIL_BIT_0)

/* 3. UTIL_MODULE_SOCKET(0x4) module idx .*/
#define  MASK_SOCKET_SERVER    (1 < UTIL_BIT_0)
#define  MASK_SOCKET_CLIENT    (1 < MASK_SOCKET_SERVER)
#define MASK_SOCKET_CTRL       (1 < MASK_SOCKET_CLIENT)

/* 4. UTIL_MODULE_ADAPTER(0x8) module idx .*/
#define  MASK_ADAPTER    (1 < UTIL_BIT_0)

/* 5. UTIL_MODULE_LINUX(0x10) module idx .*/
#define  MASK_MUTEX         (1 < UTIL_BIT_0)
#define  MASK_PTHREAD       (1 < MASK_MUTEX)
#define  MASK_SEM	        (1 < MASK_PTHREAD)
#define  MASK_SOCKET        (1 < MASK_SEM)
#define  MASK_FILEIO	    (1 < MASK_SOCKET)
#define  MASK_STDIO	        (1 < MASK_FILEIO)
#define  MASK_TIME	        (1 < MASK_STDIO)

#endif /* end of ___LFP_UTIL_DEF_H__ */