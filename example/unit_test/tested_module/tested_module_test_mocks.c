/* 
 * File:    tested_module_test_mocks.c
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    26.07.2017
 */

#include "unity_fixture.h"

#include <stddef.h>

#include "dep_module1/dep_module1.h"

#include "mocklib.h"
#include "utlib_checks.h"
#include "mocks/dep_module1_mock.h"

TEST_GROUP(mocks);

TEST_SETUP(mocks)
{
    mocklib_init();

    dep_module1_mock_init();

    utlib_test_fail_msg_init(NULL);
}

TEST_TEAR_DOWN(mocks)
{
    mocklib_init();
}

TEST(mocks, mode_basic_no_args_no_ret)
{
    dep_module1_mock_dep_no_args_no_ret_config(MOCK_MODE_BASIC);

    dep_no_args_no_ret();
    TEST_ASSERT_EQUAL(1, dep_module1_mock_dep_no_args_no_ret_cnt_get());

    dep_no_args_no_ret();
    TEST_ASSERT_EQUAL(2, dep_module1_mock_dep_no_args_no_ret_cnt_get());
}

TEST(mocks, mode_basic_no_args_ret)
{
    int32_t retval;

    retval = 5;
    dep_module1_mock_dep_no_args_ret_config(MOCK_MODE_BASIC, retval);

    TEST_ASSERT_EQUAL(retval, dep_no_args_ret());
    TEST_ASSERT_EQUAL(1, dep_module1_mock_dep_no_args_ret_cnt_get());

    retval = 15;
    dep_module1_mock_dep_no_args_ret_config(MOCK_MODE_BASIC, retval);

    TEST_ASSERT_EQUAL(retval, dep_no_args_ret());
    TEST_ASSERT_EQUAL(2, dep_module1_mock_dep_no_args_ret_cnt_get());
}

TEST(mocks, mode_basic_one_arg_no_ret)
{
    uint16_t arg1;

    arg1 = 20;
    dep_module1_mock_dep_one_arg_no_ret_config(MOCK_MODE_BASIC);

    dep_one_arg_no_ret(arg1);
    TEST_ASSERT_EQUAL(1, dep_module1_mock_dep_one_arg_no_ret_cnt_get());

    dep_one_arg_no_ret(arg1);
    TEST_ASSERT_EQUAL(2, dep_module1_mock_dep_one_arg_no_ret_cnt_get());
}

TEST(mocks, mode_basic_more_args_no_ret)
{
    int32_t arg1;
    uint8_t arg2;

    arg1 = 10;
    arg2 = 15;
    dep_module1_mock_dep_more_args_no_ret_config(MOCK_MODE_BASIC);

    dep_more_args_no_ret(arg1, arg2);
    TEST_ASSERT_EQUAL(1, dep_module1_mock_dep_more_args_no_ret_cnt_get());

    dep_more_args_no_ret(arg1, arg2);
    TEST_ASSERT_EQUAL(2, dep_module1_mock_dep_more_args_no_ret_cnt_get());
}

TEST(mocks, mode_basic_one_arg_ret)
{
    uint32_t retval;
    uint32_t arg1;

    retval = 5;
    arg1 = 10;
    dep_module1_mock_dep_one_arg_ret_config(MOCK_MODE_BASIC, retval);

    TEST_ASSERT_EQUAL(retval, dep_one_arg_ret(arg1));
    TEST_ASSERT_EQUAL(1, dep_module1_mock_dep_one_arg_ret_cnt_get());

    retval = 15;
    dep_module1_mock_dep_one_arg_ret_config(MOCK_MODE_BASIC, retval);

    TEST_ASSERT_EQUAL(retval, dep_one_arg_ret(arg1));
    TEST_ASSERT_EQUAL(2, dep_module1_mock_dep_one_arg_ret_cnt_get());
}

