/*
 * @fileName: linux_mutex.h
 * @Description: the mutex management on linux system.
 * @Author: wytaitaislee
 * @Date: 2020-09-26 18:43:32
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-04-04 16:05:53
*/

#ifndef __LINUX_MUTEX_H__
#define __LINUX_MUTEX_H__

#include "lfp_base.h"
#include <pthread.h>

typedef pthread_mutex_t     LINUX_MUTEX_T;
typedef pthread_mutexattr_t LINUX_MUTEX_ATTR_T;

#define LFP_MUTEX_CRIT(...)   \
	LFP_UTIL_BASE(UTIL_LEVEL_CRIT, UTIL_MODULE_LINUX, MASK_MUTEX, __VA_ARGS__) 
#define LFP_MUTEX_ERR(...)   \
	LFP_UTIL_BASE(UTIL_LEVEL_ERR, UTIL_MODULE_LINUX, MASK_MUTEX, __VA_ARGS__) 
#define LFP_MUTEX_INFO(...)   \
	LFP_UTIL_BASE(UTIL_LEVEL_INFO, UTIL_MODULE_LINUX, MASK_MUTEX, __VA_ARGS__)

/*@fn	      LFP_INT32 linux_mutex_create(LINUX_MUTEX_T *pMutex, LINUX_MUTEX_ATTR_T *pAttr)
* @brief 	  create a new mutex object.
* @param[in]  LINUX_MUTEX_ATTR_T *pAttr - the init attr
* @param[out] LINUX_MUTEX_T *pMutex - the mutex itself
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_mutex_create(LINUX_MUTEX_T *pMutex, LINUX_MUTEX_ATTR_T *pAttr);

/*@fn	      LFP_INT32 linux_mutex_lock(LINUX_MUTEX_T *pMutex);
* @brief      lock
* @param[in]  LINUX_MUTEX_T *pMutex - the mutex itself
* @return     LFP_OK / LFP_ERR
*/
LFP_INT32 linux_mutex_lock(LINUX_MUTEX_T *pMutex);

/*@fn	      LFP_INT32 linux_mutex_unlock(LINUX_MUTEX_T *pMutex);
* @brief      unlock
* @param[in]  LINUX_MUTEX_T *pMutex - the mutex itself
* @return     LFP_OK / LFP_ERR
*/
LFP_INT32 linux_mutex_unlock(LINUX_MUTEX_T *pMutex);

/*@fn	      LFP_INT32 linux_mutex_destroy(LINUX_MUTEX_T *pMutex)
* @brief      destroy a mutex object.
* @param[in]  LINUX_MUTEX_T *pMutex - the mutex itself
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_mutex_destroy(LINUX_MUTEX_T *pMutex);
#endif	/*end of __LINUX_MUTEX_H__ */