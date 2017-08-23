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
    RUN_TEST_CASE(mocklib, first_test);
}
