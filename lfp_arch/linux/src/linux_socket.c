/***************************************************************************************
File name: linux_socket.c
Description: Operating system adaptation layer, matching different architecture platforms.
			 pthread implement.
Author: wytaitaislee
Date: 2020-06-07
History: 1. create file. -- 2020-06-07
****************************************************************************************/

#include "linux_socket.h"
#include "linux_typesdef.h"
#include <fcntl.h>
#include <errno.h>

/*@fn		  LFP_INT32 linux_socket_create(LFP_INT32 iProFamily, LFP_INT32 iSocketType, LFP_INT32 iProtocal)
* @brief 	  create a new socket
* @param[in]  LFP_INT32 iProFamily - protocol domain
* @param[in]  LFP_INT32 iSocketType - Flow Control
* @param[in]  LFP_INT32 iProtocal - protocol type
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_socket_create(LFP_INT32 iProFamily, LFP_INT32 iSocketType, LFP_INT32 iProtocal)
{
	LFP_INT32 iRet = -1;

	iRet = socket(iProFamily, iSocketType, iProtocal);
	if(0 >= iRet)
	{
		LFP_LINUX_SOCKET_ERR("create a new socket err, iRet[%d]\n", iRet);
	}
	return iRet;
}

/*@fn		  LFP_INT32 linux_socket_bind(LFP_INT32 iSocketFd, LFP_CONST LINUX_SOCK_ADDR_T *pStruAddr, LINUX_SOCKLEN_T iSockLen)
* @brief 	  binding a server addr to the server socket
* @param[in]  LFP_INT32 iSocketFd - server socket
* @param[in]  LFP_CONST LINUX_SOCK_ADDR_T *pStruAddr - the server addr
* @param[in]  LINUX_SOCKLEN_T iSockLen - the server add len
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_socket_bind(LFP_INT32 iSocket, LFP_CONST LINUX_SOCK_ADDR_T *pStruAddr, LINUX_SOCKLEN_T iSockLen)
{
	LFP_INT32 iRet = 0;

	LFP_ASSERT_ERR_RET(iSocket > 0);
	LFP_ASSERT_ERR_RET(pStruAddr);
	iRet = bind(iSocket, pStruAddr, iSockLen);
	if(0 != iRet)
	{
		LFP_LINUX_SOCKET_ERR("binding to socket[%d] errno[%d][%s], iRet[%d]\n", 
								iSocket, errno, strerror(errno), iRet);
		return LFP_ERR;
	}
	return LFP_OK;
}

/*@fn		  LFP_INT32 linux_socket_listen(LFP_INT32 iSocket, LFP_INT32 iMaxConnect)
* @brief 	  listen for the specify port
* @param[in]  LFP_INT32 iSocket - server socket
* @param[in]  LFP_INT32 iMaxConnect - Maximum length of the waiting queue
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_socket_listen(LFP_INT32 iSocket, LFP_INT32 iMaxConnect)
{
	LFP_INT32 iRet = 0;

	LFP_ASSERT_ERR_RET(iSocket > 0);
	LFP_ASSERT_ERR_RET(iMaxConnect > 0);
	iRet = listen(iSocket, iMaxConnect);
	if(0 != iRet)
	{
		LFP_LINUX_SOCKET_ERR("socket[%d] listen err, iRet[%d]\n", iSocket, iRet);
		return LFP_ERR;
	}
	return LFP_OK; 
}

/*@fn		  LFP_INT32 linux_socket_accept(LFP_INT32 iSocket, LINUX_SOCK_ADDR_T *pStruAddr, LINUX_SOCKLEN_T* pSockLen)
* @brief 	  accept for the client.
* @param[in]  LFP_INT32 iSocket - server socket
* @param[in]  LINUX_SOCK_ADDR_T *pStruAddr - the new socket tmp addr
* @param[in]  LINUX_SOCKLEN_T* pSockLen - the length of the addr
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_socket_accept(LFP_INT32 iSocket, LINUX_SOCK_ADDR_T *pStruAddr, LINUX_SOCKLEN_T* pSockLen)
{
	LFP_ASSERT_ERR_RET(iSocket > 0);
	LFP_ASSERT_ERR_RET(pStruAddr && pSockLen);
	return accept(iSocket, pStruAddr, pSockLen);
}

/*@fn		  LFP_INT32 linux_socket_connect(LFP_INT32 iSocket, const LINUX_SOCK_ADDR_T *pStruAddr, LINUX_SOCKLEN_T iSockLen)
* @brief 	  client connect to the server.
* @param[in]  LFP_INT32 iSocket - server socket
* @param[in]  LINUX_SOCK_ADDR_T *pStruAddr - the server socket addr
* @param[in]  LINUX_SOCKLEN_T* pSockLen - the length of the addr
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_socket_connect(LFP_INT32 iSocket, const LINUX_SOCK_ADDR_T *pStruAddr, LINUX_SOCKLEN_T iSockLen)
{
	LFP_INT32 iRet = 0;

	LFP_ASSERT_ERR_RET((iSocket > 0) && (iSockLen > 0));
	LFP_ASSERT_ERR_RET(pStruAddr);
	iRet = connect(iSocket, pStruAddr, iSockLen);
	if(0 != iRet)
	{
		LFP_LINUX_SOCKET_ERR("connect to server[%d] err, iRet[%d]\n", iSocket, iRet);
		return LFP_ERR;
	}
	return LFP_OK; 
}

/*@fn		  LFP_INT32 linux_socket_close(LFP_INT32 iSocket)
* @brief 	  close the specify socket.
* @param[in]  LFP_INT32 iSocket - the specify socket
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_socket_close(LFP_INT32 iSocket)
{
	LFP_ASSERT_ERR_RET(iSocket);
	LFP_SAFE_CLOSE_SOCKET(iSocket);
	return LFP_OK;
}

/*@fn		  LINUX_SSIZE_T linux_socket_write(LFP_INT32 iSocket, const LFP_VOID* pBuf, LINUX_SIZE_T iLen)
* @brief 	  send data to the socket
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LFP_CONST LFP_VOID* pBuf - the data to be sent
* @param[in]  LINUX_SIZE_T iLen - the length of the data
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LINUX_SSIZE_T linux_socket_write(LFP_INT32 iSocket, LFP_CONST LFP_VOID* pBuf, LINUX_SIZE_T iLen)
{
	LFP_ASSERT_ERR_RET((iSocket > 0) && (iLen >= 0));
	LFP_ASSERT_ERR_RET(pBuf);
	return write(iSocket, pBuf, iLen);
}

/*@fn		  LINUX_SSIZE_T linux_socket_send(LFP_INT32 iSocket, LFP_CONST LFP_VOID* pBuf, LINUX_SIZE_T iLen, LFP_INT32 iFlags)
* @brief 	  send data to the socket
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LFP_CONST LFP_VOID* pBuf - the data to be sent
* @param[in]  LINUX_SIZE_T iLen - the length of the data
* @param[in]  LFP_INT32 iFlags - flags
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LINUX_SSIZE_T linux_socket_send(LFP_INT32 iSocket, LFP_CONST LFP_VOID* pBuf, LINUX_SIZE_T iLen, LFP_INT32 iFlags)
{
	LINUX_SSIZE_T iSendBytes = 0;

	LFP_ASSERT_ERR_RET((iSocket > 0) && (iLen > 0));
	LFP_ASSERT_ERR_RET(pBuf);
	iSendBytes = send(iSocket, pBuf, iLen, iFlags);
	return ((0 >= iSendBytes) ? LFP_ERR:iSendBytes);
}

/*@fn		  linux_socket_sendto(LFP_INT32 iSocket, LFP_CONST LFP_VOID* pBuf, LINUX_SIZE_T iLen, LFP_INT32 iFlags, 
								LFP_CONST LINUX_SOCK_ADDR_T *pDstAddr, LINUX_SOCKLEN_T iSockLen)
* @brief 	  send data to the socket
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LFP_CONST LFP_VOID* pBuf - the data to be sent
* @param[in]  LINUX_SIZE_T iLen - the length of the data
* @param[in]  LFP_INT32 iFlags - flags
* @param[in]  LFP_CONST LINUX_SOCK_ADDR_T *pDstAddr - the dst addr
* @param[in]  LINUX_SOCKLEN_T iSockLen - the addr len
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LINUX_SSIZE_T linux_socket_sendto(LFP_INT32 iSocket, LFP_CONST LFP_VOID* pBuf, LINUX_SIZE_T iLen, LFP_INT32 iFlags, LFP_CONST LINUX_SOCK_ADDR_T *pDstAddr, LINUX_SOCKLEN_T iSockLen)
{
	LINUX_SSIZE_T iSendBytes = 0;

	LFP_ASSERT_ERR_RET((iSocket > 0) && (iLen > 0) && (iSockLen > 0));
	LFP_ASSERT_ERR_RET(pBuf && pDstAddr);
	iSendBytes = sendto(iSocket, pBuf, iLen, iFlags, pDstAddr, iSockLen);
	return ((0 >= iSendBytes) ? LFP_ERR:iSendBytes);
}

/*@fn		  LINUX_SSIZE_T linux_socket_sendmsg(LFP_INT32 iSocket, LFP_CONST LINUX_MSGHDR_T *pMsg, LFP_INT32 iFlags)
* @brief 	  send data to the socket, msg type
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LFP_CONST LINUX_MSGHDR_T *pMsg - the data to be sent
* @param[in]  LFP_INT32 iFlags - flags
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LINUX_SSIZE_T linux_socket_sendmsg(LFP_INT32 iSocket, LFP_CONST LINUX_MSGHDR_T *pMsg, LFP_INT32 iFlags)
{
	LINUX_SSIZE_T iSendBytes = 0;

	LFP_ASSERT_ERR_RET((iSocket > 0));
	LFP_ASSERT_ERR_RET(pMsg);
	iSendBytes = sendmsg(iSocket, pMsg, iFlags);
	return ((0 >= iSendBytes) ? LFP_ERR:iSendBytes);	
}

/*@fn		  LFP_INT32 linux_socket_fcntl(LFP_INT32 iSocket, LFP_INT32 iStyle)
* @brief 	  change the opned file character O_BLOCK / O_NONBLOCK, ect.
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LFP_INT32 iStyle - the character too be set
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_socket_fcntl(LFP_INT32 iSocket, LFP_INT32 iStyle)
{
	LFP_INT32 iFlags = 0;

	LFP_ASSERT_ERR_RET(iSocket > 0);
	iFlags = fcntl(iSocket, F_GETFL, 0); 

	return fcntl(iSocket, F_SETFL, iFlags | iStyle);
}

/*@fn		  LINUX_SSIZE_T linux_socket_read(LFP_INT32 iSocket, LFP_VOID* pBuf, LINUX_SIZE_T iLen)
* @brief 	  recv data from a specified socket.
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LFP_CONST LFP_VOID* pBuf - the data to be recv
* @param[in]  LINUX_SIZE_T iLen - the length of the data
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LINUX_SSIZE_T linux_socket_read(LFP_INT32 iSocket, LFP_VOID* pBuf, LINUX_SIZE_T iLen)
{
	LFP_ASSERT_ERR_RET((iSocket > 0) && (iLen > 0));
	LFP_ASSERT_ERR_RET(pBuf);
	return read(iSocket, pBuf, iLen);
}

/*@fn		  LINUX_SSIZE_T linux_socket_recv(LFP_INT32 iSocket, LFP_VOID* pBuf, LINUX_SIZE_T iLen, LFP_INT32 iFlags)
* @brief 	  recv data from a specified socket.
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LFP_CONST LFP_VOID* pBuf - the data to be recv
* @param[in]  LINUX_SIZE_T iLen - the length of the data
* @param[in]  LFP_INT32 iFlags - recv flags
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LINUX_SSIZE_T linux_socket_recv(LFP_INT32 iSocket, LFP_VOID* pBuf, LINUX_SIZE_T iLen, LFP_INT32 iFlags)
{
	LFP_ASSERT_ERR_RET((iSocket > 0) && (iLen > 0));
	LFP_ASSERT_ERR_RET(pBuf);
	return recv(iSocket, pBuf, iLen, iFlags);
}

/*@fn		  LINUX_SSIZE_T linux_socket_recvfrom(LFP_INT32 iSocket, LFP_VOID* pBuf, LINUX_SIZE_T iLen, LFP_INT32 iFlags, 
												LINUX_SOCK_ADDR_T *pSrcAddr, LINUX_SOCKLEN_T *pSockLen)
* @brief 	  recv data from a specified socket, specified both socket and addr.
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LFP_CONST LFP_VOID* pBuf - the data to be recv
* @param[in]  LINUX_SIZE_T iLen - the length of the data
* @param[in]  LFP_INT32 iFlags - recv flags
* @param[in]  LINUX_SOCK_ADDR_T *pSrcAddr - the src socket addr
* @param[in]  LINUX_SOCKLEN_T *pSockLen - the addr length
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LINUX_SSIZE_T linux_socket_recvfrom(LFP_INT32 iSocket, LFP_VOID* pBuf, LINUX_SIZE_T iLen, LFP_INT32 iFlags, LINUX_SOCK_ADDR_T *pSrcAddr, LINUX_SOCKLEN_T *pSockLen)
{
	LFP_ASSERT_ERR_RET((iSocket > 0) && (iLen > 0));
	LFP_ASSERT_ERR_RET(pBuf && pSrcAddr && pSockLen);
	return recvfrom(iSocket, pBuf, iLen,iFlags, pSrcAddr, pSockLen);	
}

/*@fn		  LINUX_SSIZE_T linux_socket_recvmsg(LFP_INT32 iSocket, LINUX_MSGHDR_T *pMsg, LFP_INT32 iFlags)
* @brief 	  recv data from a specified socket, msg type.
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LINUX_MSGHDR_T *pMsg - the msg to be recv
* @param[in]  LINUX_SIZE_T iLen - the length of the data
* @param[in]  LFP_INT32 iFlags - recv flags
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LINUX_SSIZE_T linux_socket_recvmsg(LFP_INT32 iSocket, LINUX_MSGHDR_T *pMsg, LFP_INT32 iFlags)
{
	LFP_ASSERT_ERR_RET(iSocket > 0);
	LFP_ASSERT_ERR_RET(pMsg);
	return recvmsg(iSocket, pMsg, iFlags);	
}
