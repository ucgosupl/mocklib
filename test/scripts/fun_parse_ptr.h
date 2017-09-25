/*
 * File:    fun_parse_ptr.h
 * Author:  Maciej Gajdzica
 * Brief:   Function prototypes for testing scripts against arguments and return types with pointers.
 *
 * Date:    6.09.2017
 */

#ifndef _FUN_PARSE_PTR_H_
#define _FUN_PARSE_PTR_H_

void* mocklib_init(void);
void *mocklib_exp_all_called(void);
void * mocklib_exp_all_called(void);

void** mocklib_init(void);
void* * mocklib_init(void);

void **mocklib_exp_all_called(void);
void * *mocklib_exp_all_called(void);

void ** mocklib_exp_all_called(void);
void * * mocklib_exp_all_called(void);

void mocklib_common_funtype_check(mocklib_expdata_t expdata);
void mocklib_common_funtype_check(mocklib_expdata_t* expdata);
void mocklib_common_funtype_check(mocklib_expdata_t *expdata);
void mocklib_common_funtype_check(mocklib_expdata_t * expdata);
void mocklib_common_funtype_check(mocklib_expdata_t** expdata);
void mocklib_common_funtype_check(mocklib_expdata_t* * expdata);
void mocklib_common_funtype_check(mocklib_expdata_t **expdata);
void mocklib_common_funtype_check(mocklib_expdata_t * *expdata);
void mocklib_common_funtype_check(mocklib_expdata_t ** expdata);
void mocklib_common_funtype_check(mocklib_expdata_t * * expdata);

void mocklib_common_funtype_check(mocklib_expdata_t expdata, type2 arg2);
void mocklib_common_funtype_check(mocklib_expdata_t* expdata, type2 arg2);
void mocklib_common_funtype_check(mocklib_expdata_t *expdata, type2 arg2);
void mocklib_common_funtype_check(mocklib_expdata_t * expdata, type2 arg2);
void mocklib_common_funtype_check(mocklib_expdata_t** expdata, type2 arg2);
void mocklib_common_funtype_check(mocklib_expdata_t* * expdata, type2 arg2);
void mocklib_common_funtype_check(mocklib_expdata_t **expdata, type2 arg2);
void mocklib_common_funtype_check(mocklib_expdata_t * *expdata, type2 arg2);
void mocklib_common_funtype_check(mocklib_expdata_t ** expdata, type2 arg2);
void mocklib_common_funtype_check(mocklib_expdata_t * * expdata, type2 arg2);

void mocklib_common_funtype_check(mocklib_expdata_t expdata, type2 arg2);
void mocklib_common_funtype_check(mocklib_expdata_t expdata, type2* arg2);
void mocklib_common_funtype_check(mocklib_expdata_t expdata, type2 *arg2);
void mocklib_common_funtype_check(mocklib_expdata_t expdata, type2 * arg2);
void mocklib_common_funtype_check(mocklib_expdata_t expdata, type2** arg2);
void mocklib_common_funtype_check(mocklib_expdata_t expdata, type2* * arg2);
void mocklib_common_funtype_check(mocklib_expdata_t expdata, type2 **arg2);
void mocklib_common_funtype_check(mocklib_expdata_t expdata, type2 * *arg2);
void mocklib_common_funtype_check(mocklib_expdata_t expdata, type2 ** arg2);
void mocklib_common_funtype_check(mocklib_expdata_t expdata, type2 * * arg2);

#endif /* _FUN_PARSE_PTR_H_ */
