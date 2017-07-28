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

    RUN_TEST_CASE(mocks, mode_trace_no_ret_no_args_unexpected);
    RUN_TEST_CASE(mocks, mode_trace_no_ret_no_args_expect_single_call);
    RUN_TEST_CASE(mocks, mode_trace_no_ret_no_args_expect_many_calls);

    RUN_TEST_CASE(mocks, mode_trace_no_args_ret_unexpected);
    RUN_TEST_CASE(mocks, mode_trace_no_args_ret_expect_single_call);
    RUN_TEST_CASE(mocks, mode_trace_no_args_ret_expect_many_calls);

    RUN_TEST_CASE(mocks, mode_trace_one_arg_no_ret_unexpected);
    RUN_TEST_CASE(mocks, mode_trace_one_arg_no_ret_expect_single_call);
    RUN_TEST_CASE(mocks, mode_trace_one_arg_no_ret_expect_many_calls);
    RUN_TEST_CASE(mocks, mode_trace_one_arg_no_ret_wrong_arg1);

    RUN_TEST_CASE(mocks, mode_trace_more_args_no_ret_unexpected);
    RUN_TEST_CASE(mocks, mode_trace_more_args_no_ret_expect_single_call);
    RUN_TEST_CASE(mocks, mode_trace_more_args_no_ret_expect_many_calls);
    RUN_TEST_CASE(mocks, mode_trace_more_args_no_ret_wrong_arg1);
    RUN_TEST_CASE(mocks, mode_trace_more_args_no_ret_wrong_arg2);
}