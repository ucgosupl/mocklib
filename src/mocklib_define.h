/*
 * File:    mocklib_define.h
 * Author:  Maciej Gajdzica
 * Brief:   Macros creating mock interface for a given module and function.
 *
 * Date:    13.08.2017
 */

#ifndef _MOCKLIB_DEFINE_H_
#define _MOCKLIB_DEFINE_H_

/** Name of mocked function id in funtype enum. */
#define MOCKLIB_FUNTYPE(file, fun)		    MOCK_FUNTYPE_ ## file ## _ ## fun

/** Name of mock params structure. */
#define MOCKLIB_STRUCT_PARAMS(file, fun)    file ## _ ## fun ## _params

/** Name of mock internal data structure. */
#define MOCKLIB_STRUCT_INTERNAL(file, fun)  file ## _ ## fun ## _expdata_internal

/** Fields in mock params structure common to all mock types. */
#define MOCKLIB_PARAMS_COMMON_FIELDS   \
        mocklib_mode_t mode; \
        int32_t call_cnt;

/** Mock params structure definition for mocked functions with no return value. */
#define MOCKLIB_PARAMS_NORET(file, fun) \
        struct MOCKLIB_STRUCT_PARAMS(file, fun) \
        { \
            MOCKLIB_PARAMS_COMMON_FIELDS; \
            MOCKLIB_CB(file, fun) cb; \
        };

/** Mock params structure definition for mocked functions with return value. */
#define MOCKLIB_PARAMS_RET(file, fun, ret_type) \
        struct MOCKLIB_STRUCT_PARAMS(file, fun) \
        { \
            MOCKLIB_PARAMS_COMMON_FIELDS; \
            ret_type ret; \
            MOCKLIB_CB(file, fun) cb; \
        };

/** Implementation of mock cmode set function common to all mock types */
#define MOCKLIB_FUN_MODE_SET_IMPL(file, fun) \
        void MOCKLIB_FUN_MODE_SET(file, fun)(mocklib_mode_t mode)\
        {\
            MOCKLIB_STRUCT_PARAMS(file, fun).mode = mode;\
        }

/** Implementation of mock callback config function common to all mock types */
#define MOCKLIB_FUN_CB_CFG_IMPL(file, fun) \
        void MOCKLIB_FUN_CB_CFG(file, fun)(MOCKLIB_CB(file, fun) cb) \
        {\
                mocklib_common_err_if_mode_not_cb(MOCKLIB_STRUCT_PARAMS(file, fun).mode); \
                mocklib_common_cb_check((void *)cb); \
                MOCKLIB_STRUCT_PARAMS(file, fun).cb = cb; \
        }

/** Implementation of mock cnt get function common to all mock types. */
#define MOCKLIB_FUN_CNT_IMPL(file, fun) \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void) \
        { \
        return MOCKLIB_STRUCT_PARAMS(file, fun).call_cnt; \
        }

/** Fragment of mock trace expect function common to all mock types. */
#define MOCKLIB_FUN_TRACE_EXPECT_COMMON(file, fun) \
        mocklib_common_err_if_mode_not_trace(MOCKLIB_STRUCT_PARAMS(file, fun).mode); \
        expdata = mocklib_common_expdata_create_and_check(); \
        mocklib_expdata_funtype_set(expdata, MOCKLIB_FUNTYPE(file, fun));

/** Initialization procedure for a specific mock. */
#define MOCKLIB_MOCK_INIT(file, fun) \
        memset(&MOCKLIB_STRUCT_PARAMS(file, fun), 0, sizeof(struct MOCKLIB_STRUCT_PARAMS(file, fun)));

/** Mock interface declaration for mocked function with no return value and no arguments. */
#define MOCKLIB_MOCK_HEADER_NORET_ARGS0(file, fun) \
        typedef void (*MOCKLIB_CB(file, fun))(void); \
        void MOCKLIB_FUN_MODE_SET(file, fun)(mocklib_mode_t mode); \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(void); \
        void MOCKLIB_FUN_CB_CFG(file, fun)(MOCKLIB_CB(file, fun) cb); \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(void); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

/** Mock implementation for mocked function with no return value and no arguments. */
#define MOCKLIB_MOCK_NORET_ARGS0(file, fun) \
        MOCKLIB_PARAMS_NORET(file, fun); \
        static struct MOCKLIB_STRUCT_PARAMS(file, fun) \
            MOCKLIB_STRUCT_PARAMS(file, fun); \
        \
        MOCKLIB_FUN_MODE_SET_IMPL(file, fun)\
        \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(void) \
        {\
        }\
        \
        MOCKLIB_FUN_CB_CFG_IMPL(file, fun) \
        \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(void) \
        {\
            mocklib_expdata_t expdata = NULL; \
            MOCKLIB_FUN_TRACE_EXPECT_COMMON(file, fun); \
            mocklib_exp_set(expdata); \
        }\
        \
        MOCKLIB_FUN_CNT_IMPL(file, fun); \
        \
        void fun(void) \
        { \
            mocklib_expdata_t expdata = NULL; \
            MOCKLIB_STRUCT_PARAMS(file, fun).call_cnt++; \
            switch (MOCKLIB_STRUCT_PARAMS(file, fun).mode) \
            {\
            case MOCKLIB_MODE_BASIC: \
                break;\
            case MOCKLIB_MODE_TRACE: \
                expdata = mocklib_exp_get(); \
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun)); \
                break; \
            case MOCKLIB_MODE_CALLBACK: \
                MOCKLIB_STRUCT_PARAMS(file, fun).cb(); \
                break; \
            default: \
                break; \
            }\
        }

/** Mock interface declaration for mocked function with no return value and 1 argument. */
#define MOCKLIB_MOCK_HEADER_NORET_ARGS1(file, fun, arg1_type) \
        typedef void (*MOCKLIB_CB(file, fun))(arg1_type arg1); \
        void MOCKLIB_FUN_MODE_SET(file, fun)(mocklib_mode_t mode); \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(void); \
        void MOCKLIB_FUN_CB_CFG(file, fun)(MOCKLIB_CB(file, fun) cb); \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(arg1_type arg1); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

/** Mock implementation for mocked function with no return value and 1 argument. */
#define MOCKLIB_MOCK_NORET_ARGS1(file, fun, arg1_type) \
        MOCKLIB_PARAMS_NORET(file, fun); \
        struct MOCKLIB_STRUCT_INTERNAL(file, fun) \
        { \
            arg1_type arg1; \
        }; \
        static struct MOCKLIB_STRUCT_PARAMS(file, fun) \
            MOCKLIB_STRUCT_PARAMS(file, fun); \
        \
        MOCKLIB_FUN_MODE_SET_IMPL(file, fun)\
        \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(void) \
        {\
        }\
        \
        MOCKLIB_FUN_CB_CFG_IMPL(file, fun) \
        \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(arg1_type arg1) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_FUN_TRACE_EXPECT_COMMON(file, fun); \
            internal = mocklib_common_internal_create_and_check(sizeof(struct MOCKLIB_STRUCT_INTERNAL(file, fun))); \
            internal->arg1 = arg1; \
            mocklib_expdata_internal_set(expdata, internal); \
            mocklib_exp_set(expdata); \
        } \
        \
        MOCKLIB_FUN_CNT_IMPL(file, fun); \
        \
        void fun(arg1_type arg1) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_STRUCT_PARAMS(file, fun).call_cnt++; \
            \
            switch (MOCKLIB_STRUCT_PARAMS(file, fun).mode) \
            {\
            case MOCKLIB_MODE_BASIC:\
                break;\
            case MOCKLIB_MODE_TRACE:\
                expdata = mocklib_exp_get();\
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun));\
                internal = mocklib_common_internal_get_and_check(expdata);\
                UTLIB_ASSERT_EQUAL(internal->arg1, arg1);\
                break;\
            case MOCKLIB_MODE_CALLBACK:\
                MOCKLIB_STRUCT_PARAMS(file, fun).cb(arg1);\
                break;\
            default:\
                break;\
            }\
        }\

