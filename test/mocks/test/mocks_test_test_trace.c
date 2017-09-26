/*
 * File:    mocks_test_trace.c
 * Author:  Maciej Gajdzica
 * Brief:   Unit tests for mocks running in trace mode.
 *
 * Date:    26.09.2017
 */


#include "unity_fixture.h"

#include <stddef.h>

#include "dep_module1/dep_module1.h"

#include "mocklib.h"
#include "mocklib_internal.h"
#include "utlib_checks.h"
#include "dep_module1_mock.h"

/* Use test_setup template here */
TEST_GROUP(mocks_trace);

TEST_SETUP(mocks_trace)
{
    mocklib_init();

    dep_module1_mock_init();

    utlib_test_fail_msg_init(NULL);
    utlib_assert_equal_init(0);
}

TEST_TEAR_DOWN(mocks_trace)
{
    mocklib_init();
}

TEST(mocks_trace, mode_trace_no_ret_no_args_unexpected)
{
    dep_module1_mock_dep_no_args_no_ret_config(MOCKLIB_MODE_TRACE);
    utlib_test_fail_msg_init("All expected functions already called");

    dep_no_args_no_ret();

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_no_ret_no_args_expect_single_call)
{
    /* Config mock to expect single call */
    dep_module1_mock_dep_no_args_no_ret_config(MOCKLIB_MODE_TRACE);
    dep_module1_mock_dep_no_args_no_ret_expect();

    dep_no_args_no_ret();

    /* Confirm that function was called */
    TEST_ASSERT_EQUAL(1, dep_module1_mock_dep_no_args_no_ret_cnt_get());

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("All expected functions already called");

    dep_no_args_no_ret();

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_no_ret_no_args_expect_many_calls)
{
    int32_t call_cnt;
    int32_t i;

    /* Config mock to expect call_cnt calls */
    call_cnt = 3;
    dep_module1_mock_dep_no_args_no_ret_config(MOCKLIB_MODE_TRACE);
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

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("All expected functions already called");

    dep_no_args_no_ret();

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_no_args_ret_unexpected)
{
    int32_t ret;

    ret = 13;
    dep_module1_mock_dep_no_args_ret_config(MOCKLIB_MODE_TRACE, ret);
    utlib_test_fail_msg_init("All expected functions already called");

    dep_no_args_ret();

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_no_args_ret_expect_single_call)
{
    int32_t ret;

    /* Config mock to expect single call */
    ret = 14;
    dep_module1_mock_dep_no_args_ret_config(MOCKLIB_MODE_TRACE, 0);
    dep_module1_mock_dep_no_args_ret_expect(ret);

    /* Confirm that function returns expected value */
    TEST_ASSERT_EQUAL(ret, dep_no_args_ret());

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("All expected functions already called");

    dep_no_args_ret();

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_no_args_ret_expect_many_calls)
{
    int32_t ret;
    int32_t call_cnt;
    int32_t i;

    /* Config mock to expect call_cnt calls */
    call_cnt = 3;
    ret = 15;
    dep_module1_mock_dep_no_args_ret_config(MOCKLIB_MODE_TRACE, 0);
    for (i = 0; i < call_cnt; i++)
    {
        dep_module1_mock_dep_no_args_ret_expect(ret * (i + 1));
    }

    /* Confirm that function returns expected value for every call */
    for (i = 0; i < call_cnt; i++)
    {
        TEST_ASSERT_EQUAL(ret * (i + 1), dep_no_args_ret());
    }

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("All expected functions already called");

    dep_no_args_ret();

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_one_arg_no_ret_unexpected)
{
    uint16_t arg1;

    arg1 = 16;
    dep_module1_mock_dep_one_arg_no_ret_config(MOCKLIB_MODE_TRACE);
    utlib_test_fail_msg_init("All expected functions already called");

    dep_one_arg_no_ret(arg1);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_one_arg_no_ret_expect_single_call)
{
    uint16_t arg1;

    /* Config mock to expect single call */
    arg1 = 17;
    dep_module1_mock_dep_one_arg_no_ret_config(MOCKLIB_MODE_TRACE);
    dep_module1_mock_dep_one_arg_no_ret_expect(arg1);

    dep_one_arg_no_ret(arg1);

    /* Confirm that function was called */
    TEST_ASSERT_EQUAL(1, dep_module1_mock_dep_one_arg_no_ret_cnt_get());

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("All expected functions already called");

    dep_one_arg_no_ret(arg1);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_one_arg_no_ret_expect_many_calls)
{
    uint16_t arg1;
    int32_t call_cnt;
    int32_t i;

    /* Config mock to expect call_cnt calls */
    arg1 = 18;
    call_cnt = 3;
    dep_module1_mock_dep_one_arg_no_ret_config(MOCKLIB_MODE_TRACE);
    for (i = 0; i < call_cnt; i++)
    {
        dep_module1_mock_dep_one_arg_no_ret_expect(arg1 * (i + 1));
    }

    /* Call function expected number of times */
    for (i = 0; i < call_cnt; i++)
    {
        dep_one_arg_no_ret(arg1 * (i + 1));
    }

    /* Confirm that function was called */
    TEST_ASSERT_EQUAL(call_cnt, dep_module1_mock_dep_one_arg_no_ret_cnt_get());

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("All expected functions already called");

    dep_one_arg_no_ret(arg1);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_one_arg_no_ret_wrong_arg1)
{
    uint16_t arg1;

    arg1 = 19;
    dep_module1_mock_dep_one_arg_no_ret_config(MOCKLIB_MODE_TRACE);
    dep_module1_mock_dep_one_arg_no_ret_expect(arg1);

    /* Expect assert equal to fail on first call */
    utlib_assert_equal_init(1);

    dep_one_arg_no_ret(arg1 + 5);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_more_args_no_ret_unexpected)
{
    int32_t arg1;
    uint8_t arg2;

    arg1 = 20;
    arg2 = 21;
    dep_module1_mock_dep_more_args_no_ret_config(MOCKLIB_MODE_TRACE);
    utlib_test_fail_msg_init("All expected functions already called");

    dep_more_args_no_ret(arg1, arg2);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_more_args_no_ret_expect_single_call)
{
    int32_t arg1;
    uint8_t arg2;

    /* Config mock to expect single call */
    arg1 = 22;
    arg2 = 23;
    dep_module1_mock_dep_more_args_no_ret_config(MOCKLIB_MODE_TRACE);
    dep_module1_mock_dep_more_args_no_ret_expect(arg1, arg2);

    dep_more_args_no_ret(arg1, arg2);

    /* Confirm that function was called */
    TEST_ASSERT_EQUAL(1, dep_module1_mock_dep_more_args_no_ret_cnt_get());

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("All expected functions already called");

    dep_more_args_no_ret(arg1, arg2);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_more_args_no_ret_expect_many_calls)
{
    int32_t arg1;
    uint8_t arg2;
    int32_t call_cnt;
    int32_t i;

    /* Config mock to expect call_cnt calls */
    arg1 = 24;
    arg2 = 25;
    call_cnt = 3;
    dep_module1_mock_dep_more_args_no_ret_config(MOCKLIB_MODE_TRACE);
    for (i = 0; i < call_cnt; i++)
    {
        dep_module1_mock_dep_more_args_no_ret_expect(arg1 * (i + 1), arg2 * (i + 1));
    }

    /* Call function expected number of times */
    for (i = 0; i < call_cnt; i++)
    {
        dep_more_args_no_ret(arg1 * (i + 1), arg2 * (i + 1));
    }

    /* Confirm that function was called */
    TEST_ASSERT_EQUAL(call_cnt, dep_module1_mock_dep_more_args_no_ret_cnt_get());

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("All expected functions already called");

    dep_more_args_no_ret(arg1, arg2);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_more_args_no_ret_wrong_arg1)
{
    int32_t arg1;
    uint8_t arg2;

    arg1 = 26;
    arg2 = 27;
    dep_module1_mock_dep_more_args_no_ret_config(MOCKLIB_MODE_TRACE);
    dep_module1_mock_dep_more_args_no_ret_expect(arg1, arg2);

    /* Expect assert equal to fail on first call */
    utlib_assert_equal_init(1);

    dep_more_args_no_ret(arg1 + 5, arg2);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_more_args_no_ret_wrong_arg2)
{
    int32_t arg1;
    uint8_t arg2;

    arg1 = 28;
    arg2 = 29;
    dep_module1_mock_dep_more_args_no_ret_config(MOCKLIB_MODE_TRACE);
    dep_module1_mock_dep_more_args_no_ret_expect(arg1, arg2);

    /* Expect assert equal to fail on second call - first call for correct arg1 */
    utlib_assert_equal_init(2);

    dep_more_args_no_ret(arg1, arg2 + 5);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_one_arg_ret_unexpected)
{
    uint32_t arg1;

    arg1 = 30;
    dep_module1_mock_dep_one_arg_ret_config(MOCKLIB_MODE_TRACE, 0);
    utlib_test_fail_msg_init("All expected functions already called");

    dep_one_arg_ret(arg1);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_one_arg_ret_expect_single_call)
{
    uint32_t arg1;
    uint32_t ret;

    /* Config mock to expect single call */
    arg1 = 31;
    ret = 32;
    dep_module1_mock_dep_one_arg_ret_config(MOCKLIB_MODE_TRACE, 0);
    dep_module1_mock_dep_one_arg_ret_expect(ret, arg1);

    /* Confirm that function returns expected value */
    TEST_ASSERT_EQUAL(ret, dep_one_arg_ret(arg1));

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("All expected functions already called");

    dep_one_arg_ret(arg1);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_one_arg_ret_expect_many_calls)
{
    uint32_t arg1;
    uint32_t ret;
    int32_t call_cnt;
    int32_t i;

    /* Config mock to expect call_cnt calls */
    arg1 = 33;
    ret = 34;
    call_cnt = 3;
    dep_module1_mock_dep_one_arg_ret_config(MOCKLIB_MODE_TRACE, 0);
    for (i = 0; i < call_cnt; i++)
    {
        dep_module1_mock_dep_one_arg_ret_expect(ret * (i + 1), arg1 * (i + 1));
    }

    /* Confirm that function returns expected value for every call */
    for (i = 0; i < call_cnt; i++)
    {
        TEST_ASSERT_EQUAL(ret * (i + 1), dep_one_arg_ret(arg1 * (i + 1)));
    }

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("All expected functions already called");

    dep_one_arg_ret(arg1);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_one_arg_ret_wrong_arg1)
{
    uint32_t arg1;
    uint32_t ret;

    arg1 = 35;
    ret = 36;
    dep_module1_mock_dep_one_arg_ret_config(MOCKLIB_MODE_TRACE, 0);
    dep_module1_mock_dep_one_arg_ret_expect(ret, arg1);

    /* Expect assert equal to fail on first call */
    utlib_assert_equal_init(1);

    dep_one_arg_ret(arg1 + 5);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_more_args_ret_unexpected)
{
    int8_t arg1;
    int16_t arg2;

    arg1 = 37;
    arg2 = 38;
    dep_module1_mock_dep_more_args_ret_config(MOCKLIB_MODE_TRACE, 0);
    utlib_test_fail_msg_init("All expected functions already called");

    dep_more_args_ret(arg1, arg2);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_more_args_ret_expect_single_call)
{
    int8_t arg1;
    int16_t arg2;
    int8_t ret;

    /* Config mock to expect single call */
    arg1 = 39;
    arg2 = 40;
    ret = 41;
    dep_module1_mock_dep_more_args_ret_config(MOCKLIB_MODE_TRACE, 0);
    dep_module1_mock_dep_more_args_ret_expect(ret, arg1, arg2);

    /* Confirm that function returns expected value */
    TEST_ASSERT_EQUAL(ret, dep_more_args_ret(arg1, arg2));

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("All expected functions already called");

    dep_more_args_ret(arg1, arg2);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_more_args_ret_expect_many_calls)
{
    int8_t arg1;
    int16_t arg2;
    int8_t ret;
    int32_t call_cnt;
    int32_t i;

    /* Config mock to expect call_cnt calls */
    arg1 = 42;
    arg2 = 43;
    ret = 44;
    call_cnt = 3;
    dep_module1_mock_dep_more_args_ret_config(MOCKLIB_MODE_TRACE, 0);
    for (i = 0; i < call_cnt; i++)
    {
        dep_module1_mock_dep_more_args_ret_expect(ret * (i + 1), arg1 * (i + 1), arg2 * (i + 1));
    }

    /* Confirm that function returns expected value for every call */
    for (i = 0; i < call_cnt; i++)
    {
        TEST_ASSERT_EQUAL_INT8(ret * (i + 1), dep_more_args_ret(arg1 * (i + 1), arg2 * (i + 1)));
    }

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("All expected functions already called");

    dep_more_args_ret(arg1, arg2);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_more_args_ret_wrong_arg1)
{
    int8_t arg1;
    int16_t arg2;
    int8_t ret;

    arg1 = 45;
    arg2 = 46;
    ret = 47;
    dep_module1_mock_dep_more_args_ret_config(MOCKLIB_MODE_TRACE, 0);
    dep_module1_mock_dep_more_args_ret_expect(ret, arg1, arg2);

    /* Expect assert equal to fail on first call */
    utlib_assert_equal_init(1);

    dep_more_args_ret(arg1 + 5, arg2);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_more_args_ret_wrong_arg2)
{
    int8_t arg1;
    int16_t arg2;
    int8_t ret;

    arg1 = 48;
    arg2 = 49;
    ret = 50;
    dep_module1_mock_dep_more_args_ret_config(MOCKLIB_MODE_TRACE, 0);
    dep_module1_mock_dep_more_args_ret_expect(ret, arg1, arg2);

    /* Expect assert equal to fail on second call - first call for correct arg1 */
    utlib_assert_equal_init(2);

    dep_more_args_ret(arg1, arg2 + 5);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_call_no_args_no_ret_when_expected_other)
{
    /* Function under test only configured to trace mode - not expected to be called. */
    dep_module1_mock_dep_no_args_no_ret_config(MOCKLIB_MODE_TRACE);

    /* Expect to call other function. */
    dep_module1_mock_dep_no_args_ret_config(MOCKLIB_MODE_TRACE, 0);
    dep_module1_mock_dep_no_args_ret_expect(0);

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("Function called out of order");

    /* Call function under test when not expected. */
    dep_no_args_no_ret();

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_call_no_args_ret_when_expected_other)
{
    /* Function under test only configured to trace mode - not expected to be called. */
    dep_module1_mock_dep_no_args_ret_config(MOCKLIB_MODE_TRACE, 0);

    /* Expect to call other function. */
    dep_module1_mock_dep_no_args_no_ret_config(MOCKLIB_MODE_TRACE);
    dep_module1_mock_dep_no_args_no_ret_expect();

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("Function called out of order");

    /* Call function under test when not expected. */
    dep_no_args_ret();

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_call_one_arg_no_ret_when_expected_other)
{
    uint16_t arg1;

    arg1 = 51;

    /* Function under test only configured to trace mode - not expected to be called. */
    dep_module1_mock_dep_one_arg_no_ret_config(MOCKLIB_MODE_TRACE);

    /* Expect to call other function. */
    dep_module1_mock_dep_no_args_no_ret_config(MOCKLIB_MODE_TRACE);
    dep_module1_mock_dep_no_args_no_ret_expect();

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("Function called out of order");

    /* Call function under test when not expected. */
    dep_one_arg_no_ret(arg1);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_call_more_args_no_ret_when_expected_other)
{
    int32_t arg1;
    uint8_t arg2;

    arg1 = 52;
    arg2 = 53;

    /* Function under test only configured to trace mode - not expected to be called. */
    dep_module1_mock_dep_more_args_no_ret_config(MOCKLIB_MODE_TRACE);

    /* Expect to call other function. */
    dep_module1_mock_dep_no_args_no_ret_config(MOCKLIB_MODE_TRACE);
    dep_module1_mock_dep_no_args_no_ret_expect();

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("Function called out of order");

    /* Call function under test when not expected. */
    dep_more_args_no_ret(arg1, arg2);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_call_one_arg_ret_when_expected_other)
{
    uint32_t arg1;

    arg1 = 54;

    /* Function under test only configured to trace mode - not expected to be called. */
    dep_module1_mock_dep_one_arg_ret_config(MOCKLIB_MODE_TRACE, 0);

    /* Expect to call other function. */
    dep_module1_mock_dep_no_args_no_ret_config(MOCKLIB_MODE_TRACE);
    dep_module1_mock_dep_no_args_no_ret_expect();

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("Function called out of order");

    /* Call function under test when not expected. */
    dep_one_arg_ret(arg1);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_trace, mode_trace_call_more_args_ret_when_expected_other)
{
    int8_t arg1;
    int16_t arg2;

    arg1 = 55;
    arg2 = 56;

    /* Function under test only configured to trace mode - not expected to be called. */
    dep_module1_mock_dep_more_args_ret_config(MOCKLIB_MODE_TRACE, 0);

    /* Expect to call other function. */
    dep_module1_mock_dep_no_args_no_ret_config(MOCKLIB_MODE_TRACE);
    dep_module1_mock_dep_no_args_no_ret_expect();

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("Function called out of order");

    /* Call function under test when not expected. */
    dep_more_args_ret(arg1, arg2);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

