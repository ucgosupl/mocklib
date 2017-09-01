/*
 * File:    mocklib.h
 * Author:  Maciej Gajdzica
 * Brief:   Mock library public API implementation.
 *
 * Date:    27.07.2017
 */

#include <stddef.h>
#include <stdint.h>

#include "mocklib.h"
#include "mocklib_internal.h"
#include "mocklib_expfun.h"
#include "mocklib_utlib_defines.h"

#define CALL_STACK_SIZE     20

struct call_stack_params
{
    int32_t cnt;
    int32_t next;
    mocklib_expdata_t stack[CALL_STACK_SIZE];
};

PRIVATE struct call_stack_params stack_params;

void mocklib_init(void)
{
    int32_t i;

    stack_params.cnt = 0;
    stack_params.next = 0;

    for (i = 0; i < CALL_STACK_SIZE; i++)
    {
        /* Clean up any existing objects */
        if (NULL != stack_params.stack[i])
        {
            mocklib_expdata_destroy(stack_params.stack[i]);
            /* TODO: What if destroy returns error? */
        }

        stack_params.stack[i] = NULL;
    }
}

mocklib_expdata_t mocklib_exp_get(void)
{
    mocklib_expdata_t retval = NULL;

    if (stack_params.cnt > stack_params.next)
    {
        retval = stack_params.stack[stack_params.next];
        stack_params.next++;
    }
    else
    {
        UTLIB_TEST_FAIL_MSG("All expected functions already called");
    }

    return retval;
}

void mocklib_exp_set(mocklib_expdata_t exp)
{
    if (NULL == exp)
    {
        UTLIB_TEST_FAIL_MSG("Invalid expected function data");
    }

    if (CALL_STACK_SIZE > stack_params.cnt)
    {
        stack_params.stack[stack_params.cnt] = exp;
        stack_params.cnt++;
    }
    else
    {
        UTLIB_TEST_FAIL_MSG("Exceeded maximum allowed number of expected functions");
    }
}

void mocklib_exp_all_called(void)
{
    if (stack_params.next != stack_params.cnt)
    {
        UTLIB_TEST_FAIL_MSG("Not all expected functions called");
    }
}
