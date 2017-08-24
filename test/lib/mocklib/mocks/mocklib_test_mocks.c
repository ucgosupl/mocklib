/*
 * File:    mocklib_test_mocks.c
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    23.08.2017
 */

#include "unity_fixture.h"

#include <stdint.h>

#include "mocklib.h"
#include "mocklib_expfun.h"

#include "mocklib_test_mocks.h"

struct mocklib_mock_params
{
    int32_t expdata_destroy_cnt;
    mocklib_expdata_t expdata_destroy_arg_expdata;
    int32_t expdata_destroy_ret;
};

static struct mocklib_mock_params mock_params;

void mock_mocklib_expdata_destroy_init(int32_t ret)
{
    mock_params.expdata_destroy_cnt = 0;

    mock_params.expdata_destroy_arg_expdata = NULL;

    mock_params.expdata_destroy_ret = ret;
}

int32_t mock_mocklib_expdata_destroy_cnt_get(void)
{
    return mock_params.expdata_destroy_cnt;
}

mocklib_expdata_t mock_mocklib_expdata_destroy_arg_expdata_get(void)
{
    return mock_params.expdata_destroy_arg_expdata;
}

int32_t mocklib_expdata_destroy(mocklib_expdata_t expdata)
{
    mock_params.expdata_destroy_cnt++;

    mock_params.expdata_destroy_arg_expdata = expdata;

    return mock_params.expdata_destroy_ret;
}