/** Mock interface declaration for mocked function with no return value and 2 arguments. */
#define MOCKLIB_MOCK_HEADER_NORET_ARGS2(file, fun, arg1_type, arg2_type) \
        typedef void (*MOCKLIB_CB(file, fun))(arg1_type arg1, arg2_type arg2); \
        void MOCKLIB_FUN_MODE_SET(file, fun)(mocklib_mode_t mode); \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(void); \
        void MOCKLIB_FUN_CB_CFG(file, fun)(MOCKLIB_CB(file, fun) cb); \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(arg1_type arg1, arg2_type arg2); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

/** Mock implementation for mocked function with no return value and 2 arguments. */
#define MOCKLIB_MOCK_NORET_ARGS2(file, fun, arg1_type, arg2_type) \
        MOCKLIB_PARAMS_NORET(file, fun); \
        struct MOCKLIB_STRUCT_INTERNAL(file, fun) \
        { \
            arg1_type arg1; \
            arg2_type arg2; \
        }; \
        static struct MOCKLIB_STRUCT_PARAMS(file, fun) \
        MOCKLIB_STRUCT_PARAMS(file, fun); \
        \
        MOCKLIB_FUN_MODE_SET_IMPL(file, fun)\
        \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(void) \
        {\
        }\
        \
        MOCKLIB_FUN_CB_CFG_IMPL(file, fun) \
        \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(arg1_type arg1, arg2_type arg2) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_FUN_TRACE_EXPECT_COMMON(file, fun); \
            internal = mocklib_common_internal_create_and_check(sizeof(struct MOCKLIB_STRUCT_INTERNAL(file, fun))); \
            internal->arg1 = arg1; \
            internal->arg2 = arg2; \
            mocklib_expdata_internal_set(expdata, internal); \
            mocklib_exp_set(expdata); \
        } \
        \
        MOCKLIB_FUN_CNT_IMPL(file, fun); \
        \
        void fun(arg1_type arg1, arg2_type arg2) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_STRUCT_PARAMS(file, fun).call_cnt++; \
            \
            switch (MOCKLIB_STRUCT_PARAMS(file, fun).mode) \
            {\
            case MOCKLIB_MODE_BASIC:\
                break;\
            case MOCKLIB_MODE_TRACE:\
                expdata = mocklib_exp_get();\
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun));\
                internal = mocklib_common_internal_get_and_check(expdata);\
                UTLIB_ASSERT_EQUAL(internal->arg1, arg1);\
                UTLIB_ASSERT_EQUAL(internal->arg2, arg2);\
                break;\
            case MOCKLIB_MODE_CALLBACK:\
                MOCKLIB_STRUCT_PARAMS(file, fun).cb(arg1, arg2);\
                break;\
            default:\
                break;\
            }\
        }

/** Mock interface declaration for mocked function with no return value and 3 arguments. */
#define MOCKLIB_MOCK_HEADER_NORET_ARGS3(file, fun, arg1_type, arg2_type, arg3_type) \
        typedef void (*MOCKLIB_CB(file, fun))(arg1_type arg1, arg2_type arg2, arg3_type arg3); \
        void MOCKLIB_FUN_MODE_SET(file, fun)(mocklib_mode_t mode); \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(void); \
        void MOCKLIB_FUN_CB_CFG(file, fun)(MOCKLIB_CB(file, fun) cb); \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(arg1_type arg1, arg2_type arg2, arg3_type arg3); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

/** Mock implementation for mocked function with no return value and 3 arguments. */
#define MOCKLIB_MOCK_NORET_ARGS3(file, fun, arg1_type, arg2_type, arg3_type) \
        MOCKLIB_PARAMS_NORET(file, fun); \
        struct MOCKLIB_STRUCT_INTERNAL(file, fun) \
        { \
            arg1_type arg1; \
            arg2_type arg2; \
            arg3_type arg3; \
        }; \
        static struct MOCKLIB_STRUCT_PARAMS(file, fun) \
        MOCKLIB_STRUCT_PARAMS(file, fun); \
        \
        MOCKLIB_FUN_MODE_SET_IMPL(file, fun)\
        \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(void) \
        {\
        }\
        \
        MOCKLIB_FUN_CB_CFG_IMPL(file, fun) \
        \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(arg1_type arg1, arg2_type arg2, arg3_type arg3) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_FUN_TRACE_EXPECT_COMMON(file, fun); \
            internal = mocklib_common_internal_create_and_check(sizeof(struct MOCKLIB_STRUCT_INTERNAL(file, fun))); \
            internal->arg1 = arg1; \
            internal->arg2 = arg2; \
            internal->arg3 = arg3; \
            mocklib_expdata_internal_set(expdata, internal); \
            mocklib_exp_set(expdata); \
        } \
        \
        MOCKLIB_FUN_CNT_IMPL(file, fun); \
        \
        void fun(arg1_type arg1, arg2_type arg2, arg3_type arg3) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_STRUCT_PARAMS(file, fun).call_cnt++; \
            \
            switch (MOCKLIB_STRUCT_PARAMS(file, fun).mode) \
            {\
            case MOCKLIB_MODE_BASIC:\
                break;\
            case MOCKLIB_MODE_TRACE:\
                expdata = mocklib_exp_get();\
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun));\
                internal = mocklib_common_internal_get_and_check(expdata);\
                UTLIB_ASSERT_EQUAL(internal->arg1, arg1);\
                UTLIB_ASSERT_EQUAL(internal->arg2, arg2);\
                UTLIB_ASSERT_EQUAL(internal->arg3, arg3);\
                break;\
            case MOCKLIB_MODE_CALLBACK:\
                MOCKLIB_STRUCT_PARAMS(file, fun).cb(arg1, arg2, arg3);\
                break;\
            default:\
                break;\
            }\
        }

/** Mock interface declaration for mocked function with no return value and 4 arguments. */
#define MOCKLIB_MOCK_HEADER_NORET_ARGS4(file, fun, arg1_type, arg2_type, arg3_type, arg4_type) \
        typedef void (*MOCKLIB_CB(file, fun))(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4); \
        void MOCKLIB_FUN_MODE_SET(file, fun)(mocklib_mode_t mode); \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(void); \
        void MOCKLIB_FUN_CB_CFG(file, fun)(MOCKLIB_CB(file, fun) cb); \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

/** Mock implementation for mocked function with no return value and 4 arguments. */
#define MOCKLIB_MOCK_NORET_ARGS4(file, fun, arg1_type, arg2_type, arg3_type, arg4_type) \
        MOCKLIB_PARAMS_NORET(file, fun); \
        struct MOCKLIB_STRUCT_INTERNAL(file, fun) \
        { \
            arg1_type arg1; \
            arg2_type arg2; \
            arg3_type arg3; \
            arg4_type arg4; \
        }; \
        static struct MOCKLIB_STRUCT_PARAMS(file, fun) \
        MOCKLIB_STRUCT_PARAMS(file, fun); \
        \
        MOCKLIB_FUN_MODE_SET_IMPL(file, fun)\
        \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(void) \
        {\
        }\
        \
        MOCKLIB_FUN_CB_CFG_IMPL(file, fun) \
        \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_FUN_TRACE_EXPECT_COMMON(file, fun); \
            internal = mocklib_common_internal_create_and_check(sizeof(struct MOCKLIB_STRUCT_INTERNAL(file, fun))); \
            internal->arg1 = arg1; \
            internal->arg2 = arg2; \
            internal->arg3 = arg3; \
            internal->arg4 = arg4; \
            mocklib_expdata_internal_set(expdata, internal); \
            mocklib_exp_set(expdata); \
        } \
        \
        MOCKLIB_FUN_CNT_IMPL(file, fun); \
        \
        void fun(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_STRUCT_PARAMS(file, fun).call_cnt++; \
            \
            switch (MOCKLIB_STRUCT_PARAMS(file, fun).mode) \
            {\
            case MOCKLIB_MODE_BASIC:\
                break;\
            case MOCKLIB_MODE_TRACE:\
                expdata = mocklib_exp_get();\
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun));\
                internal = mocklib_common_internal_get_and_check(expdata);\
                UTLIB_ASSERT_EQUAL(internal->arg1, arg1);\
                UTLIB_ASSERT_EQUAL(internal->arg2, arg2);\
                UTLIB_ASSERT_EQUAL(internal->arg3, arg3);\
                UTLIB_ASSERT_EQUAL(internal->arg4, arg4);\
                break;\
            case MOCKLIB_MODE_CALLBACK:\
                MOCKLIB_STRUCT_PARAMS(file, fun).cb(arg1, arg2, arg3, arg4);\
                break;\
            default:\
                break;\
            }\
        }

