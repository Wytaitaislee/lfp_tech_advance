/***
 * @FilePath: lfp_socket.h
 * @Description: Socket general business module to support network
 * communication.
 * @Author: wytaitaislee
 * @Date: 2021-08-27 23:29:52
 * @LastEditTime: 2022-03-05 21:57:33
 * @LastEditors: wytaitaislee
 * @Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#ifndef __LFP_LIBS_SOCKET_H__
#define __LFP_LIBS_SOCKET_H__

#ifdef LFP_LIBS_SOCKET

#include "lfp_arch_adapter.h" /* in order to import system dependency related header files */
#include "lfp_base.h"

#define LFP_SOCKET_MAX_LISTEN (64) /* the maximum listen num */
#define LFP_SOCKET_MAX_PACKAGE_LEN \
    (1024 * 1024) /* the maximum size of the single package */
#define LFP_SOCKET_MAX_INPUT_CHAR_ONCE (1024)
#define LFP_SOCKET_EXIT_ALIVE_PERIOD \
    (60 * 10) /* max alive period when the socket exit */

#define LFP_SOCKET_SERVER_ADDR ("127.0.0.1")
#define LFP_SOCKET_SERVER_PORT (8000)
#define LFP_SOCKET_EXIT_REQUEST_KEYS ("exit")

#define LFP_SOCKET_SERVER_CRIT(...)                                     \
    LFP_LOG_BASE(LOG_LEVEL_CRIT, LOG_MODULE_SOCKET, MASK_SOCKET_SERVER, \
                 __VA_ARGS__)
#define LFP_SOCKET_SERVER_ERR(...)                                     \
    LFP_LOG_BASE(LOG_LEVEL_ERR, LOG_MODULE_SOCKET, MASK_SOCKET_SERVER, \
                 __VA_ARGS__)
#define LFP_SOCKET_SERVER_INFO(...)                                     \
    LFP_LOG_BASE(LOG_LEVEL_INFO, LOG_MODULE_SOCKET, MASK_SOCKET_SERVER, \
                 __VA_ARGS__)

#define LFP_SOCKET_CLIENT_CRIT(...)                                     \
    LFP_LOG_BASE(LOG_LEVEL_CRIT, LOG_MODULE_SOCKET, MASK_SOCKET_CLIENT, \
                 __VA_ARGS__)
#define LFP_SOCKET_CLIENT_ERR(...)                                     \
    LFP_LOG_BASE(LOG_LEVEL_ERR, LOG_MODULE_SOCKET, MASK_SOCKET_CLIENT, \
                 __VA_ARGS__)
#define LFP_SOCKET_CLIENT_INFO(...)                                     \
    LFP_LOG_BASE(LOG_LEVEL_INFO, LOG_MODULE_SOCKET, MASK_SOCKET_CLIENT, \
                 __VA_ARGS__)

#define LFP_SOCKET_CTRL_CRIT(...) \
    LFP_LOG_BASE(LOG_LEVEL_CRIT, LOG_MODULE_SOCKET, MASK_SOCKET_CTRL, __VA_ARGS__)
#define LFP_SOCKET_CTRL_ERR(...) \
    LFP_LOG_BASE(LOG_LEVEL_ERR, LOG_MODULE_SOCKET, MASK_SOCKET_CTRL, __VA_ARGS__)
#define LFP_SOCKET_CTRL_INFO(...) \
    LFP_LOG_BASE(LOG_LEVEL_INFO, LOG_MODULE_SOCKET, MASK_SOCKET_CTRL, __VA_ARGS__)

/* the head data structure */
typedef struct lfp_socket_package_head_t {
    LFP_INT32 iDataLen;
    LFP_INT32 iMaxDataLen;
} LFP_SCOKET_PACKAGE_HEAD_T;

/* the whole package data structure */
typedef struct lfp_socket_package_t {
    LFP_SCOKET_PACKAGE_HEAD_T struHead;
    LFP_INT8 *iPackageData;
} LFP_SOCKET_PACKAGE_T;

/* the full duplex data transmission structure */
typedef struct lfp_socket_ctrl_t {
    LFP_SOCKET_PACKAGE_T struRecvCtrl;
    LFP_SOCKET_PACKAGE_T struSendCtrl;
} LFP_SOCKET_CTRL_T;

/* the socket desc structure */
typedef struct lfp_socket_desc_t {
    LFP_SOCK iSockFd;
    LFP_INT32 iExitTime;
    LFP_SEM_T semSync;
    LFP_SOCKET_CTRL_T struSocketCtrl;
} LFP_SOCKET_DESC_T;

typedef struct lfp_socket_server_manage_t {
    LFP_MUTEX_T mutex;
    LFP_SOCKET_DESC_T *pSocketDesc[LFP_SOCKET_MAX_LISTEN];
} LFP_SOCKET_SERVER_MANAGE_T;

