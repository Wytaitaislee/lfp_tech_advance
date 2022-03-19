/***
 * @FilePath: lfp_slist.h
 * @Description: Singly linked list package library.
 * @Author: wytaitaislee
 * @Date: 2021-08-27 23:29:52
 * @LastEditTime: 2022-03-05 21:24:52
 * @LastEditors: wytaitaislee
 * @Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#ifndef __LFP_SLIST_H__
#define __LFP_SLIST_H__

#ifdef LFP_LIBS_SLIST

#include "lfp_base.h"

#define LFP_SLIST_CRIT(...) \
    LFP_LOG_BASE(LOG_LEVEL_CRIT, LOG_MODULE_SLIST, MASK_SLIST, __VA_ARGS__)
#define LFP_SLIST_ERR(...) \
    LFP_LOG_BASE(LOG_LEVEL_ERR, LOG_MODULE_SLIST, MASK_SLIST, __VA_ARGS__)
#define LFP_SLIST_INFO(...) \
    LFP_LOG_BASE(LOG_LEVEL_INFO, LOG_MODULE_SLIST, MASK_SLIST, __VA_ARGS__)

/*single list structure definition */
typedef struct lfp_slist_t {
    struct lfp_slist_t *pNext;
} LFP_SLIST_T;

/*@fn		  LFP_INT32 lfp_slist_init(LFP_SLIST_T* pList)
 * @brief 	  create the head node of single linked list
 * @param[in]  LFP_SLIST_T *pList the head ptr whom pointer to the single linked
 * list
 * @param[out] the same as param[in]
 * @return     LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_slist_init(LFP_SLIST_T *pList);

/*@fn		  LFP_INT32 lfp_slist_add(LFP_SLIST_T *pList, LFP_SLIST_T
 * *pNewNode)
 * @brief      Insert a new node after the specified head.
 * @param[in]  LFP_SLIST_T *pList - the head of list
 * @param[in]  LFP_SLIST_T *pNewNode - new node to be added
 * @param[out] NULL
 * @return	  LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_slist_add(LFP_SLIST_T *pList, LFP_SLIST_T *pNewNode);

/*@fn		  LFP_INT32 lfp_slist_add_tail(LFP_SLIST_T *pList, LFP_SLIST_T
 * *pNewNode)
 * @brief      Insert a new node at the end of the single linked list.
 * @param[in]  LFP_SLIST_T *pList - the head of list
 * @param[in]  LFP_SLIST_T *pNewNode - new node to be added
 * @param[out] NULL
 * @return	  LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_slist_add_tail(LFP_SLIST_T *pList, LFP_SLIST_T *pNewNode);

/*@fn		  LFP_INT32 lfp_slist_delete_element(LFP_SLIST_T *pList,
 * LFP_SLIST_T *pNode)
 * @brief 	  delete a node from the list
 * @param[in]  LFP_SLIST_T *pList - the head of list
 * @param[in]  LFP_SLIST_T *pNode - the element to be deleted
 * @param[out] NULL
 * @return	  LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_slist_delete(LFP_SLIST_T *pList, LFP_SLIST_T *pDelNode);

/*@fn		  LFP_INT32 lfp_slist_destroy(LFP_SLIST_T*pList)
 * @brief 	  destroy the list
 * @param[in]  LFP_SLIST_T *pList - the head ptr whom pointer to the single
 * linked list
 * @param[out] LFP_NULL
 * @return	  LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_slist_destroy(LFP_SLIST_T *pList);

#endif

#endif /* end of __LFP_SLIST_H__ */
