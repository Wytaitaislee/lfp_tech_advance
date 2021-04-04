/*
 * @fileName: lfp_base.h
 * @Description: The underlying basic data structure is exposed to the upper layer through 
                 this header file
 * @Author: wytaitaislee
 * @Date: 2020-11-07 22:09:34
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-04-04 17:20:42
*/

#ifndef __LFP_BASE_H__
#define __LFP_BASE_H__

#include "lfp_base_macros.h"
#include "lfp_base_typesdef.h"
#include "lfp_util_log.h"

#define LFP_MODLUE_REGISTER(func)	{#func, func}
typedef struct lfp_components_register_t
{
	LFP_CONST LFP_INT8* pModuleName;
	LFP_INT32 (*lfp_components_register)(LFP_VOID);
}LFP_COMPONENTS_REGISTER_T;

#endif /* end of __LFP_BASE_H__ */