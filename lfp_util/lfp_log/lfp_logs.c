/*
 * @FilePath     : lfp_logs.c
 * @Description: Log information control module.
 * @Author: wytaitaislee
 * @Date: 2021-08-27 23:29:52
 * @LastEditTime : 2022-05-03 15:41:08
 * @LastEditors  : wytaitaislee
 * Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#include <stdarg.h>
#include <string.h>

#include "lfp_base.h"

LFP_LOG_CTRL_T *g_pUtilCtrl = NULL;

LFP_CONST LFP_DATA LFP_LOG_MAP_T g_UtilMap[] = {
    {"CRIT", CRIT_COLOR, LOG_LEVEL_CRIT},
    {"ERR", ERR_COLOR, LOG_LEVEL_ERR},
    {"INFO", INFO_COLOR, LOG_LEVEL_INFO},
    {LFP_NULL, INFO_COLOR, LOG_LEVEL_MAX},
};

/*@fn		  LFP_INT32 __log_settings(LFP_VOID)
 * @brief 	  Low-level output control
 * @param[in]  LFP_NULL
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_STATIC LFP_CODE LFP_INT32 __log_settings(LFP_VOID) {
    setvbuf(stdout, NULL, _IONBF, 0);
    return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_log_module_init(LFP_VOID)
 * @brief 	  lfp log module init.
 * @param[in]  LFP_NULL
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 lfp_log_module_init(LFP_VOID) {
    g_pUtilCtrl = (LFP_LOG_CTRL_T *)LFP_MALLOC(sizeof(*g_pUtilCtrl));

    __log_settings();
    LFP_RET_IF(g_pUtilCtrl, LFP_ERR);
    LFP_BUFF_BEZERO(g_pUtilCtrl, sizeof(*g_pUtilCtrl));
    g_pUtilCtrl->ulUtilLevel = LFP_LOG_DEFAULT_LEVEL;
    g_pUtilCtrl->ulUtilModuleIdx = LFP_LOG_DEFAULT_IDX;
    g_pUtilCtrl->ulUtilModuleMask = LFP_LOG_DEFAULT_MASK;
    return LFP_OK;
}

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
                             LFP_UINT64 ulUtilModuleMask) {
    LFP_RET_IF(g_pUtilCtrl, LFP_ERR);

    if (!(ulUtilLevel || ulUtilModuleIdx || ulUtilModuleMask)) {
        g_pUtilCtrl->ulUtilLevel = LFP_LOG_DEFAULT_LEVEL;
        g_pUtilCtrl->ulUtilModuleIdx = LFP_LOG_DEFAULT_IDX;
        g_pUtilCtrl->ulUtilModuleMask = LFP_LOG_DEFAULT_MASK;
    } else {
        g_pUtilCtrl->ulUtilLevel = ulUtilLevel;
        g_pUtilCtrl->ulUtilModuleIdx = ulUtilModuleIdx;
        g_pUtilCtrl->ulUtilModuleMask = ulUtilModuleMask;
    }
    return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_log_module_get(LFP_LOG_CTRL_T *pUtilMsg)
 * @brief 	  get current log confg.
 * @param[in]  LFP_NULL
 * @param[out] LFP_LOG_CTRL_T *pUtilMsg - log msg buff
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 lfp_log_module_get(LFP_LOG_CTRL_T *pUtilMsg) {
    LFP_RET_IF((g_pUtilCtrl && pUtilMsg), LFP_ERR);

    *pUtilMsg = *g_pUtilCtrl;
    return LFP_OK;
}

/*@fn		 LFP_INT32 log_open(LFP_UINT64 iLevel, LFP_UINT64 iModuleIdx,
 * LFP_UINT64 iModuleMask)
 * @brief 	  if whether the log switch is open.
 * @param[in]  LFP_UINT64 ulUtilLevel - the log level
 * @param[in]  LFP_UINT64 ulUtilModuleIdx - the log idx
 * @param[in]  LFP_UINT64 ulUtilModuleMask - the log mask
 * @param[out] NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 log_open(LFP_UINT64 iLevel, LFP_UINT64 iModuleIdx,
                   LFP_UINT64 iModuleMask) {
    LFP_LOG_CTRL_T struUtil;

    LFP_BUFF_BEZERO(&struUtil, sizeof(struUtil));
    if (LFP_OK != lfp_log_module_get(&struUtil)) {
        printf("%s[%d] get log module error\n", __FUNCTION__, __LINE__);
        return LFP_ERR;
    }
    LFP_RET_IF(((iLevel < LOG_LEVEL_MAX) && (iLevel >= LOG_LEVEL_CRIT)), LFP_ERR);
    if (((1 << iLevel) & struUtil.ulUtilLevel) &&
        (iModuleIdx & struUtil.ulUtilModuleIdx) &&
        (iModuleMask & struUtil.ulUtilModuleMask)) {
        return LFP_OK;
    }
    return LFP_ERR;
}

/*@fn		  LFP_CONST LFP_CODE LFP_LOG_MAP_T* __log_get_maps(LFP_LOG_LEVEL_E
 * enumLevel)
 * @brief 	  get level str label by enum item.
 * @param[in]  LFP_LOG_LEVEL_E enumLevel - enum level
 * @param[out] LFP_NULL
 * @return	  the ptr of dbg level / LFP_NULL
 */
