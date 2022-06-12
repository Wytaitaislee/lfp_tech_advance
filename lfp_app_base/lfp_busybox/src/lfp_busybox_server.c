#include <errno.h>
#include "lfp_base.h"
#include "lfp_arch_adapter/lfp_arch_adapter.h"
#include "lfp_socket/lfp_socket.h"

#define LFP_BUSYBOX_UNIX_PATH "/var/busybox.unixsocket"
#define LFP_BUSYBOX_UNIX_Q (5)

LFP_INT32 lfp_busybox_server(LFP_VOID){
    LFP_INT32 iSockServer = -1;
    LFP_INT32 iAcceptSock = -1;
    LFP_INT32 iLen = 0;
    LFP_INT8 szbuf[1024] = {0};
    LFP_SOCK_ADDRUN_T struSockServer, struSockClient;

    LFP_BUFF_BEZERO(&struSockServer, sizeof(&struSockServer));

    iSockServer = lfp_socket_create(LFP_AF_UNIX, LFP_SOCK_STREAM, LFP_IPPROTO_TCP);
    LFP_RET_IF(LFP_OK != iSockServer, LFP_ERR);
    unlink(LFP_BUSYBOX_UNIX_PATH);
    
    struSockServer.sun_family = LFP_AF_UNIX;
    strcpy(&struSockServer.sun_path, LFP_BUSYBOX_UNIX_PATH);
    if(LFP_OK != lfp_socket_bind(iSockServer, (LFP_SOCK_ADDR_T*)&struSockServer, sizeof(struSockServer))){
        LFP_SOCKET_SERVER_ERR("unix socket binding failed\n");
        return LFP_ERR;
    }

    if (LFP_OK != lfp_socket_listen(iSockServer, LFP_SOCKET_MAX_LISTEN)) {
        LFP_SOCKET_SERVER_ERR("socket listen failed\n");
        return LFP_ERR;
    }

    iLen = sizeof(struSockClient);
    while(1)
    {
        iAcceptSock = lfp_socket_accept(iSockServer, (LFP_SOCK_ADDR_T*)&struSockClient, &iLen);
        if(-1 == iAcceptSock)
        {
            LFP_SOCKET_SERVER_ERR("socket accept failed, iAcceptSock[%d], errno[%d][%s]\n", iAcceptSock, errno, strerror(errno));
            LFP_SAFE_CLOSE_SOCKET(iAcceptSock);
            continue;
        }

        LFP_BUFF_BEZERO(szbuf, sizeof(szbuf));
		if(LFP_OK != lfp_socket_recv(iAcceptSock, szbuf, sizeof(szbuf)) == 0){
            LFP_SOCKET_SERVER_ERR("socket accept failed, iAcceptSock[%d], errno[%d][%s]\n", iAcceptSock, errno, strerror(errno));
            LFP_SAFE_CLOSE_SOCKET(iAcceptSock);
            continue;
        }
		printf("Receive: %s", szbuf);
        LFP_SAFE_CLOSE_SOCKET(iAcceptSock);
    }

	LFP_SAFE_CLOSE_SOCKET(iSockServer);
	unlink(LFP_BUSYBOX_UNIX_PATH);
    return 0;
}