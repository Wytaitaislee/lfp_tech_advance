/***************************************************************************************
File name: linux_io.h
Description: the file io management on linux system.
Author: wytaitaislee
Date: 2020-05-30
History: 1. create file. -- 2020-05-30
****************************************************************************************/

#ifndef __LINUX_FILEIO_H__
#define __LINUX_FILEIO_H__

#include "lfp_base.h"

#define LFP_FILEIO_CRIT(...)   \
	LFP_UTIL_BASE(UTIL_LEVEL_CRIT, UTIL_MODULE_LINUX, MASK_FILEIO, __VA_ARGS__) 
#define LFP_FILEIO_ERR(...)   \
	LFP_UTIL_BASE(UTIL_LEVEL_ERR, UTIL_MODULE_LINUX, MASK_FILEIO, __VA_ARGS__) 
#define LFP_FILEIO_INFO(...)   \
	LFP_UTIL_BASE(UTIL_LEVEL_INFO, UTIL_MODULE_LINUX, MASK_FILEIO, __VA_ARGS__)

/*@fn		  LFP_INT32 linux_fileio_fcntl(LFP_INT32 iFd, LFP_INT32 iStyle)
* @brief 	  change the opned file character O_BLOCK / O_NONBLOCK, ect.
* @param[in]  LFP_INT32 iFd - The specified file descriptor
* @param[in]  LFP_INT32 iStyle - the character to be set
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_fileio_fcntl(LFP_INT32 iFd, LFP_INT32 iStyle);
#endif	/*end of __LINUX_FILEIO_H__ */