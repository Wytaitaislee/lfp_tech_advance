/***
 * @FilePath: lfp_log.h
 * @Description: log debugging information control module.
 * @Author: wytaitaislee
 * @Date: 2021-08-27 23:29:52
 * @LastEditTime: 2022-03-05 22:00:33
 * @LastEditors: wytaitaislee
 * @Copyright 2022 wytaitaislee, All Rights Reserved.
 */

/**************************the log design rules*************************
 * 1. there are tree different level of the LOG module:
 *		CRIT : the most important message.
 *		ERR  ：the message where error happens.
 *		INFO ：the debugging message.
 * 2. every module has it's own idx
 * 3. if a module is too large , you can use MODULE_MASK to split it, such as:
 *		LFP_LOG_BASE(LOG_LEVEL, LOG_PRINTF, LOG_MODULE_MASK1, ...)
 *		LFP_LOG_BASE(LOG_LEVEL, LOG_PRINTF, LOG_MODULE_MASK2, ...)
 ************************************************************************/

#ifndef __LFP_LOG_H__
#define __LFP_LOG_H__

#include "lfp_log_typesdef.h"

#define COLOR_NONE "\e[0m"
#define COLOR_LRED "\e[1;31m"
#define COLOR_LGREEN "\e[1;32m"

#define CRIT_COLOR COLOR_LGREEN
#define ERR_COLOR COLOR_LRED
#define INFO_COLOR COLOR_NONE

typedef struct lfp_log_map_t {
    LFP_CONST LFP_INT8 *pLevelStr;
    LFP_CONST LFP_INT8 *pColor;
    LFP_LOG_LEVEL_E enumLevel;
} LFP_LOG_MAP_T;

typedef struct lfp_log_ctrl_t {
    /* data */
    LFP_UINT64 ulUtilLevel;
    LFP_UINT64 ulUtilModuleIdx;
    LFP_UINT64 ulUtilModuleMask;
} LFP_LOG_CTRL_T;

/*@fn		  LFP_INT32 lfp_log_module_init(LFP_VOID)
 * @brief 	  lfp log module init.
 * @param[in]  LFP_NULL
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 lfp_log_module_init(LFP_VOID);

/*@fn		  LFP_INT32 lfp_log_module_set(LFP_UINT64 ulUtilLevel,
                                LFP_INT64 ulUtilModuleIdx, LFP_UINT64
ulUtilModuleMask)
* @brief 	  set log confg, ctrl the debugging log output.
* @param[in]  LFP_UINT64 ulUtilLevel - the log level
* @param[in]  LFP_UINT64 ulUtilModuleIdx - the log idx
* @param[in]  LFP_UINT64 ulUtilModuleMask - the log mask
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_log_module_set(LFP_UINT64 ulUtilLevel, LFP_INT64 ulUtilModuleIdx,
                             LFP_UINT64 ulUtilModuleMask);

/*@fn		  LFP_INT32 lfp_log_module_get(LFP_LOG_CTRL_T *pUtilMsg)
 * @brief 	  get current log confg.
 * @param[in]  LFP_NULL
 * @param[out] LFP_LOG_CTRL_T *pUtilMsg - log msg buff
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 lfp_log_module_get(LFP_LOG_CTRL_T *pUtilMsg);

/*@fn		 LFP_INT32 log_open(LFP_UINT64 iLevel, LFP_UINT64 iModuleIdx,
 * LFP_UINT64 iModuleMask)
 * @brief 	  if whether the log switch is open.
 * @param[in]  LFP_UINT64 ulUtilLevel - the log level
 * @param[in]  LFP_UINT64 ulUtilModuleIdx - the log idx
 * @param[in]  LFP_UINT64 ulUtilModuleMask - the log mask
 * @param[out] NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 log_open(LFP_UINT64 ulUtilLevel, LFP_UINT64 ulUtilModuleIdx,
                   LFP_UINT64 ulUtilModuleMask);

/*@fn		  LFP_INT32 log_base(LFP_LOG_LEVEL_E enumLevel, LFP_CONST
                LFP_INT8 *pFilePath, LFP_CONST LFP_INT8 *pFunc, LFP_INT32 iLine,
                LFP_CONST LFP_INT8 *fmt, ...)
* @brief 	  log output base function
* @param[in]  LFP_LOG_LEVEL_E enumLevel - the output mode(level),
* @param[in]  LFP_CONST LFP_INT8 *pFunc - the function whom invoking
* @param[in]  LFP_CONST LFP_INT8 *iLen - invoke line num
* @param[out] NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 log_base(LFP_LOG_LEVEL_E enumLevel, LFP_CONST LFP_INT8 *pFilePath,
                   LFP_CONST LFP_INT8 *pFunc, LFP_INT32 iLine,
                   LFP_CONST LFP_INT8 *fmt, ...);

#define LFP_LOG_BASE(LOG_LEVEL, LOG_MODULE_IDX, LOG_MODULE_MASK, ...)\
do {                                                                          \
    if (LFP_OK == log_open(LOG_LEVEL, LOG_MODULE_IDX, LOG_MODULE_MASK)) {     \
        log_base(LOG_LEVEL, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    }                                                                         \
} while (0)
#endif /* end of __LFP_LOG_H__ */
