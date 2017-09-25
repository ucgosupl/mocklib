import time


def generate_mock_c(file_name, include_path, fun_data):
    mock_c = top_comment_generate(file_name)
    mock_c += includes_generate(file_name, include_path)

    for fun in fun_data:
        mock_c += struct_params_generate(file_name, fun[0], fun[1])
        mock_c += struct_internal_generate(file_name, fun[0], fun[1], fun[2])
        mock_c += params_declaration_generate(file_name, fun[0])
        mock_c += config_fun_generate(file_name, fun[0], fun[1])
        mock_c += expect_fun_generate(file_name, fun[0], fun[1], fun[2])
        mock_c += cnt_fun_generate(file_name, fun[0])
        mock_c += mock_fun_generate(file_name, fun[0], fun[1], fun[2])

    mock_c += mock_init_fun_generate(file_name, fun_data)

    return mock_c


def top_comment_generate(file_name):
    retval = """/*
 * File: {0}_mock.c
 * Author: File generated automatically by mocklib.
 * Brief: Mocks for functions located in {0}.h file.
 *
 * Date: {1}
 */
""".format(file_name, time.strftime("%d.%m.%Y"))
    return retval

def includes_generate(file_name, include_path):
    retval = """
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "mocklib_utlib_defines.h"

#include "mocklib.h"
#include "mocklib_internal.h"
#include "mocklib_expfun.h"
#include "mocklib_common.h"

#include "{0}{1}.h"
#include "{1}_mock.h"
#include "mocks_global.h"

""".format(include_path, file_name)
    return retval

def struct_params_generate(file_name, fun_name, ret_type):
    retval = """struct {0}_{1}_params
{{
    mocklib_mode_t mode;
    int32_t call_cnt;
""".format(file_name, fun_name)

    if "void" != ret_type:
        retval += "\n    {0} ret;\n".format(ret_type)

    retval += "};\n\n"
    return retval;

def struct_internal_generate(file_name, fun_name, ret_type, arg_type_list):
    retval = """struct {0}_{1}_expdata_internal
{{
""".format(file_name, fun_name)

    if "void" != ret_type:
        retval += "    {0} ret;\n".format(ret_type)

    if "void" != arg_type_list[0]:
        if "void" != ret_type:
            retval += "\n"

        i = 1;
        for arg_type in arg_type_list:
            retval += "    {0} arg{1};\n".format(arg_type, i)
            i += 1

    retval += "};\n\n"
    return retval

def params_declaration_generate(file_name, fun_name):
    retval = "static struct {0}_{1}_params {0}_{1}_params;\n\n".format(file_name, fun_name)
    return retval

def config_fun_generate(file_name, fun_name, ret_type):
    retval = "void {0}_mock_{1}_config(mocklib_mode_t mode".format(file_name, fun_name)

    if "void" != ret_type:
        retval += ", {0} ret".format(ret_type)

    retval += ")\n{\n"

    retval += "    {0}_{1}_params.mode = mode;\n".format(file_name, fun_name)

    if "void" != ret_type:
        retval += "    {0}_{1}_params.ret = ret;\n".format(file_name, fun_name)

    retval += "}\n\n"

    return retval

