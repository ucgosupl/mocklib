/* 
 * File:    mocks_test_runner.c
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    26.07.2017
 */

#include "unity_fixture.h"

TEST_GROUP_RUNNER(mocks_basic)
{
    RUN_TEST_CASE(mocks_basic, no_args_no_ret);

    RUN_TEST_CASE(mocks_basic, no_args_ret_fail_when_wrong_mode_passed_to_config);
    RUN_TEST_CASE(mocks_basic, no_args_ret);

    RUN_TEST_CASE(mocks_basic, one_arg_no_ret);

    RUN_TEST_CASE(mocks_basic, more_args_no_ret);

    RUN_TEST_CASE(mocks_basic, one_arg_ret_fail_when_wrong_mode_passed_to_config);
    RUN_TEST_CASE(mocks_basic, one_arg_ret);

    RUN_TEST_CASE(mocks_basic, more_args_ret_fail_when_wrong_mode_passed_to_config);
    RUN_TEST_CASE(mocks_basic, more_args_ret);
}

TEST_GROUP_RUNNER(mocks_trace)
{
    RUN_TEST_CASE(mocks_trace, no_args_no_ret_fail_when_wrong_mode_passed_to_config);
    RUN_TEST_CASE(mocks_trace, no_args_no_ret_unexpected);
    RUN_TEST_CASE(mocks_trace, no_args_no_ret_expect_single_call);
    RUN_TEST_CASE(mocks_trace, no_args_no_ret_expect_many_calls);

    RUN_TEST_CASE(mocks_trace, no_args_ret_fail_when_wrong_mode_passed_to_config);
    RUN_TEST_CASE(mocks_trace, no_args_ret_unexpected);
    RUN_TEST_CASE(mocks_trace, no_args_ret_expect_single_call);
    RUN_TEST_CASE(mocks_trace, no_args_ret_expect_many_calls);

    RUN_TEST_CASE(mocks_trace, one_arg_no_ret_fail_when_wrong_mode_passed_to_config);
    RUN_TEST_CASE(mocks_trace, one_arg_no_ret_unexpected);
    RUN_TEST_CASE(mocks_trace, one_arg_no_ret_expect_single_call);
    RUN_TEST_CASE(mocks_trace, one_arg_no_ret_expect_many_calls);
    RUN_TEST_CASE(mocks_trace, one_arg_no_ret_wrong_arg1);

    RUN_TEST_CASE(mocks_trace, more_args_no_ret_fail_when_wrong_mode_passed_to_config);
    RUN_TEST_CASE(mocks_trace, more_args_no_ret_unexpected);
    RUN_TEST_CASE(mocks_trace, more_args_no_ret_expect_single_call);
    RUN_TEST_CASE(mocks_trace, more_args_no_ret_expect_many_calls);
    RUN_TEST_CASE(mocks_trace, more_args_no_ret_wrong_arg1);
    RUN_TEST_CASE(mocks_trace, more_args_no_ret_wrong_arg2);

    RUN_TEST_CASE(mocks_trace, one_arg_ret_fail_when_wrong_mode_passed_to_config);
    RUN_TEST_CASE(mocks_trace, one_arg_ret_unexpected);
    RUN_TEST_CASE(mocks_trace, one_arg_ret_expect_single_call);
    RUN_TEST_CASE(mocks_trace, one_arg_ret_expect_many_calls);
    RUN_TEST_CASE(mocks_trace, one_arg_ret_wrong_arg1);

    RUN_TEST_CASE(mocks_trace, more_args_ret_fail_when_wrong_mode_passed_to_config);
    RUN_TEST_CASE(mocks_trace, more_args_ret_unexpected);
    RUN_TEST_CASE(mocks_trace, more_args_ret_expect_single_call);
    RUN_TEST_CASE(mocks_trace, more_args_ret_expect_many_calls);
    RUN_TEST_CASE(mocks_trace, more_args_ret_wrong_arg1);
    RUN_TEST_CASE(mocks_trace, more_args_ret_wrong_arg2);

    RUN_TEST_CASE(mocks_trace, call_no_args_no_ret_when_expected_other);
    RUN_TEST_CASE(mocks_trace, call_no_args_ret_when_expected_other);
    RUN_TEST_CASE(mocks_trace, call_one_arg_no_ret_when_expected_other);
    RUN_TEST_CASE(mocks_trace, call_more_args_no_ret_when_expected_other);
    RUN_TEST_CASE(mocks_trace, call_one_arg_ret_when_expected_other);
    RUN_TEST_CASE(mocks_trace, call_more_args_ret_when_expected_other);
}

TEST_GROUP_RUNNER(mocks_callback)
{
    RUN_TEST_CASE(mocks_callback, no_args_no_ret_fail_when_wrong_mode_passed_to_config);
    RUN_TEST_CASE(mocks_callback, no_args_no_ret_cb_called);

    RUN_TEST_CASE(mocks_callback, no_args_ret_fail_when_wrong_mode_passed_to_config);
    RUN_TEST_CASE(mocks_callback, no_args_ret_cb_called);
    RUN_TEST_CASE(mocks_callback, no_args_ret_retval);

    RUN_TEST_CASE(mocks_callback, one_arg_no_ret_fail_when_wrong_mode_passed_to_config);
    RUN_TEST_CASE(mocks_callback, one_arg_no_ret_cb_called);
    RUN_TEST_CASE(mocks_callback, one_arg_no_ret_args);

    RUN_TEST_CASE(mocks_callback, more_args_no_ret_fail_when_wrong_mode_passed_to_config);
    RUN_TEST_CASE(mocks_callback, more_args_no_ret_cb_called);
    RUN_TEST_CASE(mocks_callback, more_args_no_ret_args);

    RUN_TEST_CASE(mocks_callback, one_arg_ret_fail_when_wrong_mode_passed_to_config);
    RUN_TEST_CASE(mocks_callback, one_arg_ret_cb_called);
    RUN_TEST_CASE(mocks_callback, one_arg_ret_retval);
    RUN_TEST_CASE(mocks_callback, one_arg_ret_args);

    RUN_TEST_CASE(mocks_callback, more_args_ret_fail_when_wrong_mode_passed_to_config);
    RUN_TEST_CASE(mocks_callback, more_args_ret_cb_called);
    RUN_TEST_CASE(mocks_callback, more_args_ret_retval);
    RUN_TEST_CASE(mocks_callback, more_args_ret_args);
}
