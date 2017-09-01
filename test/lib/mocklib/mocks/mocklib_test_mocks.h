/*
 * File:    mocklib_test_mocks.h
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    23.08.2017
 */

#ifndef _MOCKLIB_TEST_MOCKS_H_
#define _MOCKLIB_TEST_MOCKS_H_

#define CALL_STACK_SIZE     20

struct call_stack_params
{
    int32_t cnt;
    int32_t next;
    mocklib_expdata_t stack[CALL_STACK_SIZE];
};

void mock_mocklib_expdata_destroy_init(void);
int32_t mock_mocklib_expdata_destroy_cnt_get(void);
mocklib_expdata_t mock_mocklib_expdata_destroy_arg_expdata_get(void);

#endif /* _MOCKLIB_TEST_MOCKS_H_ */
