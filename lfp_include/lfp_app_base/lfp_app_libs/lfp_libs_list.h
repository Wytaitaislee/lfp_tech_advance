/***
 * @FilePath: lfp_libs_list.h
 * @Description: some common macros for linked list.
 * @Author: wytaitaislee
 * @Date: 2021-08-27 23:29:52
 * @LastEditTime: 2022-03-05 21:23:37
 * @LastEditors: wytaitaislee
 * @Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#ifndef __LFP_LIBS_LIST_H__
#define __LFP_LIBS_LIST_H__

#include "lfp_base.h"
/**
 The offset of the structure element relative to the starting
 address of the structure.
*/
#define LFP_OFFSETOF(type, member) ((size_t) & ((type*)0)->member)

/**
 * LFP_CONTAINER_OF - cast a member of a structure out to the containing
 * structure
 * @ptr:    the pointer to the member.
 * @type:   the type of the container struct this is embedded in.
 * @member: the name of the member within the struct.
 */
#define LFP_CONTAINER_OF(ptr, type, member)              \
  ({                                                     \
    const typeof(((type*)0)->member)* __mptr = (ptr);    \
    (type*)((char*)(__mptr)-LFP_OFFSETOF(type, member)); \
    ;                                                    \
  })

/**
 * get the structure entity where the linked list element is located.
 */
#define LFP_LIST_ENTRY(ptr, type, member) LFP_CONTAINER_OF(ptr, type, member)

/**
 * LFP_LIST_FOR_EACH	-	iterate over a list(from head)
 * @list_loop:	the &struct "list_head" to use as a loop cursor.
 * @head:	    the head for your list.
 */
#define LFP_LIST_FOR_EACH(list_loop, head)             \
  for (list_loop = (head)->pNext; list_loop != (head); \
       list_loop = list_loop->pNext)

/**
 * LFP_LIST_FOR_EACH_PREV	-	iterate over a list(from tail)
 * @list_loop:	the &struct "list_head" to use as a loop cursor.
 * @head:	    the head for your list.
 */
#define LFP_LIST_FOR_EACH_PREV(list_loop, head)        \
  for (list_loop = (head)->pPrev; list_loop != (head); \
       list_loop = (list_loop)->pPrev)

/**
 * LFP_LIST_FIRST_ENTRY - get the first entry element from a list
 * @list_head:	the list head to take the element from.
 * @type:	    the type of the struct this is embedded in.
 * @member:	    the name of the "list_head" within the struct.
 * Note, that list is expected to be not empty.
 */
#define LFP_LIST_FIRST_ENTRY(list_head, type, member) \
  LFP_LIST_ENTRY((list_head)->pNext, type, member)

/**
 * list_next_entry - get the next element in list
 * @entry:	the type * to cursor
 * @member:	the name of the list_head within the struct.
 */
#define LFP_LIST_NEXT_ENTRY(entry, member) \
  LFP_LIST_ENTRY((entry)->member.pNext, typeof(*(entry)), member)

/**
 * LFP_LIST_FOR_EACH_ENTRY	-	iterate over a entry(from the head
 * entry)
 * @list_loop:	the &struct "list_head" to use as a loop cursor.
 * @head:	    the head for your list.
 */
#define LFP_LIST_FOR_EACH_ENTRY(entry_loop, list_head, member)             \
  for (entry_loop =                                                        \
           LFP_LIST_FIRST_ENTRY(list_head, typeof(*(entry_loop)), member); \
       &entry_loop->member != (list_head);                                 \
       entry_loop = LFP_LIST_NEXT_ENTRY(entry_loop, member))

#endif /*__LFP_LIBS_LIST_H__*/