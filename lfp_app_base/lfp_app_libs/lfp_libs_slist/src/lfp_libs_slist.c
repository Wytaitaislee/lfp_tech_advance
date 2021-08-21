/*
 * @fileName: lfp_libs_slist.c
 * @Description: Singly linked list package library
 * @Author: wytaitaislee
 * @Date: 2020-08-16 16:05:59
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-08-21 16:25:16
 */

#ifdef LFP_LIBS_SLIST

#include "lfp_base.h"
#include "lfp_libs_slist.h"

/*@fn		  LFP_SLIST_NODE_MALLOC
* @brief 	  singly linked list node alloc macro.
*/
#define LFP_SLIST_NODE_MALLOC(ppNode)											\
do																				\
{																				\
	*ppNode = (LFP_SLIST_T *)LFP_MALLOC(sizeof(LFP_SLIST_T));					\
	LFP_ASSERT_ERR_RET(*ppNode);												\
	(*ppNode)->pNext = LFP_NULL;												\
	(*ppNode)->data = 0;														\
}while(0);

/*@fn		  LFP_SLIST_NODE_FREE
* @brief 	  singly linked list node free macro.
*/
#define LFP_SLIST_NODE_FREE(pNode)												\
do																				\
{																				\
	pNode->pNext = LFP_NULL;													\
	pNode->data = 0;															\
	pNode = LFP_NULL;															\
}while(0);

/*@fn		  LFP_INT32 lfp_slist_create_head(LFP_SLIST_T** ppList)
* @brief 	  create the head node of single list
* @param[in]  the ptr of the head ptr whom pointer to the single list
* @param[out] the same as param[in]
* @return     LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_slist_create_head(LFP_SLIST_T **ppList)
{
	LFP_ASSERT_ERR_RET(ppList);
	LFP_SLIST_NODE_MALLOC(ppList);
	LFP_ASSERT_ERR_RET(*ppList);
	return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_slist_add_element(LFP_SLIST_T *pHead, LFP_UINT32 uiNum)
* @brief 	  add a specific num of nodes to the end of the single list
* @param[in]  LFP_SLIST_T *pHead - the head of the list
* @param[in]  LFP_UINT32 uiNum - the num of the specific nodes
* @param[out] NULL
* @return     LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_slist_add_element(LFP_SLIST_T *pList, LFP_UINT32 uiNum)
{	
	LFP_SLIST_T *pWalk = LFP_NULL;
	LFP_SLIST_T *pNode = LFP_NULL;
	LFP_UINT32 uiAddCnt = 0;

	LFP_ASSERT_ERR_RET(pList);
	pWalk = pList;
	/* move to the end of the list */
	while(pWalk->pNext)
	{
		pWalk = pWalk->pNext;
	}
	/* add uiNum's of node to the list */
	for(uiAddCnt = 0; uiAddCnt < uiNum; uiAddCnt++)
	{
		LFP_SLIST_NODE_MALLOC(&pNode);
		pWalk->pNext = pNode;
		pWalk = pWalk->pNext;
		LFP_SLIST_CRIT("add node[%p] to the list ok!\n", pNode);
	}
	return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_slist_append_node(LFP_SLIST_T *pList, LFP_SLIST_T *pAddNode)
