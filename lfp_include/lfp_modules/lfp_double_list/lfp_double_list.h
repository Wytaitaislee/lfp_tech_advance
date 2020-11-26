/************************************************************************************
File name: lfp_double_list.h
Description: Double linked list module data structure definition.
Author: wytaitaislee
Version: V1.0.0
Date: 2019-11-17
History: 1. create file. -- 2019-11-17
		 2. refact at 2020-05-16 , interface becomes more compatible.
************************************************************************************/

#ifndef __LFP_DOUBLE_LIST_H__
#define __LFP_DOUBLE_LIST_H__

#ifdef LFP_DOUBLE_LIST_MODULE

#include "lfp_base.h"
#include "lfp_util_logs.h"

#define LFP_DOUBLE_LIST_MODULE_NAME     "double list"
#define LFP_DOUBLE_LIST_SIGN_OK    		"lfp double list register successfully!"
#define LFP_DOUBLE_LIST_SIGN_ERR   		"lfp double list register failed!"

#define LFP_DOUBLE_LIST_ADD_ELEM (10)

#define LFP_DOUBLE_LIST_CRIT(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_CRIT, UTIL_MODULE_DOUBLE_LIST, MASK_DOUBLE_LIST, __VA_ARGS__)
#define LFP_DOUBLE_LIST_ERR(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_ERR, UTIL_MODULE_DOUBLE_LIST, MASK_DOUBLE_LIST, __VA_ARGS__)
#define LFP_DOUBLE_LIST_INFO(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_INFO, UTIL_MODULE_DOUBLE_LIST, MASK_DOUBLE_LIST, __VA_ARGS__) 

/*double list structure definition */
typedef struct lfp_double_list_t
{
	LFP_INT32 data;
	struct lfp_double_list_t *pPrev;
	struct lfp_double_list_t *pNext;
}LFP_DOUBLE_LIST_T;

/*@fn		  LFP_INT32 lfp_double_list_create_head(struct LFP_DOUBLE_LIST_T** ppList)
* @brief 	  create the head node of double list
* @param[in]  the ptr of the head ptr whom pointer to the double list
* @param[out] the same as param[in]
* @return     LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_double_list_create_head(LFP_DOUBLE_LIST_T** ppList);

/*@fn		  LFP_INT32 lfp_double_list_add_element(LFP_DOUBLE_LIST_T *pList, LFP_UINT32 uiNum)
* @brief 	  add a new node to the end of the double list
* @param[in]  LFP_DOUBLE_LIST *pList - the head of the list
* @param[in]  LFP_INT32 uiNum - the num of the nodes to be added
* @param[out] LFP_NULL
* @return     LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_double_list_add_element(LFP_DOUBLE_LIST_T *pList, LFP_UINT32 uiNum);

/*@fn		  LFP_INT32 lfp_double_list_append_node(LFP_DOUBLE_LIST_T *pList, LFP_DOUBLE_LIST_T *pAddNode)
* @brief 	  append a new node to the end of the double list
* @param[in]  LFP_DOUBLE_LIST *pList - the head of the list
* @param[in]  LFP_DOUBLE_LIST_T *pAddNode - the node to be added
* @param[out] LFP_NULL
* @return     LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_double_list_append_node(LFP_DOUBLE_LIST_T *pList, LFP_DOUBLE_LIST_T *pAddNode);

/*@fn		  LFP_INT32 lfp_double_list_insert_element_by_node(LFP_DOUBLE_LIST_T *pList, 
															LFP_DOUBLE_LIST_T* pNode, LFP_INT32 iData)
* @brief      insert a new node at the specific position to the double list
* @param[in]  LFP_DOUBLE_LIST_T *pList - the head of list
* @param[in]  LFP_INT32 iPos - the pos to be insert
* @param[in]  LFP_INT32 iData - the data to add
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_double_list_insert_element_by_pos(LFP_DOUBLE_LIST_T *pList, LFP_INT32 iPos, LFP_INT32 iData);

/*@fn		  LFP_INT32 lfp_double_list_insert_element_by_node(LFP_DOUBLE_LIST_T *pList, 
															LFP_DOUBLE_LIST_T* pNode, LFP_INT32 iData)
* @brief      insert a new node before the specific node to the double list
* @param[in]  LFP_DOUBLE_LIST_T *pList - the head of list
* @param[in]  LFP_DOUBLE_LIST_T *pNode - the next element of the inserted element
* @param[in]  LFP_INT32 iData - the data to add
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_double_list_insert_element_by_node(LFP_DOUBLE_LIST_T *pList, LFP_DOUBLE_LIST_T *pNode, LFP_INT32 iData);

/*@fn		  LFP_INT32 lfp_double_list_delete_element(LFP_DOUBLE_LIST_T *pHead, LFP_DOUBLE_LIST_T *pDelNode)
* @brief 	  delete a node from the list
* @param[in]  LFP_DOUBLE_LIST_T *pList - the head of list
* @param[in]  LFP_DOUBLE_LIST_T *pDelNode - th node to be deleted
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_double_list_delete_element(LFP_DOUBLE_LIST_T *pList, LFP_DOUBLE_LIST_T *pDelNode);


/*@fn		  LFP_INT32 lfp_double_list_destroy(LFP_DOUBLE_LIST_T **ppList)
* @brief 	  destroy the list
* @param[in]  LFP_DOUBLE_LIST_T **ppList - the address of the head of the list
* @param[out] LFP_NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_double_list_destroy(LFP_DOUBLE_LIST_T **pList);

/*@fn		  LFP_INT32 lfp_double_list_module_test_init(LFP_VOID)
* @brief 	  the entrance of the double list module.
* @param[in]  LFP_VOID
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_double_list_module_test_init(LFP_VOID);

#endif

#endif /* end of __LFP_DOUBLE_LIST_H__ */