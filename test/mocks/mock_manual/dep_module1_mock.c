/*
 * File:    dep_module1_mock.c
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    26.07.2017
 */

#include <stdint.h>
#include <string.h>

#include "unity_fixture.h"
#include "mocklib_utlib_defines.h"
#include "utlib_checks.h"

#include "mocklib.h"
#include "mocklib_expfun.h"
#include "mocklib_malloc.h"

#include "dep_module1/dep_module1.h"
#include "dep_module1_mock.h"

enum
{
    MOCK_FUNTYPE_NONE,
    MOCK_FUNTYPE_dep_module1_no_args_no_ret,
    MOCK_FUNTYPE_dep_module1_no_args_ret,
    MOCK_FUNTYPE_dep_module1_one_arg_no_ret,
    MOCK_FUNTYPE_dep_module1_more_args_no_ret,
    MOCK_FUNTYPE_dep_module1_one_arg_ret,
    MOCK_FUNTYPE_dep_module1_more_args_ret,
};

struct dep_module1_dep_no_args_no_ret_params
{
    mocklib_mode_t mode;
    int32_t call_cnt;
};

/* No internal expdata for function with no arguments and no return value. */

struct dep_module1_dep_no_args_ret_params
{
    mocklib_mode_t mode;
    int32_t call_cnt;

    int32_t ret;
};

struct dep_module1_dep_no_args_ret_expdata_internal
{
    int32_t ret;
};

struct dep_module1_dep_one_arg_no_ret_params
{
    mocklib_mode_t mode;
    int32_t call_cnt;
};

struct dep_module1_dep_one_arg_no_ret_expdata_internal
{
    uint16_t arg1;
};

struct dep_module1_dep_more_args_no_ret_params
{
    mocklib_mode_t mode;
    int32_t call_cnt;
};

struct dep_module1_dep_more_args_no_ret_expdata_internal
{
    int32_t arg1;
    uint8_t arg2;
};

struct dep_module1_dep_one_arg_ret_params
{
    mocklib_mode_t mode;
    int32_t call_cnt;

    uint32_t ret;
};

struct dep_module1_dep_one_arg_ret_expdata_internal
{
    uint32_t arg1;

    uint32_t ret;
};

struct dep_module1_dep_more_args_ret_params
{
    mocklib_mode_t mode;
    int32_t call_cnt;

    int8_t ret;
};

struct dep_module1_dep_more_args_ret_expdata_internal
{
    int8_t arg1;
    int16_t arg2;

    int8_t ret;
};

static struct dep_module1_dep_no_args_no_ret_params dep_module1_dep_no_args_no_ret_params;
static struct dep_module1_dep_no_args_ret_params dep_module1_dep_no_args_ret_params;
static struct dep_module1_dep_one_arg_no_ret_params dep_module1_dep_one_arg_no_ret_params;
static struct dep_module1_dep_more_args_no_ret_params dep_module1_dep_more_args_no_ret_params;
static struct dep_module1_dep_one_arg_ret_params dep_module1_dep_one_arg_ret_params;
static struct dep_module1_dep_more_args_ret_params dep_module1_dep_more_args_ret_params;

mocklib_expdata_t mocklib_helper_expdata_create_and_check(void)
{
    mocklib_expdata_t expdata = NULL;

    expdata = mocklib_expdata_create();

    if (NULL == expdata)
    {
        UTLIB_TEST_FAIL_MSG("Cannot create expected function data");
    }

    return expdata;
}

void * mocklib_helper_internal_create_and_check(size_t size)
{
    void *internal = NULL;

    internal = MOCKLIB_MALLOC(size);

     if (NULL == internal)
     {
         UTLIB_TEST_FAIL_MSG("Cannot create expected function internal data");
     }

    return internal;
}

mocklib_expdata_t mocklib_helper_expdata_get_and_check(void)
{
    mocklib_expdata_t expdata;

    expdata = mocklib_exp_get();
    if (NULL == expdata)
    {
        UTLIB_TEST_FAIL_MSG("All expected functions already called");
    }

    return expdata;
}

void mocklib_helper_funtype_check(mocklib_expdata_t expdata, mocklib_funtype_t funtype_exp)
{
    if (funtype_exp != mocklib_expdata_funtype_get(expdata))
    {
        UTLIB_TEST_FAIL_MSG("Function called out of order");
    }
}

void * mocklib_helper_internal_get_and_check(mocklib_expdata_t expdata)
{
    void *internal;

    internal = mocklib_expdata_internal_get(expdata);
    if (NULL == internal)
    {
        UTLIB_TEST_FAIL_MSG("Missing expected function data");
    }

    return internal;
}

