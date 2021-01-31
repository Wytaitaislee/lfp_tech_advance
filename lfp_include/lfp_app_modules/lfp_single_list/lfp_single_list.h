/************************************************************************************
File name: lfp_single_list.h
Description: Single linked list module data structure definition.
Author: wytaitaislee
Date: 2019-11-17
History: 1. create file. -- 2019-11-17
************************************************************************************/

#ifndef __LFP_LIST_SINGLE_H__
#define __LFP_LIST_SINGLE_H__

#ifdef LFP_SINGLE_LIST_MODULE

#include "lfp_base.h"

#define LFP_SINGLE_LIST_MODULE_NAME     "single list"
#define LFP_SINGLE_LIST_SIGN_OK    		"lfp single list register successfully!"
#define LFP_SINGLE_LIST_SIGN_ERR   		"lfp single list register failed!"

#define LFP_SINGLE_LIST_ADD_ELEM (10)

#define LFP_SINGLE_LIST_CRIT(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_CRIT, UTIL_MODULE_SINGLE_LIST, MASK_SINGLE_LIST, __VA_ARGS__)
#define LFP_SINGLE_LIST_ERR(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_ERR, UTIL_MODULE_SINGLE_LIST, MASK_SINGLE_LIST, __VA_ARGS__)
#define LFP_SINGLE_LIST_INFO(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_INFO, UTIL_MODULE_SINGLE_LIST, MASK_SINGLE_LIST, __VA_ARGS__)  

/*single list structure definition */
typedef struct lfp_single_list_t
{
	LFP_INT32 data;
	struct lfp_single_list_t *pNext;
}LFP_SINGLE_LIST_T;

/*@fn		  LFP_INT32 lfp_single_list_create_head(LFP_SINGLE_LIST_T** ppList)
* @brief 	  create the head node of single list
* @param[in]  the ptr of the head ptr whom pointer to the single list
* @param[out] the same as param[in]
* @return     LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_single_list_create_head(LFP_SINGLE_LIST_T **ppList);

/*@fn		  LFP_INT32 lfp_single_list_add_element(LFP_SINGLE_LIST_T *pHead, LFP_UINT32 uiNum)
* @brief 	  add a specific num of nodes to the end of the single list
* @param[in]  LFP_SINGLE_LIST_T *pHead - the head of the list
* @param[in]  LFP_UINT32 uiNum - the num of the specific nodes
* @param[out] NULL
* @return     LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_single_list_add_element(LFP_SINGLE_LIST_T *pList, LFP_UINT32 uiNum);


/*@fn		  LFP_INT32 lfp_single_list_append_node(LFP_SINGLE_LIST_T *pList, LFP_SINGLE_LIST_T *pAddNode)
* @brief 	  append a new node to the end of the single list
* @param[in]  LFP_SINGLE_LIST_T *pList - the head of the list
* @param[in]  LFP_SINGLE_LIST_T *pAddNode - the node to be added
* @param[out] LFP_NULL
* @return     LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_single_list_append_node(LFP_SINGLE_LIST_T *pList, LFP_SINGLE_LIST_T *pAddNode);

/*@fn		  LFP_INT32 lfp_single_list_insert_element_by_node( LFP_SINGLE_LIST_T *pList, 
			   					    LFP_SINGLE_LIST_T *pPrev, 
                        					    LFP_INT32 iData)
* @brief 	  add a new node to the single list(before a specific node)
* @param[in]  LFP_SINGLE_LIST_T *pList - the head of list
* @param[in]  LFP_SINGLE_LIST_T *pPrev - the previous element of the inserted element
* @param[in]  LFP_INT32 iData - the data of the new node
* @param[out] LFP_NULL
* @note		  if *pNode does not exist in the list, return LFP_ERR
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_single_list_insert_element_by_node(LFP_SINGLE_LIST_T *pList, LFP_SINGLE_LIST_T *pNode, LFP_INT32 iData);

/*@fn		  LFP_INT32 lfp_single_list_insert_element_by_pos( LFP_SINGLE_LIST_T *pList, 
								   LFP_INT32 iPos, 
								   LFP_INT32 iData)														LFP_INT32 iData)
* @brief 	  add a new node to the single list(before a specific position)
* @param[in]  LFP_SINGLE_LIST_T *pList - the head of list
* @param[in]  LFP_INT32 iPos - the specific position
* @param[in]  LFP_INT32 iData - the data of the new node
* @param[out] LFP_NULL
* @note		  if the length of the list is smaller than iPos, add a new node at the end of the list
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_single_list_insert_element_by_pos(LFP_SINGLE_LIST_T *pList, LFP_INT32 iPos, LFP_INT32 iData);

/*@fn		  LFP_INT32 lfp_single_list_delete_element(LFP_SINGLE_LIST_T *pList, LFP_SINGLE_LIST_T *pNode)
* @brief 	  delete a node from the list
* @param[in]  LFP_SINGLE_LIST_T *pList - the head of list
* @param[in]  LFP_SINGLE_LIST_T *pNode - the element to be deleted
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_single_list_delete_element(LFP_SINGLE_LIST_T *pList, LFP_SINGLE_LIST_T *pNode);

/*@fn		  LFP_INT32 lfp_single_list_destroy(LFP_SINGLE_LIST_T *ppList)
* @brief 	  destroy the list
* @param[in]  LFP_SINGLE_LIST_T **ppList - the address of the head of the list
* @param[out] LFP_NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_single_list_destroy(LFP_SINGLE_LIST_T **ppList);

#endif

#endif
