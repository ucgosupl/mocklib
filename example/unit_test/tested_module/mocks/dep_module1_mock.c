/*
 * File:    dep_module1_mock.c
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    26.07.2017
 */

#include <stdint.h>
#include <string.h>

#include "dep_module1/dep_module1.h"
#include "dep_module1_mock.h"

struct dep_module1_dep_no_args_no_ret_params
{
    int32_t call_cnt;
};

struct dep_module1_dep_no_args_ret_params
{
    int32_t call_cnt;

    int32_t ret;
};

struct dep_module1_dep_one_arg_no_ret_params
{
    int32_t call_cnt;
};

struct dep_module1_dep_more_args_no_ret_params
{
    int32_t call_cnt;
};

struct dep_module1_dep_one_arg_ret_params
{
    int32_t call_cnt;

    uint32_t ret;
};

struct dep_module1_dep_more_args_ret_params
{
    int32_t call_cnt;

    int8_t ret;
};

static struct dep_module1_dep_no_args_no_ret_params dep_module1_dep_no_args_no_ret_params;
static struct dep_module1_dep_no_args_ret_params dep_module1_dep_no_args_ret_params;
static struct dep_module1_dep_one_arg_no_ret_params dep_module1_dep_one_arg_no_ret_params;
static struct dep_module1_dep_more_args_no_ret_params dep_module1_dep_more_args_no_ret_params;
static struct dep_module1_dep_one_arg_ret_params dep_module1_dep_one_arg_ret_params;
static struct dep_module1_dep_more_args_ret_params dep_module1_dep_more_args_ret_params;

void dep_module1_mock_init(void)
{
    /* Reset all mock internal data */
    memset(&dep_module1_dep_no_args_no_ret_params, 0, sizeof(struct dep_module1_dep_no_args_no_ret_params));
    memset(&dep_module1_dep_no_args_ret_params, 0, sizeof(struct dep_module1_dep_no_args_ret_params));
    memset(&dep_module1_dep_one_arg_no_ret_params, 0, sizeof(struct dep_module1_dep_one_arg_no_ret_params));
    memset(&dep_module1_dep_more_args_no_ret_params, 0, sizeof(struct dep_module1_dep_more_args_no_ret_params));
    memset(&dep_module1_dep_one_arg_ret_params, 0, sizeof(struct dep_module1_dep_one_arg_ret_params));
    memset(&dep_module1_dep_more_args_ret_params, 0, sizeof(struct dep_module1_dep_more_args_ret_params));
}

void dep_module1_mock_dep_no_args_no_ret_config(int32_t mode)
{

}

int32_t dep_module1_mock_dep_no_args_no_ret_cnt_get(void)
{
    return dep_module1_dep_no_args_no_ret_params.call_cnt;
}

void dep_no_args_no_ret(void)
{
    dep_module1_dep_no_args_no_ret_params.call_cnt++;
    /* Log call order */
}

void dep_module1_mock_dep_no_args_ret_config(int32_t mode, int32_t ret)
{
    dep_module1_dep_no_args_ret_params.ret = ret;
}

int32_t dep_module1_mock_dep_no_args_ret_cnt_get(void)
{
    return dep_module1_dep_no_args_ret_params.call_cnt;
}

int32_t dep_no_args_ret(void)
{
    dep_module1_dep_no_args_ret_params.call_cnt++;
    /* Log call order */
    return dep_module1_dep_no_args_ret_params.ret;
}

void dep_module1_mock_dep_one_arg_no_ret_config(int32_t mode)
{

}

int32_t dep_module1_mock_dep_one_arg_no_ret_cnt_get(void)
{
    return dep_module1_dep_one_arg_no_ret_params.call_cnt;
}

void dep_one_arg_no_ret(uint16_t arg1)
{
    dep_module1_dep_one_arg_no_ret_params.call_cnt++;
    /* Log call order */
    /* Save arg1 */
}

void dep_module1_mock_dep_more_args_no_ret_config(int32_t mode)
{

}

int32_t dep_module1_mock_dep_more_args_no_ret_cnt_get(void)
{
    return dep_module1_dep_more_args_no_ret_params.call_cnt;
}

void dep_more_args_no_ret(int32_t arg1, uint8_t arg2)
{
    dep_module1_dep_more_args_no_ret_params.call_cnt++;
    /* Log call order */
    /* Save arg1 */
    /* Save arg2 */
}

void dep_module1_mock_dep_one_arg_ret_config(int32_t mode, uint32_t ret)
{
    dep_module1_dep_one_arg_ret_params.ret = ret;
}

int32_t dep_module1_mock_dep_one_arg_ret_cnt_get(void)
{
    return dep_module1_dep_one_arg_ret_params.call_cnt;
}

uint32_t dep_one_arg_ret(uint32_t arg1)
{
    dep_module1_dep_one_arg_ret_params.call_cnt++;
    /* Log call order */
    /* Save arg1 */
    return dep_module1_dep_one_arg_ret_params.ret;
}

void dep_module1_mock_dep_more_args_ret_config(int32_t mode, int8_t ret)
{
    dep_module1_dep_more_args_ret_params.ret = ret;
}

int32_t dep_module1_mock_dep_more_args_ret_cnt_get(void)
{
    return dep_module1_dep_more_args_ret_params.call_cnt;
}

int8_t dep_more_args_ret(int8_t arg1, int16_t arg2)
{
    dep_module1_dep_more_args_ret_params.call_cnt++;
    /* Log call order */
    /* Save arg1 */
    /* Save arg2 */
    return dep_module1_dep_more_args_ret_params.ret;
}
