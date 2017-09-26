/*
 *
 *                  This software is part of UniAC2 system
 *
 *          VOESTALPINE SIGNALING SOPOT COMPANY PROPRIETARY INFORMATION
 *   This software was created by Voestalpine SIGNALING Sopot and is supplied under
 *        the terms of a license agreement or nondisclosure agreement with
 *  Voestalpine SIGNALING Sopot Company and may not be copied or disclosed except in
 *                  accordance with the terms of that agreement.
 *    Copyright(c) 2016 Voestalpine SIGNALING Sopot Company. All Rights Reserved.
 *
 *     REDISTRIBUTION OF THIS SOURCE CODE MUST RETAIN THE ABOVE COPYRIGHT NOTICE
 *
 */

/*
 * File:    mocks_test_test_callback.c
 * Author:  mgajdzica
 * Brief:   Short brief.
 *
 * Date:    26 wrz 2017
 */

#include "unity_fixture.h"

#include <stddef.h>
#include <string.h>

#include "dep_module1/dep_module1.h"

#include "mocklib.h"
#include "mocklib_internal.h"
#include "utlib_checks.h"
#include "dep_module1_mock.h"

struct dep_no_args_no_ret_cb_params
{
    int32_t cnt;
};

struct dep_no_args_ret_cb_params
{
    int32_t cnt;

    int32_t ret;
};

struct dep_one_arg_no_ret_cb_params
{
    int32_t cnt;

    uint16_t arg1;
};

struct dep_more_args_no_ret_cb_params
{
    int32_t cnt;

    int32_t arg1;
    uint8_t arg2;
};

struct dep_one_arg_ret_cb_params
{
    int32_t cnt;

    uint16_t arg1;

    uint32_t ret;
};

struct dep_more_args_ret_cb_params
{
    int32_t cnt;

    int8_t arg1;
    int16_t arg2;

    int8_t ret;
};

static struct dep_no_args_no_ret_cb_params dep_no_args_no_ret_cb_params;
static struct dep_no_args_ret_cb_params dep_no_args_ret_cb_params;
static struct dep_one_arg_no_ret_cb_params dep_one_arg_no_ret_cb_params;
static struct dep_more_args_no_ret_cb_params dep_more_args_no_ret_cb_params;
static struct dep_one_arg_ret_cb_params dep_one_arg_ret_cb_params;
static struct dep_more_args_ret_cb_params dep_more_args_ret_cb_params;

static void dep_no_args_no_ret_cb(void);
static int32_t dep_no_args_ret_cb(void);
static void dep_one_arg_no_ret_cb(uint16_t arg1);
static void dep_more_args_no_ret_cb(int32_t arg1, uint8_t arg2);
static uint32_t dep_one_arg_ret_cb(uint32_t arg1);
static int8_t dep_more_args_ret_cb(int8_t arg1, int16_t arg2);

TEST_GROUP(mocks_callback);

TEST_SETUP(mocks_callback)
{
    mocklib_init();

    dep_module1_mock_init();

    utlib_test_fail_msg_init(NULL);
    utlib_assert_equal_init(0);

    memset(&dep_no_args_no_ret_cb_params, 0, sizeof(struct dep_no_args_no_ret_cb_params));
    memset(&dep_no_args_ret_cb_params, 0, sizeof(struct dep_no_args_ret_cb_params));
    memset(&dep_one_arg_no_ret_cb_params, 0, sizeof(struct dep_one_arg_no_ret_cb_params));
    memset(&dep_more_args_no_ret_cb_params, 0, sizeof(struct dep_more_args_no_ret_cb_params));
    memset(&dep_one_arg_ret_cb_params, 0, sizeof(struct dep_one_arg_ret_cb_params));
    memset(&dep_more_args_ret_cb_params, 0, sizeof(struct dep_more_args_ret_cb_params));
}

TEST_TEAR_DOWN(mocks_callback)
{
    mocklib_init();
}

TEST(mocks_callback, no_args_no_ret_fail_when_wrong_mode_passed_to_cb_config)
{
    dep_module1_mock_dep_no_args_no_ret_mode_set(MOCKLIB_MODE_BASIC);

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("Expect function shall be called only in callback mode");

    dep_module1_mock_dep_no_args_no_ret_cb_cfg(NULL);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_callback, no_args_no_ret_cb_called)
{
    dep_module1_mock_dep_no_args_no_ret_mode_set(MOCKLIB_MODE_CALLBACK);
    dep_module1_mock_dep_no_args_no_ret_cb_cfg(dep_no_args_no_ret_cb);

    dep_no_args_no_ret();

    TEST_ASSERT_EQUAL(1, dep_no_args_no_ret_cb_params.cnt);
}

