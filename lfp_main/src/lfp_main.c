/*
 * @fileName: lfp_main.c
 * @Description: lee's firmware platform main entrance.
 * @Author: wytaitaislee
 * @Date: 2020-08-16 16:05:58
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-04-04 17:54:42
*/

#include "lfp_base.h"
#include "lfp_arch_adapter.h"
#include "lfp_app_init.h"

/*
lfp module registration initialization
*/
LFP_STATIC LFP_CONST LFP_CODE LFP_COMPONENTS_REGISTER_T g_componentsRegister[] = 
{
	LFP_MODLUE_REGISTER(lfp_util_module_init),
	LFP_MODLUE_REGISTER(lfp_arch_adapter_init),
	//LFP_MODLUE_REGISTER(lfp_app_init),
};

/*
Registration and initialization of each test component module of lfp
*/
LFP_STATIC LFP_CONST LFP_CODE LFP_COMPONENTS_REGISTER_T g_componentsTestRegister[] = 
{
	//LFP_MODLUE_REGISTER(lfp_app_test_init),
};

/*@fn		  LFP_INT32 lfp_wytaitai_main_entrance(LFP_VOID)
* @brief 	  the main entrance of the project
* @param[in]  LFP_VOID
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_STATIC LFP_INT32 lfp_wytaitai_main_entrance(LFP_VOID)
{
	LFP_UINT32 uiModules = 0;
	
	for(uiModules = 0; uiModules < LFP_NELEMENTS(g_componentsRegister); uiModules++)
	{
		if(LFP_NULL != g_componentsRegister[uiModules].lfp_components_register)
		{
			g_componentsRegister[uiModules].lfp_components_register();
		}
	}
	return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_wytaitai_test_entrance(LFP_VOID)
* @brief 	  the test main entrance of the project
* @param[in]  LFP_VOID
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_STATIC LFP_INT32 lfp_wytaitai_test_entrance(LFP_VOID)
{
	LFP_UINT32 uiModules = 0;
	
	for(uiModules = 0; uiModules < LFP_NELEMENTS(g_componentsTestRegister); uiModules++)
	{
		if(LFP_NULL != g_componentsTestRegister[uiModules].lfp_components_register)
		{
			g_componentsTestRegister[uiModules].lfp_components_register();
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
