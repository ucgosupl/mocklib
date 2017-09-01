/*
 * File:    mocklib_common_test_mocks.h
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    25.08.2017
 */

#ifndef _MOCKLIB_COMMON_TEST_MOCKS_H_
#define _MOCKLIB_COMMON_TEST_MOCKS_H_

void mock_mocklib_expdata_create_init(mocklib_expdata_t ret);
int32_t mock_mocklib_expdata_create_cnt_get(void);

void mock_mocklib_expdata_funtype_get_init(mocklib_funtype_t ret);
int32_t mock_mocklib_expdata_funtype_get_cnt_get(void);
mocklib_expdata_t mock_mocklib_expdata_funtype_get_arg_expdata_get(void);

void mock_mocklib_expdata_internal_get_init(void * ret);
int32_t mock_mocklib_expdata_internal_get_cnt_get(void);
mocklib_expdata_t mock_mocklib_expdata_internal_get_arg_expdata_get(void);

#endif /* _MOCKLIB_COMMON_TEST_MOCKS_H_ */
