/*
 * @fileName: lfp_unity_test_socket.h
 * @Description: Socket unit test module
 * @Author: wytaitaislee
 * @Date: 2021-01-31 18:16:57
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-04-05 11:18:26
*/

#ifndef __LFP_UNITY_TEST_SOCKET_H__
#define __LFP_UNITY_TEST_SOCKET_H__

#ifdef LFP_SOCKET_APP
/*@fn		  LFP_INT32 lfp_unity_test_socket_init(LFP_VOID)
* @brief 	  socket communication main entrance(for test).
* @param[in]  LFP_VOID
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_unity_test_socket_init(LFP_VOID);
#endif

#endif /* end of __LFP_UNITY_TEST_SOCKET_H__ */