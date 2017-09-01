/*
 * File:    mocklib_expfun.c
 * Author:  Maciej Gajdzica
 * Brief:   Functions handling expected function data.
 *
 * Date:    27.07.2017
 */

#include <stddef.h>
#include <stdint.h>

#include "mocklib.h"
#include "mocklib_internal.h"
#include "mocklib_expfun.h"
#include "mocklib_malloc.h"
#include "mocklib_utlib_defines.h"

struct expfun_record
{
    mocklib_funtype_t funtype;
    void *internal;
};

mocklib_expdata_t mocklib_expdata_create(void)
{
    mocklib_expdata_t ret = NULL;

    ret = MOCKLIB_MALLOC(sizeof(struct expfun_record));

    if (NULL == ret)
    {
        return NULL;
    }

    ret->internal = NULL;
    ret->funtype = 0;

    return ret;
}

void mocklib_expdata_destroy(mocklib_expdata_t expdata)
{
    if (NULL == expdata)
    {
        return;
    }

    if (NULL != expdata->internal)
    {
        MOCKLIB_FREE(expdata->internal);
    }

    MOCKLIB_FREE(expdata);

    return;
}

void mocklib_expdata_funtype_set(mocklib_expdata_t expdata, mocklib_funtype_t type)
{
    if (NULL == expdata)
    {
        UTLIB_TEST_FAIL_MSG("Invalid expected function data");
        return;
    }

    expdata->funtype = type;
}

mocklib_funtype_t mocklib_expdata_funtype_get(mocklib_expdata_t expdata)
{
    if (NULL == expdata)
    {
        UTLIB_TEST_FAIL_MSG("Invalid expected function data");
        return NULL;
    }

    return expdata->funtype;
}

void mocklib_expdata_internal_set(mocklib_expdata_t expdata, void *internal)
{
    if (NULL == expdata)
    {
        UTLIB_TEST_FAIL_MSG("Invalid expected function data");
        return;
    }

    expdata->internal = internal;
}

void * mocklib_expdata_internal_get(mocklib_expdata_t expdata)
{
    if (NULL == expdata)
    {
        UTLIB_TEST_FAIL_MSG("Invalid expected function data");
        return NULL;
    }

    return expdata->internal;
}
