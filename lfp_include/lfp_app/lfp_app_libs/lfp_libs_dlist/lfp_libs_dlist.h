/*
 * @fileName: lfp_libs_dlist.h
 * @Description: Doubly linked list package library.
 * @Author: wytaitaislee
 * @Date: 2020-08-16 16:05:58
 * @LastEditors: wytaitaislee
 * @LastEditTime: 2021-08-22 10:35:30
 */

#ifndef __LFP_DLIST_H__
#define __LFP_DLIST_H__

#ifdef LFP_LIBS_DLIST

#include "lfp_base.h"

#define LFP_DLIST_MODULE_NAME       "double list"
#define LFP_DLIST_SIGN_OK    		"lfp double list register successfully!"
#define LFP_DLIST_SIGN_ERR   		"lfp double list register failed!"

#define LFP_DLIST_CRIT(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_CRIT, UTIL_MODULE_DLIST, MASK_DLIST, __VA_ARGS__)
#define LFP_DLIST_ERR(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_ERR, UTIL_MODULE_DLIST, MASK_DLIST, __VA_ARGS__)
#define LFP_DLIST_INFO(...)   \
        LFP_UTIL_BASE(UTIL_LEVEL_INFO, UTIL_MODULE_DLIST, MASK_DLIST, __VA_ARGS__) 

/*double list structure definition */
typedef struct lfp_dlist_t
{
	struct lfp_dlist_t *pPrev;
	struct lfp_dlist_t *pNext;
}LFP_DLIST_T;

/*@fn         LFP_INT32 lfp_dlist_init(struct LFP_DLIST_T** ppList)
* @brief      create the head node of double list
* @param[in]  the ptr of the head ptr whom pointer to the double list
* @param[out] the same as param[in]
* @return     LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_dlist_init(LFP_DLIST_T** ppList);

/*@fn		  LFP_INT32 lfp_dlist_add(LFP_DLIST_T *pList, LFP_DLIST_T *pNewNode)
* @brief      Insert a new node after the specified head.
* @param[in]  LFP_DLIST_T *pList - the head of list
* @param[in]  LFP_DLIST_T *pNewNode - new node to be added
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_dlist_add(LFP_DLIST_T *pList, LFP_DLIST_T *pNewNode);

/*@fn		  LFP_INT32 lfp_dlist_add_tail(LFP_DLIST_T *pList, LFP_DLIST_T *pNewNode)
* @brief      Insert a new node before the specified head.
* @param[in]  LFP_DLIST_T *pList - the head of list
* @param[in]  LFP_DLIST_T *pNewNode - new node to be added
* @param[out] NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_dlist_add_tail(LFP_DLIST_T *pList, LFP_DLIST_T *pNewNode);

/*@fn		  LFP_INT32 lfp_dlist_delete(LFP_DLIST_T *pDelNode)
* @brief 	  delete a node from the list
* @param[in]  LFP_DLIST_T *pDelNode - the node to be deleted
* @param[out] LFP_NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_dlist_delete(LFP_DLIST_T *pList, LFP_DLIST_T *pDelNode);

/*@fn		  LFP_INT32 lfp_dlist_destroy(LFP_DLIST_T *pList)
* @brief 	  destroy the list
* @param[in]  LFP_DLIST_T *pList - the address of the head of the list
* @param[out] LFP_NULL
* @return	  LFP_OK/LFP_ERR
*/
LFP_INT32 lfp_dlist_destroy(LFP_DLIST_T *pList);

#endif

#endif /* end of __LFP_DLIST_H__ */