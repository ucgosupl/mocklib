/*
 * File:    mocklib_malloc.h
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    27.07.2017
 */

#ifndef _MOCKLIB_MALLOC_H_
#define _MOCKLIB_MALLOC_H_

//#include <stdlib.h>
#include "unity_fixture.h"
#define MOCKLIB_MALLOC(size)    malloc(size)
#define MOCKLIB_FREE(obj)       free(obj)

#endif /* _MOCKLIB_MALLOC_H_ */
