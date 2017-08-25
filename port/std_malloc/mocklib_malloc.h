/*
 * File:    mocklib_malloc.h
 * Author:  Maciej Gajdzica
 * Brief:   Definitions for malloc functions used by mock library.
 *
 * Date:    27.07.2017
 */

#ifndef _MOCKLIB_MALLOC_H_
#define _MOCKLIB_MALLOC_H_

#ifdef MOCKLIB_UNIT_TEST
#include "unity_fixture.h"
#endif

#define MOCKLIB_MALLOC(size)    malloc(size)
#define MOCKLIB_FREE(obj)       free(obj)

#endif /* _MOCKLIB_MALLOC_H_ */