#define LFP_SOCKET_THIS_SERVER_DESC(pManage, idx) (pManage->pSocketDesc[idx])
#define LFP_SOCKET_THIS_RECV(pDesc) (pDesc->struSocketCtrl.struRecvCtrl)
#define LFP_SOCKET_THIS_SEND(pDesc) (pDesc->struSocketCtrl.struSendCtrl)
#define LFP_SOCKET_THIS_RECV_HEAD(pDesc) \
    ((LFP_SOCKET_THIS_RECV(pDesc)).struHead)
#define LFP_SOCKET_THIS_RECV_BODY(pDesc) \
    (LFP_SOCKET_THIS_RECV(pDesc).iPackageData)
#define LFP_SOCKET_THIS_SEND_HEAD(pDesc) (LFP_SOCKET_THIS_SEND(pDesc).struHead)
#define LFP_SOCKET_THIS_SEND_BODY(pDesc) \
    (LFP_SOCKET_THIS_SEND(pDesc).iPackageData)
#define LFP_SOCKET_THIS_BODY_OFFSET(pDesc) \
    (sizeof(pDesc->struSocketCtrl.struSendCtrl.struHead))

/*@fn		  LFP_INT32 lfp_socket_module_init(LFP_VOID)
 * @brief 	  socket communication main entrance
 * @param[in]  LFP_VOID
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 lfp_socket_module_init(LFP_VOID);

/*@fn		  LFP_INT32 lfp_socket_create_ctrl_fini(LFP_VOID)
 * @brief 	  socket create ctrl fini, recycle the malloc resources.
 * @param[in]  LFP_VOID
 * @param[out] NULL
 * @return	  LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_socket_create_ctrl_fini(LFP_VOID);

/*@fn		  LFP_VOID *lfp_socket_proc(LFP_VOID* pSockFd)
 * @brief 	  Socket server message processing task.
 * @param[in]  LFP_INT32 iSocket -- client request Network file descriptor
 * @param[out] NULL
 * @return	  LFP_NULL
 */
LFP_INT32 lfp_socket_proc(LFP_VOID *pSocket);

