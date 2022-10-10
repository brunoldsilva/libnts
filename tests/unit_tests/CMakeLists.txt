# Copyright Bruno Silva, 2022. All rights reserved.

# Get all source files in the current directory.
set(UNIT_TEST_SRCS
    data_unit_unit_tests.cpp
    session_unit_tests.cpp)

# Create an executable for the tests.
add_executable(nts_unit_tests)

# Add the source files to the executable.
target_sources(nts_unit_tests PRIVATE ${UNIT_TEST_SRCS})

# Link the required libraries.
target_link_libraries(nts_unit_tests GTest::gtest_main nts)

# Automatically add all the tests in the source files.
gtest_discover_tests(nts_unit_tests)
