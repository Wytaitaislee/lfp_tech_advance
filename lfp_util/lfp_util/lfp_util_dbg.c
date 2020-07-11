/***************************************************************************************
File name: lfp_util.c
Description: Log information control module.
Author: wytaitaislee
Version: V1.0.0
Date: 2019-11-17
History: 1. create file. -- 2019-11-17
****************************************************************************************/

#include "lfp_util.h"

LFP_UTIL_CTRL_T *g_pUtilCtrl = NULL;

LFP_CONST LFP_DATA LFP_UTIL_MAP_T g_UtilMap[] = 
{
	{"CRIT", 	UTIL_LEVEL_CRIT},
	{"ERR",  	UTIL_LEVEL_ERR},
	{"INFO", 	UTIL_LEVEL_INFO},
	{LFP_NULL,  UTIL_LEVEL_MAX},
};

/*@fn		  LFP_INT32 __util_settings(LFP_VOID)
* @brief 	  Low-level output control
* @param[in]  LFP_NULL
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_STATIC LFP_CODE LFP_INT32 __util_settings(LFP_VOID)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_util_module_init(LFP_VOID)
* @brief 	  lfp util module init.
* @param[in]  LFP_NULL
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_util_module_init(LFP_VOID)
{
	g_pUtilCtrl = (LFP_UTIL_CTRL_T*)LFP_MALLOC(sizeof(*g_pUtilCtrl));

	__util_settings();
	LFP_ASSERT_ERR_RET(g_pUtilCtrl);
	LFP_BUFF_BEZERO(g_pUtilCtrl, sizeof(*g_pUtilCtrl));
	g_pUtilCtrl->uiUtilLevel = LFP_UTIL_DEFAULT_LEVEL;
	g_pUtilCtrl->uiUtilModuleIdx = LFP_UTIL_DEFAULT_IDX;
	g_pUtilCtrl->uiUtilModuleMask = LFP_UTIL_DEFAULT_MASK;
	return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_util_module_set(LFP_UINT64 uiUtilLevel, 
								LFP_INT64 uiUtilModuleIdx, LFP_UINT64 uiUtilModuleMask)
* @brief 	  set util confg, ctrl the debugging log output.
* @param[in]  LFP_UINT64 uiUtilLevel - the util level
* @param[in]  LFP_UINT64 uiUtilModuleIdx - the util idx
* @param[in]  LFP_UINT64 uiUtilModuleMask - the util mask
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_util_module_set(LFP_UINT64 uiUtilLevel, LFP_INT64 uiUtilModuleIdx, LFP_UINT64 uiUtilModuleMask)
{
	LFP_ASSERT_ERR_RET(g_pUtilCtrl);

	if(!(uiUtilLevel || uiUtilModuleIdx || uiUtilModuleMask))
	{
		g_pUtilCtrl->uiUtilLevel = LFP_UTIL_DEFAULT_LEVEL;
		g_pUtilCtrl->uiUtilModuleIdx = LFP_UTIL_DEFAULT_IDX;
		g_pUtilCtrl->uiUtilModuleMask = LFP_UTIL_DEFAULT_MASK;
	}
	else
	{
		g_pUtilCtrl->uiUtilLevel = uiUtilLevel;
		g_pUtilCtrl->uiUtilModuleIdx = uiUtilModuleIdx;
		g_pUtilCtrl->uiUtilModuleMask = uiUtilModuleMask;
	}
	return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_util_module_get(LFP_UTIL_CTRL_T *pUtilMsg)
* @brief 	  get current util confg.
* @param[in]  LFP_NULL
* @param[out] LFP_UTIL_CTRL_T *pUtilMsg - util msg buff
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_util_module_get(LFP_UTIL_CTRL_T *pUtilMsg)
{
	LFP_ASSERT_ERR_RET(g_pUtilCtrl && pUtilMsg);

	*pUtilMsg = *g_pUtilCtrl; 
	return LFP_OK;
}

/*@fn		 LFP_INT32 __util_open(LFP_UINT64 iLevel, LFP_UINT64 iModuleIdx, LFP_UINT64 iModuleMask)
* @brief 	  if whether the util switch is open.
* @param[in]  LFP_UINT64 uiUtilLevel - the util level
* @param[in]  LFP_UINT64 uiUtilModuleIdx - the util idx
* @param[in]  LFP_UINT64 uiUtilModuleMask - the util mask
* @param[out] NULL
* @return	  LFP_OK / LFP_ERR
*/	
LFP_INT32 __util_open(LFP_UINT64 iLevel, LFP_UINT64 iModuleIdx, LFP_UINT64 iModuleMask)
{
	LFP_UTIL_CTRL_T struUtil;

	LFP_BUFF_BEZERO(&struUtil, sizeof(struUtil));
	if(LFP_OK != lfp_util_module_get(&struUtil))
	{
		printf("%s[%d] get util module error\n", __FUNCTION__, __LINE__);
		return LFP_ERR;
	}
	LFP_ASSERT_ERR_RET((iLevel < UTIL_LEVEL_MAX) && (iLevel >= UTIL_LEVEL_CRIT));
	if((( 1 << iLevel) & struUtil.uiUtilLevel)
		 && (iModuleIdx & struUtil.uiUtilModuleIdx)
		 && (iModuleMask & struUtil.uiUtilModuleMask))
	{
		return LFP_OK;
	}
	return LFP_ERR;
}

