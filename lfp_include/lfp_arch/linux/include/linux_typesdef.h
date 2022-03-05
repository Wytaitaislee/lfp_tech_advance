/***
 * @FilePath: linux_typesdef.h
 * @Description: redefine the types on linux system, the header file in
 "include" should quote this header file directly.
 * @Author: wytaitaislee
 * @Date: 2021-08-27 23:29:52
 * @LastEditTime: 2022-03-05 21:22:38
 * @LastEditors: wytaitaislee
 * @Copyright 2022 wytaitaislee, All Rights Reserved.
 */

#ifndef __LINUX_TYPESDEF_H__
#define __LINUX_TYPESDEF_H__

#include <stddef.h>
#include <stdio.h>

#define __OS_NAME_LOWER linux_
#define __OS_NAME_UPPER LINUX_

typedef size_t LINUX_SIZE_T;
typedef ssize_t LINUX_SSIZE_T;
typedef FILE LINUX_FILE;
typedef off_t LINUX_OFF_T;

#endif /*end of __LINUX_TYPESDEF_H__ */