/*
 * File:    dep_module1_mock.h
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    26.07.2017
 */

#ifndef _DEP_MODULE1_MOCK_H_
#define _DEP_MODULE1_MOCK_H_

enum
{
    /*
     * Call count is updated
     * No argument check
     * Always the same value returned
     */
    MOCK_MODE_BASIC,

    /*
     * Call count is updated
     * Arguments checked for every call
     * Other value returned for every call
     */
    MOCK_MODE_TRACE,
};

void dep_module1_mock_dep_no_args_no_ret_config(int32_t mode);
int32_t dep_module1_mock_dep_no_args_no_ret_cnt_get(void);

void dep_module1_mock_dep_no_args_ret_config(int32_t mode, int32_t ret);
int32_t dep_module1_mock_dep_no_args_ret_cnt_get(void);

void dep_module1_mock_dep_one_arg_no_ret_config(int32_t mode);
int32_t dep_module1_mock_dep_one_arg_no_ret_cnt_get(void);

void dep_module1_mock_dep_more_args_no_ret_config(int32_t mode);
int32_t dep_module1_mock_dep_more_args_no_ret_cnt_get(void);

void dep_module1_mock_dep_one_arg_ret_config(int32_t mode, uint32_t ret);
int32_t dep_module1_mock_dep_one_arg_ret_cnt_get(void);

void dep_module1_mock_dep_more_args_ret_config(int32_t mode, int8_t ret);
int32_t dep_module1_mock_dep_more_args_ret_cnt_get(void);

#endif /* _DEP_MODULE1_MOCK_H_ */
