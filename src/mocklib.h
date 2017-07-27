/*
 * File:    mocklib.h
 * Author:  Maciej Gajdzica
 * Brief:   Mock library public API.
 *
 * Date:    27.07.2017
 */

#ifndef _MOCKLIB_H_
#define _MOCKLIB_H_

typedef int32_t mocklib_funtype_t;
typedef struct expfun_record * mocklib_expdata_t;

void mocklib_init(void);
mocklib_expdata_t mocklib_exp_get(void);
void mocklib_exp_set(mocklib_expdata_t exp);

#endif /* _MOCKLIB_H_ */
