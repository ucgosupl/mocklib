/*
 * File:    mocklib_common.h
 * Author:  Maciej Gajdzica
 * Brief:   Functions used internally by generated mocks.
 *
 * Date:    13.08.2017
 */

#ifndef _MOCKLIB_COMMON_H_
#define _MOCKLIB_COMMON_H_

/**
 * Create expected function data and fail test if creation ended with error.
 *
 * @return                  Created expected function data.
 */
mocklib_expdata_t mocklib_common_expdata_create_and_check(void);

/**
 * Create internal function data and fail test if creation ended with error.
 *
 * @param size              Size of internal function data to be created.
 *
 * @return                  Created internal function data.
 */
void * mocklib_common_internal_create_and_check(size_t size);

/**
 * Check if expected function data contains data for correct function type.
 *
 * @param expdata           Expected function data.
 * @param funtype_exp       Expected function type.
 */
void mocklib_common_funtype_check(mocklib_expdata_t expdata, mocklib_funtype_t funtype_exp);

/**
 * Get internal data if exist, otherwise fail test.
 *
 * @param expdata           Expected function data.
 *
 * @return                  Internal function data.
 */
void * mocklib_common_internal_get_and_check(mocklib_expdata_t expdata);

/**
 * Fail test if mock mode is not basic.
 *
 * @param mode              Mock mode.
 */
void mocklib_common_err_if_mode_not_basic(mocklib_mode_t mode);

/**
 * Fail test if mock mode is not trace.
 *
 * @param mode              Mock mode.
 */
void mocklib_common_err_if_mode_not_trace(mocklib_mode_t mode);

/**
 * Fail test if mock mode is not callback.
 *
 * @param mode              Mock mode.
 */
void mocklib_common_err_if_mode_not_cb(mocklib_mode_t mode);

#endif /* _MOCKLIB_COMMON_H_ */
