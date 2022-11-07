# Copyright Bruno Silva, 2022. All rights reserved.

# Get all source files in the current directory.
set(SOURCES
    icmp.cpp)

# Add sources to the ICMP plugin.
target_sources(icmp PRIVATE ${SOURCES})