/*@fn		  LFP_INT32 lfp_socket_server_task(LFP_VOID* pArgs)
 * @brief 	  Socket server control task.
 * @param[in]  LFP_VOID* pArgs
 * @param[out] NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 lfp_socket_server_task(LFP_VOID *pArgs);

/*@fn		  LFP_INT32 lfp_socket_client_task(LFP_VOID* pArgs)
 * @brief 	  socket communication client task
 * @param[in]  LFP_VOID* pArgs - param
 * @param[out] NULL
 * @return	  LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_socket_client_task(LFP_VOID *pArgs);

/*@fn		  LFP_INT32 lfp_socket_create_subtask(LFP_INT32 iSocket)
 * @brief 	  the server socket create a new task to proc the client
 * communication.
 * @param[in]  LFP_INT32 iSocket - create identity
 * @param[out] NULL
 * @return	  LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_socket_create_subtask(LFP_INT32 iSocket);

/*@fn		  LFP_INT32 lfp_socket_exit_subtask(LFP_INT32 iSocket)
 * @brief 	  the server socket exit ,end of server session, recycle
 * resources.
 * @param[in]  LFP_INT32 iSocket - recycle socket id
 * @param[out] LFP_NULL
 * @return	  LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_socket_exit_subtask(LFP_INT32 iSocket);

/*@fn		  LFP_INT32 lfp_socket_server_manage_init(LFP_VOID)
 * @brief 	  socket manage init, malloc manage resources.
 * @param[in]  LFP_VOID
 * @param[out] NULL
 * @return	  LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_socket_server_manage_init(LFP_VOID);

/*@fn		  LFP_INT32 lfp_socket_server_manage_fini(LFP_VOID)
 * @brief 	  socket server manage fini, recycle the malloc resources.
 * @param[in]  LFP_VOID
 * @param[out] LFP_NULL
 * @return	  LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_socket_server_manage_fini(LFP_VOID);

/*@fn		  LFP_INT32 lfp_socket_server_manage_node_recycle(LFP_VOID)
* @brief 	  When a socket connection is disconnected and
                          no new connection is established for a period of time
                          the resource occupation is released.
* @param[in]  LFP_VOID
* @param[out] LFP_NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_socket_server_manage_node_recycle(LFP_VOID);

/*@fn		  LFP_INT32 lfp_socket_package_entry_init(LFP_SOCKET_PACKAGE_T
 * *pSocketPackage)
 * @brief 	  socket package entry init, if memory already malloced, clear
 * the memory buffer.
 * @param[in]  LFP_NULL
 * @param[out] LFP_SOCKET_PACKAGE_T *pSocketPackage - send or recv package
 * entry.
 * @return	  LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_socket_package_entry_init(LFP_SOCKET_PACKAGE_T *pSocketPackage);

/*@fn		  LFP_INT32 lfp_socket_package_entry_fini(LFP_SOCKET_PACKAGE_T
 * *pSocketPackage)
 * @brief 	  socket package entry fini, if memory already malloced, free
 * it.
 * @param[in]  LFP_NULL
 * @param[out] LFP_SOCKET_PACKAGE_T *pSocketPackage - send or recv package
 * entry.
 * @return	  LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_socket_package_entry_fini(LFP_SOCKET_PACKAGE_T *pSocketPackage);

/*@fn		  LFP_INT32 lfp_socket_ctrl_entry_init(LFP_SOCKET_CTRL_T
 * *pSocketCtrl)
 * @brief 	  socket communication entry init, include send and receive data
 * description
 * @param[in]  LFP_NULL
 * @param[out] LFP_SOCKET_CTRL_T *pSocketCtrl - communication entry
 * @return	  LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_socket_ctrl_entry_init(LFP_SOCKET_CTRL_T *pSocketCtrl);

/*@fn		  LFP_INT32 lfp_socket_ctrl_entry_fini(LFP_SOCKET_CTRL_T
 * *pSocketCtrl)
 * @brief 	  socket communication entry fini, include send and receive data
 * description
 * @param[in]  LFP_NULL
 * @param[out] LFP_SOCKET_CTRL_T *pSocketCtrl - communication entry
 * @return	  LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_socket_ctrl_entry_fini(LFP_SOCKET_CTRL_T *pSocketCtrl);

/*@fn		  LFP_INT32 lfp_socket_desc_entry_init(LFP_SOCKET_DESC_T
 * **ppDesc, LFP_INT32 iSocket)
 * @brief 	  socket desc entry init, to manage a full duplex socket
 * communication description
 * @param[in]  LFP_SOCKET_DESC_T **ppDesc - description entry
 * @param[out] LFP_INT32 iSocket - socket id
 * @return	  LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_socket_desc_entry_init(LFP_SOCKET_DESC_T **ppDesc,
                                     LFP_INT32 iSocket);

/*@fn		  LFP_INT32 lfp_socket_desc_entry_fini(LFP_SOCKET_DESC_T
 * **ppDesc)
 * @brief 	  socket desc entry fini, to manage a full duplex socket
 * communication description
 * @param[in]  LFP_SOCKET_DESC_T **ppDesc - description entry
 * @return	  LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_socket_desc_entry_fini(LFP_SOCKET_DESC_T **ppDesc);

/*@fn		  LFP_INT32 lfp_socket_server_exit(LFP_VOID)
 * @brief 	  the server exit ,end of server pthread pool, recycle the whole
 * server resources.
 * @param[out] LFP_NULL
 * @return	  LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_socket_server_exit(LFP_VOID);

/*@fn		  LFP_INT32 lfp_socket_server_init(LFP_VOID)
 * @brief 	  socket server communication main entrance
 * @param[in]  LFP_VOID
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 lfp_socket_server_init(LFP_VOID);

/*@fn		  LFP_INT32 lfp_socket_client_init(LFP_VOID)
 * @brief 	  socket client communication main entrance
 * @param[in]  LFP_VOID
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 lfp_socket_client_init(LFP_VOID);

/*@fn		  LFP_INT32 lfp_socket_recv_data_ctrl(LFP_SOCKET_DESC_T *pDesc)
 * @brief 	  recv data ctrl
 * @param[in]  LFP_SOCKET_DESC_T *pDesc - The describe of a communication
 * channel.
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 lfp_socket_recv_data_ctrl(LFP_SOCKET_DESC_T *pDesc);

/*@fn		  LFP_INT32 LFP_INT32 lfp_socket_send_data(LFP_INT32 iSocket,
 * LFP_CONST LFP_INT8* pData, LFP_INT32 iDataLen)
 * @brief 	  rsend data to the socket, custom protocol(data package : head
 * + data)
 * @param[in]  LFP_INT32 iSocket - The specified socket
 * @param[in]  LFP_INT32 pSendData - the data to send
 * @param[in]  LFP_SOCKET_PACKAGE_T *pstruPkgAll - The package data structure
 * @param[out] NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 lfp_socket_send_data(LFP_INT32 iSocket, LFP_CONST LFP_INT8 *pData,
                               LFP_INT32 iDataLen);

/*@fn		  LFP_INT32 lfp_socket_send_data(LFP_INT32 iSocket, LFP_INT8*
 * pData, LFP_INT32 iDataLen)
 * @brief 	  rsend data to the socket, custom protocol(data package : head
 * + data)
 * @param[in]  LFP_INT32 iSocket - The specified socket
 * @param[in]  LFP_INT8* pData - the data to send
 * @param[in]  LFP_INT32 iDataLen  - The length of data
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 lfp_socket_send_data_ctrl(LFP_SOCKET_DESC_T *pDesc);

/*@fn		  LFP_INT32 lfp_socket_recv_data(LFP_SOCKET_DESC_T *pDesc)
 * @brief 	  recv data from the socket, custom protocol(data package : head
 * + data body
 * @param[in]  LFP_SOCKET_DESC_T *pDesc - The describe of a communication
 * channel.
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 lfp_socket_recv_data(LFP_SOCKET_DESC_T *pDesc);

#endif

#endif /* end of __LFP_LIBS_SOCKET_H__ */
