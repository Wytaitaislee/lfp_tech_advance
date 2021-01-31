/***************************************************************************************
File name: linux_mutex.c
Description: Operating system adaptation layer, matching different architecture platforms.
             mutex implement.
Author: wytaitaislee
Date: 2020-03-29
History: 1. create file. -- 2020-03-29
****************************************************************************************/

#include "linux_mutex.h"
#include "linux_typesdef.h"

/*@fn	      LFP_INT32 linux_mutex_create(LINUX_MUTEX_T *pMutex, LINUX_MUTEX_ATTR_T *pAttr)
* @brief 	  create a new mutex.
* @param[in]  LINUX_MUTEX_ATTR_T *pAttr - the init attr
* @param[out] LINUX_MUTEX_T *pMutex - the mutex itself
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_mutex_create(LINUX_MUTEX_T *pMutex, LINUX_MUTEX_ATTR_T *pAttr)
{
    LFP_INT32 iRet = -1;
    iRet = pthread_mutex_init(pMutex, pAttr);
    if(0 != iRet)
    {
        LFP_MUTEX_ERR("create mutex failed, pMutex[%p], pAttr[%p], iRet[%d]\n", pMutex, pAttr, iRet);
        return LFP_ERR;
    }
    return LFP_OK;
}

/*@fn	      LFP_INT32 linux_mutex_lock(LINUX_MUTEX_T *pMutex);
* @brief      lock
* @param[in]  LINUX_MUTEX_T *pMutex - the mutex itself
* @return     LFP_OK / LFP_ERR
*/
LFP_INT32 linux_mutex_lock(LINUX_MUTEX_T *pMutex)
{
    LFP_INT32 iRet = -1;

    LFP_ASSERT_ERR_RET(pMutex);
    iRet = pthread_mutex_lock(pMutex);
    if(0 != iRet)
    {
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
LFP_INT32 linux_mutex_unlock(LINUX_MUTEX_T *pMutex)
{
    LFP_INT32 iRet = -1;

    LFP_ASSERT_ERR_RET(pMutex);
    iRet = pthread_mutex_unlock(pMutex);
    if(0 != iRet)
    {
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
LFP_INT32 linux_mutex_destroy(LINUX_MUTEX_T *pMutex)
{
    LFP_INT32 iRet = -1;

    LFP_ASSERT_ERR_RET(pMutex);
    iRet = pthread_mutex_destroy(pMutex);
    if(0 != iRet)
    {
        LFP_MUTEX_ERR("destroy mutex failed, pMutex[%p], iRet[%d]\n", pMutex, iRet);
        return LFP_ERR;
    }
    return LFP_OK;  
}

