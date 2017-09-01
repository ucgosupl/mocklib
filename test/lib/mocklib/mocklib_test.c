/* 
 * File:    mocklib_test.c
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    23.08.2017
 */

#include "unity_fixture.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "mocklib.h"
#include "mocklib_internal.h"

#include "mocks/mocklib_test_mocks.h"
#include "utlib_checks.h"

extern struct call_stack_params stack_params;

TEST_GROUP(mocklib);

TEST_SETUP(mocklib)
{
    memset(&stack_params, 0, sizeof(struct call_stack_params));
}

TEST_TEAR_DOWN(mocklib)
{

}

TEST(mocklib, init_params_cleared)
{
    int32_t i;

    memset(&stack_params, 0xAA, sizeof(struct call_stack_params));

     mocklib_init();

    TEST_ASSERT_EQUAL(0, stack_params.cnt);
    TEST_ASSERT_EQUAL(0, stack_params.next);

    for (i = 0; i < CALL_STACK_SIZE; i++)
    {
        TEST_ASSERT_EQUAL(NULL, stack_params.stack[i]);
    }
}

TEST(mocklib, init_stack_old_item_destroy)
{
    mocklib_expdata_t ptr_val;

    ptr_val = NULL;
    stack_params.stack[0] = ptr_val;
    mock_mocklib_expdata_destroy_init();

    mocklib_init();

    TEST_ASSERT_EQUAL(0, mock_mocklib_expdata_destroy_cnt_get());

    ptr_val = (mocklib_expdata_t)5;
    stack_params.stack[0] = ptr_val;
    mock_mocklib_expdata_destroy_init();

    mocklib_init();

    TEST_ASSERT_EQUAL(1, mock_mocklib_expdata_destroy_cnt_get());
    TEST_ASSERT_EQUAL_PTR(ptr_val, mock_mocklib_expdata_destroy_arg_expdata_get());
}

TEST(mocklib, exp_set_fail_when_arg_null)
{
    utlib_test_fail_msg_init("Invalid expected function data");

    mocklib_exp_set(NULL);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocklib, exp_set_fail_when_exp_limit_exceeded)
{
    mocklib_expdata_t exp;

    exp = (mocklib_expdata_t)1;
    stack_params.cnt = CALL_STACK_SIZE - 1;

    mocklib_exp_set(exp);

    /* When last place available on exp stack - no fail */

    utlib_test_fail_msg_init("Exceeded maximum allowed number of expected functions");

    mocklib_exp_set(exp);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocklib, exp_get_fail_when_all_exp_already_given)
{
    stack_params.cnt = 1;
    stack_params.next = 0;

    mocklib_exp_get();

    utlib_test_fail_msg_init("All expected functions already called");

    mocklib_exp_get();

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocklib, exp_get_fail_when_empty)
{
    utlib_test_fail_msg_init("All expected functions already called");

    mocklib_exp_get();

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocklib, exp_get_set)
{
    mocklib_expdata_t exp1, exp2;

    exp1 = (mocklib_expdata_t)1;
    exp2 = (mocklib_expdata_t)2;

    mocklib_exp_set(exp1);
    mocklib_exp_set(exp2);

    /* Expectations are returned in the same order as set earlier */
    TEST_ASSERT_EQUAL(exp1, mocklib_exp_get());
    TEST_ASSERT_EQUAL(exp2, mocklib_exp_get());
}

TEST(mocklib, exp_all_called_no_error_when_no_exp)
{
    mocklib_exp_all_called();

    /* Function should not trigger test fail - if not test will be failed on internal check */
}

TEST(mocklib, exp_all_called_no_error_when_all_exp_taken)
{
    mocklib_expdata_t exp;

    exp = (mocklib_expdata_t)1;

    mocklib_exp_set(exp);
    mocklib_exp_set(exp);

    mocklib_exp_get();
    mocklib_exp_get();

    mocklib_exp_all_called();

    /* Function should not trigger test fail - if not test will be failed on internal check */
}

TEST(mocklib, exp_all_called_fail_if_not_all_exp_taken)
{
    mocklib_expdata_t exp;

    exp = (mocklib_expdata_t)1;

    mocklib_exp_set(exp);
    mocklib_exp_set(exp);

    mocklib_exp_get();

    utlib_test_fail_msg_init("Not all expected functions called");

    mocklib_exp_all_called();

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}
