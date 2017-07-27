/* 
 * File:    tested_module_test_runner.c
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    26.07.2017
 */

#include "unity_fixture.h"

TEST_GROUP_RUNNER(module)
{
    RUN_TEST_CASE(module, first_test);
}

TEST_GROUP_RUNNER(mocks)
{
    RUN_TEST_CASE(mocks, mode_basic_no_args_no_ret);
    RUN_TEST_CASE(mocks, mode_basic_no_args_ret);
    RUN_TEST_CASE(mocks, mode_basic_one_arg_no_ret);
    RUN_TEST_CASE(mocks, mode_basic_more_args_no_ret);
    RUN_TEST_CASE(mocks, mode_basic_one_arg_ret);
    RUN_TEST_CASE(mocks, mode_basic_more_args_ret);
}
