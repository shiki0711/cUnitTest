/*
 * cmock_utility.h
 *
 *  Created on: 2016/6/14
 *      Author: emit.yanfeng@gmail.com
 */

#ifndef INCLUDE_CMOCK_UTILITY_H_
#define INCLUDE_CMOCK_UTILITY_H_

#define CMOCK_USE_LIBC

#ifdef CMOCK_USE_LIBC
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define cmock_fprintf   fprintf
#define cmock_strcmp    strcmp
#define cmock_memset    memset
#define cmock_memcpy    memcpy
#define cmock_exit      exit
#define cmock_offsetof  offsetof
#else
/* TODO:
 * cmock_fprintf
 * cmock_strcmp
 * cmock_memset
 * cmock_memcpy
 * cmock_exit
 * cmock_offsetof
 *  */
#endif

#define CMOCK_ALLOC_STACK(T) ((T*)(char[sizeof(T)]){0})

#define CMOCK_INTERNAL_MOCK_TYPE(funcname) \
    T_CMOCK_INTERNAL_##funcname

#define CMOCK_ALLOC_MOCK_TYPE_STACK(funcname) \
    CMOCK_ALLOC_STACK(CMOCK_INTERNAL_MOCK_TYPE(funcname))


#define _CMOCK_CONCAT(a, b)         a##b
#define CMOCK_CONCAT(a, b)          _CMOCK_CONCAT(a, b)
#define CMOCK_ANONYMOUS_VAR(var)    CMOCK_CONCAT(var, __LINE__)
#define $(var)                      CMOCK_ANONYMOUS_VAR(var)


#endif /* INCLUDE_CMOCK_UTILITY_H_ */
