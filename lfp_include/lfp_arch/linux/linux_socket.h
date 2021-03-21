/***************************************************************************************
 * @fileName: linux_socket_base.h
 * @Description:  the socket base function management on linux system.
 * @Author: wytaitaislee
 * @Date: 2020-09-26 18:43:32
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-03-21 19:59:33
****************************************************************************************/

#ifndef __LINUX_SOCKET_H__
#define __LINUX_SOCKET_H__

#include "lfp_base.h"
#include "linux/include/linux_typesdef.h"
#include <sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
/* 
#define lfp_os_data_structure_redirect(undername)
do
{
	#define LFP_#undername #LFP_OS_#undername
}while(0) */

/* socket relevant typesdef */
typedef struct sockaddr 		LINUX_SOCK_ADDR_T;
typedef struct sockaddr_in		LINUX_SOCK_ADDRIN_T;
typedef socklen_t 				LINUX_SOCKLEN_T;
typedef struct msghdr 			LINUX_MSGHDR_T;
typedef LFP_INT32				LINUX_SOCK;
#define LINUX_AF_INET			AF_INET
#define LINUX_SOCK_STREAM		SOCK_STREAM
#define LINUX_IPPROTO_TCP		IPPROTO_TCP

#define LFP_LINUX_SOCKET_CRIT(...)   \
	LFP_UTIL_BASE(UTIL_LEVEL_CRIT, UTIL_MODULE_LINUX, MASK_SOCKET, __VA_ARGS__) 
#define LFP_LINUX_SOCKET_ERR(...)   \
	LFP_UTIL_BASE(UTIL_LEVEL_ERR, UTIL_MODULE_LINUX, MASK_SOCKET, __VA_ARGS__) 
#define LFP_LINUX_SOCKET_INFO(...)   \
	LFP_UTIL_BASE(UTIL_LEVEL_INFO, UTIL_MODULE_LINUX, MASK_SOCKET, __VA_ARGS__)

