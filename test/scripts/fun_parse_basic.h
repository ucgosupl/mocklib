/*
 * File:    fun_parse_basic.h
 * Author:  Maciej Gajdzica
 * Brief:   Function prototypes for testing scripts against various return types and arguments.
 *
 * Date:    20.09.2017
 */

#ifndef _FUN_PARSE_BASIC_H_
#define _FUN_PARSE_BASIC_H_

void fun1(arg1_type arg1, arg2_type arg2);
int32_t * fun2(arg1_type *arg1, arg2_type *arg2);
int32_t ** fun3(void);
void fun4(void);

#endif /* _FUN_PARSE_BASIC_H_ */
