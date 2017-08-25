/* 
 * File:    mocklib_expfun_test_runner.c
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    24.08.2017
 */

#include "unity_fixture.h"

TEST_GROUP_RUNNER(mocklib_expfun)
{
    RUN_TEST_CASE(mocklib_expfun, create_correct_size_passed_to_malloc);
    RUN_TEST_CASE(mocklib_expfun, create_retval_passed_from_malloc);
    RUN_TEST_CASE(mocklib_expfun, create_returned_value_initialized);

    RUN_TEST_CASE(mocklib_expfun, destroy_free_not_called_when_null);
    RUN_TEST_CASE(mocklib_expfun, destroy_free_called);
    RUN_TEST_CASE(mocklib_expfun, destroy_free_internal_data_if_exist);

    RUN_TEST_CASE(mocklib_expfun, expdata_set_fail_when_null);
    RUN_TEST_CASE(mocklib_expfun, expdata_get_fail_when_null);
    RUN_TEST_CASE(mocklib_expfun, expdata_get_returns_value_set_earlier);

    RUN_TEST_CASE(mocklib_expfun, internal_set_fail_when_null);
    RUN_TEST_CASE(mocklib_expfun, internal_get_fail_when_null);
    RUN_TEST_CASE(mocklib_expfun, internal_get_returns_value_set_earlier);
}
