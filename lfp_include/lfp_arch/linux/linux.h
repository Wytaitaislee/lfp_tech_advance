/*
 * @fileName: linux.h
 * @Description: the header file management about linux system, this header file 
                 can only be referenced by the arch layer.
 * @Author: wytaitaislee
 * @Date: 2020-09-26 18:43:32
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-04-04 16:06:46
*/

#ifndef __LINUX_OS_H__
#define __LINUX_OS_H__

#include "linux/linux_pthread.h"
#include "linux/linux_mutex.h"
#include "linux/linux_semaphore.h"
#include "linux/linux_socket.h"
#include "linux/linux_fileio.h"
#include "linux/linux_stdio.h"
#include "linux/linux_time.h"

#endif	/*end of __LINUX_OS_H__ */