/** Mock interface declaration for mocked function with no return value and 5 arguments. */
#define MOCKLIB_MOCK_HEADER_NORET_ARGS5(file, fun, arg1_type, arg2_type, arg3_type, arg4_type, \
        arg5_type) \
        typedef void (*MOCKLIB_CB(file, fun))(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5); \
        void MOCKLIB_FUN_MODE_SET(file, fun)(mocklib_mode_t mode); \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(void); \
        void MOCKLIB_FUN_CB_CFG(file, fun)(MOCKLIB_CB(file, fun) cb); \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

/** Mock implementation for mocked function with no return value and 5 arguments. */
#define MOCKLIB_MOCK_NORET_ARGS5(file, fun, arg1_type, arg2_type, arg3_type, arg4_type, \
        arg5_type) \
        MOCKLIB_PARAMS_NORET(file, fun); \
        struct MOCKLIB_STRUCT_INTERNAL(file, fun) \
        { \
            arg1_type arg1; \
            arg2_type arg2; \
            arg3_type arg3; \
            arg4_type arg4; \
            arg5_type arg5; \
        }; \
        static struct MOCKLIB_STRUCT_PARAMS(file, fun) \
        MOCKLIB_STRUCT_PARAMS(file, fun); \
        \
        MOCKLIB_FUN_MODE_SET_IMPL(file, fun)\
        \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(void) \
        {\
        }\
        \
        MOCKLIB_FUN_CB_CFG_IMPL(file, fun) \
        \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_FUN_TRACE_EXPECT_COMMON(file, fun); \
            internal = mocklib_common_internal_create_and_check(sizeof(struct MOCKLIB_STRUCT_INTERNAL(file, fun))); \
            internal->arg1 = arg1; \
            internal->arg2 = arg2; \
            internal->arg3 = arg3; \
            internal->arg4 = arg4; \
            internal->arg5 = arg5; \
            mocklib_expdata_internal_set(expdata, internal); \
            mocklib_exp_set(expdata); \
        } \
        \
        MOCKLIB_FUN_CNT_IMPL(file, fun); \
        \
        void fun(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_STRUCT_PARAMS(file, fun).call_cnt++; \
            \
            switch (MOCKLIB_STRUCT_PARAMS(file, fun).mode) \
            {\
            case MOCKLIB_MODE_BASIC:\
                break;\
            case MOCKLIB_MODE_TRACE:\
                expdata = mocklib_exp_get();\
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun));\
                internal = mocklib_common_internal_get_and_check(expdata);\
                UTLIB_ASSERT_EQUAL(internal->arg1, arg1);\
                UTLIB_ASSERT_EQUAL(internal->arg2, arg2);\
                UTLIB_ASSERT_EQUAL(internal->arg3, arg3);\
                UTLIB_ASSERT_EQUAL(internal->arg4, arg4);\
                UTLIB_ASSERT_EQUAL(internal->arg5, arg5);\
                break;\
            case MOCKLIB_MODE_CALLBACK:\
                MOCKLIB_STRUCT_PARAMS(file, fun).cb(arg1, arg2, arg3, arg4, arg5);\
                break;\
            default:\
                break;\
            }\
        }

/** Mock interface declaration for mocked function with no return value and 6 arguments. */
#define MOCKLIB_MOCK_HEADER_NORET_ARGS6(file, fun, arg1_type, arg2_type, arg3_type, arg4_type, \
        arg5_type, arg6_type) \
        typedef void (*MOCKLIB_CB(file, fun))(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5, arg6_type arg6); \
        void MOCKLIB_FUN_MODE_SET(file, fun)(mocklib_mode_t mode); \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(void); \
        void MOCKLIB_FUN_CB_CFG(file, fun)(MOCKLIB_CB(file, fun) cb); \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5, arg6_type arg6); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

/** Mock implementation for mocked function with no return value and 6 arguments. */
#define MOCKLIB_MOCK_NORET_ARGS6(file, fun, arg1_type, arg2_type, arg3_type, arg4_type, \
        arg5_type, arg6_type) \
        MOCKLIB_PARAMS_NORET(file, fun); \
        struct MOCKLIB_STRUCT_INTERNAL(file, fun) \
        { \
            arg1_type arg1; \
            arg2_type arg2; \
            arg3_type arg3; \
            arg4_type arg4; \
            arg5_type arg5; \
            arg6_type arg6; \
        }; \
        static struct MOCKLIB_STRUCT_PARAMS(file, fun) \
        MOCKLIB_STRUCT_PARAMS(file, fun); \
        \
        MOCKLIB_FUN_MODE_SET_IMPL(file, fun)\
        \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(void) \
        {\
        }\
        \
        MOCKLIB_FUN_CB_CFG_IMPL(file, fun) \
        \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5, arg6_type arg6) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_FUN_TRACE_EXPECT_COMMON(file, fun); \
            internal = mocklib_common_internal_create_and_check(sizeof(struct MOCKLIB_STRUCT_INTERNAL(file, fun))); \
            internal->arg1 = arg1; \
            internal->arg2 = arg2; \
            internal->arg3 = arg3; \
            internal->arg4 = arg4; \
            internal->arg5 = arg5; \
            internal->arg6 = arg6; \
            mocklib_expdata_internal_set(expdata, internal); \
            mocklib_exp_set(expdata); \
        } \
        \
        MOCKLIB_FUN_CNT_IMPL(file, fun); \
        \
        void fun(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5, arg6_type arg6) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_STRUCT_PARAMS(file, fun).call_cnt++; \
            \
            switch (MOCKLIB_STRUCT_PARAMS(file, fun).mode) \
            {\
            case MOCKLIB_MODE_BASIC:\
                break;\
            case MOCKLIB_MODE_TRACE:\
                expdata = mocklib_exp_get();\
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun));\
                internal = mocklib_common_internal_get_and_check(expdata);\
                UTLIB_ASSERT_EQUAL(internal->arg1, arg1);\
                UTLIB_ASSERT_EQUAL(internal->arg2, arg2);\
                UTLIB_ASSERT_EQUAL(internal->arg3, arg3);\
                UTLIB_ASSERT_EQUAL(internal->arg4, arg4);\
                UTLIB_ASSERT_EQUAL(internal->arg5, arg5);\
                UTLIB_ASSERT_EQUAL(internal->arg6, arg6);\
                break;\
            case MOCKLIB_MODE_CALLBACK:\
                MOCKLIB_STRUCT_PARAMS(file, fun).cb(arg1, arg2, arg3, arg4, arg5, arg6);\
                break;\
            default:\
                break;\
            }\
        }

/** Mock interface declaration for mocked function with no return value and 7 arguments. */
#define MOCKLIB_MOCK_HEADER_NORET_ARGS7(file, fun, arg1_type, arg2_type, arg3_type, arg4_type, \
        arg5_type, arg6_type, arg7_type) \
        typedef void (*MOCKLIB_CB(file, fun))(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5, arg6_type arg6, arg7_type arg7); \
        void MOCKLIB_FUN_MODE_SET(file, fun)(mocklib_mode_t mode); \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(void); \
        void MOCKLIB_FUN_CB_CFG(file, fun)(MOCKLIB_CB(file, fun) cb); \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5, arg6_type arg6, arg7_type arg7); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

