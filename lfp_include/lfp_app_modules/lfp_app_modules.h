/************************************************************************************
File name: lfp_app_modules.h
Description: only resigster main entrance of modules
Author: wytaitaislee
Date: 2019-11-17
History: 1. create file. -- 2019-11-17
************************************************************************************/

#ifndef __LFP_APP_MODULES_H__
#define __LFP_APP_MODULES_H__

#ifdef LFP_SINGLE_LIST_MODULE
/*@fn		  LFP_INT32 lfp_single_list_module_test_init(LFP_VOID)
* @brief 	  the single list test module main entrance.
* @param[in]  LFP_VOID
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_single_list_module_test_init(LFP_VOID);
#endif

#ifdef LFP_DOUBLE_LIST_MODULE
/*@fn		  LFP_INT32 lfp_double_list_module_test_init(LFP_VOID)
* @brief 	  the entrance of the double list module.
* @param[in]  LFP_VOID
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_double_list_module_test_init(LFP_VOID);
#endif

#ifdef LFP_SOCKET_APP
#include "lfp_socket_app/lfp_socket_app.h"
#endif

#endif /* end of __LFP_APP_MODULES_H__ */