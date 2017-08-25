/* 
 * File:    mocklib_common_test_runner.c
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    25.08.2017
 */

#include "unity_fixture.h"

TEST_GROUP_RUNNER(mocklib_common)
{
    RUN_TEST_CASE(mocklib_common, expdata_cc_create_called);
    RUN_TEST_CASE(mocklib_common, expdata_cc_ret);
    RUN_TEST_CASE(mocklib_common, expdata_cc_fail_when_null);

    RUN_TEST_CASE(mocklib_common, internal_cc_malloc_arg);
    RUN_TEST_CASE(mocklib_common, internal_cc_ret);
    RUN_TEST_CASE(mocklib_common, internal_cc_fail_when_null);

    RUN_TEST_CASE(mocklib_common, funtype_check_get_arg);
    RUN_TEST_CASE(mocklib_common, funtype_check_fail_if_not_equal);

    RUN_TEST_CASE(mocklib_common, internal_gc_get_arg);
    RUN_TEST_CASE(mocklib_common, internal_gc_ret);
    RUN_TEST_CASE(mocklib_common, internal_gc_fail_when_null);

    RUN_TEST_CASE(mocklib_common, err_not_trace);
}
