# Add the current directory to the include path for the Network Testing Suite library.
target_include_directories(nts PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Get all source files in the current directory.
set(SOURCES
    composite_configuration.cpp
    json_configuration.cpp)

# Add sources to the Network Testing Suite library.
target_sources(nts PRIVATE ${SOURCES})

# Get all test files in the current directory.
set(UNIT_TEST_SRCS
    composite_configuration.test.cpp
    json_configuration.test.cpp)

# Create an unit test for each module.
unit_test_foreach(${UNIT_TEST_SRCS})

# Copy the required files to the test folder.
file(COPY ${CMAKE_SOURCE_DIR}/config/json_config_tests.json
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
