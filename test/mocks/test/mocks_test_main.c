/*
 * File:    mocks_test_main.c
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    26.07.2017
 */

#include <stdio.h>

#include "unity_fixture.h"

static void run_all_tests(void)
{
    printf("Basic mode tests:\n");
    RUN_TEST_GROUP(mocks_basic);
    printf("\nTrace mode tests:\n");
    RUN_TEST_GROUP(mocks_trace);
    printf("\nCallback mode tests:\n");
    RUN_TEST_GROUP(mocks_callback);
}

int main(void)
{
    const char *argv[] = {"mocks"};

    UnityMain(1, argv, run_all_tests);

    return 0;
}
