/***
 * @FilePath: lfp_dlist.h
 * @Description: Doubly linked list package library.
 * @Author: wytaitaislee
 * @Date: 2021-08-27 23:29:52
 * @LastEditTime: 2022-03-05 21:25:11
 * @LastEditors: wytaitaislee
 * @Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#ifndef __LFP_DLIST_H__
#define __LFP_DLIST_H__

#include "lfp_base.h"

#define LFP_DLIST_CRIT(...) \
    LFP_LOG_BASE(LOG_LEVEL_CRIT, LOG_MODULE_DLIST, MASK_DLIST, ##__VA_ARGS__)
#define LFP_DLIST_ERR(...) \
    LFP_LOG_BASE(LOG_LEVEL_ERR, LOG_MODULE_DLIST, MASK_DLIST, ##__VA_ARGS__)
#define LFP_DLIST_INFO(...) \
    LFP_LOG_BASE(LOG_LEVEL_INFO, LOG_MODULE_DLIST, MASK_DLIST, ##__VA_ARGS__)

/*double list structure definition */
typedef struct lfp_dlist_t {
    struct lfp_dlist_t *pPrev;
    struct lfp_dlist_t *pNext;
} LFP_DLIST_T;

/*@fn		  LFP_INT32 lfp_dlist_init(struct LFP_DLIST_T *pList)
 * @brief 	  create the head node of double list
 * @param[in]  the head ptr whom pointer to the double list
 * @param[out] the same as param[in]
 * @return     LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_dlist_init(LFP_DLIST_T *pList);

/*@fn         LFP_INT32 lfp_dlist_add(LFP_DLIST_T *pList, LFP_DLIST_T *pNewNode)
 * @brief      Insert a new node after the specified head.
 * @param[in]  LFP_DLIST_T *pList - the head of list
 * @param[in]  LFP_DLIST_T *pNewNode - new node to be added
 * @param[out] NULL
 * @return     LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_dlist_add(LFP_DLIST_T *pList, LFP_DLIST_T *pNewNode);

/*@fn	      LFP_INT32 lfp_dlist_add_tail(LFP_DLIST_T *pList, LFP_DLIST_T
 * *pNewNode)
 * @brief      Insert a new node before the specified head.
 * @param[in]  LFP_DLIST_T *pList - the head of list
 * @param[in]  LFP_DLIST_T *pNewNode - new node to be added
 * @param[out] NULL
 * @return     LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_dlist_add_tail(LFP_DLIST_T *pList, LFP_DLIST_T *pNewNode);

/*@fn	      LFP_INT32 lfp_dlist_delete(LFP_DLIST_T *pDelNode)
 * @brief      delete a node from the list
 * @param[in]  LFP_DLIST_T *pDelNode - the node to be deleted
 * @param[out] LFP_NULL
 * @return     LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_dlist_delete(LFP_DLIST_T *pDelNode);

/*@fn		  LFP_INT32 lfp_dlist_destroy(LFP_DLIST_T *pList)
 * @brief 	  destroy the list
 * @param[in]  LFP_DLIST_T *pList -  the head ptr whom pointer to the double
 * linked list
 * @param[out] LFP_NULL
 * @return	  LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_dlist_destroy(LFP_DLIST_T *pList);

/*@fn		   LFP_BOOL lfp_dlist_empty(LFP_DLIST_T *pList)
 * @brief 	   assert if dlist is empty
 * @param[in]  LFP_DLIST_T *pList -  the head ptr whom pointer to the double linked list
 * @param[out] LFP_NULL
 * @return	   LFP_TRUE/LFP_FALSE
 */
LFP_BOOL lfp_dlist_empty(LFP_DLIST_T *pList);

#endif /* end of __LFP_DLIST_H__ */