##
# File:		build.mk
# Author:	Maciej Gajdzica
# Brief:	Build steps for single unit test build.
#
# Date:		26.07.2017
##

include ../../makefiles/platform.mk
include ../../makefiles/mingw-gcc.mk
include ../../makefiles/funs.mk

###############################################################################
# Files and paths definitions for production files

# extensions of source C
C_EXT := c

# searching for source C and ASM files in directories provided
C_SRCS := $(call rwildcard,$(SRC_DIRS),*.$(C_EXT))

# removing artifacts added by rwildcard
C_SRCS := $(patsubst ./%, %, $(C_SRCS))

# adding single files
C_SRCS += $(filter %.$(C_EXT), $(SRC_FILES))

# searching for source C files in directories provided
C_SRCS_EXC := $(patsubst ./%, %, $(call rwildcard,$(SRC_DIRS_EXC),*.$(C_EXT)))

# adding single files
C_SRCS_EXC += $(filter %.$(C_EXT), $(SRC_FILES_EXC))

# excluding files from src list
C_SRCS := $(filter-out $(C_SRCS_EXC), $(C_SRCS))

#
################################################################################

################################################################################
# Files and paths definitions for test files

# searching for source C files in directories provided
TEST_C_SRCS := $(call rwildcard,$(TEST_SRC_DIRS),*.$(C_EXT))

# removing artifacts added by rwildcard
TEST_C_SRCS := $(patsubst ./%, %, $(TEST_C_SRCS))

# adding single files
TEST_C_SRCS += $(filter %.$(C_EXT), $(TEST_SRC_FILES))

# searching for source C and ASM files in directories provided
TEST_C_SRCS_EXC := $(patsubst ./%, %, $(call rwildcard,$(TEST_SRC_DIRS_EXC),*.$(C_EXT)))

# adding single files
TEST_C_SRCS_EXC += $(filter %.$(C_EXT), $(TEST_SRC_FILES_EXC))

# excluding files from src list
TEST_C_SRCS := $(filter-out $(TEST_C_SRCS_EXC), $(TEST_C_SRCS))

# variable storing all possible paths where dependencies could be found
VPATH := $(sort $(dir $(C_SRCS)) $(INC_DIRS) $(dir $(TEST_C_SRCS)) $(TEST_INC_DIRS))

#
################################################################################

################################################################################
# Compiler defines common to production and test files

# Compiler flags used for both C and ASM files
# 
CORE_FLAGS := -g

# Add global defines
GLOBAL_DEFS_F = $(patsubst %, -D%, $(GLOBAL_DEFS))

CORE_FLAGS += $(GLOBAL_DEFS_F)

#
################################################################################

################################################################################
# Compiler defines for production files

# Compiler flags specific for production C files
# -std - C standard: c89, c99, gnu89,gnu99, iso9899:119409
# -O0 - optimization level: -O0, -O1, -O2, -O3, -Os
# remove unused functions and variables
C_FLAGS := -std=gnu89 -O0 -ffunction-sections -fdata-sections $(DEBUG_C_FLAGS)

# Warning flags for production C files
# -Wall - standard warnings
# -Wextra - extended warnings
# -Wstrict-prototypes - additional warnings for function prototypes
# -Waddress - additional check for addressing errors
# -Wcomment - check for nested comments
C_WARNINGS := -Wall -Wextra -Wstrict-prototypes -Waddress

# Add header paths for production C files
INC_DIRS_F = $(patsubst %, -I%, $(INC_DIRS))

# final flags for C and ASM production files
C_FLAGS += $(CORE_FLAGS) $(C_WARNINGS) $(INC_DIRS_F)

#
################################################################################

################################################################################
# Compiler defines for test files

# Compiler flags specific for test C files
# -std - C standard: c89, c99, gnu89,gnu99, iso9899:119409
# -O0 - optimization level: -O0, -O1, -O2, -O3, -Os
# remove unused functions and variables
TEST_C_FLAGS := -std=gnu89 -O0 -ffunction-sections -fdata-sections $(DEBUG_C_FLAGS)

# Warning flags for test C files
# -Wall - standard warnings
# -Wextra - extended warnings
# -Wstrict-prototypes - additional warnings for function prototypes
# -Waddress - additional check for addressing errors
# -Wcomment - check for nested comments
TEST_C_WARNINGS := -Wall

# Add header paths for  test C files
TEST_INC_DIRS_F = $(INC_DIRS_F) $(patsubst %, -I%, $(TEST_INC_DIRS))

# final flags for C and ASM test files
TEST_C_FLAGS += $(CORE_FLAGS) $(TEST_C_WARNINGS) $(TEST_INC_DIRS_F)

#
################################################################################

################################################################################
# Linker defines common to production and test files

# -Wl,--gc-sections - unused function removal
# -Wl, -Map - map file to be created
# -Wl, --cref - include cross reference table in map file
LD_FLAGS := -Wl,--gc-sections -Wl,-Map=$(OUT_DIR)bin/$(TARGET_NAME).map,--cref

