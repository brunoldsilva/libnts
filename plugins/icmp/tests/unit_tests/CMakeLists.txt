# Copyright Bruno Silva, 2022. All rights reserved.

# Get all source files in the current directory.
set(UNIT_TEST_SRCS
    icmp_unit_tests.cpp)

# Create an executable for the tests.
add_executable(icmp_unit_tests)

# Add the source files to the executable.
target_sources(icmp_unit_tests PRIVATE ${UNIT_TEST_SRCS})

# Link the required libraries.
target_link_libraries(icmp_unit_tests GTest::gtest_main icmp)

# Automatically add all the tests in the source files.
gtest_discover_tests(icmp_unit_tests)
