/*
 * File:    mocklib_common.h
 * Author:  Maciej Gajdzica
 * Brief:   Functions used internally by generated mocks.
 *
 * Date:    13.08.2017
 */

#ifndef _MOCKLIB_COMMON_H_
#define _MOCKLIB_COMMON_H_

mocklib_expdata_t mocklib_common_expdata_create_and_check(void);
void * mocklib_common_internal_create_and_check(size_t size);
void mocklib_common_funtype_check(mocklib_expdata_t expdata, mocklib_funtype_t funtype_exp);
void * mocklib_common_internal_get_and_check(mocklib_expdata_t expdata);
void mocklib_common_err_if_mode_not_trace(mocklib_mode_t mode);

#endif /* _MOCKLIB_COMMON_H_ */
