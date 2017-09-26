/* 
 * File:    mocklib_common_test.c
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    25.08.2017
 */

#include "unity_fixture.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "mocklib.h"
#include "mocklib_internal.h"
#include "mocklib_common.h"

#include "mocks/mocklib_common_test_mocks.h"
#include "utlib_checks.h"
#include "utlib_malloc.h"

TEST_GROUP(mocklib_common);

TEST_SETUP(mocklib_common)
{
    utlib_test_fail_msg_init("Test fail not expected");
}

TEST_TEAR_DOWN(mocklib_common)
{

}


TEST(mocklib_common, expdata_cc_create_called)
{
    mocklib_expdata_t expdata;

    expdata = (mocklib_expdata_t)5;
    mock_mocklib_expdata_create_init(expdata);

    mocklib_common_expdata_create_and_check();

    TEST_ASSERT_EQUAL(1, mock_mocklib_expdata_create_cnt_get());
}

TEST(mocklib_common, expdata_cc_ret)
{
    mocklib_expdata_t expdata;

    expdata = (mocklib_expdata_t)5;
    mock_mocklib_expdata_create_init(expdata);

    TEST_ASSERT_EQUAL(expdata, mocklib_common_expdata_create_and_check());

    expdata = (mocklib_expdata_t)15;
    mock_mocklib_expdata_create_init(expdata);

    TEST_ASSERT_EQUAL(expdata, mocklib_common_expdata_create_and_check());
}

TEST(mocklib_common, expdata_cc_fail_when_null)
{
    mock_mocklib_expdata_create_init(NULL);
    utlib_test_fail_msg_init("Cannot create expected function data");

    mocklib_common_expdata_create_and_check();

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocklib_common, internal_cc_malloc_arg)
{
    size_t size;
    void *internal;

    internal = (void *)5;
    size = 50;
    mock_malloc_init(internal);

    mocklib_common_internal_create_and_check(size);

    TEST_ASSERT_EQUAL(1, mock_malloc_cnt_get());
    TEST_ASSERT_EQUAL(size, mock_malloc_arg_size_get());

    size = 150;
    mock_malloc_init(internal);

    mocklib_common_internal_create_and_check(size);

    TEST_ASSERT_EQUAL(size, mock_malloc_arg_size_get());
}

TEST(mocklib_common, internal_cc_ret)
{
    size_t size;
    void *internal;

    size = 50;

    internal = (void *)5;
    mock_malloc_init(internal);

    TEST_ASSERT_EQUAL(internal, mocklib_common_internal_create_and_check(size));

    internal = (void *)15;
    mock_malloc_init(internal);

    TEST_ASSERT_EQUAL(internal, mocklib_common_internal_create_and_check(size));
}

TEST(mocklib_common, internal_cc_fail_when_null)
{
    size_t size;

    size = 50;

    mock_malloc_init(NULL);
    utlib_test_fail_msg_init("Cannot create expected function internal data");

    mocklib_common_internal_create_and_check(size);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocklib_common, funtype_check_get_arg)
{
    mocklib_expdata_t expdata;
    mocklib_funtype_t funtype;

    expdata = (mocklib_expdata_t)5;
    funtype = 1;
    mock_mocklib_expdata_funtype_get_init(funtype);

    mocklib_common_funtype_check(expdata, funtype);

    TEST_ASSERT_EQUAL(1, mock_mocklib_expdata_funtype_get_cnt_get());
    TEST_ASSERT_EQUAL(expdata, mock_mocklib_expdata_funtype_get_arg_expdata_get());

    expdata = (mocklib_expdata_t)15;
    funtype = 1;
    mock_mocklib_expdata_funtype_get_init(funtype);

    mocklib_common_funtype_check(expdata, funtype);

    TEST_ASSERT_EQUAL(expdata, mock_mocklib_expdata_funtype_get_arg_expdata_get());
}

TEST(mocklib_common, funtype_check_fail_if_not_equal)
{
    mocklib_expdata_t expdata;
    mocklib_funtype_t funtype_exp, funtype_act;

    expdata = NULL;
    funtype_exp = 1;
    funtype_act = funtype_exp;
    mock_mocklib_expdata_funtype_get_init(funtype_act);

    mocklib_common_funtype_check(expdata, funtype_exp);

    expdata = NULL;
    funtype_exp = 1;
    funtype_act = funtype_exp + 1;
    mock_mocklib_expdata_funtype_get_init(funtype_act);
    utlib_test_fail_msg_init("Function called out of order");

    mocklib_common_funtype_check(expdata, funtype_exp);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocklib_common, internal_gc_get_arg)
{
    mocklib_expdata_t expdata;
    void *internal;

    internal = (void *)5;
    expdata = NULL;
    mock_mocklib_expdata_internal_get_init(internal);

    mocklib_common_internal_get_and_check(expdata);

    TEST_ASSERT_EQUAL(1, mock_mocklib_expdata_internal_get_cnt_get());
    TEST_ASSERT_EQUAL(expdata, mock_mocklib_expdata_internal_get_arg_expdata_get());

    internal = (void *)5;
    expdata = (mocklib_expdata_t)5;
    mock_mocklib_expdata_internal_get_init(internal);

    mocklib_common_internal_get_and_check(expdata);

    TEST_ASSERT_EQUAL(1, mock_mocklib_expdata_internal_get_cnt_get());
    TEST_ASSERT_EQUAL(expdata, mock_mocklib_expdata_internal_get_arg_expdata_get());
}

TEST(mocklib_common, internal_gc_ret)
{
    mocklib_expdata_t expdata;
    void *internal;

    expdata = NULL;

    internal = (void *)5;
    mock_mocklib_expdata_internal_get_init(internal);

    TEST_ASSERT_EQUAL(internal, mocklib_common_internal_get_and_check(expdata));

    internal = (void *)15;
    mock_mocklib_expdata_internal_get_init(internal);

    TEST_ASSERT_EQUAL(internal, mocklib_common_internal_get_and_check(expdata));
}

TEST(mocklib_common, internal_gc_fail_when_null)
{
    mocklib_expdata_t expdata;

    expdata = NULL;

    mock_mocklib_expdata_internal_get_init(NULL);
    utlib_test_fail_msg_init("Missing expected function data");

    mocklib_common_internal_get_and_check(expdata);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocklib_common, cb_check)
{
    mocklib_common_cb_check((void *)0xAAAAAAAA);

    utlib_test_fail_msg_init("Invalid callback function");

    mocklib_common_cb_check(NULL);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocklib_common, err_not_basic)
{
    mocklib_common_err_if_mode_not_basic(MOCKLIB_MODE_BASIC);

    utlib_test_fail_msg_init("Expect function shall be called only in basic mode");

    mocklib_common_err_if_mode_not_basic(MOCKLIB_MODE_TRACE);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocklib_common, err_not_trace)
{
    mocklib_common_err_if_mode_not_trace(MOCKLIB_MODE_TRACE);

    utlib_test_fail_msg_init("Expect function shall be called only in trace mode");

    mocklib_common_err_if_mode_not_trace(MOCKLIB_MODE_BASIC);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocklib_common, err_not_cb)
{
    mocklib_common_err_if_mode_not_cb(MOCKLIB_MODE_CALLBACK);

    utlib_test_fail_msg_init("Expect function shall be called only in callback mode");

    mocklib_common_err_if_mode_not_cb(MOCKLIB_MODE_BASIC);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}
