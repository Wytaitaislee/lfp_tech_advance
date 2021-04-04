/*
 * @fileName: lfp_arch_adapter_fileio.h
 * @Description: System adaptation layer, matching different arch.
 * @Author: wytaitaislee
 * @Date: 2020-08-16 16:05:58
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-04-04 16:07:22
*/

#ifndef __LFP_ARCH_ADAPTER_FILEIO_H__
#define __LFP_ARCH_ADAPTER_FILEIO_H__

#include "lfp_base.h"

/*@fn		  LFP_INT32 lfp_fileio_fcntl(LFP_INT32 iFd, LFP_INT32 iStyle)
* @brief 	  change the opned file character O_BLOCK / O_NONBLOCK, ect.
* @param[in]  LFP_INT32 iFd - The specified file descriptor
* @param[in]  LFP_INT32 iStyle - the character to be set
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_fileio_fcntl(LFP_INT32 iFd, LFP_INT32 iStyle);

/*@fn		  LFP_INT32 lfp_arch_adapter_fileio_register(LFP_VOID)
* @brief 	  the adapter layer register -- fileio cluster register
* @param[in]  LFP_NULL
* @param[out] LFP_NULL
* @return	  LFP_OK
*/
LFP_INT32 lfp_arch_adapter_fileio_register(LFP_VOID);

#endif	/*end of __LFP_ARCH_ADAPTER_FILEIO_H__ */