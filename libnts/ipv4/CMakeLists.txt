# Copyright (C) 2022-2023 Bruno Silva - All Rights Reserved.

# Add the current directory to the include path for the Network Testing Suite library.
target_include_directories(nts PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Get all source files in the current directory.
set(SOURCES
    ipv4.cpp)

# Add sources to the Network Testing Suite library.
target_sources(nts PRIVATE ${SOURCES})

# Get all test files in the current directory.
set(UNIT_TEST_SRCS
    ipv4.test.cpp)

# Create an unit test for each module.
unit_test_foreach(${UNIT_TEST_SRCS})
