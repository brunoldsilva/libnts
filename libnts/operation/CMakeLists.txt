# Copyright (C) 2022-2023 Bruno Silva - All Rights Reserved.

# Get all source files in the current directory.
set(SOURCES
    operation.cpp)

# Add sources to the Network Testing Suite library.
target_sources(nts PRIVATE ${SOURCES})

# Get all test files in the current directory.
set(UNIT_TEST_SRCS)

# Create an unit test for each module.
unit_test_foreach(${UNIT_TEST_SRCS})
