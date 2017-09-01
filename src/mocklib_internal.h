/*
 * File:    mocklib_internal.h
 * Author:  Maciej Gajdzica
 * Brief:   Symbols used by library internally.
 *
 * Date:    23.08.2017
 */

#ifndef _MOCKLIB_INTERNAL_H_
#define _MOCKLIB_INTERNAL_H_

#ifndef UNIT_TEST
#define PRIVATE     static
#else
#define PRIVATE
#endif

/** Type for expected function data - storing return value and expected parameters. */
typedef struct expfun_record * mocklib_expdata_t;

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

#endif /* _MOCKLIB_INTERNAL_H_ */
