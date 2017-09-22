##
# File:		generate.mk
# Author:	Maciej Gajdzica
# Brief:	Configuration for mock file generation using scripts.
#
# Date:		20.09.2017
##

include ../../../utils/makefiles/platform.mk

################################################################################
# Configurable options

# Output folder when generated mocks should be stored.
MOCK_OUT_DIR := mocks

# All files for which mocks should be generated.
MOCKED_FILES := \
../src/dep_module1/dep_module1.h \

#
################################################################################

################################################################################
# Variables used by targets

MOCK_TARGETS := $(sort $(addprefix $(MOCK_OUT_DIR)/, $(notdir $(MOCKED_FILES:.h=))))

# add path to mocked header to VPATH co it can be found when creating target
VPATH := $(dir $(MOCKED_FILES))

#
################################################################################

all : print $(MOCK_TARGETS)

# Print info
print :
	@$(ECHO) $(MOCK_TARGETS)

# Run mock generation script for a single header file.
$(MOCK_OUT_DIR)/% : %.h
	python ../../../scripts/mocklib_generate.py -o $(MOCK_OUT_DIR) $<

.PHONY : all
.PHONY : print