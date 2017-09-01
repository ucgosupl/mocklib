/*
 * File:    utlib_malloc.c
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    25.08.2017
 */

#include <stddef.h>
#include "unity_fixture.h"

#include "utlib_malloc.h"

struct malloc_mock_params
{
    int32_t malloc_cnt;
    size_t malloc_arg_size;
    void *malloc_ret;

    int32_t free_cnt;
    void *free_arg_obj;
};

static struct malloc_mock_params mock_params;

void mock_malloc_init(void *ret)
{
    mock_params.malloc_cnt = 0;

    mock_params.malloc_arg_size = 0;

    mock_params.malloc_ret = ret;
}

int32_t mock_malloc_cnt_get(void)
{
    return mock_params.malloc_cnt;
}

size_t mock_malloc_arg_size_get(void)
{
    return mock_params.malloc_arg_size;
}

void* utlib_malloc(size_t size)
{
    mock_params.malloc_cnt++;

    mock_params.malloc_arg_size = size;

    return mock_params.malloc_ret;
}

void mock_free_init(void)
{
    mock_params.free_cnt = 0;

    mock_params.free_arg_obj = NULL;
}

int32_t mock_free_cnt_get(void)
{
    return mock_params.free_cnt;
}

void * mock_free_arg_obj_get(void)
{
    return mock_params.free_arg_obj;
}

void utlib_free(void * mem)
{
    mock_params.free_cnt++;

    mock_params.free_arg_obj = mem;
}
