/*
 * File:    mocklib_expfun.h
 * Author:  Maciej Gajdzica
 * Brief:   Functions handling expected function data.
 *
 * Date:    27.07.2017
 */

#ifndef _MOCKLIB_EXPFUN_H_
#define _MOCKLIB_EXPFUN_H_

/**
 * Create single expected function data object.
 *
 * Created object is initialized with default values. If object creation is not
 * possible, NULL is returned.
 *
 * @return              Created expdata object.
 */
mocklib_expdata_t mocklib_expdata_create(void);

/**
 * Destroy single expected function data object.
 *
 * @param expdata       Expdata to be destroyed.
 */
void mocklib_expdata_destroy(mocklib_expdata_t expdata);

/**
 * Set function type in expdata.
 *
 * Test fails immediately if invalid expdata is provided.
 *
 * @param expdata       Expdata to be updated.
 * @param type          New function type value.
 */
void mocklib_expdata_funtype_set(mocklib_expdata_t expdata, mocklib_funtype_t type);

/**
 * Get function type from expdata.
 *
 * Test fails immediately if invalid expdata is provided.
 *
 * @param expdata       Expdata to be read.
 *
 * @return              Function type read.
 */
mocklib_funtype_t mocklib_expdata_funtype_get(mocklib_expdata_t expdata);

/**
 * Set internal data pointer in expdata.
 *
 * Test fails immediately if invalid expdata is provided.
 *
 * @param expdata       Expdata to be updated.
 * @param internal      New internal data pointer.
 */
void mocklib_expdata_internal_set(mocklib_expdata_t expdata, void *internal);

/**
 * Get internal data pointer from expdata.
 *
 * @param expdata       Expdata to be read.
 *
 * @return              Internal data pointer read.
 */
void * mocklib_expdata_internal_get(mocklib_expdata_t expdata);

#endif /* _MOCKLIB_EXPFUN_H_ */
