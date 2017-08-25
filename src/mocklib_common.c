/*
 * File:    mocklib_common.c
 * Author:  Maciej Gajdzica
 * Brief:   Functions used internally by generated mocks.
 *
 * Date:    13.08.2017
 */

#include <stdint.h>
#include <stddef.h>

#include "mocklib_utlib_defines.h"

#include "mocklib.h"
#include "mocklib_expfun.h"
#include "mocklib_malloc.h"
#include "mocklib_common.h"

mocklib_expdata_t mocklib_common_expdata_create_and_check(void)
{
    mocklib_expdata_t expdata = NULL;

    expdata = mocklib_expdata_create();

    if (NULL == expdata)
    {
        UTLIB_TEST_FAIL_MSG("Cannot create expected function data");
    }

    return expdata;
}

void * mocklib_common_internal_create_and_check(size_t size)
{
    void *internal = NULL;

    internal = MOCKLIB_MALLOC(size);

     if (NULL == internal)
     {
         UTLIB_TEST_FAIL_MSG("Cannot create expected function internal data");
     }

    return internal;
}

void mocklib_common_funtype_check(mocklib_expdata_t expdata, mocklib_funtype_t funtype_exp)
{
    if (funtype_exp != mocklib_expdata_funtype_get(expdata))
    {
        UTLIB_TEST_FAIL_MSG("Function called out of order");
    }
}

void * mocklib_common_internal_get_and_check(mocklib_expdata_t expdata)
{
    void *internal;

    internal = mocklib_expdata_internal_get(expdata);
    if (NULL == internal)
    {
        UTLIB_TEST_FAIL_MSG("Missing expected function data");
    }

    return internal;
}

void mocklib_common_err_if_mode_not_trace(mocklib_mode_t mode)
{
    if (MOCKLIB_MODE_TRACE != mode)
    {
        UTLIB_TEST_FAIL_MSG("Expect function shall be called only in trace mode");
    }
}