/*@fn		  LFP_CONST LFP_CODE LFP_INT8* __util_get_maps(LFP_UTIL_LEVEL_E enumLevel)
* @brief 	  get level str label by enum item.
* @param[in]  LFP_UTIL_LEVEL_E enumLevel - enum level
* @param[out] LFP_NULL
* @return	  the ptr of the str label / LFP_NULL
*/
LFP_CONST LFP_CODE LFP_INT8* __util_get_maps(LFP_UTIL_LEVEL_E enumLevel)
{
	LFP_UINT32 uiCnt = 0;
	LFP_ASSERT_NULL_RET(enumLevel < UTIL_LEVEL_MAX);

	for(uiCnt = 0; uiCnt < LFP_NELEMENTS(g_UtilMap); uiCnt++)
	{
		if(enumLevel == g_UtilMap[uiCnt].enumLevel)
		{
			return g_UtilMap[uiCnt].pLevelStr;
		}
	}
	return LFP_NULL;
}

/*@fn		  LFP_CONST LFP_INT8* __util_get_file(const LFP_INT8 *pFullPath)
* @brief 	  get file name by the absolutely path of the file
* @param[in]  const LFP_INT8 *pFullPath - the absolutely path of the file
* @param[out] LFP_NULL
* @return	  the ptr of the file name / LFP_NULL
*/
LFP_CONST LFP_CODE LFP_INT8* __util_get_file(LFP_CONST LFP_INT8 *pFullPath)
{
	LFP_CONST LFP_INT8* pFile = LFP_NULL;
	
	LFP_ASSERT_NULL_RET(pFullPath);
	if(LFP_NULL != (pFile = strrchr(pFullPath, '/')))
	{
		pFile++;	/* offset of char '/' */		
	}
	else
	{
		pFile = pFullPath; /* file itself */
	}

	return pFile;
}

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
							LFP_INT32 iLine, LFP_CONST LFP_INT8 *fmt, ...)
{
	LFP_INT8 szPtrBuf[LFP_UTIL_MAX_BUFF_SIZE] = {0};
	LFP_CONST LFP_DATA LFP_INT8 *pLevelStr = NULL;
	LFP_UTIL_CTRL_T strupUtilCtrl;
	LFP_INT32 iLen = 0;
	va_list ap = {0};
	
	LFP_BUFF_BEZERO(&strupUtilCtrl, sizeof(strupUtilCtrl));
	LFP_ASSERT((enumLevel <= UTIL_LEVEL_MAX) && pFilePath && pFunc);

	if(LFP_OK != lfp_util_module_get(&strupUtilCtrl))
	{
		printf("%s get util module error\n", __FUNCTION__);
		return LFP_ERR;
	}
	pLevelStr = __util_get_maps(enumLevel);
	LFP_ASSERT_ERR_RET(pLevelStr);

	iLen += snprintf(szPtrBuf + iLen, sizeof(szPtrBuf) - iLen, "[%s][%s][%s][%s][%d]", 	\
						__TIME__, pLevelStr, __util_get_file(pFilePath), pFunc, iLine);
	
	LFP_ASSERT_ERR_RET(iLen < LFP_UTIL_MAX_BUFF_SIZE);
	va_start(ap, fmt);
	iLen += vsnprintf(szPtrBuf + iLen, sizeof(szPtrBuf) - iLen, fmt, ap);
	va_end(ap);
	
	szPtrBuf[LFP_UTIL_MAX_BUFF_SIZE - 1] = 0;
	printf("%s", szPtrBuf);
	return LFP_OK;
}


