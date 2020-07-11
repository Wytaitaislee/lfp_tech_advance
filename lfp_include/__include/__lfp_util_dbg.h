/***************************************************************************************
File name: lfp_util_dbg.h																	
Description: util log debugging information control module.											
Author: wytaitaislee																	
Version: V1.0.0																			
Date: 2019-11-17																		
History: 1. create file. -- 2019-11-17
****************************************************************************************/

/************************the dbg util design rules*******************************************/
/* 1. there are tree different level of the UTIL module:									*/
/*		CRIT : the most important message.													*/			
/*		ERR  ：the message where error happens.												*/
/*		INFO ：the debugging message.														*/
/* 2. every module has it's own idx 														*/
/* 3. if a module is too large , you can use MODULE_MASK to split it, such as:				*/
/*		LFP_UTIL_BASE(UTIL_LEVEL, UTIL_PRINTF, UTIL_MODULE_MASK1, ...)			            */
/*		LFP_UTIL_BASE(UTIL_LEVEL, UTIL_PRINTF, UTIL_MODULE_MASK2, ...)			            */
/********************************************************************************************/

#ifndef __LFP_UTIL_DBG_H__
#define __LFP_UTIL_DBG_H__

#include "__lfp_util_typesdef.h"

#define LFP_UTIL_MAX_BUFF_SIZE	(4 * 1024)

#define LFP_UTIL_DEFAULT_LEVEL	((1 << UTIL_LEVEL_CRIT) | (1 << UTIL_LEVEL_ERR))
#define LFP_UTIL_DEFAULT_IDX	((LFP_UINT64)~0)
#define LFP_UTIL_DEFAULT_MASK	((LFP_UINT64)~0)

typedef enum
{
	UTIL_LEVEL_CRIT = 0x1,
	UTIL_LEVEL_ERR  = 0x2,
	UTIL_LEVEL_INFO = 0x4,
	UTIL_LEVEL_MAX,
}LFP_UTIL_LEVEL_E;

typedef struct lfp_util_map_t
{
	LFP_CONST LFP_INT8     *pLevelStr;
	LFP_UTIL_LEVEL_E		enumLevel;
}LFP_UTIL_MAP_T;

typedef struct lfp_util_ctrl_t
{
	/* data */
	LFP_UINT64 uiUtilLevel;
	LFP_UINT64 uiUtilModuleIdx;
	LFP_UINT64 uiUtilModuleMask;
}LFP_UTIL_CTRL_T;

/*@fn		  LFP_INT32 lfp_util_module_init(LFP_VOID)
* @brief 	  lfp util module init.
* @param[in]  LFP_NULL
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_util_module_init(LFP_VOID);

/*@fn		  LFP_INT32 lfp_util_module_set(LFP_UINT64 uiUtilLevel, 
								LFP_INT64 uiUtilModuleIdx, LFP_UINT64 uiUtilModuleMask)
* @brief 	  set util confg, ctrl the debugging log output.
* @param[in]  LFP_UINT64 uiUtilLevel - the util level
* @param[in]  LFP_UINT64 uiUtilModuleIdx - the util idx
* @param[in]  LFP_UINT64 uiUtilModuleMask - the util mask
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_util_module_set(LFP_UINT64 uiUtilLevel, LFP_INT64 uiUtilModuleIdx, LFP_UINT64 uiUtilModuleMask);

/*@fn		  LFP_INT32 lfp_util_module_get(LFP_UTIL_CTRL_T *pUtilMsg)
* @brief 	  get current util confg.
* @param[in]  LFP_NULL
* @param[out] LFP_UTIL_CTRL_T *pUtilMsg - util msg buff
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_util_module_get(LFP_UTIL_CTRL_T *pUtilMsg);

/*@fn		  LFP_CONST LFP_CODE LFP_INT8* __util_get_maps(LFP_UTIL_LEVEL_E enumLevel)
* @brief 	  get level str label by enum item.
* @param[in]  LFP_UTIL_LEVEL_E enumLevel - enum level
* @param[out] LFP_NULL
* @return	  the ptr of the str label / LFP_NULL
*/
LFP_CONST LFP_CODE LFP_INT8* __util_get_maps(LFP_UTIL_LEVEL_E enumLevel);

/*@fn		  LFP_CONST LFP_INT8* __util_get_file(const LFP_INT8 *pFullPath)
* @brief 	  get file name by the absolutely path of the file
* @param[in]  const LFP_INT8 *pFullPath - the absolutely path of the file
* @param[out] LFP_NULL
* @return	  the ptr of the file name / LFP_NULL
*/
LFP_CONST LFP_CODE LFP_INT8* __util_get_file(LFP_CONST LFP_INT8 *pFullPath);

/*@fn		 LFP_INT32 __util_open(LFP_UINT64 iLevel, LFP_UINT64 iModuleIdx, LFP_UINT64 iModuleMask)
* @brief 	  if whether the util switch is open.
* @param[in]  LFP_UINT64 uiUtilLevel - the util level
* @param[in]  LFP_UINT64 uiUtilModuleIdx - the util idx
* @param[in]  LFP_UINT64 uiUtilModuleMask - the util mask
* @param[out] NULL
* @return	  LFP_OK / LFP_ERR
*/	
LFP_INT32 __util_open(LFP_UINT64 iLevel, LFP_UINT64 iModuleIdx, LFP_UINT64 iModuleMask);

/*@fn		  LFP_INT32 __util_base(LFP_UTIL_LEVEL_E enumLevel, LFP_CONST LFP_INT8 *pFilePath, 
										LFP_CONST LFP_INT8 *pFunc, LFP_INT32 iLine, LFP_CONST LFP_INT8 *fmt, ...)
* @brief 	  log output base function
* @param[in]  LFP_UTIL_LEVEL_E enumLevel - the output mode(level), eg : CRIT ERR INFO...
* @param[in]  LFP_CONST LFP_INT8 *pFunc - the function whom invoking
* @param[in]  LFP_CONST LFP_INT8 *iLen - invoke line num
* @param[out] NULL
* @return	  LFP_OK / LFP_ERR
*/	
LFP_INT32 __util_base(LFP_UTIL_LEVEL_E enumLevel, LFP_CONST LFP_INT8 *pFilePath, LFP_CONST LFP_INT8 *pFunc, 
							LFP_INT32 iLine, LFP_CONST LFP_INT8 *fmt, ...);


#define LFP_UTIL_BASE(UTIL_LEVEL, UTIL_MODULE_IDX, UTIL_MODULE_MASK, ...) 						\
do																								\
{																								\
	if(LFP_OK == __util_open(UTIL_LEVEL, UTIL_MODULE_IDX, UTIL_MODULE_MASK))					\
	{																							\
		__util_base(UTIL_LEVEL, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__);					\
	}																							\
}while(0)
#endif /* end of __LFP_UTIL_DBG_H__ */
