/* 
 * File:    mocks_test.c
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    26.07.2017
 */

#include "unity_fixture.h"

#include <stddef.h>

#include "dep_module1/dep_module1.h"

#include "mocklib.h"
#include "mocklib_internal.h"
#include "utlib_checks.h"
#include "dep_module1_mock.h"

TEST_GROUP(mocks_basic);

TEST_SETUP(mocks_basic)
{
    mocklib_init();

    dep_module1_mock_init();

    utlib_test_fail_msg_init(NULL);
    utlib_assert_equal_init(0);
}

TEST_TEAR_DOWN(mocks_basic)
{
    mocklib_init();
}

TEST(mocks_basic, no_args_no_ret)
{
    dep_module1_mock_dep_no_args_no_ret_mode_set(MOCKLIB_MODE_BASIC);

    dep_no_args_no_ret();
    TEST_ASSERT_EQUAL(1, dep_module1_mock_dep_no_args_no_ret_cnt_get());

    dep_no_args_no_ret();
    TEST_ASSERT_EQUAL(2, dep_module1_mock_dep_no_args_no_ret_cnt_get());
}

TEST(mocks_basic, no_args_ret_fail_when_wrong_mode_passed_to_config)
{
    dep_module1_mock_dep_no_args_ret_mode_set(MOCKLIB_MODE_TRACE);

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("Expect function shall be called only in basic mode");

    dep_module1_mock_dep_no_args_ret_basic_cfg(0);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_basic, no_args_ret)
{
    int32_t retval;

    retval = 1;
    dep_module1_mock_dep_no_args_ret_mode_set(MOCKLIB_MODE_BASIC);
    dep_module1_mock_dep_no_args_ret_basic_cfg(retval);

    TEST_ASSERT_EQUAL(retval, dep_no_args_ret());
    TEST_ASSERT_EQUAL(1, dep_module1_mock_dep_no_args_ret_cnt_get());

    retval = 2;
    dep_module1_mock_dep_no_args_ret_mode_set(MOCKLIB_MODE_BASIC);
    dep_module1_mock_dep_no_args_ret_basic_cfg(retval);

    TEST_ASSERT_EQUAL(retval, dep_no_args_ret());
    TEST_ASSERT_EQUAL(2, dep_module1_mock_dep_no_args_ret_cnt_get());
}

TEST(mocks_basic, one_arg_no_ret)
{
    uint16_t arg1;

    arg1 = 3;
    dep_module1_mock_dep_one_arg_no_ret_mode_set(MOCKLIB_MODE_BASIC);

    dep_one_arg_no_ret(arg1);
    TEST_ASSERT_EQUAL(1, dep_module1_mock_dep_one_arg_no_ret_cnt_get());

    dep_one_arg_no_ret(arg1);
    TEST_ASSERT_EQUAL(2, dep_module1_mock_dep_one_arg_no_ret_cnt_get());
}

TEST(mocks_basic, more_args_no_ret)
{
    int32_t arg1;
    uint8_t arg2;

    arg1 = 4;
    arg2 = 5;
    dep_module1_mock_dep_more_args_no_ret_mode_set(MOCKLIB_MODE_BASIC);

    dep_more_args_no_ret(arg1, arg2);
    TEST_ASSERT_EQUAL(1, dep_module1_mock_dep_more_args_no_ret_cnt_get());

    dep_more_args_no_ret(arg1, arg2);
    TEST_ASSERT_EQUAL(2, dep_module1_mock_dep_more_args_no_ret_cnt_get());
}

TEST(mocks_basic, one_arg_ret_fail_when_wrong_mode_passed_to_config)
{
    dep_module1_mock_dep_one_arg_ret_mode_set(MOCKLIB_MODE_TRACE);

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("Expect function shall be called only in basic mode");

    dep_module1_mock_dep_one_arg_ret_basic_cfg(0);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_basic, one_arg_ret)
{
    uint32_t retval;
    uint32_t arg1;

    retval = 6;
    arg1 = 7;
    dep_module1_mock_dep_one_arg_ret_mode_set(MOCKLIB_MODE_BASIC);
    dep_module1_mock_dep_one_arg_ret_basic_cfg(retval);

    TEST_ASSERT_EQUAL(retval, dep_one_arg_ret(arg1));
    TEST_ASSERT_EQUAL(1, dep_module1_mock_dep_one_arg_ret_cnt_get());

    retval = 8;
    dep_module1_mock_dep_one_arg_ret_mode_set(MOCKLIB_MODE_BASIC);
    dep_module1_mock_dep_one_arg_ret_basic_cfg(retval);

    TEST_ASSERT_EQUAL(retval, dep_one_arg_ret(arg1));
    TEST_ASSERT_EQUAL(2, dep_module1_mock_dep_one_arg_ret_cnt_get());
}

TEST(mocks_basic, more_args_ret_fail_when_wrong_mode_passed_to_config)
{
    dep_module1_mock_dep_more_args_ret_mode_set(MOCKLIB_MODE_TRACE);

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("Expect function shall be called only in basic mode");

    dep_module1_mock_dep_more_args_ret_basic_cfg(0);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_basic, more_args_ret)
{
    int8_t retval;
    int8_t arg1;
    int16_t arg2;

    retval = 9;
    arg1 = 10;
    arg2 = 11;
    dep_module1_mock_dep_more_args_ret_mode_set(MOCKLIB_MODE_BASIC);
    dep_module1_mock_dep_more_args_ret_basic_cfg(retval);

    TEST_ASSERT_EQUAL(retval, dep_more_args_ret(arg1, arg2));
    TEST_ASSERT_EQUAL(1, dep_module1_mock_dep_more_args_ret_cnt_get());

    retval = 12;
    dep_module1_mock_dep_more_args_ret_mode_set(MOCKLIB_MODE_BASIC);
    dep_module1_mock_dep_more_args_ret_basic_cfg(retval);

    TEST_ASSERT_EQUAL(retval, dep_more_args_ret(arg1, arg2));
    TEST_ASSERT_EQUAL(2, dep_module1_mock_dep_more_args_ret_cnt_get());
}
