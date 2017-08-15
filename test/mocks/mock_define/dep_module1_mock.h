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

#define MOCK_INIT						MOCKLIB_FUN_MOCK_INIT(dep_module1)

#define DEP_NO_ARGS_NO_RET_CONFIG		MOCKLIB_FUN_CONFIG(dep_module1, dep_no_args_no_ret)
#define DEP_NO_ARGS_NO_RET_EXPECT		MOCKLIB_FUN_EXPECT(dep_module1, dep_no_args_no_ret)
#define DEP_NO_ARGS_NO_RET_CNT			MOCKLIB_FUN_CNT(dep_module1, dep_no_args_no_ret)

#define DEP_NO_ARGS_RET_CONFIG			MOCKLIB_FUN_CONFIG(dep_module1, dep_no_args_ret)
#define DEP_NO_ARGS_RET_EXPECT			MOCKLIB_FUN_EXPECT(dep_module1, dep_no_args_ret)
#define DEP_NO_ARGS_RET_CNT				MOCKLIB_FUN_CNT(dep_module1, dep_no_args_ret)

#define DEP_ONE_ARG_NO_RET_CONFIG		MOCKLIB_FUN_CONFIG(dep_module1, dep_one_arg_no_ret)
#define DEP_ONE_ARG_NO_RET_EXPECT		MOCKLIB_FUN_EXPECT(dep_module1, dep_one_arg_no_ret)
#define DEP_ONE_ARG_NO_RET_CNT			MOCKLIB_FUN_CNT(dep_module1, dep_one_arg_no_ret)

#define DEP_MORE_ARGS_NO_RET_CONFIG		MOCKLIB_FUN_CONFIG(dep_module1, dep_more_args_no_ret)
#define DEP_MORE_ARGS_NO_RET_EXPECT		MOCKLIB_FUN_EXPECT(dep_module1, dep_more_args_no_ret)
#define DEP_MORE_ARGS_NO_RET_CNT		MOCKLIB_FUN_CNT(dep_module1, dep_more_args_no_ret)

#define DEP_ONE_ARG_RET_CONFIG			MOCKLIB_FUN_CONFIG(dep_module1, dep_one_arg_ret)
#define DEP_ONE_ARG_RET_EXPECT			MOCKLIB_FUN_EXPECT(dep_module1, dep_one_arg_ret)
#define DEP_ONE_ARG_RET_CNT				MOCKLIB_FUN_CNT(dep_module1, dep_one_arg_ret)

#define DEP_MORE_ARGS_RET_CONFIG		MOCKLIB_FUN_CONFIG(dep_module1, dep_more_args_ret)
#define DEP_MORE_ARGS_RET_EXPECT		MOCKLIB_FUN_EXPECT(dep_module1, dep_more_args_ret)
#define DEP_MORE_ARGS_RET_CNT			MOCKLIB_FUN_CNT(dep_module1, dep_more_args_ret)

void MOCK_INIT(void);

void DEP_NO_ARGS_NO_RET_CONFIG(mocklib_mode_t mode);
void DEP_NO_ARGS_NO_RET_EXPECT(void);
int32_t DEP_NO_ARGS_NO_RET_CNT(void);

void DEP_NO_ARGS_RET_CONFIG(mocklib_mode_t mode, int32_t ret);
void DEP_NO_ARGS_RET_EXPECT(int32_t ret);
int32_t DEP_NO_ARGS_RET_CNT(void);

void DEP_ONE_ARG_NO_RET_CONFIG(mocklib_mode_t mode);
void DEP_ONE_ARG_NO_RET_EXPECT(uint16_t arg1);
int32_t DEP_ONE_ARG_NO_RET_CNT(void);

void DEP_MORE_ARGS_NO_RET_CONFIG(mocklib_mode_t mode);
void DEP_MORE_ARGS_NO_RET_EXPECT(int32_t arg1, uint8_t arg2);
int32_t DEP_MORE_ARGS_NO_RET_CNT(void);

void DEP_ONE_ARG_RET_CONFIG(mocklib_mode_t mode, uint32_t ret);
void DEP_ONE_ARG_RET_EXPECT(uint32_t arg1, uint32_t ret);
int32_t DEP_ONE_ARG_RET_CNT(void);

void DEP_MORE_ARGS_RET_CONFIG(mocklib_mode_t mode, int8_t ret);
void DEP_MORE_ARGS_RET_EXPECT(int8_t arg1, int16_t arg2, uint32_t ret);
int32_t DEP_MORE_ARGS_RET_CNT(void);

#endif /* _DEP_MODULE1_MOCK_H_ */
