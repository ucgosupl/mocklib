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
    RUN_TEST_CASE(mocklib_common, first);
}