/** Mock implementation for mocked function with no return value and 7 arguments. */
#define MOCKLIB_MOCK_NORET_ARGS7(file, fun, arg1_type, arg2_type, arg3_type, arg4_type, \
        arg5_type, arg6_type, arg7_type) \
        MOCKLIB_PARAMS_NORET(file, fun); \
        struct MOCKLIB_STRUCT_INTERNAL(file, fun) \
        { \
            arg1_type arg1; \
            arg2_type arg2; \
            arg3_type arg3; \
            arg4_type arg4; \
            arg5_type arg5; \
            arg6_type arg6; \
            arg7_type arg7; \
        }; \
        static struct MOCKLIB_STRUCT_PARAMS(file, fun) \
        MOCKLIB_STRUCT_PARAMS(file, fun); \
        \
        MOCKLIB_FUN_MODE_SET_IMPL(file, fun)\
        \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(void) \
        {\
        }\
        \
        MOCKLIB_FUN_CB_CFG_IMPL(file, fun) \
        \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5, arg6_type arg6, arg7_type arg7) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_FUN_TRACE_EXPECT_COMMON(file, fun); \
            internal = mocklib_common_internal_create_and_check(sizeof(struct MOCKLIB_STRUCT_INTERNAL(file, fun))); \
            internal->arg1 = arg1; \
            internal->arg2 = arg2; \
            internal->arg3 = arg3; \
            internal->arg4 = arg4; \
            internal->arg5 = arg5; \
            internal->arg6 = arg6; \
            internal->arg7 = arg7; \
            mocklib_expdata_internal_set(expdata, internal); \
            mocklib_exp_set(expdata); \
        } \
        \
        MOCKLIB_FUN_CNT_IMPL(file, fun); \
        \
        void fun(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5, arg6_type arg6, arg7_type arg7) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_STRUCT_PARAMS(file, fun).call_cnt++; \
            \
            switch (MOCKLIB_STRUCT_PARAMS(file, fun).mode) \
            {\
            case MOCKLIB_MODE_BASIC:\
                break;\
            case MOCKLIB_MODE_TRACE:\
                expdata = mocklib_exp_get();\
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun));\
                internal = mocklib_common_internal_get_and_check(expdata);\
                UTLIB_ASSERT_EQUAL(internal->arg1, arg1);\
                UTLIB_ASSERT_EQUAL(internal->arg2, arg2);\
                UTLIB_ASSERT_EQUAL(internal->arg3, arg3);\
                UTLIB_ASSERT_EQUAL(internal->arg4, arg4);\
                UTLIB_ASSERT_EQUAL(internal->arg5, arg5);\
                UTLIB_ASSERT_EQUAL(internal->arg6, arg6);\
                UTLIB_ASSERT_EQUAL(internal->arg7, arg7);\
                break;\
            case MOCKLIB_MODE_CALLBACK:\
                MOCKLIB_STRUCT_PARAMS(file, fun).cb(arg1, arg2, arg3, arg4, arg5, arg6, arg7);\
                break;\
            default:\
                break;\
            }\
        }

/** Mock interface declaration for mocked function with no return value and 8 arguments. */
#define MOCKLIB_MOCK_HEADER_NORET_ARGS8(file, fun, arg1_type, arg2_type, arg3_type, arg4_type, \
        arg5_type, arg6_type, arg7_type, arg8_type) \
        typedef void (*MOCKLIB_CB(file, fun))(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5, arg6_type arg6, arg7_type arg7, arg8_type arg8); \
        void MOCKLIB_FUN_MODE_SET(file, fun)(mocklib_mode_t mode); \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(void); \
        void MOCKLIB_FUN_CB_CFG(file, fun)(MOCKLIB_CB(file, fun) cb); \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5, arg6_type arg6, arg7_type arg7, arg8_type arg8); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

/** Mock implementation for mocked function with no return value and 8 arguments. */
#define MOCKLIB_MOCK_NORET_ARGS8(file, fun, arg1_type, arg2_type, arg3_type, arg4_type, \
        arg5_type, arg6_type, arg7_type, arg8_type) \
        MOCKLIB_PARAMS_NORET(file, fun); \
        struct MOCKLIB_STRUCT_INTERNAL(file, fun) \
        { \
            arg1_type arg1; \
            arg2_type arg2; \
            arg3_type arg3; \
            arg4_type arg4; \
            arg5_type arg5; \
            arg6_type arg6; \
            arg7_type arg7; \
            arg8_type arg8; \
        }; \
        static struct MOCKLIB_STRUCT_PARAMS(file, fun) \
        MOCKLIB_STRUCT_PARAMS(file, fun); \
        \
        MOCKLIB_FUN_MODE_SET_IMPL(file, fun)\
        \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(void) \
        {\
        }\
        \
        MOCKLIB_FUN_CB_CFG_IMPL(file, fun) \
        \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5, arg6_type arg6, arg7_type arg7, arg8_type arg8) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_FUN_TRACE_EXPECT_COMMON(file, fun); \
            internal = mocklib_common_internal_create_and_check(sizeof(struct MOCKLIB_STRUCT_INTERNAL(file, fun))); \
            internal->arg1 = arg1; \
            internal->arg2 = arg2; \
            internal->arg3 = arg3; \
            internal->arg4 = arg4; \
            internal->arg5 = arg5; \
            internal->arg6 = arg6; \
            internal->arg7 = arg7; \
            internal->arg8 = arg8; \
            mocklib_expdata_internal_set(expdata, internal); \
            mocklib_exp_set(expdata); \
        } \
        \
        MOCKLIB_FUN_CNT_IMPL(file, fun); \
        \
        void fun(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5, arg6_type arg6, arg7_type arg7, arg8_type arg8) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_STRUCT_PARAMS(file, fun).call_cnt++; \
            \
            switch (MOCKLIB_STRUCT_PARAMS(file, fun).mode) \
            {\
            case MOCKLIB_MODE_BASIC:\
                break;\
            case MOCKLIB_MODE_TRACE:\
                expdata = mocklib_exp_get();\
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun));\
                internal = mocklib_common_internal_get_and_check(expdata);\
                UTLIB_ASSERT_EQUAL(internal->arg1, arg1);\
                UTLIB_ASSERT_EQUAL(internal->arg2, arg2);\
                UTLIB_ASSERT_EQUAL(internal->arg3, arg3);\
                UTLIB_ASSERT_EQUAL(internal->arg4, arg4);\
                UTLIB_ASSERT_EQUAL(internal->arg5, arg5);\
                UTLIB_ASSERT_EQUAL(internal->arg6, arg6);\
                UTLIB_ASSERT_EQUAL(internal->arg7, arg7);\
                UTLIB_ASSERT_EQUAL(internal->arg8, arg8);\
                break;\
            case MOCKLIB_MODE_CALLBACK:\
                MOCKLIB_STRUCT_PARAMS(file, fun).cb(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);\
                break;\
            default:\
                break;\
            }\
        }

/** Mock interface declaration for mocked function with return value and no arguments. */
#define MOCKLIB_MOCK_HEADER_RET_ARGS0(file, fun, ret_type) \
        typedef ret_type (*MOCKLIB_CB(file, fun))(void); \
        void MOCKLIB_FUN_MODE_SET(file, fun)(mocklib_mode_t mode); \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(ret_type ret); \
        void MOCKLIB_FUN_CB_CFG(file, fun)(MOCKLIB_CB(file, fun) cb); \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(ret_type ret); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