/*@fn		  LFP_INT32 linux_socket_create(LFP_INT32 iProFamily, LFP_INT32 iSocketType, LFP_INT32 iProtocal)
* @brief 	  create a new socket
* @param[in]  LFP_INT32 iProFamily - protocol domain
* @param[in]  LFP_INT32 iSocketType - Flow Control
* @param[in]  LFP_INT32 iProtocal - protocol type
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_socket_create(LFP_INT32 iProFamily, LFP_INT32 iSocketType, LFP_INT32 iProtocal);

/*@fn		  LFP_INT32 linux_socket_bind(LFP_INT32 iSocketFd, LFP_CONST LINUX_SOCK_ADDR_T *pStruAddr, LINUX_SOCKLEN_T iSockLen)
* @brief 	  binding a server addr to the server socket
* @param[in]  LFP_INT32 iSocketFd - server socket
* @param[in]  LFP_CONST LINUX_SOCK_ADDR_T *pStruAddr - the server addr
* @param[in]  LINUX_SOCKLEN_T iSockLen - the server add len
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_socket_bind(LFP_INT32 iSocketFd, const LINUX_SOCK_ADDR_T *pStruAddr, LINUX_SOCKLEN_T iSockLen);

/*@fn		  LFP_INT32 linux_socket_listen(LFP_INT32 iSocket, LFP_INT32 iMaxConnect)
* @brief 	  listen for the specify port
* @param[in]  LFP_INT32 iSocket - server socket
* @param[in]  LFP_INT32 iMaxConnect - Maximum length of the waiting queue
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_socket_listen(LFP_INT32 iSockFd, LFP_INT32 iMaxConnect);

/*@fn		  LFP_INT32 linux_socket_accept(LFP_INT32 iSocket, LINUX_SOCK_ADDR_T *pStruAddr, LINUX_SOCKLEN_T* pSockLen)
* @brief 	  accept for the client.
* @param[in]  LFP_INT32 iSocket - server socket
* @param[in]  LINUX_SOCK_ADDR_T *pStruAddr - the new socket tmp addr
* @param[in]  LINUX_SOCKLEN_T* pSockLen - the length of the addr
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_socket_accept(LFP_INT32 iSockFd, LINUX_SOCK_ADDR_T *pStruAddr, LINUX_SOCKLEN_T* pSockLen);

/*@fn		  LFP_INT32 linux_socket_connect(LFP_INT32 iSocket, const LINUX_SOCK_ADDR_T *pStruAddr, LINUX_SOCKLEN_T iSockLen)
* @brief 	  client connect to the server.
* @param[in]  LFP_INT32 iSocket - server socket
* @param[in]  LINUX_SOCK_ADDR_T *pStruAddr - the server socket addr
* @param[in]  LINUX_SOCKLEN_T* pSockLen - the length of the addr
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_socket_connect(LFP_INT32 iSocketFd, const LINUX_SOCK_ADDR_T *pStruAddr, LINUX_SOCKLEN_T iSockLen);

/*@fn		  LFP_INT32 linux_socket_close(LFP_INT32 iSocket)
* @brief 	  close the specify socket.
* @param[in]  LFP_INT32 iSocket - the specify socket
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_socket_close(LFP_INT32 iSocketFd);

/*@fn		  LINUX_SSIZE_T linux_socket_write(LFP_INT32 iSocket, LFP_CONST LFP_VOID* pBuf, LINUX_SIZE_T iLen)
* @brief 	  send data to the socket
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LFP_CONST LFP_VOID* pBuf - the data to be sent
* @param[in]  LINUX_SIZE_T iLen - the length of the data
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LINUX_SSIZE_T linux_socket_write(LFP_INT32 iSocketFd, LFP_CONST LFP_VOID* pBuf, LINUX_SIZE_T iLen);

/*@fn		  LFP_INT32 linux_socket_fcntl(LFP_INT32 iSocket, LFP_INT32 iStyle)
* @brief 	  change the opned file character O_BLOCK / O_NONBLOCK, ect.
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LFP_INT32 iStyle - the character too be set
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_socket_fcntl(LFP_INT32 iSockFd, LFP_INT32 iStyle);

/*@fn		  LINUX_SSIZE_T linux_socket_send(LFP_INT32 iSocket, LFP_CONST LFP_VOID* pBuf, LINUX_SIZE_T iLen, LFP_INT32 iFlags)
* @brief 	  send data to the socket
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LFP_CONST LFP_VOID* pBuf - the data to be sent
* @param[in]  LINUX_SIZE_T iLen - the length of the data
* @param[in]  LFP_INT32 iFlags - flags
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LINUX_SSIZE_T linux_socket_send(LFP_INT32 iSocketFd, LFP_CONST LFP_VOID* pBuf, LINUX_SIZE_T iLen, LFP_INT32 iFlags);

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
LINUX_SSIZE_T linux_socket_sendto(LFP_INT32 iSockFd, const LFP_VOID* pBuf, LINUX_SIZE_T iLen, LFP_INT32 iFlags, const LINUX_SOCK_ADDR_T *pDstAddr, LINUX_SOCKLEN_T iSockLen);

/*@fn		  LINUX_SSIZE_T linux_socket_sendmsg(LFP_INT32 iSocket, LFP_CONST LINUX_MSGHDR_T *pMsg, LFP_INT32 iFlags)
* @brief 	  send data to the socket, msg type
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LFP_CONST LINUX_MSGHDR_T *pMsg - the data to be sent
* @param[in]  LFP_INT32 iFlags - flags
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LINUX_SSIZE_T linux_socket_sendmsg(LFP_INT32 iSocketFd, const LINUX_MSGHDR_T *pMsg, LFP_INT32 iFlags);

/*@fn		  LINUX_SSIZE_T linux_socket_read(LFP_INT32 iSocket, LFP_VOID* pBuf, LINUX_SIZE_T iLen)
* @brief 	  recv data from a specified socket.
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LFP_CONST LFP_VOID* pBuf - the data to be recv
* @param[in]  LINUX_SIZE_T iLen - the length of the data
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LINUX_SSIZE_T linux_socket_read(LFP_INT32 iSockFd, LFP_VOID* pBuf, LINUX_SIZE_T iLen);

/*@fn		  LINUX_SSIZE_T linux_socket_recv(LFP_INT32 iSocket, LFP_VOID* pBuf, LINUX_SIZE_T iLen, LFP_INT32 iFlags)
* @brief 	  recv data from a specified socket.
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LFP_CONST LFP_VOID* pBuf - the data to be recv
* @param[in]  LINUX_SIZE_T iLen - the length of the data
* @param[in]  LFP_INT32 iFlags - recv flags
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LINUX_SSIZE_T linux_socket_recv(LFP_INT32 iSockFd, LFP_VOID* pBuf, LINUX_SIZE_T iLen, LFP_INT32 iFlags);

/*@fn		  LINUX_SSIZE_T linux_socket_recvfrom(LFP_INT32 iSockFd, LFP_VOID* pBuf, LINUX_SIZE_T iLen, LFP_INT32 iFlags, 
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
LINUX_SSIZE_T linux_socket_recvfrom(LFP_INT32 iSockFd, LFP_VOID* pBuf, LINUX_SIZE_T iLen, LFP_INT32 iFlags, LINUX_SOCK_ADDR_T *pSrcAddr, LINUX_SOCKLEN_T *pSockLen);

/*@fn		  LINUX_SSIZE_T linux_socket_recvmsg(LFP_INT32 iSocket, LINUX_MSGHDR_T *pMsg, LFP_INT32 iFlags)
* @brief 	  recv data from a specified socket, msg type.
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LINUX_MSGHDR_T *pMsg - the msg to be recv
* @param[in]  LINUX_SIZE_T iLen - the length of the data
* @param[in]  LFP_INT32 iFlags - recv flags
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LINUX_SSIZE_T linux_socket_recvmsg(LFP_INT32 iSocketFd, LINUX_MSGHDR_T *pMsg, LFP_INT32 iFlags);


#endif	/*end of __LINUX_SOCKET_H__ */