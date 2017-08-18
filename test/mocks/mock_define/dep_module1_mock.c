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

MOCKLIB_PARAMS_NORET(dep_module1, dep_no_args_no_ret);

/* No internal expdata for function with no arguments and no return value. */

static struct MOCKLIB_STRUCT_PARAMS(dep_module1, dep_no_args_no_ret) MOCKLIB_STRUCT_PARAMS(dep_module1, dep_no_args_no_ret);

void MOCKLIB_FUN_CONFIG(dep_module1, dep_no_args_no_ret)(mocklib_mode_t mode)
{
    MOCKLIB_STRUCT_PARAMS(dep_module1, dep_no_args_no_ret).mode = mode;
}

void MOCKLIB_FUN_EXPECT(dep_module1, dep_no_args_no_ret)(void)
{
    mocklib_expdata_t expdata = NULL;

    MOCKLIB_FUN_EXPECT_COMMON(dep_module1, dep_no_args_no_ret);

    mocklib_exp_set(expdata);
}

MOCKLIB_FUN_CNT_IMPL(dep_module1, dep_no_args_no_ret);

void dep_no_args_no_ret(void)
{
    mocklib_expdata_t expdata = NULL;

    MOCKLIB_STRUCT_PARAMS(dep_module1, dep_no_args_no_ret).call_cnt++;

    if (MOCKLIB_MODE_TRACE == MOCKLIB_STRUCT_PARAMS(dep_module1, dep_no_args_no_ret).mode)
    {
        expdata = mocklib_common_expdata_get_and_check();

        mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(dep_module1, dep_no_args_no_ret));
    }
}

MOCKLIB_PARAMS_RET(dep_module1, dep_no_args_ret, int32_t)

struct MOCKLIB_STRUCT_INTERNAL(dep_module1, dep_no_args_ret)
{
    int32_t ret;
};

static struct MOCKLIB_STRUCT_PARAMS(dep_module1, dep_no_args_ret) MOCKLIB_STRUCT_PARAMS(dep_module1, dep_no_args_ret);

void MOCKLIB_FUN_CONFIG(dep_module1, dep_no_args_ret)(mocklib_mode_t mode, int32_t ret)
{
    MOCKLIB_STRUCT_PARAMS(dep_module1, dep_no_args_ret).mode = mode;
    MOCKLIB_STRUCT_PARAMS(dep_module1, dep_no_args_ret).ret = ret;
}

void MOCKLIB_FUN_EXPECT(dep_module1, dep_no_args_ret)(int32_t ret)
{
    mocklib_expdata_t expdata = NULL;
    struct MOCKLIB_STRUCT_INTERNAL(dep_module1, dep_no_args_ret) *internal = NULL;

    MOCKLIB_FUN_EXPECT_COMMON(dep_module1, dep_no_args_ret);

    /* Set expected function call parameters */
    internal = mocklib_common_internal_create_and_check(sizeof(struct MOCKLIB_STRUCT_INTERNAL(dep_module1, dep_no_args_ret)));
    internal->ret = ret;
    mocklib_expdata_internal_set(expdata, internal);

    mocklib_exp_set(expdata);
}

int32_t MOCKLIB_FUN_CNT(dep_module1, dep_no_args_ret)(void)
{
    return MOCKLIB_STRUCT_PARAMS(dep_module1, dep_no_args_ret).call_cnt;
}

int32_t dep_no_args_ret(void)
{
    int32_t retval;
    mocklib_expdata_t expdata = NULL;
    struct MOCKLIB_STRUCT_INTERNAL(dep_module1, dep_no_args_ret) *internal = NULL;

    MOCKLIB_STRUCT_PARAMS(dep_module1, dep_no_args_ret).call_cnt++;

    if (MOCKLIB_MODE_BASIC == MOCKLIB_STRUCT_PARAMS(dep_module1, dep_no_args_ret).mode)
    {
        retval = MOCKLIB_STRUCT_PARAMS(dep_module1, dep_no_args_ret).ret;
    }
    else if (MOCKLIB_MODE_TRACE == MOCKLIB_STRUCT_PARAMS(dep_module1, dep_no_args_ret).mode)
    {
        expdata = mocklib_common_expdata_get_and_check();

        mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(dep_module1, dep_no_args_ret));

        internal = mocklib_common_internal_get_and_check(expdata);

        retval = internal->ret;
    }
    else
    {
        //error
    }

    return retval;
}