/** Mock implementation for mocked function with return value and no arguments. */
#define MOCKLIB_MOCK_RET_ARGS0(file, fun, ret_type) \
        MOCKLIB_PARAMS_RET(file, fun, ret_type); \
        struct MOCKLIB_STRUCT_INTERNAL(file, fun) \
        { \
            ret_type ret; \
        }; \
        static struct MOCKLIB_STRUCT_PARAMS(file, fun) \
            MOCKLIB_STRUCT_PARAMS(file, fun); \
        \
        MOCKLIB_FUN_MODE_SET_IMPL(file, fun)\
        \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(ret_type ret) \
        {\
            mocklib_common_err_if_mode_not_basic(MOCKLIB_STRUCT_PARAMS(file, fun).mode);\
            MOCKLIB_STRUCT_PARAMS(file, fun).ret = ret;\
        }\
        \
        MOCKLIB_FUN_CB_CFG_IMPL(file, fun) \
        \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(ret_type ret) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_FUN_TRACE_EXPECT_COMMON(file, fun); \
            internal = mocklib_common_internal_create_and_check(sizeof(struct MOCKLIB_STRUCT_INTERNAL(file, fun))); \
            internal->ret = ret; \
            mocklib_expdata_internal_set(expdata, internal); \
            mocklib_exp_set(expdata); \
        } \
        \
        MOCKLIB_FUN_CNT_IMPL(file, fun); \
        \
        ret_type fun(void) \
        { \
            ret_type retval; \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_STRUCT_PARAMS(file, fun).call_cnt++; \
            \
            switch (MOCKLIB_STRUCT_PARAMS(file, fun).mode)\
            {\
            case MOCKLIB_MODE_BASIC:\
                retval = MOCKLIB_STRUCT_PARAMS(file, fun).ret;\
                break;\
            case MOCKLIB_MODE_TRACE:\
                expdata = mocklib_exp_get();\
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun));\
                internal = mocklib_common_internal_get_and_check(expdata);\
                retval = internal->ret;\
                break;\
            case MOCKLIB_MODE_CALLBACK:\
                retval = MOCKLIB_STRUCT_PARAMS(file, fun).cb();\
                break;\
            default:\
                break;\
            }\
            return retval;\
        }

/** Mock interface declaration for mocked function with return value and 1 argument. */
#define MOCKLIB_MOCK_HEADER_RET_ARGS1(file, fun, ret_type, arg1_type) \
        typedef ret_type (*MOCKLIB_CB(file, fun))(arg1_type arg1); \
        void MOCKLIB_FUN_MODE_SET(file, fun)(mocklib_mode_t mode); \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(ret_type ret); \
        void MOCKLIB_FUN_CB_CFG(file, fun)(MOCKLIB_CB(file, fun) cb); \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(ret_type ret, arg1_type arg1); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

/** Mock implementation for mocked function with return value and 1 argument. */
#define MOCKLIB_MOCK_RET_ARGS1(file, fun, ret_type, arg1_type) \
        MOCKLIB_PARAMS_RET(file, fun, ret_type); \
        struct MOCKLIB_STRUCT_INTERNAL(file, fun) \
        { \
            arg1_type arg1; \
            ret_type ret; \
        }; \
        static struct MOCKLIB_STRUCT_PARAMS(file, fun) \
        MOCKLIB_STRUCT_PARAMS(file, fun); \
        \
        MOCKLIB_FUN_MODE_SET_IMPL(file, fun)\
        \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(ret_type ret) \
        {\
            mocklib_common_err_if_mode_not_basic(MOCKLIB_STRUCT_PARAMS(file, fun).mode);\
            MOCKLIB_STRUCT_PARAMS(file, fun).ret = ret;\
        }\
        \
        MOCKLIB_FUN_CB_CFG_IMPL(file, fun) \
        \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(ret_type ret, arg1_type arg1) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_FUN_TRACE_EXPECT_COMMON(file, fun); \
            internal = mocklib_common_internal_create_and_check(sizeof(struct MOCKLIB_STRUCT_INTERNAL(file, fun))); \
            internal->arg1 = arg1; \
            internal->ret = ret; \
            mocklib_expdata_internal_set(expdata, internal); \
            mocklib_exp_set(expdata); \
        } \
        \
        MOCKLIB_FUN_CNT_IMPL(file, fun); \
        \
        ret_type fun(arg1_type arg1) \
        { \
            ret_type retval; \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_STRUCT_PARAMS(file, fun).call_cnt++; \
            \
            switch (MOCKLIB_STRUCT_PARAMS(file, fun).mode)\
            {\
            case MOCKLIB_MODE_BASIC:\
                retval = MOCKLIB_STRUCT_PARAMS(file, fun).ret;\
                break;\
            case MOCKLIB_MODE_TRACE:\
                expdata = mocklib_exp_get();\
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun));\
                internal = mocklib_common_internal_get_and_check(expdata);\
                UTLIB_ASSERT_EQUAL(internal->arg1, arg1);\
                retval = internal->ret;\
                break;\
            case MOCKLIB_MODE_CALLBACK:\
                retval = MOCKLIB_STRUCT_PARAMS(file, fun).cb(arg1);\
                break;\
            default:\
                break;\
            }\
            return retval;\
        }

/** Mock interface declaration for mocked function with return value and 2 arguments. */
#define MOCKLIB_MOCK_HEADER_RET_ARGS2(file, fun, ret_type, arg1_type, arg2_type) \
        typedef ret_type (*MOCKLIB_CB(file, fun))(arg1_type arg1, arg2_type arg2); \
        void MOCKLIB_FUN_MODE_SET(file, fun)(mocklib_mode_t mode); \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(ret_type ret); \
        void MOCKLIB_FUN_CB_CFG(file, fun)(MOCKLIB_CB(file, fun) cb); \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(ret_type ret, arg1_type arg1, arg2_type arg2); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

/** Mock implementation for mocked function with return value and 2 arguments. */
#define MOCKLIB_MOCK_RET_ARGS2(file, fun, ret_type, arg1_type, arg2_type) \
        MOCKLIB_PARAMS_RET(file, fun, ret_type); \
        struct MOCKLIB_STRUCT_INTERNAL(file, fun) \
        { \
            arg1_type arg1; \
            arg2_type arg2; \
            ret_type ret; \
        }; \
        static struct MOCKLIB_STRUCT_PARAMS(file, fun) \
            MOCKLIB_STRUCT_PARAMS(file, fun); \
        \
        MOCKLIB_FUN_MODE_SET_IMPL(file, fun)\
        \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(ret_type ret) \
        {\
            mocklib_common_err_if_mode_not_basic(MOCKLIB_STRUCT_PARAMS(file, fun).mode);\
            MOCKLIB_STRUCT_PARAMS(file, fun).ret = ret;\
        }\
        \
        MOCKLIB_FUN_CB_CFG_IMPL(file, fun) \
        \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(ret_type ret, arg1_type arg1, arg2_type arg2) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_FUN_TRACE_EXPECT_COMMON(file, fun); \
            internal = mocklib_common_internal_create_and_check(sizeof(struct MOCKLIB_STRUCT_INTERNAL(file, fun))); \
            internal->arg1 = arg1; \
            internal->arg2 = arg2; \
            internal->ret = ret; \
            mocklib_expdata_internal_set(expdata, internal); \
            mocklib_exp_set(expdata); \
        } \
        \
        MOCKLIB_FUN_CNT_IMPL(file, fun); \
        \
        ret_type fun(arg1_type arg1, arg2_type arg2) \
        { \
            ret_type retval; \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_STRUCT_PARAMS(file, fun).call_cnt++; \
            \
            switch (MOCKLIB_STRUCT_PARAMS(file, fun).mode)\
            {\
            case MOCKLIB_MODE_BASIC:\
                retval = MOCKLIB_STRUCT_PARAMS(file, fun).ret;\
                break;\
            case MOCKLIB_MODE_TRACE:\
                expdata = mocklib_exp_get();\
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun));\
                internal = mocklib_common_internal_get_and_check(expdata);\
                UTLIB_ASSERT_EQUAL(internal->arg1, arg1);\
                UTLIB_ASSERT_EQUAL(internal->arg2, arg2);\
                retval = internal->ret;\
                break;\
            case MOCKLIB_MODE_CALLBACK:\
                retval = MOCKLIB_STRUCT_PARAMS(file, fun).cb(arg1, arg2);\
                break;\
            default:\
                break;\
            }\
            return retval;\
        }

