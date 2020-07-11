/************************************************************************************
File name: lfp_out_modules.h
Description: Application business module management layer to manage different 
             application modules and achieve centralized configuration. 
             Only can be invoked by the upper layer.
Author: wytaitaislee
Version: V1.0.0
Date: 2019-11-17
History: 1. create file. -- 2019-11-17
************************************************************************************/

#ifndef __LFP_MODULES_H__
#define __LFP_MODULES_H__

#include "../__include/lfp_util.h"
#include "../lfp_arch_adapter/lfp_arch_adapter.h"
#ifdef LFP_SINGLE_LIST_MODULE
#include "lfp_single_list/lfp_single_list.h"
#endif

#ifdef LFP_DOUBLE_LIST_MODULE
#include "lfp_double_list/lfp_double_list.h"
#endif

#ifdef LFP_SOCKET_APP
#include "lfp_socket_app/lfp_socket_app.h"
#endif

#endif /* end of __LFP_MODULES_H__ */