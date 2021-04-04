/*
 * @fileName: lfp_app_busybox.c
 * @Description: the cmd tools for debugging the program
 * @Author: wytaitaislee
 * @Date: 2021-01-31 11:34:26
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-04-04 15:58:16
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

LFP_STATIC LFP_INT32 lfp_app_busybox_gettime(LFP_INT8 iArgs, LFP_CONST LFP_INT8 **ppArgv)
{
    return LFP_OK;
}

LFP_STATIC LFP_CONST LFP_CODE LFP_APP_BUSYBOX_T gAppBusyBoxExcel[] = 
{
    LFP_APP_BUSYBOX_REGISTER(LFP_BUSYBOX_DEFINE_GETTIME, 
                             LFP_BUSYBOX_DEFINE_GETTIME_HELP,
                             0, 
                             lfp_app_busybox_gettime),
    
};

LFP_INT32 lfp_busybox_recv_proc(LFP_APP_BUSYBOX_T *pAppBusybox)
{
    LFP_INT32 iForEach = 0;

    LFP_ASSERT_ERR_RET(pAppBusybox);
    LFP_ASSERT_ERR_RET(pAppBusybox->pCmdHelpInfo);
    for(iForEach = 0; iForEach < LFP_NELEMENTS(gAppBusyBoxExcel); iForEach++)
    {
        if(gAppBusyBoxExcel[iForEach].pCmdName == pAppBusybox->pCmdName)
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
* @brief 	  loading command modules
* @param[in]  LFP_VOID
* @param[out] LFP_NULL
* @return	  LFP_OK / LFP_ERR
*/
LFP_INT32 lfp_busybox_init(LFP_VOID)
{
    return LFP_OK;
}

