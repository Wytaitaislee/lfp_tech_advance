/***************************************************************************************
File name: linux_mutex.h
Description: the mutex management on linux system.
Author: wytaitaislee
Version: V1.0.0
Date: 2020-03-29
History: 1. create file. -- 2020-03-29
****************************************************************************************/

#ifndef __LINUX_MUTEX_H__
#define __LINUX_MUTEX_H__

#include "__linux_typesdef.h"

typedef pthread_mutex_t     LFP_MUTEX_T;
typedef pthread_mutexattr_t LFP_MUTEX_ATTR_T;

#define LFP_MUTEX_CRIT(...)   \
	LFP_UTIL_BASE(UTIL_LEVEL_CRIT, UTIL_MODULE_LINUX, MASK_MUTEX, __VA_ARGS__) 
#define LFP_MUTEX_ERR(...)   \
	LFP_UTIL_BASE(UTIL_LEVEL_ERR, UTIL_MODULE_LINUX, MASK_MUTEX, __VA_ARGS__) 
#define LFP_MUTEX_INFO(...)   \
	LFP_UTIL_BASE(UTIL_LEVEL_INFO, UTIL_MODULE_LINUX, MASK_MUTEX, __VA_ARGS__)

/*@fn	      LFP_INT32 linux_mutex_create(LFP_MUTEX_T *pMutex, LFP_MUTEX_ATTR_T *pAttr)
* @brief 	  create a new mutex object.
* @param[in]  LFP_MUTEX_ATTR_T *pAttr - the init attr
* @param[out] LFP_MUTEX_T *pMutex - the mutex itself
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_mutex_create(LFP_MUTEX_T *pMutex, LFP_MUTEX_ATTR_T *pAttr);

/*@fn	      LFP_INT32 linux_mutex_lock(LFP_MUTEX_T *pMutex);
* @brief      lock
* @param[in]  LFP_MUTEX_T *pMutex - the mutex itself
* @return     LFP_OK / LFP_ERR
*/
LFP_INT32 linux_mutex_lock(LFP_MUTEX_T *pMutex);

/*@fn	      LFP_INT32 linux_mutex_unlock(LFP_MUTEX_T *pMutex);
* @brief      unlock
* @param[in]  LFP_MUTEX_T *pMutex - the mutex itself
* @return     LFP_OK / LFP_ERR
*/
LFP_INT32 linux_mutex_unlock(LFP_MUTEX_T *pMutex);

/*@fn	      LFP_INT32 linux_mutex_destroy(LFP_MUTEX_T *pMutex)
* @brief      destroy a mutex object.
* @param[in]  LFP_MUTEX_T *pMutex - the mutex itself
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_mutex_destroy(LFP_MUTEX_T *pMutex);
#endif	/*end of __LINUX_MUTEX_H__ */