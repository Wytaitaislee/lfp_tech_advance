/***************************************************************************************
File name: __lfp_util_def.h																	
Description: Log information control module.											
Author: wytaitaislee																	
Version: V1.0.0																			
Date: 2019-11-17																		
History: 1. create file. -- 2019-11-17
         2. adjust the output arch. -- 2020-03-12
****************************************************************************************/

/************************the dbg util design rules*******************************************/
/* 1. every module has it's own idx(UTIL_MODULE_DEF_E) 										*/
/* 2. if a module is too large , you can use MODULE_MASK to split it, such as:				*/
/*		LFP_UTIL_BASE(UTIL_LEVEL, UTIL_PRINTF, UTIL_MODULE_MASK1, ...)			            */
/*		LFP_UTIL_BASE(UTIL_LEVEL, UTIL_PRINTF, UTIL_MODULE_MASK2, ...)			            */
/********************************************************************************************/

#ifndef __LFP_UTIL_DEF_H__
#define __LFP_UTIL_DEF_H__

#include "__lfp_util_typesdef.h"

#define UTIL_MASK_NUM 		(sizeof(LFP_UINT64) * 8)    /* the max mask size every single module. */

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
#define  MASK_SINGLE_LIST         (0x1)
#define  MASK_SINGLE_LIST_TEST    (0x2)
#define  MASK_SINGLE_INVALID      (0x4)

/* 2. UTIL_MODULE_DOUBLE_LIST(0x2) module idx .*/
#define  MASK_DOUBLE_LIST    (0x1)

/* 3. UTIL_MODULE_SOCKET(0x4) module idx .*/
#define  MASK_SOCKET_SERVER    (0x1)
#define  MASK_SOCKET_CLIENT    (0x2)
#define MASK_SOCKET_CTRL       (0x4)

/* 4. UTIL_MODULE_ADAPTER(0x8) module idx .*/
#define  MASK_ADAPTER    (0x1)

/* 5. UTIL_MODULE_LINUX(0x10) module idx .*/
#define  MASK_MUTEX         (0x1)
#define  MASK_PTHREAD       (0x2)
#define  MASK_SEM	        (0x4)
#define  MASK_SOCKET        (0x8)
#define  MASK_FILEIO	    (0x10)
#define  MASK_STDIO	        (0x20)

#endif /* end of ___LFP_UTIL_DEF_H__ */