# Copyright Bruno Silva, 2022. All rights reserved.

# Get all source files in the current directory.
set(SOURCES
    ipv4.cpp)

# Add sources to the Internet Protocol plugin.
target_sources(ip PRIVATE ${SOURCES})