TEST(mocks_callback, no_args_ret_fail_when_wrong_mode_passed_to_cb_config)
{
    dep_module1_mock_dep_no_args_ret_mode_set(MOCKLIB_MODE_BASIC);

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("Expect function shall be called only in callback mode");

    dep_module1_mock_dep_no_args_ret_cb_cfg(NULL);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_callback, no_args_ret_cb_called)
{
    dep_module1_mock_dep_no_args_ret_mode_set(MOCKLIB_MODE_CALLBACK);
    dep_module1_mock_dep_no_args_ret_cb_cfg(dep_no_args_ret_cb);

    dep_no_args_ret();

    TEST_ASSERT_EQUAL(1, dep_no_args_ret_cb_params.cnt);
}

TEST(mocks_callback, no_args_ret_retval)
{
    int32_t ret_expected;
    int32_t ret_actual;

    ret_expected = 1234;
    dep_no_args_ret_cb_params.ret = ret_expected;
    dep_module1_mock_dep_no_args_ret_mode_set(MOCKLIB_MODE_CALLBACK);
    dep_module1_mock_dep_no_args_ret_cb_cfg(dep_no_args_ret_cb);

    ret_actual = dep_no_args_ret();

    TEST_ASSERT_EQUAL(ret_expected, ret_actual);
}

TEST(mocks_callback, one_arg_no_ret_fail_when_wrong_mode_passed_to_cb_config)
{
    dep_module1_mock_dep_one_arg_no_ret_mode_set(MOCKLIB_MODE_BASIC);

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("Expect function shall be called only in callback mode");

    dep_module1_mock_dep_one_arg_no_ret_cb_cfg(NULL);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_callback, one_arg_no_ret_cb_called)
{
    dep_module1_mock_dep_one_arg_no_ret_mode_set(MOCKLIB_MODE_CALLBACK);
    dep_module1_mock_dep_one_arg_no_ret_cb_cfg(dep_one_arg_no_ret_cb);

    dep_one_arg_no_ret(0);

    TEST_ASSERT_EQUAL(1, dep_one_arg_no_ret_cb_params.cnt);
}

TEST(mocks_callback, one_arg_no_ret_args)
{
    uint16_t arg1;

    arg1 = 0xAAAA;
    dep_module1_mock_dep_one_arg_no_ret_mode_set(MOCKLIB_MODE_CALLBACK);
    dep_module1_mock_dep_one_arg_no_ret_cb_cfg(dep_one_arg_no_ret_cb);

    dep_one_arg_no_ret(arg1);

    TEST_ASSERT_EQUAL(arg1, dep_one_arg_no_ret_cb_params.arg1);
}

TEST(mocks_callback, more_args_no_ret_fail_when_wrong_mode_passed_to_cb_config)
{
    dep_module1_mock_dep_more_args_no_ret_mode_set(MOCKLIB_MODE_BASIC);

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("Expect function shall be called only in callback mode");

    dep_module1_mock_dep_more_args_no_ret_cb_cfg(NULL);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_callback, more_args_no_ret_cb_called)
{
    dep_module1_mock_dep_more_args_no_ret_mode_set(MOCKLIB_MODE_CALLBACK);
    dep_module1_mock_dep_more_args_no_ret_cb_cfg(dep_more_args_no_ret_cb);

    dep_more_args_no_ret(0, 0);

    TEST_ASSERT_EQUAL(1, dep_more_args_no_ret_cb_params.cnt);
}

TEST(mocks_callback, more_args_no_ret_args)
{
    int32_t arg1;
    uint8_t arg2;

    arg1 = 1234;
    arg2 = 0xAA;
    dep_module1_mock_dep_more_args_no_ret_mode_set(MOCKLIB_MODE_CALLBACK);
    dep_module1_mock_dep_more_args_no_ret_cb_cfg(dep_more_args_no_ret_cb);

    dep_more_args_no_ret(arg1, arg2);

    TEST_ASSERT_EQUAL(arg1, dep_more_args_no_ret_cb_params.arg1);
    TEST_ASSERT_EQUAL(arg2, dep_more_args_no_ret_cb_params.arg2);
}

TEST(mocks_callback, one_arg_ret_fail_when_wrong_mode_passed_to_cb_config)
{
    dep_module1_mock_dep_one_arg_ret_mode_set(MOCKLIB_MODE_BASIC);

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("Expect function shall be called only in callback mode");

    dep_module1_mock_dep_one_arg_ret_cb_cfg(NULL);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_callback, one_arg_ret_cb_called)
{
    dep_module1_mock_dep_one_arg_ret_mode_set(MOCKLIB_MODE_CALLBACK);
    dep_module1_mock_dep_one_arg_ret_cb_cfg(dep_one_arg_ret_cb);

    dep_one_arg_ret(0);

    TEST_ASSERT_EQUAL(1, dep_one_arg_ret_cb_params.cnt);
}

