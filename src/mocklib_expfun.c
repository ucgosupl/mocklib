/*
 * File:    mocklib_expfun.c
 * Author:  mgajdzica
 * Brief:   Short brief.
 *
 * Date:    27.07.2017
 */

#include <stddef.h>
#include <stdint.h>

#include "mocklib.h"
#include "mocklib_malloc.h"
#include "mocklib_expfun.h"

struct expfun_record
{
    mocklib_funtype_t funtype;
    void *internal;
};

mocklib_expdata_t mocklib_expdata_create(void)
{
    mocklib_expdata_t ret = NULL;

    ret = MOCKLIB_MALLOC(sizeof(struct expfun_record));
    ret->internal = NULL;
    ret->funtype = 0;

    return ret;
}

int32_t mocklib_expdata_destroy(mocklib_expdata_t expdata)
{
    if (NULL != expdata->internal)
    {
        MOCKLIB_FREE(expdata->internal);
    }

    MOCKLIB_FREE(expdata);

    return 0;
}

int32_t mocklib_expdata_funtype_set(mocklib_expdata_t expdata, mocklib_funtype_t type)
{
    expdata->funtype = type;

    return 0;
}

mocklib_funtype_t mocklib_expdata_funtype_get(mocklib_expdata_t expdata)
{
    return expdata->funtype;
}

int32_t mocklib_expdata_internal_set(mocklib_expdata_t expdata, void *internal)
{
    expdata->internal = internal;

    return 0;
}

void * mocklib_expdata_internal_get(mocklib_expdata_t expdata)
{
    return expdata->internal;
}
