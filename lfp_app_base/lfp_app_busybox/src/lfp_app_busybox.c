/*
 * @fileName: lfp_app_busybox.c
 * @Description: the cmd tools for debugging the program
 * @Author: wytaitaislee
 * @Date: 2021-01-31 11:34:26
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-08-21 16:21:12
*/

#include "lfp_app_busybox.h"

#define LFP_APP_BUSYBOX_REGISTER(name, help, auth, proc)    {name, help, auth, proc, 0, 0}                          \

#define LFP_APP_BUSYBOX_UNRESIGSTER(cmd)                                            \
do                                                                                  \
{                                                                                   \
    LFP_APP_BUSYBOX_ERR("unresigster cmd %s, please check the input!!!", cmd);      \
} while (0);


#define LFP_BUSYBOX_DEFINE_GETTIME      "getTime"
#define LFP_BUSYBOX_DEFINE_GETTIME_HELP "todo"

/*@fn		  LFP_STATIC LFP_INT32 lfp_app_busybox_gettime(LFP_INT8 iArgs, LFP_CONST LFP_INT8 **ppArgv)
* @brief 	  usrbusybox - get the system time
* @param[in]  LFP_NULL
* @param[out] LFP_NULL
* @return	  LFP_OK
*/
LFP_STATIC LFP_INT32 lfp_app_busybox_gettime(LFP_INT8 iArgs, LFP_CONST LFP_INT8 **ppArgv)
{
    (LFP_VOID)iArgs;
    (LFP_VOID)ppArgv;
    return LFP_OK;
}

/*@fn		  
* @brief 	  the usrbusybox excel.
* @param[in]  NULL
* @param[out] NULL
* @return	  NULL
*/
LFP_STATIC LFP_CONST LFP_CODE LFP_APP_BUSYBOX_T gAppBusyBoxExcel[] = 
{
    LFP_APP_BUSYBOX_REGISTER(LFP_BUSYBOX_DEFINE_GETTIME, 
                             LFP_BUSYBOX_DEFINE_GETTIME_HELP,
                             0, 
                             lfp_app_busybox_gettime),
    
};

/*@fn		  LFP_INT32 lfp_busybox_recv_proc(LFP_APP_BUSYBOX_T *pAppBusybox)
* @brief 	  usrbusybox exec control.
* @param[in]  LFP_NULL
* @param[out] LFP_NULL
* @return	  LFP_OK
*/
LFP_INT32 lfp_busybox_recv_proc(LFP_APP_BUSYBOX_T *pAppBusybox)
{
    LFP_UINT32 uiForEach = 0;

    LFP_ASSERT_ERR_RET(pAppBusybox);
    LFP_ASSERT_ERR_RET(pAppBusybox->pCmdHelpInfo);
    for(uiForEach = 0; uiForEach < LFP_NELEMENTS(gAppBusyBoxExcel); uiForEach++)
    {
        if(gAppBusyBoxExcel[uiForEach].pCmdName == pAppBusybox->pCmdName)
        {
            if(pAppBusybox->pCallbackBusybox)
            {
                return pAppBusybox->pCallbackBusybox(pAppBusybox->iArgs, pAppBusybox->ppArgv);
            }
        }
    }
    LFP_APP_BUSYBOX_UNRESIGSTER(pAppBusybox->pCmdName);
    return LFP_ERR;
}

/*@fn		  LFP_INT32 lfp_busybox_init(LFP_VOID)
* @brief 	  loading usr command modules
* @param[in]  LFP_VOID
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_busybox_init(LFP_VOID)
{
    return LFP_OK;
}

