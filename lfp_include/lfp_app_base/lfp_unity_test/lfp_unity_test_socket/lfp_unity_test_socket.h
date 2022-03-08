/***
 * @FilePath: lfp_unity_test_socket.h
 * @Description: Socket unit test module.
 * @Author: wytaitaislee
 * @Date: 2021-08-27 23:29:52
 * @LastEditTime: 2022-03-05 21:23:17
 * @LastEditors: wytaitaislee
 * @Copyright 2022 wytaitaislee, All Rights Reserved.
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