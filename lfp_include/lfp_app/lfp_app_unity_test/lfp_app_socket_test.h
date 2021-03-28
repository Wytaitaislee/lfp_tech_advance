/*
 * @fileName: lfp_app_socket_test.h
 * @Description: Socket unit test module
 * @Author: wytaitaislee
 * @Date: 2021-01-31 18:16:57
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-03-28 16:08:28
*/

#ifndef __LFP_APP_SOCKET_TEST_H__
#define __LFP_APP_SOCKET_TEST_H__

#ifdef LFP_SOCKET_APP
/*@fn		  LFP_INT32 lfp_socket_module_test_init(LFP_VOID)
* @brief 	  socket communication main entrance(for test).
* @param[in]  LFP_VOID
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_socket_module_test_init(LFP_VOID);
#endif

#endif /* end of __LFP_APP_SOCKET_TEST_H__ */