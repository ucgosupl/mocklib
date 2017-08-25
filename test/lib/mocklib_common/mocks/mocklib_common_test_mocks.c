/*
 * File:    mocklib_common_test_mocks.c
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    25.08.2017
 */

#include "unity_fixture.h"

#include <stdint.h>
#include <stddef.h>

#include "mocklib.h"
#include "mocklib_expfun.h"

#include "mocklib_common_test_mocks.h"

struct mocklib_common_mock_params
{
    int32_t expdata_create_cnt;
    mocklib_expdata_t expdata_create_ret;

    int32_t expdata_funtype_get_cnt;
    mocklib_expdata_t expdata_funtype_get_arg_expdata;
    mocklib_funtype_t expdata_funtype_get_ret;

    int32_t expdata_internal_get_cnt;
    mocklib_expdata_t expdata_internal_get_arg_expdata;
    void * expdata_internal_get_ret;
};

static struct mocklib_common_mock_params mock_params;

void mock_mocklib_expdata_create_init(mocklib_expdata_t ret)
{
    mock_params.expdata_create_cnt = 0;

    mock_params.expdata_create_ret = ret;
}

int32_t mock_mocklib_expdata_create_cnt_get(void)
{
    return mock_params.expdata_create_cnt;
}

mocklib_expdata_t mocklib_expdata_create(void)
{
    mock_params.expdata_create_cnt++;

    return mock_params.expdata_create_ret;
}

void mock_mocklib_expdata_funtype_get_init(mocklib_funtype_t ret)
{
    mock_params.expdata_funtype_get_cnt = 0;

    mock_params.expdata_funtype_get_arg_expdata = NULL;

    mock_params.expdata_funtype_get_ret = ret;
}

int32_t mock_mocklib_expdata_funtype_get_cnt_get(void)
{
    return mock_params.expdata_funtype_get_cnt;
}

mocklib_expdata_t mock_mocklib_expdata_funtype_get_arg_expdata_get(void)
{
    return mock_params.expdata_funtype_get_arg_expdata;
}

mocklib_funtype_t mocklib_expdata_funtype_get(mocklib_expdata_t expdata)
{
    mock_params.expdata_funtype_get_cnt++;

    mock_params.expdata_funtype_get_arg_expdata = expdata;

    return mock_params.expdata_funtype_get_ret;
}

void mock_mocklib_expdata_internal_get_init(void * ret)
{
    mock_params.expdata_internal_get_cnt = 0;

    mock_params.expdata_internal_get_arg_expdata = NULL;

    mock_params.expdata_internal_get_ret = ret;
}

int32_t mock_mocklib_expdata_internal_get_cnt_get(void)
{
    return mock_params.expdata_internal_get_cnt;
}

mocklib_expdata_t mock_mocklib_expdata_internal_get_arg_expdata_get(void)
{
    return mock_params.expdata_internal_get_arg_expdata;
}

void * mocklib_expdata_internal_get(mocklib_expdata_t expdata)
{
    mock_params.expdata_internal_get_cnt++;

    mock_params.expdata_internal_get_arg_expdata = expdata;

    return mock_params.expdata_internal_get_ret;
}
