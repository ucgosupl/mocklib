/*
 * File:    mocks_global.h
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    13.08.2017
 */

#ifndef _MOCKS_GLOBAL_H_
#define _MOCKS_GLOBAL_H_

enum
{
    MOCK_FUNTYPE_NONE,
	MOCKLIB_FUNTYPE(dep_module1, dep_no_args_no_ret),
	MOCKLIB_FUNTYPE(dep_module1, dep_no_args_ret),
	MOCKLIB_FUNTYPE(dep_module1, dep_one_arg_no_ret),
	MOCKLIB_FUNTYPE(dep_module1, dep_more_args_no_ret),
	MOCKLIB_FUNTYPE(dep_module1, dep_one_arg_ret),
	MOCKLIB_FUNTYPE(dep_module1, dep_more_args_ret),
};

#endif /* _MOCKS_GLOBAL_H_ */
