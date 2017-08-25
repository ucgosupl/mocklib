/*
 * File:    utlib_malloc.h
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    25.08.2017
 */

#ifndef _UTLIB_MALLOC_H_
#define _UTLIB_MALLOC_H_

void* utlib_malloc(size_t size);
void utlib_free(void * mem);

void mock_malloc_init(void *ret);
int32_t mock_malloc_cnt_get(void);
size_t mock_malloc_arg_size_get(void);

void mock_free_init(void);
int32_t mock_free_cnt_get(void);
void * mock_free_arg_obj_get(void);

#endif /* _UTLIB_MALLOC_H_ */
