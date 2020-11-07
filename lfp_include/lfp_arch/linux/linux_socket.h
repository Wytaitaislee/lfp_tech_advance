/***************************************************************************************
File name: linux_socket_base.h
Description: the socket base function management on linux system.
Author: wytaitaislee
Version: V1.0.0
Date: 2020-05-30
History: 1. create file. -- 2020-05-30
         2. move socket base function to the lower layer -- 2020-06-07
****************************************************************************************/

#ifndef __LINUX_SOCKET_H__
#define __LINUX_SOCKET_H__

#include "__linux_typesdef.h"
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
typedef struct sockaddr 		LFP_SOCK_ADDR_T;
typedef struct sockaddr_in		LFP_SOCK_ADDRIN_T;
typedef socklen_t 				LFP_SOCKLEN_T;
typedef struct msghdr 			LFP_MSGHDR_T;
typedef LFP_INT32				LFP_SOCK;
#define LFP_AF_INET			    AF_INET                 
#define LFP_SOCK_STREAM         SOCK_STREAM
#define LFP_IPPROTO_TCP         IPPROTO_TCP
#define LFP_SOCKET_ERR			LFP_ERR


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

/*@fn		  LFP_INT32 linux_socket_bind(LFP_INT32 iSocketFd, LFP_CONST LFP_SOCK_ADDR_T *pStruAddr, LFP_SOCKLEN_T iSockLen)
* @brief 	  binding a server addr to the server socket
* @param[in]  LFP_INT32 iSocketFd - server socket
* @param[in]  LFP_CONST LFP_SOCK_ADDR_T *pStruAddr - the server addr
* @param[in]  LFP_SOCKLEN_T iSockLen - the server add len
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_socket_bind(LFP_INT32 iSocketFd, const LFP_SOCK_ADDR_T *pStruAddr, LFP_SOCKLEN_T iSockLen);

/*@fn		  LFP_INT32 linux_socket_listen(LFP_INT32 iSocket, LFP_INT32 iMaxConnect)
* @brief 	  listen for the specify port
* @param[in]  LFP_INT32 iSocket - server socket
* @param[in]  LFP_INT32 iMaxConnect - Maximum length of the waiting queue
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_socket_listen(LFP_INT32 iSockFd, LFP_INT32 iMaxConnect);

/*@fn		  LFP_INT32 linux_socket_accept(LFP_INT32 iSocket, LFP_SOCK_ADDR_T *pStruAddr, LFP_SOCKLEN_T* pSockLen)
* @brief 	  accept for the client.
* @param[in]  LFP_INT32 iSocket - server socket
* @param[in]  LFP_SOCK_ADDR_T *pStruAddr - the new socket tmp addr
* @param[in]  LFP_SOCKLEN_T* pSockLen - the length of the addr
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_socket_accept(LFP_INT32 iSockFd, LFP_SOCK_ADDR_T *pStruAddr, LFP_SOCKLEN_T* pSockLen);

/*@fn		  LFP_INT32 linux_socket_connect(LFP_INT32 iSocket, const LFP_SOCK_ADDR_T *pStruAddr, LFP_SOCKLEN_T iSockLen)
* @brief 	  client connect to the server.
* @param[in]  LFP_INT32 iSocket - server socket
* @param[in]  LFP_SOCK_ADDR_T *pStruAddr - the server socket addr
* @param[in]  LFP_SOCKLEN_T* pSockLen - the length of the addr
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_socket_connect(LFP_INT32 iSocketFd, const LFP_SOCK_ADDR_T *pStruAddr, LFP_SOCKLEN_T iSockLen);

/*@fn		  LFP_INT32 linux_socket_close(LFP_INT32 iSocket)
* @brief 	  close the specify socket.
* @param[in]  LFP_INT32 iSocket - the specify socket
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_socket_close(LFP_INT32 iSocketFd);

/*@fn		  LFP_SSIZE_T linux_socket_write(LFP_INT32 iSocket, LFP_CONST LFP_VOID* pBuf, LFP_SIZE_T iLen)
* @brief 	  send data to the socket
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LFP_CONST LFP_VOID* pBuf - the data to be sent
* @param[in]  LFP_SIZE_T iLen - the length of the data
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_SSIZE_T linux_socket_write(LFP_INT32 iSocketFd, LFP_CONST LFP_VOID* pBuf, LFP_SIZE_T iLen);

/*@fn		  LFP_INT32 linux_socket_fcntl(LFP_INT32 iSocket, LFP_INT32 iStyle)
* @brief 	  change the opned file character O_BLOCK / O_NONBLOCK, ect.
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LFP_INT32 iStyle - the character too be set
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_socket_fcntl(LFP_INT32 iSockFd, LFP_INT32 iStyle);

/*@fn		  LFP_SSIZE_T linux_socket_send(LFP_INT32 iSocket, LFP_CONST LFP_VOID* pBuf, LFP_SIZE_T iLen, LFP_INT32 iFlags)
* @brief 	  send data to the socket
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LFP_CONST LFP_VOID* pBuf - the data to be sent
* @param[in]  LFP_SIZE_T iLen - the length of the data
* @param[in]  LFP_INT32 iFlags - flags
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_SSIZE_T linux_socket_send(LFP_INT32 iSocketFd, LFP_CONST LFP_VOID* pBuf, LFP_SIZE_T iLen, LFP_INT32 iFlags);

/*@fn		  linux_socket_sendto(LFP_INT32 iSocket, LFP_CONST LFP_VOID* pBuf, LFP_SIZE_T iLen, LFP_INT32 iFlags, 
								LFP_CONST LFP_SOCK_ADDR_T *pDstAddr, LFP_SOCKLEN_T iSockLen)
* @brief 	  send data to the socket
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LFP_CONST LFP_VOID* pBuf - the data to be sent
* @param[in]  LFP_SIZE_T iLen - the length of the data
* @param[in]  LFP_INT32 iFlags - flags
* @param[in]  LFP_CONST LFP_SOCK_ADDR_T *pDstAddr - the dst addr
* @param[in]  LFP_SOCKLEN_T iSockLen - the addr len
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_SSIZE_T linux_socket_sendto(LFP_INT32 iSockFd, const LFP_VOID* pBuf, LFP_SIZE_T iLen, LFP_INT32 iFlags, const LFP_SOCK_ADDR_T *pDstAddr, LFP_SOCKLEN_T iSockLen);

/*@fn		  LFP_SSIZE_T linux_socket_sendmsg(LFP_INT32 iSocket, LFP_CONST LFP_MSGHDR_T *pMsg, LFP_INT32 iFlags)
* @brief 	  send data to the socket, msg type
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LFP_CONST LFP_MSGHDR_T *pMsg - the data to be sent
* @param[in]  LFP_INT32 iFlags - flags
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_SSIZE_T linux_socket_sendmsg(LFP_INT32 iSocketFd, const LFP_MSGHDR_T *pMsg, LFP_INT32 iFlags);

/*@fn		  LFP_SSIZE_T linux_socket_read(LFP_INT32 iSocket, LFP_VOID* pBuf, LFP_SIZE_T iLen)
* @brief 	  recv data from a specified socket.
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LFP_CONST LFP_VOID* pBuf - the data to be recv
* @param[in]  LFP_SIZE_T iLen - the length of the data
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_SSIZE_T linux_socket_read(LFP_INT32 iSockFd, LFP_VOID* pBuf, LFP_SIZE_T iLen);

/*@fn		  LFP_SSIZE_T linux_socket_recv(LFP_INT32 iSocket, LFP_VOID* pBuf, LFP_SIZE_T iLen, LFP_INT32 iFlags)
* @brief 	  recv data from a specified socket.
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LFP_CONST LFP_VOID* pBuf - the data to be recv
* @param[in]  LFP_SIZE_T iLen - the length of the data
* @param[in]  LFP_INT32 iFlags - recv flags
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_SSIZE_T linux_socket_recv(LFP_INT32 iSockFd, LFP_VOID* pBuf, LFP_SIZE_T iLen, LFP_INT32 iFlags);

/*@fn		  LFP_SSIZE_T linux_socket_recvfrom(LFP_INT32 iSockFd, LFP_VOID* pBuf, LFP_SIZE_T iLen, LFP_INT32 iFlags, 
												LFP_SOCK_ADDR_T *pSrcAddr, LFP_SOCKLEN_T *pSockLen)
* @brief 	  recv data from a specified socket, specified both socket and addr.
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LFP_CONST LFP_VOID* pBuf - the data to be recv
* @param[in]  LFP_SIZE_T iLen - the length of the data
* @param[in]  LFP_INT32 iFlags - recv flags
* @param[in]  LFP_SOCK_ADDR_T *pSrcAddr - the src socket addr
* @param[in]  LFP_SOCKLEN_T *pSockLen - the addr length
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_SSIZE_T linux_socket_recvfrom(LFP_INT32 iSockFd, LFP_VOID* pBuf, LFP_SIZE_T iLen, LFP_INT32 iFlags, LFP_SOCK_ADDR_T *pSrcAddr, LFP_SOCKLEN_T *pSockLen);

/*@fn		  LFP_SSIZE_T linux_socket_recvmsg(LFP_INT32 iSocket, LFP_MSGHDR_T *pMsg, LFP_INT32 iFlags)
* @brief 	  recv data from a specified socket, msg type.
* @param[in]  LFP_INT32 iSocket - The specified socket
* @param[in]  LFP_MSGHDR_T *pMsg - the msg to be recv
* @param[in]  LFP_SIZE_T iLen - the length of the data
* @param[in]  LFP_INT32 iFlags - recv flags
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_SSIZE_T linux_socket_recvmsg(LFP_INT32 iSocketFd, LFP_MSGHDR_T *pMsg, LFP_INT32 iFlags);


#endif	/*end of __LINUX_SOCKET_H__ */