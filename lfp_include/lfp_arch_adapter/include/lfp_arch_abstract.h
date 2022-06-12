/***
 * @FilePath: lfp_arch_abstract.h
 * @Description: System adaptation layer. Abstract different underlying
 * implementations.
 * @Author: wytaitaislee
 * @Date: 2021-08-27 23:29:52
 * @LastEditTime: 2022-03-05 21:58:57
 * @LastEditors: wytaitaislee
 * @Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#ifndef __LFP_ARCH_ABSTRACT_H__
#define __LFP_ARCH_ABSTRACT_H__

#ifdef __cplusplus
extern "C" {
#endif

#define ARCH_NAME LFP_
#define __OS_NAME_UPPER LINUX_
#define __OS_NAME_LOWER linux_
#include "lfp_base.h"
/* X86, 32. */
#if defined(linux) || defined(unix) || defined(__unix__) || defined(__linux__)
#include "linux/linux.h"
#define LFP_AF_UNIX (LINUX_AF_UNIX)
#define LFP_AF_INET (LINUX_AF_INET)
#define LFP_SOCK_STREAM (LINUX_SOCK_STREAM)
#define LFP_IPPROTO_TCP (LINUX_IPPROTO_TCP)
#define LFP_PTHREAD_ESRCH (LINUX_PTHREAD_ESRCH)
#define LFP_PTHREAD_CREATE_DETACHED (LINUX_PTHREAD_CREATE_DETACHED)
/* win32, wins64 */
#elif defined(__WIN32__) || defined(__WIN64__)
#include "windows/windows.h"
#define LFP_AF_INET (WINDOWS_AF_INET)
#define LFP_SOCK_STREAM (WINDOWS_SOCK_STREAM)
#define LFP_IPPROTO_TCP (WINDOWS_IPPROTO_TCP)
#define LFP_PTHREAD_ESRCH (WINDOWS_PTHREAD_ESRCH)
#else
/*someother platforms */
#endif

/* os arch typesdef to lfp arch typesdef adapter macros definition */
#define __DEFINE_ARCH_TYPESDEF_ADAPTER(os, arch, item) \
    typedef os##item arch##item
#define __DEFINE_ARCH_TYPESDEF_ADAPTER_CONVERT(os, arch, item) \
    __DEFINE_ARCH_TYPESDEF_ADAPTER(os, arch, item)
#define DEFINE_ARCH_TYPESDEF_ADAPTER(BASE_NAME) \
    __DEFINE_ARCH_TYPESDEF_ADAPTER_CONVERT(__OS_NAME_UPPER, ARCH_NAME, BASE_NAME)

/* os arch function to lfp arch function adapter macros definition */
#define __DEFINE_ARCH_ADAPTER(osname, basename) (osname##basename)
#define __DEFINE_ARCH_ADAPTER_CONVERT(os, item) __DEFINE_ARCH_ADAPTER(os, item)
#define DEFINE_ARCH_ADAPTER(BASE_FUNC_NAME) \
    __DEFINE_ARCH_ADAPTER_CONVERT(__OS_NAME_LOWER, BASE_FUNC_NAME)

/* socket relevant typesdef */
DEFINE_ARCH_TYPESDEF_ADAPTER(SOCK_ADDR_T);
DEFINE_ARCH_TYPESDEF_ADAPTER(SOCK_ADDRIN_T);
DEFINE_ARCH_TYPESDEF_ADAPTER(SOCK_ADDRUN_T);
DEFINE_ARCH_TYPESDEF_ADAPTER(SOCKLEN_T);
DEFINE_ARCH_TYPESDEF_ADAPTER(MSGHDR_T);
DEFINE_ARCH_TYPESDEF_ADAPTER(SOCK);

/* mutex relevant typesdef */
DEFINE_ARCH_TYPESDEF_ADAPTER(MUTEX_T);
DEFINE_ARCH_TYPESDEF_ADAPTER(MUTEX_ATTR_T);

/* pthread relevant typesdef */
DEFINE_ARCH_TYPESDEF_ADAPTER(PTHREAD_HANDLE_T);
DEFINE_ARCH_TYPESDEF_ADAPTER(PTHREAD_ATTR_T);

/* semaphore relevant typesdef */
DEFINE_ARCH_TYPESDEF_ADAPTER(SEM_T);

