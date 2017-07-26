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