void mocklib_helper_err_if_mode_not_trace(mocklib_mode_t mode)
{
    if (MOCKLIB_MODE_TRACE != mode)
    {
        UTLIB_TEST_FAIL_MSG("Expect function shall be called only in trace mode");
    }
}

void dep_module1_mock_init(void)
{
    /* Reset all mock internal data */
    memset(&dep_module1_dep_no_args_no_ret_params, 0, sizeof(struct dep_module1_dep_no_args_no_ret_params));
    memset(&dep_module1_dep_no_args_ret_params, 0, sizeof(struct dep_module1_dep_no_args_ret_params));
    memset(&dep_module1_dep_one_arg_no_ret_params, 0, sizeof(struct dep_module1_dep_one_arg_no_ret_params));
    memset(&dep_module1_dep_more_args_no_ret_params, 0, sizeof(struct dep_module1_dep_more_args_no_ret_params));
    memset(&dep_module1_dep_one_arg_ret_params, 0, sizeof(struct dep_module1_dep_one_arg_ret_params));
    memset(&dep_module1_dep_more_args_ret_params, 0, sizeof(struct dep_module1_dep_more_args_ret_params));
}

void dep_module1_mock_dep_no_args_no_ret_config(mocklib_mode_t mode)
{
    dep_module1_dep_no_args_no_ret_params.mode = mode;
}

void dep_module1_mock_dep_no_args_no_ret_expect(void)
{
    mocklib_expdata_t expdata = NULL;

    mocklib_helper_err_if_mode_not_trace(dep_module1_dep_no_args_no_ret_params.mode);

    expdata = mocklib_helper_expdata_create_and_check();
    mocklib_expdata_funtype_set(expdata, MOCK_FUNTYPE_dep_module1_no_args_no_ret);

    mocklib_exp_set(expdata);
}

int32_t dep_module1_mock_dep_no_args_no_ret_cnt_get(void)
{
    return dep_module1_dep_no_args_no_ret_params.call_cnt;
}

void dep_no_args_no_ret(void)
{
    mocklib_expdata_t expdata = NULL;

    dep_module1_dep_no_args_no_ret_params.call_cnt++;

    if (MOCKLIB_MODE_TRACE == dep_module1_dep_no_args_no_ret_params.mode)
    {
        expdata = mocklib_helper_expdata_get_and_check();

        mocklib_helper_funtype_check(expdata, MOCK_FUNTYPE_dep_module1_no_args_no_ret);
    }
}

void dep_module1_mock_dep_no_args_ret_config(mocklib_mode_t mode, int32_t ret)
{
    dep_module1_dep_no_args_ret_params.mode = mode;
    dep_module1_dep_no_args_ret_params.ret = ret;
}

void dep_module1_mock_dep_no_args_ret_expect(int32_t ret)
{
    mocklib_expdata_t expdata = NULL;
    struct dep_module1_dep_no_args_ret_expdata_internal *internal = NULL;

    mocklib_helper_err_if_mode_not_trace(dep_module1_dep_no_args_ret_params.mode);

    expdata = mocklib_helper_expdata_create_and_check();
    mocklib_expdata_funtype_set(expdata, MOCK_FUNTYPE_dep_module1_no_args_ret);

    /* Set expected function call parameters */
    internal = mocklib_helper_internal_create_and_check(sizeof(struct dep_module1_dep_no_args_ret_expdata_internal));
    internal->ret = ret;
    mocklib_expdata_internal_set(expdata, internal);

    mocklib_exp_set(expdata);
}

int32_t dep_module1_mock_dep_no_args_ret_cnt_get(void)
{
    return dep_module1_dep_no_args_ret_params.call_cnt;
}

int32_t dep_no_args_ret(void)
{
    int32_t retval;
    mocklib_expdata_t expdata = NULL;
    struct dep_module1_dep_no_args_ret_expdata_internal *internal = NULL;

    dep_module1_dep_no_args_ret_params.call_cnt++;

    if (MOCKLIB_MODE_BASIC == dep_module1_dep_no_args_ret_params.mode)
    {
        retval = dep_module1_dep_no_args_ret_params.ret;
    }
    else if (MOCKLIB_MODE_TRACE == dep_module1_dep_no_args_ret_params.mode)
    {
        expdata = mocklib_helper_expdata_get_and_check();

        mocklib_helper_funtype_check(expdata, MOCK_FUNTYPE_dep_module1_no_args_ret);

        internal = mocklib_helper_internal_get_and_check(expdata);

        retval = internal->ret;
    }
    else
    {
        //error
    }

    return retval;
}