/* comm datatypes typesdef */
DEFINE_ARCH_TYPESDEF_ADAPTER(OFF_T);
DEFINE_ARCH_TYPESDEF_ADAPTER(SIZE_T);
DEFINE_ARCH_TYPESDEF_ADAPTER(SSIZE_T);
DEFINE_ARCH_TYPESDEF_ADAPTER(FILE);

/* Thread function cluster */
typedef struct lfp_arch_adapter_pthread_t {
    /* data */
    LFP_INT32(*pthread_create)(LFP_PTHREAD_HANDLE_T *pThreadHandle, LFP_INT32 iPrority,
                            LFP_UINT32 uiStackSize, LFP_VOID *pStartTask, LFP_VOID *pParams);
    LFP_INT32(*pthread_cancel)(LFP_PTHREAD_HANDLE_T hThreadHandle);
    LFP_INT32(*pthread_kill)(LFP_PTHREAD_HANDLE_T hThreadHandle, LFP_INT32 iSig);
    LFP_INT32(*pthread_attr_init)(LFP_PTHREAD_ATTR_T *);
    LFP_INT32(*pthread_attr_setdetachstate)(LFP_PTHREAD_ATTR_T *, LFP_INT32);
    LFP_INT32(*pthread_attr_getdetachstate)(LFP_PTHREAD_ATTR_T *, LFP_INT32 *);
    LFP_INT32(*pthread_attr_destroy)(LFP_PTHREAD_ATTR_T *);
} LFP_ARCH_ADAPTER_PTHREAD_T;

/* Mutex function cluster */
typedef struct lfp_arch_adapter_mutex_t {
    LFP_INT32(*mutex_init)(LFP_MUTEX_T *mutex, LFP_MUTEX_ATTR_T *pAttr);
    LFP_INT32(*mutex_lock)(LFP_MUTEX_T *mutex);
    LFP_INT32(*mutex_unlock)(LFP_MUTEX_T *mutex);
    LFP_INT32(*mutex_destroy)(LFP_MUTEX_T *mutex);
} LFP_ARCH_ADAPTER_MUTEX_T;

/* Semaphore function cluster */
typedef struct lfp_arch_adapter_semaphore_t {
    LFP_INT32(*semaphore_init)(LFP_SEM_T *sem, LFP_INT32 iShared, LFP_UINT32 uiInitVal);
    LFP_INT32(*semaphore_wait)(LFP_SEM_T *sem, LFP_INT32 iWaitTime);
    LFP_INT32(*semaphore_post)(LFP_SEM_T *sem);
    LFP_INT32(*semaphore_destroy)(LFP_SEM_T *sem);
} LFP_ARCH_ADAPTER_SEMAPHORE_T;

/* Lock function cluster */
typedef struct lfp_arch_adapter_lock_t {
    LFP_INT32(*lock_create)();
    LFP_INT32(*lock)();
    LFP_INT32(*unlock)();
} LFP_ARCH_ADAPTER_LOCK_T;

/* file io function cluster */
typedef struct lfp_arch_adapter_fileio_t {
    LFP_INT32(*fileio_open)(LFP_CONST LFP_INT8 *pPath, LFP_INT32 iFlags, LFP_INT32 iMode);
    LFP_OFF_T(*fileio_seek)(LFP_INT32 iFd, LFP_OFF_T iOffset, LFP_INT32 iWhence);
    LFP_INT32(*fileio_fcntl)(LFP_INT32 iFd, LFP_INT32 iStyle);
    LFP_INT32(*fileio_read)(LFP_INT32 iFd, LFP_VOID *pBuf, LFP_SIZE_T bytes);
    LFP_INT32(*fileio_write)(LFP_INT32 iFd, LFP_CONST LFP_VOID *pBuf, LFP_SIZE_T bytes);
    LFP_INT32(*fileio_close)(LFP_INT32 iFd);
} LFP_ARCH_ADAPTER_FILEIO_T;

