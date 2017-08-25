/*
 * File:    mocklib_malloc.h
 * Author:  Maciej Gajdzica
 * Brief:   Definitions for malloc functions used by mock library.
 *
 * Date:    27.07.2017
 */

#ifndef _MOCKLIB_MALLOC_H_
#define _MOCKLIB_MALLOC_H_

#include "unity_fixture.h"
#define MOCKLIB_MALLOC(size)    unity_malloc(size)
#define MOCKLIB_FREE(obj)       unity_free(obj)

#endif /* _MOCKLIB_MALLOC_H_ */
