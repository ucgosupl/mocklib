import time
import sys


def generate_define_h(max_args):
    define_h = top_generate()
    define_h += static_part_generate()

    for i in range(max_args + 1):
        define_h += mock_header_noret(i)
        define_h += mock_impl_noret(i)

    for i in range(max_args + 1):
        define_h += mock_header_ret(i)
        define_h += mock_impl_ret(i)

    define_h += bottom_guard()

    return define_h

def top_generate():
    retval = top_comment()
    retval += top_guard()

    return retval


def static_part_generate():
    retval = funtype()
    retval += struct_params()
    retval += struct_internal()
    retval += params_common_fields()
    retval += params_noret()
    retval += params_ret()
    retval += fun_mode_set_impl()
    retval += fun_cb_cfg_impl()
    retval += fun_cnt_impl()
    retval += fun_trace_expect_common()
    retval += mock_init()

    return retval


def mock_header_noret(args_cnt):
    retval = define_mock_header_noret(args_cnt)
    retval += mock_header_cb_noret(args_cnt)
    retval += mock_header_mode_set()
    retval += mock_header_basic_cfg_noret()
    retval += mock_header_cb_cfg()
    retval += mock_header_trace_expect_noret(args_cnt)
    retval += mock_header_cnt()

    return retval


def mock_header_ret(args_cnt):
    retval = define_mock_header_ret(args_cnt)
    retval += mock_header_cb_ret(args_cnt)
    retval += mock_header_mode_set()
    retval += mock_header_basic_cfg_ret()
    retval += mock_header_cb_cfg()
    retval += mock_header_trace_expect_ret(args_cnt)
    retval += mock_header_cnt()

    return retval


def mock_impl_noret(args_cnt):
    retval = define_mock_impl_noret(args_cnt)
    retval += mock_impl_params_noret()
    retval += mock_impl_internal_noret(args_cnt)
    retval += mock_impl_params_declaration()
    retval += mock_impl_mode_set()
    retval += mock_impl_basic_cfg_noret()
    retval += mock_impl_cb_cfg()
    retval += mock_impl_trace_expect_noret(args_cnt)
    retval += mock_impl_cnt()
    retval += mock_impl_fun_noret(args_cnt)

    return retval


def mock_impl_ret(args_cnt):
    retval = define_mock_impl_ret(args_cnt)
    retval += mock_impl_params_ret()
    retval += mock_impl_internal_ret(args_cnt)
    retval += mock_impl_params_declaration()
    retval += mock_impl_mode_set()
    retval += mock_impl_basic_cfg_ret()
    retval += mock_impl_cb_cfg()
    retval += mock_impl_trace_expect_ret(args_cnt)
    retval += mock_impl_cnt()
    retval += mock_impl_fun_ret(args_cnt)

    return retval


def top_comment():
    retval = """/*
 * File:    mocklib_define.h
 * Author:  File generated automatically by mocklib
 * Brief:   Macros creating mock interface for a given module and function.
 *
 * Date:    {0}
 */

""".format(time.strftime("%d.%m.%Y"))

    return retval


def top_guard():
    retval = """#ifndef _MOCKLIB_DEFINE_H_
#define _MOCKLIB_DEFINE_H_

"""
    return retval


def bottom_guard():
    retval = """#endif /* _DEP_MODULE1_MOCK_H_ */"""

    return retval


def funtype():
    retval = """/** Name of mocked function id in funtype enum. */
#define MOCKLIB_FUNTYPE(file, fun)		    MOCK_FUNTYPE_ ## file ## _ ## fun

"""
    return retval


def struct_params():
    retval = """/** Name of mock params structure. */
#define MOCKLIB_STRUCT_PARAMS(file, fun)    file ## _ ## fun ## _params

"""
    return retval


def struct_internal():
    retval = """/** Name of mock internal data structure. */
#define MOCKLIB_STRUCT_INTERNAL(file, fun)  file ## _ ## fun ## _expdata_internal

"""
    return retval


def params_common_fields():
    retval = """/** Fields in mock params structure common to all mock types. */
#define MOCKLIB_PARAMS_COMMON_FIELDS \\
        mocklib_mode_t mode;\\
        int32_t call_cnt;

"""
    return retval


