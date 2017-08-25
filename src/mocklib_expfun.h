/*
 * File:    mocklib_expfun.h
 * Author:  Maciej Gajdzica
 * Brief:   Functions handling expected function data.
 *
 * Date:    27.07.2017
 */

#ifndef _MOCKLIB_EXPFUN_H_
#define _MOCKLIB_EXPFUN_H_

mocklib_expdata_t mocklib_expdata_create(void);
void mocklib_expdata_destroy(mocklib_expdata_t expdata);
void mocklib_expdata_funtype_set(mocklib_expdata_t expdata, mocklib_funtype_t type);
mocklib_funtype_t mocklib_expdata_funtype_get(mocklib_expdata_t expdata);
void mocklib_expdata_internal_set(mocklib_expdata_t expdata, void *internal);
void * mocklib_expdata_internal_get(mocklib_expdata_t expdata);

#endif /* _MOCKLIB_EXPFUN_H_ */
