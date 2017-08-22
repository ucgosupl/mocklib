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

#define MOCKLIB_MOCK_NORET_ARGS0(file, fun) \
        MOCKLIB_PARAMS_NORET(file, fun); \
        static struct MOCKLIB_STRUCT_PARAMS(file, fun) \
            MOCKLIB_STRUCT_PARAMS(file, fun); \
        \
        void MOCKLIB_FUN_CONFIG(file, fun)(mocklib_mode_t mode) \
        {\
            MOCKLIB_STRUCT_PARAMS(file, fun).mode = mode; \
        }\
        \
        void MOCKLIB_FUN_EXPECT(file, fun)(void) \
        {\
            mocklib_expdata_t expdata = NULL; \
            MOCKLIB_FUN_EXPECT_COMMON(file, fun); \
            mocklib_exp_set(expdata); \
        }\
        \
        MOCKLIB_FUN_CNT_IMPL(file, fun); \
        \
        void fun(void) \
        { \
            mocklib_expdata_t expdata = NULL; \
            MOCKLIB_STRUCT_PARAMS(file, fun).call_cnt++; \
            if (MOCKLIB_MODE_TRACE == MOCKLIB_STRUCT_PARAMS(file, fun).mode) \
            { \
                expdata = mocklib_common_expdata_get_and_check(); \
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun)); \
            } \
        }

#define MOCKLIB_MOCK_HEADER_NORET_ARGS1(file, fun, arg1_type) \
        void MOCKLIB_FUN_CONFIG(file, fun)(mocklib_mode_t mode); \
        void MOCKLIB_FUN_EXPECT(file, fun)(arg1_type arg1); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

#define MOCKLIB_MOCK_NORET_ARGS1(file, fun, arg1_type) \
        MOCKLIB_PARAMS_NORET(file, fun); \
        struct MOCKLIB_STRUCT_INTERNAL(file, fun) \
        { \
            arg1_type arg1; \
        }; \
        static struct MOCKLIB_STRUCT_PARAMS(file, fun) \
            MOCKLIB_STRUCT_PARAMS(file, fun); \
        \
        void MOCKLIB_FUN_CONFIG(file, fun)(mocklib_mode_t mode) \
        { \
                MOCKLIB_STRUCT_PARAMS(file, fun).mode = mode; \
        } \
        \
        void MOCKLIB_FUN_EXPECT(file, fun)(arg1_type arg1) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_FUN_EXPECT_COMMON(file, fun); \
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
            if (MOCKLIB_MODE_TRACE == MOCKLIB_STRUCT_PARAMS(file, fun).mode) \
            { \
                expdata = mocklib_common_expdata_get_and_check(); \
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun)); \
                internal = mocklib_common_internal_get_and_check(expdata); \
                UTLIB_ASSERT_EQUAL(internal->arg1, arg1); \
            } \
        }

#define MOCKLIB_MOCK_HEADER_NORET_ARGS2(file, fun, arg1_type, arg2_type) \
        void MOCKLIB_FUN_CONFIG(file, fun)(mocklib_mode_t mode); \
        void MOCKLIB_FUN_EXPECT(file, fun)(arg1_type arg1, arg2_type arg2); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

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
        void MOCKLIB_FUN_CONFIG(file, fun)(mocklib_mode_t mode) \
        { \
            MOCKLIB_STRUCT_PARAMS(file, fun).mode = mode; \
        } \
        \
        void MOCKLIB_FUN_EXPECT(file, fun)(arg1_type arg1, arg2_type arg2) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_FUN_EXPECT_COMMON(file, fun); \
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
            if (MOCKLIB_MODE_TRACE == MOCKLIB_STRUCT_PARAMS(file, fun).mode) \
            { \
                expdata = mocklib_common_expdata_get_and_check(); \
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun)); \
                internal = mocklib_common_internal_get_and_check(expdata); \
                UTLIB_ASSERT_EQUAL(internal->arg1, arg1); \
                UTLIB_ASSERT_EQUAL(internal->arg2, arg2); \
            } \
        }

/* TODO: defines for more args */

#define MOCKLIB_MOCK_HEADER_RET_ARGS0(file, fun, ret_type) \
        void MOCKLIB_FUN_CONFIG(file, fun)(mocklib_mode_t mode, ret_type ret); \
        void MOCKLIB_FUN_EXPECT(file, fun)(ret_type ret); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