def params_noret():
    retval = """/** Mock params structure definition for mocked functions with no return value. */
#define MOCKLIB_PARAMS_NORET(file, fun) \\
        struct MOCKLIB_STRUCT_PARAMS(file, fun)\\
        {\\
            MOCKLIB_PARAMS_COMMON_FIELDS;\\
            MOCKLIB_CB(file, fun) cb;\\
        };

"""
    return retval


def params_ret():
    retval = """/** Mock params structure definition for mocked functions with return value. */
#define MOCKLIB_PARAMS_RET(file, fun, ret_type)\\
        struct MOCKLIB_STRUCT_PARAMS(file, fun)\\
        {\\
            MOCKLIB_PARAMS_COMMON_FIELDS;\\
            ret_type ret;\\
            MOCKLIB_CB(file, fun) cb;\\
        };

"""
    return retval


def fun_mode_set_impl():
    retval = """/** Implementation of mock cmode set function common to all mock types */
#define MOCKLIB_FUN_MODE_SET_IMPL(file, fun) \\
        void MOCKLIB_FUN_MODE_SET(file, fun)(mocklib_mode_t mode)\\
        {\\
            MOCKLIB_STRUCT_PARAMS(file, fun).mode = mode;\\
        }

"""
    return retval


def fun_cb_cfg_impl():
    retval = """/** Implementation of mock callback config function common to all mock types */
#define MOCKLIB_FUN_CB_CFG_IMPL(file, fun) \\
        void MOCKLIB_FUN_CB_CFG(file, fun)(MOCKLIB_CB(file, fun) cb)\\
        {\\
                mocklib_common_err_if_mode_not_cb(MOCKLIB_STRUCT_PARAMS(file, fun).mode);\\
                mocklib_common_cb_check((void *)cb);\\
                MOCKLIB_STRUCT_PARAMS(file, fun).cb = cb;\\
        }

"""
    return retval


def fun_cnt_impl():
    retval = """/** Implementation of mock cnt get function common to all mock types. */
#define MOCKLIB_FUN_CNT_IMPL(file, fun) \\
        int32_t MOCKLIB_FUN_CNT(file, fun)(void)\\
        {\\
        return MOCKLIB_STRUCT_PARAMS(file, fun).call_cnt;\\
        }

"""
    return retval


def fun_trace_expect_common():
    retval = """/** Fragment of mock trace expect function common to all mock types. */
#define MOCKLIB_FUN_TRACE_EXPECT_COMMON(file, fun) \\
        mocklib_common_err_if_mode_not_trace(MOCKLIB_STRUCT_PARAMS(file, fun).mode);\\
        expdata = mocklib_common_expdata_create_and_check();\\
        mocklib_expdata_funtype_set(expdata, MOCKLIB_FUNTYPE(file, fun));

"""
    return retval


def mock_init():
    retval = """#define MOCKLIB_MOCK_INIT(file, fun) \\
        memset(&MOCKLIB_STRUCT_PARAMS(file, fun), 0, sizeof(struct MOCKLIB_STRUCT_PARAMS(file, fun)));

"""
    return retval


def define_mock_header_noret(args_cnt):
    return define_mock_header(args_cnt, False)


def define_mock_header_ret(args_cnt):
    return define_mock_header(args_cnt, True)


def define_mock_header(args_cnt, is_ret):
    if is_ret is True:
        comment = ""
        define = ""
        args = ", ret_type"
    else:
        comment = "no "
        define = "NO"
        args = ""

    retval = """/** Mock interface declaration for mocked function with {1}return value. */
#define MOCKLIB_MOCK_HEADER_{2}RET_ARGS{0}(file, fun{3}""".format(args_cnt, comment, define, args)

    if args_cnt is not 0:
        for i in range(args_cnt):
            retval += ", arg{0}_type".format(i + 1)

    retval += ") \\\n"

    return retval


def mock_header_cb_noret(args_cnt):
    return mock_header_cb(args_cnt, False)


def mock_header_cb_ret(args_cnt):
    return mock_header_cb(args_cnt, True)


def mock_header_cb(args_cnt, is_ret):
    if is_ret is True:
        ret_str = "ret_type"
    else:
        ret_str = "void"

    retval = "        typedef {0} (*MOCKLIB_CB(file, fun))(".format(ret_str)
    retval += arg_list(args_cnt)
    retval += ");\\\n"

    return retval


def mock_header_mode_set():
    return "        void MOCKLIB_FUN_MODE_SET(file, fun)(mocklib_mode_t mode);\\\n"


