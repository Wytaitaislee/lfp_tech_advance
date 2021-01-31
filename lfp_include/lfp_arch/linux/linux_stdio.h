/***************************************************************************************
File name: linux_stdio.h
Description: the standard io management on linux system.
Author: wytaitaislee
Date: 2020-06-07
History: 1. create file. -- 2020-06-07
****************************************************************************************/

#ifndef __LINUX_STDIOIO_H__
#define __LINUX_STDIOIO_H__

#include "linux/__include/__linux_typesdef.h"

#define LFP_STDIO_CRIT(...)   \
	LFP_UTIL_BASE(UTIL_LEVEL_CRIT, UTIL_MODULE_LINUX, MASK_STDIO, __VA_ARGS__) 
#define LFP_STDIO_ERR(...)   \
	LFP_UTIL_BASE(UTIL_LEVEL_ERR, UTIL_MODULE_LINUX, MASK_STDIO, __VA_ARGS__) 
#define LFP_STDIO_INFO(...)   \
	LFP_UTIL_BASE(UTIL_LEVEL_INFO, UTIL_MODULE_LINUX, MASK_STDIO, __VA_ARGS__)

#endif	/*end of __LINUX_FILEIO_H__ */