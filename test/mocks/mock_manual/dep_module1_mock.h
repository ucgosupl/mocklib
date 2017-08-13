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

void dep_module1_mock_dep_no_args_no_ret_config(mocklib_mode_t mode);
void dep_module1_mock_dep_no_args_no_ret_expect(void);
int32_t dep_module1_mock_dep_no_args_no_ret_cnt_get(void);

void dep_module1_mock_dep_no_args_ret_config(mocklib_mode_t mode, int32_t ret);
void dep_module1_mock_dep_no_args_ret_expect(int32_t ret);
int32_t dep_module1_mock_dep_no_args_ret_cnt_get(void);

void dep_module1_mock_dep_one_arg_no_ret_config(mocklib_mode_t mode);
void dep_module1_mock_dep_one_arg_no_ret_expect(uint16_t arg1);
int32_t dep_module1_mock_dep_one_arg_no_ret_cnt_get(void);

void dep_module1_mock_dep_more_args_no_ret_config(mocklib_mode_t mode);
void dep_module1_mock_dep_more_args_no_ret_expect(int32_t arg1, uint8_t arg2);
int32_t dep_module1_mock_dep_more_args_no_ret_cnt_get(void);

void dep_module1_mock_dep_one_arg_ret_config(mocklib_mode_t mode, uint32_t ret);
void dep_module1_mock_dep_one_arg_ret_expect(uint32_t arg1, uint32_t ret);
int32_t dep_module1_mock_dep_one_arg_ret_cnt_get(void);

void dep_module1_mock_dep_more_args_ret_config(mocklib_mode_t mode, int8_t ret);
void dep_module1_mock_dep_more_args_ret_expect(int8_t arg1, int16_t arg2, uint32_t ret);
int32_t dep_module1_mock_dep_more_args_ret_cnt_get(void);

#endif /* _DEP_MODULE1_MOCK_H_ */
