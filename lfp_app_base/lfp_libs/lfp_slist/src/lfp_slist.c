/*
 * @FilePath: lfp_slist.c
 * @Description: Single linked list package library.
 * @Author: wytaitaislee
 * @Date: 2021-08-27 23:29:52
 * @LastEditTime: 2022-04-05 18:02:39
 * @LastEditors: wytaitaislee
 * Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#include "lfp_slist.h"

/*@fn		  LFP_SLIST_HEAD_INIT
 * @brief 	  single linked list head init(struct entity).
 */
#define LFP_SLIST_HEAD_INIT(struList) \
    { &(struList) }

#define LFP_SLIST_HEAD(struListName) \
    LFP_SLIST_T struListName = LFP_SLIST_HEAD_INIT(struListName)

/*@fn		  LFP_SLIST_INIT
 * @brief 	  single linked list head init(ptr entity).
 */
#define LFP_SLIST_INIT(pList)       \
    do {                            \
        LFP_RET_IF(pList, LFP_ERR); \
        (pList)->pNext = pList;     \
    } while (0);

/*@fn		  LFP_SLIST_NODE_MALLOC
 * @brief 	  single linked list node alloc macro.
 */
#define LFP_SLIST_NODE_MALLOC(pNode)                              \
    do {                                                          \
        (pNode) = (LFP_SLIST_T *)LFP_MALLOC(sizeof(LFP_SLIST_T)); \
        LFP_RET_IF(pNode, LFP_ERR);                               \
        (pNode)->pNext = LFP_NULL;                                \
    } while (0);

/*@fn		  LFP_SLIST_NODE_FREE
 * @brief 	  single linked list node free macro.
 */
#define LFP_SLIST_NODE_FREE(pNode) \
    do {                           \
        LFP_RET_IF(pNode, LFP_OK); \
        LFP_SAFE_FREE(pNode);      \
        pNode = LFP_NULL;          \
    } while (0);

/*@fn		  LFP_INT32 lfp_slist_init(LFP_SLIST_T* pList)
 * @brief 	  create the head node of single linked list
 * @param[in]  LFP_SLIST_T *pList the head ptr whom pointer to the single linked
 * list
 * @param[out] the same as param[in]
 * @return     LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_slist_init(LFP_SLIST_T *pList) {
    LFP_SLIST_INIT(pList);
    return LFP_OK;
}

/*@fn		  LFP_INT32 __lfp_slist_add(LFP_SLIST_T *pPrev, LFP_SLIST_T
 * *pNext, LFP_SLIST_T *pNewNode)
 * @brief 	  Insert a new node between two known consecutive entries
 * @param[in]  LFP_SLIST_T *pPrev - the previous node
 * @param[in]  LFP_SLIST_T *pNext - the next node
 * @param[in]  LFP_SLIST_T *pNewNode - new node to be added
 * @param[out] NULL
 * @return     LFP_OK/LFP_ERR
 */
