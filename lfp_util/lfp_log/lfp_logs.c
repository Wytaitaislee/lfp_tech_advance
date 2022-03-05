/*
 * @FilePath: lfp_logs.c
 * @Description: Log information control module.
 * @Author: wytaitaislee
 * @Date: 2021-08-27 23:29:52
 * @LastEditTime: 2022-03-05 22:01:11
 * @LastEditors: wytaitaislee
 * Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#include <stdarg.h>
#include <string.h>

#include "lfp_base.h"

LFP_LOG_CTRL_T *g_pUtilCtrl = NULL;

LFP_CONST LFP_DATA LFP_LOG_MAP_T g_UtilMap[] = {
    {"CRIT", LOG_LEVEL_CRIT},
    {"ERR", LOG_LEVEL_ERR},
    {"INFO", LOG_LEVEL_INFO},
    {LFP_NULL, LOG_LEVEL_MAX},
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
  LFP_RET_NULL_IF(g_pUtilCtrl);
  LFP_BUFF_BEZERO(g_pUtilCtrl, sizeof(*g_pUtilCtrl));
  g_pUtilCtrl->uiUtilLevel = LFP_LOG_DEFAULT_LEVEL;
  g_pUtilCtrl->uiUtilModuleIdx = LFP_LOG_DEFAULT_IDX;
  g_pUtilCtrl->uiUtilModuleMask = LFP_LOG_DEFAULT_MASK;
  return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_log_module_set(LFP_UINT64 uiUtilLevel,
                                LFP_INT64 uiUtilModuleIdx, LFP_UINT64
uiUtilModuleMask)
* @brief 	  set log confg, ctrl the debugging log output.
* @param[in]  LFP_UINT64 uiUtilLevel - the log level
* @param[in]  LFP_UINT64 uiUtilModuleIdx - the log idx
* @param[in]  LFP_UINT64 uiUtilModuleMask - the log mask
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_log_module_set(LFP_UINT64 uiUtilLevel, LFP_INT64 uiUtilModuleIdx,
                             LFP_UINT64 uiUtilModuleMask) {
  LFP_RET_NULL_IF(g_pUtilCtrl);

  if (!(uiUtilLevel || uiUtilModuleIdx || uiUtilModuleMask)) {
    g_pUtilCtrl->uiUtilLevel = LFP_LOG_DEFAULT_LEVEL;
    g_pUtilCtrl->uiUtilModuleIdx = LFP_LOG_DEFAULT_IDX;
    g_pUtilCtrl->uiUtilModuleMask = LFP_LOG_DEFAULT_MASK;
  } else {
    g_pUtilCtrl->uiUtilLevel = uiUtilLevel;
    g_pUtilCtrl->uiUtilModuleIdx = uiUtilModuleIdx;
    g_pUtilCtrl->uiUtilModuleMask = uiUtilModuleMask;
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
  LFP_RET_NULL_IF(g_pUtilCtrl && pUtilMsg);

  *pUtilMsg = *g_pUtilCtrl;
  return LFP_OK;
}

/*@fn		 LFP_INT32 __log_open(LFP_UINT64 iLevel, LFP_UINT64 iModuleIdx,
 * LFP_UINT64 iModuleMask)
 * @brief 	  if whether the log switch is open.
 * @param[in]  LFP_UINT64 uiUtilLevel - the log level
 * @param[in]  LFP_UINT64 uiUtilModuleIdx - the log idx
 * @param[in]  LFP_UINT64 uiUtilModuleMask - the log mask
 * @param[out] NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 __log_open(LFP_UINT64 iLevel, LFP_UINT64 iModuleIdx,
                     LFP_UINT64 iModuleMask) {
  LFP_LOG_CTRL_T struUtil;

  LFP_BUFF_BEZERO(&struUtil, sizeof(struUtil));
  if (LFP_OK != lfp_log_module_get(&struUtil)) {
    printf("%s[%d] get log module error\n", __FUNCTION__, __LINE__);
    return LFP_ERR;
  }
  LFP_RET_NULL_IF((iLevel < LOG_LEVEL_MAX) && (iLevel >= LOG_LEVEL_CRIT));
  if (((1 << iLevel) & struUtil.uiUtilLevel) &&
      (iModuleIdx & struUtil.uiUtilModuleIdx) &&
      (iModuleMask & struUtil.uiUtilModuleMask)) {
    return LFP_OK;
  }
  return LFP_ERR;
}

/*@fn		  LFP_CONST LFP_CODE LFP_INT8* __log_get_maps(LFP_LOG_LEVEL_E
 * enumLevel)
 * @brief 	  get level str label by enum item.
 * @param[in]  LFP_LOG_LEVEL_E enumLevel - enum level
 * @param[out] LFP_NULL
 * @return	  the ptr of the str label / LFP_NULL
 */
