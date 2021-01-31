/***************************************************************************************
File name: linux.h
Description: the header file management about linux system, this header file 
             can only be referenced by the arch layer.
Author: wytaitaislee
Date: 2020-03-29
History: 1. create file. -- 2020-03-29
****************************************************************************************/

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