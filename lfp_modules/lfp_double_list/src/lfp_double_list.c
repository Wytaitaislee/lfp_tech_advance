/************************************************************************************
File name: lfp_double_list.c
Description: Double linked list module implementation.
Author: wytaitaislee
Version: V1.0.0
Date: 2020-05-05
History: 1. create file. -- 2020-05-05
         2. refact at 2020-05-16
************************************************************************************/
#ifdef LFP_DOUBLE_LIST_MODULE

#include "lfp_double_list.h"

#define LFP_DOUBLE_LIST_NODE_MALLOC(ppNode)                                         \
do                                                                                  \
{                                                                                   \
    *ppNode = (LFP_DOUBLE_LIST_T *)LFP_MALLOC(sizeof(LFP_DOUBLE_LIST_T));           \
    (*ppNode)->pNext = LFP_NULL;                                                    \
    (*ppNode)->pPrev = LFP_NULL;                                                    \
    (*ppNode)->data = 0;                                                            \
} while (0);

#define LFP_DOUBLE_LIST_NODE_FREE(pNode)                                            \
do                                                                                  \
{                                                                                   \
    pNode->pNext = LFP_NULL;                                                        \
    pNode->pPrev = LFP_NULL;                                                        \
    pNode->data = 0;                                                                \
} while (0);

/*@fn		  LFP_INT32 lfp_double_list_create_head(struct LFP_DOUBLE_LIST_T** ppList)
* @brief 	  create the head node of double list
* @param[in]  the ptr of the head ptr whom pointer to the double list
* @param[out] the same as param[in]
* @return     LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_double_list_create_head(LFP_DOUBLE_LIST_T **ppList)
{
    LFP_DOUBLE_LIST_NODE_MALLOC(ppList);
    LFP_ASSERT_ERR_RET(ppList && *ppList);
    return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_double_list_insert_element_by_pos(LFP_DOUBLE_LIST_T *pList, 
                                                            LFP_INT32 iPos, LFP_INT32 iData)
* @brief      insert a new node at the specific position to the double list
* @param[in]  LFP_DOUBLE_LIST_T *pList - the head of list
* @param[in]  LFP_INT32 iPos - the pos to be insert
* @param[in]  LFP_INT32 iData - the data to add
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_double_list_insert_element_by_pos(LFP_DOUBLE_LIST_T *pList, LFP_INT32 iPos, LFP_INT32 iData)
{
    LFP_INT32 iWalkCnt = 0;
    LFP_DOUBLE_LIST_T *pWalk = LFP_NULL;
    LFP_DOUBLE_LIST_T *pPrev = LFP_NULL;
    LFP_DOUBLE_LIST_T *pNode = LFP_NULL;

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
    }
    LFP_DOUBLE_LIST_NODE_MALLOC(&pNode);
    LFP_ASSERT_ERR_RET(pNode);
    pNode->data = iData;
    if(!pWalk->pNext)
    {
        pWalk->pNext = pNode;
        pNode->pPrev = pPrev;
        return LFP_OK;
    }
    pNode->pNext = pWalk->pNext;
    pNode->pPrev = pWalk;
    pWalk->pNext->pPrev = pNode;
    pWalk->pNext = pNode;
    LFP_DOUBLE_LIST_CRIT("add node[%p] to the list ok!\n", pNode);
    return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_double_list_insert_element_by_node(LFP_DOUBLE_LIST_T *pList, 
															    LFP_DOUBLE_LIST_T* pNode, LFP_INT32 iData)
* @brief      insert a new node before the specific node to the double list
* @param[in]  LFP_DOUBLE_LIST_T *pHead - the head of list
* @param[in]  LFP_DOUBLE_LIST_T *pNode - the next element of the inserted element
* @param[in]  LFP_INT32 iData - the data to add
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_double_list_insert_element_by_node(LFP_DOUBLE_LIST_T *pList, LFP_DOUBLE_LIST_T *pNode, LFP_INT32 iData)
{
    LFP_DOUBLE_LIST_T *pWalk = LFP_NULL;
    LFP_DOUBLE_LIST_T *pNewNode = LFP_NULL;

    LFP_ASSERT_ERR_RET(pList && pNode);
    pWalk = pList;
    while(pWalk->pNext)
    {
        if(pWalk->pNext == pNode)
        {
            break;
        }
        pWalk = pWalk->pNext;
    }
    if(!pWalk->pNext)
    {
        LFP_DOUBLE_LIST_ERR("insert new node before node[%p, data:%d] err!\n", pNode, pNode->data);
        return LFP_ERR;
    }
    LFP_DOUBLE_LIST_NODE_MALLOC(&pNewNode);
    LFP_ASSERT_ERR_RET(pNewNode);
    pNewNode->data = iData;
    pNewNode->pNext = pNode;
    pNewNode->pPrev = pWalk;
    pWalk->pNext = pNewNode;
    pNode->pPrev = pNewNode;
    LFP_DOUBLE_LIST_CRIT("add node[%p] to the list ok!\n", pNewNode);
    return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_double_list_add_element(LFP_DOUBLE_LIST_T *pList, LFP_UINT32 uiNum)
* @brief 	  add a new node to the end of the double list
* @param[in]  LFP_DOUBLE_LIST *pList - the head of the list
* @param[in]  LFP_INT32 uiNum - the num of the nodes to be added
* @param[out] LFP_NULL
* @return     LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_double_list_add_element(LFP_DOUBLE_LIST_T *pList, LFP_UINT32 uiNum)
{
    LFP_DOUBLE_LIST_T *pNode = LFP_NULL;
    LFP_DOUBLE_LIST_T *pWalk = LFP_NULL;
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
        LFP_DOUBLE_LIST_NODE_MALLOC(&pNode);
        pWalk->pNext = pNode;
        pNode->pPrev = pWalk;
        pWalk = pWalk->pNext;
        LFP_DOUBLE_LIST_CRIT("add node[%p] to the list ok!\n", pNode);
    }
    
    return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_double_list_append_node(LFP_DOUBLE_LIST_T *pList, LFP_DOUBLE_LIST_T *pAddNode)
* @brief 	  append a new node to the end of the double list
* @param[in]  LFP_DOUBLE_LIST *pList - the head of the list
* @param[in]  LFP_DOUBLE_LIST_T *pAddNode - the node to be added
* @param[out] LFP_NULL
* @return     LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_double_list_append_node(LFP_DOUBLE_LIST_T *pList, LFP_DOUBLE_LIST_T *pAddNode)
{
    LFP_DOUBLE_LIST_T *pWalk = LFP_NULL;

    LFP_ASSERT_ERR_RET(pList);
    pWalk = pList;
    /* move to the end of the list */
    while(pWalk->pNext)
    {
        pWalk = pWalk->pNext;
    }
    pWalk->pNext = pAddNode;
    pAddNode->pPrev = pWalk;
    LFP_DOUBLE_LIST_CRIT("append node[%p] to the list ok!\n", pAddNode);
    return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_double_list_delete_element(LFP_DOUBLE_LIST_T *pHead, LFP_DOUBLE_LIST_T *pDelNode)
