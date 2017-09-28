import time

def generate_mock_h(file_name, fun_data):
    mock_h = top_comment_generate(file_name)
    mock_h += top_guard_generate(file_name)

    mock_h += "void {0}_mock_init(void);\n\n".format(file_name)

    for fun in fun_data:
        mock_h += callback_generate(file_name, fun[0], fun[1], fun[2])
        mock_h += mode_set_fun_generate(file_name, fun[0])
        mock_h += basic_cfg_fun_generate(file_name, fun[0], fun[1])
        mock_h += cb_cfg_fun_generate(file_name, fun[0])
        mock_h += expect_fun_generate(file_name, fun[0], fun[1], fun[2])
        mock_h += cnt_fun_generate(file_name, fun[0])
        mock_h += "\n"

    mock_h += bottom_guard_generate(file_name)

    return mock_h


def top_comment_generate(file_name):
    retval = """/*
 * File: {0}_mock.h
 * Author: File generated automatically by mocklib.
 * Brief: Mocks for functions located in {0}.h file.
 *
 * Date: {1}
 */
""".format(file_name, time.strftime("%d.%m.%Y"))
    return retval


def top_guard_generate(file_name):
    guard = "_{0}_MOCK_H_".format(file_name.upper())
    retval = """
#ifndef {0}
#define {0}

""".format(guard)
    return retval


def bottom_guard_generate(file_name):
    guard = "_{0}_MOCK_H_".format(file_name.upper())
    retval= "\n#endif /* {0} */\n".format(guard)
    return retval


def callback_generate(file_name, fun_name, ret_type, arg_type_list):
    retval = "typedef {2} (*{0}_{1}_cb)(".format(file_name, fun_name, ret_type)

    if "void" == arg_type_list[0]:
        retval += "void"
    else:
        i = 1
        for arg_type in arg_type_list:
            if (i > 1):
                retval += ", "

            retval += "{0} arg{1}".format(arg_type, i)
            i += 1

    retval += ");\n"

    return retval


def mode_set_fun_generate(file_name, fun_name):
    retval = "void {0}_mock_{1}_mode_set(mocklib_mode_t mode);\n".format(file_name, fun_name)
    return retval


def basic_cfg_fun_generate(file_name, fun_name, ret_type):
    retval = "void {0}_mock_{1}_basic_cfg(".format(file_name, fun_name)

    if "void" == ret_type:
        retval += "void"
    else:
        retval += "{0} ret ".format(ret_type)

    retval += ");\n"
    return retval


def cb_cfg_fun_generate(file_name, fun_name):
    retval = "void {0}_mock_{1}_cb_cfg({0}_{1}_cb cb);\n".format(file_name, fun_name)
    return retval


def expect_fun_generate(file_name, fun_name, ret_type, arg_type_list):
    retval = "void {0}_mock_{1}_trace_expect(".format(file_name, fun_name)

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

    retval += ");\n"
    return retval;

def cnt_fun_generate(file_name, fun_name):
    retval = "int32_t {0}_mock_{1}_cnt_get(void);\n".format(file_name, fun_name)
    return retval;

if __name__ == "__main__":
    fun1 = ("fun1", "void", ["arg1_type", "arg2_type"])
    fun2 = ("fun2", "int32_t*", ["arg1_type*", "arg2_type"])
    fun3 = ("fun3", "int32_t**", ["void"])
    fun4 = ("fun4", "void", ["void"])

    fun_data = [fun1, fun2, fun3, fun4]

    file_name = "filename"

    print(generate_mock_h(file_name, fun_data))