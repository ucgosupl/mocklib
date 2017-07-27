/*
 * File:    utlib_checks.c
 * Author:  Maciej Gajdzica
 * Brief:   Short brief.
 *
 * Date:    27.07.2017
 */
#include <string.h>

#include "unity_fixture.h"

#include "utlib_checks.h"

static const char * exp_msg = NULL;

void utlib_test_fail_msg_init(const char * msg)
{
    exp_msg = msg;
}

void utlib_test_fail_msg_check(const char * msg)
{
    if (NULL == exp_msg)
    {
        TEST_FAIL_MESSAGE("UTLIB_TEST_FAIL_MSG called unexpectedly!");
    }
    else if (0 == strcmp(msg, exp_msg))
    {
        TEST_ABORT();
    }
    else
    {
        TEST_FAIL_MESSAGE("UTLIB_TEST_FAIL_MSG error: incorrect message");
    }
}
