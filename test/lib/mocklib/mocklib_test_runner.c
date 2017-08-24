/* 
 * File:    mocklib_test_runner.c
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    23.08.2017
 */

#include "unity_fixture.h"

TEST_GROUP_RUNNER(mocklib)
{
    RUN_TEST_CASE(mocklib, init_params_cleared);
    RUN_TEST_CASE(mocklib, init_stack_old_item_destroy);

    RUN_TEST_CASE(mocklib, exp_set_fail_when_arg_null);
    RUN_TEST_CASE(mocklib, exp_set_fail_when_exp_limit_exceeded);

    RUN_TEST_CASE(mocklib, exp_get_fail_when_all_exp_already_given);
    RUN_TEST_CASE(mocklib, exp_get_fail_when_empty);

    RUN_TEST_CASE(mocklib, exp_get_set);

    RUN_TEST_CASE(mocklib, exp_all_called_no_error_when_no_exp);
    RUN_TEST_CASE(mocklib, exp_all_called_no_error_when_all_exp_taken);
    RUN_TEST_CASE(mocklib, exp_all_called_fail_if_not_all_exp_taken);
}
