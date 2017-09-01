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

struct assert_equal_params
{
    int32_t cnt;
    int32_t expected_fail;
};

static struct assert_equal_params assert_equal_params;
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

void utlib_assert_equal_init(int32_t exp_fail)
{
    assert_equal_params.cnt = 0;
    assert_equal_params.expected_fail = exp_fail;
}

void utlib_assert_equal(int32_t actual, int32_t expected)
{
    assert_equal_params.cnt++;

    if (expected != actual)
    {
        if (assert_equal_params.expected_fail != assert_equal_params.cnt)
        {
            TEST_FAIL_MESSAGE("UTLIB_ASSERT_EQUAL error: values not equal");
        }
        else
        {
            TEST_ABORT();
        }
    }
    else
    {
        if (assert_equal_params.expected_fail == 0)
        {
            /* Never expect to fail */
        }
        else
        {
            if (assert_equal_params.cnt >= assert_equal_params.expected_fail)
            {
                TEST_FAIL_MESSAGE("UTLIB_ASSERT_EQUAL error: expected fail");
            }
        }
    }
}