/** Mock interface declaration for mocked function with return value and 3 arguments. */
#define MOCKLIB_MOCK_HEADER_RET_ARGS3(file, fun, ret_type, arg1_type, arg2_type, arg3_type) \
        typedef ret_type (*MOCKLIB_CB(file, fun))(arg1_type arg1, arg2_type arg2, arg3_type arg3); \
        void MOCKLIB_FUN_MODE_SET(file, fun)(mocklib_mode_t mode); \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(ret_type ret); \
        void MOCKLIB_FUN_CB_CFG(file, fun)(MOCKLIB_CB(file, fun) cb); \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(ret_type ret, arg1_type arg1, arg2_type arg2, arg3_type arg3); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

/** Mock implementation for mocked function with return value and 3 arguments. */
#define MOCKLIB_MOCK_RET_ARGS3(file, fun, ret_type, arg1_type, arg2_type, arg3_type) \
        MOCKLIB_PARAMS_RET(file, fun, ret_type); \
        struct MOCKLIB_STRUCT_INTERNAL(file, fun) \
        { \
            arg1_type arg1; \
            arg2_type arg2; \
            arg3_type arg3; \
            ret_type ret; \
        }; \
        static struct MOCKLIB_STRUCT_PARAMS(file, fun) \
            MOCKLIB_STRUCT_PARAMS(file, fun); \
        \
        MOCKLIB_FUN_MODE_SET_IMPL(file, fun)\
        \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(ret_type ret) \
        {\
            mocklib_common_err_if_mode_not_basic(MOCKLIB_STRUCT_PARAMS(file, fun).mode);\
            MOCKLIB_STRUCT_PARAMS(file, fun).ret = ret;\
        }\
        \
        MOCKLIB_FUN_CB_CFG_IMPL(file, fun) \
        \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(ret_type ret, arg1_type arg1, arg2_type arg2, arg3_type arg3) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_FUN_TRACE_EXPECT_COMMON(file, fun); \
            internal = mocklib_common_internal_create_and_check(sizeof(struct MOCKLIB_STRUCT_INTERNAL(file, fun))); \
            internal->arg1 = arg1; \
            internal->arg2 = arg2; \
            internal->arg3 = arg3; \
            internal->ret = ret; \
            mocklib_expdata_internal_set(expdata, internal); \
            mocklib_exp_set(expdata); \
        } \
        \
        MOCKLIB_FUN_CNT_IMPL(file, fun); \
        \
        ret_type fun(arg1_type arg1, arg2_type arg2, arg3_type arg3) \
        { \
            ret_type retval; \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_STRUCT_PARAMS(file, fun).call_cnt++; \
            \
            switch (MOCKLIB_STRUCT_PARAMS(file, fun).mode)\
            {\
            case MOCKLIB_MODE_BASIC:\
                retval = MOCKLIB_STRUCT_PARAMS(file, fun).ret;\
                break;\
            case MOCKLIB_MODE_TRACE:\
                expdata = mocklib_exp_get();\
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun));\
                internal = mocklib_common_internal_get_and_check(expdata);\
                UTLIB_ASSERT_EQUAL(internal->arg1, arg1);\
                UTLIB_ASSERT_EQUAL(internal->arg2, arg2);\
                UTLIB_ASSERT_EQUAL(internal->arg3, arg3);\
                retval = internal->ret;\
                break;\
            case MOCKLIB_MODE_CALLBACK:\
                retval = MOCKLIB_STRUCT_PARAMS(file, fun).cb(arg1, arg2, arg3);\
                break;\
            default:\
                break;\
            }\
            return retval;\
        }

/** Mock interface declaration for mocked function with return value and 4 arguments. */
#define MOCKLIB_MOCK_HEADER_RET_ARGS4(file, fun, ret_type, arg1_type, arg2_type, arg3_type, arg4_type) \
        typedef ret_type (*MOCKLIB_CB(file, fun))(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4); \
        void MOCKLIB_FUN_MODE_SET(file, fun)(mocklib_mode_t mode); \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(ret_type ret); \
        void MOCKLIB_FUN_CB_CFG(file, fun)(MOCKLIB_CB(file, fun) cb); \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(ret_type ret, arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

/** Mock implementation for mocked function with return value and 4 arguments. */
#define MOCKLIB_MOCK_RET_ARGS4(file, fun, ret_type, arg1_type, arg2_type, arg3_type, arg4_type) \
        MOCKLIB_PARAMS_RET(file, fun, ret_type); \
        struct MOCKLIB_STRUCT_INTERNAL(file, fun) \
        { \
            arg1_type arg1; \
            arg2_type arg2; \
            arg3_type arg3; \
            arg4_type arg4; \
            ret_type ret; \
        }; \
        static struct MOCKLIB_STRUCT_PARAMS(file, fun) \
            MOCKLIB_STRUCT_PARAMS(file, fun); \
        \
        MOCKLIB_FUN_MODE_SET_IMPL(file, fun)\
        \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(ret_type ret) \
        {\
            mocklib_common_err_if_mode_not_basic(MOCKLIB_STRUCT_PARAMS(file, fun).mode);\
            MOCKLIB_STRUCT_PARAMS(file, fun).ret = ret;\
        }\
        \
        MOCKLIB_FUN_CB_CFG_IMPL(file, fun) \
        \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(ret_type ret, arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_FUN_TRACE_EXPECT_COMMON(file, fun); \
            internal = mocklib_common_internal_create_and_check(sizeof(struct MOCKLIB_STRUCT_INTERNAL(file, fun))); \
            internal->arg1 = arg1; \
            internal->arg2 = arg2; \
            internal->arg3 = arg3; \
            internal->arg4 = arg4; \
            internal->ret = ret; \
            mocklib_expdata_internal_set(expdata, internal); \
            mocklib_exp_set(expdata); \
        } \
        \
        MOCKLIB_FUN_CNT_IMPL(file, fun); \
        \
        ret_type fun(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4) \
        { \
            ret_type retval; \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_STRUCT_PARAMS(file, fun).call_cnt++; \
            \
            switch (MOCKLIB_STRUCT_PARAMS(file, fun).mode)\
            {\
            case MOCKLIB_MODE_BASIC:\
                retval = MOCKLIB_STRUCT_PARAMS(file, fun).ret;\
                break;\
            case MOCKLIB_MODE_TRACE:\
                expdata = mocklib_exp_get();\
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun));\
                internal = mocklib_common_internal_get_and_check(expdata);\
                UTLIB_ASSERT_EQUAL(internal->arg1, arg1);\
                UTLIB_ASSERT_EQUAL(internal->arg2, arg2);\
                UTLIB_ASSERT_EQUAL(internal->arg3, arg3);\
                UTLIB_ASSERT_EQUAL(internal->arg4, arg4);\
                retval = internal->ret;\
                break;\
            case MOCKLIB_MODE_CALLBACK:\
                retval = MOCKLIB_STRUCT_PARAMS(file, fun).cb(arg1, arg2, arg3, arg4);\
                break;\
            default:\
                break;\
            }\
            return retval;\
        }

