import time

def generate_global_h_base():
    mocks_global = top_comment_generate()
    mocks_global += top_guard_generate()
    mocks_global += enum_generate()
    mocks_global += bottom_guard_generate()

    return mocks_global


def generate_global_h_enum(file_name, fun_data):
    enum = ""

    for fun in fun_data:
        enum += "MOCK_FUNTYPE_{0}_{1},\n".format(file_name, fun[0])

    return enum


def global_h_insert(file_name, fun_data, file_base):

    base_lines = file_base.splitlines()
    line_begin = base_lines.index("    MOCK_FUNTYPE_NONE,")
    line_end = base_lines.index("};")

    funs_enum = generate_global_h_enum(file_name, fun_data)

    out_file = ""
    for line in base_lines[:line_begin+1]:
        out_file += line + '\n'

    label_lines = []

    # Read all existing lines
    for line in base_lines[line_begin+1:line_end]:
        label_lines.append(line.replace(' ', ''))

    # Read all lines to be added
    for line in funs_enum.splitlines():
        label_lines.append(line.replace(' ', ''))

    # Sort and remove duplicates
    label_sorted_no_duplicates = list(set(label_lines))
    label_sorted_no_duplicates.sort()

    # Write to output with correct formatting
    for line in label_sorted_no_duplicates:
        out_file += "    " + line + '\n'

    for line in base_lines[line_end:]:
        out_file += line + '\n'

    return out_file


def top_comment_generate():
    retval = """/*
 * File: mocks_global.h
 * Author: File generated automatically by mocklib.
 * Brief: Header common to all generated mocks.
 *
 * Date: {0}
 */
""".format(time.strftime("%d.%m.%Y"))
    return retval


def top_guard_generate():
    retval = """
#ifndef _MOCKS_GLOBAL_H_
#define _MOCKS_GLOBAL_H_

"""
    return retval


def bottom_guard_generate():
    retval= "\n#endif /* _MOCKS_GLOBAL_H_ */\n"
    return retval


def enum_generate():
    retval = """enum
{
    MOCK_FUNTYPE_NONE,
};
"""
    return retval


if __name__ == "__main__":
    fun1 = ("fun1", "void", ["arg1_type", "arg2_type"])
    fun2 = ("fun2", "int32_t*", ["arg1_type*", "arg2_type"])
    fun3 = ("fun3", "int32_t**", ["void"])
    fun4 = ("fun4", "void", ["void"])

    fun_data = [fun1, fun2, fun3, fun4]

    file_name = "filename"

    base = generate_global_h_base()
    print(base)
    print("\n==================\n")

    print(generate_global_h_enum(file_name, fun_data))
    print("\n==================\n")

    print(global_h_insert(file_name, fun_data, base))