/************************************************************************************
File name: lfp_socket_server.c
Description: Socket communication server implementation.
Author: wytaitaislee
Date: 2019.11.17
History: 1. create file. -- 2019.11.17
************************************************************************************/
#ifdef LFP_SOCKET_APP

#include "lfp_socket_app.h"

/*@fn		  LFP_VOID *lfp_socket_proc(LFP_VOID* pSockFd)
* @brief 	  Socket server message processing task.
* @param[in]  LFP_INT32 iSocket -- client request Network file descriptor
* @param[out] NULL
* @return	  LFP_NULL
*/	
LFP_INT32 lfp_socket_proc(LFP_VOID* pServerArgs)
{
	LFP_SOCKET_DESC_T *pServerDesc = LFP_NULL;
	LFP_PTHREAD_HADLE_T struSendTid = 0, struRecvTid = 0;
	LFP_INT32 iRet = LFP_ERR;

	LFP_ASSERT(pServerArgs);
	pServerDesc = (LFP_SOCKET_DESC_T*)pServerArgs;
/*
	if(lfp_socket_fcntl(pServerDesc->iSockFd, O_NONBLOCK) < 0)
	{
		LFP_SOCKET_SERVER_ERR("lfp_socket_fcntl[socket = %d] err[%d][%s]\n", pServerDesc->iSockFd, errno ,strerror(errno));
		iRet = LFP_ERR;
		goto my_return;
	}
*/
	if(LFP_OK != lfp_pthread_create(&struRecvTid, LFP_NULL, LFP_NULL, (LFP_VOID*)lfp_socket_recv_data_ctrl, (LFP_VOID*)pServerDesc))
	{
		iRet = LFP_ERR;
		goto my_return;
	}
	if(LFP_OK != lfp_pthread_create(&struSendTid, LFP_NULL, LFP_NULL, (LFP_VOID*)lfp_socket_send_data_ctrl, (LFP_VOID*)pServerDesc))
	{
		iRet = LFP_ERR;
		goto my_return;
	}

	while(1)
	{
		/* waiting for subprocess exit */
		if(LFP_PTHREAD_ESRCH == lfp_pthread_kill(struSendTid, 0) || LFP_PTHREAD_ESRCH == lfp_pthread_kill(struRecvTid, 0))
		{
			/* reduce resources ,then exit */
			lfp_pthread_cancel(struSendTid);
			lfp_pthread_cancel(struRecvTid);
			break;
		}
		lfp_sleep_ms(10);	
	}
my_return:
	LFP_LINUX_SOCKET_CRIT("server socket[%d] exit !\n", pServerDesc->iSockFd);
	lfp_socket_exit_subtask(pServerDesc->iSockFd);
	return iRet;
}

/*@fn		  LFP_INT32 lfp_socket_server_task(LFP_VOID* pArgs)
* @brief 	  Socket server control task.
* @param[in]  LFP_VOID* pArgs
* @param[out] NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_socket_server_task(LFP_VOID* pArgs)
{
	LFP_SOCK iSockServer = LFP_ERR;
	LFP_SOCK iSockNew = LFP_ERR;
	LFP_SOCK_ADDRIN_T struSockAddrIn;
	LFP_SOCK_ADDR_T struSockAddrNew;
	LFP_SOCKLEN_T struSockLen;

	LFP_SOCKET_SERVER_CRIT("server start\n");
	LFP_BUFF_BEZERO(&struSockAddrIn, sizeof(struSockAddrIn));
	LFP_BUFF_BEZERO(&struSockAddrNew, sizeof(struSockAddrNew));
	LFP_BUFF_BEZERO(&struSockLen, sizeof(struSockLen));

	struSockAddrIn.sin_family = LFP_AF_INET;
	struSockAddrIn.sin_port = htons(LFP_SOCKET_SERVER_PORT);
	struSockAddrIn.sin_addr.s_addr = inet_addr(LFP_SOCKET_SERVER_ADDR);
	
	iSockServer = lfp_socket_create(LFP_AF_INET, LFP_SOCK_STREAM, LFP_IPPROTO_TCP);
	
	if(0 >= iSockServer)
	{
		LFP_SOCKET_SERVER_ERR("server socket create err[%d], errstr[%s]\n", errno , strerror(errno));
		return LFP_ERR;	
	}
	if(LFP_OK != lfp_socket_bind(iSockServer, (LFP_SOCK_ADDR_T*)&struSockAddrIn, sizeof(struSockAddrIn)))
	{
		LFP_SOCKET_SERVER_ERR("socket binding failed\n");
		return LFP_ERR;
	}

	if(LFP_OK != lfp_socket_listen(iSockServer, LFP_SOCKET_MAX_LISTEN))
	{
		LFP_SOCKET_SERVER_ERR("socket listen failed\n");
		return LFP_ERR;
	}
	while(1)
	{
		struSockLen = sizeof(LFP_SOCK_ADDR_T);
		iSockNew = lfp_socket_accept(iSockServer, (LFP_SOCK_ADDR_T*)&struSockAddrNew, &struSockLen);
		LFP_SOCKET_SERVER_CRIT("accept a new socket iSockNew, iSockNew = %d\n", iSockNew);
		if(-1 == iSockNew)
		{
			continue;
		}
		if(LFP_OK != lfp_socket_create_subtask(iSockNew))
		{
			LFP_SOCKET_SERVER_ERR("create a new socket task err, iSockNew = %d\n", iSockNew);
			LFP_SAFE_CLOSE_SOCKET(iSockNew);
			continue;		
		}
	}
	LFP_SAFE_CLOSE_SOCKET(iSockServer);
	lfp_socket_create_ctrl_fini();
	return LFP_OK;
}

#endif