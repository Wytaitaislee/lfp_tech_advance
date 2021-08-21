/*
 * @fileName: lfp_arch_adapter_typesdef.h
 * @Description: Private data structure of platform adaptation layer. the file only can be 
                 invoked by lfp_arch_xxxx.c
 * @Author: wytaitaislee
 * @Date: 2020-08-16 16:05:58
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-08-21 16:01:36
*/
#ifndef __LFP_ARCH_ADAPTER_TYPESDEF_H__
#define __LFP_ARCH_ADAPTER_TYPESDEF_H__
 
 #include <stdio.h>

 #define LFP_PREFIX    lfp_
 #define LFP_ARCH_ADAPTER_UNDEF_RETURN(LFP_ADAPTER_RETURN)                  \
 do                                                                         \
 {                                                                          \
        return ((LFP_ADAPTER_RETURN)(-1));                                  \
 }while(0)
 
 #define LFP_ARCH_ADAPTER_UNDEF(LFP_ADAPTER_RETURN, LFP_CLASS, LFP_ADAPTER_FUNCTION_NAME)                       \
 do                                                                                                             \
 {                                                                                                              \
    printf("lfp arch adapter function: %s.%s, undefined !\n", #LFP_CLASS, #LFP_ADAPTER_FUNCTION_NAME);          \
    LFP_ARCH_ADAPTER_UNDEF_RETURN(LFP_ADAPTER_RETURN);                                                          \
 }while(0)

/* General structure definition, no parameters. */
#define LFP_ARCH_ADAPTER0(LFP_ADAPTER_CLASS, LFP_ADAPTER_FUNCTION_NAME, LFP_ADAPTER_RETURN)                 \
LFP_ADAPTER_RETURN lfp_##LFP_ADAPTER_FUNCTION_NAME()                                                        \
{                                                                                                           \
    if(NULL != LFP_ADAPTER_CLASS.LFP_ADAPTER_FUNCTION_NAME)                                                 \
    {                                                                                                       \
        return LFP_ADAPTER_CLASS.LFP_ADAPTER_FUNCTION_NAME();                                               \
    }                                                                                                       \
    else                                                                                                    \
    {                                                                                                       \
        LFP_ARCH_ADAPTER_UNDEF(LFP_ADAPTER_RETURN, LFP_CLASS, LFP_ADAPTER_FUNCTION_NAME);                   \
    }                                                                                                       \
}

/* General structure definition, 1 parameters. */
#define LFP_ARCH_ADAPTER1(LFP_ADAPTER_CLASS, LFP_ADAPTER_FUNCTION_NAME, LFP_ADAPTER_RETURN, LFP_ADAPTER_PARAM_TYPE1)\
LFP_ADAPTER_RETURN lfp_##LFP_ADAPTER_FUNCTION_NAME(LFP_ADAPTER_PARAM_TYPE1 value)                           \
{                                                                                                           \
    if(NULL != LFP_ADAPTER_CLASS.LFP_ADAPTER_FUNCTION_NAME)                                                 \
    {                                                                                                       \
        return LFP_ADAPTER_CLASS.LFP_ADAPTER_FUNCTION_NAME(value);                                          \
    }                                                                                                       \
    else                                                                                                    \
    {                                                                                                       \
        LFP_ARCH_ADAPTER_UNDEF(LFP_ADAPTER_RETURN, LFP_CLASS, LFP_ADAPTER_FUNCTION_NAME);                   \
    }                                                                                                       \
}

/* General structure definition, 2 parameters. */
#define LFP_ARCH_ADAPTER2(LFP_ADAPTER_CLASS, LFP_ADAPTER_FUNCTION_NAME, LFP_ADAPTER_RETURN,                 \
                            LFP_ADAPTER_PARAM_TYPE1, LFP_ADAPTER_PARAM_TYPE2)                               \
LFP_ADAPTER_RETURN lfp_##LFP_ADAPTER_FUNCTION_NAME(LFP_ADAPTER_PARAM_TYPE1 value1,                          \
                                                    LFP_ADAPTER_PARAM_TYPE2 value2)                         \
{                                                                                                           \
    if(NULL != LFP_ADAPTER_CLASS.LFP_ADAPTER_FUNCTION_NAME)                                                 \
    {                                                                                                       \
        return LFP_ADAPTER_CLASS.LFP_ADAPTER_FUNCTION_NAME(value1, value2);                                 \
    }                                                                                                       \
    else                                                                                                    \
    {                                                                                                       \
        LFP_ARCH_ADAPTER_UNDEF(LFP_ADAPTER_RETURN, LFP_CLASS, LFP_ADAPTER_FUNCTION_NAME);                   \
    }                                                                                                       \
}

/* General structure definition, 3 parameters. */
#define LFP_ARCH_ADAPTER3(LFP_ADAPTER_CLASS, LFP_ADAPTER_FUNCTION_NAME, LFP_ADAPTER_RETURN,                 \
                            LFP_ADAPTER_PARAM_TYPE1, LFP_ADAPTER_PARAM_TYPE2, LFP_ADAPTER_PARAM_TYPE3)      \
LFP_ADAPTER_RETURN lfp_##LFP_ADAPTER_FUNCTION_NAME(LFP_ADAPTER_PARAM_TYPE1 value1,                          \
                                                    LFP_ADAPTER_PARAM_TYPE2 value2,                         \
                                                    LFP_ADAPTER_PARAM_TYPE3 value3)                         \
{                                                                                                           \
    if(NULL != LFP_ADAPTER_CLASS.LFP_ADAPTER_FUNCTION_NAME)                                                 \
    {                                                                                                       \
        return LFP_ADAPTER_CLASS.LFP_ADAPTER_FUNCTION_NAME(value1, value2, value3);                         \
    }                                                                                                       \
    else                                                                                                    \
    {                                                                                                       \
        LFP_ARCH_ADAPTER_UNDEF(LFP_ADAPTER_RETURN, LFP_CLASS, LFP_ADAPTER_FUNCTION_NAME);                   \
    }                                                                                                       \
}

