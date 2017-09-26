/*
 * File:    dep_module1_mock.h
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    26.07.2017
 */

#ifndef _DEP_MODULE1_MOCK_H_
#define _DEP_MODULE1_MOCK_H_

void dep_module1_mock_init(void);

typedef void (*dep_module1_dep_no_args_no_ret_cb)(void);

void dep_module1_mock_dep_no_args_no_ret_config(mocklib_mode_t mode);
void dep_module1_mock_dep_no_args_no_ret_expect(void);
void dep_module1_mock_dep_no_args_no_ret_cb_config(dep_module1_dep_no_args_no_ret_cb cb);
int32_t dep_module1_mock_dep_no_args_no_ret_cnt_get(void);

typedef int32_t (*dep_module1_dep_no_args_ret_cb)(void);

void dep_module1_mock_dep_no_args_ret_config(mocklib_mode_t mode, int32_t ret);
void dep_module1_mock_dep_no_args_ret_expect(int32_t ret);
void dep_module1_mock_dep_no_args_ret_cb_config(dep_module1_dep_no_args_ret_cb cb);
int32_t dep_module1_mock_dep_no_args_ret_cnt_get(void);

typedef void (*dep_module1_dep_one_arg_no_ret_cb)(uint16_t arg1);

void dep_module1_mock_dep_one_arg_no_ret_config(mocklib_mode_t mode);
void dep_module1_mock_dep_one_arg_no_ret_expect(uint16_t arg1);
void dep_module1_mock_dep_one_arg_no_ret_cb_config(dep_module1_dep_one_arg_no_ret_cb cb);
int32_t dep_module1_mock_dep_one_arg_no_ret_cnt_get(void);

typedef void (*dep_module1_dep_more_args_no_ret_cb)(int32_t arg1, uint8_t arg2);

void dep_module1_mock_dep_more_args_no_ret_config(mocklib_mode_t mode);
void dep_module1_mock_dep_more_args_no_ret_expect(int32_t arg1, uint8_t arg2);
void dep_module1_mock_dep_more_args_no_ret_cb_config(dep_module1_dep_more_args_no_ret_cb cb);
int32_t dep_module1_mock_dep_more_args_no_ret_cnt_get(void);

typedef uint32_t (*dep_module1_dep_one_arg_ret_cb)(uint32_t arg1);

void dep_module1_mock_dep_one_arg_ret_config(mocklib_mode_t mode, uint32_t ret);
void dep_module1_mock_dep_one_arg_ret_expect(uint32_t ret, uint32_t arg1);
void dep_module1_mock_dep_one_arg_ret_cb_config(dep_module1_dep_one_arg_ret_cb cb);
int32_t dep_module1_mock_dep_one_arg_ret_cnt_get(void);

typedef int8_t (*dep_module1_dep_more_args_ret_cb)(int8_t arg1, int16_t arg2);

void dep_module1_mock_dep_more_args_ret_config(mocklib_mode_t mode, int8_t ret);
void dep_module1_mock_dep_more_args_ret_expect(int8_t ret, int8_t arg1, int16_t arg2);
void dep_module1_mock_dep_more_args_ret_cb_config(dep_module1_dep_more_args_ret_cb cb);
int32_t dep_module1_mock_dep_more_args_ret_cnt_get(void);

#endif /* _DEP_MODULE1_MOCK_H_ */
