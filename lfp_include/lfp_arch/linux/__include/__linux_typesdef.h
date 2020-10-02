/***************************************************************************************
File name: linux_typesdef.h
Description: redefine the types on linux system, the header file in "include" should quote
             this header file directly.
Author: wytaitaislee
Version: V1.0.0
Date: 2020-06-06
History: 1. create file. -- 2020-06-06
****************************************************************************************/

#ifndef __LINUX_TYPESDEF_H__
#define __LINUX_TYPESDEF_H__

#include "lfp_util.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

typedef size_t				LFP_SIZE_T;
typedef ssize_t				LFP_SSIZE_T;
typedef FILE				LFP_FILE;
typedef off_t               LFP_OFF_T;

#endif	/*end of __LINUX_TYPESDEF_H__ */