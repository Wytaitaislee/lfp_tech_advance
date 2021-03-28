/************************************************************************************
 * @fileName: lfp_socket_client.c
 * @Description: Socket communication client implementation.
 * @Author: wytaitaislee
 * @Date: 2020-08-16 16:05:59
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-03-21 19:24:47
 ************************************************************************************/

#ifdef LFP_LIBS_SOCKET

#include "lfp_libs_socket.h"
#include <errno.h>

/*@fn		  LFP_INT32 lfp_socket_client_task(LFP_VOID* pArgs)
* @brief 	  socket communication client task
* @param[in]  LFP_VOID* pArgs - param
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_socket_client_task(LFP_VOID* pClientArgs)
{
	LFP_SOCK iSockClient = LFP_ERR;
	LFP_SOCK_ADDRIN_T struSockAddrIn;
	LFP_SOCKET_DESC_T *pClientDesc = LFP_NULL;
	LFP_INT32 iRet = LFP_ERR;
	LFP_PTHREAD_HANDLE_T struSendTid = 0, struRecvTid = 0;

	LFP_BUFF_BEZERO(&struSockAddrIn, sizeof(struSockAddrIn));

	iSockClient = lfp_socket_create(LFP_AF_INET, LFP_SOCK_STREAM, LFP_IPPROTO_TCP);

	if(0 >= iSockClient)
	{
		LFP_SOCKET_CLIENT_ERR("client socket create err[%d], errstr[%s]\n", errno , strerror(errno));
		return LFP_ERR;	
	}
	iRet = lfp_socket_desc_entry_init(&pClientDesc, iSockClient);
	if(LFP_OK != iRet)
	{
		LFP_SOCKET_CLIENT_ERR("client socket init desc entry failed, iSocket[%d]\n", iSockClient);
		iRet = LFP_ERR;	
		goto my_return;	
	}
	struSockAddrIn.sin_family = LFP_AF_INET;
	struSockAddrIn.sin_addr.s_addr = inet_addr("127.0.0.1");
	struSockAddrIn.sin_port = htons(8000);

	if(LFP_OK != lfp_socket_connect(iSockClient, (LFP_SOCK_ADDR_T*)&struSockAddrIn, sizeof(LFP_SOCK_ADDR_T)))
	{
		LFP_SOCKET_CLIENT_ERR("connect to server err\n");
		iRet = LFP_ERR;
		goto my_return;
	}
	/*
	if(lfp_socket_fcntl(iSockClient, O_NONBLOCK) < 0)
	{
		LFP_SOCKET_CLIENT_ERR("lfp_socket_fcntl err[%d][%s]\n", errno ,strerror(errno));
		iRet = LFP_ERR;
		goto my_return;
	}
	*/
	
	if(LFP_OK != lfp_pthread_create(&struRecvTid, LFP_NULL, LFP_NULL, (LFP_VOID*)lfp_socket_recv_data_ctrl, (LFP_VOID*)pClientDesc))
	{
		iRet = LFP_ERR;
		goto my_return;
	}

	if(LFP_OK != lfp_pthread_create(&struSendTid, LFP_NULL, LFP_NULL, (LFP_VOID*)lfp_socket_send_data_ctrl, (LFP_VOID*)pClientDesc))
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
	lfp_socket_desc_entry_fini(&pClientDesc);
	pClientDesc = LFP_NULL;
	LFP_SAFE_CLOSE_SOCKET(iSockClient);
	return iRet;
}

#endif
