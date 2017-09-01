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
- Unity test framework support.
- Support for mocking functions with up to 8 input arguments.

# Todo
- Callback mode - call function from pointer inside mock.
- Script for creating mocks based on header files.
- Support for other testing frameworks.

# Getting started

## Steps to create mock for a single function

1. Create mock .c and .h files.
2. Create mocks_general.h file.
3. In .c file:
	3.1 Add includes to library headers:
		- mocklib.h
		- mocklib_internal.h
		- mocklib_expfun.h
		- mocklib_common.h
		- mocklib_define.h
	3.2 Add includes to mock headers:
		- Header of mocked module.
		- Mock .h file from step 1.
		- Global mock header from step 2.
	3.3 Add macros for mocking given function with proper return value and number of arguments.
	3.4 Add init function for the whole mock containing initialization of all mocked functions.
	3.5 Repeat steps 3.3 and 3.4 for every mocked function.
4. In .h file:
	4.1 Add declaration of init function from step 3.4.
	4.2 Add macro for creating headers for mocked functions.
	4.3 Repeat step 4.2 for every mocked function.
5. In test file include:
	- Header of mocked module.
	- Library headers: mocklib.h and mocklib_define.h
	- Mock .h file from step 1.
	
## Example

We want to mock following function in a file dep_module1.h:
```
int8_t dep_more_args_ret(int8_t arg1, int16_t arg2);
```

It has return value and two arguments. So in step 3.3 we must use following macro:
```
MOCKLIB_MOCK_RET_ARGS2(dep_module1, dep_more_args_ret, int8_t, int8_t, int16_t);
```

RET means return value, ARGS2 means two input arguments. Return value and input
arguments are arguments to this macro.

In step 4.2 we use macro:
```
MOCKLIB_MOCK_HEADER_RET_ARGS2(dep_module1, dep_more_args_ret, int8_t, int8_t, int16_t);
```

Example mocks created using defines can be found in folder test/mocks/mock_define.
