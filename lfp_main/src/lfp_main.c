/***************************************************************************************
 * @fileName: lfp_main.c
 * @Description: lee's firmware platform main entrance.
 * @Author: wytaitaislee
 * @Date: 2020-08-16 16:05:58
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-03-21 20:07:53
****************************************************************************************/

#include "lfp_base.h"
#include "lfp_arch_adapter.h"
#include "lfp_app_modules.h"
#include "lfp_app_busybox.h"

#define LFP_MODLUE_REGISTER(func)	{#func, func}
typedef struct lfp_components_register_t
{
	LFP_CONST LFP_INT8* pModuleName;
	LFP_INT32 (*lfp_components_register)(LFP_VOID);
}LFP_COMPONENTS_REGISTER_T;

LFP_STATIC LFP_CONST LFP_CODE LFP_COMPONENTS_REGISTER_T g_ComponentsRegister[] = 
{
	LFP_MODLUE_REGISTER(lfp_util_module_init),
	LFP_MODLUE_REGISTER(lfp_arch_adapter_init),
	LFP_MODLUE_REGISTER(lfp_busybox_init),
#ifdef LFP_SOCKET_APP
	LFP_MODLUE_REGISTER(lfp_socket_module_init),
#endif
};

LFP_STATIC LFP_CONST LFP_CODE LFP_COMPONENTS_REGISTER_T g_ComponentsTestRegister[] = 
{
#ifdef LFP_SINGLE_LIST_MODULE
	LFP_MODLUE_REGISTER(lfp_single_list_module_test_init),
#endif
#ifdef LFP_DOUBLE_LIST_MODULE
	LFP_MODLUE_REGISTER(lfp_double_list_module_test_init),
#endif
};

LFP_STATIC LFP_INT32 lfp_wytaitai_main_entrance(LFP_VOID)
{
	LFP_UINT32 uiModules = 0;
	
	for(uiModules = 0; uiModules < LFP_NELEMENTS(g_ComponentsRegister); uiModules++)
	{
		if(LFP_NULL != g_ComponentsRegister[uiModules].lfp_components_register)
		{
			g_ComponentsRegister[uiModules].lfp_components_register();
		}
	}
	return LFP_OK;
}

LFP_STATIC LFP_INT32 lfp_wytaitai_test_entrance(LFP_VOID)
{
	LFP_UINT32 uiModules = 0;
	
	for(uiModules = 0; uiModules < LFP_NELEMENTS(g_ComponentsTestRegister); uiModules++)
	{
		if(LFP_NULL != g_ComponentsTestRegister[uiModules].lfp_components_register)
		{
			g_ComponentsTestRegister[uiModules].lfp_components_register();
		}
	}
	return LFP_OK;
}
/*@fn		  LFP_INT32 main(LFP_VOID)
* @brief 	  the main entrance of the project
* @param[in]  LFP_VOID
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 main(LFP_INT32 argc, LFP_INT8* args[])
{
	lfp_wytaitai_main_entrance();
	printf("entrance of main, argc = %d, args[0] = %s\n", argc, args[1]);
	if(0 != argc && LFP_NULL != args[1])
	{
		lfp_wytaitai_test_entrance();
	}
	return LFP_OK;
}
