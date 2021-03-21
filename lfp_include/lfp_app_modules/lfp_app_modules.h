/************************************************************************************
 * @fileName: lfp_app_modules.h
 * @Description: only resigster main entrance of modules
 * @Author: wytaitaislee
 * @Date: 2021-01-31 18:16:57
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-03-21 19:53:58
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
/*@fn		  LFP_INT32 lfp_socket_module_init(LFP_VOID)
* @brief 	  socket communication main entrance
* @param[in]  LFP_VOID
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_socket_module_init(LFP_VOID);
#endif

#endif /* end of __LFP_APP_MODULES_H__ */