Mocklib
======================

C library for creating test doubles.

# Features
- Basic mode:
	* Count function calls.
	* Always return the same value.
	* Ignore input arguments.
- Trace mode:
	* Count function calls.
	* Separate return value for every call.
	* Check input arguments - other arguments for every call.
	* Check function call order.
- Macros for fast mock creation.
- Python scripts for autogenerating mocks.
- Unity test framework support.
- Support for mocking functions with up to 8 input arguments.

# Todo
- Callback mode - call function from pointer inside mock.
- Support for other testing frameworks.

# Getting started

## Scripts for autogeneration

To autogenerate mocks mocklib_generate.py script should be run with following syntax:
```
python mocklib_generate.py [-o OUT] [-i INC] FILE
```

positional arguments:
  FILE                  		Header file from which mock is generated.

optional arguments:
  -o OUT, --out OUT     		Directory where generated mocks should be stored.
  -i INC, --include_path INC	Include directory for mocked header used in generated
                        		source files.

Default value for optional arguments is empty string.

Script will generate mock .c and .h files in folder named after FILE provided, and
mocks_global.h file outside this folder. Running script for generating mocks for other
files will result in adding new folders containing mocks .c and .h files and modifications
to mocks_global.h file.

Example script usage is presented in test/mocks/mock_scripts test target.

## Macros

Macros can be used for creating mocks fast without autogeneration scripts. 

### Steps to create mock for a single function using macros

1. Create mock .c and .h files.
1. Create mocks_general.h file.
1. In .c file:
   1. Add includes to library headers:
      - mocklib.h
      - mocklib_internal.h
      - mocklib_expfun.h
      - mocklib_common.h
      - mocklib_define.h
   1. Add includes to mock headers:
      - Header of mocked module.
      - Mock .h file from step 1.
      - Global mock header from step 2.
   1. Add macros for mocking given function with proper return value and number of arguments.
   1. Add init function for the whole mock containing initialization of all mocked functions.
   1. Repeat steps 3.3 and 3.4 for every mocked function.
1. In .h file:
   1. Add declaration of init function from step 3.4.
   1. Add macro for creating headers for mocked functions.
   1. Repeat step 4.2 for every mocked function.
1. In mocks_general.h file:
   1. For every mocked function add label to the enum using macro.
1. In test file include:
   - Header of mocked module.
   - Library headers: mocklib.h and mocklib_define.h
   - Mock .h file from step 1.
	
### Example

We want to mock following function in a file dep_module1.h:
```
int8_t dep_more_args_ret(int8_t arg1, int16_t arg2);
```

It has return value and two arguments. So in step 3.3 we use macro:
```
MOCKLIB_MOCK_RET_ARGS2(dep_module1, dep_more_args_ret, int8_t, int8_t, int16_t)
```

RET means return value, ARGS2 means two input arguments. Return value and input
arguments are arguments to this macro.

In step 3.4 we use macros for init function name and for all function mocks initialization:
```
void MOCKLIB_FUN_MOCK_INIT(dep_module1)(void)
{
    MOCKLIB_MOCK_INIT(dep_module1, dep_no_args_no_ret);
}
```

In step 4.2 we use macro:
```
MOCKLIB_MOCK_HEADER_RET_ARGS2(dep_module1, dep_more_args_ret, int8_t, int8_t, int16_t)
```

In step 5.1 we use macro:
```
MOCKLIB_FUNTYPE(dep_module1, dep_no_args_no_ret)
```

Example mocks created using defines can be found in folder test/mocks/mock_define.
