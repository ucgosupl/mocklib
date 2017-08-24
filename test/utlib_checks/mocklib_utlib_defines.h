/*
 * File:    mocklib_utlib_defines.h
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    27.07.2017
 */

#ifndef _UTLIB_DEFINES_H_
#define _UTLIB_DEFINES_H_

#include "../utlib_checks/utlib_checks.h"
#define UTLIB_TEST_FAIL_MSG(msg)                utlib_test_fail_msg_check(msg)
#define UTLIB_ASSERT_EQUAL(actual, expected)    utlib_assert_equal(actual, expected)

#endif /* _UTLIB_DEFINES_H_ */