LFP_STATIC LFP_INT32 __lfp_slist_add(LFP_SLIST_T *pPrev, LFP_SLIST_T *pNext,
                                     LFP_SLIST_T *pNewNode) {
    LFP_RET_IF(pPrev && pNext && pNewNode, LFP_ERR);
    pNewNode->pNext = pNext;
    pPrev->pNext = pNewNode;
    return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_slist_add(LFP_SLIST_T *pList, LFP_SLIST_T
 * *pNewNode)
 * @brief      Insert a new node after the specified head.
 * @param[in]  LFP_SLIST_T *pList - the head of list
 * @param[in]  LFP_SLIST_T *pNewNode - new node to be added
 * @param[out] NULL
 * @return	  LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_slist_add(LFP_SLIST_T *pList, LFP_SLIST_T *pNewNode) {
    LFP_RET_IF(pList && pNewNode, LFP_ERR);
    return __lfp_slist_add(pList, pList->pNext, pNewNode);
}

/*@fn		  LFP_INT32 lfp_slist_add_tail(LFP_SLIST_T *pList, LFP_SLIST_T
 * *pNewNode)
 * @brief      Insert a new node at the end of the single linked list.
 * @param[in]  LFP_SLIST_T *pList - the head of list
 * @param[in]  LFP_SLIST_T *pNewNode - new node to be added
 * @param[out] NULL
 * @return	  LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_slist_add_tail(LFP_SLIST_T *pList, LFP_SLIST_T *pNewNode) {
    LFP_RET_IF(pList && pNewNode, LFP_ERR);
    while (pList->pNext) {
        pList = pList->pNext;
    }
    return __lfp_slist_add(pList, NULL, pNewNode);
}

/*@fn		  LFP_INT32 __lfp_delete_entry(LFP_SLIST_T *pPrev, LFP_SLIST_T
 * *pNext)
 * @brief 	  delete a node by making the prev/next node
 * @param[in]  LFP_SLIST_T *pPrev - the previous node
 * @param[in]  LFP_SLIST_T *pNext - the next node
 * @param[out] LFP_NULL
 * @return	  LFP_OK/LFP_ERR
 * @note       This is only for internal list manipulation where we know the
 * prev/next entries already!
 */
LFP_STATIC LFP_INLINE LFP_INT32 __lfp_delete_entry(LFP_SLIST_T *pPrev,
                                                   LFP_SLIST_T *pNext) {
    LFP_RET_IF(pPrev && pNext, LFP_ERR);
    pPrev->pNext = pNext;
    return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_slist_delete_element(LFP_SLIST_T *pList,
 * LFP_SLIST_T *pNode)
 * @brief 	  delete a node from the list
 * @param[in]  LFP_SLIST_T *pList - the head of list
 * @param[in]  LFP_SLIST_T *pNode - the element to be deleted
 * @param[out] NULL
 * @return	  LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_slist_delete(LFP_SLIST_T *pList, LFP_SLIST_T *pDelNode) {
    LFP_SLIST_T *pWalk = LFP_NULL;

    LFP_RET_IF(pList && pDelNode, LFP_ERR);
    pWalk = pList;
    while (pWalk->pNext) {
        if (pWalk->pNext == pDelNode) {
            break;
        }
        pWalk = pWalk->pNext;
    }
    LFP_RET_IF(pWalk, LFP_OK);
    if (LFP_OK != __lfp_delete_entry(pWalk, pDelNode->pNext)) {
        LFP_SLIST_ERR("delete node[%p] failed\n", pDelNode);
        return LFP_ERR;
    }
    LFP_SLIST_NODE_FREE(pDelNode);
    return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_slist_destroy(LFP_SLIST_T*pList)
 * @brief 	  destroy the list
 * @param[in]  LFP_SLIST_T *pList - the head ptr whom pointer to the single
 * linked list
 * @param[out] LFP_NULL
 * @return	  LFP_OK/LFP_ERR
 */
LFP_INT32 lfp_slist_destroy(LFP_SLIST_T *pList) {
    LFP_SLIST_T *pTmp = LFP_NULL;
    LFP_SLIST_T *pWalk = LFP_NULL;

    LFP_RET_IF(pList, LFP_ERR);
    pWalk = pList;
    while (pWalk) {
        pTmp = pWalk;
        pWalk = pWalk->pNext;
        LFP_SLIST_NODE_FREE(pTmp);
    }
    return LFP_OK;
}

/*@fn		   LFP_BOOL lfp_slist_empty(LFP_SLIST_T *pList)
 * @brief 	   assert if slist is empty
 * @param[in]  LFP_SLIST_T *pList -  the head ptr whom pointer to the single linked list
 * @param[out] LFP_NULL
 * @return	   LFP_TRUE/LFP_FALSE
 */
LFP_BOOL lfp_slist_empty(LFP_SLIST_T *pList) {
    LFP_RET_IF(pList, LFP_FALSE);
    if (pList->pNext == pList) {
        return LFP_TRUE;
    }
    return LFP_FALSE;
}
