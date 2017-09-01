/*
 * File:    dep_module1.h
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    26.07.2017
 */

#ifndef _DEP_MODULE1_H_
#define _DEP_MODULE1_H_

void dep_no_args_no_ret(void);
int32_t dep_no_args_ret(void);
void dep_one_arg_no_ret(uint16_t arg1);
void dep_more_args_no_ret(int32_t arg1, uint8_t arg2);
uint32_t dep_one_arg_ret(uint32_t arg1);
int8_t dep_more_args_ret(int8_t arg1, int16_t arg2);

#endif /* _DEP_MODULE1_H_ */
