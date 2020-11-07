#include "lfp_arch_adapter.h"
#include "__lfp_arch_adapter_typesdef.h"
#include "__lfp_arch_abstract.h"

#define LFP_GET_STDIO_ENTRY()             (*(LFP_ARCH_ADAPTER_STDIO_T*)LFP_GET_CLASS_ENTRY(stdio))
#define LFP_ADAPTER_STDIO_INIT(FUNC)      LFP_ADAPTER_INIT(LFP_GET_STDIO_ENTRY(), FUNC)

/* the definition of stdio io cluster */
LFP_ARCH_ADAPTER2(LFP_GET_STDIO_ENTRY(), stdio_open, LFP_FILE*, LFP_CONST LFP_INT8 *LFP_RESTRICT, LFP_CONST LFP_INT8 *LFP_RESTRICT);
LFP_ARCH_ADAPTER3(LFP_GET_STDIO_ENTRY(), stdio_seek, LFP_INT32, LFP_FILE*, LFP_LONG, LFP_INT32);
LFP_ARCH_ADAPTER4(LFP_GET_STDIO_ENTRY(), stdio_read, LFP_SIZE_T, LFP_VOID *LFP_RESTRICT, LFP_SIZE_T, LFP_SIZE_T, LFP_FILE *LFP_RESTRICT);
LFP_ARCH_ADAPTER4(LFP_GET_STDIO_ENTRY(), stdio_write, LFP_SIZE_T, LFP_CONST LFP_VOID *LFP_RESTRICT, LFP_SIZE_T, LFP_SIZE_T, LFP_FILE *LFP_RESTRICT);
LFP_ARCH_ADAPTER1(LFP_GET_STDIO_ENTRY(), stdio_close, LFP_INT32, LFP_INT32);

/*@fn		  LFP_INT32 lfp_arch_adapter_stdio_register(LFP_VOID)
* @brief 	  the adapter layer register -- stdio cluster register
* @param[in]  LFP_NULL
* @param[out] LFP_NULL
* @return	  LFP_OK
*/
LFP_INT32 lfp_arch_adapter_stdio_register(LFP_VOID)
{
//    LFP_ADAPTER_STDIO_INIT(stdio_open);
//    LFP_ADAPTER_STDIO_INIT(stdio_seek);
//    LFP_ADAPTER_STDIO_INIT(stdio_read);
//    LFP_ADAPTER_STDIO_INIT(stdio_write);
//    LFP_ADAPTER_STDIO_INIT(stdio_close);
    return LFP_OK;
}