LFP_CONST LFP_CODE LFP_INLINE LFP_LOG_MAP_T *__log_get_maps(LFP_LOG_LEVEL_E enumLevel) {
    LFP_UINT32 uiCnt = 0;
    LFP_RET_IF((enumLevel < LOG_LEVEL_MAX), LFP_NULL);

    for (uiCnt = 0; uiCnt < LFP_NELEMENTS(g_UtilMap); uiCnt++) {
        if (enumLevel == g_UtilMap[uiCnt].enumLevel) {
            return &g_UtilMap[uiCnt];
        }
    }
    return LFP_NULL;
}

/*@fn		  LFP_CONST LFP_INT8* __log_get_file(const LFP_INT8 *pFullPath)
 * @brief 	  get file name by the absolutely path of the file
 * @param[in]  const LFP_INT8 *pFullPath - the absolutely path of the file
 * @param[out] LFP_NULL
 * @return	  the ptr of the file name / LFP_NULL
 */
LFP_CONST LFP_CODE LFP_INLINE LFP_INT8 *__log_get_file(LFP_CONST LFP_INT8 *pFullPath) {
    LFP_CONST LFP_INT8 *pFile = LFP_NULL;

    LFP_RET_IF(pFullPath, LFP_NULL);
    if (LFP_NULL != (pFile = strrchr(pFullPath, '/'))) {
        pFile++; /* offset of char '/' */
    } else {
        pFile = pFullPath; /* file itself */
    }

    return pFile;
}

/*@fn		  LFP_INT32 log_base(LFP_LOG_LEVEL_E enumLevel, LFP_CONST
                LFP_INT8 *pFilePath, LFP_CONST LFP_INT8 *pFunc, LFP_INT32 iLine,
                LFP_CONST LFP_INT8 *fmt, ...)
* @brief 	  log output base function
* @param[in]  LFP_LOG_LEVEL_E enumLevel - the output mode(level)
* @param[in]  LFP_CONST LFP_INT8 *pFunc - the function whom invoking
* @param[in]  LFP_CONST LFP_INT8 *iLen - invoke line num
* @param[out] NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 log_base(LFP_LOG_LEVEL_E enumLevel, LFP_CONST LFP_INT8 *pFilePath,
                   LFP_CONST LFP_INT8 *pFunc, LFP_INT32 iLine,
                   LFP_CONST LFP_INT8 *fmt, ...) {
    LFP_INT8 szPtrBuf[LFP_LOG_MAX_BUFF_SIZE] = {0};
    LFP_CONST LFP_LOG_MAP_T *pMapItem = NULL;
    LFP_LOG_CTRL_T strupUtilCtrl;
    LFP_INT32 iLen = 0;
    va_list ap;

    LFP_BUFF_BEZERO(&strupUtilCtrl, sizeof(strupUtilCtrl));
    LFP_ASSERT((enumLevel <= LOG_LEVEL_MAX) && pFilePath && pFunc);

    if (LFP_OK != lfp_log_module_get(&strupUtilCtrl)) {
        printf("%s get log module error\n", __FUNCTION__);
        return LFP_ERR;
    }
    pMapItem = __log_get_maps(enumLevel);
    LFP_RET_IF(pMapItem, LFP_ERR);

    iLen += snprintf(szPtrBuf + iLen, sizeof(szPtrBuf) - iLen, "%s[%s][%s][%s][%s][%d]",
                     pMapItem->pColor, __TIME__, pMapItem->pLevelStr,
                     __log_get_file(pFilePath), pFunc, iLine);

    LFP_RET_IF((iLen < LFP_LOG_MAX_BUFF_SIZE), LFP_ERR);
    va_start(ap, fmt);
    iLen += vsnprintf(szPtrBuf + iLen, sizeof(szPtrBuf) - iLen, fmt, ap);
    va_end(ap);

    szPtrBuf[LFP_LOG_MAX_BUFF_SIZE - 1] = 0;
    printf("%s%s", szPtrBuf, COLOR_NONE);
    return LFP_OK;
}