TEST(mocks_callback, one_arg_ret_retval)
{
    uint32_t ret_expected;
    uint32_t ret_actual;

    ret_expected = 0xAAAAAAAA;
    dep_one_arg_ret_cb_params.ret = ret_expected;
    dep_module1_mock_dep_one_arg_ret_mode_set(MOCKLIB_MODE_CALLBACK);
    dep_module1_mock_dep_one_arg_ret_cb_cfg(dep_one_arg_ret_cb);

    ret_actual = dep_one_arg_ret(0);

    TEST_ASSERT_EQUAL(ret_expected, ret_actual);
}

TEST(mocks_callback, one_arg_ret_args)
{
    uint32_t arg1;

    arg1 = 1234;
    dep_module1_mock_dep_one_arg_ret_mode_set(MOCKLIB_MODE_CALLBACK);
    dep_module1_mock_dep_one_arg_ret_cb_cfg(dep_one_arg_ret_cb);

    dep_one_arg_ret(arg1);

    TEST_ASSERT_EQUAL(arg1, dep_one_arg_ret_cb_params.arg1);
}

TEST(mocks_callback, more_args_ret_fail_when_wrong_mode_passed_to_cb_config)
{
    dep_module1_mock_dep_more_args_ret_mode_set(MOCKLIB_MODE_BASIC);

    /* Expect mock to call test fail next */
    utlib_test_fail_msg_init("Expect function shall be called only in callback mode");

    dep_module1_mock_dep_more_args_ret_cb_cfg(NULL);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocks_callback, more_args_ret_cb_called)
{
    dep_module1_mock_dep_more_args_ret_mode_set(MOCKLIB_MODE_CALLBACK);
    dep_module1_mock_dep_more_args_ret_cb_cfg(dep_more_args_ret_cb);

    dep_more_args_ret(0, 0);

    TEST_ASSERT_EQUAL(1, dep_more_args_ret_cb_params.cnt);
}

TEST(mocks_callback, more_args_ret_retval)
{
    int8_t ret_expected;
    int8_t ret_actual;

    ret_expected = 123;
    dep_more_args_ret_cb_params.ret = ret_expected;
    dep_module1_mock_dep_more_args_ret_mode_set(MOCKLIB_MODE_CALLBACK);
    dep_module1_mock_dep_more_args_ret_cb_cfg(dep_more_args_ret_cb);

    ret_actual = dep_more_args_ret(0, 0);

    TEST_ASSERT_EQUAL(ret_expected, ret_actual);
}

TEST(mocks_callback, more_args_ret_args)
{
    int8_t arg1;
    int16_t arg2;

    arg1 = 123;
    arg2 = 1234;
    dep_module1_mock_dep_more_args_ret_mode_set(MOCKLIB_MODE_CALLBACK);
    dep_module1_mock_dep_more_args_ret_cb_cfg(dep_more_args_ret_cb);

    dep_more_args_ret(arg1, arg2);

    TEST_ASSERT_EQUAL(arg1, dep_more_args_ret_cb_params.arg1);
    TEST_ASSERT_EQUAL(arg2, dep_more_args_ret_cb_params.arg2);
}

static void dep_no_args_no_ret_cb(void)
{
    dep_no_args_no_ret_cb_params.cnt++;
}

static int32_t dep_no_args_ret_cb(void)
{
    dep_no_args_ret_cb_params.cnt++;

    return dep_no_args_ret_cb_params.ret;

}

static void dep_one_arg_no_ret_cb(uint16_t arg1)
{
    dep_one_arg_no_ret_cb_params.cnt++;

    dep_one_arg_no_ret_cb_params.arg1 = arg1;
}

static void dep_more_args_no_ret_cb(int32_t arg1, uint8_t arg2)
{
    dep_more_args_no_ret_cb_params.cnt++;

    dep_more_args_no_ret_cb_params.arg1 = arg1;
    dep_more_args_no_ret_cb_params.arg2 = arg2;
}

static uint32_t dep_one_arg_ret_cb(uint32_t arg1)
{
    dep_one_arg_ret_cb_params.cnt++;

    dep_one_arg_ret_cb_params.arg1 = arg1;

    return dep_one_arg_ret_cb_params.ret;
}

static int8_t dep_more_args_ret_cb(int8_t arg1, int16_t arg2)
{
    dep_more_args_ret_cb_params.cnt++;

    dep_more_args_ret_cb_params.arg1 = arg1;
    dep_more_args_ret_cb_params.arg2 = arg2;

    return dep_more_args_ret_cb_params.ret;
}