LFP_CONST LFP_CODE LFP_INT8 *__log_get_maps(LFP_LOG_LEVEL_E enumLevel) {
  LFP_UINT32 uiCnt = 0;
  LFP_RET_NULL_IF(enumLevel < LOG_LEVEL_MAX);

  for (uiCnt = 0; uiCnt < LFP_NELEMENTS(g_UtilMap); uiCnt++) {
    if (enumLevel == g_UtilMap[uiCnt].enumLevel) {
      return g_UtilMap[uiCnt].pLevelStr;
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
LFP_CONST LFP_CODE LFP_INT8 *__log_get_file(LFP_CONST LFP_INT8 *pFullPath) {
  LFP_CONST LFP_INT8 *pFile = LFP_NULL;

  LFP_RET_NULL_IF(pFullPath);
  if (LFP_NULL != (pFile = strrchr(pFullPath, '/'))) {
    pFile++; /* offset of char '/' */
  } else {
    pFile = pFullPath; /* file itself */
  }

  return pFile;
}

/*@fn		  LFP_INT32 __log_base(LFP_LOG_LEVEL_E enumLevel, LFP_CONST
LFP_INT8 *pFilePath, LFP_CONST LFP_INT8 *pFunc, LFP_INT32 iLine, LFP_CONST
LFP_INT8 *fmt, ...)
* @brief 	  log output base function
* @param[in]  LFP_LOG_LEVEL_E enumLevel - the output mode(level), eg : CRIT ERR
INFO...
* @param[in]  LFP_CONST LFP_INT8 *pFunc - the function whom invoking
* @param[in]  LFP_CONST LFP_INT8 *iLen - invoke line num
* @param[out] NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 __log_base(LFP_LOG_LEVEL_E enumLevel, LFP_CONST LFP_INT8 *pFilePath,
                     LFP_CONST LFP_INT8 *pFunc, LFP_INT32 iLine,
                     LFP_CONST LFP_INT8 *fmt, ...) {
  LFP_INT8 szPtrBuf[LFP_LOG_MAX_BUFF_SIZE] = {0};
  LFP_CONST LFP_DATA LFP_INT8 *pLevelStr = NULL;
  LFP_LOG_CTRL_T strupUtilCtrl;
  LFP_INT32 iLen = 0;
  va_list ap = {0};

  LFP_BUFF_BEZERO(&strupUtilCtrl, sizeof(strupUtilCtrl));
  LFP_ASSERT((enumLevel <= LOG_LEVEL_MAX) && pFilePath && pFunc);

  if (LFP_OK != lfp_log_module_get(&strupUtilCtrl)) {
    printf("%s get log module error\n", __FUNCTION__);
    return LFP_ERR;
  }
  pLevelStr = __log_get_maps(enumLevel);
  LFP_RET_NULL_IF(pLevelStr);

  iLen +=
      snprintf(szPtrBuf + iLen, sizeof(szPtrBuf) - iLen, "[%s][%s][%s][%s][%d]",
               __TIME__, pLevelStr, __log_get_file(pFilePath), pFunc, iLine);

  LFP_RET_NULL_IF(iLen < LFP_LOG_MAX_BUFF_SIZE);
  va_start(ap, fmt);
  iLen += vsnprintf(szPtrBuf + iLen, sizeof(szPtrBuf) - iLen, fmt, ap);
  va_end(ap);

  szPtrBuf[LFP_LOG_MAX_BUFF_SIZE - 1] = 0;
  printf("%s", szPtrBuf);
  return LFP_OK;
}
