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

#define MOCKLIB_PARAMS_COMMON_FIELDS   \
        mocklib_mode_t mode; \
        int32_t call_cnt;

#define MOCKLIB_PARAMS_NORET(file, fun) \
        struct MOCKLIB_STRUCT_PARAMS(file, fun) \
        { \
            MOCKLIB_PARAMS_COMMON_FIELDS; \
        };

#define MOCKLIB_PARAMS_RET(file, fun, ret_type) \
        struct MOCKLIB_STRUCT_PARAMS(file, fun) \
        { \
            MOCKLIB_PARAMS_COMMON_FIELDS; \
            ret_type ret; \
        };

#define MOCKLIB_FUN_CNT_IMPL(file, fun) \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void) \
        { \
        return MOCKLIB_STRUCT_PARAMS(file, fun).call_cnt; \
        }

#define MOCKLIB_FUN_EXPECT_COMMON(file, fun) \
        mocklib_common_err_if_mode_not_trace(MOCKLIB_STRUCT_PARAMS(file, fun).mode); \
        expdata = mocklib_common_expdata_create_and_check(); \
        mocklib_expdata_funtype_set(expdata, MOCKLIB_FUNTYPE(file, fun));

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
