/*
 * @fileName: linux_fileio.c
 * @Description: the file io management on linux system.
 * @Author: wytaitaislee
 * @Date: 2020-08-16 16:05:57
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-04-04 16:00:21
*/

#include "linux_fileio.h"
#include "linux_typesdef.h"
#include <fcntl.h>

/*@fn		  LFP_INT32 linux_fileio_fcntl(LFP_INT32 iFd, LFP_INT32 iStyle)
* @brief 	  change the opned file character O_BLOCK / O_NONBLOCK, ect.
* @param[in]  LFP_INT32 iFd - The specified file descriptor
* @param[in]  LFP_INT32 iStyle - the character to be set
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 linux_fileio_fcntl(LFP_INT32 iFd, LFP_INT32 iStyle)
{
	LFP_INT32 iFlags = 0;

	LFP_ASSERT_ERR_RET(iFd >= 0);
	iFlags = fcntl(iFd, F_GETFL, 0); 

	return fcntl(iFd, F_SETFL, iFlags | iStyle);
}


