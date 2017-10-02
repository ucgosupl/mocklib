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
 * Macro for mode set function name of a given function in mock for a given header file.
 *
 * This function sets mode for mocked function taken as argument according to MOCKLIB_MODE enum.
 *
 * Resulting function:
 * void {file}_mock_{fun}_mode_set(mocklib_mode_t mode)
 */
#define MOCKLIB_FUN_MODE_SET(file, fun)     file ## _mock_ ## fun ## _mode_set

#define MOCKLIB_FUN_BASIC_CFG(file, fun)    file ## _mock_ ## fun ## _basic_cfg

#define MOCKLIB_FUN_CB_CFG(file, fun)       file ## _mock_ ## fun ## _cb_cfg

#define MOCKLIB_CB(file, fun)               file ## _ ## fun ## _cb

/**
 * Macro for expect function name of a given function in mock for a given header file.
 *
 * Trace expect function is used to configure mock before usage in trace mode. This
 * function should be called for every expected call to the mocked function. It
 * allows for setting separate return value for every call. It also takes input
 * arguments expected by the mocked function. When mocked function is called, these
 * input arguments are checked against real values and test fails if they don't match.
 * In trace mode also order of calling traced functions matters so even if a
 * function doesn't return any value nor takes any arguments it could be traced.
 *
 * Resulting function:
 * void {file}_mock_{fun}_expect([ret_type, ret][, arg1_type arg1 ...])
 */
#define MOCKLIB_FUN_TRACE_EXPECT(file, fun) file ## _mock_ ## fun ## _trace_expect

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

    /**
     * Mock calls provided callback function, passes all arguments to it and
     * forwards returned value back to caller.
     */
    MOCKLIB_MODE_CALLBACK,
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
