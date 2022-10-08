# Copyright Bruno Silva, 2022. All rights reserved.

cmake_minimum_required(VERSION 3.1...3.24)

project(NetworkTestingSuite VERSION 0.0.0)

# Set the cpp standard.
set(CMAKE_CXX_STANDARD 14)

# Includes.
include(FetchContent)
include(GoogleTest)

# Enable testing of the project.
enable_testing()

# Configure the Network Testing Suite library.
add_library(nts STATIC)
add_subdirectory(source)
add_subdirectory(include)
# add_subdirectory(tests)

# Automatically fetch googletest.
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Find the Boost librry.
find_package(Boost 1.71.0 REQUIRED COMPONENTS system)
if(Boost_FOUND)
  include_directories($(Boost_INCLUDE_DIRS))
  target_link_libraries(nts ${Boost_LIBRARIES})
endif()
