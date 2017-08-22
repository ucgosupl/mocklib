/*
 * File:    dep_module1_mock.c
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    26.07.2017
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "mocklib_utlib_defines.h"

#include "mocklib.h"
#include "mocklib_expfun.h"
#include "mocklib_common.h"
#include "mocklib_define.h"

#include "dep_module1/dep_module1.h"
#include "dep_module1_mock.h"
#include "mocks_global.h"

MOCKLIB_MOCK_NORET_ARGS0(dep_module1, dep_no_args_no_ret);

MOCKLIB_MOCK_RET_ARGS0(dep_module1, dep_no_args_ret, int32_t);

MOCKLIB_MOCK_NORET_ARGS1(dep_module1, dep_one_arg_no_ret, uint16_t);

MOCKLIB_MOCK_NORET_ARGS2(dep_module1, dep_more_args_no_ret, int32_t, uint8_t);

MOCKLIB_MOCK_RET_ARGS1(dep_module1, dep_one_arg_ret, uint32_t, uint32_t);

MOCKLIB_MOCK_RET_ARGS2(dep_module1, dep_more_args_ret, int8_t, int8_t, int16_t);

void DEP_MODULE1_MOCK_INIT(void)
{
    /* Reset all mock internal data */
    MOCKLIB_MOCK_INIT(dep_module1, dep_no_args_no_ret);
    MOCKLIB_MOCK_INIT(dep_module1, dep_no_args_ret);
    MOCKLIB_MOCK_INIT(dep_module1, dep_one_arg_no_ret);
    MOCKLIB_MOCK_INIT(dep_module1, dep_more_args_no_ret);
    MOCKLIB_MOCK_INIT(dep_module1, dep_one_arg_ret);
    MOCKLIB_MOCK_INIT(dep_module1, dep_more_args_ret);
}
