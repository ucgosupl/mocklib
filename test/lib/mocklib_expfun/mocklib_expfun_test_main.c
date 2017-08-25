/*
 * File:    mocklib_expfun_test_main.c
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    24.08.2017
 */

#include <stdio.h>

#include "unity_fixture.h"

static void run_all_tests(void)
{
    printf("Run tests of mocklib expfun:\n");
    RUN_TEST_GROUP(mocklib_expfun);
}

int main(void)
{
    const char *argv[] = {"mocklib_expfun"};

    UnityMain(1, argv, run_all_tests);

    return 0;
}
