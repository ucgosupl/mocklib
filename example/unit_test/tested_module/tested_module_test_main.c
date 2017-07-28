/*
 * File:    tested_module_test_main.c
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    26.07.2017
 */

#include <stdio.h>

#include "unity_fixture.h"

static void run_all_tests(void)
{
    printf("Run tested_module tests:\n");
    RUN_TEST_GROUP(module);
    printf("Run tests of mocks:\n");
    RUN_TEST_GROUP(mocks);
}

int main(void)
{
    const char *argv[] = {"tested_module"};

    UnityMain(1, argv, run_all_tests);

    return 0;
}