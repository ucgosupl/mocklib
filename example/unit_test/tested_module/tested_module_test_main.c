/*
 * File:    tested_module_test_main.c
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    26.07.2017
 */


#include "unity_fixture.h"

static void run_all_tests(void)
{
    RUN_TEST_GROUP(module);
}

int main(void)
{
    const char *argv[] = {"tested_module"};

    UnityMain(1, argv, run_all_tests);

    return 0;
}
