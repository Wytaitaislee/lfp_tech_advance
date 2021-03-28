/*
 * @fileName: lfp_libs_dlist.h
 * @Description: Doubly linked list package library.
 * @Author: wytaitaislee
 * @Date: 2020-08-16 16:05:58
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-03-28 17:13:47
 */

#ifndef __LFP_DLIST_H__
#define __LFP_DLIST_H__

#ifdef LFP_DLIST_MODULE

#include "lfp_base.h"

#define LFP_DLIST_MODULE_NAME     "double list"
#define LFP_DLIST_SIGN_OK    		"lfp double list register successfully!"
#define LFP_DLIST_SIGN_ERR   		"lfp double list register failed!"

#define LFP_DLIST_ADD_ELEM (10)

#define LFP_DLIST_CRIT(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_CRIT, UTIL_MODULE_DLIST, MASK_DLIST, __VA_ARGS__)
#define LFP_DLIST_ERR(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_ERR, UTIL_MODULE_DLIST, MASK_DLIST, __VA_ARGS__)
#define LFP_DLIST_INFO(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_INFO, UTIL_MODULE_DLIST, MASK_DLIST, __VA_ARGS__) 

/*double list structure definition */
typedef struct lfp_dlist_t
{
	LFP_INT32 data;
	struct LFP_DLIST_T *pPrev;
	struct LFP_DLIST_T *pNext;
}LFP_DLIST_T;

/*@fn		  LFP_INT32 lfp_double_list_create_head(struct LFP_DLIST_T** ppList)
* @brief 	  create the head node of double list
* @param[in]  the ptr of the head ptr whom pointer to the double list
* @param[out] the same as param[in]
* @return     LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_double_list_create_head(LFP_DLIST_T** ppList);

/*@fn		  LFP_INT32 lfp_double_list_add_element(LFP_DLIST_T *pList, LFP_UINT32 uiNum)
* @brief 	  add a new node to the end of the double list
* @param[in]  LFP_DOUBLE_LIST *pList - the head of the list
* @param[in]  LFP_INT32 uiNum - the num of the nodes to be added
* @param[out] LFP_NULL
* @return     LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_double_list_add_element(LFP_DLIST_T *pList, LFP_UINT32 uiNum);

/*@fn		  LFP_INT32 lfp_double_list_append_node(LFP_DLIST_T *pList, LFP_DLIST_T *pAddNode)
* @brief 	  append a new node to the end of the double list
* @param[in]  LFP_DOUBLE_LIST *pList - the head of the list
* @param[in]  LFP_DLIST_T *pAddNode - the node to be added
* @param[out] LFP_NULL
* @return     LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_double_list_append_node(LFP_DLIST_T *pList, LFP_DLIST_T *pAddNode);

/*@fn		  LFP_INT32 lfp_double_list_insert_element_by_node(LFP_DLIST_T *pList, 
															LFP_DLIST_T* pNode, LFP_INT32 iData)
* @brief      insert a new node at the specific position to the double list
* @param[in]  LFP_DLIST_T *pList - the head of list
* @param[in]  LFP_INT32 iPos - the pos to be insert
* @param[in]  LFP_INT32 iData - the data to add
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_double_list_insert_element_by_pos(LFP_DLIST_T *pList, LFP_INT32 iPos, LFP_INT32 iData);

/*@fn		  LFP_INT32 lfp_double_list_insert_element_by_node(LFP_DLIST_T *pList, 
															LFP_DLIST_T* pNode, LFP_INT32 iData)
* @brief      insert a new node before the specific node to the double list
* @param[in]  LFP_DLIST_T *pList - the head of list
* @param[in]  LFP_DLIST_T *pNode - the next element of the inserted element
* @param[in]  LFP_INT32 iData - the data to add
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_double_list_insert_element_by_node(LFP_DLIST_T *pList, LFP_DLIST_T *pNode, LFP_INT32 iData);

/*@fn		  LFP_INT32 lfp_double_list_delete_element(LFP_DLIST_T *pHead, LFP_DLIST_T *pDelNode)
* @brief 	  delete a node from the list
* @param[in]  LFP_DLIST_T *pList - the head of list
* @param[in]  LFP_DLIST_T *pDelNode - th node to be deleted
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_double_list_delete_element(LFP_DLIST_T *pList, LFP_DLIST_T *pDelNode);


/*@fn		  LFP_INT32 lfp_double_list_destroy(LFP_DLIST_T **ppList)
* @brief 	  destroy the list
* @param[in]  LFP_DLIST_T **ppList - the address of the head of the list
* @param[out] LFP_NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_double_list_destroy(LFP_DLIST_T **pList);


#endif

#endif /* end of __LFP_DLIST_H__ */