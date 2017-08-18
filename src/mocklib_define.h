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

#define MOCKLIB_MOCK_HEADER_NORET_ARGS0(file, fun) \
        void MOCKLIB_FUN_CONFIG(file, fun)(mocklib_mode_t mode); \
        void MOCKLIB_FUN_EXPECT(file, fun)(void); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

#define MOCKLIB_MOCK_HEADER_NORET_ARGS1(file, fun, arg1_type) \
        void MOCKLIB_FUN_CONFIG(file, fun)(mocklib_mode_t mode); \
        void MOCKLIB_FUN_EXPECT(file, fun)(arg1_type arg1); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

#define MOCKLIB_MOCK_HEADER_NORET_ARGS2(file, fun, arg1_type, arg2_type) \
        void MOCKLIB_FUN_CONFIG(file, fun)(mocklib_mode_t mode); \
        void MOCKLIB_FUN_EXPECT(file, fun)(arg1_type arg1, arg2_type arg2); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

/* TODO: defines for more args */

#define MOCKLIB_MOCK_HEADER_RET_ARGS0(file, fun, ret_type) \
        void MOCKLIB_FUN_CONFIG(file, fun)(mocklib_mode_t mode, ret_type ret); \
        void MOCKLIB_FUN_EXPECT(file, fun)(ret_type ret); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

#define MOCKLIB_MOCK_HEADER_RET_ARGS1(file, fun, ret_type, arg1_type) \
        void MOCKLIB_FUN_CONFIG(file, fun)(mocklib_mode_t mode, ret_type ret); \
        void MOCKLIB_FUN_EXPECT(file, fun)(arg1_type arg1, ret_type ret); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

#define MOCKLIB_MOCK_HEADER_RET_ARGS2(file, fun, ret_type, arg1_type, arg2_type) \
        void MOCKLIB_FUN_CONFIG(file, fun)(mocklib_mode_t mode, ret_type ret); \
        void MOCKLIB_FUN_EXPECT(file, fun)(arg1_type arg1, arg2_type arg2, ret_type ret); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

/* TODO: defines for more args */

#endif /* _MOCKLIB_DEFINE_H_ */