/** Mock interface declaration for mocked function with return value and 5 arguments. */
#define MOCKLIB_MOCK_HEADER_RET_ARGS5(file, fun, ret_type, arg1_type, arg2_type, arg3_type, arg4_type, \
        arg5_type) \
        typedef ret_type (*MOCKLIB_CB(file, fun))(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5); \
        void MOCKLIB_FUN_MODE_SET(file, fun)(mocklib_mode_t mode); \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(ret_type ret); \
        void MOCKLIB_FUN_CB_CFG(file, fun)(MOCKLIB_CB(file, fun) cb); \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(ret_type ret, arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

/** Mock implementation for mocked function with return value and 5 arguments. */
#define MOCKLIB_MOCK_RET_ARGS5(file, fun, ret_type, arg1_type, arg2_type, arg3_type, arg4_type, \
        arg5_type) \
        MOCKLIB_PARAMS_RET(file, fun, ret_type); \
        struct MOCKLIB_STRUCT_INTERNAL(file, fun) \
        { \
            arg1_type arg1; \
            arg2_type arg2; \
            arg3_type arg3; \
            arg4_type arg4; \
            arg5_type arg5; \
            ret_type ret; \
        }; \
        static struct MOCKLIB_STRUCT_PARAMS(file, fun) \
            MOCKLIB_STRUCT_PARAMS(file, fun); \
        \
        MOCKLIB_FUN_MODE_SET_IMPL(file, fun)\
        \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(ret_type ret) \
        {\
            mocklib_common_err_if_mode_not_basic(MOCKLIB_STRUCT_PARAMS(file, fun).mode);\
            MOCKLIB_STRUCT_PARAMS(file, fun).ret = ret;\
        }\
        \
        MOCKLIB_FUN_CB_CFG_IMPL(file, fun) \
        \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(ret_type ret, arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_FUN_TRACE_EXPECT_COMMON(file, fun); \
            internal = mocklib_common_internal_create_and_check(sizeof(struct MOCKLIB_STRUCT_INTERNAL(file, fun))); \
            internal->arg1 = arg1; \
            internal->arg2 = arg2; \
            internal->arg3 = arg3; \
            internal->arg4 = arg4; \
            internal->arg5 = arg5; \
            internal->ret = ret; \
            mocklib_expdata_internal_set(expdata, internal); \
            mocklib_exp_set(expdata); \
        } \
        \
        MOCKLIB_FUN_CNT_IMPL(file, fun); \
        \
        ret_type fun(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5) \
        { \
            ret_type retval; \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_STRUCT_PARAMS(file, fun).call_cnt++; \
            \
            switch (MOCKLIB_STRUCT_PARAMS(file, fun).mode)\
            {\
            case MOCKLIB_MODE_BASIC:\
                retval = MOCKLIB_STRUCT_PARAMS(file, fun).ret;\
                break;\
            case MOCKLIB_MODE_TRACE:\
                expdata = mocklib_exp_get();\
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun));\
                internal = mocklib_common_internal_get_and_check(expdata);\
                UTLIB_ASSERT_EQUAL(internal->arg1, arg1);\
                UTLIB_ASSERT_EQUAL(internal->arg2, arg2);\
                UTLIB_ASSERT_EQUAL(internal->arg3, arg3);\
                UTLIB_ASSERT_EQUAL(internal->arg4, arg4);\
                UTLIB_ASSERT_EQUAL(internal->arg5, arg5);\
                retval = internal->ret;\
                break;\
            case MOCKLIB_MODE_CALLBACK:\
                retval = MOCKLIB_STRUCT_PARAMS(file, fun).cb(arg1, arg2, arg3, arg4, arg5);\
                break;\
            default:\
                break;\
            }\
            return retval; \
        }

/** Mock interface declaration for mocked function with return value and 6 arguments. */
#define MOCKLIB_MOCK_HEADER_RET_ARGS6(file, fun, ret_type, arg1_type, arg2_type, arg3_type, arg4_type, \
        arg5_type, arg6_type) \
        typedef ret_type (*MOCKLIB_CB(file, fun))(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5, arg6_type arg6); \
        void MOCKLIB_FUN_MODE_SET(file, fun)(mocklib_mode_t mode); \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(ret_type ret); \
        void MOCKLIB_FUN_CB_CFG(file, fun)(MOCKLIB_CB(file, fun) cb); \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(ret_type ret, arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5, arg6_type arg6); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

/** Mock implementation for mocked function with return value and 6 arguments. */
#define MOCKLIB_MOCK_RET_ARGS6(file, fun, ret_type, arg1_type, arg2_type, arg3_type, arg4_type, \
        arg5_type, arg6_type) \
        MOCKLIB_PARAMS_RET(file, fun, ret_type); \
        struct MOCKLIB_STRUCT_INTERNAL(file, fun) \
        { \
            arg1_type arg1; \
            arg2_type arg2; \
            arg3_type arg3; \
            arg4_type arg4; \
            arg5_type arg5; \
            arg6_type arg6; \
            ret_type ret; \
        }; \
        static struct MOCKLIB_STRUCT_PARAMS(file, fun) \
            MOCKLIB_STRUCT_PARAMS(file, fun); \
        \
        MOCKLIB_FUN_MODE_SET_IMPL(file, fun)\
        \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(ret_type ret) \
        {\
            mocklib_common_err_if_mode_not_basic(MOCKLIB_STRUCT_PARAMS(file, fun).mode);\
            MOCKLIB_STRUCT_PARAMS(file, fun).ret = ret;\
        }\
        \
        MOCKLIB_FUN_CB_CFG_IMPL(file, fun) \
        \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(ret_type ret, arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5, arg6_type arg6) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_FUN_TRACE_EXPECT_COMMON(file, fun); \
            internal = mocklib_common_internal_create_and_check(sizeof(struct MOCKLIB_STRUCT_INTERNAL(file, fun))); \
            internal->arg1 = arg1; \
            internal->arg2 = arg2; \
            internal->arg3 = arg3; \
            internal->arg4 = arg4; \
            internal->arg5 = arg5; \
            internal->arg6 = arg6; \
            internal->ret = ret; \
            mocklib_expdata_internal_set(expdata, internal); \
            mocklib_exp_set(expdata); \
        } \
        \
        MOCKLIB_FUN_CNT_IMPL(file, fun); \
        \
        ret_type fun(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5, arg6_type arg6) \
        { \
            ret_type retval; \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_STRUCT_PARAMS(file, fun).call_cnt++; \
            \
            switch (MOCKLIB_STRUCT_PARAMS(file, fun).mode)\
            {\
            case MOCKLIB_MODE_BASIC:\
                retval = MOCKLIB_STRUCT_PARAMS(file, fun).ret;\
                break;\
            case MOCKLIB_MODE_TRACE:\
                expdata = mocklib_exp_get();\
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun));\
                internal = mocklib_common_internal_get_and_check(expdata);\
                UTLIB_ASSERT_EQUAL(internal->arg1, arg1);\
                UTLIB_ASSERT_EQUAL(internal->arg2, arg2);\
                UTLIB_ASSERT_EQUAL(internal->arg3, arg3);\
                UTLIB_ASSERT_EQUAL(internal->arg4, arg4);\
                UTLIB_ASSERT_EQUAL(internal->arg5, arg5);\
                UTLIB_ASSERT_EQUAL(internal->arg6, arg6);\
                retval = internal->ret;\
                break;\
            case MOCKLIB_MODE_CALLBACK:\
                retval = MOCKLIB_STRUCT_PARAMS(file, fun).cb(arg1, arg2, arg3, arg4, arg5, arg6);\
                break;\
            default:\
                break;\
            }\
            return retval; \
        }

/** Mock interface declaration for mocked function with return value and 7 arguments. */
#define MOCKLIB_MOCK_HEADER_RET_ARGS7(file, fun, ret_type, arg1_type, arg2_type, arg3_type, arg4_type, \
        arg5_type, arg6_type, arg7_type) \
        typedef ret_type (*MOCKLIB_CB(file, fun))(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5, arg6_type arg6, arg7_type arg7); \
        void MOCKLIB_FUN_MODE_SET(file, fun)(mocklib_mode_t mode); \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(ret_type ret); \
        void MOCKLIB_FUN_CB_CFG(file, fun)(MOCKLIB_CB(file, fun) cb); \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(ret_type ret, arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5, arg6_type arg6, arg7_type arg7); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

