/***
 * @FilePath     : lfp_typesdef.h
 * @Description  : Description for this file.
 * @Author       : wytaitaislee
 * @Date         : 2021-08-27 23:29:52
 * @LastEditTime : 2022-03-05 19:29:04
 * @LastEditors  : wytaitaislee
 * @Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#ifndef __LFP_TYPESDEF_H__
#define __LFP_TYPESDEF_H__

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char LFP_UINT8;
typedef unsigned short LFP_UINT16;
typedef unsigned int LFP_UINT32;
typedef unsigned long long LFP_UINT64;
typedef char LFP_INT8;
typedef short LFP_INT16;
typedef int LFP_INT32;
typedef long long LFP_INT64;
typedef long LFP_LONG;
typedef void LFP_VOID;
typedef time_t LFP_TIME_T;

/* key words definition .*/
#define LFP_STATIC static
#define LFP_CONST const
#define LFP_RESTRICT restrict
#define LFP_INLINE inline
#define LFP_CODE
#define LFP_DATA

#define LFP_STDIN (stdin)
#define LFP_STDOUT (stdout)
#define LFP_STDERR (stderr)

#define LFP_BOOL LFP_INT32
#define LFP_OK (0)
#define LFP_ERR (-1)
#define LFP_INVALID_SOCKET (-1)
#define LFP_NULL (void *)(0)
#define LFP_TRUE (1)
#define LFP_FALSE (0)

#ifdef __cplusplus
}
#endif

#endif /* end of __LFP_TYPESDEF_H__ */
