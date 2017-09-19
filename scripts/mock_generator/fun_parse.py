import re


def fun_parse(fun_text):
    ret_type_re = re.compile(r'^[a-zA-Z0-9_]+[\s\*]+')
    ret_type = ret_type_re.search(fun_text).group()
    ret_type = ''.join(ret_type.split())
    text = ret_type_re.sub('', fun_text)

    fun_name_re = re.compile(r'^[a-zA-Z0-9_]+\s*')
    fun_name = fun_name_re.search(text).group()
    fun_name = ''.join(fun_name.split())
    text = fun_name_re.sub('', text)

    arg_re = re.compile(r'(\s*void\s*|(\s*[a-zA-Z0-9_]+[\s\*]+[a-zA-Z0-9_]+\s*,)*\s*[a-zA-Z0-9_]+[\s\*]+[a-zA-Z0-9_]+\s*)')
    args = arg_re.finditer(text)
    args_list = [item.group() for item in args]

    arg_types = []
    if 'void' == args_list[0]:
        arg_types.append(args_list[0])
    else:
        arg_type_re = re.compile(r'\s*[a-zA-Z0-9_]+[\s\*]+')
        arg_types_iter = arg_type_re.finditer(text)
        arg_types = [''.join(item.group().split()) for item in arg_types_iter]

    return fun_name, ret_type, arg_types


if __name__ == "__main__":
    f, r, a = fun_parse("void\n mocklib_common_funtype_check (mocklib_expdata_t expdata, type2 * \n * arg2);")
    print("Function name: {}".format(f))
    print("Return type: {}".format(r))
    print("Argument types: {}".format(a))