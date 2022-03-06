/***
 * @FilePath     : lfp_base.h
 * @Description  : The underlying basic data structure is exposed to the upper
 layer through this header file
 * @Author       : wytaitaislee
 * @Date         : 2021-08-27 23:29:52
 * @LastEditTime : 2022-03-05 19:45:16
 * @LastEditors  : wytaitaislee
 * @Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#ifndef __LFP_BASE_H__
#define __LFP_BASE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "__include/lfp_assert.h"
#include "__include/lfp_macros.h"
#include "__include/lfp_typesdef.h"
#include "lfp_log/lfp_log.h"

#define LFP_MODLUE_REGISTER(func) \
  { #func, func }

typedef struct lfp_components_register_t {
  LFP_CONST LFP_INT8 *pModuleName;
  LFP_INT32 (*lfp_components_register)(LFP_VOID);
} LFP_COMPONENTS_REGISTER_T;

#ifdef __cplusplus
}
#endif

#endif /* end of __LFP_BASE_H__ */