/** Mock implementation for mocked function with return value and 7 arguments. */
#define MOCKLIB_MOCK_RET_ARGS7(file, fun, ret_type, arg1_type, arg2_type, arg3_type, arg4_type, \
        arg5_type, arg6_type, arg7_type) \
        MOCKLIB_PARAMS_RET(file, fun, ret_type); \
        struct MOCKLIB_STRUCT_INTERNAL(file, fun) \
        { \
            arg1_type arg1; \
            arg2_type arg2; \
            arg3_type arg3; \
            arg4_type arg4; \
            arg5_type arg5; \
            arg6_type arg6; \
            arg7_type arg7; \
            ret_type ret; \
        }; \
        static struct MOCKLIB_STRUCT_PARAMS(file, fun) \
            MOCKLIB_STRUCT_PARAMS(file, fun); \
        \
        MOCKLIB_FUN_MODE_SET_IMPL(file, fun)\
        \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(ret_type ret) \
        {\
            mocklib_common_err_if_mode_not_basic(MOCKLIB_STRUCT_PARAMS(file, fun).mode);\
            MOCKLIB_STRUCT_PARAMS(file, fun).ret = ret;\
        }\
        \
        MOCKLIB_FUN_CB_CFG_IMPL(file, fun) \
        \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(ret_type ret, arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5, arg6_type arg6, arg7_type arg7) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_FUN_TRACE_EXPECT_COMMON(file, fun); \
            internal = mocklib_common_internal_create_and_check(sizeof(struct MOCKLIB_STRUCT_INTERNAL(file, fun))); \
            internal->arg1 = arg1; \
            internal->arg2 = arg2; \
            internal->arg3 = arg3; \
            internal->arg4 = arg4; \
            internal->arg5 = arg5; \
            internal->arg6 = arg6; \
            internal->arg7 = arg7; \
            internal->ret = ret; \
            mocklib_expdata_internal_set(expdata, internal); \
            mocklib_exp_set(expdata); \
        } \
        \
        MOCKLIB_FUN_CNT_IMPL(file, fun); \
        \
        ret_type fun(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5, arg6_type arg6, arg7_type arg7) \
        { \
            ret_type retval; \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_STRUCT_PARAMS(file, fun).call_cnt++; \
            \
            switch (MOCKLIB_STRUCT_PARAMS(file, fun).mode)\
            {\
            case MOCKLIB_MODE_BASIC:\
                retval = MOCKLIB_STRUCT_PARAMS(file, fun).ret;\
                break;\
            case MOCKLIB_MODE_TRACE:\
                expdata = mocklib_exp_get();\
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun));\
                internal = mocklib_common_internal_get_and_check(expdata);\
                UTLIB_ASSERT_EQUAL(internal->arg1, arg1);\
                UTLIB_ASSERT_EQUAL(internal->arg2, arg2);\
                UTLIB_ASSERT_EQUAL(internal->arg3, arg3);\
                UTLIB_ASSERT_EQUAL(internal->arg4, arg4);\
                UTLIB_ASSERT_EQUAL(internal->arg5, arg5);\
                UTLIB_ASSERT_EQUAL(internal->arg6, arg6);\
                UTLIB_ASSERT_EQUAL(internal->arg7, arg7);\
                retval = internal->ret;\
                break;\
            case MOCKLIB_MODE_CALLBACK:\
                retval = MOCKLIB_STRUCT_PARAMS(file, fun).cb(arg1, arg2, arg3, arg4, arg5, arg6, arg7);\
                break;\
            default:\
                break;\
            }\
            return retval; \
        }

/** Mock interface declaration for mocked function with return value and 8 arguments. */
#define MOCKLIB_MOCK_HEADER_RET_ARGS8(file, fun, ret_type, arg1_type, arg2_type, arg3_type, arg4_type, \
        arg5_type, arg6_type, arg7_type, arg8_type) \
        typedef ret_type (*MOCKLIB_CB(file, fun))(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5, arg6_type arg6, arg7_type arg7, arg8_type arg8); \
        void MOCKLIB_FUN_MODE_SET(file, fun)(mocklib_mode_t mode); \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(ret_type ret); \
        void MOCKLIB_FUN_CB_CFG(file, fun)(MOCKLIB_CB(file, fun) cb); \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(ret_type ret, arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5, arg6_type arg6, arg7_type arg7, arg8_type arg8); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

/** Mock implementation for mocked function with return value and 8 arguments. */
#define MOCKLIB_MOCK_RET_ARGS8(file, fun, ret_type, arg1_type, arg2_type, arg3_type, arg4_type, \
        arg5_type, arg6_type, arg7_type, arg8_type) \
        MOCKLIB_PARAMS_RET(file, fun, ret_type); \
        struct MOCKLIB_STRUCT_INTERNAL(file, fun) \
        { \
            arg1_type arg1; \
            arg2_type arg2; \
            arg3_type arg3; \
            arg4_type arg4; \
            arg5_type arg5; \
            arg6_type arg6; \
            arg7_type arg7; \
            arg8_type arg8; \
            ret_type ret; \
        }; \
        static struct MOCKLIB_STRUCT_PARAMS(file, fun) \
            MOCKLIB_STRUCT_PARAMS(file, fun); \
        \
        MOCKLIB_FUN_MODE_SET_IMPL(file, fun)\
        \
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(ret_type ret) \
        {\
            mocklib_common_err_if_mode_not_basic(MOCKLIB_STRUCT_PARAMS(file, fun).mode);\
            MOCKLIB_STRUCT_PARAMS(file, fun).ret = ret;\
        }\
        \
        MOCKLIB_FUN_CB_CFG_IMPL(file, fun) \
        \
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)(ret_type ret, arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5, arg6_type arg6, arg7_type arg7, arg8_type arg8) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_FUN_TRACE_EXPECT_COMMON(file, fun); \
            internal = mocklib_common_internal_create_and_check(sizeof(struct MOCKLIB_STRUCT_INTERNAL(file, fun))); \
            internal->arg1 = arg1; \
            internal->arg2 = arg2; \
            internal->arg3 = arg3; \
            internal->arg4 = arg4; \
            internal->arg5 = arg5; \
            internal->arg6 = arg6; \
            internal->arg7 = arg7; \
            internal->arg8 = arg8; \
            internal->ret = ret; \
            mocklib_expdata_internal_set(expdata, internal); \
            mocklib_exp_set(expdata); \
        } \
        \
        MOCKLIB_FUN_CNT_IMPL(file, fun); \
        \
        ret_type fun(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4, \
                arg5_type arg5, arg6_type arg6, arg7_type arg7, arg8_type arg8) \
        { \
            ret_type retval; \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_STRUCT_PARAMS(file, fun).call_cnt++; \
            \
            switch (MOCKLIB_STRUCT_PARAMS(file, fun).mode)\
            {\
            case MOCKLIB_MODE_BASIC:\
                retval = MOCKLIB_STRUCT_PARAMS(file, fun).ret;\
                break;\
            case MOCKLIB_MODE_TRACE:\
                expdata = mocklib_exp_get();\
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun));\
                internal = mocklib_common_internal_get_and_check(expdata);\
                UTLIB_ASSERT_EQUAL(internal->arg1, arg1);\
                UTLIB_ASSERT_EQUAL(internal->arg2, arg2);\
                UTLIB_ASSERT_EQUAL(internal->arg3, arg3);\
                UTLIB_ASSERT_EQUAL(internal->arg4, arg4);\
                UTLIB_ASSERT_EQUAL(internal->arg5, arg5);\
                UTLIB_ASSERT_EQUAL(internal->arg6, arg6);\
                UTLIB_ASSERT_EQUAL(internal->arg7, arg7);\
                UTLIB_ASSERT_EQUAL(internal->arg8, arg8);\
                retval = internal->ret;\
                break;\
            case MOCKLIB_MODE_CALLBACK:\
                retval = MOCKLIB_STRUCT_PARAMS(file, fun).cb(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);\
                break;\
            default:\
                break;\
            }\
            return retval; \
        }

#endif /* _MOCKLIB_DEFINE_H_ */