void dep_module1_mock_dep_one_arg_no_ret_config(mocklib_mode_t mode)
{
    dep_module1_dep_one_arg_no_ret_params.mode = mode;
}

void dep_module1_mock_dep_one_arg_no_ret_expect(uint16_t arg1)
{
    mocklib_expdata_t expdata = NULL;
    struct dep_module1_dep_one_arg_no_ret_expdata_internal *internal = NULL;

    mocklib_helper_err_if_mode_not_trace(dep_module1_dep_one_arg_no_ret_params.mode);

    expdata = mocklib_helper_expdata_create_and_check();
    mocklib_expdata_funtype_set(expdata, MOCK_FUNTYPE_dep_module1_one_arg_no_ret);

    /* Set expected function call parameters */
    internal = mocklib_helper_internal_create_and_check(sizeof(struct dep_module1_dep_one_arg_no_ret_expdata_internal));
    internal->arg1 = arg1;
    mocklib_expdata_internal_set(expdata, internal);

    mocklib_exp_set(expdata);
}

int32_t dep_module1_mock_dep_one_arg_no_ret_cnt_get(void)
{
    return dep_module1_dep_one_arg_no_ret_params.call_cnt;
}

void dep_one_arg_no_ret(uint16_t arg1)
{
    mocklib_expdata_t expdata = NULL;
    struct dep_module1_dep_one_arg_no_ret_expdata_internal *internal = NULL;

    dep_module1_dep_one_arg_no_ret_params.call_cnt++;

    if (MOCKLIB_MODE_TRACE == dep_module1_dep_one_arg_no_ret_params.mode)
    {
        expdata = mocklib_helper_expdata_get_and_check();

        mocklib_helper_funtype_check(expdata, MOCK_FUNTYPE_dep_module1_one_arg_no_ret);

        internal = mocklib_helper_internal_get_and_check(expdata);

        UTLIB_ASSERT_EQUAL(internal->arg1, arg1);
    }
}

void dep_module1_mock_dep_more_args_no_ret_config(mocklib_mode_t mode)
{
    dep_module1_dep_more_args_no_ret_params.mode = mode;
}

void dep_module1_mock_dep_more_args_no_ret_expect(int32_t arg1, uint8_t arg2)
{
    mocklib_expdata_t expdata = NULL;
    struct dep_module1_dep_more_args_no_ret_expdata_internal *internal = NULL;

    mocklib_helper_err_if_mode_not_trace(dep_module1_dep_more_args_no_ret_params.mode);

    expdata = mocklib_helper_expdata_create_and_check();
    mocklib_expdata_funtype_set(expdata, MOCK_FUNTYPE_dep_module1_more_args_no_ret);

    /* Set expected function call parameters */
    internal = mocklib_helper_internal_create_and_check(sizeof(struct dep_module1_dep_more_args_no_ret_expdata_internal));
    internal->arg1 = arg1;
    internal->arg2 = arg2;
    mocklib_expdata_internal_set(expdata, internal);

    mocklib_exp_set(expdata);
}

int32_t dep_module1_mock_dep_more_args_no_ret_cnt_get(void)
{
    return dep_module1_dep_more_args_no_ret_params.call_cnt;
}

void dep_more_args_no_ret(int32_t arg1, uint8_t arg2)
{
    mocklib_expdata_t expdata = NULL;
    struct dep_module1_dep_more_args_no_ret_expdata_internal *internal = NULL;

    dep_module1_dep_more_args_no_ret_params.call_cnt++;

    if (MOCKLIB_MODE_TRACE == dep_module1_dep_more_args_no_ret_params.mode)
    {
        expdata = mocklib_helper_expdata_get_and_check();

        mocklib_helper_funtype_check(expdata, MOCK_FUNTYPE_dep_module1_more_args_no_ret);

        internal = mocklib_helper_internal_get_and_check(expdata);

        UTLIB_ASSERT_EQUAL(internal->arg1, arg1);
        UTLIB_ASSERT_EQUAL(internal->arg2, arg2);
    }
}

void dep_module1_mock_dep_one_arg_ret_config(mocklib_mode_t mode, uint32_t ret)
{
    dep_module1_dep_one_arg_ret_params.mode = mode;
    dep_module1_dep_one_arg_ret_params.ret = ret;
}