MOCKLIB_PARAMS_NORET(dep_module1, dep_one_arg_no_ret);

struct MOCKLIB_STRUCT_INTERNAL(dep_module1, dep_one_arg_no_ret)
{
    uint16_t arg1;
};

static struct MOCKLIB_STRUCT_PARAMS(dep_module1, dep_one_arg_no_ret) MOCKLIB_STRUCT_PARAMS(dep_module1, dep_one_arg_no_ret);

void MOCKLIB_FUN_CONFIG(dep_module1, dep_one_arg_no_ret)(mocklib_mode_t mode)
{
    MOCKLIB_STRUCT_PARAMS(dep_module1, dep_one_arg_no_ret).mode = mode;
}

void MOCKLIB_FUN_EXPECT(dep_module1, dep_one_arg_no_ret)(uint16_t arg1)
{
    mocklib_expdata_t expdata = NULL;
    struct MOCKLIB_STRUCT_INTERNAL(dep_module1, dep_one_arg_no_ret) *internal = NULL;

    MOCKLIB_FUN_EXPECT_COMMON(dep_module1, dep_one_arg_no_ret);

    /* Set expected function call parameters */
    internal = mocklib_common_internal_create_and_check(sizeof(struct MOCKLIB_STRUCT_INTERNAL(dep_module1, dep_one_arg_no_ret)));
    internal->arg1 = arg1;
    mocklib_expdata_internal_set(expdata, internal);

    mocklib_exp_set(expdata);
}

MOCKLIB_FUN_CNT_IMPL(dep_module1, dep_one_arg_no_ret);

void dep_one_arg_no_ret(uint16_t arg1)
{
    mocklib_expdata_t expdata = NULL;
    struct MOCKLIB_STRUCT_INTERNAL(dep_module1, dep_one_arg_no_ret) *internal = NULL;

    MOCKLIB_STRUCT_PARAMS(dep_module1, dep_one_arg_no_ret).call_cnt++;

    if (MOCKLIB_MODE_TRACE == MOCKLIB_STRUCT_PARAMS(dep_module1, dep_one_arg_no_ret).mode)
    {
        expdata = mocklib_common_expdata_get_and_check();

        mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(dep_module1, dep_one_arg_no_ret));

        internal = mocklib_common_internal_get_and_check(expdata);

        UTLIB_ASSERT_EQUAL(internal->arg1, arg1);
    }
}

MOCKLIB_PARAMS_NORET(dep_module1, dep_more_args_no_ret);

struct MOCKLIB_STRUCT_INTERNAL(dep_module1, dep_more_args_no_ret)
{
    int32_t arg1;
    uint8_t arg2;
};

static struct MOCKLIB_STRUCT_PARAMS(dep_module1, dep_more_args_no_ret) MOCKLIB_STRUCT_PARAMS(dep_module1, dep_more_args_no_ret);

void MOCKLIB_FUN_CONFIG(dep_module1, dep_more_args_no_ret)(mocklib_mode_t mode)
{
    MOCKLIB_STRUCT_PARAMS(dep_module1, dep_more_args_no_ret).mode = mode;
}

void MOCKLIB_FUN_EXPECT(dep_module1, dep_more_args_no_ret)(int32_t arg1, uint8_t arg2)
{
    mocklib_expdata_t expdata = NULL;
    struct MOCKLIB_STRUCT_INTERNAL(dep_module1, dep_more_args_no_ret) *internal = NULL;

    MOCKLIB_FUN_EXPECT_COMMON(dep_module1, dep_more_args_no_ret);

    /* Set expected function call parameters */
    internal = mocklib_common_internal_create_and_check(sizeof(struct MOCKLIB_STRUCT_INTERNAL(dep_module1, dep_more_args_no_ret)));
    internal->arg1 = arg1;
    internal->arg2 = arg2;
    mocklib_expdata_internal_set(expdata, internal);

    mocklib_exp_set(expdata);
}

