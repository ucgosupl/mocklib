/*
 * File:    mocklib_common_test_main.c
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    25.08.2017
 */

#include <stdio.h>

#include "unity_fixture.h"

static void run_all_tests(void)
{
    printf("Run tests of mocklib common:\n");
    RUN_TEST_GROUP(mocklib_common);
}

int main(void)
{
    const char *argv[] = {"mocklib_common"};

    UnityMain(1, argv, run_all_tests);

    return 0;
}
