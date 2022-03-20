/***
 * @FilePath: linux_fileio.h
 * @Description: the file io management on linux system.
 * @Author: wytaitaislee
 * @Date: 2021-08-27 23:29:52
 * @LastEditTime: 2022-03-05 21:22:21
 * @LastEditors: wytaitaislee
 * @Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#ifndef __LINUX_FILEIO_H__
#define __LINUX_FILEIO_H__

#include "lfp_base.h"

#define LFP_FILEIO_CRIT(...) \
    LFP_LOG_BASE(LOG_LEVEL_CRIT, LOG_MODULE_LINUX, MASK_FILEIO, ##__VA_ARGS__)
#define LFP_FILEIO_ERR(...) \
    LFP_LOG_BASE(LOG_LEVEL_ERR, LOG_MODULE_LINUX, MASK_FILEIO, ##__VA_ARGS__)
#define LFP_FILEIO_INFO(...) \
    LFP_LOG_BASE(LOG_LEVEL_INFO, LOG_MODULE_LINUX, MASK_FILEIO, ##__VA_ARGS__)

/*@fn		  LFP_INT32 linux_fileio_fcntl(LFP_INT32 iFd, LFP_INT32 iStyle)
 * @brief 	  change the opned file character O_BLOCK / O_NONBLOCK, ect.
 * @param[in]  LFP_INT32 iFd - The specified file descriptor
 * @param[in]  LFP_INT32 iStyle - the character to be set
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 linux_fileio_fcntl(LFP_INT32 iFd, LFP_INT32 iStyle);
#endif /*end of __LINUX_FILEIO_H__ */