# Copyright Bruno Silva, 2022. All rights reserved.

# Configure the Ethernet plugin.
add_library(eth STATIC)
add_subdirectory(source)
add_subdirectory(include)
add_subdirectory(tests)

# Link to the Network Testing Suite library.
target_link_libraries(eth nts)
