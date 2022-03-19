/***
 * @FilePath     : lfp_assert.h
 * @Description  : Description for this file.
 * @Author       : wytaitaislee
 * @Date         : 2022-03-05 17:07:30
 * @LastEditTime : 2022-03-05 17:23:54
 * @LastEditors  : wytaitaislee
 * @Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#ifndef __LFP_ASSERT_H__
#define __LFP_ASSERT_H__

#include <assert.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* basic assert output format */
#define __LFP_ASSERT_FORMAT(c)                                                     \
    do {                                                                           \
        printf("[%s][warn][%s][%s][%d] %s ,condition err!!\n", __TIME__, __FILE__, \
               __func__, __LINE__, #c);                                            \
    } while (0);

/* assert */
#define LFP_ASSERT(c)               \
    do {                            \
        if (!(c)) {                 \
            __LFP_ASSERT_FORMAT(c); \
            assert(c);              \
        }                           \
    } while (0);

/* assert return NULL */
#define LFP_RET_VOID_IF(c)          \
    do {                            \
        if (!(c)) {                 \
            __LFP_ASSERT_FORMAT(c); \
            return;                 \
        }                           \
    } while (0);

/* assert return if */
#define LFP_RET_IF(c, ret)          \
    do {                            \
        if (!(c)) {                 \
            __LFP_ASSERT_FORMAT(c); \
            return ret;             \
        }                           \
    } while (0);

#ifdef __cplusplus
}
#endif

#endif /* end of __LFP_ASSERT_H__ */