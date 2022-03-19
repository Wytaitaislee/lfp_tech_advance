/***
 * @FilePath: linux_semaphore.h
 * @Description: the semaphore management on linux system.
 * @Author: wytaitaislee
 * @Date: 2021-08-27 23:29:52
 * @LastEditTime: 2022-03-05 21:21:30
 * @LastEditors: wytaitaislee
 * @Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#ifndef __LINUX_SEMAPHORE_H__
#define __LINUX_SEMAPHORE_H__

#include <semaphore.h>

#include "lfp_base.h"

typedef sem_t LINUX_SEM_T;
#define LFP_SEM_NONSHARED (0)
#define LFP_SEM_SHARE (1)
#define LFP_SEM_INIT_FULL (1)  /* Only for binary semaphores */
#define LFP_SEM_INIT_EMPTY (0) /* Only for binary semaphores */
#define LFP_SEM_WAIT_FOREVER (-1)

#define LFP_SEM_CRIT(...) \
    LFP_LOG_BASE(LOG_LEVEL_CRIT, LOG_MODULE_LINUX, MASK_SEM, __VA_ARGS__)
#define LFP_SEM_ERR(...) \
    LFP_LOG_BASE(LOG_LEVEL_ERR, LOG_MODULE_LINUX, MASK_SEM, __VA_ARGS__)
#define LFP_SEM_INFO(...) \
    LFP_LOG_BASE(LOG_LEVEL_INFO, LOG_MODULE_LINUX, MASK_SEM, __VA_ARGS__)

/*@fn		   LFP_INT32 linux_semaphore_init(LINUX_SEM_T *pSem, LFP_INT32
 * iShared, LFP_UINT32 uiInitValue)
 * @brief 	   semaphore init on linux system.
 * @param[in]   LFP_INT32 iShared - if whether to share between processes
 * @param[in]   LFP_INT32 iInitValue - initialization value
 * @param[out]  LINUX_SEM_T *pSem - pointer to semaphore structure entry
 * @return	   LFP_OK / LFP_ERR
 */
LFP_INT32 linux_semaphore_init(LINUX_SEM_T *pSem, LFP_INT32 iShared,
                               LFP_UINT32 uiInitValue);

/*@fn		   LFP_INT32 linux_semaphore_wait(LINUX_SEM_T *pSem, LFP_INT32
 * iWaitTime)
 * @brief 	   semaphore wait on linux system.
 * @param[out]  LINUX_SEM_T *pSem - pointer to semaphore structure entry
 * @param[in]   LFP_UINT32 iWaitTime - initialization value
 * @return	   LFP_OK / LFP_ERR
 */
LFP_INT32 linux_semaphore_wait(LINUX_SEM_T *pSem, LFP_INT32 iWaitTime);

/*@fn		   LFP_INT32 linux_semaphore_post(LINUX_SEM_T *pSem)
 * @brief 	   semaphore post on linux system.
 * @param[out]  LINUX_SEM_T *pSem - pointer to semaphore structure entry
 * @return	   LFP_OK / LFP_ERR
 */
LFP_INT32 linux_semaphore_post(LINUX_SEM_T *pSem);

/*@fn		   LFP_INT32 linux_semaphore_destroy(LINUX_SEM_T *pSem)
 * @brief 	   semaphore post on linux system.
 * @param[out]  LINUX_SEM_T *pSem - pointer to semaphore structure entry
 * @return	   LFP_OK / LFP_ERR
 */
LFP_INT32 linux_semaphore_destroy(LINUX_SEM_T *pSem);
#endif /*end of __LINUX_SEMAPHORE_H__ */