# Add static lib dirs
LIB_DIRS_F = $(patsubst %, -L%, $(LIB_DIRS))

# Add static libs
LIBS_F = $(patsubst %, -l%, $(LIBS))

# final flags for C, ASM and linker
LD_FLAGS += $(CORE_FLAGS)
LD_LIBS = $(LIB_DIRS_F) $(LIBS_F)

#
################################################################################

###############################################################################
# Defines for output files

BIN := $(OUT_DIR)bin/$(TARGET_NAME).exe
HEX := $(OUT_DIR)bin/$(TARGET_NAME).hex
LSS := $(OUT_DIR)bin/$(TARGET_NAME).lss
DMP := $(OUT_DIR)bin/$(TARGET_NAME).dmp

C_OBJS := $(addprefix $(OUT_DIR)code/, $(notdir $(C_SRCS:.$(C_EXT)=.o)))
TEST_C_OBJS := $(addprefix $(OUT_DIR)test/, $(notdir $(TEST_C_SRCS:.$(C_EXT)=.o)))
OBJS := $(C_OBJS) $(TEST_C_OBJS)

GENERATED := $(OBJS) $(BIN) $(HEX) $(LSS) $(DMP)

#
################################################################################

all : print_header make_out_dir $(BIN) $(LSS) $(DMP) $(HEX) print_size test_run
	@$(ECHO) build $(TARGET_NAME)

test_run : $(ELF)

# Binaries generation
$(HEX) : $(BIN)
	@$(ECHO) "Creating HEX image: $(HEX)"
	$(BIN2HEX) $< $@
	@$(ECHO)

# Memory dump
$(DMP) : $(BIN)
	@$(ECHO) "Creating memory dump: $(DMP)"
	$(OBJDUMP) -x --syms $< > $@
	@$(ECHO)

# Extended listing
$(LSS) : $(BIN)
	@$(ECHO) "Creating extended listing: $(LSS)"
	$(OBJDUMP) -S $< > $@
	@$(ECHO)

# Linking
$(BIN) : $(OBJS)
	@$(ECHO) "Linking target: $(ELF)"
	$(CC) $(LD_FLAGS) $(OBJS) $(LD_LIBS) -o $@
	@$(ECHO)

# Production C files compilation
$(OUT_DIR)code/%.o : %.$(C_EXT)
	@$(ECHO) "Compiling production file: $<"
	$(CC) -c $(C_FLAGS) $< -o $@
	@$(ECHO)

# Test C files compilation
$(OUT_DIR)test/%.o : %.$(C_EXT)
	@$(ECHO) "Compiling test file: $<"
	$(CC) -c $(TEST_C_FLAGS) $< -o $@
	@$(ECHO)
	
# Print output binary size
print_size : $(OBJS) $(BIN)
	@$(ECHO) "Size of modules:"
	$(SIZE) -B -t --common $(OBJS)
	@$(ECHO)
	@$(ECHO) "Size of target .elf file:"
	$(SIZE) -B $(BIN)
	@$(ECHO)

# Output build information
print_header :
	@$(ECHO)
	@$(ECHO) Target name:
	@$(ECHO) $(TARGET_NAME)
	@$(ECHO) Directory:
	@$(PWD)
	@$(ECHO)
	@$(ECHO)
	@$(ECHO)
	@$(ECHO) "Include directories:"
	@$(ECHO) $(INC_DIRS) | $(TR) " " "\n"
	@$(ECHO)
	@$(ECHO) "Source files:"
	@$(ECHO) $(C_SRCS) $(ASM_SRCS) | $(TR) " " "\n"
	@$(ECHO)
	@$(ECHO) "Source files excluded:"
	@$(ECHO) $(C_SRCS_EXC) | $(TR) " " "\n"
	@$(ECHO)
	@$(ECHO) "Test include directories:"
	@$(ECHO) $(TEST_INC_DIRS) | $(TR) " " "\n"
	@$(ECHO)
	@$(ECHO) "Test source files:"
	@$(ECHO) $(TEST_C_SRCS) | $(TR) " " "\n"
	@$(ECHO)
	@$(ECHO) "Test source files excluded:"
	@$(ECHO) $(TEST_C_SRCS_EXC) | $(TR) " " "\n"
	@$(ECHO)
	@$(ECHO) "Static library directories:"
	@$(ECHO) $(LIB_DIRS) | $(TR) " " "\n"
	@$(ECHO)
	@$(ECHO) "Static libraries:"
	@$(ECHO) $(LIBS) | $(TR) " " "\n"
	@$(ECHO)
	@$(ECHO)
	@$(ECHO)

# Create directories for output files
make_out_dir :
	@$(ECHO) "Create output directories"
	$(MKDIR) -p  $(OUT_DIR)bin
	$(MKDIR) -p  $(OUT_DIR)code
	$(MKDIR) -p  $(OUT_DIR)test
	@$(ECHO)

clean :
	@$(ECHO) clean $(TARGET_NAME)
	$(RM) -rf $(OUT_DIR)

.PHONY : all clean
.PHONY : make_out_dir print_size