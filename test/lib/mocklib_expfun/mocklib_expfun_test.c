/* 
 * File:    mocklib_expfun_test.c
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    24.08.2017
 */

#include "unity_fixture.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "mocklib.h"
#include "mocklib_internal.h"
#include "mocklib_expfun.h"

#include "mocks/mocklib_expfun_test_mocks.h"
#include "utlib_malloc.h"
#include "utlib_checks.h"

TEST_GROUP(mocklib_expfun);

TEST_SETUP(mocklib_expfun)
{

}

TEST_TEAR_DOWN(mocklib_expfun)
{

}

TEST(mocklib_expfun, create_correct_size_passed_to_malloc)
{
    mock_malloc_init(NULL);

    mocklib_expdata_create();

    TEST_ASSERT_EQUAL(1, mock_malloc_cnt_get());
    TEST_ASSERT_EQUAL(sizeof(struct expfun_record), mock_malloc_arg_size_get());
}

TEST(mocklib_expfun, create_retval_passed_from_malloc)
{
    struct expfun_record expdata;

    mock_malloc_init(NULL);
    TEST_ASSERT_EQUAL(NULL, mocklib_expdata_create());

    mock_malloc_init(&expdata);
    TEST_ASSERT_EQUAL(&expdata, mocklib_expdata_create());
}

TEST(mocklib_expfun, create_returned_value_initialized)
{
    struct expfun_record expdata;

    expdata.funtype = 0x55555555;
    expdata.internal = (void *)0xAAAAAAAA;
    mock_malloc_init(&expdata);

    mocklib_expdata_create();

    TEST_ASSERT_EQUAL(0, expdata.funtype);
    TEST_ASSERT_EQUAL_PTR(NULL, expdata.internal);
}

TEST(mocklib_expfun, destroy_free_not_called_when_null)
{
    mocklib_expdata_destroy(NULL);

    TEST_ASSERT_EQUAL(0, mock_free_cnt_get());
}

TEST(mocklib_expfun, destroy_free_called)
{
    struct expfun_record expdata;

    expdata.internal = NULL;
    mock_free_init();

    mocklib_expdata_destroy(&expdata);

    TEST_ASSERT_EQUAL(1, mock_free_cnt_get());
    TEST_ASSERT_EQUAL_PTR(&expdata, mock_free_arg_obj_get());
}

TEST(mocklib_expfun, destroy_free_internal_data_if_exist)
{
    struct expfun_record expdata;

    expdata.internal = NULL;
    mock_free_init();

    mocklib_expdata_destroy(&expdata);

    TEST_ASSERT_EQUAL(1, mock_free_cnt_get());

    expdata.internal = (void *)1;
    mock_free_init();

    mocklib_expdata_destroy(&expdata);

    TEST_ASSERT_EQUAL(2, mock_free_cnt_get());
}

TEST(mocklib_expfun, expdata_set_fail_when_null)
{
    utlib_test_fail_msg_init("Invalid expected function data");

    mocklib_expdata_funtype_set(NULL, 0);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocklib_expfun, expdata_get_fail_when_null)
{
    utlib_test_fail_msg_init("Invalid expected function data");

    mocklib_expdata_funtype_get(NULL);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocklib_expfun, expdata_get_returns_value_set_earlier)
{
    struct expfun_record expdata;
    mocklib_funtype_t funtype;

    funtype = 5;

    mocklib_expdata_funtype_set(&expdata, funtype);
    TEST_ASSERT_EQUAL(funtype, mocklib_expdata_funtype_get(&expdata));

    funtype = 15;

    mocklib_expdata_funtype_set(&expdata, funtype);
    TEST_ASSERT_EQUAL(funtype, mocklib_expdata_funtype_get(&expdata));
}

TEST(mocklib_expfun, internal_set_fail_when_null)
{
    utlib_test_fail_msg_init("Invalid expected function data");

    mocklib_expdata_internal_set(NULL, NULL);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocklib_expfun, internal_get_fail_when_null)
{
    utlib_test_fail_msg_init("Invalid expected function data");

    mocklib_expdata_internal_get(NULL);

    TEST_FAIL_MESSAGE("Test should never reach this line!");
}

TEST(mocklib_expfun, internal_get_returns_value_set_earlier)
{
    struct expfun_record expdata;
    void *internal;

    internal = NULL;

    mocklib_expdata_internal_set(&expdata, internal);
    TEST_ASSERT_EQUAL(internal, mocklib_expdata_internal_get(&expdata));

    internal = (void *)15;

    mocklib_expdata_internal_set(&expdata, internal);
    TEST_ASSERT_EQUAL(internal, mocklib_expdata_internal_get(&expdata));
}
