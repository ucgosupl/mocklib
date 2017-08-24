/*
 * File:    utlib_checks.h
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    27.07.2017
 */

#ifndef _UTLIB_CHECKS_H_
#define _UTLIB_CHECKS_H_

void utlib_test_fail_msg_init(const char * msg);
void utlib_test_fail_msg_check(const char * msg);

void utlib_assert_equal_init(int32_t exp_fail);
void utlib_assert_equal(int32_t actual, int32_t expected);

#endif /* _UTLIB_CHECKS_H_ */