* @brief 	  delete a node from the list
* @param[in]  LFP_DOUBLE_LIST_T *pHead - the head of list
* @param[in]  LFP_DOUBLE_LIST_T *pDelNode - th node to be deleted
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_double_list_delete_element(LFP_DOUBLE_LIST_T *pList, LFP_DOUBLE_LIST_T *pDelNode)
{
    LFP_DOUBLE_LIST_T * pWalk = LFP_NULL;

    LFP_ASSERT_ERR_RET(pList && pDelNode);
    pWalk = pList->pNext;
    while(pWalk)
    {
        if(pWalk == pDelNode)
        {
            break;
        }
        pWalk = pWalk->pNext;
    }
    if(!pWalk)
    {
        LFP_DOUBLE_LIST_CRIT("there is no node[%p][data:%d] in the list\n", pDelNode, pDelNode->data);
        return LFP_OK;
    }
    if(!pWalk->pNext)
    {
        pWalk->pNext = LFP_NULL;
    }
    else
    {
        pWalk->pNext->pPrev = pWalk->pPrev;
        pWalk->pPrev->pNext = pWalk->pNext;
    }
    LFP_DOUBLE_LIST_CRIT("delete node[%p] from the list ok!\n", pWalk);
    LFP_DOUBLE_LIST_NODE_FREE(pWalk);
    return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_double_list_destroy(LFP_DOUBLE_LIST_T **ppList)
* @brief 	  destroy the list
* @param[in]  LFP_DOUBLE_LIST_T **ppList - the address of the head of the list
* @param[out] LFP_NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_double_list_destroy(LFP_DOUBLE_LIST_T **pList)
{
	LFP_DOUBLE_LIST_T *pTmp = LFP_NULL;
	LFP_DOUBLE_LIST_T *pWalk = LFP_NULL;
	
	LFP_ASSERT_ERR_RET(pList && *pList);
	pWalk = *pList;
	while(pWalk)
	{
		pTmp = pWalk;
		pWalk = pWalk->pNext;
		LFP_DOUBLE_LIST_NODE_FREE(pTmp);
	}	
	*pList = LFP_NULL;
	return LFP_OK;
}

/*@fn		  LFP_STATIC LFP_INT32 lfp_double_list_module_test(LFP_VOID)
* @brief 	  test entrance for the double list module.
* @param[in]  LFP_VOID
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_STATIC LFP_INT32 lfp_double_list_module_test(LFP_VOID)
{
	LFP_INT32 iItem = 0;
    LFP_INT32 iRet = LFP_ERR;
	LFP_DOUBLE_LIST_T *pHead = LFP_NULL;
	LFP_DOUBLE_LIST_T *pNode = LFP_NULL;
	LFP_DOUBLE_LIST_T *pMid = LFP_NULL, *pTail = LFP_NULL;

	pHead = pNode = pMid = pTail = LFP_NULL;
	LFP_DOUBLE_LIST_CRIT("start testing module %s \n", LFP_DOUBLE_LIST_MODULE_NAME);
	/* 1. create a head node */
	if(LFP_OK != lfp_double_list_create_head(&pHead))
	{
		LFP_DOUBLE_LIST_ERR("create double list head failed\n");
		return LFP_ERR;
	}
	LFP_DOUBLE_LIST_CRIT("the list head is[%p].\n", pHead);
	/* 2. add  LFP_DOUBLE_LIST_ADD_ELEM element to the list */
	if(LFP_OK != lfp_double_list_add_element(pHead, LFP_DOUBLE_LIST_ADD_ELEM))
	{
		LFP_DOUBLE_LIST_ERR("add element to the list failed, addnum = %d\n", LFP_DOUBLE_LIST_ADD_ELEM);
		iRet = LFP_ERR;
		goto lfp_double_list_exit;
	}
	pTail = pHead;
	while(pTail->pNext)
	{
		if(iItem == LFP_DOUBLE_LIST_ADD_ELEM / 2)
		{
			pMid = pTail->pNext;
			LFP_DOUBLE_LIST_CRIT("the middle element is[%p]!\n", pMid);
		}
		pTail = pTail->pNext;
		iItem++;
	}
	LFP_DOUBLE_LIST_CRIT("the tail element is[%p]!\n", pTail);

	/* 3. insert a node to the end */
	if(LFP_OK != lfp_double_list_add_element(pHead, 1))
	{
		LFP_DOUBLE_LIST_ERR("insert a new node to the end err\n");
		iRet = LFP_ERR;
		goto lfp_double_list_exit;
	}
	LFP_DOUBLE_LIST_CRIT("add element to the end of th list success!\n");
	
	/* 4. insert a node to the head */
	if(LFP_OK != lfp_double_list_insert_element_by_pos(pHead, 0, 4*LFP_DOUBLE_LIST_ADD_ELEM))
	{
		LFP_DOUBLE_LIST_ERR("insert a to the head err\n");
		iRet = LFP_ERR;
		goto lfp_double_list_exit;
	}
	LFP_DOUBLE_LIST_CRIT("add element to the head of th list success!\n");
	
	/* 5. insert a node to the mid */
	if(LFP_OK != lfp_double_list_insert_element_by_node(pHead, pMid, 5*LFP_DOUBLE_LIST_ADD_ELEM))
	{
		LFP_DOUBLE_LIST_ERR("insert a node to the mid err\n");
		iRet = LFP_ERR;
		goto lfp_double_list_exit;
	}
	LFP_DOUBLE_LIST_CRIT("add element to the mid of th list success!\n");
	
	LFP_ASSERT_ERR_RET(pHead);
	pNode = pHead->pNext;
	while(pNode)
	{
		LFP_DOUBLE_LIST_CRIT("list element[%p]\n", pNode);
		pTail = pNode;
		pNode = pNode->pNext;
	}
	pNode = pHead->pNext;	
	/* 6. delete the end node of the list */
	if(LFP_OK != lfp_double_list_delete_element(pHead, pTail))
	{
		LFP_DOUBLE_LIST_ERR("delete a node[%p] err\n", pTail);
		iRet = LFP_ERR;
		goto lfp_double_list_exit;
	}
	/* 7. delete the head node of the list */
	if(LFP_OK != lfp_double_list_delete_element(pHead, pNode))
	{
		LFP_DOUBLE_LIST_ERR("delete a node[%p] err\n", pNode);
		iRet = LFP_ERR;
		goto lfp_double_list_exit;
	}
	/* 8. delete the middle node of the list */
	if(LFP_OK != lfp_double_list_delete_element(pHead, pMid))
	{
		LFP_DOUBLE_LIST_ERR("delete a node[%p] err\n", pMid);
		iRet = LFP_ERR;
		goto lfp_double_list_exit;
	}
lfp_double_list_exit:
	/* 9. destroy the double list */
	if(LFP_OK != lfp_double_list_destroy(&pHead))
	{
		LFP_DOUBLE_LIST_ERR("destroy the double list err\n");
		return LFP_ERR;
	}
	while(pHead)
	{
		LFP_DOUBLE_LIST_ERR("list element[%p] still exist\n", pHead);
		pHead = pHead->pNext;
	}	
	LFP_DOUBLE_LIST_CRIT("testing %s module ok!\n", LFP_DOUBLE_LIST_MODULE_NAME);
	return LFP_OK;
}

/*@fn		  LFP_INT32 lfp_double_list_module_test_init(LFP_VOID)
* @brief 	  the double list test module main entrance.
* @param[in]  LFP_VOID
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_double_list_module_test_init(LFP_VOID)
{
	LFP_MODULES_REGISTER_SIGN(LFP_DOUBLE_LIST_CRIT, LFP_DOUBLE_LIST_SIGN_OK);
	lfp_double_list_module_test();
	return LFP_OK;
}

#endif