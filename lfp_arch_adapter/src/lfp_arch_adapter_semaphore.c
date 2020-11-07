#include "lfp_arch_adapter.h"
#include "__lfp_arch_adapter_typesdef.h"
#include "__lfp_arch_abstract.h"

#define LFP_GET_SEMAPHORE_ENTRY()             (*(LFP_ARCH_ADAPTER_SEMAPHORE_T*)LFP_GET_CLASS_ENTRY(semaphore))
#define LFP_ADAPTER_SEMAPHORE_INIT(FUNC)      LFP_ADAPTER_INIT(LFP_GET_SEMAPHORE_ENTRY(), FUNC)

/* the definition of semaphore cluster */
LFP_ARCH_ADAPTER3(LFP_GET_SEMAPHORE_ENTRY(), semaphore_init, LFP_INT32, LFP_SEM_T*, LFP_INT32, LFP_UINT32);
LFP_ARCH_ADAPTER2(LFP_GET_SEMAPHORE_ENTRY(), semaphore_wait, LFP_INT32, LFP_SEM_T*, LFP_INT32);
LFP_ARCH_ADAPTER1(LFP_GET_SEMAPHORE_ENTRY(), semaphore_post, LFP_INT32, LFP_SEM_T*);
LFP_ARCH_ADAPTER1(LFP_GET_SEMAPHORE_ENTRY(), semaphore_destroy, LFP_INT32, LFP_SEM_T*);

/*@fn		  LFP_INT32 lfp_arch_adapter_semaphore_register(LFP_VOID)
* @brief 	  the adapter layer register -- semaphore cluster register
* @param[in]  LFP_NULL
* @param[out] LFP_NULL
* @return	  LFP_OK
*/
LFP_INT32 lfp_arch_adapter_semaphore_register(LFP_VOID)
{
    LFP_ADAPTER_SEMAPHORE_INIT(semaphore_init);
    LFP_ADAPTER_SEMAPHORE_INIT(semaphore_wait);
    LFP_ADAPTER_SEMAPHORE_INIT(semaphore_post);
    LFP_ADAPTER_SEMAPHORE_INIT(semaphore_destroy);
    return LFP_OK;
}

