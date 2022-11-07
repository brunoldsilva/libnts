# Copyright Bruno Silva, 2022. All rights reserved.

# Configure the Internet Control Message Protocol plugin.
add_library(icmp STATIC)
add_subdirectory(source)
add_subdirectory(include)
add_subdirectory(tests)

# Link to the Network Testing Suite library.
target_link_libraries(icmp nts)