def mock_header_basic_cfg_noret():
    return mock_header_basic(False)


def mock_header_basic_cfg_ret():
    return mock_header_basic(True)


def mock_header_basic(is_ret):
    if is_ret is True:
        ret_str = "ret_type ret"
    else:
        ret_str = "void"

    return "        void MOCKLIB_FUN_BASIC_CFG(file, fun)({0});\\\n".format(ret_str)


def mock_header_cb_cfg():
    return "        void MOCKLIB_FUN_CB_CFG(file, fun)(MOCKLIB_CB(file, fun) cb);\\\n"


def mock_header_trace_expect_noret(args_cnt):
    return mock_header_trace_expect(args_cnt, False)


def mock_header_trace_expect_ret(args_cnt):
    return mock_header_trace_expect(args_cnt, True)


def mock_header_trace_expect(args_cnt, is_ret):
    if is_ret is True:
        ret_str = "ret_type ret"

        if args_cnt > 0:
            ret_str += ", "
    else:
        ret_str = ""

    retval = "        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)({}".format(ret_str)
    retval += arg_list_no_void(args_cnt)
    retval += ");\\\n"
    return retval


def mock_header_cnt():
    return "        int32_t MOCKLIB_FUN_CNT(file, fun)(void);\n\n"


def define_mock_impl_noret(args_cnt):
    return define_mock_impl(args_cnt, False)


def define_mock_impl_ret(args_cnt):
    return define_mock_impl(args_cnt, True)


def define_mock_impl(args_cnt, is_ret):
    if is_ret is True:
        comment = ""
        define = ""
        args = ", ret_type"
    else:
        comment = "no "
        define = "NO"
        args = ""

    retval = """/** Mock implementation for mocked function with {1}return value. */
#define MOCKLIB_MOCK_{2}RET_ARGS{0}(file, fun{3}""".format(args_cnt, comment, define, args)

    if args_cnt is not 0:
        for i in range(args_cnt):
            retval += ", arg{0}_type".format(i + 1)

    retval += ") \\\n"

    return retval


def mock_impl_params_noret():
    return mock_impl_params(False)


def mock_impl_params_ret():
    return mock_impl_params(True)


def mock_impl_params(is_ret):
    define = ""
    args = ""

    if is_ret is False:
        define = "NO"
    else:
        args = ", ret_type"

    return "        MOCKLIB_PARAMS_{0}RET(file, fun{1});\\\n".format(define, args)


def mock_impl_internal_noret(args_cnt):
    return mock_impl_internal(args_cnt, False)


def mock_impl_internal_ret(args_cnt):
    return mock_impl_internal(args_cnt, True)


def mock_impl_internal(args_cnt, is_ret):
    retval = """        struct MOCKLIB_STRUCT_INTERNAL(file, fun)\\
        {\\
"""

    if args_cnt is not 0:
        for i in range(args_cnt):
            retval += "            arg{0}_type arg{0};\\\n".format(i + 1)

    if is_ret is True:
        retval += "            ret_type ret;\\\n"

    retval += "        };\\\n"
    return retval


def mock_impl_params_declaration():
    return """        static struct MOCKLIB_STRUCT_PARAMS(file, fun)\\
            MOCKLIB_STRUCT_PARAMS(file, fun);\\
        \\
"""


def mock_impl_mode_set():
    return """        MOCKLIB_FUN_MODE_SET_IMPL(file, fun)\\
        \\
"""


def mock_impl_basic_cfg_noret():
    return mock_impl_basic_cfg(False)


def mock_impl_basic_cfg_ret():
    return mock_impl_basic_cfg(True)


def mock_impl_basic_cfg(is_ret):
    if is_ret is True:
        args = "ret_type ret"
        impl = """
            mocklib_common_err_if_mode_not_basic(MOCKLIB_STRUCT_PARAMS(file, fun).mode);\\
            MOCKLIB_STRUCT_PARAMS(file, fun).ret = ret;\\"""
    else:
        args = "void"
        impl = ""

    return """        void MOCKLIB_FUN_BASIC_CFG(file, fun)({0})\\
        {{\\{1}
        }}\\
        \\
""".format(args, impl)


def mock_impl_cb_cfg():
    return """        MOCKLIB_FUN_CB_CFG_IMPL(file, fun)\\
        \\
"""


def mock_impl_trace_expect_noret(args_cnt):
    return mock_impl_trace_expect(args_cnt, False)


