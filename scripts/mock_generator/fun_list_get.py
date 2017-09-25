import re
import sys


def fun_list_get(text):
    tmp = preprocessing(text)
    fun_re = re.compile(r'[a-zA-Z0-9_]+[\s\*]+[a-zA-Z0-9_]+\s*\((\s*void\s*|(\s*[a-zA-Z0-9_]+[\s\*]+[a-zA-Z0-9_]+\s*,)*\s*[a-zA-Z0-9_]+[\s\*]+[a-zA-Z0-9_]+\s*)\)\s*;')
    funs = fun_re.finditer(tmp)
    list = [item.group() for item in funs]
    return list


def preprocessing(text):
    result = strip_block_comments(text)
    result = merge_line_splits(result)
    result = strip_line_comments(result)
    result = strip_preprocessor(result)
    result = strip_extern(result)
    return result


def strip_block_comments(text):
    block_re = re.compile(r'/\*[\S\s]*?\*/')
    result = block_re.sub('', text)
    return result


def merge_line_splits(text):
    split_re = re.compile(r'\\\n')
    result = split_re.sub('', text)
    return result


def strip_line_comments(text):
    line_re = re.compile(r'//.*')
    result = line_re.sub('', text)
    return result


def strip_preprocessor(text):
    preprocessor_re = re.compile(r'#.*')
    result = preprocessor_re.sub('', text)
    return result


def strip_extern(text):
    extern_re = re.compile(r'\bextern\b')
    result = extern_re.sub('', text)
    return result


if __name__ == "__main__":
    if 1 >= len(sys.argv):
        filepath = "../test/scripts/fun_parse_ptr.h"
    else:
        filepath = sys.argv[1]

    with open(filepath, "r") as file:
        res = fun_list_get(file.read())
        for s in res:
            print(s)

