#include "lfp_arch_adapter.h"
#include "__lfp_arch_adapter_typesdef.h"
#include "__lfp_arch_abstract.h"

#define LFP_GET_MUTEX_ENTRY()             (*(LFP_ARCH_ADAPTER_MUTEX_T*)LFP_GET_CLASS_ENTRY(mutex))
#define LFP_ADAPTER_MUTEX_INIT(FUNC)      LFP_ADAPTER_INIT(LFP_GET_MUTEX_ENTRY(), FUNC)

/* the definition of mutex cluster */
LFP_ARCH_ADAPTER2(LFP_GET_MUTEX_ENTRY(), mutex_create, LFP_INT32, LFP_MUTEX_T*, LFP_MUTEX_ATTR_T*);
LFP_ARCH_ADAPTER1(LFP_GET_MUTEX_ENTRY(), mutex_lock, LFP_INT32, LFP_MUTEX_T*);
LFP_ARCH_ADAPTER1(LFP_GET_MUTEX_ENTRY(), mutex_unlock, LFP_INT32, LFP_MUTEX_T*);
LFP_ARCH_ADAPTER1(LFP_GET_MUTEX_ENTRY(), mutex_destroy, LFP_INT32, LFP_MUTEX_T*);

/*@fn		  LFP_INT32 lfp_arch_adapter_mutex_register(LFP_VOID)
* @brief 	  the adapter layer register -- mutex cluster register
* @param[in]  LFP_NULL
* @param[out] LFP_NULL
* @return	  LFP_OK
*/
LFP_INT32 lfp_arch_adapter_mutex_register(LFP_VOID)
{
    LFP_ADAPTER_MUTEX_INIT(mutex_create);
    LFP_ADAPTER_MUTEX_INIT(mutex_lock);
    LFP_ADAPTER_MUTEX_INIT(mutex_unlock);
    LFP_ADAPTER_MUTEX_INIT(mutex_destroy);
    return LFP_OK;
}

