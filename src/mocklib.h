/*
 * File:    mocklib.h
 * Author:  Maciej Gajdzica
 * Brief:   Mock library public API.
 *
 * Date:    27.07.2017
 */

#ifndef _MOCKLIB_H_
#define _MOCKLIB_H_

enum
{
    /*
     * Call count is updated
     * No argument check
     * Always the same value returned
     */
    MOCKLIB_MODE_BASIC,

    /*
     * Call count is updated
     * Arguments checked for every call
     * Other value returned for every call
     */
    MOCKLIB_MODE_TRACE,
};

typedef int32_t mocklib_mode_t;
typedef int32_t mocklib_funtype_t;
typedef struct expfun_record * mocklib_expdata_t;

void mocklib_init(void);
mocklib_expdata_t mocklib_exp_get(void);
void mocklib_exp_set(mocklib_expdata_t exp);

#endif /* _MOCKLIB_H_ */
