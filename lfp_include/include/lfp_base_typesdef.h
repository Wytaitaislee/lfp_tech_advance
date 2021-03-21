/*************************************************************************************************
 * @fileName: lfp_base_typesdef.h
 * @Description: Internal basic data structure definition(types define).
 * @Author: wytaitaislee
 * @Date: 2020-08-16 16:05:58
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-03-21 19:50:59
**************************************************************************************************/

#ifndef __LFP_BASE_TYPESDEF_H__
#define __LFP_BASE_TYPESDEF_H__

#include <stdio.h>

#define LFP_BASE_MAJOR	"V1"
#define LFP_BASE_MINOR	"0"
#define LFP_BASE_SUB	"0"
#define __LFP_BASE_VERSION(major, minor, sub) (major##.##minor##.##sub)
#define LFP_BASE_VERSION __LFP_BASE_VERSION(LFP_BASE_MAJOR, LFP_BASE_MINOR, LFP_BASE_SUB)

typedef unsigned char			LFP_UINT8;
typedef unsigned short 			LFP_UINT16;
typedef unsigned int 			LFP_UINT32;
typedef unsigned long long 		LFP_UINT64;
typedef char 					LFP_INT8;
typedef short 					LFP_INT16;
typedef int 					LFP_INT32;
typedef long long 				LFP_INT64;
typedef long 					LFP_LONG;
typedef void 					LFP_VOID;

/* key words definition .*/
#define	LFP_STATIC static
#define LFP_CONST  const
#define LFP_RESTRICT  restrict
#define LFP_CODE
#define LFP_DATA

#define LFP_STDIN	(stdin)
#define LFP_STDOUT	(stdout)
#define LFP_STDERR	(stderr)

#define LFP_BOOL LFP_INT32
#define LFP_OK	(0)
#define LFP_ERR	(-1)
#define LFP_INVALID_SOCKET (-1)
#define LFP_NULL (void*)(NULL)
#define LFP_TRUE (1)
#define LFP_FALSE (0)

#endif /* end of __LFP_BASE_TYPESDEF_H__ */
