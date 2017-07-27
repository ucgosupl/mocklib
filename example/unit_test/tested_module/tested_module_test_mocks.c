/* 
 * File:    tested_module_test_mocks.c
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    26.07.2017
 */

#include "unity_fixture.h"

#include <stddef.h>

#include "mocks/dep_module1_mock.h"

TEST_GROUP(mocks);

TEST_SETUP(mocks)
{
    dep_module1_mock_init();
}

TEST_TEAR_DOWN(mocks)
{
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
    dep_module1_mock_dep_one_arg_no_ret_config(MOCK_MODE_BASIC);

    dep_one_arg_no_ret();
    TEST_ASSERT_EQUAL(1, dep_module1_mock_dep_one_arg_no_ret_cnt_get());

    dep_one_arg_no_ret();
    TEST_ASSERT_EQUAL(2, dep_module1_mock_dep_one_arg_no_ret_cnt_get());
}

TEST(mocks, mode_basic_more_args_no_ret)
{
    dep_module1_mock_dep_more_args_no_ret_config(MOCK_MODE_BASIC);

    dep_more_args_no_ret();
    TEST_ASSERT_EQUAL(1, dep_module1_mock_dep_more_args_no_ret_cnt_get());

    dep_more_args_no_ret();
    TEST_ASSERT_EQUAL(2, dep_module1_mock_dep_more_args_no_ret_cnt_get());
}

TEST(mocks, mode_basic_one_arg_ret)
{
    uint32_t retval;

    retval = 5;
    dep_module1_mock_dep_one_arg_ret_config(MOCK_MODE_BASIC, retval);

    TEST_ASSERT_EQUAL(retval, dep_one_arg_ret());
    TEST_ASSERT_EQUAL(1, dep_module1_mock_dep_one_arg_ret_cnt_get());

    retval = 15;
    dep_module1_mock_dep_one_arg_ret_config(MOCK_MODE_BASIC, retval);

    TEST_ASSERT_EQUAL(retval, dep_one_arg_ret());
    TEST_ASSERT_EQUAL(2, dep_module1_mock_dep_one_arg_ret_cnt_get());
}

TEST(mocks, mode_basic_more_args_ret)
{
    int8_t retval;

    retval = 5;
    dep_module1_mock_dep_more_args_ret_config(MOCK_MODE_BASIC, retval);

    TEST_ASSERT_EQUAL(retval, dep_more_args_ret());
    TEST_ASSERT_EQUAL(1, dep_module1_mock_dep_more_args_ret_cnt_get());

    retval = 15;
    dep_module1_mock_dep_more_args_ret_config(MOCK_MODE_BASIC, retval);

    TEST_ASSERT_EQUAL(retval, dep_more_args_ret());
    TEST_ASSERT_EQUAL(2, dep_module1_mock_dep_more_args_ret_cnt_get());
}