def expect_fun_generate(file_name, fun_name, ret_type, arg_type_list):
    retval = "void {0}_mock_{1}_expect(".format(file_name, fun_name)

    args = 0
    if "void" != ret_type:
        retval += "{0} ret, ".format(ret_type)
        args += 1

    if "void" != arg_type_list[0]:
        i = 1
        for arg_type in arg_type_list:
            retval += "{0} arg{1}, ".format(arg_type, i)
            i += 1
            args += 1

    if 0 == args:
        retval += "void"
    else:
        retval = retval[:-2]

    retval += ")\n{\n"
    retval += """    mocklib_expdata_t expdata = NULL;
    struct {0}_{1}_expdata_internal *internal = NULL;

    mocklib_common_err_if_mode_not_trace({0}_{1}_params.mode);

    expdata = mocklib_common_expdata_create_and_check();
    mocklib_expdata_funtype_set(expdata, MOCK_FUNTYPE_{0}_{1});
""".format(file_name, fun_name)

    if 0 == args:
        retval += "\n    (void)internal;\n"
    else:
        retval += "\n    internal = mocklib_common_internal_create_and_check(sizeof(struct {0}_{1}_expdata_internal));\n".format(file_name, fun_name)

        if "void" != ret_type:
            retval += "    internal->ret = ret;\n"

        if "void" != arg_type_list[0]:
            i = 1
            for arg_type in arg_type_list:
                retval += "    internal->arg{0} = arg{0};\n".format(i)
                i += 1

        retval += "    mocklib_expdata_internal_set(expdata, internal);\n"

    retval += "\n    mocklib_exp_set(expdata);\n}\n\n"

    return retval


def cnt_fun_generate(file_name, fun_data):
    retval = """int32_t {0}_mock_{1}_cnt_get(void)
{{
    return {0}_{1}_params.call_cnt;
}}

""".format(file_name, fun_data)

    return retval


def mock_fun_generate(file_name, fun_name, ret_type, arg_type_list):
    retval = "{1} {0}(".format(fun_name, ret_type)

    if "void" == arg_type_list[0]:
        retval += "void"
    else:
        i = 1
        for arg_type in arg_type_list:
            retval += "{0} arg{1}, ".format(arg_type, i)
            i += 1

        retval = retval[:-2]


    retval += ")\n{\n"

    if "void" != ret_type:
        retval += "    {0} retval;\n".format(ret_type)

    retval += """    mocklib_expdata_t expdata = NULL;
    struct {0}_{1}_expdata_internal *internal = NULL;

    {0}_{1}_params.call_cnt++;

""".format(file_name, fun_name)

    retval += "    if (MOCKLIB_MODE_BASIC == {0}_{1}_params.mode)\n    {{".format(file_name, fun_name)

    if "void" != ret_type:
        retval += "\n        retval = {0}_{1}_params.ret;".format(file_name, fun_name)

    retval += "\n    }\n"

    retval += """    else if (MOCKLIB_MODE_TRACE == {0}_{1}_params.mode)
    {{
        expdata = mocklib_exp_get();

        mocklib_common_funtype_check(expdata, MOCK_FUNTYPE_{0}_{1});
""".format(file_name, fun_name)

    args = 0
    if "void" != ret_type:
        args += 1

    if "void" != arg_type_list[0]:
            args += 1

    if 0 != args:
        retval += "\n        internal = mocklib_common_internal_get_and_check(expdata);\n\n"

        if "void" != arg_type_list[0]:
            for i in range(len(arg_type_list)):
                retval += "        UTLIB_ASSERT_EQUAL(internal->arg{0}, arg{0});\n".format(i+1)

        if "void" != ret_type:
            retval += "        retval = internal->ret;\n"

    retval += "    }\n"

    retval += """    else
    {
        /*TODO: handle error*/
    }
"""

    if "void" != ret_type:
        retval += """
    return retval;
"""

    retval += "}\n\n"

    return retval


def mock_init_fun_generate(file_name, fun_data):
    retval = "void {0}_mock_init(void)\n{{\n".format(file_name)

    for fun in fun_data:
        retval += "    memset(&{0}_{1}_params, 0, sizeof(struct {0}_{1}_params));\n".format(file_name, fun[0])

    retval += "}\n"
    return retval


if __name__ == "__main__":
    fun1 = ("fun1", "void", ["arg1_type", "arg2_type"])
    fun2 = ("fun2", "int32_t*", ["arg1_type*", "arg2_type"])
    fun3 = ("fun3", "int32_t**", ["void"])
    fun4 = ("fun4", "void", ["void"])

    fun_data = [fun1, fun2, fun3, fun4]

    file_name = "filename"
    include_path = "dir/"

    print(generate_mock_c(file_name, include_path, fun_data))