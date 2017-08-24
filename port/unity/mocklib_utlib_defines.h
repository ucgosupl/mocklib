/*
 * File:    mocklib_utlib_defines.h
 * Author:  Maciej Gajdzica
 * Brief:   Test framework defines used by mocklib for Unity.
 *
 * Date:    24.08.2017
 */

#ifndef _UTLIB_DEFINES_H_
#define _UTLIB_DEFINES_H_

#include "unity_fixture.h"
#define UTLIB_TEST_FAIL_MSG(msg)                TEST_FAIL_MESSAGE(msg)
#define UTLIB_ASSERT_EQUAL(actual, expected)    TEST_ASSERT_EQUAL(msg)

#endif /* _UTLIB_DEFINES_H_ */
