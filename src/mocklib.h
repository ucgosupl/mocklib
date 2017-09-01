/*
 * File:    mocklib.h
 * Author:  Maciej Gajdzica
 * Brief:   Mock library public API.
 *
 * Date:    27.07.2017
 */

#ifndef _MOCKLIB_H_
#define _MOCKLIB_H_

/**
 * Macro for init function name of mock for a given header file.
 *
 * Resulting function:
 * void {file}_mock_init
 */
#define MOCKLIB_FUN_MOCK_INIT(file)         file ## _mock_init

/**
 * Macro for config function name of a given function in mock for a given header file.
 *
 * Config function is used to configure mock before usage. This function takes
 * mode argument according to MOCKLIB_MODE enum. If mocked function returns any
 * value it also takes value to be returned by mock in basic mode.
 *
 * Resulting function:
 * void {file}_mock_{fun}_config(mocklib_mode_t mode [, ret_type ret])
 */
#define MOCKLIB_FUN_CONFIG(file, fun)       file ## _mock_ ## fun ## _config

/**
 * Macro for expect function name of a given function in mock for a given header file.
 *
 * Expect function is used to configure mock before usage in trace mode. This function
 * should be called for every expected call to the mocked function. It allows for
 * setting separate return value for every call. It also takes input arguments
 * expected by the mocked function. When mocked function is called, these input
 * arguments are checked against real values and test fails if they don't match.
 * In trace mode also order of calling traced functions matters so even if a
 * function doesn't return any value nor takes any arguments it could be traced.
 *
 * Resulting function:
 * void {file}_mock_{fun}_expect([ret_type, ret][, arg1_type arg1 ...])
 */
#define MOCKLIB_FUN_EXPECT(file, fun)       file ## _mock_ ## fun ## _expect

/**
 * Macro for count function name of a given function in mock for a given header file.
 *
 * This function returns number of calls to mocked function. Function enter count
 * is calculated for mocked function in every mode.
 *
 * Resulting function:
 * void {file}_mock_{fun}_cnt_get(void)
 */
#define MOCKLIB_FUN_CNT(file, fun)          file ## _mock_ ## fun ## _cnt_get

enum
{
    /**
     * The same value is returned for every call to the mocked function. No argument
     * check.
     */
    MOCKLIB_MODE_BASIC,

    /**
     * For every call to the mocked function separate return value is configured.
     * Also separate input arguments are checked for every call. Test is failed
     * on wrong input arguments or when traced functions are called in wrong
     * order.
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