#define MOCKLIB_MOCK_RET_ARGS0(file, fun, ret_type) \
        MOCKLIB_PARAMS_RET(file, fun, ret_type); \
        struct MOCKLIB_STRUCT_INTERNAL(file, fun) \
        { \
            ret_type ret; \
        }; \
        static struct MOCKLIB_STRUCT_PARAMS(file, fun) \
            MOCKLIB_STRUCT_PARAMS(file, fun); \
        \
        void MOCKLIB_FUN_CONFIG(file, fun)(mocklib_mode_t mode, ret_type ret) \
        { \
            MOCKLIB_STRUCT_PARAMS(file, fun).mode = mode; \
            MOCKLIB_STRUCT_PARAMS(file, fun).ret = ret; \
        } \
        \
        void MOCKLIB_FUN_EXPECT(file, fun)(ret_type ret) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_FUN_EXPECT_COMMON(file, fun); \
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
            if (MOCKLIB_MODE_BASIC == MOCKLIB_STRUCT_PARAMS(file, fun).mode) \
            { \
                retval = MOCKLIB_STRUCT_PARAMS(file, fun).ret; \
            } \
            else if (MOCKLIB_MODE_TRACE == MOCKLIB_STRUCT_PARAMS(file, fun).mode) \
            { \
                expdata = mocklib_common_expdata_get_and_check(); \
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun)); \
                internal = mocklib_common_internal_get_and_check(expdata); \
                retval = internal->ret; \
            } \
            else \
            { \
                /* Error */\
            } \
            return retval; \
        }

#define MOCKLIB_MOCK_HEADER_RET_ARGS1(file, fun, ret_type, arg1_type) \
        void MOCKLIB_FUN_CONFIG(file, fun)(mocklib_mode_t mode, ret_type ret); \
        void MOCKLIB_FUN_EXPECT(file, fun)(arg1_type arg1, ret_type ret); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

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
        void MOCKLIB_FUN_CONFIG(file, fun)(mocklib_mode_t mode, ret_type ret) \
        { \
            MOCKLIB_STRUCT_PARAMS(file, fun).mode = mode; \
            MOCKLIB_STRUCT_PARAMS(file, fun).ret = ret; \
        } \
        \
        void MOCKLIB_FUN_EXPECT(file, fun)(arg1_type arg1, ret_type ret) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_FUN_EXPECT_COMMON(file, fun); \
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
            if (MOCKLIB_MODE_BASIC == MOCKLIB_STRUCT_PARAMS(file, fun).mode) \
            { \
                retval = MOCKLIB_STRUCT_PARAMS(file, fun).ret; \
            } \
            else if (MOCKLIB_MODE_TRACE == MOCKLIB_STRUCT_PARAMS(file, fun).mode) \
            { \
                expdata = mocklib_common_expdata_get_and_check(); \
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun)); \
                internal = mocklib_common_internal_get_and_check(expdata); \
                UTLIB_ASSERT_EQUAL(internal->arg1, arg1); \
                retval = internal->ret; \
            } \
            else \
            { \
                /* Error */\
            } \
            return retval; \
        }

#define MOCKLIB_MOCK_HEADER_RET_ARGS2(file, fun, ret_type, arg1_type, arg2_type) \
        void MOCKLIB_FUN_CONFIG(file, fun)(mocklib_mode_t mode, ret_type ret); \
        void MOCKLIB_FUN_EXPECT(file, fun)(arg1_type arg1, arg2_type arg2, ret_type ret); \
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);

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
        void MOCKLIB_FUN_CONFIG(file, fun)(mocklib_mode_t mode, ret_type ret) \
        { \
            MOCKLIB_STRUCT_PARAMS(file, fun).mode = mode; \
            MOCKLIB_STRUCT_PARAMS(file, fun).ret = ret;    \
        } \
        \
        void MOCKLIB_FUN_EXPECT(file, fun)(arg1_type arg1, arg2_type arg2, ret_type ret) \
        { \
            mocklib_expdata_t expdata = NULL; \
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL; \
            MOCKLIB_FUN_EXPECT_COMMON(file, fun); \
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
            if (MOCKLIB_MODE_BASIC == MOCKLIB_STRUCT_PARAMS(file, fun).mode) \
            { \
                retval = MOCKLIB_STRUCT_PARAMS(file, fun).ret; \
            } \
            else if (MOCKLIB_MODE_TRACE == MOCKLIB_STRUCT_PARAMS(file, fun).mode) \
            { \
                expdata = mocklib_common_expdata_get_and_check(); \
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun)); \
                internal = mocklib_common_internal_get_and_check(expdata); \
                UTLIB_ASSERT_EQUAL(internal->arg1, arg1); \
                UTLIB_ASSERT_EQUAL(internal->arg2, arg2); \
                retval = internal->ret; \
            } \
            else \
            { \
                /* Error */\
            } \
            return retval; \
        }

/* TODO: defines for more args */
//zamienic kolejnosc w expect - najpierw ret potem arg

#endif /* _MOCKLIB_DEFINE_H_ */
