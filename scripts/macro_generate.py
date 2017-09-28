import time


def generate_define_h(max_args):
    define_h = generate_top()
    define_h += generate_static_part()

    for i in range(max_args):
        define_h += generate_noret_macros(i)

    for i in range(max_args):
        define_h += generate_ret_macros(i)

    define_h += generate_bottom()

    return define_h


def generate_top():
    retval = """/*
 * File:    mocklib_define.h
 * Author:  File generated automatically by mocklib
 * Brief:   Macros creating mock interface for a given module and function.
 *
 * Date:    {0}
 */

#ifndef _MOCKLIB_DEFINE_H_
#define _MOCKLIB_DEFINE_H_

""".format(time.strftime("%d.%m.%Y"))

    return retval


def generate_bottom():
    retval = """#endif /* _DEP_MODULE1_MOCK_H_ */"""

    return retval


def generate_static_part():
    retval = """/** Name of mocked function id in funtype enum. */
#define MOCKLIB_FUNTYPE(file, fun)		    MOCK_FUNTYPE_ ## file ## _ ## fun

/** Name of mock params structure. */
#define MOCKLIB_STRUCT_PARAMS(file, fun)    file ## _ ## fun ## _params

/** Name of mock internal data structure. */
#define MOCKLIB_STRUCT_INTERNAL(file, fun)  file ## _ ## fun ## _expdata_internal

/** Fields in mock params structure common to all mock types. */
#define MOCKLIB_PARAMS_COMMON_FIELDS \\
        mocklib_mode_t mode;\\
        int32_t call_cnt;

/** Mock params structure definition for mocked functions with no return value. */
#define MOCKLIB_PARAMS_NORET(file, fun) \\
        struct MOCKLIB_STRUCT_PARAMS(file, fun)\\
        {\\
            MOCKLIB_PARAMS_COMMON_FIELDS;\\
            MOCKLIB_CB(file, fun) cb;\\
        };

/** Mock params structure definition for mocked functions with return value. */
#define MOCKLIB_PARAMS_RET(file, fun, ret_type)\\
        struct MOCKLIB_STRUCT_PARAMS(file, fun)\\
        {\\
            MOCKLIB_PARAMS_COMMON_FIELDS;\\
            ret_type ret;\\
            MOCKLIB_CB(file, fun) cb;\\
        };

/** Implementation of mock cmode set function common to all mock types */
#define MOCKLIB_FUN_MODE_SET_IMPL(file, fun) \\
        void MOCKLIB_FUN_MODE_SET(file, fun)(mocklib_mode_t mode)\\
        {\\
            MOCKLIB_STRUCT_PARAMS(file, fun).mode = mode;\\
        }

/** Implementation of mock callback config function common to all mock types */
#define MOCKLIB_FUN_CB_CFG_IMPL(file, fun) \\
        void MOCKLIB_FUN_CB_CFG(file, fun)(MOCKLIB_CB(file, fun) cb)\\
        {\\
                mocklib_common_err_if_mode_not_cb(MOCKLIB_STRUCT_PARAMS(file, fun).mode);\\
                mocklib_common_cb_check((void *)cb);\\
                MOCKLIB_STRUCT_PARAMS(file, fun).cb = cb;\\
        }

/** Implementation of mock cnt get function common to all mock types. */
#define MOCKLIB_FUN_CNT_IMPL(file, fun) \\
        int32_t MOCKLIB_FUN_CNT(file, fun)(void)\\
        {\\
        return MOCKLIB_STRUCT_PARAMS(file, fun).call_cnt;\\
        }

/** Fragment of mock trace expect function common to all mock types. */
#define MOCKLIB_FUN_TRACE_EXPECT_COMMON(file, fun) \\
        mocklib_common_err_if_mode_not_trace(MOCKLIB_STRUCT_PARAMS(file, fun).mode);\\
        expdata = mocklib_common_expdata_create_and_check();\\
        mocklib_expdata_funtype_set(expdata, MOCKLIB_FUNTYPE(file, fun));

/** Initialization procedure for a specific mock. */
#define MOCKLIB_MOCK_INIT(file, fun) \\
        memset(&MOCKLIB_STRUCT_PARAMS(file, fun), 0, sizeof(struct MOCKLIB_STRUCT_PARAMS(file, fun)));

"""

    return retval


