import argparse
import os

import mock_generator as mg
#from mock_generator import *

argp = argparse.ArgumentParser(description='Generate mocks from given header file.')
argp.add_argument('file', help="Header file from which mock is generated.")
argp.add_argument('-o', '--out', default="", dest='out', help="Directory where generated mocks should be stored.")
argp.add_argument('-i', '--include_path', default="", dest='inc', metavar='INC', help="Include directory for mocked header used in generated source files.")
argp.add_argument('--version', action='version', version='%(prog)s 0.1.0')

args = argp.parse_args()

filepath = args.file
out_dir = args.out
inc_path = args.inc

filename = os.path.basename(filepath)
file_no_ext = os.path.splitext(filename)[0]

if out_dir != "" and out_dir[-1] is not '/':
    out_dir += '/'

if inc_path != "" and inc_path[-1] is not '/':
    inc_path += '/'

with open(filepath, "r") as file:
    fun_list = mg.fun_list_get(file.read())

fun_data = []
for fun in fun_list:
    fun_name, ret_type, arg_types = mg.fun_parse(fun)
    fun_data.append((fun_name, ret_type, arg_types))

if out_dir is not "" and not os.path.exists(out_dir + file_no_ext):
    os.makedirs(out_dir + file_no_ext)

# Generate mock h file
mock_h = mg.generate_mock_h(file_no_ext, fun_data)
mock_h_file = "{0}{1}/{1}_mock.h".format(out_dir, file_no_ext)

with open(mock_h_file, "w") as file:
    file.write(mock_h)

# Generate mock c file
mock_c = mg.generate_mock_c(file_no_ext, inc_path, fun_data)
mock_c_file = "{0}{1}/{1}_mock.c".format(out_dir, file_no_ext)

with open(mock_c_file, "w") as file:
    file.write(mock_c)

# Generatee or update global file
mock_global_file = "{0}mocks_global.h".format(out_dir)

if os.path.isfile(mock_global_file):
    file = open(mock_global_file, 'r')
    mock_global_content = file.read()
    file.close()
else:
    mock_global_content = mg.generate_global_h_base()

with open(mock_global_file, 'w') as file:
    try:
        file.write(mg.global_h_insert(file_no_ext, fun_data, mock_global_content))
    except ValueError:
        print("Invalid mocks_global.h file - delete it.")

