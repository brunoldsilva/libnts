# Add the current directory to the include path for the Network Testing Suite library.
target_include_directories(nts PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Get all source files in the current directory.
set(SOURCES
    logger_manager.cpp
    logger.cpp
    standard_logger.cpp)

# Add sources to the Network Testing Suite library.
target_sources(nts PRIVATE ${SOURCES})

# Get all test files in the current directory.
set(UNIT_TEST_SRCS
    log.test.cpp
    logger_manager.test.cpp
    standard_logger.test.cpp)

# Create an unit test for each module.
unit_test_foreach(${UNIT_TEST_SRCS})