def mock_impl_trace_expect_ret(args_cnt):
    return mock_impl_trace_expect(args_cnt, True)


def mock_impl_trace_expect(args_cnt, is_ret):
    retval = "        void MOCKLIB_FUN_TRACE_EXPECT(file, fun)("

    is_ret_or_args_used = False

    if is_ret is True:
        is_ret_or_args_used = True
        retval += "ret_type ret"

    if args_cnt is not 0:
        is_ret_or_args_used = True

        if is_ret is True:
            retval += ", "

        retval += arg_list_no_void(args_cnt)

    if is_ret_or_args_used is False:
        retval += "void"

    retval += """)\\
        {\\
            mocklib_expdata_t expdata = NULL;\\
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL;\\
            MOCKLIB_FUN_TRACE_EXPECT_COMMON(file, fun);\\
"""

    if is_ret_or_args_used is True:
        retval += "            "
        retval += "internal = mocklib_common_internal_create_and_check(sizeof(struct MOCKLIB_STRUCT_INTERNAL(file, fun)));\\\n"

        for i in range(args_cnt):
            retval += "            internal->arg{0} = arg{0};\\\n".format(i + 1)

        if is_ret is True:
            retval += "            internal->ret = ret;\\\n"

        retval += "            mocklib_expdata_internal_set(expdata, internal);\\\n"

    retval += """            mocklib_exp_set(expdata);\\
        }\\
        \\
"""

    return retval


def mock_impl_cnt():
    return """        MOCKLIB_FUN_CNT_IMPL(file, fun);\\
        \\
"""


def mock_impl_fun_noret(args_cnt):
    return mock_impl_fun(args_cnt, False)


def mock_impl_fun_ret(args_cnt):
    return mock_impl_fun(args_cnt, True)


def mock_impl_fun(args_cnt, is_ret):
    retval = "        "

    is_ret_or_args_used = False

    if is_ret is True:
        retval += "ret_type"
        is_ret_or_args_used = True
    else:
        retval += "void"

        if args_cnt > 0:
            is_ret_or_args_used = True

    retval += " fun("
    retval += arg_list(args_cnt)

    retval += ")\\\n        {\\\n"

    if is_ret is True:
        retval += "            "
        retval += "ret_type retval;\\\n"



    retval += """            mocklib_expdata_t expdata = NULL;\\
            struct MOCKLIB_STRUCT_INTERNAL(file, fun) *internal = NULL;\\
            MOCKLIB_STRUCT_PARAMS(file, fun).call_cnt++;\\
            switch (MOCKLIB_STRUCT_PARAMS(file, fun).mode)\\
            {\\
            case MOCKLIB_MODE_BASIC:\\
"""

    if is_ret is True:
        retval += "                "
        retval += "retval = MOCKLIB_STRUCT_PARAMS(file, fun).ret;\\\n"

    retval += """                break;\\
            case MOCKLIB_MODE_TRACE:\\
                expdata = mocklib_exp_get();\\
                mocklib_common_funtype_check(expdata, MOCKLIB_FUNTYPE(file, fun));\\
"""

    if is_ret_or_args_used is True:
        retval += "                internal = mocklib_common_internal_get_and_check(expdata);\\\n"

        for i in range(args_cnt):
            retval += "                UTLIB_ASSERT_EQUAL(internal->arg{0}, arg{0});\\\n".format(i + 1)

        if is_ret is True:
            retval += "                retval = internal->ret;\\\n"

    retval += """                break;\\
            case MOCKLIB_MODE_CALLBACK:\\
"""

    retval += "                "

    if is_ret is True:
        retval += "retval = "

    retval += "MOCKLIB_STRUCT_PARAMS(file, fun).cb("

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
"""

    if is_ret is True:
        retval += "            return retval;\\\n"

    retval += "        }\n\n"

    return retval


def arg_list(args_cnt):
    retval = ""

    if args_cnt is 0:
        retval += "void"
    else:
        retval += arg_list_no_void(args_cnt)

    return retval


def arg_list_no_void(args_cnt):
    retval = ""

    for i in range(args_cnt):
        if i is not 0:
            retval += ", "

        retval += "arg{0}_type arg{0}".format(i + 1)

    return retval

if __name__ == "__main__":
    args_cnt = int(sys.argv[1])

    with open("mocklib_define.h", 'w') as f:
        f.write(generate_define_h(args_cnt))