def generate_noret_macros(args_cnt):
    retval = """/** Mock interface declaration for mocked function with no return value and no arguments. */
#define MOCKLIB_MOCK_HEADER_NORET_ARGS{0}(file, fun""".format(args_cnt)

    if args_cnt is not 0:
        for i in range(args_cnt):
            retval += ", arg{0}_type".format(i + 1)

    retval += """) \\
        typedef void (*MOCKLIB_CB(file, fun))("""

    if args_cnt is 0:
        retval += "void"
    else:
        for i in range(args_cnt):
            if i is not 0:
                retval += ", "

            retval += "arg{0}_type arg{0}".format(i + 1)

    retval += ");\\\n"

    retval += """        void MOCKLIB_FUN_MODE_SET(file, fun)(mocklib_mode_t mode);\\
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(void);\\
        void MOCKLIB_FUN_CB_CFG(file, fun)(MOCKLIB_CB(file, fun) cb);\\
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)("""

    if args_cnt is 0:
        retval += "void"
    else:
        for i in range(args_cnt):
            if i is not 0:
                retval += ", "

            retval += "arg{0}_type arg{0}".format(i + 1)

    retval += """);\\
        int32_t MOCKLIB_FUN_CNT(file, fun)(void);
"""

    retval += """
/** Mock implementation for mocked function with no return value and no arguments. */
#define MOCKLIB_MOCK_NORET_ARGS{0}(file, fun""".format(args_cnt)

    if args_cnt is not 0:
        for i in range(args_cnt):
            retval += ", arg{0}_type".format(i + 1)

    retval += """) \\
        MOCKLIB_PARAMS_NORET(file, fun);\\
        struct MOCKLIB_STRUCT_INTERNAL(file, fun)\\
        {\\
"""

    if args_cnt is not 0:
        for i in range(args_cnt):
            retval += "            arg{0}_type arg{0};\\\n".format(i + 1)

    retval += """        };\\
        static struct MOCKLIB_STRUCT_PARAMS(file, fun)\\
            MOCKLIB_STRUCT_PARAMS(file, fun);\\
        \\
        MOCKLIB_FUN_MODE_SET_IMPL(file, fun)\\
        \\
        void MOCKLIB_FUN_BASIC_CFG(file, fun)(void)\\
        {\\
        }\\
        \\
        MOCKLIB_FUN_CB_CFG_IMPL(file, fun)\\
        \\
        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)("""

    if args_cnt is 0:
        retval += "void"
    else:
        for i in range(args_cnt):
            if i is not 0:
                retval += ", "
            retval += "arg{0}_type arg{0}".format(i + 1)

    retval += """)\\
        {\\
            mocklib_expdata_t expdata = NULL;\\
            MOCKLIB_FUN_TRACE_EXPECT_COMMON(file, fun);\\
            """

    if args_cnt is not 0:
        retval += "internal = mocklib_common_internal_create_and_check(sizeof(struct MOCKLIB_STRUCT_INTERNAL(file, fun)));\\"

        for i in range(args_cnt):
            retval += "internal->arg1 = arg1;\\\n".format(i + 1)

        retval += "            mocklib_expdata_internal_set(expdata, internal);\\"

    retval += """mocklib_exp_set(expdata);\\
        }\\
        \\
        MOCKLIB_FUN_CNT_IMPL(file, fun);\\
        \\
        void fun("""

    if args_cnt is 0:
        retval += "void"
    else:
        for i in range(args_cnt):
            if i is not 0:
                retval += ", "
            retval += "arg{0}_type arg{0}".format(i + 1)

    retval += """)\\
        {\\
            mocklib_expdata_t expdata = NULL;\\
            MOCKLIB_STRUCT_PARAMS(file, fun).call_cnt++;\\
            switch (MOCKLIB_STRUCT_PARAMS(file, fun).mode)\\
            {\\
            case MOCKLIB_MODE_BASIC:\\
                break;\\
            case MOCKLIB_MODE_TRACE:\\
                expdata = mocklib_exp_get();\\
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun));\\
"""

    if args_cnt is not 0:
        retval += "            internal = mocklib_common_internal_get_and_check(expdata);\\\n"

        for i in range(args_cnt):
            retval += "                UTLIB_ASSERT_EQUAL(internal->arg{0}, arg{0});\\\n".format(i + 1)

    retval += """                break;\\
            case MOCKLIB_MODE_CALLBACK:\\
                MOCKLIB_STRUCT_PARAMS(file, fun).cb("""

    if args_cnt is not 0:
        for i in range(args_cnt):
            if i is not 0:
                retval += ", "

            retval += "arg{0}".format(i + 1)

    retval += """);\\
                break;\\
            default:\\
                break;\\
            }\\
        }

"""

    return retval


def generate_ret_macros(args_cnt):
    retval = """"""
    return retval


if __name__ == "__main__":
    print(generate_define_h(2))