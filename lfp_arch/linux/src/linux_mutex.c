/*
 * @FilePath: linux_mutex.c
 * @Description: Operating system adaptation layer, matching different
 architecture platforms. mutex implement.
 * @Author: wytaitaislee
 * @Date: 2022-03-05 16:42:26
 * @LastEditTime: 2022-03-06 17:01:33
 * @LastEditors: wytaitaislee
 * Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#include "linux_mutex.h"

#include "linux_typesdef.h"

/*@fn	      LFP_INT32 linux_mutex_init(LINUX_MUTEX_T *pMutex,
 * LINUX_MUTEX_ATTR_T *pAttr)
 * @brief 	  create a new mutex.
 * @param[in]  LINUX_MUTEX_ATTR_T *pAttr - the init attr
 * @param[out] LINUX_MUTEX_T *pMutex - the mutex itself
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 linux_mutex_init(LINUX_MUTEX_T *pMutex, LINUX_MUTEX_ATTR_T *pAttr) {
  LFP_INT32 iRet = -1;
  iRet = pthread_mutex_init(pMutex, pAttr);
  if (0 != iRet) {
    LFP_MUTEX_ERR("create mutex failed, pMutex[%p], pAttr[%p], iRet[%d]\n",
                  pMutex, pAttr, iRet);
    return LFP_ERR;
  }
  return LFP_OK;
}

/*@fn	      LFP_INT32 linux_mutex_lock(LINUX_MUTEX_T *pMutex);
 * @brief      lock
 * @param[in]  LINUX_MUTEX_T *pMutex - the mutex itself
 * @return     LFP_OK / LFP_ERR
 */
LFP_INT32 linux_mutex_lock(LINUX_MUTEX_T *pMutex) {
  LFP_INT32 iRet = -1;

  LFP_RET_IF(pMutex, LFP_ERR);
  iRet = pthread_mutex_lock(pMutex);
  if (0 != iRet) {
    LFP_MUTEX_ERR("mutex unlock failed, pMutex[%p], iRet[%d]\n", pMutex, iRet);
    return LFP_ERR;
  }
  return LFP_OK;
}

/*@fn	      LFP_INT32 linux_mutex_unlock(LINUX_MUTEX_T *pMutex);
 * @brief      unlock
 * @param[in]  LINUX_MUTEX_T *pMutex - the mutex itself
 * @return     LFP_OK / LFP_ERR
 */
LFP_INT32 linux_mutex_unlock(LINUX_MUTEX_T *pMutex) {
  LFP_INT32 iRet = -1;

  LFP_RET_IF(pMutex, LFP_ERR);
  iRet = pthread_mutex_unlock(pMutex);
  if (0 != iRet) {
    LFP_MUTEX_ERR("mutex unlock failed, pMutex[%p], iRet[%d]\n", pMutex, iRet);
    return LFP_ERR;
  }
  return LFP_OK;
}

/*@fn	      LFP_INT32 linux_mutex_destroy(LINUX_MUTEX_T *pMutex)
 * @brief      destroy a mutex.
 * @param[in]  LINUX_MUTEX_T *pMutex - the mutex itself
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 linux_mutex_destroy(LINUX_MUTEX_T *pMutex) {
  LFP_INT32 iRet = -1;

  LFP_RET_IF(pMutex, LFP_ERR);
  iRet = pthread_mutex_destroy(pMutex);
  if (0 != iRet) {
    LFP_MUTEX_ERR("destroy mutex failed, pMutex[%p], iRet[%d]\n", pMutex, iRet);
    return LFP_ERR;
  }
  return LFP_OK;
}