void dep_module1_mock_dep_one_arg_ret_expect(uint32_t arg1, uint32_t ret)
{
    mocklib_expdata_t expdata = NULL;
    struct dep_module1_dep_one_arg_ret_expdata_internal *internal = NULL;

    mocklib_helper_err_if_mode_not_trace(dep_module1_dep_one_arg_ret_params.mode);

    expdata = mocklib_helper_expdata_create_and_check();
    mocklib_expdata_funtype_set(expdata, MOCK_FUNTYPE_dep_module1_one_arg_ret);

    /* Set expected function call parameters */
    internal = mocklib_helper_internal_create_and_check(sizeof(struct dep_module1_dep_one_arg_ret_expdata_internal));
    internal->arg1 = arg1;
    internal->ret = ret;
    mocklib_expdata_internal_set(expdata, internal);

    mocklib_exp_set(expdata);
}

int32_t dep_module1_mock_dep_one_arg_ret_cnt_get(void)
{
    return dep_module1_dep_one_arg_ret_params.call_cnt;
}

uint32_t dep_one_arg_ret(uint32_t arg1)
{
    uint32_t retval;
    mocklib_expdata_t expdata = NULL;
    struct dep_module1_dep_one_arg_ret_expdata_internal *internal = NULL;

    dep_module1_dep_one_arg_ret_params.call_cnt++;

    if (MOCKLIB_MODE_BASIC == dep_module1_dep_one_arg_ret_params.mode)
    {
        retval = dep_module1_dep_one_arg_ret_params.ret;
    }
    else if (MOCKLIB_MODE_TRACE == dep_module1_dep_one_arg_ret_params.mode)
    {
        expdata = mocklib_helper_expdata_get_and_check();

        mocklib_helper_funtype_check(expdata, MOCK_FUNTYPE_dep_module1_one_arg_ret);

        internal = mocklib_helper_internal_get_and_check(expdata);

        UTLIB_ASSERT_EQUAL(internal->arg1, arg1);
        retval = internal->ret;
    }
    else
    {
        //error
    }

    return retval;
}

void dep_module1_mock_dep_more_args_ret_config(mocklib_mode_t mode, int8_t ret)
{
    dep_module1_dep_more_args_ret_params.mode = mode;
    dep_module1_dep_more_args_ret_params.ret = ret;
}

void dep_module1_mock_dep_more_args_ret_expect(int8_t arg1, int16_t arg2, uint32_t ret)
{
    mocklib_expdata_t expdata = NULL;
    struct dep_module1_dep_more_args_ret_expdata_internal *internal = NULL;

    mocklib_helper_err_if_mode_not_trace(dep_module1_dep_more_args_ret_params.mode);

    expdata = mocklib_helper_expdata_create_and_check();
    mocklib_expdata_funtype_set(expdata, MOCK_FUNTYPE_dep_module1_more_args_ret);

    /* Set expected function call parameters */
    internal = mocklib_helper_internal_create_and_check(sizeof(struct dep_module1_dep_more_args_ret_expdata_internal));
    internal->arg1 = arg1;
    internal->arg2 = arg2;
    internal->ret = ret;
    mocklib_expdata_internal_set(expdata, internal);

    mocklib_exp_set(expdata);
}

int32_t dep_module1_mock_dep_more_args_ret_cnt_get(void)
{
    return dep_module1_dep_more_args_ret_params.call_cnt;
}

int8_t dep_more_args_ret(int8_t arg1, int16_t arg2)
{
    uint32_t retval;
    mocklib_expdata_t expdata = NULL;
    struct dep_module1_dep_more_args_ret_expdata_internal *internal = NULL;

    dep_module1_dep_more_args_ret_params.call_cnt++;

    if (MOCKLIB_MODE_BASIC == dep_module1_dep_more_args_ret_params.mode)
    {
        retval = dep_module1_dep_more_args_ret_params.ret;
    }
    else if (MOCKLIB_MODE_TRACE == dep_module1_dep_more_args_ret_params.mode)
    {
        expdata = mocklib_helper_expdata_get_and_check();

        mocklib_helper_funtype_check(expdata, MOCK_FUNTYPE_dep_module1_more_args_ret);

        internal = mocklib_helper_internal_get_and_check(expdata);

        UTLIB_ASSERT_EQUAL(internal->arg1, arg1);
        UTLIB_ASSERT_EQUAL(internal->arg2, arg2);
        retval = internal->ret;
    }
    else
    {
        //error
    }

    return retval;
}
