/*
 * @fileName: lfp_libs_slist.h
 * @Description: Singly linked list package library.
 * @Author: wytaitaislee
 * @Date: 2020-08-16 16:05:58
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-04-04 18:33:05
*/

#ifndef __LFP_SLIST_H__
#define __LFP_SLIST_H__

#ifdef LFP_LIBS_SLIST

#include "lfp_base.h"

#define LFP_SLIST_MODULE_NAME     "single list"
#define LFP_SLIST_SIGN_OK    		"lfp single list register successfully!"
#define LFP_SLIST_SIGN_ERR   		"lfp single list register failed!"

#define LFP_SLIST_ADD_ELEM (10)

#define LFP_SLIST_CRIT(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_CRIT, UTIL_MODULE_SLIST, MASK_SLIST, __VA_ARGS__)
#define LFP_SLIST_ERR(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_ERR, UTIL_MODULE_SLIST, MASK_SLIST, __VA_ARGS__)
#define LFP_SLIST_INFO(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_INFO, UTIL_MODULE_SLIST, MASK_SLIST, __VA_ARGS__)  

/*single list structure definition */
typedef struct lfp_slist_t
{
	LFP_INT32 data;
	struct lfp_slist_t *pNext;
}LFP_SLIST_T;

/*@fn		  LFP_INT32 lfp_slist_create_head(LFP_SLIST_T** ppList)
* @brief 	  create the head node of single list
* @param[in]  the ptr of the head ptr whom pointer to the single list
* @param[out] the same as param[in]
* @return     LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_slist_create_head(LFP_SLIST_T **ppList);

/*@fn		  LFP_INT32 lfp_slist_add_element(LFP_SLIST_T *pHead, LFP_UINT32 uiNum)
* @brief 	  add a specific num of nodes to the end of the single list
* @param[in]  LFP_SLIST_T *pHead - the head of the list
* @param[in]  LFP_UINT32 uiNum - the num of the specific nodes
* @param[out] NULL
* @return     LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_slist_add_element(LFP_SLIST_T *pList, LFP_UINT32 uiNum);


/*@fn		  LFP_INT32 lfp_slist_append_node(LFP_SLIST_T *pList, LFP_SLIST_T *pAddNode)
* @brief 	  append a new node to the end of the single list
* @param[in]  LFP_SLIST_T *pList - the head of the list
* @param[in]  LFP_SLIST_T *pAddNode - the node to be added
* @param[out] LFP_NULL
* @return     LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_slist_append_node(LFP_SLIST_T *pList, LFP_SLIST_T *pAddNode);

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
LFP_INT32 lfp_slist_insert_element_by_node(LFP_SLIST_T *pList, LFP_SLIST_T *pNode, LFP_INT32 iData);

/*@fn		  LFP_INT32 lfp_slist_insert_element_by_pos( LFP_SLIST_T *pList, 
								   LFP_INT32 iPos, 
								   LFP_INT32 iData)														LFP_INT32 iData)
* @brief 	  add a new node to the single list(before a specific position)
* @param[in]  LFP_SLIST_T *pList - the head of list
* @param[in]  LFP_INT32 iPos - the specific position
* @param[in]  LFP_INT32 iData - the data of the new node
* @param[out] LFP_NULL
* @note		  if the length of the list is smaller than iPos, add a new node at the end of the list
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_slist_insert_element_by_pos(LFP_SLIST_T *pList, LFP_INT32 iPos, LFP_INT32 iData);

/*@fn		  LFP_INT32 lfp_slist_delete_element(LFP_SLIST_T *pList, LFP_SLIST_T *pNode)
* @brief 	  delete a node from the list
* @param[in]  LFP_SLIST_T *pList - the head of list
* @param[in]  LFP_SLIST_T *pNode - the element to be deleted
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_slist_delete_element(LFP_SLIST_T *pList, LFP_SLIST_T *pNode);

/*@fn		  LFP_INT32 lfp_slist_destroy(LFP_SLIST_T *ppList)
* @brief 	  destroy the list
* @param[in]  LFP_SLIST_T **ppList - the address of the head of the list
* @param[out] LFP_NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_slist_destroy(LFP_SLIST_T **ppList);

#endif

#endif	/* end of __LFP_SLIST_H__ */
