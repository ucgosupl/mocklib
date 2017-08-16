/*
 * File:    mocklib_define.h
 * Author:  Maciej Gajdzica
 * Brief:
 *
 * Date:    13.08.2017
 */

#ifndef _MOCKLIB_DEFINE_H_
#define _MOCKLIB_DEFINE_H_

#define MOCKLIB_FUNTYPE(file, fun)		    MOCK_FUNTYPE_ ## file ## _ ## fun

#define MOCKLIB_FUN_MOCK_INIT(file)		    file ## _mock_init
#define MOCKLIB_FUN_CONFIG(file, fun)	    file ## _mock_ ## fun ## _config
#define MOCKLIB_FUN_EXPECT(file, fun)	    file ## _mock_ ## fun ## _expect
#define MOCKLIB_FUN_CNT(file, fun)		    file ## _mock_ ## fun ## _cnt_get

#define MOCKLIB_STRUCT_PARAMS(file, fun)    file ## _ ## fun ## _params
#define MOCKLIB_STRUCT_INTERNAL(file, fun)  file ## _ ## fun ## _expdata_internal

#endif /* _MOCKLIB_DEFINE_H_ */
