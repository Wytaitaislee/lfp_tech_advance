/*
 * @FilePath: lfp_arch_adapter_socket.c
 * @Description: System adaptation layer. Adapter to different socket on
 * different OS.
 * @Author: wytaitaislee
 * @Date: 2021-08-27 23:29:52
 * @LastEditTime: 2022-03-19 19:16:11
 * @LastEditors: wytaitaislee
 * Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#include "lfp_arch_abstract.h"
#include "lfp_arch_adapter.h"
#include "lfp_arch_adapter_typesdef.h"

#define LFP_GET_SOCKET_ENTRY() \
    (*(LFP_ARCH_ADAPTER_SOCKET_T*)LFP_GET_CLASS_ENTRY(socket))
#define LFP_ADAPTER_SOCKET_INIT(FUNC) \
    LFP_ADAPTER_INIT(LFP_GET_SOCKET_ENTRY(), FUNC)

/* the definition of pthread cluster */
LFP_ARCH_ADAPTER3(LFP_GET_SOCKET_ENTRY(), socket_create, LFP_INT32, LFP_INT32,
                  LFP_INT32, LFP_INT32);
LFP_ARCH_ADAPTER3(LFP_GET_SOCKET_ENTRY(), socket_bind, LFP_INT32, LFP_INT32,
                  LFP_CONST LFP_SOCK_ADDR_T*, LFP_SOCKLEN_T);
LFP_ARCH_ADAPTER2(LFP_GET_SOCKET_ENTRY(), socket_listen, LFP_INT32, LFP_INT32,
                  LFP_INT32);
LFP_ARCH_ADAPTER3(LFP_GET_SOCKET_ENTRY(), socket_accept, LFP_INT32, LFP_INT32,
                  LFP_SOCK_ADDR_T*, LFP_SOCKLEN_T*);
LFP_ARCH_ADAPTER3(LFP_GET_SOCKET_ENTRY(), socket_connect, LFP_INT32, LFP_INT32,
                  LFP_CONST LFP_SOCK_ADDR_T*, LFP_SOCKLEN_T);
LFP_ARCH_ADAPTER1(LFP_GET_SOCKET_ENTRY(), socket_close, LFP_INT32, LFP_INT32);
LFP_ARCH_ADAPTER3(LFP_GET_SOCKET_ENTRY(), socket_write, LFP_SSIZE_T, LFP_INT32,
                  LFP_CONST LFP_VOID*, LFP_SIZE_T);
LFP_ARCH_ADAPTER2(LFP_GET_SOCKET_ENTRY(), socket_fcntl, LFP_INT32, LFP_INT32,
                  LFP_INT32);
LFP_ARCH_ADAPTER4(LFP_GET_SOCKET_ENTRY(), socket_send, LFP_SSIZE_T, LFP_INT32,
                  LFP_CONST LFP_VOID*, LFP_SIZE_T, LFP_INT32);
LFP_ARCH_ADAPTER6(LFP_GET_SOCKET_ENTRY(), socket_sendto, LFP_SSIZE_T, LFP_INT32,
                  LFP_CONST LFP_VOID*, LFP_SIZE_T, LFP_INT32,
                  LFP_CONST LFP_SOCK_ADDR_T*, LFP_SOCKLEN_T);
LFP_ARCH_ADAPTER3(LFP_GET_SOCKET_ENTRY(), socket_sendmsg, LFP_SSIZE_T,
                  LFP_INT32, LFP_CONST LFP_MSGHDR_T*, LFP_INT32);
LFP_ARCH_ADAPTER3(LFP_GET_SOCKET_ENTRY(), socket_read, LFP_SSIZE_T, LFP_INT32,
                  LFP_VOID*, LFP_SIZE_T);
LFP_ARCH_ADAPTER4(LFP_GET_SOCKET_ENTRY(), socket_recv, LFP_SSIZE_T, LFP_INT32,
                  LFP_VOID*, LFP_SIZE_T, LFP_INT32);
LFP_ARCH_ADAPTER6(LFP_GET_SOCKET_ENTRY(), socket_recvfrom, LFP_SSIZE_T,
                  LFP_INT32, LFP_VOID*, LFP_SIZE_T, LFP_INT32, LFP_SOCK_ADDR_T*,
                  LFP_SOCKLEN_T*);
LFP_ARCH_ADAPTER3(LFP_GET_SOCKET_ENTRY(), socket_recvmsg, LFP_SSIZE_T,
                  LFP_INT32, LFP_MSGHDR_T*, LFP_INT32);

/*@fn		  LFP_INT32 lfp_arch_adapter_socket_register(LFP_VOID)
 * @brief 	  the adapter layer register -- socket cluster register
 * @param[in]  LFP_NULL
 * @param[out] LFP_NULL
 * @return	  LFP_OK
 */
LFP_INT32 lfp_arch_adapter_socket_register(LFP_VOID) {
    LFP_ADAPTER_SOCKET_INIT(socket_create);
    LFP_ADAPTER_SOCKET_INIT(socket_bind);
    LFP_ADAPTER_SOCKET_INIT(socket_listen);
    LFP_ADAPTER_SOCKET_INIT(socket_accept);
    LFP_ADAPTER_SOCKET_INIT(socket_connect);
    LFP_ADAPTER_SOCKET_INIT(socket_close);
    LFP_ADAPTER_SOCKET_INIT(socket_write);
    LFP_ADAPTER_SOCKET_INIT(socket_fcntl);
    LFP_ADAPTER_SOCKET_INIT(socket_send);
    LFP_ADAPTER_SOCKET_INIT(socket_sendto);
    LFP_ADAPTER_SOCKET_INIT(socket_read);
    LFP_ADAPTER_SOCKET_INIT(socket_recv);
    LFP_ADAPTER_SOCKET_INIT(socket_recvfrom);
    LFP_ADAPTER_SOCKET_INIT(socket_recvmsg);
    return LFP_OK;
}
