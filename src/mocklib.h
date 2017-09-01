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

/**
 * Initialize mock library to work.
 *
 * This function initializes library internal data and cleans up any existing
 * resources if found.
 */
void mocklib_init(void);

/**
 * Check if all expected functions were called.
 *
 * Function causes test to fail if not all function data get from internal queue.
 */
void mocklib_exp_all_called(void);

#endif /* _MOCKLIB_H_ */
