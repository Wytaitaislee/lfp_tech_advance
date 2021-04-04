/*
 * @fileName: lfp_socket_init.c
 * @Description: Socket communication control main entrance.
 * @Author: wytaitaislee
 * @Date: 2020-08-16 16:05:59
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-04-04 15:59:17
*/

#ifdef LFP_LIBS_SOCKET

#include "lfp_libs_socket.h"
#include <errno.h>

LFP_STATIC LFP_DATA LFP_SOCKET_SERVER_MANAGE_T *pSocketServerManage = LFP_NULL;

/*@fn		  LFP_INT32 lfp_socket_server_manage_init(LFP_VOID)
* @brief 	  socket manage init, malloc manage resources.
* @param[in]  LFP_VOID
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_socket_server_manage_init(LFP_VOID)
{
	LFP_INT32 iRet = LFP_ERR;

	pSocketServerManage = LFP_MALLOC(sizeof(*pSocketServerManage));
	LFP_ASSERT_ERR_RET(pSocketServerManage);
	LFP_BUFF_BEZERO(pSocketServerManage, sizeof(*pSocketServerManage));
	iRet = lfp_mutex_create(&pSocketServerManage->mutex, LFP_NULL);
	if(LFP_OK != iRet)
	{
		LFP_SOCKET_CTRL_ERR("create metex err, iRet = %d\n", iRet);
		return LFP_ERR;
	}
	return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_socket_server_manage_fini(LFP_VOID)
* @brief 	  socket server manage fini, recycle the malloc resources.
* @param[in]  LFP_VOID
* @param[out] LFP_NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_socket_server_manage_fini(LFP_VOID)
{
	if(pSocketServerManage)
	{
		lfp_mutex_destroy(&pSocketServerManage->mutex);
		LFP_SAFE_FREE(pSocketServerManage);
	}
	pSocketServerManage = LFP_NULL;
	return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_socket_server_manage_node_recycle(LFP_VOID)
* @brief 	  When a socket connection is disconnected and 
			  no new connection is established for a period of time
			  the resource occupation is released.
* @param[in]  LFP_VOID
* @param[out] LFP_NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_socket_server_manage_node_recycle(LFP_VOID)
{
	LFP_INT32 uiCnt = 0;
	time_t struTimeNow;
	LFP_INT32 iExitAliveTime = 0;

	if(!pSocketServerManage)
	{
		LFP_SOCKET_CTRL_ERR("node recycle failed, pSocketServerManage is NULL\n");
		return LFP_ERR;
	}
	lfp_mutex_lock(&pSocketServerManage->mutex);
	for(uiCnt = 0; uiCnt < LFP_NELEMENTS(pSocketServerManage->pSocketDesc); uiCnt++)
	{
		if(LFP_INVALID_SOCKET != LFP_SOCKET_THIS_SERVER_DESC(pSocketServerManage, uiCnt)->iSockFd)
		{
			continue;
		}
		iExitAliveTime = struTimeNow - LFP_SOCKET_THIS_SERVER_DESC(pSocketServerManage, uiCnt)->iExitTime;
		if(iExitAliveTime > LFP_SOCKET_EXIT_ALIVE_PERIOD)
		{
			lfp_socket_desc_entry_fini(&LFP_SOCKET_THIS_SERVER_DESC(pSocketServerManage, uiCnt));
		}
	}	
	lfp_mutex_unlock(&pSocketServerManage->mutex);
	return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_socket_package_entry_init(LFP_SOCKET_PACKAGE_T *pSocketPackage)
* @brief 	  socket package entry init, if memory already malloced, clear the memory buffer.
* @param[in]  LFP_NULL
* @param[out] LFP_SOCKET_PACKAGE_T *pSocketPackage - send or recv package entry.
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_socket_package_entry_init(LFP_SOCKET_PACKAGE_T *pSocketPackage)
{
	LFP_ASSERT_ERR_RET(pSocketPackage);
	
	LFP_BUFF_BEZERO(&pSocketPackage->struHead, sizeof(pSocketPackage->struHead));
	/* If whether the memory has been allocated */
	if(!pSocketPackage->iPackageData)
	{
		pSocketPackage->iPackageData = (LFP_INT8*)LFP_MALLOC(LFP_SOCKET_MAX_PACKAGE_LEN);
	}
	LFP_ASSERT_ERR_RET(pSocketPackage->iPackageData);
	pSocketPackage->struHead.iMaxDataLen = LFP_SOCKET_MAX_PACKAGE_LEN;
	LFP_BUFF_BEZERO(pSocketPackage->iPackageData, LFP_SOCKET_MAX_PACKAGE_LEN);
	return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_socket_package_entry_fini(LFP_SOCKET_PACKAGE_T *pSocketPackage)
