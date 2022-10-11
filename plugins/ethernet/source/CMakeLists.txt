# Copyright Bruno Silva, 2022. All rights reserved.

# Get all source files in the current directory.
set(SOURCES
    ethernet.cpp)

# Add sources to the Ethernet plugin.
target_sources(eth PRIVATE ${SOURCES})