* @brief 	  append a new node to the end of the single list
* @param[in]  LFP_SLIST_T *pList - the head of the list
* @param[in]  LFP_SLIST_T *pAddNode - the node to be added
* @param[out] LFP_NULL
* @return     LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_slist_append_node(LFP_SLIST_T *pList, LFP_SLIST_T *pAddNode)
{
    LFP_SLIST_T *pWalk = LFP_NULL;

    LFP_ASSERT_ERR_RET(pList && pAddNode);
    pWalk = pList;
    /* move to the end of the list */
    while(pWalk->pNext)
    {
        pWalk = pWalk->pNext;
    }
    pWalk->pNext = pAddNode;
    LFP_SLIST_CRIT("append node[%p] to the list ok!\n", pAddNode);
    return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_slist_insert_element_by_node( LFP_SLIST_T *pList, 
																	LFP_SLIST_T *pPrev, 
																	LFP_INT32 iData)
* @brief 	  add a new node to the single list(before a specific node)
* @param[in]  LFP_SLIST_T *pList - the head of list
* @param[in]  LFP_SLIST_T *pPrev - the previous element of the inserted element
* @param[in]  LFP_INT32 iData - the data of the new node
* @param[out] LFP_NULL
* @note		  if *pNode does not exist in the list, return LFP_ERR
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_slist_insert_element_by_node(LFP_SLIST_T *pList, LFP_SLIST_T *pNode, LFP_INT32 iData)
{
	LFP_SLIST_T *pWalk = LFP_NULL;
	LFP_SLIST_T *pNewNode = LFP_NULL;
	
	LFP_ASSERT_ERR_RET(pList && pNode);
	pWalk = pList;
	/* here we use pWalk->pNext to avoid traverse to the end */
	while(pWalk->pNext)
	{
		if(pWalk->pNext == pNode)
		{
			break;
		}
		pWalk = pWalk->pNext;
	}
	if(!pWalk->pNext)
	{	/* insert to the end of the list. */
		LFP_SLIST_ERR("there is no node[%p][data:%d] in the list\n", pNode, pNode->data);
		return LFP_ERR;
	}
	LFP_SLIST_NODE_MALLOC(&pNewNode);
	LFP_ASSERT_ERR_RET(pNewNode);
	pNewNode->data = iData;
	pNewNode->pNext = pWalk->pNext;
	pWalk->pNext = pNewNode;
	LFP_SLIST_CRIT("add node[%p] to the list ok!\n", pNewNode);
	return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_slist_insert_element_by_pos( LFP_SLIST_T *pList, 
																	LFP_INT32 iPos, 
																	LFP_INT32 iData)
* @brief 	  add a new node to the single list(before a specific position)
* @param[in]  LFP_SLIST_T *pList - the head of list
* @param[in]  LFP_INT32 iPos - the specific position
* @param[in]  LFP_INT32 iData - the data of the new node
* @param[out] LFP_NULL
* @note		  if the length of the list is smaller than iPos, add a new node at the end of the list
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_slist_insert_element_by_pos(LFP_SLIST_T *pList, LFP_INT32 iPos, LFP_INT32 iData)
{
	LFP_SLIST_T *pWalk = LFP_NULL;
	LFP_SLIST_T *pNewNode = LFP_NULL;
	LFP_INT32 iWalkCnt = 0;
	
	LFP_ASSERT_ERR_RET(pList);
	pWalk = pList;
	/* here we use pWalk->pNext to avoid traverse to the end */
	while(pWalk->pNext)
	{
		if(!pWalk->pNext)
		{
			break;
		}
		/* if iPos < 0, add the node to the end */
		if(iPos >= 0 && iWalkCnt >= iPos)
		{
			break;
		}
		iWalkCnt++;
		pWalk = pWalk->pNext;
	}
	/* Whether inserted in the middle or at the end, it is compatible */
	LFP_SLIST_NODE_MALLOC(&pNewNode);
	LFP_ASSERT_ERR_RET(pNewNode);
	pNewNode->data = iData;
	pNewNode->pNext = pWalk->pNext;	/*if pWalk is the last ,pWalk->pNext must be LFP_NULL */
	pWalk->pNext = pNewNode;
	LFP_SLIST_CRIT("add node[%p] to the list ok!\n", pNewNode);
	return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_slist_delete_element(LFP_SLIST_T *pList, LFP_SLIST_T *pNode)
* @brief 	  delete a node from the list
* @param[in]  LFP_SLIST_T *pList - the head of list
* @param[in]  LFP_SLIST_T *pNode - the element to be deleted
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_slist_delete_element(LFP_SLIST_T *pList, LFP_SLIST_T *pDelNode)
{	
	LFP_SLIST_T *pWalk = LFP_NULL;
	
	LFP_ASSERT_ERR_RET(pList && pDelNode);
	pWalk = pList;
	while(pWalk->pNext)
	{
		if(pWalk->pNext == pDelNode)
		{
			break;
		}
		pWalk = pWalk->pNext;
	}
	if(!pWalk->pNext)
	{
		LFP_SLIST_CRIT("there is no node[%p][data:%d] in the list\n", pDelNode, pDelNode->data);
		return LFP_OK; /* default delete ok .*/
	}
	pWalk->pNext = pWalk->pNext->pNext;
	LFP_SLIST_CRIT("delete node[%p] from the list ok!\n", pDelNode);
	LFP_SLIST_NODE_FREE(pDelNode);
	return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_slist_destroy(LFP_SLIST_T **pList)
* @brief 	  destroy the list
* @param[in]  LFP_SLIST_T *pList - the head of the list
* @param[out] LFP_NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_slist_destroy(LFP_SLIST_T **ppList)
{
	LFP_SLIST_T* pTmp = LFP_NULL;
	LFP_SLIST_T* pWalk = LFP_NULL;
	
	LFP_ASSERT_ERR_RET(ppList && *ppList);
	pWalk = *ppList;
	while(pWalk)
	{
		pTmp = pWalk;
		pWalk = pWalk->pNext;
		LFP_SLIST_NODE_FREE(pTmp);
	}
	*ppList = (LFP_SLIST_T*)LFP_NULL;
	return LFP_OK;
}

/*@fn		  LFP_STATIC LFP_INT32 lfp_slist_module_test(LFP_VOID)
* @brief 	  test entrance for the single list module.
* @param[in]  LFP_VOID
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_STATIC LFP_INT32 lfp_slist_module_test(LFP_VOID)
{
	LFP_INT32 iItem = 0;
	LFP_INT32 iRet = LFP_ERR;
	LFP_SLIST_T *pHead = LFP_NULL;
	LFP_SLIST_T *pNode = LFP_NULL;
	LFP_SLIST_T *pMid = LFP_NULL, *pTail = LFP_NULL;

	pHead = pNode = pMid = pTail = LFP_NULL;
	LFP_SLIST_CRIT("start testing module %s \n", LFP_SLIST_MODULE_NAME);
	/* 1. create a head node */
	if(LFP_OK != lfp_slist_create_head(&pHead))
	{
		LFP_SLIST_ERR("create list single head failed\n");
		return LFP_ERR;
	}
	LFP_SLIST_CRIT("the list head is[%p].\n", pHead);
	/* 2. add  LFP_SLIST_ADD_ELEM element to the list */

	if(LFP_OK != lfp_slist_add_element(pHead, LFP_SLIST_ADD_ELEM))
	{
		LFP_SLIST_ERR("add element to the list failed, addnum = %d\n", LFP_SLIST_ADD_ELEM);
		iRet = LFP_ERR;
		goto lfp_slist_exit;
	}
	pTail = pHead;
	while(pTail->pNext)
	{
		if(iItem == LFP_SLIST_ADD_ELEM / 2)
		{
			pMid = pTail->pNext;
			LFP_SLIST_CRIT("the middle element is[%p]!\n", pMid);
		}
		pTail = pTail->pNext;
		iItem++;
	}
	LFP_SLIST_CRIT("the tail element is[%p]!\n", pTail);

	/* 3. insert a node to the end */
	if(LFP_OK != lfp_slist_add_element(pHead, 1))
	{
		LFP_SLIST_ERR("insert a new node to the end err\n");
		iRet = LFP_ERR;
		goto lfp_slist_exit;
	}
	LFP_SLIST_CRIT("add element to the end of th list success!\n");
	
	/* 4. insert a node to the head */
	if(LFP_OK != lfp_slist_insert_element_by_pos(pHead, 0, 4*LFP_SLIST_ADD_ELEM))
	{
		LFP_SLIST_ERR("insert a to the head err\n");
		iRet = LFP_ERR;
		goto lfp_slist_exit;
	}
	LFP_SLIST_CRIT("add element to the head of th list success!\n");
	
	/* 5. insert a node to the mid */
	if(LFP_OK != lfp_slist_insert_element_by_node(pHead, pMid, 5*LFP_SLIST_ADD_ELEM))
	{
		LFP_SLIST_ERR("insert a node to the mid err\n");
		iRet = LFP_ERR;
		goto lfp_slist_exit;
	}
	LFP_SLIST_CRIT("add element to the mid of th list success!\n");
	
	LFP_ASSERT_ERR_RET(pHead);
	pNode = pHead->pNext;
	while(pNode)
	{
		LFP_SLIST_CRIT("list element[%p]\n", pNode);
		pTail = pNode;
		pNode = pNode->pNext;
	}
	pNode = pHead->pNext;	
	/* 6. delete the end node of the list */
	if(LFP_OK != lfp_slist_delete_element(pHead, pTail))
	{
		LFP_SLIST_ERR("delete a node[%p] err\n", pTail);
		iRet = LFP_ERR;
		goto lfp_slist_exit;
	}
	/* 7. delete the head node of the list */
	if(LFP_OK != lfp_slist_delete_element(pHead, pNode))
	{
		LFP_SLIST_ERR("delete a node[%p] err\n", pNode);
		iRet = LFP_ERR;
		goto lfp_slist_exit;
	}
	/* 8. delete the middle node of the list */
	if(LFP_OK != lfp_slist_delete_element(pHead, pMid))
	{
		LFP_SLIST_ERR("delete a node[%p] err\n", pMid);
		iRet = LFP_ERR;
		goto lfp_slist_exit;
	}
lfp_slist_exit:
	/* 9. destroy the single list */
	if(LFP_OK != lfp_slist_destroy(&pHead))
	{
		LFP_SLIST_ERR("destroy the single list err\n");
		return LFP_ERR;
	}
	while(pHead)
	{
		LFP_SLIST_ERR("list element[%p] still exist\n", pHead);
		pHead = pHead->pNext;
	}	
	LFP_SLIST_CRIT("testing %s module ok!\n", LFP_SLIST_MODULE_NAME);
	return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_slist_module_test_init(LFP_VOID)
* @brief 	  the single list test module main entrance.
* @param[in]  LFP_VOID
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_slist_module_test_init(LFP_VOID)
{
	LFP_MODULES_REGISTER_SIGN(LFP_SLIST_CRIT, LFP_SLIST_SIGN_OK);
	lfp_slist_module_test();
	return LFP_OK;
}

#endif
