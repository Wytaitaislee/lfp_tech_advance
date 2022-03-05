/***
 * @FilePath     : lfp_macros.h
 * @Description  : Description for this file.
 * @Author       : wytaitaislee
 * @Date         : 2021-08-27 23:29:52
 * @LastEditTime : 2022-03-05 17:24:56
 * @LastEditors  : wytaitaislee
 * @Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#ifndef __LFP_MACROS_H__
#define __LFP_MACROS_H__

#include <stdlib.h>
#include <string.h>

#include "lfp_base.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LFP_MAX(x, y) ((x > y) ? (x) : (y))
#define LFP_MIN(x, y) ((x > y) ? (y) : (x))
#define LFP_BUFF_BEZERO(pStr, len) (memset(pStr, 0, len))
#define LFP_NELEMENTS(x) (sizeof(x) / sizeof(*(x)))
#define LFP_MALLOC(size) (malloc(size))

/* assert safe free memory */
#define LFP_SAFE_FREE(p)       \
  do {                         \
    if (p) {                   \
      free(p);                 \
      p = (LFP_VOID*)LFP_NULL; \
    }                          \
  } while (0);

/* assert safe close file */
#define LFP_SAFE_CLOSE(p)      \
  do {                         \
    if (p) {                   \
      fclose(p);               \
      p = (LFP_VOID*)LFP_NULL; \
    }                          \
  } while (0);

/* assert safe close socket connection */
#define LFP_SAFE_CLOSE_SOCKET(p) \
  do {                           \
    if (p) {                     \
      close(p);                  \
      p = -1;                    \
    }                            \
  } while (0);

/* modules register sign. */
#define LFP_MODULES_REGISTER_SIGN(util, sign) \
  do {                                        \
    util("module %s !\n", sign);              \
  } while (0);

#ifdef __cplusplus
}
#endif

#endif /* end of __LFP_MACROS_H__ */