/* standard io function cluster */
typedef struct lfp_arch_adapter_stdio_t {
    LFP_FILE *(*stdio_open)(LFP_CONST LFP_INT8 *LFP_RESTRICT pPath,
                            LFP_CONST LFP_INT8 *LFP_RESTRICT pMode);
    LFP_INT32(*stdio_seek)(LFP_FILE *pFp, LFP_LONG iOffset, LFP_INT32 iWhence);
    LFP_SIZE_T(*stdio_read)(LFP_VOID *LFP_RESTRICT pBuf, LFP_SIZE_T size, LFP_SIZE_T nobjs,
                            LFP_FILE *LFP_RESTRICT pFp);
    LFP_SIZE_T(*stdio_write)(LFP_CONST LFP_VOID *LFP_RESTRICT pBuf, LFP_SIZE_T size, LFP_SIZE_T nobjs,
                            LFP_FILE *LFP_RESTRICT pFp);
    LFP_INT32(*stdio_close)(LFP_FILE *pFp);
} LFP_ARCH_ADAPTER_STDIO_T;

/* time function cluster */
typedef struct lfp_arch_adapter_time_t {
    LFP_INT32(*sleep_ms)(LFP_UINT32 uiSleepMsSeconds);
    LFP_INT32(*sleep_s)(LFP_UINT32 uiSleepSeconds);
    LFP_TIME_T(*get_time)(LFP_TIME_T *ptTime);
} LFP_ARCH_ADAPTER_TIME_T;

typedef struct lfp_arch_adapter_socket_t {
    LFP_INT32(*socket_create)(LFP_INT32, LFP_INT32, LFP_INT32);
    LFP_INT32(*socket_bind)(LFP_INT32, LFP_CONST LFP_SOCK_ADDR_T *, LFP_SOCKLEN_T);
    LFP_INT32(*socket_listen)(LFP_INT32, LFP_INT32);
    LFP_INT32(*socket_accept)(LFP_INT32, LFP_SOCK_ADDR_T *, LFP_SOCKLEN_T *);
    LFP_INT32(*socket_connect)(LFP_INT32, LFP_CONST LFP_SOCK_ADDR_T *, LFP_SOCKLEN_T);
    LFP_INT32(*socket_close)(LFP_INT32);
    LFP_SSIZE_T(*socket_write)(LFP_INT32, LFP_CONST LFP_VOID *, LFP_SIZE_T);
    LFP_INT32(*socket_fcntl)(LFP_INT32, LFP_INT32);
    LFP_SSIZE_T(*socket_send)(LFP_INT32, LFP_CONST LFP_VOID *, LFP_SIZE_T, LFP_INT32);
    LFP_SSIZE_T(*socket_sendto)(LFP_INT32, LFP_CONST LFP_VOID *, LFP_SIZE_T, LFP_INT32,
                                LFP_CONST LFP_SOCK_ADDR_T *, LFP_SOCKLEN_T);
    LFP_SSIZE_T(*socket_sendmsg)(LFP_INT32, LFP_CONST LFP_MSGHDR_T *, LFP_INT32);
    LFP_SSIZE_T(*socket_read)(LFP_INT32, LFP_VOID *, LFP_SIZE_T);
    LFP_SSIZE_T(*socket_recv)(LFP_INT32, LFP_VOID *, LFP_SIZE_T, LFP_INT32);
    LFP_SSIZE_T(*socket_recvfrom)(LFP_INT32, LFP_VOID *, LFP_SIZE_T, LFP_INT32, LFP_SOCK_ADDR_T *,
                                LFP_SOCKLEN_T *);
    LFP_SSIZE_T(*socket_recvmsg)(LFP_INT32, LFP_MSGHDR_T *, LFP_INT32);
} LFP_ARCH_ADAPTER_SOCKET_T;

/* The abstruct of the os function cluster */
typedef struct lfp_arch_adapter_os_t {
    /* data */
    LFP_ARCH_ADAPTER_PTHREAD_T struArchAdapterPthread;
    LFP_ARCH_ADAPTER_MUTEX_T struArchAdapterMutex;
    LFP_ARCH_ADAPTER_SEMAPHORE_T struArchAdapterSem;
    LFP_ARCH_ADAPTER_LOCK_T struArchAdapterLock;
    LFP_ARCH_ADAPTER_FILEIO_T struArchAdapterFileio;
    LFP_ARCH_ADAPTER_STDIO_T struArchAdapterStdio;
    LFP_ARCH_ADAPTER_SOCKET_T struArchAdapterSocket;
    LFP_ARCH_ADAPTER_TIME_T struArchAdapterTime;
} LFP_ARCH_ADAPTER_OS_T;

#ifdef __cplusplus
}
#endif

#endif /*end of __LFP_ARCH_ABSTRACT_H__ */
