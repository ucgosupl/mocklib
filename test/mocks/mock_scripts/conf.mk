##
# File:		conf.mk
# Author:	Maciej Gajdzica
# Brief:	
#
# Date:		26.07.2017
##

#Name of output files
TARGET_NAME := mock_scripts

# Directory containing compilation result.
OUT_DIR := out/

# Defines passed as compiler arguments
GLOBAL_DEFS := \
UNIT_TEST \
MOCKLIB_UNIT_TEST \

# Paths to header files (.h).
# In the code paths relative to this path should be provided.
INC_DIRS := \
../src/ \
../src/dep_module1/ \

# Paths to source file folders (.c and .S).
# In these paths source files are searched recursively in the subfolders.
SRC_DIRS := \

# Additional source files to be compiled.
SRC_FILES := \

# Source paths to be excluded from build.
SRC_DIRS_EXC := \

# Source files to be excluded from build.
SRC_FILES_EXC := \

# Paths to test header files (.h).
# In the code paths relative to this path should be provided.
TEST_INC_DIRS := \
. \
mocks/ \
mocks/dep_module1/ \
../../utlib_checks/ \
../../../src \
../../../port/std_malloc \
../../../external/Unity/src \
../../../external/Unity/extras/fixture/src \

# Paths to test source file folders (.c and .S).
# In these paths source files are searched recursively in the subfolders.
TEST_SRC_DIRS := \
./ \
../test/ \
../../utlib_checks/ \
../../../src/ \
../../../external/Unity/src/ \
../../../external/Unity/extras/fixture/src/ \

# Additional test source files to be compiled.
TEST_SRC_FILES := \

# Test source paths to be excluded from build.
TEST_SRC_DIRS_EXC := \

# Test source files to be excluded from build.
TEST_SRC_FILES_EXC := \

# Paths to the precompiled libraries (.a).
LIB_DIRS := \

# Precompiled libraries used.
# Here we provide only the name of the library. File name also contains lib
# prefix and .a extension. For example for math library we provide here only
# the name "m", but actual file name is "libm.a".
LIBS := \

include ../build.mk