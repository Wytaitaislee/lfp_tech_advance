/*
 * @FilePath: lfp_app_init.c
 * @Description: Application registration.
 * @Author: wytaitaislee
 * @Date: 2021-08-27 23:29:52
 * @LastEditTime: 2022-03-06 17:38:41
 * @LastEditors: wytaitaislee
 * Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#include "lfp_app_init.h"

#include "lfp_app_busybox/lfp_app_busybox.h"
#include "lfp_app_libs/lfp_app_libs.h"
#include "lfp_app_unity_test/lfp_app_unity_test.h"

LFP_INT32 lfp_app_unity_test_init(LFP_VOID);

LFP_CONST LFP_CODE LFP_COMPONENTS_REGISTER_T g_lfpAppRegister[] = {
    LFP_MODLUE_REGISTER(lfp_app_busybox_init),
    LFP_MODLUE_REGISTER(lfp_app_libs_init),
    LFP_MODLUE_REGISTER(lfp_app_unity_test_init),
};

/**
 * @fn: LFP_INT32 lfp_app_init(LFP_VOID)
 * @breif: Application registration
 * @param[in] LFP_VOID
 * @param[out] NULL
 * @return {*} LFP_OK
 */
LFP_INT32 lfp_app_init(LFP_VOID) {
  LFP_UINT32 uiModules = 0;

  for (uiModules = 0; uiModules < LFP_NELEMENTS(g_lfpAppRegister);
       uiModules++) {
    if (LFP_NULL != g_lfpAppRegister[uiModules].lfp_components_register) {
      g_lfpAppRegister[uiModules].lfp_components_register();
    }
  }
  return LFP_OK;
}

/**
 * @fn: LFP_INT32 lfp_app_test_init(LFP_VOID)
 * @breif: Application registration
 * @param[in] LFP_VOID
 * @param[out] NULL
 * @return {*} LFP_OK
 */
LFP_INT32 lfp_app_test_init(LFP_VOID) { return LFP_OK; }
