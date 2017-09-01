/*
 * File:    dep_module1_mock.h
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    26.07.2017
 */

#ifndef _DEP_MODULE1_MOCK_H_
#define _DEP_MODULE1_MOCK_H_

#include "mocklib_define.h"

#define DEP_MODULE1_MOCK_INIT           MOCKLIB_FUN_MOCK_INIT(dep_module1)

void DEP_MODULE1_MOCK_INIT(void);

MOCKLIB_MOCK_HEADER_NORET_ARGS0(dep_module1, dep_no_args_no_ret);

MOCKLIB_MOCK_HEADER_RET_ARGS0(dep_module1, dep_no_args_ret, int32_t);

MOCKLIB_MOCK_HEADER_NORET_ARGS1(dep_module1, dep_one_arg_no_ret, uint16_t);

MOCKLIB_MOCK_HEADER_NORET_ARGS2(dep_module1, dep_more_args_no_ret, int32_t, uint8_t);

MOCKLIB_MOCK_HEADER_RET_ARGS1(dep_module1, dep_one_arg_ret, uint32_t, uint32_t);

MOCKLIB_MOCK_HEADER_RET_ARGS2(dep_module1, dep_more_args_ret, int8_t, int8_t, int16_t);

#endif /* _DEP_MODULE1_MOCK_H_ */
