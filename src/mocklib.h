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

/** Type for mocklib mode - available modes in enum. */
typedef int32_t mocklib_mode_t;

/** Type for mocked function type - all mocked functions labels are in enum */
typedef int32_t mocklib_funtype_t;

/** Type for expected function data - storing return value and expected parameters. */
typedef struct expfun_record * mocklib_expdata_t;

/**
 * Initialize mock library to work.
 *
 * This function initializes library internal data and cleans up any existing
 * resources if found.
 */
void mocklib_init(void);

/**
 * Get data of function expected to be called next.
 *
 * When all expected function data already given - function causes test to fail.
 *
 * @return                  Expected function data.
 */
mocklib_expdata_t mocklib_exp_get(void);

/**
 * Add new expected function data to call stack.
 *
 * This function causes test to fail in following cases:
 * - Invalid input argument.
 * - Expected function data internal queue already full.
 *
 * @param exp               Expected function data.
 */
void mocklib_exp_set(mocklib_expdata_t exp);

/**
 * Check if all expected functions were called.
 *
 * Function causes test to fail if not all function data get from internal queue.
 */
void mocklib_exp_all_called(void);

#endif /* _MOCKLIB_H_ */