/* General structure definition, 4 parameters. */
#define LFP_ARCH_ADAPTER4(LFP_ADAPTER_CLASS, LFP_ADAPTER_FUNCTION_NAME, LFP_ADAPTER_RETURN,                 \
                            LFP_ADAPTER_PARAM_TYPE1, LFP_ADAPTER_PARAM_TYPE2, LFP_ADAPTER_PARAM_TYPE3,      \
                             LFP_ADAPTER_PARAM_TYPE4)                                                       \
LFP_ADAPTER_RETURN lfp_##LFP_ADAPTER_FUNCTION_NAME(LFP_ADAPTER_PARAM_TYPE1 value1,                          \
                                                    LFP_ADAPTER_PARAM_TYPE2 value2,                         \
                                                    LFP_ADAPTER_PARAM_TYPE3 value3,                         \
                                                    LFP_ADAPTER_PARAM_TYPE4 value4)                         \
{                                                                                                           \
    if(NULL != LFP_ADAPTER_CLASS.LFP_ADAPTER_FUNCTION_NAME)                                                 \
    {                                                                                                       \
        return LFP_ADAPTER_CLASS.LFP_ADAPTER_FUNCTION_NAME(value1, value2, value3, value4);                 \
    }                                                                                                       \
    else                                                                                                    \
    {                                                                                                       \
        LFP_ARCH_ADAPTER_UNDEF(LFP_ADAPTER_RETURN, LFP_CLASS, LFP_ADAPTER_FUNCTION_NAME);                   \
    }                                                                                                       \
}

/* General structure definition, 5 parameters. */
#define LFP_ARCH_ADAPTER5(LFP_ADAPTER_CLASS, LFP_ADAPTER_FUNCTION_NAME, LFP_ADAPTER_RETURN,                 \
                            LFP_ADAPTER_PARAM_TYPE1, LFP_ADAPTER_PARAM_TYPE2, LFP_ADAPTER_PARAM_TYPE3,      \
                             LFP_ADAPTER_PARAM_TYPE4, LFP_ADAPTER_PARAM_TYPE5)                              \
LFP_ADAPTER_RETURN lfp_##LFP_ADAPTER_FUNCTION_NAME(LFP_ADAPTER_PARAM_TYPE1 value1,                          \
                                                    LFP_ADAPTER_PARAM_TYPE2 value2,                         \
                                                    LFP_ADAPTER_PARAM_TYPE3 value3,                         \
                                                    LFP_ADAPTER_PARAM_TYPE4 value4,                         \
                                                    LFP_ADAPTER_PARAM_TYPE5 value5)                         \
{                                                                                                           \
    if(NULL != LFP_ADAPTER_CLASS.LFP_ADAPTER_FUNCTION_NAME)                                                 \
    {                                                                                                       \
        return LFP_ADAPTER_CLASS.LFP_ADAPTER_FUNCTION_NAME(value1, value2, value3, value4, value5);         \
    }                                                                                                       \
    else                                                                                                    \
    {                                                                                                       \
        LFP_ARCH_ADAPTER_UNDEF(LFP_ADAPTER_RETURN, LFP_CLASS, LFP_ADAPTER_FUNCTION_NAME);                   \
    }                                                                                                       \
}

/* General structure definition, 6 parameters. */
#define LFP_ARCH_ADAPTER6(LFP_ADAPTER_CLASS, LFP_ADAPTER_FUNCTION_NAME, LFP_ADAPTER_RETURN,                 \
                            LFP_ADAPTER_PARAM_TYPE1, LFP_ADAPTER_PARAM_TYPE2, LFP_ADAPTER_PARAM_TYPE3,      \
                             LFP_ADAPTER_PARAM_TYPE4, LFP_ADAPTER_PARAM_TYPE5, LFP_ADAPTER_PARAM_TYPE6)     \
LFP_ADAPTER_RETURN lfp_##LFP_ADAPTER_FUNCTION_NAME(LFP_ADAPTER_PARAM_TYPE1 value1,                          \
                                                    LFP_ADAPTER_PARAM_TYPE2 value2,                         \
                                                    LFP_ADAPTER_PARAM_TYPE3 value3,                         \
                                                    LFP_ADAPTER_PARAM_TYPE4 value4,                         \
                                                    LFP_ADAPTER_PARAM_TYPE5 value5,                         \
                                                    LFP_ADAPTER_PARAM_TYPE6 value6)                         \
{                                                                                                           \
    if(NULL != LFP_ADAPTER_CLASS.LFP_ADAPTER_FUNCTION_NAME)                                                 \
    {                                                                                                       \
        return LFP_ADAPTER_CLASS.LFP_ADAPTER_FUNCTION_NAME(value1, value2, value3, value4, value5, value6); \
    }                                                                                                       \
    else                                                                                                    \
    {                                                                                                       \
        LFP_ARCH_ADAPTER_UNDEF(LFP_ADAPTER_RETURN, LFP_CLASS, LFP_ADAPTER_FUNCTION_NAME);                   \
    }                                                                                                       \
}

#endif /*end of __LFP_ARCH_ADAPTER_TYPESDEF_H__ */