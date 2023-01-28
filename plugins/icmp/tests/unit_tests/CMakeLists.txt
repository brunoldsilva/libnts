# Copyright Bruno Silva, 2022-2023. All rights reserved.

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

# Copy the unit test environment file to the output directory.
file(COPY ${CMAKE_SOURCE_DIR}/extras/unit_tests_config.json
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/unit_tests_config.json 
     ${CMAKE_CURRENT_BINARY_DIR}/config.json)
