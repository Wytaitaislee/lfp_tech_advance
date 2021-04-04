/*
 * @fileName: linux_pthread.c
 * @Description: Operating system adaptation layer, matching different architecture platforms.
			 	  pthread implement.
 * @Author: wytaitaislee
 * @Date: 2020-08-16 16:05:57
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-04-04 16:00:42
*/

#include "linux_pthread.h"
#include "linux_typesdef.h"

/*@fn		  LFP_INT32 linux_pthread_create(LINUX_PTHREAD_HANDLE_T *pThreadHandle, LFP_INT32 iPrority,
                                LFP_UINT32 uiStackSize, LFP_VOID* pStartTask, LFP_UINT32 uiArgs, LFP_VOID* pParams)
* @brief 	  create a new thread.
* @param[in]  LINUX_PTHREAD_HANDLE_T *pThreadHandle - the thread identifier
* @param[in]  LFP_INT32 iPrority - the thread execute priority
* @param[in]  LFP_INT32 uiStackSize - the thread stack size
* @param[in]  LFP_VOID *pStartTask - the start function
* @param[in]  LFP_VOID* pParams - the params num of the start function
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_pthread_create(LINUX_PTHREAD_HANDLE_T *pThreadHandle, LFP_INT32 iPrority,			\
                                LFP_UINT32 uiStackSize, LFP_VOID* pStartTask, LFP_VOID* pParams)
{
	LFP_INT32 iRet = LFP_ERR;
	LINUX_PTHREAD_HANDLE_T iHandle = 0, *pHandle = LFP_NULL;
	
	if(!pThreadHandle)
	{	
		pHandle = &iHandle;
	}
	else
	{
		pHandle = pThreadHandle;
	}
	iRet = pthread_create(pHandle, LFP_NULL, pStartTask, pParams);
	return (0 == iRet) ? LFP_OK : LFP_ERR;
}

/*@fn		  LFP_INT32 linux_pthread_cancel(LINUX_PTHREAD_HANDLE_T hThreadHandle)
* @brief 	  send a cancellation request to a thread
* @param[in]  LINUX_PTHREAD_HANDLE_T hThreadHandle - the thread identifier
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_pthread_cancel(LINUX_PTHREAD_HANDLE_T hThreadHandle)
{
	LFP_INT32 iRet = LFP_ERR;

	iRet = pthread_cancel(hThreadHandle);
	return (0 == iRet) ? LFP_OK : LFP_ERR;
}


/*@fn		  LFP_INT32 linux_pthread_kill(LINUX_PTHREAD_HANDLE_T hThreadHandle, LFP_INT32 iSig)
* @brief 	  send a signal to a thread
* @param[in]  LINUX_PTHREAD_HANDLE_T hThreadHandle - the thread identifier
* @param[in]  LFP_INT32 iSig - signal type
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_pthread_kill(LINUX_PTHREAD_HANDLE_T hThreadHandle, LFP_INT32 iSig)
{
	/* no assert here, for pthread status test */
	return pthread_kill(hThreadHandle, iSig);
}