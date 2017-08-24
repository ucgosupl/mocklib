/*
 * File:    mocklib_test_main.c
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    23.08.2017
 */

#include <stdio.h>

#include "unity_fixture.h"

static void run_all_tests(void)
{
    printf("Run tests of mocklib:\n");
    RUN_TEST_GROUP(mocklib);
}

int main(void)
{
    const char *argv[] = {"mocklib"};

    UnityMain(1, argv, run_all_tests);

    return 0;
}
