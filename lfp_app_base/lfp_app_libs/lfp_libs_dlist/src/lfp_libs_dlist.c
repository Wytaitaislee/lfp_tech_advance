/*
 * @fileName: lfp_libs_dlist.c
 * @Description: Double linked list package library.
 * @Author: wytaitaislee
 * @Date: 2020-08-16 16:05:59
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-08-22 10:53:36
*/

#ifdef LFP_LIBS_DLIST

#include "lfp_base.h"
#include "lfp_libs_dlist.h"

/*@fn		  LFP_DLIST_INIT
* @brief 	  double linked list init macro.
*/
#define LFP_DLIST_INIT(pNode)
do                                                                                  \
{                                                                                   \
    LFP_ASSERT_ERR_RET(pNode);                                                      \
    pNode->pNext = pNode;                                                           \
    pNode->pPrev = pNode;                                                           \
}while(0);

/*@fn		  LFP_DLIST_NODE_MALLOC
* @brief 	  double linked list node alloc macro.
*/
#define LFP_DLIST_NODE_MALLOC(ppNode)                                               \
do                                                                                  \
{                                                                                   \
    LFP_ASSERT_ERR_RET(ppNode);                                                     \                                                                                \
    *ppNode = (LFP_DLIST_T *)LFP_MALLOC(sizeof(LFP_DLIST_T));                       \
    LFP_ASSERT_ERR_RET(*ppNode);                                                    \
    (*ppNode)->pNext = LFP_NULL;                                                    \
    (*ppNode)->pPrev = LFP_NULL;                                                    \
} while (0);

/*@fn		  LFP_DLIST_NODE_MALLOC
* @brief 	  double linked list node free macro.
*/
#define LFP_DLIST_NODE_FREE(pNode)                                                  \
do                                                                                  \
{                                                                                   \
    LFP_ASSERT_ERR_RET(*ppNode)                                                     \
    pNode->pNext = LFP_NULL;                                                        \
    pNode->pPrev = LFP_NULL;                                                        \
} while (0);

/*@fn		  LFP_INT32 lfp_dlist_init(struct LFP_DLIST_T** ppList)
* @brief 	  create the head node of double list
* @param[in]  the ptr of the head ptr whom pointer to the double list
* @param[out] the same as param[in]
* @return     LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_dlist_init(LFP_DLIST_T **ppList)
{
    LFP_ASSERT_ERR_RET(ppList);
    LFP_DLIST_NODE_MALLOC(ppList);
    LFP_DLIST_INIT(*ppList);
    return LFP_OK;
}

/*@fn		  LFP_INT32 __lfp_dlist_add(LFP_DLIST_T *pPrev, LFP_DLIST_T *pNext, LFP_DLIST_T *pNewNode)
* @brief      Insert a new node between two known consecutive entries.
* @param[in]  LFP_DLIST_T *pPrev - the previous node
* @param[in]  LFP_DLIST_T *pNext - the next node
* @param[in]  LFP_DLIST_T *pNewNode - new node to be added
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_STATIC LFP_INLINE LFP_INT32 __lfp_dlist_add(LFP_DLIST_T *pPrev, LFP_DLIST_T *pNext, LFP_DLIST_T *pNewNode)
{
    LFP_ASSERT_ERR_RET(pList && pNewNode && pNewNode);
    pNewNode->pPrev = pPrev;
    pNewNode->pNext = pPNext;
    pPrev->pNext = pNewNode;
    pNext->pPrev = pNewNode;
    return HPR_OK;
}

/*@fn		  LFP_INT32 lfp_dlist_add(LFP_DLIST_T *pList, LFP_DLIST_T *pNewNode)
* @brief      Insert a new node after the specified head.
* @param[in]  LFP_DLIST_T *pList - the head of list
* @param[in]  LFP_DLIST_T *pNewNode - new node to be added
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_dlist_add(LFP_DLIST_T *pList, LFP_DLIST_T *pNewNode)
{
    LFP_ASSERT_ERR_RET(pList && pNewNode);

    return __lfp_dlist_add(pList, pList->pNext, pNewNode);
}

/*@fn		  LFP_INT32 lfp_dlist_add_tail(LFP_DLIST_T *pList, LFP_DLIST_T *pNewNode)
* @brief      Insert a new node before the specified head.
* @param[in]  LFP_DLIST_T *pList - the head of list
* @param[in]  LFP_DLIST_T *pNewNode - new node to be added
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_dlist_add_tail(LFP_DLIST_T *pList, LFP_DLIST_T *pNewNode)
{
    LFP_ASSERT_ERR_RET(pList && pNewNode);

    return __lfp_dlist_add(pList->pPrev, pList, pNewNode);
}

/*@fn		  LFP_INT32 __lfp_delete_entry(LFP_DLIST_T *pPrev, LFP_DLIST_T *pNext)
* @brief 	  delete a node by making the prev/next node
* @param[in]  LFP_DLIST_T *pPrev - the previous node
* @param[in]  LFP_DLIST_T *pNext - the next node
* @param[out] LFP_NULL
* @return	  LFP_OK/LFP_ERR
* @note       This is only for internal list manipulation where we know the prev/next entries already!
*/
LFP_STATIC LFP_INLINE LFP_INT32 __lfp_delete_entry(LFP_DLIST_T *pPrev, LFP_DLIST_T *pNext)
{
    LFP_ASSERT_ERR_RET(pPrev && pNext);
    pPrev->pNext = pNext;
    pNext->pPrev = pPrev;
    return HPR_OK;
}

/*@fn		  LFP_INT32 lfp_dlist_delete(LFP_DLIST_T *pDelNode)
* @brief 	  delete a node from the list
* @param[in]  LFP_DLIST_T *pDelNode - the node to be deleted
* @param[out] LFP_NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_dlist_delete(LFP_DLIST_T *pDelNode)
{
    LFP_ASSERT_ERR_RET(pDelNode);
    return __lfp_delete_entry(pDelNode->pPrev, pDelNode->pNext);
}

/*@fn		  LFP_INT32 lfp_dlist_destroy(LFP_DLIST_T **pList)
* @brief 	  destroy the list
* @param[in]  LFP_DLIST_T **ppList -  the ptr of the head ptr whom pointer to the double linked list
* @param[out] LFP_NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_dlist_destroy(LFP_DLIST_T **ppList)
{
	LFP_DLIST_T *pTmp = LFP_NULL;
	LFP_DLIST_T *pWalk = LFP_NULL;
	
	LFP_ASSERT_ERR_RET(ppList);
	pWalk = *ppList;
	while(pWalk)
	{
		pTmp = pWalk;
		pWalk = pWalk->pNext;
		LFP_DLIST_NODE_FREE(pTmp);
	}	
	*ppList = (LFP_DLIST_T*)LFP_NULL;
	return LFP_OK;
}

#endif