/************************************************************************************
File name: __lfp_base.h
Description: Internal basic data structure definition, 1. only can be invoked in 
			 lfp_base directory; 2. Exposed from the lfp_base.h file to the upper layer.
Author: wytaitaislee
Version: V1.0.0(LFP_BASE_VERSION)
Date: 2019-11-17
History: 1. create file. -- 2019-11-17
************************************************************************************/

#ifndef __LFP_UTIL_TYPESDEF_H__
#define __LFP_UTIL_TYPESDEF_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <stdarg.h>

#define LFP_BASE_VERSION "V1.0.0"

/* --------------------------basic data structure typedefine[start]---------------- */
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

/* --------------------------basic data structure typedef[end]----------------- */

#define LFP_MAX(x, y) 				((x > y) ? (x) : (y))
#define LFP_MIN(x, y) 				((x > y) ? (y) : (x))
#define LFP_BUFF_BEZERO(pStr, len) 	(memset(pStr , 0, len))
#define LFP_NELEMENTS(x)			(sizeof(x) / sizeof(*x))
#define LFP_MALLOC(size)			(malloc(size))

/* assert */
#define LFP_ASSERT(c)																\
do																					\
{																					\
	if(!(c)){printf("[%s][warn][%s][%s][%d] %s ,condition err!!\n", 				\
				__TIME__, __FILE__, __func__, __LINE__, #c);assert(c);}				\
}while(0)

/* assert return NULL */
#define LFP_ASSERT_NULL_RET(c)															\
do																						\
{																						\
	if(!(c)){printf("[%s][warn][%s][%s][%d]  %s ,condition err!!\n", 					\
					__TIME__, __FILE__, __func__, __LINE__, #c);return LFP_NULL;} 		\
}while(0)

/* assert return error */	
#define LFP_ASSERT_ERR_RET(c)															\
do																						\
{																						\
	if(!(c)){printf("[%s][warn][%s][%s][%d] %s ,condition err!!\n", 					\
					__TIME__, __FILE__, __func__, __LINE__, #c);return LFP_ERR;}		\
}while(0)

/* assert return ok */
#define LFP_ASSERT_OK_RET(c)															\
do																						\
{																						\
	if(!(c)){printf("[%s][warn][%s][%s][%d] %s ,condition err!!\n", 					\
					__TIME__, __FILE__, __func__, __LINE__, #c);return LFP_OK;}			\
}while(0)
	
/* assert safe free memory */
#define LFP_SAFE_FREE(p)															\
do																					\
{																					\
	if(p){free(p);p = (LFP_VOID*)NULL;}														\
}while(0)
	
/* assert safe close file */
#define LFP_SAFE_CLOSE(p)															\
do																					\
{																					\
	if(p){fclose(p);p = (LFP_VOID*)NULL;}														\
}while(0)

/* assert safe close socket connection */
#define LFP_SAFE_CLOSE_SOCKET(p)													\
do																					\
{																					\
	if(p){close(p);p = (LFP_VOID*)NULL;}														\
}while(0)

#define LFP_MODULES_REGISTER_SIGN(util, sign)										\
do 																					\
{																					\
	util("module %s !\n", sign);													\
}while(0)
#endif /* end of __LFP_UTIL_TYPESDEF_H__ */
