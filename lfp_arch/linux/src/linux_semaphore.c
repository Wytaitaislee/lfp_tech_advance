/*
 * @FilePath: linux_semaphore.c
 * @Description: the semaphore management on linux system.
 * @Author: wytaitaislee
 * @Date: 2022-03-05 16:42:26
 * @LastEditTime: 2022-03-19 19:15:44
 * @LastEditors: wytaitaislee
 * Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#include "linux_semaphore.h"

#include "linux_typesdef.h"

/*@fn		   LFP_INT32 linux_semaphore_init(LINUX_SEM_T *pSem, LFP_INT32
 * iShared, LFP_UINT32 uiInitValue)
 * @brief 	   semaphore init on linux system.
 * @param[in]   LFP_INT32 iShared - if whether to share between processes
 * @param[in]   LFP_UINT32 iInitValue - initialization value
 * @param[out]  LINUX_SEM_T *pSem - pointer to semaphore structure entry
 * @return	   LFP_OK / LFP_ERR
 */
LFP_INT32 linux_semaphore_init(LINUX_SEM_T *pSem, LFP_INT32 iShared,
                               LFP_UINT32 uiInitValue) {
    LFP_RET_IF(pSem, LFP_ERR);
    if (0 != sem_init(pSem, iShared, uiInitValue)) {
        LFP_SEM_ERR("semaphore init failed\n");
        return LFP_ERR;
    }
    return LFP_OK;
}

/*@fn		   LFP_INT32 linux_semaphore_wait(LINUX_SEM_T *pSem, LFP_INT32
 * iWaitTime)
 * @brief 	   semaphore wait on linux system.
 * @param[out]  LINUX_SEM_T *pSem - pointer to semaphore structure entry
 * @param[in]   LFP_UINT32 iWaitTime - initialization value
 * @return	   LFP_OK / LFP_ERR
 */
LFP_INT32 linux_semaphore_wait(LINUX_SEM_T *pSem, LFP_INT32 iWaitTime) {
    // LFP_UINT32 iWaits = 0;

    LFP_RET_IF(pSem, LFP_ERR);
    (LFP_VOID) iWaitTime;
    /*
    iWaits = (LFP_SEM_WAIT_FOREVER == iWaitTime) ?
    ((LFP_INT32)LFP_SEM_WAIT_FOREVER) : 0 while(1)
    {
        if(0 == sem_wait(pSem))
        {

        }
    }
    */
    if (0 != sem_wait(pSem)) {
        LFP_SEM_ERR("semaphore wait failed\n");
        return LFP_ERR;
    }
    return LFP_OK;
}

/*@fn		   LFP_INT32 linux_semaphore_post(LINUX_SEM_T *pSem)
 * @brief 	   semaphore post on linux system.
 * @param[out]  LINUX_SEM_T *pSem - pointer to semaphore structure entry
 * @return	   LFP_OK / LFP_ERR
 */
LFP_INT32 linux_semaphore_post(LINUX_SEM_T *pSem) {
    LFP_RET_IF(pSem, LFP_ERR);
    if (0 != sem_post(pSem)) {
        LFP_SEM_ERR("semaphore post failed\n");
        return LFP_ERR;
    }
    return LFP_OK;
}

/*@fn		   LFP_INT32 linux_semaphore_destroy(LINUX_SEM_T *pSem)
 * @brief 	   semaphore post on linux system.
 * @param[out]  LINUX_SEM_T *pSem - pointer to semaphore structure entry
 * @return	   LFP_OK / LFP_ERR
 */
LFP_INT32 linux_semaphore_destroy(LINUX_SEM_T *pSem) {
    LFP_RET_IF(pSem, LFP_ERR);
    if (0 != sem_destroy(pSem)) {
        LFP_SEM_ERR("semaphore post failed\n");
        return LFP_ERR;
    }
    return LFP_OK;
}
