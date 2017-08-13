##
# File:		mingw-gcc.mk
# Author:	Maciej Gajdzica
# Brief:	Definitions for build using mingw-gcc compiler.
#
# Date:		26.07.2017
##


TOOLCHAIN := 

AR := $(TOOLCHAIN)ar
AS := $(TOOLCHAIN)gcc -x assembler-with-cpp
CC := $(TOOLCHAIN)gcc
OBJCOPY := $(TOOLCHAIN)objcopy
OBJDUMP := $(TOOLCHAIN)objdump
SIZE := $(TOOLCHAIN)size
DBG := $(TOOLCHAIN)gdb
BIN2HEX := $(TOOLCHAIN)objcopy -O ihex