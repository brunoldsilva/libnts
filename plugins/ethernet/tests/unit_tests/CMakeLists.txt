# Copyright Bruno Silva, 2022. All rights reserved.

# Get all source files in the current directory.
set(UNIT_TEST_SRCS
    ethernet_unit_tests.cpp)

# Create an executable for the tests.
add_executable(eth_unit_tests)

# Add the source files to the executable.
target_sources(eth_unit_tests PRIVATE ${UNIT_TEST_SRCS})

# Link the required libraries.
target_link_libraries(eth_unit_tests GTest::gtest_main eth)

# Automatically add all the tests in the source files.
gtest_discover_tests(eth_unit_tests)
