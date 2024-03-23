function(unit_test_foreach)
    # Create an unit test for each module.
    foreach(TEST IN LISTS ARGV)
        # Test name is file name without .cpp extension.
        get_filename_component(TEST_NAME ${TEST} NAME_WLE)
        # Create the test executable.
        add_executable(${TEST_NAME})
        # Add source files to the executable.
        target_sources(${TEST_NAME} PRIVATE ${TEST})
        # Get include directories of the Network Testing Suite.
        get_target_property(NTS_INCLUDE_DIRS nts INCLUDE_DIRECTORIES)
        # Add include directories.
        target_include_directories(${TEST_NAME} PUBLIC ${NTS_INCLUDE_DIRS})
        # Link to the required libraries.
        target_link_libraries(${TEST_NAME} GTest::gtest_main nts)
        # Automatically discover all tests.
        gtest_discover_tests(${TEST_NAME})
    endforeach()    
endfunction(unit_test_foreach)
