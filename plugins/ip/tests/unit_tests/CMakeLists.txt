# Copyright Bruno Silva, 2022. All rights reserved.

# Get all source files in the current directory.
set(UNIT_TEST_SRCS
    ipv4_unit_tests.cpp)

# Create an executable for the tests.
add_executable(ipv4_unit_tests)

# Add the source files to the executable.
target_sources(ipv4_unit_tests PRIVATE ${UNIT_TEST_SRCS})

# Link the required libraries.
target_link_libraries(ipv4_unit_tests GTest::gtest_main ip)

# Automatically add all the tests in the source files.
gtest_discover_tests(ipv4_unit_tests)