* @brief 	  socket package entry fini, if memory already malloced, free it.
* @param[in]  LFP_NULL
* @param[out] LFP_SOCKET_PACKAGE_T *pSocketPackage - send or recv package entry.
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_socket_package_entry_fini(LFP_SOCKET_PACKAGE_T *pSocketPackage)
{
	LFP_ASSERT_ERR_RET(pSocketPackage);
	
	LFP_SAFE_FREE(pSocketPackage->iPackageData);
	return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_socket_ctrl_entry_init(LFP_SOCKET_CTRL_T *pSocketCtrl)
* @brief 	  socket communication entry init, including receiving/sending data description
* @param[in]  LFP_NULL
* @param[out] LFP_SOCKET_CTRL_T *pSocketCtrl - communication entry 
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_socket_ctrl_entry_init(LFP_SOCKET_CTRL_T *pSocketCtrl)
{
	LFP_INT32 iRet = LFP_ERR;

	LFP_ASSERT_ERR_RET(pSocketCtrl);

	iRet = lfp_socket_package_entry_init(&pSocketCtrl->struRecvCtrl);
	if(LFP_OK != iRet)
	{
		LFP_SAFE_FREE(pSocketCtrl->struRecvCtrl.iPackageData);
		LFP_SAFE_FREE(pSocketCtrl->struSendCtrl.iPackageData);
		return LFP_ERR;
	}
	iRet = lfp_socket_package_entry_init(&pSocketCtrl->struSendCtrl);
	if(LFP_OK != iRet)
	{
		LFP_SAFE_FREE(pSocketCtrl->struRecvCtrl.iPackageData);
		LFP_SAFE_FREE(pSocketCtrl->struSendCtrl.iPackageData);
		return LFP_ERR;
	}
	return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_socket_ctrl_entry_fini(LFP_SOCKET_CTRL_T *pSocketCtrl)
* @brief 	  socket communication entry fini, include send and receive data description
* @param[in]  LFP_NULL
* @param[out] LFP_SOCKET_CTRL_T *pSocketCtrl - communication entry 
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_socket_ctrl_entry_fini(LFP_SOCKET_CTRL_T *pSocketCtrl)
{
	LFP_ASSERT_ERR_RET(pSocketCtrl);

	if(LFP_OK != lfp_socket_package_entry_fini(&pSocketCtrl->struRecvCtrl))
	{
		LFP_SOCKET_CTRL_ERR("server malloc recvCtrl failed\n");
		return LFP_ERR;
	}
	if(LFP_OK != lfp_socket_package_entry_fini(&pSocketCtrl->struSendCtrl))
	{
		LFP_SOCKET_CTRL_ERR("server malloc send failed\n");
		return LFP_ERR;		
	}
	return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_socket_desc_entry_init(LFP_SOCKET_DESC_T **ppDesc, LFP_INT32 iSocket)
* @brief 	  socket desc entry init, to manage a full duplex socket communication description
* @param[in]  LFP_SOCKET_DESC_T **ppDesc - description entry
* @param[out] LFP_INT32 iSocket - socket id 
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_socket_desc_entry_init(LFP_SOCKET_DESC_T **ppDesc, LFP_INT32 iSocket)
{
	LFP_SOCKET_DESC_T *pDescEntry = LFP_NULL;
	LFP_INT32 iRet = LFP_ERR;

	LFP_ASSERT_ERR_RET(ppDesc);
	/* If whether the memory has been allocated */
	if(!(*ppDesc))
	{
		*ppDesc = (LFP_SOCKET_DESC_T*)LFP_MALLOC(sizeof(LFP_SOCKET_DESC_T));
	}
	pDescEntry = *ppDesc;
	LFP_ASSERT_ERR_RET(pDescEntry);
	pDescEntry->iSockFd = iSocket;
	iRet = lfp_socket_ctrl_entry_init(&pDescEntry->struSocketCtrl);
	if(LFP_OK != iRet)
	{
		LFP_SOCKET_CTRL_ERR("server malloc memory entry, iSocket = %d\n", pDescEntry->iSockFd);
		LFP_SAFE_FREE(pDescEntry);
		*ppDesc = LFP_NULL;
		return LFP_ERR;
	}
	return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_socket_desc_entry_fini(LFP_SOCKET_DESC_T **ppDesc)
* @brief 	  socket desc entry fini, to manage a full duplex socket communication description
* @param[in]  LFP_SOCKET_DESC_T **ppDesc - description entry
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_socket_desc_entry_fini(LFP_SOCKET_DESC_T **ppDesc)
{
	
	LFP_SOCKET_DESC_T *pDescEntry = LFP_NULL;
	LFP_INT32 iRet = LFP_ERR;

	LFP_ASSERT_ERR_RET(ppDesc);
	pDescEntry = *ppDesc;
	LFP_ASSERT_ERR_RET(pDescEntry);
	iRet = lfp_socket_ctrl_entry_fini(&pDescEntry->struSocketCtrl);
	LFP_SAFE_CLOSE_SOCKET(pDescEntry->iSockFd);
	*ppDesc = LFP_NULL;
	return iRet;
}

/*@fn		  LFP_INT32 lfp_socket_create_subtask(LFP_INT32 iSocket)
* @brief 	  the server socket create a new task to proc the client communication.
* @param[in]  LFP_INT32 iSocket - create socket id
* @param[out] LFP_NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_socket_create_subtask(LFP_INT32 iSocket)
{
	LFP_UINT32 uiCnt = 0;
	LFP_INT32 iRet = LFP_ERR;

	LFP_ASSERT_ERR_RET(iSocket > 0);
	LFP_ASSERT_ERR_RET(pSocketServerManage);

	lfp_mutex_lock(&pSocketServerManage->mutex);
	for(uiCnt = 0; uiCnt < LFP_NELEMENTS(pSocketServerManage->pSocketDesc); uiCnt++)
	{
		if(!LFP_SOCKET_THIS_SERVER_DESC(pSocketServerManage, uiCnt))
		{
			iRet = lfp_socket_desc_entry_init(&LFP_SOCKET_THIS_SERVER_DESC(pSocketServerManage, uiCnt), iSocket);
			break;
		}
	}
	if(uiCnt >= LFP_NELEMENTS(pSocketServerManage->pSocketDesc) || LFP_OK != iRet)
	{
		LFP_SOCKET_CTRL_ERR("server malloc memory entry failed, iSocket = %d\n", iSocket);
		lfp_mutex_unlock(&pSocketServerManage->mutex);
		return LFP_ERR;
	}
	LFP_SOCKET_THIS_SERVER_DESC(pSocketServerManage, uiCnt)->iSockFd = iSocket;
	if(LFP_OK != lfp_pthread_create(LFP_NULL, LFP_NULL, LFP_NULL, (LFP_VOID*)lfp_socket_proc, LFP_SOCKET_THIS_SERVER_DESC(pSocketServerManage, uiCnt)))
	{
		LFP_SOCKET_CTRL_ERR("create a new socket task err, iSocket = %d\n", iSocket);
		LFP_SAFE_CLOSE_SOCKET(LFP_SOCKET_THIS_SERVER_DESC(pSocketServerManage, uiCnt)->iSockFd);
		LFP_SOCKET_THIS_SERVER_DESC(pSocketServerManage, uiCnt)->iSockFd = LFP_INVALID_SOCKET;
		lfp_mutex_unlock(&pSocketServerManage->mutex);
		return LFP_ERR;
	}
	lfp_mutex_unlock(&pSocketServerManage->mutex);
	return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_socket_exit_subtask(LFP_INT32 iSocket)
* @brief 	  the server socket exit ,end of server session, recycle resources.
* @param[in]  LFP_INT32 iSocket - recycle socket id
* @param[out] LFP_NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_socket_exit_subtask(LFP_INT32 iSocket)
{
	LFP_INT32 uiCnt = 0;

	LFP_ASSERT_ERR_RET(iSocket > 0);
	LFP_ASSERT_ERR_RET(pSocketServerManage);
	lfp_mutex_lock(&pSocketServerManage->mutex);
	for(uiCnt = 0; uiCnt < LFP_NELEMENTS(pSocketServerManage->pSocketDesc); uiCnt++)
	{
		if(LFP_NULL == LFP_SOCKET_THIS_SERVER_DESC(pSocketServerManage, uiCnt))
		{
			continue;
		}
		if(iSocket ==  LFP_SOCKET_THIS_SERVER_DESC(pSocketServerManage, uiCnt)->iSockFd)
		{
			/* don't free if memory has been allocated ,just set the socket invalid
			for the next socket request */
			LFP_SAFE_CLOSE_SOCKET(LFP_SOCKET_THIS_SERVER_DESC(pSocketServerManage, uiCnt)->iSockFd);
			LFP_SOCKET_THIS_SERVER_DESC(pSocketServerManage, uiCnt)->iSockFd = LFP_INVALID_SOCKET;
		}
	}
	lfp_mutex_unlock(&pSocketServerManage->mutex);
	return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_socket_server_exit(LFP_VOID)
* @brief 	  the server exit ,end of server pthread pool, recycle the whole server resources.
* @param[out] LFP_NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_socket_server_exit(LFP_VOID)
{
	LFP_INT32 uiCnt = 0;

	LFP_ASSERT_ERR_RET(pSocketServerManage);
	lfp_mutex_lock(&pSocketServerManage->mutex);
	for(uiCnt = 0; uiCnt < LFP_NELEMENTS(pSocketServerManage->pSocketDesc); uiCnt++)
	{
		if(0 <= LFP_SOCKET_THIS_SERVER_DESC(pSocketServerManage, uiCnt)->iSockFd)
		{
			lfp_socket_desc_entry_fini(&LFP_SOCKET_THIS_SERVER_DESC(pSocketServerManage, uiCnt));
		}
	}
	lfp_mutex_unlock(&pSocketServerManage->mutex);
	return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_socket_server_init(LFP_VOID)
* @brief 	  socket server communication main entrance
* @param[in]  LFP_VOID
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_socket_server_init(LFP_VOID)
{
	LFP_INT32 iRet = LFP_ERR;

	if(LFP_OK != (iRet = lfp_socket_server_task(LFP_NULL)))
	{
		LFP_SOCKET_CTRL_ERR("socket server start err, iRet = %d\n", iRet);
		return LFP_ERR;
	}
    return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_socket_client_init(LFP_VOID)
* @brief 	  socket client communication main entrance
* @param[in]  LFP_VOID
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_socket_client_init(LFP_VOID)
{
	LFP_INT32 iRet = LFP_ERR;

	if(LFP_OK != (iRet = lfp_socket_client_task(LFP_NULL)))
	{
		LFP_SOCKET_CTRL_ERR("socket client start err, iRet = %d\n", iRet);
		return LFP_ERR;
	}
    return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_socket_recv_data_ctrl(LFP_SOCKET_DESC_T *pDesc)
* @brief 	  recv data ctrl
* @param[in]  LFP_SOCKET_DESC_T *pDesc - The describe of a communication channel.
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_socket_recv_data_ctrl(LFP_SOCKET_DESC_T *pDesc)
{
	LFP_INT32 iRet = LFP_OK;
	
	LFP_ASSERT_ERR_RET(pDesc);
	while(1)
	{
		if(LFP_OK != lfp_socket_package_entry_init(&pDesc->struSocketCtrl.struRecvCtrl))
		{
			LFP_SOCKET_CTRL_ERR("init package entry err\n");
			iRet = LFP_ERR;
			goto exit_recv_data_ctrl;
		}

		if(LFP_OK != lfp_socket_recv_data(pDesc))
		{
			LFP_SOCKET_CTRL_ERR("socket client recv data err, iRet = %d\n");
			iRet = LFP_ERR;
			goto exit_recv_data_ctrl;
		}
	}
exit_recv_data_ctrl:
	return iRet;	
}

/*@fn		  LFP_INT32 lfp_socket_recv_data(LFP_SOCKET_DESC_T *pDesc)
* @brief 	  recv data from the socket, custom protocol(data package : head + data body)
* @param[in]  LFP_SOCKET_DESC_T *pDesc - The describe of a communication channel.
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_socket_recv_data(LFP_SOCKET_DESC_T *pDesc)
{
	LFP_INT32 iRecvLen = 0, iRetLen = 0;
	LFP_INT32 iNeedRecvLen = 0;
	LFP_INT8* pRecvBuf = LFP_NULL;

	LFP_ASSERT_ERR_RET(pDesc);
	LFP_ASSERT_ERR_RET(LFP_SOCKET_THIS_RECV_BODY(pDesc));
	iNeedRecvLen = sizeof(LFP_SOCKET_THIS_RECV_HEAD(pDesc));
	LFP_BUFF_BEZERO(LFP_SOCKET_THIS_RECV_BODY(pDesc), LFP_SOCKET_THIS_RECV_HEAD(pDesc).iMaxDataLen);
	LFP_SOCKET_THIS_RECV_HEAD(pDesc).iDataLen = 0;
	pRecvBuf = LFP_SOCKET_THIS_RECV_BODY(pDesc);
	while(iRecvLen < iNeedRecvLen)
	{
		iRetLen = lfp_socket_read(pDesc->iSockFd, pRecvBuf + iRecvLen, iNeedRecvLen - iRecvLen);
		if(iRetLen <= 0)
		{
			if(EAGAIN == errno || EINTR == errno)
			{/* end reading this time .*/
				usleep(20);
				LFP_SOCKET_CTRL_ERR("recv data busy[%d][%s]\n", errno ,strerror(errno));
				continue;
			}
			else
			{
				LFP_SOCKET_CTRL_ERR("socket maybe closed, err[%d][%s]\n", errno ,strerror(errno));
				return LFP_ERR;
			}
		}
		iRecvLen += iRetLen;
		/* the head data received ok. */
		if(iRecvLen == sizeof(LFP_SOCKET_THIS_RECV_HEAD(pDesc)) && iNeedRecvLen == sizeof(LFP_SOCKET_THIS_RECV_HEAD(pDesc)))
		{
			LFP_SOCKET_CTRL_ERR("iDataLen = %d, isocketFd = %d--------\n", LFP_SOCKET_THIS_RECV_HEAD(pDesc).iDataLen, pDesc->iSockFd);
			memcpy(&LFP_SOCKET_THIS_RECV_HEAD(pDesc), LFP_SOCKET_THIS_RECV_BODY(pDesc), sizeof(LFP_SOCKET_THIS_RECV_HEAD(pDesc)));
			iNeedRecvLen = LFP_MIN(LFP_SOCKET_THIS_RECV_HEAD(pDesc).iDataLen, LFP_SOCKET_THIS_RECV_HEAD(pDesc).iMaxDataLen);
		}
	}
	LFP_SOCKET_CTRL_CRIT("%s, length : %d\n", LFP_SOCKET_THIS_RECV_BODY(pDesc)+sizeof(LFP_SOCKET_THIS_RECV_HEAD(pDesc)), strlen(LFP_SOCKET_THIS_RECV_BODY(pDesc) + sizeof(LFP_SOCKET_THIS_RECV_HEAD(pDesc))));
	return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_socket_send_data_ctrl()
* @brief 	  rsend data to the socket, custom protocol(data package : head + data)
* @param[in]  LFP_SOCKET_DESC_T *pDesc - The describe of a communication channel.
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_socket_send_data_ctrl(LFP_SOCKET_DESC_T *pDesc)
{
	LFP_INT32 iRet = LFP_OK;
	LFP_INT32 iOffset = 0;
	LFP_INT8* pBodyData = LFP_NULL;
	LFP_INT8 aInputBuf[LFP_SOCKET_MAX_INPUT_CHAR_ONCE] = {0};

	LFP_ASSERT_ERR_RET(pDesc);
	iOffset = LFP_SOCKET_THIS_BODY_OFFSET(pDesc);
	while(1)
	{
		if(LFP_OK != lfp_socket_package_entry_init(&pDesc->struSocketCtrl.struSendCtrl))
		{
			iRet = LFP_ERR;
			goto send_data_ctrl_exit;
		}
		LFP_BUFF_BEZERO(aInputBuf, sizeof(aInputBuf));
		while(!fgets(aInputBuf, sizeof(aInputBuf) - iOffset, LFP_STDIN))
		{
			if(0 == strncmp(aInputBuf, LFP_SOCKET_EXIT_REQUEST_KEYS, LFP_MIN(strlen(aInputBuf), strlen(LFP_SOCKET_EXIT_REQUEST_KEYS))))
			{
				LFP_SOCKET_CTRL_CRIT("iSocket[%d] communication end\n", pDesc->iSockFd);
				iRet = LFP_OK;
				goto send_data_ctrl_exit;
			}
			break;
		}
		aInputBuf[LFP_SOCKET_MAX_INPUT_CHAR_ONCE] = 0;	/* the end of the sentence */
		pBodyData = (LFP_INT8*)LFP_SOCKET_THIS_SEND_BODY(pDesc) + iOffset;
		
		memcpy(pBodyData, aInputBuf, strlen(aInputBuf));
		LFP_SOCKET_THIS_SEND_HEAD(pDesc).iDataLen = iOffset + strlen(pBodyData);
		memcpy(LFP_SOCKET_THIS_SEND_BODY(pDesc), &LFP_SOCKET_THIS_SEND_HEAD(pDesc), sizeof(LFP_SOCKET_THIS_SEND_HEAD(pDesc)));
		if(LFP_OK != lfp_socket_send_data(pDesc->iSockFd, LFP_SOCKET_THIS_SEND_BODY(pDesc), 
										LFP_SOCKET_THIS_SEND_HEAD(pDesc).iDataLen))
		{
			iRet = LFP_ERR;
			goto send_data_ctrl_exit;
		}
	}
send_data_ctrl_exit:
	return iRet;
}

/*@fn		  LFP_INT32 lfp_socket_send_data(LFP_INT32 iSocket, LFP_INT8* pData, LFP_INT32 iDataLen)
* @brief 	  rsend data to the socket, custom protocol(data package : head + data)
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LFP_INT8* pData - the data to send
* @param[in]  LFP_INT32 iDataLen  - The length of data
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_socket_send_data(LFP_INT32 iSocket, LFP_CONST LFP_INT8* pData, LFP_INT32 iDataLen)
{
	LFP_ASSERT_ERR_RET((iSocket >= 0) && (pData) && (iDataLen > 0));

	LFP_SOCKET_CTRL_ERR("send data to client, iDataLen = %d\n", iDataLen);
	if(0 > lfp_socket_write(iSocket, pData, iDataLen))
	{
		LFP_SOCKET_CTRL_ERR("send data to err, err = %d\n", errno);
		return LFP_ERR;
	}
	return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_socket_module_init(LFP_VOID)
* @brief 	  socket communication main entrance
* @param[in]  LFP_VOID
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_socket_module_init(LFP_VOID)
{
	LFP_ASSERT_ERR_RET((LFP_OK == lfp_socket_server_manage_init()));
	LFP_ASSERT_ERR_RET((LFP_OK == lfp_socket_server_init()));

    return LFP_OK;
}

#endif