MOCKLIB_FUN_CNT_IMPL(dep_module1, dep_more_args_no_ret);

void dep_more_args_no_ret(int32_t arg1, uint8_t arg2)
{
    mocklib_expdata_t expdata = NULL;
    struct MOCKLIB_STRUCT_INTERNAL(dep_module1, dep_more_args_no_ret) *internal = NULL;

    MOCKLIB_STRUCT_PARAMS(dep_module1, dep_more_args_no_ret).call_cnt++;

    if (MOCKLIB_MODE_TRACE == MOCKLIB_STRUCT_PARAMS(dep_module1, dep_more_args_no_ret).mode)
    {
        expdata = mocklib_common_expdata_get_and_check();

        mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(dep_module1, dep_more_args_no_ret));

        internal = mocklib_common_internal_get_and_check(expdata);

        UTLIB_ASSERT_EQUAL(internal->arg1, arg1);
        UTLIB_ASSERT_EQUAL(internal->arg2, arg2);
    }
}

MOCKLIB_PARAMS_RET(dep_module1, dep_one_arg_ret, uint32_t);

struct MOCKLIB_STRUCT_INTERNAL(dep_module1, dep_one_arg_ret)
{
    uint32_t arg1;

    uint32_t ret;
};

static struct MOCKLIB_STRUCT_PARAMS(dep_module1, dep_one_arg_ret) MOCKLIB_STRUCT_PARAMS(dep_module1, dep_one_arg_ret);

void MOCKLIB_FUN_CONFIG(dep_module1, dep_one_arg_ret)(mocklib_mode_t mode, uint32_t ret)
{
    MOCKLIB_STRUCT_PARAMS(dep_module1, dep_one_arg_ret).mode = mode;
    MOCKLIB_STRUCT_PARAMS(dep_module1, dep_one_arg_ret).ret = ret;
}

void MOCKLIB_FUN_EXPECT(dep_module1, dep_one_arg_ret)(uint32_t arg1, uint32_t ret)
{
    mocklib_expdata_t expdata = NULL;
    struct MOCKLIB_STRUCT_INTERNAL(dep_module1, dep_one_arg_ret) *internal = NULL;

    MOCKLIB_FUN_EXPECT_COMMON(dep_module1, dep_one_arg_ret);

    /* Set expected function call parameters */
    internal = mocklib_common_internal_create_and_check(sizeof(struct MOCKLIB_STRUCT_INTERNAL(dep_module1, dep_one_arg_ret)));
    internal->arg1 = arg1;
    internal->ret = ret;
    mocklib_expdata_internal_set(expdata, internal);

    mocklib_exp_set(expdata);
}

MOCKLIB_FUN_CNT_IMPL(dep_module1, dep_one_arg_ret);

uint32_t dep_one_arg_ret(uint32_t arg1)
{
    uint32_t retval;
    mocklib_expdata_t expdata = NULL;
    struct MOCKLIB_STRUCT_INTERNAL(dep_module1, dep_one_arg_ret) *internal = NULL;

    MOCKLIB_STRUCT_PARAMS(dep_module1, dep_one_arg_ret).call_cnt++;

    if (MOCKLIB_MODE_BASIC == MOCKLIB_STRUCT_PARAMS(dep_module1, dep_one_arg_ret).mode)
    {
        retval = MOCKLIB_STRUCT_PARAMS(dep_module1, dep_one_arg_ret).ret;
    }
    else if (MOCKLIB_MODE_TRACE == MOCKLIB_STRUCT_PARAMS(dep_module1, dep_one_arg_ret).mode)
    {
        expdata = mocklib_common_expdata_get_and_check();

        mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(dep_module1, dep_one_arg_ret));

        internal = mocklib_common_internal_get_and_check(expdata);

        UTLIB_ASSERT_EQUAL(internal->arg1, arg1);
        retval = internal->ret;
    }
    else
    {
        //error
    }

    return retval;
}

MOCKLIB_PARAMS_RET(dep_module1, dep_more_args_ret, int8_t);

struct MOCKLIB_STRUCT_INTERNAL(dep_module1, dep_more_args_ret)
{
    int8_t arg1;
    int16_t arg2;

    int8_t ret;
};

