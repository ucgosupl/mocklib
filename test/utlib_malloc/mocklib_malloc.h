/*
 * File:    mocklib_malloc.h
 * Author:  Maciej Gajdzica
 * Brief:   Definitions for malloc functions used by mock library.
 *
 * Date:    27.07.2017
 */

#ifndef _MOCKLIB_MALLOC_H_
#define _MOCKLIB_MALLOC_H_

#include "utlib_malloc.h"
#define MOCKLIB_MALLOC(size)    utlib_malloc(size)
#define MOCKLIB_FREE(obj)       utlib_free(obj)

#endif /* _MOCKLIB_MALLOC_H_ */