TEST(mocks, mode_basic_more_args_ret)
{
    int8_t retval;
    int8_t arg1;
    int16_t arg2;

    retval = 5;
    arg1 = 1;
    arg2 = 2;
    dep_module1_mock_dep_more_args_ret_config(MOCK_MODE_BASIC, retval);

    TEST_ASSERT_EQUAL(retval, dep_more_args_ret(arg1, arg2));
    TEST_ASSERT_EQUAL(1, dep_module1_mock_dep_more_args_ret_cnt_get());

    retval = 15;
    dep_module1_mock_dep_more_args_ret_config(MOCK_MODE_BASIC, retval);

    TEST_ASSERT_EQUAL(retval, dep_more_args_ret(arg1, arg2));
    TEST_ASSERT_EQUAL(2, dep_module1_mock_dep_more_args_ret_cnt_get());
}

TEST(mocks, mode_trace_no_ret_no_args_unexpected)
{
    dep_module1_mock_dep_no_args_no_ret_config(MOCK_MODE_TRACE);
    utlib_test_fail_msg_init("Unexpected call to function");

    dep_no_args_no_ret();

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks, mode_trace_no_ret_no_args_expect_single_call)
{
    /* Config mock to expect single call */
    dep_module1_mock_dep_no_args_no_ret_config(MOCK_MODE_TRACE);
    dep_module1_mock_dep_no_args_no_ret_expect();

    dep_no_args_no_ret();

    /* Confirm that function was called */
    TEST_ASSERT_EQUAL(1, dep_module1_mock_dep_no_args_no_ret_cnt_get());

    /* Expect mock to call test fail on next call */
    utlib_test_fail_msg_init("Unexpected call to function");

    dep_no_args_no_ret();

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks, mode_trace_no_ret_no_args_expect_many_calls)
{
    int32_t call_cnt;
    int32_t i;

    /* Config mock to expect call_cnt calls */
    call_cnt = 3;
    dep_module1_mock_dep_no_args_no_ret_config(MOCK_MODE_TRACE);
    for (i = 0; i < call_cnt; i++)
    {
        dep_module1_mock_dep_no_args_no_ret_expect();
    }

    /* Call function expected number of times */
    for (i = 0; i < call_cnt; i++)
    {
        dep_no_args_no_ret();
    }

    /* Confirm that function was called */
    TEST_ASSERT_EQUAL(call_cnt, dep_module1_mock_dep_no_args_no_ret_cnt_get());

    /* Expect mock to call test fail on next call */
    utlib_test_fail_msg_init("Unexpected call to function");

    dep_no_args_no_ret();

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks, mode_trace_no_args_ret_unexpected)
{
    int32_t ret;

    ret = 15;
    dep_module1_mock_dep_no_args_ret_config(MOCK_MODE_TRACE, ret);
    utlib_test_fail_msg_init("Unexpected call to function");

    dep_no_args_ret();

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks, mode_trace_no_args_ret_expect_single_call)
{
    int32_t ret;

    /* Config mock to expect single call */
    ret = 15;
    dep_module1_mock_dep_no_args_ret_config(MOCK_MODE_TRACE, 0);
    dep_module1_mock_dep_no_args_ret_expect(ret);

    /* Confirm that function returns expected value */
    TEST_ASSERT_EQUAL(ret, dep_no_args_ret());

    /* Expect mock to call test fail on next call */
    utlib_test_fail_msg_init("Unexpected call to function");

    dep_no_args_ret();

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks, mode_trace_no_args_ret_expect_many_calls)
{
    int32_t call_cnt;
    int32_t i;

    /* Config mock to expect call_cnt calls */
    call_cnt = 3;
    dep_module1_mock_dep_no_args_ret_config(MOCK_MODE_TRACE, 0);
    for (i = 0; i < call_cnt; i++)
    {
        dep_module1_mock_dep_no_args_ret_expect(i);
    }

    /* Confirm that function returns expected value for every call */
    for (i = 0; i < call_cnt; i++)
    {
        TEST_ASSERT_EQUAL(i, dep_no_args_ret());
    }

    /* Expect mock to call test fail on next call */
    utlib_test_fail_msg_init("Unexpected call to function");

    dep_no_args_ret();

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

//expect one function call other
