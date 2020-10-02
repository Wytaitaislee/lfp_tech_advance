/***************************************************************************************
File name: __lfp_util_macros.h																	
Description: define the basic macro function structure.											
Author: wytaitaislee																	
Version: V1.0.0																			
Date: 2020-09-26																		
History: 1. create file. -- 2020.09.26
****************************************************************************************/

#ifndef __LFP_UTIL_MACROS_H__
#define __LFP_UTIL_MACROS_H__

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

#endif /* end of __LFP_UTIL_MACROS_H__ */