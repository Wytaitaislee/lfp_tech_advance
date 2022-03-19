/*
 * @FilePath: linux_fileio.c
 * @Description: the file io management on linux system.
 * @Author: wytaitaislee
 * @Date: 2022-03-05 16:42:26
 * @LastEditTime: 2022-03-19 19:15:33
 * @LastEditors: wytaitaislee
 * Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#include "linux_fileio.h"

#include <fcntl.h>

#include "linux_typesdef.h"

/*@fn		  LFP_INT32 linux_fileio_fcntl(LFP_INT32 iFd, LFP_INT32 iStyle)
 * @brief 	  change the opned file character O_BLOCK / O_NONBLOCK, ect.
 * @param[in]  LFP_INT32 iFd - The specified file descriptor
 * @param[in]  LFP_INT32 iStyle - the character to be set
 * @param[out] LFP_NULL
 * @return	  LFP_OK / LFP_ERR
 */
LFP_INT32 linux_fileio_fcntl(LFP_INT32 iFd, LFP_INT32 iStyle) {
    LFP_INT32 iFlags = 0;

    LFP_RET_IF((iFd >= 0), LFP_ERR);
    iFlags = fcntl(iFd, F_GETFL, 0);

    return fcntl(iFd, F_SETFL, iFlags | iStyle);
}