static struct MOCKLIB_STRUCT_PARAMS(dep_module1, dep_more_args_ret) MOCKLIB_STRUCT_PARAMS(dep_module1, dep_more_args_ret);

void MOCKLIB_FUN_CONFIG(dep_module1, dep_more_args_ret)(mocklib_mode_t mode, int8_t ret)
{
    MOCKLIB_STRUCT_PARAMS(dep_module1, dep_more_args_ret).mode = mode;
    MOCKLIB_STRUCT_PARAMS(dep_module1, dep_more_args_ret).ret = ret;
}

void MOCKLIB_FUN_EXPECT(dep_module1, dep_more_args_ret)(int8_t arg1, int16_t arg2, int8_t ret)
{
    mocklib_expdata_t expdata = NULL;
    struct MOCKLIB_STRUCT_INTERNAL(dep_module1, dep_more_args_ret) *internal = NULL;

    MOCKLIB_FUN_EXPECT_COMMON(dep_module1, dep_more_args_ret);

    /* Set expected function call parameters */
    internal = mocklib_common_internal_create_and_check(sizeof(struct MOCKLIB_STRUCT_INTERNAL(dep_module1, dep_more_args_ret)));
    internal->arg1 = arg1;
    internal->arg2 = arg2;
    internal->ret = ret;
    mocklib_expdata_internal_set(expdata, internal);

    mocklib_exp_set(expdata);
}

MOCKLIB_FUN_CNT_IMPL(dep_module1, dep_more_args_ret);

int8_t dep_more_args_ret(int8_t arg1, int16_t arg2)
{
	int8_t retval;
    mocklib_expdata_t expdata = NULL;
    struct MOCKLIB_STRUCT_INTERNAL(dep_module1, dep_more_args_ret) *internal = NULL;

    MOCKLIB_STRUCT_PARAMS(dep_module1, dep_more_args_ret).call_cnt++;

    if (MOCKLIB_MODE_BASIC == MOCKLIB_STRUCT_PARAMS(dep_module1, dep_more_args_ret).mode)
    {
        retval = MOCKLIB_STRUCT_PARAMS(dep_module1, dep_more_args_ret).ret;
    }
    else if (MOCKLIB_MODE_TRACE == MOCKLIB_STRUCT_PARAMS(dep_module1, dep_more_args_ret).mode)
    {
        expdata = mocklib_common_expdata_get_and_check();

        mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(dep_module1, dep_more_args_ret));

        internal = mocklib_common_internal_get_and_check(expdata);

        UTLIB_ASSERT_EQUAL(internal->arg1, arg1);
        UTLIB_ASSERT_EQUAL(internal->arg2, arg2);
        retval = internal->ret;
    }
    else
    {
        //error
    }

    return retval;
}


void MOCK_INIT(void)
{
    /* Reset all mock internal data */
    memset(&MOCKLIB_STRUCT_PARAMS(dep_module1, dep_no_args_no_ret), 0, sizeof(struct MOCKLIB_STRUCT_PARAMS(dep_module1, dep_no_args_no_ret)));
    memset(&MOCKLIB_STRUCT_PARAMS(dep_module1, dep_no_args_ret), 0, sizeof(struct MOCKLIB_STRUCT_PARAMS(dep_module1, dep_no_args_ret)));
    memset(&MOCKLIB_STRUCT_PARAMS(dep_module1, dep_one_arg_no_ret), 0, sizeof(struct MOCKLIB_STRUCT_PARAMS(dep_module1, dep_one_arg_no_ret)));
    memset(&MOCKLIB_STRUCT_PARAMS(dep_module1, dep_more_args_no_ret), 0, sizeof(struct MOCKLIB_STRUCT_PARAMS(dep_module1, dep_more_args_no_ret)));
    memset(&MOCKLIB_STRUCT_PARAMS(dep_module1, dep_one_arg_ret), 0, sizeof(struct MOCKLIB_STRUCT_PARAMS(dep_module1, dep_one_arg_ret)));
    memset(&MOCKLIB_STRUCT_PARAMS(dep_module1, dep_more_args_ret), 0, sizeof(struct MOCKLIB_STRUCT_PARAMS(dep_module1, dep_more_args_ret)));
}
