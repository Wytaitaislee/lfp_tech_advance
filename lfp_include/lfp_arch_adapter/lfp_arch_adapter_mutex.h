/***
 * @FilePath: lfp_arch_adapter_mutex.h
 * @Description: System adaptation layer, matching different arch.
 * @Author: wytaitaislee
 * @Date: 2021-08-27 23:29:52
 * @LastEditTime: 2022-03-05 21:18:51
 * @LastEditors: wytaitaislee
 * @Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#ifndef __LFP_ARCH_ADAPTER_MUTEX_H__
#define __LFP_ARCH_ADAPTER_MUTEX_H__

#include "include/lfp_arch_abstract.h"
#include "lfp_base.h"

/*@fn	      LFP_INT32 lfp_mutex_init(LFP_MUTEX_T *pMutex, LFP_MUTEX_ATTR_T
 * *pAttr)
 * @brief      create a new mutex.
 * @param[in]  LFP_MUTEX_ATTR_T *pAttr - the init attr
 * @param[out] LFP_MUTEX_T *pMutex - the mutex itself
 * @return     LFP_OK / LFP_ERR
 */
LFP_INT32 lfp_mutex_init(LFP_MUTEX_T *pMutex, LFP_MUTEX_ATTR_T *pAttr);

/*@fn	      LFP_INT32 lfp_mutex_lock(LFP_MUTEX_T *pMutex);
 * @brief      lock
 * @param[in]  LFP_MUTEX_T *pMutex - the mutex itself
 * @return     LFP_OK / LFP_ERR
 */
LFP_INT32 lfp_mutex_lock(LFP_MUTEX_T *pMutex);

/*@fn	      LFP_INT32 lfp_mutex_unlock(LFP_MUTEX_T *pMutex);
 * @brief      unlock
 * @param[in]  LFP_MUTEX_T *pMutex - the mutex itself
 * @return     LFP_OK / LFP_ERR
 */
LFP_INT32 lfp_mutex_unlock(LFP_MUTEX_T *pMutex);

/*@fn	      LFP_INT32 lfp_mutex_destroy(LFP_MUTEX_T *pMutex)
 * @brief      destroy a mutex.
 * @param[in]  LFP_MUTEX_T *pMutex - the mutex itself
 * @return     LFP_OK / LFP_ERR
 */
LFP_INT32 lfp_mutex_destroy(LFP_MUTEX_T *pMutex);

/*@fn		  LFP_INT32 lfp_arch_adapter_mutex_register(LFP_VOID)
 * @brief 	  the adapter layer register -- mutex cluster register
 * @param[in]  LFP_NULL
 * @param[out] LFP_NULL
 * @return	  LFP_OK
 */
LFP_INT32 lfp_arch_adapter_mutex_register(LFP_VOID);

#endif /*end of __LFP_ARCH_ADAPTER_MUTEX_H__ */